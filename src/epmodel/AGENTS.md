# epmodel Agent Notes

These notes are specific to work under `src/epmodel/`.

## Read First

When working on epmodel parity or topology behavior, read these first:

- `src/epmodel/README.md`
- `.opencode/hvac-parity-docs/hvac-api-roadmap.md`
- `doc/idd-schema-alignment/os_hvac_concepts.md`

Also keep these references available when needed:

- `doc/idd-schema-alignment/InputOutputReference.pdf` for EnergyPlus field
  semantics
- `resources/energyplus/` for authoritative EnergyPlus schema shape, field
  order, extensibles, and object-list relationships

Status, queue order, and next-task planning belong in the roadmap file, not
in README documents.

## Working Style Preferences

Apply these preferences unless the user asks otherwise.

- Preserve public `openstudio::model` API shape for parity work. Do not add
  new public APIs unless divergence is intentional and explicitly documented.
- For EnergyPlus-only connective-tissue types with no canonical
  `openstudio::model` counterpart, keep public wrapper APIs minimal and keep
  mutators in `*_Impl`.
- Prefer the `AirLoopHVAC` style of implementation: keep topology traversal,
  lookup, and canonicalization logic local and readable in the main method
  body.
- Avoid anonymous namespace helper functions, anonymous lambdas used as
  mini-methods, and tiny private helper methods that only hide straightforward
  logic. Inline the code unless a helper clearly improves readability.
- Reduce layers and duplicate naming. Do not introduce separate impl-only
  names for the same conceptual object when the public name already works.
- Keep public wrapper classes thin. For parity-oriented types, put
  substantive behavior, relationship mutation, and helper logic in `*_Impl`.
- If adding a new aligned parent type, add the corresponding `*_Impl` layer
  too. Do not concentrate new behavior in the public base class.
- Prefer high-level typed APIs over raw workspace field access when both
  express the same behavior clearly.
- Prefer composition of existing typed APIs over direct field-level methods.
  Use low-level field access only when no equivalent typed composition exists.
- Prefer pointer/object-target linkage APIs over direct name-string writes for
  object relationships. Reserve `setString(...)` for true scalar data.
- Do not reach into raw extensible-group mechanics from unrelated code. If a
  caller needs structured extensible mutation, add a private impl-level API on
  the owning type and keep storage manipulation there.
- Add short intent comments where code depends on topology assumptions,
  canonicalization contracts, or parity-driven invariants.
- Prefer object-level identity comparisons over raw handle comparisons when
  the wrappers already express the relationship clearly.
- In epmodel tests, prefer public wrapper APIs and typed `Model` queries.
  Avoid low-level `Workspace`/`IdfObject` helpers unless the test is
  explicitly about that layer.
- In epmodel tests, construct the concrete wrapper under test rather than
  using `ModelObject::create(...)` as a shortcut.

## Canonicalization Policy

- Canonicalization is the central repair and assurance phase. It should run at
  model construction and load boundaries, not as an ad hoc runtime crutch.
- Canonicalizers must converge the model to a valid epmodel state.
- Prefer repair over rejection when the intended structure can be recovered
  reasonably from persisted EnergyPlus-backed storage.
- If content is not salvageable without inventing unsupported semantics, drop
  the minimum invalid content necessary to restore validity.
- Do not leave partially repaired or internally contradictory topology behind.
- Outside canonicalizers, normal API methods should not invoke
  canonicalization. They should assume canonical state and rely on established
  invariants.
- When cross-type ordering is not guaranteed, refactor canonicalization scope
  upward so ordering is guaranteed there instead of adding runtime fallback
  paths.
- After canonicalization, prefer assertions and direct logic over fallback
  branches for guaranteed states.
- Canonicalizers must log meaningful repairs, drops, normalizations, and
  failed repair attempts through `addLoadInfo`, `addLoadWarning`, and
  `addLoadError`.
- Keep canonicalization logic close to the owning type so repair decisions
  remain local, explicit, and reviewable.
- For compound HVAC owners, implement separate impl-level methods for normal
  owner maintenance and canonicalization repair, such as
  `maintainContainedAirPath()` and `repairContainedAirPath(LoadContext&)`.
  Do not collapse those two call paths back into one public-facing routine.

## Schema Alignment Notes Convention

Type-local parity status belongs in `Schema Alignment Notes` blocks in
`src/epmodel/**/*.hpp`.

Required bullets:

- `Status`
- `Canonical Counterpart`
- `Implemented Parity`

Optional bullets when useful:

- `Documented Delta`
- `Field/Storage Mapping`
- `Evidence`

`Remaining Parity Work` is required unless the type is truly at parity with
only documented deltas remaining.

Status vocabulary:

- `Scaffolded`
- `Scalar Parity`
- `Partial Parity`
- `Near Parity`
- `Parity with documented deltas`
