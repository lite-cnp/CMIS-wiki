---
type: query
title: How should hosts use Sian3 APSU cAPI?
created: 2026-06-09
updated: 2026-06-09
tags: [cmis, apsu, sian3, broadcom, host-bring-up, query]
related: [../concepts/autonomous-path-startup.md, ../concepts/vendor-specific-cmis-customizations.md, ../synthesis/apsu-ilt-customer-note-plan.md]
sources: [../sources/lumentum-2026-8023dj-apsu-ilt-support-plan.md, ../sources/lumentum-2026-dpsm-apsu-ilt-state-machine.md, ../sources/broadcom-2026-sian3-apsu-application-notes.md, ../sources/broadcom-2025-sian3-ilt-procedure.md, ../sources/feng-jiang-2026-sian3-link-training-verification-email-thread.md, ../sources/oif2026-093-08-802-3dj-apsu-draft.md, ../sources/ieee-p802-3dj-d2-3.md]
status: draft
---

# How should hosts use Sian3 APSU cAPI?

For Broadcom Sian3, host software should treat the APSU cAPI as a vendor-specific APSU and link-training control/status plane. Use it alongside CMIS Data Path or Network Path state, not as a replacement for CMIS state-machine handling.

## Short Answer

Enable APSU/link training through Sian3 cAPI, keep the default timers and automatic modes unless debugging requires otherwise, then poll both APSU progress and readiness fields until the path is up. For APSU applications, do not treat CMIS `DPActivated` alone as proof that live Ethernet DATA is flowing.

## Current Customer-Note CDB Overlay

The newer Lumentum [802.3dj APSU/iLT support plan](../sources/lumentum-2026-8023dj-apsu-ilt-support-plan.md) describes the current customer-facing module interface as NVIDIA-defined vendor CDB rather than CMIS Page 70h. Use that plan for customer-note status and roadmap wording:

- Current firmware implements vendor CDB commands `0xA200`, `0xA201`, `0xA082`, and `0xA083`.
- APSU/iLT is disabled by default and enabled by the host per lane.
- Formal CMIS Page 70h support is planned after validation closure and should not be claimed as current behavior.
- The [DPSM APSU/iLT diagram](../sources/lumentum-2026-dpsm-apsu-ilt-state-machine.md) keeps the same host rule: `DPActivated` is CMIS configuration complete, while live DATA readiness still needs APSU/LT status such as `PATH_UP`, RTS, or iLT completion.

Keep the rest of this page as Broadcom Sian3 cAPI background. When writing the customer note for current firmware, prefer the vendor CDB command names above over cAPI field names unless the audience specifically needs the Broadcom cAPI mapping.

## Bring-Up Checklist

1. Confirm the target application/path is APSU capable and that the Sian3 firmware is in scope for the application note, `D003_0000` or newer.
2. Choose one of the valid Sian3 configurations: both sides LT on, client LT only, line LT only, APSU without LT, or APSU/LT disabled.
3. Use `capi_set_lane_config_info()` with `LANE_CONFIG_TYPE_LANE_LINK_TRAINING_INFO` to set `lnktrn_en` and `apsu_en`.
4. Prefer defaults for `auto_pol_en`, `auto_restart`, `slicer_mode`, `retimer_mode`, and the APSU timers unless the lab setup needs a controlled override.
5. Use `capi_get_lane_info()` with `lnktrn_status` enabled to monitor bring-up.
6. Require a coherent readiness view: `apsu_control_state` at `PATH_UP`, `training_status` at path-up, frame lock asserted, local/remote Rx ready, and local/remote RTS asserted.
7. Record `recovery_reason` and `recovery_event_count` before subsequent reads clear them.
8. For bundled ports, handle a single-lane restart as a whole-port training restart.

## Operational Gotchas

- Non-link-training frames from a link partner can cause repeated Sian3 restarts while status reports no training-frame lock and signal detected.
- A squelched link-partner transmitter reports signal loss and triggers restart.
- Enabling link training enables automatic Rx polarity detection/correction; disabling link training returns polarity to the user setting.
- Client-side Sian3 link training can auto-select NR or ER slicer mode.
- Sian3 uses PAM2 and PRBS13 in `QUIET`, then requests PRBS31 after entering `TRAIN_LOCAL`.
- The electrical side supports Tx equalization and precoder request; the Sian3 optical receiver does not request Tx precoder from the link partner.

## Lab Verification Evidence From Feng Jiang Thread

The Outlook thread [feng-jiang-2026-sian3-link-training-verification-email-thread](../sources/feng-jiang-2026-sian3-link-training-verification-email-thread.md) adds module-level verification evidence from Sian3 BERT and DUT module testing.

Test setup and scope captured in the email body:

- Feng tested `TP0 -> TP1` and `TP4 -> TP5` on Sian3 BERT and DUT module.
- Link training was enabled on both BERT and DUT module host side for the polarity recovery case.
- The thread requested high-loss evidence, but the fetched body text does not confirm the actual loss profile.

Observed behavior:

- Polarity: setting DUT `InputPolarityFlipTx` and `OutputPolarityFlipRx` to `255` broke traffic; enabling link training restored traffic, with link-training status `3` and polarity changed on DUT module host Tx and BERT host Tx.
- SI/taps: with degraded module/BERT taps, BER became worse; enabling link training changed taps and improved BER.
- Convergence: after enabling link training, status and taps changed too quickly for Feng to measure convergence time using the DSP API.
- Repeatability: three runs with the same degraded taps produced almost the same optimized tap values, with small differences.
- Temperature corners: at 0, 45, and 70 C case temperatures, optimized DSP tap values differed by temperature.
- Temperature shift: after optimizing at 10 C and moving to 60 C, FIR did not update automatically even though BER changed. Disabling and re-enabling link training produced a new FIR value adjusted to the current temperature.
- Write protection: trying to change FIR while link training was enabled failed with `return_result = 1`.

Host diagnostic implications:

- Treat link training as a startup/restart optimization event, not necessarily a continuously adaptive FIR update loop.
- If the environment changes materially after a successful link-training pass, a host-side diagnostic may need to restart LT to force a new FIR solution.
- Do not rely only on `training_status == 3`; capture BER/tap evidence before and after LT when customer-facing verification is needed.
- Preserve raw screenshots/attachments when available because the email body references reports but does not expose exact numeric tap tables.

## Obsolete ILT Procedure Context

[broadcom-2025-sian3-ilt-procedure](../sources/broadcom-2025-sian3-ilt-procedure.md) appears to be the older Broadcom attachment discussed in the email thread. It should be used as a historical setup reference, not as current APSU behavior guidance.

Useful setup sequence from the old procedure:

1. Keep ILT disabled during module preparation.
2. Match BERT and module chip modes; the example uses `MODE_14` with submode `14.1` for an 8x212G KP4 PAM4 repeater configuration.
3. Use BERT Tx PRBS and verify PRBS lock on module Host Rx, module Line Rx, and BERT Rx to validate lane swap and polarity.
4. Disable PRBS, enable FEC pattern from BERT Tx, and confirm FEC monitor lock with ILT still disabled.
5. Enable ILT on BERT host side using `CAPI_ENABLE_LKTRN`.
6. Configure the module chip mode.
7. Enable ILT on both module host and line sides.
8. Check module client, module line, and BERT client status with `CAPI_GET_LKTRN_STATUS`.

Use this older flow only to understand the lab setup. Prefer the newer APSU application note for field definitions, valid configurations, APSU status interpretation, and current firmware scope.

## Relationship to CMIS and OIF APSU Drafts

The OIF APSU draft models APSU as orthogonal to CMIS configuration state and sketches standard CMIS Page 70h controls/status. The Sian3 note shows a vendor cAPI realization of similar IEEE variables. Keep these layers separate:

- CMIS still owns module, data-path, and network-path configuration state.
- IEEE APSU/ILT owns protocol startup and readiness for DATA.
- Sian3 cAPI exposes the implementation-specific control and status path for APSU/ILT on Broadcom Sian3.

## Practical Host Rule

For Sian3 APSU links, a host bring-up routine should have two gates: a CMIS configuration gate and a Sian3 APSU readiness gate. Only after both pass should the host classify the link as ready for normal data operation.
