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
import os.path, io
from config import TagError


################################################################################
# Global Variables
################################################################################
def tagFilterInit(filterFileName):
    global filterList
    filterList = TagFilter(filterFileName)
    filterList.parseFilterFile()

################################################################################
# TagFilter Class
#
# Generic class used for tag filtering, i.e. whether if the tag expansion shall
# be ignored or kept in the output list
################################################################################
class TagFilter(object):
    
    filterFile = None
    filterOutExactMatch = []
    filterOutPartialMatch = []
    filterOutChildExactMatch = []
    arrayExpandExactMatch = []
    
    def __init__(self, filterFilename):
        if filterFilename:
            if not os.path.isfile(filterFilename):
                raise TagError("Filter file does not exist")
            
            self.filterFile = open(filterFilename, "r")


    ############################################################################
    # Instance destructor
    ############################################################################
    def __del__(self):
        if self.filterFile:
            self.filterFile.close()
        
    ############################################################################
    # Parse filter file and prepare filtering lists
    ############################################################################
    def parseFilterFile(self):
        
        if not self.filterFile:
            # Nothing to do here
            return
        # Read first line
        strLine = self.filterFile.readline()
        while strLine:
            if strLine[0] == '#':
                if strLine[1] == '*':
                    self.filterOutPartialMatch.append(strLine[2:].rstrip("\n\r"))
                else:
                    self.filterOutExactMatch.append(strLine[1:].rstrip("\n\r"))
            elif strLine[0] == '*':
                self.filterOutChildExactMatch.append(strLine[1:].rstrip("\n\r"))
            elif strLine[0] == '-':
                self.arrayExpandExactMatch.append(strLine[1:].rstrip("\n\r"))
            # else ignore the line and keep going
            strLine = self.filterFile.readline()
        
        
    ############################################################################
    # Check if a virtual tag is in filtered list or not
    ############################################################################
    def vtagEnabled(self, vtagLabel):
        
        if not vtagLabel:
            # Name is empty
            return False
        
        if self.filterFile == None:
            # Always return true as there's no filter file
            return True
        
        if any(vtagLabel == label for label in self.filterOutExactMatch):
            return False
        
        if any(vtagLabel.startswith(label) for label in self.filterOutPartialMatch):
            return False
        
        # Now filter its children
        if any((label in vtagLabel and vtagLabel > label) for label in self.filterOutChildExactMatch):
            return False
        
        return True
    
        
    ############################################################################
    # Check if a struct tag is filtered as top level (i.e. no expansion)
    ############################################################################
    def vtagStructTopLevelProcess(self, vtagLabel):
        
        if not vtagLabel:
            # Name is empty
            return False
        
        if self.filterFile == None:
            # Always return true as there's no filter file
            return True
        if any((label == vtagLabel) for label in self.filterOutChildExactMatch):
            return False
        if any(label in vtagLabel for label in self.filterOutPartialMatch):
            return False
        
        return True
        
        
    ############################################################################
    # Check if a physical tag is enabled or not
    ############################################################################
    def phyTagEnabled(self, vtagLabel):
        
        if not vtagLabel:
            # Name is empty
            return False
        
        if self.filterFile == None:
            # Always return true as there's no filter file
            return True
        if any(label == vtagLabel for label in self.filterOutPartialMatch):
            return False
        
        return True
        
        
    ############################################################################
    # Check if an array tag is to be expanded or not
    ############################################################################
    def tagArrayExpandEnabled(self, vtagLabel):
        
        if not vtagLabel:
            # Name is empty
            return True
        
        if self.filterFile == None:
            # Always return true as there's no filter file
            return False
        if any(label == vtagLabel for label in self.arrayExpandExactMatch):
            return True
        
        return False
        
        
        