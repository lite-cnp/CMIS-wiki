---
type: query
title: Security Related CDB Commands
tags: [cmis, cdb, security, authentication]
related: [../concepts/command-data-block.md, ../concepts/low-memory-register-map.md]
sources: [../sources/oif-cmis-05-4.md, ../sources/oif-cmis-05-3.md]
created: 2026-06-11
updated: 2026-06-11
---

# Security Related CDB Commands

CMIS security-related CDB commands are an optional advertised command group in the `0400h-04FFh` command ID range. In CMIS 5.4 this group is described as "Security Features"; in CMIS 5.3 the same command set appears as "Security Related Commands". The practical purpose is module authentication: the host retrieves the module's Initial Device ID certificate, sends a digest of a host-generated challenge, retrieves the module's signature, and verifies that signature with the public key from the certificate.

## Discovery

Before using these commands, the host should confirm ordinary CDB support and then issue `CMD 0044h` (`Security Features and Capabilities`). The reply advertises:

- Support bits for `0400h-04FFh`.
- Number of available certificate instances, up to four.
- Whether certificate chains are supported.
- Certificate format and per-certificate lengths.
- Digest length, signature generation time, signature length, signature format, and padding scheme.

The certificate instance index uses `0` for the leaf certificate. Higher instance indexes represent certificates used to sign lower-index certificates when a chain is supported.

## CMD 0044h Format Check

Per the common CDB convention, `0044h` is a no-payload request:

- `CMDID = 0044h`.
- `EPLLength = 0`.
- `LPLLength = 0`.
- `CdbChkCode` is computed over bytes `9Fh:128-132` only; for `00 44 00 00 00`, the check code is `BBh`.
- Host-written `RPLLength` and `RPLChkCode` placeholders at `9Fh:134-135` are not included in `CdbChkCode` and are ignored by the module while receiving the command.

The reply is LPL-only. The advertised fields run from `9Fh:136` through `9Fh:187`, inclusive, so the reply payload length is `52` bytes and `RPLChkCode` covers exactly those 52 bytes.

Two specification-definition pitfalls showed up in the local sources:

- CMIS 5.3 Table 9-12 lists `RPLLength = 50`, but the field range through `9Fh:187` requires `52`. CMIS 5.4 Table 9-14 uses `52`, which matches the common CDB reply convention.
- CMIS 5.4 Table 9-14 describes support bits for `0400h-04FFh` as a 32-byte bitmap at `9Fh:136-167`, but its printed byte-index formula appears to omit the `0400h` base offset. The usable interpretation is `offset = CMDID - 0400h`, `bit = offset mod 8`, and `byte = 136 + floor(offset / 8)`. For example, `0400h` is byte `136` bit `0`, `0405h` is byte `136` bit `5`, `0408h` is byte `137` bit `0`, and `04FFh` is byte `167` bit `7`.

## Authentication Commands

| Command | Name | Payload path | Role |
|---|---|---|---|
| `0400h` | Get IDevID Certificate in LPL | Segmented LPL reply | Reads one segment of the selected certificate. Host supplies `CertificateIndex` and `SegmentIndex`; reply returns `ReturnStatus`, matching segment index, and up to 117 bytes of certificate data. |
| `0401h` | Get IDevID Certificate in EPL | Complete EPL reply | Reads the selected certificate in one CDB interaction when EPL capacity is sufficient. Reply gives `ReturnStatus`, actual certificate length, and certificate bytes in pages `A0h-AFh`. |
| `0402h` | Set Digest To Sign in LPL | LPL command | Sends the digest of a host-generated random challenge for the module to sign. Reply returns a detailed status. |
| `0403h` | Set Digest To Sign in EPL | EPL command | Same as `0402h`, but the digest is carried in EPL. |
| `0404h` | Get Digest Signature in LPL | Segmented LPL reply | Reads one segment of the signature over the most recently supplied digest. Host supplies `SegmentIndex`; reply returns `ReturnStatus`, matching segment index, and up to 117 bytes of signature data. |
| `0405h` | Get Digest Signature in EPL | Complete EPL reply | Reads the full digest signature in EPL. Reply gives `ReturnStatus`, signature length, and signature bytes in pages `A0h-AFh`. |
| `0406h-04FFh` | Reserved | N/A | Reserved for future security-related commands. |

## Host Flow

1. Discover support with `0044h`.
2. Retrieve the leaf certificate, and any advertised chain certificates, with `0400h` or `0401h`.
3. Validate the certificate or chain against the host trust policy.
4. Generate a random challenge and hash it using the digest length indicated by `0044h`.
5. Send the digest with `0402h` or `0403h`.
6. Wait according to the advertised signature generation time.
7. Retrieve the signature with `0404h` or `0405h`.
8. Verify the signature using the public key from the certificate.

This authenticates possession of the private key corresponding to the module certificate. It does not by itself encrypt the CMIS management channel.

## Status And Error Handling

Security commands return detailed status codes in addition to normal CDB completion status. Standard security return statuses include success, communication error, unexpected error, user command data error, signature request without a prior digest, signature request while the module is not ready, invalid private key, invalid public key in certificate, security device not found or not operational, security-device read error, and security-device write error. Custom status codes are reserved in the `1000h-1FFFh` range.

## Password Commands Are Separate

CMIS also has CDB password commands, but they are not part of the `0400h-04FFh` Security Features command group:

- `0001h` (`Enter Password`) sends a four-byte host password in LPL.
- `0002h` (`Change Password`) sends a four-byte new password in LPL.

These commands are security-adjacent access-control commands. They should not be confused with the module-authentication flow above. The local low-memory note also records the CMIS rule that password protection is a standard mechanism for custom data or functionality; CMIS-specified features should not be password-protected unless explicitly permitted or advertised.

## Implementation Notes

- Treat the whole group as optional. Use advertisements, not command-ID assumptions.
- Choose LPL commands when segmentation is acceptable or EPL is not available.
- Choose EPL commands when the complete certificate or signature fits in available EPL pages.
- For segmented LPL reads, start at `SegmentIndex=0` and increment until the advertised certificate or signature length is fully collected.
- If an EPL retrieval reports length `0`, treat that as insufficient EPL capacity for the requested object.
- Repeated `Get Digest Signature` calls return the same signature until a new `Set Digest To Sign` command is issued.

Source anchors: [oif-cmis-05-4](../sources/oif-cmis-05-4.md), CMIS 5.4 PDF pages 325, 340, 385-392; [oif-cmis-05-3](../sources/oif-cmis-05-3.md), CMIS 5.3 PDF pages 300, 343-350.
