################################################################################
# C code and documentation generator module.
#
# For a given set of tags etc. it generates the C and H files required by the
# firmware. It also generates HTML file for internal and external use.
################################################################################
# Copyright (c) 2018-2019, 2022 Qualcomm Technologies International, Ltd.
# All Rights Reserved
# Confidential and Proprietary - Qualcomm Technologies International, Ltd.
################################################################################


################################################################################
# Library Imports
################################################################################
from __future__ import print_function
import os
from codegen_templates import CodeGenTemplates
import config
from config import TagError
import tag_descriptor


################################################################################
# Global Variables
################################################################################


################################################################################
# Global Functions
################################################################################

################################################################################
# Write a single line to an HTF file for a tag value.
#
# Optionally write line-continuation character and indent the string by a set amount.
def HtfWriteLine(htf, str, indent=0, cont=True):
    if not config.options.compactHTF:
        str = " "*indent + str.expandtabs(8)
        if cont:
            if len(str) < 100:
                padLen = 100 - len(str)
                str += " "*padLen
            else:
                str += "\t\t"
            str += "\\"
        str += "\n"
        str = str.expandtabs(8)

    htf.write(str)



################################################################################
# Class Definitions
################################################################################

################################################################################
# Generate C source and header files for the tags.
#
# TagCfg.exe seems to have support for generating files for multiple platforms
# at once, but doesn't seem to emit platform-specific source filenames.
# Either way we don't use it that way anyway, and here we particularly only
# need to emit files for one platform, given the internal parser state.
#
# There is a possible future requirement to fully utilise the tag-platform
# relationships, to allow a single XML file to hold tag data for all targets.
# In that case the selected chip/platform will be used to filter.
#
# This function doesn't generate the HTML files - that will be handled as a
# separate output file type.
################################################################################
class CodeGen():
    # Class variables to define constants.
    CFG_PREFIX = "CFG_"
    CFG_TAG_PREFIX = "CFG_TAG_"

    ############################################################################
    # Check if a given type name has previously been generated, and is the same if so
    ############################################################################
    @staticmethod
    def checkUnique(generatedTypes, typeName, otherType):
        if typeName in generatedTypes:
            # Compare the two types. This uses class-specific equality tests to
            # allow more fine-grained control of the test, e.g. it will allow
            # two enum types with the same name and enum values, that differ
            # only in the default value.
            #
            if otherType == generatedTypes[typeName]:
                # We've previously generated this type so just silently return now
                if config.options.debug: print("Same type found (skipping): %s" % typeName)
                return False

            raise TagError("Differing type definitions found for %s" % typeName)
        else:
            generatedTypes[typeName] = otherType

        return True


    ############################################################################
    # Pad an identifier string to the right with spaces.
    #
    # padIdent      pads to a minimum width of 50 characters.
    # padIdentMid   pads to a minimum width of 20 characters.
    # padIdentShort pads to a minimum width of 10 characters.
    ############################################################################
    @staticmethod
    def padTo(ident, minWidth):
        ident = ident.ljust(minWidth)

        # Protect against super-long identifiers that blow past this column limit
        if ident[-1:] != " ": ident += " "

        return ident

    @staticmethod
    def padIdent(ident):
        return CodeGen.padTo(ident, 50)

    @staticmethod
    def padIdentMid(ident):
        return CodeGen.padTo(ident, 20)

    @staticmethod
    def padIdentShort(ident):
        return CodeGen.padTo(ident, 10)


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
        return CodeGen.makeIdent(ident).upper()


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

        self.genUL = False

        self.oneSpace = self.twoSpace = self.threeSpace = ""
        if config.options.compat:
            self.oneSpace = " "
            self.twoSpace = "  "
            self.threeSpace = "   "


    ############################################################################
    # Main entry point to generate C and H code for a given platform
    ############################################################################
    def generateCode(self, platName):
        # For now we only expect a single platform to be defined
        if self.nvmTags.tagPlatforms.numPlatforms != 1:
            raise TagError("Expected 1 Tag Platform, got %d" % self.nvmTags.tagPlatforms.numPlatforms)
        self.platName = platName

        if 1: #not config.options.fileList:
            if not os.path.exists(self.srcPath): os.makedirs(self.srcPath)
            if not os.path.exists(self.incPath): os.makedirs(self.incPath)

        if config.options.verbose:
            print("===  Generating %s source files  ===" % platName)

        # There must be at least one lower layer tag to generate code
        if not self.nvmTags.hasLLTags():
            raise TagError("No Lower Layer tags found in tag list")

        # Generate each of the files in turn. Any internal errors will result in
        # an exception being thrown and the generation aborted.
        self.genLLTagListH()
        self.genLLTagDataTypesH()
        self.genLLConfigH()
        if config.options.buildType == "ROM":
            self.genLLConfigC()
        self.genGroupsH(False, True)
        if config.options.buildType == "ROM":
            self.genGroupsC(False, True)
        elif config.options.buildType == "PATCH":
            self.genGroupsH(False, False)
            self.genGroupsC(False, False)

        # Currently we don't support upper layer tag generation (there aren't
        # any UL tags in the TCF files today). If we did it would look something
        # like this:
        if self.genUL and self.nvmTags.checkHigherLayerTags():
            self.genULTagListH()
            self.genULTagDataTypesH()
            self.genULConfigH()
            self.genULConfigC()
            self.genGroupsH(True)
            self.genGroupsC(True)


    ############################################################################
    # Main entry point to generate HTML documentation for a given platform
    ############################################################################
    def generateHTML(self, platName):
        if self.nvmTags.tagPlatforms.numPlatforms != 1:
            raise TagError("Expected 1 Tag Platform, got %d" % self.nvmTags.tagPlatforms.numPlatforms)
        self.platName = platName

        if not config.options.fileList:
            if not os.path.exists(self.outpath): os.makedirs(self.outpath)

        if config.options.verbose:
            print("===  Generating %s HTML documentation  ===" % platName)

        # There must be at least one lower layer tag to generate HTML
        if not self.nvmTags.hasLLTags():
            raise TagError("No Lower Layer tags found in tag list")

        # Generate internal and external HTML documentation
        self.genInternalUsersFile()
        self.genExternalUsersFile()


    ############################################################################
    # Generate Lower Layer tag list header file cfg_tags.h
    ############################################################################
    def genLLTagListH(self):
        from tags import NvmTags

        tagListFile = CodeGen.CFG_PREFIX.lower() + "tags.h"
        self.file = self.createFile(tagListFile, True)
        if self.file is None:
            if config.options.fileList:
                return
            else:
                raise TagError("Unable to create file: %s" % tagListFile)
        
        self.writeFileHeader(tagListFile, " *     This file contains a list of all the tags\n")
        self.writeHeaderProt(tagListFile)

        self.file.write('#include "prod_defs.h"\n')
        
        self.file.write("\n/* Define if this is a patch build and VTags are supported for this platform */\n")
        if config.options.buildType == "ROM" or config.options.scope == "physical":
            strFeature = "NOT_INCLUDE_FEATURE"
        elif config.options.buildType == "PATCH":
            strFeature = "INCLUDE_FEATURE"
        else:
            raise TagError("Build type not recognised %s" % config.options.buildType)
        
        self.file.write("#define   %s%s\n" % (CodeGen.padIdent("CFG_PATCH_BUILD_VTAG_SUPPORT"), strFeature.ljust(10)))
        
        self.file.write("\n/* Tag Defines */\n")

        # Write some generic #define's first
        self.file.write("#define   %s%s/* Unused Tag Number */\n" %  (CodeGen.padIdent(CodeGen.CFG_PREFIX + "NVM_TAG_UNUSED"), "(0xFF)".ljust(10)))
        self.file.write("#define   %s%s/* Invalid Tag Length */\n" % (CodeGen.padIdent(CodeGen.CFG_PREFIX + "NVM_UNUSED_LENGTH_VALUE"), "(0xFF)".ljust(10)))
        self.file.write("\n/* Tag List */\n")

        lastTag = 1
        self.file.write("#define   %s%s/*   %d   */\n" % (CodeGen.padIdent(CodeGen.CFG_TAG_PREFIX + "NVM_SIGNATURE"), ("(0x%02X)"%lastTag).ljust(10), lastTag))

        for tag in self.nvmTags.tags:
            # TagCfg.exe checks for Duplicate!=0 or Obsolete!=0 here, but today no tags have this
            if tag.num < lastTag:
                print("WARNING! Unsorted tag list at tag %d (previous tag was %d)" % (tag.num, lastTag))
                continue
            # Don't process upper layer tags
            if tag.num > NvmTags.MAX_LL_TAGS:
                continue

            lastTag = tag.num

            # Prefix the Tag Group to the tag name to get the C definition
            tagNameH = CodeGen.padIdent(self.makeUpperIdent(CodeGen.CFG_TAG_PREFIX + tag.group + "_" + tag.name))
            self.file.write("#define   %s%s/*   %d   */\n" % (tagNameH, ("(0x%02X)"%lastTag).ljust(10), lastTag))

        # Write the last tag number to finish off the file
        self.file.write("#define   %s%s/*   %d   */\n" % (CodeGen.padIdent("CFG_NVM_MAX_TAG_VALUE"), ("(0x%02X)"%lastTag).ljust(10), lastTag))
        self.file.write("\n\n")

        self.file.write("\n#endif /* } #ifndef %s*/\n" % self.hdrProt)

        # Close the file when we've finished
        self.file.close()
        self.file = None


    ############################################################################
    # Generate Lower Layer tag data types header file cfg_tag_types.h
    ############################################################################
    def genLLTagDataTypesH(self):
        from tags import NvmTags

        tagTypesFile = CodeGen.CFG_PREFIX.lower() + "tag_types.h"
        self.file = self.createFile(tagTypesFile, True)
        if self.file is None:
            if config.options.fileList:
                return
            else:
                raise TagError("Unable to create file: %s" % tagListFile)

        self.writeFileHeader(tagTypesFile)
        self.file.write('#include "pfal_types.h"\n\n')
        self.writeHeaderProt(tagTypesFile)

        generatedTypes = {}
        lastTag = 1
        for tag in self.nvmTags.tags:
            if not tag.genCode() or tag.num > NvmTags.MAX_LL_TAGS or tag.dynMem:
                # Don't generate code for this tag
                continue

            # There was a whole bunch of code here related to platform-specific tags(??)
            # that is not currently implemented. For now we just assume all tags go in order
            self.file.write("\n/* DataTypes for Tag : %u : %s */\n" % (tag.num, tag.name))
            tag.genTagDataTypes(self.file, generatedTypes)

            lastTag = tag.num

        self.file.write("\n\n")
        self.file.write("\n#endif /* } #ifndef %s*/\n" % self.hdrProt)

        # Close the file when we've finished
        self.file.close()
        self.file = None


    ############################################################################
    # Generate Lower Layer config header file
    ############################################################################
    def genLLConfigH(self):
        configH = "cfg.h"
        tagTypesFile = CodeGen.CFG_PREFIX.lower() + "tag_types.h"
        tagsFile = CodeGen.CFG_PREFIX.lower() + "tags.h"

        self.file = self.createFile(configH, True)
        if self.file is None:
            if config.options.fileList:
                return
            else:
                raise TagError("Unable to create file: %s" % tagListFile)

        self.writeFileHeader(configH, " *     This file contains a list of all the tags\n")
        self.writeHeaderProt(configH)
        self.file.write('#include "bt_features.h"\n')

        for group in self.nvmTags.tagGroups.groups:
            if not self.nvmTags.genSourceForGroup(group['name'], True):
                continue
            define = CodeGen.makeUpperIdent("CFG_TAGGROUP_" + group['name'])
            self.file.write("#ifndef    %s\n" % define)
            self.file.write("#define    %s      NOT_INCLUDE_FEATURE\n" % define)
            self.file.write("#endif\n")

        self.file.write("\n")
        self.file.write("#include \"%s\"\n" % tagsFile)
        self.file.write("#include \"%s\"\n" % tagTypesFile)

        for group in self.nvmTags.tagGroups.groups:
            if not self.nvmTags.genSourceForGroup(group['name'], True):
                continue
            define = CodeGen.makeUpperIdent("CFG_TAGGROUP_" + group['name'])
            self.file.write("#if (%s == INCLUDE_FEATURE)\n" % define)
            self.file.write("#include \"%s\"\n" % (CodeGen.CFG_PREFIX + group['name'] + ".h").lower())
            self.file.write("#if CFG_PATCH_BUILD_VTAG_SUPPORT == INCLUDE_FEATURE\n")
            self.file.write("#include \"%s\"\n" % (CodeGen.CFG_PREFIX + group['name'] + "_patch.h").lower())
            self.file.write("#endif /* CFG_PATCH_BUILD_VTAG_SUPPORT == INCLUDE_FEATURE */\n")
            self.file.write("#endif\n")

        self.file.write(CodeGenTemplates.configHFuncHdr.format(oneSpace=self.oneSpace))

        # Also write the function prototype for CFG_Relocate if needed.
        if config.options.relocatable:
            self.file.write(CodeGenTemplates.configHRelocateFuncProto)

        self.file.write("\n#endif /* } #ifndef %s*/\n" % self.hdrProt)

        # Close the file when we've finished
        self.file.close()
        self.file = None


    ############################################################################
    # Generate Lower Layer config source file
    ############################################################################
    def genLLConfigC(self):
        configC = "cfg.c"

        self.file = self.createFile(configC, False)
        if self.file is None:
            if config.options.fileList:
                return
            else:
                raise TagError("Unable to create file: %s" % tagListFile)

        if config.options.compat:
            configC = "CFG.c"
        self.writeFileHeader(configC, " *     This file contains a list of all the tags\n")
        self.file.write('#include "pf.h"\n')
        self.file.write('#include "cfg.h"\n')
        self.file.write('#include "pfal_cfg.h"\n')

        if config.options.relocatable:
            self.file.write('#include "pfal_rm_modem.h"\n')

        self.file.write('\n')

        # Generate the function pointers and the pointer setting functions
        self.file.write(CodeGenTemplates.configCFuncPtr)

        if config.options.relocatable:
            self.file.write(CodeGenTemplates.configCRelocVars)

        self.file.write(CodeGenTemplates.configCFuncs)

        # Keep all the local variables together
        if config.options.relocatable:
            self.file.write('    void *Address;\n')
            self.file.write('    UINT32 Length;\n\n')

        self.file.write("    PF_OS_Init_NVM();\n\n")

        self.file.write("    /* Copy the default configuration values into the parameter structure */\n")
        for group in self.nvmTags.tagGroups.groups:
            if not self.nvmTags.genSourceForGroup(group['name'], True):
                continue
            define = CodeGen.makeUpperIdent("CFG_TAGGROUP_" + group['name'])
            self.file.write("#if (%s == INCLUDE_FEATURE)\n" % define)
            self.file.write("    CFG_%s_Init();\n" % group['name'])
            self.file.write("#endif\n")

        relocate_code = ''

        if config.options.relocatable:
            self.file.write(CodeGenTemplates.CFG_InitCallInitialize.format(oneSpace=self.oneSpace))

            relocate_code += '\n'
            relocate_code += '    if((CFG_RelocateAddr != NULL) && (CFG_RelocateLength > 0))\n'
            relocate_code += '    {\n'
            relocate_code += '        Address = CFG_RelocateAddr;\n'
            relocate_code += '        Length = CFG_RelocateLength;\n\n'
            for group in self.nvmTags.tagGroups.groups:
                if not self.nvmTags.genSourceForGroup(group['name'], True):
                    continue
                define = CodeGen.makeUpperIdent("CFG_TAGGROUP_" + group['name'])
                relocate_code += '#if (%s == INCLUDE_FEATURE)\n' % define
                relocate_code += '        if(ReturnValue)\n'
                relocate_code += '        {\n'
                relocate_code += '            ReturnValue = CFG_{}_Relocate( &Address, &Length );\n'.format(group['name'])
                relocate_code += '        }\n'
                relocate_code += '#endif\n'
            relocate_code += '    }\n'

        self.file.write(CodeGenTemplates.configCInitBody.format(oneSpace=self.oneSpace, relocate=relocate_code))

        if config.options.relocatable:
            self.file.write("\n")

            self.file.write(CodeGenTemplates.configRelocateFunc.format(oneSpace=self.oneSpace))

            self.file.write('    CFG_RelocateAddr = Address;\n')
            self.file.write('    CFG_RelocateLength = Length;\n')


            self.file.write("\n")
            self.file.write("    return (SiW_TRUE);\n")
            self.file.write("}\n")

        self.file.write("\n")

        self.file.write(CodeGenTemplates.configGetConfigParaInfoHeader.format(oneSpace=self.oneSpace))

        for group in self.nvmTags.tagGroups.groups:
            if not self.nvmTags.genSourceForGroup(group['name'], True):
                continue
            define = CodeGen.makeUpperIdent("CFG_TAGGROUP_" + group['name'])
            self.file.write("#if (%s == INCLUDE_FEATURE)\n" % define)
            self.file.write("    if( CFG_%s_GetConfigParameterInfo(pNvmEntry) )\n" % group['name'])
            self.file.write("    {\n")
            self.file.write("        return SiW_TRUE;\n")
            self.file.write("    }\n")
            self.file.write("#endif\n")

        self.file.write(CodeGenTemplates.configChandleVarConfig.format(oneSpace=self.oneSpace))

        for group in self.nvmTags.tagGroups.groups:
            if not self.nvmTags.genSourceForGroup(group['name'], True):
                continue
            define = CodeGen.makeUpperIdent("CFG_TAGGROUP_" + group['name'])
            self.file.write("#if (%s == INCLUDE_FEATURE)\n" % define)
            self.file.write("    if( CFG_%s_HandleVariableConfigParameter(pNvmEntry) )\n" % group['name'])
            self.file.write("    {\n")
            self.file.write("        return SiW_TRUE;\n")
            self.file.write("    }\n")
            self.file.write("#endif\n")

        self.file.write(CodeGenTemplates.configCGetTagEntry)

        for group in self.nvmTags.tagGroups.groups:
            if not self.nvmTags.genSourceForGroup(group['name'], True):
                continue
            define = CodeGen.makeUpperIdent("CFG_TAGGROUP_" + group['name'])
            self.file.write("#if (%s == INCLUDE_FEATURE)\n" % define)
            self.file.write("    if( CFG_%s_GetTagEntry(Tag, Length) )\n" % group['name'])
            self.file.write("    {\n")
            self.file.write("        return SiW_TRUE;\n")
            self.file.write("    }\n")
            self.file.write("#endif\n")

        self.file.write(CodeGenTemplates.configCWriteDyn.format(oneSpace=self.oneSpace))

        for group in self.nvmTags.tagGroups.groups:
            if not self.nvmTags.genSourceForGroup(group['name'], True):
                continue
            define = CodeGen.makeUpperIdent("CFG_TAGGROUP_" + group['name'])
            self.file.write("#if (%s == INCLUDE_FEATURE)\n" % define)
            self.file.write("    CFG_%s_WriteDynamicConfigParameters();\n" % group['name'])
            self.file.write("#endif\n")

        self.file.write(CodeGenTemplates.configCEnd)

        # Close the file when we've finished
        self.file.close()
        self.file = None


    ############################################################################
    # Generate tag groups header file
    ############################################################################
    def genGroupsH(self, genUL, romCode):
        if genUL:
            raise TagError("Upper Layer code generation not implemented yet")

        tagTypesFile = CodeGen.CFG_PREFIX.lower() + "tag_types.h"
        
        if romCode:
            patchStr = ""
        else:
            patchStr = "patch_"

        # Iterate through each group in turn, generating group-specific header files
        for group in self.nvmTags.tagGroups.groups:
            if not self.nvmTags.genSourceForGroup(group['name'], not genUL):
                continue
            
            # Check if this is a patch build
            if romCode:
                groupsH = (CodeGen.CFG_PREFIX + group['name'] + ".h").lower()
            else:
                groupsH = (CodeGen.CFG_PREFIX + group['name'] + "_patch.h").lower()

            self.file = self.createFile(groupsH, True)
            if self.file is None:
                if config.options.fileList:
                    # Just loop around to the next file after we've derived the filename
                    continue
                else:
                    raise TagError("Unable to create file: %s" % groupsH)

            if config.options.compat:
                # Filenames displayed in files are not case-corrected
                groupsH = CodeGen.CFG_PREFIX + group['name'] + ".h"

            self.writeFileHeader(groupsH, " *     This file contains a list of all the tags\n")
            self.writeHeaderProt(groupsH)
            self.file.write('#include "bt_features.h"\n')
            self.file.write('#include "pfal_types.h"\n\n')

            define = CodeGen.makeUpperIdent("CFG_TAGGROUP_" + group['name'])
            self.file.write("#if (%s == INCLUDE_FEATURE)\n\n" % define)
            self.file.write("#include  \"%s\"\n" % tagTypesFile)
            self.file.write('#include  "pfal_cfg.h"\n')
            
            # Check if this is a patch build
            if not romCode:
                # Include ROM related definitions
                self.file.write("#include \"%s\"\n" % (CodeGen.CFG_PREFIX + group['name'] + ".h").lower())

            # NOTE: Code generation for RAM-less tags is not currently supported.
            hasDynMemTags = False
            for tag in self.nvmTags.tags:
                if group['name']!=tag.group or not tag.genCode():
                    continue
                # Check if this is a patch build
                if romCode:
                    if config.options.buildType == "PATCH" and tag.isPatched:
                        # Do not add tag here
                        continue
                else:
                    if not tag.isPatched:
                        # Only add patched tags here
                        continue

                if tag.dynMem:
                    hasDynMemTags = True

            ####################################################################
            # Process each tag in the group to go into static RAM
            ####################################################################
            hasStaticRAM = False
            indent = 4
            groupStructName = self.makeUpperIdent("CFG_STRUCT_" + group['name'] + "_" + patchStr + "TYPE")

            for tag in self.nvmTags.tags:
                if group['name']!=tag.group or not tag.genCode() or tag.dynMem:
                    continue
                # Check if this is a patch build
                if romCode:
                    if config.options.buildType == "PATCH" and tag.isPatched:
                        # Do not add tag here
                        continue
                else:
                    if not tag.isPatched:
                        # Only add patched tags here
                        continue

                # Print section header for first tag
                if not hasStaticRAM:
                    hasStaticRAM = True
                    self.file.write("\n/* Structure containing the tags that belong to the group : %s with static RAM */\n" % tag.group)
                    self.file.write("typedef struct \n{")

                self.file.write("\n")
                self.file.write("\n%s/* Tag : %u : %s */\n" % (" "*indent, tag.num, tag.name))
                tag.typeInfo.genTagElement(self.file, indent)

            # These names are used for the structure trailing info and also later for generating the reference macros
            if romCode:
                defaultsStructName = "CFG_Defaults_" + group['name']
                paramsStructName = "CFG_Parameters_" + group['name']
            else:
                defaultsStructName = "patch_CFG_Defaults_EXT_" + group['name']
                paramsStructName = "patch_CFG_Parameters_EXT_" + group['name']

            # Write structure trailing information
            if hasStaticRAM:
                self.file.write("\n} %s;\n\n" % groupStructName)

                self.file.write("extern const %s  %s;\n" % (groupStructName, defaultsStructName))
                if config.options.relocatable:
                    self.file.write("extern %s  *%s;\n" % (groupStructName.ljust(28), paramsStructName))
                else:
                    self.file.write("extern %s  %s;\n" % (groupStructName.ljust(28), paramsStructName))

            # TODO: RAM-less tags would be generated here if we needed them (but we don't)

            if hasDynMemTags:
                self.file.write("\n/* Structure containing pointers to the tags that belong to the group : %s without static RAM */\n" % group['name'])
                self.file.write("typedef struct \n{")

                for tag in self.nvmTags.tags:
                    if group['name']!=tag.group or not tag.genCode() or not tag.dynMem:
                        continue

                    # Check if this is a patch build
                    if romCode:
                        if config.options.buildType == "PATCH" and tag.isPatched:
                            # Do not add tag here
                            continue
                    else:
                        if not tag.isPatched:
                            # Only add patched tags here
                            continue
                    
                    self.file.write("\n")
                    self.file.write("%s/* Tag : %u : %s */\n" % (" "*indent, tag.num, tag.name))
                    self.file.write("   UINT8 *Cfg_%s_Ptr;\n" % CodeGen.makeIdent(tag.name))
                
                if romCode:
                    dynPtrType = CodeGen.makeUpperIdent("CFG_STRUCT_DYNMEM_" + group['name'] + "_PTR_TYPE")
                    self.file.write("\n} %s;\n\n" % dynPtrType)
                    self.file.write("extern %s CFG_DynMem_Ptrs_%s;\n" % (CodeGen.padTo(dynPtrType, 30), group['name']))
                else:
                    dynPtrType = CodeGen.makeUpperIdent("CFG_STRUCT_DYNMEM_" + group['name'] + "_PATCH_PTR_TYPE")
                    self.file.write("\n} %s;\n\n" % dynPtrType)
                    self.file.write("extern %s patch_CFG_DynMem_Ptrs_EXT_%s;\n" % (CodeGen.padTo(dynPtrType, 30), group['name']))

            ####################################################################
            # Generate reference macros for each tag
            ####################################################################
            
            self.file.write("\n#define  %s" % CodeGen.padTo(CodeGen.makeUpperIdent("%sCFG_%s_PARAMETERS_PTR" % (patchStr, group['name'])), 40))
            if hasStaticRAM:
                self.file.write(" ((UINT8 *) &(%s))\n" % paramsStructName)
            else:
                # No tags available in this group. Define data as NULL
                self.file.write("NULL\n")
            
            self.file.write("\n#define  %s" % CodeGen.padTo(CodeGen.makeUpperIdent("%sCFG_%s_DEFAULTS_PTR" % (patchStr, group['name'])), 40))
            if hasStaticRAM:
                self.file.write(" ((UINT8 *) &(%s))\n" % defaultsStructName)
            else:
                # No tags available in this group. Define data as NULL
                self.file.write("NULL\n")
                
            for tag in self.nvmTags.tags:
                if group['name']!=tag.group or not tag.genCode():
                    continue
                
                # Check if this is a patch build
                if romCode:
                    if config.options.buildType == "PATCH" and tag.isPatched:
                        # Do not add tag here
                        continue
                else:
                    if not tag.isPatched:
                        # Only add patched tags here
                        continue

                self.file.write("\n/* Tag : %u : %s */\n" % (tag.num, tag.name))
                self.file.write("/* References to the configuration parameter values */\n")

                if tag.dynMem:
                    self.file.write("#define  %s" % CodeGen.padTo(CodeGen.makeUpperIdent("CFG_%s_%s_PTR" % (tag.group, tag.name)), 40))
                    self.file.write("(CFG_DynMem_Ptrs_%s.Cfg_%s_Ptr)\n"% (tag.group, CodeGen.makeIdent(tag.name)) )
                else:
                    if config.options.relocatable: 
                        tag.typeInfo.genTagElementRef(self.file, "%sCFG_%s" % (patchStr, tag.group), paramsStructName + "->")
                    else:
                        tag.typeInfo.genTagElementRef(self.file, "%sCFG_%s" % (patchStr, tag.group), paramsStructName + ".")

                if not tag.dynMem:
                    self.file.write("\n/* References to the default configuration parameter values */\n")
                    tag.typeInfo.genTagElementRef(self.file, "%sCFG_DEFAULT_%s" % (patchStr, tag.group), defaultsStructName + ".")

            ####################################################################
            # Generate function prototypes for tag group functions
            ####################################################################
            if romCode:
                self.file.write(CodeGenTemplates.groupHFunc.format(groupName=group['name'], oneSpace=self.oneSpace))
            else:
                self.file.write(CodeGenTemplates.groupHPatchFunc.format(groupName=group['name'], oneSpace=self.oneSpace))

            if config.options.relocatable:
                self.file.write("\n")
                self.file.write(CodeGenTemplates.groupRelocateFunc.format(groupName=group['name'], oneSpace=self.oneSpace))

            self.file.write("\n#endif /* #if (%s == INCLUDE_FEATURE) */\n" % define)
            self.file.write("\n#endif /* } #ifndef %s*/\n" % self.hdrProt)

            # Close the file when we've finished
            self.file.close()
            self.file = None


    ############################################################################
    # Generate tag groups source file
    ############################################################################
    def genGroupsC(self, genUL, romCode):
        if genUL:
            raise TagError("Upper Layer code generation not implemented yet")

        tagTypesFile = CodeGen.CFG_PREFIX.lower() + "tag_types.h"
        tagsFile = CodeGen.CFG_PREFIX.lower() + "tags.h"
        
        if romCode:
            patchStr = ""
            groupVarName = "CFG_Parameters_"
            groupDefaultName = "CFG_Defaults_"
            attributeSection = ""
        else:
            patchStr = "_patch"
            groupVarName = "patch_CFG_Parameters_EXT_"
            groupDefaultName = "patch_CFG_Defaults_EXT_"
            attributeSection = """__attribute__((section("CFG_Parameters")))"""

        # Iterate through each group in turn, generating group-specific source files
        for group in self.nvmTags.tagGroups.groups:
            if not self.nvmTags.genSourceForGroup(group['name'], not genUL):
                continue

            groupsC = (CodeGen.CFG_PREFIX + group['name'] + patchStr + ".c").lower()
            groupsH = (CodeGen.CFG_PREFIX + group['name'] + patchStr + ".h").lower()

            self.file = self.createFile(groupsC, False)
            if self.file is None:
                if config.options.fileList:
                    # Just loop around to the next file after we've derived the filename
                    continue
                else:
                    raise TagError("Unable to create file: %s" % tagListFile)

            if config.options.compat:
                # Filenames displayed in files are not case-corrected
                groupsC = CodeGen.CFG_PREFIX + group['name'] + patchStr + ".c"

            self.writeFileHeader(groupsC, " *     This file contains the tag data belonging to the group : %s\n" % group['name'])

            self.file.write('#include "pf.h"\n')
            self.file.write('#include "pfal_cfg.h"\n')
            self.file.write("#include \"%s\"\n" % tagsFile)
            self.file.write("#include \"%s\"\n\n\n" % tagTypesFile)

            define = CodeGen.makeUpperIdent("CFG_TAGGROUP_" + group['name'])
            self.file.write("#if (%s == INCLUDE_FEATURE)\n\n" % define)
            self.file.write("#include \"%s\"\n" % groupsH)

            ####################################################################
            # Generate array definitions for each tag
            ####################################################################
            hasStaticRAM = False
            hasDynMem = False
            indent = 4
            groupStructName = self.makeUpperIdent("CFG_STRUCT_" + group['name'] + patchStr + "_TYPE")

            for tag in self.nvmTags.tags:
                if group['name']!=tag.group or not tag.genCode() or tag.dynMem:
                    continue
                if romCode:
                    if config.options.buildType == "PATCH" and tag.isPatched:
                        # Do not add tag here
                        continue
                else:
                    if not tag.isPatched:
                        # Only add patched tags here
                        continue

                # Print section header for first tag
                if not hasStaticRAM:
                    hasStaticRAM = True
                    self.file.write("\n/* Default values to the tags that belong to the group : %s */\n" % tag.group)
                    if config.options.relocatable:
                        self.file.write("%s  *%s%s;\n\n" % (groupStructName, groupVarName, tag.group))
                    else:
                        self.file.write("%s  %s%s %s;\n\n" % (groupStructName, groupVarName, tag.group, attributeSection)) 
                    self.file.write("const %s  %s%s =\n{" % (groupStructName, groupDefaultName, tag.group))
                else:
                    # This is not the first tag so add a comma separator
                    self.file.write(",")

                self.file.write("\n%s/* Tag : %u : %s */\n" % (" "*indent, tag.num, tag.name))
                tag.typeInfo.genTagDefaultData(self.file, indent)

            if hasStaticRAM:
                self.file.write("\n};\n\n")

            for tag in self.nvmTags.tags:
                if group['name']!=tag.group or not tag.genCode() or not tag.dynMem:
                    continue
                if romCode:
                    if config.options.buildType == "PATCH" and tag.isPatched:
                        # Do not add tag here
                        continue
                else:
                    if not tag.isPatched:
                        # Only add patched tags here
                        continue

                if not hasDynMem:
                    hasDynMem = True
                    self.file.write("\n/* Default values to the tags that belong to the group : %s */\n" % tag.group)
                    dynPtrType = CodeGen.makeUpperIdent("CFG_STRUCT_DYNMEM_" + tag.group + "_PTR_TYPE")
                    self.file.write("%s  CFG_DynMem_Ptrs_%s;\n" % (dynPtrType, tag.group))
            if romCode:
                self.file.write(CodeGenTemplates.groupCInit.format(groupName=group['name']))
            else:
                self.file.write(CodeGenTemplates.groupCPatchInit.format(groupName=group['name']))

            if hasStaticRAM:
                if config.options.relocatable:
                    # Write the code in CInit funciton 
                    self.file.write("    %s%s = (%s *)(&%s%s);\n" % (groupVarName, group['name'], groupStructName, groupDefaultName, group['name']))
                else:
                    self.file.write("    /* Copy the default configuration values into the parameter structure */\n")
                    self.file.write("    PFAL_PROC_memscpy(&%s%s, (sizeof(%s)), &%s%s, (sizeof(%s)));\n" %
                        (groupVarName, group['name'], groupStructName, groupDefaultName, group['name'], groupStructName))

            # Point the RAM pointers to the compile time default values
            if hasDynMem:
                for tag in self.nvmTags.tags:
                    if group['name']!=tag.group or not tag.genCode() or not tag.dynMem:
                        continue
                    if romCode:
                        if config.options.buildType == "PATCH" and tag.isPatched:
                            # Do not add tag here
                            continue
                    else:
                        if not tag.isPatched:
                            # Only add patched tags here
                            continue

                    self.file.write("    /* Tag : %u : %s */\n" % (tag.num, tag.name))
                    if romCode:
                        self.file.write("    %s = NULL;\n" % CodeGen.makeUpperIdent("CFG_%s_%s_PTR" % (tag.group, tag.name)))
                    else:
                        self.file.write("    %s = NULL;\n" % CodeGen.makeUpperIdent("PATCH_CFG_%s_%s_PTR" % (tag.group, tag.name)))

            # Write function to relocate default group configuration values
            if config.options.relocatable:
                if romCode:
                    self.file.write(CodeGenTemplates.groupCRelocate.format(groupName=group['name']))
                else:
                    self.file.write(CodeGenTemplates.groupCPatchRelocate.format(groupName=group['name']))
               
                self.file.write("    if((NULL == *Address) || (*Length <= sizeof(%s)))\n" % groupStructName)
                self.file.write("    {\n")
                self.file.write("        return(SiW_FALSE);\n")
                self.file.write("    }\n")
                self.file.write("    PFAL_PROC_memscpy(*Address, *Length, &%s%s, sizeof(%s));\n" % (groupDefaultName, group['name'], groupStructName))
                self.file.write("    %s%s  = (%s *)(*Address);\n" % (groupVarName, group['name'], groupStructName))
                self.file.write("    *Length           -= sizeof(%s);\n" % groupStructName)
                self.file.write("    *Address           = (UINT8 *)(*Address) + sizeof(%s);\n" % groupStructName)
                self.file.write("    return(SiW_TRUE);\n")

            # Write functions to retrieve length and value locations of the parameters that belong to the group
            if romCode:
                self.file.write(CodeGenTemplates.groupCGetConfig.format(groupName=group['name']))
            else:
                self.file.write(CodeGenTemplates.groupCPatchGetConfig.format(groupName=group['name']))

            if hasStaticRAM:
                self.file.write(CodeGenTemplates.groupCGetConfigStaticRAM)
                for tag in self.nvmTags.tags:
                    if group['name']!=tag.group or not tag.genCode() or tag.dynMem:
                            continue
                    if romCode:
                        if config.options.buildType == "PATCH" and tag.isPatched:
                            # Do not add tag here
                            continue
                    else:
                        if not tag.isPatched:
                            # Only add patched tags here
                            continue

                    self.file.write("\n        case %d:\n" % tag.num)
                    self.file.write("        {/* Tag : %u : %s */\n" % (tag.num, tag.name))
                    self.file.write("            pNvmEntry->Length = %d;\n" % tag.getMaxLength())
                    if romCode:
                        self.file.write("            pNvmEntry->pValue = %s;\n" % self.makeUpperIdent("CFG_%s_%s_PTR" % (tag.group, tag.typeInfo.typeInfo.name)))
                    else:
                        self.file.write("            pNvmEntry->pValue = %s;\n" % self.makeUpperIdent("PATCH_CFG_%s_%s_PTR" % (tag.group, tag.typeInfo.typeInfo.name)))
                    self.file.write("            bConfigParameterFound=SiW_TRUE;\n")
                    self.file.write("            break;\n")
                    self.file.write("        }\n")
                self.file.write(CodeGenTemplates.groupCGetConfigStaticRAMDefault)
            else:
                self.file.write("    return(SiW_FALSE);\n")
            self.file.write("}\n\n")

            # Write function to handle the Dynamic Memory tags that belong to the group
            if romCode:
                self.file.write(CodeGenTemplates.groupCHandleVarConfig.format(groupName=group['name'], oneSpace=self.oneSpace))
            else:
                self.file.write(CodeGenTemplates.groupCPatchHandleVarConfig.format(groupName=group['name'], oneSpace=self.oneSpace))

            if hasDynMem:
                self.file.write("    SiW_BOOLEAN bConfigParameterFound=SiW_FALSE;\n")
                self.file.write("    switch(pNvmEntry->Tag)\n")
                self.file.write("    {")

                for tag in self.nvmTags.tags:
                    if group['name']!=tag.group or not tag.genCode() or not tag.dynMem:
                        continue
                    if romCode:
                        if config.options.buildType == "PATCH" and tag.isPatched:
                            # Do not add tag here
                            continue
                    else:
                        if not tag.isPatched:
                            # Only add patched tags here
                            continue
                            
                    self.file.write(CodeGenTemplates.groupCHandleVarConfigCase.format(tagNum=tag.num, tagName=tag.name, tagPtr=self.makeUpperIdent("CFG_%s_%s_PTR" % (tag.group, tag.name))))

                self.file.write(CodeGenTemplates.groupCHandleVarConfigDefault)
            else:
                self.file.write("    return(SiW_FALSE);\n")
            self.file.write("}\n\n")

            if romCode:
                self.file.write(CodeGenTemplates.groupCDynamicTags.format(groupName=group['name'], oneSpace=self.oneSpace))
            else:
                self.file.write(CodeGenTemplates.groupCPatchDynamicTags.format(groupName=group['name'], oneSpace=self.oneSpace))
                self.file.write("\n#endif /* CFG_PATCH_BUILD_VTAG_SUPPORT == INCLUDE_FEATURE */\n")
            self.file.write("\n#endif /* #if (%s == INCLUDE_FEATURE) */\n" % define)

            # Close the file when we've finished
            self.file.close()
            self.file = None


    ############################################################################
    # Write generic file header boilerplate.
    #
    # This can include file-specific descriptive text.
    ############################################################################
    def writeFileHeader(self, filename, extraHeader=None):
        self.file.write("/*\n")
        self.file.write(" *************************************************************************\n")
        self.file.write(" *\n")
        self.file.write(" * %s\n" % filename)
        self.file.write(" *\n")
        self.file.write(" *************************************************************************\n")
        self.file.write(" *\n")
        self.file.write(" * Purpose:\n")

        # Write extra header supplied by caller
        if extraHeader is not None: self.file.write(extraHeader)

        # Write end of header with copyright information etc.
        self.file.write(CodeGenTemplates.legal.format(year=config.timestamp.year, oneSpace=self.oneSpace, twoSpace=self.twoSpace, threeSpace=self.threeSpace))
        self.file.write(" *************************************************************************\n")
        self.file.write(" */\n\n")


    ############################################################################
    # Write a standard C header include guard protection #ifdef / #define
    ############################################################################
    def writeHeaderProt(self, filename):
        self.hdrProt = "_" + self.makeUpperIdent(filename) + "_"
        self.file.write("#ifndef %s /* { */\n" % self.hdrProt)
        self.file.write("#define %s\n\n" % self.hdrProt)


    ############################################################################
    # Create a new file in the output folder. Check that it is writable
    ############################################################################
    def createFile(self, filename, isHeader):
        # Ensure lower case filenames for C and H files
        if filename[-4:] != ".htm":
            filename = filename.lower()
            isCode = True
        else:
            isCode = False

        if isHeader:
            filename = self.incPath + filename
        elif isCode:
            filename = self.srcPath + filename
        else:
            filename = self.outpath + filename

        if config.options.fileList:
            print("%s" % filename)
            return None
        elif config.options.verbose:
            print("Generating %s" % filename)

        # If this fails to open we'll just let the IOError exception go up
        return open(filename, "w")


    ############################################################################
    # Generate HTML documentation - this function is common to both internal
    # and external code generation
    ############################################################################
    def genHTML(self, htmlFile, allowInternal):

        self.file = self.createFile(htmlFile, False)
        if self.file is None:
            if config.options.fileList:
                return
            else:
                raise TagError("Unable to create file: %s" % htmlFile)

        self.file.write(CodeGenTemplates.htmlLegal.format(year=config.timestamp.year, timestamp=self.nvmTags.timestamp, oneSpace=self.oneSpace))

        for tag in self.nvmTags.tagScope:
            if tag.internal and config.options.hideInternal:
                continue

            self.file.write("<TR>\n")
            self.file.write("<TD> %u </TD>\n" % tag.num)
            self.file.write("<TD><a href=\"#%u\"><b> %s </b></a></TD>\n" % (tag.num, tag.name))
            if tag.hasVarArray():
                self.file.write("<TD>Variable</TD>\n")
            else:
                self.file.write("<TD> %u </TD>\n" % tag.getMaxLength())
            self.file.write("</TR>\n")
        self.file.write("</TABLE>\n")

        self.file.write("<h3>Description of Parameters</h3>\n")
        self.file.write("\n<hr>\n")

        for tag in self.nvmTags.tagScope:
            # Tag details for internal tags are excluded from customer-facing external documentation
            showDetails = True
            if tag.internal:
                if config.options.hideInternal:
                    # Don't include internal tag details at all if suppressed at command line
                    continue
                elif not allowInternal:
                    showDetails = False

            self.file.write("<h4><A NAME=\"%u\">%s </h4>\n" % (tag.num, tag.name))
            if showDetails and tag.desc is not None:
                self.file.write("%s \n" % tag.desc)
            self.file.write("\n<ul>\n")
            self.file.write("<li><b>Number         :</b> %u \n" % tag.num)

            self.file.write("<li><b>Platforms :</b>\n")
            self.file.write("\n<ul>\n")

            for plat in self.nvmTags.tagPlatforms.platforms:
                self.file.write("<li>%s \n" % plat['name'])

            self.file.write("\n</ul>\n\n")

            if showDetails:
                if tag.hasVarArray():
                    self.file.write("<li><b>Size :</b> Variable\n")
                else:
                    self.file.write("<li><b>Size :</b> %u \n" % tag.getMaxLength())

                self.file.write("<li><b>Format         :</b> \n")
                self.file.write("\n<ul>\n")
                tag.typeInfo.genTagUserFormat(self.file, 15, 0)
                self.file.write("\n</ul>\n\n")

            # Version Added and Version Obsolete information could be written but we don't currently use it.

            if len(tag.related) > 0:
                self.file.write("<li><b>Related Parameters : </b>\n")
                self.file.write("\n<ul>\n")
                for relatedTagNum in tag.related:
                    relatedTag = self.nvmTags.getTag(relatedTagNum)
                    if relatedTag is not None:
                        self.file.write("<a href=\"#%u\"><b> %s</b></a>" % (relatedTag.num, relatedTag.name))
                        self.file.write("<br>\n")
                self.file.write("\n</ul>\n")

            if tag.internal:
                self.file.write("<br><b>Note : Qualcomm Internal Use only. This key should only be changed on advice from Qualcomm </b><br>\n")

            self.file.write("</ul>\n")
            self.file.write("<a href=\"#TR\"><b>Back to Index</b></a>\n")
            self.file.write("\n<hr>\n")

        self.file.write("\n</body>\n")
        self.file.write("\n</html>\n")

        # Close the file when we've finished
        self.file.close()
        self.file = None


    ############################################################################
    # Generate internal HTML documentation for tags
    ############################################################################
    def genInternalUsersFile(self):
        self.genHTML("ConfigurationParameters.htm", True)


    ############################################################################
    # Generate external HTML documentation for tags
    ############################################################################
    def genExternalUsersFile(self):
        self.genHTML("ExternalConfigurationParameters.htm", False)
