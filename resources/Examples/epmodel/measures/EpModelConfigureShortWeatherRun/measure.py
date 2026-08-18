import openstudio


class EpModelConfigureShortWeatherRun(openstudio.measure.ModelMeasure):
    def name(self):
        return "EPModel Configure Short Weather Run"

    def description(self):
        return "Set up a weather simulation for July 21 through July 27."

    def modeler_description(self):
        return "Uses six timesteps per hour and enables the sizing calculations needed by the model."

    def arguments(self, model=None):
        return openstudio.measure.OSArgumentVector()

    def run(self, model, runner, user_arguments):
        super().run(model, runner, user_arguments)
        if not runner.validateUserArguments(self.arguments(model), user_arguments):
            return False

        run_period = openstudio.epmodel.getRunPeriod(model)
        timestep = openstudio.epmodel.getTimestep(model)
        simulation_control = openstudio.epmodel.getSimulationControl(model)
        updates = [
            run_period.setBeginMonth(7),
            run_period.setBeginDayOfMonth(21),
            run_period.setEndMonth(7),
            run_period.setEndDayOfMonth(27),
            timestep.setNumberOfTimestepsPerHour(6),
            simulation_control.setDoZoneSizingCalculation(
                bool(model.getThermalZones())
            ),
            simulation_control.setDoSystemSizingCalculation(
                bool(model.getAirLoopHVACs())
            ),
            simulation_control.setDoPlantSizingCalculation(bool(model.getPlantLoops())),
            simulation_control.setRunSimulationforSizingPeriods(True),
            simulation_control.setRunSimulationforWeatherFileRunPeriods(True),
            simulation_control.setMaximumNumberofWarmupDays(50),
        ]
        if not all(updates):
            runner.registerError("Could not configure the short weather simulation.")
            return False

        runner.registerFinalCondition(
            "Configured a six-timestep-per-hour weather simulation for July 21-27."
        )
        return True


EpModelConfigureShortWeatherRun().registerWithApplication()
