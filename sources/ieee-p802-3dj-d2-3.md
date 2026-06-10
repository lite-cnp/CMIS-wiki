---
type: source
title: IEEE P802.3dj D2.3
created: 2026-05-25
updated: 2026-05-25
tags: [ieee-802-3dj, ethernet, apsu, ilt, rts, source]
related: [autonomous-path-startup, sources/ieee-802-3-2022]
year: 2025
venue: IEEE Draft Amendment
source_filename: 8023dj_D2p3.pdf
source_note: Raw source file is available at CMIS/raw/sources/8023dj_D2p3.pdf in this workspace.
status: draft
---

# IEEE P802.3dj D2.3

IEEE P802.3dj D2.3 is a draft amendment for 200 Gb/s, 400 Gb/s, 800 Gb/s, and 1.6 Tb/s Ethernet. In this vault it is used primarily as the source for Autonomous Path Startup, ready-to-send, and inter-sublayer link training behavior referenced by the CMIS APSU draft.

## APSU Anchors

- Annex 178B defines APSU functions for electrical and optical interfaces.
- APSU is the coordinated, orderly initialization of inter-sublayer links in a path.
- APSU is facilitated by the Ready-to-Send function and the Inter-Sublayer Link Training function.
- RTS propagates readiness to transition an ISL to DATA mode.
- ILT establishes peer communication, optimizes signaling, and coordinates transition to DATA mode.
- Annex 178B treats an interface as an AUI component or a PMD, and an ISL as either a pair of AUI components plus AUI channel or a pair of PMDs plus medium.
- The common state-machine flow uses RTS update, training control, training frame lock, and coefficient update state diagrams; key states include `QUIET`, `TRAIN_LOCAL`, `TRAIN_REMOTE`, `ISL_READY`, `PATH_READY`, `PATH_UP`, `RECOVERY`, and `FAIL`.

## APSU/iLT Link Notes

- 200 Gb/s-per-lane AUI C2C and C2M components are functionally equivalent to the relevant PMD clauses and include ILT with E1 format plus RTS.
- Electrical PMD clauses such as KR/CR use E1-format training.
- Optical IMDD PMD clauses in the local draft's 180-183 family use O1-format training and coordinate modulation, training pattern, precoder state, receiver state, and transition to DATA.
- The CMIS/OIF overlay should not treat `DPActivated` as live-data readiness; APSU/iLT readiness remains a separate protocol gate.

## Wiki Entry Points

- [autonomous-path-startup](../concepts/autonomous-path-startup.md)
- [oif2026-093-08-802-3dj-apsu-draft](oif2026-093-08-802-3dj-apsu-draft.md)
- [ieee-802-3-2022](ieee-802-3-2022.md)
- [standard-apsu-ilt-procedure-host-vs-media-links](../queries/standard-apsu-ilt-procedure-host-vs-media-links.md)

Source anchors: clauses 116.2.9, 169.2.10, 174.2.12, 178.8.9, 179.8.9, 180.5.12, 181.5.12, 182.5.12, 183.5.12, and Annex 178B.
