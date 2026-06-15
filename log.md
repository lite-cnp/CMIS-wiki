# Research Log

## 2026-06-12 concept | MPI calibration for module vendors

- Added [mpi-calibration-module-vendor](concepts/mpi-calibration-module-vendor.md), covering lab setup, data collection, model fitting, verification, and production reporting for calibrated `mpi_metrics` and `mpi_metrics_mpicoff`.
- Updated [multipath-interference-mpi-metrics](concepts/multipath-interference-mpi-metrics.md) and [index](index.md) with the new calibration entry.

## 2026-06-12 synthesis | MPI customer requirements from email

- Added [mpi-customer-requirements-from-email](synthesis/mpi-customer-requirements-from-email.md), synthesizing MSFT VDM/CDB MPI requirements, Broadcom `mpi_metric` interpretation, MPICAN validation questions, ZFR8 MPI test-setting concerns, and VM8/Gungnir-S validation themes from Outlook evidence.
- Updated [multipath-interference-mpi-metrics](concepts/multipath-interference-mpi-metrics.md) with a link to the customer-requirements overlay.
- Updated [index](index.md) with the new synthesis.

## 2026-06-12 ingest | Broadcom MPI Metrics Feature application note

- Added [broadcom-2025-mpi-metrics-feature](sources/broadcom-2025-mpi-metrics-feature.md), summarizing the password-protected Broadcom `87XXX-85XXX-83XXX-AN100.pdf` application note for MPI metrics and optical dust detection.
- Added [multipath-interference-mpi-metrics](concepts/multipath-interference-mpi-metrics.md), defining `mpi_metrics`, `mpi_metrics_mpicoff`, the MPIC-live-traffic rule, and the boundary between vendor cAPI diagnostics and CMIS/VDM exposure.
- Added [how-should-hosts-use-broadcom-mpi-metrics](queries/how-should-hosts-use-broadcom-mpi-metrics.md), capturing host guidance for enabling `mpi_include`, reading per-lane values, and avoiding threshold/standardization overclaims.
- Updated [index](index.md), [cmis-document-family-map](synthesis/cmis-document-family-map.md), [vendor-specific-cmis-customizations](concepts/vendor-specific-cmis-customizations.md), and [versatile-diagnostics-monitoring](concepts/versatile-diagnostics-monitoring.md) with the new source and concept.

## 2026-06-11 query | What CDB command 0045h is for

- Added [what-is-cdb-command-0045h-for](queries/what-is-cdb-command-0045h-for.md), explaining that `CMD 0045h` discovers externally defined or supplement-defined CDB command sets, with current practical use as the CMIS-VCS support bit before `4000h`/`4001h`/`4002h`.
- Noted the CMIS 5.3 `0045h` table typo where the `CMDID` row says `0043h`; CMIS 5.4 fixes the row.
- Updated [index](index.md) with the saved query.

## 2026-06-11 query | CMIS CDB command table errata candidates

- Added [cmis-cdb-command-table-errata](queries/cmis-cdb-command-table-errata.md), a table-consistency audit of CMIS 5.3/5.4 CDB command definitions.
- Captured likely CDB table mistakes including CMIS 5.4 `0005h` check code, `0006h` command-data range overlap, CMIS 5.3 `0045h` CMDID typo, CMIS 5.4 query-bitmap offset formulas, `0051h` reply layout/length issues, `0100h` reply-header references and Fixed/Factory load range typo, CMIS 5.4 `010Bh`/`010Ch`/`010Dh` length conflicts, and `0290h` command-data range overlap.
- Updated [index](index.md) with the saved errata query.

## 2026-06-11 query | Security-related CDB commands

- Added [security-related-cdb-commands](queries/security-related-cdb-commands.md), summarizing the CMIS `0400h-04FFh` security CDB command group for IDevID certificate retrieval, challenge digest signing, signature retrieval, advertised capabilities, detailed statuses, and LPL/EPL usage.
- Noted that `0001h` Enter Password and `0002h` Change Password are security-adjacent CDB password commands, but not part of the `0400h-04FFh` Security Features authentication command group.
- Added a `CMD 0044h` format audit: CMIS 5.3's `RPLLength = 50` conflicts with the `9Fh:136-187` reply field range and should be treated as `52`; CMIS 5.4 fixes that length but appears to omit the `0400h` base offset in the command-support bitmap byte-index formula.
- Updated [index](index.md) to include the saved query.

## 2026-06-10 synthesis | Page 70h low-level reuse model

- Added the `Reusable Diagnostic Harness` glossary term to [CONTEXT](CONTEXT.md) to separate setup/diagnostic reuse from the formal Page 70h pass/fail interface.
- Updated [apsu-ilt-page70h-verification-plan](synthesis/apsu-ilt-page70h-verification-plan.md) with a low-level resource reuse model covering current CMIS host/exerciser access, Sian3 BERT/DUT setup, Python debug wrappers, vendor CDB helpers, traffic/FEC helper calls, and existing degraded-tap/polarity procedure seed material.
- Added evidence-package requirements for reused harness script/tool revision, function or command list, and evidence role.
- Added the `Low-Level Verification Primitive` glossary term and a reusable primitive catalog for run metadata, Page 70h mapping, permissions, control acceptance, status polling, FEC recovery, diagnostic Sian3 link-training state, vendor CDB coexistence, precode, fault setup, and evidence packaging.
- Added the `Primitive Requirement Class` glossary term and primitive activation rules for mandatory core, conditional, and diagnostic-only primitive usage.
- Added the `Low-Level Test-Case Sheet` glossary term and a sheet template for execution-level row expansion without widening the main matrix.
- Added the `Mapping-First Execution Order` glossary term and the first concrete low-level sheet, `BR-005`, for freezing and verifying the Page 70h-to-lab lane mapping manifest before lane-specific results are accepted.
- Added the `Coexistence-First Control Validation` glossary term and the `BR-006` low-level sheet for ordered mixed-session Page 70h/vendor CDB coexistence before nominal APSU enable/disable is accepted.
- Added the `Invalid-Write Rule Freeze` glossary term and the `BR-007` low-level sheet separating CMIS reserved-field behavior from non-reserved invalid-control behavior before byte-map and control tests execute.
- Added the `Control Acceptance Timeout Freeze` glossary term and the `BR-008` low-level sheet for freezing timeout values and confirmation methods before command-driven Page 70h tests execute.
- Added the `Page 70h Byte-Map Foundation` glossary term and paired low-level sheets `P70H-001` and `P70H-002` for implemented byte ranges, access permissions, reserved bytes, reserved bits, and side-effect checks.
- Added the `Non-Reserved Invalid Control Test` glossary term and the `P70H-003` low-level sheet for unsupported controls, invalid lane masks, unsupported applications, invalid side/lane combinations, and state-dependent invalid writes.
- Added the `Active Mapping Validation` glossary term and the `P70H-004` low-level sheet for proving the frozen mapping manifest with safe Page 70h behavior plus fixture and traffic/FEC correlation.
- Added the `Changing-State Coherency Test` glossary term and the `P70H-005` low-level sheet for stable and changing-state multi-byte Page 70h monitor/status coherency validation.
- Added the `Management-Status Latency Test` glossary term and the `P70H-006` low-level sheet separating Page 70h status publication latency from APSU/iLT control-to-traffic-recovery timing.
- Added the `Complete Ethernet-Interface Enablement` glossary term and the `APSU-001` low-level sheet for nominal Page 70h APSU/iLT enable/disable across the full enabled lane set.
- Added the `Data-Ready Evidence Pair` glossary term and the `APSU-002` low-level sheet requiring both Page 70h readiness/status and external traffic/FEC evidence for data-ready APSU state.
- Added the `Readiness Ordering Test` glossary term and the `APSU-003` low-level sheet for Page 70h RTS, local ready, remote ready, and path-up/readiness status ordering.
- Added the `Page 70h Exposure Gate` glossary term and the `APSU-004` low-level sheet for training pattern control/readback only when exposed through Page 70h or tied to a customer-facing claim.
- Added the `Precode Exposure Test` glossary term and the `APSU-005` low-level sheet for Page 70h precode request/readback, with vendor CDB `CMDA082h`/`CMDA083h` limited to correlation or coexistence evidence.
- Added the `Degraded-Tap Recovery Proof` glossary term and the `APSU-006` low-level sheet reusing Feng's degraded-tap procedure as setup while keeping Page 70h status and traffic/FEC BER improvement as formal evidence.
- Added the `Bundled Restart Proof` glossary term and the `APSU-007` low-level sheet treating the complete Ethernet interface lane set as the default Sian3 restart domain.
- Added the `STR-001` low-level sheet for quantified high-loss or bounded lab-observed attenuation validation using current VOA/loss resources without overstating uncalibrated loss evidence.
- Added the `Convergence-Time Test` glossary term and the `STR-002` low-level sheet for formal control-to-traffic-recovery timing using Page 70h control acceptance as start and external traffic/FEC recovery as stop.
- Added the `Polarity Recovery Exposure Test` glossary term and the `STR-003` low-level sheet requiring ordered polarity recovery evidence when Page 70h exposes polarity behavior or a customer claim depends on it.
- Added the `Repeat Degraded-Tap Recovery Set` glossary term and the `STR-004` low-level sheet requiring three Page 70h-triggered degraded-tap recovery runs with labeled endpoints and before/after traffic/FEC evidence.
- Added the `Stable Release Temperature Validation` glossary term and the `STR-005` low-level sheet requiring measured module case-temperature stabilization, Page 70h status/control evidence, and traffic/FEC evidence at frozen release temperature points.
- Added the `STR-006` low-level sheet for conditional active temperature-shift validation only when Page 70h exposure or customer/release claims make transition behavior in scope.
- Added the `Non-LT-Frame Partner Behavior` glossary term and the `STR-007` low-level sheet as conditional implementation-reference coverage gated by Page 70h exposure or customer claim.
- Added the `Partner Fault Trigger` glossary term and the `STR-008` low-level sheet for partner squelch/signal-loss behavior when it affects Page 70h readiness or recovery.
- Added the `Recovery Counter Exposure Test` glossary term and the `STR-009` low-level sheet for Page 70h recovery reason/event count first-read and read-clear behavior.
- Added the `Slicer/Timer Characterization` glossary term and the `STR-010` low-level sheet, diagnostic-only by default unless Page 70h exposure or claim wording promotes it to formal validation.
- Added the `Bounded Link-Partner Interop Claim` glossary term and the `INT-001` low-level sheet for non-Sian3 partner interoperability, bounded to the tested partner identity/class when broader partner coverage is not available.
- Added the `Bounded Host-Management Interop Claim` glossary term and the `INT-002` low-level sheet for Page 70h host/exerciser/scripted-profile interoperability, bounded to the covered profile or setup class when a real customer host stack is not tested.
- Added the `Page 70h To Sian3 Diagnostic Correlation` glossary term and the `INT-003` low-level sheet, keeping Sian3 cAPI, debug CDB, and vendor CDB comparison diagnostic-only and unable to override formal Page 70h results.
- Added the `Evidence Package Completeness Audit` glossary term and the `INT-004` low-level sheet for Gate 5 artifact completeness, raw evidence traceability, customer-safe excerpt review, and internal-debug evidence separation.
- Added the `Final Release Decision Summary` glossary term and the `INT-005` low-level sheet for status-label-only release decisions, bounded release notes, intentionally unclaimed items, blocked items, and claim-to-evidence traceability.
- Aligned the primitive catalog and primitive activation rules with `INT-001` through `INT-005`, including interop mapping, host permission/control/polling, conditional traffic/FEC evidence, diagnostic Sian3 correlation, and release-review evidence packaging.
- Updated [index](index.md) to describe the Page 70h verification plan as including low-level test-case sheets.

## 2026-06-10 synthesis | APSU/iLT verification report edit

- Reworked [apsu-ilt-verification-report](synthesis/apsu-ilt-verification-report.md) into a tighter customer-safe verification report with clearer sections for current interface, standards/vendor baseline, evidence coverage, open gaps, validation actions, and traceability.
- Incorporated the Sian3 source-code recheck by treating `remote_tf_lock`, remote TP/MC mode status, and the main APSU timers as covered by source while keeping remaining exact IEEE variable exposure gaps explicit.
- Updated [index](index.md) to describe the report as customer-safe evidence-boundary guidance rather than a general status dump.

## 2026-06-10 synthesis | Page 70h verification plan hardening

- Added [CONTEXT](CONTEXT.md) as the CMIS APSU/iLT validation glossary used to define formal pass/fail, bounded evidence, status labels, freeze checklist, and raw-evidence traceability terms.
- Updated [apsu-ilt-page70h-verification-plan](synthesis/apsu-ilt-page70h-verification-plan.md) with the pre-execution freeze checklist, reviewer sign-off/change control, Page 70h status-label rules, control-acceptance confirmation, host access profile, mapping manifest, bounded interop/high-loss/temperature claims, and raw evidence retention requirements.
- Added [ADR 0001 Page 70h and Vendor CDB Coexistence](docs/adr/0001-page70h-and-vendor-cdb-coexistence.md), recording that Page 70h and vendor CDB coexist as ordered CMIS I2C-MCI transactions over one shared effective APSU/iLT state.

## 2026-06-10 query | IEEE APSU/iLT fields missing from Sian3 cAPI

- Added [ieee-apsu-ilt-fields-missing-from-sian3-capi](queries/ieee-apsu-ilt-fields-missing-from-sian3-capi.md), comparing IEEE P802.3dj Annex 178B management variables against the documented Broadcom Sian3 APSU cAPI fields.
- Identified missing or partial Sian3 cAPI exposure for `mr_restart`, reset variables, training-pattern identifiers/seeds, `remote_tf_lock`, `isl_ready`, `training_failure`, `uses_recovered_clock`, and direct host-set access to initial-condition/coefficient request fields.
- Confirmed Sian3 cAPI covers the main enablement/status/readiness/recovery/timer path, including `lnktrn_en`, `apsu_en`, `apsu_control_state`, `training_status`, RTS/readiness bits, `polarity_correction`, `recovery_event_count`, and the main Annex 178B timers.
- Rechecked against `C:/Users/huy82684/projects/1p6_sian3_fw_h5` source via CodeGraph and literal search. Corrected `remote_tf_lock` to covered in `link_training_status_t`, noted source-only coverage for `remote_tp_mode` and `remote_mc_mode`, and separated public cAPI gaps from lite-CDB/debug packet fields such as `mr_restrt`, `identifier_i`, `prbs13_seed_i`, and `prbs31_seed_i`.

## 2026-06-10 query | Standard APSU/iLT procedure and link-side comparison

- Added [standard-apsu-ilt-procedure-host-vs-media-links](queries/standard-apsu-ilt-procedure-host-vs-media-links.md), summarizing IEEE P802.3dj/D2.3 Annex 178B APSU/RTS/ILT functional flow from the local raw draft.
- Compared host-side AUI/PMA-style links and media-side PMD links: same Annex 178B state-machine model, different interface object, medium, training format, and CMIS entry point.
- Updated [ieee-p802-3dj-d2-3](sources/ieee-p802-3dj-d2-3.md) to note the local raw PDF and add APSU/iLT link anchors.

## 2026-06-10 query | Sian3 APSU/iLT conflict audit

- Added [sian3-behavior-conflicts-with-802-3dj-apsu-ilt](queries/sian3-behavior-conflicts-with-802-3dj-apsu-ilt.md), concluding that the vault records no direct Sian3-vs-802.3dj APSU/iLT standards conflict.
- Classified the active risks as Page 70h/interface gaps, unverified path-level conformance, non-Sian3 interoperability gaps, and customer-claim-sensitive Sian3 behaviors such as bundled restart, restart-based FIR optimization, and vendor cAPI-only status.

## 2026-06-09 synthesis | APSU/iLT Page 70h verification plan

- Added [apsu-ilt-page70h-verification-plan](synthesis/apsu-ilt-page70h-verification-plan.md), an internal engineering validation plan for next-release CMIS Page 70h APSU/iLT support.
- Captured release gates, formal Page 70h pass/fail rules, evidence requirements, detailed test matrix, and mitigation coverage for the current IEEE/OIF/Sian3 verification gaps.

## 2026-06-09 synthesis | APSU/iLT verification report

- Added [apsu-ilt-verification-report](synthesis/apsu-ilt-verification-report.md), reporting current APSU/iLT implementation status, lab verification evidence, and gaps for the 1.6T 2xDR4 FRO module.
- Captured status labels across current vendor CDB support, planned CMIS Page 70h alignment, Sian3 lab evidence, implementation gaps, and verification evidence gaps.

## 2026-06-09 ingest | Feng Sian3 link-training screencopies

- Updated [feng-jiang-2026-sian3-link-training-verification-email-thread](sources/feng-jiang-2026-sian3-link-training-verification-email-thread.md) with analysis of `raw/sources/screencopies/`.
- Reclassified polarity evidence from email-only to email plus screencopy-backed evidence: polarity forcing broke traffic, LT was enabled on DUT/BERT lanes, and polarity readback masks changed.
- Kept high-loss proof, convergence-time measurement, May 26 temperature-shift raw log/screenshot, third repeatability raw log, Page 70h validation, and interoperability closure as remaining gaps.

## 2026-06-09 ingest | Feng Sian3 link-training raw attachments

- Updated [feng-jiang-2026-sian3-link-training-verification-email-thread](sources/feng-jiang-2026-sian3-link-training-verification-email-thread.md) with analysis of `raw/sources/link_training.7z`, `raw/sources/link_training_temperation.7z`, `raw/sources/logs_20260522104400.txt`, and `raw/sources/test-setup-apsu-ilt.png`.
- Captured numeric BER, LT status, repeated tap readback, and 0/45/70 C temperature-corner evidence from the loaded logs.
- Reclassified remaining gaps: quantified physical high-loss setting, convergence-time measurement, May 26 temperature-shift raw log/screenshot, polarity-recovery raw log/screenshot, third repeatability raw log, endpoint labeling for duplicate tap records, Page 70h validation, and interoperability closure.

## 2026-06-09 ingest | Current APSU/iLT customer-note plan

- Added [lumentum-2026-8023dj-apsu-ilt-support-plan](sources/lumentum-2026-8023dj-apsu-ilt-support-plan.md), summarizing the current APSU/iLT implementation status from `raw/sources/8023dj_apsu_ilt_cmis_slides.pptx` and the matching PDF customer-note export.
- Added [lumentum-2026-dpsm-apsu-ilt-state-machine](sources/lumentum-2026-dpsm-apsu-ilt-state-machine.md), extracting the embedded draw.io state-machine model from `raw/sources/dpsm-apsu-ilt-state-machine.drawio.png`.
- Added [apsu-ilt-customer-note-plan](synthesis/apsu-ilt-customer-note-plan.md), capturing the customer-note position: vendor CDB implemented today, CMIS Page 70h planned after validation closure, and `DPActivated` is not sufficient for live Ethernet DATA readiness.
- Updated APSU, vendor-specific customization, state-machine query, Sian3 cAPI query, document-family map, and `wiki/index.md` navigation for the current implementation plan.

## 2026-06-09 ingest | Obsolete Sian3 ILT procedure attachment

- Added [broadcom-2025-sian3-ilt-procedure](sources/broadcom-2025-sian3-ilt-procedure.md), summarizing `raw/sources/Sian3_ILT_AN.pdf` as an obsolete Broadcom Sian3 ILT BERT/DUT procedure source.
- Marked the 2025 ILT procedure as superseded by [broadcom-2026-sian3-apsu-application-notes](sources/broadcom-2026-sian3-apsu-application-notes.md), which has later firmware scope and current APSU terminology.
- Updated [feng-jiang-2026-sian3-link-training-verification-email-thread](sources/feng-jiang-2026-sian3-link-training-verification-email-thread.md), [how-should-hosts-use-sian3-apsu-capi](queries/how-should-hosts-use-sian3-apsu-capi.md), [autonomous-path-startup](concepts/autonomous-path-startup.md), [vendor-specific-cmis-customizations](concepts/vendor-specific-cmis-customizations.md), [cmis-document-family-map](synthesis/cmis-document-family-map.md), and `wiki/index.md` to classify the attachment correctly.

## 2026-06-09 ingest | Feng Jiang Sian3 link-training verification email thread

- Added [feng-jiang-2026-sian3-link-training-verification-email-thread](sources/feng-jiang-2026-sian3-link-training-verification-email-thread.md), summarizing the Outlook thread `Sian3 DSP Link Training Verification` with body-level evidence for BERT/DUT setup, polarity recovery, SI/tap optimization, repeatability, and temperature behavior.
- Updated [how-should-hosts-use-sian3-apsu-capi](queries/how-should-hosts-use-sian3-apsu-capi.md), [broadcom-2026-sian3-apsu-application-notes](sources/broadcom-2026-sian3-apsu-application-notes.md), [autonomous-path-startup](concepts/autonomous-path-startup.md), and `wiki/index.md` to link the email-derived verification evidence.
- Noted that Outlook exposed attachment presence and inline screenshot references, but the available connector tools did not expose attachment file contents.

## 2026-06-09 ingest | Broadcom Sian3 APSU application note

- Added [broadcom-2026-sian3-apsu-application-notes](sources/broadcom-2026-sian3-apsu-application-notes.md), a vendor-specific source page for `raw/sources/Sian3 APSU Application Notes_Customer_Release.pdf`.
- Added [how-should-hosts-use-sian3-apsu-capi](queries/how-should-hosts-use-sian3-apsu-capi.md), a host bring-up analysis for Sian3 APSU cAPI readiness and diagnostics.
- Updated [autonomous-path-startup](concepts/autonomous-path-startup.md), [how-do-apsu-and-cmis-state-machines-interact](queries/how-do-apsu-and-cmis-state-machines-interact.md), [vendor-specific-cmis-customizations](concepts/vendor-specific-cmis-customizations.md), [cmis-document-family-map](synthesis/cmis-document-family-map.md), and `wiki/index.md` so the Broadcom source is classified as vendor-specific implementation material.

## 2026-05-26 query | CMIS-VCS register-map pages

- Added [upper-page-18h-register-map](concepts/upper-page-18h-register-map.md), a CMIS-VCS staged Control Set overflow page with an embedded C register-view struct.
- Added [upper-page-19h-register-map](concepts/upper-page-19h-register-map.md), a CMIS-VCS active Control Set overflow page with an embedded C register-view struct.
- Updated CMIS-VCS, Control Set, CDB, supplement, memory-map, source, and index navigation so the VCS overflow pages are GitHub-navigable.

## 2026-05-26 query | CMIS upper-page embedded C views

- Replaced header-only C Register View snippets on the CMIS 5.4 upper-page register-map pages with self-contained embedded C views so the structs, bitfields, enums, and static assertions are visible directly in Obsidian.
- Applied the inline C view pattern to Pages 00h, 01h, 02h, 04h, 10h, 11h, 12h, 13h, 14h, and 2Fh; Page 0Dh was already generated in that format.

## 2026-05-26 query | CMIS Page 0Dh register map

- Added [upper-page-0dh-register-map](concepts/upper-page-0dh-register-map.md), a CMIS 5.4 firmware-management page covering Page 0Dh capabilities, load status, and firmware load version descriptors.
- Extended [cmis-5-4-upper-page-registers.h](code/cmis-5-4-upper-page-registers.h) with Page 0Dh bitfield/register views, firmware load descriptor structs, and common firmware status code enums.
- Embedded the Page 0Dh C register view directly in the Markdown page so the struct and bitfields are visible in Obsidian.
- Updated [management-memory-map](concepts/management-memory-map.md) and `wiki/index.md` to link Page 0Dh directly.

## 2026-05-26 query | CMIS upper-page C bitfields

- Added [cmis-5-4-upper-page-registers.h](code/cmis-5-4-upper-page-registers.h), a detailed little-endian ARM-oriented C header with named bitfields, enums, byte-order wrappers, and static offset/size assertions for Pages 00h, 01h, 02h, 04h, 10h, 11h, 12h, 13h, 14h, and 2Fh.
- Updated the upper-page register-map pages with detailed bitfield/register definitions instead of only abstract byte-array overlays.

## 2026-05-26 query | GitHub-navigable wiki links

- Converted internal wiki cross-references from Obsidian wikilinks to GitHub-navigable relative Markdown links.
- Updated contributor guidance in `AGENTS.md` and `README.md` to keep future internal links GitHub-compatible.

# 2026-06-15 synthesis | I3C analyzer candidate inventory

- Added [i3c-analyzer-candidate-inventory](synthesis/i3c-analyzer-candidate-inventory.md) to normalize the exact vendor products mentioned in the email thread.
- Updated [index](index.md) with the analyzer inventory entry.

# 2026-06-15 clarification | I3C analyzer ownership mapping

- Updated [i3c-analyzer-candidate-inventory](synthesis/i3c-analyzer-candidate-inventory.md) with the confirmed owner-to-product mapping: `SC4420` for ADI recommendation, `Introspect` for Taiwan, `Prodigy` for Hong Kong, `Easyi3C` for your search, and `Keysight` for Hua Zhang's query.
- Aligned [huabin-he-2026-i3c-host-adapter-candidates](sources/huabin-he-2026-i3c-host-adapter-candidates.md) and [i3c-host-adapter-decision](synthesis/i3c-host-adapter-decision.md) to point at the inventory page.

# 2026-06-15 roadmap | CMIS over I3C execution order

- Reworked [cmis-over-i3c-roadmap](synthesis/cmis-over-i3c-roadmap.md) to start with `M45x/S` EVB bring-up, validate against `Introspect` and `SC4420`, then move to `STM32H563/573` bridging, I3C-MCI conformance, and transparent bridging to approved in-module DSP targets.
- Added explicit access-control scope for the transparent-bridge extension and linked the roadmap to the analyzer inventory page.

# 2026-06-15 synthesis | I3C host adapter decision

- Added [i3c-host-adapter-decision](synthesis/i3c-host-adapter-decision.md) to turn the adapter candidate discussion into a recommended lab/prod path.
- Linked the synthesis from [index](index.md).

# 2026-06-15 ingest | I3C host adapter candidates

- Added [huabin-he-2026-i3c-host-adapter-candidates](sources/huabin-he-2026-i3c-host-adapter-candidates.md) from the I3C bring-up thread family.
- Added [i3c-host-adapter-candidate-vs-public-baseline](comparisons/i3c-host-adapter-candidate-vs-public-baseline.md) to link the internal adapter options with public MIPI I3C references.
- Updated [cmis-over-i3c-roadmap](synthesis/cmis-over-i3c-roadmap.md) with the adapter candidate direction.

# 2026-06-15 comparison | MIPI I3C Basic v1.1.1 vs v1.2

- Added [mipi-i3c-basic-v1-1-1-vs-v1-2](comparisons/mipi-i3c-basic-v1-1-1-vs-v1-2.md) to capture the public baseline-versus-recommended-version distinction for I3C Basic.
- Linked the comparison from [index](index.md).

# 2026-06-15 clarification | I3C Basic baseline vs target version

- Added explicit wording to the I3C MCI concept and CMIS-over-I3C roadmap that treats uploaded `I3C Basic v1.1.1` as the vault baseline and `v1.2` as the external target version.

# 2026-06-15 browser + ingest | MIPI I3C FAQ review

- Re-checked the public MIPI I3C FAQ and confirmed that `I3C Basic` is public, while MIPI recommends `I3C v1.2` / `I3C Basic v1.2` as the newest recommended versions.
- Updated the public FAQ source page, the I3CMCI concept page, and the CMIS-over-I3C roadmap to treat the uploaded `v1.1.1` file as the local baseline reference.

# 2026-06-15 ingest | MIPI I3C Basic v1.1.1 spec

- Added [mipi-i3c-basic-v1-1-1](sources/mipi-i3c-basic-v1-1-1.md) from `CMIS/raw/sources/I3CMCI/I3C_MIPI-v1.1.1.pdf`.
- Updated [i3c-based-management-communication-interface](concepts/i3c-based-management-communication-interface.md) and [management-communication-interface](concepts/management-communication-interface.md) to treat the uploaded Basic spec as the local public normative baseline.
- Updated [index](index.md) with the new primary I3C Basic source page.

# 2026-06-15 ingest | MIPI I3C Basic FAQ

- Downloaded the public `MIPI-I3C-Basic-FAQ-v1-1-1-public.pdf` companion document into `raw/sources/I3CMCI/`.
- Added [mipi-i3c-basic-faq-v1-1-1](sources/mipi-i3c-basic-faq-v1-1-1.md) as the public FAQ companion to the gated I3C Basic spec.

# 2026-06-15 ingest | MIPI public I3C references

- Added source pages for the downloaded public MIPI I3C files under `raw/sources/I3CMCI/`.
- Linked the new MIPI sources into [index](index.md) and the CMIS-over-I3C roadmap context.

# 2026-06-15 synthesis | CMIS over I3C roadmap

- Added [cmis-over-i3c-roadmap](synthesis/cmis-over-i3c-roadmap.md) to unify the draft I3CMCI text, the firmware role note, and the provisional bring-up schedule.
- Updated [index](index.md) with the roadmap synthesis entry.

# 2026-06-15 ingest | I3C bring-up schedule planning email

- Added [huabin-he-2026-i3c-bringup-schedule-planning](sources/huabin-he-2026-i3c-bringup-schedule-planning.md) from the Huabin He Outlook thread.
- Added [what-is-the-current-i3c-bringup-schedule](queries/what-is-the-current-i3c-bringup-schedule.md) to preserve the draft phase plan without freezing the schedule.
- Updated [index](index.md) with the new source and query pages.

# 2026-06-15 query | CMIS over I3C implementation decisions

- Added [what-implementation-decisions-does-cmis-over-i3c-require](queries/what-implementation-decisions-does-cmis-over-i3c-require.md) to capture the engineering decisions implied by the uploaded role note.
- Linked the query from [index](index.md) so the CMIS-over-I3C work is discoverable from the wiki landing page.

# 2026-06-15 ingest | CMIS over I3C role note

- Added [oif2026-057-01-firmware-functional-design-authority-cmis-over-i3c](sources/oif2026-057-01-firmware-functional-design-authority-cmis-over-i3c.md) from `CMIS/raw/sources/oif2026.057.01.docx`.
- Added [cmis-over-i3c-firmware-architecture](concepts/cmis-over-i3c-firmware-architecture.md) to capture the implementation architecture implied by the role note.
- Updated [i3c-based-management-communication-interface](concepts/i3c-based-management-communication-interface.md) and [management-communication-interface](concepts/management-communication-interface.md) with the implementation-oriented delta.

# 2026-06-15 ingest | Broadcom AN100 upload refresh

- Confirmed `CMIS/raw/sources/87XXX-85XXX-83XXX-AN100.pdf` as the raw Broadcom MPI metrics application note upload.
- Noted that `CMIS/raw/sources/87XXX-85XXX-83XXX-AN100_.pdf` is a zero-byte duplicate upload.
- Refreshed the Broadcom AN100 source page and the MPI metrics concept page metadata to reflect the current raw upload.

## 2026-05-26 query | CMIS 5.4 upper-page register maps

- Added upper-memory register-map pages for [upper-page-00h-register-map](concepts/upper-page-00h-register-map.md), [upper-page-01h-register-map](concepts/upper-page-01h-register-map.md), [upper-page-02h-register-map](concepts/upper-page-02h-register-map.md), [upper-page-04h-register-map](concepts/upper-page-04h-register-map.md), [upper-page-10h-register-map](concepts/upper-page-10h-register-map.md), [upper-page-11h-register-map](concepts/upper-page-11h-register-map.md), [upper-page-12h-register-map](concepts/upper-page-12h-register-map.md), [upper-page-13h-register-map](concepts/upper-page-13h-register-map.md), [upper-page-14h-register-map](concepts/upper-page-14h-register-map.md), and [upper-page-2fh-register-map](concepts/upper-page-2fh-register-map.md).
- Embedded page-local C register-view structs for the requested pages, using explicit byte arrays or CMIS big-endian wrappers so the layouts are safe on little-endian ARM targets.
- Updated [management-memory-map](concepts/management-memory-map.md) and `wiki/index.md` with links to the new upper-page maps.

## 2026-05-26 query | CMIS 5.4 lower memory register map

- Added [low-memory-register-map](concepts/low-memory-register-map.md) with a detailed CMIS 5.4 Lower Memory overview, implementation notes, and an embedded packed C register-view struct modeled after generated CMIS C headers.
- Updated `wiki/index.md` and [management-memory-map](concepts/management-memory-map.md) to include the new lower-memory concept page.
- Refined the embedded C struct member names to use CMIS-style CamelCase identifiers.
- Corrected the embedded C struct for little-endian ARM use by replacing native multi-byte monitor/password fields with explicit CMIS big-endian byte wrappers and offset assertions.

## 2026-05-25 ingest | CMIS 5.4 and document family update

- Added [oif-cmis-05-4](sources/oif-cmis-05-4.md) as the current base CMIS source page.
- Added OIF supplement source pages for [oif-cmis-vcs-01-1](sources/oif-cmis-vcs-01-1.md), [oif-cmis-ff-01-0](sources/oif-cmis-ff-01-0.md), and [oif-c-cmis-01-4](sources/oif-c-cmis-01-4.md).
- Added [oif-elsfp-cmis-01-0](sources/oif-elsfp-cmis-01-0.md) and modeled [elsfp-cmis](concepts/elsfp-cmis.md) as a standalone companion IA for ELSFP resource modules.
- Added draft source pages for [oif2026-057-01-i3cmci-draft](sources/oif2026-057-01-i3cmci-draft.md) and [oif2026-093-08-802-3dj-apsu-draft](sources/oif2026-093-08-802-3dj-apsu-draft.md).
- Added IEEE reference stubs for [ieee-802-3-2022](sources/ieee-802-3-2022.md) and [ieee-p802-3dj-d2-3](sources/ieee-p802-3dj-d2-3.md).
- Added a vendor-specific source stub for [google-gmis-imdd-transceiver-customizations](sources/google-gmis-imdd-transceiver-customizations.md) with extraction caveats.
- Updated navigation, supplement, memory-map, MCI, control-set, DPSM, NPSM, and implementer-map pages for the new source set.

## 2026-05-25 ingest | OIF-CMIS-05.3

- Generated first substantive wiki pass from `raw/sources/OIF-CMIS-05.3.pdf`.
- Added source, entity, concept, comparison, synthesis, and query pages for the actual OIF Common Management Interface Specification domain.
- Corrected earlier starter content that conflated OIF CMIS with unrelated OASIS content-management CMIS.
- Updated `wiki/index.md` and `wiki/overview.md` as navigation entry points.

## 2026-05-21

- Project created.
- Saved query page `thinkwe-need-to-answer-the-user-they-said-yes-to-m-2026-05-21-073851.md`.

## 2026-05-21 ingest | Legacy starter guide

- Imported the initial spec-to-wiki transformation guide.

# 2026-06-15 roadmap correction | STM32H563-first I3C bring-up

- Updated [cmis-over-i3c-roadmap](synthesis/cmis-over-i3c-roadmap.md) after the Huabin follow-up discussion: Phase 1 and Phase 2 now start on available `STM32H563` EVBs because the ST I3C controller/target packages and examples are more mature, then migrate the validated behavior to `M45x/S`.
- Updated [huabin-he-2026-i3c-bringup-schedule-planning](sources/huabin-he-2026-i3c-bringup-schedule-planning.md) and [what-is-the-current-i3c-bringup-schedule](queries/what-is-the-current-i3c-bringup-schedule.md) so future schedule answers reflect the STM32-first decision.
- Updated [index](index.md) to describe the current roadmap as STM32H563-first with later M45x/S migration.

# 2026-06-15 schedule update | I3C bring-up review version

- Expanded [what-is-the-current-i3c-bringup-schedule](queries/what-is-the-current-i3c-bringup-schedule.md) into a reviewable phase schedule with entry conditions, exit gates, phase details, and external links for ST EVBs, STM32CubeH5, MIPI I3C, Introspect, and SC4420.
- Updated [index](index.md) so the schedule entry describes the STM32H563-first plan and migration gates.

# 2026-06-15 scope clarification | I3CMCI subset vs MIPI I3C feature set

- Added [i3cmci-required-subset-vs-mipi-i3c-feature-set](comparisons/i3cmci-required-subset-vs-mipi-i3c-feature-set.md) to record that the baseline is I3CMCI over conformant MIPI I3C controller/target behavior for the subset I3CMCI uses, not the full MIPI I3C v1.1.1/v1.2 feature set.
- Updated [cmis-over-i3c-roadmap](synthesis/cmis-over-i3c-roadmap.md), [i3c-based-management-communication-interface](concepts/i3c-based-management-communication-interface.md), [oif2026-057-01-firmware-functional-design-authority-cmis-over-i3c](sources/oif2026-057-01-firmware-functional-design-authority-cmis-over-i3c.md), [what-is-the-current-i3c-bringup-schedule](queries/what-is-the-current-i3c-bringup-schedule.md), and [mipi-i3c-basic-v1-1-1-vs-v1-2](comparisons/mipi-i3c-basic-v1-1-1-vs-v1-2.md) to link the scope boundary.

# 2026-06-15 schedule proposal | 12-week I3C-MCI bring-up

- Added [i3c-bringup-12-week-schedule-proposal](synthesis/i3c-bringup-12-week-schedule-proposal.md), consolidating the STM32-first plan, I3C-MCI subset scope, analyzer path, M45x/S migration, and Week 12 readiness review into a detailed technical schedule.
- Updated [index](index.md) to surface the 12-week schedule proposal from Start Here and Synthesis.

# 2026-06-15 schedule correction | Add Ethernet-to-I3C fan-out workstream

- Updated [i3c-bringup-12-week-schedule-proposal](synthesis/i3c-bringup-12-week-schedule-proposal.md) to include the STM32H563/573 Ethernet-to-I3C fan-out as a parallel adapter workstream across the 12-week plan.
- Updated [i3c-host-adapter-decision](synthesis/i3c-host-adapter-decision.md) and [index](index.md) to reflect that production/lab fan-out is tracked in parallel while module-side I3C-MCI proof remains the critical path.

# 2026-06-15 schedule correction | Add controlled DSP debug-bridge posture

- Updated [i3c-bringup-12-week-schedule-proposal](synthesis/i3c-bringup-12-week-schedule-proposal.md) to track transparent bridging to in-module DSP I3C targets as a separate controlled debug-interface workstream, not as normal CMIS management traffic.
- Clarified that the DSP bridge should be treated like `SWD`: disabled by default, explicitly enabled, access controlled, allowlisted, logged, and lockable or removable for production use.
- Updated [cmis-over-i3c-roadmap](synthesis/cmis-over-i3c-roadmap.md), [i3cmci-required-subset-vs-mipi-i3c-feature-set](comparisons/i3cmci-required-subset-vs-mipi-i3c-feature-set.md), [what-is-the-current-i3c-bringup-schedule](queries/what-is-the-current-i3c-bringup-schedule.md), and [index](index.md) with the same debug-interface framing.
