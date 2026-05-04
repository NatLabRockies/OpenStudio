#ifndef EPMODEL_WaterToWaterComponent_I
#define EPMODEL_WaterToWaterComponent_I

#ifdef SWIGPYTHON
  %module openstudioepmodelwatertowatercomponent
#endif

%include <epmodel/EPModel_Common_Include.i>
%import <epmodel/EPModel.i>
%import <epmodel/HVACComponent/EPModelHVACComponent.i>

EPMODELOBJECT_WRAP(CentralHeatPumpSystem, <epmodel/WaterToWaterComponent/CentralHeatPumpSystem.hpp>, 0, 1)
EPMODELOBJECT_WRAP(HeatPumpPlantLoopEIRCooling, <epmodel/WaterToWaterComponent/HeatPumpPlantLoopEIRCooling.hpp>, 0, 1)
EPMODELOBJECT_WRAP(HeatPumpPlantLoopEIRHeating, <epmodel/WaterToWaterComponent/HeatPumpPlantLoopEIRHeating.hpp>, 0, 1)
EPMODELOBJECT_WRAP(HeatPumpWaterToWaterEquationFitCooling, <epmodel/WaterToWaterComponent/HeatPumpWaterToWaterEquationFitCooling.hpp>, 0, 1)
EPMODELOBJECT_WRAP(HeatPumpWaterToWaterEquationFitHeating, <epmodel/WaterToWaterComponent/HeatPumpWaterToWaterEquationFitHeating.hpp>, 0, 1)
EPMODELOBJECT_WRAP(HeatExchangerFluidToFluid, <epmodel/WaterToWaterComponent/HeatExchangerFluidToFluid.hpp>, 0, 1)
EPMODELOBJECT_WRAP(WaterToWaterComponent, <epmodel/WaterToWaterComponent/WaterToWaterComponent.hpp>, 0, 0)
EPMODELOBJECT_WRAP(WaterHeaterMixed, <epmodel/WaterToWaterComponent/WaterHeaterMixed.hpp>, 0, 1)
EPMODELOBJECT_WRAP(WaterHeaterStratified, <epmodel/WaterToWaterComponent/WaterHeaterStratified.hpp>, 0, 1)
EPMODELOBJECT_WRAP(ThermalStorageChilledWaterStratified, <epmodel/WaterToWaterComponent/ThermalStorageChilledWaterStratified.hpp>, 0, 1)
EPMODELOBJECT_WRAP(ChillerAbsorption, <epmodel/WaterToWaterComponent/ChillerAbsorption.hpp>, 0, 1)
EPMODELOBJECT_WRAP(ChillerAbsorptionIndirect, <epmodel/WaterToWaterComponent/ChillerAbsorptionIndirect.hpp>, 0, 1)
EPMODELOBJECT_WRAP(ChillerElectric, <epmodel/WaterToWaterComponent/ChillerElectric.hpp>, 0, 1)
EPMODELOBJECT_WRAP(ChillerElectricEIR, <epmodel/WaterToWaterComponent/ChillerElectricEIR.hpp>, 0, 1)
EPMODELOBJECT_WRAP(ChillerElectricReformulatedEIR, <epmodel/WaterToWaterComponent/ChillerElectricReformulatedEIR.hpp>, 0, 1)
EPMODELOBJECT_WRAP(ChillerElectricASHRAE205, <epmodel/WaterToWaterComponent/ChillerElectricASHRAE205.hpp>, 0, 1)

#endif
