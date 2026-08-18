import openstudio


class EpModelRemoveAllHVACSystems(openstudio.measure.ModelMeasure):
    def name(self):
        return "EPModel Remove All HVAC Systems"

    def description(self):
        return "Remove every air loop, zone HVAC component, and plant loop through their public EPModel ownership APIs."

    def modeler_description(self):
        return (
            "Exercises owner-level HVAC removal and reconciles SimulationControl with the resulting zone-only model. "
            "The measure deliberately contains no EnergyPlus object-type deletion list and no raw field or node manipulation."
        )

    def arguments(self, model=None):
        return openstudio.measure.OSArgumentVector()

    @staticmethod
    def remove_owners(runner, owners, label):
        removed_count = 0
        for owner in owners:
            name = owner.nameString()
            removed = owner.remove()
            if not removed:
                runner.registerError(f"Could not remove {label} '{name}' through its ownership API.")
                return None
            removed_count += len(removed)
        return removed_count

    def run(self, model, runner, user_arguments):
        super().run(model, runner, user_arguments)
        if not runner.validateUserArguments(self.arguments(model), user_arguments):
            return False

        initial_object_count = model.numObjects()
        initial_air_loops = len(model.getAirLoopHVACs())
        initial_zone_hvac = len(model.getZoneHVACComponents())
        initial_plant_loops = len(model.getPlantLoops())
        runner.registerInitialCondition(
            f"The model contains {initial_air_loops} air loop(s), {initial_zone_hvac} zone HVAC component(s), "
            f"and {initial_plant_loops} plant loop(s)."
        )

        removed_air_objects = self.remove_owners(runner, list(model.getAirLoopHVACs()), "air loop")
        if removed_air_objects is None:
            return False

        # Re-query after air-loop removal. AirLoopHVAC owns its terminals and may
        # remove zone equipment as part of demand-side topology cleanup.
        removed_zone_objects = self.remove_owners(
            runner, list(model.getZoneHVACComponents()), "zone HVAC component"
        )
        if removed_zone_objects is None:
            return False

        # Remove plants last so shared water-to-air components can first detach
        # cleanly from their air-side and zone-side owners.
        removed_plant_objects = self.remove_owners(runner, list(model.getPlantLoops()), "plant loop")
        if removed_plant_objects is None:
            return False

        remaining = {
            "air loops": len(model.getAirLoopHVACs()),
            "zone HVAC components": len(model.getZoneHVACComponents()),
            "plant loops": len(model.getPlantLoops()),
        }
        failures = [f"{count} {label}" for label, count in remaining.items() if count]
        if failures:
            runner.registerError("Owner-level HVAC removal left " + ", ".join(failures) + ".")
            return False

        simulation_control = openstudio.epmodel.getSimulationControl(model)
        sizing_controls = [
            (
                simulation_control.setDoSystemSizingCalculation(False),
                "Could not disable system sizing after removing all air systems.",
            ),
            (
                simulation_control.setDoPlantSizingCalculation(False),
                "Could not disable plant sizing after removing all plant systems.",
            ),
            (
                simulation_control.setDoHVACSizingSimulationforSizingPeriods(False),
                "Could not disable HVAC sizing simulations after removing all HVAC systems.",
            ),
        ]
        for condition, message in sizing_controls:
            if not condition:
                runner.registerError(message)
                return False

        runner.registerFinalCondition(
            f"Removed {initial_object_count - model.numObjects()} model object(s) through the public ownership APIs "
            f"({removed_air_objects} from air-loop removal, {removed_zone_objects} from zone-HVAC removal, "
            f"and {removed_plant_objects} from plant-loop removal)."
        )
        return True


EpModelRemoveAllHVACSystems().registerWithApplication()
