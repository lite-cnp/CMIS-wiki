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

The struct exposes Page 2Fh as a byte-accurate overlay. Use the masks below for control/status bits instead of relying on compiler bitfield layout.

```c
#ifndef CMIS_5_4_PAGE_2FH_H
#define CMIS_5_4_PAGE_2FH_H

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

static inline uint16_t CmisBe16ToU16(cmis_be16_t value)
{
    return (uint16_t)(((uint16_t)value.Msb << 8) | value.Lsb);
}

enum {
    CmisPage2FhVDMSupportMask = 0x03u,
    CmisPage2FhPowerSavingSupportMask = 0x04u,
    CmisPage2FhDutyCycleSupportMask = 0x08u,
    CmisPage2FhFreezeRequestMask = 0x80u,
    CmisPage2FhPowerSavingModeMask = 0x40u,
    CmisPage2FhMonitoringDutyCycleMask = 0x3Cu,
    CmisPage2FhFreezeDoneMask = 0x80u,
    CmisPage2FhUnfreezeDoneMask = 0x40u
};

typedef struct CMIS_PACKED {
    uint8_t VDMAdvertisement;        /* 2Fh:128 */
    cmis_be16_t FineIntervalLength;  /* 2Fh:129-130 */
    uint8_t Reserved131_143[13];     /* 2Fh:131-143 */
    uint8_t DynamicControls;         /* 2Fh:144 */
    uint8_t DynamicStatus;           /* 2Fh:145 */
    uint8_t Reserved146_255[110];    /* 2Fh:146-255 */
} cmis_5_4_page_2fh_t;

#if defined(__STDC_VERSION__) && (__STDC_VERSION__ >= 201112L)
_Static_assert(sizeof(cmis_be16_t) == 2u, "CMIS BE16 wrapper must be 2 bytes");
_Static_assert(sizeof(cmis_5_4_page_2fh_t) == 128u, "CMIS Page 2Fh overlay must be 128 bytes");
_Static_assert(offsetof(cmis_5_4_page_2fh_t, FineIntervalLength) == 1u, "2Fh:129 offset mismatch");
_Static_assert(offsetof(cmis_5_4_page_2fh_t, DynamicControls) == 16u, "2Fh:144 offset mismatch");
_Static_assert(offsetof(cmis_5_4_page_2fh_t, DynamicStatus) == 17u, "2Fh:145 offset mismatch");
#endif

#endif /* CMIS_5_4_PAGE_2FH_H */
```

## Source Anchors

- [oif-cmis-05-4](../sources/oif-cmis-05-4.md), section 8.27.8, "Page 2Fh (VDM Advertisement and Dynamic Controls)".
- Table 8-177, summary of Page 20h-2Fh VDM page definitions.
- Table 8-186, VDM advertisement and control registers.
- PDF pages 310-312 in the CMIS 5.4 source.
