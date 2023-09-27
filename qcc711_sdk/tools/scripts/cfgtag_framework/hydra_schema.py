################################################################################
# Hydra database schema, wrapped into a multi-line Python variable.
################################################################################
# Copyright (c) 2018-2019 Qualcomm Technologies International, Ltd.
# All Rights Reserved
# Confidential and Proprietary - Qualcomm Technologies International, Ltd.
################################################################################


################################################################################
# Global Variables
################################################################################
sqlCreateTables='''
-- HydraCore config database schema

-- >>>>>>>>>>>>>>>>>>> Make sure the VERSION NUMBER at the bottom of the file is updated when the database structure is changed <<<<<<<<<<<<<<<<<<<<<<<<<<<<

-- Version 1 = original
-- Version 2 = addition of array_length_min/max to config_elements


-- notes on hashes:
-- The hashes are to identify existing elements, defaults, structures, etc. that contain identical information to some new element
-- When the table containing the hash has other tables hanging off it, the hash will contain information from those subordinate table's rows.
-- The hashes will not be derived from any of the uids, though - these serve as foreign keys, etc. but don't identify the data.

  create table schema_version (
    schema_version integer not null,
    minor_version INTEGER NOT NULL,
    comment VARCHAR(100),
    primary key (schema_version)
);

create table system_versions (
    system_uid integer,
    chip_name varchar(80),
    chip_id integer,
    rom_name varchar(80),
    rom_version integer,
    patch_release_level integer,
    system_version_label varchar(80),
    system_description text,
    customer_name varchar(80),
    system_release_date_time datetime,
    metadata_hash varchar(33), -- an MD5 hash of the hashes of all elements relevant to this combination of subfw_ids
    primary key (system_uid)
);

create table subsystem_firmware_versions (
    subfw_uid integer,
    subsystem_name varchar(20),
    subsystem_layer varchar(20),
    subsystem_alias varchar(20),
    subsystem_id integer, -- enum value from FILENAME_SUBSYSTEM_ID defined in filename.xml / filename_prim.h
    version integer,
    variant integer,
    description text,
    build_date_time datetime,
    primary key (subfw_uid)
);

create table system_subfw_versions (
    system_uid integer,
    subfw_uid integer,
    primary key (system_uid, subfw_uid),
    foreign key (subfw_uid) references subsystem_firmware_versions(subfw_uid),
    foreign key (system_uid) references system_versions(system_uid)
);

create table system_efuse_hashes (
    system_uid integer,
    efuse_hash integer,
    foreign key (system_uid) references system_versions(system_uid)
);

create table patch_files (
    subfw_uid integer,
    patch_level integer,
    patch_hash varchar(33), -- an MD5 hash of the patch file
    foreign key (subfw_uid) references subsystem_firmware_versions (subfw_uid)
);


-- An element might appear in a table as a Value, and under these circumstances there'll be a table name specified in the config_element.
-- the Indexes surrounding the tabled value are specified in the config_table_indices above.
-- a particular elem_uid can appear as an index in several tables, but a Value can appear only in one table,
--  i.e. the config_element itself will name the table it's in.

-- contains just unique versions of these items
create table config_elements (
    elem_uid integer, -- this is the unique ID for this version of the config element.
    psid integer, -- this is the PSID-like ID.  There might be several versions of elems all with this ID.  These mignt also be NULL IDs, e.g. for array elements which are actually structures, and for table indices
    name varchar(80),
    label text,
    category varchar(40),
    is_internal boolean default 0,
    format varchar(20),
    range_min integer,
    range_max integer,
    oid varchar(20), -- BER encoded dotted decimal number for this, when referring to wi-fi data
    type varchar(80) not null,  -- either integer, octet_string, uint8, int8, uint16, int16, uint32, int32, uint64, int64, a struct_name or an enum_name
    units varchar(80),
    is_array bool default 0, -- indicates that this element can contain a number of elements of the defined type, where the number may be constrained by array_length_min and/or array_length_max.
    array_length_min integer,
    array_length_max integer,
    description_user text,
    description_internal text,
    additional_information text,
    source_reference text, -- description of the origin of this config element.
    source_default varchar(20),
    access_rights varchar(14),  -- One of read_write, read_only, write_only, not_accessible.
    hash varchar(33), -- an MD5 hash of the contents of all the fields in the config_elements table (except for the elem_uid)
    primary key (elem_uid)
);

create table subfw_elements (
    subfw_uid integer,
    elem_uid integer,
    enum_uid integer,
    struct_uid integer,
    table_uid integer,
    primary key (subfw_uid, elem_uid),
    foreign key (subfw_uid) references subsystem_firmware_versions(subfw_uid),
    foreign key (elem_uid) references config_elements(elem_uid)
    foreign key (enum_uid) references enum_defs(enum_uid)
    foreign key (struct_uid) references struct_defs(struct_uid)
    foreign key (table_uid) references config_tables(table_uid)
);

-- contains just unique versions of these items
create table enum_defs (
    enum_uid integer,
    enum_name varchar(80),
    hash varchar(33), -- an MD5 hash of the enum_name, the enum_include and all of the enum_entries' names and values.
    primary key (enum_uid)
);

create table enum_entry (
    enum_entry_uid integer,
    enum_uid integer,
    enum_label varchar(80),
    enum_value integer,
    enum_description text,
    primary key (enum_entry_uid),
    foreign key (enum_uid) references enum_defs (enum_uid)
);


create table struct_defs (
    struct_uid integer,
    struct_name varchar(80),
    hash varchar(33), -- an MD5 hash of struct_name and all the config_element contents pointed to by structure elements referencing this structure definition.
    primary key (struct_uid)
);

-- contains just unique versions of these items
create table structure_elements (
    struct_uid integer,
    elem_uid integer,
    lsb_bit_position integer, -- the position in bits of this structure element, counting from the msb in the parent object, little-endian
    bit_width integer, -- the length in bits represented by this structure element in the'master' element, at offset above.
    primary key (struct_uid, elem_uid),
    foreign key (struct_uid) references struct_defs (struct_uid),
    foreign key (elem_uid) references config_elements (elem_uid)
);


create table config_tables ( -- Tables are first-class objects, at the level of config_elements.
-- They contain rows and columns.  The columns are config elements themselves.
    table_uid integer primary key,
    table_name varchar(80),
    description_user text,
    description_internal text,
    oid varchar(20),  -- the BER encoded (dotted decimal) representation of the table.
    source_reference text, -- description of the origin of this table.
    is_internal boolean default 0,
    num_indices integer,
    hash varchar(33) -- an MD5 hash of the contents of the name and the index info
);


create table config_table_indices (
    table_uid integer,
    elem_uid integer not null,
    position integer,
    primary key (table_uid, elem_uid),
    foreign key (table_uid) references config_tables (table_uid),
    foreign key (elem_uid) references config_elements (elem_uid)
);


create table config_element_default_values (
   def_uid integer not null,
   elem_uid integer not null, -- the 'leaf' element for which this default value applies
   value_string text,
   value_int integer,
   index1_value integer,
   index2_value integer,
   index3_value integer,
   hash varchar(33), -- an MD5 hash of the contents of the name and the index info
   primary key (def_uid),
   foreign key (elem_uid) references config_elements (elem_uid)
);


create table subfw_defaults (
    subfw_uid  integer,
    def_uid integer,
    primary key (subfw_uid, def_uid),
    foreign key (subfw_uid) references subsystem_firmware_versions (subfw_uid),
    foreign key (def_uid) references config_element_default_values (def_uid)
);


create table default_arrays (
    def_uid integer,
    value integer,
    foreign key (def_uid) references config_element_default_values (def_uid)
);


create table functions (
    func_uid integer,
    elem_uid integer,
    function_name varchar(80),
    type varchar(20),
    is_for_vif boolean,
    primary key (func_uid)
);


INSERT INTO schema_version VALUES(3,1,"") -- <<<<<<<<<<<<   Make sure this VERSION NUMBER (and the copy in hyconfdbutil.pl) is updated when the database structure is changed <<<<<<<<<<<<<<<<<<<<<<<<<<<<
'''
