---
type: source
title: Huabin He 2026 I3C Bringup Schedule Planning
created: 2026-06-15
updated: 2026-06-15
tags: [cmis, i3c, mci, schedule, firmware, source]
related: [../concepts/cmis-over-i3c-firmware-architecture.md, ../concepts/i3c-based-management-communication-interface.md, ../queries/what-implementation-decisions-does-cmis-over-i3c-require.md]
authors: [Huabin He, Hock Gin Lim]
year: 2026
venue: Outlook email thread
source_filename: Outlook: Fw: I3C Bringup...
status: draft
---

# Huabin He 2026 I3C Bringup Schedule Planning

This email thread proposes an initial schedule and dependency list for CMIS-over-I3C bring-up across STM32 and M450 platforms. It is explicitly framed as a review draft, with the schedule to be refined later. A follow-up discussion with Huabin confirmed that the early execution should keep Phase 1 and Phase 2 on `STM32H563` EVBs first, then migrate the validated behavior to `M45x/S`.

## Core Proposal

The thread proposes a staged development plan:

1. STM32-to-STM32 I3C controller/target bring-up
2. PC-to-STM32 bridge to STM32 I3C target with CMIS register support
3. PC-to-STM32 bridge to M450 I3C target with CMIS register support
4. STM32 I3C controller to M450 I3C target with legacy I2C compatibility

The thread also calls out the need for I3C dongles, analyzers, and cost-effective production test adapters.

## Follow-Up Decision

After discussion with Huabin, the near-term plan should implement Phase 1 and Phase 2 on `STM32H563` EVBs first. The reason is practical: Huabin has the STM32H563 EVBs available now, and the ST I3C support packages include more mature examples for both controller and target roles. Once the STM32 path proves the controller/target mechanics, bridge flow, and CMIS register-access behavior, the target-side implementation should migrate to `M45x/S` for the XPO/module-side path.

## Schedule Summary

| Phase | Scope | Duration | Dates |
|---|---|---:|---|
| 1 | STM32 I3C controller to STM32 I3C target bring-up | 7 days | 2026-06-15 to 2026-06-25 |
| 2 | PC to STM32 bridge to STM32 target with CMIS register support | 45 days | not explicitly stated |
| 3 | PC to STM32 bridge to M450 target with CMIS register support | 30 days | not explicitly stated |
| 4 | STM32 I3C controller to M450 target with legacy I2C compatibility | 7 days | not explicitly stated |

The email's total estimated duration is 89 days. Treat that estimate as provisional because the follow-up decision shifts the first learning loop toward available STM32H563 EVBs and defers the `M45x/S` migration until after Phase 1 and Phase 2 behavior is understood.

## Dependencies And Open Questions

- `OIF 2026.057.01` and `MIPI I3C v1.2` are the reference baselines for now.
- What exact CMIS-over-I3C behavior is expected.
- How the STM32 and M450 target behaviors should align.
- How to migrate the STM32 target stack and CMIS behavior cleanly into the `M45x/S` / XPO structure.
- What I3C analyzer, sniffer, and dongle equipment is available.
- Whether a cost-effective production I3C dongle should be built around STM32H563/573 boards.

## Relation To The Role Note

This schedule planning email directly extends the uploaded CMIS-over-I3C functional-design-authority note and can be read alongside [oif2026-057-01-firmware-functional-design-authority-cmis-over-i3c](oif2026-057-01-firmware-functional-design-authority-cmis-over-i3c.md).

## Wiki Entry Points

- [cmis-over-i3c-firmware-architecture](../concepts/cmis-over-i3c-firmware-architecture.md)
- [i3c-based-management-communication-interface](../concepts/i3c-based-management-communication-interface.md)
- [management-communication-interface](../concepts/management-communication-interface.md)

Source anchor: Outlook message `Fw: I3C Bringup...`, from Huabin He, received 2026-06-15 02:31:48Z.
