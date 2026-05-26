---
type: concept
title: CMIS 5.4 Upper Page 14h Register Map
created: 2026-05-26
updated: 2026-05-26
tags: [cmis, memory-map, upper-memory, page-14h, diagnostics, banked, register-map]
related: [management-memory-map, upper-page-13h-register-map, versatile-diagnostics-monitoring, cmis-5-4]
sources: [oif-cmis-05-4]
---

# CMIS 5.4 Upper Page 14h Register Map

Banked Page 14h contains module performance diagnostics results. A selector register chooses which result payload appears in bytes 192-255.

## Addressing and Access Model

Select Page 14h with `PageSelect = 14h` and select the bank with `BankSelect` when the page is banked. Struct offset 0 corresponds to register address `14h:128` in the selected bank.

Pages 13h and 14h are optional and advertised together by Page 01h. Page 14h may be banked, with each bank referring to up to 8 lanes.

## Byte-Range Overview

| Bytes | Size | Field Group | Host Use |
|---|---:|---|---|
| 128 | 1 | `DiagnosticsSelector` | Selects the content of diagnostics data bytes 192-255. |
| 129 | 1 | reserved | Reserved. |
| 130-131 | 2 | custom | Vendor custom selector-adjacent bytes. |
| 132-139 | 8 | diagnostics flags | Latched diagnostics flags. |
| 140-149 | 10 | reserved | Reserved. |
| 150-191 | 42 | reserved gap | Reserved in the 128-byte overlay before diagnostics data. |
| 192-255 | 64 | diagnostics data | Selector-dependent result payload. |

## Field Notes

- `DiagnosticsSelector` changes the meaning of bytes 192-255. Hosts must wait the diagnostics data content switch time before consuming the new payload.
- Selector values include real-time BER, gated BER, error counters, total-bit counters, and SNR payloads.
- Table 8-137 explicitly defines some selected diagnostics payloads as little-endian U64 or U16 values. This is an exception to the usual CMIS big-endian scalar rule.
- Diagnostics flags are latched. Masks for these flags live on [upper-page-13h-register-map](upper-page-13h-register-map.md) bytes 206-223.

## C Register View

The selected diagnostics payload is intentionally left as raw bytes because its endianness and layout depend on `DiagnosticsSelector`.

```c
#ifndef CMIS_5_4_PAGE_14H_H
#define CMIS_5_4_PAGE_14H_H

#include <stddef.h>
#include <stdint.h>

#if defined(__GNUC__) || defined(__clang__)
#define CMIS_PACKED __attribute__((packed))
#else
#define CMIS_PACKED
#endif

typedef struct CMIS_PACKED {
    uint8_t DiagnosticsSelector;  /* 14h:128 */
    uint8_t Reserved129;          /* 14h:129 */
    uint8_t Custom130_131[2];     /* 14h:130-131 */
    uint8_t DiagnosticsFlags[8];  /* 14h:132-139 */
    uint8_t Reserved140_149[10];  /* 14h:140-149 */
    uint8_t Reserved150_191[42];  /* 14h:150-191 */
    uint8_t DiagnosticsData[64];  /* 14h:192-255 */
} cmis_5_4_page_14h_t;

#if defined(__STDC_VERSION__) && (__STDC_VERSION__ >= 201112L)
_Static_assert(sizeof(cmis_5_4_page_14h_t) == 128u, "CMIS Page 14h overlay must be 128 bytes");
_Static_assert(offsetof(cmis_5_4_page_14h_t, DiagnosticsFlags) == 4u, "14h:132 offset mismatch");
_Static_assert(offsetof(cmis_5_4_page_14h_t, DiagnosticsData) == 64u, "14h:192 offset mismatch");
#endif

#endif /* CMIS_5_4_PAGE_14H_H */
```

## Source Anchors

- [oif-cmis-05-4](../sources/oif-cmis-05-4.md), section 8.17, "Banked Page 14h (Module Performance Diagnostics Results)".
- Table 8-135, Page 14h overview.
- Table 8-136, diagnostics selector register.
- Table 8-137, diagnostics selector options.
- Table 8-138, latched diagnostics flags.
- Table 8-139, diagnostics data.
- PDF pages 274-276 in the CMIS 5.4 source.
