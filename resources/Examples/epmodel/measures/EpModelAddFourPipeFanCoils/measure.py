import openstudio


class EpModelAddFourPipeFanCoils(openstudio.measure.ModelMeasure):
    SYSTEM_PREFIX = "EPModel Four-Pipe Fan Coils"
    AIR_FLOW_RATE = 0.45
    CHILLED_WATER_FLOW_RATE = 0.00042
    HOT_WATER_FLOW_RATE = 0.00020

    def name(self):
        return "EPModel Add Four-Pipe Fan Coils"

    def description(self):
        return "Serve every thermostatically controlled zone with a direct four-pipe fan coil on shared hot-water and chilled-water loops."

    def modeler_description(self):
        return (
            "Exercises direct zone ownership, contained fan and water-coil air paths, shared plant demand branches, "
            "and explicit fan-coil sizing without an AirLoopHVAC."
        )

    def arguments(self, model=None):
        return openstudio.measure.OSArgumentVector()

    @staticmethod
    def require_condition(runner, condition, message):
        if condition:
            return True

        runner.registerError(message)
        return False

    @staticmethod
    def node_handle(model_object):
        if model_object.is_initialized() and model_object.get().to_Node().is_initialized():
            return model_object.get().to_Node().get().handle()
        return None

    def add_common_loop_pipes(self, model, runner, loop, prefix):
        supply_bypass = openstudio.epmodel.PipeAdiabatic(model)
        supply_bypass.setName(f"{prefix} Supply Bypass")
        if not self.require_condition(
            runner,
            loop.addSupplyBranchForComponent(supply_bypass),
            f"Could not add the {prefix} supply bypass.",
        ):
            return False

        supply_outlet_pipe = openstudio.epmodel.PipeAdiabatic(model)
        supply_outlet_pipe.setName(f"{prefix} Supply Outlet Pipe")
        if not self.require_condition(
            runner,
            supply_outlet_pipe.addToNode(loop.supplyOutletNode()),
            f"Could not add the {prefix} supply outlet pipe.",
        ):
            return False

        demand_inlet_pipe = openstudio.epmodel.PipeAdiabatic(model)
        demand_inlet_pipe.setName(f"{prefix} Demand Inlet Pipe")
        if not self.require_condition(
            runner,
            demand_inlet_pipe.addToNode(loop.demandInletNode()),
            f"Could not add the {prefix} demand inlet pipe.",
        ):
            return False

        demand_bypass = openstudio.epmodel.PipeAdiabatic(model)
        demand_bypass.setName(f"{prefix} Demand Bypass")
        if not self.require_condition(
            runner,
            loop.addDemandBranchForComponent(demand_bypass),
            f"Could not add the {prefix} demand bypass.",
        ):
            return False

        demand_outlet_pipe = openstudio.epmodel.PipeAdiabatic(model)
        demand_outlet_pipe.setName(f"{prefix} Demand Outlet Pipe")
        if not self.require_condition(
            runner,
            demand_outlet_pipe.addToNode(loop.demandOutletNode()),
            f"Could not add the {prefix} demand outlet pipe.",
        ):
            return False

        return True

    def build_hot_water_loop(self, model, runner, pump_zone, zone_count):
        prefix = f"{self.SYSTEM_PREFIX} Hot Water"
        loop_flow_rate = self.HOT_WATER_FLOW_RATE * zone_count * 1.25
        setpoint_schedule = openstudio.epmodel.ScheduleConstant(model)
        setpoint_schedule.setName(f"{prefix} Setpoint")
        if not self.require_condition(
            runner, setpoint_schedule.setValue(60.0), "Could not set the hot-water temperature."
        ):
            return None

        loop = openstudio.epmodel.PlantLoop(model)
        loop.setName(f"{prefix} Loop")
        if not self.require_condition(
            runner,
            loop.sizingPlant().setLoopType("Heating"),
            "Could not set the hot-water loop type.",
        ):
            return None
        if not self.require_condition(
            runner,
            loop.sizingPlant().setDesignLoopExitTemperature(60.0),
            "Could not set the hot-water design temperature.",
        ):
            return None
        if not self.require_condition(
            runner,
            loop.sizingPlant().setLoopDesignTemperatureDifference(10.0),
            "Could not set the hot-water design temperature difference.",
        ):
            return None
        if not self.require_condition(
            runner,
            loop.setMaximumLoopFlowRate(loop_flow_rate),
            "Could not set the hot-water loop flow rate.",
        ):
            return None

        pump = openstudio.epmodel.PumpVariableSpeed(model)
        pump.setName(f"{prefix} Pump")
        pump.autosizeRatedPowerConsumption()
        if not self.require_condition(
            runner, pump.setRatedFlowRate(loop_flow_rate), "Could not set the hot-water pump flow rate."
        ):
            return None
        if not self.require_condition(
            runner, pump.setRatedPumpHead(120_000.0), "Could not set the hot-water pump head."
        ):
            return None
        if not self.require_condition(
            runner, pump.setMotorEfficiency(0.90), "Could not set the hot-water pump motor efficiency."
        ):
            return None
        if not self.require_condition(
            runner, pump.setZone(pump_zone), "Could not assign the hot-water pump heat-loss zone."
        ):
            return None
        if not self.require_condition(
            runner, pump.addToNode(loop.supplyInletNode()), "Could not add the hot-water pump."
        ):
            return None

        boiler = openstudio.epmodel.BoilerHotWater(model)
        boiler.setName(f"{prefix} Boiler")
        if not self.require_condition(runner, boiler.setFuelType("NaturalGas"), "Could not set the boiler fuel type."):
            return None
        if not self.require_condition(
            runner, boiler.setNominalCapacity(10_000.0 * zone_count), "Could not set the boiler capacity."
        ):
            return None
        if not self.require_condition(
            runner,
            boiler.setDesignWaterFlowRate(loop_flow_rate),
            "Could not set the boiler water flow rate.",
        ):
            return None
        if not self.require_condition(
            runner,
            loop.addSupplyBranchForComponent(boiler),
            "Could not add the boiler supply branch.",
        ):
            return None

        operation = openstudio.epmodel.PlantEquipmentOperationHeatingLoad(model)
        operation.setName(f"{prefix} Heating Operation Scheme")
        if not self.require_condition(
            runner,
            operation.addEquipment(boiler),
            "Could not add the boiler to its operation scheme.",
        ):
            return None
        if not self.require_condition(
            runner,
            loop.setPlantEquipmentOperationHeatingLoad(operation),
            "Could not assign the hot-water operation scheme.",
        ):
            return None
        if not self.add_common_loop_pipes(model, runner, loop, prefix):
            return None

        setpoint_manager = openstudio.epmodel.SetpointManagerScheduled(model)
        setpoint_manager.setName(f"{prefix} Setpoint Manager")
        if not self.require_condition(
            runner,
            setpoint_manager.setSchedule(setpoint_schedule),
            "Could not set the hot-water setpoint-manager schedule.",
        ):
            return None
        if not self.require_condition(
            runner,
            setpoint_manager.addToNode(loop.supplyOutletNode()),
            "Could not add the hot-water setpoint manager.",
        ):
            return None
        if not self.require_condition(
            runner,
            loop.setLoopTemperatureSetpointNode(loop.supplyOutletNode()),
            "Could not set the hot-water loop setpoint node.",
        ):
            return None

        return loop

    def build_chilled_water_loop(self, model, runner, pump_zone, zone_count):
        prefix = f"{self.SYSTEM_PREFIX} Chilled Water"
        loop_flow_rate = self.CHILLED_WATER_FLOW_RATE * zone_count * 1.25
        setpoint_schedule = openstudio.epmodel.ScheduleConstant(model)
        setpoint_schedule.setName(f"{prefix} Setpoint")
        if not self.require_condition(
            runner, setpoint_schedule.setValue(7.22), "Could not set the chilled-water temperature."
        ):
            return None

        loop = openstudio.epmodel.PlantLoop(model)
        loop.setName(f"{prefix} Loop")
        if not self.require_condition(
            runner,
            loop.sizingPlant().setLoopType("Cooling"),
            "Could not set the chilled-water loop type.",
        ):
            return None
        if not self.require_condition(
            runner,
            loop.sizingPlant().setDesignLoopExitTemperature(7.22),
            "Could not set the chilled-water design temperature.",
        ):
            return None
        if not self.require_condition(
            runner,
            loop.sizingPlant().setLoopDesignTemperatureDifference(5.0),
            "Could not set the chilled-water design temperature difference.",
        ):
            return None
        if not self.require_condition(
            runner,
            loop.setMaximumLoopFlowRate(loop_flow_rate),
            "Could not set the chilled-water loop flow rate.",
        ):
            return None

        pump = openstudio.epmodel.PumpVariableSpeed(model)
        pump.setName(f"{prefix} Pump")
        pump.autosizeRatedPowerConsumption()
        if not self.require_condition(
            runner, pump.setRatedFlowRate(loop_flow_rate), "Could not set the chilled-water pump flow rate."
        ):
            return None
        if not self.require_condition(
            runner, pump.setRatedPumpHead(120_000.0), "Could not set the chilled-water pump head."
        ):
            return None
        if not self.require_condition(
            runner, pump.setMotorEfficiency(0.90), "Could not set the chilled-water pump motor efficiency."
        ):
            return None
        if not self.require_condition(
            runner,
            pump.setZone(pump_zone),
            "Could not assign the chilled-water pump heat-loss zone.",
        ):
            return None
        if not self.require_condition(
            runner, pump.addToNode(loop.supplyInletNode()), "Could not add the chilled-water pump."
        ):
            return None

        chiller = openstudio.epmodel.ChillerElectricEIR(model)
        chiller.setName(f"{prefix} Air-Cooled Chiller")
        if not self.require_condition(
            runner,
            chiller.setCondenserType("AirCooled"),
            "Could not set the chiller condenser type.",
        ):
            return None
        if not self.require_condition(
            runner, chiller.setReferenceCapacity(10_000.0 * zone_count), "Could not set the chiller capacity."
        ):
            return None
        if not self.require_condition(runner, chiller.setReferenceCOP(3.2), "Could not set the chiller COP."):
            return None
        if not self.require_condition(
            runner,
            chiller.setReferenceChilledWaterFlowRate(loop_flow_rate),
            "Could not set the chiller water flow rate.",
        ):
            return None
        if not self.require_condition(
            runner,
            loop.addSupplyBranchForComponent(chiller),
            "Could not add the chiller supply branch.",
        ):
            return None

        operation = openstudio.epmodel.PlantEquipmentOperationCoolingLoad(model)
        operation.setName(f"{prefix} Cooling Operation Scheme")
        if not self.require_condition(
            runner,
            operation.addEquipment(chiller),
            "Could not add the chiller to its operation scheme.",
        ):
            return None
        if not self.require_condition(
            runner,
            loop.setPlantEquipmentOperationCoolingLoad(operation),
            "Could not assign the chilled-water operation scheme.",
        ):
            return None
        if not self.add_common_loop_pipes(model, runner, loop, prefix):
            return None

        setpoint_manager = openstudio.epmodel.SetpointManagerScheduled(model)
        setpoint_manager.setName(f"{prefix} Setpoint Manager")
        if not self.require_condition(
            runner,
            setpoint_manager.setSchedule(setpoint_schedule),
            "Could not set the chilled-water setpoint-manager schedule.",
        ):
            return None
        if not self.require_condition(
            runner,
            setpoint_manager.addToNode(loop.supplyOutletNode()),
            "Could not add the chilled-water setpoint manager.",
        ):
            return None
        if not self.require_condition(
            runner,
            loop.setLoopTemperatureSetpointNode(loop.supplyOutletNode()),
            "Could not set the chilled-water loop setpoint node.",
        ):
            return None

        return loop

    def build_fan_coil(self, model, runner, zone, index, hot_water_loop, chilled_water_loop):
        prefix = f"{self.SYSTEM_PREFIX} {index + 1:02d}"
        schedule = model.alwaysOnDiscreteSchedule()

        fan = openstudio.epmodel.FanConstantVolume(model, schedule)
        fan.setName(f"{prefix} Fan")
        fan_settings = [
            fan.setFanTotalEfficiency(0.70),
            fan.setPressureRise(250.0),
            fan.setMaximumFlowRate(self.AIR_FLOW_RATE),
            fan.setMotorEfficiency(0.90),
            fan.setMotorInAirstreamFraction(1.0),
        ]
        if not self.require_condition(runner, all(fan_settings), f"Could not configure {prefix}'s fan."):
            return None

        cooling_coil = openstudio.epmodel.CoilCoolingWater(model, schedule)
        cooling_coil.setName(f"{prefix} Cooling Coil")
        cooling_settings = [
            cooling_coil.setDesignWaterFlowRate(self.CHILLED_WATER_FLOW_RATE),
            cooling_coil.setDesignAirFlowRate(self.AIR_FLOW_RATE),
            cooling_coil.setDesignInletWaterTemperature(7.22),
            cooling_coil.setDesignInletAirTemperature(26.0),
            cooling_coil.setDesignOutletAirTemperature(14.0),
            cooling_coil.setDesignInletAirHumidityRatio(0.0100),
            cooling_coil.setDesignOutletAirHumidityRatio(0.0085),
        ]
        if not self.require_condition(runner, all(cooling_settings), f"Could not configure {prefix}'s cooling coil."):
            return None

        heating_coil = openstudio.epmodel.CoilHeatingWater(model, schedule)
        heating_coil.setName(f"{prefix} Heating Coil")
        heating_settings = [
            heating_coil.setPerformanceInputMethod("UFactorTimesAreaAndDesignWaterFlowRate"),
            heating_coil.setUFactorTimesAreaValue(500.0),
            heating_coil.setMaximumWaterFlowRate(self.HOT_WATER_FLOW_RATE),
        ]
        if not self.require_condition(runner, all(heating_settings), f"Could not configure {prefix}'s heating coil."):
            return None

        fan_coil = openstudio.epmodel.ZoneHVACFourPipeFanCoil(model)
        fan_coil.setName(prefix)
        fan_coil_settings = [
            fan_coil.setAvailabilitySchedule(schedule),
            fan_coil.setCapacityControlMethod("ConstantFanVariableFlow"),
            fan_coil.setMaximumSupplyAirFlowRate(self.AIR_FLOW_RATE),
            fan_coil.setMaximumOutdoorAirFlowRate(0.0),
            fan_coil.setSupplyAirFanOperatingModeSchedule(schedule),
            fan_coil.setMaximumColdWaterFlowRate(self.CHILLED_WATER_FLOW_RATE),
            fan_coil.setMinimumColdWaterFlowRate(0.0),
            fan_coil.setCoolingConvergenceTolerance(0.001),
            fan_coil.setMaximumHotWaterFlowRate(self.HOT_WATER_FLOW_RATE),
            fan_coil.setMinimumHotWaterFlowRate(0.0),
            fan_coil.setHeatingConvergenceTolerance(0.001),
            fan_coil.setMinimumSupplyAirTemperatureInCoolingMode(14.0),
            fan_coil.setMaximumSupplyAirTemperatureInHeatingMode(31.3),
            fan_coil.setSupplyAirFan(fan),
            fan_coil.setCoolingCoil(cooling_coil),
            fan_coil.setHeatingCoil(heating_coil),
        ]
        if not self.require_condition(runner, all(fan_coil_settings), f"Could not configure {prefix}."):
            return None

        if not self.require_condition(
            runner,
            fan_coil.addToThermalZone(zone),
            f"Could not add {prefix} to {zone.nameString()}.",
        ):
            return None
        if not self.require_condition(
            runner,
            chilled_water_loop.addDemandBranchForComponent(cooling_coil),
            f"Could not connect {prefix}'s cooling coil to chilled water.",
        ):
            return None
        if not self.require_condition(
            runner,
            hot_water_loop.addDemandBranchForComponent(heating_coil),
            f"Could not connect {prefix}'s heating coil to hot water.",
        ):
            return None

        return [fan_coil, fan, cooling_coil, heating_coil]

    def validate_fan_coil(self, model, runner, zone, system, hot_water_loop, chilled_water_loop):
        fan_coil, fan, cooling_coil, heating_coil = system

        mixer = next(
            (
                candidate
                for candidate in model.getOutdoorAirMixers()
                if candidate.nameString() == f"{fan_coil.nameString()} OA Mixer"
            ),
            None,
        )

        children = fan_coil.children()
        expected_child_handles = [
            fan.handle(),
            cooling_coil.handle(),
            heating_coil.handle(),
            mixer.handle() if mixer is not None else None,
        ]
        if not self.require_condition(
            runner,
            [child.handle() for child in children] == expected_child_handles,
            f"{fan_coil.nameString()} does not expose the exact contained-child order.",
        ):
            return False

        owner_valid = (
            fan_coil.thermalZone().is_initialized()
            and fan_coil.thermalZone().get().handle() == zone.handle()
            and fan.containingHVACComponent().is_initialized()
            and fan.containingHVACComponent().get().handle() == fan_coil.handle()
            and cooling_coil.containingHVACComponent().is_initialized()
            and cooling_coil.containingHVACComponent().get().handle() == fan_coil.handle()
            and heating_coil.containingHVACComponent().is_initialized()
            and heating_coil.containingHVACComponent().get().handle() == fan_coil.handle()
        )
        if not self.require_condition(
            runner,
            owner_valid,
            f"{fan_coil.nameString()} has inconsistent zone or child ownership.",
        ):
            return False

        plant_valid = (
            cooling_coil.plantLoop().is_initialized()
            and cooling_coil.plantLoop().get().handle() == chilled_water_loop.handle()
            and heating_coil.plantLoop().is_initialized()
            and heating_coil.plantLoop().get().handle() == hot_water_loop.handle()
        )
        if not self.require_condition(
            runner, plant_valid, f"{fan_coil.nameString()} has inconsistent plant ownership."
        ):
            return False

        inlet = fan_coil.inletNode()
        fan_outlet = fan_coil.fanOutletNode()
        cooling_outlet = fan_coil.coolingCoilOutletNode()
        outlet = fan_coil.outletNode()
        roles_present = (
            inlet.is_initialized()
            and fan_outlet.is_initialized()
            and cooling_outlet.is_initialized()
            and outlet.is_initialized()
        )
        if not self.require_condition(
            runner, roles_present, f"{fan_coil.nameString()} is missing a contained-path node role."
        ):
            return False

        mixer_roles_present = (
            mixer is not None
            and mixer.mixedAirNode().is_initialized()
            and mixer.returnAirNode().is_initialized()
            and mixer.outdoorAirNode().is_initialized()
            and mixer.reliefAirNode().is_initialized()
        )
        if not self.require_condition(
            runner,
            mixer_roles_present,
            f"{fan_coil.nameString()} is missing its direct-zone outdoor-air mixer.",
        ):
            return False

        path_handles = [
            inlet.get().handle(),
            fan_outlet.get().handle(),
            cooling_outlet.get().handle(),
            outlet.get().handle(),
        ]
        path_valid = (
            len({str(handle) for handle in path_handles}) == 4
            and mixer.returnAirNode().get().handle() == inlet.get().handle()
            and self.node_handle(fan.inletModelObject()) == mixer.mixedAirNode().get().handle()
            and self.node_handle(fan.outletModelObject()) == fan_outlet.get().handle()
            and self.node_handle(cooling_coil.airInletModelObject()) == fan_outlet.get().handle()
            and self.node_handle(cooling_coil.airOutletModelObject()) == cooling_outlet.get().handle()
            and self.node_handle(heating_coil.airInletModelObject()) == cooling_outlet.get().handle()
            and self.node_handle(heating_coil.airOutletModelObject()) == outlet.get().handle()
        )
        return self.require_condition(
            runner, path_valid, f"{fan_coil.nameString()} has an inconsistent contained air path."
        )

    def run(self, model, runner, user_arguments):
        super().run(model, runner, user_arguments)
        if not runner.validateUserArguments(self.arguments(model), user_arguments):
            return False

        all_zones = sorted(model.getThermalZones(), key=lambda zone: zone.nameString())
        zones = [zone for zone in all_zones if not zone.thermostat().empty()]
        if not self.require_condition(
            runner,
            bool(zones),
            "The model has no thermostatically controlled zones to condition.",
        ):
            return False

        existing = {
            "air loops": len(model.getAirLoopHVACs()),
            "zone HVAC components": len(model.getZoneHVACComponents()),
            "plant loops": len(model.getPlantLoops()),
            "ideal-loads systems": len(model.getZoneHVACIdealLoadsAirSystems()),
        }
        conflicts = [f"{count} {label}" for label, count in existing.items() if count]
        if not self.require_condition(
            runner,
            not conflicts,
            "Four-pipe fan coils require an HVAC-ready model, but found " + ", ".join(conflicts) + ".",
        ):
            return False

        hot_water_loop = self.build_hot_water_loop(model, runner, zones[0], len(zones))
        chilled_water_loop = self.build_chilled_water_loop(model, runner, zones[0], len(zones))
        if hot_water_loop is None or chilled_water_loop is None:
            return False

        systems = [
            self.build_fan_coil(model, runner, zone, index, hot_water_loop, chilled_water_loop)
            for index, zone in enumerate(zones)
        ]
        if any(system is None for system in systems):
            return False

        for index, system in enumerate(systems):
            if not self.validate_fan_coil(model, runner, zones[index], system, hot_water_loop, chilled_water_loop):
                return False

        cooling_coils = [system[2] for system in systems]
        heating_coils = [system[3] for system in systems]
        chilled_demand_handles = [component.handle() for component in chilled_water_loop.demandComponents()]
        hot_demand_handles = [component.handle() for component in hot_water_loop.demandComponents()]
        shared_membership = all(coil.handle() in chilled_demand_handles for coil in cooling_coils) and all(
            coil.handle() in hot_demand_handles for coil in heating_coils
        )
        if not self.require_condition(
            runner,
            shared_membership,
            "The water coils are not all members of their shared plant loops.",
        ):
            return False

        fan_coils = model.getZoneHVACFourPipeFanCoils()
        owner_handles = [
            fan_coil.thermalZone().get().handle() for fan_coil in fan_coils if fan_coil.thermalZone().is_initialized()
        ]
        exact_owners = (
            len(fan_coils) == len(zones)
            and len({str(handle) for handle in owner_handles}) == len(zones)
            and all(zone.handle() in owner_handles for zone in zones)
        )
        if not self.require_condition(
            runner, exact_owners, "Expected one directly owned four-pipe fan coil for every controlled zone."
        ):
            return False
        if not self.require_condition(
            runner,
            len(model.getAirLoopHVACs()) == 0,
            "The fan-coil measure unexpectedly created an AirLoopHVAC.",
        ):
            return False

        runner.registerFinalCondition(
            f"Added {len(systems)} direct four-pipe fan coil(s) on shared explicit hot-water and chilled-water loops; "
            f"left {len(all_zones) - len(zones)} unconditioned zone(s) without HVAC."
        )
        return True


EpModelAddFourPipeFanCoils().registerWithApplication()
