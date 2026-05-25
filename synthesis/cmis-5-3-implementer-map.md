---
type: synthesis
title: CMIS 5.3 Implementer Map
created: 2026-05-25
updated: 2026-05-25
tags: [cmis, implementation, synthesis]
related: [sources/oif-cmis-05-3, cmis-management-stack, management-memory-map, applications-and-data-paths, command-data-block]
sources: [oif-cmis-05-3]
---

# CMIS 5.3 Implementer Map

This page is the working entry point for implementing or reviewing CMIS 5.3 behavior.

For current CMIS work in this vault, use [[cmis-5-4-implementer-map]]. This page is retained for the original 5.3 wiki baseline.

## Mental Model

CMIS is a small register access core with a large advertised capability space around it. The host should first establish basic manageability, then discover the module, then enable only the features that the module advertises.

## Read First

1. [[sources/oif-cmis-05-3]] for the authoritative source and chapter map.
2. [[cmis-management-stack]] for the protocol layering.
3. [[management-memory-map]] for addressing, pages, banks, access types, flags, and masks.
4. [[module-state-machine]] for module power/manageability lifecycle.
5. [[applications-and-data-paths]] and [[control-sets]] for provisioning transmission functions.
6. [[data-path-state-machine]] for Data Path initialization and activation.

## Optional Feature Branches

- Use [[command-data-block]] when command/reply interaction is advertised.
- Use [[versatile-diagnostics-monitoring]] for extensible monitors and statistics.
- Use [[network-path-applications]] for client encapsulation and multiplexing modules.
- Use [[management-communication-interface]] details when implementing I2CMCI or SPIMCI transaction behavior.

## Implementation Heuristics

- Treat advertised features as the boundary of what the host may use.
- Treat custom extensions as optional and silent by default.
- Prefer stepwise configuration unless a module advertises intervention-free reconfiguration and the application needs it.
- Read timing requirements before deciding whether to poll, retry, or wait.
- For multi-byte values, rely on coherency only where the spec explicitly grants it.
- For flags, remember that summaries do not clear underlying flags; clear-on-read applies to the flag byte itself.

## Open Work

- Add a register-page atlas with one page per major CMIS page group.
- Add initialization flow pages based on Appendix D.
- Add CDB command pages for the commands most relevant to firmware update, PM, and security.
- Add VDM observable pages for BER, FERC, SEWmax, SNR, and LTP.
