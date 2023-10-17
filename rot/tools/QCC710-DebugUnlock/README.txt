// =============================================================================
// * Copyright (c) 2021 Qualcomm Technologies, Inc.
// * All Rights Reserved.
// * Confidential and Proprietary - Qualcomm Technologies, Inc.
// =============================================================================

================================================================================
Prerequisites
================================================================================
    1. Python version >= 3.7
    2. Sectools
    3. JLink software
    4. Install following python packages
        - Install "argparse" using "pip install argparse==1.4.0"
        - Install QCOM internal package "pydbg-core" (Applicable for JLink based
        testing only) using
        "pip install -i https://devpi.qualcomm.com/qtil/rel pydbg-core"

================================================================================
Contents
================================================================================
Following are the key files required for Debug unlock tool execution
    - debug_unlock.py
    - debugger_framework.py
    - dmi_utils.py

================================================================================
Usage
================================================================================
Step 1) Generate the DPR request using sectools (Optional step)

Syntax: python generate_dpr.py -c <config_file> [--ahb_sysfabric_dbgen] [--debug_module_dbgen] [--apps_dbgen] [--apps_aon_dbgen] [--apps_watchdog_dbgen]

i) "python generate_dpr.py -h" -- for detailed generate dpr tool usage help
ii) Config parameter (-c) indicates configuration file that contains available configuration options and its explanation.
iii) Specify the oem debug re-enable request. Possible options: --ahb_sysfabric_dbgen, --debug_module_dbgen, --apps_dbgen, --apps_aon_dbgen and --apps_watchdog_dbgen. These five arguments are optional.

Eg: python generate_dpr.py -c debug.cfg --ahb_sysfabric_dbgen --debug_module_dbgen --apps_dbgen --apps_aon_dbgen --apps_watchdog_dbgen



Step 2) Executing the DPR request using Debug unlock tool.

Syntax: python debug_unlock.py -d <signed_dpr> -l <log_option>

i) "python debug_unlock.py -h" -- for detailed tool usage help
ii) Signed dpr file parameter (-d) specifies the path of signed dpr request bin file.
iii) Log level parameter (-l) indicates log level. Supported: "low"/"high".

Eg: python debug_unlock.py -d "output_files/signedDprRequest.bin" -l "high"
