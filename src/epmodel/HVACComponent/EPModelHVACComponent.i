#ifndef EPMODEL_HVACComponent_I
#define EPMODEL_HVACComponent_I

#ifdef SWIGPYTHON
  %module openstudioepmodelhvaccomponent
#endif

%include <epmodel/EPModel_Common_Include.i>
%import <epmodel/EPModel.i>
%import <epmodel/ParentObject/EPModelParentObject.i>

EPMODELOBJECT_WRAP(HVACComponent, <epmodel/HVACComponent/HVACComponent.hpp>, 0, 0)
EPMODELOBJECT_WRAP(AirConditionerVariableRefrigerantFlowFluidTemperatureControl, <epmodel/HVACComponent/AirConditionerVariableRefrigerantFlowFluidTemperatureControl.hpp>, 0, 1)
EPMODELOBJECT_WRAP(AirConditionerVariableRefrigerantFlowFluidTemperatureControlHR, <epmodel/HVACComponent/AirConditionerVariableRefrigerantFlowFluidTemperatureControlHR.hpp>, 0, 1)
EPMODELOBJECT_WRAP(ControllerWaterCoil, <epmodel/HVACComponent/ControllerWaterCoil.hpp>, 0, 1)
EPMODELOBJECT_WRAP(AirLoopHVACOutdoorAirSystem, <epmodel/HVACComponent/AirLoopHVACOutdoorAirSystem.hpp>, 0, 1)
EPMODELOBJECT_WRAP(ThermalZone, <epmodel/HVACComponent/ThermalZone.hpp>, 0, 1)

#endif
