#!/usr/bin/env python
"""!
@brief Generates Secure Wrap and Provisioning Command blobs.

@section
Copyright (c) 2020 Qualcomm Technologies, Inc.
All rights reserved.
Confidential and Proprietary - Qualcomm Technologies, Inc.
"""


from typing import Union
from binascii import hexlify

from Crypto.Cipher import AES
from Crypto.Random import get_random_bytes
from cryptography.hazmat.primitives.ciphers.aead import AESGCM

from kdf.derive_key import NISTKDFContext, DerivedKeyAlgo, SecuritySelector, derive_key_nist, ROTDebugState, OEMLifeCycleState

import json
import sys
import getopt

##
# @cond 0
# Length of Cipher Suite
SCR_CIPHER_SUITE_LENGTH = 1
# Length of Family Key Set
SCR_FAMILY_KEY_SET_LENGTH = 1
# Length of Command type
SCR_COMMAND_TYPE_LENGTH = 2
# Length of Packet Length
SCR_PACKET_LENGTH_LENGTH = 2
# Length of Version Minor and Major
SCR_VERSION_LENGTH = 2
# Length of Reserved
SCR_RESERVED_LENGTH = 2
# Length of Tag Length
SCR_TAG_LENGTH_LENGTH = 2
# Length of AAD
SCR_AAD_LENGTH_LENGTH = 2
# Length of Derivation Key Version
SCR_DERIVATION_KEY_VERSION = 4
# Length of Fuse Address
SCR_FUSE_ADDRESS_LENGTH = 4
# Length of Initial Vector
SCR_INITIAL_VECTOR_LENGTH = 12
# Length of OEM Batch Secret
SCR_OEM_BATCH_SECRET_LENGTH = 16
# Length of wraaping key
SCR_WRAPPING_KEY_LENGTH = 32
# Length of Tag
SCR_TAG_LENGTH = 16
# Max length of AAD
SCR_MAX_AAD_LENGTH = 16
# Length of input key
SCR_DEVICE_FACT_PROV_KEY_LENGTH = 32
# Base fuse address for OEMBatchSecret
# (ChpRandomBaseKey)
SCR_BASE_FUSE_ADDRESS = 0x50040998
# Number of Address-Value pairs
SCR_NUMBER_OF_PAIRS = 0x04
# Length of number of Address-Value pairs
SCR_NUMBER_OF_PAIRS_LENGTH = 4
# Endianess to convert interger to bytes
SCR_LITTLE_ENDIAN = "little"
# Usage Error String
USAGE_STRING = "Invalid Command. Usage- python3 secure_wrap.py -j <jsonfile> -o <outputfile>"


# Label for deriving device factory provisioning
# key using NIST KDF
SCR_LABEL = "4a12a789d41cc278eaf412665a81d501"
# AAD to encrypt provisioning blob
SCR_AAD = 'face5eedface5eedface5eedface5eed'
# @endcond


def _check_params(kdf_context: NISTKDFContext,
                  entity_dev_fact_prov_key: bytes,
                  batch_secret_wrapping_key: bytes,
                  oem_batch_secret: bytes):
    """!
    @param kdf_context: application specific context to be used for diversifying the blobs.
    @param entity_dev_fact_prov_key: bytes contains the key of length 32 bytes.
    @param batch_secret_wrapping_key: bytes contains a random key to encrypt payload
    (oem_batch_secret). The length of the key is 16 bytes.
    @param oem_batch_secret: bytes contains the payload of length 128 bits.

    @exception ValueError: if any of the argument is None or length of input keys length or payload
    (oem_batch_secret) is invalid or the algorithm is invalid.
    @exception TypeError: if the data type mismatches for any of the input arguments.
    """
    if kdf_context is None:
        raise ValueError("'kdf_context' cannot be None.")
    elif entity_dev_fact_prov_key is None:
        raise ValueError("'entity_dev_fact_prov_key' cannot be None.")
    elif batch_secret_wrapping_key is None:
        raise ValueError("'batch_secret_wrapping_key' cannot be None.")
    elif oem_batch_secret is None:
        raise ValueError("'oem_batch_secret' cannot be None.")
    elif len(entity_dev_fact_prov_key) != SCR_DEVICE_FACT_PROV_KEY_LENGTH:
        raise ValueError("'entity_dev_fact_prov_key' must be {} bytes.".format(
            SCR_DEVICE_FACT_PROV_KEY_LENGTH))
    elif len(batch_secret_wrapping_key) != SCR_WRAPPING_KEY_LENGTH:
        raise ValueError(
            "'batch_secret_wrapping_key' must be {} bytes.".format(SCR_WRAPPING_KEY_LENGTH))
    elif len(oem_batch_secret) != SCR_OEM_BATCH_SECRET_LENGTH:
        raise ValueError("'oem_batch_secret' must be {} bytes.".format(SCR_OEM_BATCH_SECRET_LENGTH))
    elif not isinstance(kdf_context, NISTKDFContext):
        raise TypeError(
            "'kdf_context' must be of type <Class NISTKDFContext>, not {}.".format(
                type(kdf_context).__name__))
    elif not isinstance(entity_dev_fact_prov_key, bytes):
        raise TypeError(
            "'entity_dev_fact_prov_key' must be bytes, not {}.".format(
                type(entity_dev_fact_prov_key).__name__))
    elif not isinstance(batch_secret_wrapping_key, bytes):
        raise TypeError(
            "'batch_secret_wrapping_key' must be bytes, not {}.".format(
                type(batch_secret_wrapping_key).__name__))
    elif not isinstance(oem_batch_secret, bytes):
        raise TypeError(
            "'oem_batch_secret' must be bytes, not {}.".format(
                type(oem_batch_secret).__name__))
    else:
        NotImplemented

    if kdf_context.algorithm.value == DerivedKeyAlgo.AES256_SIV.value:
        print("Algorithm:\n", kdf_context.algorithm, "\n")
    else:
        raise ValueError("Algorithm not supported.")


def _generate_aes_gcm_provisioning_blob(
        batch_secret_wrapping_key: bytes,
        oem_batch_secret: bytes) -> bytes:
    """!
    Returns the provisioning blob.

    @param batch_secret_wrapping_key: bytes contains a random key to encrypt payload
    (oem_batch_secret).
    @param oem_batch_secret: bytes contains the payload of 16 bytes.

    @retval bytes: containing AES-GCM provisioning command blob.
    """
    # Create the Header of the Command
    command_type = 0x0282
    v_minor = 0x01
    v_major = 0x01
    cipher_suite = 0x01
    family_key_set = 0x01
    reserved = 0x00
    iv = get_random_bytes(SCR_INITIAL_VECTOR_LENGTH)

    header = [
        v_minor.to_bytes(
            SCR_VERSION_LENGTH, SCR_LITTLE_ENDIAN), v_major.to_bytes(
            SCR_VERSION_LENGTH, SCR_LITTLE_ENDIAN), cipher_suite.to_bytes(
            SCR_CIPHER_SUITE_LENGTH, SCR_LITTLE_ENDIAN), family_key_set.to_bytes(
            SCR_FAMILY_KEY_SET_LENGTH, SCR_LITTLE_ENDIAN), reserved.to_bytes(
            SCR_RESERVED_LENGTH, SCR_LITTLE_ENDIAN), iv]

    # Prepare the payload
    #
    # Let, the OEM Batch Secret be
    # { 0x44, 0xe4, 0xd4, 0x55, 0x36, 0x96, 0x76, 0xe6, \
    #   0x17, 0x47, 0x57, 0x26, 0x54, 0xb6, 0x57, 0x95 }
    #
    # And, the Starting Address of the fuse be 0x50040940
    #
    # So, the payload will be:
    # { 0x04, 0x00, 0x00, 0x00, 0x98, 0x09, 0x04, 0x50, 0x44,
    #   0xe4, 0xd4, 0x55, 0x9c, 0x09, 0x04, 0x50, 0x36, 0x96,
    #   0x76, 0xe6, 0xa0, 0x09, 0x04, 0x50, 0x17, 0x47, 0x57,
    #   0x26, 0xa4, 0x09, 0x04, 0x50, 0x54, 0xb6, 0x57, 0x95}

    # Insert number of address-value pairs at the beginning of the payload
    payload = [SCR_NUMBER_OF_PAIRS.to_bytes(SCR_NUMBER_OF_PAIRS_LENGTH, SCR_LITTLE_ENDIAN)]
    address = SCR_BASE_FUSE_ADDRESS

    for i in range(0, 16, 4):
        # Append the address of the fuse
        payload.append(address.to_bytes(SCR_FUSE_ADDRESS_LENGTH, SCR_LITTLE_ENDIAN))
        # Append the value on the address
        payload.append(oem_batch_secret[(i):(i + 4)])
        # Increment address by 4 bytes
        address = address + 4

    print("Provisioning Command:\n")
    print("\tIV:\n\t", hexlify(iv), "\n")
    print("\tUnencrypted Payload:\n\t", hexlify(b"".join(payload)), "\n")

    # Encrypt the payload using the key (batch_secret_wrapping_key)
    aes_gcm = AESGCM(batch_secret_wrapping_key)
    cipher_text = aes_gcm.encrypt(iv, b"".join(payload), bytes.fromhex(SCR_AAD))

    # Add tag to header
    aes_gcm_tag = cipher_text[-SCR_TAG_LENGTH:]
    header.append(aes_gcm_tag)

    # Add AAD to header
    aad_length = len(bytes.fromhex(SCR_AAD))
    if aad_length > SCR_MAX_AAD_LENGTH:
        raise ValueError("Invalid AAD.")
    print("\tAAD\n\t", SCR_AAD, "\n")
    header.append(bytes.fromhex(SCR_AAD))

    # Get encrypted payload out of cipher text
    cipher_text_length = len(cipher_text) - SCR_TAG_LENGTH
    cipher_text = cipher_text[:cipher_text_length]

    # Prepare the packet length and add command type to header
    header_length = len(b"".join(header))
    packet_length = header_length + cipher_text_length
    header.insert(0, packet_length.to_bytes(SCR_PACKET_LENGTH_LENGTH, SCR_LITTLE_ENDIAN))
    header.insert(0, command_type.to_bytes(SCR_COMMAND_TYPE_LENGTH, SCR_LITTLE_ENDIAN))

    print("\tHeader:\n\t", hexlify(b"".join(header)), "\n")
    print("\tEncrypted Payload:\n\t", hexlify(cipher_text), "\n")

    # Create the AES GCM Provisioning Command blob
    aes_gcm_provisioning = [b"".join(header), cipher_text]

    return b"".join(aes_gcm_provisioning)


def _generate_aes_siv_wrap_blob(
        dev_fact_prov_kw_key: bytes,
        batch_secret_wrapping_key: bytes,
        bsve: int) -> bytes:
    """!
    Returns the secure wrap.

    @param dev_fact_prov_kw_key: bytes contains the key of length 32 bytes.
    @param batch_secret_wrapping_key: bytes contains a random key to encrypt payload
    (oem_batch_secret).
    @param bsve: int contains the Security Selector.

    @retval bytes: containing AES-SIV wrap command blob.
    """
    # Create the Header of the Command
    command_type = 0x0281
    v_minor = 0x01
    v_major = 0x01
    cipher_suite = 0x10
    family_key_set = 0x00
    reserved = 0x00
    derivation_key_version = bsve

    header = [
        v_minor.to_bytes(
            SCR_VERSION_LENGTH, SCR_LITTLE_ENDIAN), v_major.to_bytes(
            SCR_VERSION_LENGTH, SCR_LITTLE_ENDIAN), cipher_suite.to_bytes(
            SCR_CIPHER_SUITE_LENGTH, SCR_LITTLE_ENDIAN), family_key_set.to_bytes(
            SCR_FAMILY_KEY_SET_LENGTH, SCR_LITTLE_ENDIAN), reserved.to_bytes(
            SCR_RESERVED_LENGTH, SCR_LITTLE_ENDIAN), derivation_key_version.to_bytes(
            SCR_DERIVATION_KEY_VERSION, SCR_LITTLE_ENDIAN), bytes(
            SCR_LABEL, 'utf-8')]

    # Encrypt payload (batch_secret_wrapping_key) using key (dev_fact_prov_kw_key)
    cipher = AES.new(dev_fact_prov_kw_key, AES.MODE_SIV)
    secure_wrap, tag = cipher.encrypt_and_digest(batch_secret_wrapping_key)

    # Append tag to the header
    header.append(tag)

    # Prepare the packet length and add command type to header
    header_length = len(b"".join(header))
    packet_length = header_length + len(secure_wrap)
    header.insert(0, packet_length.to_bytes(SCR_PACKET_LENGTH_LENGTH, SCR_LITTLE_ENDIAN))
    header.insert(0, command_type.to_bytes(SCR_COMMAND_TYPE_LENGTH, SCR_LITTLE_ENDIAN))

    print("Secure Wrap:\n")
    print("\tHeader:\n\t", hexlify(b"".join(header)), "\n")
    print("\tEncrypted Payload:\n\t", hexlify(secure_wrap), "\n")
    print("\tTag:\n\t", hexlify(tag), "\n")

    # Create the AES SIV Wrap Command blob
    aes_siv_wrap = [b"".join(header), secure_wrap]

    return b"".join(aes_siv_wrap)


def generate_secure_blob(kdf_context: NISTKDFContext,
                         entity_dev_fact_prov_key: bytes = None,
                         batch_secret_wrapping_key: bytes = None,
                         oem_batch_secret: bytes = None) -> bytes:
    """!
    Returns the secure blob to be used to provision OEM Batch Secret on the QCC710 device.

    @param kdf_context: application specific context to be used for diversifying the blobs.
    @param entity_dev_fact_prov_key: bytes contains the key of length 32 bytes.
    @param batch_secret_wrapping_key: bytes contains a random key to encrypt payload
    (oem_batch_secret). The length of the key is 16 bytes.
    @param oem_batch_secret: bytes contains the payload of length 128 bits.

    @exception ValueError: if any of the argument is None or length of input keys length or payload
    (oem_batch_secret) is invalid or the algorithm is invalid.
    @exception TypeError: if the data type mismatches for any of the input arguments.

    @retval bytes: secure blob to be used to provision OEM Batch Secret on the QCC710 device.
    """
    # Check Parameters
    _check_params(
        kdf_context,
        entity_dev_fact_prov_key,
        batch_secret_wrapping_key,
        oem_batch_secret)

    # Derive Key using NIST KDF
    try:
        dev_fact_prov_kw_key = derive_key_nist(kdf_context, entity_dev_fact_prov_key, SCR_LABEL)
    except ValueError as err:
        raise ValueError(err)
    except TypeError as err:
        raise TypeError(err)

    print("Key:\n", hexlify(dev_fact_prov_kw_key), "\n")

    # Prepare Security Context Selector for KDF Context
    bsve = 0x00

    # Update Security Selector
    bsve = bsve | SecuritySelector.DEBUG_STATE.value | \
        SecuritySelector.TME_LCS.value | SecuritySelector.SW_CONTEXT.value

    # Update Security Selector
    if kdf_context.oem_product_seed is not None:
        bsve = bsve | SecuritySelector.OEM_PRODUCT_SEED.value

    # Update Security Selector
    if kdf_context.oem_lcs is not None:
        bsve = bsve | SecuritySelector.OEM_LCS.value

    # Generate the AES SIV Wrap Command blob
    aes_siv_wrap = _generate_aes_siv_wrap_blob(
        dev_fact_prov_kw_key, batch_secret_wrapping_key, bsve)

    # Generate the AES GCM Provisioning Command blob
    aes_gcm_provisioning = _generate_aes_gcm_provisioning_blob(
        batch_secret_wrapping_key, oem_batch_secret)

    # Concatenate secure wrap and provisioning blob
    secure_blob = aes_siv_wrap + aes_gcm_provisioning

    return secure_blob


def main(argv):

    # Get the command line options and arguments
    try:
        opts, args = getopt.getopt(argv, "hj:o:")
    except getopt.GetoptError:
        print (USAGE_STRING)
        # Exit in case of error
        sys.exit(2)

    # Check the no of command line options passed.If less, then print usage and exit
    if len(opts) != 2:
        print (USAGE_STRING)
        # Exit in error scenario
        sys.exit(2)
    else:
        for opt, arg in opts:
            if opt == '-h':
                print (USAGE_STRING)
                # Exit in non-error scenario
                sys.exit()
            elif opt in ("-j"):
                configfile = arg
            elif opt in ("-o"):
                outputfile = arg

    # Read the configuration from input json file
    with open(configfile,) as file:
        data = json.load(file)
        file.close()

    # Entity Device Factory Provisioning Key of length 32 bytes
    entity_dev_fact_prov_key = data['entity_dev_fact_prov_key']
    # OEM Batch Secret of length 16 bytes
    oem_batch_secret = data['oem_batch_secret']
    # OEM Product Seed of length 16 bytes
    oem_product_seed = data['NISTKDFContext']['oem_product_seed']
    # Activation of OEM (boolean)
    is_oem_lcs_activated = data['NISTKDFContext']['is_oem_lcs_activated']
    # Batch Secret Wrapping Key
    batch_secret_wrapping_key = data['batch_secret_wrapping_key']

    # Default ROT debug State
    debug_state = ROTDebugState.DISABLE

    # If ROT debug state is provided in configuration file
    if "rot_debug_state" in data['NISTKDFContext']:
        if (data['NISTKDFContext']['rot_debug_state'] == 0):
           debug_state = ROTDebugState.ENABLE
 
    # OEM LCS
    if (data['NISTKDFContext']['oem_lcs'] == 0):
        oem_lcs = OEMLifeCycleState.OEM_LCS_PRODUCTION
    elif (data['NISTKDFContext']['oem_lcs'] == 1):
        oem_lcs = OEMLifeCycleState.OEM_LCS_PROVISIONING
    elif (data['NISTKDFContext']['oem_lcs'] == 2):
        oem_lcs = OEMLifeCycleState.OEM_LCS_DEVELOPMENT
    elif (data['NISTKDFContext']['oem_lcs'] == 3):
        oem_lcs = OEMLifeCycleState.OEM_LCS_RMA

    # Generate Secure Blob to be used for secure OTP provisioning
    # ROTDebugState is hardcoded as DISABLE
    kdf_context = NISTKDFContext(ROTDebugState.DISABLE, DerivedKeyAlgo.AES256_SIV, bytes.fromhex(
        oem_product_seed), oem_lcs, is_oem_lcs_activated)
    secure_blob = generate_secure_blob(kdf_context,
                                       bytes.fromhex(entity_dev_fact_prov_key),
                                       bytes.fromhex(batch_secret_wrapping_key),
                                       bytes.fromhex(oem_batch_secret))

    # Write the secure blob in the output file
    with open(outputfile, 'wb') as file:
        file.write(secure_blob)
        file.close()


if __name__ == "__main__":
    main(sys.argv[1:])
