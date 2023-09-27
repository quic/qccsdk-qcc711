################################################################################
# Bitfield tag type processing
################################################################################
# Copyright (c) 2018-2021 Qualcomm Technologies International, Ltd.
# All Rights Reserved
# Confidential and Proprietary - Qualcomm Technologies International, Ltd.
################################################################################


################################################################################
# Library Imports
################################################################################
from __future__ import print_function
try:
    from builtins import str
except ImportError:
    pass
import re
from codegen import CodeGen
import config
from config import BasicType, TagTypeInfo, TagError
from tag_descriptor import TagDescriptor
from hydra_db import SdbDescriptor
from codegen import HtfWriteLine
import tag_filter
import tag_descriptor
from xml_wrapper import ET


################################################################################
# Global Variables
################################################################################


################################################################################
# Local Functions
################################################################################


################################################################################
# Class describing a single enumerated value
################################################################################
class TagTypeBitVal(TagDescriptor):
    def __init__(self, typeInfo, parent, name="", startBit=0, endBit=0):
        TagDescriptor.__init__(self)
        
        self.name = name
        self.type = typeInfo
        self.desc = ""
        self.isBitfield = 0
        self.startBit = startBit
        self.endBit = endBit
        self.default = 0
        self.original = []
        self.parent = parent


    ############################################################################
    # Member-level equality check
    ############################################################################
    def __eq__(self, other):
        # Trivial equality test first, are they the same instance?
        if self is other:
            return True

        # Are they the same class?
        if not isinstance(other, TagTypeBitVal):
            return False

        # They are the same if the name and bitfields are identical.
        return self.name == other.name and self.isBitfield == other.isBitfield and self.startBit == other.startBit and self.endBit == other.endBit

    def __ne__(self, other):
        return not self.__eq__(other)


    ############################################################################
    # Get a database descriptor for this type
    ############################################################################
    def getSdbDescriptor(self):
        # Each bit value is treated similar to a structure element, albeit one
        # that is very narrow (or possibly only one bit wide). That means every
        # bit value gets its own entry in the config_elements table
        d = SdbDescriptor()
        self.addHashInfo(d)

        return d

    ############################################################################
    # Add tag information to be used for MD5 calculation
    ############################################################################  
    def addHashInfo(self, d):
        
        d.addCommonFields(self.name, self.name, self.type.getTypeString())
        d.addDescription(self.desc)

        # Set the range_min and range_max parameters to the range of values
        # (starting at 0) that can be stored within the number of bits available
        # to this bitfield. E.g. if startBit=2 and endBit=4, there are 3 bits
        # in total, so the range would be 0 to 7.
        d.addRange(0, (2 << (self.endBit-self.startBit)) - 1)


    ############################################################################
    # Generate an integer bitmask for the given start and end bits
    ############################################################################
    def getBitMask(self):
        bitmask = (1 << (self.endBit+1)) - 1
        if self.startBit > 0:
            antimask = ~((1 << self.startBit) - 1)
            bitmask &= antimask
        return bitmask



    ############################################################################
    # Load enum value from the RAM copy of the TCF file
    ############################################################################
    def loadTCF(self, tcf, sectionName):
        self.name = tcf.get(sectionName, "Name")
        self.desc = tcf.get(sectionName, "Desc")
        self.isBitfield = int(tcf.get(sectionName, "BitsOrField"))
        self.startBit = int(tcf.get(sectionName, "BitFrom"))
        if self.isBitfield:
            self.endBit = int(tcf.get(sectionName, "BitEnd"))
        else:
            self.endBit = self.startBit
        self.default = int(tcf.get(sectionName, "BitsDefault"))

        if self.endBit < self.startBit:
            if config.options.strict:
                raise TagError("%s: invalid bitfield, end %d cannot be less than start %d" % (sectionName, self.endBit, self.startBit))
            else:
                # Warn the user and fix the internal representation
                print("%s: invalid bitfield, end %d cannot be less than start %d" % (sectionName, self.endBit, self.startBit))
                tmp = self.startBit
                self.startBit = self.endBit
                self.endBit = tmp

        if self.isBitfield and self.endBit == self.startBit:
            if config.options.strict:
                raise TagError("%s: bitfield specified with only a single bit" % sectionName)
            else:
                # Warn the user and fix the internal representation
                print("%s: bitfield specified with only a single bit" % sectionName)
                self.isBitfield = 0


    ############################################################################
    # Save bit value to a TCF file
    ############################################################################
    def saveTCF(self, tcf, sectionName):
        tcf.write("[%s]\n" % sectionName)
        tcf.write("Name = %s\n" % self.name)
        tcf.write("Desc = %s\n" % self.desc)
        tcf.write("BitsOrField = %d\n" % self.isBitfield)
        tcf.write("BitFrom = %d\n" % self.startBit)
        tcf.write("BitEnd = %d\n" % self.endBit)
        tcf.write("BitsDefault = %d\n" % self.default)
        tcf.write("\n")


    ############################################################################
    # Load bit value from an XML tree
    ############################################################################
    def loadXML(self, bitElem):
        self.name = bitElem.get("name")
        if bitElem.text is not None:
            self.desc = bitElem.text
        else:
            self.desc = ""
        self.startBit = int(bitElem.get("start"))
        self.endBit = int(bitElem.get("end"))
        if self.startBit != self.endBit:
            self.isBitfield = 1
        else:
            self.isBitfield = 0

        self.default = int(bitElem.get("default"))

        if self.endBit < self.startBit:
            raise TagError("%s: invalid bitfield, end %d cannot be less than start %d" % (self.name, self.endBit, self.startBit))

    ############################################################################
    # Load bit value from an TCFX tree
    ############################################################################
    def loadTCFX(self, bitElem):
        self.name = bitElem.get("Name")
        self.desc = bitElem.get("Description").strip()

        if bitElem.get("Size") is not None or bitElem.get("Type") is not None:
            raise TagError("\n\nOlder version of TCFX is being used, BITFIELD elements are not supposed to have Size / Type.\nPlease move to latest CTM release to edit the TCFX file.\n\n")
        
        self.startBit = int(bitElem.get("Start"))
        self.endBit = int(bitElem.get("End"))
        if self.startBit != self.endBit:
            self.isBitfield = 1
        else:
            self.isBitfield = 0

        self.default = config.ToInt(bitElem.get("Default"), self.type.size, self.type.isSigned())

        if self.endBit < self.startBit:
            raise TagError("%s: invalid bitfield, end %d cannot be less than start %d" % (self.name, self.endBit, self.startBit))
            
            
    ############################################################################
    # Merge BIT values from an .nvmx file
    ############################################################################
    def mergeNVMX(self, bitElem):
        if self.name != bitElem.get("Name") and config.options.alignToTCFX:
            return
            
        val = bitElem.get("Value")
        
        if not val:
            raise TagError("%s : invalid Value" %(self.name))
            
        self.default = config.ToInt(val, self.type.size, self.type.isSigned())
        
    ############################################################################
    # Save bit value to an XML tree
    ############################################################################
    def saveXML(self, bitsElem):
        # isBitfield is implicit in having more than one bit so we only need to
        # store start and end bits in the XML
        bitElem = ET.SubElement(bitsElem, "BIT")
        bitElem.set("name", str(self.name))
        bitElem.set("start", str(self.startBit))
        bitElem.set("end", str(self.endBit))
        bitElem.set("default", str(self.default))
        bitElem.text = self.desc

    ############################################################################
    # Save bit value to an TCFX tree
    ############################################################################
    def saveTCFX(self, bitsElem):
        # isBitfield is implicit in having more than one bit so we only need to
        # store start and end bits in the XML
        bitElem = ET.SubElement(bitsElem, "ELEMENTS")
        bitElem.set("Name", str(self.name))
        bitElem.set("Default", config.ToHex(self.default, self.type.size))
        bitElem.set("Start", str(self.startBit))
        bitElem.set("End", str(self.endBit))
        bitElem.set("Description", self.desc)
        
    ############################################################################
    # Save bit value to an NVMX tree
    ############################################################################
    def saveNVMX(self, bitsElem):
        # isBitfield is implicit in having more than one bit so we only need to
        # store start and end bits in the XML
        bitElem = ET.SubElement(bitsElem, "ELEMENTS")
        bitElem.set("Name", str(self.name))
        bitElem.set("Value", config.ToHex(self.default, 1))
        
    ############################################################################
    # Save Tag Type to the system configuration database
    ############################################################################
    def saveSDB(self, sdb):
        # Get the type descriptor then save to the database (or retrieve UID if already present)
        d = self.getSdbDescriptor()
        elemUid = d.saveSDB(sdb)

        # Cross-reference the config_element for this type to the FW release
        sdb.xrefElement(elemUid)

        return elemUid, None


    ############################################################################
    # Get the ROM default value for this type, for inserting into the SDB
    ############################################################################
    def getSdbDefault(self, tag):
        # Just return the bit value default value
        return [self.default]
        

################################################################################
# Class describing a bitfield Tag Type
################################################################################
class TagTypeBits(TagDescriptor):
    def __init__(self, parent):
        TagDescriptor.__init__(self)
        
        self.name = ""
        self.type = BasicType()
        self.bits = []
        self.default = 0
        self.original = []
        self.highestBit = 0
        self.parent = parent
        self.vListObj = None
        self.wrappingType = TagTypeInfo.BITFIELD


    ############################################################################
    # Member-level equality check
    ############################################################################
    def __eq__(self, other):
        # Trivial equality test first, are they the same instance?
        if self is other:
            return True

        # Are they the same class?
        if not isinstance(other, TagTypeBits):
            return False

        # They are the same if the name and bitfields are identical.
        if self.name != other.name or len(self.bits) != len(other.bits) or self.type.dataType != other.type.dataType:
            return False

        for i in range(len(self.bits)):
            if self.bits[i] != other.bits[i]:
                return False

        return True

    def __ne__(self, other):
        return not self.__eq__(other)


    ############################################################################
    # Sort the list of bits into ascending bit order. This is not needed (or
    # desired) in every case, but can be used to ensure a consistent ordering
    # for some output formats.
    ############################################################################
    def sortBits(self):
        self.bits = sorted(self.bits, key=lambda bit: bit.startBit)


    ############################################################################
    # Search for any explicitly-defined reservedNN fields in the bitmask and
    # determine what the next-highest value would be. This is then used when
    # adding more reserved fields at the end during SDB generation.
    ############################################################################
    def nextReserved(self):
        lowestRsv = -1
        for bitVal in self.bits:
            m = re.match("^reserved([0-9]+)$", bitVal.name, re.IGNORECASE)
            if m:
                val = int(m.group(1))
                if lowestRsv < val:
                    lowestRsv = val

        return lowestRsv + 1


    ############################################################################
    # For Hydra database processing the bitfield definition can't have any gaps
    # in the range of bits defined, across the entire integer size of the word.
    # So rebuild the "bits" list inserting extra pad bits as required to ensure
    # the struct is correctly aligned.
    ############################################################################
    def getPaddedBits(self):
        # Sort the bits before starting to ensure consistent output
        self.sortBits()

        lastBit = -1
        reservedCount = self.nextReserved()
        paddedBits = []
        for bitVal in self.bits:
            # Check if we need to insert any padding fields before this bit
            for resBit in range(lastBit+1, bitVal.startBit):
                # Create an individual padding bit value
                padBit = TagTypeBitVal(self.type, self, name="reserved%d" % reservedCount, startBit=resBit, endBit=resBit)
                paddedBits.append(padBit)
                reservedCount += 1
            paddedBits.append(bitVal)
            lastBit = bitVal.endBit
        
        # Now add final padding fields to cover the extent of the underlying type
        for resBit in range(lastBit+1, self.highestBit+1):
            # Create an individual padding bit value
            padBit = TagTypeBitVal(self.type, self, name="reserved%d" % reservedCount, startBit=resBit, endBit=resBit)
            paddedBits.append(padBit)
            reservedCount += 1

        return paddedBits


    ############################################################################
    # Return the top-level tag object that owns this type
    ############################################################################
    def getTag(self):
        return self.parent.getTag()


    ############################################################################
    # Get a database descriptor for this type
    ############################################################################
    def getSdbDescriptor(self, tag, forHash=False):
        
        d = SdbDescriptor()
        
        if forHash:
            self.addHashInfo(d, tag)
            
        else:
            if tag is not None:
                name = tag.name
            else:
                name = self.name
            if self.vListObj:
                tagName = self.vListObj.tagName
            else:
                tagName = name
            d.addCommonFields(name, tagName, self.getTypeString())
            if tag:
                d.addDescription(tag.desc)
                
            if self.vListObj:
                d.addTagData(self.vListObj.tagId, False)

        return d


    ############################################################################
    # Add tag information to be used for MD5 calculation
    ############################################################################  
    def addHashInfo(self, d, tag):
        if tag is not None:
            name = tag.name
        else:
            name = self.name
        d.addCommonFields(name, self.name, self.getTypeString())
            
        # Add dummy description and overwrite it with all bitfields
        d.addDescription(name)

        if self.isVtagPublished:
            # VTag has been found in filter list. Read info 
            d.addTagData(self.getVtagNumber(), False)
        
        descr = "bitfield:\n"

        # The bitfield hash is dependent on the descriptor for each bit value
        for bitVal in self.bits:
            bitVal.addHashInfo(bitVal)
            descr += bitVal.values[bitVal.names.index("name")] + ": "
            descr += bitVal.values[bitVal.names.index("description_user")] + "\n"
            d.extend( bitVal )
        # Replace the dummy description which will always be on the first
        # occurrence of description_user
        d.values[d.names.index("description_user")] = descr


    ############################################################################
    # Get the type name as a string
    ############################################################################
    def getTypeString(self, lowercase=True, baseNameOnly=False, prefixParent=False):
        return super(TagTypeBits, self).getTypeString(lowercase=lowercase, baseNameOnly=baseNameOnly, prefixParent=True)


    ############################################################################
    # Load bitfield definition from the RAM copy of the TCF file
    ############################################################################
    def loadTCF(self, tcf, sectionName):
        sectionName += "%d" % TagTypeInfo.BITFIELD
        self.name = tcf.get(sectionName, "Name")
        self.type.size = int(tcf.get(sectionName, "TagLength"))
        self.type.evalType()
        self.default = int(tcf.get(sectionName, "TagTypeValueDefault"))
        self.type.value = self.default

        sectionName += "_Data"
        combinedDefault = 0
        for i in range(int(tcf.get(sectionName, "Num"))):
            bitVal = TagTypeBitVal(self.type, self)
            bitVal.loadTCF(tcf, sectionName+"_%d" % i)
            self.bits.append(bitVal)

            combinedDefault |= (bitVal.default << bitVal.startBit)

            if self.highestBit < bitVal.endBit:
                self.highestBit = bitVal.endBit

        # Ensure no defined bitfield overflows the integer type size
        if self.highestBit > (self.type.size*8)-1:
            raise TagError("%s: Highest bit %d overflows integer size %d" % (sectionName, self.highestBit, self.type.size))

        # Allow overall tag length to override max bits currently defined
        if self.highestBit < (self.type.size*8)-1:
            self.highestBit = (self.type.size*8)-1

        # Check that the bitwise OR of individual bit defaults matches the top-level
        # default for the type
        if combinedDefault != self.default:
            raise TagError("%s: Combined default 0x%x doesn't match type default 0x%x" % (sectionName, combinedDefault, self.default))

        if self.type.signed:
            raise TagError("%s: Bitmasks must always be unsigned" % sectionName)
        
        # Don't allow overlapping bit ranges
        bitsDefined = 0
        for bitVal in self.bits:
            b = bitVal.getBitMask()
            if bitsDefined & b:
                raise TagError("%s: overlapping bit range found in %s" % (sectionName, bitVal.name))
            bitsDefined |= b


    ############################################################################
    # Save bitfield to a TCF file
    ############################################################################
    def saveTCF(self, tcf, sectionName):
        sectionName += "%d" % TagTypeInfo.BITFIELD
        tcf.write("[%s]\n" % sectionName)
        tcf.write("Name = %s\n" % self.name)
        tcf.write("TagLength = %d\n" % self.type.size)
        tcf.write("TagTypeValueDefault = %d\n" % self.default)
        tcf.write("\n")

        sectionName += "_Data"
        tcf.write("[%s]\n" % sectionName)
        tcf.write("Num = %d\n" % len(self.bits))
        tcf.write("\n")

        i = 0
        for bitVal in self.bits:
            bitVal.saveTCF(tcf, "%s_%d" % (sectionName, i))
            i += 1


    ############################################################################
    # Save bitfield to an HTF file
    ############################################################################
    def saveHTF(self, htf, indent, elemSuffix=""):
        # Fill in missing bit ranges for Hydra database compatibility.
        paddedBits = self.getPaddedBits()

        # Get associated vtag name for sub-element in a physical tag
        if self.parent is None or self.getTag().isVtag or self.vListObj is None:
            vtagName = ""
        else:
            vtagName = "\t[V] %s" % self.vListObj.tagName

        bitStr = "{ "
        if not config.options.compactHTF:
            bitStr += "  /* %s%s */" % (SdbDescriptor.makeShortName(self.name), vtagName)
        HtfWriteLine(htf, bitStr, indent)

        for bitVal in paddedBits:
            bitStr =  "0x%02x" % (bitVal.default)
            if paddedBits.index(bitVal) != len(paddedBits)-1:
                bitStr += ","
            if not config.options.compactHTF:
                bitStr += "\t/* %s */" % (SdbDescriptor.makeShortName(bitVal.name))

            HtfWriteLine(htf, bitStr, indent+4)

        # Line continuation is not required if current indent is 0, as this means
        # we are the top-level element of the tag
        if config.options.compactHTF:
            htf.write(" ")  # extra space before closing brace in one-line mode
        HtfWriteLine(htf, "}"+elemSuffix, indent, cont=(indent>0))


    ############################################################################
    # Merge tag values from an .nvm file
    ############################################################################
    def mergeNVM(self, tagVal):
        if len(tagVal) < self.type.size:
            raise TagError("Bitfield %s expects %d bytes in NVM file" % (self.name, self.type.size))

        newVal = tagVal[:self.type.size]
        tagVal = tagVal[self.type.size:]

        # Update the default value
        self.original.append(self.default)
        self.default = 0
        shift = 0
        for byte in newVal:
            self.default = self.default | (byte << shift)
            shift += 8

        # And propagate to each of the bitfields
        val = self.default
        for bitVal in self.bits:
            b = bitVal.getBitMask()
            bitVal.default = (val & b) >> bitVal.startBit
            val = val & ~b

        # There shouldn't be any bits left set
        if val:
            raise TagError("Bitfield %s new default sets reserved bits (0x%x)" % (self.name, val))

        return tagVal

    ############################################################################
    # Merge tag values from an .nvmx file
    ############################################################################
    def mergeNVMX(self, nvmxTagType):
        if nvmxTagType.get("Name") != self.name and not config.options.alignToTCFX:
            raise TagError("NVMX Tag is not aligned with the Elements.")
        
        nvmxBITElems = nvmxTagType.findall("ELEMENTS")
        
        if len(nvmxBITElems) != len(self.bits) and not config.options.alignToTCFX:
            raise TagError("NVMX Tag is not aligned with the Elements.")
        
        self.default = 0        
        for nvmxBITElem, bit in zip(nvmxBITElems, self.bits):
            ElementName = nvmxBITElem.get("Name")
            if ElementName != bit.name and not config.options.alignToTCFX:
                raise TagError("NVMX Tag is not aligned with the Elements.")
            bit.mergeNVMX(nvmxBITElem)
            
            self.default |= (bit.default << bit.startBit)
        
            if self.highestBit < bit.endBit:
                self.highestBit = bit.endBit
                
        self.type.value = self.default
        
        # Ensure no defined bitfield overflows the integer type size
        if self.highestBit > (self.type.size*8)-1:
            raise TagError("<BITS>: Highest bit %d overflows integer size %d" % (self.highestBit, self.type.size))

        # Allow overall tag length to override max bits currently defined
        if self.highestBit < (self.type.size*8)-1:
            self.highestBit = (self.type.size*8)-1

    ############################################################################
    # Save bitfield to an NVM file
    ############################################################################
    def saveNVM(self, nvm):
        # Iterate through the default writing the value byte by byte
        default = self.default
        for _ in range(self.type.size):
            nvm.write(" %02X" % (default & 0xFF))
            default >>= 8


    ############################################################################
    # Load bitfield from an XML tree
    ############################################################################
    def loadXML(self, xmlTagType):
        self.name = xmlTagType.get("name")
        self.type.size = int(xmlTagType.get("length"))
        self.type.evalType()

        xmlBitsType = xmlTagType.find("BITS")
        if xmlBitsType is None:
            raise TagError("Malformed XML: BITS type is missing <BITS> child element")

        # Parse the individual <BIT> tags. Note that we don't treat missing <BIT>
        # elements as an error unless --strict processing has been requested.
        # (Empty bitfields were used in the legacy TCF file).
        xmlBitElems = xmlBitsType.findall("BIT")
        if len(xmlBitElems) == 0 and config.options.strict:
            raise TagError("Malformed XML: <BITS> doesn't have any <BIT> child elements")

        self.default = 0
        for xmlBitElem in xmlBitElems:
            bitVal = TagTypeBitVal(self.type, self)
            bitVal.loadXML(xmlBitElem)
            self.bits.append(bitVal)

            self.default |= (bitVal.default << bitVal.startBit)

            if self.highestBit < bitVal.endBit:
                self.highestBit = bitVal.endBit
                
        self.type.value = self.default

        # Ensure no defined bitfield overflows the integer type size
        if self.highestBit > (self.type.size*8)-1:
            raise TagError("<BITS>: Highest bit %d overflows integer size %d" % (self.highestBit, self.type.size))

        # Allow overall tag length to override max bits currently defined
        if self.highestBit < (self.type.size*8)-1:
            self.highestBit = (self.type.size*8)-1

    ############################################################################
    # Load bitfield from an TCFX tree
    ############################################################################
    def loadTCFX(self, tcfxTagType):
        self.name = tcfxTagType.get("Name")
        self.type.size = int(tcfxTagType.get("Size"))
        self.type.evalType()

        if tcfxTagType.get("Type") != "BITFIELD":
            raise TagError("Malformed TCFX: is not of type BITFIELD")

        # Parse the individual <ELEMENTS> tags. Note that we don't treat missing BITS
        # elements as an error unless --strict processing has been requested.
        # (Empty bitfields were used in the legacy TCF file).
        tcfxBitElems = tcfxTagType.findall("ELEMENTS")
        if len(tcfxBitElems) == 0 and config.options.strict:
            raise TagError("Malformed TCFX: <BITS> doesn't have any <BIT> child elements")

        self.default = 0
        for tcfxBitElem in tcfxBitElems:
            bitVal = TagTypeBitVal(self.type, self)
            bitVal.loadTCFX(tcfxBitElem)
            self.bits.append(bitVal)

            self.default |= (bitVal.default << bitVal.startBit)

            if self.highestBit < bitVal.endBit:
                self.highestBit = bitVal.endBit
                
        self.type.value = self.default

        # Ensure no defined bitfield overflows the integer type size
        if self.highestBit > (self.type.size*8)-1:
            raise TagError("<BITS>: Highest bit %d overflows integer size %d" % (self.highestBit, self.type.size))

        # Allow overall tag length to override max bits currently defined
        if self.highestBit < (self.type.size*8)-1:
            self.highestBit = (self.type.size*8)-1
            
    ############################################################################
    # Save bitfield to an XML tree
    ############################################################################
    def saveXML(self, typeElem):
        typeElem = ET.SubElement(typeElem, "TAG_TYPE")
        typeElem.set("type", "BITS")
        typeElem.set("name", self.name)
        typeElem.set("length", str(self.type.size))

        bitsElem = ET.SubElement(typeElem, "BITS")
        for bitVal in self.bits:
            bitVal.saveXML(bitsElem)

    ############################################################################
    # Save bitfield to an TCFX tree
    ############################################################################
    def saveTCFX (self, typeElem):
        typeElem = ET.SubElement(typeElem, "ELEMENTS")
        typeElem.set("Name", self.name)
        typeElem.set("Type", "BITFIELD")
        typeElem.set("Size", str(self.type.size))

        for bitVal in self.bits:
            bitVal.saveTCFX(typeElem)
            
    ############################################################################
    # Save bitfield to an NVMX tree
    ############################################################################
    def saveNVMX (self, typeElem):
        typeElem = ET.SubElement(typeElem, "ELEMENTS")
        typeElem.set("Name", self.name)
        for bitVal in self.bits:
            bitVal.saveNVMX(typeElem)
            
    ############################################################################
    # Save bitfield to the system configuration database
    ############################################################################
    def saveSDB(self, sdb, tag):
        
        # The bits definition is treated as if it were a struct with sub-byte sized elements
        # TBD - currently this is mostly a block copy of the same function in TagTypeStruct - scope to optimise?

        # Calculate the hash for this struct and check if it is already in the DB
        d = self.getSdbDescriptor(tag, forHash=True)
        md5 = d.getHash()
        sdb.sql.execute("SELECT struct_uid FROM struct_defs where hash='%s'" % md5)
        hashed = sdb.sql.fetchall()

        if len(hashed) == 0:
            # add struct definition to database
            sdb.sql.execute("INSERT INTO struct_defs (struct_uid, struct_name, hash) VALUES(NULL, ?, ?)", (self.getTypeString(), md5))
            sdb.sql.execute("SELECT max(struct_uid) FROM struct_defs")
            structUid = (sdb.sql.fetchone())[0]
            
            if config.options.debug:
                print("Added bit: %s" % self.getTypeString())

            sdb.recordStruct(structUid, self.getTypeString(), md5)

            # Fill in missing bit ranges for Hydra database compatibility.
            paddedBits = self.getPaddedBits()

            # Now add struct_element definitions to database for each bit, including padding
            for bitVal in paddedBits:
                # Save the nested structure element first, to get its elemUid.
                # Don't pass the top-level tag element down, so that nested
                # elements have no tag ID.
                elemUid, _ = bitVal.saveSDB(sdb)

                sql = "INSERT INTO structure_elements (struct_uid, elem_uid, lsb_bit_position, bit_width) VALUES (?,?,?,?)"
                sqlValues = (structUid, elemUid, bitVal.startBit, bitVal.endBit+1-bitVal.startBit)
                sdb.sql.execute(sql, sqlValues)

        else:
            structUid = hashed[0][0]

        # Now add the config element entry as well. Recreate the descriptor using
        # just the common fields but keep the hash
        d = self.getSdbDescriptor(tag)
        d.hash = md5
        elemUid = d.saveSDB(sdb)

        # Cross-reference the config_element for this type to the FW release
        sdb.xrefElement(elemUid, structUid, TagTypeInfo.STRUCTURE)

        return elemUid, structUid


    ############################################################################
    # Get the ROM default value for this type, for inserting into the SDB
    ############################################################################
    def getSdbDefault(self, tag):
        # The bitfield default is technically a simple integer. However as we
        # represent the bitfield as a struct in the database, we also need to
        # provide the default as an array of values for each bit value.
        #
        default = []
        paddedBits = self.getPaddedBits()

        # Now add struct_element definitions to database for each bit, including padding
        for bitVal in paddedBits:
            default.extend(bitVal.getSdbDefault(None))
        return default


    ############################################################################
    # Save struct to an VLIST file
    ############################################################################
    def saveVLIST(self, vlist, tag, print_intermediate = True):
        
        expname = self.getTypeStringRecursive()
        
        if print_intermediate and vlist.filter.vtagEnabled(expname):
            
            # Make sure this is published in case it is not in the known VTag list
            self.isVtagPublished = True

            self.addHashInfo(self, tag)
            md5 = self.getHash(shortHash=True)
    
            if not tag_descriptor.vListInfo.isTagDefined(expname, md5):
                vlist.SaveTagInfo(expname, md5, int(self.values[self.names.index("psid")]), self.getTagName())
                
            if config.options.debug:
                print("saveVLIST tagtype_bits " + expname)

        # Do not export bits as we only want the bitfield container


    ############################################################################
    # Generate tag data types header information
    ############################################################################
    def genTagDataTypes(self, file, generatedTypes, indent):
        file.write("\n")
        for bitVal in self.bits:
            typeName = CodeGen.makeUpperIdent("CFG_" + self.name + "_" + bitVal.name + "_MASK")
            if not CodeGen.checkUnique(generatedTypes, typeName, self):
                continue

            if self.highestBit < 8: formatSpec = "#define   %s(0x%02X)\n"
            elif self.highestBit < 16: formatSpec = "#define   %s(0x%04X)\n"
            else: formatSpec = "#define   %s(0x%08X)\n"

            file.write(formatSpec % (CodeGen.padIdent(typeName), bitVal.getBitMask()))


    ############################################################################
    # Generate tag element information
    ############################################################################
    def genTagElement(self, file, indent):
        if self.highestBit < 8: bitType = "UINT8 "
        elif self.highestBit < 16: bitType = "UINT16 "
        else: bitType = "UINT32 "

        file.write((" "*indent + bitType).ljust(11) + CodeGen.makeIdent("Cfg_" + self.name) + ";")


    ############################################################################
    # Generate tag element reference information
    ############################################################################
    def genTagElementRef(self, file, baseDefine, baseElem):
        elemName = baseElem+CodeGen.makeIdent("Cfg_"+self.name)
        file.write("#define  %s" % CodeGen.padTo(CodeGen.makeUpperIdent("%s_%s_PTR" % (baseDefine, self.name)), 40))
        file.write(" ((UINT8 *) &(%s))\n" % elemName)

        file.write("#define  %s" % CodeGen.padTo(CodeGen.makeUpperIdent("%s_%s" % (baseDefine, self.name)), 40))
        file.write(" (%s)\n" % elemName)


    ############################################################################
    # Generate tag default values
    ############################################################################
    def genTagDefaultData(self, file, indent):
        typeStr = self.type.getTypeString()
        file.write(" "*indent + "(" + typeStr + ")0x" + self.type.getFormatSpec() % self.default)


    ############################################################################
    # Generate tag format information for HTML
    ############################################################################
    def genTagUserFormat(self, file, indent, byteIndex):
        file.write(" "*indent + "<b>" + self.type.getByteRangeStr(byteIndex))
        file.write(" :  %s</b>\n" % self.name)
        byteIndex += self.type.size

        file.write("<ul>\n")
        for bitVal in self.bits:
            file.write(" "*(indent+4) + bitVal.desc)
            file.write("\n<br>\n")

        file.write(" "*(indent+4) + "<b>Default :</b> ")
        self.genTagDefaultData(file, 0)
        file.write("</ul>\n\n")

        return byteIndex
