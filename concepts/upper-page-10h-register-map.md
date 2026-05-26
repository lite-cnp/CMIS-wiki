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

This self-contained C view is embedded directly in the page so it is visible in Obsidian. It expands lane control into lane bitmap bitfields, staged-control-set structs, two-bit and nibble lane maps, and a named lane-mask block.

```c
#include <stddef.h>
#include <stdint.h>

#if defined(__GNUC__) || defined(__clang__)
#define CMIS_PACKED __attribute__((packed))
#else
#define CMIS_PACKED
#endif


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
        uint8_t Lane1 : 2;
        uint8_t Lane2 : 2;
        uint8_t Lane3 : 2;
        uint8_t Lane4 : 2;
    };
    uint8_t Raw;
} cmis_lane4_2bit_t;

typedef struct CMIS_PACKED {
    cmis_lane4_2bit_t Lane1To4;
    cmis_lane4_2bit_t Lane5To8;
} cmis_lane8_2bit_t;

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

typedef union CMIS_PACKED {
    struct {
        uint8_t ExplicitControl : 1;
        uint8_t DataPathID : 3;
        uint8_t AppSelCode : 4;
    };
    uint8_t Raw;
} cmis_dp_config_lane_t;

typedef struct CMIS_PACKED {
    cmis_lane8_bitmap_t ApplyDPInitLane;                  /* 10h:143 or 178 */
    cmis_lane8_bitmap_t ApplyImmediateLane;               /* 10h:144 or 179 */
    cmis_dp_config_lane_t DataPathConfig[8];              /* 10h:145-152 or 180-187 */
    cmis_lane8_bitmap_t AdaptiveInputEqEnableTx;          /* 10h:153 or 188 */
    cmis_lane8_2bit_t AdaptiveInputEqRecallTx;            /* 10h:154-155 or 189-190 */
    cmis_lane8_nibble_t HostControlledInputEqTargetTx;    /* 10h:156-159 or 191-194 */
    cmis_lane8_bitmap_t CDREnableTx;                      /* 10h:160 or 195 */
    cmis_lane8_bitmap_t CDRBypassRx;                      /* 10h:161 or 196 */
    cmis_lane8_nibble_t OutputEqPreCursorTargetRx;        /* 10h:162-165 or 197-200 */
    cmis_lane8_nibble_t OutputEqPostCursorTargetRx;       /* 10h:166-169 or 201-204 */
    cmis_lane8_nibble_t OutputAmplitudeTargetRx;          /* 10h:170-173 or 205-208 */
    cmis_lane8_bitmap_t OutputDisableTx;                  /* 10h:174 or 209 */
    cmis_lane8_bitmap_t OutputDisableRx;                  /* 10h:175 or 210 */
    cmis_lane8_bitmap_t ApplyImmediateTx;                 /* 10h:176 or 211 */
    cmis_lane8_bitmap_t ApplyImmediateRx;                 /* 10h:177 or 212 */
} cmis_page_10h_staged_control_set_t;

typedef struct CMIS_PACKED {
    cmis_lane8_bitmap_t DPStateChangedMask;               /* 10h:213 */
    cmis_lane8_bitmap_t FailureMaskTx;                    /* 10h:214 */
    cmis_lane8_bitmap_t LOSMaskTx;                        /* 10h:215 */
    cmis_lane8_bitmap_t CDRLOLMaskTx;                     /* 10h:216 */
    cmis_lane8_bitmap_t AdaptiveInputEqFailMaskTx;        /* 10h:217 */
    cmis_lane8_bitmap_t OpticalPowerHighAlarmMaskTx;      /* 10h:218 */
    cmis_lane8_bitmap_t OpticalPowerLowAlarmMaskTx;       /* 10h:219 */
    cmis_lane8_bitmap_t OpticalPowerHighWarningMaskTx;    /* 10h:220 */
    cmis_lane8_bitmap_t OpticalPowerLowWarningMaskTx;     /* 10h:221 */
    cmis_lane8_bitmap_t LaserBiasHighAlarmMaskTx;         /* 10h:222 */
    cmis_lane8_bitmap_t LaserBiasLowAlarmMaskTx;          /* 10h:223 */
    cmis_lane8_bitmap_t LaserBiasHighWarningMaskTx;       /* 10h:224 */
    cmis_lane8_bitmap_t LaserBiasLowWarningMaskTx;        /* 10h:225 */
    cmis_lane8_bitmap_t LOSMaskRx;                        /* 10h:226 */
    cmis_lane8_bitmap_t CDRLOLMaskRx;                     /* 10h:227 */
    cmis_lane8_bitmap_t OpticalPowerHighAlarmMaskRx;      /* 10h:228 */
    cmis_lane8_bitmap_t OpticalPowerLowAlarmMaskRx;       /* 10h:229 */
    cmis_lane8_bitmap_t OpticalPowerHighWarningMaskRx;    /* 10h:230 */
    cmis_lane8_bitmap_t OpticalPowerLowWarningMaskRx;     /* 10h:231 */
    cmis_lane8_bitmap_t OutputStatusChangedMaskRx;        /* 10h:232 */
} cmis_page_10h_lane_masks_t;

typedef struct CMIS_PACKED {
    cmis_lane8_bitmap_t DPDeinitLane;                     /* 10h:128 */
    cmis_lane8_bitmap_t InputPolarityFlipTx;              /* 10h:129 */
    cmis_lane8_bitmap_t OutputDisableTx;                  /* 10h:130 */
    cmis_lane8_bitmap_t AutoSquelchDisableTx;             /* 10h:131 */
    cmis_lane8_bitmap_t OutputSquelchForceTx;             /* 10h:132 */
    uint8_t Reserved133;                                  /* 10h:133 */
    cmis_lane8_bitmap_t AdaptiveInputEqFreezeTx;          /* 10h:134 */
    cmis_lane8_2bit_t AdaptiveInputEqStoreTx;             /* 10h:135-136 */
    cmis_lane8_bitmap_t OutputPolarityFlipRx;             /* 10h:137 */
    cmis_lane8_bitmap_t OutputDisableRx;                  /* 10h:138 */
    cmis_lane8_bitmap_t AutoSquelchDisableRx;             /* 10h:139 */
    uint8_t Reserved140To142[3];                          /* 10h:140-142 */
    cmis_page_10h_staged_control_set_t StagedControlSet0; /* 10h:143-177 */
    cmis_page_10h_staged_control_set_t StagedControlSet1; /* 10h:178-212 */
    cmis_page_10h_lane_masks_t LaneSpecificMasks;         /* 10h:213-232 */
    uint8_t Reserved233To239[7];                          /* 10h:233-239 */
    uint8_t Custom240To255[16];                           /* 10h:240-255 */
} cmis_5_4_page_10h_t;

_Static_assert(sizeof(cmis_lane8_bitmap_t) == 1u, "lane bitmap must be 1 byte");
_Static_assert(sizeof(cmis_lane8_2bit_t) == 2u, "2-bit lane map must be 2 bytes");
_Static_assert(sizeof(cmis_lane8_nibble_t) == 4u, "nibble lane map must be 4 bytes");
_Static_assert(sizeof(cmis_page_10h_staged_control_set_t) == 35u, "Page 10h staged set must be 35 bytes");
_Static_assert(sizeof(cmis_page_10h_lane_masks_t) == 20u, "Page 10h masks must be 20 bytes");
_Static_assert(sizeof(cmis_5_4_page_10h_t) == 128u, "Page 10h must be 128 bytes");
_Static_assert(offsetof(cmis_5_4_page_10h_t, StagedControlSet0) == 15u, "10h:143 offset mismatch");
```

## Source Anchors

- [oif-cmis-05-4](../sources/oif-cmis-05-4.md), section 8.13, "Banked Page 10h (Lane Control and Data Path Control)".
- Table 8-77, Page 10h overview.
- Tables 8-78 through 8-91, Page 10h control and mask definitions.
- PDF pages 221-234 in the CMIS 5.4 source.
