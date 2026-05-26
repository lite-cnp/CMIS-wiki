---
type: concept
title: CMIS 5.4 Upper Page 13h Register Map
created: 2026-05-26
updated: 2026-05-26
tags: [cmis, memory-map, upper-memory, page-13h, diagnostics, banked, register-map]
related: [management-memory-map, upper-page-14h-register-map, versatile-diagnostics-monitoring, cmis-5-4]
sources: [oif-cmis-05-4]
---

# CMIS 5.4 Upper Page 13h Register Map

Banked Page 13h contains module performance diagnostics advertisements and controls: loopback capability, diagnostic measurement capability, pattern generator/checker support, generator/checker controls, measurement controls, loopback controls, diagnostics masks, and a user pattern.

## Addressing and Access Model

Select Page 13h with `PageSelect = 13h` and select the bank with `BankSelect`. Struct offset 0 corresponds to register address `13h:128` in the selected bank.

Pages 13h and 14h are optional and are advertised jointly by Page 01h. Page 13h is the control side; [upper-page-14h-register-map](upper-page-14h-register-map.md) is the result side.

## Byte-Range Overview

| Bytes | Size | Field Group | Host Use |
|---|---:|---|---|
| 128 | 1 | loopback capabilities | Diagnostics loopback capability advertisement. |
| 129 | 1 | diagnostics measurement capabilities | Supported measurement behavior. |
| 130 | 1 | diagnostic reporting capabilities | Supported reporting options. |
| 131 | 1 | pattern generation/checking locations | Where generators and checkers can be placed. |
| 132-142 | 11 | pattern capabilities | Pattern generator/checker PRBS, swap, and invert capabilities. |
| 143 | 1 | reserved | Reserved for module advertisements. |
| 144-151 | 8 | host-side pattern generator controls | Per-host-lane generator controls. |
| 152-159 | 8 | media-side pattern generator controls | Per-media-lane generator controls. |
| 160-167 | 8 | host-side pattern checker controls | Per-host-lane checker controls. |
| 168-175 | 8 | media-side pattern checker controls | Per-media-lane checker controls. |
| 176-179 | 4 | clocking and measurement controls | Clock and measurement behavior controls. |
| 180-183 | 4 | loopback controls | Loopback control registers. |
| 184-191 | 8 | host scratchpad area | Host state storage for restart detection. |
| 192-195 | 4 | reserved | Reserved. |
| 196-205 | 10 | custom | Vendor custom diagnostics controls. |
| 206-223 | 18 | diagnostics flag masks | Masks for Page 14h diagnostics flags. |
| 224-255 | 32 | user pattern | User-defined 32-byte test pattern. |

## Field Notes

- Pattern generator/checker support is optional. Hosts should check capability bits before enabling controls.
- The diagnostics flag masks at bytes 206-223 correspond to Page 14h flag bytes.
- `HostScratchpadArea` is host-owned storage exposed by the module. It is useful for detecting module resets or host state loss but should not be treated as non-volatile storage.
- `UserPattern` provides the 32-byte pattern used by supported user-pattern diagnostics modes.

## C Register View

Most Page 13h controls are byte-granular lane arrays or masks. The struct keeps them as byte arrays to avoid implementation-defined bitfield layout assumptions.

```c
#ifndef CMIS_5_4_PAGE_13H_H
#define CMIS_5_4_PAGE_13H_H

#include <stddef.h>
#include <stdint.h>

#if defined(__GNUC__) || defined(__clang__)
#define CMIS_PACKED __attribute__((packed))
#else
#define CMIS_PACKED
#endif

typedef struct CMIS_PACKED {
    uint8_t LoopbackCapabilities;                         /* 13h:128 */
    uint8_t DiagnosticsMeasurementCapabilities;           /* 13h:129 */
    uint8_t DiagnosticReportingCapabilities;              /* 13h:130 */
    uint8_t PatternGenerationAndCheckingLocations;        /* 13h:131 */
    uint8_t PatternGenerationAndCheckingCapabilities[11]; /* 13h:132-142 */
    uint8_t Reserved143;                                  /* 13h:143 */
    uint8_t PatternGeneratorControlsHostSide[8];          /* 13h:144-151 */
    uint8_t PatternGeneratorControlsMediaSide[8];         /* 13h:152-159 */
    uint8_t PatternCheckerControlsHostSide[8];            /* 13h:160-167 */
    uint8_t PatternCheckerControlsMediaSide[8];           /* 13h:168-175 */
    uint8_t ClockingAndMeasurementControls[4];            /* 13h:176-179 */
    uint8_t LoopbackControls[4];                          /* 13h:180-183 */
    uint8_t HostScratchpadArea[8];                        /* 13h:184-191 */
    uint8_t Reserved192_195[4];                           /* 13h:192-195 */
    uint8_t Custom196_205[10];                            /* 13h:196-205 */
    uint8_t DiagnosticsFlagMasks[18];                     /* 13h:206-223 */
    uint8_t UserPattern[32];                              /* 13h:224-255 */
} cmis_5_4_page_13h_t;

#if defined(__STDC_VERSION__) && (__STDC_VERSION__ >= 201112L)
_Static_assert(sizeof(cmis_5_4_page_13h_t) == 128u, "CMIS Page 13h overlay must be 128 bytes");
_Static_assert(offsetof(cmis_5_4_page_13h_t, PatternGeneratorControlsHostSide) == 16u, "13h:144 offset mismatch");
_Static_assert(offsetof(cmis_5_4_page_13h_t, DiagnosticsFlagMasks) == 78u, "13h:206 offset mismatch");
_Static_assert(offsetof(cmis_5_4_page_13h_t, UserPattern) == 96u, "13h:224 offset mismatch");
#endif

#endif /* CMIS_5_4_PAGE_13H_H */
```

## Source Anchors

- [oif-cmis-05-4](../sources/oif-cmis-05-4.md), section 8.16, "Banked Page 13h (Module Performance Diagnostics Control)".
- Table 8-110, Page 13h overview.
- Tables 8-111 through 8-134, Page 13h capability, control, mask, scratchpad, and user-pattern definitions.
- PDF pages 253-273 in the CMIS 5.4 source.
