---
type: source
title: OIF-CMIS-VCS-01.1
created: 2026-05-25
updated: 2026-05-25
tags: [cmis, oif, supplement, vcs, signal-integrity, source]
related: [cmis-versatile-control-set, control-sets, cmis-supplements]
authors: [OIF Physical and Link Layer Working Group]
year: 2025
url: "https://www.oiforum.com/"
venue: OIF Implementation Agreement
source_filename: OIF-CMIS-VCS-01.1.pdf
source_note: Raw source file is not included in this wiki-only repository.
---

# OIF-CMIS-VCS-01.1

OIF-CMIS-VCS-01.1 defines CMIS Versatile Control Sets. It generalizes CMIS signal-integrity control handling by letting a module advertise a module-specific list of signal-integrity parameters and where those parameters live in the CMIS Control Set space.

## Scope

The supplement extends [control-sets](../concepts/control-sets.md) without breaking base CMIS compatibility. A host that does not understand VCS can continue to use the base CMIS behavior. A VCS-aware host can discover additional SI properties and use the versatile parameter space when the module advertises support.

## Revision 1.1 Highlights

- Adds LPO-related support.
- Adds an EqualizerTarget attribute.
- Adds a PropertyFlags attribute to indicate host or media interface context.
- Fixes the staged Control Set 0 register range.
- Updates examples and appendices.

## Wiki Entry Points

- [cmis-versatile-control-set](../concepts/cmis-versatile-control-set.md)
- [cmis-supplements](../concepts/cmis-supplements.md)
- [control-sets](../concepts/control-sets.md)
- [management-memory-map](../concepts/management-memory-map.md)

Source anchors: abstract and revision history, OIF-CMIS-VCS-01.1.
