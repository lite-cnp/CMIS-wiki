---
type: concept
title: CMIS 5.4 Upper Page 04h Register Map
created: 2026-05-26
updated: 2026-05-26
tags: [cmis, memory-map, upper-memory, page-04h, tunable-laser, register-map]
related: [management-memory-map, upper-page-12h-register-map, applications-and-data-paths, cmis-5-4]
sources: [oif-cmis-05-4]
---

# CMIS 5.4 Upper Page 04h Register Map

Page 04h advertises tunable laser capabilities: supported wavelength grids, channel ranges, fine-tuning support, and programmable output power range.

## Addressing and Access Model

Select Page 04h with `PageSelect = 04h`; Page 04h is not banked. Struct offset 0 corresponds to register address `04h:128`.

Page 04h is an advertisement page. Runtime tuning control and status live on [upper-page-12h-register-map](upper-page-12h-register-map.md).

## Byte-Range Overview

| Bytes | Size | Field Group | Host Use |
|---|---:|---|---|
| 128-129 | 2 | wavelength grids | Supported grid spacings and fine-tuning support bits. |
| 130-189 | 60 | channel number ranges | Low/high channel ranges per supported grid. |
| 190-197 | 8 | fine-tuning support | Fine-tuning resolution and low/high offset limits. |
| 198-201 | 4 | programmable output power | Minimum and maximum programmable output power. |
| 202-254 | 53 | reserved | Reserved. |
| 255 | 1 | page checksum | Checksum over bytes 128-254. |

## Field Notes

- Channel number ranges are signed S16 values. Decode them as CMIS big-endian on little-endian hosts.
- CMIS 5.4 includes 150 GHz and 300 GHz grid support in the Page 04h laser capability table.
- Fine-tuning and programmable power advertisements only define module capability. Use Page 12h controls for per-lane runtime values.
- Hosts should verify Page 04h support through Page 01h and the relevant application descriptors before assuming tunable laser support.

## C Register View

The channel range and tuning fields use explicit big-endian wrappers. The struct is a layout overlay; business logic should decode the named fields according to Table 8-68.

```c
#ifndef CMIS_5_4_PAGE_04H_H
#define CMIS_5_4_PAGE_04H_H

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

static inline uint16_t CmisBe16ToU16(cmis_be16_t value)
{
    return (uint16_t)(((uint16_t)value.Msb << 8) | value.Lsb);
}

static inline int16_t CmisBe16ToS16(cmis_be16_t value)
{
    return (int16_t)CmisBe16ToU16(value);
}

typedef struct CMIS_PACKED {
    uint8_t WavelengthGrids[2];             /* 04h:128-129 */
    cmis_be16_t ChannelNumberRanges[30];    /* 04h:130-189 */
    cmis_be16_t FineTuningSupport[4];       /* 04h:190-197 */
    cmis_be16_t ProgrammableOutputPower[2]; /* 04h:198-201 */
    uint8_t Reserved202_254[53];            /* 04h:202-254 */
    uint8_t PageChecksum;                   /* 04h:255 */
} cmis_5_4_page_04h_t;

#if defined(__STDC_VERSION__) && (__STDC_VERSION__ >= 201112L)
_Static_assert(sizeof(cmis_be16_t) == 2u, "CMIS BE16 wrapper must be 2 bytes");
_Static_assert(sizeof(cmis_5_4_page_04h_t) == 128u, "CMIS Page 04h overlay must be 128 bytes");
_Static_assert(offsetof(cmis_5_4_page_04h_t, ChannelNumberRanges) == 2u, "04h:130 offset mismatch");
_Static_assert(offsetof(cmis_5_4_page_04h_t, PageChecksum) == 127u, "04h:255 offset mismatch");
#endif

#endif /* CMIS_5_4_PAGE_04H_H */
```

## Source Anchors

- [oif-cmis-05-4](../sources/oif-cmis-05-4.md), section 8.7, "Page 04h (Laser Capabilities Advertising)".
- Table 8-67, Page 04h overview.
- Table 8-68, laser capabilities for tunable lasers.
- PDF pages 214-216 in the CMIS 5.4 source.
