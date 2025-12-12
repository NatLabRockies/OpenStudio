#require '/usr/local/openstudio-3.10.0/Ruby/openstudio'

include OpenStudio::Model

m = Model.new

alwaysOn = m.alwaysOnDiscreteSchedule

htg_coil = CoilHeatingDXSingleSpeed.new(m)
clg_coil = CoilCoolingDXSingleSpeed.new(m)
supp_htg_coil = CoilHeatingElectric.new(m, alwaysOn)
fan = FanOnOff.new(m, alwaysOn)
pthp = ZoneHVACPackagedTerminalHeatPump.new(m, alwaysOn, fan, htg_coil, clg_coil, supp_htg_coil)

fan = FanOnOff.new(m, alwaysOn)
heating_coil = CoilHeatingWaterToAirHeatPumpEquationFit.new(m)
cooling_coil = CoilCoolingWaterToAirHeatPumpEquationFit.new(m)
supp_heating_coil = CoilHeatingElectric.new(m, alwaysOn)
wahp = ZoneHVACWaterToAirHeatPump.new(m, alwaysOn, fan, heating_coil, cooling_coil, supp_heating_coil)

fan = FanOnOff.new(m, alwaysOn)
clg_coil = CoilCoolingDXSingleSpeed.new(m)
htg_coil = CoilHeatingDXSingleSpeed.new(m)
sup_htg_coil = CoilHeatingElectric.new(m, alwaysOn)
unitary = AirLoopHVACUnitaryHeatPumpAirToAir.new(m, alwaysOn, fan, htg_coil, clg_coil, sup_htg_coil)

fan = FanConstantVolume.new(m, alwaysOn)
heat = CoilHeatingElectricMultiStage.new(m)
cool = CoilCoolingDXMultiSpeed.new(m)
supp_heat = CoilHeatingElectric.new(m, alwaysOn)
unitary = AirLoopHVACUnitaryHeatPumpAirToAirMultiSpeed.new(m, fan, heat, cool, supp_heat)

m.save('test_vt_DXHeatingCoilSizingRatio.osm', true)
