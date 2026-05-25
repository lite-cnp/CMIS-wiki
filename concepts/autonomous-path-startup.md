---
type: concept
title: Autonomous Path Startup
created: 2026-05-25
updated: 2026-05-25
tags: [cmis, ieee-802-3dj, apsu, ilt, rts, draft]
related: [sources/oif2026-093-08-802-3dj-apsu-draft, sources/ieee-p802-3dj-d2-3, data-path-state-machine, network-path-applications]
sources: [oif2026-093-08-802-3dj-apsu-draft, ieee-p802-3dj-d2-3]
status: draft
---

# Autonomous Path Startup

Autonomous Path Startup, or APSU, is the IEEE 802.3dj mechanism for coordinated startup of inter-sublayer links in a path. It is built from Ready-to-Send (RTS) and Inter-Sublayer Link Training (ILT) functions.

## IEEE Model

- APSU coordinates initialization across all ISLs in a path.
- RTS propagates readiness to transition an ISL to DATA mode.
- ILT establishes peer communication, optimizes signaling, and coordinates the transition to DATA mode.
- IEEE P802.3dj places the main APSU behavior in Annex 178B.

## CMIS Relationship

CMIS configures modules, applications, and data paths. APSU is protocol-specific behavior that starts after the relevant interface configuration is ready. The OIF APSU draft treats APSU as orthogonal to CMIS state machines:

- The [[module-state-machine]] is unchanged.
- Host-interface APSU can begin at DPInitialized.
- Media-interface APSU can begin at DPTxTurnOn.
- DPActivated means CMIS configuration is complete; live Ethernet DATA still depends on APSU completion.
- The same relationship applies to [[network-path-applications]] where NPSM is involved.

## Draft CMIS Register Model

The OIF draft assigns Page 70h for APSU control and monitoring. It includes interface-level control/status, training-pattern controls, media-side ILT status, and host-side ILT status.

## Host Rule

A host should not infer APSU completion from DPSM state alone. For APSU applications, use the APSU control/status fields in addition to the base CMIS state-machine and output-status fields.
