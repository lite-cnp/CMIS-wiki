---
type: synthesis
title: CMIS Document Family Map
created: 2026-05-25
updated: 2026-06-09
tags: [cmis, synthesis, document-map]
related: [sources/oif-cmis-05-4, cmis-supplements, elsfp-cmis, autonomous-path-startup, vendor-specific-cmis-customizations]
sources: [oif-cmis-05-4, oif-cmis-vcs-01-1, oif-cmis-ff-01-0, oif-c-cmis-01-4, oif-elsfp-cmis-01-0, lumentum-2026-8023dj-apsu-ilt-support-plan, lumentum-2026-dpsm-apsu-ilt-state-machine, broadcom-2026-sian3-apsu-application-notes, broadcom-2025-sian3-ilt-procedure]
---

# CMIS Document Family Map

This page classifies the raw CMIS-related documents in the vault so base CMIS, optional supplements, draft extensions, standalone companion IAs, IEEE references, and vendor-specific notes do not blur together.

## Base Specifications

- [oif-cmis-05-4](../sources/oif-cmis-05-4.md) - current base CMIS revision in this vault.
- [oif-cmis-05-3](../sources/oif-cmis-05-3.md) - previous base revision used for the first wiki pass.

## OIF Supplements

- [oif-cmis-vcs-01-1](../sources/oif-cmis-vcs-01-1.md) - [cmis-versatile-control-set](../concepts/cmis-versatile-control-set.md).
- [oif-cmis-ff-01-0](../sources/oif-cmis-ff-01-0.md) - [cmis-form-factor-management](../concepts/cmis-form-factor-management.md).
- [oif-c-cmis-01-4](../sources/oif-c-cmis-01-4.md) - [coherent-cmis](../concepts/coherent-cmis.md).

## Standalone Companion IA

- [oif-elsfp-cmis-01-0](../sources/oif-elsfp-cmis-01-0.md) - [elsfp-cmis](../concepts/elsfp-cmis.md) for External Laser Small Form Factor Pluggable resource modules.

## Draft Extensions

- [oif2026-057-01-i3cmci-draft](../sources/oif2026-057-01-i3cmci-draft.md) - [i3c-based-management-communication-interface](../concepts/i3c-based-management-communication-interface.md) draft.
- [oif2026-093-08-802-3dj-apsu-draft](../sources/oif2026-093-08-802-3dj-apsu-draft.md) - [autonomous-path-startup](../concepts/autonomous-path-startup.md) CMIS integration draft.

## IEEE References

- [ieee-802-3-2022](../sources/ieee-802-3-2022.md) - base IEEE Ethernet source.
- [ieee-p802-3dj-d2-3](../sources/ieee-p802-3dj-d2-3.md) - IEEE draft source for APSU, RTS, and ILT.

## Vendor-Specific Notes

- [google-gmis-imdd-transceiver-customizations](../sources/google-gmis-imdd-transceiver-customizations.md) - vendor-specific GMIS/IMDD source stub.
- [lumentum-2026-8023dj-apsu-ilt-support-plan](../sources/lumentum-2026-8023dj-apsu-ilt-support-plan.md) - current APSU/iLT customer-note plan using vendor CDB commands today and planned CMIS Page 70h alignment later.
- [lumentum-2026-dpsm-apsu-ilt-state-machine](../sources/lumentum-2026-dpsm-apsu-ilt-state-machine.md) - state-machine diagram showing APSU/iLT actions as orthogonal to DPSM.
- [broadcom-2026-sian3-apsu-application-notes](../sources/broadcom-2026-sian3-apsu-application-notes.md) - vendor-specific Broadcom Sian3 APSU/link-training implementation note using cAPI fields.
- [broadcom-2025-sian3-ilt-procedure](../sources/broadcom-2025-sian3-ilt-procedure.md) - obsolete Broadcom Sian3 ILT BERT/DUT procedure source superseded by the 2026 APSU application note.

## Classification Rule

When adding new CMIS notes, first classify the source. Do not promote draft, standalone, or vendor-specific behavior into the base CMIS model unless a published base revision or supplement explicitly does so.
