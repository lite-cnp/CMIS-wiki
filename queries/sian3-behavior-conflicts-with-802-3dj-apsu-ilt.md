---
type: query
title: Do Sian3 behaviors conflict with 802.3dj APSU/iLT?
created: 2026-06-10
updated: 2026-06-10
tags: [cmis, apsu, ilt, sian3, ieee-802-3dj, query]
related: [../concepts/autonomous-path-startup.md, ../sources/broadcom-2026-sian3-apsu-application-notes.md, ../sources/oif2026-093-08-802-3dj-apsu-draft.md, ../sources/ieee-p802-3dj-d2-3.md, ../synthesis/apsu-ilt-verification-report.md]
sources: [../sources/broadcom-2026-sian3-apsu-application-notes.md, ../sources/broadcom-2025-sian3-ilt-procedure.md, ../sources/oif2026-093-08-802-3dj-apsu-draft.md, ../sources/ieee-p802-3dj-d2-3.md, ../concepts/autonomous-path-startup.md, ../queries/how-should-hosts-use-sian3-apsu-capi.md, ../queries/how-do-apsu-and-cmis-state-machines-interact.md, ../synthesis/apsu-ilt-verification-report.md, ../synthesis/apsu-ilt-page70h-verification-plan.md]
status: draft
---

# Do Sian3 behaviors conflict with 802.3dj APSU/iLT?

## Short Answer

No direct standards conflict is currently recorded in the vault between Broadcom Sian3 APSU behavior and the IEEE 802.3dj APSU/iLT model.

The current issues are better classified as interface gaps, validation gaps, and customer-claim risks:

- Sian3 cAPI is a vendor-specific implementation of APSU/iLT variables, not a standard CMIS interface.
- Current customer firmware support is vendor CDB based; CMIS Page 70h support is planned, not current.
- Full IEEE 802.3dj APSU path-level conformance and non-Sian3 interoperability remain unverified.
- Some Sian3 behaviors are valid implementation-reference items, but they must be bounded if they are exposed through Page 70h or used in customer-facing claims.

## Baseline

IEEE P802.3dj D2.3 defines APSU as coordinated initialization of inter-sublayer links in a path. It is facilitated by RTS and ILT. RTS propagates readiness for DATA mode; ILT establishes peer communication, optimizes signaling, and coordinates transition to DATA mode.

The OIF APSU draft maps this into CMIS by treating APSU as orthogonal to the normal CMIS state machines. MSM is unchanged, DPSM/NPSM remain configuration state machines, and Page 70h is the planned CMIS control and monitoring surface for APSU applications.

The Sian3 APSU application note is classified as a vendor-specific implementation source aligned to IEEE P802.3dj Annex 178B Draft 2.4. It should be used as implementation evidence, not as a replacement for IEEE/OIF behavior.

## Conflict Check

| Sian3 behavior or current implementation point | Conflict with 802.3dj? | Notes |
|---|---:|---|
| Sian3 exposes APSU/iLT through cAPI fields such as `apsu_en`, `lnktrn_en`, `apsu_control_state`, `training_status`, readiness bits, RTS bits, polarity, and recovery counters. | No | This maps to APSU/iLT concepts, but remains vendor-specific unless mapped through standard CMIS Page 70h. |
| Current customer support uses vendor CDB commands instead of CMIS Page 70h. | No, but claim-sensitive | It conflicts only with a claim that current firmware already supports standard Page 70h APSU/iLT. |
| `DPActivated` is not sufficient for live Ethernet DATA readiness. | No | This aligns with the OIF/IEEE model: CMIS configuration completion is separate from APSU path readiness. |
| Sian3 allows APSU on with LT on both sides, one side, or neither side; and APSU/LT both off. | No direct conflict recorded | The valid matrix should be validated against host/media control masks before customer claims. |
| The Sian3 note does not present APSU off with LT on. | No direct conflict recorded | Treat as a Sian3-supported-configuration limitation unless IEEE/OIF or a customer requirement expects independent LT with APSU off. |
| Rx polarity correction is enabled by default when LT is enabled and returns to user setting when LT is disabled. | No | Verified as lab-observed behavior, but current evidence still lacks a single ordered raw polarity log. |
| Client-side auto NR/ER slicer selection under LT. | No | Vendor behavior; avoid presenting it as a generic 802.3dj/CMIS requirement. |
| Sian3 uses PAM2/PRBS13 in `QUIET`, then requests PRBS31 in `TRAIN_LOCAL`. | No direct conflict recorded | Needs explicit capture if Page 70h or customer claims expose training-pattern sequencing. |
| Electrical-side Tx equalization and precoder request are available; Sian3 optical receiver does not request Tx precoder from the link partner. | No direct conflict recorded | Bound any precoder claim by side/interface. |
| One-lane restart restarts all lanes in a bundled port. | No direct conflict recorded | Must be treated as a bundle restart-domain behavior and validated if exposed through Page 70h or used in release claims. |
| Non-LT frames or partner squelch cause restart behavior. | No direct conflict recorded | Fault/recovery behavior needs validation against formal Page 70h status if customer-visible. |
| FIR did not automatically re-optimize after a 10 C to 60 C temperature shift until LT was restarted. | No, but claim-sensitive | Compatible with treating LT as startup/restart optimization, not continuous adaptation. Do not claim continuous FIR adaptation. |
| Recovery reason and recovery event count are read-clear fields. | No | Diagnostic polling must preserve first-read evidence; Page 70h behavior must be explicitly specified if similar fields are exposed. |

## Claims To Avoid

- Do not claim current standard CMIS Page 70h support; current support is vendor CDB based and Page 70h is planned.
- Do not claim full IEEE 802.3dj APSU path-level conformance from the available Sian3 lab evidence.
- Do not claim `DPActivated` means live Ethernet DATA is ready.
- Do not claim Sian3 cAPI status is a customer-facing CMIS status surface unless it is actually mapped and validated through Page 70h.
- Do not imply continuous FIR adaptation across environmental shifts; the loaded evidence supports restart-based re-optimization.
- Do not generalize Sian3-only behaviors to non-Sian3 link partners without interoperability evidence.

## Validation Implication

For next-release Page 70h validation, the formal pass/fail authority should be CMIS Page 70h plus external traffic/FEC, timing, loss, and temperature evidence. Vendor CDB, lab-only debug CDB, and Sian3 cAPI should remain diagnostic correlation paths.

Any Page 70h status contradiction against external measurements should be treated as a validation failure. The current vault does not record such a contradiction; it records the need to validate Page 70h once implemented.
