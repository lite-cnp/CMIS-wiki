---
type: concept
title: CMIS 5.4 Upper Page 02h Register Map
created: 2026-05-26
updated: 2026-05-26
tags: [cmis, memory-map, upper-memory, page-02h, thresholds, register-map]
related: [management-memory-map, low-memory-register-map, versatile-diagnostics-monitoring, cmis-5-4]
sources: [oif-cmis-05-4]
---

# CMIS 5.4 Upper Page 02h Register Map

Page 02h contains module-level and lane-related supervision thresholds. Hosts use it to interpret alarm and warning flags from Lower Memory and lane-monitoring pages.

## Addressing and Access Model

Select Page 02h with `PageSelect = 02h`; Page 02h is not banked. Struct offset 0 corresponds to register address `02h:128`.

The threshold fields are read-only advertisements. CMIS scalar multi-byte values place the most significant byte at the lowest register address, so little-endian ARM code must not cast these fields directly to native integers.

## Byte-Range Overview

| Bytes | Size | Field Group | Host Use |
|---|---:|---|---|
| 128-175 | 48 | module-level supervision thresholds | Temperature, voltage, auxiliary, and custom monitor alarm/warning thresholds. |
| 176-199 | 24 | lane-related supervision thresholds | Tx optical power, laser bias, and Rx optical power thresholds. |
| 200-229 | 30 | reserved | Reserved. |
| 230-254 | 25 | custom | Vendor custom threshold or metadata area. |
| 255 | 1 | page checksum | Checksum over bytes 128-254. |

## Field Notes

- Table 8-64 defines module thresholds as a sequence of S16/U16 scalar values. Decode each two-byte field as CMIS big-endian.
- Table 8-65 defines lane-related thresholds. These thresholds are shared advertisements, not per-bank live monitor values.
- The live monitor values that are compared to many of these thresholds are on [low-memory-register-map](low-memory-register-map.md) and Page 11h.
- Reserved bytes should be written only if a future CMIS revision or a vendor-specific contract explicitly defines them.

## C Register View

The wrappers model the CMIS byte order explicitly. On a little-endian ARM CPU, convert through helper functions before comparing values.

```c
#ifndef CMIS_5_4_PAGE_02H_H
#define CMIS_5_4_PAGE_02H_H

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
    cmis_be16_t ModuleLevelSupervisionThresholds[24]; /* 02h:128-175 */
    cmis_be16_t LaneRelatedSupervisionThresholds[12]; /* 02h:176-199 */
    uint8_t Reserved200_229[30];                      /* 02h:200-229 */
    uint8_t Custom230_254[25];                        /* 02h:230-254 */
    uint8_t PageChecksum;                             /* 02h:255 */
} cmis_5_4_page_02h_t;

#if defined(__STDC_VERSION__) && (__STDC_VERSION__ >= 201112L)
_Static_assert(sizeof(cmis_be16_t) == 2u, "CMIS BE16 wrapper must be 2 bytes");
_Static_assert(sizeof(cmis_5_4_page_02h_t) == 128u, "CMIS Page 02h overlay must be 128 bytes");
_Static_assert(offsetof(cmis_5_4_page_02h_t, LaneRelatedSupervisionThresholds) == 48u, "02h:176 offset mismatch");
_Static_assert(offsetof(cmis_5_4_page_02h_t, PageChecksum) == 127u, "02h:255 offset mismatch");
#endif

#endif /* CMIS_5_4_PAGE_02H_H */
```

## Source Anchors

- [oif-cmis-05-4](../sources/oif-cmis-05-4.md), section 8.5, "Page 02h (Module and Lane Supervision Thresholds)".
- Table 8-63, Page 02h overview.
- Table 8-64, module-level supervision thresholds.
- Table 8-65, lane-related supervision thresholds.
- PDF pages 211-212 in the CMIS 5.4 source.
