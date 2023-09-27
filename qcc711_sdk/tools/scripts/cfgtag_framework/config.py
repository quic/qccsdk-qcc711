################################################################################
# Top level type definitions and other config
################################################################################
# Copyright (c) 2018-2021 Qualcomm Technologies International, Ltd.
# All Rights Reserved
# Confidential and Proprietary - Qualcomm Technologies International, Ltd.
################################################################################


################################################################################
# Library Imports
################################################################################
import os, re, datetime
from optparse import OptionParser


################################################################################
# Global Variables
################################################################################

# Execution timestamp object for use when writing files
timestamp = datetime.datetime.now()

# Parsed command line options
options = None
inputFile = None
outputFile = None

# Input formats
inputFormats = [ "xml", "tcf", "tcfx" ]

# Output formats
outputFormats = [ "xml", "tcf", "tcfx", "sdb", "htf", "nvm", "nvmx", "src", "html", "vtags" , "vlist", "offsets" ]

# Output scope (what classes of tags are emitted)
outputScope = [ "physical", "virtual", "all" ]


################################################################################
# Class Definitions
################################################################################


################################################################################
# Tag Exception Class
################################################################################
class TagError(Exception):
    def __init__(self, msg):
        self.msg = msg


################################################################################
# Class describing a basic integer type
################################################################################
class BasicType:
    # Class Variables (used as enumerations)
    TYPE_UCHAR = 0
    TYPE_USHORT = 1
    TYPE_UINT = 2
    TYPE_SCHAR = 3
    TYPE_SSHORT = 4
    TYPE_SINT = 5

    def __init__(self):
        self.dataType = None
        self.signed = 0
        self.value = 0
        self.size = 0

    def getTypeRange(self):
        # Return the valid C integer range for this type
        numBits = self.size * 8
        min = 0 - (1<<(numBits-1))
        max = (1<<(numBits-1)) - 1
        if not self.isSigned():
            min += (1<<(numBits-1))
            max += (1<<(numBits-1))
        return min, max

    def getTypeString(self):
        if self.dataType == BasicType.TYPE_UCHAR:   return "UINT8"
        if self.dataType == BasicType.TYPE_SCHAR:   return "INT8"
        if self.dataType == BasicType.TYPE_USHORT:  return "UINT16"
        if self.dataType == BasicType.TYPE_SSHORT:  return "INT16"
        if self.dataType == BasicType.TYPE_UINT:    return "UINT32"
        if self.dataType == BasicType.TYPE_SINT:    return "INT32"
        raise TagError("Unknown data type: %d" % self.dataType)

    def getFormatSpec(self):
        global options

        # Backwards compatibility: TagCfg.exe always emits signed numbers as
        # 32-bit unsigned hex (and casts to INT8 etc.). This seems odd, so when
        # not using compatibility mode just emit signed numbers as decimal
        if options.compat or not self.signed:
            return self.getHexFormatSpec(zeroPad=True)
        else:
            return "%d"

    def getHexFormatSpec(self, zeroPad=True):
        if zeroPad:
            return "%%0%dX" % (2*self.size)
        else:
            return "%%%dX" % (2*self.size)

    # Helper function to convert a signed integer to equivalent unsigned hex value
    # using the current type's definition.
    def forHex(self, val):
        if val < 0:
            if self.size==1: val += 0x100
            elif self.size == 2: val += 0x10000
            else: val += 0x100000000
        return val

    # Helper function to convert an unsigned hex value to an equivalent signed integer
    # using the current type's definition.
    def fromHex(self, val):
        _, max = self.getTypeRange()
        if val > max:
            val -= (max+1)*2
        return val

    # Convert the value to a little-endian octet byte sequence corresponding to the value
    def getByteStr(self):
        if self.isSigned():
            intVal = self.forHex(self.value)
        else:
            intVal = self.value

        default = []
        for i in range(self.size):
            byte = (intVal & 0xFF)
            default.append(byte)
            intVal >>= 8

        return default

    def getByteRangeStr(self, byteIndex):
        if self.size == 1:
            rangeStr = "Byte %u" % (byteIndex)
        else:
            rangeStr = "Byte %u - %u" % (byteIndex, byteIndex+self.size-1)

        return rangeStr

    def isSigned(self):
        if self.signed or self.dataType == BasicType.TYPE_SCHAR or self.dataType == BasicType.TYPE_SSHORT or self.dataType == BasicType.TYPE_SINT:
            return True
        else:
            return False

    def evalType(self):
        if self.size == 1:
            if self.signed: self.dataType = BasicType.TYPE_SCHAR
            else: self.dataType = BasicType.TYPE_UCHAR
        elif self.size == 2:
            if self.signed: self.dataType = BasicType.TYPE_SSHORT
            else: self.dataType = BasicType.TYPE_USHORT
        elif self.size == 4:
            if self.signed: self.dataType = BasicType.TYPE_SINT
            else: self.dataType = BasicType.TYPE_UINT
        else:
            raise TagError("Unsupported size for data type: %d" % self.size)


################################################################################
# Generic tag type information
################################################################################
class TagTypeInfo:
    # Class Variables (used as enumerations)
    INTEGER = 0
    ENUM = 1
    BITFIELD = 2
    STRUCTURE = 3
    VARIABLE_ARRAY = 4
    FIXED_ARRAY = 5
    STRUCT_ARRAY = 6
    RAW_BYTES = 255

    typeNameMap = {
        'VALUE':        	INTEGER,
        'INTEGER' :			INTEGER,
        'ENUM':         	ENUM,
        'BITS':         	BITFIELD,
        'BITFIELD':			BITFIELD,
        'STRUCT':       	STRUCTURE,
        'STRUCTURE':		STRUCTURE,
        'STRUCT_ARRAY':		STRUCT_ARRAY,
        'VAR_ARRAY':		VARIABLE_ARRAY,
        'VARIABLE_ARRAY':	VARIABLE_ARRAY,
        'FIXED_ARRAY':		FIXED_ARRAY }


################################################################################
# Local Functions
################################################################################


################################################################################
# Returns Hexadecimal String from Integer 
# we have Format Spec implemented already , needs to be
# merged with the function in Basic Type
################################################################################
def ToHex(number, size, LowerCase=True):
    mod_val = 1 << (size * 8)
    number = (number + mod_val) % mod_val
    fmt_str = '0x{{:0X}}'.format(size * 2)
    if LowerCase:
        fmt_str.lower()
    return fmt_str.format(number)

################################################################################
# Return Integer from Hexadecimal string or number
# we have Format Spec implemented already , needs to be
# merged with the function in Basic Type
################################################################################
def ToInt(hex_number, size, IsSigned):
    if not hex_number:
        return 
    nbits = 8 * size
    if type(hex_number) == str:
        hex_number = int(hex_number, 16)
        if not IsSigned:
            return hex_number
    return int(-(hex_number & (1 << nbits - 1)) | (hex_number & ((1 << (nbits - 1)) - 1)))
    
################################################################################
# Return a string that concatenates a list of options with commas and a final "or"
################################################################################
def GetOptionListString(optList):
    if len(optList) == 0:
        return ""

    if len(optList) == 1:
        return optList[0]

    if len(optList) == 2:
        return "%s or %s" % (optList[0], optList[1])
    else:
        lastOption = optList[-1]
        return ", ".join(optList[:-1]) + ", or %s" % lastOption


################################################################################
# Comma-separate option arg list of integers.
# Support integer ranges via M-N notation
#
# E.g. given --foo=1,3-5,8 return a list [1, 3, 4, 5, 8]
#
################################################################################
def CommaSeparatedOption(option, opt, value, parser):
    valList = []
    try:
        for val in re.sub(",,+", ",", value.strip(',')).split(','):
            valRange = val.split('-')
            if len(valRange) == 1:
                valList.append(int(val))
            elif len(valRange) == 2:
                start = int(valRange[0])
                stop = int(valRange[1])
                if start > stop:
                    temp = start
                    start = stop
                    stop = temp
                valList.extend(range(start, stop+1))
            else:
                raise TagError("%s option must be a comma-separated list of integers" % opt)
    except ValueError:
        raise TagError("%s option must be a comma-separated list of integers" % opt)

    setattr(parser.values, option.dest, valList)


################################################################################
# Command-line options parsing
#
################################################################################
def ParseOptions():
    global options, inputFile, outputFile, timestamp

    parser = OptionParser(usage='%prog [options] input_file [output_file]')

    parser.add_option('--input', dest='input', action='store',
                        choices=inputFormats,
                        default=None,
                        help="Select the input file format (%s)" % GetOptionListString(inputFormats))

    parser.add_option('--output', dest='output', action='store',
                        choices=outputFormats,
                        default=None,
                        help="Select the output file format (%s)" % GetOptionListString(outputFormats))

    parser.add_option('--scope', dest='scope', action='store',
                        choices=outputScope,
                        default="all",
                        help="Select the classes of tag that will be output (%s), default is all tags" % GetOptionListString(outputScope))

    parser.add_option('--filterVtagList', dest='filterVtagList', action='store',
                        default=None,
                        help="Virtual tag filter list file")

    parser.add_option('--tags', type="string", dest='tags', action='callback', callback=CommaSeparatedOption,
                        help="Provide comma-separated ranges of tag IDs to process. For example: --tags=1,2,17, --tags=1-12,83-127 etc.")

    parser.add_option('--filterInternal', dest='filterInternal', action='store_true',
                        help="Filter out (don't process) all tags marked internal. This overrides any tag selection made with the --tags option.")

    parser.add_option('--fileList', dest='fileList', action='store_true',
                        default=False,
                        help="With --output=src, rather than generate the files simply write a list of files to stdout, e.g. for build system dependency generation")

    parser.add_option('-s', '--summarise', dest='summarise', action='store_true',
                        default=False,
                        help="Print a summary of tags (name, number, size), one per line")

    parser.add_option('--strict', dest='strict', action='store_true',
                        default=False,
                        help="Enable stricter parsing, default is to only warn on errors")

    parser.add_option('--compat', dest='compat', action='store_true',
                        default=False,
                        help="Enable backward-compatibility mode on code generation")

    parser.add_option('--hideInternal', dest='hideInternal', action='store_true',
                        default=False,
                        help="With --output=html, internal tags are omitted from external documentation rather than just summarised")

    parser.add_option('--compactHTF', dest='compactHTF', action='store_true',
                        default=False,
                        help="Write more compact HTF files, omitting descriptive comments and multi-line output")

    parser.add_option('--eraseDB', dest='eraseDB', action='store_true',
                        default=False,
                        help="Erase any existing database contents before writing new data")

    parser.add_option('--fwVersion', dest='fwVersion', action='store',
                        default=None,
                        help="Specify the FW subsystem version (required for --output=sdb)")

    parser.add_option('--sysInfo', dest='sysInfo', action='store',
                        default=None,
                        help="Specify the RCF system information file (required for --output=sdb)")

    parser.add_option('--noDefaults', dest='noDefaults', action='store_true',
                        default=False,
                        help="Don't include ROM defaults when writing SDB database")

    parser.add_option('--merge', dest='merge', action='append',
                        default=[],
                        help="Specify a NVM / NVMX file containing tag values to merge into the database. This overwrites the default values in the tag definition file.")
                        
    parser.add_option('--convertToNVMX', dest='convertToNVMX', action='store_true',
                        default=False,
                        help="Convert existing NVM to NVMX based on TCF file, merge the NVM values to TCFX and save only changed tags from that of TCFX.")
                        
    parser.add_option('--alignToTCFX', dest='alignToTCFX', action='store_true',
                        default=False,
                        help="When one or more tags of TCFX files are edited to add or delete elements, then the corresponding change should be made to NVMX files.")
                        
    parser.add_option('-v', '--verbose', dest='verbose', action='store_true',
                        default=False,
                        help='Enable verbose output (not suitable for scripting)')

    parser.add_option('--looseTime', dest='looseTime', action='store_true',
                        default=False,
                        help='Loosen up timestamps by setting seconds to 0')

    parser.add_option('--debug', dest='debug', action='store_true',
                        default=False,
                        help='Turn on debug output')

    parser.add_option('--list', dest='vtagListFile', action='store',
                        default=None,
                        help="Specify the virtual tag list file (required for --output=sdb,vlist,vtag)")

    parser.add_option('--baseId', dest='baseId', action='store',
                        default=None,
                        help="Select the base ID for virtual tags (required for --output=vlist)")

    parser.add_option('--patchBaseId', dest='patchBaseId', action='store', type='int',
                        default=65535,
                        help="Select the patch base ID for virtual tags")

    parser.add_option('--lastTagId', dest='lastTagId', action='store', type='int',
                        default=65535,
                        help="Last known NVM tag before ROM tapeout")

    parser.add_option('--relocatable', dest='relocatable', action='store_true',
                        default=False,
                        help='Enable relocatable NVM tag code generating')

    parser.add_option('--symdefs', dest='symdefsFile', action='store',
                        default=None,
                        help='Input symdefs file (required for --output=offsets).')

    parser.add_option('--symdefs-type', dest='symdefsType', action='store',
                        default='symdef',
                        help='Input symdefs file type (required for --output=offsets): symdef|scl.')

    parser.add_option('--offsets-base', dest='offsetsBase', action='store',
                        default=None,
                        help='Base address for config tags structures (required for --output=offsets).')

    # Process command line arguments
    options, args = parser.parse_args()

    # Validate correct number of positional arguments
    if len(args) < 1 or (len(args) == 1 and not options.summarise and not options.fileList and not options.alignToTCFX):
        parser.print_help()
        raise TagError("Missing input/output files on the command line.")
    if len(args) > 2:
        parser.print_help()
        raise TagError("Too many input/output files on the command line.")

    inputFile = args[0]
    if len(args) > 1:
        outputFile = args[1]

    # Validate input and output file types if not overridden on the command line
    if options.input is None:
        options.input = os.path.splitext(inputFile)[1][1:]
        if options.input not in inputFormats:
            parser.print_help()
            raise TagError("Unknown input file type (%s). Consider using --input= to clarify." % options.input)

    if options.output is None and outputFile is not None:
        # Must explicitly state output type if the destination is a directory
        if os.path.isdir(outputFile):
            raise TagError("For directory output you must explicitly state the output file type.")

        options.output = os.path.splitext(outputFile)[1][1:]
        if options.output not in outputFormats:
            parser.print_help()
            raise TagError("Unknown output file type (%s). Consider using --output= to clarify." % options.output)

    # Check that the output type can be met with the output scope
    if options.scope == "physical":
        if options.output == "vtags":
            raise TagError("--output=%s is not supported with --scope=physical." % options.output)

    # SDB file output requires the user to specify the system information as well
    if options.output == "sdb":
        if options.fwVersion is None:
            raise TagError("--output=%s requires --fwVersion option as well." % options.output)
        if options.sysInfo is None:
            raise TagError("--output=%s requires --sysInfo option as well." % options.output)
    elif options.output == "vlist":
        # For virtual tag list, either the input file is specified or the base ID
        if options.vtagListFile is None and options.baseId is None:
            raise TagError("--output=%s requires either --list or --baseId option as well." % options.output)

    # File list is only valid for src and HTML output
    if options.fileList and options.output != "src" and options.output != "html":
        raise TagError("--fileList argument cannot be used with --output=%s." % options.output)

    # For multi-file output types, check the output path exists, and normalise it
    # to include a trailing slash
    if (options.output == "src" or options.output == "html" or options.output == "vtags"):
        if not os.path.isdir(outputFile):
            raise TagError("For vtags, src, and html output types, the target must be an existing directory.")
        if outputFile[-1:] != "/":
            outputFile += "/"
    elif outputFile and os.path.isdir(outputFile):
            raise TagError("For %s output type, the target cannot be a directory." % options.output) is None

    #Conversion of NVM to NVMX validation
    if options.convertToNVMX and (options.input != "tcfx" or options.output != "nvmx" or options.merge == []):
        raise TagError("For Converting NVM to NVMX, provide input should be TCFX , \n Output should be NVMX, --merge should have list of NVM files that are to be converted.")
    
    if options.alignToTCFX and (options.input != 'tcfx' or options.merge == []):
        raise TagError("--alignToTCFX \n\tOption is to be used for bring NVMX Tags aligned to that of TCFX \n\tby assiging default values from TCFX to the NVMX for the added / deleted elements of the TAG \n\t& no additional NVM / NVMX files are to be merged.")
        
    # Debug implies verbose
    if options.debug: options.verbose = True
    
    if options.lastTagId is None or options.lastTagId == 65535:
        # We're building the ROM
        options.buildType = "ROM"
    else:
        # We're building the PATCH
        options.buildType = "PATCH"

    if options.looseTime:
        # Zero the seconds in the timestamp for ease of testing. It makes diff'ing
        # rapidly-generated files easier as they will usually have the same timestamp.
        timestamp = timestamp.replace(second=0)
