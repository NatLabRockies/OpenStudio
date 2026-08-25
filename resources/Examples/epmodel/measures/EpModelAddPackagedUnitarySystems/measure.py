import openstudio


class EpModelAddPackagedUnitarySystems(openstudio.measure.ModelMeasure):
    SYSTEM_PREFIX = "EPModel Packaged Unitary"

    def name(self):
        return "EPModel Add Packaged Unitary Systems"

    def description(self):
        return "Add a packaged single-zone gas/electric system to every zone with a thermostat."

    def modeler_description(self):
        return "Each system includes outdoor air, an on/off fan, gas heat, DX cooling, and a constant-volume terminal."

    def arguments(self, model=None):
        return openstudio.measure.OSArgumentVector()

    @staticmethod
    def require_condition(runner, condition, message):
        if condition:
            return True
        runner.registerError(message)
        return False

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
            "Remove the existing HVAC systems before adding packaged unitary systems; found "
            + ", ".join(conflicts)
            + ".",
        ):
            return False

        schedule = model.alwaysOnDiscreteSchedule()
        for index, zone in enumerate(zones, 1):
            system_name = f"{self.SYSTEM_PREFIX} {index}"

            if not self.require_condition(
                runner,
                zone.sizingZone().setCoolingDesignAirFlowMethod("DesignDayWithLimit"),
                f"Could not give '{zone.nameString()}' a minimum design cooling airflow.",
            ):
                return False

            air_loop = openstudio.epmodel.AirLoopHVAC(model)
            air_loop.setName(f"{system_name} Air Loop")
            air_loop.sizingSystem().setCentralCoolingDesignSupplyAirTemperature(12.8)
            air_loop.sizingSystem().setCentralHeatingDesignSupplyAirTemperature(40.0)

            outdoor_air = openstudio.epmodel.AirLoopHVACOutdoorAirSystem(model)
            outdoor_air.setName(f"{system_name} Outdoor Air System")
            outdoor_air.getControllerOutdoorAir().setMinimumOutdoorAirFlowRate(0.0)
            outdoor_air.getControllerOutdoorAir().autosizeMaximumOutdoorAirFlowRate()

            fan = openstudio.epmodel.FanOnOff(model, schedule)
            fan.setName(f"{system_name} Supply Fan")
            fan.setFanEfficiency(0.7)
            fan.setPressureRise(500.0)
            fan.autosizeMaximumFlowRate()
            fan.setMotorEfficiency(0.9)

            heating = openstudio.epmodel.CoilHeatingGas(model, schedule)
            heating.setName(f"{system_name} Gas Heating Coil")
            heating.setGasBurnerEfficiency(0.8)
            heating.autosizeNominalCapacity()

            cooling = openstudio.epmodel.CoilCoolingDXSingleSpeed(model)
            cooling.setName(f"{system_name} DX Cooling Coil")
            cooling.setAvailabilitySchedule(schedule)
            cooling.setRatedCOP(3.0)
            cooling.autosizeRatedTotalCoolingCapacity()
            cooling.autosizeRatedSensibleHeatRatio()
            cooling.autosizeRatedAirFlowRate()

            unitary = openstudio.epmodel.AirLoopHVACUnitaryHeatCool(
                model, schedule, fan, heating, cooling
            )
            unitary.setName(f"{system_name} Unitary")
            if not self.require_condition(
                runner,
                unitary.setControllingZone(zone),
                f"Could not set '{zone.nameString()}' as the packaged unitary controlling zone.",
            ):
                return False
            unitary.setFanPlacement("BlowThrough")
            unitary.autosizeMaximumSupplyAirTemperature()
            unitary.autosizeCoolingSupplyAirFlowRate()
            unitary.autosizeHeatingSupplyAirFlowRate()
            unitary.autosizeNoLoadSupplyAirFlowRate()

            if not self.require_condition(
                runner,
                outdoor_air.addToNode(air_loop.supplyOutletNode()),
                f"Could not add the outdoor-air system for '{zone.nameString()}'.",
            ):
                return False
            if not self.require_condition(
                runner,
                unitary.addToNode(air_loop.supplyOutletNode()),
                f"Could not add the packaged unitary for '{zone.nameString()}'.",
            ):
                return False

            terminal = openstudio.epmodel.AirTerminalSingleDuctConstantVolumeNoReheat(
                model, schedule
            )
            terminal.setName(f"{system_name} Terminal")
            terminal.autosizeMaximumAirFlowRate()
            if not self.require_condition(
                runner,
                air_loop.addBranchForZone(zone, terminal),
                f"Could not connect the packaged unitary air loop to '{zone.nameString()}'.",
            ):
                return False

        runner.registerFinalCondition(
            f"Added packaged single-zone systems to {len(zones)} zone(s); "
            f"left {len(all_zones) - len(zones)} unconditioned zone(s) unchanged."
        )
        return True


EpModelAddPackagedUnitarySystems().registerWithApplication()
