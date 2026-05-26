---
type: concept
title: CMIS 5.4 Upper Page 01h Register Map
created: 2026-05-26
updated: 2026-05-26
tags: [cmis, memory-map, upper-memory, page-01h, register-map]
related: [management-memory-map, applications-and-data-paths, command-data-block, cmis-5-4]
sources: [oif-cmis-05-4]
---

# CMIS 5.4 Upper Page 01h Register Map

Page 01h is the main advertising page. It tells the host which static capabilities, optional pages, controls, flags, monitors, CDB functions, lane polarity features, and application descriptor extensions the module supports.

## Addressing and Access Model

Select Page 01h with `PageSelect = 01h`; Page 01h is not banked. Struct offset 0 corresponds to register address `01h:128`.

Page 01h is largely read-only advertisement data. The page checksum at `01h:255` covers bytes `01h:130-254`, intentionally excluding firmware revision bytes `01h:128-129` so a firmware update does not force a broader memory-map update.

## Byte-Range Overview

| Bytes | Size | Field Group | Host Use |
|---|---:|---|---|
| 128-131 | 4 | inactive firmware and hardware revisions | Identify inactive firmware image and hardware revision. |
| 132-137 | 6 | supported link length | Fiber media link length advertisements. |
| 138-141 | 4 | wavelength information | Nominal wavelength and tolerance for single-wavelength modules. |
| 142 | 1 | supported pages and banks | Baseline page/bank discovery advertisement. |
| 143-144 | 2 | durations | Module and data-path timing advertisements. |
| 145-154 | 10 | module characteristics | Static module attributes and behavioral options. |
| 155-156 | 2 | supported controls | Module-level and lane-level control support. |
| 157-158 | 2 | supported flags | Flag support advertisement. |
| 159-160 | 2 | supported monitors | Monitor support advertisement. |
| 161-162 | 2 | supported signal integrity controls | SI control support advertisement. |
| 163-166 | 4 | supported CDB functionality | CDB messaging capabilities and limits. |
| 167-169 | 3 | additional durations | Additional advertised timing values. |
| 170 | 1 | reserved | Reserved. |
| 171-172 | 2 | lane polarity inversion | Host and media lane polarity support. |
| 173-174 | 2 | extended supported pages and banks | Additional page and bank support advertisement. |
| 175 | 1 | normalized application descriptors | NAD support advertisement. |
| 176-190 | 15 | media lane advertising | Media lane assignment options for up to 8 lanes. |
| 191-222 | 32 | custom | Vendor custom advertisement area. |
| 223-250 | 28 | additional application descriptors | Extension space for application advertisement. |
| 251-254 | 4 | miscellaneous advertisements | Miscellaneous feature bits. |
| 255 | 1 | page checksum | Checksum over bytes 130-254. |

## Field Notes

- Hosts should read Page 01h before probing optional pages. Use `SupportedPagesAndBanksAdvertisement` fields to avoid unnecessary accesses to unsupported upper pages.
- Bytes 163-166 are the bridge from base discovery into [command-data-block](command-data-block.md) behavior. Treat CDB support as optional even when the memory page exists.
- Media lane assignment advertisement is independent from run-time lane status. Use Page 11h for active mapping and live state.
- Bytes 223-250 extend application descriptors. Host application matching code should be prepared for both the base descriptors and these additional descriptors.

## C Register View

The overlay keeps multi-byte advertisements as byte arrays. On little-endian ARM, decode U16/S16 values from the byte array using CMIS big-endian scalar rules unless a specific table states another encoding.

```c
#ifndef CMIS_5_4_PAGE_01H_H
#define CMIS_5_4_PAGE_01H_H

#include <stddef.h>
#include <stdint.h>

#if defined(__GNUC__) || defined(__clang__)
#define CMIS_PACKED __attribute__((packed))
#else
#define CMIS_PACKED
#endif

typedef struct CMIS_PACKED {
    uint8_t InactiveFirmwareAndHardwareRevisions[4];      /* 01h:128-131 */
    uint8_t SupportedLinkLength[6];                       /* 01h:132-137 */
    uint8_t WavelengthInformation[4];                     /* 01h:138-141 */
    uint8_t SupportedPagesAndBanksAdvertisement142;       /* 01h:142 */
    uint8_t DurationsAdvertisements[2];                   /* 01h:143-144 */
    uint8_t ModuleCharacteristicsAdvertisement[10];       /* 01h:145-154 */
    uint8_t SupportedControls[2];                         /* 01h:155-156 */
    uint8_t SupportedFlags[2];                            /* 01h:157-158 */
    uint8_t SupportedMonitors[2];                         /* 01h:159-160 */
    uint8_t SupportedSignalIntegrityControls[2];          /* 01h:161-162 */
    uint8_t SupportedCDBFunctionality[4];                 /* 01h:163-166 */
    uint8_t AdditionalDurationsAdvertisements[3];         /* 01h:167-169 */
    uint8_t Reserved170;                                  /* 01h:170 */
    uint8_t LanePolarityInversionAdvertisement[2];        /* 01h:171-172 */
    uint8_t SupportedPagesAndBanksAdvertisement173[2];    /* 01h:173-174 */
    uint8_t NormalizedApplicationDescriptorsSupport;      /* 01h:175 */
    uint8_t MediaLaneAdvertising[15];                     /* 01h:176-190 */
    uint8_t Custom191_222[32];                            /* 01h:191-222 */
    uint8_t AdditionalApplicationDescriptors[28];         /* 01h:223-250 */
    uint8_t MiscellaneousAdvertisements[4];               /* 01h:251-254 */
    uint8_t PageChecksum;                                 /* 01h:255 */
} cmis_5_4_page_01h_t;

#if defined(__STDC_VERSION__) && (__STDC_VERSION__ >= 201112L)
_Static_assert(sizeof(cmis_5_4_page_01h_t) == 128u, "CMIS Page 01h overlay must be 128 bytes");
_Static_assert(offsetof(cmis_5_4_page_01h_t, SupportedPagesAndBanksAdvertisement142) == 14u, "01h:142 offset mismatch");
_Static_assert(offsetof(cmis_5_4_page_01h_t, AdditionalApplicationDescriptors) == 95u, "01h:223 offset mismatch");
_Static_assert(offsetof(cmis_5_4_page_01h_t, PageChecksum) == 127u, "01h:255 offset mismatch");
#endif

#endif /* CMIS_5_4_PAGE_01H_H */
```

## Source Anchors

- [oif-cmis-05-4](../sources/oif-cmis-05-4.md), section 8.4, "Page 01h (Advertising)".
- Table 8-43, Page 01h overview.
- Tables 8-44 through 8-62, Page 01h field definitions.
- PDF pages 195-210 in the CMIS 5.4 source.
