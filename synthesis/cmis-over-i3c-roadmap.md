---
type: synthesis
title: CMIS Over I3C Roadmap
created: 2026-06-15
updated: 2026-06-15
tags: [cmis, i3c, mci, firmware, roadmap, synthesis]
related: [../sources/oif2026-057-01-firmware-functional-design-authority-cmis-over-i3c.md, ../sources/oif2026-057-01-i3cmci-draft.md, ../sources/huabin-he-2026-i3c-bringup-schedule-planning.md, ../concepts/cmis-over-i3c-firmware-architecture.md, ../synthesis/i3c-analyzer-candidate-inventory.md, ../comparisons/i3cmci-required-subset-vs-mipi-i3c-feature-set.md, ../queries/what-implementation-decisions-does-cmis-over-i3c-require.md, ../queries/what-is-the-current-i3c-bringup-schedule.md]
sources: [../sources/oif2026-057-01-firmware-functional-design-authority-cmis-over-i3c.md, ../sources/oif2026-057-01-i3cmci-draft.md, ../sources/huabin-he-2026-i3c-bringup-schedule-planning.md]
status: draft
---

# CMIS Over I3C Roadmap

This synthesis combines the draft I3CMCI transport text, the CMIS-over-I3C functional-design-authority note, Huabin He's schedule-planning email and follow-up discussion, and the later analyzer/adapter ownership mapping into one implementation roadmap.

## Working Thesis

The draft I3CMCI specification is necessary but not sufficient. A real implementation also needs a portable target-firmware architecture, explicit fallback and recovery behavior, and a staged bring-up plan that uses the fastest available learning platform before migrating to the first product path. After discussion with Huabin, the first implementation anchor is `STM32H563/573` EVBs because the boards are available now and the ST I3C controller/target support packages and examples are more mature. `M45x/S` remains the migration target for the XPO/module-side path after the STM32 reference behavior is proven.

For now, the engineering baselines are `OIF 2026.057.01` for I3CMCI behavior and the I3CMCI-required subset of `MIPI I3C v1.2` / `I3C Basic v1.2` controller/target behavior. In this vault, `v1.1.1` is the stored public baseline file and `v1.2` is the target version family to align to when we need the latest public MIPI recommendation, but full MIPI feature-set implementation is not the I3CMCI baseline.

Transparent bridging to approved in-module DSP I3C targets is a separate debug-interface topic, not normal CMIS management traffic. Treat it like `SWD`: disabled by default, explicitly enabled, access controlled, logged, and lockable or removable for production use.

## Roadmap Layers

### 1. Transport definition

The draft I3CMCI document establishes the protocol baseline:

- Host acts as I3C controller.
- CMIS module acts as I3C target.
- ENTDAA is used for dynamic address assignment.
- READ, WRITE, and TEST remain the core access primitives.
- Legacy I2C compatibility remains required.
- Broader MIPI I3C features outside the required I3CMCI subset are tracked in [i3cmci-required-subset-vs-mipi-i3c-feature-set](../comparisons/i3cmci-required-subset-vs-mipi-i3c-feature-set.md).

### 2. Firmware architecture

The role note translates the transport into an implementation problem:

- build a portable I3C target stack
- separate protocol logic from MCU-specific HAL code
- preserve CMIS coherency and timing contracts
- validate the stack across more than one controller implementation
- plan a production I3C adapter for lab and factory use

The bring-up thread, follow-up discussion, and later inventory note narrow the execution order:

- `STM32H563/573` EVBs first for Phase 1 and Phase 2 because hardware is available and ST examples cover both controller and target sides
- basic STM32 controller-to-STM32 target bring-up before CMIS register semantics
- STM32 bridge-to-STM32 target CMIS register access before migrating target-side logic
- `Introspect` and `SC4420` as validation fixtures once acquired
- migration to `M45x/S` as the XPO/module-side target path after STM32 reference behavior is stable
- `Keysight`, `Prodigy`, `Easyi3C`, and `SC4420` recorded as part of the analyzer/adapter landscape, with ownership clarified in the inventory page

### 3. Bring-up schedule

The schedule email proposed a four-phase progression, and the follow-up decision keeps Phase 1 and Phase 2 on STM32 first before migrating to `M45x/S`:

1. `STM32H563/573` EVB controller-to-target basic I3C bring-up
2. PC-to-STM32 bridge and STM32 I3C target CMIS register access
3. Validation against `Introspect` and `SC4420` once purchased
4. Migration of the target stack and CMIS access model to `M45x/S` for the XPO/module-side path
5. I3C-MCI conformance, legacy I2C compatibility, and controlled debug-interface bridging to approved in-module targets such as DSPs under SWD-like access control

The email frames this as a draft plan and explicitly says the schedule will be defined further later.

## Immediate Open Questions

- Which exact ST I3C support-package and example versions should be frozen as the STM32 reference implementation input?
- What is the exact register-access and recovery behavior for the target stack?
- How should the STM32 target abstraction map onto the later `M45x/S` HAL and XPO firmware structure?
- What SWD-like access-control policy applies to transparent bridging into non-CMIS targets: authorization, enablement, target allowlist, transaction allowlist, logging, and production lock/disable behavior?
- What schedule milestones should replace the provisional 89-day estimate?

## Practical Interpretation

Treat the current state as a phased program:

- first, prove basic I3C controller/target mechanics on available `STM32H563/573` EVBs
- second, add the PC-to-STM32 bridge and CMIS register access on the STM32 target path
- third, validate the STM32 reference behavior against known analyzer fixtures (`Introspect`, `SC4420`) once available
- fourth, migrate the validated target stack and CMIS access behavior to `M45x/S` for the XPO/module-side path
- fifth, complete I3C-MCI conformance and legacy I2C coexistence, then gate any transparent bridge to approved in-module DSP targets as a privileged debug interface with SWD-like access control

## Related Pages

- [cmis-over-i3c-firmware-architecture](../concepts/cmis-over-i3c-firmware-architecture.md)
- [i3c-based-management-communication-interface](../concepts/i3c-based-management-communication-interface.md)
- [management-communication-interface](../concepts/management-communication-interface.md)
- [i3c-analyzer-candidate-inventory](../synthesis/i3c-analyzer-candidate-inventory.md)
- [i3cmci-required-subset-vs-mipi-i3c-feature-set](../comparisons/i3cmci-required-subset-vs-mipi-i3c-feature-set.md)
- [what-implementation-decisions-does-cmis-over-i3c-require](../queries/what-implementation-decisions-does-cmis-over-i3c-require.md)
- [what-is-the-current-i3c-bringup-schedule](../queries/what-is-the-current-i3c-bringup-schedule.md)
