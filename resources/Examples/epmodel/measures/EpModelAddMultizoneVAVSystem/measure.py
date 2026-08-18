import openstudio


class EpModelAddMultizoneVAVSystem(openstudio.measure.ModelMeasure):
    SYSTEM_PREFIX = "EPModel Multizone VAV"

    def name(self):
        return "EPModel Add Multizone VAV System"

    def description(self):
        return (
            "Serve every thermostatically controlled zone with one multizone VAV system and central hot-water and "
            "chilled-water plants."
        )

    def modeler_description(self):
        return (
            "Consumes the same HVAC-ready contract as the other addition measures, then builds a variable-volume air "
            "system with hot-water reheat, a boiler hot-water loop, and an air-cooled-chiller chilled-water loop."
        )

    def arguments(self, model=None):
        return openstudio.measure.OSArgumentVector()

    @staticmethod
    def require_condition(runner, condition, message):
        if condition:
            return True
        runner.registerError(message)
        return False

    def build_plant_loop(self, model, runner, zone, heating, zone_count):
        kind = "Hot Water" if heating else "Chilled Water"
        temperature = 82.0 if heating else 7.22
        delta = 11.0 if heating else 6.67
        flow_rate = (0.00020 if heating else 0.00042) * zone_count * 1.25

        schedule = openstudio.epmodel.ScheduleConstant(model)
        schedule.setName(f"{self.SYSTEM_PREFIX} {kind} Setpoint")
        if not self.require_condition(runner, schedule.setValue(temperature), f"Could not set the {kind.lower()} setpoint."):
            return None

        loop = openstudio.epmodel.PlantLoop(model)
        sizing = loop.sizingPlant()
        if not self.require_condition(
            runner,
            all(
                [
                    sizing.setLoopType("Heating" if heating else "Cooling"),
                    sizing.setDesignLoopExitTemperature(temperature),
                    sizing.setLoopDesignTemperatureDifference(delta),
                    loop.setMaximumLoopFlowRate(flow_rate),
                ]
            ),
            f"Could not configure the {kind.lower()} loop sizing.",
        ):
            return None

        pump = openstudio.epmodel.PumpVariableSpeed(model)
        pump.setName(f"{self.SYSTEM_PREFIX} {kind} Pump")
        pump.autosizeRatedPowerConsumption()
        if not self.require_condition(
            runner,
            all(
                [
                    pump.setRatedFlowRate(flow_rate),
                    pump.setRatedPumpHead(120_000.0),
                    pump.setMotorEfficiency(0.9),
                    pump.setZone(zone),
                    pump.addToNode(loop.supplyInletNode()),
                ]
            ),
            f"Could not configure and connect the {kind.lower()} pump.",
        ):
            return None

        if heating:
            equipment = openstudio.epmodel.BoilerHotWater(model)
            equipment.setName(f"{self.SYSTEM_PREFIX} Hot Water Boiler")
            if not self.require_condition(runner, equipment.setFuelType("NaturalGas"), "Could not set the boiler fuel type."):
                return None
            equipment.autosizeNominalCapacity()
            equipment.autosizeDesignWaterFlowRate()
            operation = openstudio.epmodel.PlantEquipmentOperationHeatingLoad(model)
            operation.setName(f"{self.SYSTEM_PREFIX} Hot Water Heating Operation Scheme")
            operation_is_set = operation.addEquipment(equipment) and loop.setPlantEquipmentOperationHeatingLoad(operation)
        else:
            equipment = openstudio.epmodel.ChillerElectricEIR(model)
            equipment.setName(f"{self.SYSTEM_PREFIX} Air-Cooled Chiller")
            operation = openstudio.epmodel.PlantEquipmentOperationCoolingLoad(model)
            operation.setName(f"{self.SYSTEM_PREFIX} Chilled Water Cooling Operation Scheme")
            operation_is_set = operation.addEquipment(equipment) and loop.setPlantEquipmentOperationCoolingLoad(operation)

        if not self.require_condition(
            runner,
            operation_is_set and loop.addSupplyBranchForComponent(equipment),
            f"Could not connect the {kind.lower()} equipment and operation scheme.",
        ):
            return None

        for label, placement in [
            ("Supply Bypass", "supply_branch"),
            ("Supply Outlet Pipe", "supply_outlet"),
            ("Demand Inlet Pipe", "demand_inlet"),
            ("Demand Bypass", "demand_branch"),
            ("Demand Outlet Pipe", "demand_outlet"),
        ]:
            pipe = openstudio.epmodel.PipeAdiabatic(model)
            pipe.setName(f"{self.SYSTEM_PREFIX} {kind} {label}")
            if placement == "supply_branch":
                connected = loop.addSupplyBranchForComponent(pipe)
            elif placement == "supply_outlet":
                connected = pipe.addToNode(loop.supplyOutletNode())
            elif placement == "demand_inlet":
                connected = pipe.addToNode(loop.demandInletNode())
            elif placement == "demand_branch":
                connected = loop.addDemandBranchForComponent(pipe)
            else:
                connected = pipe.addToNode(loop.demandOutletNode())
            if not self.require_condition(runner, connected, f"Could not connect the {kind.lower()} {label.lower()}."):
                return None

        spm = openstudio.epmodel.SetpointManagerScheduled(model)
        spm.setName(f"{self.SYSTEM_PREFIX} {kind} Setpoint Manager")
        if not self.require_condition(
            runner,
            spm.setSchedule(schedule)
            and spm.addToNode(loop.supplyOutletNode())
            and loop.setLoopTemperatureSetpointNode(loop.supplyOutletNode()),
            f"Could not configure the {kind.lower()} setpoint manager.",
        ):
            return None

        return loop

    def build_multizone_air_loop(self, model, runner, hot_water_loop, chilled_water_loop):
        deck_schedule = openstudio.epmodel.ScheduleConstant(model)
        deck_schedule.setName(f"{self.SYSTEM_PREFIX} Deck Air Setpoint")
        if not self.require_condition(runner, deck_schedule.setValue(12.8), "Could not set the VAV deck-air setpoint."):
            return None

        air_loop = openstudio.epmodel.AirLoopHVAC(model)
        air_loop.setName(f"{self.SYSTEM_PREFIX} System")
        sizing = air_loop.sizingSystem()
        sizing.setCentralCoolingDesignSupplyAirTemperature(12.8)
        sizing.setCentralHeatingDesignSupplyAirTemperature(16.7)
        if hasattr(sizing, "setTypeofLoadtoSizeOn"):
            sizing.setTypeofLoadtoSizeOn("Sensible")

        outdoor_air_system = openstudio.epmodel.AirLoopHVACOutdoorAirSystem(model)
        outdoor_air_system.setName(f"{self.SYSTEM_PREFIX} Outdoor Air System")
        outdoor_air_system.getControllerOutdoorAir().setName(f"{self.SYSTEM_PREFIX} Outdoor Air Controller")

        cooling_coil = openstudio.epmodel.CoilCoolingWater(model)
        cooling_coil.setName(f"{self.SYSTEM_PREFIX} Central Cooling Coil")
        cooling_coil.autosizeDesignWaterFlowRate()
        cooling_coil.autosizeDesignAirFlowRate()

        heating_coil = openstudio.epmodel.CoilHeatingWater(model)
        heating_coil.setName(f"{self.SYSTEM_PREFIX} Central Heating Coil")

        fan = openstudio.epmodel.FanVariableVolume(model)
        fan.setName(f"{self.SYSTEM_PREFIX} Supply Fan")

        supply_outlet_node = air_loop.supplyOutletNode()
        for component in [outdoor_air_system, cooling_coil, heating_coil, fan]:
            if not self.require_condition(
                runner, component.addToNode(supply_outlet_node), f"Could not add {component.nameString()} to the VAV supply path."
            ):
                return None

        if not self.require_condition(
            runner,
            chilled_water_loop.addDemandBranchForComponent(cooling_coil)
            and hot_water_loop.addDemandBranchForComponent(heating_coil),
            "Could not connect the central water coils to their plant loops.",
        ):
            return None

        for name, node in [
            ("Deck Air", supply_outlet_node),
            ("Cooling Coil Outlet", heating_coil.airInletModelObject().get().to_Node().get()),
            ("Heating Coil Outlet", fan.inletModelObject().get().to_Node().get()),
        ]:
            spm = openstudio.epmodel.SetpointManagerScheduled(model)
            spm.setName(f"{self.SYSTEM_PREFIX} {name} Setpoint Manager")
            if not self.require_condition(
                runner,
                spm.setSchedule(deck_schedule) and spm.addToNode(node),
                f"Could not add the {name.lower()} setpoint manager.",
            ):
                return None

        return air_loop

    def run(self, model, runner, user_arguments):
        super().run(model, runner, user_arguments)
        if not runner.validateUserArguments(self.arguments(model), user_arguments):
            return False

        all_zones = sorted(model.getThermalZones(), key=lambda zone: zone.nameString())
        zones = [zone for zone in all_zones if not zone.thermostat().empty()]

        if not zones:
            runner.registerError("The model has no thermostatically controlled zones to condition.")
            return False

        existing = {
            "air loops": len(model.getAirLoopHVACs()),
            "zone HVAC components": len(model.getZoneHVACComponents()),
            "plant loops": len(model.getPlantLoops()),
            "ideal-loads systems": len(model.getZoneHVACIdealLoadsAirSystems()),
        }
        conflicts = [f"{count} {label}" for label, count in existing.items() if count]
        if conflicts:
            runner.registerError(
                "The multizone VAV system requires an HVAC-ready model, but found " + ", ".join(conflicts) + "."
            )
            return False

        pump_zone = zones[0]
        hot_water_loop = self.build_plant_loop(model, runner, pump_zone, True, len(zones))
        chilled_water_loop = self.build_plant_loop(model, runner, pump_zone, False, len(zones))

        if hot_water_loop is None or chilled_water_loop is None:
            runner.registerError("Could not link the plant pumps to a thermal zone for skin-loss gains.")
            return False

        hot_water_loop.setName(f"{self.SYSTEM_PREFIX} Hot Water Loop")
        chilled_water_loop.setName(f"{self.SYSTEM_PREFIX} Chilled Water Loop")

        air_loop = self.build_multizone_air_loop(model, runner, hot_water_loop, chilled_water_loop)
        if air_loop is None:
            return False
        for zone in zones:
            reheat_coil = openstudio.epmodel.CoilHeatingWater(model)
            reheat_coil.setName(f"{zone.nameString()} Reheat Coil")
            if not self.require_condition(
                runner,
                hot_water_loop.addDemandBranchForComponent(reheat_coil),
                f"Could not connect the reheat coil for '{zone.nameString()}'.",
            ):
                return False
            terminal = openstudio.epmodel.AirTerminalSingleDuctVAVReheat(
                model, model.alwaysOnDiscreteSchedule(), reheat_coil
            )
            terminal.setName(f"{zone.nameString()} VAV Reheat Terminal")
            if not self.require_condition(
                runner,
                air_loop.addBranchForZone(zone, terminal),
                f"Could not connect the VAV terminal for '{zone.nameString()}'.",
            ):
                return False

        if not self.require_condition(
            runner,
            len(air_loop.thermalZones()) == len(zones)
            and len(model.getAirTerminalSingleDuctVAVReheats()) == len(zones),
            "The VAV system does not serve every controlled zone exactly once.",
        ):
            return False

        runner.registerFinalCondition(
            f"Added one multizone VAV air system serving {len(zones)} controlled zone(s), with hot-water reheat, "
            f"central chilled water, and shared plant loops; left {len(all_zones) - len(zones)} unconditioned zone(s) without HVAC."
        )
        return True


EpModelAddMultizoneVAVSystem().registerWithApplication()
