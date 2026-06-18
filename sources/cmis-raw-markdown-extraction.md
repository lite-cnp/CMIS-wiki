---
type: source
title: CMIS Raw Markdown Extraction
created: 2026-06-18
updated: 2026-06-18
tags: [cmis, source, extraction, markitdown]
related: [../synthesis/cmis-document-family-map.md, ../sources/oif-cmis-05-4.md, ../concepts/i3c-based-management-communication-interface.md, ../concepts/autonomous-path-startup.md, ../sources/broadcom-2025-mpi-metrics-feature.md]
authors: [local]
year: 2026
venue: Generated extraction cache
source_filename: raw/sources/markdown/conversion-results.json
status: draft
---

# CMIS Raw Markdown Extraction

This page records the MarkItDown conversion pass over CMIS raw document materials. The generated Markdown files are a searchable extraction cache, not replacement source material. Original PDFs, DOCX, and PPTX files remain authoritative for tables, figures, pagination, access rules, and normative wording.

## Conversion Summary

| Field | Value |
|---|---|
| Tool | `python -m markitdown` |
| Manifest updated | `2026-06-18T12:44:48+08:00` |
| Source root | `CMIS/raw/sources` |
| Output root | `CMIS/raw/sources/markdown` |
| Manifest | `CMIS/raw/sources/markdown/conversion-results.json` |
| Candidate types | `.pdf`, `.docx`, `.doc`, `.pptx`, `.ppt` |
| Candidates | 23 |
| Converted | 23 |
| Skipped empty | 0 |
| Failed | 0 |

## Conversion Coverage

| Cluster | Converted Markdown | Wiki entry points |
|---|---|---|
| CMIS base and OIF family | `OIF-CMIS-05.4.md`, `OIF-CMIS-05.3.md`, `OIF-CMIS-VCS-01.1.md`, `OIF-CMIS-FF-01.0.md`, `OIF-C-CMIS-01.4_IA.md`, `OIF-ELSFP-CMIS-01.0.md` | [cmis-document-family-map](../synthesis/cmis-document-family-map.md), [oif-cmis-05-4](oif-cmis-05-4.md) |
| IEEE Ethernet / APSU references | `8023-2022.md`, `8023dj_D2p3.md`, `oif2026.093.08.md` | [ieee-802-3-2022](ieee-802-3-2022.md), [ieee-p802-3dj-d2-3](ieee-p802-3dj-d2-3.md), [oif2026-093-08-802-3dj-apsu-draft](oif2026-093-08-802-3dj-apsu-draft.md) |
| I3CMCI and MIPI I3C | `oif2026.057.01.md`, `I3CMCI__I3C_MIPI-v1.1.1.md`, `I3CMCI__MIPI-Alliance-I3C-v1-2-Hot-Join-App-Note-public-edition.md`, `I3CMCI__MIPI-I3C-App-Note-Virtual-Devices-Targets-public-edition.md`, `I3CMCI__MIPI-I3C-Basic-FAQ-v1-1-1-public.md`, `I3CMCI__MIPI-I3C-and-I3C-Basic-Version-History-Table-030625.md`, `I3CMCI__MIPI-I3C-v1-1-Current-DCR-Table.md`, `I3CMCI__MIPI-Webinar-Whats-New-with-I3C-15-Sep-2021.md` | [oif2026-057-01-i3cmci-draft](oif2026-057-01-i3cmci-draft.md), [i3c-based-management-communication-interface](../concepts/i3c-based-management-communication-interface.md), [mipi-i3c-basic-v1-1-1](mipi-i3c-basic-v1-1-1.md) |
| APSU, ILT, and vendor implementation notes | `8023dj_apsu_ilt_cmis.md`, `8023dj_apsu_ilt_cmis_slides.md`, `Sian3 APSU Application Notes_Customer_Release.md`, `Sian3_ILT_AN.md`, `Google CMIS5.0+ (GMIS) IMDD Tra...izations (Rev 2.1 ).md`, `87XXX-85XXX-83XXX-AN100.md` | [autonomous-path-startup](../concepts/autonomous-path-startup.md), [broadcom-2026-sian3-apsu-application-notes](broadcom-2026-sian3-apsu-application-notes.md), [google-gmis-imdd-transceiver-customizations](google-gmis-imdd-transceiver-customizations.md), [broadcom-2025-mpi-metrics-feature](broadcom-2025-mpi-metrics-feature.md) |

## Exceptions

| Source | Status | Handling |
|---|---|---|
| `I3CMCI/MIPI-I3C-v1-1-Current-DCR-Table.pdf` | Converted with weak yield | The generated Markdown is only 204 bytes. Use [mipi-i3c-v1-1-current-dcr-table](mipi-i3c-v1-1-current-dcr-table.md) and the original PDF for DCR details. |

## Protected Source Recovery

The Broadcom AN100 PDF was recovered after the user supplied the document password. The workflow decrypted the PDF only to a temporary `%TEMP%` file, ran MarkItDown on that temporary copy, and removed the temporary file afterward. The password is not stored in the wiki or manifest.

- `87XXX-85XXX-83XXX-AN100.pdf` -> `CMIS/raw/sources/markdown/87XXX-85XXX-83XXX-AN100.md`
- The zero-byte duplicate raw upload `87XXX-85XXX-83XXX-AN100_.pdf` was deleted from `CMIS/raw/sources/`.

## DOCX Recovery

The first DOCX conversion attempt failed because the local MarkItDown installation lacked the optional DOCX dependency. Installing `markitdown[docx]` recovered both draft DOCX files:

- `oif2026.057.01.docx` -> `CMIS/raw/sources/markdown/oif2026.057.01.md`
- `oif2026.093.08.docx` -> `CMIS/raw/sources/markdown/oif2026.093.08.md`

## Usage Rule

Use the generated Markdown cache for full-text search, cross-document triage, and quick source anchoring. Use the original raw documents and existing source pages for final interpretation, especially for register tables, state-machine figures, password-protected vendor notes, and draft requirement wording.
