---
type: synthesis
title: I3C Host Adapter Decision
created: 2026-06-15
updated: 2026-06-15
tags: [i3c, host-adapter, decision, synthesis]
related: [../sources/huabin-he-2026-i3c-host-adapter-candidates.md, ../sources/mipi-i3c-basic-v1-1-1.md, ../sources/mipi-i3c-basic-faq-v1-1-1.md, ../sources/mipi-i3c-basic-v1-2-hot-join-app-note.md, ../sources/mipi-i3c-virtual-devices-and-targets-app-note.md, ../concepts/cmis-over-i3c-firmware-architecture.md, ../synthesis/cmis-over-i3c-roadmap.md]
sources: [../sources/huabin-he-2026-i3c-host-adapter-candidates.md, ../sources/mipi-i3c-basic-v1-1-1.md, ../sources/mipi-i3c-basic-faq-v1-1-1.md, ../sources/mipi-i3c-basic-v1-2-hot-join-app-note.md, ../sources/mipi-i3c-virtual-devices-and-targets-app-note.md]
status: draft
---

# I3C Host Adapter Decision

This synthesis turns the candidate discussion into a practical recommendation for CMIS-over-I3C bring-up.

## Recommendation

Use the STM32H563/573 evaluation-board path as the primary low-cost lab controller-bridge candidate, with the M450/M451S as the preferred module-side target platform. For analyzer and debug gear, treat the exact vendor ownership mapping as recorded in the inventory page: `SC4420` for the ADI-recommended path, `Introspect` for the Taiwan team purchase, `Prodigy` for Hong Kong, `Easyi3C` for your search, and `Keysight` for Hua Zhang's query. Track the production STM32H563/573 Ethernet-to-I3C fan-out as a parallel adapter workstream during the 12-week bring-up plan, while keeping module-side I3C-MCI proof as the critical path.

## Why This Is The Best Fit

- It aligns with the public MIPI I3C Basic baseline now staged in the vault.
- It matches the draft CMIS-over-I3C transport model and the firmware architecture note.
- It gives the team a cheap, replaceable lab controller bridge instead of depending on scarce commercial protocol generators.
- It preserves the ability to move from lab bring-up to a cost-effective production adapter later.
- It allows the Ethernet-to-I3C fan-out concept to mature in parallel with firmware bring-up instead of being deferred until after the module-side path is done.

## Public References Used

- [mipi-i3c-basic-v1-1-1](../sources/mipi-i3c-basic-v1-1-1.md) for the public normative baseline
- [mipi-i3c-basic-faq-v1-1-1](../sources/mipi-i3c-basic-faq-v1-1-1.md) for public availability and version guidance
- [mipi-i3c-basic-v1-2-hot-join-app-note](../sources/mipi-i3c-basic-v1-2-hot-join-app-note.md) for hot-join and target participation context
- [mipi-i3c-virtual-devices-and-targets-app-note](../sources/mipi-i3c-virtual-devices-and-targets-app-note.md) for virtual-target and abstraction context
- [i3c-analyzer-candidate-inventory](i3c-analyzer-candidate-inventory.md) for the owner-to-product mapping

## Open Decisions

- Whether the Week 12 fan-out target should be lab prototype, factory prototype, or architecture review.
- Whether fan-out should target multiple STM32 controller boards first, multiple I3C buses from one board if supported, or both.
- Whether a second controller candidate should be kept as a backup for hardware risk reduction.
- What the minimum analyzer feature set is for first-pass bring-up versus deeper debug.

## Related Pages

- [huabin-he-2026-i3c-host-adapter-candidates](../sources/huabin-he-2026-i3c-host-adapter-candidates.md)
- [cmis-over-i3c-roadmap](cmis-over-i3c-roadmap.md)
- [cmis-over-i3c-firmware-architecture](../concepts/cmis-over-i3c-firmware-architecture.md)
