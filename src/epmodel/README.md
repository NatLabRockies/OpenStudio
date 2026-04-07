# epmodel

`src/epmodel` hosts a standalone OpenStudio model library built directly on
the EnergyPlus schema. It lives in `openstudio::epmodel` and exists so the
project can explore a future EnergyPlus-aligned model layer based on
`Energy+.idd` without destabilizing the long-lived `openstudio::model` stack
that is built around `OpenStudio.idd`.

At a high level, epmodel is no longer just a narrow experiment around a few
HVAC wrappers. It has grown into a broad model layer with real object
coverage, its own topology and canonicalization rules, and a large amount of
API work aimed at reproducing the canonical `openstudio::model` API. That
parity with `openstudio::model` is the central goal of the project. It is
still an incubation branch of the architecture, but it should be read as a
serious model implementation, not as a throwaway prototype.

## Why epmodel exists

The motivating tension is straightforward:

- OpenStudio's canonical public model API is widely adopted and too
  significant to deprecate in whole.
- EnergyPlus is the persistence and simulation schema that ultimately matters
  to many workflows.
- The two object models do not line up one-to-one, especially in
  relationship-heavy areas where OpenStudio exposes higher-level modeling
  concepts over more fragmented EnergyPlus storage. HVAC topology is one
  important example, but it is not the only one.

epmodel exists to make EnergyPlus the persisted source of truth while still
reproducing the canonical `openstudio::model` API and user-facing semantics as
faithfully as possible. That means the library has to solve two problems at
once:

1. preserve essentially all of the `openstudio::model` programming experience,
   with only small exceptions where the existing surface cannot or should not
   be carried forward unchanged
2. accept that many relationships have to be stored and repaired according to
   EnergyPlus rules rather than OpenStudio's historical internal schema

Keeping epmodel separate from `openstudio::model` is deliberate. It allows the
project to evolve storage choices, canonicalization behavior, and wrapper
shape in an EnergyPlus-first way without creating churn in the existing model
implementation before the tradeoffs are well understood.

## What The Codebase Covers Today

epmodel now spans much more than a small HVAC island. The code under
`src/epmodel` reaches into many domains, even though the amount of deliberate,
hands-on implementation work is not uniform across them. The tree includes
types in areas such as:

- HVAC loops, components, zone equipment, thermostats, setpoint managers, and
  availability managers
- plant and air-side families, including water-to-air, water-to-water, and
  air-to-air component groups
- schedules, schedule bases, resource objects, and sizing-period objects
- geometry-facing and enclosure-facing domains such as spaces, surfaces,
  constructions, materials, glazing, and shading
- space loads, exterior loads, and related instance objects
- electrical and generation domains including generators, inverters, storage,
  and photovoltaic performance objects
- AirflowNetwork-related objects and other EnergyPlus-specific families

The practical takeaway is that epmodel should be understood as a growing model
layer for the broader EnergyPlus object space, not just as an HVAC sandbox.
At the same time, the deepest sustained implementation effort has still been
concentrated in some parts of the model more than others, with HVAC remaining
the most active front.

## Core Architectural Ideas

### EnergyPlus Is The Persisted Schema

`epmodel::Model` derives from `Workspace` and enforces
`IddFileType::EnergyPlus`. The model is not a thin facade over
`openstudio::model`; it is its own implementation with its own impl types and
its own rules about how typed wrappers map onto EnergyPlus-backed storage,
even as the public wrapper hierarchy is intended to mirror
`openstudio::model`.

This matters because many modeling concepts that feel like first-class objects
in canonical OpenStudio APIs are not stored that way in EnergyPlus. That is
not unique to epmodel; the model API has always exposed a higher-level view
over persisted data rather than acting as a direct view into the persistence
layer. epmodel continues that pattern, but it does so against `Energy+.idd`
instead of `OpenStudio.idd`.

### Typed Object Materialization Happens At Import Boundaries

Construction from `IdfFile`, construction from `Workspace`, and
`Model::load(...)` all try to materialize concrete epmodel impl types where
those types exist. That gives the library a chance to restore a rich typed
object graph immediately instead of leaving the model in a generic workspace
state.

In other words, importing content into epmodel is not just "read the file and
store some IDF objects." It is also the point where the library rebuilds the
best available typed interpretation of that file.

### Canonicalization Is A First-Class Part Of Model Construction

After import and cloning, epmodel runs canonicalization with
`SanitizationPolicy::Repair`. This is one of the most important architectural
differences to keep in mind when reading the code.

Canonicalization is not treated as an optional cleanup utility. It is the
phase where epmodel normalizes representational variants, repairs recoverable
structure, drops the minimum invalid content necessary when recovery is not
possible, and establishes the invariants that normal API methods are expected
to rely on afterward.

That design is a response to the reality of EnergyPlus-backed storage. Many
relationships can be represented in more than one partial or inconsistent way,
especially when content comes from imported files, cloning, or intermediate
mutation states. It is also a recognition that incoming IDF content may be
inaccurate, incomplete, or simply broken. In practice, epmodel often has to
deal with content that was authored or edited by humans, and that means the
library cannot assume the persisted file is already internally coherent.
epmodel chooses to make canonicalization the place where that incoming content
is normalized back into a coherent in-memory model.

### EnergyPlus Connective Tissue Is Part Of The Real Model

Objects such as `Branch`, `BranchList`, `ConnectorList`, and related path
objects are not treated as incidental implementation details that can simply
be ignored. In EnergyPlus, they are part of how topology is actually persisted.

epmodel therefore treats them as legitimate storage representation while still
building toward parity with the higher-level `openstudio::model` traversal and
convenience APIs. This is one reason the code often looks relationship-driven
rather than scalar-field-driven: the topology is real, and the connective
tissue is part of that reality.

## Identity, Persistence, And Transient Topology

### Handles Are Runtime Identity, Not Stable File Identity

Because epmodel uses the EnergyPlus IDD, handles are not persisted into saved
IDF content. Handles still exist at runtime as part of `WorkspaceObject`, but
they are regenerated on load and clone. Code should not treat handles as a
stable identity across save/load boundaries. Where stable identity matters,
names and explicit object relationships are the safer anchors.

### Names Need To Be Treated Defensively

`openstudio::epmodel::ModelObject` names are not guaranteed to exist, and the
code should not assume they are globally unique just because a wrapper is
typed. That is the current behavior, not necessarily the final policy;
canonicalization may eventually adopt a stronger rule that globally uniquifies
names. Until then, implementation code should stay defensive around empty
names and duplicate-name cases and should continue using `nextName(...)` and
related patterns where needed.

More importantly, object relationships in epmodel should not be modeled
through names in the first place. Relationship handling should go through the
typed target and pointer APIs, such as `getTarget(...)` and `setPointer(...)`,
so the object graph is expressed directly instead of being reconstructed from
name strings.

### Some Topology Objects Are Intentionally Transient

epmodel supports transient `ModelObject` instances that exist in memory but
are not written out to the saved file. This is mainly used where the public
modeling surface wants object identity even though EnergyPlus does not persist
the same concept as a standalone object.

The current factory-backed transient type is `Node`. That is an important
detail, but the larger point is architectural: epmodel is willing to keep
runtime-only `ModelObject` wrappers when they are needed to preserve the
canonical model API, even if EnergyPlus does not persist the same concept as a
standalone object. `Node` is the clearest current example of that policy.

Transient objects are created and retrieved by name. That by-name identity is
intentional; it prevents the topology layer from silently multiplying
equivalent runtime objects during wiring and traversal.

## Relationship-Driven Modeling

One of the easiest ways to misunderstand epmodel is to expect every useful
modeling concept to have one obvious persisted home. In many cases that is not
how the EnergyPlus object graph works.

Several important surfaces in epmodel are therefore relationship-driven:

- loop topology is expressed through branches, connectors, nodes, and ordered
  traversal paths
- ownership and adjacency are often recovered from typed traversal APIs rather
  than from a single scalar field
- some EnergyPlus-facing objects are best understood as derived projection
  state rather than as the canonical home of the relationship

One example of this broader pattern is outdoor-air assignment. It is useful
here because it shows how epmodel chooses an authoritative relationship path.
In the current model, the canonical zone outdoor-air relationship runs
through:

`Space -> ThermalZone -> Sizing:Zone -> DesignSpecification:OutdoorAir:SpaceList`

This illustrates a larger implementation pattern in epmodel: choose an
authoritative relationship path, normalize to it, and keep any derived
EnergyPlus-facing projection state synchronized through typed owner APIs.

## HVAC Topology Notes

`Node::inletModelObject()` and `Node::outletModelObject()` are a good example
of how epmodel approaches topology. A fan, coil, or pump can often answer
inlet and outlet questions from its own ports. A `Node` is different. It is
part of the loop connective tissue, so its upstream and downstream neighbors
have to be resolved from the owning loop topology rather than from a local
field lookup alone.

In practice, that means:

- `StraightComponent::inletModelObject()` and
  `StraightComponent::outletModelObject()` use direct port-based lookups where
  that is sufficient
- `Node::inletModelObject()` and `Node::outletModelObject()` resolve through
  ordered loop traversal paths
- `Node::airLoopHVAC()` and `Node::airLoopHVACOutdoorAirSystem()` resolve
  ownership from canonicalized loop and outdoor-air-system traversal surfaces,
  with a few targeted branch-node checks where current mutation flows still
  need them
- more general helpers such as `HVACComponent::airLoopHVAC()` can use
  `Loop::components()`, which concatenates supply and demand paths, but
  supply-side, demand-side, and outdoor-air-specific traversal helpers should
  still be preferred when role-specific behavior matters

No caching is assumed by default here. The current bias is toward correct and
deterministic traversal first, with caching added only if performance proves it
is necessary.

## Current Status

The big-picture summary is that epmodel is broad, structurally serious,
and still selectively incomplete.

It already has complete coverage of the EnergyPlus IDD type set, including
type-safe accessor methods for scalar properties and fields on those types. It
also has a real import and repair story, a typed model layer across many
domains, and a large amount of `openstudio::model` parity work.
At the same time, it does not yet include every type that is exclusive to the
original `OpenStudio.idd`.
For the concrete backlog of `OpenStudio.idd`-exclusive types that still need
to migrate into epmodel, see `doc/idd-schema-alignment/idd_mapping.md` under
`## OS-only Types`.

What is still incomplete is not basic type presence or scalar field coverage.
The big-picture distinction is that HVAC is already fairly well developed,
while form, fabric, and loads have not yet received the same level of focused
implementation work. The main remaining gaps are therefore less about whether
epmodel has the corresponding EnergyPlus types and more about where sustained
human development effort has gone so far.

## Active HVAC Parity Work

Although epmodel spans many domains, HVAC is still the most active parity area
right now. The list below is meant to summarize the current implementation
fronts without turning the README into a day-by-day work log.

### Scope

The main HVAC parity surface currently centers on:

- `src/epmodel/HVACComponent`
- `src/epmodel/ZoneHVACComponent`
- `src/epmodel/WaterToAirComponent`
- `src/epmodel/WaterToWaterComponent`
- `src/epmodel/AirToAirComponent`
- `src/epmodel/Mixer`
- `src/epmodel/Splitter`
- `src/epmodel/StraightComponent`
- `src/epmodel/Loop/AirLoopHVAC.hpp`
- `src/epmodel/Loop/PlantLoop.hpp`
- `src/epmodel/HVACComponent/ThermalZone.hpp`

### Zone HVAC, Unitary System, and Air Terminals

This remains a high-priority area because the core zone and air-side anchors
are in place, but many of the ergonomic relationship helpers that make the
canonical model pleasant to use still need to be finished at the family level.

The main remaining gaps are:

- attached fan, coil, and component helpers
- availability and operating schedule relationships
- inlet, outlet, and control-node conveniences
- stronger zone attachment and equipment-list ergonomics

#### Compound HVAC Relationship Strategy

For compound zone and unitary HVAC types, the parent object should be the
place that keeps the internal air path consistent.

In practice, that means the fan, coils, and other contained components should
still be available through normal typed relationships, but the parent decides
which nodes they use and in what order they are connected. Internal nodes with
clear user meaning should be exposed through the parent compound itself. We
should preserve that structure through the normal typed APIs instead of
letting unrelated child objects break it and then trying to repair the damage
afterward.

This also means direct attempts to change the connectivity of contained
components should be rejected through the normal typed APIs. If a fan or coil
is owned by a compound unitary, operations such as disconnecting it or moving
it onto another node should fail rather than silently damaging the parent
topology. Containment queries such as `containingHVACComponent()` are the
mechanism for enforcing that rule.

Canonicalization is still where we repair bad persisted state. If an IDF load,
raw field edit, or other non-canonical input leaves the internal wiring in a
bad state, canonicalization should put it back into a valid epmodel form.

When an internal node has a clear meaning to users, epmodel may expose an
accessor for that node on the owning compound even if the canonical
`openstudio::model` type never did. That is meant to make common workflows
easier, not to replace or break existing ones. The compound still owns the
wiring itself, but the returned `Node` is a normal model object that users can
inspect and rename.

`ZoneHVACUnitHeater` is the first concrete example of this pattern: the parent
owns the internal air path, exposes the meaningful internal fan-outlet node on
the compound, and rejects direct typed topology edits on the contained
air-side components.

### Water-To-Air Families

The main remaining gaps are:

- performance curves
- schedules and control relationships
- speed, stage, and performance-data APIs
- explicit air-side and plant-side coupling helpers
- family-consistent companion-object access

### Water-To-Water Families

The main remaining gaps are:

- performance curves
- schedules and control relationships
- staging and extensible performance data
- explicit plant-loop coupling helpers
- family-consistent companion-object access

### Shared Relationship Cleanup

Some of the remaining work is not really about one HVAC family. It is about
cleaning up cross-cutting relationship patterns so families can build on a
more consistent base.

That cleanup is follow-on work, not a restart of the current infrastructure.
The main remaining gaps are:

- canonical schedule-type validation where the canonical model enforces
  schedule type keys
- direct inlet, outlet, and control-node conveniences on remaining component
  families
- performance curve and table relationship helpers that repeat across owners
- consistent optional companion-object access patterns
- methodical removal of remaining raw name-lookup fallbacks from ordinary
  typed accessors, keeping repair paths in canonicalization only

### Outdoor-Air Completion

The main remaining gaps are:

- populating `DesignSpecification:ZoneAirDistribution` when zone-owned
  sizing or distribution data exists
- keeping `Space`, `ThermalZone`, `SizingZone`, and derived outdoor-air
  projection state synchronized through mutation paths
- implementing or explicitly bounding outdoor-air math and aggregation
  behavior
- adding regression coverage for zone reassignment and projection rebuilds

### Deferred AirLoopHVAC Follow-On

The single-duct `AirLoopHVAC` anchor work is in a reasonably good stopping
state. What remains here is mostly follow-on surface area rather than missing
foundational structure.

The main remaining gaps are:

- dual-duct APIs
- supply-splitter and multi-splitter surfaces
- wider relationship conveniences around the existing air-loop anchors

### EnergyPlus-Only Wrapper Work

Some wrappers have no canonical `openstudio::model` counterpart. Those types
still matter, but they should not be forced into an artificial parity story.

The current guidance is:

- do not invent false canonical counterparts
- prioritize EnergyPlus-only wrappers when there is clear epmodel usability
  value
- keep this work behind canonical-wrapper gaps unless it unblocks real
  workflows

## Active Non-HVAC Work

The big-picture gap outside HVAC is that epmodel is not yet developed to the
same degree in form, fabric, and loads. The list below is not exhaustive, but
it captures two important examples.

### ScheduleRuleset

epmodel now has a literal `ScheduleYear` wrapper for EnergyPlus
`Schedule:Year`, which is the correct EnergyPlus-backed object identity.
What remains to be determined is how epmodel should model canonical
`ScheduleRuleset`. The main remaining work is not scalar field coverage on
`Schedule:Year`. It is the higher-level non-scalar relationship surface around
days, rules, week schedules, special days, and the other structure that makes
`ScheduleRuleset` a first-class model object in `openstudio::model`.

### Space Load Definitions

This is currently one of the clearest non-HVAC development gaps. epmodel has
instance-side wrappers for several load objects such as `People`, `Lights`,
and equipment loads, but it does not yet carry forward the corresponding
definition-side model in the way the canonical `openstudio::model` API does.
That matters because the OpenStudio load model is built around the separation
between reusable definitions and placed instances. Bringing that structure
forward is a significant part of making loads, and eventually more of form and
fabric, feel like complete model domains rather than just EnergyPlus object
coverage.

## Type-Local Parity Notes

The source of truth for wrapper-level parity claims is the `Schema Alignment
Notes` block in epmodel headers under `src/epmodel/**/*.hpp`.

Those notes should compare epmodel types to the canonical
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
