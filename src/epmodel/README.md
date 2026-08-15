# EPModel

`openstudio::epmodel` stores an OpenStudio model directly in EnergyPlus
IDD/IDF objects. The goal is to support the parts of the established
`openstudio::model` API that applications and measures rely on without keeping
a second OSM representation in memory.

EPModel is still under development. It has broad object coverage, but many
classes do not yet behave exactly like their Model counterparts. HVAC
connections are farther along than most other areas.

## What compatibility means

Model is the reference because it reflects years of real use. It is not always
consistent, and EPModel does not copy behavior that would leave an invalid
EnergyPlus model. When Model behavior is unclear:

1. write a test that shows what callers can observe;
2. keep the object graph valid if a change is rejected;
3. document any intentional difference; and
4. review Model production changes separately.

A matching class or method name is not enough. Compatibility can include:

- constructors, overloads, inheritance, and Ruby/Python bindings;
- defaults, optional values, reset methods, autosizing, and autocalculation;
- references, ownership, replacement, removal, and cloning;
- HVAC connection changes and traversal order;
- save/load behavior;
- execution from Ruby or Python; and
- successful EnergyPlus simulation and comparable results.

## Storage and conversion

`epmodel::Model` derives from `Workspace` and uses the EnergyPlus IDD. It loads
and saves IDF directly. EnergyPlus objects and their references are the saved
model.

An OSM can be brought into EPModel through the existing translators:

1. `openstudio::osversion::VersionTranslator` updates the OSM.
2. `openstudio::energyplus::ForwardTranslator` converts it to IDF.
3. EPModel loads the IDF.

This conversion does not guarantee that every Model convenience is available
or that simulation results are identical.

## Loading and repair

Construction from `IdfFile` and `Model::load(...)` creates concrete EPModel
wrappers for registered EnergyPlus object types. Other objects remain usable
through the generic workspace wrapper. Construction from an existing
`Workspace` preserves EPModel wrapper types already present in that workspace;
generic workspace objects remain generic.

EPModel canonicalizes imported data after loading. Canonicalization repairs
missing or inconsistent references when the intended connection is clear. If
repair would require guessing, it removes the smallest invalid piece and logs
what happened.

Normal API calls assume the model has already been canonicalized. Repair code
belongs with the class that owns the affected relationship. See
[AGENTS.md](AGENTS.md) for the implementation rules.

## HVAC connections

Model saves a general connection graph made from `OS:Connection` objects and
numbered ports. EnergyPlus instead uses component node fields, branches,
connector lists, splitters, mixers, supply and return paths, equipment lists,
and node lists.

EPModel implements connection and traversal methods by reading the EnergyPlus
branches, connectors, paths, and node fields. It does not add `OS:Connection`
objects to the IDF.

The base classes describe common connection shapes:

| Class | Usual shape |
| --- | --- |
| `StraightComponent` | One air or plant stream |
| `WaterToAirComponent` | One air stream and one water stream |
| `WaterToWaterComponent` | Two or more plant connections |
| `AirToAirComponent` | Two air streams |
| `ZoneHVACComponent` | Equipment owned by a thermal zone |
| `Mixer` / `Splitter` | Several inlets or outlets |

Each concrete class still decides where it may be connected, which object owns
the connection, and what is removed with it. Air-system behavior and closing
topology work are summarized in [AirSystemTopology.md](AirSystemTopology.md),
and plant behavior and its broad-core stopping point are in
[PlantSystemTopology.md](PlantSystemTopology.md). Horizontal wrapper work is
selected using [HVACComponentRoadmap.md](HVACComponentRoadmap.md).

## Identity and ownership

EnergyPlus does not save OpenStudio handles, so handles change after save/load.
Names and object references carry saved identity. Names can be missing or
duplicated, so relationship code should use typed targets and pointer APIs
instead of searching by name. Node fields should use the shared node helpers so
renames update every live reference.

For relationships stored in more than one place, one object must own the
change and the other views must follow it. Examples include:

- outdoor-air assignments stored through zone sizing and per-space lists;
- fans and coils contained by packaged HVAC equipment;
- radiant surfaces stored through EnergyPlus surface groups; and
- plant components represented by rows on an EnergyPlus branch.

A contained child must not be able to rewire its parent's internal air path on
its own.

## Objects that EnergyPlus does not save directly

Some Model objects have no standalone EnergyPlus object. EPModel keeps these
as runtime-only `ModelObject` wrappers. Current examples include nodes, child
coils whose fields live on zone equipment, and speed data stored in parent
extensible rows.

Types marked `is_transient` are found or created by type and name. Some owning
classes also mark ordinary companion objects as runtime-only while presenting
a larger object, as the dedicated outdoor-air system does. Attached child
wrappers read and write their parent's saved fields. If they can be removed and
kept by the caller, they must retain their values after detachment.

`Model.hpp` contains the creation methods. `Model.cpp` maps EnergyPlus object
types to concrete wrappers.

## Finding current implementation status

There is no generated Model/EPModel comparison table in the repository. Such a
table becomes stale quickly, and declarations alone do not show behavior.

For a particular class, check:

1. its public header and `Schema Alignment Notes`;
2. its implementation and tests under `src/epmodel/test`;
3. any translator, Ruby, Python, or simulation test that uses it;
4. `resources/energyplus/ProposedEnergy+.idd` and
   `resources/model/OpenStudio.idd`; and
5. Git history when the reason for a design choice is not clear from the code.

Use the Input Output Reference shipped with the configured EnergyPlus version.
A separately checked-in PDF can easily be the wrong version.

HVAC has the most complete connection, ownership, and reload support. Plant
topology has reached its representative broad-core stopping point, while the
air roadmap has a short closing set of bridge and reload work. After that,
development should expand horizontally across component families using real
workflows and the class-local notes as evidence. Many classes in other areas
currently provide only their EnergyPlus fields and a subset of Model behavior.
Ruby/Python use and numerical agreement must be tested separately.

## Integration workflows

The larger EPModel workflow collection lives in
[OpenStudio-resources](https://github.com/NatLabRockies/OpenStudio-resources/tree/develop/epmodel).
It contains OSWs, their supporting measures, and shared input files. This
repository should keep only examples intended to ship with OpenStudio and
tests that belong in the normal build.

A workflow shows that its particular path works. It does not prove that every
method on the classes it touches is complete.

## Header notes

Public wrapper headers use `Schema Alignment Notes` for class-specific facts.
They should identify the Model counterpart, say what works, explain unusual
EnergyPlus storage, list intentional differences, and state what is still
missing. EnergyPlus-only wrappers should simply say that no Model counterpart
exists.

## Ruby and Python bindings

To expose a production wrapper through SWIG:

- add its source and headers to `src/epmodel/CMakeLists.txt`;
- add the public header to `EPModelObjectIncludes.hpp`;
- add its forward declaration to `EPModel_Common_Include.i`;
- add it to the appropriate EPModel SWIG submodule; and
- wire a new submodule into CMake, Python imports, and Ruby initialization when
  necessary.

Do not bind unfinished generated wrappers. A SWIG entry only shows that the
binding was generated; run the Ruby or Python code before claiming it works.

## Other useful files

- [AGENTS.md](AGENTS.md): implementation and review rules.
- [AirSystemTopology.md](AirSystemTopology.md): air-system support and air
  backlog.
- [PlantSystemTopology.md](PlantSystemTopology.md): plant-system contract,
  maturity, and stopping point.
- [HVACComponentRoadmap.md](HVACComponentRoadmap.md): rules and priorities for
  horizontal HVAC wrapper work.
- [scaffolds/README.md](scaffolds/README.md): the historical scaffold source
  directory.
- `resources/energyplus/ProposedEnergy+.idd`: EnergyPlus schema used by
  EPModel.
- `resources/model/OpenStudio.idd`: schema used by Model.
