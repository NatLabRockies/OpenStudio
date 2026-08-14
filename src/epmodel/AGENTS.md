# EPModel development rules

These rules apply to work under `src/epmodel/`.

## Start here

When working on epmodel parity or topology behavior, read these first:

- `src/epmodel/README.md`
- `src/epmodel/AirSystemTopology.md` for air-system topology work

Use these references when needed:

- `resources/energyplus/` for EnergyPlus schema shape, field
  order, extensibles, and object-list relationships
- the Input Output Reference distributed with the configured EnergyPlus
  version for field semantics

## Implementation

- Preserve public `openstudio::model` API shape for parity work. Do not add
  new public APIs unless divergence is intentional and explicitly documented.
- For EnergyPlus-only connective-tissue types with no canonical
  `openstudio::model` counterpart, keep public wrapper APIs minimal and keep
  mutators in `*_Impl`.
- For EnergyPlus-only types that exist as real persisted E+ objects but still
  have no canonical same-name `openstudio::model` wrapper, prefer read-only
  public wrappers for now. Let owning parent types and impl code perform
  mutation through `*_Impl` instead of growing standalone public mutator
  surfaces prematurely.
- Prefer the `AirLoopHVAC` style of implementation: keep topology traversal,
  lookup, and canonicalization logic local and readable in the main method
  body.
- Avoid anonymous namespace helper functions, anonymous lambdas used as
  mini-methods, and tiny private helper methods that only hide straightforward
  logic. Inline the code unless a helper clearly improves readability.
- Reduce layers and duplicate naming. Do not introduce separate impl-only
  names for the same conceptual object when the public name already works.
- Keep public wrapper classes thin. For classes that follow the Model API, put
  substantive behavior, relationship mutation, and helper logic in `*_Impl`.
- In public wrapper headers, group accessors by field or concept. Prefer
  getter / setter / reset blocks for one field at a time over separate
  "all getters" and "all setters" sections.
- If adding a new aligned parent type, add the corresponding `*_Impl` layer
  too. Do not concentrate new behavior in the public base class.
- Prefer high-level typed APIs over raw workspace field access when both
  express the same behavior clearly.
- Prefer composition of existing typed APIs over direct field-level methods.
  Use low-level field access only when no equivalent typed composition exists.
- Prefer pointer/object-target linkage APIs over direct name-string writes for
  object relationships. Reserve `setString(...)` for true scalar data.
- For extensible object-list rows, cast to `WorkspaceExtensibleGroup` and use
  `getTarget(...)` / `setPointer(...)` instead of hand-rolled type-and-name
  lookup. If that path does not work, first suspect missing or incorrect
  object-list/reference markup in the IDD schema rather than falling back to
  name lookup silently.
- For `NodeType` fields, use the shared `ModelObject_Impl` node resolver
  helpers instead of local "read the string and look up the node by name"
  logic. If a getter returns a `Node`, it should be a live linked node, not
  an untracked transient object.
- Do not reach into raw extensible-group mechanics from unrelated code. If a
  caller needs structured extensible mutation, add a private impl-level API on
  the owning type and keep storage manipulation there.
- Add short comments where code depends on topology assumptions, repair rules,
  or API invariants.
- Prefer object-level identity comparisons over raw handle comparisons when
  the wrappers already express the relationship clearly.
- In epmodel tests, prefer public wrapper APIs and typed `Model` queries.
  Avoid low-level `Workspace`/`IdfObject` helpers unless the test is
  explicitly about that layer.
- In epmodel tests, construct the concrete wrapper under test rather than
  using `ModelObject::create(...)` as a shortcut.

## Topology mutation plans

- Use a `*Plan` for a multi-object topology change with a distinct prepare and
  commit boundary. Plans are one-shot and non-copyable, and they track an
  explicit prepared/committed state.
- A read-only preflight plan proves every owner, endpoint, and removal before
  mutation. Its `commit()` performs only the already-proven invariant writes
  and does not return a recoverable failure.
- A provisional-mutation plan may create or rewire state while preparing. Its
  destructor restores the exact original representation and removes only
  objects that the plan created. This includes both managed object targets and
  unresolved raw backing text when either representation is possible.
- Enroll an attempted mutation in the plan before calling a setter. A setter
  may partially write and still report failure.
- Finish all fallible preparation, including preparation of nested plans,
  before any plan crosses its commit boundary. Commit nested plans in an
  explicit dependency order, then make the outer `commit()` a state-only or
  otherwise no-fail operation.
- Reserve `Guard` for scoped temporary restoration and `Snapshot` for captured
  state that has no prepare/commit lifecycle. Do not call either one a plan
  merely because it participates in rollback.

## Canonicalization

- Canonicalization repairs imported models. It should run during construction
  and loading, not as an ad hoc runtime fallback.
- Canonicalizers must converge the model to a valid epmodel state.
- Prefer repair over rejection when the intended structure can be recovered
  reasonably from persisted EnergyPlus-backed storage.
- If content is not salvageable without inventing unsupported semantics, drop
  the minimum invalid content necessary to restore validity.
- Do not leave partially repaired or internally contradictory topology behind.
- Outside canonicalizers, normal API methods should not invoke
  canonicalization. They should assume canonical state and rely on established
  invariants.
- When one type must be repaired before another, put that ordering in a common
  owner such as the Model canonicalizer. Do not add runtime fallback paths.
- After canonicalization, prefer assertions and direct logic over fallback
  branches for guaranteed states.
- Canonicalizers must log repairs, removals, normalization, and failed repair
  attempts through `addLoadInfo`, `addLoadWarning`, and
  `addLoadError`.
- Keep canonicalization logic close to the owning type so repair decisions
  remain local, explicit, and reviewable.
- For compound HVAC owners, implement separate impl-level methods for normal
  owner maintenance and canonicalization repair, such as
  `maintainContainedAirPath()` and `repairContainedAirPath(LoadContext&)`, or
  `maintainContainedTopology()` and `repairContainedTopology(LoadContext&)`
  when the owned structure is broader than air alone. Do not collapse those
  two call paths back into one public-facing routine.
- Keep contained-child routing rules owner-local. If a compound family needs
  to switch on supported child types to find air inlet or outlet ports, do it
  in that family's `.cpp` with a plain comment that says what is allowed.
  Do not keep growing shared base helpers that try to enumerate every child
  shape used by every compound HVAC family.
- Do not hand-roll node-field resolution in local files. If code needs the
  `Node` behind a node field, use the shared `ModelObject_Impl`
  node-field helpers so resolved nodes are linked back to the owning field and
  later renames stay tracked.
- When canonical `openstudio::model` exposes OS-only companion objects that do
  not exist as standalone EnergyPlus objects, epmodel may represent them as
  transient child wrappers backed by persisted parent storage. Keep that
  write-through mapping explicit, document it in the type notes, and avoid
  inventing fake persisted children.

## Schema Alignment Notes

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

## Review

Have separate agents review nontrivial code changes. At minimum, check:

- these rules and `epmodel/README.md`;
- whether the README needs to change with the code; and
- similar EPModel classes and tests.
