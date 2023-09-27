#===============================================================================
# Copyright (c) 2021 Qualcomm Technologies, Inc.
# All Rights Reserved.
# Confidential and Proprietary - Qualcomm Technologies, Inc.
#===============================================================================

import dmi_utils
from dmi_utils import *
import debugger_framework
import argparse
import time

NUM_ITERATIONS_TO_CHECK_DMI_STATE = 5
CHECK_DMI_STATE_TIMEOUT = 1

class debug_unlock_tool(object):
    def __init__(self, signed_dpr, log):
        self.signed_dpr = signed_dpr
        self.log = log

        # Assigning trace log and DMI log level
        if self.log == "high":
            dmi_utils.dmi_log_level = DMI_LOG_INFO
            dmi_utils.trace_log_option = TRACE_LOG_ENABLE
        else:
            dmi_utils.dmi_log_level = DMI_LOG_ERROR
            dmi_utils.trace_log_option = TRACE_LOG_DISABLE

        self.dbg = debugger_framework.jlink()

    #Writing the contents to a file
    def file_write(self,path,out_buffers):
        for out_buffer in out_buffers:
            file=open(path,"wb")
            for data in out_buffer:
                file.write(data.to_bytes(4, byteorder='little', signed=False))
            file.close()
        return SUCCESS

    #Reading the contents from a file
    def file_read(self,path):
        dmi_log(DMI_LOG_INFO,"Reading data from input file: %s" % path)
        rfile=open(path,"rb")
        data = rfile.read()
        rfile.close()
        file_length=len(data)
        dmi_log(DMI_LOG_INFO,"file_length: %d"%file_length)

        in_buffers = []
        while file_length > 0:
            buffer_size_to_send = int.from_bytes(data[2:4], byteorder='little', signed=False)
            dmi_log(DMI_LOG_INFO,"buffer_size_to_send: %d" %buffer_size_to_send)

            if ( buffer_size_to_send > file_length):
                dmi_log(DMI_LOG_ERROR,"File length validation Failed")
                return GEN_ERROR
            in_buffer =[]
            in_buf_size = min(buffer_size_to_send + 4, file_length)
            for i in range(0, in_buf_size, 4):
                in_buffer.append(int.from_bytes(data[i:i+4], byteorder='little', signed=False))
            in_buffers.append(in_buffer)
            file_length = file_length - in_buf_size
            if file_length > 0:
                data = data[in_buf_size:]
        return in_buffers

    #Starting the DMI session
    def start_session(self):
        dmi_log(DMI_LOG_INFO,"DMI Session Started")
        return self.dbg.setup()

    #Executing the DMI session
    def execute_session(self,in_buffer,out_buffer):
        # Checking target healty status before communicating
        dmi_trace_log("Checking for DMI SW State")
        for iteration_num in range(NUM_ITERATIONS_TO_CHECK_DMI_STATE):
            if self.dbg.get_dmi_sw_state() == DMI_HEALTHY:
                break
            dmi_log(DMI_LOG_INFO,"Waiting for DMI state to become healthy for ",iteration_num*CHECK_DMI_STATE_TIMEOUT," seconds.")
            time.sleep(CHECK_DMI_STATE_TIMEOUT)
        if self.dbg.get_dmi_sw_state() != DMI_HEALTHY:
            dmi_log(DMI_LOG_ERROR,"Target is not in HEALTHY STATE. Terminating DMI HOST Tool execution!!!")
            return GEN_ERROR
        if self.dbg.set_dmi_client_state(DMI_CLIENT_HEALTHY) == GEN_ERROR:
            dmi_log(DMI_LOG_ERROR,"Failed to set DMI_CLIENT_HEALTHY state")
            return GEN_ERROR
        dmi_trace_log("DMI SW Healthy!!!\n")
        dmi_trace_log("Starting to Send DMI Command")
        if self.dbg.send_data(in_buffer) == GEN_ERROR :
            dmi_log(DMI_LOG_ERROR,"Send data failed")
            return GEN_ERROR
        dmi_trace_log("DMI Command sent successfully!!!\n")
        dmi_trace_log("Waiting for DMI Command response.")
        time.sleep(2)
        if self.dbg.get_data(out_buffer) != SUCCESS:
            dmi_log(DMI_LOG_ERROR,"Receive data failed")
            return GEN_ERROR
        dmi_trace_log("Received DMI Command response successfully!!!\n")
        return SUCCESS

    #End session
    def end_session(self):
        self.dbg.make_rot_sleep()

    #Handling the error
    def error_recovery(self):
        return self.dbg.error_recovery()

    #Main entry API for tool script
    def main_loop(self):
        #Generate the DPR request
        dpr_bin = self.signed_dpr

        #Starting DMI session
        status = self.start_session()
        if status != SUCCESS:
            dmi_log(DMI_LOG_ERROR,"Start_session failed with error: %d"%error)
            return GEN_ERROR

        #Reading the generated DPR command request file
        in_buffers = self.file_read(dpr_bin)
        if in_buffers == GEN_ERROR :
            print ("Reading File Failed")
            return GEN_ERROR

        #Executing the DPR request
        out_buffers = []
        for in_buffer in in_buffers:
            in_buffer_hex=[]
            for element in in_buffer:
                in_buffer_hex.append(hex(element))

            #execute_session() can be called multiple times after start_session()
            out_buffer =[]
            if self.execute_session(in_buffer, out_buffer) == GEN_ERROR :
                # execute_session() failed, attempt error recovery
                dmi_log(DMI_LOG_INFO,"Execute_ session failed. Attempting Error Recovery!!")
                if self.error_recovery() == GEN_ERROR:
                    dmi_log(DMI_LOG_ERROR,"Error recovery failed. Exiting tool")
                else:
                    dmi_log(DMI_LOG_INFO,"Error recovery successful")
                return GEN_ERROR

            #Printing Out buffer contents in hex format.
            out_buffer_hex=[]
            for element in out_buffer:
                out_buffer_hex.append(hex(element))
            out_buffers.append(out_buffer)

        #Ending DMI session
        self.end_session()

        #Storing the ouput in output file
        for out_buffer_hex in out_buffers:
            if out_buffer_hex[1] == 0x0:
                dmi_log(DMI_LOG_INFO,"Command execution is successful")
            else:
                dmi_log(DMI_LOG_INFO,"Command failed with error code: 0x%x"%out_buffer_hex[1])

        return SUCCESS

#Main entry point for the tool script.
def main():
    #Parsing the input parameters
    parser = argparse.ArgumentParser()
    parser.add_argument('-d', '--signed_dpr', help='Signed DPR request bin file', required=True)
    parser.add_argument('-l', '--log', help='Specify the log level', required=True)
    args = parser.parse_args()

    tool = debug_unlock_tool(args.signed_dpr, args.log)
    tool.main_loop()

if __name__ == "__main__":
    main()
