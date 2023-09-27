################################################################################
# Tag Platforms processing.
################################################################################
# Copyright (c) 2018-2020 Qualcomm Technologies International, Ltd.
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
from config import TagError
from xml_wrapper import ET


################################################################################
# Global Variables
################################################################################


################################################################################
# Local Functions
################################################################################


################################################################################
# TagPlatforms Class
#
# Holds all information on the defined Tag Platforms.
################################################################################
class TagPlatforms:
    def __init__(self):
        self.numPlatforms = 0
        self.maxNameLen = 0
        self.platforms = []


    ############################################################################
    # Load Tag Platform definitions from the RAM copy of the TCF file
    ############################################################################
    def loadTCF(self, tcf):
        self.numPlatforms = int(tcf.get("TagPlatforms", "Num"))
        for i in range(0, self.numPlatforms):
            platSection = "TagPlatforms%d_Platform" % i
            if not tcf.has_section(platSection):
                raise TagError("TagPlatform %d is missing section '%s'" % (i, platSection))
            if not tcf.has_option(platSection, "Name"):
                raise TagError("TagPlatform '%s' is missing 'Name'" % (platSection))
            if not tcf.has_option(platSection, "Desc"):
                raise TagError("TagPlatform '%s' is missing 'Desc'" % (platSection))

            tagPlat = {}
            tagPlat['idx']   = i
            tagPlat['name']  = tcf.get(platSection, "Name")
            tagPlat['desc']  = tcf.get(platSection, "Desc")
            tagPlat['id']    = int(tcf.get(platSection, "PlatformID"))
            
            #these are only used by the TCF format and support 
            #will be removed when TCF support is removed from parse_tags
            tagPlat['macro'] = tcf.get(platSection, "EnableMacro")
            tagPlat['value'] = tcf.get(platSection, "MacroValue")
            
            self.platforms.append(tagPlat)

            if len(tagPlat['name']) > self.maxNameLen:
                self.maxNameLen = len(tagPlat['name'])


    ############################################################################
    # Save Tag Platform definitions to a TCF file
    ############################################################################
    def saveTCF(self, tcf):
        tcf.write("\n#\n# ------------------------ TagPlatforms Data ------------\n#\n\n")
        tcf.write("[TagPlatforms]\n")
        tcf.write("Num = %u\n" % self.numPlatforms)
        tcf.write("\n")

        for tagPlat in self.platforms:
            # Write the heading
            tcf.write("[TagPlatforms%d_Platform]\n" % tagPlat['idx'])

            # And now write the platform information
            tcf.write("Name = %s\n" % tagPlat['name'])
            tcf.write("PlatformID = %d\n" % tagPlat['id'])
            tcf.write("EnableMacro = %s\n" % tagPlat['macro'])
            tcf.write("MacroValue = %s\n" % tagPlat['value'])
            tcf.write("Desc = %s\n" % tagPlat['desc'])


    ############################################################################
    # Load Tag Platform definitions from an XML tree
    ############################################################################
    def loadXML(self, rootElem):
        xmlPlatformList = rootElem.findall("TAG_PLATFORM")
        self.numPlatforms = len(xmlPlatformList)

        i = 0       # Platform count for TCF compatibility
        for xmlPlat in xmlPlatformList:
            tagPlat = {}
            tagPlat['idx']   = i
            tagPlat['name']  = xmlPlat.get("name")
            tagPlat['desc']  = xmlPlat.text
            tagPlat['id']    = int(xmlPlat.get("id"))
            tagPlat['macro'] = rootElem.get("enableMacro")
            tagPlat['value'] = xmlPlat.get("macroValue")
            self.platforms.append(tagPlat)

            if tagPlat['name'] is None:
                raise TagError("TagPlatform '%d' is missing 'name'" % i)
            if tagPlat['desc'] is None or tagPlat['desc'].strip() == "":
                raise TagError("TagPlatform '%d' is missing description" % i)

            if len(tagPlat['name']) > self.maxNameLen:
                self.maxNameLen = len(tagPlat['name'])

            i += 1

    ############################################################################
    # Load Tag Platform definitions from an TCFX tree
    ############################################################################
    def loadTCFX(self, rootElem):
        tcfxPlatformList = rootElem.findall("PLATFORM")
        self.numPlatforms = len(tcfxPlatformList)

        for index,tcfxPlat in enumerate(tcfxPlatformList):
            tagPlat = {}
            tagPlat['idx']   = index
            tagPlat['name']  = tcfxPlat.get("Name")
            tagPlat['desc']  = tcfxPlat.get("Description").strip()
            tagPlat['id']    = int(tcfxPlat.get("ID"))
            #the macro and value parameters are obsolete, only used by the TCF format. 
            #When we eventually remove TCF support from parse_tags this code can be removed as well.
            tagPlat['macro'] = ''
            tagPlat['value'] = ''
            
            self.platforms.append(tagPlat)

            if tagPlat['name'] is None:
                raise TagError("TagPlatform '%d' is missing 'name'" % index)
            if tagPlat['desc'] is None or tagPlat['desc'].strip() == "":
                raise TagError("TagPlatform '%d' is missing description" % index)

            if len(tagPlat['name']) > self.maxNameLen:
                self.maxNameLen = len(tagPlat['name'])

    ############################################################################
    # Save Tag Platform definitions to an XML tree
    ############################################################################
    def saveXML(self, rootElem):
        tagPlatformsElem = ET.SubElement(rootElem, "TAG_PLATFORMS")
        enableMacro = None

        for tagPlat in self.platforms:
            # Save the enable macro for the first platform, this is expected to
            # be the same for all platforms
            if enableMacro is None:
                enableMacro = tagPlat['macro']

            platElem = ET.SubElement(tagPlatformsElem, "TAG_PLATFORM")
            platElem.set("name", tagPlat['name'])
            platElem.set("id", str(tagPlat['id']))
            platElem.set("macroValue", tagPlat['value'])
            platElem.text = tagPlat['desc']

        if enableMacro is not None:
            tagPlatformsElem.set("enableMacro", enableMacro)

    ############################################################################
    # Save Tag Platform definitions to an TCFX tree
    ############################################################################
    def saveTCFX(self, rootElem):
        tagPlatformsElem = ET.SubElement(rootElem, "PLATFORMS")
        enableMacro = None

        for tagPlat in self.platforms:
            platElem = ET.SubElement(tagPlatformsElem, "PLATFORM")
            platElem.set("Name", tagPlat['name'])
            platElem.set("ID", str(tagPlat['id']))
            platElem.set("Description", tagPlat['desc'])
