---
type: query
title: IEEE APSU/iLT fields missing from Sian3 cAPI
created: 2026-06-10
updated: 2026-06-10
tags: [ieee-802-3dj, apsu, ilt, sian3, capi, gap-analysis, query]
related: [../sources/ieee-p802-3dj-d2-3.md, ../sources/broadcom-2026-sian3-apsu-application-notes.md, standard-apsu-ilt-procedure-host-vs-media-links.md, sian3-behavior-conflicts-with-802-3dj-apsu-ilt.md]
sources: [../sources/ieee-p802-3dj-d2-3.md, ../sources/broadcom-2026-sian3-apsu-application-notes.md, standard-apsu-ilt-procedure-host-vs-media-links.md, "C:/Users/huy82684/projects/1p6_sian3_fw_h5/v0_1/fw/src/dsp/chip/indep/inc/capi_def.h", "C:/Users/huy82684/projects/1p6_sian3_fw_h5/v0_1/fw/src/qsfpMsaRegs.c", "C:/Users/huy82684/projects/1p6_sian3_fw_h5/v0_1/fw/src/qsfpLiteCdb.h"]
status: draft
---

# IEEE APSU/iLT Fields Missing From Sian3 cAPI

## Scope

This compares IEEE P802.3dj/D2.3 Annex 178B management variables and PICS items against:

- the Sian3 APSU cAPI fields documented in `CMIS/raw/sources/Sian3 APSU Application Notes_Customer_Release.pdf`;
- the current source-code cAPI structs in `C:/Users/huy82684/projects/1p6_sian3_fw_h5/v0_1/fw/src/dsp/chip/indep/inc/capi_def.h`;
- the firmware bridge/debug code in `qsfpMsaRegs.c` and lite-CDB packet definitions in `qsfpLiteCdb.h`.

`Missing` below means not exposed as a named public Sian3 APSU cAPI field in `lane_lnktrn_info_t` or `link_training_status_t`. It does not prove the Sian3 firmware lacks the underlying protocol behavior internally.

## Source-Code Recheck Delta

The source-code check corrects the earlier PDF-only conclusion:

- `remote_tf_lock` is implemented in `link_training_status_t` and is bridged through `qsfpMsaRegs.c`; it should be treated as covered.
- `remote_tp_mode` and `remote_mc_mode` are also present in the source status struct even though the earlier note focused on local mode fields.
- All five main Annex 178B timers are host-settable through public cAPI: `max_recovery_events`, `forward_rts_timer`, `recovery_timer`, `propagation_timer`, `quiet_timer`, and `max_wait_timer`.
- `mr_restart`, `identifier_i`, `prbs13_seed_i`, and `prbs31_seed_i` appear in `qsfpLiteCdb.h` lite-CDB packet definitions, but not in the public cAPI structs or the `qsfpMsaRegs.c` cAPI bridge path searched here. Treat them as lite-CDB/debug-surface fields, not public Sian3 cAPI fields.

## Short Answer

Yes. Sian3 cAPI covers the main APSU/iLT enablement, progress, readiness, recovery counter, coefficient/status, and timer controls, but it does not expose every IEEE Annex 178B management variable.

The main gaps are:

- `mr_restart` is not exposed as a named public APSU/iLT cAPI restart control. A misspelled `mr_restrt` bit exists in lite-CDB command layouts `0xb001`/`0xb002`.
- `PMA_reset` and `PMD_reset` are not part of the APSU cAPI surface.
- `identifier_i`, `prbs13_seed_i`, and `prbs31_seed_i` are not exposed as public cAPI training-pattern seed/identifier controls; they appear only in the lite-CDB `0xb003` status layout found in source.
- `isl_ready` and `training_failure` are not exposed as named status fields; Sian3 exposes higher-level `training_status`, `apsu_control_state`, and recovery fields.
- `uses_recovered_clock` is not exposed as a named status variable; Sian3 exposes `retimer_mode` as a configuration mode.
- `ic_req`, `coef_sel`, and `coef_req` appear in Sian3 status/readback fields but not as explicit host-set cAPI controls in the documented setter path.
- IEEE frame-level details such as frame marker, parity, coefficient-select echo, and handshake timing are protocol/PICS requirements, not directly exposed as Sian3 cAPI management fields.

## IEEE Annex 178B Management Variables Vs Sian3 cAPI

| IEEE Annex 178B variable or item | Type | Sian3 cAPI coverage in current note | Gap classification |
|---|---|---|---|
| `PMA_reset` | Control | Not listed in APSU cAPI. | Missing from APSU cAPI; likely handled by non-APSU reset/control paths if available. |
| `PMD_reset` | Control | Not listed in APSU cAPI. | Missing from APSU cAPI; likely handled by non-APSU reset/control paths if available. |
| `mr_restart` | Control | No named public cAPI restart field. `qsfpLiteCdb.h` defines `mr_restrt` in lite-CDB command layouts, but this was not found in the public `lane_lnktrn_info_t` cAPI struct. | Missing from public cAPI; present only in lite-CDB/debug packet definition found here. |
| `mr_training_enable` | Control/status | `lnktrn_en`; status also reports `mr_training_enable`. | Covered. |
| `training_status` | Status | `training_status` with idle/training/ISL-ready/path-up/fail mapping. | Covered, though Sian3 value names differ from IEEE literal values. |
| `identifier_i` | Control/config | Not in public cAPI structs. Present in `qsfpLiteCdb.h` `0xb003` get-status packet layout. | Missing from public cAPI; lite-CDB/debug status field exists. |
| `prbs13_seed_i` | Control/config | Not in public cAPI structs. Present in `qsfpLiteCdb.h` `0xb003` get-status packet layout. | Missing from public cAPI; lite-CDB/debug status field exists. |
| `prbs31_seed_i` | Control/config | Not in public cAPI structs. Present in `qsfpLiteCdb.h` `0xb003` get-status packet layout. | Missing from public cAPI; lite-CDB/debug status field exists. |
| `ic_req` | Control field | Sian3 reports `init_cond_request` and remote counterpart in status. Setter path does not expose it. | Readback/diagnostic only in documented cAPI; no explicit host-set control shown. |
| `coef_sel` | Control field | Sian3 reports `coeff_select` and remote counterpart in status. Setter path does not expose it. | Readback/diagnostic only in documented cAPI; no explicit host-set control shown. |
| `coef_req` | Control field | Sian3 reports `coeff_request` and remote counterpart in status. Setter path does not expose it. | Readback/diagnostic only in documented cAPI; no explicit host-set control shown. |
| `coef_sts` | Status | `coeff_status` and `remote_coeff_status`. | Covered. |
| `ic_sts` | Status | `init_cond_status` and `remote_init_cond_status`. | Covered. |
| `local_tf_lock` | Status | `local_tf_lock`. | Covered. |
| `remote_tf_lock` | Status | Present in `link_training_status_t` and bridged into `qsfpMsaRegs.c`. | Covered by source, even if not prominent in the PDF summary. |
| `local_rx_ready` | Status | `local_rx_ready`. | Covered. |
| `remote_rx_ready` | Status | `remote_rx_ready`. | Covered. |
| `local_rts` | Status | `local_rts`. | Covered. |
| `remote_rts` | Status | `remote_rts`. | Covered. |
| `max_recovery_events` | Control/config | `max_recovery_events`. | Covered. |
| `max_wait_timer_duration` | Timer/config | `apsu_max_wait_timer`. | Covered under Sian3 name. |
| `uses_recovered_clock` | Status/config variable | No named status field. Sian3 exposes `retimer_mode`. | Partial; mode control exists, standard variable not directly exposed. |
| `local_mc_mode` | Status | `local_mc_mode`. | Covered. |
| `local_tp_mode` | Status | `local_tp_mode`. | Covered. |
| Remote training-pattern and modulation modes | Status | `remote_tp_mode` and `remote_mc_mode` are present in `link_training_status_t`. | Covered by source. |
| `isl_ready` | Status | No named field. Can be inferred from `apsu_control_state`, `training_status`, and readiness bits. | Missing as named status; inferable. |
| `training_failure` | Status | No named field. Sian3 has `training_status = Fail`, `apsu_control_state = FAIL`, and `recovery_reason`. | Missing as named status; inferable/diagnostic alternative exists. |
| `polarity_correction` | Status | `polarity_correction`; Sian3 also has `auto_pol_en` control. | Covered. |

## Timer Coverage

| IEEE timer concept | Sian3 cAPI field | Coverage |
|---|---|---|
| `forward_rts_timer`, 10-90 ms | `forward_rts_timer` | Covered. |
| `quiet_timer`, 100-200 ms | `apsu_quiet_timer` | Covered under Sian3 name. |
| `propagation_timer`, 100-200 ms | `propagation_timer` | Covered. |
| `recovery_timer`, 20-30 ms | `recovery_timer` | Covered. |
| `max_wait_timer_duration` / `max_wait_timer` | `max_wait_timer` / PDF name `apsu_max_wait_timer` | Covered. Source uses `uint16_t max_wait_timer`, documents 0-27 seconds, 0 infinite, and default 12000 ms; validation checks 0-27000. |

## Counters And Recovery

| IEEE item | Sian3 cAPI field | Coverage |
|---|---|---|
| `recovery_event_count` | `recovery_event_count` | Covered; read clears it. |
| Recovery reason | `recovery_reason` | Sian3 extension/diagnostic field; useful even though it is not one of the extracted Annex 178B management variables. |

## Protocol/PICS Items Not Exposed As cAPI Knobs

IEEE Annex 178B PICS lists mandatory or optional functions such as frame marker handling, polarity detection, synchronous PRBS13, free-running PRBS13, free-running PRBS31, E1/O1 control and status field structures, training frame lock, coefficient update request/response processes, and handshake timing. Sian3 claims behavior aligned to these areas, but the cAPI does not expose every low-level frame field as a management knob.

For API-level gap tracking, treat these as implementation/protocol requirements rather than missing host controls unless a validation plan needs direct management visibility into a specific field.

## Practical Impact

For current Sian3 cAPI-based bring-up:

- Use `lnktrn_en`, `apsu_en`, `apsu_control_state`, `training_status`, readiness bits, RTS bits, polarity, coefficient/status fields, recovery fields, and timer fields as the documented API surface.
- Do not promise full IEEE Annex 178B management-variable coverage through Sian3 cAPI.
- For future CMIS Page 70h mapping, decide whether the missing named fields need direct exposure, derived status, or explicit "not supported/not applicable" behavior.

Source-code reference points:

- `capi_def.h:1044-1153` defines `lane_lnktrn_info_t` public cAPI controls and timer fields.
- `capi_def.h:4216-4290` defines `link_training_status_t`, including `remote_tf_lock`, remote pattern/mode fields, readiness bits, RTS bits, recovery fields, coefficient fields, APSU state, and APSU enable status.
- `qsfpMsaRegs.c:5812-5871` and `qsfpMsaRegs.c:6652-6703` bridge the lane link-training config/status fields through the firmware debug/CDB path.
- `qsfpLiteCdb.h:74-264` defines lite-CDB command/status packets with `mr_restrt`, `identifier_i`, `prbs13_seed_i`, and `prbs31_seed_i`, but these are not the same as the public cAPI structs.
