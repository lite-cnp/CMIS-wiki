---
type: synthesis
title: APSU/iLT Page 70h Verification Plan
created: 2026-06-09
updated: 2026-06-09
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
