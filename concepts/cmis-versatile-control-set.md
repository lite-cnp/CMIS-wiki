---
type: concept
title: CMIS Versatile Control Set
created: 2026-05-25
updated: 2026-05-25
tags: [cmis, vcs, control-sets, signal-integrity]
related: [sources/oif-cmis-vcs-01-1, control-sets, management-memory-map, cmis-supplements]
sources: [oif-cmis-vcs-01-1, oif-cmis-05-4]
---

# CMIS Versatile Control Set

CMIS Versatile Control Set, or CMIS-VCS, is an optional supplement that generalizes the fixed signal-integrity fields in base CMIS [[control-sets]].

## Problem It Solves

Base CMIS provides a standard set of signal-integrity controls. Advanced modules may need additional SI parameters, different parameter placement, or a module-specific parameter list. VCS lets the module advertise those parameters and their register locations.

## Host Model

1. Detect VCS support from the base CMIS advertisement.
2. Read the VCS parameter description from the advertised parameter space.
3. Treat VCS fields as part of the Control Set flow, not as independent side-band tuning.
4. Fall back to base CMIS fields when VCS is not advertised or not understood.

## Memory Map Touchpoints

CMIS 5.4 reserves VCS parameter space on Pages 18h and 19h. CDB command ranges are also restricted for VCS supplement use.

## Related Pages

- [[sources/oif-cmis-vcs-01-1]]
- [[control-sets]]
- [[management-memory-map]]
- [[cmis-supplements]]
