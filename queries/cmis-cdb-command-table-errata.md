---
type: query
title: CMIS CDB Command Table Errata Candidates
tags: [cmis, cdb, errata, specification-review]
related: [../concepts/command-data-block.md, security-related-cdb-commands.md]
sources: [../sources/oif-cmis-05-4.md, ../sources/oif-cmis-05-3.md]
created: 2026-06-11
updated: 2026-06-11
---

# CMIS CDB Command Table Errata Candidates

This note records likely request/reply format mistakes found by checking CMIS 5.3 and CMIS 5.4 CDB command tables against the common CDB convention:

- `CdbChkCode` covers `9Fh:128-132` plus command LPL bytes, excluding `9Fh:133-135`.
- `RPLLength` values `0-120` count reply LPL bytes from `9Fh:136`.
- `RPLChkCode` covers the returned reply body, not the command header.
- Unused command/reply ranges should start after the last defined byte.

## High-Confidence Format Issues

| Revision | Command | Issue | Expected interpretation |
|---|---|---|---|
| 5.4 | `0005h` Get Module Time | `CdbChkCode` is printed as `FBh`, but the no-payload checksum for `00 05 00 00 00` is `FAh`. | Use `FAh`. |
| 5.4 | `0006h` Set Module Time | Command data defines `9Fh:136-143` `TimeSpec` and `9Fh:144` `IsIncrement`, then also marks `9Fh:136-255` as no data passed. | The unused command-data range should start at `9Fh:145`. |
| 5.3 | `0045h` Externally Defined Features | Table 9-13 is for `0045h`, but the `CMDID` row says `CMD ID 0043h`. | Use `CMDID = 0045h`; for a no-payload request, the check code is `BAh`. |
| 5.3 | `0044h` Security Features and Capabilities | `RPLLength` is printed as `50`, but reply fields run through `9Fh:187`, which is 52 bytes from `9Fh:136`. | Use `RPLLength = 52`. CMIS 5.4 fixes this. |
| 5.4 | `0042h`, `0043h`, `0044h` query bitmaps | The command-support bitmap formulas print a group-offset condition such as `0 <= i - 512 <= 255`, but then use `byte = 136 + floor(i/8)`. That omits the group base offset. | For `0042h`, use `offset = CMDID - 0200h`; for `0043h`, `offset = CMDID - 0300h`; for `0044h`, `offset = CMDID - 0400h`; then `byte = 136 + floor(offset/8)` and `bit = offset mod 8`. |
| 5.3 | `0051h` Get Interface Code Description | Reply data overlaps `9Fh:139` as both reserved and the first byte of `InterfaceName`; byte `203` is skipped. | Treat `9Fh:139-154` as `InterfaceName` and `9Fh:203` as the alignment reserved byte. CMIS 5.4 fixes this placement. |
| 5.4 | `0051h` Get Interface Code Description | Table keeps `RPLLength = 92` but reply data now extends through `9Fh:231` after adding `BitsPerSymbolExact` and `GridSpacingMin`. | Use `RPLLength = 96` for `9Fh:136-231`. |
| 5.3, 5.4 | `0100h` Get Firmware Info | Reply header rows point to the command-header table: 5.3 says `Table 8-178`; 5.4 says `Table 8-198`. | These should point to the reply-header table: `Table 8-179` in 5.3 and `Table 8-199` in 5.4. |
| 5.3, 5.4 | `0100h` Get Firmware Info | The information bit for Factory/Boot or Fixed Load points to `9Fh:201-245`, but the actual fields are `9Fh:210-245`. `9Fh:201-209` belongs to the B image/load extra string. | Use `9Fh:210-245` for Factory/Boot or Fixed Load information. |
| 5.4 | `010Bh` Check Firmware Activation Options | Reply header says `RPLLength = 0` and `RPLChkCode = 0`, but reply data defines `9Fh:136` `TrafficImpact` and `9Fh:137` `ConfigImpact`. | Use `RPLLength = 2` and computed `RPLChkCode`. |
| 5.4 | `010Ch` Store Firmware Load Tag | `LPLLength` value is blank while command data defines `Bank`, `Control`, and `LoadTag` through `9Fh:201`. | As drawn, full tag storage requires `LPLLength = 66`; if a shorter clear-only form is intended, the table needs to state that explicitly. |
| 5.4 | `010Dh` Retrieve Firmware Load Tag | `LPLLength` value is blank even though command data defines `9Fh:136` `Bank`. Reply header says `RPLLength = 0` and `RPLChkCode = 0`, but reply data returns `9Fh:136-201`. | Use request `LPLLength = 1`; reply should use `RPLLength = 66` and computed `RPLChkCode`. |
| 5.3, 5.4 | `0290h` Temperature Histogram | Command data defines `9Fh:136` `SubCommands`, then also marks `9Fh:136-255` as no data passed. | The unused command-data range should start at `9Fh:137`. The reply `RPLLength = 52` is consistent with `9Fh:136-187`. |

## Lower-Severity Editorial Issues

- `0216/0217h` is printed without the `h` suffix on `0216` in both revisions' table titles. This is cosmetic; the command rows still identify `0216h` and `0217h`.
- `0109h` Run Firmware Image/Load has blank reply length/check rows in places where no reply body is returned, or where the command may reset/switch before a success reply is read. Treat this as underspecified editorial wording rather than a clear payload-length conflict.
- Several variable-length security and firmware commands correctly leave `RPLLength` or `LPLLength` computed or command-dependent; those were not counted as errors unless the byte map contradicted a concrete numeric value.

## Scope

This was a table-consistency audit, not a formal OIF errata check. It focused on Chapter 9 CDB command definitions in the local CMIS 5.3 and 5.4 PDFs and checked command IDs, check-code constants, LPL/RPL byte counts, reply-header references, and obvious overlapping byte ranges.

Source anchors: [oif-cmis-05-3](../sources/oif-cmis-05-3.md), CDB chapter PDF pages 302, 305, 309-310, 339-340; [oif-cmis-05-4](../sources/oif-cmis-05-4.md), CDB chapter PDF pages 332-333, 338-340, 345, 349-350, 361-363, 383-384.
