---
type: concept
title: CMIS Form Factor Management
created: 2026-05-25
updated: 2026-05-25
tags: [cmis, form-factor, hardware-signals, cmis-ff]
related: [sources/oif-cmis-ff-01-0, management-interface, management-memory-map, cmis-supplements]
sources: [oif-cmis-ff-01-0, oif-cmis-05-4]
---

# CMIS Form Factor Management

CMIS Form Factor Management, or CMIS-FF, maps form-factor-specific hardware management signals into the CMIS management model.

## Why It Exists

Some module form factors expose legacy or form-factor-specific low-speed signals for interrupt, rate select, transmit disable, receive loss-of-signal, transmit fault, and low-power behavior. CMIS-FF standardizes how those facilities are represented alongside generic CMIS management.

## Page Allocation

CMIS-FF uses Page 05h for form-factor-specific registers. The base [[management-memory-map]] advertises whether the CMIS-FF supplement is supported.

## Host Rule

Use CMIS generic names and state-machine behavior as the primary model. Use CMIS-FF to translate or control form-factor-specific signal behavior only when the module advertises support.

## Related Pages

- [[sources/oif-cmis-ff-01-0]]
- [[management-interface]]
- [[management-memory-map]]
- [[cmis-supplements]]
