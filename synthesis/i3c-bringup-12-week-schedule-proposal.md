---
type: synthesis
title: I3C Bring-Up 12-Week Schedule Proposal
created: 2026-06-15
updated: 2026-06-15
tags: [cmis, i3c, i3cmci, schedule, firmware, roadmap, synthesis]
related: [cmis-over-i3c-roadmap.md, i3c-host-adapter-decision.md, i3c-analyzer-candidate-inventory.md, ../queries/what-is-the-current-i3c-bringup-schedule.md, ../comparisons/i3cmci-required-subset-vs-mipi-i3c-feature-set.md, ../sources/huabin-he-2026-i3c-bringup-schedule-planning.md, ../sources/huabin-he-2026-i3c-host-adapter-candidates.md]
sources: [cmis-over-i3c-roadmap.md, i3c-host-adapter-decision.md, ../queries/what-is-the-current-i3c-bringup-schedule.md, ../comparisons/i3cmci-required-subset-vs-mipi-i3c-feature-set.md, ../sources/oif2026-057-01-i3cmci-draft.md, ../sources/huabin-he-2026-i3c-bringup-schedule-planning.md, ../sources/huabin-he-2026-i3c-host-adapter-candidates.md]
status: draft
---

# I3C Bring-Up 12-Week Schedule Proposal

This proposal consolidates the I3C-MCI draft baseline, the STM32-first execution decision, the analyzer/tool mapping, the production adapter direction, and the scope clarification that I3C-MCI only requires a subset of the full MIPI I3C feature set.

## Baseline Assumptions

- Baseline behavior is `OIF 2026.057.01` plus the I3C-MCI-required subset of `MIPI I3C v1.2` / `I3C Basic v1.2`.
- Phase 1 and Phase 2 start on available `STM32H563/573` EVBs because Huabin has the boards and the ST controller/target examples are more mature.
- `M45x/S` remains the module-side migration target for the XPO path.
- Analyzer validation should use `Introspect` and `SC4420` when available.
- Production `STM32H563/573` Ethernet-to-I3C fan-out should run as a parallel adapter workstream because the original thread explicitly targets low-latency STM32 EVB firmware for lab and factory use.
- The first 12 weeks should prove I3C-MCI register transport, not the full MIPI I3C feature set.
- Transparent bridging to in-module DSPs or other non-CMIS I3C targets is not a normal CMIS management feature. Treat it like `SWD`: a privileged debug interface with explicit enablement, access control, audit logging, and production lock/disable policy.
- Out-of-baseline features include HDR modes, mandatory Hot-Join, mandatory IBI data path, module-side Controller role, multi-controller handoff, virtual targets, and unrestricted transparent bridging to non-CMIS targets.

## Workstreams

| Workstream | Purpose | Week 12 Target |
|---|---|---|
| A. I3C-MCI module bring-up | Prove the required I3C-MCI subset from STM32 reference path to `M45x/S` migration. | `M45x/S` target path demonstrates equivalent CMIS register access and recovery behavior. |
| B. STM32H563/573 Ethernet-to-I3C fan-out adapter | Turn the STM32 controller bridge into a practical low-latency lab/factory adapter path. | Ethernet command path and fan-out prototype are demonstrated or have a clear continuation plan. |
| C. Validation and evidence | Validate the subset with analyzers, logs, and repeatable scripts. | Evidence package separates pass/fail results, tool gaps, and next-phase work. |
| D. Controlled DSP debug bridge | Keep transparent access to in-module DSP I3C targets visible as a debug-interface topic, not a baseline CMIS feature. | Access policy, allowed transaction envelope, enable/disable model, logging, and next-phase implementation gate are reviewed. |

## 12-Week Plan

| Week | Phase | Focus | Exit Gate |
|---:|---|---|---|
| 1 | 0 | Scope, lab, adapter architecture, debug-interface posture, and reference freeze | ST package/example versions, EVB setup, wiring, test harness, I3C-MCI subset checklist, adapter protocol sketch, and DSP bridge security posture are frozen |
| 2-3 | 1 | STM32H563/573 controller-to-target transport plus adapter skeleton | ENTDAA, dynamic address readiness, SDR private read/write, basic error logging, 12.5 MHz smoke path, and local bridge CLI are demonstrated |
| 4-5 | 2 | PC-to-STM32 bridge, host harness, and Ethernet control plane | PC command path issues repeatable I3C private transactions; Ethernet framing, status model, and latency instrumentation are in place |
| 6-7 | 3 | STM32 target CMIS register model, adapter API hardening, and DSP debug-bridge policy | `READ`, `WRITE`, and `TEST` work end to end; adapter API handles transaction IDs, errors, retries, and logging; DSP bridge policy is separated from CMIS register transport |
| 8 | 4 | Analyzer validation, fan-out checkpoint, and DSP bridge security review | Introspect/SC4420 captures confirm DAA/register transactions, adapter fan-out design is reviewed against lab/factory needs, and debug-interface access rules are checkpointed |
| 9-10 | 5 | `M45x/S` target migration, fan-out prototype, and DSP bridge architecture | Target state machine and CMIS behavior are ported behind `M45x/S` HAL; adapter can address one or more controller instances in prototype form; controlled DSP bridge architecture is drafted |
| 11 | 6 | Legacy I2C fallback, robustness, and adapter stress | Legacy fallback, dynamic-address recovery, NACK/timeout handling, mixed-bus smoke tests, Ethernet latency, and adapter reconnect behavior are validated |
| 12 | 7 | Readiness review and handoff | Evidence package, issue list, adapter continuation plan, DSP debug-interface gate, scope decisions, and next-phase recommendations are reviewed |

## Detailed Sub-Tasks

### Phase 0: Scope, lab, and reference freeze

- Confirm exact `STM32H563/573` EVB model: `NUCLEO-H563ZI`, `STM32H573I-DK`, or both.
- Freeze `STM32CubeH5` package version and selected controller/target examples.
- Freeze I3C-MCI-required feature subset against [i3cmci-required-subset-vs-mipi-i3c-feature-set](../comparisons/i3cmci-required-subset-vs-mipi-i3c-feature-set.md).
- Define test harness format for controller logs, target logs, analyzer captures, and pass/fail sheets.
- Confirm board wiring, pull-ups, power setup, and target bus speed.
- Define the Ethernet-to-I3C adapter control model: transport framing, command IDs, status codes, target/controller selection, timeout model, and log format.
- Define the transparent DSP bridge posture as a debug interface, similar to `SWD`: disabled by default, explicitly enabled, access controlled, logged, and lockable for production.
- Decide whether the Week 12 adapter goal is lab-only, factory-prototype, or production-architecture review.
- Decide whether the Week 12 DSP bridge goal is policy-only, architecture review, or a non-shipping proof-of-concept.
- Create open-issue log for spec ambiguity, tool availability, and platform limitations.

### Phase 1: STM32H563/573 controller-to-target transport

- Bring up one STM32 EVB as I3C Controller and one as I3C Target.
- Validate `ENTDAA` and dynamic address assignment.
- Confirm target readiness only after dynamic address assignment.
- Exercise SDR private read/write transfers at basic speed and at the target `12.5 MHz` path.
- Capture NACK, timeout, bus-reset, and re-initialization behavior.
- Create a local bridge CLI or debug shell that can issue deterministic controller transactions before Ethernet is added.
- Keep IBI, Hot-Join, HDR, and multi-controller behavior as optional observations, not required exit criteria.

### Phase 2: PC-to-STM32 bridge and host harness

- Implement a deterministic host command interface for the STM32 controller bridge.
- Map host commands to I3C private read/write transactions.
- Add transaction IDs, timestamps, status codes, and failure classification.
- Add scriptable smoke tests for DAA, read, write, repeated read/write, and negative cases.
- Measure command-response latency and bridge-side buffering limits.
- Add Ethernet transport for the same command model used by the local bridge path.
- Define adapter reconnect, controller reset, and target bus reset behavior.
- Keep production mechanical/package completeness out of Week 5, but keep protocol/API decisions production-conscious.

### Phase 3: STM32 target CMIS register model

- Implement a minimal CMIS memory window on STM32 target firmware.
- Implement `READ`, `WRITE`, and `TEST` behavior over I3C-MCI transport.
- Add page/bank select behavior only to the extent needed for the first validation path.
- Define multi-byte coherency behavior and reject unsupported access patterns cleanly.
- Define retry, NACK, timeout, and recovery behavior before migration to `M45x/S`.
- Produce an end-to-end PC-to-bridge-to-target CMIS register demo.
- Harden adapter API behavior for read/write/test command batching, error propagation, and trace correlation.
- Keep any DSP bridge commands outside the CMIS register map until an explicit debug-interface policy is approved.
- Define the minimum debug-interface controls: target allowlist, command allowlist, session enablement, authorization hook, transaction log, and production disable/lock state.

### Phase 4: Analyzer validation checkpoint

- Validate STM32 reference behavior with `Introspect` if available.
- Validate STM32 reference behavior with `SC4420` if available.
- Capture DAA, assigned address readiness, SDR private read/write, error/recovery, and bridge-generated sequences.
- Compare analyzer interpretation against bridge logs and target logs.
- Review Ethernet-to-I3C fan-out topology: one Ethernet endpoint to one I3C controller, one endpoint to multiple controller boards, or one board controlling multiple I3C buses if hardware supports it.
- Decide what fan-out means for the first prototype: multi-board orchestration, multi-bus control, or factory rack control.
- Review whether controlled DSP bridging needs direct target routing, virtual-target presentation, or a module-MCU-mediated command proxy.
- Confirm analyzer visibility requirements for DSP debug-bridge transactions so future evidence can distinguish CMIS traffic from privileged debug traffic.
- If analyzers are not available by Week 8, freeze the capture plan and continue migration with a recorded validation risk.

### Phase 5: `M45x/S` target migration

- Define the portable target HAL boundary from the STM32 reference implementation.
- Port target state machine, DAA response, private transfer handlers, and CMIS register access to `M45x/S`.
- Integrate with XPO/module-side firmware structure without coupling protocol logic to MCU-specific code.
- Run the same PC-to-STM32 bridge tests against the `M45x/S` target.
- Compare STM32 target behavior and `M45x/S` target behavior at transaction, timing, and recovery levels.
- Record platform-specific differences that need firmware or hardware follow-up.
- Prototype fan-out control using the same host harness against at least one STM32 bridge instance, and document the extension path to multiple controllers.
- Draft the controlled DSP bridge architecture around a module-side policy enforcement point, not raw always-on pass-through.
- Define how approved in-module DSP I3C targets are discovered, named, allowlisted, and isolated from CMIS target behavior.

### Phase 6: Legacy I2C fallback and robustness

- Validate legacy I2C startup and fallback behavior.
- Validate recovery after repeated dynamic-address failures.
- Test mixed I3C/I2C bus smoke cases within the intended CMIS use case.
- Confirm failure handling for unsupported CCCs and out-of-scope MIPI features.
- Re-check CMIS timing and coherency expectations under retry and recovery flows.
- Stress adapter reconnect, command timeout, controller reset, bus reset, and repeated transaction behavior over Ethernet.
- Measure command latency and jitter for the adapter path and identify whether it is suitable for lab automation, factory testing, or both.
- Validate the negative policy path for the DSP bridge design: disabled state, unauthorized request, unsupported target, unsupported command, locked production state, and required logging.

### Phase 7: Readiness review and handoff

- Package source, firmware binaries, host scripts, logs, analyzer captures, and test reports.
- Review compliance against the I3C-MCI-required subset.
- Publish a known-issues list separating firmware defects, spec ambiguities, tool gaps, and platform risks.
- Publish adapter status separately: lab-ready, factory-prototype-ready, or architecture-only.
- Publish controlled DSP bridge status separately: policy-only, architecture-ready, proof-of-concept-ready, or out of next-phase scope.
- Decide whether the next phase should focus on conformance depth, production adapter hardening, IBI alerting, or SWD-like controlled DSP debug bridging.

## Critical Dependencies

- Availability of two STM32H563/573 EVBs and stable ST I3C examples.
- Agreement on exact `OIF 2026.057.01` interpretation for required CCCs and recovery.
- Analyzer availability, especially `Introspect` and `SC4420`.
- Access to `M45x/S` EVB or equivalent XPO target hardware by Week 8.
- Ethernet stack maturity on the selected STM32H563/573 EVB path and agreement on host-side adapter API.
- Clarity on whether production fan-out means multi-board Ethernet orchestration, multi-bus support on one board, or both.
- Agreement that HDR, Hot-Join, virtual targets, full CCC catalog, and unrestricted transparent non-CMIS bridging remain out of the first baseline.
- Agreement on the debug-interface policy for controlled DSP bridging: authorization, enablement, logging, target allowlist, transaction allowlist, and production lock/disable behavior.

## Review Questions

- Should Week 8 analyzer validation block `M45x/S` migration, or proceed as a documented risk if tools are late?
- Which ST example versions should be frozen as the reference input?
- What is the minimum page/bank CMIS register coverage required for the first demo?
- Which recovery behavior from `OIF 2026.057.01` should be treated as mandatory for the Week 12 review?
- What should Week 12 require for the STM32H563/573 Ethernet-to-I3C fan-out: lab prototype, factory prototype, or architecture review?
- Should fan-out target multiple STM32 controller boards first, or multiple I3C buses from one controller board if hardware supports it?
- Should controlled DSP bridging be limited to architecture and policy in the first 12 weeks, or should a non-shipping proof-of-concept be allowed after CMIS register transport is stable?
- Who owns the SWD-like access-control policy for the DSP bridge: module firmware, host-tool software, manufacturing tooling, security review, or a shared gate?

## Related Pages

- [cmis-over-i3c-roadmap](cmis-over-i3c-roadmap.md)
- [i3c-host-adapter-decision](i3c-host-adapter-decision.md)
- [what-is-the-current-i3c-bringup-schedule](../queries/what-is-the-current-i3c-bringup-schedule.md)
- [i3cmci-required-subset-vs-mipi-i3c-feature-set](../comparisons/i3cmci-required-subset-vs-mipi-i3c-feature-set.md)
- [i3c-analyzer-candidate-inventory](i3c-analyzer-candidate-inventory.md)
