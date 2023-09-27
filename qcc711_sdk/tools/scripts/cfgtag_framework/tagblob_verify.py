################################################################################
# NVM Cfg Tag offsets verification utility
################################################################################
# Copyright (c) 2021 Qualcomm Technologies International, Ltd.
# All Rights Reserved
# Confidential and Proprietary - Qualcomm Technologies International, Ltd.
################################################################################

from tagblob import *

from offsets_fileformats import OffsetsFile

import argparse
from sys import exit


def setup_argparse():

    # Named Arguments:
    #  -b/--bin or -h/--hex for bin/hex parsing (exclusive, required)
    #  -t/--taginfo for offsets input file (required)
    #  -i/--input for input bin/hex (required)
    #  --tcfx for input TCFX (required)
    #  --ignore-missing in case missing tags from offsets file should be non-fatal (optional)

    parser = argparse.ArgumentParser(description='Patches a Config Tag NVM blob using tag files and offsets metadata.')

    # Add --bin/--hex options
    ftype_group = parser.add_mutually_exclusive_group(required=True)
    ftype_group.add_argument('-b', '--bin', dest='file_format', action='store_const', const='bin', help='Input config tag file is in binary format..')
    if hexfile:
        ftype_group.add_argument('-x', '--hex', dest='file_format', action='store_const', const='hex', help='Input config tag file is in ihex format.')

    # Positional arguments
    parser.add_argument('-t', '--taginfo', required=True, help='Tag offsets metadata file for locating tags within a blob.')
    parser.add_argument('-i', '--input',   required=True, help='Input blob file, containing tags to be compared against the tcfx.')
    parser.add_argument('--allow-missing', action='store_true', default=False, help='Treats missing tags from taginfo file as warnings instead of errors.')
    parser.add_argument('--tcfx',          required=True, help='TCFX Input File containing tag defaults.')

    return parser


def main():
    errors = 0
    parser = setup_argparse()
    args = parser.parse_args()

    # Read tag metadata
    print('Loading offsets information from {} ...'.format(args.taginfo))
    offsets_info = OffsetsFile.load_from(args.taginfo)
    if offsets_info is None:
        print('Error loading offsets metadata.')
        return 1

    # Read input blob
    if args.file_format == 'bin':
        blob = BinaryFile.load_from(args.input)
    elif args.file_format == 'hex':
        blob = IHexFile.load_from(args.input, offsets_info.base)
    else:
        raise NotImplementedError('Invalid file format specified.')

    print('Reading tag definitions from TCFX...')
    tcfx = load_tcfx(args.tcfx)

    # Build up a tag-number-to-tag dictionary
    tcfx_tag_dict = {}
    for tag in tcfx.tags:
        tcfx_tag_dict[tag.num] = tag

    print('Verifying tags...')
    tags = sorted(offsets_info.tags())

    for tag_num in tags:
        if tag_num not in tcfx_tag_dict:
            print('Tag number {} not in TCFX.'.format(tag_num))
            if not args.allow_missing:
                errors += 1

            # Tag is missing, so skip to the next tag offset defined.
            continue

        tag = tcfx_tag_dict[tag_num]
        tcfx_data = tcfx_tag_to_binary(tag)
        data_len = len(tcfx_data)

        blob_data = blob.get_data(offsets_info[tag_num], data_len)
        if tcfx_data == blob_data:
            print('Tag {}: validated {} bytes'.format(tag_num, data_len))
        else:
            print('Tag {} mismatch.'.format(tag_num))
            errors += 1

    if errors == 0:
        print('All tags validated successfully!')
        return 0

    print('Tags validated with {} error(s) found.'.format(errors))
    return 1


if __name__ == '__main__':
    ret = main()
    exit(ret)
