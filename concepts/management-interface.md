---
type: concept
title: Management Interface
created: 2026-05-25
updated: 2026-05-25
tags: [cmis, management-interface, msl, ral]
related: [cmis-management-stack, register-access-layer, management-communication-interface, cmis-host, cmis-managed-module, cmis-form-factor-management]
sources: [oif-cmis-05-4, oif-cmis-05-3]
---

# Management Interface

The CMIS management interface is the set of mechanisms a [cmis-host](../entities/cmis-host.md) uses to manage a [cmis-managed-module](../entities/cmis-managed-module.md). It combines discrete management signals with register access over a management communication link.

## Horizontal Parts

- **Management Signaling Layer (MSL)**: control/status hardware signals with fixed or programmable management function. Core examples are Reset, Interrupt, and optional LowPwrRequestHW.
- **Register Access Layer (RAL)**: software-visible READ, WRITE, and TEST access to module management memory.

## Vertical Transport

The [management-communication-interface](management-communication-interface.md) implements RAL primitives across the physical interconnect. CMIS defines I2CMCI and SPIMCI variants, while [i3c-based-management-communication-interface](i3c-based-management-communication-interface.md) is draft/future-direction material.

## Form-Factor Signals

[cmis-form-factor-management](cmis-form-factor-management.md) maps form-factor-specific hardware signals into the generic CMIS management model when a module advertises CMIS-FF support.

## Why It Matters

CMIS separates management meaning from transport mechanics. This lets the same management application layer operate over different MCI variants and form factors, provided the required primitives and timing behavior are preserved.

Source anchor: CMIS 5.4 chapter 5 and Appendix B.
