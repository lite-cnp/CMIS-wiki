---
type: comparison
title: MIPI I3C Basic v1.1.1 vs v1.2
created: 2026-06-15
updated: 2026-06-15
tags: [i3c, mipi, comparison, baseline, versioning]
related: [../sources/mipi-i3c-basic-v1-1-1.md, ../sources/mipi-i3c-basic-faq-v1-1-1.md, ../concepts/i3c-based-management-communication-interface.md, ../synthesis/cmis-over-i3c-roadmap.md]
sources: [../sources/mipi-i3c-basic-v1-1-1.md, ../sources/mipi-i3c-basic-faq-v1-1-1.md, ../sources/mipi-i3c-basic-v1-2-hot-join-app-note.md, ../sources/mipi-i3c-virtual-devices-and-targets-app-note.md, ../sources/mipi-i3c-version-history-table.md, ../sources/mipi-i3c-basic-v1-2-whats-new-webinar.md]
status: draft
---

# MIPI I3C Basic v1.1.1 vs v1.2

This note compares the uploaded public `v1.1.1` baseline with the `v1.2` direction called out by the public FAQ and supporting MIPI materials.

## High-Level Difference

`v1.2` is presented by MIPI as the newest recommended version set, while `v1.1.1` remains a valid public baseline and a local reference point for the vault.

## What Stays Stable

- Public Basic subset availability for non-members
- Two-wire I3C / I3C Basic framing model
- Controller and target role model
- Dynamic Address Assignment, Hot-Join, and IBI as core I3C concepts
- Use as the public base for CMIS-over-I3C planning

## What The Public FAQ Says Changed

- `I3C Basic v1.2` is primarily an editorial update to `v1.1.1`
- It incorporates fixes, improvements, and clarifications from the v1.1.1 errata and v1.2 updates
- MIPI recommends implementers move to `I3C v1.2` / `I3C Basic v1.2` as the newest recommended versions

## Practical Implication For CMIS Over I3C

- Treat the uploaded `v1.1.1` PDF as the captured local baseline
- Use the FAQ and companion docs to understand the path to the newer recommendation
- Avoid treating `v1.1.1` as a frozen long-term target when the vault is aiming at current public guidance
- For I3CMCI, use the newer MIPI version family as a protocol-family baseline, but only require the subset of controller/target behavior that I3CMCI actually uses; see [i3cmci-required-subset-vs-mipi-i3c-feature-set](i3cmci-required-subset-vs-mipi-i3c-feature-set.md).

## Related Pages

- [mipi-i3c-basic-v1-1-1](../sources/mipi-i3c-basic-v1-1-1.md)
- [mipi-i3c-basic-faq-v1-1-1](../sources/mipi-i3c-basic-faq-v1-1-1.md)
- [i3c-based-management-communication-interface](../concepts/i3c-based-management-communication-interface.md)
- [i3cmci-required-subset-vs-mipi-i3c-feature-set](i3cmci-required-subset-vs-mipi-i3c-feature-set.md)
- [cmis-over-i3c-roadmap](../synthesis/cmis-over-i3c-roadmap.md)
