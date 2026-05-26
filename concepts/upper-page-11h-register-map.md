---
type: concept
title: CMIS 5.4 Upper Page 11h Register Map
created: 2026-05-26
updated: 2026-05-26
tags: [cmis, memory-map, upper-memory, page-11h, banked, status, register-map]
related: [management-memory-map, data-path-state-machine, upper-page-10h-register-map, applications-and-data-paths, cmis-5-4]
sources: [oif-cmis-05-4]
---

# CMIS 5.4 Upper Page 11h Register Map

Banked Page 11h contains live lane and data-path state, lane flags, media-lane monitors, configuration command status, active control-set state, data-path conditions, and media-lane mapping.

## Addressing and Access Model

Select Page 11h with `PageSelect = 11h` and select the lane bank with `BankSelect`. Each bank covers up to 8 lanes. Struct offset 0 corresponds to register address `11h:128` in the selected bank.

Page 11h is primarily read-only status and monitor data. Several flag fields have read/clear behavior in the spec, so host software should follow the register access layer rules for clearing latched flags.

## Byte-Range Overview

| Bytes | Size | Field Group | Host Use |
|---|---:|---|---|
| 128-131 | 4 | data path states | Current state machine state for each lane-associated data path. |
| 132-133 | 2 | lane output status | Output signal validity indications. |
| 134-153 | 20 | lane-specific flags | State changed, Tx, and Rx lane flags. |
| 154-201 | 48 | lane-specific monitors | Media-side optical power and laser bias monitors. |
| 202-205 | 4 | configuration status | Apply/configuration command status and result codes. |
| 206-234 | 29 | active control set | Provisioned application assignment and SI settings. |
| 235-239 | 5 | data path conditions | Dynamic condition indications. |
| 240-255 | 16 | media lane mapping | Mapping of media lanes to media wavelengths and fibers. |

## Field Notes

- Pair Page 11h with [upper-page-10h-register-map](upper-page-10h-register-map.md): Page 10h writes request changes; Page 11h reports the resulting state.
- Lane-specific monitors use CMIS multi-byte scalar encoding where applicable. Do not read two adjacent monitor bytes as a native little-endian integer.
- `ConfigStatus` and result codes are the main completion path for staged-control apply operations.
- Media lane mapping is bank-local. Hosts managing more than 8 lanes must combine the selected bank and lane index.

## C Register View

The overlay uses raw byte groups for live status areas. This avoids accidental native-endian interpretation on little-endian ARM while preserving exact register offsets.

```c
#ifndef CMIS_5_4_PAGE_11H_H
#define CMIS_5_4_PAGE_11H_H

#include <stddef.h>
#include <stdint.h>

#if defined(__GNUC__) || defined(__clang__)
#define CMIS_PACKED __attribute__((packed))
#else
#define CMIS_PACKED
#endif

typedef struct CMIS_PACKED {
    uint8_t DataPathStates[4];                           /* 11h:128-131 */
    uint8_t LaneOutputStatus[2];                         /* 11h:132-133 */
    uint8_t LaneSpecificFlags[20];                       /* 11h:134-153 */
    uint8_t LaneSpecificMonitors[48];                    /* 11h:154-201 */
    uint8_t ConfigurationStatus[4];                      /* 11h:202-205 */
    uint8_t ActiveControlSet[29];                        /* 11h:206-234 */
    uint8_t DataPathConditions[5];                       /* 11h:235-239 */
    uint8_t MediaLaneToMediaWavelengthAndFiberMapping[16]; /* 11h:240-255 */
} cmis_5_4_page_11h_t;

#if defined(__STDC_VERSION__) && (__STDC_VERSION__ >= 201112L)
_Static_assert(sizeof(cmis_5_4_page_11h_t) == 128u, "CMIS Page 11h overlay must be 128 bytes");
_Static_assert(offsetof(cmis_5_4_page_11h_t, LaneSpecificFlags) == 6u, "11h:134 offset mismatch");
_Static_assert(offsetof(cmis_5_4_page_11h_t, ConfigurationStatus) == 74u, "11h:202 offset mismatch");
_Static_assert(offsetof(cmis_5_4_page_11h_t, MediaLaneToMediaWavelengthAndFiberMapping) == 112u, "11h:240 offset mismatch");
#endif

#endif /* CMIS_5_4_PAGE_11H_H */
```

## Source Anchors

- [oif-cmis-05-4](../sources/oif-cmis-05-4.md), section 8.14, "Banked Page 11h (Lane Status and Data Path Status)".
- Table 8-92, Page 11h overview.
- Tables 8-93 through 8-107, Page 11h state, flag, monitor, status, active-control, and mapping definitions.
- PDF pages 237-248 in the CMIS 5.4 source.
