#ifndef EPMODEL_WaterToAirComponent_I
#define EPMODEL_WaterToAirComponent_I

#ifdef SWIGPYTHON
  %module openstudioepmodelwatertoaircomponent
#endif

%include <epmodel/EPModel_Common_Include.i>
%import <epmodel/EPModel.i>
%import <epmodel/HVACComponent/EPModelHVACComponent.i>

EPMODELOBJECT_WRAP(CoilWaterHeatingAirToWaterHeatPumpVariableSpeed, <epmodel/WaterToAirComponent/CoilWaterHeatingAirToWaterHeatPumpVariableSpeed.hpp>, 0, 1)
EPMODELOBJECT_WRAP(CoilWaterHeatingAirToWaterHeatPump, <epmodel/WaterToAirComponent/CoilWaterHeatingAirToWaterHeatPump.hpp>, 0, 1)
EPMODELOBJECT_WRAP(WaterToAirComponent, <epmodel/WaterToAirComponent/WaterToAirComponent.hpp>, 0, 0)
EPMODELOBJECT_WRAP(CoilCoolingWater, <epmodel/WaterToAirComponent/CoilCoolingWater.hpp>, 0, 1)
EPMODELOBJECT_WRAP(CoilHeatingWater, <epmodel/WaterToAirComponent/CoilHeatingWater.hpp>, 0, 1)
EPMODELOBJECT_WRAP(CoilCoolingWaterToAirHeatPumpEquationFit, <epmodel/WaterToAirComponent/CoilCoolingWaterToAirHeatPumpEquationFit.hpp>, 0, 1)
EPMODELOBJECT_WRAP(CoilHeatingWaterToAirHeatPumpEquationFit, <epmodel/WaterToAirComponent/CoilHeatingWaterToAirHeatPumpEquationFit.hpp>, 0, 1)
EPMODELOBJECT_WRAP(CoilCoolingWaterToAirHeatPumpVariableSpeedEquationFit, <epmodel/WaterToAirComponent/CoilCoolingWaterToAirHeatPumpVariableSpeedEquationFit.hpp>, 0, 1)
EPMODELOBJECT_WRAP(CoilHeatingWaterToAirHeatPumpVariableSpeedEquationFit, <epmodel/WaterToAirComponent/CoilHeatingWaterToAirHeatPumpVariableSpeedEquationFit.hpp>, 0, 1)
EPMODELOBJECT_WRAP(CoilUserDefined, <epmodel/WaterToAirComponent/CoilUserDefined.hpp>, 0, 1)

#endif
