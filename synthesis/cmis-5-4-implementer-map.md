---
type: synthesis
title: CMIS 5.4 Implementer Map
created: 2026-05-25
updated: 2026-05-26
tags: [cmis, implementation, synthesis, cmis-5-4]
related: [sources/oif-cmis-05-4, cmis-5-4, management-memory-map, upper-page-0dh-register-map, applications-and-data-paths, cmis-supplements]
sources: [oif-cmis-05-4]
---

# CMIS 5.4 Implementer Map

This page is the current working entry point for implementing or reviewing CMIS behavior against Revision 5.4.

## Read First

1. [oif-cmis-05-4](../sources/oif-cmis-05-4.md) for the current source map.
2. [cmis-5-3-to-5-4](../comparisons/cmis-5-3-to-5-4.md) for the delta from the earlier wiki baseline.
3. [cmis-management-stack](../concepts/cmis-management-stack.md) for the management layering.
4. [management-memory-map](../concepts/management-memory-map.md) for addressing, pages, banks, access types, flags, and masks.
5. [module-state-machine](../concepts/module-state-machine.md), [applications-and-data-paths](../concepts/applications-and-data-paths.md), [control-sets](../concepts/control-sets.md), and [data-path-state-machine](../concepts/data-path-state-machine.md) for core bring-up behavior.

## New 5.4 Areas to Check

- Supported page and named feature advertisement on Page 0Ch.
- Firmware management additions on [Page 0Dh](../concepts/upper-page-0dh-register-map.md) and related [command-data-block](../concepts/command-data-block.md) commands.
- Lane/Data Path management and monitoring on Pages 60h and 61h.
- Media lane thresholds on Page 62h.
- Media lane switching on Page 6Dh.
- Larger lane and application scaling.

## Extension Branches

- [cmis-versatile-control-set](../concepts/cmis-versatile-control-set.md) for flexible signal-integrity controls.
- [coherent-cmis](../concepts/coherent-cmis.md) for coherent module management.
- [cmis-form-factor-management](../concepts/cmis-form-factor-management.md) for form-factor hardware signal mapping.
- [elsfp-cmis](../concepts/elsfp-cmis.md) for external laser resource modules.
- [autonomous-path-startup](../concepts/autonomous-path-startup.md) for draft 802.3dj APSU integration.
- [i3c-based-management-communication-interface](../concepts/i3c-based-management-communication-interface.md) for draft I3C-based transport.

## Practical Rule

Base CMIS gives the host the discovery and state-machine contract. Supplements and drafts add capability branches, but the host should enter those branches only after support is advertised and the relevant source document is in scope.
