---
type: source
title: Broadcom 2026 Sian3 APSU Application Notes
created: 2026-06-09
updated: 2026-06-09
tags: [cmis, apsu, ilt, ieee-802-3dj, broadcom, sian3, vendor-specific, source]
related: [../concepts/autonomous-path-startup.md, ../concepts/vendor-specific-cmis-customizations.md, ../sources/broadcom-2025-sian3-ilt-procedure.md, ../sources/feng-jiang-2026-sian3-link-training-verification-email-thread.md, ../queries/how-should-hosts-use-sian3-apsu-capi.md]
authors: [Broadcom]
year: 2026
venue: Customer Release Application Note
source_filename: raw/sources/Sian3 APSU Application Notes_Customer_Release.pdf
firmware_scope: "Sian3 FW D003_0000 or newer"
supersedes: broadcom-2025-sian3-ilt-procedure
status: draft
---

# Broadcom 2026 Sian3 APSU Application Notes

This Broadcom Sian3 application note describes a vendor implementation of IEEE 802.3dj Annex 178B Autonomous Path Startup (APSU) and link training for 200 Gb/s electrical and optical interfaces. It is useful as an implementation example, not as a base CMIS or OIF supplement source.

## Classification

- Vendor-specific implementation note for Sian3.
- Aligned to IEEE P802.3dj Annex 178B Draft 2.4.
- Applies to Sian3 firmware `D003_0000` or newer.
- Uses Broadcom cAPI fields rather than a standard CMIS memory-map interface.
- Complements the OIF APSU draft source [oif2026-093-08-802-3dj-apsu-draft](oif2026-093-08-802-3dj-apsu-draft.md) and the concept page [autonomous-path-startup](../concepts/autonomous-path-startup.md).
- Supersedes the older procedure-only source [broadcom-2025-sian3-ilt-procedure](broadcom-2025-sian3-ilt-procedure.md), which is useful historically but should not be treated as current guidance.

## Core Implementation Points

- Sian3 supports APSU and link training on both client and line sides for all lanes of a port.
- Rx polarity detection and correction is enabled by default when link training is enabled. When link training is disabled, Rx polarity returns to the user setting.
- Client-side link training can automatically select NR or ER slicer mode based on channel condition.
- Link training uses PAM2 and PRBS13 in `QUIET`; after transition to `TRAIN_LOCAL`, firmware requests PRBS31 as the training-pattern payload.
- Training-pattern changes are supported based on the link partner request; Sian3 receiver requests the partner to send free-running PRBS31.
- Tx equalization control and precoder request are available for the electrical side per the standard.
- Tx precoder change follows link-partner request, but the Sian3 optical receiver does not request Tx precoder from the link partner.
- On bundled lane ports, any one-lane link-training restart restarts link training on all lanes in the bundle.

## Valid APSU and Link-Training Configurations

| APSU | Client-side link training | Line-side link training | Meaning |
|---|---|---|---|
| ON | ON | ON | APSU with link training on both sides. |
| ON | ON | OFF | APSU with client-side link training only. |
| ON | OFF | ON | APSU with line-side link training only. |
| ON | OFF | OFF | APSU without link training. |
| OFF | OFF | OFF | APSU and link training disabled. |

The note does not present mixed configurations where APSU is off but one side of link training is on.

## Interop and Restart Behavior

- If link training is enabled and the link partner sends non-link-training frames, Sian3 keeps restarting link training. The status cAPI reports no training-frame lock and signal detected.
- If link training is enabled and the link partner squelches its transmitter, the status cAPI reports signal loss and Sian3 restarts link training.
- For an 800GbE bundled port with four 200G lanes, one lane restart causes all four lanes to restart link training.

## Fault Handling When Links Are Up

| APSU | Client LT | Line LT | Client-side LOS or CDR LOL | Line-side LOS or CDR LOL |
|---|---|---|---|---|
| ON | ON | ON | Client and line sides squelch Tx and restart link training. | Client and line sides squelch Tx and restart link training. |
| ON | ON | OFF | Client side squelches Tx and restarts link training; line side squelches Tx. | Client side squelches Tx and restarts link training; line side squelches Tx. |
| ON | OFF | ON | Line side squelches Tx and restarts link training; client side squelches Tx. | Line side squelches Tx and restarts link training; client side squelches Tx. |
| ON | OFF | OFF | Line side squelches Tx; client-side Tx stays in mission mode. | Client side squelches Tx; line-side Tx stays in mission mode. |
| OFF | OFF | OFF | Line side squelches Tx; client-side Tx stays in mission mode. | Client side squelches Tx; line-side Tx stays in mission mode. |

## Control and Configuration cAPI Fields

| Field | Meaning | Values or default |
|---|---|---|
| `apsu_en` | APSU enable/disable | `0` disable default, `1` enable |
| `lnktrn_en` | Link-training enable/disable | `0` disable default, `1` enable |
| `opposite_cdr_first` | Whether to wait for opposite CDR lock before starting link training | `0` start training then check CDR lock default, `1` wait first |
| `auto_restart` | Restart link training after failure | `0` do not restart, `1` restart default |
| `auto_pol_en` | Auto polarity enable | `0` disabled, `1` enabled default |
| `slicer_mode` | Client-side slicer mode | `0` auto select default, `1` NR, `2` ER |
| `retimer_mode` | Retimer or PCS mode | `0` PCS local clock/data generation, `1` retimer mode default |
| `lnktrn_type` | Link-training type | read-only |
| `max_recovery_events` | Maximum allowed transitions into `RECOVERY` | `0` unlimited default, otherwise 1-31 |
| `forward_rts_timer` | Timer for RTS update state diagram in `SWITCH_CLOCK` | 10-90 ms, default 20 ms |
| `recovery_timer` | Timer for training control in `RECOVERY` | 20-30 ms, default 30 ms |
| `propagation_timer` | Timer for training control in `PATH_READY` | 100-200 ms, default 100 ms |
| `apsu_quiet_timer` | Timer when training control enters `QUIET` | 100-200 ms, default 100 ms |
| `apsu_max_wait_timer` | Timer when training control enters `TRAIN_START` | 0-27000 ms, default 12000 ms; `0` means infinite |

The sample setter path uses `capi_set_lane_config_info()` with `LANE_CONFIG_TYPE_LANE_LINK_TRAINING_INFO`, setting `lnktrn_en` and `apsu_en` through `capi_lane_config_info.type.lane_lnktrn_info`.

## Status cAPI Fields

| Field | Meaning |
|---|---|
| `apsu_enabled` | Whether APSU is enabled. |
| `mr_training_enable` | `1` if link training is enabled, `0` if disabled. |
| `apsu_control_state` | APSU training control state: `0 QUIET`, `1 SEND_TRAINING`, `2 TRAIN_START`, `3 TRAIN_LOCAL`, `4 TRAIN_REMOTE`, `5 ISL_READY`, `6 PATH_READY`, `7 PATH_UP`, `8 RECOVERY`, `9 FAIL`, `10 SEND_LOCAL`. |
| `training_status` | `0 Idle`, `1 Training`, `2 ISL ready`, `3 Path up`, `4 Fail`. |
| `local_tp_mode` | Tx training pattern: `0` synchronous PRBS13, `1` free-running PRBS13, `2` free-running PRBS31. |
| `local_mc_mode` | Training-pattern modulation/coding: `0` PAM2, `1` PAM2 with precoding, `2` PAM4, `3` PAM4 with precoding. |
| `tx_mode` | Tx mode: `0` squelched, `1` training, `2` local pattern, `3` data from the other interface. |
| `local_tf_lock` | `1` if training-frame marker is identified. |
| `local_rx_ready` | `1` if local Rx is optimized and ready for data. |
| `remote_rx_ready` | Peer-interface value of `local_rx_ready`. |
| `local_rts` | Local ready-to-send/receive normal data. |
| `remote_rts` | Peer-interface value of `local_rts`. |
| `polarity_correction` | `1` if an inverted marker is detected. |
| `recovery_reason` | Link-training recovery reason; read clears it. |
| `recovery_event_count` | Incremented on each transition into `RECOVERY`; read clears it. |
| `coeff_status`, `init_cond_status`, `init_cond_request`, `coeff_select`, `coeff_request` | Local coefficient and initial-condition state. |
| `remote_coeff_status`, `remote_init_cond_status`, `remote_init_cond_request`, `remote_coeff_select`, `remote_coeff_request` | Link-partner coefficient and initial-condition state. |

The sample getter path uses `capi_get_lane_info()` with `lane_info.param.is.lnktrn_status = 1`.

## IEEE Variable and Frame-Field Mapping

The note copies IEEE ILT/APSU variables such as `mr_training_enable`, `apsu_enabled`, `apsu_control_state`, `training_status`, `local_tp_mode`, `local_mc_mode`, `tx_mode`, `local_tf_lock`, `local_rx_ready`, `remote_rx_ready`, `local_rts`, `remote_rts`, `polarity_correction`, and `recovery_event_count`.

Rendered pages 12-13 contain IEEE control/status frame-field tables. Key fields include:

- Control: initial-condition request, continue training, modulation/precoding request, training-pattern request, coefficient select, and coefficient request.
- Status: receiver ready, ILT, training-pattern status, modulation/precoding status, receiver frame lock, initial-condition status, parity, coefficient select echo, and coefficient status.

## Host Implications

- Treat Sian3 cAPI as a vendor-specific control/status plane that is analogous to IEEE APSU variables, not as a base CMIS register map.
- For APSU-capable Sian3 links, combine CMIS DPSM/NPSM state with Sian3 APSU status. `DPActivated` is not enough to prove the link is ready for Ethernet DATA.
- Poll both progress state (`apsu_control_state`, `training_status`) and readiness bits (`local_rx_ready`, `remote_rx_ready`, `local_rts`, `remote_rts`, `local_tf_lock`).
- Use `recovery_reason` and `recovery_event_count` carefully because reads clear them.
- Treat a lane bundle as a shared failure/restart domain.
- Default timers and auto modes are part of the vendor note; only override them with a specific bring-up or debug reason.

## Related Verification Thread

[feng-jiang-2026-sian3-link-training-verification-email-thread](feng-jiang-2026-sian3-link-training-verification-email-thread.md) records module-level BERT/DUT checks against this application-note behavior. The thread adds observed evidence for polarity correction, DSP tap/BER optimization, repeatability, temperature-corner behavior, and a caveat that FIR is not automatically re-optimized after a temperature shift unless link training is restarted.

## Superseded Procedure Note

[broadcom-2025-sian3-ilt-procedure](broadcom-2025-sian3-ilt-procedure.md) is an older `E000_FF10`-era ILT procedure/log note. It gives concrete CLI flow for BERT/module setup, PRBS/FEC pattern checks, enabling `CAPI_ENABLE_LKTRN`, and reading `CAPI_GET_LKTRN_STATUS`, but it predates this APSU note and does not contain the newer APSU feature/fault-handling model.

## Extraction Notes

- Text was extracted with `pdfplumber`.
- Pages 12-13 contain embedded/raster IEEE tables; they were checked by rendering with `pypdfium2`.
- The diagonal "Broadcom Proprietary" watermark introduces stray single letters in raw text extraction; those artifacts were ignored in this summary.
