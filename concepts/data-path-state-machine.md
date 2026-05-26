---
type: concept
title: Data Path State Machine
created: 2026-05-25
updated: 2026-05-25
tags: [cmis, state-machine, dpsm, data-paths]
related: [applications-and-data-paths, control-sets, module-state-machine, network-path-applications, autonomous-path-startup]
sources: [oif-cmis-05-4, oif-cmis-05-3, oif2026-093-08-802-3dj-apsu-draft]
---

# Data Path State Machine

The Data Path State Machine (DPSM) reports and controls the initialization status of one Data Path. It is distinct from signal quality or output-status reporting.

## State Flow

| State | Meaning |
|---|---|
| DPDeactivated | Data Path resources are quiescent and unused |
| DPInit | Module initializes Data Path resources |
| DPInitialized | Data Path resources are initialized |
| DPTxTurnOn | Module turns on Tx outputs |
| DPActivated | Data Path Tx outputs are operational |
| DPTxTurnOff | Module turns off Tx outputs |
| DPDeinit | Module deinitializes Data Path resources |

## Control Inputs

The host controls Data Path initialization and deinitialization primarily through DPDeinit bits and through [control-sets](control-sets.md) Apply triggers. Per-lane output controls such as OutputDisableTx and OutputSquelchForceTx can affect whether a Data Path is activated.

## Status Model

The module reports the same DPSM state on all lanes belonging to the Data Path. A host usually only needs to read the first lane of the Data Path to determine the state.

## Independence

Parallel Data Paths are required to operate independently from the host viewpoint. Changing one Data Path should not interrupt unrelated Data Paths.

## APSU Draft Interaction

For IEEE 802.3dj [autonomous-path-startup](autonomous-path-startup.md) applications, DPSM remains a CMIS configuration state machine. APSU is protocol-specific and runs orthogonally:

- APSU cannot start in DPDeactivated or DPInit.
- Host-interface APSU can begin at DPInitialized.
- Media-interface APSU can begin at DPTxTurnOn.
- DPActivated means the Data Path is configured; live protocol data still depends on APSU completion.

Use [how-do-apsu-and-cmis-state-machines-interact](../queries/how-do-apsu-and-cmis-state-machines-interact.md) for the host-facing summary.

Source anchors: CMIS 5.4 section 6.3.3; OIF 2026.093.08 draft DPSM relationship tables.
