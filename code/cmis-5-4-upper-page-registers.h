/*
 * CMIS 5.4 upper-page register views.
 *
 * Scope: upper-memory bytes 128-255 for Pages 00h, 01h, 02h, 04h,
 * 0Dh, 10h, 11h, 12h, 13h, 14h, and 2Fh.
 *
 * Target assumption: little-endian ARM with GCC or Clang bitfield layout.
 * CMIS multi-byte scalars are big-endian unless a table explicitly states
 * another byte order, so this header uses byte wrappers instead of native
 * uint16_t/uint32_t overlays for CMIS scalar values.
 */

#ifndef CMIS_5_4_UPPER_PAGE_REGISTERS_H
#define CMIS_5_4_UPPER_PAGE_REGISTERS_H

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

typedef struct CMIS_PACKED {
    uint8_t Byte3;
    uint8_t Byte2;
    uint8_t Byte1;
    uint8_t Byte0;
} cmis_be32_t;

typedef struct CMIS_PACKED {
    uint8_t Lsb;
    uint8_t Msb;
} cmis_le16_t;

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

typedef union CMIS_PACKED {
    struct {
        uint8_t Lane1 : 2;
        uint8_t Lane2 : 2;
        uint8_t Lane3 : 2;
        uint8_t Lane4 : 2;
    };
    uint8_t Raw;
} cmis_lane4_2bit_t;

typedef struct CMIS_PACKED {
    cmis_lane4_2bit_t Lane1To4;
    cmis_lane4_2bit_t Lane5To8;
} cmis_lane8_2bit_t;

typedef union CMIS_PACKED {
    struct {
        uint8_t OddLane : 4;
        uint8_t EvenLane : 4;
    };
    uint8_t Raw;
} cmis_lane_pair_nibble_t;

typedef struct CMIS_PACKED {
    cmis_lane_pair_nibble_t Lane1To2;
    cmis_lane_pair_nibble_t Lane3To4;
    cmis_lane_pair_nibble_t Lane5To6;
    cmis_lane_pair_nibble_t Lane7To8;
} cmis_lane8_nibble_t;

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

typedef union CMIS_PACKED {
    struct {
        uint8_t ExplicitControl : 1;
        uint8_t DataPathID : 3;
        uint8_t AppSelCode : 4;
    };
    uint8_t Raw;
} cmis_dp_config_lane_t;

typedef enum {
    CmisModulePowerClass1 = 0,
    CmisModulePowerClass2 = 1,
    CmisModulePowerClass3 = 2,
    CmisModulePowerClass4 = 3,
    CmisModulePowerClass5 = 4,
    CmisModulePowerClass6 = 5,
    CmisModulePowerClass7 = 6,
    CmisModulePowerClass8 = 7
} cmis_module_power_class_t;

typedef enum {
    CmisLengthMultiplier0p1m = 0,
    CmisLengthMultiplier1m = 1,
    CmisLengthMultiplier10m = 2,
    CmisLengthMultiplier100m = 3
} cmis_length_multiplier_t;

typedef enum {
    CmisMciFlowControlStaticBytes = 0,
    CmisMciFlowControlSpeedDependentDuration = 1
} cmis_mci_flow_control_duration_encoding_t;

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

typedef enum {
    CmisDpStateReserved = 0x0,
    CmisDpStateDeactivatedOrUnusedLane = 0x1,
    CmisDpStateInit = 0x2,
    CmisDpStateDeinit = 0x3,
    CmisDpStateActivated = 0x4,
    CmisDpStateTxTurnOn = 0x5,
    CmisDpStateTxTurnOff = 0x6,
    CmisDpStateInitialized = 0x7
} cmis_dp_state_t;

typedef enum {
    CmisConfigUndefined = 0x0,
    CmisConfigSuccess = 0x1,
    CmisConfigRejected = 0x2,
    CmisConfigRejectedInvalidAppSel = 0x3,
    CmisConfigRejectedInvalidDataPath = 0x4,
    CmisConfigRejectedInvalidSI = 0x5,
    CmisConfigRejectedLanesInUse = 0x6,
    CmisConfigRejectedPartialDataPath = 0x7,
    CmisConfigRejectedNoEmulation = 0x8,
    CmisConfigInProgress = 0xC
} cmis_config_status_t;

typedef enum {
    CmisPatternPRBS31Q = 0x0,
    CmisPatternPRBS31 = 0x1,
    CmisPatternPRBS23Q = 0x2,
    CmisPatternPRBS23 = 0x3,
    CmisPatternPRBS15Q = 0x4,
    CmisPatternPRBS15 = 0x5,
    CmisPatternPRBS13Q = 0x6,
    CmisPatternPRBS13 = 0x7,
    CmisPatternPRBS9Q = 0x8,
    CmisPatternPRBS9 = 0x9,
    CmisPatternPRBS7Q = 0xA,
    CmisPatternPRBS7 = 0xB,
    CmisPatternSSPRQ = 0xC,
    CmisPatternCustom = 0xE,
    CmisPatternUserPattern = 0xF
} cmis_pattern_id_t;

typedef enum {
    CmisDiagnosticsSelectorNone = 0x00,
    CmisDiagnosticsSelectorRealTimeBER = 0x01,
    CmisDiagnosticsSelectorHostLane1To4Counters = 0x02,
    CmisDiagnosticsSelectorHostLane5To8Counters = 0x03,
    CmisDiagnosticsSelectorMediaLane1To4Counters = 0x04,
    CmisDiagnosticsSelectorMediaLane5To8Counters = 0x05,
    CmisDiagnosticsSelectorSNR = 0x06,
    CmisDiagnosticsSelectorGatedBER = 0x11,
    CmisDiagnosticsSelectorGatedHostLane1To4Counters = 0x12,
    CmisDiagnosticsSelectorGatedHostLane5To8Counters = 0x13,
    CmisDiagnosticsSelectorGatedMediaLane1To4Counters = 0x14,
    CmisDiagnosticsSelectorGatedMediaLane5To8Counters = 0x15
} cmis_diagnostics_selector_t;

typedef enum {
    CmisVdmGroup1Supported = 0,
    CmisVdmGroups1To2Supported = 1,
    CmisVdmGroups1To3Supported = 2,
    CmisVdmGroups1To4Supported = 3
} cmis_vdm_support_t;

typedef enum {
    CmisFirmwareStatusFixedLoadRunningNoValidLoad = 0x00,
    CmisFirmwareStatusRunningACommittedAValidAAndB = 0x03,
    CmisFirmwareStatusFixedLoadRunningValidB = 0x04,
    CmisFirmwareStatusTrialRunBCommittedAValidAAndB = 0x12,
    CmisFirmwareStatusTrialRunBFallbackValidB = 0x16,
    CmisFirmwareStatusTrialRunACommittedBValidAAndB = 0x21,
    CmisFirmwareStatusRunningBCommittedBValidAAndB = 0x30,
    CmisFirmwareStatusRunningBCommittedBValidB = 0x34,
    CmisFirmwareStatusFixedLoadRunningValidA = 0x40,
    CmisFirmwareStatusRunningAUncommittedValidA = 0x41,
    CmisFirmwareStatusFixedLoadRunningCommittedAValidA = 0x42,
    CmisFirmwareStatusRunningACommittedAValidA = 0x43,
    CmisFirmwareStatusFixedLoadRunningNoCommittedLoad = 0x44,
    CmisFirmwareStatusRunningAFallbackValidA = 0x61
} cmis_firmware_status_code_t;

typedef struct CMIS_PACKED {
    uint8_t SFF8024IdentifierCopy;          /* 00h:128 */
    uint8_t VendorName[16];                 /* 00h:129-144 */
    uint8_t VendorOUI[3];                   /* 00h:145-147 */
    uint8_t VendorPN[16];                   /* 00h:148-163 */
    uint8_t VendorRev[2];                   /* 00h:164-165 */
    uint8_t VendorSN[16];                   /* 00h:166-181 */
    uint8_t DateCode[8];                    /* 00h:182-189 */
    uint8_t CLEICode[10];                   /* 00h:190-199 */
    union {
        struct {
            uint8_t Reserved : 5;
            uint8_t ModulePowerClass : 3;   /* 00h:200.7-5 */
        };
        uint8_t Raw;
    } ModulePowerClass;                     /* 00h:200 */
    uint8_t MaxPower;                       /* 00h:201 */
    union {
        struct {
            uint8_t BaseLength : 6;          /* 00h:202.5-0 */
            uint8_t LengthMultiplier : 2;    /* 00h:202.7-6 */
        };
        uint8_t Raw;
    } CableAssemblyLinkLength;              /* 00h:202 */
    uint8_t ConnectorType;                  /* 00h:203 */
    uint8_t AttenuationAt5GHz;              /* 00h:204 */
    uint8_t AttenuationAt7GHz;              /* 00h:205 */
    uint8_t AttenuationAt12p9GHz;           /* 00h:206 */
    uint8_t AttenuationAt25p8GHz;           /* 00h:207 */
    uint8_t AttenuationAt53p1GHz;           /* 00h:208 */
    uint8_t Reserved209;                    /* 00h:209 */
    cmis_lane8_bitmap_t MediaLaneUnsupported; /* 00h:210 */
    union {
        struct {
            uint8_t FarEndConfiguration : 5; /* 00h:211.4-0 */
            uint8_t Reserved : 3;
        };
        uint8_t Raw;
    } CableAssemblyInformation;             /* 00h:211 */
    uint8_t MediaInterfaceTechnology;       /* 00h:212 */
    union {
        struct {
            uint8_t MciFlowControlDuration : 7;         /* 00h:213.6-0 */
            uint8_t MciFlowControlDurationEncoding : 1; /* 00h:213.7 */
        };
        uint8_t Raw;
    } MCIRelatedAdvertisement;              /* 00h:213 */
    uint8_t Reserved214To220[7];            /* 00h:214-220 */
    uint8_t Custom221;                      /* 00h:221 */
    uint8_t PageChecksum;                   /* 00h:222 */
    uint8_t CustomInfoNV[33];               /* 00h:223-255 */
} cmis_5_4_page_00h_t;

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

typedef struct CMIS_PACKED {
    cmis_be16_t TempMonHighAlarmThreshold;                 /* 02h:128-129 */
    cmis_be16_t TempMonLowAlarmThreshold;                  /* 02h:130-131 */
    cmis_be16_t TempMonHighWarningThreshold;               /* 02h:132-133 */
    cmis_be16_t TempMonLowWarningThreshold;                /* 02h:134-135 */
    cmis_be16_t VccMonHighAlarmThreshold;                  /* 02h:136-137 */
    cmis_be16_t VccMonLowAlarmThreshold;                   /* 02h:138-139 */
    cmis_be16_t VccMonHighWarningThreshold;                /* 02h:140-141 */
    cmis_be16_t VccMonLowWarningThreshold;                 /* 02h:142-143 */
    cmis_be16_t Aux1MonHighAlarmThreshold;                 /* 02h:144-145 */
    cmis_be16_t Aux1MonLowAlarmThreshold;                  /* 02h:146-147 */
    cmis_be16_t Aux1MonHighWarningThreshold;               /* 02h:148-149 */
    cmis_be16_t Aux1MonLowWarningThreshold;                /* 02h:150-151 */
    cmis_be16_t Aux2MonHighAlarmThreshold;                 /* 02h:152-153 */
    cmis_be16_t Aux2MonLowAlarmThreshold;                  /* 02h:154-155 */
    cmis_be16_t Aux2MonHighWarningThreshold;               /* 02h:156-157 */
    cmis_be16_t Aux2MonLowWarningThreshold;                /* 02h:158-159 */
    cmis_be16_t Aux3MonHighAlarmThreshold;                 /* 02h:160-161 */
    cmis_be16_t Aux3MonLowAlarmThreshold;                  /* 02h:162-163 */
    cmis_be16_t Aux3MonHighWarningThreshold;               /* 02h:164-165 */
    cmis_be16_t Aux3MonLowWarningThreshold;                /* 02h:166-167 */
    cmis_be16_t CustomMonHighAlarmThreshold;               /* 02h:168-169 */
    cmis_be16_t CustomMonLowAlarmThreshold;                /* 02h:170-171 */
    cmis_be16_t CustomMonHighWarningThreshold;             /* 02h:172-173 */
    cmis_be16_t CustomMonLowWarningThreshold;              /* 02h:174-175 */
    cmis_be16_t OpticalPowerTxHighAlarmThreshold;          /* 02h:176-177 */
    cmis_be16_t OpticalPowerTxLowAlarmThreshold;           /* 02h:178-179 */
    cmis_be16_t OpticalPowerTxHighWarningThreshold;        /* 02h:180-181 */
    cmis_be16_t OpticalPowerTxLowWarningThreshold;         /* 02h:182-183 */
    cmis_be16_t LaserBiasCurrentHighAlarmThreshold;        /* 02h:184-185 */
    cmis_be16_t LaserBiasCurrentLowAlarmThreshold;         /* 02h:186-187 */
    cmis_be16_t LaserBiasCurrentHighWarningThreshold;      /* 02h:188-189 */
    cmis_be16_t LaserBiasCurrentLowWarningThreshold;       /* 02h:190-191 */
    cmis_be16_t OpticalPowerRxHighAlarmThreshold;          /* 02h:192-193 */
    cmis_be16_t OpticalPowerRxLowAlarmThreshold;           /* 02h:194-195 */
    cmis_be16_t OpticalPowerRxHighWarningThreshold;        /* 02h:196-197 */
    cmis_be16_t OpticalPowerRxLowWarningThreshold;         /* 02h:198-199 */
    uint8_t Reserved200To229[30];                          /* 02h:200-229 */
    uint8_t Custom230To254[25];                            /* 02h:230-254 */
    uint8_t PageChecksum;                                  /* 02h:255 */
} cmis_5_4_page_02h_t;

typedef union CMIS_PACKED {
    struct {
        uint8_t GridSupported3p125GHz : 1;
        uint8_t GridSupported6p25GHz : 1;
        uint8_t GridSupported12p5GHz : 1;
        uint8_t GridSupported25GHz : 1;
        uint8_t GridSupported50GHz : 1;
        uint8_t GridSupported100GHz : 1;
        uint8_t GridSupported33GHz : 1;
        uint8_t GridSupported75GHz : 1;
    };
    uint8_t Raw;
} cmis_page_04h_grid_support_128_t;

typedef union CMIS_PACKED {
    struct {
        uint8_t Reserved0To5 : 6;
        uint8_t GridSupported150GHz : 1;
        uint8_t FineTuningSupported : 1;
    };
    uint8_t Raw;
} cmis_page_04h_grid_support_129_t;

typedef struct CMIS_PACKED {
    cmis_page_04h_grid_support_128_t WavelengthGrids128;  /* 04h:128 */
    cmis_page_04h_grid_support_129_t WavelengthGrids129;  /* 04h:129 */
    cmis_be16_t GridLowChannel3p125GHz;                   /* 04h:130-131 */
    cmis_be16_t GridHighChannel3p125GHz;                  /* 04h:132-133 */
    cmis_be16_t GridLowChannel6p25GHz;                    /* 04h:134-135 */
    cmis_be16_t GridHighChannel6p25GHz;                   /* 04h:136-137 */
    cmis_be16_t GridLowChannel12p5GHz;                    /* 04h:138-139 */
    cmis_be16_t GridHighChannel12p5GHz;                   /* 04h:140-141 */
    cmis_be16_t GridLowChannel25GHz;                      /* 04h:142-143 */
    cmis_be16_t GridHighChannel25GHz;                     /* 04h:144-145 */
    cmis_be16_t GridLowChannel50GHz;                      /* 04h:146-147 */
    cmis_be16_t GridHighChannel50GHz;                     /* 04h:148-149 */
    cmis_be16_t GridLowChannel100GHz;                     /* 04h:150-151 */
    cmis_be16_t GridHighChannel100GHz;                    /* 04h:152-153 */
    cmis_be16_t GridLowChannel33GHz;                      /* 04h:154-155 */
    cmis_be16_t GridHighChannel33GHz;                     /* 04h:156-157 */
    cmis_be16_t GridLowChannel75GHz;                      /* 04h:158-159 */
    cmis_be16_t GridHighChannel75GHz;                     /* 04h:160-161 */
    cmis_be16_t GridLowChannel150GHz;                     /* 04h:162-163 */
    cmis_be16_t GridHighChannel150GHz;                    /* 04h:164-165 */
    cmis_be16_t GridLowChannel300GHz;                     /* 04h:166-167 */
    cmis_be16_t GridHighChannel300GHz;                    /* 04h:168-169 */
    uint8_t Reserved170To189[20];                         /* 04h:170-189 */
    cmis_be16_t FineTuningResolution;                     /* 04h:190-191 */
    cmis_be16_t FineTuningLowOffset;                      /* 04h:192-193 */
    cmis_be16_t FineTuningHighOffset;                     /* 04h:194-195 */
    uint8_t FineTuningAndPowerSupport196;                 /* 04h:196 */
    uint8_t Reserved197;                                  /* 04h:197 */
    cmis_be16_t ProgOutputPowerMin;                       /* 04h:198-199 */
    cmis_be16_t ProgOutputPowerMax;                       /* 04h:200-201 */
    uint8_t Reserved202To254[53];                         /* 04h:202-254 */
    uint8_t PageChecksum;                                 /* 04h:255 */
} cmis_5_4_page_04h_t;

typedef union CMIS_PACKED {
    struct {
        uint8_t BankASupported : 1;             /* 0Dh:128.0 */
        uint8_t BankBSupported : 1;             /* 0Dh:128.1 */
        uint8_t FixedBankSupported : 1;         /* 0Dh:128.2 */
        uint8_t FixedLoadProvidesService : 1;   /* 0Dh:128.3 */
        uint8_t Reserved4To6 : 3;
        uint8_t CdbDownloadSupported : 1;       /* 0Dh:128.7 */
    };
    uint8_t Raw;
} cmis_page_0dh_capabilities_t;

typedef union CMIS_PACKED {
    struct {
        uint8_t OperationalStatusA : 1;         /* 0Dh:136.0 */
        uint8_t AdministrativeStatusA : 1;      /* 0Dh:136.1 */
        uint8_t ValidityStatusA : 1;            /* 0Dh:136.2, 0b = valid */
        uint8_t Reserved3 : 1;
        uint8_t OperationalStatusB : 1;         /* 0Dh:136.4 */
        uint8_t AdministrativeStatusB : 1;      /* 0Dh:136.5 */
        uint8_t ValidityStatusB : 1;            /* 0Dh:136.6, 0b = valid */
        uint8_t Reserved7 : 1;
    };
    uint8_t Raw;
} cmis_page_0dh_loads_status_t;

typedef struct CMIS_PACKED {
    uint8_t MajorVersion;                       /* descriptor byte 0 */
    uint8_t MinorVersion;                       /* descriptor byte 1 */
    cmis_be16_t BuildNumber;                    /* descriptor bytes 2-3 */
    uint8_t Description[32];                    /* descriptor bytes 4-35 */
} cmis_firmware_load_version_descriptor_t;

typedef struct CMIS_PACKED {
    cmis_page_0dh_capabilities_t CapabilitiesRegister; /* 0Dh:128 */
    uint8_t Reserved129To131[3];                       /* 0Dh:129-131 */
    uint8_t Reserved132To135[4];                       /* 0Dh:132-135 */
    cmis_page_0dh_loads_status_t LoadsStatusRegister;  /* 0Dh:136 */
    uint8_t Reserved137To147[11];                      /* 0Dh:137-147 */
    cmis_firmware_load_version_descriptor_t VersionLoadA; /* 0Dh:148-183 */
    cmis_firmware_load_version_descriptor_t VersionLoadB; /* 0Dh:184-219 */
    cmis_firmware_load_version_descriptor_t VersionFixedLoad; /* 0Dh:220-255 */
} cmis_5_4_page_0dh_t;

typedef struct CMIS_PACKED {
    cmis_lane8_bitmap_t ApplyDPInitLane;                  /* 10h:143 or 178 */
    cmis_lane8_bitmap_t ApplyImmediateLane;               /* 10h:144 or 179 */
    cmis_dp_config_lane_t DataPathConfig[8];              /* 10h:145-152 or 180-187 */
    cmis_lane8_bitmap_t AdaptiveInputEqEnableTx;          /* 10h:153 or 188 */
    cmis_lane8_2bit_t AdaptiveInputEqRecallTx;            /* 10h:154-155 or 189-190 */
    cmis_lane8_nibble_t HostControlledInputEqTargetTx;    /* 10h:156-159 or 191-194 */
    cmis_lane8_bitmap_t CDREnableTx;                      /* 10h:160 or 195 */
    cmis_lane8_bitmap_t CDRBypassRx;                      /* 10h:161 or 196 */
    cmis_lane8_nibble_t OutputEqPreCursorTargetRx;        /* 10h:162-165 or 197-200 */
    cmis_lane8_nibble_t OutputEqPostCursorTargetRx;       /* 10h:166-169 or 201-204 */
    cmis_lane8_nibble_t OutputAmplitudeTargetRx;          /* 10h:170-173 or 205-208 */
    cmis_lane8_bitmap_t OutputDisableTx;                  /* 10h:174 or 209 */
    cmis_lane8_bitmap_t OutputDisableRx;                  /* 10h:175 or 210 */
    cmis_lane8_bitmap_t ApplyImmediateTx;                 /* 10h:176 or 211 */
    cmis_lane8_bitmap_t ApplyImmediateRx;                 /* 10h:177 or 212 */
} cmis_page_10h_staged_control_set_t;

typedef struct CMIS_PACKED {
    cmis_lane8_bitmap_t DPStateChangedMask;               /* 10h:213 */
    cmis_lane8_bitmap_t FailureMaskTx;                    /* 10h:214 */
    cmis_lane8_bitmap_t LOSMaskTx;                        /* 10h:215 */
    cmis_lane8_bitmap_t CDRLOLMaskTx;                     /* 10h:216 */
    cmis_lane8_bitmap_t AdaptiveInputEqFailMaskTx;        /* 10h:217 */
    cmis_lane8_bitmap_t OpticalPowerHighAlarmMaskTx;      /* 10h:218 */
    cmis_lane8_bitmap_t OpticalPowerLowAlarmMaskTx;       /* 10h:219 */
    cmis_lane8_bitmap_t OpticalPowerHighWarningMaskTx;    /* 10h:220 */
    cmis_lane8_bitmap_t OpticalPowerLowWarningMaskTx;     /* 10h:221 */
    cmis_lane8_bitmap_t LaserBiasHighAlarmMaskTx;         /* 10h:222 */
    cmis_lane8_bitmap_t LaserBiasLowAlarmMaskTx;          /* 10h:223 */
    cmis_lane8_bitmap_t LaserBiasHighWarningMaskTx;       /* 10h:224 */
    cmis_lane8_bitmap_t LaserBiasLowWarningMaskTx;        /* 10h:225 */
    cmis_lane8_bitmap_t LOSMaskRx;                        /* 10h:226 */
    cmis_lane8_bitmap_t CDRLOLMaskRx;                     /* 10h:227 */
    cmis_lane8_bitmap_t OpticalPowerHighAlarmMaskRx;      /* 10h:228 */
    cmis_lane8_bitmap_t OpticalPowerLowAlarmMaskRx;       /* 10h:229 */
    cmis_lane8_bitmap_t OpticalPowerHighWarningMaskRx;    /* 10h:230 */
    cmis_lane8_bitmap_t OpticalPowerLowWarningMaskRx;     /* 10h:231 */
    cmis_lane8_bitmap_t OutputStatusChangedMaskRx;        /* 10h:232 */
} cmis_page_10h_lane_masks_t;

typedef struct CMIS_PACKED {
    cmis_lane8_bitmap_t DPDeinitLane;                     /* 10h:128 */
    cmis_lane8_bitmap_t InputPolarityFlipTx;              /* 10h:129 */
    cmis_lane8_bitmap_t OutputDisableTx;                  /* 10h:130 */
    cmis_lane8_bitmap_t AutoSquelchDisableTx;             /* 10h:131 */
    cmis_lane8_bitmap_t OutputSquelchForceTx;             /* 10h:132 */
    uint8_t Reserved133;                                  /* 10h:133 */
    cmis_lane8_bitmap_t AdaptiveInputEqFreezeTx;          /* 10h:134 */
    cmis_lane8_2bit_t AdaptiveInputEqStoreTx;             /* 10h:135-136 */
    cmis_lane8_bitmap_t OutputPolarityFlipRx;             /* 10h:137 */
    cmis_lane8_bitmap_t OutputDisableRx;                  /* 10h:138 */
    cmis_lane8_bitmap_t AutoSquelchDisableRx;             /* 10h:139 */
    uint8_t Reserved140To142[3];                          /* 10h:140-142 */
    cmis_page_10h_staged_control_set_t StagedControlSet0; /* 10h:143-177 */
    cmis_page_10h_staged_control_set_t StagedControlSet1; /* 10h:178-212 */
    cmis_page_10h_lane_masks_t LaneSpecificMasks;         /* 10h:213-232 */
    uint8_t Reserved233To239[7];                          /* 10h:233-239 */
    uint8_t Custom240To255[16];                           /* 10h:240-255 */
} cmis_5_4_page_10h_t;

typedef struct CMIS_PACKED {
    cmis_lane8_bitmap_t DPStateChangedFlag;               /* 11h:134 */
    cmis_lane8_bitmap_t FailureFlagTx;                    /* 11h:135 */
    cmis_lane8_bitmap_t LOSFlagTx;                        /* 11h:136 */
    cmis_lane8_bitmap_t CDRLOLFlagTx;                     /* 11h:137 */
    cmis_lane8_bitmap_t AdaptiveInputEqFailFlagTx;        /* 11h:138 */
    cmis_lane8_bitmap_t OpticalPowerHighAlarmFlagTx;      /* 11h:139 */
    cmis_lane8_bitmap_t OpticalPowerLowAlarmFlagTx;       /* 11h:140 */
    cmis_lane8_bitmap_t OpticalPowerHighWarningFlagTx;    /* 11h:141 */
    cmis_lane8_bitmap_t OpticalPowerLowWarningFlagTx;     /* 11h:142 */
    cmis_lane8_bitmap_t LaserBiasHighAlarmFlagTx;         /* 11h:143 */
    cmis_lane8_bitmap_t LaserBiasLowAlarmFlagTx;          /* 11h:144 */
    cmis_lane8_bitmap_t LaserBiasHighWarningFlagTx;       /* 11h:145 */
    cmis_lane8_bitmap_t LaserBiasLowWarningFlagTx;        /* 11h:146 */
    cmis_lane8_bitmap_t LOSFlagRx;                        /* 11h:147 */
    cmis_lane8_bitmap_t CDRLOLFlagRx;                     /* 11h:148 */
    cmis_lane8_bitmap_t OpticalPowerHighAlarmFlagRx;      /* 11h:149 */
    cmis_lane8_bitmap_t OpticalPowerLowAlarmFlagRx;       /* 11h:150 */
    cmis_lane8_bitmap_t OpticalPowerHighWarningFlagRx;    /* 11h:151 */
    cmis_lane8_bitmap_t OpticalPowerLowWarningFlagRx;     /* 11h:152 */
    cmis_lane8_bitmap_t OutputStatusChangedFlagRx;        /* 11h:153 */
} cmis_page_11h_lane_flags_t;

typedef struct CMIS_PACKED {
    cmis_dp_config_lane_t DPConfigLane[8];                /* 11h:206-213 */
    cmis_lane8_bitmap_t AdaptiveInputEqEnableTx;          /* 11h:214 */
    cmis_lane8_2bit_t AdaptiveInputEqRecalledTx;          /* 11h:215-216 */
    cmis_lane8_nibble_t HostControlledInputEqTargetTx;    /* 11h:217-220 */
    cmis_lane8_bitmap_t CDREnableTx;                      /* 11h:221 */
    cmis_lane8_bitmap_t CDREnableRx;                      /* 11h:222 */
    cmis_lane8_nibble_t OutputEqPreCursorTargetRx;        /* 11h:223-226 */
    cmis_lane8_nibble_t OutputEqPostCursorTargetRx;       /* 11h:227-230 */
    cmis_lane8_nibble_t OutputAmplitudeTargetRx;          /* 11h:231-234 */
} cmis_page_11h_active_control_set_t;

typedef union CMIS_PACKED {
    struct {
        uint8_t MediaLaneToFiberMapping : 4;
        uint8_t MediaLaneToWavelengthMapping : 4;
    };
    uint8_t Raw;
} cmis_page_11h_media_lane_mapping_t;

typedef struct CMIS_PACKED {
    cmis_lane8_nibble_t DPStateHostLane;                  /* 11h:128-131 */
    cmis_lane8_bitmap_t OutputStatusRx;                   /* 11h:132 */
    cmis_lane8_bitmap_t OutputStatusTx;                   /* 11h:133 */
    cmis_page_11h_lane_flags_t LaneSpecificFlags;         /* 11h:134-153 */
    cmis_be16_t OpticalPowerTx[8];                        /* 11h:154-169 */
    cmis_be16_t LaserBiasTx[8];                           /* 11h:170-185 */
    cmis_be16_t OpticalPowerRx[8];                        /* 11h:186-201 */
    cmis_lane8_nibble_t ConfigStatusLane;                 /* 11h:202-205 */
    cmis_page_11h_active_control_set_t ActiveControlSet;  /* 11h:206-234 */
    cmis_lane8_bitmap_t DPInitPendingLane;                /* 11h:235 */
    uint8_t Reserved236To239[4];                          /* 11h:236-239 */
    cmis_page_11h_media_lane_mapping_t MediaLaneMappingTx[8]; /* 11h:240-247 */
    cmis_page_11h_media_lane_mapping_t MediaLaneMappingRx[8]; /* 11h:248-255 */
} cmis_5_4_page_11h_t;

typedef union CMIS_PACKED {
    struct {
        uint8_t FineTuningEnableTx : 1;
        uint8_t Reserved : 3;
        uint8_t GridSpacingTx : 4;
    };
    uint8_t Raw;
} cmis_page_12h_grid_spacing_t;

typedef union CMIS_PACKED {
    struct {
        uint8_t WavelengthUnlockStatusTx : 1;
        uint8_t TuningInProgressTx : 1;
        uint8_t Reserved : 6;
    };
    uint8_t Raw;
} cmis_page_12h_status_indicator_t;

typedef union CMIS_PACKED {
    struct {
        uint8_t TuningComplete : 1;
        uint8_t WavelengthUnlocked : 1;
        uint8_t InvalidChannelNumber : 1;
        uint8_t TuningNotAccepted : 1;
        uint8_t FineTuningOutOfRange : 1;
        uint8_t TargetOutputPowerOutOfRange : 1;
        uint8_t Reserved : 2;
    };
    uint8_t Raw;
} cmis_page_12h_flag_or_mask_t;

typedef struct CMIS_PACKED {
    cmis_page_12h_grid_spacing_t GridSpacings[8];         /* 12h:128-135 */
    cmis_be16_t ChannelOffsetNumbers[8];                  /* 12h:136-151 */
    cmis_be16_t FineTuningOffsets[8];                     /* 12h:152-167 */
    cmis_be32_t LaserFrequencies[8];                      /* 12h:168-199 */
    cmis_be16_t TargetOutputPower[8];                     /* 12h:200-215 */
    uint8_t Reserved216To221[6];                          /* 12h:216-221 */
    cmis_page_12h_status_indicator_t StatusIndicators[8]; /* 12h:222-229 */
    cmis_lane8_bitmap_t FlagSummary;                      /* 12h:230 */
    cmis_page_12h_flag_or_mask_t Flags[8];                /* 12h:231-238 */
    cmis_page_12h_flag_or_mask_t Masks[8];                /* 12h:239-246 */
    uint8_t Reserved247To255[9];                          /* 12h:247-255 */
} cmis_5_4_page_12h_t;

typedef union CMIS_PACKED {
    struct {
        uint8_t MediaSideOutputLoopback : 1;
        uint8_t MediaSideInputLoopback : 1;
        uint8_t HostSideOutputLoopback : 1;
        uint8_t HostSideInputLoopback : 1;
        uint8_t PerLaneHostSideLoopbacks : 1;
        uint8_t PerLaneMediaSideLoopbacks : 1;
        uint8_t SimultaneousHostAndMediaSideLoopbacks : 1;
        uint8_t Reserved : 1;
    };
    uint8_t Raw;
} cmis_page_13h_loopback_capabilities_t;

typedef union CMIS_PACKED {
    struct {
        uint8_t Reserved0To1 : 2;
        uint8_t AutoRestartGatingSupported : 1;
        uint8_t PerLaneGatingTimersSupported : 1;
        uint8_t PeriodicUpdatesSupported : 1;
        uint8_t GatingResultsSupported : 1;
        uint8_t GatingSupport : 2;
    };
    uint8_t Raw;
} cmis_page_13h_measurement_capabilities_t;

typedef union CMIS_PACKED {
    struct {
        uint8_t BitErrorRatioResultsSupported : 1;
        uint8_t BitsAndErrorsCountingSupported : 1;
        uint8_t Reserved2To3 : 2;
        uint8_t HostSideInputSNRMeasurement : 1;
        uint8_t MediaSideInputSNRMeasurement : 1;
        uint8_t HostSideFEC : 1;
        uint8_t MediaSideFEC : 1;
    };
    uint8_t Raw;
} cmis_page_13h_reporting_capabilities_t;

typedef union CMIS_PACKED {
    struct {
        uint8_t PRBSCheckerHostSidePostFEC : 1;
        uint8_t PRBSCheckerHostSidePreFEC : 1;
        uint8_t PRBSGeneratorHostSidePostFEC : 1;
        uint8_t PRBSGeneratorHostSidePreFEC : 1;
        uint8_t PRBSCheckerMediaSidePostFEC : 1;
        uint8_t PRBSCheckerMediaSidePreFEC : 1;
        uint8_t PRBSGeneratorMediaSidePostFEC : 1;
        uint8_t PRBSGeneratorMediaSidePreFEC : 1;
    };
    uint8_t Raw;
} cmis_page_13h_pattern_locations_t;

typedef struct CMIS_PACKED {
    cmis_le16_t HostSideGeneratorSupportsPattern;         /* 13h:132-133 */
    cmis_le16_t MediaSideGeneratorSupportsPattern;        /* 13h:134-135 */
    cmis_le16_t HostSideCheckerSupportsPattern;           /* 13h:136-137 */
    cmis_le16_t MediaSideCheckerSupportsPattern;          /* 13h:138-139 */
    uint8_t PatternOptions140;                            /* 13h:140 */
    uint8_t PatternSwapInvertCapabilities;                /* 13h:141 */
    uint8_t PerLanePatternCapabilities;                   /* 13h:142 */
} cmis_page_13h_pattern_capabilities_t;

typedef struct CMIS_PACKED {
    cmis_lane8_bitmap_t EnableLane;
    cmis_lane8_bitmap_t DataInvertLane;
    cmis_lane8_bitmap_t SwapSymbolBitsLane;
    cmis_lane8_bitmap_t FECSelectLane;
    cmis_lane8_nibble_t PatternSelectLane;
} cmis_page_13h_pattern_control_t;

typedef union CMIS_PACKED {
    struct {
        uint8_t MediaPRBSGeneratorClockSource : 4;
        uint8_t HostPRBSGeneratorClockSource : 4;
    };
    uint8_t Raw;
} cmis_page_13h_generator_clock_source_t;

typedef union CMIS_PACKED {
    struct {
        uint8_t UpdatePeriodSelect : 1;
        uint8_t MeasurementTime : 3;
        uint8_t AutoRestartGating : 1;
        uint8_t ResetErrorInformation : 1;
        uint8_t Reserved6 : 1;
        uint8_t StartStopIsGlobal : 1;
    };
    uint8_t Raw;
} cmis_page_13h_measurement_control_t;

typedef union CMIS_PACKED {
    struct {
        uint8_t MediaPRBSCheckerClockSource : 2;
        uint8_t HostPRBSCheckerClockSource : 2;
        uint8_t Reserved : 4;
    };
    uint8_t Raw;
} cmis_page_13h_checker_clock_source_t;

typedef struct CMIS_PACKED {
    union {
        struct {
            uint8_t Reserved : 7;
            uint8_t LossOfReferenceClockMask : 1;
        };
        uint8_t Raw;
    } LossOfReferenceClock;                              /* 13h:206 */
    uint8_t Reserved207;                                 /* 13h:207 */
    cmis_lane8_bitmap_t PatternCheckGatingCompleteMaskHostLane; /* 13h:208 */
    cmis_lane8_bitmap_t PatternCheckGatingCompleteMaskMediaLane; /* 13h:209 */
    cmis_lane8_bitmap_t PatternGeneratorLOLMaskHostLane; /* 13h:210 */
    cmis_lane8_bitmap_t PatternGeneratorLOLMaskMediaLane; /* 13h:211 */
    cmis_lane8_bitmap_t PatternCheckerLOLMaskHostLane;   /* 13h:212 */
    cmis_lane8_bitmap_t PatternCheckerLOLMaskMediaLane;  /* 13h:213 */
    uint8_t Reserved214To223[10];                        /* 13h:214-223 */
} cmis_page_13h_diagnostics_masks_t;

typedef struct CMIS_PACKED {
    cmis_page_13h_loopback_capabilities_t LoopbackCapabilities; /* 13h:128 */
    cmis_page_13h_measurement_capabilities_t DiagnosticsMeasurementCapabilities; /* 13h:129 */
    cmis_page_13h_reporting_capabilities_t DiagnosticReportingCapabilities; /* 13h:130 */
    cmis_page_13h_pattern_locations_t PatternGenerationAndCheckingLocations; /* 13h:131 */
    cmis_page_13h_pattern_capabilities_t PatternGenerationAndCheckingCapabilities; /* 13h:132-142 */
    uint8_t Reserved143;                                  /* 13h:143 */
    cmis_page_13h_pattern_control_t PatternGeneratorControlsHostSide; /* 13h:144-151 */
    cmis_page_13h_pattern_control_t PatternGeneratorControlsMediaSide; /* 13h:152-159 */
    cmis_page_13h_pattern_control_t PatternCheckerControlsHostSide; /* 13h:160-167 */
    cmis_page_13h_pattern_control_t PatternCheckerControlsMediaSide; /* 13h:168-175 */
    cmis_page_13h_generator_clock_source_t GeneratorClockSource; /* 13h:176 */
    cmis_page_13h_measurement_control_t MeasurementControl; /* 13h:177 */
    cmis_page_13h_checker_clock_source_t CheckerClockSource; /* 13h:178 */
    uint8_t Reserved179;                                  /* 13h:179 */
    cmis_lane8_bitmap_t MediaSideOutputLoopbackEnable;    /* 13h:180 */
    cmis_lane8_bitmap_t MediaSideInputLoopbackEnable;     /* 13h:181 */
    cmis_lane8_bitmap_t HostSideOutputLoopbackEnable;     /* 13h:182 */
    cmis_lane8_bitmap_t HostSideInputLoopbackEnable;      /* 13h:183 */
    uint8_t HostScratchpadArea[8];                        /* 13h:184-191 */
    uint8_t Reserved192To195[4];                          /* 13h:192-195 */
    uint8_t Custom196To205[10];                           /* 13h:196-205 */
    cmis_page_13h_diagnostics_masks_t DiagnosticsMasks;   /* 13h:206-223 */
    uint8_t UserPattern[32];                              /* 13h:224-255 */
} cmis_5_4_page_13h_t;

typedef struct CMIS_PACKED {
    union {
        struct {
            uint8_t Reserved : 7;
            uint8_t LossOfReferenceClockFlag : 1;
        };
        uint8_t Raw;
    } LossOfReferenceClock;                              /* 14h:132 */
    uint8_t Reserved133;                                 /* 14h:133 */
    cmis_lane8_bitmap_t PatternCheckGatingCompleteFlagHostLane; /* 14h:134 */
    cmis_lane8_bitmap_t PatternCheckGatingCompleteFlagMediaLane; /* 14h:135 */
    cmis_lane8_bitmap_t PatternGeneratorLOLFlagHostLane; /* 14h:136 */
    cmis_lane8_bitmap_t PatternGeneratorLOLFlagMediaLane; /* 14h:137 */
    cmis_lane8_bitmap_t PatternCheckerLOLFlagHostLane;   /* 14h:138 */
    cmis_lane8_bitmap_t PatternCheckerLOLFlagMediaLane;  /* 14h:139 */
} cmis_page_14h_diagnostics_flags_t;

typedef struct CMIS_PACKED {
    uint8_t DiagnosticsSelector;                         /* 14h:128 */
    uint8_t Reserved129;                                 /* 14h:129 */
    uint8_t Custom130To131[2];                           /* 14h:130-131 */
    cmis_page_14h_diagnostics_flags_t DiagnosticsFlags;  /* 14h:132-139 */
    uint8_t Reserved140To191[52];                        /* 14h:140-191 */
    uint8_t DiagnosticsData[64];                         /* 14h:192-255 */
} cmis_5_4_page_14h_t;

typedef union CMIS_PACKED {
    struct {
        uint8_t VDMSupport : 2;
        uint8_t PowerSavingSupport : 1;
        uint8_t DutyCycleSupport : 1;
        uint8_t Reserved : 4;
    };
    uint8_t Raw;
} cmis_page_2fh_vdm_advertisement_t;

typedef union CMIS_PACKED {
    struct {
        uint8_t Reserved0To1 : 2;
        uint8_t MonitoringDutyCycle : 4;
        uint8_t PowerSavingMode : 1;
        uint8_t FreezeRequest : 1;
    };
    uint8_t Raw;
} cmis_page_2fh_dynamic_controls_t;

typedef union CMIS_PACKED {
    struct {
        uint8_t Reserved0To5 : 6;
        uint8_t UnfreezeDone : 1;
        uint8_t FreezeDone : 1;
    };
    uint8_t Raw;
} cmis_page_2fh_dynamic_status_t;

typedef struct CMIS_PACKED {
    cmis_page_2fh_vdm_advertisement_t VDMAdvertisement;  /* 2Fh:128 */
    cmis_be16_t FineIntervalLength;                      /* 2Fh:129-130 */
    uint8_t Reserved131To143[13];                        /* 2Fh:131-143 */
    cmis_page_2fh_dynamic_controls_t DynamicControls;    /* 2Fh:144 */
    cmis_page_2fh_dynamic_status_t DynamicStatus;        /* 2Fh:145 */
    uint8_t Reserved146To255[110];                       /* 2Fh:146-255 */
} cmis_5_4_page_2fh_t;

#if defined(__STDC_VERSION__) && (__STDC_VERSION__ >= 201112L)
_Static_assert(sizeof(cmis_be16_t) == 2u, "cmis_be16_t must be 2 bytes");
_Static_assert(sizeof(cmis_be32_t) == 4u, "cmis_be32_t must be 4 bytes");
_Static_assert(sizeof(cmis_lane8_bitmap_t) == 1u, "lane bitmap must be 1 byte");
_Static_assert(sizeof(cmis_lane8_2bit_t) == 2u, "2-bit lane map must be 2 bytes");
_Static_assert(sizeof(cmis_lane8_nibble_t) == 4u, "nibble lane map must be 4 bytes");
_Static_assert(sizeof(cmis_application_descriptor4_t) == 4u, "application descriptor must be 4 bytes");
_Static_assert(sizeof(cmis_page_01h_supported_pages_173_t) == 1u, "Page 01h byte 173 must be 1 byte");
_Static_assert(sizeof(cmis_page_0dh_capabilities_t) == 1u, "Page 0Dh capabilities must be 1 byte");
_Static_assert(sizeof(cmis_page_0dh_loads_status_t) == 1u, "Page 0Dh load status must be 1 byte");
_Static_assert(sizeof(cmis_firmware_load_version_descriptor_t) == 36u, "firmware descriptor must be 36 bytes");
_Static_assert(sizeof(cmis_page_10h_staged_control_set_t) == 35u, "Page 10h staged set must be 35 bytes");
_Static_assert(sizeof(cmis_page_10h_lane_masks_t) == 20u, "Page 10h masks must be 20 bytes");
_Static_assert(sizeof(cmis_page_11h_lane_flags_t) == 20u, "Page 11h flags must be 20 bytes");
_Static_assert(sizeof(cmis_page_11h_active_control_set_t) == 29u, "Page 11h active control set must be 29 bytes");
_Static_assert(sizeof(cmis_page_13h_pattern_control_t) == 8u, "Page 13h pattern controls must be 8 bytes");
_Static_assert(sizeof(cmis_page_13h_diagnostics_masks_t) == 18u, "Page 13h diagnostics masks must be 18 bytes");
_Static_assert(sizeof(cmis_page_14h_diagnostics_flags_t) == 8u, "Page 14h diagnostics flags must be 8 bytes");

_Static_assert(sizeof(cmis_5_4_page_00h_t) == 128u, "Page 00h must be 128 bytes");
_Static_assert(sizeof(cmis_5_4_page_01h_t) == 128u, "Page 01h must be 128 bytes");
_Static_assert(sizeof(cmis_5_4_page_02h_t) == 128u, "Page 02h must be 128 bytes");
_Static_assert(sizeof(cmis_5_4_page_04h_t) == 128u, "Page 04h must be 128 bytes");
_Static_assert(sizeof(cmis_5_4_page_0dh_t) == 128u, "Page 0Dh must be 128 bytes");
_Static_assert(sizeof(cmis_5_4_page_10h_t) == 128u, "Page 10h must be 128 bytes");
_Static_assert(sizeof(cmis_5_4_page_11h_t) == 128u, "Page 11h must be 128 bytes");
_Static_assert(sizeof(cmis_5_4_page_12h_t) == 128u, "Page 12h must be 128 bytes");
_Static_assert(sizeof(cmis_5_4_page_13h_t) == 128u, "Page 13h must be 128 bytes");
_Static_assert(sizeof(cmis_5_4_page_14h_t) == 128u, "Page 14h must be 128 bytes");
_Static_assert(sizeof(cmis_5_4_page_2fh_t) == 128u, "Page 2Fh must be 128 bytes");

_Static_assert(offsetof(cmis_5_4_page_00h_t, PageChecksum) == 94u, "00h:222 offset mismatch");
_Static_assert(offsetof(cmis_5_4_page_01h_t, AdditionalApplicationDescriptors) == 95u, "01h:223 offset mismatch");
_Static_assert(offsetof(cmis_5_4_page_02h_t, PageChecksum) == 127u, "02h:255 offset mismatch");
_Static_assert(offsetof(cmis_5_4_page_04h_t, PageChecksum) == 127u, "04h:255 offset mismatch");
_Static_assert(offsetof(cmis_5_4_page_0dh_t, LoadsStatusRegister) == 8u, "0Dh:136 offset mismatch");
_Static_assert(offsetof(cmis_5_4_page_0dh_t, VersionLoadA) == 20u, "0Dh:148 offset mismatch");
_Static_assert(offsetof(cmis_5_4_page_0dh_t, VersionLoadB) == 56u, "0Dh:184 offset mismatch");
_Static_assert(offsetof(cmis_5_4_page_0dh_t, VersionFixedLoad) == 92u, "0Dh:220 offset mismatch");
_Static_assert(offsetof(cmis_5_4_page_10h_t, StagedControlSet0) == 15u, "10h:143 offset mismatch");
_Static_assert(offsetof(cmis_5_4_page_11h_t, ActiveControlSet) == 78u, "11h:206 offset mismatch");
_Static_assert(offsetof(cmis_5_4_page_12h_t, FlagSummary) == 102u, "12h:230 offset mismatch");
_Static_assert(offsetof(cmis_5_4_page_13h_t, DiagnosticsMasks) == 78u, "13h:206 offset mismatch");
_Static_assert(offsetof(cmis_5_4_page_14h_t, DiagnosticsData) == 64u, "14h:192 offset mismatch");
_Static_assert(offsetof(cmis_5_4_page_2fh_t, DynamicControls) == 16u, "2Fh:144 offset mismatch");
#endif

#endif /* CMIS_5_4_UPPER_PAGE_REGISTERS_H */
