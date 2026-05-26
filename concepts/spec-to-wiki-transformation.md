---
type: concept
title: Spec-to-Wiki Transformation
created: 2026-05-21
updated: 2026-05-25
tags: [wiki-building, methodology, spec]
related: [overview, sources/oif-cmis-05-3, cmis-5-3-implementer-map]
sources: ["thinkwe-need-to-answer-the-user-they-said-yes-to-m-2026-05-21-073851.md"]
---

# Spec-to-Wiki Transformation

This concept describes a structured methodology for converting a technical specification document into an interlinked wiki knowledge base.

## Core Principle

Decompose the specification into source, entity, concept, query, comparison, and synthesis pages with stable frontmatter and GitHub-navigable relative Markdown links.

## Current Application

For OIF-CMIS-05.3, the transformation focuses on the actual OIF Common Management Interface Specification domain:

- [oif-cmis-05-3](../sources/oif-cmis-05-3.md) as the authoritative source page.
- [cmis-management-stack](cmis-management-stack.md) and [management-memory-map](management-memory-map.md) as architectural anchors.
- [applications-and-data-paths](applications-and-data-paths.md), [control-sets](control-sets.md), [module-state-machine](module-state-machine.md), and [data-path-state-machine](data-path-state-machine.md) as core feature pages.
- [command-data-block](command-data-block.md) and [versatile-diagnostics-monitoring](versatile-diagnostics-monitoring.md) as advanced feature pages.
- [cmis-5-3-implementer-map](../synthesis/cmis-5-3-implementer-map.md) as the main synthesis page.

## Caution

CMIS also names an unrelated OASIS content-management standard. This wiki is about OIF CMIS, not the OASIS content-management domain.
