################################################################################
# C code and documentation generator module.
#
# For a given set of tags etc. it generates the C and H files required by the
# firmware. It also generates HTML file for internal and external use.
################################################################################
# Copyright (c) 2018-2019 Qualcomm Technologies International, Ltd.
# All Rights Reserved
# Confidential and Proprietary - Qualcomm Technologies International, Ltd.
################################################################################


################################################################################
# Library Imports
################################################################################
from __future__ import print_function
import os
import config
from config import TagError
import io
import tag_filter
import tag_descriptor


################################################################################
# Global Variables
################################################################################


################################################################################
# Global Functions
################################################################################


################################################################################
# Class Definitions
################################################################################
class VtagsGenTemplates():
    infoFileIncludes = '''
#include <stddef.h>

#include "prod.h"
#include "pf.h"
#include "pfal_cfg.h"
#include "cfg_tags.h"
#include "cfg_tag_types.h"
#include "cfg_vt.h"
'''
    infoFileTaggroup_bt = '''
#if (CFG_TAGGROUP_BT == INCLUDE_FEATURE)

#include "cfg_bt.h"

'''
    infoFileTaggroup_rm = '''
#if (CFG_TAGGROUP_RM == INCLUDE_FEATURE)

#include "cfg_rm.h"

'''
    infoFileTaggroup_sys = '''
#if (CFG_TAGGROUP_SYS == INCLUDE_FEATURE)

#include "cfg_sys.h"

'''
    infoFileTaggroup_voice = '''
#if (CFG_TAGGROUP_VOICE == INCLUDE_FEATURE)

#include "cfg_voice.h"

'''
    infoFileTaggroup_nulef = '''
#if (CFG_TAGGROUP_NULEF == INCLUDE_FEATURE)

#include "cfg_nulef.h"

'''

    infoFilePatchTaggroup_bt = '''
#if (CFG_TAGGROUP_BT == INCLUDE_FEATURE)

#include "cfg_bt_patch.h"

'''
    infoFilePatchTaggroup_rm = '''
#if (CFG_TAGGROUP_RM == INCLUDE_FEATURE)

#include "cfg_rm_patch.h"

'''
    infoFilePatchTaggroup_sys = '''
#if (CFG_TAGGROUP_SYS == INCLUDE_FEATURE)

#include "cfg_sys_patch.h"

'''
    infoFilePatchTaggroup_voice = '''
#if (CFG_TAGGROUP_VOICE == INCLUDE_FEATURE)

#include "cfg_voice_patch.h"

'''
    infoFilePatchTaggroup_nulef = '''
#if (CFG_TAGGROUP_NULEF == INCLUDE_FEATURE)

#include "cfg_nulef_patch.h"

'''

    tagFilePreamble = '''
typedef signed char        INT8;
typedef signed short       INT16;
typedef signed long        INT32;
typedef signed long long   INT64;
typedef unsigned char      UINT8;
typedef unsigned short     UINT16;
typedef unsigned long      UINT32;
typedef unsigned long long UINT64;
'''


################################################################################
# Generate C source and header files for the vtags.
################################################################################
class VtagsGen():
    # Class variables to define constants.
    CFG_PREFIX = "CFG_"
    CFG_TAG_PREFIX = "CFG_TAG_"

    ############################################################################
    # Given an arbitrary identifier ensure it is syntactically valid C
    ############################################################################
    @staticmethod
    def makeIdent(ident):
        # Replace spaces and dashes with underscores as well
        return ident.replace(" ", "_").replace("-", "_").replace(".", "_")


    ############################################################################
    # Given an arbitrary identifier ensure it is syntactically valid C, and upper case.
    ############################################################################
    @staticmethod
    def makeUpperIdent(ident):
        return VtagsGen.makeIdent(ident).upper()


    ############################################################################
    # Instance initialiser
    ############################################################################
    def __init__(self, nvmTags, outPath):
        self.nvmTags = nvmTags
        self.outpath = outPath
        self.platName = ""

        # C and H files are emitted to separate sub-folders under the output path.
        self.srcPath = outPath + "src/"
        self.incPath = outPath + "inc/"
        
        self.outfile = None
        self.patchoutfile = None
        
        if config.options.patchBaseId is not None:
            self.patchBaseId = int(config.options.patchBaseId)

        self.genUL = False
        self.groups = []
        self.tagGroupFile = {}
        self.vtagGroups = {}
        
    ############################################################################
    # Main entry point to generate C and H code for a given platform
    ############################################################################
    def generateCode(self, platName):
        
        if 1: #not config.options.fileList:
            if not os.path.exists(self.srcPath): os.makedirs(self.srcPath)
#            if not os.path.exists(self.incPath): os.makedirs(self.incPath)

        if config.options.verbose:
            print("===  Generating %s virtual tags files  ===" % platName)

        # There must be at least one lower layer tag to generate code
        if not self.nvmTags.hasLLTags():
            raise TagError("No Lower Layer tags found in tag list")
        
        # Now we can export the various configuration elements (types,
        # descriptions etc.) into the database.
        self.nvmTags.generateVtag(self)
        
    def UpdateGroup(self, groupName):
        
        # Close previously 
        self.closeFile()
        
        if not groupName in ['BT', 'RM', 'SYS', 'Voice', 'NULEF']:
            return
         
        self.group = groupName
        if config.options.buildType == 'ROM':
            outfile = self.createFile('cfg_' + self.group + '_vt_info.c', False)
            sectionName = self.makeUpperIdent(self.group )
        else:
            # We're building the patch, so add ROM in file name
            outfile = self.createFile('cfg_' + self.group + '_rom_vt_info.c', False)
            sectionName = self.makeUpperIdent(self.group ) + '_ROM'

        outfile.write(VtagsGenTemplates.infoFileIncludes)

        if self.group == 'BT':
            outfile.write(VtagsGenTemplates.infoFileTaggroup_bt)
        elif self.group == "RM":
            outfile.write(VtagsGenTemplates.infoFileTaggroup_rm)
        elif self.group == 'SYS':
            outfile.write(VtagsGenTemplates.infoFileTaggroup_sys)
        elif self.group == 'Voice':
            outfile.write(VtagsGenTemplates.infoFileTaggroup_voice)
        elif self.group == 'NULEF':
            outfile.write(VtagsGenTemplates.infoFileTaggroup_nulef)            
        else:
            raise RuntimeError('Unknown group %s' % self.group)
        
        # Update type info and name
        self.structInfo = self.makeUpperIdent("CFG_STRUCT_" + self.group + "_TYPE")
        self.structName =  "CFG_Parameters_" + self.group
        
        outfile.write('__attribute__((section("CFG_STRUCT_' + sectionName + '_TYPE_VT_INFO' + '"))) UINT32 ' + self.group + '_VT_INFO[] = {\n')
        outfile.write('0xDEEDBEAF,\n')
        
        self.outfile = outfile
        
        if config.options.buildType == 'PATCH':
            patchoutfile = self.createFile('cfg_' + self.group + '_patch_vt_info.c', False)
    
            patchoutfile.write(VtagsGenTemplates.infoFileIncludes)
    
            if self.group == 'BT':
                patchoutfile.write(VtagsGenTemplates.infoFilePatchTaggroup_bt)
            elif self.group == "RM":
                patchoutfile.write(VtagsGenTemplates.infoFilePatchTaggroup_rm)
            elif self.group == 'SYS':
                patchoutfile.write(VtagsGenTemplates.infoFilePatchTaggroup_sys)
            elif self.group == 'Voice':
                patchoutfile.write(VtagsGenTemplates.infoFilePatchTaggroup_voice)
            elif self.group == 'NULEF':
                patchoutfile.write(VtagsGenTemplates.infoFilePatchTaggroup_nulef)
            else:
                raise RuntimeError('Unknown group %s' % self.group)
            
            # Update type info and name
            self.patchstructInfo = self.makeUpperIdent("CFG_STRUCT_" + self.group + "_PATCH_TYPE")
            self.patchstructName =  "patch_CFG_Parameters_EXT_" + self.group
            
            patchoutfile.write('__attribute__((section("' + self.patchstructInfo + '_VT_INFO' + '"))) UINT32 ' + self.group + '_PATCH_VT_INFO[] = {\n')
            patchoutfile.write('0xDEEDBEAF,\n')

            self.patchoutfile = patchoutfile
        
    def writeOutFile(self, tagId, typeName, typeString, isTagPatched = False):
        
        outfile = self.outfile
        structInfo = self.structInfo
        structName = self.structName
        # Check if we need to add VTag to VTag Info Table
        if hasattr(self, "patchBaseId"):
            if isTagPatched: 
                # Add VTAG to FW patch tables
                if config.options.verbose:
                    print ("Tag ID %d added to patch tables, not available in ROM image" %tagId)
                outfile = self.patchoutfile
                structInfo = self.patchstructInfo
                structName = self.patchstructName
            
        # Extract data type
        if typeString not in ('UINT8', 'INT8', 'UINT16', 'INT16', 'UINT32', 'INT32'):
            type_info = 'VIRTAG_TYPE_UINT8'
        else:
            type_info = 'VIRTAG_TYPE_' + typeString

        outfile.write("0x%4.4X,\n" % tagId)
        outfile.write("offsetof(%s, %s),\n" % (structInfo, typeName))
        outfile.write("sizeof(%s.%s),\n" %(structName, typeName))
        outfile.write("%s,\n" % type_info)
        
    def closeFile(self):
        
        if self.outfile:
            
            self.outfile.write('0xDEADDEED\n};\n\n#endif\n')
            self.outfile.close()
            
        if self.patchoutfile:
            
            self.patchoutfile.write('0xDEADDEED\n};\n\n#endif\n')
            self.patchoutfile.close()
        
        self.outfile = None
        self.patchoutfile = None

    ############################################################################
    # Create a new file in the output folder. Check that it is writable
    ############################################################################
    def createFile(self, filename, isHeader):
        # Ensure lower case filenames for C and H files
        filename = filename.lower()

        if isHeader:
            filename = self.incPath + filename
        else:
            filename = self.srcPath + filename

        if config.options.fileList:
            print("%s" % filename)
            return None
        elif config.options.verbose:
            print("Generating %s" % filename)

        # If this fails to open we'll just let the IOError exception go up
        return open(filename, "w")


################################################################################
# Export the tag configuration to the Virtual Tag list.
################################################################################
class ExportVLIST():


    ############################################################################
    # Instance initialiser
    ############################################################################
    def __init__(self, nvmTags, outputFileName):
        self.nvmTags = nvmTags
        # Current build file containing new VTAG definitions
        self.outputFileName = outputFileName
        self.groupStr = ""
        
        if config.options.filterVtagList:
            tagFilterFileName = config.options.filterVtagList
        else:
            tagFilterFileName = ""
        
        self.filter = tag_filter.TagFilter(tagFilterFileName)


    ############################################################################
    # Instance destructor
    ############################################################################
    def __del__(self):
        try:
            if self.outputFile is not None:
                self.outputFile.close()
            
        except Exception:
            # Ignore errors at this stage
            pass


    ############################################################################
    # Create new database if non-existent
    ############################################################################
    def Create(self):
        self.outputFile = open(self.outputFileName, "w")
        if tag_descriptor.vListInfo.isVListValid():
            # Assign first free index in VLIST
            tag_descriptor.vListInfo.vtagIndex = tag_descriptor.vListInfo.highestID + 1
        else:
            # Assign base vtag index
            tag_descriptor.vListInfo.vtagIndex = int(config.options.baseId)
        
    def UpdateGroup(self, group):
        #self.groupStr = "Cfg_params_%s_" % group
        self.groupStr = ""


    ############################################################################
    # Create new database if non-existent
    ############################################################################
    def SaveTagInfo(self, vtagRepr, vtagHash, vtagIndex, vtagName = "", isInternal = True):
        
        if not vtagName:
            vtagName = "TAG_%5.5d" % self.vtagIndex
            
        if isInternal:
            internalFlag = 'Int'
        else:
            internalFlag = 'Ext'
                
        outstr = "%5.5d %s %s %s %s%s\n" % (vtagIndex, internalFlag, vtagHash, vtagName, self.groupStr, vtagRepr)
        self.outputFile.write(outstr)
        

    ############################################################################
    # Create new database if non-existent
    ############################################################################
    def Export(self):

        self.enums = {}
        self.structs = {}

        # Now we can export the various configuration elements (types,
        # descriptions etc.) into the database.
        self.nvmTags.saveVLIST(self)

        self.validateTypes()


    ############################################################################
    # Check for duplicate enum definitions. The TCF and XML formats allow this,
    # but as SDB config_elements refer to enum and struct types by name only
    # they have to be unique across the entire set of NVM tags. This is true
    # even if two structs with the same name have different elements (and
    # thus different hashes)
    #
    # TBD: actually the "efficient mapping layer" may minimise this issue, but
    # worth checking anyway
    ############################################################################
    def validateTypes(self):
        dupeFound = False
        for enum,defn in self.enums.items():
            if len(defn) > 1:
                if not dupeFound:
                    dupeFound = True
                    print("\nENUM VALIDATION===============")
                print("%s has %d definitions" % (enum, len(defn)))
                for d in defn:
                    print("  : %3d %s = %s" % (d[0], d[1], d[2]))

        if dupeFound:
            raise TagError("Cannot generate SDB as not all ENUMs are uniquely named")

        dupeFound = False
        for struct,defn in self.structs.items():
            if len(defn) > 1:
                if not dupeFound:
                    dupeFound = True
                    print("\nSTRUCT VALIDATION\n=================")
                print("%s has %d definitions" % (struct, len(defn)))
                for d in defn:
                    print("  : %3d %s = %s" % (d[0], d[1], d[2]))

        if dupeFound:
            raise TagError("Cannot generate SDB as not all STRUCTs are uniquely named")


    ############################################################################
    # Get the combined hash of all element hashes that comprise the subsystem
    ############################################################################
    def getSystemHash(self):
        elementHashes = []

        m = hashlib.md5()
        for d in elementHashes:
            m.update(d)
        return m.hexdigest()
    
