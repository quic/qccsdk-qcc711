# ===============================================================================
# Copyright (c) 2021 Qualcomm Technologies, Inc.
# All Rights Reserved.
# Confidential and Proprietary - Qualcomm Technologies, Inc.
#
# This tool will add file header containing the encryption information to decryption.
#      struct key_header {
#          u8 key_type=0   // 0: Derived.
#          u8 nonce[32]    // This is part of the recorded configuration of HKDF tool.
#          u8 label[32]    // This is part of the recorded configuration of HKDF tool.
#      }
#      or
#      struct key_header {
#          u8 key_type=1   // 1: Static.
#          u32 key_id      // Key_id mapping with static key.
#      }
#
#      struct file_header {
#          u16 header_length              // Length of header.
#          u8  version                    // 1 (Version 1).
#          u32 encrypted_data_length      // Length of encrypted data.
#          u16 block_length                 // size of block encrypted at once.
#          u8  algo                       // 0:AES_GCM.
#          u8  tag_length                 // Default:4Bytes.
#          u8  iv_length                  // Fixed 12Bytes.
#          u8  iv[12]                     // AesGCMIV or a random number.
#          struct key_header key_header   // struct of key header.
#       }
# ===============================================================================

import argparse
import json
import os
import struct
from Cryptodome.Cipher import AES
# please install token package first
from kdf import derive_key
from kdf.derive_key import (
    DebugState,
    derive_key_hkdf,
    OEMLifeCycleState,
    HKDFContext,
    DerivedKeyAlgo
)


class Encrypt_File_Tool():
    tag_length = 4
    iv_length = 12
    counter_length = 4
    version = 1
    algo = 0

    def __init__(self):
        """
        Initializes the Encryption tool.
        """

        parser = argparse.ArgumentParser(description='Encryption Tool')
        parser.add_argument('input_file', type=str, help='Plaintext input file')
        parser.add_argument('output_file', type=str, help='Encrypted output file')
        parser.add_argument('key_file', type=str, help='Json file containing the key information')
        parser.add_argument('-v', '--iv', type=str, default="0", help='64-bit IV for the GCM encryption operation. Use 0 (default) for a randomly generated value')
        parser.add_argument('-b', '--block-length', type=int, default=4096, help='Length of each encrypted block in the output file. Default is 4096 bytes.')

        self.config = parser.parse_args()

    def encrypt(self, key, mode, iv, plaintext, tag_length):
        """
        Encrypt plaintext.

        Parameters:
            key: Secret data is encoded using this key.
            iv: must be unique, a nonce.
            mode: mode of operation.
            plaintext: User-readable data you care about.
            tag_length: The minimum length tag must be.

        Returns:
            ciphertext, tag: The encoded data and the truncated bytes to verify during decryption.
        """
        cipher = AES.new(key, mode, nonce=iv, mac_len=tag_length)
        return cipher.encrypt_and_digest(plaintext)

    def generate_kdf_context(self, key_config):
        """
        Generate KDF context.

        Parameters:
            key_config:  key config dictionary.

        Returns:
            kdf_context: kdf context.
        """
        # Debug State
        debug_state = eval('DebugState.{}'.format(key_config['DebugState']))
        # Secure Boot State
        secure_boot_state = eval(key_config['SecureBootState'])
        # Set algorithm to SHA256_HMAC
        algorithm = eval('DerivedKeyAlgo.{}'.format(key_config['Algorithm']))
        # OEM ID
        oem_id = eval(key_config['OemId'])
        # OEM RC Hash of length 64 bytes
        oem_rc_hash = eval(key_config['OemRcHash'])
        # OEM Life Cycle State
        oem_lcs = eval('OEMLifeCycleState.{}'.format(key_config['OemLcs']))
        # Activation of OEM (boolean)
        is_oem_lcs_activated = eval(key_config['IsOemLcsActivated'])

        # Prepare KDF Context
        kdf_context = HKDFContext(
            debug_state,
            secure_boot_state,
            algorithm,
            oem_id,
            oem_rc_hash.to_bytes(64, byteorder='big'),
            oem_lcs,
            is_oem_lcs_activated)

        return kdf_context

    def generate_key(self, key_file):
        """
        Generate encrypted key and key header.

        Parameters:
            key_file:  Json file containing the key information.

        Returns:
            key, key_header: encrypted key and key header containing the key information.
        """

        with open(key_file, 'r') as f:
            key_config = json.load(f)

        key_type = key_config['KeyType']
        if key_type == 'Derived':  # Derived mode
            if 'Nonce' in key_config:
                nonce = eval(key_config['Nonce']).to_bytes(32, byteorder='big')
            else:
                nonce = os.urandom(32)

            if 'Label' in key_config:
                label = key_config['Label']
            else:
                label = ''

            base_key = eval(key_config['OemBatchSecret']).to_bytes(16, byteorder='big')

            kdf_context = self.generate_kdf_context(key_config)

            # Key Derivation using HKDF
            key = derive_key_hkdf(kdf_context, base_key, label, nonce)
            key_header = struct.pack('<B', 0) + nonce + struct.pack('<32s', label.encode())

        elif key_type == 'Static':  # Static mode
            value = eval(key_config['Key'])
            key = value.to_bytes(16, byteorder='big')
            key_header = struct.pack('<BI', 1, int(key_config['KeyId'], 0))
        else:
            raise ValueError('key type error')

        return key, key_header

    def generate_file_header(self, file_size, block_length, iv, key_header):
        """
        Generate encrypted file header.

        Parameters:
            file_size: plaintext file size.
            block_length: size of block encrypted at once.
            iv: 96-bit IV for the GCM encryption operation.
            key_header: header including key information.

        Returns:
            file_header: file header including key information.
        """

        tag_num = (file_size + block_length - 1) // block_length
        encrypted_data_length = file_size + tag_num * self.tag_length
        header_length = 24 + len(key_header)

        return struct.pack('<HBIHBBB12s', header_length, self.version, encrypted_data_length, block_length, self.algo, self.tag_length, self.iv_length, iv) + key_header

    def encrypt_file(self):
        """
        Encrypt file.
        """
        value = eval(self.config.iv)
        counter = 0
        if value == 0:
            iv_8bytes = os.urandom(self.iv_length - self.counter_length)
        else:
            iv_8bytes = struct.pack('>2I', value >> 32, value % (2 ** 32))

        iv = iv_8bytes + struct.pack('>I', counter)
        key, key_header = self.generate_key(self.config.key_file)
        file_header = self.generate_file_header(os.path.getsize(self.config.input_file), self.config.block_length, iv, key_header)
        iv_step = self.config.block_length // 16 + 1

        with open(self.config.input_file, mode='rb') as src:
            with open(self.config.output_file, 'wb') as des:
                des.write(file_header)
                for block in iter(lambda: src.read(self.config.block_length), b''):
                    ciphertext, tag = self.encrypt(key, AES.MODE_GCM, iv, block, self.tag_length)
                    des.write(ciphertext)
                    des.write(tag)
                    counter += iv_step
                    iv = iv_8bytes + struct.pack('>I', counter)


def main():
    """
    Main entry point for the tool script.
    """
    tool = Encrypt_File_Tool()
    tool.encrypt_file()


if __name__ == '__main__':
    main()
