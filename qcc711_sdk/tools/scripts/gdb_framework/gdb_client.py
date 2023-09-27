#===============================================================================
# Copyright (c) 2020-2021 Qualcomm Technologies, Inc.
# All Rights Reserved.
# Confidential and Proprietary - Qualcomm Technologies, Inc.
#===============================================================================
import sys
import os
import socket
import subprocess
import traceback
import random

class GDB_Client_Error(Exception):
    '''
    General GDB client error and super class for all GDB client exceptions.
    '''
    pass


class RemoteError(GDB_Client_Error):
    '''
    Exception indicating an error on the remote script.
    '''
    pass


class GDB_Client(object):
    '''
    Class representing the GDB client.
    '''
    SOCKET_FAMILY = socket.AF_INET
    SOCKET_ADDR = '127.0.0.1'
    MAX_PACKET_SIZE = 1024

    COMMAND_EXEC = 'EXEC'
    COMMAND_EVAL = 'EVAL'
    COMMAND_EXIT = 'EXIT'

    RESPONSE_CONNECT = 'CONNECT'
    RESPONSE_SUCCESS = 'SUCCESS'
    RESPONSE_RESULT = 'RESULT'
    RESPONSE_EXCEPT = 'EXCEPT'

    def __init__(self, server_port, client_exe, udp_port, log_file=None):
        '''
        Initializer for a GDB Client object.

        Parameters:
            server_port: GDB server port number.
            client_exe:  GDB client executable.
            udp_port:    UPD port for IPC traffic to the GDB client.
        '''
        self.server_port = server_port
        self.client_exe = client_exe
        self.udp_server = udp_port
        self.client_proc = None
        self.udp_socket = None
        self.udp_client = None
        self.default_timeout = 5
        self.log_file = log_file
        self.client_log = None

    @staticmethod
    def format_packet(command, data):
        '''
        Generates a packet to send over the socket.

        Parameters:
            command: Command or response type for the packet.
            data:    Data in the packet.

        Returns:
            An encoded packet.
        '''
        return '{}|{}|{}'.format(command, len(data), data).encode()

    @staticmethod
    def parse_packet(packet):
        '''
        Parses an encoded packet from the socket.

        Parameters:
            packet: Packet to parse.
            command: Command or response type for the packet.
            data:    Data in the packet.

        Returns:
            A list comprising of the command or response type (str), the length
            of the data (int) and the data (str).
        '''
        data = packet.decode().split('|', 2)
        data[1] = int(data[1])

        if data[1] != len(data[2]):
            raise GDB_Client_Error('Invalid packet: ' + str(data))
        return data

    def start(self):
        '''
        Starts the GDB client.
        '''
        # Verify the client hasn't already been started
        if self.client_proc:
            raise Execption('Socket to GDB client already started')

        try:
            # Create the UDP socket.
            self.udp_socket = socket.socket(GDB_Client.SOCKET_FAMILY, socket.SOCK_DGRAM, socket.IPPROTO_UDP)
            self.udp_socket.settimeout(self.default_timeout)

            # Start the GDB client
            randnum = random.randrange(0xFFFFFFFF)
            os.environ['GDB_PYTHON_RANDNUM'] = str(randnum)
            os.environ['GDB_PYTHON_SOCKET_PORT'] = str(self.udp_server)
            self.udp_socket.bind((GDB_Client.SOCKET_ADDR, self.udp_server))

            if self.log_file:
                if self.log_file == 'stdout':
                    self.client_log = None
                else:
                    self.client_log = open(self.log_file, 'ab')
                    self.client_log.write(b'\n********************************************************************************\n')
            else:
                self.client_log = open(os.devnull, 'wb')
            self.client_proc = subprocess.Popen([self.client_exe, '-command', __file__.rstrip('c'), '-batch', '-return-child-result'], stdout=self.client_log)

            # wait for the GDB client to connect to the socket
            response, address = self.udp_socket.recvfrom(GDB_Client.MAX_PACKET_SIZE)
            if address[0] != GDB_Client.SOCKET_ADDR:
                raise GDB_Client_Error('Unexpected Address: ' + str(address))

            response = GDB_Client.parse_packet(response)
            if response[0] != GDB_Client.RESPONSE_CONNECT:
                raise GDB_Client_Error('Unexpected Response: ' + str(response))

            if int(response[2]) != randnum:
                raise GDB_Client_Error('Client Verification Error')

            self.udp_client = address[1]
            self.udp_socket.connect(address)

            print('GDB tool port:   {0}:{1}'.format(GDB_Client.SOCKET_ADDR, self.udp_server))
            print('GDB client port: {0}:{1}'.format(GDB_Client.SOCKET_ADDR, self.udp_client))
        except:
            # Clean up the sockets and subprocess
            self.stop(True)
            raise

    def stop(self, Force=False):
        '''
        Kills the GDB client.
        '''
        try:
            if Force:
                self.client_proc.terminate()
            elif self.client_proc.poll() == None:
                try:
                    # Send an exit to the subprocess and wait for it to close.
                    self.udp_socket.settimeout(1)
                    self.udp_socket.send(GDB_Client.format_packet(GDB_Client.COMMAND_EXIT, ''))
                    self.udp_socket.recvfrom(GDB_Client.format_packet(MAX_PACKET_SIZE))
                    self.client_proc.communicate()
                except:
                    # Failed to kill the subproccess cleanly so just force it
                    self.client_proc.terminate()

            if self.client_log:
                self.client_log.close()
        except:
            pass

        # Close the socket
        try:
            self.udp_socket.close()
        except:
            pass

        self.client_proc = None
        self.udp_socket = None

    def send_command(self, command, data, timeout=None):
        '''
        Sends a command to the GDB client and wants for a response.

        Parameters:
            command: Command to send to the GDB client.
            data:    Data for the command
            timeout: Time in seconds for the operation to complete.

        Returns:
            A list containing the response type, data length, and response data
            received.
        '''
        # If no timeout was specified, use the default
        if timeout == None:
            timeout = self.default_timeout

        # make sure there isn't anything waiting in the receive buffer that may
        # have carried over from a previous command.
        try:
            self.udp_socket.settimeout(0)
            while True:
                self.udp_socket.recv(GDB_Client.MAX_PACKET_SIZE)
        except socket.error:
            pass

        # Send the data and wait for a response
        self.udp_socket.settimeout(self.default_timeout)
        command = GDB_Client.format_packet(command, data)
        if self.udp_socket.send(command) != len(command):
            raise GDB_Client_Error("Failed to send full command in one packet.")

        self.udp_socket.settimeout(timeout)
        response, address = self.udp_socket.recvfrom(GDB_Client.MAX_PACKET_SIZE)

        if (address[0] != GDB_Client.SOCKET_ADDR) or (address[1] != self.udp_client):
            raise GDB_Client_Error('Unexpected Address: ' + str(address))

        # Parse the response
        response = GDB_Client.parse_packet(response)

        if response[0] == GDB_Client.RESPONSE_EXCEPT:
            # Remote exception occurred.  Print out the remote exception
            # information and raise an exception locally to indicate the error.
            # The text for the exception will be the name of the remote
            # exception raised.
            response = response[2].split('|', 1)
            print(response[1])
            raise RemoteError(response[0])

        return response

    def execute(self, command, timeout=None):
        '''
        Executes a command on the GDB Client.

        Parameters:
            command: string representation of the command to execute on the GDB
                     client. This will be passed into exec().
            timeout: Time in seconds for the operation to complete. This can be
                     used to set a longer timeout if the operation is expected
                     to take time to complete.
        '''
        # Send the command
        response = self.send_command(GDB_Client.COMMAND_EXEC, command, timeout)

        # Verify the response
        if (response[0] != GDB_Client.RESPONSE_SUCCESS) or (response[2] != ''):
            raise GDB_Client_Error('Unexpected execute response: "{}"'.format(response))

    def evaluate(self, command, timeout=None):
        '''
        Evaluates a command on the GDB Client.

        Parameters:
            command: string representation of the command to execute on the GDB
                     client. This will be passed into eval().
            timeout: Time in seconds for the operation to complete. This can be
                     used to set a longer timeout if the operation is expected
                     to take time to complete.

        Returns:
            The result of the evaluation
        '''
        # Send the command
        response = self.send_command(GDB_Client.COMMAND_EVAL, command, timeout)

        # Verify the response
        if (response[0] != GDB_Client.RESPONSE_RESULT):
            raise GDB_Client_Error('Unexpected evaluate response: "{}"'.format(response))

        # Evaluate and return the response
        return eval(response[2])


def main():
    '''
    Main entry point for the script when called by the GDB client.
    '''
    print('Python ' + sys.version)

    # get the data from the environment variables.
    server_port = int(os.environ['GDB_PYTHON_SOCKET_PORT'])
    randnum = int(os.environ['GDB_PYTHON_RANDNUM'])

    # Create the sockets
    tool_socket = socket.socket(GDB_Client.SOCKET_FAMILY, socket.SOCK_DGRAM, socket.IPPROTO_UDP)
    try:
        tool_socket.settimeout(5)

        # Connect the socket and get the local port number
        tool_socket.connect((GDB_Client.SOCKET_ADDR, server_port))
        client_port = tool_socket.getsockname()[1]

        tool_socket.send(GDB_Client.format_packet(GDB_Client.RESPONSE_CONNECT, str(randnum)))

        # initialize the dictionaries for the exec and eval commands.
        client_globals = {}
        client_locals = {}
        exec('', client_globals, client_locals)
        client_globals['gdb'] = gdb

        # Increase the timeout for the receive operations. This will ensure the
        # socket will get closed even if the tool script doesn't clean up
        # correctly.
        tool_socket.settimeout(60)

        # Loop until an EXIT command is received or an exception occurs.
        running = True
        while running:
            command, address = tool_socket.recvfrom(GDB_Client.MAX_PACKET_SIZE)

            if (address[0] != GDB_Client.SOCKET_ADDR) or (address[1] != server_port):
                print('Unexpected server address: {0}. Ignoring command'.format(address))
            else:
                try:
                    com_string = ''
                    command = GDB_Client.parse_packet(command)

                    if command[0] == GDB_Client.COMMAND_EXEC:
                        # Execute the command and respond with success
                        com_string = "exec('{}')".format(command[2])
                        exec(command[2], client_globals, client_locals)
                        response = GDB_Client.RESPONSE_SUCCESS
                        data = ''

                    elif command[0] == GDB_Client.COMMAND_EVAL:
                        # Evaluate the command and turn the response into a string
                        com_string = "eval('{}')".format(command[2])
                        data = str([eval(command[2], client_globals, client_locals)])[1:-1]
                        response = GDB_Client.RESPONSE_RESULT

                    elif command[0] == GDB_Client.COMMAND_EXIT:
                        # Terminate the app
                        running = False
                        response = 'EXIT|0|'
                        data = ''
                    else:
                        # Unexpected command
                        raise GDB_Client_Error('Unexpected Command: ' + str(command))
                except Exception as e:
                    response = GDB_Client.RESPONSE_EXCEPT
                    tb_string = traceback.format_exc()
                    if com_string:
                        tb_string = 'Error: {}\n'.format(com_string) + tb_string
                    data = '{}|{}'.format(repr(e), tb_string)

                if response:
                    # if still running, send the response back to the tool
                    error = 'Error:'
                    tool_socket.send(GDB_Client.format_packet(response, data))
    except:
        # print the exception information as otherwise GDB absorbs it.
        print(traceback.format_exc())
        raise
    finally:
        tool_socket.close()

if __name__ == "__main__":
    main()

