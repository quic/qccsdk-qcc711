################################################################################
# Struct tag type processing
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
from config import TagTypeInfo, TagError
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
# Class describing a struct Tag Type
################################################################################
class TagTypeStruct(TagDescriptor):
    def __init__(self, parent, varElemId=None):
        TagDescriptor.__init__(self)
        
        self.name = ""
        self.size = 0
        self.fields = []
        self.parent = parent
        self.varElemId = varElemId
        self.vListObj = None
        self.wrappingType = TagTypeInfo.STRUCTURE


    ############################################################################
    # Member-level equality check
    ############################################################################
    def __eq__(self, other):
        # Trivial equality test first, are they the same instance?
        if self is other:
            return True

        # Are they the same class?
        if not isinstance(other, TagTypeStruct):
            return False

        # They are the same if the name and field types are identical.
        if self.name != other.name or len(self.fields) != len(other.fields):
            return False

        diffs = ""
        for i in range(len(self.fields)):
            if self.fields[i] != other.fields[i]:
                if diffs == "": diffs += self.name + "\n"
                diffs += "[x] %d %s  <==> %s" % (i, self.fields[i].typeInfo.name, other.fields[i].typeInfo.name) + "\n"

        if diffs != "":
            if config.options.debug:
                print(diffs)
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
    def getSdbDescriptor(self, tag, forHash=False, arrayType=None):

        d = SdbDescriptor()

        self.addHashInfo(d, tag, forHash, arrayType)

        return d
        

    ############################################################################
    # Add tag information to be used for MD5 calculation
    ############################################################################  
    def addHashInfo(self, d, tag, unravelFields = True, arrayType=None):
        if tag is not None:
            name = tag.name
        else:
            name = self.name

        isArray = False
        arrayMin = arrayMax = 0
        if arrayType is None and tag is not None:
            # Check if this top-level tag is actually a struct array
            if tag.typeInfo.type == TagTypeInfo.STRUCT_ARRAY:
                arrayType = tag.typeInfo.typeInfo

        if arrayType is not None:
            isArray = True
            if arrayType.wrappingType == TagTypeInfo.VARIABLE_ARRAY:
                arrayMin = 0
                arrayMax = arrayType.varElemCount.val
            else:
                arrayMin = arrayMax = len(arrayType.elems)

        if self.isVtagPublished:
            # VTag has been found in filter list. Read info
            tagName = self.getVtagName() 
        else:
            tagName = name
            
        if hasattr(d, 'elemType'):
            # This is a special case where we are encoding information of the struct type of a struct array
            d.addCommonFields(d.elemType.name, tagName, d.elemType.name.replace(" ", "_").replace("-", "_").replace(".", "_").lower() + '_t', isArray=isArray)
        else:
            d.addCommonFields(name, tagName, self.getTypeString(), isArray=isArray)
        if isArray:
            d.addRange(arrayMin, arrayMax, isArray=True)

        if unravelFields:
            # The structure hash is also dependent on the width and position of
            # the structure elements, plus the descriptors for all child elements
            lsb = 0
            if hasattr(d, 'elemType'):
                fields = d.elemType.fields
            else:
                fields = self.fields
            for field in fields:
                length = field.getMaxLength()
                d.addField("lsb_bit_position", lsb)
                d.addField("bit_width", 8*length )
                lsb += (8*length)
                field.addHashInfo(field, None)
                d.extend( field )

        elif tag:
            if tag.desc:
                descr = tag.desc + "\n\n"
            else: 
                descr = ""
            descr += self.name + " fields:\n\n"
            for field in self.fields:
                # Extract description from each field:
                try:
                    descr += field.values[field.names.index("name")] + ": "
                    descr += field.values[field.names.index("description_user")] + "\n"
                except:
                    break
            d.addDescription(descr)
            
        if self.isVtagPublished:
            # VTag has been found in filter list. Read info 
            d.addTagData(self.getVtagNumber(), False)


    ############################################################################
    # Get the maximum size of the tag, in bytes
    ############################################################################
    def getMaxLength(self):
        # Note 'size' in TCF appears to be wrong sometimes (e.g. see tag 161,
        # which has length 24 but is actually 84 due to the variable array).
        # Iterate across all elements to get the correct size
        maxLen = 0
        for field in self.fields:
            maxLen += field.getMaxLength()

        return maxLen


    ############################################################################
    # Get the type alignment requirement, in bytes
    ############################################################################
    def getAlignment(self):
        return max(f.getAlignment() for f in self.fields)


    ############################################################################
    # Determine if the tag type contains a variable-length array
    ############################################################################
    def hasVarArray(self):
        for field in self.fields:
            # Short-cut the atomic types here to save some code
            if field.type == TagTypeInfo.INTEGER or field.type == TagTypeInfo.ENUM or field.type == TagTypeInfo.BITFIELD:
                continue
            elif field.hasVarArray():
                return True
        return False


    ############################################################################
    # Load struct definition from the RAM copy of the TCF file
    ############################################################################
    def loadTCF(self, tcf, sectionName):
        from tagtype import TagType         # Circular definition so localise to this function

        sectionName += "%d" % TagTypeInfo.STRUCTURE
        self.name = tcf.get(sectionName, "Name")
        self.size = int(tcf.get(sectionName, "TagLength"))

        sectionName += "_Data"
        for i in range(int(tcf.get(sectionName, "Num"))):
            field = TagType(parent=self)
            field.loadTCF(tcf, sectionName+"_%d" % i)
            self.fields.append(field)


    ############################################################################
    # Save struct to a TCF file
    ############################################################################
    def saveTCF(self, tcf, sectionName):
        sectionName += "%d" % TagTypeInfo.STRUCTURE
        tcf.write("[%s]\n" % sectionName)
        tcf.write("Name = %s\n" % self.name)
        tcf.write("TagLength = %d\n" % self.size)
        tcf.write("\n")

        sectionName += "_Data"
        tcf.write("[%s]\n" % sectionName)
        tcf.write("Num = %d\n" % len(self.fields))
        tcf.write("\n")

        i = 0
        for field in self.fields:
            field.saveTCF(tcf, "%s_%d" % (sectionName, i))
            i += 1


    ############################################################################
    # Save struct to an HTF file
    ############################################################################
    def saveHTF(self, htf, indent, elemSuffix=""):

        # Get associated vtag name for sub-element in a physical tag
        if self.parent is None or self.getTag().isVtag or self.vListObj is None:
            vtagName = ""
        else:
            vtagName = "\t[V] %s" % self.vListObj.tagName

        structStr = "{ "
        if not config.options.compactHTF:
            structStr += "  /* %s%s */" % (SdbDescriptor.makeShortName(self.name), vtagName)
        HtfWriteLine(htf, structStr, indent)

        for field in self.fields:
            if self.fields.index(field) != len(self.fields)-1:
                es = ","
            else:
                es = ""

            field.saveHTF(htf, indent+4, elemSuffix=es)

        # Line continuation is not required if current indent is 0, as this means
        # we are the top-level element of the tag
        if config.options.compactHTF:
            htf.write(" ")  # extra space before closing brace in one-line mode
        HtfWriteLine(htf, "}"+elemSuffix, indent, cont=(indent>0))


    ############################################################################
    # Merge tag values from an .nvm file
    ############################################################################
    def mergeNVM(self, tagVal):
        for field in self.fields:
            tagVal = field.mergeNVM(tagVal)

        return tagVal

    ############################################################################
    # Merge tag values from an .nvm file
    ############################################################################
    def mergeNVMX(self, nvmx):
        nvmxStructElems = nvmx.findall("ELEMENTS")

        for nvmxStructElem, field in zip (nvmxStructElems, self.fields):
            field.mergeNVMX(nvmxStructElem)

    ############################################################################
    # Save struct to an NVM file
    ############################################################################
    def saveNVM(self, nvm):
        for field in self.fields:
            field.saveNVM(nvm)


    ############################################################################
    # Load struct from an XML tree
    ############################################################################
    def loadXML(self, xmlTagType):
        from tagtype import TagType         # Circular definition so localise to this function

        self.name = xmlTagType.get("name")
        self.size = int(xmlTagType.get("length"))

        xmlStructElems = xmlTagType.findall("TAG_TYPE")
        if len(xmlStructElems) == 0:
            raise TagError("Malformed XML: STRUCT doesn't have any elements")

        for xmlStructElem in xmlStructElems:
            field = TagType(parent=self)
            field.loadXML(xmlStructElem)
            self.fields.append(field)

    ############################################################################
    # Load struct from an TCFX tree
    ############################################################################
    def loadTCFX(self, tcfxTagType):
        from tagtype import TagType         # Circular definition so localise to this function

        self.name = tcfxTagType.get("Name")
        self.size = int(tcfxTagType.get("Size"))

        tcfxStructElems = tcfxTagType.findall("ELEMENTS")
        if len(tcfxStructElems) == 0:
            raise TagError("Malformed TCFX: STRUCT doesn't have any elements")

        for tcfxStructElem in tcfxStructElems:
            field = TagType(parent=self)
            field.loadTCFX(tcfxStructElem)
            self.fields.append(field)
            
    ############################################################################
    # Save struct to an XML tree
    ############################################################################
    def saveXML(self, tagElem, isArrayElem=False):
        if isArrayElem:
            typeElem = ET.SubElement(tagElem, "ARRAY")
        else:
            typeElem = ET.SubElement(tagElem, "TAG_TYPE")
        typeElem.set("type", "STRUCT")
        typeElem.set("name", self.name)
        typeElem.set("length", str(self.size))

        for field in self.fields:
            field.saveXML(typeElem)
    ############################################################################
    # Save struct to an TCFX tree
    ############################################################################
    def saveTCFX(self, tagElem, isArrayElem=False):
        if isArrayElem:
            typeElem = ET.SubElement(tagElem, "ARRAY")
            isArrayInit = True
        else:
            typeElem = ET.SubElement(tagElem, "ELEMENTS")
        typeElem.set("Name", self.name)
        
        if not isArrayElem:
            typeElem.set("Type", "STRUCTURE")
            typeElem.set("Size", str(self.size))
        
        
        for field in self.fields:
            field.saveTCFX(typeElem)

    ############################################################################
    # Save struct to an NVMX tree
    ############################################################################
    def saveNVMX(self, tagElem):
        typeElem = ET.SubElement(tagElem, "ELEMENTS")
        typeElem.set("Name", self.name)

        for field in self.fields:
            field.saveNVMX(typeElem)
            
    ############################################################################
    # Save struct to the system configuration database
    ############################################################################
    def saveSDB(self, sdb, tag):
        from tagtype import TagTypeArray    # Circular definition so localise to this function

        # If this struct is actually the definition for a (var/)struct array then
        # separate out that object.
        if isinstance(tag, TagTypeArray):
            arrayType = tag
            tag = None
        else:
            arrayType = None

        # Calculate the hash for this struct and check if it is already in the DB
        d = self.getSdbDescriptor(None, forHash=True, arrayType=arrayType)
        md5 = d.getHash(debug=True)
        sdb.sql.execute("SELECT struct_uid FROM struct_defs where hash='%s'" % md5)
        hashed = sdb.sql.fetchall()

        if len(hashed) == 0:
            # add struct definition to database
            sdb.sql.execute("INSERT INTO struct_defs (struct_uid, struct_name, hash) VALUES(NULL, ?, ?)", (self.getTypeString(), md5))
            sdb.sql.execute("SELECT max(struct_uid) FROM struct_defs")
            structUid = (sdb.sql.fetchone())[0]

            if config.options.debug:
                print("Created struct: %s" % self.getTypeString())

            # Some debugging to assist with issue writing combined physical/virtual database (--scope=all), turned off for now
            if False: #self.getTypeString() == "hci_sco_tx_t":  # Or just do --tags=154,1491
                import pprint
                print("Created struct: %s" % self.getTypeString())
                pp = pprint.PrettyPrinter(indent=4)
                pp.pprint(zip(d.names, d.values))

            sdb.recordStruct(structUid, self.getTypeString(), md5)

            # add struct_element definitions to database
            lsb = 0
            for field in self.fields:
                # Save the nested structure element first, to get its elemUid.
                if self.varElemId is not None and isinstance(field, TagTypeStruct):
                    elemUid = self.varElemId
                else:
                    elemUid, _ = field.saveSDB(sdb, None)

                length = field.getMaxLength()

                sql = "INSERT INTO structure_elements (struct_uid, elem_uid, lsb_bit_position, bit_width) VALUES (?,?,?,?)"
                sqlValues = (structUid, elemUid, lsb, 8*length)
                sdb.sql.execute(sql, sqlValues)
                lsb += (8*length)

        else:
            structUid = hashed[0][0]

            # Even if the structure hash is unchanged, we need verify the sub-elements are in the DB as well
            # TBD: well not sure why the hash would be correct in this case, but it copies the Perl source
            #for field in self.fields:
            #    _, _ = field.saveSDB(sdb, None)

        # Now add the config element entry as well. Recreate the descriptor using
        # just the common fields to ensure the hash is correct
        #if arrayType and arrayType.arrayType == TagTypeInfo.VARIABLE_ARRAY:
        #    # Don't use the VAR_ARRAY to build the config_element here, as the top-level
        #    # isn't an array
        #    arrayType = None
        #    print "SKIPPING arrayType"

        d = self.getSdbDescriptor(tag, arrayType=arrayType)
        elemUid = d.saveSDB(sdb)

        # Cross-reference the config_element for this type to the FW release
        sdb.xrefElement(elemUid, structUid, TagTypeInfo.STRUCTURE)

        return elemUid, structUid


    ############################################################################
    # Get the ROM default value for this type, for inserting into the SDB
    ############################################################################
    def getSdbDefault(self, tag):
        # The struct default is the simply the concatenation of the fields of
        # the struct. The struct definition is required to be aligned to the
        # memory layout by design, so there is no need for packing or alignment
        # handling here.
        #
        default = []
        for field in self.fields:
            default.extend(field.getSdbDefault(None))
        return default


    ############################################################################
    # Save struct to an VLIST file
    ############################################################################
    def saveVLIST(self, vlist, tag, print_intermediate = True):
        from tagtype import TagTypeArray    # Circular definition so localise to this function

        expname = self.getTypeStringRecursive()

        # Check if we need to update tag fields
        if tag_descriptor.vListInfo.isVListValid():
            if isinstance(tag, TagTypeArray):
                # This is a special case where we have to use the parent's name 
                # (this is element of parent) 
                recName = tag.getTypeStringRecursive()
            else:
                recName = self.getTypeStringRecursive()
            self.vListObj = tag_descriptor.vListInfo.findTagByName(recName)

        if (print_intermediate and
             vlist.filter.vtagEnabled(expname) and 
             not vlist.filter.tagArrayExpandEnabled(expname)):
            
            # Make sure this is published in case it is not in the known VTag list
            self.isVtagPublished = True

            # If this struct is actually the definition for a (var/)struct array then
            # separate out that object.
            if isinstance(tag, TagTypeArray):
                arrayType = tag
                tag = None
            else:
                arrayType = None
            self.addHashInfo(self, tag, False, arrayType=arrayType)
            
            md5 = self.getHash(shortHash=True, debug=True)
            
            if not tag_descriptor.vListInfo.isTagDefined(expname, md5): 
                vlist.SaveTagInfo(expname, md5, int(self.values[self.names.index("psid")]), self.getTagName())
                
            if config.options.debug:
                print("saveVLIST tagtype_struct " + expname)
        
        for field in self.fields:
            field.saveVLIST(vlist, None)


    ############################################################################
    # Export tag to VT info file
    ############################################################################
    def saveVtag(self, vtag):
        
        extentedName = self.getTypeStringRecursive()
        vlistObj = tag_descriptor.vListInfo.findTagByName(extentedName) 
        if (vlistObj and (config.options.buildType == 'ROM' or vlistObj.tagId > config.options.patchBaseId)):
            
            # Save element as UINT8
            vtag.writeOutFile(vlistObj.tagId, self.getStructStringRecursive(), 'UINT8', vlistObj.physicalTag.isPatched)
        
        for field in self.fields:
            field.saveVtag(vtag)


    ############################################################################
    # Generate tag data types header information
    ############################################################################
    def genTagDataTypes(self, file, generatedTypes, indent):
        indent += 4
        
        # Generate the sub-types for each structure element */
        for field in self.fields:
            field.genTagDataTypes(file, generatedTypes, indent)

        # Now generate the structure definition itself
        typeName = CodeGen.makeUpperIdent("CFG_STRUCT_" + self.name + "_TYPE")
        if not CodeGen.checkUnique(generatedTypes, typeName, self):
            return
        
        file.write("\n")
        file.write("typedef  struct \n")
        file.write("{")

        indent = 4
        for field in self.fields:
            file.write("\n")
            field.genTagElement(file, indent)

        file.write("\n} %s;" % typeName)


    ############################################################################
    # Generate tag element information
    ############################################################################
    def genTagElement(self, file, indent):
        typeName = CodeGen.makeUpperIdent("CFG_STRUCT_" + self.name + "_TYPE")
        file.write(" "*indent + CodeGen.padIdentMid(typeName) + CodeGen.makeIdent("Cfg_" + self.name) + ";")


    ############################################################################
    # Generate tag element reference information
    ############################################################################
    def genTagElementRef(self, file, baseDefine, baseElem):
        elemName = baseElem+CodeGen.makeIdent("Cfg_"+self.name)
        file.write("#define  %s" % CodeGen.padTo(CodeGen.makeUpperIdent("%s_%s_PTR" % (baseDefine, self.name)), 40))
        file.write(" ((UINT8 *) &(%s))\n" % elemName)

        file.write("#define  %s" % CodeGen.padTo(CodeGen.makeUpperIdent("%s_%s" % (baseDefine, self.name)), 40))
        file.write(" (%s)\n" % elemName)

        for field in self.fields:
            file.write("\n")
            field.genTagElementRef(file, baseDefine+"_"+self.name, elemName+".")


    ############################################################################
    # Generate tag default values
    ############################################################################
    def genTagDefaultData(self, file, indent):
        file.write(" "*indent + "{ ")

        isFirst = True
        for field in self.fields:
            if isFirst:
                isFirst = False
                file.write("\n")
            else:
                file.write(",\n")
            field.genTagDefaultData(file, indent+4)

        file.write("\n" + " "*indent + "}")


    ############################################################################
    # Generate tag format information for HTML
    ############################################################################
    def genTagUserFormat(self, file, indent, byteIndex):
        for field in self.fields:
            byteIndex = field.genTagUserFormat(file, indent, byteIndex)
        return byteIndex
