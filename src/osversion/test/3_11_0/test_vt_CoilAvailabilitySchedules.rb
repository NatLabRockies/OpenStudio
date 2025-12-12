#require '/usr/local/openstudio-3.10.0/Ruby/openstudio'

include OpenStudio::Model

m = Model.new

coil = CoilCoolingDXVariableSpeed.new(m)
coil = CoilHeatingDXVariableSpeed.new(m)
coil = CoilCoolingWaterToAirHeatPumpEquationFit.new(m)
coil = CoilHeatingWaterToAirHeatPumpEquationFit.new(m)
coil = CoilCoolingWaterToAirHeatPumpVariableSpeedEquationFit.new(m)
coil = CoilHeatingWaterToAirHeatPumpVariableSpeedEquationFit.new(m)
coil = CoilWaterHeatingAirToWaterHeatPump.new(m)
coil = CoilWaterHeatingAirToWaterHeatPumpWrapped.new(m)
coil = CoilWaterHeatingAirToWaterHeatPumpVariableSpeed.new(m)

m.save('test_vt_CoilAvailabilitySchedules.osm', true)
