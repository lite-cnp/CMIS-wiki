---
type: concept
title: CMIS Over I3C Firmware Architecture
created: 2026-06-15
updated: 2026-06-15
tags: [cmis, i3c, firmware, architecture, mci]
related: [../sources/oif2026-057-01-firmware-functional-design-authority-cmis-over-i3c.md, i3c-based-management-communication-interface, management-communication-interface, cmis-management-stack]
sources: [../sources/oif2026-057-01-firmware-functional-design-authority-cmis-over-i3c.md, ../sources/oif2026-057-01-i3cmci-draft.md]
status: draft
---

# CMIS Over I3C Firmware Architecture

CMIS over I3C firmware architecture is the implementation layer that turns the draft I3CMCI transport into a production-ready module subsystem. It sits below the CMIS register model and above the MCU-specific I3C peripheral blocks.

## What It Must Cover

- I3C target/slave behavior for CMIS modules.
- Negotiation between legacy I2C mode and I3C mode.
- Dynamic address assignment and event signaling.
- Read/write/test access primitives that preserve CMIS register semantics.
- Coherency across multi-byte register and memory accesses.
- Timing contracts, reset recovery, and fallback to I2C.

## Implementation Concerns

- A portable HAL is required if the same stack will run on STM32, ADI, or future MCUs.
- The protocol layer should not embed MCU-specific assumptions.
- Production validation must include at least two independent controller implementations to catch host-specific edge cases.

## Why It Matters

The draft I3CMCI specification defines what the bus behavior should be. This architecture concern defines how a module vendor actually ships that behavior without breaking legacy I2C hosts or CMIS timing guarantees.

## Related Pages

- [i3c-based-management-communication-interface](i3c-based-management-communication-interface.md)
- [management-communication-interface](management-communication-interface.md)
- [cmis-management-stack](cmis-management-stack.md)

