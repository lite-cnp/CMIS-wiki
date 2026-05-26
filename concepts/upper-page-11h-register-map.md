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

This self-contained C view is embedded directly in the page so it is visible in Obsidian. It expands status bytes into DP-state nibbles, lane-status bitmaps, flag bitmaps, monitor big-endian wrappers, configuration-status nibbles, active-control-set fields, and media-lane mapping nibbles.

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

typedef enum {
    CmisDpStateReserved = 0x0,
    CmisDpStateDeactivatedOrUnusedLane = 0x1,
    CmisDpStateInit = 0x2,
    CmisDpStateDeinit = 0x3,
    CmisDpStateActivated = 0x4,
    CmisDpStateTxTurnOn = 0x5,
    CmisDpStateTxTurnOff = 0x6,
    CmisDpStateInitialized = 0x7
} cmis_dp_state_t;

typedef enum {
    CmisConfigUndefined = 0x0,
    CmisConfigSuccess = 0x1,
    CmisConfigRejected = 0x2,
    CmisConfigRejectedInvalidAppSel = 0x3,
    CmisConfigRejectedInvalidDataPath = 0x4,
    CmisConfigRejectedInvalidSI = 0x5,
    CmisConfigRejectedLanesInUse = 0x6,
    CmisConfigRejectedPartialDataPath = 0x7,
    CmisConfigRejectedNoEmulation = 0x8,
    CmisConfigInProgress = 0xC
} cmis_config_status_t;

typedef struct CMIS_PACKED {
    cmis_lane8_bitmap_t DPStateChangedFlag;               /* 11h:134 */
    cmis_lane8_bitmap_t FailureFlagTx;                    /* 11h:135 */
    cmis_lane8_bitmap_t LOSFlagTx;                        /* 11h:136 */
    cmis_lane8_bitmap_t CDRLOLFlagTx;                     /* 11h:137 */
    cmis_lane8_bitmap_t AdaptiveInputEqFailFlagTx;        /* 11h:138 */
    cmis_lane8_bitmap_t OpticalPowerHighAlarmFlagTx;      /* 11h:139 */
    cmis_lane8_bitmap_t OpticalPowerLowAlarmFlagTx;       /* 11h:140 */
    cmis_lane8_bitmap_t OpticalPowerHighWarningFlagTx;    /* 11h:141 */
    cmis_lane8_bitmap_t OpticalPowerLowWarningFlagTx;     /* 11h:142 */
    cmis_lane8_bitmap_t LaserBiasHighAlarmFlagTx;         /* 11h:143 */
    cmis_lane8_bitmap_t LaserBiasLowAlarmFlagTx;          /* 11h:144 */
    cmis_lane8_bitmap_t LaserBiasHighWarningFlagTx;       /* 11h:145 */
    cmis_lane8_bitmap_t LaserBiasLowWarningFlagTx;        /* 11h:146 */
    cmis_lane8_bitmap_t LOSFlagRx;                        /* 11h:147 */
    cmis_lane8_bitmap_t CDRLOLFlagRx;                     /* 11h:148 */
    cmis_lane8_bitmap_t OpticalPowerHighAlarmFlagRx;      /* 11h:149 */
    cmis_lane8_bitmap_t OpticalPowerLowAlarmFlagRx;       /* 11h:150 */
    cmis_lane8_bitmap_t OpticalPowerHighWarningFlagRx;    /* 11h:151 */
    cmis_lane8_bitmap_t OpticalPowerLowWarningFlagRx;     /* 11h:152 */
    cmis_lane8_bitmap_t OutputStatusChangedFlagRx;        /* 11h:153 */
} cmis_page_11h_lane_flags_t;

typedef struct CMIS_PACKED {
    cmis_dp_config_lane_t DPConfigLane[8];                /* 11h:206-213 */
    cmis_lane8_bitmap_t AdaptiveInputEqEnableTx;          /* 11h:214 */
    cmis_lane8_2bit_t AdaptiveInputEqRecalledTx;          /* 11h:215-216 */
    cmis_lane8_nibble_t HostControlledInputEqTargetTx;    /* 11h:217-220 */
    cmis_lane8_bitmap_t CDREnableTx;                      /* 11h:221 */
    cmis_lane8_bitmap_t CDREnableRx;                      /* 11h:222 */
    cmis_lane8_nibble_t OutputEqPreCursorTargetRx;        /* 11h:223-226 */
    cmis_lane8_nibble_t OutputEqPostCursorTargetRx;       /* 11h:227-230 */
    cmis_lane8_nibble_t OutputAmplitudeTargetRx;          /* 11h:231-234 */
} cmis_page_11h_active_control_set_t;

typedef union CMIS_PACKED {
    struct {
        uint8_t MediaLaneToFiberMapping : 4;
        uint8_t MediaLaneToWavelengthMapping : 4;
    };
    uint8_t Raw;
} cmis_page_11h_media_lane_mapping_t;

typedef struct CMIS_PACKED {
    cmis_lane8_nibble_t DPStateHostLane;                  /* 11h:128-131 */
    cmis_lane8_bitmap_t OutputStatusRx;                   /* 11h:132 */
    cmis_lane8_bitmap_t OutputStatusTx;                   /* 11h:133 */
    cmis_page_11h_lane_flags_t LaneSpecificFlags;         /* 11h:134-153 */
    cmis_be16_t OpticalPowerTx[8];                        /* 11h:154-169 */
    cmis_be16_t LaserBiasTx[8];                           /* 11h:170-185 */
    cmis_be16_t OpticalPowerRx[8];                        /* 11h:186-201 */
    cmis_lane8_nibble_t ConfigStatusLane;                 /* 11h:202-205 */
    cmis_page_11h_active_control_set_t ActiveControlSet;  /* 11h:206-234 */
    cmis_lane8_bitmap_t DPInitPendingLane;                /* 11h:235 */
    uint8_t Reserved236To239[4];                          /* 11h:236-239 */
    cmis_page_11h_media_lane_mapping_t MediaLaneMappingTx[8]; /* 11h:240-247 */
    cmis_page_11h_media_lane_mapping_t MediaLaneMappingRx[8]; /* 11h:248-255 */
} cmis_5_4_page_11h_t;

_Static_assert(sizeof(cmis_be16_t) == 2u, "cmis_be16_t must be 2 bytes");
_Static_assert(sizeof(cmis_lane8_bitmap_t) == 1u, "lane bitmap must be 1 byte");
_Static_assert(sizeof(cmis_lane8_2bit_t) == 2u, "2-bit lane map must be 2 bytes");
_Static_assert(sizeof(cmis_lane8_nibble_t) == 4u, "nibble lane map must be 4 bytes");
_Static_assert(sizeof(cmis_page_11h_lane_flags_t) == 20u, "Page 11h flags must be 20 bytes");
_Static_assert(sizeof(cmis_page_11h_active_control_set_t) == 29u, "Page 11h active control set must be 29 bytes");
_Static_assert(sizeof(cmis_5_4_page_11h_t) == 128u, "Page 11h must be 128 bytes");
_Static_assert(offsetof(cmis_5_4_page_11h_t, ActiveControlSet) == 78u, "11h:206 offset mismatch");
```

## Source Anchors

- [oif-cmis-05-4](../sources/oif-cmis-05-4.md), section 8.14, "Banked Page 11h (Lane Status and Data Path Status)".
- Table 8-92, Page 11h overview.
- Tables 8-93 through 8-107, Page 11h state, flag, monitor, status, active-control, and mapping definitions.
- PDF pages 237-248 in the CMIS 5.4 source.
