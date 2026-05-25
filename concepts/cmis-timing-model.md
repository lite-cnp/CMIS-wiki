---
type: concept
title: CMIS Timing Model
created: 2026-05-25
updated: 2026-05-25
tags: [cmis, timing, ral, msl]
related: [management-interface, register-access-layer, command-data-block, versatile-diagnostics-monitoring]
sources: [oif-cmis-05-3]
---

# CMIS Timing Model

The CMIS timing model defines management-related timing requirements for signals, register access, register dependencies, interrupts, and high-speed signal condition interactions.

## Important Timings

| Symbol | Meaning |
|---|---|
| t_reset_init | Minimum Reset assert duration |
| tMgmtInit | Maximum time until the module reaches manageability in ModuleLowPwr |
| tREAD | Maximum READ latency variation |
| tWRITE | Maximum volatile WRITE latency |
| tWRITENV | Maximum non-volatile WRITE latency |
| tBPC | Maximum bank/page change time |
| tCDBF | Maximum CDB foreground processing completion time |
| tCDBC | Maximum CDB command capture time |
| tVDMF | Maximum VDM statistics freeze time |

## Host Implications

The host can either wait for specified maximum durations, retry rejected accesses, or use TEST readiness polling. For dependencies where stale data is possible, the host must wait for the relevant dependency timing rather than expecting the module to reject early reads.

Source anchor: chapter 10, PDF pages 351-355.
