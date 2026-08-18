# EPModel technology-preview examples

These workflows demonstrate native Python ModelMeasures operating on the
EnergyPlus-backed `OpenStudio::EPModel` API. They are a deliberately small,
user-facing selection from the broader integration corpus maintained in
OpenStudio-resources.

## Examples built from an empty model

Five workflows create the same simple building from an empty IDF and then add
different heating and cooling systems:

| Heating and cooling system | Workflow |
| --- | --- |
| Ideal loads | `epmodel_from_scratch.osw` |
| Packaged single-zone gas/electric | `epmodel_from_scratch_packaged_unitary.osw` |
| Multizone VAV with hot-water reheat | `epmodel_from_scratch_multizone_vav.osw` |
| Packaged terminal heat pumps | `epmodel_from_scratch_packaged_terminal_heat_pumps.osw` |
| Four-pipe fan coils with central plants | `epmodel_from_scratch_four_pipe_fan_coils.osw` |

## Examples built from reference buildings

Each supported DOE reference building has one curated workflow. The workflow
removes the original heating and cooling equipment through the public ownership
APIs and adds a system suited to the building use. Together, the set demonstrates
all five system measures without presenting every possible combination.

| Reference building | Replacement system | Workflow |
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

Hospital and Large Office are not included yet. Their water-cooled chillers are
connected to older condenser-loop objects that EPModel cannot safely remove as
one owned system. The examples keep that boundary explicit instead of partly
deleting those systems.

The system measures use typed EPModel ownership and connection APIs. Across the
collection they demonstrate idealized zone equipment, single-zone and multizone
air loops, packaged zone equipment, contained fans and coils, outdoor-air paths,
VAV terminals, and shared hot-water and chilled-water plants. Each measure
conditions only thermostatically controlled zones, leaving intentionally
unconditioned zones untouched.

All workflows run July 21–27 with the Chicago TMY3 weather file supplied by the
configured EnergyPlus distribution. The larger reference buildings take longer
than the from-scratch examples because loading and removing their original HVAC
can be a meaningful part of the run time.

## Running from a development build

CMake stages the complete example directory under the build tree. Run from that
directory because the reference-building inputs come from the EnergyPlus
distribution selected when OpenStudio is configured:

```console
cd <openstudio-build>/resources/Examples/epmodel
../../../Products/openstudio run -w epmodel_from_scratch.osw
../../../Products/openstudio run -w epmodel_reference_medium_office.osw
```

Choose any other workflow from the tables above. The executable location can
vary for multi-configuration generators; an absolute path to the build's
`openstudio` executable works as well.

## Running from an installation

The installer places this directory at `Examples/epmodel` and copies the
configured EnergyPlus inputs into its `files` directory. Copy the whole example
to a writable working directory before running it, because a system installation
may be read-only and the workflow writes `out.osw`, `run`, and `reports`:

```console
cp -R <openstudio-install>/Examples/epmodel <writable-directory>/
cd <writable-directory>/epmodel
<openstudio-install>/bin/openstudio run -w epmodel_reference_medium_office.osw
```

On platforms where the CLI is at the installation root, use that executable
instead. The OSWs contain only paths relative to the copied example; measures do
not inspect the source tree or guess an installation prefix.

## Packaging policy

Do not install all EnergyPlus `ExampleFiles`. This curated set owns only the
inputs used by its workflows. CMake obtains those IDFs from the configured
EnergyPlus package, which keeps their version aligned with the bundled
EnergyPlus executable. Add another reference building only when a shipped
workflow uses it.
