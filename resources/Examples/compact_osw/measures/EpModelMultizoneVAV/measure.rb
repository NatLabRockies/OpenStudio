class EpModelMultizoneVAV < OpenStudio::Measure::ModelMeasure
  SYSTEM_PREFIX = 'EpModel Multizone VAV'

  def name
    return SYSTEM_PREFIX
  end

  def description
    return 'Replace existing air loops with one multizone VAV system served by central hot water and chilled water plants.'
  end

  def modeler_description
    return 'Finds zones served by existing AirLoopHVAC objects, removes those air loops, and reconnects the zones to a new multizone air system with water heating, water cooling, a boiler hot water loop, and an air-cooled chiller chilled water loop.'
  end

  def arguments(model)
    return OpenStudio::Measure::OSArgumentVector.new
  end

  def build_hot_water_loop(model)
    hot_water_schedule = OpenStudio::EPModel::ScheduleConstant.new(model)
    hot_water_schedule.setName("#{SYSTEM_PREFIX} Hot Water Setpoint")
    hot_water_schedule.setValue(82.0)

    loop = OpenStudio::EPModel::PlantLoop.new(model)
    loop.sizingPlant.setLoopType('Heating')
    loop.sizingPlant.setDesignLoopExitTemperature(82.0)
    loop.sizingPlant.setLoopDesignTemperatureDifference(11.0)

    pump = OpenStudio::EPModel::PumpVariableSpeed.new(model)
    pump.setName("#{SYSTEM_PREFIX} Hot Water Pump")
    pump.addToNode(loop.supplyInletNode)

    boiler = OpenStudio::EPModel::BoilerHotWater.new(model)
    boiler.setName("#{SYSTEM_PREFIX} Hot Water Boiler")
    boiler.setFuelType('NaturalGas')
    boiler.autosizeNominalCapacity
    boiler.autosizeDesignWaterFlowRate
    loop.addSupplyBranchForComponent(boiler)

    heating_operation = OpenStudio::EPModel::PlantEquipmentOperationHeatingLoad.new(model)
    heating_operation.setName("#{SYSTEM_PREFIX} Hot Water Heating Operation Scheme")
    heating_operation.addEquipment(boiler)
    loop.setPlantEquipmentOperationHeatingLoad(heating_operation)

    supply_bypass = OpenStudio::EPModel::PipeAdiabatic.new(model)
    supply_bypass.setName("#{SYSTEM_PREFIX} Hot Water Supply Bypass")
    loop.addSupplyBranchForComponent(supply_bypass)

    supply_outlet_pipe = OpenStudio::EPModel::PipeAdiabatic.new(model)
    supply_outlet_pipe.setName("#{SYSTEM_PREFIX} Hot Water Supply Outlet Pipe")
    supply_outlet_pipe.addToNode(loop.supplyOutletNode)

    demand_inlet_pipe = OpenStudio::EPModel::PipeAdiabatic.new(model)
    demand_inlet_pipe.setName("#{SYSTEM_PREFIX} Hot Water Demand Inlet Pipe")
    demand_inlet_pipe.addToNode(loop.demandInletNode)

    demand_bypass = OpenStudio::EPModel::PipeAdiabatic.new(model)
    demand_bypass.setName("#{SYSTEM_PREFIX} Hot Water Demand Bypass")
    loop.addDemandBranchForComponent(demand_bypass)

    demand_outlet_pipe = OpenStudio::EPModel::PipeAdiabatic.new(model)
    demand_outlet_pipe.setName("#{SYSTEM_PREFIX} Hot Water Demand Outlet Pipe")
    demand_outlet_pipe.addToNode(loop.demandOutletNode)

    spm = OpenStudio::EPModel::SetpointManagerScheduled.new(model)
    spm.setName("#{SYSTEM_PREFIX} Hot Water Setpoint Manager")
    spm.setSchedule(hot_water_schedule)
    spm.addToNode(loop.supplyOutletNode)
    loop.setLoopTemperatureSetpointNode(loop.supplyOutletNode) if loop.respond_to?(:setLoopTemperatureSetpointNode)

    loop
  end

  def build_chilled_water_loop(model)
    chilled_water_schedule = OpenStudio::EPModel::ScheduleConstant.new(model)
    chilled_water_schedule.setName("#{SYSTEM_PREFIX} Chilled Water Setpoint")
    chilled_water_schedule.setValue(7.22)

    loop = OpenStudio::EPModel::PlantLoop.new(model)
    loop.sizingPlant.setLoopType('Cooling')
    loop.sizingPlant.setDesignLoopExitTemperature(7.22)
    loop.sizingPlant.setLoopDesignTemperatureDifference(6.67)

    pump = OpenStudio::EPModel::PumpVariableSpeed.new(model)
    pump.setName("#{SYSTEM_PREFIX} Chilled Water Pump")
    pump.addToNode(loop.supplyInletNode)

    chiller = OpenStudio::EPModel::ChillerElectricEIR.new(model)
    chiller.setName("#{SYSTEM_PREFIX} Air-Cooled Chiller")
    loop.addSupplyBranchForComponent(chiller)

    cooling_operation = OpenStudio::EPModel::PlantEquipmentOperationCoolingLoad.new(model)
    cooling_operation.setName("#{SYSTEM_PREFIX} Chilled Water Cooling Operation Scheme")
    cooling_operation.addEquipment(chiller)
    loop.setPlantEquipmentOperationCoolingLoad(cooling_operation)

    supply_bypass = OpenStudio::EPModel::PipeAdiabatic.new(model)
    supply_bypass.setName("#{SYSTEM_PREFIX} Chilled Water Supply Bypass")
    loop.addSupplyBranchForComponent(supply_bypass)

    supply_outlet_pipe = OpenStudio::EPModel::PipeAdiabatic.new(model)
    supply_outlet_pipe.setName("#{SYSTEM_PREFIX} Chilled Water Supply Outlet Pipe")
    supply_outlet_pipe.addToNode(loop.supplyOutletNode)

    demand_inlet_pipe = OpenStudio::EPModel::PipeAdiabatic.new(model)
    demand_inlet_pipe.setName("#{SYSTEM_PREFIX} Chilled Water Demand Inlet Pipe")
    demand_inlet_pipe.addToNode(loop.demandInletNode)

    demand_bypass = OpenStudio::EPModel::PipeAdiabatic.new(model)
    demand_bypass.setName("#{SYSTEM_PREFIX} Chilled Water Demand Bypass")
    loop.addDemandBranchForComponent(demand_bypass)

    demand_outlet_pipe = OpenStudio::EPModel::PipeAdiabatic.new(model)
    demand_outlet_pipe.setName("#{SYSTEM_PREFIX} Chilled Water Demand Outlet Pipe")
    demand_outlet_pipe.addToNode(loop.demandOutletNode)

    spm = OpenStudio::EPModel::SetpointManagerScheduled.new(model)
    spm.setName("#{SYSTEM_PREFIX} Chilled Water Setpoint Manager")
    spm.setSchedule(chilled_water_schedule)
    spm.addToNode(loop.supplyOutletNode)
    loop.setLoopTemperatureSetpointNode(loop.supplyOutletNode) if loop.respond_to?(:setLoopTemperatureSetpointNode)

    loop
  end

  def build_multizone_air_loop(model, hot_water_loop, chilled_water_loop)
    deck_schedule = OpenStudio::EPModel::ScheduleConstant.new(model)
    deck_schedule.setName("#{SYSTEM_PREFIX} Deck Air Setpoint")
    deck_schedule.setValue(12.8)

    air_loop = OpenStudio::EPModel::AirLoopHVAC.new(model)
    air_loop.setName("#{SYSTEM_PREFIX} System")

    sizing_system = air_loop.sizingSystem
    sizing_system.setCentralCoolingDesignSupplyAirTemperature(12.8)
    sizing_system.setCentralHeatingDesignSupplyAirTemperature(16.7)
    sizing_system.setTypeofLoadtoSizeOn('Sensible') if sizing_system.respond_to?(:setTypeofLoadtoSizeOn)

    outdoor_air_system = OpenStudio::EPModel::AirLoopHVACOutdoorAirSystem.new(model)
    outdoor_air_system.setName("#{SYSTEM_PREFIX} Outdoor Air System")
    controller = outdoor_air_system.getControllerOutdoorAir
    controller.setName("#{SYSTEM_PREFIX} Outdoor Air Controller")

    cooling_coil = OpenStudio::EPModel::CoilCoolingWater.new(model)
    cooling_coil.setName("#{SYSTEM_PREFIX} Central Cooling Coil")
    cooling_coil.autosizeDesignWaterFlowRate
    cooling_coil.autosizeDesignAirFlowRate

    heating_coil = OpenStudio::EPModel::CoilHeatingWater.new(model)
    heating_coil.setName("#{SYSTEM_PREFIX} Central Heating Coil")

    fan = OpenStudio::EPModel::FanVariableVolume.new(model)
    fan.setName("#{SYSTEM_PREFIX} Supply Fan")

    supply_outlet_node = air_loop.supplyOutletNode
    outdoor_air_system.addToNode(supply_outlet_node)
    cooling_coil.addToNode(supply_outlet_node)
    heating_coil.addToNode(supply_outlet_node)
    fan.addToNode(supply_outlet_node)

    chilled_water_loop.addDemandBranchForComponent(cooling_coil)
    hot_water_loop.addDemandBranchForComponent(heating_coil)
    spm = OpenStudio::EPModel::SetpointManagerScheduled.new(model)
    spm.setName("#{SYSTEM_PREFIX} Deck Air Setpoint Manager")
    spm.setSchedule(deck_schedule)
    spm.addToNode(supply_outlet_node)

    cooling_coil_outlet_spm = OpenStudio::EPModel::SetpointManagerScheduled.new(model)
    cooling_coil_outlet_spm.setName("#{SYSTEM_PREFIX} Cooling Coil Outlet Setpoint Manager")
    cooling_coil_outlet_spm.setSchedule(deck_schedule)
    cooling_coil_outlet_spm.addToNode(heating_coil.airInletModelObject.get.to_Node.get)

    heating_coil_outlet_spm = OpenStudio::EPModel::SetpointManagerScheduled.new(model)
    heating_coil_outlet_spm.setName("#{SYSTEM_PREFIX} Heating Coil Outlet Setpoint Manager")
    heating_coil_outlet_spm.setSchedule(deck_schedule)
    heating_coil_outlet_spm.addToNode(fan.inletModelObject.get.to_Node.get)

    return air_loop
  end

  def run(model, runner, user_arguments)
    super(model, runner, user_arguments)

    if !runner.validateUserArguments(arguments(model), user_arguments)
      return false
    end

    zones = []
    air_loops = model.getAirLoopHVACs()
    air_loops.each do |loop|
      zones.concat(loop.thermalZones())
      loop.remove()
    end

    hot_water_loop = build_hot_water_loop(model)
    chilled_water_loop = build_chilled_water_loop(model)
    hot_water_loop.setName("#{SYSTEM_PREFIX} Hot Water Loop")
    chilled_water_loop.setName("#{SYSTEM_PREFIX} Chilled Water Loop")
    air_loop = build_multizone_air_loop(model, hot_water_loop, chilled_water_loop)

    zones.each do |zone|
      reheat_coil = OpenStudio::EPModel::CoilHeatingWater.new(model)
      reheat_coil.setName("#{zone.nameString} Reheat Coil")
      hot_water_loop.addDemandBranchForComponent(reheat_coil)

      terminal = OpenStudio::EPModel::AirTerminalSingleDuctVAVReheat.new(model)
      terminal.setName("#{zone.nameString} VAV Reheat Terminal")
      terminal.setReheatCoil(reheat_coil)
      air_loop.addBranchForZone(zone, terminal)
    end

    runner.registerFinalCondition("Removed #{air_loops.size} AirLoopHVAC object(s), created one multizone VAV air system, and reattached #{zones.size} zone(s) with boiler hot water and chilled water plant service.")
    return true
  end
end

EpModelMultizoneVAV.new.registerWithApplication
