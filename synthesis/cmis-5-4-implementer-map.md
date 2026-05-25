---
type: synthesis
title: CMIS 5.4 Implementer Map
created: 2026-05-25
updated: 2026-05-25
tags: [cmis, implementation, synthesis, cmis-5-4]
related: [sources/oif-cmis-05-4, cmis-5-4, management-memory-map, applications-and-data-paths, cmis-supplements]
sources: [oif-cmis-05-4]
---

# CMIS 5.4 Implementer Map

This page is the current working entry point for implementing or reviewing CMIS behavior against Revision 5.4.

## Read First

1. [[sources/oif-cmis-05-4]] for the current source map.
2. [[cmis-5-3-to-5-4]] for the delta from the earlier wiki baseline.
3. [[cmis-management-stack]] for the management layering.
4. [[management-memory-map]] for addressing, pages, banks, access types, flags, and masks.
5. [[module-state-machine]], [[applications-and-data-paths]], [[control-sets]], and [[data-path-state-machine]] for core bring-up behavior.

## New 5.4 Areas to Check

- Supported page and named feature advertisement on Page 0Ch.
- Firmware management additions on Page 0Dh and related [[command-data-block]] commands.
- Lane/Data Path management and monitoring on Pages 60h and 61h.
- Media lane thresholds on Page 62h.
- Media lane switching on Page 6Dh.
- Larger lane and application scaling.

## Extension Branches

- [[cmis-versatile-control-set]] for flexible signal-integrity controls.
- [[coherent-cmis]] for coherent module management.
- [[cmis-form-factor-management]] for form-factor hardware signal mapping.
- [[elsfp-cmis]] for external laser resource modules.
- [[autonomous-path-startup]] for draft 802.3dj APSU integration.
- [[i3c-based-management-communication-interface]] for draft I3C-based transport.

## Practical Rule

Base CMIS gives the host the discovery and state-machine contract. Supplements and drafts add capability branches, but the host should enter those branches only after support is advertised and the relevant source document is in scope.
