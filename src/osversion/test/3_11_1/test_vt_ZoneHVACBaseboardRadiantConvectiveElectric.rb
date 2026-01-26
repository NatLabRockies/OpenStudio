#require '/usr/local/openstudio-3.11.0/Ruby/openstudio'

include OpenStudio::Model

m = Model.new

brce = ZoneHVACBaseboardRadiantConvectiveElectric.new(m)
brce.setFractionofRadiantEnergyIncidentonPeople(0.31);

m.save('test_vt_ZoneHVACBaseboardRadiantConvectiveElectric.osm', true)
