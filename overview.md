---
type: overview
title: OIF CMIS Wiki Overview
created: 2026-05-21
updated: 2026-06-18
tags: [cmis, oif, spec]
related: [sources/oif-cmis-05-4, sources/cmis-raw-markdown-extraction, cmis-5-4-implementer-map, cmis-document-family-map, cmis-management-stack]
sources: [cmis-raw-markdown-extraction, oif-cmis-05-4, oif-cmis-05-3]
---

# OIF CMIS Wiki Overview

This wiki digests the OIF **Common Management Interface Specification** document family, centered on [OIF-CMIS-05.4](sources/oif-cmis-05-4.md) as the current base revision and retaining [OIF-CMIS-05.3](sources/oif-cmis-05-3.md) as the earlier baseline.

Start with [cmis-5-4-implementer-map](synthesis/cmis-5-4-implementer-map.md) for implementation reading order and [cmis-document-family-map](synthesis/cmis-document-family-map.md) for source classification.

For full-text search across raw PDF/DOCX/PPTX materials, use [cmis-raw-markdown-extraction](sources/cmis-raw-markdown-extraction.md) as the extraction manifest and caveat list.

## Current Base

- [oif-cmis-05-4](sources/oif-cmis-05-4.md) - current base specification source page.
- [cmis-5-4](concepts/cmis-5-4.md) - concise concept page for the 5.4 revision.
- [cmis-5-3-to-5-4](comparisons/cmis-5-3-to-5-4.md) - delta from the prior wiki baseline.
- [oif-cmis-05-3](sources/oif-cmis-05-3.md) - retained CMIS 5.3 source page.

## Core Architecture

- [cmis-management-stack](concepts/cmis-management-stack.md) - layered view of CMIS management.
- [management-interface](concepts/management-interface.md) - MSL, RAL, and MCI in the management interface.
- [register-access-layer](concepts/register-access-layer.md) - READ, WRITE, TEST, hold-off, and coherency.
- [management-communication-interface](concepts/management-communication-interface.md) - I2CMCI, SPIMCI, and draft I3CMCI transport context.
- [management-memory-map](concepts/management-memory-map.md) - lower/upper memory, pages, banks, access types, flags, and masks.

## Core Behaviors

- [applications-and-data-paths](concepts/applications-and-data-paths.md) - how modules advertise and instantiate transmission functions.
- [control-sets](concepts/control-sets.md) - staged and active configuration mechanism.
- [module-state-machine](concepts/module-state-machine.md) - module power and manageability lifecycle.
- [data-path-state-machine](concepts/data-path-state-machine.md) - Data Path initialization and activation lifecycle.
- [network-path-applications](concepts/network-path-applications.md) - client encapsulation and multiplexing support.

## Advanced Features

- [versatile-diagnostics-monitoring](concepts/versatile-diagnostics-monitoring.md) - extensible observables, thresholds, flags, and statistics.
- [command-data-block](concepts/command-data-block.md) - optional command/reply messaging.
- [cmis-timing-model](concepts/cmis-timing-model.md) - timing limits relevant to host management.
- [cmis-supplements](concepts/cmis-supplements.md) - optional supplement specifications and compatibility rules.

## Supplements and Companion Documents

- [cmis-versatile-control-set](concepts/cmis-versatile-control-set.md) - VCS signal-integrity parameter extension.
- [coherent-cmis](concepts/coherent-cmis.md) - coherent module supplement.
- [cmis-form-factor-management](concepts/cmis-form-factor-management.md) - form-factor hardware management supplement.
- [elsfp-cmis](concepts/elsfp-cmis.md) - standalone companion IA for ELSFP resource modules.

## Draft and External References

- [i3c-based-management-communication-interface](concepts/i3c-based-management-communication-interface.md) - draft I3C-based MCI.
- [autonomous-path-startup](concepts/autonomous-path-startup.md) - draft CMIS integration with IEEE 802.3dj APSU.
- [ieee-p802-3dj-d2-3](sources/ieee-p802-3dj-d2-3.md) - IEEE draft source for APSU, RTS, and ILT.
- [vendor-specific-cmis-customizations](concepts/vendor-specific-cmis-customizations.md) - boundary for vendor-specific GMIS/custom behavior.

## Important Correction

This wiki is about **OIF Common Management Interface Specification**, not the unrelated OASIS content-management CMIS standard.
