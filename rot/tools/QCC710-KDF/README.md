<!-- 
 Copyright (c) 2020, 2022 Qualcomm Technologies, Inc.
 All rights reserved.
 Confidential and Proprietary - Qualcomm Technologies, Inc. 
-->
# Lists of APIs this packages supports
- ### Key Derivation using HKDF 
- ### Key Derivation using NIST KDF 

### Dependencies
1. python >= 3.7
2. pip >= 19.0.0
3. wheel 0.36.2
4. cryptography 3.4.7
5. ecdsa 0.17.0

The package has been tested with dependency version listed above.
The package requires Ubuntu Version 18.04 LTS.
The package also use dataclasses but with the python version 3.7 and above, dataclasses are in-built.
In case your execution environment complains about dataclasses, you may install version 0.8 explicitly.

### Check Dependencies
1. python3
```
python3 --version
pip3 --version
```

If not installed, please follow the steps below to install python3 and pip. 

### Install Dependecies
* python3
```
sudo apt install python3 python3-pip
```

Note: Please check whether you have latest pip3 version. If not, please upgrade pip3 using below command:
```
python -m pip install --upgrade pip
```

* wheel
Run the below command from project root directory.
```
pip3 install wheel==0.36.2
```

* cryptography
```
pip3 install cryptography==3.4.7
```

* ecdsa
```
pip3 install ecdsa==0.17.0
```

### Install package
Go to QCC710-KDF project root directory
```
cd QCC710-KDF
```
Run the below command from project root directory.
```
pip3 install -e .
```

### Run Tests
- Install pytest framework to get list of test passed and failed.
```
pip3 install pytest
```

- Run the below commands from tests directory in QCC710-KDF/kdf.
```
cd ./kdf/tests/
pytest -rP
```
