---
type: concept
title: Module State Machine
created: 2026-05-25
updated: 2026-05-25
tags: [cmis, state-machine, msm]
related: [cmis-managed-module, data-path-state-machine, control-sets, cmis-timing-model, elsfp-cmis, autonomous-path-startup]
sources: [oif-cmis-05-4, oif-cmis-05-3, oif-elsfp-cmis-01-0]
---

# Module State Machine

The Module State Machine (MSM) represents the power and manageability lifecycle of a CMIS module.

## Main States

| State | Meaning |
|---|---|
| Resetting | Module electronics and management interface transition to reset |
| Reset | Ground state after insertion, power-up, or reset |
| MgmtInit | Module initializes memory defaults and management communication |
| ModuleLowPwr | Management interface is operational while module remains in low power |
| ModulePwrUp | Module transitions toward high power |
| ModuleReady | Module is fully operational and may consume advertised high power |
| ModulePwrDn | Module transitions back toward low power |
| ModuleFault | Module waits for host action after fault handling |

## Low Power Control

LowPwrS is derived from software and hardware low-power requests. It controls module power-mode transitions, but it does not itself initialize Data Paths.

## Host Implications

The host can perform meaningful discovery and setup in ModuleLowPwr, then move the module toward ModuleReady when the system can support the advertised power. Data Paths remain separately governed by the [data-path-state-machine](data-path-state-machine.md).

## Extension Notes

- [elsfp-cmis](elsfp-cmis.md) resource modules implement MSM without needing DPSM or NPSM behavior.
- The draft [autonomous-path-startup](autonomous-path-startup.md) integration leaves MSM unchanged.

Source anchors: CMIS 5.4 section 6.3.2; OIF-ELSFP-CMIS-01.0 resource module definition.
