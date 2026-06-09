---
type: source
title: Lumentum 2026 802.3dj APSU/iLT Support Plan
created: 2026-06-09
updated: 2026-06-09
tags: [cmis, apsu, ilt, ieee-802-3dj, cdb, page-70h, lumentum, customer-note, source]
related: [../concepts/autonomous-path-startup.md, ../concepts/vendor-specific-cmis-customizations.md, ../sources/lumentum-2026-dpsm-apsu-ilt-state-machine.md, ../synthesis/apsu-ilt-customer-note-plan.md, ../queries/how-do-apsu-and-cmis-state-machines-interact.md, ../queries/how-should-hosts-use-sian3-apsu-capi.md]
authors: [Lumentum]
year: 2026
venue: Customer Technical Summary
source_files: [raw/sources/8023dj_apsu_ilt_cmis_slides.pptx, raw/sources/8023dj_apsu_ilt_cmis.pdf]
pptx_sha256: E09E133860A15D19F84B158C5A3C6D3DA112D6F54245E729840A478F66C46384
pdf_sha256: 77E08C652BC96648CC722EF0DD49F7663FAE1B6E968E60320EA40D2A63791D4F
product_scope: "1.6T 2xDR4 FRO module"
reference: OIF2026.093.08
status: current
---

# Lumentum 2026 802.3dj APSU/iLT Support Plan

This source captures the current customer-note position for IEEE 802.3dj APSU/iLT support on the 1.6T 2xDR4 FRO module. The raw folder contains both a slide deck and a PDF customer technical note export for the same support plan.

## Classification

- Current customer-note implementation and roadmap source.
- Vendor-specific current interface: NVIDIA-defined CDB commands.
- Standards-alignment target: OIF2026.093.08 Page 70h APSU/iLT mapping.
- Related state-machine diagram: [lumentum-2026-dpsm-apsu-ilt-state-machine](lumentum-2026-dpsm-apsu-ilt-state-machine.md).
- Related synthesis for customer wording: [apsu-ilt-customer-note-plan](../synthesis/apsu-ilt-customer-note-plan.md).

## Current Implementation Status

| Area | Current status |
|---|---|
| NVIDIA-defined vendor CDB interface | Implemented in current firmware. |
| APSU/iLT default behavior | Disabled by default; host enables per lane. |
| Precoding control | Implemented through vendor CDB. |
| CMIS MSM/DPSM behavior | Implemented consistently with the APSU draft model. |
| CMIS Page 70h APSU mapping | Planned, not implemented yet. |

The customer-note wording should not imply that formal CMIS Page 70h support is already available. The current host-facing control path is vendor CDB.

## Implemented Vendor CDB Commands

| Command | Function |
|---|---|
| `0xA200` | Get LT capability for host-side iLT, media-side iLT, and media-side APSU capability. |
| `0xA201` | Set/Get per-lane host LT, media LT, and APSU enable/disable masks. |
| `0xA082` | Set per-lane precoding override for host TX/RX and media TX/RX. |
| `0xA083` | Get precoding capability and current host/media TX/RX precoding state. |

`0xA201` returns effective active masks for host-side LT, media-side LT, and APSU. `0xA082` and `0xA083` cover host TX, host RX, media TX, and media RX precoding control/readback.

## Default Behavior

| Feature | Default |
|---|---|
| Host-side LT | Disabled. |
| Media-side LT | Disabled. |
| APSU | Disabled. |
| Precoding | Loaded from firmware/NVR configuration. |

The host may enable host LT, media LT, and APSU per lane with `0xA201`. Precoding overrides use `0xA082`.

## CMIS State-Machine Interpretation

The source keeps APSU/iLT orthogonal to the CMIS state machines:

- MSM behavior is unchanged.
- DPSM remains a CMIS configuration state machine.
- `DPActivated` means the CMIS datapath turn-on sequence has completed.
- Live Ethernet DATA readiness still depends on APSU/LT status, such as `PATH_UP`, RTS, or iLT status.
- Host software should not infer APSU completion from DPSM state alone.

## Planned CMIS Page 70h Mapping

The planned standardized interface follows the draft OIF2026.093.08 Page 70h layout:

| Page 70h range | Planned use |
|---|---|
| 128-131 | Interface-level APSU, ILT, and RTS control/status. |
| 132-151 | Per-lane training pattern control. |
| 152-191 | Media interface per-lane ILT control/status. |
| 192-230 | Host interface per-lane ILT control/status. |
| 231-255 | Reserved. |

## Release Phasing

| Phase | Scope | Status |
|---|---|---|
| Phase 1 | NVIDIA-defined vendor CDB commands `0xA200`, `0xA201`, `0xA082`, and `0xA083`. | Implemented in current firmware. |
| Phase 2 | Formal CMIS Page 70h APSU control/status mapping. | Planned. |

Firmware version and release timing for Page 70h support remain to be confirmed after validation closure.

## Customer-Note Use

Use this source as the primary current-status input for a customer note. The note can say that initial IEEE 802.3dj APSU/iLT control is supported through vendor CDB today, while formal CMIS Page 70h support is planned after validation. It should keep the standard draft reference visible and avoid presenting draft Page 70h behavior as already implemented.
