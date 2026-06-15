---
type: concept
title: I3C-Based Management Communication Interface
created: 2026-05-25
updated: 2026-06-15
tags: [cmis, i3c, mci, draft]
related: [sources/oif2026-057-01-i3cmci-draft, sources/oif2026-057-01-firmware-functional-design-authority-cmis-over-i3c, sources/mipi-i3c-basic-v1-1-1, management-communication-interface, register-access-layer]
sources: [oif2026-057-01-i3cmci-draft, oif2026-057-01-firmware-functional-design-authority-cmis-over-i3c, mipi-i3c-basic-v1-1-1, oif-cmis-05-4]
status: draft
---

# I3C-Based Management Communication Interface

The I3C-based Management Communication Interface, or I3CMCI, is a draft CMIS MCI variant based on the public MIPI I3C Basic family. The uploaded `MIPI I3C Basic v1.1.1` specification is the clearest public normative baseline in this vault.

## Intent

I3CMCI aims to keep CMIS [register-access-layer](register-access-layer.md) semantics while providing a faster and lower-latency management transport than I2CMCI. It also preserves a migration path from legacy I2C operation.

## Draft Role Model

- The CMIS host is the I3C Controller.
- The CMIS module is the I3C Target.
- The module does not take Controller role.
- The module starts from legacy I2C-compatible behavior and transitions through I3C negotiation.

## Public Baseline

- The uploaded [mipi-i3c-basic-v1-1-1](../sources/mipi-i3c-basic-v1-1-1.md) is the public normative base reference now staged in the vault.
- Companion public pages for Hot-Join, virtual targets, version history, and FAQs are also staged under `raw/sources/I3CMCI/`.
- The full I3C member-version specification remains separate from the public Basic subset.
- The public FAQ explicitly recommends moving to `I3C v1.2` / `I3C Basic v1.2` for the newest recommended version set, so `v1.1.1` should be treated as the local baseline file, not the long-term target.

In other words, `v1.1.1` is the captured baseline for this vault; `v1.2` is the external target version when we want the newest public recommendation.

## Important Draft Mechanics

- Dynamic address assignment uses ENTDAA.
- A target is I3CMCI-ready only after dynamic address assignment.
- Required management operations still map to byte-addressed READ, WRITE, and TEST primitives.
- Recovery restarts negotiation from legacy I2C if the dynamic I3C address stops responding for the specified window.

## Implementation Caveat

This is draft material. Do not code final compliance behavior from this page without checking the latest published CMIS revision or final I3CMCI text.

The uploaded CMIS-over-I3C role note reinforces that real products also need a portable target HAL, negotiation/recovery logic, and cross-controller validation before the draft transport can be treated as production-ready.
