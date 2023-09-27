# ===============================================================================
# Copyright (c) 2020-2021 Qualcomm Technologies, Inc.
# All Rights Reserved.
# Confidential and Proprietary - Qualcomm Technologies, Inc.
# ===============================================================================
# coding=utf-8
from nvm_programmer import NVM_Programmer, VerifyError
from otp_programmer import OTP_Program_Tool
from secure_programmer import SecureProgrammer
from secure_programmer import NVM_Uart
from gdb_framework.gdb_client import GDB_Client_Error
import socket
import json
import sys
import os
import time


class QCC710_Programmer(SecureProgrammer, OTP_Program_Tool):

    DEFAULT_RAM_IMAGE = '../bin/qcc710_programmer.elf'

    def __init__(self):
        """
        Initializes the GDB tool.
        """
        # *** Tool description ***
        self.ToolDescription = 'QCC710 Program tool'
        super(QCC710_Programmer, self).__init__()

    def add_arguments(self):
        """
        Add tool specific arguments.
        """
        # *** Tool specific arguments ***
        self.argparser.add_argument(dest='input', help='config JSON file for otp/mtp and image')
        self.argparser.add_argument('-i', '--ram-image', default=QCC710_Programmer.DEFAULT_RAM_IMAGE, help='Location of the tool application RAM image.')
        self.argparser.add_argument('-S', '--secure', default=False, action='store_true', help='Indicates programming secure image through config JSON file. --uart-port must be specified when using this flag.')
        self.argparser.add_argument('-V', '--verify-all', default=False, action='store_true', help="Verified the binary as an update package and verify all images as if debug was going to be locked.")
        self.argparser.add_argument('--uart-port', type=str, default=None, help='UART port for traffic to APSS')
        self.argparser.add_argument('--field_cfg', default='otp_field_list.json', help='json file for the field configuration')
        self.argparser.add_argument('--log', default='INFO', choices=['INFO', 'DEBUG'], help='log level')
        self.argparser.add_argument('--lock-debug', default=False, action='store_true', help='Lock debug mode')
        self.argparser.add_argument('--secure-boot', default=False, action='store_true', help='Enable secure boot')
        self.argparser.add_argument('--apply-time', type=float, default=3.0, help='Time needed for apply update. It depends on image size. The average NVM programming time is 100us/64bits.')

    def request_write_nvm(self):
        '''
        Request permissions to write to NVM.
        '''
        self.gdb_execute('call ReqWriteNvm()')
        if self.read_int(self.result_buf):
            raise Exception('Request NVM write failed')

    def release_write_nvm(self):
        '''
        Releases a request for NVM write permissions.
        '''
        self.gdb_execute('call RelWriteNvm()')

    def write_nvm(self, image_config, user_config, verify_all=False, lock_debug=False):
        '''
        Write image and user config to NVM, apply update.

        Parameters:
            image_config: image config options, such as image, address, update.
            user_config:  user config options, such as iamge, address.
            lock_debug:   lock debug or not.
        '''
        try:
            self.request_write_nvm()
            self.download(image_config['image'], True, int(image_config['address'], 0))
            if user_config['image']:
                self.download(user_config['image'], True, int(user_config['address'], 0))
            self.release_write_nvm()
            if verify_all:
                self.verify_update(image_config['image'], int(image_config['address'], 0), True)
            if image_config['update'] == 'True':
                self.apply_update(image_config['image'], int(image_config['address'], 0), lock_debug)
        except:
            self.cleanup_ram_image()
            raise

    def run(self):
        """
        Start tool.
        """
        # Check arguments. --uart-port must be specified if -S is used.
        if self.config['secure'] and self.config['uart_port'] == None:
            self.argparser.print_help()
            sys.exit('--uart-port must be specified if -S is used.')

        # Perform common tool setup
        self.setup()

        try:
            # *** Write none-secure OTP. Reset is needed after writing done ***

            # Download ram image
            self.init_ram_image(self.config['ram_image'])

            self.load_fields(self.config['field_cfg'])

            # Load config json file
            with open(self.config['input'], 'r') as f:
                json_dict = json.load(f)

            # Write OTP MTP values
            for field, value in json_dict['otp_config']['otp_mtp_values'].items():
                self.write_otp_value(field, value)

            # *** End writing none-secure OTP ***
        except:
            raise
        finally:
            self.cleanup()

        # Perform common tool setup
        self.setup()

        try:
            # *** Write secure OTP ***

            # Download ram image
            self.init_ram_image(self.config['ram_image'])

            # Write secure otp file
            self.write_otp_secure(json_dict['otp_config']['secure_file'])

            # *** End writing secure OTP ***
        except:
            raise
        finally:
            self.cleanup()

        # Perform common tool setup
        self.setup()

        try:
            # *** Write NVM image and user config image ***

            # Download ram image
            self.init_ram_image(self.config['ram_image'])

            image_config = {}
            if self.config['secure']:
                image_config = {'image': json_dict['image_config']['secure_config']['secure_loader_update'],
                                'address': str(SecureProgrammer.ADDRESS_TO_WRITE_LOADER_DEMO_IMAGE), 'update': 'True'}
            else:
                image_config = json_dict['image_config']['non_secure_config']

            self.write_nvm(image_config, json_dict['user_config'], self.config['verify_all'], self.config['lock_debug'])

            # *** End NVM image and user config image ***
        except:
            raise
        finally:
            self.cleanup()

        if self.config['secure']:
            uart_config = json_dict['image_config']['secure_config'].copy()
            uart_config.update(self.config)
            uart_config['address'] = int(json_dict['image_config']['secure_config']['address'], 0)
            nvm_uart_tool = NVM_Uart(uart_config)
            nvm_uart_tool.run()

        if self.config['secure_boot']:
            # Wait for apply update ready
            time.sleep(self.config['apply_time'])

            # Perform common tool setup
            self.setup()

            try:
                # *** Enable secure boot ***

                # Download ram image
                self.init_ram_image(self.config['ram_image'])

                # Enable secure boot
                #self.write_otp_value('OEM_SECURITY_POLICY', '0x80')

                # Reset
                self.gdb_execute('monitor reset')

                # *** End enable secure boot ***
            except:
                raise
            finally:
                self.cleanup()

def main():
    """
    Main entry point for the tool script.
    """
    try:
        tool = QCC710_Programmer()
        tool.run()
        print('SUCCESS')
    except ValueError or TypeError:
        print('ERR_PROGRAM')
    except socket.timeout:
        print('ERR_TIMEOUT')
    except GDB_Client_Error:
        print('ERR_CONNECTION')
    except VerifyError:
        print('ERR_VERIFY')
    except:
        print('ERR_UNKNOWN')


if __name__ == "__main__":
    main()
