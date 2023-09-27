# ===============================================================================
# Copyright (c) 2020-2021 Qualcomm Technologies, Inc.
# All Rights Reserved.
# Confidential and Proprietary - Qualcomm Technologies, Inc.
# ===============================================================================
# coding=utf-8
from gdb_framework.gdb_framework import GDB_Framework
import json
import sys
import os
import re
import math
import logging


class ACCESS:
    READ_ONLY = 1
    WRITE_ONLY = 2
    READ_WRITE = 3


class TYPE:
    SINGLE = 1
    MULTIPLE = 2


class FIELD_TYPE:
    OTP = 1
    MTP = 2


class Scope():
    """
    Describe OTP Field address info
    """
    def __init__(self, address, offset, length):
        self.address = address
        self.offset = offset
        self.length = length


class Ziggy_OTP_Field(object):
    def __init__(self, name, scopes, access, field_type):
        self.__name = name
        self.__scopes = scopes
        self.__access = access
        self.__field_type = field_type

    @property
    def scopes(self):
        return self.__scopes

    @property
    def size(self):
        length = 0
        for scope in self.scopes:
            length += scope.length
        return length

    @property
    def access(self):
        return self.__access

    @property
    def type(self):
        register_number = 0
        for scope in self.scopes:
            register_number += (scope.offset + scope.length + 31) // 32

        if register_number == 1:
            return TYPE.SINGLE
        else:
            return TYPE.MULTIPLE

    @property
    def name(self):
        return self.__name

    @property
    def field_type(self):
        return self.__field_type


access_mapping = {
    'READ_ONLY': ACCESS.READ_ONLY,
    'WRITE_ONLY': ACCESS.WRITE_ONLY,
    'READ_WRITE': ACCESS.READ_WRITE
}


class OTP_Program_Tool(GDB_Framework):
    def __init__(self):
        """
        Initializes the GDB tool.
        """
        # *** Tool description ***
        self.ToolDescription = 'OTP Program tool'
        super(OTP_Program_Tool, self).__init__()

        self.fields = []
        log_level = getattr(logging, self.config['log'])
        logging.basicConfig(level=log_level, format='%(funcName)s: %(message)s')

    def add_arguments(self):
        """
        Add tool specific arguments.
        """
        # *** Tool specific arguments ***
        self.argparser.add_argument('-i', '--ram-image', default='../bin/otp_tool.elf', help='Location of the RAM image to load')
        self.argparser.add_argument('-j', '--json', help='json file for OEM fuse field')
        self.argparser.add_argument('-f', '--secure-file', help='secured binary file')
        self.argparser.add_argument('--field_cfg', default='otp_field_list.json', help='json file for the field configuration')
        self.argparser.add_argument('--read', nargs='+', help='List of field name')
        self.argparser.add_argument('-w', '--write', nargs='+', help='List of key-value pairs of OTP tags to program')
        self.argparser.add_argument('--read-register', nargs='+', help='List of register address')
        self.argparser.add_argument('--write-register', nargs='+', help='List of address-value pairs of registers to program')
        self.argparser.add_argument('--log', default='INFO', choices=['INFO', 'DEBUG'], help='log level')

    def exec_otp_function(self, func):
        """
        Execute remote target function.

        Parameters:
            func: a string of calling function, like func().

        Returns:
            status of function result.
        """
        self.gdb_execute('call ' + func)
        res = self.read_buf('ResultBuffer', 1)[0]
        logging.debug('{} complete. result is {}.'.format(func, res))
        if res != 0:
            raise ValueError('{} OTP operation failed.'.format(func))

        return res

    def write_register(self, address, value):
        """
        Writing register value.

        Parameters:
            address: register address.
            value: register value should be written.
        """
        if address % 4:
            raise ValueError('Address is not 4 bytes alignment')

        self.write_int('FuseAddr', address)
        self.write_int('FuseVal', value)
        self.exec_otp_function('OtpWrite()')
        # Clear Buffer
        self.write_int('FuseAddr', 0)
        self.write_int('FuseVal', 0)

    def read_register(self, address):
        """
        Reading register value.

        Parameters:
            address: register address.

        Returns:
            register value.
        """
        if address % 4:
            raise ValueError('Address is not 4 bytes alignment')

        self.write_int('FuseAddr', address)
        self.exec_otp_function('OtpRead()')
        register_value = self.read_int('FuseVal')
        # Clear Buffer
        self.write_int('FuseAddr', 0)
        self.write_int('FuseVal', 0)
        return register_value

    def write_field(self, field, field_value):
        """
        Writing field value, field must be in a unique register.

        Parameters:
            field: an object with field information.
            field_value: field value should be written.
        """
        # There is only one scope in field
        for scope in field.scopes:
            current_field_value = 0
            if field.access != ACCESS.WRITE_ONLY and field.field_type == FIELD_TYPE.MTP:
                # Read the field before modifying it.
                current_field_value = self.read_register(scope.address)

                # Keep the bytes not planned for writing
                mask = 0xFFFFFFFF - (((1 << scope.length) - 1) << scope.offset)
                current_field_value &= mask

            logging.debug('current_field_value=0x{:08X}'.format(current_field_value))
            value = (field_value << scope.offset) | current_field_value
            logging.debug('FuseAddr=0x{:08X} FuseVal=0x{:08X}'.format(scope.address, value))
            self.write_register(scope.address, value)

    def read_field(self, field):
        """
        Reading field value, field must be in a unique register.

        Parameters:
            field: an object with field information.

        Returns:
            field value.
        """
        # There is only one scope in field
        for scope in field.scopes:
            mask_value = ((1 << scope.length) - 1) << scope.offset
            register_value = self.read_register(scope.address)
            logging.debug('FuseAddr=0x{:08X} FuseVal=0x{:08X}'.format(scope.address, register_value))
            field_value = (register_value & mask_value) >> scope.offset

            return field_value

    def write_address_multiple(self, field):
        """
        Writing all register addresses that field holds.

        Parameters:
            field: an object with field information.

        Returns:
            list of each field scope register number
        """
        register_num_list = []
        address = self.get_symbol_info('FuseArray')['address']
        for scope in field.scopes:
            register_num = 0
            last_address = scope.address + ((scope.offset + scope.length + 7) // 8)
            for register_address in range(scope.address, last_address, 4):
                logging.debug('FuseArray_address=0x{:08X} register_address=0x{:08X}'.format(address, register_address))
                self.write_int(address, register_address)
                register_num += 1
                address += 8

            register_num_list.append(register_num)

        return register_num_list

    def write_field_multiple(self, field, field_value):
        """
        Writing field value into multiple registers.

        Parameters:
            field: an object with field information.
            field_value: field value should be written.
        """
        register_num_list = self.write_address_multiple(field)
        address = self.get_symbol_info('FuseArray')['address'] + 4

        for scope, register_num in zip(field.scopes, register_num_list):
            scope_value = (field_value & ((1 << scope.length) - 1)) << scope.offset
            field_value >>= scope.length

            if field.access != ACCESS.WRITE_ONLY and field.field_type == FIELD_TYPE.MTP:
                last_address = scope.address + (register_num - 1) * 4
                last_offset = (scope.length + scope.offset) % 32
                # Read the overlapping fields and combine it with the value to write
                scope_value |= self.read_register(scope.address) & ((1 << scope.offset) - 1)
                current_value = (self.read_register(last_address) & (0xffffffff - ((1 << last_offset) - 1)))
                scope_value |= current_value << ((register_num - 1) * 32)

            logging.debug('scope_value=0x{0:0{1}X}'.format(scope_value, register_num * 8))

            for i in range(register_num):
                value = scope_value & 0xffffffff
                logging.debug('FuseArray_address=0x{:08X}, FuseVal=0x{:08X}'.format(address, value))
                self.write_int(address, value)
                scope_value >>= 32
                address += 8

        logging.debug('FuseSize=0x{:08X}'.format(sum(register_num_list)))
        self.write_int('FuseSize', sum(register_num_list))
        self.exec_otp_function('OtpWriteMultiple()')

        # Clear buffer. Don't use write_buf, it will raise a socket error if datagram is large.
        address = self.get_symbol_info('FuseArray')['address']
        for i in range(sum(register_num_list)):
            self.write_int(address, 0)
            self.write_int(address + 4, 0)
            address += 8
        self.write_int('FuseSize', 0)

    def read_field_multiple(self, field):
        """
        Reading field value from multiple registers.

        Parameters:
            field: an object with field information.

        Returns:
            field value
        """
        register_num_list = self.write_address_multiple(field)
        logging.debug('FuseSize=0x{:08X}'.format(sum(register_num_list)))
        self.write_int('FuseSize', sum(register_num_list))
        self.exec_otp_function('OtpReadMultiple()')

        address = self.get_symbol_info('FuseArray')['address'] + 4
        field_value = 0
        length = 0
        for scope, register_num in zip(field.scopes, register_num_list):
            scope_value = 0
            for i in range(register_num):
                value = self.read_int(address)
                logging.debug('FuseArray_value_address=0x{:08X}, FuseArray_value=0x{:08X}'.format(address, value))
                scope_value += value << (i * 32)
                address += 8
            logging.debug('scope_value=0x{0:0{1}X}'.format(scope_value, register_num * 8))
            field_value += ((scope_value >> scope.offset) & ((1 << scope.length) - 1)) << length
            length += scope.length

        # Clear buffer. Don't use write_buf, it will raise a socket error if datagram is large.
        address = self.get_symbol_info('FuseArray')['address']
        for i in range(sum(register_num_list)):
            self.write_int(address, 0)
            self.write_int(address + 4, 0)
            address += 8
        self.write_int('FuseSize', 0)

        return field_value

    def write_otp_value(self, field_name, field_value):
        """
        write OTP value.

        Parameters:
            field_name:  OEM field name.
            field_value: hex string as OEM field value.
        """
        field_value = int(field_value, 0)
        field_size = 0
        for field in self.fields:
            if field.name == field_name:
                if field.access == ACCESS.READ_ONLY:
                    raise TypeError('Field {} is not writable'.format(field.name))

                field_size = field.size
                if field.type == TYPE.MULTIPLE:
                    self.write_field_multiple(field, field_value)
                else:
                    self.write_field(field, field_value)

        if field_size:
            print('Field: {0} Value: 0x{1:0{2}X}'.format(field_name, field_value, (field_size + 3) / 4))
        else:
            raise TypeError('Field {} was not in config'.format(field_name))

    def write_otp_nonsecure(self, file_name):
        """
        Write OTP from json file.

        Parameters:
            file_name: json file.
        """
        if file_name:
            print('\n\n********************************************************************************')
            print('****************************  Writing OTP from file ****************************')
            print('********************************************************************************')

            with open(file_name, 'r') as f:
                field_dict = json.load(f)
            # *** writing each field from json file ***
            for field, value in field_dict.items():
                self.write_otp_value(field, value)

    def write_otp_tag(self, tag_list):
        """
        Write OTP by tag.

        Parameters:
            tag_list: List of key-value pairs of OTP tags to program
        """
        if tag_list:
            print('\n\n********************************************************************************')
            print('***********************   Writing OTP from command line  ***********************')
            print('********************************************************************************')

            for tag in tag_list:
                field_name, field_value = tag.split('=', 2)
                self.write_otp_value(field_name, field_value)

    def write_otp_secure(self, file_name):
        """
        Write secure OTP.

        Parameters:
            file_name: secured binary file
        """
        # *** Write secure OTP ***
        if file_name:
            print('\n\n********************************************************************************')
            print('******************************    Writing Secure OTP  **************************')
            print('********************************************************************************')

            length = os.path.getsize(file_name)
            print('Secure OTP File name: {}, length: {} bytes'.format(file_name, length))

            if length > 256 or length == 0:
                raise ValueError('file length {} fail'.format(length))

            self.load_bin(file_name, self.get_symbol_info('FuseArray')['address'])
            self.write_int('FuseSize', length)
            self.exec_otp_function('OtpSecureWrite()')

    def read_otp_field(self, field_list):
        """
        Read OEM Fuse Field value.

        Parameters:
            field_list: List of field name
        """
        if field_list:
            print('\n\n********************************************************************************')
            print('************************    Reading Non-Secure OTP  ****************************')
            print('********************************************************************************')

            for field_name in field_list:
                found = False
                for field in self.fields:
                    if field.name == field_name:
                        if field.access == ACCESS.WRITE_ONLY:
                            raise TypeError('Field {} is not readable'.format(field.name))

                        if field.type == TYPE.MULTIPLE:
                            value = self.read_field_multiple(field)
                        else:
                            value = self.read_field(field)

                        if found:
                            if field_value != value:
                                print('  WARNING!!! Field mismatch: Address {0:08X}, Value: 0x{1:0{2}X}'.format(field.scopes[0].address, value, (field.size + 3) / 4))
                        else:
                            found = True
                            field_value = value
                            print('Field: {0}, Value: 0x{1:0{2}X}'.format(field.name, field_value, (field.size + 3) / 4))

                if not found:
                    raise TypeError('Field {} was not in config'.format(field_name))

    def read_register_list(self, addr_list):
        """
        Reading register list value.

        Parameters:
            addr_list: List of register address.
        """
        if addr_list:
            print('\n\n********************************************************************************')
            print('***********************         Reading Register         ***********************')
            print('********************************************************************************')

            for addr in addr_list:
                addr = int(addr, 0)
                value = self.read_register(addr)
                print('Address: 0x{0:08X} Value: 0x{1:08X}'.format(addr, value))

    def write_register_list(self, addr_value_list):
        """
        Writing register list value.

        Parameters:
            addr_value_list: List of address-value pairs of register.
        """
        if addr_value_list:
            print('\n\n********************************************************************************')
            print('***********************         Writing Register         ***********************')
            print('********************************************************************************')

            for pair in addr_value_list:
                addr, value = pair.split('=', 2)
                addr = int(addr, 0)
                value = int(value, 0)
                print('Address: 0x{0:08X} Value: 0x{1:08X}'.format(addr, value))
                self.write_register(addr, value)

    def load_fields(self, file_name):
        """
        Load OTP and MTP fields from json file.

        Parameters:
            file_name: json file.
        """
        with open(file_name, 'r') as f:
            json_dict = json.load(f)

        for entry in json_dict['otp_fields']:
            name = entry['name']
            scope = Scope(int(entry['address'], 0), entry['offset'], entry['length'])
            access = access_mapping[entry['access']]
            self.fields.append(Ziggy_OTP_Field(name, [scope], access, FIELD_TYPE.OTP))

        for entry in json_dict['mtp_fields']:
            name = entry['name']
            scope = Scope(int(entry['address'], 0), entry['offset'], entry['length'])
            access = access_mapping[entry['access']]
            self.fields.append(Ziggy_OTP_Field(name, [scope], access, FIELD_TYPE.MTP))

    def run(self):
        """
        Start tool.
        """
        # Verify at least one read or write option was specified.
        # Otherwise, print out the help menu and exit.
        for config_option in ['json', 'write', 'read', 'write_register', 'read_register', 'secure_file']:
            if self.config[config_option] != None:
                break
        else:
            self.argparser.print_help()
            sys.exit()

        self.load_fields(self.config['field_cfg'])

        # Perform common tool setup
        self.setup()

        try:
            # *** Tool specific code ***

            # Load RAM symbols
            self.load_elf(self.config['ram_image'])
            self.gdb_execute('c')

            # Initialize IPC
            self.exec_otp_function('Initialize()')

            # Write OTP from json file.
            self.write_otp_nonsecure(self.config['json'])

            # Write secure OTP.
            self.write_otp_secure(self.config['secure_file'])

            # Write OTP by tag.
            self.write_otp_tag(self.config['write'])

            # Read OEM Fuse Field value.
            self.read_otp_field(self.config['read'])

            # Write Register.
            self.write_register_list(self.config['write_register'])

            # Read Register.
            self.read_register_list(self.config['read_register'])

            # *** End tool specific code ***
        except:
            raise
        finally:
            self.cleanup()


def main():
    """
    Main entry point for the tool script.
    """
    tool = OTP_Program_Tool()
    tool.run()


if __name__ == "__main__":
    main()
