---
type: synthesis
title: APSU/iLT Page 70h Verification Plan
created: 2026-06-09
updated: 2026-06-10
tags: [cmis, apsu, ilt, verification-plan, page-70h, ieee-802-3dj, sian3]
related: [apsu-ilt-verification-report.md, apsu-ilt-customer-note-plan.md, ../sources/lumentum-2026-8023dj-apsu-ilt-support-plan.md, ../sources/lumentum-2026-dpsm-apsu-ilt-state-machine.md, ../sources/broadcom-2026-sian3-apsu-application-notes.md, ../sources/feng-jiang-2026-sian3-link-training-verification-email-thread.md, ../sources/oif2026-093-08-802-3dj-apsu-draft.md, ../sources/ieee-p802-3dj-d2-3.md]
sources: [apsu-ilt-verification-report.md, apsu-ilt-customer-note-plan.md, ../sources/lumentum-2026-8023dj-apsu-ilt-support-plan.md, ../sources/lumentum-2026-dpsm-apsu-ilt-state-machine.md, ../sources/broadcom-2026-sian3-apsu-application-notes.md, ../sources/feng-jiang-2026-sian3-link-training-verification-email-thread.md, ../sources/oif2026-093-08-802-3dj-apsu-draft.md, ../sources/ieee-p802-3dj-d2-3.md]
status: planned
---

# APSU/iLT Page 70h Verification Plan

This is an internal engineering verification plan for the next-release 1.6T 2xDR4 FRO module firmware with CMIS Page 70h APSU/iLT support. Its purpose is to close or explicitly bound the gaps identified in [apsu-ilt-verification-report](apsu-ilt-verification-report.md) against IEEE 802.3dj APSU/iLT behavior, OIF CMIS Page 70h, and the Broadcom Sian3 APSU application note.

Formal pass/fail for this plan is based on CMIS Page 70h behavior plus external lab measurements. CMIS Page 70h is the formal pass/fail interface. Vendor CDB, lab-only P253.66 debug CDB, and Sian3 cAPI are diagnostic and correlation paths only. BERT APIs, traffic/FEC counters, loss, temperature, and timing captures are external measurement evidence.

## Scope And Assumptions

| Item | Plan position |
|---|---|
| Firmware scope | Next-release firmware with CMIS Page 70h APSU/iLT support. |
| Module scope | 1.6T 2xDR4 FRO module. |
| Formal pass/fail interface | CMIS Page 70h only. |
| Diagnostic correlation paths | Vendor CDB, lab-only P253.66 debug CDB, Sian3 cAPI, and module logs. |
| Lab scope | Expanded setup with Sian3 BERT/DUT, calibrated loss fixtures or VOA, temperature chamber, traffic/FEC capture, link-partner interoperability coverage, and host-management interoperability coverage. |
| Normative baseline | IEEE P802.3dj D2.3 and OIF2026.093.08 Page 70h draft material. |
| Implementation references | Broadcom Sian3 APSU AN, current customer-note plan, current verification report, and prior lab evidence. |
| Release rule | A Page 70h failure cannot be overridden by vendor CDB, debug CDB, or Sian3 cAPI correlation. |

## Baseline And Source-Diff Checkpoint

Before formal execution, freeze the verification matrix to the normative baseline and implementation references in the vault:

- [ieee-p802-3dj-d2-3](../sources/ieee-p802-3dj-d2-3.md)
- [oif2026-093-08-802-3dj-apsu-draft](../sources/oif2026-093-08-802-3dj-apsu-draft.md)
- Implementation references:
  - [broadcom-2026-sian3-apsu-application-notes](../sources/broadcom-2026-sian3-apsu-application-notes.md)
  - [apsu-ilt-customer-note-plan](apsu-ilt-customer-note-plan.md)
  - [apsu-ilt-verification-report](apsu-ilt-verification-report.md)

P0 checkpoint: before lab execution starts, re-diff the latest available IEEE/OIF draft material and any updated Sian3 application-note/source material against the frozen matrix. Any changed Page 70h byte definition, APSU state meaning, legal status ordering, timer range, status bit behavior, or fault/recovery rule must be recorded as a matrix update before testing.

## Formal Pass/Fail Rule

CMIS Page 70h is the formal pass/fail interface. A test can use diagnostic paths to explain a failure, but the formal result must come from Page 70h transaction logs and external measurements such as traffic/FEC BER, calibrated loss, temperature, and timing capture. If Page 70h status contradicts external measurement evidence, the result is a P0 failure because the formal status surface is not trustworthy. In the detailed matrix, `Interface under test` means the Page 70h field, control, or status surface being evaluated.

| Interface | Allowed use |
|---|---|
| CMIS Page 70h | Formal pass/fail for control, status, readiness, recovery, and Page 70h mapping. |
| Vendor CDB | Diagnostic comparison with previous implementation. |
| Lab-only P253.66 debug CDB | Internal Sian3 cAPI correlation and root-cause isolation. |
| Sian3 cAPI | Underlying DSP behavior correlation. |
| BERT APIs and traffic/FEC counters | External behavioral measurement. |
| Chamber and loss instrumentation | Environmental and channel-condition evidence. |

## Low-Level Resource Reuse Model

Current Sian3 lab resources can be reused as setup, diagnostic, or external evidence resources. Low-level Page 70h test cases must still define the Page 70h transaction as the formal action or observation under test.

| Reused resource | Reuse role | Current candidate | Formal evidence boundary |
|---|---|---|---|
| CMIS host, exerciser, or scripted host access profile | Formal Page 70h control/status access | Current available CMIS host/exerciser/scripted setup plus a Page 70h transaction wrapper | Page 70h transaction logs decide pass/fail for control, status, permissions, coherency, latency, and mapping. |
| Sian3 BERT/DUT lab setup | External measurement and fixture reuse | Existing `TP0 -> TP1` and `TP4 -> TP5` setup, VOA/loss path, chamber, and traffic/FEC capture | BER, loss, temperature, and timing corroborate Page 70h behavior and expose evidence contradictions; they do not replace Page 70h. |
| Sian3 Python debug wrappers | Setup and diagnostic correlation | `1p6_sian3_h5_python/yapp/sian3.py` `SIAN3.set_lktrn_info`, `SIAN3.set_apsu_enable`, `SIAN3.get_apsu_enable`, `SIAN3.get_lktrn_info`, `SIAN3.get_lktrn_stat` | Use to seed degraded conditions, confirm underlying Sian3 state, or diagnose failures only. |
| Vendor CDB helpers | Coexistence and migration comparison | `1p6_sian3_h5_python/yapp/cdb.py` `CDB.CMDA200h`, `CDB.CMDA201h`, `CDB.CMDA082h`, `CDB.CMDA083h` | Use for ordered mixed-session coexistence, legacy comparison, and precode correlation; a vendor CDB pass does not satisfy a Page 70h test row. |
| Traffic/FEC helper calls | External behavior evidence | `1p6_sian3_h5_python/yapp/sian3.py` `SIAN3.clear_fec_mon`, `SIAN3.get_fec_pgen`, `SIAN3.get_fec_pmon`, `SIAN3.set_traffic_fec_all` | Use for BER/recovery criteria and data-ready correlation. |
| Existing degraded-tap and polarity recovery scripts/screenshots | Procedure seed material | Feng link-training verification script sequence and screencopy-backed degraded-tap/polarity procedures | Reuse as procedure templates only after lane labels, script version, Page 70h wrapper, and raw evidence IDs are added. |

Each low-level test case must record the reused setup resource, formal Page 70h action or read, diagnostic calls used before or after the formal action, expected external measurement, script or tool revision, and raw evidence artifact IDs.

## Low-Level Verification Primitives

Detailed test cases should compose these primitives instead of duplicating complete procedures in every matrix row.

| Primitive ID | Purpose | Reusable resource or setup | Required evidence | Typical matrix use |
|---|---|---|---|---|
| PRIM-RUN-META | Create immutable run context before any control or status action. | Existing lab run-numbering and evidence archive process. | Run number, firmware version, module serial, host/exerciser identity, partner identity/class when applicable, script/tool revision, mapping manifest revision, operator, setup ID, and artifact ID prefix. | All executed formal, bounded, diagnostic, audit, and release-summary rows. |
| PRIM-P70H-MAP | Validate Page 70h page, bank, side, lane, and Ethernet-interface mapping. | Page 70h host access plus mapping manifest; Sian3 cAPI diagnostic correlation if needed. | Page/bank/lane read/write log, mapping manifest cross-check, fixture port labels, traffic/FEC lane IDs, partner/host profile mapping when applicable, and any diagnostic correlation log. | BR-005, P70H-001, P70H-004, APSU/STR rows using lane-specific behavior, INT-001, INT-002. |
| PRIM-P70H-PERM | Verify Page 70h permissions, reserved fields, invalid writes, and no side effects. | Page 70h host access; module logs only for diagnosis. | Baseline read, attempted write, return status when available, readback, adjacent/status readback, and no-state-change or explicit-error result per frozen declaration. | P70H-001, P70H-002, P70H-003, BR-004, BR-007, INT-002. |
| PRIM-P70H-CONTROL | Execute a Page 70h control action and prove control acceptance. | CMIS host, exerciser, or scripted host access profile. | Timestamped Page 70h write, return status, effective control readback or next legal status transition, control acceptance timeout reference, and failure classification if confirmation is missing. | APSU-001, APSU-004, APSU-005, APSU-007, STR-002, STR-003, INT-001, INT-002. |
| PRIM-P70H-POLL | Poll Page 70h status with declared timing and legal ordering checks. | CMIS host/exerciser polling loop. | Declared polling interval, actual polling intervals, missed/failed reads, observed status sequence, legal status ordering source, and status publication latency markers. | P70H-005, P70H-006, APSU-002, APSU-003, STR-002, STR-008, INT-001, INT-002. |
| PRIM-FEC-RECOVERY | Measure external traffic/FEC behavior before, during, and after APSU/iLT action. | Sian3 BERT/DUT setup and traffic/FEC helper calls such as `SIAN3.clear_fec_mon`, `SIAN3.get_fec_pgen`, `SIAN3.get_fec_pmon`, and `SIAN3.set_traffic_fec_all`. | Pre-FEC BER, post-FEC BER, traffic pattern, measurement window, recovery threshold, recovery timestamp, and enabled lane set. | APSU-002, APSU-006, STR-001, STR-002, STR-004, STR-005, STR-006, STR-008, INT-001, INT-002 when host actions affect link state. |
| PRIM-DIAG-LT | Capture diagnostic Sian3 link-training state without deciding formal pass/fail. | Sian3 Python debug wrappers such as `SIAN3.set_lktrn_info`, `SIAN3.get_lktrn_info`, `SIAN3.get_lktrn_stat`, `SIAN3.set_apsu_enable`, and `SIAN3.get_apsu_enable`. | Function or command list, parameters, returned state, timestamp, lane/side labels, and diagnostic-only evidence label. | P70H-004, APSU-003, APSU-006, APSU-007, STR-003, STR-009, STR-010, INT-001, INT-002, INT-003. |
| PRIM-VCDB-COEX | Prove vendor CDB and Page 70h coexist as ordered mixed-session writes. | Vendor CDB helpers such as `CDB.CMDA200h`, `CDB.CMDA201h`, `CDB.CMDA082h`, and `CDB.CMDA083h`, plus Page 70h access. | Ordered transaction log, shared effective state readback through both surfaces, later-same-key-wins check, invalid-write result, and confirmation Page 70h remains formal pass/fail. | BR-006, APSU-001, APSU-005, INT-003. |
| PRIM-PRECODE | Validate precoding exposure and correlation when in release scope. | Page 70h precode controls/status if exposed; `CDB.CMDA082h` and `CDB.CMDA083h` for diagnostic/vendor comparison. | Page 70h command/readback, operational precode state, capability flags, diagnostic correlation, and customer-claim boundary. | APSU-005 and any precode customer claim. |
| PRIM-FAULT-SETUP | Inject or establish stress/fault condition before observing Page 70h behavior. | Existing degraded-tap, polarity, VOA/loss, temperature chamber, partner-squelch, or non-LT partner procedure seed material. | Setup command list, fixture/instrument settings, partner/fixture condition when applicable, before-state evidence, expected trigger, and confirmation that the condition was present before Page 70h observation. | STR-001, STR-003, STR-004, STR-005, STR-006, STR-007, STR-008, STR-009, INT-001 when interop uses a staged partner condition. |
| PRIM-EVIDENCE-PKG | Close each run or release review with traceable raw evidence and customer-safe boundary. | Internal evidence archive plus customer-facing evidence package process. | Raw artifact IDs, stable archive paths or filenames, selected sanitized excerpts, status label, bounded claim text when needed, internal-only evidence list when applicable, and reviewer sign-off. | All formal, bounded, diagnostic-only, audit, and release-summary rows, including INT-001 through INT-005. |

Primitive composition does not reduce evidence requirements. If a test row uses a primitive, the row inherits that primitive's required evidence and must still declare the Page 70h interface under test, expected result, and release-decision status label.

### Primitive Requirement Classes

Each low-level test case must classify its primitive use before execution.

| Primitive ID | Requirement class | Activation rule |
|---|---|---|
| PRIM-RUN-META | Mandatory core | Required for every executed formal, bounded, diagnostic, audit, or release-summary row. For `Blocked` or `Not Run` rows without execution, the row/result inventory records the missing prerequisite or intentional omission instead of lab-run metadata. |
| PRIM-EVIDENCE-PKG | Mandatory core | Required for every row result before release review, including executed formal rows, bounded rows, diagnostic-only rows, blocked/not-run rationale, `INT-004` audit output, and `INT-005` release-summary output. |
| PRIM-P70H-MAP | Conditional | Required when the row depends on bank, side, lane, Ethernet interface, DUT/REF, fixture, or traffic/FEC lane identity. |
| PRIM-P70H-PERM | Conditional | Required when the row exercises byte permissions, reserved fields, invalid writes, unsupported controls, unsupported applications, or side-effect checks. |
| PRIM-P70H-CONTROL | Conditional | Required when the row performs a supported Page 70h write, command, restart, enable, disable, or write-only/self-clearing action. |
| PRIM-P70H-POLL | Conditional | Required when the row evaluates status publication latency, observed status sequence, readiness, recovery, or legal ordering. |
| PRIM-FEC-RECOVERY | Conditional | Required when the row claims data-ready behavior, traffic recovery, BER improvement, repeatability, link-partner operation, temperature behavior, or high-loss operation. |
| PRIM-FAULT-SETUP | Conditional | Required when the row depends on degraded taps, polarity inversion, loss, temperature, partner squelch, non-LT partner behavior, recovery counter triggers, or another injected/staged condition. |
| PRIM-PRECODE | Conditional | Required when Page 70h exposes precode behavior or the release/customer claim includes precoding. |
| PRIM-VCDB-COEX | Conditional | Required when the row tests Page 70h/vendor CDB coexistence, migration behavior, or shared effective APSU/iLT state. |
| PRIM-DIAG-LT | Diagnostic-only | Use only for Sian3 state correlation, root-cause isolation, or mapping confidence; it cannot decide a formal Page 70h pass/fail result. |

Rows that use a conditional primitive must state why the activation rule applies. Rows that omit an apparently applicable conditional primitive must record a reviewer-approved reason before execution.

## Low-Level Test-Case Sheets

The detailed test matrix remains the coverage summary. Rows that need execution detail are expanded into low-level test-case sheets. A sheet may remain in this plan as a subsection or later move to a dedicated page if the procedure becomes too large; the sheet ID must stay tied to the matrix test ID.

Initial sheet coverage:

- Gate 1 readiness and coexistence: `BR-005`, `BR-006`, `BR-007`, `BR-008`.
- Page 70h interface validation: `P70H-001` through `P70H-006`.
- Nominal APSU/iLT functional validation: `APSU-001` through `APSU-007`.
- Stress and recovery validation using current lab resources first: `STR-001` through `STR-004`.
- Add `STR-005` through `STR-010` and `INT-001` through `INT-005` when the corresponding setup, partner, host/exerciser, or customer claim is in scope for the release.

Each sheet must use this structure:

| Field | Required content |
|---|---|
| Test ID and title | Matrix row ID and concise execution title. |
| Requirement class | Formal row status: in-scope formal, conditional, diagnostic-only, or not-run with reason. |
| Primitives used | Mandatory core, conditional, and diagnostic-only primitives with activation rationale. |
| Reused resources | Setup, scripts, helper calls, instruments, and diagnostic paths reused from the low-level resource reuse model. |
| Formal Page 70h action/read | Page, bank, side, lane/interface context, byte or range, write/read value, expected access behavior, and control acceptance requirement when applicable. |
| Diagnostic calls | Vendor CDB, debug CDB, Sian3 cAPI, BERT/FEC helper calls, and whether each call is setup, diagnostic correlation, coexistence evidence, or external measurement evidence. |
| Procedure outline | Ordered execution steps, including precondition checks, formal Page 70h transaction, status polling, external measurement, diagnostics, cleanup, and rerun rule. |
| Expected observation | Expected Page 70h result, external measurement result, legal status ordering, and diagnostic correlation expectation when used. |
| Pass/fail criteria | Formal status-label rule, failure classification, evidence contradiction rule, bounded claim rule, and blockers. |
| Evidence artifacts | Raw artifact IDs, archive paths or filenames, script/tool revisions, setup photo or diagram, and customer-safe excerpt boundary. |
| Known blockers | Missing implementation, missing setup, missing mapping, missing timeout, missing draft mapping, or missing raw data. |

No low-level test-case sheet may use debug CDB, Sian3 cAPI, or vendor CDB as the formal pass/fail action unless the row is explicitly diagnostic-only or a coexistence row whose formal result is still judged through Page 70h plus ordered mixed-session evidence.

Sheet execution order starts with `BR-005`. Lane-specific functional, stress, recovery, coexistence, and interoperability rows may execute physically before `BR-005` is complete, but their formal result remains `Blocked` until the mapping manifest is frozen, reviewed, and cross-checked.

### BR-005 - Host/Media Lane Inventory And Mapping Manifest

| Field | Content |
|---|---|
| Test ID and title | `BR-005` - Freeze and verify host/media lane inventory and mapping manifest. |
| Requirement class | In-scope formal Gate 1 prerequisite. Missing, ambiguous, or unreviewed mapping produces `Blocked` for this row and any dependent lane-specific row. |
| Primitives used | Mandatory core: `PRIM-RUN-META`, `PRIM-EVIDENCE-PKG`. Conditional: `PRIM-P70H-MAP`. Diagnostic-only: `PRIM-DIAG-LT` when Sian3 side/lane state is used for correlation. |
| Reused resources | Current CMIS host/exerciser or scripted host access profile for Page 70h reads/writes; existing Sian3 BERT/DUT setup covering `TP0 -> TP1` and `TP4 -> TP5`; traffic/FEC lane IDs; fixture photo/diagram; Sian3 Python debug wrappers only for correlation. |
| Formal Page 70h action/read | Read Page 70h bank, side, lane, capability/status/control fields needed to identify each supported APSU/iLT Ethernet interface and enabled lane set. If safe non-disruptive writes exist for mapping validation, execute only after reset/default capture and use Page 70h readback as the formal result. |
| Diagnostic calls | Use Sian3 cAPI/debug wrappers only to correlate side/lane identity and underlying Sian3 state. Record function or command names and parameters as diagnostic-only evidence. |
| Procedure outline | 1. Assign immutable run number and setup ID. 2. Capture firmware/module/host/script revisions. 3. Capture or create mapping manifest from firmware/test-tooling source of truth when available, otherwise hand-author with reviewer tag. 4. Annotate DUT/REF labels, fixture ports, `TP0 -> TP1`, `TP4 -> TP5`, host/media side, Ethernet interface, enabled lane set, and traffic/FEC lane IDs. 5. Read Page 70h mapping-relevant fields through the host access profile. 6. Cross-check Page 70h result against manifest, fixture labels, traffic/FEC lane IDs, and diagnostic Sian3 side/lane data if used. 7. Archive manifest, transaction log, setup photo/diagram, and diagnostic log. |
| Expected observation | Page 70h bank/side/lane interpretation matches the frozen manifest, fixture labels, and traffic/FEC lane IDs. Diagnostic Sian3 correlation, if used, does not contradict the Page 70h mapping. |
| Pass/fail criteria | `Pass` when the mapping manifest is frozen, versioned, reviewed, and Page 70h mapping checks agree with fixture and traffic/FEC identity. `Fail` when Page 70h mapping contradicts verified fixture or traffic/FEC identity. `Blocked` when the manifest, review, setup labeling, Page 70h implementation, or required raw evidence is missing. |
| Evidence artifacts | `BR-005-Rxx-P70H-001` transaction log; `BR-005-Rxx-MAP-001` mapping manifest; `BR-005-Rxx-SETUP-001` setup photo/diagram; `BR-005-Rxx-DIAG-001` diagnostic correlation log when used; script/tool revision record. |
| Known blockers | Missing Page 70h implementation, missing mapping source of truth, unlabeled fixture, unlabeled DUT/REF endpoint, unlabeled traffic/FEC lane IDs, missing script revision, or contradictory diagnostic correlation. |

### BR-006 - Page 70h And Vendor CDB Coexistence

| Field | Content |
|---|---|
| Test ID and title | `BR-006` - Validate Page 70h and vendor CDB coexistence during the transition period. |
| Requirement class | In-scope formal Gate 1 prerequisite when vendor CDB remains supported alongside Page 70h. Missing coexistence evidence produces `Blocked` for nominal control rows that rely on shared APSU/iLT state. |
| Primitives used | Mandatory core: `PRIM-RUN-META`, `PRIM-EVIDENCE-PKG`. Conditional: `PRIM-P70H-MAP`, `PRIM-P70H-CONTROL`, `PRIM-P70H-POLL`, `PRIM-VCDB-COEX`. Diagnostic-only: `PRIM-DIAG-LT` only for root-cause correlation if Page 70h and vendor CDB disagree. |
| Reused resources | Current CMIS host/exerciser or scripted host access profile for Page 70h; vendor CDB helpers in `1p6_sian3_h5_python/yapp/cdb.py` such as `CDB.CMDA200h`, `CDB.CMDA201h`, `CDB.CMDA082h`, and `CDB.CMDA083h`; mapping manifest from `BR-005`; traffic/FEC checks only when needed to expose an evidence contradiction. |
| Formal Page 70h action/read | Use Page 70h as the formal control/status surface for APSU/iLT enable/disable, status/readback, restart/control action when supported, precode if exposed, and invalid/reserved behavior. Page 70h readback after vendor CDB writes is the formal check that the shared effective state is visible through Page 70h. |
| Diagnostic calls | Use `CDB.CMDA200h` for vendor capability comparison, `CDB.CMDA201h` for vendor LT/APSU enable/disable, and `CDB.CMDA082h`/`CDB.CMDA083h` for precode coexistence when precode is in scope. Record CDB command ID, arguments, transaction order, return status, and response fields. |
| Procedure outline | 1. Confirm `BR-005` mapping manifest is frozen or mark this row `Blocked`. 2. Capture default Page 70h state and vendor CDB capability/status state. 3. Page 70h write enable for one mapped Ethernet interface and read back through Page 70h. 4. Read vendor CDB state for the same key and confirm no contradiction. 5. Vendor CDB write disable for the same key and read back through Page 70h. 6. Execute same-key ordered writes in both directions and confirm later accepted transaction wins for that key only. 7. Execute different-key writes and confirm unrelated keys do not change. 8. Exercise one non-reserved invalid control class and CMIS reserved field behavior without partial disagreement. 9. Archive ordered transaction log, readbacks, and any diagnostic state captures. |
| Expected observation | Both surfaces expose one shared effective APSU/iLT state keyed by Ethernet interface, side, lane set, and control field. Page 70h remains consistent after vendor CDB writes, vendor CDB comparison does not contradict Page 70h, later ordered same-key writes win, different-key writes remain isolated, and invalid/reserved behavior does not create side effects. |
| Pass/fail criteria | `Pass` when ordered mixed-session evidence proves shared effective state and no Page 70h/vendor CDB behavior conflict for the representative coverage set. `Fail` when the surfaces disagree, later same-key write behavior is inconsistent, a different key changes unexpectedly, an invalid/reserved write causes a side effect, or Page 70h cannot report the effective state. `Blocked` when Page 70h implementation, vendor CDB access, mapping, or transaction logging is missing. |
| Evidence artifacts | `BR-006-Rxx-P70H-001` Page 70h transaction log; `BR-006-Rxx-VCDB-001` vendor CDB transaction log; `BR-006-Rxx-ORDER-001` ordered mixed-session sequence; `BR-006-Rxx-DIAG-001` diagnostic correlation log if used; `BR-006-Rxx-FEC-001` traffic/FEC evidence only when needed. |
| Known blockers | Missing Page 70h control/status implementation, missing vendor CDB access, missing `BR-005` mapping, missing ordered timestamp log, unclear shared-state key definition, or unresolved invalid/reserved write declaration. |

### BR-007 - Invalid-Write And Reserved-Field Rule Freeze

| Field | Content |
|---|---|
| Test ID and title | `BR-007` - Freeze invalid-write declaration before formal Page 70h validation. |
| Requirement class | In-scope formal Gate 1 prerequisite for `P70H-001`, `P70H-002`, `P70H-003`, `BR-004`, `BR-006`, and any control row that exercises unsupported, invalid, or reserved behavior. |
| Primitives used | Mandatory core: `PRIM-RUN-META`, `PRIM-EVIDENCE-PKG`. Conditional: `PRIM-P70H-PERM`. Diagnostic-only: module logs only for root-cause diagnosis if a reserved or invalid write appears to mutate state. |
| Reused resources | Current CMIS host/exerciser or scripted host access profile for Page 70h read/write attempts; release/interface spec draft for non-reserved invalid controls; CMIS reserved-field rule from the normative baseline. |
| Formal Page 70h action/read | No broad mutation sweep is executed in this rule-freeze row. Capture the pre-execution declaration that reserved bytes/bits are read-only and writes are silently rejected or ignored without side effects; capture the declared behavior for unsupported controls, invalid lane masks, unsupported applications, invalid state-dependent writes, and coexistence invalid writes. |
| Diagnostic calls | None required. Module logs may be captured in later execution rows if an invalid or reserved write unexpectedly changes state. |
| Procedure outline | 1. Assign immutable run number and checklist revision. 2. Freeze the Page 70h invalid-write declaration before byte-map/control execution. 3. Separate CMIS reserved bytes/bits from non-reserved invalid controls. 4. List invalid classes: unsupported controls, invalid lane masks, unsupported applications, invalid side/lane combinations, invalid state-dependent writes, and cross-surface coexistence invalid writes. 5. For each non-reserved invalid class, record expected return status where CMIS allows and expected no-state-change behavior. 6. Record reviewer sign-off and link the declaration to affected test rows. |
| Expected observation | The declaration is complete enough that later rows can judge readback, side effects, and error/no-state-change behavior without changing expectations during execution. Reserved bytes/bits follow CMIS reserved-field behavior; non-reserved invalid controls follow the frozen release/interface declaration. |
| Pass/fail criteria | `Pass` when the invalid-write declaration is frozen, reviewed, separates reserved from non-reserved invalid behavior, and covers all affected Page 70h/control/coexistence classes. `Fail` when the declaration contradicts CMIS reserved-field behavior. `Blocked` when any in-scope invalid class lacks a declared expected behavior before execution. |
| Evidence artifacts | `BR-007-Rxx-DECL-001` invalid-write declaration; `BR-007-Rxx-REVIEW-001` reviewer sign-off; `BR-007-Rxx-MATRIX-001` affected-row traceability list. |
| Known blockers | Missing release/interface spec mapping, unresolved OIF/CMIS interpretation for a field, missing reviewer sign-off, or mixed treatment of reserved bytes/bits and non-reserved invalid controls. |

### BR-008 - Control Acceptance Timeout Freeze

| Field | Content |
|---|---|
| Test ID and title | `BR-008` - Freeze control acceptance timeouts before command-driven validation. |
| Requirement class | In-scope formal Gate 1 prerequisite for any row that performs supported Page 70h enable/disable, command, restart, write-only, self-clearing, or state-dependent control actions. |
| Primitives used | Mandatory core: `PRIM-RUN-META`, `PRIM-EVIDENCE-PKG`. Conditional: `PRIM-P70H-CONTROL`, `PRIM-P70H-POLL` for controls whose acceptance is confirmed by a status transition. Diagnostic-only: none required. |
| Reused resources | CMIS/OIF timeout requirements when defined; release/interface spec for controls without normative timeout; current host/exerciser or scripted host access profile to prove timestamping and polling capability. |
| Formal Page 70h action/read | No functional control action is required in this rule-freeze row. Capture the timeout table for each supported Page 70h control class and the confirmation method: effective readback, return status plus next legal status transition, or other release/interface-spec-defined confirmation. |
| Diagnostic calls | None required. Diagnostic CDB or Sian3 cAPI timestamps may be used in later rows only as supporting evidence, never as the start/stop authority for formal Page 70h acceptance. |
| Procedure outline | 1. Assign immutable run number and checklist revision. 2. List every supported Page 70h control class that can affect APSU/iLT state. 3. For each control, record whether it is readable, write-only, self-clearing, or state-dependent. 4. Assign timeout from CMIS/OIF where defined; otherwise assign release/interface-spec timeout before execution. 5. Define the control acceptance confirmation method. 6. Confirm host/exerciser can timestamp writes, readbacks, observed status transitions, polling intervals, missed reads, and timeout expiry. 7. Record reviewer sign-off and affected-row traceability. |
| Expected observation | Every command-driven row has a predeclared timeout and confirmation method before execution. Write-only or self-clearing controls are classified by return status plus next legal observed status transition, not by assumed acceptance. |
| Pass/fail criteria | `Pass` when all supported control classes have frozen timeout values, confirmation methods, host timing capability, reviewer sign-off, and affected-row traceability. `Fail` when the timeout declaration contradicts CMIS/OIF requirements. `Blocked` when any in-scope supported control lacks a timeout or confirmation method before execution. |
| Evidence artifacts | `BR-008-Rxx-TIMEOUT-001` timeout table; `BR-008-Rxx-REVIEW-001` reviewer sign-off; `BR-008-Rxx-HOST-001` host/exerciser timestamp and polling capability record; `BR-008-Rxx-MATRIX-001` affected-row traceability list. |
| Known blockers | Missing Page 70h control list, unresolved CMIS/OIF timeout interpretation, missing release/interface timeout for a supported control, missing host timestamp capability, or missing reviewer sign-off. |

### P70H-001 - Page 70h Byte Ranges And Access Permissions

| Field | Content |
|---|---|
| Test ID and title | `P70H-001` - Validate Page 70h byte ranges `128-131`, `132-151`, `152-191`, and `192-230`. |
| Requirement class | In-scope formal Gate 2 foundation for all Page 70h functional rows. Missing byte-map or permission evidence produces `Blocked` for dependent Page 70h control/status rows. |
| Primitives used | Mandatory core: `PRIM-RUN-META`, `PRIM-EVIDENCE-PKG`. Conditional: `PRIM-P70H-MAP` for bank/side/lane context and `PRIM-P70H-PERM` for access permissions. |
| Reused resources | Current CMIS host/exerciser or scripted host access profile; `BR-005` mapping manifest; `BR-007` invalid-write declaration; release/interface Page 70h register map; OIF Page 70h draft byte definitions. |
| Formal Page 70h action/read | Select the target Page 70h bank/context, read ranges `128-131`, `132-151`, `152-191`, and `192-230`, compare implemented fields and access permissions to the frozen register map, perform safe write/readback checks for writable non-destructive fields, and avoid using functional APSU state transitions as proof for this row unless they are covered by a linked functional row. |
| Diagnostic calls | None required. Diagnostic Sian3 state reads may be used only if a field-to-side/lane mapping contradiction appears and must be labeled diagnostic-only. |
| Procedure outline | 1. Confirm `BR-005`, `BR-007`, and host access profile are frozen. 2. Capture baseline Page 70h reads for all implemented banks/contexts in scope. 3. Compare byte presence, field width, access type, reset/default value class, and permission behavior to the frozen map. 4. For writable safe fields, write a declared safe value, read back effective value, restore default or prior value, and verify cleanup. 5. For read-only fields, attempt write only when covered by `BR-007` and verify no mutation. 6. Archive transaction log, comparison table, and any cleanup evidence. |
| Expected observation | Implemented byte ranges and access permissions match the frozen Page 70h map. Safe writable fields accept and read back expected values; read-only fields do not mutate; cleanup restores prior state; no adjacent field or APSU/iLT behavior changes unexpectedly. |
| Pass/fail criteria | `Pass` when all in-scope byte ranges and permissions match the frozen map and no side effects are observed. `Fail` when a required byte/range is missing, access permission differs, readback is inconsistent, or side effects occur. `Blocked` when the frozen map, host access profile, `BR-005`, or `BR-007` is missing. |
| Evidence artifacts | `P70H-001-Rxx-P70H-001` transaction log; `P70H-001-Rxx-MAP-001` byte-map comparison table; `P70H-001-Rxx-CLEANUP-001` restore/cleanup record when writes are performed. |
| Known blockers | Missing Page 70h implementation, incomplete frozen register map, missing host support for required page/bank selection, unresolved access type for a field, or unsafe write target without a linked functional row. |

### P70H-002 - Reserved Bytes And Reserved Bits

| Field | Content |
|---|---|
| Test ID and title | `P70H-002` - Verify reserved bytes `231-255` and reserved bits follow CMIS reserved-field behavior. |
| Requirement class | In-scope formal Gate 2 foundation for byte-map integrity and invalid/reserved behavior. |
| Primitives used | Mandatory core: `PRIM-RUN-META`, `PRIM-EVIDENCE-PKG`. Conditional: `PRIM-P70H-PERM`; `PRIM-P70H-MAP` only when reserved behavior is bank/side/lane context dependent. |
| Reused resources | Same host access profile and before/after readback pattern as `P70H-001`; `BR-007` invalid-write rule freeze; frozen Page 70h register map; module status reads for side-effect checks. |
| Formal Page 70h action/read | Read reserved bytes `231-255` and all reserved bits inside implemented Page 70h fields, attempt declared reserved-field write patterns, read back reserved fields and adjacent/status fields, and verify writes are silently rejected or ignored without side effects. |
| Diagnostic calls | None required. Module logs may be captured only if reserved writes appear to mutate state. Vendor CDB and Sian3 cAPI are not used to prove reserved-field behavior. |
| Procedure outline | 1. Confirm `BR-007` declares CMIS reserved-field behavior. 2. Capture baseline reads of reserved bytes, fields containing reserved bits, adjacent fields, and relevant APSU/iLT status. 3. Attempt declared write patterns to reserved bytes/bits using the host access profile. 4. Read back the reserved locations, adjacent fields, and relevant Page 70h status. 5. Confirm no change to reserved values, no adjacent mutation, and no APSU/iLT state transition. 6. Archive raw transaction log and before/after comparison. |
| Expected observation | Reserved bytes and bits remain stable or return their defined reserved value class after write attempts; writes are silently rejected or ignored; no adjacent field, status, control, traffic, or APSU/iLT state changes. |
| Pass/fail criteria | `Pass` when every tested reserved byte/bit follows CMIS reserved-field behavior with no side effects. `Fail` when a reserved write changes reserved state, mutates adjacent fields, triggers APSU/iLT behavior, or creates cross-surface disagreement. `Blocked` when `BR-007`, the frozen map, or host write/readback logging is missing. |
| Evidence artifacts | `P70H-002-Rxx-P70H-001` transaction log; `P70H-002-Rxx-RSV-001` before/after reserved-field comparison; `P70H-002-Rxx-SIDE-001` adjacent/status side-effect check. |
| Known blockers | Ambiguous reserved-bit definitions in the frozen map, host inability to perform controlled reserved write attempts, missing side-effect observation points, or unresolved conflict between release/interface spec and CMIS reserved-field behavior. |

### P70H-003 - Non-Reserved Invalid Controls And Invalid Lane Masks

| Field | Content |
|---|---|
| Test ID and title | `P70H-003` - Verify non-reserved invalid writes and invalid lane masks follow the frozen invalid-write declaration. |
| Requirement class | In-scope formal Gate 2 negative-control validation. This row does not cover reserved bytes or reserved bits; those remain covered by `P70H-002`. |
| Primitives used | Mandatory core: `PRIM-RUN-META`, `PRIM-EVIDENCE-PKG`. Conditional: `PRIM-P70H-PERM`, `PRIM-P70H-MAP`, `PRIM-P70H-CONTROL` when an invalid control is attempted through a normal control location. Diagnostic-only: module logs only if an unexpected mutation is observed. |
| Reused resources | Host access profile from `P70H-001`; `BR-005` mapping manifest; `BR-007` invalid-write declaration; `BR-008` control acceptance timeout table when the invalid class resembles a supported command; traffic/FEC snapshot only when needed to prove no side effect. |
| Formal Page 70h action/read | Attempt predeclared non-reserved invalid writes such as unsupported controls, invalid lane masks, unsupported applications, invalid side/lane combinations, invalid state-dependent writes, and invalid cross-surface coexistence writes. Read back the targeted control/status fields, adjacent fields, and relevant Page 70h readiness/status. |
| Diagnostic calls | None required. Vendor CDB comparison may be used only in coexistence-specific invalid classes and must remain diagnostic unless the row is linked to `BR-006`. |
| Procedure outline | 1. Confirm `BR-005`, `BR-007`, and applicable `BR-008` entries are frozen. 2. Capture baseline Page 70h state, affected control/readback fields, adjacent fields, and relevant traffic/FEC snapshot if side effects need external observation. 3. Execute each declared non-reserved invalid write class through the host access profile. 4. Record return status when available. 5. Read back affected and adjacent fields. 6. Confirm explicit error where declared or no state change where declared. 7. Confirm no partial mutation, no cross-surface disagreement, and no APSU/iLT or traffic side effect. 8. Restore any state if a failed write unexpectedly mutated state, then classify the run as `Fail`, not cleanup success. |
| Expected observation | Every invalid non-reserved control follows the frozen declaration: explicit error where declared or no state change where declared. No control subset mutates, no unrelated lane or side changes, no Page 70h/vendor CDB disagreement appears, and traffic/FEC/APSU state remains unaffected unless the invalid class explicitly expects a fault response. |
| Pass/fail criteria | `Pass` when all tested invalid classes follow the frozen declaration with no partial mutation or side effects. `Fail` when an invalid write is accepted unexpectedly, partially mutates state, changes an unrelated key, causes Page 70h/vendor CDB disagreement, or changes APSU/iLT or traffic behavior. `Blocked` when the invalid-write declaration, mapping, host logging, or relevant timeout declaration is missing. |
| Evidence artifacts | `P70H-003-Rxx-P70H-001` invalid-write transaction log; `P70H-003-Rxx-STATE-001` before/after state comparison; `P70H-003-Rxx-SIDE-001` side-effect evidence; `P70H-003-Rxx-DIAG-001` diagnostic log if used. |
| Known blockers | Missing invalid-write declaration for a class, ambiguity between reserved and non-reserved invalid fields, missing lane/application support matrix, unsafe invalid write pattern, or missing observation path for side effects. |

### P70H-004 - Active Host/Media Side And Lane Mapping Validation

| Field | Content |
|---|---|
| Test ID and title | `P70H-004` - Verify Page 70h host/media side and per-lane mapping against the frozen mapping manifest. |
| Requirement class | In-scope formal Gate 2 mapping proof for lane-specific Page 70h validation. `BR-005` freezes the manifest; this row actively proves it with Page 70h behavior and external correlation. |
| Primitives used | Mandatory core: `PRIM-RUN-META`, `PRIM-EVIDENCE-PKG`. Conditional: `PRIM-P70H-MAP`, `PRIM-P70H-CONTROL` only for safe mapping actions, `PRIM-P70H-POLL` for status-observation mapping, and `PRIM-FEC-RECOVERY` when traffic/FEC lane identity is used. Diagnostic-only: `PRIM-DIAG-LT` for Sian3 correlation. |
| Reused resources | `BR-005` mapping manifest; current host access profile; Sian3 BERT/DUT setup with `TP0 -> TP1` and `TP4 -> TP5`; traffic/FEC lane IDs; setup photo/diagram; Sian3 debug wrappers only for diagnostic correlation. |
| Formal Page 70h action/read | For each in-scope Ethernet interface, side, and enabled lane set, execute a safe Page 70h per-lane/per-interface observation or non-disruptive control/readback sequence that can be tied to the mapping manifest. The formal proof is Page 70h transaction evidence plus external fixture/traffic/FEC correlation. |
| Diagnostic calls | Use Sian3 cAPI/debug wrappers such as `SIAN3.get_lktrn_info`, `SIAN3.get_lktrn_stat`, `SIAN3.get_apsu_enable`, or equivalent only to explain the underlying side/lane identity. Record these as diagnostic-only with plain path plus symbol names. |
| Procedure outline | 1. Confirm `BR-005` is `Pass`; otherwise mark this row `Blocked`. 2. Select safe Page 70h observation/action for each side/lane or Ethernet interface in scope. 3. Capture baseline Page 70h state and traffic/FEC lane identity. 4. Execute the Page 70h observation/action in one mapped lane or interface at a time, using the complete Ethernet interface lane set for normal APSU/iLT validation unless this is a declared partial-lane negative/isolation check. 5. Correlate observed Page 70h side/lane/interface result to fixture labels and traffic/FEC lane IDs. 6. Capture optional Sian3 diagnostic state. 7. Restore state and archive logs. |
| Expected observation | Page 70h side/lane/interface behavior matches the frozen mapping manifest, fixture labels, and traffic/FEC lane IDs for every in-scope mapped path. Diagnostic Sian3 correlation, if captured, agrees or explains a failure without overriding Page 70h evidence. |
| Pass/fail criteria | `Pass` when active Page 70h mapping evidence and external correlation agree for every in-scope path. `Fail` when Page 70h mapping contradicts fixture, traffic/FEC, or the frozen manifest. `Blocked` when `BR-005`, safe Page 70h observation/action, traffic/FEC lane identity, setup labels, or required logging is missing. |
| Evidence artifacts | `P70H-004-Rxx-P70H-001` per-lane/per-interface transaction log; `P70H-004-Rxx-FEC-001` traffic/FEC lane correlation log when used; `P70H-004-Rxx-SETUP-001` setup photo/diagram reference; `P70H-004-Rxx-DIAG-001` diagnostic Sian3 correlation log if used. |
| Known blockers | Missing safe Page 70h mapping action/observation, incomplete `BR-005` manifest, unlabeled fixture, unlabeled traffic/FEC lanes, inability to isolate observation per mapped path, or contradictory diagnostic state. |

### P70H-005 - Multi-Byte Monitor And Status Data Coherency

| Field | Content |
|---|---|
| Test ID and title | `P70H-005` - Verify CMIS data coherency for multi-byte Page 70h monitors and status. |
| Requirement class | In-scope formal Gate 2 coherency validation for all Page 70h multi-byte monitors or status values used by APSU/iLT release claims. |
| Primitives used | Mandatory core: `PRIM-RUN-META`, `PRIM-EVIDENCE-PKG`. Conditional: `PRIM-P70H-POLL`; `PRIM-P70H-CONTROL` when a Page 70h action creates the changing-state window; `PRIM-FEC-RECOVERY` only when traffic/FEC confirms the external state transition. |
| Reused resources | Current host access profile with defined multi-byte read sequence; Page 70h transaction logger; `BR-008` timeout table when a control action starts the transition; traffic/FEC capture or diagnostic status only as correlation. |
| Formal Page 70h action/read | Read each in-scope multi-byte Page 70h monitor/status value repeatedly under a stable state, then read the same value class while APSU/iLT state is changing. The formal evidence is the sequence of Page 70h multi-byte snapshots and whether any valid-looking value is torn or mixed-generation. |
| Diagnostic calls | Host retry logs are diagnostic robustness evidence only. Sian3 cAPI/debug status may explain underlying transitions, but cannot mask a Page 70h coherency failure. |
| Procedure outline | 1. Confirm the host access profile defines byte/range read size, order, retry behavior, and timestamping for multi-byte fields. 2. Capture stable-state repeated reads for each in-scope multi-byte monitor/status value. 3. Start a controlled APSU/iLT transition through Page 70h or an independently observed external trigger. 4. Poll the same multi-byte values through the declared read sequence during the changing-state window. 5. Log raw bytes, interpreted values, timestamps, retry attempts, missed reads, and any invalid/unstable marker. 6. Compare snapshots for torn or mixed-generation values. 7. Archive raw transaction log and coherency analysis. |
| Expected observation | Stable reads produce coherent repeated snapshots. Changing-state reads may show old-generation or new-generation values, or a declared invalid/unstable marker, but must not expose a torn or mixed-generation value as valid. Host retries may appear in the log but do not remove a previously exposed valid-looking torn value from the evidence. |
| Pass/fail criteria | `Pass` when stable and changing-state reads show coherent values or declared invalid/unstable markers with no valid-looking torn values. `Fail` when a multi-byte monitor/status read exposes torn or mixed-generation data as valid, or when retry behavior hides such a value. `Blocked` when the host access profile, multi-byte field list, changing-state trigger, or raw byte logging is missing. |
| Evidence artifacts | `P70H-005-Rxx-P70H-001` raw multi-byte transaction log; `P70H-005-Rxx-COH-001` coherency analysis; `P70H-005-Rxx-HOST-001` host read-sequence and retry record; `P70H-005-Rxx-DIAG-001` diagnostic transition correlation if used. |
| Known blockers | Missing Page 70h multi-byte field list, unclear valid/invalid marker definition, host unable to log raw bytes, no safe changing-state trigger, or reliance on host retries as the only coherency protection. |

### P70H-006 - Page 70h Status Publication Latency

| Field | Content |
|---|---|
| Test ID and title | `P70H-006` - Measure Page 70h status publication latency. |
| Requirement class | In-scope formal Gate 2 management-status timing validation. This row measures Page 70h publication delay only; control-to-traffic-recovery time is covered by `STR-002`. |
| Primitives used | Mandatory core: `PRIM-RUN-META`, `PRIM-EVIDENCE-PKG`. Conditional: `PRIM-P70H-POLL`; `PRIM-P70H-CONTROL` for command-driven changes; `PRIM-FEC-RECOVERY` only to identify an independently observed external trigger or evidence contradiction, not to define status publication latency. |
| Reused resources | Host access profile with declared polling interval and missed-read logging; `BR-008` control acceptance timeout table for command-driven triggers; Page 70h transaction logger; external traffic/FEC or diagnostic timestamps as supporting evidence only. |
| Formal Page 70h action/read | For command-driven changes, start timing at Page 70h control transaction completion after control acceptance confirmation. For fault/recovery changes, start timing at the independently observed external event. Stop timing at the first Page 70h read that reports the new stable status. |
| Diagnostic calls | BERT timing, traffic/FEC, vendor CDB, debug CDB, or Sian3 cAPI timestamps may be captured as supporting evidence but cannot replace the Page 70h start/stop definitions. |
| Procedure outline | 1. Confirm declared polling interval, host timestamp resolution, missed-read logging, and `BR-008` confirmation method where applicable. 2. Capture baseline Page 70h status. 3. Trigger the status change through Page 70h control after acceptance confirmation or through an independently observed external event. 4. Poll Page 70h at the declared interval and record actual intervals, missed reads, failed reads, raw status values, and interpreted status. 5. Identify first stable Page 70h status read. 6. Calculate status publication latency and compare to the predeclared limit, or classify as measured/bounded/non-contradictory when no numeric limit is available. 7. Archive raw timing and polling logs. |
| Expected observation | Page 70h publishes the expected status within the predeclared limit, or within a bounded measured window that does not create an evidence contradiction when no numeric limit exists. Observed status sequence is legal and does not report data-ready APSU state before the traffic/FEC recovery criterion is met. |
| Pass/fail criteria | `Pass` when status publication latency meets the declared limit or bounded criterion, missed/failed reads are recorded, and the observed status sequence is legal. `Fail` when latency exceeds the declared limit, is unbounded, hides missed/failed reads, creates an evidence contradiction, or reports a data-ready APSU state before traffic/FEC recovery. `Blocked` when the polling interval, timestamp capability, trigger definition, or status mapping is missing. |
| Evidence artifacts | `P70H-006-Rxx-P70H-001` raw status polling log; `P70H-006-Rxx-TIME-001` latency calculation; `P70H-006-Rxx-HOST-001` polling interval and missed-read record; `P70H-006-Rxx-DIAG-001` supporting external or diagnostic timestamps if used. |
| Known blockers | Missing declared polling interval, missing status mapping, missing trigger definition, missing host timestamp capability, missing `BR-008` acceptance rule for command-driven tests, or no safe way to create the status transition. |

### APSU-001 - Complete Ethernet-Interface APSU/iLT Enable And Disable

| Field | Content |
|---|---|
| Test ID and title | `APSU-001` - Enable and disable APSU/iLT per complete host/media Ethernet interface lane set. |
| Requirement class | In-scope formal Gate 3 nominal functional validation. Partial-lane enablement is not used as the normal pass case; it belongs to negative or isolation testing with explicit expected behavior. |
| Primitives used | Mandatory core: `PRIM-RUN-META`, `PRIM-EVIDENCE-PKG`. Conditional: `PRIM-P70H-MAP`, `PRIM-P70H-CONTROL`, `PRIM-P70H-POLL`, `PRIM-FEC-RECOVERY` if traffic continuity/recovery is part of the row. Diagnostic-only: `PRIM-DIAG-LT`; conditional coexistence: `PRIM-VCDB-COEX` only when tied to `BR-006`. |
| Reused resources | `BR-005` mapping manifest; `BR-006` coexistence rule when vendor CDB remains supported; `BR-008` timeout table; `P70H-004` active mapping evidence; current host access profile; Sian3 BERT/DUT setup and traffic/FEC capture; optional vendor CDB/debug correlation. |
| Formal Page 70h action/read | Through Page 70h, enable APSU/iLT for the complete enabled lane set of each in-scope Ethernet interface and side, confirm control acceptance, poll status/readiness, then disable and confirm the effective state returns to the expected disabled/default state. |
| Diagnostic calls | Vendor CDB may be read for coexistence comparison after Page 70h writes; Sian3 cAPI/debug wrappers such as `SIAN3.get_lktrn_info`, `SIAN3.get_lktrn_stat`, and `SIAN3.get_apsu_enable` may be used only for diagnostic correlation. |
| Procedure outline | 1. Confirm `BR-005`, `BR-006` when applicable, `BR-008`, `P70H-001`, `P70H-004`, and host access profile prerequisites. 2. Capture baseline Page 70h control/status, traffic/FEC state, and optional diagnostic state. 3. Write Page 70h enable for the complete enabled lane set of the Ethernet interface. 4. Confirm control acceptance by readback or next legal status transition within the frozen timeout. 5. Poll Page 70h status through the declared interval until the expected enabled state is stable. 6. Capture traffic/FEC evidence if the row claims active data-ready behavior. 7. Optionally read vendor CDB/debug state for correlation. 8. Write Page 70h disable for the same complete lane set and confirm disabled/default state. 9. Archive logs and cleanup state. |
| Expected observation | Page 70h accepts enable/disable for the complete Ethernet-interface lane set, publishes legal observed status transitions, and reports the effective state consistently. Any vendor CDB/debug correlation agrees with Page 70h or is recorded as diagnostic evidence for a failure. |
| Pass/fail criteria | `Pass` when Page 70h enable and disable are accepted, readback/status confirms the expected effective state within the frozen timeout, observed status sequence is legal, and external evidence does not contradict Page 70h. `Fail` when Page 70h cannot control/report the state, acceptance confirmation is missing after timeout, status ordering is illegal, Page 70h contradicts external evidence, or partial/unrelated lanes mutate. `Blocked` when mapping, timeout, Page 70h byte-map, active mapping, or host logging prerequisites are missing. |
| Evidence artifacts | `APSU-001-Rxx-P70H-001` control/status transaction log; `APSU-001-Rxx-TIME-001` control acceptance timing; `APSU-001-Rxx-FEC-001` traffic/FEC evidence if used; `APSU-001-Rxx-VCDB-001` vendor CDB comparison if used; `APSU-001-Rxx-DIAG-001` Sian3 diagnostic correlation if used. |
| Known blockers | Missing Page 70h enable/disable implementation, incomplete enabled lane set mapping, missing acceptance timeout, unsafe disable cleanup path, vendor CDB/Page 70h state disagreement from `BR-006`, or no traffic/FEC observation path for a data-ready claim. |

### APSU-002 - Data-Ready APSU State Correlation

| Field | Content |
|---|---|
| Test ID and title | `APSU-002` - Verify data-ready APSU state is not inferred from `DPActivated` or `PATH_UP` alone. |
| Requirement class | In-scope formal Gate 3 readiness validation for nominal APSU/iLT operation. |
| Primitives used | Mandatory core: `PRIM-RUN-META`, `PRIM-EVIDENCE-PKG`. Conditional: `PRIM-P70H-MAP`, `PRIM-P70H-CONTROL`, `PRIM-P70H-POLL`, `PRIM-FEC-RECOVERY`. Diagnostic-only: `PRIM-DIAG-LT` for Sian3 state correlation. |
| Reused resources | `APSU-001` enable sequence; Page 70h status polling; traffic/FEC capture from the Sian3 BERT/DUT setup; predeclared traffic/FEC recovery criterion; optional diagnostic Sian3 cAPI/debug status. |
| Formal Page 70h action/read | Enable APSU/iLT through Page 70h for the complete Ethernet-interface lane set, poll Page 70h readiness/status/path state through the declared interval, and capture the observed status sequence until readiness is stable. |
| Diagnostic calls | Sian3 cAPI/debug status such as LT state, ready bits, or path-up indicators may be captured only to correlate Page 70h readiness and explain failures. `DPActivated` and `PATH_UP` are supporting indicators, not complete data-ready proof. |
| Procedure outline | 1. Confirm prerequisites from `APSU-001`, `P70H-004`, `P70H-005`, and `P70H-006` as applicable. 2. Capture baseline Page 70h status, DPSM state if available, and traffic/FEC state. 3. Enable APSU/iLT through Page 70h and confirm control acceptance. 4. Poll Page 70h readiness/status and record observed status sequence. 5. Capture traffic/FEC measurements until the predeclared recovery criterion is met or timeout expires. 6. Compare the first Page 70h data-ready indication with the traffic/FEC recovery timestamp. 7. Record any `DPActivated`, `PATH_UP`, or diagnostic Sian3 state as supporting evidence only. 8. Archive readiness, traffic/FEC, timing, and diagnostic logs. |
| Expected observation | Page 70h data-ready/readiness status does not assert before traffic/FEC meets the predeclared recovery criterion. `DPActivated` or `PATH_UP` may occur as supporting states, but a formal data-ready result requires both Page 70h readiness/status and external traffic/FEC evidence. |
| Pass/fail criteria | `Pass` when Page 70h readiness/status and traffic/FEC recovery agree within the declared timing/polling rules and the observed status sequence is legal. `Fail` when Page 70h reports data-ready before traffic/FEC recovery, traffic/FEC passes while Page 70h remains not-ready beyond the declared latency/timeout rule, `DPActivated` or `PATH_UP` is treated as sufficient by itself, or any evidence contradiction remains unresolved. `Blocked` when the recovery criterion, traffic/FEC capture, status mapping, or Page 70h polling setup is missing. |
| Evidence artifacts | `APSU-002-Rxx-P70H-001` readiness/status polling log; `APSU-002-Rxx-FEC-001` traffic/FEC recovery log; `APSU-002-Rxx-TIME-001` readiness-to-traffic correlation; `APSU-002-Rxx-DIAG-001` diagnostic state log if used. |
| Known blockers | Missing traffic/FEC recovery criterion, missing Page 70h readiness mapping, no stable traffic/FEC measurement window, missing status polling interval, or inability to distinguish `DPActivated`, `PATH_UP`, and data-ready APSU state. |

### APSU-003 - RTS, Local Ready, Remote Ready, And Path-Up Ordering

| Field | Content |
|---|---|
| Test ID and title | `APSU-003` - Verify local/remote RTS and ready-bit transitions through Page 70h. |
| Requirement class | In-scope formal Gate 3 readiness/status-ordering validation. BER and traffic recovery remain primarily covered by `APSU-002`; this row checks Page 70h readiness exposure and legal observed status sequence. |
| Primitives used | Mandatory core: `PRIM-RUN-META`, `PRIM-EVIDENCE-PKG`. Conditional: `PRIM-P70H-CONTROL`, `PRIM-P70H-POLL`, `PRIM-P70H-MAP`. Diagnostic-only: `PRIM-DIAG-LT`; `PRIM-FEC-RECOVERY` only as a guardrail against false data-ready indication. |
| Reused resources | `APSU-001` enable sequence; `APSU-002` data-ready evidence pair for guardrail checks; Page 70h status polling; legal status ordering source from IEEE/OIF or frozen release/interface mapping; optional Sian3 cAPI/debug correlation for RTS/ready/path-up state. |
| Formal Page 70h action/read | Start APSU/iLT through Page 70h, then poll Page 70h status fields that expose RTS, local ready, remote ready, path-up/readiness, or their mapped equivalents. Record every observed transition and its timestamp using the declared polling interval. |
| Diagnostic calls | Sian3 cAPI/debug readiness or LT status may be captured to explain observed Page 70h transitions, but legal ordering is judged from the normative baseline or frozen release/interface mapping and the Page 70h observed sequence. |
| Procedure outline | 1. Confirm legal status ordering source is frozen. 2. Capture baseline Page 70h readiness/status. 3. Enable or restart APSU/iLT through Page 70h and confirm control acceptance. 4. Poll Page 70h at the declared interval until stable data-ready or terminal/fault state. 5. Record observed RTS, local ready, remote ready, path-up/readiness values and timestamps. 6. Compare observed order to the legal ordering source without requiring every transient state to be captured. 7. Use traffic/FEC only to ensure Page 70h does not report data-ready before recovery. 8. Archive status sequence and diagnostic correlation if used. |
| Expected observation | Every observed Page 70h transition is legal for the selected APSU/iLT state path. Page 70h readiness indicators do not jump to data-ready before required precursor observations or before traffic/FEC guardrail evidence permits it. Missing unobserved transients are acceptable when polling interval could have skipped them, but observed illegal transitions are failures. |
| Pass/fail criteria | `Pass` when observed Page 70h RTS/ready/path-up sequence is legal, mapped fields are stable and interpretable, and traffic/FEC guardrail does not contradict readiness. `Fail` when Page 70h exposes illegal ordering, reports data-ready too early, maps readiness fields incorrectly, or diagnostic evidence reveals a Page 70h contradiction. `Blocked` when legal ordering source, status mapping, polling interval, or control trigger is missing. |
| Evidence artifacts | `APSU-003-Rxx-P70H-001` observed status sequence log; `APSU-003-Rxx-ORDER-001` legal-ordering comparison; `APSU-003-Rxx-FEC-001` traffic/FEC guardrail evidence if used; `APSU-003-Rxx-DIAG-001` diagnostic status correlation if used. |
| Known blockers | Missing legal ordering source, ambiguous Page 70h readiness mapping, polling interval too slow for claimed ordering detail, missing trigger, or missing traffic/FEC guardrail for a data-ready claim. |

### APSU-004 - Training Pattern Control And Observation

| Field | Content |
|---|---|
| Test ID and title | `APSU-004` - Verify training pattern control/readback and PRBS13/PRBS31 or relevant training-pattern behavior. |
| Requirement class | Conditional formal Gate 3 validation when training pattern control/status is exposed through Page 70h or used in a customer-facing claim. Diagnostic-only when pattern behavior is accessible only through vendor CDB, debug CDB, Sian3 cAPI, or BERT instrumentation. |
| Primitives used | Mandatory core: `PRIM-RUN-META`, `PRIM-EVIDENCE-PKG`. Conditional formal: `PRIM-P70H-CONTROL`, `PRIM-P70H-POLL`, `PRIM-P70H-MAP`. External evidence: `PRIM-FEC-RECOVERY` or BERT pattern observation when applicable. Diagnostic-only: `PRIM-DIAG-LT`. |
| Reused resources | Page 70h host access profile if pattern fields exist; BERT pattern detection; Sian3 BERT/DUT setup; Sian3 AN/source material for expected PRBS13/PRBS31 or training-pattern behavior; diagnostic Sian3 cAPI/debug state only for correlation. |
| Formal Page 70h action/read | If Page 70h exposes training pattern control/status, write or select the supported pattern through Page 70h, confirm control acceptance/readback, poll any pattern/status fields, and restore the previous/default configuration. If Page 70h does not expose pattern control/status, mark this row `Diagnostic Only` or `Not Run` unless a customer claim requires another formal surface. |
| Diagnostic calls | BERT pattern detection is external evidence. Sian3 cAPI/debug or vendor CDB pattern fields are diagnostic or implementation-reference evidence unless the behavior is exposed through Page 70h or tied to a customer claim. |
| Procedure outline | 1. Confirm whether Page 70h exposes training pattern control/status in the frozen map. 2. If exposed, capture baseline Page 70h pattern state and BERT observation. 3. Select the supported pattern through Page 70h and confirm acceptance/readback within the frozen timeout. 4. Observe expected pattern through BERT instrumentation. 5. Poll relevant Page 70h status and record observed sequence. 6. Restore prior/default pattern state. 7. If not exposed, capture diagnostic-only evidence and label the row accordingly. |
| Expected observation | When Page 70h exposes the feature, Page 70h control/readback and BERT observation agree on the selected supported training pattern. When not exposed, diagnostic evidence may characterize behavior but does not decide a formal Page 70h pass/fail result. |
| Pass/fail criteria | `Pass` when Page 70h-exposed pattern control/readback works, BERT observation confirms the expected pattern, cleanup succeeds, and no evidence contradiction appears. `Fail` when Page 70h exposes the feature but cannot control/read back it correctly, BERT observation contradicts Page 70h, or cleanup fails. `Blocked` when the Page 70h exposure decision, pattern mapping, timeout, or BERT observation path is missing for an in-scope formal claim. `Diagnostic Only` when the behavior is not Page 70h-exposed and no customer-facing claim depends on it. |
| Evidence artifacts | `APSU-004-Rxx-P70H-001` Page 70h pattern transaction log when formal; `APSU-004-Rxx-BERT-001` BERT pattern observation; `APSU-004-Rxx-CLEANUP-001` restore record; `APSU-004-Rxx-DIAG-001` diagnostic Sian3/vendor evidence if used. |
| Known blockers | Missing Page 70h pattern fields for a formal claim, unclear PRBS13/PRBS31 mapping, BERT unable to detect the selected pattern, unsafe pattern switch procedure, or missing cleanup path. |

### APSU-005 - Precoding Request, Readback, And Operational Correlation

| Field | Content |
|---|---|
| Test ID and title | `APSU-005` - Verify precoding request/readback behavior when exposed through Page 70h or used in a customer claim. |
| Requirement class | Conditional formal Gate 3 validation when precoding is exposed through Page 70h or included in a customer-facing claim. Diagnostic-only when only vendor CDB, debug CDB, or Sian3 cAPI exposes the behavior and no customer claim depends on it. |
| Primitives used | Mandatory core: `PRIM-RUN-META`, `PRIM-EVIDENCE-PKG`. Conditional formal: `PRIM-P70H-CONTROL`, `PRIM-P70H-POLL`, `PRIM-PRECODE`, `PRIM-P70H-MAP`. Conditional coexistence: `PRIM-VCDB-COEX` when vendor CDB coexistence is part of the row. Diagnostic-only: `PRIM-DIAG-LT`. |
| Reused resources | Page 70h precode fields if implemented; vendor CDB helpers `1p6_sian3_h5_python/yapp/cdb.py` `CDB.CMDA082h` and `CDB.CMDA083h` for correlation/coexistence; Sian3 BERT/DUT setup; diagnostic Sian3 cAPI/debug state if needed. |
| Formal Page 70h action/read | If Page 70h exposes precoding, write the supported Page 70h precode request/control, confirm control acceptance/readback, poll any Page 70h operational precode status, and restore prior/default state. If Page 70h does not expose precoding and no customer claim requires it, classify as `Diagnostic Only` or `Not Run`. |
| Diagnostic calls | Use `CDB.CMDA082h` to set vendor precode only for coexistence or comparison cases, and `CDB.CMDA083h` to read vendor capability/operational precode state. Record CDB command ID, arguments, response fields, and label them diagnostic or coexistence evidence. |
| Procedure outline | 1. Confirm Page 70h exposure decision and precode mapping in the frozen map. 2. Capture baseline Page 70h precode state and optional vendor CDB `CMDA083h` state. 3. If formal, write Page 70h precode request and confirm acceptance/readback within the frozen timeout. 4. Poll Page 70h operational precode status or mapped equivalent. 5. Optionally compare with `CMDA083h` and diagnostic Sian3 state. 6. If coexistence is in scope, execute ordered Page 70h/vendor CDB precode operations under `BR-006` rules. 7. Restore prior/default precode state and archive evidence. |
| Expected observation | When Page 70h exposes precode behavior, Page 70h request/readback and operational state agree. Vendor CDB `CMDA082h`/`CMDA083h` correlation, if used, does not contradict Page 70h; coexistence evidence shows one shared effective precode state for the same key. |
| Pass/fail criteria | `Pass` when Page 70h-exposed precode request/readback works, operational state is consistent, cleanup succeeds, and optional vendor CDB correlation does not contradict it. `Fail` when Page 70h exposes precode but cannot control/read back it, operational state contradicts Page 70h, vendor CDB coexistence creates disagreement for the same key, or cleanup fails. `Blocked` when Page 70h exposure decision, precode map, timeout, or observation path is missing for an in-scope formal claim. `Diagnostic Only` when precode is not Page 70h-exposed and no customer-facing claim depends on it. |
| Evidence artifacts | `APSU-005-Rxx-P70H-001` Page 70h precode transaction log when formal; `APSU-005-Rxx-VCDB-001` vendor CDB precode log if used; `APSU-005-Rxx-DIAG-001` diagnostic state correlation if used; `APSU-005-Rxx-CLEANUP-001` restore record. |
| Known blockers | Missing Page 70h precode fields for a formal claim, ambiguous precode mapping, missing operational precode readback, unsupported vendor CDB access for coexistence comparison, unsafe precode state change, or missing cleanup path. |

### APSU-006 - Degraded-Tap Recovery And BER Improvement

| Field | Content |
|---|---|
| Test ID and title | `APSU-006` - Verify tap optimization improves BER under degraded tap setup. |
| Requirement class | In-scope formal Gate 3 functional validation using the existing degraded-tap procedure as setup seed material. |
| Primitives used | Mandatory core: `PRIM-RUN-META`, `PRIM-EVIDENCE-PKG`. Conditional: `PRIM-FAULT-SETUP`, `PRIM-P70H-CONTROL`, `PRIM-P70H-POLL`, `PRIM-FEC-RECOVERY`, `PRIM-P70H-MAP`. Diagnostic-only: `PRIM-DIAG-LT` for Sian3 tap and LT-state correlation. |
| Reused resources | Feng degraded-tap script sequence and screencopy-backed procedure; Sian3 BERT/DUT setup with `TP0 -> TP1` and `TP4 -> TP5`; traffic/FEC BER capture; existing Sian3 debug/cAPI tap setup and readback path; Page 70h host access profile for the formal trigger/status. |
| Formal Page 70h action/read | After degraded taps are established and baseline BER is captured, trigger APSU/iLT enable or restart through Page 70h, confirm control acceptance, poll Page 70h readiness/status through the declared interval, and capture the final Page 70h state. |
| Diagnostic calls | Use existing degraded-tap setup and tap readback scripts to create and confirm the impaired precondition. Sian3 LT/tap diagnostics may be captured after Page 70h action to explain tap movement, but pass/fail is based on Page 70h status plus external traffic/FEC improvement. |
| Procedure outline | 1. Confirm `BR-005`, `P70H-004`, `APSU-001`, `APSU-002`, and traffic/FEC recovery criterion are available. 2. Start from a known active data path and capture baseline Page 70h status and BER. 3. Apply the degraded-tap setup from the reused Feng procedure and record script/tool revision, tap targets, readback, side/lane labels, and affected Ethernet interface. 4. Measure degraded pre-APSU traffic/FEC BER. 5. Trigger APSU/iLT through Page 70h enable or restart and confirm control acceptance. 6. Poll Page 70h readiness/status and capture optional Sian3 diagnostic tap/LT state. 7. Measure post-APSU traffic/FEC BER over the declared window. 8. Restore nominal taps or known-good state and archive all logs. |
| Expected observation | The degraded-tap precondition worsens traffic/FEC behavior relative to baseline, Page 70h accepts the APSU/iLT trigger, Page 70h reports legal recovery/readiness status, and post-APSU traffic/FEC BER improves to the declared criterion. Diagnostic tap movement, if captured, agrees with the recovery narrative but is not sufficient by itself. |
| Pass/fail criteria | `Pass` when degraded precondition is confirmed, Page 70h control/status succeeds, observed status sequence is legal, and post-APSU traffic/FEC BER meets the declared improvement/recovery criterion. `Fail` when Page 70h cannot trigger/report recovery, BER does not improve to criterion, Page 70h reports readiness before traffic/FEC recovery, diagnostic evidence contradicts Page 70h, or cleanup cannot restore a safe state. `Blocked` when degraded-tap setup, tap readback, mapping, Page 70h trigger, BER capture, or recovery criterion is missing. |
| Evidence artifacts | `APSU-006-Rxx-SETUP-001` degraded-tap setup/readback log; `APSU-006-Rxx-P70H-001` Page 70h trigger/status log; `APSU-006-Rxx-FEC-001` before/after traffic/FEC BER log; `APSU-006-Rxx-DIAG-001` Sian3 tap/LT diagnostic log if used; `APSU-006-Rxx-CLEANUP-001` restore record. |
| Known blockers | Missing script revision for degraded-tap setup, unlabeled DUT/REF or side/lane endpoints, no repeatable degraded BER condition, missing Page 70h enable/restart trigger, missing BER threshold/window, or inability to restore nominal tap state. |

### APSU-007 - Bundled Lane Restart Domain

| Field | Content |
|---|---|
| Test ID and title | `APSU-007` - Verify restart-domain behavior for bundled lane restart. |
| Requirement class | In-scope formal Gate 3 validation when Page 70h exposes restart behavior or when bundled restart behavior supports a customer-facing claim. |
| Primitives used | Mandatory core: `PRIM-RUN-META`, `PRIM-EVIDENCE-PKG`. Conditional: `PRIM-P70H-MAP`, `PRIM-P70H-CONTROL`, `PRIM-P70H-POLL`, `PRIM-FEC-RECOVERY`. Diagnostic-only: `PRIM-DIAG-LT` for Sian3 restart-domain correlation. |
| Reused resources | `BR-005` mapping manifest; `APSU-001` enable sequence; `APSU-002` data-ready proof; Page 70h restart/control fields if implemented; Sian3 BERT/DUT traffic/FEC capture; optional Sian3 cAPI/debug status for lane-domain correlation. |
| Formal Page 70h action/read | Trigger the supported Page 70h restart or restart-equivalent action for a lane or lane-context inside the enabled Ethernet interface, confirm control acceptance, and poll Page 70h status for every lane in the expected restart domain. |
| Diagnostic calls | Sian3 cAPI/debug state may be used to correlate which lanes restarted and to explain Sian3 bundled behavior. It cannot replace Page 70h restart action/status or traffic/FEC recovery evidence. |
| Procedure outline | 1. Confirm the expected restart domain is frozen as the complete Ethernet interface lane set unless the release explicitly defines another isolation rule. 2. Bring the complete Ethernet interface to data-ready state using `APSU-001` and `APSU-002`. 3. Capture baseline Page 70h per-lane/interface status and traffic/FEC state. 4. Trigger Page 70h restart for one lane or restart context inside the interface. 5. Confirm control acceptance within the frozen timeout. 6. Poll Page 70h status for all lanes in the expected domain and adjacent/out-of-domain lanes if applicable. 7. Capture traffic/FEC interruption and recovery for the complete interface. 8. Capture optional Sian3 diagnostic restart/LT state. 9. Verify cleanup and return to data-ready state. |
| Expected observation | A Page 70h restart trigger inside the Sian3 bundled Ethernet interface produces restart/recovery behavior across the full enabled lane set, while unrelated interfaces or out-of-domain lanes remain unaffected. Page 70h status sequence is legal and traffic/FEC recovers according to the declared criterion. |
| Pass/fail criteria | `Pass` when the Page 70h restart is accepted, all lanes in the expected restart domain show the expected restart/recovery response, out-of-domain lanes remain stable, observed status ordering is legal, and traffic/FEC recovers. `Fail` when restart affects only an unintended subset, affects unrelated lanes, Page 70h status contradicts traffic/FEC, restart acceptance times out, or recovery does not meet criterion. `Blocked` when restart fields, restart-domain declaration, mapping, status polling, or traffic/FEC recovery evidence is missing. |
| Evidence artifacts | `APSU-007-Rxx-P70H-001` restart/status transaction log; `APSU-007-Rxx-DOMAIN-001` restart-domain comparison; `APSU-007-Rxx-FEC-001` traffic/FEC interruption and recovery log; `APSU-007-Rxx-DIAG-001` Sian3 diagnostic correlation if used; `APSU-007-Rxx-CLEANUP-001` final data-ready/restore record. |
| Known blockers | Missing Page 70h restart action, unclear restart-domain declaration, incomplete lane mapping, no out-of-domain observation path, missing traffic/FEC recovery criterion, or inability to restore a data-ready state after restart. |

### STR-001 - Quantified High-Loss Or Bounded Lab-Observed Attenuation

| Field | Content |
|---|---|
| Test ID and title | `STR-001` - Validate behavior over a quantified high-loss channel or bounded lab-observed attenuation case. |
| Requirement class | In-scope formal Gate 4 stress validation. Use `Bounded` claim wording unless insertion-loss profile or calibrated fixture characterization supports a quantified high-loss channel claim. |
| Primitives used | Mandatory core: `PRIM-RUN-META`, `PRIM-EVIDENCE-PKG`. Conditional: `PRIM-FAULT-SETUP`, `PRIM-P70H-CONTROL`, `PRIM-P70H-POLL`, `PRIM-FEC-RECOVERY`, `PRIM-P70H-MAP`. Diagnostic-only: `PRIM-DIAG-LT` if Sian3 state is used for root-cause correlation. |
| Reused resources | Current VOA/loss setup where available; Sian3 BERT/DUT setup; traffic/FEC BER capture; Page 70h host access profile; loss calibration records; setup photo/diagram with fixture/cable/VOA identity. |
| Formal Page 70h action/read | Under the declared loss condition, trigger or enable APSU/iLT through Page 70h, confirm control acceptance, poll Page 70h readiness/status, and correlate status with traffic/FEC recovery. |
| Diagnostic calls | Sian3 cAPI/debug link-training state may be captured only for diagnostic correlation. Loss setting and traffic/FEC evidence are external measurement evidence, not diagnostic CDB proof. |
| Procedure outline | 1. Declare whether the run is a quantified high-loss channel or bounded lab-observed attenuation case. 2. Record fixture/cable/VOA identity, attenuation setting, calibration timestamp, and insertion-loss profile or state that only bounded attenuation evidence is available. 3. Bring the link to baseline data-ready state and capture Page 70h and traffic/FEC baseline. 4. Apply the declared loss condition. 5. Trigger APSU/iLT through Page 70h if required or observe recovery under loss. 6. Poll Page 70h readiness/status and capture traffic/FEC BER over the declared window. 7. Record any diagnostic Sian3 state. 8. Restore nominal loss condition and archive evidence. |
| Expected observation | Page 70h status and external traffic/FEC evidence remain consistent under the declared loss condition. For a quantified high-loss channel claim, the loss path is documented by insertion-loss profile or calibrated fixture characterization. For a single VOA setting or incomplete loss characterization, the result is bounded to that lab-observed attenuation case. |
| Pass/fail criteria | `Pass` when Page 70h control/status and traffic/FEC evidence meet the declared recovery/readiness criterion under a fully characterized quantified high-loss channel. `Bounded` when Page 70h behavior passes but the loss evidence is limited to a specific calibrated VOA setting or lab-observed attenuation. `Fail` when Page 70h status contradicts traffic/FEC, recovery fails, loss setup is misrepresented, or APSU/iLT behavior is unstable under the declared condition. `Blocked` when loss characterization, mapping, Page 70h trigger/status, or traffic/FEC evidence is missing. |
| Evidence artifacts | `STR-001-Rxx-LOSS-001` loss calibration or bounded attenuation record; `STR-001-Rxx-P70H-001` Page 70h status/control log; `STR-001-Rxx-FEC-001` traffic/FEC BER log; `STR-001-Rxx-SETUP-001` setup photo/diagram; `STR-001-Rxx-DIAG-001` diagnostic state log if used. |
| Known blockers | Missing attenuation calibration, missing insertion-loss profile for a quantified high-loss claim, unclear fixture/cable identity, no stable BER measurement window, missing Page 70h status path, or inability to restore nominal loss condition. |

### STR-002 - Control-To-Traffic-Recovery Time

| Field | Content |
|---|---|
| Test ID and title | `STR-002` - Measure control-to-traffic-recovery time independently. |
| Requirement class | In-scope formal Gate 4 convergence-time validation. This row measures traffic/FEC recovery timing; Page 70h status publication latency remains covered by `P70H-006`. |
| Primitives used | Mandatory core: `PRIM-RUN-META`, `PRIM-EVIDENCE-PKG`. Conditional: `PRIM-P70H-CONTROL`, `PRIM-P70H-POLL`, `PRIM-FEC-RECOVERY`, `PRIM-P70H-MAP`; `PRIM-FAULT-SETUP` when a degraded/loss/fault condition creates the recovery scenario. Diagnostic-only: `PRIM-DIAG-LT` for Sian3 timing correlation. |
| Reused resources | `P70H-006` host timestamp and polling capability; `BR-008` control acceptance timeout table; Page 70h start/restart trigger; Sian3 BERT/DUT traffic/FEC capture; current timing hooks and external timer; optional diagnostic CDB/cAPI timestamps as supporting evidence. |
| Formal Page 70h action/read | Trigger APSU/iLT start or restart through Page 70h, confirm control acceptance, record the formal start timestamp, then capture Page 70h status polling as supporting management status evidence while external traffic/FEC recovery defines the stop timestamp. |
| Diagnostic calls | Diagnostic CDB, Sian3 cAPI, and internal LT timestamps may be captured to explain phases of recovery, but they do not start or stop the formal convergence-time measurement. |
| Procedure outline | 1. Confirm Page 70h trigger, `BR-008` timeout, traffic/FEC recovery criterion, timestamp resolution, and run clock alignment are frozen. 2. Establish starting condition: nominal restart, degraded-tap case, loss case, or other declared recovery scenario. 3. Capture baseline Page 70h and traffic/FEC state. 4. Execute Page 70h start/restart trigger and confirm control acceptance. 5. Mark start time at Page 70h control completion after acceptance confirmation. 6. Capture traffic/FEC continuously until the predeclared recovery criterion is met. 7. Mark stop time at external traffic/FEC recovery. 8. Record Page 70h status transition timestamps from `P70H-006` style polling as supporting evidence. 9. Calculate elapsed time and archive raw logs. |
| Expected observation | Control-to-traffic-recovery time is measured from a Page 70h-accepted trigger to external traffic/FEC recovery. Page 70h status transitions are consistent with traffic/FEC evidence but are not used as the stop condition. |
| Pass/fail criteria | `Pass` when elapsed control-to-traffic-recovery time meets the predeclared limit or bounded criterion, traffic/FEC recovery is stable over the declared window, and Page 70h status does not contradict recovery. `Fail` when recovery exceeds the declared limit, never reaches criterion, Page 70h reports recovery before traffic/FEC recovers, or timing evidence is inconsistent. `Blocked` when the trigger, acceptance confirmation, traffic/FEC recovery criterion, timestamping, or raw timing log is missing. |
| Evidence artifacts | `STR-002-Rxx-P70H-001` Page 70h trigger/status log; `STR-002-Rxx-FEC-001` traffic/FEC recovery log; `STR-002-Rxx-TIME-001` convergence-time calculation; `STR-002-Rxx-DIAG-001` diagnostic timing correlation if used. |
| Known blockers | Missing customer or release timing limit, missing recovery criterion, no synchronized timestamps, missing Page 70h trigger, missing control acceptance confirmation, unstable traffic/FEC measurement, or diagnostic-only timing being used as the formal timer. |

### STR-003 - Polarity Recovery Ordered Evidence

| Field | Content |
|---|---|
| Test ID and title | `STR-003` - Produce ordered polarity recovery raw evidence when polarity status is exposed through Page 70h or used in a customer claim. |
| Requirement class | Conditional formal Gate 4 validation when polarity control/status is Page 70h-exposed, affects Page 70h readiness/recovery behavior, or supports a customer-facing claim. Diagnostic-only when polarity behavior is available only through Sian3 cAPI/debug material and no claim depends on it. |
| Primitives used | Mandatory core: `PRIM-RUN-META`, `PRIM-EVIDENCE-PKG`. Conditional formal: `PRIM-FAULT-SETUP`, `PRIM-P70H-CONTROL`, `PRIM-P70H-POLL`, `PRIM-FEC-RECOVERY`, `PRIM-P70H-MAP`. Diagnostic-only: `PRIM-DIAG-LT` for Sian3 polarity state. |
| Reused resources | Feng polarity screencopies and scripts as procedure seed material; Sian3 BERT/DUT setup; traffic/FEC capture; Page 70h host access profile when polarity fields/actions are exposed; Sian3 diagnostic polarity state only for correlation. |
| Formal Page 70h action/read | If Page 70h exposes polarity control/status or a restart/status path that reflects polarity recovery, capture Page 70h action/status before, during, and after the induced polarity condition. If not exposed and no customer claim depends on it, mark the row `Diagnostic Only` or `Not Run`. |
| Diagnostic calls | Sian3 cAPI/debug polarity reads may be captured to identify induced polarity state and recovery path. They must be recorded as diagnostic-only unless the behavior is mapped through Page 70h or required by customer claim wording. |
| Procedure outline | 1. Confirm Page 70h polarity exposure or customer-claim requirement. 2. Capture baseline Page 70h readiness/status, traffic/FEC, and optional diagnostic polarity state. 3. Induce or configure the polarity condition using the reused lab procedure and record exact action, timestamp, side/lane/interface, and script/tool revision. 4. Capture traffic/FEC break or impairment if expected. 5. Trigger or observe Page 70h recovery path and poll status through declared interval. 6. Capture traffic/FEC recovery to the declared criterion. 7. Capture optional diagnostic polarity state after recovery. 8. Archive one ordered raw log tying setup, Page 70h status/action, traffic/FEC, and diagnostic evidence. |
| Expected observation | For a formal row, Page 70h status/action reflects legal recovery behavior and does not contradict traffic/FEC recovery. The ordered log shows the induced polarity condition, recovery sequence, and final data-ready evidence. Diagnostic Sian3 polarity state, if used, supports but does not replace Page 70h evidence. |
| Pass/fail criteria | `Pass` when Page 70h-exposed polarity recovery or mapped readiness/recovery behavior is legal, traffic/FEC recovers, and ordered evidence is complete. `Fail` when Page 70h contradicts traffic/FEC, recovery fails, status ordering is illegal, polarity evidence is unordered or screenshot-only for a formal claim, or diagnostic state contradicts Page 70h. `Blocked` when Page 70h exposure decision, induction method, mapping, traffic/FEC recovery criterion, or ordered raw logging is missing. `Diagnostic Only` when polarity is not Page 70h-exposed and no customer-facing claim depends on it. |
| Evidence artifacts | `STR-003-Rxx-POLARITY-001` ordered polarity setup/recovery log; `STR-003-Rxx-P70H-001` Page 70h status/action log when formal; `STR-003-Rxx-FEC-001` traffic/FEC break and recovery log; `STR-003-Rxx-DIAG-001` diagnostic polarity state if used. |
| Known blockers | Missing Page 70h polarity mapping for a formal claim, no controlled polarity induction method, screenshot-only evidence, missing ordered timestamps, missing traffic/FEC recovery criterion, or no cleanup/restore path. |

### STR-004 - Repeat Degraded-Tap Recovery With Labeled Endpoints

| Field | Content |
|---|---|
| Test ID and title | `STR-004` - Repeat degraded-tap recovery three times with labeled endpoints. |
| Requirement class | In-scope formal Gate 4 repeatability validation for degraded-tap APSU/iLT recovery. Existing Feng evidence is seed material and counts only if it satisfies this sheet's evidence requirements. |
| Primitives used | Mandatory core: `PRIM-RUN-META`, `PRIM-EVIDENCE-PKG`. Conditional: `PRIM-FAULT-SETUP`, `PRIM-P70H-CONTROL`, `PRIM-P70H-POLL`, `PRIM-FEC-RECOVERY`, `PRIM-P70H-MAP`. Diagnostic-only: `PRIM-DIAG-LT` for tap/LT correlation. |
| Reused resources | Same degraded-tap setup and Page 70h procedure as `APSU-006`; Feng script sequence as procedure seed; Sian3 BERT/DUT setup; traffic/FEC BER capture; diagnostic Sian3 tap/LT readback where available. |
| Formal Page 70h action/read | For each of three immutable runs, establish the same degraded-tap precondition, trigger APSU/iLT through Page 70h enable or restart, confirm control acceptance, poll Page 70h readiness/status, and capture final Page 70h state. |
| Diagnostic calls | Existing tap setup/readback scripts and Sian3 LT/tap diagnostics may confirm the precondition and explain recovery, but repeatability is judged from repeated Page 70h status behavior and traffic/FEC improvement. |
| Procedure outline | 1. Freeze the degraded-tap recipe, lane/interface mapping, endpoint labels, BER threshold/window, and cleanup procedure. 2. For each of three runs, assign a new immutable run number. 3. Capture DUT/REF or local/remote labels, side/lane labels, baseline Page 70h status, and baseline traffic/FEC. 4. Apply the same degraded-tap recipe and confirm readback. 5. Capture degraded pre-APSU BER. 6. Trigger APSU/iLT through Page 70h and confirm acceptance. 7. Poll Page 70h readiness/status and capture post-APSU BER. 8. Restore known-good state before the next run. 9. Compare all three runs for consistency and archive evidence. |
| Expected observation | All three runs show the same labeled setup and degraded-tap recipe, Page 70h trigger/status reaches the expected legal recovery/readiness state, and post-APSU traffic/FEC BER meets the declared criterion. Diagnostic tap/LT state, if used, is consistent with the repeated recovery narrative. |
| Pass/fail criteria | `Pass` when three complete runs meet the same Page 70h status and traffic/FEC recovery criteria with labeled endpoints and no evidence contradictions. `Fail` when any run fails recovery, produces inconsistent Page 70h status, lacks endpoint/lane labeling, contradicts traffic/FEC, or cannot be restored safely. `Blocked` when fewer than three compliant runs are available, endpoint labels are missing, the degraded-tap recipe changes without a new revision, or raw evidence is incomplete. |
| Evidence artifacts | `STR-004-R01..R03-SETUP-001` degraded-tap setup/readback logs; `STR-004-R01..R03-P70H-001` Page 70h trigger/status logs; `STR-004-R01..R03-FEC-001` before/after traffic/FEC logs; `STR-004-R01..R03-DIAG-001` diagnostic tap/LT logs if used; `STR-004-Rxx-SUMMARY-001` repeatability comparison. |
| Known blockers | Only one or two complete runs, historical runs missing Page 70h trigger/status, unlabeled DUT/REF or local/remote endpoints, different degraded-tap recipes across runs, missing BER windows, or missing cleanup evidence between runs. |

### STR-005 - Stable Release Temperature Points

| Field | Content |
|---|---|
| Test ID and title | `STR-005` - Validate stable release temperature points. |
| Requirement class | In-scope formal Gate 4 temperature validation when release notes or customer evidence claim APSU/iLT behavior at low, nominal, or high temperature. Chamber-only evidence produces `Bounded`, not a full release temperature claim. |
| Primitives used | Mandatory core: `PRIM-RUN-META`, `PRIM-EVIDENCE-PKG`. Conditional: `PRIM-FAULT-SETUP` for temperature setup, `PRIM-P70H-CONTROL`, `PRIM-P70H-POLL`, `PRIM-FEC-RECOVERY`, `PRIM-P70H-MAP`. Diagnostic-only: `PRIM-DIAG-LT` when Sian3 state is captured for root-cause correlation. |
| Reused resources | Current temperature chamber setup; prior 0 C, 45 C, and 70 C evidence as seed material only; measured module case-temperature logging; Page 70h host access profile; traffic/FEC BER capture; setup photo/diagram. |
| Formal Page 70h action/read | At each frozen stable temperature point, after measured module case temperature satisfies target band and dwell/stabilization criteria, trigger or observe APSU/iLT through Page 70h, poll readiness/status, and correlate with traffic/FEC evidence. |
| Diagnostic calls | Sian3 cAPI/debug state may be captured only to explain failures. Chamber setpoint is setup context and does not replace measured module case temperature. |
| Procedure outline | 1. Freeze release temperature points, measured module case-temperature target bands, dwell/stabilization criteria, and traffic/FEC recovery criterion. 2. For each temperature point, set chamber target and wait until measured module case temperature enters the target band and remains stable for the required dwell time. 3. Capture temperature timestamp, chamber setpoint, measured module case temperature, firmware/module/script revisions, and setup ID. 4. Capture baseline Page 70h and traffic/FEC state. 5. Trigger or observe Page 70h APSU/iLT behavior at the stable temperature point. 6. Poll Page 70h status and capture traffic/FEC BER over the declared window. 7. Record optional diagnostic Sian3 state. 8. Repeat for each frozen point and archive evidence. |
| Expected observation | Page 70h status/readiness and traffic/FEC evidence remain consistent at each frozen stable temperature point after measured module case temperature stabilization. Prior 0 C, 45 C, and 70 C logs may support planning only unless they match the frozen points and include required measured module case-temperature and Page 70h evidence. |
| Pass/fail criteria | `Pass` when every frozen release temperature point has measured module case-temperature stabilization evidence, Page 70h status/control evidence, and traffic/FEC evidence meeting the declared criterion. `Bounded` when Page 70h behavior passes but evidence is based only on chamber setpoint or a placeholder temperature point. `Fail` when Page 70h contradicts traffic/FEC, recovery/readiness fails at a frozen point, or measured temperature is outside the target band. `Blocked` when temperature points, stabilization criteria, measured module temperature logging, Page 70h status, or traffic/FEC evidence is missing. |
| Evidence artifacts | `STR-005-Rxx-TEMP-001` measured module temperature and dwell record; `STR-005-Rxx-P70H-001` Page 70h status/control log; `STR-005-Rxx-FEC-001` traffic/FEC BER log; `STR-005-Rxx-SETUP-001` chamber/setup record; `STR-005-Rxx-DIAG-001` diagnostic state log if used. |
| Known blockers | Missing measured module case-temperature sensor/log, reliance on chamber setpoint only, unfrozen release temperature points, missing dwell criteria, unstable temperature during test, missing Page 70h status path, or no traffic/FEC evidence at a temperature point. |

### STR-006 - Active Temperature-Shift Behavior

| Field | Content |
|---|---|
| Test ID and title | `STR-006` - Validate behavior during active temperature shift when claimed or exposed. |
| Requirement class | Conditional Gate 4 validation required only when Page 70h exposes temperature-shift behavior, readiness/recovery during active transition is part of the release/customer claim, or prior lab-observed shift behavior is used in customer-facing evidence. Otherwise classify as `Not Run` or `Diagnostic Only`. |
| Primitives used | Mandatory core: `PRIM-RUN-META`, `PRIM-EVIDENCE-PKG`. Conditional: `PRIM-FAULT-SETUP` for temperature transition, `PRIM-P70H-POLL`, `PRIM-FEC-RECOVERY`, `PRIM-P70H-MAP`; `PRIM-P70H-CONTROL` only if a Page 70h action is performed during the shift. Diagnostic-only: `PRIM-DIAG-LT` if Sian3 state is captured. |
| Reused resources | Temperature chamber ramp/transition capability; measured module case-temperature logging; Page 70h host access profile; traffic/FEC capture; prior temperature-shift observations only as seed material unless they satisfy this sheet's evidence requirements. |
| Formal Page 70h action/read | Capture Page 70h readiness/status before shift, during ramp or transition, and after dwell at the target temperature. If Page 70h control is exercised during the transition, confirm control acceptance and poll status with declared intervals. |
| Diagnostic calls | Sian3 cAPI/debug state may be captured to explain behavior during the transition. Chamber setpoint and diagnostic state do not replace Page 70h status plus measured module temperature and traffic/FEC evidence. |
| Procedure outline | 1. Confirm the customer/release claim or Page 70h exposure that makes active temperature-shift validation in scope. 2. Freeze start and target temperature conditions, ramp/transition profile if controlled, measured module case-temperature logging, dwell requirement after target, and traffic/FEC criterion. 3. Capture before-shift Page 70h status, traffic/FEC, and measured module case temperature. 4. Start the chamber transition and continuously or periodically log measured module case temperature, Page 70h status, and traffic/FEC. 5. Record any Page 70h control action during transition if used. 6. Continue logging after target dwell criterion is met. 7. Archive ordered temperature, Page 70h, traffic/FEC, and diagnostic logs. |
| Expected observation | Page 70h status and traffic/FEC evidence remain consistent before, during, and after the temperature transition. Any transient readiness/recovery behavior is legal and bounded by declared status publication and traffic/FEC recovery criteria. |
| Pass/fail criteria | `Pass` when active transition evidence meets the claimed behavior with measured module temperature, Page 70h status, and traffic/FEC agreement. `Fail` when Page 70h contradicts traffic/FEC, readiness/recovery fails during a claimed transition, status ordering is illegal, or evidence is chamber-setpoint-only for a formal claim. `Blocked` when the transition profile, measured module temperature logging, Page 70h status, or traffic/FEC capture is missing. `Not Run` or `Diagnostic Only` when active temperature-shift behavior is not claimed or Page 70h-exposed. |
| Evidence artifacts | `STR-006-Rxx-TEMP-001` measured temperature transition log; `STR-006-Rxx-P70H-001` Page 70h status/control log; `STR-006-Rxx-FEC-001` traffic/FEC transition log; `STR-006-Rxx-DIAG-001` diagnostic state log if used. |
| Known blockers | No active transition claim, missing measured module temperature during ramp, uncontrolled or undocumented transition profile, missing traffic/FEC capture during ramp, missing Page 70h status polling, or only screenshot/chamber-setpoint evidence. |

### STR-007 - Non-LT-Frame Partner Behavior

| Field | Content |
|---|---|
| Test ID and title | `STR-007` - Validate behavior with a non-LT-frame partner when exposed or claimed. |
| Requirement class | Conditional implementation-reference Gate 4 coverage. Formal only when Page 70h exposes the related status/fault/recovery path or when a customer-facing claim requires non-LT-frame partner behavior. Otherwise classify as `Diagnostic Only` or `Not Run`. |
| Primitives used | Mandatory core: `PRIM-RUN-META`, `PRIM-EVIDENCE-PKG`. Conditional formal: `PRIM-FAULT-SETUP`, `PRIM-P70H-POLL`, `PRIM-FEC-RECOVERY`, `PRIM-P70H-MAP`; `PRIM-P70H-CONTROL` if a Page 70h restart/control action is used. Diagnostic-only: `PRIM-DIAG-LT`. |
| Reused resources | Link-partner setup capable of withholding or failing LT-frame behavior; partner logs; Page 70h host access profile; Sian3 BERT/DUT traffic/FEC capture where applicable; Sian3 diagnostic state for root-cause correlation. |
| Formal Page 70h action/read | If formal, capture Page 70h readiness/fault/recovery status before, during, and after the non-LT-frame partner condition. If a restart is supported and part of the scenario, trigger it through Page 70h and confirm control acceptance. |
| Diagnostic calls | Partner logs and Sian3 cAPI/debug LT state may be used to confirm the non-LT-frame condition and explain Page 70h behavior. They do not decide formal pass/fail unless the row is explicitly diagnostic-only. |
| Procedure outline | 1. Confirm Page 70h exposure or customer claim that makes this behavior in scope. 2. Configure or select a link partner that does not provide expected LT frames or training-frame lock condition. 3. Capture baseline Page 70h status, traffic/FEC, partner identity/class, and partner logs. 4. Apply the non-LT-frame condition and poll Page 70h readiness/fault/recovery status. 5. Trigger Page 70h restart/control if the scenario requires it and confirm acceptance. 6. Capture traffic/FEC behavior and partner logs during the condition. 7. Restore a normal partner/training condition and confirm recovery if required. 8. Archive Page 70h, partner, traffic/FEC, and diagnostic evidence. |
| Expected observation | For a formal row, Page 70h exposes a legal and non-misleading readiness/fault/recovery status for the non-LT-frame condition and does not report data-ready while traffic/FEC or partner evidence indicates failure. Diagnostic/partner logs explain the condition without replacing Page 70h evidence. |
| Pass/fail criteria | `Pass` when Page 70h-exposed fault/recovery behavior is legal, does not contradict partner or traffic/FEC evidence, and recovery/restoration behavior meets the declared criterion. `Fail` when Page 70h reports false readiness, hides the non-LT-frame condition, status ordering is illegal, restart/control acceptance fails, or traffic/FEC contradicts Page 70h. `Blocked` when Page 70h exposure/claim, partner setup, partner logs, traffic/FEC, or status mapping is missing. `Diagnostic Only` or `Not Run` when the behavior is not Page 70h-exposed and no claim depends on it. |
| Evidence artifacts | `STR-007-Rxx-P70H-001` Page 70h status/control log; `STR-007-Rxx-PARTNER-001` partner identity and LT-frame condition log; `STR-007-Rxx-FEC-001` traffic/FEC behavior log; `STR-007-Rxx-DIAG-001` Sian3 diagnostic state if used; `STR-007-Rxx-CLEANUP-001` restoration record if recovery is part of the scenario. |
| Known blockers | No available non-LT-frame partner or mode, missing partner logs, no Page 70h status/fault exposure for a formal claim, missing traffic/FEC observation, inability to restore normal link behavior, or overbroad interop wording from one partner condition. |

### STR-008 - Partner Squelch And Signal-Loss Behavior

| Field | Content |
|---|---|
| Test ID and title | `STR-008` - Validate partner squelch and signal-loss behavior when it affects Page 70h readiness or recovery. |
| Requirement class | In-scope formal Gate 4 fault/recovery validation when partner squelch, signal loss, or equivalent external partner fault affects Page 70h readiness/recovery or a customer-facing claim. |
| Primitives used | Mandatory core: `PRIM-RUN-META`, `PRIM-EVIDENCE-PKG`. Conditional formal: `PRIM-FAULT-SETUP`, `PRIM-P70H-POLL`, `PRIM-FEC-RECOVERY`, `PRIM-P70H-MAP`; `PRIM-P70H-CONTROL` if Page 70h restart/recovery control is used. Diagnostic-only: `PRIM-DIAG-LT`. |
| Reused resources | Partner setup capable of squelch or signal-loss injection; partner logs; traffic/FEC capture; Page 70h host access profile; optional Sian3 cAPI/debug state for root-cause correlation. |
| Formal Page 70h action/read | Capture Page 70h readiness/fault/recovery status before, during, and after the partner fault trigger. If Page 70h restart or recovery control is part of the procedure, trigger it through Page 70h and confirm control acceptance. |
| Diagnostic calls | Partner logs and traffic/FEC evidence define the external trigger and link effect. Sian3 cAPI/debug state may explain internal behavior, but Page 70h status and external traffic/FEC determine formal readiness/recovery correctness. |
| Procedure outline | 1. Confirm the partner fault trigger, Page 70h status mapping, traffic/FEC recovery criterion, and cleanup/restoration path. 2. Bring the interface to data-ready state. 3. Capture baseline Page 70h status, partner state, and traffic/FEC. 4. Induce partner squelch, signal loss, or equivalent partner fault and timestamp the external event. 5. Poll Page 70h readiness/fault/recovery status at the declared interval. 6. Capture traffic/FEC loss or impairment. 7. Remove the fault or execute Page 70h recovery/restart control if required. 8. Capture Page 70h recovery status and traffic/FEC recovery. 9. Archive partner, Page 70h, traffic/FEC, and diagnostic logs. |
| Expected observation | Page 70h reports legal readiness/fault/recovery status in response to the externally observed partner fault and does not report data-ready while traffic/FEC or partner evidence indicates signal loss. After fault removal or recovery action, Page 70h and traffic/FEC return to consistent ready state within declared timing/recovery criteria. |
| Pass/fail criteria | `Pass` when Page 70h status sequence is legal, tracks the externally observed partner fault without false data-ready indication, and recovery matches traffic/FEC evidence. `Fail` when Page 70h hides the fault, reports data-ready during traffic/FEC loss, recovery status contradicts external evidence, control acceptance fails, or recovery does not meet criterion. `Blocked` when the partner fault trigger, Page 70h status mapping, partner logs, traffic/FEC capture, or cleanup path is missing. |
| Evidence artifacts | `STR-008-Rxx-PARTNER-001` partner squelch/signal-loss trigger log; `STR-008-Rxx-P70H-001` Page 70h status/control log; `STR-008-Rxx-FEC-001` traffic/FEC loss and recovery log; `STR-008-Rxx-DIAG-001` diagnostic state if used; `STR-008-Rxx-CLEANUP-001` fault removal/recovery record. |
| Known blockers | No controllable partner squelch/signal-loss mechanism, missing partner logs, missing Page 70h fault/readiness mapping, no traffic/FEC observation, no recovery path, or inability to distinguish partner fault from local module fault. |

### STR-009 - Recovery Reason And Event Count Read-Clear

| Field | Content |
|---|---|
| Test ID and title | `STR-009` - Validate recovery reason and recovery event count read-clear behavior when exposed through Page 70h. |
| Requirement class | Conditional formal Gate 4 validation when recovery reason or recovery event count is Page 70h-exposed or included in a customer-facing claim. Diagnostic-only when only Sian3 cAPI/debug exposes the counters and no Page 70h/customer claim depends on them. |
| Primitives used | Mandatory core: `PRIM-RUN-META`, `PRIM-EVIDENCE-PKG`. Conditional formal: `PRIM-FAULT-SETUP`, `PRIM-P70H-POLL`, `PRIM-P70H-MAP`; `PRIM-P70H-CONTROL` if a Page 70h recovery/restart action is used. Diagnostic-only: `PRIM-DIAG-LT` for Sian3 recovery counter correlation. |
| Reused resources | Page 70h host access profile; Page 70h recovery reason/count fields if implemented; Sian3 diagnostic recovery reason/event count where available; fault or recovery injection setup from `STR-008`, `APSU-007`, or another declared trigger. |
| Formal Page 70h action/read | Inject or trigger a defined recovery event, read Page 70h recovery reason and event count, then perform the defined read-clear sequence and read again to verify clear behavior or persistence behavior as specified by the frozen Page 70h mapping. |
| Diagnostic calls | Sian3 cAPI/debug recovery counters may be captured before and after Page 70h reads to correlate internal behavior, but they do not replace Page 70h first-read/second-read evidence. |
| Procedure outline | 1. Confirm Page 70h recovery reason/count exposure and read-clear semantics in the frozen map. 2. Capture baseline Page 70h counters/status and optional diagnostic counters. 3. Inject a declared recovery event or execute a Page 70h restart/recovery action. 4. Confirm the event occurred using Page 70h status and external evidence when applicable. 5. Read Page 70h recovery reason and event count for the first-read value. 6. Execute the defined clear behavior, such as read-clear on first read or explicit clear if specified. 7. Read the fields a second time and verify cleared or expected persistent value. 8. Capture diagnostic correlation and archive ordered logs. |
| Expected observation | Page 70h first read reports the expected recovery reason/count for the injected event. The second read shows the defined cleared or persistent behavior. Diagnostic counters, if captured, are consistent with the Page 70h-visible behavior or explain a failure. |
| Pass/fail criteria | `Pass` when Page 70h recovery reason/count fields report the event, follow the frozen read-clear semantics, and do not contradict external or diagnostic evidence. `Fail` when fields do not update, clear incorrectly, fail to clear when required, clear early, report an impossible reason/count, or contradict Page 70h recovery status. `Blocked` when Page 70h exposure, read-clear semantics, recovery injection, or raw ordered read logging is missing. `Diagnostic Only` when counters are not Page 70h-exposed and no customer-facing claim depends on them. |
| Evidence artifacts | `STR-009-Rxx-P70H-001` ordered Page 70h recovery counter reads; `STR-009-Rxx-FAULT-001` recovery event injection log; `STR-009-Rxx-DIAG-001` diagnostic recovery counter correlation if used; `STR-009-Rxx-CLEAR-001` read-clear comparison. |
| Known blockers | Missing Page 70h recovery fields, unclear read-clear semantics, no controlled recovery event, missing ordered timestamps, diagnostic-only counters for a formal claim, or inability to distinguish counter clear from event absence. |

### STR-010 - Slicer Modes And Timer Behavior Characterization

| Field | Content |
|---|---|
| Test ID and title | `STR-010` - Characterize slicer modes and timer behavior where supported. |
| Requirement class | `Diagnostic Only` by default. Promote to conditional formal Gate 4 validation only when slicer mode or timer behavior is exposed through Page 70h, affects Page 70h behavior, or appears in release/customer claim wording. |
| Primitives used | Mandatory core: `PRIM-RUN-META`, `PRIM-EVIDENCE-PKG`. Conditional formal: `PRIM-P70H-CONTROL`, `PRIM-P70H-POLL`, `PRIM-P70H-MAP` when Page 70h exposes controls/status. External evidence: `PRIM-FEC-RECOVERY` only if behavior affects traffic/recovery claims. Diagnostic-only: `PRIM-DIAG-LT` for Sian3 slicer/timer state. |
| Reused resources | Sian3 cAPI/debug slicer mode and timer controls/readbacks; Page 70h host access profile if exposed; traffic/FEC capture when a mode/timer claim affects recovery behavior; Sian3 AN/source material for supported modes/timer expectations. |
| Formal Page 70h action/read | If formal, write/read Page 70h slicer mode or timer controls/status, confirm control acceptance/readback, and observe the mapped behavior through Page 70h status and external traffic/FEC when relevant. If not exposed and unclaimed, capture diagnostic characterization only. |
| Diagnostic calls | Use Sian3 cAPI/debug controls and readbacks to characterize auto/NR/ER slicer modes and timer settings. These calls remain diagnostic unless Page 70h exposure or customer claim promotes the behavior. |
| Procedure outline | 1. Determine whether slicer/timer behavior is Page 70h-exposed or claimed. 2. If not, mark `Diagnostic Only` and capture optional Sian3 characterization with script/tool revision. 3. If formal, freeze Page 70h field mapping, supported value ranges, timeout/readback expectations, and cleanup state. 4. Capture baseline Page 70h and diagnostic state. 5. Apply each supported Page 70h mode/timer setting, confirm acceptance/readback, and observe relevant status/traffic behavior. 6. Restore default/nominal settings. 7. Archive Page 70h, traffic/FEC, and diagnostic logs. |
| Expected observation | Diagnostic-only runs produce bounded characterization without release pass/fail effect. Formal runs show Page 70h control/readback/status consistency for supported slicer/timer values and no traffic/FEC contradiction when behavior affects recovery. |
| Pass/fail criteria | `Diagnostic Only` when behavior is not Page 70h-exposed and no claim depends on it. `Pass` when Page 70h-exposed controls/readbacks work for supported values, status behavior is legal, cleanup succeeds, and external evidence does not contradict it. `Fail` when Page 70h exposes the behavior but cannot control/read back it, unsupported values mutate state unexpectedly, recovery behavior contradicts Page 70h, or cleanup fails. `Blocked` when a formal claim lacks Page 70h mapping, supported value ranges, timeout/readback rules, or observation path. |
| Evidence artifacts | `STR-010-Rxx-DIAG-001` Sian3 slicer/timer characterization log; `STR-010-Rxx-P70H-001` Page 70h transaction log when formal; `STR-010-Rxx-FEC-001` traffic/FEC evidence if relevant; `STR-010-Rxx-CLEANUP-001` restore record. |
| Known blockers | Missing Page 70h exposure decision, unclear supported value ranges, no cleanup path, Sian3-only evidence for a formal claim, or customer wording that implies timer/slicer behavior without a mapped Page 70h proof. |

### INT-001 - Non-Sian3 Link-Partner Interoperability

| Field | Content |
|---|---|
| Test ID and title | `INT-001` - Validate APSU/iLT with at least one non-Sian3 link partner. |
| Requirement class | Conditional formal Gate 5 interoperability validation. Use `Bounded` when only one non-Sian3 partner identity or partner class is covered; use `Blocked` if link-partner interoperability is claimed but no suitable partner/setup is available. |
| Primitives used | Mandatory core: `PRIM-RUN-META`, `PRIM-EVIDENCE-PKG`. Conditional formal: `PRIM-P70H-MAP`, `PRIM-P70H-CONTROL`, `PRIM-P70H-POLL`, `PRIM-FEC-RECOVERY`. Diagnostic-only: `PRIM-DIAG-LT` when Sian3 or vendor state is captured for correlation. |
| Reused resources | Current Sian3 BERT/DUT lab setup as much as possible; CMIS Page 70h host/exerciser/scripted access profile; non-Sian3 partner module, BERT, or equivalent link partner; traffic/FEC BER capture; partner-side logs or screenshots; optional Sian3 cAPI/debug CDB correlation logs. |
| Formal Page 70h action/read | Use Page 70h as the formal control/status interface to enable, restart, poll, and verify APSU/iLT behavior for the Ethernet interface and full enabled lane set under the tested partner setup. Capture ordered Page 70h transactions, status transitions, readiness/path-up indication, and any exposed fault/recovery fields. |
| Diagnostic calls | Use vendor CDB, lab-only debug CDB, Sian3 cAPI, or partner tooling only to explain correlation, setup, or failure triage. These calls do not replace Page 70h control/status evidence or traffic/FEC evidence. |
| Procedure outline | 1. Record non-Sian3 partner identity or partner class, revision, port/interface mode, cable/fixture/loss path, Ethernet interface, enabled lane set, and setup diagram/photo. 2. Freeze the Page 70h host access profile and mapping manifest for the interop setup. 3. Capture baseline Page 70h status and traffic/FEC before APSU/iLT action. 4. Execute Page 70h enable or restart over the complete enabled lane set. 5. Poll Page 70h status until stable readiness/path-up or declared timeout. 6. Capture partner logs and traffic/FEC behavior during and after convergence. 7. Disable/restore the link through Page 70h or the declared cleanup path. 8. Produce bounded release wording if partner coverage is limited to one identity or class. |
| Expected observation | Page 70h control is accepted, status sequence is legal, readiness/path-up state aligns with partner logs and traffic/FEC, and the Ethernet interface recovers without contradictions between Page 70h, partner evidence, and external traffic/FEC. One-partner evidence supports only a bounded link-partner interop claim. |
| Pass/fail criteria | `Pass` when the tested non-Sian3 partner setup shows legal Page 70h control/status behavior, readiness/path-up aligns with partner and traffic/FEC evidence, cleanup succeeds, and the claim scope is fully covered by the tested partner set. `Bounded` when the tested setup passes but coverage is limited to one partner identity/class or a narrow operating condition. `Fail` when Page 70h behavior fails, status contradicts partner or traffic/FEC evidence, APSU/iLT cannot recover the tested link, or cleanup fails. `Blocked` when partner identity/class, Page 70h mapping, partner logs, traffic/FEC evidence, or host access profile is missing for an in-scope interop claim. `Not Run` when link-partner interoperability is intentionally outside the current release scope and no customer-facing claim depends on it. |
| Evidence artifacts | `INT-001-Rxx-P70H-001` ordered Page 70h transaction/status log; `INT-001-Rxx-PARTNER-001` partner identity/class and partner-side log or screenshot; `INT-001-Rxx-FEC-001` traffic/FEC BER log; `INT-001-Rxx-SETUP-001` setup photo/diagram and lane/interface manifest; `INT-001-Rxx-DIAG-001` diagnostic correlation log if used; `INT-001-Rxx-RELEASE-001` bounded release wording when applicable. |
| Known blockers | No non-Sian3 partner available, unclear partner identity/class, missing partner-side observability, missing Page 70h support/status mapping, no traffic/FEC capture, incomplete Ethernet-interface lane coverage, unmanaged setup changes between runs, or release wording that claims broader interoperability than the tested partner coverage supports. |

### INT-002 - Host-Management Interoperability

| Field | Content |
|---|---|
| Test ID and title | `INT-002` - Validate Page 70h behavior with at least one non-Lumentum or customer-like CMIS host/exerciser. |
| Requirement class | Conditional formal Gate 5 host-management interoperability validation. Use `Bounded` when coverage is limited to one host/exerciser identity, one scripted host access profile, or one setup class; use `Blocked` if host-management interoperability is claimed but no suitable host/exerciser/scripted profile is available. |
| Primitives used | Mandatory core: `PRIM-RUN-META`, `PRIM-EVIDENCE-PKG`. Conditional formal: `PRIM-P70H-MAP`, `PRIM-P70H-PERM`, `PRIM-P70H-CONTROL`, `PRIM-P70H-POLL`, `PRIM-FEC-RECOVERY` when control/readiness behavior is exercised. Diagnostic-only: `PRIM-DIAG-LT` only when Sian3 or vendor state is captured to explain host-visible behavior. |
| Reused resources | Current available CMIS host, CMIS exerciser, or internal Python/lab-automation setup as much as possible; Page 70h access script or transaction logger; existing Page 70h byte-map, permission, control, and status test fragments; traffic/FEC capture when host actions affect link readiness; optional diagnostic correlation through vendor CDB, debug CDB, or Sian3 cAPI. |
| Formal Page 70h action/read | Execute Page 70h reads/writes through the selected host/exerciser/scripted profile. Record page select, bank select, byte/range read sizes, byte/range write sizes, polling interval, retry behavior, error handling, and multi-byte monitor/status read sequence. Page 70h transaction results and resulting Page 70h status are the formal management evidence. |
| Diagnostic calls | Use Sian3 cAPI, vendor CDB, debug CDB, or internal module logs only to explain differences between expected and observed host-visible behavior. Diagnostic calls do not replace the selected host/exerciser/scripted profile transaction log. |
| Procedure outline | 1. Assign a host access profile label and classify it as real customer host, customer-like exerciser, CMIS lab exerciser, or scripted host access profile. 2. Record host/exerciser/software identity, script revision, access timing, page/bank select method, read/write size limits, retry/error policy, and multi-byte read sequence. 3. Run Page 70h byte-map and permission smoke reads through the selected profile. 4. Execute one nominal Page 70h APSU/iLT control action and poll Page 70h status through the same profile. 5. Exercise declared retry/error handling using a safe invalid or unsupported transaction from the frozen invalid-write rules. 6. Read multi-byte monitor/status fields using the declared sequence and check coherency. 7. Capture traffic/FEC evidence when host control changes link behavior. 8. Produce bounded release wording if the profile is not a real customer host stack or if only one setup class is covered. |
| Expected observation | The selected host/exerciser/scripted profile can access Page 70h consistently, control actions and polling behave legally, reserved/invalid behavior follows frozen CMIS rules, multi-byte reads remain coherent, and any link-affecting host actions align with traffic/FEC evidence. Scripted-profile evidence supports only a bounded host-management interop claim. |
| Pass/fail criteria | `Pass` when the tested host-management claim scope is fully covered by the selected host/exerciser set and Page 70h access, controls, status polling, error handling, multi-byte coherency, and cleanup all behave legally. `Bounded` when behavior passes only for one host/exerciser identity, scripted profile, or setup class. `Fail` when Page 70h access is unreliable, legal host operations are rejected, reserved/invalid operations mutate state incorrectly, polling/status behavior is misleading, multi-byte coherency fails, link evidence contradicts Page 70h, or cleanup fails. `Blocked` when the host access profile, transaction logging, Page 70h mapping, host/exerciser identity, retry/error policy, or multi-byte read sequence is missing for an in-scope claim. `Not Run` when host-management interoperability is intentionally outside current release scope and no customer-facing claim depends on it. |
| Evidence artifacts | `INT-002-Rxx-HOST-001` host/exerciser/scripted profile description; `INT-002-Rxx-P70H-001` ordered Page 70h transaction log; `INT-002-Rxx-ERR-001` retry/error and invalid-write behavior log; `INT-002-Rxx-COH-001` multi-byte coherency read log; `INT-002-Rxx-FEC-001` traffic/FEC evidence when link state changes; `INT-002-Rxx-DIAG-001` diagnostic correlation if used; `INT-002-Rxx-RELEASE-001` bounded release wording when applicable. |
| Known blockers | No available host/exerciser/scripted profile, unclear profile classification, missing transaction logging, missing page/bank select details, missing retry/error policy, missing multi-byte read sequence, no safe invalid-write case, incomplete Page 70h mapping, or release wording that claims broader customer-host interoperability than the tested profile supports. |

### INT-003 - Page 70h To Sian3 Diagnostic Correlation

| Field | Content |
|---|---|
| Test ID and title | `INT-003` - Correlate Page 70h status/control behavior to Sian3 cAPI and debug state for diagnosis only. |
| Requirement class | `Diagnostic Only`. This row supports mapping confidence and failure triage but cannot override Page 70h formal results from Gate 2, Gate 3, Gate 4, `INT-001`, or `INT-002`. |
| Primitives used | Mandatory core: `PRIM-RUN-META`, `PRIM-EVIDENCE-PKG`. Diagnostic-only: `PRIM-DIAG-LT`, `PRIM-VCDB-COEX` when vendor CDB state is captured for comparison. Conditional formal evidence is not assigned to this row. |
| Reused resources | `1p6_sian3_h5_python/yapp/sian3.py` `SIAN3.get_lktrn_info`, `SIAN3.get_lktrn_stat`, `SIAN3.get_apsu_enable`, `SIAN3.set_lktrn_info`, `SIAN3.set_apsu_enable`; `1p6_sian3_h5_python/yapp/cdb.py` `CDB.CMDA200h`, `CDB.CMDA201h`, `CDB.CMDA082h`, `CDB.CMDA083h`; Page 70h transaction logger; optional traffic/FEC logs only when needed to understand a contradiction. |
| Formal Page 70h action/read | Read or reuse the ordered Page 70h control/status logs from the formal row being diagnosed. If a paired diagnostic run is needed, repeat the same Page 70h access pattern and mark the paired Page 70h log as diagnostic-correlation context unless it is also part of a separately executed formal row. |
| Diagnostic calls | Capture Sian3 cAPI/debug CDB/vendor CDB state immediately before and after the Page 70h action or status transition under investigation. Record symbol name, command ID where applicable, parameters, side/lane/Ethernet-interface mapping, timestamp, and returned state. |
| Procedure outline | 1. Link the diagnostic run to a formal row and immutable run number. 2. Record why correlation is needed: mapping confidence, unexpected Page 70h status, traffic/FEC contradiction, coexistence question, or implementation debug. 3. Capture baseline Page 70h state. 4. Capture baseline diagnostic state using the declared functions or CDB commands. 5. Execute or reference the Page 70h action/status transition under study. 6. Capture post-action Page 70h state and diagnostic state with ordered timestamps. 7. Compare side/lane/Ethernet-interface mapping, APSU enable state, LT status, readiness/path-up state, precode state when relevant, and recovery/fault state when exposed. 8. File the correlation result as diagnostic-only evidence and link any formal failure back to the formal row. |
| Expected observation | Diagnostic state should explain or align with Page 70h state for the mapped Ethernet interface and enabled lane set. Any mismatch becomes a triage finding or possible Page 70h failure in the linked formal row, not a standalone pass/fail result for this diagnostic row. |
| Pass/fail criteria | `Diagnostic Only` for all executions of this row. A useful correlation log can support root-cause analysis, mapping confidence, or failure triage. It cannot change a formal Page 70h `Fail` to `Pass`, cannot convert missing Page 70h exposure into formal coverage, and cannot support a customer-facing Page 70h claim by itself. |
| Evidence artifacts | `INT-003-Rxx-P70H-001` linked Page 70h transaction/status log; `INT-003-Rxx-DIAG-001` Sian3 cAPI/debug CDB state log; `INT-003-Rxx-VCDB-001` vendor CDB comparison log when used; `INT-003-Rxx-MAP-001` side/lane/Ethernet-interface mapping comparison; `INT-003-Rxx-TRIAGE-001` diagnostic conclusion and linked formal-row impact. |
| Known blockers | Missing linked formal row/run number, missing timestamps, ambiguous side/lane mapping, diagnostic function or CDB command unavailable, missing symbol/command/parameter record, or attempted use of diagnostic evidence as the formal Page 70h result. |

### INT-004 - Final Evidence Package Completeness Audit

| Field | Content |
|---|---|
| Test ID and title | `INT-004` - Audit final Page 70h APSU/iLT evidence package completeness. |
| Requirement class | In-scope formal Gate 5 audit row for any release or customer-facing APSU/iLT statement. This row does not retest behavior; it verifies evidence completeness, traceability, and customer/internal evidence boundaries. |
| Primitives used | Mandatory core: `PRIM-RUN-META`, `PRIM-EVIDENCE-PKG`. No diagnostic-only primitive can close this row by itself; diagnostic artifacts are checked only for correct labeling and traceability. |
| Reused resources | Evidence artifacts from `BR-*`, `P70H-*`, `APSU-*`, `STR-*`, and `INT-*` rows; internal evidence archive; customer-facing evidence package; setup photos or diagrams; script/tool revision records; Page 70h transaction logs; traffic/FEC logs; timing logs; partner/host logs; diagnostic CDB/cAPI logs when used. |
| Formal Page 70h action/read | None. This is an audit of completed or intentionally omitted evidence. Page 70h transaction logs from each formal row are checked for presence, ordering, timestamping, mapping context, run number, and artifact ID linkage. |
| Diagnostic calls | None. Existing diagnostic artifacts are reviewed only to confirm they are marked diagnostic-only, linked to the correct formal row, and excluded from customer-facing proof unless explicitly approved. |
| Procedure outline | 1. Generate the final test-result inventory covering every planned row and status label. 2. Confirm each executed formal or bounded row has immutable run number, firmware/module identity, Ethernet interface, enabled lane set, setup ID, host access profile, script/tool versions, and reviewer trace. 3. Confirm every raw artifact has a stable artifact ID in test/run/type/sequence format and a durable raw path or archive ID. 4. Confirm Page 70h logs, traffic/FEC logs, timing logs, partner logs, host/exerciser logs, setup photos, and diagnostic logs exist where required by each sheet. 5. Confirm `Blocked`, `Not Run`, and `Diagnostic Only` rows have explicit reasons and no accidental customer-facing claim. 6. Confirm customer-facing excerpts are sanitized and trace to stable internal evidence IDs. 7. Confirm internal debug CDB, Sian3 cAPI, internal lab paths, and sensitive implementation details remain internal unless explicitly approved. 8. Record audit result and open evidence defects. |
| Expected observation | The final evidence package can trace each release/customer statement to stable internal artifact IDs and can explain every missing or bounded area without exposing internal debug material as customer proof. |
| Pass/fail criteria | `Pass` when every in-scope result has complete required artifacts, stable IDs, durable raw paths or archive IDs, setup/script versions, status labels, reviewer trace, and customer/internal evidence separation. `Fail` when a customer-facing claim lacks traceable evidence, raw evidence cannot be located, internal debug evidence is used as customer proof without approval, or artifact IDs are inconsistent. `Blocked` when the audit cannot complete because a required row result, evidence inventory, archive location, or reviewer trace is missing. `Bounded` is not used as the audit result; bounded claims are inputs checked by this audit. |
| Evidence artifacts | `INT-004-Rxx-INVENTORY-001` final row/result inventory; `INT-004-Rxx-ARTIFACTS-001` artifact ID to raw path/archive map; `INT-004-Rxx-CUSTOMER-001` customer-facing excerpt and claim traceability checklist; `INT-004-Rxx-INTERNAL-001` internal-only debug/sensitive evidence list; `INT-004-Rxx-DEFECTS-001` evidence defects and disposition record; `INT-004-Rxx-REVIEW-001` reviewer sign-off or blocker record. |
| Known blockers | Missing raw archive access, missing setup/script versions, artifact IDs not assigned consistently, customer excerpts not traceable to internal evidence, unreviewed internal debug material in customer-facing content, missing reviewer trace, or incomplete row/result inventory. |

### INT-005 - Final Release Decision Summary And Bounded Release Notes

| Field | Content |
|---|---|
| Test ID and title | `INT-005` - Produce final release decision summary and bounded release notes. |
| Requirement class | In-scope formal Gate 5 release-decision row for any Page 70h APSU/iLT release or customer-facing note. This row summarizes reviewed evidence and claim scope; it does not introduce new behavior evidence. |
| Primitives used | Mandatory core: `PRIM-RUN-META`, `PRIM-EVIDENCE-PKG`. Inputs come from `INT-004` plus completed row results. Diagnostic-only inputs can be listed only as diagnostic support and cannot create or upgrade a customer-facing claim. |
| Reused resources | `INT-004` evidence inventory; final test matrix; artifact ID map; customer-facing evidence package; bounded release-note wording; P0/P1/P2 release criteria; reviewer sign-off record; internal-only evidence list. |
| Formal Page 70h action/read | None. The summary references Page 70h evidence from completed formal rows by stable artifact ID and raw path/archive metadata. Missing Page 70h evidence cannot be replaced by diagnostic CDB, Sian3 cAPI, vendor CDB, screenshots, or narrative statements. |
| Diagnostic calls | None. Existing diagnostic artifacts may be listed under diagnostic-only evidence, mapping confidence, or root-cause support, but not as formal proof for Page 70h behavior. |
| Procedure outline | 1. Import the audited row/result inventory from `INT-004`. 2. For each release/customer-facing claim, assign one status label: `Pass`, `Fail`, `Blocked`, `Not Run`, `Bounded`, or `Diagnostic Only`. 3. List verified claims with the exact Page 70h rows and stable internal evidence IDs that support them. 4. List bounded claims with exact scope limits, such as one partner class, one host/exerciser profile, bounded lab-observed attenuation, or measured temperature coverage limits. 5. List intentionally unclaimed items and the reason they are not claimed. 6. List blocked items with missing prerequisite or evidence defect. 7. List diagnostic-only evidence separately, including Sian3 cAPI/debug CDB/vendor CDB correlation and any optional Sian3 behavior characterization. 8. Draft customer-facing wording using sanitized summaries and customer-safe excerpts only. 9. Confirm no numeric scores, percentage coverage, or weighted summaries are used. 10. Record reviewer approval or release blocker disposition. |
| Expected observation | The release decision is understandable from status labels and claim-to-evidence traceability alone. Customer-facing wording states only what was verified or bounded by evidence and omits or explicitly avoids unsupported claims. Internal debug evidence remains internal unless approved for release. |
| Pass/fail criteria | `Pass` when the summary uses only approved status labels, every customer-facing claim traces to stable internal evidence IDs, bounded claims are explicitly scoped, blocked and unclaimed items are visible, diagnostic-only evidence is separated, and reviewer approval is recorded. `Fail` when unsupported customer-facing claims remain, score/percentage language is used, evidence IDs are missing, bounded limits are hidden, diagnostic evidence is used as formal proof, or customer/internal evidence boundaries are violated. `Blocked` when `INT-004` is incomplete, release criteria are unresolved, reviewer approval is missing, or required claim-to-evidence mapping cannot be produced. |
| Evidence artifacts | `INT-005-Rxx-SUMMARY-001` final status-label release decision summary; `INT-005-Rxx-CLAIMS-001` claim-to-evidence traceability table; `INT-005-Rxx-BOUNDED-001` bounded release-note wording; `INT-005-Rxx-UNCLAIMED-001` intentionally unclaimed and blocked item list; `INT-005-Rxx-CUSTOMER-001` customer-facing package excerpt set; `INT-005-Rxx-REVIEW-001` reviewer approval or blocker disposition. |
| Known blockers | Incomplete `INT-004` audit, unresolved Page 70h failures, missing artifact IDs, unapproved customer-facing wording, overbroad interoperability/high-loss/temperature wording, unseparated diagnostic evidence, score or percentage language, or missing reviewer decision. |

## Lab Setup And Instrumentation

Required setup:

- DUT: next-release 1.6T 2xDR4 FRO module firmware image under test.
- Reference path: Sian3 BERT/DUT setup covering `TP0 -> TP1` and `TP4 -> TP5`.
- Link-partner interoperability path: at least one non-Sian3 link partner capable of exercising APSU/iLT behavior.
- Host-management interoperability path: use the current available CMIS host, exerciser, or scripted setup as much as possible; at least one non-Lumentum or customer-like CMIS host/exerciser must exercise Page 70h access, polling, control, and status behavior before making a bounded host-management claim.
- CMIS host or exerciser capable of Page 70h reads/writes, timestamped transaction logging, declared polling intervals, and recording missed or failed reads.
- Calibrated VOA or loss fixture with recorded attenuation, insertion-loss profile, or calibrated fixture characterization appropriate to the claim being made.
- Temperature chamber with setpoint, measured module case-temperature logging, and ability to verify target band plus dwell time.
- Traffic/FEC BER capture with per-lane pre-FEC BER and post-FEC BER.
- Pre-declared traffic/FEC recovery criterion for each test case, including Ethernet interface, enabled lane set, BER threshold, and observation window.
- Diagnostic access to vendor CDB, P253.66 debug CDB, and Sian3 cAPI when needed for correlation.

Every execution attempt must receive a unique immutable run number and record firmware version, module serial, partner identity, script version, operator, physical setup, pre-execution checklist revision, mapping manifest revision, Ethernet interface identity, enabled lane set, lane/path labels, and instrument configuration.

Normal APSU/iLT validation uses the complete Ethernet interface lane set. Partial-lane enablement is reserved for negative or isolation tests and must declare the expected behavior before execution.

## Evidence Package Requirements

Each formal test must produce these artifacts when applicable:

- Page 70h transaction log with timestamp, page, bank, byte/range, read/write value, return status, lane/interface context, script version, and any missed or failed reads.
- Mapping manifest tying Page 70h bank, side, and lane fields to Ethernet interface, enabled lane set, host/media side, DUT/REF labels, physical fixture ports, and traffic/FEC lane IDs, including source, revision, lab annotations, and review record.
- Traffic/FEC log with lane identity, pre-FEC BER, post-FEC BER, measurement window, and traffic pattern.
- Traffic/FEC recovery criterion record with Ethernet interface, enabled lane set, BER threshold, observation window, and pass/fail outcome.
- Timing log with explicit Page 70h start/restart trigger, control acceptance confirmation, control acceptance timeout when applicable, and control-to-traffic-recovery time; status publication latency start/stop markers using Page 70h control completion after control acceptance confirmation or independently observed external event as start and first stable Page 70h status read as stop; declared maximum polling interval, actual observed polling intervals, missed or failed reads, observed status sequence, and legal status ordering source; first training, path-ready, path-up, diagnostic CDB, or Sian3 cAPI timestamps may be captured as supporting status evidence only.
- Loss calibration record with VOA attenuation, insertion-loss profile or calibrated fixture characterization when claiming a quantified high-loss channel, cable or fixture identity, calibration timestamp, and bounded lab-observed attenuation label when only a single VOA setting is available.
- Temperature record with chamber setpoint, measured module case temperature, predeclared target band, dwell time, stabilization timestamp, measurement timestamp, and bounded lab-observed temperature label when only chamber setpoint is available.
- Recovery log with recovery reason, recovery event count, read-clear behavior, and restart sequence.
- Diagnostic correlation log when vendor CDB, P253.66 debug CDB, or Sian3 cAPI is used.
- Reusable diagnostic harness record with script/tool revision, reused function or command list, evidence role, and confirmation that the harness is not the formal pass/fail interface.
- Invalid test run record for isolated host/exerciser failures, including immutable run number, reason, retained raw evidence, and replacement rerun linkage.
- Host access profile for host-management interoperability, including setup class, scripted profile label when implemented by internal Python or similar lab automation, page/bank select behavior, byte/range read/write sizes, polling interval, retry behavior, error handling, and multi-byte monitor/status read sequence.
- Setup photo or diagram with DUT/REF, host/media side, and lane/path labels.
- Raw evidence retention record assigning stable evidence artifact IDs to raw Page 70h transaction logs, traffic/FEC logs, timing logs, setup photos, relevant screenshots, host/script versions, generated summaries, and stable external archive IDs or paths when large raw captures remain in controlled storage. Artifact IDs use deterministic test/run/type/sequence format, such as `P70H-006-R01-TIMING-001`, and do not encode pass/fail status.
- Customer-facing evidence package with sanitized summaries, bounded claims, selected customer-safe excerpts or screenshots, and claim-to-evidence traceability to stable internal evidence artifact IDs; full raw logs with internal debug CDB, Sian3 cAPI, internal lab paths, or sensitive implementation details remain internal under stable archive IDs.

## Release Gates

| Gate | Name | Purpose | Exit criteria |
|---|---|---|---|
| Gate 0 | Baseline freeze and draft/source diff | Prevent stale assumptions. | Matrix frozen; draft re-diff complete; changes recorded; named engineering reviewer sign-off complete. |
| Gate 1 | Firmware and Page 70h bring-up readiness | Prove the image is ready for formal validation. | Firmware identity, Page 70h discovery, APSU-capable gating, defaults, resets, non-APSU compatibility, mapping manifest, invalid-write declaration, control acceptance timeout declarations, and named engineering reviewer sign-off pass. |
| Gate 2 | Page 70h register/access validation | Prove the standardized CMIS interface before behavior claims. | Byte ranges, permissions, reserved bytes, invalid writes, lane/bank mapping, CMIS data coherency, and status publication behavior pass. |
| Gate 3 | APSU/iLT functional validation | Prove nominal Page 70h APSU/iLT behavior. | Enable/disable, data-ready APSU state, legal observed status sequence, RTS, path-up status values, training pattern, precoding, tap/BER improvement, and bundle behavior pass. |
| Gate 4 | Stress, fault, and recovery validation | Close current evidence gaps and classify Sian3 AN behavior as required implementation-reference coverage or optional vendor-behavior characterization. | Quantified high-loss channel, control-to-traffic-recovery time, polarity, repeatability, temperature, partner faults, recovery counters, and restart behavior pass or are explicitly bounded. |
| Gate 5 | Interop and evidence package | Prove customer-relevant behavior and auditability. | Link-partner and host-management interoperability complete or explicitly bounded; host access profile recorded; internal evidence archive and customer-facing evidence package are complete; release criteria are reviewed. |

## Pre-Execution Freeze Checklist

Before formal lab execution, freeze these items with named engineering reviewer sign-off. Tool-generated documentation can prepare the checklist, but human approval is required before Gate 0/Gate 1 exit. Missing in-scope items make the affected test `Blocked`; do not invent expectations during execution. Any post-freeze change creates a new checklist revision; prior runs remain valid only with a reviewer no-impact record, otherwise affected tests rerun under the new revision. Normative IEEE/OIF changes touching byte definitions, status meaning, legal ordering, timers, or reserved behavior default to rerun or re-review for affected tests; a no-impact decision must document why the tested fields are untouched.

- Source and draft versions: IEEE P802.3dj, OIF Page 70h, Sian3 AN/source material, customer-note plan, and release-candidate firmware identity.
- Release/interface spec mapping: Page 70h field mapping, APSU/iLT state mapping, legal status ordering, supported command/control classes, and customer-claim scope.
- Invalid-write declaration: non-reserved invalid control behavior, invalid lane-mask behavior, unsupported-application behavior, coexistence invalid-write behavior, and CMIS reserved field behavior confirmation.
- Control acceptance timeouts: per supported command/control class, using CMIS/OIF values where defined and release/interface spec values where not defined.
- Mapping manifest: Page 70h bank, side, and lane fields mapped to Ethernet interface, enabled lane set, host/media side, DUT/REF labels, physical fixture ports, and traffic/FEC lane IDs.
- Host access profile: setup class, scripted profile label when applicable, page/bank selection, byte/range read/write sizes, polling interval, retry behavior, error handling, and multi-byte monitor/status read sequence.
- Polling and status criteria: declared polling intervals, status publication latency limit or bounded first-release criterion, observed status sequence expectation, and legal status ordering source.
- Traffic/FEC recovery criteria: Ethernet interface, enabled lane set, BER threshold, observation window, pre-FEC/post-FEC capture, and pass/fail rule.
- Temperature criteria: release temperature points, measured module case-temperature target bands, dwell/stabilization criteria, and active temperature-shift definition when claimed or exposed through Page 70h.
- Loss criteria: quantified high-loss channel characterization level or bounded lab-observed attenuation label, including calibration source and timestamp.
- Evidence identity and retention: immutable run numbering, evidence artifact ID format, raw evidence retention storage or archive IDs, customer-facing evidence package boundary, and claim-to-evidence traceability.
- Sign-off and change-control record: named engineering reviewer, sign-off date, checklist revision, any explicitly bounded release claims accepted before execution, post-freeze checklist changes, normative-change impact review when applicable, reviewer no-impact decisions, and rerun linkage for affected tests.

## Detailed Test Matrix

| Test ID | Gate | Objective | Reference source | Interface under test | External evidence / diagnostic correlation paths | Required evidence | Gap mitigated |
|---|---|---|---|---|---|---|---|
| STD-001 | Gate 0 | Freeze source versions and matrix baseline. | IEEE/OIF/Sian3/customer-note baselines | Page 70h planning matrix | None | Source version list and matrix revision record. | Prevent stale requirements. |
| STD-002 | Gate 0 | Re-diff latest drafts and source material before execution. | Latest available IEEE/OIF drafts and updated Sian3 source material | Page 70h planning matrix | None | Diff summary with accepted matrix updates. | Draft or source drift. |
| BR-001 | Gate 1 | Record firmware identity and build configuration. | Release candidate metadata | Page 70h | Vendor CDB/debug CDB only for identity correlation | Firmware version, build metadata, module serial, feature flags. | Build ambiguity. |
| BR-002 | Gate 1 | Verify Page 70h presence and APSU-capable application gating. | OIF Page 70h | Page 70h | CMIS application advertisement | Page 70h discovery log for APSU and non-APSU apps, including capability advertisement, non-APSU not-capable/default read behavior if readable, and proof that active APSU/iLT controls are not exposed as supported for non-APSU applications. | Page 70h exposure errors. |
| BR-003 | Gate 1 | Verify default APSU/iLT states after reset and power transitions. | OIF Page 70h, customer-note defaults | Page 70h | Module logs | Reset, power-cycle, low-power, data-path-reset, and module-reset logs. | Default/reset ambiguity. |
| BR-004 | Gate 1 | Verify non-APSU applications remain backward compatible. | OIF draft | Page 70h and normal CMIS app behavior | Traffic/FEC counters | Non-APSU app bring-up and traffic logs, plus rejected or no-state-change Page 70h write attempts per frozen invalid-write declaration when Page 70h is readable. | Non-APSU regression. |
| BR-005 | Gate 1 | Freeze and verify host/media lane inventory and mapping manifest. | OIF Page 70h | Page 70h | Sian3 cAPI diagnostic correlation | Mapping manifest exported from firmware/test tooling when possible, or hand-authored with version and Gate 1 review record; lab annotations for fixture ports and DUT/REF labels; lane/bank mapping log tying Page 70h bank, side, and lane fields to Ethernet interface, enabled lane set, host/media side, physical fixture ports, and traffic/FEC lane IDs. | Lane mapping ambiguity. |
| BR-006 | Gate 1 | Validate vendor CDB and Page 70h coexistence during the transition period. | Customer-note plan, Page 70h release plan | Page 70h | Vendor CDB transaction logs | Representative coexistence coverage using ordered mixed-session Page 70h/vendor CDB control and readback log through CMIS I2C-MCI, covering at least one enable/disable control, one restart/control action when supported, one status/readback path, and one non-reserved invalid control class; evidence proves one shared effective APSU/iLT state keyed by Ethernet interface, side, lane set, and control field; same keyed readback through both surfaces; later ordered transaction wins only for the same key; non-reserved invalid-write behavior is consistent with no partial disagreement; CMIS reserved fields follow CMIS reserved field behavior; and Page 70h remains formal pass/fail. True concurrent or high-rate race testing is not required for this coexistence claim. | Coexistence validation. |
| BR-007 | Gate 1 | Freeze invalid-write declaration before formal Page 70h validation. | Firmware release/interface spec, OIF Page 70h | Page 70h | None | Invalid-write declaration covering unsupported controls, invalid lane masks, unsupported applications, and cross-surface coexistence writes, plus confirmation that reserved bytes and bits follow CMIS reserved field behavior. For non-reserved invalid controls, explicit errors are preferred where CMIS allows, but no state change is acceptable when declared. | Test-time expectation drift. |
| BR-008 | Gate 1 | Freeze control acceptance timeouts before command-driven validation. | CMIS/OIF timeout requirements, firmware release/interface spec | Page 70h | None | Control acceptance timeout declaration for each supported command/control class, using CMIS/OIF values where defined and release/interface spec values where not defined. | Open-ended command acceptance. |
| P70H-001 | Gate 2 | Validate Page 70h byte ranges `128-131`, `132-151`, `152-191`, and `192-230`. | OIF Page 70h | Page 70h | None | Read/write map with expected permissions. | Page 70h mis-map. |
| P70H-002 | Gate 2 | Verify reserved bytes `231-255` and reserved bits follow CMIS reserved field behavior. | OIF Page 70h, CMIS reserved field behavior | Page 70h | None | Baseline read, attempted writes, readback showing stable reserved fields, and adjacent/status readback showing no side effects. | Reserved byte/bit behavior. |
| P70H-003 | Gate 2 | Verify non-reserved invalid writes and invalid lane masks follow the frozen invalid-write declaration. | OIF Page 70h, firmware release/interface spec | Page 70h | Module logs | Invalid-write declaration reference, transaction log, return status, and post-state readback showing explicit error where allowed or declared no state change, with no partial mutation. | Invalid control handling. |
| P70H-004 | Gate 2 | Verify Page 70h host/media side and per-lane mapping against the frozen mapping manifest. | OIF Page 70h, Sian3 AN | Page 70h | Sian3 cAPI diagnostic correlation | Page 70h per-lane operation with diagnostic side/lane correlation and traffic/FEC lane ID confirmation against the mapping manifest. | DUT/REF and side labeling. |
| P70H-005 | Gate 2 | Verify CMIS data coherency for multi-byte monitors and status. | CMIS data coherency, OIF Page 70h | Page 70h | Host-script retry logs diagnostic only | Repeated multi-byte read snapshots under stable and changing states showing no torn or mixed-generation monitor/status value is exposed as valid; any retry sequence is logged but does not mask a valid-looking torn value. | Stale or torn status. |
| P70H-006 | Gate 2 | Measure Page 70h status publication latency. | OIF Page 70h | Page 70h | BERT timing capture; diagnostic CDB/cAPI timestamps supporting only | Predeclared latency limit, or first-release measured/bounded/non-contradictory criterion; control acceptance confirmation and timeout for command-driven changes; start timestamp from Page 70h control completion after acceptance confirmation or independently observed external event; stop timestamp from first stable Page 70h status read; declared maximum polling interval, actual polling intervals, missed or failed reads, invalid test run classification when applicable, and transition log. | Status latency ambiguity. |
| P70H-007 | Gate 2 | Verify Page 70h access during DPSM transitions. | DPSM/APSU state-machine source | Page 70h | Module state logs | Access log during DPInitialized, DPTxTurnOn, DPActivated, and deactivation. | DP state interaction. |
| APSU-001 | Gate 3 | Enable and disable APSU/iLT per host/media lane. | OIF Page 70h, customer-note plan | Page 70h | Vendor CDB/debug CDB correlation | Per-lane control acceptance confirmation, applicable control acceptance timeout, enable/readback, active-state logs, and control acceptance failure classification when a supported command returns success without confirmation. | Current vendor CDB migration. |
| APSU-002 | Gate 3 | Verify data-ready APSU state is not inferred from `DPActivated` alone. | IEEE/OIF/Sian3 AN | Page 70h | Traffic/FEC counters | DP state, Page 70h readiness, path-up status values, observed status sequence, and traffic correlation log showing no data-ready APSU state before traffic/FEC recovery criterion is met. | Full APSU path readiness. |
| APSU-003 | Gate 3 | Verify local/remote RTS and ready-bit transitions. | IEEE/OIF legal status ordering; release/interface spec mapping when needed | Page 70h | Sian3 cAPI diagnostic correlation only | RTS, local ready, remote ready, path-up transition log, legal status ordering source, and observed status sequence showing legal ordering for observed transitions without requiring every transient state. | Readiness status exposure. |
| APSU-004 | Gate 3 | Verify training pattern control/readback and PRBS13/PRBS31 behavior. | OIF Page 70h, Sian3 AN | Page 70h | BERT pattern detection, Sian3 cAPI | Pattern command/readback and BERT observation log. | Training-pattern gap. |
| APSU-005 | Gate 3 | Verify precoding request/readback behavior when exposed through Page 70h or used in a customer claim. | Sian3 AN, customer-note precoding support | Page 70h | Vendor CDB, Sian3 cAPI | Page 70h precode command/readback and diagnostic correlation. | Required implementation-reference coverage for precode mapping. |
| APSU-006 | Gate 3 | Verify tap optimization improves BER under degraded tap setup. | Sian3 AN, Feng evidence | Page 70h | BERT/FEC counters, Sian3 cAPI | Before/after taps, BER, and Page 70h status log. | Selected LT behavior through Page 70h. |
| APSU-007 | Gate 3 | Verify restart-domain behavior for bundled lane restart. | Sian3 AN | Page 70h | Sian3 cAPI diagnostic correlation | One-lane restart command, Ethernet interface restart-domain response, and all-lane bundle response log. | Required implementation-reference coverage for bundle restart. |
| STR-001 | Gate 4 | Validate behavior over a quantified high-loss channel or bounded lab-observed attenuation case. | Customer request, verification gap | Page 70h | Loss calibration, BERT/FEC counters | Insertion-loss profile or calibrated fixture characterization for quantified high-loss channel claims; single calibrated VOA attenuation allowed only as bounded lab-observed attenuation; fixture/cable identity, calibration timestamp, Page 70h status, BER, and recovery log. | Quantified high-loss proof or bounded attenuation evidence. |
| STR-002 | Gate 4 | Measure control-to-traffic-recovery time independently. | Customer request, verification gap | Page 70h | External timer, BERT/FEC counters | Page 70h start/restart trigger with control acceptance confirmation, pre-declared traffic/FEC recovery criterion, traffic/FEC recovery timestamp, elapsed time, and optional supporting status-transition timestamps. | Convergence time as currently meant by customer request. |
| STR-003 | Gate 4 | Produce ordered polarity recovery raw evidence when polarity status is exposed through Page 70h or used in a customer claim. | Sian3 AN, Feng evidence | Page 70h | BERT/FEC counters, Sian3 cAPI | Traffic break, Page 70h command, polarity status, recovery, and traffic log. | Required implementation-reference coverage for polarity. |
| STR-004 | Gate 4 | Repeat degraded-tap recovery three times with labeled endpoints. | Customer request, Feng evidence gap | Page 70h | BERT/FEC counters, Sian3 cAPI | Three run logs with DUT/REF or local/remote labels. | Repeatability and endpoint labeling. |
| STR-005 | Gate 4 | Validate release temperature points. | Product/customer temperature requirement; Feng evidence placeholders | Page 70h | Chamber logs, BERT/FEC counters | Frozen low, nominal, and high release temperature points; temperature stabilization criterion for each point; measured module case temperature as pass/fail evidence; proof the module reached target band and completed dwell before Page 70h APSU/iLT actions begin; chamber setpoint as setup context; placeholder status of prior 0 C, 45 C, and 70 C evidence unless adopted by the release plan; Page 70h status, taps, and BER logs. | Temperature-corner coverage. |
| STR-006 | Gate 4 | Validate active temperature-shift behavior when exposed through Page 70h or used in a customer claim. | Sian3 AN, Feng email evidence | Page 70h | Chamber logs, Sian3 cAPI, BERT/FEC counters | Active shift definition, such as 10 C to 60 C when adopted; measured module case temperature before shift, during ramp/transition, and after dwell; FIR/status before shift, failed or accepted FIR change, LT restart, new FIR, Page 70h status, traffic/FEC, and BER logs. Stable endpoint-only behavior is covered by release temperature points in `STR-005`. | Required implementation-reference coverage when claimed; otherwise optional vendor-behavior characterization. |
| STR-007 | Gate 4 | Validate behavior with non-LT frame partner. | Sian3 AN | Page 70h | Partner logs, Sian3 cAPI | Restart/status log with no training-frame lock condition. | Non-LT partner restart. |
| STR-008 | Gate 4 | Validate partner squelch and signal-loss behavior when it affects Page 70h readiness or recovery. | Sian3 AN | Page 70h | Partner logs, BERT/FEC counters | Squelch trigger, signal-loss status, restart behavior, Page 70h readiness/recovery status, and recovery log. | Required implementation-reference coverage for fault handling. |
| STR-009 | Gate 4 | Validate recovery reason and recovery event count read-clear behavior when exposed through Page 70h. | Sian3 AN | Page 70h | Sian3 cAPI diagnostic correlation | Recovery injection, Page 70h read, second read after clear, and diagnostic correlation. | Required implementation-reference coverage for recovery counters. |
| STR-010 | Gate 4 | Characterize slicer modes and timer behavior where supported. | Sian3 AN | Page 70h if exposed; otherwise diagnostic only | Sian3 cAPI, BERT/FEC counters | Auto/NR/ER mode logs and timer override/readback/behavior logs. | P2 by default; promote to P1/P0 only if exposed through Page 70h or used in a customer claim. |
| INT-001 | Gate 5 | Validate APSU/iLT with at least one non-Sian3 link partner. | IEEE/OIF interoperability expectation | Page 70h | Partner logs, traffic/FEC counters | Link-partner interop setup, partner identity/class, Page 70h status, traffic, and error logs; bounded release wording if only one non-Sian3 partner is covered. | Link-partner interoperability bounded to covered partner class. |
| INT-002 | Gate 5 | Validate Page 70h behavior with at least one non-Lumentum or customer-like CMIS host/exerciser. | OIF Page 70h host-management expectation | Page 70h | Host transaction logs | Current available CMIS host, exerciser, or scripted setup used as much as possible; host/exerciser identity/class; scripted host access profile label when implemented by internal Python or similar lab automation; host access profile covering page/bank select behavior, byte/range read/write sizes, polling interval, retry behavior, error handling, and multi-byte monitor/status read sequence; Page 70h access/control/status logs and error logs; bounded release wording if only one customer-like host/exerciser or scripted setup class is covered. | Host-management interoperability bounded to covered host/exerciser class. |
| INT-003 | Gate 5 | Correlate Page 70h status to Sian3 cAPI for diagnosis only. | Sian3 AN | Page 70h | P253.66 debug CDB, Sian3 cAPI | Side-by-side Page 70h and diagnostic status log. | Mapping confidence. |
| INT-004 | Gate 5 | Audit final evidence package completeness. | Verification plan | Page 70h logs and all lab artifacts | None | Evidence checklist signed off by engineering reviewer, including stable evidence artifact IDs in test/run/type/sequence format, with raw filenames, paths, or external archive IDs as metadata for transaction logs, traffic/FEC logs, timing logs, setup photos, relevant screenshots, host/script versions, and generated summaries. | Auditability. |
| INT-005 | Gate 5 | Produce final release decision summary and bounded release notes. | Verification plan | Page 70h | All artifacts | Label-only release decision summary using `Pass`, `Fail`, `Blocked`, `Not Run`, `Bounded`, and `Diagnostic Only`; verified claims, unverified topics, intentionally omitted claims, bounded release notes, customer-facing evidence package containing only sanitized summaries and customer-safe excerpts/screenshots, and claim-to-evidence traceability from each customer-facing claim to stable internal evidence artifact IDs. Numeric scores or percentage coverage summaries are not used. | Release decision traceability. |

## Release Criteria

### P0 Release Blockers

Any of these blocks a Page 70h APSU/iLT release claim:

- Page 70h is absent for APSU-capable applications, gated incorrectly, or exposes active APSU/iLT controls as supported for non-APSU applications.
- Page 70h byte ranges are mis-mapped.
- Reserved bytes or bits change on attempted write, are unstable on read, or produce side effects.
- Invalid-write declaration is missing, incomplete, or contradicted by Page 70h behavior.
- Control acceptance timeout declarations are missing for supported command/control classes that need them.
- Multi-byte Page 70h monitors or status values violate CMIS data coherency or expose torn data as valid.
- Mapping manifest is missing, ambiguous, unreviewed when hand-authored, or contradicted by Page 70h, diagnostic, fixture, or traffic/FEC evidence.
- Defaults after reset or power cycle do not match the expected state.
- Representative coexistence coverage for ordered mixed-session Page 70h/vendor CDB writes is missing when coexistence is part of the release.
- Page 70h cannot control or report supported APSU/iLT state.
- Command-driven tests lack control acceptance confirmation before timing or status polling is treated as formal evidence.
- A supported Page 70h command/control returns success but never produces control acceptance confirmation.
- A supported write-only or self-clearing Page 70h command/control exceeds its control acceptance timeout without the next legal observed status transition.
- Nominal supported cases cannot reach expected data-ready APSU state, path-up status value, or RTS status through Page 70h.
- Legal status ordering source is missing or based only on diagnostic behavior when IEEE/OIF or frozen release/interface mapping is required.
- Observed status sequence contains an illegal transition or reports data-ready APSU state before the traffic/FEC recovery criterion is met.
- Status publication latency is unmeasured, unbounded by a declared polling interval, exceeds a predeclared limit, hides missed or failed reads, has repeated missed or failed reads, or creates an evidence contradiction inside the declared polling window.
- Page 70h disagrees with traffic/FEC evidence in a way that cannot be resolved.
- Page 70h status contradicts external measurement evidence, even if one side appears to show a passing link.
- Non-APSU applications regress, or readable Page 70h behavior for non-APSU applications fails to show not-capable/default status and no APSU/iLT state mutation.
- Quantified high-loss channel claims are made without insertion-loss profile or calibrated fixture characterization, bounded lab-observed attenuation is generalized as channel-loss compliance, or control-to-traffic-recovery claims are made without independent timing evidence.
- Release temperature points are not frozen before Gate 4 when temperature coverage is part of the release claim.
- Temperature stabilization criterion is missing, or APSU/iLT actions start before measured module case temperature reaches target band and completes dwell.
- Full release temperature claims are made from chamber setpoint only, without measured module case temperature evidence.
- Host-management interoperability is claimed without a frozen host access profile, without labeling an internal Python/lab-automation profile as scripted, or without bounding the claim to the covered host/exerciser or scripted setup class.
- A post-freeze checklist change affects setup, expected behavior, or claim scope and affected tests are not rerun under the new revision or covered by a reviewer no-impact record.
- A post-freeze normative IEEE/OIF change touches tested byte definitions, status meaning, legal ordering, timers, or reserved behavior without rerun, re-review, or documented reviewer no-impact rationale.

### P1 Engineering Confidence Items

These should pass or be explicitly bounded in release notes:

- Repeatability across at least three runs.
- Release temperature points.
- Ordered polarity recovery.
- Recovery reason and recovery event count.
- Bundled restart.
- Partner fault behavior.
- Link-partner interoperability beyond the bounded first non-Sian3 partner class.
- Host-management interoperability beyond the bounded first customer-like host/exerciser class.
- Active temperature-shift and LT restart behavior when claimed or exposed through Page 70h.
- Sian3 AN behavior that is required because the release depends on it, exposes it through Page 70h, or uses it in a customer-facing claim.
- Vendor CDB and Page 70h coexistence during the transition period.
- Full cross-product Page 70h/vendor CDB coexistence coverage when not required by a customer claim.

### P2 Follow-Up Items

These improve confidence but should not block release unless tied to a customer claim:

- Additional link-partner types beyond the bounded first non-Sian3 partner class.
- Real customer host-stack coverage beyond the bounded first customer-like host/exerciser class.
- Larger temperature/loss sweep.
- Automation polish.
- Additional correlation between Page 70h and Sian3 cAPI diagnostics.
- More compact customer-safe report packaging.
- Optional Sian3 vendor-behavior characterization that is not exposed through Page 70h and not used in customer-facing claims.

Optional vendor-behavior characterization is P2 by default. Promote it to P1 or P0 only when the behavior is exposed through Page 70h, affects the formal pass/fail interface, or supports a customer-facing claim.

Customer requests drive coverage in this plan. Customer claims require supporting evidence and must be bounded or omitted when the relevant evidence remains incomplete.

The final release decision summary must use release decision status labels only: `Pass`, `Fail`, `Blocked`, `Not Run`, `Bounded`, and `Diagnostic Only`. Do not use numeric scores, percentage coverage, or weighted coverage summaries. `Diagnostic Only` is reserved for Sian3 cAPI, debug CDB, vendor-only characterization, or supporting evidence that cannot decide formal pass/fail; Page 70h interface-under-test rows must use `Pass`, `Fail`, `Blocked`, `Not Run`, or `Bounded`. `Bounded` is allowed only when Page 70h behavior passes for the tested scope but the release or customer claim must be limited because external evidence scope is narrow; it must not be used when Page 70h behavior itself fails. `Blocked` means the test is in release scope but cannot proceed because a prerequisite is missing or failed. `Not Run` means the test is intentionally outside current release scope and the reason is recorded.

Gate 5 must produce bounded release notes for any customer request or optional behavior that is not fully covered by release evidence, including bounded lab-observed attenuation cases, bounded lab-observed temperature cases, quantified high-loss channel, release temperature points, control-to-traffic-recovery time, optional Sian3 behavior, one-partner link interoperability, one-host host-management interoperability, and interop gaps.

Gate 5 must retain or identify the raw evidence behind each summarized result. A stable external path or archive ID is acceptable for large raw captures when access-controlled and durable; copy artifacts into the repo only for small, customer-safe screenshots or distilled logs. A summary table without linked or identified raw logs, screenshots, setup photos, and script versions is not sufficient for auditability.

Gate 5 must keep full raw logs with internal debug CDB, Sian3 cAPI, internal lab paths, or sensitive implementation details in the internal evidence archive unless explicitly approved for release. The customer-facing evidence package should use sanitized summaries, bounded claims, and selected customer-safe excerpts or screenshots.

Every customer-facing claim must trace to one or more stable internal evidence artifact IDs. Artifact IDs encode test ID, immutable run number, artifact type, and sequence number, and do not encode pass/fail status. Every execution attempt, including an invalid run, receives a new run number; reruns link back to the replaced invalid run rather than reusing its number. Raw filenames, paths, and external archive IDs are retained as artifact metadata, not used as the primary claim traceability key. Claims without traceable internal evidence must be omitted or marked intentionally unclaimed.

## Gap Mitigation Map

| Prior gap | Planned mitigation |
|---|---|
| Page 70h not implemented in current firmware | Gate 1 and Gate 2 validate Page 70h presence, mapping, and access behavior. |
| Detailed readiness/status not customer-accessible | Gate 2 and Gate 3 require Page 70h status and readiness logs. |
| Full APSU path-level conformance unverified | Gate 3 and Gate 5 cover readiness, RTS, path-up, DP state interaction, and interop. |
| Quantified high-loss proof missing | `STR-001` requires insertion-loss profile or calibrated fixture characterization for quantified high-loss claims; single VOA attenuation is bounded lab-observed attenuation only. |
| Convergence time unmeasured | `STR-002` requires independent control-to-traffic-recovery timing. |
| Polarity evidence not ordered raw log | `STR-003` requires ordered Page 70h and traffic evidence. |
| Repeatability third raw run missing | `STR-004` requires three labeled runs. |
| DUT/REF tap endpoint labels missing | `STR-004` requires endpoint labels. |
| Temperature-shift raw evidence missing | `STR-006` requires active shift/restart evidence when the behavior is claimed or exposed through Page 70h; endpoint-only temperature behavior belongs to `STR-005`. |
| Recovery and bundled restart unverified | `APSU-007`, `STR-009`, and `STR-010` cover restart, counters, and timers. |
| Link-partner interoperability missing | `INT-001` requires at least one non-Sian3 link partner and bounds the release claim to the covered partner class unless broader partner evidence exists. |
| Host-management interoperability missing | `INT-002` requires at least one non-Lumentum or customer-like CMIS host/exerciser and bounds the release claim to the covered host/exerciser class unless broader host-stack evidence exists. |

## Source Traceability

Primary vault sources:

- [apsu-ilt-verification-report](apsu-ilt-verification-report.md)
- [apsu-ilt-customer-note-plan](apsu-ilt-customer-note-plan.md)
- [lumentum-2026-8023dj-apsu-ilt-support-plan](../sources/lumentum-2026-8023dj-apsu-ilt-support-plan.md)
- [lumentum-2026-dpsm-apsu-ilt-state-machine](../sources/lumentum-2026-dpsm-apsu-ilt-state-machine.md)
- [broadcom-2026-sian3-apsu-application-notes](../sources/broadcom-2026-sian3-apsu-application-notes.md)
- [feng-jiang-2026-sian3-link-training-verification-email-thread](../sources/feng-jiang-2026-sian3-link-training-verification-email-thread.md)
- [oif2026-093-08-802-3dj-apsu-draft](../sources/oif2026-093-08-802-3dj-apsu-draft.md)
- [ieee-p802-3dj-d2-3](../sources/ieee-p802-3dj-d2-3.md)
- [how-should-hosts-use-sian3-apsu-capi](../queries/how-should-hosts-use-sian3-apsu-capi.md)
- [how-do-apsu-and-cmis-state-machines-interact](../queries/how-do-apsu-and-cmis-state-machines-interact.md)
