---
type: concept
title: MPI Calibration for Module Vendors
tags: [optical-modules, mpi, calibration, diagnostics, cmis, vdm]
related: [optical-modules, mpi-customer-requirements-from-email]
sources:
  - ../sources/broadcom-2025-mpi-metrics-feature.md
  - multipath-interference-mpi-metrics.md
  - ../queries/how-should-hosts-use-broadcom-mpi-metrics.md
  - ../synthesis/mpi-customer-requirements-from-email.md
created: 2026-06-12
updated: 2026-06-12
status: draft
---

# MPI Calibration for Module Vendors

## Goal

The goal is to turn unitless DSP MPI metrics into a module-vendor-controlled customer value: either calibrated MPI in dB, a dB-like severity value, or a documented severity class. The conversion must be empirical. The existing MPI source notes say `mpi_metrics` and `mpi_metrics_mpicoff` are unitless and do not directly yield absolute MPI dB.

Keep two calibrations, not one:

| Raw metric | Physical meaning to calibrate | Recommended reported value |
|---|---|---|
| `mpi_metrics` | Residual / output-side MPI condition after MPIC correction is active. | `mpi_out_db` or `mpi_residual_db`, plus the raw value. |
| `mpi_metrics_mpicoff` | Pre-correction / input-side MPI estimate as if MPIC were disabled, without turning MPIC off during live traffic. | `mpi_in_db` or `mpi_pre_correction_db`, plus the raw value. |

Do not subtract the two raw metrics and call the result cancellation gain in dB. They are unitless internal statistics with different meanings. If cancellation gain is required, derive it from the two separately calibrated dB values and document the convention.

## dB Convention

Define the dB convention before collecting data. Two conventions are common:

- Signed interference ratio: `MPI_dB_signed = 10 * log10(P_interfering / P_main)`. This is usually negative because the interfering path is weaker.
- Positive impairment magnitude: `MPI_dB_mag = -10 * log10(P_interfering / P_main)`. This is easier for customer limits because a larger positive number means weaker reflected/interfering power.

Pick one convention for all plots, firmware fields, limits, and CMIS/VDM descriptors. If customer language says "MPI dB" without a sign convention, record both the mathematical definition and the displayed scaling.

## Lab Setup

Use a setup that can create known, repeatable MPI levels while preserving normal module operation:

1. DUT module with production-like optics, DSP firmware, module firmware, and host-management access.
2. Host controller for CMIS/I2C/MDIO polling and DSP diagnostic reads.
3. BERT or traffic generator/checker to record BER, FEC statistics, lock state, SNR, and LTP alongside MPI.
4. Temperature control for module case temperature.
5. Optical power control using VOA and calibrated power meter.
6. Controlled MPI injector: a main optical path plus a delayed/reflected path with adjustable attenuation or return loss. Record reflector setting, delay fiber, polarization condition, connector state, and optical power.
7. Reference measurement path where possible: optical return-loss meter, calibrated reflector, reference receiver, or offline measurement that establishes `P_interfering / P_main`.

The calibration fixture should make the physical MPI level the independent variable. The DSP metrics are dependent variables.

## Data Collection Procedure

1. Warm up the module and fixture until optical power, temperature, CDR lock, and BER are stable.
2. Establish a clean baseline with intentional MPI disabled or minimized. Record both raw metrics, SNR, LTP, BER/FEC, optical power, temperature, lane, firmware revision, and MPIC state.
3. Sweep a controlled set of physical MPI levels across the intended operating range.
4. At each MPI level, wait for metric settling, then collect repeated samples per lane. Use median and percentile values, not just one read.
5. Keep MPIC enabled for normal `mpi_metrics` and `mpi_metrics_mpicoff` collection. `mpi_metrics_mpicoff` exists to estimate the pre-correction condition without disabling MPIC during live traffic.
6. In lab-only characterization, optionally collect a separate MPIC-disabled data set if the link remains safe and the procedure is approved. Treat that data as validation evidence, not as the production polling mode.
7. Repeat across lanes, representative modules, optical power corners, temperature corners, firmware revisions, and relevant application modes.

Minimum useful table columns:

| Column | Purpose |
|---|---|
| module_id, lane, firmware_rev | Traceability and population coverage. |
| temp_c, rx_power_dbm, tx_power_dbm | Conditions that may shift the metric. |
| mpi_physical_db, mpi_convention | Ground-truth target and sign convention. |
| mpi_metrics, mpi_metrics_mpicoff | Raw DSP metrics to calibrate. |
| mpic_state | Confirms correction state. |
| snr, ltp, ber, fec_uncorrectable, cdr_lock | Correlation and validity checks. |
| sample_age_ms, poll_period_ms | Freshness and host-visible behavior. |

## Model Fitting

Build two separate calibration data sets:

- Input-side model: `mpi_in_db = f_in(mpi_metrics_mpicoff, lane, temp_c, rx_power_dbm, firmware_rev)`.
- Output-side model: `mpi_out_db = f_out(mpi_metrics, lane, temp_c, rx_power_dbm, firmware_rev)`.

Start with a monotonic lookup table or piecewise-linear fit. Polynomial fits can work, but they are easier to overfit and harder to bound safely in firmware. A practical production model is usually:

1. Reject invalid samples: CDR unlocked, BER unstable, raw metric saturated, optical power out of range, or calibration range exceeded.
2. Apply a lane normalization if needed: global curve plus per-lane offset/gain.
3. Convert raw metric to dB using a monotonic LUT.
4. Clamp or flag out-of-range values instead of extrapolating silently.
5. Report uncertainty or quality flags when the estimate is near a range edge.

Use separate model versions for `mpi_metrics` and `mpi_metrics_mpicoff`. Store the model version in firmware or manufacturing data so field logs can be interpreted later.

## Verification

Verify the model with data that was not used for fitting:

- Hold out modules, lanes, and temperature/power corners.
- Check monotonicity: increasing physical MPI should move the calibrated value in the expected direction.
- Check repeatability and hysteresis by sweeping MPI up and down.
- Check cross-correlation with SNR, BER, and FEC behavior.
- Record residual error such as mean error, maximum error, and 95th percentile error.
- Define the production acceptance target, for example "within X dB over the specified range" once real data is available.

If `mpi_metrics_mpicoff` tracks dust/input stress well but `mpi_metrics` is flattened by effective cancellation, report them as different observables instead of forcing them into one MPI number.

## Production Reporting

Expose enough metadata for a host or customer to interpret the value:

- raw `mpi_metrics`
- raw `mpi_metrics_mpicoff`
- calibrated `mpi_out_db`
- calibrated `mpi_in_db`
- units and dB convention
- lane mapping
- valid/invalid state
- saturation or out-of-range flags
- sample age and update cadence
- MPIC state
- calibration/model version

For CMIS VDM exposure, define separate observables for `mpi_in_db` and `mpi_out_db` if both are reported. Do not expose a single field named "MPI dB" unless the metric source and convention are unambiguous.

## Calibration Deliverables

A module-vendor calibration package should include:

- fixture diagram and calibration equipment list,
- physical MPI dB definition and uncertainty budget,
- data-collection script and raw data schema,
- fitting script and model coefficients/LUT,
- per-lane or per-module correction policy,
- firmware implementation note,
- CMIS/VDM mapping note if the value is host-visible,
- validation report with hold-out data,
- production test limits and retest criteria.

## Common Mistakes

- Treating `mpi_metrics` and `mpi_metrics_mpicoff` as the same quantity.
- Reporting unitless values as dB without empirical calibration.
- Disabling MPIC during live traffic to get a pre-correction metric.
- Using raw metric difference as cancellation gain.
- Building a curve from one lane or one module and applying it globally.
- Ignoring temperature, optical power, firmware version, or metric saturation.
- Publishing customer thresholds before BER/SNR/FEC correlation is measured.

## Source Notes

The Broadcom MPI note summarized in [Broadcom 2025 MPI Metrics Feature](../sources/broadcom-2025-mpi-metrics-feature.md) defines `mpi_metrics` and `mpi_metrics_mpicoff` as unitless diagnostics and leaves thresholds, dB conversion, and CMIS exposure to the module vendor and customer. The internal [MPI Customer Requirements From Email](../synthesis/mpi-customer-requirements-from-email.md) records the need for calibrated MPI reporting, VDM/CDB mapping, polling policy, and validation evidence.
