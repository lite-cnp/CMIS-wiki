---
type: query
title: What is the current I3C bring-up schedule?
created: 2026-06-15
updated: 2026-06-15
tags: [cmis, i3c, schedule, firmware, query]
related: [../sources/huabin-he-2026-i3c-bringup-schedule-planning.md, ../synthesis/cmis-over-i3c-roadmap.md, ../comparisons/i3cmci-required-subset-vs-mipi-i3c-feature-set.md, ../concepts/cmis-over-i3c-firmware-architecture.md]
sources: [../sources/huabin-he-2026-i3c-bringup-schedule-planning.md, ../synthesis/cmis-over-i3c-roadmap.md, ../comparisons/i3cmci-required-subset-vs-mipi-i3c-feature-set.md]
status: draft
---

# What is the current I3C bring-up schedule?

The current schedule is a draft plan, not a fixed commitment. The latest working decision is to implement Phase 1 and Phase 2 on available `STM32H563/573` EVBs first, then migrate the validated target behavior to `M45x/S`.

## Short Answer

Use `STM32H563/573` EVBs as the first execution platform because Huabin has the boards now and the ST I3C support packages include more mature controller-side and target-side examples. After STM32 Phase 1 and Phase 2 prove the transport, bridge, and CMIS register-access behavior, migrate the target stack to `M45x/S` for the XPO/module-side path. Track the Ethernet-to-I3C fan-out adapter in parallel, and treat any transparent bridge to in-module DSP I3C targets like `SWD`: a privileged debug interface, not normal CMIS management traffic. The original 89-day estimate remains provisional and should be re-estimated after the STM32 reference path is running.

## Reference Baselines

- `OIF 2026.057.01` for I3CMCI behavior.
- I3CMCI-required subset of `MIPI I3C v1.2` / `I3C Basic v1.2` controller/target behavior, not the full MIPI feature set.
- ST `STM32H563/573` EVB examples as the first firmware learning/reference path.
- SWD-like access-control posture for transparent DSP bridging: disabled by default, explicitly enabled, allowlisted, logged, and lockable or removable for production use.

## Updated Schedule

| Phase | Focus | Provisional Duration | Entry Condition | Exit Gate |
|---|---|---:|---|---|
| 0 | Reference and lab setup freeze | 1-2 days | STM32H563/573 EVBs available | ST package/example versions, board wiring, and baseline test setup recorded |
| 1 | STM32H563/573 controller-to-target basic I3C bring-up | 7 days | Two STM32 EVBs ready | Dynamic Address Assignment, private read/write, optional IBI observation, and 12.5 MHz transfer test pass or have tracked issues |
| 2 | PC-to-STM32 bridge plus STM32 target CMIS register access | 45 days | Phase 1 transport stable enough for register work | PC-initiated CMIS read/write path works through the bridge to the STM32 target |
| 3 | Analyzer validation with Introspect and SC4420 | TBD / parallel when tools arrive | Analyzer fixtures available | Captures confirm protocol behavior or identify tool/firmware discrepancies |
| 4 | M45x/S target migration for XPO/module-side path | 30 days | STM32 target behavior and CMIS access model understood | M45x/S target supports equivalent CMIS register access through the STM32 bridge |
| 5 | Legacy I2C compatibility, I3C-MCI conformance, and controlled DSP debug-bridge policy | 7 days initial compatibility pass plus TBD conformance work | M45x/S target path stable | Mixed I3C/I2C behavior validated and non-CMIS DSP target bridging is gated by SWD-like debug-interface policy |

## Phase Details

### Phase 0: Reference and lab setup freeze

- Freeze the ST package/example versions used for the STM32 reference path.
- Record the exact EVB type, wiring, power setup, and bus-speed target.
- Confirm whether `NUCLEO-H563ZI`, `STM32H573I-DK`, or both are in Huabin's available setup.
- Keep `OIF 2026.057.01` and `MIPI I3C v1.2` as the behavior baselines.

### Phase 1: STM32H563/573 EVB controller-to-target transport

- Configure one STM32 EVB as I3C controller and one as I3C target.
- Validate Dynamic Address Assignment.
- Validate private read/write transactions.
- Observe IBI behavior if the ST examples expose it cleanly.
- Test the target bus speed from the original proposal, especially the 12.5 MHz path.
- Record driver limitations and any behavior that must not leak into the later portable target stack.

### Phase 2: PC-to-STM32 bridge and STM32 target CMIS register access

- Bring up the upstream PC-to-bridge path, initially matching the SUB-20-oriented proposal where applicable.
- Convert upstream control messages into I3C private read/write transactions.
- Add a minimal CMIS register model on the STM32 target.
- Validate end-to-end register read/write from PC through the STM32 bridge to the STM32 target.
- Define basic retry, timeout, NACK, and recovery behavior before migrating to `M45x/S`.
- Keep any future DSP bridge command path separate from the CMIS register-access baseline until an explicit debug-interface policy is approved.

### Phase 3: Analyzer validation

- Validate the STM32 reference behavior with Introspect once available.
- Validate the same behavior with SC4420 once available.
- Compare capture quality, timing visibility, and controller/target transaction interpretation.
- Use findings to decide which analyzer becomes the main debug reference.

### Phase 4: M45x/S migration

- Port the target-side state machine and CMIS register behavior to `M45x/S`.
- Keep protocol logic separate from the `M45x/S` HAL and XPO integration code.
- Compare STM32-target behavior against `M45x/S` behavior using the same controller/bridge transactions.
- Close platform-specific timing, interrupt, and recovery gaps.

### Phase 5: Compatibility and controlled expansion

- Validate legacy I2C coexistence on the same bus.
- Check fallback behavior when legacy devices or repeated dynamic-address failures are present.
- Complete I3C-MCI / CMIS conformance checks once the target path is stable.
- Add transparent bridging only for approved in-module targets, such as DSPs, under an explicit SWD-like debug-interface policy.
- Require target allowlist, transaction allowlist, explicit enablement, authorization hook, audit log, and production lock/disable behavior before any bridge implementation is treated as release-eligible.

## What Is Still Unsettled

- Final schedule dates for the STM32-first phases and the M45x/S migration
- Exact ST support-package/example versions to freeze for the STM32 reference path
- Equipment availability for dongles, analyzers, and sniffers
- Detailed register-access, error-recovery, and HAL-abstraction behavior for migration
- Exact Week 12 target for the Ethernet-to-I3C fan-out adapter: lab prototype, factory prototype, or architecture review
- Whether controlled DSP bridging stays policy-only in the 12-week plan or allows a non-shipping proof-of-concept after CMIS transport is stable

## External Review Links

- [ST NUCLEO-H563ZI](https://www.st.com/en/evaluation-tools/nucleo-h563zi.html)
- [ST STM32H573I-DK](https://www.st.com/en/evaluation-tools/stm32h573i-dk.html)
- [STMicroelectronics STM32CubeH5 firmware package](https://github.com/STMicroelectronics/STM32CubeH5)
- [MIPI I3C specification page](https://www.mipi.org/specifications/i3c-sensor-specification)
- [Introspect Technology I3C design and test](https://introspect.ca/products-solutions/i3c-design-and-test/)
- [SignalCraft SC4420](https://www.signalcraft.com/products/serial-bus-controllers/sc4420/)

## Related Pages

- [huabin-he-2026-i3c-bringup-schedule-planning](../sources/huabin-he-2026-i3c-bringup-schedule-planning.md)
- [cmis-over-i3c-roadmap](../synthesis/cmis-over-i3c-roadmap.md)
- [i3cmci-required-subset-vs-mipi-i3c-feature-set](../comparisons/i3cmci-required-subset-vs-mipi-i3c-feature-set.md)
- [cmis-over-i3c-firmware-architecture](../concepts/cmis-over-i3c-firmware-architecture.md)
- [i3c-based-management-communication-interface](../concepts/i3c-based-management-communication-interface.md)
