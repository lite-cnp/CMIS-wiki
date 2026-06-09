---
type: concept
title: CMIS Versatile Control Set
created: 2026-05-25
updated: 2026-05-26
tags: [cmis, vcs, control-sets, signal-integrity]
related: [sources/oif-cmis-vcs-01-1, control-sets, management-memory-map, upper-page-18h-register-map, upper-page-19h-register-map, command-data-block, cmis-supplements]
sources: [oif-cmis-vcs-01-1, oif-cmis-05-4]
---

# CMIS Versatile Control Set

CMIS Versatile Control Set, or CMIS-VCS, is an optional supplement that generalizes the fixed signal-integrity fields in base CMIS [control-sets](control-sets.md).

## Problem It Solves

Base CMIS provides a standard set of signal-integrity controls. Advanced modules may need additional SI parameters, different parameter placement, or a module-specific parameter list. VCS lets the module advertise those parameters and their register locations.

## Host Model

1. Detect VCS support with the externally defined features CDB command.
2. Read the VCS overview and parameter descriptors from the CMIS-VCS CDB command group.
3. Treat VCS fields as part of the Control Set flow, not as independent side-band tuning.
4. Fall back to base CMIS fields when VCS is not advertised or not understood.

## Memory Map Touchpoints

CMIS 5.4 reserves VCS parameter space on Pages 18h and 19h. These pages are lane-banked extension pages:

- [upper-page-18h-register-map](upper-page-18h-register-map.md) extends the writable staged Control Set SI-control windows.
- [upper-page-19h-register-map](upper-page-19h-register-map.md) extends the read-only active Control Set SI-status window.

The actual per-byte parameter meanings are not fixed by page number. A host builds the map from VCS Descriptor TLVs:

- CMD `0045h` advertises whether the module supports the VCS command group.
- CMD `4000h` returns VCS overview information, including version, `ApplicationMask` length, CMIS-base compatibility, overflow page requirement, and read-only parameter support.
- CMD `4001h` returns read-write VCS parameter descriptors for the staged and active Control Set spaces.
- CMD `4002h` returns read-only VCS parameter descriptors when supported; these appear only in the active Control Set space.

## Related Pages

- [oif-cmis-vcs-01-1](../sources/oif-cmis-vcs-01-1.md)
- [control-sets](control-sets.md)
- [management-memory-map](management-memory-map.md)
- [upper-page-18h-register-map](upper-page-18h-register-map.md)
- [upper-page-19h-register-map](upper-page-19h-register-map.md)
- [cmis-supplements](cmis-supplements.md)
