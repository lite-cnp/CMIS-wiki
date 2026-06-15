---
type: synthesis
title: CMIS Over I3C Roadmap
created: 2026-06-15
updated: 2026-06-15
tags: [cmis, i3c, mci, firmware, roadmap, synthesis]
related: [../sources/oif2026-057-01-firmware-functional-design-authority-cmis-over-i3c.md, ../sources/oif2026-057-01-i3cmci-draft.md, ../sources/huabin-he-2026-i3c-bringup-schedule-planning.md, ../concepts/cmis-over-i3c-firmware-architecture.md, ../synthesis/i3c-analyzer-candidate-inventory.md, ../queries/what-implementation-decisions-does-cmis-over-i3c-require.md, ../queries/what-is-the-current-i3c-bringup-schedule.md]
sources: [../sources/oif2026-057-01-firmware-functional-design-authority-cmis-over-i3c.md, ../sources/oif2026-057-01-i3cmci-draft.md, ../sources/huabin-he-2026-i3c-bringup-schedule-planning.md]
status: draft
---

# CMIS Over I3C Roadmap

This synthesis combines the draft I3CMCI transport text, the CMIS-over-I3C functional-design-authority note, Huabin He's schedule-planning email, and the later analyzer/adapter ownership mapping into one implementation roadmap.

## Working Thesis

The draft I3CMCI specification is necessary but not sufficient. A real implementation also needs a portable target-firmware architecture, explicit fallback and recovery behavior, and a staged bring-up plan that validates the first product path before broadening to bridge and multi-target control. The public MIPI FAQ recommends `I3C v1.2` / `I3C Basic v1.2` as the newest recommended version set, so the uploaded `v1.1.1` file should be treated as a baseline reference in this vault rather than the final target.

In this vault, `v1.1.1` is the stored baseline file and `v1.2` is the target version family to align to when we need the latest public MIPI recommendation.

## Roadmap Layers

### 1. Transport definition

The draft I3CMCI document establishes the protocol baseline:

- Host acts as I3C controller.
- CMIS module acts as I3C target.
- ENTDAA is used for dynamic address assignment.
- READ, WRITE, and TEST remain the core access primitives.
- Legacy I2C compatibility remains required.

### 2. Firmware architecture

The role note translates the transport into an implementation problem:

- build a portable I3C target stack
- separate protocol logic from MCU-specific HAL code
- preserve CMIS coherency and timing contracts
- validate the stack across more than one controller implementation
- plan a production I3C adapter for lab and factory use

The bring-up thread and later inventory note narrow the execution order:

- `M45x/S` EVB first as the target bring-up anchor for `XPO`
- `Introspect` and `SC4420` as the first validation fixtures once acquired
- `STM32H563/573` as the controller-bridge milestone, with Ethernet fan-out to multiple controllers
- `Keysight`, `Prodigy`, `Easyi3C`, and `SC4420` recorded as part of the analyzer/adapter landscape, with ownership clarified in the inventory page

### 3. Bring-up schedule

The schedule email proposed a four-phase progression, but the roadmap now reorders the execution around the confirmed product plan:

1. `M45x/S` EVB target bring-up
2. Validation against `Introspect` and `SC4420` once purchased
3. `STM32H563/573` controller bridging with Ethernet to multiple controllers
4. I3C-MCI implementation and CMIS conformance validation
5. Transparent bridging to approved in-module targets such as DSPs under access control

The email frames this as a draft plan and explicitly says the schedule will be defined further later.

## Immediate Open Questions

- Which I3CMCI draft or proposal is the active reference for engineering?
- What is the exact register-access and recovery behavior for the target stack?
- What access-control policy applies to transparent bridging into non-CMIS targets?
- What schedule milestones should replace the provisional 89-day estimate?

## Practical Interpretation

Treat the current state as a phased program:

- first, prove I3C transport mechanics on the `M45x/S` EVB path
- second, validate against the known analyzer fixtures (`Introspect`, `SC4420`) before broad controller work
- third, bring up the `STM32H563/573` bridge and fan out to multiple controllers
- fourth, implement I3C-MCI and pass CMIS conformance
- fifth, extend transparent bridging to approved in-module DSP targets under access control

## Related Pages

- [cmis-over-i3c-firmware-architecture](../concepts/cmis-over-i3c-firmware-architecture.md)
- [i3c-based-management-communication-interface](../concepts/i3c-based-management-communication-interface.md)
- [management-communication-interface](../concepts/management-communication-interface.md)
- [i3c-analyzer-candidate-inventory](../synthesis/i3c-analyzer-candidate-inventory.md)
- [what-implementation-decisions-does-cmis-over-i3c-require](../queries/what-implementation-decisions-does-cmis-over-i3c-require.md)
- [what-is-the-current-i3c-bringup-schedule](../queries/what-is-the-current-i3c-bringup-schedule.md)
