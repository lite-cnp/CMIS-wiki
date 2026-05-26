# Wiki Index

## Start Here

- [[overview]] - current wiki overview.
- [[cmis-5-4-implementer-map]] - implementation reading order for CMIS 5.4.
- [[cmis-document-family-map]] - classification of base specs, supplements, drafts, IEEE references, and vendor-specific notes.

## Entities

- [[oasis-oif]] - Optical Internetworking Forum, publisher of CMIS base specifications and supplements.
- [[cmis-host]] - Managing side that initiates CMIS management access.
- [[cmis-managed-module]] - Managed module target exposed through CMIS.

## Concepts

- [[cmis-5-4]] - Current CMIS base revision represented in this vault.
- [[cmis-management-stack]] - Layered view of CMIS management protocols and responsibilities.
- [[management-interface]] - MSL, RAL, and MCI as the module management interface.
- [[register-access-layer]] - READ, WRITE, TEST, access hold-off, and coherency rules.
- [[management-communication-interface]] - I2CMCI, SPIMCI, and draft I3CMCI context.
- [[management-memory-map]] - CMIS pages, banks, lower/upper memory, flags, masks, and access types.
- [[low-memory-register-map]] - Detailed CMIS 5.4 Lower Memory byte map with an embedded C register-view struct.
- [[applications-and-data-paths]] - Application advertisement, lane assignment, and Data Path instances.
- [[control-sets]] - Active and staged configuration sets plus Apply triggers.
- [[module-state-machine]] - Module power/manageability lifecycle.
- [[data-path-state-machine]] - Data Path initialization and activation lifecycle.
- [[network-path-applications]] - Client encapsulation, Host Paths, Network Paths, and NPSM.
- [[versatile-diagnostics-monitoring]] - VDM observables, thresholds, samples, flags, masks, and statistics.
- [[command-data-block]] - Optional CDB command/reply messaging.
- [[cmis-timing-model]] - Management timing requirements and host timing choices.
- [[cmis-supplements]] - CMIS supplement specifications and compatibility principle.
- [[cmis-versatile-control-set]] - Optional VCS supplement for flexible signal-integrity parameters.
- [[coherent-cmis]] - C-CMIS supplement for coherent modules.
- [[cmis-form-factor-management]] - CMIS-FF form-factor hardware management supplement.
- [[elsfp-cmis]] - ELSFP external laser resource module companion IA.
- [[i3c-based-management-communication-interface]] - Draft I3C-based CMIS MCI variant.
- [[autonomous-path-startup]] - Draft IEEE 802.3dj APSU integration context.
- [[vendor-specific-cmis-customizations]] - Boundary for vendor-specific CMIS behavior.
- [[spec-to-wiki-transformation]] - Methodology for decomposing a specification into a structured wiki.

## Sources

- [[sources/oif-cmis-05-4]] - OIF-CMIS-05.4 current base source page.
- [[sources/oif-cmis-05-3]] - OIF-CMIS-05.3 source page and document map.
- [[sources/oif-cmis-vcs-01-1]] - CMIS-VCS supplement source.
- [[sources/oif-cmis-ff-01-0]] - CMIS-FF supplement source.
- [[sources/oif-c-cmis-01-4]] - C-CMIS coherent supplement source.
- [[sources/oif-elsfp-cmis-01-0]] - ELSFP CMIS source.
- [[sources/oif2026-057-01-i3cmci-draft]] - I3CMCI draft source.
- [[sources/oif2026-093-08-802-3dj-apsu-draft]] - APSU CMIS draft source.
- [[sources/ieee-802-3-2022]] - IEEE 802.3 base source stub.
- [[sources/ieee-p802-3dj-d2-3]] - IEEE 802.3dj draft source for APSU.
- [[sources/google-gmis-imdd-transceiver-customizations]] - vendor-specific GMIS source stub.
- [[sources/thinkwe-need-to-answer-the-user-they-said-yes-to-m-2026-05-21-073851]] - Legacy starter guide for turning a specification into a wiki.

## Queries

- [[queries/how-should-a-host-bring-up-a-cmis-module]] - Host-oriented CMIS bring-up flow.
- [[queries/how-do-apsu-and-cmis-state-machines-interact]] - Draft APSU and CMIS state-machine interaction.
- [[queries/thinkwe-need-to-answer-the-user-they-said-yes-to-m-2026-05-21-073851|Legacy starter query]]

## Comparisons

- [[cmis-5-3-to-5-4]] - Summary of CMIS 5.4 changes relative to 5.3.
- [[cmis-5-2-to-5-3]] - Summary of CMIS 5.3 changes relative to 5.2.

## Synthesis

- [[cmis-document-family-map]] - Classification map for CMIS base specs, supplements, drafts, and references.
- [[cmis-5-4-implementer-map]] - Implementation-oriented reading map for CMIS 5.4.
- [[cmis-5-3-implementer-map]] - Implementation-oriented reading map for the generated wiki.
