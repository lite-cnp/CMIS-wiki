---
type: concept
title: CMIS 5.4 Upper Page 10h Register Map
created: 2026-05-26
updated: 2026-05-26
tags: [cmis, memory-map, upper-memory, page-10h, banked, data-path, register-map]
related: [management-memory-map, control-sets, data-path-state-machine, upper-page-11h-register-map, cmis-5-4]
sources: [oif-cmis-05-4]
---

# CMIS 5.4 Upper Page 10h Register Map

Banked Page 10h contains lane control, data-path initialization control, staged control sets, and lane-specific interrupt masks. It is the main host-write page for data-path configuration.

## Addressing and Access Model

Select Page 10h with `PageSelect = 10h` and select the lane bank with `BankSelect`. Each bank covers up to 8 lanes. Struct offset 0 corresponds to register address `10h:128` in the selected bank.

Writes to this page can trigger configuration actions. Host software should stage fields, apply the correct trigger byte, then monitor Page 11h configuration status and data-path state.

## Byte-Range Overview

| Bytes | Size | Field Group | Host Use |
|---|---:|---|---|
| 128 | 1 | data path control | Per-lane `DPDeinit` control bits for associated data-path state machines. |
| 129-142 | 14 | lane-specific direct controls | Direct-effect lane controls independent of staged control sets. |
| 143-177 | 35 | staged control set 0 | Application assignment and signal-integrity controls for set 0. |
| 178-212 | 35 | staged control set 1 | Application assignment and signal-integrity controls for set 1. |
| 213-232 | 20 | lane-specific masks | Interrupt masks for lane-related flags. |
| 233-239 | 7 | reserved | Reserved. |
| 240-255 | 16 | custom | Vendor custom controls. |

## Field Notes

- `DataPathControl` controls deinitialization of the data-path state machines. It is separate from staged application assignment.
- Lane-specific direct controls include Tx/Rx output mute and lane signal-integrity fields that take effect without applying a staged control set.
- Staged control sets 0 and 1 let a host prepare an application assignment and SI controls, then apply them with trigger registers.
- Page 10h should be paired with [upper-page-11h-register-map](upper-page-11h-register-map.md) reads for `ConfigStatus`, result codes, active control set, and lane flags.
- Banked writes should respect any module support for bank broadcast and the host's own lane ownership model.

## C Register View

The overlay is intentionally byte grouped because most Page 10h fields are one-byte lane arrays or control bitmaps. Decode bit semantics with Table 8-78 through Table 8-91.

```c
#ifndef CMIS_5_4_PAGE_10H_H
#define CMIS_5_4_PAGE_10H_H

#include <stddef.h>
#include <stdint.h>

#if defined(__GNUC__) || defined(__clang__)
#define CMIS_PACKED __attribute__((packed))
#else
#define CMIS_PACKED
#endif

typedef struct CMIS_PACKED {
    uint8_t DataPathControl;              /* 10h:128 */
    uint8_t LaneSpecificControlFields[14];/* 10h:129-142 */
    uint8_t StagedControlSet0[35];        /* 10h:143-177 */
    uint8_t StagedControlSet1[35];        /* 10h:178-212 */
    uint8_t LaneSpecificMasks[20];        /* 10h:213-232 */
    uint8_t Reserved233_239[7];           /* 10h:233-239 */
    uint8_t Custom240_255[16];            /* 10h:240-255 */
} cmis_5_4_page_10h_t;

#if defined(__STDC_VERSION__) && (__STDC_VERSION__ >= 201112L)
_Static_assert(sizeof(cmis_5_4_page_10h_t) == 128u, "CMIS Page 10h overlay must be 128 bytes");
_Static_assert(offsetof(cmis_5_4_page_10h_t, StagedControlSet0) == 15u, "10h:143 offset mismatch");
_Static_assert(offsetof(cmis_5_4_page_10h_t, StagedControlSet1) == 50u, "10h:178 offset mismatch");
_Static_assert(offsetof(cmis_5_4_page_10h_t, LaneSpecificMasks) == 85u, "10h:213 offset mismatch");
#endif

#endif /* CMIS_5_4_PAGE_10H_H */
```

## Source Anchors

- [oif-cmis-05-4](../sources/oif-cmis-05-4.md), section 8.13, "Banked Page 10h (Lane Control and Data Path Control)".
- Table 8-77, Page 10h overview.
- Tables 8-78 through 8-91, Page 10h control and mask definitions.
- PDF pages 221-234 in the CMIS 5.4 source.
