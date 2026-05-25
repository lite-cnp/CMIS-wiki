---
type: concept
title: CMIS Supplements
created: 2026-05-25
updated: 2026-05-25
tags: [cmis, supplements, extensions]
related: [oasis-oif, management-interface, network-path-applications, cmis-document-family-map]
sources: [oif-cmis-05-4, oif-cmis-05-3]
---

# CMIS Supplements

CMIS supplements define extensions or restrictions for important subclasses of CMIS-managed modules while relying on the CMIS base specification.

## Supplements Mentioned in CMIS 5.4

- [[cmis-versatile-control-set|CMIS-VCS]]: Versatile Control Set for signal-integrity parameters.
- [[coherent-cmis|C-CMIS]]: coherent transmission capabilities.
- [[cmis-form-factor-management|CMIS-FF]]: form-factor-specific management facilities.
- CMIS-LT: host-to-module electrical link training support.
- [[elsfp-cmis|CMIS-ELSFP]]: external laser source resource modules.

## Compatibility Principle

A module within the scope of a supplement must still behave as a standard CMIS module by default when inserted into an arbitrary CMIS host. Supplement-specific behavior should require a host that understands and intentionally enables it.

## Classification Notes

- VCS, C-CMIS, and CMIS-FF are optional OIF supplement branches for CMIS managed modules.
- ELSFP is listed in the CMIS supplement family, but this wiki tracks it as a standalone companion IA because it defines an external laser resource module profile.
- Draft work such as [[i3c-based-management-communication-interface]] and [[autonomous-path-startup]] should stay marked as draft until published in a final base revision or supplement.
- Vendor-specific material belongs under [[vendor-specific-cmis-customizations]] unless an OIF source standardizes it.

Source anchor: CMIS 5.4 section 1.1.2.
