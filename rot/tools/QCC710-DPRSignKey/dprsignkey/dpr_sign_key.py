#!/usr/bin/env python
"""!
@brief Generates Secure Wrap and Provisioning Command blobs.

@section
Copyright (c) 2022 Qualcomm Technologies, Inc.
All rights reserved.
Confidential and Proprietary - Qualcomm Technologies, Inc.
"""
import getopt
import json
import sys
from binascii import hexlify

from Crypto.PublicKey import ECC

from kdf.derive_key import OEMLifeCycleState, NISTKDFContext, DerivedKeyAlgo, derive_key_nist, DRV_OEM_ID_LENGTH, \
    DRV_LITTLE_ENDIAN, _derive_key_internal, HKDFContext, DRV_NONCE_LENGTH, ROTDebugState

# Usage Error String
USAGE_STRING = "Invalid Command. Usage- python3 dpr_sign_key.py -j <json file> -o <output folder path>"
LABEL_STRING = "DPR"
# Length of OEM Batch Secret
OEM_BATCH_SECRET_LENGTH = 16
# Length of OEM Product Seed
OEM_PRODUCT_SEED_LENGTH = 16
# Length of OEM Product Id
OEM_PRODUCT_ID_LENGTH = 2
# Length of input key
DEVICE_FACT_PROV_KEY_LENGTH = 32
# Length of Chip Unique Id
CHIP_UNIQUE_ID_LENGTH = 8
# PartyUinfo.Identity for DPR KDF Context
DPR_DRV_PARTY_U_INFO_IDENTITY = "DPR"

# ECC_NIST_SECP521 const arrays represent the curve order n of G or each curve
# Reference: https://www.secg.org/sec2-v2.pdf
ECC_NIST_SECP521_r1_ORDER = "000001ffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffff" \
                            "fffa51868783bf2f966b7fcc0148f709a5d03bb5c9b8899c47aebb6fb71e91386409"


def _validate_derived_private_key_order(derived_private_key: bytes = None) -> bool:
    """!
    Validates derived private key is less than order of the curve P-521 to make sure
    public key can be derived from it

    @param derived_private_key: bytes contains the derived private key of 68 bytes aligned to
    521-bits and 0 padded.

    @exception ValueError: if Derived Key provided is None or length is not 68 bytes.
    @exception TypeError: if Derived Key data type is not bytes.

    @retval bool: true if derived private key validation against NIST P-521 order is success,
    false otherwise.
    """
    return_flag = False
    curve_order = bytes.fromhex(ECC_NIST_SECP521_r1_ORDER)

    if len(curve_order) == len(derived_private_key):
        # Compare against the curve order buffer
        compare_val = 0
        for index in range(len(curve_order)):
            if curve_order[index] != derived_private_key[index]:
                compare_val = curve_order[index] - derived_private_key[index]
                break

        # If derived private_key is of the correct order, we still need to ensure it is non-zero
        if compare_val > 0:
            for byte in derived_private_key:
                if byte != 0:
                    return_flag = True
                    break

    return return_flag


def _check_dpr_signing_key_params(entity_dev_fact_prov_key: bytes = None,
                                  oem_batch_secret: bytes = None,
                                  chip_unique_id: bytes = None,
                                  oem_id: int = None,
                                  oem_product_id: bytes = None,
                                  oem_product_seed: bytes = None,
                                  is_oem_lcs_activated: bool = None,
                                  oem_lcs: OEMLifeCycleState = None,
                                  debug_state: ROTDebugState = None):
    """!
    Validates the various attributes received for generating Private Key

    @param entity_dev_fact_prov_key: bytes contains the factory provisioning key of length 32 bytes.
    @param oem_batch_secret: bytes contains the OEM Batch Secret of 16 bytes.
    @param chip_unique_id: bytes contains the Chip Unique Id of 8 bytes
    @param oem_id: int signifying OEM id
    @param oem_product_id: bytes contains the OEM Product Id of 2 bytes
    @param oem_product_seed: bytes contains the OEM Product Seed of 16 bytes
    @param is_oem_lcs_activated: bool signifying OEM LCS is activated or not
    @param oem_lcs: <Class @ref OEMLifeCycleState> is an OEM optionally controlled Life Cycle State.
    @param debug_state: <Class @ref ROTDebugState> is an SoC debug enable condition.

    @exception ValueError: if any of the argument is None.
    @exception TypeError: if the data type mismatches for any of the input arguments.
    @exception OverflowError: if length of OEM ID is invalid.
    """
    if entity_dev_fact_prov_key is None:
        raise ValueError("Dev Factory Provisioning Key cannot be None.")
    if chip_unique_id is None:
        raise ValueError("Chip Unique Id cannot be None.")
    if oem_batch_secret is None:
        raise ValueError("OEM Batch Secret cannot be None.")
    elif oem_id is None:
        raise ValueError("OEM Id cannot be None.")
    elif oem_product_id is None:
        raise ValueError("OEM Product Id cannot be None.")
    elif oem_product_seed is None:
        raise ValueError("OEM Product Seed cannot be None.")
    elif is_oem_lcs_activated is None:
        raise ValueError("OEM LCS Activated flag cannot be None.")
    elif oem_lcs is None:
        raise ValueError("OEM LCS cannot be None.")
    elif debug_state is None:
        raise ValueError("Debug State cannot be None.")
    elif not isinstance(entity_dev_fact_prov_key, bytes):
        raise TypeError("'entity_dev_fact_prov_key' must be bytes, not {}.".format(
            type(entity_dev_fact_prov_key).__name__))
    elif not isinstance(chip_unique_id, bytes):
        raise TypeError("'chip_unique_id' must be bytes, not {}.".format(
            type(entity_dev_fact_prov_key).__name__))
    elif not isinstance(oem_batch_secret, bytes):
        raise TypeError("'oem_batch_secret' must be bytes, not {}.".format(
            type(oem_batch_secret).__name__))
    elif not isinstance(oem_id, int):
        raise TypeError("'oem_id' must be int, not {}.".format(type(oem_id).__name__))
    elif not isinstance(oem_product_id, bytes):
        raise TypeError(
            "'oem_product_id' must be bytes, not {}.".format(
                type(oem_product_id).__name__))
    elif not isinstance(oem_product_seed, bytes):
        raise TypeError(
            "'oem_product_seed' must be bytes, not {}.".format(
                type(oem_product_seed).__name__))
    elif not isinstance(is_oem_lcs_activated, bool):
        raise TypeError("'is_oem_lcs_activated' must be boolean, not {}.".format(
            type(is_oem_lcs_activated).__name__))
    elif not isinstance(oem_lcs, OEMLifeCycleState):
        raise TypeError("'oem_lcs' must be of type <Class OEMLifeCycleState>, not {}.".format(
            type(oem_lcs).__name__))
    elif not isinstance(debug_state, ROTDebugState):
        raise TypeError("'debug_state' must be of type <Class ROTDebugState>, not {}.".format(
            type(debug_state).__name__))
    elif len(entity_dev_fact_prov_key) != DEVICE_FACT_PROV_KEY_LENGTH:
        raise ValueError("'entity_dev_fact_prov_key' must be {} bytes.".format(
            DEVICE_FACT_PROV_KEY_LENGTH))
    elif len(chip_unique_id) != CHIP_UNIQUE_ID_LENGTH:
        raise ValueError("'chip_unique_id' must be {} bytes.".format(CHIP_UNIQUE_ID_LENGTH))
    elif len(oem_batch_secret) != OEM_BATCH_SECRET_LENGTH:
        raise ValueError("'oem_batch_secret' must be {} bytes.".format(OEM_BATCH_SECRET_LENGTH))
    elif len(oem_product_id) != OEM_PRODUCT_ID_LENGTH:
        raise ValueError("'oem_product_id' must be {} bytes.".format(OEM_PRODUCT_ID_LENGTH))
    elif len(oem_product_seed) != OEM_PRODUCT_SEED_LENGTH:
        raise ValueError("'oem_product_seed' must be {} bytes.".format(OEM_PRODUCT_SEED_LENGTH))

    try:
        oem_id.to_bytes(DRV_OEM_ID_LENGTH, DRV_LITTLE_ENDIAN)
    except OverflowError:
        raise OverflowError("'oem_id' must be {0} bytes.".format(DRV_OEM_ID_LENGTH))
    except AttributeError:
        NotImplemented


def get_dpr_signing_key(entity_dev_fact_prov_key: bytes = None,
                        oem_batch_secret: bytes = None,
                        chip_unique_id: bytes = None,
                        oem_id: int = None,
                        oem_product_id: bytes = None,
                        oem_product_seed: bytes = None,
                        is_oem_lcs_activated: bool = None,
                        oem_lcs: OEMLifeCycleState = None,
                        debug_state: ROTDebugState = None) -> bytes:
    """!
    Get the NIST P-521 based ECC Private Key which will be used for signing OEM's DPR Request.

    @param entity_dev_fact_prov_key: bytes contains the factory provisioning key of length 32 bytes.
    @param oem_batch_secret: bytes contains the OEM Batch Secret of 16 bytes.
    @param chip_unique_id: bytes contains the Chip Unique Id of 8 bytes
    @param oem_id: int signifying OEM id
    @param oem_product_id: bytes contains the OEM Product Id of 2 bytes
    @param oem_product_seed: bytes contains the OEM Product Seed of 16 bytes
    @param is_oem_lcs_activated: bool signifying OEM LCS is activated or not
    @param oem_lcs: <Class @ref OEMLifeCycleState> is an OEM optionally controlled Life Cycle State.
    @param debug_state: <Class @ref ROTDebugState> is an SoC debug enable condition.

    @exception ValueError: if any of the argument is None.
    @exception TypeError: if the data type mismatches for any of the input arguments.
    @exception OverflowError: if length of OEM ID is invalid.

    @retval bytes: it contains the generated NIST P-521 based ECC Private Key. None will be returned
    in case no valid private key is derived.
    """
    # Check parameters
    _check_dpr_signing_key_params(entity_dev_fact_prov_key, oem_batch_secret, chip_unique_id, oem_id, oem_product_id,
                                  oem_product_seed, is_oem_lcs_activated, oem_lcs, debug_state)

    # Prepare the HKDFContext to be used for deriving Mixing Key from OEM Batch Secret
    hkdf_context = HKDFContext(
        None,
        None,
        DerivedKeyAlgo.KDF_NIST,
        oem_id,
        None,
        oem_lcs,
        is_oem_lcs_activated,
        chip_unique_id,
        oem_product_id)

    # Generate the mixing key from OEM Batch Secret
    mixing_key = _derive_key_internal(hkdf_context, oem_batch_secret, LABEL_STRING, None,
                                      DPR_DRV_PARTY_U_INFO_IDENTITY, False)
    print("Generated Mixing Key:\n", hexlify(mixing_key), "\n")

    signing_private_key = None
    # Initialize a byte array to be used as Nonce
    nonce_array = bytearray(DRV_NONCE_LENGTH - 1)
    # Iterate from 0x00 to 0xff to get the first private key smaller than curve order
    for index in range(0xff):
        print("Iteration {} : Derive Final key\n".format(index + 1))
        # Add one byte of index as Nonce
        nonce_bytes = nonce_array
        nonce_bytes.insert(0, index)

        # Prepare the NISTKDFContext to be used for deriving DPR Signing Private Key
        kdf_context = NISTKDFContext(
            debug_state,
            DerivedKeyAlgo.ECC_ALGO_ECDSA,
            oem_product_seed,
            oem_lcs,
            is_oem_lcs_activated,
            mixing_key)

        # Generate the DPR Signing Private Key
        derived_key = derive_key_nist(kdf_context, entity_dev_fact_prov_key, LABEL_STRING, bytes(nonce_bytes),
                                      DPR_DRV_PARTY_U_INFO_IDENTITY)

        print("Iteration {} : Final Derived Key:\n{}\n".format(index + 1, hexlify(derived_key)))

        # Align the drive key to be 0 padded 521-bits aligned
        derived_key_bytearray = bytearray(derived_key)
        # Modify the first 3 bytes to make it 521 bits align from 544 bits
        derived_key_bytearray[0] = 0x00
        derived_key_bytearray[1] = 0x00
        # In Third byte keep only first bit
        derived_key_bytearray[2] = derived_key_bytearray[2] & 0x01

        signing_private_key = bytes(derived_key_bytearray)

        print("Iteration {} : Generated Signing Private Key:\n{}\n".format(index + 1, hexlify(signing_private_key)))

        is_valid_key = _validate_derived_private_key_order(signing_private_key)

        if is_valid_key:
            # If derived key is valid break or iterate again
            print("Iteration {} : Generated Signing Private key is Valid.\n".format(index + 1))
            break
        else:
            print("Iteration {} : Generated Signing Private key is Invalid.\n".format(index + 1))
            signing_private_key = None

    return signing_private_key


def main(argv):
    # Get the command line options and arguments
    try:
        opts, args = getopt.getopt(argv, "hj:o:")
    except getopt.GetoptError:
        print(USAGE_STRING)
        # Exit in case of error
        sys.exit(2)

    # Check the no of command line options passed.If less, then print usage and exit
    if len(opts) != 2:
        print(USAGE_STRING)
        # Exit in error scenario
        sys.exit(2)
    else:
        for opt, arg in opts:
            if opt == '-h':
                print(USAGE_STRING)
                # Exit in non-error scenario
                sys.exit()
            elif opt in "-j":
                configfile = arg
            elif opt in "-o":
                output_folder = arg

    # Read the configuration from input json file
    with open(configfile, ) as file:
        data = json.load(file)
        file.close()

    # Entity Device Factory Provisioning Key of length 32 bytes
    entity_dev_fact_prov_key = data['entity_dev_fact_prov_key']
    # OEM Batch Secret of length 16 bytes
    oem_batch_secret = data['oem_batch_secret']
    # Chip Unique Id of length 8 bytes
    chip_unique_id = data['KDFContext']['chip_unique_id']
    # OEM Id (integer)
    oem_id = data['KDFContext']['oem_id']
    # OEM Product Id of length 2 bytes
    oem_product_id = data['KDFContext']['oem_product_id']
    # OEM Product Seed of length 16 bytes
    oem_product_seed = data['KDFContext']['oem_product_seed']
    # Activation of OEM (boolean)
    is_oem_lcs_activated = data['KDFContext']['is_oem_lcs_activated']
    # OEM LCS
    if data['KDFContext']['oem_lcs'] == 0:
        oem_lcs = OEMLifeCycleState.OEM_LCS_PRODUCTION
    elif data['KDFContext']['oem_lcs'] == 1:
        oem_lcs = OEMLifeCycleState.OEM_LCS_PROVISIONING
    elif data['KDFContext']['oem_lcs'] == 2:
        oem_lcs = OEMLifeCycleState.OEM_LCS_DEVELOPMENT
    elif data['KDFContext']['oem_lcs'] == 3:
        oem_lcs = OEMLifeCycleState.OEM_LCS_RMA

    # Default ROT debug State
    debug_state = ROTDebugState.DISABLE

    # If debug state is provided in configuration file
    if "rot_debug_state" in data['KDFContext']:
        if data['KDFContext']['rot_debug_state'] == 0:
            debug_state = ROTDebugState.ENABLE

    # Generate private key to be used for OEM DPR
    private_key = get_dpr_signing_key(bytes.fromhex(entity_dev_fact_prov_key), bytes.fromhex(oem_batch_secret),
                                      bytes.fromhex(chip_unique_id), oem_id, bytes.fromhex(oem_product_id),
                                      bytes.fromhex(oem_product_seed), is_oem_lcs_activated, oem_lcs, debug_state)

    # Generate a PEM file containing the generated DPR private key
    key = ECC.construct(curve='P-521', d=int.from_bytes(private_key, "big"))
    file = open(output_folder + 'dpr_sign_key.pem', 'wt')
    file.write(key.export_key(format='PEM'))
    file.close()


if __name__ == "__main__":
    main(sys.argv[1:])
