import openstudio


class EpModelAddPackagedUnitarySystems(openstudio.measure.ModelMeasure):
    SYSTEM_PREFIX = "EPModel Packaged Unitary"

    def name(self):
        return "EPModel Add Packaged Unitary Systems"

    def description(self):
        return "Add one autosized packaged single-zone air conditioner to every thermostatically controlled zone in an HVAC-ready EPModel."

    def modeler_description(self):
        return (
            "Builds each system from an AirLoopHVAC, outdoor-air system, AirLoopHVAC:UnitaryHeatCool with an on/off fan, "
            "DX cooling coil, gas heating coil, and a constant-volume no-reheat terminal using typed EPModel APIs."
        )

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
        if not self.require_condition(runner, bool(zones), "The model has no thermostatically controlled zones to condition."):
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
            "Packaged unitary systems require an HVAC-ready model, but found " + ", ".join(conflicts) + ".",
        ):
            return False

        schedule = model.alwaysOnDiscreteSchedule()
        created = []
        for index, zone in enumerate(zones, 1):
            system_name = f"{self.SYSTEM_PREFIX} {index}"

            air_loop = openstudio.epmodel.AirLoopHVAC(model)
            air_loop.setName(f"{system_name} Air Loop")
            air_loop.sizingSystem().setCentralCoolingDesignSupplyAirTemperature(12.8)
            air_loop.sizingSystem().setCentralHeatingDesignSupplyAirTemperature(40.0)

            outdoor_air = openstudio.epmodel.AirLoopHVACOutdoorAirSystem(model)
            outdoor_air.setName(f"{system_name} Outdoor Air System")
            outdoor_air.getControllerOutdoorAir().autosizeMinimumOutdoorAirFlowRate()
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

            unitary = openstudio.epmodel.AirLoopHVACUnitaryHeatCool(model, schedule, fan, heating, cooling)
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

            terminal = openstudio.epmodel.AirTerminalSingleDuctConstantVolumeNoReheat(model, schedule)
            terminal.setName(f"{system_name} Terminal")
            terminal.autosizeMaximumAirFlowRate()
            if not self.require_condition(
                runner,
                air_loop.addBranchForZone(zone, terminal),
                f"Could not connect the packaged unitary air loop to '{zone.nameString()}'.",
            ):
                return False

            relationships_are_coherent = (
                not unitary.airLoopHVAC().empty()
                and unitary.airLoopHVAC().get().handle() == air_loop.handle()
                and unitary.supplyFan().handle() == fan.handle()
                and unitary.heatingCoil().handle() == heating.handle()
                and unitary.coolingCoil().handle() == cooling.handle()
                and not unitary.controllingZone().empty()
                and unitary.controllingZone().get().handle() == zone.handle()
                and len(air_loop.thermalZones()) == 1
                and air_loop.thermalZones()[0].handle() == zone.handle()
            )
            if not self.require_condition(
                runner,
                relationships_are_coherent,
                f"The packaged system relationships for '{zone.nameString()}' are not coherent.",
            ):
                return False
            created.append((air_loop, unitary, terminal))

        if not self.require_condition(
            runner,
            len(model.getAirLoopHVACUnitaryHeatCools()) == len(zones),
            "The number of packaged unitary systems does not match the number of thermal zones.",
        ):
            return False

        runner.registerFinalCondition(
            f"Added {len(created)} autosized packaged unitary system(s), one for each thermostatically controlled zone; "
            f"left {len(all_zones) - len(zones)} unconditioned zone(s) without HVAC."
        )
        return True


EpModelAddPackagedUnitarySystems().registerWithApplication()
