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
#include "Splitter/AirLoopHVACZoneSplitter_Impl.hpp"
#include "Loop/AirLoopHVAC_Impl.hpp"
#include "Loop/PlantLoop_Impl.hpp"
#include "AvailabilityManagerAssignmentList_Impl.hpp"
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
#include "ModelObject/RefrigerationSystem_Impl.hpp"
#include "ModelObject/RefrigerationSubcoolerLiquidSuction_Impl.hpp"
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
#include "ModelObject/ChillerElectric_Impl.hpp"
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
#include "DesignSpecificationOutdoorAir_Impl.hpp"
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
#include "HVACComponent/CoilCoolingDXVariableRefrigerantFlow_Impl.hpp"
#include "HVACComponent/CoilCoolingDXVariableRefrigerantFlowFluidTemperatureControl_Impl.hpp"
#include "HVACComponent/CoilHeatingDXVariableRefrigerantFlow_Impl.hpp"
#include "HVACComponent/CoilHeatingDXVariableRefrigerantFlowFluidTemperatureControl_Impl.hpp"
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
#include "ModelObject/CurveCubicLinear_Impl.hpp"
#include "ModelObject/CurveChillerPartLoadWithLift_Impl.hpp"
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
#include "ModelObject/PlantEquipmentOperationChillerHeaterChangeover_Impl.hpp"
#include "ModelObject/PlantEquipmentOperationComponentSetpoint_Impl.hpp"
#include "ModelObject/PlantEquipmentOperationThermalEnergyStorage_Impl.hpp"
#include "ModelObject/PlantEquipmentOperationSchemes_Impl.hpp"
#include "PlantEquipmentOperationRangeBasedScheme/PlantEquipmentOperationCoolingLoad_Impl.hpp"
#include "PlantEquipmentOperationRangeBasedScheme/PlantEquipmentOperationHeatingLoad_Impl.hpp"
#include "PlantEquipmentOperationRangeBasedScheme/PlantEquipmentOperationOutdoorDewpoint_Impl.hpp"
#include "PlantEquipmentOperationRangeBasedScheme/PlantEquipmentOperationOutdoorDewpointDifference_Impl.hpp"
#include "PlantEquipmentOperationRangeBasedScheme/PlantEquipmentOperationOutdoorDryBulbDifference_Impl.hpp"
#include "PlantEquipmentOperationRangeBasedScheme/PlantEquipmentOperationOutdoorWetBulbDifference_Impl.hpp"
#include "PlantEquipmentOperationRangeBasedScheme/PlantEquipmentOperationOutdoorDryBulb_Impl.hpp"
#include "PlantEquipmentOperationRangeBasedScheme/PlantEquipmentOperationOutdoorRelativeHumidity_Impl.hpp"
#include "PlantEquipmentOperationRangeBasedScheme/PlantEquipmentOperationOutdoorWetBulb_Impl.hpp"
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
#include "Schedule/ScheduleRuleset_Impl.hpp"
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
#include "ModelObject/PlantEquipmentOperationUncontrolled_Impl.hpp"
#include "ModelObject/PlantEquipmentOperationUserDefined_Impl.hpp"
#include "ModelObject/SpaceHVACZoneReturnMixer_Impl.hpp"
#include "ModelObject/GroundHeatTransferControl_Impl.hpp"
#include "ModelObject/GroundHeatTransferBasementAutoGrid_Impl.hpp"
#include "ModelObject/GroundHeatTransferBasementBldgData_Impl.hpp"
#include "ModelObject/GroundHeatTransferBasementComBldg_Impl.hpp"
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
#include "NodeList_Impl.hpp"
#include "OutdoorAirMixer_Impl.hpp"
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
#include "SetpointManagerMixedAir_Impl.hpp"
#include "SetpointManager/SetpointManagerScheduled_Impl.hpp"
#include "SetpointManager/SetpointManagerScheduledDualSetpoint_Impl.hpp"
#include "SetpointManager/SetpointManagerSingleZoneCooling_Impl.hpp"
#include "SetpointManager/SetpointManagerSingleZoneOneStageCooling_Impl.hpp"
#include "SetpointManager/SetpointManagerSingleZoneOneStageHeating_Impl.hpp"
#include "SetpointManager/SetpointManagerSingleZoneHeating_Impl.hpp"
#include "SetpointManager/SetpointManagerSingleZoneHumidityMaximum_Impl.hpp"
#include "SetpointManager/SetpointManagerSingleZoneHumidityMinimum_Impl.hpp"
#include "SetpointManager/SetpointManagerSingleZoneReheat_Impl.hpp"
#include "HVACComponent/ThermalZone_Impl.hpp"
#include "ZoneHVACAirDistributionUnit_Impl.hpp"
#include "ZoneHVACEquipmentConnections_Impl.hpp"
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
      const auto type = object.iddObject().type();
      static const IddObjectType plantEquipmentOperationChillerHeaterChangeoverType("PlantEquipmentOperation_ChillerHeaterChangeover");
      static const IddObjectType plantEquipmentOperationComponentSetpointType("PlantEquipmentOperation_ComponentSetpoint");
      static const IddObjectType plantEquipmentOperationThermalEnergyStorageType("PlantEquipmentOperation_ThermalEnergyStorage");
      static const IddObjectType plantEquipmentOperationUncontrolledType("PlantEquipmentOperation_Uncontrolled");
      static const IddObjectType plantEquipmentOperationUserDefinedType("PlantEquipmentOperation_UserDefined");
      static const IddObjectType plantEquipmentOperationCoolingLoadType("PlantEquipmentOperation_CoolingLoad");
      static const IddObjectType plantEquipmentOperationHeatingLoadType("PlantEquipmentOperation_HeatingLoad");
      static const IddObjectType plantEquipmentOperationOutdoorDewpointType("PlantEquipmentOperation_OutdoorDewpoint");
      static const IddObjectType plantEquipmentOperationOutdoorDewpointDifferenceType("PlantEquipmentOperation_OutdoorDewpointDifference");
      static const IddObjectType plantEquipmentOperationOutdoorDryBulbDifferenceType("PlantEquipmentOperation_OutdoorDryBulbDifference");
      static const IddObjectType plantEquipmentOperationOutdoorDryBulbType("PlantEquipmentOperation_OutdoorDryBulb");
      static const IddObjectType plantEquipmentOperationOutdoorRelativeHumidityType("PlantEquipmentOperation_OutdoorRelativeHumidity");
      static const IddObjectType plantEquipmentOperationOutdoorWetBulbType("PlantEquipmentOperation_OutdoorWetBulb");
      static const IddObjectType plantEquipmentOperationOutdoorWetBulbDifferenceType("PlantEquipmentOperation_OutdoorWetBulbDifference");
      if (type == IddObjectType::AirLoopHVAC) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new AirLoopHVAC_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::PlantLoop) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new PlantLoop_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::AirLoopHVAC_SupplyPath) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new AirLoopHVACSupplyPath_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::AirLoopHVAC_ReturnPath) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new AirLoopHVACReturnPath_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::AirLoopHVAC_ReturnPlenum) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new AirLoopHVACReturnPlenum_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::AirLoopHVAC_SupplyPlenum) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new AirLoopHVACSupplyPlenum_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::AirLoopHVAC_OutdoorAirSystem) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new AirLoopHVACOutdoorAirSystem_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::AirLoopHVAC_ControllerList) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new AirLoopHVACControllerList_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::AirLoopHVAC_ZoneSplitter) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new AirLoopHVACZoneSplitter_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::AirLoopHVAC_ZoneMixer) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new AirLoopHVACZoneMixer_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::AvailabilityManagerAssignmentList) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new AvailabilityManagerAssignmentList_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::AvailabilityManager_NightCycle) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new AvailabilityManagerNightCycle_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::AvailabilityManager_DifferentialThermostat) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new AvailabilityManagerDifferentialThermostat_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::AvailabilityManager_HighTemperatureTurnOff) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new AvailabilityManagerHighTemperatureTurnOff_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::AvailabilityManager_HighTemperatureTurnOn) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new AvailabilityManagerHighTemperatureTurnOn_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::AvailabilityManager_LowTemperatureTurnOff) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new AvailabilityManagerLowTemperatureTurnOff_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::AvailabilityManager_LowTemperatureTurnOn) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new AvailabilityManagerLowTemperatureTurnOn_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::AvailabilityManager_HybridVentilation) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new AvailabilityManagerHybridVentilation_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::AvailabilityManager_NightVentilation) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new AvailabilityManagerNightVentilation_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::AvailabilityManager_OptimumStart) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new AvailabilityManagerOptimumStart_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::AvailabilityManager_ScheduledOff) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new AvailabilityManagerScheduledOff_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::AvailabilityManager_ScheduledOn) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new AvailabilityManagerScheduledOn_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::Branch) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new Branch_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::BranchList) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new BranchList_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::Building) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new Building_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::Site_Location) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new Site_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::BuildingSurface_Detailed) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new Surface_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::FenestrationSurface_Detailed) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new SubSurface_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::InternalMass) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new InteriorPartitionSurface_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::Boiler_HotWater) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new BoilerHotWater_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::Boiler_Steam) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new BoilerSteam_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::DistrictCooling) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new DistrictCooling_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::DistrictHeating_Steam) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new DistrictHeatingSteam_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::DistrictHeating_Water) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new DistrictHeatingWater_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::Duct) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new Duct_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::Pipe_Adiabatic) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new PipeAdiabatic_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::Pipe_Indoor) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new PipeIndoor_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::Pipe_Outdoor) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new PipeOutdoor_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::Pipe_Adiabatic_Steam) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new PipeAdiabaticSteam_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::Pipe_Underground) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new PipeUnderground_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::PipingSystem_Underground_Domain) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new PipingSystemUndergroundDomain_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::PipingSystem_Underground_PipeCircuit) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new PipingSystemUndergroundPipeCircuit_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::PipingSystem_Underground_PipeSegment) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new PipingSystemUndergroundPipeSegment_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::Pump_ConstantSpeed) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new PumpConstantSpeed_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::Pump_VariableSpeed) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new PumpVariableSpeed_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::Pump_VariableSpeed_Condensate) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new PumpVariableSpeedCondensate_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::HeaderedPumps_ConstantSpeed) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new HeaderedPumpsConstantSpeed_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::HeaderedPumps_VariableSpeed) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new HeaderedPumpsVariableSpeed_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::Humidifier_Steam_Electric) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new HumidifierSteamElectric_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::Humidifier_Steam_Gas) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new HumidifierSteamGas_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::SwimmingPool_Indoor) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new SwimmingPoolIndoor_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::Duct_Loss_Conduction) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new DuctLossConduction_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::Duct_Loss_Leakage) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new DuctLossLeakage_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::Duct_Loss_MakeupAir) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new DuctLossMakeupAir_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::EvaporativeCooler_Direct_CelDekPad) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new EvaporativeCoolerDirectCelDekPad_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::EvaporativeCooler_Direct_ResearchSpecial) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new EvaporativeCoolerDirectResearchSpecial_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::EvaporativeCooler_Indirect_ResearchSpecial) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new EvaporativeCoolerIndirectResearchSpecial_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::EvaporativeCooler_Indirect_CelDekPad) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new EvaporativeCoolerIndirectCelDekPad_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::EvaporativeCooler_Indirect_WetCoil) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new EvaporativeCoolerIndirectWetCoil_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::EvaporativeFluidCooler_SingleSpeed) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new EvaporativeFluidCoolerSingleSpeed_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::EvaporativeFluidCooler_TwoSpeed) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new EvaporativeFluidCoolerTwoSpeed_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::FluidCooler_SingleSpeed) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new FluidCoolerSingleSpeed_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::FluidCooler_TwoSpeed) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new FluidCoolerTwoSpeed_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::GroundHeatExchanger_HorizontalTrench) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new GroundHeatExchangerHorizontalTrench_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::GroundHeatExchanger_ResponseFactors) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new GroundHeatExchangerVertical_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::GroundHeatExchanger_Vertical_Array) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new GroundHeatExchangerVerticalArray_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::GroundHeatExchanger_Vertical_Single) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new GroundHeatExchangerVerticalSingle_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::GroundHeatExchanger_Vertical_Sizing_Rectangle) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new GroundHeatExchangerVerticalSizingRectangle_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::GroundHeatExchanger_Pond) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new GroundHeatExchangerPond_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::GroundHeatExchanger_Surface) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new GroundHeatExchangerSurface_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::GroundHeatExchanger_Slinky) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new GroundHeatExchangerSlinky_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::FluidProperties_Concentration) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new FluidPropertiesConcentration_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::FluidProperties_GlycolConcentration) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new FluidPropertiesGlycolConcentration_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::FluidProperties_Name) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new FluidPropertiesName_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::FluidProperties_Saturated) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new FluidPropertiesSaturated_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::FluidProperties_Superheated) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new FluidPropertiesSuperheated_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::FluidProperties_Temperatures) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new FluidPropertiesTemperatures_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::Foundation_Kiva) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new FoundationKiva_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::Foundation_Kiva_Settings) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new FoundationKivaSettings_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::CoolingTower_SingleSpeed) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new CoolingTowerSingleSpeed_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::CoolingTower_TwoSpeed) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new CoolingTowerTwoSpeed_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::CoolingTower_VariableSpeed) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new CoolingTowerVariableSpeed_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::CoolingTower_VariableSpeed_Merkel) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new CoolingTowerVariableSpeedMerkel_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::CoolingTowerPerformance_CoolTools) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new CoolingTowerPerformanceCoolTools_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::CoolingTowerPerformance_YorkCalc) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new CoolingTowerPerformanceYorkCalc_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::Chiller_Absorption) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new ChillerAbsorption_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::Chiller_Absorption_Indirect) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new ChillerAbsorptionIndirect_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::Chiller_CombustionTurbine) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new ChillerCombustionTurbine_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::Generator_CombustionTurbine) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new GeneratorCombustionTurbine_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::Generator_InternalCombustionEngine) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new GeneratorInternalCombustionEngine_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::Generator_MicroCHP) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new GeneratorMicroCHP_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::Generator_MicroCHP_NonNormalizedParameters) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new GeneratorMicroCHPNonNormalizedParameters_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::Generator_MicroTurbine) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new GeneratorMicroTurbine_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::Generator_Photovoltaic) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new GeneratorPhotovoltaic_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::Generator_WindTurbine) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new GeneratorWindTurbine_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::Generator_PVWatts) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new GeneratorPVWatts_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::PhotovoltaicPerformance_Simple) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new PhotovoltaicPerformanceSimple_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::PhotovoltaicPerformance_Sandia) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new PhotovoltaicPerformanceSandia_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::Generator_FuelCell) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new GeneratorFuelCell_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::Generator_FuelCell_AirSupply) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new GeneratorFuelCellAirSupply_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::Generator_FuelCell_AuxiliaryHeater) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new GeneratorFuelCellAuxiliaryHeater_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::Generator_FuelCell_ElectricalStorage) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new GeneratorFuelCellElectricalStorage_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::Generator_FuelCell_Inverter) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new GeneratorFuelCellInverter_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::Generator_FuelCell_PowerModule) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new GeneratorFuelCellPowerModule_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::Generator_FuelCell_WaterSupply) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new GeneratorFuelCellWaterSupply_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::Generator_FuelSupply) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new GeneratorFuelSupply_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::Generator_FuelCell_ExhaustGasToWaterHeatExchanger) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new GeneratorFuelCellExhaustGasToWaterHeatExchanger_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::Generator_FuelCell_StackCooler) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new GeneratorFuelCellStackCooler_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::ChillerHeater_Absorption_DirectFired) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new ChillerHeaterAbsorptionDirectFired_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::ChillerHeater_Absorption_DoubleEffect) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new ChillerHeaterAbsorptionDoubleEffect_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::ChillerHeaterPerformance_Electric_EIR) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new ChillerHeaterPerformanceElectricEIR_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::Chiller_ConstantCOP) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new ChillerConstantCOP_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::Chiller_EngineDriven) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new ChillerEngineDriven_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::Chiller_Electric) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new ChillerElectric_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::Chiller_Electric_EIR) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new ChillerElectricEIR_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::Chiller_Electric_ReformulatedEIR) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new ChillerElectricReformulatedEIR_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::Chiller_Electric_ASHRAE205) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new ChillerElectricASHRAE205_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::Fan_ConstantVolume) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new FanConstantVolume_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::Fan_ComponentModel) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new FanComponentModel_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::Fan_OnOff) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new FanOnOff_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::Fan_SystemModel) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new FanSystemModel_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::Fan_VariableVolume) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new FanVariableVolume_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::FanPerformance_NightVentilation) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new FanPerformanceNightVentilation_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::FaultModel_Fouling_AirFilter) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new FaultModelFoulingAirFilter_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::FaultModel_Fouling_Boiler) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new FaultModelFoulingBoiler_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::FaultModel_Fouling_Chiller) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new FaultModelFoulingChiller_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::FaultModel_Fouling_Coil) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new FaultModelFoulingCoil_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::FaultModel_Fouling_CoolingTower) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new FaultModelFoulingCoolingTower_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::FaultModel_Fouling_EvaporativeCooler) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new FaultModelFoulingEvaporativeCooler_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::FaultModel_EnthalpySensorOffset_OutdoorAir) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new FaultModelEnthalpySensorOffsetOutdoorAir_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::FaultModel_EnthalpySensorOffset_ReturnAir) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new FaultModelEnthalpySensorOffsetReturnAir_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::FaultModel_HumidistatOffset) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new FaultModelHumidistatOffset_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::FaultModel_HumiditySensorOffset_OutdoorAir) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new FaultModelHumiditySensorOffsetOutdoorAir_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::FaultModel_ThermostatOffset) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new FaultModelThermostatOffset_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::FaultModel_TemperatureSensorOffset_ChillerSupplyWater) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new FaultModelTemperatureSensorOffsetChillerSupplyWater_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::FaultModel_TemperatureSensorOffset_CoilSupplyAir) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new FaultModelTemperatureSensorOffsetCoilSupplyAir_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::FaultModel_TemperatureSensorOffset_CondenserSupplyWater) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new FaultModelTemperatureSensorOffsetCondenserSupplyWater_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::FaultModel_TemperatureSensorOffset_OutdoorAir) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new FaultModelTemperatureSensorOffsetOutdoorAir_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::FaultModel_TemperatureSensorOffset_ReturnAir) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new FaultModelTemperatureSensorOffsetReturnAir_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::Floor_Adiabatic) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new FloorAdiabatic_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::Floor_Detailed) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new FloorDetailed_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::Floor_GroundContact) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new FloorGroundContact_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::Floor_Interzone) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new FloorInterzone_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::Coil_Cooling_DX_SingleSpeed) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new CoilCoolingDXSingleSpeed_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::Coil_Cooling_DX_SingleSpeed_ThermalStorage) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new CoilCoolingDXSingleSpeedThermalStorage_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::Coil_Cooling_DX_VariableSpeed) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new CoilCoolingDXVariableSpeed_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::Coil_Cooling_DX_MultiSpeed) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new CoilCoolingDXMultiSpeed_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::Coil_Cooling_DX_TwoSpeed) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new CoilCoolingDXTwoSpeed_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::Coil_Cooling_DX_TwoStageWithHumidityControlMode) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new CoilCoolingDXTwoStageWithHumidityControlMode_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::CoilPerformance_DX_Cooling) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new CoilPerformanceDXCooling_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::Coil_Cooling_DX_CurveFit_OperatingMode) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new CoilCoolingDXCurveFitOperatingMode_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::Coil_Cooling_DX_CurveFit_Performance) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new CoilCoolingDXCurveFitPerformance_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::Coil_Cooling_DX_CurveFit_Speed) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new CoilCoolingDXCurveFitSpeed_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::HeatExchanger_Desiccant_BalancedFlow_PerformanceDataType1) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new HeatExchangerDesiccantBalancedFlowPerformanceDataType1_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::MaterialProperty_GlazingSpectralData) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new MaterialPropertyGlazingSpectralData_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::MaterialProperty_HeatAndMoistureTransfer_Diffusion) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new MaterialPropertyHeatAndMoistureTransferDiffusion_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::MaterialProperty_HeatAndMoistureTransfer_Redistribution) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new MaterialPropertyHeatAndMoistureTransferRedistribution_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::MaterialProperty_HeatAndMoistureTransfer_Settings) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new MaterialPropertyHeatAndMoistureTransferSettings_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::MaterialProperty_HeatAndMoistureTransfer_SorptionIsotherm) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new MaterialPropertyHeatAndMoistureTransferSorptionIsotherm_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::MaterialProperty_HeatAndMoistureTransfer_Suction) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new MaterialPropertyHeatAndMoistureTransferSuction_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::MaterialProperty_HeatAndMoistureTransfer_ThermalConductivity) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new MaterialPropertyHeatAndMoistureTransferThermalConductivity_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::MaterialProperty_MoisturePenetrationDepth_Settings) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new MaterialPropertyMoisturePenetrationDepthSettings_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::MaterialProperty_VariableAbsorptance) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new MaterialPropertyVariableAbsorptance_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::MaterialProperty_VariableThermalConductivity) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new MaterialPropertyVariableThermalConductivity_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::MaterialProperty_PhaseChange) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new MaterialPropertyPhaseChange_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::MaterialProperty_PhaseChangeHysteresis) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new MaterialPropertyPhaseChangeHysteresis_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::Coil_Cooling_DX) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new CoilCoolingDX_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::Coil_Cooling_DX_VariableRefrigerantFlow) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new CoilCoolingDXVariableRefrigerantFlow_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::Coil_Cooling_DX_VariableRefrigerantFlow_FluidTemperatureControl) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new CoilCoolingDXVariableRefrigerantFlowFluidTemperatureControl_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::Coil_Heating_DX_VariableRefrigerantFlow) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new CoilHeatingDXVariableRefrigerantFlow_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::Coil_Heating_DX_VariableRefrigerantFlow_FluidTemperatureControl) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new CoilHeatingDXVariableRefrigerantFlowFluidTemperatureControl_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::Coil_Cooling_Water) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new CoilCoolingWater_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::Coil_Heating_Water) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new CoilHeatingWater_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::Coil_Cooling_WaterToAirHeatPump_EquationFit) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new CoilCoolingWaterToAirHeatPumpEquationFit_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::Coil_Heating_WaterToAirHeatPump_EquationFit) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new CoilHeatingWaterToAirHeatPumpEquationFit_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::Coil_Cooling_WaterToAirHeatPump_VariableSpeedEquationFit) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new CoilCoolingWaterToAirHeatPumpVariableSpeedEquationFit_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::Coil_Heating_WaterToAirHeatPump_VariableSpeedEquationFit) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new CoilHeatingWaterToAirHeatPumpVariableSpeedEquationFit_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::Coil_UserDefined) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new CoilUserDefined_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::Coil_Cooling_WaterToAirHeatPump_ParameterEstimation) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new CoilCoolingWaterToAirHeatPumpParameterEstimation_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::Coil_Heating_WaterToAirHeatPump_ParameterEstimation) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new CoilHeatingWaterToAirHeatPumpParameterEstimation_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::Coil_Cooling_Water_DetailedGeometry) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new CoilCoolingWaterDetailedGeometry_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::Coil_DX_ASHRAE205_Performance) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new CoilDXASHRAE205Performance_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::Coil_Heating_DX_MultiSpeed) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new CoilHeatingDXMultiSpeed_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::Coil_Heating_DX_SingleSpeed) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new CoilHeatingDXSingleSpeed_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::Coil_Heating_DX_VariableSpeed) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new CoilHeatingDXVariableSpeed_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::Coil_Heating_Desuperheater) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new CoilHeatingDesuperheater_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::Coil_WaterHeating_Desuperheater) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new CoilWaterHeatingDesuperheater_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::Coil_Heating_Electric) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new CoilHeatingElectric_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::Coil_Heating_Electric_MultiStage) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new CoilHeatingElectricMultiStage_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::Coil_Heating_Fuel) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new CoilHeatingGas_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::Coil_Heating_Gas_MultiStage) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new CoilHeatingGasMultiStage_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::Coil_Heating_Steam) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new CoilHeatingSteam_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::Coil_WaterHeating_AirToWaterHeatPump_Wrapped) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new CoilWaterHeatingAirToWaterHeatPumpWrapped_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::Coil_WaterHeating_AirToWaterHeatPump_Pumped) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new CoilWaterHeatingAirToWaterHeatPump_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::Coil_WaterHeating_AirToWaterHeatPump_VariableSpeed) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new CoilWaterHeatingAirToWaterHeatPumpVariableSpeed_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::Controller_WaterCoil) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new ControllerWaterCoil_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::CoilSystem_Cooling_DX) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new CoilSystemCoolingDX_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::CoilSystem_Heating_DX) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new CoilSystemHeatingDX_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::CoilSystem_Cooling_DX_HeatExchangerAssisted) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new CoilSystemCoolingDXHeatExchangerAssisted_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::CoilSystem_IntegratedHeatPump_AirSource) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new CoilSystemIntegratedHeatPumpAirSource_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::CoilSystem_Cooling_Water) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new CoilSystemCoolingWater_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::CoilSystem_Cooling_Water_HeatExchangerAssisted) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new CoilSystemCoolingWaterHeatExchangerAssisted_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::SetpointManager_MixedAir) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new SetpointManagerMixedAir_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::SetpointManager_MultiZone_Cooling_Average) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new SetpointManagerMultiZoneCoolingAverage_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::SetpointManager_MultiZone_Heating_Average) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new SetpointManagerMultiZoneHeatingAverage_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::SetpointManager_MultiZone_MaximumHumidity_Average) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new SetpointManagerMultiZoneMaximumHumidityAverage_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::SetpointManager_MultiZone_MinimumHumidity_Average) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new SetpointManagerMultiZoneMinimumHumidityAverage_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::SetpointManager_MultiZone_Humidity_Maximum) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new SetpointManagerMultiZoneHumidityMaximum_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::SetpointManager_MultiZone_Humidity_Minimum) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new SetpointManagerMultiZoneHumidityMinimum_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::SetpointManager_Coldest) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new SetpointManagerColdest_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::SetpointManager_FollowGroundTemperature) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new SetpointManagerFollowGroundTemperature_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::SetpointManager_FollowOutdoorAirTemperature) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new SetpointManagerFollowOutdoorAirTemperature_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::SetpointManager_OutdoorAirPretreat) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new SetpointManagerOutdoorAirPretreat_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::SetpointManager_OutdoorAirReset) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new SetpointManagerOutdoorAirReset_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::SetpointManager_FollowSystemNodeTemperature) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new SetpointManagerFollowSystemNodeTemperature_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::SetpointManager_SystemNodeReset_Humidity) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new SetpointManagerSystemNodeResetHumidity_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::SetpointManager_SystemNodeReset_Temperature) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new SetpointManagerSystemNodeResetTemperature_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::SetpointManager_Warmest) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new SetpointManagerWarmest_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::SetpointManager_WarmestTemperatureFlow) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new SetpointManagerWarmestTemperatureFlow_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::SetpointManager_CondenserEnteringReset) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new SetpointManagerCondenserEnteringReset_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::SetpointManager_CondenserEnteringReset_Ideal) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new SetpointManagerCondenserEnteringResetIdeal_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::SetpointManager_ReturnAirBypassFlow) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new SetpointManagerReturnAirBypassFlow_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::SetpointManager_ReturnTemperature_ChilledWater) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new SetpointManagerReturnTemperatureChilledWater_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::SetpointManager_ReturnTemperature_HotWater) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new SetpointManagerReturnTemperatureHotWater_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::SetpointManager_Scheduled) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new SetpointManagerScheduled_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::SetpointManager_Scheduled_DualSetpoint) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new SetpointManagerScheduledDualSetpoint_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::SetpointManager_SingleZone_Cooling) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new SetpointManagerSingleZoneCooling_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::SetpointManager_SingleZone_OneStageCooling) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new SetpointManagerSingleZoneOneStageCooling_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::SetpointManager_SingleZone_OneStageHeating) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new SetpointManagerSingleZoneOneStageHeating_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::SetpointManager_SingleZone_Heating) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new SetpointManagerSingleZoneHeating_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::SetpointManager_SingleZone_Humidity_Maximum) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new SetpointManagerSingleZoneHumidityMaximum_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::SetpointManager_SingleZone_Humidity_Minimum) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new SetpointManagerSingleZoneHumidityMinimum_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::SetpointManager_SingleZone_Reheat) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new SetpointManagerSingleZoneReheat_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::AirTerminal_SingleDuct_ConstantVolume_NoReheat) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new AirTerminalSingleDuctConstantVolumeNoReheat_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::AirTerminal_SingleDuct_ConstantVolume_Reheat) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new AirTerminalSingleDuctConstantVolumeReheat_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::AirTerminal_SingleDuct_Mixer) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new AirTerminalSingleDuctInletSideMixer_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::AirTerminal_SingleDuct_ParallelPIU_Reheat) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new AirTerminalSingleDuctParallelPIUReheat_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::AirTerminal_SingleDuct_SeriesPIU_Reheat) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new AirTerminalSingleDuctSeriesPIUReheat_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::AirTerminal_DualDuct_ConstantVolume) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new AirTerminalDualDuctConstantVolume_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::AirTerminal_DualDuct_VAV) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new AirTerminalDualDuctVAV_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::AirTerminal_DualDuct_VAV_OutdoorAir) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new AirTerminalDualDuctVAVOutdoorAir_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::AirTerminal_SingleDuct_ConstantVolume_CooledBeam) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new AirTerminalSingleDuctConstantVolumeCooledBeam_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::AirTerminal_SingleDuct_ConstantVolume_FourPipeBeam) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new AirTerminalSingleDuctConstantVolumeFourPipeBeam_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::AirTerminal_SingleDuct_ConstantVolume_FourPipeInduction) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new AirTerminalSingleDuctConstantVolumeFourPipeInduction_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::AirTerminal_SingleDuct_UserDefined) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new AirTerminalSingleDuctUserDefined_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::AirTerminal_SingleDuct_VAV_HeatAndCool_NoReheat) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new AirTerminalSingleDuctVAVHeatAndCoolNoReheat_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::AirTerminal_SingleDuct_VAV_HeatAndCool_Reheat) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new AirTerminalSingleDuctVAVHeatAndCoolReheat_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::AirTerminal_SingleDuct_VAV_NoReheat) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new AirTerminalSingleDuctVAVNoReheat_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::AirTerminal_SingleDuct_VAV_Reheat) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new AirTerminalSingleDuctVAVReheat_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::AirTerminal_SingleDuct_VAV_Reheat_VariableSpeedFan) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new AirTerminalSingleDuctVAVReheatVariableSpeedFan_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::Node) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new Node_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::NodeList) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new NodeList_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::OutdoorAir_Mixer) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new OutdoorAirMixer_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::AirLoopHVAC_OutdoorAirSystem_EquipmentList) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new AirLoopHVACOutdoorAirSystemEquipmentList_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::Controller_OutdoorAir) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new ControllerOutdoorAir_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::OS_ZoneHVAC_EnergyRecoveryVentilator_Controller) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new ZoneHVACEnergyRecoveryVentilatorController_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::Controller_MechanicalVentilation) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new ControllerMechanicalVentilation_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::DesignSpecification_OutdoorAir) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new DesignSpecificationOutdoorAir_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::DesignSpecification_OutdoorAir_SpaceList) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new DesignSpecificationOutdoorAirSpaceList_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::DesignSpecification_AirTerminal_Sizing) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new DesignSpecificationAirTerminalSizing_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::DesignSpecification_ZoneHVAC_Sizing) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new DesignSpecificationZoneHVACSizing_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::Zone) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new ThermalZone_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::Space) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new Space_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::SpaceHVAC_EquipmentConnections) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new SpaceHVACEquipmentConnections_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::SpaceHVAC_ZoneEquipmentSplitter) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new SpaceHVACZoneEquipmentSplitter_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::Sizing_Zone) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new SizingZone_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::Sizing_Plant) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new SizingPlant_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::Sizing_System) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new SizingSystem_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::SizingPeriod_DesignDay) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new DesignDay_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::SizingPeriod_WeatherFileConditionType) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new SizingPeriodWeatherFileConditionType_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::SizingPeriod_WeatherFileDays) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new SizingPeriodWeatherFileDays_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::Sizing_Parameters) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new SizingParameters_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::ZoneHVAC_EquipmentConnections) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new ZoneHVACEquipmentConnections_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::ZoneHVAC_EquipmentList) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new ZoneHVACEquipmentList_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::ZoneHVAC_AirDistributionUnit) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new ZoneHVACAirDistributionUnit_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::ZoneHVAC_Baseboard_Convective_Electric) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new ZoneHVACBaseboardConvectiveElectric_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::ZoneHVAC_Baseboard_Convective_Water) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new ZoneHVACBaseboardConvectiveWater_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::ZoneHVAC_Baseboard_RadiantConvective_Electric) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new ZoneHVACBaseboardRadiantConvectiveElectric_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::ZoneHVAC_Baseboard_RadiantConvective_Water) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new ZoneHVACBaseboardRadiantConvectiveWater_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::ZoneHVAC_CoolingPanel_RadiantConvective_Water) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new ZoneHVACCoolingPanelRadiantConvectiveWater_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::ZoneHVAC_HighTemperatureRadiant) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new ZoneHVACHighTemperatureRadiant_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::OS_ZoneHVAC_PackagedTerminalAirConditioner) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new ZoneHVACPackagedTerminalAirConditioner_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::OS_ZoneHVAC_PackagedTerminalHeatPump) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new ZoneHVACPackagedTerminalHeatPump_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::OS_ZoneHVAC_TerminalUnit_VariableRefrigerantFlow) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new ZoneHVACTerminalUnitVariableRefrigerantFlow_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::ZoneHVAC_LowTemperatureRadiant_ConstantFlow) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new ZoneHVACLowTempRadiantConstFlow_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::ZoneHVAC_LowTemperatureRadiant_VariableFlow) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new ZoneHVACLowTempRadiantVarFlow_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::ZoneHVAC_LowTemperatureRadiant_VariableFlow_Design) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new ZoneHVACLowTempRadiantVarFlow_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::ZoneHVAC_LowTemperatureRadiant_Electric) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new ZoneHVACLowTemperatureRadiantElectric_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::ZoneHVAC_Baseboard_RadiantConvective_Water_Design) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new ZoneHVACBaseboardRadiantConvectiveWaterDesign_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::ZoneHVAC_Baseboard_RadiantConvective_Steam) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new ZoneHVACBaseboardRadiantConvectiveSteam_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::ZoneHVAC_Baseboard_RadiantConvective_Steam_Design) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new ZoneHVACBaseboardRadiantConvectiveSteamDesign_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::OS_ZoneHVAC_Dehumidifier_DX) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new ZoneHVACDehumidifierDX_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::ZoneHVAC_EnergyRecoveryVentilator) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new ZoneHVACEnergyRecoveryVentilator_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::Refrigeration_AirChiller) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new RefrigerationAirChiller_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::Refrigeration_Condenser_AirCooled) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new RefrigerationCondenserAirCooled_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::Refrigeration_GasCooler_AirCooled) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new RefrigerationGasCoolerAirCooled_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::Refrigeration_Condenser_EvaporativeCooled) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new RefrigerationCondenserEvaporativeCooled_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::Refrigeration_Condenser_Cascade) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new RefrigerationCondenserCascade_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::Refrigeration_Subcooler) {
        if (auto subcoolerType = object.getString(Refrigeration_SubcoolerFields::SubcoolerType, true)) {
          if (openstudio::istringEqual(*subcoolerType, "LiquidSuction")) {
            return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new RefrigerationSubcoolerLiquidSuction_Impl(object, this, keepHandle));
          }
        }
      }
      if (type == IddObjectType::Refrigeration_SecondarySystem) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new RefrigerationSecondarySystem_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::Refrigeration_TranscriticalSystem) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new RefrigerationTranscriticalSystem_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::Refrigeration_WalkIn) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new RefrigerationWalkIn_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::OS_Refrigeration_Condenser_WaterCooled) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new RefrigerationCondenserWaterCooled_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::Refrigeration_Case) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new RefrigerationCase_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::Refrigeration_Compressor) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new RefrigerationCompressor_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::Refrigeration_System) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new RefrigerationSystem_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::OS_Refrigeration_CompressorRack) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new RefrigerationCompressorRack_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::ZoneHVAC_EvaporativeCoolerUnit) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new ZoneHVACEvaporativeCoolerUnit_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::ZoneHVAC_UnitHeater) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new ZoneHVACUnitHeater_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::OS_ZoneHVAC_UnitVentilator) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new ZoneHVACUnitVentilator_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::ZoneHVAC_FourPipeFanCoil) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new ZoneHVACFourPipeFanCoil_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::ZoneHVAC_IdealLoadsAirSystem) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new ZoneHVACIdealLoadsAirSystem_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::ZoneHVAC_ExhaustControl) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new ZoneHVACExhaustControl_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::ZoneHVAC_HybridUnitaryHVAC) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new ZoneHVACHybridUnitaryHVAC_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::ZoneHVAC_ForcedAir_UserDefined) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new ZoneHVACForcedAirUserDefined_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::ZoneHVAC_OutdoorAirUnit) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new ZoneHVACOutdoorAirUnit_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::ZoneHVAC_OutdoorAirUnit_EquipmentList) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new ZoneHVACOutdoorAirUnitEquipmentList_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::ZoneHVAC_VentilatedSlab) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new ZoneHVACVentilatedSlab_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::ZoneHVAC_WindowAirConditioner) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new ZoneHVACWindowAirConditioner_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::ZoneHVAC_WaterToAirHeatPump) {
        LOG_FREE(Info, "openstudio.epmodel.Model", "Creating a ZoneHVACWaterToAirHeatPump workspace object");
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new ZoneHVACWaterToAirHeatPump_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::OS_ZoneVentilation_WindandStackOpenArea) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new ZoneVentilationWindandStackOpenArea_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::AirConditioner_VariableRefrigerantFlow) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new AirConditionerVariableRefrigerantFlow_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::SolarCollector_FlatPlate_PhotovoltaicThermal) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new SolarCollectorFlatPlatePhotovoltaicThermal_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::SolarCollector_FlatPlate_Water) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new SolarCollectorFlatPlateWater_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::SolarCollector_IntegralCollectorStorage) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new SolarCollectorIntegralCollectorStorage_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::SolarCollectorPerformance_FlatPlate) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new SolarCollectorPerformanceFlatPlate_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::SolarCollectorPerformance_IntegralCollectorStorage) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new SolarCollectorPerformanceIntegralCollectorStorage_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::SolarCollectorPerformance_PhotovoltaicThermal_BIPVT) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new SolarCollectorPerformancePhotovoltaicThermalBIPVT_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::SolarCollectorPerformance_PhotovoltaicThermal_Simple) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new SolarCollectorPerformancePhotovoltaicThermalSimple_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::SolarCollector_UnglazedTranspired) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new SolarCollectorUnglazedTranspired_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::SolarCollector_UnglazedTranspired_Multisystem) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new SolarCollectorUnglazedTranspiredMultisystem_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::SurfaceContaminantSourceAndSink_Generic_BoundaryLayerDiffusion) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new SurfaceContaminantSourceAndSinkGenericBoundaryLayerDiffusion_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::SurfaceContaminantSourceAndSink_Generic_DepositionVelocitySink) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new SurfaceContaminantSourceAndSinkGenericDepositionVelocitySink_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::SurfaceContaminantSourceAndSink_Generic_PressureDriven) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new SurfaceContaminantSourceAndSinkGenericPressureDriven_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::SurfaceControl_MovableInsulation) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new SurfaceControlMovableInsulation_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::SurfaceProperties_VaporCoefficients) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new SurfacePropertiesVaporCoefficients_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::HeatPump_AirToWater) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new HeatPumpAirToWater_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::HeatPump_AirToWater_FuelFired_Cooling) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new HeatPumpAirToWaterFuelFiredCooling_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::HeatPump_AirToWater_FuelFired_Heating) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new HeatPumpAirToWaterFuelFiredHeating_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::LoadProfile_Plant) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new LoadProfilePlant_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::PlantComponent_TemperatureSource) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new PlantComponentTemperatureSource_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::PlantComponent_UserDefined) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new PlantComponentUserDefined_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::TemperingValve) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new TemperingValve_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::OS_WaterUse_Connections) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new WaterUseConnections_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::AirConditioner_VariableRefrigerantFlow_FluidTemperatureControl) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new AirConditionerVariableRefrigerantFlowFluidTemperatureControl_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::AirConditioner_VariableRefrigerantFlow_FluidTemperatureControl_HR) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new AirConditionerVariableRefrigerantFlowFluidTemperatureControlHR_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::CentralHeatPumpSystem) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new CentralHeatPumpSystem_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::HeatPump_PlantLoop_EIR_Cooling) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new HeatPumpPlantLoopEIRCooling_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::HeatPump_PlantLoop_EIR_Heating) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new HeatPumpPlantLoopEIRHeating_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::HeatPump_WaterToWater_EquationFit_Cooling) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new HeatPumpWaterToWaterEquationFitCooling_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::HeatPump_WaterToWater_EquationFit_Heating) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new HeatPumpWaterToWaterEquationFitHeating_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::HeatPump_WaterToWater_ParameterEstimation_Cooling) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new HeatPumpWaterToWaterParameterEstimationCooling_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::HeatPump_WaterToWater_ParameterEstimation_Heating) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new HeatPumpWaterToWaterParameterEstimationHeating_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::HeatExchanger_FluidToFluid) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new HeatExchangerFluidToFluid_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::WaterHeater_Mixed) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new WaterHeaterMixed_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::WaterHeater_Stratified) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new WaterHeaterStratified_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::WaterHeater_Sizing) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new WaterHeaterSizing_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::ComfortViewFactorAngles) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new ComfortViewFactorAngles_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::ComplexFenestrationProperty_SolarAbsorbedLayers) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new ComplexFenestrationPropertySolarAbsorbedLayers_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::Construction_ComplexFenestrationState) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new ConstructionComplexFenestrationState_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::Compliance_Building) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new ComplianceBuilding_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::Shading_Building) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new ShadingBuilding_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::Shading_Building_Detailed) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new ShadingBuildingDetailed_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::Shading_Fin) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new ShadingFin_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::Shading_Fin_Projection) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new ShadingFinProjection_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::Shading_Overhang) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new ShadingOverhang_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::Shading_Overhang_Projection) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new ShadingOverhangProjection_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::Shading_Site) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new ShadingSite_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::Shading_Site_Detailed) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new ShadingSiteDetailed_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::Shading_Zone_Detailed) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new ShadingZoneDetailed_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::ShadingProperty_Reflectance) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new ShadingPropertyReflectance_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::WindowMaterial_Blind) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new Blind_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::WindowMaterial_Shade) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new detail::Shade_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::WindowMaterial_Shade_EquivalentLayer) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new WindowMaterialShadeEquivalentLayer_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::WindowMaterial_Screen) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new detail::Screen_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::WindowMaterial_Blind_EquivalentLayer) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new WindowMaterialBlindEquivalentLayer_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::WindowMaterial_Drape_EquivalentLayer) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new WindowMaterialDrapeEquivalentLayer_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::WindowMaterial_ComplexShade) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new WindowMaterialComplexShade_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::WindowMaterial_Gap) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new WindowMaterialGap_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::WindowMaterial_Gap_EquivalentLayer) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new WindowMaterialGapEquivalentLayer_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::WindowMaterial_Glazing_EquivalentLayer) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new WindowMaterialGlazingEquivalentLayer_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::WindowMaterial_Screen_EquivalentLayer) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new WindowMaterialScreenEquivalentLayer_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::WindowMaterial_Gas) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new Gas_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::WindowMaterial_GasMixture) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new GasMixture_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::ShadowCalculation) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new ShadowCalculation_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::ComponentCost_Adjustments) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new ComponentCostAdjustments_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::CurrencyType) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new CurrencyType_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::LifeCycleCost_Parameters) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new LifeCycleCostParameters_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::LifeCycleCost_UsePriceEscalation) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new LifeCycleCostUsePriceEscalation_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::RunPeriod) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new RunPeriod_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::RunPeriodControl_DaylightSavingTime) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new RunPeriodControlDaylightSavingTime_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::RunPeriodControl_SpecialDays) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new RunPeriodControlSpecialDays_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::ElectricLoadCenter_Distribution) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new ElectricLoadCenterDistribution_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::ElectricLoadCenter_Storage_Converter) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new ElectricLoadCenterStorageConverter_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::ElectricLoadCenter_Inverter_FunctionOfPower) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new ElectricLoadCenterInverterFunctionOfPower_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::ElectricLoadCenter_Transformer) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new ElectricLoadCenterTransformer_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::EnergyManagementSystem_Actuator) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new EnergyManagementSystemActuator_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::EnergyManagementSystem_ConstructionIndexVariable) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new EnergyManagementSystemConstructionIndexVariable_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::EnergyManagementSystem_GlobalVariable) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new EnergyManagementSystemGlobalVariable_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::EnergyManagementSystem_InternalVariable) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new EnergyManagementSystemInternalVariable_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::EnergyManagementSystem_MeteredOutputVariable) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new EnergyManagementSystemMeteredOutputVariable_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::EnergyManagementSystem_OutputVariable) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new EnergyManagementSystemOutputVariable_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::Output_Constructions) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new OutputConstructions_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::Output_DaylightFactors) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new OutputDaylightFactors_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::Output_DebuggingData) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new OutputDebuggingData_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::Output_Diagnostics) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new OutputDiagnostics_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::Output_EnergyManagementSystem) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new OutputEnergyManagementSystem_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::Output_EnvironmentalImpactFactors) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new OutputEnvironmentalImpactFactors_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::OutputControl_Files) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new OutputControlFiles_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::OutputControl_IlluminanceMap_Style) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new OutputControlIlluminanceMapStyle_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::OutputControl_ReportingTolerances) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new OutputControlReportingTolerances_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::OutputControl_ResilienceSummaries) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new OutputControlResilienceSummaries_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::OutputControl_Sizing_Style) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new OutputControlSizingStyle_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::OutputControl_Table_Style) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new OutputControlTableStyle_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::OutputControl_Timestamp) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new OutputControlTimestamp_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::OutputControl_SurfaceColorScheme) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new OutputControlSurfaceColorScheme_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::Output_JSON) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new OutputJSON_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::Output_Meter) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new OutputMeter_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::Output_Meter_Cumulative) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new OutputMeterCumulative_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::Output_Meter_Cumulative_MeterFileOnly) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new OutputMeterCumulativeMeterFileOnly_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::Output_Meter_MeterFileOnly) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new OutputMeterMeterFileOnly_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::Output_PreprocessorMessage) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new OutputPreprocessorMessage_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::Output_SQLite) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new OutputSQLite_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::Output_Schedules) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new OutputSchedules_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::Output_Table_Annual) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new OutputTableAnnual_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::Output_Table_Monthly) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new OutputTableMonthly_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::Output_Table_ReportPeriod) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new OutputTableReportPeriod_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::Output_Table_SummaryReports) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new OutputTableSummaryReports_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::Output_Table_TimeBins) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new OutputTableTimeBins_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::Output_Variable) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new OutputVariable_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::Output_VariableDictionary) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new OutputVariableDictionary_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::Output_Surfaces_List) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new OutputSurfacesList_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::Output_Surfaces_Drawing) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new OutputSurfacesDrawing_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::PythonPlugin_OutputVariable) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new PythonPluginOutputVariable_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::OS_PythonPlugin_TrendVariable) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new PythonPluginTrendVariable_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::OS_PythonPlugin_Variable) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new PythonPluginVariable_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::PythonPlugin_SearchPaths) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new PythonPluginSearchPaths_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::EnergyManagementSystem_Sensor) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new EnergyManagementSystemSensor_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::EnergyManagementSystem_TrendVariable) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new EnergyManagementSystemTrendVariable_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::EnvironmentalImpactFactors) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new EnvironmentalImpactFactors_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::FuelFactors) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new FuelFactors_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::Meter_Custom) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new MeterCustom_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::Meter_CustomDecrement) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new MeterCustomDecrement_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::EnergyManagementSystem_Program) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new EnergyManagementSystemProgram_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::EnergyManagementSystem_Subroutine) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new EnergyManagementSystemSubroutine_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::EnergyManagementSystem_ProgramCallingManager) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new EnergyManagementSystemProgramCallingManager_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::ElectricLoadCenter_Inverter_LookUpTable) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new ElectricLoadCenterInverterLookUpTable_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::ElectricLoadCenter_Inverter_PVWatts) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new ElectricLoadCenterInverterPVWatts_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::ElectricLoadCenter_Inverter_Simple) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new ElectricLoadCenterInverterSimple_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::ElectricLoadCenter_Storage_Battery) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new ElectricLoadCenterStorageBattery_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::ElectricLoadCenter_Storage_Simple) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new ElectricLoadCenterStorageSimple_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::ElectricLoadCenter_Storage_LiIonNMCBattery) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new ElectricLoadCenterStorageLiIonNMCBattery_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::ComponentCost_LineItem) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new ComponentCostLineItem_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::ComponentCost_Reference) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new ComponentCostReference_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::LifeCycleCost_NonrecurringCost) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new LifeCycleCost_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::LifeCycleCost_RecurringCosts) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new LifeCycleCost_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::LifeCycleCost_UseAdjustment) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new LifeCycleCostUseAdjustment_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::CondenserLoop) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new CondenserLoop_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::CondenserEquipmentList) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new CondenserEquipmentList_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::CondenserEquipmentOperationSchemes) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new CondenserEquipmentOperationSchemes_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::ConvergenceLimits) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new ConvergenceLimits_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::PerformancePrecisionTradeoffs) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new PerformancePrecisionTradeoffs_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::HeatBalanceAlgorithm) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new HeatBalanceAlgorithm_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::HybridModel_Zone) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new HybridModelZone_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::IndoorLivingWall) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new IndoorLivingWall_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::HeatBalanceSettings_ConductionFiniteDifference) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new HeatBalanceSettingsConductionFiniteDifference_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::HVACTemplate_Plant_Boiler) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new HVACTemplatePlantBoiler_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::HVACTemplate_Plant_Boiler_ObjectReference) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new HVACTemplatePlantBoilerObjectReference_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::HVACTemplate_Plant_ChilledWaterLoop) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new HVACTemplatePlantChilledWaterLoop_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::HVACTemplate_Plant_Chiller) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new HVACTemplatePlantChiller_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::HVACTemplate_Plant_Chiller_ObjectReference) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new HVACTemplatePlantChillerObjectReference_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::HVACTemplate_Plant_HotWaterLoop) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new HVACTemplatePlantHotWaterLoop_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::HVACTemplate_Plant_MixedWaterLoop) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new HVACTemplatePlantMixedWaterLoop_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::HVACTemplate_Plant_Tower) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new HVACTemplatePlantTower_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::HVACTemplate_Plant_Tower_ObjectReference) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new HVACTemplatePlantTowerObjectReference_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::HVACTemplate_System_ConstantVolume) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new HVACTemplateSystemConstantVolume_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::HVACTemplate_System_DedicatedOutdoorAir) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new HVACTemplateSystemDedicatedOutdoorAir_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::HVACTemplate_System_DualDuct) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new HVACTemplateSystemDualDuct_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::HVACTemplate_System_PackagedVAV) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new HVACTemplateSystemPackagedVAV_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::HVACTemplate_System_VAV) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new HVACTemplateSystemVAV_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::HVACTemplate_System_VRF) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new HVACTemplateSystemVRF_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::HVACTemplate_Thermostat) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new HVACTemplateThermostat_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::HVACTemplate_Zone_BaseboardHeat) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new HVACTemplateZoneBaseboardHeat_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::HVACTemplate_Zone_ConstantVolume) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new HVACTemplateZoneConstantVolume_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::HVACTemplate_Zone_DualDuct) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new HVACTemplateZoneDualDuct_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::HVACTemplate_Zone_FanCoil) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new HVACTemplateZoneFanCoil_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::HVACTemplate_Zone_PTAC) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new HVACTemplateZonePTAC_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::HVACTemplate_Zone_PTHP) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new HVACTemplateZonePTHP_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::HVACTemplate_Zone_WaterToAirHeatPump) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new HVACTemplateZoneWaterToAirHeatPump_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::HVACTemplate_Zone_VAV) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new HVACTemplateZoneVAV_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::HVACTemplate_Zone_VAV_HeatAndCool) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new HVACTemplateZoneVAVHeatAndCool_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::HVACTemplate_Zone_VAV_FanPowered) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new HVACTemplateZoneVAVFanPowered_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::HVACTemplate_Zone_VRF) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new HVACTemplateZoneVRF_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::HVACTemplate_Zone_Unitary) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new HVACTemplateZoneUnitary_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::HVACTemplate_System_UnitaryHeatPump_AirToAir) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new HVACTemplateSystemUnitaryHeatPumpAirToAir_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::HVACTemplate_System_UnitarySystem) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new HVACTemplateSystemUnitarySystem_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::HVACTemplate_System_Unitary) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new HVACTemplateSystemUnitary_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::HVACSystemRootFindingAlgorithm) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new HVACSystemRootFindingAlgorithm_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::SurfaceConvectionAlgorithm_Inside) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new InsideSurfaceConvectionAlgorithm_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::SurfaceConvectionAlgorithm_Outside) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new OutsideSurfaceConvectionAlgorithm_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::SurfaceConvectionAlgorithm_Inside_AdaptiveModelSelections) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new SurfaceConvectionAlgorithmInsideAdaptiveModelSelections_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::SurfaceConvectionAlgorithm_Outside_AdaptiveModelSelections) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new SurfaceConvectionAlgorithmOutsideAdaptiveModelSelections_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::SurfaceConvectionAlgorithm_Inside_UserCurve) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new SurfaceConvectionAlgorithmInsideUserCurve_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::SurfaceConvectionAlgorithm_Outside_UserCurve) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new SurfaceConvectionAlgorithmOutsideUserCurve_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::SurfaceProperty_ConvectionCoefficients) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new SurfacePropertyConvectionCoefficients_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::SurfaceProperty_ConvectionCoefficients_MultipleSurface) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new SurfacePropertyConvectionCoefficientsMultipleSurface_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::SurfaceProperty_ExposedFoundationPerimeter) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new SurfacePropertyExposedFoundationPerimeter_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::SurfaceProperty_ExteriorNaturalVentedCavity) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new SurfacePropertyExteriorNaturalVentedCavity_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::SurfaceProperty_GroundSurfaces) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new SurfacePropertyGroundSurfaces_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::SurfaceProperty_HeatBalanceSourceTerm) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new SurfacePropertyHeatBalanceSourceTerm_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::SurfaceProperty_IncidentSolarMultiplier) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new SurfacePropertyIncidentSolarMultiplier_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::SurfaceProperty_HeatTransferAlgorithm) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new SurfacePropertyHeatTransferAlgorithm_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::SurfaceProperty_HeatTransferAlgorithm_Construction) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new SurfacePropertyHeatTransferAlgorithmConstruction_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::SurfaceProperty_HeatTransferAlgorithm_MultipleSurface) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new SurfacePropertyHeatTransferAlgorithmMultipleSurface_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::SurfaceProperty_HeatTransferAlgorithm_SurfaceList) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new SurfacePropertyHeatTransferAlgorithmSurfaceList_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::SurfaceProperty_SolarIncidentInside) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new SurfacePropertySolarIncidentInside_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::SurfaceProperty_SurroundingSurfaces) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new SurfacePropertySurroundingSurfaces_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::SurfaceProperty_Underwater) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new SurfacePropertyUnderwater_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::SurfaceProperty_OtherSideCoefficients) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new SurfacePropertyOtherSideCoefficients_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::OS_SurfaceProperty_OtherSideConditionsModel) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new SurfacePropertyOtherSideConditionsModel_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::GlobalGeometryRules) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new GlobalGeometryRules_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::DaylightingDevice_LightWell) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new DaylightingDeviceLightWell_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::DaylightingDevice_Shelf) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new DaylightingDeviceShelf_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::DaylightingDevice_Tubular) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new DaylightingDeviceTubular_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::Daylighting_DELight_ComplexFenestration) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new DaylightingDELightComplexFenestration_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::Dehumidifier_Desiccant_NoFans) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new DehumidifierDesiccantNoFans_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::Dehumidifier_Desiccant_System) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new DehumidifierDesiccantSystem_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::Curve_Bicubic) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new CurveBicubic_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::Curve_Cubic) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new CurveCubic_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::Curve_Biquadratic) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new CurveBiquadratic_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::Curve_Exponent) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new CurveExponent_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::Curve_DoubleExponentialDecay) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new CurveDoubleExponentialDecay_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::Curve_ExponentialDecay) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new CurveExponentialDecay_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::Curve_ExponentialSkewNormal) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new CurveExponentialSkewNormal_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::Curve_FanPressureRise) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new CurveFanPressureRise_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::Curve_Functional_PressureDrop) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new CurveFunctionalPressureDrop_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::Curve_Linear) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new CurveLinear_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::Curve_Quadratic) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new CurveQuadratic_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::Curve_Quartic) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new CurveQuartic_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::Curve_QuadLinear) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new CurveQuadLinear_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::Curve_QuintLinear) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new CurveQuintLinear_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::Curve_RectangularHyperbola1) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new CurveRectangularHyperbola1_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::Curve_RectangularHyperbola2) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new CurveRectangularHyperbola2_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::Curve_Sigmoid) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new CurveSigmoid_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::Curve_Triquadratic) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new CurveTriquadratic_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::Curve_QuadraticLinear) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new CurveQuadraticLinear_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::Curve_CubicLinear) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new CurveCubicLinear_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::Curve_ChillerPartLoadWithLift) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new CurveChillerPartLoadWithLift_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::AirflowNetwork_Distribution_Component_Coil) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new AirflowNetworkDistributionComponentCoil_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::AirflowNetwork_Distribution_Component_ConstantPressureDrop) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new AirflowNetworkDistributionComponentConstantPressureDrop_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::Ceiling_Adiabatic) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new CeilingAdiabatic_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::Ceiling_Interzone) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new CeilingInterzone_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::Roof) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new Roof_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::RoofIrrigation) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new RoofIrrigation_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::RoofCeiling_Detailed) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new RoofCeilingDetailed_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::Wall_Adiabatic) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new WallAdiabatic_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::Wall_Detailed) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new WallDetailed_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::Wall_Exterior) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new WallExterior_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::Wall_Interzone) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new WallInterzone_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::Wall_Underground) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new WallUnderground_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::Door) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new Door_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::Door_Interzone) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new DoorInterzone_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::GlazedDoor) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new GlazedDoor_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::GlazedDoor_Interzone) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new GlazedDoorInterzone_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::Window_Interzone) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new WindowInterzone_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::WindowGap_DeflectionState) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new WindowGapDeflectionState_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::WindowGap_SupportPillar) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new WindowGapSupportPillar_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::WindowProperty_AirflowControl) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new WindowPropertyAirflowControl_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::WindowProperty_StormWindow) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new WindowPropertyStormWindow_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::WindowThermalModel_Params) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new WindowThermalModelParams_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::WindowsCalculationEngine) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new WindowsCalculationEngine_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::WindowProperty_FrameAndDivider) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new WindowPropertyFrameAndDivider_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::WindowShadingControl) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new ShadingControl_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::AirflowNetwork_Distribution_Component_Duct) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new AirflowNetworkDistributionComponentDuct_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::AirflowNetwork_Distribution_DuctSizing) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new AirflowNetworkDistributionDuctSizing_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::AirflowNetwork_Distribution_DuctViewFactors) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new AirflowNetworkDistributionDuctViewFactors_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::AirflowNetwork_Distribution_Linkage) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new AirflowNetworkDistributionLinkage_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::AirflowNetwork_Distribution_Node) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new AirflowNetworkDistributionNode_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::AirflowNetwork_IntraZone_Node) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new AirflowNetworkIntraZoneNode_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::AirflowNetwork_IntraZone_Linkage) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new AirflowNetworkIntraZoneLinkage_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::AirflowNetwork_MultiZone_ExternalNode) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new AirflowNetworkMultiZoneExternalNode_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::AirflowNetwork_MultiZone_Zone) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new AirflowNetworkMultiZoneZone_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::AirflowNetwork_MultiZone_SpecifiedFlowRate) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new AirflowNetworkMultiZoneSpecifiedFlowRate_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::AirflowNetwork_MultiZone_ReferenceCrackConditions) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new AirflowNetworkMultiZoneReferenceCrackConditions_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::AirflowNetwork_MultiZone_WindPressureCoefficientArray) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new AirflowNetworkMultiZoneWindPressureCoefficientArray_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::AirflowNetwork_MultiZone_WindPressureCoefficientValues) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new AirflowNetworkMultiZoneWindPressureCoefficientValues_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::AirflowNetwork_MultiZone_Surface) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new AirflowNetworkMultiZoneSurface_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::AirflowNetwork_MultiZone_Surface_Crack) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new AirflowNetworkMultiZoneSurfaceCrack_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::AirflowNetwork_MultiZone_Surface_EffectiveLeakageArea) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new AirflowNetworkMultiZoneSurfaceEffectiveLeakageArea_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::AirflowNetwork_MultiZone_Component_DetailedOpening) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new AirflowNetworkMultiZoneComponentDetailedOpening_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::AirflowNetwork_MultiZone_Component_HorizontalOpening) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new AirflowNetworkMultiZoneComponentHorizontalOpening_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::AirflowNetwork_MultiZone_Component_SimpleOpening) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new AirflowNetworkMultiZoneComponentSimpleOpening_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::AirflowNetwork_MultiZone_Component_ZoneExhaustFan) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new AirflowNetworkMultiZoneComponentZoneExhaustFan_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::AirflowNetwork_OccupantVentilationControl) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new AirflowNetworkOccupantVentilationControl_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::AirflowNetwork_SimulationControl) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new AirflowNetworkSimulationControl_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::SimulationControl) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new SimulationControl_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::OS_Timestep) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new Timestep_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::AirflowNetwork_ZoneControl_PressureController) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new AirflowNetworkZoneControlPressureController_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::AirflowNetwork_Distribution_Component_Fan) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new AirflowNetworkDistributionComponentFan_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::AirflowNetwork_Distribution_Component_HeatExchanger) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new AirflowNetworkDistributionComponentHeatExchanger_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::AirflowNetwork_Distribution_Component_Leak) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new AirflowNetworkDistributionComponentLeak_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::AirflowNetwork_Distribution_Component_LeakageRatio) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new AirflowNetworkDistributionComponentLeakageRatio_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::AirflowNetwork_Distribution_Component_OutdoorAirFlow) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new AirflowNetworkDistributionComponentOutdoorAirFlow_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::AirflowNetwork_Distribution_Component_ReliefAirFlow) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new AirflowNetworkDistributionComponentReliefAirFlow_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::AirflowNetwork_Distribution_Component_TerminalUnit) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new AirflowNetworkDistributionComponentTerminalUnit_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::AirLoopHVAC_DedicatedOutdoorAirSystem) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new AirLoopHVACDedicatedOutdoorAirSystem_Impl(object, this, keepHandle));
      }
      if (type == plantEquipmentOperationChillerHeaterChangeoverType) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new PlantEquipmentOperationChillerHeaterChangeover_Impl(object, this, keepHandle));
      }
      if (type == plantEquipmentOperationComponentSetpointType) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new PlantEquipmentOperationComponentSetpoint_Impl(object, this, keepHandle));
      }
      if (type == plantEquipmentOperationThermalEnergyStorageType) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new PlantEquipmentOperationThermalEnergyStorage_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::PlantEquipmentOperationSchemes) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new PlantEquipmentOperationSchemes_Impl(object, this, keepHandle));
      }
      if (type == plantEquipmentOperationUncontrolledType) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new PlantEquipmentOperationUncontrolled_Impl(object, this, keepHandle));
      }
      if (type == plantEquipmentOperationUserDefinedType) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new PlantEquipmentOperationUserDefined_Impl(object, this, keepHandle));
      }
      if (type == plantEquipmentOperationCoolingLoadType || type == IddObjectType::OS_PlantEquipmentOperation_CoolingLoad) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new PlantEquipmentOperationCoolingLoad_Impl(object, this, keepHandle));
      }
      if (type == plantEquipmentOperationHeatingLoadType || type == IddObjectType::OS_PlantEquipmentOperation_HeatingLoad) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new PlantEquipmentOperationHeatingLoad_Impl(object, this, keepHandle));
      }
      if (type == plantEquipmentOperationOutdoorDewpointType || type == IddObjectType::OS_PlantEquipmentOperation_OutdoorDewpoint) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new PlantEquipmentOperationOutdoorDewpoint_Impl(object, this, keepHandle));
      }
      if (type == plantEquipmentOperationOutdoorDewpointDifferenceType
          || type == IddObjectType::OS_PlantEquipmentOperation_OutdoorDewpointDifference) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new PlantEquipmentOperationOutdoorDewpointDifference_Impl(object, this, keepHandle));
      }
      if (type == plantEquipmentOperationOutdoorDryBulbDifferenceType || type == IddObjectType::OS_PlantEquipmentOperation_OutdoorDryBulbDifference) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new PlantEquipmentOperationOutdoorDryBulbDifference_Impl(object, this, keepHandle));
      }
      if (type == plantEquipmentOperationOutdoorWetBulbDifferenceType || type == IddObjectType::OS_PlantEquipmentOperation_OutdoorWetBulbDifference) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new PlantEquipmentOperationOutdoorWetBulbDifference_Impl(object, this, keepHandle));
      }
      if (type == plantEquipmentOperationOutdoorDryBulbType || type == IddObjectType::OS_PlantEquipmentOperation_OutdoorDryBulb) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new PlantEquipmentOperationOutdoorDryBulb_Impl(object, this, keepHandle));
      }
      if (type == plantEquipmentOperationOutdoorRelativeHumidityType || type == IddObjectType::OS_PlantEquipmentOperation_OutdoorRelativeHumidity) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new PlantEquipmentOperationOutdoorRelativeHumidity_Impl(object, this, keepHandle));
      }
      if (type == plantEquipmentOperationOutdoorWetBulbType || type == IddObjectType::OS_PlantEquipmentOperation_OutdoorWetBulb) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new PlantEquipmentOperationOutdoorWetBulb_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::ZoneAirBalance_OutdoorAir) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new ZoneAirBalanceOutdoorAir_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::ZoneAirContaminantBalance) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new ZoneAirContaminantBalance_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::ZoneAirHeatBalanceAlgorithm) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new ZoneAirHeatBalanceAlgorithm_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::ZoneAirMassFlowConservation) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new ZoneAirMassFlowConservation_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::ZoneCoolTower_Shower) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new ZoneCoolTowerShower_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::ZoneCrossMixing) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new ZoneCrossMixing_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::ZoneMixing) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new ZoneMixing_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::ZoneRefrigerationDoorMixing) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new ZoneRefrigerationDoorMixing_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::ZoneThermalChimney) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new ZoneThermalChimney_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::ZoneProperty_LocalEnvironment) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new ZonePropertyLocalEnvironment_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::ZoneProperty_UserViewFactors_BySurfaceName) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new ZonePropertyUserViewFactorsBySurfaceName_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::ZoneInfiltration_DesignFlowRate) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new SpaceInfiltrationDesignFlowRate_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::ZoneInfiltration_FlowCoefficient) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new SpaceInfiltrationFlowCoefficient_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::ZoneInfiltration_EffectiveLeakageArea) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new SpaceInfiltrationEffectiveLeakageArea_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::ZoneEarthtube) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new ZoneEarthtube_Impl(object, this, keepHandle));
      }
      if (type == ZoneEarthtubeParameters::iddObjectType()) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new ZoneEarthtubeParameters_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::ZoneGroup) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new ZoneGroup_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::ZoneControl_ContaminantController) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new ZoneControlContaminantController_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::OS_ZoneControl_Humidistat) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new ZoneControlHumidistat_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::ZoneControl_Thermostat_OperativeTemperature) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new ZoneControlThermostatOperativeTemperature_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::ZoneControl_Thermostat_TemperatureAndHumidity) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new ZoneControlThermostatTemperatureAndHumidity_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::ZoneControl_Thermostat_ThermalComfort) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new ZoneControlThermostatThermalComfort_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::ZoneControl_Thermostat_StagedDualSetpoint) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new ZoneControlThermostatStagedDualSetpoint_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::ZoneContaminantSourceAndSink_CarbonDioxide) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new ZoneContaminantSourceAndSinkCarbonDioxide_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::ZoneContaminantSourceAndSink_Generic_Constant) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new ZoneContaminantSourceAndSinkGenericConstant_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::ZoneContaminantSourceAndSink_Generic_CutoffModel) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new ZoneContaminantSourceAndSinkGenericCutoffModel_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::ZoneContaminantSourceAndSink_Generic_DecaySource) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new ZoneContaminantSourceAndSinkGenericDecaySource_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::ZoneContaminantSourceAndSink_Generic_DepositionRateSink) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new ZoneContaminantSourceAndSinkGenericDepositionRateSink_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::ZoneBaseboard_OutdoorTemperatureControlled) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new ZoneBaseboardOutdoorTemperatureControlled_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::ZoneCapacitanceMultiplier_ResearchSpecial) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new ZoneCapacitanceMultiplierResearchSpecial_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::UtilityCost_Charge_Block) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new UtilityCostChargeBlock_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::UtilityCost_Charge_Simple) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new UtilityCostChargeSimple_Impl(object, this, keepHandle));
      }
      if (type == UtilityCostComputation::iddObjectType()) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new UtilityCostComputation_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::UtilityCost_Qualify) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new UtilityCostQualify_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::UtilityCost_Ratchet) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new UtilityCostRatchet_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::UtilityCost_Tariff) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new UtilityCostTariff_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::UtilityCost_Variable) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new UtilityCostVariable_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::DemandManager_ElectricEquipment) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new DemandManagerElectricEquipment_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::DemandManager_ExteriorLights) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new DemandManagerExteriorLights_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::Exterior_Lights) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new ExteriorLights_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::Exterior_FuelEquipment) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new ExteriorFuelEquipment_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::Exterior_WaterEquipment) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new ExteriorWaterEquipment_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::ExternalInterface) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new ExternalInterface_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::ExternalInterface_Actuator) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new ExternalInterfaceActuator_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::ExternalInterface_Variable) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new ExternalInterfaceVariable_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::ExternalInterface_FunctionalMockupUnitImport) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new ExternalInterfaceFunctionalMockupUnitImport_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::ExternalInterface_FunctionalMockupUnitImport_From_Variable) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new ExternalInterfaceFunctionalMockupUnitImportFromVariable_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::ExternalInterface_FunctionalMockupUnitImport_To_Actuator) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new ExternalInterfaceFunctionalMockupUnitImportToActuator_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::ExternalInterface_FunctionalMockupUnitImport_To_Variable) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new ExternalInterfaceFunctionalMockupUnitImportToVariable_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::ExternalInterface_FunctionalMockupUnitExport_From_Variable) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new ExternalInterfaceFunctionalMockupUnitExportFromVariable_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::ExternalInterface_FunctionalMockupUnitExport_To_Actuator) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new ExternalInterfaceFunctionalMockupUnitExportToActuator_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::ExternalInterface_FunctionalMockupUnitExport_To_Variable) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new ExternalInterfaceFunctionalMockupUnitExportToVariable_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::ExternalInterface_FunctionalMockupUnitImport_To_Schedule) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new ExternalInterfaceFunctionalMockupUnitImportToSchedule_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::ExternalInterface_FunctionalMockupUnitExport_To_Schedule) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new ExternalInterfaceFunctionalMockupUnitExportToSchedule_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::ExternalInterface_Schedule) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new ExternalInterfaceSchedule_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::Schedule_Compact) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new ScheduleCompact_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::Schedule_Constant) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new ScheduleConstant_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::Schedule_Year) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new ScheduleRuleset_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::Schedule_Day_Interval) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new ScheduleDay_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::Schedule_File) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new ScheduleFile_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::Schedule_File_Shading) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new ScheduleFileShading_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::Schedule_Day_List) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new ScheduleDayList_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::Schedule_Day_Hourly) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new ScheduleDayHourly_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::Schedule_Week_Compact) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new ScheduleWeekCompact_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::ScheduleTypeLimits) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new ScheduleTypeLimits_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::Table_IndependentVariable) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new TableIndependentVariable_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::Table_Lookup) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new TableLookup_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::Schedule_Week_Daily) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new ScheduleWeek_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::SpaceList) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new SpaceType_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::DemandManager_Lights) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new DemandManagerLights_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::DemandManager_Thermostats) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new DemandManagerThermostats_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::DemandManager_Ventilation) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new DemandManagerVentilation_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::DemandManagerAssignmentList) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new DemandManagerAssignmentList_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::Matrix_TwoDimension) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new MatrixTwoDimension_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::ElectricEquipment) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new ElectricEquipment_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::ElectricEquipment_ITE_AirCooled) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new ElectricEquipmentITEAirCooled_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::GasEquipment) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new GasEquipment_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::HotWaterEquipment) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new HotWaterEquipment_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::SteamEquipment) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new SteamEquipment_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::OtherEquipment) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new OtherEquipment_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::Lights) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new Lights_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::People) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new People_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::WaterUse_Equipment) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new WaterUseEquipment_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::WaterUse_RainCollector) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new WaterUseRainCollector_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::WaterUse_Storage) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new WaterUseStorage_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::WaterUse_Well) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new WaterUseWell_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::Material) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new StandardOpaqueMaterial_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::Material_AirGap) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new AirGap_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::Material_NoMass) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new MasslessOpaqueMaterial_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::Material_RoofVegetation) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new RoofVegetation_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::OS_WindowMaterial_Glazing_RefractionExtinctionMethod) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new RefractionExtinctionGlazing_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::OS_WindowMaterial_GlazingGroup_Thermochromic) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new ThermochromicGlazing_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::OS_WindowMaterial_Glazing) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new StandardGlazing_Impl(object, this, keepHandle));
      }
      // Schema Alignment Notes:
      // - API: Preserves openstudio::model::SimpleGlazing scalar names/signatures while keeping the epmodel surface focused on scalars.
      // - Field Mapping: Maps WindowMaterial:SimpleGlazingSystem fields (U Factor, Solar Heat Gain Coefficient, Visible Transmittance)
      //   through WindowMaterial_SimpleGlazingSystemFields per ForwardTranslator/ForwardTranslateSimpleGlazing.cpp.
      if (type == IddObjectType::WindowMaterial_SimpleGlazingSystem) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new SimpleGlazing_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::HeatExchanger_AirToAir_FlatPlate) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new HeatExchangerAirToAirFlatPlate_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::HeatExchanger_AirToAir_SensibleAndLatent) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new HeatExchangerAirToAirSensibleAndLatent_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::HeatExchanger_Desiccant_BalancedFlow) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new HeatExchangerDesiccantBalancedFlow_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::AirLoopHVAC_ExhaustSystem) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new AirLoopHVACExhaustSystem_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::AirLoopHVAC_Mixer) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new AirLoopHVACMixer_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::AirLoopHVAC_Splitter) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new AirLoopHVACSplitter_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::SpaceHVAC_ZoneReturnMixer) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new SpaceHVACZoneReturnMixer_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::GroundHeatTransfer_Control) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new GroundHeatTransferControl_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::GroundHeatTransfer_Basement_AutoGrid) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new GroundHeatTransferBasementAutoGrid_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::GroundHeatTransfer_Basement_BldgData) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new GroundHeatTransferBasementBldgData_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::GroundHeatTransfer_Basement_ComBldg) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new GroundHeatTransferBasementComBldg_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::GroundHeatTransfer_Basement_MatlProps) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new GroundHeatTransferBasementMatlProps_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::GroundHeatTransfer_Basement_Insulation) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new GroundHeatTransferBasementInsulation_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::GroundHeatTransfer_Basement_ManualGrid) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new GroundHeatTransferBasementManualGrid_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::GroundHeatTransfer_Basement_SimParameters) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new GroundHeatTransferBasementSimParameters_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::GroundHeatTransfer_Basement_SurfaceProps) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new GroundHeatTransferBasementSurfaceProps_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::GroundHeatTransfer_Basement_XFACE) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new GroundHeatTransferBasementXFACE_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::GroundHeatTransfer_Basement_YFACE) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new GroundHeatTransferBasementYFACE_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::GroundHeatTransfer_Basement_ZFACE) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new GroundHeatTransferBasementZFACE_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::GroundHeatTransfer_Slab_AutoGrid) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new GroundHeatTransferSlabAutoGrid_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::GroundHeatTransfer_Slab_ManualGrid) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new GroundHeatTransferSlabManualGrid_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::GroundHeatTransfer_Slab_BoundConds) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new GroundHeatTransferSlabBoundConds_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::GroundHeatTransfer_Slab_BldgProps) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new GroundHeatTransferSlabBldgProps_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::GroundHeatTransfer_Slab_EquivalentSlab) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new GroundHeatTransferSlabEquivalentSlab_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::GroundHeatTransfer_Slab_Materials) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new GroundHeatTransferSlabMaterials_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::GroundHeatTransfer_Slab_MatlProps) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new GroundHeatTransferSlabMatlProps_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::GroundHeatTransfer_Slab_Insulation) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new GroundHeatTransferSlabInsulation_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::GroundHeatTransfer_Slab_XFACE) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new GroundHeatTransferSlabXFACE_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::GroundHeatTransfer_Slab_YFACE) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new GroundHeatTransferSlabYFACE_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::GroundHeatTransfer_Slab_ZFACE) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new GroundHeatTransferSlabZFACE_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::Site_GroundDomain_Slab) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new SiteGroundDomainSlab_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::Site_GroundDomain_Basement) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new SiteGroundDomainBasement_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::Site_GroundTemperature_Deep) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new SiteGroundTemperatureDeep_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::Site_GroundTemperature_FCfactorMethod) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new SiteGroundTemperatureFCfactorMethod_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::Site_GroundTemperature_Shallow) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new SiteGroundTemperatureShallow_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::Site_GroundTemperature_BuildingSurface) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new SiteGroundTemperatureBuildingSurface_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::Site_GroundTemperature_Undisturbed_FiniteDifference) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new SiteGroundTemperatureUndisturbedFiniteDifference_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::Site_GroundTemperature_Undisturbed_KusudaAchenbach) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new SiteGroundTemperatureUndisturbedKusudaAchenbach_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::Site_GroundTemperature_Undisturbed_Xing) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new SiteGroundTemperatureUndisturbedXing_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::Site_GroundReflectance) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new SiteGroundReflectance_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::Site_GroundReflectance_SnowModifier) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new SiteGroundReflectanceSnowModifier_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::Site_Precipitation) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new SitePrecipitation_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::Site_WaterMainsTemperature) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new SiteWaterMainsTemperature_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::Site_WeatherStation) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new SiteWeatherStation_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::Site_SolarAndVisibleSpectrum) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new SiteSolarAndVisibleSpectrum_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::Site_SpectrumData) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new SiteSpectrumData_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::WeatherProperty_SkyTemperature) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new SkyTemperature_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::Construction) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new Construction_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::ConstructionProperty_InternalHeatSource) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new ConstructionWithInternalSource_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::Construction_AirBoundary) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new ConstructionAirBoundary_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::Construction_CfactorUndergroundWall) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new CFactorUndergroundWallConstruction_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::Construction_FfactorGroundFloor) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new FFactorGroundFloorConstruction_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::Construction_WindowDataFile) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new ConstructionWindowDataFile_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::Construction_WindowEquivalentLayer) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new ConstructionWindowEquivalentLayer_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::RoomAir_TemperaturePattern_ConstantGradient) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new RoomAirTemperaturePatternConstantGradient_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::RoomAir_TemperaturePattern_NondimensionalHeight) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new RoomAirTemperaturePatternNondimensionalHeight_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::RoomAir_TemperaturePattern_SurfaceMapping) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new RoomAirTemperaturePatternSurfaceMapping_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::RoomAir_TemperaturePattern_TwoGradient) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new RoomAirTemperaturePatternTwoGradient_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::RoomAir_TemperaturePattern_UserDefined) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new RoomAirTemperaturePatternUserDefined_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::RoomAirModelType) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new RoomAirModelType_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::RoomAirSettings_AirflowNetwork) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new RoomAirSettingsAirflowNetwork_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::RoomAirSettings_CrossVentilation) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new RoomAirSettingsCrossVentilation_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::RoomAirSettings_OneNodeDisplacementVentilation) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new RoomAirSettingsOneNodeDisplacementVentilation_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::RoomAirSettings_ThreeNodeDisplacementVentilation) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new RoomAirSettingsThreeNodeDisplacementVentilation_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::RoomAirSettings_UnderFloorAirDistributionExterior) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new RoomAirSettingsUnderFloorAirDistributionExterior_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::RoomAirSettings_UnderFloorAirDistributionInterior) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new RoomAirSettingsUnderFloorAirDistributionInterior_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::RoomAir_Node) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new RoomAirNode_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::RoomAir_Node_AirflowNetwork) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new RoomAirNodeAirflowNetwork_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::RoomAir_Node_AirflowNetwork_AdjacentSurfaceList) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new RoomAirNodeAirflowNetworkAdjacentSurfaceList_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::RoomAir_Node_AirflowNetwork_HVACEquipment) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new RoomAirNodeAirflowNetworkHVACEquipment_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::RoomAir_Node_AirflowNetwork_InternalGains) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new RoomAirNodeAirflowNetworkInternalGains_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::AirLoopHVAC_Unitary_Furnace_HeatCool) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new AirLoopHVACUnitaryFurnaceHeatCool_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::AirLoopHVAC_Unitary_Furnace_HeatOnly) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new AirLoopHVACUnitaryFurnaceHeatOnly_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::AirLoopHVAC_UnitaryHeatCool) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new AirLoopHVACUnitaryHeatCool_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::AirLoopHVAC_UnitaryHeatOnly) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new AirLoopHVACUnitaryHeatOnly_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::AirLoopHVAC_UnitaryHeatPump_AirToAir) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new AirLoopHVACUnitaryHeatPumpAirToAir_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::AirLoopHVAC_UnitaryHeatPump_WaterToAir) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new AirLoopHVACUnitaryHeatPumpWaterToAir_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::AirLoopHVAC_UnitaryHeatPump_AirToAir_MultiSpeed) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new AirLoopHVACUnitaryHeatPumpAirToAirMultiSpeed_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::AirLoopHVAC_UnitaryHeatCool_VAVChangeoverBypass) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new AirLoopHVACUnitaryHeatCoolVAVChangeoverBypass_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::AirLoopHVAC_UnitarySystem) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new AirLoopHVACUnitarySystem_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::WaterHeater_HeatPump_PumpedCondenser) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new WaterHeaterHeatPump_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::OS_WaterHeater_HeatPump_WrappedCondenser) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new WaterHeaterHeatPumpWrappedCondenser_Impl(object, this, keepHandle));
      }
      // Schema Alignment Notes:
      // - EnergyPlus exposes ThermostatSetpoint:DualSetpoint plus ThermostatSetpoint:SingleCooling and ThermostatSetpoint:SingleHeating when only a cooling or heating schedule exists.
      // - Map these single-setpoint IddObjectTypes here as aliases so the existing ThermostatSetpointDualSetpoint API stays stable while Name remains the only scalar.
      if (type == IddObjectType::ThermostatSetpoint_SingleHeatingOrCooling) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new ThermostatSetpointSingleHeatingOrCooling_Impl(object, this, keepHandle));
      }
      if ((type == IddObjectType::ThermostatSetpoint_DualSetpoint) || (type == IddObjectType::ThermostatSetpoint_SingleCooling)
          || (type == IddObjectType::ThermostatSetpoint_SingleHeating)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new ThermostatSetpointDualSetpoint_Impl(object, this, keepHandle));
      }
      // Schema Alignment Notes:
      // - Type has no openstudio::model counterpart and keeps IDD-derived naming.
      // - Field Mapping: Fanger Thermal Comfort Heating Schedule Name and Fanger Thermal Comfort Cooling Schedule Name
      //   are ScheduleNames object-list fields (relationship-like references) and stay excluded from scalar accessors.
      if (type == IddObjectType::ThermostatSetpoint_ThermalComfort_Fanger_DualSetpoint) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new ThermostatSetpointThermalComfortFangerDualSetpoint_Impl(object, this, keepHandle));
      }
      // Schema Alignment Notes:
      // - No openstudio::model counterpart exists, so the class name is IDD-derived.
      // - Field Mapping: Fanger Thermal Comfort Schedule Name is a ScheduleNames object-list relationship and remains excluded from scalar accessor generation.
      if (type == IddObjectType::ThermostatSetpoint_ThermalComfort_Fanger_SingleCooling) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new ThermostatSetpointThermalComfortFangerSingleCooling_Impl(object, this, keepHandle));
      }
      // Schema Alignment Notes:
      // - No openstudio::model counterpart exists, so the class name is IDD-derived.
      // - Field Mapping: Fanger Thermal Comfort Schedule Name is a ScheduleNames object-list relationship and remains excluded from scalar accessor generation.
      if (type == IddObjectType::ThermostatSetpoint_ThermalComfort_Fanger_SingleHeating) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new ThermostatSetpointThermalComfortFangerSingleHeating_Impl(object, this, keepHandle));
      }
      // Schema Alignment Notes:
      // - No openstudio::model counterpart exists, so the class name stays IDD-derived.
      // - Field Mapping: Fanger Thermal Comfort Schedule Name is a ScheduleNames object-list relationship and therefore excluded from scalar accessors.
      if (type == IddObjectType::ThermostatSetpoint_ThermalComfort_Fanger_SingleHeatingOrCooling) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new ThermostatSetpointThermalComfortFangerSingleHeatingOrCooling_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::ThermalStorage_ChilledWater_Mixed) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new ThermalStorageChilledWaterMixed_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::ThermalStorage_ChilledWater_Stratified) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new ThermalStorageChilledWaterStratified_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::ThermalStorage_HotWater_Stratified) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new ThermalStorageHotWaterStratified_Impl(object, this, keepHandle));
      }

      if (type == IddObjectType::ThermalStorage_Ice_Detailed) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new ThermalStorageIceDetailed_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::ThermalStorage_Ice_Simple) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new ThermalStorageIceSimple_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::ThermalStorage_PCM) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new ThermalStoragePCM_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::ThermalStorage_Sizing) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new ThermalStorageSizing_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::Version) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new Version_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::Fan_ZoneExhaust) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new FanZoneExhaust_Impl(object, this, keepHandle));
      }
      return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new ModelObject_Impl(object, this, keepHandle));
    }

    std::shared_ptr<openstudio::detail::WorkspaceObject_Impl> Model_Impl::createObject(const IdfObject& object, bool keepHandle, bool isTransient) {
      auto result = createObject(object, keepHandle);
      result->setTransient(isTransient);
      return result;
    }

    std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>
      Model_Impl::createObject(const std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>& originalObjectImplPtr, bool keepHandle) {

      if (auto airLoop = std::dynamic_pointer_cast<AirLoopHVAC_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new AirLoopHVAC_Impl(*airLoop, this, keepHandle));
      }
      if (auto plantLoop = std::dynamic_pointer_cast<PlantLoop_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new PlantLoop_Impl(*plantLoop, this, keepHandle));
      }
      if (auto supplyPath = std::dynamic_pointer_cast<AirLoopHVACSupplyPath_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new AirLoopHVACSupplyPath_Impl(*supplyPath, this, keepHandle));
      }
      if (auto returnPath = std::dynamic_pointer_cast<AirLoopHVACReturnPath_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new AirLoopHVACReturnPath_Impl(*returnPath, this, keepHandle));
      }
      if (auto returnPlenum = std::dynamic_pointer_cast<AirLoopHVACReturnPlenum_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new AirLoopHVACReturnPlenum_Impl(*returnPlenum, this, keepHandle));
      }
      if (auto supplyPlenum = std::dynamic_pointer_cast<AirLoopHVACSupplyPlenum_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new AirLoopHVACSupplyPlenum_Impl(*supplyPlenum, this, keepHandle));
      }
      if (auto outdoorAirSystem = std::dynamic_pointer_cast<AirLoopHVACOutdoorAirSystem_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new AirLoopHVACOutdoorAirSystem_Impl(*outdoorAirSystem, this, keepHandle));
      }
      if (auto controllerList = std::dynamic_pointer_cast<AirLoopHVACControllerList_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new AirLoopHVACControllerList_Impl(*controllerList, this, keepHandle));
      }
      if (auto zoneSplitter = std::dynamic_pointer_cast<AirLoopHVACZoneSplitter_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new AirLoopHVACZoneSplitter_Impl(*zoneSplitter, this, keepHandle));
      }
      if (auto zoneMixer = std::dynamic_pointer_cast<AirLoopHVACZoneMixer_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new AirLoopHVACZoneMixer_Impl(*zoneMixer, this, keepHandle));
      }
      if (auto construction = std::dynamic_pointer_cast<Construction_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new Construction_Impl(*construction, this, keepHandle));
      }
      if (auto constructionWithInternalSource = std::dynamic_pointer_cast<ConstructionWithInternalSource_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new ConstructionWithInternalSource_Impl(*constructionWithInternalSource, this, keepHandle));
      }
      if (auto constructionAirBoundary = std::dynamic_pointer_cast<ConstructionAirBoundary_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new ConstructionAirBoundary_Impl(*constructionAirBoundary, this, keepHandle));
      }
      if (auto cFactorUndergroundWallConstruction = std::dynamic_pointer_cast<CFactorUndergroundWallConstruction_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new CFactorUndergroundWallConstruction_Impl(*cFactorUndergroundWallConstruction, this, keepHandle));
      }
      if (auto fFactorGroundFloorConstruction = std::dynamic_pointer_cast<FFactorGroundFloorConstruction_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new FFactorGroundFloorConstruction_Impl(*fFactorGroundFloorConstruction, this, keepHandle));
      }
      if (auto availabilityManagerAssignmentList = std::dynamic_pointer_cast<AvailabilityManagerAssignmentList_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new AvailabilityManagerAssignmentList_Impl(*availabilityManagerAssignmentList, this, keepHandle));
      }
      if (auto availabilityManagerNightCycle = std::dynamic_pointer_cast<AvailabilityManagerNightCycle_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new AvailabilityManagerNightCycle_Impl(*availabilityManagerNightCycle, this, keepHandle));
      }
      if (auto availabilityManagerDifferentialThermostat =
            std::dynamic_pointer_cast<AvailabilityManagerDifferentialThermostat_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new AvailabilityManagerDifferentialThermostat_Impl(*availabilityManagerDifferentialThermostat, this, keepHandle));
      }
      if (auto availabilityManagerHighTemperatureTurnOff =
            std::dynamic_pointer_cast<AvailabilityManagerHighTemperatureTurnOff_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new AvailabilityManagerHighTemperatureTurnOff_Impl(*availabilityManagerHighTemperatureTurnOff, this, keepHandle));
      }
      if (auto availabilityManagerHighTemperatureTurnOn =
            std::dynamic_pointer_cast<AvailabilityManagerHighTemperatureTurnOn_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new AvailabilityManagerHighTemperatureTurnOn_Impl(*availabilityManagerHighTemperatureTurnOn, this, keepHandle));
      }
      if (auto availabilityManagerLowTemperatureTurnOff =
            std::dynamic_pointer_cast<AvailabilityManagerLowTemperatureTurnOff_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new AvailabilityManagerLowTemperatureTurnOff_Impl(*availabilityManagerLowTemperatureTurnOff, this, keepHandle));
      }
      if (auto availabilityManagerLowTemperatureTurnOn =
            std::dynamic_pointer_cast<AvailabilityManagerLowTemperatureTurnOn_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new AvailabilityManagerLowTemperatureTurnOn_Impl(*availabilityManagerLowTemperatureTurnOn, this, keepHandle));
      }
      if (auto availabilityManagerHybridVentilation = std::dynamic_pointer_cast<AvailabilityManagerHybridVentilation_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new AvailabilityManagerHybridVentilation_Impl(*availabilityManagerHybridVentilation, this, keepHandle));
      }
      if (auto availabilityManagerNightVentilation = std::dynamic_pointer_cast<AvailabilityManagerNightVentilation_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new AvailabilityManagerNightVentilation_Impl(*availabilityManagerNightVentilation, this, keepHandle));
      }
      if (auto availabilityManagerOptimumStart = std::dynamic_pointer_cast<AvailabilityManagerOptimumStart_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new AvailabilityManagerOptimumStart_Impl(*availabilityManagerOptimumStart, this, keepHandle));
      }
      if (auto availabilityManagerScheduledOff = std::dynamic_pointer_cast<AvailabilityManagerScheduledOff_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new AvailabilityManagerScheduledOff_Impl(*availabilityManagerScheduledOff, this, keepHandle));
      }
      if (auto availabilityManagerScheduledOn = std::dynamic_pointer_cast<AvailabilityManagerScheduledOn_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new AvailabilityManagerScheduledOn_Impl(*availabilityManagerScheduledOn, this, keepHandle));
      }
      if (auto branch = std::dynamic_pointer_cast<Branch_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new Branch_Impl(*branch, this, keepHandle));
      }
      if (auto branchList = std::dynamic_pointer_cast<BranchList_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new BranchList_Impl(*branchList, this, keepHandle));
      }
      if (auto building = std::dynamic_pointer_cast<Building_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new Building_Impl(*building, this, keepHandle));
      }
      if (auto site = std::dynamic_pointer_cast<Site_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new Site_Impl(*site, this, keepHandle));
      }
      if (auto surface = std::dynamic_pointer_cast<Surface_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new Surface_Impl(*surface, this, keepHandle));
      }
      if (auto subSurface = std::dynamic_pointer_cast<SubSurface_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new SubSurface_Impl(*subSurface, this, keepHandle));
      }
      if (auto boilerHotWater = std::dynamic_pointer_cast<BoilerHotWater_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new BoilerHotWater_Impl(*boilerHotWater, this, keepHandle));
      }
      if (auto boilerSteam = std::dynamic_pointer_cast<BoilerSteam_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new BoilerSteam_Impl(*boilerSteam, this, keepHandle));
      }
      if (auto districtCooling = std::dynamic_pointer_cast<DistrictCooling_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new DistrictCooling_Impl(*districtCooling, this, keepHandle));
      }
      if (auto districtHeatingSteam = std::dynamic_pointer_cast<DistrictHeatingSteam_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new DistrictHeatingSteam_Impl(*districtHeatingSteam, this, keepHandle));
      }
      if (auto districtHeatingWater = std::dynamic_pointer_cast<DistrictHeatingWater_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new DistrictHeatingWater_Impl(*districtHeatingWater, this, keepHandle));
      }
      if (auto duct = std::dynamic_pointer_cast<Duct_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new Duct_Impl(*duct, this, keepHandle));
      }
      if (auto pipeAdiabatic = std::dynamic_pointer_cast<PipeAdiabatic_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new PipeAdiabatic_Impl(*pipeAdiabatic, this, keepHandle));
      }
      if (auto pipeIndoor = std::dynamic_pointer_cast<PipeIndoor_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new PipeIndoor_Impl(*pipeIndoor, this, keepHandle));
      }
      if (auto pipeOutdoor = std::dynamic_pointer_cast<PipeOutdoor_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new PipeOutdoor_Impl(*pipeOutdoor, this, keepHandle));
      }
      if (auto pipeAdiabaticSteam = std::dynamic_pointer_cast<PipeAdiabaticSteam_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new PipeAdiabaticSteam_Impl(*pipeAdiabaticSteam, this, keepHandle));
      }
      if (auto pipeUnderground = std::dynamic_pointer_cast<PipeUnderground_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new PipeUnderground_Impl(*pipeUnderground, this, keepHandle));
      }
      if (auto pipingSystemUndergroundDomain = std::dynamic_pointer_cast<PipingSystemUndergroundDomain_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new PipingSystemUndergroundDomain_Impl(*pipingSystemUndergroundDomain, this, keepHandle));
      }
      if (auto pipingSystemUndergroundPipeCircuit = std::dynamic_pointer_cast<PipingSystemUndergroundPipeCircuit_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new PipingSystemUndergroundPipeCircuit_Impl(*pipingSystemUndergroundPipeCircuit, this, keepHandle));
      }
      if (auto pipingSystemUndergroundPipeSegment = std::dynamic_pointer_cast<PipingSystemUndergroundPipeSegment_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new PipingSystemUndergroundPipeSegment_Impl(*pipingSystemUndergroundPipeSegment, this, keepHandle));
      }
      if (auto pumpConstantSpeed = std::dynamic_pointer_cast<PumpConstantSpeed_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new PumpConstantSpeed_Impl(*pumpConstantSpeed, this, keepHandle));
      }
      if (auto pumpVariableSpeed = std::dynamic_pointer_cast<PumpVariableSpeed_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new PumpVariableSpeed_Impl(*pumpVariableSpeed, this, keepHandle));
      }
      if (auto pumpVariableSpeedCondensate = std::dynamic_pointer_cast<PumpVariableSpeedCondensate_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new PumpVariableSpeedCondensate_Impl(*pumpVariableSpeedCondensate, this, keepHandle));
      }
      if (auto headeredPumpsConstantSpeed = std::dynamic_pointer_cast<HeaderedPumpsConstantSpeed_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new HeaderedPumpsConstantSpeed_Impl(*headeredPumpsConstantSpeed, this, keepHandle));
      }
      if (auto headeredPumpsVariableSpeed = std::dynamic_pointer_cast<HeaderedPumpsVariableSpeed_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new HeaderedPumpsVariableSpeed_Impl(*headeredPumpsVariableSpeed, this, keepHandle));
      }
      if (auto humidifierSteamElectric = std::dynamic_pointer_cast<HumidifierSteamElectric_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new HumidifierSteamElectric_Impl(*humidifierSteamElectric, this, keepHandle));
      }
      if (auto humidifierSteamGas = std::dynamic_pointer_cast<HumidifierSteamGas_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new HumidifierSteamGas_Impl(*humidifierSteamGas, this, keepHandle));
      }
      if (auto ductLossConduction = std::dynamic_pointer_cast<DuctLossConduction_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new DuctLossConduction_Impl(*ductLossConduction, this, keepHandle));
      }
      if (auto ductLossLeakage = std::dynamic_pointer_cast<DuctLossLeakage_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new DuctLossLeakage_Impl(*ductLossLeakage, this, keepHandle));
      }
      if (auto ductLossMakeupAir = std::dynamic_pointer_cast<DuctLossMakeupAir_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new DuctLossMakeupAir_Impl(*ductLossMakeupAir, this, keepHandle));
      }
      if (auto evaporativeCoolerDirectCelDekPad = std::dynamic_pointer_cast<EvaporativeCoolerDirectCelDekPad_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new EvaporativeCoolerDirectCelDekPad_Impl(*evaporativeCoolerDirectCelDekPad, this, keepHandle));
      }
      if (auto evaporativeCoolerDirectResearchSpecial =
            std::dynamic_pointer_cast<EvaporativeCoolerDirectResearchSpecial_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new EvaporativeCoolerDirectResearchSpecial_Impl(*evaporativeCoolerDirectResearchSpecial, this, keepHandle));
      }
      if (auto evaporativeCoolerIndirectResearchSpecial =
            std::dynamic_pointer_cast<EvaporativeCoolerIndirectResearchSpecial_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new EvaporativeCoolerIndirectResearchSpecial_Impl(*evaporativeCoolerIndirectResearchSpecial, this, keepHandle));
      }
      if (auto evaporativeCoolerIndirectCelDekPad = std::dynamic_pointer_cast<EvaporativeCoolerIndirectCelDekPad_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new EvaporativeCoolerIndirectCelDekPad_Impl(*evaporativeCoolerIndirectCelDekPad, this, keepHandle));
      }
      if (auto evaporativeCoolerIndirectWetCoil = std::dynamic_pointer_cast<EvaporativeCoolerIndirectWetCoil_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new EvaporativeCoolerIndirectWetCoil_Impl(*evaporativeCoolerIndirectWetCoil, this, keepHandle));
      }
      if (auto evaporativeFluidCoolerSingleSpeed = std::dynamic_pointer_cast<EvaporativeFluidCoolerSingleSpeed_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new EvaporativeFluidCoolerSingleSpeed_Impl(*evaporativeFluidCoolerSingleSpeed, this, keepHandle));
      }
      if (auto evaporativeFluidCoolerTwoSpeed = std::dynamic_pointer_cast<EvaporativeFluidCoolerTwoSpeed_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new EvaporativeFluidCoolerTwoSpeed_Impl(*evaporativeFluidCoolerTwoSpeed, this, keepHandle));
      }
      if (auto fluidCoolerSingleSpeed = std::dynamic_pointer_cast<FluidCoolerSingleSpeed_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new FluidCoolerSingleSpeed_Impl(*fluidCoolerSingleSpeed, this, keepHandle));
      }
      if (auto fluidCoolerTwoSpeed = std::dynamic_pointer_cast<FluidCoolerTwoSpeed_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new FluidCoolerTwoSpeed_Impl(*fluidCoolerTwoSpeed, this, keepHandle));
      }
      if (auto groundHeatExchangerHorizontalTrench = std::dynamic_pointer_cast<GroundHeatExchangerHorizontalTrench_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new GroundHeatExchangerHorizontalTrench_Impl(*groundHeatExchangerHorizontalTrench, this, keepHandle));
      }
      if (auto groundHeatExchangerVertical = std::dynamic_pointer_cast<GroundHeatExchangerVertical_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new GroundHeatExchangerVertical_Impl(*groundHeatExchangerVertical, this, keepHandle));
      }
      if (auto groundHeatExchangerVerticalArray = std::dynamic_pointer_cast<GroundHeatExchangerVerticalArray_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new GroundHeatExchangerVerticalArray_Impl(*groundHeatExchangerVerticalArray, this, keepHandle));
      }
      if (auto groundHeatExchangerVerticalSingle = std::dynamic_pointer_cast<GroundHeatExchangerVerticalSingle_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new GroundHeatExchangerVerticalSingle_Impl(*groundHeatExchangerVerticalSingle, this, keepHandle));
      }
      if (auto groundHeatExchangerVerticalSizingRectangle =
            std::dynamic_pointer_cast<GroundHeatExchangerVerticalSizingRectangle_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new GroundHeatExchangerVerticalSizingRectangle_Impl(*groundHeatExchangerVerticalSizingRectangle, this, keepHandle));
      }
      if (auto groundHeatExchangerPond = std::dynamic_pointer_cast<GroundHeatExchangerPond_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new GroundHeatExchangerPond_Impl(*groundHeatExchangerPond, this, keepHandle));
      }
      if (auto groundHeatExchangerSurface = std::dynamic_pointer_cast<GroundHeatExchangerSurface_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new GroundHeatExchangerSurface_Impl(*groundHeatExchangerSurface, this, keepHandle));
      }
      if (auto groundHeatExchangerSlinky = std::dynamic_pointer_cast<GroundHeatExchangerSlinky_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new GroundHeatExchangerSlinky_Impl(*groundHeatExchangerSlinky, this, keepHandle));
      }
      if (auto fluidPropertiesConcentration = std::dynamic_pointer_cast<FluidPropertiesConcentration_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new FluidPropertiesConcentration_Impl(*fluidPropertiesConcentration, this, keepHandle));
      }
      if (auto fluidPropertiesGlycolConcentration = std::dynamic_pointer_cast<FluidPropertiesGlycolConcentration_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new FluidPropertiesGlycolConcentration_Impl(*fluidPropertiesGlycolConcentration, this, keepHandle));
      }
      if (auto fluidPropertiesName = std::dynamic_pointer_cast<FluidPropertiesName_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new FluidPropertiesName_Impl(*fluidPropertiesName, this, keepHandle));
      }
      if (auto fluidPropertiesSaturated = std::dynamic_pointer_cast<FluidPropertiesSaturated_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new FluidPropertiesSaturated_Impl(*fluidPropertiesSaturated, this, keepHandle));
      }
      if (auto fluidPropertiesSuperheated = std::dynamic_pointer_cast<FluidPropertiesSuperheated_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new FluidPropertiesSuperheated_Impl(*fluidPropertiesSuperheated, this, keepHandle));
      }
      if (auto fluidPropertiesTemperatures = std::dynamic_pointer_cast<FluidPropertiesTemperatures_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new FluidPropertiesTemperatures_Impl(*fluidPropertiesTemperatures, this, keepHandle));
      }
      if (auto foundationKiva = std::dynamic_pointer_cast<FoundationKiva_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new FoundationKiva_Impl(*foundationKiva, this, keepHandle));
      }
      if (auto foundationKivaSettings = std::dynamic_pointer_cast<FoundationKivaSettings_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new FoundationKivaSettings_Impl(*foundationKivaSettings, this, keepHandle));
      }
      if (auto coolingTowerSingleSpeed = std::dynamic_pointer_cast<CoolingTowerSingleSpeed_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new CoolingTowerSingleSpeed_Impl(*coolingTowerSingleSpeed, this, keepHandle));
      }
      if (auto coolingTowerTwoSpeed = std::dynamic_pointer_cast<CoolingTowerTwoSpeed_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new CoolingTowerTwoSpeed_Impl(*coolingTowerTwoSpeed, this, keepHandle));
      }
      if (auto coolingTowerVariableSpeed = std::dynamic_pointer_cast<CoolingTowerVariableSpeed_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new CoolingTowerVariableSpeed_Impl(*coolingTowerVariableSpeed, this, keepHandle));
      }
      if (auto coolingTowerVariableSpeedMerkel = std::dynamic_pointer_cast<CoolingTowerVariableSpeedMerkel_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new CoolingTowerVariableSpeedMerkel_Impl(*coolingTowerVariableSpeedMerkel, this, keepHandle));
      }
      if (auto coolingTowerPerformanceCoolTools = std::dynamic_pointer_cast<CoolingTowerPerformanceCoolTools_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new CoolingTowerPerformanceCoolTools_Impl(*coolingTowerPerformanceCoolTools, this, keepHandle));
      }
      if (auto coolingTowerPerformanceYorkCalc = std::dynamic_pointer_cast<CoolingTowerPerformanceYorkCalc_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new CoolingTowerPerformanceYorkCalc_Impl(*coolingTowerPerformanceYorkCalc, this, keepHandle));
      }
      if (auto chillerAbsorption = std::dynamic_pointer_cast<ChillerAbsorption_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new ChillerAbsorption_Impl(*chillerAbsorption, this, keepHandle));
      }
      if (auto chillerAbsorptionIndirect = std::dynamic_pointer_cast<ChillerAbsorptionIndirect_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new ChillerAbsorptionIndirect_Impl(*chillerAbsorptionIndirect, this, keepHandle));
      }
      if (auto chillerCombustionTurbine = std::dynamic_pointer_cast<ChillerCombustionTurbine_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new ChillerCombustionTurbine_Impl(*chillerCombustionTurbine, this, keepHandle));
      }
      if (auto generatorCombustionTurbine = std::dynamic_pointer_cast<GeneratorCombustionTurbine_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new GeneratorCombustionTurbine_Impl(*generatorCombustionTurbine, this, keepHandle));
      }
      if (auto generatorInternalCombustionEngine = std::dynamic_pointer_cast<GeneratorInternalCombustionEngine_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new GeneratorInternalCombustionEngine_Impl(*generatorInternalCombustionEngine, this, keepHandle));
      }
      if (auto generatorMicroCHP = std::dynamic_pointer_cast<GeneratorMicroCHP_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new GeneratorMicroCHP_Impl(*generatorMicroCHP, this, keepHandle));
      }
      if (auto generatorMicroCHPNonNormalizedParameters =
            std::dynamic_pointer_cast<GeneratorMicroCHPNonNormalizedParameters_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new GeneratorMicroCHPNonNormalizedParameters_Impl(*generatorMicroCHPNonNormalizedParameters, this, keepHandle));
      }
      if (auto generatorMicroTurbine = std::dynamic_pointer_cast<GeneratorMicroTurbine_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new GeneratorMicroTurbine_Impl(*generatorMicroTurbine, this, keepHandle));
      }
      if (auto generatorPhotovoltaic = std::dynamic_pointer_cast<GeneratorPhotovoltaic_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new GeneratorPhotovoltaic_Impl(*generatorPhotovoltaic, this, keepHandle));
      }
      if (auto generatorWindTurbine = std::dynamic_pointer_cast<GeneratorWindTurbine_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new GeneratorWindTurbine_Impl(*generatorWindTurbine, this, keepHandle));
      }
      if (auto generatorPVWatts = std::dynamic_pointer_cast<GeneratorPVWatts_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new GeneratorPVWatts_Impl(*generatorPVWatts, this, keepHandle));
      }
      if (auto photovoltaicPerformanceSimple = std::dynamic_pointer_cast<PhotovoltaicPerformanceSimple_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new PhotovoltaicPerformanceSimple_Impl(*photovoltaicPerformanceSimple, this, keepHandle));
      }
      if (auto photovoltaicPerformanceSandia = std::dynamic_pointer_cast<PhotovoltaicPerformanceSandia_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new PhotovoltaicPerformanceSandia_Impl(*photovoltaicPerformanceSandia, this, keepHandle));
      }
      if (auto generatorFuelCell = std::dynamic_pointer_cast<GeneratorFuelCell_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new GeneratorFuelCell_Impl(*generatorFuelCell, this, keepHandle));
      }
      if (auto generatorFuelCellAirSupply = std::dynamic_pointer_cast<GeneratorFuelCellAirSupply_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new GeneratorFuelCellAirSupply_Impl(*generatorFuelCellAirSupply, this, keepHandle));
      }
      if (auto generatorFuelCellAuxiliaryHeater = std::dynamic_pointer_cast<GeneratorFuelCellAuxiliaryHeater_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new GeneratorFuelCellAuxiliaryHeater_Impl(*generatorFuelCellAuxiliaryHeater, this, keepHandle));
      }
      if (auto generatorFuelCellElectricalStorage = std::dynamic_pointer_cast<GeneratorFuelCellElectricalStorage_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new GeneratorFuelCellElectricalStorage_Impl(*generatorFuelCellElectricalStorage, this, keepHandle));
      }
      if (auto generatorFuelCellInverter = std::dynamic_pointer_cast<GeneratorFuelCellInverter_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new GeneratorFuelCellInverter_Impl(*generatorFuelCellInverter, this, keepHandle));
      }
      if (auto generatorFuelCellPowerModule = std::dynamic_pointer_cast<GeneratorFuelCellPowerModule_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new GeneratorFuelCellPowerModule_Impl(*generatorFuelCellPowerModule, this, keepHandle));
      }
      if (auto generatorFuelCellWaterSupply = std::dynamic_pointer_cast<GeneratorFuelCellWaterSupply_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new GeneratorFuelCellWaterSupply_Impl(*generatorFuelCellWaterSupply, this, keepHandle));
      }
      if (auto generatorFuelSupply = std::dynamic_pointer_cast<GeneratorFuelSupply_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new GeneratorFuelSupply_Impl(*generatorFuelSupply, this, keepHandle));
      }
      if (auto generatorFuelCellExhaustGasToWaterHeatExchanger =
            std::dynamic_pointer_cast<GeneratorFuelCellExhaustGasToWaterHeatExchanger_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new GeneratorFuelCellExhaustGasToWaterHeatExchanger_Impl(*generatorFuelCellExhaustGasToWaterHeatExchanger, this, keepHandle));
      }
      if (auto generatorFuelCellStackCooler = std::dynamic_pointer_cast<GeneratorFuelCellStackCooler_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new GeneratorFuelCellStackCooler_Impl(*generatorFuelCellStackCooler, this, keepHandle));
      }
      if (auto chillerHeaterAbsorptionDirectFired = std::dynamic_pointer_cast<ChillerHeaterAbsorptionDirectFired_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new ChillerHeaterAbsorptionDirectFired_Impl(*chillerHeaterAbsorptionDirectFired, this, keepHandle));
      }
      if (auto chillerHeaterAbsorptionDoubleEffect = std::dynamic_pointer_cast<ChillerHeaterAbsorptionDoubleEffect_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new ChillerHeaterAbsorptionDoubleEffect_Impl(*chillerHeaterAbsorptionDoubleEffect, this, keepHandle));
      }
      if (auto chillerHeaterPerformanceElectricEIR = std::dynamic_pointer_cast<ChillerHeaterPerformanceElectricEIR_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new ChillerHeaterPerformanceElectricEIR_Impl(*chillerHeaterPerformanceElectricEIR, this, keepHandle));
      }
      if (auto chillerConstantCOP = std::dynamic_pointer_cast<ChillerConstantCOP_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new ChillerConstantCOP_Impl(*chillerConstantCOP, this, keepHandle));
      }
      if (auto chillerEngineDriven = std::dynamic_pointer_cast<ChillerEngineDriven_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new ChillerEngineDriven_Impl(*chillerEngineDriven, this, keepHandle));
      }
      if (auto chillerElectric = std::dynamic_pointer_cast<ChillerElectric_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new ChillerElectric_Impl(*chillerElectric, this, keepHandle));
      }
      if (auto chillerElectricEIR = std::dynamic_pointer_cast<ChillerElectricEIR_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new ChillerElectricEIR_Impl(*chillerElectricEIR, this, keepHandle));
      }
      if (auto chillerElectricReformulatedEIR = std::dynamic_pointer_cast<ChillerElectricReformulatedEIR_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new ChillerElectricReformulatedEIR_Impl(*chillerElectricReformulatedEIR, this, keepHandle));
      }
      if (auto chillerElectricASHRAE205 = std::dynamic_pointer_cast<ChillerElectricASHRAE205_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new ChillerElectricASHRAE205_Impl(*chillerElectricASHRAE205, this, keepHandle));
      }
      if (auto fan = std::dynamic_pointer_cast<FanConstantVolume_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new FanConstantVolume_Impl(*fan, this, keepHandle));
      }
      if (auto fanComponentModel = std::dynamic_pointer_cast<FanComponentModel_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new FanComponentModel_Impl(*fanComponentModel, this, keepHandle));
      }
      if (auto fanOnOff = std::dynamic_pointer_cast<FanOnOff_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new FanOnOff_Impl(*fanOnOff, this, keepHandle));
      }
      if (auto fanSystemModel = std::dynamic_pointer_cast<FanSystemModel_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new FanSystemModel_Impl(*fanSystemModel, this, keepHandle));
      }
      if (auto fanVariableVolume = std::dynamic_pointer_cast<FanVariableVolume_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new FanVariableVolume_Impl(*fanVariableVolume, this, keepHandle));
      }
      if (auto fanPerformanceNightVentilation = std::dynamic_pointer_cast<FanPerformanceNightVentilation_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new FanPerformanceNightVentilation_Impl(*fanPerformanceNightVentilation, this, keepHandle));
      }
      if (auto faultModelFoulingAirFilter = std::dynamic_pointer_cast<FaultModelFoulingAirFilter_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new FaultModelFoulingAirFilter_Impl(*faultModelFoulingAirFilter, this, keepHandle));
      }
      if (auto faultModelFoulingBoiler = std::dynamic_pointer_cast<FaultModelFoulingBoiler_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new FaultModelFoulingBoiler_Impl(*faultModelFoulingBoiler, this, keepHandle));
      }
      if (auto faultModelFoulingChiller = std::dynamic_pointer_cast<FaultModelFoulingChiller_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new FaultModelFoulingChiller_Impl(*faultModelFoulingChiller, this, keepHandle));
      }
      if (auto faultModelFoulingCoil = std::dynamic_pointer_cast<FaultModelFoulingCoil_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new FaultModelFoulingCoil_Impl(*faultModelFoulingCoil, this, keepHandle));
      }
      if (auto faultModelFoulingCoolingTower = std::dynamic_pointer_cast<FaultModelFoulingCoolingTower_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new FaultModelFoulingCoolingTower_Impl(*faultModelFoulingCoolingTower, this, keepHandle));
      }
      if (auto faultModelFoulingEvaporativeCooler = std::dynamic_pointer_cast<FaultModelFoulingEvaporativeCooler_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new FaultModelFoulingEvaporativeCooler_Impl(*faultModelFoulingEvaporativeCooler, this, keepHandle));
      }
      if (auto faultModelEnthalpySensorOffsetOutdoorAir =
            std::dynamic_pointer_cast<FaultModelEnthalpySensorOffsetOutdoorAir_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new FaultModelEnthalpySensorOffsetOutdoorAir_Impl(*faultModelEnthalpySensorOffsetOutdoorAir, this, keepHandle));
      }
      if (auto faultModelEnthalpySensorOffsetReturnAir =
            std::dynamic_pointer_cast<FaultModelEnthalpySensorOffsetReturnAir_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new FaultModelEnthalpySensorOffsetReturnAir_Impl(*faultModelEnthalpySensorOffsetReturnAir, this, keepHandle));
      }
      if (auto faultModelHumidistatOffset = std::dynamic_pointer_cast<FaultModelHumidistatOffset_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new FaultModelHumidistatOffset_Impl(*faultModelHumidistatOffset, this, keepHandle));
      }
      if (auto faultModelHumiditySensorOffsetOutdoorAir =
            std::dynamic_pointer_cast<FaultModelHumiditySensorOffsetOutdoorAir_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new FaultModelHumiditySensorOffsetOutdoorAir_Impl(*faultModelHumiditySensorOffsetOutdoorAir, this, keepHandle));
      }
      if (auto faultModelThermostatOffset = std::dynamic_pointer_cast<FaultModelThermostatOffset_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new FaultModelThermostatOffset_Impl(*faultModelThermostatOffset, this, keepHandle));
      }
      if (auto faultModelTemperatureSensorOffsetChillerSupplyWater =
            std::dynamic_pointer_cast<FaultModelTemperatureSensorOffsetChillerSupplyWater_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new FaultModelTemperatureSensorOffsetChillerSupplyWater_Impl(*faultModelTemperatureSensorOffsetChillerSupplyWater, this, keepHandle));
      }
      if (auto faultModelTemperatureSensorOffsetCoilSupplyAir =
            std::dynamic_pointer_cast<FaultModelTemperatureSensorOffsetCoilSupplyAir_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new FaultModelTemperatureSensorOffsetCoilSupplyAir_Impl(*faultModelTemperatureSensorOffsetCoilSupplyAir, this, keepHandle));
      }
      if (auto faultModelTemperatureSensorOffsetCondenserSupplyWater =
            std::dynamic_pointer_cast<FaultModelTemperatureSensorOffsetCondenserSupplyWater_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new FaultModelTemperatureSensorOffsetCondenserSupplyWater_Impl(*faultModelTemperatureSensorOffsetCondenserSupplyWater, this, keepHandle));
      }
      if (auto faultModelTemperatureSensorOffsetOutdoorAir =
            std::dynamic_pointer_cast<FaultModelTemperatureSensorOffsetOutdoorAir_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new FaultModelTemperatureSensorOffsetOutdoorAir_Impl(*faultModelTemperatureSensorOffsetOutdoorAir, this, keepHandle));
      }
      if (auto faultModelTemperatureSensorOffsetReturnAir =
            std::dynamic_pointer_cast<FaultModelTemperatureSensorOffsetReturnAir_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new FaultModelTemperatureSensorOffsetReturnAir_Impl(*faultModelTemperatureSensorOffsetReturnAir, this, keepHandle));
      }
      if (auto floorAdiabatic = std::dynamic_pointer_cast<FloorAdiabatic_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new FloorAdiabatic_Impl(*floorAdiabatic, this, keepHandle));
      }
      if (auto floorDetailed = std::dynamic_pointer_cast<FloorDetailed_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new FloorDetailed_Impl(*floorDetailed, this, keepHandle));
      }
      if (auto floorGroundContact = std::dynamic_pointer_cast<FloorGroundContact_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new FloorGroundContact_Impl(*floorGroundContact, this, keepHandle));
      }
      if (auto floorInterzone = std::dynamic_pointer_cast<FloorInterzone_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new FloorInterzone_Impl(*floorInterzone, this, keepHandle));
      }
      if (auto coilCoolingDXSingleSpeed = std::dynamic_pointer_cast<CoilCoolingDXSingleSpeed_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new CoilCoolingDXSingleSpeed_Impl(*coilCoolingDXSingleSpeed, this, keepHandle));
      }
      if (auto coilCoolingDXSingleSpeedThermalStorage =
            std::dynamic_pointer_cast<CoilCoolingDXSingleSpeedThermalStorage_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new CoilCoolingDXSingleSpeedThermalStorage_Impl(*coilCoolingDXSingleSpeedThermalStorage, this, keepHandle));
      }
      if (auto coilCoolingDXVariableSpeed = std::dynamic_pointer_cast<CoilCoolingDXVariableSpeed_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new CoilCoolingDXVariableSpeed_Impl(*coilCoolingDXVariableSpeed, this, keepHandle));
      }
      if (auto coilCoolingDXMultiSpeed = std::dynamic_pointer_cast<CoilCoolingDXMultiSpeed_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new CoilCoolingDXMultiSpeed_Impl(*coilCoolingDXMultiSpeed, this, keepHandle));
      }
      if (auto coilCoolingDXTwoSpeed = std::dynamic_pointer_cast<CoilCoolingDXTwoSpeed_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new CoilCoolingDXTwoSpeed_Impl(*coilCoolingDXTwoSpeed, this, keepHandle));
      }
      if (auto coilCoolingDXTwoStageWithHumidityControlMode =
            std::dynamic_pointer_cast<CoilCoolingDXTwoStageWithHumidityControlMode_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new CoilCoolingDXTwoStageWithHumidityControlMode_Impl(*coilCoolingDXTwoStageWithHumidityControlMode, this, keepHandle));
      }
      if (auto coilPerformanceDXCooling = std::dynamic_pointer_cast<CoilPerformanceDXCooling_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new CoilPerformanceDXCooling_Impl(*coilPerformanceDXCooling, this, keepHandle));
      }
      if (auto coilCoolingDXCurveFitOperatingMode = std::dynamic_pointer_cast<CoilCoolingDXCurveFitOperatingMode_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new CoilCoolingDXCurveFitOperatingMode_Impl(*coilCoolingDXCurveFitOperatingMode, this, keepHandle));
      }
      if (auto coilCoolingDXCurveFitPerformance = std::dynamic_pointer_cast<CoilCoolingDXCurveFitPerformance_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new CoilCoolingDXCurveFitPerformance_Impl(*coilCoolingDXCurveFitPerformance, this, keepHandle));
      }
      if (auto coilCoolingDXCurveFitSpeed = std::dynamic_pointer_cast<CoilCoolingDXCurveFitSpeed_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new CoilCoolingDXCurveFitSpeed_Impl(*coilCoolingDXCurveFitSpeed, this, keepHandle));
      }
      if (auto heatExchangerDesiccantBalancedFlowPerformanceDataType1 =
            std::dynamic_pointer_cast<HeatExchangerDesiccantBalancedFlowPerformanceDataType1_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new HeatExchangerDesiccantBalancedFlowPerformanceDataType1_Impl(*heatExchangerDesiccantBalancedFlowPerformanceDataType1, this, keepHandle));
      }
      if (auto materialPropertyGlazingSpectralData = std::dynamic_pointer_cast<MaterialPropertyGlazingSpectralData_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new MaterialPropertyGlazingSpectralData_Impl(*materialPropertyGlazingSpectralData, this, keepHandle));
      }
      if (auto materialPropertyHeatAndMoistureTransferDiffusion =
            std::dynamic_pointer_cast<MaterialPropertyHeatAndMoistureTransferDiffusion_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new MaterialPropertyHeatAndMoistureTransferDiffusion_Impl(*materialPropertyHeatAndMoistureTransferDiffusion, this, keepHandle));
      }
      if (auto materialPropertyHeatAndMoistureTransferRedistribution =
            std::dynamic_pointer_cast<MaterialPropertyHeatAndMoistureTransferRedistribution_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new MaterialPropertyHeatAndMoistureTransferRedistribution_Impl(*materialPropertyHeatAndMoistureTransferRedistribution, this, keepHandle));
      }
      if (auto materialPropertyHeatAndMoistureTransferSettings =
            std::dynamic_pointer_cast<MaterialPropertyHeatAndMoistureTransferSettings_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new MaterialPropertyHeatAndMoistureTransferSettings_Impl(*materialPropertyHeatAndMoistureTransferSettings, this, keepHandle));
      }
      if (auto materialPropertyHeatAndMoistureTransferSorptionIsotherm =
            std::dynamic_pointer_cast<MaterialPropertyHeatAndMoistureTransferSorptionIsotherm_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new MaterialPropertyHeatAndMoistureTransferSorptionIsotherm_Impl(
          *materialPropertyHeatAndMoistureTransferSorptionIsotherm, this, keepHandle));
      }
      if (auto materialPropertyHeatAndMoistureTransferSuction =
            std::dynamic_pointer_cast<MaterialPropertyHeatAndMoistureTransferSuction_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new MaterialPropertyHeatAndMoistureTransferSuction_Impl(*materialPropertyHeatAndMoistureTransferSuction, this, keepHandle));
      }
      if (auto materialPropertyHeatAndMoistureTransferThermalConductivity =
            std::dynamic_pointer_cast<MaterialPropertyHeatAndMoistureTransferThermalConductivity_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new MaterialPropertyHeatAndMoistureTransferThermalConductivity_Impl(
          *materialPropertyHeatAndMoistureTransferThermalConductivity, this, keepHandle));
      }
      if (auto materialPropertyMoisturePenetrationDepthSettings =
            std::dynamic_pointer_cast<MaterialPropertyMoisturePenetrationDepthSettings_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new MaterialPropertyMoisturePenetrationDepthSettings_Impl(*materialPropertyMoisturePenetrationDepthSettings, this, keepHandle));
      }
      if (auto materialPropertyVariableAbsorptance = std::dynamic_pointer_cast<MaterialPropertyVariableAbsorptance_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new MaterialPropertyVariableAbsorptance_Impl(*materialPropertyVariableAbsorptance, this, keepHandle));
      }
      if (auto materialPropertyVariableThermalConductivity =
            std::dynamic_pointer_cast<MaterialPropertyVariableThermalConductivity_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new MaterialPropertyVariableThermalConductivity_Impl(*materialPropertyVariableThermalConductivity, this, keepHandle));
      }
      if (auto materialPropertyPhaseChange = std::dynamic_pointer_cast<MaterialPropertyPhaseChange_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new MaterialPropertyPhaseChange_Impl(*materialPropertyPhaseChange, this, keepHandle));
      }
      if (auto materialPropertyPhaseChangeHysteresis = std::dynamic_pointer_cast<MaterialPropertyPhaseChangeHysteresis_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new MaterialPropertyPhaseChangeHysteresis_Impl(*materialPropertyPhaseChangeHysteresis, this, keepHandle));
      }
      if (auto coilCoolingDX = std::dynamic_pointer_cast<CoilCoolingDX_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new CoilCoolingDX_Impl(*coilCoolingDX, this, keepHandle));
      }
      if (auto coilCoolingDXVariableRefrigerantFlow = std::dynamic_pointer_cast<CoilCoolingDXVariableRefrigerantFlow_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new CoilCoolingDXVariableRefrigerantFlow_Impl(*coilCoolingDXVariableRefrigerantFlow, this, keepHandle));
      }
      if (auto coilCoolingDXVariableRefrigerantFlowFluidTemperatureControl =
            std::dynamic_pointer_cast<CoilCoolingDXVariableRefrigerantFlowFluidTemperatureControl_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new CoilCoolingDXVariableRefrigerantFlowFluidTemperatureControl_Impl(
          *coilCoolingDXVariableRefrigerantFlowFluidTemperatureControl, this, keepHandle));
      }
      if (auto coilHeatingDXVariableRefrigerantFlow = std::dynamic_pointer_cast<CoilHeatingDXVariableRefrigerantFlow_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new CoilHeatingDXVariableRefrigerantFlow_Impl(*coilHeatingDXVariableRefrigerantFlow, this, keepHandle));
      }
      if (auto coilHeatingDXVariableRefrigerantFlowFluidTemperatureControl =
            std::dynamic_pointer_cast<CoilHeatingDXVariableRefrigerantFlowFluidTemperatureControl_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new CoilHeatingDXVariableRefrigerantFlowFluidTemperatureControl_Impl(
          *coilHeatingDXVariableRefrigerantFlowFluidTemperatureControl, this, keepHandle));
      }
      if (auto coilCoolingWater = std::dynamic_pointer_cast<CoilCoolingWater_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new CoilCoolingWater_Impl(*coilCoolingWater, this, keepHandle));
      }
      if (auto coilHeatingWater = std::dynamic_pointer_cast<CoilHeatingWater_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new CoilHeatingWater_Impl(*coilHeatingWater, this, keepHandle));
      }
      if (auto coilCoolingWaterToAirHeatPumpEquationFit =
            std::dynamic_pointer_cast<CoilCoolingWaterToAirHeatPumpEquationFit_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new CoilCoolingWaterToAirHeatPumpEquationFit_Impl(*coilCoolingWaterToAirHeatPumpEquationFit, this, keepHandle));
      }
      if (auto coilHeatingWaterToAirHeatPumpEquationFit =
            std::dynamic_pointer_cast<CoilHeatingWaterToAirHeatPumpEquationFit_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new CoilHeatingWaterToAirHeatPumpEquationFit_Impl(*coilHeatingWaterToAirHeatPumpEquationFit, this, keepHandle));
      }
      if (auto coilCoolingWaterToAirHeatPumpVariableSpeedEquationFit =
            std::dynamic_pointer_cast<CoilCoolingWaterToAirHeatPumpVariableSpeedEquationFit_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new CoilCoolingWaterToAirHeatPumpVariableSpeedEquationFit_Impl(*coilCoolingWaterToAirHeatPumpVariableSpeedEquationFit, this, keepHandle));
      }
      if (auto coilHeatingWaterToAirHeatPumpVariableSpeedEquationFit =
            std::dynamic_pointer_cast<CoilHeatingWaterToAirHeatPumpVariableSpeedEquationFit_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new CoilHeatingWaterToAirHeatPumpVariableSpeedEquationFit_Impl(*coilHeatingWaterToAirHeatPumpVariableSpeedEquationFit, this, keepHandle));
      }
      if (auto coilUserDefined = std::dynamic_pointer_cast<CoilUserDefined_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new CoilUserDefined_Impl(*coilUserDefined, this, keepHandle));
      }
      if (auto coilCoolingWaterToAirHeatPumpParameterEstimation =
            std::dynamic_pointer_cast<CoilCoolingWaterToAirHeatPumpParameterEstimation_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new CoilCoolingWaterToAirHeatPumpParameterEstimation_Impl(*coilCoolingWaterToAirHeatPumpParameterEstimation, this, keepHandle));
      }
      if (auto coilHeatingWaterToAirHeatPumpParameterEstimation =
            std::dynamic_pointer_cast<CoilHeatingWaterToAirHeatPumpParameterEstimation_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new CoilHeatingWaterToAirHeatPumpParameterEstimation_Impl(*coilHeatingWaterToAirHeatPumpParameterEstimation, this, keepHandle));
      }
      if (auto coilCoolingWaterDetailedGeometry = std::dynamic_pointer_cast<CoilCoolingWaterDetailedGeometry_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new CoilCoolingWaterDetailedGeometry_Impl(*coilCoolingWaterDetailedGeometry, this, keepHandle));
      }
      if (auto coilDXASHRAE205Performance = std::dynamic_pointer_cast<CoilDXASHRAE205Performance_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new CoilDXASHRAE205Performance_Impl(*coilDXASHRAE205Performance, this, keepHandle));
      }
      if (auto coilHeatingDXMultiSpeed = std::dynamic_pointer_cast<CoilHeatingDXMultiSpeed_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new CoilHeatingDXMultiSpeed_Impl(*coilHeatingDXMultiSpeed, this, keepHandle));
      }
      if (auto coilHeatingDXSingleSpeed = std::dynamic_pointer_cast<CoilHeatingDXSingleSpeed_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new CoilHeatingDXSingleSpeed_Impl(*coilHeatingDXSingleSpeed, this, keepHandle));
      }
      if (auto coilHeatingDXVariableSpeed = std::dynamic_pointer_cast<CoilHeatingDXVariableSpeed_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new CoilHeatingDXVariableSpeed_Impl(*coilHeatingDXVariableSpeed, this, keepHandle));
      }
      if (auto coilHeatingDesuperheater = std::dynamic_pointer_cast<CoilHeatingDesuperheater_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new CoilHeatingDesuperheater_Impl(*coilHeatingDesuperheater, this, keepHandle));
      }
      if (auto coilWaterHeatingDesuperheater = std::dynamic_pointer_cast<CoilWaterHeatingDesuperheater_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new CoilWaterHeatingDesuperheater_Impl(*coilWaterHeatingDesuperheater, this, keepHandle));
      }
      if (auto coilHeatingElectric = std::dynamic_pointer_cast<CoilHeatingElectric_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new CoilHeatingElectric_Impl(*coilHeatingElectric, this, keepHandle));
      }
      if (auto coilHeatingElectricMultiStage = std::dynamic_pointer_cast<CoilHeatingElectricMultiStage_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new CoilHeatingElectricMultiStage_Impl(*coilHeatingElectricMultiStage, this, keepHandle));
      }
      if (auto coilHeatingGasMultiStage = std::dynamic_pointer_cast<CoilHeatingGasMultiStage_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new CoilHeatingGasMultiStage_Impl(*coilHeatingGasMultiStage, this, keepHandle));
      }
      if (auto coilHeatingSteam = std::dynamic_pointer_cast<CoilHeatingSteam_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new CoilHeatingSteam_Impl(*coilHeatingSteam, this, keepHandle));
      }
      if (auto coilWaterHeatingAirToWaterHeatPumpWrapped =
            std::dynamic_pointer_cast<CoilWaterHeatingAirToWaterHeatPumpWrapped_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new CoilWaterHeatingAirToWaterHeatPumpWrapped_Impl(*coilWaterHeatingAirToWaterHeatPumpWrapped, this, keepHandle));
      }
      if (auto coilWaterHeatingAirToWaterHeatPump = std::dynamic_pointer_cast<CoilWaterHeatingAirToWaterHeatPump_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new CoilWaterHeatingAirToWaterHeatPump_Impl(*coilWaterHeatingAirToWaterHeatPump, this, keepHandle));
      }
      if (auto coilWaterHeatingAirToWaterHeatPumpVariableSpeed =
            std::dynamic_pointer_cast<CoilWaterHeatingAirToWaterHeatPumpVariableSpeed_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new CoilWaterHeatingAirToWaterHeatPumpVariableSpeed_Impl(*coilWaterHeatingAirToWaterHeatPumpVariableSpeed, this, keepHandle));
      }
      if (auto controllerWaterCoil = std::dynamic_pointer_cast<ControllerWaterCoil_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new ControllerWaterCoil_Impl(*controllerWaterCoil, this, keepHandle));
      }
      if (auto coilHeatingFuel = std::dynamic_pointer_cast<CoilHeatingGas_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new CoilHeatingGas_Impl(*coilHeatingFuel, this, keepHandle));
      }
      if (auto coilSystemCoolingDX = std::dynamic_pointer_cast<CoilSystemCoolingDX_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new CoilSystemCoolingDX_Impl(*coilSystemCoolingDX, this, keepHandle));
      }
      if (auto coilSystemHeatingDX = std::dynamic_pointer_cast<CoilSystemHeatingDX_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new CoilSystemHeatingDX_Impl(*coilSystemHeatingDX, this, keepHandle));
      }
      if (auto coilSystemCoolingDXHeatExchangerAssisted =
            std::dynamic_pointer_cast<CoilSystemCoolingDXHeatExchangerAssisted_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new CoilSystemCoolingDXHeatExchangerAssisted_Impl(*coilSystemCoolingDXHeatExchangerAssisted, this, keepHandle));
      }
      if (auto coilSystemIntegratedHeatPumpAirSource = std::dynamic_pointer_cast<CoilSystemIntegratedHeatPumpAirSource_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new CoilSystemIntegratedHeatPumpAirSource_Impl(*coilSystemIntegratedHeatPumpAirSource, this, keepHandle));
      }
      if (auto coilSystemCoolingWater = std::dynamic_pointer_cast<CoilSystemCoolingWater_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new CoilSystemCoolingWater_Impl(*coilSystemCoolingWater, this, keepHandle));
      }
      if (auto coilSystemCoolingWaterHeatExchangerAssisted =
            std::dynamic_pointer_cast<CoilSystemCoolingWaterHeatExchangerAssisted_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new CoilSystemCoolingWaterHeatExchangerAssisted_Impl(*coilSystemCoolingWaterHeatExchangerAssisted, this, keepHandle));
      }
      if (auto setpointManagerMixedAir = std::dynamic_pointer_cast<SetpointManagerMixedAir_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new SetpointManagerMixedAir_Impl(*setpointManagerMixedAir, this, keepHandle));
      }
      if (auto setpointManagerMultiZoneCoolingAverage =
            std::dynamic_pointer_cast<SetpointManagerMultiZoneCoolingAverage_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new SetpointManagerMultiZoneCoolingAverage_Impl(*setpointManagerMultiZoneCoolingAverage, this, keepHandle));
      }
      if (auto setpointManagerMultiZoneHeatingAverage =
            std::dynamic_pointer_cast<SetpointManagerMultiZoneHeatingAverage_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new SetpointManagerMultiZoneHeatingAverage_Impl(*setpointManagerMultiZoneHeatingAverage, this, keepHandle));
      }
      if (auto setpointManagerMultiZoneMaximumHumidityAverage =
            std::dynamic_pointer_cast<SetpointManagerMultiZoneMaximumHumidityAverage_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new SetpointManagerMultiZoneMaximumHumidityAverage_Impl(*setpointManagerMultiZoneMaximumHumidityAverage, this, keepHandle));
      }
      if (auto setpointManagerMultiZoneMinimumHumidityAverage =
            std::dynamic_pointer_cast<SetpointManagerMultiZoneMinimumHumidityAverage_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new SetpointManagerMultiZoneMinimumHumidityAverage_Impl(*setpointManagerMultiZoneMinimumHumidityAverage, this, keepHandle));
      }
      if (auto setpointManagerMultiZoneHumidityMaximum =
            std::dynamic_pointer_cast<SetpointManagerMultiZoneHumidityMaximum_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new SetpointManagerMultiZoneHumidityMaximum_Impl(*setpointManagerMultiZoneHumidityMaximum, this, keepHandle));
      }
      if (auto setpointManagerMultiZoneHumidityMinimum =
            std::dynamic_pointer_cast<SetpointManagerMultiZoneHumidityMinimum_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new SetpointManagerMultiZoneHumidityMinimum_Impl(*setpointManagerMultiZoneHumidityMinimum, this, keepHandle));
      }
      if (auto setpointManagerColdest = std::dynamic_pointer_cast<SetpointManagerColdest_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new SetpointManagerColdest_Impl(*setpointManagerColdest, this, keepHandle));
      }
      if (auto setpointManagerFollowGroundTemperature =
            std::dynamic_pointer_cast<SetpointManagerFollowGroundTemperature_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new SetpointManagerFollowGroundTemperature_Impl(*setpointManagerFollowGroundTemperature, this, keepHandle));
      }
      if (auto setpointManagerFollowOutdoorAirTemperature =
            std::dynamic_pointer_cast<SetpointManagerFollowOutdoorAirTemperature_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new SetpointManagerFollowOutdoorAirTemperature_Impl(*setpointManagerFollowOutdoorAirTemperature, this, keepHandle));
      }
      if (auto setpointManagerOutdoorAirPretreat = std::dynamic_pointer_cast<SetpointManagerOutdoorAirPretreat_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new SetpointManagerOutdoorAirPretreat_Impl(*setpointManagerOutdoorAirPretreat, this, keepHandle));
      }
      if (auto setpointManagerOutdoorAirReset = std::dynamic_pointer_cast<SetpointManagerOutdoorAirReset_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new SetpointManagerOutdoorAirReset_Impl(*setpointManagerOutdoorAirReset, this, keepHandle));
      }
      if (auto setpointManagerFollowSystemNodeTemperature =
            std::dynamic_pointer_cast<SetpointManagerFollowSystemNodeTemperature_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new SetpointManagerFollowSystemNodeTemperature_Impl(*setpointManagerFollowSystemNodeTemperature, this, keepHandle));
      }
      if (auto setpointManagerSystemNodeResetHumidity =
            std::dynamic_pointer_cast<SetpointManagerSystemNodeResetHumidity_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new SetpointManagerSystemNodeResetHumidity_Impl(*setpointManagerSystemNodeResetHumidity, this, keepHandle));
      }
      if (auto setpointManagerSystemNodeResetTemperature =
            std::dynamic_pointer_cast<SetpointManagerSystemNodeResetTemperature_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new SetpointManagerSystemNodeResetTemperature_Impl(*setpointManagerSystemNodeResetTemperature, this, keepHandle));
      }
      if (auto setpointManagerWarmest = std::dynamic_pointer_cast<SetpointManagerWarmest_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new SetpointManagerWarmest_Impl(*setpointManagerWarmest, this, keepHandle));
      }
      if (auto setpointManagerWarmestTemperatureFlow = std::dynamic_pointer_cast<SetpointManagerWarmestTemperatureFlow_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new SetpointManagerWarmestTemperatureFlow_Impl(*setpointManagerWarmestTemperatureFlow, this, keepHandle));
      }
      if (auto setpointManagerCondenserEnteringReset = std::dynamic_pointer_cast<SetpointManagerCondenserEnteringReset_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new SetpointManagerCondenserEnteringReset_Impl(*setpointManagerCondenserEnteringReset, this, keepHandle));
      }
      if (auto setpointManagerCondenserEnteringResetIdeal =
            std::dynamic_pointer_cast<SetpointManagerCondenserEnteringResetIdeal_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new SetpointManagerCondenserEnteringResetIdeal_Impl(*setpointManagerCondenserEnteringResetIdeal, this, keepHandle));
      }
      if (auto setpointManagerReturnAirBypassFlow = std::dynamic_pointer_cast<SetpointManagerReturnAirBypassFlow_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new SetpointManagerReturnAirBypassFlow_Impl(*setpointManagerReturnAirBypassFlow, this, keepHandle));
      }
      if (auto setpointManagerReturnTemperatureChilledWater =
            std::dynamic_pointer_cast<SetpointManagerReturnTemperatureChilledWater_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new SetpointManagerReturnTemperatureChilledWater_Impl(*setpointManagerReturnTemperatureChilledWater, this, keepHandle));
      }
      if (auto setpointManagerReturnTemperatureHotWater =
            std::dynamic_pointer_cast<SetpointManagerReturnTemperatureHotWater_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new SetpointManagerReturnTemperatureHotWater_Impl(*setpointManagerReturnTemperatureHotWater, this, keepHandle));
      }
      if (auto setpointManagerScheduled = std::dynamic_pointer_cast<SetpointManagerScheduled_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new SetpointManagerScheduled_Impl(*setpointManagerScheduled, this, keepHandle));
      }
      if (auto setpointManagerScheduledDualSetpoint = std::dynamic_pointer_cast<SetpointManagerScheduledDualSetpoint_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new SetpointManagerScheduledDualSetpoint_Impl(*setpointManagerScheduledDualSetpoint, this, keepHandle));
      }
      if (auto setpointManagerSingleZoneCooling = std::dynamic_pointer_cast<SetpointManagerSingleZoneCooling_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new SetpointManagerSingleZoneCooling_Impl(*setpointManagerSingleZoneCooling, this, keepHandle));
      }
      if (auto setpointManagerSingleZoneOneStageCooling =
            std::dynamic_pointer_cast<SetpointManagerSingleZoneOneStageCooling_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new SetpointManagerSingleZoneOneStageCooling_Impl(*setpointManagerSingleZoneOneStageCooling, this, keepHandle));
      }
      if (auto setpointManagerSingleZoneOneStageHeating =
            std::dynamic_pointer_cast<SetpointManagerSingleZoneOneStageHeating_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new SetpointManagerSingleZoneOneStageHeating_Impl(*setpointManagerSingleZoneOneStageHeating, this, keepHandle));
      }
      if (auto setpointManagerSingleZoneHeating = std::dynamic_pointer_cast<SetpointManagerSingleZoneHeating_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new SetpointManagerSingleZoneHeating_Impl(*setpointManagerSingleZoneHeating, this, keepHandle));
      }
      if (auto setpointManagerSingleZoneHumidityMaximum =
            std::dynamic_pointer_cast<SetpointManagerSingleZoneHumidityMaximum_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new SetpointManagerSingleZoneHumidityMaximum_Impl(*setpointManagerSingleZoneHumidityMaximum, this, keepHandle));
      }
      if (auto setpointManagerSingleZoneHumidityMinimum =
            std::dynamic_pointer_cast<SetpointManagerSingleZoneHumidityMinimum_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new SetpointManagerSingleZoneHumidityMinimum_Impl(*setpointManagerSingleZoneHumidityMinimum, this, keepHandle));
      }
      if (auto setpointManagerSingleZoneReheat = std::dynamic_pointer_cast<SetpointManagerSingleZoneReheat_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new SetpointManagerSingleZoneReheat_Impl(*setpointManagerSingleZoneReheat, this, keepHandle));
      }
      if (auto airTerminal = std::dynamic_pointer_cast<AirTerminalSingleDuctConstantVolumeNoReheat_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new AirTerminalSingleDuctConstantVolumeNoReheat_Impl(*airTerminal, this, keepHandle));
      }
      if (auto airTerminalReheat = std::dynamic_pointer_cast<AirTerminalSingleDuctConstantVolumeReheat_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new AirTerminalSingleDuctConstantVolumeReheat_Impl(*airTerminalReheat, this, keepHandle));
      }
      if (auto airTerminalSingleDuctInletSideMixer = std::dynamic_pointer_cast<AirTerminalSingleDuctInletSideMixer_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new AirTerminalSingleDuctInletSideMixer_Impl(*airTerminalSingleDuctInletSideMixer, this, keepHandle));
      }
      if (auto airTerminalParallelPIUReheat = std::dynamic_pointer_cast<AirTerminalSingleDuctParallelPIUReheat_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new AirTerminalSingleDuctParallelPIUReheat_Impl(*airTerminalParallelPIUReheat, this, keepHandle));
      }
      if (auto airTerminalSeriesPIUReheat = std::dynamic_pointer_cast<AirTerminalSingleDuctSeriesPIUReheat_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new AirTerminalSingleDuctSeriesPIUReheat_Impl(*airTerminalSeriesPIUReheat, this, keepHandle));
      }
      if (auto airTerminalDualDuctConstantVolume = std::dynamic_pointer_cast<AirTerminalDualDuctConstantVolume_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new AirTerminalDualDuctConstantVolume_Impl(*airTerminalDualDuctConstantVolume, this, keepHandle));
      }
      if (auto airTerminalDualDuctVAV = std::dynamic_pointer_cast<AirTerminalDualDuctVAV_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new AirTerminalDualDuctVAV_Impl(*airTerminalDualDuctVAV, this, keepHandle));
      }
      if (auto airTerminalDualDuctVAVOutdoorAir = std::dynamic_pointer_cast<AirTerminalDualDuctVAVOutdoorAir_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new AirTerminalDualDuctVAVOutdoorAir_Impl(*airTerminalDualDuctVAVOutdoorAir, this, keepHandle));
      }
      if (auto airTerminalSingleDuctConstantVolumeCooledBeam =
            std::dynamic_pointer_cast<AirTerminalSingleDuctConstantVolumeCooledBeam_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new AirTerminalSingleDuctConstantVolumeCooledBeam_Impl(*airTerminalSingleDuctConstantVolumeCooledBeam, this, keepHandle));
      }
      if (auto airTerminalSingleDuctConstantVolumeFourPipeBeam =
            std::dynamic_pointer_cast<AirTerminalSingleDuctConstantVolumeFourPipeBeam_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new AirTerminalSingleDuctConstantVolumeFourPipeBeam_Impl(*airTerminalSingleDuctConstantVolumeFourPipeBeam, this, keepHandle));
      }
      if (auto airTerminalSingleDuctConstantVolumeFourPipeInduction =
            std::dynamic_pointer_cast<AirTerminalSingleDuctConstantVolumeFourPipeInduction_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new AirTerminalSingleDuctConstantVolumeFourPipeInduction_Impl(*airTerminalSingleDuctConstantVolumeFourPipeInduction, this, keepHandle));
      }
      if (auto airTerminalSingleDuctUserDefined = std::dynamic_pointer_cast<AirTerminalSingleDuctUserDefined_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new AirTerminalSingleDuctUserDefined_Impl(*airTerminalSingleDuctUserDefined, this, keepHandle));
      }
      if (auto airTerminalSingleDuctVAVHeatAndCoolNoReheat =
            std::dynamic_pointer_cast<AirTerminalSingleDuctVAVHeatAndCoolNoReheat_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new AirTerminalSingleDuctVAVHeatAndCoolNoReheat_Impl(*airTerminalSingleDuctVAVHeatAndCoolNoReheat, this, keepHandle));
      }
      if (auto airTerminalSingleDuctVAVHeatAndCoolReheat =
            std::dynamic_pointer_cast<AirTerminalSingleDuctVAVHeatAndCoolReheat_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new AirTerminalSingleDuctVAVHeatAndCoolReheat_Impl(*airTerminalSingleDuctVAVHeatAndCoolReheat, this, keepHandle));
      }
      if (auto airTerminalSingleDuctVAVNoReheat = std::dynamic_pointer_cast<AirTerminalSingleDuctVAVNoReheat_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new AirTerminalSingleDuctVAVNoReheat_Impl(*airTerminalSingleDuctVAVNoReheat, this, keepHandle));
      }
      if (auto airTerminalSingleDuctVAVReheat = std::dynamic_pointer_cast<AirTerminalSingleDuctVAVReheat_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new AirTerminalSingleDuctVAVReheat_Impl(*airTerminalSingleDuctVAVReheat, this, keepHandle));
      }
      if (auto airTerminalSingleDuctVAVReheatVariableSpeedFan =
            std::dynamic_pointer_cast<AirTerminalSingleDuctVAVReheatVariableSpeedFan_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new AirTerminalSingleDuctVAVReheatVariableSpeedFan_Impl(*airTerminalSingleDuctVAVReheatVariableSpeedFan, this, keepHandle));
      }
      if (auto node = std::dynamic_pointer_cast<Node_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new Node_Impl(*node, this, keepHandle));
      }
      if (auto nodeList = std::dynamic_pointer_cast<NodeList_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new NodeList_Impl(*nodeList, this, keepHandle));
      }
      if (auto outdoorAirMixer = std::dynamic_pointer_cast<OutdoorAirMixer_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new OutdoorAirMixer_Impl(*outdoorAirMixer, this, keepHandle));
      }
      if (auto outdoorAirEquipmentList = std::dynamic_pointer_cast<AirLoopHVACOutdoorAirSystemEquipmentList_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new AirLoopHVACOutdoorAirSystemEquipmentList_Impl(*outdoorAirEquipmentList, this, keepHandle));
      }
      if (auto outdoorAirController = std::dynamic_pointer_cast<ControllerOutdoorAir_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new ControllerOutdoorAir_Impl(*outdoorAirController, this, keepHandle));
      }
      if (auto energyRecoveryVentilatorController =
            std::dynamic_pointer_cast<ZoneHVACEnergyRecoveryVentilatorController_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new ZoneHVACEnergyRecoveryVentilatorController_Impl(*energyRecoveryVentilatorController, this, keepHandle));
      }
      if (auto mechanicalVentilationController = std::dynamic_pointer_cast<ControllerMechanicalVentilation_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new ControllerMechanicalVentilation_Impl(*mechanicalVentilationController, this, keepHandle));
      }
      if (auto dsoa = std::dynamic_pointer_cast<DesignSpecificationOutdoorAir_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new DesignSpecificationOutdoorAir_Impl(*dsoa, this, keepHandle));
      }
      if (auto dsoaSpaceList = std::dynamic_pointer_cast<DesignSpecificationOutdoorAirSpaceList_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new DesignSpecificationOutdoorAirSpaceList_Impl(*dsoaSpaceList, this, keepHandle));
      }
      if (auto dsats = std::dynamic_pointer_cast<DesignSpecificationAirTerminalSizing_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new DesignSpecificationAirTerminalSizing_Impl(*dsats, this, keepHandle));
      }
      if (auto dszhs = std::dynamic_pointer_cast<DesignSpecificationZoneHVACSizing_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new DesignSpecificationZoneHVACSizing_Impl(*dszhs, this, keepHandle));
      }
      if (auto zone = std::dynamic_pointer_cast<ThermalZone_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new ThermalZone_Impl(*zone, this, keepHandle));
      }
      if (auto space = std::dynamic_pointer_cast<Space_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new Space_Impl(*space, this, keepHandle));
      }
      if (auto spaceConnections = std::dynamic_pointer_cast<SpaceHVACEquipmentConnections_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new SpaceHVACEquipmentConnections_Impl(*spaceConnections, this, keepHandle));
      }
      if (auto spaceSplitter = std::dynamic_pointer_cast<SpaceHVACZoneEquipmentSplitter_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new SpaceHVACZoneEquipmentSplitter_Impl(*spaceSplitter, this, keepHandle));
      }
      if (auto sizingZone = std::dynamic_pointer_cast<SizingZone_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new SizingZone_Impl(*sizingZone, this, keepHandle));
      }
      if (auto sizingPlant = std::dynamic_pointer_cast<SizingPlant_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new SizingPlant_Impl(*sizingPlant, this, keepHandle));
      }
      if (auto sizingSystem = std::dynamic_pointer_cast<SizingSystem_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new SizingSystem_Impl(*sizingSystem, this, keepHandle));
      }
      if (auto designDay = std::dynamic_pointer_cast<DesignDay_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new DesignDay_Impl(*designDay, this, keepHandle));
      }
      if (auto sizingPeriodWeatherFileConditionType = std::dynamic_pointer_cast<SizingPeriodWeatherFileConditionType_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new SizingPeriodWeatherFileConditionType_Impl(*sizingPeriodWeatherFileConditionType, this, keepHandle));
      }
      if (auto sizingPeriodWeatherFileDays = std::dynamic_pointer_cast<SizingPeriodWeatherFileDays_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new SizingPeriodWeatherFileDays_Impl(*sizingPeriodWeatherFileDays, this, keepHandle));
      }
      if (auto sizingParameters = std::dynamic_pointer_cast<SizingParameters_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new SizingParameters_Impl(*sizingParameters, this, keepHandle));
      }
      if (auto zoneConnections = std::dynamic_pointer_cast<ZoneHVACEquipmentConnections_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new ZoneHVACEquipmentConnections_Impl(*zoneConnections, this, keepHandle));
      }
      if (auto zoneEquipmentList = std::dynamic_pointer_cast<ZoneHVACEquipmentList_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new ZoneHVACEquipmentList_Impl(*zoneEquipmentList, this, keepHandle));
      }
      if (auto airDistributionUnit = std::dynamic_pointer_cast<ZoneHVACAirDistributionUnit_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new ZoneHVACAirDistributionUnit_Impl(*airDistributionUnit, this, keepHandle));
      }
      if (auto vrf = std::dynamic_pointer_cast<AirConditionerVariableRefrigerantFlow_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new AirConditionerVariableRefrigerantFlow_Impl(*vrf, this, keepHandle));
      }
      if (auto collector = std::dynamic_pointer_cast<SolarCollectorFlatPlatePhotovoltaicThermal_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new SolarCollectorFlatPlatePhotovoltaicThermal_Impl(*collector, this, keepHandle));
      }
      if (auto collector = std::dynamic_pointer_cast<SolarCollectorFlatPlateWater_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new SolarCollectorFlatPlateWater_Impl(*collector, this, keepHandle));
      }
      if (auto collector = std::dynamic_pointer_cast<SolarCollectorIntegralCollectorStorage_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new SolarCollectorIntegralCollectorStorage_Impl(*collector, this, keepHandle));
      }
      if (auto collector = std::dynamic_pointer_cast<SolarCollectorPerformanceFlatPlate_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new SolarCollectorPerformanceFlatPlate_Impl(*collector, this, keepHandle));
      }
      if (auto collector = std::dynamic_pointer_cast<SolarCollectorPerformanceIntegralCollectorStorage_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new SolarCollectorPerformanceIntegralCollectorStorage_Impl(*collector, this, keepHandle));
      }
      if (auto collector = std::dynamic_pointer_cast<SolarCollectorPerformancePhotovoltaicThermalBIPVT_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new SolarCollectorPerformancePhotovoltaicThermalBIPVT_Impl(*collector, this, keepHandle));
      }
      if (auto collector = std::dynamic_pointer_cast<SolarCollectorPerformancePhotovoltaicThermalSimple_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new SolarCollectorPerformancePhotovoltaicThermalSimple_Impl(*collector, this, keepHandle));
      }
      if (auto collector = std::dynamic_pointer_cast<SolarCollectorUnglazedTranspired_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new SolarCollectorUnglazedTranspired_Impl(*collector, this, keepHandle));
      }
      if (auto collector = std::dynamic_pointer_cast<SolarCollectorUnglazedTranspiredMultisystem_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new SolarCollectorUnglazedTranspiredMultisystem_Impl(*collector, this, keepHandle));
      }
      if (auto surfaceContaminantBLD =
            std::dynamic_pointer_cast<SurfaceContaminantSourceAndSinkGenericBoundaryLayerDiffusion_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new SurfaceContaminantSourceAndSinkGenericBoundaryLayerDiffusion_Impl(*surfaceContaminantBLD, this, keepHandle));
      }
      if (auto surfaceContaminantDVS =
            std::dynamic_pointer_cast<SurfaceContaminantSourceAndSinkGenericDepositionVelocitySink_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new SurfaceContaminantSourceAndSinkGenericDepositionVelocitySink_Impl(*surfaceContaminantDVS, this, keepHandle));
      }
      if (auto surfaceContaminantPD = std::dynamic_pointer_cast<SurfaceContaminantSourceAndSinkGenericPressureDriven_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new SurfaceContaminantSourceAndSinkGenericPressureDriven_Impl(*surfaceContaminantPD, this, keepHandle));
      }
      if (auto surfaceControlMovIns = std::dynamic_pointer_cast<SurfaceControlMovableInsulation_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new SurfaceControlMovableInsulation_Impl(*surfaceControlMovIns, this, keepHandle));
      }
      if (auto surfacePropertiesVaporCoefficients = std::dynamic_pointer_cast<SurfacePropertiesVaporCoefficients_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new SurfacePropertiesVaporCoefficients_Impl(*surfacePropertiesVaporCoefficients, this, keepHandle));
      }
      if (auto heatPumpAirToWater = std::dynamic_pointer_cast<HeatPumpAirToWater_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new HeatPumpAirToWater_Impl(*heatPumpAirToWater, this, keepHandle));
      }
      if (auto heatPumpAirToWaterFuelFiredCooling = std::dynamic_pointer_cast<HeatPumpAirToWaterFuelFiredCooling_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new HeatPumpAirToWaterFuelFiredCooling_Impl(*heatPumpAirToWaterFuelFiredCooling, this, keepHandle));
      }
      if (auto heatPumpAirToWaterFuelFiredHeating = std::dynamic_pointer_cast<HeatPumpAirToWaterFuelFiredHeating_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new HeatPumpAirToWaterFuelFiredHeating_Impl(*heatPumpAirToWaterFuelFiredHeating, this, keepHandle));
      }
      if (auto loadProfilePlant = std::dynamic_pointer_cast<LoadProfilePlant_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new LoadProfilePlant_Impl(*loadProfilePlant, this, keepHandle));
      }
      if (auto plantComponentTemperatureSource = std::dynamic_pointer_cast<PlantComponentTemperatureSource_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new PlantComponentTemperatureSource_Impl(*plantComponentTemperatureSource, this, keepHandle));
      }
      if (auto plantComponentUserDefined = std::dynamic_pointer_cast<PlantComponentUserDefined_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new PlantComponentUserDefined_Impl(*plantComponentUserDefined, this, keepHandle));
      }
      if (auto temperingValve = std::dynamic_pointer_cast<TemperingValve_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new TemperingValve_Impl(*temperingValve, this, keepHandle));
      }
      if (auto waterUseConnections = std::dynamic_pointer_cast<WaterUseConnections_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new WaterUseConnections_Impl(*waterUseConnections, this, keepHandle));
      }
      if (auto vrfFluid = std::dynamic_pointer_cast<AirConditionerVariableRefrigerantFlowFluidTemperatureControl_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new AirConditionerVariableRefrigerantFlowFluidTemperatureControl_Impl(*vrfFluid, this, keepHandle));
      }
      if (auto vrfFluidHR = std::dynamic_pointer_cast<AirConditionerVariableRefrigerantFlowFluidTemperatureControlHR_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new AirConditionerVariableRefrigerantFlowFluidTemperatureControlHR_Impl(*vrfFluidHR, this, keepHandle));
      }
      if (auto centralHeatPumpSystem = std::dynamic_pointer_cast<CentralHeatPumpSystem_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new CentralHeatPumpSystem_Impl(*centralHeatPumpSystem, this, keepHandle));
      }
      if (auto heatPumpPlantLoopEIRCooling = std::dynamic_pointer_cast<HeatPumpPlantLoopEIRCooling_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new HeatPumpPlantLoopEIRCooling_Impl(*heatPumpPlantLoopEIRCooling, this, keepHandle));
      }
      if (auto heatPumpPlantLoopEIRHeating = std::dynamic_pointer_cast<HeatPumpPlantLoopEIRHeating_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new HeatPumpPlantLoopEIRHeating_Impl(*heatPumpPlantLoopEIRHeating, this, keepHandle));
      }
      if (auto heatPumpWaterToWaterEquationFitCooling =
            std::dynamic_pointer_cast<HeatPumpWaterToWaterEquationFitCooling_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new HeatPumpWaterToWaterEquationFitCooling_Impl(*heatPumpWaterToWaterEquationFitCooling, this, keepHandle));
      }
      if (auto heatPumpWaterToWaterEquationFitHeating =
            std::dynamic_pointer_cast<HeatPumpWaterToWaterEquationFitHeating_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new HeatPumpWaterToWaterEquationFitHeating_Impl(*heatPumpWaterToWaterEquationFitHeating, this, keepHandle));
      }
      if (auto waterHeaterStratified = std::dynamic_pointer_cast<WaterHeaterStratified_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new WaterHeaterStratified_Impl(*waterHeaterStratified, this, keepHandle));
      }
      if (auto waterHeaterMixed = std::dynamic_pointer_cast<WaterHeaterMixed_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new WaterHeaterMixed_Impl(*waterHeaterMixed, this, keepHandle));
      }
      if (auto waterHeaterSizing = std::dynamic_pointer_cast<WaterHeaterSizing_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new WaterHeaterSizing_Impl(*waterHeaterSizing, this, keepHandle));
      }
      if (auto heatPumpWaterToWaterParameterEstimationCooling =
            std::dynamic_pointer_cast<HeatPumpWaterToWaterParameterEstimationCooling_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new HeatPumpWaterToWaterParameterEstimationCooling_Impl(*heatPumpWaterToWaterParameterEstimationCooling, this, keepHandle));
      }
      if (auto heatPumpWaterToWaterParameterEstimationHeating =
            std::dynamic_pointer_cast<HeatPumpWaterToWaterParameterEstimationHeating_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new HeatPumpWaterToWaterParameterEstimationHeating_Impl(*heatPumpWaterToWaterParameterEstimationHeating, this, keepHandle));
      }
      if (auto heatExchangerFluidToFluid = std::dynamic_pointer_cast<HeatExchangerFluidToFluid_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new HeatExchangerFluidToFluid_Impl(*heatExchangerFluidToFluid, this, keepHandle));
      }
      if (auto comfortViewFactorAngles = std::dynamic_pointer_cast<ComfortViewFactorAngles_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new ComfortViewFactorAngles_Impl(*comfortViewFactorAngles, this, keepHandle));
      }
      if (auto complexFenestrationPropertySolarAbsorbedLayers =
            std::dynamic_pointer_cast<ComplexFenestrationPropertySolarAbsorbedLayers_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new ComplexFenestrationPropertySolarAbsorbedLayers_Impl(*complexFenestrationPropertySolarAbsorbedLayers, this, keepHandle));
      }
      if (auto constructionComplexFenestrationState = std::dynamic_pointer_cast<ConstructionComplexFenestrationState_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new ConstructionComplexFenestrationState_Impl(*constructionComplexFenestrationState, this, keepHandle));
      }
      if (auto complianceBuilding = std::dynamic_pointer_cast<ComplianceBuilding_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new ComplianceBuilding_Impl(*complianceBuilding, this, keepHandle));
      }
      if (auto shadingBuilding = std::dynamic_pointer_cast<ShadingBuilding_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new ShadingBuilding_Impl(*shadingBuilding, this, keepHandle));
      }
      if (auto shadingBuildingDetailed = std::dynamic_pointer_cast<ShadingBuildingDetailed_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new ShadingBuildingDetailed_Impl(*shadingBuildingDetailed, this, keepHandle));
      }
      if (auto shadingFin = std::dynamic_pointer_cast<ShadingFin_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new ShadingFin_Impl(*shadingFin, this, keepHandle));
      }
      if (auto shadingFinProjection = std::dynamic_pointer_cast<ShadingFinProjection_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new ShadingFinProjection_Impl(*shadingFinProjection, this, keepHandle));
      }
      if (auto shadingOverhang = std::dynamic_pointer_cast<ShadingOverhang_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new ShadingOverhang_Impl(*shadingOverhang, this, keepHandle));
      }
      if (auto shadingOverhangProjection = std::dynamic_pointer_cast<ShadingOverhangProjection_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new ShadingOverhangProjection_Impl(*shadingOverhangProjection, this, keepHandle));
      }
      if (auto shadingSite = std::dynamic_pointer_cast<ShadingSite_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new ShadingSite_Impl(*shadingSite, this, keepHandle));
      }
      if (auto shadingSiteDetailed = std::dynamic_pointer_cast<ShadingSiteDetailed_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new ShadingSiteDetailed_Impl(*shadingSiteDetailed, this, keepHandle));
      }
      if (auto shadingZoneDetailed = std::dynamic_pointer_cast<ShadingZoneDetailed_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new ShadingZoneDetailed_Impl(*shadingZoneDetailed, this, keepHandle));
      }
      if (auto shadingPropertyReflectance = std::dynamic_pointer_cast<ShadingPropertyReflectance_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new ShadingPropertyReflectance_Impl(*shadingPropertyReflectance, this, keepHandle));
      }
      if (auto blind = std::dynamic_pointer_cast<Blind_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new Blind_Impl(*blind, this, keepHandle));
      }
      if (auto shade = std::dynamic_pointer_cast<detail::Shade_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new detail::Shade_Impl(*shade, this, keepHandle));
      }
      if (auto shadeEquivalentLayer = std::dynamic_pointer_cast<WindowMaterialShadeEquivalentLayer_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new WindowMaterialShadeEquivalentLayer_Impl(*shadeEquivalentLayer, this, keepHandle));
      }
      if (auto screen = std::dynamic_pointer_cast<detail::Screen_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new detail::Screen_Impl(*screen, this, keepHandle));
      }
      if (auto blindEquivalentLayer = std::dynamic_pointer_cast<WindowMaterialBlindEquivalentLayer_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new WindowMaterialBlindEquivalentLayer_Impl(*blindEquivalentLayer, this, keepHandle));
      }
      if (auto drapeEquivalentLayer = std::dynamic_pointer_cast<WindowMaterialDrapeEquivalentLayer_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new WindowMaterialDrapeEquivalentLayer_Impl(*drapeEquivalentLayer, this, keepHandle));
      }
      if (auto complexShade = std::dynamic_pointer_cast<WindowMaterialComplexShade_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new WindowMaterialComplexShade_Impl(*complexShade, this, keepHandle));
      }
      if (auto gap = std::dynamic_pointer_cast<WindowMaterialGap_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new WindowMaterialGap_Impl(*gap, this, keepHandle));
      }
      if (auto gapEquivalentLayer = std::dynamic_pointer_cast<WindowMaterialGapEquivalentLayer_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new WindowMaterialGapEquivalentLayer_Impl(*gapEquivalentLayer, this, keepHandle));
      }
      if (auto glazingEquivalentLayer = std::dynamic_pointer_cast<WindowMaterialGlazingEquivalentLayer_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new WindowMaterialGlazingEquivalentLayer_Impl(*glazingEquivalentLayer, this, keepHandle));
      }
      if (auto screenEquivalentLayer = std::dynamic_pointer_cast<WindowMaterialScreenEquivalentLayer_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new WindowMaterialScreenEquivalentLayer_Impl(*screenEquivalentLayer, this, keepHandle));
      }
      if (auto gas = std::dynamic_pointer_cast<Gas_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new Gas_Impl(*gas, this, keepHandle));
      }
      if (auto gasMixture = std::dynamic_pointer_cast<GasMixture_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new GasMixture_Impl(*gasMixture, this, keepHandle));
      }
      if (auto shadowCalculation = std::dynamic_pointer_cast<ShadowCalculation_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new ShadowCalculation_Impl(*shadowCalculation, this, keepHandle));
      }
      if (auto componentCostAdjustments = std::dynamic_pointer_cast<ComponentCostAdjustments_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new ComponentCostAdjustments_Impl(*componentCostAdjustments, this, keepHandle));
      }
      if (auto currencyType = std::dynamic_pointer_cast<CurrencyType_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new CurrencyType_Impl(*currencyType, this, keepHandle));
      }
      if (auto lifeCycleCostParameters = std::dynamic_pointer_cast<LifeCycleCostParameters_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new LifeCycleCostParameters_Impl(*lifeCycleCostParameters, this, keepHandle));
      }
      if (auto lifeCycleCostUsePriceEscalation = std::dynamic_pointer_cast<LifeCycleCostUsePriceEscalation_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new LifeCycleCostUsePriceEscalation_Impl(*lifeCycleCostUsePriceEscalation, this, keepHandle));
      }
      if (auto runPeriodControlDaylightSavingTime = std::dynamic_pointer_cast<RunPeriodControlDaylightSavingTime_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new RunPeriodControlDaylightSavingTime_Impl(*runPeriodControlDaylightSavingTime, this, keepHandle));
      }
      if (auto runPeriodControlSpecialDays = std::dynamic_pointer_cast<RunPeriodControlSpecialDays_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new RunPeriodControlSpecialDays_Impl(*runPeriodControlSpecialDays, this, keepHandle));
      }
      if (auto electricLoadCenterDistribution = std::dynamic_pointer_cast<ElectricLoadCenterDistribution_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new ElectricLoadCenterDistribution_Impl(*electricLoadCenterDistribution, this, keepHandle));
      }
      if (auto electricLoadCenterStorageConverter = std::dynamic_pointer_cast<ElectricLoadCenterStorageConverter_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new ElectricLoadCenterStorageConverter_Impl(*electricLoadCenterStorageConverter, this, keepHandle));
      }
      if (auto electricLoadCenterInverterFunctionOfPower =
            std::dynamic_pointer_cast<ElectricLoadCenterInverterFunctionOfPower_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new ElectricLoadCenterInverterFunctionOfPower_Impl(*electricLoadCenterInverterFunctionOfPower, this, keepHandle));
      }
      if (auto electricLoadCenterTransformer = std::dynamic_pointer_cast<ElectricLoadCenterTransformer_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new ElectricLoadCenterTransformer_Impl(*electricLoadCenterTransformer, this, keepHandle));
      }
      if (auto energyManagementSystemActuator = std::dynamic_pointer_cast<EnergyManagementSystemActuator_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new EnergyManagementSystemActuator_Impl(*energyManagementSystemActuator, this, keepHandle));
      }
      if (auto energyManagementSystemConstructionIndexVariable =
            std::dynamic_pointer_cast<EnergyManagementSystemConstructionIndexVariable_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new EnergyManagementSystemConstructionIndexVariable_Impl(*energyManagementSystemConstructionIndexVariable, this, keepHandle));
      }
      if (auto energyManagementSystemGlobalVariable = std::dynamic_pointer_cast<EnergyManagementSystemGlobalVariable_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new EnergyManagementSystemGlobalVariable_Impl(*energyManagementSystemGlobalVariable, this, keepHandle));
      }
      if (auto energyManagementSystemInternalVariable =
            std::dynamic_pointer_cast<EnergyManagementSystemInternalVariable_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new EnergyManagementSystemInternalVariable_Impl(*energyManagementSystemInternalVariable, this, keepHandle));
      }
      if (auto energyManagementSystemMeteredOutputVariable =
            std::dynamic_pointer_cast<EnergyManagementSystemMeteredOutputVariable_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new EnergyManagementSystemMeteredOutputVariable_Impl(*energyManagementSystemMeteredOutputVariable, this, keepHandle));
      }
      if (auto energyManagementSystemOutputVariable = std::dynamic_pointer_cast<EnergyManagementSystemOutputVariable_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new EnergyManagementSystemOutputVariable_Impl(*energyManagementSystemOutputVariable, this, keepHandle));
      }
      if (auto outputConstructions = std::dynamic_pointer_cast<OutputConstructions_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new OutputConstructions_Impl(*outputConstructions, this, keepHandle));
      }
      if (auto outputDaylightFactors = std::dynamic_pointer_cast<OutputDaylightFactors_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new OutputDaylightFactors_Impl(*outputDaylightFactors, this, keepHandle));
      }
      if (auto outputDebuggingData = std::dynamic_pointer_cast<OutputDebuggingData_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new OutputDebuggingData_Impl(*outputDebuggingData, this, keepHandle));
      }
      if (auto outputDiagnostics = std::dynamic_pointer_cast<OutputDiagnostics_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new OutputDiagnostics_Impl(*outputDiagnostics, this, keepHandle));
      }
      if (auto outputEnergyManagementSystem = std::dynamic_pointer_cast<OutputEnergyManagementSystem_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new OutputEnergyManagementSystem_Impl(*outputEnergyManagementSystem, this, keepHandle));
      }
      if (auto outputEnvironmentalImpactFactors = std::dynamic_pointer_cast<OutputEnvironmentalImpactFactors_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new OutputEnvironmentalImpactFactors_Impl(*outputEnvironmentalImpactFactors, this, keepHandle));
      }
      if (auto outputControlFiles = std::dynamic_pointer_cast<OutputControlFiles_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new OutputControlFiles_Impl(*outputControlFiles, this, keepHandle));
      }
      if (auto outputControlIlluminanceMapStyle = std::dynamic_pointer_cast<OutputControlIlluminanceMapStyle_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new OutputControlIlluminanceMapStyle_Impl(*outputControlIlluminanceMapStyle, this, keepHandle));
      }
      if (auto outputControlReportingTolerances = std::dynamic_pointer_cast<OutputControlReportingTolerances_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new OutputControlReportingTolerances_Impl(*outputControlReportingTolerances, this, keepHandle));
      }
      if (auto outputControlResilienceSummaries = std::dynamic_pointer_cast<OutputControlResilienceSummaries_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new OutputControlResilienceSummaries_Impl(*outputControlResilienceSummaries, this, keepHandle));
      }
      if (auto outputControlSizingStyle = std::dynamic_pointer_cast<OutputControlSizingStyle_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new OutputControlSizingStyle_Impl(*outputControlSizingStyle, this, keepHandle));
      }
      if (auto outputControlTableStyle = std::dynamic_pointer_cast<OutputControlTableStyle_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new OutputControlTableStyle_Impl(*outputControlTableStyle, this, keepHandle));
      }
      if (auto outputControlTimestamp = std::dynamic_pointer_cast<OutputControlTimestamp_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new OutputControlTimestamp_Impl(*outputControlTimestamp, this, keepHandle));
      }
      if (auto outputControlSurfaceColorScheme = std::dynamic_pointer_cast<OutputControlSurfaceColorScheme_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new OutputControlSurfaceColorScheme_Impl(*outputControlSurfaceColorScheme, this, keepHandle));
      }
      if (auto outputJSON = std::dynamic_pointer_cast<OutputJSON_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new OutputJSON_Impl(*outputJSON, this, keepHandle));
      }
      if (auto outputPreprocessorMessage = std::dynamic_pointer_cast<OutputPreprocessorMessage_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new OutputPreprocessorMessage_Impl(*outputPreprocessorMessage, this, keepHandle));
      }
      if (auto outputSQLite = std::dynamic_pointer_cast<OutputSQLite_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new OutputSQLite_Impl(*outputSQLite, this, keepHandle));
      }
      if (auto outputSchedules = std::dynamic_pointer_cast<OutputSchedules_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new OutputSchedules_Impl(*outputSchedules, this, keepHandle));
      }
      if (auto outputTableAnnual = std::dynamic_pointer_cast<OutputTableAnnual_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new OutputTableAnnual_Impl(*outputTableAnnual, this, keepHandle));
      }
      if (auto outputTableMonthly = std::dynamic_pointer_cast<OutputTableMonthly_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new OutputTableMonthly_Impl(*outputTableMonthly, this, keepHandle));
      }
      if (auto outputTableReportPeriod = std::dynamic_pointer_cast<OutputTableReportPeriod_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new OutputTableReportPeriod_Impl(*outputTableReportPeriod, this, keepHandle));
      }
      if (auto outputTableSummaryReports = std::dynamic_pointer_cast<OutputTableSummaryReports_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new OutputTableSummaryReports_Impl(*outputTableSummaryReports, this, keepHandle));
      }
      if (auto outputTableTimeBins = std::dynamic_pointer_cast<OutputTableTimeBins_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new OutputTableTimeBins_Impl(*outputTableTimeBins, this, keepHandle));
      }
      if (auto outputVariable = std::dynamic_pointer_cast<OutputVariable_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new OutputVariable_Impl(*outputVariable, this, keepHandle));
      }
      if (auto outputVariableDictionary = std::dynamic_pointer_cast<OutputVariableDictionary_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new OutputVariableDictionary_Impl(*outputVariableDictionary, this, keepHandle));
      }
      if (auto outputSurfacesList = std::dynamic_pointer_cast<OutputSurfacesList_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new OutputSurfacesList_Impl(*outputSurfacesList, this, keepHandle));
      }
      if (auto outputSurfacesDrawing = std::dynamic_pointer_cast<OutputSurfacesDrawing_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new OutputSurfacesDrawing_Impl(*outputSurfacesDrawing, this, keepHandle));
      }
      if (auto pythonPluginOutputVariable = std::dynamic_pointer_cast<PythonPluginOutputVariable_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new PythonPluginOutputVariable_Impl(*pythonPluginOutputVariable, this, keepHandle));
      }
      if (auto pythonPluginTrendVariable = std::dynamic_pointer_cast<PythonPluginTrendVariable_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new PythonPluginTrendVariable_Impl(*pythonPluginTrendVariable, this, keepHandle));
      }
      if (auto pythonPluginVariable = std::dynamic_pointer_cast<PythonPluginVariable_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new PythonPluginVariable_Impl(*pythonPluginVariable, this, keepHandle));
      }
      if (auto pythonPluginSearchPaths = std::dynamic_pointer_cast<PythonPluginSearchPaths_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new PythonPluginSearchPaths_Impl(*pythonPluginSearchPaths, this, keepHandle));
      }
      if (auto energyManagementSystemTrendVariable = std::dynamic_pointer_cast<EnergyManagementSystemTrendVariable_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new EnergyManagementSystemTrendVariable_Impl(*energyManagementSystemTrendVariable, this, keepHandle));
      }
      if (auto environmentalImpactFactors = std::dynamic_pointer_cast<EnvironmentalImpactFactors_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new EnvironmentalImpactFactors_Impl(*environmentalImpactFactors, this, keepHandle));
      }
      if (auto fuelFactors = std::dynamic_pointer_cast<FuelFactors_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new FuelFactors_Impl(*fuelFactors, this, keepHandle));
      }
      if (auto meterCustom = std::dynamic_pointer_cast<MeterCustom_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new MeterCustom_Impl(*meterCustom, this, keepHandle));
      }
      if (auto meterCustomDecrement = std::dynamic_pointer_cast<MeterCustomDecrement_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new MeterCustomDecrement_Impl(*meterCustomDecrement, this, keepHandle));
      }
      if (auto energyManagementSystemProgram = std::dynamic_pointer_cast<EnergyManagementSystemProgram_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new EnergyManagementSystemProgram_Impl(*energyManagementSystemProgram, this, keepHandle));
      }
      if (auto energyManagementSystemSubroutine = std::dynamic_pointer_cast<EnergyManagementSystemSubroutine_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new EnergyManagementSystemSubroutine_Impl(*energyManagementSystemSubroutine, this, keepHandle));
      }
      if (auto energyManagementSystemProgramCallingManager =
            std::dynamic_pointer_cast<EnergyManagementSystemProgramCallingManager_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new EnergyManagementSystemProgramCallingManager_Impl(*energyManagementSystemProgramCallingManager, this, keepHandle));
      }
      if (auto electricLoadCenterInverterLookUpTable = std::dynamic_pointer_cast<ElectricLoadCenterInverterLookUpTable_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new ElectricLoadCenterInverterLookUpTable_Impl(*electricLoadCenterInverterLookUpTable, this, keepHandle));
      }
      if (auto electricLoadCenterInverterPVWatts = std::dynamic_pointer_cast<ElectricLoadCenterInverterPVWatts_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new ElectricLoadCenterInverterPVWatts_Impl(*electricLoadCenterInverterPVWatts, this, keepHandle));
      }
      if (auto electricLoadCenterInverterSimple = std::dynamic_pointer_cast<ElectricLoadCenterInverterSimple_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new ElectricLoadCenterInverterSimple_Impl(*electricLoadCenterInverterSimple, this, keepHandle));
      }
      if (auto electricLoadCenterStorageBattery = std::dynamic_pointer_cast<ElectricLoadCenterStorageBattery_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new ElectricLoadCenterStorageBattery_Impl(*electricLoadCenterStorageBattery, this, keepHandle));
      }
      if (auto electricLoadCenterStorageSimple = std::dynamic_pointer_cast<ElectricLoadCenterStorageSimple_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new ElectricLoadCenterStorageSimple_Impl(*electricLoadCenterStorageSimple, this, keepHandle));
      }
      if (auto electricLoadCenterStorageLiIonNMCBattery =
            std::dynamic_pointer_cast<ElectricLoadCenterStorageLiIonNMCBattery_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new ElectricLoadCenterStorageLiIonNMCBattery_Impl(*electricLoadCenterStorageLiIonNMCBattery, this, keepHandle));
      }
      if (auto componentCostLineItem = std::dynamic_pointer_cast<ComponentCostLineItem_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new ComponentCostLineItem_Impl(*componentCostLineItem, this, keepHandle));
      }
      if (auto componentCostReference = std::dynamic_pointer_cast<ComponentCostReference_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new ComponentCostReference_Impl(*componentCostReference, this, keepHandle));
      }
      if (auto lifeCycleCost = std::dynamic_pointer_cast<LifeCycleCost_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new LifeCycleCost_Impl(*lifeCycleCost, this, keepHandle));
      }
      if (auto lifeCycleCostUseAdjustment = std::dynamic_pointer_cast<LifeCycleCostUseAdjustment_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new LifeCycleCostUseAdjustment_Impl(*lifeCycleCostUseAdjustment, this, keepHandle));
      }
      if (auto condenserLoop = std::dynamic_pointer_cast<CondenserLoop_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new CondenserLoop_Impl(*condenserLoop, this, keepHandle));
      }
      if (auto condenserEquipmentList = std::dynamic_pointer_cast<CondenserEquipmentList_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new CondenserEquipmentList_Impl(*condenserEquipmentList, this, keepHandle));
      }
      if (auto condenserEquipmentOperationSchemes = std::dynamic_pointer_cast<CondenserEquipmentOperationSchemes_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new CondenserEquipmentOperationSchemes_Impl(*condenserEquipmentOperationSchemes, this, keepHandle));
      }
      if (auto convergenceLimits = std::dynamic_pointer_cast<ConvergenceLimits_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new ConvergenceLimits_Impl(*convergenceLimits, this, keepHandle));
      }
      if (auto performancePrecisionTradeoffs = std::dynamic_pointer_cast<PerformancePrecisionTradeoffs_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new PerformancePrecisionTradeoffs_Impl(*performancePrecisionTradeoffs, this, keepHandle));
      }
      if (auto heatBalanceAlgorithm = std::dynamic_pointer_cast<HeatBalanceAlgorithm_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new HeatBalanceAlgorithm_Impl(*heatBalanceAlgorithm, this, keepHandle));
      }
      if (auto hybridModelZone = std::dynamic_pointer_cast<HybridModelZone_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new HybridModelZone_Impl(*hybridModelZone, this, keepHandle));
      }
      if (auto indoorLivingWall = std::dynamic_pointer_cast<IndoorLivingWall_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new IndoorLivingWall_Impl(*indoorLivingWall, this, keepHandle));
      }
      if (auto heatBalanceSettingsConductionFiniteDifference =
            std::dynamic_pointer_cast<HeatBalanceSettingsConductionFiniteDifference_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new HeatBalanceSettingsConductionFiniteDifference_Impl(*heatBalanceSettingsConductionFiniteDifference, this, keepHandle));
      }
      if (auto hvacTemplatePlantBoiler = std::dynamic_pointer_cast<HVACTemplatePlantBoiler_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new HVACTemplatePlantBoiler_Impl(*hvacTemplatePlantBoiler, this, keepHandle));
      }
      if (auto hvacTemplatePlantBoilerObjectReference =
            std::dynamic_pointer_cast<HVACTemplatePlantBoilerObjectReference_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new HVACTemplatePlantBoilerObjectReference_Impl(*hvacTemplatePlantBoilerObjectReference, this, keepHandle));
      }
      if (auto hvacTemplatePlantChilledWaterLoop = std::dynamic_pointer_cast<HVACTemplatePlantChilledWaterLoop_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new HVACTemplatePlantChilledWaterLoop_Impl(*hvacTemplatePlantChilledWaterLoop, this, keepHandle));
      }
      if (auto hvacTemplatePlantChiller = std::dynamic_pointer_cast<HVACTemplatePlantChiller_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new HVACTemplatePlantChiller_Impl(*hvacTemplatePlantChiller, this, keepHandle));
      }
      if (auto hvacTemplatePlantChillerObjectReference =
            std::dynamic_pointer_cast<HVACTemplatePlantChillerObjectReference_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new HVACTemplatePlantChillerObjectReference_Impl(*hvacTemplatePlantChillerObjectReference, this, keepHandle));
      }
      if (auto hvacTemplatePlantHotWaterLoop = std::dynamic_pointer_cast<HVACTemplatePlantHotWaterLoop_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new HVACTemplatePlantHotWaterLoop_Impl(*hvacTemplatePlantHotWaterLoop, this, keepHandle));
      }
      if (auto hvacTemplatePlantMixedWaterLoop = std::dynamic_pointer_cast<HVACTemplatePlantMixedWaterLoop_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new HVACTemplatePlantMixedWaterLoop_Impl(*hvacTemplatePlantMixedWaterLoop, this, keepHandle));
      }
      if (auto hvacTemplatePlantTower = std::dynamic_pointer_cast<HVACTemplatePlantTower_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new HVACTemplatePlantTower_Impl(*hvacTemplatePlantTower, this, keepHandle));
      }
      if (auto hvacTemplatePlantTowerObjectReference = std::dynamic_pointer_cast<HVACTemplatePlantTowerObjectReference_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new HVACTemplatePlantTowerObjectReference_Impl(*hvacTemplatePlantTowerObjectReference, this, keepHandle));
      }
      if (auto hvacTemplateSystemConstantVolume = std::dynamic_pointer_cast<HVACTemplateSystemConstantVolume_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new HVACTemplateSystemConstantVolume_Impl(*hvacTemplateSystemConstantVolume, this, keepHandle));
      }
      if (auto hvacTemplateSystemDedicatedOutdoorAir = std::dynamic_pointer_cast<HVACTemplateSystemDedicatedOutdoorAir_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new HVACTemplateSystemDedicatedOutdoorAir_Impl(*hvacTemplateSystemDedicatedOutdoorAir, this, keepHandle));
      }
      if (auto hvacTemplateSystemDualDuct = std::dynamic_pointer_cast<HVACTemplateSystemDualDuct_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new HVACTemplateSystemDualDuct_Impl(*hvacTemplateSystemDualDuct, this, keepHandle));
      }
      if (auto hvacTemplateSystemPackagedVAV = std::dynamic_pointer_cast<HVACTemplateSystemPackagedVAV_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new HVACTemplateSystemPackagedVAV_Impl(*hvacTemplateSystemPackagedVAV, this, keepHandle));
      }
      if (auto hvacTemplateSystemVAV = std::dynamic_pointer_cast<HVACTemplateSystemVAV_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new HVACTemplateSystemVAV_Impl(*hvacTemplateSystemVAV, this, keepHandle));
      }
      if (auto hvacTemplateSystemVRF = std::dynamic_pointer_cast<HVACTemplateSystemVRF_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new HVACTemplateSystemVRF_Impl(*hvacTemplateSystemVRF, this, keepHandle));
      }
      if (auto hvacTemplateThermostat = std::dynamic_pointer_cast<HVACTemplateThermostat_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new HVACTemplateThermostat_Impl(*hvacTemplateThermostat, this, keepHandle));
      }
      if (auto hvacTemplateZoneBaseboardHeat = std::dynamic_pointer_cast<HVACTemplateZoneBaseboardHeat_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new HVACTemplateZoneBaseboardHeat_Impl(*hvacTemplateZoneBaseboardHeat, this, keepHandle));
      }
      if (auto hvacTemplateZoneConstantVolume = std::dynamic_pointer_cast<HVACTemplateZoneConstantVolume_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new HVACTemplateZoneConstantVolume_Impl(*hvacTemplateZoneConstantVolume, this, keepHandle));
      }
      if (auto hvacTemplateZoneDualDuct = std::dynamic_pointer_cast<HVACTemplateZoneDualDuct_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new HVACTemplateZoneDualDuct_Impl(*hvacTemplateZoneDualDuct, this, keepHandle));
      }
      if (auto hvacTemplateZoneFanCoil = std::dynamic_pointer_cast<HVACTemplateZoneFanCoil_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new HVACTemplateZoneFanCoil_Impl(*hvacTemplateZoneFanCoil, this, keepHandle));
      }
      if (auto hvacTemplateZonePTAC = std::dynamic_pointer_cast<HVACTemplateZonePTAC_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new HVACTemplateZonePTAC_Impl(*hvacTemplateZonePTAC, this, keepHandle));
      }
      if (auto hvacTemplateZonePTHP = std::dynamic_pointer_cast<HVACTemplateZonePTHP_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new HVACTemplateZonePTHP_Impl(*hvacTemplateZonePTHP, this, keepHandle));
      }
      if (auto hvacTemplateZoneWaterToAirHeatPump = std::dynamic_pointer_cast<HVACTemplateZoneWaterToAirHeatPump_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new HVACTemplateZoneWaterToAirHeatPump_Impl(*hvacTemplateZoneWaterToAirHeatPump, this, keepHandle));
      }
      if (auto hvacTemplateZoneVAV = std::dynamic_pointer_cast<HVACTemplateZoneVAV_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new HVACTemplateZoneVAV_Impl(*hvacTemplateZoneVAV, this, keepHandle));
      }
      if (auto hvacTemplateZoneVAVHeatAndCool = std::dynamic_pointer_cast<HVACTemplateZoneVAVHeatAndCool_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new HVACTemplateZoneVAVHeatAndCool_Impl(*hvacTemplateZoneVAVHeatAndCool, this, keepHandle));
      }
      if (auto hvacTemplateZoneVAVFanPowered = std::dynamic_pointer_cast<HVACTemplateZoneVAVFanPowered_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new HVACTemplateZoneVAVFanPowered_Impl(*hvacTemplateZoneVAVFanPowered, this, keepHandle));
      }
      if (auto hvacTemplateZoneVRF = std::dynamic_pointer_cast<HVACTemplateZoneVRF_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new HVACTemplateZoneVRF_Impl(*hvacTemplateZoneVRF, this, keepHandle));
      }
      if (auto hvacTemplateZoneUnitary = std::dynamic_pointer_cast<HVACTemplateZoneUnitary_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new HVACTemplateZoneUnitary_Impl(*hvacTemplateZoneUnitary, this, keepHandle));
      }
      if (auto hvacTemplateSystemUnitaryHeatPumpAirToAir =
            std::dynamic_pointer_cast<HVACTemplateSystemUnitaryHeatPumpAirToAir_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new HVACTemplateSystemUnitaryHeatPumpAirToAir_Impl(*hvacTemplateSystemUnitaryHeatPumpAirToAir, this, keepHandle));
      }
      if (auto hvacTemplateSystemUnitarySystem = std::dynamic_pointer_cast<HVACTemplateSystemUnitarySystem_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new HVACTemplateSystemUnitarySystem_Impl(*hvacTemplateSystemUnitarySystem, this, keepHandle));
      }
      if (auto hvacTemplateSystemUnitary = std::dynamic_pointer_cast<HVACTemplateSystemUnitary_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new HVACTemplateSystemUnitary_Impl(*hvacTemplateSystemUnitary, this, keepHandle));
      }
      if (auto hvacSystemRootFindingAlgorithm = std::dynamic_pointer_cast<HVACSystemRootFindingAlgorithm_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new HVACSystemRootFindingAlgorithm_Impl(*hvacSystemRootFindingAlgorithm, this, keepHandle));
      }
      if (auto insideSurfaceConvectionAlgorithm = std::dynamic_pointer_cast<InsideSurfaceConvectionAlgorithm_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new InsideSurfaceConvectionAlgorithm_Impl(*insideSurfaceConvectionAlgorithm, this, keepHandle));
      }
      if (auto outsideSurfaceConvectionAlgorithm = std::dynamic_pointer_cast<OutsideSurfaceConvectionAlgorithm_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new OutsideSurfaceConvectionAlgorithm_Impl(*outsideSurfaceConvectionAlgorithm, this, keepHandle));
      }
      if (auto surfaceConvectionAlgorithmInsideAdaptiveModelSelections =
            std::dynamic_pointer_cast<SurfaceConvectionAlgorithmInsideAdaptiveModelSelections_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new SurfaceConvectionAlgorithmInsideAdaptiveModelSelections_Impl(
          *surfaceConvectionAlgorithmInsideAdaptiveModelSelections, this, keepHandle));
      }
      if (auto surfaceConvectionAlgorithmOutsideAdaptiveModelSelections =
            std::dynamic_pointer_cast<SurfaceConvectionAlgorithmOutsideAdaptiveModelSelections_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new SurfaceConvectionAlgorithmOutsideAdaptiveModelSelections_Impl(
          *surfaceConvectionAlgorithmOutsideAdaptiveModelSelections, this, keepHandle));
      }
      if (auto surfaceConvectionAlgorithmInsideUserCurve =
            std::dynamic_pointer_cast<SurfaceConvectionAlgorithmInsideUserCurve_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new SurfaceConvectionAlgorithmInsideUserCurve_Impl(*surfaceConvectionAlgorithmInsideUserCurve, this, keepHandle));
      }
      if (auto surfaceConvectionAlgorithmOutsideUserCurve =
            std::dynamic_pointer_cast<SurfaceConvectionAlgorithmOutsideUserCurve_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new SurfaceConvectionAlgorithmOutsideUserCurve_Impl(*surfaceConvectionAlgorithmOutsideUserCurve, this, keepHandle));
      }
      if (auto surfacePropertyConvectionCoefficients = std::dynamic_pointer_cast<SurfacePropertyConvectionCoefficients_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new SurfacePropertyConvectionCoefficients_Impl(*surfacePropertyConvectionCoefficients, this, keepHandle));
      }
      if (auto surfacePropertyConvectionCoefficientsMultipleSurface =
            std::dynamic_pointer_cast<SurfacePropertyConvectionCoefficientsMultipleSurface_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new SurfacePropertyConvectionCoefficientsMultipleSurface_Impl(*surfacePropertyConvectionCoefficientsMultipleSurface, this, keepHandle));
      }
      if (auto surfacePropertyExposedFoundationPerimeter =
            std::dynamic_pointer_cast<SurfacePropertyExposedFoundationPerimeter_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new SurfacePropertyExposedFoundationPerimeter_Impl(*surfacePropertyExposedFoundationPerimeter, this, keepHandle));
      }
      if (auto surfacePropertyExteriorNaturalVentedCavity =
            std::dynamic_pointer_cast<SurfacePropertyExteriorNaturalVentedCavity_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new SurfacePropertyExteriorNaturalVentedCavity_Impl(*surfacePropertyExteriorNaturalVentedCavity, this, keepHandle));
      }
      if (auto surfacePropertyGroundSurfaces = std::dynamic_pointer_cast<SurfacePropertyGroundSurfaces_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new SurfacePropertyGroundSurfaces_Impl(*surfacePropertyGroundSurfaces, this, keepHandle));
      }
      if (auto surfacePropertyHeatBalanceSourceTerm = std::dynamic_pointer_cast<SurfacePropertyHeatBalanceSourceTerm_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new SurfacePropertyHeatBalanceSourceTerm_Impl(*surfacePropertyHeatBalanceSourceTerm, this, keepHandle));
      }
      if (auto surfacePropertyIncidentSolarMultiplier =
            std::dynamic_pointer_cast<SurfacePropertyIncidentSolarMultiplier_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new SurfacePropertyIncidentSolarMultiplier_Impl(*surfacePropertyIncidentSolarMultiplier, this, keepHandle));
      }
      if (auto surfacePropertyHeatTransferAlgorithm = std::dynamic_pointer_cast<SurfacePropertyHeatTransferAlgorithm_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new SurfacePropertyHeatTransferAlgorithm_Impl(*surfacePropertyHeatTransferAlgorithm, this, keepHandle));
      }
      if (auto surfacePropertyHeatTransferAlgorithmConstruction =
            std::dynamic_pointer_cast<SurfacePropertyHeatTransferAlgorithmConstruction_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new SurfacePropertyHeatTransferAlgorithmConstruction_Impl(*surfacePropertyHeatTransferAlgorithmConstruction, this, keepHandle));
      }
      if (auto surfacePropertyHeatTransferAlgorithmMultipleSurface =
            std::dynamic_pointer_cast<SurfacePropertyHeatTransferAlgorithmMultipleSurface_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new SurfacePropertyHeatTransferAlgorithmMultipleSurface_Impl(*surfacePropertyHeatTransferAlgorithmMultipleSurface, this, keepHandle));
      }
      if (auto surfacePropertyHeatTransferAlgorithmSurfaceList =
            std::dynamic_pointer_cast<SurfacePropertyHeatTransferAlgorithmSurfaceList_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new SurfacePropertyHeatTransferAlgorithmSurfaceList_Impl(*surfacePropertyHeatTransferAlgorithmSurfaceList, this, keepHandle));
      }
      if (auto surfacePropertySolarIncidentInside = std::dynamic_pointer_cast<SurfacePropertySolarIncidentInside_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new SurfacePropertySolarIncidentInside_Impl(*surfacePropertySolarIncidentInside, this, keepHandle));
      }
      if (auto surfacePropertySurroundingSurfaces = std::dynamic_pointer_cast<SurfacePropertySurroundingSurfaces_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new SurfacePropertySurroundingSurfaces_Impl(*surfacePropertySurroundingSurfaces, this, keepHandle));
      }
      if (auto surfacePropertyUnderwater = std::dynamic_pointer_cast<SurfacePropertyUnderwater_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new SurfacePropertyUnderwater_Impl(*surfacePropertyUnderwater, this, keepHandle));
      }
      if (auto surfacePropertyOtherSideCoefficients = std::dynamic_pointer_cast<SurfacePropertyOtherSideCoefficients_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new SurfacePropertyOtherSideCoefficients_Impl(*surfacePropertyOtherSideCoefficients, this, keepHandle));
      }
      if (auto surfacePropertyOtherSideConditionsModel =
            std::dynamic_pointer_cast<SurfacePropertyOtherSideConditionsModel_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new SurfacePropertyOtherSideConditionsModel_Impl(*surfacePropertyOtherSideConditionsModel, this, keepHandle));
      }
      if (auto globalGeometryRules = std::dynamic_pointer_cast<GlobalGeometryRules_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new GlobalGeometryRules_Impl(*globalGeometryRules, this, keepHandle));
      }
      if (auto daylightingDeviceLightWell = std::dynamic_pointer_cast<DaylightingDeviceLightWell_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new DaylightingDeviceLightWell_Impl(*daylightingDeviceLightWell, this, keepHandle));
      }
      if (auto daylightingDeviceShelf = std::dynamic_pointer_cast<DaylightingDeviceShelf_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new DaylightingDeviceShelf_Impl(*daylightingDeviceShelf, this, keepHandle));
      }
      if (auto daylightingDeviceTubular = std::dynamic_pointer_cast<DaylightingDeviceTubular_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new DaylightingDeviceTubular_Impl(*daylightingDeviceTubular, this, keepHandle));
      }
      if (auto daylightingDELightComplexFenestration = std::dynamic_pointer_cast<DaylightingDELightComplexFenestration_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new DaylightingDELightComplexFenestration_Impl(*daylightingDELightComplexFenestration, this, keepHandle));
      }
      if (auto dehumidifierDesiccantNoFans = std::dynamic_pointer_cast<DehumidifierDesiccantNoFans_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new DehumidifierDesiccantNoFans_Impl(*dehumidifierDesiccantNoFans, this, keepHandle));
      }
      if (auto dehumidifierDesiccantSystem = std::dynamic_pointer_cast<DehumidifierDesiccantSystem_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new DehumidifierDesiccantSystem_Impl(*dehumidifierDesiccantSystem, this, keepHandle));
      }
      if (auto curveBicubic = std::dynamic_pointer_cast<CurveBicubic_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new CurveBicubic_Impl(*curveBicubic, this, keepHandle));
      }
      if (auto curveCubic = std::dynamic_pointer_cast<CurveCubic_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new CurveCubic_Impl(*curveCubic, this, keepHandle));
      }
      if (auto curveBiquadratic = std::dynamic_pointer_cast<CurveBiquadratic_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new CurveBiquadratic_Impl(*curveBiquadratic, this, keepHandle));
      }
      if (auto curveExponent = std::dynamic_pointer_cast<CurveExponent_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new CurveExponent_Impl(*curveExponent, this, keepHandle));
      }
      if (auto curveDoubleExponentialDecay = std::dynamic_pointer_cast<CurveDoubleExponentialDecay_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new CurveDoubleExponentialDecay_Impl(*curveDoubleExponentialDecay, this, keepHandle));
      }
      if (auto curveExponentialDecay = std::dynamic_pointer_cast<CurveExponentialDecay_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new CurveExponentialDecay_Impl(*curveExponentialDecay, this, keepHandle));
      }
      if (auto curveExponentialSkewNormal = std::dynamic_pointer_cast<CurveExponentialSkewNormal_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new CurveExponentialSkewNormal_Impl(*curveExponentialSkewNormal, this, keepHandle));
      }
      if (auto curveFanPressureRise = std::dynamic_pointer_cast<CurveFanPressureRise_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new CurveFanPressureRise_Impl(*curveFanPressureRise, this, keepHandle));
      }
      if (auto curveFunctionalPressureDrop = std::dynamic_pointer_cast<CurveFunctionalPressureDrop_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new CurveFunctionalPressureDrop_Impl(*curveFunctionalPressureDrop, this, keepHandle));
      }
      if (auto curveLinear = std::dynamic_pointer_cast<CurveLinear_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new CurveLinear_Impl(*curveLinear, this, keepHandle));
      }
      if (auto curveQuadratic = std::dynamic_pointer_cast<CurveQuadratic_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new CurveQuadratic_Impl(*curveQuadratic, this, keepHandle));
      }
      if (auto curveQuartic = std::dynamic_pointer_cast<CurveQuartic_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new CurveQuartic_Impl(*curveQuartic, this, keepHandle));
      }
      if (auto curveQuadLinear = std::dynamic_pointer_cast<CurveQuadLinear_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new CurveQuadLinear_Impl(*curveQuadLinear, this, keepHandle));
      }
      if (auto curveQuintLinear = std::dynamic_pointer_cast<CurveQuintLinear_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new CurveQuintLinear_Impl(*curveQuintLinear, this, keepHandle));
      }
      if (auto curveRectangularHyperbola1 = std::dynamic_pointer_cast<CurveRectangularHyperbola1_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new CurveRectangularHyperbola1_Impl(*curveRectangularHyperbola1, this, keepHandle));
      }
      if (auto curveRectangularHyperbola2 = std::dynamic_pointer_cast<CurveRectangularHyperbola2_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new CurveRectangularHyperbola2_Impl(*curveRectangularHyperbola2, this, keepHandle));
      }
      if (auto curveSigmoid = std::dynamic_pointer_cast<CurveSigmoid_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new CurveSigmoid_Impl(*curveSigmoid, this, keepHandle));
      }
      if (auto curveTriquadratic = std::dynamic_pointer_cast<CurveTriquadratic_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new CurveTriquadratic_Impl(*curveTriquadratic, this, keepHandle));
      }
      if (auto curveQuadraticLinear = std::dynamic_pointer_cast<CurveQuadraticLinear_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new CurveQuadraticLinear_Impl(*curveQuadraticLinear, this, keepHandle));
      }
      if (auto curveCubicLinear = std::dynamic_pointer_cast<CurveCubicLinear_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new CurveCubicLinear_Impl(*curveCubicLinear, this, keepHandle));
      }
      if (auto curveChillerPartLoadWithLift = std::dynamic_pointer_cast<CurveChillerPartLoadWithLift_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new CurveChillerPartLoadWithLift_Impl(*curveChillerPartLoadWithLift, this, keepHandle));
      }
      if (auto constructionWindowDataFile = std::dynamic_pointer_cast<ConstructionWindowDataFile_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new ConstructionWindowDataFile_Impl(*constructionWindowDataFile, this, keepHandle));
      }
      if (auto constructionWindowEquivalentLayer = std::dynamic_pointer_cast<ConstructionWindowEquivalentLayer_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new ConstructionWindowEquivalentLayer_Impl(*constructionWindowEquivalentLayer, this, keepHandle));
      }
      if (auto roomAirTemperaturePatternConstantGradient =
            std::dynamic_pointer_cast<RoomAirTemperaturePatternConstantGradient_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new RoomAirTemperaturePatternConstantGradient_Impl(*roomAirTemperaturePatternConstantGradient, this, keepHandle));
      }
      if (auto roomAirTemperaturePatternNondimensionalHeight =
            std::dynamic_pointer_cast<RoomAirTemperaturePatternNondimensionalHeight_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new RoomAirTemperaturePatternNondimensionalHeight_Impl(*roomAirTemperaturePatternNondimensionalHeight, this, keepHandle));
      }
      if (auto roomAirTemperaturePatternSurfaceMapping =
            std::dynamic_pointer_cast<RoomAirTemperaturePatternSurfaceMapping_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new RoomAirTemperaturePatternSurfaceMapping_Impl(*roomAirTemperaturePatternSurfaceMapping, this, keepHandle));
      }
      if (auto roomAirTemperaturePatternTwoGradient = std::dynamic_pointer_cast<RoomAirTemperaturePatternTwoGradient_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new RoomAirTemperaturePatternTwoGradient_Impl(*roomAirTemperaturePatternTwoGradient, this, keepHandle));
      }
      if (auto roomAirTemperaturePatternUserDefined = std::dynamic_pointer_cast<RoomAirTemperaturePatternUserDefined_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new RoomAirTemperaturePatternUserDefined_Impl(*roomAirTemperaturePatternUserDefined, this, keepHandle));
      }
      if (auto roomAirModelType = std::dynamic_pointer_cast<RoomAirModelType_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new RoomAirModelType_Impl(*roomAirModelType, this, keepHandle));
      }
      if (auto roomAirSettingsAirflowNetwork = std::dynamic_pointer_cast<RoomAirSettingsAirflowNetwork_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new RoomAirSettingsAirflowNetwork_Impl(*roomAirSettingsAirflowNetwork, this, keepHandle));
      }
      if (auto roomAirSettingsCrossVentilation = std::dynamic_pointer_cast<RoomAirSettingsCrossVentilation_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new RoomAirSettingsCrossVentilation_Impl(*roomAirSettingsCrossVentilation, this, keepHandle));
      }
      if (auto roomAirSettingsOneNodeDisplacementVentilation =
            std::dynamic_pointer_cast<RoomAirSettingsOneNodeDisplacementVentilation_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new RoomAirSettingsOneNodeDisplacementVentilation_Impl(*roomAirSettingsOneNodeDisplacementVentilation, this, keepHandle));
      }
      if (auto roomAirSettingsThreeNodeDisplacementVentilation =
            std::dynamic_pointer_cast<RoomAirSettingsThreeNodeDisplacementVentilation_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new RoomAirSettingsThreeNodeDisplacementVentilation_Impl(*roomAirSettingsThreeNodeDisplacementVentilation, this, keepHandle));
      }
      if (auto roomAirSettingsUnderFloorAirDistributionExterior =
            std::dynamic_pointer_cast<RoomAirSettingsUnderFloorAirDistributionExterior_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new RoomAirSettingsUnderFloorAirDistributionExterior_Impl(*roomAirSettingsUnderFloorAirDistributionExterior, this, keepHandle));
      }
      if (auto roomAirSettingsUnderFloorAirDistributionInterior =
            std::dynamic_pointer_cast<RoomAirSettingsUnderFloorAirDistributionInterior_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new RoomAirSettingsUnderFloorAirDistributionInterior_Impl(*roomAirSettingsUnderFloorAirDistributionInterior, this, keepHandle));
      }
      if (auto roomAirNode = std::dynamic_pointer_cast<RoomAirNode_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new RoomAirNode_Impl(*roomAirNode, this, keepHandle));
      }
      if (auto roomAirNodeAirflowNetwork = std::dynamic_pointer_cast<RoomAirNodeAirflowNetwork_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new RoomAirNodeAirflowNetwork_Impl(*roomAirNodeAirflowNetwork, this, keepHandle));
      }
      if (auto roomAirNodeAirflowNetworkAdjacentSurfaceList =
            std::dynamic_pointer_cast<RoomAirNodeAirflowNetworkAdjacentSurfaceList_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new RoomAirNodeAirflowNetworkAdjacentSurfaceList_Impl(*roomAirNodeAirflowNetworkAdjacentSurfaceList, this, keepHandle));
      }
      if (auto roomAirNodeAirflowNetworkHVACEquipment =
            std::dynamic_pointer_cast<RoomAirNodeAirflowNetworkHVACEquipment_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new RoomAirNodeAirflowNetworkHVACEquipment_Impl(*roomAirNodeAirflowNetworkHVACEquipment, this, keepHandle));
      }
      if (auto roomAirNodeAirflowNetworkInternalGains =
            std::dynamic_pointer_cast<RoomAirNodeAirflowNetworkInternalGains_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new RoomAirNodeAirflowNetworkInternalGains_Impl(*roomAirNodeAirflowNetworkInternalGains, this, keepHandle));
      }
      if (auto airflowNetworkDistributionComponentCoil =
            std::dynamic_pointer_cast<AirflowNetworkDistributionComponentCoil_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new AirflowNetworkDistributionComponentCoil_Impl(*airflowNetworkDistributionComponentCoil, this, keepHandle));
      }
      if (auto airflowNetworkDistributionComponentConstantPressureDrop =
            std::dynamic_pointer_cast<AirflowNetworkDistributionComponentConstantPressureDrop_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new AirflowNetworkDistributionComponentConstantPressureDrop_Impl(
          *airflowNetworkDistributionComponentConstantPressureDrop, this, keepHandle));
      }
      if (auto ceilingAdiabatic = std::dynamic_pointer_cast<CeilingAdiabatic_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new CeilingAdiabatic_Impl(*ceilingAdiabatic, this, keepHandle));
      }
      if (auto ceilingInterzone = std::dynamic_pointer_cast<CeilingInterzone_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new CeilingInterzone_Impl(*ceilingInterzone, this, keepHandle));
      }
      if (auto roof = std::dynamic_pointer_cast<Roof_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new Roof_Impl(*roof, this, keepHandle));
      }
      if (auto roofIrrigation = std::dynamic_pointer_cast<RoofIrrigation_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new RoofIrrigation_Impl(*roofIrrigation, this, keepHandle));
      }
      if (auto roofCeilingDetailed = std::dynamic_pointer_cast<RoofCeilingDetailed_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new RoofCeilingDetailed_Impl(*roofCeilingDetailed, this, keepHandle));
      }
      if (auto wallAdiabatic = std::dynamic_pointer_cast<WallAdiabatic_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new WallAdiabatic_Impl(*wallAdiabatic, this, keepHandle));
      }
      if (auto wallDetailed = std::dynamic_pointer_cast<WallDetailed_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new WallDetailed_Impl(*wallDetailed, this, keepHandle));
      }
      if (auto wallExterior = std::dynamic_pointer_cast<WallExterior_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new WallExterior_Impl(*wallExterior, this, keepHandle));
      }
      if (auto wallInterzone = std::dynamic_pointer_cast<WallInterzone_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new WallInterzone_Impl(*wallInterzone, this, keepHandle));
      }
      if (auto wallUnderground = std::dynamic_pointer_cast<WallUnderground_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new WallUnderground_Impl(*wallUnderground, this, keepHandle));
      }
      if (auto door = std::dynamic_pointer_cast<Door_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new Door_Impl(*door, this, keepHandle));
      }
      if (auto doorInterzone = std::dynamic_pointer_cast<DoorInterzone_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new DoorInterzone_Impl(*doorInterzone, this, keepHandle));
      }
      if (auto glazedDoor = std::dynamic_pointer_cast<GlazedDoor_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new GlazedDoor_Impl(*glazedDoor, this, keepHandle));
      }
      if (auto glazedDoorInterzone = std::dynamic_pointer_cast<GlazedDoorInterzone_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new GlazedDoorInterzone_Impl(*glazedDoorInterzone, this, keepHandle));
      }
      if (auto windowInterzone = std::dynamic_pointer_cast<WindowInterzone_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new WindowInterzone_Impl(*windowInterzone, this, keepHandle));
      }
      if (auto windowGapDeflectionState = std::dynamic_pointer_cast<WindowGapDeflectionState_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new WindowGapDeflectionState_Impl(*windowGapDeflectionState, this, keepHandle));
      }
      if (auto windowGapSupportPillar = std::dynamic_pointer_cast<WindowGapSupportPillar_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new WindowGapSupportPillar_Impl(*windowGapSupportPillar, this, keepHandle));
      }
      if (auto windowPropertyAirflowControl = std::dynamic_pointer_cast<WindowPropertyAirflowControl_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new WindowPropertyAirflowControl_Impl(*windowPropertyAirflowControl, this, keepHandle));
      }
      if (auto windowPropertyStormWindow = std::dynamic_pointer_cast<WindowPropertyStormWindow_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new WindowPropertyStormWindow_Impl(*windowPropertyStormWindow, this, keepHandle));
      }
      if (auto windowThermalModelParams = std::dynamic_pointer_cast<WindowThermalModelParams_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new WindowThermalModelParams_Impl(*windowThermalModelParams, this, keepHandle));
      }
      if (auto windowsCalculationEngine = std::dynamic_pointer_cast<WindowsCalculationEngine_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new WindowsCalculationEngine_Impl(*windowsCalculationEngine, this, keepHandle));
      }
      if (auto windowPropertyFrameAndDivider = std::dynamic_pointer_cast<WindowPropertyFrameAndDivider_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new WindowPropertyFrameAndDivider_Impl(*windowPropertyFrameAndDivider, this, keepHandle));
      }
      if (auto shadingControl = std::dynamic_pointer_cast<ShadingControl_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new ShadingControl_Impl(*shadingControl, this, keepHandle));
      }
      if (auto airflowNetworkDistributionComponentDuct =
            std::dynamic_pointer_cast<AirflowNetworkDistributionComponentDuct_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new AirflowNetworkDistributionComponentDuct_Impl(*airflowNetworkDistributionComponentDuct, this, keepHandle));
      }
      if (auto airflowNetworkDistributionDuctSizing = std::dynamic_pointer_cast<AirflowNetworkDistributionDuctSizing_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new AirflowNetworkDistributionDuctSizing_Impl(*airflowNetworkDistributionDuctSizing, this, keepHandle));
      }
      if (auto airflowNetworkDistributionDuctViewFactors =
            std::dynamic_pointer_cast<AirflowNetworkDistributionDuctViewFactors_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new AirflowNetworkDistributionDuctViewFactors_Impl(*airflowNetworkDistributionDuctViewFactors, this, keepHandle));
      }
      if (auto airflowNetworkDistributionLinkage = std::dynamic_pointer_cast<AirflowNetworkDistributionLinkage_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new AirflowNetworkDistributionLinkage_Impl(*airflowNetworkDistributionLinkage, this, keepHandle));
      }
      if (auto airflowNetworkDistributionNode = std::dynamic_pointer_cast<AirflowNetworkDistributionNode_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new AirflowNetworkDistributionNode_Impl(*airflowNetworkDistributionNode, this, keepHandle));
      }
      if (auto airflowNetworkIntraZoneNode = std::dynamic_pointer_cast<AirflowNetworkIntraZoneNode_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new AirflowNetworkIntraZoneNode_Impl(*airflowNetworkIntraZoneNode, this, keepHandle));
      }
      if (auto airflowNetworkIntraZoneLinkage = std::dynamic_pointer_cast<AirflowNetworkIntraZoneLinkage_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new AirflowNetworkIntraZoneLinkage_Impl(*airflowNetworkIntraZoneLinkage, this, keepHandle));
      }
      if (auto airflowNetworkMultiZoneExternalNode = std::dynamic_pointer_cast<AirflowNetworkMultiZoneExternalNode_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new AirflowNetworkMultiZoneExternalNode_Impl(*airflowNetworkMultiZoneExternalNode, this, keepHandle));
      }
      if (auto airflowNetworkMultiZoneZone = std::dynamic_pointer_cast<AirflowNetworkMultiZoneZone_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new AirflowNetworkMultiZoneZone_Impl(*airflowNetworkMultiZoneZone, this, keepHandle));
      }
      if (auto airflowNetworkMultiZoneSpecifiedFlowRate =
            std::dynamic_pointer_cast<AirflowNetworkMultiZoneSpecifiedFlowRate_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new AirflowNetworkMultiZoneSpecifiedFlowRate_Impl(*airflowNetworkMultiZoneSpecifiedFlowRate, this, keepHandle));
      }
      if (auto airflowNetworkMultiZoneReferenceCrackConditions =
            std::dynamic_pointer_cast<AirflowNetworkMultiZoneReferenceCrackConditions_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new AirflowNetworkMultiZoneReferenceCrackConditions_Impl(*airflowNetworkMultiZoneReferenceCrackConditions, this, keepHandle));
      }
      if (auto airflowNetworkMultiZoneWindPressureCoefficientArray =
            std::dynamic_pointer_cast<AirflowNetworkMultiZoneWindPressureCoefficientArray_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new AirflowNetworkMultiZoneWindPressureCoefficientArray_Impl(*airflowNetworkMultiZoneWindPressureCoefficientArray, this, keepHandle));
      }
      if (auto airflowNetworkMultiZoneWindPressureCoefficientValues =
            std::dynamic_pointer_cast<AirflowNetworkMultiZoneWindPressureCoefficientValues_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new AirflowNetworkMultiZoneWindPressureCoefficientValues_Impl(*airflowNetworkMultiZoneWindPressureCoefficientValues, this, keepHandle));
      }
      if (auto airflowNetworkMultiZoneSurface = std::dynamic_pointer_cast<AirflowNetworkMultiZoneSurface_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new AirflowNetworkMultiZoneSurface_Impl(*airflowNetworkMultiZoneSurface, this, keepHandle));
      }
      if (auto airflowNetworkMultiZoneSurfaceCrack = std::dynamic_pointer_cast<AirflowNetworkMultiZoneSurfaceCrack_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new AirflowNetworkMultiZoneSurfaceCrack_Impl(*airflowNetworkMultiZoneSurfaceCrack, this, keepHandle));
      }
      if (auto airflowNetworkMultiZoneSurfaceEffectiveLeakageArea =
            std::dynamic_pointer_cast<AirflowNetworkMultiZoneSurfaceEffectiveLeakageArea_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new AirflowNetworkMultiZoneSurfaceEffectiveLeakageArea_Impl(*airflowNetworkMultiZoneSurfaceEffectiveLeakageArea, this, keepHandle));
      }
      if (auto airflowNetworkMultiZoneComponentDetailedOpening =
            std::dynamic_pointer_cast<AirflowNetworkMultiZoneComponentDetailedOpening_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new AirflowNetworkMultiZoneComponentDetailedOpening_Impl(*airflowNetworkMultiZoneComponentDetailedOpening, this, keepHandle));
      }
      if (auto airflowNetworkMultiZoneComponentHorizontalOpening =
            std::dynamic_pointer_cast<AirflowNetworkMultiZoneComponentHorizontalOpening_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new AirflowNetworkMultiZoneComponentHorizontalOpening_Impl(*airflowNetworkMultiZoneComponentHorizontalOpening, this, keepHandle));
      }
      if (auto airflowNetworkMultiZoneComponentSimpleOpening =
            std::dynamic_pointer_cast<AirflowNetworkMultiZoneComponentSimpleOpening_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new AirflowNetworkMultiZoneComponentSimpleOpening_Impl(*airflowNetworkMultiZoneComponentSimpleOpening, this, keepHandle));
      }
      if (auto airflowNetworkMultiZoneComponentZoneExhaustFan =
            std::dynamic_pointer_cast<AirflowNetworkMultiZoneComponentZoneExhaustFan_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new AirflowNetworkMultiZoneComponentZoneExhaustFan_Impl(*airflowNetworkMultiZoneComponentZoneExhaustFan, this, keepHandle));
      }
      if (auto airflowNetworkOccupantVentilationControl =
            std::dynamic_pointer_cast<AirflowNetworkOccupantVentilationControl_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new AirflowNetworkOccupantVentilationControl_Impl(*airflowNetworkOccupantVentilationControl, this, keepHandle));
      }
      if (auto airflowNetworkSimulationControl = std::dynamic_pointer_cast<AirflowNetworkSimulationControl_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new AirflowNetworkSimulationControl_Impl(*airflowNetworkSimulationControl, this, keepHandle));
      }
      if (auto simulationControl = std::dynamic_pointer_cast<SimulationControl_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new SimulationControl_Impl(*simulationControl, this, keepHandle));
      }
      if (auto airflowNetworkZoneControlPressureController =
            std::dynamic_pointer_cast<AirflowNetworkZoneControlPressureController_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new AirflowNetworkZoneControlPressureController_Impl(*airflowNetworkZoneControlPressureController, this, keepHandle));
      }
      if (auto airflowNetworkDistributionComponentFan =
            std::dynamic_pointer_cast<AirflowNetworkDistributionComponentFan_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new AirflowNetworkDistributionComponentFan_Impl(*airflowNetworkDistributionComponentFan, this, keepHandle));
      }
      if (auto airflowNetworkDistributionComponentHeatExchanger =
            std::dynamic_pointer_cast<AirflowNetworkDistributionComponentHeatExchanger_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new AirflowNetworkDistributionComponentHeatExchanger_Impl(*airflowNetworkDistributionComponentHeatExchanger, this, keepHandle));
      }
      if (auto airflowNetworkDistributionComponentLeak =
            std::dynamic_pointer_cast<AirflowNetworkDistributionComponentLeak_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new AirflowNetworkDistributionComponentLeak_Impl(*airflowNetworkDistributionComponentLeak, this, keepHandle));
      }
      if (auto airflowNetworkDistributionComponentLeakageRatio =
            std::dynamic_pointer_cast<AirflowNetworkDistributionComponentLeakageRatio_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new AirflowNetworkDistributionComponentLeakageRatio_Impl(*airflowNetworkDistributionComponentLeakageRatio, this, keepHandle));
      }
      if (auto airflowNetworkDistributionComponentOutdoorAirFlow =
            std::dynamic_pointer_cast<AirflowNetworkDistributionComponentOutdoorAirFlow_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new AirflowNetworkDistributionComponentOutdoorAirFlow_Impl(*airflowNetworkDistributionComponentOutdoorAirFlow, this, keepHandle));
      }
      if (auto airflowNetworkDistributionComponentReliefAirFlow =
            std::dynamic_pointer_cast<AirflowNetworkDistributionComponentReliefAirFlow_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new AirflowNetworkDistributionComponentReliefAirFlow_Impl(*airflowNetworkDistributionComponentReliefAirFlow, this, keepHandle));
      }
      if (auto airflowNetworkDistributionComponentTerminalUnit =
            std::dynamic_pointer_cast<AirflowNetworkDistributionComponentTerminalUnit_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new AirflowNetworkDistributionComponentTerminalUnit_Impl(*airflowNetworkDistributionComponentTerminalUnit, this, keepHandle));
      }
      if (auto doas = std::dynamic_pointer_cast<AirLoopHVACDedicatedOutdoorAirSystem_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new AirLoopHVACDedicatedOutdoorAirSystem_Impl(*doas, this, keepHandle));
      }
      if (auto changeover = std::dynamic_pointer_cast<PlantEquipmentOperationChillerHeaterChangeover_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new PlantEquipmentOperationChillerHeaterChangeover_Impl(*changeover, this, keepHandle));
      }
      if (auto componentSetpoint = std::dynamic_pointer_cast<PlantEquipmentOperationComponentSetpoint_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new PlantEquipmentOperationComponentSetpoint_Impl(*componentSetpoint, this, keepHandle));
      }
      if (auto thermalEnergyStorage = std::dynamic_pointer_cast<PlantEquipmentOperationThermalEnergyStorage_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new PlantEquipmentOperationThermalEnergyStorage_Impl(*thermalEnergyStorage, this, keepHandle));
      }
      if (auto schemes = std::dynamic_pointer_cast<PlantEquipmentOperationSchemes_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new PlantEquipmentOperationSchemes_Impl(*schemes, this, keepHandle));
      }
      if (auto uncontrolled = std::dynamic_pointer_cast<PlantEquipmentOperationUncontrolled_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new PlantEquipmentOperationUncontrolled_Impl(*uncontrolled, this, keepHandle));
      }
      if (auto userDefined = std::dynamic_pointer_cast<PlantEquipmentOperationUserDefined_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new PlantEquipmentOperationUserDefined_Impl(*userDefined, this, keepHandle));
      }
      if (auto coolingLoad = std::dynamic_pointer_cast<PlantEquipmentOperationCoolingLoad_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new PlantEquipmentOperationCoolingLoad_Impl(*coolingLoad, this, keepHandle));
      }
      if (auto heatingLoad = std::dynamic_pointer_cast<PlantEquipmentOperationHeatingLoad_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new PlantEquipmentOperationHeatingLoad_Impl(*heatingLoad, this, keepHandle));
      }
      if (auto outdoorDewpoint = std::dynamic_pointer_cast<PlantEquipmentOperationOutdoorDewpoint_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new PlantEquipmentOperationOutdoorDewpoint_Impl(*outdoorDewpoint, this, keepHandle));
      }
      if (auto outdoorDewpointDifference = std::dynamic_pointer_cast<PlantEquipmentOperationOutdoorDewpointDifference_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new PlantEquipmentOperationOutdoorDewpointDifference_Impl(*outdoorDewpointDifference, this, keepHandle));
      }
      if (auto outdoorDryBulbDifference = std::dynamic_pointer_cast<PlantEquipmentOperationOutdoorDryBulbDifference_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new PlantEquipmentOperationOutdoorDryBulbDifference_Impl(*outdoorDryBulbDifference, this, keepHandle));
      }
      if (auto outdoorDryBulb = std::dynamic_pointer_cast<PlantEquipmentOperationOutdoorDryBulb_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new PlantEquipmentOperationOutdoorDryBulb_Impl(*outdoorDryBulb, this, keepHandle));
      }
      if (auto outdoorRelativeHumidity = std::dynamic_pointer_cast<PlantEquipmentOperationOutdoorRelativeHumidity_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new PlantEquipmentOperationOutdoorRelativeHumidity_Impl(*outdoorRelativeHumidity, this, keepHandle));
      }
      if (auto outdoorWetBulb = std::dynamic_pointer_cast<PlantEquipmentOperationOutdoorWetBulb_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new PlantEquipmentOperationOutdoorWetBulb_Impl(*outdoorWetBulb, this, keepHandle));
      }
      if (auto outdoorWetBulbDifference = std::dynamic_pointer_cast<PlantEquipmentOperationOutdoorWetBulbDifference_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new PlantEquipmentOperationOutdoorWetBulbDifference_Impl(*outdoorWetBulbDifference, this, keepHandle));
      }
      if (auto zoneAirBalance = std::dynamic_pointer_cast<ZoneAirBalanceOutdoorAir_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new ZoneAirBalanceOutdoorAir_Impl(*zoneAirBalance, this, keepHandle));
      }
      if (auto zoneAirContaminantBalance = std::dynamic_pointer_cast<ZoneAirContaminantBalance_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new ZoneAirContaminantBalance_Impl(*zoneAirContaminantBalance, this, keepHandle));
      }
      if (auto zoneAirHeatBalanceAlgorithm = std::dynamic_pointer_cast<ZoneAirHeatBalanceAlgorithm_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new ZoneAirHeatBalanceAlgorithm_Impl(*zoneAirHeatBalanceAlgorithm, this, keepHandle));
      }
      if (auto zoneAirMassFlowConservation = std::dynamic_pointer_cast<ZoneAirMassFlowConservation_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new ZoneAirMassFlowConservation_Impl(*zoneAirMassFlowConservation, this, keepHandle));
      }
      if (auto zoneCoolTowerShower = std::dynamic_pointer_cast<ZoneCoolTowerShower_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new ZoneCoolTowerShower_Impl(*zoneCoolTowerShower, this, keepHandle));
      }
      if (auto zoneCrossMixing = std::dynamic_pointer_cast<ZoneCrossMixing_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new ZoneCrossMixing_Impl(*zoneCrossMixing, this, keepHandle));
      }
      if (auto zoneMixing = std::dynamic_pointer_cast<ZoneMixing_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new ZoneMixing_Impl(*zoneMixing, this, keepHandle));
      }
      if (auto zoneRefrigerationDoorMixing = std::dynamic_pointer_cast<ZoneRefrigerationDoorMixing_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new ZoneRefrigerationDoorMixing_Impl(*zoneRefrigerationDoorMixing, this, keepHandle));
      }
      if (auto zoneThermalChimney = std::dynamic_pointer_cast<ZoneThermalChimney_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new ZoneThermalChimney_Impl(*zoneThermalChimney, this, keepHandle));
      }
      if (auto zonePropertyLocalEnvironment = std::dynamic_pointer_cast<ZonePropertyLocalEnvironment_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new ZonePropertyLocalEnvironment_Impl(*zonePropertyLocalEnvironment, this, keepHandle));
      }
      if (auto zonePropertyUserViewFactorsBySurfaceName =
            std::dynamic_pointer_cast<ZonePropertyUserViewFactorsBySurfaceName_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new ZonePropertyUserViewFactorsBySurfaceName_Impl(*zonePropertyUserViewFactorsBySurfaceName, this, keepHandle));
      }
      if (auto spaceInfiltrationDesignFlowRate = std::dynamic_pointer_cast<SpaceInfiltrationDesignFlowRate_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new SpaceInfiltrationDesignFlowRate_Impl(*spaceInfiltrationDesignFlowRate, this, keepHandle));
      }
      if (auto spaceInfiltrationFlowCoefficient = std::dynamic_pointer_cast<SpaceInfiltrationFlowCoefficient_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new SpaceInfiltrationFlowCoefficient_Impl(*spaceInfiltrationFlowCoefficient, this, keepHandle));
      }
      if (auto spaceInfiltrationEffectiveLeakageArea = std::dynamic_pointer_cast<SpaceInfiltrationEffectiveLeakageArea_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new SpaceInfiltrationEffectiveLeakageArea_Impl(*spaceInfiltrationEffectiveLeakageArea, this, keepHandle));
      }
      if (auto zoneEarthtube = std::dynamic_pointer_cast<ZoneEarthtube_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new ZoneEarthtube_Impl(*zoneEarthtube, this, keepHandle));
      }
      if (auto zoneEarthtubeParameters = std::dynamic_pointer_cast<ZoneEarthtubeParameters_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new ZoneEarthtubeParameters_Impl(*zoneEarthtubeParameters, this, keepHandle));
      }
      if (auto zoneGroup = std::dynamic_pointer_cast<ZoneGroup_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new ZoneGroup_Impl(*zoneGroup, this, keepHandle));
      }
      if (auto zoneControlContaminantController = std::dynamic_pointer_cast<ZoneControlContaminantController_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new ZoneControlContaminantController_Impl(*zoneControlContaminantController, this, keepHandle));
      }
      if (auto zoneControlHumidistat = std::dynamic_pointer_cast<ZoneControlHumidistat_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new ZoneControlHumidistat_Impl(*zoneControlHumidistat, this, keepHandle));
      }
      if (auto zoneControlThermostatOperativeTemperature =
            std::dynamic_pointer_cast<ZoneControlThermostatOperativeTemperature_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new ZoneControlThermostatOperativeTemperature_Impl(*zoneControlThermostatOperativeTemperature, this, keepHandle));
      }
      if (auto zoneControlThermostatTemperatureAndHumidity =
            std::dynamic_pointer_cast<ZoneControlThermostatTemperatureAndHumidity_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new ZoneControlThermostatTemperatureAndHumidity_Impl(*zoneControlThermostatTemperatureAndHumidity, this, keepHandle));
      }
      if (auto zoneControlThermostatThermalComfort = std::dynamic_pointer_cast<ZoneControlThermostatThermalComfort_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new ZoneControlThermostatThermalComfort_Impl(*zoneControlThermostatThermalComfort, this, keepHandle));
      }
      if (auto zoneControlThermostatStagedDualSetpoint =
            std::dynamic_pointer_cast<ZoneControlThermostatStagedDualSetpoint_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new ZoneControlThermostatStagedDualSetpoint_Impl(*zoneControlThermostatStagedDualSetpoint, this, keepHandle));
      }
      if (auto zoneContaminantSourceAndSinkCarbonDioxide =
            std::dynamic_pointer_cast<ZoneContaminantSourceAndSinkCarbonDioxide_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new ZoneContaminantSourceAndSinkCarbonDioxide_Impl(*zoneContaminantSourceAndSinkCarbonDioxide, this, keepHandle));
      }
      if (auto zoneContaminantSourceAndSinkGenericConstant =
            std::dynamic_pointer_cast<ZoneContaminantSourceAndSinkGenericConstant_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new ZoneContaminantSourceAndSinkGenericConstant_Impl(*zoneContaminantSourceAndSinkGenericConstant, this, keepHandle));
      }
      if (auto zoneContaminantSourceAndSinkGenericCutoffModel =
            std::dynamic_pointer_cast<ZoneContaminantSourceAndSinkGenericCutoffModel_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new ZoneContaminantSourceAndSinkGenericCutoffModel_Impl(*zoneContaminantSourceAndSinkGenericCutoffModel, this, keepHandle));
      }
      if (auto zoneContaminantSourceAndSinkGenericDecaySource =
            std::dynamic_pointer_cast<ZoneContaminantSourceAndSinkGenericDecaySource_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new ZoneContaminantSourceAndSinkGenericDecaySource_Impl(*zoneContaminantSourceAndSinkGenericDecaySource, this, keepHandle));
      }
      if (auto zoneContaminantSourceAndSinkGenericDepositionRateSink =
            std::dynamic_pointer_cast<ZoneContaminantSourceAndSinkGenericDepositionRateSink_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new ZoneContaminantSourceAndSinkGenericDepositionRateSink_Impl(*zoneContaminantSourceAndSinkGenericDepositionRateSink, this, keepHandle));
      }
      if (auto zoneBaseboardOutdoorTemperatureControlled =
            std::dynamic_pointer_cast<ZoneBaseboardOutdoorTemperatureControlled_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new ZoneBaseboardOutdoorTemperatureControlled_Impl(*zoneBaseboardOutdoorTemperatureControlled, this, keepHandle));
      }
      if (auto zoneCapacitanceMultiplierResearchSpecial =
            std::dynamic_pointer_cast<ZoneCapacitanceMultiplierResearchSpecial_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new ZoneCapacitanceMultiplierResearchSpecial_Impl(*zoneCapacitanceMultiplierResearchSpecial, this, keepHandle));
      }
      if (auto block = std::dynamic_pointer_cast<UtilityCostChargeBlock_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new UtilityCostChargeBlock_Impl(*block, this, keepHandle));
      }
      if (auto simple = std::dynamic_pointer_cast<UtilityCostChargeSimple_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new UtilityCostChargeSimple_Impl(*simple, this, keepHandle));
      }
      if (auto computation = std::dynamic_pointer_cast<UtilityCostComputation_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new UtilityCostComputation_Impl(*computation, this, keepHandle));
      }
      if (auto qualify = std::dynamic_pointer_cast<UtilityCostQualify_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new UtilityCostQualify_Impl(*qualify, this, keepHandle));
      }
      if (auto ratchet = std::dynamic_pointer_cast<UtilityCostRatchet_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new UtilityCostRatchet_Impl(*ratchet, this, keepHandle));
      }
      if (auto tariff = std::dynamic_pointer_cast<UtilityCostTariff_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new UtilityCostTariff_Impl(*tariff, this, keepHandle));
      }
      if (auto variable = std::dynamic_pointer_cast<UtilityCostVariable_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new UtilityCostVariable_Impl(*variable, this, keepHandle));
      }
      if (auto demandManagerElectricEquipment = std::dynamic_pointer_cast<DemandManagerElectricEquipment_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new DemandManagerElectricEquipment_Impl(*demandManagerElectricEquipment, this, keepHandle));
      }
      if (auto demandManagerExteriorLights = std::dynamic_pointer_cast<DemandManagerExteriorLights_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new DemandManagerExteriorLights_Impl(*demandManagerExteriorLights, this, keepHandle));
      }
      if (auto exteriorLights = std::dynamic_pointer_cast<ExteriorLights_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new ExteriorLights_Impl(*exteriorLights, this, keepHandle));
      }
      if (auto exteriorFuelEquipment = std::dynamic_pointer_cast<ExteriorFuelEquipment_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new ExteriorFuelEquipment_Impl(*exteriorFuelEquipment, this, keepHandle));
      }
      if (auto exteriorWaterEquipment = std::dynamic_pointer_cast<ExteriorWaterEquipment_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new ExteriorWaterEquipment_Impl(*exteriorWaterEquipment, this, keepHandle));
      }
      if (auto externalInterface = std::dynamic_pointer_cast<ExternalInterface_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new ExternalInterface_Impl(*externalInterface, this, keepHandle));
      }
      if (auto externalInterfaceActuator = std::dynamic_pointer_cast<ExternalInterfaceActuator_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new ExternalInterfaceActuator_Impl(*externalInterfaceActuator, this, keepHandle));
      }
      if (auto externalInterfaceVariable = std::dynamic_pointer_cast<ExternalInterfaceVariable_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new ExternalInterfaceVariable_Impl(*externalInterfaceVariable, this, keepHandle));
      }
      if (auto externalInterfaceFunctionalMockupUnitImport =
            std::dynamic_pointer_cast<ExternalInterfaceFunctionalMockupUnitImport_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new ExternalInterfaceFunctionalMockupUnitImport_Impl(*externalInterfaceFunctionalMockupUnitImport, this, keepHandle));
      }
      if (auto externalInterfaceFunctionalMockupUnitImportFromVariable =
            std::dynamic_pointer_cast<ExternalInterfaceFunctionalMockupUnitImportFromVariable_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new ExternalInterfaceFunctionalMockupUnitImportFromVariable_Impl(
          *externalInterfaceFunctionalMockupUnitImportFromVariable, this, keepHandle));
      }
      if (auto externalInterfaceFunctionalMockupUnitImportToActuator =
            std::dynamic_pointer_cast<ExternalInterfaceFunctionalMockupUnitImportToActuator_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new ExternalInterfaceFunctionalMockupUnitImportToActuator_Impl(*externalInterfaceFunctionalMockupUnitImportToActuator, this, keepHandle));
      }
      if (auto externalInterfaceFunctionalMockupUnitImportToVariable =
            std::dynamic_pointer_cast<ExternalInterfaceFunctionalMockupUnitImportToVariable_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new ExternalInterfaceFunctionalMockupUnitImportToVariable_Impl(*externalInterfaceFunctionalMockupUnitImportToVariable, this, keepHandle));
      }
      if (auto externalInterfaceFunctionalMockupUnitExportFromVariable =
            std::dynamic_pointer_cast<ExternalInterfaceFunctionalMockupUnitExportFromVariable_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new ExternalInterfaceFunctionalMockupUnitExportFromVariable_Impl(
          *externalInterfaceFunctionalMockupUnitExportFromVariable, this, keepHandle));
      }
      if (auto externalInterfaceFunctionalMockupUnitExportToActuator =
            std::dynamic_pointer_cast<ExternalInterfaceFunctionalMockupUnitExportToActuator_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new ExternalInterfaceFunctionalMockupUnitExportToActuator_Impl(*externalInterfaceFunctionalMockupUnitExportToActuator, this, keepHandle));
      }
      if (auto externalInterfaceFunctionalMockupUnitExportToVariable =
            std::dynamic_pointer_cast<ExternalInterfaceFunctionalMockupUnitExportToVariable_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new ExternalInterfaceFunctionalMockupUnitExportToVariable_Impl(*externalInterfaceFunctionalMockupUnitExportToVariable, this, keepHandle));
      }
      if (auto externalInterfaceFunctionalMockupUnitImportToSchedule =
            std::dynamic_pointer_cast<ExternalInterfaceFunctionalMockupUnitImportToSchedule_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new ExternalInterfaceFunctionalMockupUnitImportToSchedule_Impl(*externalInterfaceFunctionalMockupUnitImportToSchedule, this, keepHandle));
      }
      if (auto externalInterfaceFunctionalMockupUnitExportToSchedule =
            std::dynamic_pointer_cast<ExternalInterfaceFunctionalMockupUnitExportToSchedule_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new ExternalInterfaceFunctionalMockupUnitExportToSchedule_Impl(*externalInterfaceFunctionalMockupUnitExportToSchedule, this, keepHandle));
      }
      if (auto externalInterfaceSchedule = std::dynamic_pointer_cast<ExternalInterfaceSchedule_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new ExternalInterfaceSchedule_Impl(*externalInterfaceSchedule, this, keepHandle));
      }
      if (auto scheduleCompact = std::dynamic_pointer_cast<ScheduleCompact_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new ScheduleCompact_Impl(*scheduleCompact, this, keepHandle));
      }
      if (auto scheduleConstant = std::dynamic_pointer_cast<ScheduleConstant_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new ScheduleConstant_Impl(*scheduleConstant, this, keepHandle));
      }
      if (auto scheduleRuleset = std::dynamic_pointer_cast<ScheduleRuleset_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new ScheduleRuleset_Impl(*scheduleRuleset, this, keepHandle));
      }
      if (auto scheduleDay = std::dynamic_pointer_cast<ScheduleDay_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new ScheduleDay_Impl(*scheduleDay, this, keepHandle));
      }
      if (auto scheduleFile = std::dynamic_pointer_cast<ScheduleFile_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new ScheduleFile_Impl(*scheduleFile, this, keepHandle));
      }
      if (auto scheduleFileShading = std::dynamic_pointer_cast<ScheduleFileShading_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new ScheduleFileShading_Impl(*scheduleFileShading, this, keepHandle));
      }
      if (auto scheduleDayList = std::dynamic_pointer_cast<ScheduleDayList_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new ScheduleDayList_Impl(*scheduleDayList, this, keepHandle));
      }
      if (auto scheduleDayHourly = std::dynamic_pointer_cast<ScheduleDayHourly_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new ScheduleDayHourly_Impl(*scheduleDayHourly, this, keepHandle));
      }
      if (auto scheduleWeekCompact = std::dynamic_pointer_cast<ScheduleWeekCompact_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new ScheduleWeekCompact_Impl(*scheduleWeekCompact, this, keepHandle));
      }
      if (auto scheduleTypeLimits = std::dynamic_pointer_cast<ScheduleTypeLimits_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new ScheduleTypeLimits_Impl(*scheduleTypeLimits, this, keepHandle));
      }
      if (auto tableIndependentVariable = std::dynamic_pointer_cast<TableIndependentVariable_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new TableIndependentVariable_Impl(*tableIndependentVariable, this, keepHandle));
      }
      if (auto tableLookup = std::dynamic_pointer_cast<TableLookup_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new TableLookup_Impl(*tableLookup, this, keepHandle));
      }
      if (auto scheduleWeek = std::dynamic_pointer_cast<ScheduleWeek_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new ScheduleWeek_Impl(*scheduleWeek, this, keepHandle));
      }
      if (auto spaceType = std::dynamic_pointer_cast<SpaceType_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new SpaceType_Impl(*spaceType, this, keepHandle));
      }
      if (auto demandManagerLights = std::dynamic_pointer_cast<DemandManagerLights_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new DemandManagerLights_Impl(*demandManagerLights, this, keepHandle));
      }
      if (auto demandManagerThermostats = std::dynamic_pointer_cast<DemandManagerThermostats_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new DemandManagerThermostats_Impl(*demandManagerThermostats, this, keepHandle));
      }
      if (auto demandManagerAssignmentList = std::dynamic_pointer_cast<DemandManagerAssignmentList_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new DemandManagerAssignmentList_Impl(*demandManagerAssignmentList, this, keepHandle));
      }
      if (auto matrixTwoDimension = std::dynamic_pointer_cast<MatrixTwoDimension_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new MatrixTwoDimension_Impl(*matrixTwoDimension, this, keepHandle));
      }
      if (auto electricEquipment = std::dynamic_pointer_cast<ElectricEquipment_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new ElectricEquipment_Impl(*electricEquipment, this, keepHandle));
      }
      if (auto electricEquipmentITEAirCooled = std::dynamic_pointer_cast<ElectricEquipmentITEAirCooled_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new ElectricEquipmentITEAirCooled_Impl(*electricEquipmentITEAirCooled, this, keepHandle));
      }
      if (auto gasEquipment = std::dynamic_pointer_cast<GasEquipment_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new GasEquipment_Impl(*gasEquipment, this, keepHandle));
      }
      if (auto hotWaterEquipment = std::dynamic_pointer_cast<HotWaterEquipment_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new HotWaterEquipment_Impl(*hotWaterEquipment, this, keepHandle));
      }
      if (auto steamEquipment = std::dynamic_pointer_cast<SteamEquipment_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new SteamEquipment_Impl(*steamEquipment, this, keepHandle));
      }
      if (auto otherEquipment = std::dynamic_pointer_cast<OtherEquipment_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new OtherEquipment_Impl(*otherEquipment, this, keepHandle));
      }
      if (auto lights = std::dynamic_pointer_cast<Lights_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new Lights_Impl(*lights, this, keepHandle));
      }
      if (auto people = std::dynamic_pointer_cast<People_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new People_Impl(*people, this, keepHandle));
      }
      if (auto waterUseEquipment = std::dynamic_pointer_cast<WaterUseEquipment_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new WaterUseEquipment_Impl(*waterUseEquipment, this, keepHandle));
      }
      if (auto waterUseRainCollector = std::dynamic_pointer_cast<WaterUseRainCollector_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new WaterUseRainCollector_Impl(*waterUseRainCollector, this, keepHandle));
      }
      if (auto waterUseStorage = std::dynamic_pointer_cast<WaterUseStorage_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new WaterUseStorage_Impl(*waterUseStorage, this, keepHandle));
      }
      if (auto waterUseWell = std::dynamic_pointer_cast<WaterUseWell_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new WaterUseWell_Impl(*waterUseWell, this, keepHandle));
      }
      if (auto refractionExtinctionGlazing = std::dynamic_pointer_cast<RefractionExtinctionGlazing_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new RefractionExtinctionGlazing_Impl(*refractionExtinctionGlazing, this, keepHandle));
      }
      if (auto thermochromicGlazing = std::dynamic_pointer_cast<ThermochromicGlazing_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new ThermochromicGlazing_Impl(*thermochromicGlazing, this, keepHandle));
      }
      if (auto standardGlazing = std::dynamic_pointer_cast<StandardGlazing_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new StandardGlazing_Impl(*standardGlazing, this, keepHandle));
      }
      if (auto simpleGlazing = std::dynamic_pointer_cast<SimpleGlazing_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new SimpleGlazing_Impl(*simpleGlazing, this, keepHandle));
      }
      if (auto standardOpaqueMaterial = std::dynamic_pointer_cast<StandardOpaqueMaterial_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new StandardOpaqueMaterial_Impl(*standardOpaqueMaterial, this, keepHandle));
      }
      if (auto airGap = std::dynamic_pointer_cast<AirGap_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new AirGap_Impl(*airGap, this, keepHandle));
      }
      if (auto masslessOpaqueMaterial = std::dynamic_pointer_cast<MasslessOpaqueMaterial_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new MasslessOpaqueMaterial_Impl(*masslessOpaqueMaterial, this, keepHandle));
      }
      if (auto roofVegetation = std::dynamic_pointer_cast<RoofVegetation_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new RoofVegetation_Impl(*roofVegetation, this, keepHandle));
      }
      if (auto heatExchangerAirToAirFlatPlate = std::dynamic_pointer_cast<HeatExchangerAirToAirFlatPlate_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new HeatExchangerAirToAirFlatPlate_Impl(*heatExchangerAirToAirFlatPlate, this, keepHandle));
      }
      if (auto heatExchangerAirToAirSensibleAndLatent =
            std::dynamic_pointer_cast<HeatExchangerAirToAirSensibleAndLatent_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new HeatExchangerAirToAirSensibleAndLatent_Impl(*heatExchangerAirToAirSensibleAndLatent, this, keepHandle));
      }
      if (auto heatExchangerDesiccantBalancedFlow = std::dynamic_pointer_cast<HeatExchangerDesiccantBalancedFlow_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new HeatExchangerDesiccantBalancedFlow_Impl(*heatExchangerDesiccantBalancedFlow, this, keepHandle));
      }
      if (auto exhaustSystem = std::dynamic_pointer_cast<AirLoopHVACExhaustSystem_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new AirLoopHVACExhaustSystem_Impl(*exhaustSystem, this, keepHandle));
      }
      if (auto airLoopHVACMixer = std::dynamic_pointer_cast<AirLoopHVACMixer_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new AirLoopHVACMixer_Impl(*airLoopHVACMixer, this, keepHandle));
      }
      if (auto airLoopHVACSplitter = std::dynamic_pointer_cast<AirLoopHVACSplitter_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new AirLoopHVACSplitter_Impl(*airLoopHVACSplitter, this, keepHandle));
      }
      if (auto spaceHVACZoneReturnMixer = std::dynamic_pointer_cast<SpaceHVACZoneReturnMixer_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new SpaceHVACZoneReturnMixer_Impl(*spaceHVACZoneReturnMixer, this, keepHandle));
      }
      if (auto groundHeatTransferControl = std::dynamic_pointer_cast<GroundHeatTransferControl_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new GroundHeatTransferControl_Impl(*groundHeatTransferControl, this, keepHandle));
      }
      if (auto groundHeatTransferBasementAutoGrid = std::dynamic_pointer_cast<GroundHeatTransferBasementAutoGrid_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new GroundHeatTransferBasementAutoGrid_Impl(*groundHeatTransferBasementAutoGrid, this, keepHandle));
      }
      if (auto groundHeatTransferBasementBldgData = std::dynamic_pointer_cast<GroundHeatTransferBasementBldgData_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new GroundHeatTransferBasementBldgData_Impl(*groundHeatTransferBasementBldgData, this, keepHandle));
      }
      if (auto groundHeatTransferBasementComBldg = std::dynamic_pointer_cast<GroundHeatTransferBasementComBldg_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new GroundHeatTransferBasementComBldg_Impl(*groundHeatTransferBasementComBldg, this, keepHandle));
      }
      if (auto groundHeatTransferBasementMatlProps = std::dynamic_pointer_cast<GroundHeatTransferBasementMatlProps_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new GroundHeatTransferBasementMatlProps_Impl(*groundHeatTransferBasementMatlProps, this, keepHandle));
      }
      if (auto groundHeatTransferBasementInsulation = std::dynamic_pointer_cast<GroundHeatTransferBasementInsulation_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new GroundHeatTransferBasementInsulation_Impl(*groundHeatTransferBasementInsulation, this, keepHandle));
      }
      if (auto groundHeatTransferBasementManualGrid = std::dynamic_pointer_cast<GroundHeatTransferBasementManualGrid_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new GroundHeatTransferBasementManualGrid_Impl(*groundHeatTransferBasementManualGrid, this, keepHandle));
      }
      if (auto groundHeatTransferBasementSimParameters =
            std::dynamic_pointer_cast<GroundHeatTransferBasementSimParameters_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new GroundHeatTransferBasementSimParameters_Impl(*groundHeatTransferBasementSimParameters, this, keepHandle));
      }
      if (auto groundHeatTransferBasementSurfaceProps =
            std::dynamic_pointer_cast<GroundHeatTransferBasementSurfaceProps_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new GroundHeatTransferBasementSurfaceProps_Impl(*groundHeatTransferBasementSurfaceProps, this, keepHandle));
      }
      if (auto groundHeatTransferBasementXFACE = std::dynamic_pointer_cast<GroundHeatTransferBasementXFACE_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new GroundHeatTransferBasementXFACE_Impl(*groundHeatTransferBasementXFACE, this, keepHandle));
      }
      if (auto groundHeatTransferBasementYFACE = std::dynamic_pointer_cast<GroundHeatTransferBasementYFACE_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new GroundHeatTransferBasementYFACE_Impl(*groundHeatTransferBasementYFACE, this, keepHandle));
      }
      if (auto groundHeatTransferBasementZFACE = std::dynamic_pointer_cast<GroundHeatTransferBasementZFACE_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new GroundHeatTransferBasementZFACE_Impl(*groundHeatTransferBasementZFACE, this, keepHandle));
      }
      if (auto groundHeatTransferSlabAutoGrid = std::dynamic_pointer_cast<GroundHeatTransferSlabAutoGrid_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new GroundHeatTransferSlabAutoGrid_Impl(*groundHeatTransferSlabAutoGrid, this, keepHandle));
      }
      if (auto groundHeatTransferSlabManualGrid = std::dynamic_pointer_cast<GroundHeatTransferSlabManualGrid_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new GroundHeatTransferSlabManualGrid_Impl(*groundHeatTransferSlabManualGrid, this, keepHandle));
      }
      if (auto groundHeatTransferSlabBoundConds = std::dynamic_pointer_cast<GroundHeatTransferSlabBoundConds_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new GroundHeatTransferSlabBoundConds_Impl(*groundHeatTransferSlabBoundConds, this, keepHandle));
      }
      if (auto groundHeatTransferSlabBldgProps = std::dynamic_pointer_cast<GroundHeatTransferSlabBldgProps_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new GroundHeatTransferSlabBldgProps_Impl(*groundHeatTransferSlabBldgProps, this, keepHandle));
      }
      if (auto groundHeatTransferSlabEquivalentSlab = std::dynamic_pointer_cast<GroundHeatTransferSlabEquivalentSlab_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new GroundHeatTransferSlabEquivalentSlab_Impl(*groundHeatTransferSlabEquivalentSlab, this, keepHandle));
      }
      if (auto groundHeatTransferSlabMaterials = std::dynamic_pointer_cast<GroundHeatTransferSlabMaterials_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new GroundHeatTransferSlabMaterials_Impl(*groundHeatTransferSlabMaterials, this, keepHandle));
      }
      if (auto groundHeatTransferSlabMatlProps = std::dynamic_pointer_cast<GroundHeatTransferSlabMatlProps_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new GroundHeatTransferSlabMatlProps_Impl(*groundHeatTransferSlabMatlProps, this, keepHandle));
      }
      if (auto groundHeatTransferSlabInsulation = std::dynamic_pointer_cast<GroundHeatTransferSlabInsulation_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new GroundHeatTransferSlabInsulation_Impl(*groundHeatTransferSlabInsulation, this, keepHandle));
      }
      if (auto groundHeatTransferSlabXFACE = std::dynamic_pointer_cast<GroundHeatTransferSlabXFACE_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new GroundHeatTransferSlabXFACE_Impl(*groundHeatTransferSlabXFACE, this, keepHandle));
      }
      if (auto groundHeatTransferSlabYFACE = std::dynamic_pointer_cast<GroundHeatTransferSlabYFACE_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new GroundHeatTransferSlabYFACE_Impl(*groundHeatTransferSlabYFACE, this, keepHandle));
      }
      if (auto groundHeatTransferSlabZFACE = std::dynamic_pointer_cast<GroundHeatTransferSlabZFACE_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new GroundHeatTransferSlabZFACE_Impl(*groundHeatTransferSlabZFACE, this, keepHandle));
      }
      if (auto siteGroundDomainSlab = std::dynamic_pointer_cast<SiteGroundDomainSlab_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new SiteGroundDomainSlab_Impl(*siteGroundDomainSlab, this, keepHandle));
      }
      if (auto siteGroundReflectance = std::dynamic_pointer_cast<SiteGroundReflectance_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new SiteGroundReflectance_Impl(*siteGroundReflectance, this, keepHandle));
      }
      if (auto siteGroundReflectanceSnowModifier = std::dynamic_pointer_cast<SiteGroundReflectanceSnowModifier_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new SiteGroundReflectanceSnowModifier_Impl(*siteGroundReflectanceSnowModifier, this, keepHandle));
      }
      if (auto siteGroundDomainBasement = std::dynamic_pointer_cast<SiteGroundDomainBasement_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new SiteGroundDomainBasement_Impl(*siteGroundDomainBasement, this, keepHandle));
      }
      if (auto siteGroundTemperatureDeep = std::dynamic_pointer_cast<SiteGroundTemperatureDeep_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new SiteGroundTemperatureDeep_Impl(*siteGroundTemperatureDeep, this, keepHandle));
      }
      if (auto siteGroundTemperatureFCfactorMethod = std::dynamic_pointer_cast<SiteGroundTemperatureFCfactorMethod_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new SiteGroundTemperatureFCfactorMethod_Impl(*siteGroundTemperatureFCfactorMethod, this, keepHandle));
      }
      if (auto siteGroundTemperatureShallow = std::dynamic_pointer_cast<SiteGroundTemperatureShallow_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new SiteGroundTemperatureShallow_Impl(*siteGroundTemperatureShallow, this, keepHandle));
      }
      if (auto siteGroundTemperatureBuildingSurface = std::dynamic_pointer_cast<SiteGroundTemperatureBuildingSurface_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new SiteGroundTemperatureBuildingSurface_Impl(*siteGroundTemperatureBuildingSurface, this, keepHandle));
      }
      if (auto siteGroundTemperatureUndisturbedFiniteDifference =
            std::dynamic_pointer_cast<SiteGroundTemperatureUndisturbedFiniteDifference_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new SiteGroundTemperatureUndisturbedFiniteDifference_Impl(*siteGroundTemperatureUndisturbedFiniteDifference, this, keepHandle));
      }
      if (auto siteGroundTemperatureUndisturbedKusudaAchenbach =
            std::dynamic_pointer_cast<SiteGroundTemperatureUndisturbedKusudaAchenbach_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new SiteGroundTemperatureUndisturbedKusudaAchenbach_Impl(*siteGroundTemperatureUndisturbedKusudaAchenbach, this, keepHandle));
      }
      if (auto siteGroundTemperatureUndisturbedXing = std::dynamic_pointer_cast<SiteGroundTemperatureUndisturbedXing_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new SiteGroundTemperatureUndisturbedXing_Impl(*siteGroundTemperatureUndisturbedXing, this, keepHandle));
      }
      if (auto sitePrecipitation = std::dynamic_pointer_cast<SitePrecipitation_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new SitePrecipitation_Impl(*sitePrecipitation, this, keepHandle));
      }
      if (auto siteWaterMainsTemperature = std::dynamic_pointer_cast<SiteWaterMainsTemperature_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new SiteWaterMainsTemperature_Impl(*siteWaterMainsTemperature, this, keepHandle));
      }
      if (auto siteWeatherStation = std::dynamic_pointer_cast<SiteWeatherStation_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new SiteWeatherStation_Impl(*siteWeatherStation, this, keepHandle));
      }
      if (auto siteSolarAndVisibleSpectrum = std::dynamic_pointer_cast<SiteSolarAndVisibleSpectrum_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new SiteSolarAndVisibleSpectrum_Impl(*siteSolarAndVisibleSpectrum, this, keepHandle));
      }
      if (auto siteSpectrumData = std::dynamic_pointer_cast<SiteSpectrumData_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new SiteSpectrumData_Impl(*siteSpectrumData, this, keepHandle));
      }
      if (auto skyTemperature = std::dynamic_pointer_cast<SkyTemperature_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new SkyTemperature_Impl(*skyTemperature, this, keepHandle));
      }
      if (auto airLoopHVACUnitaryFurnaceHeatCool = std::dynamic_pointer_cast<AirLoopHVACUnitaryFurnaceHeatCool_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new AirLoopHVACUnitaryFurnaceHeatCool_Impl(*airLoopHVACUnitaryFurnaceHeatCool, this, keepHandle));
      }
      if (auto airLoopHVACUnitaryFurnaceHeatOnly = std::dynamic_pointer_cast<AirLoopHVACUnitaryFurnaceHeatOnly_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new AirLoopHVACUnitaryFurnaceHeatOnly_Impl(*airLoopHVACUnitaryFurnaceHeatOnly, this, keepHandle));
      }
      if (auto airLoopHVACUnitaryHeatCool = std::dynamic_pointer_cast<AirLoopHVACUnitaryHeatCool_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new AirLoopHVACUnitaryHeatCool_Impl(*airLoopHVACUnitaryHeatCool, this, keepHandle));
      }
      if (auto airLoopHVACUnitaryHeatOnly = std::dynamic_pointer_cast<AirLoopHVACUnitaryHeatOnly_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new AirLoopHVACUnitaryHeatOnly_Impl(*airLoopHVACUnitaryHeatOnly, this, keepHandle));
      }
      if (auto airLoopHVACUnitaryHeatPumpAirToAir = std::dynamic_pointer_cast<AirLoopHVACUnitaryHeatPumpAirToAir_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new AirLoopHVACUnitaryHeatPumpAirToAir_Impl(*airLoopHVACUnitaryHeatPumpAirToAir, this, keepHandle));
      }
      if (auto airLoopHVACUnitaryHeatPumpWaterToAir = std::dynamic_pointer_cast<AirLoopHVACUnitaryHeatPumpWaterToAir_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new AirLoopHVACUnitaryHeatPumpWaterToAir_Impl(*airLoopHVACUnitaryHeatPumpWaterToAir, this, keepHandle));
      }
      if (auto airLoopHVACUnitaryHeatPumpAirToAirMultiSpeed =
            std::dynamic_pointer_cast<AirLoopHVACUnitaryHeatPumpAirToAirMultiSpeed_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new AirLoopHVACUnitaryHeatPumpAirToAirMultiSpeed_Impl(*airLoopHVACUnitaryHeatPumpAirToAirMultiSpeed, this, keepHandle));
      }
      if (auto airLoopHVACUnitaryHeatCoolVAVChangeoverBypass =
            std::dynamic_pointer_cast<AirLoopHVACUnitaryHeatCoolVAVChangeoverBypass_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new AirLoopHVACUnitaryHeatCoolVAVChangeoverBypass_Impl(*airLoopHVACUnitaryHeatCoolVAVChangeoverBypass, this, keepHandle));
      }
      if (auto airLoopHVACUnitarySystem = std::dynamic_pointer_cast<AirLoopHVACUnitarySystem_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new AirLoopHVACUnitarySystem_Impl(*airLoopHVACUnitarySystem, this, keepHandle));
      }
      if (auto zoneHVACBaseboardConvectiveElectric = std::dynamic_pointer_cast<ZoneHVACBaseboardConvectiveElectric_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new ZoneHVACBaseboardConvectiveElectric_Impl(*zoneHVACBaseboardConvectiveElectric, this, keepHandle));
      }
      if (auto zoneHVACBaseboardConvectiveWater = std::dynamic_pointer_cast<ZoneHVACBaseboardConvectiveWater_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new ZoneHVACBaseboardConvectiveWater_Impl(*zoneHVACBaseboardConvectiveWater, this, keepHandle));
      }
      if (auto zoneHVACBaseboardRadiantConvectiveElectric =
            std::dynamic_pointer_cast<ZoneHVACBaseboardRadiantConvectiveElectric_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new ZoneHVACBaseboardRadiantConvectiveElectric_Impl(*zoneHVACBaseboardRadiantConvectiveElectric, this, keepHandle));
      }
      if (auto zoneHVACBaseboardRadiantConvectiveWater =
            std::dynamic_pointer_cast<ZoneHVACBaseboardRadiantConvectiveWater_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new ZoneHVACBaseboardRadiantConvectiveWater_Impl(*zoneHVACBaseboardRadiantConvectiveWater, this, keepHandle));
      }
      if (auto zoneHVACCoolingPanelRadiantConvectiveWater =
            std::dynamic_pointer_cast<ZoneHVACCoolingPanelRadiantConvectiveWater_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new ZoneHVACCoolingPanelRadiantConvectiveWater_Impl(*zoneHVACCoolingPanelRadiantConvectiveWater, this, keepHandle));
      }
      if (auto zoneHVACHighTemperatureRadiant = std::dynamic_pointer_cast<ZoneHVACHighTemperatureRadiant_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new ZoneHVACHighTemperatureRadiant_Impl(*zoneHVACHighTemperatureRadiant, this, keepHandle));
      }
      if (auto zoneHVACPackagedTerminalAirConditioner =
            std::dynamic_pointer_cast<ZoneHVACPackagedTerminalAirConditioner_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new ZoneHVACPackagedTerminalAirConditioner_Impl(*zoneHVACPackagedTerminalAirConditioner, this, keepHandle));
      }
      if (auto zoneHVACPackagedTerminalHeatPump = std::dynamic_pointer_cast<ZoneHVACPackagedTerminalHeatPump_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new ZoneHVACPackagedTerminalHeatPump_Impl(*zoneHVACPackagedTerminalHeatPump, this, keepHandle));
      }
      if (auto zoneHVACWaterToAirHeatPump = std::dynamic_pointer_cast<ZoneHVACWaterToAirHeatPump_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new ZoneHVACWaterToAirHeatPump_Impl(*zoneHVACWaterToAirHeatPump, this, keepHandle));
      }
      if (auto zoneHVACTerminalUnitVariableRefrigerantFlow =
            std::dynamic_pointer_cast<ZoneHVACTerminalUnitVariableRefrigerantFlow_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new ZoneHVACTerminalUnitVariableRefrigerantFlow_Impl(*zoneHVACTerminalUnitVariableRefrigerantFlow, this, keepHandle));
      }
      if (auto zoneHVACLowTempRadiantConstFlow = std::dynamic_pointer_cast<ZoneHVACLowTempRadiantConstFlow_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new ZoneHVACLowTempRadiantConstFlow_Impl(*zoneHVACLowTempRadiantConstFlow, this, keepHandle));
      }
      if (auto zoneHVACLowTempRadiantVarFlow = std::dynamic_pointer_cast<ZoneHVACLowTempRadiantVarFlow_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new ZoneHVACLowTempRadiantVarFlow_Impl(*zoneHVACLowTempRadiantVarFlow, this, keepHandle));
      }
      if (auto zoneHVACLowTemperatureRadiantElectric = std::dynamic_pointer_cast<ZoneHVACLowTemperatureRadiantElectric_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new ZoneHVACLowTemperatureRadiantElectric_Impl(*zoneHVACLowTemperatureRadiantElectric, this, keepHandle));
      }
      if (auto zoneHVACIdealLoadsAirSystem = std::dynamic_pointer_cast<ZoneHVACIdealLoadsAirSystem_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new ZoneHVACIdealLoadsAirSystem_Impl(*zoneHVACIdealLoadsAirSystem, this, keepHandle));
      }
      if (auto zoneHVACBaseboardRadiantConvectiveWaterDesign =
            std::dynamic_pointer_cast<ZoneHVACBaseboardRadiantConvectiveWaterDesign_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new ZoneHVACBaseboardRadiantConvectiveWaterDesign_Impl(*zoneHVACBaseboardRadiantConvectiveWaterDesign, this, keepHandle));
      }
      if (auto zoneHVACBaseboardRadiantConvectiveSteam =
            std::dynamic_pointer_cast<ZoneHVACBaseboardRadiantConvectiveSteam_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new ZoneHVACBaseboardRadiantConvectiveSteam_Impl(*zoneHVACBaseboardRadiantConvectiveSteam, this, keepHandle));
      }
      if (auto zoneHVACBaseboardRadiantConvectiveSteamDesign =
            std::dynamic_pointer_cast<ZoneHVACBaseboardRadiantConvectiveSteamDesign_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new ZoneHVACBaseboardRadiantConvectiveSteamDesign_Impl(*zoneHVACBaseboardRadiantConvectiveSteamDesign, this, keepHandle));
      }
      if (auto zoneHVACDehumidifierDX = std::dynamic_pointer_cast<ZoneHVACDehumidifierDX_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new ZoneHVACDehumidifierDX_Impl(*zoneHVACDehumidifierDX, this, keepHandle));
      }
      if (auto zoneHVACFourPipeFanCoil = std::dynamic_pointer_cast<ZoneHVACFourPipeFanCoil_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new ZoneHVACFourPipeFanCoil_Impl(*zoneHVACFourPipeFanCoil, this, keepHandle));
      }
      if (auto zoneHVACEnergyRecoveryVentilator = std::dynamic_pointer_cast<ZoneHVACEnergyRecoveryVentilator_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new ZoneHVACEnergyRecoveryVentilator_Impl(*zoneHVACEnergyRecoveryVentilator, this, keepHandle));
      }
      if (auto zoneHVACEvaporativeCoolerUnit = std::dynamic_pointer_cast<ZoneHVACEvaporativeCoolerUnit_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new ZoneHVACEvaporativeCoolerUnit_Impl(*zoneHVACEvaporativeCoolerUnit, this, keepHandle));
      }
      if (auto zoneHVACUnitHeater = std::dynamic_pointer_cast<ZoneHVACUnitHeater_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new ZoneHVACUnitHeater_Impl(*zoneHVACUnitHeater, this, keepHandle));
      }
      if (auto zoneVentilationWindandStackOpenArea = std::dynamic_pointer_cast<ZoneVentilationWindandStackOpenArea_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new ZoneVentilationWindandStackOpenArea_Impl(*zoneVentilationWindandStackOpenArea, this, keepHandle));
      }
      if (auto zoneHVACUnitVentilator = std::dynamic_pointer_cast<ZoneHVACUnitVentilator_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new ZoneHVACUnitVentilator_Impl(*zoneHVACUnitVentilator, this, keepHandle));
      }
      if (auto zoneHVACHybridUnitaryHVAC = std::dynamic_pointer_cast<ZoneHVACHybridUnitaryHVAC_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new ZoneHVACHybridUnitaryHVAC_Impl(*zoneHVACHybridUnitaryHVAC, this, keepHandle));
      }
      if (auto zoneHVACExhaustControl = std::dynamic_pointer_cast<ZoneHVACExhaustControl_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new ZoneHVACExhaustControl_Impl(*zoneHVACExhaustControl, this, keepHandle));
      }
      if (auto zoneHVACForcedAirUserDefined = std::dynamic_pointer_cast<ZoneHVACForcedAirUserDefined_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new ZoneHVACForcedAirUserDefined_Impl(*zoneHVACForcedAirUserDefined, this, keepHandle));
      }
      if (auto zoneHVACOutdoorAirUnit = std::dynamic_pointer_cast<ZoneHVACOutdoorAirUnit_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new ZoneHVACOutdoorAirUnit_Impl(*zoneHVACOutdoorAirUnit, this, keepHandle));
      }
      if (auto zoneHVACOutdoorAirUnitEquipmentList = std::dynamic_pointer_cast<ZoneHVACOutdoorAirUnitEquipmentList_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new ZoneHVACOutdoorAirUnitEquipmentList_Impl(*zoneHVACOutdoorAirUnitEquipmentList, this, keepHandle));
      }
      if (auto zoneHVACVentilatedSlab = std::dynamic_pointer_cast<ZoneHVACVentilatedSlab_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new ZoneHVACVentilatedSlab_Impl(*zoneHVACVentilatedSlab, this, keepHandle));
      }
      if (auto zoneHVACWindowAirConditioner = std::dynamic_pointer_cast<ZoneHVACWindowAirConditioner_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new ZoneHVACWindowAirConditioner_Impl(*zoneHVACWindowAirConditioner, this, keepHandle));
      }
      if (auto refrigerationAirChiller = std::dynamic_pointer_cast<RefrigerationAirChiller_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new RefrigerationAirChiller_Impl(*refrigerationAirChiller, this, keepHandle));
      }
      if (auto refrigerationCondenserAirCooled = std::dynamic_pointer_cast<RefrigerationCondenserAirCooled_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new RefrigerationCondenserAirCooled_Impl(*refrigerationCondenserAirCooled, this, keepHandle));
      }
      if (auto refrigerationGasCooler = std::dynamic_pointer_cast<RefrigerationGasCoolerAirCooled_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new RefrigerationGasCoolerAirCooled_Impl(*refrigerationGasCooler, this, keepHandle));
      }
      if (auto refrigerationCondenserEvaporativeCooled =
            std::dynamic_pointer_cast<RefrigerationCondenserEvaporativeCooled_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new RefrigerationCondenserEvaporativeCooled_Impl(*refrigerationCondenserEvaporativeCooled, this, keepHandle));
      }
      if (auto refrigerationCondenserCascade = std::dynamic_pointer_cast<RefrigerationCondenserCascade_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new RefrigerationCondenserCascade_Impl(*refrigerationCondenserCascade, this, keepHandle));
      }
      if (auto refrigerationSubcoolerLiquidSuction = std::dynamic_pointer_cast<RefrigerationSubcoolerLiquidSuction_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new RefrigerationSubcoolerLiquidSuction_Impl(*refrigerationSubcoolerLiquidSuction, this, keepHandle));
      }
      if (auto refrigerationCondenserWaterCooled = std::dynamic_pointer_cast<RefrigerationCondenserWaterCooled_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new RefrigerationCondenserWaterCooled_Impl(*refrigerationCondenserWaterCooled, this, keepHandle));
      }
      if (auto refrigerationSecondarySystem = std::dynamic_pointer_cast<RefrigerationSecondarySystem_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new RefrigerationSecondarySystem_Impl(*refrigerationSecondarySystem, this, keepHandle));
      }
      if (auto refrigerationCase = std::dynamic_pointer_cast<RefrigerationCase_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new RefrigerationCase_Impl(*refrigerationCase, this, keepHandle));
      }
      if (auto refrigerationCompressor = std::dynamic_pointer_cast<RefrigerationCompressor_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new RefrigerationCompressor_Impl(*refrigerationCompressor, this, keepHandle));
      }
      if (auto refrigerationCompressorRack = std::dynamic_pointer_cast<RefrigerationCompressorRack_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new RefrigerationCompressorRack_Impl(*refrigerationCompressorRack, this, keepHandle));
      }
      if (auto refrigerationSystem = std::dynamic_pointer_cast<RefrigerationSystem_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new RefrigerationSystem_Impl(*refrigerationSystem, this, keepHandle));
      }
      if (auto refrigerationWalkIn = std::dynamic_pointer_cast<RefrigerationWalkIn_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new RefrigerationWalkIn_Impl(*refrigerationWalkIn, this, keepHandle));
      }
      if (auto refrigerationTranscriticalSystem = std::dynamic_pointer_cast<RefrigerationTranscriticalSystem_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new RefrigerationTranscriticalSystem_Impl(*refrigerationTranscriticalSystem, this, keepHandle));
      }
      if (auto thermostatSetpointDualSetpoint = std::dynamic_pointer_cast<ThermostatSetpointDualSetpoint_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new ThermostatSetpointDualSetpoint_Impl(*thermostatSetpointDualSetpoint, this, keepHandle));
      }
      if (auto thermostatSetpointSingleHeatingOrCooling =
            std::dynamic_pointer_cast<ThermostatSetpointSingleHeatingOrCooling_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new ThermostatSetpointSingleHeatingOrCooling_Impl(*thermostatSetpointSingleHeatingOrCooling, this, keepHandle));
      }
      if (auto thermostatSetpointThermalComfortFangerDualSetpoint =
            std::dynamic_pointer_cast<ThermostatSetpointThermalComfortFangerDualSetpoint_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new ThermostatSetpointThermalComfortFangerDualSetpoint_Impl(*thermostatSetpointThermalComfortFangerDualSetpoint, this, keepHandle));
      }
      if (auto thermostatSetpointThermalComfortFangerSingleCooling =
            std::dynamic_pointer_cast<ThermostatSetpointThermalComfortFangerSingleCooling_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new ThermostatSetpointThermalComfortFangerSingleCooling_Impl(*thermostatSetpointThermalComfortFangerSingleCooling, this, keepHandle));
      }
      if (auto thermostatSetpointThermalComfortFangerSingleHeating =
            std::dynamic_pointer_cast<ThermostatSetpointThermalComfortFangerSingleHeating_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new ThermostatSetpointThermalComfortFangerSingleHeating_Impl(*thermostatSetpointThermalComfortFangerSingleHeating, this, keepHandle));
      }
      if (auto thermostatSetpointThermalComfortFangerSingleHeatingOrCooling =
            std::dynamic_pointer_cast<ThermostatSetpointThermalComfortFangerSingleHeatingOrCooling_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new ThermostatSetpointThermalComfortFangerSingleHeatingOrCooling_Impl(
          *thermostatSetpointThermalComfortFangerSingleHeatingOrCooling, this, keepHandle));
      }
      if (auto thermalStorageChilledWaterMixed = std::dynamic_pointer_cast<ThermalStorageChilledWaterMixed_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new ThermalStorageChilledWaterMixed_Impl(*thermalStorageChilledWaterMixed, this, keepHandle));
      }
      if (auto thermalStorageChilledWaterStratified = std::dynamic_pointer_cast<ThermalStorageChilledWaterStratified_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new ThermalStorageChilledWaterStratified_Impl(*thermalStorageChilledWaterStratified, this, keepHandle));
      }
      if (auto thermalStorageHotWaterStratified = std::dynamic_pointer_cast<ThermalStorageHotWaterStratified_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new ThermalStorageHotWaterStratified_Impl(*thermalStorageHotWaterStratified, this, keepHandle));
      }
      if (auto thermalStorageIceDetailed = std::dynamic_pointer_cast<ThermalStorageIceDetailed_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new ThermalStorageIceDetailed_Impl(*thermalStorageIceDetailed, this, keepHandle));
      }
      if (auto thermalStorageIceSimple = std::dynamic_pointer_cast<ThermalStorageIceSimple_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new ThermalStorageIceSimple_Impl(*thermalStorageIceSimple, this, keepHandle));
      }
      if (auto thermalStoragePCM = std::dynamic_pointer_cast<ThermalStoragePCM_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new ThermalStoragePCM_Impl(*thermalStoragePCM, this, keepHandle));
      }
      if (auto thermalStorageSizing = std::dynamic_pointer_cast<ThermalStorageSizing_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new ThermalStorageSizing_Impl(*thermalStorageSizing, this, keepHandle));
      }
      if (auto version = std::dynamic_pointer_cast<Version_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new Version_Impl(*version, this, keepHandle));
      }
      if (auto waterHeaterHeatPump = std::dynamic_pointer_cast<WaterHeaterHeatPump_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new WaterHeaterHeatPump_Impl(*waterHeaterHeatPump, this, keepHandle));
      }
      if (auto waterHeaterHeatPumpWrappedCondenser = std::dynamic_pointer_cast<WaterHeaterHeatPumpWrappedCondenser_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new WaterHeaterHeatPumpWrappedCondenser_Impl(*waterHeaterHeatPumpWrappedCondenser, this, keepHandle));
      }
      if (auto fanZoneExhaust = std::dynamic_pointer_cast<FanZoneExhaust_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new FanZoneExhaust_Impl(*fanZoneExhaust, this, keepHandle));
      }
      return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new ModelObject_Impl(*originalObjectImplPtr, this, keepHandle));
    }

    openstudio::epmodel::Model Model_Impl::model() const {
      return Model(std::dynamic_pointer_cast<Model_Impl>(std::const_pointer_cast<openstudio::detail::Workspace_Impl>(this->shared_from_this())));
    }

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
