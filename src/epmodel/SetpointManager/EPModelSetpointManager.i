#ifndef EPMODEL_SetpointManager_I
#define EPMODEL_SetpointManager_I

#ifdef SWIGPYTHON
  %module openstudioepmodelsetpointmanager
#endif

%include <epmodel/EPModel_Common_Include.i>
%import <epmodel/EPModel.i>
%import <epmodel/HVACComponent/EPModelHVACComponent.i>

EPMODELOBJECT_WRAP(SetpointManager, <epmodel/SetpointManager/SetpointManager.hpp>, 0, 0)
EPMODELOBJECT_WRAP(SetpointManagerColdest, <epmodel/SetpointManager/SetpointManagerColdest.hpp>, 0, 1)
EPMODELOBJECT_WRAP(SetpointManagerFollowGroundTemperature, <epmodel/SetpointManager/SetpointManagerFollowGroundTemperature.hpp>, 0, 1)
EPMODELOBJECT_WRAP(SetpointManagerFollowOutdoorAirTemperature, <epmodel/SetpointManager/SetpointManagerFollowOutdoorAirTemperature.hpp>, 0, 1)
EPMODELOBJECT_WRAP(SetpointManagerOutdoorAirPretreat, <epmodel/SetpointManager/SetpointManagerOutdoorAirPretreat.hpp>, 0, 1)
EPMODELOBJECT_WRAP(SetpointManagerOutdoorAirReset, <epmodel/SetpointManager/SetpointManagerOutdoorAirReset.hpp>, 0, 1)
EPMODELOBJECT_WRAP(SetpointManagerFollowSystemNodeTemperature, <epmodel/SetpointManager/SetpointManagerFollowSystemNodeTemperature.hpp>, 0, 1)
EPMODELOBJECT_WRAP(SetpointManagerSystemNodeResetHumidity, <epmodel/SetpointManager/SetpointManagerSystemNodeResetHumidity.hpp>, 0, 1)
EPMODELOBJECT_WRAP(SetpointManagerSystemNodeResetTemperature, <epmodel/SetpointManager/SetpointManagerSystemNodeResetTemperature.hpp>, 0, 1)
EPMODELOBJECT_WRAP(SetpointManagerWarmest, <epmodel/SetpointManager/SetpointManagerWarmest.hpp>, 0, 1)
EPMODELOBJECT_WRAP(SetpointManagerWarmestTemperatureFlow, <epmodel/SetpointManager/SetpointManagerWarmestTemperatureFlow.hpp>, 0, 1)
EPMODELOBJECT_WRAP(SetpointManagerMultiZoneCoolingAverage, <epmodel/SetpointManager/SetpointManagerMultiZoneCoolingAverage.hpp>, 0, 1)
EPMODELOBJECT_WRAP(SetpointManagerMultiZoneHeatingAverage, <epmodel/SetpointManager/SetpointManagerMultiZoneHeatingAverage.hpp>, 0, 1)
EPMODELOBJECT_WRAP(SetpointManagerMultiZoneMaximumHumidityAverage, <epmodel/SetpointManager/SetpointManagerMultiZoneMaximumHumidityAverage.hpp>, 0, 1)
EPMODELOBJECT_WRAP(SetpointManagerMultiZoneMinimumHumidityAverage, <epmodel/SetpointManager/SetpointManagerMultiZoneMinimumHumidityAverage.hpp>, 0, 1)
EPMODELOBJECT_WRAP(SetpointManagerMultiZoneHumidityMaximum, <epmodel/SetpointManager/SetpointManagerMultiZoneHumidityMaximum.hpp>, 0, 1)
EPMODELOBJECT_WRAP(SetpointManagerMultiZoneHumidityMinimum, <epmodel/SetpointManager/SetpointManagerMultiZoneHumidityMinimum.hpp>, 0, 1)
EPMODELOBJECT_WRAP(SetpointManagerMixedAir, <epmodel/SetpointManager/SetpointManagerMixedAir.hpp>, 0, 1)
EPMODELOBJECT_WRAP(SetpointManagerScheduled, <epmodel/SetpointManager/SetpointManagerScheduled.hpp>, 0, 1)
EPMODELOBJECT_WRAP(SetpointManagerScheduledDualSetpoint, <epmodel/SetpointManager/SetpointManagerScheduledDualSetpoint.hpp>, 0, 1)
EPMODELOBJECT_WRAP(SetpointManagerSingleZoneCooling, <epmodel/SetpointManager/SetpointManagerSingleZoneCooling.hpp>, 0, 1)
EPMODELOBJECT_WRAP(SetpointManagerSingleZoneOneStageCooling, <epmodel/SetpointManager/SetpointManagerSingleZoneOneStageCooling.hpp>, 0, 1)
EPMODELOBJECT_WRAP(SetpointManagerSingleZoneOneStageHeating, <epmodel/SetpointManager/SetpointManagerSingleZoneOneStageHeating.hpp>, 0, 1)
EPMODELOBJECT_WRAP(SetpointManagerSingleZoneHeating, <epmodel/SetpointManager/SetpointManagerSingleZoneHeating.hpp>, 0, 1)
EPMODELOBJECT_WRAP(SetpointManagerSingleZoneHumidityMaximum, <epmodel/SetpointManager/SetpointManagerSingleZoneHumidityMaximum.hpp>, 0, 1)
EPMODELOBJECT_WRAP(SetpointManagerSingleZoneHumidityMinimum, <epmodel/SetpointManager/SetpointManagerSingleZoneHumidityMinimum.hpp>, 0, 1)
EPMODELOBJECT_WRAP(SetpointManagerSingleZoneReheat, <epmodel/SetpointManager/SetpointManagerSingleZoneReheat.hpp>, 0, 1)

#endif
