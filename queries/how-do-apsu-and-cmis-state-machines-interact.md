---
type: query
title: How do APSU and CMIS state machines interact?
created: 2026-05-25
updated: 2026-06-09
tags: [cmis, apsu, dpsm, npsm, query]
related: [autonomous-path-startup, data-path-state-machine, network-path-applications, how-should-hosts-use-sian3-apsu-capi, apsu-ilt-customer-note-plan]
sources: [oif2026-093-08-802-3dj-apsu-draft, ieee-p802-3dj-d2-3, lumentum-2026-dpsm-apsu-ilt-state-machine, lumentum-2026-8023dj-apsu-ilt-support-plan, broadcom-2026-sian3-apsu-application-notes]
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

## Current Customer-Note Diagram

The Lumentum [DPSM APSU/iLT state-machine diagram](../sources/lumentum-2026-dpsm-apsu-ilt-state-machine.md) restates the rule in implementation form:

- APSU/iLT does not add DPSM states.
- MSM is unchanged.
- Host-side APSU/host iLT may begin at `DPInitialized`.
- Media-side APSU/media iLT may begin at `DPTxTurnOn`.
- `DPActivated` is a CMIS configuration-complete state; live Ethernet DATA readiness requires `PATH_UP` or the relevant RTS/iLT complete status.

This is the preferred wording for the current customer note because it keeps the DPSM model intact while explaining why the host still needs APSU/LT readiness checks.

## Sian3 Implementation Note

The Broadcom [Sian3 APSU application note](../sources/broadcom-2026-sian3-apsu-application-notes.md) supports the same separation in implementation terms. Sian3 exposes APSU and link-training progress through vendor cAPI fields such as `apsu_control_state`, `training_status`, `local_tf_lock`, `local_rx_ready`, `remote_rx_ready`, `local_rts`, and `remote_rts`. For Sian3, host logic should combine CMIS configuration state with those cAPI readiness fields before declaring a path ready for normal data.

## Host Implication

A host should combine base CMIS status with APSU status. Polling only DPSM is insufficient for APSU applications because the module can reach DPActivated while protocol-specific APSU work is still determining whether the path is ready for DATA mode.
