#ifndef EPMODEL_AirToAirComponent_I
#define EPMODEL_AirToAirComponent_I

#ifdef SWIGPYTHON
  %module openstudioepmodelairtoaircomponent
#endif

%include <epmodel/EPModel_Common_Include.i>
%import <epmodel/EPModel.i>
%import <epmodel/HVACComponent/EPModelHVACComponent.i>

EPMODELOBJECT_WRAP(AirToAirComponent, <epmodel/AirToAirComponent/AirToAirComponent.hpp>, 0, 0)
EPMODELOBJECT_WRAP(HeatExchangerAirToAirSensibleAndLatent, <epmodel/AirToAirComponent/HeatExchangerAirToAirSensibleAndLatent.hpp>, 0, 1)
EPMODELOBJECT_WRAP(HeatExchangerDesiccantBalancedFlow, <epmodel/AirToAirComponent/HeatExchangerDesiccantBalancedFlow.hpp>, 0, 1)

#endif
