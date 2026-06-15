---
type: source
title: MIPI I3C Basic v1.1.1
created: 2026-06-15
updated: 2026-06-15
tags: [i3c, mipi, specification, basic, source]
related: [../concepts/i3c-based-management-communication-interface.md, ../concepts/management-communication-interface.md, ../concepts/cmis-over-i3c-roadmap.md]
authors: [MIPI Alliance]
year: 2021
venue: MIPI Specification
source_filename: raw/sources/I3CMCI/I3C_MIPI-v1.1.1.pdf
status: draft
---

# MIPI I3C Basic v1.1.1

This is the public MIPI I3C Basic specification, version 1.1.1. It is the real normative base reference for the public Basic subset and a more authoritative source than the companion FAQ or app notes.

For the purposes of this vault, treat this file as the captured public baseline, while the FAQ and MIPI download page point forward to the newer `v1.2` recommendation.

## Scope

MIPI I3C Basic v1.1.1 defines the public subset of the I3C family. It covers the two-wire bus model, controller and target roles, dynamic address assignment, in-band interrupts, hot-join, timing and error handling, CCCs, and the features that are included or excluded relative to the full I3C family.

## Why It Matters For CMIS Over I3C

- It is the closest public baseline for the draft I3CMCI transport.
- It establishes the public Basic feature set that a CMIS-over-I3C target can reasonably rely on.
- It provides the normative background for controller, target, DAA, IBI, hot-join, error recovery, and timing behavior.

## Representative Coverage

- Basic two-wire I3C bus behavior and backward compatibility with legacy I2C
- Controller and target role model
- Dynamic Address Assignment
- In-Band Interrupts
- Hot-Join
- Common Command Codes
- SDR error detection and recovery
- Target Reset
- HDR-related data transfer and framing behavior

## Wiki Entry Points

- [i3c-based-management-communication-interface](../concepts/i3c-based-management-communication-interface.md)
- [management-communication-interface](../concepts/management-communication-interface.md)
- [cmis-over-i3c-roadmap](../synthesis/cmis-over-i3c-roadmap.md)

Source anchor: title page, contents, introduction, and core transport sections of the uploaded PDF.
