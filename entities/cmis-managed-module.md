---
type: entity
title: CMIS Managed Module
created: 2026-05-25
updated: 2026-05-25
tags: [cmis, module, transceiver]
related: [cmis-host, management-memory-map, module-state-machine, applications-and-data-paths, network-path-applications, elsfp-cmis]
sources: [oif-cmis-05-4, oif-cmis-05-3]
---

# CMIS Managed Module

A CMIS managed module is the target managed by a [cmis-host](cmis-host.md). It exposes a standard management memory map and one or more management communication interfaces so the host can discover, configure, monitor, and operate the module.

## Main Types

- **Transmission module**: provides data transmission service between host lanes and media lanes.
- **Resource module**: provides resources, such as laser sources, but does not provide a transmission path.
- **Flat memory module**: exposes only a simpler fixed memory map.
- **Paged memory module**: supports dynamic page and bank mapping into upper memory.

## Functional Interfaces

- Host interface: high-speed electrical connection to the host.
- Media interface: electrical or optical connection to transmission media or a remote peer.
- Management interface: low-speed management communication and control/status signaling.

## Key Behaviors

CMIS modules advertise capabilities through the [management-memory-map](../concepts/management-memory-map.md), transition through the [module-state-machine](../concepts/module-state-machine.md), and expose optional advanced features such as [versatile-diagnostics-monitoring](../concepts/versatile-diagnostics-monitoring.md), [command-data-block](../concepts/command-data-block.md), and [network-path-applications](../concepts/network-path-applications.md).

[elsfp-cmis](../concepts/elsfp-cmis.md) is the main resource-module profile currently represented in this wiki.

Source anchors: CMIS 5.4 sections 1.1 and 4.1.
