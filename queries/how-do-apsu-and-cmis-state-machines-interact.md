---
type: query
title: How do APSU and CMIS state machines interact?
created: 2026-05-25
updated: 2026-05-25
tags: [cmis, apsu, dpsm, npsm, query]
related: [autonomous-path-startup, data-path-state-machine, network-path-applications]
sources: [oif2026-093-08-802-3dj-apsu-draft, ieee-p802-3dj-d2-3]
status: draft
---

# How do APSU and CMIS state machines interact?

APSU does not replace the CMIS state machines. CMIS still configures module resources and transitions Data Paths or Network Paths through their normal management states. APSU starts only when the relevant interface is configured enough for IEEE 802.3dj RTS/ILT behavior to run.

## Short Answer

- MSM is unchanged.
- DPSM/NPSM remain configuration state machines.
- Host-interface APSU can start at DPInitialized.
- Media-interface APSU can start at DPTxTurnOn.
- DPActivated means CMIS configuration is complete, not that live Ethernet DATA is flowing.
- For APSU applications, live data depends on APSU completion, such as PATH_UP or the relevant RTS/ILT status.

## Host Implication

A host should combine base CMIS status with APSU status. Polling only DPSM is insufficient for APSU applications because the module can reach DPActivated while protocol-specific APSU work is still determining whether the path is ready for DATA mode.
