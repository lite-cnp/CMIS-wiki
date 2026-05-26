---
type: concept
title: CMIS 5.4 Lower Memory Register Map
created: 2026-05-26
updated: 2026-05-26
tags: [cmis, memory-map, lower-memory, registers, c-struct]
related: [cmis-5-4, management-memory-map, register-access-layer, command-data-block, applications-and-data-paths, cmis-timing-model]
sources: [oif-cmis-05-4]
---

# CMIS 5.4 Lower Memory Register Map

Lower Memory is the always-addressable CMIS byte range `00h:0-127`. It is the host's stable entry point into a module: the host uses it to identify the module, read global status, inspect flag summaries, control module-wide behavior, read module-level monitors, discover the first advertised Applications, enter passwords for custom facilities, and select the bank/page mapped into Upper Memory.

CMIS 5.4 keeps the core lower-memory shape inherited from CMIS 5.3, but it should be read against 5.4 because the surrounding memory map, firmware handling, named feature discovery, and page set are now broader.

## Addressing Model

- `00h:0-127` is Lower Memory and is directly addressable.
- `00h:128-255` is Upper Memory, whose content is selected by `BankSelect` at `00h:126` and `PageSelect` at `00h:127`.
- Byte accesses are performed through the [[register-access-layer]] READ, WRITE, and TEST primitives.
- Multi-byte scalar monitor values are encoded in CMIS data formats, not native C host endianness.
- Static or flat-memory modules may report only a subset of dynamic behavior, but still expose the lower-memory identification and core status model.

Source anchors: [[sources/oif-cmis-05-4]], sections 8.1-8.2 and Tables 8-4 through 8-26.

## Lower Memory Overview

| Bytes | Area | Role |
|---|---|---|
| `0-2` | Management Characteristics | SFF-8024 identifier, CMIS revision, memory model, MCI speed, and reconfiguration support. |
| `3` | Global Status | Interrupt output status and current Module State. |
| `4-7` | Flags Summary | Summary bits for lane/page flags in banks 0-3. |
| `8-13` | Module-Level Flags | Global status-change, firmware, CDB completion, monitor alarm/warning, and custom flags. |
| `14-25` | Module-Level Monitors | Temperature, supply voltage, Aux1-3, and custom monitor current values. |
| `26-30` | Module-Level Controls | Software reset, low-power request, hardware low-power enable, squelch method, bank broadcast, SPIMCI speed, reserved/custom bytes. |
| `31-36` | Module-Level Masks | Interrupt mask bits corresponding to module-level flags. |
| `37-38` | CDB Command Status | Status bytes for CDB instances 1 and 2. |
| `39-40` | Active Firmware Version | Active module firmware major/minor revision. |
| `41` | Module Fault Information | Reason for entry into `ModuleFault`. |
| `42-45` | Miscellaneous Status | Password command result plus reserved bytes. |
| `46-55` | Reserved | Reserved. |
| `56-63` | Extended Module Information | CMIS state-machine support, module function type, SFF-8024 subtype/heatsink/fiber-face data, low-power restrictions. |
| `64-84` | Custom | Vendor/custom lower-memory data. |
| `85-117` | Applications Advertising | Media type and the first eight basic Application Descriptors. |
| `118-125` | Password Facilities | Password change and password entry write-only/self-clearing fields. |
| `126-127` | Page Mapping | Bank and page selectors for Upper Memory. |

## Key Field Groups

### Management Characteristics

Bytes `0-2` tell the host whether it is looking at a CMIS-managed module and how the management interface should be treated.

| Address | Field | Meaning |
|---|---|---|
| `00h:0` | `SFF8024Identifier` | SFF-8024 module identifier. CMIS interpretation of the rest of the map is valid only when this identifies a CMIS-managed module. |
| `00h:1` | `CmisRevision` | BCD-like CMIS revision: upper nibble is major, lower nibble is minor. CMIS 5.4 is encoded as `54h`. |
| `00h:2.7` | `MemoryModel` | `0b` paged memory, `1b` flat memory. |
| `00h:2.6` | `SteppedConfigOnly` | Whether only step-by-step reconfiguration is supported, possibly with one intervention-free mode. |
| `00h:2.5-2` | `MciMaxSpeed` | Maximum advertised MCI clock speed. Encoding depends on I2CMCI vs SPIMCI. |
| `00h:2.1-0` | `AutoCommissioning` | Which intervention-free reconfiguration procedure is supported when `SteppedConfigOnly` is set. |

### Status, Flags, and Masks

Byte `3` reports the interrupt line and module state. Module-state encoding is:

| Code | State |
|---|---|
| `000b` | Reserved |
| `001b` | `ModuleLowPwr` |
| `010b` | `ModulePwrUp` |
| `011b` | `ModuleReady` |
| `100b` | `ModulePwrDn` |
| `101b` | `ModuleFault` |
| `110b-111b` | Reserved |

Bytes `4-7` summarize asserted flags in Bank 0-3 for Pages `11h`, `12h`, `14h`, and `2Ch`. A host clears a summarized flag by reading the underlying flag on the summarized page and bank; reading the summary bit alone is not the clear operation.

Bytes `8-13` hold module-level flags. CMIS 5.4 includes `AbnormalFwIndicationFlag` at `00h:8.3`, indicating that the running firmware content deviates from the active firmware version's identified load. The corresponding mask is `00h:31.3`.

Bytes `31-36` hold the masks that determine which module-level flags can cause a hardware interrupt. Mask bits align with the flag bits in bytes `8-11`; byte `35` is reserved for masks and byte `36` is custom.

### Monitors and Controls

Module-level monitor values are in bytes `14-25`:

| Address | Field | Format |
|---|---|---|
| `00h:14-15` | `TempMonValue` | `S16`, 1/256 deg C increments. |
| `00h:16-17` | `VccMonVoltage` | `U16`, 100 uV increments. |
| `00h:18-19` | `Aux1MonValue` | `S16`; observable advertised in Page 01h. |
| `00h:20-21` | `Aux2MonValue` | `S16`; observable advertised in Page 01h. |
| `00h:22-23` | `Aux3MonValue` | `S16`; observable advertised in Page 01h. |
| `00h:24-25` | `CustomMonValue` | `S16` or `U16`, vendor-defined. |

Byte `26` contains module-wide controls: bank broadcast enable, hardware low-power request enable, squelch method selection, software low-power request, software reset, and custom low bits. Byte `27` contains `MciSpeedConfiguration` for SPIMCI. Bytes `29-30` are custom.

### CDB, Firmware, Fault, and Password Status

Bytes `37-38` are CDB status bytes for CDB instances 1 and 2. Each status byte has `CdbIsBusy` at bit 7, `CdbHasFailed` at bit 6, and a six-bit `CdbCommandResult`.

Bytes `39-40` report the active firmware major/minor revision. `00h/00h` indicates no firmware; `FFh/FFh` indicates an invalid active firmware load; other values are vendor-defined version numbers.

Byte `41` reports why the module entered `ModuleFault`, including TEC runaway, data memory corruption, program memory corruption, transmitter fault, receiver fault, temperature-related fault, custom fault codes, and reserved ranges.

Byte `42.3-0` is `PasswordCmdResult`, the result of the most recent password entry or password change through `00h:118-125`. Its support is advertised by `01h:251.3-2`.

### Extended Module Information

Bytes `56-63` provide a compact classification of how the module should be managed:

| Address | Field | Meaning |
|---|---|---|
| `00h:56` | `CmisSmSupport` | State-machine support: undefined legacy, no SM, MSM only, MSM+DPSM, or MSM+DPSM+NPSM. |
| `00h:57` | `ModuleFunctionType` | `0` transmission module, `1` ELSFP resource module, `128-255` custom. |
| `00h:60.3-0` | `SFF8024ModuleSubtype` | SFF-8024 subtype code. |
| `00h:61.7-4` | `SFF8024HeatsinkType` | SFF-8024 heatsink type. |
| `00h:61.1-0` | `SFF8024FiberFaceType` | Unknown/not applicable, PC/UPC, APC, or reserved. |
| `00h:62` | `LowPowerRestrictions` | Advertises which CDB/query classes are unavailable in `ModuleLowPwr`. |

### Application Advertising

Byte `85` selects the Media Type table used to interpret `MediaInterfaceID` values. Bytes `86-117` hold eight four-byte Application Descriptors. Each descriptor contains:

| Offset | Field | Meaning |
|---|---|---|
| `+0` | `HostInterfaceID` | Host electrical interface ID from SFF-8024. |
| `+1` | `MediaInterfaceID` | Media interface ID selected by `MediaType`. |
| `+2.7-4` | `HostLaneCount` | Explicit host lane count or `0` for interface-defined. |
| `+2.3-0` | `MediaLaneCount` | Explicit media lane count or `0` for interface-defined. |
| `+3` | `HostLaneAssignmentOptions` | Bitmap for possible starting host lanes 1-8. |

The fifth basic descriptor byte, `MediaLaneAssignmentOptions`, is not in Lower Memory. It lives on Page `01h` alongside additional Application advertisement space.

### Password and Page Mapping

Password entry and change fields use 32-bit values in big-endian order and must be written as size-matched four-byte WRITE operations:

| Address | Field | Access |
|---|---|---|
| `00h:118-121` | `PasswordChangeEntryArea` | `WO/SC`, optional. |
| `00h:122-125` | `PasswordEntryArea` | `WO/SC`, optional. |

Password protection is only a standard mechanism for custom data or functionality. CMIS-specified features must not be password-protected unless a CMIS specification explicitly permits or advertises it.

For Upper Memory remapping:

| Address | Field | Rule |
|---|---|---|
| `00h:126` | `BankSelect` | Bank index for banked pages; ignored for unbanked pages. |
| `00h:127` | `PageSelect` | Page index mapped into Upper Memory. The module may clear it to Page `00h` if an unsupported page is requested. |

For arbitrary page-address changes or bank changes, the host should write both bytes `126-127` in one WRITE access. For a page-only change within the current bank, writing only `PageSelect` is allowed.

## C Struct Definition

This struct is a register-view aid modeled after generated CMIS C headers, with explicit raw-byte aliases for bitfield bytes. It is useful for driver review and documentation, but production code should still treat bitfield layout as compiler-defined and should convert multi-byte numeric values from the CMIS wire format explicitly.

```c
#ifndef CMIS_5_4_LOW_MEMORY_H
#define CMIS_5_4_LOW_MEMORY_H

#include <stdint.h>

#if defined(__GNUC__) || defined(__clang__)
#define CMIS_PACKED __attribute__((packed))
#else
#define CMIS_PACKED
#endif

typedef enum {
    CMIS_MODULE_STATE_RESERVED_0 = 0,
    CMIS_MODULE_STATE_LOW_PWR = 1,
    CMIS_MODULE_STATE_PWR_UP = 2,
    CMIS_MODULE_STATE_READY = 3,
    CMIS_MODULE_STATE_PWR_DN = 4,
    CMIS_MODULE_STATE_FAULT = 5,
    CMIS_MODULE_STATE_RESERVED_6 = 6,
    CMIS_MODULE_STATE_RESERVED_7 = 7,
} cmis_module_state_t;

typedef struct CMIS_PACKED {
    uint8_t page11h : 1;
    uint8_t page12h : 1;
    uint8_t page14h : 1;
    uint8_t page2ch : 1;
    uint8_t reserved : 4;
} cmis_flags_summary_t;

typedef struct CMIS_PACKED {
    uint8_t host_interface_id;
    uint8_t media_interface_id;
    uint8_t media_lane_count : 4;
    uint8_t host_lane_count : 4;
    uint8_t host_lane_assignment_options;
} cmis_lower_app_descriptor_t;

typedef struct CMIS_PACKED {
    uint8_t sff8024_identifier;       /* 00h:0 */
    uint8_t cmis_revision;            /* 00h:1, e.g. 54h for CMIS 5.4 */

    union {
        struct {
            uint8_t auto_commissioning : 2;  /* 00h:2.1-0 */
            uint8_t mci_max_speed : 4;       /* 00h:2.5-2 */
            uint8_t stepped_config_only : 1; /* 00h:2.6 */
            uint8_t memory_model : 1;        /* 00h:2.7 */
        };
        uint8_t raw;
    } management_characteristics;     /* 00h:2 */

    union {
        struct {
            uint8_t interrupt_deasserted : 1; /* 00h:3.0 */
            uint8_t module_state : 3;         /* 00h:3.3-1 */
            uint8_t reserved : 4;             /* 00h:3.7-4 */
        };
        uint8_t raw;
    } global_status;                  /* 00h:3 */

    cmis_flags_summary_t flags_summary_bank[4]; /* 00h:4-7 */

    union {
        struct {
            uint8_t module_state_changed : 1;       /* 00h:8.0 */
            uint8_t module_firmware_error : 1;      /* 00h:8.1 */
            uint8_t data_path_firmware_error : 1;   /* 00h:8.2 */
            uint8_t abnormal_fw_indication : 1;     /* 00h:8.3 */
            uint8_t reserved : 2;                   /* 00h:8.5-4 */
            uint8_t cdb_cmd_complete_1 : 1;         /* 00h:8.6 */
            uint8_t cdb_cmd_complete_2 : 1;         /* 00h:8.7 */
        };
        uint8_t raw;
    } module_flags;                   /* 00h:8 */

    union {
        struct {
            uint8_t temp_high_alarm : 1;
            uint8_t temp_low_alarm : 1;
            uint8_t temp_high_warning : 1;
            uint8_t temp_low_warning : 1;
            uint8_t vcc_high_alarm : 1;
            uint8_t vcc_low_alarm : 1;
            uint8_t vcc_high_warning : 1;
            uint8_t vcc_low_warning : 1;
        };
        uint8_t raw;
    } temp_vcc_flags;                 /* 00h:9 */

    union {
        struct {
            uint8_t aux1_high_alarm : 1;
            uint8_t aux1_low_alarm : 1;
            uint8_t aux1_high_warning : 1;
            uint8_t aux1_low_warning : 1;
            uint8_t aux2_high_alarm : 1;
            uint8_t aux2_low_alarm : 1;
            uint8_t aux2_high_warning : 1;
            uint8_t aux2_low_warning : 1;
        };
        uint8_t raw;
    } aux1_aux2_flags;                /* 00h:10 */

    union {
        struct {
            uint8_t aux3_high_alarm : 1;
            uint8_t aux3_low_alarm : 1;
            uint8_t aux3_high_warning : 1;
            uint8_t aux3_low_warning : 1;
            uint8_t custom_high_alarm : 1;
            uint8_t custom_low_alarm : 1;
            uint8_t custom_high_warning : 1;
            uint8_t custom_low_warning : 1;
        };
        uint8_t raw;
    } aux3_custom_flags;              /* 00h:11 */

    uint8_t reserved_12;              /* 00h:12 */
    uint8_t custom_module_flags;      /* 00h:13 */

    uint16_t temp_mon_value;          /* 00h:14-15, CMIS big-endian S16 */
    uint16_t vcc_mon_voltage;         /* 00h:16-17, CMIS big-endian U16 */
    uint16_t aux1_mon_value;          /* 00h:18-19, CMIS big-endian S16 */
    uint16_t aux2_mon_value;          /* 00h:20-21, CMIS big-endian S16 */
    uint16_t aux3_mon_value;          /* 00h:22-23, CMIS big-endian S16 */
    uint16_t custom_mon_value;        /* 00h:24-25, CMIS big-endian S16/U16 */

    union {
        struct {
            uint8_t custom : 3;               /* 00h:26.2-0 */
            uint8_t software_reset : 1;       /* 00h:26.3, WO/SC */
            uint8_t low_pwr_request_sw : 1;   /* 00h:26.4 */
            uint8_t squelch_method_select : 1;/* 00h:26.5 */
            uint8_t low_pwr_allow_request_hw : 1; /* 00h:26.6 */
            uint8_t bank_broadcast_enable : 1;/* 00h:26.7 */
        };
        uint8_t raw;
    } module_controls;                /* 00h:26 */

    union {
        struct {
            uint8_t mci_speed_configuration : 4; /* 00h:27.3-0 */
            uint8_t reserved : 4;               /* 00h:27.7-4 */
        };
        uint8_t raw;
    } mci_speed_control;              /* 00h:27 */

    uint8_t reserved_28;              /* 00h:28 */
    uint8_t custom_29_30[2];          /* 00h:29-30 */

    union {
        struct {
            uint8_t module_state_changed : 1;       /* 00h:31.0 */
            uint8_t module_firmware_error : 1;      /* 00h:31.1 */
            uint8_t data_path_firmware_error : 1;   /* 00h:31.2 */
            uint8_t abnormal_fw_indication : 1;     /* 00h:31.3 */
            uint8_t reserved : 2;                   /* 00h:31.5-4 */
            uint8_t cdb_cmd_complete_1 : 1;         /* 00h:31.6 */
            uint8_t cdb_cmd_complete_2 : 1;         /* 00h:31.7 */
        };
        uint8_t raw;
    } module_masks;                   /* 00h:31 */

    union {
        struct {
            uint8_t temp_high_alarm : 1;
            uint8_t temp_low_alarm : 1;
            uint8_t temp_high_warning : 1;
            uint8_t temp_low_warning : 1;
            uint8_t vcc_high_alarm : 1;
            uint8_t vcc_low_alarm : 1;
            uint8_t vcc_high_warning : 1;
            uint8_t vcc_low_warning : 1;
        };
        uint8_t raw;
    } temp_vcc_masks;                 /* 00h:32 */

    union {
        struct {
            uint8_t aux1_high_alarm : 1;
            uint8_t aux1_low_alarm : 1;
            uint8_t aux1_high_warning : 1;
            uint8_t aux1_low_warning : 1;
            uint8_t aux2_high_alarm : 1;
            uint8_t aux2_low_alarm : 1;
            uint8_t aux2_high_warning : 1;
            uint8_t aux2_low_warning : 1;
        };
        uint8_t raw;
    } aux1_aux2_masks;                /* 00h:33 */

    union {
        struct {
            uint8_t aux3_high_alarm : 1;
            uint8_t aux3_low_alarm : 1;
            uint8_t aux3_high_warning : 1;
            uint8_t aux3_low_warning : 1;
            uint8_t custom_high_alarm : 1;
            uint8_t custom_low_alarm : 1;
            uint8_t custom_high_warning : 1;
            uint8_t custom_low_warning : 1;
        };
        uint8_t raw;
    } aux3_custom_masks;              /* 00h:34 */

    uint8_t reserved_35;              /* 00h:35 */
    uint8_t custom_module_masks;      /* 00h:36 */

    uint8_t cdb_status_1;             /* 00h:37 */
    uint8_t cdb_status_2;             /* 00h:38 */
    uint8_t active_fw_major;          /* 00h:39 */
    uint8_t active_fw_minor;          /* 00h:40 */
    uint8_t module_fault_cause;       /* 00h:41 */

    union {
        struct {
            uint8_t password_cmd_result : 4; /* 00h:42.3-0 */
            uint8_t reserved : 4;            /* 00h:42.7-4 */
        };
        uint8_t raw;
    } misc_status;                    /* 00h:42 */

    uint8_t reserved_43_55[13];       /* 00h:43-55 */

    uint8_t cmis_sm_support;          /* 00h:56 */
    uint8_t module_function_type;     /* 00h:57 */
    uint8_t reserved_58_59[2];        /* 00h:58-59 */

    union {
        struct {
            uint8_t sff8024_module_subtype : 4; /* 00h:60.3-0 */
            uint8_t reserved : 4;               /* 00h:60.7-4 */
        };
        uint8_t raw;
    } module_subtype;                 /* 00h:60 */

    union {
        struct {
            uint8_t sff8024_fiber_face_type : 2; /* 00h:61.1-0 */
            uint8_t reserved : 2;                /* 00h:61.3-2 */
            uint8_t sff8024_heatsink_type : 4;   /* 00h:61.7-4 */
        };
        uint8_t raw;
    } connector_thermal_type;         /* 00h:61 */

    union {
        struct {
            uint8_t cdb_fw_cmds_unsupported : 1;   /* 00h:62.0 */
            uint8_t cdb_cmds_unsupported : 1;      /* 00h:62.1 */
            uint8_t cdb_fw_query_unsupported : 1;  /* 00h:62.2 */
            uint8_t cdb_query_unsupported : 1;     /* 00h:62.3 */
            uint8_t reserved : 3;                  /* 00h:62.6-4 */
            uint8_t validity_indication : 1;       /* 00h:62.7 */
        };
        uint8_t raw;
    } low_power_restrictions;         /* 00h:62 */

    uint8_t reserved_63;              /* 00h:63 */
    uint8_t custom_64_84[21];         /* 00h:64-84 */

    uint8_t media_type;               /* 00h:85 */
    cmis_lower_app_descriptor_t app[8];/* 00h:86-117 */

    uint8_t password_change_entry[4]; /* 00h:118-121, write U32 big-endian */
    uint8_t password_entry[4];        /* 00h:122-125, write U32 big-endian */
    uint8_t bank_select;              /* 00h:126 */
    uint8_t page_select;              /* 00h:127 */
} cmis_5_4_low_memory_t;

#if __STDC_VERSION__ >= 202311L
static_assert(sizeof(cmis_5_4_low_memory_t) == 128,
              "cmis_5_4_low_memory_t must be 128 bytes");
#elif __STDC_VERSION__ >= 201112L
_Static_assert(sizeof(cmis_5_4_low_memory_t) == 128,
               "cmis_5_4_low_memory_t must be 128 bytes");
#endif

#endif /* CMIS_5_4_LOW_MEMORY_H */
```

## Implementation Notes

- Prefer byte offsets and masks in portable driver code; use the struct as documentation or for controlled compiler environments.
- Do not read multi-byte fields as native-endian integers without conversion. CMIS defines byte order and data formats at the register level.
- Treat RO/COR flags carefully: reading the underlying flag can clear it, while summary bits point to where the clear-on-read operation must happen.
- Do not assume CDB support just because the CDB status registers exist; use the Page 01h CDB advertisements before issuing CDB commands.
- Do not assume password support. Password entry and result support are advertised separately on Page 01h, and password protection is for custom facilities unless explicitly standardized.
- When changing a banked Upper Memory page, write `BankSelect` and `PageSelect` together unless only the page index changes within the current bank.

