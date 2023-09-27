#===============================================================================
# Copyright (c) 2020-2021 Qualcomm Technologies, Inc.
# All Rights Reserved.
# Confidential and Proprietary - Qualcomm Technologies, Inc.
#===============================================================================
import argparse
import os
from struct import *

class TLV_generator():
    '''
    QCC710 TLV file generator
    '''
    # Default location for the generated TLV file
    DEFAULT_GENERATED_TLV = './qcc710_update.tlv'

    # Default values for the TLV fields with fixed length
    DEFAULT_TLV_TYPE = 1
    DEFAULT_TOTAL_LENGTH = 36
    DEFAULT_PATCH_DATA_LENGTH = 0
    DEFAULT_SIGNING_FORMAT_VERSION = 0
    DEFAULT_SIGNATURE_ALGORITHM = 0
    DEFAULT_TLV_RSP_CONFIG = 0
    DEFAULT_IMAGE_TYPE = 1
    DEFAULT_PRODUCT_ID = 24
    DEFAULT_ROM_BUILD_VERSION = 0
    DEFAULT_PATCH_VERSION = 0
    DEFAULT_RESERVED_1 = 0
    DEFAULT_ANTI_ROLLBACK_VERSION = 0
    DEFAULT_SERIAL_NUMBER_LOW = 0
    DEFAULT_SERIAL_NUMBER_HIGH = 0
    DEFAULT_DEBUG_BITS = 0
    DEFAULT_RESERVED_2 = 0
    DEFAULT_PATCH_ENTRY_ADDRESS = 0
    DEFAULT_SIGNATURE_LENGTH = 0
    DEFAULT_PUBLIC_KEY_LENGTH = 0
    DEFAULT_TLV_LENGTH = DEFAULT_TOTAL_LENGTH + DEFAULT_SIGNATURE_LENGTH + DEFAULT_PUBLIC_KEY_LENGTH

    # Max TLV length
    MAX_TLV_LENGTH = 0xFFFFFF

    def __init__(self):
        '''
        Initialize TLV generator
        '''
        self.Description = 'QCC710 TLV generator'

        self.add_arguments()

        # Parse all the arguments.
        self.config = self.argparser.parse_args().__dict__

        self.intialize_TLV_fields()

    def add_arguments(self):
        '''
        Add TLV generator specific arguments.
        '''
        self.argparser = argparse.ArgumentParser(description=self.Description)
        self.argparser.add_argument(dest='source', help='Location of the signed binary file.')
        self.argparser.add_argument('-r', '--rsp', default=False, action='store_true', help='Suppress controller responses during the download process.')
        self.argparser.add_argument('-d', '--dst', default=TLV_generator.DEFAULT_GENERATED_TLV, help='Location of the generated TLV files.')

    def intialize_TLV_fields(self):
        '''
        Initialize TLV fields that have fixed length.
        '''
        self.TLV_Type = TLV_generator.DEFAULT_TLV_TYPE
        self.TLV_Length = TLV_generator.DEFAULT_TLV_LENGTH
        self.Total_Length = TLV_generator.DEFAULT_TOTAL_LENGTH
        self.Patch_Data_Length = TLV_generator.DEFAULT_PATCH_DATA_LENGTH
        self.Signing_Format_Version = TLV_generator.DEFAULT_SIGNING_FORMAT_VERSION
        self.Signature_Algorithm = TLV_generator.DEFAULT_SIGNATURE_ALGORITHM
        self.Tlv_Rsp_Config = TLV_generator.DEFAULT_TLV_RSP_CONFIG
        self.Image_Type = TLV_generator.DEFAULT_IMAGE_TYPE
        self.Product_ID = TLV_generator.DEFAULT_PRODUCT_ID
        self.ROM_Build_Version = TLV_generator.DEFAULT_ROM_BUILD_VERSION
        self.Patch_Version = TLV_generator.DEFAULT_PATCH_VERSION
        self.Reserved_1 = TLV_generator.DEFAULT_RESERVED_1
        self.Anti_Rollback_Version = TLV_generator.DEFAULT_ANTI_ROLLBACK_VERSION
        self.Serial_Number_Low = TLV_generator.DEFAULT_SERIAL_NUMBER_LOW
        self.Serial_Number_High = TLV_generator.DEFAULT_SERIAL_NUMBER_HIGH
        self.Debug_Bits = TLV_generator.DEFAULT_DEBUG_BITS
        self.Reserved_2 = TLV_generator.DEFAULT_RESERVED_2
        self.Patch_Entry_Address = TLV_generator.DEFAULT_PATCH_ENTRY_ADDRESS

    def populate_TLV_fields(self, signed_image):
        '''
        Polulate the TLV fields.

        Parameters:
            signed_image: path to the signed binary image.
        '''
        # Updata response config if the response flag is set.
        if self.config['rsp']:
            self.Tlv_Rsp_Config = 1

        # Open the signed image file and get its contents
        signed_image = signed_image.replace(os.sep, '/')
        with open(signed_image, 'rb') as file:
            self.signed_image_contents = file.read()

        # Update patch data length field
        self.Patch_Data_Length = len(self.signed_image_contents)

        if self.Patch_Data_Length:
            # Update TLV length field
            self.TLV_Length += self.Patch_Data_Length

            if self.TLV_Length <= TLV_generator.MAX_TLV_LENGTH :
                #Update Total length field
                self.Total_Length += self.Patch_Data_Length
            else:
                raise Exception('Invalid TLV length.')
        else:
            raise Exception('Invalid signed image length.')


    def generate_TLV_file(self, dst):
        '''
        Write the populated TLV fields to a file.

        Parameters:
            dst: path to the generated TLV file.
        '''
        # Open the tlv file for writting
        dst = dst.replace(os.sep, '/')
        with open(dst, 'wb') as file:
            file.write(pack('<B', self.TLV_Type))
            file.write(pack('<I', self.TLV_Length))

            # TLV_Length is 3 bytes long and is packed as a 4 bytes value,
            # so adjust the current position one byte back from the end.
            file.seek(-1,2)

            file.write(pack('<I', self.Total_Length))
            file.write(pack('<I', self.Patch_Data_Length))
            file.write(pack('<B', self.Signing_Format_Version))
            file.write(pack('<B', self.Signature_Algorithm))
            file.write(pack('<B', self.Tlv_Rsp_Config))
            file.write(pack('<B', self.Image_Type))
            file.write(pack('<H', self.Product_ID))
            file.write(pack('<H', self.ROM_Build_Version))
            file.write(pack('<H', self.Patch_Version))
            file.write(pack('<H', self.Reserved_1))
            file.write(pack('<I', self.Anti_Rollback_Version))
            file.write(pack('<I', self.Serial_Number_Low))
            file.write(pack('<H', self.Serial_Number_High))
            file.write(pack('<B', self.Debug_Bits))
            file.write(pack('<B', self.Reserved_2))
            file.write(pack('<I', self.Patch_Entry_Address))

            # Write the signed image
            file.write(self.signed_image_contents)

    def run(self):
        '''
        Start TLV generator.
        '''

        try:
            # Populate TLV fields.
            self.populate_TLV_fields(self.config['source'])

            # Write TLV fields to a file
            self.generate_TLV_file(self.config['dst'])
        except:
            raise
        finally:
            print('TLV file has been generated successfully.')

def main():
    '''
    Main entry point for the TLV generator.
    '''
    generator = TLV_generator()
    generator.run()

if __name__ == "__main__":
    main()

