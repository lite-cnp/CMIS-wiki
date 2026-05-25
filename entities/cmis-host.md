---
type: entity
title: CMIS Host
created: 2026-05-25
updated: 2026-05-25
tags: [cmis, host, management]
related: [cmis-managed-module, management-interface, register-access-layer, command-data-block, cmis-supplements]
sources: [oif-cmis-05-4, oif-cmis-05-3]
---

# CMIS Host

A CMIS host is the managing side of the interface. It initiates management communication, reads and writes the module memory map, reacts to interrupts, and configures module functionality through advertised standard features.

## Responsibilities

- Discover whether the attached [[cmis-managed-module]] is CMIS-compliant.
- Read static and dynamic advertisements before using optional functionality.
- Use the [[register-access-layer]] READ, WRITE, and TEST primitives correctly.
- Configure [[applications-and-data-paths]] through [[control-sets]].
- Handle [[module-state-machine]] and [[data-path-state-machine]] transitions.
- Poll or respond to flags and interrupts.
- Use [[command-data-block]] only when it is advertised.
- Respect timing, access hold-off, and synchronization requirements from the [[cmis-timing-model]].

## Implementation Notes

The host is always the MCI initiator/controller side, while the module is always the MCI target side. This matters for [[management-communication-interface]] variants such as I2CMCI, SPIMCI, and draft I3CMCI.

Hosts should treat optional, draft, and custom extensions conservatively: use standard CMIS management first, then enable optional features only after advertisements show support and the relevant supplement or draft is in scope.

Source anchors: CMIS 5.4 sections 4.2, 5.2, and Appendix B.
