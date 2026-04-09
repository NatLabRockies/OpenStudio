/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "Model.hpp"
#include "Model_Impl.hpp"

#include <utilities/core/Compare.hpp>
#include <utilities/idd/Refrigeration_Subcooler_FieldEnums.hxx>

#include "ModelObject/AirLoopHVACReturnPath_Impl.hpp"
#include "Mixer/AirLoopHVACReturnPlenum_Impl.hpp"
#include "Splitter/AirLoopHVACSupplyPlenum_Impl.hpp"
#include "ModelObject/AirLoopHVACSupplyPath_Impl.hpp"
#include "ModelObject/AirLoopHVACControllerList_Impl.hpp"
#include "ModelObject/RoomAirTemperaturePatternConstantGradient_Impl.hpp"
#include "ModelObject/RoomAirTemperaturePatternNondimensionalHeight_Impl.hpp"
#include "ModelObject/RoomAirTemperaturePatternSurfaceMapping_Impl.hpp"
#include "ModelObject/RoomAirTemperaturePatternTwoGradient_Impl.hpp"
#include "ModelObject/RoomAirTemperaturePatternUserDefined_Impl.hpp"
#include "ModelObject/RoomAirModelType_Impl.hpp"
#include "ModelObject/RoomAirSettingsAirflowNetwork_Impl.hpp"
#include "ModelObject/RoomAirSettingsCrossVentilation_Impl.hpp"
#include "ModelObject/RoomAirSettingsOneNodeDisplacementVentilation_Impl.hpp"
#include "ModelObject/RoomAirSettingsThreeNodeDisplacementVentilation_Impl.hpp"
#include "ModelObject/RoomAirSettingsUnderFloorAirDistributionExterior_Impl.hpp"
#include "ModelObject/RoomAirSettingsUnderFloorAirDistributionInterior_Impl.hpp"
#include "ModelObject/RoomAirNode_Impl.hpp"
#include "ModelObject/RoomAirNodeAirflowNetwork_Impl.hpp"
#include "ModelObject/RoomAirNodeAirflowNetworkHVACEquipment_Impl.hpp"
#include "ModelObject/RoomAirNodeAirflowNetworkAdjacentSurfaceList_Impl.hpp"
#include "ModelObject/RoomAirNodeAirflowNetworkInternalGains_Impl.hpp"
#include "ModelObject/ThermalStorageChilledWaterMixed_Impl.hpp"
#include "ModelObject/ThermalStorageHotWaterStratified_Impl.hpp"
#include "ModelObject/ThermalStorageIceSimple_Impl.hpp"
#include "ModelObject/ThermalStoragePCM_Impl.hpp"
#include "ModelObject/ThermalStorageSizing_Impl.hpp"
#include "ModelObject/Version_Impl.hpp"
#include "ModelObject/RunPeriodControlDaylightSavingTime_Impl.hpp"
#include "ModelObject/RunPeriodControlSpecialDays_Impl.hpp"
#include "HVACComponent/AirLoopHVACOutdoorAirSystem_Impl.hpp"
#include "ModelObject/AirLoopHVACOutdoorAirSystemEquipmentList_Impl.hpp"
#include "Mixer/AirTerminalDualDuctConstantVolume_Impl.hpp"
#include "Mixer/AirTerminalDualDuctVAV_Impl.hpp"
#include "Mixer/AirTerminalDualDuctVAVOutdoorAir_Impl.hpp"
#include "StraightComponent/AirTerminalSingleDuctConstantVolumeCooledBeam_Impl.hpp"
#include "StraightComponent/AirTerminalSingleDuctConstantVolumeFourPipeBeam_Impl.hpp"
#include "StraightComponent/AirTerminalSingleDuctConstantVolumeFourPipeInduction_Impl.hpp"
#include "ModelObject/AirTerminalSingleDuctUserDefined_Impl.hpp"
#include "StraightComponent/AirTerminalSingleDuctVAVHeatAndCoolNoReheat_Impl.hpp"
#include "StraightComponent/AirTerminalSingleDuctVAVHeatAndCoolReheat_Impl.hpp"
#include "StraightComponent/AirTerminalSingleDuctVAVNoReheat_Impl.hpp"
#include "StraightComponent/AirTerminalSingleDuctVAVReheat_Impl.hpp"
#include "ModelObject/AirTerminalSingleDuctVAVReheatVariableSpeedFan_Impl.hpp"
#include "StraightComponent/AirTerminalSingleDuctConstantVolumeReheat_Impl.hpp"
#include "StraightComponent/AirTerminalSingleDuctInletSideMixer_Impl.hpp"
#include "StraightComponent/AirTerminalSingleDuctParallelPIUReheat_Impl.hpp"
#include "StraightComponent/AirTerminalSingleDuctSeriesPIUReheat_Impl.hpp"
#include "Mixer/AirLoopHVACZoneMixer_Impl.hpp"
#include "Mixer/ConnectorMixer_Impl.hpp"
#include "Splitter/AirLoopHVACZoneSplitter_Impl.hpp"
#include "Splitter/ConnectorSplitter_Impl.hpp"
#include "Loop/AirLoopHVAC_Impl.hpp"
#include "Loop/PlantLoop_Impl.hpp"
#include "ModelObject/AvailabilityManagerAssignmentList_Impl.hpp"
#include "AvailabilityManager/AvailabilityManagerNightCycle_Impl.hpp"
#include "AvailabilityManager/AvailabilityManagerDifferentialThermostat_Impl.hpp"
#include "AvailabilityManager/AvailabilityManagerHighTemperatureTurnOn_Impl.hpp"
#include "AvailabilityManager/AvailabilityManagerHighTemperatureTurnOff_Impl.hpp"
#include "AvailabilityManager/AvailabilityManagerLowTemperatureTurnOn_Impl.hpp"
#include "AvailabilityManager/AvailabilityManagerLowTemperatureTurnOff_Impl.hpp"
#include "AvailabilityManager/AvailabilityManagerHybridVentilation_Impl.hpp"
#include "AvailabilityManager/AvailabilityManagerNightVentilation_Impl.hpp"
#include "AvailabilityManager/AvailabilityManagerOptimumStart_Impl.hpp"
#include "AvailabilityManager/AvailabilityManagerScheduledOff_Impl.hpp"
#include "AvailabilityManager/AvailabilityManagerScheduledOn_Impl.hpp"
#include "StraightComponent/AirTerminalSingleDuctConstantVolumeNoReheat_Impl.hpp"
#include "StraightComponent/BoilerHotWater_Impl.hpp"
#include "StraightComponent/BoilerSteam_Impl.hpp"
#include "StraightComponent/DistrictCooling_Impl.hpp"
#include "StraightComponent/DistrictHeatingSteam_Impl.hpp"
#include "StraightComponent/DistrictHeatingWater_Impl.hpp"
#include "StraightComponent/Duct_Impl.hpp"
#include "StraightComponent/PipeAdiabatic_Impl.hpp"
#include "StraightComponent/PipeIndoor_Impl.hpp"
#include "StraightComponent/PipeOutdoor_Impl.hpp"
#include "ModelObject/PipeAdiabaticSteam_Impl.hpp"
#include "ModelObject/PipeUnderground_Impl.hpp"
#include "ModelObject/PipingSystemUndergroundDomain_Impl.hpp"
#include "ModelObject/PipingSystemUndergroundPipeCircuit_Impl.hpp"
#include "ModelObject/PipingSystemUndergroundPipeSegment_Impl.hpp"
#include "StraightComponent/PumpConstantSpeed_Impl.hpp"
#include "StraightComponent/PumpVariableSpeed_Impl.hpp"
#include "StraightComponent/HeaderedPumpsConstantSpeed_Impl.hpp"
#include "StraightComponent/HeaderedPumpsVariableSpeed_Impl.hpp"
#include "StraightComponent/HumidifierSteamElectric_Impl.hpp"
#include "StraightComponent/HumidifierSteamGas_Impl.hpp"
#include "ModelObject/DuctLossConduction_Impl.hpp"
#include "ModelObject/DuctLossLeakage_Impl.hpp"
#include "ModelObject/DuctLossMakeupAir_Impl.hpp"
#include "ModelObject/FluidPropertiesConcentration_Impl.hpp"
#include "ModelObject/FluidPropertiesGlycolConcentration_Impl.hpp"
#include "ModelObject/FluidPropertiesName_Impl.hpp"
#include "ModelObject/FluidPropertiesSaturated_Impl.hpp"
#include "ModelObject/FluidPropertiesSuperheated_Impl.hpp"
#include "ModelObject/FluidPropertiesTemperatures_Impl.hpp"
#include "ModelObject/FuelFactors_Impl.hpp"
#include "ModelObject/MeterCustom_Impl.hpp"
#include "ModelObject/MeterCustomDecrement_Impl.hpp"
#include "ModelObject/FoundationKiva_Impl.hpp"
#include "ModelObject/FoundationKivaSettings_Impl.hpp"
#include "StraightComponent/EvaporativeCoolerDirectResearchSpecial_Impl.hpp"
#include "StraightComponent/EvaporativeCoolerIndirectResearchSpecial_Impl.hpp"
#include "StraightComponent/EvaporativeFluidCoolerSingleSpeed_Impl.hpp"
#include "StraightComponent/EvaporativeFluidCoolerTwoSpeed_Impl.hpp"
#include "StraightComponent/FluidCoolerSingleSpeed_Impl.hpp"
#include "StraightComponent/FluidCoolerTwoSpeed_Impl.hpp"
#include "StraightComponent/GroundHeatExchangerHorizontalTrench_Impl.hpp"
#include "StraightComponent/GroundHeatExchangerVertical_Impl.hpp"
#include "StraightComponent/SwimmingPoolIndoor_Impl.hpp"
#include "ModelObject/GroundHeatExchangerVerticalArray_Impl.hpp"
#include "ModelObject/GroundHeatExchangerVerticalSingle_Impl.hpp"
#include "ModelObject/GroundHeatExchangerVerticalSizingRectangle_Impl.hpp"
#include "ModelObject/GroundHeatExchangerPond_Impl.hpp"
#include "ModelObject/GroundHeatExchangerSurface_Impl.hpp"
#include "ModelObject/GroundHeatExchangerSlinky_Impl.hpp"
#include "ModelObject/EvaporativeCoolerDirectCelDekPad_Impl.hpp"
#include "ModelObject/EvaporativeCoolerIndirectCelDekPad_Impl.hpp"
#include "ModelObject/EvaporativeCoolerIndirectWetCoil_Impl.hpp"
#include "StraightComponent/CoolingTowerSingleSpeed_Impl.hpp"
#include "StraightComponent/CoolingTowerTwoSpeed_Impl.hpp"
#include "StraightComponent/CoolingTowerVariableSpeed_Impl.hpp"
#include "ModelObject/CoolingTowerVariableSpeedMerkel_Impl.hpp"
#include "ModelObject/CoolingTowerPerformanceCoolTools_Impl.hpp"
#include "ModelObject/CoolingTowerPerformanceYorkCalc_Impl.hpp"
#include "WaterToWaterComponent/ChillerAbsorption_Impl.hpp"
#include "WaterToWaterComponent/ChillerAbsorptionIndirect_Impl.hpp"
#include "WaterToWaterComponent/ThermalStorageChilledWaterStratified_Impl.hpp"
#include "WaterToWaterComponent/WaterHeaterStratified_Impl.hpp"
#include "ModelObject/ChillerCombustionTurbine_Impl.hpp"
#include "ModelObject/GeneratorCombustionTurbine_Impl.hpp"
#include "ModelObject/GeneratorInternalCombustionEngine_Impl.hpp"
#include "ModelObject/GeneratorMicroCHP_Impl.hpp"
#include "ModelObject/GeneratorMicroCHPNonNormalizedParameters_Impl.hpp"
#include "Generator/GeneratorMicroTurbine_Impl.hpp"
#include "Generator/GeneratorPhotovoltaic_Impl.hpp"
#include "Generator/GeneratorWindTurbine_Impl.hpp"
#include "Generator/GeneratorPVWatts_Impl.hpp"
#include "PhotovoltaicPerformance/PhotovoltaicPerformanceSimple_Impl.hpp"
#include "PhotovoltaicPerformance/PhotovoltaicPerformanceSandia_Impl.hpp"
#include "Generator/GeneratorFuelCell_Impl.hpp"
#include "ModelObject/GeneratorFuelCellAirSupply_Impl.hpp"
#include "ModelObject/GeneratorFuelCellAuxiliaryHeater_Impl.hpp"
#include "ModelObject/GeneratorFuelCellElectricalStorage_Impl.hpp"
#include "ModelObject/GeneratorFuelCellInverter_Impl.hpp"
#include "ModelObject/GeneratorFuelCellPowerModule_Impl.hpp"
#include "ModelObject/GeneratorFuelCellWaterSupply_Impl.hpp"
#include "ModelObject/GeneratorFuelSupply_Impl.hpp"
#include "StraightComponent/GeneratorFuelCellExhaustGasToWaterHeatExchanger_Impl.hpp"
#include "StraightComponent/GeneratorFuelCellStackCooler_Impl.hpp"
#include "ModelObject/ChillerHeaterAbsorptionDirectFired_Impl.hpp"
#include "ModelObject/ChillerHeaterAbsorptionDoubleEffect_Impl.hpp"
#include "ParentObject/ChillerHeaterPerformanceElectricEIR_Impl.hpp"
#include "ParentObject/CoilPerformanceDXCooling_Impl.hpp"
#include "ParentObject/ComponentCostAdjustments_Impl.hpp"
#include "ParentObject/CurrencyType_Impl.hpp"
#include "ParentObject/LifeCycleCostParameters_Impl.hpp"
#include "ParentObject/LifeCycleCostUsePriceEscalation_Impl.hpp"
#include "ParentObject/RunPeriod_Impl.hpp"
#include "ParentObject/ElectricLoadCenterDistribution_Impl.hpp"
#include "ParentObject/ElectricLoadCenterStorageConverter_Impl.hpp"
#include "ParentObject/RefrigerationCase_Impl.hpp"
#include "ParentObject/RefrigerationCondenserAirCooled_Impl.hpp"
#include "ParentObject/RefrigerationCondenserEvaporativeCooled_Impl.hpp"
#include "ParentObject/RefrigerationGasCoolerAirCooled_Impl.hpp"
#include "ParentObject/RefrigerationCompressor_Impl.hpp"
#include "ParentObject/RefrigerationSecondarySystem_Impl.hpp"
#include "ModelObject/RefrigerationCondenserCascade_Impl.hpp"
#include "ModelObject/RefrigerationSubcooler_Impl.hpp"
#include "ModelObject/RefrigerationSystem_Impl.hpp"
#include "ModelObject/RefrigerationSubcoolerLiquidSuction_Impl.hpp"
#include "ModelObject/RefrigerationSubcoolerMechanical_Impl.hpp"
#include "ModelObject/RefrigerationTranscriticalSystem_Impl.hpp"
#include "ModelObject/RefrigerationWalkIn_Impl.hpp"
#include "Inverter/ElectricLoadCenterInverterLookUpTable_Impl.hpp"
#include "Inverter/ElectricLoadCenterInverterPVWatts_Impl.hpp"
#include "Inverter/ElectricLoadCenterInverterSimple_Impl.hpp"
#include "ModelObject/ElectricLoadCenterInverterFunctionOfPower_Impl.hpp"
#include "ModelObject/ElectricLoadCenterTransformer_Impl.hpp"
#include "ModelObject/EnergyManagementSystemActuator_Impl.hpp"
#include "ModelObject/EnergyManagementSystemConstructionIndexVariable_Impl.hpp"
#include "ModelObject/EnergyManagementSystemInternalVariable_Impl.hpp"
#include "ModelObject/EnergyManagementSystemGlobalVariable_Impl.hpp"
#include "ModelObject/EnergyManagementSystemMeteredOutputVariable_Impl.hpp"
#include "ModelObject/EnergyManagementSystemOutputVariable_Impl.hpp"
#include "ModelObject/OutputConstructions_Impl.hpp"
#include "ModelObject/OutputDaylightFactors_Impl.hpp"
#include "ModelObject/OutputDebuggingData_Impl.hpp"
#include "ModelObject/OutputDiagnostics_Impl.hpp"
#include "ModelObject/OutputEnergyManagementSystem_Impl.hpp"
#include "ModelObject/OutputEnvironmentalImpactFactors_Impl.hpp"
#include "ModelObject/OutputControlFiles_Impl.hpp"
#include "ModelObject/OutputControlIlluminanceMapStyle_Impl.hpp"
#include "ModelObject/OutputControlReportingTolerances_Impl.hpp"
#include "ModelObject/OutputControlResilienceSummaries_Impl.hpp"
#include "ModelObject/OutputControlSizingStyle_Impl.hpp"
#include "ModelObject/OutputControlTableStyle_Impl.hpp"
#include "ModelObject/OutputControlTimestamp_Impl.hpp"
#include "ModelObject/OutputControlSurfaceColorScheme_Impl.hpp"
#include "ModelObject/OutputJSON_Impl.hpp"
#include "ModelObject/OutputMeter_Impl.hpp"
#include "ModelObject/OutputMeterCumulative_Impl.hpp"
#include "ModelObject/OutputMeterCumulativeMeterFileOnly_Impl.hpp"
#include "ModelObject/OutputMeterMeterFileOnly_Impl.hpp"
#include "ModelObject/OutputPreprocessorMessage_Impl.hpp"
#include "ModelObject/OutputSQLite_Impl.hpp"
#include "ModelObject/OutputSchedules_Impl.hpp"
#include "ModelObject/OutputTableAnnual_Impl.hpp"
#include "ModelObject/OutputTableMonthly_Impl.hpp"
#include "ModelObject/OutputTableReportPeriod_Impl.hpp"
#include "ModelObject/OutputTableSummaryReports_Impl.hpp"
#include "ModelObject/OutputTableTimeBins_Impl.hpp"
#include "ModelObject/OutputVariable_Impl.hpp"
#include "ModelObject/OutputVariableDictionary_Impl.hpp"
#include "ModelObject/OutputSurfacesList_Impl.hpp"
#include "ModelObject/OutputSurfacesDrawing_Impl.hpp"
#include "ModelObject/PythonPluginOutputVariable_Impl.hpp"
#include "ModelObject/PythonPluginTrendVariable_Impl.hpp"
#include "ModelObject/PythonPluginVariable_Impl.hpp"
#include "ModelObject/EnergyManagementSystemSensor_Impl.hpp"
#include "ModelObject/EnergyManagementSystemTrendVariable_Impl.hpp"
#include "ModelObject/EnvironmentalImpactFactors_Impl.hpp"
#include "ModelObject/EnergyManagementSystemProgram_Impl.hpp"
#include "ModelObject/EnergyManagementSystemSubroutine_Impl.hpp"
#include "ModelObject/EnergyManagementSystemProgramCallingManager_Impl.hpp"
#include "ModelObject/ElectricLoadCenterStorageBattery_Impl.hpp"
#include "ElectricalStorage/ElectricLoadCenterStorageSimple_Impl.hpp"
#include "ElectricalStorage/ElectricLoadCenterStorageLiIonNMCBattery_Impl.hpp"
#include "ModelObject/ChillerConstantCOP_Impl.hpp"
#include "ModelObject/ChillerEngineDriven_Impl.hpp"
#include "WaterToWaterComponent/ChillerElectric_Impl.hpp"
#include "WaterToWaterComponent/ChillerElectricEIR_Impl.hpp"
#include "WaterToWaterComponent/ChillerElectricReformulatedEIR_Impl.hpp"
#include "WaterToWaterComponent/ChillerElectricASHRAE205_Impl.hpp"
#include "ModelObject/Branch_Impl.hpp"
#include "ParentObject/Building_Impl.hpp"
#include "ParentObject/Site_Impl.hpp"
#include "PlanarSurface/Surface_Impl.hpp"
#include "PlanarSurface/SubSurface_Impl.hpp"
#include "PlanarSurface/InteriorPartitionSurface_Impl.hpp"
#include "BranchList_Impl.hpp"
#include "StraightComponent/CoilCoolingDXMultiSpeed_Impl.hpp"
#include "StraightComponent/CoilCoolingDXSingleSpeed_Impl.hpp"
#include "StraightComponent/CoilCoolingDXSingleSpeedThermalStorage_Impl.hpp"
#include "StraightComponent/CoilCoolingDXVariableSpeed_Impl.hpp"
#include "StraightComponent/CoilCoolingDXTwoSpeed_Impl.hpp"
#include "StraightComponent/CoilCoolingDXTwoStageWithHumidityControlMode_Impl.hpp"
#include "ResourceObject/CoilCoolingDXCurveFitPerformance_Impl.hpp"
#include "ResourceObject/CoilCoolingDXCurveFitOperatingMode_Impl.hpp"
#include "ResourceObject/CoilCoolingDXCurveFitSpeed_Impl.hpp"
#include "ResourceObject/HeatExchangerDesiccantBalancedFlowPerformanceDataType1_Impl.hpp"
#include "ResourceObject/MaterialPropertyGlazingSpectralData_Impl.hpp"
#include "ResourceObject/ShadingControl_Impl.hpp"
#include "ResourceObject/PythonPluginSearchPaths_Impl.hpp"
#include "ResourceObject/WindowPropertyFrameAndDivider_Impl.hpp"
#include "Glazing/RefractionExtinctionGlazing_Impl.hpp"
#include "Glazing/ThermochromicGlazing_Impl.hpp"
#include "Glazing/SimpleGlazing_Impl.hpp"
#include "Glazing/StandardGlazing_Impl.hpp"
#include "ModelObject/MaterialPropertyHeatAndMoistureTransferDiffusion_Impl.hpp"
#include "ModelObject/MaterialPropertyHeatAndMoistureTransferRedistribution_Impl.hpp"
#include "ModelObject/MaterialPropertyHeatAndMoistureTransferSettings_Impl.hpp"
#include "ModelObject/MaterialPropertyHeatAndMoistureTransferSorptionIsotherm_Impl.hpp"
#include "ModelObject/MaterialPropertyHeatAndMoistureTransferSuction_Impl.hpp"
#include "ModelObject/MaterialPropertyHeatAndMoistureTransferThermalConductivity_Impl.hpp"
#include "ModelObject/MaterialPropertyMoisturePenetrationDepthSettings_Impl.hpp"
#include "ModelObject/MaterialPropertyPhaseChange_Impl.hpp"
#include "ModelObject/MaterialPropertyPhaseChangeHysteresis_Impl.hpp"
#include "ModelObject/MaterialPropertyVariableAbsorptance_Impl.hpp"
#include "ModelObject/MaterialPropertyVariableThermalConductivity_Impl.hpp"
#include "StraightComponent/CoilCoolingDX_Impl.hpp"
#include "StraightComponent/CoilHeatingDXMultiSpeed_Impl.hpp"
#include "StraightComponent/CoilHeatingDXSingleSpeed_Impl.hpp"
#include "StraightComponent/CoilHeatingDXVariableSpeed_Impl.hpp"
#include "StraightComponent/CoilHeatingDesuperheater_Impl.hpp"
#include "StraightComponent/CoilWaterHeatingDesuperheater_Impl.hpp"
#include "StraightComponent/CoilHeatingElectric_Impl.hpp"
#include "StraightComponent/CoilHeatingElectricMultiStage_Impl.hpp"
#include "StraightComponent/CoilHeatingGasMultiStage_Impl.hpp"
#include "ModelObject/CoilHeatingSteam_Impl.hpp"
#include "ModelObject/CoilWaterHeatingAirToWaterHeatPumpWrapped_Impl.hpp"
#include "HVACComponent/CoilWaterHeatingAirToWaterHeatPump_Impl.hpp"
#include "StraightComponent/CoilHeatingGas_Impl.hpp"
#include "ModelObject/CoilSystemCoolingDX_Impl.hpp"
#include "ModelObject/CoilSystemHeatingDX_Impl.hpp"
#include "StraightComponent/CoilSystemCoolingDXHeatExchangerAssisted_Impl.hpp"
#include "StraightComponent/CoilSystemIntegratedHeatPumpAirSource_Impl.hpp"
#include "StraightComponent/CoilSystemCoolingWater_Impl.hpp"
#include "StraightComponent/CoilSystemCoolingWaterHeatExchangerAssisted_Impl.hpp"
#include "ModelObject/ControllerMechanicalVentilation_Impl.hpp"
#include "ParentObject/ControllerOutdoorAir_Impl.hpp"
#include "ParentObject/ZoneHVACEnergyRecoveryVentilatorController_Impl.hpp"
#include "ParentObject/SimulationControl_Impl.hpp"
#include "ModelObject/Timestep_Impl.hpp"
#include "ResourceObject/DesignSpecificationOutdoorAir_Impl.hpp"
#include "ModelObject/DesignSpecificationOutdoorAirSpaceList_Impl.hpp"
#include "StraightComponent/FanConstantVolume_Impl.hpp"
#include "StraightComponent/FanComponentModel_Impl.hpp"
#include "StraightComponent/FanOnOff_Impl.hpp"
#include "StraightComponent/FanSystemModel_Impl.hpp"
#include "StraightComponent/FanVariableVolume_Impl.hpp"
#include "ZoneHVACComponent/FanZoneExhaust_Impl.hpp"
#include "ZoneHVACComponent/WaterHeaterHeatPump_Impl.hpp"
#include "ZoneHVACComponent/WaterHeaterHeatPumpWrappedCondenser_Impl.hpp"
#include "ModelObject_Impl.hpp"
#include "StraightComponent/AirConditionerVariableRefrigerantFlow_Impl.hpp"
#include "StraightComponent/RefrigerationCompressorRack_Impl.hpp"
#include "StraightComponent/RefrigerationCondenserWaterCooled_Impl.hpp"
#include "StraightComponent/SolarCollectorFlatPlatePhotovoltaicThermal_Impl.hpp"
#include "StraightComponent/SolarCollectorFlatPlateWater_Impl.hpp"
#include "StraightComponent/SolarCollectorIntegralCollectorStorage_Impl.hpp"
#include "ModelObject/SolarCollectorPerformanceFlatPlate_Impl.hpp"
#include "ModelObject/SolarCollectorPerformanceIntegralCollectorStorage_Impl.hpp"
#include "ModelObject/SolarCollectorPerformancePhotovoltaicThermalBIPVT_Impl.hpp"
#include "ModelObject/SolarCollectorPerformancePhotovoltaicThermalSimple_Impl.hpp"
#include "ModelObject/SolarCollectorUnglazedTranspired_Impl.hpp"
#include "ModelObject/SolarCollectorUnglazedTranspiredMultisystem_Impl.hpp"
#include "ModelObject/SurfaceContaminantSourceAndSinkGenericBoundaryLayerDiffusion_Impl.hpp"
#include "ModelObject/SurfaceContaminantSourceAndSinkGenericDepositionVelocitySink_Impl.hpp"
#include "ModelObject/SurfaceContaminantSourceAndSinkGenericPressureDriven_Impl.hpp"
#include "ModelObject/SurfaceControlMovableInsulation_Impl.hpp"
#include "ModelObject/SurfacePropertiesVaporCoefficients_Impl.hpp"
#include "StraightComponent/LoadProfilePlant_Impl.hpp"
#include "StraightComponent/PlantComponentTemperatureSource_Impl.hpp"
#include "StraightComponent/PlantComponentUserDefined_Impl.hpp"
#include "StraightComponent/HeatPumpAirToWater_Impl.hpp"
#include "StraightComponent/HeatPumpAirToWaterFuelFiredCooling_Impl.hpp"
#include "StraightComponent/HeatPumpAirToWaterFuelFiredHeating_Impl.hpp"
#include "StraightComponent/TemperingValve_Impl.hpp"
#include "StraightComponent/WaterUseConnections_Impl.hpp"
#include "StraightComponent/ThermalStorageIceDetailed_Impl.hpp"
#include "HVACComponent/AirConditionerVariableRefrigerantFlowFluidTemperatureControl_Impl.hpp"
#include "HVACComponent/AirConditionerVariableRefrigerantFlowFluidTemperatureControlHR_Impl.hpp"
#include "StraightComponent/CoilCoolingDXVariableRefrigerantFlow_Impl.hpp"
#include "StraightComponent/CoilCoolingDXVariableRefrigerantFlowFluidTemperatureControl_Impl.hpp"
#include "StraightComponent/CoilHeatingDXVariableRefrigerantFlow_Impl.hpp"
#include "StraightComponent/CoilHeatingDXVariableRefrigerantFlowFluidTemperatureControl_Impl.hpp"
#include "HVACComponent/CoilWaterHeatingAirToWaterHeatPumpVariableSpeed_Impl.hpp"
#include "HVACComponent/ControllerWaterCoil_Impl.hpp"
#include "WaterToAirComponent/CoilCoolingWater_Impl.hpp"
#include "WaterToAirComponent/CoilHeatingWater_Impl.hpp"
#include "WaterToAirComponent/CoilCoolingWaterToAirHeatPumpEquationFit_Impl.hpp"
#include "WaterToAirComponent/CoilHeatingWaterToAirHeatPumpEquationFit_Impl.hpp"
#include "WaterToAirComponent/CoilCoolingWaterToAirHeatPumpVariableSpeedEquationFit_Impl.hpp"
#include "WaterToAirComponent/CoilHeatingWaterToAirHeatPumpVariableSpeedEquationFit_Impl.hpp"
#include "WaterToAirComponent/CoilUserDefined_Impl.hpp"
#include "ModelObject/CoilCoolingWaterToAirHeatPumpParameterEstimation_Impl.hpp"
#include "ModelObject/CoilHeatingWaterToAirHeatPumpParameterEstimation_Impl.hpp"
#include "ModelObject/CoilCoolingWaterDetailedGeometry_Impl.hpp"
#include "ModelObject/CoilDXASHRAE205Performance_Impl.hpp"
#include "WaterToWaterComponent/CentralHeatPumpSystem_Impl.hpp"
#include "WaterToWaterComponent/HeatPumpPlantLoopEIRCooling_Impl.hpp"
#include "WaterToWaterComponent/HeatPumpPlantLoopEIRHeating_Impl.hpp"
#include "WaterToWaterComponent/HeatPumpWaterToWaterEquationFitCooling_Impl.hpp"
#include "WaterToWaterComponent/HeatPumpWaterToWaterEquationFitHeating_Impl.hpp"
#include "ModelObject/HeatPumpWaterToWaterParameterEstimationCooling_Impl.hpp"
#include "ModelObject/HeatPumpWaterToWaterParameterEstimationHeating_Impl.hpp"
#include "WaterToWaterComponent/HeatExchangerFluidToFluid_Impl.hpp"
#include "WaterToWaterComponent/WaterHeaterMixed_Impl.hpp"
#include "ModelObject/AirflowNetworkDistributionComponentCoil_Impl.hpp"
#include "ModelObject/AirflowNetworkDistributionComponentConstantPressureDrop_Impl.hpp"
#include "ModelObject/CeilingAdiabatic_Impl.hpp"
#include "ModelObject/CeilingInterzone_Impl.hpp"
#include "ModelObject/Roof_Impl.hpp"
#include "ModelObject/RoofIrrigation_Impl.hpp"
#include "ModelObject/RoofCeilingDetailed_Impl.hpp"
#include "ModelObject/WallAdiabatic_Impl.hpp"
#include "ModelObject/WallDetailed_Impl.hpp"
#include "ModelObject/WallExterior_Impl.hpp"
#include "ModelObject/WallInterzone_Impl.hpp"
#include "ModelObject/WallUnderground_Impl.hpp"
#include "ModelObject/Door_Impl.hpp"
#include "ModelObject/DoorInterzone_Impl.hpp"
#include "ModelObject/GlazedDoor_Impl.hpp"
#include "ModelObject/GlazedDoorInterzone_Impl.hpp"
#include "ModelObject/WindowInterzone_Impl.hpp"
#include "ModelObject/WindowGapDeflectionState_Impl.hpp"
#include "ModelObject/WindowGapSupportPillar_Impl.hpp"
#include "ModelObject/WindowPropertyAirflowControl_Impl.hpp"
#include "ModelObject/WindowPropertyStormWindow_Impl.hpp"
#include "ModelObject/WindowThermalModelParams_Impl.hpp"
#include "ModelObject/WindowsCalculationEngine_Impl.hpp"
#include "ModelObject/ComfortViewFactorAngles_Impl.hpp"
#include "ModelObject/ComplexFenestrationPropertySolarAbsorbedLayers_Impl.hpp"
#include "ModelObject/ConstructionComplexFenestrationState_Impl.hpp"
#include "ModelObject/ComplianceBuilding_Impl.hpp"
#include "ModelObject/ShadingBuilding_Impl.hpp"
#include "ModelObject/ShadingBuildingDetailed_Impl.hpp"
#include "ModelObject/ShadingFin_Impl.hpp"
#include "ModelObject/ShadingFinProjection_Impl.hpp"
#include "ModelObject/ShadingOverhang_Impl.hpp"
#include "ModelObject/ShadingOverhangProjection_Impl.hpp"
#include "ModelObject/ShadingSite_Impl.hpp"
#include "ModelObject/ShadingSiteDetailed_Impl.hpp"
#include "ModelObject/ShadingZoneDetailed_Impl.hpp"
#include "ModelObject/ShadingPropertyReflectance_Impl.hpp"
#include "ShadingMaterial/Blind_Impl.hpp"
#include "ShadingMaterial/Shade_Impl.hpp"
#include "ShadingMaterial/Screen_Impl.hpp"
#include "ModelObject/WindowMaterialBlindEquivalentLayer_Impl.hpp"
#include "ModelObject/WindowMaterialComplexShade_Impl.hpp"
#include "ModelObject/WindowMaterialDrapeEquivalentLayer_Impl.hpp"
#include "ModelObject/WindowMaterialGap_Impl.hpp"
#include "ModelObject/WindowMaterialGapEquivalentLayer_Impl.hpp"
#include "ModelObject/WindowMaterialGlazingEquivalentLayer_Impl.hpp"
#include "ModelObject/WindowMaterialShadeEquivalentLayer_Impl.hpp"
#include "ModelObject/WindowMaterialScreenEquivalentLayer_Impl.hpp"
#include "GasLayer/Gas_Impl.hpp"
#include "GasLayer/GasMixture_Impl.hpp"
#include "ModelObject/ShadowCalculation_Impl.hpp"
#include "ModelObject/ComponentCostLineItem_Impl.hpp"
#include "ModelObject/ComponentCostReference_Impl.hpp"
#include "ModelObject/LifeCycleCost_Impl.hpp"
#include "ModelObject/LifeCycleCostUseAdjustment_Impl.hpp"
#include "ModelObject/CondenserLoop_Impl.hpp"
#include "ModelObject/CondenserEquipmentList_Impl.hpp"
#include "ModelObject/CondenserEquipmentOperationSchemes_Impl.hpp"
#include "ModelObject/ConvergenceLimits_Impl.hpp"
#include "ModelObject/PerformancePrecisionTradeoffs_Impl.hpp"
#include "ModelObject/HeatBalanceAlgorithm_Impl.hpp"
#include "ModelObject/HybridModelZone_Impl.hpp"
#include "ModelObject/IndoorLivingWall_Impl.hpp"
#include "AirToAirComponent/HeatExchangerAirToAirSensibleAndLatent_Impl.hpp"
#include "AirToAirComponent/HeatExchangerDesiccantBalancedFlow_Impl.hpp"
#include "ModelObject/HeatBalanceSettingsConductionFiniteDifference_Impl.hpp"
#include "ModelObject/HVACTemplatePlantBoiler_Impl.hpp"
#include "ModelObject/HVACTemplatePlantBoilerObjectReference_Impl.hpp"
#include "ModelObject/HVACTemplatePlantChilledWaterLoop_Impl.hpp"
#include "ModelObject/HVACTemplatePlantChiller_Impl.hpp"
#include "ModelObject/HVACTemplatePlantChillerObjectReference_Impl.hpp"
#include "ModelObject/HVACTemplatePlantHotWaterLoop_Impl.hpp"
#include "ModelObject/HVACTemplatePlantMixedWaterLoop_Impl.hpp"
#include "ModelObject/HVACTemplatePlantTower_Impl.hpp"
#include "ModelObject/HVACTemplatePlantTowerObjectReference_Impl.hpp"
#include "ModelObject/HVACTemplateSystemConstantVolume_Impl.hpp"
#include "ModelObject/HVACTemplateSystemDedicatedOutdoorAir_Impl.hpp"
#include "ModelObject/HVACTemplateSystemDualDuct_Impl.hpp"
#include "ModelObject/HVACTemplateSystemPackagedVAV_Impl.hpp"
#include "ModelObject/HVACTemplateSystemVAV_Impl.hpp"
#include "ModelObject/HVACTemplateSystemVRF_Impl.hpp"
#include "ModelObject/HVACTemplateThermostat_Impl.hpp"
#include "Thermostat/ThermostatSetpointDualSetpoint_Impl.hpp"
#include "ModelObject/ThermostatSetpointSingleHeatingOrCooling_Impl.hpp"
#include "ModelObject/ThermostatSetpointThermalComfortFangerDualSetpoint_Impl.hpp"
#include "ModelObject/ThermostatSetpointThermalComfortFangerSingleCooling_Impl.hpp"
#include "ModelObject/ThermostatSetpointThermalComfortFangerSingleHeating_Impl.hpp"
#include "ModelObject/ThermostatSetpointThermalComfortFangerSingleHeatingOrCooling_Impl.hpp"
#include "ModelObject/HVACTemplateZoneBaseboardHeat_Impl.hpp"
#include "ModelObject/HVACTemplateZoneConstantVolume_Impl.hpp"
#include "ModelObject/HVACTemplateZoneDualDuct_Impl.hpp"
#include "ModelObject/HVACTemplateZoneFanCoil_Impl.hpp"
#include "ModelObject/HVACTemplateZonePTAC_Impl.hpp"
#include "ModelObject/HVACTemplateZonePTHP_Impl.hpp"
#include "ModelObject/HVACTemplateZoneWaterToAirHeatPump_Impl.hpp"
#include "ModelObject/HVACTemplateZoneVAV_Impl.hpp"
#include "ModelObject/HVACTemplateZoneVAVHeatAndCool_Impl.hpp"
#include "ModelObject/HVACTemplateZoneVAVFanPowered_Impl.hpp"
#include "ModelObject/HVACTemplateZoneVRF_Impl.hpp"
#include "ModelObject/HVACTemplateZoneUnitary_Impl.hpp"
#include "ModelObject/HVACTemplateSystemUnitaryHeatPumpAirToAir_Impl.hpp"
#include "ModelObject/HVACTemplateSystemUnitarySystem_Impl.hpp"
#include "ModelObject/HVACTemplateSystemUnitary_Impl.hpp"
#include "ModelObject/HVACSystemRootFindingAlgorithm_Impl.hpp"
#include "ModelObject/InsideSurfaceConvectionAlgorithm_Impl.hpp"
#include "ModelObject/OutsideSurfaceConvectionAlgorithm_Impl.hpp"
#include "ModelObject/SurfaceConvectionAlgorithmInsideAdaptiveModelSelections_Impl.hpp"
#include "ModelObject/SurfaceConvectionAlgorithmOutsideAdaptiveModelSelections_Impl.hpp"
#include "ModelObject/SurfaceConvectionAlgorithmInsideUserCurve_Impl.hpp"
#include "ModelObject/SurfaceConvectionAlgorithmOutsideUserCurve_Impl.hpp"
#include "ModelObject/SurfacePropertyConvectionCoefficients_Impl.hpp"
#include "ModelObject/SurfacePropertyConvectionCoefficientsMultipleSurface_Impl.hpp"
#include "ModelObject/SurfacePropertyExposedFoundationPerimeter_Impl.hpp"
#include "ModelObject/SurfacePropertyExteriorNaturalVentedCavity_Impl.hpp"
#include "ModelObject/SurfacePropertyGroundSurfaces_Impl.hpp"
#include "ModelObject/SurfacePropertyHeatBalanceSourceTerm_Impl.hpp"
#include "ModelObject/SurfacePropertyIncidentSolarMultiplier_Impl.hpp"
#include "ModelObject/SurfacePropertyHeatTransferAlgorithm_Impl.hpp"
#include "ModelObject/SurfacePropertyHeatTransferAlgorithmConstruction_Impl.hpp"
#include "ModelObject/SurfacePropertyHeatTransferAlgorithmMultipleSurface_Impl.hpp"
#include "ModelObject/SurfacePropertyHeatTransferAlgorithmSurfaceList_Impl.hpp"
#include "ModelObject/SurfacePropertySolarIncidentInside_Impl.hpp"
#include "ModelObject/SurfacePropertySurroundingSurfaces_Impl.hpp"
#include "ModelObject/SurfacePropertyUnderwater_Impl.hpp"
#include "ResourceObject/SurfacePropertyOtherSideCoefficients_Impl.hpp"
#include "ResourceObject/SurfacePropertyOtherSideConditionsModel_Impl.hpp"
#include "ModelObject/GlobalGeometryRules_Impl.hpp"
#include "ModelObject/GeometryTransform_Impl.hpp"
#include "ModelObject/DaylightingDeviceLightWell_Impl.hpp"
#include "ModelObject/DaylightingDeviceShelf_Impl.hpp"
#include "ModelObject/DaylightingDeviceTubular_Impl.hpp"
#include "ModelObject/DaylightingDELightComplexFenestration_Impl.hpp"
#include "ModelObject/DehumidifierDesiccantNoFans_Impl.hpp"
#include "ModelObject/DehumidifierDesiccantSystem_Impl.hpp"
#include "Curve/CurveBicubic_Impl.hpp"
#include "Curve/CurveCubic_Impl.hpp"
#include "Curve/CurveBiquadratic_Impl.hpp"
#include "Curve/CurveExponent_Impl.hpp"
#include "Curve/CurveDoubleExponentialDecay_Impl.hpp"
#include "Curve/CurveExponentialDecay_Impl.hpp"
#include "Curve/CurveExponentialSkewNormal_Impl.hpp"
#include "Curve/CurveFanPressureRise_Impl.hpp"
#include "Curve/CurveFunctionalPressureDrop_Impl.hpp"
#include "Curve/CurveLinear_Impl.hpp"
#include "Curve/CurveQuadLinear_Impl.hpp"
#include "Curve/CurveQuintLinear_Impl.hpp"
#include "Curve/CurveRectangularHyperbola1_Impl.hpp"
#include "Curve/CurveRectangularHyperbola2_Impl.hpp"
#include "Curve/CurveSigmoid_Impl.hpp"
#include "Curve/CurveTriquadratic_Impl.hpp"
#include "Curve/CurveQuadratic_Impl.hpp"
#include "Curve/CurveQuartic_Impl.hpp"
#include "Curve/CurveQuadraticLinear_Impl.hpp"
#include "Curve/TableLookup_Impl.hpp"
#include "Curve/CurveCubicLinear_Impl.hpp"
#include "Curve/CurveChillerPartLoadWithLift_Impl.hpp"
#include "ModelObject/AirflowNetworkDistributionComponentDuct_Impl.hpp"
#include "ModelObject/AirflowNetworkDistributionDuctSizing_Impl.hpp"
#include "ModelObject/AirflowNetworkDistributionDuctViewFactors_Impl.hpp"
#include "AirflowNetworkLinkage/AirflowNetworkDistributionLinkage_Impl.hpp"
#include "AirflowNetworkNode/AirflowNetworkDistributionNode_Impl.hpp"
#include "ModelObject/AirflowNetworkIntraZoneNode_Impl.hpp"
#include "ModelObject/AirflowNetworkIntraZoneLinkage_Impl.hpp"
#include "ModelObject/AirflowNetworkMultiZoneExternalNode_Impl.hpp"
#include "ModelObject/AirflowNetworkMultiZoneZone_Impl.hpp"
#include "ModelObject/AirflowNetworkMultiZoneSpecifiedFlowRate_Impl.hpp"
#include "ModelObject/AirflowNetworkMultiZoneReferenceCrackConditions_Impl.hpp"
#include "ModelObject/AirflowNetworkMultiZoneWindPressureCoefficientArray_Impl.hpp"
#include "ModelObject/AirflowNetworkMultiZoneWindPressureCoefficientValues_Impl.hpp"
#include "ModelObject/AirflowNetworkMultiZoneSurface_Impl.hpp"
#include "ModelObject/AirflowNetworkMultiZoneSurfaceCrack_Impl.hpp"
#include "ModelObject/AirflowNetworkMultiZoneSurfaceEffectiveLeakageArea_Impl.hpp"
#include "ModelObject/AirflowNetworkMultiZoneComponentDetailedOpening_Impl.hpp"
#include "ModelObject/AirflowNetworkMultiZoneComponentHorizontalOpening_Impl.hpp"
#include "ModelObject/AirflowNetworkMultiZoneComponentSimpleOpening_Impl.hpp"
#include "ModelObject/AirflowNetworkMultiZoneComponentZoneExhaustFan_Impl.hpp"
#include "ModelObject/AirflowNetworkOccupantVentilationControl_Impl.hpp"
#include "ParentObject/AirflowNetworkSimulationControl_Impl.hpp"
#include "ModelObject/AirflowNetworkZoneControlPressureController_Impl.hpp"
#include "ModelObject/AirflowNetworkDistributionComponentFan_Impl.hpp"
#include "ModelObject/AirflowNetworkDistributionComponentHeatExchanger_Impl.hpp"
#include "ModelObject/AirflowNetworkDistributionComponentLeak_Impl.hpp"
#include "ModelObject/AirflowNetworkDistributionComponentLeakageRatio_Impl.hpp"
#include "ModelObject/AirflowNetworkDistributionComponentOutdoorAirFlow_Impl.hpp"
#include "ModelObject/AirflowNetworkDistributionComponentReliefAirFlow_Impl.hpp"
#include "ModelObject/AirflowNetworkDistributionComponentTerminalUnit_Impl.hpp"
#include "ModelObject/AirLoopHVACDedicatedOutdoorAirSystem_Impl.hpp"
#include "PlantEquipmentOperationScheme/PlantEquipmentOperationChillerHeaterChangeover_Impl.hpp"
#include "PlantEquipmentOperationScheme/PlantEquipmentOperationComponentSetpoint_Impl.hpp"
#include "PlantEquipmentOperationScheme/PlantEquipmentOperationThermalEnergyStorage_Impl.hpp"
#include "ModelObject/PlantEquipmentOperationSchemes_Impl.hpp"
#include "PlantEquipmentOperationScheme/PlantEquipmentOperationCoolingLoad_Impl.hpp"
#include "PlantEquipmentOperationScheme/PlantEquipmentOperationHeatingLoad_Impl.hpp"
#include "PlantEquipmentOperationScheme/PlantEquipmentOperationOutdoorDewpoint_Impl.hpp"
#include "PlantEquipmentOperationScheme/PlantEquipmentOperationOutdoorDewpointDifference_Impl.hpp"
#include "PlantEquipmentOperationScheme/PlantEquipmentOperationOutdoorDryBulbDifference_Impl.hpp"
#include "PlantEquipmentOperationScheme/PlantEquipmentOperationOutdoorWetBulbDifference_Impl.hpp"
#include "PlantEquipmentOperationScheme/PlantEquipmentOperationOutdoorDryBulb_Impl.hpp"
#include "PlantEquipmentOperationScheme/PlantEquipmentOperationOutdoorRelativeHumidity_Impl.hpp"
#include "PlantEquipmentOperationScheme/PlantEquipmentOperationOutdoorWetBulb_Impl.hpp"
#include "SpaceLoad/SpaceInfiltrationDesignFlowRate_Impl.hpp"
#include "SpaceLoad/SpaceInfiltrationFlowCoefficient_Impl.hpp"
#include "SpaceLoad/SpaceInfiltrationEffectiveLeakageArea_Impl.hpp"
#include "ModelObject/ZoneCapacitanceMultiplierResearchSpecial_Impl.hpp"
#include "ModelObject/ZoneAirBalanceOutdoorAir_Impl.hpp"
#include "ModelObject/ZoneAirContaminantBalance_Impl.hpp"
#include "ModelObject/ZoneAirHeatBalanceAlgorithm_Impl.hpp"
#include "ModelObject/ZoneAirMassFlowConservation_Impl.hpp"
#include "ModelObject/ZoneCoolTowerShower_Impl.hpp"
#include "ModelObject/ZoneCrossMixing_Impl.hpp"
#include "ModelObject/ZoneMixing_Impl.hpp"
#include "ModelObject/ZoneRefrigerationDoorMixing_Impl.hpp"
#include "ModelObject/ZoneThermalChimney_Impl.hpp"
#include "ModelObject/ZonePropertyLocalEnvironment_Impl.hpp"
#include "ModelObject/ZonePropertyUserViewFactorsBySurfaceName_Impl.hpp"
#include "ModelObject/ZoneEarthtube_Impl.hpp"
#include "ModelObject/ZoneEarthtubeParameters_Impl.hpp"
#include "ModelObject/ZoneGroup_Impl.hpp"
#include "ModelObject/ZoneEarthtubeParameters.hpp"
#include "ModelObject/ZoneControlContaminantController_Impl.hpp"
#include "ModelObject/ZoneControlHumidistat_Impl.hpp"
#include "ModelObject/ZoneControlThermostatOperativeTemperature_Impl.hpp"
#include "ModelObject/ZoneControlThermostatTemperatureAndHumidity_Impl.hpp"
#include "ModelObject/ZoneControlThermostatThermalComfort_Impl.hpp"
#include "Thermostat/ZoneControlThermostatStagedDualSetpoint_Impl.hpp"
#include "ModelObject/ZoneContaminantSourceAndSinkCarbonDioxide_Impl.hpp"
#include "ModelObject/ZoneContaminantSourceAndSinkGenericConstant_Impl.hpp"
#include "ModelObject/ZoneContaminantSourceAndSinkGenericCutoffModel_Impl.hpp"
#include "ModelObject/ZoneContaminantSourceAndSinkGenericDecaySource_Impl.hpp"
#include "ModelObject/ZoneContaminantSourceAndSinkGenericDepositionRateSink_Impl.hpp"
#include "ModelObject/ZoneBaseboardOutdoorTemperatureControlled_Impl.hpp"
#include "ModelObject/WaterHeaterSizing_Impl.hpp"
#include "ModelObject/WaterUseRainCollector_Impl.hpp"
#include "ModelObject/WaterUseStorage_Impl.hpp"
#include "ModelObject/WaterUseWell_Impl.hpp"
#include "ModelObject/UtilityCostChargeBlock_Impl.hpp"
#include "ModelObject/UtilityCostChargeSimple_Impl.hpp"
#include "ModelObject/UtilityCostComputation_Impl.hpp"
#include "ModelObject/UtilityCostComputation.hpp"
#include "ModelObject/UtilityCostQualify_Impl.hpp"
#include "ModelObject/UtilityCostQualify.hpp"
#include "ModelObject/UtilityCostRatchet_Impl.hpp"
#include "ModelObject/UtilityCostRatchet.hpp"
#include "ModelObject/UtilityCostTariff_Impl.hpp"
#include "ModelObject/UtilityCostTariff.hpp"
#include "ModelObject/UtilityCostVariable_Impl.hpp"
#include "ModelObject/UtilityCostVariable.hpp"
#include "ModelObject/DemandManagerElectricEquipment_Impl.hpp"
#include "ModelObject/DemandManagerExteriorLights_Impl.hpp"
#include "ExteriorLoadInstance/ExteriorLights_Impl.hpp"
#include "ExteriorLoadInstance/ExteriorFuelEquipment_Impl.hpp"
#include "ExteriorLoadInstance/ExteriorWaterEquipment_Impl.hpp"
#include "ModelObject/ExternalInterface_Impl.hpp"
#include "ModelObject/ExternalInterfaceActuator_Impl.hpp"
#include "ModelObject/ExternalInterfaceVariable_Impl.hpp"
#include "ModelObject/ExternalInterfaceFunctionalMockupUnitImport_Impl.hpp"
#include "ModelObject/ExternalInterfaceFunctionalMockupUnitImportFromVariable_Impl.hpp"
#include "ModelObject/ExternalInterfaceFunctionalMockupUnitImportToActuator_Impl.hpp"
#include "ModelObject/ExternalInterfaceFunctionalMockupUnitImportToVariable_Impl.hpp"
#include "ModelObject/ExternalInterfaceFunctionalMockupUnitExportFromVariable_Impl.hpp"
#include "ModelObject/ExternalInterfaceFunctionalMockupUnitExportToActuator_Impl.hpp"
#include "ModelObject/ExternalInterfaceFunctionalMockupUnitExportToVariable_Impl.hpp"
#include "Schedule/ExternalInterfaceFunctionalMockupUnitImportToSchedule_Impl.hpp"
#include "Schedule/ExternalInterfaceFunctionalMockupUnitExportToSchedule_Impl.hpp"
#include "Schedule/ExternalInterfaceSchedule_Impl.hpp"
#include "Schedule/ScheduleCompact_Impl.hpp"
#include "Schedule/ScheduleConstant_Impl.hpp"
#include "Schedule/ScheduleYear_Impl.hpp"
#include "ScheduleBase/ScheduleDay_Impl.hpp"
#include "ScheduleInterval/ScheduleFile_Impl.hpp"
#include "ModelObject/ScheduleFileShading_Impl.hpp"
#include "ModelObject/ScheduleDayList_Impl.hpp"
#include "ModelObject/ScheduleDayHourly_Impl.hpp"
#include "ModelObject/ScheduleWeekCompact_Impl.hpp"
#include "ResourceObject/ScheduleTypeLimits_Impl.hpp"
#include "ResourceObject/ScheduleWeek_Impl.hpp"
#include "ResourceObject/SpaceType_Impl.hpp"
#include "ResourceObject/TableIndependentVariable_Impl.hpp"
#include "ModelObject/DemandManagerLights_Impl.hpp"
#include "ModelObject/DemandManagerThermostats_Impl.hpp"
#include "ModelObject/DemandManagerVentilation_Impl.hpp"
#include "ModelObject/DemandManagerAssignmentList_Impl.hpp"
#include "ModelObject/MatrixTwoDimension_Impl.hpp"
#include "SpaceLoadInstance/ElectricEquipment_Impl.hpp"
#include "SpaceLoadInstance/ElectricEquipmentITEAirCooled_Impl.hpp"
#include "SpaceLoadInstance/GasEquipment_Impl.hpp"
#include "SpaceLoadInstance/HotWaterEquipment_Impl.hpp"
#include "SpaceLoadInstance/SteamEquipment_Impl.hpp"
#include "SpaceLoadInstance/OtherEquipment_Impl.hpp"
#include "SpaceLoadInstance/Lights_Impl.hpp"
#include "SpaceLoadInstance/People_Impl.hpp"
#include "SpaceLoadInstance/WaterUseEquipment_Impl.hpp"
#include "OpaqueMaterial/StandardOpaqueMaterial_Impl.hpp"
#include "OpaqueMaterial/AirGap_Impl.hpp"
#include "OpaqueMaterial/MasslessOpaqueMaterial_Impl.hpp"
#include "OpaqueMaterial/RoofVegetation_Impl.hpp"
#include "ModelObject/HeatExchangerAirToAirFlatPlate_Impl.hpp"
#include "ModelObject/DesignSpecificationAirTerminalSizing_Impl.hpp"
#include "ModelObject/DesignSpecificationZoneHVACSizing_Impl.hpp"
#include "ModelObject/AirLoopHVACExhaustSystem_Impl.hpp"
#include "ModelObject/AirLoopHVACMixer_Impl.hpp"
#include "ModelObject/PumpVariableSpeedCondensate_Impl.hpp"
#include "ModelObject/AirLoopHVACSplitter_Impl.hpp"
#include "PlantEquipmentOperationScheme/PlantEquipmentOperationUncontrolled_Impl.hpp"
#include "PlantEquipmentOperationScheme/PlantEquipmentOperationUserDefined_Impl.hpp"
#include "ModelObject/SpaceHVACZoneReturnMixer_Impl.hpp"
#include "ModelObject/GroundHeatTransferControl_Impl.hpp"
#include "ModelObject/GroundHeatTransferBasementAutoGrid_Impl.hpp"
#include "ModelObject/GroundHeatTransferBasementBldgData_Impl.hpp"
#include "ModelObject/GroundHeatTransferBasementComBldg_Impl.hpp"
#include "ModelObject/GroundHeatTransferBasementEquivAutoGrid_Impl.hpp"
#include "ModelObject/GroundHeatTransferBasementMatlProps_Impl.hpp"
#include "ModelObject/GroundHeatTransferBasementInsulation_Impl.hpp"
#include "ModelObject/GroundHeatTransferBasementManualGrid_Impl.hpp"
#include "ModelObject/GroundHeatTransferBasementSimParameters_Impl.hpp"
#include "ModelObject/GroundHeatTransferBasementSurfaceProps_Impl.hpp"
#include "ModelObject/GroundHeatTransferBasementXFACE_Impl.hpp"
#include "ModelObject/GroundHeatTransferBasementYFACE_Impl.hpp"
#include "ModelObject/GroundHeatTransferBasementZFACE_Impl.hpp"
#include "ModelObject/GroundHeatTransferSlabAutoGrid_Impl.hpp"
#include "ModelObject/GroundHeatTransferSlabManualGrid_Impl.hpp"
#include "ModelObject/GroundHeatTransferSlabBoundConds_Impl.hpp"
#include "ModelObject/GroundHeatTransferSlabBldgProps_Impl.hpp"
#include "ModelObject/GroundHeatTransferSlabEquivalentSlab_Impl.hpp"
#include "ModelObject/GroundHeatTransferSlabMaterials_Impl.hpp"
#include "ModelObject/GroundHeatTransferSlabMatlProps_Impl.hpp"
#include "ModelObject/GroundHeatTransferSlabInsulation_Impl.hpp"
#include "ModelObject/GroundHeatTransferSlabXFACE_Impl.hpp"
#include "ModelObject/GroundHeatTransferSlabYFACE_Impl.hpp"
#include "ModelObject/GroundHeatTransferSlabZFACE_Impl.hpp"
#include "ModelObject/SiteGroundDomainBasement_Impl.hpp"
#include "ModelObject/SiteGroundDomainSlab_Impl.hpp"
#include "ModelObject/SiteGroundTemperatureDeep_Impl.hpp"
#include "ModelObject/SiteGroundTemperatureFCfactorMethod_Impl.hpp"
#include "ModelObject/SiteGroundTemperatureShallow_Impl.hpp"
#include "ModelObject/SiteGroundTemperatureBuildingSurface_Impl.hpp"
#include "ModelObject/SiteGroundTemperatureUndisturbedFiniteDifference_Impl.hpp"
#include "ModelObject/SiteGroundTemperatureUndisturbedKusudaAchenbach_Impl.hpp"
#include "ModelObject/SiteGroundTemperatureUndisturbedXing_Impl.hpp"
#include "ModelObject/SiteGroundReflectance_Impl.hpp"
#include "ModelObject/SiteGroundReflectanceSnowModifier_Impl.hpp"
#include "ModelObject/SiteHeightVariation_Impl.hpp"
#include "ModelObject/SitePrecipitation_Impl.hpp"
#include "ModelObject/SizingParameters_Impl.hpp"
#include "ModelObject/SiteWaterMainsTemperature_Impl.hpp"
#include "ModelObject/SiteWeatherStation_Impl.hpp"
#include "ModelObject/SiteSolarAndVisibleSpectrum_Impl.hpp"
#include "ModelObject/SiteSpectrumData_Impl.hpp"
#include "ModelObject/SkyTemperature_Impl.hpp"
#include "LayeredConstruction/Construction_Impl.hpp"
#include "LayeredConstruction/ConstructionWithInternalSource_Impl.hpp"
#include "ConstructionBase/ConstructionAirBoundary_Impl.hpp"
#include "ConstructionBase/CFactorUndergroundWallConstruction_Impl.hpp"
#include "ConstructionBase/FFactorGroundFloorConstruction_Impl.hpp"
#include "ModelObject/ConstructionWindowDataFile_Impl.hpp"
#include "ModelObject/ConstructionWindowEquivalentLayer_Impl.hpp"
#include "ModelObject/AirLoopHVACUnitaryFurnaceHeatCool_Impl.hpp"
#include "ModelObject/AirLoopHVACUnitaryFurnaceHeatOnly_Impl.hpp"
#include "ModelObject/AirLoopHVACUnitaryHeatOnly_Impl.hpp"
#include "ModelObject/AirLoopHVACUnitaryHeatCool_Impl.hpp"
#include "StraightComponent/AirLoopHVACUnitaryHeatPumpAirToAir_Impl.hpp"
#include "ModelObject/AirLoopHVACUnitaryHeatPumpWaterToAir_Impl.hpp"
#include "StraightComponent/AirLoopHVACUnitaryHeatPumpAirToAirMultiSpeed_Impl.hpp"
#include "StraightComponent/AirLoopHVACUnitaryHeatCoolVAVChangeoverBypass_Impl.hpp"
#include "ZoneHVACComponent/AirLoopHVACUnitarySystem_Impl.hpp"
#include "ZoneHVACComponent/ZoneHVACBaseboardConvectiveElectric_Impl.hpp"
#include "ZoneHVACComponent/ZoneHVACBaseboardRadiantConvectiveElectric_Impl.hpp"
#include "ZoneHVACComponent/ZoneHVACBaseboardRadiantConvectiveWater_Impl.hpp"
#include "ZoneHVACComponent/ZoneHVACCoolingPanelRadiantConvectiveWater_Impl.hpp"
#include "ZoneHVACComponent/ZoneHVACBaseboardRadiantConvectiveWaterDesign_Impl.hpp"
#include "ZoneHVACComponent/ZoneHVACBaseboardConvectiveWater_Impl.hpp"
#include "ZoneHVACComponent/ZoneHVACDehumidifierDX_Impl.hpp"
#include "ZoneHVACComponent/ZoneHVACEnergyRecoveryVentilator_Impl.hpp"
#include "ZoneHVACComponent/ZoneHVACUnitHeater_Impl.hpp"
#include "ZoneHVACComponent/ZoneHVACUnitVentilator_Impl.hpp"
#include "ZoneHVACComponent/ZoneHVACEvaporativeCoolerUnit_Impl.hpp"
#include "ZoneHVACComponent/ZoneHVACFourPipeFanCoil_Impl.hpp"
#include "ZoneHVACComponent/ZoneVentilationWindandStackOpenArea_Impl.hpp"
#include "ZoneHVACComponent/ZoneHVACHighTemperatureRadiant_Impl.hpp"
#include "ZoneHVACComponent/ZoneHVACPackagedTerminalAirConditioner_Impl.hpp"
#include "ZoneHVACComponent/ZoneHVACPackagedTerminalHeatPump_Impl.hpp"
#include "ZoneHVACComponent/ZoneHVACWaterToAirHeatPump_Impl.hpp"
#include "ZoneHVACComponent/ZoneHVACTerminalUnitVariableRefrigerantFlow_Impl.hpp"
#include "ZoneHVACComponent/ZoneHVACIdealLoadsAirSystem_Impl.hpp"
#include "ZoneHVACComponent/ZoneHVACLowTempRadiantConstFlow_Impl.hpp"
#include "ZoneHVACComponent/ZoneHVACLowTemperatureRadiantElectric_Impl.hpp"
#include "ZoneHVACComponent/ZoneHVACLowTempRadiantVarFlow_Impl.hpp"
#include "ZoneHVACComponent/RefrigerationAirChiller_Impl.hpp"
#include "ModelObject/ZoneHVACBaseboardRadiantConvectiveSteam_Impl.hpp"
#include "ModelObject/ZoneHVACBaseboardRadiantConvectiveSteamDesign_Impl.hpp"
#include "ModelObject/ZoneHVACExhaustControl_Impl.hpp"
#include "ModelObject/ZoneHVACHybridUnitaryHVAC_Impl.hpp"
#include "ModelObject/ZoneHVACForcedAirUserDefined_Impl.hpp"
#include "ModelObject/ZoneHVACOutdoorAirUnit_Impl.hpp"
#include "ModelObject/ZoneHVACOutdoorAirUnitEquipmentList_Impl.hpp"
#include "ModelObject/ZoneHVACVentilatedSlab_Impl.hpp"
#include "ModelObject/ZoneHVACWindowAirConditioner_Impl.hpp"
#include "ModelObject/FanPerformanceNightVentilation_Impl.hpp"
#include "ModelObject/FaultModelFoulingAirFilter_Impl.hpp"
#include "ModelObject/FaultModelFoulingBoiler_Impl.hpp"
#include "ModelObject/FaultModelFoulingChiller_Impl.hpp"
#include "ModelObject/FaultModelFoulingCoil_Impl.hpp"
#include "ModelObject/FaultModelFoulingCoolingTower_Impl.hpp"
#include "ModelObject/FaultModelFoulingEvaporativeCooler_Impl.hpp"
#include "ModelObject/FaultModelEnthalpySensorOffsetOutdoorAir_Impl.hpp"
#include "ModelObject/FaultModelEnthalpySensorOffsetReturnAir_Impl.hpp"
#include "ModelObject/FaultModelHumidistatOffset_Impl.hpp"
#include "ModelObject/FaultModelHumiditySensorOffsetOutdoorAir_Impl.hpp"
#include "ModelObject/FaultModelThermostatOffset_Impl.hpp"
#include "ModelObject/FaultModelTemperatureSensorOffsetChillerSupplyWater_Impl.hpp"
#include "ModelObject/FaultModelTemperatureSensorOffsetCoilSupplyAir_Impl.hpp"
#include "ModelObject/FaultModelTemperatureSensorOffsetCondenserSupplyWater_Impl.hpp"
#include "ModelObject/FaultModelTemperatureSensorOffsetOutdoorAir_Impl.hpp"
#include "ModelObject/FaultModelTemperatureSensorOffsetReturnAir_Impl.hpp"
#include "ModelObject/FloorAdiabatic_Impl.hpp"
#include "ModelObject/FloorDetailed_Impl.hpp"
#include "ModelObject/FloorGroundContact_Impl.hpp"
#include "ModelObject/FloorInterzone_Impl.hpp"
#include "Node_Impl.hpp"
#include "ModelObject/NodeList_Impl.hpp"
#include "ModelObject/OutdoorAirMixer_Impl.hpp"
#include "ModelObject/SizingPlant_Impl.hpp"
#include "ModelObject/SizingSystem_Impl.hpp"
#include "SizingPeriod/DesignDay_Impl.hpp"
#include "ModelObject/SizingPeriodWeatherFileConditionType_Impl.hpp"
#include "ModelObject/SizingPeriodWeatherFileDays_Impl.hpp"
#include "SizingZone_Impl.hpp"
#include "ModelObject/SpaceHVACEquipmentConnections_Impl.hpp"
#include "ModelObject/SpaceHVACZoneEquipmentSplitter_Impl.hpp"
#include "PlanarSurfaceGroup/Space_Impl.hpp"
#include "SetpointManager/SetpointManagerColdest_Impl.hpp"
#include "SetpointManager/SetpointManagerFollowGroundTemperature_Impl.hpp"
#include "SetpointManager/SetpointManagerFollowOutdoorAirTemperature_Impl.hpp"
#include "SetpointManager/SetpointManagerOutdoorAirPretreat_Impl.hpp"
#include "SetpointManager/SetpointManagerOutdoorAirReset_Impl.hpp"
#include "SetpointManager/SetpointManagerFollowSystemNodeTemperature_Impl.hpp"
#include "SetpointManager/SetpointManagerSystemNodeResetHumidity_Impl.hpp"
#include "SetpointManager/SetpointManagerSystemNodeResetTemperature_Impl.hpp"
#include "SetpointManager/SetpointManagerWarmest_Impl.hpp"
#include "SetpointManager/SetpointManagerWarmestTemperatureFlow_Impl.hpp"
#include "SetpointManager/SetpointManagerMultiZoneCoolingAverage_Impl.hpp"
#include "SetpointManager/SetpointManagerMultiZoneHeatingAverage_Impl.hpp"
#include "SetpointManager/SetpointManagerMultiZoneMaximumHumidityAverage_Impl.hpp"
#include "SetpointManager/SetpointManagerMultiZoneMinimumHumidityAverage_Impl.hpp"
#include "SetpointManager/SetpointManagerMultiZoneHumidityMaximum_Impl.hpp"
#include "SetpointManager/SetpointManagerMultiZoneHumidityMinimum_Impl.hpp"
#include "ModelObject/SetpointManagerCondenserEnteringReset_Impl.hpp"
#include "ModelObject/SetpointManagerCondenserEnteringResetIdeal_Impl.hpp"
#include "ModelObject/SetpointManagerReturnAirBypassFlow_Impl.hpp"
#include "ModelObject/SetpointManagerReturnTemperatureChilledWater_Impl.hpp"
#include "ModelObject/SetpointManagerReturnTemperatureHotWater_Impl.hpp"
#include "SetpointManager/SetpointManagerMixedAir_Impl.hpp"
#include "SetpointManager/SetpointManagerScheduled_Impl.hpp"
#include "SetpointManager/SetpointManagerScheduledDualSetpoint_Impl.hpp"
#include "SetpointManager/SetpointManagerSingleZoneCooling_Impl.hpp"
#include "SetpointManager/SetpointManagerSingleZoneOneStageCooling_Impl.hpp"
#include "SetpointManager/SetpointManagerSingleZoneOneStageHeating_Impl.hpp"
#include "SetpointManager/SetpointManagerSingleZoneHeating_Impl.hpp"
#include "SetpointManager/SetpointManagerSingleZoneHumidityMaximum_Impl.hpp"
#include "SetpointManager/SetpointManagerSingleZoneHumidityMinimum_Impl.hpp"
#include "SetpointManager/SetpointManagerSingleZoneReheat_Impl.hpp"
#include "ModelObject/EnergyManagementSystemCurveOrTableIndexVariable_Impl.hpp"
#include "ModelObject/GroundHeatTransferBasementInterior_Impl.hpp"
#include "ModelPartitionMaterial/InfraredTransparentMaterial_Impl.hpp"
#include "ModelObject/ParametricFileNameSuffix_Impl.hpp"
#include "ModelObject/ParametricLogic_Impl.hpp"
#include "ModelObject/ParametricRunControl_Impl.hpp"
#include "ModelObject/ParametricSetValueForRun_Impl.hpp"
#include "ResourceObject/PythonPluginInstance_Impl.hpp"
#include "ModelObject/SiteVariableLocation_Impl.hpp"
#include "ModelObject/SpaceHVACZoneEquipmentMixer_Impl.hpp"
#include "ModelObject/SurfacePropertyLocalEnvironment_Impl.hpp"
#include "ModelObject/Window_Impl.hpp"
#include "ModelObject/ZoneHVACVentilatedSlabSlabGroup_Impl.hpp"
#include "HVACComponent/ThermalZone_Impl.hpp"
#include "ModelObject/ZoneHVACAirDistributionUnit_Impl.hpp"
#include "ModelObject/ZoneHVACEquipmentConnections_Impl.hpp"
#include "ModelObject/ZoneHVACEquipmentList_Impl.hpp"

#include <utilities/idd/IddEnums.hxx>

#include "../utilities/core/Filesystem.hpp"
#include "../utilities/idf/IdfFile.hpp"
#include "../utilities/idf/IdfObject.hpp"

#include <sstream>

namespace openstudio {
namespace epmodel {

  void SanitizationReport::log() const {
    static constexpr const char* prefix = "[canonicalize] ";
    for (const auto& message : messages) {
      if (message.rfind("ERROR: ", 0) == 0) {
        LOG_FREE(Error, "openstudio.epmodel.Model", prefix << message.substr(7));
      } else if (message.rfind("WARN: ", 0) == 0) {
        LOG_FREE(Warn, "openstudio.epmodel.Model", prefix << message.substr(6));
      } else if (message.rfind("INFO: ", 0) == 0) {
        LOG_FREE(Info, "openstudio.epmodel.Model", prefix << message.substr(6));
      } else {
        LOG_FREE(Info, "openstudio.epmodel.Model", prefix << message);
      }
    }
  }

  // Creates an empty epmodel Workspace with the EnergyPlus schema and a Version object.
  // Use this when building an epmodel programmatically from scratch.
  Model::Model() : Workspace(std::shared_ptr<detail::Model_Impl>(new detail::Model_Impl())) {
    this->addVersionObject();
  }

  // Preferred import path for EnergyPlus IDF content.
  // This path calls Model_Impl::createObject(const IdfObject&, ...), which selects concrete
  // epmodel impl types by IddObjectType (for example AirLoopHVAC -> AirLoopHVAC_Impl).
  // The stored pointer type is WorkspaceObject_Impl, but the runtime type remains concrete.
  // After object ingestion, canonicalization runs with Repair policy.
  Model::Model(const openstudio::IdfFile& idfFile) : Workspace(std::shared_ptr<detail::Model_Impl>(new detail::Model_Impl(idfFile))) {
    openstudio::detail::WorkspaceObject_ImplPtrVector objectImplPtrs;
    if (auto vo = idfFile.versionObject()) {
      objectImplPtrs.push_back(getImpl<detail::Model_Impl>()->createObject(*vo, true));
    }
    for (const IdfObject& idfObject : idfFile.objects()) {
      objectImplPtrs.push_back(getImpl<detail::Model_Impl>()->createObject(idfObject, true));
    }
    getImpl<detail::Model_Impl>()->addObjects(objectImplPtrs);
    canonicalize(SanitizationPolicy::Repair);
  }

  // Converts/clones an existing Workspace into an epmodel::Model.
  // This path calls Model_Impl::createObject(const shared_ptr<WorkspaceObject_Impl>&, ...),
  // which preserves concrete runtime type when the source Workspace already contains epmodel
  // impl objects. If the source is a generic Workspace, concrete casts fail and the fallback
  // is ModelObject_Impl, so concrete epmodel queries may return fewer objects.
  // After cloning, canonicalization runs with Repair policy.
  Model::Model(const openstudio::Workspace& workspace)
    : Workspace(std::shared_ptr<detail::Model_Impl>(new detail::Model_Impl(*(workspace.getImpl<openstudio::detail::Workspace_Impl>()), true))) {
    openstudio::detail::WorkspaceObject_ImplPtrVector newObjectImplPtrs;
    HandleMap oldNewHandleMap;
    if (auto vo = workspace.versionObject()) {
      newObjectImplPtrs.push_back(getImpl<detail::Model_Impl>()->createObject(vo->getImpl<openstudio::detail::WorkspaceObject_Impl>(), true));
    }
    for (const WorkspaceObject& object : workspace.getImpl<openstudio::detail::Workspace_Impl>()->objects()) {
      newObjectImplPtrs.push_back(getImpl<detail::Model_Impl>()->createObject(object.getImpl<openstudio::detail::WorkspaceObject_Impl>(), true));
    }
    getImpl<detail::Model_Impl>()->addClones(newObjectImplPtrs, oldNewHandleMap, true);
    canonicalize(SanitizationPolicy::Repair);
  }

  // Convenience loader for disk-based IDF files.
  // Internally this delegates to the IdfFile constructor above (typed object materialization
  // plus canonicalization with Repair policy).
  boost::optional<Model> Model::load(const openstudio::path& idfPath) {
    if (!openstudio::filesystem::is_regular_file(idfPath)) {
      LOG_FREE(Warn, "openstudio.epmodel.Model", "Path is not a valid file: " << idfPath);
      return boost::none;
    }

    auto idfFile = openstudio::IdfFile::load(idfPath, openstudio::IddFileType::EnergyPlus);
    if (!idfFile) {
      LOG_FREE(Warn, "openstudio.epmodel.Model", "Failed to load idf at " << idfPath);
      return boost::none;
    }

    return Model(*idfFile);
  }

  // Internal bridge used when wrapping an already-constructed Model_Impl.
  Model::Model(std::shared_ptr<openstudio::epmodel::detail::Model_Impl> impl) : Workspace(std::move(impl)) {}

  SanitizationReport Model::canonicalize(SanitizationPolicy policy) {
    detail::LoadContext context{*this, policy, SanitizationReport{}, {}};
    if (policy == SanitizationPolicy::None) {
      return context.report;
    }

    // Fixed-point pass over all objects:
    // 1. One-time execution per object handle is enforced via context.visited.
    // 2. Order is intentionally not relied upon.
    // 3. Newly created objects from canonicalizers are picked up in later passes.
    while (true) {
      const auto visitedBefore = context.visited.size();
      for (const auto& object : this->objects()) {
        if (auto impl = object.getImpl<detail::ModelObject_Impl>()) {
          impl->canonicalize(context);
        }
      }
      if (context.visited.size() == visitedBefore) {
        break;
      }
    }

    std::ostringstream summary;
    summary << "Sanitization complete: infos=" << context.report.infoCount << ", warnings=" << context.report.warningCount
            << ", errors=" << context.report.errorCount << ".";
    detail::addLoadInfo(context, summary.str());
    return context.report;
  }

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
  namespace detail {

    void addLoadInfo(LoadContext& ctx, const std::string& message) {
      ++ctx.report.infoCount;
      ctx.report.messages.push_back("INFO: " + message);
      LOG_FREE(Info, "openstudio.epmodel.Model", message);
    }

    void addLoadWarning(LoadContext& ctx, const std::string& message) {
      ++ctx.report.warningCount;
      ctx.report.messages.push_back("WARN: " + message);
      LOG_FREE(Warn, "openstudio.epmodel.Model", message);
    }

    void addLoadError(LoadContext& ctx, const std::string& message) {
      ++ctx.report.errorCount;
      ctx.report.messages.push_back("ERROR: " + message);
      LOG_FREE(Error, "openstudio.epmodel.Model", message);
    }

    Model_Impl::Model_Impl() : Workspace_Impl(StrictnessLevel::Draft, IddFileType::EnergyPlus) {
      // careful not to call anything that calls shared_from_this here, this is not yet constructed
    }

    Model_Impl::Model_Impl(const IdfFile& idfFile) : Workspace_Impl(idfFile, StrictnessLevel(StrictnessLevel::Draft)) {
      // careful not to call anything that calls shared_from_this here, this is not yet constructed
      if (iddFileType() != IddFileType::EnergyPlus) {
        LOG_AND_THROW("epmodel::Model must be constructed with the EnergyPlus Idd as the underlying data schema. (Attempted construction "
                      << "from IdfFile with IddFileType " << idfFile.iddFileType().valueDescription() << ".)");
      }
    }

    Model_Impl::Model_Impl(const openstudio::detail::Workspace_Impl& workspace, bool keepHandles)
      : openstudio::detail::Workspace_Impl(workspace, keepHandles) {
      // careful not to call anything that calls shared_from_this here, this is not yet constructed
      if (iddFileType() != IddFileType::EnergyPlus) {
        LOG_AND_THROW("epmodel::Model must be constructed with the EnergyPlus Idd as the underlying data schema. (Attempted construction "
                      << "from Workspace with IddFileType " << workspace.iddFileType().valueDescription() << ".)");
      }
    }

    Model_Impl::Model_Impl(const Model_Impl& other, bool keepHandles) : Workspace_Impl(other, keepHandles) {}

    Model_Impl::Model_Impl(const Model_Impl& other, const std::vector<Handle>& hs, bool keepHandles, StrictnessLevel level)
      : Workspace_Impl(other, hs, keepHandles, level) {}

    std::shared_ptr<openstudio::detail::WorkspaceObject_Impl> Model_Impl::createObject(const IdfObject& object, bool keepHandle) {
      auto result = modelObjectCreator.getNew(this, object, keepHandle);
      if (!result) {
        result = std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new ModelObject_Impl(object, this, keepHandle));
      }
      return result;
    }

    std::shared_ptr<openstudio::detail::WorkspaceObject_Impl> Model_Impl::createObject(const IdfObject& object, bool keepHandle, bool isTransient) {
      auto result = createObject(object, keepHandle);
      result->setTransient(isTransient);
      return result;
    }

    std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>
      Model_Impl::createObject(const std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>& originalObjectImplPtr, bool keepHandle) {

      auto result = modelObjectCreator.getCopy(this, originalObjectImplPtr, keepHandle);
      if (!result) {
        result = std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new ModelObject_Impl(*originalObjectImplPtr, this, keepHandle));
      }

      return result;
    }

    std::shared_ptr<openstudio::detail::WorkspaceObject_Impl> detail::Model_Impl::ModelObjectCreator::getNew(Model_Impl* model, const IdfObject& obj,
                                                                                                             bool keepHandle) const {
      auto typeToCreate = obj.iddObject().type();
      std::shared_ptr<openstudio::detail::WorkspaceObject_Impl> result;
      auto it = m_newMap.find(typeToCreate);
      if (it != m_newMap.end()) {
        result = it->second(model, obj, keepHandle);
      }
      return result;
    }

    std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>
      detail::Model_Impl::ModelObjectCreator::getCopy(Model_Impl* model, const std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>& obj,
                                                      bool keepHandle) const {
      auto typeToCreate = obj->iddObject().type();
      std::shared_ptr<openstudio::detail::WorkspaceObject_Impl> result;
      auto it = m_copyMap.find(typeToCreate);
      if (it != m_copyMap.end()) {
        result = it->second(model, obj, keepHandle);
      }
      return result;
    }

    detail::Model_Impl::ModelObjectCreator::ModelObjectCreator() {
#define REGISTER_NEW_CONSTRUCTOR(_iddType, _implClass)                                                            \
  m_newMap[_iddType] = [](openstudio::epmodel::detail::Model_Impl* m, const IdfObject& object, bool keepHandle) { \
    return std::make_shared<_implClass>(object, m, keepHandle);                                                   \
  };

      REGISTER_NEW_CONSTRUCTOR(IddObjectType::AirConditioner_VariableRefrigerantFlow, AirConditionerVariableRefrigerantFlow_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::AirConditioner_VariableRefrigerantFlow_FluidTemperatureControl,
                               AirConditionerVariableRefrigerantFlowFluidTemperatureControl_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::AirConditioner_VariableRefrigerantFlow_FluidTemperatureControl_HR,
                               AirConditionerVariableRefrigerantFlowFluidTemperatureControlHR_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::AirLoopHVAC, AirLoopHVAC_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::AirLoopHVAC_ControllerList, AirLoopHVACControllerList_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::AirLoopHVAC_DedicatedOutdoorAirSystem, AirLoopHVACDedicatedOutdoorAirSystem_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::AirLoopHVAC_ExhaustSystem, AirLoopHVACExhaustSystem_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::AirLoopHVAC_Mixer, AirLoopHVACMixer_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::AirLoopHVAC_OutdoorAirSystem, AirLoopHVACOutdoorAirSystem_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::AirLoopHVAC_OutdoorAirSystem_EquipmentList, AirLoopHVACOutdoorAirSystemEquipmentList_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::AirLoopHVAC_ReturnPath, AirLoopHVACReturnPath_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::AirLoopHVAC_ReturnPlenum, AirLoopHVACReturnPlenum_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::AirLoopHVAC_Splitter, AirLoopHVACSplitter_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::AirLoopHVAC_SupplyPath, AirLoopHVACSupplyPath_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::AirLoopHVAC_SupplyPlenum, AirLoopHVACSupplyPlenum_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::AirLoopHVAC_UnitaryHeatCool, AirLoopHVACUnitaryHeatCool_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::AirLoopHVAC_UnitaryHeatCool_VAVChangeoverBypass, AirLoopHVACUnitaryHeatCoolVAVChangeoverBypass_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::AirLoopHVAC_UnitaryHeatOnly, AirLoopHVACUnitaryHeatOnly_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::AirLoopHVAC_UnitaryHeatPump_AirToAir, AirLoopHVACUnitaryHeatPumpAirToAir_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::AirLoopHVAC_UnitaryHeatPump_AirToAir_MultiSpeed, AirLoopHVACUnitaryHeatPumpAirToAirMultiSpeed_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::AirLoopHVAC_UnitaryHeatPump_WaterToAir, AirLoopHVACUnitaryHeatPumpWaterToAir_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::AirLoopHVAC_UnitarySystem, AirLoopHVACUnitarySystem_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::AirLoopHVAC_Unitary_Furnace_HeatCool, AirLoopHVACUnitaryFurnaceHeatCool_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::AirLoopHVAC_Unitary_Furnace_HeatOnly, AirLoopHVACUnitaryFurnaceHeatOnly_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::AirLoopHVAC_ZoneMixer, AirLoopHVACZoneMixer_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::AirLoopHVAC_ZoneSplitter, AirLoopHVACZoneSplitter_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::AirTerminal_DualDuct_ConstantVolume, AirTerminalDualDuctConstantVolume_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::AirTerminal_DualDuct_VAV, AirTerminalDualDuctVAV_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::AirTerminal_DualDuct_VAV_OutdoorAir, AirTerminalDualDuctVAVOutdoorAir_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::AirTerminal_SingleDuct_ConstantVolume_CooledBeam, AirTerminalSingleDuctConstantVolumeCooledBeam_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::AirTerminal_SingleDuct_ConstantVolume_FourPipeBeam,
                               AirTerminalSingleDuctConstantVolumeFourPipeBeam_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::AirTerminal_SingleDuct_ConstantVolume_FourPipeInduction,
                               AirTerminalSingleDuctConstantVolumeFourPipeInduction_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::AirTerminal_SingleDuct_ConstantVolume_NoReheat, AirTerminalSingleDuctConstantVolumeNoReheat_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::AirTerminal_SingleDuct_ConstantVolume_Reheat, AirTerminalSingleDuctConstantVolumeReheat_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::AirTerminal_SingleDuct_Mixer, AirTerminalSingleDuctInletSideMixer_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::AirTerminal_SingleDuct_ParallelPIU_Reheat, AirTerminalSingleDuctParallelPIUReheat_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::AirTerminal_SingleDuct_SeriesPIU_Reheat, AirTerminalSingleDuctSeriesPIUReheat_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::AirTerminal_SingleDuct_UserDefined, AirTerminalSingleDuctUserDefined_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::AirTerminal_SingleDuct_VAV_HeatAndCool_NoReheat, AirTerminalSingleDuctVAVHeatAndCoolNoReheat_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::AirTerminal_SingleDuct_VAV_HeatAndCool_Reheat, AirTerminalSingleDuctVAVHeatAndCoolReheat_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::AirTerminal_SingleDuct_VAV_NoReheat, AirTerminalSingleDuctVAVNoReheat_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::AirTerminal_SingleDuct_VAV_Reheat, AirTerminalSingleDuctVAVReheat_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::AirTerminal_SingleDuct_VAV_Reheat_VariableSpeedFan,
                               AirTerminalSingleDuctVAVReheatVariableSpeedFan_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::AirflowNetwork_Distribution_Component_Coil, AirflowNetworkDistributionComponentCoil_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::AirflowNetwork_Distribution_Component_ConstantPressureDrop,
                               AirflowNetworkDistributionComponentConstantPressureDrop_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::AirflowNetwork_Distribution_Component_Duct, AirflowNetworkDistributionComponentDuct_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::AirflowNetwork_Distribution_Component_Fan, AirflowNetworkDistributionComponentFan_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::AirflowNetwork_Distribution_Component_HeatExchanger,
                               AirflowNetworkDistributionComponentHeatExchanger_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::AirflowNetwork_Distribution_Component_Leak, AirflowNetworkDistributionComponentLeak_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::AirflowNetwork_Distribution_Component_LeakageRatio,
                               AirflowNetworkDistributionComponentLeakageRatio_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::AirflowNetwork_Distribution_Component_OutdoorAirFlow,
                               AirflowNetworkDistributionComponentOutdoorAirFlow_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::AirflowNetwork_Distribution_Component_ReliefAirFlow,
                               AirflowNetworkDistributionComponentReliefAirFlow_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::AirflowNetwork_Distribution_Component_TerminalUnit,
                               AirflowNetworkDistributionComponentTerminalUnit_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::AirflowNetwork_Distribution_DuctSizing, AirflowNetworkDistributionDuctSizing_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::AirflowNetwork_Distribution_DuctViewFactors, AirflowNetworkDistributionDuctViewFactors_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::AirflowNetwork_Distribution_Linkage, AirflowNetworkDistributionLinkage_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::AirflowNetwork_Distribution_Node, AirflowNetworkDistributionNode_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::AirflowNetwork_IntraZone_Linkage, AirflowNetworkIntraZoneLinkage_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::AirflowNetwork_IntraZone_Node, AirflowNetworkIntraZoneNode_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::AirflowNetwork_MultiZone_Component_DetailedOpening,
                               AirflowNetworkMultiZoneComponentDetailedOpening_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::AirflowNetwork_MultiZone_Component_HorizontalOpening,
                               AirflowNetworkMultiZoneComponentHorizontalOpening_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::AirflowNetwork_MultiZone_Component_SimpleOpening, AirflowNetworkMultiZoneComponentSimpleOpening_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::AirflowNetwork_MultiZone_Component_ZoneExhaustFan, AirflowNetworkMultiZoneComponentZoneExhaustFan_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::AirflowNetwork_MultiZone_ExternalNode, AirflowNetworkMultiZoneExternalNode_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::AirflowNetwork_MultiZone_ReferenceCrackConditions,
                               AirflowNetworkMultiZoneReferenceCrackConditions_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::AirflowNetwork_MultiZone_SpecifiedFlowRate, AirflowNetworkMultiZoneSpecifiedFlowRate_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::AirflowNetwork_MultiZone_Surface, AirflowNetworkMultiZoneSurface_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::AirflowNetwork_MultiZone_Surface_Crack, AirflowNetworkMultiZoneSurfaceCrack_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::AirflowNetwork_MultiZone_Surface_EffectiveLeakageArea,
                               AirflowNetworkMultiZoneSurfaceEffectiveLeakageArea_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::AirflowNetwork_MultiZone_WindPressureCoefficientArray,
                               AirflowNetworkMultiZoneWindPressureCoefficientArray_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::AirflowNetwork_MultiZone_WindPressureCoefficientValues,
                               AirflowNetworkMultiZoneWindPressureCoefficientValues_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::AirflowNetwork_MultiZone_Zone, AirflowNetworkMultiZoneZone_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::AirflowNetwork_OccupantVentilationControl, AirflowNetworkOccupantVentilationControl_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::AirflowNetwork_SimulationControl, AirflowNetworkSimulationControl_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::AirflowNetwork_ZoneControl_PressureController, AirflowNetworkZoneControlPressureController_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::AvailabilityManagerAssignmentList, AvailabilityManagerAssignmentList_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::AvailabilityManager_DifferentialThermostat, AvailabilityManagerDifferentialThermostat_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::AvailabilityManager_HighTemperatureTurnOff, AvailabilityManagerHighTemperatureTurnOff_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::AvailabilityManager_HighTemperatureTurnOn, AvailabilityManagerHighTemperatureTurnOn_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::AvailabilityManager_HybridVentilation, AvailabilityManagerHybridVentilation_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::AvailabilityManager_LowTemperatureTurnOff, AvailabilityManagerLowTemperatureTurnOff_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::AvailabilityManager_LowTemperatureTurnOn, AvailabilityManagerLowTemperatureTurnOn_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::AvailabilityManager_NightCycle, AvailabilityManagerNightCycle_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::AvailabilityManager_NightVentilation, AvailabilityManagerNightVentilation_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::AvailabilityManager_OptimumStart, AvailabilityManagerOptimumStart_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::AvailabilityManager_ScheduledOff, AvailabilityManagerScheduledOff_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::AvailabilityManager_ScheduledOn, AvailabilityManagerScheduledOn_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::Boiler_HotWater, BoilerHotWater_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::Boiler_Steam, BoilerSteam_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::Branch, Branch_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::BranchList, BranchList_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::Building, Building_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::BuildingSurface_Detailed, Surface_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::Ceiling_Adiabatic, CeilingAdiabatic_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::Ceiling_Interzone, CeilingInterzone_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::CentralHeatPumpSystem, CentralHeatPumpSystem_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::ChillerHeaterPerformance_Electric_EIR, ChillerHeaterPerformanceElectricEIR_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::ChillerHeater_Absorption_DirectFired, ChillerHeaterAbsorptionDirectFired_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::ChillerHeater_Absorption_DoubleEffect, ChillerHeaterAbsorptionDoubleEffect_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::Chiller_Absorption, ChillerAbsorption_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::Chiller_Absorption_Indirect, ChillerAbsorptionIndirect_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::Chiller_CombustionTurbine, ChillerCombustionTurbine_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::Chiller_ConstantCOP, ChillerConstantCOP_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::Chiller_Electric, ChillerElectric_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::Chiller_Electric_ASHRAE205, ChillerElectricASHRAE205_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::Chiller_Electric_EIR, ChillerElectricEIR_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::Chiller_Electric_ReformulatedEIR, ChillerElectricReformulatedEIR_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::Chiller_EngineDriven, ChillerEngineDriven_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::CoilPerformance_DX_Cooling, CoilPerformanceDXCooling_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::CoilSystem_Cooling_DX, CoilSystemCoolingDX_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::CoilSystem_Cooling_DX_HeatExchangerAssisted, CoilSystemCoolingDXHeatExchangerAssisted_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::CoilSystem_Cooling_Water, CoilSystemCoolingWater_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::CoilSystem_Cooling_Water_HeatExchangerAssisted, CoilSystemCoolingWaterHeatExchangerAssisted_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::CoilSystem_Heating_DX, CoilSystemHeatingDX_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::CoilSystem_IntegratedHeatPump_AirSource, CoilSystemIntegratedHeatPumpAirSource_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::Coil_Cooling_DX, CoilCoolingDX_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::Coil_Cooling_DX_CurveFit_OperatingMode, CoilCoolingDXCurveFitOperatingMode_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::Coil_Cooling_DX_CurveFit_Performance, CoilCoolingDXCurveFitPerformance_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::Coil_Cooling_DX_CurveFit_Speed, CoilCoolingDXCurveFitSpeed_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::Coil_Cooling_DX_MultiSpeed, CoilCoolingDXMultiSpeed_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::Coil_Cooling_DX_SingleSpeed, CoilCoolingDXSingleSpeed_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::Coil_Cooling_DX_SingleSpeed_ThermalStorage, CoilCoolingDXSingleSpeedThermalStorage_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::Coil_Cooling_DX_TwoSpeed, CoilCoolingDXTwoSpeed_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::Coil_Cooling_DX_TwoStageWithHumidityControlMode, CoilCoolingDXTwoStageWithHumidityControlMode_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::Coil_Cooling_DX_VariableRefrigerantFlow, CoilCoolingDXVariableRefrigerantFlow_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::Coil_Cooling_DX_VariableRefrigerantFlow_FluidTemperatureControl,
                               CoilCoolingDXVariableRefrigerantFlowFluidTemperatureControl_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::Coil_Cooling_DX_VariableSpeed, CoilCoolingDXVariableSpeed_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::Coil_Cooling_Water, CoilCoolingWater_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::Coil_Cooling_WaterToAirHeatPump_EquationFit, CoilCoolingWaterToAirHeatPumpEquationFit_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::Coil_Cooling_WaterToAirHeatPump_ParameterEstimation,
                               CoilCoolingWaterToAirHeatPumpParameterEstimation_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::Coil_Cooling_WaterToAirHeatPump_VariableSpeedEquationFit,
                               CoilCoolingWaterToAirHeatPumpVariableSpeedEquationFit_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::Coil_Cooling_Water_DetailedGeometry, CoilCoolingWaterDetailedGeometry_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::Coil_DX_ASHRAE205_Performance, CoilDXASHRAE205Performance_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::Coil_Heating_DX_MultiSpeed, CoilHeatingDXMultiSpeed_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::Coil_Heating_DX_SingleSpeed, CoilHeatingDXSingleSpeed_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::Coil_Heating_DX_VariableRefrigerantFlow, CoilHeatingDXVariableRefrigerantFlow_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::Coil_Heating_DX_VariableRefrigerantFlow_FluidTemperatureControl,
                               CoilHeatingDXVariableRefrigerantFlowFluidTemperatureControl_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::Coil_Heating_DX_VariableSpeed, CoilHeatingDXVariableSpeed_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::Coil_Heating_Desuperheater, CoilHeatingDesuperheater_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::Coil_Heating_Electric, CoilHeatingElectric_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::Coil_Heating_Electric_MultiStage, CoilHeatingElectricMultiStage_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::Coil_Heating_Fuel, CoilHeatingGas_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::Coil_Heating_Gas_MultiStage, CoilHeatingGasMultiStage_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::Coil_Heating_Steam, CoilHeatingSteam_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::Coil_Heating_Water, CoilHeatingWater_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::Coil_Heating_WaterToAirHeatPump_EquationFit, CoilHeatingWaterToAirHeatPumpEquationFit_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::Coil_Heating_WaterToAirHeatPump_ParameterEstimation,
                               CoilHeatingWaterToAirHeatPumpParameterEstimation_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::Coil_Heating_WaterToAirHeatPump_VariableSpeedEquationFit,
                               CoilHeatingWaterToAirHeatPumpVariableSpeedEquationFit_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::Coil_UserDefined, CoilUserDefined_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::Coil_WaterHeating_AirToWaterHeatPump_Pumped, CoilWaterHeatingAirToWaterHeatPump_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::Coil_WaterHeating_AirToWaterHeatPump_VariableSpeed,
                               CoilWaterHeatingAirToWaterHeatPumpVariableSpeed_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::Coil_WaterHeating_AirToWaterHeatPump_Wrapped, CoilWaterHeatingAirToWaterHeatPumpWrapped_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::Coil_WaterHeating_Desuperheater, CoilWaterHeatingDesuperheater_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::ComfortViewFactorAngles, ComfortViewFactorAngles_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::ComplexFenestrationProperty_SolarAbsorbedLayers, ComplexFenestrationPropertySolarAbsorbedLayers_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::Compliance_Building, ComplianceBuilding_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::ComponentCost_Adjustments, ComponentCostAdjustments_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::ComponentCost_LineItem, ComponentCostLineItem_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::ComponentCost_Reference, ComponentCostReference_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::CondenserEquipmentList, CondenserEquipmentList_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::CondenserEquipmentOperationSchemes, CondenserEquipmentOperationSchemes_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::CondenserLoop, CondenserLoop_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::Connector_Mixer, ConnectorMixer_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::Connector_Splitter, ConnectorSplitter_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::Construction, Construction_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::ConstructionProperty_InternalHeatSource, ConstructionWithInternalSource_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::Construction_AirBoundary, ConstructionAirBoundary_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::Construction_CfactorUndergroundWall, CFactorUndergroundWallConstruction_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::Construction_ComplexFenestrationState, ConstructionComplexFenestrationState_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::Construction_FfactorGroundFloor, FFactorGroundFloorConstruction_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::Construction_WindowDataFile, ConstructionWindowDataFile_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::Construction_WindowEquivalentLayer, ConstructionWindowEquivalentLayer_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::Controller_MechanicalVentilation, ControllerMechanicalVentilation_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::Controller_OutdoorAir, ControllerOutdoorAir_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::Controller_WaterCoil, ControllerWaterCoil_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::ConvergenceLimits, ConvergenceLimits_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::CoolingTowerPerformance_CoolTools, CoolingTowerPerformanceCoolTools_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::CoolingTowerPerformance_YorkCalc, CoolingTowerPerformanceYorkCalc_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::CoolingTower_SingleSpeed, CoolingTowerSingleSpeed_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::CoolingTower_TwoSpeed, CoolingTowerTwoSpeed_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::CoolingTower_VariableSpeed, CoolingTowerVariableSpeed_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::CoolingTower_VariableSpeed_Merkel, CoolingTowerVariableSpeedMerkel_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::CurrencyType, CurrencyType_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::Curve_Bicubic, CurveBicubic_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::Curve_Biquadratic, CurveBiquadratic_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::Curve_ChillerPartLoadWithLift, CurveChillerPartLoadWithLift_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::Curve_Cubic, CurveCubic_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::Curve_CubicLinear, CurveCubicLinear_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::Curve_DoubleExponentialDecay, CurveDoubleExponentialDecay_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::Curve_Exponent, CurveExponent_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::Curve_ExponentialDecay, CurveExponentialDecay_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::Curve_ExponentialSkewNormal, CurveExponentialSkewNormal_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::Curve_FanPressureRise, CurveFanPressureRise_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::Curve_Functional_PressureDrop, CurveFunctionalPressureDrop_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::Curve_Linear, CurveLinear_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::Curve_QuadLinear, CurveQuadLinear_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::Curve_Quadratic, CurveQuadratic_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::Curve_QuadraticLinear, CurveQuadraticLinear_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::Curve_Quartic, CurveQuartic_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::Curve_QuintLinear, CurveQuintLinear_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::Curve_RectangularHyperbola1, CurveRectangularHyperbola1_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::Curve_RectangularHyperbola2, CurveRectangularHyperbola2_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::Curve_Sigmoid, CurveSigmoid_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::Curve_Triquadratic, CurveTriquadratic_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::DaylightingDevice_LightWell, DaylightingDeviceLightWell_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::DaylightingDevice_Shelf, DaylightingDeviceShelf_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::DaylightingDevice_Tubular, DaylightingDeviceTubular_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::Daylighting_DELight_ComplexFenestration, DaylightingDELightComplexFenestration_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::Dehumidifier_Desiccant_NoFans, DehumidifierDesiccantNoFans_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::Dehumidifier_Desiccant_System, DehumidifierDesiccantSystem_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::DemandManagerAssignmentList, DemandManagerAssignmentList_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::DemandManager_ElectricEquipment, DemandManagerElectricEquipment_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::DemandManager_ExteriorLights, DemandManagerExteriorLights_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::DemandManager_Lights, DemandManagerLights_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::DemandManager_Thermostats, DemandManagerThermostats_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::DemandManager_Ventilation, DemandManagerVentilation_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::DesignSpecification_AirTerminal_Sizing, DesignSpecificationAirTerminalSizing_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::DesignSpecification_OutdoorAir, DesignSpecificationOutdoorAir_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::DesignSpecification_OutdoorAir_SpaceList, DesignSpecificationOutdoorAirSpaceList_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::DesignSpecification_ZoneHVAC_Sizing, DesignSpecificationZoneHVACSizing_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::DistrictCooling, DistrictCooling_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::DistrictHeating_Steam, DistrictHeatingSteam_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::DistrictHeating_Water, DistrictHeatingWater_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::Door, Door_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::Door_Interzone, DoorInterzone_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::Duct, Duct_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::Duct_Loss_Conduction, DuctLossConduction_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::Duct_Loss_Leakage, DuctLossLeakage_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::Duct_Loss_MakeupAir, DuctLossMakeupAir_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::ElectricEquipment, ElectricEquipment_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::ElectricEquipment_ITE_AirCooled, ElectricEquipmentITEAirCooled_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::ElectricLoadCenter_Distribution, ElectricLoadCenterDistribution_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::ElectricLoadCenter_Inverter_FunctionOfPower, ElectricLoadCenterInverterFunctionOfPower_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::ElectricLoadCenter_Inverter_LookUpTable, ElectricLoadCenterInverterLookUpTable_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::ElectricLoadCenter_Inverter_PVWatts, ElectricLoadCenterInverterPVWatts_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::ElectricLoadCenter_Inverter_Simple, ElectricLoadCenterInverterSimple_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::ElectricLoadCenter_Storage_Battery, ElectricLoadCenterStorageBattery_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::ElectricLoadCenter_Storage_Converter, ElectricLoadCenterStorageConverter_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::ElectricLoadCenter_Storage_LiIonNMCBattery, ElectricLoadCenterStorageLiIonNMCBattery_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::ElectricLoadCenter_Storage_Simple, ElectricLoadCenterStorageSimple_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::ElectricLoadCenter_Transformer, ElectricLoadCenterTransformer_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::EnergyManagementSystem_Actuator, EnergyManagementSystemActuator_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::EnergyManagementSystem_ConstructionIndexVariable, EnergyManagementSystemConstructionIndexVariable_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::EnergyManagementSystem_CurveOrTableIndexVariable, EnergyManagementSystemCurveOrTableIndexVariable_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::EnergyManagementSystem_GlobalVariable, EnergyManagementSystemGlobalVariable_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::EnergyManagementSystem_InternalVariable, EnergyManagementSystemInternalVariable_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::EnergyManagementSystem_MeteredOutputVariable, EnergyManagementSystemMeteredOutputVariable_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::EnergyManagementSystem_OutputVariable, EnergyManagementSystemOutputVariable_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::EnergyManagementSystem_Program, EnergyManagementSystemProgram_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::EnergyManagementSystem_ProgramCallingManager, EnergyManagementSystemProgramCallingManager_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::EnergyManagementSystem_Sensor, EnergyManagementSystemSensor_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::EnergyManagementSystem_Subroutine, EnergyManagementSystemSubroutine_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::EnergyManagementSystem_TrendVariable, EnergyManagementSystemTrendVariable_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::EnvironmentalImpactFactors, EnvironmentalImpactFactors_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::EvaporativeCooler_Direct_CelDekPad, EvaporativeCoolerDirectCelDekPad_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::EvaporativeCooler_Direct_ResearchSpecial, EvaporativeCoolerDirectResearchSpecial_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::EvaporativeCooler_Indirect_CelDekPad, EvaporativeCoolerIndirectCelDekPad_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::EvaporativeCooler_Indirect_ResearchSpecial, EvaporativeCoolerIndirectResearchSpecial_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::EvaporativeCooler_Indirect_WetCoil, EvaporativeCoolerIndirectWetCoil_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::EvaporativeFluidCooler_SingleSpeed, EvaporativeFluidCoolerSingleSpeed_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::EvaporativeFluidCooler_TwoSpeed, EvaporativeFluidCoolerTwoSpeed_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::Exterior_FuelEquipment, ExteriorFuelEquipment_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::Exterior_Lights, ExteriorLights_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::Exterior_WaterEquipment, ExteriorWaterEquipment_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::ExternalInterface, ExternalInterface_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::ExternalInterface_Actuator, ExternalInterfaceActuator_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::ExternalInterface_FunctionalMockupUnitExport_From_Variable,
                               ExternalInterfaceFunctionalMockupUnitExportFromVariable_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::ExternalInterface_FunctionalMockupUnitExport_To_Actuator,
                               ExternalInterfaceFunctionalMockupUnitExportToActuator_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::ExternalInterface_FunctionalMockupUnitExport_To_Schedule,
                               ExternalInterfaceFunctionalMockupUnitExportToSchedule_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::ExternalInterface_FunctionalMockupUnitExport_To_Variable,
                               ExternalInterfaceFunctionalMockupUnitExportToVariable_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::ExternalInterface_FunctionalMockupUnitImport, ExternalInterfaceFunctionalMockupUnitImport_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::ExternalInterface_FunctionalMockupUnitImport_From_Variable,
                               ExternalInterfaceFunctionalMockupUnitImportFromVariable_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::ExternalInterface_FunctionalMockupUnitImport_To_Actuator,
                               ExternalInterfaceFunctionalMockupUnitImportToActuator_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::ExternalInterface_FunctionalMockupUnitImport_To_Schedule,
                               ExternalInterfaceFunctionalMockupUnitImportToSchedule_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::ExternalInterface_FunctionalMockupUnitImport_To_Variable,
                               ExternalInterfaceFunctionalMockupUnitImportToVariable_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::ExternalInterface_Schedule, ExternalInterfaceSchedule_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::ExternalInterface_Variable, ExternalInterfaceVariable_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::FanPerformance_NightVentilation, FanPerformanceNightVentilation_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::Fan_ComponentModel, FanComponentModel_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::Fan_ConstantVolume, FanConstantVolume_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::Fan_OnOff, FanOnOff_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::Fan_SystemModel, FanSystemModel_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::Fan_VariableVolume, FanVariableVolume_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::Fan_ZoneExhaust, FanZoneExhaust_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::FaultModel_EnthalpySensorOffset_OutdoorAir, FaultModelEnthalpySensorOffsetOutdoorAir_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::FaultModel_EnthalpySensorOffset_ReturnAir, FaultModelEnthalpySensorOffsetReturnAir_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::FaultModel_Fouling_AirFilter, FaultModelFoulingAirFilter_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::FaultModel_Fouling_Boiler, FaultModelFoulingBoiler_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::FaultModel_Fouling_Chiller, FaultModelFoulingChiller_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::FaultModel_Fouling_Coil, FaultModelFoulingCoil_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::FaultModel_Fouling_CoolingTower, FaultModelFoulingCoolingTower_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::FaultModel_Fouling_EvaporativeCooler, FaultModelFoulingEvaporativeCooler_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::FaultModel_HumidistatOffset, FaultModelHumidistatOffset_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::FaultModel_HumiditySensorOffset_OutdoorAir, FaultModelHumiditySensorOffsetOutdoorAir_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::FaultModel_TemperatureSensorOffset_ChillerSupplyWater,
                               FaultModelTemperatureSensorOffsetChillerSupplyWater_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::FaultModel_TemperatureSensorOffset_CoilSupplyAir, FaultModelTemperatureSensorOffsetCoilSupplyAir_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::FaultModel_TemperatureSensorOffset_CondenserSupplyWater,
                               FaultModelTemperatureSensorOffsetCondenserSupplyWater_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::FaultModel_TemperatureSensorOffset_OutdoorAir, FaultModelTemperatureSensorOffsetOutdoorAir_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::FaultModel_TemperatureSensorOffset_ReturnAir, FaultModelTemperatureSensorOffsetReturnAir_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::FaultModel_ThermostatOffset, FaultModelThermostatOffset_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::FenestrationSurface_Detailed, SubSurface_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::Floor_Adiabatic, FloorAdiabatic_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::Floor_Detailed, FloorDetailed_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::Floor_GroundContact, FloorGroundContact_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::Floor_Interzone, FloorInterzone_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::FluidCooler_SingleSpeed, FluidCoolerSingleSpeed_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::FluidCooler_TwoSpeed, FluidCoolerTwoSpeed_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::FluidProperties_Concentration, FluidPropertiesConcentration_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::FluidProperties_GlycolConcentration, FluidPropertiesGlycolConcentration_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::FluidProperties_Name, FluidPropertiesName_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::FluidProperties_Saturated, FluidPropertiesSaturated_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::FluidProperties_Superheated, FluidPropertiesSuperheated_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::FluidProperties_Temperatures, FluidPropertiesTemperatures_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::Foundation_Kiva, FoundationKiva_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::Foundation_Kiva_Settings, FoundationKivaSettings_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::FuelFactors, FuelFactors_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::GasEquipment, GasEquipment_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::Generator_CombustionTurbine, GeneratorCombustionTurbine_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::Generator_FuelCell, GeneratorFuelCell_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::Generator_FuelCell_AirSupply, GeneratorFuelCellAirSupply_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::Generator_FuelCell_AuxiliaryHeater, GeneratorFuelCellAuxiliaryHeater_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::Generator_FuelCell_ElectricalStorage, GeneratorFuelCellElectricalStorage_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::Generator_FuelCell_ExhaustGasToWaterHeatExchanger,
                               GeneratorFuelCellExhaustGasToWaterHeatExchanger_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::Generator_FuelCell_Inverter, GeneratorFuelCellInverter_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::Generator_FuelCell_PowerModule, GeneratorFuelCellPowerModule_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::Generator_FuelCell_StackCooler, GeneratorFuelCellStackCooler_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::Generator_FuelCell_WaterSupply, GeneratorFuelCellWaterSupply_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::Generator_FuelSupply, GeneratorFuelSupply_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::Generator_InternalCombustionEngine, GeneratorInternalCombustionEngine_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::Generator_MicroCHP, GeneratorMicroCHP_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::Generator_MicroCHP_NonNormalizedParameters, GeneratorMicroCHPNonNormalizedParameters_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::Generator_MicroTurbine, GeneratorMicroTurbine_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::Generator_PVWatts, GeneratorPVWatts_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::Generator_Photovoltaic, GeneratorPhotovoltaic_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::Generator_WindTurbine, GeneratorWindTurbine_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::GeometryTransform, GeometryTransform_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::GlazedDoor, GlazedDoor_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::GlazedDoor_Interzone, GlazedDoorInterzone_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::GlobalGeometryRules, GlobalGeometryRules_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::GroundHeatExchanger_HorizontalTrench, GroundHeatExchangerHorizontalTrench_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::GroundHeatExchanger_Pond, GroundHeatExchangerPond_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::GroundHeatExchanger_ResponseFactors, GroundHeatExchangerVertical_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::GroundHeatExchanger_Slinky, GroundHeatExchangerSlinky_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::GroundHeatExchanger_Surface, GroundHeatExchangerSurface_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::GroundHeatExchanger_Vertical_Array, GroundHeatExchangerVerticalArray_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::GroundHeatExchanger_Vertical_Single, GroundHeatExchangerVerticalSingle_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::GroundHeatExchanger_Vertical_Sizing_Rectangle, GroundHeatExchangerVerticalSizingRectangle_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::GroundHeatTransfer_Basement_AutoGrid, GroundHeatTransferBasementAutoGrid_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::GroundHeatTransfer_Basement_BldgData, GroundHeatTransferBasementBldgData_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::GroundHeatTransfer_Basement_ComBldg, GroundHeatTransferBasementComBldg_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::GroundHeatTransfer_Basement_EquivAutoGrid, GroundHeatTransferBasementEquivAutoGrid_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::GroundHeatTransfer_Basement_Insulation, GroundHeatTransferBasementInsulation_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::GroundHeatTransfer_Basement_Interior, GroundHeatTransferBasementInterior_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::GroundHeatTransfer_Basement_ManualGrid, GroundHeatTransferBasementManualGrid_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::GroundHeatTransfer_Basement_MatlProps, GroundHeatTransferBasementMatlProps_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::GroundHeatTransfer_Basement_SimParameters, GroundHeatTransferBasementSimParameters_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::GroundHeatTransfer_Basement_SurfaceProps, GroundHeatTransferBasementSurfaceProps_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::GroundHeatTransfer_Basement_XFACE, GroundHeatTransferBasementXFACE_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::GroundHeatTransfer_Basement_YFACE, GroundHeatTransferBasementYFACE_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::GroundHeatTransfer_Basement_ZFACE, GroundHeatTransferBasementZFACE_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::GroundHeatTransfer_Control, GroundHeatTransferControl_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::GroundHeatTransfer_Slab_AutoGrid, GroundHeatTransferSlabAutoGrid_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::GroundHeatTransfer_Slab_BldgProps, GroundHeatTransferSlabBldgProps_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::GroundHeatTransfer_Slab_BoundConds, GroundHeatTransferSlabBoundConds_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::GroundHeatTransfer_Slab_EquivalentSlab, GroundHeatTransferSlabEquivalentSlab_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::GroundHeatTransfer_Slab_Insulation, GroundHeatTransferSlabInsulation_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::GroundHeatTransfer_Slab_ManualGrid, GroundHeatTransferSlabManualGrid_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::GroundHeatTransfer_Slab_Materials, GroundHeatTransferSlabMaterials_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::GroundHeatTransfer_Slab_MatlProps, GroundHeatTransferSlabMatlProps_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::GroundHeatTransfer_Slab_XFACE, GroundHeatTransferSlabXFACE_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::GroundHeatTransfer_Slab_YFACE, GroundHeatTransferSlabYFACE_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::GroundHeatTransfer_Slab_ZFACE, GroundHeatTransferSlabZFACE_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::HVACSystemRootFindingAlgorithm, HVACSystemRootFindingAlgorithm_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::HVACTemplate_Plant_Boiler, HVACTemplatePlantBoiler_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::HVACTemplate_Plant_Boiler_ObjectReference, HVACTemplatePlantBoilerObjectReference_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::HVACTemplate_Plant_ChilledWaterLoop, HVACTemplatePlantChilledWaterLoop_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::HVACTemplate_Plant_Chiller, HVACTemplatePlantChiller_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::HVACTemplate_Plant_Chiller_ObjectReference, HVACTemplatePlantChillerObjectReference_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::HVACTemplate_Plant_HotWaterLoop, HVACTemplatePlantHotWaterLoop_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::HVACTemplate_Plant_MixedWaterLoop, HVACTemplatePlantMixedWaterLoop_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::HVACTemplate_Plant_Tower, HVACTemplatePlantTower_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::HVACTemplate_Plant_Tower_ObjectReference, HVACTemplatePlantTowerObjectReference_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::HVACTemplate_System_ConstantVolume, HVACTemplateSystemConstantVolume_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::HVACTemplate_System_DedicatedOutdoorAir, HVACTemplateSystemDedicatedOutdoorAir_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::HVACTemplate_System_DualDuct, HVACTemplateSystemDualDuct_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::HVACTemplate_System_PackagedVAV, HVACTemplateSystemPackagedVAV_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::HVACTemplate_System_Unitary, HVACTemplateSystemUnitary_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::HVACTemplate_System_UnitaryHeatPump_AirToAir, HVACTemplateSystemUnitaryHeatPumpAirToAir_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::HVACTemplate_System_UnitarySystem, HVACTemplateSystemUnitarySystem_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::HVACTemplate_System_VAV, HVACTemplateSystemVAV_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::HVACTemplate_System_VRF, HVACTemplateSystemVRF_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::HVACTemplate_Thermostat, HVACTemplateThermostat_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::HVACTemplate_Zone_BaseboardHeat, HVACTemplateZoneBaseboardHeat_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::HVACTemplate_Zone_ConstantVolume, HVACTemplateZoneConstantVolume_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::HVACTemplate_Zone_DualDuct, HVACTemplateZoneDualDuct_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::HVACTemplate_Zone_FanCoil, HVACTemplateZoneFanCoil_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::HVACTemplate_Zone_PTAC, HVACTemplateZonePTAC_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::HVACTemplate_Zone_PTHP, HVACTemplateZonePTHP_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::HVACTemplate_Zone_Unitary, HVACTemplateZoneUnitary_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::HVACTemplate_Zone_VAV, HVACTemplateZoneVAV_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::HVACTemplate_Zone_VAV_FanPowered, HVACTemplateZoneVAVFanPowered_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::HVACTemplate_Zone_VAV_HeatAndCool, HVACTemplateZoneVAVHeatAndCool_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::HVACTemplate_Zone_VRF, HVACTemplateZoneVRF_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::HVACTemplate_Zone_WaterToAirHeatPump, HVACTemplateZoneWaterToAirHeatPump_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::HeaderedPumps_ConstantSpeed, HeaderedPumpsConstantSpeed_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::HeaderedPumps_VariableSpeed, HeaderedPumpsVariableSpeed_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::HeatBalanceAlgorithm, HeatBalanceAlgorithm_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::HeatBalanceSettings_ConductionFiniteDifference, HeatBalanceSettingsConductionFiniteDifference_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::HeatExchanger_AirToAir_FlatPlate, HeatExchangerAirToAirFlatPlate_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::HeatExchanger_AirToAir_SensibleAndLatent, HeatExchangerAirToAirSensibleAndLatent_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::HeatExchanger_Desiccant_BalancedFlow, HeatExchangerDesiccantBalancedFlow_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::HeatExchanger_Desiccant_BalancedFlow_PerformanceDataType1,
                               HeatExchangerDesiccantBalancedFlowPerformanceDataType1_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::HeatExchanger_FluidToFluid, HeatExchangerFluidToFluid_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::HeatPump_AirToWater, HeatPumpAirToWater_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::HeatPump_AirToWater_FuelFired_Cooling, HeatPumpAirToWaterFuelFiredCooling_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::HeatPump_AirToWater_FuelFired_Heating, HeatPumpAirToWaterFuelFiredHeating_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::HeatPump_PlantLoop_EIR_Cooling, HeatPumpPlantLoopEIRCooling_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::HeatPump_PlantLoop_EIR_Heating, HeatPumpPlantLoopEIRHeating_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::HeatPump_WaterToWater_EquationFit_Cooling, HeatPumpWaterToWaterEquationFitCooling_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::HeatPump_WaterToWater_EquationFit_Heating, HeatPumpWaterToWaterEquationFitHeating_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::HeatPump_WaterToWater_ParameterEstimation_Cooling, HeatPumpWaterToWaterParameterEstimationCooling_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::HeatPump_WaterToWater_ParameterEstimation_Heating, HeatPumpWaterToWaterParameterEstimationHeating_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::HotWaterEquipment, HotWaterEquipment_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::Humidifier_Steam_Electric, HumidifierSteamElectric_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::Humidifier_Steam_Gas, HumidifierSteamGas_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::HybridModel_Zone, HybridModelZone_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::IndoorLivingWall, IndoorLivingWall_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::InternalMass, InteriorPartitionSurface_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::LifeCycleCost_NonrecurringCost, LifeCycleCost_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::LifeCycleCost_Parameters, LifeCycleCostParameters_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::LifeCycleCost_RecurringCosts, LifeCycleCost_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::LifeCycleCost_UseAdjustment, LifeCycleCostUseAdjustment_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::LifeCycleCost_UsePriceEscalation, LifeCycleCostUsePriceEscalation_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::Lights, Lights_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::LoadProfile_Plant, LoadProfilePlant_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::Material, StandardOpaqueMaterial_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::MaterialProperty_GlazingSpectralData, MaterialPropertyGlazingSpectralData_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::MaterialProperty_HeatAndMoistureTransfer_Diffusion,
                               MaterialPropertyHeatAndMoistureTransferDiffusion_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::MaterialProperty_HeatAndMoistureTransfer_Redistribution,
                               MaterialPropertyHeatAndMoistureTransferRedistribution_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::MaterialProperty_HeatAndMoistureTransfer_Settings,
                               MaterialPropertyHeatAndMoistureTransferSettings_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::MaterialProperty_HeatAndMoistureTransfer_SorptionIsotherm,
                               MaterialPropertyHeatAndMoistureTransferSorptionIsotherm_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::MaterialProperty_HeatAndMoistureTransfer_Suction, MaterialPropertyHeatAndMoistureTransferSuction_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::MaterialProperty_HeatAndMoistureTransfer_ThermalConductivity,
                               MaterialPropertyHeatAndMoistureTransferThermalConductivity_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::MaterialProperty_MoisturePenetrationDepth_Settings,
                               MaterialPropertyMoisturePenetrationDepthSettings_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::MaterialProperty_PhaseChange, MaterialPropertyPhaseChange_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::MaterialProperty_PhaseChangeHysteresis, MaterialPropertyPhaseChangeHysteresis_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::MaterialProperty_VariableAbsorptance, MaterialPropertyVariableAbsorptance_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::MaterialProperty_VariableThermalConductivity, MaterialPropertyVariableThermalConductivity_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::Material_AirGap, AirGap_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::Material_InfraredTransparent, InfraredTransparentMaterial_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::Material_NoMass, MasslessOpaqueMaterial_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::Material_RoofVegetation, RoofVegetation_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::Matrix_TwoDimension, MatrixTwoDimension_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::Meter_Custom, MeterCustom_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::Meter_CustomDecrement, MeterCustomDecrement_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::Node, Node_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::NodeList, NodeList_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::OtherEquipment, OtherEquipment_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::OutdoorAir_Mixer, OutdoorAirMixer_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::OutputControl_Files, OutputControlFiles_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::OutputControl_IlluminanceMap_Style, OutputControlIlluminanceMapStyle_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::OutputControl_ReportingTolerances, OutputControlReportingTolerances_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::OutputControl_ResilienceSummaries, OutputControlResilienceSummaries_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::OutputControl_Sizing_Style, OutputControlSizingStyle_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::OutputControl_SurfaceColorScheme, OutputControlSurfaceColorScheme_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::OutputControl_Table_Style, OutputControlTableStyle_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::OutputControl_Timestamp, OutputControlTimestamp_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::Output_Constructions, OutputConstructions_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::Output_DaylightFactors, OutputDaylightFactors_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::Output_DebuggingData, OutputDebuggingData_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::Output_Diagnostics, OutputDiagnostics_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::Output_EnergyManagementSystem, OutputEnergyManagementSystem_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::Output_EnvironmentalImpactFactors, OutputEnvironmentalImpactFactors_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::Output_JSON, OutputJSON_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::Output_Meter, OutputMeter_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::Output_Meter_Cumulative, OutputMeterCumulative_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::Output_Meter_Cumulative_MeterFileOnly, OutputMeterCumulativeMeterFileOnly_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::Output_Meter_MeterFileOnly, OutputMeterMeterFileOnly_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::Output_PreprocessorMessage, OutputPreprocessorMessage_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::Output_SQLite, OutputSQLite_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::Output_Schedules, OutputSchedules_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::Output_Surfaces_Drawing, OutputSurfacesDrawing_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::Output_Surfaces_List, OutputSurfacesList_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::Output_Table_Annual, OutputTableAnnual_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::Output_Table_Monthly, OutputTableMonthly_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::Output_Table_ReportPeriod, OutputTableReportPeriod_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::Output_Table_SummaryReports, OutputTableSummaryReports_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::Output_Table_TimeBins, OutputTableTimeBins_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::Output_Variable, OutputVariable_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::Output_VariableDictionary, OutputVariableDictionary_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::Parametric_FileNameSuffix, ParametricFileNameSuffix_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::Parametric_Logic, ParametricLogic_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::Parametric_RunControl, ParametricRunControl_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::Parametric_SetValueForRun, ParametricSetValueForRun_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::People, People_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::PerformancePrecisionTradeoffs, PerformancePrecisionTradeoffs_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::PhotovoltaicPerformance_Sandia, PhotovoltaicPerformanceSandia_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::PhotovoltaicPerformance_Simple, PhotovoltaicPerformanceSimple_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::Pipe_Adiabatic, PipeAdiabatic_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::Pipe_Adiabatic_Steam, PipeAdiabaticSteam_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::Pipe_Indoor, PipeIndoor_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::Pipe_Outdoor, PipeOutdoor_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::Pipe_Underground, PipeUnderground_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::PipingSystem_Underground_Domain, PipingSystemUndergroundDomain_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::PipingSystem_Underground_PipeCircuit, PipingSystemUndergroundPipeCircuit_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::PipingSystem_Underground_PipeSegment, PipingSystemUndergroundPipeSegment_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::PlantComponent_TemperatureSource, PlantComponentTemperatureSource_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::PlantComponent_UserDefined, PlantComponentUserDefined_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::PlantEquipmentOperationSchemes, PlantEquipmentOperationSchemes_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::PlantEquipmentOperation_ChillerHeaterChangeover, PlantEquipmentOperationChillerHeaterChangeover_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::PlantEquipmentOperation_ComponentSetpoint, PlantEquipmentOperationComponentSetpoint_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::PlantEquipmentOperation_CoolingLoad, PlantEquipmentOperationCoolingLoad_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::PlantEquipmentOperation_HeatingLoad, PlantEquipmentOperationHeatingLoad_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::PlantEquipmentOperation_OutdoorDewpoint, PlantEquipmentOperationOutdoorDewpoint_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::PlantEquipmentOperation_OutdoorDewpointDifference,
                               PlantEquipmentOperationOutdoorDewpointDifference_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::PlantEquipmentOperation_OutdoorDryBulb, PlantEquipmentOperationOutdoorDryBulb_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::PlantEquipmentOperation_OutdoorDryBulbDifference, PlantEquipmentOperationOutdoorDryBulbDifference_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::PlantEquipmentOperation_OutdoorRelativeHumidity, PlantEquipmentOperationOutdoorRelativeHumidity_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::PlantEquipmentOperation_OutdoorWetBulb, PlantEquipmentOperationOutdoorWetBulb_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::PlantEquipmentOperation_OutdoorWetBulbDifference, PlantEquipmentOperationOutdoorWetBulbDifference_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::PlantEquipmentOperation_ThermalEnergyStorage, PlantEquipmentOperationThermalEnergyStorage_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::PlantEquipmentOperation_Uncontrolled, PlantEquipmentOperationUncontrolled_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::PlantEquipmentOperation_UserDefined, PlantEquipmentOperationUserDefined_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::PlantLoop, PlantLoop_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::Pump_ConstantSpeed, PumpConstantSpeed_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::Pump_VariableSpeed, PumpVariableSpeed_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::Pump_VariableSpeed_Condensate, PumpVariableSpeedCondensate_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::PythonPlugin_Instance, PythonPluginInstance_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::PythonPlugin_OutputVariable, PythonPluginOutputVariable_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::PythonPlugin_SearchPaths, PythonPluginSearchPaths_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::PythonPlugin_TrendVariable, PythonPluginTrendVariable_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::PythonPlugin_Variables, PythonPluginVariable_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::Refrigeration_AirChiller, RefrigerationAirChiller_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::Refrigeration_Case, RefrigerationCase_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::Refrigeration_Compressor, RefrigerationCompressor_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::Refrigeration_CompressorRack, RefrigerationCompressorRack_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::Refrigeration_Condenser_AirCooled, RefrigerationCondenserAirCooled_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::Refrigeration_Condenser_Cascade, RefrigerationCondenserCascade_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::Refrigeration_Condenser_EvaporativeCooled, RefrigerationCondenserEvaporativeCooled_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::Refrigeration_Condenser_WaterCooled, RefrigerationCondenserWaterCooled_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::Refrigeration_GasCooler_AirCooled, RefrigerationGasCoolerAirCooled_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::Refrigeration_SecondarySystem, RefrigerationSecondarySystem_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::Refrigeration_System, RefrigerationSystem_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::Refrigeration_TranscriticalSystem, RefrigerationTranscriticalSystem_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::Refrigeration_WalkIn, RefrigerationWalkIn_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::Roof, Roof_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::RoofCeiling_Detailed, RoofCeilingDetailed_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::RoofIrrigation, RoofIrrigation_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::RoomAirModelType, RoomAirModelType_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::RoomAirSettings_AirflowNetwork, RoomAirSettingsAirflowNetwork_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::RoomAirSettings_CrossVentilation, RoomAirSettingsCrossVentilation_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::RoomAirSettings_OneNodeDisplacementVentilation, RoomAirSettingsOneNodeDisplacementVentilation_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::RoomAirSettings_ThreeNodeDisplacementVentilation, RoomAirSettingsThreeNodeDisplacementVentilation_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::RoomAirSettings_UnderFloorAirDistributionExterior,
                               RoomAirSettingsUnderFloorAirDistributionExterior_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::RoomAirSettings_UnderFloorAirDistributionInterior,
                               RoomAirSettingsUnderFloorAirDistributionInterior_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::RoomAir_Node, RoomAirNode_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::RoomAir_Node_AirflowNetwork, RoomAirNodeAirflowNetwork_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::RoomAir_Node_AirflowNetwork_AdjacentSurfaceList, RoomAirNodeAirflowNetworkAdjacentSurfaceList_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::RoomAir_Node_AirflowNetwork_HVACEquipment, RoomAirNodeAirflowNetworkHVACEquipment_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::RoomAir_Node_AirflowNetwork_InternalGains, RoomAirNodeAirflowNetworkInternalGains_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::RoomAir_TemperaturePattern_ConstantGradient, RoomAirTemperaturePatternConstantGradient_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::RoomAir_TemperaturePattern_NondimensionalHeight, RoomAirTemperaturePatternNondimensionalHeight_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::RoomAir_TemperaturePattern_SurfaceMapping, RoomAirTemperaturePatternSurfaceMapping_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::RoomAir_TemperaturePattern_TwoGradient, RoomAirTemperaturePatternTwoGradient_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::RoomAir_TemperaturePattern_UserDefined, RoomAirTemperaturePatternUserDefined_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::RunPeriod, RunPeriod_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::RunPeriodControl_DaylightSavingTime, RunPeriodControlDaylightSavingTime_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::RunPeriodControl_SpecialDays, RunPeriodControlSpecialDays_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::ScheduleTypeLimits, ScheduleTypeLimits_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::Schedule_Compact, ScheduleCompact_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::Schedule_Constant, ScheduleConstant_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::Schedule_Day_Hourly, ScheduleDayHourly_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::Schedule_Day_Interval, ScheduleDay_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::Schedule_Day_List, ScheduleDayList_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::Schedule_File, ScheduleFile_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::Schedule_File_Shading, ScheduleFileShading_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::Schedule_Week_Compact, ScheduleWeekCompact_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::Schedule_Week_Daily, ScheduleWeek_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::Schedule_Year, ScheduleYear_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::SetpointManager_Coldest, SetpointManagerColdest_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::SetpointManager_CondenserEnteringReset, SetpointManagerCondenserEnteringReset_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::SetpointManager_CondenserEnteringReset_Ideal, SetpointManagerCondenserEnteringResetIdeal_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::SetpointManager_FollowGroundTemperature, SetpointManagerFollowGroundTemperature_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::SetpointManager_FollowOutdoorAirTemperature, SetpointManagerFollowOutdoorAirTemperature_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::SetpointManager_FollowSystemNodeTemperature, SetpointManagerFollowSystemNodeTemperature_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::SetpointManager_MixedAir, SetpointManagerMixedAir_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::SetpointManager_MultiZone_Cooling_Average, SetpointManagerMultiZoneCoolingAverage_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::SetpointManager_MultiZone_Heating_Average, SetpointManagerMultiZoneHeatingAverage_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::SetpointManager_MultiZone_Humidity_Maximum, SetpointManagerMultiZoneHumidityMaximum_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::SetpointManager_MultiZone_Humidity_Minimum, SetpointManagerMultiZoneHumidityMinimum_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::SetpointManager_MultiZone_MaximumHumidity_Average, SetpointManagerMultiZoneMaximumHumidityAverage_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::SetpointManager_MultiZone_MinimumHumidity_Average, SetpointManagerMultiZoneMinimumHumidityAverage_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::SetpointManager_OutdoorAirPretreat, SetpointManagerOutdoorAirPretreat_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::SetpointManager_OutdoorAirReset, SetpointManagerOutdoorAirReset_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::SetpointManager_ReturnAirBypassFlow, SetpointManagerReturnAirBypassFlow_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::SetpointManager_ReturnTemperature_ChilledWater, SetpointManagerReturnTemperatureChilledWater_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::SetpointManager_ReturnTemperature_HotWater, SetpointManagerReturnTemperatureHotWater_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::SetpointManager_Scheduled, SetpointManagerScheduled_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::SetpointManager_Scheduled_DualSetpoint, SetpointManagerScheduledDualSetpoint_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::SetpointManager_SingleZone_Cooling, SetpointManagerSingleZoneCooling_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::SetpointManager_SingleZone_Heating, SetpointManagerSingleZoneHeating_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::SetpointManager_SingleZone_Humidity_Maximum, SetpointManagerSingleZoneHumidityMaximum_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::SetpointManager_SingleZone_Humidity_Minimum, SetpointManagerSingleZoneHumidityMinimum_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::SetpointManager_SingleZone_OneStageCooling, SetpointManagerSingleZoneOneStageCooling_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::SetpointManager_SingleZone_OneStageHeating, SetpointManagerSingleZoneOneStageHeating_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::SetpointManager_SingleZone_Reheat, SetpointManagerSingleZoneReheat_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::SetpointManager_SystemNodeReset_Humidity, SetpointManagerSystemNodeResetHumidity_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::SetpointManager_SystemNodeReset_Temperature, SetpointManagerSystemNodeResetTemperature_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::SetpointManager_Warmest, SetpointManagerWarmest_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::SetpointManager_WarmestTemperatureFlow, SetpointManagerWarmestTemperatureFlow_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::ShadingProperty_Reflectance, ShadingPropertyReflectance_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::Shading_Building, ShadingBuilding_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::Shading_Building_Detailed, ShadingBuildingDetailed_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::Shading_Fin, ShadingFin_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::Shading_Fin_Projection, ShadingFinProjection_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::Shading_Overhang, ShadingOverhang_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::Shading_Overhang_Projection, ShadingOverhangProjection_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::Shading_Site, ShadingSite_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::Shading_Site_Detailed, ShadingSiteDetailed_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::Shading_Zone_Detailed, ShadingZoneDetailed_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::ShadowCalculation, ShadowCalculation_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::SimulationControl, SimulationControl_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::Site_GroundDomain_Basement, SiteGroundDomainBasement_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::Site_GroundDomain_Slab, SiteGroundDomainSlab_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::Site_GroundReflectance, SiteGroundReflectance_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::Site_GroundReflectance_SnowModifier, SiteGroundReflectanceSnowModifier_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::Site_GroundTemperature_BuildingSurface, SiteGroundTemperatureBuildingSurface_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::Site_GroundTemperature_Deep, SiteGroundTemperatureDeep_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::Site_GroundTemperature_FCfactorMethod, SiteGroundTemperatureFCfactorMethod_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::Site_GroundTemperature_Shallow, SiteGroundTemperatureShallow_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::Site_GroundTemperature_Undisturbed_FiniteDifference,
                               SiteGroundTemperatureUndisturbedFiniteDifference_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::Site_GroundTemperature_Undisturbed_KusudaAchenbach,
                               SiteGroundTemperatureUndisturbedKusudaAchenbach_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::Site_GroundTemperature_Undisturbed_Xing, SiteGroundTemperatureUndisturbedXing_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::Site_HeightVariation, SiteHeightVariation_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::Site_Location, Site_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::Site_Precipitation, SitePrecipitation_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::Site_SolarAndVisibleSpectrum, SiteSolarAndVisibleSpectrum_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::Site_SpectrumData, SiteSpectrumData_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::Site_VariableLocation, SiteVariableLocation_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::Site_WaterMainsTemperature, SiteWaterMainsTemperature_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::Site_WeatherStation, SiteWeatherStation_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::SizingPeriod_DesignDay, DesignDay_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::SizingPeriod_WeatherFileConditionType, SizingPeriodWeatherFileConditionType_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::SizingPeriod_WeatherFileDays, SizingPeriodWeatherFileDays_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::Sizing_Parameters, SizingParameters_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::Sizing_Plant, SizingPlant_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::Sizing_System, SizingSystem_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::Sizing_Zone, SizingZone_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::SolarCollectorPerformance_FlatPlate, SolarCollectorPerformanceFlatPlate_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::SolarCollectorPerformance_IntegralCollectorStorage,
                               SolarCollectorPerformanceIntegralCollectorStorage_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::SolarCollectorPerformance_PhotovoltaicThermal_BIPVT,
                               SolarCollectorPerformancePhotovoltaicThermalBIPVT_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::SolarCollectorPerformance_PhotovoltaicThermal_Simple,
                               SolarCollectorPerformancePhotovoltaicThermalSimple_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::SolarCollector_FlatPlate_PhotovoltaicThermal, SolarCollectorFlatPlatePhotovoltaicThermal_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::SolarCollector_FlatPlate_Water, SolarCollectorFlatPlateWater_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::SolarCollector_IntegralCollectorStorage, SolarCollectorIntegralCollectorStorage_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::SolarCollector_UnglazedTranspired, SolarCollectorUnglazedTranspired_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::SolarCollector_UnglazedTranspired_Multisystem, SolarCollectorUnglazedTranspiredMultisystem_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::Space, Space_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::SpaceHVAC_EquipmentConnections, SpaceHVACEquipmentConnections_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::SpaceHVAC_ZoneEquipmentMixer, SpaceHVACZoneEquipmentMixer_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::SpaceHVAC_ZoneEquipmentSplitter, SpaceHVACZoneEquipmentSplitter_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::SpaceHVAC_ZoneReturnMixer, SpaceHVACZoneReturnMixer_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::SpaceList, SpaceType_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::SteamEquipment, SteamEquipment_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::SurfaceContaminantSourceAndSink_Generic_BoundaryLayerDiffusion,
                               SurfaceContaminantSourceAndSinkGenericBoundaryLayerDiffusion_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::SurfaceContaminantSourceAndSink_Generic_DepositionVelocitySink,
                               SurfaceContaminantSourceAndSinkGenericDepositionVelocitySink_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::SurfaceContaminantSourceAndSink_Generic_PressureDriven,
                               SurfaceContaminantSourceAndSinkGenericPressureDriven_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::SurfaceControl_MovableInsulation, SurfaceControlMovableInsulation_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::SurfaceConvectionAlgorithm_Inside, InsideSurfaceConvectionAlgorithm_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::SurfaceConvectionAlgorithm_Inside_AdaptiveModelSelections,
                               SurfaceConvectionAlgorithmInsideAdaptiveModelSelections_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::SurfaceConvectionAlgorithm_Inside_UserCurve, SurfaceConvectionAlgorithmInsideUserCurve_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::SurfaceConvectionAlgorithm_Outside, OutsideSurfaceConvectionAlgorithm_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::SurfaceConvectionAlgorithm_Outside_AdaptiveModelSelections,
                               SurfaceConvectionAlgorithmOutsideAdaptiveModelSelections_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::SurfaceConvectionAlgorithm_Outside_UserCurve, SurfaceConvectionAlgorithmOutsideUserCurve_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::SurfaceProperties_VaporCoefficients, SurfacePropertiesVaporCoefficients_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::SurfaceProperty_ConvectionCoefficients, SurfacePropertyConvectionCoefficients_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::SurfaceProperty_ConvectionCoefficients_MultipleSurface,
                               SurfacePropertyConvectionCoefficientsMultipleSurface_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::SurfaceProperty_ExposedFoundationPerimeter, SurfacePropertyExposedFoundationPerimeter_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::SurfaceProperty_ExteriorNaturalVentedCavity, SurfacePropertyExteriorNaturalVentedCavity_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::SurfaceProperty_GroundSurfaces, SurfacePropertyGroundSurfaces_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::SurfaceProperty_HeatBalanceSourceTerm, SurfacePropertyHeatBalanceSourceTerm_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::SurfaceProperty_HeatTransferAlgorithm, SurfacePropertyHeatTransferAlgorithm_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::SurfaceProperty_HeatTransferAlgorithm_Construction,
                               SurfacePropertyHeatTransferAlgorithmConstruction_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::SurfaceProperty_HeatTransferAlgorithm_MultipleSurface,
                               SurfacePropertyHeatTransferAlgorithmMultipleSurface_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::SurfaceProperty_HeatTransferAlgorithm_SurfaceList,
                               SurfacePropertyHeatTransferAlgorithmSurfaceList_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::SurfaceProperty_IncidentSolarMultiplier, SurfacePropertyIncidentSolarMultiplier_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::SurfaceProperty_LocalEnvironment, SurfacePropertyLocalEnvironment_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::SurfaceProperty_OtherSideCoefficients, SurfacePropertyOtherSideCoefficients_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::SurfaceProperty_OtherSideConditionsModel, SurfacePropertyOtherSideConditionsModel_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::SurfaceProperty_SolarIncidentInside, SurfacePropertySolarIncidentInside_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::SurfaceProperty_SurroundingSurfaces, SurfacePropertySurroundingSurfaces_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::SurfaceProperty_Underwater, SurfacePropertyUnderwater_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::SwimmingPool_Indoor, SwimmingPoolIndoor_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::Table_IndependentVariable, TableIndependentVariable_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::Table_Lookup, TableLookup_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::TemperingValve, TemperingValve_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::ThermalStorage_ChilledWater_Mixed, ThermalStorageChilledWaterMixed_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::ThermalStorage_ChilledWater_Stratified, ThermalStorageChilledWaterStratified_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::ThermalStorage_HotWater_Stratified, ThermalStorageHotWaterStratified_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::ThermalStorage_Ice_Detailed, ThermalStorageIceDetailed_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::ThermalStorage_Ice_Simple, ThermalStorageIceSimple_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::ThermalStorage_PCM, ThermalStoragePCM_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::ThermalStorage_Sizing, ThermalStorageSizing_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::ThermostatSetpoint_DualSetpoint, ThermostatSetpointDualSetpoint_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::ThermostatSetpoint_SingleCooling, ThermostatSetpointDualSetpoint_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::ThermostatSetpoint_SingleHeating, ThermostatSetpointDualSetpoint_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::ThermostatSetpoint_SingleHeatingOrCooling, ThermostatSetpointSingleHeatingOrCooling_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::ThermostatSetpoint_ThermalComfort_Fanger_DualSetpoint,
                               ThermostatSetpointThermalComfortFangerDualSetpoint_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::ThermostatSetpoint_ThermalComfort_Fanger_SingleCooling,
                               ThermostatSetpointThermalComfortFangerSingleCooling_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::ThermostatSetpoint_ThermalComfort_Fanger_SingleHeating,
                               ThermostatSetpointThermalComfortFangerSingleHeating_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::ThermostatSetpoint_ThermalComfort_Fanger_SingleHeatingOrCooling,
                               ThermostatSetpointThermalComfortFangerSingleHeatingOrCooling_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::Timestep, Timestep_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::UtilityCost_Charge_Block, UtilityCostChargeBlock_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::UtilityCost_Charge_Simple, UtilityCostChargeSimple_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::UtilityCost_Qualify, UtilityCostQualify_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::UtilityCost_Ratchet, UtilityCostRatchet_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::UtilityCost_Tariff, UtilityCostTariff_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::UtilityCost_Variable, UtilityCostVariable_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::Version, Version_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::Wall_Adiabatic, WallAdiabatic_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::Wall_Detailed, WallDetailed_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::Wall_Exterior, WallExterior_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::Wall_Interzone, WallInterzone_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::Wall_Underground, WallUnderground_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::WaterHeater_HeatPump_PumpedCondenser, WaterHeaterHeatPump_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::WaterHeater_HeatPump_WrappedCondenser, WaterHeaterHeatPumpWrappedCondenser_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::WaterHeater_Mixed, WaterHeaterMixed_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::WaterHeater_Sizing, WaterHeaterSizing_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::WaterHeater_Stratified, WaterHeaterStratified_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::WaterUse_Connections, WaterUseConnections_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::WaterUse_Equipment, WaterUseEquipment_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::WaterUse_RainCollector, WaterUseRainCollector_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::WaterUse_Storage, WaterUseStorage_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::WaterUse_Well, WaterUseWell_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::WeatherProperty_SkyTemperature, SkyTemperature_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::Window, Window_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::WindowGap_DeflectionState, WindowGapDeflectionState_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::WindowGap_SupportPillar, WindowGapSupportPillar_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::WindowMaterial_Blind, Blind_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::WindowMaterial_Blind_EquivalentLayer, WindowMaterialBlindEquivalentLayer_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::WindowMaterial_Screen, Screen_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::WindowMaterial_Shade, Shade_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::WindowMaterial_ComplexShade, WindowMaterialComplexShade_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::WindowMaterial_Drape_EquivalentLayer, WindowMaterialDrapeEquivalentLayer_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::WindowMaterial_Gap, WindowMaterialGap_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::WindowMaterial_Gap_EquivalentLayer, WindowMaterialGapEquivalentLayer_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::WindowMaterial_Gas, Gas_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::WindowMaterial_GasMixture, GasMixture_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::WindowMaterial_Glazing, StandardGlazing_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::WindowMaterial_GlazingGroup_Thermochromic, ThermochromicGlazing_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::WindowMaterial_Glazing_EquivalentLayer, WindowMaterialGlazingEquivalentLayer_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::WindowMaterial_Glazing_RefractionExtinctionMethod, RefractionExtinctionGlazing_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::WindowMaterial_Screen_EquivalentLayer, WindowMaterialScreenEquivalentLayer_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::WindowMaterial_Shade_EquivalentLayer, WindowMaterialShadeEquivalentLayer_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::WindowMaterial_SimpleGlazingSystem, SimpleGlazing_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::WindowProperty_AirflowControl, WindowPropertyAirflowControl_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::WindowProperty_FrameAndDivider, WindowPropertyFrameAndDivider_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::WindowProperty_StormWindow, WindowPropertyStormWindow_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::WindowShadingControl, ShadingControl_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::WindowThermalModel_Params, WindowThermalModelParams_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::Window_Interzone, WindowInterzone_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::WindowsCalculationEngine, WindowsCalculationEngine_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::Zone, ThermalZone_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::ZoneAirBalance_OutdoorAir, ZoneAirBalanceOutdoorAir_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::ZoneAirContaminantBalance, ZoneAirContaminantBalance_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::ZoneAirHeatBalanceAlgorithm, ZoneAirHeatBalanceAlgorithm_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::ZoneAirMassFlowConservation, ZoneAirMassFlowConservation_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::ZoneBaseboard_OutdoorTemperatureControlled, ZoneBaseboardOutdoorTemperatureControlled_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::ZoneCapacitanceMultiplier_ResearchSpecial, ZoneCapacitanceMultiplierResearchSpecial_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::ZoneContaminantSourceAndSink_CarbonDioxide, ZoneContaminantSourceAndSinkCarbonDioxide_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::ZoneContaminantSourceAndSink_Generic_Constant, ZoneContaminantSourceAndSinkGenericConstant_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::ZoneContaminantSourceAndSink_Generic_CutoffModel, ZoneContaminantSourceAndSinkGenericCutoffModel_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::ZoneContaminantSourceAndSink_Generic_DecaySource, ZoneContaminantSourceAndSinkGenericDecaySource_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::ZoneContaminantSourceAndSink_Generic_DepositionRateSink,
                               ZoneContaminantSourceAndSinkGenericDepositionRateSink_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::ZoneControl_ContaminantController, ZoneControlContaminantController_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::ZoneControl_Humidistat, ZoneControlHumidistat_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::ZoneControl_Thermostat_OperativeTemperature, ZoneControlThermostatOperativeTemperature_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::ZoneControl_Thermostat_StagedDualSetpoint, ZoneControlThermostatStagedDualSetpoint_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::ZoneControl_Thermostat_TemperatureAndHumidity, ZoneControlThermostatTemperatureAndHumidity_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::ZoneControl_Thermostat_ThermalComfort, ZoneControlThermostatThermalComfort_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::ZoneCoolTower_Shower, ZoneCoolTowerShower_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::ZoneCrossMixing, ZoneCrossMixing_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::ZoneEarthtube, ZoneEarthtube_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::ZoneGroup, ZoneGroup_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::ZoneHVAC_AirDistributionUnit, ZoneHVACAirDistributionUnit_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::ZoneHVAC_Baseboard_Convective_Electric, ZoneHVACBaseboardConvectiveElectric_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::ZoneHVAC_Baseboard_Convective_Water, ZoneHVACBaseboardConvectiveWater_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::ZoneHVAC_Baseboard_RadiantConvective_Electric, ZoneHVACBaseboardRadiantConvectiveElectric_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::ZoneHVAC_Baseboard_RadiantConvective_Steam, ZoneHVACBaseboardRadiantConvectiveSteam_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::ZoneHVAC_Baseboard_RadiantConvective_Steam_Design, ZoneHVACBaseboardRadiantConvectiveSteamDesign_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::ZoneHVAC_Baseboard_RadiantConvective_Water, ZoneHVACBaseboardRadiantConvectiveWater_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::ZoneHVAC_Baseboard_RadiantConvective_Water_Design, ZoneHVACBaseboardRadiantConvectiveWaterDesign_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::ZoneHVAC_CoolingPanel_RadiantConvective_Water, ZoneHVACCoolingPanelRadiantConvectiveWater_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::ZoneHVAC_Dehumidifier_DX, ZoneHVACDehumidifierDX_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::ZoneHVAC_EnergyRecoveryVentilator, ZoneHVACEnergyRecoveryVentilator_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::ZoneHVAC_EnergyRecoveryVentilator_Controller, ZoneHVACEnergyRecoveryVentilatorController_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::ZoneHVAC_EquipmentConnections, ZoneHVACEquipmentConnections_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::ZoneHVAC_EquipmentList, ZoneHVACEquipmentList_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::ZoneHVAC_EvaporativeCoolerUnit, ZoneHVACEvaporativeCoolerUnit_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::ZoneHVAC_ExhaustControl, ZoneHVACExhaustControl_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::ZoneHVAC_ForcedAir_UserDefined, ZoneHVACForcedAirUserDefined_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::ZoneHVAC_FourPipeFanCoil, ZoneHVACFourPipeFanCoil_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::ZoneHVAC_HighTemperatureRadiant, ZoneHVACHighTemperatureRadiant_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::ZoneHVAC_HybridUnitaryHVAC, ZoneHVACHybridUnitaryHVAC_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::ZoneHVAC_IdealLoadsAirSystem, ZoneHVACIdealLoadsAirSystem_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::ZoneHVAC_LowTemperatureRadiant_ConstantFlow, ZoneHVACLowTempRadiantConstFlow_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::ZoneHVAC_LowTemperatureRadiant_Electric, ZoneHVACLowTemperatureRadiantElectric_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::ZoneHVAC_LowTemperatureRadiant_VariableFlow, ZoneHVACLowTempRadiantVarFlow_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::ZoneHVAC_LowTemperatureRadiant_VariableFlow_Design, ZoneHVACLowTempRadiantVarFlow_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::ZoneHVAC_OutdoorAirUnit, ZoneHVACOutdoorAirUnit_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::ZoneHVAC_OutdoorAirUnit_EquipmentList, ZoneHVACOutdoorAirUnitEquipmentList_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::ZoneHVAC_PackagedTerminalAirConditioner, ZoneHVACPackagedTerminalAirConditioner_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::ZoneHVAC_PackagedTerminalHeatPump, ZoneHVACPackagedTerminalHeatPump_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::ZoneHVAC_TerminalUnit_VariableRefrigerantFlow, ZoneHVACTerminalUnitVariableRefrigerantFlow_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::ZoneHVAC_UnitHeater, ZoneHVACUnitHeater_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::ZoneHVAC_UnitVentilator, ZoneHVACUnitVentilator_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::ZoneHVAC_VentilatedSlab, ZoneHVACVentilatedSlab_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::ZoneHVAC_VentilatedSlab_SlabGroup, ZoneHVACVentilatedSlabSlabGroup_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::ZoneHVAC_WaterToAirHeatPump, ZoneHVACWaterToAirHeatPump_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::ZoneHVAC_WindowAirConditioner, ZoneHVACWindowAirConditioner_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::ZoneInfiltration_DesignFlowRate, SpaceInfiltrationDesignFlowRate_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::ZoneInfiltration_EffectiveLeakageArea, SpaceInfiltrationEffectiveLeakageArea_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::ZoneInfiltration_FlowCoefficient, SpaceInfiltrationFlowCoefficient_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::ZoneMixing, ZoneMixing_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::ZoneProperty_LocalEnvironment, ZonePropertyLocalEnvironment_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::ZoneProperty_UserViewFactors_BySurfaceName, ZonePropertyUserViewFactorsBySurfaceName_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::ZoneRefrigerationDoorMixing, ZoneRefrigerationDoorMixing_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::ZoneThermalChimney, ZoneThermalChimney_Impl);
      REGISTER_NEW_CONSTRUCTOR(IddObjectType::ZoneVentilation_WindandStackOpenArea, ZoneVentilationWindandStackOpenArea_Impl);
      REGISTER_NEW_CONSTRUCTOR(UtilityCostComputation::iddObjectType(), UtilityCostComputation_Impl);
      REGISTER_NEW_CONSTRUCTOR(ZoneEarthtubeParameters::iddObjectType(), ZoneEarthtubeParameters_Impl);

      m_newMap[IddObjectType::Refrigeration_Subcooler] = [](openstudio::epmodel::detail::Model_Impl* m, const IdfObject& object,
                                                            bool keepHandle) -> std::shared_ptr<openstudio::detail::WorkspaceObject_Impl> {
        if (auto subcoolerType = object.getString(Refrigeration_SubcoolerFields::SubcoolerType, false)) {
          if (openstudio::istringEqual(*subcoolerType, "LiquidSuction")) {
            return std::make_shared<RefrigerationSubcoolerLiquidSuction_Impl>(object, m, keepHandle);
          }
          if (openstudio::istringEqual(*subcoolerType, "Mechanical")) {
            return std::make_shared<RefrigerationSubcoolerMechanical_Impl>(object, m, keepHandle);
          }
        }
        return std::make_shared<RefrigerationSubcooler_Impl>(object, m, keepHandle);
      };

#define REGISTER_COPY_CONSTRUCTOR(_iddType, _implClass)                                                                                      \
  m_copyMap[_iddType] = [](openstudio::epmodel::detail::Model_Impl* m, const std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>& ptr, \
                           bool keepHandle) -> std::shared_ptr<openstudio::detail::WorkspaceObject_Impl> {                                   \
    if (auto typed = std::dynamic_pointer_cast<_implClass>(ptr)) {                                                                           \
      return std::make_shared<_implClass>(*typed, m, keepHandle);                                                                            \
    }                                                                                                                                        \
    return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>();                                                                      \
  };

      REGISTER_COPY_CONSTRUCTOR(IddObjectType::AirConditioner_VariableRefrigerantFlow, AirConditionerVariableRefrigerantFlow_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::AirConditioner_VariableRefrigerantFlow_FluidTemperatureControl,
                                AirConditionerVariableRefrigerantFlowFluidTemperatureControl_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::AirConditioner_VariableRefrigerantFlow_FluidTemperatureControl_HR,
                                AirConditionerVariableRefrigerantFlowFluidTemperatureControlHR_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::AirLoopHVAC, AirLoopHVAC_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::AirLoopHVAC_ControllerList, AirLoopHVACControllerList_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::AirLoopHVAC_DedicatedOutdoorAirSystem, AirLoopHVACDedicatedOutdoorAirSystem_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::AirLoopHVAC_ExhaustSystem, AirLoopHVACExhaustSystem_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::AirLoopHVAC_Mixer, AirLoopHVACMixer_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::AirLoopHVAC_OutdoorAirSystem, AirLoopHVACOutdoorAirSystem_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::AirLoopHVAC_OutdoorAirSystem_EquipmentList, AirLoopHVACOutdoorAirSystemEquipmentList_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::AirLoopHVAC_ReturnPath, AirLoopHVACReturnPath_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::AirLoopHVAC_ReturnPlenum, AirLoopHVACReturnPlenum_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::AirLoopHVAC_Splitter, AirLoopHVACSplitter_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::AirLoopHVAC_SupplyPath, AirLoopHVACSupplyPath_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::AirLoopHVAC_SupplyPlenum, AirLoopHVACSupplyPlenum_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::AirLoopHVAC_UnitaryHeatCool, AirLoopHVACUnitaryHeatCool_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::AirLoopHVAC_UnitaryHeatCool_VAVChangeoverBypass, AirLoopHVACUnitaryHeatCoolVAVChangeoverBypass_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::AirLoopHVAC_UnitaryHeatOnly, AirLoopHVACUnitaryHeatOnly_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::AirLoopHVAC_UnitaryHeatPump_AirToAir, AirLoopHVACUnitaryHeatPumpAirToAir_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::AirLoopHVAC_UnitaryHeatPump_AirToAir_MultiSpeed, AirLoopHVACUnitaryHeatPumpAirToAirMultiSpeed_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::AirLoopHVAC_UnitaryHeatPump_WaterToAir, AirLoopHVACUnitaryHeatPumpWaterToAir_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::AirLoopHVAC_UnitarySystem, AirLoopHVACUnitarySystem_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::AirLoopHVAC_Unitary_Furnace_HeatCool, AirLoopHVACUnitaryFurnaceHeatCool_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::AirLoopHVAC_Unitary_Furnace_HeatOnly, AirLoopHVACUnitaryFurnaceHeatOnly_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::AirLoopHVAC_ZoneMixer, AirLoopHVACZoneMixer_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::AirLoopHVAC_ZoneSplitter, AirLoopHVACZoneSplitter_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::AirTerminal_DualDuct_ConstantVolume, AirTerminalDualDuctConstantVolume_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::AirTerminal_DualDuct_VAV, AirTerminalDualDuctVAV_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::AirTerminal_DualDuct_VAV_OutdoorAir, AirTerminalDualDuctVAVOutdoorAir_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::AirTerminal_SingleDuct_ConstantVolume_CooledBeam, AirTerminalSingleDuctConstantVolumeCooledBeam_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::AirTerminal_SingleDuct_ConstantVolume_FourPipeBeam,
                                AirTerminalSingleDuctConstantVolumeFourPipeBeam_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::AirTerminal_SingleDuct_ConstantVolume_FourPipeInduction,
                                AirTerminalSingleDuctConstantVolumeFourPipeInduction_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::AirTerminal_SingleDuct_ConstantVolume_NoReheat, AirTerminalSingleDuctConstantVolumeNoReheat_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::AirTerminal_SingleDuct_ConstantVolume_Reheat, AirTerminalSingleDuctConstantVolumeReheat_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::AirTerminal_SingleDuct_Mixer, AirTerminalSingleDuctInletSideMixer_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::AirTerminal_SingleDuct_ParallelPIU_Reheat, AirTerminalSingleDuctParallelPIUReheat_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::AirTerminal_SingleDuct_SeriesPIU_Reheat, AirTerminalSingleDuctSeriesPIUReheat_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::AirTerminal_SingleDuct_UserDefined, AirTerminalSingleDuctUserDefined_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::AirTerminal_SingleDuct_VAV_HeatAndCool_NoReheat, AirTerminalSingleDuctVAVHeatAndCoolNoReheat_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::AirTerminal_SingleDuct_VAV_HeatAndCool_Reheat, AirTerminalSingleDuctVAVHeatAndCoolReheat_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::AirTerminal_SingleDuct_VAV_NoReheat, AirTerminalSingleDuctVAVNoReheat_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::AirTerminal_SingleDuct_VAV_Reheat, AirTerminalSingleDuctVAVReheat_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::AirTerminal_SingleDuct_VAV_Reheat_VariableSpeedFan,
                                AirTerminalSingleDuctVAVReheatVariableSpeedFan_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::AirflowNetwork_Distribution_Component_Coil, AirflowNetworkDistributionComponentCoil_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::AirflowNetwork_Distribution_Component_ConstantPressureDrop,
                                AirflowNetworkDistributionComponentConstantPressureDrop_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::AirflowNetwork_Distribution_Component_Duct, AirflowNetworkDistributionComponentDuct_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::AirflowNetwork_Distribution_Component_Fan, AirflowNetworkDistributionComponentFan_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::AirflowNetwork_Distribution_Component_HeatExchanger,
                                AirflowNetworkDistributionComponentHeatExchanger_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::AirflowNetwork_Distribution_Component_Leak, AirflowNetworkDistributionComponentLeak_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::AirflowNetwork_Distribution_Component_LeakageRatio,
                                AirflowNetworkDistributionComponentLeakageRatio_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::AirflowNetwork_Distribution_Component_OutdoorAirFlow,
                                AirflowNetworkDistributionComponentOutdoorAirFlow_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::AirflowNetwork_Distribution_Component_ReliefAirFlow,
                                AirflowNetworkDistributionComponentReliefAirFlow_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::AirflowNetwork_Distribution_Component_TerminalUnit,
                                AirflowNetworkDistributionComponentTerminalUnit_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::AirflowNetwork_Distribution_DuctSizing, AirflowNetworkDistributionDuctSizing_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::AirflowNetwork_Distribution_DuctViewFactors, AirflowNetworkDistributionDuctViewFactors_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::AirflowNetwork_Distribution_Linkage, AirflowNetworkDistributionLinkage_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::AirflowNetwork_Distribution_Node, AirflowNetworkDistributionNode_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::AirflowNetwork_IntraZone_Linkage, AirflowNetworkIntraZoneLinkage_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::AirflowNetwork_IntraZone_Node, AirflowNetworkIntraZoneNode_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::AirflowNetwork_MultiZone_Component_DetailedOpening,
                                AirflowNetworkMultiZoneComponentDetailedOpening_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::AirflowNetwork_MultiZone_Component_HorizontalOpening,
                                AirflowNetworkMultiZoneComponentHorizontalOpening_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::AirflowNetwork_MultiZone_Component_SimpleOpening, AirflowNetworkMultiZoneComponentSimpleOpening_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::AirflowNetwork_MultiZone_Component_ZoneExhaustFan,
                                AirflowNetworkMultiZoneComponentZoneExhaustFan_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::AirflowNetwork_MultiZone_ExternalNode, AirflowNetworkMultiZoneExternalNode_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::AirflowNetwork_MultiZone_ReferenceCrackConditions,
                                AirflowNetworkMultiZoneReferenceCrackConditions_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::AirflowNetwork_MultiZone_SpecifiedFlowRate, AirflowNetworkMultiZoneSpecifiedFlowRate_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::AirflowNetwork_MultiZone_Surface, AirflowNetworkMultiZoneSurface_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::AirflowNetwork_MultiZone_Surface_Crack, AirflowNetworkMultiZoneSurfaceCrack_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::AirflowNetwork_MultiZone_Surface_EffectiveLeakageArea,
                                AirflowNetworkMultiZoneSurfaceEffectiveLeakageArea_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::AirflowNetwork_MultiZone_WindPressureCoefficientArray,
                                AirflowNetworkMultiZoneWindPressureCoefficientArray_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::AirflowNetwork_MultiZone_WindPressureCoefficientValues,
                                AirflowNetworkMultiZoneWindPressureCoefficientValues_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::AirflowNetwork_MultiZone_Zone, AirflowNetworkMultiZoneZone_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::AirflowNetwork_OccupantVentilationControl, AirflowNetworkOccupantVentilationControl_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::AirflowNetwork_SimulationControl, AirflowNetworkSimulationControl_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::AirflowNetwork_ZoneControl_PressureController, AirflowNetworkZoneControlPressureController_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::AvailabilityManagerAssignmentList, AvailabilityManagerAssignmentList_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::AvailabilityManager_DifferentialThermostat, AvailabilityManagerDifferentialThermostat_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::AvailabilityManager_HighTemperatureTurnOff, AvailabilityManagerHighTemperatureTurnOff_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::AvailabilityManager_HighTemperatureTurnOn, AvailabilityManagerHighTemperatureTurnOn_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::AvailabilityManager_HybridVentilation, AvailabilityManagerHybridVentilation_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::AvailabilityManager_LowTemperatureTurnOff, AvailabilityManagerLowTemperatureTurnOff_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::AvailabilityManager_LowTemperatureTurnOn, AvailabilityManagerLowTemperatureTurnOn_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::AvailabilityManager_NightCycle, AvailabilityManagerNightCycle_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::AvailabilityManager_NightVentilation, AvailabilityManagerNightVentilation_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::AvailabilityManager_OptimumStart, AvailabilityManagerOptimumStart_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::AvailabilityManager_ScheduledOff, AvailabilityManagerScheduledOff_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::AvailabilityManager_ScheduledOn, AvailabilityManagerScheduledOn_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::Boiler_HotWater, BoilerHotWater_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::Boiler_Steam, BoilerSteam_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::Branch, Branch_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::BranchList, BranchList_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::Building, Building_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::BuildingSurface_Detailed, Surface_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::Ceiling_Adiabatic, CeilingAdiabatic_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::Ceiling_Interzone, CeilingInterzone_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::CentralHeatPumpSystem, CentralHeatPumpSystem_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::ChillerHeaterPerformance_Electric_EIR, ChillerHeaterPerformanceElectricEIR_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::ChillerHeater_Absorption_DirectFired, ChillerHeaterAbsorptionDirectFired_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::ChillerHeater_Absorption_DoubleEffect, ChillerHeaterAbsorptionDoubleEffect_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::Chiller_Absorption, ChillerAbsorption_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::Chiller_Absorption_Indirect, ChillerAbsorptionIndirect_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::Chiller_CombustionTurbine, ChillerCombustionTurbine_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::Chiller_ConstantCOP, ChillerConstantCOP_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::Chiller_Electric, ChillerElectric_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::Chiller_Electric_ASHRAE205, ChillerElectricASHRAE205_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::Chiller_Electric_EIR, ChillerElectricEIR_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::Chiller_Electric_ReformulatedEIR, ChillerElectricReformulatedEIR_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::Chiller_EngineDriven, ChillerEngineDriven_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::CoilPerformance_DX_Cooling, CoilPerformanceDXCooling_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::CoilSystem_Cooling_DX, CoilSystemCoolingDX_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::CoilSystem_Cooling_DX_HeatExchangerAssisted, CoilSystemCoolingDXHeatExchangerAssisted_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::CoilSystem_Cooling_Water, CoilSystemCoolingWater_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::CoilSystem_Cooling_Water_HeatExchangerAssisted, CoilSystemCoolingWaterHeatExchangerAssisted_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::CoilSystem_Heating_DX, CoilSystemHeatingDX_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::CoilSystem_IntegratedHeatPump_AirSource, CoilSystemIntegratedHeatPumpAirSource_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::Coil_Cooling_DX, CoilCoolingDX_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::Coil_Cooling_DX_CurveFit_OperatingMode, CoilCoolingDXCurveFitOperatingMode_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::Coil_Cooling_DX_CurveFit_Performance, CoilCoolingDXCurveFitPerformance_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::Coil_Cooling_DX_CurveFit_Speed, CoilCoolingDXCurveFitSpeed_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::Coil_Cooling_DX_MultiSpeed, CoilCoolingDXMultiSpeed_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::Coil_Cooling_DX_SingleSpeed, CoilCoolingDXSingleSpeed_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::Coil_Cooling_DX_SingleSpeed_ThermalStorage, CoilCoolingDXSingleSpeedThermalStorage_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::Coil_Cooling_DX_TwoSpeed, CoilCoolingDXTwoSpeed_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::Coil_Cooling_DX_TwoStageWithHumidityControlMode, CoilCoolingDXTwoStageWithHumidityControlMode_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::Coil_Cooling_DX_VariableRefrigerantFlow, CoilCoolingDXVariableRefrigerantFlow_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::Coil_Cooling_DX_VariableRefrigerantFlow_FluidTemperatureControl,
                                CoilCoolingDXVariableRefrigerantFlowFluidTemperatureControl_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::Coil_Cooling_DX_VariableSpeed, CoilCoolingDXVariableSpeed_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::Coil_Cooling_Water, CoilCoolingWater_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::Coil_Cooling_WaterToAirHeatPump_EquationFit, CoilCoolingWaterToAirHeatPumpEquationFit_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::Coil_Cooling_WaterToAirHeatPump_ParameterEstimation,
                                CoilCoolingWaterToAirHeatPumpParameterEstimation_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::Coil_Cooling_WaterToAirHeatPump_VariableSpeedEquationFit,
                                CoilCoolingWaterToAirHeatPumpVariableSpeedEquationFit_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::Coil_Cooling_Water_DetailedGeometry, CoilCoolingWaterDetailedGeometry_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::Coil_DX_ASHRAE205_Performance, CoilDXASHRAE205Performance_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::Coil_Heating_DX_MultiSpeed, CoilHeatingDXMultiSpeed_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::Coil_Heating_DX_SingleSpeed, CoilHeatingDXSingleSpeed_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::Coil_Heating_DX_VariableRefrigerantFlow, CoilHeatingDXVariableRefrigerantFlow_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::Coil_Heating_DX_VariableRefrigerantFlow_FluidTemperatureControl,
                                CoilHeatingDXVariableRefrigerantFlowFluidTemperatureControl_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::Coil_Heating_DX_VariableSpeed, CoilHeatingDXVariableSpeed_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::Coil_Heating_Desuperheater, CoilHeatingDesuperheater_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::Coil_Heating_Electric, CoilHeatingElectric_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::Coil_Heating_Electric_MultiStage, CoilHeatingElectricMultiStage_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::Coil_Heating_Fuel, CoilHeatingGas_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::Coil_Heating_Gas_MultiStage, CoilHeatingGasMultiStage_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::Coil_Heating_Steam, CoilHeatingSteam_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::Coil_Heating_Water, CoilHeatingWater_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::Coil_Heating_WaterToAirHeatPump_EquationFit, CoilHeatingWaterToAirHeatPumpEquationFit_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::Coil_Heating_WaterToAirHeatPump_ParameterEstimation,
                                CoilHeatingWaterToAirHeatPumpParameterEstimation_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::Coil_Heating_WaterToAirHeatPump_VariableSpeedEquationFit,
                                CoilHeatingWaterToAirHeatPumpVariableSpeedEquationFit_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::Coil_UserDefined, CoilUserDefined_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::Coil_WaterHeating_AirToWaterHeatPump_Pumped, CoilWaterHeatingAirToWaterHeatPump_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::Coil_WaterHeating_AirToWaterHeatPump_VariableSpeed,
                                CoilWaterHeatingAirToWaterHeatPumpVariableSpeed_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::Coil_WaterHeating_AirToWaterHeatPump_Wrapped, CoilWaterHeatingAirToWaterHeatPumpWrapped_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::Coil_WaterHeating_Desuperheater, CoilWaterHeatingDesuperheater_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::ComfortViewFactorAngles, ComfortViewFactorAngles_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::ComplexFenestrationProperty_SolarAbsorbedLayers, ComplexFenestrationPropertySolarAbsorbedLayers_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::Compliance_Building, ComplianceBuilding_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::ComponentCost_Adjustments, ComponentCostAdjustments_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::ComponentCost_LineItem, ComponentCostLineItem_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::ComponentCost_Reference, ComponentCostReference_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::CondenserEquipmentList, CondenserEquipmentList_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::CondenserEquipmentOperationSchemes, CondenserEquipmentOperationSchemes_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::CondenserLoop, CondenserLoop_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::Connector_Mixer, ConnectorMixer_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::Connector_Splitter, ConnectorSplitter_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::Construction, Construction_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::ConstructionProperty_InternalHeatSource, ConstructionWithInternalSource_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::Construction_AirBoundary, ConstructionAirBoundary_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::Construction_CfactorUndergroundWall, CFactorUndergroundWallConstruction_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::Construction_ComplexFenestrationState, ConstructionComplexFenestrationState_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::Construction_FfactorGroundFloor, FFactorGroundFloorConstruction_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::Construction_WindowDataFile, ConstructionWindowDataFile_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::Construction_WindowEquivalentLayer, ConstructionWindowEquivalentLayer_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::Controller_MechanicalVentilation, ControllerMechanicalVentilation_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::Controller_OutdoorAir, ControllerOutdoorAir_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::Controller_WaterCoil, ControllerWaterCoil_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::ConvergenceLimits, ConvergenceLimits_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::CoolingTowerPerformance_CoolTools, CoolingTowerPerformanceCoolTools_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::CoolingTowerPerformance_YorkCalc, CoolingTowerPerformanceYorkCalc_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::CoolingTower_SingleSpeed, CoolingTowerSingleSpeed_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::CoolingTower_TwoSpeed, CoolingTowerTwoSpeed_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::CoolingTower_VariableSpeed, CoolingTowerVariableSpeed_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::CoolingTower_VariableSpeed_Merkel, CoolingTowerVariableSpeedMerkel_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::CurrencyType, CurrencyType_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::Curve_Bicubic, CurveBicubic_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::Curve_Biquadratic, CurveBiquadratic_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::Curve_ChillerPartLoadWithLift, CurveChillerPartLoadWithLift_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::Curve_Cubic, CurveCubic_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::Curve_CubicLinear, CurveCubicLinear_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::Curve_DoubleExponentialDecay, CurveDoubleExponentialDecay_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::Curve_Exponent, CurveExponent_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::Curve_ExponentialDecay, CurveExponentialDecay_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::Curve_ExponentialSkewNormal, CurveExponentialSkewNormal_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::Curve_FanPressureRise, CurveFanPressureRise_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::Curve_Functional_PressureDrop, CurveFunctionalPressureDrop_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::Curve_Linear, CurveLinear_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::Curve_QuadLinear, CurveQuadLinear_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::Curve_Quadratic, CurveQuadratic_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::Curve_QuadraticLinear, CurveQuadraticLinear_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::Curve_Quartic, CurveQuartic_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::Curve_QuintLinear, CurveQuintLinear_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::Curve_RectangularHyperbola1, CurveRectangularHyperbola1_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::Curve_RectangularHyperbola2, CurveRectangularHyperbola2_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::Curve_Sigmoid, CurveSigmoid_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::Curve_Triquadratic, CurveTriquadratic_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::DaylightingDevice_LightWell, DaylightingDeviceLightWell_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::DaylightingDevice_Shelf, DaylightingDeviceShelf_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::DaylightingDevice_Tubular, DaylightingDeviceTubular_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::Daylighting_DELight_ComplexFenestration, DaylightingDELightComplexFenestration_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::Dehumidifier_Desiccant_NoFans, DehumidifierDesiccantNoFans_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::Dehumidifier_Desiccant_System, DehumidifierDesiccantSystem_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::DemandManagerAssignmentList, DemandManagerAssignmentList_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::DemandManager_ElectricEquipment, DemandManagerElectricEquipment_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::DemandManager_ExteriorLights, DemandManagerExteriorLights_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::DemandManager_Lights, DemandManagerLights_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::DemandManager_Thermostats, DemandManagerThermostats_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::DemandManager_Ventilation, DemandManagerVentilation_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::DesignSpecification_AirTerminal_Sizing, DesignSpecificationAirTerminalSizing_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::DesignSpecification_OutdoorAir, DesignSpecificationOutdoorAir_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::DesignSpecification_OutdoorAir_SpaceList, DesignSpecificationOutdoorAirSpaceList_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::DesignSpecification_ZoneHVAC_Sizing, DesignSpecificationZoneHVACSizing_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::DistrictCooling, DistrictCooling_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::DistrictHeating_Steam, DistrictHeatingSteam_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::DistrictHeating_Water, DistrictHeatingWater_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::Door, Door_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::Door_Interzone, DoorInterzone_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::Duct, Duct_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::Duct_Loss_Conduction, DuctLossConduction_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::Duct_Loss_Leakage, DuctLossLeakage_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::Duct_Loss_MakeupAir, DuctLossMakeupAir_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::ElectricEquipment, ElectricEquipment_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::ElectricEquipment_ITE_AirCooled, ElectricEquipmentITEAirCooled_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::ElectricLoadCenter_Distribution, ElectricLoadCenterDistribution_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::ElectricLoadCenter_Inverter_FunctionOfPower, ElectricLoadCenterInverterFunctionOfPower_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::ElectricLoadCenter_Inverter_LookUpTable, ElectricLoadCenterInverterLookUpTable_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::ElectricLoadCenter_Inverter_PVWatts, ElectricLoadCenterInverterPVWatts_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::ElectricLoadCenter_Inverter_Simple, ElectricLoadCenterInverterSimple_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::ElectricLoadCenter_Storage_Battery, ElectricLoadCenterStorageBattery_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::ElectricLoadCenter_Storage_Converter, ElectricLoadCenterStorageConverter_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::ElectricLoadCenter_Storage_LiIonNMCBattery, ElectricLoadCenterStorageLiIonNMCBattery_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::ElectricLoadCenter_Storage_Simple, ElectricLoadCenterStorageSimple_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::ElectricLoadCenter_Transformer, ElectricLoadCenterTransformer_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::EnergyManagementSystem_Actuator, EnergyManagementSystemActuator_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::EnergyManagementSystem_ConstructionIndexVariable,
                                EnergyManagementSystemConstructionIndexVariable_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::EnergyManagementSystem_CurveOrTableIndexVariable,
                                EnergyManagementSystemCurveOrTableIndexVariable_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::EnergyManagementSystem_GlobalVariable, EnergyManagementSystemGlobalVariable_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::EnergyManagementSystem_InternalVariable, EnergyManagementSystemInternalVariable_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::EnergyManagementSystem_MeteredOutputVariable, EnergyManagementSystemMeteredOutputVariable_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::EnergyManagementSystem_OutputVariable, EnergyManagementSystemOutputVariable_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::EnergyManagementSystem_Program, EnergyManagementSystemProgram_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::EnergyManagementSystem_ProgramCallingManager, EnergyManagementSystemProgramCallingManager_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::EnergyManagementSystem_Sensor, EnergyManagementSystemSensor_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::EnergyManagementSystem_Subroutine, EnergyManagementSystemSubroutine_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::EnergyManagementSystem_TrendVariable, EnergyManagementSystemTrendVariable_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::EnvironmentalImpactFactors, EnvironmentalImpactFactors_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::EvaporativeCooler_Direct_CelDekPad, EvaporativeCoolerDirectCelDekPad_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::EvaporativeCooler_Direct_ResearchSpecial, EvaporativeCoolerDirectResearchSpecial_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::EvaporativeCooler_Indirect_CelDekPad, EvaporativeCoolerIndirectCelDekPad_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::EvaporativeCooler_Indirect_ResearchSpecial, EvaporativeCoolerIndirectResearchSpecial_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::EvaporativeCooler_Indirect_WetCoil, EvaporativeCoolerIndirectWetCoil_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::EvaporativeFluidCooler_SingleSpeed, EvaporativeFluidCoolerSingleSpeed_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::EvaporativeFluidCooler_TwoSpeed, EvaporativeFluidCoolerTwoSpeed_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::Exterior_FuelEquipment, ExteriorFuelEquipment_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::Exterior_Lights, ExteriorLights_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::Exterior_WaterEquipment, ExteriorWaterEquipment_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::ExternalInterface, ExternalInterface_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::ExternalInterface_Actuator, ExternalInterfaceActuator_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::ExternalInterface_FunctionalMockupUnitExport_From_Variable,
                                ExternalInterfaceFunctionalMockupUnitExportFromVariable_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::ExternalInterface_FunctionalMockupUnitExport_To_Actuator,
                                ExternalInterfaceFunctionalMockupUnitExportToActuator_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::ExternalInterface_FunctionalMockupUnitExport_To_Schedule,
                                ExternalInterfaceFunctionalMockupUnitExportToSchedule_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::ExternalInterface_FunctionalMockupUnitExport_To_Variable,
                                ExternalInterfaceFunctionalMockupUnitExportToVariable_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::ExternalInterface_FunctionalMockupUnitImport, ExternalInterfaceFunctionalMockupUnitImport_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::ExternalInterface_FunctionalMockupUnitImport_From_Variable,
                                ExternalInterfaceFunctionalMockupUnitImportFromVariable_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::ExternalInterface_FunctionalMockupUnitImport_To_Actuator,
                                ExternalInterfaceFunctionalMockupUnitImportToActuator_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::ExternalInterface_FunctionalMockupUnitImport_To_Schedule,
                                ExternalInterfaceFunctionalMockupUnitImportToSchedule_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::ExternalInterface_FunctionalMockupUnitImport_To_Variable,
                                ExternalInterfaceFunctionalMockupUnitImportToVariable_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::ExternalInterface_Schedule, ExternalInterfaceSchedule_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::ExternalInterface_Variable, ExternalInterfaceVariable_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::FanPerformance_NightVentilation, FanPerformanceNightVentilation_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::Fan_ComponentModel, FanComponentModel_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::Fan_ConstantVolume, FanConstantVolume_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::Fan_OnOff, FanOnOff_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::Fan_SystemModel, FanSystemModel_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::Fan_VariableVolume, FanVariableVolume_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::Fan_ZoneExhaust, FanZoneExhaust_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::FaultModel_EnthalpySensorOffset_OutdoorAir, FaultModelEnthalpySensorOffsetOutdoorAir_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::FaultModel_EnthalpySensorOffset_ReturnAir, FaultModelEnthalpySensorOffsetReturnAir_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::FaultModel_Fouling_AirFilter, FaultModelFoulingAirFilter_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::FaultModel_Fouling_Boiler, FaultModelFoulingBoiler_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::FaultModel_Fouling_Chiller, FaultModelFoulingChiller_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::FaultModel_Fouling_Coil, FaultModelFoulingCoil_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::FaultModel_Fouling_CoolingTower, FaultModelFoulingCoolingTower_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::FaultModel_Fouling_EvaporativeCooler, FaultModelFoulingEvaporativeCooler_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::FaultModel_HumidistatOffset, FaultModelHumidistatOffset_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::FaultModel_HumiditySensorOffset_OutdoorAir, FaultModelHumiditySensorOffsetOutdoorAir_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::FaultModel_TemperatureSensorOffset_ChillerSupplyWater,
                                FaultModelTemperatureSensorOffsetChillerSupplyWater_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::FaultModel_TemperatureSensorOffset_CoilSupplyAir, FaultModelTemperatureSensorOffsetCoilSupplyAir_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::FaultModel_TemperatureSensorOffset_CondenserSupplyWater,
                                FaultModelTemperatureSensorOffsetCondenserSupplyWater_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::FaultModel_TemperatureSensorOffset_OutdoorAir, FaultModelTemperatureSensorOffsetOutdoorAir_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::FaultModel_TemperatureSensorOffset_ReturnAir, FaultModelTemperatureSensorOffsetReturnAir_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::FaultModel_ThermostatOffset, FaultModelThermostatOffset_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::FenestrationSurface_Detailed, SubSurface_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::Floor_Adiabatic, FloorAdiabatic_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::Floor_Detailed, FloorDetailed_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::Floor_GroundContact, FloorGroundContact_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::Floor_Interzone, FloorInterzone_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::FluidCooler_SingleSpeed, FluidCoolerSingleSpeed_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::FluidCooler_TwoSpeed, FluidCoolerTwoSpeed_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::FluidProperties_Concentration, FluidPropertiesConcentration_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::FluidProperties_GlycolConcentration, FluidPropertiesGlycolConcentration_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::FluidProperties_Name, FluidPropertiesName_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::FluidProperties_Saturated, FluidPropertiesSaturated_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::FluidProperties_Superheated, FluidPropertiesSuperheated_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::FluidProperties_Temperatures, FluidPropertiesTemperatures_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::Foundation_Kiva, FoundationKiva_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::Foundation_Kiva_Settings, FoundationKivaSettings_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::FuelFactors, FuelFactors_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::GasEquipment, GasEquipment_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::Generator_CombustionTurbine, GeneratorCombustionTurbine_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::Generator_FuelCell, GeneratorFuelCell_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::Generator_FuelCell_AirSupply, GeneratorFuelCellAirSupply_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::Generator_FuelCell_AuxiliaryHeater, GeneratorFuelCellAuxiliaryHeater_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::Generator_FuelCell_ElectricalStorage, GeneratorFuelCellElectricalStorage_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::Generator_FuelCell_ExhaustGasToWaterHeatExchanger,
                                GeneratorFuelCellExhaustGasToWaterHeatExchanger_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::Generator_FuelCell_Inverter, GeneratorFuelCellInverter_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::Generator_FuelCell_PowerModule, GeneratorFuelCellPowerModule_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::Generator_FuelCell_StackCooler, GeneratorFuelCellStackCooler_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::Generator_FuelCell_WaterSupply, GeneratorFuelCellWaterSupply_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::Generator_FuelSupply, GeneratorFuelSupply_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::Generator_InternalCombustionEngine, GeneratorInternalCombustionEngine_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::Generator_MicroCHP, GeneratorMicroCHP_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::Generator_MicroCHP_NonNormalizedParameters, GeneratorMicroCHPNonNormalizedParameters_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::Generator_MicroTurbine, GeneratorMicroTurbine_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::Generator_PVWatts, GeneratorPVWatts_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::Generator_Photovoltaic, GeneratorPhotovoltaic_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::Generator_WindTurbine, GeneratorWindTurbine_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::GeometryTransform, GeometryTransform_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::GlazedDoor, GlazedDoor_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::GlazedDoor_Interzone, GlazedDoorInterzone_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::GlobalGeometryRules, GlobalGeometryRules_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::GroundHeatExchanger_HorizontalTrench, GroundHeatExchangerHorizontalTrench_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::GroundHeatExchanger_Pond, GroundHeatExchangerPond_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::GroundHeatExchanger_ResponseFactors, GroundHeatExchangerVertical_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::GroundHeatExchanger_Slinky, GroundHeatExchangerSlinky_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::GroundHeatExchanger_Surface, GroundHeatExchangerSurface_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::GroundHeatExchanger_Vertical_Array, GroundHeatExchangerVerticalArray_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::GroundHeatExchanger_Vertical_Single, GroundHeatExchangerVerticalSingle_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::GroundHeatExchanger_Vertical_Sizing_Rectangle, GroundHeatExchangerVerticalSizingRectangle_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::GroundHeatTransfer_Basement_AutoGrid, GroundHeatTransferBasementAutoGrid_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::GroundHeatTransfer_Basement_BldgData, GroundHeatTransferBasementBldgData_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::GroundHeatTransfer_Basement_ComBldg, GroundHeatTransferBasementComBldg_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::GroundHeatTransfer_Basement_EquivAutoGrid, GroundHeatTransferBasementEquivAutoGrid_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::GroundHeatTransfer_Basement_Insulation, GroundHeatTransferBasementInsulation_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::GroundHeatTransfer_Basement_Interior, GroundHeatTransferBasementInterior_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::GroundHeatTransfer_Basement_ManualGrid, GroundHeatTransferBasementManualGrid_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::GroundHeatTransfer_Basement_MatlProps, GroundHeatTransferBasementMatlProps_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::GroundHeatTransfer_Basement_SimParameters, GroundHeatTransferBasementSimParameters_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::GroundHeatTransfer_Basement_SurfaceProps, GroundHeatTransferBasementSurfaceProps_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::GroundHeatTransfer_Basement_XFACE, GroundHeatTransferBasementXFACE_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::GroundHeatTransfer_Basement_YFACE, GroundHeatTransferBasementYFACE_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::GroundHeatTransfer_Basement_ZFACE, GroundHeatTransferBasementZFACE_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::GroundHeatTransfer_Control, GroundHeatTransferControl_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::GroundHeatTransfer_Slab_AutoGrid, GroundHeatTransferSlabAutoGrid_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::GroundHeatTransfer_Slab_BldgProps, GroundHeatTransferSlabBldgProps_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::GroundHeatTransfer_Slab_BoundConds, GroundHeatTransferSlabBoundConds_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::GroundHeatTransfer_Slab_EquivalentSlab, GroundHeatTransferSlabEquivalentSlab_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::GroundHeatTransfer_Slab_Insulation, GroundHeatTransferSlabInsulation_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::GroundHeatTransfer_Slab_ManualGrid, GroundHeatTransferSlabManualGrid_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::GroundHeatTransfer_Slab_Materials, GroundHeatTransferSlabMaterials_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::GroundHeatTransfer_Slab_MatlProps, GroundHeatTransferSlabMatlProps_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::GroundHeatTransfer_Slab_XFACE, GroundHeatTransferSlabXFACE_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::GroundHeatTransfer_Slab_YFACE, GroundHeatTransferSlabYFACE_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::GroundHeatTransfer_Slab_ZFACE, GroundHeatTransferSlabZFACE_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::HVACSystemRootFindingAlgorithm, HVACSystemRootFindingAlgorithm_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::HVACTemplate_Plant_Boiler, HVACTemplatePlantBoiler_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::HVACTemplate_Plant_Boiler_ObjectReference, HVACTemplatePlantBoilerObjectReference_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::HVACTemplate_Plant_ChilledWaterLoop, HVACTemplatePlantChilledWaterLoop_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::HVACTemplate_Plant_Chiller, HVACTemplatePlantChiller_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::HVACTemplate_Plant_Chiller_ObjectReference, HVACTemplatePlantChillerObjectReference_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::HVACTemplate_Plant_HotWaterLoop, HVACTemplatePlantHotWaterLoop_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::HVACTemplate_Plant_MixedWaterLoop, HVACTemplatePlantMixedWaterLoop_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::HVACTemplate_Plant_Tower, HVACTemplatePlantTower_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::HVACTemplate_Plant_Tower_ObjectReference, HVACTemplatePlantTowerObjectReference_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::HVACTemplate_System_ConstantVolume, HVACTemplateSystemConstantVolume_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::HVACTemplate_System_DedicatedOutdoorAir, HVACTemplateSystemDedicatedOutdoorAir_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::HVACTemplate_System_DualDuct, HVACTemplateSystemDualDuct_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::HVACTemplate_System_PackagedVAV, HVACTemplateSystemPackagedVAV_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::HVACTemplate_System_Unitary, HVACTemplateSystemUnitary_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::HVACTemplate_System_UnitaryHeatPump_AirToAir, HVACTemplateSystemUnitaryHeatPumpAirToAir_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::HVACTemplate_System_UnitarySystem, HVACTemplateSystemUnitarySystem_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::HVACTemplate_System_VAV, HVACTemplateSystemVAV_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::HVACTemplate_System_VRF, HVACTemplateSystemVRF_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::HVACTemplate_Thermostat, HVACTemplateThermostat_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::HVACTemplate_Zone_BaseboardHeat, HVACTemplateZoneBaseboardHeat_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::HVACTemplate_Zone_ConstantVolume, HVACTemplateZoneConstantVolume_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::HVACTemplate_Zone_DualDuct, HVACTemplateZoneDualDuct_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::HVACTemplate_Zone_FanCoil, HVACTemplateZoneFanCoil_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::HVACTemplate_Zone_PTAC, HVACTemplateZonePTAC_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::HVACTemplate_Zone_PTHP, HVACTemplateZonePTHP_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::HVACTemplate_Zone_Unitary, HVACTemplateZoneUnitary_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::HVACTemplate_Zone_VAV, HVACTemplateZoneVAV_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::HVACTemplate_Zone_VAV_FanPowered, HVACTemplateZoneVAVFanPowered_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::HVACTemplate_Zone_VAV_HeatAndCool, HVACTemplateZoneVAVHeatAndCool_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::HVACTemplate_Zone_VRF, HVACTemplateZoneVRF_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::HVACTemplate_Zone_WaterToAirHeatPump, HVACTemplateZoneWaterToAirHeatPump_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::HeaderedPumps_ConstantSpeed, HeaderedPumpsConstantSpeed_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::HeaderedPumps_VariableSpeed, HeaderedPumpsVariableSpeed_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::HeatBalanceAlgorithm, HeatBalanceAlgorithm_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::HeatBalanceSettings_ConductionFiniteDifference, HeatBalanceSettingsConductionFiniteDifference_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::HeatExchanger_AirToAir_FlatPlate, HeatExchangerAirToAirFlatPlate_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::HeatExchanger_AirToAir_SensibleAndLatent, HeatExchangerAirToAirSensibleAndLatent_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::HeatExchanger_Desiccant_BalancedFlow, HeatExchangerDesiccantBalancedFlow_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::HeatExchanger_Desiccant_BalancedFlow_PerformanceDataType1,
                                HeatExchangerDesiccantBalancedFlowPerformanceDataType1_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::HeatExchanger_FluidToFluid, HeatExchangerFluidToFluid_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::HeatPump_AirToWater, HeatPumpAirToWater_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::HeatPump_AirToWater_FuelFired_Cooling, HeatPumpAirToWaterFuelFiredCooling_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::HeatPump_AirToWater_FuelFired_Heating, HeatPumpAirToWaterFuelFiredHeating_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::HeatPump_PlantLoop_EIR_Cooling, HeatPumpPlantLoopEIRCooling_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::HeatPump_PlantLoop_EIR_Heating, HeatPumpPlantLoopEIRHeating_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::HeatPump_WaterToWater_EquationFit_Cooling, HeatPumpWaterToWaterEquationFitCooling_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::HeatPump_WaterToWater_EquationFit_Heating, HeatPumpWaterToWaterEquationFitHeating_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::HeatPump_WaterToWater_ParameterEstimation_Cooling,
                                HeatPumpWaterToWaterParameterEstimationCooling_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::HeatPump_WaterToWater_ParameterEstimation_Heating,
                                HeatPumpWaterToWaterParameterEstimationHeating_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::HotWaterEquipment, HotWaterEquipment_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::Humidifier_Steam_Electric, HumidifierSteamElectric_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::Humidifier_Steam_Gas, HumidifierSteamGas_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::HybridModel_Zone, HybridModelZone_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::IndoorLivingWall, IndoorLivingWall_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::InternalMass, InteriorPartitionSurface_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::LifeCycleCost_NonrecurringCost, LifeCycleCost_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::LifeCycleCost_Parameters, LifeCycleCostParameters_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::LifeCycleCost_RecurringCosts, LifeCycleCost_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::LifeCycleCost_UseAdjustment, LifeCycleCostUseAdjustment_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::LifeCycleCost_UsePriceEscalation, LifeCycleCostUsePriceEscalation_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::Lights, Lights_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::LoadProfile_Plant, LoadProfilePlant_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::Material, StandardOpaqueMaterial_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::MaterialProperty_GlazingSpectralData, MaterialPropertyGlazingSpectralData_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::MaterialProperty_HeatAndMoistureTransfer_Diffusion,
                                MaterialPropertyHeatAndMoistureTransferDiffusion_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::MaterialProperty_HeatAndMoistureTransfer_Redistribution,
                                MaterialPropertyHeatAndMoistureTransferRedistribution_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::MaterialProperty_HeatAndMoistureTransfer_Settings,
                                MaterialPropertyHeatAndMoistureTransferSettings_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::MaterialProperty_HeatAndMoistureTransfer_SorptionIsotherm,
                                MaterialPropertyHeatAndMoistureTransferSorptionIsotherm_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::MaterialProperty_HeatAndMoistureTransfer_Suction, MaterialPropertyHeatAndMoistureTransferSuction_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::MaterialProperty_HeatAndMoistureTransfer_ThermalConductivity,
                                MaterialPropertyHeatAndMoistureTransferThermalConductivity_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::MaterialProperty_MoisturePenetrationDepth_Settings,
                                MaterialPropertyMoisturePenetrationDepthSettings_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::MaterialProperty_PhaseChange, MaterialPropertyPhaseChange_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::MaterialProperty_PhaseChangeHysteresis, MaterialPropertyPhaseChangeHysteresis_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::MaterialProperty_VariableAbsorptance, MaterialPropertyVariableAbsorptance_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::MaterialProperty_VariableThermalConductivity, MaterialPropertyVariableThermalConductivity_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::Material_AirGap, AirGap_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::Material_InfraredTransparent, InfraredTransparentMaterial_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::Material_NoMass, MasslessOpaqueMaterial_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::Material_RoofVegetation, RoofVegetation_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::Matrix_TwoDimension, MatrixTwoDimension_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::Meter_Custom, MeterCustom_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::Meter_CustomDecrement, MeterCustomDecrement_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::Node, Node_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::NodeList, NodeList_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::OtherEquipment, OtherEquipment_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::OutdoorAir_Mixer, OutdoorAirMixer_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::OutputControl_Files, OutputControlFiles_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::OutputControl_IlluminanceMap_Style, OutputControlIlluminanceMapStyle_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::OutputControl_ReportingTolerances, OutputControlReportingTolerances_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::OutputControl_ResilienceSummaries, OutputControlResilienceSummaries_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::OutputControl_Sizing_Style, OutputControlSizingStyle_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::OutputControl_SurfaceColorScheme, OutputControlSurfaceColorScheme_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::OutputControl_Table_Style, OutputControlTableStyle_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::OutputControl_Timestamp, OutputControlTimestamp_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::Output_Constructions, OutputConstructions_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::Output_DaylightFactors, OutputDaylightFactors_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::Output_DebuggingData, OutputDebuggingData_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::Output_Diagnostics, OutputDiagnostics_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::Output_EnergyManagementSystem, OutputEnergyManagementSystem_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::Output_EnvironmentalImpactFactors, OutputEnvironmentalImpactFactors_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::Output_JSON, OutputJSON_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::Output_Meter, OutputMeter_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::Output_Meter_Cumulative, OutputMeterCumulative_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::Output_Meter_Cumulative_MeterFileOnly, OutputMeterCumulativeMeterFileOnly_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::Output_Meter_MeterFileOnly, OutputMeterMeterFileOnly_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::Output_PreprocessorMessage, OutputPreprocessorMessage_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::Output_SQLite, OutputSQLite_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::Output_Schedules, OutputSchedules_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::Output_Surfaces_Drawing, OutputSurfacesDrawing_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::Output_Surfaces_List, OutputSurfacesList_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::Output_Table_Annual, OutputTableAnnual_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::Output_Table_Monthly, OutputTableMonthly_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::Output_Table_ReportPeriod, OutputTableReportPeriod_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::Output_Table_SummaryReports, OutputTableSummaryReports_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::Output_Table_TimeBins, OutputTableTimeBins_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::Output_Variable, OutputVariable_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::Output_VariableDictionary, OutputVariableDictionary_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::Parametric_FileNameSuffix, ParametricFileNameSuffix_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::Parametric_Logic, ParametricLogic_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::Parametric_RunControl, ParametricRunControl_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::Parametric_SetValueForRun, ParametricSetValueForRun_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::People, People_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::PerformancePrecisionTradeoffs, PerformancePrecisionTradeoffs_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::PhotovoltaicPerformance_Sandia, PhotovoltaicPerformanceSandia_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::PhotovoltaicPerformance_Simple, PhotovoltaicPerformanceSimple_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::Pipe_Adiabatic, PipeAdiabatic_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::Pipe_Adiabatic_Steam, PipeAdiabaticSteam_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::Pipe_Indoor, PipeIndoor_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::Pipe_Outdoor, PipeOutdoor_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::Pipe_Underground, PipeUnderground_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::PipingSystem_Underground_Domain, PipingSystemUndergroundDomain_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::PipingSystem_Underground_PipeCircuit, PipingSystemUndergroundPipeCircuit_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::PipingSystem_Underground_PipeSegment, PipingSystemUndergroundPipeSegment_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::PlantComponent_TemperatureSource, PlantComponentTemperatureSource_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::PlantComponent_UserDefined, PlantComponentUserDefined_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::PlantEquipmentOperationSchemes, PlantEquipmentOperationSchemes_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::PlantEquipmentOperation_ChillerHeaterChangeover, PlantEquipmentOperationChillerHeaterChangeover_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::PlantEquipmentOperation_ComponentSetpoint, PlantEquipmentOperationComponentSetpoint_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::PlantEquipmentOperation_CoolingLoad, PlantEquipmentOperationCoolingLoad_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::PlantEquipmentOperation_HeatingLoad, PlantEquipmentOperationHeatingLoad_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::PlantEquipmentOperation_OutdoorDewpoint, PlantEquipmentOperationOutdoorDewpoint_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::PlantEquipmentOperation_OutdoorDewpointDifference,
                                PlantEquipmentOperationOutdoorDewpointDifference_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::PlantEquipmentOperation_OutdoorDryBulb, PlantEquipmentOperationOutdoorDryBulb_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::PlantEquipmentOperation_OutdoorDryBulbDifference,
                                PlantEquipmentOperationOutdoorDryBulbDifference_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::PlantEquipmentOperation_OutdoorRelativeHumidity, PlantEquipmentOperationOutdoorRelativeHumidity_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::PlantEquipmentOperation_OutdoorWetBulb, PlantEquipmentOperationOutdoorWetBulb_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::PlantEquipmentOperation_OutdoorWetBulbDifference,
                                PlantEquipmentOperationOutdoorWetBulbDifference_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::PlantEquipmentOperation_ThermalEnergyStorage, PlantEquipmentOperationThermalEnergyStorage_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::PlantEquipmentOperation_Uncontrolled, PlantEquipmentOperationUncontrolled_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::PlantEquipmentOperation_UserDefined, PlantEquipmentOperationUserDefined_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::PlantLoop, PlantLoop_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::Pump_ConstantSpeed, PumpConstantSpeed_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::Pump_VariableSpeed, PumpVariableSpeed_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::Pump_VariableSpeed_Condensate, PumpVariableSpeedCondensate_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::PythonPlugin_Instance, PythonPluginInstance_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::PythonPlugin_OutputVariable, PythonPluginOutputVariable_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::PythonPlugin_SearchPaths, PythonPluginSearchPaths_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::PythonPlugin_TrendVariable, PythonPluginTrendVariable_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::PythonPlugin_Variables, PythonPluginVariable_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::Refrigeration_AirChiller, RefrigerationAirChiller_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::Refrigeration_Case, RefrigerationCase_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::Refrigeration_Compressor, RefrigerationCompressor_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::Refrigeration_CompressorRack, RefrigerationCompressorRack_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::Refrigeration_Condenser_AirCooled, RefrigerationCondenserAirCooled_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::Refrigeration_Condenser_Cascade, RefrigerationCondenserCascade_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::Refrigeration_Condenser_EvaporativeCooled, RefrigerationCondenserEvaporativeCooled_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::Refrigeration_Condenser_WaterCooled, RefrigerationCondenserWaterCooled_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::Refrigeration_GasCooler_AirCooled, RefrigerationGasCoolerAirCooled_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::Refrigeration_SecondarySystem, RefrigerationSecondarySystem_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::Refrigeration_System, RefrigerationSystem_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::Refrigeration_TranscriticalSystem, RefrigerationTranscriticalSystem_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::Refrigeration_WalkIn, RefrigerationWalkIn_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::Roof, Roof_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::RoofCeiling_Detailed, RoofCeilingDetailed_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::RoofIrrigation, RoofIrrigation_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::RoomAirModelType, RoomAirModelType_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::RoomAirSettings_AirflowNetwork, RoomAirSettingsAirflowNetwork_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::RoomAirSettings_CrossVentilation, RoomAirSettingsCrossVentilation_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::RoomAirSettings_OneNodeDisplacementVentilation, RoomAirSettingsOneNodeDisplacementVentilation_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::RoomAirSettings_ThreeNodeDisplacementVentilation,
                                RoomAirSettingsThreeNodeDisplacementVentilation_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::RoomAirSettings_UnderFloorAirDistributionExterior,
                                RoomAirSettingsUnderFloorAirDistributionExterior_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::RoomAirSettings_UnderFloorAirDistributionInterior,
                                RoomAirSettingsUnderFloorAirDistributionInterior_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::RoomAir_Node, RoomAirNode_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::RoomAir_Node_AirflowNetwork, RoomAirNodeAirflowNetwork_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::RoomAir_Node_AirflowNetwork_AdjacentSurfaceList, RoomAirNodeAirflowNetworkAdjacentSurfaceList_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::RoomAir_Node_AirflowNetwork_HVACEquipment, RoomAirNodeAirflowNetworkHVACEquipment_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::RoomAir_Node_AirflowNetwork_InternalGains, RoomAirNodeAirflowNetworkInternalGains_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::RoomAir_TemperaturePattern_ConstantGradient, RoomAirTemperaturePatternConstantGradient_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::RoomAir_TemperaturePattern_NondimensionalHeight, RoomAirTemperaturePatternNondimensionalHeight_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::RoomAir_TemperaturePattern_SurfaceMapping, RoomAirTemperaturePatternSurfaceMapping_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::RoomAir_TemperaturePattern_TwoGradient, RoomAirTemperaturePatternTwoGradient_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::RoomAir_TemperaturePattern_UserDefined, RoomAirTemperaturePatternUserDefined_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::RunPeriod, RunPeriod_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::RunPeriodControl_DaylightSavingTime, RunPeriodControlDaylightSavingTime_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::RunPeriodControl_SpecialDays, RunPeriodControlSpecialDays_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::ScheduleTypeLimits, ScheduleTypeLimits_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::Schedule_Compact, ScheduleCompact_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::Schedule_Constant, ScheduleConstant_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::Schedule_Day_Hourly, ScheduleDayHourly_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::Schedule_Day_Interval, ScheduleDay_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::Schedule_Day_List, ScheduleDayList_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::Schedule_File, ScheduleFile_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::Schedule_File_Shading, ScheduleFileShading_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::Schedule_Week_Compact, ScheduleWeekCompact_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::Schedule_Week_Daily, ScheduleWeek_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::Schedule_Year, ScheduleYear_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::SetpointManager_Coldest, SetpointManagerColdest_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::SetpointManager_CondenserEnteringReset, SetpointManagerCondenserEnteringReset_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::SetpointManager_CondenserEnteringReset_Ideal, SetpointManagerCondenserEnteringResetIdeal_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::SetpointManager_FollowGroundTemperature, SetpointManagerFollowGroundTemperature_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::SetpointManager_FollowOutdoorAirTemperature, SetpointManagerFollowOutdoorAirTemperature_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::SetpointManager_FollowSystemNodeTemperature, SetpointManagerFollowSystemNodeTemperature_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::SetpointManager_MixedAir, SetpointManagerMixedAir_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::SetpointManager_MultiZone_Cooling_Average, SetpointManagerMultiZoneCoolingAverage_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::SetpointManager_MultiZone_Heating_Average, SetpointManagerMultiZoneHeatingAverage_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::SetpointManager_MultiZone_Humidity_Maximum, SetpointManagerMultiZoneHumidityMaximum_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::SetpointManager_MultiZone_Humidity_Minimum, SetpointManagerMultiZoneHumidityMinimum_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::SetpointManager_MultiZone_MaximumHumidity_Average,
                                SetpointManagerMultiZoneMaximumHumidityAverage_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::SetpointManager_MultiZone_MinimumHumidity_Average,
                                SetpointManagerMultiZoneMinimumHumidityAverage_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::SetpointManager_OutdoorAirPretreat, SetpointManagerOutdoorAirPretreat_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::SetpointManager_OutdoorAirReset, SetpointManagerOutdoorAirReset_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::SetpointManager_ReturnAirBypassFlow, SetpointManagerReturnAirBypassFlow_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::SetpointManager_ReturnTemperature_ChilledWater, SetpointManagerReturnTemperatureChilledWater_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::SetpointManager_ReturnTemperature_HotWater, SetpointManagerReturnTemperatureHotWater_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::SetpointManager_Scheduled, SetpointManagerScheduled_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::SetpointManager_Scheduled_DualSetpoint, SetpointManagerScheduledDualSetpoint_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::SetpointManager_SingleZone_Cooling, SetpointManagerSingleZoneCooling_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::SetpointManager_SingleZone_Heating, SetpointManagerSingleZoneHeating_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::SetpointManager_SingleZone_Humidity_Maximum, SetpointManagerSingleZoneHumidityMaximum_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::SetpointManager_SingleZone_Humidity_Minimum, SetpointManagerSingleZoneHumidityMinimum_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::SetpointManager_SingleZone_OneStageCooling, SetpointManagerSingleZoneOneStageCooling_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::SetpointManager_SingleZone_OneStageHeating, SetpointManagerSingleZoneOneStageHeating_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::SetpointManager_SingleZone_Reheat, SetpointManagerSingleZoneReheat_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::SetpointManager_SystemNodeReset_Humidity, SetpointManagerSystemNodeResetHumidity_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::SetpointManager_SystemNodeReset_Temperature, SetpointManagerSystemNodeResetTemperature_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::SetpointManager_Warmest, SetpointManagerWarmest_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::SetpointManager_WarmestTemperatureFlow, SetpointManagerWarmestTemperatureFlow_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::ShadingProperty_Reflectance, ShadingPropertyReflectance_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::Shading_Building, ShadingBuilding_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::Shading_Building_Detailed, ShadingBuildingDetailed_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::Shading_Fin, ShadingFin_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::Shading_Fin_Projection, ShadingFinProjection_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::Shading_Overhang, ShadingOverhang_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::Shading_Overhang_Projection, ShadingOverhangProjection_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::Shading_Site, ShadingSite_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::Shading_Site_Detailed, ShadingSiteDetailed_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::Shading_Zone_Detailed, ShadingZoneDetailed_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::ShadowCalculation, ShadowCalculation_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::SimulationControl, SimulationControl_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::Site_GroundDomain_Basement, SiteGroundDomainBasement_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::Site_GroundDomain_Slab, SiteGroundDomainSlab_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::Site_GroundReflectance, SiteGroundReflectance_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::Site_GroundReflectance_SnowModifier, SiteGroundReflectanceSnowModifier_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::Site_GroundTemperature_BuildingSurface, SiteGroundTemperatureBuildingSurface_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::Site_GroundTemperature_Deep, SiteGroundTemperatureDeep_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::Site_GroundTemperature_FCfactorMethod, SiteGroundTemperatureFCfactorMethod_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::Site_GroundTemperature_Shallow, SiteGroundTemperatureShallow_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::Site_GroundTemperature_Undisturbed_FiniteDifference,
                                SiteGroundTemperatureUndisturbedFiniteDifference_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::Site_GroundTemperature_Undisturbed_KusudaAchenbach,
                                SiteGroundTemperatureUndisturbedKusudaAchenbach_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::Site_GroundTemperature_Undisturbed_Xing, SiteGroundTemperatureUndisturbedXing_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::Site_HeightVariation, SiteHeightVariation_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::Site_Location, Site_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::Site_Precipitation, SitePrecipitation_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::Site_SolarAndVisibleSpectrum, SiteSolarAndVisibleSpectrum_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::Site_SpectrumData, SiteSpectrumData_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::Site_VariableLocation, SiteVariableLocation_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::Site_WaterMainsTemperature, SiteWaterMainsTemperature_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::Site_WeatherStation, SiteWeatherStation_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::SizingPeriod_DesignDay, DesignDay_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::SizingPeriod_WeatherFileConditionType, SizingPeriodWeatherFileConditionType_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::SizingPeriod_WeatherFileDays, SizingPeriodWeatherFileDays_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::Sizing_Parameters, SizingParameters_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::Sizing_Plant, SizingPlant_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::Sizing_System, SizingSystem_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::Sizing_Zone, SizingZone_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::SolarCollectorPerformance_FlatPlate, SolarCollectorPerformanceFlatPlate_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::SolarCollectorPerformance_IntegralCollectorStorage,
                                SolarCollectorPerformanceIntegralCollectorStorage_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::SolarCollectorPerformance_PhotovoltaicThermal_BIPVT,
                                SolarCollectorPerformancePhotovoltaicThermalBIPVT_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::SolarCollectorPerformance_PhotovoltaicThermal_Simple,
                                SolarCollectorPerformancePhotovoltaicThermalSimple_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::SolarCollector_FlatPlate_PhotovoltaicThermal, SolarCollectorFlatPlatePhotovoltaicThermal_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::SolarCollector_FlatPlate_Water, SolarCollectorFlatPlateWater_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::SolarCollector_IntegralCollectorStorage, SolarCollectorIntegralCollectorStorage_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::SolarCollector_UnglazedTranspired, SolarCollectorUnglazedTranspired_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::SolarCollector_UnglazedTranspired_Multisystem, SolarCollectorUnglazedTranspiredMultisystem_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::Space, Space_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::SpaceHVAC_EquipmentConnections, SpaceHVACEquipmentConnections_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::SpaceHVAC_ZoneEquipmentMixer, SpaceHVACZoneEquipmentMixer_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::SpaceHVAC_ZoneEquipmentSplitter, SpaceHVACZoneEquipmentSplitter_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::SpaceHVAC_ZoneReturnMixer, SpaceHVACZoneReturnMixer_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::SpaceList, SpaceType_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::SteamEquipment, SteamEquipment_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::SurfaceContaminantSourceAndSink_Generic_BoundaryLayerDiffusion,
                                SurfaceContaminantSourceAndSinkGenericBoundaryLayerDiffusion_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::SurfaceContaminantSourceAndSink_Generic_DepositionVelocitySink,
                                SurfaceContaminantSourceAndSinkGenericDepositionVelocitySink_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::SurfaceContaminantSourceAndSink_Generic_PressureDriven,
                                SurfaceContaminantSourceAndSinkGenericPressureDriven_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::SurfaceControl_MovableInsulation, SurfaceControlMovableInsulation_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::SurfaceConvectionAlgorithm_Inside, InsideSurfaceConvectionAlgorithm_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::SurfaceConvectionAlgorithm_Inside_AdaptiveModelSelections,
                                SurfaceConvectionAlgorithmInsideAdaptiveModelSelections_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::SurfaceConvectionAlgorithm_Inside_UserCurve, SurfaceConvectionAlgorithmInsideUserCurve_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::SurfaceConvectionAlgorithm_Outside, OutsideSurfaceConvectionAlgorithm_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::SurfaceConvectionAlgorithm_Outside_AdaptiveModelSelections,
                                SurfaceConvectionAlgorithmOutsideAdaptiveModelSelections_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::SurfaceConvectionAlgorithm_Outside_UserCurve, SurfaceConvectionAlgorithmOutsideUserCurve_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::SurfaceProperties_VaporCoefficients, SurfacePropertiesVaporCoefficients_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::SurfaceProperty_ConvectionCoefficients, SurfacePropertyConvectionCoefficients_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::SurfaceProperty_ConvectionCoefficients_MultipleSurface,
                                SurfacePropertyConvectionCoefficientsMultipleSurface_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::SurfaceProperty_ExposedFoundationPerimeter, SurfacePropertyExposedFoundationPerimeter_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::SurfaceProperty_ExteriorNaturalVentedCavity, SurfacePropertyExteriorNaturalVentedCavity_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::SurfaceProperty_GroundSurfaces, SurfacePropertyGroundSurfaces_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::SurfaceProperty_HeatBalanceSourceTerm, SurfacePropertyHeatBalanceSourceTerm_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::SurfaceProperty_HeatTransferAlgorithm, SurfacePropertyHeatTransferAlgorithm_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::SurfaceProperty_HeatTransferAlgorithm_Construction,
                                SurfacePropertyHeatTransferAlgorithmConstruction_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::SurfaceProperty_HeatTransferAlgorithm_MultipleSurface,
                                SurfacePropertyHeatTransferAlgorithmMultipleSurface_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::SurfaceProperty_HeatTransferAlgorithm_SurfaceList,
                                SurfacePropertyHeatTransferAlgorithmSurfaceList_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::SurfaceProperty_IncidentSolarMultiplier, SurfacePropertyIncidentSolarMultiplier_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::SurfaceProperty_LocalEnvironment, SurfacePropertyLocalEnvironment_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::SurfaceProperty_OtherSideCoefficients, SurfacePropertyOtherSideCoefficients_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::SurfaceProperty_OtherSideConditionsModel, SurfacePropertyOtherSideConditionsModel_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::SurfaceProperty_SolarIncidentInside, SurfacePropertySolarIncidentInside_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::SurfaceProperty_SurroundingSurfaces, SurfacePropertySurroundingSurfaces_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::SurfaceProperty_Underwater, SurfacePropertyUnderwater_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::SwimmingPool_Indoor, SwimmingPoolIndoor_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::Table_IndependentVariable, TableIndependentVariable_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::Table_Lookup, TableLookup_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::TemperingValve, TemperingValve_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::ThermalStorage_ChilledWater_Mixed, ThermalStorageChilledWaterMixed_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::ThermalStorage_ChilledWater_Stratified, ThermalStorageChilledWaterStratified_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::ThermalStorage_HotWater_Stratified, ThermalStorageHotWaterStratified_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::ThermalStorage_Ice_Detailed, ThermalStorageIceDetailed_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::ThermalStorage_Ice_Simple, ThermalStorageIceSimple_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::ThermalStorage_PCM, ThermalStoragePCM_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::ThermalStorage_Sizing, ThermalStorageSizing_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::ThermostatSetpoint_DualSetpoint, ThermostatSetpointDualSetpoint_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::ThermostatSetpoint_SingleCooling, ThermostatSetpointDualSetpoint_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::ThermostatSetpoint_SingleHeating, ThermostatSetpointDualSetpoint_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::ThermostatSetpoint_SingleHeatingOrCooling, ThermostatSetpointSingleHeatingOrCooling_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::ThermostatSetpoint_ThermalComfort_Fanger_DualSetpoint,
                                ThermostatSetpointThermalComfortFangerDualSetpoint_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::ThermostatSetpoint_ThermalComfort_Fanger_SingleCooling,
                                ThermostatSetpointThermalComfortFangerSingleCooling_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::ThermostatSetpoint_ThermalComfort_Fanger_SingleHeating,
                                ThermostatSetpointThermalComfortFangerSingleHeating_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::ThermostatSetpoint_ThermalComfort_Fanger_SingleHeatingOrCooling,
                                ThermostatSetpointThermalComfortFangerSingleHeatingOrCooling_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::Timestep, Timestep_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::UtilityCost_Charge_Block, UtilityCostChargeBlock_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::UtilityCost_Charge_Simple, UtilityCostChargeSimple_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::UtilityCost_Qualify, UtilityCostQualify_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::UtilityCost_Ratchet, UtilityCostRatchet_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::UtilityCost_Tariff, UtilityCostTariff_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::UtilityCost_Variable, UtilityCostVariable_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::Version, Version_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::Wall_Adiabatic, WallAdiabatic_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::Wall_Detailed, WallDetailed_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::Wall_Exterior, WallExterior_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::Wall_Interzone, WallInterzone_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::Wall_Underground, WallUnderground_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::WaterHeater_HeatPump_PumpedCondenser, WaterHeaterHeatPump_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::WaterHeater_HeatPump_WrappedCondenser, WaterHeaterHeatPumpWrappedCondenser_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::WaterHeater_Mixed, WaterHeaterMixed_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::WaterHeater_Sizing, WaterHeaterSizing_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::WaterHeater_Stratified, WaterHeaterStratified_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::WaterUse_Connections, WaterUseConnections_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::WaterUse_Equipment, WaterUseEquipment_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::WaterUse_RainCollector, WaterUseRainCollector_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::WaterUse_Storage, WaterUseStorage_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::WaterUse_Well, WaterUseWell_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::WeatherProperty_SkyTemperature, SkyTemperature_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::Window, Window_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::WindowGap_DeflectionState, WindowGapDeflectionState_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::WindowGap_SupportPillar, WindowGapSupportPillar_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::WindowMaterial_Blind, Blind_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::WindowMaterial_Blind_EquivalentLayer, WindowMaterialBlindEquivalentLayer_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::WindowMaterial_Screen, Screen_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::WindowMaterial_Shade, Shade_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::WindowMaterial_ComplexShade, WindowMaterialComplexShade_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::WindowMaterial_Drape_EquivalentLayer, WindowMaterialDrapeEquivalentLayer_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::WindowMaterial_Gap, WindowMaterialGap_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::WindowMaterial_Gap_EquivalentLayer, WindowMaterialGapEquivalentLayer_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::WindowMaterial_Gas, Gas_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::WindowMaterial_GasMixture, GasMixture_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::WindowMaterial_Glazing, StandardGlazing_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::WindowMaterial_GlazingGroup_Thermochromic, ThermochromicGlazing_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::WindowMaterial_Glazing_EquivalentLayer, WindowMaterialGlazingEquivalentLayer_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::WindowMaterial_Glazing_RefractionExtinctionMethod, RefractionExtinctionGlazing_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::WindowMaterial_Screen_EquivalentLayer, WindowMaterialScreenEquivalentLayer_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::WindowMaterial_Shade_EquivalentLayer, WindowMaterialShadeEquivalentLayer_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::WindowMaterial_SimpleGlazingSystem, SimpleGlazing_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::WindowProperty_AirflowControl, WindowPropertyAirflowControl_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::WindowProperty_FrameAndDivider, WindowPropertyFrameAndDivider_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::WindowProperty_StormWindow, WindowPropertyStormWindow_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::WindowShadingControl, ShadingControl_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::WindowThermalModel_Params, WindowThermalModelParams_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::Window_Interzone, WindowInterzone_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::WindowsCalculationEngine, WindowsCalculationEngine_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::Zone, ThermalZone_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::ZoneAirBalance_OutdoorAir, ZoneAirBalanceOutdoorAir_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::ZoneAirContaminantBalance, ZoneAirContaminantBalance_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::ZoneAirHeatBalanceAlgorithm, ZoneAirHeatBalanceAlgorithm_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::ZoneAirMassFlowConservation, ZoneAirMassFlowConservation_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::ZoneBaseboard_OutdoorTemperatureControlled, ZoneBaseboardOutdoorTemperatureControlled_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::ZoneCapacitanceMultiplier_ResearchSpecial, ZoneCapacitanceMultiplierResearchSpecial_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::ZoneContaminantSourceAndSink_CarbonDioxide, ZoneContaminantSourceAndSinkCarbonDioxide_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::ZoneContaminantSourceAndSink_Generic_Constant, ZoneContaminantSourceAndSinkGenericConstant_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::ZoneContaminantSourceAndSink_Generic_CutoffModel, ZoneContaminantSourceAndSinkGenericCutoffModel_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::ZoneContaminantSourceAndSink_Generic_DecaySource, ZoneContaminantSourceAndSinkGenericDecaySource_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::ZoneContaminantSourceAndSink_Generic_DepositionRateSink,
                                ZoneContaminantSourceAndSinkGenericDepositionRateSink_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::ZoneControl_ContaminantController, ZoneControlContaminantController_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::ZoneControl_Humidistat, ZoneControlHumidistat_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::ZoneControl_Thermostat_OperativeTemperature, ZoneControlThermostatOperativeTemperature_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::ZoneControl_Thermostat_StagedDualSetpoint, ZoneControlThermostatStagedDualSetpoint_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::ZoneControl_Thermostat_TemperatureAndHumidity, ZoneControlThermostatTemperatureAndHumidity_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::ZoneControl_Thermostat_ThermalComfort, ZoneControlThermostatThermalComfort_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::ZoneCoolTower_Shower, ZoneCoolTowerShower_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::ZoneCrossMixing, ZoneCrossMixing_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::ZoneEarthtube, ZoneEarthtube_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::ZoneGroup, ZoneGroup_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::ZoneHVAC_AirDistributionUnit, ZoneHVACAirDistributionUnit_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::ZoneHVAC_Baseboard_Convective_Electric, ZoneHVACBaseboardConvectiveElectric_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::ZoneHVAC_Baseboard_Convective_Water, ZoneHVACBaseboardConvectiveWater_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::ZoneHVAC_Baseboard_RadiantConvective_Electric, ZoneHVACBaseboardRadiantConvectiveElectric_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::ZoneHVAC_Baseboard_RadiantConvective_Steam, ZoneHVACBaseboardRadiantConvectiveSteam_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::ZoneHVAC_Baseboard_RadiantConvective_Steam_Design, ZoneHVACBaseboardRadiantConvectiveSteamDesign_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::ZoneHVAC_Baseboard_RadiantConvective_Water, ZoneHVACBaseboardRadiantConvectiveWater_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::ZoneHVAC_Baseboard_RadiantConvective_Water_Design, ZoneHVACBaseboardRadiantConvectiveWaterDesign_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::ZoneHVAC_CoolingPanel_RadiantConvective_Water, ZoneHVACCoolingPanelRadiantConvectiveWater_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::ZoneHVAC_Dehumidifier_DX, ZoneHVACDehumidifierDX_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::ZoneHVAC_EnergyRecoveryVentilator, ZoneHVACEnergyRecoveryVentilator_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::ZoneHVAC_EnergyRecoveryVentilator_Controller, ZoneHVACEnergyRecoveryVentilatorController_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::ZoneHVAC_EquipmentConnections, ZoneHVACEquipmentConnections_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::ZoneHVAC_EquipmentList, ZoneHVACEquipmentList_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::ZoneHVAC_EvaporativeCoolerUnit, ZoneHVACEvaporativeCoolerUnit_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::ZoneHVAC_ExhaustControl, ZoneHVACExhaustControl_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::ZoneHVAC_ForcedAir_UserDefined, ZoneHVACForcedAirUserDefined_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::ZoneHVAC_FourPipeFanCoil, ZoneHVACFourPipeFanCoil_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::ZoneHVAC_HighTemperatureRadiant, ZoneHVACHighTemperatureRadiant_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::ZoneHVAC_HybridUnitaryHVAC, ZoneHVACHybridUnitaryHVAC_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::ZoneHVAC_IdealLoadsAirSystem, ZoneHVACIdealLoadsAirSystem_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::ZoneHVAC_LowTemperatureRadiant_ConstantFlow, ZoneHVACLowTempRadiantConstFlow_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::ZoneHVAC_LowTemperatureRadiant_Electric, ZoneHVACLowTemperatureRadiantElectric_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::ZoneHVAC_LowTemperatureRadiant_VariableFlow, ZoneHVACLowTempRadiantVarFlow_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::ZoneHVAC_LowTemperatureRadiant_VariableFlow_Design, ZoneHVACLowTempRadiantVarFlow_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::ZoneHVAC_OutdoorAirUnit, ZoneHVACOutdoorAirUnit_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::ZoneHVAC_OutdoorAirUnit_EquipmentList, ZoneHVACOutdoorAirUnitEquipmentList_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::ZoneHVAC_PackagedTerminalAirConditioner, ZoneHVACPackagedTerminalAirConditioner_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::ZoneHVAC_PackagedTerminalHeatPump, ZoneHVACPackagedTerminalHeatPump_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::ZoneHVAC_TerminalUnit_VariableRefrigerantFlow, ZoneHVACTerminalUnitVariableRefrigerantFlow_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::ZoneHVAC_UnitHeater, ZoneHVACUnitHeater_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::ZoneHVAC_UnitVentilator, ZoneHVACUnitVentilator_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::ZoneHVAC_VentilatedSlab, ZoneHVACVentilatedSlab_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::ZoneHVAC_VentilatedSlab_SlabGroup, ZoneHVACVentilatedSlabSlabGroup_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::ZoneHVAC_WaterToAirHeatPump, ZoneHVACWaterToAirHeatPump_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::ZoneHVAC_WindowAirConditioner, ZoneHVACWindowAirConditioner_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::ZoneInfiltration_DesignFlowRate, SpaceInfiltrationDesignFlowRate_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::ZoneInfiltration_EffectiveLeakageArea, SpaceInfiltrationEffectiveLeakageArea_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::ZoneInfiltration_FlowCoefficient, SpaceInfiltrationFlowCoefficient_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::ZoneMixing, ZoneMixing_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::ZoneProperty_LocalEnvironment, ZonePropertyLocalEnvironment_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::ZoneProperty_UserViewFactors_BySurfaceName, ZonePropertyUserViewFactorsBySurfaceName_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::ZoneRefrigerationDoorMixing, ZoneRefrigerationDoorMixing_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::ZoneThermalChimney, ZoneThermalChimney_Impl);
      REGISTER_COPY_CONSTRUCTOR(IddObjectType::ZoneVentilation_WindandStackOpenArea, ZoneVentilationWindandStackOpenArea_Impl);
      REGISTER_COPY_CONSTRUCTOR(UtilityCostComputation::iddObjectType(), UtilityCostComputation_Impl);
      REGISTER_COPY_CONSTRUCTOR(ZoneEarthtubeParameters::iddObjectType(), ZoneEarthtubeParameters_Impl);

      m_copyMap[IddObjectType::Refrigeration_Subcooler] = [](openstudio::epmodel::detail::Model_Impl* m,
                                                             const std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>& ptr,
                                                             bool keepHandle) -> std::shared_ptr<openstudio::detail::WorkspaceObject_Impl> {
        if (auto liquid = std::dynamic_pointer_cast<RefrigerationSubcoolerLiquidSuction_Impl>(ptr)) {
          return std::make_shared<RefrigerationSubcoolerLiquidSuction_Impl>(*liquid, m, keepHandle);
        }
        if (auto mechanical = std::dynamic_pointer_cast<RefrigerationSubcoolerMechanical_Impl>(ptr)) {
          return std::make_shared<RefrigerationSubcoolerMechanical_Impl>(*mechanical, m, keepHandle);
        }
        if (auto base = std::dynamic_pointer_cast<RefrigerationSubcooler_Impl>(ptr)) {
          return std::make_shared<RefrigerationSubcooler_Impl>(*base, m, keepHandle);
        }
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>();
      };
    }

    const detail::Model_Impl::ModelObjectCreator detail::Model_Impl::modelObjectCreator;
    openstudio::epmodel::Model Model_Impl::model() const {
      return Model(std::dynamic_pointer_cast<Model_Impl>(std::const_pointer_cast<openstudio::detail::Workspace_Impl>(this->shared_from_this())));
    }

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
