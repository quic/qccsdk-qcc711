################################################################################
# Generate Hydra SDB database directly from the source definitions, to avoid
# converting to the intermediate Hydra XML format.
#
# Note that Hydra hyconfdbutil.pl has an XML export option to obtain Hydra XML
# from a source database.
################################################################################
# Copyright (c) 2018-2019 Qualcomm Technologies International, Ltd.
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
import os, re, sqlite3, hashlib
import config
from config import TagTypeInfo, TagError
from tag_descriptor import TagDescriptor
import hydra_schema


################################################################################
# Global Variables
################################################################################


################################################################################
# Local Functions
################################################################################
    
    
################################################################################
# SDB Database Descriptor.
################################################################################
class SdbDescriptor(TagDescriptor):
    
    def __init__(self):
        TagDescriptor.__init__(self)


    ############################################################################
    # Save a descriptor to the config_elements table if no matching entry
    ############################################################################
    def saveSDB(self, sdb):
        # Calculate the hash and check if it is already in the DB
        md5 = self.getHash()
        sdb.sql.execute("SELECT elem_uid FROM config_elements where hash='%s'" % md5)
        hashed = sdb.sql.fetchall()

        if len(hashed) == 0:
            # Build the column names and values for inserting this
            sqlNames = "elem_uid, hash"
            sqlValStr = "NULL, ?"
            sqlValues = [md5]

            for name,val in zip(self.names, self.values):
                sqlNames += ", " + name
                sqlValStr += ", ?"
                sqlValues.append(val)

            sqlCmd = "INSERT INTO config_elements (%s) VALUES(%s)" % (sqlNames, sqlValStr)
            sdb.sql.execute(sqlCmd, sqlValues)

            # Now retrieve the elemUid of the newly-inserted element, using the hash
            sdb.sql.execute("SELECT elem_uid FROM config_elements where hash='%s'" % md5)
            hashed = sdb.sql.fetchall()

        elemUid = hashed[0][0]

        return elemUid


    ############################################################################
    # Save a descriptor to the config_element_default_values table if no matching entry
    ############################################################################
    def saveDefault(self, sdb):
        # Calculate the hash and check if it is already in the DB
        md5 = self.getHash()
        sdb.sql.execute("SELECT def_uid FROM config_element_default_values where hash='%s'" % md5)
        hashed = sdb.sql.fetchall()

        if len(hashed) == 0:
            # Build the column names and values for inserting this
            sqlNames = "def_uid, elem_uid, hash"
            sqlValStr = "NULL, ?, ?"
            sqlValues = [self.elemUid, md5]

            # Remove the array default pseudo-column from the descriptor, as its only used for hashing
            if self.defArrayIdx is not None:
                del self.names[self.defArrayIdx]
                del self.values[self.defArrayIdx]

            for name,val in zip(self.names, self.values):
                sqlNames += ", " + name
                sqlValStr += ", ?"
                sqlValues.append(val)

            sqlCmd = "INSERT INTO config_element_default_values (%s) VALUES(%s)" % (sqlNames, sqlValStr)
            sdb.sql.execute(sqlCmd, sqlValues)

            # Now retrieve the defUid of the newly-inserted default, using the hash
            sdb.sql.execute("SELECT def_uid FROM config_element_default_values where hash='%s'" % md5)
            defUid = sdb.sql.fetchall()[0][0]

            # And finally link back to the FW ID.
            sdb.linkDefaults(defUid)

        else:
            defUid = hashed[0][0]

        return defUid


################################################################################
# Export the tag configuration to the Hydra SDB database.
################################################################################
class ExportSDB():
    SCHEMA_VERSION_MAJOR = 3
    SCHEMA_VERSION_MINOR = 1


    ############################################################################
    # Instance initialiser
    ############################################################################
    def __init__(self, nvmTags, outputFile):
        self.nvmTags = nvmTags
        self.outputFile = outputFile
        self.platName = ""
        self.sqlConn = None
        self.sql = None
        self.subFwUid = None

        # Read the RCF system information file to get additional build information
        rcf = open(config.options.sysInfo, "r")
        self.sysInfo = {}
        self.sysInfo['chipName'] = rcf.readline().strip()
        self.sysInfo['romName'] = rcf.readline().strip()

        idVersion = rcf.readline().strip().split(',')
        if len(idVersion) < 2:
            raise TagError("Malformed RCF: require Chip ID, Version on line 3")
        self.sysInfo['chipID'] = int(idVersion[0], 0)
        self.sysInfo['romVersion'] = int(idVersion[1], 0)
        # eFuse hashes are not processed just now

        self.sysInfo['patchRelease'] = int(rcf.readline().strip(), 0)
        self.sysInfo['sysVersionLabel'] = rcf.readline().strip()
        self.sysInfo['sysDescription'] = rcf.readline().strip()
        self.sysInfo['customerName'] = rcf.readline().strip()
        self.sysInfo['releaseDateTime'] = rcf.readline().strip()

        # Replace "now" timestamp with the current system time
        if self.sysInfo['releaseDateTime'].lower() == "now":
            self.sysInfo['releaseDateTime'] = config.timestamp.strftime("%Y-%m-%d %H:%M:%S")

        # The last line of the RCF is typically the FW version for one or more
        # subsystems, but we don't use that here. However we do expect the line
        # to be populated, to ensure the RCF is correctly defined.
        if rcf.readline() == "":
            raise TagError("Malformed RCF: not enough lines present")

        rcf.close()


    ############################################################################
    # Instance destructor
    ############################################################################
    def __del__(self):
        try:
            if self.sqlConn is not None:
                self.sqlConn.close()
                self.sqlConn = None
        except Exception:
            # Ignore errors at this stage
            pass


    ############################################################################
    # Create new database if non-existent
    ############################################################################
    def Create(self):
        # Verify that the schema version matches the generator version
        expVersion = 'schema_version VALUES\(%d,%d,""\)' % (self.SCHEMA_VERSION_MAJOR, self.SCHEMA_VERSION_MINOR)
        if re.search(expVersion, hydra_schema.sqlCreateTables) is None:
            raise TagError("Hydra SQL Schema mismatch")

        # Close the existing connection if required
        if self.sqlConn:
            self.sqlConn.close()

        # Open SQL database - this will create the file if it doesn't already exist
        self.sqlConn = sqlite3.connect(self.outputFile)
        self.sql = self.sqlConn.cursor()

        # Drop tables to clear existing data
        dropSQL = ""
        tableNames = re.findall("create table (\S+) \(", hydra_schema.sqlCreateTables)
        for t in tableNames:
            dropSQL += "DROP TABLE IF EXISTS %s;\n" % t
        self.sql.executescript(dropSQL)

        # Create new tables using schema
        self.sql.executescript(hydra_schema.sqlCreateTables)

        self.sqlConn.commit()


    ############################################################################
    # Open the database and validate the database schema
    ############################################################################
    def Open(self):
        if self.sqlConn is None:
            # Check the file exists before opening it
            if not os.path.isfile(self.outputFile):
                raise TagError("Cannot find database file: %s" % self.outputFile)

            self.sqlConn = sqlite3.connect(self.outputFile)
            self.sql = self.sqlConn.cursor()

        # Check the DB schema matches
        self.sql.execute("SELECT * from schema_version")
        schemaVer = (self.sql.fetchone())[0]

        # optionally could up-issue the DB schema here, but we don't support
        # version 1 databases so no need.
        if schemaVer != self.SCHEMA_VERSION:
            raise TagError("Incompatible database schema (%d) in: %s" % (schemaVer, self.outputFile))


    ############################################################################
    # Create new database if non-existent
    ############################################################################
    def Export(self):
        # Construct the database metadata first
        version = int(config.options.fwVersion, 0)

        metaDataNames = "version, variant, subsystem_id, subsystem_name, " +    \
            "subsystem_layer, subsystem_alias, description, build_date_time"
        metaDataValues = (version, 0, 1, "bt", None, None, None, self.sysInfo['releaseDateTime'])

        if config.options.verbose:
            print("Adding metadata for 'bt' version %d.%d" % (version, 0))
        self.sql.execute("INSERT INTO subsystem_firmware_versions (subfw_uid, %s) VALUES(NULL, ?,?,?,?,?,?,?,?)" % metaDataNames, metaDataValues)

        # Read back the new Subsystem ID
        self.sql.execute("SELECT max(subfw_uid) from subsystem_firmware_versions")
        self.subFwUid = (self.sql.fetchone())[0]
        if config.options.debug:
            print("New subfw_uid = %d" % self.subFwUid)

        self.enums = {}
        self.structs = {}

        # Now we can export the various configuration elements (types,
        # descriptions etc.) into the database.
        self.nvmTags.saveSDB(self)

        self.validateTypes()

        # Populate the system_versions table
        self.saveSystemVersion()

        # Commit the changes
        self.sqlConn.commit()

    def recordEnum(self, enumUid, name, hash):
        newEnum = (enumUid, name, hash)
        if name not in self.enums:
            self.enums[name] = []
        self.enums[name].append(newEnum)

    def recordStruct(self, structUid, name, hash):
        newStruct = (structUid, name, hash)
        if name not in self.structs:
            self.structs[name] = []
        self.structs[name].append(newStruct)
        

    ############################################################################
    # Check for duplicate enum definitions. The TCF and XML formats allow this,
    # but as SDB config_elements refer to enum and struct types by name only
    # they have to be unique across the entire set of NVM tags. This is true
    # even if two structs with the same name have different elements (and
    # thus different hashes)
    #
    # TBD: actually the "efficient mapping layer" may minimise this issue, but
    # worth checking anyway
    ############################################################################
    def validateTypes(self):
        dupeFound = False
        for enum,defn in self.enums.items():
            if len(defn) > 1:
                if not dupeFound:
                    dupeFound = True
                    print("\nENUM VALIDATION===============")
                print("%s has %d definitions" % (enum, len(defn)))
                for d in defn:
                    print("  : %3d %s = %s" % (d[0], d[1], d[2]))

        if dupeFound:
            raise TagError("Cannot generate SDB as not all ENUMs are uniquely named")

        dupeFound = False
        for struct,defn in self.structs.items():
            if len(defn) > 1:
                if not dupeFound:
                    dupeFound = True
                    print("\nSTRUCT VALIDATION\n=================")
                print("%s has %d definitions" % (struct, len(defn)))
                for d in defn:
                    print("  : %3d %s = %s" % (d[0], d[1], d[2]))

        if dupeFound:
            raise TagError("Cannot generate SDB as not all STRUCTs are uniquely named")


    ############################################################################
    # Insert a cross-reference in the subfw_elements table for a new element and type
    ############################################################################
    def xrefElement(self, elemUid, typeUid=None, tagType=None):
        # Check if we have already created this element (e.g. 2 structures with the same fields)
        self.sql.execute("SELECT elem_uid FROM subfw_elements WHERE subfw_uid=? AND elem_uid=?", (self.subFwUid, elemUid))
        knownElem = self.sql.fetchall()
        if len(knownElem) == 0:
            # Add an entry to the subfw_elements table mapping this new element
            # to the current subsystem FW ID.
            sqlValStr = "?, ?"
            sqlValues = [self.subFwUid, elemUid]

            # Fill in the third value for possible enum_uid
            if typeUid is not None and tagType == TagTypeInfo.ENUM:
                sqlValStr += ", ?"
                sqlValues.append(typeUid)
            else:
                sqlValStr += ", NULL"

            # Fill in the fourth value for possible struct_uid
            if typeUid is not None and tagType == TagTypeInfo.STRUCTURE:
                sqlValStr += ", ?"
                sqlValues.append(typeUid)
            else:
                sqlValStr += ", NULL"

            sqlCmd = "INSERT INTO subfw_elements (subfw_uid, elem_uid, enum_uid, struct_uid) VALUES(%s)" % sqlValStr
            self.sql.execute(sqlCmd, sqlValues)


    ############################################################################
    # Add a new row to subfw_defaults to link a default value with this FW
    ############################################################################
    def linkDefaults(self, defUid):
        self.sql.execute("INSERT INTO subfw_defaults (subfw_uid, def_uid) VALUES(?,?)", (self.subFwUid, defUid))


    ############################################################################
    # Get the combined hash of all element hashes that comprise the subsystem
    ############################################################################
    def getSystemHash(self):
        elementHashes = []

        # Compute the hash of all hashes in the FW versions in this system, pushing all into hash_array first
        self.sql.execute("SELECT hash FROM enum_defs WHERE enum_uid in (SELECT enum_uid from subfw_elements WHERE subfw_uid=%d)" % self.subFwUid)
        elementHashes.extend( [row[0] for row in self.sql.fetchall()] )

        self.sql.execute("SELECT hash FROM config_tables WHERE table_uid in (SELECT table_uid from subfw_elements WHERE subfw_uid=%d)" % self.subFwUid)
        elementHashes.extend( [row[0] for row in self.sql.fetchall()] )

        self.sql.execute("SELECT hash FROM config_element_default_values WHERE def_uid in (SELECT def_uid from subfw_defaults WHERE subfw_uid=%d)" % self.subFwUid)
        elementHashes.extend( [row[0] for row in self.sql.fetchall()] )

        self.sql.execute("SELECT hash FROM config_elements WHERE elem_uid in (SELECT elem_uid from subfw_elements WHERE subfw_uid=%d)" % self.subFwUid)
        elementHashes.extend( [row[0] for row in self.sql.fetchall()] )

        self.sql.execute("SELECT hash FROM struct_defs WHERE struct_uid in (SELECT struct_uid from subfw_elements WHERE subfw_uid=%d)" % self.subFwUid)
        elementHashes.extend( [row[0] for row in self.sql.fetchall()] )

        # Also get the subsystem FW version as an additional hash element
        self.sql.execute("SELECT version FROM subsystem_firmware_versions WHERE subfw_uid=%d" % self.subFwUid)
        elementHashes.extend( [str(row[0]) for row in self.sql.fetchall()] )

        if len(elementHashes) == 0:
            raise TagError("No elements found in database for subsystem ID %d" % self.subFwUid)

        m = hashlib.md5()
        for d in elementHashes:
            m.update(d.encode('utf-8'))
        return m.hexdigest()


    ############################################################################
    # Save system version information to database
    ############################################################################
    def saveSystemVersion(self):
        # Populate a new row in the system_versions table
        if config.options.verbose:
            print("Adding system version %s." % self.sysInfo['sysVersionLabel'])
            print("         Chip = %s %s patch %d" % (self.sysInfo['chipName'], self.sysInfo['romName'], self.sysInfo['patchRelease']))
            print("   Build date = %s" % self.sysInfo['releaseDateTime'])
            print("  Description = %s" % self.sysInfo['sysDescription'])
            
        sysVersionLabels = self.sysInfo['sysVersionLabel'].split(",")
        
        for label in sysVersionLabels:

            sql = "INSERT INTO system_versions "
            sql += "(system_uid, chip_name, chip_id, rom_name, rom_version, patch_release_level, system_version_label, system_description, customer_name, system_release_date_time, metadata_hash)"
            sql += " VALUES (NULL, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?)"
    
            sqlValues = (self.sysInfo['chipName'], self.sysInfo['chipID'], self.sysInfo['romName'], self.sysInfo['romVersion'],
                         self.sysInfo['patchRelease'], label, self.sysInfo['sysDescription'],
                         self.sysInfo['customerName'], self.sysInfo['releaseDateTime'], self.getSystemHash())
            self.sql.execute(sql, sqlValues)
    
            # Retrieve the new system UID and cross-link to the subsystem FW UID
            self.sql.execute("SELECT max(system_uid) FROM system_versions")
            systemUid = (self.sql.fetchone())[0]
            self.sql.execute("INSERT INTO system_subfw_versions (system_uid, subfw_uid) VALUES (?, ?)", (systemUid, self.subFwUid))
