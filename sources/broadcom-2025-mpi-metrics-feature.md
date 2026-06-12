---
type: source
title: Broadcom 2025 MPI Metrics Feature
created: 2026-06-12
updated: 2026-06-12
tags: [cmis, broadcom, mpi, dust-detection, diagnostics, vendor-specific, source]
related: [../concepts/multipath-interference-mpi-metrics.md, ../concepts/vendor-specific-cmis-customizations.md, ../concepts/versatile-diagnostics-monitoring.md, ../queries/how-should-hosts-use-broadcom-mpi-metrics.md, ../sources/broadcom-2026-sian3-apsu-application-notes.md]
authors: [Broadcom]
year: 2025
venue: Application Note
source_filename: raw/sources/87XXX-85XXX-83XXX-AN100.pdf
document_id: 87XXX-85XXX-83XXX-AN100
status: draft
---

# Broadcom 2025 MPI Metrics Feature

This Broadcom application note is titled `BCM87XXX/BCM85XXX/BCM83XXX Application Note: MPI Metrics Feature`. It describes a firmware/cAPI method for dust detection using multipath interference (MPI) metrics in single-mode optical applications.

The raw PDF is password-protected. It was opened locally with the user-provided password for extraction; the password is not stored in the wiki.

## Classification

- Vendor-specific Broadcom application note.
- Diagnostic/dust-detection source, not a base CMIS or OIF supplement source.
- Applicable to listed Broadcom `BCM87XXX`, `BCM85XXX`, and `BCM83XXX` module DSP products.
- Example packages in the note include `BCM85812_Official_ModuleRel_vD0.9_D005` or newer and `BCM85814_ENGR_ModuleRel_vE0.3.3_E003_B000` or newer.
- Related to the existing Sian3/APSU wiki only as a Broadcom module-DSP diagnostic source. It does not define APSU/iLT behavior.

## Core Content

The note defines two unitless MPI metrics exposed by Broadcom firmware and cAPI:

| Metric | Meaning | Interpretation |
|---|---|---|
| `mpi_metrics` | MPI metric at the MPIC output on the media lane, with Broadcom MPIC/correction enabled. | Lower value corresponds to lower MPI after cancellation, generally aligning with better BER/SNR. |
| `mpi_metrics_mpicoff` | Detection metric that estimates the MPI condition as if MPIC were disabled, without actually turning MPIC off during live traffic. | Higher value indicates a stronger optical dust/MPI condition before cancellation. |

The note emphasizes that MPIC should remain enabled while live traffic is running. The `mpi_metrics_mpicoff` value is computed by estimating how hard the canceler is working rather than by disabling the canceler in the live link.

## CMIS Boundary

The application note says the two exposed MPI metrics are unitless. It also says absolute MPI values in dB at MPIC output or input are not provided by Broadcom firmware. Those absolute values would require module-vendor measurement and calibration.

The note explicitly leaves threshold setting and CMIS exposure policy to the module vendor and end customer. It does not define which CMIS registers or which CMIS VDM observables should carry `mpi_metrics` or `mpi_metrics_mpicoff`.

## Host Procedure

The note gives a short procedure:

1. Power up the module and verify I2C or MDIO communication.
2. Bring up the CLI interface and confirm DSP communication.
3. Verify that the media Rx CDR is locked.
4. Configure and enable MPI collection.
5. Set `mpi_include = 1` in the fast CMIS SNR interface API.
6. Poll SNR/LTP output and read per-lane `mpi_metrics` and `mpi_metrics_mpicoff`.

The sample log selects media core, all media lanes, requests SNR polling, enables the MPI output option, and then reports per-lane `brcm_snr`, `cmis_snr`, `cmis_ltp`, `mpi_metrics`, and `mpi_metrics_mpicoff`.

## Host Implications

- Treat these metrics as Broadcom vendor diagnostics unless and until the module maps them into a customer-facing CMIS register or VDM observable.
- Do not disable MPIC to obtain an input-side MPI estimate during live traffic; use `mpi_metrics_mpicoff`.
- Establish system-specific thresholds through module vendor and customer calibration.
- Correlate MPI metrics with BER/SNR degradation rather than treating the unitless values as absolute dB MPI.
- If these values are exposed through CMIS VDM, keep the VDM observable definition, units, scaling, and alarm thresholds explicit.

## Extraction Notes

- Text was extracted from `87XXX-85XXX-83XXX-AN100.pdf` with `pdfplumber` using the supplied password.
- The PDF has an 8-page structure: cover/legal, overview, MPI metric explanation, host/API procedure, sample output, and revision history.
- The document contains a diagonal Broadcom confidentiality watermark that introduces stray single-letter artifacts in raw text extraction; those artifacts were ignored in this summary.

Source anchors: PDF pages 1-7, metadata title and subject, section 1 Overview, section 2 MPI Metrics, and the sample fast CMIS SNR interface log.
