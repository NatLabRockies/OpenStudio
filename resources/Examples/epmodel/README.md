# EPModel technology-preview examples

These workflows demonstrate native Python ModelMeasures operating on the
EnergyPlus-backed `OpenStudio::EPModel` API. They are a deliberately small,
user-facing selection from the broader integration corpus maintained in
OpenStudio-resources.

## Examples

The examples form a two-by-five composition matrix. One building source starts
from an empty IDF and creates geometry, constructions, schedules, zones, and
thermostats. The other starts from the DOE Small Office New-2004 Chicago
reference building and removes its air loops, zone equipment, and plant loops
through the public ownership APIs. Either source then accepts the same HVAC
addition measures:

| HVAC system | From-scratch workflow | Reference-building workflow |
| --- | --- | --- |
| Ideal loads | `epmodel_from_scratch.osw` | `epmodel_reference_building.osw` |
| Packaged single-zone gas/electric | `epmodel_from_scratch_packaged_unitary.osw` | `epmodel_reference_building_packaged_unitary.osw` |
| Multizone VAV with hot-water reheat | `epmodel_from_scratch_multizone_vav.osw` | `epmodel_reference_building_multizone_vav.osw` |
| Packaged terminal heat pumps | `epmodel_from_scratch_packaged_terminal_heat_pumps.osw` | `epmodel_reference_building_packaged_terminal_heat_pumps.osw` |
| Four-pipe fan coils with central plants | `epmodel_from_scratch_four_pipe_fan_coils.osw` | `epmodel_reference_building_four_pipe_fan_coils.osw` |

The HVAC measures use typed EPModel ownership and connection APIs. Together they
demonstrate idealized zone equipment, single-zone and multizone air loops,
packaged zone equipment, contained fans and coils, outdoor-air paths, VAV
terminals, and shared hot-water and chilled-water plants. Each measure conditions
only thermostatically controlled zones, leaving intentionally unconditioned zones
such as the reference-building attic untouched.

All workflows run July 21–27 with the Chicago TMY3 weather file supplied by
the configured EnergyPlus distribution, so they are quick, location-consistent,
and runnable offline.

## Running from a development build

CMake stages the complete example directory under the build tree. Run from
that staged directory, because the reference-building seed is supplied by the
EnergyPlus distribution selected when OpenStudio is configured:

```console
cd <openstudio-build>/resources/Examples/epmodel
../../../Products/openstudio run -w epmodel_from_scratch.osw
../../../Products/openstudio run -w epmodel_from_scratch_packaged_unitary.osw
../../../Products/openstudio run -w epmodel_from_scratch_multizone_vav.osw
../../../Products/openstudio run -w epmodel_from_scratch_packaged_terminal_heat_pumps.osw
../../../Products/openstudio run -w epmodel_from_scratch_four_pipe_fan_coils.osw
../../../Products/openstudio run -w epmodel_reference_building.osw
../../../Products/openstudio run -w epmodel_reference_building_packaged_unitary.osw
../../../Products/openstudio run -w epmodel_reference_building_multizone_vav.osw
../../../Products/openstudio run -w epmodel_reference_building_packaged_terminal_heat_pumps.osw
../../../Products/openstudio run -w epmodel_reference_building_four_pipe_fan_coils.osw
```

The executable location can vary for multi-configuration generators; an
absolute path to the build's `openstudio` executable works as well.

## Running from an installation

The installer places this directory at `Examples/epmodel` and copies the
configured EnergyPlus inputs into its `files` directory. Copy the whole example
to a writable working directory before running it, because a system installation
may be read-only and the workflow writes `out.osw`, `run`, and `reports`:

```console
cp -R <openstudio-install>/Examples/epmodel <writable-directory>/
cd <writable-directory>/epmodel
<openstudio-install>/bin/openstudio run -w epmodel_from_scratch.osw
<openstudio-install>/bin/openstudio run -w epmodel_from_scratch_packaged_unitary.osw
<openstudio-install>/bin/openstudio run -w epmodel_from_scratch_multizone_vav.osw
<openstudio-install>/bin/openstudio run -w epmodel_from_scratch_packaged_terminal_heat_pumps.osw
<openstudio-install>/bin/openstudio run -w epmodel_from_scratch_four_pipe_fan_coils.osw
<openstudio-install>/bin/openstudio run -w epmodel_reference_building.osw
<openstudio-install>/bin/openstudio run -w epmodel_reference_building_packaged_unitary.osw
<openstudio-install>/bin/openstudio run -w epmodel_reference_building_multizone_vav.osw
<openstudio-install>/bin/openstudio run -w epmodel_reference_building_packaged_terminal_heat_pumps.osw
<openstudio-install>/bin/openstudio run -w epmodel_reference_building_four_pipe_fan_coils.osw
```

On platforms where the CLI is at the installation root, use that executable
instead. The OSWs themselves contain only paths relative to the copied example;
measures do not inspect the source tree or guess an installation prefix.

## Packaging policy

Do not install all EnergyPlus `ExampleFiles`. The curated workflow owns its
small input set, while CMake sources the reference IDF from the configured
EnergyPlus package. This keeps the OpenStudio installer small and guarantees
that the IDF version matches the bundled EnergyPlus executable. Add another
reference building only when a shipped workflow uses it.
