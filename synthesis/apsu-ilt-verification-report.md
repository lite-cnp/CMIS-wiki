---
type: synthesis
title: APSU/iLT Verification Report
created: 2026-06-09
updated: 2026-06-09
tags: [cmis, apsu, ilt, verification, ieee-802-3dj, page-70h, sian3, cdb]
related: [apsu-ilt-customer-note-plan.md, ../sources/lumentum-2026-8023dj-apsu-ilt-support-plan.md, ../sources/lumentum-2026-dpsm-apsu-ilt-state-machine.md, ../sources/broadcom-2026-sian3-apsu-application-notes.md, ../sources/feng-jiang-2026-sian3-link-training-verification-email-thread.md, ../sources/oif2026-093-08-802-3dj-apsu-draft.md, ../sources/ieee-p802-3dj-d2-3.md, ../queries/how-should-hosts-use-sian3-apsu-capi.md, ../queries/how-do-apsu-and-cmis-state-machines-interact.md]
sources: [apsu-ilt-customer-note-plan.md, ../sources/lumentum-2026-8023dj-apsu-ilt-support-plan.md, ../sources/lumentum-2026-dpsm-apsu-ilt-state-machine.md, ../sources/broadcom-2026-sian3-apsu-application-notes.md, ../sources/feng-jiang-2026-sian3-link-training-verification-email-thread.md, ../sources/oif2026-093-08-802-3dj-apsu-draft.md, ../sources/ieee-p802-3dj-d2-3.md]
---

# APSU/iLT Verification Report

This report summarizes current APSU/iLT verification for the 1.6T 2xDR4 FRO module firmware. It separates customer-safe claims from internal lab evidence, and it calls out what is still missed against the IEEE 802.3dj APSU/iLT model, the OIF CMIS Page 70h draft mapping, and the Broadcom Sian3 APSU application note.

Status labels used below are `Implemented`, `Planned`, `Verified`, `Unverified`, and `Missing`.

## Executive Summary

| Topic | Status | Customer-safe conclusion |
|---|---|---|
| Current customer control surface | Implemented | APSU/iLT control is available through NVIDIA-defined vendor CDB commands, not through standard CMIS Page 70h yet. |
| CMIS Page 70h | Planned | Page 70h should be described as planned; the goal is to use the CMIS standardized interface as soon as possible. |
| Selected LT behavior | Verified | Lab-observed evidence supports polarity recovery, degraded-tap BER improvement, repeatability in loaded runs, and 0/45/70 C temperature-corner behavior. |
| Full APSU path-level conformance | Unverified | Current evidence verifies selected LT and Sian3 status behavior, not complete IEEE 802.3dj APSU path-level conformance. |
| Physical high-loss condition | Unverified | The setup image shows a GoLight VOA and logs show degraded BER, but the actual attenuation or insertion loss is not captured. |
| Convergence time | Unverified | Available logs do not independently measure convergence time; the reported sampling times occur after DUT LT enable. |
| Temperature-shift behavior | Verified | Lab-observed email evidence says FIR did not automatically change after a 10 C to 60 C shift until LT was disabled and re-enabled; this is not a general product guarantee. |

The safest current customer message is: vendor CDB support is implemented for APSU/iLT enablement and precoding control/readback; selected Sian3 LT behaviors have been lab-observed; CMIS Page 70h is planned; full APSU conformance, quantified high-loss coverage, convergence time, and standard Page 70h validation remain open.

## Current Firmware Implementation Snapshot

Current firmware support is vendor CDB based:

| Area | Status | Current position |
|---|---|---|
| Capability reporting | Implemented | `0xA200` reports host-side iLT, media-side iLT, and media-side APSU capability. |
| Per-lane LT/APSU control | Implemented | `0xA201` sets/gets per-lane host LT, media LT, and APSU enable/disable masks. |
| Precoding override | Implemented | `0xA082` controls host TX/RX and media TX/RX precoding. |
| Precoding state readback | Implemented | `0xA083` reports precoding capability and current precoding state. |
| Default behavior | Implemented | APSU/iLT is disabled by default; the host enables it per lane. |
| CMIS state-machine model | Implemented | MSM remains unchanged and DPSM remains the CMIS configuration state machine; live Ethernet DATA readiness must not be inferred from `DPActivated` alone. |
| CMIS Page 70h | Planned | Formal CMIS Page 70h APSU/iLT control and status mapping is future work. |

The current vendor CDB surface is enough for host-driven enable/disable and active-mask readback, plus precoding control/readback. It does not expose the full standardized APSU/LT status model that Page 70h is expected to provide.

## Interface And Evidence Access Paths

| Access path | Status | What it proves | What it does not prove |
|---|---|---|---|
| Customer vendor CDB | Implemented | Current customer-accessible control path for `0xA200`, `0xA201`, `0xA082`, and `0xA083`. | Does not prove standard CMIS Page 70h support or full detailed APSU status exposure. |
| Lab-only P253.66 debug CDB | Implemented | Internal lab bridge from Python tooling to Sian3 cAPI for LT info, LT status, and precode fields. | Does not prove customer access or Page 70h compliance. |
| Underlying Sian3 cAPI | Implemented | Broadcom behavior model exercised by firmware and lab debug paths. | Does not by itself define a CMIS customer interface. |
| Email/lab observation | Verified | Observed LT behavior, BER/tap changes, status fields, and selected temperature/polarity behavior. | Does not create a general product guarantee without a controlled validation report. |
| Planned CMIS Page 70h | Planned | Target standardized customer-facing APSU/iLT control/status interface. | Does not exist in the current firmware evidence. |

Several verifications used an internal debug CDB interface to call Sian3 cAPI directly. Treat those results as lab-only evidence for underlying firmware and Sian3 behavior. They are not evidence that the same detailed fields are customer-facing through CMIS Page 70h.

## Current Firmware Vs Customer-Note Plan

| Baseline item | Status | Evidence/access path | Gap type | Recommended action |
|---|---|---|---|---|
| Vendor CDB capability report through `0xA200` | Implemented | Customer vendor CDB | None | Keep as the current customer control-plane claim. |
| Per-lane host LT, media LT, and APSU masks through `0xA201` | Implemented | Customer vendor CDB | None | Use active masks for current customer-visible enable/readback. |
| Precoding override through `0xA082` and readback through `0xA083` | Implemented | Customer vendor CDB | None | Keep separate from APSU/LT readiness claims. |
| APSU/iLT disabled by default and host-enabled per lane | Implemented | Customer-note plan, customer vendor CDB | None | State as the default behavior. |
| MSM unchanged and DPSM preserved | Implemented | State-machine source | Verification gap | Describe as design alignment; do not imply lab verification of all state-machine transitions. |
| `DPActivated` is not enough for live Ethernet DATA readiness | Implemented | State-machine source, Sian3 status model | None | Continue to require APSU/LT readiness such as `PATH_UP`, RTS, or iLT complete. |
| Formal CMIS Page 70h control/status | Planned | Planned CMIS Page 70h | Implementation gap | State that Page 70h is planned and should become the standardized customer interface as soon as possible. |
| Detailed standardized APSU/LT readiness status for customers | Missing | Planned CMIS Page 70h | Implementation gap | Do not represent lab-only Sian3 cAPI status as current customer Page 70h support. |

## Current Firmware Vs IEEE/OIF APSU Baseline

| Baseline item | Status | Evidence/access path | Gap type | Recommended action |
|---|---|---|---|---|
| APSU provides coordinated orderly initialization of ISLs in a path | Unverified | IEEE/OIF source, lab observations | Verification gap | Build a path-level APSU validation report before claiming conformance. |
| ILT establishes peer communication, optimizes signaling, and coordinates transition toward DATA | Unverified | Email/lab observation, underlying Sian3 cAPI | Verification gap | Use selected lab-observed LT behavior as supporting evidence, but do not claim full IEEE ILT conformance. |
| RTS/readiness must gate live DATA separately from CMIS `DPActivated` | Implemented | State-machine source, Sian3 AN status model | None | Keep this rule in customer wording. |
| CMIS Page 70h exposes standardized APSU/iLT control, status, and troubleshooting | Planned | OIF Page 70h draft, customer-note plan | Implementation gap | Implement and validate Page 70h; do not claim it now. |
| APSU and non-APSU behavior coexist without changing MSM | Implemented | OIF draft, state-machine source | Verification gap | Treat as design alignment until covered by explicit regression evidence. |
| Multiple APSU/iLT instances across host/media lanes | Implemented | Customer vendor CDB masks | Verification gap | Add broader matrix coverage for host/media and per-lane combinations. |
| Full IEEE 802.3dj APSU interoperability | Unverified | Current vault evidence | Verification gap | Test with non-Sian3 partners and standard host assumptions. |

## Current Firmware Vs Sian3 APSU Application Note

| Sian3 AN expectation | Status | Evidence/access path | Gap type | Recommended action |
|---|---|---|---|---|
| APSU/LT controls map to Sian3 lane configuration fields | Implemented | Customer vendor CDB, lab-only P253.66 debug CDB, underlying Sian3 cAPI | None | Keep cAPI details in implementation evidence, not as the customer interface. |
| `training_status = 3`, `apsu_control_state = 7`, and local/remote ready asserted for path up | Verified | Loaded Feng logs, lab-only P253.66 debug CDB | None | Use as lab-observed status evidence. |
| Rx polarity correction when LT is enabled | Verified | Email/lab observation, screencopies | Verification gap | Phrase as lab-observed; a single ordered, timestamped polarity raw log is still missing. |
| Tx equalization/tap optimization improves degraded BER | Verified | Loaded logs, screencopies | None | Use numeric BER ranges and tap stability as lab evidence. |
| Temperature-corner operation at about 0 C, 45 C, and 70 C | Verified | Loaded temperature logs | None | Keep this as lab-observed behavior. |
| Temperature shift from 10 C to 60 C without automatic FIR re-optimization | Verified | Email/lab observation | Verification gap | Use customer-safe wording and avoid implying continuous adaptation. |
| Training pattern, mode sequencing, and detailed TP/MC/TF-lock behavior | Unverified | Sian3 AN | Verification gap | Add explicit captures if the customer note needs this level of conformance. |
| Bundled lane restart, recovery reason, and recovery counter behavior | Unverified | Sian3 AN | Verification gap | Add recovery/restart tests before claiming this behavior. |
| Valid APSU/LT configuration matrix from the AN | Unverified | Sian3 AN, current CDB masks | Verification gap | Validate selected combinations against host/media enable masks. |

## Evidence And Test Coverage

| Evidence item | Status | Evidence/access path | What is covered | Remaining gap |
|---|---|---|---|---|
| Test setup image | Verified | Email/lab observation | Temperature chamber, Sian3 DUT BERT board, Sian3 REF BERT board, DUT/REF GungnirS modules, `TP0 -> TP1`, `TP4 -> TP5`, and GoLight VOA. | Actual VOA attenuation and insertion loss are missing. |
| May 22 degraded-tap run | Verified | Loaded logs | Worse-tap BER from `1.34e-10` to `6.38e-7`; after DUT LT, LT-on BER from `0` to `2.49e-12`; status path up and ready bits asserted. | Does not quantify physical channel loss. |
| BERT-only LT before DUT LT | Verified | Loaded logs | BER parsed as `1.0` before DUT LT, supporting the need for both sides to be enabled. | Not a standalone conformance test. |
| May 25 repeatability loaded runs | Verified | Loaded logs | Two runs show worse-tap BER up to `6.20e-7` and `6.13e-7`; LT-on BER down to `0` to `2.87e-12` and `0` to `1.60e-12`; repeated tap readback stable. | Email describes three runs; only two raw repeatability logs are loaded. |
| Third repeatability raw log | Missing | Email/lab observation | Email says three runs existed. | Import only if the customer claim needs three-run raw support. |
| Temperature corners | Verified | Loaded logs | About 0 C, 45 C, and 70 C runs show `training_status = 3`, `apsu_control_state = 7`, ready bits asserted, and LT-on BER up to `1.12e-10`, `2.33e-12`, and `2.66e-12`. | Still not convergence-time evidence. |
| Temperature-shift behavior | Verified | Email/lab observation | Email reports 10 C worse-tap BER about `10e-8`, LT BER about `10e-11`, 60 C after half hour BER about `10e-12`, failed FIR change while LT enabled, then new FIR after LT restart. | Matching raw log/screenshot is missing; phrase as lab-observed only. |
| Polarity recovery | Verified | Email/lab observation, screencopies | Polarity forcing broke traffic with FEC BER `1.0`; enabling LT on BERT and DUT recovered traffic; polarity masks changed. | Single ordered, timestamped polarity raw log is missing. |
| Common degraded tap settings | Verified | Loaded logs, screencopies | Lanes 0-3 used `[0, 0, -7, 50, 0, 0, 0, 0, 0, 0, 0, 0, 0]`; lanes 4-7 used `[-10, 10, 50, 78, 0, 0, 0, 0, 0, 0, 0, 0, 0]`. | Logs emit two tap records per lane without endpoint labels. |
| Convergence time | Unverified | Loaded logs, email/lab observation | Current evidence says taps changed too quickly for the DSP API method to capture. | Add an independent timing method or state unmeasured. |
| Customer vendor CDB transaction trace | Missing | Customer vendor CDB | Current source plan documents the commands. | Capture transaction logs if needed for customer evidence. |
| Page 70h validation | Missing | Planned CMIS Page 70h | Draft ranges are known. | Validate after implementation. |
| Non-Sian3 interoperability | Missing | Current vault evidence | None in loaded evidence. | Add interoperability coverage before claiming broad APSU compatibility. |

## Implementation Gaps

- `Planned`: Formal CMIS Page 70h APSU/iLT control and status mapping is not implemented yet.
- `Missing`: Standard CMIS-accessible Page 70h readiness/status is not currently available to customers.
- `Implemented`: Current customer support is vendor CDB based, so it should be described as current interim support rather than standardized CMIS memory-map support.
- `Missing`: Detailed Sian3 cAPI fields such as `apsu_control_state`, RTS bits, Rx-ready bits, recovery counters, and polarity correction are visible through lab/internal paths, but not through customer-facing standard CMIS Page 70h.
- `Unverified`: The local code tree indicates APSU programming is included when `BRCM_SPECIFIC = 0`, but the exact customer firmware build should confirm this macro state.

## Verification Evidence Gaps

- `Unverified`: Quantified physical high-loss coverage is not proven. The logs show degraded BER up to `4.99e-6` under forced worse taps and the setup image shows a VOA, but no attenuation or insertion-loss value is captured.
- `Unverified`: Convergence time is not measured by the current evidence.
- `Missing`: The third May 25 repeatability raw log is not loaded, although the email describes three runs.
- `Missing`: The May 26 temperature-shift raw log or screenshot is not loaded; the current evidence is email-body lab observation.
- `Missing`: A single ordered, timestamped polarity raw log is not loaded; screencopies and email support the behavior but not a formal raw sequence.
- `Unverified`: The loaded logs do not identify which of the two tap records per lane belongs to DUT versus REF/BERT endpoint.
- `Missing`: Page 70h validation is not available because Page 70h is planned, not current.
- `Missing`: Interoperability evidence with non-Sian3 partners is not loaded.
- `Unverified`: Full IEEE 802.3dj APSU path-level conformance remains open.

## Recommended Validation Actions

| Priority | Action | Reason |
|---|---|---|
| P0 | State clearly that Page 70h is planned and that standardized CMIS access should be used as soon as possible. | Prevents the customer note from implying current Page 70h support. |
| P0 | Confirm the exact customer firmware build and `BRCM_SPECIFIC` macro state. | Local code evidence should match the delivered build before being used as implementation evidence. |
| P0 | Prove or remove the high-loss claim. | Current evidence shows degraded BER, not quantified physical high loss. |
| P0 | Measure convergence time with an independent method or state it as unmeasured. | Current logs only show post-enable sampling timestamps. |
| P0 | Qualify temperature-shift behavior as lab-observed and not a general product guarantee. | The observation is useful, but raw supporting artifacts are not loaded. |
| P1 | Import the missing third repeatability raw log, May 26 temperature-shift raw artifact, or ordered polarity raw log only if those claims are needed. | Avoids over-collecting raw data while closing specific evidence gaps. |
| P1 | Capture customer vendor CDB transactions for `0xA200`, `0xA201`, `0xA082`, and `0xA083`. | Supports the customer-accessible part of the implementation with direct traces. |
| P1 | Validate Page 70h once implemented. | Moves detailed customer-facing status to the standard interface. |
| P1 | Add host/media lane combination and non-Sian3 interoperability coverage. | Reduces risk around APSU/iLT configuration breadth and partner assumptions. |
| P2 | Label DUT versus REF/BERT tap records in future logs. | Makes tap optimization evidence easier to audit. |
| P2 | Maintain a compact evidence map from customer claims to log/screenshot/source artifacts. | Keeps the customer note defensible as the source set grows. |

## Source Traceability

Primary vault sources:

- [apsu-ilt-customer-note-plan](apsu-ilt-customer-note-plan.md)
- [lumentum-2026-8023dj-apsu-ilt-support-plan](../sources/lumentum-2026-8023dj-apsu-ilt-support-plan.md)
- [lumentum-2026-dpsm-apsu-ilt-state-machine](../sources/lumentum-2026-dpsm-apsu-ilt-state-machine.md)
- [broadcom-2026-sian3-apsu-application-notes](../sources/broadcom-2026-sian3-apsu-application-notes.md)
- [feng-jiang-2026-sian3-link-training-verification-email-thread](../sources/feng-jiang-2026-sian3-link-training-verification-email-thread.md)
- [oif2026-093-08-802-3dj-apsu-draft](../sources/oif2026-093-08-802-3dj-apsu-draft.md)
- [ieee-p802-3dj-d2-3](../sources/ieee-p802-3dj-d2-3.md)
- [how-should-hosts-use-sian3-apsu-capi](../queries/how-should-hosts-use-sian3-apsu-capi.md)
- [how-do-apsu-and-cmis-state-machines-interact](../queries/how-do-apsu-and-cmis-state-machines-interact.md)

Code-derived evidence, kept as implementation traceability rather than main customer conclusions:

- `1p6_sian3_h5_python/yapp/sian3.py :: Debug`
- `1p6_sian3_h5_python/yapp/sian3.py :: Debug.set_lktrn_info`
- `1p6_sian3_h5_python/yapp/sian3.py :: Debug.get_lktrn_stat`
- `1p6_sian3_h5_python/yapp/sian3.py :: Debug.set_apsu_enable`
- `1p6_sian3_h5_python/yapp/sian3.py :: Debug.get_apsu_enable`
- `1p6_sian3_h5_python/yapp/sian3.py :: Debug.set_precode`
- `1p6_sian3_h5_python/yapp/sian3.py :: Debug.get_precode`
- `1p6_sian3_h5_python/bert_sian3_lib/sian3.py :: Debug`
- `1p6_sian3_fw_h5/v0_1/fw/src/liteIntRegs.h :: debug_access_t`
- `1p6_sian3_fw_h5/v0_1/fw/src/liteIntRegs.h :: dsp_debug_cmd_lktrn_info_t`
- `1p6_sian3_fw_h5/v0_1/fw/src/liteIntRegs.h :: dsp_debug_cmd_lktrn_status_t`
- `1p6_sian3_fw_h5/v0_1/fw/src/liteIntRegs.h :: dsp_debug_cmd_precode_t`
- `1p6_sian3_fw_h5/v0_1/fw/src/qsfpMsaRegs.c :: DSP_DEBUG_CMD_LKTRN_INFO`
- `1p6_sian3_fw_h5/v0_1/fw/src/qsfpMsaRegs.c :: DSP_DEBUG_CMD_LKTRN_STAT`
- `1p6_sian3_fw_h5/v0_1/fw/src/qsfpMsaRegs.c :: DSP_DEBUG_CMD_PRECODE`
- `1p6_sian3_fw_h5/v0_1/fw/src/qsfpCdb.c :: QSfpVdrA200`
- `1p6_sian3_fw_h5/v0_1/fw/src/qsfpCdb.c :: QSfpVdrA201`
- `1p6_sian3_fw_h5/v0_1/fw/src/qsfpCdbLt.h :: ACT_LT_ENABLE`
- `1p6_sian3_fw_h5/v0_1/fw/src/dsp/dsp_sian.c :: ProcessDspLktrn`
- `1p6_sian3_fw_h5/v0_1/fw/src/main.h :: BRCM_SPECIFIC`
