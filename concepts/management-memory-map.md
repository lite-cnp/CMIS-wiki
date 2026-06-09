---
type: concept
title: Management Memory Map
created: 2026-05-25
updated: 2026-05-26
tags: [cmis, memory-map, pages, banks]
related: [register-access-layer, low-memory-register-map, upper-page-00h-register-map, upper-page-01h-register-map, upper-page-02h-register-map, upper-page-04h-register-map, upper-page-0dh-register-map, upper-page-10h-register-map, upper-page-11h-register-map, upper-page-12h-register-map, upper-page-13h-register-map, upper-page-14h-register-map, upper-page-18h-register-map, upper-page-19h-register-map, upper-page-2fh-register-map, command-data-block, versatile-diagnostics-monitoring, applications-and-data-paths, cmis-5-4]
sources: [oif-cmis-05-4, oif-cmis-05-3]
---

# Management Memory Map

The CMIS management memory map is a byte-organized address space exposed to the host through a 256-byte directly addressable window.

## Addressing Model

- **Lower Memory**: bytes 00h-7Fh, always directly addressable. See [low-memory-register-map](low-memory-register-map.md) for the detailed CMIS 5.4 byte map.
- **Upper Memory**: bytes 80h-FFh, dynamically mapped to selected pages and banks.
- **Page**: a 128-byte upper-memory view selected by page address.
- **Bank**: an additional selector used for lane groups, CDB instances, VDM groups, and larger data spaces.

## Required Support

All CMIS devices support Lower Memory and Page 00h. Paged memory modules additionally support required pages such as Page 01h, Page 02h, and Bank 0 of Pages 10h and 11h. CMIS 5.4 adds stronger advertised discovery for supported pages and named features.

## Important Page Groups

| Page Range | Purpose |
|---|---|
| 00h | [Administrative information](upper-page-00h-register-map.md) |
| 01h | [Advertising](upper-page-01h-register-map.md) |
| 02h | [Threshold information](upper-page-02h-register-map.md) |
| 04h | [Tunable laser capability advertising](upper-page-04h-register-map.md) |
| 05h | [cmis-form-factor-management](cmis-form-factor-management.md) registers |
| 0Ch | CMIS 5.4 supported pages and named features |
| 0Dh | [CMIS 5.4 firmware management](upper-page-0dh-register-map.md) |
| 10h-1Fh | Lane, data path, network path, diagnostics, extensions; see [upper-page-10h-register-map](upper-page-10h-register-map.md), [upper-page-11h-register-map](upper-page-11h-register-map.md), [upper-page-12h-register-map](upper-page-12h-register-map.md), [upper-page-13h-register-map](upper-page-13h-register-map.md), and [upper-page-14h-register-map](upper-page-14h-register-map.md) |
| 18h-19h | [cmis-versatile-control-set](cmis-versatile-control-set.md) overflow parameter space; see [Page 18h](upper-page-18h-register-map.md) and [Page 19h](upper-page-19h-register-map.md) |
| 1Ah-1Bh | [elsfp-cmis](elsfp-cmis.md) advertisements, flags, controls, and monitors |
| 20h-2Fh | [versatile-diagnostics-monitoring](versatile-diagnostics-monitoring.md), including [Page 2Fh VDM advertisement and dynamic control](upper-page-2fh-register-map.md) |
| 30h-4Fh | [coherent-cmis](coherent-cmis.md) registers |
| 60h-62h | CMIS 5.4 lane/Data Path management, monitoring, and media-lane Tx power thresholds |
| 6Dh | CMIS 5.4 media lane switching |
| 70h | Draft [autonomous-path-startup](autonomous-path-startup.md) control and monitoring page |
| 9Fh | [command-data-block](command-data-block.md) local command/reply page |
| A0h-AFh | CDB extended payload pages |
| B0h-FFh | Vendor-specific custom pages |

## Implementation Rules

Lane-banked pages group lanes in sets of eight. Bank 0 covers lanes 1-8, bank 1 covers lanes 9-16, bank 2 covers lanes 17-24, and bank 3 covers lanes 25-32.

CMIS 5.4 adds support for larger lane counts, so host code should not hard-code the older 32-lane assumption when a 5.4 module advertises larger capability.

Source anchors: CMIS 5.4 revision history, sections 8.1.1-8.1.4, Table 8-1, and supplement page references.
