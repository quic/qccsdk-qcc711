#===============================================================================
# Copyright (c) 2021 Qualcomm Technologies, Inc.
# All Rights Reserved.
# Confidential and Proprietary - Qualcomm Technologies, Inc.
#===============================================================================

###############################################################################
# DMI States
###############################################################################
DMI_UNINITIALIZED       = 0x0000
DMI_HEALTHY             = 0x4844   # ASCII("DH")
DMI_ERROR               = 0x4544   # ASCII("DE")
DMI_FATAL               = 0x4644   # ASCII("DF")
DMI_STATE_MASK          = 0xFFFF

DMI_CLIENT_HEALTHY      = 0x0000
DMI_CLIENT_ERROR_ACK    = 0x4143   # ASCII("CA")

###############################################################################
# DMI Error codes
###############################################################################
SUCCESS                 = 0
GEN_ERROR               = -1
ATTACH_ERROR            = -2

###############################################################################
# DMI Log levels
###############################################################################
DMI_LOG_ERROR           = 0
DMI_LOG_WARN            = 1
DMI_LOG_INFO            = 2
DMI_LOG_DEBUG           = 3

###############################################################################
# Trace Log
###############################################################################
TRACE_LOG_ENABLE        = 1
TRACE_LOG_DISABLE       = 0

###############################################################################
# Storing the address of scratch pad registers
###############################################################################
dmi_reg_set = {
    "DMI_FIFO_STATUS0"      :   0x00,
    "DMI_FIFO_STATUS1"      :   0x04,
    "DMI_INFIFO"            :   0x20,
    "DMI_OUTFIFO"           :   0x24,
    "DMI_INBOUND_SCRATCH0"  :   0x40,
    "DMI_INBOUND_SCRATCH1"  :   0x44,
    "DMI_OUTBOUND_SCRATCH0" :   0x60,
    "DMI_OUTBOUND_SCRATCH1" :   0x64
}

global dmi_log_level
global trace_log_option

#Initializing the variables
dmi_log_level = DMI_LOG_INFO
trace_log_option = TRACE_LOG_ENABLE

def dmi_log(*args):
    global dmi_log_level
    logs = ["DMI_LOG_ERROR", "DMI_LOG_WARN", "DMI_LOG_INFO", "DMI_LOG_DEBUG"]
    if int(args[0]) <= dmi_log_level:
        print("["+logs[int(args[0])]+"] "+"".join(map(str,args[1])))

def dmi_trace_log(*args):
    global trace_log_option
    if trace_log_option == 1:
        print("[DMI_LOG_TRACE]::"+"".join(map(str,args[0])))
    else:
        dmi_log(DMI_LOG_DEBUG, *args)
