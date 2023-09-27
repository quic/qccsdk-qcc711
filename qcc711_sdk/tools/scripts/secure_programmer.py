# ===============================================================================
# Copyright (c) 2020-2021 Qualcomm Technologies, Inc.
# All Rights Reserved.
# Confidential and Proprietary - Qualcomm Technologies, Inc.
# ===============================================================================
# coding=utf-8
from nvm_programmer import NVM_Programmer
import os
import sys
import struct
import serial
import binascii
import logging

# All kinds of messages to be communicated with APSS.
MSG_TYPE = {
    'MSG_ACK': 0,
    'MSG_HELLO': 1,
    'MSG_VERIFY': 2,
    'MSG_APPLY': 3,
    'MSG_MISCTRL': 4,
    'MSG_SEND_HEADER': 5,
    'MSG_SEND_BLOCK': 6,
    'MSG_SEND_TAG': 7,
}


MSG_ACK = {
    0: 'MSG_ACK_OK',
    1: 'MSG_ACK_ERROR_MSG_NULL',
    2: 'MSG_ACK_ERROR_CRC',
    3: 'MSG_ACK_ERROR_MAGIC',
    4: 'MSG_ACK_ERROR_RCV_HEADER_NO_MEMORY',
    5: 'MSG_ACK_ERROR_RCV_HEADER_DERIVE_KEY',
    6: 'MSG_ACK_ERROR_RCV_HEADER_NVM_WRITE',
    7: 'MSG_ACK_ERROR_RCV_TAG_DECRYPTION',
    8: 'MSG_ACK_ERROR_RCV_TAG_NVM_WRITE',
    9: 'MSG_ACK_ERROR_RCV_TAG_CLEAR_KEY',
    10: 'MSG_ACK_ERROR_RCV_TAG_NVM_RELEASE',
    11: 'MSG_ACK_ERROR_VERIFY_UPDATE',
    12: 'MSG_ACK_ERROR_VERIFY_BASE',
    13: 'MSG_ACK_ERROR_VERIFY_AUTH_FAILURE',
    14: 'MSG_ACK_ERROR_VERIFY_INVALID_INPUT',
    15: 'MSG_ACK_ERROR_VERIFY_IMAGE_OVERLAP',
    16: 'MSG_ACK_ERROR_APPLY',
}


class SecureProgrammerUartTimeout(Exception):
    """
    UART Data timeout error, does not receive required size data over a period of time.
    """
    pass

class SecureImageFile(object):
    """
    Class representing the Secure Image File.
    """

    def __init__(self, file_name):
        """
        Initializer for a Secure Image File object.

        Parameters:
            file_name:     Path for Secure Image File.
        """
        with open(file_name, 'rb') as f:
            data = f.read()

        # Parse header of Secure Image File
        self.parse_header(data, os.path.getsize(file_name))

        # Parse body of Secure Image File
        self.parse_body(data)

    def parse_header(self, data, file_size):
        """
        Parse header of Secure Image File.

        Parameters:
            data:      Secure Image File content
            file_size: File size of Secure Image File.
        """
        self.header_len = struct.unpack('<H', data[:2])[0]
        self.version = struct.unpack('<B', data[2:3])[0]
        self.data_len = struct.unpack('<I', data[3:7])[0]
        self.block_len = struct.unpack('<H', data[7:9])[0]
        self.algo = struct.unpack('<B', data[9:10])[0]
        self.tag_len = struct.unpack('<B', data[10:11])[0]
        self.iv_len = struct.unpack('<B', data[11:12])[0]
        self.iv_blob = data[12:24]
        self.key_type = struct.unpack('<B', data[24:25])[0]
        if self.header_len + self.data_len != file_size:
            raise Exception('Invalid Secure image file size: {}'.format(file_size))

        if self.key_type == 0:
            # if self.header_len != 73:
            #     raise ValueError('Wrong header len {} with key type {}'.format(self.header_len, self.key_type))
            self.nonce = data[25:57]
            self.label = data[57:89]
        elif self.key_type == 1:
            # if self.header_len != 29:
            #     raise ValueError('Wrong header len {} with key type {}'.format(self.header_len, self.key_type))
            self.keyid = struct.unpack('<I', data[25:29])[0]
        else:
            raise ValueError('Wrong key type {}'.format(self.key_type))

        # No need include 'header_len' and 'version'
        self.header_data = data[3:self.header_len]

    def parse_body(self, data):
        """
        Parse body of Secure Image File.

        Parameters:
            data: Secure Image File content

        Returns:
            A list containing all blocks & tags.
        """
        body = []
        body_data = data[self.header_len:]
        block_len = self.block_len
        tag_len = self.tag_len
        block_tag_len = block_len + tag_len

        block_tag_list = [body_data[offs:offs + block_tag_len] for offs in range(0, len(body_data), block_tag_len)]
        for block_tag in block_tag_list:
            block = {'type': MSG_TYPE['MSG_SEND_BLOCK'],
                     'data': block_tag[:len(block_tag) - tag_len],
                     'len': len(block_tag) - tag_len}
            body.append(block)

            tag = {'type': MSG_TYPE['MSG_SEND_TAG'],
                   'data': block_tag[-tag_len:],
                   'len': tag_len}
            body.append(tag)

        self.body = body


class NVM_Uart(object):
    """
    Class representing the NVM Uart Tool.
    """

    MAGIC_HEADER = b'QCOM'
    len_magic_header = len(MAGIC_HEADER)
    len_type = 2
    len_length = 2
    len_checksum = 2

    OK = 0
    ERROR = 1
    log_buf = []

    def __init__(self, config):
        """
        Initializer for a NVM Uart Tool object.

        Parameters:
            config:     Config from argparse.
        """
        self.uart = None
        self.resend_count = 0
        self.last_msg = None
        self.config = config
        self.secure_image = SecureImageFile(self.config['secure_image'])

        log_level = getattr(logging, self.config['log'])
        logging.basicConfig(level=log_level, format='%(message)s')

    def setup(self):
        """
        Setup the UART connection.
        """
        self.uart = serial.Serial(port=self.config['uart_port'], baudrate=self.config['baudrate'], timeout=60, write_timeout=5, rtscts=0)

    def cleanup(self):
        """
        Cleanup the UART connection.
        """
        if self.uart:
            self.uart.close()

    def send(self, buf):
        """
        Send buffer through UART.

        Parameters:
            buf: The buffer to send.
        """
        self.uart.write(buf)

    def receive(self, size):
        """
        Receive specific size data from UART.
        If there is not enough size read, this means a timeout occurs.

        Parameters:
            size: The size of data to receive.

        Returns:
            List of bytes that were received.
       """
        buf = self.uart.read(size)
        if len(buf) != size:
            if len(self.log_buf) > 0:
                logging.debug('Wrong content in log_buf: {}'.format(' '.join(map(lambda x: binascii.b2a_hex(x), self.log_buf))))
                self.log_buf = []
            raise SecureProgrammerUartTimeout('Receive timeout.')
        return buf

    def get_msg_type_str(self, msg_type):
        return list(MSG_TYPE.keys())[list(MSG_TYPE.values()).index(msg_type)]

    @staticmethod
    def crc16_ccitt(data):
        """
        Calculate the CRC-16 CCITT FALSE value of the giving data.

        Parameters:
            data: The hex string to calculate CRC-16 CCITT FALSE value.

        Returns:
            The CRC-16 CCITT FALSE value in hex string.
        """
        crc16 = binascii.crc_hqx(data, 0xFFFF)
        return struct.pack('<H', crc16)

    def verify_checksum(self, msg):
        """
        Verify whether the checksum is correct

        Parameters:
            msg: The whole message content, last 2 bytes is checksum.
        """
        checksum = msg[-self.len_checksum:]
        msg = msg[:-self.len_checksum]
        return NVM_Uart.crc16_ccitt(msg) == checksum

    @staticmethod
    def format_msg_head(msg_type, body_len):
        """
        Generates a message head to send through UART.

        Parameters:
            msg_type: The type of message.
            body_len: The length of message body

        Returns:
            An encoded message head.
        """
        return NVM_Uart.MAGIC_HEADER + struct.pack('<H', msg_type) + struct.pack('<H', body_len)

    def send_msg(self, msg_type):
        """
        Send message through UART.

        Parameters:
            msg_type: The type of message.
        """
        msg = NVM_Uart.format_msg_head(msg_type, self.len_checksum)
        msg += NVM_Uart.crc16_ccitt(msg)
        self.send(msg)
        self.last_msg = msg
        logging.debug('Send {}'.format(self.get_msg_type_str(struct.unpack('<H', msg[4:6])[0])))

    def recv_msg(self):
        """
        Read message from UART.

        Returns:
            The message type & body read from UART.
        """

        # Continue receiving until 'QCOM'
        msg_head = b''
        while True:
            msg_head += self.receive(1)
            pos = msg_head.find(self.MAGIC_HEADER)
            if pos == -1:
                self.log_buf = msg_head
            else:
                self.log_buf = msg_head[:pos]
                msg_head = msg_head[pos:]
                break

        if len(self.log_buf) > 0:
            logging.debug('Warning, wrong content before msg head: {}'.format(' '.join(map(lambda x: binascii.b2a_hex(x), self.log_buf))))
            self.log_buf = []

        msg_head += self.receive(self.len_type + self.len_length)
        if msg_head[:self.len_magic_header] != self.MAGIC_HEADER:
            logging.debug(' '.join(map(lambda x: binascii.b2a_hex(x), msg_head)))
            raise Exception('Wrong magic header.')

        msg_type = struct.unpack('<H', msg_head[self.len_magic_header:self.len_magic_header + self.len_type])[0]
        msg_len = struct.unpack('<H', msg_head[self.len_magic_header + self.len_type:self.len_magic_header + self.len_type + self.len_length])[0]
        msg_body = self.receive(msg_len)
        logging.debug('Recv {}'.format(self.get_msg_type_str(msg_type)))

        if not self.verify_checksum(msg_head + msg_body):
            raise Exception('CRC check error.')
        return msg_type, msg_body[:-self.len_checksum]

    def waiting_for_msg_ack_ok(self):
        """
        Continue reading message from UART until MSG_ACK OK read.
        """
        while True:
            msg_type, msg_body = self.recv_msg()
            if msg_type != MSG_TYPE['MSG_ACK']:
                raise Exception('Wrong msg received {}.'.format(msg_type))

            code = struct.unpack('<B', msg_body)[0]
            if code == self.OK:
                return
            else:
                raise Exception('Wrong MSG_ACK code {}.'.format(MSG_ACK[code]))

    def send_msg_misctrl(self):
        """
        Send misctrl through UART.
        """
        msg = NVM_Uart.format_msg_head(MSG_TYPE['MSG_MISCTRL'], self.len_magic_header + self.len_type + self.len_length + self.len_checksum)
        msg += struct.pack('<I', self.config['address'])
        msg += struct.pack('<I', 0)
        msg += NVM_Uart.crc16_ccitt(msg)
        self.send(msg)
        self.last_msg = msg
        logging.debug('Send MSG_MISCTRL')

    def send_msg_image_header(self):
        """
        Send image header through UART.
        """
        msg = NVM_Uart.format_msg_head(MSG_TYPE['MSG_SEND_HEADER'], self.secure_image.header_len + self.len_checksum)
        msg += self.secure_image.header_data
        msg += NVM_Uart.crc16_ccitt(msg)
        self.send(msg)
        self.last_msg = msg
        logging.debug('Send MSG_SEND_HEADER')

    def send_msg_image_body(self, block):
        """
        Send image block/tag through UART.

        Parameters:
            block: The image body BLOCK/TAG to send.
       """
        msg_type = block['type']
        msg = NVM_Uart.format_msg_head(msg_type, block['len'] + self.len_checksum)
        msg += block['data']
        msg += NVM_Uart.crc16_ccitt(msg)
        self.send(msg)
        self.last_msg = msg
        logging.debug('Send {}'.format(self.get_msg_type_str(msg_type)))

    def resend_last_msg(self):
        """
        Resend last message.
        """
        if self.last_msg:
            if self.resend_count < 3:
                self.resend_count += 1
                self.send(self.last_msg)
                logging.debug('Resend {}'.format(self.get_msg_type_str(struct.unpack('<H', self.last_msg[4:6])[0])))
            else:
                raise Exception('Resend too many times.')

    def run(self):
        """
        Start tool.
        """
        print('Sending encrypted update package: {}'.format(self.config['secure_image']))
        try:
            self.setup()

            # Send handshake
            msg_type, msg_body = self.recv_msg()
            if msg_type == MSG_TYPE['MSG_HELLO']:
                self.send_msg(MSG_TYPE['MSG_HELLO'])
            else:
                raise Exception('Handshake is not complete.')
            self.waiting_for_msg_ack_ok()

            # Send image misctrl
            self.send_msg_misctrl()
            self.waiting_for_msg_ack_ok()

            # Send image header
            self.send_msg_image_header()
            self.waiting_for_msg_ack_ok()

            # Send image body
            for block in self.secure_image.body:
                self.send_msg_image_body(block)
                self.waiting_for_msg_ack_ok()

            # Send verify
            self.send_msg(MSG_TYPE['MSG_VERIFY'])
            self.waiting_for_msg_ack_ok()

            # Send apply
            self.send_msg(MSG_TYPE['MSG_APPLY'])
            print('Status:Success\n')
        except BaseException:
            print('Status:Failed\n')
            raise
        finally:
            self.cleanup()


class SecureProgrammer(NVM_Programmer):
    """
    Class representing the NVM Secure Programming Tool.
    """

    ADDRESS_TO_WRITE_LOADER_DEMO_IMAGE = 0x10240000

    def __init__(self):
        """
        Initializes the Secure Programmer Tool.
        """

        self.ToolDescription = 'NVM Secure Program tool'
        super(SecureProgrammer, self).__init__()

    def add_arguments(self):
        """
        Add tool specific arguments.
        """
        # Secure programmer tool specific arguments
        self.argparser.add_argument(dest='input', help='File to program.')
        self.argparser.add_argument('-i', '--ram-image', default=NVM_Programmer.DEFAULT_RAM_IMAGE, help='Path for RAM image.')

        # NVM UART tool specific arguments
        self.argparser.add_argument('secure_image', type=str, help='Path for Secure Image File')
        self.argparser.add_argument('uart_port', type=str, help='UART port for traffic to APSS')
        self.argparser.add_argument('-B', '--baudrate', type=int, default=115200, help='Baudrate')
        self.argparser.add_argument('-a', '--address', type=lambda x: int(x, 0), default=0x10248000, help='Address to write secure image')
        self.argparser.add_argument('-L', '--lock-debug', default=False, action='store_true', help='Lock debug mode')
        self.argparser.add_argument('--recover', default=False, action='store_true', help='Recover from a partial update. this skips downloading the secure loader.')
        self.argparser.add_argument('--log', default='INFO', choices=['INFO', 'DEBUG'], help='log level')

    def run(self):
        """
        Start tool.
        """
        # Perform common tool setup
        self.setup()

        try:
            # *** Tool specific code ***
            self.init_ram_image(self.config['ram_image'])

            try:
                self.download(self.config['input'], True, self.ADDRESS_TO_WRITE_LOADER_DEMO_IMAGE)
                self.apply_update(self.config['input'],  self.ADDRESS_TO_WRITE_LOADER_DEMO_IMAGE, self.config['lock_debug'])
            except:
                self.cleanup_ram_image()
                raise
            # *** End tool specific code ***
        except:
            raise
        finally:
            self.cleanup()

def main():
    """
    Main entry point for the tool script.
    """
    print('\n\n********************************************************************************')
    print('********************* Launching NVM Secure Programming *************************')
    print('********************************************************************************')
    secure_programmer_tool = SecureProgrammer()
    if not '--recover' in sys.argv:
        secure_programmer_tool.run()

    nvm_uart_tool = NVM_Uart(secure_programmer_tool.config)
    nvm_uart_tool.run()


if __name__ == "__main__":
    main()
