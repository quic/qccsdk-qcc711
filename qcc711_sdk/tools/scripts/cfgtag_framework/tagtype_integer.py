################################################################################
# Integer tag type processing
################################################################################
# Copyright (c) 2018-2020 Qualcomm Technologies International, Ltd.
# All Rights Reserved
# Confidential and Proprietary - Qualcomm Technologies International, Ltd.
################################################################################


################################################################################
# Library Imports
################################################################################
from __future__ import print_function
try:
    from builtins import str
except ImportError:
    pass
from codegen import CodeGen
import config
from config import BasicType, TagTypeInfo, TagError
from tag_descriptor import TagDescriptor
from hydra_db import SdbDescriptor
from codegen import HtfWriteLine
import tag_filter
import tag_descriptor
from xml_wrapper import ET


################################################################################
# Global Variables
################################################################################


################################################################################
# Local Functions
################################################################################



################################################################################
# Class describing an integer Tag Type
################################################################################
class TagTypeInt(TagDescriptor):
    def __init__(self, parent):
        TagDescriptor.__init__(self)

        self.name = ""
        self.desc = ""
        self.default = 0
        self.original = []
        self.min = 0
        self.max = 0
        self.type = BasicType()
        self.val = 0  # Only used so far to store max count of Var Array
        self.parent = parent
        self.vListObj = None
        self.wrappingType = TagTypeInfo.INTEGER


    ############################################################################
    # Member-level equality check
    ############################################################################
    def __eq__(self, other):
        # Trivial equality test first, are they the same instance?
        if self is other:
            return True

        # Are they the same class?
        if not isinstance(other, TagTypeInt):
            return False

        # They are the same if the name and bitfields are identical.
        if self.name != other.name or self.min != other.min or self.max != other.max:
            return False

        return True

    def __ne__(self, other):
        return not self.__eq__(other)


    ############################################################################
    # Return the top-level tag object that owns this type
    ############################################################################
    def getTag(self):
        return self.parent.getTag()


    ############################################################################
    # Get a database descriptor for this type
    ############################################################################
    def getSdbDescriptor(self, tag, forHash=False):
        
        d = SdbDescriptor()
        
        self.addHashInfo(d, tag, forHash)

        return d
    

    ############################################################################
    # Add tag information to be used for MD5 calculation
    ############################################################################  
    def addHashInfo(self, d, tag, addHashData = True):
        
        if tag is not None:
            name = tag.name
            desc = tag.desc
        else:
            name = self.name
            desc= self.desc
            
        if self.isVtagPublished:
            # VTag has been found in filter list. Read info
            tagName = self.getVtagName() 
        else:
            tagName = name
            
        d.addCommonFields(name, tagName, self.type.getTypeString())
        d.addDescription(desc)
        d.addRange(self.min, self.max)

        if self.isVtagPublished:
            # VTag has been found in filter list. Read info 
            d.addTagData(self.getVtagNumber(), False)


    ############################################################################
    # Load integer value definition from a TCF file
    ############################################################################
    def loadTCF(self, tcf, sectionName):
        sectionName += "%d" % TagTypeInfo.INTEGER
        self.name = tcf.get(sectionName, "Name")
        self.desc = tcf.get(sectionName, "TagTypeDescription")
        self.type.size = int(tcf.get(sectionName, "TagLength"))
        self.type.signed = int(tcf.get(sectionName, "Signed"))
        self.type.evalType()

        self.min = int(tcf.get(sectionName, "TagTypeValueMin"))
        self.max = int(tcf.get(sectionName, "TagTypeValueMax"))
        self.default = int(tcf.get(sectionName, "TagTypeValueDefault"))
        self.type.value = self.default

        # If min & max are both zero with a non-zero default then adjust the
        # range of the integer to allow any possible value for the size.
        # Record the fact we did this to allow saving back to TCF/XML to preserve
        # the original 0/0 range.
        if self.min == 0 and self.max == 0 and self.default != 0:
            if config.options.debug:
                print("%s: invalid integer, default %d is outside range min %d - max %d; setting max range" % (sectionName, self.default, self.min, self.max))
            self.min, self.max = self.type.getTypeRange()
            self.maxRangeExtended = True
        else:
            self.maxRangeExtended = False

        if self.max < self.min:
            print("%s: invalid integer, min %d cannot be greater than max %d" % (sectionName, self.min, self.max))


    ############################################################################
    # Save integer value to a TCF file
    ############################################################################
    def saveTCF(self, tcf, sectionName):
        if self.maxRangeExtended:
            min = max = 0
        else:
            min = self.min
            max = self.max

        tcf.write("[%s%d]\n" % (sectionName, TagTypeInfo.INTEGER))
        tcf.write("Name = %s\n" % self.name)
        tcf.write("TagLength = %s\n" % self.type.size)
        tcf.write("Signed = %d\n" % self.type.signed)
        tcf.write("TagTypeValueMin = %d\n" % min)
        tcf.write("TagTypeValueMax = %d\n" % max)
        tcf.write("TagTypeValueDefault = %d\n" % self.default)
        tcf.write("TagTypeDescription = %s\n" % self.desc)
        tcf.write("\n")


    ############################################################################
    # Save integer value to an HTF file
    ############################################################################
    def saveHTF(self, htf, indent, elemSuffix="", octetString=False):
        # TBD: this might be better emitting as decimal when signed?
        getVal = lambda v: self.type.forHex(v) if self.type.isSigned() else v

        intVal = getVal(self.default)

        intStr = ""
        if not octetString: intStr += "0x"
        intStr += self.type.getHexFormatSpec(zeroPad=True) % (intVal)

        history = ""
        sep = "0x"
        for old in self.original:
            history += sep + (self.type.getHexFormatSpec(zeroPad=True) % (old))
            sep = " -> 0x"
        if history != "":
            history += " -> " + intStr
            history = "\t[M] %s" % history

        # Get associated vtag name for sub-element in a physical tag
        if self.parent is None or self.getTag().isVtag or self.vListObj is None:
            vtagName = ""
        else:
            vtagName = "\t[V] %s" % self.vListObj.tagName

        intStr += elemSuffix
        if not config.options.compactHTF and not octetString:
            intStr += "\t/* %s%s%s */" % (SdbDescriptor.makeShortName(self.name), vtagName, history)

        if octetString:
            # No multi-line formatting for octet strings
            htf.write(intStr)
        else:
            HtfWriteLine(htf, intStr, indent, cont=(indent>0))


    ############################################################################
    # Merge tag values from an .nvm file
    ############################################################################
    def mergeNVM(self, tagVal):
        if len(tagVal) < self.type.size:
            raise TagError("Integer %s expects %d bytes in NVM file" % (self.name, self.type.size))

        newVal = tagVal[:self.type.size]
        tagVal = tagVal[self.type.size:]

        # Get the new default value as an integer first
        newInt = 0
        shift = 0
        for byte in newVal:
            newInt = newInt | (byte << shift)
            shift += 8

        newInt = self.type.fromHex(newInt)

        if self.default == newInt:
            # Nothing to update so just return now
            return tagVal

        # Update the default value if it has changed
        self.original.append(self.default)
        self.default = newInt

        return tagVal
        
        
    ############################################################################
    # Merge tag values from an .nvm file
    ############################################################################
    def mergeNVMX(self, arrayElem):
        val = arrayElem.get("Value")
        
        if not val:
            raise TagError("%s : invalid Value" %(self.name))
        
        self.default = config.ToInt(val, self.type.size, self.type.isSigned())
        
        self.type.value = self.default

        if self.default > self.max and self.default < self.min:
            print("%s: invalid Value, cannot be less than min %d or cannot be greater than max %d" % (self.name, self.default, self.min, self.max))
            
    ############################################################################
    # Save integer value to an NVM file
    ############################################################################
    def saveNVM(self, nvm):
        default = self.default
        for _ in range(self.type.size):
            nvm.write(" %02X" % (default & 0xFF))
            default >>= 8


    ############################################################################
    # Load integer value from an XML file
    ############################################################################
    def loadXML(self, xmlTagType):
        self.name = xmlTagType.get("name")
        self.type.size = int(xmlTagType.get("length"))

        xmlValue = xmlTagType.find("VALUE")
        if xmlValue is None:
            raise TagError("Malformed XML: VALUE type doesn't have <VALUE> element")

        if xmlValue.text is not None:
            self.desc = xmlValue.text
        else:
            self.desc = ""

        tmp = xmlValue.get("signed")
        if tmp is not None:
            self.type.signed = 1
        else:
            self.type.signed = 0

        self.type.evalType()

        self.min = int(xmlValue.get("min"))
        self.max = int(xmlValue.get("max"))
        self.default = int(xmlValue.get("default"))
        self.type.value = self.default

        if self.max < self.min:
            print("%s: invalid integer, min %d cannot be greater than max %d" % (self.name, self.min, self.max))
    
    ############################################################################
    # Load integer value from an TCFX file
    ############################################################################
    def loadTCFX(self, tcfxTagType, isArrayElem=False, isElementType=False, isVariableElementType=False):
        if isElementType or isVariableElementType:
            self.name = tcfxTagType.get("VariableName")
        else:
            self.name = tcfxTagType.get("Name")

        self.desc = tcfxTagType.get("Description", "").strip()
        if self.desc is None:
            self.desc = ""
            
        if not isArrayElem:
            if isElementType:
                self.type.size  = int(tcfxTagType.get("ElementSize"))
            elif isVariableElementType:
                self.type.size  = int(tcfxTagType.get("VariableSize"))
            else:
                self.type.size  = int(tcfxTagType.get("Size"))

            tmp = tcfxTagType.get("Signed")
            self.type.signed = int ( not ( (not tmp) or (tmp.lower() == "false") ) )
                
            if isVariableElementType:
                self.max    = int(tcfxTagType.get("Max"))
            else:
                self.max        = config.ToInt(tcfxTagType.get("Max"), self.type.size, self.type.isSigned())
                self.min        = config.ToInt(tcfxTagType.get("Min"), self.type.size, self.type.isSigned())
        
        if tcfxTagType.get("Default"):
            self.default    = config.ToInt(tcfxTagType.get("Default"), self.type.size, self.type.isSigned())
        
        self.type.value = self.default

        self.type.evalType()
        
        if self.min == 0 and self.max == 0 and self.default != 0:
            if config.options.debug:
                print("%s: invalid integer, default %d is outside range min %d - max %d; setting max range" % (self.name, self.default, self.min, self.max))
            self.min, self.max = self.type.getTypeRange()
            self.maxRangeExtended = True
        else:
            self.maxRangeExtended = False
           
        if self.max < self.min:
            print("%s: invalid integer, min %d cannot be greater than max %d" % (self.name, self.min, self.max))

    ############################################################################
    # Save integer value to an XML tree
    ############################################################################
    def saveXML(self, typeElem, isArrayElem=False):
        if self.maxRangeExtended and config.options.compat:
            min = max = 0
        else:
            min = self.min
            max = self.max

        if isArrayElem:
            typeElem = ET.SubElement(typeElem, "ARRAY")
        else:
            typeElem = ET.SubElement(typeElem, "TAG_TYPE")
        typeElem.set("type", "VALUE")
        typeElem.set("name", self.name)
        typeElem.set("length", str(self.type.size))

        valueElem = ET.SubElement(typeElem, "VALUE")
        if self.type.signed:
            valueElem.set("signed", "")
        valueElem.set("min", str(self.min))
        valueElem.set("max", str(self.max))
        valueElem.set("default", str(self.default))
        valueElem.text = self.desc
    
    ############################################################################
    # Save integer value to an TCFX tree
    ############################################################################
    def saveTCFX (self, typeElem, isFixedArrayElem=False,  isElementType=False):
        if self.maxRangeExtended and config.options.compat:
            min = max = 0
        else:
            min = self.min
            max = self.max

        typeElem = ET.SubElement(typeElem, "ELEMENTS")
        typeElem.set("Name", self.name)
        
        if not isFixedArrayElem:
            if not isElementType:
                typeElem.set("Type", "INTEGER")
                typeElem.set("Size", str(self.type.size))

            typeElem.set("Min", config.ToHex(self.min , self.type.size))
            typeElem.set("Max", config.ToHex(self.max, self.type.size))
            
        typeElem.set("Default", config.ToHex(self.default, self.type.size))
        
        if not isFixedArrayElem:
            typeElem.set("Signed", str(bool(self.type.signed)).lower())
            
        typeElem.set("Description", str(self.desc))

    ############################################################################
    # Save integer value to an NVMX tree
    ############################################################################
    def saveNVMX (self, typeElem):
        typeElem = ET.SubElement(typeElem, "ELEMENTS")
        typeElem.set("Name", self.name)
        typeElem.set("Value", config.ToHex(self.default, self.type.size))
        
    ############################################################################
    # Save Tag Type to the system configuration database
    ############################################################################
    def saveSDB(self, sdb, tag):

        # Get the type descriptor then save to the database (or retrieve UID if already present)
        d = self.getSdbDescriptor(tag)
        elemUid = d.saveSDB(sdb)

        # Cross-reference the config_element for this type to the FW release
        sdb.xrefElement(elemUid)

        return elemUid, None


    ############################################################################
    # Get the ROM default value for this type, for inserting into the SDB
    ############################################################################
    def getSdbDefault(self, tag):
        # We're a simple integer so just return the underlying basic type's value
        return [self.default]


    ############################################################################
    # Save struct to an VLIST file
    ############################################################################
    def saveVLIST(self, vlist, tag):
        
        expname = self.getTypeStringRecursive()
        # Check the filtered list
        if vlist.filter.vtagEnabled(expname):
            # Make sure this is published in case it is not in the known VTag list
            self.isVtagPublished = True
            self.addHashInfo(self, tag)
            md5 = self.getHash(shortHash=True)
            
            tagName = self.getTagName()
            elemIdx = self.readTableElementIdx()
            if elemIdx:
                tagName = tagName + "_" + elemIdx 
            
            if not tag_descriptor.vListInfo.isTagDefined(expname, md5):
                vlist.SaveTagInfo(expname, md5, int(self.values[self.names.index("psid")]), tagName)
                
            if config.options.debug:
                print("saveVLIST tagtype_integer " + expname)


    ############################################################################
    # Generate tag data types header information
    ############################################################################
    def genTagDataTypes(self, file, generatedTypes, indent):
        
        # Hmm, if there is indent then we don't generate anything? Not sure what this is yet
        if indent > 0:
            return
        
        typeStr = self.type.getTypeString()
        typeName = CodeGen.makeUpperIdent("CFG_" + self.name + "_TYPE")
        if not CodeGen.checkUnique(generatedTypes, typeName, self):
            return
        file.write("\n/*  %s  */\n" % self.desc)
        file.write("typedef %s%s;\n" % (typeStr.ljust(10), typeName))


    ############################################################################
    # Generate tag element information
    ############################################################################
    def genTagElement(self, file, indent):
        typeStr = self.type.getTypeString()
        file.write((" "*indent + typeStr).ljust(11) + CodeGen.makeIdent("Cfg_" + self.name) + ";")


    ############################################################################
    # Generate tag element reference information
    ############################################################################
    def genTagElementRef(self, file, baseDefine, baseElem):
        elemName = baseElem+CodeGen.makeIdent("Cfg_"+self.name)
        file.write("#define  %s" % CodeGen.padTo(CodeGen.makeUpperIdent("%s_%s_PTR" % (baseDefine, self.name)), 40))
        file.write(" ((UINT8 *) &(%s))\n" % elemName)

        file.write("#define  %s" % CodeGen.padTo(CodeGen.makeUpperIdent("%s_%s" % (baseDefine, self.name)), 40))
        file.write(" (%s)\n" % elemName)


    ############################################################################
    # Generate tag default values
    ############################################################################
    def genTagDefaultData(self, file, indent):
        typeStr = self.type.getTypeString()

        # Backwards compatibility: TagCfg.exe always emits signed numbers as
        # 32-bit unsigned hex (and casts to INT8 etc.). This seems odd, so when
        # not using compatibility mode just emit signed numbers as decimal.
        # Otherwise the signed value is adjusted to be a positive 32-bit value
        # (which will be cast back to the appropriate type by the compiler).
        #
        if config.options.compat or not self.type.signed:
            hexPrefix = "0x"
            val = self.default
            if config.options.compat and val < 0:
                val += 0x100000000
        else:
            # Not in compatibility mode *and* the integer is signed
            hexPrefix = ""
            val = self.default

        file.write(" "*indent + "(" + typeStr + ")" + hexPrefix + self.type.getFormatSpec() % val)


    ############################################################################
    # Generate tag format information for HTML
    ############################################################################
    def genTagUserFormat(self, file, indent, byteIndex):
        file.write(" "*indent + "<b>" + self.type.getByteRangeStr(byteIndex))
        byteIndex += self.type.size

        if config.options.compat and self.type.size==1:
            file.write(" ")
        file.write(": %s:</b>\n" % self.name)
        file.write("<ul>\n")

        indent += 4
        file.write(" "*indent + ("<b>Range   : </b>Min : 0x"+self.type.getHexFormatSpec()+", (%dd)") % (self.type.forHex(self.min), self.min))
        file.write(" "*(indent+8) + ("  Max : 0x"+self.type.getHexFormatSpec()+", (%dd)\n") % (self.type.forHex(self.max), self.max))
        file.write("<br>\n")
        file.write(" "*indent + ("<b>Default :</b> 0x"+self.type.getHexFormatSpec()+", (%dd)\n") % (self.type.forHex(self.default), self.default))
        file.write("</ul>\n")

        return byteIndex
