# HVAC Topology in `src/model`

This document describes how HVAC systems are represented in the OpenStudio model layer. It focuses on the **methodology** and core building blocks (loops, HVAC components, and connections), not on every concrete derived class.

## Scope

- Covers HVAC topology in `src/model` as implemented by `Loop`, `HVACComponent`, and `Connection`.
- Emphasizes how components are connected and traversed to describe air- and water-side systems.
- Mentions related helpers (Node, Splitter, Mixer, PortList) only as needed to understand topology.

## Core Concepts

### Components connect via ports

`HVACComponent` is the base class for model objects that participate in HVAC networks. It exposes a **port-based** connection mechanism.

- A **connection** is directional: source object + source port → target object + target port.
- Ports are unsigned integers that correspond to fields on an object’s IDD definition.
- Connectivity is stored in a dedicated `Connection` object plus back-pointers from both endpoints.
- `Connection` allows for arbitrary HVAC topoligies to be expressed, but in practice the higher level OpenStudio types and APIs enforce the constraints of EnergyPlus.

Key API points:

- `Model::connect(sourceObject, sourcePort, targetObject, targetPort)` creates a `Connection` and sets pointers on both objects.
- `Model::disconnect(object, port)` removes the `Connection` and clears both endpoints.
- `Connection` is a `ModelObject` that records source/target object handles and their ports.

Relevant files:

- `src/model/HVACComponent.hpp`
- `src/model/Connection.hpp`
- `src/model/Model.cpp` (connect/disconnect)

### Nodes are HVACComponents

`Node` is a `StraightComponent` and therefore an `HVACComponent`. It provides a standardized **inlet** and **outlet** port and is used to structure system topology.  

- Many add/remove operations assume that components are connected through nodes.
- Node edges drive traversal by returning the downstream component (or a zone via PortList).

Relevant file:

- `src/model/Node.cpp`

### Splitters and mixers define branches

Branching is expressed with `Splitter` and `Mixer`:

- A **Splitter** has one inlet and multiple outlet ports (branch starts).
- A **Mixer** has multiple inlet ports and one outlet port (branch ends).

These objects are required because a `Connection` links a single (object, port) to a single (object, port); one-to-many or many-to-one flow must be represented explicitly with splitter/mixer ports and intermediate nodes.

Branches are created or removed by manipulating the splitter/mixer ports and inserting nodes as needed.

Relevant files:

- `src/model/Splitter.hpp`, `src/model/Splitter.cpp`
- `src/model/Mixer.hpp`, `src/model/Mixer.cpp`

### PortList bridges HVAC to zones

Some connections (especially for zone equipment/terminals) go through `PortList` objects, which allow multiple attachments to a single HVAC component.

- `PortList` provides an extensible set of ports backed by the IDD.
- It is used to connect zone terminals and thermal zones.
- Example: zone equipment connections use a `PortList` to attach multiple terminal units to a `ThermalZone` without implying a flow split/merge the way a `Splitter`/`Mixer` does.

Relevant file:

- `src/model/PortList.cpp`

* PortList conecptually overlaps with Splitter and Mixer and might be a historical inconsistency and arguably a design flaw in OpenStudio.

## HVACComponent-Derived Base Classes (Non-IDD)

Several classes derive from `HVACComponent` but are **base types** that do not map to a single EnergyPlus IDD object. These classes encode topology rules (port counts, allowed connections, and loop association) that concrete subclasses inherit.

### `HVACComponent`

Root type for HVAC graph participation.

- Provides the port-based connectivity model (via `Model::connect`/`Model::disconnect`).
- Caches loop membership (`AirLoopHVAC`, `PlantLoop`, `AirLoopHVACOutdoorAirSystem`) and resets caches on disconnect.
- Supplies core operations like `addToNode`, `addToSplitter`, `remove`, and `edges` that derived classes override.

Relevant files:

- `src/model/HVACComponent.hpp`
- `src/model/HVACComponent.cpp`
- `src/model/Model.cpp`

### `StraightComponent`

Base for components with **exactly one inlet and one outlet**.

- Enforces a single in/out port pair and a linear (non-branching) connection model.
- Implements `edges(...)` to traverse from inlet to outlet.
- Can appear on either air or plant loops; subclasses may restrict this further.
- `WaterUseConnections` is a representative restricted case: although it derives from `StraightComponent`, the canonical model only allows it on plant demand nodes because it models a demand-side water-use subsystem.
- `RefrigerationCondenserWaterCooled` is another plant-demand-only restricted case: despite its straight-component shape, canonical behavior only allows placement on plant demand nodes because it models a refrigeration condenser served by a condenser-water loop.
- `RefrigerationCompressorRack` is another plant-demand-only restricted case: despite its straight-component shape, canonical behavior only allows placement on plant demand nodes because a water-cooled rack rejects heat through a condenser-water loop, and the wrapper also owns the COP and optional condenser-fan curves plus condenser schedule and heat-rejection-zone helpers while deferring the refrigerated case/walk-in list convenience in epmodel. In epmodel, the condenser schedule helpers rely on the shared schedule-type registry for validation, and the remaining topology boundary was narrowed to an explicit same-loop plant-demand reattach verification rather than a documented assumption.
- `SwimmingPoolIndoor` is another plant-demand-only restricted case: despite its straight-component shape, canonical behavior only allows placement on plant demand nodes because it represents a pool heating load served from the plant demand side. epmodel mirrors that placement rule and the canonical exposed constructor defaults for average depth, maximum people, heating flow, and miscellaneous power, but it still omits the canonical surface and schedule relationship helpers and retains extra cover-factor default/reset conveniences.
- `GroundHeatExchangerVertical` is another restricted case: despite its straight-component shape, canonical behavior is limited to plant-loop non-demand nodes, including supply inlet and supply outlet placement, and rejects plant-demand or air-loop placement.
- `HeatPumpAirToWater` is another restricted case: despite its straight-component shape, the wrapper itself is non-insertable, `addToNode(...)` returns false, and canonical plant-loop attachment happens through the heating and cooling operation-mode children instead.
- `HeatPumpAirToWaterFuelFiredCooling` is another restricted case: despite its straight-component shape, canonical behavior only allows placement on plant supply nodes, and epmodel now mirrors that restriction while preserving the wrapper's direct companion/curve helper surface.
- `HeatPumpAirToWaterFuelFiredHeating` is the heating-side counterpart: despite its straight-component shape, canonical behavior only allows placement on plant supply nodes, and epmodel now mirrors that restriction while preserving the wrapper's direct companion/curve helper surface.
- `GeneratorFuelCellStackCooler` is another restricted case: despite its straight-component shape, canonical behavior only allows placement on plant-loop nodes, including supply and demand placement, and epmodel now mirrors that restriction while preserving the parent fuel-cell lookup and scalar field surface.
- `PlantComponentUserDefined` is a mixed schema-alignment case: canonical `openstudio::model` treats it as a one-connection `StraightComponent` with EMS and ambient-zone companion relationships, while epmodel preserves the EnergyPlus Number of Plant Loop Connections and Plant Connection 2-4 loading/flow-request fields as scalar pass-throughs, restricts new writes to the canonical one-connection value, and intentionally omits the OpenStudio-only companion-object API.
- Examples: `FanConstantVolume`, `PumpConstantSpeed`, `BoilerHotWater`, `CoilHeatingElectric`.

Relevant files:

- `src/model/StraightComponent.hpp`
- `src/model/StraightComponent_Impl.hpp`

### `WaterToAirComponent`

Base for components that interface **one air stream and one water stream**.

- Defines distinct air-side and water-side inlet/outlet ports.
- `addToNode` is context-sensitive: adding to an air node connects the air ports; adding to a plant node connects the water ports.
- Provides explicit air-side and water-side disconnect helpers and loop-removal helpers.
- Examples: `CoilHeatingWater`, `CoilCoolingWater`, `CoilUserDefined`.

Relevant file:

- `src/model/WaterToAirComponent.hpp`

### `WaterToWaterComponent`

Base for components that connect **two plant loops** (supply and demand), with optional tertiary connections.

- Defines four primary ports: supply inlet/outlet and demand inlet/outlet.
- Exposes `plantLoop()`, `secondaryPlantLoop()`, and `tertiaryPlantLoop()` to reflect multi-loop attachment.
- Offers distinct removal methods for each loop to preserve loop integrity.
- Examples: `ChillerElectricEIR`, `HeatExchangerFluidToFluid`, `CentralHeatPumpSystem`.

Note: Some EnergyPlus component types do not fit neatly into a single base type because they can interact with more than two loops. A common example is a water-cooled chiller with heat recovery, which can connect to chilled water, condenser, and heat-recovery plant loops simultaneously (modeled via the tertiary plant loop ports).

Relevant file:

- `src/model/WaterToWaterComponent.hpp`

### `AirToAirComponent`

Base for components that connect **two air streams** (primary and secondary).

- Defines primary and secondary air inlet/outlet ports.
- Used for heat recovery and similar devices that bridge supply and exhaust air streams.
- `addToNode` is typically implemented by subclasses to enforce correct stream placement.
- Examples: `HeatExchangerAirToAirSensibleAndLatent`, `HeatExchangerDesiccantBalancedFlow`.

Relevant file:

- `src/model/AirToAirComponent.hpp`

### `ZoneHVACComponent`

Base for equipment that **serves a single ThermalZone**.

- Defines inlet/outlet ports intended for zone exhaust/supply connections.
- `addToThermalZone` and `removeFromThermalZone` manage zone-level topology and equipment connections.
- `addToNode` supports cases where a ZoneHVAC component is placed on an air loop (e.g., DOAS feeding a zone device), with guardrails on valid locations.
- Zones attached to an `AirLoopHVAC` via an air terminal do not use `ZoneHVACComponent`; the terminal is an `HVACComponent`, and the zone connects through its `PortList`/equipment list associations.
- Examples: `ZoneHVACFourPipeFanCoil`, `ZoneHVACPackagedTerminalHeatPump`, `ZoneHVACIdealLoadsAirSystem`.

Relevant file:

- `src/model/ZoneHVACComponent.hpp`



## How Connections Are Created

### Direct connections via `Model::connect`

All connectivity is ultimately recorded with `Model::connect` (see “Components connect via ports” above). This is the primitive operation used by higher-level helpers such as `addToNode`, `addToSplitter`, and loop branch methods.

### Typical HVAC connection in OpenStudio (osm) format

Below is a minimal OSM-style schematic showing how a `Fan:ConstantVolume` connects to a `Node`, which then connects to a `Coil:Cooling:DX:SingleSpeed`. It shows the **handle-based** links and the **back-references** stored on the endpoints’ inlet/outlet port fields. Only the fields relevant to `OS:Connection` are shown.

```
OS:Fan:ConstantVolume,
  {FAN-HANDLE},                      !- Handle
  Fan 1,                             !- Name
  ,                                  !- Inlet Port (unused in this snippet)
  {CONN-NODE->COIL-HANDLE};          !- Outlet Port (back-reference to OS:Connection)

OS:Node,
  {NODE-HANDLE},                     !- Handle
  Node 1,                            !- Name
  {CONN-FAN->NODE-HANDLE},           !- Inlet Port (back-reference to OS:Connection)
  {CONN-NODE->COIL-HANDLE};          !- Outlet Port (back-reference to OS:Connection)

OS:Coil:Cooling:DX:SingleSpeed,
  {COIL-HANDLE},                     !- Handle
  Coil 1,                            !- Name
  {CONN-NODE->COIL-HANDLE},          !- Inlet Port (back-reference to OS:Connection)
  ;                                  !- Outlet Port (unused in this snippet)

OS:Connection,
  {CONN-FAN->NODE-HANDLE},           !- Handle
  Fan->Node,                         !- Name
  {FAN-HANDLE},                      !- Source Object (by handle)
  <Fan Outlet Port #>,               !- Source Port (outlet port index)
  {NODE-HANDLE},                     !- Target Object (by handle)
  <Node Inlet Port #>;               !- Target Port (inlet port index)

OS:Connection,
  {CONN-NODE->COIL-HANDLE},          !- Handle
  Node->Coil,                        !- Name
  {NODE-HANDLE},                     !- Source Object (by handle)
  <Node Outlet Port #>,              !- Source Port (outlet port index)
  {COIL-HANDLE},                     !- Target Object (by handle)
  <Coil Inlet Port #>;               !- Target Port (inlet port index)
```

### `HVACComponent::addToNode`

`HVACComponent::addToNode(Node&)` is the standard way to insert a component into a loop. Concrete derived classes override it to enforce contextual rules (air vs. plant compatibility, special port usage, etc.).

The base implementation (used by many components) handles these cases:

- If adding to a node at the **system endpoint**, it inserts the component between the endpoint node and its neighbor.
- If the endpoint isn’t a node (e.g., OA relief/oa stream), it **inserts a new node** to preserve node-based topology.
- If adding midstream, it inserts the component between the node and its downstream component, then inserts a new node after the component.

Relevant file:

- `src/model/HVACComponent.cpp`

### Adding to splitters (branches)

`HVACComponent::addToSplitter(Splitter&)` is overridden in branch-capable components to:

- Allocate a new outlet port on the splitter.
- Insert a node for the new branch.
- Connect the component to that branch node.

The actual mechanics follow the same `Model::connect` pattern with nodes inserted to preserve consistent topology.

## Loop Topology

`Loop` is the abstract base class for air and plant loops. It is **not** an `HVACComponent`; it participates in topology by owning and connecting HVAC components (nodes, splitters, mixers) via `Model::connect`. Concrete subclasses build an initial loop scaffold in `createTopology()` (core nodes, splitters/mixers, and their wiring).

### Common Loop structure

Each loop exposes a standardized set of key objects:

- **Supply side:** inlet node → components → outlet node(s)
- **Demand side:** inlet node(s) → components → outlet node
- **Branching:** splitters and mixers connect supply/demand branches

The following are common across loops:

- `supplyInletNode()`, `supplyOutletNode()` / `supplyOutletNodes()`
- `demandInletNode()` / `demandInletNodes()`, `demandOutletNode()`
- `demandSplitter()` and `demandMixer()`

### AirLoopHVAC

`AirLoopHVAC` constructs an air-side loop with zone splitters/mixers, supply and demand nodes, and optional outdoor air systems. Dual-duct loops are represented by multiple supply outlet nodes and demand inlet nodes aligned by index.

Key structural points:

- Single duct: one supply outlet node and one demand inlet node.
- Dual duct: two supply outlet nodes and two demand inlet nodes, aligned by index.
- Zone splitters/mixers define how branches attach to zones.

#### AirLoopHVAC Topology (Single-Duct, minimal scaffold)

The diagram below mirrors `AirLoopHVAC_Impl::createTopology()` and shows the initial OS:Connection wiring. Boxes are `HVACComponent` instances unless noted; the `AirLoopHVAC` object itself is **not** an `HVACComponent` but participates via its fields/ports.


```
+----------------------------------------------------------------------------------+
|                                   AirLoopHVAC                                     |
|                                                                                  |
|   +--------------------------- SUPPLY PATH ---------------------------+          |
|   | [SupplySideInletNodeName]                                        |          |
|   |          |                                                       |          |
|   |          v                                                       |          |
|   |     Node (SupplyInlet)                                           |          |
|   |          |                                                       |          |
|   |          v                                                       |          |
|   |     Node (SupplyOutlet)                                          |          |
|   |          |                                                       |          |
|   |          v                                                       |          |
|   | [SupplySideOutletNodeA]                                          |          |
|   +------------------------------------------------------------------+          |
|                                                                                  |
|   +--------------------------- DEMAND PATH ---------------------------+          |
|   | [DemandSideInletNodeA]                                           |          |
|   |          |                                                       |          |
|   |          v                                                       |          |
|   |     Node (DemandInlet)                                           |          |
|   |          |                                                       |          |
|   |          v                                                       |          |
|   | AirLoopHVACZoneSplitter                                          |          |
|   |          |                                                       |          |
|   |          v                                                       |          |
|   |      Node (Branch)                                               |          |
|   |          |                                                       |          |
|   |          v                                                       |          |
|   | AirLoopHVACZoneMixer                                             |          |
|   |          |                                                       |          |
|   |          v                                                       |          |
|   |     Node (DemandOutlet)                                          |          |
|   |          |                                                       |          |
|   |          v                                                       |          |
|   | [DemandSideOutletNodeName]                                       |          |
|   +------------------------------------------------------------------+          |
|                                                                                  |
+----------------------------------------------------------------------------------+

Legend
- Items in brackets [ ... ] are OpenStudio field names on the AirLoopHVAC object.
- “Node (name)” and HVAC objects (e.g., AirLoopHVACZoneSplitter) are ModelObjects.
- Each vertical line segment represents an OS:Connection (ModelObject type = Connection)
  linking an OutletPort -> InletPort between the adjacent ModelObjects.
```


Branching to zones happens by adding additional outlet ports on the zone splitter (and matching inlet ports on the zone mixer), with a `Node` created per branch and zone equipment/terminals inserted between the splitter and mixer.

#### AirLoopHVAC Topology (Single-Duct with equipment + one zone)

Example with supply-side components (fan, heating coil, cooling coil) and one zone branch. This matches the usual `addToNode` insertion pattern: each inserted component sits between two `Node` objects on the supply path. On the demand side, the terminal sits between the zone splitter and the zone inlet `PortList`, then the `ThermalZone` connects through its zone air return node before reaching the zone mixer.

```
+----------------------------------------------------------------------------------+
|                                   AirLoopHVAC                                     |
|                                                                                  |
|   +--------------------------- SUPPLY PATH ---------------------------+          |
|   | [SupplySideInletNodeName]                                        |          |
|   |          |                                                       |          |
|   |          v                                                       |          |
|   |     Node (SupplyInlet)                                           |          |
|   |          |                                                       |          |
|   |          v                                                       |          |
|   |     Fan:ConstantVolume                                           |          |
|   |          |                                                       |          |
|   |          v                                                       |          |
|   |     Node (AfterFan)                                              |          |
|   |          |                                                       |          |
|   |          v                                                       |          |
|   |     Coil:Heating:Water                                           |          |
|   |          |                                                       |          |
|   |          v                                                       |          |
|   |     Node (AfterHeatingCoil)                                      |          |
|   |          |                                                       |          |
|   |          v                                                       |          |
|   |     Coil:Cooling:Water                                           |          |
|   |          |                                                       |          |
|   |          v                                                       |          |
|   |     Node (SupplyOutlet)                                          |          |
|   |          |                                                       |          |
|   |          v                                                       |          |
|   | [SupplySideOutletNodeA]                                          |          |
|   +------------------------------------------------------------------+          |
|                                                                                  |
|   +--------------------------- DEMAND PATH ---------------------------+          |
|   | [DemandSideInletNodeA]                                           |          |
|   |          |                                                       |          |
|   |          v                                                       |          |
|   |     Node (DemandInlet)                                           |          |
|   |          |                                                       |          |
|   |          v                                                       |          |
|   | AirLoopHVACZoneSplitter                                          |          |
|   |          | (branch 1)                                             |          |
|   |          v                                                       |          |
|   |     Node (Branch1Inlet)                                          |          |
|   |          |                                                       |          |
|   |          v                                                       |          |
|   | AirTerminal:SingleDuct:VAV:NoReheat                              |          |
|   |          |                                                       |          |
|   |          v                                                       |          |
|   |     Node (Branch1Outlet)                                         |          |
|   |          |                                                       |          |
|   |          v                                                       |          |
|   | PortList (Zone Air Inlet)                                       |          |
|   |          |  (object reference, not OS:Connection)                |          |
|   |          v                                                      |          |
|   | ThermalZone (Office)                                            |          |
|   |          |                                                      |          |
|   |          v                                                      |          |
|   |     Node (ZoneReturn)                                           |          |
|   |          |                                                       |          |
|   |          v                                                       |          |
|   | AirLoopHVACZoneMixer                                             |          |
|   |          |                                                       |          |
|   |          v                                                       |          |
|   |     Node (DemandOutlet)                                          |          |
|   |          |                                                       |          |
|   |          v                                                       |          |
|   | [DemandSideOutletNodeName]                                       |          |
|   +------------------------------------------------------------------+          |
|                                                                                  |
|   PortList (Zone Equipment List)  <---->  AirTerminal                          |
|                                                                                  |
+----------------------------------------------------------------------------------+
```

Legend
- Items in brackets [ ... ] are OpenStudio field names on the AirLoopHVAC object.
- “Node (name)” and HVAC objects (fan/coils/splitter/mixer/terminal) are ModelObjects.
- Each vertical line segment represents an OS:Connection (OutletPort -> InletPort), except where explicitly labeled as an object reference (PortList ↔ ThermalZone).
- The ThermalZone is an `HVACComponent` connected via `PortList` objects (zone air inlet and equipment list). The zone air inlet `PortList` is inline in the branch; the equipment list is a side association. The zone exhaust `PortList` is used for ZoneHVAC connections, not the loop return path.

Relevant files:

- `src/model/AirLoopHVAC.hpp`
- `src/model/AirLoopHVAC.cpp`

### PlantLoop

`PlantLoop` builds a water-side topology with supply/demand splitters and mixers. Plant branches are added/removed by inserting nodes and connecting components between splitter/mixer pairs.

Relevant files:

- `src/model/PlantLoop.hpp`
- `src/model/PlantLoop.cpp`

## Traversal: How the Loop Graph Is Walked

`Loop` provides `supplyComponents`, `demandComponents`, and `components` to enumerate equipment. Traversal uses a **depth-first search** driven by `HVACComponent::edges`.

- `Loop_Impl::supplyComponents(...)` and `demandComponents(...)` start from inlet nodes and search to outlet nodes.
- Each `HVACComponent` (notably `Node`, `Splitter`, `Mixer`, etc.) provides `edges(...)` to return the next components in the flow path.
- Results are filtered by `IddObjectType` when requested.

### Graph traversal implementation (key code)

- `src/model/Loop.cpp`: DFS helpers (`findModelObject`, `findModelObjects`) walk the graph from a source toward a sink using `edges(...)`, tracking a visited list to avoid cycles and collecting unique path nodes.
- `src/model/HVACComponent.cpp`: default `HVACComponent_Impl::edges(...)` behavior.
- `src/model/Node.cpp`: `Node_Impl::edges(...)` returns the downstream connection for a simple in/out component.
- `src/model/Splitter.cpp`: `Splitter_Impl::edges(...)` returns all branch outlets (fan-out).
- `src/model/Mixer.cpp`: `Mixer_Impl::edges(...)` returns the single downstream outlet (fan-in completion).

Relevant files:

- `src/model/Loop.cpp`
- `src/model/HVACComponent.cpp`
- `src/model/Node.cpp`

## Example Translation Inventory (minimal_airloop.osm ↔ minimal_airloop.idf)

Reference files:

- `doc/idd-schema-alignment/minimal_airloop.osm`
- `doc/idd-schema-alignment/minimal_airloop.idf`

### Direct OS → E+ translations (object type pairs)

- `OS:AirLoopHVAC` → `AirLoopHVAC`
- `OS:AirLoopHVAC:ZoneMixer` → `AirLoopHVAC:ZoneMixer`
- `OS:AirLoopHVAC:ZoneSplitter` → `AirLoopHVAC:ZoneSplitter`
- `OS:AirTerminal:SingleDuct:ConstantVolume:NoReheat` → `AirTerminal:SingleDuct:ConstantVolume:NoReheat`
- `OS:Coil:Cooling:DX:SingleSpeed` → `Coil:Cooling:DX:SingleSpeed`
- `OS:Coil:Heating:Electric` → `Coil:Heating:Electric`
- `OS:Curve:Biquadratic` → `Curve:Biquadratic`
- `OS:Curve:Quadratic` → `Curve:Quadratic`
- `OS:Fan:ConstantVolume` → `Fan:ConstantVolume`
- `OS:Schedule:Constant` → `Schedule:Constant`
- `OS:ScheduleTypeLimits` → `ScheduleTypeLimits`
- `OS:ThermalZone` → `Zone`
- `OS:Version` → `Version`
- `OS:ZoneHVAC:EquipmentList` → `ZoneHVAC:EquipmentList`

### Translator-generated E+ objects (no OS object in the OSM)

These appear in the IDF but do not have a corresponding OS object in `minimal_airloop.osm`:

- `AirLoopHVAC:SupplyPath`
- `BranchList`
- `Branch`
- `NodeList`
- `OutdoorAir:Node`
- `ZoneHVAC:EquipmentConnections`
- `ZoneHVAC:AirDistributionUnit` (wrapper generated for the terminal)

### OS objects that do not translate to E+ (no direct E+ object)

These OS objects are present in the OSM but do not have direct E+ object counterparts (they are OpenStudio-only or internal topology constructs):

- `OS:Connection`, `OS:Node`, `OS:PortList` (internal topology objects)

## What would it take to underpin the OS API with EnergyPlus-native data structures?

This is a thought sketch (not a proposal) about what it might entail to replace `OpenStudio.idd`-driven topology with EnergyPlus-native constructs while preserving the OS API.

- **Nodes become virtual**: EnergyPlus uses node *names* in many objects but does not define a full `Node` object. The OS `Node` could become a virtual, non‑persisted model object (or a thin view over named node fields) rather than a concrete IDD object.
- **Connections map to E+ HVAC topology objects**: OS `Connection` would be replaced by explicit E+ constructs such as `Branch`, `BranchList`, `AirLoopHVAC:SupplyPath`, `AirLoopHVAC:ReturnPath`, and `Connector:*` objects for fan‑out/fan‑in. This would require reworking how `Model::connect` and port fields are stored.
- **PortList semantics**: Zone equipment/air inlet/exhaust lists could map more directly to `ZoneHVAC:EquipmentConnections`/`ZoneHVAC:EquipmentList` and `NodeList` objects, potentially eliminating OS‑specific `PortList` persistence.
- **API surface vs. persistence**: The OS API expects graph traversal (`edges(...)`, `supplyComponents`, `demandComponents`) across a generalized graph. An E+‑native backing store would likely need a translation layer or cached graph to preserve these traversal semantics.
- **Schema versioning**: EnergyPlus schema changes would directly impact the OS model layer, so version alignment and migration tooling would become more central.

## References (Code)

- `src/model/Loop.hpp`
- `src/model/Loop.cpp`
- `src/model/HVACComponent.hpp`
- `src/model/HVACComponent.cpp`
- `src/model/Connection.hpp`
- `src/model/Connection.cpp`
- `src/model/Model.cpp`
- `src/model/Node.cpp`
- `src/model/Splitter.cpp`
- `src/model/Mixer.cpp`
- `src/model/PortList.cpp`
