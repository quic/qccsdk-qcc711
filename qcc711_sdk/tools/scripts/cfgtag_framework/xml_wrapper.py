################################################################################
# XML library wrapper, with fallback to Python standard library.
#
# We prefer lxml as it's implementation has additional XML formatting options
# (pretty_print) which is useful when emitting XML. However the Python standard
# library also includes an XML parser (albeit missing pretty_print). This
# wrapper hides the implementation detail from the rest of parse_tags.
#
################################################################################
# Copyright (c) 2020 Qualcomm Technologies, Inc.
# All Rights Reserved
# Confidential and Proprietary - Qualcomm Technologies, Inc.
################################################################################


################################################################################
# Library Imports
################################################################################
from __future__ import print_function

# Load the XML parser, try LXML first to get its extra formatting options, then
# try the native C implementation, finally fallback to Python implementation.
try:
    from lxml import etree as ET
    xmlIsLXML = True
except ImportError:
    xmlIsLXML = False
    try:
        import xml.etree.cElementTree as ET
    except ImportError:
        import xml.etree.ElementTree as ET



############################################################################
# Save all tag information to an XML file
############################################################################
def xmlToString(xmlElem, debug=False):
    global xmlIsLXML

    if xmlIsLXML:
        if debug: print("Using LXML")
        xmlText = ET.tostring(xmlElem, pretty_print=True, xml_declaration=True, encoding="utf-8")
    else:
        if debug: print("Using ElementTree")
        xmlText = ET.tostring(xmlElem, encoding="utf-8")

    return xmlText

