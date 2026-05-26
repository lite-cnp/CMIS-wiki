---
type: concept
title: CMIS Management Stack
created: 2026-05-25
updated: 2026-05-25
tags: [cmis, architecture, management-stack]
related: [management-interface, register-access-layer, management-communication-interface, command-data-block, management-memory-map, cmis-supplements]
sources: [oif-cmis-05-4, oif-cmis-05-3]
---

# CMIS Management Stack

CMIS is easiest to understand as a layered management stack between a [cmis-host](../entities/cmis-host.md) and a [cmis-managed-module](../entities/cmis-managed-module.md).

## Layers

| Layer | Role | Wiki Page |
|---|---|---|
| Management application layer | Defines meaning and behavioral effects of management operations | [applications-and-data-paths](applications-and-data-paths.md), [control-sets](control-sets.md), [module-state-machine](module-state-machine.md) |
| Optional message layer | Provides host-command/module-reply messaging | [command-data-block](command-data-block.md) |
| Register Access Layer | Provides READ, WRITE, and TEST over a 256-byte window | [register-access-layer](register-access-layer.md) |
| Data transfer layer | Carries access primitives over a concrete bus/protocol | [management-communication-interface](management-communication-interface.md) |
| Management Signaling Layer | Provides discrete low-speed management signals | [management-interface](management-interface.md) |
| Physical interconnection layer | Provided by form factor hardware specifications | [cmis-supplements](cmis-supplements.md) |

## Design Point

The key design choice is that a small byte-oriented register interface remains the mandatory core, while more complex behavior is layered through pages, banks, advertisements, state machines, and optional CDB messages.

CMIS 5.4 keeps that design point and expands the advertised feature model so supplements, larger lane/application counts, and new page groups can be discovered before use.

Source anchor: CMIS 5.4 section 4.2.
