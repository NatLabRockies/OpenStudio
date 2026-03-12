# File Map

## Workflow docs

- `doc/idd-schema-alignment/campaigns/README.md`
  - Quick orientation.
- `doc/idd-schema-alignment/campaigns/workflow-contract.md`
  - Minimal manifest contract and local state model.
- `doc/idd-schema-alignment/campaigns/operator-manual.md`
  - Chat-first operating instructions.
- `doc/idd-schema-alignment/campaigns/file-map.md`
  - This map.

## Manifests

- `doc/idd-schema-alignment/campaigns/manifests/`
  - Repo-committed campaign manifests.

## Examples

- `doc/idd-schema-alignment/campaigns/examples/method-grouping-fixture/MethodGroupingFixture.hpp`
- `doc/idd-schema-alignment/campaigns/examples/method-grouping-fixture/MethodGroupingFixture_Impl.hpp`
- `doc/idd-schema-alignment/campaigns/examples/method-grouping-fixture/MethodGroupingFixture.cpp`
  - Deliberately disordered fixture used to validate code-changing behavior.

## Backend tooling

- `doc/idd-schema-alignment/scripts/epmodel_campaign_cli.py`
  - Manifest-driven backend CLI with target resolution, checkpointing, and code-changing execution.

## Local state (ignored)

- `.opencode/epmodel-campaigns/`
  - Implicit runtime state root.
- `.opencode/epmodel-campaigns/<manifest-stem>/resolution.json`
  - Canonical reviewed resolution from `describe`.
- `.opencode/epmodel-campaigns/<manifest-stem>/subjects.json`
  - Persisted resolved subjects from `describe`.
- `.opencode/epmodel-campaigns/<manifest-stem>/work-items.json`
  - Persisted normalized work items from `describe`.
- `.opencode/epmodel-campaigns/<manifest-stem>/runs/<run_id>/run.json`
  - Run summary, execution policy, and phase status.
- `.opencode/epmodel-campaigns/<manifest-stem>/runs/<run_id>/subjects.json`
  - Resolved include/exclude subjects.
- `.opencode/epmodel-campaigns/<manifest-stem>/runs/<run_id>/work-items.json`
  - Normalized execution units, per-item progress, and per-item validation metadata.
- `.opencode/epmodel-campaigns/<manifest-stem>/runs/<run_id>/events.jsonl`
  - Append-only run log.
