@ECHO OFF

REM
REM This is an example of how to use the cfgtag.py script to update a config tag binary.
REM Paths are relative to this batch script i.e. "SDK_ROOT/tools/scripts/examples".
REM 
REM The script requires some parameters to run:
REM  - The TCFX file describing the config tags to be edited.
REM  - The offsets file describing tag locations.
REM  - The input config tag to be patched.
REM  - The generated output config tag. 
REM  - The list of NVMX files that are applied to the binary.
REM 
REM These inputs are hardcoded in this example, however, in most cases, the list of NVMX
REM files should be determined at build time, and applied to the Qualcomm-provided binary
REM containing the baseline configuration. The patched output binary should then be used
REM when creating the final application image.
REM
REM The utility also allows the following options in special use cases:
REM  --allow-missing    : Allows applying NVMX files containing unknown tags, which will be skipped.
REM  --allow-duplicates : Allows applying NVMX files containing already-patched tags. Useful when overriding a previous NVMX.
REM
REM IMPORTANT NOTE!
REM 
REM The TCFX file and offsets file must not be modified, as it describes critical layout
REM information in order to properly interpret the tags and patch the correct location.
REM

SET SDK_ROOT=..\..\..\

SET TCFX_PATH="%SDK_ROOT%\tools\cfgtag\qcc710.tcfx"
SET OFFSETS_PATH="%SDK_ROOT%\tools\cfgtag\qcc710.offsets"

SET INPUT_APP="%SDK_ROOT%\bin\qcc710_btcfg_app.bin"
SET OUTPUT_APP="%SDK_ROOT%\bin\qcc710_btcfg_app_user.bin"

SET INPUT_HCI="%SDK_ROOT%\bin\qcc710_btcfg_hci.bin"
SET OUTPUT_HCI="%SDK_ROOT%\bin\qcc710_btcfg_hci_user.bin"

REM Run the utility twice, once for each QCC710 image.
REM Note the utility allows multiple NVMX files to be specified at once.
python ..\cfgtag.py --bin --taginfo %OFFSETS_PATH% --tcfx %TCFX_PATH% --input %INPUT_APP% --output %OUTPUT_APP% bd_addr_and_power.nvmx
python ..\cfgtag.py --bin --taginfo %OFFSETS_PATH% --tcfx %TCFX_PATH% --input %INPUT_HCI% --output %OUTPUT_HCI% bd_addr_and_power.nvmx
