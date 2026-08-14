# EPModel

`openstudio::epmodel` is an EnergyPlus-backed model layer. Its long-term goal is
to reproduce the useful public behavior of `openstudio::model` while storing
the model directly in EnergyPlus IDD/IDF structures.

EPModel is deliberately separate from the established Model library. That
keeps the stable OpenStudio API available while the project works through the
places where OpenStudio concepts and EnergyPlus storage do not line up. HVAC
topology is the most developed example, but the same problem appears in
relationships, reusable definitions, schedules, geometry, and other domains.

EPModel is active development, not a complete alternative to Model. Broad
object coverage or matching method names do not establish behavioral parity.

## Compatibility target

The target is equivalent public behavior where that behavior is coherent and
useful, not identical implementation or serialized text.

`openstudio::model` is the compatibility reference because it embodies years
of real use. It is not an infallible specification. When the reference has
ambiguous or internally inconsistent ownership behavior, EPModel should:

1. characterize the behavior through public observations;
2. preserve graph integrity and reject mutations atomically;
3. document a deliberate difference when copying the reference would make the
   EnergyPlus-backed model contradictory; and
4. leave changes to Model production behavior for separate human review.

Parity must be stated for a bounded capability. It includes more than the C++
surface:

- constructors, methods, overloads, inheritance, and bindings;
- values, defaults, optionality, reset, autosize, and autocalculate behavior;
- relationships, ownership, replacement, removal, and cloning;
- topology mutation and ordered traversal;
- save/load reconstruction and canonicalization;
- workflow execution through Ruby or Python; and
- EnergyPlus execution and numerical behavior.

Evidence for one dimension does not prove another.

## EnergyPlus is the persisted schema

`epmodel::Model` derives from `Workspace` and uses
`IddFileType::EnergyPlus`. It loads and saves IDF content directly. EnergyPlus
objects and relationships are therefore the persisted source of truth; EPModel
does not maintain a second OSM representation behind its API.

Existing OSM assets still have a migration path:

1. `openstudio::osversion::VersionTranslator` upgrades older OSM content into
   the current `openstudio::model` schema.
2. The EnergyPlus `ForwardTranslator` converts that Model to IDF.
3. EPModel loads the IDF and materializes the concrete wrappers it supports.

This is a migration boundary, not proof that the resulting EPModel has every
Model convenience or produces numerically identical results.

## Import and canonicalization

Construction from `IdfFile` and `Model::load(...)` materialize concrete
EPModel implementation types where a factory registration exists. Imported
objects that do not have a concrete wrapper remain usable as generic
workspace-backed objects. Construction from an existing `Workspace` preserves
concrete EPModel runtime types when they are already present; objects from a
generic workspace use the generic wrapper fallback.

Those import paths run canonicalization with repair enabled. Canonicalization
is the boundary that converts incomplete or inconsistent IDF relationships
into the coherent state normal APIs expect. Object-specific implementations
may repair recoverable structure, normalize competing representations, or
drop the minimum unsalvageable content.

Canonicalization is not a general runtime fallback. Normal API methods should
operate on established invariants. Repair decisions belong to the object that
owns the relationship, and cross-object ordering belongs at a scope that can
guarantee it. The implementation policy is in [AGENTS.md](AGENTS.md).

## Model topology and EnergyPlus topology

Canonical Model persists a general graph built from concrete `OS:Connection`
objects and numbered ports. `Node`, `PortList`, `Splitter`, and `Mixer` objects
participate in that graph.

EnergyPlus stores the same physical intent differently. Component node-name
fields coexist with connective objects such as `Branch`, `BranchList`,
`ConnectorList`, `Connector:Splitter`, `Connector:Mixer`, supply paths, return
paths, equipment connections, equipment lists, and node lists.

EPModel preserves familiar public traversal and mutation over the EnergyPlus
representation. It does not recreate an OSM connection graph in the saved
file. Equivalent inlet/outlet adjacency, loop membership, ordering, and
ownership can therefore be backed by different persisted objects.

The base families describe useful shapes, not universal placement permission:

| Family | General shape |
| --- | --- |
| `StraightComponent` | One air or plant stream |
| `WaterToAirComponent` | One air stream and one water stream |
| `WaterToWaterComponent` | Multiple plant roles, sometimes including heat recovery |
| `AirToAirComponent` | Two air streams |
| `ZoneHVACComponent` | Equipment owned by a thermal zone |
| `Mixer` / `Splitter` | Fan-in and fan-out relationships |

Concrete types still decide supported loop sides, ownership, contained paths,
and lifecycle. Current air-system coverage and priorities are summarized in
[AirSystemTopology.md](AirSystemTopology.md).

## Identity and relationships

EnergyPlus IDF does not persist OpenStudio handles. Handles remain useful
runtime identity, but they are regenerated across save/load. Persisted identity
must come from object relationships and, where EnergyPlus requires it, names.

Names need defensive handling. They may be absent or duplicated, so normal
relationship code should prefer typed targets and pointer APIs over string
search. Node fields should use the shared node resolvers so a named node becomes
a live, tracked relationship that follows later renames.

For relationship-heavy concepts, EPModel chooses one authoritative owner and
treats other representations as projections. Examples include:

- zone outdoor-air assignments owned through zone sizing and per-space lists;
- compound HVAC parents that own their internal fan/coil air paths;
- radiant surface selectors projected into persisted EnergyPlus surface
  groups; and
- loop traversal that projects an EnergyPlus branch row back to the canonical
  child wrapper callers attached.

The owning API must keep the persisted relationship and all public views in
agreement. A child controlled by a compound owner must not be able to rewire
the owner's path independently.

## Transient ModelObjects

Some canonical OpenStudio concepts need runtime object identity even though
EnergyPlus does not persist them as standalone objects. EPModel represents
those concepts as transient `ModelObject` wrappers.

The recurring patterns are:

- virtual nodes over EnergyPlus node-name fields;
- canonical child coils projected from fields on a persisted zone-equipment
  parent; and
- speed-data children projected from extensible rows on a persisted parent
  coil.

Name-keyed transient view types are created and recovered by typed name so
repeated traversal returns the same runtime concept. Their `is_transient`
markers and the public creation APIs in `Model.hpp` identify this mechanism.
Owning APIs may also mark normally persisted companion wrappers transient when
projecting runtime topology, as the dedicated outdoor-air system does.

Projected wrappers read and write through to their persisted owner while
attached, and must retain coherent detached state when removed. Factory
registration in `Model.cpp` determines which concrete wrapper is materialized;
it is not an inventory of every transient runtime state.

## Where status and evidence live

There is intentionally no checked-in generated table that claims repository-
wide Model/EPModel parity. Such tables go stale quickly and declaration or IDD
mapping alone cannot establish behavior.

Use these sources, in this order:

1. Public headers under `src/epmodel`, especially type-local `Schema Alignment
   Notes`, for the intended current contract and documented deltas.
2. Source and focused tests under `src/epmodel/test` for implemented behavior.
3. Registered workflow and translation tests for binding, migration, and
   execution evidence.
4. `resources/energyplus/ProposedEnergy+.idd` and
   `resources/model/OpenStudio.idd` for current schema facts.
5. Git history for rationale and superseded campaign evidence.

Use the Input Output Reference distributed with the configured EnergyPlus
version for field semantics. Do not rely on a separately checked-in PDF that
can drift from the schema in this repository.

Current maturity is uneven:

- EnergyPlus-backed wrappers exist across many domains.
- HVAC has the deepest relationship, topology, ownership, and persistence
  work.
- Many wrappers outside HVAC still have only scalar or partial parity.
- Binding presence, workflow execution, and numerical equivalence remain
  separately evidenced capabilities.

## External workflow corpus

Broad EPModel integration and simulation workflows are maintained in the
[OpenStudio-resources EPModel corpus](https://github.com/NatLabRockies/OpenStudio-resources/tree/develop/epmodel).
That repository owns the growing OSW collection, its supporting measures, and
shared seed files. This source repository should contain only deliberately
selected user-facing examples and tests that belong in the normal OpenStudio
build. A successful external workflow is evidence for the transitions it
exercises; it is not a repository-wide parity claim.

## Type-local schema alignment notes

Public wrapper headers use `Schema Alignment Notes` to keep class-level status
beside the API it describes. Notes should state:

- status and canonical counterpart, if one exists;
- implemented public behavior;
- intentional API or storage differences;
- non-obvious EnergyPlus field or relationship mapping; and
- remaining work at a meaningful behavioral boundary.

EnergyPlus-only wrappers should say that they have no canonical counterpart
rather than inventing a parity claim.

## Binding checklist

When a production wrapper should be exposed through SWIG:

- add its C++ source and headers to `src/epmodel/CMakeLists.txt`;
- add the public header to `EPModelObjectIncludes.hpp`;
- add its forward declaration to `EPModel_Common_Include.i`;
- add the wrapper to the appropriate EPModel SWIG submodule;
- wire a new submodule into CMake, Python imports, and Ruby initialization when
  necessary; and
- do not expose scaffold-only types as production bindings.

SWIG registration proves only that binding machinery exists. Execute the
required Ruby or Python path before claiming scripting behavior.

## Working documents

- [AGENTS.md](AGENTS.md): implementation and review rules.
- [AirSystemTopology.md](AirSystemTopology.md): current air-system topology coverage,
  evidence levels, and next priorities.
- `src/epmodel/scaffolds/README.md`: meaning of scaffold-only wrappers.
- `resources/energyplus/ProposedEnergy+.idd`: EnergyPlus schema used by
  EPModel.
- `resources/model/OpenStudio.idd`: canonical Model persistence schema.
