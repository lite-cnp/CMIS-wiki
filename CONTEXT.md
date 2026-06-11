# CMIS Wiki

This context defines the domain language used by the CMIS wiki for module management, APSU/iLT planning, and verification evidence.

## Language

**Page 70h APSU/iLT Release Validation**:
Validation of next-release 1.6T 2xDR4 FRO module firmware behavior exposed through CMIS Page 70h. IEEE 802.3dj, OIF Page 70h, and the Sian3 application note are reference baselines for the validation plan, not a claim of formal IEEE conformance certification.
_Avoid_: IEEE certification, APSU conformance certification, Sian3 certification

**Formal Pass/Fail Interface**:
The management interface whose observed behavior determines whether a verification test passes or fails. For Page 70h APSU/iLT release validation, this is CMIS Page 70h.
_Avoid_: Primary interface, customer interface, interface under test

**External Measurement Evidence**:
Lab evidence from instruments and observations outside the formal pass/fail interface, such as traffic/FEC counters, loss calibration, temperature logs, and timing captures. This evidence can confirm behavior and expose contradictions, but it does not replace Page 70h as the formal pass/fail interface.
_Avoid_: Diagnostic interface, debug evidence

**Diagnostic Correlation Path**:
A non-authoritative path used to explain or correlate Page 70h behavior, not to decide pass/fail. In this context, vendor CDB is a legacy/current customer control comparison path, P253.66 Debug CDB is a lab-only bridge to Sian3 cAPI, and Sian3 cAPI is an underlying DSP behavior reference path.
_Avoid_: Alternate pass/fail path, backup interface, equivalent interface

**Page 70h To Sian3 Diagnostic Correlation**:
A diagnostic-only comparison between Page 70h control/status behavior and Sian3 cAPI, debug CDB, or vendor CDB state. It is used for mapping confidence, failure triage, and implementation debugging. It cannot change a Page 70h formal `Pass`, `Fail`, `Blocked`, `Bounded`, or `Not Run` result.
_Avoid_: Sian3 proof of Page 70h pass, debug override, customer-facing formal result

**Reusable Diagnostic Harness**:
Existing lab automation and instrumentation reused to set conditions or collect supporting evidence for Page 70h APSU/iLT validation while remaining outside the formal pass/fail interface. It can provide setup, external measurement, and diagnostic correlation evidence, but it cannot convert a Page 70h failure into a pass.
_Avoid_: Formal test interface, compliance harness, customer host proof

**Low-Level Verification Primitive**:
A reusable validation action with a defined purpose, required evidence, and evidence boundary that can be composed into one or more Page 70h APSU/iLT test cases. A primitive is smaller than a full matrix row and does not by itself define the release result unless a test row explicitly uses it as formal evidence.
_Avoid_: One-off script step, full test procedure, duplicate row procedure

**Primitive Requirement Class**:
The role a low-level verification primitive has inside a test case: mandatory core for every formal run, conditional when the row exercises the relevant behavior, or diagnostic-only when the primitive supports explanation without deciding formal pass/fail.
_Avoid_: Optional evidence bucket, informal priority, release decision status

**Low-Level Test-Case Sheet**:
A durable execution-oriented expansion of a verification matrix row into primitives, setup reuse, Page 70h formal actions or reads, diagnostic calls, expected observations, pass/fail criteria, evidence IDs, and blockers. It complements the main matrix; it does not replace the matrix as the release coverage summary.
_Avoid_: Ad hoc lab note, script comments, main matrix replacement

**Normative Baseline**:
The standards or draft standards that define expected CMIS/APSU behavior for the validation plan. In this context, the normative baseline is IEEE P802.3dj and OIF Page 70h draft material.
_Avoid_: Reference baseline, implementation note

**Implementation Reference**:
Vendor, customer-note, internal report, or prior lab-evidence material used to shape validation coverage without becoming a standard. In this context, the Sian3 application note, customer-note plan, current verification report, and prior lab evidence are implementation references.
_Avoid_: Standard, normative source

**Reference Source**:
Any source used to justify a validation test case, including normative baselines, implementation references, customer requests, and prior lab evidence. This term intentionally does not imply standards authority.
_Avoid_: Baseline source, requirement source

**Evidence Contradiction**:
A mismatch between the formal pass/fail interface and external measurement evidence, such as Page 70h reporting ready while traffic/FEC indicates failure, or Page 70h reporting not ready while traffic is passing. Evidence contradictions are validation failures because they show the formal status surface is not trustworthy.
_Avoid_: Benign mismatch, diagnostic discrepancy

**Data-Ready APSU State**:
The condition where Page 70h readiness/status and external traffic evidence agree that the path is ready for Ethernet DATA. `PATH_UP` is one relevant APSU/LT state value, but it is not the whole readiness concept by itself.
_Avoid_: DPActivated, PATH_UP-only readiness, traffic-only readiness

**Data-Ready Evidence Pair**:
The paired evidence required to prove data-ready APSU state: Page 70h readiness/status evidence plus external traffic/FEC evidence meeting the predeclared recovery criterion. Either side alone is supporting evidence, not a complete data-ready proof.
_Avoid_: Single-bit readiness proof, DPActivated proof, BER-only proof

**Degraded-Tap Recovery Proof**:
A functional APSU/iLT validation that creates a controlled impaired precondition with degraded tap settings, then proves Page 70h-triggered APSU/iLT reaches expected status and improves external traffic/FEC behavior. Diagnostic tap state can explain the result, but it is not the formal pass criterion by itself.
_Avoid_: Tap-only proof, diagnostic FIR proof, BER improvement without Page 70h status

**Repeat Degraded-Tap Recovery Set**:
A set of repeated degraded-tap recovery runs using the same declared procedure, labeled endpoints, immutable run numbers, Page 70h trigger/status evidence, and before/after traffic/FEC evidence. Existing historical runs count only when they meet the same evidence bar.
_Avoid_: Screenshot repeatability, unlabeled repeat runs, diagnostic-only repeat set

**APSU-Capable Application Gating**:
The CMIS/OIF capability-advertisement behavior that separates APSU/iLT-capable applications from non-APSU applications. Non-APSU applications must not expose active APSU/iLT controls as supported. If Page 70h remains readable for a non-APSU application, it must show not-capable or default status; writes must be rejected or produce no state change according to the frozen invalid-write declaration, and normal non-APSU CMIS behavior must not regress.
_Avoid_: Page 70h active for all applications, hidden APSU support, non-APSU control enablement

**Link-Partner Interoperability**:
Validation that APSU/iLT link behavior works with a non-Sian3 link partner. This probes training, readiness, fault, and recovery behavior across the physical/link partner boundary. One non-Sian3 partner supports only a bounded first-release claim for that partner class; multiple partner types are expansion coverage unless a customer claim requires broad interoperability.
_Avoid_: Host interop, management interop, broad interoperability from one partner

**Bounded Link-Partner Interop Claim**:
A release or customer-facing interoperability statement limited to the exact non-Sian3 partner identity or partner class, firmware/software revision when available, Ethernet interface, enabled lane set, physical setup, and operating conditions tested. It is used when Page 70h behavior and traffic/FEC pass for the tested setup but the evidence does not cover broad link-partner interoperability.
_Avoid_: Broad interoperability, standards compliance from one partner, customer-general partner claim

**Non-LT-Frame Partner Behavior**:
Behavior observed when the link partner does not provide the expected link-training frames or training-frame lock condition. It becomes formal Page 70h release validation only when Page 70h exposes the related status/fault/recovery path or a customer-facing claim depends on it.
_Avoid_: Default release blocker, broad interop proof, Sian3-only diagnostic result

**Partner Fault Trigger**:
An externally induced partner-side condition, such as squelch or signal loss, used to validate Page 70h readiness, fault, or recovery behavior. The partner condition is external evidence for the trigger; Page 70h remains the formal status surface when module readiness or recovery changes.
_Avoid_: Internal module fault, diagnostic-only trigger, partner log as Page 70h proof

**Host-Management Interoperability**:
Validation that CMIS Page 70h management behavior works with a non-Lumentum or customer-like CMIS host/exerciser. This probes Page 70h access, control, status, polling, and error-handling expectations across the management boundary. One customer-like CMIS host/exerciser supports only a bounded first-release claim for that host/exerciser class; real customer host-stack coverage is expansion unless a customer claim requires customer-host interoperability.
_Avoid_: Link interop, DSP interop, broad customer-host interoperability from one exerciser

**Bounded Host-Management Interop Claim**:
A release or customer-facing management interoperability statement limited to the exact CMIS host, exerciser, scripted host access profile, or setup class tested. It is used when Page 70h access, control, status, polling, retry/error handling, and multi-byte read behavior pass for the tested profile but the evidence does not cover a real customer host stack or broader host ecosystem.
_Avoid_: Broad customer-host interoperability, production host-stack proof, unqualified CMIS host claim

**Host Access Profile**:
The frozen access pattern used for host-management interoperability validation. It records page select and bank select behavior, byte or range read/write sizes, polling interval, retry behavior, error handling, and multi-byte monitor/status read sequence. It should use the current available CMIS host, exerciser, or scripted setup as much as possible, and must bound the release claim to that setup class when it is not a real customer host stack.
_Avoid_: Vague customer-like host, implicit script behavior, unbounded host-stack claim

**Scripted Host Access Profile**:
A host access profile implemented by an internal Python script or similar lab automation against the CMIS interface. It is acceptable for first-release lab validation when all transactions are logged and the release result is bounded to the scripted profile. It is not customer host-stack interoperability unless repeated with an actual customer host stack.
_Avoid_: Customer host proof, production host stack, unqualified host interoperability

**Quantified High-Loss Channel**:
A physical channel-loss condition documented with the strongest available characterization for the claim being made. A release or customer claim about a high-loss channel should use an insertion-loss profile or calibrated fixture characterization when available. A single calibrated VOA attenuation value is acceptable only for a bounded lab-observed attenuation case and must not be generalized as channel-loss compliance. Degraded taps or degraded BER alone do not qualify as a quantified high-loss channel.
_Avoid_: High loss, degraded BER, worse taps

**Bounded Lab-Observed Attenuation Case**:
A lab result tied to a specific calibrated VOA setting or attenuation condition without enough channel characterization to support a general high-loss channel claim. It may support a bounded release note, but not a broad channel-loss compliance claim.
_Avoid_: High-loss channel proof, compliance channel, generalized loss claim

**Release Temperature Points**:
The frozen low, nominal, and high module temperature conditions used for release validation. Pass/fail evidence is based on measured module case temperature; chamber setpoint and dwell time are setup context. Prior evidence points such as 0 C, 45 C, and 70 C are placeholders unless they match the product or customer requirement and are frozen before Gate 4 execution.
_Avoid_: Prior evidence as release requirement, informal temperature corners, unfrozen temperature sweep

**Temperature Stabilization Criterion**:
The predeclared target band and dwell time for measured module case temperature at each release temperature point. Page 70h APSU/iLT actions for temperature validation start only after the measured module case temperature reaches the target band and remains stable for the required dwell time.
_Avoid_: Chamber ramp test, setpoint-only dwell, unstable corner

**Stable Release Temperature Validation**:
Validation at frozen release temperature points after measured module case temperature satisfies the stabilization criterion. It is endpoint validation, not an active temperature-shift test.
_Avoid_: Chamber-setpoint proof, active temperature shift, placeholder corner

**Active Temperature-Shift Test**:
A temperature-transition test that captures APSU/iLT behavior before shift, during ramp or transition, and after dwell at the target temperature. It is distinct from stable endpoint release temperature validation and is required only when exposed through Page 70h or used in a customer claim.
_Avoid_: Endpoint-only temperature corner, stable-temperature duplicate, unclaimed shift behavior

**Bounded Lab-Observed Temperature Case**:
A lab result based on chamber setpoint without measured module case temperature evidence. It may support a bounded release note, but not a full release temperature claim.
_Avoid_: Release temperature proof, chamber-only pass/fail, unmeasured module temperature

**Control-to-Traffic-Recovery Time**:
The elapsed time from the Page 70h control action that starts or restarts APSU/iLT to externally observed traffic/FEC recovery. This is the convergence-time metric for the Page 70h APSU/iLT release validation plan.
_Avoid_: Control-to-training time, control-to-path-up time, status polling timestamp

**Convergence-Time Test**:
A stress validation that measures control-to-traffic-recovery time using Page 70h control acceptance as the start authority and external traffic/FEC recovery as the stop authority. Page 70h status timestamps support analysis but do not define convergence time.
_Avoid_: Status publication latency test, diagnostic recovery timer, path-up-only timing

**Control Acceptance Confirmation**:
Evidence that a Page 70h command or control write was accepted before timing or status polling is treated as formal evidence. For readable controls, confirmation requires write completion plus readback of the effective control or state. For write-only or self-clearing controls, confirmation requires transaction return status plus the next legal observed status transition.
_Avoid_: Raw write timestamp, assumed command acceptance, unconfirmed trigger

**Control Acceptance Failure**:
A supported Page 70h command or control write that returns success but never produces control acceptance confirmation. This is a Page 70h control failure for the affected release claim. Unsupported commands or controls are not classified this way; they are evaluated under the frozen invalid-write declaration.
_Avoid_: Delayed acceptance, successful write, diagnostic-only mismatch

**Control Acceptance Timeout**:
The predeclared maximum wait time for control acceptance confirmation on a supported Page 70h command or control. If CMIS/OIF defines the timeout, that value is used. Otherwise the release/interface spec must freeze the timeout before execution. For write-only or self-clearing controls, timeout expiry without the next legal observed status transition is a control acceptance failure, not a status publication latency result.
_Avoid_: Open-ended wait, post-test timeout, latency substitute

**Control Acceptance Timeout Freeze**:
The Gate 1 declaration of timeout values for supported Page 70h controls before command-driven tests execute. Missing timeout values make affected command, restart, enable/disable, write-only, or self-clearing control tests `Blocked` rather than open-ended.
_Avoid_: Timeout chosen during debug, indefinite wait, status-latency substitute

**Status Publication Latency**:
The elapsed time for Page 70h to publish a status change after the observable trigger for that change. For command-driven changes, the start is Page 70h control transaction completion after control acceptance confirmation. For fault or recovery changes, the start is the independently observed external event. The stop is the first Page 70h read that reports the new stable status. The release validation must either check this against a predeclared limit or, when no numeric limit is available, show it is measured, bounded, and does not create an evidence contradiction inside the declared polling window.
_Avoid_: Convergence time, traffic recovery time, unbounded polling delay

**Management-Status Latency Test**:
A Page 70h timing test that measures only the publication delay of management status after a defined trigger. It is separate from control-to-traffic-recovery time, which measures link recovery using external traffic/FEC evidence.
_Avoid_: Convergence-time test, BER recovery timer, diagnostic timestamp comparison

**Declared Polling Interval**:
The maximum Page 70h polling interval assigned before execution for a specific test case or status class, plus the actual observed polling intervals recorded in the evidence. Missed or failed reads are part of the evidence and cannot be hidden from status publication latency analysis.
_Avoid_: Implicit script loop, best-effort polling, unstated host timing

**Observed Status Sequence**:
The Page 70h status values captured during a test using the declared polling interval. The sequence is not required to include every transient APSU/iLT training state, but every observed transition must be legal for the relevant state machine and must not report a data-ready APSU state before the traffic/FEC recovery criterion is met.
_Avoid_: Complete state trace, inferred missing states, polling-independent state proof

**Legal Status Ordering**:
The allowed order of observed Page 70h APSU/iLT status transitions. The authority is the normative baseline first: OIF Page 70h plus IEEE P802.3dj APSU/iLT state behavior. Where the normative baseline leaves a gap, the release/interface spec mapping must be frozen before execution. Sian3 AN and Sian3 cAPI can explain or correlate ordering, but do not override the Page 70h/IEEE/OIF ordering unless the behavior is explicitly exposed through Page 70h or used in a customer claim.
_Avoid_: Sian3-only ordering, diagnostic ordering, post-test state mapping

**Readiness Ordering Test**:
A Page 70h status validation that proves observed RTS, local ready, remote ready, and path-up/readiness transitions appear in a legal order. It is not the BER recovery proof; traffic/FEC is used only to catch false data-ready reporting.
_Avoid_: Traffic recovery test, BER convergence test, diagnostic-state ordering

**Invalid Test Run**:
A test execution that cannot be used for pass/fail because of an isolated test-infrastructure or host/exerciser failure. The run must be retained in the evidence package and rerun; repeated failures, or a failure that hides an evidence contradiction, are validation failures rather than invalid runs.
_Avoid_: Dropped run, ignored failure, clean rerun

**Immutable Run Number**:
The rule that every execution attempt receives a unique run number, including invalid runs. A rerun does not reuse the invalid run number; it links back as a replacement attempt while the invalid run artifacts remain retained.
_Avoid_: Reused run number, overwritten invalid run, invisible rerun

**Traffic/FEC Recovery**:
The condition where all enabled lanes in a test case meet the test's pre-declared BER criterion for a fixed observation window, with both pre-FEC and post-FEC values captured. The numeric BER threshold and observation window must be set before execution and recorded with the evidence.
_Avoid_: Brief clean sample, partial lane recovery, traffic looks okay

**Enabled Lane Set**:
The host-side or media-side lanes that comprise the Ethernet interface explicitly placed under APSU/iLT control by Page 70h for a test case. Lanes outside that Ethernet interface are out of pass/fail scope unless the test is specifically checking isolation or no-regression behavior.
_Avoid_: Arbitrary lane subset, all physical lanes

**Complete Ethernet-Interface Enablement**:
The normal APSU/iLT enablement case where Page 70h controls the full enabled lane set that comprises the Ethernet interface under test. It is the nominal functional proof; partial-lane enablement is reserved for negative or isolation tests.
_Avoid_: Partial-lane nominal proof, arbitrary lane enablement, reduced-interface pass

**Mapping Manifest**:
The frozen pre-execution mapping that ties Page 70h bank, side, and lane fields to Ethernet interface, enabled lane set, host/media side, DUT/REF labels, physical fixture ports, and traffic/FEC lane IDs. Prefer a manifest exported from the firmware or test-tooling source of truth, with lab annotation for fixture ports and DUT/REF labels. A hand-authored manifest is valid only when versioned, reviewed before Gate 1 exit, and cross-checked by mapping validation. Functional APSU/iLT, stress, and recovery evidence is not valid if the mapping manifest is missing or ambiguous.
_Avoid_: Ad hoc lane labels, post-test mapping, unlabeled fixture setup

**Mapping-First Execution Order**:
The validation order that freezes and verifies the mapping manifest before accepting any lane-specific Page 70h APSU/iLT functional, stress, recovery, coexistence, or interoperability evidence. A later test may run physically before mapping is complete, but it cannot be used for formal pass/fail until the mapping dependency is resolved.
_Avoid_: Post-run mapping fixup, lane labels by memory, deferred mapping prerequisite

**Active Mapping Validation**:
The execution test that proves the frozen mapping manifest by exercising safe Page 70h per-lane or per-interface observations or actions and correlating them to fixture labels and traffic/FEC lane identity. Diagnostic Sian3 state may explain the result but does not replace Page 70h plus external correlation.
_Avoid_: Manifest-only mapping, Sian3-only mapping proof, post-hoc lane inference

**Partial-Lane Test**:
A negative or isolation test that intentionally enables fewer than all lanes in the Ethernet interface lane set. Normal APSU/iLT validation uses the complete Ethernet interface lane set; partial-lane behavior must have an explicit expected result.
_Avoid_: Normal lane enablement, reduced-lane validation

**Restart Domain**:
The Ethernet interface lane set affected by a lane-level APSU/iLT restart or fault. For Sian3 bundled behavior, the restart domain is the full bundled Ethernet interface unless a test explicitly validates a different isolation rule.
_Avoid_: Single-lane restart scope, arbitrary bundle

**Bundled Restart Proof**:
A validation that a Page 70h lane-level restart or fault action affects the expected restart domain. For the Sian3 bundled case, the expected domain is the complete Ethernet interface lane set unless the release explicitly defines a narrower isolation rule.
_Avoid_: Single-lane assumption, unproven bundle behavior, partial-interface restart proof

**Required Implementation Reference Coverage**:
Validation coverage for implementation-reference behavior that the release depends on or exposes through the formal pass/fail interface. Failures in this coverage can block release when they affect Page 70h behavior or customer-facing claims.
_Avoid_: Optional vendor characterization

**Page 70h Exposure Gate**:
The rule that implementation-reference behavior becomes formal release validation only when it is exposed through Page 70h, affects Page 70h behavior, or supports a customer-facing claim. Otherwise it remains diagnostic-only or optional vendor-behavior characterization.
_Avoid_: Debug-only release proof, vendor-feature conformance by default, hidden formal requirement

**Recovery Counter Exposure Test**:
A validation case for recovery reason and recovery event count when those fields are exposed through Page 70h or support a customer-facing claim. Formal validation includes first-read value, read-clear behavior when defined, second-read result, and diagnostic correlation only as supporting evidence.
_Avoid_: Sian3-only recovery counter proof, unread clear behavior, customer claim from debug counter

**Polarity Recovery Exposure Test**:
A validation case for polarity recovery behavior when polarity control/status is exposed through Page 70h or supports a customer-facing claim. It requires an ordered raw log tying induced polarity condition, Page 70h evidence when exposed, traffic/FEC recovery, and diagnostic polarity state when used.
_Avoid_: Screenshot-only polarity proof, diagnostic-only formal pass, unordered polarity evidence

**Precode Exposure Test**:
A validation case for precoding behavior when precoding is exposed through Page 70h or used in a customer-facing claim. Vendor CDB precode helpers may support correlation or coexistence evidence, but Page 70h remains the formal pass/fail interface for Page 70h release validation.
_Avoid_: Vendor-CDB-only precode proof, hidden precode claim, diagnostic precode pass

**Optional Vendor-Behavior Characterization**:
Validation coverage for vendor-specific behavior that improves understanding but is not release-blocking unless the behavior is exposed through Page 70h or included in a customer-facing claim.
_Avoid_: Required conformance test, release blocker

**Slicer/Timer Characterization**:
Vendor-behavior characterization for slicer mode and timer override/readback behavior. It is diagnostic-only by default and becomes formal Page 70h validation only when exposed through Page 70h or used in release/customer claim wording.
_Avoid_: Default release blocker, debug-only formal proof, unclaimed timer conformance

**Customer Request**:
A behavior, setup, or result category the customer has asked to see verified. A customer request drives validation coverage, but it does not automatically become an external statement.
_Avoid_: Customer commitment, release claim

**Customer Claim**:
A statement intended for external customer communication. A customer claim requires supporting evidence and must be bounded when evidence is incomplete.
_Avoid_: Customer request, lab observation

**Bounded Release Note**:
A release note entry that states what was verified, what was not verified, and which customer claims are intentionally not made. It is used when a customer request or optional behavior is not fully covered by release evidence.
_Avoid_: Caveat, disclaimer, informal limitation

**Release Decision Status Label**:
The only status format used in the final release decision summary. Allowed labels are `Pass`, `Fail`, `Blocked`, `Not Run`, `Bounded`, and `Diagnostic Only`. `Diagnostic Only` is reserved for Sian3 cAPI, debug CDB, vendor-only characterization, or supporting evidence that cannot decide formal pass/fail; a Page 70h interface-under-test row must use `Pass`, `Fail`, `Blocked`, `Not Run`, or `Bounded`. Numeric scores, percentage coverage, or weighted coverage summaries are not used because they would overstate the rigor of a gated evidence model.
_Avoid_: Coverage percentage, numeric score, weighted evidence score

**Bounded Page 70h Result**:
A release decision status used when Page 70h behavior passes for the tested scope, but the customer or release claim must be limited because external evidence scope is narrower than the request. Examples include one non-Sian3 partner, one scripted host access profile, a bounded lab-observed attenuation case, or placeholder temperature points. It is not used when Page 70h behavior itself fails.
_Avoid_: Soft fail, partial pass for failed Page 70h behavior, unbounded claim

**Blocked Result**:
A release decision status used when a test is in release scope but cannot proceed because a prerequisite is missing or failed, such as missing Page 70h implementation, missing mapping manifest, missing timeout declaration, or unavailable required setup.
_Avoid_: Not run by choice, deferred optional item, skipped without blocker

**Not Run Result**:
A release decision status used when a test is intentionally outside the current release scope and the reason is recorded. It is not used for in-scope tests blocked by missing prerequisites.
_Avoid_: Blocked test, unexplained skip, hidden failure

**Raw Evidence Retention**:
The rule that final verification evidence must identify or link the raw artifacts behind each result, including Page 70h transaction logs, traffic/FEC logs, timing logs, setup photos, host/script versions, and relevant screenshots. Stable external paths or archive IDs are acceptable when access-controlled and durable; the wiki records enough metadata to retrieve them later. Copy artifacts into the repo only for small, customer-safe screenshots or distilled logs. Summaries are useful for review, but they do not replace raw evidence for auditability.
_Avoid_: Summary-only evidence, unattached screenshot, untraceable result, large raw capture committed to wiki

**Pre-Execution Freeze Checklist**:
The Gate 0/Gate 1 readiness checklist of declarations and source versions that must be frozen before formal lab execution. It includes source/draft versions, release/interface spec mapping, invalid-write declaration, control acceptance timeouts, mapping manifest, host access profile, polling intervals, traffic/FEC recovery criteria, release temperature points and stabilization criteria, loss characterization level, and evidence artifact ID scheme. Missing in-scope checklist items produce `Blocked`, not ad hoc test expectations.
_Avoid_: Test-time declaration, informal readiness, post-run expectation freeze

**Engineering Reviewer Sign-Off**:
The named human approval that freezes the pre-execution checklist before formal lab execution. Tool-generated documentation can prepare the checklist, but a named engineering reviewer must approve source versions, release claims, and pass/fail expectations before Gate 0/Gate 1 exit.
_Avoid_: Tool-only approval, anonymous review, implicit freeze

**Checklist Change Control**:
The rule for any change after the pre-execution checklist is frozen. A post-freeze change creates a new checklist revision. Prior runs remain valid only when the named engineering reviewer records that the change does not affect their setup, expected behavior, or claim scope; otherwise affected tests must be rerun under the new checklist revision. Normative IEEE/OIF changes that touch byte definitions, status meaning, legal ordering, timers, or reserved behavior default to rerun or re-review for affected tests; a no-impact decision is allowed only when the reviewer documents why the tested fields are untouched.
_Avoid_: Silent checklist edit, retroactive expectation change, unreviewed rerun waiver

**Customer-Facing Evidence Package**:
The sanitized customer package derived from the internal evidence archive. It includes bounded claims, summaries, and selected customer-safe excerpts or screenshots. Full raw logs containing internal debug CDB, Sian3 cAPI, internal lab paths, or other sensitive implementation details remain internal under stable archive IDs. Internal debug CDB and Sian3 cAPI evidence may support diagnostic traceability, but they are not customer-facing proof unless explicitly approved.
_Avoid_: Full internal raw-log package, customer proof from debug CDB, unbounded customer excerpt

**Evidence Package Completeness Audit**:
A Gate 5 audit that checks every formal, bounded, blocked, not-run, and diagnostic-only result has the required evidence record, stable artifact IDs, raw paths or archive IDs, setup/script versions, customer-safe excerpts when needed, and a clear boundary between internal evidence and customer-facing material.
_Avoid_: Summary-only audit, customer package without raw traceability, internal debug evidence release

**Claim-To-Evidence Traceability**:
The mapping from each customer-facing claim to one or more internal evidence artifact IDs. A claim can be shown to the customer as a sanitized summary or excerpt, but the internal evidence package must preserve the raw artifact reference. Claims without traceable internal evidence are omitted or marked intentionally unclaimed.
_Avoid_: Untraceable claim, summary-only claim, customer statement without artifact ID

**Final Release Decision Summary**:
The Gate 5 summary that reports Page 70h APSU/iLT release status using only approved status labels. It lists verified claims, bounded claims, intentionally unclaimed items, blocked items, diagnostic-only evidence, customer-facing wording, and the stable internal evidence artifact IDs behind each claim. It does not use numeric scores, percentage coverage, or weighted evidence summaries.
_Avoid_: Scorecard, coverage percentage, weighted release metric

**Evidence Artifact ID**:
A stable human-readable identifier assigned by the evidence package to a retained artifact. The identifier should encode test ID, run number, artifact type, and sequence number, such as `P70H-006-R01-TIMING-001` or `STR-005-R02-TEMP-001`. It must not encode pass/fail status because review status can change while artifact identity remains stable. Raw filenames, filesystem paths, and external archive IDs are metadata attached to the artifact ID, not the primary traceability key, because raw filenames can duplicate or change across report revisions.
_Avoid_: Raw filename as claim ID, unstable path reference, duplicate screenshot ID

**Coexistence Validation**:
Validation that two supported control surfaces can operate during a transition period without creating contradictory behavior. For Page 70h APSU/iLT release validation, vendor CDB and CMIS Page 70h coexist for a while, both reach the module through the CMIS I2C-MCI interface as ordered transactions, and Page 70h remains the formal pass/fail interface.
_Avoid_: Dual authority, equivalent controls

**Coexistence-First Control Validation**:
The validation order that proves Page 70h and vendor CDB share one effective APSU/iLT state before nominal enable/disable behavior is treated as ready for release. It prevents a passing single-surface enable test from hiding cross-surface conflicts during the transition period.
_Avoid_: Single-surface migration proof, independent CDB validation, dual-state acceptance

**Ordered Mixed-Session Writes**:
An ordered sequence of accepted Page 70h and vendor CDB writes through the CMIS I2C-MCI interface during one validation session. Because both surfaces serialize through this interface, coexistence validation does not require true concurrent or high-rate race testing; it requires timestamped transaction order and consistent readback after each accepted write.
_Avoid_: Concurrent control race, independent control path, unsorted mixed log

**Representative Coexistence Coverage**:
The P0 coexistence-validation scope for ordered mixed-session writes. It covers representative controls for each relevant keyed state class, including at least one enable/disable control, one restart or control action when supported, one status/readback path, and one non-reserved invalid control class. Full cross-product coexistence coverage is P1 unless it supports a customer claim.
_Avoid_: Full cross-product by default, single happy-path coexistence, race coverage

**Conflict-Free Control Surface**:
A control surface that operates on the same underlying APSU/iLT state as the other supported control surfaces. The shared effective state is keyed by Ethernet interface, side, lane set, and control field; a control accepted through either Page 70h or vendor CDB updates that keyed state, both surfaces read back the same effective keyed state, the later transaction in an ordered mixed-session sequence wins only for the same key, and unsupported or invalid writes fail or are ignored without partial disagreement.
_Avoid_: Independent state, shadow state, split authority

**Invalid-Write Behavior**:
The predeclared behavior for unsupported or invalid non-reserved control writes. Unless the normative baseline requires a specific response, the release may use explicit error or no state change, but it must be consistent, observable, and must not produce partial mutation or cross-surface disagreement. This does not override CMIS reserved field behavior for reserved bytes or bits.
_Avoid_: Undefined behavior, best effort write

**Invalid-Write Declaration**:
The release/interface-level declaration that names expected behavior for each unsupported or invalid non-reserved write class before formal validation begins. The validation plan references and verifies this declaration; if it is missing, bring-up readiness is not complete.
_Avoid_: Test-time expectation, ad hoc invalid-write handling

**Invalid-Write Rule Freeze**:
The Gate 1 declaration that separates CMIS reserved-field behavior from non-reserved invalid-control behavior before Page 70h byte-map or control tests execute. Missing or post-hoc invalid-write rules make affected tests `Blocked`.
_Avoid_: Test-time invalid-write interpretation, merged reserved/invalid behavior, post-run rule selection

**CMIS Reserved Field Behavior**:
The CMIS rule for reserved bytes or reserved bits: they are read-only, attempted writes are silently rejected, and the write attempt must not change the reserved field or any related module state.
_Avoid_: Writable reserved field, vendor-defined reserved behavior

**Page 70h Byte-Map Foundation**:
The paired validation of implemented Page 70h byte ranges, access permissions, reserved bytes, and reserved bits before functional APSU/iLT control tests are accepted. It establishes that the host sees the expected management surface and that reserved or invalid access does not mutate APSU/iLT state.
_Avoid_: Functional APSU proof, register smoke test, reserved-field characterization

**Non-Reserved Invalid Control Test**:
A Page 70h negative test for unsupported or semantically invalid controls that are not reserved bytes or reserved bits. It verifies the frozen invalid-write declaration, no partial mutation, no cross-surface disagreement, and no APSU/iLT or traffic side effect.
_Avoid_: Reserved-field test, malformed I2C transaction, destructive fuzzing

**CMIS Data Coherency**:
The CMIS requirement that multi-byte monitors and status values are presented coherently to the host. For Page 70h validation, a multi-byte monitor or status read must not expose torn or mixed-generation data as a valid value. Host-script retries may be used for diagnostic robustness, but they do not mask a CMIS data coherency failure.
_Avoid_: Best-effort coherency, host retry as coherency substitute

**Changing-State Coherency Test**:
A data-coherency test that reads multi-byte Page 70h monitors or status repeatedly while APSU/iLT status is transitioning. It proves the module does not expose torn or mixed-generation values as valid during state changes.
_Avoid_: Stable-only coherency test, host-retry proof, status polling latency test
