---
type: concept
title: Vendor-Specific CMIS Customizations
created: 2026-05-25
updated: 2026-06-09
tags: [cmis, vendor-specific, custom]
related: [sources/google-gmis-imdd-transceiver-customizations, sources/lumentum-2026-8023dj-apsu-ilt-support-plan, sources/lumentum-2026-dpsm-apsu-ilt-state-machine, sources/broadcom-2026-sian3-apsu-application-notes, sources/broadcom-2025-sian3-ilt-procedure, management-memory-map, cmis-supplements, autonomous-path-startup]
sources: [google-gmis-imdd-transceiver-customizations, lumentum-2026-8023dj-apsu-ilt-support-plan, lumentum-2026-dpsm-apsu-ilt-state-machine, broadcom-2026-sian3-apsu-application-notes, broadcom-2025-sian3-ilt-procedure, oif-cmis-05-4]
---

# Vendor-Specific CMIS Customizations

Vendor-specific CMIS customization documents can define behavior that is useful in a particular ecosystem but is not part of the OIF CMIS base specification or an OIF supplement.

## Interpretation Boundary

Use the following hierarchy when classifying behavior:

1. Base CMIS behavior from [oif-cmis-05-4](../sources/oif-cmis-05-4.md).
2. OIF supplement behavior from [cmis-supplements](cmis-supplements.md).
3. Draft OIF/IEEE behavior, clearly marked as draft.
4. Vendor-specific behavior, used only in the vendor-defined context.

## Memory Map Rule

Vendor behavior should be treated as custom unless it is advertised through standard CMIS capability fields or placed in a standard OIF supplement area. Do not let vendor-only assumptions leak into base host logic.

## Current Vendor Sources

[google-gmis-imdd-transceiver-customizations](../sources/google-gmis-imdd-transceiver-customizations.md) is present in the raw source set, but the extracted text is not clean enough for detailed wiki extraction.

[lumentum-2026-8023dj-apsu-ilt-support-plan](../sources/lumentum-2026-8023dj-apsu-ilt-support-plan.md) is the current APSU/iLT customer-note plan. It classifies current firmware support as NVIDIA-defined vendor CDB commands and Page 70h support as planned, not implemented yet.

[lumentum-2026-dpsm-apsu-ilt-state-machine](../sources/lumentum-2026-dpsm-apsu-ilt-state-machine.md) is a state-machine diagram source for the same plan. It keeps APSU/iLT outside DPSM and states that `DPActivated` is CMIS configuration complete, while live Ethernet DATA readiness still depends on APSU/LT status.

[broadcom-2026-sian3-apsu-application-notes](../sources/broadcom-2026-sian3-apsu-application-notes.md) is a Broadcom Sian3 customer application note for APSU/link-training behavior. It is useful for implementation and diagnostics, but its cAPI fields are vendor-specific and should not be treated as base CMIS registers.

[broadcom-2025-sian3-ilt-procedure](../sources/broadcom-2025-sian3-ilt-procedure.md) is an older Broadcom Sian3 ILT procedure/log note. It is classified as obsolete because the newer APSU application note uses later firmware scope and provides the current feature/fault/status model.
