#require '/usr/local/openstudio-3.11.0/Ruby/openstudio'

include OpenStudio::Model

m = Model.new

operatingMode = CoilCoolingDXCurveFitOperatingMode.new(m)
operatingMode.setName('Coil Cooling DX Curve Fit Operating Mode 1')
operatingMode.setApplyLatentDegradationtoSpeedsGreaterthan1(true)

m.save('test_vt_CoilCoolingDXCurveFitOperatingMode.osm', true)
