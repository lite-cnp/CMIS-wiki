---
type: concept
title: Autonomous Path Startup
created: 2026-05-25
updated: 2026-06-09
tags: [cmis, ieee-802-3dj, apsu, ilt, rts, cdb, draft]
related: [sources/oif2026-093-08-802-3dj-apsu-draft, sources/ieee-p802-3dj-d2-3, sources/lumentum-2026-8023dj-apsu-ilt-support-plan, sources/lumentum-2026-dpsm-apsu-ilt-state-machine, sources/broadcom-2026-sian3-apsu-application-notes, sources/broadcom-2025-sian3-ilt-procedure, sources/feng-jiang-2026-sian3-link-training-verification-email-thread, synthesis/apsu-ilt-customer-note-plan, data-path-state-machine, network-path-applications, vendor-specific-cmis-customizations]
sources: [oif2026-093-08-802-3dj-apsu-draft, ieee-p802-3dj-d2-3, lumentum-2026-8023dj-apsu-ilt-support-plan, lumentum-2026-dpsm-apsu-ilt-state-machine, broadcom-2026-sian3-apsu-application-notes, broadcom-2025-sian3-ilt-procedure, feng-jiang-2026-sian3-link-training-verification-email-thread]
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

- The [module-state-machine](module-state-machine.md) is unchanged.
- Host-interface APSU can begin at DPInitialized.
- Media-interface APSU can begin at DPTxTurnOn.
- DPActivated means CMIS configuration is complete; live Ethernet DATA still depends on APSU completion.
- The same relationship applies to [network-path-applications](network-path-applications.md) where NPSM is involved.

## Draft CMIS Register Model

The OIF draft assigns Page 70h for APSU control and monitoring. It includes interface-level control/status, training-pattern controls, media-side ILT status, and host-side ILT status.

## Current Customer-Note Implementation Status

The Lumentum [802.3dj APSU/iLT support plan](../sources/lumentum-2026-8023dj-apsu-ilt-support-plan.md) describes the current 1.6T 2xDR4 FRO customer-note position:

- Initial APSU/iLT support is implemented through NVIDIA-defined vendor CDB commands, not through CMIS Page 70h yet.
- APSU/iLT is disabled by default and enabled by the host per lane.
- `0xA200` reports LT/APSU capability, `0xA201` controls host LT, media LT, and APSU masks, and `0xA082`/`0xA083` set/read back per-lane precoding.
- Formal CMIS Page 70h APSU control/status is planned after validation closure and should not be described as current firmware behavior.

The companion [DPSM APSU/iLT state-machine diagram](../sources/lumentum-2026-dpsm-apsu-ilt-state-machine.md) reinforces the same state-machine rule: APSU/iLT does not add DPSM states, and live Ethernet DATA readiness still requires APSU/LT status after CMIS configuration completes.

## Vendor Implementation: Sian3

The Broadcom [Sian3 APSU application note](../sources/broadcom-2026-sian3-apsu-application-notes.md) is a vendor-specific implementation source. It should not be promoted into base CMIS behavior, but it shows practical host-facing APSU details:

- Sian3 permits five APSU/link-training configurations: both sides LT on, client-side LT only, line-side LT only, APSU without LT, and APSU/LT disabled.
- APSU and link-training settings apply to all lanes of the same port. On bundled ports, one lane restart restarts link training across the bundle.
- With link training enabled, Sian3 enables automatic Rx polarity detection/correction and can auto-select client-side NR or ER slicer mode.
- Sian3 cAPI exposes control fields such as `apsu_en`, `lnktrn_en`, `auto_restart`, timer settings, and status fields such as `apsu_control_state`, `training_status`, frame lock, local/remote Rx readiness, RTS, polarity correction, and recovery counters.
- `recovery_reason` and `recovery_event_count` are read-clear fields, so host diagnostics should capture them before repeated polling clears evidence.

The [Feng Jiang Sian3 verification thread](../sources/feng-jiang-2026-sian3-link-training-verification-email-thread.md) adds lab evidence that Sian3 link training can recover deliberate polarity inversion and improve degraded DSP tap/BER conditions. It also shows that FIR may not automatically update after temperature changes unless link training is disabled and re-enabled.

[broadcom-2025-sian3-ilt-procedure](../sources/broadcom-2025-sian3-ilt-procedure.md) is an older `E000_FF10`-era procedure source. It is useful for BERT/DUT setup steps, but the newer APSU application note should be preferred for current behavior and terminology.

## Host Rule

A host should not infer APSU completion from DPSM state alone. For APSU applications, use the relevant APSU control/status fields in addition to the base CMIS state-machine and output-status fields. For the current customer-note CDB path, combine CMIS state with vendor CDB control/readback and APSU/LT readiness status. For Sian3 cAPI specifically, combine CMIS state with the vendor cAPI readiness fields described in [how-should-hosts-use-sian3-apsu-capi](../queries/how-should-hosts-use-sian3-apsu-capi.md).
