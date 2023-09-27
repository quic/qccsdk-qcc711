################################################################################
# Tag Groups processing.
################################################################################
# Copyright (c) 2018-2020 Qualcomm Technologies International, Ltd.
# All Rights Reserved
# Confidential and Proprietary - Qualcomm Technologies International, Ltd.
################################################################################


################################################################################
# Library Imports
################################################################################
from config import TagError
from xml_wrapper import ET


################################################################################
# Global Variables
################################################################################


################################################################################
# Local Functions
################################################################################


################################################################################
# TagGroups Class
#
# Holds all information on the defined Tag Groups.
################################################################################
class TagGroups:
    def __init__(self):
        self.numGroups = 0
        self.maxNameLen = 3     # This is used for debug formatting, min size 3 chars
        self.groups = []


    ############################################################################
    # Get a Tag Group index for a given name
    ############################################################################
    def getIndex(self, name):
        for group in self.groups:
            if group['name'] == name:
                return group['idx']

        raise TagError("Group %s doesn't exist" % name)


    ############################################################################
    # Load Tag Group definitions from the RAM copy of the TCF file
    ############################################################################
    def loadTCF(self, tcf):
        self.numGroups = int(tcf.get("TagGroups", "Num"))
        for i in range(0, self.numGroups):
            groupSection = "TagGroups%d_Group" % i
            if not tcf.has_section(groupSection):
                raise TagError("TagGroup %d is missing section '%s'" % (i, groupSection))
            if not tcf.has_option(groupSection, "Name"):
                raise TagError("TagGroup '%s' is missing 'Name'" % (groupSection))
            if not tcf.has_option(groupSection, "Desc"):
                raise TagError("TagGroup '%s' is missing 'Desc'" % (groupSection))

            tagGroup = {}
            tagGroup['idx']  = i
            tagGroup['name'] = tcf.get(groupSection, "Name")
            tagGroup['desc'] = tcf.get(groupSection, "Desc")
            self.groups.append(tagGroup)

            if len(tagGroup['name']) > self.maxNameLen:
                self.maxNameLen = len(tagGroup['name'])


    ############################################################################
    # Save Tag Group definitions to a TCF file
    ############################################################################
    def saveTCF(self, tcf):
        tcf.write("\n#\n# ------------------------ TagGroups Data ------------\n#\n\n")
        tcf.write("[TagGroups]\n")
        tcf.write("Num = %u\n" % self.numGroups)
        tcf.write("\n")

        for tagGroup in self.groups:
            # Write the heading
            tcf.write("[TagGroups%d_Group]\n" % tagGroup['idx'])

            # And now write the platform information
            tcf.write("Name = %s\n" % tagGroup['name'])
            tcf.write("Desc = %s\n" % tagGroup['desc'])


    ############################################################################
    # Load Tag Group definitions from an XML tree
    ############################################################################
    def loadXML(self, rootElem):
        xmlGroupList = rootElem.findall("TAG_GROUP")
        self.numGroups = len(xmlGroupList)

        i = 0       # Group count for TCF compatibility
        for xmlGroup in xmlGroupList:
            tagGroup = {}
            tagGroup['idx']  = i
            tagGroup['name'] = xmlGroup.get("name")
            tagGroup['desc'] = xmlGroup.text
            self.groups.append(tagGroup)

            if tagGroup['name'] is None:
                raise TagError("TagGroup '%d' is missing 'name'" % i)
            if tagGroup['desc'] is None or tagGroup['desc'].strip() == "":
                raise TagError("TagGroup '%d' is missing description" % i)

            if len(tagGroup['name']) > self.maxNameLen:
                self.maxNameLen = len(tagGroup['name'])

            i += 1

    ############################################################################
    # Load Tag Group definitions from an TCFX tree
    ############################################################################
    def loadTCFX(self, rootElem):
        tcfxGroupList = rootElem.findall("TAG_GROUP")
        self.numGroups = len(tcfxGroupList)

        for index, tcfxGroup in enumerate(tcfxGroupList):
            tagGroup = {}
            tagGroup['idx']  = index
            tagGroup['name'] = tcfxGroup.get("Name")
            tagGroup['desc'] = tcfxGroup.get("Description").strip()
            self.groups.append(tagGroup)

            if tagGroup['name'] is None:
                raise TagError("TagGroup '%d' is missing 'name'" % index)
            if tagGroup['desc'] is None or tagGroup['desc'].strip() == "":
                raise TagError("TagGroup '%d' is missing description" % index)

            if len(tagGroup['name']) > self.maxNameLen:
                self.maxNameLen = len(tagGroup['name'])
            
    ############################################################################
    # Save Tag Group definitions to an XML tree
    ############################################################################
    def saveXML(self, rootElem):
        tagGroupsElem = ET.SubElement(rootElem, "TAG_GROUPS")

        for tagGroup in self.groups:
            groupElem = ET.SubElement(tagGroupsElem, "TAG_GROUP")
            groupElem.set("name", tagGroup['name'])
            groupElem.text = tagGroup['desc']

    ############################################################################
    # Save Tag Group definitions to an TCFX tree
    ############################################################################
    def saveTCFX(self, rootElem):
        tagGroupsElem = ET.SubElement(rootElem, "TAG_GROUPS")

        for tagGroup in self.groups:
            groupElem = ET.SubElement(tagGroupsElem, "TAG_GROUP")
            groupElem.set("Name", tagGroup['name'])
            groupElem.set("Description", tagGroup['desc'])