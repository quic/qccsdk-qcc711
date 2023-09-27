################################################################################
# Enumerated tag type processing
################################################################################
# Copyright (c) 2018-2021 Qualcomm Technologies International, Ltd.
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
import config, re
from config import BasicType, TagTypeInfo, TagError
from codegen import CodeGen
from hydra_db import SdbDescriptor
from codegen import HtfWriteLine
from tag_descriptor import TagDescriptor
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
# Class describing a single enumerated value
################################################################################
class TagTypeEnumVal(object):
    def __init__(self, parent):
        self.name = ""
        self.desc = ""
        self.value = 0
        self.parent = parent
        self.typeInfo = self.parent.type


    ############################################################################
    # Member-level equality check
    ############################################################################
    def __eq__(self, other):
        # Trivial equality test first, are they the same instance?
        if self is other:
            return True

        # Are they the same class?
        if not isinstance(other, TagTypeEnumVal):
            return False

        # They are the same if the name and enum values are identical.
        return self.name == other.name and self.value == other.value

    def __ne__(self, other):
        return not self.__eq__(other)


    ############################################################################
    # Get the enum val as a string identifier
    ############################################################################
    def getIdent(self):
        # Replace spaces and dashes with underscores; don't modify case
        ident = self.name.replace(" ", "_").replace("-", "_").replace(".", "_")

        # Prefix the parent enum definition's type string
        ident = self.parent.getTypeString(lowercase=False, baseNameOnly=True) + "_" + ident

        return ident


    ############################################################################
    # Load enum value from the RAM copy of the TCF file
    ############################################################################
    def loadTCF(self, tcf, sectionName):
        self.name = tcf.get(sectionName, "Name")
        self.desc = tcf.get(sectionName, "Desc")
        self.value = int(tcf.get(sectionName, "Value"))


    ############################################################################
    # Save enum value to a TCF file
    ############################################################################
    def saveTCF(self, tcf, sectionName):
        tcf.write("[%s]\n" % sectionName)
        tcf.write("Name = %s\n" % self.name)
        tcf.write("Desc = %s\n" % self.desc)
        tcf.write("Value = %d\n" % self.value)
        tcf.write("\n")


    ############################################################################
    # Load enum value from an XML tree
    ############################################################################
    def loadXML(self, enumValElem):
        self.name = enumValElem.get("name")
        self.value = int(enumValElem.get("value"))
        if enumValElem.text is not None:
            self.desc = enumValElem.text
        else:
            self.desc = ""

    ############################################################################
    # Load enum value from an TCFX tree
    ############################################################################
    def loadTCFX(self, enumValElem):
        self.name = enumValElem.get("Name")
        
        if enumValElem.get("Size") is not None or enumValElem.get("Type") is not None:
            raise TagError("\n\n\nOlder version of TCFX is being used, BITFIELD elements are not supposed to have Size / Type.\nPlease move to latest CTM release to edit the TCFX file.")
        
        self.value = config.ToInt(enumValElem.get("Default") , 1, self.parent.type.isSigned())
        if enumValElem.get("Description"):
            self.desc = enumValElem.get("Description").strip()
        else:
            self.desc = ""
            
    ############################################################################
    # Save enum value to an XML tree
    ############################################################################
    def saveXML(self, typeElem):
        enumElem = ET.SubElement(typeElem, "ENUM_VALUE")
        enumElem.set("name", self.name)
        enumElem.set("value", str(self.value))
        enumElem.text = self.desc
		
    ############################################################################
    # Save enum value to an TCFX tree
    ############################################################################
    def saveTCFX(self, typeElem):
        enumElem = ET.SubElement(typeElem, "ELEMENTS")
        enumElem.set("Name", self.name)
        enumElem.set("Default", str ( config.ToHex (self.value, 1) ))
        enumElem.set("Description", str(self.desc))


################################################################################
# Class describing an enumerated Tag Type
################################################################################
class TagTypeEnum(TagDescriptor):
    def __init__(self, parent):
        TagDescriptor.__init__(self)
        
        self.name = ""
        self.desc = ""
        self.type = BasicType()
        self.vals = []
        self.default = None
        self.original = []
        self.parent = parent
        self.vListObj = None
        self.wrappingType = TagTypeInfo.ENUM


    ############################################################################
    # Member-level equality check
    ############################################################################
    def __eq__(self, other):
        # Trivial equality test first, are they the same instance?
        if self is other:
            return True

        # Are they the same class?
        if not isinstance(other, TagTypeEnum):
            return False

        # They are the same if the name, type and enum values are identical.
        if self.name != other.name or len(self.vals) != len(other.vals) or self.type.dataType != other.type.dataType:
            return False

        for i in range(len(self.vals)):
            if self.vals[i] != other.vals[i]:
                return False


        # Note that we deliberately do not compare the default value as this
        # doesn't affect type generation.

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
    def addHashInfo(self, d, tag, forHash=False):

        if forHash:
            # When generating the enum hash we don't use the parent tag name
            # for the label. Vtags for enums embedded in an array type would
            # end up with different labels and thus different hashes even
            # though the enum type is actually the same.
            #
            d.addCommonFields(self.name, self.name, self.getTypeString())

            # Extend the hash with the enum val definitions. These are dummy
            # entries that don't get used when writing the enum definition to
            # the database
            for enumVal in self.vals:
                d.addField("enum_label", enumVal.name)
                d.addField("enum_value", str(enumVal.value))
                if enumVal.desc != "":
                    d.addField("enum_description", enumVal.desc)
        else:    
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
            d.addCommonFields(name, tagName, self.getTypeString())
            d.addDescription(desc)

            if self.isVtagPublished:
                # VTag has been found in filter list. Read info 
                d.addTagData(self.getVtagNumber(), False)


    ############################################################################
    # Get the maximum size of the tag, in bytes
    ############################################################################
    def getMaxLength(self):
        return self.type.size


    ############################################################################
    # Load enum definition from the RAM copy of the TCF file
    ############################################################################
    def loadTCF(self, tcf, sectionName):
        sectionName += "%d" % TagTypeInfo.ENUM
        self.name = tcf.get(sectionName, "Name")
        self.type.size = int(tcf.get(sectionName, "TagLength"))
        self.type.signed = int(tcf.get(sectionName, "Signed"))
        self.type.evalType()

        sectionName += "_Data"
        for i in range(int(tcf.get(sectionName, "Num"))):
            enumVal = TagTypeEnumVal(self)
            enumVal.loadTCF(tcf, sectionName+"_%d" % i)
            self.vals.append(enumVal)

        self.default = TagTypeEnumVal(self)
        self.default.loadTCF(tcf, sectionName+"_Default")
        self.type.value = self.default.value

        # Validate that the default is a defined enumeration value
        for enumVal in self.vals:
            if self.default.name == enumVal.name:
                # We've found a match so just return
                return

        # If we get here there was no match for the default enum name
        raise TagError("%s: No previous definition for default enum value %s" % (sectionName, self.default.name))


    ############################################################################
    # Save enum to a TCF file
    ############################################################################
    def saveTCF(self, tcf, sectionName):
        sectionName += "%d" % TagTypeInfo.ENUM
        tcf.write("[%s]\n" % sectionName)
        tcf.write("Name = %s\n" % self.name)
        tcf.write("TagLength = %d\n" % self.type.size)
        tcf.write("Signed = %d\n" % self.type.signed)
        tcf.write("\n")

        sectionName += "_Data"
        tcf.write("[%s]\n" % sectionName)
        tcf.write("Num = %d\n" % len(self.vals))
        tcf.write("\n")

        i = 0
        for enumVal in self.vals:
            enumVal.saveTCF(tcf, "%s_%d" % (sectionName, i))
            i += 1
        self.default.saveTCF(tcf, "%s_Default" % sectionName)


    ############################################################################
    # Save enum to an HTF file
    ############################################################################
    def saveHTF(self, htf, indent, elemSuffix=""):
        # Write the enum default value as a label rather than hex value
        enumStr = self.default.getIdent() + elemSuffix

        history = ""
        sep = ""
        for old in self.original:
            history += sep + old.getIdent() + elemSuffix
            sep = " -> "
        if history != "":
            history += sep + enumStr
            history = "\t[M] %s" % history

        # Get associated vtag name for sub-element in a physical tag
        if self.parent is None or self.getTag().isVtag or self.vListObj is None:
            vtagName = ""
        else:
            vtagName = "\t[V] %s" % self.vListObj.tagName

        if not config.options.compactHTF:
            enumStr += "\t/* %s%s%s */" % (SdbDescriptor.makeShortName(self.name), vtagName, history)
        HtfWriteLine(htf, enumStr, indent, cont=(indent>0))


    ############################################################################
    # Merge tag values from an .nvm file
    ############################################################################
    def mergeNVM(self, tagVal):
        if len(tagVal) < self.type.size:
            raise TagError("Enum %s expects %d bytes in NVM file" % (self.name, self.type.size))

        newVal = tagVal[:self.type.size]
        tagVal = tagVal[self.type.size:]

        # Get the new default value as an integer first
        enumInt = 0
        shift = 0
        for byte in newVal:
            enumInt = enumInt | (byte << shift)
            shift += 8

        if self.default.value == enumInt:
            # Nothing to update so just return now
            return tagVal

        # Update the default value if it has changed, also validating that it is a defined enum val
        self.original.append(self.default)

        enum = None
        for enumVal in self.vals:
            if enumVal.value == enumInt:
                enum = enumVal
                break

        if enum is None:
            raise TagError("ENUM: No <ENUM_VALUE> definition for %s new default value %d" % (self.name, enumInt))

        # Update the default
        self.default = TagTypeEnumVal(self)
        self.default.name = enum.name
        self.default.desc = enum.desc
        self.default.value = enum.value

        return tagVal
        
        
    ############################################################################
    # Merge tag values from an .nvmx file
    ############################################################################
    def mergeNVMX(self, nvmxTagType):
        if nvmxTagType.get("Name") != self.name and not config.options.alignToTCFX:
            raise TagError("NVMX Tag is not aligned with the Elements.")

        self.default.value = config.ToInt(nvmxTagType.get("Value"), self.type.size, self.type.isSigned())

    ############################################################################
    # Save enum to an NVM file
    ############################################################################
    def saveNVM(self, nvm):
        default = self.default.value
        for _ in range(self.type.size):
            nvm.write(" %02X" % (default & 0xFF))
            default >>= 8


    ############################################################################
    # Load enum from an XML tree
    ############################################################################
    def loadXML(self, xmlTagType):
        self.name = xmlTagType.get("name")
        self.type.size = int(xmlTagType.get("length"))

        xmlEnumType = xmlTagType.find("ENUM")
        if xmlEnumType is None:
            raise TagError("Malformed XML: ENUM type is missing <ENUm> child element")

        if xmlEnumType.get("signed") is not None:
            self.type.signed = 1
        else:
            self.type.signed = 0
        self.type.evalType()

        xmlEnumElems = xmlEnumType.findall("ENUM_VALUE")
        if len(xmlEnumElems) == 0:
            raise TagError("Malformed XML: <ENUM> doesn't have any <ENUM_VALUE> child elements")

        for xmlEnumElem in xmlEnumElems:
            enumVal = TagTypeEnumVal(self)
            enumVal.loadXML(xmlEnumElem)
            self.vals.append(enumVal)

        self.default = TagTypeEnumVal(self)
        self.default.name = xmlEnumType.get("default")

        # Validate that the default is a defined enumeration value
        for enumVal in self.vals:
            if self.default.name == enumVal.name:
                # We've found a match so just return
                self.default.desc = enumVal.desc
                self.default.value = enumVal.value
                return

        # If we get here there was no match for the default enum name
        raise TagError("ENUM: No <ENUM_VALUE> definition for default enum value %s" % self.default.name)

    ############################################################################
    # Load enum from an TCFX tree
    ############################################################################
    def loadTCFX(self, tcfxTagType):
        self.name = tcfxTagType.get("Name")
        self.type.size = int(tcfxTagType.get("Size"))

        if tcfxTagType.get("Type") != "ENUM":
            raise TagError("Malformed TCFX: ENUM type is incorrect")

        tmp = tcfxTagType.get("Signed")
        self.type.signed = int ( not ( (not tmp) or (tmp.lower() == "false") ) )
        
        self.type.evalType()

        tcfxEnumElems = tcfxTagType.findall("ELEMENTS")
        if len(tcfxEnumElems) == 0:
            raise TagError("Malformed TCFX: <ENUM> doesn't have any child elements")

        for tcfxEnumElem in tcfxEnumElems:
            enumVal = TagTypeEnumVal(self)
            enumVal.loadTCFX(tcfxEnumElem)
            self.vals.append(enumVal)

        self.default = TagTypeEnumVal(self)
        self.default.value = config.ToInt(tcfxTagType.get("Default"), self.type.size, self.type.isSigned())

        # Validate that the default is a defined enumeration value
        for enumVal in self.vals:
            if self.default.value == enumVal.value:
                # We've found a match so just return
                self.default.desc = enumVal.desc
                self.default.name = enumVal.name
                self.default.value = enumVal.value
                return

        # If we get here there was no match for the default enum name
        raise TagError("ENUM: No <ENUM_VALUE> definition for default enum value %s" % self.default.name)


    ############################################################################
    # Save enum to an XML tree
    ############################################################################
    def saveXML(self, typeElem):
        typeElem = ET.SubElement(typeElem, "TAG_TYPE")
        typeElem.set("type", "ENUM")
        typeElem.set("name", self.name)
        typeElem.set("length", str(self.type.size))

        enumElem = ET.SubElement(typeElem, "ENUM")
        if self.type.signed:
            enumElem.set("signed", "")
        enumElem.set("default", self.default.name)

        for enumVal in self.vals:
            enumVal.saveXML(enumElem)

    ############################################################################
    # Save enum to an TCFX tree
    ############################################################################
    def saveTCFX(self, typeElem):
        # Validate that the default is a defined enumeration value
        for enumVal in self.vals:
            if self.default.name == enumVal.name:
                self.default.value = enumVal.value
        typeElem = ET.SubElement(typeElem, "ELEMENTS")
        typeElem.set("Name", self.name)
        typeElem.set("Type", "ENUM")
        typeElem.set("Size", str(self.type.size))
        typeElem.set("Default", config.ToHex(self.default.value, self.type.size))
        typeElem.set("Signed", str(bool(self.type.signed)).lower())

        for enumVal in self.vals:
            enumVal.saveTCFX(typeElem)
        
    ############################################################################
    # Save enum to an NVMX tree
    ############################################################################
    def saveNVMX(self, typeElem):
        typeElem = ET.SubElement(typeElem, "ELEMENTS")
        typeElem.set("Name", self.name)
        typeElem.set("Value", config.ToHex(self.default.value, self.type.size))

    ############################################################################
    # Save enum to the system configuration database
    ############################################################################
    def saveSDB(self, sdb, tag):

        # Calculate the hash for this enumeration and check if it is already in the DB
        d = self.getSdbDescriptor(tag, forHash=True)
        md5 = d.getHash()
        sdb.sql.execute("SELECT enum_uid FROM enum_defs where hash='%s'" % md5)
        hashed = sdb.sql.fetchall()

        if len(hashed) == 0:
            # add enum definition to database
            sdb.sql.execute("INSERT INTO enum_defs (enum_uid, enum_name, hash) VALUES(NULL, ?, ?)", (self.getTypeString(), md5))
            sdb.sql.execute("SELECT max(enum_uid) FROM enum_defs")
            enumUid = (sdb.sql.fetchone())[0]

            sdb.recordEnum(enumUid, self.getTypeString(), md5)

            # add enum_entry definitions to database
            for enumVal in self.vals:
                #if ' ' in enumVal.name:
                #    #raise TagError("Malformed ENUM %s: spaces not allowed in label '%s'" % (self.name, enumVal.name))
                #    print "WARING! Malformed ENUM %s: spaces not allowed in label '%s'" % (self.name, enumVal.name)

                sql = "INSERT INTO enum_entry (enum_uid, enum_label, enum_value, enum_description) VALUES (?,?,?,?)"
                sqlValues = (enumUid, enumVal.getIdent(), enumVal.value, enumVal.desc)
                sdb.sql.execute(sql, sqlValues)
        else:
            enumUid = hashed[0][0]

        # Now add the config element entry as well. Recreate the descriptor using
        # just the common fields to ensure the hash is correct
        d = self.getSdbDescriptor(tag)
        elemUid = d.saveSDB(sdb)

        # Cross-reference the config_element for this type to the FW release
        sdb.xrefElement(elemUid, enumUid, TagTypeInfo.ENUM)

        return elemUid, enumUid


    ############################################################################
    # Get the ROM default value for this type, for inserting into the SDB
    ############################################################################
    def getSdbDefault(self, tag):
        # The enum default is the value of the underlying basic type, so just return it
        return [self.default.value]


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
                print("saveVLIST tagtype_enum " + expname)


    ############################################################################
    # Generate tag data types header information
    ############################################################################
    def genTagDataTypes(self, file, generatedTypes, indent):
        
        typeName = CodeGen.makeUpperIdent("CFG_ENUM_" + self.name + "_TYPE")
        if not CodeGen.checkUnique(generatedTypes, typeName, self):
            return

        file.write("\ntypedef enum \n{")
        count = 0
        for enumVal in self.vals:
            if count: file.write(",")
            file.write("\n")

            enumName = CodeGen.makeIdent(self.name + "_" + enumVal.name)
            file.write("%s = %s" % (CodeGen.padIdentMid("    " + enumName), enumVal.value))

            count += 1

        file.write("\n")
        file.write("} %s;" % typeName)


    ############################################################################
    # Generate tag element information
    ############################################################################
    def genTagElement(self, file, indent):
        typeName = CodeGen.makeUpperIdent("CFG_ENUM_" + self.name + "_TYPE")
        file.write(" "*indent + CodeGen.padIdentShort(typeName) + CodeGen.makeIdent("Cfg_" + self.name) + ";")


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
        file.write(CodeGen.padIdentMid(" "*indent + CodeGen.makeIdent(self.name + "_" + self.default.name)))


    ############################################################################
    # Generate tag format information for HTML
    ############################################################################
    def genTagUserFormat(self, file, indent, byteIndex):
        file.write(" "*indent + "<b>" + self.type.getByteRangeStr(byteIndex))
        byteIndex += self.type.size

        file.write(" : %s</b>\n" % self.name)
        file.write("<ul>\n")

        indent += 4
        file.write(" "*indent + "<b>Possible Values :</b>\n")
        file.write("<ul>\n")

        count = 0
        for enumVal in self.vals:
            if count: file.write("\n<br>\n")
            file.write(CodeGen.padIdentMid(" "*(indent+4) + CodeGen.makeIdent(enumVal.name)))
            file.write(" = %d" % enumVal.value)
            count += 1
        file.write("\n</ul>\n")
        file.write(" "*indent + "<b>Default :</b> " + CodeGen.makeIdent(self.default.name))
        file.write("\n</ul>\n")

        return byteIndex
