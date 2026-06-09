---
type: concept
title: CMIS-VCS Upper Page 19h Register Map
created: 2026-05-26
updated: 2026-05-26
tags: [cmis, vcs, memory-map, upper-memory, page-19h, control-sets, register-map]
related: [cmis-versatile-control-set, upper-page-11h-register-map, upper-page-18h-register-map, control-sets, management-memory-map]
sources: [oif-cmis-vcs-01-1, oif-cmis-05-4]
---

# CMIS-VCS Upper Page 19h Register Map

Page 19h is the CMIS-VCS overflow page for read-only active Control Set signal-integrity parameters. It extends the active Control Set memory space on [upper-page-11h-register-map](upper-page-11h-register-map.md) when a module's VCS descriptor requires additional active-status space.

## Addressing and Access Model

Select Page 19h with `PageSelect = 19h` and select the same lane bank model used by Pages 10h and 11h. CMIS base classifies Page 19h as a lane/Data Path status extension page for an 8-lane group, with up to 32 banks.

Hosts should treat Page 19h as read-only VCS status/active-control space:

- Use [command-data-block](command-data-block.md) CMD `0045h` to check externally defined VCS support.
- Use CMIS-VCS CMD `4000h` to determine whether overflow pages are required and whether read-only VCS parameters are supported.
- Use CMD `4001h` to map read-write parameters into the active Control Set with the same offsets used by the staged sets.
- Use CMD `4002h` when read-only VCS parameter support is advertised; read-only parameters appear only in the active Control Set memory space after the read-write parameters.

## Byte-Range Overview

| Bytes | Size | Field Group | Host Use |
|---|---:|---|---|
| 128-151 | 24 | not assigned by CMIS-VCS | Page 19h bytes outside the Table 4-1 active overflow window. Do not treat these bytes as VCS parameter space unless another source defines them. |
| 152-207 | 56 | `ActiveControlSetOverflow` | Read-only overflow region for the active Control Set after the Page 11h active SI-status window is filled. |
| 208-255 | 48 | not assigned by CMIS-VCS | Page 19h bytes outside the CMIS-VCS active overflow allocation. |

## Field Notes

- Page 19h does not have fixed per-byte parameter meanings in CMIS-VCS. The field layout is descriptor-defined by the TLV streams returned by CMD `4001h` and, when supported, CMD `4002h`.
- Read-write VCS parameters appear at the same register offsets in Staged Control Set 0, Staged Control Set 1, and the Active Control Set. This lets a host compare provisioned and active values by using the same descriptor-derived offsets.
- Read-only VCS parameters are active-only. They are placed after all read-write VCS parameters in active Control Set memory and are not represented on Page 18h staged overflow.
- The active Control Set base SI-status region is Page 11h bytes 214-234. Page 19h bytes 152-207 are used only after that region is filled.
- A VCS parameter must be fully contained within a page. Do not split one parameter across the Page 11h/Page 19h boundary.

## C Register View

This self-contained C view is embedded directly in the page so it is visible in Obsidian. It models the fixed Page 19h active overflow window and includes VCS parameter IDs plus the descriptor TLV header needed to interpret the raw active overflow bytes. The individual VCS parameter fields remain descriptor-defined, so raw byte windows are intentional here.

```c
#include <stddef.h>
#include <stdint.h>

#if defined(__GNUC__) || defined(__clang__)
#define CMIS_PACKED __attribute__((packed))
#else
#define CMIS_PACKED
#endif

typedef enum {
    CmisVcsParameterReservedSpaceIndicator = 0x00,
    CmisVcsParameterExplicitControlPerParam = 0x01,
    CmisVcsParameterAdaptiveInputEqEnableTx = 0x02,
    CmisVcsParameterAdaptiveInputEqRecallTx = 0x03,
    CmisVcsParameterHostControlledInputEqTargetTx = 0x04,
    CmisVcsParameterCDREnableTx = 0x05,
    CmisVcsParameterCDREnableRx = 0x06,
    CmisVcsParameterOutputEqPrePostCursorTargetRx = 0x07,
    CmisVcsParameterOutputAmplitudeTargetRx = 0x08,
    CmisVcsParameterHostControlledInputEqTargetNumericTx = 0x09,
    CmisVcsParameterOutputEqTargetNumericRx = 0x0A,
    CmisVcsParameterOutputPrecodingEnableRx = 0x0B,
    CmisVcsParameterInputPrecodingEnableTx = 0x0C,
    CmisVcsParameterOutputEqPrePostCursorCoeffRx = 0x0D,
    CmisVcsParameterOutputFineAmplitudeSettingRx = 0x0E,
    CmisVcsParameterHostChannelLossRx = 0x0F,
    CmisVcsParameterHostChannelLossTx = 0x10,
    CmisVcsParameterNonLinearCompensationTx = 0x11,
    CmisVcsParameterInputEqPrePostCursorCoeffTx = 0x12
} cmis_vcs_parameter_id_t;

typedef struct CMIS_PACKED {
    uint8_t VcsParameterID;
    uint8_t VcsParameterLength;
} cmis_vcs_parameter_tlv_header_t;

typedef struct CMIS_PACKED {
    uint8_t Bytes[56];
} cmis_vcs_active_overflow_region_t;

typedef struct CMIS_PACKED {
    uint8_t Reserved128To151[24];                         /* 19h:128-151 */
    cmis_vcs_active_overflow_region_t ActiveControlSetOverflow; /* 19h:152-207 */
    uint8_t Reserved208To255[48];                         /* 19h:208-255 */
} cmis_vcs_page_19h_t;

static inline const uint8_t *CmisVcsPage19HActiveOverflow(const cmis_vcs_page_19h_t *Page)
{
    return Page->ActiveControlSetOverflow.Bytes;
}

_Static_assert(sizeof(cmis_vcs_parameter_tlv_header_t) == 2u, "VCS TLV header must be 2 bytes");
_Static_assert(sizeof(cmis_vcs_active_overflow_region_t) == 56u, "VCS active overflow region must be 56 bytes");
_Static_assert(sizeof(cmis_vcs_page_19h_t) == 128u, "CMIS-VCS Page 19h overlay must be 128 bytes");
_Static_assert(offsetof(cmis_vcs_page_19h_t, ActiveControlSetOverflow) == 24u, "19h:152 offset mismatch");
```

## Source Anchors

- [oif-cmis-vcs-01-1](../sources/oif-cmis-vcs-01-1.md), section 4.4, "Memory Map".
- Table 4-1, CMIS base Control Set Memory Map.
- Sections 4.3, 4.4, 4.7, and 6.1 through 6.5 for VCS advertisement, overflow allocation, `ApplicationMask`, read-write descriptors, and read-only descriptors.
- Table 5-1, CMIS-VCS descriptors.
- Table 6-2, VCS CDB command overview.
- PDF pages 18-26 and 58-65 in the CMIS-VCS 01.1 source.
