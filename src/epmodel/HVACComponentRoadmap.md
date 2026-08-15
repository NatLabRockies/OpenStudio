# HVAC component work in EPModel

This page explains how to choose horizontal HVAC wrapper work now that the air
and plant topology campaigns have reached their stopping points. It is
deliberately not a class inventory. The public header's `Schema Alignment
Notes`, its implementation and tests, and any executable workflow are the
current status for a particular class.

The representative 80-percent boundary is met. Future phases must be driven by
a concrete workflow or a shared correctness defect, not by wrapper inventory.

## Selection rule

Choose a component phase when it does at least one of the following:

- unblocks a real model-building script, measure, or OSW;
- completes one useful relationship pattern across sibling classes;
- adds save/load and post-load mutation to an otherwise mature family;
- fixes ownership or rejected-operation behavior that can corrupt a model; or
- supplies a representative Ruby or Python and EnergyPlus path.

Do not choose work merely because an EnergyPlus object has another scalar
field or a generated wrapper exists. Prefer a complete, representative family
slice over scattered methods on unrelated classes.

## Evidence expected from a phase

A normal phase should include the applicable layers below:

1. Model-shaped public C++ APIs with typed EnergyPlus-backed relationships.
2. In-memory assignment, reset, invalid-target preservation, and ownership
   tests.
3. Connection rejection or transaction tests when more than one object is
   mutated.
4. Save/load followed by another public change.
5. Ruby or Python use in OpenStudio-resources when the phase serves a real
   workflow.
6. EnergyPlus execution when the workflow is intended to simulate.

Not every scalar family needs topology tests, and not every relationship needs
a new workflow. The header notes must say which evidence was actually added.

## Ordered horizontal priorities

1. **Workflow-blocking relationships.** Add missing schedules, curves,
   design objects, zones, and companion links in coherent sibling families.
2. **Mature topology without reload evidence.** Close save/load and post-load
   mutation gaps before adding more connection shapes.
3. **Contained equipment used by common systems.** Complete parent-owned fan,
   coil, node, and removal behavior for one real packaged or zone system at a
   time.
4. **Language and simulation breadth.** Turn established C++ paths into
   compact Ruby/Python workflows and numerical checks where results matter.

OpenStudio-resources owns the broad workflow corpus. This repository owns the
production behavior, focused tests, and only deliberately selected examples.

## The 80-percent boundary

The horizontal campaign is broadly useful when representative air terminals,
fans, heating and cooling coils, packaged zone equipment, air-to-air
equipment, plant equipment, and controls can be constructed, linked, saved,
reloaded, changed again, and exercised from at least one scripting workflow.
Sibling classes may still have documented scalar or convenience gaps.

The remaining 20 percent includes blanket clone and cross-model transfer,
SQL-backed autosized results for every family, unusual malformed imports,
AirflowNetwork depth, every optional performance curve, rare equipment
combinations, and exhaustive numerical parity. Address those only for a
specific use case or a shared architectural defect.

See [AirSystemTopology.md](AirSystemTopology.md) and
[PlantSystemTopology.md](PlantSystemTopology.md) for the connection contracts
that component work builds on.
