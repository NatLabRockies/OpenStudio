import openstudio


class EpModelAddPackagedTerminalHeatPumps(openstudio.measure.ModelMeasure):
    SYSTEM_PREFIX = "EPModel Packaged Terminal Heat Pump"

    def name(self):
        return "EPModel Add Packaged Terminal Heat Pumps"

    def description(self):
        return "Add one autosized packaged terminal heat pump with local outdoor air to every thermostatically controlled zone."

    def modeler_description(self):
        return (
            "Consumes an HVAC-ready EPModel and builds each PTHP from an on/off fan, single-speed DX heating and cooling "
            "coils, supplemental electric heat, and its owned outdoor-air mixer using typed EPModel APIs."
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
            "Packaged terminal heat pumps require an HVAC-ready model, but found " + ", ".join(conflicts) + ".",
        ):
            return False

        schedule = model.alwaysOnDiscreteSchedule()
        created = []
        for index, zone in enumerate(zones, 1):
            prefix = f"{self.SYSTEM_PREFIX} {index}"

            fan = openstudio.epmodel.FanOnOff(model, schedule)
            fan.setName(f"{prefix} Fan")
            fan.setFanEfficiency(0.7)
            fan.setPressureRise(300.0)
            fan.autosizeMaximumFlowRate()
            fan.setMotorEfficiency(0.9)

            heating = openstudio.epmodel.CoilHeatingDXSingleSpeed(model)
            heating.setName(f"{prefix} DX Heating Coil")
            heating.setAvailabilitySchedule(schedule)
            heating.autosizeRatedTotalHeatingCapacity()
            heating.autosizeRatedAirFlowRate()

            cooling = openstudio.epmodel.CoilCoolingDXSingleSpeed(model)
            cooling.setName(f"{prefix} DX Cooling Coil")
            cooling.setAvailabilitySchedule(schedule)
            cooling.setRatedCOP(3.0)
            cooling.autosizeRatedTotalCoolingCapacity()
            cooling.autosizeRatedSensibleHeatRatio()
            cooling.autosizeRatedAirFlowRate()

            supplemental = openstudio.epmodel.CoilHeatingElectric(model)
            supplemental.setName(f"{prefix} Supplemental Heating Coil")
            supplemental.setAvailabilitySchedule(schedule)
            supplemental.setEfficiency(1.0)
            supplemental.autosizeNominalCapacity()

            pthp = openstudio.epmodel.ZoneHVACPackagedTerminalHeatPump(model)
            pthp.setName(prefix)
            settings = [
                pthp.setAvailabilitySchedule(schedule),
                pthp.setSupplyAirFan(fan),
                pthp.setHeatingCoil(heating),
                pthp.setCoolingCoil(cooling),
                pthp.setSupplementalHeatingCoil(supplemental),
                pthp.setFanPlacement("BlowThrough"),
            ]
            if not self.require_condition(runner, all(settings), f"Could not configure the PTHP for '{zone.nameString()}'."):
                return False

            pthp.autosizeSupplyAirFlowRateDuringCoolingOperation()
            pthp.autosizeSupplyAirFlowRateDuringHeatingOperation()
            pthp.autosizeSupplyAirFlowRateWhenNoCoolingorHeatingisNeeded()
            pthp.autosizeOutdoorAirFlowRateDuringCoolingOperation()
            pthp.autosizeOutdoorAirFlowRateDuringHeatingOperation()
            pthp.autosizeOutdoorAirFlowRateWhenNoCoolingorHeatingisNeeded()
            pthp.autosizeMaximumSupplyAirTemperaturefromSupplementalHeater()

            if not self.require_condition(
                runner,
                pthp.addToThermalZone(zone),
                f"Could not add the PTHP to '{zone.nameString()}'.",
            ):
                return False

            relationships_are_coherent = (
                not pthp.thermalZone().empty()
                and pthp.thermalZone().get().handle() == zone.handle()
                and pthp.supplyAirFan().handle() == fan.handle()
                and pthp.heatingCoil().handle() == heating.handle()
                and pthp.coolingCoil().handle() == cooling.handle()
                and pthp.supplementalHeatingCoil().handle() == supplemental.handle()
                and not pthp.inletNode().empty()
                and not pthp.outletNode().empty()
            )
            if not self.require_condition(
                runner,
                relationships_are_coherent,
                f"The packaged-terminal relationships for '{zone.nameString()}' are not coherent.",
            ):
                return False
            created.append(pthp)

        if not self.require_condition(
            runner,
            len(model.getZoneHVACPackagedTerminalHeatPumps()) == len(zones),
            "The number of packaged terminal heat pumps does not match the number of controlled zones.",
        ):
            return False

        runner.registerFinalCondition(
            f"Added {len(created)} autosized packaged terminal heat pump(s), one for each controlled zone; "
            f"left {len(all_zones) - len(zones)} unconditioned zone(s) without HVAC."
        )
        return True


EpModelAddPackagedTerminalHeatPumps().registerWithApplication()
