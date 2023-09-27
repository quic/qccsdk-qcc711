# Lists of APIs this tool supports
- ### Validation of QCC710 Update Package generated using QCC710-Signing Tool 

### Dependencies
1. python >= 3.7
2. pip >= 19.0.0
3. beautifultable 1.0.1
4. termcolor 1.1.0
5. colorama 0.4.4

The tool has been tested with dependency version listed above.
The tool has been tested on Windows 10 and Ubuntu 18.04.
The tool also use dataclasses but with the python version 3.7 and above, dataclasses are in-built.
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
python3 -m pip install --upgrade pip
```

* beautifultable
```
python3 -m pip install beautifultable==1.0.1
```

* termcolor
```
python3 -m pip install termcolor==1.1.0
```

* colorama
```
python3 -m pip install colorama==0.4.4
```

### Execute Tool
- Go to QCC710-PackageParser project root directory
```
cd QCC710-PackageParser/parser
```
- Run the below command from project root directory.
```
python3 parse_and_verify_update_package.py -p <absolute path of update package>
```

### Execute Tool with Validation result logged in file
- Go to QCC710-PackageParser project root directory
```
cd QCC710-PackageParser/parser
```
- Run the below command from project root directory.
```
python3 parse_and_verify_update_package.py -p <absolute path of update package> --gen_log
```

### Sample Outputs
```
╔══════════════╤═════════════════════════════╤═══════════════════════════╤═══════════════════════════╤════════════════════╗
║              │ Available in Update Package │ Available in QTI Manifest │ Available in OEM Manifest │ Validation Message ║
╟──────────────┼─────────────────────────────┼───────────────────────────┼───────────────────────────┼────────────────────╢
║  BT Config   │             Yes             │      Not Applicable       │            Yes            │    Image Valid     ║
╟──────────────┼─────────────────────────────┼───────────────────────────┼───────────────────────────┼────────────────────╢
║  BTSS Patch  │             Yes             │            Yes            │      Not Applicable       │    Image Valid     ║
╟──────────────┼─────────────────────────────┼───────────────────────────┼───────────────────────────┼────────────────────╢
║     APSS     │             Yes             │      Not Applicable       │            Yes            │    Image Valid     ║
╟──────────────┼─────────────────────────────┼───────────────────────────┼───────────────────────────┼────────────────────╢
║  RoT Patch   │             Yes             │            Yes            │      Not Applicable       │    Image Valid     ║
╟──────────────┼─────────────────────────────┼───────────────────────────┼───────────────────────────┼────────────────────╢
║   License    │             Yes             │            Yes            │            Yes            │    Image Valid     ║
╟──────────────┼─────────────────────────────┼───────────────────────────┼───────────────────────────┼────────────────────╢
║ QTI Manifest │             Yes             │      Not Applicable       │      Not Applicable       │    Image Valid     ║
╟──────────────┼─────────────────────────────┼───────────────────────────┼───────────────────────────┼────────────────────╢
║ OEM Manifest │             Yes             │      Not Applicable       │      Not Applicable       │    Image Valid     ║
╚══════════════╧═════════════════════════════╧═══════════════════════════╧═══════════════════════════╧════════════════════╝
Overall Status of Update Package : Valid

╔══════════════╤═════════════════════════════╤═══════════════════════════╤═══════════════════════════╤════════════════════╗
║              │ Available in Update Package │ Available in QTI Manifest │ Available in OEM Manifest │ Validation Message ║
╟──────────────┼─────────────────────────────┼───────────────────────────┼───────────────────────────┼────────────────────╢
║  BT Config   │             Yes             │      Not Applicable       │            Yes            │    Image Valid     ║
╟──────────────┼─────────────────────────────┼───────────────────────────┼───────────────────────────┼────────────────────╢
║  BTSS Patch  │             Yes             │            Yes            │      Not Applicable       │    Image Valid     ║
╟──────────────┼─────────────────────────────┼───────────────────────────┼───────────────────────────┼────────────────────╢
║     APSS     │             Yes             │      Not Applicable       │            Yes            │    Image Valid     ║
╟──────────────┼─────────────────────────────┼───────────────────────────┼───────────────────────────┼────────────────────╢
║  RoT Patch   │             Yes             │            Yes            │      Not Applicable       │    Image Valid     ║
╟──────────────┼─────────────────────────────┼───────────────────────────┼───────────────────────────┼────────────────────╢
║   License    │             Yes             │            No             │            Yes            │    Image Valid     ║
╟──────────────┼─────────────────────────────┼───────────────────────────┼───────────────────────────┼────────────────────╢
║ QTI Manifest │             Yes             │      Not Applicable       │      Not Applicable       │    Image Valid     ║
╟──────────────┼─────────────────────────────┼───────────────────────────┼───────────────────────────┼────────────────────╢
║ OEM Manifest │             Yes             │      Not Applicable       │      Not Applicable       │    Image Valid     ║
╚══════════════╧═════════════════════════════╧═══════════════════════════╧═══════════════════════════╧════════════════════╝
Overall Status of Update Package : Valid
Note : License is present in only one manifest. Make sure license on chip, if present, is same as the one used in update package

╔══════════════╤═════════════════════════════╤═══════════════════════════╤═══════════════════════════╤════════════════════╗
║              │ Available in Update Package │ Available in QTI Manifest │ Available in OEM Manifest │ Validation Message ║
╟──────────────┼─────────────────────────────┼───────────────────────────┼───────────────────────────┼────────────────────╢
║  BT Config   │             Yes             │      Not Applicable       │            Yes            │    Image Valid     ║
╟──────────────┼─────────────────────────────┼───────────────────────────┼───────────────────────────┼────────────────────╢
║  BTSS Patch  │             Yes             │            Yes            │      Not Applicable       │    Image Valid     ║
╟──────────────┼─────────────────────────────┼───────────────────────────┼───────────────────────────┼────────────────────╢
║     APSS     │             Yes             │      Not Applicable       │            Yes            │   Image Invalid    ║
╟──────────────┼─────────────────────────────┼───────────────────────────┼───────────────────────────┼────────────────────╢
║  RoT Patch   │             Yes             │            Yes            │      Not Applicable       │    Image Valid     ║
╟──────────────┼─────────────────────────────┼───────────────────────────┼───────────────────────────┼────────────────────╢
║   License    │             Yes             │            Yes            │            Yes            │    Image Valid     ║
╟──────────────┼─────────────────────────────┼───────────────────────────┼───────────────────────────┼────────────────────╢
║ QTI Manifest │             Yes             │      Not Applicable       │      Not Applicable       │    Image Valid     ║
╟──────────────┼─────────────────────────────┼───────────────────────────┼───────────────────────────┼────────────────────╢
║ OEM Manifest │             Yes             │      Not Applicable       │      Not Applicable       │    Image Valid     ║
╚══════════════╧═════════════════════════════╧═══════════════════════════╧═══════════════════════════╧════════════════════╝
Overall Status of Update Package : Invalid
```