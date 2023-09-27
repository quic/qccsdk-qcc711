################################################################################
# NVM Cfg Tag binary/hex blob patching utility
################################################################################
# Copyright (c) 2021 Qualcomm Technologies, Inc.
# All Rights Reserved.
# Confidential and Proprietary - Qualcomm Technologies, Inc.
################################################################################

from tagblob import *

import argparse
import os

from sys import exit
from offsets_fileformats import OffsetsFile

from xml_wrapper import ET

# This function expects tag_dict to be a dictionary of {tag_name: }
def read_nvmx_file(filename, tag_dict, allow_missing):
    
    tag_list = []

    # Read the NVMX into an XML structure.
    nvmxobj = ET.parse(filename)
    nvmx = nvmxobj.getroot()

    # Version check.
    version = nvmx.find('FORMAT_VERSION').text
    if version not in ['1', '1.0']:
        raise RuntimeError('Unrecognized NVMX version {}'.format(version))

    # Iterate through all of the tags.
    nvmx_tags = nvmx.find('TAGS').findall('TAG')
    for nvmx_tag in nvmx_tags:
        name = nvmx_tag.get('Name')

        # Check for unknown tags.
        if name not in tag_dict:
            if not allow_missing:
                print('Warning: skipping unknown tag "{}"'.format(name))
                continue
            else:
                raise RuntimeError('Unknown tag "{}" in NVMX file'.format(name))

        # Continue processing the tag.
        tag = tag_dict[name]
        tag.mergeNVMX(nvmx_tag)
        
        # Use the NVM saving capability of the tag object to extract a byte
        # stream of the actual updated tag data. This expects a file-like object.
        #
        # This may be refactored in the future if the tag object is updated
        # to use a byte stream instead of ascii encoding.

        data = tcfx_tag_to_binary(tag)
        tag_tuple = (tag.num, data)
        tag_list.append(tag_tuple)

    return tag_list

class TagBlobPatcher(object):
    def __init__(self):

        self.fileformat = None        # Required, accepts 'bin' or 'hex'
        self.taginfo = None           # Required, filename of tag offsets info
        self.input = None             # Required, input tag blob file
        self.output = None            # Required, output tag blob file
        self.allow_missing = False    # Controls whether missing tags in the taginfo file are ignored or fatal
        self.allow_duplicates = False # Controls whether duplicate tags in NVM[X] files are allowed or fatal
        self.tcfx = None              # Required only when parsing 
        self.nvm_files = []           # List of NVM[X] patch files to apply to the input blob

    def generate(self):
        
        # Keep track of which tags have been encountered already.
        patched_tags = set()

        # Read tag metadata
        print('Loading offsets information from {} ...'.format(self.taginfo))
        offsets_info = OffsetsFile.load_from(self.taginfo)
        if offsets_info is None:
            print('Error loading offsets metadata.')
            return 1

        # Read input blob
        if self.file_format == 'bin':
            blob = BinaryFile.load_from(self.input)
        elif self.file_format == 'hex':
            blob = IHexFile.load_from(self.input, offsets_info.base)
        else:
            raise NotImplementedError('Invalid file format specified.')

        if self.tcfx is not None:
            print('Reading tag definitions from TCFX...')
            tcfx = load_tcfx(self.tcfx)

            # Convert the tag list into a lookup table.
            tcfx_tag_dict = {}
            for tag in tcfx.tags:
                tcfx_tag_dict[tag.name] = tag

        # Process each NVM file in order.
        for nvm_filename in self.nvm_files:
            print('Applying NVM patch ({}) ...'.format(nvm_filename))

            # Enforce file extensions here
            try:
                if nvm_filename.endswith('.nvmx'):
                    tags_list = read_nvmx_file(nvm_filename, tcfx_tag_dict, self.allow_missing)
                else:
                    print('Unrecognized file extension (only .nvmx supported)')
                    return 1
            except RuntimeError as e:
                print('Error reading NVM data: {}'.format(e))
                return 1

            for tagnum, data in tags_list:

                try:
                    offset = offsets_info.get_tag(tagnum)
                except KeyError:
                    if self.allow_missing:
                        print('Warning: Skipping unknown tag {} present in {}.'.format(tagnum, nvm_filename))
                        continue
                    else:
                        print('Error: Unknown tag {} present in {}.'.format(tagnum, nvm_filename))
                        return 1

                if tagnum in patched_tags:
                    if self.allow_duplicates:
                        print('Warning: Duplicate tag {} present in {}.'.format(tagnum, nvm_filename))
                    else:
                        print('Error: Duplicate tag {} present in {}.'.format(tagnum, nvm_filename))
                        return 1

                print('  Patching tag {} ({} byte(s))'.format(tagnum, len(data)))
                blob.patch_data(data, offset)
                patched_tags.add(tagnum)

        # Write output blob to its new filename.
        print('Writing output to {} ...'.format(self.output))
        blob.filename = self.output
        blob.save()

        print('Done.')
        return 0

def setup_argparse():

    # Named Arguments:
    #  -b/--bin or -h/--hex for bin/hex parsing (exclusive, required)
    #  -t/--taginfo for offsets input file (required)
    #  -i/--input for input bin/hex (required)
    #  -o/--output for output bin/hex (required)
    #  --ignore-missing in case missing tags from offsets file should be non-fatal (optional)
    #
    # Positional Arguments:
    #  [nvm_files...] for one or multiple .nvmx files to parse and patch

    parser = argparse.ArgumentParser(description='Patches a Config Tag NVM blob using tag files and offsets metadata.')

    # Add --bin/--hex options
    ftype_group = parser.add_mutually_exclusive_group(required=True)
    ftype_group.add_argument('-b', '--bin', dest='file_format', action='store_const', const='bin', help='Input/output config tag files are in binary format.')
    if hexfile:
        ftype_group.add_argument('-x', '--hex', dest='file_format', action='store_const', const='hex', help='Input/output config tag files are in ihex format.')

    # Positional arguments
    parser.add_argument('-t', '--taginfo', required=True, help='Tag offsets metadata file for locating tags within a blob.')
    parser.add_argument('-i', '--input',   required=True, help='Input blob file, containing tags to be patched.')
    parser.add_argument('-o', '--output',  required=True, help='Output blob file, with patched tag binary data.')
    parser.add_argument('--allow-missing',    action='store_true', default=False, help='Treats missing tags from taginfo file as warnings instead of errors.')
    parser.add_argument('--allow-duplicates', action='store_true', default=False, help='When loading NVM files, allows a tag to be present more than once (processed in order).')
    parser.add_argument('--tcfx', required=True, help='TCFX Input File')

    # NVM file list
    parser.add_argument('nvm_files', nargs='+', help='List of NVMX files to apply as patches.')

    return parser


def main():
    parser = setup_argparse()
    args = parser.parse_args()

    patcher = TagBlobPatcher()

    # Right now this is manually copying things over. TBD whether we switch over to using
    # a for-each w/ args.vars() and setattr(patcher, ...)
    patcher.file_format      = args.file_format
    patcher.taginfo          = args.taginfo
    patcher.input            = args.input
    patcher.output           = args.output
    patcher.allow_missing    = args.allow_missing
    patcher.allow_duplicates = args.allow_duplicates
    patcher.tcfx             = args.tcfx
    patcher.nvm_files        = args.nvm_files
    
    return patcher.generate()

if __name__ == '__main__':
    ret = main()
    exit(ret)
