---
type: source
title: OIF-CMIS-05.3
created: 2026-05-25
updated: 2026-05-25
tags: [cmis, oif, specification, source]
related: [overview, cmis-management-stack, management-memory-map, command-data-block, versatile-diagnostics-monitoring]
authors: [OIF Physical and Link Layer Working Group]
year: 2024
url: "https://www.oiforum.com/"
venue: OIF Implementation Agreement
source_filename: OIF-CMIS-05.3.pdf
source_note: Raw source file is not included in this wiki-only repository.
---

# OIF-CMIS-05.3

OIF-CMIS-05.3 is Revision 5.3 of the **Common Management Interface Specification**. It defines a generic management interface and host-module interaction protocol for CMIS-compliant managed modules, including pluggable and onboard optical/electrical modules.

## Scope

The base specification targets module suppliers, transceiver suppliers, system manufacturers, and system integrators. It is intended to let host and module software share a common management model across form factors and module capabilities.

The spec applies to modules managed over a CMIS-defined [management-communication-interface](../concepts/management-communication-interface.md), with basic operations exposed through a 256-byte addressable window and dynamic page/bank mapping for larger management spaces.

Source anchor: section 1.1, PDF pages 26-27.

## Module Classes

- [cmis-managed-module](../entities/cmis-managed-module.md) - generic managed target of the host management interface.
- Transmission modules - modules that provide data transmission service to a host system.
- Resource modules - modules that provide resources, such as external laser sources, without implementing a transmission path.
- Basic modules - data-agnostic system interface modules.
- Complex modules - data-format-aware modules, such as modules with lane deskewing or FEC functions.
- Client encapsulation modules - modules that map one or more host signals into independently operated network signals.

Source anchors: sections 1.1 and 4.1, PDF pages 26-48.

## Document Map

- Chapter 1 introduces purpose, scope, supplements, and document organization.
- Chapter 3 defines vocabulary and data types.
- Chapter 4 explains general concepts and the [cmis-management-stack](../concepts/cmis-management-stack.md).
- Chapter 5 defines the [management-interface](../concepts/management-interface.md) and [register-access-layer](../concepts/register-access-layer.md).
- Chapter 6 defines core management features such as [applications-and-data-paths](../concepts/applications-and-data-paths.md), [control-sets](../concepts/control-sets.md), [module-state-machine](../concepts/module-state-machine.md), and [data-path-state-machine](../concepts/data-path-state-machine.md).
- Chapter 7 defines advanced features, including [versatile-diagnostics-monitoring](../concepts/versatile-diagnostics-monitoring.md), [command-data-block](../concepts/command-data-block.md), [network-path-applications](../concepts/network-path-applications.md), and host lane switching.
- Chapter 8 defines the [management-memory-map](../concepts/management-memory-map.md).
- Chapter 9 is the CDB command catalog.
- Chapter 10 defines the [cmis-timing-model](../concepts/cmis-timing-model.md).
- Appendix B defines [management-communication-interface](../concepts/management-communication-interface.md) variants.

Source anchor: section 1.2, PDF page 28.

## Rev. 5.3 Highlights

Revision 5.3 states that existing CMIS 5.2-compliant hosts and modules are also CMIS 5.3-compliant. The release adds or clarifies support for CPO, ELSFP, resource modules, host-module link training supplements, SPIMCI, Normalized Application Descriptors, VDM power saving, FEC symbol error weight observables, host lane switching, additional CDB commands, and security-related CDB command groups.

Source anchor: revision history, PDF pages 8-10.

## Wiki Entry Points

- [cmis-5-3-implementer-map](../synthesis/cmis-5-3-implementer-map.md)
- [cmis-5-2-to-5-3](../comparisons/cmis-5-2-to-5-3.md)
- [cmis-management-stack](../concepts/cmis-management-stack.md)
- [management-memory-map](../concepts/management-memory-map.md)
- [applications-and-data-paths](../concepts/applications-and-data-paths.md)
- [command-data-block](../concepts/command-data-block.md)
- [versatile-diagnostics-monitoring](../concepts/versatile-diagnostics-monitoring.md)
