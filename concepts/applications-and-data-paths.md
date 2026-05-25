---
type: concept
title: Applications and Data Paths
created: 2026-05-25
updated: 2026-05-25
tags: [cmis, applications, data-paths]
related: [cmis-managed-module, control-sets, data-path-state-machine, network-path-applications]
sources: [oif-cmis-05-4, oif-cmis-05-3]
---

# Applications and Data Paths

An **Application** is a supported transmission function that maps or processes signals between host lanes and media lanes. A **Data Path** is the concrete allocation of host lanes, media lanes, and internal resources used to instantiate an Application.

## Application Advertisement

Modules advertise supported Applications through Application Descriptors. Each basic descriptor includes host interface ID, media interface ID, lane counts, host lane assignment options, and media lane assignment options.

Basic advertisement covers up to 15 Applications. CMIS 5.3 added Normalized Application Descriptors. CMIS 5.4 expands NAD capacity further, allowing up to 255 NAD pages for larger application sets.

## Data Path Rules

- A Data Path uses consecutive host lanes and consecutive media lanes.
- Parallel Data Paths must be independent from the host viewpoint.
- Most Data Path attributes are duplicated per lane, but all lanes in the same Data Path report the same Data Path state.
- A host must select only non-conflicting Applications and lane assignments that the module advertised as supported.

## Related Mechanisms

Application selection and lane assignment are written into [[control-sets]]. The module realizes those settings through the [[data-path-state-machine]].

Source anchors: sections 6.2.1-6.2.2, PDF pages 56-61.
