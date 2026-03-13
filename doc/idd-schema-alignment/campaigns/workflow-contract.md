# epmodel Campaign Workflow Contract

workflow: `epmodel_campaign`

## Purpose

Define a minimal manifest contract for resumable epmodel campaigns. The manifest
describes what to change, how to filter targets, and what background material to
keep nearby. The backend tool owns execution details and local state.

## Operator interaction

Primary interaction pattern:

`Use manifest <path> and <action>`

Supported actions:

- `describe`
- `run`
- `resume`
- `status`

`describe` is the canonical resolution step. It resolves fuzzy target text into
concrete subjects and work items, then persists that reviewed resolution under
the campaign state root.

When selectors are not covered by simple path/class/generic rules, `describe`
uses the configured OpenCode runner to resolve fuzzy selector text against the
live epmodel candidate catalog.

## Manifest contract

Required keys:

- `workflow`: must equal `epmodel_campaign`
- `change`: freeform change intent

Optional keys:

- `targets.include`: target selectors
- `targets.exclude`: target selectors to subtract from the include set
- `execution.each_work_item`: freeform instructions for what each work item should do and validate
- `execution.after_all_work_items`: freeform instructions for final build/test and optional final repair pass
- `execution.backend`: `cli` by default or `server` for an opt-in shared OpenCode server backend
- `execution.resolution_agent`: optional `model` and `variant` overrides for selector resolution
- `execution.subject_agent`: optional `model`, `variant`, and `parallelism` overrides for per-subject execution
- `execution.after_all_agent`: optional `model` and `variant` overrides for the final phase
- `context.read`: repo paths to load eagerly before planning/execution
- `context.references`: repo paths to keep available but load only when needed
- `context.notes`: short operator guidance

Current selector styles:

- file paths or globs, for example `src/epmodel/StraightComponent/*.hpp`
- direct class names
- supported natural-language selectors, for example:
  - `all epmodel types`
  - `all concrete epmodel types`
  - `all base classes that derive from HVACComponent`

The backend intentionally keeps selector interpretation small and generic.
Campaign-specific semantic targeting is resolved with OpenCode/LLM assistance,
then persisted as canonical subjects and work items for audit.

Selectors resolve to `subjects`, not necessarily types. Current subject kinds are:

- `type`
- `file`
- `method`

Future campaigns may introduce other kinds.

## Subjects and work items

The workflow has two stages after selector interpretation:

1. resolve selectors into `subjects`
2. normalize subjects into `work_items`

Rules:

- a subject is a resolved repo entity such as a type or file
- a work item is the execution unit for the requested change
- each run must normalize to exactly one `work_item_kind`
- if the resolved subjects cannot be normalized cleanly to one work-item kind,
  the run fails hard during planning

Current built-in accessor-grouping campaigns resolve and execute as file subjects.

## Execution policy

The run has two execution layers:

1. `execution.each_work_item`
2. `execution.after_all_work_items`

Interpretation:

- each work item gets the same shared campaign context snapshot
- each work item runs in its own agent session at the OpenCode layer
- `each_work_item` controls whether item-local validation is expected
- `after_all_work_items` controls final build/test behavior after all work items are done
- if the final phase requests repair, that repair happens as a separate final pass, not by reopening original work-item sessions

Current backend behavior:

- item-local execution is recorded per work item
- when `after_all_work_items` is empty, the run can complete normally
- when `after_all_work_items` is present, the backend executes it as a final agent phase
- manifest agent config overrides backend defaults for model speed/quality tradeoffs
- subject parallelism is bounded and conflict-aware using editable-path locking

## Source of truth

Target discovery is code-first:

- `src/epmodel/**/*.hpp`
- `src/epmodel/**/*.cpp`
- `src/epmodel/**/*_Impl.hpp`

The workflow uses live `src/epmodel` code and reviewed campaign context as its source of truth.

## State and progress

Local state root:

- `.opencode/epmodel-campaigns/<manifest-stem>/`

Campaign-level artifacts:

- `resolution.json`: canonical reviewed resolution metadata for the current manifest hash
- `subjects.json`: persisted resolved subjects from `describe`
- `work-items.json`: normalized work-item ids and subject-to-work-item mapping from `describe`

The three files are intentionally distinct:

- `resolution.json` is the audit record and summary
- `subjects.json` is the full resolved subject set
- `work-items.json` stores normalization output only and avoids duplicating full subject payloads
- when normalization is identity, `work-items.json` points back to `subjects.json` instead of repeating the whole set

Run artifacts:

- `latest-run.json`: pointer to the latest run for this manifest stem
- `runs/<run_id>/run.json`: run state, manifest hash, plan, execution policy, subject summary, work-item summary
- `runs/<run_id>/subjects.json`: resolved include/exclude subjects
- `runs/<run_id>/work-items.json`: normalized work items with per-item status and changed files
- `runs/<run_id>/events.jsonl`: append-only event log
- `runs/<run_id>/control.json`: requested operator control state such as continue, pause, or cancel
- `runs/<run_id>/controller.log`: detached controller output
- `runs/<run_id>/server.log`: shared OpenCode server output when `execution.backend: server`

Run states:

- `planned`
- `resolved`
- `running`
- `paused`
- `completed`
- `failed`
- `cancelled`

Execution phase states recorded in `run.json`:

- `work_items`: `pending`, `running`, `completed`, `paused`, `failed`, `cancelled`
- `after_all_work_items`: `not_requested`, `pending`, `running`, `completed`, `failed`

Work-item states:

- `pending`
- `queued`
- `in_progress`
- `done`
- `skipped`
- `failed`

Resume behavior:

- `run` requires a current persisted resolution from `describe`
- if the manifest hash changes after `describe`, the persisted resolution becomes stale and `run` fails until `describe` is run again
- `resume` reuses the latest non-terminal run only when the manifest hash still matches
- otherwise a new run is created

Status and control behavior:

- `status --manifest <path>` reports the latest run snapshot
- `status --manifest <path> --watch` streams refreshed summaries until the run finishes
- `pause --manifest <path>` requests a clean pause once active work items drain
- `cancel --manifest <path>` requests a clean cancellation once active work items drain
- `run` and `resume` detach by default; use `--foreground` for debugging

## Current built-in change support

The backend currently implements one code-changing strategy:

- group related getter/setter/default/reset methods in declarations and definitions

Other target-resolution patterns may be recognized during `describe`, but they
are not runnable until a matching code-changing strategy exists.

Execution is modeled as one work item per agent session at the OpenCode layer.
The backend state is recorded per work item so fan-out and resume can stay clean.

## Backend CLI

CLI path:

- `doc/idd-schema-alignment/scripts/epmodel_campaign_cli.py`

Commands:

- `use --manifest <path> --action <text>`
- `status --manifest <path> [--run-id <id>] [--json] [--watch]`
- `pause --manifest <path> [--run-id <id>]`
- `cancel --manifest <path> [--run-id <id>]`
- `resume --manifest <path> [--foreground]`
- `validate-manifest --manifest <path>`
