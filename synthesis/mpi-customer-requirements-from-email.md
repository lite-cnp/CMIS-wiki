---
type: synthesis
title: MPI Customer Requirements From Email
created: 2026-06-12
updated: 2026-06-12
tags: [cmis, mpi, vdm, cdb, msft, zfr8, gungnir-s, vm8, broadcom, marvell, customer-requirements]
related:
  - ../concepts/multipath-interference-mpi-metrics.md
  - ../concepts/versatile-diagnostics-monitoring.md
  - ../concepts/command-data-block.md
  - ../queries/how-should-hosts-use-broadcom-mpi-metrics.md
  - ../sources/broadcom-2025-mpi-metrics-feature.md
sources:
  - ../sources/broadcom-2025-mpi-metrics-feature.md
  - "Outlook: RE: New function VDM and CDB need for 1.6T 2xDR4, Xianqing Shao, 2026-06-03"
  - "Outlook: RE: [External]:Re: 1.6T DR8 issue sync up with Lumentum, Xianqing Shao, 2026-06-12"
  - "Outlook: [External]:RE: 2xDR4 SpicaGen2 MPI @ MSFT, Rittik Shah, 2025-11-20"
  - "Outlook: RE: [External]:Latest ZFR8 spec, Sameer Chandani, 2026-03-09"
  - "Outlook: RE: [External]:Re: SIAN3 SNR LTP report, Xianqing Shao, 2025-12-05"
  - "Outlook: RE: Gunginr-S Techanical Meeting, Tao Chen, 2026-06-11"
  - "Outlook: Add new FW version testing results//RE: add VM8 testing results//RE: NYZ01G9L0098 Burst Error in TC, Fei Wang, 2026-03-26"
status: draft
---

# MPI Customer Requirements From Email

## Summary

MPI is now a customer-facing diagnostic requirement, not only a Broadcom cAPI diagnostic. The strongest requirement signal is from MSFT: CMIS [VDM](../concepts/versatile-diagnostics-monitoring.md) is expected to cover MPI, eSNR, and LTP, with MPI sourced from Broadcom `mpi_metric`; [CDB](../concepts/command-data-block.md) is also expected to expose RMON functions. A separate Broadcom thread says MPI is not a base CMIS requirement and MPI-inclusive SNR/LTP polling can be time-consuming, so the product requirement needs an explicit interface, cadence, conversion, and acceptance-policy decision.

This page should be read as a customer-requirements overlay on top of [multipath-interference-mpi-metrics](../concepts/multipath-interference-mpi-metrics.md) and [how-should-hosts-use-broadcom-mpi-metrics](../queries/how-should-hosts-use-broadcom-mpi-metrics.md).

## Requirement Backlog

| ID | Customer / scope | Requirement | Current evidence | Decision needed |
|---|---|---|---|---|
| MPI-REQ-1 | MSFT 1.6T 2xDR4 | CMIS VDM should cover MPI, eSNR, and LTP. MPI should come from Broadcom `mpi_metric`. | Tao Chen wrote on 2026-06-03 that MSFT has a new CMIS VDM/CDB requirement covering MPI, eSNR, LTP, and RMON. | Choose the VDM mapping, including a custom MPI VDM type ID. |
| MPI-REQ-2 | MSFT 1.6T 2xDR4 | CDB should add RMON functions. | The same 2026-06-03 thread links the CDB request with the VDM MPI/eSNR/LTP request. | Define which RMON counters/functions are required and who owns them. |
| MPI-REQ-3 | MSFT / Broadcom SIAN3 | Confirm the exact Broadcom API for MPI-related data. | Xianqing noted that CMIS has no defined VDM type ID for MPI and that BRCM API mapping still needs confirmation. | Confirm whether `capi_get_lane_info`, `FAST_CMIS_SNR`, or another API is the production source. |
| MPI-REQ-4 | MSFT / reporting | Convert unitless MPI metrics into something customer-meaningful. | Broadcom AN100 says `mpi_metric` and `mpi_metric_mpicoff` are unitless statistical severity indicators; Xianqing concluded MPI dB cannot be calculated directly and proposed LUT or polynomial fitting. | Build a calibration data set: measured MPI_DB versus `mpi_metric` and `mpi_metric_mpicoff`. |
| MPI-REQ-5 | MSFT / polling | Decide whether the customer expects polling MPI and at what cadence. | Broadcom FAE said MPI dump is time-consuming and not a CMIS requirement; Xianqing answered that the customer requires MPI. SNR/LTP/MPI polling was reported around 700 ms. | Define polling mode, latency budget, cache strategy, and freshness semantics. |
| MPI-REQ-6 | MSFT 2xDR4 / Marvell SpicaGen2 | Confirm MPICAN enablement and explain why it is enabled. | Rittik Shah asked whether SpicaGen2 LRX MPICAN is enabled for MSFT 2xDR4 and requested the rationale. Tao answered it has been enabled since Oct 2025. | Keep a customer-ready rationale for MPICAN enablement. |
| MPI-REQ-7 | MSFT 2xDR4 / Marvell SpicaGen2 | Compare BER curve data with and without MPICAN. | Marvell requested BER curve data with and without MPICAN. Tao shared data and said the best observed condition was TIA_AGC_BW=0.2 MHz plus MPICAN enabled; Marvell later judged TIA AGC BW dominant and MPICAN minor. | Preserve the comparison data and make the test condition explicit. |
| MPI-REQ-8 | Google/ZFR8 spec | Determine whether DSP mode definition changes affect test settings for Engine, Traffic, and MPI. | Sameer asked whether ZFR8 DSP mode definition changes require module settings during test and whether Mode B is the default power-up mode. | Clarify FW default versus test-software write sequence. |
| MPI-REQ-9 | VM8 / validation | Validate TC behavior with MPI and track FW improvements. | VM8 TC with MPI found errors mainly at TX output in B2B testing; FW v1.8.18 and v1.8.20 showed improved TC-with-MPI performance versus v1.8.9. | Tie MPI validation to FW release acceptance and customer qualification data. |
| MPI-REQ-10 | Gungnir-S / MSFT SDVT and NPI | Provide MPI setup and data to MSFT as part of product integration. | Gungnir-S technical meeting notes list product integration actions: share eSNR/LTP samples for customer spec discussion and discuss MPI testing setup/provide data to MSFT. | Define a repeatable MSFT MPI setup, data package, and owner. |

## Technical Interpretation

Broadcom's naming matters:

- `mpi_metric` is measured after the MPI canceller, so it reflects residual MPI after MPIC.
- `mpi_metric_mpicoff` estimates the metric before the MPI canceller, equivalent to MPI cancellation disabled.
- Both are unitless statistical severity indicators from PAM4 slicer-noise analysis.
- They do not directly yield MPI_DB. A calibration LUT or polynomial fit is needed if FW must report a dB-like customer value.

The product should therefore avoid presenting raw `mpi_metric` as a standard physical unit unless the customer agrees. A safer requirement statement is: "Report a customer-defined MPI severity metric via VDM; if MPI dB is required, report a calibrated value and document the calibration method."

## Interface Notes

The email discussion says CMIS does not define a VDM Type ID for MPI. That means the MSFT-facing implementation likely needs a custom VDM assignment, plus agreement on:

- VDM page/type/field allocation for MPI.
- Whether the value is raw `mpi_metric`, raw `mpi_metric_mpicoff`, calibrated MPI_DB, or multiple fields.
- Lane granularity and update cadence.
- Units, scaling, invalid/unavailable encoding, and saturation behavior.
- Whether CDB/RMON exposes the same MPI data, related counters, or only supporting statistics.

SNR/LTP/MPI appears to be tied to `FAST_CMIS_SNR` in current debug flow. The email thread contrasts all-lane LOL/LOS access at about 40 ms with SNR/LTP/MPI polling around 700 ms, so performance must be treated as a requirement.

## Validation Themes

Validation needs to connect MPI visibility to customer outcomes:

- BER versus MPI curve: MSFT asked for a way to set/change MPI and read BER/MPI to plot BER versus MPI.
- MPICAN comparison: Marvell/MSFT asked for BER curves with MPICAN enabled and disabled.
- TC with MPI: VM8 testing showed MPI-related TC failures concentrated around TX output, then improved in later FW versions.
- ZFR8 test setup: DSP mode defaults may affect Engine, Traffic, and MPI test settings.
- Gungnir-S integration: customer-facing data packages should include MPI setup/data alongside eSNR/LTP.

## Open Questions

1. What exact customer-visible MPI quantity is required: raw `mpi_metric`, `mpi_metric_mpicoff`, calibrated MPI_DB, or all of them?
2. What custom CMIS VDM Type ID should be assigned to MPI, and who approves it with MSFT?
3. Which BRCM API is stable enough for production polling?
4. What is the acceptable MPI polling latency and freshness?
5. What are the acceptance thresholds for BER versus MPI and TC-with-MPI validation?
6. Should MPICAN state be reported as a separate status/config field?
7. How should MPI reporting handle lanes where LTP/SNR/MPI data is invalid, saturated, or too slow to refresh?

## Source Notes

- 2026-06-03, Xianqing Shao, "RE: New function VDM and CDB need for 1.6T 2xDR4": MSFT asks for CMIS VDM coverage of MPI/eSNR/LTP, CDB RMON functions, and MPI from `mpi_metric`; Xianqing flags missing CMIS VDM type ID and BRCM API confirmation.
- 2026-06-12, Xianqing Shao, "RE: [External]:Re: 1.6T DR8 issue sync up with Lumentum": Broadcom AN100 explains `mpi_metric` and `mpi_metric_mpicoff`; customer requires MPI; SNR/LTP/MPI polling takes about 700 ms.
- 2025-11-20, Rittik Shah, "[External]:RE: 2xDR4 SpicaGen2 MPI @ MSFT": Marvell/MSFT asks for MPICAN enablement rationale and BER data with/without MPICAN; later review says TIA AGC BW dominates and MPICAN has minor effect.
- 2026-03-09, Sameer Chandani, "RE: [External]:Latest ZFR8 spec": latest ZFR8 DSP mode definition raises test-setting questions for Engine, Traffic, and MPI.
- 2025-12-05, Xianqing Shao, "RE: [External]:Re: SIAN3 SNR LTP report": SNR/LTP/VDM implementation has ambiguity between CMIS SNR and BRCM SNR definitions.
- 2026-06-11, Tao Chen, "RE: Gunginr-S Techanical Meeting": product integration notes call out MPI testing setup and data for MSFT.
- 2026-03-26, Fei Wang, "Add new FW version testing results//RE: add VM8 testing results//RE: NYZ01G9L0098 Burst Error in TC": TC-with-MPI results show FW improvement and TX-output-focused failure analysis.
