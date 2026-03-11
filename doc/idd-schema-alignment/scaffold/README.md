# Epmodel Scaffold Queue

Temporary queue artifacts for one-type-at-a-time epmodel scaffold saturation.

## Files

- `../epmodel-scaffold-contract.md`: normative scaffold contract.
- `inventory.yml`: ordered type queue and status records.
  - Supports per-type `output_dir` for enforced directory hierarchy placement.
- `overrides.yml`: per-type mapping/exclusion overrides.
- `runs.log.yml`: append-only run history.

## CLI

Use:

```bash
python3 doc/idd-schema-alignment/scripts/epmodel_scaffold_cli.py status
python3 doc/idd-schema-alignment/scripts/epmodel_scaffold_cli.py seed
python3 doc/idd-schema-alignment/scripts/epmodel_scaffold_cli.py next
python3 doc/idd-schema-alignment/scripts/epmodel_scaffold_cli.py run --max-items 5
```

Defaults:

- `--max-retries 3`
- `--max-minutes-per-type 30`
- `run --max-items 0` (default unlimited; set a number to cap one session)

The CLI invokes `codex exec` with a fixed prompt contract and validates
`contract_version` before accepting results.

Scaffold runs instruct the coding agent to use `-j32` for build/test commands when supported.
`run` auto-seeds from `idd_mapping_appendix.generated.md` if no pending items remain.
For existing epmodel types, runs are expected to migrate files into configured `output_dir` and extend existing implementations.
The driver validates that generated headers do not contain inline non-template scalar method bodies.
The driver also requires explicit Ruby parity checks in each result (optionality, choice handling,
setter semantics, default/autosize/autocalculate/reset, required getter strictness, naming).
When using a subdirectory output target, the driver also enforces migration of existing base-class
files from `src/epmodel/` root into the same subdirectory.
