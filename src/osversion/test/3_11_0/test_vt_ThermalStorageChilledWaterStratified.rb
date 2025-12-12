#require '/usr/local/openstudio-3.10.0/Ruby/openstudio'

include OpenStudio::Model

m = Model.new

ts = ThermalStorageChilledWaterStratified.new(m)

m.save('test_vt_ThermalStorageChilledWaterStratified.osm', true)
