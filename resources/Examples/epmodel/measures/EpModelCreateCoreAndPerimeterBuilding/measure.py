import openstudio


class EpModelCreateCoreAndPerimeterBuilding(openstudio.measure.ModelMeasure):
    BUILDING_WIDTH = 30.0
    BUILDING_DEPTH = 20.0
    PERIMETER_DEPTH = 4.5
    FLOOR_TO_FLOOR_HEIGHT = 3.6

    def name(self):
        return "EPModel Create Core and Perimeter Building"

    def description(self):
        return "Create a multistory office with core and perimeter thermal zones."

    def modeler_description(self):
        return (
            "Creates five zones per story, intersects and matches interior surfaces, adds exterior windows, "
            "and assigns thermostats and outdoor-air requirements."
        )

    def arguments(self, model=None):
        args = openstudio.measure.OSArgumentVector()
        number_of_stories = openstudio.measure.OSArgument.makeIntegerArgument(
            "number_of_stories", True
        )
        number_of_stories.setDisplayName("Number of stories")
        number_of_stories.setDefaultValue(2)
        args.append(number_of_stories)
        return args

    @staticmethod
    def require_condition(runner, condition, message):
        if condition:
            return True
        runner.registerError(message)
        return False

    def build_constructions(self, model, runner):
        concrete = openstudio.epmodel.StandardOpaqueMaterial(model)
        concrete.setName("Core and Perimeter Concrete")
        concrete.setRoughness("MediumRough")
        concrete.setThickness(0.10)
        concrete.setConductivity(1.4)
        concrete.setDensity(2200.0)
        concrete.setSpecificHeat(900.0)

        insulation = openstudio.epmodel.StandardOpaqueMaterial(model)
        insulation.setName("Core and Perimeter Insulation")
        insulation.setRoughness("MediumRough")
        insulation.setThickness(0.09)
        insulation.setConductivity(0.04)
        insulation.setDensity(32.0)
        insulation.setSpecificHeat(1400.0)

        gypsum = openstudio.epmodel.StandardOpaqueMaterial(model)
        gypsum.setName("Core and Perimeter Gypsum Board")
        gypsum.setRoughness("Smooth")
        gypsum.setThickness(0.0127)
        gypsum.setConductivity(0.16)
        gypsum.setDensity(800.0)
        gypsum.setSpecificHeat(1090.0)

        opaque_layers = openstudio.epmodel.MaterialVector()
        # A symmetric assembly can be used on both sides of matched surfaces
        # without requiring a second, reversed construction.
        for material in [gypsum, insulation, concrete, insulation, gypsum]:
            opaque_layers.append(material)
        opaque_construction = openstudio.epmodel.Construction(model)
        opaque_construction.setName("Core and Perimeter Opaque Construction")
        if not self.require_condition(
            runner,
            opaque_construction.setLayers(opaque_layers),
            "Could not create the opaque construction.",
        ):
            return None

        glazing = openstudio.epmodel.SimpleGlazing(model)
        glazing.setName("Core and Perimeter Glazing")
        glazing.setUFactor(2.3)
        glazing.setSolarHeatGainCoefficient(0.35)

        glazing_layers = openstudio.epmodel.MaterialVector()
        glazing_layers.append(glazing)
        glazing_construction = openstudio.epmodel.Construction(model)
        glazing_construction.setName("Core and Perimeter Window Construction")
        if not self.require_condition(
            runner,
            glazing_construction.setLayers(glazing_layers),
            "Could not create the window construction.",
        ):
            return None

        return opaque_construction, glazing_construction

    @staticmethod
    def build_design_day(
        model,
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
        design_day.setMonth(month)
        design_day.setDayOfMonth(day)
        design_day.setDayType(day_type)
        design_day.setMaximumDryBulbTemperature(dry_bulb)
        design_day.setDailyDryBulbTemperatureRange(daily_range)
        design_day.setHumidityConditionType("WetBulb")
        design_day.setWetBulbOrDewPointAtMaximumDryBulb(wet_bulb)
        design_day.setBarometricPressure(99000.0)
        design_day.setWindSpeed(3.0)
        design_day.setWindDirection(180.0)
        design_day.setRainIndicator(False)
        design_day.setSnowIndicator(False)
        design_day.setSolarModelIndicator("ASHRAEClearSky")
        design_day.setSkyClearness(sky_clearness)

    def footprint_definitions(self):
        width = self.BUILDING_WIDTH
        depth = self.BUILDING_DEPTH
        perimeter = self.PERIMETER_DEPTH

        return [
            (
                "West Perimeter",
                [
                    (0.0, 0.0),
                    (0.0, depth),
                    (perimeter, depth - perimeter),
                    (perimeter, perimeter),
                ],
            ),
            (
                "North Perimeter",
                [
                    (0.0, depth),
                    (width, depth),
                    (width - perimeter, depth - perimeter),
                    (perimeter, depth - perimeter),
                ],
            ),
            (
                "East Perimeter",
                [
                    (width, depth),
                    (width, 0.0),
                    (width - perimeter, perimeter),
                    (width - perimeter, depth - perimeter),
                ],
            ),
            (
                "South Perimeter",
                [
                    (width, 0.0),
                    (0.0, 0.0),
                    (perimeter, perimeter),
                    (width - perimeter, perimeter),
                ],
            ),
            (
                "Core",
                [
                    (perimeter, perimeter),
                    (perimeter, depth - perimeter),
                    (width - perimeter, depth - perimeter),
                    (width - perimeter, perimeter),
                ],
            ),
        ]

    def build_space_and_zone(
        self,
        model,
        runner,
        story,
        story_number,
        label,
        footprint,
        heating_schedule,
        cooling_schedule,
    ):
        z = (story_number - 1) * self.FLOOR_TO_FLOOR_HEIGHT
        points = openstudio.Point3dVector()
        for x, y in footprint:
            points.append(openstudio.Point3d(x, y, z))

        prefix = f"Story {story_number} {label}"
        optional_space = openstudio.epmodel.Space.fromFloorPrint(
            points,
            self.FLOOR_TO_FLOOR_HEIGHT,
            model,
            f"{prefix} Space",
        )
        if not self.require_condition(
            runner,
            not optional_space.empty(),
            f"Could not create {prefix.lower()} geometry.",
        ):
            return None

        space = optional_space.get()

        zone = openstudio.epmodel.ThermalZone(model)
        zone.setName(f"{prefix} Zone")
        if not self.require_condition(
            runner,
            space.setBuildingStory(story) and space.setThermalZone(zone),
            f"Could not assign {prefix.lower()} to its story and thermal zone.",
        ):
            return None

        thermostat = openstudio.epmodel.ThermostatSetpointDualSetpoint(model)
        thermostat.setName(f"{prefix} Thermostat")
        thermostat_settings = [
            thermostat.setHeatingSetpointTemperatureSchedule(heating_schedule),
            thermostat.setCoolingSetpointTemperatureSchedule(cooling_schedule),
            zone.setThermostatSetpointDualSetpoint(thermostat),
        ]
        if not self.require_condition(
            runner,
            all(thermostat_settings),
            f"Could not add a thermostat to {prefix.lower()}.",
        ):
            return None

        outdoor_air_settings = [
            zone.setOutdoorAirMethod("Sum"),
            zone.setOutdoorAirFlowperFloorArea(0.0003),
        ]
        if not self.require_condition(
            runner,
            all(outdoor_air_settings),
            f"Could not set the outdoor-air requirement for {prefix.lower()}.",
        ):
            return None

        return space, zone

    def add_envelope(self, spaces, runner, opaque_construction, glazing_construction):
        window_count = 0
        for space in spaces:
            for surface in space.surfaces():
                surface.setConstruction(opaque_construction)
                if (
                    surface.surfaceType() != "Wall"
                    or surface.outsideBoundaryCondition() != "Outdoors"
                ):
                    continue

                window = surface.setWindowToWallRatio(0.35)
                if not self.require_condition(
                    runner,
                    not window.empty(),
                    f"Could not add a window to '{surface.nameString()}'.",
                ):
                    return None
                if not self.require_condition(
                    runner,
                    window.get().setConstruction(glazing_construction),
                    f"Could not set the construction for '{window.get().nameString()}'.",
                ):
                    return None
                window_count += 1

        return window_count

    def run(self, model, runner, user_arguments):
        super().run(model, runner, user_arguments)
        if not runner.validateUserArguments(self.arguments(model), user_arguments):
            return False

        number_of_stories = runner.getIntegerArgumentValue(
            "number_of_stories", user_arguments
        )
        if not self.require_condition(
            runner,
            1 <= number_of_stories <= 3,
            "Number of stories must be between 1 and 3.",
        ):
            return False
        if not self.require_condition(
            runner,
            not model.getSpaces() and not model.getThermalZones(),
            "This measure requires a seed without spaces or thermal zones.",
        ):
            return False

        building = openstudio.epmodel.getBuilding(model)
        building.setName("EPModel Core and Perimeter Office")
        building.setNorthAxis(0.0)

        simulation_control = openstudio.epmodel.getSimulationControl(model)
        simulation_control.setDoZoneSizingCalculation(True)
        simulation_control.setDoSystemSizingCalculation(False)
        simulation_control.setDoPlantSizingCalculation(False)

        self.build_design_day(
            model,
            "Chicago Summer Design Day",
            7,
            21,
            "SummerDesignDay",
            35.0,
            11.0,
            23.0,
            1.0,
        )
        self.build_design_day(
            model,
            "Chicago Winter Design Day",
            1,
            21,
            "WinterDesignDay",
            -15.0,
            0.0,
            -15.0,
            0.0,
        )

        constructions = self.build_constructions(model, runner)
        if constructions is None:
            return False

        heating_schedule = openstudio.epmodel.ScheduleConstant(model)
        heating_schedule.setName("Office Heating Setpoint")
        heating_schedule.setValue(21.0)

        cooling_schedule = openstudio.epmodel.ScheduleConstant(model)
        cooling_schedule.setName("Office Cooling Setpoint")
        cooling_schedule.setValue(24.0)

        spaces = openstudio.epmodel.SpaceVector()
        zones = []
        footprints = self.footprint_definitions()
        for story_number in range(1, number_of_stories + 1):
            story = openstudio.epmodel.BuildingStory(model)
            story.setName(f"Story {story_number}")
            story.setNominalZCoordinate((story_number - 1) * self.FLOOR_TO_FLOOR_HEIGHT)
            story.setNominalFloortoFloorHeight(self.FLOOR_TO_FLOOR_HEIGHT)

            for label, footprint in footprints:
                result = self.build_space_and_zone(
                    model,
                    runner,
                    story,
                    story_number,
                    label,
                    footprint,
                    heating_schedule,
                    cooling_schedule,
                )
                if result is None:
                    return False
                space, zone = result
                spaces.append(space)
                zones.append(zone)

        openstudio.epmodel.intersectSurfaces(spaces)
        openstudio.epmodel.matchSurfaces(spaces)

        matched_surface_count = sum(
            1
            for space in spaces
            for surface in space.surfaces()
            if not surface.adjacentSurface().empty()
        )
        expected_matched_surface_count = 26 * number_of_stories - 10
        if not self.require_condition(
            runner,
            matched_surface_count == expected_matched_surface_count,
            "The generated spaces did not produce the expected interior surface matches.",
        ):
            return False

        window_count = self.add_envelope(
            spaces, runner, constructions[0], constructions[1]
        )
        if window_count is None:
            return False

        runner.registerFinalCondition(
            f"Created a {number_of_stories}-story core and perimeter office with "
            f"{len(zones)} thermal zones and {window_count} exterior windows."
        )
        return True


EpModelCreateCoreAndPerimeterBuilding().registerWithApplication()
