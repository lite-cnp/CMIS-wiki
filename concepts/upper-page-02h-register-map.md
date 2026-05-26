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

This self-contained C view is embedded directly in the page so it is visible in Obsidian. It names every threshold field individually and models all CMIS U16/S16 threshold values as explicit big-endian byte wrappers for little-endian ARM targets.

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

typedef struct CMIS_PACKED {
    cmis_be16_t TempMonHighAlarmThreshold;                 /* 02h:128-129 */
    cmis_be16_t TempMonLowAlarmThreshold;                  /* 02h:130-131 */
    cmis_be16_t TempMonHighWarningThreshold;               /* 02h:132-133 */
    cmis_be16_t TempMonLowWarningThreshold;                /* 02h:134-135 */
    cmis_be16_t VccMonHighAlarmThreshold;                  /* 02h:136-137 */
    cmis_be16_t VccMonLowAlarmThreshold;                   /* 02h:138-139 */
    cmis_be16_t VccMonHighWarningThreshold;                /* 02h:140-141 */
    cmis_be16_t VccMonLowWarningThreshold;                 /* 02h:142-143 */
    cmis_be16_t Aux1MonHighAlarmThreshold;                 /* 02h:144-145 */
    cmis_be16_t Aux1MonLowAlarmThreshold;                  /* 02h:146-147 */
    cmis_be16_t Aux1MonHighWarningThreshold;               /* 02h:148-149 */
    cmis_be16_t Aux1MonLowWarningThreshold;                /* 02h:150-151 */
    cmis_be16_t Aux2MonHighAlarmThreshold;                 /* 02h:152-153 */
    cmis_be16_t Aux2MonLowAlarmThreshold;                  /* 02h:154-155 */
    cmis_be16_t Aux2MonHighWarningThreshold;               /* 02h:156-157 */
    cmis_be16_t Aux2MonLowWarningThreshold;                /* 02h:158-159 */
    cmis_be16_t Aux3MonHighAlarmThreshold;                 /* 02h:160-161 */
    cmis_be16_t Aux3MonLowAlarmThreshold;                  /* 02h:162-163 */
    cmis_be16_t Aux3MonHighWarningThreshold;               /* 02h:164-165 */
    cmis_be16_t Aux3MonLowWarningThreshold;                /* 02h:166-167 */
    cmis_be16_t CustomMonHighAlarmThreshold;               /* 02h:168-169 */
    cmis_be16_t CustomMonLowAlarmThreshold;                /* 02h:170-171 */
    cmis_be16_t CustomMonHighWarningThreshold;             /* 02h:172-173 */
    cmis_be16_t CustomMonLowWarningThreshold;              /* 02h:174-175 */
    cmis_be16_t OpticalPowerTxHighAlarmThreshold;          /* 02h:176-177 */
    cmis_be16_t OpticalPowerTxLowAlarmThreshold;           /* 02h:178-179 */
    cmis_be16_t OpticalPowerTxHighWarningThreshold;        /* 02h:180-181 */
    cmis_be16_t OpticalPowerTxLowWarningThreshold;         /* 02h:182-183 */
    cmis_be16_t LaserBiasCurrentHighAlarmThreshold;        /* 02h:184-185 */
    cmis_be16_t LaserBiasCurrentLowAlarmThreshold;         /* 02h:186-187 */
    cmis_be16_t LaserBiasCurrentHighWarningThreshold;      /* 02h:188-189 */
    cmis_be16_t LaserBiasCurrentLowWarningThreshold;       /* 02h:190-191 */
    cmis_be16_t OpticalPowerRxHighAlarmThreshold;          /* 02h:192-193 */
    cmis_be16_t OpticalPowerRxLowAlarmThreshold;           /* 02h:194-195 */
    cmis_be16_t OpticalPowerRxHighWarningThreshold;        /* 02h:196-197 */
    cmis_be16_t OpticalPowerRxLowWarningThreshold;         /* 02h:198-199 */
    uint8_t Reserved200To229[30];                          /* 02h:200-229 */
    uint8_t Custom230To254[25];                            /* 02h:230-254 */
    uint8_t PageChecksum;                                  /* 02h:255 */
} cmis_5_4_page_02h_t;

_Static_assert(sizeof(cmis_be16_t) == 2u, "cmis_be16_t must be 2 bytes");
_Static_assert(sizeof(cmis_5_4_page_02h_t) == 128u, "Page 02h must be 128 bytes");
_Static_assert(offsetof(cmis_5_4_page_02h_t, PageChecksum) == 127u, "02h:255 offset mismatch");
```

## Source Anchors

- [oif-cmis-05-4](../sources/oif-cmis-05-4.md), section 8.5, "Page 02h (Module and Lane Supervision Thresholds)".
- Table 8-63, Page 02h overview.
- Table 8-64, module-level supervision thresholds.
- Table 8-65, lane-related supervision thresholds.
- PDF pages 211-212 in the CMIS 5.4 source.
