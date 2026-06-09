---
type: source
title: Lumentum 2026 DPSM APSU/iLT State Machine
created: 2026-06-09
updated: 2026-06-09
tags: [cmis, apsu, ilt, dpsm, state-machine, lumentum, customer-note, source]
related: [../concepts/autonomous-path-startup.md, ../concepts/data-path-state-machine.md, ../sources/lumentum-2026-8023dj-apsu-ilt-support-plan.md, ../synthesis/apsu-ilt-customer-note-plan.md, ../queries/how-do-apsu-and-cmis-state-machines-interact.md]
authors: [Lumentum]
year: 2026
venue: Implementation State-Machine Diagram
source_filename: raw/sources/dpsm-apsu-ilt-state-machine.drawio.png
source_sha256: D51458CCED49999657636F5348EB334AC2E26FE43430F0CC63E34037A9CF44DB
diagram_format: draw.io embedded in PNG
status: current
---

# Lumentum 2026 DPSM APSU/iLT State Machine

This PNG contains an embedded draw.io model that overlays APSU/iLT actions onto the CMIS-05.4 DPSM topology. It is a current state-machine explanation source for the customer-note plan.

## Classification

- Current implementation/state-machine diagram.
- Clarifies how APSU/iLT actions relate to CMIS DPSM.
- Supports the implementation plan in [lumentum-2026-8023dj-apsu-ilt-support-plan](lumentum-2026-8023dj-apsu-ilt-support-plan.md).

## Extracted Diagram Model

The diagram preserves the normal CMIS DPSM topology:

- `DPDeactivated`
- `DPInit`
- `DPDeinit`
- `DPInitialized`
- `DPTxTurnOn`
- `DPTxTurnOff`
- `DPActivated`

The APSU/iLT side of the diagram states that APSU/iLT does not add DPSM states. MSM is unchanged, and DPSM remains the CMIS configuration state machine.

## APSU/iLT Action Points

| Action area | State-machine relationship | Control/status focus |
|---|---|---|
| Host-side APSU / host iLT | May begin at `DPInitialized`. | Enable mask, lane LT, precoding, RTS/iLT result. |
| Media-side APSU / media iLT | May begin at `DPTxTurnOn`. | Training and RTS status run independently from DPSM transitions. |
| Live Ethernet DATA gate | Checked after `DPActivated`, but not guaranteed by `DPActivated`. | DATA ready requires `PATH_UP` or the relevant RTS/iLT complete status. |

The diagram explicitly labels host-side and media-side APSU/iLT actions as allowed at their respective DPSM points while keeping those actions outside the DPSM transition graph.

## Host Interpretation

A host should treat DPSM and APSU/iLT as two gates:

1. CMIS configuration gate: DPSM reaches the expected configuration state, such as `DPActivated`.
2. APSU/iLT readiness gate: protocol startup reports `PATH_UP`, RTS completion, or iLT completion for the relevant interface.

For a customer note, this diagram is the cleanest visual source for the statement that `DPActivated` is configuration-complete, not live-data-ready, when APSU/iLT is involved.
