#ifndef EPMODEL_WaterToWaterComponent_I
#define EPMODEL_WaterToWaterComponent_I

#ifdef SWIGPYTHON
  %module openstudioepmodelwatertowatercomponent
#endif

%include <epmodel/EPModel_Common_Include.i>
%import <epmodel/EPModel.i>
%import <epmodel/HVACComponent/EPModelHVACComponent.i>

EPMODELOBJECT_WRAP(CentralHeatPumpSystem, <epmodel/WaterToWaterComponent/CentralHeatPumpSystem.hpp>)
EPMODELOBJECT_WRAP(HeatPumpPlantLoopEIRCooling, <epmodel/WaterToWaterComponent/HeatPumpPlantLoopEIRCooling.hpp>)
EPMODELOBJECT_WRAP(HeatPumpPlantLoopEIRHeating, <epmodel/WaterToWaterComponent/HeatPumpPlantLoopEIRHeating.hpp>)
EPMODELOBJECT_WRAP(HeatPumpWaterToWaterEquationFitCooling, <epmodel/WaterToWaterComponent/HeatPumpWaterToWaterEquationFitCooling.hpp>)
EPMODELOBJECT_WRAP(HeatPumpWaterToWaterEquationFitHeating, <epmodel/WaterToWaterComponent/HeatPumpWaterToWaterEquationFitHeating.hpp>)
EPMODELOBJECT_WRAP(HeatExchangerFluidToFluid, <epmodel/WaterToWaterComponent/HeatExchangerFluidToFluid.hpp>)
EPMODELOBJECT_WRAP(WaterToWaterComponent, <epmodel/WaterToWaterComponent/WaterToWaterComponent.hpp>)
EPMODELOBJECT_WRAP(WaterHeaterMixed, <epmodel/WaterToWaterComponent/WaterHeaterMixed.hpp>)
EPMODELOBJECT_WRAP(WaterHeaterStratified, <epmodel/WaterToWaterComponent/WaterHeaterStratified.hpp>)
EPMODELOBJECT_WRAP(ThermalStorageChilledWaterStratified, <epmodel/WaterToWaterComponent/ThermalStorageChilledWaterStratified.hpp>)
EPMODELOBJECT_WRAP(ChillerAbsorption, <epmodel/WaterToWaterComponent/ChillerAbsorption.hpp>)
EPMODELOBJECT_WRAP(ChillerAbsorptionIndirect, <epmodel/WaterToWaterComponent/ChillerAbsorptionIndirect.hpp>)
EPMODELOBJECT_WRAP(ChillerElectric, <epmodel/WaterToWaterComponent/ChillerElectric.hpp>)
EPMODELOBJECT_WRAP(ChillerElectricEIR, <epmodel/WaterToWaterComponent/ChillerElectricEIR.hpp>)
EPMODELOBJECT_WRAP(ChillerElectricReformulatedEIR, <epmodel/WaterToWaterComponent/ChillerElectricReformulatedEIR.hpp>)
EPMODELOBJECT_WRAP(ChillerElectricASHRAE205, <epmodel/WaterToWaterComponent/ChillerElectricASHRAE205.hpp>)

#endif
