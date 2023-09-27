################################################################################
# Generic definitions for tag types.
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
import config
from config import BasicType, TagTypeInfo, TagError
from tag_descriptor import TagDescriptor
from tagtype_integer import TagTypeInt
from tagtype_enum import TagTypeEnum
from tagtype_bits import TagTypeBits
from tagtype_struct import TagTypeStruct
from codegen import CodeGen
from hydra_db import SdbDescriptor
from codegen import HtfWriteLine
import tag_descriptor
from xml_wrapper import ET


################################################################################
# Global Variables
################################################################################


################################################################################
# Local Functions
################################################################################


################################################################################
# TagType Class
#
# Defines a type for a particular tag. May contain nested types
################################################################################
class TagType(TagDescriptor):
    def __init__(self, parent):
        
        TagDescriptor.__init__(self)
        
        self.type = 0
        self.size = 0
        self.typeInfo = None
        self.parent = parent


    ############################################################################
    # Member-level equality check
    ############################################################################
    def __eq__(self, other):
        # Trivial equality test first, are they the same instance?
        if self is other:
            return True

        # Are they the same class?
        if not isinstance(other, TagType):
            return False

        # They are the same if the type and size are identical.
        if self.type != other.type or self.size != other.size or self.typeInfo != other.typeInfo:
            return False

        return True

    def __ne__(self, other):
        return not self.__eq__(other)


    ############################################################################
    # Internal helper function to call the correct constructor for a give type
    ############################################################################
    def __constructTypeInfo__(self):
        if self.type == TagTypeInfo.INTEGER:
            self.typeInfo = TagTypeInt(self.parent)
        elif self.type == TagTypeInfo.ENUM:
            self.typeInfo = TagTypeEnum(self.parent)
        elif self.type == TagTypeInfo.BITFIELD:
            self.typeInfo = TagTypeBits(self.parent)
        elif self.type == TagTypeInfo.STRUCTURE:
            self.typeInfo = TagTypeStruct(self.parent)
        elif self.type == TagTypeInfo.VARIABLE_ARRAY:
            self.typeInfo = TagTypeArray(self.parent, TagTypeInfo.VARIABLE_ARRAY)
        elif self.type == TagTypeInfo.FIXED_ARRAY:
            self.typeInfo = TagTypeArray(self.parent, TagTypeInfo.FIXED_ARRAY)
        elif self.type == TagTypeInfo.STRUCT_ARRAY:
            self.typeInfo = TagTypeArray(self.parent, TagTypeInfo.STRUCT_ARRAY)
        else:
            self.typeInfo = None


    ############################################################################
    # Get a database descriptor for this type
    ############################################################################
    def getSdbDescriptor(self, tag, forHash=False):
        return self.typeInfo.getSdbDescriptor(tag, forHash=forHash)


    ############################################################################
    # Get a database descriptor for this type
    ############################################################################
    def addHashInfo(self, d, tag):
        return self.typeInfo.addHashInfo(d, tag)


    ############################################################################
    # Get the maximum size of the tag, in bytes
    ############################################################################
    def getMaxLength(self):
        return self.typeInfo.getMaxLength()

    ############################################################################
    # Get the type alignment requirement, in bytes
    ############################################################################
    def getAlignment(self):
        return self.typeInfo.getAlignment()

    ############################################################################
    # Determine if the tag type contains a variable-length array
    ############################################################################
    def hasVarArray(self):
        # Short-cut the atomic types here to save some code
        if self.type == TagTypeInfo.INTEGER or self.type == TagTypeInfo.ENUM or self.type == TagTypeInfo.BITFIELD:
            return False
        else:
            return self.typeInfo.hasVarArray()


    ############################################################################
    # Extract vtag definitions from this tag type
    ############################################################################
    def extractVtags(self, physTag, vtags):
        return self.typeInfo.extractVtags(physTag, vtags)


    ############################################################################
    # Load Tag Type definition from the RAM copy of the TCF file
    ############################################################################
    def loadTCF(self, tcf, sectionName):
        self.type = int(tcf.get(sectionName, "TagType"))
        self.__constructTypeInfo__()
        if self.typeInfo is None:
            raise TagError("%s -- Unknown tag type: %d" % (sectionName, self.type))

        self.typeInfo.loadTCF(tcf, sectionName)


    ############################################################################
    # Save Tag Type to a TCF file
    ############################################################################
    def saveTCF(self, tcf, sectionName):
        tcf.write("[%s]\n" % sectionName)
        tcf.write("TagType = %d\n" % self.type)
        tcf.write("\n")

        self.typeInfo.saveTCF(tcf, sectionName)


    ############################################################################
    # Save Tag Type to an HTF file
    ############################################################################
    def saveHTF(self, htf, indent, elemSuffix=""):
        self.typeInfo.saveHTF(htf, indent, elemSuffix)


    ############################################################################
    # Merge tag values from an .nvm file
    ############################################################################
    def mergeNVM(self, tagVal):
        return self.typeInfo.mergeNVM(tagVal)

    ############################################################################
    # Merge tag values from an .nvmx file
    ############################################################################
    def mergeNVMX(self, nvmxTagType):
        return self.typeInfo.mergeNVMX(nvmxTagType)


    ############################################################################
    # Save Tag Type to an NVM file
    ############################################################################
    def saveNVM(self, nvm):
        self.typeInfo.saveNVM(nvm)


    ############################################################################
    # Load Tag Type from an XML tree
    ############################################################################
    def loadXML(self, xmlTagType):
        typeName = xmlTagType.get("type", "")
        if typeName == "":
            raise TagError("Malformed XML: <TAG_TYPE> is missing 'type' attribute")

        if typeName not in TagTypeInfo.typeNameMap:
            raise TagError("Malformed XML: <TAG_TYPE> has unknown 'type': %s" % typeName)

        self.type = TagTypeInfo.typeNameMap[typeName]
        self.__constructTypeInfo__()    # Can't fail for XML as we've already validated typeName

        self.typeInfo.loadXML(xmlTagType)

    ############################################################################
    # Load Tag Type from an TCFX tree
    ############################################################################
    def loadTCFX(self, tcfxTagType):
        typeName = tcfxTagType.get("Type", "")
        if not typeName:
            raise TagError("Malformed TCFX: <ELEMENTS> is missing 'type' attribute")

        if typeName not in TagTypeInfo.typeNameMap:
            raise TagError("Malformed TCFX: <ELEMENTS> has unknown 'type': %s" % typeName)

        self.type = TagTypeInfo.typeNameMap[typeName]

        self.__constructTypeInfo__()    # Can't fail for TCFX as we've already validated typeName

        self.typeInfo.loadTCFX(tcfxTagType)

    ############################################################################
    # Save Tag Type to an XML tree
    ############################################################################
    def saveXML(self, tagElem):
        # The attributes of the TAG_TYPE element are populated by the typeInfo classes
        self.typeInfo.saveXML(tagElem)

    ############################################################################
    # Save Tag Type to an TCFX file
    ############################################################################
    def saveTCFX (self, tcfx, isArrayInit=False):
        self.typeInfo.saveTCFX (tcfx)
    
    ############################################################################
    # Save Tag Type to an NVMX file
    ############################################################################
    def saveNVMX (self, nvmx, isArrayInit=False):
        self.typeInfo.saveNVMX (nvmx)
        
    ############################################################################
    # Save Tag Type to the system configuration database
    ############################################################################
    def saveSDB(self, sdb, tag):
        return self.typeInfo.saveSDB(sdb, tag)


    ############################################################################
    # Get the ROM default value for this type, for inserting into the SDB
    ############################################################################
    def getSdbDefault(self, tag):
        return self.typeInfo.getSdbDefault(tag)


    ############################################################################
    # Save struct to an VLIST file
    ############################################################################
    def saveVLIST(self, vlist, tag):
        return self.typeInfo.saveVLIST(vlist, tag)


    ############################################################################
    # Export tag to VT info file
    ############################################################################
    def saveVtag(self, vtag):
        return self.typeInfo.saveVtag(vtag)


    ############################################################################
    # Generate tag data types header information
    ############################################################################
    def genTagDataTypes(self, file, generatedTypes, indent):
        self.typeInfo.genTagDataTypes(file, generatedTypes, indent)


    ############################################################################
    # Generate tag element information
    ############################################################################
    def genTagElement(self, file, indent):
        self.typeInfo.genTagElement(file, indent)


    ############################################################################
    # Generate tag element reference information
    ############################################################################
    def genTagElementRef(self, file, baseDefine, baseElem):
        self.typeInfo.genTagElementRef(file, baseDefine, baseElem)


    ############################################################################
    # Generate tag default values
    ############################################################################
    def genTagDefaultData(self, file, indent):
        self.typeInfo.genTagDefaultData(file, indent)


    ############################################################################
    # Generate tag format information for HTML
    ############################################################################
    def genTagUserFormat(self, file, indent, byteIndex):
        return self.typeInfo.genTagUserFormat(file, indent, byteIndex)


    ############################################################################
    # Get the extended type name as a string, including the parent's name
    ############################################################################
    def getTypeStringRecursive(self):
        return self.typeInfo.getTypeStringRecursive()


    ############################################################################
    # Get the extended C struct name as a string, including parent
    ############################################################################
    def getStructStringRecursive(self):
        return self.typeInfo.getStructStringRecursive()


    ############################################################################
    # Check if one particular element is a table element and return index
    ############################################################################
    def readTableElementIdx(self):
        return self.typeInfo.readTableElementIdx()


################################################################################
# Class describing a generic array Tag Type, used for fixed and struct arrays
################################################################################
class TagTypeArray(TagDescriptor):
    def __init__(self, parent, arrayType):
        TagDescriptor.__init__(self)

        self.name = ""
        self.desc = ""
        self.size = 0
        self.varElemCount = None
        self.elemType = None
        self.elems = []
        self.parent = parent
        self.vListObj = None
        self.wrappingType = arrayType


    ############################################################################
    # Member-level equality check
    ############################################################################
    def __eq__(self, other):
        # Trivial equality test first, are they the same instance?
        if self is other:
            return True

        # Are they the same class?
        if not isinstance(other, TagTypeArray):
            return False

        # Check common elements applicable to all array types
        if self.name != other.name or self.wrappingType != other.wrappingType or len(self.elems) != len(other.elems):
            return False

        # Type-specific checks
        if self.wrappingType == TagTypeInfo.VARIABLE_ARRAY and self.varElemCount.val != other.varElemCount.val:
            return False

        # Array element checks
        if self.wrappingType != TagTypeInfo.FIXED_ARRAY:
            for i in range(len(self.elems)):
                if self.elems[i] != other.elems[i]:
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
        
        self.addHashInfo(d, tag)

        return d
        

    ############################################################################
    # Add tag information to be used for MD5 calculation
    ############################################################################  
    def addHashInfo(self, d, tag):
        if self.wrappingType == TagTypeInfo.VARIABLE_ARRAY:
            arrayMin = self.varElemCount.val
            arrayMax = self.varElemCount.val
        else:
            arrayMin = len(self.elems)
            arrayMax = len(self.elems)

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

        # store top-level tags that are uint8/int8 arrays as octet strings in the database      
        if (self.wrappingType is TagTypeInfo.FIXED_ARRAY and
            self.vListObj and 
            (self.elemType.type.dataType == BasicType.TYPE_UCHAR or
                    self.elemType.type.dataType == BasicType.TYPE_SCHAR)):
            d.addCommonFields(name, tagName, "octet_string", isArray=False)
            d.addRange(arrayMin, arrayMax, isArray=False)
        elif (self.wrappingType is TagTypeInfo.FIXED_ARRAY):
            d.addCommonFields(name, tagName, self.elemType.type.getTypeString(), isArray=True)
            d.addRange(arrayMin, arrayMax, isArray=True) 
        else:
            d.addCommonFields(name, tagName, self.elemType.getTypeString(), isArray=True)
            d.addRange(arrayMin, arrayMax, isArray=True)

        d.addDescription(desc)
        # If this a top-level tag element, then add tag generic data as well
        if self.isVtagPublished:
            # VTag has been found in filter list. Read info 
            d.addTagData(self.getVtagNumber(), False)


    ############################################################################
    # Get the maximum size of the tag, in bytes
    ############################################################################
    def getMaxLength(self):
        # If the tag is dynamically allocated, then a variable length array
        # doesn't include the array elements, just the element count field.
        if not self.getTag().dynMem or self.wrappingType != TagTypeInfo.VARIABLE_ARRAY:
            length = len(self.elems) * self.elemType.getMaxLength()
        else:
            length = 0

        if self.wrappingType == TagTypeInfo.VARIABLE_ARRAY:
            length += self.varElemCount.getMaxLength()

        return length


    ############################################################################
    # Get the type alignment requirement, in bytes
    ############################################################################
    def getAlignment(self):
        # Array alignment is the same as the underlying type.
        return self.elemType.getAlignment()


    ############################################################################
    # Determine if the tag type contains a variable-length array
    ############################################################################
    def hasVarArray(self):
        if self.wrappingType == TagTypeInfo.VARIABLE_ARRAY:
            return True
        elif self.wrappingType == TagTypeInfo.FIXED_ARRAY:
            return False
        else:
            # Descend into struct array
            return self.elemType.hasVarArray()


    ############################################################################
    # Load array definition from the RAM copy of the TCF file
    ############################################################################
    def loadTCF(self, tcf, sectionName):
        sectionName += "%d" % self.wrappingType
        self.name = tcf.get(sectionName, "Name")
        self.size = int(tcf.get(sectionName, "TagLength"))
        numElems = int(tcf.get(sectionName, "ElementCount"))

        sectionName += "_Data"

        # Load the generic element descriptor
        if self.wrappingType == TagTypeInfo.FIXED_ARRAY:
            if numElems != int(tcf.get(sectionName, "Num")):
                # Seems to be duplicate information in the file format
                raise TagError("%s -- ElementCount (%d) doesn't match Num" % (self.name, numElems))
            self.elemType = TagTypeInt(parent=None)
            self.elemType.loadTCF(tcf, sectionName)
        else:
            # Variable length struct arrays have an additional Element Count data item, stored as TagTypeInt
            if self.wrappingType == TagTypeInfo.VARIABLE_ARRAY:
                self.varElemCount = TagTypeInt(parent=None)
                self.varElemCount.loadTCF(tcf, sectionName)
                self.varElemCount.val = numElems

                # Non-zero default length is unexpected for VAR_ARRAY, as there are no ROM defaults for any current tag
                if self.varElemCount.default != 0:
                    print("WARNING! Non-zero default length %d for VAR_ARRAY '%s', forcing to 0" % (self.varElemCount.default, self.name))
                    self.varElemCount.default = 0

            # Var and Struct arrays are followed by a structure type definition
            self.elemType = TagTypeStruct(parent=self)
            self.elemType.loadTCF(tcf, sectionName)

        # Now load the individual element definitions.
        for i in range(numElems):
            if self.wrappingType == TagTypeInfo.FIXED_ARRAY:
                field = TagTypeInt(parent=None)
            else:
                field = TagTypeStruct(parent=self)

            if self.wrappingType == TagTypeInfo.VARIABLE_ARRAY:
                # Just copy from the defaults in the structure definition
                field.fields = self.elemType.fields
                field.name = "%s_%d" % (self.elemType.name, i)
            else:
                field.loadTCF(tcf, sectionName+"_%d" % i)

            self.elems.append(field)


    ############################################################################
    # Save array to a TCF file
    ############################################################################
    def saveTCF(self, tcf, sectionName):
        sectionName += "%d" % self.wrappingType
        tcf.write("[%s]\n" % sectionName)
        tcf.write("Name = %s\n" % self.name)
        tcf.write("TagLength = %d\n" % self.size)
        tcf.write("\n")
        if self.wrappingType == TagTypeInfo.FIXED_ARRAY:
            tcf.write("EnableAsciiEdit = %d\n" % 0)     # Dummy field, not used by any config files today
            tcf.write("\n")
        if self.wrappingType == TagTypeInfo.VARIABLE_ARRAY:
            tcf.write("ElementCount = %d\n" % self.varElemCount.val)
        else:
            tcf.write("ElementCount = %d\n" % len(self.elems))
        tcf.write("\n")

        sectionName += "_Data"
        if self.wrappingType != TagTypeInfo.VARIABLE_ARRAY:
            tcf.write("[%s]\n" % sectionName)

        if self.wrappingType == TagTypeInfo.FIXED_ARRAY:
            tcf.write("Num = %d\n" % len(self.elems))
            tcf.write("\n")
        elif self.wrappingType == TagTypeInfo.VARIABLE_ARRAY:
            self.varElemCount.saveTCF(tcf, sectionName)

        # Save the generic element descriptor
        self.elemType.saveTCF(tcf, sectionName)

        # Now save the individual element definitions
        if self.wrappingType != TagTypeInfo.VARIABLE_ARRAY:
            i = 0
            for elem in self.elems:
                elem.saveTCF(tcf, "%s_%d" % (sectionName, i))
                i += 1


    ############################################################################
    # Save array to an HTF file
    ############################################################################
    def saveHTF(self, htf, indent, elemSuffix=""):
        if self.wrappingType == TagTypeInfo.VARIABLE_ARRAY:
            raise TagError("Unimplemented HTF output for variable length arrays")

        # Get associated vtag name for sub-element in a physical tag
        if self.parent is None or self.getTag().isVtag or self.vListObj is None:
            vtagName = ""
        else:
            vtagName = "\t[V] %s" % self.vListObj.tagName

        # Top-level integer arrays are encoded as octet-string type in the
        # database, so we need to use square brackets rather than curly
        if (self.vListObj and
            self.wrappingType == TagTypeInfo.FIXED_ARRAY and
            (self.elemType.type.dataType == BasicType.TYPE_UCHAR or self.elemType.type.dataType == BasicType.TYPE_SCHAR)):
            openBracket  = "["
            closeBracket = "]"
            octetString = True
        else:
            openBracket  = "{"
            closeBracket = "}"
            octetString = False

        # Write the array elements for FIXED_ARRAY and STRUCT_ARRAY always.
        arrayStr = openBracket + " "
        if octetString:
            htf.write(arrayStr)
        else:
            if not config.options.compactHTF:
                arrayStr += "  /* %s[ %d ]%s */" % (SdbDescriptor.makeShortName(self.name), len(self.elems), vtagName)
            HtfWriteLine(htf, arrayStr, indent)

        for elem in self.elems:
            if octetString:
                elem.saveHTF(htf, indent+4, elemSuffix=" ", octetString=octetString)
            else:
                if self.elems.index(elem) != len(self.elems)-1:
                    es = ","
                else:
                    es = ""
                elem.saveHTF(htf, indent+4, elemSuffix=es)

        # Line continuation is not required if current indent is 0, as this means
        # we are the top-level element of the tag
        if config.options.compactHTF and not octetString:
            htf.write(" ")  # extra space before closing brace in one-line mode
        HtfWriteLine(htf, closeBracket+elemSuffix, indent, cont=(indent>0))


    ############################################################################
    # Merge tag values from an .nvm file
    ############################################################################
    def mergeNVM(self, tagVal):
        
        if self.wrappingType == TagTypeInfo.VARIABLE_ARRAY:
            # The first elements before Variable Array till the size of Variable
            # Tells us how many structure elements are going to be defined in
            # the NVM tag, so using that constraint, we will merge the array
            # if the variablesize is 2 bytes, then 2 bytes are to be read

            tagVal = self.varElemCount.mergeNVM (tagVal)

            variable_array_length = self.varElemCount.default

                        
            for index,elem in enumerate(self.elems):
                if index >= variable_array_length:
                    break
                tagVal = elem.mergeNVM(tagVal)

            #Need to trim the elements of variable array based on size
            self.elems = self.elems[:variable_array_length]
        else:
            for elem in self.elems:
                tagVal = elem.mergeNVM(tagVal)

        return tagVal


    ############################################################################
    # Merge tag values from an .nvmx file
    ############################################################################
    def mergeNVMX(self, nvmxTagType):
        if nvmxTagType.get("Name") != self.name and not config.options.alignToTCFX:
            raise TagError("NVMX Tag is not aligned with the Elements.")
            
        nvmxArrayElems = nvmxTagType.findall("ELEMENTS")
        
        # Now load the individual element definitions.
        if self.wrappingType == TagTypeInfo.VARIABLE_ARRAY:
            #Limiting the number of variable Array to the number of elements
            #present in NVMX file
            self.elems = self.elems[:len(nvmxArrayElems)]
        
            
        for nvmxArrayElem, elem in zip (nvmxArrayElems, self.elems):
            if nvmxArrayElem.get("Name") != elem.name and self.wrappingType != TagTypeInfo.VARIABLE_ARRAY:
                raise TagError("NVMX Tag %s is not aligned with the Elements."%(nvmxArrayElem.get("Name")))
                
            elem.mergeNVMX(nvmxArrayElem)
            

        
    ############################################################################
    # Save array to an NVM file
    ############################################################################
    def saveNVM(self, nvm):
        if self.wrappingType == TagTypeInfo.VARIABLE_ARRAY:
            self.varElemCount.saveNVM(nvm)

            if self.getTag().dynMem:
                # For now just write a zero-length variable array structure, on the
                # basis that no current tag using VAR_ARRAY has any ROM defaults.
                return

            elif self.varElemCount.default != 0:
                raise TagError("saveNVM VAR_ARRAY not yet implemented for non-zero length default")

        # Write the array elements for FIXED_ARRAY and STRUCT_ARRAY always.
        # For VAR_ARRAY we'll only do this if the tag isn't flagged as dynamic memory
        for elem in self.elems:
            elem.saveNVM(nvm)


    ############################################################################
    # Load Tag Type from an XML tree
    ############################################################################
    def loadXML(self, xmlTagType):
        self.name = xmlTagType.get("name")
        self.size = int(xmlTagType.get("length"))
        numElems = int(xmlTagType.get("numElems"))

        # Load the generic element descriptor
        if self.wrappingType == TagTypeInfo.FIXED_ARRAY:
            xmlArrayType = xmlTagType.find("TAG_TYPE")
            if xmlArrayType is None:
                raise TagError("Malformed XML: FIXED_ARRAY doesn't have <TAG_TYPE> element")
            if xmlArrayType.get("type", "") != "VALUE":
                raise TagError("Malformed XML: FIXED_ARRAY <TAG_TYPE> isn't of type 'VALUE'")

            self.elemType = TagTypeInt(parent=None)
            self.elemType.loadXML(xmlArrayType)
        else:
            # Structure arrays have one <TAG_TYPE> describing the structure.
            # Variable length struct arrays have an additional Element Count
            # data item first to store the current array length
            xmlArrayType = xmlTagType.findall("TAG_TYPE")

            # For VAR_ARRAY load the element count field
            if self.wrappingType == TagTypeInfo.VARIABLE_ARRAY:
                xmlVarCount = xmlArrayType.pop(0)
                if xmlVarCount is None:
                    raise TagError("Malformed XML: VAR_ARRAY doesn't have <TAG_TYPE> element for Element Count")
                if xmlVarCount.get("type", "") != "VALUE":
                    raise TagError("Malformed XML: VAR_ARRAY has invalid type of <TAG_TYPE> for Element Count (not VALUE)")

                self.varElemCount = TagTypeInt(parent=None)
                self.varElemCount.loadXML(xmlVarCount)
                self.varElemCount.val = numElems

                # Non-zero default length is unexpected for VAR_ARRAY, as there are no ROM defaults for any current tag
                if self.varElemCount.default != 0:
                    print("WARNING! Non-zero default length %d for VAR_ARRAY '%s', forcing to 0" % (self.varElemCount.default, self.name))
                    self.varElemCount.default = 0

            xmlStructType = xmlArrayType.pop(0)
            if xmlStructType is None:
                raise TagError("Malformed XML: ARRAY doesn't have <TAG_TYPE> element for structure definition")
            if xmlStructType.get("type", "") != "STRUCT":
                raise TagError("Malformed XML: ARRAY has invalid type of <TAG_TYPE> for structure definition (not STRUCT)")

            # By this point there should be no more TAG_TYPE elements in the array
            if len(xmlArrayType) > 0:
                raise TagError("Malformed XML: Too many <TAG_TYPE> elements in array type")

            # Load the generic type information.
            self.elemType = TagTypeStruct(parent=self)
            self.elemType.loadXML(xmlStructType)

        # Now load the individual element definitions.
        if self.wrappingType == TagTypeInfo.VARIABLE_ARRAY:
            # Special case, there is no array information in the XML file so copy from the defaults
            for i in range(numElems):
                field = TagTypeStruct(parent=self)
                field.fields = self.elemType.fields
                field.name = "%s_%d" % (self.elemType.name, i)
                self.elems.append(field)
        else:
            xmlArrayElems = xmlTagType.findall("ARRAY")
            for xmlArrayElem in xmlArrayElems:
                if self.wrappingType == TagTypeInfo.FIXED_ARRAY:
                    field = TagTypeInt(parent=None)
                else:
                    field = TagTypeStruct(parent=self)

                field.loadXML(xmlArrayElem)

                self.elems.append(field)

    ############################################################################
    # Load Tag Type from an TCFX tree
    ############################################################################
    def loadTCFX(self, tcfxTagType):
        self.name = tcfxTagType.get("Name")
        
        if self.wrappingType != TagTypeInfo.VARIABLE_ARRAY:
            self.size = int(tcfxTagType.get("Size"))

        # Load the generic element descriptor
        if self.wrappingType == TagTypeInfo.FIXED_ARRAY:
            self.elemType = TagTypeInt(parent=None)
            self.elemType.loadTCFX(tcfxTagType=tcfxTagType, isArrayElem=False, isElementType=True)
            
        else:
            # Structure arrays have one <TAG_TYPE> describing the structure.
            # Variable length struct arrays have an additional Element Count
            # data item first to store the current array length
            tcfxStructType = tcfxTagType.find("ELEMENTS")
            
            # For VAR_ARRAY load the element count field
            if self.wrappingType == TagTypeInfo.VARIABLE_ARRAY:
                self.varElemCount = TagTypeInt(parent=None)
                self.varElemCount.loadTCFX(tcfxTagType=tcfxTagType, isArrayElem=False, isElementType=False, isVariableElementType=True)
                self.varElemCount.val = self.varElemCount.max
                
                self.size = self.varElemCount.default
                
            # Load the generic type information.
            self.elemType = TagTypeStruct(parent=self)
            self.elemType.loadTCFX(tcfxStructType)
            
            if self.wrappingType != TagTypeInfo.VARIABLE_ARRAY:
                self.elemType.name = tcfxTagType.get("VariableName")
            
        # Now load the individual element definitions.
        if self.wrappingType == TagTypeInfo.VARIABLE_ARRAY:
            # Special case, there is no array information in the TCFX file so copy from the defaults
            numElems = int(tcfxTagType.get("Max"))
            
            tcfxArrayElems = tcfxTagType.findall("ELEMENTS")
            
            for i in range(numElems):
                field = TagTypeStruct(parent=self)
                #field.fields = self.elemType.fields 
				#Replacing above line of code 
                #Because Upon 'equals to' Python adds new reference to the same address (shallow copy), 
                #which should not be the case for MergeNVM / MergeNVMX of Variable Array
                #Probably this needs to be done in other File formats as well for TCF / XML
                field.loadTCFX(tcfxStructType)
                field.name = "%s_%d" % (self.elemType.name, i)
                self.elems.append(field)

        else:
            tcfxArrayElems = tcfxTagType.findall("ELEMENTS")

            for tcfxArrayElem in tcfxArrayElems:
                if self.wrappingType == TagTypeInfo.FIXED_ARRAY:
                    field               = TagTypeInt(parent=None)
                    field.type.size     = self.elemType.type.size
                    field.type.signed   = self.elemType.type.signed
                    field.min           = self.elemType.min
                    field.max           = self.elemType.max
                    field.loadTCFX(tcfxTagType=tcfxArrayElem, isArrayElem=True)
                    
                else:
                    field = TagTypeStruct(parent=self)
                    field.loadTCFX(tcfxArrayElem)

                self.elems.append(field)

    ############################################################################
    # Save Tag Type to an XML tree
    ############################################################################
    def saveXML(self, tagElem):
        typeElem = ET.SubElement(tagElem, "TAG_TYPE")
        if self.wrappingType == TagTypeInfo.FIXED_ARRAY:
            typeElem.set("type", "FIXED_ARRAY")
        elif self.wrappingType == TagTypeInfo.STRUCT_ARRAY:
            typeElem.set("type", "STRUCT_ARRAY")
        else:
            typeElem.set("type", "VAR_ARRAY")

        typeElem.set("name", self.name)
        typeElem.set("length", str(self.size))
        typeElem.set("numElems", str(len(self.elems)))

        # For VAR_ARRAY save the element count field
        if self.wrappingType == TagTypeInfo.VARIABLE_ARRAY:
            self.varElemCount.saveXML(typeElem)

        # Save the generic type information.
        self.elemType.saveXML(typeElem)

        # Save the default values unless its a variable array (which has no defaults)
        if self.wrappingType != TagTypeInfo.VARIABLE_ARRAY:
            for elem in self.elems:
                elem.saveXML(typeElem, isArrayElem=True)

    ############################################################################
    # Save Tag Type to an TCFX tree
    ############################################################################
    def saveTCFX (self, tagElem, isArrayInit=False):
        typeElem = ET.SubElement(tagElem, "ELEMENTS")
        typeElem.set("Name", self.name)
        
        if self.wrappingType == TagTypeInfo.FIXED_ARRAY:
            typeElem.set("Type", "FIXED_ARRAY")
        elif self.wrappingType == TagTypeInfo.STRUCT_ARRAY:
            typeElem.set("Type", "STRUCT_ARRAY")
        else:
            typeElem.set("Type", "VARIABLE_ARRAY")

        if self.wrappingType == TagTypeInfo.STRUCT_ARRAY:
            typeElem.set("Size", str(self.size))    

        # For VAR_ARRAY save the additional attributes
        if self.wrappingType == TagTypeInfo.VARIABLE_ARRAY: 
            typeElem.set("Size", str(self.varElemCount.max * self.elemType.size + self.varElemCount.type.size))
            typeElem.set("Max", str(self.varElemCount.max))
            typeElem.set("Default", config.ToHex(self.varElemCount.default, self.varElemCount.type.size))
            typeElem.set("Description", str(self.varElemCount.desc))
            typeElem.set("VariableName", str(self.varElemCount.name))
            typeElem.set("VariableSize", str(self.varElemCount.type.size))
        
        # Save the generic type information. Needs to be upgraded to TAG itself as attributes
        if self.wrappingType == TagTypeInfo.FIXED_ARRAY:
            typeElem.set("ElementSize", str(self.elemType.type.size))
            typeElem.set("Size", str(self.size))
            typeElem.set("Min", config.ToHex(self.elemType.min , self.elemType.type.size))
            typeElem.set("Max", config.ToHex(self.elemType.max , self.elemType.type.size))
            typeElem.set("Signed", str(bool(self.elemType.type.signed)).lower())
            typeElem.set("Description", str(self.elemType.desc))
            typeElem.set("VariableName", self.elemType.name)
        elif self.wrappingType == TagTypeInfo.VARIABLE_ARRAY:
            self.elemType.saveTCFX(typeElem)
        else:
            typeElem.set("VariableName", self.elemType.name)
            
        # Save the default values unless its a variable array (which has no defaults)
        if self.wrappingType != TagTypeInfo.VARIABLE_ARRAY:
            for elem in self.elems:
                if self.wrappingType == TagTypeInfo.FIXED_ARRAY:
                    elem.saveTCFX (typeElem=typeElem, isFixedArrayElem=True)
                else:
                    elem.saveTCFX (typeElem)
    
    ############################################################################
    # Save array to an NVM file
    ############################################################################
    def saveNVM(self, nvm):
        if self.wrappingType == TagTypeInfo.VARIABLE_ARRAY:
            self.varElemCount.saveNVM(nvm)

            if self.getTag().dynMem:
                # For now just write a zero-length variable array structure, on the
                # basis that no current tag using VAR_ARRAY has any ROM defaults.
                return

            elif self.varElemCount.default != 0:
                raise TagError("saveNVM VAR_ARRAY not yet implemented for non-zero length default")

        # Write the array elements for FIXED_ARRAY and STRUCT_ARRAY always.
        # For VAR_ARRAY we'll only do this if the tag isn't flagged as dynamic memory
        for elem in self.elems:
            elem.saveNVM(nvm)
            
    ############################################################################
    # Save Tag Type to an NVMX tree
    ############################################################################
    def saveNVMX (self, tagElem, isArrayInit=False):
        
        typeElem = ET.SubElement(tagElem, "ELEMENTS")
        
        typeElem.set("Name", self.name)
 
        #typeElem.set("Size", str(self.size))

        # Write the array elements for FIXED_ARRAY and STRUCT_ARRAY always.
        # For VAR_ARRAY we'll only do this if the tag isn't flagged as dynamic memory        
        for elem in self.elems:
            elem.saveNVMX (typeElem)
                    
    ############################################################################
    # Save Tag Type to the system configuration database
    ############################################################################
    def saveSDB(self, sdb, tag):
        structUid = None

        if self.wrappingType == TagTypeInfo.FIXED_ARRAY:
            # Get the type descriptor then save to the database (or retrieve UID if already present)
            d = self.getSdbDescriptor(tag)
            elemUid = d.saveSDB(sdb)

            # Cross-reference the config_element for this type to the FW release
            sdb.xrefElement(elemUid)

        elif self.wrappingType == TagTypeInfo.STRUCT_ARRAY and tag is not None:
            # This is a top-level struct array. So just let TagTypeStruct do all
            # the work by forwarding the tag details to it. Note that ConfigCmd
            # *does* handle array-of-struct correctly if it is the overall tag type.

            # Propagate the struct array vtag info to the struct object
            structVList = self.elemType.vListObj
            if self.vListObj is not None:
                if structVList is not None:
                    raise TagError("Nested VTAG in STRUCT_ARRAY")
                self.elemType.vListObj = self.vListObj
                self.elemType.isVtagPublished = self.isVtagPublished

            elemUid, structUid = self.elemType.saveSDB(sdb, tag)

            # Restore struct vtag info
            self.elemType.vListObj = structVList

            # TBD: why do we need to export the elements if top-level tag is flagged as struct array in SDB?
            if self.vListObj is None:
                for elem in self.elems:
                    subelemUid, substructUid = elem.saveSDB(sdb, tag)
                    sdb.xrefElement(subelemUid, substructUid, TagTypeInfo.STRUCTURE)

        else:
            # This is a nested struct array or a variable struct array so we
            # handle it slightly differently.
            #
            # First save the nested struct definition and pass down the handle
            # to this type to allow TagTypeStruct.saveSDB() to fill the array
            # information correctly.
            origStructName = self.elemType.name
            if self.wrappingType == TagTypeInfo.VARIABLE_ARRAY:
                self.elemType.name += " Elem"
            elemUid, structUid = self.elemType.saveSDB(sdb, self)
            self.elemType.name = origStructName

            # Cross-reference the nested struct config_element to the FW release
            sdb.xrefElement(elemUid, structUid, TagTypeInfo.STRUCTURE)

            # ConfigCmd doesn't handle nested arrays-of-structs, so we fake it up by emitting a pseudo-struct that
            # unrolls the array elements. For example, the following C-style struct-array definition:
            #
            #    struct FOO x[10];
            #
            # becomes:
            #
            #    struct FOO_ARRAY
            #    {
            #        struct FOO x0;
            #        struct FOO x1;
            #        ...
            #        struct FOO x9;
            #    };
            #    struct FOO_ARRAY x;
            #
            if self.wrappingType == TagTypeInfo.STRUCT_ARRAY:
                pseudoStruct = TagTypeStruct(parent=self)
                pseudoStruct.name = self.elemType.name + " Array"
                pseudoStruct.size = self.size
                for elem in self.elems:
                    pseudoStruct.fields.append(elem)
                elemUid, structUid = pseudoStruct.saveSDB(sdb, tag)

                # Cross-reference the config_element for the nested struct type to the FW release
                sdb.xrefElement(elemUid, structUid, TagTypeInfo.STRUCTURE)

            # For var struct array we also need to save a pseudo-struct definition
            # that encapsulates the var elem count parameter followed by the
            # nested struct array. We build a temporary struct def here to hold
            # the details. Note that TagTypeStruct.saveSDB() will not process
            # the nested struct again to avoid recursion problems propagating
            # the array type.
            #
            # If this is a top-level structure then tag is not None so the tag
            # details will be saved as well.
            if self.wrappingType == TagTypeInfo.VARIABLE_ARRAY:
                pseudoStruct = TagTypeStruct(parent=self, varElemId=elemUid)
                pseudoStruct.name = self.name
                pseudoStruct.size = self.size
                pseudoStruct.fields.append(self.varElemCount)
                pseudoStruct.fields.append(self.elemType)
                elemUid, structUid = pseudoStruct.saveSDB(sdb, tag)

                # Cross-reference the config_element for the nested struct type to the FW release
                sdb.xrefElement(elemUid, structUid, TagTypeInfo.STRUCTURE)
            
        return elemUid, structUid


    ############################################################################
    # Get the ROM default value for this type, for inserting into the SDB
    ############################################################################
    def getSdbDefault(self, tag):
        # Array defaults are the concatenation of the defaults of each array
        # element (irrespective of whether thats an integer or a struct).
        # Note that variable-length tags are not typically going to have
        # sensible default as they don't exist in ROM, so we don't write the
        # defaults.
        #
        default = []
        if self.wrappingType != TagTypeInfo.VARIABLE_ARRAY:
            for elem in self.elems:
                default.extend(elem.getSdbDefault(None))

        return default


    ############################################################################
    # Save struct to an VLIST file
    ############################################################################
    def saveVLIST(self, vlist, tag):
        # Check array type
        if self.wrappingType == TagTypeInfo.FIXED_ARRAY:
            expname = self.getTypeStringRecursive()
            # Check the filtered list
            if vlist.filter.vtagEnabled(expname):
                # Make sure this is published in case it is not in the known VTag list
                self.isVtagPublished = True
                self.addHashInfo(self, tag)
                md5 = self.getHash(shortHash=True)
                if not tag_descriptor.vListInfo.isTagDefined(expname, md5): 
                    vlist.SaveTagInfo(expname, md5, int(self.values[self.names.index("psid")]), self.getTagName())
                if config.options.debug:
                    print("saveVLIST tagtype_array " + expname)
        elif self.wrappingType == TagTypeInfo.STRUCT_ARRAY and tag is not None:
            # This is a top-level struct array. So just let TagTypeStruct do all
            # the work by forwarding the tag details to it. Save all the elements
            for elem in self.elems:
                elem.saveVLIST(vlist, tag)
        else:
            
            if self.wrappingType == TagTypeInfo.VARIABLE_ARRAY:
                name = self.name
                for i in range(0, self.varElemCount.max):
                    pseudoStruct = TagTypeStruct(parent=self)
                    self.elemType.name = name + " " + str(i)
                    pseudoStruct.name = name + " " + str(i)
                    pseudoStruct.size = self.size
                    pseudoStruct.fields.append(self.elemType)
                    pseudoStruct.saveVLIST(vlist, tag, False)
            
            elif self.wrappingType == TagTypeInfo.STRUCT_ARRAY:
                pseudoStruct = TagTypeStruct(parent=self.parent)
                pseudoStruct.name = self.name
                pseudoStruct.size = self.size
                pseudoStruct.elemType = self.elemType
                for elem in self.elems:
                    pseudoStruct.fields.append(elem)
                pseudoStruct.saveVLIST(vlist, self)
            
            else:
                # This is a nested struct array or a variable struct array so we
                # handle it slightly differently.
                #
                # First save the nested struct definition and pass down the handle
                # to this type to allow TagTypeStruct.saveSDB() to fill the array
                # information correctly.
                origStructName = self.elemType.name
                
                self.elemType.saveVLIST(vlist, self)


    ############################################################################
    # Export tag to VT info file
    ############################################################################
    def saveVtag(self, vtag):
        from tags import Tag
        # Check array type
        if self.wrappingType == TagTypeInfo.FIXED_ARRAY:
            extentedName = self.getTypeStringRecursive()
            vlistObj = tag_descriptor.vListInfo.findTagByName(extentedName) 
            if vlistObj and (config.options.buildType == 'ROM' or vlistObj.tagId > config.options.patchBaseId):
                
                vtag.writeOutFile(vlistObj.tagId, self.getStructStringRecursive(), self.elemType.type.getTypeString(), vlistObj.physicalTag.isPatched)

                if config.options.debug:
                    print("saveVtag tagtype_array " + extentedName)
        elif self.wrappingType == TagTypeInfo.STRUCT_ARRAY and isinstance(self.parent, Tag):
            # This is a top-level struct array. So just let TagTypeStruct do all
            # the work by forwarding the tag details to it. Save all the elements
            for elem in self.elems:
                elem.saveVtag(vtag)
        else:
            
            if self.wrappingType == TagTypeInfo.VARIABLE_ARRAY:
                name = self.name
                for i in range(0, self.varElemCount.max):
                    pseudoStruct = TagTypeStruct(parent=self)
                    self.elemType.name = name + " " + str(i)
                    pseudoStruct.name = name + " " + str(i)
                    pseudoStruct.size = self.size
                    pseudoStruct.fields.append(self.elemType)
                    pseudoStruct.saveVtag(vtag)
            
            elif self.wrappingType == TagTypeInfo.STRUCT_ARRAY:
                pseudoStruct = TagTypeStruct(parent=self.parent)
                pseudoStruct.name = self.name
                pseudoStruct.size = self.size
                pseudoStruct.elemType = self.elemType
                for elem in self.elems:
                    pseudoStruct.fields.append(elem)
                pseudoStruct.saveVtag(vtag)
            
            else:
                # This is a nested struct array or a variable struct array so we
                # handle it slightly differently.
                #
                # First save the nested struct definition and pass down the handle
                # to this type to allow TagTypeStruct.saveSDB() to fill the array
                # information correctly.
                origStructName = self.elemType.name
                
                self.elemType.saveVtag(vtag, self)


    ############################################################################
    # Generate tag data types header information
    ############################################################################
    def genTagDataTypes(self, file, generatedTypes, indent):
        if self.wrappingType == TagTypeInfo.FIXED_ARRAY:
            typeStr = self.elemType.type.getTypeString()
            typeName = CodeGen.makeUpperIdent("CFG_" + self.name + "_ARRAY_TYPE")
            if not CodeGen.checkUnique(generatedTypes, typeName, self):
                return
            maxCountStr = CodeGen.makeUpperIdent("CFG_" + self.name + "_MAX_ENTRIES")
            file.write("\n#define   %s    (%d)\n" % (maxCountStr, len(self.elems)))
            file.write("\n/*  %s  */\n" % self.desc)
            file.write("typedef %s%s[%s];\n" % (typeStr.ljust(10), typeName, maxCountStr))

        elif self.wrappingType == TagTypeInfo.STRUCT_ARRAY:
            typeName = CodeGen.makeUpperIdent("CFG_" + self.name + "_MAX_ENTRIES")
            if not CodeGen.checkUnique(generatedTypes, typeName, self):
                return
            file.write("\n#define   %s    (%d)\n" % (typeName, len(self.elems)))
            self.elemType.genTagDataTypes(file, generatedTypes, indent)

        else:
            self.elemType.genTagDataTypes(file, generatedTypes, indent)
            typeName = CodeGen.makeUpperIdent("CFG_STRUCT_" + self.name + "_TYPE")
            if not CodeGen.checkUnique(generatedTypes, typeName, self):
                return

            if indent == 0:
                file.write("\n")

            maxCountStr = CodeGen.makeUpperIdent("CFG_" + self.name + "_MAX_ENTRIES")
            file.write("\n#define   %s    (%d)\n" % (maxCountStr, self.varElemCount.val))
            if config.options.compat: file.write("    ")    # some spaces chars on a blank line, for no obvious reason
            file.write("\ntypedef struct \n{\n")
            self.varElemCount.genTagElement(file, 4)
            file.write("\n")

            subTypeName = CodeGen.makeUpperIdent("CFG_STRUCT_" + self.elemType.name + "_TYPE")
            if config.options.compat: indent += 1   # C++ PadString pads one extra character
            file.write("%s%s%s[%s];\n" % (" "*indent, CodeGen.padIdentMid(subTypeName), CodeGen.makeIdent("Cfg_" + self.elemType.name), maxCountStr))
            file.write("} %s;\n" % typeName)


    ############################################################################
    # Generate tag element information
    ############################################################################
    def genTagElement(self, file, indent):
        if self.wrappingType == TagTypeInfo.FIXED_ARRAY:
            typeName = CodeGen.makeUpperIdent("CFG_" + self.name + "_ARRAY_TYPE")
            file.write(" "*indent + CodeGen.padIdentMid(typeName) + CodeGen.makeIdent("Cfg_" + self.name) + ";")

        elif self.wrappingType == TagTypeInfo.STRUCT_ARRAY:
            typeName = CodeGen.makeUpperIdent("CFG_STRUCT_" + self.elemType.name + "_TYPE")
            file.write(" "*indent + CodeGen.padIdentMid(typeName) + CodeGen.makeIdent("Cfg_" + self.name) + "[%d];" % len(self.elems))

        else:
            typeName = CodeGen.makeUpperIdent("CFG_STRUCT_" + self.name + "_TYPE")
            file.write(" "*indent + CodeGen.padIdentMid(typeName) + CodeGen.makeIdent("Cfg_" + self.name) + ";")


    ############################################################################
    # Generate tag element reference information
    ############################################################################
    def genTagElementRef(self, file, baseDefine, baseElem):
        arrayIndex = ""
        if self.wrappingType == TagTypeInfo.FIXED_ARRAY or self.wrappingType == TagTypeInfo.STRUCT_ARRAY:
            arrayIndex = "[0]"

        elemName = baseElem+CodeGen.makeIdent("Cfg_"+self.name)
        file.write("#define  %s" % CodeGen.padTo(CodeGen.makeUpperIdent("%s_%s_PTR" % (baseDefine, self.name)), 40))
        file.write(" ((UINT8 *) &(%s%s))\n" % (elemName, arrayIndex))

        file.write("#define  %s" % CodeGen.padTo(CodeGen.makeUpperIdent("%s_%s" % (baseDefine, self.name)), 40))
        file.write(" (%s)\n" % elemName)


    ############################################################################
    # Generate tag default values
    ############################################################################
    def genTagDefaultData(self, file, indent):
        if self.wrappingType == TagTypeInfo.FIXED_ARRAY or self.wrappingType == TagTypeInfo.STRUCT_ARRAY:
            file.write(" "*indent + "{ ")

            isFirst = True
            for elem in self.elems:
                if isFirst:
                    isFirst = False
                else:
                    file.write(",")

                if self.wrappingType == TagTypeInfo.FIXED_ARRAY:
                    # Deliberately set indent to 0 for integer array elements as they are presented on one line
                    elemIndent = 0
                else:
                    file.write("\n")
                    elemIndent = indent+4

                elem.genTagDefaultData(file, elemIndent)

            if self.wrappingType == TagTypeInfo.FIXED_ARRAY:
                file.write(" }")
            else:
                file.write("\n" + " "*indent + "}")

        else:
            file.write(" "*indent + "{\n")
            indent += 4

            self.varElemCount.genTagDefaultData(file, indent)
            file.write(",\n")
            file.write(" "*indent + "{\n")

            isFirst = True
            for elem in self.elems:
                if isFirst:
                    isFirst = False
                else:
                    file.write(",\n")
                elem.genTagDefaultData(file, indent+4)
            file.write("\n")
            file.write(" "*indent + "}\n")

            indent -= 4
            file.write(" "*indent + "}")


    ############################################################################
    # Generate tag format information for HTML
    ############################################################################
    def genTagUserFormat(self, file, indent, byteIndex):
        if self.wrappingType == TagTypeInfo.FIXED_ARRAY or self.wrappingType == TagTypeInfo.STRUCT_ARRAY:
            file.write(" "*indent + "<b>Bytes %u-%u:</b>  A %u element array of %u byte elements\n" %
                       (byteIndex, byteIndex+self.getMaxLength()-1, len(self.elems), self.elemType.getMaxLength()) )

            file.write("<br>\n")

            if self.wrappingType == TagTypeInfo.STRUCT_ARRAY:
                file.write(" "*indent + "<b>Element Format: </b>\n")
                file.write("<br>\n")
                self.elemType.genTagUserFormat(file, indent, 0)

                file.write(" "*indent + "<b>Default    :</b>\n")
                self.genTagDefaultData(file, indent)
            else:
                file.write(" "*indent + "<b>Default :</b>")
                self.genTagDefaultData(file, 0)

            file.write("<br>\n")

        else:
            file.write(" "*indent + "<b>Bytes %u-%u:</b>  A Variable array of maximum %u elements with %u byte elements\n" %
                       (byteIndex, byteIndex+self.getMaxLength()-1, len(self.elems), self.elemType.getMaxLength()) )
            file.write("<ul>\n")

            file.write(" "*indent + "<b>" + self.varElemCount.type.getByteRangeStr(byteIndex))
            if config.options.compat and self.varElemCount.type.size==1:
                file.write(" ")
            file.write(": </b> %s : Maximum Count: 0x%X, (%dd)\n" % (self.varElemCount.name, len(self.elems), len(self.elems)))
            file.write("<br>\n")

            file.write("<b>Element Format: </b>\n")
            file.write("<ul>\n")
            self.elemType.genTagUserFormat(file, indent, 0)
            file.write("</ul>\n")
            file.write("</ul>\n")

        byteIndex += self.getMaxLength()
        return byteIndex
