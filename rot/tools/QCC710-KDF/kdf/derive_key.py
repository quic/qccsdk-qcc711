#!/usr/bin/env python
"""!
@brief Derives a key from a base key using provided diversifiers.

@section
Copyright (c) 2020, 2022 Qualcomm Technologies, Inc.
All rights reserved.
Confidential and Proprietary - Qualcomm Technologies, Inc.
"""


from enum import Enum
from typing import Optional
from binascii import hexlify
from dataclasses import dataclass

from cryptography.hazmat.backends import _get_backend, default_backend
from cryptography.hazmat.primitives import hashes, hmac
from cryptography.hazmat.primitives.kdf.hkdf import HKDF


##
# @cond 0
# Length of Secure Boot State
DRV_SECURE_BOOT_STATE_LENGTH = 1
# Length of Debug State Length
DRV_DEBUG_STATE_LENGTH = 1
# Length of Life Cycle State
DRV_LCS_LENGTH = 1
# Length of OEM ID
DRV_OEM_ID_LENGTH = 2
# Length of algorithm
DRV_ALGORITHM_LENGTH = 4
# Length of BSVE
DRV_BSVE_LENGTH = 4
# Length of Key Length
DRV_KEY_LENGTH_LENGTH = 4
# Length of OEM Product Seed
DRV_OEM_PRODUCT_SEED_LENGTH = 16
# @anchor NONCE_LENGTH
# Length of Nonce
DRV_NONCE_LENGTH = 32
# @anchor BASE_KEY_16_LENGTH
# Length of Base Key (16 bytes)
DRV_BASE_KEY_16_LENGTH = 16
# @anchor BASE_KEY_32_LENGTH
# Length of Base Key (32 bytes)
DRV_BASE_KEY_32_LENGTH = 32
# @anchor BASE_KEY_68_LENGTH
# Length of Base Key (68 bytes)
DRV_BASE_KEY_68_LENGTH = 68
# Max length of output key (derived key)
DRV_MAX_OUTPUT_KEY_16_LENGTH = 16
# Max length of output key (derived key)
DRV_MAX_OUTPUT_KEY_32_LENGTH = 32
# Max length of output key (derived key)
DRV_MAX_OUTPUT_KEY_64_LENGTH = 64
# Max length of output key (derived key)
DRV_MAX_OUTPUT_KEY_68_LENGTH = 68
# Length of OEM RC Hash
DRV_OEM_RC_HASH_LENGTH = 64
# @anchor MAX_LABEL_LENGTH
# Max length of Label (Salt)
DRV_MAX_LABEL_LENGTH = 32
# Length of Label (Salt) with padding
DRV_LABEL_LENGTH = 64
# Length of Software Context
DRV_SW_CONTEXT_LENGTH = 128
# Endianess to convert interger to bytes
DRV_LITTLE_ENDIAN = "little"
# Stuffing Bytes
DRV_STUFF_BYTES = b'\x00'

# TME LCS for KDF Context
DRV_TME_LCS = 0x05
# PartyUInfo.Identity for KDF Context
DRV_PARTY_U_INFO_IDENTITY = "OEM"


@dataclass
class SecuritySelector(Enum):
    """!
    @anchor SecuritySelector
    Contains the list of Security Selectors.
    """
    SECURE_BOOT_STATE = 0x00000002
    DEBUG_STATE = 0x00000004
    TME_LCS = 0x00000008
    SW_CONTEXT = 0x00000020
    MIXING_KEY = 0x00000080
    CHIP_UNIQUE_ID = 0x00000100
    OEM_ID = 0x00001000
    OEM_PRODUCT_ID = 0x00002000
    OEM_RC_HASH = 0x00010000
    OEM_PRODUCT_SEED = 0x00020000
    OEM_LCS = 0x00200000


# @endcond
@dataclass
class DebugState(Enum):
    """!
    @anchor DebugState
    Contains the list of Debug States.
    """
    ENABLE = 0
    DISABLE = 1
    DISABLE_SINCE_BOOT = 2
    DISABLE_PERMANENT = 3
    DISABLE_FULL_PERMANENT = 4


@dataclass
class DerivedKeyAlgo(Enum):
    """!
    @anchor DerivedKeyAlgo
    Contains the list of algorithms used for using the derived key.
    """
    shift = 14

    ECC_ALGO_ECDSA = 0x00 << shift
    AES128_CBC = 0x04 << shift
    AES256_CBC = 0x05 << shift
    AES256_SIV = 0x0C << shift
    AES128_CTR = 0x0D << shift
    AES256_CTR = 0x0E << shift
    SHA256_HMAC = 0x12 << shift
    AES128_GCM = 0x17 << shift
    AES256_GCM = 0x18 << shift
    KDF_NIST = 0x20 << shift
    # Since HKDF_128, and HKDF_256 both use the same PRF, 
    # we use the same shift value for both
    HKDF_128 = 0x21 << shift
    HKDF_256 = 0x21 << shift


@dataclass
class OEMLifeCycleState(Enum):
    """!
    @anchor OEMLifeCycleState
    Contains the list of OEM Life Cycle States.
    """
    OEM_LCS_PRODUCTION = 0
    OEM_LCS_PROVISIONING = 1
    OEM_LCS_DEVELOPMENT = 2
    OEM_LCS_RMA = 3


@dataclass
class ROTDebugState(Enum):
    """!
    @anchor ROTDebugState
    Contains the list of Debug States for ROT.
    Bit0 of the debug disable vector will govern
    the ROT debug state. Bit0=0 for ENABLE else DISABLE.
    """
    ENABLE = 0
    DISABLE = 1


# @cond 0
@dataclass
class _KDF(Enum):
    """!
    Contains list of Key Derivation Functions.
    """
    HKDF = 0
    NIST = 1


@dataclass
class _PartyInfo:
    """!
    Consists of Party Info to create Software Context.
    """
    identity: bytes = None
    nonce: bytes = None
    other: bytes = None

    def __bytes__(self):
        info = [self.identity, self.nonce, self.other]
        p_info = list(filter(None, info))
        return b''.join(p_info)


@dataclass
class _SupPubInfo:
    """!
    Consists of Sup Pub Info to create Software Context.
    """
    protected: bytes = None
    other: bytes = None

    def __bytes__(self):
        info = [self.protected, self.other]
        s_info = list(filter(None, info))
        return b''.join(s_info)


@dataclass
class _SWContext:
    """!
    Consists of Algorithm, Party U Info, Party V Info and Sup Pub Info which creates the Software
    Context for HKDF and NIST.
    """
    algorithm: DerivedKeyAlgo = None
    u_info: _PartyInfo = None
    v_info: _PartyInfo = None
    s_info: _SupPubInfo = None

    def __init__(self, algorithm, party_u_info_identity, nonce):
        self.algorithm = algorithm
        self.u_info = _PartyInfo(bytes(party_u_info_identity, 'utf-8'), nonce)
        self.v_info = _PartyInfo()
        self.s_info = _SupPubInfo()

    def __bytes__(self):
        sw_ctxt = [
            self.algorithm.value.to_bytes(
                DRV_ALGORITHM_LENGTH, DRV_LITTLE_ENDIAN), bytes(
                self.u_info), bytes(
                self.v_info), bytes(
                self.s_info)]
        return b''.join(sw_ctxt)


@dataclass
class _HwContext:
    """!
    Consists of Secure Boot State, Debug State, TME Life Cycle State, Mixing Key, Chip Unique Id,
    OEM ID, OEM RC Hash, OEM Product Seed and OEM Life Cycle State KDF Context which creates
    Hardware Context for HKDF and NIST KDF.
    """
    variant: _KDF = None

    secure_boot_state: bytes = None
    debug_state: bytes = None
    tme_lcs: bytes = None
    mixing_key: bytes = None
    chip_unique_id: bytes = None

    oem_id: bytes = None
    oem_rc_hash: bytes = None
    oem_product_seed: bytes = None
    oem_lcs_kdf: bytes = None
    oem_product_id: bytes = None

    def __bytes__(self):
        hw = []
        if self.debug_state is not None:
            hw.append(self.debug_state)

        if self.tme_lcs is not None:
            hw.append(self.tme_lcs)

        if self.variant is _KDF.HKDF:
            if self.secure_boot_state is not None:
                hw.insert(0, self.secure_boot_state)

            if self.chip_unique_id is not None:
                hw.append(self.chip_unique_id)

            if self.oem_id is not None and self.oem_product_id is None:
                hw.append(DRV_STUFF_BYTES)
                hw.append(DRV_STUFF_BYTES)
                hw.append(self.oem_id)
            elif self.oem_id is None and self.oem_product_id is not None:
                hw.append(self.oem_product_id)
                hw.append(DRV_STUFF_BYTES)
                hw.append(DRV_STUFF_BYTES)
            elif self.oem_id is not None and self.oem_product_id is not None:
                hw.append(self.oem_product_id)
                hw.append(self.oem_id)

            if self.oem_rc_hash is not None:
                hw.append(self.oem_rc_hash)
        else:
            if self.mixing_key is not None:
                hw.append(self.mixing_key)
            hw.append(self.oem_product_seed)

        if self.oem_lcs_kdf is not None:
            hw.append(self.oem_lcs_kdf)

        hw_ctxt = list(filter(None, hw))

        return b''.join(hw_ctxt)


@dataclass
class _KDFContext:
    """!
    Consists of Label, Software Context, BSVE, Hardware Context and Key Length which creates KDF
    Context for HKDF and NIST KDF.
    """
    label: bytes = None
    sw_ctxt: _SWContext = None
    bsve: int = None
    hw_ctxt: _HwContext = None
    key_length: int = None

    def __bytes__(self):
        kdf = [
            self.label, self.sw_ctxt, self.bsve.to_bytes(
                DRV_BSVE_LENGTH, DRV_LITTLE_ENDIAN), bytes(
                self.hw_ctxt), self.key_length.to_bytes(
                DRV_KEY_LENGTH_LENGTH, DRV_LITTLE_ENDIAN)]
        kdf_ctxt = list(filter(None, kdf))
        return b''.join(kdf_ctxt)


# @endcond
@dataclass
class HKDFContext:
    """!
    @anchor HKDFContext
    Consists of Debug State, Secure Boot State, Algorithm, OEM ID, OEM RC Hash, OEM LCS,
    OEM LCS Activated, Chip Unique Id and OEM Product ID to create KDF Context for HKDF.

    Members of the class are as follows:
    @anchor debug_state
    - debug_state: <Class @ref DebugState> is an SoC debug enable condition. The default
    value is that the debug is @ref DebugState.DISABLE.
    @anchor secure_boot_state
    - secure_boot_state: bool is the OEM’s application authentication at boot condition. 
    The default value is False (no authentication).
    @anchor algorithm
    - algorithm: <Class @ref DerivedKeyAlgo> is the algorithm for which the derived key is used.
    @anchor oem_id
    - oem_id: int (Optional) is the OEM Identifier provided by Qualcomm.
    @anchor oem_rc_hash
    - oem_rc_hash: bytes (Optional) is the Root Certificate Hash the OEM shares with Qualcomm as 
    part of OEM Onboarding.
    @anchor oem_lcs
    - oem_lcs: <Class @ref OEMLifeCycleState> (Optional) is an OEM optionally controlled Life 
    Cycle State. The default value is @ref OEMLifeCycleState.OEM_LCS_PRODUCTION.
    @anchor is_oem_lcs_activated
    - is_oem_lcs_activated: bool (Optional) is an OEM LCS activation state. The default value 
    is False.
    - chip_unique_id: bytes (Optional) is the 8 bytes Chip Unique Id read from the chip.
    - oem_product_id: bytes (Optional) is the OEM Product Id provided by OEM.
    """
    debug_state: DebugState = None
    secure_boot_state: bool = None
    algorithm: DerivedKeyAlgo = None
    oem_id: int = None
    oem_rc_hash: bytes = None
    oem_lcs: OEMLifeCycleState = None
    is_oem_lcs_activated: bool = None
    chip_unique_id: bytes = None
    oem_product_id: bytes = None


@dataclass
class NISTKDFContext:
    """!
    @anchor NISTKDFContext
    Consists of Debug State, Algorithm, OEM Product Seed, OEM LCS and OEM LCS Activated to create 
    KDF Context for NIST KDF.

    Members of the class are as follows:
    - debug_state: <Class @ref DebugState>
    - algorithm: <Class @ref DerivedKeyAlgo>
    - oem_product_seed: bytes
    - oem_lcs: <Class @ref OEMLifeCycleState>
    - is_oem_lcs_activated: bool
    - mixing_key: bytes

    """
    debug_state: DebugState = None
    algorithm: DerivedKeyAlgo = None
    oem_product_seed: bytes = None
    oem_lcs: OEMLifeCycleState = None
    is_oem_lcs_activated: bool = None
    mixing_key: bytes = None


def _check_params(kdf_context: HKDFContext, base_key: bytes, label: str, nonce: bytes, party_u_info_identity: str):
    """!
    @param kdf_context: @ref HKDFContext <Class Object>.
    @param base_key: bytes containing Base Key of 32 bytes or 16 bytes.
    @param label: free-form label, maximum length is 32 bytes including the terminating NULL
    character.
    @param nonce: bytes containing a random number of 32 bytes.
    @param party_u_info_identity: str Party U Info Identity string to be used in KDF

    @exception ValueError: if algorithm or Base Key is None or length of Base Key, Label or Nonce
    is invalid.
    @exception TypeError: if the data type mismatches for any of the input arguments.
    """
    if kdf_context is None:
        raise ValueError("HKDFContext cannot be None.")
    elif kdf_context.algorithm is None:
        raise ValueError("'algorithm' cannot be None.")
    elif base_key is None:
        raise ValueError("Base Key cannot be None.")
    elif party_u_info_identity is None:
        raise ValueError("Party U Info Identity cannot be None.")
    elif kdf_context.debug_state is not None and not isinstance(kdf_context.debug_state, DebugState):
        raise TypeError(
            "'debug_state' must be of type <Class DebugState>, not {}.".format(
                type(
                    kdf_context.debug_state).__name__))
    elif kdf_context.secure_boot_state is not None and not isinstance(kdf_context.secure_boot_state, bool):
        raise TypeError("'secure_boot_state' must be boolean, not {}.".format(
            type(kdf_context.secure_boot_state).__name__))
    elif not isinstance(kdf_context.algorithm, DerivedKeyAlgo):
        raise TypeError(
            "'algorithm' must be of type <Class DerivedKeyAlgo>, not {}.".format(
                type(
                    kdf_context.algorithm).__name__))
    elif not isinstance(base_key, bytes):
        raise TypeError("'base_key' must be bytes, not {}.".format(type(base_key).__name__))
    elif (len(base_key) != DRV_BASE_KEY_16_LENGTH) and (len(base_key) != DRV_BASE_KEY_32_LENGTH) and (
            len(base_key) != DRV_BASE_KEY_68_LENGTH):
        raise ValueError(
            "Length of Base key can be {0}, {1} or {2} bytes.".format(
                DRV_BASE_KEY_16_LENGTH,
                DRV_BASE_KEY_32_LENGTH,
                DRV_BASE_KEY_68_LENGTH))
    elif label is not None and len(label) > DRV_MAX_LABEL_LENGTH:
        raise ValueError(
            "Length of Label exceeds by {0} bytes.".format(
                len(label) - DRV_MAX_LABEL_LENGTH))
    elif nonce is not None and len(nonce) != DRV_NONCE_LENGTH:
        raise ValueError(
            "Length of Nonce exceeds by {0} bytes.".format(
                len(nonce) - DRV_NONCE_LENGTH))
    elif not isinstance(party_u_info_identity, str):
        raise TypeError("'party_u_info_identity' must be str, not {}.".format(type(party_u_info_identity).__name__))
    elif kdf_context.chip_unique_id is not None and not isinstance(kdf_context.chip_unique_id, bytes):
        raise TypeError("'chip_unique_id' must be bytes, not {}.".format(type(kdf_context.chip_unique_id).__name__))
    elif kdf_context.oem_product_id is not None and not isinstance(kdf_context.oem_product_id, bytes):
        raise TypeError("'oem_product_id' must be bytes, not {}.".format(type(kdf_context.oem_product_id).__name__))
    else:
        NotImplemented
    return


def _hkdf_check_params(kdf_context: HKDFContext, base_key: bytes, label: str, nonce: bytes):
    """!
    @param kdf_context: @ref HKDFContext <Class Object>.
    @param base_key: bytes containing Base Key of 32 bytes or 16 bytes.
    @param label: free-form label, maximum length is 32 bytes including the terminating NULL
    character.
    @param nonce: bytes containing a random number of 32 bytes.

    @exception ValueError: if any of the argument is None except the Nonce and Label or length of
    OEM RC Hash, Base Key or Nonce is invalid.
    @exception TypeError: if the data type mismatches for any of the input arguments.
    @exception OverflowError: if length of OEM ID is invalid.
    """
    if kdf_context is None:
        raise ValueError("HKDFContext cannot be None.")
    elif kdf_context.debug_state is None:
        raise ValueError("Debug State cannot be None.")
    elif kdf_context.secure_boot_state is None:
        raise ValueError("Secure Boot State cannot be None.")
    elif kdf_context.algorithm is None:
        raise ValueError("'algorithm' cannot be None.")
    elif kdf_context.oem_id is None:
        raise ValueError("'oem_id' cannot be None.")
    elif kdf_context.oem_rc_hash is None:
        raise ValueError("'oem_rc_hash' cannot be None.")
    elif kdf_context.oem_lcs is None:
        raise ValueError("'oem_lcs' cannot be None.")
    elif kdf_context.is_oem_lcs_activated is None:
        raise ValueError("'is_oem_lcs_activated' cannot be None.")
    elif not isinstance(kdf_context.debug_state, DebugState):
        raise TypeError(
            "'debug_state' must be of type <Class DebugState>, not {}.".format(
                type(
                    kdf_context.debug_state).__name__))
    elif not isinstance(kdf_context.secure_boot_state, bool):
        raise TypeError("'secure_boot_state' must be boolean, not {}.".format(
            type(kdf_context.secure_boot_state).__name__))
    elif not isinstance(kdf_context.algorithm, DerivedKeyAlgo):
        raise TypeError(
            "'algorithm' must be of type <Class DerivedKeyAlgo>, not {}.".format(
                type(
                    kdf_context.algorithm).__name__))
    elif not isinstance(kdf_context.oem_id, int):
        raise TypeError("'oem_id' must be int, not {}.".format(type(kdf_context.oem_id).__name__))
    elif not isinstance(kdf_context.oem_rc_hash, bytes):
        raise TypeError(
            "'oem_rc_hash' must be bytes, not {}.".format(
                type(
                    kdf_context.oem_rc_hash).__name__))
    elif not isinstance(kdf_context.oem_lcs, OEMLifeCycleState):
        raise TypeError(
            "'oem_lcs' must be of type <Class OEMLifeCycleState>, not {}.".format(
                type(
                    kdf_context.oem_lcs).__name__))
    elif not isinstance(kdf_context.is_oem_lcs_activated, bool):
        raise TypeError("'is_oem_lcs_activated' must be boolean, not {}.".format(
            type(kdf_context.is_oem_lcs_activated).__name__))
    elif len(kdf_context.oem_rc_hash) != DRV_OEM_RC_HASH_LENGTH:
        raise ValueError("'oem_rc_hash' must be {} bytes.".format(DRV_OEM_RC_HASH_LENGTH))
    else:
        NotImplemented

    _check_params(kdf_context, base_key, label, nonce, DRV_PARTY_U_INFO_IDENTITY)

    try:
        kdf_context.oem_id.to_bytes(DRV_OEM_ID_LENGTH, DRV_LITTLE_ENDIAN)
    except OverflowError:
        raise OverflowError("'oem_id' must be {0} bytes.".format(DRV_OEM_ID_LENGTH))
    except AttributeError:
        NotImplemented


def _derive_key_internal(kdf_context: HKDFContext,
                         base_key: bytes = None,
                         label: Optional[str] = None,
                         nonce: Optional[bytes] = None,
                         party_u_info_identity: Optional[str] = DRV_PARTY_U_INFO_IDENTITY,
                         use_tme_lcs: Optional[bool] = True):
    """!
    Returns the key derivation key derived from base key using HKDF.

    HKDF is a simple key derivation function (KDF) based on a hash-based message authentication
    code (HMAC). It extracts a random key using an HMAC hash function on an optional salt (label).
    This API supports HKDF SHA-256.

    @param kdf_context: @ref HKDFContext <Class Object>.
    @param base_key: bytes containing Base Key of 32 bytes or 16 bytes.
    @param label: (Optional) free-form label, maximum length is 32 bytes including the terminating
    NULL character.
    @param nonce: (Optional) bytes containing a random number of 32 bytes.
    @param party_u_info_identity: (Optional) str Party U Info Identity string to be used in KDF.
    Default value is @ref DRV_PARTY_U_INFO_IDENTITY
    @param use_tme_lcs: (Optional) bool flag to decide whether to include TME LCS in KDF Context or not.
    Default value is set to True to make sure it TME LCS is included by default.

    @exception ValueError: if algorithm or Base Key is None or length of Base Key, Label or Nonce
    is invalid.
    @exception TypeError: if the data type mismatches for any of the input arguments.

    @retval bytes: containing a cryptographic key with a length based on provided supported
    algorithm <Class @ref DerivedKeyAlgo>.
    """
    # Check parameters
    _check_params(kdf_context, base_key, label, nonce, party_u_info_identity)

    # Prepare label for KDF Context
    # Length of @ref LABEL_LENGTH bytes and pad zeroes until
    # 64 bytes
    if label is not None:
        label = label[:DRV_MAX_LABEL_LENGTH]
    else:
        label = ""

    # Padded label consists of label with upto 64 bytes padding and
    # 4 bytes of spacer word, So total length of the padded label is
    # 68 bytes.
    padded_label = label.ljust((DRV_LABEL_LENGTH + 4), '\x00')
    print("Label:\n", padded_label, "\n")

    # Prepare Software Context for KDF Context
    # Append zeroes until MAX_SW_CONTEXT_LENGTH bytes
    sw_ctxt = _SWContext(kdf_context.algorithm, party_u_info_identity, nonce)
    padded_sw_ctxt = bytes(sw_ctxt).ljust(DRV_SW_CONTEXT_LENGTH, b'\x00')
    print("SW Context:\n", hexlify(padded_sw_ctxt), "\n")

    # Prepare Security Context Selector for KDF Context
    bsve = 0x00

    # Set Secure Boot State for Hardware Context and update Security Selector
    if kdf_context.secure_boot_state is None:
        secure_boot = None
    else:
        secure_boot = kdf_context.secure_boot_state.to_bytes(DRV_SECURE_BOOT_STATE_LENGTH, DRV_LITTLE_ENDIAN)
        bsve = bsve | SecuritySelector.SECURE_BOOT_STATE.value

    # Set Debug State for Hardware Context and update Security Selector
    if kdf_context.debug_state is None:
        debug_state = None
    else:
        if kdf_context.debug_state.value == DebugState.ENABLE.value:
            state_debug = True
        else:
            state_debug = False
        debug_state = state_debug.to_bytes(DRV_DEBUG_STATE_LENGTH, DRV_LITTLE_ENDIAN)
        bsve = bsve | SecuritySelector.DEBUG_STATE.value

    # Set TME LCS for Hardware Context and update Security Selector
    if use_tme_lcs:
        tme_lcs = DRV_TME_LCS.to_bytes(DRV_LCS_LENGTH, DRV_LITTLE_ENDIAN)
        bsve = bsve | SecuritySelector.TME_LCS.value
    else:
        tme_lcs = None

    # Update Security Selector to make SW Context as part of KDF Context
    bsve = bsve | SecuritySelector.SW_CONTEXT.value

    # Set OEM ID for Hardware Context and update Security Selector
    if kdf_context.oem_id is None:
        oem_id = None
    else:
        oem_id = kdf_context.oem_id.to_bytes(DRV_OEM_ID_LENGTH, DRV_LITTLE_ENDIAN)
        bsve = bsve | SecuritySelector.OEM_ID.value

    # Set OEM RC Hash for Hardware Context and update Security Selector
    if kdf_context.oem_rc_hash is None:
        oem_rc_hash = None
    else:
        oem_rc_hash = kdf_context.oem_rc_hash
        bsve = bsve | SecuritySelector.OEM_RC_HASH.value

    # Set OEM LCS KDF Context for Hardware Context and update Security Selector
    # Encode OEM LCS and generate OEM LCS KDF Context
    if kdf_context.oem_lcs is None or kdf_context.is_oem_lcs_activated is None:
        oem_lcs_kdf_ctxt = None
    else:
        oem_lcs_kdf = (kdf_context.is_oem_lcs_activated << 2) | kdf_context.oem_lcs.value
        oem_lcs_kdf_ctxt = oem_lcs_kdf.to_bytes(DRV_LCS_LENGTH, DRV_LITTLE_ENDIAN)
        bsve = bsve | SecuritySelector.OEM_LCS.value

    # Set OEM Product Id for Hardware Context and update Security Selector
    if kdf_context.oem_product_id is None:
        oem_product_id = None
    else:
        oem_product_id = kdf_context.oem_product_id
        bsve = bsve | SecuritySelector.OEM_PRODUCT_ID.value

    # Set Chip Unique Id for Hardware Context and update Security Selector
    if kdf_context.chip_unique_id is None:
        chip_unique_id = None
    else:
        chip_unique_id = kdf_context.chip_unique_id
        bsve = bsve | SecuritySelector.CHIP_UNIQUE_ID.value

    print("BSVE:\n", hex(bsve), "\n")

    # Prepare Hardware Context for KDF Context
    hw_ctxt = _HwContext(
        variant=_KDF.HKDF,
        secure_boot_state=secure_boot,
        debug_state=debug_state,
        tme_lcs=tme_lcs,
        chip_unique_id=chip_unique_id,
        oem_id=oem_id,
        oem_rc_hash=oem_rc_hash,
        oem_lcs_kdf=oem_lcs_kdf_ctxt,
        oem_product_id=oem_product_id)
    print("HW Context:\n", hexlify(bytes(hw_ctxt)), "\n")

    # Get Key Length based on algorithm
    if kdf_context.algorithm is DerivedKeyAlgo.AES128_CBC:
        key_length = DRV_MAX_OUTPUT_KEY_16_LENGTH
    elif kdf_context.algorithm is DerivedKeyAlgo.AES128_CTR:
        key_length = DRV_MAX_OUTPUT_KEY_16_LENGTH
    elif kdf_context.algorithm is DerivedKeyAlgo.AES128_GCM:
        key_length = DRV_MAX_OUTPUT_KEY_16_LENGTH
    elif kdf_context.algorithm is DerivedKeyAlgo.HKDF_128:
        key_length = DRV_MAX_OUTPUT_KEY_16_LENGTH
    elif kdf_context.algorithm is DerivedKeyAlgo.AES256_CBC:
        key_length = DRV_MAX_OUTPUT_KEY_32_LENGTH
    elif kdf_context.algorithm is DerivedKeyAlgo.AES256_CTR:
        key_length = DRV_MAX_OUTPUT_KEY_32_LENGTH
    elif kdf_context.algorithm is DerivedKeyAlgo.AES256_GCM:
        key_length = DRV_MAX_OUTPUT_KEY_32_LENGTH
    elif kdf_context.algorithm is DerivedKeyAlgo.SHA256_HMAC:
        key_length = DRV_MAX_OUTPUT_KEY_32_LENGTH
    elif kdf_context.algorithm is DerivedKeyAlgo.HKDF_256:
        key_length = DRV_MAX_OUTPUT_KEY_32_LENGTH
    elif kdf_context.algorithm is DerivedKeyAlgo.KDF_NIST:
        key_length = DRV_MAX_OUTPUT_KEY_32_LENGTH
    else:
        raise ValueError("Invalid algorithm")

    number_of_bits = key_length * 8
    if key_length == DRV_MAX_OUTPUT_KEY_68_LENGTH:
        number_of_bits = 521

    # Prepare KDF Context
    kdf_ctxt = _KDFContext(bytes(padded_label,
                                 'utf-8'), padded_sw_ctxt, bsve, hw_ctxt, number_of_bits)
    print("KDF Context:\n", hexlify(bytes(kdf_ctxt)), "\n")

    # Generate Derived Key using HKDF where,
    # Algorithm used is SHA256,
    # First 32 bytes of Label is used,
    # KDF Context is provided as HMAC input.
    derived_key = HKDF(algorithm=hashes.SHA256(),
                       length=key_length,
                       salt=bytes(padded_label[:DRV_LABEL_LENGTH], "utf-8"),
                       info=bytes(kdf_ctxt),
                       backend=default_backend()).derive(base_key)

    return derived_key


def derive_key_hkdf(kdf_context: HKDFContext,
                    base_key: bytes = None,
                    label: Optional[str] = None,
                    nonce: Optional[bytes] = None) -> bytes:
    """!
    Returns the key derivation key derived from base key using HKDF.

    HKDF is a simple key derivation function (KDF) based on a hash-based message authentication
    code (HMAC). It extracts a random key using an HMAC hash function on an optional salt (label).
    This API supports HKDF SHA-256.

    @param kdf_context: @ref HKDFContext <Class Object>.
    @param base_key: bytes containing Base Key of 16 bytes, 32 bytes or 68 bytes. Base Key might be
    required to be word aligned i.e. little endian 0 padded as per the table below
                    Base Key                    Length Supported         Padding
                    ========                    ================         =======
    -              Symmetric Key                      16/32                N.A.
    -P256 based Shared Secret(X-Coordinate Only)       32          Little endian 0 padded
    -P521 based Shared Secret(X-Coordinate Only)       68          Little endian 0 padded

    A word is of 4 bytes. So in case of a 66 bytes(x coordinate only) shared secret belonging to
    curve P521, 2 bytes will have to be added at the beginning in order to make it 68 bytes.
    Whereas a 32 bytes(x coordinate only) shared secret belonging to curve P256 can be directly
    used as Base Key. 
    @param label: (Optional) free-form label, maximum length is 32 bytes including the terminating
    NULL character.
    @param nonce: (Optional) bytes containing a random number of 32 bytes.

    @exception ValueError: if any of the argument is None except the Nonce and Label or length of 
    OEM RC Hash, Base Key or Nonce is invalid.
    @exception TypeError: if the data type mismatches for any of the input arguments.
    @exception OverflowError: if length of OEM ID is invalid.

    @retval bytes: containing a cryptographic key with a length based on provided supported
    algorithm <Class @ref DerivedKeyAlgo>.
    """
    # Check parameters
    _hkdf_check_params(kdf_context, base_key, label, nonce)

    # Generate Derived Key
    derived_key = _derive_key_internal(kdf_context, base_key, label, nonce, DRV_PARTY_U_INFO_IDENTITY)

    return derived_key


def _nist_check_params(kdf_context: NISTKDFContext, base_key: bytes, label: str, nonce: bytes,
                       party_u_info_identity: str):
    """!
    @param kdf_context: @ref NISTKDFContext <Class Object>.
    @param base_key: bytes containing Base Key of 32 bytes or 16 bytes.
    @param label: (Optional) free-form label, maximum length is 32 bytes including the terminating
    NULL character.
    @param nonce: (Optional) bytes containing a random number of 32 bytes.
    @param party_u_info_identity: str Party U Info Identity string to be used in KDF

    @exception ValueError: if any of the argument is None except the Nonce or length of
    OEM Product Seed, Base Key or Nonce is invalid.
    @exception TypeError: if the data type mismatches for any of the input arguments.
    """
    if kdf_context is None:
        raise ValueError("NISTKDFContext cannot be None.")
    elif kdf_context.debug_state is None:
        raise ValueError("Debug State cannot be None.")
    elif kdf_context.algorithm is None:
        raise ValueError("'algorithm' cannot be None.")
    elif kdf_context.oem_product_seed is None:
        raise ValueError("'oem_product_seed' cannot be None.")
    elif kdf_context.oem_lcs is None:
        raise ValueError("'oem_lcs' cannot be None.")
    elif kdf_context.is_oem_lcs_activated is None:
        raise ValueError("'is_oem_lcs_activated' cannot be None.")
    elif base_key is None:
        raise ValueError("Base Key cannot be None.")
    elif party_u_info_identity is None:
        raise ValueError("Party U Info Identity cannot be None.")
    elif not isinstance(kdf_context.debug_state, ROTDebugState):
        raise TypeError(
            "'debug_state' must be of type <Class DebugState>, not {}.".format(
                type(
                    kdf_context.debug_state).__name__))
    elif not isinstance(kdf_context.algorithm, DerivedKeyAlgo):
        raise TypeError(
            "'algorithm' must be of type <Class DerivedKeyAlgo>, not {}.".format(
                type(
                    kdf_context.algorithm).__name__))
    elif not isinstance(kdf_context.oem_product_seed, bytes):
        raise TypeError(
            "'oem_product_seed' must be bytes, not {}.".format(
                type(
                    kdf_context.oem_product_seed).__name__))
    elif not isinstance(kdf_context.oem_lcs, OEMLifeCycleState):
        raise TypeError(
            "'oem_lcs' must be of type <Class OEMLifeCycleState>, not {}.".format(
                type(
                    kdf_context.oem_lcs).__name__))
    elif not isinstance(kdf_context.is_oem_lcs_activated, bool):
        raise TypeError("'is_oem_lcs_activated' must be boolean, not {}.".format(
            type(kdf_context.is_oem_lcs_activated).__name__))
    elif not isinstance(base_key, bytes):
        raise TypeError("'base_key' must be bytes, not {}.".format(type(base_key).__name__))
    elif not isinstance(party_u_info_identity, str):
        raise TypeError("'party_u_info_identity' must be str, not {}.".format(type(party_u_info_identity).__name__))
    elif len(kdf_context.oem_product_seed) != DRV_OEM_PRODUCT_SEED_LENGTH:
        raise ValueError("'oem_product_seed' must be {} bytes.".format(DRV_OEM_PRODUCT_SEED_LENGTH))
    elif (len(base_key) != DRV_BASE_KEY_16_LENGTH) and (len(base_key) != DRV_BASE_KEY_32_LENGTH):
        raise ValueError(
            "Length of Base key can be {0} or {1} bytes.".format(
                DRV_BASE_KEY_16_LENGTH,
                DRV_BASE_KEY_32_LENGTH))
    elif label is not None and len(label) > DRV_MAX_LABEL_LENGTH:
        raise ValueError(
            "Length of Label exceeds by {0} bytes.".format(
                len(label) - DRV_MAX_LABEL_LENGTH))
    elif nonce is not None and len(nonce) != DRV_NONCE_LENGTH:
        raise ValueError(
            "Length of Nonce exceeds by {0} bytes.".format(
                len(nonce) - DRV_NONCE_LENGTH))
    elif kdf_context.mixing_key is not None and not isinstance(kdf_context.mixing_key, bytes):
        raise TypeError("'mixing_key' must be bytes, not {}.".format(type(kdf_context.mixing_key).__name__))
    else:
        NotImplemented


def derive_key_nist(kdf_context: NISTKDFContext,
                    base_key: bytes = None,
                    label: Optional[str] = None,
                    nonce: Optional[bytes] = None,
                    party_u_info_identity: Optional[str] = DRV_PARTY_U_INFO_IDENTITY) -> bytes:
    """!
    Returns the key derivation key derived from base key using NIST.

    This API supports NIST KDF SHA-512.

    @param kdf_context: @ref NISTKDFContext <Class Object>.
    @param base_key: bytes containing Base Key of 32 bytes or 16 bytes.
    @param label: (Optional) free-form label, maximum length is 32 bytes including the terminating
    NULL character.
    @param nonce: (Optional) bytes containing a random number of 32 bytes.
    @param party_u_info_identity: (Optional) str Party U Info Identity string to be used in KDF.
    Default value is @ref DRV_PARTY_U_INFO_IDENTITY

    @exception ValueError: if any of the argument in array is None except the Nonce or length of
    OEM Product Seed, Base Key or Nonce is invalid.
    @exception TypeError: if the data type mismatches for any of the input arguments.

    @retval bytes: containing a cryptographic key with a length based on provided supported
    algorithm.
    """
    # Check Parameters
    _nist_check_params(kdf_context, base_key, label, nonce, party_u_info_identity)

    # Prepare label for KDF Context
    # Length of @ref LABEL_LENGTH bytes and pad zeroes until
    # 64 bytes
    if label is not None:
        label = label[:DRV_MAX_LABEL_LENGTH]
    else:
        label = ""

    # Padded label consists of label with upto 64 bytes padding and
    # 4 bytes of spacer word, So total length of the padded label is
    # 68 bytes.
    padded_label = label.ljust((DRV_LABEL_LENGTH + 4), '\x00')
    print("Label:\n", padded_label, "\n")

    # Prepare Software Context for KDF Context
    # Append zeroes until MAX_SW_CONTEXT_LENGTH bytes
    sw_ctxt = _SWContext(kdf_context.algorithm, party_u_info_identity, nonce)
    padded_sw_ctxt = bytes(sw_ctxt).ljust(DRV_SW_CONTEXT_LENGTH, b'\x00')
    print("SW Context:\n", hexlify(padded_sw_ctxt), "\n")

    # Prepare Security Context Selector for KDF Context
    bsve = 0x00

    # Set Debug State for Hardware Context and update Security Selector
    if kdf_context.debug_state.value == ROTDebugState.ENABLE.value:
        state_debug = True
    else:
        state_debug = False
    debug_state = state_debug.to_bytes(DRV_DEBUG_STATE_LENGTH, DRV_LITTLE_ENDIAN)
    bsve = bsve | SecuritySelector.DEBUG_STATE.value

    # Set TME LCS for Hardware Context and update Security Selector
    tme_lcs = DRV_TME_LCS.to_bytes(DRV_LCS_LENGTH, DRV_LITTLE_ENDIAN)
    bsve = bsve | SecuritySelector.TME_LCS.value

    # Update Security Selector to make SW Context as part of KDF Context
    bsve = bsve | SecuritySelector.SW_CONTEXT.value

    # Set OEM Product Seed for Hardware Context and update Security Selector
    oem_product_seed = kdf_context.oem_product_seed
    bsve = bsve | SecuritySelector.OEM_PRODUCT_SEED.value

    # Set OEM LCS KDF Context for Hardware Context and update Security Selector
    # Encode OEM LCS and generate OEM LCS KDF Context
    oem_lcs_kdf = (kdf_context.is_oem_lcs_activated << 2) | kdf_context.oem_lcs.value
    oem_lcs_kdf_ctxt = oem_lcs_kdf.to_bytes(DRV_LCS_LENGTH, DRV_LITTLE_ENDIAN)
    bsve = bsve | SecuritySelector.OEM_LCS.value

    # Set Mixing Key for Hardware Context and update Security Selector
    if kdf_context.mixing_key is None:
        mixing_key = None
    else:
        mixing_key = kdf_context.mixing_key
        bsve = bsve | SecuritySelector.MIXING_KEY.value

    print("BSVE:\n", hex(bsve), "\n")

    # Prepare Hardware Context for KDF Context
    hw_ctxt = _HwContext(
        variant=_KDF.NIST,
        debug_state=debug_state,
        tme_lcs=tme_lcs,
        oem_product_seed=oem_product_seed,
        oem_lcs_kdf=oem_lcs_kdf_ctxt,
        mixing_key=mixing_key)
    print("Hw Context:\n", hexlify(bytes(hw_ctxt)), "\n")

    # Get Key Length based on algorithm
    if kdf_context.algorithm is DerivedKeyAlgo.AES128_CBC:
        key_length = DRV_MAX_OUTPUT_KEY_16_LENGTH
    elif kdf_context.algorithm is DerivedKeyAlgo.AES128_CTR:
        key_length = DRV_MAX_OUTPUT_KEY_16_LENGTH
    elif kdf_context.algorithm is DerivedKeyAlgo.AES128_GCM:
        key_length = DRV_MAX_OUTPUT_KEY_16_LENGTH
    elif kdf_context.algorithm is DerivedKeyAlgo.AES256_CBC:
        key_length = DRV_MAX_OUTPUT_KEY_32_LENGTH
    elif kdf_context.algorithm is DerivedKeyAlgo.AES256_CTR:
        key_length = DRV_MAX_OUTPUT_KEY_32_LENGTH
    elif kdf_context.algorithm is DerivedKeyAlgo.AES256_GCM:
        key_length = DRV_MAX_OUTPUT_KEY_32_LENGTH
    elif kdf_context.algorithm is DerivedKeyAlgo.AES256_SIV:
        # This is a special case, where the key length of 
        # the derived key is 64 bytes instead of 32 bytes as 
        # per algorithm. 
        # This derived key is used for generating Secure Wrap.
        key_length = DRV_MAX_OUTPUT_KEY_64_LENGTH
    elif kdf_context.algorithm is DerivedKeyAlgo.ECC_ALGO_ECDSA:
        key_length = DRV_MAX_OUTPUT_KEY_68_LENGTH
    else:
        raise ValueError("Invalid algorithm")

    number_of_bits = key_length * 8
    if key_length == DRV_MAX_OUTPUT_KEY_68_LENGTH:
        number_of_bits = 521

    # Prepare KDF Context
    kdf_ctxt = _KDFContext(bytes(padded_label,
                                 'utf-8'), padded_sw_ctxt, bsve, hw_ctxt, number_of_bits)
    print("KDF Context:\n", hexlify(bytes(kdf_ctxt)), "\n")

    # Generate Derived Key using HKDF where,
    # Algorithm used is SHA512,
    # Counter is provided as HMAC input,
    # KDF Context is provided as HMAC input.
    algorithm = hashes.SHA512()
    backend = _get_backend(default_backend())
    max_length = 255 * algorithm.digest_size

    if key_length > max_length:
        raise ValueError(
            "Can not derive keys larger than {} octets.".format(max_length)
        )

    output = [b""]
    counter = 1
    while algorithm.digest_size * (len(output) - 1) < key_length:
        h = hmac.HMAC(base_key, algorithm, backend=backend)
        h.update(bytes([counter]))
        h.update(bytes(kdf_ctxt))
        output.append(h.finalize())
        counter += 1

    return b"".join(output)[:key_length]
