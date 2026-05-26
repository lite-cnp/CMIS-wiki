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

This self-contained C view is embedded directly in the page so it is visible in Obsidian. It expands diagnostics control into capability bitfields, pattern ID enums, per-lane generator/checker control bitmaps, pattern-select nibbles, measurement-control fields, loopback bitmaps, and diagnostics masks.

```c
#include <stddef.h>
#include <stdint.h>

#if defined(__GNUC__) || defined(__clang__)
#define CMIS_PACKED __attribute__((packed))
#else
#define CMIS_PACKED
#endif


typedef struct CMIS_PACKED {
    uint8_t Lsb;
    uint8_t Msb;
} cmis_le16_t;

typedef union CMIS_PACKED {
    struct {
        uint8_t Lane1 : 1;
        uint8_t Lane2 : 1;
        uint8_t Lane3 : 1;
        uint8_t Lane4 : 1;
        uint8_t Lane5 : 1;
        uint8_t Lane6 : 1;
        uint8_t Lane7 : 1;
        uint8_t Lane8 : 1;
    };
    uint8_t Raw;
} cmis_lane8_bitmap_t;

typedef union CMIS_PACKED {
    struct {
        uint8_t OddLane : 4;
        uint8_t EvenLane : 4;
    };
    uint8_t Raw;
} cmis_lane_pair_nibble_t;

typedef struct CMIS_PACKED {
    cmis_lane_pair_nibble_t Lane1To2;
    cmis_lane_pair_nibble_t Lane3To4;
    cmis_lane_pair_nibble_t Lane5To6;
    cmis_lane_pair_nibble_t Lane7To8;
} cmis_lane8_nibble_t;

typedef enum {
    CmisPatternPRBS31Q = 0x0,
    CmisPatternPRBS31 = 0x1,
    CmisPatternPRBS23Q = 0x2,
    CmisPatternPRBS23 = 0x3,
    CmisPatternPRBS15Q = 0x4,
    CmisPatternPRBS15 = 0x5,
    CmisPatternPRBS13Q = 0x6,
    CmisPatternPRBS13 = 0x7,
    CmisPatternPRBS9Q = 0x8,
    CmisPatternPRBS9 = 0x9,
    CmisPatternPRBS7Q = 0xA,
    CmisPatternPRBS7 = 0xB,
    CmisPatternSSPRQ = 0xC,
    CmisPatternCustom = 0xE,
    CmisPatternUserPattern = 0xF
} cmis_pattern_id_t;

typedef union CMIS_PACKED {
    struct {
        uint8_t MediaSideOutputLoopback : 1;
        uint8_t MediaSideInputLoopback : 1;
        uint8_t HostSideOutputLoopback : 1;
        uint8_t HostSideInputLoopback : 1;
        uint8_t PerLaneHostSideLoopbacks : 1;
        uint8_t PerLaneMediaSideLoopbacks : 1;
        uint8_t SimultaneousHostAndMediaSideLoopbacks : 1;
        uint8_t Reserved : 1;
    };
    uint8_t Raw;
} cmis_page_13h_loopback_capabilities_t;

typedef union CMIS_PACKED {
    struct {
        uint8_t Reserved0To1 : 2;
        uint8_t AutoRestartGatingSupported : 1;
        uint8_t PerLaneGatingTimersSupported : 1;
        uint8_t PeriodicUpdatesSupported : 1;
        uint8_t GatingResultsSupported : 1;
        uint8_t GatingSupport : 2;
    };
    uint8_t Raw;
} cmis_page_13h_measurement_capabilities_t;

typedef union CMIS_PACKED {
    struct {
        uint8_t BitErrorRatioResultsSupported : 1;
        uint8_t BitsAndErrorsCountingSupported : 1;
        uint8_t Reserved2To3 : 2;
        uint8_t HostSideInputSNRMeasurement : 1;
        uint8_t MediaSideInputSNRMeasurement : 1;
        uint8_t HostSideFEC : 1;
        uint8_t MediaSideFEC : 1;
    };
    uint8_t Raw;
} cmis_page_13h_reporting_capabilities_t;

typedef union CMIS_PACKED {
    struct {
        uint8_t PRBSCheckerHostSidePostFEC : 1;
        uint8_t PRBSCheckerHostSidePreFEC : 1;
        uint8_t PRBSGeneratorHostSidePostFEC : 1;
        uint8_t PRBSGeneratorHostSidePreFEC : 1;
        uint8_t PRBSCheckerMediaSidePostFEC : 1;
        uint8_t PRBSCheckerMediaSidePreFEC : 1;
        uint8_t PRBSGeneratorMediaSidePostFEC : 1;
        uint8_t PRBSGeneratorMediaSidePreFEC : 1;
    };
    uint8_t Raw;
} cmis_page_13h_pattern_locations_t;

typedef struct CMIS_PACKED {
    cmis_le16_t HostSideGeneratorSupportsPattern;         /* 13h:132-133 */
    cmis_le16_t MediaSideGeneratorSupportsPattern;        /* 13h:134-135 */
    cmis_le16_t HostSideCheckerSupportsPattern;           /* 13h:136-137 */
    cmis_le16_t MediaSideCheckerSupportsPattern;          /* 13h:138-139 */
    uint8_t PatternOptions140;                            /* 13h:140 */
    uint8_t PatternSwapInvertCapabilities;                /* 13h:141 */
    uint8_t PerLanePatternCapabilities;                   /* 13h:142 */
} cmis_page_13h_pattern_capabilities_t;

typedef struct CMIS_PACKED {
    cmis_lane8_bitmap_t EnableLane;
    cmis_lane8_bitmap_t DataInvertLane;
    cmis_lane8_bitmap_t SwapSymbolBitsLane;
    cmis_lane8_bitmap_t FECSelectLane;
    cmis_lane8_nibble_t PatternSelectLane;
} cmis_page_13h_pattern_control_t;

typedef union CMIS_PACKED {
    struct {
        uint8_t MediaPRBSGeneratorClockSource : 4;
        uint8_t HostPRBSGeneratorClockSource : 4;
    };
    uint8_t Raw;
} cmis_page_13h_generator_clock_source_t;

typedef union CMIS_PACKED {
    struct {
        uint8_t UpdatePeriodSelect : 1;
        uint8_t MeasurementTime : 3;
        uint8_t AutoRestartGating : 1;
        uint8_t ResetErrorInformation : 1;
        uint8_t Reserved6 : 1;
        uint8_t StartStopIsGlobal : 1;
    };
    uint8_t Raw;
} cmis_page_13h_measurement_control_t;

typedef union CMIS_PACKED {
    struct {
        uint8_t MediaPRBSCheckerClockSource : 2;
        uint8_t HostPRBSCheckerClockSource : 2;
        uint8_t Reserved : 4;
    };
    uint8_t Raw;
} cmis_page_13h_checker_clock_source_t;

typedef struct CMIS_PACKED {
    union {
        struct {
            uint8_t Reserved : 7;
            uint8_t LossOfReferenceClockMask : 1;
        };
        uint8_t Raw;
    } LossOfReferenceClock;                              /* 13h:206 */
    uint8_t Reserved207;                                 /* 13h:207 */
    cmis_lane8_bitmap_t PatternCheckGatingCompleteMaskHostLane; /* 13h:208 */
    cmis_lane8_bitmap_t PatternCheckGatingCompleteMaskMediaLane; /* 13h:209 */
    cmis_lane8_bitmap_t PatternGeneratorLOLMaskHostLane; /* 13h:210 */
    cmis_lane8_bitmap_t PatternGeneratorLOLMaskMediaLane; /* 13h:211 */
    cmis_lane8_bitmap_t PatternCheckerLOLMaskHostLane;   /* 13h:212 */
    cmis_lane8_bitmap_t PatternCheckerLOLMaskMediaLane;  /* 13h:213 */
    uint8_t Reserved214To223[10];                        /* 13h:214-223 */
} cmis_page_13h_diagnostics_masks_t;

typedef struct CMIS_PACKED {
    cmis_page_13h_loopback_capabilities_t LoopbackCapabilities; /* 13h:128 */
    cmis_page_13h_measurement_capabilities_t DiagnosticsMeasurementCapabilities; /* 13h:129 */
    cmis_page_13h_reporting_capabilities_t DiagnosticReportingCapabilities; /* 13h:130 */
    cmis_page_13h_pattern_locations_t PatternGenerationAndCheckingLocations; /* 13h:131 */
    cmis_page_13h_pattern_capabilities_t PatternGenerationAndCheckingCapabilities; /* 13h:132-142 */
    uint8_t Reserved143;                                  /* 13h:143 */
    cmis_page_13h_pattern_control_t PatternGeneratorControlsHostSide; /* 13h:144-151 */
    cmis_page_13h_pattern_control_t PatternGeneratorControlsMediaSide; /* 13h:152-159 */
    cmis_page_13h_pattern_control_t PatternCheckerControlsHostSide; /* 13h:160-167 */
    cmis_page_13h_pattern_control_t PatternCheckerControlsMediaSide; /* 13h:168-175 */
    cmis_page_13h_generator_clock_source_t GeneratorClockSource; /* 13h:176 */
    cmis_page_13h_measurement_control_t MeasurementControl; /* 13h:177 */
    cmis_page_13h_checker_clock_source_t CheckerClockSource; /* 13h:178 */
    uint8_t Reserved179;                                  /* 13h:179 */
    cmis_lane8_bitmap_t MediaSideOutputLoopbackEnable;    /* 13h:180 */
    cmis_lane8_bitmap_t MediaSideInputLoopbackEnable;     /* 13h:181 */
    cmis_lane8_bitmap_t HostSideOutputLoopbackEnable;     /* 13h:182 */
    cmis_lane8_bitmap_t HostSideInputLoopbackEnable;      /* 13h:183 */
    uint8_t HostScratchpadArea[8];                        /* 13h:184-191 */
    uint8_t Reserved192To195[4];                          /* 13h:192-195 */
    uint8_t Custom196To205[10];                           /* 13h:196-205 */
    cmis_page_13h_diagnostics_masks_t DiagnosticsMasks;   /* 13h:206-223 */
    uint8_t UserPattern[32];                              /* 13h:224-255 */
} cmis_5_4_page_13h_t;

_Static_assert(sizeof(cmis_lane8_bitmap_t) == 1u, "lane bitmap must be 1 byte");
_Static_assert(sizeof(cmis_lane8_nibble_t) == 4u, "nibble lane map must be 4 bytes");
_Static_assert(sizeof(cmis_page_13h_pattern_control_t) == 8u, "Page 13h pattern controls must be 8 bytes");
_Static_assert(sizeof(cmis_page_13h_diagnostics_masks_t) == 18u, "Page 13h diagnostics masks must be 18 bytes");
_Static_assert(sizeof(cmis_5_4_page_13h_t) == 128u, "Page 13h must be 128 bytes");
_Static_assert(offsetof(cmis_5_4_page_13h_t, DiagnosticsMasks) == 78u, "13h:206 offset mismatch");
```

## Source Anchors

- [oif-cmis-05-4](../sources/oif-cmis-05-4.md), section 8.16, "Banked Page 13h (Module Performance Diagnostics Control)".
- Table 8-110, Page 13h overview.
- Tables 8-111 through 8-134, Page 13h capability, control, mask, scratchpad, and user-pattern definitions.
- PDF pages 253-273 in the CMIS 5.4 source.
