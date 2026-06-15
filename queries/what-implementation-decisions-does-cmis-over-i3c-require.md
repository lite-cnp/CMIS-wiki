---
type: query
title: What implementation decisions does CMIS over I3C require?
created: 2026-06-15
updated: 2026-06-15
tags: [cmis, i3c, mci, firmware, query]
related: [../concepts/cmis-over-i3c-firmware-architecture.md, ../concepts/i3c-based-management-communication-interface.md, ../concepts/management-communication-interface.md]
sources: [../sources/oif2026-057-01-firmware-functional-design-authority-cmis-over-i3c.md, ../sources/oif2026-057-01-i3cmci-draft.md]
status: draft
---

# What implementation decisions does CMIS over I3C require?

The draft I3CMCI text answers the protocol question, but the uploaded role note shows that a production implementation still needs several vendor decisions before the transport can be treated as ship-ready.

## Short Answer

CMIS over I3C needs an explicit target-firmware architecture, a portable HAL, a negotiation and recovery policy, and a validation plan that proves the design works across more than one controller implementation and preserves CMIS timing/coherency semantics.

## Decisions To Make

1. **HAL ownership and scope**
   - Define the interface between the I3C protocol stack and MCU-specific I3C peripherals.
   - Decide what stays in the portable layer versus per-MCU adapters.

2. **Negotiation and fallback behavior**
   - Specify how the module detects legacy I2C hosts.
   - Define the exact transition from I2C mode to I3C mode.
   - Decide how the firmware recovers after repeated NACKs or an autonomous reset.

3. **CCC and readiness policy**
   - Confirm which CCCs are mandatory in the implementation.
   - Decide when the module should expose itself as I3CMCI-ready.
   - Define event-enable defaults for IBI and hot-join behavior.

4. **CMIS coherency and timing**
   - Ensure multi-byte register accesses do not tear across the transport boundary.
   - Preserve CMIS timing contracts during bus negotiation and recovery.

5. **Interoperability validation**
   - Validate against at least two independent I3C controller implementations.
   - Confirm the implementation does not rely on a single host adapter or lab stack.

6. **Production-line support**
   - Decide whether a low-cost I3C host adapter is needed for manufacturing.
   - Define the host-side control API and throughput targets if the adapter is part of the flow.

## Why This Matters

The draft spec makes I3CMCI look straightforward, but the role note makes clear that the real work is the engineering boundary: portable firmware architecture, recovery logic, and interoperability validation.

## Related Pages

- [cmis-over-i3c-firmware-architecture](../concepts/cmis-over-i3c-firmware-architecture.md)
- [i3c-based-management-communication-interface](../concepts/i3c-based-management-communication-interface.md)
- [management-communication-interface](../concepts/management-communication-interface.md)
- [oif2026-057-01-firmware-functional-design-authority-cmis-over-i3c](../sources/oif2026-057-01-firmware-functional-design-authority-cmis-over-i3c.md)
- [oif2026-057-01-i3cmci-draft](../sources/oif2026-057-01-i3cmci-draft.md)

