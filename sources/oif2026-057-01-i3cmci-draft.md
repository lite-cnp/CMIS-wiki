---
type: source
title: OIF 2026.057.01 I3CMCI Draft
created: 2026-05-25
updated: 2026-05-25
tags: [cmis, oif, draft, i3c, mci, source]
related: [i3c-based-management-communication-interface, management-communication-interface, register-access-layer]
authors: [OIF Physical and Link Layer Working Group]
year: 2026
venue: OIF Draft Contribution
source_filename: oif2026.057.01.docx
source_note: Raw source file is not included in this wiki-only repository.
status: draft
---

# OIF 2026.057.01 I3CMCI Draft

This draft contribution defines an I3C-based Management Communication Interface, or I3CMCI, for CMIS modules.

## Scope

I3CMCI is proposed as a higher-bandwidth, lower-latency, reduced-pin-count alternative to I2C-based CMIS management while maintaining backward compatibility with legacy I2C operation.

## Main Points

- The host acts as the I3C Controller.
- The CMIS module acts as an I3C Target and does not request or assume Controller role.
- The interface uses I3C SCL/SDA with open-drain arbitration and push-pull SDR transfers.
- Supported management primitives are still register read/write oriented: READ, WRITE, and TEST.
- Dynamic address assignment is performed with ENTDAA.
- A module is I3CMCI-ready only after a dynamic address has been assigned.
- The draft describes recovery by restarting from legacy I2C negotiation after repeated dynamic-address NACKs.

## Draft Caveat

The extracted draft text contains unresolved editorial notes and some requirement-wording inconsistencies around supported Common Command Codes. Treat it as a design direction, not a final host implementation contract.

## Wiki Entry Points

- [[i3c-based-management-communication-interface]]
- [[management-communication-interface]]
- [[register-access-layer]]

Source anchor: Appendix B.4 draft text, OIF 2026.057.01.
