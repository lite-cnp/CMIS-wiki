---
type: query
title: What Is CDB Command 0045h For
tags: [cmis, cdb, supplements, vcs]
related: [../concepts/command-data-block.md, ../concepts/cmis-versatile-control-set.md, cmis-cdb-command-table-errata.md]
sources: [../sources/oif-cmis-05-4.md, ../sources/oif-cmis-05-3.md, ../sources/oif-cmis-vcs-01-1.md]
created: 2026-06-11
updated: 2026-06-11
---

# What Is CDB Command 0045h For

`CMD 0045h` is the base-CMIS discovery command for externally defined or supplement-defined CDB command sets.

In CMIS 5.3 it is titled `Externally Defined Features`. In CMIS 5.4 it is renamed more directly as `Query Supplement Support`. Its current practical role in this wiki is to let a host discover whether the module supports the CMIS-VCS supplement command set before the host issues VCS commands such as `4000h`, `4001h`, or `4002h`.

## Request

`0045h` is a no-payload CDB request:

- `CMDID = 0045h`
- `EPLLength = 0`
- `LPLLength = 0`
- `CdbChkCode = BAh` for the bytes `00 45 00 00 00`

CMIS 5.3 Table 9-13 contains an apparent typo: the table is for `0045h`, but its `CMDID` row says `CMD ID 0043h`. Treat that as `0045h`; CMIS 5.4 fixes the row.

## Reply

The reply is one LPL byte:

- `RPLLength = 1`
- `9Fh:136 SupplementSupport`
- Bit `0`: `0` means CMIS-VCS commands are not supported; `1` means CMIS-VCS commands are supported.

The reply check byte is computed over that one reply byte.

## Host Use

Use `0045h` after establishing CDB support and before relying on supplement command spaces. For CMIS-VCS, the host flow is:

1. Issue `0045h`.
2. If `SupplementSupport[0] = 1`, issue VCS discovery commands.
3. Use `4000h` for VCS overview.
4. Use `4001h` for read-write VCS descriptors.
5. Use `4002h` for read-only VCS descriptors when advertised.

If `0045h` is not supported, or if the VCS support bit is `0`, a host should not assume that Pages 18h/19h VCS parameter meanings are valid. Fall back to base CMIS controls.

Source anchors: [command-data-block](../concepts/command-data-block.md), [cmis-versatile-control-set](../concepts/cmis-versatile-control-set.md), [cmis-cdb-command-table-errata](cmis-cdb-command-table-errata.md), [oif-cmis-05-4](../sources/oif-cmis-05-4.md), [oif-cmis-vcs-01-1](../sources/oif-cmis-vcs-01-1.md).
