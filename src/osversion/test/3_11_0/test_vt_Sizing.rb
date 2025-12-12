#require '/usr/local/openstudio-3.4.0/Ruby/openstudio'

include OpenStudio::Model

m = Model.new
z = ThermalZone.new(m)
sz = z.sizingZone

a = AirLoopHVAC.new(m)
ss = a.sizingSystem

m.save('test_vt_Sizing.osm', true)
