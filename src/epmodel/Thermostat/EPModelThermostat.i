#ifndef EPMODEL_Thermostat_I
#define EPMODEL_Thermostat_I

#ifdef SWIGPYTHON
  %module openstudioepmodelthermostat
#endif

%include <epmodel/EPModel_Common_Include.i>
%import <epmodel/EPModel.i>

EPMODELOBJECT_WRAP(Thermostat, <epmodel/Thermostat/Thermostat.hpp>)
EPMODELOBJECT_WRAP(ThermostatSetpointDualSetpoint, <epmodel/Thermostat/ThermostatSetpointDualSetpoint.hpp>)
EPMODELOBJECT_WRAP(ZoneControlThermostatStagedDualSetpoint, <epmodel/Thermostat/ZoneControlThermostatStagedDualSetpoint.hpp>)

#endif
