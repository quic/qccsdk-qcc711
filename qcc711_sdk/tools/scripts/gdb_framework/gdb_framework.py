#===============================================================================
# Copyright (c) 2020-2021 Qualcomm Technologies, Inc.
# All Rights Reserved.
# Confidential and Proprietary - Qualcomm Technologies, Inc.
#===============================================================================
import argparse
import importlib
import os
import sys
import gdb_client
import re

class GDB_Framework(object):
    '''
    Base class for a GDB tool
    '''
    def __init__(self):
        '''
        Initializer for the GDB Framework. This will parse all the arguments and
        initialize the GDB server and client objects.
        '''
        if not self.ToolDescription:
            self.ToolDescription = 'GDB Tool Framework'

        # Add in the base arguments.
        self.argparser = argparse.ArgumentParser(description=self.ToolDescription)
        self.argparser.add_argument('-s', '--server', default='segger', help='GDB server being used.  This should match the name of a "gdb_server_<SERVER>.py" script (default=segger).')
        self.argparser.add_argument('-p', '--server-port', type=int, default=28038, help='GDB server port number.')
        self.argparser.add_argument('-c', '--client-exe', default='arm-none-eabi-gdb-py', help='GDB client executable.')
        self.argparser.add_argument('-u', '--udp-port', type=int, default=19383, help='UDP port for IPC traffic to the GDB client.')
        self.argparser.add_argument('-l', '--client-log', default=None, help='Log file for the GDB client output. Use "stdout" to display to the console.')

        # Add the tool specific arguments
        self.add_arguments()

        # Get the GDB server script and add its arguments.
        config, unknown = self.argparser.parse_known_args()
        self.server_module = importlib.import_module('gdb_framework.gdb_server_' + config.server)
        self.server_module.add_arguments(self.argparser)

        # Parse all the arguments.
        self.config = self.argparser.parse_args().__dict__

        # Create the GDB server and client objects.
        self.server = self.server_module.GDB_Server(**self.config)
        self.client = gdb_client.GDB_Client(self.config['server_port'], self.config['client_exe'], self.config['udp_port'], self.config['client_log'])

    def add_arguments(self):
        '''
        Stub function for tool specific arguments.
        '''
        pass

    def setup(self, script='"qcc710_apps.JLinkScript"'):
        '''
        Performs the common tool initilization including parsing arguments and
        initializing the GDB server and client.

        Parameters:
            parser: argparse object used for parsing the command line arguments.

        Returns:
            A tuple of the arguments object returne from argparse and the method
            used to send commands to the GDB client.
        '''
        # Start the server and client.
        try:
            print('Python ' + sys.version)
            print('********************************************************************************')
            print('********************************************************************************')

            print('Starting GDB Server...')
            self.server.start(script)
            print('********************************************************************************')
            print('Starting GDB Client...')
            self.client.start()
            print('********************************************************************************')

            # Perform the server specific setup
            print('Initializing GDB...')
            self.init_gdb()
            print('********************************************************************************')
            print('********************************************************************************')
        except:
            self.cleanup()
            raise

    def init_gdb(self):
        '''
        Common GDB initialization.
        '''
        self.gdb_execute('target remote localhost:{0}'.format(self.config['server_port']))
        self.server.client_setup(self.client)
        self.execute('import struct')
        self.execute('inferior = gdb.selected_inferior()')

    def cleanup(self):
        '''
        Performs common tool cleanup.
        '''
        try:
            self.client.stop()
        except:
            pass

        try:
            self.server.stop()
        except:
            pass

    def execute(self, *args, **kwargs):
        '''
        Executes a command on the GDB Client.

        Parameters:
            command: string representation of the command to execute on the GDB
                     client. This will be passed into exec().
            timeout: Time in seconds for the operation to complete. This can be
                     used to set a longer timeout if the operation is expected
                     to take time to complete.
        '''
        self.client.execute(*args, **kwargs)

    def evaluate(self, *args, **kwargs):
        '''
        Evaluates a command on the GDB Client.

        Parameters:
            command: string representation of the command to execute on the GDB
                     client. This will be passed into eval().
            timeout: Time in seconds for the operation to complete. This can be
                     used to set a longer timeout if the operation is expected
                     to take time to complete.

        Returns:
            The result of the evaluation
        '''
        return self.client.evaluate(*args, **kwargs)

    def gdb_execute(self, command, *args, **kwargs):
        '''
        Execute the GDB command in the GDB client.

        Parameters:
            command: GDB command to execute.
            timeout: Time in seconds for the operation to complete. This can be
                     used to set a longer timeout if the operation is expected
                     to take time to complete.
        '''
        self.execute('gdb.execute("{}")'.format(command), *args, **kwargs)

    def get_symbol_info(self, symbol):
        '''
        Gets the address for a symbol

        Parameters:
            symbol: Symbol to query.

        Returns:
            A tuple of the address and size of the symbol
        '''
        result = {}
        self.execute('temp=gdb.lookup_symbol("{}")[0]'.format(symbol))
        result['name'] = self.evaluate('temp.name')
        result['address'] = self.evaluate('int(temp.value().address)')
        result['type'] = self.evaluate('str(temp.type)')
        result['is_function'] = self.evaluate('temp.is_function')

        if not result['is_function']:
            result['size'] = self.evaluate('int(temp.type.sizeof)')

        return result

    def read_int(self, address, size=None):
        '''
        Reads an integer value

        Parameters:
            address: Address or symbol name to read.
            size:    Size of the integer to read (default=4). If not specified
                     and the address is a symbol name, the size of the symbol
                     will be used.

        Returns:
            The value of the integer.
        '''
        if isinstance(address, str):
            # Address is a string so resolve it as a symbol
            symbol = self.get_symbol_info(address)
            address = symbol['address']

            if ('size' in symbol) and (not size):
                size = symbol['size']

        if not size:
            size = 4

        if size > 8:
            raise ValueError('Size too large to read as an integer.')

        # Read the contents back and convert it to an integer
        value_buffer = self.evaluate('list(inferior.read_memory(0x{:08X}, {}))'.format(address, size))
        hex_string = ''.join('{:02x}'.format(ord(byte)) for byte in reversed(value_buffer))

        return int(hex_string, 16)

    def read_buf(self, address, length=None):
        '''
        Reads a region of memory

        Parameters:
            address: Address or symbol name to read.
            length:  Amount of data to read. If not specified and the address
                     is a symbol name, the size of the symbol will be used.
                     This must be specified if the address is an integer.

        Returns:
            List of bytes that were read.
        '''
        if isinstance(address, str):
            # Address is a string so resolve it as a symbol
            symbol = self.get_symbol_info(address)
            address = symbol['address']
            if not length:
                length = symbol['size']
        elif not length:
            raise(ValueError('length must be specified'))

        value_buffer = self.evaluate('list(inferior.read_memory(0x{:08X},{}))'.format(address, length))

        return [ord(byte) for byte in value_buffer]

    def write_int(self, address, value, size=None):
        '''
        Writes an integer value

        Parameters:
            address: Address or symbol name to write.
            value:   Value to write.
            size:    Size of the integer to write (default=4). If not
                     specified and the address is a symbol name, the size of
                     the symbol will be used.
        '''
        if isinstance(address, str):
            # Address is a string so resolve it as a symbol
            symbol = self.get_symbol_info(address)
            address = symbol['address']

            if ('size' in symbol) and (not size):
                size = symbol['size']
        elif not size:
            size = 4

        if size > 8:
            raise ValueError('Size too large to write as an integer.')

        self.execute('inferior.write_memory(0x{:08X},struct.pack("<Q",{})[:{}])'.format(address, str(value), str(size)))

    def write_buf(self, address, buffer):
        '''
        Writes a buffer to memory

        Parameters:
            address: Address or symbol name to write.
            buffer:  List of byte values to write.
        '''
        if isinstance(address, str):
            # Address is a string so resolve it as a symbol
            symbol = self.get_symbol_info(address)
            address = symbol['address']

        self.execute('inferior.write_memory(0x{:08X},"".join(chr(byte) for byte in {}))'.format(address, str(buffer)))

    def load_elf(self, filename, vector_address=0x20014000):
        '''
        Loads an elf file and writes it to the device.

        Parameters:
            filename: Name of the elf file to load.
        '''

        # Load the elf file.
        self.gdb_execute('file {}'.format(filename.replace(os.sep, '/')))
        self.gdb_execute('load')

        # Set stack pointer, program counter and VTOR
        self.gdb_execute('set $sp=0x{:08X}'.format(self.read_int(vector_address)))
        self.gdb_execute('set $pc=0x{:08X}'.format(self.read_int(vector_address + 4)))

    def load_bin(self, filename, address):
        '''
        Loads an binary file and writes it to the address specified.

        Parameters:
            filename: Name of the binary file to load.
            address:  Address for the binary file to be written.
        '''
        # Load the bin file.
        self.gdb_execute('restore {} binary 0x{:08X}'.format(filename.replace(os.sep, '/'), address))
