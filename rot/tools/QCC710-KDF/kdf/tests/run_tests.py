#!/usr/bin/env python
"""!
@brief It invokes various test cases for APIs
defined in package.


@section
Copyright (c) 2020 Qualcomm Technologies, Inc.
All rights reserved.
Confidential and Proprietary - Qualcomm Technologies, Inc.
"""


from test_derive_key import tests_derive_key_hkdf, tests_derive_key_nist


def main():
    # Key Derivation using HKDF
    # Test cases for key derivation. Key is derived from base key
    # using HKDF
    tests_derive_key_hkdf()

    # Key Derivation using NIST KDF
    # Test cases for key derivation. Key is derived from base key
    # using NIST KDF
    tests_derive_key_nist()


if __name__ == "__main__":
    main()
