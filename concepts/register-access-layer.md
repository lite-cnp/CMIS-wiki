---
type: concept
title: Register Access Layer
created: 2026-05-25
updated: 2026-05-25
tags: [cmis, ral, registers]
related: [management-interface, management-memory-map, management-communication-interface, cmis-timing-model]
sources: [oif-cmis-05-3]
---

# Register Access Layer

The Register Access Layer (RAL) is the essential CMIS software access model. It lets the host READ, WRITE, and TEST byte-addressed management locations in the 256-byte directly addressable window.

## Core Primitives

- **READ**: retrieve one or more bytes from the addressable memory window.
- **WRITE**: write one or more bytes to the addressable memory window.
- **TEST**: determine whether the module is ready for READ or WRITE access.

## Access Hold-Off

A module may temporarily reject access while internal work is completing. A host can handle this by using worst-case timing, retrying rejected accesses, or testing readiness before access.

## Coherency

Single-byte accesses are coherent. Size-matched READs of scalar multi-byte read-only registers are also coherent. Multi-byte WRITE operations are generally not atomic unless a specific higher-level protocol says otherwise.

## Design Implication

RAL is intentionally small. Higher-level synchronization is provided by specific mechanisms such as [[control-sets]], [[command-data-block]], flags, status fields, and handshakes.

Source anchors: sections 5.2.3-5.2.5, PDF pages 53-54.
