---
type: concept
title: CMIS 5.4
created: 2026-05-25
updated: 2026-05-25
tags: [cmis, revision, cmis-5-4]
related: [sources/oif-cmis-05-4, cmis-5-3-to-5-4, cmis-supplements, management-memory-map]
sources: [oif-cmis-05-4]
---

# CMIS 5.4

CMIS 5.4 is the current base revision represented in this vault. It preserves compatibility with CMIS 5.3 while integrating maintenance fixes, scaling improvements, and additional advertised feature mechanisms.

## What Changed Strategically

- CMIS remains a host-module management interface based on [register-access-layer](register-access-layer.md) operations and the [management-memory-map](management-memory-map.md).
- The revision tightens Network Path handling and integrates CMIS 5.x errata.
- It expands the system for advertising supported pages, named features, and option profiles.
- It increases scale for applications and lanes.
- It adds several new page groups for firmware, lane management, monitoring, thresholds, and media lane switching.
- It documents future directions for I3C-compatible MCI and IEEE 802.3dj link training support.

## Compatibility Posture

CMIS 5.4 is designed as an incremental revision. A CMIS 5.3 host should not assume new 5.4-only capabilities unless the module advertises them, and a CMIS 5.4 host should continue to respect older advertised capability boundaries.

## Reading Path

1. [oif-cmis-05-4](../sources/oif-cmis-05-4.md)
2. [cmis-5-3-to-5-4](../comparisons/cmis-5-3-to-5-4.md)
3. [cmis-5-4-implementer-map](../synthesis/cmis-5-4-implementer-map.md)
4. [cmis-document-family-map](../synthesis/cmis-document-family-map.md)
