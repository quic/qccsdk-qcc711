################################################################################
# File format support for offsets / symdefs files
################################################################################
# Copyright (c) 2021 Qualcomm Technologies International, Ltd.
# All Rights Reserved
# Confidential and Proprietary - Qualcomm Technologies International, Ltd.
################################################################################

from datetime import datetime

class OffsetsFile(object):
    def __init__(self, offsets=None, baseaddr=None):
        if offsets is None:
            self._offsets = {}
        else:
            self._offsets = offsets.copy()

        if baseaddr is None:
            self.base = 0
        else:
            self.base = baseaddr


    def set_tag(self, tagNum, offset):

        if not isinstance(tagNum, int): raise TypeError('tagNum must be an int')
        if not isinstance(offset, int): raise TypeError('offset must be an int')

        self._offsets[tagNum] = offset

    def get_tag(self, tagNum):
        # This will raise a KeyError if the tag is not present.
        return self._offsets[tagNum]

    def __setitem__(self, idx, value):
        self.set_tag(idx, value)

    def __getitem__(self, idx):
        return self.get_tag(idx)

    def tags(self):
        return self._offsets.keys()

    def save(self, filename, input_tcf_name=None):
        with open(filename, 'w') as f:

            # Write the header
            f.write('# <NVM Offsets>\n')
            time_str = datetime.now().strftime("%Y-%m-%d %H:%M:%S")
            if input_tcf_name is not None:
                f.write('# Generated on {} from {}\n'.format(time_str, input_tcf_name))
            else:
                f.write('# Generated on {}\n'.format(time_str))

            f.write('Base {}\n'.format(hex(self.base)))

            # Write each offset
            tagList = sorted(self._offsets.keys())

            for num in tagList:
                f.write('Tag {} = {}\n'.format(num, self._offsets[num]))

    @staticmethod
    def load_from(filename, strict=True):

        errors = 0
        obj = OffsetsFile()
        base_found = False

        with open(filename, 'r') as f:
            for idx, line in enumerate(f.readlines()):
                line = line.strip()

                # Skip comments
                if line.startswith('#'):
                    continue

                # Skip empty lines
                if len(line) == 0:
                    continue

                # Lines should be in 'Tag X = Y' format
                fields = line.split()
                try:
                    assert len(fields) > 1
                    if fields[0] == 'Tag':

                        if not base_found:
                            raise RuntimeError('Tag field present before Base.')

                        assert len(fields) == 4
                        assert fields[2] == '='

                        tagNum = int(fields[1])
                        offset = int(fields[3])

                        # Check for duplicates
                        if tagNum in obj._offsets:
                            raise KeyError()

                        obj.set_tag(tagNum, offset)

                    elif fields[0] == 'Base':
                        # Check if we've already encountered a base address
                        if base_found:
                            raise RuntimeError('Duplicate base address')

                        assert len(fields) == 2
                        obj.base = int(fields[1], 16)
                        base_found = True

                except RuntimeError as e:
                    print('Error: {} on line {}'.format(e, idx + 1))
                    errors += 1
                except KeyError:
                    print('Error: duplicate tag {} found on line {}'.format(tagNum, idx + 1))
                    errors += 1
                except:
                    print('Error: line {} has incorrect format'.format(idx + 1))
                    errors += 1

                    # Skip this line.
                    continue

        if not base_found:
            print('Warning: no base address found in offsets file.')
            return None

        # To prevent a botched update, do not return a usable object if we encountered any errors.
        if errors > 0:
            return None

        return obj


class SymDefsFile(object):

    # Declare the various symdefs types

    TYPE_SYMDEF = 0 # Generated from QC-LLVM and RVCT
    TYPE_SCL    = 1 # Converted as part of Scons build

    _type_map = {
        'symdef': TYPE_SYMDEF,
        'scl': TYPE_SCL,
    }

    def __init__(self, filename, filetype, strict=True):
        self.filename = filename
        self.filetype = filetype
        self.symbols = {}
        self.strict = strict

    def get_symbol(self, symbol):
        if symbol in self.symbols:
            return self.symbols[symbol]
        return None

    @staticmethod
    def load_from(filename, filetype, strict=True):
        symdefs = SymDefsFile(filename, filetype)
        symdefs._load()
        return symdefs

    @staticmethod
    def get_filetype(type_string):
        type_string = type_string.lower()

        if type_string in SymDefsFile._type_map:
            return SymDefsFile._type_map[type_string]

        raise ValueError('Invalid Symdefs filetype.')

    #
    # Helper functions to populate the self.symbols dictionary
    #

    def _load(self):
        with open(self.filename, 'r') as f:
            if self.filetype == SymDefsFile.TYPE_SYMDEF:
                return self._from_symdefs(f)
            elif self.filetype == SymDefsFile.TYPE_SCL:
                return self._from_scl(f)
            else:
                raise ValueError('Unsupported file type.')

    # RVCT-style symdefs (i.e. starts with #<SYMDEFS>)
    def _from_symdefs(self, f):
        # Symbols are in the format:
        # 0xADDR TYPE SymbolName
        # Lines that begin with a # are ignored

        for idx, line in enumerate(f.readlines()):

            # Split on repeated runs of whitespace instead of individual spaces
            args = line.split()

            if len(args) == 0:
                continue

            # Ignore comments
            if args[0].startswith('#'):
                continue

            if args[0].startswith('0x'):
                # Take everything directly
                address = int(args[0], 16)
                symname = args[2]
                
                self.symbols[symname] = address
            else:
                errmsg = 'Line {} does not start with an 0x format address'.format(idx + 1)
                if self.strict:
                    raise RuntimeError(errmsg)

                print('Warning: ' + errmsg)


    # Converted symdef-to-scl files (i.e. plain "symbol = 0xADDR;" style, usually has _conv in filename")
    def _from_scl(self, f):
        # Symbols are in the format:
        # SymbolName = 0xADDR; /* TYPE */
        # C-style comments (not parsed)

        for idx, line in enumerate(f.readlines()):

            # Split on repeated runs of whitespace instead of individual spaces
            args = line.split()

            # Ignore empty lines
            if len(args) == 0:
                continue

            # Split arguments should be symname <ignored> address; <ignored>+
            if len(args) < 3:
                errmsg = 'Line {} does not have the minimum fields to parse'.format(idx + 1)
                if self.strict:
                    raise RuntimeError(errmsg)

                print('Warning: ' + errmsg)
                continue

            if args[1] == '=' and args[2].startswith('0x') and args[2].endswith(';'):
                # Strip the trailing semicolon off the address, take everything else
                symname = args[0]
                address = int(args[2][:-1], 16)
                
                self.symbols[symname] = address
            else:
                errmsg = 'Line {} is not in address assignment format'.format(idx + 1)
                if self.strict:
                    raise RuntimeError(errmsg)

                print('Warning: ' + errmsg)
                print(args)
