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

This self-contained C view is embedded directly in the page so it is visible in Obsidian. It exposes wavelength-grid support bytes as named bitfield unions and keeps channel range, fine-tuning, and output-power fields as explicit big-endian byte wrappers.

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

typedef union CMIS_PACKED {
    struct {
        uint8_t GridSupported3p125GHz : 1;
        uint8_t GridSupported6p25GHz : 1;
        uint8_t GridSupported12p5GHz : 1;
        uint8_t GridSupported25GHz : 1;
        uint8_t GridSupported50GHz : 1;
        uint8_t GridSupported100GHz : 1;
        uint8_t GridSupported33GHz : 1;
        uint8_t GridSupported75GHz : 1;
    };
    uint8_t Raw;
} cmis_page_04h_grid_support_128_t;

typedef union CMIS_PACKED {
    struct {
        uint8_t Reserved0To5 : 6;
        uint8_t GridSupported150GHz : 1;
        uint8_t FineTuningSupported : 1;
    };
    uint8_t Raw;
} cmis_page_04h_grid_support_129_t;

typedef struct CMIS_PACKED {
    cmis_page_04h_grid_support_128_t WavelengthGrids128;  /* 04h:128 */
    cmis_page_04h_grid_support_129_t WavelengthGrids129;  /* 04h:129 */
    cmis_be16_t GridLowChannel3p125GHz;                   /* 04h:130-131 */
    cmis_be16_t GridHighChannel3p125GHz;                  /* 04h:132-133 */
    cmis_be16_t GridLowChannel6p25GHz;                    /* 04h:134-135 */
    cmis_be16_t GridHighChannel6p25GHz;                   /* 04h:136-137 */
    cmis_be16_t GridLowChannel12p5GHz;                    /* 04h:138-139 */
    cmis_be16_t GridHighChannel12p5GHz;                   /* 04h:140-141 */
    cmis_be16_t GridLowChannel25GHz;                      /* 04h:142-143 */
    cmis_be16_t GridHighChannel25GHz;                     /* 04h:144-145 */
    cmis_be16_t GridLowChannel50GHz;                      /* 04h:146-147 */
    cmis_be16_t GridHighChannel50GHz;                     /* 04h:148-149 */
    cmis_be16_t GridLowChannel100GHz;                     /* 04h:150-151 */
    cmis_be16_t GridHighChannel100GHz;                    /* 04h:152-153 */
    cmis_be16_t GridLowChannel33GHz;                      /* 04h:154-155 */
    cmis_be16_t GridHighChannel33GHz;                     /* 04h:156-157 */
    cmis_be16_t GridLowChannel75GHz;                      /* 04h:158-159 */
    cmis_be16_t GridHighChannel75GHz;                     /* 04h:160-161 */
    cmis_be16_t GridLowChannel150GHz;                     /* 04h:162-163 */
    cmis_be16_t GridHighChannel150GHz;                    /* 04h:164-165 */
    cmis_be16_t GridLowChannel300GHz;                     /* 04h:166-167 */
    cmis_be16_t GridHighChannel300GHz;                    /* 04h:168-169 */
    uint8_t Reserved170To189[20];                         /* 04h:170-189 */
    cmis_be16_t FineTuningResolution;                     /* 04h:190-191 */
    cmis_be16_t FineTuningLowOffset;                      /* 04h:192-193 */
    cmis_be16_t FineTuningHighOffset;                     /* 04h:194-195 */
    uint8_t FineTuningAndPowerSupport196;                 /* 04h:196 */
    uint8_t Reserved197;                                  /* 04h:197 */
    cmis_be16_t ProgOutputPowerMin;                       /* 04h:198-199 */
    cmis_be16_t ProgOutputPowerMax;                       /* 04h:200-201 */
    uint8_t Reserved202To254[53];                         /* 04h:202-254 */
    uint8_t PageChecksum;                                 /* 04h:255 */
} cmis_5_4_page_04h_t;

_Static_assert(sizeof(cmis_be16_t) == 2u, "cmis_be16_t must be 2 bytes");
_Static_assert(sizeof(cmis_5_4_page_04h_t) == 128u, "Page 04h must be 128 bytes");
_Static_assert(offsetof(cmis_5_4_page_04h_t, PageChecksum) == 127u, "04h:255 offset mismatch");
```

## Source Anchors

- [oif-cmis-05-4](../sources/oif-cmis-05-4.md), section 8.7, "Page 04h (Laser Capabilities Advertising)".
- Table 8-67, Page 04h overview.
- Table 8-68, laser capabilities for tunable lasers.
- PDF pages 214-216 in the CMIS 5.4 source.
