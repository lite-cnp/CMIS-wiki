---
type: comparison
title: I3C Host Adapter Candidates vs Public Baseline
created: 2026-06-15
updated: 2026-06-15
tags: [i3c, host-adapter, comparison, public-links]
related: [../sources/huabin-he-2026-i3c-host-adapter-candidates.md, ../sources/mipi-i3c-basic-v1-1-1.md, ../sources/mipi-i3c-basic-faq-v1-1-1.md]
sources: [../sources/huabin-he-2026-i3c-host-adapter-candidates.md, ../sources/mipi-i3c-basic-v1-1-1.md, ../sources/mipi-i3c-basic-faq-v1-1-1.md, ../sources/mipi-i3c-basic-v1-2-hot-join-app-note.md, ../sources/mipi-i3c-virtual-devices-and-targets-app-note.md]
status: draft
---

# I3C Host Adapter Candidates vs Public Baseline

This note connects the internal adapter candidates with the public MIPI I3C materials that justify them.

## Internal Candidates

- STM32H563/573 eval boards as controller bridge hardware
- M450/M451S as the preferred module-side bring-up target
- Keysight protocol analysis gear for decode/trigger/debug
- Cost-effective production I3C dongle for factory testing

## Public References That Support The Direction

- [mipi-i3c-basic-v1-1-1](../sources/mipi-i3c-basic-v1-1-1.md) for the public normative base
- [mipi-i3c-basic-faq-v1-1-1](../sources/mipi-i3c-basic-faq-v1-1-1.md) for version guidance and public availability
- [mipi-i3c-basic-v1-2-hot-join-app-note](../sources/mipi-i3c-basic-v1-2-hot-join-app-note.md) for hot-join and target participation context
- [mipi-i3c-virtual-devices-and-targets-app-note](../sources/mipi-i3c-virtual-devices-and-targets-app-note.md) for abstracted target/device concepts

## Practical Takeaway

The internal thread is not inventing a new bus model. It is deciding which off-the-shelf controller, analyzer, and low-cost bridge path can best implement and validate the already-public I3C Basic behavior used by CMIS-over-I3C.

