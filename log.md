# Research Log

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
