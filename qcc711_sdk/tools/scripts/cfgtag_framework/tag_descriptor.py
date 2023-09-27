################################################################################
# Tags processing.
################################################################################
# Copyright (c) 2018-2019 Qualcomm Technologies International, Ltd.
# All Rights Reserved
# Confidential and Proprietary - Qualcomm Technologies International, Ltd.
################################################################################


################################################################################
# Library Imports
################################################################################
try:
    from builtins import str
except ImportError:
    pass
import os.path, hashlib, textwrap
import config
from config import TagError
from codegen import HtfWriteLine
from codegen import CodeGen
################################################################################
# Global Variables
################################################################################
def tagVListOpen(vlistFileName):
    global vListInfo
    vListInfo = TagVListInfo()
    vListInfo.parseVListrFile(vlistFileName)


################################################################################
# Class representing a single Virtual Tag definition from the signature file.
################################################################################
class VListType(object):
    def __init__(self, tagId, md5, tagName, tagExtName, isInternal):
        self.tagId = tagId
        self.md5 = md5
        self.tagName = tagName
        self.tagExtName = tagExtName
        self.isInternal = isInternal
        self.tagObject = None


################################################################################
# Virtual Tag Info Class
#
# Holds information about all defined virtual tags (which may include vtags
# not available in the available physical tag definitions).
################################################################################
class TagVListInfo(object):
    def __init__(self):
        self.vlistValid = False
        self.vlist = {}
        self.highestID = 0
        self.physicalTag = None
        self.vtagIndex = 0


    ############################################################################
    # Parse VList file and prepare list
    ############################################################################
    def parseVListrFile(self, vlistFilename):
        if not vlistFilename:
            return

        # Try to open VLIST and process it
        if not os.path.isfile(vlistFilename):
            raise TagError("VList file not found: %s" % vlistFilename)

        with open(vlistFilename, "r") as vlistFile:
            for line in vlistFile:
                if line[0] == ";":
                    # Skip commented lines
                    continue
                line = line.rstrip("\n\r")
                # Split string between various fields
                strList = line.split(" ")

                if strList[1] == 'Int':
                    isInternal = True
                elif strList[1] == 'Ext':
                    isInternal = False
                else:
                    raise TagError("VLIST format error, unexpected flag: internal")

                vlistObj = VListType(tagId = int(strList[0]),
                                     md5 = strList[2],
                                     tagName = strList[3],
                                     tagExtName = strList[4],
                                     isInternal = isInternal)

                # Add the new item to the vtag dictionary
                if vlistObj.tagExtName in self.vlist:
                    raise TagError("Duplicate VLIST tag extended name: %s" % vlistObj.tagExtName)
                self.vlist[vlistObj.tagExtName] = vlistObj

                # Update the highest vtag ID count
                if self.highestID < vlistObj.tagId:
                    self.highestID = vlistObj.tagId

        self.vlistValid = True


    ############################################################################
    # Search extended name in VTag list
    ############################################################################
    def findTagByName(self, tagExtName):
        if tagExtName in self.vlist:
            return self.vlist[tagExtName]
        return None


    ############################################################################
    # Check if a certain VTag is already defined in VTag list
    ############################################################################
    def isTagDefined(self, name, md5):
        vlistObj = self.findTagByName(name)
        if vlistObj and vlistObj.md5 == md5:
            return True
        return False


    ############################################################################
    # Check if the vtag list is valid
    ############################################################################
    def isVListValid(self):
        return self.vlistValid


################################################################################
# Tag Descriptor.
################################################################################
class TagDescriptor(object):
    def __init__(self):
        self.names = []
        self.values = []
        self.hash = None
        self.elemUid = None     # Used for processing default values
        self.defArrayIdx = None
        self.isVtagPublished = False  # Used to check if VTags are to be exported


    ############################################################################
    # Given an tag name generate a default short name for it
    ############################################################################
    @staticmethod
    def makeShortName(label):
        # Replace spaces and dashes with underscores; convert to lower case
        return label.replace(" ", "_").replace("-", "_").replace(".", "_").lower()


    ############################################################################
    # Extend a descriptor with a copy of another descriptor
    ############################################################################
    def extend(self, other):
        self.names.extend(other.names)
        self.values.extend(other.values)
        self.hash = None    # Invalidate hash


    ############################################################################
    # Add field to database descriptor, converting to string if necessary
    ############################################################################
    def addField(self, name, value):
        # Do not duplicate information
        if name in self.names: #and value in self.values:
            return
        
        # All values are stored as strings
        if type(value) is not str:
            # Convert boolean to integer first
            if type(value) is bool:
                if value: value = 1
                else: value = 0

            value = str(value)

        self.names.append(name)
        self.values.append(str(value))
        self.hash = None    # Invalidate hash


    ############################################################################
    # Add common fields used by every type
    ############################################################################
    def addCommonFields(self, label, progID, typeName, isArray=False):
        self.addField("label", label)
        self.addField("name", progID)   # Could be progID, but not guaranteed to be unique
        self.addField("type", typeName.lower())
        self.addField("is_array", isArray)


    ############################################################################
    # Add external and optional internal tag description
    ############################################################################
    def addDescription(self, desc, internalDesc=None):
        self.addField("description_user", desc)
        if internalDesc is not None:
            self.addField("description_internal", internalDesc)


    ############################################################################
    # Add tag top-level data to the descriptor
    ############################################################################
    def addTagData(self, tagNum, internal=False):
        self.addField("psid", tagNum)
        self.addField("is_internal", internal)


    ############################################################################
    # Add fields for integer or array range (array range is number of elements allowed)
    ############################################################################
    def addRange(self, minimum, maximum, isArray=False):
        if isArray:
            self.addField("array_length_min", minimum)
            self.addField("array_length_max", maximum)
        else:
            self.addField("range_min", minimum)
            self.addField("range_max", maximum)


    ############################################################################
    # Add fields used to store a ROM default value
    ############################################################################
    def addDefault(self, elemUid, defaultVal):
        self.addField("elem_uid", elemUid)
        if defaultVal is not None:
            if type(defaultVal) is str:
                # Is it an array? We treat this as a pseudo-column for hashing only
                if defaultVal.find(",") > -1:
                    if self.defArrayIdx is None:
                        self.defArrayIdx = len(self.names)
                        self.addField("default_array", defaultVal)
                    else:
                        raise TagError("Internal error - multiple array defaults")
                else:
                    self.addField("value_string", defaultVal)

            else:
                self.addField("value_int", defaultVal)
        self.elemUid = elemUid


    ############################################################################
    # Get a unified list of parts that describe this type, to be fed into a
    # hashing algorithm. Depending on the context, an extended hash or short
    # hash can be selected, i.e. a long hash can be used to uniquely identify a
    # tag in the tag database and a short hash can be used to uniquely identify
    # the scope of a tag for VTags. The caller may provide a prefix if required
    ############################################################################
    def getHashParts(self, shortHash=False, hashParts=None):
        hashParts = hashParts or []
        allowedParams = ["name", "label", "type", "is_array", "psid", "is_internal"]
        for name,val in zip(self.names, self.values):
            if name in allowedParams or shortHash==False:
                hashParts.extend( [name, val] )
        return hashParts


    ############################################################################
    # Generate an MD5 hash of the Tag descriptor. Use short hash to identify
    # tags in VTag list and long hash to identify tags in tag database
    ############################################################################
    def getHash(self, shortHash=False, hashParts=None, debug=False):
        hashParts = hashParts or []

        if self.hash is None:
            hashParts = self.getHashParts(shortHash, hashParts)
            m = hashlib.md5()
            if type(hashParts) == list:
                for d in hashParts:
                    #if debug: print "HASH: ", d
                    m.update(d.encode('utf-8'))
            else:
                m.update(hashParts)
            self.hash = m.hexdigest()

        return self.hash


    ############################################################################
    # Get the type name as a string
    ############################################################################
    def getTypeString(self, lowercase=True, baseNameOnly=False, prefixParent=False):
        # Bitfields need the parent name prefixed as well
        typeStr = ""
        if not baseNameOnly and prefixParent and self.parent is not None:
            typeStr = self.parent.name + "_"
        typeStr += self.name

        # Replace spaces and dashes with underscores
        typeStr = typeStr.replace(" ", "_").replace("-", "_").replace(".", "_")

        # Optionally suffix _t and/or convert to lower case
        if not baseNameOnly:
            typeStr += "_t"
        if lowercase:
            typeStr = typeStr.lower()

        return typeStr


    ############################################################################
    # Get the C struct name as a string
    ############################################################################
    def getStructString(self):
        # Replace spaces and dashes with underscores;
        return "Cfg_" + self.name.replace(" ", "_").replace("-", "_").replace(".", "_")


    ############################################################################
    # Get the extended type name as a string, including the parent's name
    ############################################################################
    def getTypeStringRecursive(self):
        # Replace spaces and dashes with underscores; convert to lower case
        if self.parent is not None:
            tag_name = self.parent.getTypeStringRecursive()
            if tag_name is not "":
                tag_name += "."
            tag_name += self.getTypeString(baseNameOnly=True)
            return tag_name
        else:
            return self.getTypeString(baseNameOnly=True)


    ############################################################################
    # Get the extended C struct name as a string, including parent
    ############################################################################
    def getStructStringRecursive(self):
        from tagtype import TagTypeArray
        # Replace spaces and dashes with underscores; convert to lower case
        if self.parent is not None:
            tag_name = self.parent.getStructStringRecursive()
            if isinstance(self.parent, TagTypeArray):
                # Skip object name if this is an element of the array
                idx = self.parent.elems.index(self)
                tag_name += "[%s]" % idx
            else:
                if tag_name is not "":
                    tag_name += "."
                tag_name += self.getStructString()
            return tag_name
        else:
            return self.getStructString()


    ############################################################################
    # Check if top level tag is internal
    ############################################################################
    def isTagInternal(self):
        if self.parent is not None:
            return self.parent.isTagInternal()
        else:
            return self.internal


    ############################################################################
    # Check if one particular element is a table element and return index
    ############################################################################
    def readTableElementIdx(self):
        from tagtype import TagTypeArray    # Circular definition so localise to this function
        if self.parent is not None:
            if type(self.parent) == TagTypeArray:
                # This is an element of the array. Return index
                nameList = self.name.split('_')
                return nameList[-1]
            else:
                return self.parent.readTableElementIdx()
        else:
            return None


    ############################################################################
    # Get the string to be used as tag name
    ############################################################################
    def getTagName(self):
        name = self.getTypeStringRecursive()
        # Get the first and the last part of the expanded name
        if '.' in name:
            strSplit = name.split('.')
            retString = strSplit[0].upper() + '_' + strSplit[-1].upper()
            return retString
        else:
            return name.upper()


    ############################################################################
    # Extract vtag definitions from this tag type if possible
    #
    # The function handles "leaf" tag types and also those that contain
    # child tag types. Child types are not allowed to define a virtual tag if
    # a vtag is defined for the current type.
    ############################################################################
    def extractVtags(self, physTag, vtags):
        from tagtype import TagTypeArray
        from tagtype_struct import TagTypeStruct

        # Check for a vtag definition for the current type first
        vtagCreated = physTag.loadVtag(self, vtags)

        if isinstance(self, TagTypeArray) or isinstance(self, TagTypeStruct):
            # Iterate through child nodes as well for recursive types
            childVtagCreated = False

            if isinstance(self, TagTypeArray):
                nodes = self.elems
            else:
                nodes = self.fields

            for node in nodes:
                if node.extractVtags(physTag, vtags):
                    childVtagCreated = True

                # We don't allow complex structs that are vtags to have nested vtags
                # as it would allow the same information to be written from multiple
                # vtags which could confuse customers
                #
                if vtagCreated and childVtagCreated:
                    raise TagError("Nested vtags detected under: %s" % self.name)

            if childVtagCreated:
                # Propagate vtag created status up to parent
                vtagCreated = True

        return vtagCreated


    ############################################################################
    # Export tag to VT info file
    ############################################################################
    def saveVtag(self, vtag):
        extentedName = self.getTypeStringRecursive()
        vlistObj = vListInfo.findTagByName(extentedName)
        if vlistObj and (config.options.buildType == 'ROM' or vlistObj.tagId > config.options.patchBaseId):
            vtag.writeOutFile(vlistObj.tagId, self.getStructStringRecursive(), self.type.getTypeString(), vlistObj.physicalTag.isPatched)


    ############################################################################
    # Get the maximum size of the tag, in bytes
    ############################################################################
    def getMaxLength(self):
        return self.type.size


    ############################################################################
    # Get VTag name as read from the VTag list
    ############################################################################
    def getVtagName(self):
        if self.vListObj:
            tagName = self.vListObj.tagName
        else:
            tagName = self.getTagName()
            elemIdx = self.readTableElementIdx()
            if elemIdx:
                tagName = tagName + "_" + elemIdx 
        return tagName


    ############################################################################
    # Get VTag number as read from the VTag list
    ############################################################################
    def getVtagNumber(self):
        
        if self.vListObj:
            tagId = self.vListObj.tagId
        else:
            tagId = vListInfo.vtagIndex
            vListInfo.vtagIndex += 1
            
        return tagId
    
    ############################################################################
    # Get the type alignment requirement, in bytes
    ############################################################################
    def getAlignment(self):
        # The trivial case for integer types (int/bits/enum) is just the size
        # of the type, since it is 1/2/4 bytes. This function is overridden by
        # the array and struct types.
		
        return self.getMaxLength()
