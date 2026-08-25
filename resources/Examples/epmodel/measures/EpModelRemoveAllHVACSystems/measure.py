import openstudio


class EpModelRemoveAllHVACSystems(openstudio.measure.ModelMeasure):
    def name(self):
        return "EPModel Remove All HVAC Systems"

    def description(self):
        return "Remove air loops, zone HVAC equipment, and plant loops from an EPModel."

    def modeler_description(self):
        return "Removes air systems before plant systems and updates settings that depend on the removed equipment."

    def arguments(self, model=None):
        return openstudio.measure.OSArgumentVector()

    @staticmethod
    def remove_owners(runner, owners, label):
        for owner in owners:
            name = owner.nameString()
            removed = owner.remove()
            if not removed:
                runner.registerError(f"Could not remove {label} '{name}'.")
                return False
        return True

    def run(self, model, runner, user_arguments):
        super().run(model, runner, user_arguments)
        if not runner.validateUserArguments(self.arguments(model), user_arguments):
            return False

        initial_air_loops = len(model.getAirLoopHVACs())
        initial_zone_hvac = len(model.getZoneHVACComponents())
        initial_plant_loops = len(model.getPlantLoops())

        if not self.remove_owners(runner, list(model.getAirLoopHVACs()), "air loop"):
            return False

        # Re-query because removing air loops may also remove attached zone equipment.
        if not self.remove_owners(
            runner, list(model.getZoneHVACComponents()), "zone HVAC component"
        ):
            return False

        # Remove plant loops after their air-side and zone-side equipment.
        if not self.remove_owners(runner, list(model.getPlantLoops()), "plant loop"):
            return False

        # Refrigerated cases cannot reject heat to return air after the air systems are gone.
        refrigeration_case_type = openstudio.epmodel.RefrigerationCase.iddObjectType()
        refrigeration_case_names = [
            obj.nameString()
            for obj in model.objects()
            if obj.iddObject().type() == refrigeration_case_type
        ]
        for case_name in refrigeration_case_names:
            refrigeration_case = model.getRefrigerationCaseByName(case_name)
            if not refrigeration_case:
                runner.registerError(f"Could not find refrigerated case '{case_name}'.")
                return False
            refrigeration_case = refrigeration_case.get()
            if refrigeration_case.underCaseHVACReturnAirFraction() <= 0.0:
                continue
            if not refrigeration_case.setUnderCaseHVACReturnAirFraction(0.0):
                runner.registerError(
                    f"Could not disconnect refrigerated case '{refrigeration_case.nameString()}' from HVAC return air."
                )
                return False

        simulation_control = openstudio.epmodel.getSimulationControl(model)
        sizing_controls = [
            simulation_control.setDoSystemSizingCalculation(False),
            simulation_control.setDoPlantSizingCalculation(False),
            simulation_control.setDoHVACSizingSimulationforSizingPeriods(False),
        ]
        if not all(sizing_controls):
            runner.registerError(
                "Could not update the sizing settings after removing HVAC."
            )
            return False

        runner.registerFinalCondition(
            f"Removed {initial_air_loops} air loop(s), {initial_zone_hvac} zone HVAC system(s), "
            f"and {initial_plant_loops} plant loop(s)."
        )
        return True


EpModelRemoveAllHVACSystems().registerWithApplication()
