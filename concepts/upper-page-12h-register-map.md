---
type: concept
title: CMIS 5.4 Upper Page 12h Register Map
created: 2026-05-26
updated: 2026-05-26
tags: [cmis, memory-map, upper-memory, page-12h, banked, tunable-laser, register-map]
related: [management-memory-map, upper-page-04h-register-map, applications-and-data-paths, cmis-5-4]
sources: [oif-cmis-05-4]
---

# CMIS 5.4 Upper Page 12h Register Map

Banked Page 12h contains tunable laser control, status, flags, and masks for up to 8 media lanes per bank. Page 04h advertises capability; Page 12h carries runtime values.

## Addressing and Access Model

Select Page 12h with `PageSelect = 12h` and select the media-lane bank with `BankSelect`. Struct offset 0 corresponds to register address `12h:128` in the selected bank.

Byte arrays with one byte per lane use the lowest byte address for lane 1 in the bank. Bit arrays use bit 0 for lane 1.

## Byte-Range Overview

| Bytes | Size | Field Group | Host Use |
|---|---:|---|---|
| 128-135 | 8 | grid spacings | One grid-spacing byte per media lane. |
| 136-151 | 16 | channel offset numbers | One S16 channel offset per media lane. |
| 152-167 | 16 | fine tuning offsets | One S16 fine-tuning offset per media lane. |
| 168-199 | 32 | laser frequencies | One U32 laser frequency per media lane. |
| 200-215 | 16 | target output power | One S16 target output power per media lane. |
| 216-221 | 6 | reserved | Reserved. |
| 222-229 | 8 | status indicators | One status byte per media lane. |
| 230 | 1 | flag summary | One bit per media lane. |
| 231-238 | 8 | flags | One flag byte per media lane. |
| 239-246 | 8 | masks | One mask byte per media lane; default masks are set. |
| 247-255 | 9 | reserved | Reserved. Page 12h has no page checksum. |

## Field Notes

- `ChannelOffsetNumbers`, `FineTuningOffsets`, `LaserFrequencies`, and `TargetOutputPower` are CMIS scalar values. Decode them as big-endian unless a table explicitly states a different order.
- Page 12h flag and mask arrays are lane-indexed. A host should compute lane number as `bank * 8 + lane_in_bank`.
- There is no Page 12h checksum. Hosts should rely on normal access timing and status/flag validation.

## C Register View

The multi-byte lane arrays use explicit big-endian wrappers so the overlay is safe on little-endian ARM.

```c
#ifndef CMIS_5_4_PAGE_12H_H
#define CMIS_5_4_PAGE_12H_H

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
    uint8_t Byte3;
    uint8_t Byte2;
    uint8_t Byte1;
    uint8_t Byte0;
} cmis_be32_t;

static inline uint16_t CmisBe16ToU16(cmis_be16_t value)
{
    return (uint16_t)(((uint16_t)value.Msb << 8) | value.Lsb);
}

static inline int16_t CmisBe16ToS16(cmis_be16_t value)
{
    return (int16_t)CmisBe16ToU16(value);
}

static inline uint32_t CmisBe32ToU32(cmis_be32_t value)
{
    return ((uint32_t)value.Byte3 << 24) |
           ((uint32_t)value.Byte2 << 16) |
           ((uint32_t)value.Byte1 << 8) |
           (uint32_t)value.Byte0;
}

typedef struct CMIS_PACKED {
    uint8_t GridSpacings[8];             /* 12h:128-135 */
    cmis_be16_t ChannelOffsetNumbers[8]; /* 12h:136-151 */
    cmis_be16_t FineTuningOffsets[8];    /* 12h:152-167 */
    cmis_be32_t LaserFrequencies[8];     /* 12h:168-199 */
    cmis_be16_t TargetOutputPower[8];    /* 12h:200-215 */
    uint8_t Reserved216_221[6];          /* 12h:216-221 */
    uint8_t StatusIndicators[8];         /* 12h:222-229 */
    uint8_t FlagSummary;                 /* 12h:230 */
    uint8_t Flags[8];                    /* 12h:231-238 */
    uint8_t Masks[8];                    /* 12h:239-246 */
    uint8_t Reserved247_255[9];          /* 12h:247-255 */
} cmis_5_4_page_12h_t;

#if defined(__STDC_VERSION__) && (__STDC_VERSION__ >= 201112L)
_Static_assert(sizeof(cmis_be16_t) == 2u, "CMIS BE16 wrapper must be 2 bytes");
_Static_assert(sizeof(cmis_be32_t) == 4u, "CMIS BE32 wrapper must be 4 bytes");
_Static_assert(sizeof(cmis_5_4_page_12h_t) == 128u, "CMIS Page 12h overlay must be 128 bytes");
_Static_assert(offsetof(cmis_5_4_page_12h_t, LaserFrequencies) == 40u, "12h:168 offset mismatch");
_Static_assert(offsetof(cmis_5_4_page_12h_t, FlagSummary) == 102u, "12h:230 offset mismatch");
#endif

#endif /* CMIS_5_4_PAGE_12H_H */
```

## Source Anchors

- [oif-cmis-05-4](../sources/oif-cmis-05-4.md), section 8.15, "Banked Page 12h (Tunable Laser Control and Status)".
- Table 8-108, Page 12h overview.
- Table 8-109, laser tuning, status, and flags for tunable transmitters.
- PDF page 250 in the CMIS 5.4 source.
