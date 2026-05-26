---
type: concept
title: CMIS 5.4 Upper Page 01h Register Map
created: 2026-05-26
updated: 2026-05-26
tags: [cmis, memory-map, upper-memory, page-01h, register-map]
related: [management-memory-map, applications-and-data-paths, command-data-block, upper-page-0dh-register-map, cmis-5-4]
sources: [oif-cmis-05-4]
---

# CMIS 5.4 Upper Page 01h Register Map

Page 01h is the main advertising page. It tells the host which static capabilities, optional pages, controls, flags, monitors, CDB functions, lane polarity features, and application descriptor extensions the module supports.

## Addressing and Access Model

Select Page 01h with `PageSelect = 01h`; Page 01h is not banked. Struct offset 0 corresponds to register address `01h:128`.

Page 01h is largely read-only advertisement data. The page checksum at `01h:255` covers bytes `01h:130-254`, intentionally excluding firmware revision bytes `01h:128-129` so a firmware update does not force a broader memory-map update.

## Byte-Range Overview

| Bytes | Size | Field Group | Host Use |
|---|---:|---|---|
| 128-131 | 4 | inactive firmware and hardware revisions | Identify inactive firmware image and hardware revision. |
| 132-137 | 6 | supported link length | Fiber media link length advertisements. |
| 138-141 | 4 | wavelength information | Nominal wavelength and tolerance for single-wavelength modules. |
| 142 | 1 | supported pages and banks | Baseline page/bank discovery advertisement. |
| 143-144 | 2 | durations | Module and data-path timing advertisements. |
| 145-154 | 10 | module characteristics | Static module attributes and behavioral options. |
| 155-156 | 2 | supported controls | Module-level and lane-level control support. |
| 157-158 | 2 | supported flags | Flag support advertisement. |
| 159-160 | 2 | supported monitors | Monitor support advertisement. |
| 161-162 | 2 | supported signal integrity controls | SI control support advertisement. |
| 163-166 | 4 | supported CDB functionality | CDB messaging capabilities and limits. |
| 167-169 | 3 | additional durations | Additional advertised timing values. |
| 170 | 1 | reserved | Reserved. |
| 171-172 | 2 | lane polarity inversion | Host and media lane polarity support. |
| 173-174 | 2 | extended supported pages and banks | Additional page and bank support advertisement. |
| 175 | 1 | normalized application descriptors | NAD support advertisement. |
| 176-190 | 15 | media lane advertising | Media lane assignment options for up to 8 lanes. |
| 191-222 | 32 | custom | Vendor custom advertisement area. |
| 223-250 | 28 | additional application descriptors | Extension space for application advertisement. |
| 251-254 | 4 | miscellaneous advertisements | Miscellaneous feature bits. |
| 255 | 1 | page checksum | Checksum over bytes 130-254. |

## Field Notes

- Hosts should read Page 01h before probing optional pages. Use `SupportedPagesAndBanksAdvertisement` fields to avoid unnecessary accesses to unsupported upper pages.
- `SupportedPagesAndBanks173.PageDhSupported` advertises whether [upper-page-0dh-register-map](upper-page-0dh-register-map.md) is present for firmware management.
- Bytes 163-166 are the bridge from base discovery into [command-data-block](command-data-block.md) behavior. Treat CDB support as optional even when the memory page exists.
- Media lane assignment advertisement is independent from run-time lane status. Use Page 11h for active mapping and live state.
- Bytes 223-250 extend application descriptors. Host application matching code should be prepared for both the base descriptors and these additional descriptors.

## C Register View

This self-contained C view is embedded directly in the page so it is visible in Obsidian. It expands Page 01h advertisements into named byte unions and enums for banks, duration encodings, control support, CDB support, optional-page discovery, and additional application descriptors.

```c
#include <stddef.h>
#include <stdint.h>

#if defined(__GNUC__) || defined(__clang__)
#define CMIS_PACKED __attribute__((packed))
#else
#define CMIS_PACKED
#endif


typedef struct CMIS_PACKED {
    uint8_t Msb;
    uint8_t Lsb;
} cmis_be16_t;

typedef union CMIS_PACKED {
    struct {
        uint8_t Lane1 : 1;
        uint8_t Lane2 : 1;
        uint8_t Lane3 : 1;
        uint8_t Lane4 : 1;
        uint8_t Lane5 : 1;
        uint8_t Lane6 : 1;
        uint8_t Lane7 : 1;
        uint8_t Lane8 : 1;
    };
    uint8_t Raw;
} cmis_lane8_bitmap_t;

typedef struct CMIS_PACKED {
    uint8_t HostInterfaceID;
    uint8_t MediaInterfaceID;
    union {
        struct {
            uint8_t MediaLaneCount : 4;
            uint8_t HostLaneCount : 4;
        };
        uint8_t Raw;
    } LaneCounts;
    uint8_t HostLaneAssignmentOptions;
} cmis_application_descriptor4_t;

typedef enum {
    CmisBanks0Supported = 0,
    CmisBanks0To1Supported = 1,
    CmisBanks0To3Supported = 2,
    CmisBanksDefinedByPage01hByte174 = 3
} cmis_page_01h_banks_supported_t;

typedef enum {
    CmisDurationLessThan1ms = 0x0,
    CmisDuration1msTo5ms = 0x1,
    CmisDuration5msTo10ms = 0x2,
    CmisDuration10msTo50ms = 0x3,
    CmisDuration50msTo100ms = 0x4,
    CmisDuration100msTo500ms = 0x5,
    CmisDuration500msTo1s = 0x6,
    CmisDuration1sTo5s = 0x7,
    CmisDuration5sTo10s = 0x8,
    CmisDuration10sTo1min = 0x9,
    CmisDuration1minTo5min = 0xA,
    CmisDuration5minTo10min = 0xB,
    CmisDuration10minTo50min = 0xC,
    CmisDurationAtLeast50min = 0xD
} cmis_state_duration_encoding_t;

typedef union CMIS_PACKED {
    struct {
        uint8_t BaseLengthSMF : 6;
        uint8_t LengthMultiplierSMF : 2;
    };
    uint8_t Raw;
} cmis_page_01h_smf_length_t;

typedef union CMIS_PACKED {
    struct {
        uint8_t BanksSupported : 2;
        uint8_t Page03hSupported : 1;
        uint8_t CmisFfSupported : 1;
        uint8_t CoherentPagesSupported : 1;
        uint8_t DiagnosticPagesSupported : 1;
        uint8_t VDMPagesSupported : 1;
        uint8_t NetworkPathPagesSupported : 1;
    };
    uint8_t Raw;
} cmis_page_01h_supported_pages_142_t;

typedef union CMIS_PACKED {
    struct {
        uint8_t ModSelWaitTimeMantissa : 5;
        uint8_t ModSelWaitTimeExponent : 3;
    };
    uint8_t Raw;
} cmis_page_01h_modsel_wait_time_t;

typedef union CMIS_PACKED {
    struct {
        uint8_t MaxDurationDPInit : 4;
        uint8_t MaxDurationDPDeinit : 4;
    };
    uint8_t Raw;
} cmis_page_01h_dp_duration_t;

typedef union CMIS_PACKED {
    struct {
        uint8_t Aux1MonObservable : 1;
        uint8_t Aux2MonObservable : 1;
        uint8_t Aux3MonObservable : 1;
        uint8_t TimingPage15hSupported : 1;
        uint8_t ePPSSupported : 1;
        uint8_t TxInputClockingCapabilities : 2;
        uint8_t CoolingImplemented : 1;
    };
    uint8_t Raw;
} cmis_page_01h_module_characteristics_145_t;

typedef union CMIS_PACKED {
    struct {
        uint8_t TxDisableIsModuleWide : 1;
        uint8_t TxDisableIsFast : 1;
        uint8_t RxLOSIsFast : 1;
        uint8_t RxLOSType : 1;
        uint8_t RxPowerMeasurementType : 1;
        uint8_t RxOutputEqType : 2;
        uint8_t OpticalDetectorType : 1;
    };
    uint8_t Raw;
} cmis_page_01h_module_characteristics_151_t;

typedef union CMIS_PACKED {
    struct {
        uint8_t InputPolarityFlipTxSupported : 1;
        uint8_t OutputDisableTxSupported : 1;
        uint8_t AutoSquelchDisableTxSupported : 1;
        uint8_t ForcedSquelchTxSupported : 1;
        uint8_t SquelchMethodTx : 2;
        uint8_t TransmitterIsTunable : 1;
        uint8_t WavelengthIsControllable : 1;
    };
    uint8_t Raw;
} cmis_page_01h_supported_controls_tx_t;

typedef union CMIS_PACKED {
    struct {
        uint8_t OutputPolarityFlipRxSupported : 1;
        uint8_t OutputDisableRxSupported : 1;
        uint8_t AutoSquelchDisableRxSupported : 1;
        uint8_t Reserved : 4;
        uint8_t BankBroadcastSupported : 1;
    };
    uint8_t Raw;
} cmis_page_01h_supported_controls_rx_t;

typedef union CMIS_PACKED {
    struct {
        uint8_t CdbMaxPagesEPL : 4;
        uint8_t CdbAutoPagingSupported : 1;
        uint8_t CdbBackgroundModeSupported : 1;
        uint8_t CdbInstancesSupported : 2;
    };
    uint8_t Raw;
} cmis_page_01h_cdb_support_163_t;

typedef union CMIS_PACKED {
    struct {
        uint8_t Reserved0To3 : 4;
        uint8_t PageFhSupported : 1;
        uint8_t PageEhSupported : 1;
        uint8_t PageDhSupported : 1;
        uint8_t PageChSupported : 1;
    };
    uint8_t Raw;
} cmis_page_01h_supported_pages_173_t;

typedef union CMIS_PACKED {
    struct {
        uint8_t ExtraLaneBanksSupported : 5;
        uint8_t Page62hSupported : 1;
        uint8_t Page61hSupported : 1;
        uint8_t Page60hSupported : 1;
    };
    uint8_t Raw;
} cmis_page_01h_supported_pages_174_t;

typedef struct CMIS_PACKED {
    uint8_t ModuleInactiveFirmwareMajorRevision;           /* 01h:128 */
    uint8_t ModuleInactiveFirmwareMinorRevision;           /* 01h:129 */
    uint8_t ModuleHardwareMajorRevision;                   /* 01h:130 */
    uint8_t ModuleHardwareMinorRevision;                   /* 01h:131 */
    cmis_page_01h_smf_length_t SupportedLengthSMF;         /* 01h:132 */
    uint8_t LengthOM5;                                     /* 01h:133 */
    uint8_t LengthOM4;                                     /* 01h:134 */
    uint8_t LengthOM3;                                     /* 01h:135 */
    uint8_t LengthOM2;                                     /* 01h:136 */
    uint8_t LengthMultiplierSMF2;                          /* 01h:137.7-6 */
    cmis_be16_t NominalWavelength;                         /* 01h:138-139 */
    cmis_be16_t WavelengthTolerance;                       /* 01h:140-141 */
    cmis_page_01h_supported_pages_142_t SupportedPagesAndBanks142; /* 01h:142 */
    cmis_page_01h_modsel_wait_time_t ModSelWaitTime;       /* 01h:143 */
    cmis_page_01h_dp_duration_t DataPathDurations;         /* 01h:144 */
    cmis_page_01h_module_characteristics_145_t ModuleCharacteristics145; /* 01h:145 */
    uint8_t ModuleTempMax;                                 /* 01h:146 */
    uint8_t ModuleTempMin;                                 /* 01h:147 */
    cmis_be16_t PropagationDelay;                          /* 01h:148-149 */
    uint8_t OperatingVoltageMin;                           /* 01h:150 */
    cmis_page_01h_module_characteristics_151_t ModuleCharacteristics151; /* 01h:151 */
    uint8_t CDRPowerSavedPerLane;                          /* 01h:152 */
    uint8_t RxOutputLevelsAndTxInputEqMax;                 /* 01h:153 */
    uint8_t RxOutputEqLimits;                              /* 01h:154 */
    cmis_page_01h_supported_controls_tx_t SupportedControlsTx; /* 01h:155 */
    cmis_page_01h_supported_controls_rx_t SupportedControlsRx; /* 01h:156 */
    uint8_t SupportedFlagsTx;                              /* 01h:157 */
    uint8_t SupportedFlagsRx;                              /* 01h:158 */
    uint8_t SupportedModuleMonitors;                       /* 01h:159 */
    uint8_t SupportedLaneMonitors;                         /* 01h:160 */
    uint8_t SupportedSignalIntegrityTx;                    /* 01h:161 */
    uint8_t SupportedSignalIntegrityRx;                    /* 01h:162 */
    cmis_page_01h_cdb_support_163_t CDBSupport163;         /* 01h:163 */
    uint8_t CdbReadWriteLengthExtension;                   /* 01h:164 */
    uint8_t CdbExtendedBusyAndTrigger;                     /* 01h:165 */
    uint8_t CdbMaxBusyTime;                                /* 01h:166 */
    uint8_t ModulePowerDurations;                          /* 01h:167 */
    uint8_t DataPathTxDurations;                           /* 01h:168 */
    uint8_t MaxDurationBPC;                                /* 01h:169.3-0 */
    uint8_t Reserved170;                                   /* 01h:170 */
    cmis_lane8_bitmap_t DefaultInputPolarityTx;            /* 01h:171 */
    cmis_lane8_bitmap_t DefaultOutputPolarityRx;           /* 01h:172 */
    cmis_page_01h_supported_pages_173_t SupportedPagesAndBanks173; /* 01h:173 */
    cmis_page_01h_supported_pages_174_t SupportedPagesAndBanks174; /* 01h:174 */
    uint8_t NADBanksSupported;                             /* 01h:175 */
    uint8_t MediaLaneAssignmentOptionsApp1To15[15];        /* 01h:176-190 */
    uint8_t Custom191To222[32];                            /* 01h:191-222 */
    cmis_application_descriptor4_t AdditionalApplicationDescriptors[7]; /* 01h:223-250 */
    uint8_t MiscellaneousAdvertisements[4];                /* 01h:251-254 */
    uint8_t PageChecksum;                                  /* 01h:255 */
} cmis_5_4_page_01h_t;

_Static_assert(sizeof(cmis_be16_t) == 2u, "cmis_be16_t must be 2 bytes");
_Static_assert(sizeof(cmis_lane8_bitmap_t) == 1u, "lane bitmap must be 1 byte");
_Static_assert(sizeof(cmis_application_descriptor4_t) == 4u, "application descriptor must be 4 bytes");
_Static_assert(sizeof(cmis_page_01h_supported_pages_173_t) == 1u, "Page 01h byte 173 must be 1 byte");
_Static_assert(sizeof(cmis_5_4_page_01h_t) == 128u, "Page 01h must be 128 bytes");
_Static_assert(offsetof(cmis_5_4_page_01h_t, AdditionalApplicationDescriptors) == 95u, "01h:223 offset mismatch");
```

## Source Anchors

- [oif-cmis-05-4](../sources/oif-cmis-05-4.md), section 8.4, "Page 01h (Advertising)".
- Table 8-43, Page 01h overview.
- Tables 8-44 through 8-62, Page 01h field definitions.
- PDF pages 195-210 in the CMIS 5.4 source.
