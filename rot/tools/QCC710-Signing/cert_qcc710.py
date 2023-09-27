# ==============================================================================
# Copyright (c) 2020-2021 Qualcomm Technologies, Inc.
# All Rights Reserved.
# Confidential and Proprietary - Qualcomm Technologies, Inc.
# ==============================================================================
import argparse
import os
from pathlib import Path


class CertQCC710(object):
    """
    Class to create the QCC710 certificates.
    """
    TEMP_PATH = 'target'

    def __init__(self, tool_path, privkey, pubkey):
        """
        Initializer for the CertQCC710 class.

        :param tool_path: Path to the JAR backend.
        :param privkey:   Private key file.
        :param pubkey:    Public key file.
        """
        self.tool_path = tool_path
        self.privkey = privkey
        self.pubkey = pubkey

    def generate(self, cert_config, output):
        """
        Creates a certificate binary.

        :param cert_config: JSON configuration file for the certificate.
        :param output:      Name of the generated certificates.
        """
        out_path = Path(output)

        # Command parameters
        command = [
            f'java',
            f'-cp "{self.tool_path}"',
            f'GenerateEntitlementCertificate',
            f'--cert "{cert_config}"',
            f'--privkey "{self.privkey}"',
            f'--pubkey "{self.pubkey}"',
            f'--out "{out_path.parent / out_path.stem}"',
            f'--logLevel ERROR',
        ]
        command = ' '.join(command)

        # Make sure the path exists.
        out_path.parent.mkdir(parents=True, exist_ok=True)

        # Execute the tool.
        if os.system(command):
            print(f'\nError executing tool: {command}\n')
            raise Exception('Error executing tool')

        # Clean up generated files
        try:
            os.remove(os.path.join(self.TEMP_PATH, 'rolling.log'))
            os.rmdir(self.TEMP_PATH)
        except:
            pass


def main():
    # Parse the command line arguments.
    parser = argparse.ArgumentParser(description='Generate OEM Root Entitlement certificate for QCC710.')
    parser.add_argument('-p', '--tool_path', default='./signing-tool-backend-all-1.0.1.jar', help='Path to JAR backend.')
    parser.add_argument('--privkey', required=True, help='Private key file.')
    parser.add_argument('--pubkey', required=True, help='Public key file.')
    parser.add_argument('-c', '--cert', required=True, help='Certificate input file.')
    parser.add_argument('-o', '--output', help='Output files prefix (defaults to CWD and the name of the JSON file).')
    args = parser.parse_args()

    # Build the cert object
    cert = CertQCC710(args.tool_path, args.privkey, args.pubkey)

    # Generate the cert with the given output path
    output = args.output if args.output is not None else Path(args.cert).stem
    cert.generate(args.cert, output)


if __name__ == "__main__":
    main()
