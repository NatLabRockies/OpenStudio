import openstudio


class EpModelFromScratch(openstudio.measure.ModelMeasure):
    def name(self):
        return "EPModel From Scratch"

    def description(self):
        return "Build a small HVAC-ready EPModel without SpaceType, SpaceList, or space-load objects."

    def modeler_description(self):
        return "Creates explicit geometry, zones, constructions, constant schedules, and thermostats using only public typed EPModel APIs."

    def arguments(self, model=None):
        args = openstudio.measure.OSArgumentVector()
        zone_count = openstudio.measure.OSArgument.makeIntegerArgument("zone_count", True)
        zone_count.setDisplayName("Number of detached shoebox zones")
        zone_count.setDefaultValue(1)
        args.append(zone_count)

        return args

    @staticmethod
    def require_condition(runner, condition, message):
        if condition:
            return True
        runner.registerError(message)
        return False

    def build_constructions(self, model, runner):
        opaque = openstudio.epmodel.StandardOpaqueMaterial(model)
        opaque.setName("From Scratch Opaque Material")
        settings = [
            (opaque.setRoughness("MediumRough"), "Could not set opaque material roughness."),
            (opaque.setThickness(0.2), "Could not set opaque material thickness."),
            (opaque.setConductivity(1.4), "Could not set opaque material conductivity."),
            (opaque.setDensity(2200.0), "Could not set opaque material density."),
            (opaque.setSpecificHeat(900.0), "Could not set opaque material specific heat."),
        ]
        for condition, message in settings:
            if not self.require_condition(runner, condition, message):
                return None

        opaque_layers = openstudio.epmodel.MaterialVector()
        opaque_layers.append(opaque)
        opaque_construction = openstudio.epmodel.Construction(model)
        opaque_construction.setName("From Scratch Opaque Construction")
        if not self.require_condition(
            runner,
            opaque_construction.setLayers(opaque_layers),
            "Could not set opaque construction layers.",
        ):
            return None

        glazing = openstudio.epmodel.SimpleGlazing(model)
        glazing.setName("From Scratch Simple Glazing")
        if not self.require_condition(
            runner, glazing.setUFactor(2.7), "Could not set glazing U-factor."
        ) or not self.require_condition(
            runner, glazing.setSolarHeatGainCoefficient(0.4), "Could not set glazing SHGC."
        ):
            return None

        glazing_layers = openstudio.epmodel.MaterialVector()
        glazing_layers.append(glazing)
        glazing_construction = openstudio.epmodel.Construction(model)
        glazing_construction.setName("From Scratch Glazing Construction")
        if not self.require_condition(
            runner,
            glazing_construction.setLayers(glazing_layers),
            "Could not set glazing construction layers.",
        ):
            return None

        return [opaque_construction, glazing_construction]

    def build_design_day(
        self,
        model,
        runner,
        name,
        month,
        day,
        day_type,
        dry_bulb,
        daily_range,
        wet_bulb,
        sky_clearness,
    ):
        design_day = openstudio.epmodel.DesignDay(model)
        design_day.setName(name)
        settings = [
            design_day.setMonth(month),
            design_day.setDayOfMonth(day),
            design_day.setDayType(day_type),
            design_day.setMaximumDryBulbTemperature(dry_bulb),
            design_day.setDailyDryBulbTemperatureRange(daily_range),
            design_day.setHumidityConditionType("WetBulb"),
            design_day.setWetBulbOrDewPointAtMaximumDryBulb(wet_bulb),
            design_day.setBarometricPressure(99000.0),
            design_day.setWindSpeed(3.0),
            design_day.setWindDirection(180.0),
            design_day.setRainIndicator(False),
            design_day.setSnowIndicator(False),
            design_day.setSolarModelIndicator("ASHRAEClearSky"),
            design_day.setSkyClearness(sky_clearness),
        ]
        if not self.require_condition(runner, all(settings), f"Could not configure {name}."):
            return None

        return design_day

    def build_zone(
        self,
        model,
        runner,
        index,
        opaque_construction,
        glazing_construction,
        heating_schedule,
        cooling_schedule,
    ):
        x = index * 12.0
        points = openstudio.Point3dVector()
        for point in [
            openstudio.Point3d(x, 0.0, 0.0),
            openstudio.Point3d(x, 10.0, 0.0),
            openstudio.Point3d(x + 10.0, 10.0, 0.0),
            openstudio.Point3d(x + 10.0, 0.0, 0.0),
        ]:
            points.append(point)

        prefix = f"From Scratch Zone {index + 1:02d}"
        space = openstudio.epmodel.Space.fromFloorPrint(points, 3.0, model, f"{prefix} Space")
        if not self.require_condition(runner, not space.empty(), f"Could not create {prefix} geometry."):
            return None

        space = space.get()
        zone = openstudio.epmodel.ThermalZone(model)
        zone.setName(prefix)
        if not self.require_condition(
            runner, space.setThermalZone(zone), f"Could not assign {prefix} Space to its zone."
        ):
            return None

        window_added = False
        for surface in space.surfaces():
            if not self.require_condition(
                runner,
                surface.setConstruction(opaque_construction),
                f"Could not assign {surface.nameString()}'s construction.",
            ):
                return None
            if surface.surfaceType() != "Wall" or window_added:
                continue
            window = surface.setWindowToWallRatio(0.30)
            if not self.require_condition(runner, not window.empty(), f"Could not add {prefix}'s window."):
                return None
            if not self.require_condition(
                runner,
                window.get().setConstruction(glazing_construction),
                f"Could not assign {prefix}'s glazing construction.",
            ):
                return None
            window_added = True

        thermostat = openstudio.epmodel.ThermostatSetpointDualSetpoint(model)
        thermostat.setName(f"{prefix} Thermostat")
        for condition, message in [
            (
                thermostat.setHeatingSetpointTemperatureSchedule(heating_schedule),
                f"Could not set {prefix}'s heating schedule.",
            ),
            (
                thermostat.setCoolingSetpointTemperatureSchedule(cooling_schedule),
                f"Could not set {prefix}'s cooling schedule.",
            ),
            (
                zone.setThermostatSetpointDualSetpoint(thermostat),
                f"Could not set {prefix}'s thermostat.",
            ),
        ]:
            if not self.require_condition(runner, condition, message):
                return None

        return zone

    def run(self, model, runner, user_arguments):
        super().run(model, runner, user_arguments)
        if not runner.validateUserArguments(self.arguments(model), user_arguments):
            return False
        zone_count = runner.getIntegerArgumentValue("zone_count", user_arguments)
        if not self.require_condition(runner, 0 < zone_count <= 20, "zone_count must be between 1 and 20."):
            return False
        if not self.require_condition(
            runner,
            not model.getSpaces() and not model.getThermalZones(),
            "The from-scratch builder requires a seed without Spaces or ThermalZones.",
        ):
            return False

        building = openstudio.epmodel.getBuilding(model)
        building.setName("From Scratch Building")

        simulation_control = openstudio.epmodel.getSimulationControl(model)
        controls = [
            (simulation_control.setDoZoneSizingCalculation(True), "Could not enable zone sizing."),
            (
                simulation_control.setDoSystemSizingCalculation(False),
                "Could not disable unused system sizing.",
            ),
            (
                simulation_control.setDoPlantSizingCalculation(False),
                "Could not disable unused plant sizing.",
            ),
        ]
        for condition, message in controls:
            if not self.require_condition(runner, condition, message):
                return False

        summer_day = self.build_design_day(
            model,
            runner,
            "From Scratch Summer Design Day",
            7,
            21,
            "SummerDesignDay",
            35.0,
            11.0,
            23.0,
            1.0,
        )
        winter_day = self.build_design_day(
            model,
            runner,
            "From Scratch Winter Design Day",
            1,
            21,
            "WinterDesignDay",
            -15.0,
            0.0,
            -15.0,
            0.0,
        )
        if summer_day is None or winter_day is None:
            return False

        constructions = self.build_constructions(model, runner)
        if constructions is None:
            return False

        heating_schedule = openstudio.epmodel.ScheduleConstant(model)
        heating_schedule.setName("From Scratch Heating Setpoint")
        if not self.require_condition(runner, heating_schedule.setValue(20.0), "Could not set the heating setpoint."):
            return False

        cooling_schedule = openstudio.epmodel.ScheduleConstant(model)
        cooling_schedule.setName("From Scratch Cooling Setpoint")
        if not self.require_condition(runner, cooling_schedule.setValue(24.0), "Could not set the cooling setpoint."):
            return False

        zones = [
            self.build_zone(
                model,
                runner,
                index,
                constructions[0],
                constructions[1],
                heating_schedule,
                cooling_schedule,
            )
            for index in range(zone_count)
        ]
        if any(zone is None for zone in zones):
            return False

        if not self.require_condition(
            runner,
            not model.getSpaceTypes() and not model.getSpaceLists(),
            "The alpha example unexpectedly created SpaceType or SpaceList objects.",
        ):
            return False

        runner.registerFinalCondition(
            f"Built {len(zones)} HVAC-ready explicit zone(s) from an empty IDF using direct constructions, constant schedules, and thermostats."
        )
        return True


EpModelFromScratch().registerWithApplication()
