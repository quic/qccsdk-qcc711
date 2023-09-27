#!/usr/bin/env python
"""!
@brief It invokes various test cases of HKDF implementation.

@section
Copyright (c) 2020 Qualcomm Technologies, Inc.
All rights reserved.
Confidential and Proprietary - Qualcomm Technologies, Inc.
"""
from hashlib import sha256

from binascii import hexlify

from cryptography.hazmat.primitives import hmac, hashes
from ecdsa import curves

import ecdsa as ed

from kdf import derive_key
from kdf.derive_key import (
    DebugState,
    ROTDebugState,
    derive_key_hkdf, 
    derive_key_nist, 
    OEMLifeCycleState, 
    HKDFContext, 
    NISTKDFContext, 
    DerivedKeyAlgo
)


def _test_derive_hkdf_with_oem_batch_secret():
    """!
    Test Vector 1: Where OEM Batch Secret is used as base key.
    """
    # Nonce of length 32 bytes
    nonce                   =   "fb8d40ded206dc01f7368a42e20d2d04be68c7ff5f09665a81d50172346b1bb6"
    # Label is a string of length 32 bytes
    label                   =   "4a12a789d41cc278eaf412665a81d501"
    # OEM Batch Secret as base key of length 16 bytes
    base_key                =   "f0f0a5a5f0f0a5a5f0f0a5a5f0f0a5a5"
    # OEM RC Hash of length 64 bytes
    oem_rc_hash             =   "cf96861c4216b4a3bbba8f6af63edf276935153be6e6ee82ef5223a4be6c0328"\
                                "a8c317f349645618c7d63e0b93ef864d3a7f435e59208b7990caa6166af1ac94"
    # Debug State
    debug_state             =   DebugState.ENABLE
    # Secure Boot State
    secure_boot_state       =   False
    # Set algorithm to SHA256_HMAC
    algorithm               =   DerivedKeyAlgo.SHA256_HMAC
    # OEM ID
    oem_id                  =   0x12
    # OEM Life Cycle State KDF is 0x07 ((is_oem_lcs_activated << 2) | oem_lcs)
    oem_lcs                 =   OEMLifeCycleState.OEM_LCS_RMA
    # Activation of OEM (boolean)
    is_oem_lcs_activated    =   True
    # HMAC message
    hmac_message            =   "43e846a0710b3e507befadfb7a53de5afc6b65673a1cf290fbe5f19baadd466f"
    # Expected output
    expected_output         =   "be46fed2879a38888d420cf981df9e7f00884c9d46be9bb3e21c6df457744689"
    # Expected HMAC output
    expected_hmac_output    =   "44310b836dcde18a3e71d3483f5e53394ac888b790d948b444892d2a9ccad08b"

    # Prepare KDF Context
    kdf_context = HKDFContext(
        debug_state,
        secure_boot_state,
        algorithm,
        oem_id,
        bytes.fromhex(oem_rc_hash),
        oem_lcs,
        is_oem_lcs_activated)

    # Key Derivation using HKDF
    derived_key = derive_key_hkdf(kdf_context, bytes.fromhex(base_key), label, bytes.fromhex(nonce))

    assert derived_key == bytes.fromhex(expected_output)
    print("Output Key Material:\n", hexlify(derived_key))
    hh = hmac.HMAC(derived_key, hashes.SHA256())
    hh.update(bytes.fromhex(hmac_message))
    hmac_output = hh.finalize()
    print("HMAC:\n", hexlify(hmac_output), "\n")
    assert hmac_output == bytes.fromhex(expected_hmac_output)
    print("Test Passed.\n")


def _test_derive_hkdf_in_key_16_out_key_32():
    """!
    Test Vector 2: Where length of base key is 16 bytes and length of derived key is 32 bytes.
    Source: https://confluence.qualcomm.com/confluence/pages/viewpage.action?pageId=429503272#ZiggyKDFs&SecureWrapTool-BaseKeyLength-16bytes
    """
    # Nonce of length 32 bytes
    nonce                   =   "fb8d40ded206dc01f7368a42e20d2d04be68c7ff5f09665a81d50172346b1bb6"
    # Label is a string of length 32 bytes
    label                   =   "4a12a789d41cc278eaf412665a81d501"
    # Base Key of length 16 bytes
    base_key                =   "519b423d715f8b581f4fa8ee59f4771a"
    # OEM RC Hash of length 64 bytes
    oem_rc_hash             =   "cf96861c4216b4a3bbba8f6af63edf276935153be6e6ee82ef5223a4be6c0328"\
                                "a8c317f349645618c7d63e0b93ef864d3a7f435e59208b7990caa6166af1ac94"
    # Debug State
    debug_state             =   DebugState.ENABLE
    # Secure Boot State
    secure_boot_state       =   False
    # Set algorithm to SHA256_HMAC
    algorithm               =   DerivedKeyAlgo.SHA256_HMAC
    # OEM ID
    oem_id                  =   0x12
    # OEM Life Cycle State KDF is 0x07 ((is_oem_lcs_activated << 2) | oem_lcs)
    oem_lcs                 =   OEMLifeCycleState.OEM_LCS_RMA
    # Activation of OEM (boolean)
    is_oem_lcs_activated    =   True
    # HMAC message
    hmac_message            =   "43e846a0710b3e507befadfb7a53de5afc6b65673a1cf290fbe5f19baadd466f"
    # Expected output
    expected_output         =   "07d63643e6c83ee3da88213f9400914e9054c82426e9fbdd62cc94ced6a1bd3a"
    # Expected HMAC output
    expected_hmac_output    =   "70625e9c924361ee777ae3202480c5210191f96a47bd337247bc778e6341637d"

    # Prepare KDF Context
    kdf_context = HKDFContext(
        debug_state,
        secure_boot_state,
        algorithm,
        oem_id,
        bytes.fromhex(oem_rc_hash),
        oem_lcs,
        is_oem_lcs_activated)

    # Key Derivation using HKDF
    derived_key = derive_key_hkdf(kdf_context, bytes.fromhex(base_key), label, bytes.fromhex(nonce))

    assert derived_key == bytes.fromhex(expected_output)
    print("Output Key Material:\n", hexlify(derived_key))
    hh = hmac.HMAC(derived_key, hashes.SHA256())
    hh.update(bytes.fromhex(hmac_message))
    hmac_output = hh.finalize()
    print("HMAC:\n", hexlify(hmac_output), "\n")
    assert hmac_output == bytes.fromhex(expected_hmac_output)
    print("Test Passed.\n")


def _test_derive_hkdf_in_key_32_out_key_32():
    """!
    Test Vector 3: Where length of base key is 32 bytes and length of derived key is 32 bytes.
    Source: https://confluence.qualcomm.com/confluence/pages/viewpage.action?pageId=429503272#ZiggyKDFs&SecureWrapTool-BaseKeyLength-32bytes
    """
    # Nonce of length 32 bytes
    nonce                   =   "fb8d40ded206dc01f7368a42e20d2d04be68c7ff5f09665a81d50172346b1bb6"
    # Label is a string of length 32 bytes
    label                   =   "4a12a789d41cc278eaf412665a81d501"
    # Base Key of length 32 bytes
    base_key                =   "519b423d715f8b581f4fa8ee59f4771a5b44c8130b4e3eacca54a56dda72b464"
    # OEM RC Hash of length 64 bytes
    oem_rc_hash             =   "cf96861c4216b4a3bbba8f6af63edf276935153be6e6ee82ef5223a4be6c0328"\
                                "a8c317f349645618c7d63e0b93ef864d3a7f435e59208b7990caa6166af1ac94"
    # Debug State
    debug_state             =   DebugState.ENABLE
    # Secure Boot State
    secure_boot_state       =   False
    # Set algorithm to SHA256_HMAC
    algorithm               =   DerivedKeyAlgo.SHA256_HMAC
    # OEM ID
    oem_id                  =   0x12
    # OEM Life Cycle State KDF is 0x07 ((is_oem_lcs_activated << 2) | oem_lcs)
    oem_lcs                 =   OEMLifeCycleState.OEM_LCS_RMA
    # Activation of OEM (boolean)
    is_oem_lcs_activated    =   True
    # HMAC message
    hmac_message            =   "43e846a0710b3e507befadfb7a53de5afc6b65673a1cf290fbe5f19baadd466f"
    # Expected output
    expected_output         =   "4e56363689e721499a1a9d7363ec306aa6dc2af350f249c6fdd0b94aa5cc7ad8"
    # Expected HMAC output
    expected_hmac_output    =   "4787689b973a78f618661bbed07c1f5d144b02cd7c8e6bf3ff1a1f1b90f82e8b"

    # Prepare KDF Context
    kdf_context = HKDFContext(
        debug_state,
        secure_boot_state,
        algorithm,
        oem_id,
        bytes.fromhex(oem_rc_hash),
        oem_lcs,
        is_oem_lcs_activated)

    # Key Derivation using HKDF
    derived_key = derive_key_hkdf(kdf_context, bytes.fromhex(base_key), label, bytes.fromhex(nonce))

    assert derived_key == bytes.fromhex(expected_output)
    print("Output Key Material:\n", hexlify(derived_key))
    hh = hmac.HMAC(derived_key, hashes.SHA256())
    hh.update(bytes.fromhex(hmac_message))
    hmac_output = hh.finalize()
    print("HMAC:\n", hexlify(hmac_output), "\n")
    assert hmac_output == bytes.fromhex(expected_hmac_output)
    print("Test Passed.\n")


def _test_derive_hkdf_in_key_16_out_key_16():
    """!
    Test Vector 4: Where length of base key is 16 bytes and length of derived key is 16 bytes.
    """
    # Nonce of length 32 bytes
    nonce                   =   "fb8d40ded206dc01f7368a42e20d2d04be68c7ff5f09665a81d50172346b1bb6"
    # Label is a string of length 32 bytes
    label                   =   "4a12a789d41cc278eaf412665a81d501"
    # Base Key of length 16 bytes
    base_key                =   "519b423d715f8b581f4fa8ee59f4771a"
    # OEM RC Hash of length 64 bytes
    oem_rc_hash             =   "cf96861c4216b4a3bbba8f6af63edf276935153be6e6ee82ef5223a4be6c0328"\
                                "a8c317f349645618c7d63e0b93ef864d3a7f435e59208b7990caa6166af1ac94"
    # Debug State
    debug_state             =   DebugState.ENABLE
    # Secure Boot State
    secure_boot_state       =   False
    # Set algorithm to HKDF_128
    algorithm_hkdf_128      =   DerivedKeyAlgo.HKDF_128
    # Set algorithm to SHA256_HMAC
    algorithm_sha_hmac_256  =   DerivedKeyAlgo.SHA256_HMAC
    # OEM ID
    oem_id                  =   0x12
    # OEM Life Cycle State KDF is 0x07 ((is_oem_lcs_activated << 2) | oem_lcs)
    oem_lcs                 =   OEMLifeCycleState.OEM_LCS_RMA
    # Activation of OEM (boolean)
    is_oem_lcs_activated    =   True
    # HMAC message
    hmac_message            =   "43e846a0710b3e507befadfb7a53de5afc6b65673a1cf290fbe5f19baadd466f"
    # Expected output
    expected_output         =   "47d73a06f63c48c727e69cc20e0e3d54"
    # Expected HMAC output
    expected_hmac_output    =   "7b375495b808db465904b8e04758f00fe81e6fe71bd8b83e55abd049e33f5234"

    # Prepare KDF Context
    kdf_context = HKDFContext(
        debug_state,
        secure_boot_state,
        algorithm_hkdf_128,
        oem_id,
        bytes.fromhex(oem_rc_hash),
        oem_lcs,
        is_oem_lcs_activated)

    # Key Derivation using HKDF
    derived_key = derive_key_hkdf(kdf_context, bytes.fromhex(base_key), label, bytes.fromhex(nonce))

    assert derived_key == bytes.fromhex(expected_output)
    print("Output Key Material:\n", hexlify(derived_key))

    # Prepare KDF Context
    kdf_context = HKDFContext(
        debug_state,
        secure_boot_state,
        algorithm_sha_hmac_256,
        oem_id,
        bytes.fromhex(oem_rc_hash),
        oem_lcs,
        is_oem_lcs_activated)

    # Key Derivation using HKDF
    derived_derived_key = derive_key_hkdf(kdf_context, derived_key, label, bytes.fromhex(nonce))
    hh = hmac.HMAC(derived_derived_key, hashes.SHA256())
    hh.update(bytes.fromhex(hmac_message))
    hmac_output = hh.finalize()
    print("HMAC:\n", hexlify(hmac_output), "\n")
    assert hmac_output == bytes.fromhex(expected_hmac_output)
    print("Test Passed.\n")


def _test_derive_hkdf_in_key_32_out_key_16():
    """!
    Test Vector 5: Where length of base key is 32 bytes and length of derived key is 16 bytes.
    """
    # Nonce of length 32 bytes
    nonce                   =   "fb8d40ded206dc01f7368a42e20d2d04be68c7ff5f09665a81d50172346b1bb6"
    # Label is a string of length 32 bytes
    label                   =   "4a12a789d41cc278eaf412665a81d501"
    # Base Key of length 32 bytes
    base_key                =   "519b423d715f8b581f4fa8ee59f4771a5b44c8130b4e3eacca54a56dda72b464"
    # OEM RC Hash of length 64 bytes
    oem_rc_hash             =   "cf96861c4216b4a3bbba8f6af63edf276935153be6e6ee82ef5223a4be6c0328"\
                                "a8c317f349645618c7d63e0b93ef864d3a7f435e59208b7990caa6166af1ac94"
    # Debug State
    debug_state             =   DebugState.ENABLE
    # Secure Boot State
    secure_boot_state       =   False
    # Set algorithm to HKDF_128
    algorithm_hkdf_128      =   DerivedKeyAlgo.HKDF_128
    # Set algorithm to SHA256_HMAC
    algorithm_sha_hmac_256  =   DerivedKeyAlgo.SHA256_HMAC
    # OEM ID
    oem_id                  =   0x12
    # OEM Life Cycle State KDF is 0x07 ((is_oem_lcs_activated << 2) | oem_lcs)
    oem_lcs                 =   OEMLifeCycleState.OEM_LCS_RMA
    # Activation of OEM (boolean)
    is_oem_lcs_activated    =   True
    # HMAC message
    hmac_message            =   "43e846a0710b3e507befadfb7a53de5afc6b65673a1cf290fbe5f19baadd466f"
    # Expected output
    expected_output         =   "b38826de437b57f9514eb16c2ca2e9d5"
    # Expected HMAC output
    expected_hmac_output    =   "08dc09dc58e25bc942a62e556bf92f85268c9eb8a1c76df1b5ea6d9e31275a56"

    # Prepare KDF Context
    kdf_context = HKDFContext(
        debug_state,
        secure_boot_state,
        algorithm_hkdf_128,
        oem_id,
        bytes.fromhex(oem_rc_hash),
        oem_lcs,
        is_oem_lcs_activated)

    # Key Derivation using HKDF
    derived_key = derive_key_hkdf(kdf_context, bytes.fromhex(base_key), label, bytes.fromhex(nonce))

    assert derived_key == bytes.fromhex(expected_output)
    print("Output Key Material:\n", hexlify(derived_key))

    # Prepare KDF Context
    kdf_context = HKDFContext(
        debug_state,
        secure_boot_state,
        algorithm_sha_hmac_256,
        oem_id,
        bytes.fromhex(oem_rc_hash),
        oem_lcs,
        is_oem_lcs_activated)

    # Key Derivation using HKDF
    derived_derived_key = derive_key_hkdf(kdf_context, derived_key, label, bytes.fromhex(nonce))
    hh = hmac.HMAC(derived_derived_key, hashes.SHA256())
    hh.update(bytes.fromhex(hmac_message))
    hmac_output = hh.finalize()
    print("HMAC:\n", hexlify(hmac_output), "\n")
    assert hmac_output == bytes.fromhex(expected_hmac_output)
    print("Test Passed.\n")


def _test_derive_hkdf_in_P256_shared_secret_out_key_32():
    """!
    Test Vector 6: Where shared secret generated pf curve P-256 is base key and length of derived key is 32 bytes.
    """
    # Nonce of length 32 bytes
    nonce                   =   "fb8d40ded206dc01f7368a42e20d2d04be68c7ff5f09665a81d50172346b1bb6"
    # Label is a string of length 32 bytes
    label                   =   "4a12a789d41cc278eaf412665a81d501"
    # Private Key of the curve P-256 belonging to Party One
    private_key             =   "bcc9527647d99c450aeecc814f6990242e600fb4072eeaa53d016e2cbce16cf6"
    # Public Key of the curve P-256 belonging to Party Two
    public_key              =   "8ddcc959c8f1f434ef7f292a94f9e27d47813ef9aabcd836895e1279fd117354" \
                                "c521164b102c66c9db334145fd313a6754149fd8903c2877d7c9301c94ec400f"
    # OEM RC Hash of length 64 bytes
    oem_rc_hash             =   "cf96861c4216b4a3bbba8f6af63edf276935153be6e6ee82ef5223a4be6c0328" \
                                "a8c317f349645618c7d63e0b93ef864d3a7f435e59208b7990caa6166af1ac94"
    # Debug State
    debug_state             =   DebugState.ENABLE
    # Secure Boot State
    secure_boot_state       =   False
    # Set algorithm to SHA256_HMAC
    algorithm               =   DerivedKeyAlgo.SHA256_HMAC
    # OEM ID
    oem_id                  =   0x12
    # OEM Life Cycle State KDF is 0x07 ((is_oem_lcs_activated << 2) | oem_lcs)
    oem_lcs                 =   OEMLifeCycleState.OEM_LCS_RMA
    # Activation of OEM (boolean)
    is_oem_lcs_activated    =   True
    # HMAC message
    hmac_message            =   "43e846a0710b3e507befadfb7a53de5afc6b65673a1cf290fbe5f19baadd466f"
    # Expected shared secret
    expected_shared_secret  =   "6243bb4d81fa63202478bc517ac1bae18c68405ab55f4fe48e16a1356764ec33"
    # Expected output
    expected_output         =   "5218e53212d187441375b260731f4c51b07e055ebc3bc0ab43752e6dd4d30009"
    # Expected HMAC output
    expected_hmac_output    =   "aada337a213edcb5fb6ca692d9b20aecc19eda4cfa60db96c7652f6cb0675f98"

    # Generate ECDH Shared secret
    prv_key = ed.SigningKey.from_string(bytes.fromhex(private_key), curve=curves.NIST256p, hashfunc=sha256)
    pub_key = ed.VerifyingKey.from_string(bytes.fromhex(public_key), curve=curves.NIST256p, hashfunc=sha256)
    ecc = ed.ECDH(curves.NIST256p, prv_key, pub_key)
    shared_secret = ecc.generate_sharedsecret_bytes()
    assert shared_secret == bytes.fromhex(expected_shared_secret)
    print("Shared secret generated to be used for as base key HKDF:\n", hexlify(shared_secret), "\n")

    # Prepare KDF Context
    kdf_context = HKDFContext(
        debug_state,
        secure_boot_state,
        algorithm,
        oem_id,
        bytes.fromhex(oem_rc_hash),
        oem_lcs,
        is_oem_lcs_activated)

    # Key Derivation using HKDF
    derived_key = derive_key_hkdf(kdf_context, shared_secret, label, bytes.fromhex(nonce))

    assert derived_key == bytes.fromhex(expected_output)
    print("Output Key Material:\n", hexlify(derived_key))
    hh = hmac.HMAC(derived_key, hashes.SHA256())
    hh.update(bytes.fromhex(hmac_message))
    hmac_output = hh.finalize()
    print("HMAC:\n", hexlify(hmac_output), "\n")
    assert hmac_output == bytes.fromhex(expected_hmac_output)
    print("Test Passed.\n")


def _test_derive_hkdf_in_P521_shared_secret_out_key_32():
    """!
    Test Vector 7: Where shared secret generated pf curve P-521 is base key and length of derived key is 32 bytes.
    """
    # Nonce of length 32 bytes
    nonce                   =   "fb8d40ded206dc01f7368a42e20d2d04be68c7ff5f09665a81d50172346b1bb6"
    # Label is a string of length 32 bytes
    label                   =   "4a12a789d41cc278eaf412665a81d501"
    # Private Key of the curve P-521 belonging to Party One
    private_key             =   "01138ffe50e2e1509210c9a7c5d413dc17df97bedc7cc4735fc7e4d3e34a5266" \
                                "3a0ed3e823a11a3fb56250cdf64945e490e7d431dbe3d8ce92cc3ac8bd1d73d8" \
                                "816a"
    # Public Key of the curve P-521 belonging to Party Two
    public_key              =   "016f10323157ed9e5875dc4f3ce9c1f581b83589441e3f70b5811816912e9e8b" \
                                "a276525e6f497f81ce8e52dd2b39461eaf404c367fbed6769e41135886d240a2" \
                                "b8e7008a7a396e451067681770ce1affcb55f004880048741c97eed68aa55bd4" \
                                "ee129ee97b10e893555bee7b23de0625c892bfecbb1cf15da37350a3f38999d5" \
                                "9e11a948"
    # OEM RC Hash of length 64 bytes
    oem_rc_hash             =   "cf96861c4216b4a3bbba8f6af63edf276935153be6e6ee82ef5223a4be6c0328" \
                                "a8c317f349645618c7d63e0b93ef864d3a7f435e59208b7990caa6166af1ac94"
    # Debug State
    debug_state             =   DebugState.ENABLE
    # Secure Boot State
    secure_boot_state       =   False
    # Set algorithm to SHA256_HMAC
    algorithm               =   DerivedKeyAlgo.SHA256_HMAC
    # OEM ID
    oem_id                  =   0x12
    # OEM Life Cycle State KDF is 0x07 ((is_oem_lcs_activated << 2) | oem_lcs)
    oem_lcs                 =   OEMLifeCycleState.OEM_LCS_RMA
    # Activation of OEM (boolean)
    is_oem_lcs_activated    =   True
    # HMAC message
    hmac_message            =   "43e846a0710b3e507befadfb7a53de5afc6b65673a1cf290fbe5f19baadd466f"
    # Expected shared secret
    expected_shared_secret  =   "016cc3f8b2d2fec5e817303f54d123dbde878a288ebf31097c882dd0f3daa864" \
                                "f76afa5c5b73827097bd7dd929aa0feae0a495eeb6aea0372c3a78c59054784e" \
                                "3905"
    # Expected output
    expected_output         =   "dd3dbe36e9fd0e65fce0df7126c44d8148d818ad6e419c0e9e0a90e64e36cde1"
    # Expected HMAC output
    expected_hmac_output    =   "958832024330d6606beb0b2a951e270f6e00ba9708a5b13f6346c04ba99c2310"

    # Generate ECDH Shared secret
    prv_key = ed.SigningKey.from_string(bytes.fromhex(private_key), curve=curves.NIST521p, hashfunc=sha256)
    pub_key = ed.VerifyingKey.from_string(bytes.fromhex(public_key), curve=curves.NIST521p, hashfunc=sha256)
    ecc = ed.ECDH(curves.NIST521p, prv_key, pub_key)
    shared_secret = ecc.generate_sharedsecret_bytes()
    assert shared_secret == bytes.fromhex(expected_shared_secret)
    shared_secret = shared_secret.rjust(68, b'\x00')
    print("Shared secret generated to be used for as base key HKDF:\n", hexlify(shared_secret), "\n")

    # Prepare KDF Context
    kdf_context = HKDFContext(
        debug_state,
        secure_boot_state,
        algorithm,
        oem_id,
        bytes.fromhex(oem_rc_hash),
        oem_lcs,
        is_oem_lcs_activated)

    # Key Derivation using HKDF
    derived_key = derive_key_hkdf(kdf_context, shared_secret, label, bytes.fromhex(nonce))

    assert derived_key == bytes.fromhex(expected_output)
    print("Output Key Material:\n", hexlify(derived_key))
    hh = hmac.HMAC(derived_key, hashes.SHA256())
    hh.update(bytes.fromhex(hmac_message))
    hmac_output = hh.finalize()
    print("HMAC:\n", hexlify(hmac_output), "\n")
    assert hmac_output == bytes.fromhex(expected_hmac_output)
    print("Test Passed.\n")


def _test_derive_key_hkdf_invalid_nonce():
    """!
    Test case where length of nonce is invalid.
    """
    # Nonce of length 48 bytes
    nonce                   =   "fb8d40ded206dc01f7368a42e20d2d04be68c7ff5f09665a81d50172346b1bb6"\
                                "fb8d40ded206dc01f7368a42e20d2d04"
    # Label is a string of length 32 bytes
    label                   =   "4a12a789d41cc278eaf412665a81d501"
    # Base Key of length 16 bytes
    base_key                =   "665a81d50172346b1bb6d92fdb98ff43"
    # OEM RC Hash of length 64 bytes
    oem_rc_hash             =   "be68c7ff5f09665a81d50172346b1bb6d92fdb98ff43fb8d40ded206dc01f736"\
                                "8a42e20d2d04be68c7ff5f09665a81d5fb8d40ded206dc01f7368a42e20d2d04"
    # Debug State
    debug_state             =   DebugState.DISABLE
    # Secure Boot State
    secure_boot_state       =   False
    # Set algorithm to AES256_GCM
    algorithm               =   DerivedKeyAlgo.AES256_GCM
    # OEM ID
    oem_id                  =   0x1001
    # OEM Life Cycle State KDF is 0x06 ((is_oem_lcs_activated << 2) | oem_lcs)
    oem_lcs                 =   OEMLifeCycleState.OEM_LCS_DEVELOPMENT
    # Activation of OEM (boolean)
    is_oem_lcs_activated    =   True

    # Prepare KDF Context
    kdf_context = HKDFContext(
        debug_state,
        secure_boot_state,
        algorithm,
        oem_id,
        bytes.fromhex(oem_rc_hash),
        oem_lcs,
        is_oem_lcs_activated)
    try:
        # Key Derivation using HKDF
        derived_key = derive_key_hkdf(
            kdf_context,
            bytes.fromhex(base_key),
            label,
            bytes.fromhex(nonce))
    except ValueError as err:
        print(err)
        print("Test Passed.")
        return
        
    raise AssertionError("Test Failed.")


def _test_derive_key_hkdf_with_invalid_label():
    """!
    Test case where length of label is invalid.
    """
    # Nonce of length 32 bytes
    nonce                   =   "fb8d40ded206dc01f7368a42e20d2d044a12a789d41cc278eaf412665a81d501"
    # Label is a string of length 64 bytes
    label                   =   "4a12a789d41cc278eaf412665a81d50172346b1bb6d92fdb98ff43fb8d40ded2"
    # Base Key of length 16 bytes
    base_key                =   "665a81d50172346b1bb6d92fdb98ff43"
    # OEM RC Hash of length 64 bytes
    oem_rc_hash             =   "be68c7ff5f09665a81d50172346b1bb6d92fdb98ff43fb8d40ded206dc01f736"\
                                "8a42e20d2d04be68c7ff5f09665a81d5fb8d40ded206dc01f7368a42e20d2d04"
    # Debug State
    debug_state             =   DebugState.DISABLE
    # Secure Boot State
    secure_boot_state       =   False
    # Set algorithm to AES256_GCM
    algorithm               =   DerivedKeyAlgo.AES256_GCM
    # OEM ID
    oem_id                  =   0x1001
    # OEM Life Cycle State KDF is 0x06 ((is_oem_lcs_activated << 2) | oem_lcs)
    oem_lcs                 =   OEMLifeCycleState.OEM_LCS_DEVELOPMENT
    # Activation of OEM (boolean)
    is_oem_lcs_activated    =   True

    # Prepare KDF Context
    kdf_context = HKDFContext(
        debug_state,
        secure_boot_state,
        algorithm,
        oem_id,
        bytes.fromhex(oem_rc_hash),
        oem_lcs,
        is_oem_lcs_activated)
    try:
        # Key Derivation using HKDF
        derived_key = derive_key_hkdf(
            kdf_context,
            bytes.fromhex(base_key),
            label,
            bytes.fromhex(nonce))
    except ValueError as err:
        print(err)
        print("Test Passed.")
        return

    raise AssertionError("Test Failed.")


def _test_derive_key_hkdf_invalid_base_key():
    """!
    Test case where length of base key is invalid.
    """
    # Nonce of length 32 bytes
    nonce                   =   "fb8d40ded206dc01f7368a42e20d2d04be68c7ff5f09665a81d50172346b1bb6"
    # Label is a string of length 32 bytes
    label                   =   "4a12a789d41cc278eaf412665a81d501"
    # Base Key of length 48 bytes
    base_key                =   "665a81d50172346b1bb6d92fdb98ff43fb8d40ded206dc01f7368a42e20d2d04"\
                                "06dc01f78a42e20d2d04be68c7ff5f09"
    # OEM RC Hash of length 64 bytes
    oem_rc_hash             =   "be68c7ff5f09665a81d50172346b1bb6d92fdb98ff43fb8d40ded206dc01f736"\
                                "8a42e20d2d04be68c7ff5f09665a81d5fb8d40ded206dc01f7368a42e20d2d04"
    # Debug State
    debug_state             =   DebugState.DISABLE
    # Secure Boot State
    secure_boot_state       =   False
    # Set algorithm to AES256_GCM
    algorithm               =   DerivedKeyAlgo.AES256_GCM
    # OEM ID
    oem_id                  =   0x1001
    # OEM Life Cycle State KDF is 0x06 ((is_oem_lcs_activated << 2) | oem_lcs)
    oem_lcs                 =   OEMLifeCycleState.OEM_LCS_DEVELOPMENT
    # Activation of OEM (boolean)
    is_oem_lcs_activated    =   True

    # Prepare KDF Context
    kdf_context = HKDFContext(
        debug_state,
        secure_boot_state,
        algorithm,
        oem_id,
        bytes.fromhex(oem_rc_hash),
        oem_lcs,
        is_oem_lcs_activated)
    try:
        # Key Derivation using HKDF
        derived_key = derive_key_hkdf(
            kdf_context,
            bytes.fromhex(base_key),
            label,
            bytes.fromhex(nonce))
    except ValueError as err:
        print(err)
        print("Test Passed.")
        return
    
    raise AssertionError("Test Failed.")


def _test_derive_key_hkdf_invalid_oem_rc_hash():
    """!
    Test case where length of OEM RC Hash is invalid.
    """
    # Nonce of length 32 bytes
    nonce                   =   "fb8d40ded206dc01f7368a42e20d2d04be68c7ff5f09665a81d50172346b1bb6"
    # Label is a string of length 32 bytes
    label                   =   "4a12a789d41cc278eaf412665a81d501"
    # Base Key of length 32 bytes
    base_key                =   "665a81d50172346b1bb6d92fdb98ff43fb8d40ded206dc01f7368a42e20d2d04"
    # OEM RC Hash of length 32 bytes
    oem_rc_hash             =   "be68c7ff5f09665a81d50172346b1bb6d92fdb98ff43fb8d40ded206dc01f736"
    # Debug State
    debug_state             =   DebugState.DISABLE
    # Secure Boot State
    secure_boot_state       =   False
    # Set algorithm to AES256_GCM
    algorithm               =   DerivedKeyAlgo.AES256_GCM
    # OEM ID
    oem_id                  =   0x1001
    # OEM Life Cycle State KDF is 0x06 ((is_oem_lcs_activated << 2) | oem_lcs)
    oem_lcs                 =   OEMLifeCycleState.OEM_LCS_DEVELOPMENT
    # Activation of OEM (boolean)
    is_oem_lcs_activated    =   True

    # Prepare KDF Context
    kdf_context = HKDFContext(
        debug_state,
        secure_boot_state,
        algorithm,
        oem_id,
        bytes.fromhex(oem_rc_hash),
        oem_lcs,
        is_oem_lcs_activated)
    try:
        # Key Derivation using HKDF
        derived_key = derive_key_hkdf(
            kdf_context,
            bytes.fromhex(base_key),
            label,
            bytes.fromhex(nonce))
    except ValueError as err:
        print(err)
        print("Test Passed.")
        return
    
    raise AssertionError("Test Failed.")


def _test_derive_key_hkdf_invalid_oem_id():
    """!
    Test case where value of OEM ID is invalid.
    """
    # Nonce of length 32 bytes
    nonce                   =   "fb8d40ded206dc01f7368a42e20d2d04be68c7ff5f09665a81d50172346b1bb6"
    # Label is a string of length 32 bytes
    label                   =   "4a12a789d41cc278eaf412665a81d501"
    # Base Key of length 32 bytes
    base_key                =   "665a81d50172346b1bb6d92fdb98ff43fb8d40ded206dc01f7368a42e20d2d04"
    # OEM RC Hash of length 64 bytes
    oem_rc_hash             =   "be68c7ff5f09665a81d50172346b1bb6d92fdb98ff43fb8d40ded206dc01f736"\
                                "8a42e20d2d04be68c7ff5f09665a81d54a12a789d41cc278eaf412665a81d501"
    # Debug State
    debug_state             =   DebugState.DISABLE
    # Secure Boot State
    secure_boot_state       =   False
    # Set algorithm to AES256_GCM
    algorithm               =   DerivedKeyAlgo.AES256_GCM
    # OEM ID should be within 2 bytes
    oem_id                  =   0x10001
    # OEM Life Cycle State KDF is 0x06 ((is_oem_lcs_activated << 2) | oem_lcs)
    oem_lcs                 =   OEMLifeCycleState.OEM_LCS_DEVELOPMENT
    # Activation of OEM (boolean)
    is_oem_lcs_activated    =   True

    # Prepare KDF Context
    kdf_context = HKDFContext(
        debug_state,
        secure_boot_state,
        algorithm,
        oem_id,
        bytes.fromhex(oem_rc_hash),
        oem_lcs,
        is_oem_lcs_activated)
    try:
        # Key Derivation using HKDF
        derived_key = derive_key_hkdf(
            kdf_context,
            bytes.fromhex(base_key),
            label,
            bytes.fromhex(nonce))
    except OverflowError as err:
        print(err)
        print("Test Passed.")
        return
    
    raise AssertionError("Test Failed.")


def _test_derive_key_hkdf_invalid_oem_lcs():
    """!
    Test case where value of OEM LCS is invalid.
    """
    # Nonce of length 32 bytes
    nonce                   =   "fb8d40ded206dc01f7368a42e20d2d04be68c7ff5f09665a81d50172346b1bb6"
    # Label is a string of length 32 bytes
    label                   =   "4a12a789d41cc278eaf412665a81d501"
    # Base Key of length 32 bytes
    base_key                =   "665a81d50172346b1bb6d92fdb98ff43fb8d40ded206dc01f7368a42e20d2d04"
    # OEM RC Hash of length 64 bytes
    oem_rc_hash             =   "be68c7ff5f09665a81d50172346b1bb6d92fdb98ff43fb8d40ded206dc01f736"\
                                "8a42e20d2d04be68c7ff5f09665a81d54a12a789d41cc278eaf412665a81d501"
    # Debug State
    debug_state             =   DebugState.DISABLE
    # Secure Boot State
    secure_boot_state       =   False
    # Set algorithm to AES256_GCM
    algorithm               =   DerivedKeyAlgo.AES256_GCM
    # OEM ID
    oem_id                  =   0x1001
    # OEM LCS should be an instance of OEMLifeCycleState
    oem_lcs                 =   1
    # Activation of OEM (boolean)
    is_oem_lcs_activated    =   True

    # Prepare KDF Context
    kdf_context = HKDFContext(
        debug_state,
        secure_boot_state,
        algorithm,
        oem_id,
        bytes.fromhex(oem_rc_hash),
        oem_lcs,
        is_oem_lcs_activated)
    try:
        # Key Derivation using HKDF
        derived_key = derive_key_hkdf(
            kdf_context,
            bytes.fromhex(base_key),
            label,
            bytes.fromhex(nonce))
    except TypeError as err:
        print(err)
        print("Test Passed.")
        return
    
    raise AssertionError("Test Failed.")


def _test_derive_key_hkdf_invalid_oem_lcs_activated():
    """!
    Test case where value of 'is_oem_lcs_activated' is invalid.
    """
    # Nonce of length 32 bytes
    nonce                   =   "fb8d40ded206dc01f7368a42e20d2d04be68c7ff5f09665a81d50172346b1bb6"
    # Label is a string of length 32 bytes
    label                   =   "4a12a789d41cc278eaf412665a81d501"
    # Base Key of length 48 bytes
    base_key                =   "665a81d50172346b1bb6d92fdb98ff43fb8d40ded206dc01f7368a42e20d2d04"
    # OEM RC Hash of length 64 bytes
    oem_rc_hash             =   "be68c7ff5f09665a81d50172346b1bb6d92fdb98ff43fb8d40ded206dc01f736"\
                                "8a42e20d2d04be68c7ff5f09665a81d54a12a789d41cc278eaf412665a81d501"
    # Debug State
    debug_state             =   DebugState.DISABLE
    # Secure Boot State
    secure_boot_state       =   False
    # Set algorithm to AES256_GCM
    algorithm               =   DerivedKeyAlgo.AES256_GCM
    # OEM ID
    oem_id                  =   0x1001
    # OEM Life Cycle State KDF is 0x06 ((is_oem_lcs_activated << 2) | oem_lcs)
    oem_lcs                 =   OEMLifeCycleState.OEM_LCS_DEVELOPMENT
    # This should be a boolean not integer
    is_oem_lcs_activated    =   1

    # Prepare KDF Context
    kdf_context = HKDFContext(
        debug_state,
        secure_boot_state,
        algorithm,
        oem_id,
        bytes.fromhex(oem_rc_hash),
        oem_lcs,
        is_oem_lcs_activated)
    try:
        # Key Derivation using HKDF
        derived_key = derive_key_hkdf(
            kdf_context,
            bytes.fromhex(base_key),
            label,
            bytes.fromhex(nonce))
    except TypeError as err:
        print(err)
        print("Test Passed.")
        return
    
    raise AssertionError("Test Failed.")


def _test_derive_key_nist():
    """!
    Test Vector 1: Where length of base key is 32 bytes and length of derived key is 32 bytes.
    Source: https://confluence.qualcomm.com/confluence/pages/viewpage.action?pageId=429503272#ZiggyKDFs&SecureWrapTool-TestVectorDefinition.1
    """
    # Nonce of length 32 bytes
    nonce                   =   "fb8d40ded206dc01f7368a42e20d2d04be68c7ff5f09665a81d50172346b1bb6"
    # Label is a string of length 32 bytes
    label                   =   "4a12a789d41cc278eaf412665a81d501"
    # Base Key of length 32 bytes
    base_key                =   "665a81d50172346b1bb6d92fdb98ff43fb8d40ded206dc01f7368a42e20d2d04"
    # Debug State
    debug_state             =   ROTDebugState.DISABLE
    # Set algorithm to AES256_GCM
    algorithm               =   DerivedKeyAlgo.AES256_GCM
    # OEM Product Seed of length 16 bytes
    oem_product_seed        =   "31fb36552c218e6a377f8a3251b4a2bf"
    # OEM Life Cycle State KDF is 0x06 ((is_oem_lcs_activated << 2) | oem_lcs)
    oem_lcs                 =   OEMLifeCycleState.OEM_LCS_DEVELOPMENT
    # Activation of OEM (boolean)
    is_oem_lcs_activated    =   True
    # Expected Output
    expected_output         =   "65d16e1649e7d5423fa79c4acb30cc5c7a2087245556d4c6f8ea6e40f9dccc9a"

    # Prepare KDF Context
    kdf_context = NISTKDFContext(debug_state, algorithm, bytes.fromhex(
        oem_product_seed), oem_lcs, is_oem_lcs_activated)
    
    # Key Derivation using NIST KDF
    derived_key = derive_key_nist(kdf_context, bytes.fromhex(base_key), label, bytes.fromhex(nonce))

    assert derived_key == bytes.fromhex(expected_output)
    print("Output Key Material:\n", hexlify(derived_key))
    print("Test Passed.\n")


def _test_derive_key_nist_invalid_nonce():
    """!
    Test case where length of nonce is invalid.
    """
    # Nonce of length 48 bytes
    nonce                   =   "fb8d40ded206dc01f7368a42e20d2d04be68c7ff5f09665a81d50172346b1bb6"\
                                "06dc01f78a42e20d2d04be68c7ff5f09"
    # Label is a string of length 32 bytes
    label                   =   "4a12a789d41cc278eaf412665a81d501"
    # Base Key of length 32 bytes
    base_key                =   "665a81d50172346b1bb6d92fdb98ff43fb8d40ded206dc01f7368a42e20d2d04"
    # Debug State
    debug_state             =   ROTDebugState.DISABLE
    # Set algorithm to AES256_GCM
    algorithm               =   DerivedKeyAlgo.AES256_GCM
    # OEM Product Seed of length 16 bytes
    oem_product_seed        =   "31fb36552c218e6a377f8a3251b4a2bf"
    # OEM Life Cycle State KDF is 0x06 ((is_oem_lcs_activated << 2) | oem_lcs)
    oem_lcs                 =   OEMLifeCycleState.OEM_LCS_DEVELOPMENT
    # Activation of OEM (boolean)
    is_oem_lcs_activated    =   True

    # Prepare KDF Context
    kdf_context = NISTKDFContext(debug_state, algorithm, bytes.fromhex(
        oem_product_seed), oem_lcs, is_oem_lcs_activated)
    try:
        # Key Derivation using NIST KDF
        derived_key = derive_key_nist(
            kdf_context,
            bytes.fromhex(base_key),
            label,
            bytes.fromhex(nonce))
    except ValueError as err:
        print(err)
        print("Test Passed.\n")
        return
    
    raise AssertionError("Test Failed.")


def _test_derive_key_nist_with_invalid_label():
    """!
    Test case where length of label is invalid.
    """
    # Nonce of length 32 bytes
    nonce                   =   "fb8d40ded206dc01f7368a42e20d2d04be68c7ff5f09665a81d50172346b1bb6"
    # Label is a string of length 64 bytes
    label                   =   "be68c7ff5f09665a81d50172346b1bb6d92fdb98ff43fb8d40ded206dc01f736"
    # Base Key of length 32 bytes
    base_key                =   "665a81d50172346b1bb6d92fdb98ff43fb8d40ded206dc01f7368a42e20d2d04"
    # Debug State
    debug_state             =   ROTDebugState.DISABLE
    # Set algorithm to AES256_GCM
    algorithm               =   DerivedKeyAlgo.AES256_GCM
    # OEM Product Seed of length 16 bytes
    oem_product_seed        =   "31fb36552c218e6a377f8a3251b4a2bf"
    # OEM Life Cycle State KDF is 0x06 ((is_oem_lcs_activated << 2) | oem_lcs)
    oem_lcs                 =   OEMLifeCycleState.OEM_LCS_DEVELOPMENT
    # Activation of OEM (boolean)
    is_oem_lcs_activated    =   True

    # Prepare KDF Context
    kdf_context = NISTKDFContext(debug_state, algorithm, bytes.fromhex(
        oem_product_seed), oem_lcs, is_oem_lcs_activated)
    try:
        # Key Derivation using NIST KDF
        derived_key = derive_key_nist(
            kdf_context,
            bytes.fromhex(base_key),
            label,
            bytes.fromhex(nonce))
    except ValueError as err:
        print(err)
        print("Test Passed.\n")
        return
    
    raise AssertionError("Test Failed.")


def _test_derive_key_nist_invalid_base_key():
    """!
    Test case where length of base key is invalid.
    """
    # Nonce of length 32 bytes
    nonce                   =   "fb8d40ded206dc01f7368a42e20d2d04be68c7ff5f09665a81d50172346b1bb6"
    # Label is a string of length 32 bytes
    label                   =   "4a12a789d41cc278eaf412665a81d501"
    # Base Key of length 48 bytes
    base_key                =   "665a81d50172346b1bb6d92fdb98ff43fb8d40ded206dc01f7368a42e20d2d04"\
                                "06dc01f78a42e20d2d04be68c7ff5f09"
    # Debug State
    debug_state             =   ROTDebugState.DISABLE
    # Set algorithm to AES256_GCM
    algorithm               =   DerivedKeyAlgo.AES256_GCM
    # OEM Product Seed of length 16 bytes
    oem_product_seed        =   "31fb36552c218e6a377f8a3251b4a2bf"
    # OEM Life Cycle State KDF is 0x06 ((is_oem_lcs_activated << 2) | oem_lcs)
    oem_lcs                 =   OEMLifeCycleState.OEM_LCS_DEVELOPMENT
    # Activation of OEM (boolean)
    is_oem_lcs_activated    =   True

    # Prepare KDF Context
    kdf_context = NISTKDFContext(debug_state, algorithm, bytes.fromhex(
        oem_product_seed), oem_lcs, is_oem_lcs_activated)
    try:
        # Key Derivation using NIST KDF
        derived_key = derive_key_nist(
            kdf_context,
            bytes.fromhex(base_key),
            label,
            bytes.fromhex(nonce))
    except ValueError as err:
        print(err)
        print("Test Passed.\n")
        return
    
    raise AssertionError("Test Failed.")


def _test_derive_key_nist_invalid_algorithm():
    """!
    Test case where value of algorithm is invalid.
    """
    # Nonce of length 32 bytes
    nonce                   =   "fb8d40ded206dc01f7368a42e20d2d04be68c7ff5f09665a81d50172346b1bb6"
    # Label is a string of length 32 bytes
    label                   =   "4a12a789d41cc278eaf412665a81d501"
    # Base Key of length 32 bytes
    base_key                =   "665a81d50172346b1bb6d92fdb98ff43fb8d40ded206dc01f7368a42e20d2d04"
    # Debug State
    debug_state             =   ROTDebugState.DISABLE
    # Algorithm should be an instance of DerivedKeyAlgo
    algorithm               =   0x18 << 14
    # OEM Product Seed of length 16 bytes
    oem_product_seed        =   "31fb36552c218e6a377f8a3251b4a2bf"
    # OEM Life Cycle State KDF is 0x06 ((is_oem_lcs_activated << 2) | oem_lcs)
    oem_lcs                 =   OEMLifeCycleState.OEM_LCS_DEVELOPMENT
    # Activation of OEM (boolean)
    is_oem_lcs_activated    =   True

    # Prepare KDF Context
    kdf_context = NISTKDFContext(debug_state, algorithm, bytes.fromhex(
        oem_product_seed), oem_lcs, is_oem_lcs_activated)
    try:
        # Key Derivation using NIST KDF
        derived_key = derive_key_nist(
            kdf_context,
            bytes.fromhex(base_key),
            label,
            bytes.fromhex(nonce))
    except TypeError as err:
        print(err)
        print("Test Passed.\n")
        return
    
    raise AssertionError("Test Failed.")


def _test_derive_key_nist_invalid_oem_product_seed():
    """!
    Test case where length of OEM Product Seed is invalid.
    """
    # Nonce of length 32 bytes
    nonce                   =   "fb8d40ded206dc01f7368a42e20d2d04be68c7ff5f09665a81d50172346b1bb6"
    # Label is a string of length 32 bytes
    label                   =   "4a12a789d41cc278eaf412665a81d501"
    # Base Key of length 32 bytes
    base_key                =   "665a81d50172346b1bb6d92fdb98ff43fb8d40ded206dc01f7368a42e20d2d04"
    # Debug State
    debug_state             =   ROTDebugState.DISABLE
    # Set algorithm to AES256_GCM
    algorithm               =   DerivedKeyAlgo.AES256_GCM
    # OEM Product Seed of length 32 bytes
    oem_product_seed        =   "31fb36552c218e6a377f8a3251b4a2bf06dc01f78a42e20d2d04be68c7ff5f09"
    # OEM Life Cycle State KDF is 0x06 ((is_oem_lcs_activated << 2) | oem_lcs)
    oem_lcs                 =   OEMLifeCycleState.OEM_LCS_DEVELOPMENT
    # Activation of OEM (boolean)
    is_oem_lcs_activated    =   True

    # Prepare KDF Context
    kdf_context = NISTKDFContext(debug_state, algorithm, bytes.fromhex(
        oem_product_seed), oem_lcs, is_oem_lcs_activated)
    try:
        # Key Derivation using NIST KDF
        derived_key = derive_key_nist(
            kdf_context,
            bytes.fromhex(base_key),
            label,
            bytes.fromhex(nonce))
    except ValueError as err:
        print(err)
        print("Test Passed.\n")
        return
    
    raise AssertionError("Test Failed.")


def _test_derive_key_nist_invalid_oem_lcs():
    """!
    Test case where value of OEM LCS is invalid.
    """
    # Nonce of length 32 bytes
    nonce                   =   "fb8d40ded206dc01f7368a42e20d2d04be68c7ff5f09665a81d50172346b1bb6"
    # Label is a string of length 32 bytes
    label                   =   "4a12a789d41cc278eaf412665a81d501"
    # Base Key of length 32 bytes
    base_key                =   "665a81d50172346b1bb6d92fdb98ff43fb8d40ded206dc01f7368a42e20d2d04"
    # Debug State
    debug_state             =   ROTDebugState.DISABLE
    # Set algorithm to AES256_GCM
    algorithm               =   DerivedKeyAlgo.AES256_GCM
    # OEM Product Seed of length 32 bytes
    oem_product_seed        =   "31fb36552c218e6a377f8a3251b4a2bf"
    # OEM LCS should be an instance of OEMLifeCycleState
    oem_lcs                 =   1
    # Activation of OEM (boolean)
    is_oem_lcs_activated    =   True

    # Prepare KDF Context
    kdf_context = NISTKDFContext(debug_state, algorithm, bytes.fromhex(
        oem_product_seed), oem_lcs, is_oem_lcs_activated)
    try:
        # Key Derivation using NIDT KDF
        derived_key = derive_key_nist(
            kdf_context,
            bytes.fromhex(base_key),
            label,
            bytes.fromhex(nonce))
    except TypeError as err:
        print(err)
        print("Test Passed.\n")
        return
    
    raise AssertionError("Test Failed.")


def _test_derive_key_nist_invalid_oem_lcs_activated():
    """!
    Test case where value of 'is_oem_lcs_activated' is invalid.
    """
    # Nonce of length 32 bytes
    nonce                   =   "fb8d40ded206dc01f7368a42e20d2d04be68c7ff5f09665a81d50172346b1bb6"
    # Label is a string of length 32 bytes
    label                   =   "4a12a789d41cc278eaf412665a81d501"
    # Base Key of length 32 bytes
    base_key                =   "665a81d50172346b1bb6d92fdb98ff43fb8d40ded206dc01f7368a42e20d2d04"
    # Debug State
    debug_state             =   ROTDebugState.DISABLE
    # Set algorithm to AES256_GCM
    algorithm               =   DerivedKeyAlgo.AES256_GCM
    # OEM Product Seed of length 16 bytes
    oem_product_seed        =   "31fb36552c218e6a377f8a3251b4a2bf"
    # OEM Life Cycle State KDF is 0x06 ((is_oem_lcs_activated << 2) | oem_lcs)
    oem_lcs                 =   OEMLifeCycleState.OEM_LCS_DEVELOPMENT
    # This should be boolean instead of integer
    is_oem_lcs_activated    =   1

    # Prepare KDF Context
    kdf_context = NISTKDFContext(debug_state, algorithm, bytes.fromhex(
        oem_product_seed), oem_lcs, is_oem_lcs_activated)
    try:
        # Key Derivation using NIST KDF
        derived_key = derive_key_nist(
            kdf_context,
            bytes.fromhex(base_key),
            label,
            bytes.fromhex(nonce))
    except TypeError as err:
        print(err)
        print("Test Passed.\n")
        return
    
    raise AssertionError("Test Failed.")


def tests_derive_key_hkdf():
    print("\n########## Derive Key using HKDF ###########\n")

    # This represent Life Cycle State of Root of Trust
    # Setting TME LCS to OP_INT to perform tests
    derive_key.DRV_TME_LCS = 0x0b

    print("\n########## Test1: Derive Key using HKDF with OEM batch secret ###########\n")
    _test_derive_hkdf_with_oem_batch_secret()

    print("\n########## Test2: Derive Key using HKDF with in_key 16 bytes and out_key 32 bytes ###########\n")
    _test_derive_hkdf_in_key_16_out_key_32()

    print("\n########## Test3: Derive Key using HKDF with in_key 32 bytes and out_key 32 bytes ###########\n")
    _test_derive_hkdf_in_key_32_out_key_32()

    print("\n########## Test4: Derive Key using HKDF with in_key 16 bytes and out_key 16 bytes ###########\n")
    _test_derive_hkdf_in_key_16_out_key_16()

    print("\n########## Test5: Derive Key using HKDF with in_key 32 bytes and out_key 16 bytes ###########\n")
    _test_derive_hkdf_in_key_32_out_key_16()

    print("\n########## Test6: Derive Key using HKDF with in_key P256 Shared secret and out_key 32 bytes ###########\n")
    _test_derive_hkdf_in_P256_shared_secret_out_key_32()

    print("\n########## Test7: Derive Key using HKDF with in_key P521 Shared secret and out_key 32 bytes ###########\n")
    _test_derive_hkdf_in_P521_shared_secret_out_key_32()

    # This represent Life Cycle State of Root of Trust
    # Setting TME LCS to OP_EXT
    derive_key.DRV_TME_LCS = 0x05

    print("\n########## Test8: Derive Key using HKDF with invalid Nonce ###########\n")
    _test_derive_key_hkdf_invalid_nonce()

    print("\n########## Test9: Derive Key using HKDF with invalid Label ###########\n")
    _test_derive_key_hkdf_with_invalid_label()

    print("\n########## Test10: Derive Key using HKDF with invalid Base Key ###########\n")
    _test_derive_key_hkdf_invalid_base_key()

    print("\n########## Test11: Derive Key using HKDF with invalid OEM RC Hash ###########\n")
    _test_derive_key_hkdf_invalid_oem_rc_hash()

    print("\n########## Test12: Derive Key using HKDF with invalid OEM ID ###########\n")
    _test_derive_key_hkdf_invalid_oem_id()

    print("\n########## Test13: Derive Key using HKDF with invalid OEM LCS ###########\n")
    _test_derive_key_hkdf_invalid_oem_lcs()

    print("\n########## Test14: Derive Key using HKDF with invalid OEM LCS Activated ###########\n")
    _test_derive_key_hkdf_invalid_oem_lcs_activated()


def tests_derive_key_nist():
    print("\n########## Derive Key using NIST ###########\n")

    print("\n########## Test1: Derive Key using NIST with all valid parameters ###########\n")
    _test_derive_key_nist()

    print("\n########## Test2: Derive Key using NIST with invalid Nonce ###########\n")
    _test_derive_key_nist_invalid_nonce()

    print("\n########## Test3: Derive Key using NIST with invalid Label ###########\n")
    _test_derive_key_nist_with_invalid_label()

    print("\n########## Test4: Derive Key using NIST with invalid Base Key ###########\n")
    _test_derive_key_nist_invalid_base_key()

    print("\n########## Test5: Derive Key using NIST with invalid Algorithm ###########\n")
    _test_derive_key_nist_invalid_algorithm()

    print("\n########## Test6: Derive Key using NIST with invalid OEM Product Seed ###########\n")
    _test_derive_key_nist_invalid_oem_product_seed()

    print("\n########## Test7: Derive Key using NIST with invalid OEM LCS ###########\n")
    _test_derive_key_nist_invalid_oem_lcs()

    print("\n########## Test8: Derive Key using NIST with invalid OEM LCS Activated ###########\n")
    _test_derive_key_nist_invalid_oem_lcs_activated()
