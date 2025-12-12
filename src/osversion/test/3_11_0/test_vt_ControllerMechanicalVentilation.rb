#require '/usr/local/openstudio-3.10.0/Ruby/openstudio'

include OpenStudio::Model

m = Model.new

controller_mv = ControllerMechanicalVentilation.new(m)
controller_mv.setSystemOutdoorAirMethod("ProportionalControl")

m.save('test_vt_ControllerMechanicalVentilation.osm', true)
