---
type: synthesis
title: I3C Analyzer Candidate Inventory
created: 2026-06-15
updated: 2026-06-15
tags: [i3c, analyzer, inventory, synthesis]
related: [../sources/huabin-he-2026-i3c-host-adapter-candidates.md, ../sources/mipi-i3c-basic-v1-1-1.md, ../sources/mipi-i3c-basic-faq-v1-1-1.md]
sources: [../sources/huabin-he-2026-i3c-host-adapter-candidates.md, ../sources/mipi-i3c-basic-v1-1-1.md, ../sources/mipi-i3c-basic-faq-v1-1-1.md, ../sources/mipi-i3c-basic-v1-2-hot-join-app-note.md, ../sources/mipi-i3c-virtual-devices-and-targets-app-note.md]
status: draft
---

# I3C Analyzer Candidate Inventory

This page records the I3C analyzer and host-adapter product mappings mentioned in the thread family.

## Exact Named Products And Mappings

| Candidate | Role | Mapping |
|---|---|---|
| [Easyi3C Tower I3C Host Adapter Pro](https://easyi3c.com/pro.html) | Host adapter / controller bridge | Your search |
| [SignalCraft SC4420](https://www.signalcraft.com/products/serial-bus-controllers/sc4420/) | MIPI-SPMI / MIPI-I3C / MIPI-RFFE controller | Analog Devices recommended |
| [Introspect Technology MIPI I3C Design, Test, and Debug Solutions](https://introspect.ca/products-solutions/i3c-design-and-test/) | Host controller / emulator / debug system | Taiwan team bought |
| [Prodigy Technovations PGY-I3C-EX-PD](https://www.prodigytechno.com/product/i3c-protocol-analyzer-and-exerciser/) | Protocol analyzer / exerciser | Hong Kong team |
| [Keysight D9010MPLP LowSpeed MIPI Protocol Decode/Trigger Software](https://www.keysight.com/us/en/product/D9010MPLP/lowspeed-mipi-protocol-decode-trigger-software-rffe-i3c-spmi.html) | Protocol decode/trigger for Keysight oscilloscopes | Hua Zhang's query |
| [Promira Serial Platform](https://www.totalphase.com/products/promira-serial/) | Serial platform | Mentioned in thread, but not confirmed as an I3C-capable choice |

## Practical Reading

- `Easyi3C` is the budget/controller-bridge path under your search.
- `SC4420` is the ADI-recommended path.
- `Introspect` is the Taiwan team’s older purchase.
- `Prodigy` is the Hong Kong team’s analyzer.
- `Keysight` is Hua Zhang’s queried option.
- `Promira` was mentioned, but the thread questioned whether it actually supports I3C.

## Public References

- [mipi-i3c-basic-v1-1-1](../sources/mipi-i3c-basic-v1-1-1.md)
- [mipi-i3c-basic-faq-v1-1-1](../sources/mipi-i3c-basic-faq-v1-1-1.md)
- [mipi-i3c-basic-v1-2-hot-join-app-note](../sources/mipi-i3c-basic-v1-2-hot-join-app-note.md)
- [mipi-i3c-virtual-devices-and-targets-app-note](../sources/mipi-i3c-virtual-devices-and-targets-app-note.md)

## Related Pages

- [huabin-he-2026-i3c-host-adapter-candidates](../sources/huabin-he-2026-i3c-host-adapter-candidates.md)
- [i3c-host-adapter-decision](i3c-host-adapter-decision.md)
- [cmis-over-i3c-roadmap](cmis-over-i3c-roadmap.md)

