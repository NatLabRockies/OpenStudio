# Plant-system topology in EPModel

This page describes the plant-loop behavior that EPModel currently promises
at its representative 80-percent stopping point. It is a behavior and boundary
document, not an active roadmap or class inventory; class-local parity notes
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

The transactional evidence falls into four capability archetypes:

1. **Core loop and single-owner branches.** Canonical loop construction,
   ordered traversal, typed nodes, companion scaffolds, and `PipeAdiabatic`
   supply/demand attachment, relocation, and removal establish the base branch
   contract.
2. **Air- or zone-owned water coils.** Standalone `CoilHeatingWater` and
   `CoilCoolingWater`, the heating coil in
   `AirTerminalSingleDuctConstantVolumeReheat`, and the exact heating/cooling
   children of an ordinary-zone `ZoneHVACFourPipeFanCoil` can move without
   changing their air-side parent, sibling, controller, or zone ownership.
3. **Multi-loop equipment with distinct roles.** Exact secondary, source, or
   heat-recovery moves are covered for `HeatExchangerFluidToFluid`, both
   equation-fit water-to-water heat pumps,
   `ThermalStorageChilledWaterStratified`, `ChillerElectricEIR`, and both
   plant-loop EIR heat pumps. Surviving primary/load/condenser roles, companion
   links, settings, and owner lifetimes remain unchanged.
4. **Companion, lifecycle, and workflow evidence.** `SizingPlant` companions
   swap atomically between proven loops; storage retains its uniquely owned
   `WaterHeaterSizing` until its final owner is removed. The representative
   hot-water, chilled-water, and condenser-water slice also has Ruby and
   successful EnergyPlus workflow evidence.

Where applicable, the exact paths above include rejection-before-mutation,
rollback and retry, default and parallel branch shapes, save/load, and
owner-removal evidence. They are exact type-and-role contracts, not generic
`StraightComponent`, `WaterToAirComponent`, or `WaterToWaterComponent`
behavior. In particular, contained coils outside the named parents, generic
condenser moves, and tertiary roles on other chiller families are not implied.
Consult the class header and focused tests for each operation's precise
preconditions.

## Uneven maturity and evidence levels

Plant support spans scalar relationships, in-memory topology, save/load,
post-load mutation, language bindings, and EnergyPlus execution. A type may be
strong at one level and incomplete at the next. Use its `Schema Alignment
Notes`, implementation, focused tests, translator coverage, and the configured
EnergyPlus IDD; do not infer maturity from registration or a matching class
name.

## Recommended stopping point

The representative plant effort has reached its intended broad-core milestone:
canonical loop infrastructure and lifecycle, transactional branch editing, and
several materially different one-, two-, and three-loop component families are
covered through failure, retry, and save/load. Further work is primarily
family-specific depth rather than a prerequisite for using or extending the
plant model. Treat the following items as demand-driven follow-up, not as an
active completion checklist.

The plant topology roadmap is therefore closed at the useful 80-percent
boundary. New plant topology should start only from a concrete component or
workflow need, not from an attempt to generalize every branch and ownership
combination.

## Demand-driven boundaries

- Add another topology family or contained owner only for a concrete use case,
  with exact role, ownership, rejection, rollback, reload, and removal proof.
- Treat connected direct removal, clone/cross-model transfer, and unusual
  malformed imports as separate designs rather than generic branch behavior.
- Select additional language, SQL/autosizing, and numerical evidence through
  [HVACComponentRoadmap.md](HVACComponentRoadmap.md).

The corresponding air contract and stopping point are in
[AirSystemTopology.md](AirSystemTopology.md).
See [README.md](README.md) for the broader EPModel design and storage model.
