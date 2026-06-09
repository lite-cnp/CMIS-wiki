---
type: concept
title: Control Sets
created: 2026-05-25
updated: 2026-05-26
tags: [cmis, configuration, control-sets]
related: [applications-and-data-paths, data-path-state-machine, management-memory-map, cmis-versatile-control-set, upper-page-18h-register-map, upper-page-19h-register-map]
sources: [oif-cmis-05-4, oif-cmis-05-3, oif-cmis-vcs-01-1]
---

# Control Sets

Control Sets are groups of per-lane configuration registers that define Data Path behavior. They are the main staging and commitment mechanism for Application and signal-integrity configuration.

## Types

- **Active Control Set**: read-only report of the configuration currently provisioned for module hardware.
- **Staged Control Set**: host-writeable configuration area for proposed future settings.

## Configuration Flow

1. **Definition**: the host writes desired settings into a Staged Control Set.
2. **Provisioning**: the module validates and copies staged settings into the Active Control Set.
3. **Commissioning**: the module commits the Active Control Set to hardware.

## Apply Triggers

- **ApplyDPInit**: supports stepwise provisioning and, when supported, regular intervention-free reconfiguration through DPSM state cycling.
- **ApplyImmediate**: supports faster hot reconfiguration without changing the DPSM state, when supported and allowed.

## Host Rule

Apply operations are Data Path operations. A host normally triggers all lanes of a Data Path together, even if only one lane-specific field changed.

## Versatile Control Sets

[cmis-versatile-control-set](cmis-versatile-control-set.md) extends the Control Set idea for module-specific signal-integrity parameters. A VCS-aware host discovers the parameter list and locations from CDB VCS descriptors, then maps those parameters into base Control Set SI space and, when required, overflow Page [18h](upper-page-18h-register-map.md) for staged values and Page [19h](upper-page-19h-register-map.md) for active values.

Source anchors: CMIS 5.4 sections 6.2.3-6.2.4; OIF-CMIS-VCS-01.1 abstract.
