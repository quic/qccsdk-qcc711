#!/usr/bin/env python
"""!
@brief Parse the QCC710 Update Package and verifies the integrity of the involved binaries.

@section
Copyright (c) 2022 Qualcomm Technologies, Inc.
All rights reserved.
Confidential and Proprietary - Qualcomm Technologies, Inc.
"""
import argparse
import os
import struct

from beautifultable import BeautifulTable
from colorama import init, deinit
from dataclasses import dataclass
from datetime import datetime
from hashlib import sha512
from termcolor import colored

# Maximum number of supported image descriptors
MAX_SUPPORTED_IMAGE_DESCRIPTORS = 7
# Size of the TLV header.
TLV_HEADER_SIZE = 4
# Identifier for Manifest Data
TLV_MANIFEST_ID = "0x0000"
# Identifier for Update Data
TLV_UPDATE_ID = "0x0001"
# Identifier for Image Descriptor
TLV_TYPE_IMAGE_DESCRIPTOR = "0x8291"
# Identifier for Image Descriptor Software Component Id
TLV_TYPE_IMAGE_DESC_SOFTWARE_COMPONENT_ID = "0x8351"
# Identifier of Image Descriptor Algorithm Hash
TLV_TYPE_IMAGE_DESC_IMAGE_ALG_HASH = "0x8384"
# Identifier of Image Descriptor Address Size
TLV_TYPE_IMAGE_DESC_ADDRESS_SIZE = "0x8386"
# Identifier for Image Id
TLV_TYPE_SOFTWARE_COMPONENT_ID = "0x8422"
# Identifier for Image Hash
TLV_TYPE_IMAGE_HASH = "0x8441"
# Identifier for Image Address
TLV_TYPE_IMAGE_ADDRESS = "0x8448"
# Identifier for Image Size
TLV_TYPE_IMAGE_SIZE = "0x8449"
# Identifier for Boot Manifest
TLV_TYPE_BOOT_MANIFEST = "0x8600"
# Identifier for Boot Manifest Hash Table
TLV_TYPE_BOOT_MANIFEST_HASH_TABLE = "0x8601"
# Identifier for Boot Manifest Hash Table Entry
TLV_TYPE_BOOT_MANIFEST_HASH_TABLE_ENTRY = "0x8602"
# Identifier for Image Descriptor Array
TLV_TYPE_IMAGE_DESCRIPTOR_ARRAY = "0x8603"

# APSS Image Id
SOFTWARE_COMPONENT_ID_APSS = "0x00000032"
#  RoT Patch Image Id
SOFTWARE_COMPONENT_ID_ROT = "0x00000035"
# BT Patch Image Id
SOFTWARE_COMPONENT_ID_BTSS = "0x00000038"
# License Image Id
SOFTWARE_COMPONENT_ID_LICENSE = "0x00000048"
# BT Config Image Id
SOFTWARE_COMPONENT_ID_BTCFG = "0x00000049"
# QTI Boot Manifest Image Id
SOFTWARE_COMPONENT_ID_QTI_BOOT_MANIFEST = "0x0000004E"
# OEM Boot Manifest Image Id
SOFTWARE_COMPONENT_ID_OEM_BOOT_MANIFEST = "0x0000004F"

# Validation status for Image whose hashes matches
VALIDATION_STATUS_IMAGE_VALID = "Image Valid"
# Validation status for Image whose hashes do not match
VALIDATION_STATUS_IMAGE_INVALID = "Image Invalid"
# Validation status for Image which is not present in update package
VALIDATION_STATUS_IMAGE_NOT_UPDATED = "Image Not Updated"
# Validation status for Image which is not present in expected Manifest
VALIDATION_STATUS_IMAGE_NOT_PRESENT = "Image Missing"


@dataclass
class _TlvBuffer:
    """!
    Consists of bytes and buffer length which creates the TLV Buffer.
    """
    data: bytes = None
    length: int = None


@dataclass
class _ImageDescriptor:
    """!
    Consists of TLV Buffer bytes, length of TLV Buffer, Image's Id, Image's Hash bytes, Image's Address
    and Image's Size which creates the Image Descriptor.
    """
    tlv_buffer: bytes = None
    tlv_length: int = None
    image_id: int = None
    image_hash: bytes = None
    address: int = None
    size: int = None


@dataclass
class _Manifest:
    """!
    Consists of Boot Manifest bytes, length of Boot Manifest bytes, Image Descriptors bytes, length of
    Image Descriptors bytes, number of Image Descriptors and the list of Image Descriptors which creates
    the Manifest.
    """
    boot_manifest: bytes = None
    boot_manifest_length: int = None
    image_descriptors: bytes = None
    image_descriptors_length: int = None
    image_descriptor_count: int = None
    image_descriptor_list: list = None


def _check_update_package_params(update_package_file: str):
    """!
    Validates the input received for parsing and validating the QCC710 Update package

    @param update_package_file: string containing absolute path of the update package.

    @exception ValueError: if any of the argument is None.
    @exception TypeError: if the data type mismatches for any of the input arguments.
    """
    if update_package_file is None:
        raise ValueError("Update Package Filename cannot be None.")
    elif not isinstance(update_package_file, str):
        raise TypeError(
            "Update Package Filename must be str, not {}.".format(
                type(update_package_file).__name__))
    else:
        NotImplemented


def _get_tlv(tlv_type: int, first_entry: bool, input_tlv: _TlvBuffer):
    """!
    Parse the provided TLV Buffer to retrieve the TLV for provided Tag value

    @param tlv_type: int containing the Tag for which TLV is required.
    @param first_entry: bool signifying whether the TLV to be retrieved must be the first TLV in the input TLV buffer
    @param input_tlv: @ref _TlvBuffer <Class Object> containing the input TLV Buffer.

    @exception ValueError: if the input TLV Buffer is invalid or TLV for provided Tag do not exist.

    @retval _TlvBuffer <Class Object>: the TLV Buffer for provided tag
    """
    buffer = input_tlv.data
    tlv_length = input_tlv.length
    output_tlv = _TlvBuffer()
    entry_found = False

    while tlv_length > TLV_HEADER_SIZE:
        read_type, read_length = struct.unpack('<HH', buffer[:4])
        tlv_length = tlv_length - TLV_HEADER_SIZE
        buffer = buffer[TLV_HEADER_SIZE:]
        if read_length <= tlv_length:
            if read_type == tlv_type:
                # Entry Found
                output_tlv.data = buffer
                output_tlv.length = read_length
                entry_found = True
                break
            else:
                # Round the length up to the four - byte boundary and move to the next TLV.
                read_length = (read_length + 3) & ~3
                buffer = buffer[read_length:]
                tlv_length = tlv_length - read_length
        else:
            # Invalid TLV length.
            raise ValueError("Length of TLV data is invalid.")

        if first_entry:
            break

    if not entry_found:
        # Entry Not Found
        raise ValueError("TLV for provided type not found.")

    return output_tlv


def _parse_boot_manifest(tlv_data: _TlvBuffer):
    """!
    Parse the provided TLV Buffer to create the Boot Manifest

    @param tlv_data: @ref _TlvBuffer <Class Object> containing the input TLV Buffer.

    @exception ValueError: if the input TLV Buffer is invalid.

    @retval _Manifest <Class Object>: the Boot Manifest Class Object
    """
    boot_manifest = _Manifest()

    boot_manifest.boot_manifest = tlv_data.data
    # Verify the boot manifest is the first thing in the buffer.
    boot_manifest_tlv = _get_tlv(int(TLV_TYPE_BOOT_MANIFEST, 16), True, tlv_data)
    boot_manifest.boot_manifest_length = boot_manifest_tlv.length + TLV_HEADER_SIZE

    # Parse the hash table for the expected image IDs.
    # Get the hash table TLV data.
    boot_manifest_hash_table_tlv = _get_tlv(int(TLV_TYPE_BOOT_MANIFEST_HASH_TABLE, 16), False, boot_manifest_tlv)
    # Get the list of descriptors
    boot_manifest.image_descriptor_count = 0
    index = 0
    while index < MAX_SUPPORTED_IMAGE_DESCRIPTORS and boot_manifest_hash_table_tlv.length >= TLV_HEADER_SIZE:
        # Verify the hash table entry is the first thing in the buffer.
        entry_tlv = _get_tlv(int(TLV_TYPE_BOOT_MANIFEST_HASH_TABLE_ENTRY, 16), True, boot_manifest_hash_table_tlv)
        # Read the Image id
        id_tlv = _get_tlv(int(TLV_TYPE_SOFTWARE_COMPONENT_ID, 16), False, entry_tlv)
        if id_tlv.length == TLV_HEADER_SIZE:
            if boot_manifest.image_descriptor_list is None:
                boot_manifest.image_descriptor_list = []
            image_descriptor = _ImageDescriptor()
            image_descriptor.image_id = int.from_bytes(id_tlv.data[:id_tlv.length], "little")
            boot_manifest.image_descriptor_list.append(image_descriptor)
            boot_manifest.image_descriptor_count += 1
            boot_manifest_hash_table_tlv.length -= (entry_tlv.length + TLV_HEADER_SIZE)
            boot_manifest_hash_table_tlv.data = boot_manifest_hash_table_tlv.data[(entry_tlv.length + TLV_HEADER_SIZE):]
        else:
            # Invalid TLV length.
            raise ValueError("Length of Boot Manifest Hash Table Entry TLV data is invalid.")
        index += 1

    # Make sure the entire length of the hash table was consumed.
    if boot_manifest_hash_table_tlv.length != 0:
        raise ValueError("Length of Boot Manifest Hash Table TLV data is invalid.")

    return boot_manifest


def _parse_image_hash_addr_size(image_descriptor: _ImageDescriptor):
    """!
    Parse the provided Image Descriptor to retrieve Image's Hash, address and size

    @param image_descriptor: @ref _ImageDescriptor <Class Object> containing the input Image Descriptor.

    @exception ValueError: if the input Image Descriptor is invalid.

    @retval bytes: containing hash of the image
    @retval int: containing address of the image
    @retval int: containing size of the image
    """
    hash_tlv_data = _TlvBuffer()
    tlv_data = _TlvBuffer()

    hash_tlv_data.data = image_descriptor.tlv_buffer[TLV_HEADER_SIZE:]
    hash_tlv_data.length = image_descriptor.tlv_length + TLV_HEADER_SIZE

    tlv_data.data = image_descriptor.tlv_buffer[TLV_HEADER_SIZE:]
    tlv_data.length = image_descriptor.tlv_length + TLV_HEADER_SIZE

    # Read the Image Hash
    hash_tlv_data = _get_tlv(int(TLV_TYPE_IMAGE_DESC_IMAGE_ALG_HASH, 16), False, hash_tlv_data)
    entry_tlv = _get_tlv(int(TLV_TYPE_IMAGE_HASH, 16), False, hash_tlv_data)
    if entry_tlv.length == 64:
        image_hash = entry_tlv.data[:64]
    else:
        raise ValueError("Invalid length of Image Hash in Image Descriptor Array.")

    # Read the size and address.
    tlv_data = _get_tlv(int(TLV_TYPE_IMAGE_DESC_ADDRESS_SIZE, 16), False, tlv_data)
    entry_tlv = _get_tlv(int(TLV_TYPE_IMAGE_ADDRESS, 16), False, tlv_data)
    if entry_tlv.length == 8:
        if int.from_bytes(entry_tlv.data[4:8], "big") == 0:
            address = int.from_bytes(entry_tlv.data[:4], "little")
        else:
            raise ValueError("Invalid location of Image in Image Descriptor Array.")
    else:
        raise ValueError("Invalid length of Image Address in Image Descriptor Array.")

    entry_tlv = _get_tlv(int(TLV_TYPE_IMAGE_SIZE, 16), False, tlv_data)
    if entry_tlv.length == 8:
        if int.from_bytes(entry_tlv.data[4:8], "big") == 0:
            size = int.from_bytes(entry_tlv.data[:4], "little")
        else:
            raise ValueError("Invalid value of Image size in Image Descriptor Array.")
    else:
        raise ValueError("Invalid length of Image Size in Image Descriptor Array.")

    return image_hash, address, size


def _parse_image_descriptors(tlv_data: _TlvBuffer, boot_manifest: _Manifest):
    """!
    Parse the provided TLV Buffer to retrieve the Image Descriptors and populate provided
    Boot Manifest with it

    @param tlv_data: @ref _TlvBuffer <Class Object> containing the Image Descriptor.
    @param boot_manifest: @ref _Manifest <Class Object> containing the Boot Manifest to which retrieved
    Image Descriptor needs to be added

    @exception ValueError: if the input TLV Buffer containing Image Descriptor is Invalid.

    @retval _Manifest <Class Object>: the Boot Manifest Class Object with retrieved Image Descriptors
    """
    boot_manifest.image_descriptors = tlv_data.data
    # Verify this is an image descriptor array.
    image_descriptor_array_tlv = _get_tlv(int(TLV_TYPE_IMAGE_DESCRIPTOR_ARRAY, 16), True, tlv_data)
    boot_manifest.image_descriptors_length = image_descriptor_array_tlv.length + TLV_HEADER_SIZE

    if (image_descriptor_array_tlv.length + TLV_HEADER_SIZE) == tlv_data.length:
        while image_descriptor_array_tlv.length >= TLV_HEADER_SIZE:
            # Verify this is an image descriptor entry.
            entry_tlv = _get_tlv(int(TLV_TYPE_IMAGE_DESCRIPTOR, 16), True, image_descriptor_array_tlv)
            # Read the image ID.
            id_tlv = _get_tlv(int(TLV_TYPE_IMAGE_DESC_SOFTWARE_COMPONENT_ID, 16), False, entry_tlv)
            if id_tlv.length == TLV_HEADER_SIZE:
                image_id = int.from_bytes(id_tlv.data[:id_tlv.length], "little")
                # Find an entry for the descriptor.
                index = 0
                while index < boot_manifest.image_descriptor_count:
                    if boot_manifest.image_descriptor_list[index].image_id == image_id:
                        if boot_manifest.image_descriptor_list[index].tlv_buffer is None:
                            boot_manifest.image_descriptor_list[index].tlv_buffer = image_descriptor_array_tlv.data
                            boot_manifest.image_descriptor_list[index].tlv_length = entry_tlv.length + TLV_HEADER_SIZE
                            boot_manifest.image_descriptor_list[index].image_hash, \
                            boot_manifest.image_descriptor_list[index].address, \
                            boot_manifest.image_descriptor_list[index].size = \
                                _parse_image_hash_addr_size(boot_manifest.image_descriptor_list[index])
                        else:
                            # Duplicate entry of Image
                            raise ValueError("Image already exists in Image Descriptor Array.")
                        break
                    index += 1

                if index == boot_manifest.image_descriptor_count:
                    # Image Entry not Found
                    raise ValueError("Image doesn't exists in Image Descriptor Array.")

                image_descriptor_array_tlv.length -= (entry_tlv.length + TLV_HEADER_SIZE)
                image_descriptor_array_tlv.data = image_descriptor_array_tlv.data[(entry_tlv.length + TLV_HEADER_SIZE):]
            else:
                # Invalid TLV length.
                raise ValueError("Length of Image Descriptor Array Entry Image TLV data is invalid.")

        if image_descriptor_array_tlv.length == 0:
            # Make sure all image descriptors were accounted for.
            index = 0
            while index < boot_manifest.image_descriptor_count:
                if boot_manifest.image_descriptor_list[index].tlv_buffer is None:
                    # Descriptor is missing from Image Descriptor Array
                    raise ValueError("Descriptor missing in Image Descriptor Array.")
                index += 1
        else:
            # Entire buffer wasn't consumed.
            raise ValueError("Length of Image Descriptor Array Entry Image TLV data is invalid.")
    else:
        raise ValueError("Length of Image Descriptor Array TLV data is invalid.")

    return boot_manifest


def _pad_len(image_size: int):
    """!
    Returns the number of bytes required for padding to make image size a multiple of 4 i.e. word size

    @param image_size: int containing the size of the image.

    @retval int: number of bytes to pad
    """
    return (4 - (image_size % 4)) % 4


def _parse_update_package(update_data: bytes):
    """!
    Parse the provided bytes of QCC710 Update Package

    @param update_data: bytes containing the QCC710 Update Package.

    @exception ValueError: if the input bytes containing QCC710 Update Package is invalid.

    @retval dictionary: it contains hash and binary of each image present in update package
    @retval dictionary: it contains hash of each image present in update package's QTI Manifest
    @retval dictionary: it contains hash of each image present in update package's OEM Manifest
    """
    update_package_image_map = {}
    qti_manifest_image_map = {}
    oem_manifest_image_map = {}

    # Create the TLV data type from the read bytes
    input_tlv = _TlvBuffer(update_data, len(update_data))

    # Read the first tag which should be the update id
    output_tlv = _get_tlv(int(TLV_UPDATE_ID, 16), True, input_tlv)

    # Parse the Boot Manifest Hash Table
    boot_manifest = _parse_boot_manifest(output_tlv)

    # Proceed with Parsing of Image Descriptors
    image_descriptor_tlv = _TlvBuffer()
    image_descriptor_tlv.length = output_tlv.length - boot_manifest.boot_manifest_length
    image_descriptor_tlv.data = output_tlv.data[boot_manifest.boot_manifest_length:]

    # Parse the Image Descriptor Array
    boot_manifest = _parse_image_descriptors(image_descriptor_tlv, boot_manifest)

    # Parse the Image Binaries appended at the end of update package to get QTI Manifest and OEM Manifest
    # along with creation of map to store Hash of Images present in the update package
    update_data_binaries = update_data[(boot_manifest.boot_manifest_length + boot_manifest.image_descriptors_length +
                                        TLV_HEADER_SIZE):]
    qti_manifest_bytes = None
    oem_manifest_bytes = None
    index = 0
    while index < boot_manifest.image_descriptor_count:
        image_descriptor_entry = boot_manifest.image_descriptor_list[index]
        image_binary = update_data_binaries[:image_descriptor_entry.size]
        update_package_image_map[image_descriptor_entry.image_id] = [image_descriptor_entry.image_hash, image_binary]
        if image_descriptor_entry.image_id == int(SOFTWARE_COMPONENT_ID_QTI_BOOT_MANIFEST, 16):
            qti_manifest_bytes = image_binary
        if image_descriptor_entry.image_id == int(SOFTWARE_COMPONENT_ID_OEM_BOOT_MANIFEST, 16):
            oem_manifest_bytes = image_binary
        # Update the master data binary to exclude the read binary
        update_data_binaries = update_data_binaries[image_descriptor_entry.size +
                                                    _pad_len(image_descriptor_entry.size):]
        index += 1

    # Validate that the remaining length of read binaries is zero to make sure all the binaries have been read correctly
    if len(update_data_binaries) > 0:
        raise ValueError("Error while reading binaries from update package.")

    if qti_manifest_bytes is not None and len(qti_manifest_bytes) > 0:
        # Create the TLV data type for QTI Manifest
        qti_manifest_binary_tlv = _TlvBuffer(qti_manifest_bytes, len(qti_manifest_bytes))

        # Read the first tag which should be the manifest id
        qti_manifest_tlv = _get_tlv(int(TLV_MANIFEST_ID, 16), True, qti_manifest_binary_tlv)

        # Parse the QTI Manifest Boot Manifest Hash Table
        qti_manifest_boot_manifest = _parse_boot_manifest(qti_manifest_tlv)

        # Proceed with Parsing of QTI Manifest Image Descriptors
        qti_manifest_image_descriptor_tlv = _TlvBuffer()
        qti_manifest_image_descriptor_tlv.length = qti_manifest_tlv.length - \
                                                   qti_manifest_boot_manifest.boot_manifest_length
        qti_manifest_image_descriptor_tlv.data = qti_manifest_tlv.data[
                                                 qti_manifest_boot_manifest.boot_manifest_length:]

        # Parse the QTI Manifest Image Descriptor Array
        qti_manifest_boot_manifest = _parse_image_descriptors(qti_manifest_image_descriptor_tlv,
                                                              qti_manifest_boot_manifest)

        # Create the map to store Hash of Images present in the QTI Manifest
        index = 0
        while index < qti_manifest_boot_manifest.image_descriptor_count:
            image_descriptor_entry = qti_manifest_boot_manifest.image_descriptor_list[index]
            qti_manifest_image_map[image_descriptor_entry.image_id] = image_descriptor_entry.image_hash
            index += 1

    if oem_manifest_bytes is not None and len(oem_manifest_bytes) > 0:
        # Create the TLV data type for QTI Manifest
        oem_manifest_binary_tlv = _TlvBuffer(oem_manifest_bytes, len(oem_manifest_bytes))

        # Read the first tag which should be the manifest id
        oem_manifest_tlv = _get_tlv(int(TLV_MANIFEST_ID, 16), True, oem_manifest_binary_tlv)

        # Parse the OEM Manifest Boot Manifest Hash Table
        oem_manifest_boot_manifest = _parse_boot_manifest(oem_manifest_tlv)

        # Proceed with Parsing of OEM Manifest Image Descriptors
        oem_manifest_image_descriptor_tlv = _TlvBuffer()
        oem_manifest_image_descriptor_tlv.length = oem_manifest_tlv.length - \
                                                   oem_manifest_boot_manifest.boot_manifest_length
        oem_manifest_image_descriptor_tlv.data = oem_manifest_tlv.data[
                                                 oem_manifest_boot_manifest.boot_manifest_length:]

        # Parse the OEM Manifest Image Descriptor Array
        oem_manifest_boot_manifest = _parse_image_descriptors(oem_manifest_image_descriptor_tlv,
                                                              oem_manifest_boot_manifest)

        # Create the map to store Hash of Images present in the QTI Manifest
        index = 0
        while index < oem_manifest_boot_manifest.image_descriptor_count:
            image_descriptor_entry = oem_manifest_boot_manifest.image_descriptor_list[index]
            oem_manifest_image_map[image_descriptor_entry.image_id] = image_descriptor_entry.image_hash
            index += 1

    return update_package_image_map, qti_manifest_image_map, oem_manifest_image_map


def _get_image_name_from_id(image_id: int):
    """!
    Retrieve the Image name based on provided Image Id

    @param image_id: image_id the Image Id.

    @retval string: the name of the Image
    """
    switcher = {
        int(SOFTWARE_COMPONENT_ID_APSS, 16): "APSS",
        int(SOFTWARE_COMPONENT_ID_ROT, 16): "RoT Patch",
        int(SOFTWARE_COMPONENT_ID_BTSS, 16): "BTSS Patch",
        int(SOFTWARE_COMPONENT_ID_LICENSE, 16): "License",
        int(SOFTWARE_COMPONENT_ID_BTCFG, 16): "BT Config",
        int(SOFTWARE_COMPONENT_ID_QTI_BOOT_MANIFEST, 16): "QTI Manifest",
        int(SOFTWARE_COMPONENT_ID_OEM_BOOT_MANIFEST, 16): "OEM Manifest",
    }
    return switcher.get(image_id, "Invalid Image Id")


def _prepare_printable_table(validation_map: dict):
    """!
    Prepare the BeautifulTable instance to be printed on console.

    @param validation_map: dict containing the validation results of various images present in QCC710 Update package.

    @retval BeautifulTable <Class Object>: the BeautifulTable instance to be printed on console
    @retval string: containing the message regarding license presence in one manifest only
    """
    print_table = BeautifulTable(maxwidth=150)
    print_table.set_style(BeautifulTable.STYLE_GRID)
    print_table.columns.header = ["Available in Update Package", "Available in QTI Manifest",
                                  "Available in OEM Manifest", "Validation Message"]
    index = 0
    license_info_message = ""
    for image_id in validation_map.keys():
        validation_msgs_list = validation_map.get(image_id)

        if image_id == int(SOFTWARE_COMPONENT_ID_LICENSE, 16) \
                and validation_msgs_list[3] == VALIDATION_STATUS_IMAGE_VALID \
                and ((validation_msgs_list[1] == "Yes" and validation_msgs_list[2] == 'No')
                     or (validation_msgs_list[1] == "No" and validation_msgs_list[2] == 'Yes')):
            license_info_message += "Note : "
            license_info_message += colored("License is present in only one manifest. Make sure license on chip, if "
                                            "present, is same as the one used in update package", 'yellow')

        if validation_msgs_list[1] == "Not Applicable":
            validation_msgs_list[1] = colored(validation_msgs_list[1], 'blue')
        if validation_msgs_list[1] == "Manifest Not Available":
            validation_msgs_list[1] = colored(validation_msgs_list[1], 'cyan')
        if validation_msgs_list[2] == "Not Applicable":
            validation_msgs_list[2] = colored(validation_msgs_list[2], 'blue')
        if validation_msgs_list[2] == "Manifest Not Available":
            validation_msgs_list[2] = colored(validation_msgs_list[2], 'cyan')

        if validation_msgs_list[3] == VALIDATION_STATUS_IMAGE_VALID:
            validation_msgs_list[3] = colored(validation_msgs_list[3], 'green')
        elif validation_msgs_list[3] == VALIDATION_STATUS_IMAGE_NOT_UPDATED:
            validation_msgs_list[3] = colored(validation_msgs_list[3], 'cyan')
        else:
            validation_msgs_list[3] = colored(validation_msgs_list[3], 'red')

        print_table.rows.insert(index, validation_msgs_list, header=_get_image_name_from_id(image_id))
        index += 1

    return print_table, license_info_message


def parse_and_verify_update_package(update_package_file: str):
    """
    Parse the Update package present at the provided absolute path and verifies if the images are
    valid or not.

    The QCC710 Update Package along with Images/Binaries also contains the hashes of the images.The QTI Manifest
    and OEM Manifest also contains the hashes of the images which were used to create them. The API verifies that
    hashes of the images present in update package matches with the one present in respective manifest and the
    update package.

    The dictionary returned by this API contains information about all the 7 binaries, which can be in update package,
    in the sequence ['Available in Update Package', 'Available in QTI Manifest', 'Available in OEM Manifest',
    'Validation Message'] for each Image. In case any Image is not present then it simply states that Image is not
    updated

    @param update_package_file: str containing absolute path of the update package.

    @exception ValueError: if the update package binary is invalid.
    @exception TypeError: if the data type mismatches for any of the input arguments.

    @retval boolean: True when validation is successful else False.
    @retval dictionary : containing the validation message for each image.
    """
    # Check parameters
    _check_update_package_params(update_package_file)

    # Read the binary data of update package
    with open(update_package_file, 'rb') as update_package_binary:
        update_data = update_package_binary.read()

    # Validate the length of read binary data
    if len(update_data) < TLV_HEADER_SIZE:
        raise ValueError("Invalid length of update package binary.")

    # Parse the TLVs present in input file to get various binaries and Hashes
    update_package_image_map, qti_manifest_image_map, oem_manifest_image_map = _parse_update_package(update_data)

    # Validate that parsing of update package went fine
    if len(update_package_image_map.keys()) == 0 or (len(qti_manifest_image_map.keys()) == 0 and
                                                     len(oem_manifest_image_map.keys()) == 0):
        raise ValueError("Invalid update package")

    image_validation_status = {}
    # Proceed with validation of Image Binaries by comparing them with hashes present
    # Image Descriptor and Manifests along with the calculated hash
    for image_id in update_package_image_map.keys():
        image_hash, image_bytes = update_package_image_map.get(image_id)
        hash_obj = sha512()
        hash_obj.update(image_bytes)
        calculated_image_hash = hash_obj.digest()
        # BTSS Patch and RoT Patch if present should be validated against QTI Manifest
        if image_id == int(SOFTWARE_COMPONENT_ID_BTSS, 16) or image_id == int(SOFTWARE_COMPONENT_ID_ROT, 16):
            manifest_image_hash = qti_manifest_image_map.get(image_id)
            if manifest_image_hash is None:
                image_validation_status[image_id] = VALIDATION_STATUS_IMAGE_NOT_PRESENT
            if image_hash == calculated_image_hash and image_hash == manifest_image_hash:
                image_validation_status[image_id] = VALIDATION_STATUS_IMAGE_VALID
            else:
                image_validation_status[image_id] = VALIDATION_STATUS_IMAGE_INVALID
        # BT Config and Apss if present should be validated against QEM Manifest
        elif image_id == int(SOFTWARE_COMPONENT_ID_BTCFG, 16) or image_id == int(SOFTWARE_COMPONENT_ID_APSS, 16):
            manifest_image_hash = oem_manifest_image_map.get(image_id)
            if manifest_image_hash is None:
                image_validation_status[image_id] = VALIDATION_STATUS_IMAGE_NOT_PRESENT
            if image_hash == calculated_image_hash and image_hash == manifest_image_hash:
                image_validation_status[image_id] = VALIDATION_STATUS_IMAGE_VALID
            else:
                image_validation_status[image_id] = VALIDATION_STATUS_IMAGE_INVALID
        # QTI Manifest and OEM Manifest should be validated only against the Update Package Hash
        elif image_id == int(SOFTWARE_COMPONENT_ID_QTI_BOOT_MANIFEST, 16) or \
                image_id == int(SOFTWARE_COMPONENT_ID_OEM_BOOT_MANIFEST, 16):
            if image_hash == calculated_image_hash:
                image_validation_status[image_id] = VALIDATION_STATUS_IMAGE_VALID
            else:
                image_validation_status[image_id] = VALIDATION_STATUS_IMAGE_INVALID
        # License can be in both the manifest and if present in both then both should be same
        elif image_id == int(SOFTWARE_COMPONENT_ID_LICENSE, 16):
            qti_manifest_image_hash = qti_manifest_image_map.get(image_id)
            oem_manifest_image_hash = oem_manifest_image_map.get(image_id)

            if qti_manifest_image_hash is not None and oem_manifest_image_hash is not None:
                if qti_manifest_image_hash != oem_manifest_image_hash:
                    image_validation_status[image_id] = VALIDATION_STATUS_IMAGE_INVALID
                else:
                    if image_hash == calculated_image_hash and image_hash == qti_manifest_image_hash:
                        image_validation_status[image_id] = VALIDATION_STATUS_IMAGE_VALID
                    else:
                        image_validation_status[image_id] = VALIDATION_STATUS_IMAGE_INVALID
            elif qti_manifest_image_hash is not None and oem_manifest_image_hash is None:
                if image_hash == calculated_image_hash and image_hash == qti_manifest_image_hash:
                    image_validation_status[image_id] = VALIDATION_STATUS_IMAGE_VALID
                else:
                    image_validation_status[image_id] = VALIDATION_STATUS_IMAGE_INVALID
            elif qti_manifest_image_hash is None and oem_manifest_image_hash is not None:
                if image_hash == calculated_image_hash and image_hash == oem_manifest_image_hash:
                    image_validation_status[image_id] = VALIDATION_STATUS_IMAGE_VALID
                else:
                    image_validation_status[image_id] = VALIDATION_STATUS_IMAGE_INVALID
            elif qti_manifest_image_hash is None and oem_manifest_image_hash is None:
                image_validation_status[image_id] = VALIDATION_STATUS_IMAGE_NOT_PRESENT

    # Proceed with identifying whether Validation was success or not
    is_update_package_valid = True
    for image_id in image_validation_status.keys():
        if image_validation_status.get(image_id) != VALIDATION_STATUS_IMAGE_VALID:
            is_update_package_valid = False
            break

    # Proceed with creation of Map which will be used for print and logging
    # The Map will contain a list for each Image Id with info in the sequence
    # 'Available in Update Package', 'Available in QTI Manifest', 'Available in OEM Manifest', 'Validation Message'
    # Add all the images ids to the map
    validation_map = {int(SOFTWARE_COMPONENT_ID_BTCFG, 16): ["", "", "", ""],
                      int(SOFTWARE_COMPONENT_ID_BTSS, 16): ["", "", "", ""],
                      int(SOFTWARE_COMPONENT_ID_APSS, 16): ["", "", "", ""],
                      int(SOFTWARE_COMPONENT_ID_ROT, 16): ["", "", "", ""],
                      int(SOFTWARE_COMPONENT_ID_LICENSE, 16): ["", "", "", ""],
                      int(SOFTWARE_COMPONENT_ID_QTI_BOOT_MANIFEST, 16): ["", "", "", ""],
                      int(SOFTWARE_COMPONENT_ID_OEM_BOOT_MANIFEST, 16): ["", "", "", ""]}

    is_qti_manifest_present = True
    is_oem_manifest_present = True
    for image_id in validation_map.keys():
        if update_package_image_map.get(image_id) is None:
            validation_map.get(image_id)[0] = "No"
            validation_map.get(image_id)[3] = VALIDATION_STATUS_IMAGE_NOT_UPDATED
            if image_id == int(SOFTWARE_COMPONENT_ID_QTI_BOOT_MANIFEST, 16):
                is_qti_manifest_present = False
            if image_id == int(SOFTWARE_COMPONENT_ID_OEM_BOOT_MANIFEST, 16):
                is_oem_manifest_present = False
        else:
            validation_map.get(image_id)[0] = "Yes"
            validation_map.get(image_id)[3] = image_validation_status.get(image_id)

        # BTSS Patch and RoT Patch are expected to be present in QTI Manifest
        if image_id == int(SOFTWARE_COMPONENT_ID_BTSS, 16) or image_id == int(SOFTWARE_COMPONENT_ID_ROT, 16):
            if qti_manifest_image_map.get(image_id) is None:
                validation_map.get(image_id)[1] = "No"
            else:
                validation_map.get(image_id)[1] = "Yes"
            validation_map.get(image_id)[2] = "Not Applicable"
        # BT Config and Apss are expected to be present in QEM Manifest
        elif image_id == int(SOFTWARE_COMPONENT_ID_BTCFG, 16) or image_id == int(SOFTWARE_COMPONENT_ID_APSS, 16):
            validation_map.get(image_id)[1] = "Not Applicable"
            if oem_manifest_image_map.get(image_id) is None:
                validation_map.get(image_id)[2] = "No"
            else:
                validation_map.get(image_id)[2] = "Yes"
        # QTI Manifest and OEM Manifest are not expected in any Manifest
        elif image_id == int(SOFTWARE_COMPONENT_ID_QTI_BOOT_MANIFEST, 16) or \
                image_id == int(SOFTWARE_COMPONENT_ID_OEM_BOOT_MANIFEST, 16):
            validation_map.get(image_id)[1] = "Not Applicable"
            validation_map.get(image_id)[2] = "Not Applicable"
        # License can be in both the manifest
        elif image_id == int(SOFTWARE_COMPONENT_ID_LICENSE, 16):
            if qti_manifest_image_map.get(image_id) is None:
                validation_map.get(image_id)[1] = "No"
            else:
                validation_map.get(image_id)[1] = "Yes"

            if oem_manifest_image_map.get(image_id) is None:
                validation_map.get(image_id)[2] = "No"
            else:
                validation_map.get(image_id)[2] = "Yes"

    # Based on whether QTI Manifest or OEM Manifest is present update their respective columns
    for image_id in validation_map.keys():
        if not is_qti_manifest_present:
            if validation_map.get(image_id)[1] != "Not Applicable":
                validation_map.get(image_id)[1] = "Manifest Not Available"

        if not is_oem_manifest_present:
            if validation_map.get(image_id)[2] != "Not Applicable":
                validation_map.get(image_id)[2] = "Manifest Not Available"

    return is_update_package_valid, validation_map


def main():
    """!
    The function to be invoked when the script is executed.

    The function process the command line arguments and invoke the API to parse and validate the QCC710
    Update package. Post that it print the result on console. And if specified as an argument then it also
    logs the result in a file.
    """
    # Parse the command line arguments.
    parser = argparse.ArgumentParser(description='Parse the QCC710 Update Package and verifies the integrity of the '
                                                 'involved binaries.')
    parser.add_argument('-p', '--package', required=True, help='Input QCC710 Update Package.')
    parser.add_argument('--gen_log', action='store_true', default=False, help='Whether to log the validation output '
                                                                              'in a log file.')
    arguments = parser.parse_args()

    # Parse and Validate the QCC710 Update Package present at provided path
    is_valid, validation_map = parse_and_verify_update_package(arguments.package)

    # If mentioned, log the result in a file
    if arguments.gen_log:
        # Create the output log file
        # YY_mm_dd_H_M_S
        date_string = datetime.now().strftime("%Y_%m_%d_%H_%M_%S")
        output = os.path.splitext(arguments.package)[0] + '_' + date_string + '.log'
        # Write the log text in output log file
        with open(output, 'w') as file:
            file.write("/**\n")
            file.write("  * For each Binary, info is logged in following sequence:\n")
            file.write("  * 'Binary' : ['Available in Update Package', 'Available in QTI Manifest', "
                       "'Available in OEM Manifest', 'Validation Message']\n")
            file.write("  */\n\n")
            for image_id, info_list in validation_map.items():
                file.write(_get_image_name_from_id(image_id) + ":" + str(info_list) + "\n")
            file.write("\nIs Update package Valid : " + str(is_valid))

    # Prepare the termcolor table to be used for printing data on console
    print_table, license_info_message = _prepare_printable_table(validation_map)

    # Use Colorama to make Termcolor work on Windows too
    init()
    # Print the table on console
    print(print_table)
    # Get the overall image validation status
    overall_status = "Overall Status of Update Package : "
    if is_valid:
        overall_status += colored("Valid", 'green', attrs=['bold'])
    else:
        overall_status += colored("Invalid", 'red', attrs=['bold'])
    # Print the overall validation status
    print(overall_status)
    # Print if License is present in only one manifest
    if len(license_info_message) > 0:
        print(license_info_message)
    # Stop using Colorama before your program exits
    deinit()


if __name__ == "__main__":
    main()
