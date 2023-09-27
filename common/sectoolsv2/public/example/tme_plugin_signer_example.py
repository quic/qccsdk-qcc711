#  ===============================================================================
#  Copyright (c) 2021 Qualcomm Technologies, Inc.
#  All Rights Reserved.
#  Confidential and Proprietary - Qualcomm Technologies, Inc.
#  ===============================================================================
import hashlib
from pathlib import Path
from subprocess import run
from tempfile import TemporaryDirectory
from typing import Any, List, Tuple

from public.tme_signable import TMESignable

try:
    from common.crypto.openssl.openssl import OPENSSL
except ModuleNotFoundError:
    # This example relies on OpenSSL being installed on the system.
    OPENSSL = "openssl"


# noinspection PyUnusedLocal
# pylint: disable=unused-argument
def sign(tme: TMESignable, allowed_algorithm_ids: List[str], security_profile,
         plugin_signer_args: Any) -> Tuple[str, bytes]:
    """ A TME plugin signer example which relies on OpenSSL for signature generation. """

    # Check the TME object type being signed. This example only supports DPR signing.
    assert "DPR" in tme.describe()

    # Demonstrate how to print the contents of the DPR being signed.
    print(tme)

    # Choose one of the supported signing algorithms.
    assert "ECDSA_P521_SHA512" in allowed_algorithm_ids
    algorithm_id = "ECDSA_P521_SHA512"

    # Get the hash to sign. DO NOT compute another hash over the hash returned by get_signable_hash. The signature must
    #   be directly computed using the hash returned by get_signable_hash.
    hash_to_sign = tme.get_signable_hash(algorithm_id)

    # Demonstrate how to verify that the hash to sign matches the data to be signed. This example assumes that
    #   ECDSA_P521_SHA512 was the selected algorithm id.
    data_to_sign = tme.get_signable_data(algorithm_id)
    assert hash_to_sign == hashlib.sha512(data_to_sign).digest()

    # Demonstrate how to generate the signature using the hash_to_sign and a DER-encoded private key. DO NOT UNDER ANY
    #   CIRCUMSTANCE USE THE KEY PRESENT IN THIS EXAMPLE FOR PRODUCTION PURPOSES. In production, the private key should
    #   be OEM-generated and should never be present in source code or a non-secure environment. Ideally it should be
    #   secured by an HSM. This example is only intended to demonstrate how to compute the signature from the
    #   hash_to_sign.
    private_key = b"0\x81\xf7\x02\x01\x000\x10\x06\x07*\x86H\xce=\x02\x01\x06\x05+\x81\x04\x00#\x04\x81\xdf0\x81\xdc\x02\x01\x01\x04B\x00\xc7!I\xca\x19`\xfb\x9ax\n\x89\xdb4`f\xc1\xcb\xc0\x16mh\x0c^\x90\xd9\xb0^,\xde\xe7\xd0\xcb\xc5\x8a\xa7\x9fWE\xcf\xb0\xc1\x9dag\x905\xdd\xdd\x1a@u\n\xc4P\x90\x15\xf5\xba\x86\xa7/\xc7\x98d\x18\xa0\x07\x06\x05+\x81\x04\x00#\xa1\x81\x89\x03\x81\x86\x00\x04\x01\xea\x95Q\x85\x81NTr^L\xbc\x19\x9d\xd3\xefp\xd4\x9b\xf5W\x1c\xce\xfe\x94\xd35\x07\xd7\xb4K?\xde+\xd2\xae\x88\x97Q\x93*\x05\xafR\x7f\x1b\xfa\xbcE\x9f#\xee\xb3^\x9d\xda\xb3\xf7\x91l\xe6u\xe6A\x00\x1c\x01\x97\xbc\x8a9\xdfu]:o`\xcc\xa8\xba\xa0\x1c\xef\xe8p\x18\xbe\xda\xdc\x0c\xa4\xda\xf6\xf5\x85\x18%\x9a\xc9\xaf41\x0fJl\xa7\x88\xac\xa8\xca6\xd9\xe3\x1a>\xd6\xf6\xf4^\xd0\x99\x15\x1a\x9cG\x85>\x86\xbcj\x17\x1b"
    with TemporaryDirectory() as temp_dir:
        private_key_path = Path(temp_dir) / "key.bin"
        private_key_path.write_bytes(private_key)
        hash_path = Path(temp_dir) / "hash.bin"
        hash_path.write_bytes(hash_to_sign)
        cmd = [OPENSSL, "pkeyutl", "-sign", "-keyform", "DER", "-in", str(hash_path), "-inkey", str(private_key_path)]
        signature = run(cmd, capture_output=True, check=True, timeout=20).stdout

    # Return the selected algorithm id and computed signature.
    return algorithm_id, signature
