#ifndef EPMODEL_ParentObject_I
#define EPMODEL_ParentObject_I

#ifdef SWIGPYTHON
  %module openstudioepmodelparentobject
#endif

%include <epmodel/EPModel_Common_Include.i>
%import <epmodel/EPModel.i>

EPMODELOBJECT_WRAP(CoilWaterHeatingAirToWaterHeatPumpVariableSpeedSpeedData, <epmodel/ParentObject/CoilWaterHeatingAirToWaterHeatPumpVariableSpeedSpeedData.hpp>, 0, 1)
EPMODELOBJECT_WRAP(AirflowNetworkSimulationControl, <epmodel/ParentObject/AirflowNetworkSimulationControl.hpp>, 1, 1)
EPMODELOBJECT_WRAP(ParentObject, <epmodel/ParentObject/ParentObject.hpp>, 0, 0)
EPMODELOBJECT_WRAP(ControllerOutdoorAir, <epmodel/ParentObject/ControllerOutdoorAir.hpp>, 0, 1)
EPMODELOBJECT_WRAP(ZoneHVACEnergyRecoveryVentilatorController, <epmodel/ParentObject/ZoneHVACEnergyRecoveryVentilatorController.hpp>, 0, 1)
EPMODELOBJECT_WRAP(ElectricLoadCenterDistribution, <epmodel/ParentObject/ElectricLoadCenterDistribution.hpp>, 0, 1)
EPMODELOBJECT_WRAP(ElectricLoadCenterStorageConverter, <epmodel/ParentObject/ElectricLoadCenterStorageConverter.hpp>, 0, 1)
EPMODELOBJECT_WRAP(RefrigerationCase, <epmodel/ParentObject/RefrigerationCase.hpp>, 0, 1)
EPMODELOBJECT_WRAP(RefrigerationCondenserAirCooled, <epmodel/ParentObject/RefrigerationCondenserAirCooled.hpp>, 0, 1)
EPMODELOBJECT_WRAP(RefrigerationCondenserEvaporativeCooled, <epmodel/ParentObject/RefrigerationCondenserEvaporativeCooled.hpp>, 0, 1)
EPMODELOBJECT_WRAP(RefrigerationGasCoolerAirCooled, <epmodel/ParentObject/RefrigerationGasCoolerAirCooled.hpp>, 0, 1)
EPMODELOBJECT_WRAP(RefrigerationCompressor, <epmodel/ParentObject/RefrigerationCompressor.hpp>, 0, 1)
EPMODELOBJECT_WRAP(RefrigerationSecondarySystem, <epmodel/ParentObject/RefrigerationSecondarySystem.hpp>, 0, 1)
EPMODELOBJECT_WRAP(Building, <epmodel/ParentObject/Building.hpp>, 1, 1)
EPMODELOBJECT_WRAP(Site, <epmodel/ParentObject/Site.hpp>, 1, 1)
EPMODELOBJECT_WRAP(ComponentCostAdjustments, <epmodel/ParentObject/ComponentCostAdjustments.hpp>, 0, 1)
EPMODELOBJECT_WRAP(CurrencyType, <epmodel/ParentObject/CurrencyType.hpp>, 0, 1)
EPMODELOBJECT_WRAP(RunPeriod, <epmodel/ParentObject/RunPeriod.hpp>, 1, 1)
EPMODELOBJECT_WRAP(LifeCycleCostParameters, <epmodel/ParentObject/LifeCycleCostParameters.hpp>, 1, 1)
EPMODELOBJECT_WRAP(LifeCycleCostUsePriceEscalation, <epmodel/ParentObject/LifeCycleCostUsePriceEscalation.hpp>, 0, 1)
EPMODELOBJECT_WRAP(SimulationControl, <epmodel/ParentObject/SimulationControl.hpp>, 1, 1)
EPMODELOBJECT_WRAP(ChillerHeaterPerformanceElectricEIR, <epmodel/ParentObject/ChillerHeaterPerformanceElectricEIR.hpp>, 0, 1)
EPMODELOBJECT_WRAP(CoilPerformanceDXCooling, <epmodel/ParentObject/CoilPerformanceDXCooling.hpp>, 0, 1)
EPMODELOBJECT_WRAP(CoilCoolingWaterToAirHeatPumpVariableSpeedEquationFitSpeedData, <epmodel/ParentObject/CoilCoolingWaterToAirHeatPumpVariableSpeedEquationFitSpeedData.hpp>, 0, 1)
EPMODELOBJECT_WRAP(CoilHeatingWaterToAirHeatPumpVariableSpeedEquationFitSpeedData, <epmodel/ParentObject/CoilHeatingWaterToAirHeatPumpVariableSpeedEquationFitSpeedData.hpp>, 0, 1)

#endif
