# Research Log

## 2026-06-09 synthesis | APSU/iLT verification report

- Added [apsu-ilt-verification-report](synthesis/apsu-ilt-verification-report.md), reporting current APSU/iLT implementation status, lab verification evidence, and gaps for the 1.6T 2xDR4 FRO module.
- Captured status labels across current vendor CDB support, planned CMIS Page 70h alignment, Sian3 lab evidence, implementation gaps, and verification evidence gaps.

## 2026-06-09 ingest | Feng Sian3 link-training screencopies

- Updated [feng-jiang-2026-sian3-link-training-verification-email-thread](sources/feng-jiang-2026-sian3-link-training-verification-email-thread.md) with analysis of `raw/sources/screencopies/`.
- Reclassified polarity evidence from email-only to email plus screencopy-backed evidence: polarity forcing broke traffic, LT was enabled on DUT/BERT lanes, and polarity readback masks changed.
- Kept high-loss proof, convergence-time measurement, May 26 temperature-shift raw log/screenshot, third repeatability raw log, Page 70h validation, and interoperability closure as remaining gaps.

## 2026-06-09 ingest | Feng Sian3 link-training raw attachments

- Updated [feng-jiang-2026-sian3-link-training-verification-email-thread](sources/feng-jiang-2026-sian3-link-training-verification-email-thread.md) with analysis of `raw/sources/link_training.7z`, `raw/sources/link_training_temperation.7z`, `raw/sources/logs_20260522104400.txt`, and `raw/sources/test-setup-apsu-ilt.png`.
- Captured numeric BER, LT status, repeated tap readback, and 0/45/70 C temperature-corner evidence from the loaded logs.
- Reclassified remaining gaps: quantified physical high-loss setting, convergence-time measurement, May 26 temperature-shift raw log/screenshot, polarity-recovery raw log/screenshot, third repeatability raw log, endpoint labeling for duplicate tap records, Page 70h validation, and interoperability closure.

## 2026-06-09 ingest | Current APSU/iLT customer-note plan

- Added [lumentum-2026-8023dj-apsu-ilt-support-plan](sources/lumentum-2026-8023dj-apsu-ilt-support-plan.md), summarizing the current APSU/iLT implementation status from `raw/sources/8023dj_apsu_ilt_cmis_slides.pptx` and the matching PDF customer-note export.
- Added [lumentum-2026-dpsm-apsu-ilt-state-machine](sources/lumentum-2026-dpsm-apsu-ilt-state-machine.md), extracting the embedded draw.io state-machine model from `raw/sources/dpsm-apsu-ilt-state-machine.drawio.png`.
- Added [apsu-ilt-customer-note-plan](synthesis/apsu-ilt-customer-note-plan.md), capturing the customer-note position: vendor CDB implemented today, CMIS Page 70h planned after validation closure, and `DPActivated` is not sufficient for live Ethernet DATA readiness.
- Updated APSU, vendor-specific customization, state-machine query, Sian3 cAPI query, document-family map, and `wiki/index.md` navigation for the current implementation plan.

## 2026-06-09 ingest | Obsolete Sian3 ILT procedure attachment

- Added [broadcom-2025-sian3-ilt-procedure](sources/broadcom-2025-sian3-ilt-procedure.md), summarizing `raw/sources/Sian3_ILT_AN.pdf` as an obsolete Broadcom Sian3 ILT BERT/DUT procedure source.
- Marked the 2025 ILT procedure as superseded by [broadcom-2026-sian3-apsu-application-notes](sources/broadcom-2026-sian3-apsu-application-notes.md), which has later firmware scope and current APSU terminology.
- Updated [feng-jiang-2026-sian3-link-training-verification-email-thread](sources/feng-jiang-2026-sian3-link-training-verification-email-thread.md), [how-should-hosts-use-sian3-apsu-capi](queries/how-should-hosts-use-sian3-apsu-capi.md), [autonomous-path-startup](concepts/autonomous-path-startup.md), [vendor-specific-cmis-customizations](concepts/vendor-specific-cmis-customizations.md), [cmis-document-family-map](synthesis/cmis-document-family-map.md), and `wiki/index.md` to classify the attachment correctly.

## 2026-06-09 ingest | Feng Jiang Sian3 link-training verification email thread

- Added [feng-jiang-2026-sian3-link-training-verification-email-thread](sources/feng-jiang-2026-sian3-link-training-verification-email-thread.md), summarizing the Outlook thread `Sian3 DSP Link Training Verification` with body-level evidence for BERT/DUT setup, polarity recovery, SI/tap optimization, repeatability, and temperature behavior.
- Updated [how-should-hosts-use-sian3-apsu-capi](queries/how-should-hosts-use-sian3-apsu-capi.md), [broadcom-2026-sian3-apsu-application-notes](sources/broadcom-2026-sian3-apsu-application-notes.md), [autonomous-path-startup](concepts/autonomous-path-startup.md), and `wiki/index.md` to link the email-derived verification evidence.
- Noted that Outlook exposed attachment presence and inline screenshot references, but the available connector tools did not expose attachment file contents.

## 2026-06-09 ingest | Broadcom Sian3 APSU application note

- Added [broadcom-2026-sian3-apsu-application-notes](sources/broadcom-2026-sian3-apsu-application-notes.md), a vendor-specific source page for `raw/sources/Sian3 APSU Application Notes_Customer_Release.pdf`.
- Added [how-should-hosts-use-sian3-apsu-capi](queries/how-should-hosts-use-sian3-apsu-capi.md), a host bring-up analysis for Sian3 APSU cAPI readiness and diagnostics.
- Updated [autonomous-path-startup](concepts/autonomous-path-startup.md), [how-do-apsu-and-cmis-state-machines-interact](queries/how-do-apsu-and-cmis-state-machines-interact.md), [vendor-specific-cmis-customizations](concepts/vendor-specific-cmis-customizations.md), [cmis-document-family-map](synthesis/cmis-document-family-map.md), and `wiki/index.md` so the Broadcom source is classified as vendor-specific implementation material.

## 2026-05-26 query | CMIS-VCS register-map pages

- Added [upper-page-18h-register-map](concepts/upper-page-18h-register-map.md), a CMIS-VCS staged Control Set overflow page with an embedded C register-view struct.
- Added [upper-page-19h-register-map](concepts/upper-page-19h-register-map.md), a CMIS-VCS active Control Set overflow page with an embedded C register-view struct.
- Updated CMIS-VCS, Control Set, CDB, supplement, memory-map, source, and index navigation so the VCS overflow pages are GitHub-navigable.

## 2026-05-26 query | CMIS upper-page embedded C views

- Replaced header-only C Register View snippets on the CMIS 5.4 upper-page register-map pages with self-contained embedded C views so the structs, bitfields, enums, and static assertions are visible directly in Obsidian.
- Applied the inline C view pattern to Pages 00h, 01h, 02h, 04h, 10h, 11h, 12h, 13h, 14h, and 2Fh; Page 0Dh was already generated in that format.

## 2026-05-26 query | CMIS Page 0Dh register map

- Added [upper-page-0dh-register-map](concepts/upper-page-0dh-register-map.md), a CMIS 5.4 firmware-management page covering Page 0Dh capabilities, load status, and firmware load version descriptors.
- Extended [cmis-5-4-upper-page-registers.h](code/cmis-5-4-upper-page-registers.h) with Page 0Dh bitfield/register views, firmware load descriptor structs, and common firmware status code enums.
- Embedded the Page 0Dh C register view directly in the Markdown page so the struct and bitfields are visible in Obsidian.
- Updated [management-memory-map](concepts/management-memory-map.md) and `wiki/index.md` to link Page 0Dh directly.

## 2026-05-26 query | CMIS upper-page C bitfields

- Added [cmis-5-4-upper-page-registers.h](code/cmis-5-4-upper-page-registers.h), a detailed little-endian ARM-oriented C header with named bitfields, enums, byte-order wrappers, and static offset/size assertions for Pages 00h, 01h, 02h, 04h, 10h, 11h, 12h, 13h, 14h, and 2Fh.
- Updated the upper-page register-map pages with detailed bitfield/register definitions instead of only abstract byte-array overlays.

## 2026-05-26 query | GitHub-navigable wiki links

- Converted internal wiki cross-references from Obsidian wikilinks to GitHub-navigable relative Markdown links.
- Updated contributor guidance in `AGENTS.md` and `README.md` to keep future internal links GitHub-compatible.

## 2026-05-26 query | CMIS 5.4 upper-page register maps

- Added upper-memory register-map pages for [upper-page-00h-register-map](concepts/upper-page-00h-register-map.md), [upper-page-01h-register-map](concepts/upper-page-01h-register-map.md), [upper-page-02h-register-map](concepts/upper-page-02h-register-map.md), [upper-page-04h-register-map](concepts/upper-page-04h-register-map.md), [upper-page-10h-register-map](concepts/upper-page-10h-register-map.md), [upper-page-11h-register-map](concepts/upper-page-11h-register-map.md), [upper-page-12h-register-map](concepts/upper-page-12h-register-map.md), [upper-page-13h-register-map](concepts/upper-page-13h-register-map.md), [upper-page-14h-register-map](concepts/upper-page-14h-register-map.md), and [upper-page-2fh-register-map](concepts/upper-page-2fh-register-map.md).
- Embedded page-local C register-view structs for the requested pages, using explicit byte arrays or CMIS big-endian wrappers so the layouts are safe on little-endian ARM targets.
- Updated [management-memory-map](concepts/management-memory-map.md) and `wiki/index.md` with links to the new upper-page maps.

## 2026-05-26 query | CMIS 5.4 lower memory register map

- Added [low-memory-register-map](concepts/low-memory-register-map.md) with a detailed CMIS 5.4 Lower Memory overview, implementation notes, and an embedded packed C register-view struct modeled after generated CMIS C headers.
- Updated `wiki/index.md` and [management-memory-map](concepts/management-memory-map.md) to include the new lower-memory concept page.
- Refined the embedded C struct member names to use CMIS-style CamelCase identifiers.
- Corrected the embedded C struct for little-endian ARM use by replacing native multi-byte monitor/password fields with explicit CMIS big-endian byte wrappers and offset assertions.

## 2026-05-25 ingest | CMIS 5.4 and document family update

- Added [oif-cmis-05-4](sources/oif-cmis-05-4.md) as the current base CMIS source page.
- Added OIF supplement source pages for [oif-cmis-vcs-01-1](sources/oif-cmis-vcs-01-1.md), [oif-cmis-ff-01-0](sources/oif-cmis-ff-01-0.md), and [oif-c-cmis-01-4](sources/oif-c-cmis-01-4.md).
- Added [oif-elsfp-cmis-01-0](sources/oif-elsfp-cmis-01-0.md) and modeled [elsfp-cmis](concepts/elsfp-cmis.md) as a standalone companion IA for ELSFP resource modules.
- Added draft source pages for [oif2026-057-01-i3cmci-draft](sources/oif2026-057-01-i3cmci-draft.md) and [oif2026-093-08-802-3dj-apsu-draft](sources/oif2026-093-08-802-3dj-apsu-draft.md).
- Added IEEE reference stubs for [ieee-802-3-2022](sources/ieee-802-3-2022.md) and [ieee-p802-3dj-d2-3](sources/ieee-p802-3dj-d2-3.md).
- Added a vendor-specific source stub for [google-gmis-imdd-transceiver-customizations](sources/google-gmis-imdd-transceiver-customizations.md) with extraction caveats.
- Updated navigation, supplement, memory-map, MCI, control-set, DPSM, NPSM, and implementer-map pages for the new source set.

## 2026-05-25 ingest | OIF-CMIS-05.3

- Generated first substantive wiki pass from `raw/sources/OIF-CMIS-05.3.pdf`.
- Added source, entity, concept, comparison, synthesis, and query pages for the actual OIF Common Management Interface Specification domain.
- Corrected earlier starter content that conflated OIF CMIS with unrelated OASIS content-management CMIS.
- Updated `wiki/index.md` and `wiki/overview.md` as navigation entry points.

## 2026-05-21

- Project created.
- Saved query page `thinkwe-need-to-answer-the-user-they-said-yes-to-m-2026-05-21-073851.md`.

## 2026-05-21 ingest | Legacy starter guide

- Imported the initial spec-to-wiki transformation guide.
