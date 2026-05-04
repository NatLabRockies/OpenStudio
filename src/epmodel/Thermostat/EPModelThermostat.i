#ifndef EPMODEL_Thermostat_I
#define EPMODEL_Thermostat_I

#ifdef SWIGPYTHON
  %module openstudioepmodelthermostat
#endif

%include <epmodel/EPModel_Common_Include.i>
%import <epmodel/EPModel.i>

EPMODELOBJECT_WRAP(Thermostat, <epmodel/Thermostat/Thermostat.hpp>, 0, 0)
EPMODELOBJECT_WRAP(ThermostatSetpointDualSetpoint, <epmodel/Thermostat/ThermostatSetpointDualSetpoint.hpp>, 0, 1)
EPMODELOBJECT_WRAP(ZoneControlThermostatStagedDualSetpoint, <epmodel/Thermostat/ZoneControlThermostatStagedDualSetpoint.hpp>, 0, 1)

#endif
