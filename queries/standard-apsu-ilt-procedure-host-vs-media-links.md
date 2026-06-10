---
type: query
title: Standard APSU/iLT procedure and host-vs-media links
created: 2026-06-10
updated: 2026-06-10
tags: [ieee-802-3dj, apsu, ilt, rts, pma, pmd, aui, query]
related: [../concepts/autonomous-path-startup.md, ../sources/ieee-p802-3dj-d2-3.md, ../sources/oif2026-093-08-802-3dj-apsu-draft.md, ../queries/how-do-apsu-and-cmis-state-machines-interact.md]
sources: [../sources/ieee-p802-3dj-d2-3.md, ../sources/oif2026-093-08-802-3dj-apsu-draft.md, ../concepts/autonomous-path-startup.md, ../queries/how-do-apsu-and-cmis-state-machines-interact.md, ../sources/lumentum-2026-dpsm-apsu-ilt-state-machine.md]
status: draft
---

# Standard APSU/iLT Procedure And Host-Vs-Media Links

## Scope And Caveat

This note summarizes the local raw draft source `CMIS/raw/sources/8023dj_D2p3.pdf`, IEEE P802.3dj/D2.3 dated 2025-11-28. It is an unapproved draft and may differ from a later IEEE 802.3dj draft or final publication.

IEEE 802.3dj does not define a CMIS host-management procedure such as "write register X, poll register Y." That mapping is handled by OIF/CMIS Page 70h draft work. IEEE 802.3dj defines the APSU/RTS/ILT functions, variables, training frames, and state diagrams used by AUI components and PMDs.

## Short Answer

The standard APSU/iLT procedure is:

1. Identify the path and every inter-sublayer link, or ISL, in that path.
2. Each APSU-capable ISL has two peer interfaces. An interface is either an AUI component or a PMD.
3. The RTS function propagates readiness from adjacent and peer interfaces.
4. The ILT function establishes peer communication, locks training frames, handles polarity, optionally optimizes signaling, exchanges receiver-ready and RTS information, and coordinates transition to DATA mode.
5. Per-lane ILT moves through the training control states from `QUIET`/training transmission through local and remote training, `ISL_READY`, `PATH_READY`, and `PATH_UP`; recovery and fail states handle loss of lock, readiness loss, or timeout.
6. When an interface has local readiness and remote readiness for the same path, it switches to DATA mode.
7. When all interfaces in the path are in DATA mode, communication on the path is established.

The key state and status variables are `mr_training_enable`, `training_status`, `lane_training_status`, `local_tf_lock`, `remote_tf_lock`, `local_rx_ready`, `remote_rx_ready`, `local_rts`, `remote_rts`, `isl_ready`, `tx_mode`, `polarity_correction`, and recovery/timer variables.

## Annex 178B Functional Flow

| Stage | What happens |
|---|---|
| Capability | An ISL can use APSU when both peer interfaces and related sublayers implement RTS and ILT, or equivalent functions. A PHY, Physical Layer, or path is APSU-capable only if the relevant ISLs can be activated by APSU. |
| RTS initialization | `local_rts` starts false. RTS waits for adjacent-interface readiness through service primitives and, when training is enabled, waits for ILT status to become ready or OK. |
| ILT start | Per-lane ILT begins in `QUIET`, initializes training-related variables, and uses the quiet timer. |
| Training-frame exchange | In training mode, peer interfaces exchange training frames. Training frame lock sets `local_tf_lock`; inverted markers set `polarity_correction`. |
| Local/remote training | `TRAIN_LOCAL` and `TRAIN_REMOTE` allow training-pattern, modulation/precoding, initial-condition, coefficient, and receiver-ready exchange according to the interface type. |
| Receiver ready | Each lane reports local and remote receiver readiness through `local_rx_ready` and `remote_rx_ready`. |
| ISL readiness | When all lane conditions are satisfied, the interface-level status can reach `READY`; per-lane state can pass through `ISL_READY`. |
| Path readiness | RTS propagates readiness across adjacent and peer interfaces. `PATH_READY` holds through a propagation timer before final data transition. |
| Data mode | `PATH_UP` sets `tx_mode = data`; the interface transmits normal data. |
| Recovery/fail | Loss of required lock/readiness, max-wait expiry, recovery-timer expiry, or too many recovery events can force `RECOVERY` or `FAIL`. |

Annex 178B also defines management-visible variables for MDIO mappings, but CMIS modules should use the CMIS/OIF mapping once Page 70h is implemented.

## Host-Side AUI/PMA Link Vs Media-Side PMD Link

The standard-level logic is the same: both host-side and media-side links are ISLs controlled by the Annex 178B RTS/ILT framework. The differences are in what the peer interface is, the medium, and the training-frame or physical-layer details selected by the relevant clause.

| Topic | Host-side PMA/AUI link | Media-side PMD link |
|---|---|---|
| Standard object | Usually an AUI component link, especially C2M between host and module, or C2C inside equipment. In Annex 178B, an AUI component is an interface. | A PMD-to-PMD link across the physical medium between PHYs. In Annex 178B, a PMD is also an interface. |
| ISL definition | Pair of AUI components plus the AUI channel. | Pair of PMDs in different PHYs plus the medium. |
| Module interpretation | Host electrical side of a pluggable module maps naturally to C2M AUI behavior. | Media side maps to the optical or copper PMD behavior of the Ethernet PHY. |
| Training format in local draft | 200 Gb/s-per-lane C2C and C2M AUI components are functionally equivalent to Clause 178/179 PMDs and include ILT with E1 format plus RTS. | Electrical KR/CR PMDs use E1. Optical IMDD PMDs in Clauses 180-183 use O1. Some coherent PMD clauses list ILT/RTS as mandatory for the associated AUIs rather than for the PMD itself. |
| What ILT can tune/request | Electrical AUI/PMD behavior can include coefficient/update style training and precoder request depending on the clause. | Optical IMDD PMD behavior uses O1 training to coordinate modulation, training pattern, precoder state, receiver state, and DATA transition. |
| CMIS timing relationship | In the CMIS/OIF overlay, host-interface APSU or host iLT may begin at `DPInitialized`. | In the CMIS/OIF overlay, media-interface APSU or media iLT may begin at `DPTxTurnOn`. |
| DATA-ready rule | `DPActivated` does not prove host-side live data; APSU/iLT readiness still matters. | Same rule: `DPActivated` does not prove media-side live data; PMD-side APSU/iLT readiness still matters. |

## Practical Takeaway For CMIS Work

For CMIS firmware or validation, keep three layers separate:

- IEEE 802.3dj: Annex 178B defines the RTS/ILT functional state machines and per-interface/per-lane behavior.
- PMD/AUI clauses: select which PMD/AUI types require ILT/RTS and which training frame format or equalization behavior applies.
- OIF/CMIS Page 70h: should expose the standard APSU/iLT control and status surface for modules. Current vendor CDB or Sian3 cAPI paths are implementation-specific until Page 70h is implemented and validated.

The host-side and media-side procedures are therefore not two different APSU algorithms. They are the same APSU/RTS/ILT algorithm instantiated on different ISLs with different physical interface clauses and different CMIS state-machine entry points.
