---
type: concept
title: ELSFP CMIS
created: 2026-05-25
updated: 2026-05-25
tags: [cmis, elsfp, external-laser, resource-module]
related: [sources/oif-elsfp-cmis-01-0, module-state-machine, management-memory-map, cmis-supplements]
sources: [oif-elsfp-cmis-01-0, oif-cmis-05-4]
---

# ELSFP CMIS

ELSFP CMIS defines CMIS management for External Laser Small Form Factor Pluggable modules.

## Classification

Treat ELSFP as a standalone companion implementation agreement for a resource module profile. CMIS 5.4 lists CMIS-ELSFP in the supplement family, but the subject is a managed external laser source module rather than a regular transceiver feature extension.

## Resource Module Model

ELSFP uses the CMIS resource module concept. It implements the [module-state-machine](module-state-machine.md) and CMIS management access, but it does not need Data Path or Network Path state machines because it does not carry a normal CMIS transmission application.

## Memory Map Touchpoints

| Page | Purpose |
|---|---|
| 1Ah | ELSFP advertisements and flags |
| 1Bh | ELSFP controls and monitors |

## Host Model

The host discovers the module as an ELSFP resource module, reads ELSFP advertisements and thresholds, supervises module and lane flags, and controls/monitors external laser behavior through the ELSFP pages.

## Related Pages

- [oif-elsfp-cmis-01-0](../sources/oif-elsfp-cmis-01-0.md)
- [management-memory-map](management-memory-map.md)
- [module-state-machine](module-state-machine.md)
- [cmis-supplements](cmis-supplements.md)
