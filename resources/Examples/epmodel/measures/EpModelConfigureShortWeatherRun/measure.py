import openstudio


class EpModelConfigureShortWeatherRun(openstudio.measure.ModelMeasure):
    def name(self):
        return "EPModel Configure Short Weather Run"

    def description(self):
        return "Configure an EPModel to run July 21-27 using its workflow weather file."

    def modeler_description(self):
        return (
            "Uses public RunPeriod, Timestep, and SimulationControl APIs to provide a fast, "
            "repeatable simulation setup shared by the example workflows."
        )

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
            (run_period.setBeginMonth(7), "Could not set the run-period start month."),
            (run_period.setBeginDayOfMonth(21), "Could not set the run-period start day."),
            (run_period.setEndMonth(7), "Could not set the run-period end month."),
            (run_period.setEndDayOfMonth(27), "Could not set the run-period end day."),
            (timestep.setNumberOfTimestepsPerHour(6), "Could not set simulation timesteps."),
            (
                simulation_control.setDoZoneSizingCalculation(bool(model.getThermalZones())),
                "Could not configure zone sizing calculations.",
            ),
            (
                simulation_control.setDoSystemSizingCalculation(bool(model.getAirLoopHVACs())),
                "Could not configure system sizing calculations.",
            ),
            (
                simulation_control.setDoPlantSizingCalculation(bool(model.getPlantLoops())),
                "Could not configure plant sizing calculations.",
            ),
            (
                simulation_control.setRunSimulationforSizingPeriods(True),
                "Could not enable sizing-period simulations.",
            ),
            (
                simulation_control.setRunSimulationforWeatherFileRunPeriods(True),
                "Could not enable weather-file run periods.",
            ),
        ]
        for condition, message in updates:
            if not condition:
                runner.registerError(message)
                return False

        runner.registerFinalCondition("Configured a six-timestep-per-hour weather simulation for July 21-27.")
        return True


EpModelConfigureShortWeatherRun().registerWithApplication()
