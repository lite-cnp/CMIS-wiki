# Wiki Index

## Start Here

- [overview](overview.md) - current wiki overview.
- [cmis-5-4-implementer-map](synthesis/cmis-5-4-implementer-map.md) - implementation reading order for CMIS 5.4.
- [cmis-document-family-map](synthesis/cmis-document-family-map.md) - classification of base specs, supplements, drafts, IEEE references, and vendor-specific notes.
- [i3c-host-adapter-decision](synthesis/i3c-host-adapter-decision.md) - recommended lab and production adapter path for CMIS-over-I3C.
- [i3c-analyzer-candidate-inventory](synthesis/i3c-analyzer-candidate-inventory.md) - named I3C analyzer and adapter products plus unresolved internal gear.

## Entities

- [oasis-oif](entities/oasis-oif.md) - Optical Internetworking Forum, publisher of CMIS base specifications and supplements.
- [cmis-host](entities/cmis-host.md) - Managing side that initiates CMIS management access.
- [cmis-managed-module](entities/cmis-managed-module.md) - Managed module target exposed through CMIS.

## Concepts

- [cmis-5-4](concepts/cmis-5-4.md) - Current CMIS base revision represented in this vault.
- [cmis-management-stack](concepts/cmis-management-stack.md) - Layered view of CMIS management protocols and responsibilities.
- [management-interface](concepts/management-interface.md) - MSL, RAL, and MCI as the module management interface.
- [register-access-layer](concepts/register-access-layer.md) - READ, WRITE, TEST, access hold-off, and coherency rules.
- [management-communication-interface](concepts/management-communication-interface.md) - I2CMCI, SPIMCI, and draft I3CMCI context.
- [management-memory-map](concepts/management-memory-map.md) - CMIS pages, banks, lower/upper memory, flags, masks, and access types.
- [low-memory-register-map](concepts/low-memory-register-map.md) - Detailed CMIS 5.4 Lower Memory byte map with an embedded C register-view struct.
- [upper-page-00h-register-map](concepts/upper-page-00h-register-map.md) - CMIS 5.4 Page 00h administrative information register map.
- [upper-page-01h-register-map](concepts/upper-page-01h-register-map.md) - CMIS 5.4 Page 01h advertising register map.
- [upper-page-02h-register-map](concepts/upper-page-02h-register-map.md) - CMIS 5.4 Page 02h supervision threshold register map.
- [upper-page-04h-register-map](concepts/upper-page-04h-register-map.md) - CMIS 5.4 Page 04h tunable laser capability register map.
- [upper-page-0dh-register-map](concepts/upper-page-0dh-register-map.md) - CMIS 5.4 Page 0Dh firmware management register map.
- [upper-page-10h-register-map](concepts/upper-page-10h-register-map.md) - CMIS 5.4 banked Page 10h lane and data-path control register map.
- [upper-page-11h-register-map](concepts/upper-page-11h-register-map.md) - CMIS 5.4 banked Page 11h lane and data-path status register map.
- [upper-page-12h-register-map](concepts/upper-page-12h-register-map.md) - CMIS 5.4 banked Page 12h tunable laser control and status register map.
- [upper-page-13h-register-map](concepts/upper-page-13h-register-map.md) - CMIS 5.4 banked Page 13h diagnostics control register map.
- [upper-page-14h-register-map](concepts/upper-page-14h-register-map.md) - CMIS 5.4 banked Page 14h diagnostics result register map.
- [upper-page-18h-register-map](concepts/upper-page-18h-register-map.md) - CMIS-VCS Page 18h staged Control Set overflow register map.
- [upper-page-19h-register-map](concepts/upper-page-19h-register-map.md) - CMIS-VCS Page 19h active Control Set overflow register map.
- [upper-page-2fh-register-map](concepts/upper-page-2fh-register-map.md) - CMIS 5.4 banked Page 2Fh VDM advertisement and dynamic control register map.
- [applications-and-data-paths](concepts/applications-and-data-paths.md) - Application advertisement, lane assignment, and Data Path instances.
- [control-sets](concepts/control-sets.md) - Active and staged configuration sets plus Apply triggers.
- [module-state-machine](concepts/module-state-machine.md) - Module power/manageability lifecycle.
- [data-path-state-machine](concepts/data-path-state-machine.md) - Data Path initialization and activation lifecycle.
- [network-path-applications](concepts/network-path-applications.md) - Client encapsulation, Host Paths, Network Paths, and NPSM.
- [versatile-diagnostics-monitoring](concepts/versatile-diagnostics-monitoring.md) - VDM observables, thresholds, samples, flags, masks, and statistics.
- [multipath-interference-mpi-metrics](concepts/multipath-interference-mpi-metrics.md) - Broadcom vendor MPI metrics used as dust-detection diagnostics and possible CMIS/VDM mapping candidates.
- [mpi-calibration-module-vendor](concepts/mpi-calibration-module-vendor.md) - module-vendor method for calibrating unitless MPI metrics into dB-like customer values.
- [command-data-block](concepts/command-data-block.md) - Optional CDB command/reply messaging.
- [cmis-timing-model](concepts/cmis-timing-model.md) - Management timing requirements and host timing choices.
- [cmis-supplements](concepts/cmis-supplements.md) - CMIS supplement specifications and compatibility principle.
- [cmis-versatile-control-set](concepts/cmis-versatile-control-set.md) - Optional VCS supplement for flexible signal-integrity parameters.
- [coherent-cmis](concepts/coherent-cmis.md) - C-CMIS supplement for coherent modules.
- [cmis-form-factor-management](concepts/cmis-form-factor-management.md) - CMIS-FF form-factor hardware management supplement.
- [elsfp-cmis](concepts/elsfp-cmis.md) - ELSFP external laser resource module companion IA.
- [i3c-based-management-communication-interface](concepts/i3c-based-management-communication-interface.md) - Draft I3C-based CMIS MCI variant.
- [cmis-over-i3c-firmware-architecture](concepts/cmis-over-i3c-firmware-architecture.md) - Implementation architecture for CMIS-over-I3C target firmware, HAL, and validation.
- [autonomous-path-startup](concepts/autonomous-path-startup.md) - Draft IEEE 802.3dj APSU integration context plus vendor implementation notes.
- [vendor-specific-cmis-customizations](concepts/vendor-specific-cmis-customizations.md) - Boundary for vendor-specific CMIS behavior.
- [spec-to-wiki-transformation](concepts/spec-to-wiki-transformation.md) - Methodology for decomposing a specification into a structured wiki.

## Sources

- [oif-cmis-05-4](sources/oif-cmis-05-4.md) - OIF-CMIS-05.4 current base source page.
- [oif-cmis-05-3](sources/oif-cmis-05-3.md) - OIF-CMIS-05.3 source page and document map.
- [oif-cmis-vcs-01-1](sources/oif-cmis-vcs-01-1.md) - CMIS-VCS supplement source.
- [oif-cmis-ff-01-0](sources/oif-cmis-ff-01-0.md) - CMIS-FF supplement source.
- [oif-c-cmis-01-4](sources/oif-c-cmis-01-4.md) - C-CMIS coherent supplement source.
- [oif-elsfp-cmis-01-0](sources/oif-elsfp-cmis-01-0.md) - ELSFP CMIS source.
- [oif2026-057-01-i3cmci-draft](sources/oif2026-057-01-i3cmci-draft.md) - I3CMCI draft source.
- [oif2026-057-01-firmware-functional-design-authority-cmis-over-i3c](sources/oif2026-057-01-firmware-functional-design-authority-cmis-over-i3c.md) - Firmware role note for CMIS over I3C implementation, validation, and HAL ownership.
- [huabin-he-2026-i3c-bringup-schedule-planning](sources/huabin-he-2026-i3c-bringup-schedule-planning.md) - Outlook schedule-planning thread for I3C bring-up across STM32 and M450 platforms.
- [mipi-i3c-basic-v1-2-hot-join-app-note](sources/mipi-i3c-basic-v1-2-hot-join-app-note.md) - Public MIPI Hot-Join application note for I3C Basic v1.2.
- [mipi-i3c-virtual-devices-and-targets-app-note](sources/mipi-i3c-virtual-devices-and-targets-app-note.md) - Public MIPI note on virtual devices and virtual targets.
- [mipi-i3c-version-history-table](sources/mipi-i3c-version-history-table.md) - Public I3C/I3C Basic feature version history table.
- [mipi-i3c-v1-1-current-dcr-table](sources/mipi-i3c-v1-1-current-dcr-table.md) - Public current DCR table for I3C implementers.
- [mipi-i3c-basic-v1-2-whats-new-webinar](sources/mipi-i3c-basic-v1-2-whats-new-webinar.md) - Public webinar summarizing what’s new in I3C Basic and the ecosystem.
- [mipi-i3c-basic-faq-v1-1-1](sources/mipi-i3c-basic-faq-v1-1-1.md) - Public FAQ for MIPI I3C Basic v1.1.1 and version/licensing context.
- [mipi-i3c-basic-v1-1-1](sources/mipi-i3c-basic-v1-1-1.md) - Public normative MIPI I3C Basic v1.1.1 specification.
- [huabin-he-2026-i3c-host-adapter-candidates](sources/huabin-he-2026-i3c-host-adapter-candidates.md) - Outlook thread capturing I3C host adapter and analyzer candidates.
- [oif2026-093-08-802-3dj-apsu-draft](sources/oif2026-093-08-802-3dj-apsu-draft.md) - APSU CMIS draft source.
- [lumentum-2026-8023dj-apsu-ilt-support-plan](sources/lumentum-2026-8023dj-apsu-ilt-support-plan.md) - current APSU/iLT customer-note plan using vendor CDB today and planned CMIS Page 70h alignment later.
- [lumentum-2026-dpsm-apsu-ilt-state-machine](sources/lumentum-2026-dpsm-apsu-ilt-state-machine.md) - state-machine diagram showing APSU/iLT actions as orthogonal to DPSM.
- [broadcom-2026-sian3-apsu-application-notes](sources/broadcom-2026-sian3-apsu-application-notes.md) - Broadcom Sian3 APSU/link-training application note and cAPI source.
- [broadcom-2025-sian3-ilt-procedure](sources/broadcom-2025-sian3-ilt-procedure.md) - obsolete Broadcom Sian3 ILT BERT/DUT procedure source.
- [broadcom-2025-mpi-metrics-feature](sources/broadcom-2025-mpi-metrics-feature.md) - Broadcom MPI metrics application note for optical dust-detection diagnostics using unitless cAPI metrics.
- [feng-jiang-2026-sian3-link-training-verification-email-thread](sources/feng-jiang-2026-sian3-link-training-verification-email-thread.md) - Outlook thread summarizing Sian3 BERT/DUT link-training verification setup, procedures, and results.
- [ieee-802-3-2022](sources/ieee-802-3-2022.md) - IEEE 802.3 base source stub.
- [ieee-p802-3dj-d2-3](sources/ieee-p802-3dj-d2-3.md) - IEEE 802.3dj draft source for APSU.
- [google-gmis-imdd-transceiver-customizations](sources/google-gmis-imdd-transceiver-customizations.md) - vendor-specific GMIS source stub.
- [thinkwe-need-to-answer-the-user-they-said-yes-to-m-2026-05-21-073851](sources/thinkwe-need-to-answer-the-user-they-said-yes-to-m-2026-05-21-073851.md) - Legacy starter guide for turning a specification into a wiki.

## Code Artifacts

- [cmis-5-4-upper-page-registers.h](code/cmis-5-4-upper-page-registers.h) - Detailed little-endian ARM-oriented C register views for the CMIS 5.4 upper pages documented in this wiki.

## Project Docs

- [CONTEXT](CONTEXT.md) - domain language for CMIS APSU/iLT validation, evidence, and release-decision terms.
- [ADR 0001 Page 70h and Vendor CDB Coexistence](docs/adr/0001-page70h-and-vendor-cdb-coexistence.md) - decision record for Page 70h/vendor CDB coexistence through ordered CMIS I2C-MCI transactions.

## Queries

- [cmis-cdb-command-table-errata](queries/cmis-cdb-command-table-errata.md) - Audit notes for likely CMIS 5.3/5.4 CDB command table mistakes in command IDs, check codes, payload lengths, reply references, and byte ranges.
- [what-is-cdb-command-0045h-for](queries/what-is-cdb-command-0045h-for.md) - Explains `CMD 0045h` as the base-CMIS supplement-support discovery command, especially for CMIS-VCS.
- [security-related-cdb-commands](queries/security-related-cdb-commands.md) - Explanation of CMIS security-related CDB command discovery, certificate retrieval, digest signing, signature retrieval, and password-command boundaries.
- [how-should-a-host-bring-up-a-cmis-module](queries/how-should-a-host-bring-up-a-cmis-module.md) - Host-oriented CMIS bring-up flow.
- [how-do-apsu-and-cmis-state-machines-interact](queries/how-do-apsu-and-cmis-state-machines-interact.md) - Draft APSU and CMIS state-machine interaction.
- [how-should-hosts-use-sian3-apsu-capi](queries/how-should-hosts-use-sian3-apsu-capi.md) - Host use of Broadcom Sian3 APSU cAPI during bring-up.
- [how-should-hosts-use-broadcom-mpi-metrics](queries/how-should-hosts-use-broadcom-mpi-metrics.md) - Host guidance for using Broadcom MPI metrics as vendor dust-detection diagnostics without overclaiming CMIS standardization.
- [ieee-apsu-ilt-fields-missing-from-sian3-capi](queries/ieee-apsu-ilt-fields-missing-from-sian3-capi.md) - Gap matrix comparing IEEE Annex 178B APSU/iLT variables against documented Sian3 cAPI fields.
- [sian3-behavior-conflicts-with-802-3dj-apsu-ilt](queries/sian3-behavior-conflicts-with-802-3dj-apsu-ilt.md) - Conflict audit for Sian3 APSU/iLT behavior against IEEE 802.3dj and OIF Page 70h expectations.
- [standard-apsu-ilt-procedure-host-vs-media-links](queries/standard-apsu-ilt-procedure-host-vs-media-links.md) - Standard APSU/iLT functional flow and host-side AUI/PMA versus media-side PMD link differences.
- [what-implementation-decisions-does-cmis-over-i3c-require](queries/what-implementation-decisions-does-cmis-over-i3c-require.md) - Implementation decisions needed to ship CMIS over I3C beyond the draft transport text.
- [what-is-the-current-i3c-bringup-schedule](queries/what-is-the-current-i3c-bringup-schedule.md) - Draft 4-phase bring-up schedule and unresolved dependencies.
- [Legacy starter query](queries/thinkwe-need-to-answer-the-user-they-said-yes-to-m-2026-05-21-073851.md)

## Comparisons

- [cmis-5-3-to-5-4](comparisons/cmis-5-3-to-5-4.md) - Summary of CMIS 5.4 changes relative to 5.3.
- [cmis-5-2-to-5-3](comparisons/cmis-5-2-to-5-3.md) - Summary of CMIS 5.3 changes relative to 5.2.
- [mipi-i3c-basic-v1-1-1-vs-v1-2](comparisons/mipi-i3c-basic-v1-1-1-vs-v1-2.md) - Public I3C Basic baseline versus the newer recommended public version.
- [i3c-host-adapter-candidate-vs-public-baseline](comparisons/i3c-host-adapter-candidate-vs-public-baseline.md) - Internal adapter candidates linked to the public MIPI I3C references that justify them.

## Synthesis

- [cmis-document-family-map](synthesis/cmis-document-family-map.md) - Classification map for CMIS base specs, supplements, drafts, and references.
- [cmis-5-4-implementer-map](synthesis/cmis-5-4-implementer-map.md) - Implementation-oriented reading map for CMIS 5.4.
- [cmis-5-3-implementer-map](synthesis/cmis-5-3-implementer-map.md) - Implementation-oriented reading map for the generated wiki.
- [apsu-ilt-customer-note-plan](synthesis/apsu-ilt-customer-note-plan.md) - current APSU/iLT implementation status and customer-note development plan.
- [apsu-ilt-verification-report](synthesis/apsu-ilt-verification-report.md) - customer-safe APSU/iLT verification status, evidence boundaries, open gaps, and validation actions for the 1.6T 2xDR4 FRO module.
- [apsu-ilt-page70h-verification-plan](synthesis/apsu-ilt-page70h-verification-plan.md) - internal engineering verification plan and low-level test-case sheets for next-release CMIS Page 70h APSU/iLT firmware validation.
- [cmis-over-i3c-roadmap](synthesis/cmis-over-i3c-roadmap.md) - combined roadmap for draft I3CMCI, firmware architecture, and the provisional bring-up schedule.
- [mpi-customer-requirements-from-email](synthesis/mpi-customer-requirements-from-email.md) - customer-facing MPI requirements from MSFT, Broadcom, Marvell, Google/ZFR8, VM8, and Gungnir-S email evidence.
