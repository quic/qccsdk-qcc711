#===============================================================================
# Copyright (c) 2020-2021 Qualcomm Technologies, Inc.
# All Rights Reserved.
# Confidential and Proprietary - Qualcomm Technologies, Inc.
#===============================================================================
import struct

class HexFile(object):
    '''
    Class for parsing, manipulating and writing the contents of a hex file.
    '''
    class HexBlock(object):
        '''
        Container for a continugous block of hex data.
        '''
        def __init__(self, address, data):
            '''
            Initializer for a HexBlock object

            address: Start address of the block
            data:    Data for the block
            '''
            self.address = address
            self.data = data

        def __len__(self):
            '''
            len() Handler for a HexBlock object.

            Returns the length of the data represented by the block
            '''
            return len(self.data)

        def start(self):
            '''
            Returns the starting address of the block.
            '''
            return self.address

        def end(self):
            '''
            Returns the end of the block (address of last byte + 1).
            '''
            return self.address + len(self.data)

    RECORD_TYPE_DATA = 0
    RECORD_TYPE_END_OF_FILE = 1
    RECORD_TYPE_EXTENDED_SEGMENT_ADDRESS = 2
    RECORD_TYPE_START_SEGMENT_ADDRESS = 3
    RECORD_TYPE_EXTENDED_LINEAR_ADDRESS = 4
    RECORD_TYPE_START_LINEAR_ADDRESS = 5

    RECORD_GROUP_DATA = 0
    RECORD_GROUP_END_OF_FILE = 1
    RECORD_GROUP_EXTENDED_ADDRESS = 2
    RECORD_GROUP_START_ADDRESS = 3

    FILE_TYPE_I8HEX = 8
    FILE_TYPE_I16HEX = 16
    FILE_TYPE_I32HEX = 32

    PARSE_MAP = {
        RECORD_TYPE_DATA:{'type':FILE_TYPE_I8HEX, 'group':RECORD_GROUP_DATA},
        RECORD_TYPE_END_OF_FILE:{'type':FILE_TYPE_I8HEX, 'group':RECORD_GROUP_END_OF_FILE},
        RECORD_TYPE_EXTENDED_SEGMENT_ADDRESS:{'type':FILE_TYPE_I16HEX, 'group':RECORD_GROUP_EXTENDED_ADDRESS},
        RECORD_TYPE_START_SEGMENT_ADDRESS:{'type':FILE_TYPE_I16HEX, 'group':RECORD_GROUP_START_ADDRESS},
        RECORD_TYPE_EXTENDED_LINEAR_ADDRESS:{'type':FILE_TYPE_I32HEX, 'group':RECORD_GROUP_EXTENDED_ADDRESS},
        RECORD_TYPE_START_LINEAR_ADDRESS:{'type':FILE_TYPE_I32HEX, 'group':RECORD_GROUP_START_ADDRESS},
    }

    WRITE_MAP = {
        FILE_TYPE_I8HEX:{},
        FILE_TYPE_I16HEX:{
            RECORD_GROUP_EXTENDED_ADDRESS:RECORD_TYPE_EXTENDED_SEGMENT_ADDRESS,
            RECORD_GROUP_START_ADDRESS:RECORD_TYPE_START_SEGMENT_ADDRESS
        },
        FILE_TYPE_I32HEX:{
            RECORD_GROUP_EXTENDED_ADDRESS:RECORD_TYPE_EXTENDED_LINEAR_ADDRESS,
            RECORD_GROUP_START_ADDRESS:RECORD_TYPE_START_LINEAR_ADDRESS
        },
    }

    def __init__(self, filename=None):
        '''
        Constructor for a HexFile object.

        Parameters:
            filename: Hex file to read
        '''
        if filename:
            self.__parse_file(filename)
        else:
            self.blocks = []
            self.file_type = HexFile.FILE_TYPE_I8HEX
            self.start = None

    def __len__(self):
        return (self.blocks[-1].end() - self.blocks[0].start()) if self.blocks else 0

    def __parse_file(self, filename):
        '''
        Parses a hex file.

        filename: Name of the file to parse.
        '''
        self.file_type = HexFile.FILE_TYPE_I8HEX
        self.start = None
        self.blocks = []

        # Parse the individual lines of the hex file.
        with open(filename, 'r') as file:
            line_list = file.readlines()

        # Remove any empty lines from the list. Keep the original line number
        # for error reporting
        line_list = [line.strip() for line in line_list]
        line_list = [(num, line) for num, line in enumerate(line_list, 1) if line]

        # Parse the lines
        end_reached = False
        ext_addr = 0
        line_data = []
        for number, line in line_list:
            try:
                if end_reached:
                    raise Exception('Line after End Of File record')

                if line[0] != ':':
                    raise Exception('Invalid start of line')

                # Verify the checksum
                if (sum(list(bytearray.fromhex(line[1:]))) % 0x100) != 0:
                    raise Exception('Invalid Checksum')

                # Parse the line
                length = int(line[1:3], 16)
                address = int(line[3:7], 16)
                command = int(line[7:9], 16)
                data = line[9:-2]

                if (length * 2) != len(data):
                    raise Exception('Invalid line length'.format(number))

                # Process the line
                info = HexFile.PARSE_MAP[command]

                # Validate the record type
                if info['type'] > self.file_type:
                    self.file_type = info['type']

                # Process the command
                if info['group'] == HexFile.RECORD_GROUP_DATA:
                    line_data.append([number, ext_addr + address, bytearray.fromhex(data)])
                elif info['group'] == HexFile.RECORD_GROUP_END_OF_FILE:
                    end_reached = True
                elif info['group'] == HexFile.RECORD_GROUP_EXTENDED_ADDRESS:
                    if (length != 2):
                        raise Exception('Invalid line')

                    ext_addr = int(data, 16) * 0x10000
                elif info['group'] == HexFile.RECORD_GROUP_START_ADDRESS:
                    if (length != 4):
                        raise Exception('Invalid line')

                    if self.start != None:
                        raise Exception('Duplicate start address record')

                    self.start = int(data, 16)
            except:
                print('Error parsing line {}'.format(number))
                raise

        if not end_reached:
            raise Exception('No End Of File record found')

        # Merge lines where possible and form a final list of contiguous blocks.
        next_addr = -1
        for line in sorted(line_data, key=lambda _line: _line[1]):
            # Check for duplicate address. As the list is sorted, the address of
            # the current line will only be less than the end of the previous
            # line if there is overlap.
            if line[1] < next_addr:
                print('Error parsing line {}'.format(line[0]))
                raise Exception('Duplicate address')

            if line[1] == next_addr:
                # Merge with the previous block
                self.blocks[-1].data += line[2]
                next_addr += len(line[2])
            else:
                # Add as a new block
                self.blocks.append(HexFile.HexBlock(line[1], line[2]))
                next_addr = line[1] + len(line[2])

    def __check_overlap(self, address, length):
        '''
        Checks for any overlap between the current hex data and the address and
        length specified

        Parameters:
            address: Starting address of the range to check.
            length:  Length of the range to check
        '''
        for block in self.blocks:
            if (address < block.end()) and ((address + length) > block.start()):
                print(hex(block.address))
                raise Exception('Data overlaps with existing data.')

    def __write_line(self, file, command, address, data):
        '''
        Formats a single hex line.

        Parameters:
            file:    File to write the line to.
            command: Record type of the line.
            address: Address of the line.
            data:    Data for the line.
        '''
        line_data = bytearray(struct.pack('>BHB', len(data), address, command)) + data
        line_data += bytearray([(-sum(bytearray(line_data))) % 0x100])

        file.write(':')
        file.write(''.join(['{:02X}'.format(byte) for byte in line_data]))
        file.write('\n')

    def write_hex(self, filename, line_length=16):
        '''
        Writes the hex data to a hex file.

        Parameters:
            filename: Name of the file to create.
        '''
        # adjust the file type if necessary.
        file_type = self.file_type if 'file_type' in self.__dict__ else HexFile.FILE_TYPE_I8HEX
        if (file_type == HexFile.FILE_TYPE_I8HEX) and (self.end_address() > 0x10000):
            file_type = HexFile.FILE_TYPE_I32HEX

        info = HexFile.WRITE_MAP[file_type]

        with open(filename, 'w') as file:
            cur_ext_addr = -1
            for block in self.blocks:
                offset = 0
                while offset < len(block):
                    # calculate the address and length of the line
                    address = block.start() + offset
                    ext_addr = address >> 16
                    address = address & 0xFFFF
                    line_len = min(line_length, 0x10000 - address)

                    if (ext_addr != cur_ext_addr) and (file_type != HexFile.FILE_TYPE_I8HEX):
                        # Write the new extended address
                        self.__write_line(file, info[HexFile.RECORD_GROUP_EXTENDED_ADDRESS], 0, struct.pack('>H', ext_addr))
                        cur_ext_addr = ext_addr

                    self.__write_line(file, HexFile.RECORD_TYPE_DATA, address, block.data[offset:offset + line_len])
                    offset += line_len

            # Write the start address if present
            if self.start != None:
                self.__write_line(file, info[HexFile.RECORD_GROUP_START_ADDRESS], 0, struct.pack('>I', self.start))

            # Write the end of file
            self.__write_line(file, HexFile.RECORD_TYPE_END_OF_FILE, 0, b'')

    def write_bin(self, filename, address=None, length = None, byte=b'\xFF'):
        '''
        Write the data in the hex file to a binary file.

        *Note* If the address and length are not specified, this function will
               try to return all the hex data as a single contiguous buffer. If
               the object blocks in very different address spaces, this can
               create very large files (up to 4GB).

        filename: Binary file to create.
        address:  Address of data to write. Defaults to the beginning of the hex
                  data.
        length:   Amount of data to writes. Defaults to write until the end of
                  the hex data.
        fill:     Byte value to use for any gaps in the hex data.
        '''
        if address == None:
            address = self.blocks[0].start() if self.blocks else 0

        if length == None:
            length = (self.blocks[-1].end() - address) if self.blocks else 0

        if len(byte) != 1:
            raise ValueError('Invalid fill byte')

        data_end = address + length
        with open(filename, 'wb') as file:
            for block in self.blocks:
                # Write fill bytes for anything before the block
                if address < block.start():
                    write_len = min(data_end, block.start()) - address
                    file.write(byte * write_len)
                    address += write_len

                # Write any bytes from the block
                if block.start() <= address < block.end():
                    offset = address - block.start()
                    write_len = min(data_end, block.end()) - address
                    file.write(block.data[offset:offset + write_len])
                    address += write_len

                # break out early if everything has been written
                if address == data_end:
                    break

            # Write fill bytes for anything after the last block
            if address < data_end:
                file.write(byte * (data_end - address))

    def start_address(self):
        '''
        Returns the starting address for the data in the HexFile object.
        '''

        return self.blocks[0].start() if self.blocks else 0

    def end_address(self):
        '''
        Returns the end address for the data in the HexFile object.
        '''
        return (self.blocks[-1].end() - 1) if self.blocks else 0

    def offset_address(self, offset):
        '''
        Applies an offset to the address of the data in the hex file

        offset: Offset to apply to the address of the hex data as a signed
                integer.
        '''
        # Verify the offset is valid
        if self.blocks:
            if ((self.blocks[0].start() + offset) < 0) or ((self.blocks[-1].end() + offset) > 0x100000000):
                raise ValueError('Invalid offset')

        # Apply the offset
        for block in self.blocks:
            block.address += offset

    def block_list(self):
        '''
        Returns a list of blocks in the HexFile object. Each block will be
        represented as a tuple of the starting address of the block and its
        length.
        '''
        return [(block.start(), len(block)) for block in self.blocks]

    def get(self, address=None, length=None, byte=b'\xFF'):
        '''
        Returns a bytearray containing the data at the specified address.

        *Note* If the address and length are not specified, this function will
               try to return all the hex data as a single contiguous buffer. If
               the object blocks in very different address spaces, this can
               cause hanging for long periods and memory errors.

        Parameters:
            address: Address of data to read. Defaults to the beginning of the
                     hex data.
            length:  Amount of data to read. Defaults to fill to the end of the
                     hex data.
            byte:    Value for bytes that aren't in the hex data.
        '''
        if address == None:
            address = self.blocks[0].start() if self.blocks else 0

        if length == None:
            length = (self.blocks[-1].end() - address) if self.blocks else 0

        if len(byte) != 1:
            raise ValueError('Invalid fill byte')

        data_end = address + length
        data = bytearray()
        for block in self.blocks:
            # Fill in any bytes that are before the block
            if address < block.start():
                copy_len = min(data_end, block.start()) - address
                data += byte * copy_len
                address += copy_len

            # Copy any bytes from the block
            if block.start() <= address < block.end():
                offset = address - block.start()
                copy_len = min(data_end, block.end()) - address
                data += block.data[offset:offset + copy_len]
                address += copy_len

            # break out early if everything has been copied
            if address == data_end:
                break

        # fill any data remaining at the end
        if address < data_end:
            data += byte * (data_end - address)

        return data

    def merge(self, hex_file):
        '''
        Merges the contents of another hex file into this one. This does not
        allow overlaps. The start value of the specified HexFile object will be
        used if the value in the current object is not set.

        hex_file:      HexFile object to merge.
        '''
        for block in hex_file.blocks:
            self.__check_overlap(block.start(), len(block))

        for block in hex_file.blocks:
            self.modify(block.start(), block.data)

        if self.start == None:
            self.start = hex_file.start

    def add(self, address, data):
        '''
        Add new data to the HexFile object.  An exception will be raised if the
        new data will overlap existing data.

        Parameters:
            address: Address of the new data.
            data:    The new data as a list, bytearray, or string.
        '''
        # make sure the data doesn't overlap with any existing data.
        self.__check_overlap(address, len(data))

        # use HexFile.modify to handle the rest
        self.modify(address, data)

    def modify(self, address, data):
        '''
        Adds or modifies data in the HexFile object.

        Parameters:
            address: Address of the new data.
            data:    The new data as a list, bytearray, or string.
        '''
        data = bytearray(data)
        data_end = address + len(data)
        for index, block in enumerate(self.blocks):
            # Determine if the modify area will overlap or touch the current
            # block
            if (address <= block.end()) and (data_end >= block.start()):
                # Join with the current block.
                new_data = bytearray()
                if address > block.start():
                    # use the beginning of the existing block.
                    new_data = block.data[:address - block.start()]

                new_data += data

                if data_end < block.end():
                    # use the end fo the existing block
                    new_data += block.data[-(block.end() - data_end):]

                block.data = new_data
                block.address = min(address, block.start())

                # Determine if we need to merge with the next block
                while ((index + 1) < len(self.blocks)) and (self.blocks[index + 1].start() <= block.end()):
                    offset = block.end() - self.blocks[index + 1].start()
                    block.data += self.blocks[index + 1].data[offset:]
                    del self.blocks[index + 1]

                data = None
                break
            elif address < block.start():
                # Modify area is before the current block so just add a new
                # block
                self.blocks.append(HexFile.HexBlock(address, data))
                self.blocks.sort(key=lambda Block: Block.address)
                data = None
                break

        if data:
            # data is after the last block so just add it on.
            self.blocks.append(HexFile.HexBlock(address, data))

    def delete(self, address, length):
        '''
        Removes data from the HexFile object.

        Parameters:
            address: Address of the data to remove.
            length:  Amount of data to remove.
        '''
        end_addr = address + length
        for block in self.blocks:
            if end_addr < block.start():
                break

            if address < block.start():
                address = block.start()

            if address <= block.end():
                # remove data from this block
                del_len = min(end_addr, block.end()) - block.start()
                if address == block.start():
                    # Remove data from the beginning of the block
                    del block.data[:del_len]
                    block.address += del_len
                elif end_addr >= block.end():
                    # Remove data from the end of the block
                    del block.data[address - block.start():]
                else:
                    # Remove data from the middle of the block. This means
                    # splitting the block in two.
                    self.blocks.append(HexFile.HexBlock(end_addr, block.data[-(block.end() - end_addr):]))
                    del block.data[address - block.start():]
                    break

        # Remove any empty blocks
        index = 0
        while index < len(self.blocks):
            if not self.blocks[index].data:
                del self.blocks[index]
            else:
                index += 1

        # Resort the data in case a block was added
        self.blocks.sort(key=lambda block: block.start())

    def remove_start(self):
        '''
        Removes the start register value from the HexFile object.
        '''
        self.start = -1

    def fill(self, address=None, length=None, byte=b'\xFF'):
        '''
        Fils in any gaps in the hex data.

        *Note* If the address and length are not specified, this function will
               try to fill all gaps between blocks. If the object blocks in very
               different address spaces, this can cause hanging for long periods
               and memory errors.

        Parameters:
            address: Starting address to fill. Defaults to the beginning of the
                     hex data.
            length:  Amount of data to fill. Defaults to fill to the end of the
                     hex data.
            fill:    Value for bytes that aren't in the hex data.
        '''
        if address == None:
            address = self.start_address()

        if length == None:
            length = self.end_address() - address

        if len(byte) != 1:
            raise ValueError('Invalid fill byte')

        if self.blocks:
            # insert a new block for any gaps
            data_end = address + length
            new_blocks = []
            for block in self.blocks:
                if address < block.start():
                    fill_len = min(data_end, block.start()) - address
                    new_blocks.append(HexFile.HexBlock(address, byte * fill_len))
                    address = block.end()

                if data_end <= block.end():
                    break
                else:
                    address = max(address, block.end())

            if data_end > self.blocks[-1].end():
                # fill area goes beyond the last block
                address = max(address, self.blocks[-1].end())
                new_blocks.append(HexFile.HexBlock(address, byte * (data_end - address)))


            # Merge the new blocks
            self.blocks += new_blocks
            self.blocks.sort(key=lambda block: block.start())

            index = 0
            while (index + 1) < len(self.blocks):
                if self.blocks[index].end() == self.blocks[index + 1].start():
                    self.blocks[index].data += self.blocks[index + 1].data
                    del self.blocks[index + 1]
                else:
                    index += 1
        else:
            # There are currently no blocks so just add a new block.
            self.blocks.append(HexFile.HexBlock(address, byte * length))

