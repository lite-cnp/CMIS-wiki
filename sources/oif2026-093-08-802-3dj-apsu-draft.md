---
type: source
title: OIF 2026.093.08 802.3dj APSU Draft
created: 2026-05-25
updated: 2026-06-18
tags: [cmis, oif, draft, apsu, ieee-802-3dj, source]
related: [autonomous-path-startup, data-path-state-machine, network-path-applications, management-memory-map]
authors: [OIF Physical and Link Layer Working Group]
year: 2026
venue: OIF Draft Contribution
source_filename: oif2026.093.08.docx
source_note: Raw source file is not included in this wiki-only repository.
converted_markdown: raw/sources/markdown/oif2026.093.08.md
status: draft
---

# OIF 2026.093.08 802.3dj APSU Draft

This draft contribution specifies how CMIS can facilitate IEEE 802.3dj Autonomous Path Startup, or APSU, for CMIS-compliant modules.

## Scope

The draft focuses on CMIS awareness of APSU, the relationship between APSU and [data-path-state-machine](../concepts/data-path-state-machine.md) / [network-path-applications](../concepts/network-path-applications.md), multiple ILT instances, timers, access to Annex 178B variables, and APSU monitoring or troubleshooting through CMIS.

## Key Draft Decisions

- Changes are limited to data paths or interfaces with APSU support.
- Non-APSU applications must remain backward compatible.
- APSU and non-APSU applications may coexist in one module.
- The [module-state-machine](../concepts/module-state-machine.md) is unchanged.
- APSU intersects DPSM and NPSM transitions but remains protocol-specific and orthogonal to CMIS configuration state.
- Draft Page 70h is dedicated to APSU control and monitoring and is only valid for APSU applications.

## Page 70h Draft Allocation

| Byte Range | Subject |
|---|---|
| 128-131 | Interface-level APSU, ILT, and RTS control/status |
| 132-151 | Per-lane training pattern control |
| 152-191 | Media interface per-lane ILT control/status |
| 192-230 | Host interface per-lane ILT control/status |
| 231-255 | Reserved |

## Extraction Notes

- MarkItDown conversion succeeded on 2026-06-18 after installing the optional `markitdown[docx]` dependency.
- The generated Markdown cache is `CMIS/raw/sources/markdown/oif2026.093.08.md`.

## Wiki Entry Points

- [autonomous-path-startup](../concepts/autonomous-path-startup.md)
- [data-path-state-machine](../concepts/data-path-state-machine.md)
- [network-path-applications](../concepts/network-path-applications.md)
- [management-memory-map](../concepts/management-memory-map.md)
- [ieee-p802-3dj-d2-3](ieee-p802-3dj-d2-3.md)

Source anchors: working scope, introduction, DPSM relationship table, and Page 70h overview, OIF 2026.093.08.
