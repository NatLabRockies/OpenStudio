# epmodel Agent Notes

These notes are specific to work under `src/epmodel/`.

## Reference Docs

When working on epmodel HVAC topology and API parity, read these two docs
first:

- `doc/idd-schema-alignment/README.md`
- `doc/idd-schema-alignment/os_hvac_concepts.md`

These are the primary narrative references for epmodel goals,
canonicalization expectations, and the intended `openstudio::model` HVAC
topology patterns that epmodel should mirror.

Also keep `doc/idd-schema-alignment/InputOutputReference.pdf` in mind as a
field-by-field EnergyPlus reference. When implementing or reviewing epmodel
wrappers for specific E+ object types, use it to confirm what each field means
and which fields are true object relationships versus plain scalar data.

For epmodel schema questions, treat the EnergyPlus IDD under
`resources/energyplus/` as the authoritative source of truth for object types,
field order,
extensibles, and object-list relationships. Use the Input Output Reference to
understand field semantics and intent, but do not let it override the
EnergyPlus IDD when there is any ambiguity about schema shape.

## Working Style Preferences

Apply these preferences unless the user asks otherwise.

- Preserve public `openstudio::model` API shape for parity work. Avoid adding
  new public APIs unless divergence is intentional and explicitly discussed.
- Prefer the `AirLoopHVAC` style of implementation: keep topology traversal,
  lookup, and canonicalization logic local and readable in the main method body.
- Avoid anonymous namespace helper functions, anonymous lambdas used as
  mini-methods, and tiny private helper methods that only hide straightforward
  logic. Prefer to inline this code except in rare cases where the helper
  clearly improves the implementation. If an anonymous helper really is
  warranted, document it thoroughly in normal human prose: why it exists, what
  it is doing, and why inlining would be worse.
- Reduce layers and duplicate naming. Do not introduce separate impl-only names
  for the same conceptual object when the public name already works.
- Prefer direct assertions over defensive fallback branches when canonical state
  guarantees the object relationship exists. Example: `getImpl(...)` should be
  `OS_ASSERT`ed rather than treated as optional when wrapper/impl pairing makes
  success mandatory.
- Do not add routine `OS_ASSERT` checks immediately after retrieving an
  object's own impl with `getImpl<...>()` in ordinary wrapper/impl code. Follow
  the usual `openstudio::model` style and call through directly. Reserve
  assertions for genuine narrowing assumptions, such as when a base wrapper is
  expected to carry a more specific impl type.
- Rely on polymorphism instead of explicit type-special-casing when the base
  impl interface already supports virtual dispatch.
- When choosing between generic abstraction and explicit code, prefer explicit
  code unless there is clear repeated structure worth standardizing across loop
  implementations.
- Avoid reaching into raw extensible-group mechanics from unrelated code. If a
  caller needs to add, remove, or clear structured extensible rows, add a
  private impl-level API on the owning type and keep the storage manipulation
  there.
- Add comments where the code relies on topology assumptions, canonicalization
  contracts, or other non-obvious invariants. Write these comments in normal
  developer prose that explains the reasoning to a human reader, not in terse
  shorthand or agent-style fragments.
- Spend effort on canonicalization and then trust it. Normal API and
  implementation code should assume canonical state and use assertions to
  verify invariants rather than performing conditional fallback logic or
  on-the-fly repair.
- In canonicalizers, raw field-level APIs such as `getString`,
  `setPointer`, `getModelObjectTarget`, and extensible-group mutation are
  acceptable on the owning type itself. This is the layer that is closest to
  the EnergyPlus-backed schema and is allowed to normalize it directly.
- Do not reach into another object's raw fields from unrelated code, even from
  another canonicalizer, unless the aggregate object truly owns that persisted
  structure and there is no cleaner owner-local repair point. Prefer to move
  field-level repair behind the owning type or let that type canonicalize
  itself.
- Prefer owner-local canonicalization when the repair decision depends only on
  the object's own fields. Prefer aggregate canonicalization when the invariant
  spans multiple objects or requires parent context such as membership,
  ordering, topology placement, or generated default names.
- Private impl-only `ensure*` helpers are allowed when they encode a concrete
  canonicalization invariant on the owning type. They should stay typed,
  should not expose raw schema details like field strings to callers, and
  should not become general runtime mutation APIs.
- For relationship fields, prefer `setPointer(...)` directly. Do not pair
  `setString(name)` with `setPointer(handle)` on the same field unless there is
  a very specific documented reason, because pointer fields already derive
  their displayed value from the target relationship.
- Prefer object-level identity comparisons over raw handle comparisons when the
  wrappers already express the same relationship clearly. Drop down to handles
  only when the wrapper comparison is not available or would obscure what is
  being compared.
- When describing topology support, distinguish between read-only
  query/navigation support and full loop-interface support. A secondary or
  tertiary interface is not "implemented" unless add/remove/manipulation
  semantics exist too.
- In epmodel tests, prefer public epmodel wrapper APIs and typed `Model`
  queries. Avoid generic `Workspace`/`IdfObject` relationship helpers such as
  `getModelObjectTarget`, `getTarget`, or similar field-level APIs unless the
  test is explicitly about that lower layer.
- In epmodel tests, do not use `ModelObject::create(...)` as a shortcut when a
  concrete wrapper type exists. Construct the actual epmodel wrapper the test
  means to exercise.

## Canonicalization Policy

These rules apply to epmodel canonicalizers in general, not only HVAC types.

- Canonicalizers must always converge the model to a valid epmodel state.
- Prefer repair over rejection when the intended structure can be recovered
  reasonably from the persisted EnergyPlus-backed schema.
- If content is not salvageable without inventing unsupported semantics, drop
  the minimum invalid content necessary to restore validity.
- Do not leave partially repaired or internally contradictory topology behind.
  Canonicalization should finish in a state that normal API code can trust.
- Outside canonicalizers, do not add fallback repair logic for malformed
  state. Runtime code should assume canonicalized invariants and use
  assertions for impossible conditions.
- Canonicalizers must log all meaningful repairs, drops, normalizations, and
  failed repair attempts through `addLoadInfo`, `addLoadWarning`, and
  `addLoadError`.
- Use `addLoadInfo` for benign normalization and default creation,
  `addLoadWarning` for recoverable invalid input that required repair or
  content removal, and `addLoadError` for unrecoverable conditions or failed
  repair attempts.
- When dropping content, prefer preserving the owning object and the maximum
  amount of unambiguous structure around it.
- Keep canonicalization logic close to the owning type so
  relationship-specific repair decisions remain local, explicit, and
  reviewable.
