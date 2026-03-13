# IDD Schema Alignment (OpenStudio <-> EnergyPlus)

This directory tracks the effort to align the OpenStudio model schema (OpenStudio.idd) with the EnergyPlus IDD.
The core goal is to make OpenStudio's `openstudio::model::Model` and `ModelObject` ecosystem fully compatible
with EnergyPlus schema so that `openstudio::model::Model::load` can load any **valid** IDF for the supported
EnergyPlus version (one OpenStudio version maps to one E+ version).

Key ideas captured so far:
- OpenStudio model schema is currently based on **OpenStudio.idd**, which differs from **Energy+.idd**.
- Long-term target is full alignment of OpenStudio schema with EnergyPlus, while preserving (or carefully
  documenting) API changes in `ModelObject` subclasses.
- EnergyPlus IDD changes should be minimal. Surgical changes are expected to resolve key HVAC differences so
  OS-only Node/Connection types are not required in the aligned model. OS will instead adopt EnergyPlus
  connective tissue (`Branch`, `BranchList`, `ConnectorList`, etc.).
- Some EnergyPlus IDD additions are still expected. These should be passive additions that carry OS-specific
  information but can be ignored by the EnergyPlus engine.

Current artifacts:
- IDD locations: `../../resources/model/OpenStudio.idd` (current OpenStudio IDD) and
  `../../resources/energyplus/ProposedEnergy+.idd` (EnergyPlus proposed IDD).
- `os_hvac_concepts.md`: How HVAC topology is expressed in `src/model`, including loops, `HVACComponent` base
  classes, and how `OS:Connection` encodes node-style relationships.
- `idd_mapping.md`: High-level two-way OS↔E+ IDD mapping summary, including explicit OS-only and E+-only type
  lists.
- `idd_mapping_appendix.generated.md`: Machine-generated full inventory tables for all OS and E+ types with
  translator evidence.
- `os_idd_object_relationships.md`: HVAC‑only object‑list relationships derived from `OpenStudio.idd`.
- `scripts/generate_os_idd_object_relationships.py`: Script to regenerate `os_idd_object_relationships.md`.

## epmodel (EnergyPlus-aligned model sandbox)

The `../../src/epmodel` directory hosts an experimental standalone model library used to explore a future
EnergyPlus-aligned OpenStudio data model. It lives in `openstudio::epmodel` and is deliberately kept separate
from the existing `openstudio::model` implementation while alignment work is incubated.

### Why epmodel exists

`src/epmodel` provides a safe place to prototype the transition without destabilizing the existing model API.
OpenStudio’s current model layer is based on `OpenStudio.idd`. The long-term alignment goal is to use
`Energy+.idd` as the schema source of truth, and epmodel is built on `Energy+.idd` from the start.

### Current status

epmodel includes a `Model` that derives from `Workspace` and enforces `IddFileType::EnergyPlus`, plus generated
class scaffolding across the full EnergyPlus IDD object inventory and core HVAC infrastructure (e.g.,
`HVACComponent`, `StraightComponent`, `AirLoopHVAC`, `BranchList`, `Branch`, and `Node`).
It is fully standalone and does **not** inherit from the existing `openstudio::model` classes (for example
`ParentObject`), even though that might be reconsidered later.

Current capability includes EnergyPlus-backed object loading, generated scalar field accessors for all scaffolded
types, and generic object/field access through `epmodel::ModelObject` and `WorkspaceObject` primitives. The major
remaining work is parity behavior: implementing and validating non-scalar relationships, topology semantics,
canonicalization guarantees, and API-compatible behavior so `openstudio::model` behavior is reproduced faithfully on
top of EnergyPlus schema storage.

### Handle persistence (EnergyPlus IDD)

Because epmodel uses the EnergyPlus IDD, objects **do not** have a handle field in the schema. Handles still
exist at runtime (they are part of `WorkspaceObject`), but they are **not persisted** to IDF and will be
regenerated on load/clone. Do not rely on handles for stable identity across save/load; use names or explicit
keys instead.

### Transient ModelObject types

Epmodel supports transient `ModelObject` instances that exist in-memory but are not persisted to the saved file.
This allows API parity with `openstudio::model` for objects that are part of HVAC topology (such as `Node`) while
keeping the EnergyPlus-backed IDF clean. Transient objects are created and retrieved by name just like regular
objects, and the model provides factory helpers (for example `Model::getOrCreateTransientByName<T>`) to ensure
only one instance exists for a given name (case-insensitive), with empty names treated as an error.

### openstudio::epmodel::ModelObject names
ModelObject names are not guaranteed, so implementation should remain defensive around empty/duplicate-name
cases and use `nextName(...)` patterns where appropriate.

### Node inlet/outlet resolution

`Node::inletModelObject()` and `Node::outletModelObject()` depend on HVAC topology. The current approach is
intentionally hybrid and avoids caching:

- **StraightComponent fast path:** `StraightComponent::inletModelObject()` /
  `StraightComponent::outletModelObject()` use direct field lookups via `inletPort()` / `outletPort()` for speed
  and simplicity.
- **Topology path for nodes:** `Node::inletModelObject()` / `Node::outletModelObject()` use the
  owning loop’s topology path (supply or demand as applicable). In practice this means traversing
  `AirLoopHVAC::supplyComponents(...)` and `AirLoopHVAC::demandComponents(...)` to resolve adjacent HVAC objects.
- **Demand-side topology:** `AirLoopHVAC::demandComponents(...)` now returns a
  demand path for implemented HVAC cases (including zone splitter/mixer and currently supported terminals), with
  behavior validated by `src/epmodel/test/IDF_SmallOffice_GTest.cpp`.
- **Loop traversal elsewhere:** other traversal helpers (for example
  `HVACComponent::airLoopHVAC()`) use `Loop::components()`, which concatenates `supplyComponents` and
  `demandComponents`.
- **No caching initially:** topology queries may be more expensive, but they are correct and
  deterministic. Caching can be added later if performance becomes a concern (for example, using adjacency
  caches or port fields where applicable).

### Developer Notes (from epmodel implementation reviews)

These notes capture working design guidance that emerged while building `openstudio::epmodel` APIs to mirror
`openstudio::model`.

- API parity and mutability boundaries:
  - For types that already exist in `openstudio::model`, epmodel should mirror public API shape and semantics.
    Do not add new public methods unless parity divergence is intentional and documented.
  - For connective-tissue types introduced for EnergyPlus schema alignment (no
    `openstudio::model` counterpart), keep mutators implementation-only in `*_Impl` and keep wrapper public API
    minimal.
  - Avoid exposing low-level `*ObjectName` string setter/getter APIs unless
    that API already exists in `openstudio::model`.

- Canonicalization contract:
  - Canonicalization is the central repair/assurance phase and should run at model construction/load boundaries,
    not as an ad hoc runtime crutch in normal API flows.
  - Canonicalization does **not** guarantee a single global deterministic type
    order. The same object graph may be canonicalized in different per-type orders depending on context.
  - `*_Impl::doCanonicalize` methods may call related-object canonicalizers when
    cross-type guarantees are needed.
  - Outside canonicalizers, normal API methods should **not** invoke canonicalization; they should assume
    canonical state and rely on established invariants.
  - When cross-type ordering is not guaranteed, refactor canonicalization scope
    upward so ordering is guaranteed there. Do not use low-level fallback paths to paper over ordering issues.
  - After canonicalization, prefer assertions and direct logic over fallback
    branches, chatty logging, and defensive throw paths for guaranteed states.

- Implementation style:
  - Keep public wrapper classes thin. For existing `openstudio::model`-parity
    types, put substantive behavior, relationship mutation, and helper logic in `*_Impl`; public wrapper methods
    should primarily forward to the impl.
  - If adding a new aligned parent type (for example `Curve` or
    `ResourceObject` in epmodel), add the corresponding `*_Impl` layer too. Do not concentrate new behavior in the
    public base class because that breaks the existing wrapper/impl contract.
  - Prefer high-level object APIs (`getModelObjectTarget`, typed helpers, etc.)
    over low-level workspace field access when both express the same behavior.
  - Prefer composition of existing typed APIs over direct field-level methods.
    Use low-level field access only when no equivalent API composition exists.
  - Prefer pointer/object-target linkage APIs over direct name-string writes for object relationships; reserve
    `setString(...)` for true scalar/string data.
  - Treat EnergyPlus connective-tissue objects (`Branch`, `BranchList`,
    `AirLoopHVAC:SupplyPath`, `AirLoopHVAC:ReturnPath`, etc.) as storage representation while keeping topology
    APIs conceptually aligned with `openstudio::model`.
  - Keep helper methods implementation-private when they are scaffolding
    details rather than stable model-facing behavior.
  - Prefer C++ standard library routines (`<algorithm>`, `<ranges>`, etc.) over handwritten
    loops/boilerplate when clarity improves (project is C++20).
  - Add short intent comments for non-trivial control flow and parity-driven behavior so future edits preserve
    invariants.

- Name lookup and object creation:
  - Keep by-name lookup and creation semantics aligned with `openstudio::model`.
    Do not introduce generic by-name get-or-create behavior for regular persisted model objects.
  - In epmodel, keep generic by-name get-or-create limited to transient factory types (for example `Node`) where
    name-keyed identity avoids duplicate topology objects during wiring.
  - Do not expose new `getOrCreate*` APIs on public wrappers for existing `openstudio::model` types unless parity
    requires it.
  - Keep domain-object scaffolding `getOrCreate*` logic at canonicalization/initialization boundaries, not routine
    post-canonical getters.

- Testing guidance:
  - Keep topology and behavior tests at public API level where possible.
  - Prefer direct `ModelObject` comparisons over handle comparisons unless handle identity is specifically under
    test.
  - Limited impl-level tests are acceptable when behavior is difficult to assert cleanly through public APIs.
  - Primary IDF-load integration/regression suite for current epmodel HVAC API behavior is
    `src/epmodel/test/IDF_SmallOffice_GTest.cpp`.

### DSOA / OA Controller / CMV Pattern

- Canonical source-of-truth for zone OA assignment in epmodel is:
  `Space -> ThermalZone -> Sizing:Zone -> DesignSpecification:OutdoorAir:SpaceList`.
- CMV = `Controller:MechanicalVentilation`.
  In this section, "CMV entries" means CMV extensible groups where each group stores:
  - `Zone or ZoneList Name` (the served `ThermalZone`)
  - `Design Specification Outdoor Air Object Name` (the zone's `DesignSpecification:OutdoorAir:SpaceList`)
  - `Design Specification Zone Air Distribution Object Name` (currently blank in epmodel scaffolding)
  These CMV groups are derived E+ runtime projection, not authoritative storage.
- Canonicalization behaves like pseudo reverse-translation: it normalizes multiple representational forms into one
  canonical graph and logs fixups. Example: if DSOA assignment appears in non-canonical or duplicated forms,
  canonicalization converges it to canonical list-based storage and removes invalid/duplicate connective-tissue
  state.
- epmodel has no explicit forward translator surface, so we do not have a single late-stage place to derive
  transient E+ runtime projections (including CMV extensible groups). Therefore some projections must be kept
  synchronized in real time at required API mutation points. This is intentionally explicit and can be tedious.
- For CMV specifically, synchronization ownership lives at `AirLoopHVAC`
  level (`syncControllerMechanicalVentilationZoneOutdoorAirEntries()`), where loop scope and served zones are
  known. Implementation should call high-level impl mutators (`clear...` + `add...`) on CMV rather than raw
  workspace operations from unrelated types.
- Space-level DSOA setter supports both zoned and unzoned spaces:
  zoned writes to zone-owned DSOA SpaceList; unzoned writes to an orphan model-owned DSOA SpaceList. Zone
  assignment changes migrate the Space assignment between these homes, then trigger loop-level CMV synchronization.
- This pattern motivates a potential future pseudo forward-translation phase
  (for example `Model::finalize()` / `ModelObject::finalize()`):
  canonicalization would remain pseudo RT (normalize into canonical model graph), while finalize would perform
  pseudo FT work (derive runtime-facing projections in one deliberate pass).
  Until then, projection sync remains an explicit API-mutation responsibility.

### Outstanding DSOA Work (epmodel)

- `ControllerMechanicalVentilation` canonical synthesis currently populates
  loop-scoped Zone + DSOA/DSOA:SpaceList extensible groups only; `DesignSpecification:ZoneAirDistribution`
  linkage is not implemented yet.
- No OA math/aggregation behavior yet (current work is structural scaffolding).

### API/Field Divergence Tracking (for 500+ types)

These notes are intentionally lightweight and are **not** a comprehensive list of all current API/field
differences.

Current convention:

- Keep running notes as we discover differences during implementation/review.
- Prefer per-type notes in `src/epmodel/<Type>.hpp` (`Schema Alignment Notes`) when a type has an important
  divergence from `openstudio::model`.
- Keep notes concise and factual: what differs now, and any obvious follow-up.
- If a type has no notable note yet, that does not mean it is already at parity.

Recommended header note template:

```cpp
// Schema Alignment Notes:
// - API: <method or behavior> currently delegates to <object/field> in E+ schema.
// - Field Mapping: <OS concept> maps to <EnergyPlus object/field(s)>.
// - TODO(parity): Replace/adjust when <target parity milestone>.
```

If/when we do a full audit, we will capture a comprehensive type-by-type pass separately.

## Workplan

1. Reconcile `OpenStudio.idd` and the current `Energy+.idd` proposal
1. AirLoopHVAC supply side APIs (single duct)
1. AirLoopHVAC demand side APIs
1. Update Workflow for epmodel (load epmodel::Model instead of model::Model, remove EP translation)
1. Demonstrate a functioning end to end workflow (We don't need comprehensive APIs to do this)
1. AirLoopHVAC outdoor air systems APIs
1. AirLoopHVAC supply side (dual duct) APIs
1. Zone / System Sizing and supporting HVAC APIs
1. PlantLoop supply side APIs
1. PlantLoop demand side APIs
1. ZoneHVAC APIs
1. Identify possible additions to the Energy+.idd
1. Building envelope, Space, SpaceType, etc
1. Loads, LoadDefinition, etc
1. All of the APIs that are not HVAC, envelope, loads

## OSM Version Translation

OpenStudio bundles an OS version translator to update older OSM files to the latest schema. We do not expect new
translations beyond the current v3.11 release. Instead, the OpenStudio-to-EnergyPlus translator will do the heavy
lifting going forward.

Once the model layer is aligned to EnergyPlus, the EnergyPlus version translator should make a separate OSM
translator unnecessary. We still expect one final OpenStudio-to-OpenStudio translation step from OS v3.11 to what
will become v4.0. The existing OpenStudio -> EnergyPlus translator can likely serve as that final bridge, with
any remaining EnergyPlus version translation applied afterward.

Expect to enhance the OpenStudio-to-EnergyPlus translator on the road to OpenStudio 4.0.
Additions to the EnergyPlus IDD should be coordinated with development of `openstudio::epmodel`.

## Possible Migration Pathway

It is technically feasible to run `openstudio::model` and `openstudio::epmodel` in parallel during migration.
That enables a staged transition instead of a single cutover.

During the transition, the workflow can remain familiar:

```text
Seed OSM (<= v3.11) -> OS version translation (to v3.11) -> Model Measures -> EnergyPlus Translator -> EnergyPlus Measures -> Simulation
```

The key difference is that `openstudio::epmodel` APIs become available inside EnergyPlus Measures. This allows IDF
manipulation through high-level OpenStudio APIs instead of field-level edits.

As `openstudio::epmodel` approaches full API parity with `openstudio::model`, reliance on Model Measures written
against the legacy `openstudio::model` API should decline. If this path succeeds, typical workflows can simplify
to:

Most existing Model Measures should be portable to EnergyPlus Measures with
minimal code changes (primarily measure type/context and assumptions about
OSM-vs-IDF inputs).

```text
Seed IDF -> EnergyPlus Measures (using `openstudio::epmodel` APIs) -> Simulation
```

## Related GH Issues (running list)

- [Additional Properties](https://github.com/NatLabRockies/EnergyPlus/issues/8775)

## Challenges to Address

- Canonicalization now provides a deliberate sanitization/repair phase at load/create boundaries. Conceptually, this
  is similar to a lightweight reverse translator: it normalizes representational variants into a canonical in-memory
  graph and logs fixups.
- We still do not have an explicit forward-translation-equivalent phase. Some runtime projections/derived structures
  must currently be maintained at mutation points, which spreads pseudo-FT responsibilities across API code.
- Without translation, it is also unclear how OpenStudio should manage IDF object ordering. Historically,
  OpenStudio has preferred to write IDFs in logical order rather than grouping objects strictly by type. This
  convention predates OpenStudio at NLR. The underlying OpenStudio Workspace does support explicit object ordering,
  but maintaining that order in real time for each API action might be impractical.

### Possible Solutions

- Continue with EnergyPlus-backed model API implementation (as prototyped in epmodel), with canonicalization as the
  explicit pseudo-RT normalization surface.
- Introduce a finalize phase (for example `Model::finalize()` and/or `ModelObject::finalize()`) that runs before
  save/close and acts as pseudo-FT: compute/refresh required derived runtime-facing projections in one deliberate
  place.
- As an alternative, use an updated EnergyPlus forward translator instead of finalize for pseudo-FT responsibilities
  (object ordering control and required simulation-object injection).
- Keep the OS schema and model API implementation largely the same, but
  methodically drive behavior/API parity across the now scaffolded full EnergyPlus
  IDD coverage, and extend the EnergyPlus translation layer to support full
  round-trip to and from EnergyPlus IDF format.

## Related schema-alignment docs

This sandbox is tracked alongside the IDD schema-alignment effort:

- `doc/idd-schema-alignment/README.md`: Overview and scope of the alignment work.
- `doc/idd-schema-alignment/idd_mapping.md`: full OS↔E+ IDD mapping summary (includes OS-only and E+-only lists).
- `doc/idd-schema-alignment/idd_mapping_appendix.generated.md`: generated full inventory tables.
- `doc/idd-schema-alignment/os_idd_object_relationships.md`: HVAC-only OpenStudio IDD object-list relationships.
- `doc/idd-schema-alignment/os_hvac_concepts.md`: How HVAC topology is expressed in `src/model`.
- `doc/idd-schema-alignment/campaigns/`: OpenCode-first manifest workflow for post-saturation parity campaigns,
  including the minimal manifest contract, operator docs, file map, manifests, and examples.
- `doc/idd-schema-alignment/scripts/epmodel_campaign_cli.py`: manifest-driven backend CLI for code-first target
  resolution, local run state, and resumable campaign execution.
