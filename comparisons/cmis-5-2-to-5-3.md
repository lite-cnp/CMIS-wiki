---
type: comparison
title: CMIS 5.2 to 5.3
created: 2026-05-25
updated: 2026-05-25
tags: [cmis, revision-history, comparison]
related: [sources/oif-cmis-05-3, management-communication-interface, versatile-diagnostics-monitoring, command-data-block, network-path-applications]
sources: [oif-cmis-05-3]
---

# CMIS 5.2 to 5.3

CMIS 5.3 is presented as backwards compatible with CMIS 5.2: existing CMIS 5.2-compliant host and module implementations are also CMIS 5.3-compliant.

## Major Additions

| Area | 5.3 Change |
|---|---|
| CPO and ELSFP | Adds project-based support hooks and resource module concepts |
| MCI | Adds [SPIMCI](../concepts/management-communication-interface.md#variants) |
| Applications | Adds Normalized Application Descriptors for up to 240 Applications |
| Configuration | Allows partial support advertisement for intervention-free reconfiguration |
| VDM | Adds optional power-saving mode and new FEC symbol error weight observables |
| CDB | Adds new query, PM, security, and externally defined feature commands |
| Memory map | Adds/updates pages and advertisements for host lane switching, C-CMIS, CMIS-FF, CMIS-VCS, CMIS-LT, and resource modules |
| Document structure | Adds resource module section, supplement section, compatibility section, and SPIMCI appendix |

## Compatibility Takeaway

The main host risk is not baseline compliance. It is assuming that optional 5.3 features exist before reading advertisements. Hosts should continue to discover capabilities through the memory map and use feature-specific pages only when advertised.

Source anchor: revision history, PDF pages 8-10.
