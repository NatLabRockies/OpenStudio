# Air-system topology in EPModel

This page summarizes air loops, terminals, zone equipment, and the air
behavior of air-side equipment. It does not cover plant loops in general.
Only the `ZoneHVACUnitVentilator` air behavior is tracked here; its plant
attachment belongs in the plant roadmap. Class details belong in the headers
and tests.

Plant topology is the active cross-cutting development focus; its ordered
roadmap is in [PlantSystemTopology.md](PlantSystemTopology.md). This page's
backlog is limited to air-side work. `ZoneHVACUnitVentilator` is the bridge
case used by the plant hot-water/chilled-water vertical slice, while its plant
attachment remains part of [PlantSystemTopology.md](PlantSystemTopology.md).

## What should match Model

EPModel and Model save HVAC connections differently, but callers should see
the same answers when Model behavior is well defined:

- what each component is connected to;
- which loop, loop side, zone, or parent owns it;
- the order of components returned by traversal;
- what remains after moving, disconnecting, or removing a component; and
- whether save/load restores connections that can still be changed.

## How far a test goes

Tests cover different amounts of behavior. In increasing order, they may show
that:

1. the C++ API exists;
2. values and references work in memory;
3. connection changes, ownership, and rejected operations work;
4. save/load restores the connections and they still can be changed;
5. the required Ruby or Python code runs; and
6. EnergyPlus runs and produces the expected structure or results.

Passing one of these steps does not imply that the later steps work, or that a
similar class behaves the same way.

## Rules for changing connections

1. Check placement and ownership before changing anything.
2. A rejected operation must leave both the old and new systems unchanged.
3. Each connection has one owner.
4. Moving a component must remove the old connection and create the new one.
5. Traversal and ownership methods must agree with the saved connections.
6. Disconnecting keeps the component. Removing it deletes only objects that it
   owns and reconnects anything that remains.
7. Packaged equipment controls its internal fan, coil, and node connections.
8. Equipment connected to more than one loop remains alive until its last
   owner removes it.
9. Save/load may rebuild helper objects, but public connection methods must
   return the same system.

## How connection changes commit

Multi-object connection changes use a one-shot plan with a clear prepare and
commit boundary. There are two supported shapes:

- A preflight plan reads and proves the entire change before mutation. Once
  prepared, its commit contains no expected failure path.
- A provisional plan may stage reversible connections or owned helper objects.
  Until commit, abandoning the plan restores the exact original targets and
  raw unresolved references and deletes only objects created by that plan.

Setters are treated as capable of partially writing before reporting failure,
so rollback ownership is recorded before each call. Composite changes prepare
all child plans first and commit them in dependency order. Fallible discovery
or preparation does not happen inside `commit()`.

## What works now

| Area | Implemented | Still missing |
| --- | --- | --- |
| Air-loop basics | Multi-zone demand branches, ordered traversal, separate connector rows, insertion and removal, and single- and dual-duct loops | General rebranching within the same loop and badly malformed imported systems |
| Ordinary single duct | Constant-volume and VAV terminals use the same plenum-aware branch code; VAV reheat also has an EnergyPlus topology test | Reload tests for several VAV variants and more Ruby/Python use |
| Supply and return plenums | Shared supply plenums, common returns, and separate dual-duct supply lanes support reassignment, removal, and reload | Unusual connector combinations outside the tested operations |
| PIU, induction, and beams | Series and Parallel PIU, four-pipe induction, cooled beam, and four-pipe beam handle their children and remove atomically | Reload and workflow tests for beams, plus some secondary-port helpers |
| Direct dual duct | Constant-volume, VAV, and VAV outdoor-air terminals connect two supply decks to one zone; per-deck supply and common return plenums work | Reload and workflow tests for VAV and VAV outdoor-air terminals |
| Outdoor and exhaust air | Outdoor and relief paths, dedicated outdoor-air systems, heat recovery, evaporative and desiccant equipment, zone exhaust, and central exhaust | More equipment-order combinations and numerical testing |
| Air-side coils and heaters | Gas heat, two-speed DX, curve-fit DX, and assisted cooling have tested placements and retain object identity | More equipment families and numerical comparison |
| Packaged systems | Fan coils, unitary systems, VRF, packaged terminals, and water-to-air heat pumps control their internal paths while connecting to loops and zones | Clone and cross-model transfer, missing convenience methods, and numerical VRF testing |

This table describes the cases that have been tested. It is not a claim that
all methods on those classes are complete.

## Terminal families

The best-tested member of a family is useful when adding a similar terminal,
but each class still needs tests for attachment, rejection, ownership,
removal, and save/load.

| Family | Best-tested class | Other classes | Next work |
| --- | --- | --- | --- |
| Ordinary single duct | `AirTerminalSingleDuctVAVReheat` | Constant-volume, VAV no-reheat, reheat, and heat-and-cool variants share branch code | Add reload tests for VAV no-reheat and heat-and-cool variants; run `VAVHeatAndCoolReheat` in a workflow |
| PIU | Series and Parallel PIU are both references because their induced-air paths differ | Both handle their fan and coil paths, plant connections, plenums, repair, and reload | Clone and sizing methods are separate work |
| Induction and beam | `AirTerminalSingleDuctConstantVolumeFourPipeInduction` | Cooled and four-pipe beams cover attachment, ownership, removal, and plant cleanup | Add reload and workflow tests for both beams |
| Direct dual duct | `AirTerminalDualDuctConstantVolume` has the reload tests; `AirTerminalDualDuctVAV` has the larger VAV API | All three direct dual-duct terminals have connection-change tests | Add reload tests for VAV and VAV outdoor air, then run them in workflows |
| Inlet-side mixer | `AirTerminalSingleDuctInletSideMixer` | No similar terminal | Treat the downstream ZoneHVAC equipment separately |
| Special single duct | None yet | User-defined and variable-speed-fan terminals have limited C++ tests and remain in the historical scaffold directory | Define their EMS and fan ownership behavior before adding more API |

Add a separate family when the number of air streams, ownership, branch shape,
or saved EnergyPlus objects changes caller-visible behavior. Scalar field
differences alone do not need a new family.

## Air backlog and bridge work

1. Complete the `ZoneHVACUnitVentilator` air-side behavior around the bridge
   scenario above: `FanSystemModel`, electric heat, water-coil child wiring,
   local outdoor air, save/load, and post-load changes. Plant attachment is
   tracked in the plant roadmap.
2. Add the missing terminal reload tests listed above.
3. Choose later air work from real model-building scripts, measures, and OSWs.
   Add only the methods needed by the chosen use case.
4. Add Ruby/Python and EnergyPlus tests when the use case needs them. Keep
   exploratory workflows in OpenStudio-resources rather than the main source
   repository.

## Other open work

- clone and cross-model transfer;
- moving an existing branch within one loop;
- transactional outdoor/relief two-stream mutation and equipment/controller
  update plans;
- Ruby/Python overloads not yet used by a test;
- autosized values read from SQL results;
- Model/EPModel file comparison;
- numerical comparison on clean simulations;
- multi-speed unitary stage data;
- AirflowNetwork, leakage, and space-level HVAC; and
- repair of malformed systems not produced by the supported API.

Stop for a design review when Model behavior is ambiguous, when two reasonable
implementations would behave differently for callers, or when the work would
require a Model production change.

See [README.md](README.md) for the rest of the EPModel design and where to find
class-specific information.
