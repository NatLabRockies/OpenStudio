#require '/usr/local/openstudio-3.10.0/Ruby/openstudio'

include OpenStudio::Model

m = Model.new

htg = HeatPumpAirToWaterFuelFiredHeating.new(m)
clg = HeatPumpAirToWaterFuelFiredCooling.new(m)

m.save('test_vt_HeatPumpAirToWaterFuelFired.osm', true)
