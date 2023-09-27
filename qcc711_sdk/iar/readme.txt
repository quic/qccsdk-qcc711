The 'qcc710_Loader' folder contains the flash loader for qcc710.
To use qcc710 flash loader:
- Select a project in workspace, right click on it to open project config options.
- Select 'Debugger' in category column.
- Click on 'Setup' tag, select 'J-Link/J-Trace' under 'Driver' section, check 'Run to' option and put in main.
- Click on 'Download' tag, select 'Verify download', 'Use flashloader(s)', 'Overwrite default board file' options and
  put in $PROJ_DIR$\..\qcc710_Loader\qcc710_Loader.board
- Click on 'J-Link/J-Trace' in in category column.
- Select 'Setup' tag, set 'Reset' to 'Normal', set 'JTAG/SWD speed' to 'Auto'.
- Select 'Connection' tag, set 'Communication' to 'USB', set 'Interface' to 'SWD'.
- Click OK

The 'Qualcomm' folder contains files for adding qcc710 to IAR device list.
For adding qcc710 to IAR device list:
- Copy the 'Qualcomm' folder into 'IAR_TOOL_DIR\config\devices' folder
- IAR_TOOL_DIR is path to the folder where the IAR is installed, for example C:\Program Files (x86)\IAR Systems\Embedded Workbench 8.0\arm
To use the qcc710 from IAR device list:
- Select a project in workspace, right click on it to open project config options.
- Select 'General Options' in category column.
- Select 'Target', click 'Device' in 'Processor Variant' section.
- Click on 'device list' icon, go to 'Qualcomm' section and click on it to use 'qcc710' as the target device.

To use batch build
- Click on 'Project' on the menu bar.
- Select 'Batch build ...'
- Select the desired bacth build action in the pop out window.
- Click 'Make', 'Clean', or 'Rebuild All'

