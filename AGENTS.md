# AGENTS.md

This repository is an Obsidian vault for CMIS wiki notes.

## How To Answer Questions

- Treat this folder as the vault root.
- Start from `index.md`, `overview.md`, `synthesis/cmis-5-4-implementer-map.md`, and `synthesis/cmis-document-family-map.md`.
- Prefer local wiki content over external search.
- Use `rg` first when searching notes.
- Cite local files and line numbers when useful.
- Keep CMIS 5.4 as the current base revision unless the user asks about a different revision.
- Keep source classification clear:
  - Base specs: `sources/oif-cmis-05-4.md`, `sources/oif-cmis-05-3.md`
  - Supplements: VCS, FF, C-CMIS
  - Standalone companion IA: ELSFP
  - Drafts: I3CMCI and 802.3dj APSU
  - External references: IEEE 802.3 and 802.3dj
  - Vendor-specific notes: Google GMIS/custom behavior
- Do not assume raw PDFs or DOCX files are present. Source pages record source filenames but the raw files are intentionally not part of this wiki-only repo.

## Editing Rules

- Preserve GitHub-navigable relative Markdown links such as `[cmis-5-4](concepts/cmis-5-4.md)` and `[oif-cmis-05-4](sources/oif-cmis-05-4.md)`.
- When editing notes in subdirectories, make internal link targets relative to the current file.
- Add frontmatter to new notes.
- Prefer concise concept pages with clear links to source pages.
- Do not promote draft or vendor-specific behavior into base CMIS notes without marking the status clearly.
