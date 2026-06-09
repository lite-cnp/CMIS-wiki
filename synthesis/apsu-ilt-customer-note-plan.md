---
type: synthesis
title: APSU/iLT Customer Note Plan
created: 2026-06-09
updated: 2026-06-09
tags: [cmis, apsu, ilt, cdb, page-70h, customer-note, synthesis]
related: [../concepts/autonomous-path-startup.md, ../concepts/vendor-specific-cmis-customizations.md, ../sources/lumentum-2026-8023dj-apsu-ilt-support-plan.md, ../sources/lumentum-2026-dpsm-apsu-ilt-state-machine.md, ../sources/broadcom-2026-sian3-apsu-application-notes.md, ../sources/feng-jiang-2026-sian3-link-training-verification-email-thread.md]
sources: [../sources/lumentum-2026-8023dj-apsu-ilt-support-plan.md, ../sources/lumentum-2026-dpsm-apsu-ilt-state-machine.md, ../sources/broadcom-2026-sian3-apsu-application-notes.md, ../sources/feng-jiang-2026-sian3-link-training-verification-email-thread.md, ../sources/oif2026-093-08-802-3dj-apsu-draft.md]
status: current
---

# APSU/iLT Customer Note Plan

This synthesis is the current customer-note position for APSU/iLT implementation status and further development. It reconciles the current vendor CDB implementation plan with the draft CMIS Page 70h model and the earlier Sian3 APSU/cAPI material.

## Customer Position

Current firmware supports initial IEEE 802.3dj APSU/iLT control through NVIDIA-defined vendor CDB commands. Formal CMIS Page 70h APSU control/status support is planned, not implemented yet, and should be described as a later standards-alignment phase after validation closure.

## Current Implementation Status

| Area | Customer-note wording |
|---|---|
| Vendor CDB interface | Implemented in current firmware. |
| APSU/iLT defaults | Disabled by default; host enables per lane. |
| Per-lane LT/APSU control | Available through `0xA201` active masks. |
| Precoding control/readback | Available through `0xA082` and `0xA083`. |
| CMIS state machines | MSM unchanged; DPSM remains the configuration state machine. |
| CMIS Page 70h | Planned after validation closure; do not claim current support. |

## Implemented CDB Surface

| Command | Customer-facing meaning |
|---|---|
| `0xA200` | Reports host-side iLT, media-side iLT, and media-side APSU capability. |
| `0xA201` | Sets/gets per-lane host LT, media LT, and APSU enable/disable masks. |
| `0xA082` | Overrides host TX/RX and media TX/RX precoding per lane. |
| `0xA083` | Reports precoding capability and current host/media TX/RX precoding state. |

The command set is enough for host-driven APSU/iLT enablement and diagnostics before the formal CMIS Page 70h mapping is available.

## State-Machine Rule

Use two readiness gates in customer-facing explanations:

1. CMIS gate: DPSM completes the datapath configuration sequence and can reach `DPActivated`.
2. APSU/iLT gate: live Ethernet DATA readiness is determined from APSU/LT status such as `PATH_UP`, RTS, or iLT completion.

Host-side APSU/host iLT may begin at `DPInitialized`. Media-side APSU/media iLT may begin at `DPTxTurnOn`. Neither action adds new DPSM states.

## Development Plan

| Phase | Scope | Status |
|---|---|---|
| Phase 1 | NVIDIA-defined vendor CDB support for capability, LT/APSU lane masks, and precoding control/readback. | Current firmware. |
| Phase 2 | Formal CMIS Page 70h APSU/iLT control/status mapping aligned to OIF2026.093.08. | Planned after validation closure. |

Keep firmware version and release timing as open until validation closure confirms them.

## Evidence To Carry Forward

- [lumentum-2026-8023dj-apsu-ilt-support-plan](../sources/lumentum-2026-8023dj-apsu-ilt-support-plan.md) is the primary current-status and roadmap source.
- [lumentum-2026-dpsm-apsu-ilt-state-machine](../sources/lumentum-2026-dpsm-apsu-ilt-state-machine.md) is the clearest state-machine source for the `DPActivated` caveat.
- [broadcom-2026-sian3-apsu-application-notes](../sources/broadcom-2026-sian3-apsu-application-notes.md) remains useful for detailed Sian3 APSU/link-training behavior and cAPI field concepts.
- [feng-jiang-2026-sian3-link-training-verification-email-thread](../sources/feng-jiang-2026-sian3-link-training-verification-email-thread.md) provides lab evidence for polarity recovery, tap/BER improvement, repeatability, and temperature-sensitive restart behavior.

## Customer-Note Boundaries

- Say "vendor CDB implemented today" and "CMIS Page 70h planned" as separate statements.
- Do not present draft OIF2026.093.08 Page 70h ranges as current firmware behavior.
- Do not use `DPActivated` alone as a live-data-ready claim.
- Keep Broadcom cAPI details as implementation background unless the customer note is specifically about that cAPI interface.
- Keep exact Page 70h firmware version, release timing, and interoperability closure as open items.
