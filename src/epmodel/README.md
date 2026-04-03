# epmodel

`src/epmodel` hosts an experimental standalone model library for an
EnergyPlus-aligned future OpenStudio model layer. It lives in
`openstudio::epmodel` and is intentionally separate from
`openstudio::model` while schema-alignment work is incubated.

## Purpose

epmodel exists to prototype an OpenStudio model API that uses
`Energy+.idd` as the persisted schema source of truth without destabilizing
the existing `openstudio::model` implementation based on `OpenStudio.idd`.

For active parity status, queue ordering, and next steps, use:

- `.opencode/hvac-parity-docs/hvac-api-roadmap.md`

## Core Model Characteristics

- `epmodel::Model` derives from `Workspace` and enforces
  `IddFileType::EnergyPlus`.
- epmodel is standalone. It does not inherit from the existing
  `openstudio::model` class hierarchy.
- EnergyPlus connective-tissue objects such as `Branch`, `BranchList`,
  `ConnectorList`, and related path objects are treated as persisted storage
  representation.
- Public parity targets should still follow canonical
  `openstudio::model` API shape and user-visible semantics wherever that
  parity is claimed.

## Storage and Identity Notes

### Handle Persistence

Because epmodel uses the EnergyPlus IDD, handles are not persisted to saved
IDF. Handles still exist at runtime as part of `WorkspaceObject`, but they
will be regenerated on load and clone. Do not rely on handles for stable
identity across save/load boundaries. Use names or explicit object
relationships instead.

### Transient ModelObject Types

epmodel supports transient `ModelObject` instances that exist in memory but
are not written to the saved file. This is mainly used for topology-facing
API parity where OpenStudio expects object identity even though EnergyPlus
does not persist the same object directly.

Current examples include transient `Node` objects used to preserve loop and
component ergonomics while keeping the EnergyPlus-backed file clean.

Transient objects are created and retrieved by name. Generic by-name
get-or-create behavior is intentionally limited to these transient factory
types, where name-keyed identity avoids duplicate topology objects during
wiring.

### ModelObject Names

`openstudio::epmodel::ModelObject` names are not guaranteed. Implementation
code should stay defensive around empty or duplicate-name cases and use
`nextName(...)` patterns where appropriate.

## Topology Notes

### Node Inlet and Outlet Resolution

`Node::inletModelObject()` and `Node::outletModelObject()` depend on HVAC
topology and intentionally use a hybrid approach without caching.

- `StraightComponent::inletModelObject()` and
  `StraightComponent::outletModelObject()` use direct field lookups via
  `inletPort()` and `outletPort()` where that is sufficient.
- `Node::inletModelObject()` and `Node::outletModelObject()` resolve through
  the owning loop topology path instead of trying to infer adjacency from raw
  fields alone.
- `AirLoopHVAC::demandComponents(...)` is the current demand-side topology
  anchor for implemented air-side behavior.
- Other traversal helpers such as `HVACComponent::airLoopHVAC()` can use
  `Loop::components()`, which concatenates supply and demand paths.

No caching is assumed initially. Prefer correct deterministic traversal first,
then add caching only if performance proves it is necessary.

## DSOA / OA Controller / CMV Pattern

Canonical source of truth for zone outdoor-air assignment in epmodel is:

`Space -> ThermalZone -> Sizing:Zone -> DesignSpecification:OutdoorAir:SpaceList`

`Controller:MechanicalVentilation` extensible groups are treated as a derived
runtime projection, not the authoritative home of that relationship state.

Within epmodel:

- Canonicalization behaves like a pseudo reverse-translation pass. It
  normalizes representational variants into a canonical in-memory graph and
  logs repairs.
- epmodel does not currently have a separate pseudo forward-translation or
  finalize phase. As a result, some derived EnergyPlus-facing projections must
  be synchronized explicitly at mutation points.
- For CMV specifically, synchronization ownership lives at `AirLoopHVAC`
  through `syncControllerMechanicalVentilationZoneOutdoorAirEntries()`.
- Callers should manipulate CMV projection state through high-level owner
  APIs, not by editing unrelated raw extensible groups directly.
- Space-level DSOA assignment supports both zoned and unzoned spaces. Zoned
  spaces write through the zone-owned DSOA SpaceList; unzoned spaces use an
  orphan model-owned list until zone attachment changes.

## Type-Local Parity Notes

The source of truth for type-level parity claims is the `Schema Alignment
Notes` block in epmodel headers under `src/epmodel/**/*.hpp`.

These notes should compare epmodel types to the canonical
`openstudio::model` counterpart when one exists, and they should document:

- current parity status
- meaningful public API or behavior deltas
- EnergyPlus-backed storage mapping when that mapping matters
- the next concrete missing parity work

## Reference Docs

- `src/epmodel/AGENTS.md`: implementation guidance for agents and reviewers
- `doc/idd-schema-alignment/os_hvac_concepts.md`: narrative reference for
  canonical `openstudio::model` HVAC topology patterns
- `resources/energyplus/`: EnergyPlus IDD and generated schema source of truth
- `doc/idd-schema-alignment/InputOutputReference.pdf`: EnergyPlus field-level
  semantics reference
