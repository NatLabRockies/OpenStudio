# EPModel examples

EPModel (`openstudio::epmodel::Model`) recreates the familiar
`openstudio::model::Model` API on top of EnergyPlus objects. It loads and saves
IDF files instead of OSM files, allowing applications and measures to work
directly with an EnergyPlus model while retaining the established OpenStudio
API shape.

EPModel is a work in progress, but these workflows demonstrate substantial
capability already available through Python measures. Each workflow creates or
edits an EnergyPlus model and finishes by running EnergyPlus for a short summer
week.

## Create a new building

The following workflows start with an empty IDF. They create a two-story office
with north, south, east, west, and core zones on each floor. Interior surfaces
are matched between zones and stories, and windows are added to the exterior
walls. The footprint is 30 m by 20 m, with a 4.5 m perimeter depth and 3.6 m
floor-to-floor height. Each workflow then adds one of five heating and cooling
systems.

| System | Workflow |
| --- | --- |
| Ideal loads | `epmodel_core_perimeter_ideal_loads.osw` |
| Packaged single-zone gas/electric | `epmodel_core_perimeter_packaged_unitary.osw` |
| Multizone VAV with hot-water reheat | `epmodel_core_perimeter_multizone_vav.osw` |
| Packaged terminal heat pumps | `epmodel_core_perimeter_packaged_terminal_heat_pumps.osw` |
| Four-pipe fan coils with central plants | `epmodel_core_perimeter_four_pipe_fan_coils.osw` |

### What the new-building examples include

These examples currently focus on geometry and heating and cooling systems.
EnergyPlus can already represent space loads, schedules, and construction
assignments, but not in forms that are directly compatible with the OpenStudio
Model API. To close that gap, three new EnergyPlus features are being
developed:

- **Shared load definitions:** new definition and instance objects will let
  many people, lighting, and equipment loads share one definition while each
  instance keeps its own location, schedule, and multiplier.
- **Rules-based annual schedules:** `Schedule:Year:Rules` and
  `Schedule:Week:Rule` will describe a default day and prioritized exceptions
  without expanding them into many week and day objects.
- **Construction assignment sets:** `ConstructionAssignmentSet` and its
  surface assignment objects will let spaces and buildings provide
  constructions by surface type, while individual surfaces can still override
  them.

Until these features are fully integrated into EnergyPlus, the measures do not
create new space loads such as people, lights, or plug loads. Existing space
loads in the reference buildings pass through EPModel unchanged and remain in
the resulting IDF. The new-building examples use simple constructions and only
the schedules needed for heating and cooling.

## Change a reference building

These workflows load an EnergyPlus reference building, replace its heating and
cooling equipment, and simulate the updated building. Zones with thermostats
receive new equipment; unconditioned zones are left alone.

| Reference building | New system | Workflow |
| --- | --- | --- |
| Full Service Restaurant | Packaged single-zone gas/electric | `epmodel_reference_full_service_restaurant.osw` |
| Large Hotel | Four-pipe fan coils with central plants | `epmodel_reference_large_hotel.osw` |
| Medium Office | Multizone VAV with hot-water reheat | `epmodel_reference_medium_office.osw` |
| Midrise Apartment | Packaged terminal heat pumps | `epmodel_reference_midrise_apartment.osw` |
| Outpatient | Multizone VAV with hot-water reheat | `epmodel_reference_outpatient.osw` |
| Primary School | Multizone VAV with hot-water reheat | `epmodel_reference_primary_school.osw` |
| Quick Service Restaurant | Packaged single-zone gas/electric | `epmodel_reference_quick_service_restaurant.osw` |
| Secondary School | Multizone VAV with hot-water reheat | `epmodel_reference_secondary_school.osw` |
| Small Hotel | Packaged terminal heat pumps | `epmodel_reference_small_hotel.osw` |
| Small Office | Packaged single-zone gas/electric | `epmodel_reference_small_office.osw` |
| Stand-alone Retail | Packaged single-zone gas/electric | `epmodel_reference_stand_alone_retail.osw` |
| Strip Mall | Packaged single-zone gas/electric | `epmodel_reference_strip_mall.osw` |
| Supermarket | Packaged single-zone gas/electric | `epmodel_reference_supermarket.osw` |
| Warehouse | Ideal loads | `epmodel_reference_warehouse.osw` |

All workflows use Chicago weather and run from July 21 through July 27. Larger
reference buildings may take a few minutes to complete.

## Run from a development build

The examples are staged in the build directory:

```console
cd <openstudio-build>/resources/Examples/epmodel
../../../Products/openstudio run -w epmodel_core_perimeter_ideal_loads.osw
../../../Products/openstudio run -w epmodel_reference_medium_office.osw
```

The executable may be in a different configuration directory on some build
systems. An absolute path to the build's `openstudio` executable also works.

## Run from an installation

Copy the example directory to a writable location before running it. A workflow
creates `out.osw`, `run`, and `reports` in the working directory.

```console
cp -R <openstudio-install>/Examples/epmodel <writable-directory>/
cd <writable-directory>/epmodel
<openstudio-install>/bin/openstudio run -w epmodel_reference_medium_office.osw
```

On installations where the CLI is at the installation root, use that
executable instead. Every workflow uses paths relative to the copied example
directory.
