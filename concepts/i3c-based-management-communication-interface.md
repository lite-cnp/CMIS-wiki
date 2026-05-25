---
type: concept
title: I3C-Based Management Communication Interface
created: 2026-05-25
updated: 2026-05-25
tags: [cmis, i3c, mci, draft]
related: [sources/oif2026-057-01-i3cmci-draft, management-communication-interface, register-access-layer]
sources: [oif2026-057-01-i3cmci-draft, oif-cmis-05-4]
status: draft
---

# I3C-Based Management Communication Interface

The I3C-based Management Communication Interface, or I3CMCI, is a draft CMIS MCI variant based on MIPI I3C Basic.

## Intent

I3CMCI aims to keep CMIS [[register-access-layer]] semantics while providing a faster and lower-latency management transport than I2CMCI. It also preserves a migration path from legacy I2C operation.

## Draft Role Model

- The CMIS host is the I3C Controller.
- The CMIS module is the I3C Target.
- The module does not take Controller role.
- The module starts from legacy I2C-compatible behavior and transitions through I3C negotiation.

## Important Draft Mechanics

- Dynamic address assignment uses ENTDAA.
- A target is I3CMCI-ready only after dynamic address assignment.
- Required management operations still map to byte-addressed READ, WRITE, and TEST primitives.
- Recovery restarts negotiation from legacy I2C if the dynamic I3C address stops responding for the specified window.

## Implementation Caveat

This is draft material. Do not code final compliance behavior from this page without checking the latest published CMIS revision or final I3CMCI text.
