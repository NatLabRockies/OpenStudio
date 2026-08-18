import openstudio


class EpModelAddIdealLoads(openstudio.measure.ModelMeasure):
    def name(self):
        return "EPModel Add Ideal Loads"

    def description(self):
        return "Add an ideal-loads air system to every thermal zone in an HVAC-ready EPModel."

    def modeler_description(self):
        return "Uses ThermalZone.setUseIdealAirLoads after verifying that no air loops, zone equipment, or plant loops remain."

    def arguments(self, model=None):
        return openstudio.measure.OSArgumentVector()

    def run(self, model, runner, user_arguments):
        super().run(model, runner, user_arguments)
        if not runner.validateUserArguments(self.arguments(model), user_arguments):
            return False

        zones = list(model.getThermalZones())
        if not zones:
            runner.registerError("The model has no thermal zones to condition.")
            return False

        existing = {
            "air loops": len(model.getAirLoopHVACs()),
            "zone HVAC components": len(model.getZoneHVACComponents()),
            "plant loops": len(model.getPlantLoops()),
        }
        conflicts = [f"{count} {label}" for label, count in existing.items() if count]
        if conflicts:
            runner.registerError("Ideal loads requires an HVAC-ready model, but found " + ", ".join(conflicts) + ".")
            return False

        for zone in zones:
            if not zone.setUseIdealAirLoads(True):
                runner.registerError(f"Could not add ideal loads to thermal zone '{zone.nameString()}'.")
                return False

        if len(model.getZoneHVACIdealLoadsAirSystems()) != len(zones):
            runner.registerError("The number of ideal-loads systems does not match the number of thermal zones.")
            return False

        runner.registerFinalCondition(f"Added ideal loads to {len(zones)} thermal zone(s).")
        return True


EpModelAddIdealLoads().registerWithApplication()
