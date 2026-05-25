---
type: concept
title: Vendor-Specific CMIS Customizations
created: 2026-05-25
updated: 2026-05-25
tags: [cmis, vendor-specific, custom]
related: [sources/google-gmis-imdd-transceiver-customizations, management-memory-map, cmis-supplements]
sources: [google-gmis-imdd-transceiver-customizations, oif-cmis-05-4]
---

# Vendor-Specific CMIS Customizations

Vendor-specific CMIS customization documents can define behavior that is useful in a particular ecosystem but is not part of the OIF CMIS base specification or an OIF supplement.

## Interpretation Boundary

Use the following hierarchy when classifying behavior:

1. Base CMIS behavior from [[sources/oif-cmis-05-4]].
2. OIF supplement behavior from [[cmis-supplements]].
3. Draft OIF/IEEE behavior, clearly marked as draft.
4. Vendor-specific behavior, used only in the vendor-defined context.

## Memory Map Rule

Vendor behavior should be treated as custom unless it is advertised through standard CMIS capability fields or placed in a standard OIF supplement area. Do not let vendor-only assumptions leak into base host logic.

## Current Source Stub

[[sources/google-gmis-imdd-transceiver-customizations]] is present in the raw source set, but the extracted text is not clean enough for detailed wiki extraction.
