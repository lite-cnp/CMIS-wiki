---
type: concept
title: CMIS 5.4 Upper Page 0Dh Register Map
created: 2026-05-26
updated: 2026-05-26
tags: [cmis, memory-map, upper-memory, page-0dh, firmware, register-map]
related: [management-memory-map, command-data-block, upper-page-01h-register-map, cmis-5-4]
sources: [oif-cmis-05-4]
---

# CMIS 5.4 Upper Page 0Dh Register Map

Page 0Dh is an optional CMIS 5.4 firmware-management page. It lets a module advertise basic firmware-load capabilities and expose firmware-load status/version information in registers, without requiring the host to enter the CDB command flow for every status check.

## Addressing and Access Model

Select Page 0Dh with `PageSelect = 0Dh`; Page 0Dh is not banked. Struct offset 0 corresponds to register address `0Dh:128`.

Support is advertised by `PageDhSupported` at `01h:173.6` on [upper-page-01h-register-map](upper-page-01h-register-map.md). Hosts should read that advertisement before selecting Page 0Dh, and should still use [command-data-block](command-data-block.md) firmware commands for operations such as querying detailed features, downloading, running, committing, or retrieving firmware load tags.

## Byte-Range Overview

| Bytes | Size | Field Group | Host Use |
|---|---:|---|---|
| 128 | 1 | `CapabilitiesRegister` | Convenience advertisement for firmware load banks, fixed load support, and CDB-based download support. |
| 129-131 | 3 | reserved | Reserved, read-only. |
| 132-135 | 4 | reserved control | Reserved, read/write. |
| 136 | 1 | `LoadsStatusRegister` | Bank A/B operational, administrative, and validity status bits. |
| 137-147 | 11 | reserved | Reserved, read-only. |
| 148-183 | 36 | `VersionLoadA` | Version descriptor for the firmware load in Bank A. |
| 184-219 | 36 | `VersionLoadB` | Version descriptor for the firmware load in Bank B. |
| 220-255 | 36 | `VersionFixedLoad` | Version descriptor for the fixed firmware load. |

## Field Notes

- `CapabilitiesRegister.BankASupported` is required for download support; `BankBSupported` requires Bank A support. `FixedBankSupported` advertises the fixed firmware-load bank.
- `CapabilitiesRegister.FixedLoadProvidesService` distinguishes a fixed load that provides auxiliary firmware-management facilities from a fixed load that additionally provides transmission service.
- `CapabilitiesRegister.CdbDownloadSupported` says the running load supports CDB-based firmware download. Page 0Dh itself does not carry firmware image payload.
- `LoadsStatusRegister` uses the same per-bank status encoding described for firmware status in section 7.3.1.4: operational status `1b` means running, administrative status `1b` means committed, and validity status `1b` means invalid. The positive validity state is encoded as `0b` for backward compatibility.
- At most one load can be committed at a time, and a reset or power cycle uses the committed load. Special status values such as `00h`, `04h`, `40h`, and `44h` indicate cases where the fixed/factory load is running or neither Bank A nor Bank B is running.
- Each version descriptor contains `MajorVersion`, `MinorVersion`, a big-endian `BuildNumber`, and a 32-byte ASCII `Description`. Host code should gate Bank B and fixed-load interpretation on the corresponding capability bits.

## C Register View

This self-contained C view is embedded directly in the page so it is visible in Obsidian. It exposes Page 0Dh capability and status bytes as named bitfield unions, adds a reusable firmware-load version descriptor, and defines common firmware status byte values from the CMIS status examples. Multi-byte build numbers remain explicit big-endian byte wrappers for little-endian ARM targets.

```c
#include <stddef.h>
#include <stdint.h>

#if defined(__GNUC__) || defined(__clang__)
#define CMIS_PACKED __attribute__((packed))
#else
#define CMIS_PACKED
#endif

typedef struct CMIS_PACKED {
    uint8_t Msb;
    uint8_t Lsb;
} cmis_be16_t;

typedef enum {
    CmisFirmwareStatusFixedLoadRunningNoValidLoad = 0x00,
    CmisFirmwareStatusRunningACommittedAValidAAndB = 0x03,
    CmisFirmwareStatusFixedLoadRunningValidB = 0x04,
    CmisFirmwareStatusTrialRunBCommittedAValidAAndB = 0x12,
    CmisFirmwareStatusTrialRunBFallbackValidB = 0x16,
    CmisFirmwareStatusTrialRunACommittedBValidAAndB = 0x21,
    CmisFirmwareStatusRunningBCommittedBValidAAndB = 0x30,
    CmisFirmwareStatusRunningBCommittedBValidB = 0x34,
    CmisFirmwareStatusFixedLoadRunningValidA = 0x40,
    CmisFirmwareStatusRunningAUncommittedValidA = 0x41,
    CmisFirmwareStatusFixedLoadRunningCommittedAValidA = 0x42,
    CmisFirmwareStatusRunningACommittedAValidA = 0x43,
    CmisFirmwareStatusFixedLoadRunningNoCommittedLoad = 0x44,
    CmisFirmwareStatusRunningAFallbackValidA = 0x61
} cmis_firmware_status_code_t;

typedef union CMIS_PACKED {
    struct {
        uint8_t BankASupported : 1;             /* 0Dh:128.0 */
        uint8_t BankBSupported : 1;             /* 0Dh:128.1 */
        uint8_t FixedBankSupported : 1;         /* 0Dh:128.2 */
        uint8_t FixedLoadProvidesService : 1;   /* 0Dh:128.3 */
        uint8_t Reserved4To6 : 3;
        uint8_t CdbDownloadSupported : 1;       /* 0Dh:128.7 */
    };
    uint8_t Raw;
} cmis_page_0dh_capabilities_t;

typedef union CMIS_PACKED {
    struct {
        uint8_t OperationalStatusA : 1;         /* 0Dh:136.0 */
        uint8_t AdministrativeStatusA : 1;      /* 0Dh:136.1 */
        uint8_t ValidityStatusA : 1;            /* 0Dh:136.2, 0b = valid */
        uint8_t Reserved3 : 1;
        uint8_t OperationalStatusB : 1;         /* 0Dh:136.4 */
        uint8_t AdministrativeStatusB : 1;      /* 0Dh:136.5 */
        uint8_t ValidityStatusB : 1;            /* 0Dh:136.6, 0b = valid */
        uint8_t Reserved7 : 1;
    };
    uint8_t Raw;
} cmis_page_0dh_loads_status_t;

typedef struct CMIS_PACKED {
    uint8_t MajorVersion;                       /* descriptor byte 0 */
    uint8_t MinorVersion;                       /* descriptor byte 1 */
    cmis_be16_t BuildNumber;                    /* descriptor bytes 2-3 */
    uint8_t Description[32];                    /* descriptor bytes 4-35 */
} cmis_firmware_load_version_descriptor_t;

typedef struct CMIS_PACKED {
    cmis_page_0dh_capabilities_t CapabilitiesRegister; /* 0Dh:128 */
    uint8_t Reserved129To131[3];                       /* 0Dh:129-131 */
    uint8_t Reserved132To135[4];                       /* 0Dh:132-135 */
    cmis_page_0dh_loads_status_t LoadsStatusRegister;  /* 0Dh:136 */
    uint8_t Reserved137To147[11];                      /* 0Dh:137-147 */
    cmis_firmware_load_version_descriptor_t VersionLoadA; /* 0Dh:148-183 */
    cmis_firmware_load_version_descriptor_t VersionLoadB; /* 0Dh:184-219 */
    cmis_firmware_load_version_descriptor_t VersionFixedLoad; /* 0Dh:220-255 */
} cmis_5_4_page_0dh_t;

static inline uint16_t CmisPage0DHBuildNumber(const cmis_firmware_load_version_descriptor_t *Descriptor)
{
    return (uint16_t)(((uint16_t)Descriptor->BuildNumber.Msb << 8) | Descriptor->BuildNumber.Lsb);
}

static inline uint8_t CmisPage0DHBankAIsRunning(const cmis_5_4_page_0dh_t *Page)
{
    return (uint8_t)Page->LoadsStatusRegister.OperationalStatusA;
}

_Static_assert(sizeof(cmis_be16_t) == 2u, "cmis_be16_t must be 2 bytes");
_Static_assert(sizeof(cmis_page_0dh_capabilities_t) == 1u, "Page 0Dh capabilities must be 1 byte");
_Static_assert(sizeof(cmis_page_0dh_loads_status_t) == 1u, "Page 0Dh load status must be 1 byte");
_Static_assert(sizeof(cmis_firmware_load_version_descriptor_t) == 36u, "firmware descriptor must be 36 bytes");
_Static_assert(sizeof(cmis_5_4_page_0dh_t) == 128u, "CMIS Page 0Dh overlay must be 128 bytes");
_Static_assert(offsetof(cmis_5_4_page_0dh_t, LoadsStatusRegister) == 8u, "0Dh:136 offset mismatch");
_Static_assert(offsetof(cmis_5_4_page_0dh_t, VersionLoadA) == 20u, "0Dh:148 offset mismatch");
_Static_assert(offsetof(cmis_5_4_page_0dh_t, VersionLoadB) == 56u, "0Dh:184 offset mismatch");
_Static_assert(offsetof(cmis_5_4_page_0dh_t, VersionFixedLoad) == 92u, "0Dh:220 offset mismatch");
```

## Source Anchors

- [oif-cmis-05-4](../sources/oif-cmis-05-4.md), section 8.12, "Page 0Dh (Firmware Management)".
- Table 8-74, Page 0Dh overview.
- Table 8-75, firmware load `VersionDescriptor` data structure.
- Table 8-76, Page 0Dh firmware management registers.
- Section 7.3.1.4 and Tables 7-1 through 7-4, firmware administration/status encoding and common status codes.
- Table 8-58, `PageDhSupported` advertisement at `01h:173.6`.
- PDF pages 128-129, 207, and 220 in the CMIS 5.4 source.
