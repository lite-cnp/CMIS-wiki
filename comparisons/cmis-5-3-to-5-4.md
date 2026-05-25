---
type: comparison
title: CMIS 5.3 to CMIS 5.4
created: 2026-05-25
updated: 2026-05-25
tags: [cmis, comparison, revision]
related: [sources/oif-cmis-05-3, sources/oif-cmis-05-4, cmis-5-4]
sources: [oif-cmis-05-3, oif-cmis-05-4]
---

# CMIS 5.3 to CMIS 5.4

CMIS 5.4 is an incremental revision over CMIS 5.3. The specification states that CMIS 5.3 compliant hosts and modules are also CMIS 5.4 compliant, with possible exceptions around uncorrected Network Path behavior covered by CMIS 5.x errata.

## Main Deltas

| Area | 5.4 Change |
|---|---|
| Network Paths | Integrates NP errata and cleans related terminology/register text |
| Advertisements | Adds named features, option profiles, and supported-page maps |
| Scale | Expands NAD/application scaling and supports up to 256 lanes |
| Firmware | Consolidates firmware management and adds related CDB handling |
| Performance management | Adds consolidated PM handling with not-available processing |
| Lane management | Adds fixed polarity inversion, acquisition counters, and media lane switching |
| Optical controls | Adds programmable relative optical power thresholds and a 300 GHz grid option |
| CDB | Adds module time commands, an EPL variant of Get Application Attributes, and more interface attributes |
| Future direction | Calls out I3C-compatible MCI, IEEE 802.3dj in-band link training, and secure management |

## New 5.4 Pages

- 0Ch: supported pages and named features.
- 0Dh: firmware management.
- 60h: lane/Data Path management.
- 61h: lane/Data Path monitoring.
- 62h: media lane Tx output power thresholds.
- 6Dh: media lane switching.

## Practical Host Guidance

Keep CMIS 5.3 host behavior intact. Add CMIS 5.4 behavior as advertised capabilities, especially for named features, larger lane counts, new memory pages, and new CDB commands.
