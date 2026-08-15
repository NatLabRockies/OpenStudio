# Air-system topology in EPModel

This page summarizes air loops, terminals, zone equipment, and the air
behavior of air-side equipment. It does not cover plant loops in general.
Only the `ZoneHVACUnitVentilator` air behavior is tracked here; its plant
attachment belongs in the plant roadmap. Class details belong in the headers
and tests.

Plant topology has reached the representative broad-core stopping point in
[PlantSystemTopology.md](PlantSystemTopology.md). Air topology has a short
closing set below. `ZoneHVACUnitVentilator` is the remaining bridge case: its
contained air path belongs here, while its water-coil attachment uses the
established plant contract. After the closing set, work should move to the
horizontal selection rules in
[HVACComponentRoadmap.md](HVACComponentRoadmap.md), not continue indefinitely
through increasingly unusual topology combinations.

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
| Induction and beam | `AirTerminalSingleDuctConstantVolumeFourPipeInduction` | Cooled and four-pipe beams cover in-memory attachment, ownership, removal, and plant cleanup | Defer beam reload and workflows until their OS-prefixed terminal/coil storage has an EnergyPlus-native persistence design |
| Direct dual duct | The constant-volume, VAV, and VAV outdoor-air terminals all have reload and post-load change tests | VAV also exposes its directly stored availability, DSOA, and turndown relationships | The topology family is at its stopping point; add SQL or translated outdoor-air conveniences only for a concrete use case |
| Inlet-side mixer | `AirTerminalSingleDuctInletSideMixer` | No similar terminal | Treat the downstream ZoneHVAC equipment separately |
| Special single duct | None yet | User-defined and variable-speed-fan terminals have limited C++ tests and remain in the historical scaffold directory | Define their EMS and fan ownership behavior before adding more API |

Add a separate family when the number of air streams, ownership, branch shape,
or saved EnergyPlus objects changes caller-visible behavior. Scalar field
differences alone do not need a new family.

## Air topology stopping point

The `ZoneHVACUnitVentilator` bridge and the direct dual-duct family now have
their planned C++, Ruby, reload, post-load change, and EnergyPlus evidence.
The remaining beam reload/workflow candidate was also investigated. It cannot
be completed by adding evidence alone: the cooled-beam terminal and beam coil
relationships still rely on OS-prefixed objects that do not return as typed
objects through the EnergyPlus-schema `epmodel::Model::load` path.

That persistence redesign belongs to horizontal component work, not another
topology phase. The topology-led air campaign has therefore reached its
stopping point. Later work must be justified by a real use case or a shared
defect across several families. Missing scalar conveniences, clone depth,
unusual connector shapes, and malformed imports are not reasons to reopen it.

## Other open work

- clone and cross-model transfer;
- moving an existing branch within one loop;
- transactional outdoor/relief two-stream mutation and equipment/controller
  update plans;
- Ruby/Python overloads not yet used by a test;
- autosized values read from SQL results;
- EnergyPlus-native storage for the OS-prefixed cooled-beam and beam-coil
  relationships;
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
