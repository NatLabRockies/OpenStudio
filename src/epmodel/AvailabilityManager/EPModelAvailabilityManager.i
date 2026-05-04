#ifndef EPMODEL_AvailabilityManager_I
#define EPMODEL_AvailabilityManager_I

#ifdef SWIGPYTHON
  %module openstudioepmodelavailabilitymanager
#endif

%include <epmodel/EPModel_Common_Include.i>
%import <epmodel/EPModel.i>

EPMODELOBJECT_WRAP(AvailabilityManagerDifferentialThermostat, <epmodel/AvailabilityManager/AvailabilityManagerDifferentialThermostat.hpp>, 0, 1)
EPMODELOBJECT_WRAP(AvailabilityManagerHighTemperatureTurnOff, <epmodel/AvailabilityManager/AvailabilityManagerHighTemperatureTurnOff.hpp>, 0, 1)
EPMODELOBJECT_WRAP(AvailabilityManagerHighTemperatureTurnOn, <epmodel/AvailabilityManager/AvailabilityManagerHighTemperatureTurnOn.hpp>, 0, 1)
EPMODELOBJECT_WRAP(AvailabilityManagerLowTemperatureTurnOff, <epmodel/AvailabilityManager/AvailabilityManagerLowTemperatureTurnOff.hpp>, 0, 1)
EPMODELOBJECT_WRAP(AvailabilityManagerLowTemperatureTurnOn, <epmodel/AvailabilityManager/AvailabilityManagerLowTemperatureTurnOn.hpp>, 0, 1)
EPMODELOBJECT_WRAP(AvailabilityManagerHybridVentilation, <epmodel/AvailabilityManager/AvailabilityManagerHybridVentilation.hpp>, 0, 1)
EPMODELOBJECT_WRAP(AvailabilityManagerNightVentilation, <epmodel/AvailabilityManager/AvailabilityManagerNightVentilation.hpp>, 0, 1)
EPMODELOBJECT_WRAP(AvailabilityManagerOptimumStart, <epmodel/AvailabilityManager/AvailabilityManagerOptimumStart.hpp>, 0, 1)
EPMODELOBJECT_WRAP(AvailabilityManagerScheduledOff, <epmodel/AvailabilityManager/AvailabilityManagerScheduledOff.hpp>, 0, 1)
EPMODELOBJECT_WRAP(AvailabilityManagerScheduledOn, <epmodel/AvailabilityManager/AvailabilityManagerScheduledOn.hpp>, 0, 1)
EPMODELOBJECT_WRAP(AvailabilityManager, <epmodel/AvailabilityManager/AvailabilityManager.hpp>, 0, 0)
EPMODELOBJECT_WRAP(AvailabilityManagerNightCycle, <epmodel/AvailabilityManager/AvailabilityManagerNightCycle.hpp>, 0, 1)

#endif
