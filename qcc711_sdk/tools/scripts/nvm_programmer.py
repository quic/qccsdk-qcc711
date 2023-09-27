#===============================================================================
# Copyright (c) 2020-2021 Qualcomm Technologies, Inc.
# All Rights Reserved.
# Confidential and Proprietary - Qualcomm Technologies, Inc.
#===============================================================================
from __future__ import print_function
from gdb_framework import hexfile
import binascii
import os

from gdb_framework.gdb_framework import GDB_Framework

import socket
from socket import SOCK_DGRAM

class VerifyError(Exception):
    pass

class NVM_Programmer(GDB_Framework):
    ERROR_MAP = {
        0:"Success",
        1:"Failed",
        2:"Invalid Address",
        3:"Busy",
        4:"Update Package Authentication Failure",
        5:"Invalid Update Package",
        6:"Update Package Image Overlap",
    }

    DEFAULT_RAM_IMAGE = '../bin/nvm_programmer.elf'

    def __init__(self):
        '''
        Initializes the GDB tool.
        '''
        # *** Tool description ***
        self.ToolDescription = 'NVM programming tool'

        super(NVM_Programmer, self).__init__()

        # *** Tool specific initialization ***
        pass

    def add_arguments(self):
        '''
        Add tool specific arguments.
        '''
        # *** Tool specific arguments ***
        self.argparser.add_argument(dest='input', help='File to program.')
        self.argparser.add_argument('-i', '--ram-image', default=NVM_Programmer.DEFAULT_RAM_IMAGE, help='Location of the tool application RAM image.')
        self.argparser.add_argument('-b', '--binary', default=None, metavar='ADDRESS', help='Indicates the input is a binary file.')
        self.argparser.add_argument('-U', '--update', default=False, action='store_true', help='Indicates the binary file is an update package. -b must be speicied when using this flag.')
        self.argparser.add_argument('-v', '--verify-update', default=False, action='store_true', help="Verified the binary as an update package but doesn't apply it. This is similar to the -U option but doesn't apply the update.")
        self.argparser.add_argument('-V', '--verify-all', default=False, action='store_true', help="Verified the binary as an update package and verify all images as if debug was going to be locked.")
        self.argparser.add_argument('--lock-debug', default=False, action='store_true', help='Lock debug mode')

    def run(self):
        '''
        Start tool.
        '''
        # Get the address of VerifyUpdate and ApplyUpdate if both -b and
        # -U options are specified
        if self.config['update'] and self.config['binary'] == None:
            self.argparser.print_help()
            sys.exit('-b must be specified if -U is used.')

        # Perform common tool setup
        self.setup()

        try:
            # *** Tool specific code ***
            self.init_ram_image(self.config['ram_image'])

            try:
                if self.config['binary']:
                    self.download(self.config['input'], True, int(self.config['binary'], 0))

                    if self.config['update']:
                       self.apply_update(self.config['input'], int(self.config['binary'], 0), self.config['lock_debug'])
                    elif self.config['verify_update'] or self.config['verify_all']:
                        self.verify_update(self.config['input'], int(self.config['binary'], 0), self.config['verify_all'])
                        print('Update package valid.')
                else:
                    self.download(self.config['input'])

            except:
                self.cleanup_ram_image()
                raise
            else:
                if not self.config['update']:
                    self.cleanup_ram_image()

            # *** End tool specific code ***
        except:
            raise
        finally:
            self.cleanup()

    def init_ram_image(self, ram_image=DEFAULT_RAM_IMAGE):
        '''
        Downloads a RAM applcation onto the target.

        Parameters:
            ram_image: path to the RAM image being downloaded and initialized.
        '''

        # Load the NVM programmer RAM image.
        self.load_elf(ram_image)
        self.gdb_execute('c')

        # Initialize the RAM app.
        self.result_buf = self.get_symbol_info('ResultBuffer')['address']
        self.param_buf = self.get_symbol_info('ParameterBuffer')['address']

        self.gdb_execute('call Initialize()')
        if self.read_int(self.result_buf):
            raise Exception('Intialization failed')

    def cleanup_ram_image(self):
        '''
        Cleans up the RAM application on the target.
        '''
        self.gdb_execute('call Cleanup()')

    def download(self, nvm_image, is_binary=False, bin_addr=0):
        '''
        Downloads and initialize a RAM applcation on the target.

        Parameters:
            nvm_image: path to the NVM image being programmed.
            is_binary: flag indicates if the NVM image is a bin file.
            bin_addr:  the start address where the bin file should be programmed.
        '''
        nvm_image = nvm_image.replace(os.sep, '/')

        # Get the address and size of the buffers.
        data_buf = self.get_symbol_info('DataBuffer')
        data_buf_addr = data_buf['address']
        data_buf_size = data_buf['size']

        if is_binary:
            bin_str = 'binary'
            hex_file = hexfile.HexFile()
            with open(nvm_image, 'rb') as file:
                hex_file.add(bin_addr, file.read())
        else:
            bin_str = ''
            hex_file = hexfile.HexFile(nvm_image)

        print('Programming {}'.format(nvm_image))

        # Loop through and program all blocks in the file.
        for start_address, size in hex_file.block_list():
            print('Programming {} bytes to 0x{:08X}'.format(size, start_address))

            # Determine the offset address of the data in the file. If
            # this is a binary file, the offset will be zero.
            if is_binary:
                file_offset = 0;
            else:
                file_offset = start_address

            write_len = data_buf_size

            # Transfer the image to data_buf_addr on target in pieces
            # and program them into NVM
            address = start_address
            length = size
            try:
                while length:
                    if write_len > length:
                        write_len = length

                    # Load the next block of the image into the DataBuffer
                    self.gdb_execute('restore {} {} {} 0x{:08X} 0x{:08X}'.format(nvm_image, bin_str, data_buf_addr - file_offset, file_offset, file_offset + write_len))

                    # Execute the Write command and verify the result
                    self.write_int(self.param_buf, address)
                    self.write_int(self.param_buf + 4, write_len)
                    self.gdb_execute('call Write()')
                    if self.read_int(self.result_buf):
                        raise Exception('Write operation failed')

                    address += write_len
                    file_offset += write_len
                    length -= write_len
                    print('.', end='')
            except:
                raise
            finally:
                print()

            # Get the checksum of what was programmed
            self.write_int(self.param_buf, start_address)
            self.write_int(self.param_buf + 4, size)
            self.gdb_execute('call Checksum()')
            crc_result = self.read_int(self.result_buf + 4)

            # Compare the checksum
            image_crc = binascii.crc32(hex_file.get(start_address, size)) & 0xFFFFFFFF
            if crc_result != image_crc:
                raise Exception('CRC32 verification failed.')

            print('Image programmed successfully.')

    def verify_update(self, nvm_image, bin_addr, verify_all=False):
        '''
        Verify the update image.
        '''
        print('Verifying update...')
        self.write_int(self.param_buf, bin_addr)
        with open(nvm_image, 'rb') as file:
            self.write_int(self.param_buf + 4, len(file.read()))

        if verify_all:
            self.write_int(self.param_buf + 8, 1)
        else:
            self.write_int(self.param_buf + 8, 0)

        # Verify the update package
        self.gdb_execute('call VerifyUpdate()')
        result = self.read_int(self.result_buf)
        if result:
            raise VerifyError(NVM_Programmer.ERROR_MAP[result])

    def apply_update(self, nvm_image, bin_addr, lock_debug=False):
        '''
        Verify and apply the update image.
        '''
        self.verify_update(nvm_image, bin_addr, lock_debug);

        print('Applying update...')
        self.write_int(self.param_buf, bin_addr)
        with open(nvm_image, 'rb') as file:
            self.write_int(self.param_buf + 4, len(file.read()))

        if lock_debug:
            self.write_int(self.param_buf + 8, 1)
        else:
            self.write_int(self.param_buf + 8, 0)

        try:
            self.gdb_execute('call ApplyUpdate()', 0.1)
        except socket.timeout:
            # socket.timeout is expected after ApplyUpdate
            pass

def main():
    '''
    Main entry point for the tool script.
    '''
    tool = NVM_Programmer()

    try:
        tool.run()
    except VerifyError as error:
        print('Update Verification Failed: {}!!!'.format(str(error)))

    print()

if __name__ == "__main__":
    main()
