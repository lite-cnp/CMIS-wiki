---
type: concept
title: CMIS 5.4 Upper Page 00h Register Map
created: 2026-05-26
updated: 2026-05-26
tags: [cmis, memory-map, upper-memory, page-00h, register-map]
related: [management-memory-map, low-memory-register-map, cmis-5-4]
sources: [oif-cmis-05-4]
---

# CMIS 5.4 Upper Page 00h Register Map

Page 00h is the required administrative information page. It exposes static identification, vendor, module power, media, cable assembly, and MCI advertisement fields in Upper Memory bytes 128-255.

## Addressing and Access Model

Select Page 00h with `PageSelect = 00h`; Page 00h is not banked. The C overlay below models only the 128-byte Upper Memory window, so struct offset 0 corresponds to register address `00h:128`.

Most fields on this page are read-only advertisements. The page checksum at `00h:222` covers bytes `00h:128` through `00h:221`; the final custom area starts after the checksum and is outside that checksum span.

## Byte-Range Overview

| Bytes | Size | Field Group | Host Use |
|---|---:|---|---|
| 128 | 1 | `SFF8024IdentifierCopy` | Required copy of Lower Memory byte `00h:0`. |
| 129-199 | 71 | vendor information | `VendorName`, `VendorOUI`, `VendorPN`, `VendorRev`, `VendorSN`, `DateCode`, and `CLEICode`. |
| 200-201 | 2 | `ModulePowerCharacteristics` | Power class and `MaxPower` advertisement. |
| 202 | 1 | `CableAssemblyLinkLength` | Cable length encoding for cable assemblies; zero for detachable media. |
| 203 | 1 | `ConnectorType` | Media-side connector type from the SFF-8024 connector table. |
| 204-209 | 6 | `CopperCableAttenuation` | Copper cable attenuation values when applicable; otherwise reserved. |
| 210 | 1 | `MediaLaneInformation` | Per-lane unsupported mask for modules with up to 8 host lanes. |
| 211 | 1 | `CableAssemblyInformation` | Far-end breakout configuration for cable assemblies. |
| 212 | 1 | `MediaInterfaceTechnology` | Media-side device or cable technology code. |
| 213-214 | 2 | `MCIRelatedAdvertisement` | SPIMCI flow-control advertisement. |
| 215-220 | 6 | reserved | Reserved. |
| 221 | 1 | custom | Vendor custom byte included in the checksum. |
| 222 | 1 | `PageChecksum` | Low byte of the arithmetic sum of bytes 128-221. |
| 223-255 | 33 | custom | Non-volatile vendor custom information outside the checksum. |

## Field Notes

- `VendorName`, `VendorPN`, `VendorRev`, `VendorSN`, `DateCode`, and `CLEICode` are fixed-width ASCII fields. Hosts should trim right-side ASCII spaces without assuming a NUL terminator.
- `ModulePowerCharacteristics` splits byte 200 into `ModulePowerClass` in bits 7-5 and reserved bits 4-0; byte 201 is `MaxPower` in 0.25 W units.
- `CableAssemblyLinkLength` uses bits 7-6 as a multiplier selector and bits 5-0 as the base length value.
- `MediaLaneInformation` and `CableAssemblyInformation` are not banked. For modules with more than 8 host lanes, hosts need to follow the CMIS 5.4 lane-count rules rather than treating byte 210 as a complete lane map.
- `MCIRelatedAdvertisement` is relevant to SPIMCI. I2CMCI hosts can usually ignore it unless they share common discovery code.

## C Register View

The struct is byte-address accurate for a little-endian ARM target because it does not reinterpret CMIS multi-byte data as native integers. Decode bit fields with masks or explicit helper functions in driver code.

```c
#ifndef CMIS_5_4_PAGE_00H_H
#define CMIS_5_4_PAGE_00H_H

#include <stddef.h>
#include <stdint.h>

#if defined(__GNUC__) || defined(__clang__)
#define CMIS_PACKED __attribute__((packed))
#else
#define CMIS_PACKED
#endif

typedef struct CMIS_PACKED {
    uint8_t SFF8024IdentifierCopy;          /* 00h:128 */
    uint8_t VendorName[16];                 /* 00h:129-144 */
    uint8_t VendorOUI[3];                   /* 00h:145-147 */
    uint8_t VendorPN[16];                   /* 00h:148-163 */
    uint8_t VendorRev[2];                   /* 00h:164-165 */
    uint8_t VendorSN[16];                   /* 00h:166-181 */
    uint8_t DateCode[8];                    /* 00h:182-189 */
    uint8_t CLEICode[10];                   /* 00h:190-199 */
    uint8_t ModulePowerCharacteristics[2];  /* 00h:200-201 */
    uint8_t CableAssemblyLinkLength;        /* 00h:202 */
    uint8_t ConnectorType;                  /* 00h:203 */
    uint8_t CopperCableAttenuation[6];      /* 00h:204-209 */
    uint8_t MediaLaneInformation;           /* 00h:210 */
    uint8_t CableAssemblyInformation;       /* 00h:211 */
    uint8_t MediaInterfaceTechnology;       /* 00h:212 */
    uint8_t MCIRelatedAdvertisement[2];     /* 00h:213-214 */
    uint8_t Reserved215_220[6];             /* 00h:215-220 */
    uint8_t Custom221;                      /* 00h:221 */
    uint8_t PageChecksum;                   /* 00h:222 */
    uint8_t Custom223_255[33];              /* 00h:223-255 */
} cmis_5_4_page_00h_t;

#if defined(__STDC_VERSION__) && (__STDC_VERSION__ >= 201112L)
_Static_assert(sizeof(cmis_5_4_page_00h_t) == 128u, "CMIS Page 00h overlay must be 128 bytes");
_Static_assert(offsetof(cmis_5_4_page_00h_t, SFF8024IdentifierCopy) == 0u, "00h:128 offset mismatch");
_Static_assert(offsetof(cmis_5_4_page_00h_t, PageChecksum) == 94u, "00h:222 offset mismatch");
_Static_assert(offsetof(cmis_5_4_page_00h_t, Custom223_255) == 95u, "00h:223 offset mismatch");
#endif

#endif /* CMIS_5_4_PAGE_00H_H */
```

## Source Anchors

- [oif-cmis-05-4](../sources/oif-cmis-05-4.md), section 8.3, "Page 00h (Administrative Information)".
- Table 8-27, Page 00h overview.
- Tables 8-28 through 8-42, field definitions for bytes `00h:128-222`.
- PDF pages 188-194 in the CMIS 5.4 source.
