#require '/usr/local/openstudio-3.10.0/Ruby/openstudio'

include OpenStudio::Model

m = Model.new

mains = m.getSiteWaterMainsTemperature

m.save('test_vt_SiteWaterMainsTemperature.osm', true)
