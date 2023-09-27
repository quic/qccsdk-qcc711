# ===============================================================================
# Copyright (c) 2020-2021 Qualcomm Technologies, Inc.
# All Rights Reserved.
# Confidential and Proprietary - Qualcomm Technologies, Inc.
# ===============================================================================
import argparse
from copy import copy
from hashlib import sha512
import json
import os
from pathlib import Path
import struct
import sys

# Mapping of command line names fpr images to the names used by the SignQCC710 class.
IMAGE_LIST = {
    'btcfg': 'BTSS_CFG',
    'btss': 'BTSS',
    'apss': 'APP_SS',
    'tme': 'TME_FW_SS',
    'lic': 'BTSS_LIC',
    'qti_man': 'QTI_BOOT_MANIFEST',
    'oem_man': 'OEM_BOOT_MANIFEST',
}

# Mapping of binary SWIDs to the names used by the SignQCC710 class.
SWIDS_TO_NAMES = {
    0x0032: 'apss',
    0x0035: 'tme',
    0x0038: 'btss',
    0x0048: 'lic',
    0x0049: 'btcfg',
}

class Image(object):
    """
    Class representing an Image Descriptor.
    """
    def __init__(self, name, filename, address, max_size, sec_ver, requires=None):
        """
        Initializes a Descriptor object.

        :param name:     Name of the image.
        :param filename: Filename of the image binary.
        :param address:  Start address of the image.
        :param max_size: Maximum valid size of the image.
        :param sec_ver:  Security version attribute for the image descriptor.
        :param requires: List of images this image requires.
        """
        self.name = name
        self.filename = filename
        self.address = address
        self.max_size = int(max_size)
        self.requires = requires[:] if requires is not None else list()
        self.sec_ver = sec_ver

        # Read the data.
        with open(filename, 'rb') as file:
            self.data = file.read()

        # Verify the image.
        if len(self.data) > self.max_size:
            raise Exception('{} exceeded max size: "{}"'.format(name, len(self.data)))

    def __eq__(self, other):
        """
        Compares a Descriptor object against either another descriptor or an
        image name.

        :param other: Name of the object or string to compare to.
        """
        if isinstance(other, Image):
            return self.name == other.name
        else:
            return self.name == other

    def data_len(self):
        """
        Determines the length of the image.

        :return: Length of the image in bytes.
        """
        return len(self.data)

    def pad_len(self):
        """
        Determines the number of bytes needed to pad the image to 4-byte
        alignment.

        :return: Bytes needed to pad the image to 4-byte alignment.
        """
        return (4 - (self.data_len() % 4)) % 4

    def padded_len(self):
        """
        Determines the length of the image padded to 4-byte alignment

        :return: Lenght of the image padded to 4-byte alignemnt in bytes.
        """
        return self.data_len() + self.pad_len()

    def write_json(self, out_path='.', prefix='ImageDescriptor_'):
        """
        Create the JSON file for the descriptor.

        :param out_path: Path for the JSON file.
        :param prefix:   prefix for the JSON file.

        :return: The filename of the JSON file. This will be a combination
                 of the out_path, prefix, and image name.
        """
        hash_obj = sha512()
        hash_obj.update(self.data)
        sha_hash = hash_obj.digest()

        try:
            # Python 2
            sha_hash = sha_hash.encode('hex')
        except AttributeError:
            # Python 3
            sha_hash = sha_hash.hex()

        # Form the image descriptor configuration data.
        descriptor = {
            'SecurityVersion': self.sec_ver,
            'SoftwareComponentIdentifier': self.name + '_SWID',
            'MeasurementRegisterTarget': 'NA',
            'HashValues': {
                'AlgorithmIdentifier': 'SHA_512',
                'HashArray': sha_hash,
            },
            'ImageAddressSize': {
                'Address': self.address,
                'Size': self.data_len(),
            },
        }

        # Write the descriptor to a file and add a reference to the object.
        filename = Path(out_path) / f'{prefix}{self.name}.json'
        filename.parent.mkdir(parents=True, exist_ok=True)
        with filename.open(mode='w') as file:
            json.dump(descriptor, file, indent=4)

        return filename


class SignQCC710(object):
    """
    Class to sign the QCC710 images
    """
    TEMP_PATH = 'target'
    MANIFEST_ID = 0x0000
    UPDATE_ID = 0x0001

    IMAGE_INFO = {
        'BTSS_CFG': {
            'start': 0x10200000,
            'size': 0x00000B00,
            'requires': ['OEM_BOOT_MANIFEST'],
        },
        'BTSS': {
            'start': 0x10200B00,
            'size': 0x0000F500,
            'requires': ['QTI_BOOT_MANIFEST'],
        },
        'APP_SS': {
            'start': 0x10210000,
            'size': 0x00068000,
            'requires': ['OEM_BOOT_MANIFEST'],
        },
        'TME_FW_SS': {
            'start': 0x10278000,
            'size': 0x00007000,
            'requires': ['QTI_BOOT_MANIFEST'],
        },
        'QTI_BOOT_MANIFEST': {
            'start': 0x1027F000,
            'size': 0x00000800,
            'requires': [],
        },
        'OEM_BOOT_MANIFEST': {
            'start': 0x1027F800,
            'size': 0x00000780,
            'requires': [],
        },
        'BTSS_LIC': {
            'start': 0x1027FF80,
            'size': 0x00000080,
            'requires': ['QTI_BOOT_MANIFEST', 'OEM_BOOT_MANIFEST'],
        },
    }

    def __init__(self, tool_path, bmht, sec_vers, privkey, pubkey):
        """
        Initializer for the SignQCC710 class.

        :param tool_path: Path to the JAR backend.
        :param bmht:      Image Authentication Request BHMT file.
        :param sec_vers:  Dict of {image names: security versions}.
        :param privkey:   Private key file.
        :param pubkey:    Public key file.
        """
        self.tool_path = tool_path
        self.bmht = bmht
        self.privkey = privkey
        self.pubkey = pubkey
        self.images = []
        self.sec_vers = sec_vers

    def add_image(self, name, filename):
        """
        Add an image descriptor to the object.

        :param name :    Type of image as one of the keys in IMAGE_INFO.
        :param filename: Binary file for the image.
        """
        if name in self.images:
            raise Exception('Duplicate Image: "{}"'.format(name))

        info = self.IMAGE_INFO[name]
        try:
            security_version = self.sec_vers[name]
        except KeyError:
            print(f'ERROR: No security version found for {name} image.')
            sys.exit(1)
        else:
            self.images.append(Image(name, filename, info['start'], info['size'], security_version, info['requires']))

    def generate(self, cert, image_list=None, update=False):
        """
        Get the options for generating the manifests.

        :param cert:       Root entitlement certificate file.
        :param image_list: List of images to use, defaults to all current images.
        :param update:     True for an update manifest, False for a boot manifest.

        :return: A tuple containing the binary data and the MRC hash for the
                 generated manifest
        """
        # Form the command.
        out_prefix = os.path.join(self.TEMP_PATH, 'manifest')
        command = [
            f'java',
            f'-cp {self.tool_path}',
            f'GenerateBootManifest',
            f'--cert {cert}',
            f'--cmdFile {self.bmht}',
            f'--privkey {self.privkey}',
            f'--pubkey {self.pubkey}',
            f'--out {out_prefix}',
            f'--logLevel ERROR',
        ]

        # Generate the json files for the image descriptors and add them to the
        # command.
        if not image_list:
            image_list = self.IMAGE_INFO.keys()

        offset = 0
        file_list = []
        command.append('--IDESC')
        for image in self.images:
            if image.name in image_list:
                if update:
                    image = copy(image)
                    image.address = offset
                    offset += image.padded_len()
                filename = image.write_json(self.TEMP_PATH)
                file_list.append(filename)
                command.append(f'"{filename}"')

        # Turn the command list into a string.
        command = ' '.join(command)

        # Execute the tool.
        try:
            if os.system(command):
                print('\nError executing tool: {}\n'.format(command))
                raise Exception('Error executing tool')

            # Read the generated manifest data.
            with open(out_prefix + '.bin', 'rb') as file:
                manifest = file.read()

            # Catch the case where the tool failed but didn't exit with an error
            if len(manifest) < 4:
                print('\nError executing tool: {}\n'.format(command))
                raise Exception('Error executing tool')

            with open(out_prefix + '-idesc.bin', 'rb') as file:
                manifest += file.read()

            # Get the MRC Hash.
            with open(out_prefix + '.json', 'r') as file:
                man_info = json.load(file)
                mrc_hash = man_info['SvcImageAuthentication']['ImageDescriptor']['FingerprintHash']['HashArray']
                if mrc_hash.startswith('0x'):
                    mrc_hash = mrc_hash[2:]
        except:
            raise
        finally:
            # remove the json files that were created.
            for filename in file_list:
                os.remove(filename)

            try:
                # Remove the intermediate files.
                os.remove(os.path.join(self.TEMP_PATH, 'rolling.log'))
                for ext in ['.json', '.bin', '.hex']:
                    os.remove(out_prefix + ext)
                    os.remove(out_prefix + '-idesc' + ext)
            except:
                pass

            try:
                os.rmdir(self.TEMP_PATH)
            except:
                pass

        return manifest, mrc_hash

    def gen_manifest(self, cert, output):
        """
        Generate the manifest binary.

        :param cert:   Binary certificate file.
        :param output: Output file.
        """
        # Sanitize received list of images for a boot manifest
        required = set(['BTSS_CFG', 'APP_SS'])
        licensed = set(['BTSS_CFG', 'APP_SS', 'BTSS_LIC'])
        have = set([image.name for image in self.images])
        if have != required and have != licensed:
            raise Exception(f'Required images missing. {required} is required, BTSS_LIC is optional. \nGot {have}')

        # Generate the boot manifest
        manifest, mrc_hash = self.generate(cert, image_list=have)

        # Ensure output path exists and create files
        Path(output).parent.mkdir(parents=True, exist_ok=True)
        with open(output, 'wb') as file:
            # Write the manifest tag and values
            file.write(struct.pack('<HH', self.MANIFEST_ID, len(manifest)))
            file.write(manifest)

        # write the hash to a file
        with open(os.path.splitext(output)[0] + '.hash', 'w') as file:
            file.write('sign:')
            file.write(mrc_hash)
            # write the reversed MRC for the OTP_Programmer
            file.write('\notp: ')
            file.write(''.join([mrc_hash[Index-2:Index] for Index in range(len(mrc_hash),0,-2)]))

    def gen_update(self, cert, output):
        """
        Generate the update package.

        :param cert:   Binary certificate file.
        :param output: Output file.
        """
        # Verify the required manifests were specified.
        for image in self.images:
            for required in image.requires:
                if required not in self.images:
                    raise Exception(f'Missing required image: "{required}"')

        manifest, _ = self.generate(cert, update=True)

        # Ensure output path exists and create files
        Path(output).parent.mkdir(parents=True, exist_ok=True)
        with open(output, 'wb') as file:
            file.write(struct.pack('<HH', self.UPDATE_ID, len(manifest)))
            file.write(manifest)

            # Write the images to be updated
            for image in self.images:
                file.write(image.data)
                file.write(b'\0' * image.pad_len())


def get_secvers_from_manifest(manifest_file):
    """
    Find the security version field for all images in the received manifest file.
    Return a dictionary with all {SWID: security_version} pairs found.

    :param manifest_file: Boot manifest file containing image descriptor array.
    """
    # print(f'Reading security versions from {manifest_file}')
    security_versions = {}
    with open(manifest_file, 'rb') as f:
        try:
            tag, _ = struct.unpack('<HH', f.read(4))     # Get tag,len for top level container
            tag, l_bm = struct.unpack('<HH', f.read(4))  # Get tag,len for boot manifest
            f.seek(l_bm, 1)

            # Collect ID entries
            tag, l_ida = struct.unpack('<HH', f.read(4))  # Get tag,len for ID array
            idx = 0
            while idx < l_ida:
                # print(idx, l_ida)
                tag, l_id = struct.unpack('<HH', f.read(4))  # Get tag,len for first ID
                security_versions.update(get_security_version_and_swid(f.read(l_id)))
                idx += 4 + l_id

        except struct.error as e:
            print(f'ERROR: Couldn\'t read Security Version fields from file {manifest_file}.')
            print(e.with_traceback())
            sys.exit(1)

    return security_versions


def get_security_version_and_swid(id_data):
    """
    Parse tags in image descriptor looking for SWID and SecVer.
    Returns a dict with IMAGE_NAME: security_version.
    Doesn't recur into tags as wanted tags are top-level.

    :param id_data: Image descriptor binary data.
    """
    # print(f'Parsing Image descriptor: {type(id_data)}, {len(id_data)}, {id_data.hex()}')
    swid, security_version = -1, -1
    idx = 0
    while idx < len(id_data):
        t, l = struct.unpack_from('<HH', id_data, idx)
        if l == 4:
            fmt = 'I'
        elif l == 8:
            fmt = 'L'
        else:
            fmt = f'{l}s'
        v = struct.unpack_from(f'<{fmt}', id_data, idx + 4)[0]
        # print(f'tag {t:#06x}, len {l}, value {hex(v) if l < 8 else binascii.hexlify(v)}')
        if t == 0x8351:
            swid = v
        if t == 0x8301:
            security_version = v
        idx += 4 + l

    return {IMAGE_LIST[SWIDS_TO_NAMES[swid]]: security_version}


def main():
    # Parse the command line arguments.
    parser = argparse.ArgumentParser(description='Generate signed manifests for the QCC710.')
    parser.add_argument('-p', '--tool_path', metavar='PATH_TO_JAR_FILE', default='./signing-tool-backend-all-1.0.1.jar')
    parser.add_argument('-o', '--output',    help='Output bin file (defaults to CWD and the name of the JSON file).')
    parser.add_argument('-t', '--type', required=True, metavar='<manifest|update>', choices=['manifest', 'update'])
    parser.add_argument('-c', '--cert', required=True, metavar='CERT_FILE',   help='Root certificate file.')
    parser.add_argument('-b', '--bmht', required=True, metavar='BMHT_FILE',   help='IAR BMHT to use.')
    parser.add_argument('--privkey',    required=True, metavar='PRIVATE_KEY', help='Private key file.')
    parser.add_argument('--pubkey',     required=True, metavar='PUBLIC_KEY',  help='Public key file.')
    image_group = parser.add_argument_group('Images')
    image_group.add_argument('-Q', '--qti-man', metavar='QTI_MANIFEST', help='QTI manifest.')
    image_group.add_argument('-O', '--oem-man', metavar='OEM_MANIFEST', help='OEM manifest.')
    image_group.add_argument('-T', '--tme', metavar='TME_IMAGE', help='TME image file.')
    image_group.add_argument('-B', '--btss', metavar='BTSS_IMAGE', help='BTSS image file.')
    image_group.add_argument('-C', '--btcfg', metavar='BTCFG_IMAGE', help='BT CFG image file.')
    image_group.add_argument('-A', '--apss', metavar='APSS_IMAGE', help='APSS image file.')
    image_group.add_argument('-L', '--lic', metavar='LIC_IMAGE', help='License image file.')
    sec_ver_group = parser.add_argument_group('Security Versions', 'Security version of binary images.')
    sec_ver_group.add_argument('-V', '--sec_ver_apps', metavar='SEC_VER_APPS', default=1, help='Apps security version.')
    args = parser.parse_args()

    # Get security version fields:
    # For boot manifest, from CLI.
    # For update manifest, read from the boot manifests.
    if args.type == 'manifest':
        security_versions = {
            IMAGE_LIST['apss']: args.sec_ver_apps,
            IMAGE_LIST['btcfg']: 1,
            IMAGE_LIST['lic']: 1,
        }
    else:
        security_versions = {
            IMAGE_LIST['oem_man']: 1,
            IMAGE_LIST['qti_man']: 1,
        }
        for man in filter(None, [args.oem_man, args.qti_man]):
            security_versions.update(get_secvers_from_manifest(man))

    # Build the signing object
    print(f'INFO: Using security versions: {security_versions}.')
    sign_qcc710 = SignQCC710(args.tool_path, args.bmht, security_versions, args.privkey, args.pubkey)

    # Add all the specified images to the signing object
    for image, name in IMAGE_LIST.items():
        if args.__dict__[image]:
            sign_qcc710.add_image(name, args.__dict__[image])

    output = args.output if args.output is not None else Path(args.cert).stem
    if args.type == 'manifest':
        sign_qcc710.gen_manifest(args.cert, output)
    elif args.type == 'update':
        if args.sec_ver_apps or args.sec_ver_btcfg or args.sec_ver_lic:
            print('INFO: Security versions read from corresponding boot manifests.')
        sign_qcc710.gen_update(args.cert, output)


if __name__ == "__main__":
    main()
