---
type: source
title: OIF-CMIS-FF-01.0
created: 2026-05-25
updated: 2026-05-25
tags: [cmis, oif, supplement, form-factor, source]
related: [cmis-form-factor-management, management-interface, management-memory-map, cmis-supplements]
authors: [OIF Physical and Link Layer Working Group]
year: 2024
url: "https://www.oiforum.com/"
venue: OIF Implementation Agreement
source_filename: OIF-CMIS-FF-01.0.pdf
source_note: Raw source file is not included in this wiki-only repository.
---

# OIF-CMIS-FF-01.0

OIF-CMIS-FF-01.0 defines form-factor-specific hardware management features used together with CMIS.

## Scope

CMIS-FF maps form-factor hardware controls and status signals into the CMIS management model. It is meant to provide management coverage comparable to legacy form-factor specifications such as SFF-8472, SFF-8636, and SFP-DD MSA MIS, while keeping the generic CMIS register and state-machine model intact.

## Main Areas

- Form-factor-specific Management Signaling Layer signal names.
- Mapping between generic CMIS signal names and form-factor signal names.
- Hardware transmit disable and rate-select behavior.
- Page 05h allocation for CMIS-FF registers.
- Signal features such as IntL, RxLOS, TxFault, LPMode, TxDis, and Rate Select.
- Form-factor handling for SFP112, SFP-DD, SFP-DD112, QSFP112, QSFP-DD, QSFP-DD800, and QSFP-DD1600.

## Wiki Entry Points

- [[cmis-form-factor-management]]
- [[management-interface]]
- [[management-memory-map]]
- [[cmis-supplements]]

Source anchors: abstract and table of contents, OIF-CMIS-FF-01.0.
