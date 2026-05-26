---
type: concept
title: CMIS 5.4 Upper Page 2Fh Register Map
created: 2026-05-26
updated: 2026-05-26
tags: [cmis, memory-map, upper-memory, page-2fh, vdm, banked, register-map]
related: [management-memory-map, versatile-diagnostics-monitoring, cmis-5-4]
sources: [oif-cmis-05-4]
---

# CMIS 5.4 Upper Page 2Fh Register Map

Banked Page 2Fh advertises VDM group support and provides dynamic controls for freezing, unfreezing, and power-saving behavior of VDM statistics reporting.

## Addressing and Access Model

Select Page 2Fh with `PageSelect = 2Fh` and select the VDM bank with `BankSelect` where applicable. Struct offset 0 corresponds to register address `2Fh:128`.

Freezing or unfreezing in one supported bank is defined to occur across all supported banks. Host code should treat the freeze handshake as a multi-bank operation even when it polls a single bank.

## Byte-Range Overview

| Bytes | Size | Field Group | Host Use |
|---|---:|---|---|
| 128 | 1 | VDM support advertisement | Number of supported VDM groups plus support for duty cycle and power saving controls. |
| 129-130 | 2 | `FineIntervalLength` | U16 sampling period for statistics updates in 0.1 ms units. |
| 131-143 | 13 | reserved | Reserved. |
| 144 | 1 | dynamic controls | `FreezeRequest`, `PowerSavingMode`, and `MonitoringDutyCycle`. |
| 145 | 1 | dynamic status | `FreezeDone` and `UnfreezeDone` handshake bits. |
| 146-255 | 110 | reserved | Reserved. |

## Field Notes

- `VDMSupport` at `2Fh:128.1-0` advertises whether VDM group 1, groups 1-2, groups 1-3, or groups 1-4 are supported.
- `PowerSavingSupport` and `DutyCycleSupport` advertise whether the corresponding dynamic controls in byte 144 are valid.
- Raising `FreezeRequest` freezes statistics reporting registers so the host can read a consistent interval result. Clearing it allows reporting registers to update again.
- `FreezeDone` and `UnfreezeDone` are the pollable completion bits. Conservative hosts should combine polling with the specified timing guard.
- `FineIntervalLength` is a CMIS U16 and therefore big-endian in registers.

## C Register View

This self-contained C view is embedded directly in the page so it is visible in Obsidian. It exposes VDM group support, fine interval length, dynamic controls, and dynamic status as named fields including MonitoringDutyCycle, FreezeRequest, FreezeDone, and UnfreezeDone.

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

typedef enum {
    CmisVdmGroup1Supported = 0,
    CmisVdmGroups1To2Supported = 1,
    CmisVdmGroups1To3Supported = 2,
    CmisVdmGroups1To4Supported = 3
} cmis_vdm_support_t;

typedef union CMIS_PACKED {
    struct {
        uint8_t VDMSupport : 2;
        uint8_t PowerSavingSupport : 1;
        uint8_t DutyCycleSupport : 1;
        uint8_t Reserved : 4;
    };
    uint8_t Raw;
} cmis_page_2fh_vdm_advertisement_t;

typedef union CMIS_PACKED {
    struct {
        uint8_t Reserved0To1 : 2;
        uint8_t MonitoringDutyCycle : 4;
        uint8_t PowerSavingMode : 1;
        uint8_t FreezeRequest : 1;
    };
    uint8_t Raw;
} cmis_page_2fh_dynamic_controls_t;

typedef union CMIS_PACKED {
    struct {
        uint8_t Reserved0To5 : 6;
        uint8_t UnfreezeDone : 1;
        uint8_t FreezeDone : 1;
    };
    uint8_t Raw;
} cmis_page_2fh_dynamic_status_t;

typedef struct CMIS_PACKED {
    cmis_page_2fh_vdm_advertisement_t VDMAdvertisement;  /* 2Fh:128 */
    cmis_be16_t FineIntervalLength;                      /* 2Fh:129-130 */
    uint8_t Reserved131To143[13];                        /* 2Fh:131-143 */
    cmis_page_2fh_dynamic_controls_t DynamicControls;    /* 2Fh:144 */
    cmis_page_2fh_dynamic_status_t DynamicStatus;        /* 2Fh:145 */
    uint8_t Reserved146To255[110];                       /* 2Fh:146-255 */
} cmis_5_4_page_2fh_t;

_Static_assert(sizeof(cmis_be16_t) == 2u, "cmis_be16_t must be 2 bytes");
_Static_assert(sizeof(cmis_5_4_page_2fh_t) == 128u, "Page 2Fh must be 128 bytes");
_Static_assert(offsetof(cmis_5_4_page_2fh_t, DynamicControls) == 16u, "2Fh:144 offset mismatch");
```

## Source Anchors

- [oif-cmis-05-4](../sources/oif-cmis-05-4.md), section 8.27.8, "Page 2Fh (VDM Advertisement and Dynamic Controls)".
- Table 8-177, summary of Page 20h-2Fh VDM page definitions.
- Table 8-186, VDM advertisement and control registers.
- PDF pages 310-312 in the CMIS 5.4 source.
