#require '/usr/local/openstudio-3.10.0/Ruby/openstudio'

include OpenStudio::Model

m = Model.new

efcss = EvaporativeFluidCoolerSingleSpeed.new(m)
# Field before insertion
efcss.setPerformanceInputMethod("StandardDesignCapacity")
# Field after insertion, also last field
efcss.setStandardDesignCapacity(123.0)
# New required field
efcss.setDesignEnteringAirWetbulbTemperature(26.6)

efcts = EvaporativeFluidCoolerTwoSpeed.new(m)
# New required field
efcts.setDesignEnteringWaterTemperature(150.0)

m.save('test_vt_EvaporativeFluidCooler.osm', true)
