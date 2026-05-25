---
type: query
title: How Should a Host Bring Up a CMIS Module?
created: 2026-05-25
updated: 2026-05-25
tags: [cmis, host-flow, initialization]
related: [module-state-machine, data-path-state-machine, control-sets, management-memory-map]
sources: [oif-cmis-05-3]
---

# How Should a Host Bring Up a CMIS Module?

## Short Answer

A host should bring up a CMIS module in two layers: first establish module manageability through the [[module-state-machine]], then configure and initialize desired [[applications-and-data-paths]] through [[control-sets]] and the [[data-path-state-machine]].

## Typical Flow

1. Apply power and release or deassert Reset according to form factor rules.
2. Wait until the module becomes manageable in ModuleLowPwr, respecting `tMgmtInit`.
3. Read Lower Memory and Page 00h/01h advertisements to identify module type, CMIS version, memory capabilities, power, Applications, and optional features.
4. Decide whether to remain in low power for setup or allow transition toward ModuleReady.
5. Prepare desired Application and Data Path configuration in a Staged Control Set.
6. Apply staged settings to provision the Active Control Set.
7. Request Data Path initialization by clearing the relevant DPDeinit bits.
8. Watch Data Path state and flags until the target Data Paths reach DPInitialized or DPActivated.
9. Enable or leave enabled Tx/Rx outputs according to policy and application requirements.

## Notes

Appendix D gives example initialization flows for quick hardware initialization, quick software initialization, and software configuration plus initialization. These examples intentionally omit some module-specific variations.

Source anchors: sections 6.3.2, 6.3.3, and Appendix D, PDF pages 74-93 and 388-393.
