---
type: comparison
title: I3CMCI Required Subset vs MIPI I3C Feature Set
created: 2026-06-15
updated: 2026-06-15
tags: [cmis, i3c, i3cmci, mipi, scope, comparison]
related: [../sources/oif2026-057-01-i3cmci-draft.md, ../sources/oif2026-057-01-firmware-functional-design-authority-cmis-over-i3c.md, ../sources/mipi-i3c-basic-v1-1-1.md, ../sources/mipi-i3c-version-history-table.md, ../concepts/i3c-based-management-communication-interface.md, ../synthesis/cmis-over-i3c-roadmap.md]
sources: [../sources/oif2026-057-01-i3cmci-draft.md, ../sources/oif2026-057-01-firmware-functional-design-authority-cmis-over-i3c.md, ../sources/mipi-i3c-basic-v1-1-1.md, ../sources/mipi-i3c-version-history-table.md, ../sources/mipi-i3c-basic-v1-2-hot-join-app-note.md, ../sources/mipi-i3c-virtual-devices-and-targets-app-note.md]
status: draft
---

# I3CMCI Required Subset vs MIPI I3C Feature Set

This page records the scope decision from the Huabin/Yajun discussion: `MIPI I3C v1.1.1/v1.2` defines a much broader feature set than I3CMCI needs. The implementation baseline should be I3CMCI over conformant MIPI I3C controller/target behavior for the subset that I3CMCI uses, not full implementation of every MIPI I3C feature.

## Required I3CMCI Subset

- Host acts as the I3C Controller.
- CMIS module acts as the I3C Target and does not assume Controller role.
- Legacy I2C-compatible startup and fallback remain supported.
- Dynamic Address Assignment uses `ENTDAA`.
- The module becomes I3CMCI-ready only after dynamic address assignment.
- Transport uses I3C SCL/SDA with open-drain arbitration and push-pull SDR transfers.
- CMIS management access remains register-oriented through `READ`, `WRITE`, and `TEST`.
- Required CCC handling is limited to the final I3CMCI-required set, such as negotiation, dynamic-address, enable/disable event, and status commands; the draft wording still needs final confirmation.
- Recovery restarts from legacy I2C negotiation after repeated dynamic-address failures.

## Features Not Required By The I3CMCI Baseline

| Broader MIPI I3C feature | I3CMCI baseline status | Reason |
|---|---|---|
| HDR transfer modes such as `HDR-DDR` and `HDR-T` | Not required | The draft I3CMCI access path is register-oriented and uses SDR-style private transfer behavior. HDR may be useful for future bandwidth work, but it is not needed to prove CMIS `READ`/`WRITE`/`TEST`. |
| Module-side Controller role | Not required | The CMIS module is an I3C Target. It should not request or assume Controller role. |
| Multi-controller handoff or arbitration | Not required | I3CMCI assumes the host owns Controller responsibility. Multi-controller behavior is outside the first CMIS management path. |
| Full MIPI CCC catalog | Not required | Only the CCCs needed for I3CMCI negotiation, dynamic addressing, event enable/disable if used, status, and recovery should be mandatory. |
| IBI generation as a required data path | Not required for the minimum register-access baseline | CMIS management can be proven with host-initiated register access. IBI may be validated as a platform capability or future alert path, but it is not required for first-pass I3CMCI `READ`/`WRITE`/`TEST`. |
| Hot-Join as a required module behavior | Not required for the minimum baseline | The current baseline starts from legacy I2C-compatible negotiation and host-controlled dynamic address assignment. Hot-Join should remain a reference topic unless the final I3CMCI text requires late bus participation. |
| Virtual devices and virtual targets | Not required | I3CMCI exposes the CMIS module management target directly. Virtualized endpoints are adapter or bridge architecture choices, not baseline module requirements. |
| Transparent bridging to in-module DSPs or other non-CMIS targets | Not required by I3CMCI baseline; tracked as a controlled debug-interface extension | Treat this like `SWD`, not like normal CMIS management traffic. It needs explicit enablement, access control, target and command allowlists, audit logging, and production lock/disable behavior before implementation. |
| Production dongle or factory adapter feature completeness | Not required for module conformance | Lab and production adapters may implement more controller features, but the module-side I3CMCI requirement should stay tied to the CMIS transport subset. |
| HDR-rate electrical validation and eye-diagram coverage | Not required for the first baseline | SDR signal integrity at the selected bring-up rate is needed. HDR-rate validation belongs only if HDR modes become an explicit future requirement. |
| Broad multi-drop topology simulation beyond the CMIS use case | Not required | Legacy I2C coexistence remains important, but arbitrary multi-drop ecosystem coverage is broader than the first I3CMCI path. |
| Generic MIPI ecosystem features such as HCI-oriented host integration | Not required | These may matter for a commercial controller product, but they are not CMIS module I3CMCI behavior. |
| Target Reset as a mandatory management feature | Not required unless final I3CMCI text requires it | MIPI covers Target Reset, but the I3CMCI draft summary does not make it part of the minimum CMIS register-access path. |

## Practical Baseline Rule

Treat `MIPI I3C v1.2` / `I3C Basic v1.2` as the protocol family to align with, but gate implementation by I3CMCI requirements. A feature is mandatory only if it is needed for the CMIS module to complete I3CMCI negotiation, dynamic address assignment, SDR register access, required CCC handling, legacy fallback, or recovery.

## Debug-Interface Rule For DSP Bridging

Transparent access to in-module DSP I3C targets should be modeled as a privileged debug interface similar to `SWD`, not as a general-purpose management feature. It should be disabled by default, explicitly enabled only by an authorized host or manufacturing/debug tool, constrained to approved targets and transactions, logged for traceability, and lockable or removable for production configurations.

## Implication For Bring-Up

- Phase 1 on `STM32H563/573` should use ST examples to validate controller/target mechanics, but should not turn every ST or MIPI example feature into a product requirement.
- Phase 2 should focus on CMIS register access through the bridge, not HDR, virtual targets, or multi-controller behavior.
- Analyzer validation should confirm the I3CMCI subset first.
- `M45x/S` migration should port only the required target subset plus any consciously accepted optional extensions.
- Controlled DSP bridging should have policy and architecture checkpoints during the 12-week plan, but should not be treated as passing the I3CMCI baseline unless the CMIS register-transport path also passes independently.

## Related Pages

- [oif2026-057-01-i3cmci-draft](../sources/oif2026-057-01-i3cmci-draft.md)
- [oif2026-057-01-firmware-functional-design-authority-cmis-over-i3c](../sources/oif2026-057-01-firmware-functional-design-authority-cmis-over-i3c.md)
- [i3c-based-management-communication-interface](../concepts/i3c-based-management-communication-interface.md)
- [cmis-over-i3c-roadmap](../synthesis/cmis-over-i3c-roadmap.md)
- [what-is-the-current-i3c-bringup-schedule](../queries/what-is-the-current-i3c-bringup-schedule.md)
