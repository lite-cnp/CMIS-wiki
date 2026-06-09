---
type: source
title: Broadcom 2025 Sian3 ILT Procedure
created: 2026-06-09
updated: 2026-06-09
tags: [cmis, apsu, ilt, link-training, broadcom, sian3, obsolete, procedure, source]
related: [../sources/broadcom-2026-sian3-apsu-application-notes.md, ../sources/feng-jiang-2026-sian3-link-training-verification-email-thread.md, ../concepts/autonomous-path-startup.md, ../queries/how-should-hosts-use-sian3-apsu-capi.md]
authors: [Broadcom, Rachel Huang]
year: 2025
venue: Application Note
source_filename: raw/sources/Sian3_ILT_AN.pdf
firmware_scope: "Sian3 FW E000_FF10 or newer; mentions planned behavior after E000_F110"
superseded_by: broadcom-2026-sian3-apsu-application-notes
status: obsolete
---

# Broadcom 2025 Sian3 ILT Procedure

This Broadcom application note is titled `Sian3 DSP Inter-layer link training features (ILT) Procedure`. It is a 49-page procedure/log document created in December 2025. It appears to be the older application note referenced in the `Sian3 DSP Link Training Verification` email thread.

Treat this source as obsolete or historical. The current source in this vault is [broadcom-2026-sian3-apsu-application-notes](broadcom-2026-sian3-apsu-application-notes.md), which uses APSU terminology, scopes firmware `D003_0000 or newer`, and aligns to IEEE P802.3dj Annex 178B Draft 2.4.

## Why It Is Obsolete

| Field | Older ILT procedure | Newer APSU application note |
|---|---|---|
| Raw file | `Sian3_ILT_AN.pdf` | `Sian3 APSU Application Notes_Customer_Release.pdf` |
| Creation/modification metadata | 2025-12-06 | Created 2026-04-23, modified 2026-06-02 |
| Title | Sian3 DSP Inter-layer link training features (ILT) Procedure | Sian3 Autonomous Path Startup (APSU) App Notes |
| Firmware scope | FW no earlier than `E000_FF10`; mentions next release after `E000_F110` | FW `D003_0000` or newer |
| Focus | CLI procedure and sample logs for BERT-to-module ILT enable/check | APSU feature behavior, valid configurations, fault handling, cAPI fields, IEEE variable mapping |
| Status in wiki | Historical/procedure reference | Current vendor-specific source |

## Useful Historical Content

Although obsolete, the document is useful because it gives a concrete BERT/DUT bring-up flow:

1. Prepare the module with ILT disabled.
2. Program BERT and module in the same chip mode.
3. For the TH6C-style example, use `MODE_14 - CHIP_MODE_8X212G_KP4PAM_TO_8X212G_KP4PAM` and submode `14.1 - Repeater`.
4. Enable PRBS pattern generation from BERT Tx.
5. Check PRBS lock on Sian3 module Host Rx, Line Rx, and BERT Rx to validate lane swap and polarity.
6. Disable PRBS and enable FEC pattern from BERT Tx.
7. With ILT disabled, confirm FEC monitor lock on module Host Rx, module Line Rx, and BERT Rx.
8. Enable ILT on the BERT host side through `CAPI_ENABLE_LKTRN`.
9. Configure module chip mode.
10. Enable ILT on both module host and line sides.
11. Check module client ILT status with `CAPI_GET_LKTRN_STATUS`.
12. Check module line ILT status.
13. Check BERT client ILT status.

## Key Behavioral Notes

- Both line-side and client-side ILT within the module should be enabled to ensure a complete data path.
- The note says `LT Status = 3` means successful ILT and other values mean unsuccessful ILT. The text says "patch up"; this appears to correspond to "path up" in the newer APSU terminology.
- While ILT is enabled, it uses PRBS pattern generators from both BERT and module sides, so user control of those PRBS generators is unavailable and can return errors.
- ILT can time out. The procedure recommends disabling and re-enabling ILT if enablement takes too long from either the BERT or module side.
- The note says a future firmware release after `E000_F110` would add a user-selectable option to retain optimized Sian host-side settings: Tx FIR, Tx polarity, Tx precoding enable, and Rx NR/ER mode.
- The note says ILT only adjusts line-side Tx precoding enable and line-side Rx NR/ER, so those line-side parameters would not be saved.

## Example Status Fields

The procedure logs successful status retrieval across lanes. Typical fields in the logs include:

- `LT Enabled = 1`
- `LT Status = 3`
- `local_tp_mode` / `remote_tp_mode`
- `local_mc_mode` / `remote_mc_mode`
- `tx_mode`
- `local_tf_lock` / `remote_tf_lock`
- `local_rx_ready` / `remote_rx_ready`
- `local_rts` / `remote_rts`
- `polarity_correction`
- `LT recovery reason`
- `recovery_event_count`
- coefficient and initial-condition fields

The newer APSU application note has a cleaner status-field mapping and should be preferred for field definitions.

## Relationship to Feng Jiang Verification Thread

Feng Jiang's email reported that this older document only covered CLI settings and how to check link-training status, with no actual function or performance description. That assessment matches the extracted document: it is mostly a procedure/log guide, not a verification report.

The thread's module-level evidence for polarity correction, DSP tap improvement, repeatability, and temperature behavior is captured separately in [feng-jiang-2026-sian3-link-training-verification-email-thread](feng-jiang-2026-sian3-link-training-verification-email-thread.md).

## Extraction Notes

- Text was extracted from `Sian3_ILT_AN.pdf` with `pdfplumber`.
- Representative pages were rendered with `pypdfium2` to confirm title, obsolete/procedure scope, and status-log formatting.
- The document contains a diagonal `Broadcom Confidential` watermark, which creates stray text artifacts in raw extraction.
