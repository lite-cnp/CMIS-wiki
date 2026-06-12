---
type: concept
title: Versatile Diagnostics Monitoring
created: 2026-05-25
updated: 2026-05-25
tags: [cmis, vdm, diagnostics, monitoring]
related: [management-memory-map, cmis-timing-model, command-data-block, coherent-cmis, multipath-interference-mpi-metrics]
sources: [oif-cmis-05-4, oif-cmis-05-3, broadcom-2025-mpi-metrics-feature]
---

# Versatile Diagnostics Monitoring

Versatile Diagnostics Monitoring (VDM) is an optional CMIS feature for exposing extensible diagnostics and performance observables.

## Memory Structure

| Pages | Purpose |
|---|---|
| 20h-23h | Observable descriptors |
| 24h-27h | Real-time sample values |
| 28h-2Bh | Threshold sets |
| 2Ch | Threshold-crossing flags |
| 2Dh | Masks |
| 2Fh | Advertisements and dynamic controls |

## Observable Model

A module can advertise up to 256 observables for each group of eight lanes. Observables may be module-level, Data Path-level, or lane-specific.

## Statistics Model

VDM distinguishes short sampling intervals from longer host-defined statistics collection intervals. The host can use Freeze and Unfreeze behavior to close a statistics interval and read stable min, max, average, or accumulated values.

## Important 5.3 Changes

CMIS 5.3 adds VDM power-saving support, adds symbol error weight statistics, and adds CPO-related monitors such as power supply and external laser optical input power observables.

## Important 5.4 Notes

CMIS 5.4 corrects and clarifies some VDM observable definitions, especially tunable laser observables, and refines VDM Freeze timing and handshake behavior. It also retains VDM as a key extension point used by supplements such as [coherent-cmis](coherent-cmis.md).

## Vendor Metric Mapping Boundary

Vendor diagnostics such as [multipath-interference-mpi-metrics](multipath-interference-mpi-metrics.md) may be candidates for CMIS exposure, but they are not base VDM observables unless a module advertises and describes them through a concrete VDM descriptor. Hosts should rely on the advertised descriptor for identity, lane association, units, scaling, and thresholds.

Source anchors: CMIS 5.4 revision history, section 7.1, and VDM page descriptions.
