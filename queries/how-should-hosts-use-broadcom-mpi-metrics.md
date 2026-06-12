---
type: query
title: How Should Hosts Use Broadcom MPI Metrics
created: 2026-06-12
updated: 2026-06-12
tags: [cmis, broadcom, mpi, diagnostics, dust-detection, host-guidance]
related: [../sources/broadcom-2025-mpi-metrics-feature.md, ../concepts/multipath-interference-mpi-metrics.md, ../concepts/versatile-diagnostics-monitoring.md]
sources: [../sources/broadcom-2025-mpi-metrics-feature.md]
status: draft
---

# How Should Hosts Use Broadcom MPI Metrics

Use Broadcom MPI metrics as a vendor diagnostic for optical dust/MPI condition, not as a base CMIS feature unless the module separately exposes them through a documented CMIS register or VDM observable.

## Basic Flow

1. Confirm the module and DSP are reachable over the management path.
2. Confirm media Rx CDR lock before interpreting MPI values.
3. Use the Broadcom fast CMIS SNR interface API with `mpi_include = 1`.
4. Poll per-lane SNR/LTP output.
5. Read both `mpi_metrics` and `mpi_metrics_mpicoff` for each media lane.
6. Trend the values over time and correlate them with BER/SNR/FEC behavior.

## What To Read

- `mpi_metrics`: output-side MPI metric after MPIC correction.
- `mpi_metrics_mpicoff`: input-side-style dust detection metric estimated without disabling MPIC.

Use `mpi_metrics_mpicoff` as the safer dust-detection indicator during live traffic because it avoids turning MPIC off.

## What Not To Assume

- Do not assume these values are standardized CMIS VDM observables.
- Do not assume the unitless values are dB.
- Do not use Broadcom's note alone to set alarm thresholds.
- Do not disable MPIC during live traffic just to measure input-side MPI.

## Threshold Policy

The Broadcom note leaves tolerable limits to the module vendor and end customer. A practical host policy should therefore require:

- module-specific calibration data,
- lane-specific baseline values,
- correlation with SNR/BER/FEC evidence,
- documented warning/alarm thresholds, and
- a clear customer-facing CMIS or VDM mapping if the values leave the vendor cAPI context.

## CMIS Exposure Decision

If the module exposes these values through CMIS, prefer VDM-style exposure with explicit descriptors and thresholds. Keep the following visible in the interface specification:

- observable identity,
- lane/media-side association,
- unitless scaling,
- update cadence,
- threshold semantics,
- whether the value is `mpi_metrics` or `mpi_metrics_mpicoff`.

Source: [broadcom-2025-mpi-metrics-feature](../sources/broadcom-2025-mpi-metrics-feature.md).
