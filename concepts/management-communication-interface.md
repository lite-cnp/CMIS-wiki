---
type: concept
title: Management Communication Interface
created: 2026-05-25
updated: 2026-05-25
tags: [cmis, mci, i2c, spi, i3c]
related: [management-interface, register-access-layer, cmis-management-stack, i3c-based-management-communication-interface]
sources: [oif-cmis-05-4, oif-cmis-05-3, oif2026-057-01-i3cmci-draft]
---

# Management Communication Interface

The Management Communication Interface (MCI) is the data transfer layer that carries [[register-access-layer]] operations between the [[cmis-host]] and the [[cmis-managed-module]].

## Roles

The host is always the initiator. The module is always the target.

## Variants

| Variant | Meaning | Notes |
|---|---|---|
| I2CMCI | I2C-based MCI | Initial CMIS MCI, formerly described as TWI in older versions |
| SPIMCI | SPI-based MCI | Added to support use cases such as CPO and higher-bandwidth management |
| I3CMCI | I3C-based MCI | Draft/future-direction variant; see [[i3c-based-management-communication-interface]] |

## I2CMCI Notes

I2CMCI is a tailored I2C-like protocol using SCL and SDA. It uses START and STOP conditions, ACK/NACK flow control, and control bytes for READ and WRITE access.

Because I2CMCI does not include endpoint addressing, form factors may use a module select signal to let multiple modules share a bus.

## Architectural Point

Separating MCI from RAL lets CMIS carry the same management application model over future physical or protocol variants.

## Draft I3CMCI Direction

CMIS 5.4 lists an I2C-compatible MCI based on I3C as a future direction. The draft I3CMCI contribution keeps byte-addressed [[register-access-layer]] operations but moves transport negotiation, dynamic addressing, and higher-speed transfer behavior into MIPI I3C Basic semantics.

Source anchors: CMIS 5.4 Appendix B and future directions section; OIF 2026.057.01 draft Appendix B.4.
