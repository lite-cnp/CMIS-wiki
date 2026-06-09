---
type: concept
title: CMIS-VCS Upper Page 18h Register Map
created: 2026-05-26
updated: 2026-05-26
tags: [cmis, vcs, memory-map, upper-memory, page-18h, control-sets, register-map]
related: [cmis-versatile-control-set, upper-page-10h-register-map, upper-page-19h-register-map, control-sets, management-memory-map]
sources: [oif-cmis-vcs-01-1, oif-cmis-05-4]
---

# CMIS-VCS Upper Page 18h Register Map

Page 18h is the CMIS-VCS overflow page for writable staged Control Set signal-integrity parameters. It extends the staged Control Set memory spaces on [upper-page-10h-register-map](upper-page-10h-register-map.md) when a module's VCS descriptor does not fit in the base Page 10h SI-control fields.

## Addressing and Access Model

Select Page 18h with `PageSelect = 18h` and select the same lane bank model used by Pages 10h and 11h. CMIS base classifies Page 18h as a lane/Data Path configuration extension page for an 8-lane group, with up to 32 banks.

Hosts should use Page 18h only after VCS discovery:

- Use [command-data-block](command-data-block.md) CMD `0045h` to check externally defined VCS support.
- Use CMIS-VCS CMD `4000h` to read the VCS overview, including VCS version, `ApplicationMask` length, CMIS-base compatibility, overflow-page requirement, and read-only parameter support.
- Use CMD `4001h` to read the read-write VCS descriptor. The descriptor determines which fields occupy Page 10h and Page 18h.

## Byte-Range Overview

| Bytes | Size | Field Group | Host Use |
|---|---:|---|---|
| 128-143 | 16 | not assigned by CMIS-VCS | Page 18h bytes outside the Table 4-1 staged overflow windows. Do not treat these bytes as VCS parameter space unless another source defines them. |
| 144-199 | 56 | `StagedControlSet0Overflow` | Writable overflow region for Staged Control Set 0 after the Page 10h staged set 0 SI-control window is filled. |
| 200-255 | 56 | `StagedControlSet1Overflow` | Writable overflow region for Staged Control Set 1 after the Page 10h staged set 1 SI-control window is filled. |

## Field Notes

- Page 18h does not have fixed per-byte parameter meanings in CMIS-VCS. The field layout is descriptor-defined by the TLV stream returned by CMD `4001h`.
- The host calculates each VCS parameter offset by accumulating the advertised `MemoryLength` values in descriptor order.
- The Page 10h staged SI-control regions are filled before Page 18h overflow is used: Page 10h bytes 153-175 for staged set 0, then Page 18h bytes 144-199; Page 10h bytes 188-210 for staged set 1, then Page 18h bytes 200-255.
- A VCS parameter must be fully contained within a page. Do not split one parameter across the Page 10h/Page 18h boundary or across Page 18h windows.
- `ApplicationMask` determines which AppSel codes use a parameter, but it does not change the memory layout. Unsupported base-compatible locations are represented with `ReservedSpaceIndicator`.

## C Register View

This self-contained C view is embedded directly in the page so it is visible in Obsidian. It models the fixed Page 18h overflow windows and includes VCS parameter IDs plus the descriptor TLV header needed to interpret the raw overflow bytes. The individual VCS parameter fields remain descriptor-defined, so raw byte windows are intentional here.

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
} cmis_vcs_staged_overflow_region_t;

typedef struct CMIS_PACKED {
    uint8_t Reserved128To143[16];                         /* 18h:128-143 */
    cmis_vcs_staged_overflow_region_t StagedControlSet0Overflow; /* 18h:144-199 */
    cmis_vcs_staged_overflow_region_t StagedControlSet1Overflow; /* 18h:200-255 */
} cmis_vcs_page_18h_t;

static inline uint8_t *CmisVcsPage18HStagedOverflow(cmis_vcs_page_18h_t *Page, uint8_t StagedSet)
{
    return (StagedSet == 0u) ? Page->StagedControlSet0Overflow.Bytes : Page->StagedControlSet1Overflow.Bytes;
}

_Static_assert(sizeof(cmis_vcs_parameter_tlv_header_t) == 2u, "VCS TLV header must be 2 bytes");
_Static_assert(sizeof(cmis_vcs_staged_overflow_region_t) == 56u, "VCS staged overflow region must be 56 bytes");
_Static_assert(sizeof(cmis_vcs_page_18h_t) == 128u, "CMIS-VCS Page 18h overlay must be 128 bytes");
_Static_assert(offsetof(cmis_vcs_page_18h_t, StagedControlSet0Overflow) == 16u, "18h:144 offset mismatch");
_Static_assert(offsetof(cmis_vcs_page_18h_t, StagedControlSet1Overflow) == 72u, "18h:200 offset mismatch");
```

## Source Anchors

- [oif-cmis-vcs-01-1](../sources/oif-cmis-vcs-01-1.md), section 4.4, "Memory Map".
- Table 4-1, CMIS base Control Set Memory Map.
- Sections 4.3, 4.5, 4.7, and 6.1 through 6.4 for VCS advertisement, compatibility, `ApplicationMask`, and descriptor TLV handling.
- Table 5-1, CMIS-VCS descriptors.
- Table 6-2, VCS CDB command overview.
- PDF pages 18-26 and 58-64 in the CMIS-VCS 01.1 source.
