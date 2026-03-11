# Epmodel Scaffold Contract

contract_version: 0.1.6

## Purpose

This contract defines the normative scaffold-generation behavior for the temporary
`openstudio::epmodel` saturation effort. It is designed for serial, one-type-at-a-time runs.

## Sources and precedence

- Derived from existing generator conventions in:
  - `developer/ruby/SubProjectClassGenerators/ModelClassGenerator.rb`
  - `developer/ruby/MakeModelObjects.rb`
- If this contract and generator behavior differ, this contract governs for this effort.

## Required preflight for each run

1. Read this contract.
2. Read `doc/idd-schema-alignment/scaffold/inventory.yml`.
3. Read `doc/idd-schema-alignment/scaffold/overrides.yml`.
4. Read generator references listed above.
5. Read relevant existing `src/epmodel` base-family examples.

## API stability rules

1. Preserve existing API/class names for types with `openstudio::model` counterparts.
2. Preserve existing accessor method names/signatures even when IDD field names drift.
3. Map preserved APIs to current EnergyPlus/IDD fields internally.
4. For types without model counterparts, use IDD-derived names.
5. If safe mapping is not possible or an API break appears required, stop and mark blocked.

For types that already exist in `src/epmodel`:

6. Do not block solely because the class already has non-scalar functionality.
7. Migrate existing scaffold files into `output_dir` while preserving public API and behavior.
8. Add missing scalar accessors incrementally on top of existing implementation.
9. Treat include/CMake/test path updates required by file moves as normal scaffold work, not API breaks.

## Naming and mapping priority

1. Existing `src/model` class and API names.
2. ForwardTranslator evidence.
3. IDD-derived naming only when no model counterpart exists.

## Field accessor scope

Generate accessors only for simple scalar fields.

Exclude relationship-like fields, including:

- `\\object-list` target fields
- `\\reference` provider fields
- `\\type node`
- known target-link fields from `overrides.yml`

## Ruby parity rules (must replicate)

Mirror `developer/ruby/SubProjectClassGenerators/ModelClassGenerator.rb` behavior for generated field APIs:

1. Optionality logic:
  - Apply `optionalGetter?`-style rules from required/default/autosize/autocalculate metadata.
  - Do not infer optionality from type alone.

2. Choice/enum handling:
  - Non-boolean choice fields are `std::string` accessors with generated `...Values()` helpers.
  - Boolean choice fields map to `bool` with yes/no or true/false conversion semantics.

3. Setter failure semantics:
  - Follow `setCanFail?` conventions.
  - For non-failable setters, still return `bool` and assert success.

4. Default/autosize/autocalculate API surface:
  - Generate and wire `is...Defaulted`, `is...Autosized`, `autosize...`, `is...Autocalculated`, `autocalculate...` where applicable.

5. Reset behavior:
  - Generate reset methods only when allowed by field metadata (`hasReset?` style).

6. Required getter strictness:
  - Required/non-optional getters must enforce presence (assert/throw behavior) consistently with Ruby pattern.

7. Naming transforms:
  - Use Ruby generator naming transforms for getter/setter names and argument names.
  - Do not invent ad hoc naming.

## File pattern

Generate/update exactly three files per type:

- `<Type>.hpp`
- `<Type>.cpp`
- `<Type>_Impl.hpp`

Place these files under the type's configured `output_dir` inventory field (directory hierarchy),
not directly in `src/epmodel` root.

When introducing/using an epmodel subdirectory for a type, move that type's base-class files
into the same `output_dir` in the same run (if those base files currently exist at
`src/epmodel/<BaseClass>.*`).

Method placement must mirror Ruby generator conventions:

- Public method declarations in `<Type>.hpp`
- Implementation method declarations in `<Type>_Impl.hpp`
- Public/Impl method definitions in `<Type>.cpp`
- Do not inline non-template scalar accessor bodies in `<Type>.hpp`

## Folder bucket placement

1. Candidate bucket is immediate parent class.
2. If bucket count is below threshold (`3`), climb ancestor chain.
3. Select first ancestor bucket with count `>= 3`.
4. Final fallback bucket: `ModelObject`.

## Comment conventions

When API/field mappings differ from schema names, add concise comments in headers using:

```cpp
// Schema Alignment Notes:
// - API: <method or behavior> currently delegates to <object/field> in E+ schema.
// - Field Mapping: <OS concept> maps to <EnergyPlus object/field(s)>.
// - TODO(parity): Replace/adjust when <target parity milestone>.
```

## Done criteria for a type

A type may be marked `done` only when all are true:

1. Required scaffold files updated.
  - For pre-existing types, files are migrated to configured `output_dir`.
2. Mapping notes/comments added where needed.
3. Targeted build/tests pass.
  - Use parallel build/test execution with `-j32` where command supports it.
4. Minimum per-type tests include compile and scalar accessor roundtrip.

## Run result contract

Each agent run must emit a machine-readable result block with:

- `contract_version`
- `status` (`done`, `blocked`, `retry`)
- `summary`
- `files_changed`
- `mapping_decisions`
- `excluded_fields`
- `tests`
- `blocker_reason` (required if `status=blocked`)

A CLI must reject results with mismatched `contract_version`.

## Lifecycle

This toolchain is temporary. After scaffold saturation, queue automation is expected to be
frozen/deprecated and work transitions to normal human+agent custom parity development.
