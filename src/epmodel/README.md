# epmodel

`src/epmodel` hosts a standalone OpenStudio model library built directly on
the EnergyPlus schema. It lives in `openstudio::epmodel` and exists so the
project can explore a future EnergyPlus-aligned model layer based on
`Energy+.idd` without destabilizing the long-lived `openstudio::model` stack
that is built around `OpenStudio.idd`.

`openstudio::epmodel` is actively evolving into a broad model layer with
meaningful object coverage, its own topology and canonicalization rules, and
substantial API work aimed at reproducing the canonical
`openstudio::model` surface. Achieving strong parity with
`openstudio::model` is the project's central goal. 

## Why epmodel exists

The motivating tension is that:

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
implementation before the tradeoffs are well understood. At the same time, the
nearby, stable `openstudio::model` implementation remains an important source
of truth and reference point for epmodel build-out.

## Core Architectural Ideas

### EnergyPlus Is The Persisted Schema

`epmodel::Model` derives from `Workspace` and enforces
`IddFileType::EnergyPlus`. In practical terms, `openstudio::epmodel::Model`
loads and saves IDF content directly, unlike `openstudio::model::Model`, which
loads and saves OSM content.

That removes a whole translation boundary inside epmodel itself. Once content
is in IDF form, epmodel does not need a separate translator layer to turn that
IDF into some other persisted model representation before normal model APIs can
operate on it.

### Migration Pathway

This does not mean existing OSM assets lose a migration path. The established
`openstudio::osversion::VersionTranslator` still provides the upgrade path for
older OpenStudio models into the current `openstudio::model` schema, including
the current 3.11 generation of OSM files.

From there, the existing EnergyPlus `ForwardTranslator` provides the next step:
translate the current `openstudio::model::Model` to IDF, then load that IDF
into `epmodel::Model`. The practical migration story is therefore incremental
rather than disruptive: old OSM content can move forward through the existing
OpenStudio upgrade machinery, then cross once into EnergyPlus-backed epmodel
storage.

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
especially when IDF content comes from unknown sources. It also reflects the
fact that incoming IDF content may be inaccurate, incomplete, or simply
broken.

In practice, epmodel often has to deal with content that was authored or
edited by humans, and that means the library cannot assume the persisted file
is already internally coherent. epmodel chooses to make canonicalization the
place where that incoming content is normalized back into a coherent in-memory
model. In implementation terms, that work is centered on
`openstudio::epmodel::ModelObject_Impl::doCanonicalize(...)` and the derived
overrides that repair object-specific structure.

### EnergyPlus Connective Tissue Is Part Of The Real Model

Objects such as `Branch`, `BranchList`, `ConnectorList`, and related path
objects are not treated as incidental implementation details that can simply
be ignored. In EnergyPlus, they are part of how topology is actually persisted.
Today this is most visible in HVAC, but the same pattern will likely appear in
other domains as epmodel expands.

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

epmodel supports transient `ModelObject` instances that exist at runtime but
are not written to the saved file. This is used when the canonical modeling
surface wants object identity for a concept that EnergyPlus does not persist
as a standalone object.

`Node` is the oldest and still the clearest example, but it is no longer the
only one. More generally, epmodel is willing to keep runtime-only wrappers
when that is the cleanest way to preserve canonical `openstudio::model`
semantics over EnergyPlus-backed storage.

Transient objects are created and retrieved by name. That by-name identity is
intentional: it prevents wiring and traversal code from silently creating
duplicate runtime objects for the same conceptual element.

A second recurring case appears when canonical `openstudio::model` factors one
EnergyPlus object into multiple wrapper objects. In those cases, epmodel may
expose transient companion wrappers that read and write through to a real
persisted parent object instead of introducing persisted children that do not
exist in the EnergyPlus schema or in the saved IDF.

The clearest current examples are four radiant `ZoneHVAC` families whose
canonical OpenStudio API exposes plant-side coil children:

- `ZoneHVACLowTempRadiantConstFlow`
- `ZoneHVACLowTempRadiantVarFlow`
- `ZoneHVACCoolingPanelRadiantConvectiveWater`
- `ZoneHVACBaseboardRadiantConvectiveWater`

The same architectural pattern also applies to
`ZoneHVACBaseboardConvectiveWater`. In all five cases, canonical
`openstudio::model` exposes a coil child that is meant to participate in
plant-loop placement and traversal, but EnergyPlus stores the relevant
plant-side identity and fields on the parent zone equipment object instead of
as a separate standalone coil object. epmodel therefore preserves the
canonical coil child as a transient view over the persisted parent object.

The current solution is deliberate:

- the persisted branch row still stores the real parent `ZoneHVAC` object
- the transient child coil can still be added to the plant loop through the
  canonical child-facing API
- high-level plant-loop traversal then projects that stored parent row back to
  the transient child coil when the branch inlet and outlet nodes match that
  coil's specific heating or cooling water-node pair

This keeps the saved EnergyPlus graph truthful while still preserving the
canonical OpenStudio experience that callers expect. The object that the user
adds to the loop is also the object that the high-level loop traversal APIs
return, even though the underlying branch storage still belongs to the parent
zone equipment object.

The current transient type inventory is:

- Topology connective tissue: `Node`
- Canonical radiant and baseboard coil children projected from a persisted
  parent object: `CoilHeatingLowTempRadiantConstFlow`,
  `CoilCoolingLowTempRadiantConstFlow`,
  `CoilHeatingLowTempRadiantVarFlow`,
  `CoilCoolingLowTempRadiantVarFlow`, `CoilCoolingWaterPanelRadiant`,
  `CoilHeatingWaterBaseboardRadiant`, `CoilHeatingWaterBaseboard`
- Canonical variable-speed speed-data children projected from parent-coil
  extensible rows:
  `CoilCoolingWaterToAirHeatPumpVariableSpeedEquationFitSpeedData`,
  `CoilHeatingWaterToAirHeatPumpVariableSpeedEquationFitSpeedData`,
  `CoilWaterHeatingAirToWaterHeatPumpVariableSpeedSpeedData`

`src/epmodel/Model.hpp` is the authoritative registration point for transient
factory types. When a new transient type is added there, this README should be
updated in the same change so the documented inventory stays complete.

### Some Canonical Surface Intent Is Projected Into EnergyPlus Companion Objects

Transient child objects are only one half of the radiant-family problem. The
other half is that canonical `openstudio::model` sometimes stores higher-level
intent that EnergyPlus does not store in the same form.

The low-temperature radiant families are the clearest example. Canonical
OpenStudio exposes a selector such as `radiantSurfaceType()` and a derived
`surfaces()` view. EnergyPlus does not persist that selector directly. Instead,
it persists a referenced `ZoneHVAC:LowTemperatureRadiant:SurfaceGroup` object
that spells out the actual surfaces and their fractions.

epmodel handles that mismatch deliberately:

- the real persisted EnergyPlus surface-group object remains the storage truth
- the canonical OpenStudio-facing API is preserved on the parent wrapper
- `setRadiantSurfaceType(...)` rewrites the persisted EnergyPlus surface group
  from the current attached zone and the chosen canonical selector
- `surfaces()` reads the actual stored EnergyPlus group membership back out
- `radiantSurfaceType()` returns a canonical value only when the stored surface
  group exactly matches one of the recognized canonical buckets for the
  attached zone; otherwise it returns `none`

This is different from the transient-coil pattern. In the coil case, epmodel is
preserving missing child object identity over one persisted parent object. In
the surface-group case, epmodel is preserving missing high-level canonical
intent over a lower-level persisted EnergyPlus companion object.

The practical rule is:

- use transient wrappers when canonical OpenStudio exposes child objects that
  EnergyPlus flattened away
- use additive canonical views over persisted companion objects when canonical
  OpenStudio exposes higher-level intent that EnergyPlus stored only as emitted
  projection state

## Relationship-Driven Modeling

One of the challenges of the EnergyPlus object graph is that a modeling
concept does not always have one obvious persisted home. epmodel therefore has
to choose an authoritative relationship path, normalize to it, and treat some
other EnergyPlus-facing objects as derived projection state rather than as the
canonical home of the relationship.

Outdoor-air assignment is a representative example. In the current model, the
canonical zone outdoor-air relationship runs through:

`Space -> ThermalZone -> Sizing:Zone -> DesignSpecification:OutdoorAir:SpaceList`

The important point is not just that this path exists. It is that epmodel uses
this path as the authoritative one, normalizes imported or edited state back
to it, and keeps any derived EnergyPlus-facing projection state synchronized
through typed owner APIs.

In the current implementation, that rule shows up concretely in a few places:

- `Space::designSpecificationOutdoorAir()` first follows the zone-owned
  `SizingZone` path to `designSpecificationOutdoorAirSpaceList()` and resolves
  the per-space assignment there. Only if that canonical path is absent does
  it fall back to scanning lists that already contain the space.
- `Space::setDesignSpecificationOutdoorAir(...)` writes through the same owner
  path. Zoned spaces are routed to the zone's `DesignSpecification:OutdoorAir:SpaceList`;
  unzoned spaces are routed to an orphan list. The setter then removes the
  space from every other list so one space does not quietly accumulate multiple
  competing assignments.
- `SizingZone_Impl::doCanonicalize(...)` makes the representation explicit. If
  a zone has spaces and any outdoor-air assignment exists, canonicalization
  rebuilds one `DesignSpecification:OutdoorAir:SpaceList` from current zone
  membership and resolved per-space assignments, then points `Sizing:Zone` at
  that list. Direct `Sizing:Zone -> DesignSpecification:OutdoorAir` storage is
  treated as non-canonical and normalized away into the space-list form.
- The zone-facing `ThermalZone` scalar API is still preserved, but it is a
  projection over the underlying space assignments rather than an independent
  persisted owner. `zoneSharedDesignSpecificationOutdoorAir()` only reports a
  zone-level DSOA when every space in the zone resolves to the same object, and
  the corresponding setters create or reuse one shared DSOA and push it back
  down onto all of the zone's spaces.

That is the larger relationship-driven pattern in epmodel. Public APIs can
still present a clean zone-facing surface, but the code chooses one
authoritative storage path underneath, rewrites incoming state back to that
path, and treats other views as projections over it.

## HVAC Topology Notes

For the canonical `openstudio::model` picture, see
`doc/idd-schema-alignment/os_hvac_concepts.md`. That document describes the
OpenStudio HVAC topology built around explicit `OS:Connection` wiring and the
familiar model-layer loop scaffolding.

The epmodel challenge is not that this public topology disappears. It is that
the persisted EnergyPlus representation underneath is different. As noted
earlier, EnergyPlus connective tissue such as `Branch`, `BranchList`,
`AirLoopHVAC:SupplyPath`, `AirLoopHVAC:ReturnPath`, and `Connector:*` objects
is part of the real model. That changes how traversal and ownership questions
have to be answered.

`Node` is a good example of that difference. In canonical OpenStudio, a node is
easy to think about as one more object in the explicit connection chain. In
epmodel, a fan, coil, or pump can often still answer inlet and outlet
questions from its own port fields, but a `Node` usually cannot. Its upstream
and downstream meaning depends on where it sits in the canonicalized supply,
demand, or outdoor-air traversal path for the owning loop.

In practice:

- `StraightComponent::inletModelObject()` and
  `StraightComponent::outletModelObject()` still use direct port-based lookups
  where that is sufficient
- `Node::inletModelObject()` and `Node::outletModelObject()` resolve adjacency
  by asking the owning loop for its ordered `supplyComponents(...)` or
  `demandComponents(...)` path and then finding the neighboring objects around
  the node in that path
- `Node::airLoopHVAC()` and `Node::airLoopHVACOutdoorAirSystem()` resolve
  ownership from canonicalized loop and outdoor-air-system traversal surfaces,
  with a few targeted branch-node checks retained for current mutation flows
- OpenStudio-style meta traversal APIs such as `Loop::components()`,
  `supplyComponents(...)`, and `demandComponents(...)` still matter in
  epmodel; the difference is that epmodel has to reconstruct them over
  canonicalized EnergyPlus topology, and role-specific helpers should be
  preferred when role-specific behavior matters

That does not mean every `StraightComponent` is freely insertable everywhere a
straight-through port pair exists. Some canonical wrappers deliberately narrow
placement to one loop role. `WaterUseConnections`, `RefrigerationCondenserWaterCooled`,
`RefrigerationCompressorRack`, and `SwimmingPoolIndoor` are the clearest
current plant-demand-only examples in this category: despite inheriting the
generic straight-component shape, canonical `openstudio::model` and epmodel
only allow them on plant loop demand nodes because they represent demand-side
water-use, refrigeration-rack condenser-water, refrigeration-condenser, and
pool-heating subsystems rather than
general-purpose air or plant inline components. For `RefrigerationCompressorRack`, the condenser schedule helpers rely on the shared epmodel schedule-type registry rather than wrapper-local validation alone, and the same-loop plant-demand reattach path is now covered explicitly in the entity test suite. For `SwimmingPoolIndoor`, that
placement parity is only one slice of the story: epmodel still intentionally
omits the canonical surface and schedule relationship helpers and currently
retains extra cover-factor default/reset conveniences that are documented as
wrapper-local behavior rather than canonical parity. `HeatPumpAirToWater` is a
different restricted case: the wrapper itself is non-insertable, and canonical
loop attachment happens through the underlying heating and cooling
operation-mode objects instead.
`PlantComponentUserDefined` is another special case in a different direction:
its canonical `openstudio::model` wrapper is still a one-connection
`StraightComponent`, but the EnergyPlus-backed epmodel wrapper also preserves
the persisted Number of Plant Loop Connections field and Plant Connection 2-4
loading and flow-request scalar fields as direct pass-through accessors while
still enforcing the canonical one-connection write contract and intentionally
omitting the canonical EMS, actuator, and ambient-zone companion-object
surface. Canonical `openstudio::model` also bootstraps those EMS companion
objects in its constructor; epmodel intentionally stops at the persisted
EnergyPlus scalar defaults for Plant Connection 1.

The guiding principle is that these traversal APIs should reflect the
canonicalized topology accurately and consistently. That may carry performance
implications in some cases, but those should be addressed as needed through
targeted optimization and/or caching rather than by weakening the topology
model itself.

### Compound HVAC Ownership

Several canonical HVAC family shapes follow the same general principle:
`ZoneHVACComponent` types with multiple internal series components, `AirTerminal`
types with internal components, and `AirLoopHVACUnitary` families all rely on
the parent object to own the internal topology. Child fans, coils, and other
contained components should still be available through normal typed
relationships, but the parent decides which nodes they use, in what order they
are connected, and which internal node roles are meaningful enough to expose.

That has two consequences. First, direct attempts to rewire contained
components through normal typed APIs should fail rather than silently damaging
the parent topology. Second, canonicalization remains the place where bad
persisted state is repaired back into a valid epmodel form when an IDF load or
other non-canonical input arrives in a broken shape.

This pattern is not universal. Radiant families are the clearest
counterexample: they are more relationship-driven, and epmodel may use
transient child wrappers or companion-object views to preserve the canonical
object shape without pretending EnergyPlus persisted separate child objects.
`GroundHeatExchangerVertical` is a related persisted-storage case: the
canonical straight-component wrapper is backed by a
`GroundHeatExchanger:ResponseFactors` object plus linked
`GroundHeatExchanger:System` and `GroundHeatExchanger:Vertical:Properties`
companions, and plant-loop traversal projects the stored system branch row
back to the wrapper callers attached to the loop. The current epmodel parity
slice still intentionally omits the canonical `groundTemperature()` and
`maximumLengthofSimulation()` helpers because the EnergyPlus-backed storage
does not expose direct persisted fields for that OpenStudio-only state.

## Current Status

Current status, in brief:

- EnergyPlus IDD coverage is complete, including type-safe scalar accessors
  across that type set.
- The library already includes import, repair, canonicalization, and a typed
  model layer across many domains.
- `openstudio::model` parity work is substantial, with HVAC currently the most
  developed area.
- Not every `OpenStudio.idd`-exclusive type has migrated yet. For that backlog,
  see `doc/idd-schema-alignment/idd_mapping.generated.md` under
  `## OS Types With No EP Output Evidence`.
- The main remaining gaps are now less about basic type presence and more about
  depth of focused implementation effort, especially outside HVAC.

## Active HVAC Parity Work

epmodel aims to expand across the full model domain, but HVAC is still the
most active parity area right now. The list below is meant to summarize the
current implementation fronts without turning the README into a day-by-day
work log.

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

#### Remaining ZoneHVAC Wrappers

Most of the main `ZoneHVACComponent` families now have their core parity and
ownership work in place. The remaining wrappers are a smaller set of
special-case types whose open work does not fit the same compound-unit or
radiant-family patterns documented above.

The current remaining set is:

- `ZoneHVACIdealLoadsAirSystem`
- `AirLoopHVACUnitarySystem`
- `RefrigerationAirChiller`
- `FanZoneExhaust`
- `ZoneVentilationWindandStackOpenArea`

These should not be treated as another generic compound-zone-unit batch.

- `ZoneHVACIdealLoadsAirSystem` is still a true `ZoneHVAC` wrapper, but its
  remaining work is mostly canonical relationship, schedule, and helper
  surface rather than child-topology ownership.
- `AirLoopHVACUnitarySystem` lives in `ZoneHVACComponent` for historical API
  reasons, but it is really a broader unitary-system parity track rather than
  one more zone-equipment family.
- `RefrigerationAirChiller` is a zone-adjacent refrigeration object, not part
  of the same family shape as the unitary and radiant `ZoneHVAC` families
  described above.
- `FanZoneExhaust` and `ZoneVentilationWindandStackOpenArea` are both genuine
  zone-side objects, but their remaining work is mostly specialized airflow
  and zone-linkage behavior, not compound internal topology.

The practical consequence is that the broad `ZoneHVAC` ownership strategy is
already established. The remaining wrappers should be handled as targeted
special cases, with their own canonical evidence and design review, instead of
being forced into patterns that were designed for unitary, radiant, or
water-heater families.

### Water-To-Air Families

Most of the core water-to-air surface is now in place. The direct coil families
generally expose their canonical schedules, curves, speed-data APIs, and
air/water topology helpers through the current `WaterToAirComponent` base and
derived wrappers. The remaining active cleanup work is narrower:

- `HeatPumpAirToWater` now covers the wrapper-level operating-mode schedule, air-node-name, and direct curve-reference helpers, but the wrapper itself remains non-insertable and epmodel still lacks the canonical heating/cooling operation-mode child wrappers that own plant-loop placement.
- `HeatPumpAirToWaterFuelFiredCooling` now covers the canonical companion-heating link and direct required/optional curve-reference helpers, and it stays plant-supply-only like the canonical straight-component wrapper; the remaining documented delta is the omitted air-source-node helper for the translator-emitted `OutdoorAir:Node` companion object.
- `HeatPumpAirToWaterFuelFiredHeating` now matches the same heating-side parity slice: canonical default curves and explicit-curve constructor, companion-cooling and optional curve-reference helpers, and plant-supply-only placement are all preserved; the remaining documented delta is again the omitted air-source-node helper for the translator-emitted `OutdoorAir:Node` companion object.
- `WaterToAirComponent` still documents missing base clone and remaining
  canonical convenience behavior, even though the shared air/water topology
  contract is present.
- Some variable-speed wrappers still intentionally stub SQL-backed autosized
  result lookups.
- AirflowNetwork equivalent-duct mapping has been added for the equation-fit
  water-to-air heat-pump coils and still needs to be extended where documented
  on the remaining family wrappers.

### Water-To-Water Families

Most water-to-water wrappers are now near parity or parity with documented
deltas. The shared `WaterToWaterComponent` topology contract is in place, and
many derived wrappers already expose their canonical curves, schedules,
plant-loop conveniences, autosized-helper surface, and companion-object access
where those concepts apply. The remaining work is mostly targeted:

- SQL-backed autosized result lookup is still stubbed or incomplete on some
  chiller and heat-pump wrappers.
- `CentralHeatPumpSystem` still omits the canonical module-list/module-object
  graph until epmodel has the supporting object families.
- `ChillerElectricASHRAE205` still omits representation-file linkage until
  epmodel exposes `ExternalFile`.
- Some water-heater and thermal-storage clone, schedule-seeding, and
  sizing-application workflows intentionally differ from the canonical model
  implementation.
- The base `WaterToWaterComponent` should only grow additional shared
  convenience behavior when multiple derived wrappers need the same support.

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
still matter, but they should not be forced into an artificial parity frame.

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
- meaningful public API or behavior deltas relative to `openstudio::model`
- EnergyPlus-backed storage mapping when that mapping is not obvious

## Reference Docs

- `src/epmodel/AGENTS.md`: implementation guidance for agents and reviewers
- `doc/idd-schema-alignment/os_hvac_concepts.md`: narrative reference for
  canonical `openstudio::model` HVAC topology patterns
- `resources/energyplus/`: EnergyPlus IDD and generated schema source of truth
- `doc/idd-schema-alignment/InputOutputReference.pdf`: EnergyPlus field-level
  semantics reference
