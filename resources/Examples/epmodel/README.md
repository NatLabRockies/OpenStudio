# EPModel examples

These workflows use Python measures to create and edit EnergyPlus models with
EPModel. Each workflow finishes by running EnergyPlus for a short summer week.

## Create a new building

The following workflows start with an empty IDF. They create a simple building
with windows and thermostats, then add one of five heating and cooling systems.

| System | Workflow |
| --- | --- |
| Ideal loads | `epmodel_from_scratch.osw` |
| Packaged single-zone gas/electric | `epmodel_from_scratch_packaged_unitary.osw` |
| Multizone VAV with hot-water reheat | `epmodel_from_scratch_multizone_vav.osw` |
| Packaged terminal heat pumps | `epmodel_from_scratch_packaged_terminal_heat_pumps.osw` |
| Four-pipe fan coils with central plants | `epmodel_from_scratch_four_pipe_fan_coils.osw` |

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
../../../Products/openstudio run -w epmodel_from_scratch.osw
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
