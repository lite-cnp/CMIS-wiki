---
type: synthesis
title: APSU/iLT Verification Report
created: 2026-06-09
updated: 2026-06-10
tags: [cmis, apsu, ilt, verification, ieee-802-3dj, page-70h, sian3, cdb]
related: [apsu-ilt-customer-note-plan.md, ../sources/lumentum-2026-8023dj-apsu-ilt-support-plan.md, ../sources/lumentum-2026-dpsm-apsu-ilt-state-machine.md, ../sources/broadcom-2026-sian3-apsu-application-notes.md, ../sources/feng-jiang-2026-sian3-link-training-verification-email-thread.md, ../sources/oif2026-093-08-802-3dj-apsu-draft.md, ../sources/ieee-p802-3dj-d2-3.md, ../queries/how-should-hosts-use-sian3-apsu-capi.md, ../queries/how-do-apsu-and-cmis-state-machines-interact.md, ../queries/ieee-apsu-ilt-fields-missing-from-sian3-capi.md]
sources: [apsu-ilt-customer-note-plan.md, ../sources/lumentum-2026-8023dj-apsu-ilt-support-plan.md, ../sources/lumentum-2026-dpsm-apsu-ilt-state-machine.md, ../sources/broadcom-2026-sian3-apsu-application-notes.md, ../sources/feng-jiang-2026-sian3-link-training-verification-email-thread.md, ../sources/oif2026-093-08-802-3dj-apsu-draft.md, ../sources/ieee-p802-3dj-d2-3.md]
status: draft
---

# APSU/iLT Verification Report

This report summarizes current APSU/iLT verification for the 1.6T 2xDR4 FRO module firmware.

It separates customer-safe claims from internal lab evidence. It also identifies gaps against IEEE 802.3dj APSU/iLT, OIF CMIS Page 70h, and the Broadcom Sian3 APSU application note.

Status labels are `Implemented`, `Planned`, `Verified`, `Unverified`, and `Missing`.

## Executive Summary

| Topic | Status | Customer-safe conclusion |
|---|---|---|
| Current customer control surface | Implemented | APSU/iLT control is available through NVIDIA-defined vendor CDB commands. It is not exposed through standard CMIS Page 70h yet. |
| CMIS Page 70h | Planned | Page 70h should be described as planned. It is the intended standardized interface for future releases. |
| Selected Sian3 LT behavior | Verified | Lab evidence supports polarity recovery, degraded-tap BER improvement, repeatability, and 0 C, 45 C, and 70 C temperature-corner behavior. |
| Full APSU path conformance | Unverified | Current evidence verifies selected LT and Sian3 status behavior. It does not prove complete IEEE 802.3dj APSU path-level conformance. |
| Physical high-loss condition | Unverified | The setup image shows a GoLight VOA and logs show degraded BER. The actual attenuation or insertion loss is not captured. |
| Convergence time | Unverified | Available logs do not independently measure convergence time. Sampling timestamps occur after DUT LT enable. |
| Temperature-shift behavior | Verified | Email evidence says FIR did not automatically change after a 10 C to 60 C shift until LT was disabled and re-enabled. This is not a product guarantee. |

The safest customer message is narrow.

Vendor CDB support is implemented for APSU/iLT enablement and precoding control/readback. Selected Sian3 LT behaviors have been observed in the lab. CMIS Page 70h is planned.

Full APSU conformance, quantified high-loss coverage, convergence time, and standard Page 70h validation remain open.

## Current Customer Interface

Current firmware support is vendor CDB based. The customer-visible surface is enough for enable/disable, active-mask readback, and precoding control/readback.

It does not expose the full standardized APSU/LT status model that Page 70h is expected to provide.

| Access path | Status | Current use | Boundary |
|---|---|---|---|
| Customer vendor CDB | Implemented | `0xA200` reports host LT, media LT, and media APSU capability. `0xA201` sets/gets host LT, media LT, and APSU enable masks. | Does not prove Page 70h support or detailed APSU status exposure. |
| Customer precoding CDB | Implemented | `0xA082` controls host TX/RX and media TX/RX precoding. `0xA083` reports capability and current state. | Keep this separate from APSU/LT readiness claims. |
| Lab-only P253.66 debug CDB | Implemented | Internal Python tooling reaches Sian3 cAPI for LT info, LT status, APSU enable, and precode fields. | This is lab evidence. It is not a customer interface. |
| Underlying Sian3 cAPI | Implemented | Firmware and lab paths exercise Broadcom lane LT/APSU configuration and status. | It is implementation evidence, not a CMIS management interface. |
| CMIS Page 70h | Planned | Intended standard customer interface for APSU/iLT control, status, and troubleshooting. | It is not available in current firmware evidence. |
| CMIS state machines | Implemented | MSM remains unchanged. DPSM remains the CMIS configuration state machine. | Live Ethernet DATA readiness must not be inferred from `DPActivated` alone. |

APSU/iLT is disabled by default. The host enables it per lane through the current vendor CDB path.

## Standards And Vendor Baseline

The standards baseline defines the target behavior. The current firmware evidence supports parts of that target, but not the whole APSU path model.

| IEEE/OIF baseline item | Status | Current evidence | Validation decision |
|---|---|---|---|
| APSU coordinates orderly ISL initialization across a path | Unverified | IEEE/OIF source plus selected lab observations. | Build a path-level APSU validation report before claiming conformance. |
| iLT establishes peer communication, optimizes signaling, and coordinates transition toward DATA | Unverified | Email/lab observations and Sian3 cAPI status. | Use as supporting evidence only. Do not claim full IEEE iLT conformance. |
| RTS/readiness gates live DATA separately from `DPActivated` | Implemented | State-machine source and Sian3 status model. | Keep this rule in customer wording. |
| Page 70h exposes standardized APSU/iLT control and status | Planned | OIF draft and customer-note plan. | Implement and validate it before claiming support. |
| APSU and non-APSU behavior coexist without changing MSM | Implemented | OIF draft and state-machine source. | Treat as design alignment until regression-tested. |
| Multiple APSU/iLT instances cover host/media lanes | Implemented | Vendor CDB enable masks. | Add broader host/media lane-combination coverage. |
| Broad IEEE 802.3dj APSU interoperability | Unverified | No non-Sian3 partner evidence is loaded. | Test with non-Sian3 partners before making broad compatibility claims. |

The Sian3 baseline defines the vendor behavior currently exercised by firmware and lab tooling.

| Sian3 expectation | Status | Current evidence | Validation decision |
|---|---|---|---|
| APSU/LT controls map to Sian3 lane configuration fields | Implemented | Customer vendor CDB, lab debug CDB, and Sian3 cAPI. | Keep cAPI details as implementation evidence. Do not present them as the customer interface. |
| Path-up status uses `training_status = 3`, `apsu_control_state = 7`, and local/remote ready asserted | Verified | Loaded Feng logs through lab debug CDB. | Use as lab-observed status evidence. |
| Rx polarity correction works when LT is enabled | Verified | Email observations and screencopies. | Phrase as lab-observed until a single ordered raw log is loaded. |
| Tx equalization/tap optimization improves degraded BER | Verified | Loaded logs and screencopies. | Use numeric BER ranges and tap stability as lab evidence. |
| Temperature corners at about 0 C, 45 C, and 70 C work | Verified | Loaded temperature logs. | Keep as lab-observed behavior. |
| Temperature shift from 10 C to 60 C does not force automatic FIR re-optimization | Verified | Email observation. | Avoid implying continuous adaptation. |
| Sian3 status includes remote TF lock and remote mode fields | Implemented | Source recheck of `link_training_status_t` and `qsfpMsaRegs.c`. | Treat `remote_tf_lock`, `remote_tp_mode`, and `remote_mc_mode` as covered by source. |
| Sian3 APSU timers are host-settable through public cAPI | Implemented | Source recheck of `lane_lnktrn_info_t`. | Treat `max_recovery_events`, `forward_rts_timer`, `recovery_timer`, `propagation_timer`, `quiet_timer`, and `max_wait_timer` as covered. |
| Training pattern, mode sequencing, and detailed TP/MC/TF-lock behavior are captured | Unverified | Sian3 application note. | Add explicit captures if the customer note needs this detail. |
| Bundled lane restart, recovery reason, and recovery counter behavior are validated | Unverified | Sian3 application note and source fields. | Add restart/recovery tests before claiming the behavior. |
| Valid APSU/LT configuration matrix is covered | Unverified | Sian3 application note and current CDB masks. | Validate selected host/media enable-mask combinations. |

The source recheck narrows the cAPI gap list.

The remaining public cAPI gaps are mainly exact IEEE variable exposure: `PMA_reset`, `PMD_reset`, `uses_recovered_clock`, `isl_ready`, `training_failure`, and direct host-set `ic_req`, `coef_sel`, and `coef_req`.

## Evidence Coverage

The loaded evidence supports selected LT behavior. It does not yet support every customer claim a complete verification report would need.

| Evidence item | Status | Covered | Remaining gap |
|---|---|---|---|
| Test setup image | Verified | Temperature chamber, Sian3 DUT BERT board, Sian3 REF BERT board, DUT/REF GungnirS modules, `TP0 -> TP1`, `TP4 -> TP5`, and GoLight VOA. | Actual VOA attenuation and insertion loss are missing. |
| May 22 degraded-tap run | Verified | Worse-tap BER ranged from `1.34e-10` to `6.38e-7`. After DUT LT, LT-on BER ranged from `0` to `2.49e-12`, with path-up status and ready bits asserted. | Physical channel loss is not quantified. |
| BERT-only LT before DUT LT | Verified | BER parsed as `1.0` before DUT LT, supporting the need to enable both sides. | This is not a standalone conformance test. |
| May 25 repeatability loaded runs | Verified | Two runs show worse-tap BER up to `6.20e-7` and `6.13e-7`. LT-on BER fell to `0` to `2.87e-12` and `0` to `1.60e-12`. | Email describes three runs. Only two raw repeatability logs are loaded. |
| Third repeatability raw log | Missing | Email says a third run existed. | Import only if a three-run claim is needed. |
| Temperature corners | Verified | About 0 C, 45 C, and 70 C runs show `training_status = 3`, `apsu_control_state = 7`, ready bits asserted, and LT-on BER up to `1.12e-10`, `2.33e-12`, and `2.66e-12`. | This is not convergence-time evidence. |
| Temperature-shift behavior | Verified | Email reports 10 C worse-tap BER about `10e-8`, LT BER about `10e-11`, 60 C BER about `10e-12`, no FIR change while LT stayed enabled, and new FIR after restart. | Matching raw log or screenshot is missing. |
| Polarity recovery | Verified | Forced polarity broke traffic with FEC BER `1.0`. Enabling LT on BERT and DUT recovered traffic, and polarity masks changed. | A single ordered, timestamped raw log is missing. |
| Common degraded tap settings | Verified | Lanes 0-3 used `[0, 0, -7, 50, 0, 0, 0, 0, 0, 0, 0, 0, 0]`. Lanes 4-7 used `[-10, 10, 50, 78, 0, 0, 0, 0, 0, 0, 0, 0, 0]`. | Logs emit two tap records per lane without endpoint labels. |
| Convergence time | Unverified | Evidence says taps changed too quickly for the DSP API method to capture. | Add an independent timing method or state unmeasured. |
| Customer vendor CDB transaction trace | Missing | Source plan documents the commands. | Capture direct `0xA200`, `0xA201`, `0xA082`, and `0xA083` transactions if customer evidence needs them. |
| Page 70h validation | Missing | Draft ranges and intended mapping are known. | Validate after implementation. |
| Non-Sian3 interoperability | Missing | No loaded evidence. | Add partner coverage before claiming broad APSU compatibility. |

## Open Gaps

These are the gaps that should control customer wording and validation priority.

| Gap | Status | Impact | Close condition |
|---|---|---|---|
| Standard CMIS Page 70h interface | Planned | Current support is vendor CDB based, not standard CMIS memory-map support. | Implement and validate Page 70h. |
| Customer-visible detailed APSU/LT status | Missing | Lab-only Sian3 fields are not the same as customer-facing standard status. | Expose standard status through Page 70h or document explicit limits. |
| Exact customer firmware build evidence | Unverified | Local code evidence may not match the delivered image. | Confirm the build and `BRCM_SPECIFIC` macro state. |
| Quantified high-loss claim | Unverified | Logs show degraded BER, not measured physical loss. | Capture attenuation or insertion loss, or remove the high-loss wording. |
| Convergence time | Unverified | Current timestamps are post-enable observations. | Measure with an independent method or state unmeasured. |
| Missing raw artifacts | Missing | Third repeatability run, temperature-shift artifact, and ordered polarity raw log are not loaded. | Import only the artifacts needed for intended claims. |
| DUT versus REF/BERT tap identity | Unverified | Logs show two tap records per lane without endpoint labels. | Label endpoints in future logs. |
| Non-Sian3 interoperability | Missing | Current evidence is Sian3-focused. | Test against non-Sian3 partners and standard host assumptions. |
| Full IEEE APSU path conformance | Unverified | Evidence covers selected LT behavior, not complete path behavior. | Run a path-level APSU conformance validation. |

## Recommended Validation Actions

| Priority | Action | Reason |
|---|---|---|
| P0 | State that Page 70h is planned, not current. | Prevents the customer note from implying current standard CMIS support. |
| P0 | Confirm the exact customer firmware build and `BRCM_SPECIFIC` macro state. | Keeps implementation evidence tied to the delivered image. |
| P0 | Prove or remove the high-loss claim. | Current evidence shows degraded BER, not quantified physical loss. |
| P0 | Measure convergence time with an independent method or mark it unmeasured. | Current logs only show post-enable sampling. |
| P0 | Qualify temperature-shift behavior as lab-observed. | The observation is useful, but raw artifacts are not loaded. |
| P1 | Import the third repeatability log, May 26 temperature-shift artifact, or ordered polarity raw log only if those claims are needed. | Closes specific claim gaps without collecting unnecessary raw data. |
| P1 | Capture customer vendor CDB transactions for `0xA200`, `0xA201`, `0xA082`, and `0xA083`. | Gives direct evidence for the customer-accessible path. |
| P1 | Validate Page 70h after implementation. | Moves detailed customer status to the standard interface. |
| P1 | Add host/media lane-combination and non-Sian3 interoperability coverage. | Reduces risk around configuration breadth and partner assumptions. |
| P2 | Label DUT and REF/BERT tap records in future logs. | Makes tap optimization evidence easier to audit. |
| P2 | Maintain a compact claim-to-evidence map. | Keeps the customer note defensible as evidence grows. |

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
- [ieee-apsu-ilt-fields-missing-from-sian3-capi](../queries/ieee-apsu-ilt-fields-missing-from-sian3-capi.md)

Code-derived evidence is implementation traceability, not a customer-facing interface claim.

- Vendor CDB path: `qsfpCdb.c :: QSfpVdrA200`, `qsfpCdb.c :: QSfpVdrA201`, and `qsfpCdbLt.h :: ACT_LT_ENABLE`.
- Lab debug bridge: `sian3.py :: Debug`, `liteIntRegs.h :: debug_access_t`, `dsp_debug_cmd_lktrn_info_t`, `dsp_debug_cmd_lktrn_status_t`, and `dsp_debug_cmd_precode_t`.
- Firmware debug handling: `qsfpMsaRegs.c :: DSP_DEBUG_CMD_LKTRN_INFO`, `DSP_DEBUG_CMD_LKTRN_STAT`, and `DSP_DEBUG_CMD_PRECODE`.
- Sian3 public cAPI: `capi_def.h :: lane_lnktrn_info_t` and `capi_def.h :: link_training_status_t`.
- Sian3 cAPI bridge: `qsfpMsaRegs.c` lane link-training config/status copy paths.
- Lite CDB packet fields: `qsfpLiteCdb.h` command/status layouts for `mr_restrt`, `identifier_i`, `prbs13_seed_i`, and `prbs31_seed_i`.
- Precoding path: `sian3.py :: Debug.set_precode`, `Debug.get_precode`, and `qsfpMsaRegs.c :: DSP_DEBUG_CMD_PRECODE`.
- Build switch to confirm: `main.h :: BRCM_SPECIFIC`.
