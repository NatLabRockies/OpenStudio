#require '/usr/local/openstudio-3.11.0/Ruby/openstudio'

include OpenStudio::Model

m = Model.new

central_hp = CentralHeatPumpSystem.new(m)
central_hp.setName('Central Heat Pump System 1')
central_hp.setAncillaryPower(500)

chp_module = CentralHeatPumpSystemModule.new(m)
central_hp.addModule(chp_module)

eir = chp_module.chillerHeaterModulesPerformanceComponent
eir.setName('Chiller Heater Performance Electric EIR 1')

# Wire up a real Cooling Loop so the field right after the removed
# 'Control Method' (Cooling Loop Inlet Node Name) has real content too
plant_loop = PlantLoop.new(m)
plant_loop.addSupplyBranchForComponent(central_hp)

central_hp.supplyInletModelObject.get.setName('Central Heat Pump System Cooling Inlet Node')
central_hp.supplyOutletModelObject.get.setName('Central Heat Pump System Cooling Outlet Node')

m.save('test_vt_CentralHeatPumpSystem.osm', true)
