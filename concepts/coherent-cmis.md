---
type: concept
title: Coherent CMIS
created: 2026-05-25
updated: 2026-05-25
tags: [cmis, coherent, 400zr, c-cmis]
related: [sources/oif-c-cmis-01-4, command-data-block, versatile-diagnostics-monitoring, cmis-supplements]
sources: [oif-c-cmis-01-4, oif-cmis-05-4]
---

# Coherent CMIS

Coherent CMIS, or C-CMIS, is the CMIS supplement for coherent modules.

## Scope

C-CMIS extends base CMIS with coherent-specific memory pages, advertisements, diagnostics, media and host interface registers, and supplement-specific CDB commands. Its initial release family is focused on coherent 400ZR-style modules.

## Memory Map Touchpoints

CMIS 5.4 reserves banked Pages 30h-4Fh for C-CMIS registers. It also reserves a CDB command ID block for C-CMIS command definitions.

## Host Rule

A host should first use base CMIS discovery and capability advertisement. Coherent-specific behavior should only be used after the module advertises C-CMIS support.

## Related Pages

- [[sources/oif-c-cmis-01-4]]
- [[command-data-block]]
- [[versatile-diagnostics-monitoring]]
- [[management-memory-map]]
- [[cmis-supplements]]
