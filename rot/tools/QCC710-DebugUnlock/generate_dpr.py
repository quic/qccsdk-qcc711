#===============================================================================
# Copyright (c) 2021 Qualcomm Technologies, Inc.
# All Rights Reserved.
# Confidential and Proprietary - Qualcomm Technologies, Inc.
#===============================================================================
import argparse
import os
import ast
import sys
import platform
from dmi_utils import *

class generate_dpr_tool(object):
    def __init__(self):
        #Parsing the input parameters
        self.parser = argparse.ArgumentParser()
        self.parser.add_argument('-c', '--config_file', help='Configuration file', required=True)
        self.parser.add_argument('--ahb_sysfabric_dbgen', nargs='?', const=' --debug-ahb-sysfabric-dbgen', default='', help='Enable AHB_SYSFABRIC_DBGEN.')
        self.parser.add_argument('--debug_module_dbgen', nargs='?', const=' --debug-debug-module-dbgen', default='', help='Enable DEBUG_MODULE_DBGEN.')
        self.parser.add_argument('--apps_dbgen', nargs='?', const=' --debug-apps-dbgen', default='', help='Enable APPS_DBGEN.')
        self.parser.add_argument('--apps_aon_dbgen', nargs='?', const=' --debug-apps-aon-dbgen', default='', help='Enable AON register access debug for APPS.')
        self.parser.add_argument('--apps_watchdog_dbgen', nargs='?', const=' --debug-apps-watchdog-dbgen', default='', help='Disable Apps watchdog chip reset on bite.')
        self.args = self.parser.parse_args()

        #Read the configuration file
        config_file = self.args.config_file
        if os.path.exists(config_file):
            with open(config_file) as f:
              data = f.read()
            f.close()
        else:
           dmi_log(DMI_LOG_ERROR,"\"%s\" file path Invalid (OR) Does not Exist"%config_file)
           sys.exit()

        self.configData = ast.literal_eval(data)

    #Generating a DPR request
    def generate_dpr_request(self):
        signed_dpr = self.configData['signed_dpr']
        security_profile = self.configData['security_profile']
        sectools = self.configData['sectools']
        private_key = self.configData['private_key']
        certificate = self.configData['certificate']
        chip_unique_id = self.configData['chip_unique_id']
        sectools_additional_input = self.configData['sectools_additional_input']

        #Remove previous dpr request file
        if(os.path.isfile(signed_dpr)):
            os.remove(signed_dpr)

        debug_vector_command = self.args.apps_watchdog_dbgen + self.args.apps_aon_dbgen + self.args.apps_dbgen + self.args.debug_module_dbgen + self.args.ahb_sysfabric_dbgen
        if platform.system()=="Windows":
            sectools = '""'+sectools+'"'
        command = sectools+" tme-secure-debug --generate --dec \""+certificate+"\" --serial-number "+chip_unique_id+" --security-profile \""+security_profile+"\""+debug_vector_command+" --root-key \""+private_key+"\""+sectools_additional_input+" --sign --signing-mode LOCAL --outfile \""+signed_dpr+"\""
        os.system(command)

        if os.path.exists(signed_dpr) == False:
            dmi_log(DMI_LOG_ERROR,"DPR request command failed.")
            sys.exit()

        dmi_log(DMI_LOG_INFO,"DPR request generated successfully.")

if __name__ == "__main__":
    tool = generate_dpr_tool()
    tool.generate_dpr_request()
