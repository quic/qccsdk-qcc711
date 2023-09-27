# ===============================================================================
#
#  Copyright (c) 2021 Qualcomm Technologies, Inc.
#  All Rights Reserved.
#  Confidential and Proprietary - Qualcomm Technologies, Inc.
#
# ===============================================================================
from os import urandom
from struct import pack
from typing import Any, List, Tuple

try:
    from common.crypto.crypto_ccm import encrypt
except ModuleNotFoundError:
    # noinspection PyUnusedLocal
    def encrypt(message: bytes, key: bytes, iv: bytes, associated_data: bytes) -> bytes:
        raise RuntimeError("OEM must implement AES CCM logic.")


# noinspection PyUnusedLocal
def get_wrapped_l2_wrapped_l3_clear_l3(image_inspectable_data: Any, root_key_type: int,
                                       encrypted_segment_indices: List[int], security_profile: Any,
                                       plugin_encrypter_args: str, **kwargs: Any) -> Tuple[bytes, bytes, bytes]:
    """
    A plugin encrypter example capable of generation Encryption Parameters compliant with the UIE 1.0 L2 1.0
    specification. OEM must implement AES CCM encrypt functionality.
    """
    # DO NOT UNDER ANY CIRCUMSTANCE USE THE L1 KEY PRESENT IN THIS EXAMPLE FOR PRODUCTION PURPOSES. In production, the
    #   keys should be OEM-generated and should never be present in source code or a non-secure environment except for
    #   the L3 key which must be provided in the clear as the third return value. Ideally the L1 and L2 keys should be
    #   secured by an HSM. This example is only intended to demonstrate how to compute the wrapped L2 and wrapped L3
    #   data.
    l1 = b'l&\xd6(^\xf3"\xef\x9e\xe5\x81\x04\xb54\x96\xcb'
    l2 = urandom(16)
    l3 = urandom(16)

    root_key_type_map = {
        0: "RTL QTI",
        1: "OTP OEM",
        2: "OTP QTI"
    }
    print(f"L1 should be an {root_key_type_map[root_key_type]} key.")

    # --plugin-encrypter-args can be used to pass custom input values to a plugin encrypter.
    if plugin_encrypter_args:
        print(f"Value provided via --plugin-encrypter-args: {plugin_encrypter_args}")

    # Create Wrapped L2 B0.
    l2_b0_flags = 0x79
    l2_b0_nonce = urandom(13)
    l2_b0_q = 16
    l2_b0 = (pack("<B13s", l2_b0_flags, l2_b0_nonce) +
             pack(">H", l2_b0_q))  # This is big endian.

    # Create Wrapped L2 Associate Data.
    l2_associated_data_length = pack(">H", 32)  # This is big endian.
    l2_associated_reserved_0 = 0
    l2_associated_reserved_1 = 0
    l2_associated_major_version = 1
    l2_associated_minor_version = 0
    l2_associated_key_ladder_length = 3
    l2_associated_reserved_2 = 0
    security_profile_software_id = int(security_profile.image.sw_id, 0)
    # Determine the Software ID by extracting it in the following order:
    #   1) v6 Hash Table Segment OEM Metadata.
    #   2) v6 Hash Table Segment QTI Metadata.
    #   3) v7 Hash Table Segment Common Metadata.
    #   4) Security Profile (v3 and v5 Hash Table Segments only contain the Software ID within the Attestation
    #      certificate which is not available to the plugin encrypter).
    software_id = getattr(image_inspectable_data, "oem_metadata_software_id",
                          getattr(image_inspectable_data, "qti_metadata_software_id",
                                  getattr(image_inspectable_data, "common_metadata_software_id",
                                          security_profile_software_id)))
    l2_associated_software_id_bitmap = 1 << software_id
    l2_associated_reserved_3 = b""
    l2_associated_data = (l2_associated_data_length +
                          pack("<BBBBBBI20s", l2_associated_reserved_0, l2_associated_reserved_1,
                               l2_associated_major_version, l2_associated_minor_version,
                               l2_associated_key_ladder_length, l2_associated_reserved_2,
                               l2_associated_software_id_bitmap, l2_associated_reserved_3))

    # Encrypt L2 Key via AES CCM.
    wrapped_l2_key_payload_and_mac = encrypt(l2, l1, l2_b0_nonce, l2_associated_data)

    # Extract Wrapped L2 Key Payload.
    l2_key_payload = wrapped_l2_key_payload_and_mac[:16]

    # Extract Wrapped L2 MAC.
    l2_mac = wrapped_l2_key_payload_and_mac[16:]

    # Create Wrapped L2.
    wrapped_l2 = l2_b0 + l2_associated_data + l2_key_payload + l2_mac

    # Create Wrapped L3 B0.
    l3_b0_flags = 0x79
    l3_b0_nonce = urandom(13)
    l3_b0_q = 16
    l3_b0 = (pack("<B13s", l3_b0_flags, l3_b0_nonce) +
             pack(">H", l3_b0_q))   # This is big endian.

    # Create Wrapped L3 Associate Data.
    l3_associated_data_length = pack(">H", 32)  # This is big endian.
    l3_associated_data_reserved_0 = 0
    l3_associated_data_reserved_1 = 0
    l3_associated_data_image_encryption_algorithm = 1  # Corresponds to AES.
    l3_associated_data_image_encryption_mode = 1  # Corresponds to CBC CTS.
    l3_associated_data_reserved_2 = 0
    l3_associated_data_reserved_3 = 0
    l3_associated_data_reserved_4 = 0
    # Mark all segments as encrypted if no segment indices are provided.
    l3_associated_data_all_segments_encrypted = not encrypted_segment_indices
    # Ignored when all segments are marked for encryption.
    l3_associated_data_number_of_encrypted_segments = len(encrypted_segment_indices)
    l3_associated_data_reserved_5 = 0
    l3_associated_data_reserved_6 = 0
    l3_associated_data_segment_bitmap_0 = 0  # Ignored when all segments are marked for encryption.
    l3_associated_data_segment_bitmap_1 = 0  # Ignored when all segments are marked for encryption.
    for encrypted_segment_index in encrypted_segment_indices:
        if encrypted_segment_index < 64:
            l3_associated_data_segment_bitmap_0 |= 1 << encrypted_segment_index
        elif encrypted_segment_index < 128:
            l3_associated_data_segment_bitmap_1 |= 1 << encrypted_segment_index - 64
    l3_associated_data = (l3_associated_data_length +
                          pack("<BBBBBBI?BBBQQ", l3_associated_data_reserved_0, l3_associated_data_reserved_1,
                               l3_associated_data_image_encryption_algorithm,
                               l3_associated_data_image_encryption_mode, l3_associated_data_reserved_2,
                               l3_associated_data_reserved_3, l3_associated_data_reserved_4,
                               l3_associated_data_all_segments_encrypted,
                               l3_associated_data_number_of_encrypted_segments, l3_associated_data_reserved_5,
                               l3_associated_data_reserved_6, l3_associated_data_segment_bitmap_0,
                               l3_associated_data_segment_bitmap_1))

    # Encrypt L3 Key via AES CCM.
    wrapped_l3_key_payload_and_mac = encrypt(l3, l2, l3_b0_nonce, l3_associated_data)

    # Extract Wrapped L3 Key Payload.
    l3_key_payload = wrapped_l3_key_payload_and_mac[:16]

    # Extract Wrapped L3 MAC.
    l3_mac = wrapped_l3_key_payload_and_mac[16:]

    # Create Wrapped L3.
    wrapped_l3 = l3_b0 + l3_associated_data + l3_key_payload + l3_mac

    # Return Wrapped L2, Wrapped L3, and clear L3.
    return wrapped_l2, wrapped_l3, l3


def get_encryption_spec_versions() -> Tuple[int, int, int]:
    """ This example is specific to the UIE 1.0 L2 1.0 specification. """
    return 1, 1, 0
