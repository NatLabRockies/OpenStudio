#ifndef EPMODEL_ZoneHVACComponent_I
#define EPMODEL_ZoneHVACComponent_I

#ifdef SWIGPYTHON
  %module openstudioepmodelzonehvaccomponent
#endif

%include <epmodel/EPModel_Common_Include.i>
%import <epmodel/EPModel.i>
%import <epmodel/HVACComponent/EPModelHVACComponent.i>
%import <epmodel/StraightComponent/EPModelStraightComponent.i>

EPMODELOBJECT_WRAP(ZoneHVACComponent, <epmodel/ZoneHVACComponent/ZoneHVACComponent.hpp>, 0, 0)
EPMODELOBJECT_WRAP(AirLoopHVACUnitarySystem, <epmodel/ZoneHVACComponent/AirLoopHVACUnitarySystem.hpp>, 0, 1)
EPMODELOBJECT_WRAP(ZoneHVACBaseboardConvectiveElectric, <epmodel/ZoneHVACComponent/ZoneHVACBaseboardConvectiveElectric.hpp>, 0, 1)
EPMODELOBJECT_WRAP(ZoneHVACBaseboardRadiantConvectiveWater, <epmodel/ZoneHVACComponent/ZoneHVACBaseboardRadiantConvectiveWater.hpp>, 0, 1)
EPMODELOBJECT_WRAP(ZoneHVACBaseboardRadiantConvectiveWaterDesign, <epmodel/ZoneHVACComponent/ZoneHVACBaseboardRadiantConvectiveWaterDesign.hpp>, 0, 1)
EPMODELOBJECT_WRAP(ZoneHVACCoolingPanelRadiantConvectiveWater, <epmodel/ZoneHVACComponent/ZoneHVACCoolingPanelRadiantConvectiveWater.hpp>, 0, 1)
EPMODELOBJECT_WRAP(ZoneHVACBaseboardRadiantConvectiveElectric, <epmodel/ZoneHVACComponent/ZoneHVACBaseboardRadiantConvectiveElectric.hpp>, 0, 1)
EPMODELOBJECT_WRAP(ZoneHVACBaseboardConvectiveWater, <epmodel/ZoneHVACComponent/ZoneHVACBaseboardConvectiveWater.hpp>, 0, 1)
EPMODELOBJECT_WRAP(WaterHeaterHeatPump, <epmodel/ZoneHVACComponent/WaterHeaterHeatPump.hpp>, 0, 1)
EPMODELOBJECT_WRAP(WaterHeaterHeatPumpWrappedCondenser, <epmodel/ZoneHVACComponent/WaterHeaterHeatPumpWrappedCondenser.hpp>, 0, 1)
EPMODELOBJECT_WRAP(ZoneHVACWaterToAirHeatPump, <epmodel/ZoneHVACComponent/ZoneHVACWaterToAirHeatPump.hpp>, 0, 1)
EPMODELOBJECT_WRAP(ZoneHVACDehumidifierDX, <epmodel/ZoneHVACComponent/ZoneHVACDehumidifierDX.hpp>, 0, 1)
EPMODELOBJECT_WRAP(ZoneHVACEnergyRecoveryVentilator, <epmodel/ZoneHVACComponent/ZoneHVACEnergyRecoveryVentilator.hpp>, 0, 1)
EPMODELOBJECT_WRAP(ZoneHVACEvaporativeCoolerUnit, <epmodel/ZoneHVACComponent/ZoneHVACEvaporativeCoolerUnit.hpp>, 0, 1)
EPMODELOBJECT_WRAP(ZoneHVACUnitHeater, <epmodel/ZoneHVACComponent/ZoneHVACUnitHeater.hpp>, 0, 1)
EPMODELOBJECT_WRAP(RefrigerationAirChiller, <epmodel/ZoneHVACComponent/RefrigerationAirChiller.hpp>, 0, 1)
EPMODELOBJECT_WRAP(ZoneVentilationWindandStackOpenArea, <epmodel/ZoneHVACComponent/ZoneVentilationWindandStackOpenArea.hpp>, 0, 1)
EPMODELOBJECT_WRAP(ZoneHVACUnitVentilator, <epmodel/ZoneHVACComponent/ZoneHVACUnitVentilator.hpp>, 0, 1)
EPMODELOBJECT_WRAP(ZoneHVACFourPipeFanCoil, <epmodel/ZoneHVACComponent/ZoneHVACFourPipeFanCoil.hpp>, 0, 1)
EPMODELOBJECT_WRAP(ZoneHVACHighTemperatureRadiant, <epmodel/ZoneHVACComponent/ZoneHVACHighTemperatureRadiant.hpp>, 0, 1)
EPMODELOBJECT_WRAP(ZoneHVACPackagedTerminalAirConditioner, <epmodel/ZoneHVACComponent/ZoneHVACPackagedTerminalAirConditioner.hpp>, 0, 1)
EPMODELOBJECT_WRAP(ZoneHVACPackagedTerminalHeatPump, <epmodel/ZoneHVACComponent/ZoneHVACPackagedTerminalHeatPump.hpp>, 0, 1)
EPMODELOBJECT_WRAP(ZoneHVACTerminalUnitVariableRefrigerantFlow, <epmodel/ZoneHVACComponent/ZoneHVACTerminalUnitVariableRefrigerantFlow.hpp>, 0, 1)
EPMODELOBJECT_WRAP(ZoneHVACIdealLoadsAirSystem, <epmodel/ZoneHVACComponent/ZoneHVACIdealLoadsAirSystem.hpp>, 0, 1)
EPMODELOBJECT_WRAP(ZoneHVACLowTempRadiantConstFlow, <epmodel/ZoneHVACComponent/ZoneHVACLowTempRadiantConstFlow.hpp>, 0, 1)
EPMODELOBJECT_WRAP(ZoneHVACLowTempRadiantVarFlow, <epmodel/ZoneHVACComponent/ZoneHVACLowTempRadiantVarFlow.hpp>, 0, 1)
EPMODELOBJECT_WRAP(ZoneHVACLowTemperatureRadiantElectric, <epmodel/ZoneHVACComponent/ZoneHVACLowTemperatureRadiantElectric.hpp>, 0, 1)
EPMODELOBJECT_WRAP(FanZoneExhaust, <epmodel/ZoneHVACComponent/FanZoneExhaust.hpp>, 0, 1)

#endif
