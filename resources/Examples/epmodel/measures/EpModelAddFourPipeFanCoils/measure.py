import openstudio


class EpModelAddFourPipeFanCoils(openstudio.measure.ModelMeasure):
    SYSTEM_PREFIX = "EPModel Four-Pipe Fan Coils"
    AIR_FLOW_RATE = 0.45
    CHILLED_WATER_FLOW_RATE = 0.00042
    HOT_WATER_FLOW_RATE = 0.00020

    def name(self):
        return "EPModel Add Four-Pipe Fan Coils"

    def description(self):
        return "Add a four-pipe fan coil to every zone with a thermostat."

    def modeler_description(self):
        return "The fan coils share hot-water and chilled-water loops served by a gas boiler and an air-cooled chiller."

    def arguments(self, model=None):
        return openstudio.measure.OSArgumentVector()

    @staticmethod
    def require_condition(runner, condition, message):
        if condition:
            return True

        runner.registerError(message)
        return False

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
        setpoint_schedule.setValue(60.0)

        loop = openstudio.epmodel.PlantLoop(model)
        loop.setName(f"{prefix} Loop")
        loop.sizingPlant().setLoopType("Heating")
        loop.sizingPlant().setDesignLoopExitTemperature(60.0)
        loop.sizingPlant().setLoopDesignTemperatureDifference(10.0)
        loop.setMaximumLoopFlowRate(loop_flow_rate)

        pump = openstudio.epmodel.PumpVariableSpeed(model)
        pump.setName(f"{prefix} Pump")
        pump.autosizeRatedPowerConsumption()
        pump.setRatedFlowRate(loop_flow_rate)
        pump.setRatedPumpHead(120_000.0)
        pump.setMotorEfficiency(0.90)
        if not self.require_condition(
            runner,
            pump.setZone(pump_zone),
            "Could not assign the hot-water pump heat-loss zone.",
        ):
            return None
        if not self.require_condition(
            runner,
            pump.addToNode(loop.supplyInletNode()),
            "Could not add the hot-water pump.",
        ):
            return None

        boiler = openstudio.epmodel.BoilerHotWater(model)
        boiler.setName(f"{prefix} Boiler")
        boiler.setFuelType("NaturalGas")
        boiler.setNominalCapacity(10_000.0 * zone_count)
        boiler.setDesignWaterFlowRate(loop_flow_rate)
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
        setpoint_schedule.setValue(7.22)

        loop = openstudio.epmodel.PlantLoop(model)
        loop.setName(f"{prefix} Loop")
        loop.sizingPlant().setLoopType("Cooling")
        loop.sizingPlant().setDesignLoopExitTemperature(7.22)
        loop.sizingPlant().setLoopDesignTemperatureDifference(5.0)
        loop.setMaximumLoopFlowRate(loop_flow_rate)

        pump = openstudio.epmodel.PumpVariableSpeed(model)
        pump.setName(f"{prefix} Pump")
        pump.autosizeRatedPowerConsumption()
        pump.setRatedFlowRate(loop_flow_rate)
        pump.setRatedPumpHead(120_000.0)
        pump.setMotorEfficiency(0.90)
        if not self.require_condition(
            runner,
            pump.setZone(pump_zone),
            "Could not assign the chilled-water pump heat-loss zone.",
        ):
            return None
        if not self.require_condition(
            runner,
            pump.addToNode(loop.supplyInletNode()),
            "Could not add the chilled-water pump.",
        ):
            return None

        chiller = openstudio.epmodel.ChillerElectricEIR(model)
        chiller.setName(f"{prefix} Air-Cooled Chiller")
        chiller.setCondenserType("AirCooled")
        chiller.setReferenceCapacity(10_000.0 * zone_count)
        chiller.setReferenceCOP(3.2)
        chiller.setReferenceChilledWaterFlowRate(loop_flow_rate)
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

    def build_fan_coil(
        self, model, runner, zone, index, hot_water_loop, chilled_water_loop
    ):
        prefix = f"{self.SYSTEM_PREFIX} {index + 1:02d}"
        schedule = model.alwaysOnDiscreteSchedule()

        fan = openstudio.epmodel.FanConstantVolume(model, schedule)
        fan.setName(f"{prefix} Fan")
        fan.setFanTotalEfficiency(0.70)
        fan.setPressureRise(250.0)
        fan.setMaximumFlowRate(self.AIR_FLOW_RATE)
        fan.setMotorEfficiency(0.90)
        fan.setMotorInAirstreamFraction(1.0)

        cooling_coil = openstudio.epmodel.CoilCoolingWater(model, schedule)
        cooling_coil.setName(f"{prefix} Cooling Coil")
        cooling_coil.setDesignWaterFlowRate(self.CHILLED_WATER_FLOW_RATE)
        cooling_coil.setDesignAirFlowRate(self.AIR_FLOW_RATE)
        cooling_coil.setDesignInletWaterTemperature(7.22)
        cooling_coil.setDesignInletAirTemperature(26.0)
        cooling_coil.setDesignOutletAirTemperature(14.0)
        cooling_coil.setDesignInletAirHumidityRatio(0.0100)
        cooling_coil.setDesignOutletAirHumidityRatio(0.0085)

        heating_coil = openstudio.epmodel.CoilHeatingWater(model, schedule)
        heating_coil.setName(f"{prefix} Heating Coil")
        heating_coil.setPerformanceInputMethod("UFactorTimesAreaAndDesignWaterFlowRate")
        heating_coil.setUFactorTimesAreaValue(500.0)
        heating_coil.setMaximumWaterFlowRate(self.HOT_WATER_FLOW_RATE)

        fan_coil = openstudio.epmodel.ZoneHVACFourPipeFanCoil(model)
        fan_coil.setName(prefix)
        fan_coil.setAvailabilitySchedule(schedule)
        fan_coil.setCapacityControlMethod("ConstantFanVariableFlow")
        fan_coil.setMaximumSupplyAirFlowRate(self.AIR_FLOW_RATE)
        fan_coil.setMaximumOutdoorAirFlowRate(0.0)
        fan_coil.setSupplyAirFanOperatingModeSchedule(schedule)
        fan_coil.setMaximumColdWaterFlowRate(self.CHILLED_WATER_FLOW_RATE)
        fan_coil.setMinimumColdWaterFlowRate(0.0)
        fan_coil.setCoolingConvergenceTolerance(0.001)
        fan_coil.setMaximumHotWaterFlowRate(self.HOT_WATER_FLOW_RATE)
        fan_coil.setMinimumHotWaterFlowRate(0.0)
        fan_coil.setHeatingConvergenceTolerance(0.001)
        fan_coil.setMinimumSupplyAirTemperatureInCoolingMode(14.0)
        fan_coil.setMaximumSupplyAirTemperatureInHeatingMode(31.3)
        if not self.require_condition(
            runner,
            all(
                [
                    fan_coil.setSupplyAirFan(fan),
                    fan_coil.setCoolingCoil(cooling_coil),
                    fan_coil.setHeatingCoil(heating_coil),
                ]
            ),
            f"Could not assemble {prefix}.",
        ):
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

        return fan_coil

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
            "Remove the existing HVAC systems before adding four-pipe fan coils; found "
            + ", ".join(conflicts)
            + ".",
        ):
            return False

        hot_water_loop = self.build_hot_water_loop(model, runner, zones[0], len(zones))
        chilled_water_loop = self.build_chilled_water_loop(
            model, runner, zones[0], len(zones)
        )
        if hot_water_loop is None or chilled_water_loop is None:
            return False

        systems = [
            self.build_fan_coil(
                model, runner, zone, index, hot_water_loop, chilled_water_loop
            )
            for index, zone in enumerate(zones)
        ]
        if any(system is None for system in systems):
            return False

        runner.registerFinalCondition(
            f"Added four-pipe fan coils to {len(systems)} zone(s); "
            f"left {len(all_zones) - len(zones)} unconditioned zone(s) unchanged."
        )
        return True


EpModelAddFourPipeFanCoils().registerWithApplication()
