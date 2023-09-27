<!-- 
 Copyright (c) 2020, 2022 Qualcomm Technologies, Inc.
 All rights reserved.
 Confidential and Proprietary - Qualcomm Technologies, Inc. 
-->
# Lists of APIs this packages supports
- ### X.509 Secure Wrap

### Dependencies
1. python >= 3.7
2. pip >= 19.0.0
3. wheel 0.36.2
4. pycryptodome 3.10.1
5. cryptography 3.4.7
6. QCC710-KDF 0.7.9

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

* pycryptodome
```
pip3 install pycryptodome==3.10.1
```
Note: 'pycryptodome' will not work along with 'pycrypto'. If any of your other project have 'pycrypto' dependency, please setup virtual environment and install 'wheel', 'pycose' and 'pycryptodome' in virtual environment or if 'pycrypto' is not required, please run below command.
```
pip3 uninstall pycrypto
```

* cryptography
```
pip3 install cryptography==3.4.7
```

* QCC710-KDF
Go to QCC710-KDF project root directory.
```
cd QCC710-KDF
```
Run the below command from project root directory.
```
pip3 install -e .
```

### Execute secure_wrap.py 
Go to securewrap folder in QCC710-SecureWrap.
```
cd QCC710-SecureWrap/securewrap
```
Run the below command.
```
python3 secure_wrap.py -j config.json -o outputfile
```