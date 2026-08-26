#require '/usr/local/openstudio-3.11.0/Ruby/openstudio'

include OpenStudio::Model

m = Model.new

brce = ZoneHVACBaseboardRadiantConvectiveElectric.new(m)
brce.setFractionofRadiantEnergyIncidentonPeople(0.31);

brcw = ZoneHVACBaseboardRadiantConvectiveWater.new(m)
brcw.setFractionofRadiantEnergyIncidentonPeople(0.32);

cprcw = ZoneHVACCoolingPanelRadiantConvectiveWater.new(m)
cprcw.setFractionofRadiantEnergyIncidentonPeople(0.33);

m.save('test_vt_ZoneHVACRadiantConvective.osm', true)
