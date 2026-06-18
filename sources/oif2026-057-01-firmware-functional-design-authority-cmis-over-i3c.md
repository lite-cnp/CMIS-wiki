---
type: source
title: OIF 2026.057.01 Firmware Functional Design Authority for CMIS over I3C
created: 2026-06-15
updated: 2026-06-18
tags: [cmis, oif, i3c, mci, firmware, architecture, source]
related: [../concepts/i3c-based-management-communication-interface.md, ../concepts/management-communication-interface.md, ../concepts/cmis-management-stack.md]
authors: [Lumentum]
year: 2026
venue: Internal role / architecture note
source_filename: oif2026.057.01.docx
converted_markdown: raw/sources/markdown/oif2026.057.01.md
status: draft
---

# OIF 2026.057.01 Firmware Functional Design Authority for CMIS over I3C

This internal note defines the responsibilities for a firmware functional design authority owning the CMIS-over-I3C target/slave subsystem. It is not a CMIS specification, but it is a useful implementation guide for the draft I3CMCI transport. Its broad MIPI I3C feature list should be read as expertise and possible extension coverage, not as the minimum I3CMCI baseline.

## Scope

The note focuses on end-to-end ownership of the I3C target firmware subsystem for pluggable transceivers. It treats I3CMCI as the transport layer for CMIS management over MIPI I3C Basic while preserving backward compatibility with legacy I2C hosts.

## Main Responsibilities

- Own the I3C target/slave subsystem architecture and roadmap.
- Design the I3CMCI-compliant protocol stack. The original note lists broad I3C expertise areas such as SDR and HDR modes, CCC handling, DAA, IBI generation, hot-join, and controller arbitration; the current scope decision narrows the mandatory baseline to the I3CMCI-required subset.
- Ensure transparent fallback to I2C mode for legacy hosts.
- Preserve CMIS coherency and timing behavior across register and memory accesses.
- Define a portable HAL so the protocol layer can be reused across MCUs.
- Lead implementation on STM32H563 and ADuCM45x targets.
- Own a production-line I3C host adapter concept for manufacturing use.
- Produce porting guides, interface specs, and validation strategy documentation.

## Validation Themes

- Verify I3CMCI behavior against multiple independent I3C controller implementations.
- Confirm correct handling of required CCCs and access primitives.
- Validate the I2C-to-I3C negotiation flow and the 250 ms NACK-based recovery rule.
- Confirm I2C backward compatibility at standard I2C rates.

## Relationship To The Draft

The note references the draft I3CMCI specification and is best read as an implementation companion to [oif2026-057-01-i3cmci-draft](oif2026-057-01-i3cmci-draft.md).

The required/not-required feature boundary is tracked in [i3cmci-required-subset-vs-mipi-i3c-feature-set](../comparisons/i3cmci-required-subset-vs-mipi-i3c-feature-set.md).

## Extraction Notes

- MarkItDown conversion succeeded on 2026-06-18 after installing the optional `markitdown[docx]` dependency.
- The generated Markdown cache is `CMIS/raw/sources/markdown/oif2026.057.01.md`.

## Wiki Entry Points

- [i3c-based-management-communication-interface](../concepts/i3c-based-management-communication-interface.md)
- [management-communication-interface](../concepts/management-communication-interface.md)
- [cmis-management-stack](../concepts/cmis-management-stack.md)

Source anchor: the uploaded DOCX content in `CMIS/raw/sources/oif2026.057.01.docx`.
