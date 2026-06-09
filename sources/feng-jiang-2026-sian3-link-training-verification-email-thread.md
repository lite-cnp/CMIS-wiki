---
type: source
title: Feng Jiang 2026 Sian3 Link Training Verification Email Thread
created: 2026-06-09
updated: 2026-06-09
tags: [cmis, apsu, ilt, link-training, sian3, broadcom, verification, email-thread, source]
related: [../concepts/autonomous-path-startup.md, ../sources/broadcom-2025-sian3-ilt-procedure.md, ../sources/broadcom-2026-sian3-apsu-application-notes.md, ../queries/how-should-hosts-use-sian3-apsu-capi.md]
authors: [Feng Jiang, Tao Chen, Huirong Liu, Hock Gin Lim]
year: 2026
venue: Outlook Email Thread
source_subject: "Sian3 DSP Link Training Verification"
date_range: "2026-05-20 to 2026-06-03"
status: draft
---

# Feng Jiang 2026 Sian3 Link Training Verification Email Thread

This source page summarizes the Outlook thread `Sian3 DSP Link Training Verification`, searched on 2026-06-09. The thread records the customer-facing verification question, Broadcom guidance, and Feng Jiang's module-level verification reports for Sian3 link training / ILT.

## Source Scope

- Initial request: Tao Chen asked Broadcom for link-training verification data because the end customer wanted evidence for ILT performance at high electrical loss, convergence time, repeatability, and temperature corners.
- Broadcom response: Huirong Liu pointed to attached steps for verifying LT between BERT and DUT, and later clarified that TP5 Tx sets the training pattern to TP4 Rx and TP4 feeds back to TP5 through TP4 Tx. Huirong also stated that interconnected sides need link training enabled together.
- Feng Jiang's role: Feng produced internal verification reports and conclusions from BERT/DUT testing, including polarity recovery, SI/tap optimization, repeatability, and temperature-corner behavior.
- Attachment status: `Sian3_ILT_AN.pdf` was later loaded into `raw/sources/` and analyzed as [broadcom-2025-sian3-ilt-procedure](broadcom-2025-sian3-ilt-procedure.md). Feng's link-training logs and setup screenshot were later loaded under `raw/sources/` and are summarized below. Inline email screenshots beyond the loaded files are still not separately OCRed.

## Thread Timeline

| Date | Sender | Relevant content |
|---|---|---|
| 2026-05-20 | Tao Chen | Asked for LT/ILT verification data, including high-loss performance, convergence time, repeatability, temperature-corner behavior, whether DSP FW `E002_4000` included host-side SI optimization, and whether Broadcom had setup/results to reference. |
| 2026-05-20 | Huirong Liu | Replied that attached steps can be used to verify LT between BERT and DUT. |
| 2026-05-21 | Feng Jiang | Reported that the Broadcom document only covered CLI settings and link-training status checks, with no actual function or performance description. |
| 2026-05-22 | Feng Jiang | Reported module-level LT verification on `TP0 -> TP1` and `TP4 -> TP5` using Sian3 BERT and DUT module. |
| 2026-05-25 | Feng Jiang | Reported repeatability checks: convergence time was hard to capture, reads after enabling LT already showed optimized taps, and three runs with the same degraded taps produced nearly the same optimized values. |
| 2026-05-26 | Feng Jiang | Reported temperature-corner checks at case temperatures 0, 45, and 70 C; optimized DSP tap values differed by temperature. |
| 2026-05-26 | Feng Jiang | Responded to the temperature-shift concern with a 10 C to 60 C test: FIR did not update just because temperature and BER changed; disable/enable LT produced a new FIR value. |
| 2026-06-03 | Huirong Liu | Clarified TP4/TP5 feedback direction and stated that both interconnected sides need link training enabled together. |

## Test Setup From Email Body

- Setup named by Feng: Sian3 BERT and DUT module.
- Lane/path cases named in the email: `TP0 -> TP1` and `TP4 -> TP5`.
- Link training was enabled on both BERT and DUT module host side during the polarity recovery procedure.
- The loaded `raw/sources/test-setup-apsu-ilt.png` screenshot shows a temperature chamber containing a Sian3 DUT BERT board with DUT GungnirS module, a Sian3 REF BERT board with REF GungnirS module, `TP0`/`TP1` and `TP4`/`TP5` labeling, and a GoLight VOA in the inter-module path.
- The loaded setup screenshot does not show the configured VOA attenuation, insertion loss, or other quantified channel-loss value.
- Tao later asked whether the BERT setup was high loss because the converged FIR peaking looked small; the fetched body text does not include a direct answer to that high-loss question.

## Loaded Raw Attachment Analysis

Raw files analyzed on 2026-06-09:

- `raw/sources/link_training.7z`: contains `logs_20260522104400.txt`, `logs_20260525084845.txt`, and `logs_20260525093549.txt`.
- `raw/sources/link_training_temperation.7z`: contains `logs_20260525141908_0.txt`, `logs_20260525145654_45.txt`, and `logs_20260525162219_70.txt`.
- `raw/sources/logs_20260522104400.txt`: duplicate standalone copy of the May 22 log in `link_training.7z`.
- `raw/sources/test-setup-apsu-ilt.png`: setup screenshot described above.
- `raw/sources/screencopies/`: 26 PNG screencopies from the Feng verification thread. Two duplicate pairs were observed: `988a30fb-c1a1-46c4-9fbb-2636a95999af.png` / `(1).png`, and `c5b9acd9-124f-466e-90e1-91038bdf3364.png` / `(1).png`.

Common log procedure:

- The script starts from active module/data paths.
- It sets degraded taps on BERT and DUT sides, then confirms the programmed tap readback.
- It measures FEC BER before LT, after enabling the BERT-side LT only, and after enabling DUT LT.
- It reads Sian3 LT status and tap values repeatedly.
- Several logs explicitly disable LT at the end; those after-disable status values should not be interpreted as LT-on failures.
- The logs emit two tap records per lane, but do not label which record is DUT vs REF/BERT endpoint.

Common degraded tap settings:

- Lanes 0 to 3 read back `[0, 0, -7, 50, 0, 0, 0, 0, 0, 0, 0, 0, 0]`.
- Lanes 4 to 7 read back `[-10, 10, 50, 78, 0, 0, 0, 0, 0, 0, 0, 0, 0]`.

### May 22 Numeric Log

`logs_20260522104400.txt` shows:

- Worse-tap pre-FEC BER range before DUT LT: `1.34e-10` to `6.38e-7`.
- BERT-only LT before DUT LT: all parsed BER values were `1.0`, consistent with the later Broadcom statement that interconnected sides need LT enabled together.
- LT-on status after DUT LT: all parsed status records had `training_status = 3`, `apsu_control_state = 7`, `local_rx_ready = 1`, and `remote_rx_ready = 1`.
- LT-on BER range after DUT LT: `0` to `2.49e-12`.
- LT-on tap readback was stable across seven repeated tap snapshots through about `1279 s` of status sampling.

### May 25 Repeatability Numeric Logs

`logs_20260525084845.txt` and `logs_20260525093549.txt` show:

- Worse-tap pre-FEC BER ranges before DUT LT: up to `6.20e-7` and `6.13e-7`.
- BERT-only LT before DUT LT: all parsed BER values were `1.0`.
- LT-on status after DUT LT: all parsed LT-on status records had `training_status = 3`, `apsu_control_state = 7`, `local_rx_ready = 1`, and `remote_rx_ready = 1`.
- LT-on BER ranges after DUT LT: `0` to `2.87e-12` and `0` to `1.60e-12`.
- LT-on tap readback was stable across nine repeated tap snapshots in each run, through about `1631 s` of status sampling.
- After the script disabled LT, status changed to `training_status = 0` and readiness deasserted; this is an expected after-disable condition, not a converged-LT failure.

### Temperature-Corner Numeric Logs

The temperature logs show:

| Log | Case temperature range | Worse-tap BER before DUT LT | LT-on BER after DUT LT | LT-on status |
|---|---:|---:|---:|---|
| `logs_20260525141908_0.txt` | `-0.80` to `0.64 C` | `7.50e-12` to `1.10e-8` | `0` to `1.12e-10` | `training_status = 3`, `apsu_control_state = 7`, local/remote ready |
| `logs_20260525145654_45.txt` | `43.33` to `44.99 C` | `4.63e-11` to `3.17e-7` | `0` to `2.33e-12` | `training_status = 3`, `apsu_control_state = 7`, local/remote ready |
| `logs_20260525162219_70.txt` | `69.70` to `71.72 C` | `1.22e-9` to `4.99e-6` | `0` to `2.66e-12` | `training_status = 3`, `apsu_control_state = 7`, local/remote ready |

Each temperature log showed stable LT-on tap readback across four repeated tap snapshots before the script disabled LT.

### Screencopy Evidence

The loaded screencopies add image-backed evidence for the lab procedure and polarity case:

- `screencopies/3c62193d-53f5-43be-abb9-17227f1a8fd2.png` shows the test script structure: set degraded taps, check BER, enable BERT LT first, enable DUT LT as the start point, then repeat link status, tap, and BER checks before disabling LT.
- `screencopies/93b0341c-19f7-4a0c-b1c2-a29fd7f821ba.png` shows the degraded tap commands used by the script: lanes 0 to 3 use `[0, 0, -7, 50, ...]`; lanes 4 to 7 use `[-10, 10, 50, 78, ...]`.
- `screencopies/fdb5f44b-e217-4978-8c11-573181b15508.png` shows two direct writes, `com.b.twi_pbbw(0x10,0,129,255)` and `com.b.twi_pbbw(0x10,0,137,255)`, followed by BERT and DUT FEC checks reporting `pre_fec_ber = 1.0` and `post_fec_ber = 1.0` on all lanes. This supports the email statement that polarity forcing broke traffic.
- `screencopies/74495e63-68d1-4b3b-92f3-f1538a365d0e.png` and the duplicate `c5b9acd9...` screencopies show LT enable commands for all lanes on both DUT and BERT sides, with successful `lnktrn_en = 1` readback.
- `screencopies/9c85b002-0272-4d85-9391-08a4c81cfb3f.png`, `screencopies/a67ca052-db29-48ae-993d-55ccdb41f755.png`, and `screencopies/e0f49051-e31e-432c-b909-f79ca0e83030.png` show `get_polarity_all(0,255,...)` readbacks where DUT/BERT direction masks change between `15` and `240`. These support that polarity fields changed during the recovery experiment, although the filenames do not provide a complete timestamped before/after sequence.
- The remaining screencopies are visual copies of tap, BER, and LT-status outputs that align with the parsed logs. They do not add a quantified VOA attenuation value, insertion-loss value, Page 70h validation, or customer vendor-CDB transaction trace.

## Procedure: Polarity Optimization

1. Start with traffic passing.
2. Set DUT module `InputPolarityFlipTx` and `OutputPolarityFlipRx` to `255`.
3. Confirm traffic breaks after the polarity change.
4. Enable link training on the BERT and DUT module host side.
5. Observe link-training status becomes `3`.
6. Confirm traffic recovers.
7. Confirm polarity changed for DUT module host Tx and BERT host Tx.

## Result: Polarity Optimization

Feng's conclusion was that link training can correct polarity in both directions.

## Procedure: SI / Tap Optimization

1. Start with traffic passing.
2. Set degraded taps on the module and BERT.
3. Observe worse BER.
4. Enable link training.
5. Observe taps change and BER improves.

## Result: SI / Tap Optimization

Feng's conclusion was that link training can improve DSP taps in both directions. After enabling link training, `training_status` became `3` and DSP taps changed quickly enough that Feng could not measure convergence time using the DSP API.

## Repeatability Findings

- Feng tried reading tap values ten times after enabling link training; each read returned the same tap value.
- Feng ran the script three times with the same degraded taps.
- After enabling link training, optimized values were almost the same, with small differences.
- After disabling link training, taps returned to default values; Feng noted the module DSP taps had small differences.
- Loaded May 25 logs now provide numeric BER, LT status, and repeated tap readback evidence for two repeatability runs. The email still describes three runs, but only two May 25 repeatability logs are currently loaded in `raw/sources/link_training.7z`.

## Temperature-Corner Findings

Feng ran the script at case temperatures 0, 45, and 70 C.

Conclusions from the email body:

- After enabling link training, DSP taps were optimized.
- Convergence time still could not be obtained through the DSP API.
- Optimized DSP tap values were different at the three temperatures.
- Loaded temperature logs now provide numeric BER, LT status, temperature readback, and repeated tap readback evidence for the 0, 45, and 70 C cases.

## Temperature-Shift Retest

Tao and Hock asked what happens if a link is optimized at one temperature and then temperature changes across the range.

Feng's follow-up test:

1. At 10 C, set degraded taps and measure BER around `10e-8`.
2. At 10 C, enable link training and check BER/FIR; BER improved to around `10e-11`.
3. Change case temperature to 60 C and wait about half an hour.
4. Check BER/FIR again; FIR did not change and BER was around `10e-12`.
5. Try changing FIR while link training is enabled; the operation failed with `return_result = 1`.
6. Disable and re-enable link training; FIR changed and BER was around `10e-12`.

Feng's conclusions:

- Link training only optimizes FIR when the first connection succeeds.
- If temperature and BER change later, FIR is not automatically updated.
- User FIR setting is blocked while link training is enabled.
- Disabling and re-enabling link training after a temperature change can produce a new FIR value adjusted for the current temperature.

## Broadcom Clarification

In the June 3 reply, Huirong Liu stated:

- TP5 Tx sets the training pattern to TP4 Rx.
- TP4 feeds back to TP5 through TP4 Tx.
- The same behavior applies for TP4 Tx.
- Interconnected sides need to enable link training together.
- Remaining questions should refer to the application notes.

## Open Evidence Gaps

- Broadcom's older attached LT/ILT procedure has now been loaded and summarized as [broadcom-2025-sian3-ilt-procedure](broadcom-2025-sian3-ilt-procedure.md).
- Feng's loaded logs now provide exact tap arrays, BER ranges, status values, and temperature readback for the May 22, May 25 repeatability, and 0/45/70 C temperature-corner cases.
- Feng's loaded screencopies now provide screenshot-backed evidence for degraded-tap commands, LT enable commands, polarity-forcing traffic break, and polarity readback changes.
- The loaded setup screenshot identifies the chamber, DUT/REF Sian3 BERT boards, DUT/REF GungnirS modules, TP0/TP1 and TP4/TP5 paths, and a GoLight VOA, but it does not capture the actual VOA attenuation or quantified insertion-loss profile.
- The high-electrical-loss condition was requested by the customer and questioned by Tao. The logs show degraded pre-FEC BER up to `4.99e-6` under the forced worse-tap condition, but they still do not prove a quantified physical high-loss channel.
- The May 26 temperature-shift retest is still supported by email body text only; a matching raw log or screenshot for the 10 C to 60 C shift is not currently loaded.
- The polarity-recovery procedure is now supported by email body text plus screencopies. A single ordered, timestamped polarity raw log is still not loaded.
- Convergence time remains unmeasured. The `link training enable time` entries in the logs are repeated status-sampling timestamps after DUT LT enable, not an independent convergence-time measurement.
- The loaded logs do not include customer CMIS Page 70h validation, customer vendor-CDB transaction logs, or interoperability evidence with non-Sian3 partners.

## Vault Implications

- Treat this thread as implementation/lab evidence, not as a normative CMIS or IEEE source.
- It confirms that Sian3 LT/ILT can be demonstrated at module level through polarity recovery and DSP tap/BER improvement.
- It also shows a host diagnostic caveat: link training may not continuously re-optimize FIR after environmental changes unless LT is restarted.
