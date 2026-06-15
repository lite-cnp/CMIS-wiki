---
type: query
title: What is the current I3C bring-up schedule?
created: 2026-06-15
updated: 2026-06-15
tags: [cmis, i3c, schedule, firmware, query]
related: [../sources/huabin-he-2026-i3c-bringup-schedule-planning.md, ../concepts/cmis-over-i3c-firmware-architecture.md]
sources: [../sources/huabin-he-2026-i3c-bringup-schedule-planning.md]
status: draft
---

# What is the current I3C bring-up schedule?

The current schedule is a draft four-phase plan, not a fixed commitment.

## Short Answer

The thread proposes 7 days for STM32 bring-up, then 45 days for PC-to-STM32 bridge work, 30 days for M450 target porting, and 7 days for mixed I3C/I2C compatibility validation. The stated total is 89 days, but the email explicitly says the schedule will be defined further later.

## Current Plan

1. STM32 controller to STM32 target bring-up
2. PC to STM32 bridge plus CMIS register support on STM32 target
3. PC to STM32 bridge plus CMIS register support on M450 target
4. STM32 controller to M450 target with legacy I2C compatibility

## What Is Still Unsettled

- Final schedule dates for phases 2 to 4
- Exact I3CMCI draft/reference to use
- Equipment availability for dongles, analyzers, and sniffers
- Whether the production adapter becomes part of the near-term plan

## Related Pages

- [huabin-he-2026-i3c-bringup-schedule-planning](../sources/huabin-he-2026-i3c-bringup-schedule-planning.md)
- [cmis-over-i3c-firmware-architecture](../concepts/cmis-over-i3c-firmware-architecture.md)
- [i3c-based-management-communication-interface](../concepts/i3c-based-management-communication-interface.md)

