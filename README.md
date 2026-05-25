# CMIS Wiki

This repository is an Obsidian vault for CMIS notes.

It is also structured so people can clone it and ask Codex questions against the local wiki files.

## Open Locally

After cloning, open this repository folder directly as an Obsidian vault.

Start with:

- `index.md`
- `overview.md`
- `synthesis/cmis-5-4-implementer-map.md`
- `synthesis/cmis-document-family-map.md`

## Scope

The vault is centered on OIF CMIS 5.4, with supporting notes for CMIS 5.3, OIF supplements, draft extensions, IEEE references, and vendor-specific source stubs.

Raw PDFs and DOCX source files are not included in this wiki-only repository. Source pages record source filenames and notes so readers can identify the upstream documents.

## Recommended Workflow

```sh
git pull
```

Then open or reload the vault in Obsidian.

When contributing, keep internal links in Obsidian wikilink format, for example:

```md
[[cmis-5-4]]
[[sources/oif-cmis-05-4]]
```

## Query With Codex

Clone the repository:

```sh
git clone <repo-url> cmis-wiki
cd cmis-wiki
```

Then run Codex from the repository root using your normal Codex setup. The root `AGENTS.md` tells Codex how to treat this folder as a local CMIS wiki.

Example prompts:

```text
Explain the major differences between CMIS 5.3 and 5.4 using this wiki.
```

```text
Summarize APSU for CMIS and point me to the relevant notes.
```

```text
What does Page 0Dh contain in CMIS 5.4?
```

Useful entry points for Codex:

- `index.md`
- `overview.md`
- `synthesis/cmis-5-4-implementer-map.md`
- `synthesis/cmis-document-family-map.md`
- `comparisons/cmis-5-3-to-5-4.md`

## What To Commit

Commit the wiki-only vault contents:

- Markdown notes: `*.md`
- Root guidance: `README.md`, `AGENTS.md`
- Repo hygiene: `.gitignore`
- Wiki directories: `concepts/`, `sources/`, `synthesis/`, `queries/`, `comparisons/`, `entities/`

Do not commit raw source artifacts unless you intentionally have redistribution rights:

- OIF/IEEE PDFs
- draft DOCX files
- extraction caches
- unlinked generated media
