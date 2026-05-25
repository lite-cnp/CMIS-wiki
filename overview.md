---
type: overview
title: OIF CMIS Wiki Overview
created: 2026-05-21
updated: 2026-05-25
tags: [cmis, oif, spec]
related: [sources/oif-cmis-05-4, cmis-5-4-implementer-map, cmis-document-family-map, cmis-management-stack]
sources: [oif-cmis-05-4, oif-cmis-05-3]
---

# OIF CMIS Wiki Overview

This wiki digests the OIF **Common Management Interface Specification** document family, centered on [[sources/oif-cmis-05-4|OIF-CMIS-05.4]] as the current base revision and retaining [[sources/oif-cmis-05-3|OIF-CMIS-05.3]] as the earlier baseline.

Start with [[cmis-5-4-implementer-map]] for implementation reading order and [[cmis-document-family-map]] for source classification.

## Current Base

- [[sources/oif-cmis-05-4]] - current base specification source page.
- [[cmis-5-4]] - concise concept page for the 5.4 revision.
- [[cmis-5-3-to-5-4]] - delta from the prior wiki baseline.
- [[sources/oif-cmis-05-3]] - retained CMIS 5.3 source page.

## Core Architecture

- [[cmis-management-stack]] - layered view of CMIS management.
- [[management-interface]] - MSL, RAL, and MCI in the management interface.
- [[register-access-layer]] - READ, WRITE, TEST, hold-off, and coherency.
- [[management-communication-interface]] - I2CMCI, SPIMCI, and draft I3CMCI transport context.
- [[management-memory-map]] - lower/upper memory, pages, banks, access types, flags, and masks.

## Core Behaviors

- [[applications-and-data-paths]] - how modules advertise and instantiate transmission functions.
- [[control-sets]] - staged and active configuration mechanism.
- [[module-state-machine]] - module power and manageability lifecycle.
- [[data-path-state-machine]] - Data Path initialization and activation lifecycle.
- [[network-path-applications]] - client encapsulation and multiplexing support.

## Advanced Features

- [[versatile-diagnostics-monitoring]] - extensible observables, thresholds, flags, and statistics.
- [[command-data-block]] - optional command/reply messaging.
- [[cmis-timing-model]] - timing limits relevant to host management.
- [[cmis-supplements]] - optional supplement specifications and compatibility rules.

## Supplements and Companion Documents

- [[cmis-versatile-control-set]] - VCS signal-integrity parameter extension.
- [[coherent-cmis]] - coherent module supplement.
- [[cmis-form-factor-management]] - form-factor hardware management supplement.
- [[elsfp-cmis]] - standalone companion IA for ELSFP resource modules.

## Draft and External References

- [[i3c-based-management-communication-interface]] - draft I3C-based MCI.
- [[autonomous-path-startup]] - draft CMIS integration with IEEE 802.3dj APSU.
- [[sources/ieee-p802-3dj-d2-3]] - IEEE draft source for APSU, RTS, and ILT.
- [[vendor-specific-cmis-customizations]] - boundary for vendor-specific GMIS/custom behavior.

## Important Correction

This wiki is about **OIF Common Management Interface Specification**, not the unrelated OASIS content-management CMIS standard.
