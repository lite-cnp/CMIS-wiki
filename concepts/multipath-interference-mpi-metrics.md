---
type: concept
title: Multipath Interference MPI Metrics
created: 2026-06-12
updated: 2026-06-15
tags: [cmis, mpi, diagnostics, dust-detection, broadcom, vendor-specific]
related: [../sources/broadcom-2025-mpi-metrics-feature.md, vendor-specific-cmis-customizations.md, versatile-diagnostics-monitoring.md]
sources: [../sources/broadcom-2025-mpi-metrics-feature.md]
status: draft
---

# Multipath Interference MPI Metrics

Multipath interference (MPI) metrics are Broadcom firmware/cAPI diagnostic values used as a dust-detection signal in single-mode optical links. In the Broadcom AN100 source, they are unitless values derived from PAM-4 slicer-noise behavior and are related to BER/SNR degradation.

## Metric Pair

| Metric | Where it applies | Meaning |
|---|---|---|
| `mpi_metrics` | MPIC output, media lane | MPI after Broadcom MPI cancellation/correction is active. |
| `mpi_metrics_mpicoff` | MPIC input estimate, media lane | Detection metric estimating the MPI condition as if MPIC were disabled. |

`mpi_metrics_mpicoff` is the more direct dust-condition indicator because it estimates the pre-cancellation MPI condition. `mpi_metrics` is expected to be lower when MPIC is doing useful correction.

## MPIC Rule

The Broadcom note says MPIC should remain enabled during live traffic. The `mpi_metrics_mpicoff` metric exists so the host can observe a pre-cancellation-style dust signal without actually disabling MPIC and disturbing the link.

## CMIS Boundary

These metrics are not base CMIS observables by themselves. The Broadcom note leaves two key decisions outside the firmware note:

- What limits are tolerable for a given optical system.
- Which CMIS register or VDM item, if any, should expose the metrics.

That makes MPI metrics a vendor-diagnostic source until a module maps them into a documented CMIS surface.

## Relationship To VDM

If a module exposes these values through [versatile-diagnostics-monitoring](versatile-diagnostics-monitoring.md), the host should rely on the module's VDM descriptor for observable identity, scaling, units, thresholds, and lane grouping. The Broadcom note does not define a standard VDM observable code for either metric.

## Customer Requirement Overlay

The customer-facing requirement history is tracked separately in [mpi-customer-requirements-from-email](../synthesis/mpi-customer-requirements-from-email.md). That synthesis records MSFT's VDM/CDB request, the custom VDM Type ID issue, the need to confirm the production Broadcom API, polling-latency concerns, and validation themes such as BER versus MPI and MPICAN enabled/disabled comparison.

## Practical Interpretation

- Rising `mpi_metrics_mpicoff` suggests increasing dust/MPI stress before cancellation.
- `mpi_metrics` indicates the remaining output-side MPI condition after correction.
- Both values should be trended with SNR, LTP, BER, FEC, and lane identity.
- Absolute MPI in dB requires external module-vendor calibration; Broadcom firmware does not provide those absolute dB values.

For a module-vendor calibration procedure, see [mpi-calibration-module-vendor](mpi-calibration-module-vendor.md).

Source: [broadcom-2025-mpi-metrics-feature](../sources/broadcom-2025-mpi-metrics-feature.md).
