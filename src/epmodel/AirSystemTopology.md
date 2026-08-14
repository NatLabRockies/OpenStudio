# EPModel air-system topology

This document is the current big-picture roadmap for air-system topology in
`openstudio::epmodel`. It covers air loops, terminals, zone equipment, and the
plant connections those air-side objects own; it is not a complete plant-loop
roadmap. Detailed behavior belongs in source, type-local schema notes, and
focused tests. Historical work orders, generated inventories, test counts, and
agent logs are intentionally not repeated here.

## Goal

Preserve the public topology behavior that real OpenStudio workflows depend on
while using EnergyPlus objects as persisted storage.

Model and EPModel do not need identical internal graphs. Model persists generic
connections and ports; EPModel persists component node fields, branches,
connectors, paths, equipment connections, and transient views. The public
observations should nevertheless agree where the reference behavior is
coherent:

- what a component is connected to;
- which loop, side, zone, or compound owns each role;
- the order returned by traversal;
- what survives replacement, detachment, and removal; and
- whether save/load restores live relationships that can still be mutated.

Model is the compatibility reference, not an infallible specification.
Integrity-breaking reference behavior is characterized and reviewed rather
than copied automatically.

## Evidence levels

Readiness is scoped to a named class, relationship, or transition.

| Level | Evidence |
| --- | --- |
| R0 | The required public C++ surface is present |
| R1 | Scalar and relationship state behaves coherently |
| R2 | Graph mutation, ownership, and rejection behavior is tested |
| R3 | Save/load reconstructs the graph and post-load mutation works |
| R4 | The required Ruby or Python workflow executes |
| R5 | EnergyPlus executes, with explicit topology or result observations |

A higher level for one transition does not complete a class, its siblings, or
its numerical behavior.

## Topology contracts

The established HVAC work follows these rules:

1. Validate placement and ownership before mutation.
2. Rejected operations leave both source and target graphs unchanged.
3. Each supported role has one authoritative owner and placement.
4. Successful movement heals the old path and establishes the new path.
5. Traversal, adjacency, and ownership queries agree.
6. Detachment preserves the component; removal deletes only lifecycle-owned
   objects and heals surviving paths.
7. Compound parents control contained fan, coil, and node paths.
8. Removing one owner of multi-role equipment preserves other live roles; the
   final owner determines deletion.
9. Reload may rebuild different connective objects but must restore equivalent
   public behavior.

These are tested design contracts, not claims that every HVAC wrapper already
implements them.

## Current coverage

| Topology area | Representative implementation | Current boundary |
| --- | --- | --- |
| Air-loop foundation | Multi-zone demand branches, ordered traversal, independent connector rows, transactional insertion/removal, and single- and dual-duct loop shapes | General same-loop rebranching and arbitrary malformed imported graphs |
| Ordinary single duct | Constant-volume and VAV families use shared, plenum-aware branch transactions; VAV reheat also has scoped EnergyPlus topology execution | Reload coverage for several VAV siblings and scripting/workflow evidence |
| Supply and return plenums | Shared single-duct plenums, common returns, and independent per-deck dual-duct supply lanes support reassignment, removal, and reload | Malformed connector combinations outside tested transactions |
| PIU, induction, and beams | Series and Parallel PIU, four-pipe induction, cooled beam, and four-pipe beam have family-specific ownership and atomic removal | Beam reload/workflow evidence and secondary-port conveniences |
| Direct dual duct | Constant-volume, VAV, and VAV outdoor-air terminals use two supply decks and one zone transaction; per-deck supply and common return plenums are supported | Reload/workflow evidence for VAV and VAV outdoor-air variants |
| Outdoor and exhaust air | Outdoor/relief paths, dedicated outdoor-air membership, heat recovery, evaporative/desiccant equipment, zone exhaust, and central exhaust have representative topology | General equipment ordering and numerical performance |
| Direct air-side equipment | Representative gas heat, two-speed DX, curve-fit DX, and assisted cooling equipment retain public identity across supported placements | Broader equipment families and numerical equivalence |
| Compound systems | Representative fan coils, unitary systems, VRF variants, packaged terminals, and water-to-air heat pumps own contained paths while participating in external loops | Clone/cross-model transfer, remaining helpers, and numerical VRF behavior |

These are bounded topology results, not repository-wide API parity or complete
simulation equivalence.

## Terminal archetypes

A reference member defines the richest tested contract for one topology shape.
It is a behavioral guide, not code to copy mechanically. A sibling is covered
only after its own attachment, rejection, ownership, removal, and persistence
boundaries are exercised.

| Archetype | Reference | Current sibling position | Next closure |
| --- | --- | --- | --- |
| Ordinary single duct | `AirTerminalSingleDuctVAVReheat` | Constant-volume and VAV no-reheat, reheat, and heat-and-cool variants share the branch transactions | Add reload for VAV no-reheat and heat-and-cool siblings; exercise `VAVHeatAndCoolReheat` in a representative workflow |
| PIU | Series and Parallel PIU are paired references because their induced-air order differs | Both cover owned fan/coil paths, plant roles, plenums, repair, and reload | Topology shape is established; clone and sizing APIs are separate work |
| Induction and beam | `AirTerminalSingleDuctConstantVolumeFourPipeInduction` | Cooled and four-pipe beams cover attachment, ownership, removal, and plant cleanup | Add reload and representative workflow evidence for both beams |
| Direct dual duct | `AirTerminalDualDuctConstantVolume` for persistence; `AirTerminalDualDuctVAV` for the richer VAV surface | All three direct terminal families have focused mutation coverage | Add reload for VAV and VAV outdoor air, then representative workflow evidence |
| Inlet-side mixer | `AirTerminalSingleDuctInletSideMixer` | No same-shape sibling | Treat downstream ZoneHVAC breadth separately |
| Special single duct | No reference promoted | User-defined and variable-speed-fan terminals are C++-only wrappers in the historical scaffolds grouping with bounded tests | Establish their EMS or owned-fan contracts before expanding them |

Create a new archetype when air-stream count, ownership, branch cardinality, or
persisted projection changes observable behavior. Do not multiply archetypes
for scalar-only differences.

## Next priorities

1. Carry one `ZoneHVACUnitVentilator` using `FanSystemModel`, electric heat,
   chilled-water cooling, local outdoor air, and one plant connection through
   reload and post-load mutation. The existing implementation covers contained
   ownership and repair, but not this representative persisted configuration.
2. Close the terminal reload gaps named above. Reuse a family transaction only
   when the topology shape is actually the same.
3. Select subsequent work from real model-building scripts, measures, or OSWs.
   Define the smallest required public transition before expanding API surface.
4. Add binding and EnergyPlus evidence only when the selected workflow needs
   R4 or R5. Keep large exploratory workflows outside the core repository when
   they are evidence rather than maintained product tests.

## Broader boundaries

- clone and cross-model transfer;
- general same-loop rebranching;
- scripting overloads outside executed workflows;
- autosized and SQL-backed result conveniences;
- normalized Model/EPModel artifact comparison;
- scoped numerical comparison on clean simulations;
- multi-speed unitary stage-data architecture;
- AirflowNetwork, leakage, and space-level HVAC; and
- repair policy for malformed graphs not represented by current transactions.

Stop and seek a focused design decision when two plausible semantics produce
different public behavior, when a framework would precede two real examples,
when a test would observe storage rather than behavior, or when progress would
require changing Model production code.

## Evidence ownership

The repository-wide evidence policy is in [README.md](README.md). Earlier
curated campaign rationale is recoverable from Git at `bc9f746072`; it is not
maintained as a second status file. Do not freeze test counts, generated API
snapshots, or campaign logs here. They age faster than the contracts they are
meant to explain.
