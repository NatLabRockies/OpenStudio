# epmodel Agent Notes

These notes are specific to work under `src/epmodel/`.

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
