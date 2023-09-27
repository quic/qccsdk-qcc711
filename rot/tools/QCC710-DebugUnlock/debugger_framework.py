#===============================================================================
# Copyright (c) 2021 Qualcomm Technologies, Inc.
# All Rights Reserved.
# Confidential and Proprietary - Qualcomm Technologies, Inc.
#===============================================================================

import os
import subprocess
import ctypes
import time
import platform
import binascii
import socket
import os
import codecs
import ast
import sys
from dmi_utils import *
from csr.front_end.pydbg_front_end import device_attach

ITERATION = 20
TIMEOUT = 2
WAKE_UP_TIME_LIMIT = 4

class jlink(object):
    def __init__(self):
        dmi_log(DMI_LOG_INFO,"Debugger Selected :: JLink" )
        self.dmi=''

    #Setting up the Jlink connection
    def setup(self):
        device = device_attach(device_url="jlink", target="ziggy")
        if device is None:
            dmi_log(DMI_LOG_ERROR,"Unable to Attach device")
            return GEN_ERROR

        self.sys_fabric = device.chip.system_fabric
        self.wake_up_rot()

        self.dmi = device.chip.tme_dmi
        if  self.dmi is None:
            dmi_log(DMI_LOG_ERROR," DMI Module not Found in Pydbg")
            return GEN_ERROR

        return SUCCESS

    #Waking up ROT sub-system
    def wake_up_rot(self):
        dmi_log(DMI_LOG_INFO,"Waking up ROT from sleep")

        #Wake up ROT through Sys Fabric
        #Ignoring the error when setting the ROT vote through jlink
        try:
            self.sys_fabric.dataw[0x500063fc] = 1
        except:
            pass

        try:
            #Wait till ROT wakes up for WAKE_UP_TIME_LIMIT seconds
            num_seconds = 0
            while num_seconds < WAKE_UP_TIME_LIMIT:
                if self.sys_fabric.dataw[0x500063fc] == 2:
                    dmi_log(DMI_LOG_INFO,"ROT is up")
                    break
                time.sleep(1)
                num_seconds += 1
        except:
            dmi_log(DMI_LOG_ERROR,"Unable to wake up ROT by voting through Sys Fabric")

    #Put ROT sub-system to sleep
    def make_rot_sleep(self):
        dmi_log(DMI_LOG_INFO,"Making ROT go to sleep")
        try:
            self.sys_fabric.dataw[0x500063fc] = 0
        except:
            dmi_log(DMI_LOG_ERROR,"Unable to make ROT go to sleep by voting through Sys Fabric")

    #Defining the trace logs
    def trace_log(self, op, name, data):
        global dmi_reg_set
        dmi_trace_log("[%5s][%21s][A:0x%08x][D:0x%08x] successful"% (op, name, dmi_reg_set[name], data))

    #Reading the value from memory address
    def read_memory(self, name):
        global dmi_reg_set
        address = dmi_reg_set[name]
        data = self.dmi.dataw[address]
        self.trace_log("Read", name, data)
        return data

    #Writing the value at memory address
    def write_memory(self, name, data):
        global dmi_reg_set
        address = dmi_reg_set[name]
        self.dmi.dataw[address] = data
        self.trace_log("Write", name, data)
        return SUCCESS

    #Checking the status of DMI INFIFO or DMI OUTFIFO
    def check_status(self,status):
        for x in range(ITERATION) :
            data=self.read_memory('DMI_FIFO_STATUS1')
            if data == GEN_ERROR:
                pass
            else :
                infifo_length  =  (data & 0x000000ff)
                outfifo_length = ((data & 0x0000ff00) >> 8)
                if ( status == "READ"):
                    if outfifo_length >  0  :
                        return SUCCESS, outfifo_length
                    else:
                        dmi_log(DMI_LOG_INFO,"READ: ROT did not respond for ",x*TIMEOUT," seconds.")
                        time.sleep(TIMEOUT)
                elif ( status == "WRITE"):
                    if infifo_length > 0  :
                        return SUCCESS, infifo_length
                    else:
                        dmi_log(DMI_LOG_INFO,"WRITE: ROT did not consume data for ",x*TIMEOUT," seconds.")
                        time.sleep(TIMEOUT)
                if self.get_dmi_sw_state() != DMI_HEALTHY :
                    break
        return GEN_ERROR, 0

    #Sedning data to DMI INFIFO
    def send_data(self,in_buffer):
        dmi_trace_log("Total 0x%08x Words to write into %s" % (len(in_buffer),'DMI_INFIFO'))

        infifo_length = 0
        for data in in_buffer:
            if infifo_length == 0:
                infifo_status, infifo_length = self.check_status("WRITE")
                if infifo_status != 0 :
                    dmi_log(DMI_LOG_DEBUG,"No free space available to write to DMI_INFIFO")
                    return GEN_ERROR
            error = self.write_memory('DMI_INFIFO',data)
            if error == GEN_ERROR:
                return GEN_ERROR
            infifo_length -= 1

        return SUCCESS

    #Getting the data from DMI OUT FIFO
    def get_data(self,out_buffer):
        data=0
        outfifo_length = 0
        outfifo_status, outfifo_length = self.check_status("READ")
        if outfifo_status == 0:
            data = self.read_memory("DMI_OUTFIFO")
            bytes_to_be_read=((data & 0xffff0000) >> 16 )
            out_buffer.append((data))
            if data == GEN_ERROR:
                dmi_log(DMI_LOG_DEBUG,"Read from DMI_OUTFIFO Failed")
                return GEN_ERROR
            else:
                dmi_trace_log("Total 0x%08x Words remaining to read from %s" % (int(int(bytes_to_be_read)/4),'DMI_OUTFIFO'))
                outfifo_length -= 1
        else :
            dmi_log(DMI_LOG_ERROR,"No Words available to read from DMI_OUTFIFO")
            return GEN_ERROR
        for i in range(0, bytes_to_be_read, 4):
            if outfifo_length == 0:
                outfifo_status, outfifo_length = self.check_status("READ")
                if outfifo_status != 0 :
                    return GEN_ERROR
            data = self.read_memory("DMI_OUTFIFO")
            if data == GEN_ERROR:
                return GEN_ERROR
            out_buffer.append((data))
            outfifo_length -= 1

        return SUCCESS

    #Handling the error
    def error_recovery(self):
        dmi_log(DMI_LOG_INFO,"Attempting DMI Error recovery")
        if GEN_ERROR == self.set_dmi_client_state(DMI_CLIENT_ERROR_ACK):
            return GEN_ERROR
        if self.read_memory("DMI_INBOUND_SCRATCH0") != DMI_CLIENT_ERROR_ACK:
            dmi_log(DMI_LOG_ERROR,"ROT Not Up!!")
        else:
            for i in range(10):
                dmi_sw_state = self.get_dmi_sw_state()
                if dmi_sw_state == DMI_HEALTHY:
                    if GEN_ERROR == self.set_dmi_client_state(DMI_CLIENT_HEALTHY):
                        return GEN_ERROR
                    dmi_log(DMI_LOG_INFO,"DMI Error recovery successful")
                    return SUCCESS
                time.sleep(1)
        dmi_log(DMI_LOG_ERROR,"DMI Error recovery failed")
        return GEN_ERROR

    #Getting the software state of DMI
    def get_dmi_sw_state(self):
        dmi_sw_state = self.read_memory("DMI_OUTBOUND_SCRATCH0") & DMI_STATE_MASK
        return dmi_sw_state

    #Getting DMI Client status
    def set_dmi_client_state(self, dmi_client_state):
        return self.write_memory("DMI_INBOUND_SCRATCH0", dmi_client_state)
