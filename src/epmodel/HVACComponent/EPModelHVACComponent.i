#ifndef EPMODEL_HVACComponent_I
#define EPMODEL_HVACComponent_I

#ifdef SWIGPYTHON
  %module openstudioepmodelhvaccomponent
#endif

%include <epmodel/EPModel_Common_Include.i>
%import <epmodel/EPModel.i>
%import <epmodel/ParentObject/EPModelParentObject.i>

EPMODELOBJECT_WRAP(HVACComponent, <epmodel/HVACComponent/HVACComponent.hpp>)
EPMODELOBJECT_WRAP(AirConditionerVariableRefrigerantFlowFluidTemperatureControl, <epmodel/HVACComponent/AirConditionerVariableRefrigerantFlowFluidTemperatureControl.hpp>)
EPMODELOBJECT_WRAP(AirConditionerVariableRefrigerantFlowFluidTemperatureControlHR, <epmodel/HVACComponent/AirConditionerVariableRefrigerantFlowFluidTemperatureControlHR.hpp>)
EPMODELOBJECT_WRAP(ControllerWaterCoil, <epmodel/HVACComponent/ControllerWaterCoil.hpp>)
EPMODELOBJECT_WRAP(AirLoopHVACOutdoorAirSystem, <epmodel/HVACComponent/AirLoopHVACOutdoorAirSystem.hpp>)
EPMODELOBJECT_WRAP(ThermalZone, <epmodel/HVACComponent/ThermalZone.hpp>)

#endif
