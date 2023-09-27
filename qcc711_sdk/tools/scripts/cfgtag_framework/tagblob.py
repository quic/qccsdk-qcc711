################################################################################
# Support classes / functions / imports for tagblob_*.py
################################################################################
# Copyright (c) 2021 Qualcomm Technologies International, Ltd.
# All Rights Reserved
# Confidential and Proprietary - Qualcomm Technologies International, Ltd.
################################################################################

import os

from xml_wrapper import ET
from tags import NvmTags

# Optional support for hexfile.py if it is provided
try:
    import hexfile
except ImportError:
    hexfile = None


try:
    # Python 2
    from StringIO import StringIO
except ImportError:
    # Python 3
    from io import StringIO


# The underlying code has an ingrained dependency to a global located within config.py...
# This needs to be faked out here in order to allow the other code to run (but should be refactored eventually)
import config

class DummyOptions(object): pass
config.options = DummyOptions()
config.options.debug = False
config.options.strict = False
config.options.verbose = False


# Superclass for supported file formats
class NvmDataFile(object):
    
    def __init__(self, filename):
        self.filename = filename
        pass

    @classmethod
    def load_from(cls, *args, **kwargs): 
        instance = cls(*args, **kwargs)
        instance.load()
        return instance

    def load(self):
        raise NotImplementedError()

    def save(self):
        raise NotImplementedError()

    def patch_data(self, data, offset):
        raise NotImplementedError()

    def get_data(self, offset, len):
        raise NotImplementedError()


class BinaryFile(NvmDataFile):
    
    def __init__(self, filename):
        super(BinaryFile, self).__init__(filename)
        self._data = []

    def load(self):
        with open(self.filename, 'rb') as f:
            # Python 2 doesn't treat file reads as bytes() objects,
            # so we wrap the whole thing in a bytearray for compatibility with both 2 and 3
            self._data = bytearray(f.read())

    def save(self):
        with open(self.filename, 'wb') as f:
            f.write(self._data)

    def patch_data(self, data, offset):
        # Ensure this doesn't exceed our max size.
        if len(data) + offset > len(self._data):
            raise IndexError('Patch data is out-of-bounds.')

        len_prev = len(self._data)
        self._data[offset:offset+len(data)] = data

        assert len_prev == len(self._data) # Sanity check

    def get_data(self, offset, length):
        return list(self._data[offset:offset+length])


# This class is more-or-less a wrapper for the underlying hexfile.HexFile implementation
class IHexFile(NvmDataFile):
    
    def __init__(self, filename, base_addr):
        super(IHexFile, self).__init__(filename)
        self._hf = None
        self._baseaddr = base_addr

    def load(self):
        self._hf = hexfile.HexFile(self.filename)

    def save(self):
        self._hf.write_hex(self.filename)

    def patch_data(self, data, offset):
        self._hf.modify(self._baseaddr + offset, data)

    def get_data(self, offset, length):
        return list(self._hf.get(self._baseaddr + offset, length))


def load_tcfx(filename):

    mandatoryTCFXElements = ['FORMAT_VERSION', 'TAG_GROUPS', 'PLATFORMS', 'TAGS']

    if not os.path.isfile(filename):
        raise RuntimeError('Cannot open file: {}'.format(filename))

    # Read the entire TCFX contents into memory
    tcfxTree = ET.parse(filename)
    tcfx = tcfxTree.getroot()

    # Some basic validation - we expect a certain set of top-level sections to exist
    if tcfx.tag != 'TCF':
        raise RuntimeError('Malformed TCFX: root element is not <TCF>')

    rootChildren = [C.tag for C in list(tcfx)]
    for section in mandatoryTCFXElements:
        if section not in rootChildren:
            raise RuntimeError('Malformed TCFX: <TCF> doesn\'t contain {} element'.format(section))

    # Load the NVM tag data from the TCFX tree
    nvmTags = NvmTags()
    nvmTags.loadTCFX(tcfx)

    return nvmTags


# Converts a tag object loaded from a TCFX into a binary value representation.
def tcfx_tag_to_binary(tag):
    sio = StringIO()
    tag.typeInfo.saveNVM(sio)

    # Extract tag data (it is in a .nvm hex string format)
    sio.seek(0)
    nvm_str = sio.read()
    data = [int(x, 16) for x in nvm_str.split()]

    return data


if __name__ == '__main__':
    raise RuntimeError('tagblob.py is meant to be imported and not run')
