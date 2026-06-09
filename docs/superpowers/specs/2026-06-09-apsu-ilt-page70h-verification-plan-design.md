---
title: APSU/iLT Page 70h Verification Plan Design
date: 2026-06-09
status: self-reviewed-awaiting-user-review
deliverable: CMIS/wiki/synthesis/apsu-ilt-page70h-verification-plan.md
---

# APSU/iLT Page 70h Verification Plan Design

## Goal

Create a detailed internal engineering verification plan for the next release 1.6T 2xDR4 FRO module firmware where CMIS Page 70h supports APSU/iLT control and status. The plan must mitigate the known gaps against IEEE 802.3dj APSU/iLT behavior, OIF CMIS Page 70h, and the Broadcom Sian3 APSU application note as much as possible.

The final durable wiki page will be:

`CMIS/wiki/synthesis/apsu-ilt-page70h-verification-plan.md`

The final page will also require updates to `CMIS/wiki/index.md` and `CMIS/wiki/log.md`.

## Approved Scope Decisions

- Audience: internal engineering validation plan.
- Firmware assumption: next release firmware supports CMIS Page 70h, but the plan must include Page 70h bring-up and readiness checks before formal verification.
- Lab scope: expanded interop setup, including at least one non-Sian3 partner or host in addition to the Sian3 BERT/DUT setup.
- Formal pass/fail interface: CMIS Page 70h only.
- Diagnostic/correlation interfaces: existing vendor CDB, lab-only P253.66 debug CDB, Sian3 cAPI, BERT APIs, traffic/FEC counters, and module logs.
- Standards baseline: freeze the initial matrix to the current vault baselines, with a P0 checkpoint to re-diff against newer drafts before execution.
- Durable output: create an Obsidian synthesis page for the final plan.

## Primary Source Inputs

Use the current vault pages as the source set:

- `CMIS/wiki/synthesis/apsu-ilt-verification-report.md`
- `CMIS/wiki/synthesis/apsu-ilt-customer-note-plan.md`
- `CMIS/wiki/sources/lumentum-2026-8023dj-apsu-ilt-support-plan.md`
- `CMIS/wiki/sources/lumentum-2026-dpsm-apsu-ilt-state-machine.md`
- `CMIS/wiki/sources/broadcom-2026-sian3-apsu-application-notes.md`
- `CMIS/wiki/sources/feng-jiang-2026-sian3-link-training-verification-email-thread.md`
- `CMIS/wiki/sources/oif2026-093-08-802-3dj-apsu-draft.md`
- `CMIS/wiki/sources/ieee-p802-3dj-d2-3.md`
- `CMIS/wiki/queries/how-should-hosts-use-sian3-apsu-capi.md`
- `CMIS/wiki/queries/how-do-apsu-and-cmis-state-machines-interact.md`

The plan should not reopen raw files unless the source pages contain a contradiction or the plan needs a concrete artifact name already summarized in the source pages.

## Non-Goals

- Do not define new firmware features beyond the next-release Page 70h implementation.
- Do not create a transitional customer vendor CDB detailed status interface.
- Do not let vendor CDB, lab-only debug CDB, or Sian3 cAPI override a Page 70h formal failure.
- Do not claim new lab results.
- Do not produce customer-safe marketing wording as the primary artifact.
- Do not generate firmware implementation tasks; this is a verification-plan artifact.

## Recommended Approach

Use a gate-based verification plan with an embedded traceability matrix.

The rejected alternatives were:

- A traceability-matrix-first plan: strong auditability but too heavy before execution flow is clear.
- A lab-scenario-first plan: easy to execute but weaker at proving complete Page 70h and standards coverage.

The gate-based plan is preferred because it gives firmware and validation teams a clear release path while still requiring each test to trace back to IEEE 802.3dj, OIF Page 70h, Sian3 AN, or a known evidence gap.

## Plan Architecture

The final verification plan should use these release gates.

### Gate 0: Baseline Freeze And Standards Diff

Purpose: prevent execution against stale assumptions.

Required content:

- Freeze the initial matrix to IEEE P802.3dj D2.3, OIF2026.093.08 Page 70h, Broadcom Sian3 APSU AN, the current customer-note plan, and the current verification report.
- Add a P0 checkpoint to re-diff against newer IEEE/OIF/Sian3 drafts before formal execution.
- Record all differences as matrix updates before test execution starts.

### Gate 1: Firmware And Page 70h Bring-Up Readiness

Purpose: prove the next release image is ready for formal validation.

Required content:

- Firmware version, module serial, build metadata, feature flags, and exact release candidate identity.
- Page 70h discovery and APSU-capable application gating.
- Default APSU/iLT state after reset, power cycle, low-power transition, data-path reset, and module reset.
- Non-APSU application backward compatibility.
- Host/media lane inventory and bank/lane mapping.
- Confirmation that vendor CDB and lab-only debug CDB are diagnostic-only for this plan.

### Gate 2: Page 70h Register And Access Validation

Purpose: validate the standardized CMIS interface before using it for behavior claims.

Required Page 70h ranges:

- `128-131`: interface-level APSU, ILT, and RTS control/status.
- `132-151`: per-lane training pattern control.
- `152-191`: media interface per-lane ILT control/status.
- `192-230`: host interface per-lane ILT control/status.
- `231-255`: reserved.

Required checks:

- Read/write permissions and write-one/clear or sticky-clear semantics where applicable.
- Reserved byte behavior.
- Invalid writes and invalid lane masks.
- Lane/bank mapping and host/media side mapping.
- Default values and reset values.
- Multi-byte coherency and polling behavior.
- Status update latency and stale-read handling.
- Access behavior during DPSM transitions.

### Gate 3: APSU/iLT Functional Validation

Purpose: prove nominal and expected APSU/iLT behavior through Page 70h.

Required coverage:

- APSU/iLT enable and disable per host/media lane.
- Path-up behavior and readiness gating.
- RTS local/remote readiness.
- Training status progression.
- Local and remote ready bits.
- PRBS13/PRBS31 and training-pattern behavior.
- Precoding request/readback behavior.
- Tap optimization and BER improvement.
- Bundle restart behavior.
- DP state interaction: `DPActivated` alone must not be treated as Ethernet DATA ready.

### Gate 4: Stress, Fault, And Recovery Validation

Purpose: close the current evidence gaps and validate Sian3 AN fault behavior.

Required coverage:

- Quantified high-loss physical channel with recorded VOA attenuation or insertion-loss profile.
- Independent convergence-time measurement.
- Ordered polarity raw log with traffic break, Page 70h command, Page 70h status, polarity correction indication, and traffic recovery.
- Three-run repeatability with same degraded taps and labeled DUT/REF or local/remote endpoints.
- Temperature corners at about 0 C, 45 C, and 70 C.
- Temperature-shift behavior with raw log, including whether FIR changes without LT restart and behavior after disable/re-enable.
- Non-LT frame partner behavior.
- Link partner squelch and signal-loss behavior.
- Recovery reason and recovery event count behavior, including read-clear handling.
- Bundled lane restart and fault isolation.
- Slicer auto/NR/ER behavior where supported.
- Timer behavior for forward RTS, recovery, propagation, quiet, and max-wait timers.

### Gate 5: Interop And Evidence Package

Purpose: verify customer-relevant behavior and produce auditable release evidence.

Required coverage:

- Sian3-to-Sian3 setup.
- At least one non-Sian3 partner or host.
- Page 70h transaction trace as the formal evidence.
- Vendor CDB/debug CDB/Sian3 cAPI correlation logs only when needed for diagnosis.
- Final evidence package with raw logs, setup photos, calibration data, script version, firmware version, module serials, partner identity, BERT configuration, and pass/fail summary.

## Test Matrix Schema

Each test case in the final plan should use this shape:

| Field | Required content |
|---|---|
| Test ID | Stable ID such as `P70H-BR-001` or `APSU-FN-004`. |
| Objective | One clear behavior to prove. |
| Baseline source | IEEE 802.3dj, OIF Page 70h, Sian3 AN, customer-note plan, or regression baseline. |
| Interface under test | CMIS Page 70h for formal pass/fail. |
| Diagnostic interfaces | Vendor CDB, P253.66 debug CDB, Sian3 cAPI, BERT APIs, or traffic/FEC counters when used. |
| Setup | Hardware, lane side, module/partner, loss, temperature, and traffic condition. |
| Procedure | Stepwise operations. |
| Expected result | Specific Page 70h status, traffic, BER, or event behavior. |
| Pass/fail criteria | Binary rule using Page 70h and external measurements. |
| Required evidence | Logs, screenshots, calibration, timing capture, or raw data files. |
| Gap mitigated | Current report gap or standards/AN behavior covered. |

## Evidence Requirements

The plan must require machine-readable evidence where possible:

- Page 70h transaction logs with timestamp, page, bank, byte/range, read/write value, return status, lane/interface context, and script version.
- Traffic/FEC BER logs with pre-FEC BER, post-FEC BER, lane identity, measurement window, and traffic pattern.
- Convergence timing logs with explicit start trigger, first observed state change, first path-ready state, first path-up state, and traffic recovery time.
- Loss calibration data with VOA attenuation, insertion loss, cable/fixture identity, and calibration timestamp.
- Temperature logs with chamber setpoint, module case temperature, dwell time, and measurement timestamp.
- Recovery event logs with recovery reason, recovery event count, read-clear behavior, and restart sequence.
- Sian3 debug/cAPI correlation logs when used, explicitly marked diagnostic-only.
- Setup photos or diagrams for physical topology and lane/path labeling.
- Firmware version, module serial, partner identity, BERT configuration, script commit/hash, and operator.

## Required Coverage Groups

### Page 70h Protocol Coverage

The final plan must cover presence/gating, access permissions, reserved bytes, default values, reset behavior, lane/bank mapping, APSU-capable application gating, coherency, invalid writes, status latency, and sticky/status clear rules.

### Interface-Level APSU/iLT/RTS Coverage

The final plan must cover bytes `128-131`: interface-level enablement, status aggregation, RTS state, readiness transitions, and DP state interaction.

### Training-Pattern Coverage

The final plan must cover bytes `132-151`: per-lane pattern control/readback, invalid pattern requests, and correlation with Sian3 local/remote TP and MC modes.

### Media-Side ILT Coverage

The final plan must cover bytes `152-191`: media-side per-lane enable/status, path-up state, local/remote ready, RTS, fault/recovery, and APSU interaction.

### Host-Side ILT Coverage

The final plan must cover bytes `192-230`: host-side per-lane enable/status, path-up state, local/remote ready, RTS, fault/recovery, and the current Feng-style host-side cases carried forward through Page 70h.

### Sian3 AN Behavioral Coverage

The final plan must cover polarity correction, slicer auto/NR/ER behavior, precoder request behavior, bundled lane restart, timers, recovery reason/event count, non-LT frame restart, Tx squelch, signal loss, fault handling when links are up, training-pattern behavior, and temperature-shift restart behavior.

### Gap-Closure Coverage

The final plan must explicitly close or bound these current gaps:

- Quantified high-loss physical channel.
- Independent convergence timing.
- Three-run repeatability.
- Ordered polarity raw log.
- DUT/REF endpoint labeling.
- Page 70h customer-facing transaction traces.
- Non-Sian3 interoperability.
- Temperature-shift raw evidence.
- Recovery reason/event count behavior.
- Full APSU path-level validation beyond selected LT behavior.

## Pass/Fail And Release Criteria

### P0 Release Blockers

Any of these should block a Page 70h APSU/iLT release claim:

- Page 70h is absent, gated incorrectly, or exposed for unsupported applications.
- Page 70h byte ranges are mis-mapped.
- Reserved bytes are writable or return unstable values.
- Host/media lane mapping is wrong or ambiguous.
- Defaults after reset/power cycle do not match the specification.
- Page 70h cannot control or report supported APSU/iLT state.
- Nominal supported cases cannot reach expected path-up, ready, or RTS status through Page 70h.
- Page 70h disagrees with external traffic/FEC evidence in a way that cannot be resolved.
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

These are useful but should not block release unless tied to a customer claim:

- Additional partner coverage.
- Larger temperature/loss sweep.
- Automation polish.
- Better report formatting.
- Additional correlation between Page 70h and Sian3 cAPI diagnostics.

## Final Wiki Page Structure

The final durable page should use this structure:

1. Executive intent.
2. Scope and assumptions.
3. Baselines and standards-diff checkpoint.
4. Formal pass/fail rule: Page 70h only.
5. Lab setup and instrumentation.
6. Evidence package requirements.
7. Release gates.
8. Detailed test matrix.
9. Page 70h register/access tests.
10. APSU/iLT functional tests.
11. Sian3 AN behavior tests.
12. Stress, fault, recovery, and temperature tests.
13. Interop tests.
14. Release criteria and gap mitigation map.
15. Source traceability.

## Validation After Final Page Creation

After creating the final wiki page:

- Read the page back through `rtk obsidian vault=llmwiki read`.
- Check relative Markdown links from the final plan, `index.md`, and `log.md`.
- Check touched files for non-ASCII characters.
- Verify the final page uses Page 70h as formal pass/fail.
- Verify vendor CDB/debug CDB are diagnostic-only.
- Verify known gaps from `apsu-ilt-verification-report.md` are each covered or explicitly bounded.
- Commit the wiki page, index, log, and this design spec in the CMIS wiki repo if not already committed.

## Open Assumptions To Carry Into The Plan

- The next release firmware has a Page 70h implementation ready for bring-up validation.
- The final Page 70h field-level mapping follows the OIF2026.093.08 ranges already summarized in the vault.
- The lab can access expanded interop assets, including at least one non-Sian3 partner or host.
- Existing vendor CDB, P253.66 debug CDB, and Sian3 cAPI tooling remain available for correlation and debug.
- The final plan can specify required evidence even if some artifacts are not yet collected.
