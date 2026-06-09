# APSU/iLT Page 70h Verification Plan Implementation Plan

> **For agentic workers:** REQUIRED SUB-SKILL: Use superpowers:subagent-driven-development (recommended) or superpowers:executing-plans to implement this plan task-by-task. Steps use checkbox (`- [ ]`) syntax for tracking.

**Goal:** Create a durable internal engineering verification plan for next-release CMIS Page 70h APSU/iLT firmware validation.

**Architecture:** Add one Obsidian synthesis page as the authoritative verification plan, then update the wiki index and research log. The page will use a gate-based validation flow with a detailed test matrix, Page 70h as the formal pass/fail interface, and vendor/debug CDB paths marked diagnostic-only.

**Tech Stack:** Obsidian Markdown, CMIS wiki conventions, PowerShell, `rtk`, `rg`, Git.

---

## File Structure

- Create: `synthesis/apsu-ilt-page70h-verification-plan.md`
  - Responsibility: final internal engineering verification plan for next-release Page 70h APSU/iLT firmware.
- Modify: `index.md`
  - Responsibility: add the synthesis page to the wiki navigation.
- Modify: `log.md`
  - Responsibility: record the new synthesis page and its purpose.
- Existing source inputs:
  - `synthesis/apsu-ilt-verification-report.md`
  - `synthesis/apsu-ilt-customer-note-plan.md`
  - `sources/lumentum-2026-8023dj-apsu-ilt-support-plan.md`
  - `sources/lumentum-2026-dpsm-apsu-ilt-state-machine.md`
  - `sources/broadcom-2026-sian3-apsu-application-notes.md`
  - `sources/feng-jiang-2026-sian3-link-training-verification-email-thread.md`
  - `sources/oif2026-093-08-802-3dj-apsu-draft.md`
  - `sources/ieee-p802-3dj-d2-3.md`
  - `queries/how-should-hosts-use-sian3-apsu-capi.md`
  - `queries/how-do-apsu-and-cmis-state-machines-interact.md`
- Plan source:
  - `docs/superpowers/specs/2026-06-09-apsu-ilt-page70h-verification-plan-design.md`

## Task 1: Create The Final Verification Plan Page

**Files:**
- Create: `synthesis/apsu-ilt-page70h-verification-plan.md`

- [ ] **Step 1: Add frontmatter and opening sections**

Use `apply_patch` to create `synthesis/apsu-ilt-page70h-verification-plan.md` with this frontmatter and opening content:

```markdown
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

Formal pass/fail for this plan is based on CMIS Page 70h behavior plus external lab measurements. Existing vendor CDB, lab-only P253.66 debug CDB, Sian3 cAPI, BERT APIs, and traffic/FEC counters are diagnostic and correlation paths only.
```

- [ ] **Step 2: Add scope and assumptions**

Append these sections:

```markdown
## Scope And Assumptions

| Item | Plan position |
|---|---|
| Firmware scope | Next-release firmware with CMIS Page 70h APSU/iLT support. |
| Module scope | 1.6T 2xDR4 FRO module. |
| Formal interface | CMIS Page 70h only. |
| Diagnostic interfaces | Vendor CDB, lab-only P253.66 debug CDB, Sian3 cAPI, BERT APIs, traffic/FEC counters, and module logs. |
| Lab scope | Expanded setup with Sian3 BERT/DUT, calibrated loss fixtures or VOA, temperature chamber, traffic/FEC capture, and at least one non-Sian3 partner or host. |
| Standards baseline | IEEE P802.3dj D2.3, OIF2026.093.08 Page 70h, Broadcom Sian3 APSU AN, current customer-note plan, and current verification report. |
| Release rule | A Page 70h failure cannot be overridden by vendor CDB, debug CDB, or Sian3 cAPI correlation. |

## Baseline And Standards-Diff Checkpoint

Before formal execution, freeze the verification matrix to these vault baselines:

- [ieee-p802-3dj-d2-3](../sources/ieee-p802-3dj-d2-3.md)
- [oif2026-093-08-802-3dj-apsu-draft](../sources/oif2026-093-08-802-3dj-apsu-draft.md)
- [broadcom-2026-sian3-apsu-application-notes](../sources/broadcom-2026-sian3-apsu-application-notes.md)
- [apsu-ilt-customer-note-plan](apsu-ilt-customer-note-plan.md)
- [apsu-ilt-verification-report](apsu-ilt-verification-report.md)

P0 checkpoint: before lab execution starts, re-diff the latest available IEEE/OIF/Sian3 draft material against the frozen matrix. Any changed Page 70h byte definition, APSU state meaning, timer range, status bit behavior, or fault/recovery rule must be recorded as a matrix update before testing.
```

- [ ] **Step 3: Add formal pass/fail rule, setup, and evidence sections**

Append these sections:

```markdown
## Formal Pass/Fail Rule

CMIS Page 70h is the interface under test. A test can use diagnostic paths to explain a failure, but the formal result must come from Page 70h transaction logs and external measurements such as traffic/FEC BER, calibrated loss, temperature, and timing capture.

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
- Interop path: at least one non-Sian3 partner or host capable of exercising APSU/iLT expectations.
- CMIS host or exerciser capable of Page 70h reads/writes and timestamped transaction logging.
- Calibrated VOA or loss fixture with recorded attenuation or insertion-loss profile.
- Temperature chamber with setpoint, dwell time, and module case-temperature logging.
- Traffic/FEC BER capture with per-lane pre-FEC BER and post-FEC BER.
- Diagnostic access to vendor CDB, P253.66 debug CDB, and Sian3 cAPI when needed for correlation.

Every run must record firmware version, module serial, partner identity, script version, operator, physical setup, lane/path labels, and instrument configuration.

## Evidence Package Requirements

Each formal test must produce these artifacts when applicable:

- Page 70h transaction log with timestamp, page, bank, byte/range, read/write value, return status, lane/interface context, and script version.
- Traffic/FEC log with lane identity, pre-FEC BER, post-FEC BER, measurement window, and traffic pattern.
- Timing log with explicit start trigger, first training state change, first path-ready state, first path-up state, and traffic recovery time.
- Loss calibration record with VOA attenuation, insertion loss, cable or fixture identity, and calibration timestamp.
- Temperature record with chamber setpoint, module case temperature, dwell time, and measurement timestamp.
- Recovery log with recovery reason, recovery event count, read-clear behavior, and restart sequence.
- Diagnostic correlation log when vendor CDB, P253.66 debug CDB, or Sian3 cAPI is used.
- Setup photo or diagram with DUT/REF, host/media side, and lane/path labels.
```

- [ ] **Step 4: Add release gates**

Append this section:

```markdown
## Release Gates

| Gate | Name | Purpose | Exit criteria |
|---|---|---|---|
| Gate 0 | Baseline freeze and standards diff | Prevent stale assumptions. | Matrix frozen; draft re-diff complete; changes recorded. |
| Gate 1 | Firmware and Page 70h bring-up readiness | Prove the image is ready for formal validation. | Firmware identity, Page 70h discovery, APSU-capable gating, defaults, resets, non-APSU compatibility, and lane mapping pass. |
| Gate 2 | Page 70h register/access validation | Prove the standardized CMIS interface before behavior claims. | Byte ranges, permissions, reserved bytes, invalid writes, lane/bank mapping, coherency, and status update behavior pass. |
| Gate 3 | APSU/iLT functional validation | Prove nominal Page 70h APSU/iLT behavior. | Enable/disable, readiness, RTS, path-up, training pattern, precoding, tap/BER improvement, and bundle behavior pass. |
| Gate 4 | Stress, fault, and recovery validation | Close current evidence gaps and Sian3 AN behavior gaps. | High loss, convergence timing, polarity, repeatability, temperature, partner faults, recovery counters, and restart behavior pass or are explicitly bounded. |
| Gate 5 | Interop and evidence package | Prove customer-relevant behavior and auditability. | Non-Sian3 interop completes; evidence package is complete; release criteria are reviewed. |
```

- [ ] **Step 5: Add detailed test matrix**

Append this section with the full matrix:

```markdown
## Detailed Test Matrix

| Test ID | Gate | Objective | Baseline source | Interface under test | Diagnostic interfaces | Required evidence | Gap mitigated |
|---|---|---|---|---|---|---|---|
| STD-001 | Gate 0 | Freeze source versions and matrix baseline. | IEEE/OIF/Sian3/customer-note baselines | Page 70h planning matrix | None | Source version list and matrix revision record. | Prevent stale requirements. |
| STD-002 | Gate 0 | Re-diff latest drafts before execution. | Latest available IEEE/OIF/Sian3 drafts | Page 70h planning matrix | None | Diff summary with accepted matrix updates. | Draft drift. |
| BR-001 | Gate 1 | Record firmware identity and build configuration. | Release candidate metadata | Page 70h | Vendor CDB/debug CDB only for identity correlation | Firmware version, build metadata, module serial, feature flags. | Build ambiguity. |
| BR-002 | Gate 1 | Verify Page 70h presence and APSU-capable application gating. | OIF Page 70h | Page 70h | CMIS application advertisement | Page 70h discovery log for APSU and non-APSU apps. | Page 70h exposure errors. |
| BR-003 | Gate 1 | Verify default APSU/iLT states after reset and power transitions. | OIF Page 70h, customer-note defaults | Page 70h | Module logs | Reset, power-cycle, low-power, data-path-reset, and module-reset logs. | Default/reset ambiguity. |
| BR-004 | Gate 1 | Verify non-APSU applications remain backward compatible. | OIF draft | Page 70h and normal CMIS app behavior | Traffic/FEC counters | Non-APSU app bring-up and traffic logs. | Non-APSU regression. |
| BR-005 | Gate 1 | Verify host/media lane inventory and bank mapping. | OIF Page 70h | Page 70h | Sian3 cAPI diagnostic correlation | Lane/bank mapping log for host and media sides. | Lane mapping ambiguity. |
| P70H-001 | Gate 2 | Validate Page 70h byte ranges `128-131`, `132-151`, `152-191`, and `192-230`. | OIF Page 70h | Page 70h | None | Read/write map with expected permissions. | Page 70h mis-map. |
| P70H-002 | Gate 2 | Verify reserved bytes `231-255` are stable and not writable. | OIF Page 70h | Page 70h | None | Reserved-byte read/write rejection log. | Reserved byte behavior. |
| P70H-003 | Gate 2 | Verify invalid writes and invalid lane masks are rejected or ignored as specified. | OIF Page 70h | Page 70h | Module logs | Invalid write transaction log and post-state readback. | Invalid control handling. |
| P70H-004 | Gate 2 | Verify host/media side mapping and per-lane mapping. | OIF Page 70h, Sian3 AN | Page 70h | Sian3 cAPI diagnostic correlation | Page 70h per-lane operation with diagnostic side/lane correlation. | DUT/REF and side labeling. |
| P70H-005 | Gate 2 | Verify multi-byte coherency and polling behavior. | CMIS behavior expectations, OIF Page 70h | Page 70h | None | Repeated read snapshots under stable and changing states. | Stale or torn status. |
| P70H-006 | Gate 2 | Measure Page 70h status update latency. | OIF Page 70h | Page 70h | BERT timing capture | Timestamped command/status transition log. | Status latency ambiguity. |
| P70H-007 | Gate 2 | Verify Page 70h access during DPSM transitions. | DPSM/APSU state-machine source | Page 70h | Module state logs | Access log during DPInitialized, DPTxTurnOn, DPActivated, and deactivation. | DP state interaction. |
| APSU-001 | Gate 3 | Enable and disable APSU/iLT per host/media lane. | OIF Page 70h, customer-note plan | Page 70h | Vendor CDB/debug CDB correlation | Per-lane enable/readback and active-state logs. | Current vendor CDB migration. |
| APSU-002 | Gate 3 | Verify path-up readiness is not inferred from `DPActivated` alone. | IEEE/OIF/Sian3 AN | Page 70h | Traffic/FEC counters | DP state, Page 70h readiness, and traffic correlation log. | Full APSU path readiness. |
| APSU-003 | Gate 3 | Verify local/remote RTS and ready-bit transitions. | IEEE/OIF/Sian3 AN | Page 70h | Sian3 cAPI diagnostic correlation | RTS, local ready, remote ready, and path-up transition log. | Readiness status exposure. |
| APSU-004 | Gate 3 | Verify training pattern control/readback and PRBS13/PRBS31 behavior. | OIF Page 70h, Sian3 AN | Page 70h | BERT pattern detection, Sian3 cAPI | Pattern command/readback and BERT observation log. | Training-pattern gap. |
| APSU-005 | Gate 3 | Verify precoding request/readback behavior. | Sian3 AN, customer-note precoding support | Page 70h | Vendor CDB, Sian3 cAPI | Page 70h precode command/readback and diagnostic correlation. | Precode mapping gap. |
| APSU-006 | Gate 3 | Verify tap optimization improves BER under degraded tap setup. | Sian3 AN, Feng evidence | Page 70h | BERT/FEC counters, Sian3 cAPI | Before/after taps, BER, and Page 70h status log. | Selected LT behavior through Page 70h. |
| APSU-007 | Gate 3 | Verify bundled lane restart behavior. | Sian3 AN | Page 70h | Sian3 cAPI diagnostic correlation | One-lane restart command and all-lane bundle response log. | Bundle restart gap. |
| STR-001 | Gate 4 | Validate quantified high-loss behavior. | Customer request, verification gap | Page 70h | Loss calibration, BERT/FEC counters | VOA/loss profile, Page 70h status, BER, and recovery log. | High-loss proof. |
| STR-002 | Gate 4 | Measure convergence time independently. | Customer request, verification gap | Page 70h | External timer, BERT/FEC counters | Start trigger, state changes, path-up time, and traffic recovery time. | Convergence time. |
| STR-003 | Gate 4 | Produce ordered polarity recovery raw evidence. | Sian3 AN, Feng evidence | Page 70h | BERT/FEC counters, Sian3 cAPI | Traffic break, Page 70h command, polarity status, recovery, and traffic log. | Polarity raw log gap. |
| STR-004 | Gate 4 | Repeat degraded-tap recovery three times with labeled endpoints. | Customer request, Feng evidence gap | Page 70h | BERT/FEC counters, Sian3 cAPI | Three run logs with DUT/REF or local/remote labels. | Repeatability and endpoint labeling. |
| STR-005 | Gate 4 | Validate 0 C, 45 C, and 70 C temperature corners. | Feng evidence, customer request | Page 70h | Chamber logs, BERT/FEC counters | Temperature, dwell, Page 70h status, taps, and BER logs. | Temperature-corner coverage. |
| STR-006 | Gate 4 | Validate 10 C to 60 C temperature-shift behavior. | Sian3 AN, Feng email evidence | Page 70h | Chamber logs, Sian3 cAPI, BERT/FEC counters | FIR/status before shift, after dwell, failed or accepted FIR change, LT restart, new FIR, and BER logs. | Temperature-shift raw evidence. |
| STR-007 | Gate 4 | Validate behavior with non-LT frame partner. | Sian3 AN | Page 70h | Partner logs, Sian3 cAPI | Restart/status log with no training-frame lock condition. | Non-LT partner restart. |
| STR-008 | Gate 4 | Validate partner squelch and signal-loss behavior. | Sian3 AN | Page 70h | Partner logs, BERT/FEC counters | Squelch trigger, signal-loss status, restart behavior, and recovery log. | Fault handling. |
| STR-009 | Gate 4 | Validate recovery reason and recovery event count read-clear behavior. | Sian3 AN | Page 70h | Sian3 cAPI diagnostic correlation | Recovery injection, Page 70h read, second read after clear, and diagnostic correlation. | Recovery counter behavior. |
| STR-010 | Gate 4 | Validate slicer modes and timer behavior where supported. | Sian3 AN | Page 70h | Sian3 cAPI, BERT/FEC counters | Auto/NR/ER mode logs and timer override/readback/behavior logs. | Slicer and timer coverage. |
| INT-001 | Gate 5 | Validate APSU/iLT with at least one non-Sian3 partner or host. | IEEE/OIF interoperability expectation | Page 70h | Partner logs, traffic/FEC counters | Interop setup, Page 70h status, traffic, and error logs. | Non-Sian3 interoperability. |
| INT-002 | Gate 5 | Correlate Page 70h status to Sian3 cAPI for diagnosis only. | Sian3 AN | Page 70h | P253.66 debug CDB, Sian3 cAPI | Side-by-side Page 70h and diagnostic status log. | Mapping confidence. |
| INT-003 | Gate 5 | Audit final evidence package completeness. | Verification plan | Page 70h logs and all lab artifacts | None | Evidence checklist signed off by engineering reviewer. | Auditability. |
| INT-004 | Gate 5 | Produce final release decision summary. | Verification plan | Page 70h | All artifacts | P0/P1/P2 result summary and bounded release notes. | Release decision traceability. |
```

- [ ] **Step 6: Add release criteria and source traceability**

Append these sections:

```markdown
## Release Criteria

### P0 Release Blockers

Any of these blocks a Page 70h APSU/iLT release claim:

- Page 70h is absent, gated incorrectly, or exposed for unsupported applications.
- Page 70h byte ranges are mis-mapped.
- Reserved bytes are writable or unstable.
- Host/media lane mapping is wrong or ambiguous.
- Defaults after reset or power cycle do not match the expected state.
- Page 70h cannot control or report supported APSU/iLT state.
- Nominal supported cases cannot reach expected path-up, ready, or RTS status through Page 70h.
- Page 70h disagrees with traffic/FEC evidence in a way that cannot be resolved.
- Non-APSU applications regress.
- High-loss or convergence claims are made without calibrated loss or independent timing evidence.

### P1 Engineering Confidence Items

These should pass or be explicitly bounded in release notes:

- Repeatability across at least three runs.
- Temperature corners.
- Ordered polarity recovery.
- Recovery reason and recovery event count.
- Bundled restart.
- Partner fault behavior.
- Non-Sian3 interoperability.
- Temperature shift and LT restart behavior.

### P2 Follow-Up Items

These improve confidence but should not block release unless tied to a customer claim:

- Additional partner coverage.
- Larger temperature/loss sweep.
- Automation polish.
- Additional correlation between Page 70h and Sian3 cAPI diagnostics.
- More compact customer-safe report packaging.

## Gap Mitigation Map

| Prior gap | Planned mitigation |
|---|---|
| Page 70h not implemented in current firmware | Gate 1 and Gate 2 validate Page 70h presence, mapping, and access behavior. |
| Detailed readiness/status not customer-accessible | Gate 2 and Gate 3 require Page 70h status and readiness logs. |
| Full APSU path-level conformance unverified | Gate 3 and Gate 5 cover readiness, RTS, path-up, DP state interaction, and interop. |
| High-loss proof missing | `STR-001` requires calibrated loss evidence. |
| Convergence time unmeasured | `STR-002` requires independent timing. |
| Polarity evidence not ordered raw log | `STR-003` requires ordered Page 70h and traffic evidence. |
| Repeatability third raw run missing | `STR-004` requires three labeled runs. |
| DUT/REF tap endpoint labels missing | `STR-004` requires endpoint labels. |
| Temperature-shift raw evidence missing | `STR-006` requires raw shift/restart evidence. |
| Recovery and bundled restart unverified | `APSU-007`, `STR-009`, and `STR-010` cover restart, counters, and timers. |
| Non-Sian3 interoperability missing | `INT-001` requires at least one non-Sian3 partner or host. |

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
```

- [ ] **Step 7: Read the new page locally**

Run:

```powershell
rtk proxy powershell -NoProfile -Command "Get-Content -Raw 'synthesis\apsu-ilt-page70h-verification-plan.md'"
```

Expected: the new page renders as one Markdown file with the sections above and no malformed table rows.

## Task 2: Update Wiki Index And Research Log

**Files:**
- Modify: `index.md`
- Modify: `log.md`

- [ ] **Step 1: Add the index entry**

Use `apply_patch` to add this line under `## Synthesis` in `index.md`, after `apsu-ilt-verification-report` if present:

```markdown
- [apsu-ilt-page70h-verification-plan](synthesis/apsu-ilt-page70h-verification-plan.md) - internal engineering verification plan for next-release CMIS Page 70h APSU/iLT firmware validation.
```

- [ ] **Step 2: Add the log entry**

Use `apply_patch` to add this entry immediately after `# Research Log` in `log.md`:

```markdown
## 2026-06-09 synthesis | APSU/iLT Page 70h verification plan

- Added [apsu-ilt-page70h-verification-plan](synthesis/apsu-ilt-page70h-verification-plan.md), an internal engineering validation plan for next-release CMIS Page 70h APSU/iLT support.
- Captured release gates, formal Page 70h pass/fail rules, evidence requirements, detailed test matrix, and mitigation coverage for the current IEEE/OIF/Sian3 verification gaps.
```

- [ ] **Step 3: Verify navigation references**

Run:

```powershell
rtk proxy powershell -NoProfile -Command "rg -n 'apsu-ilt-page70h-verification-plan' index.md log.md synthesis\apsu-ilt-page70h-verification-plan.md"
```

Expected: one match in `index.md`, one match in `log.md`, and self/source references in the synthesis page only if included.

## Task 3: Validate The Wiki Page

**Files:**
- Validate: `synthesis/apsu-ilt-page70h-verification-plan.md`
- Validate: `index.md`
- Validate: `log.md`

- [ ] **Step 1: Read back through Obsidian CLI**

Run:

```powershell
rtk obsidian vault=llmwiki read path="CMIS/wiki/synthesis/apsu-ilt-page70h-verification-plan.md"
```

Expected: Obsidian CLI returns the full Markdown page.

- [ ] **Step 2: Check ASCII-only content**

Run:

```powershell
rtk proxy powershell -NoProfile -Command "rg -n '[^\x00-\x7F]' synthesis\apsu-ilt-page70h-verification-plan.md index.md log.md; if (`$LASTEXITCODE -eq 1) { exit 0 } else { exit `$LASTEXITCODE }"
```

Expected: no output and exit code 0.

- [ ] **Step 3: Check relative link targets**

Run:

```powershell
rtk proxy powershell -NoProfile -Command "Test-Path synthesis\apsu-ilt-page70h-verification-plan.md; Test-Path synthesis\apsu-ilt-verification-report.md; Test-Path synthesis\apsu-ilt-customer-note-plan.md; Test-Path sources\lumentum-2026-8023dj-apsu-ilt-support-plan.md; Test-Path sources\lumentum-2026-dpsm-apsu-ilt-state-machine.md; Test-Path sources\broadcom-2026-sian3-apsu-application-notes.md; Test-Path sources\feng-jiang-2026-sian3-link-training-verification-email-thread.md; Test-Path sources\oif2026-093-08-802-3dj-apsu-draft.md; Test-Path sources\ieee-p802-3dj-d2-3.md; Test-Path queries\how-should-hosts-use-sian3-apsu-capi.md; Test-Path queries\how-do-apsu-and-cmis-state-machines-interact.md"
```

Expected: eleven `True` lines.

- [ ] **Step 4: Check content rules**

Run:

```powershell
rtk proxy powershell -NoProfile -Command "rg -n 'Formal pass/fail|diagnostic|P253.66|Page 70h|vendor CDB|high-loss|convergence|polarity|temperature-shift|non-Sian3' synthesis\apsu-ilt-page70h-verification-plan.md"
```

Expected: matches show that Page 70h is formal pass/fail, vendor/debug CDB are diagnostic, and all prior gaps are covered.

## Task 4: Commit The Wiki Update

**Files:**
- Add: `synthesis/apsu-ilt-page70h-verification-plan.md`
- Modify: `index.md`
- Modify: `log.md`
- Already present: `docs/superpowers/specs/2026-06-09-apsu-ilt-page70h-verification-plan-design.md`
- Add: `docs/superpowers/plans/2026-06-09-apsu-ilt-page70h-verification-plan.md`

- [ ] **Step 1: Check repo status**

Run:

```powershell
rtk proxy powershell -NoProfile -Command "git status --short --branch"
```

Expected: the new synthesis page, `index.md`, `log.md`, and this implementation plan are visible; `.obsidian/` remains untracked and should not be staged.

- [ ] **Step 2: Stage intended files only**

Run:

```powershell
rtk proxy powershell -NoProfile -Command "git add synthesis\apsu-ilt-page70h-verification-plan.md index.md log.md docs\superpowers\plans\2026-06-09-apsu-ilt-page70h-verification-plan.md"
```

Expected: no output.

- [ ] **Step 3: Review staged files**

Run:

```powershell
rtk proxy powershell -NoProfile -Command "git diff --cached --name-status; git diff --cached --stat"
```

Expected: staged files include only the final synthesis page, `index.md`, `log.md`, and this implementation plan. `.obsidian/` is not staged.

- [ ] **Step 4: Commit**

Run:

```powershell
rtk proxy powershell -NoProfile -Command "git commit -m 'Add APSU iLT Page 70h verification plan'"
```

Expected: commit succeeds with the new verification plan and navigation/log updates.

- [ ] **Step 5: Final status**

Run:

```powershell
rtk proxy powershell -NoProfile -Command "git status --short --branch"
```

Expected: branch is ahead of origin; `.obsidian/` remains untracked.

## Self-Review Checklist

- [ ] The plan creates one durable synthesis page and updates index/log.
- [ ] The final page uses CMIS Page 70h as the formal pass/fail interface.
- [ ] Vendor CDB, P253.66 debug CDB, and Sian3 cAPI are diagnostic-only.
- [ ] Page 70h ranges `128-131`, `132-151`, `152-191`, `192-230`, and `231-255` are covered.
- [ ] High-loss, convergence timing, polarity raw log, repeatability, endpoint labeling, temperature shift, recovery counters, bundled restart, and non-Sian3 interop are covered.
- [ ] Validation commands are exact and use `rtk`.
- [ ] `.obsidian/` is not staged.
