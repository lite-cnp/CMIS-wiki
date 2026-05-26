---
type: source
title: OIF-ELSFP-CMIS-01.0
created: 2026-05-25
updated: 2026-05-25
tags: [cmis, oif, elsfp, external-laser, source]
related: [elsfp-cmis, cmis-supplements, module-state-machine, management-memory-map]
authors: [OIF Physical and Link Layer Working Group]
year: 2024
url: "https://www.oiforum.com/"
venue: OIF Implementation Agreement
source_filename: OIF-ELSFP-CMIS-01.0.pdf
source_note: Raw source file is not included in this wiki-only repository.
---

# OIF-ELSFP-CMIS-01.0

OIF-ELSFP-CMIS-01.0 defines CMIS management for External Laser Small Form Factor Pluggable modules.

## Scope

This is tracked in this vault as a standalone companion implementation agreement for ELSFP resource modules. CMIS 5.4 lists CMIS-ELSFP in the supplement family, but ELSFP is not just an optional feature branch inside ordinary transceiver applications. It defines a managed external laser resource module profile.

## Key Points

- ELSFP modules use the CMIS two-wire MCI model.
- CMIS 5.3 resource module concepts are the base.
- ELSFP modules implement the [module-state-machine](../concepts/module-state-machine.md) but do not need Data Path or Network Path state machines.
- ELSFP-specific advertisements, flags, controls, and monitors are placed on Pages 1Ah and 1Bh.
- The IA covers module and lane thresholds, flags, masks, save/restore behavior, output fiber checks, bias current, output power, lane frequency, and firmware upgrade handling.

## Wiki Entry Points

- [elsfp-cmis](../concepts/elsfp-cmis.md)
- [management-memory-map](../concepts/management-memory-map.md)
- [cmis-supplements](../concepts/cmis-supplements.md)
- [module-state-machine](../concepts/module-state-machine.md)

Source anchors: abstract, management interface section, resource module definition, and page list, OIF-ELSFP-CMIS-01.0.
