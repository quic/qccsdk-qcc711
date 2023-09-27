################################################################################
# Tags processing.
################################################################################
# Copyright (c) 2018-2022 Qualcomm Technologies International, Ltd.
# All Rights Reserved
# Confidential and Proprietary - Qualcomm Technologies International, Ltd.
################################################################################


################################################################################
# Library Imports
################################################################################
from __future__ import print_function
try:
    from future import standard_library
    standard_library.install_aliases()
    from builtins import str
except ImportError:
    pass
import os.path, textwrap
from datetime import date
import traceback
try:
    import configparser
except ImportError:
    import ConfigParser
from tag_groups import TagGroups
from tag_platforms import TagPlatforms
from tag_features import TagFeatures
from tagtype import TagType
import config
from config import BasicType, TagTypeInfo, TagError
from hydra_db import SdbDescriptor
from codegen import HtfWriteLine
import tag_descriptor
from xml_wrapper import ET, xmlToString


################################################################################
# Global Variables
################################################################################

# Mandatory NVM file sections
mandatoryNvmSections = [ "General", "Tag" ]

# Mandatory NVM section options
mandatoryNvmOptions = { 'General' : [ "Signature", "FormatVersion", "Timestamp" ], 'Tag' : [ "Num" ] }


################################################################################
# Local Functions
################################################################################


################################################################################
# Tags Class
#
# Holds all information on the defined Tags.
################################################################################
class Tag:
    def __init__(self, index):
        self.idx = index
        self.legacyPlatform = None  # only populated when loading legacy TCFs
        self.isVtag = False
        self.isUpdated = False      # only populated during merge nvm , used 
                                    # for storing only updated tags.

    ############################################################################
    # Return the top-level tag object. This is used by nested types to call
    # back through their parents back to this function
    ############################################################################
    def getTag(self):
        return self


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
        return self.typeInfo.hasVarArray()


    ############################################################################
    # Check if code should be generated for this tag
    ############################################################################
    def genCode(self):
        # We currently don't store the Obsolete or Duplicate status, so unlike
        # TagCfg this is just based on the NoDefaults tag
        if self.noDef:
            return False
        return True


    ############################################################################
    # Extract vtag definitions from this tag
    ############################################################################
    def extractVtags(self, vtags):
        return self.typeInfo.extractVtags(self, vtags)


    ############################################################################
    # Load Virtual Tag definition from a sub-type of an existing physical tag
    ############################################################################
    def loadVtag(self, physTagType, vtags):
        # Is this type definion a vtag?
        vListObj = tag_descriptor.vListInfo.findTagByName(physTagType.getTypeStringRecursive())
        if vListObj is None:
            return False

        # Attach tag type to vtag definition
        if vListObj.tagObject is not None:
            raise TagError("vtag signature %d matches more than one physical tag (%d & %d)" % (vListObj.tagId, vListObj.tagObject.getTag().num, physTagType.getTag().num))
        vListObj.tagObject = physTagType
        vListObj.physicalTag = self

        # Cross-reference the vtag definition with the tag type
        physTagType.vListObj = vListObj
        # VTag is in VTag list, so we need to publish it
        physTagType.isVtagPublished = True

        # Now create a brand new Tag object to hold the vtag definition
        newVtag = Tag(len(vtags))
        vtags.append(newVtag)

        newVtag.isVtag = True
        newVtag.num = vListObj.tagId
        newVtag.name = vListObj.tagName

        # Extract the tag description from the tag type. Note that struct and
        # bit types have no field description, but maybe the physical tag parent
        # does so we try to get it from there. This will fail for structs within structs
        from tagtype_struct import TagTypeStruct
        from tagtype_bits import TagTypeBits

        if not isinstance(physTagType, TagTypeStruct) and not isinstance(physTagType, TagTypeBits):
            newVtag.desc = physTagType.desc
        elif hasattr(physTagType.parent, 'desc'):
            newVtag.desc = physTagType.parent.desc
        else:
            newVtag.desc = None # TBD: need to get struct-of-struct descs from somewhere...

        newVtag.note = None    # TBD: get from physical tag type, once we move to new XML format

        # Virtual tag inherits the physical tag group
        newVtag.group = self.group
        newVtag.groupIdx = self.groupIdx

        if vListObj.isInternal:
            # TBD: think this is pending an update from my shelved changes for Razor's new XML format
            newVtag.internal = 1
        else:
            newVtag.internal = 0

        # Virtual tags currently always generate code and are non-dynamic tags.
        # Virtual tags don't currently support relationships
        newVtag.noDef = 0
        newVtag.dynMem = 0
        newVtag.related = []

        # This vtag simply copies the tag type from the physical tag
        tagType = TagType(parent=newVtag)
        tagType.type = physTagType.wrappingType
        tagType.typeInfo = physTagType
        newVtag.typeInfo = tagType

        return True


    ############################################################################
    # Load Tag Group definitions from the RAM copy of the TCF file
    ############################################################################
    def loadTCF(self, tcf, tagSection, tagGroups, tagPlatforms):
        self.num      = int(tcf.get(tagSection, "Number"))
        self.name     = tcf.get(tagSection, "Name")
        self.desc     = tcf.get(tagSection, "Desc")
        self.note     = None    # TCF format doesn't support internal notes
        self.group    = tcf.get(tagSection, "GroupName")
        self.internal = int(tcf.get(tagSection, "SiliconWave"))
        self.noDef    = int(tcf.get(tagSection, "NoDefaults"))  # If this is set no code will be generated
        self.dynMem   = int(tcf.get(tagSection, "UseDynMem"))
        self.related  = []

        tagRelated = tcf.get(tagSection, "RelatedTagNumbers")
        if tagRelated != "":
            self.related = [int(RT) for RT in tagRelated.replace(" ", "").split(",")]

        # Save the platform disable information although note we don't use this
        # when writing TCFs just now
        self.legacyPlatform = {}
        for tagPlat in tagPlatforms.platforms:
            disabled = False
            if int(tcf.get(tagSection, "%s%s_Disable" % (tagSection, tagPlat['name']))):
                disabled = True
            self.legacyPlatform[tagPlat['name']] = disabled

        # TagCfg.exe has code for backward compatibility where the group index
        # was defined without a GroupName. That conversion is not required here
        # as we currently are using "fresh" .tcf files that always have the
        # GroupName defined. If this exception fires then you may need to
        # open the .tcf in TagCfg.exe and save it to update it.
        #
        if self.group == "":
            raise TagError("Empty GroupName for tag %d" % self.num)

        # The GroupIndex field is not correctly populated in the source files so validate against GroupName instead.
        self.groupIdx = tagGroups.getIndex(self.group)

        # Get the tag type information for this tag
        tagType = TagType(parent=self)
        tagType.loadTCF(tcf, tagSection+"_Type")
        self.typeInfo = tagType

        if config.options.verbose:
            # Print NVM tags that have non-default values for little-used options
            tmp = int(tcf.get(tagSection, "VersionAdded"))
            if tmp!=0: print("WARNING! Tag %d has VersionAdded = %d" % (self.num, tmp))
            tmp = int(tcf.get(tagSection, "Obsolete"))
            if tmp!=0: print("WARNING! Tag %d has Obsolete = %d" % (self.num, tmp))
            tmp = int(tcf.get(tagSection, "VersionObsolete"))
            if tmp!=9999: print("WARNING! Tag %d has VersionObsolete = %d" % (self.num, tmp))
            tmp = tcf.get(tagSection, "ObsoleteDetails")
            if tmp != "In Use" and tmp != "": print("WARNING! Tag %d has ObsoleteDetails = %s" % (self.num, tmp))
            tmp = int(tcf.get(tagSection, "Duplicate"))
            if tmp!=0: print("WARNING! Tag %d has Duplicate = %d" % (self.num, tmp))
            tmp = int(tcf.get(tagSection, "Dynamic"))
            if tmp!=0: print("WARNING! Tag %d has Dynamic = %d" % (self.num, tmp))
            tmp = int(tcf.get(tagSection, "NoRAM"))
            if tmp!=0: print("WARNING! Tag %d has NoRAM = %d" % (self.num, tmp))
            tmp = int(tcf.get(tagSection, "OverrideOnly"))
            if tmp!=0: print("WARNING! Tag %d has OverrideOnly = %d" % (self.num, tmp))
            tmp = int(tcf.get(tagSection, "ExtendedTag"))
            if tmp!=0: print("WARNING! Tag %d has ExtendedTag = %d" % (self.num, tmp))
            tmp = int(tcf.get(tagSection, "PlatformSpecific"))
            if tmp!=1: print("WARNING! Tag %d has PlatformSpecific = %d" % (self.num, tmp))


    ############################################################################
    # Save Tag definitions to a TCF file
    ############################################################################
    def saveTCF(self, tcf, tagPlatforms):
        # Write the heading
        sectionName = "Tags%d" % self.idx
        tcf.write("[%s]\n" % sectionName)

        # And now write the tag information. A lot of these don't seem to be
        # used in current firmware so for now we just write default values.
        tcf.write("Number = %u\n" % self.num)
        tcf.write("Name = %s\n" % self.name)
        tcf.write("Desc = %s\n" % self.desc)
        tcf.write("VersionAdded = %u\n" % 0)
        tcf.write("Obsolete = %u\n" % 0)
        tcf.write("VersionObsolete = %u\n" % 9999)
        tcf.write("ObsoleteDetails = %s\n" % "")  # Can also be "In Use" in some cases but doesn't seem to matter
        tcf.write("SiliconWave = %u\n" % self.internal)
        tcf.write("Duplicate = %u\n" % 0)
        tcf.write("Dynamic = %u\n" % 0)
        tcf.write("NoRAM = %u\n" % 0)
        tcf.write("OverrideOnly = %u\n" % 0)
        tcf.write("NoDefaults = %u\n" % self.noDef)
        tcf.write("UseDynMem = %u\n" % self.dynMem)
        tcf.write("ExtendedTag = %u\n" % 0)
        tcf.write("RelatedTagNumbers = %s\n" % ", ".join([str(RT) for RT in self.related]))

        tcf.write("GroupIndex = %u\n" % self.groupIdx)
        tcf.write("GroupName = %s\n" % self.group)
        tcf.write("PlatformSpecific = %u\n" % 1)
        tcf.write("\n")

        if self.note is not None:
            print("WARNING! Internal note on tag %d lost when writing TCF" % self.num)

        # Write platform disable information - this doesn't seem to be generated or used properly so just write the same value for new TCFs
        for tagPlat in tagPlatforms.platforms:
            platDisable = 0
            if config.options.compat:
                platDisable = 1
            tcf.write("%s%s_Disable = %u\n" % (sectionName, tagPlat['name'], platDisable))
        tcf.write("\n")

        # Write tag type information
        sectionName += "_Type"
        if self.typeInfo is not None:
            self.typeInfo.saveTCF(tcf, sectionName)


    ############################################################################
    # Save Tag value to an HTF file
    ############################################################################
    def saveHTF(self, htf, indent):
        msg = ""
        if self.typeInfo is None:                       # Don't emit empty tags
            msg = "HTF: Skipping empty tag %d"
        if self.getMaxLength() == 0:                    # Can't write a zero-length tag
            msg = "HTF: Skipping zero-length tag %d"

        if msg != "":
            if config.options.verbose: print(msg % self.num)
            return

        # Write the tag
        htf.write("\n# %s\n" % self.name)
        if not config.options.compactHTF:
            htf.write("# \n")
            desc = self.desc if self.desc else ""
            htf.write("# %s\n" % textwrap.fill(desc, width=80, subsequent_indent="# "))
            htf.write("# \n")

        newTagStr = "%s = " % SdbDescriptor.makeShortName(self.name)
        newTagStr = newTagStr.upper()   # capitalise tag names in the HTF to make them stand out

        # Basic integer and enum types remain on one line for clarity, all others are written multi-line
        if self.typeInfo.type != TagTypeInfo.INTEGER and self.typeInfo.type != TagTypeInfo.ENUM:
            HtfWriteLine(htf, newTagStr, indent=0)
        else:
            htf.write(newTagStr)

        self.typeInfo.saveHTF(htf, indent)
        htf.write("\n\n")


    ############################################################################
    # Merge tag values from an .nvm file
    ############################################################################
    def mergeNVM(self, tagVal):
        return self.typeInfo.mergeNVM(tagVal)

    ############################################################################
    # Load Tag definition from an NVMX tree
    ############################################################################
    def mergeNVMX(self, nvmxTag):
        # Get the tag type information for this tag
        nvmxTagType = nvmxTag.find("ELEMENTS")
        return self.typeInfo.mergeNVMX(nvmxTagType)
        
    ############################################################################
    # Save Tag value to an NVM file
    ############################################################################
    def saveNVM(self, nvm):
        msg = ""
        if self.typeInfo is None:                       # Don't emit empty tags
            msg = "NVM: Skipping empty tag %d"
        if self.getMaxLength() == 0:                    # Can't write a zero-length tag
            msg = "NVM: Skipping zero-length tag %d"

        if msg != "":
            if config.options.verbose: print(msg % self.num)
            return

        # Write the heading
        sectionName = "Tag%d" % self.idx
        nvm.write("[%s]\n" % sectionName)

        # And now write the tag value information.
        nvm.write("TagNum = %u\n" % self.num)
        nvm.write("TagLength = %u\n" % self.getMaxLength())
        nvm.write("TagValue =")

        self.typeInfo.saveNVM(nvm)

        nvm.write("\n\n")


    ############################################################################
    # Load Tag definition from an XML tree
    ############################################################################
    def loadXML(self, xmlTag, tagGroups):
        self.num = int(xmlTag.get("id"))
        self.name = xmlTag.get("name")

        self.group = xmlTag.get("group", "")
        if self.group == "":
            raise TagError("No tag 'group' provided for tag %d" % self.num)

        # Convert the group to a group index for TCF backward compatibility
        self.groupIdx = tagGroups.getIndex(self.group)

        tmp = xmlTag.get("internal")
        if tmp is not None:
            self.internal = 1
        else:
            self.internal = 0

        tmp = xmlTag.get("noDefaults")
        if tmp is not None:
            # If this is set no code will be generated
            self.noDef = 1
        else:
            self.noDef = 0

        tmp = xmlTag.get("dynamic")
        if tmp is not None:
            self.dynMem = 1
        else:
            self.dynMem = 0

        descElem = xmlTag.find("DESCRIPTION")
        if descElem is not None and descElem.text is not None:
            self.desc = descElem.text
        else:
            self.desc = ""

        noteElem = xmlTag.find("NOTE")
        if noteElem is not None:
            self.note = noteElem.text
        else:
            self.note = None

        self.related = []

        tagRelated = xmlTag.find("RELATED_TAGS")
        if tagRelated is not None and tagRelated.text != "":
            self.related = [int(RT) for RT in tagRelated.text.replace(" ", "").split(",")]

        # Get the tag type information for this tag
        xmlTagType = xmlTag.find("TAG_TYPE")
        if xmlTagType is None:
            raise TagError("Malformed XML: tag %d doesn't have <TAG_TYPE> element" % self.num)

        tagType = TagType(parent=self)
        tagType.loadXML(xmlTagType)
        self.typeInfo = tagType

    ############################################################################
    # Load Tag definition from an TCFX tree
    ############################################################################
    def loadTCFX(self, tcfxTag, tagGroups):
        self.num = int(tcfxTag.get("Number"))
        
        self.name = tcfxTag.get("Name")
        
        self.tagattr = tcfxTag.find("TAG_ATTRIBUTES")
        
        self.group = self.tagattr.get("TagGroups", "")
        if self.group == "":
            raise TagError("No tag 'group' provided for tag %d" % self.num)

        # Convert the group to a group index for TCF backward compatibility
        self.groupIdx = tagGroups.getIndex(self.group)

        tmp = self.tagattr.get("Internal")
        if tmp is None or tmp.lower() == "true":
            self.internal = 1
        else:
            self.internal = 0

        tmp = self.tagattr.get("GenerateSource")
        if tmp is None or tmp.lower () == "true":
            # If this is set no code will be generated
            self.noDef = 0
        else:
            self.noDef = 1
            
        tmp = self.tagattr.get("Dynamic")
        if tmp is None or tmp.lower() == "false":
            self.dynMem = 0
        else:
            self.dynMem = 1
            
        tmp = self.tagattr.get("Platforms")
        if tmp is None:
            self.platforms = ""
        else:
            self.platforms = tmp

        tmp = self.tagattr.get("PlatformSpecific")
        if tmp is None or tmp.lower () == "true":
            # If this is set no code will be generated
            self.platspecific = 1
        else:
            self.platspecific = 0
            
        descElem = tcfxTag.find("DESCRIPTION")
        
        if descElem is not None and descElem.text is not None:
            self.desc = descElem.text.strip()
        else:
            self.desc = ""
        
        noteElem = tcfxTag.find("NOTE")
        if noteElem:
            self.note = noteElem.text
        else:
            self.note = None

        self.related = []

        tagRelated = tcfxTag.find("RELATED_TAGS")
        if tagRelated is not None and tagRelated.text != "":
            self.related = [int(RT) for RT in tagRelated.text.replace(" ", "").split(",")]

        # Get the tag type information for this tag
        tcfxTagType = tcfxTag.find("ELEMENTS")
        if tcfxTagType is None:
            raise TagError("Malformed TCFX: tag %d doesn't have <ELEMENTS> element" % self.num)        

        tagType = TagType(parent=self)
    
        tagType.loadTCFX(tcfxTagType)
        self.typeInfo = tagType
        
    ############################################################################
    # Save Tag definition to an XML tree
    ############################################################################
    def saveXML(self, rootElem):
        tagElem = ET.SubElement(rootElem, "TAG")
        tagElem.set("id", str(self.num))
        tagElem.set("name", self.name)

        tagElem.set("group", self.group)
        if self.internal:
            tagElem.set("internal", "")
        if self.noDef:
            tagElem.set("noDefaults", "")
        if self.dynMem:
            tagElem.set("dynamic", "")

        descElem = ET.SubElement(tagElem, "DESCRIPTION")
        descElem.text = self.desc

        if self.note is not None:
            noteElem = ET.SubElement(tagElem, "NOTE")
            noteElem.text = self.note

        if len(self.related):
            related = ET.SubElement(tagElem, "RELATED_TAGS")
            related.text = ", ".join([str(RT) for RT in self.related])

        self.typeInfo.saveXML(tagElem)

    ############################################################################
    # Save Tag definition to an TCFX tree
    ############################################################################
    def saveTCFX (self, rootElem):
        tagElem = ET.SubElement(rootElem, "TAG")
        tagElem.set("Number", str(self.num))
        tagElem.set("Name", self.name)
        
        descElem = ET.SubElement(tagElem, "DESCRIPTION")
        descElem.text = self.desc
        
        tagattr = ET.SubElement(tagElem, "TAG_ATTRIBUTES")
        tagattr.set("Version", "0")
        tagattr.set("GenerateSource", str(not bool (self.noDef)).lower())
        tagattr.set("Internal", str(bool(self.internal)).lower())
            
        tagattr.set("Dynamic", str(bool(self.dynMem)).lower())
        tagattr.set("TagGroups", self.group)
        tagattr.set("PlatformSpecific", str(bool(self.platspecific)).lower())
        tagattr.set("Platforms", self.platforms)
        #Features attribute is currently placeholder.
        #Each Tag will be mapped to a Feature Set and code generation
        #Should depend on Features once defined in TCFX
        tagattr.set("Features", "")

        if self.note is not None:
            noteElem = ET.SubElement(tagElem, "NOTE")
            noteElem.text = self.note

        if len(self.related):
            related = ET.SubElement(tagElem, "RELATED_TAGS")
            related.text = ", ".join([str(RT) for RT in self.related])
        
        self.typeInfo.saveTCFX (tagElem)

    ############################################################################
    # Save Tag definition to an NVMX tree
    ############################################################################
    def saveNVMX (self, rootElem):
        tagElem = ET.SubElement(rootElem, "TAG")
        tagElem.set("Name", self.name)
        
        self.typeInfo.saveNVMX (tagElem)

    ############################################################################
    # Save all tag information to the system configuration database
    ############################################################################
    def saveSDB(self, sdb):
        # Save the top-level type definition for the tag; for nested structures
        # this will recursively save definitions as required. The type returns
        # its generic elem_uid from the config_elements table. Enums and structs
        # also return their type UID from the enum_defs or struct_defs table.
        #
        if config.options.verbose:
            print("**** Saving tag %d to SDB" % self.num)

        (elemUid, _) = self.typeInfo.saveSDB(sdb, self)

        if not config.options.noDefaults:
            # Get the defaults for the tag and save to the database. Complex tags
            # are treated as an array stored at the top-level of the structure,
            # while integer types (VALUE & ENUM) can be written directly to the
            # config_element_default_values table.

            default = self.typeInfo.getSdbDefault(self)
            if len(default) == 1:
                default = default[0]

            if type(default) is list:
                defaultDescriptor = ",".join(str(v) for v in default)
            else:
                defaultDescriptor = default

            # Save the default value, for arrays the hash includes the array string
            d = SdbDescriptor()
            d.addDefault(elemUid, defaultDescriptor)
            defUid = d.saveDefault(sdb)

            if type(default) is list:
                # Write each byte of the default array to the database as well
                for d in default:
                    sql = "INSERT INTO default_arrays (def_uid, value) VALUES (?,?)"
                    sdb.sql.execute(sql, (defUid, d))


    ############################################################################
    # Save struct to an VLIST file
    ############################################################################
    def saveVLIST(self, vlist):
        return self.typeInfo.saveVLIST(vlist, self)
        

    ############################################################################
    # Export tag to VT info file
    ############################################################################
    def saveVtag(self, vtag):
        return self.typeInfo.saveVtag(vtag)


    ############################################################################
    # Generate tag data types header information
    ############################################################################
    def genTagDataTypes(self, file, generatedTypes):
        self.typeInfo.genTagDataTypes(file, generatedTypes, 0)
        

    ############################################################################
    # Get the extended type name as a string, including the parent's name
    ############################################################################
    def getTypeStringRecursive(self):
        if (not hasattr(self, "typeInfo")) or self is self.typeInfo.parent:
            return ""
        else:
            return self.typeInfo.getTypeStringRecursive()
        

    ############################################################################
    # Get the extended C struct name as a string, including parent
    ############################################################################
    def getStructStringRecursive(self):
        if (not hasattr(self, "typeInfo")) or self is self.typeInfo.parent:
            return ""
        else:
            return self.typeInfo.getStructStringRecursive()


    ############################################################################
    # Check if top level tag is internal
    ############################################################################
    def isTagInternal(self):
        return self.internal
        
        
    ############################################################################
    # Check if one particular element is a table element and return index
    ############################################################################
    def readTableElementIdx(self):
        if (not hasattr(self, "typeInfo")) or self is self.typeInfo.parent:
            return None
        else:
            return self.typeInfo.getTypeStringRecursive()



################################################################################
# NvmTags Class
#
# Generic class holding an internal representation of the NVM tags
################################################################################
class NvmTags:
    # Class variables to define constants.
    MAX_LL_TAGS = 255

    def __init__(self):
        # Tag Groups and Tag Platforms
        self.tagGroups = TagGroups()
        self.tagPlatforms = TagPlatforms()
        self.tagFeatures = TagFeatures()

        # Tag information (the bulk of the data)
        self.maxNameLen = 0
        self.tags = []
        self.vtags = []
        self.tagScope = []
        self.knownTags = {}

        # General information held at the top of the TCF file
        self.sig = ""
        self.version = ""
        self.timestamp = ""
        self.newTag = 0


    ############################################################################
    # Determine if a given tag should be processed. This is dependent on the
    # range of tags provided on the command line (via --tags) and whether
    # internal tags are to be filtered out (via --filterInternal).
    ############################################################################
    def processTag(self, tag):
        if config.options.filterInternal and tag.internal:
            # Don't process internal tags
            return False

        if config.options.tags is not None and tag.num not in config.options.tags:
            # Tag number is not in the provided list of tags to process
            return False

        return True


    ############################################################################
    # Lookup a given tag number and return tag information if it exists
    ############################################################################
    def getTag(self, num):
        if num in self.knownTags:
            return self.knownTags[num]
        return None


    ############################################################################
    # Check if any Lower Layer tags exist in the tag list
    ############################################################################
    def hasLLTags(self):
        for tag in self.tags:
            if tag.num <= NvmTags.MAX_LL_TAGS:
                return True
        return False


    ############################################################################
    # Check if any Upper Layer tags exist in the tag list
    ############################################################################
    def hasULTags(self):
        for tag in self.tags:
            if tag.num > NvmTags.MAX_LL_TAGS:
                return True
        return False


    ############################################################################
    # Check if any Lower Layer tags exist in the tag list
    ############################################################################
    def genSourceForGroup(self, group, isLL):
        for tag in self.tags:
            if (isLL and tag.num <= NvmTags.MAX_LL_TAGS) or (not isLL and tag.num > NvmTags.MAX_LL_TAGS):
                # This tag is in the supplied tag group and will generate code
                if group==tag.group and tag.genCode():
                    return True
        return False


    ############################################################################
    # Extract vtag definitions from available physical tags
    ############################################################################
    def extractVtags(self):
        for tag in self.tags:
            # For each physical tag scan it for all known virtual tags
            tag.extractVtags(self.vtags)
            if tag.num > config.options.lastTagId:
                tag.isPatched = True
            else:
                tag.isPatched = False

        for vtag in self.vtags:
            # Fix up the index based on the number of physical tags
            vtag.idx += len(self.tags)

            # Extend knownTags based on the vtags
            if vtag.num in self.knownTags:
                # Don't allow multiple tags with same ID, whether physical or virtual
                raise TagError("Duplicate vtag number %d found" % vtag.num)
            else:
                # Copy the tag into a known tags dictionary for faster retrieval
                self.knownTags[vtag.num] = vtag

        # Set the output scope of tag classes
        if config.options.scope != "virtual":
            self.tagScope.extend(self.tags)
        if config.options.scope != "physical":
            self.tagScope.extend(self.vtags)

        # Some output types are better to have the list sorted by tag ID
        if config.options.output == "html" or config.options.output == "sdb" or config.options.output == "nvm":
            self.tagScope.sort(key=lambda x: x.num)


    ############################################################################
    # Read all tag information from a TCF
    ############################################################################
    def loadTCF(self, tcf):
        # Read the [General] information section
        self.sig = tcf.get("General", "Signature")
        self.version = tcf.get("General", "FormatVersion")
        self.timestamp = tcf.get("General", "TimeStamp")
        self.newTag = int(tcf.get("General", "NewTagNumber"))

        # Validate signature
        if self.sig != "Matunga":
            raise TagError("Unknown TCF signature: %s" % self.sig)

        # Validate version
        if self.version != "1.0":
            raise TagError("Unexpected TCF version: %s" % self.version)

        # Read the Tag Groups
        self.tagGroups.loadTCF(tcf)

        # Read the Tag Platforms
        self.tagPlatforms.loadTCF(tcf)

        # Read the Tags
        numTagsTCF = int(tcf.get("Tags", "Num"))
        relatedTags = {}
        for i in range(0, numTagsTCF):
            tagSection = "Tags%d" % i
            if not tcf.has_section(tagSection):
                raise TagError("Tag %d is missing section '%s'" % (i, tagSection))
            if not tcf.has_option(tagSection, "Name"):
                raise TagError("Tag '%s' is missing 'Name'" % (tagSection))
            if not tcf.has_option(tagSection, "Desc"):
                raise TagError("Tag '%s' is missing 'Desc'" % (tagSection))

            tag = Tag(i)
            tag.loadTCF(tcf, tagSection, self.tagGroups, self.tagPlatforms)
            self.tags.append(tag)

            if tag.num in self.knownTags:
                # We don't currently support parsing a TCF with multiple tags with the same number
                raise TagError("Duplicate tag number %d found in file" % tag.num)
            else:
                # Copy the tag into a known tags dictionary for faster retrieval
                self.knownTags[tag.num] = tag

            if tag.related != "":
                if tag.num not in relatedTags:
                    relatedTags[tag.num] = tag.related
                elif relatedTags[tag.num] != tag.related:
                    raise TagError("Same tag %d has different relations '%s' and '%s'" % (tag.num, relatedTags[tag.num], tag.related) )

            if len(tag.name) > self.maxNameLen:
                self.maxNameLen = len(tag.name)

        # Test to see if all related tags actually exist in the file (this is a minor warning)
        if config.options.verbose:
            for tagNum, tagRelated in relatedTags.items():
                for related in tagRelated:
                    if related not in self.knownTags:
                        print("WARING! Tag %d claims to be related to non-existent tag: %d" % (tagNum, related))


    ############################################################################
    # Save all tag information to an opened TCF file
    ############################################################################
    def saveTCF(self, outputFile):
        # Open the file for writing, we just write text straight to the file
        # rather than trying to build up the structure in RAM first.
        tcf = open(outputFile, "w")

        # Write the [General] information section, updating the timestamp as we go
        tcf.write("#\n")
        tcf.write("#\n")
        tcf.write("#  Please DO NOT hand edit this file! Use TagCfg tool to Edit.\n")
        tcf.write("#\n")
        tcf.write("#\n")
        tcf.write("\n")
        tcf.write("\n")
        tcf.write("[General]\n")
        tcf.write("Signature = %s\n" % self.sig)
        tcf.write("FormatVersion = %s\n" % self.version)
        tcf.write("Timestamp = %s\n" % config.timestamp.strftime("%A %B %d, %Y   %I:%M:%S %p"))
        tcf.write("NewTagNumber = %d\n" % self.newTag)
        tcf.write("\n")

        # Write the Tag Groups
        self.tagGroups.saveTCF(tcf)

        # Write the Tag Platforms
        self.tagPlatforms.saveTCF(tcf)

        # Count the number of tags to be written in a first pass (required for TCF header)
        tagsWritten = 0
        for tag in self.tagScope:
            if self.processTag(tag):
                tagsWritten += 1

        # Write the Tags
        tcf.write("\n#\n# ------------------------ Tag Data ------------\n#\n\n")
        tcf.write("[Tags]\n")
        tcf.write("Num = %u\n" % tagsWritten)
        tcf.write("\n")

        tagFilteredIdx = 0
        for tag in self.tagScope:
            if self.processTag(tag):
                # Temporarily adjust the tag index so that we write a TCF file
                # containing contiguous tag indices
                savedIdx = tag.idx
                tag.idx = tagFilteredIdx
                tagFilteredIdx += 1

                # Write the tag to the TCF file
                tag.saveTCF(tcf, self.tagPlatforms)

                # Restore the original tag index. This bit is not strictly needed,
                # as the script will exit after the save, but it's cleaner.
                tag.idx = savedIdx

        tcf.close()


    ############################################################################
    # Save tag values to an HTF file
    ############################################################################
    def saveHTF(self, outputFile):
        # Open the file for writing, we just write text straight to the file
        # rather than trying to build up the structure in RAM first.
        htf = open(outputFile, "w")

        htf.write("version=UNRELEASED\n\n")
        htf.write("file=bt15\n\n")

        # Save the selected tags default values to the HTF file
        for tag in self.tagScope:
            if self.processTag(tag):
                if not tag.hasVarArray():
                    tag.saveHTF(htf, 0)
                elif config.options.verbose:
                    print("Not exporting tag %d '%s' to HTF, as it contains a variable-length array" % (tag.num, tag.name))

        htf.close()


    ############################################################################
    # Merge tag values from an .nvm file
    ############################################################################
    def mergeNVM(self, nvm):
        # Some basic validation - we expect a certain set of top-level sections to exist
        for section in mandatoryNvmSections:
            if not nvm.has_section(section):
                raise TagError("NVM file is missing mandatory section '%s'" % section)

        # And we expect the top-level groups to have certain options defined
        for section,options in mandatoryNvmOptions.items():
            for option in options:
                if not nvm.has_option(section, option):
                    raise TagError("Section '%s' is missing mandatory field '%s'" % (section, option))

        # Read the raw tag data into a byte stream for each tag
        numTags = int(nvm.get("Tag", "Num"))
        tagValues = {}

        for i in range(0, numTags):
            tagSection = "Tag%d" % i
            if not nvm.has_section(tagSection):
                raise TagError("Tag value %d is missing section '%s'" % (i, tagSection))
            for option in ["TagNum", "TagLength", "TagValue" ]:
                if not nvm.has_option(tagSection, option):
                    raise TagError("Section '%s' is missing mandatory field '%s'" % (tagSection, option))

            tagNum = int(nvm.get(tagSection, "TagNum"))
            tagLen = int(nvm.get(tagSection, "TagLength"))
            tagVal = [int(x,16) for x in nvm.get(tagSection, "TagValue").split()]

            # Validate value length
            if tagLen != len(tagVal) and not tag.hasVarArray():
                raise TagError("Section '%s' value length %d doesn't match expected length %d" % (tagSection, len(tagVal), tagLen))

            # Save the byte stream as an array of integers
            tagValues[tagNum] = tagVal

        # Now update the default values for any tags in scope.
        # (We could just update all tags, but that doesn't gain us anything).
        for tag in self.tagScope:
            if self.processTag(tag) and tag.num in tagValues:
                #Used by Save NVMX to save only updated tags, if not used, then it will save remaining tags as well. 
                tag.isUpdated = True

                if config.options.debug:
                    print("  ... merging values into tag %d" % tag.num)

                tagVal = tagValues[tag.num]

                # Consume the new tag value. There should be no data returned after this
                tagVal = tag.mergeNVM(tagVal)
                if len(tagVal) > 0:
                    raise TagError("Tag '%d' didn't consume all tag value - %d bytes remain" % (tag.num, len(tagVal)))
    
    def mergeNVMX(self, nvmx):
        # Read the Format Version
        nvmxVersion = nvmx.find("FORMAT_VERSION")
        self.version = nvmxVersion.text
        
        if self.version not in ['1', '1.0']:
            raise TagError("Unexpected nvmx version: %s" % self.version)
            
        
        # Read the Tags
        nvmxTags = nvmx.find("TAGS")

        nvmxTagList = nvmxTags.findall("TAG")

        for nvmxTag in nvmxTagList:
            isTagFound = None
            
            nvmxTagName = nvmxTag.get("Name")
        
            #Finding the Matching NVMX Tag which matches the Tags that are loaded from Input File
            for tag in self.tagScope:
                if nvmxTagName == tag.name:
                    isTagFound = True
                    break
                
            if not isTagFound:
                if config.options.alignToTCFX:
                #Tag is present in the Merge NVMX file but not in TCFX which means that it needs to be deleted.
                    continue

                raise TagError("NVMX tag %s is not found in the exisiting tags" % nvmxTagName)
            
            #For the tag found, merge the NVMX values
            tag.mergeNVMX(nvmxTag)
            self.tags.append(tag)
            
            #Used by Save NVMX to save only updated tags, if not used, then it will save remaining tags as well. 
            tag.isUpdated = True

            
    ############################################################################
    # Save tag values to an NVM file
    ############################################################################
    def saveNVM(self, outputFile):
        # Open the file for writing, we just write text straight to the file
        # rather than trying to build up the structure in RAM first.
        nvm = open(outputFile, "w")

        # Write the [General] information section, updating the timestamp as we go
        nvm.write("#\n")
        nvm.write("#\n")
        nvm.write("#  NVM Tag Values\n")
        nvm.write("#\n")
        nvm.write("#\n")
        nvm.write("\n")
        nvm.write("[General]\n")
        nvm.write("Signature = windows\n")
        nvm.write("FormatVersion = %s\n" % self.version)
        nvm.write("Timestamp = %s\n" % config.timestamp.strftime("%A %B %d, %Y   %I:%M:%S %p"))
        nvm.write("\n")

        # Count the number of tags to be written in a first pass (required for [Tag] section)
        tagsWritten = 0
        for tag in self.tagScope:
            if self.processTag(tag):
                tagsWritten += 1

        # Write the Tags
        nvm.write("[Tag]\n")
        nvm.write("Num = %u\n" % tagsWritten)
        nvm.write("\n")

        tagFilteredIdx = 0
        for tag in self.tagScope:
            if self.processTag(tag):
                # Temporarily adjust the tag index so that we write a NVM file
                # containing contiguous tag indices
                savedIdx = tag.idx
                tag.idx = tagFilteredIdx
                tagFilteredIdx += 1

                # Write the tag to the nvm file
                tag.saveNVM(nvm)

                # Restore the original tag index. This bit is not strictly needed,
                # as the script will exit after the save, but it's cleaner.
                tag.idx = savedIdx

        nvm.close()


    ############################################################################
    # Read all tag information from an XML tree
    ############################################################################
    def loadXML(self, xml):
        # Read the information section and set defaults for TCF compatibility
        self.sig = "Matunga"
        self.version = xml.get("version")
        self.timestamp = xml.get("timeStamp")

        # Validate version
        if self.version != "1.0":
            raise TagError("Unexpected XML version: %s" % self.version)

        # Read the Tag Groups
        xmlGroups = xml.find("TAG_GROUPS")
        self.tagGroups.loadXML(xmlGroups)

        # Read the Tag Platforms
        xmlPlatforms = xml.find("TAG_PLATFORMS")
        self.tagPlatforms.loadXML(xmlPlatforms)

        # Read the Tags
        xmlTags = xml.find("TAGS")
        self.newTag = int(xmlTags.get("newTag"))

        xmlTagList = xmlTags.findall("TAG")
        relatedTags = {}

        i = 0       # Tag count for TCF compatibility
        for xmlTag in xmlTagList:
            tag = Tag(i)
            i += 1

            tag.loadXML(xmlTag, self.tagGroups)
            self.tags.append(tag)

            if tag.num in self.knownTags:
                # We don't currently support parsing an XML with multiple tags with the same number
                raise TagError("Duplicate tag number %d found in file" % tag.num)
            else:
                # Copy the tag into a known tags dictionary for faster retrieval
                self.knownTags[tag.num] = tag

            if tag.related != "":
                if tag.num not in relatedTags:
                    relatedTags[tag.num] = tag.related
                elif relatedTags[tag.num] != tag.related:
                    raise TagError("Same tag %d has different relations '%s' and '%s'" % (tag.num, relatedTags[tag.num], tag.related) )

            if len(tag.name) > self.maxNameLen:
                self.maxNameLen = len(tag.name)

        # Test to see if all related tags actually exist in the file (this is a minor warning)
        if config.options.verbose:
            for tagNum, tagRelated in relatedTags.items():
                for related in tagRelated:
                    if related not in self.knownTags:
                        print("WARING! Tag %d claims to be related to non-existent tag: %d" % (tagNum, related))


    ############################################################################
    # Read all tag information from an TCFX tree
    ############################################################################
    def loadTCFX(self, tcfx):
        # Read the information section and set defaults for TCF compatibility
        self.sig = "Matunga"
        self.timestamp = tcfx.get("timeStamp")

        # Read the Format Version
        tcfxVersion = tcfx.find("FORMAT_VERSION")
        self.version = tcfxVersion.text
        
        # Validate version
        if self.version != "1.0":
            raise TagError("Unexpected TCFX version: %s" % self.version)

        # Read the Tag Groups
        tcfxGroups = tcfx.find("TAG_GROUPS")
        self.tagGroups.loadTCFX(tcfxGroups)
        
        # Read the Tag Platforms
        tcfxPlatforms = tcfx.find("PLATFORMS")
        self.tagPlatforms.loadTCFX(tcfxPlatforms)

        # Read the Tag Features
        tcfxFeatures = tcfx.find("FEATURES")
        self.tagFeatures.loadTCFX(tcfxFeatures)
        
        # Read the Tags
        tcfxTags = tcfx.find("TAGS")

        tcfxTagList = tcfxTags.findall("TAG")
        relatedTags = {}

        for index,tcfxTag in enumerate(tcfxTagList):
            tag = Tag(index)

            tag.loadTCFX(tcfxTag, self.tagGroups)
            
            self.tags.append(tag)

            # Update highest tag number
            if tag.num > self.newTag:
                self.newTag = tag.num

            if tag.num in self.knownTags:
                # We don't currently support parsing an TCFX with multiple tags with the same number
                raise TagError("Duplicate tag number %d found in file" % tag.num)
            else:
                # Copy the tag into a known tags dictionary for faster retrieval
                self.knownTags[tag.num] = tag

            if tag.related:
                if tag.num not in relatedTags:
                    relatedTags[tag.num] = tag.related
                elif relatedTags[tag.num] != tag.related:
                    raise TagError("Same tag %d has different relations '%s' and '%s'" % (tag.num, relatedTags[tag.num], tag.related) )

            if len(tag.name) > self.maxNameLen:
                self.maxNameLen = len(tag.name)

        # Test to see if all related tags actually exist in the file (this is a minor warning)
        if config.options.verbose:
            for tagNum, tagRelated in relatedTags.items():
                for related in tagRelated:
                    if related not in self.knownTags:
                        print("WARING! Tag %d claims to be related to non-existent tag: %d" % (tagNum, related))
        
    ############################################################################
    # Save all tag information to an XML file
    ############################################################################
    def saveXML(self, outputFile):

        # Construct an XML representation of the tag data we hold in our
        # internal structures.
        tagConfig = ET.Element("TAG_CONFIG")
        tagConfig.set("version", self.version)
        tagConfig.set("timestamp", config.timestamp.strftime("%A %B %d, %Y   %I:%M:%S %p"))

        # Write the Tag Groups
        self.tagGroups.saveXML(tagConfig)

        # Write the Tag Platforms
        self.tagPlatforms.saveXML(tagConfig)

        # Write the Tags
        tagsElem = ET.SubElement(tagConfig, "TAGS")
        tagsElem.set("newTag", str(self.newTag))

        for tag in self.tagScope:
            if self.processTag(tag):
                tag.saveXML(tagsElem)

        # Finally write the XML structure to the given file, with some additional
        # custom formatting to given an easier life to users manually reading the file
        xmlText = xmlToString(tagConfig, config.options.debug)
        xmlText = xmlText.replace(bytearray("</TAG_GROUPS>", 'utf-8'), bytearray("</TAG_GROUPS>\n", 'utf-8'))
        xmlText = xmlText.replace(bytearray("</TAG_PLATFORMS>", 'utf-8'), bytearray("</TAG_PLATFORMS>\n", 'utf-8'))
        xmlText = xmlText.replace(bytearray("</TAG><TAG", 'utf-8'), bytearray("</TAG>\n<TAG", 'utf-8'))

        xmlFile = open(outputFile, "wb")
        xmlFile.write(xmlText)
        xmlFile.close()

    ############################################################################
    # Save all tag information to an TCFX file
    # This function is inherited from saveXML and uses it's functionalities as needed
    ############################################################################
    def saveTCFX(self, outputFile):

        # Construct an XML representation of the tag data we hold in our
        # internal structures.
        TCFX = ET.Element("TCF")
        
        CopyRightBuilder = ET.SubElement ( TCFX, "COPYRIGHT" )
        CopyRightBuilder.text = "Copyright (c) 2019-{0} Qualcomm Technologies, Inc.\n\tAll Rights Reserved.\n\tConfidential and Proprietary - Qualcomm Technologies, Inc.".format(date.today().year)
        
        FormatVersion = ET.SubElement ( TCFX, "FORMAT_VERSION" )
        FormatVersion.text = self.version
        
        # Write the Tag Groups using XML Function
        self.tagGroups.saveTCFX(TCFX)
        
        
        # Write the Tag Platforms
        self.tagPlatforms.saveTCFX(TCFX)
        
        # Write the Feature Flags
        self.tagFeatures.saveTCFX(TCFX)

        tagsElem = ET.SubElement(TCFX, "TAGS")

        for tag in self.tagScope:
            if self.processTag(tag):
                tag.saveTCFX (tagsElem)
        
        # Finally write the TCFX structure to the given file, with some additional
        # custom formatting to given an easier life to users manually reading the file
        TCFXText = xmlToString(TCFX, config.options.debug)
        TCFXText = TCFXText.replace(bytearray("</TAG_GROUPS>", 'utf-8'), bytearray("</TAG_GROUPS>\n", 'utf-8'))
        TCFXText = TCFXText.replace(bytearray("</PLATFORMS>", 'utf-8'), bytearray("</PLATFORMS>\n", 'utf-8'))
        TCFXText = TCFXText.replace(bytearray("</FEATURES>", 'utf-8'), bytearray("</FEATURES>\n", 'utf-8'))
        TCFXText = TCFXText.replace(bytearray("</TAG><TAG", 'utf-8'), bytearray("</TAG>\n<TAG", 'utf-8'))
        TCFXText = TCFXText.replace(bytearray('"/>', 'utf-8'), bytearray('" />', 'utf-8'))

        TCFXfile = open(outputFile, "wb")
        TCFXfile.write(TCFXText)
        TCFXfile.close()
    
    ############################################################################
    # Save all tag information to an NVMX file
    # This function is inherited from saveXML and uses it's functionalities as needed
    ############################################################################
    def saveNVMX(self, outputFile, SaveOnlyUpdatedTags = False):

        # Construct an XML representation of the tag data we hold in our
        # internal structures.
        NVMX = ET.Element("NVM")
        
        FormatVersion = ET.SubElement ( NVMX, "FORMAT_VERSION" )
        FormatVersion.text = self.version

        ChangeSummary = ET.SubElement ( NVMX, "ChangeSummary" )
        
        # Inheriting Change summary from the input file to have only
        # significant difference for the TCFX alignment(s).
        # and Blank If change summary is not present / empty.
        if config.options.alignToTCFX:
            input = ET.parse(outputFile).getroot()
            tmp = input.find("ChangeSummary")
            if tmp is not None and tmp.text:
                ChangeSummary.text = tmp.text

        tagsElem = ET.SubElement(NVMX, "TAGS")

        for tag in self.tagScope:
            if self.processTag(tag):
                #If only updated tags are to be saved
                #This is useful for converting NVM to NVMX
                if SaveOnlyUpdatedTags: 
                    if tag.isUpdated:
                        tag.saveNVMX (tagsElem)
                #If default NVMX is to be saved
                else: 
                    tag.saveNVMX (tagsElem)

        # Finally write the XML structure to the given file, with some additional
        # custom formatting to given an easier life to users manually reading the file
        NVMXText = xmlToString(NVMX, config.options.debug)
        NVMXText = NVMXText.replace(bytearray("<NVM>", 'utf-8'), bytearray('<NVM xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance" xmlns:xsd="http://www.w3.org/2001/XMLSchema">', 'utf-8'))
        NVMXText = NVMXText.replace(bytearray("</TAG>", 'utf-8'), bytearray("</TAG>", 'utf-8'))
        NVMXText = NVMXText.replace(bytearray('/>', 'utf-8'), bytearray(' />', 'utf-8'))
        NVMXText = NVMXText.replace(bytearray("'", 'utf-8'), bytearray('"', 'utf-8'))
        NVMXText = NVMXText.rstrip()

        try:
            NVMXfile = open(outputFile, "wb")
        except:
            raise TagError("No write permissions for the file : {}, please checkout / clear Read only".format(NVMXfile))
        NVMXfile.write(NVMXText)
        NVMXfile.close()
        
    ############################################################################
    # Save all tag information to the system configuration database
    ############################################################################
    def saveSDB(self, sdb):
        # Groups and platforms are not exported to the database
        for tag in self.tagScope:
            if self.processTag(tag):
                tag.saveSDB(sdb)


    ############################################################################
    # Save struct to an VLIST file
    ############################################################################
    def saveVLIST(self, vlist):
        # Loop over tag groups
        for group in self.tagGroups.groups:
            vlist.UpdateGroup(group["name"])
            for tag in self.tags:       # NOTE: Always just the physical tags, not tagScope
                if tag.group == group["name"]:
                    if self.processTag(tag):
                        tag.saveVLIST(vlist)


    ############################################################################
    # Save Tag Type to source files
    ############################################################################
    def generateVtag(self, vtag):
        # Loop over tag groups
        for group in self.tagGroups.groups:
            vtag.UpdateGroup(group["name"])
            for tag in self.vtags:      # NOTE: Always just the vtags, not tagScope
                if tag.group == group["name"]:
                    if self.processTag(tag):
                        tag.saveVtag(vtag)
