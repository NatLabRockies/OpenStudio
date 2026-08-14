# Plant-system topology in EPModel

This page describes the plant-loop behavior that EPModel currently promises
and the order of work needed to make plant systems dependable. It is a
behavior and roadmap document, not a class inventory; class-local parity notes
and tests are the evidence for a particular type.

## Current topology contract

`PlantLoop` stores the EnergyPlus plant representation directly. A loop has a
supply side and a demand side, each represented by branches, node fields, and
the corresponding splitter/mixer connector objects. The public loop API
projects that saved structure as ordered component traversal, inlet/outlet
nodes, side-specific add/remove operations, and component-to-loop ownership.
The loop also links to and manages its sizing object, operation schemes and
schedules, availability-manager assignment, setpoint node, and canonical
branch and connector companions. Those relationships are persisted as
EnergyPlus object links; a loop relationship does not by itself imply that
the linked object has the same removal lifetime as the loop.

Condenser service uses the same EPModel `PlantLoop` wrapper with
`SizingPlant.setLoopType("Condenser")`. The scaffolded `CondenserLoop` family
is not a prerequisite for this topology contract or its representative
chilled/condenser slice.

Plant components must use typed node and object-target relationships. Names
are saved identity hints, not a substitute for a linked target. A component
that has more than one plant connection (for example, a chiller with chilled
water and condenser water) remains attached to each owner independently and
must not be removed while another owner still needs it. Air-side owners retain
control of their contained air path; a child coil cannot rewire that path by
itself.

Canonicalization repairs imported or incomplete loop structure when the
intended topology is clear. Normal API methods operate on that canonical
state. EPModel does not add `OS:Connection` objects: the EnergyPlus branches,
connectors, node fields, and object lists are the persisted source of truth.

## Safety rules for topology changes

1. Validate the side, placement, ownership, endpoints, and all affected
   loops before changing a connection.
2. A rejected operation leaves the old and new systems unchanged, including
   unresolved reference text where that is the persisted representation.
3. One owner performs each multi-object change. Related branch, connector,
   node, and equipment-list writes are one topology operation.
4. Prepare all fallible work before commit. A prepared commit is no-fail and
   only applies already-proven invariant writes.
5. If preparation makes provisional changes, rollback restores the exact
   original representation and removes only objects created by that plan.
   Record rollback ownership before invoking a setter because a setter can
   partially write and still report failure.
6. Removing a loop or branch removes only objects it owns and detaches
   surviving components. Save/load must reconstruct the same public topology.

These rules apply even when a change crosses an air-side component and one or
more plant loops.

## What works now

All evidence in this section applies to a canonicalized EPModel state. The
delivered C++ topology slice includes default loop construction with canonical
branch, connector, sizing, operation-scheme, and availability-manager
companions; ordered supply/demand traversal; typed node access; and common
scalar loop, sizing, setpoint, and operation-scheme APIs.

The transactional branch evidence is deliberately exact rather than generic:

- `PipeAdiabatic` supply- and demand-side attachment, cross-loop move,
  single-component branch removal, rejection, failure injection, rollback, and
  public-API retry are covered. The source and target branch/connective tissue
  remains consistent, and the pipe and its surviving nodes retain the expected
  lifetime.
- Standalone `CoilHeatingWater` and `CoilCoolingWater` can move between plant
  loops on the demand side while retaining their direct `AirLoopHVAC` owner,
  air-side path, controller, controller-list membership, and coil settings.
  Their source and target plant representations are checked across rejection,
  rollback, save/load, and retry paths.
- A contained `CoilHeatingWater` owned by
  `AirTerminalSingleDuctConstantVolumeReheat` can make the same exact demand
  move without rewiring its owning `AirLoopHVAC`, served `ThermalZone`, or
  `ZoneHVACAirDistributionUnit`. The terminal and child relationship, air
  nodes, settings, and zone/air-loop membership survive failure injection,
  rollback, save/load, and retry; the contained path correctly has no
  `ControllerWaterCoil`.
- An exact `CoilHeatingWater` or `CoilCoolingWater` child of a fully configured
  `ZoneHVACFourPipeFanCoil` can move between plant demand loops when the parent
  is ordinary `ThermalZone` equipment. The parent retains its fan, sibling
  coil, complete air path, zone boundary, settings, and equipment-list
  membership across rejection, rollback, save/load, and retry. Air-loop,
  outdoor-air-system, inlet-side-mixer, ambiguous-owner, and controller-owned
  variants remain rejected.
- A configured `ChillerElectricEIR` can detach from a condenser loop without
  losing its chilled-water ownership. Removing the condenser loop removes only
  condenser-owned branch, operation, and companion objects; a replacement
  condenser loop can then be attached and saved/reloaded without disturbing
  the chiller's surviving chilled-water path.

The representative C++ hot-water, chilled-water, and condenser-water vertical
slice covers construction, typed `SizingPlant` loop types, equipment and
operation relationships, rejection safety, save/load, condenser detachment,
and replacement-loop mutation. The Ruby/OpenStudio-resources workflow for this
slice also completes a successful EnergyPlus execution.

Component relationship evidence includes all five `PumpVariableSpeed`
relationships (flow-rate schedule, pump curve, RPM schedule, minimum-pressure
schedule, and maximum-pressure schedule), including invalid-target rejection
and save/load identity. `PumpConstantSpeed` flow-rate schedule and pump-curve
relationships are covered as well. `HeaderedPumpsConstantSpeed` and
`HeaderedPumpsVariableSpeed` cover flow-rate schedule and `ThermalZone`
relationships, including rejection and save/load evidence. `BoilerHotWater`
normalized efficiency-curve relationships likewise cover typed assignment,
reset, invalid-target rejection, and save/load identity.

`SizingPlant` has a total, read-only `PlantLoop` back-reference after
canonicalization, with save/load identity and canonical removal of orphan and
duplicate companions covered. An atomic public `setPlantLoop` retarget remains
deferred until it can preserve exactly one `Sizing:Plant` companion per loop.

These results establish supported topology paths, not blanket parity. Broad
`StraightComponent`, `WaterToAirComponent`, and `WaterToWaterComponent`
generalization remains incomplete; contained water coils beyond the
exact reheat-terminal and ordinary-zone four-pipe fan-coil paths remain outside
the move contract; and unusual malformed imports, broad clone or cross-model
operations, atomic sizing retarget, and numerical parity beyond the delivered
workflow remain separate work.

## Uneven maturity and evidence levels

Plant support currently spans several levels: scalar and relationship
accessors; in-memory branch placement; save/load topology; post-load mutation;
language bindings; and EnergyPlus execution with comparable results. A type
may be strong at one level and incomplete at the next. The exact paths listed
above have transactional and reload evidence, while loop infrastructure is
still ahead of broad transactional reconfiguration. Many component wrappers
also have substantially more field coverage than topology, clone/remove,
cross-model transfer, or numerical evidence.

Use the component header's `Schema Alignment Notes`, its implementation and
tests, translator coverage, and the configured EnergyPlus IDD when assessing a
specific gap. Do not infer maturity from registration, matching class names,
or the presence of a scalar test.

## Ordered plant roadmap

1. **Atomic sizing-loop retarget.** Add a public `SizingPlant` retarget that
   preserves exactly one sizing companion per loop, keeps each sizing object's
   identity and settings together, and restores both loop relationships if a
   multi-object write fails.
2. **Broader multi-owner and component topology.** Extend the proven paths to
   broader `WaterToWaterComponent` ownership and secondary/tertiary ports,
   then to additional `StraightComponent` and `WaterToAirComponent` families,
   including branch replacement, equipment-list ownership, clone/remove, and
   cross-model transfer. Keep unsupported mutators out of wrappers until their
   ownership is defined.
3. **Additional contained owners.** Apply the private relocation boundary to
   another selected compound owner only after its child roles, internal air or
   zone path, controller behavior, and removal lifetime have exact rejection,
   rollback, reload, and post-load mutation evidence.
4. **Language and numerical expansion.** Extend Ruby/Python coverage and
   EnergyPlus/numerical comparison workflows beyond the delivered
   OpenStudio-resources slice. Add broader parity matrices and SQL/autosizing
   evidence only as concrete use cases require them; keep unusual malformed
   imports deferred until their repair contract is defined.

Air-specific backlog remains in [AirSystemTopology.md](AirSystemTopology.md).
See [README.md](README.md) for the broader EPModel design and storage model.
