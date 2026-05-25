---
type: source
title: OIF-CMIS-05.4
created: 2026-05-25
updated: 2026-05-25
tags: [cmis, oif, specification, source]
related: [cmis-5-4, cmis-supplements, management-memory-map, command-data-block]
authors: [OIF Physical and Link Layer Working Group]
year: 2026
url: "https://www.oiforum.com/"
venue: OIF Implementation Agreement
source_filename: OIF-CMIS-05.4.pdf
source_note: Raw source file is not included in this wiki-only repository.
---

# OIF-CMIS-05.4

OIF-CMIS-05.4 is Revision 5.4 of the [[oasis-oif|OIF]] Common Management Interface Specification. It is now the current base-source page for this vault's CMIS wiki.

## Relationship to 5.3

Revision 5.4 states that CMIS 5.3 compliant host and module implementations are also CMIS 5.4 compliant, with possible exceptions for unmodified Network Path implementations that did not take the CMIS 5.x errata corrections.

Use [[cmis-5-3-to-5-4]] for the short delta map.

## Major 5.4 Themes

- Network Path errata integration and cleanup of [[network-path-applications]] terminology and register descriptions.
- Expanded application and lane scalability, including support for up to 255 Normalized Application Descriptor pages and up to 256 lanes.
- New named feature and option profile advertising, including a map of supported pages and features.
- Firmware Load Management consolidation and additional CDB firmware commands.
- Consolidated Performance Management handling with not-available processing.
- New acquisition counters, media lane switching support, relative optical power thresholds, 300 GHz grid option, and 12-bit Interface UID handling.
- Future-direction hooks for I3C-compatible MCI, IEEE 802.3dj in-band link training, and secure management.

## New Memory Pages

Revision 5.4 adds these notable page assignments:

| Page | Purpose |
|---|---|
| 0Ch | Module management, supported pages, and named features |
| 0Dh | Firmware management |
| 60h | Lane/Data Path management for fixed polarity inversion and reset acquisition counts |
| 61h | Lane/Data Path monitoring for Tx/Rx acquisition counters |
| 62h | Media lane warning and alarm thresholds for Tx output power |
| 6Dh | Media lane switching |

## Supplements Referenced

CMIS 5.4 explicitly describes the CMIS supplement family:

- [[cmis-versatile-control-set]] from OIF-CMIS-VCS-01.1.
- [[coherent-cmis]] from OIF-C-CMIS-01.4.
- [[cmis-form-factor-management]] from OIF-CMIS-FF-01.0.
- CMIS-LT for host-to-module electrical link training.
- [[elsfp-cmis]] from OIF-CMIS-ELSFP-01.0.

## Wiki Entry Points

- [[cmis-5-4]]
- [[cmis-document-family-map]]
- [[cmis-5-4-implementer-map]]
- [[management-memory-map]]
- [[cmis-supplements]]

Source anchors: revision history pages 11-12, section 1.1.2, section 1.2, section 1.3, Table 8-1, and referenced supplement list.
