#require '/usr/local/openstudio-3.10.0/Ruby/openstudio'

include OpenStudio::Model

m = Model.new

ocf = m.getOutputControlFiles

m.save('test_vt_OutputControlFiles.osm', true)
