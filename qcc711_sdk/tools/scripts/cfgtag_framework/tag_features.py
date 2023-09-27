################################################################################
# Tag Platforms processing.
################################################################################
# Copyright (c) 2020 Qualcomm Technologies International, Ltd.
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
# TagFeatures Class
#
# Holds all information on the defined Tag Features.
################################################################################
class TagFeatures:
    def __init__(self):
        self.numFeatures = 0
        self.maxNameLen = 0
        self.Features = []
        
    ############################################################################
    # Load Tag Feature definitions from an TCFX tree
    ############################################################################
    def loadTCFX(self, rootElem):
        tcfxFeatureList = rootElem.findall("FEATURE")
        self.numFeatures = len(tcfxFeatureList)

        for index, tcfxFeature in enumerate(tcfxFeatureList):
            tagFeature = {}
            tagFeature['idx']   = index
            tagFeature['name']  = tcfxFeature.get("Name")
            tagFeature['desc']  = tcfxFeature.get("Description").strip()
            self.Features.append(tagFeature)
            
            if tagFeature['name'] is None:
                raise TagError("TagFeature '%d' is missing 'name'" % index)
            if tagFeature['desc'] is None or tagFeature['desc'].strip() == "":
                raise TagError("TagFeature '%d' is missing description" % index)

            if len(tagFeature['name']) > self.maxNameLen:
                self.maxNameLen = len(tagFeature['name'])
            
    ############################################################################
    # Save Tag Feature definitions to an TCFX tree
    ############################################################################
    def saveTCFX(self, rootElem):
        TagFeaturesElem = ET.SubElement(rootElem, "FEATURES")
        enableMacro = None

        for tagFeature in self.Features:
            FeatureElem = ET.SubElement(TagFeaturesElem, "FEATURE")
            FeatureElem.set("Name", tagFeature['name'])
            FeatureElem.set("Description", tagFeature['desc'])