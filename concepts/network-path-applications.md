---
type: concept
title: Network Path Applications
created: 2026-05-25
updated: 2026-05-25
tags: [cmis, network-path, multiplexing, client-encapsulation]
related: [applications-and-data-paths, data-path-state-machine, management-memory-map, autonomous-path-startup]
sources: [oif-cmis-05-4, oif-cmis-05-3, oif2026-093-08-802-3dj-apsu-draft]
---

# Network Path Applications

Network Path Applications are CMIS client encapsulation applications. They map one or more host-side signals into an independently maintained media-side network signal.

## Key Concepts

- **Host Path (HP)**: host-side segment for one host signal or tributary.
- **Network Path (NP)**: media-side segment carrying the network signal.
- **NP Application**: an Application with an independently controlled Network Path.
- **DP Application**: a system-interface Application without client encapsulation.

## Why They Exist

System interface Data Paths assume tighter coupling between host and media side operation. Client encapsulation applications require looser coupling so the media-side network signal can stay operational while host tributaries are added, removed, or replaced.

## State Machines

An N:1 multiplex NP Application uses N host-side DPSM instances plus one Network Path State Machine (NPSM), rather than one DPSM for the whole Application.

## Restrictions

CMIS 5.3 requires all host lanes encapsulated into a network signal to use the same per-lane data rate, simplifying advertisement and compatibility rules. CMIS 5.4 integrates Network Path errata and should be used as the current base reference for NPSM behavior.

## APSU Draft Interaction

The [autonomous-path-startup](autonomous-path-startup.md) draft says the DPSM/APSU relationship applies similarly to NPSM states. For Network Path Applications, the host should treat NPSM as configuration state and read APSU status separately when the application requires IEEE 802.3dj APSU.

Source anchors: CMIS 5.4 section 7.6; OIF 2026.093.08 NPSM draft section.
