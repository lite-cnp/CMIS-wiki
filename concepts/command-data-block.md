---
type: concept
title: Command Data Block
created: 2026-05-25
updated: 2026-05-26
tags: [cmis, cdb, messaging]
related: [register-access-layer, management-memory-map, upper-page-0dh-register-map, cmis-versatile-control-set, upper-page-18h-register-map, upper-page-19h-register-map, versatile-diagnostics-monitoring, cmis-timing-model, coherent-cmis]
sources: [oif-cmis-05-4, oif-cmis-05-3, oif-c-cmis-01-4, oif-cmis-vcs-01-1]
---

# Command Data Block

Command Data Block (CDB) is an optional command/reply messaging mechanism layered on top of the basic register interface.

## Purpose

CDB lets the host invoke module functions that do not fit naturally into simple READ and WRITE register interactions. Conceptually, the host sends a command and later receives a reply.

## Message Areas

- Page 9Fh contains the CDB command/reply header and a 120-byte Local Payload (LPL) area.
- Pages A0h-AFh provide Extended Payload (EPL) space up to 2048 bytes.
- Each CDB instance is distinguished by bank address.

## Completion

The module reports CDB status in CdbStatus registers and signals completion through CdbCmdCompleteFlag bits. A host may poll or use interrupt-driven completion.

## Processing Modes

- **Foreground mode**: module rejects register access while processing the command.
- **Background mode**: register access can continue while the command executes.

## Command Groups

CMIS defines CDB groups for module commands, capabilities inquiry, firmware management, performance monitoring, data recording, diagnostics/debug, security features, OIF-restricted supplements, and custom commands.

CMIS-VCS uses CDB discovery before its overflow pages are meaningful: CMD `0045h` advertises VCS support, CMD `4000h` returns the VCS overview, CMD `4001h` returns read-write VCS descriptors, and CMD `4002h` returns read-only VCS descriptors when supported. Those descriptor streams define how VCS parameters map into [Page 18h](upper-page-18h-register-map.md) and [Page 19h](upper-page-19h-register-map.md).

## CMIS 5.4 Notes

CMIS 5.4 adds Get/Set Module Time commands, an EPL variant of Get Application Attributes, firmware management additions, and new interface attributes. [upper-page-0dh-register-map](upper-page-0dh-register-map.md) provides a register-readable summary of firmware load capabilities/status, while CDB firmware commands remain the operational path for firmware query, transfer, run, commit, and tag retrieval flows. CMIS 5.4 also reserves command ID space for supplements such as [coherent-cmis](coherent-cmis.md) and [cmis-versatile-control-set](cmis-versatile-control-set.md).

Source anchors: CMIS 5.4 revision history, section 7.2, sections 8.23-8.24, and chapter 9.
