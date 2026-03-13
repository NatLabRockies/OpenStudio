# Operator Manual

This workflow is OpenCode-first. The manifest is the entrypoint. The backend CLI
handles target resolution, local state, and resumable execution.

## Normal operator pattern

Use one sentence:

`Use manifest <path> and <action>`

Examples:

- `Use manifest <path> and describe.`
- `Use manifest <path> and run.`
- `Use manifest <path> and resume.`
- `Use manifest <path> and status.`

Normal flow:

1. run `describe`
2. review the persisted resolution
3. run `run`

## What the manifest says

- `change`: the freeform code-change intent
- `targets`: optional include/exclude filters that resolve to subjects
- `execution.each_work_item`: what each work item should do and whether to validate it immediately
- `execution.after_all_work_items`: what should happen once all work items are complete
- `execution.backend`: `cli` by default, or opt in to `server` for a shared OpenCode server
- `execution.resolution_agent`: optional model/variant settings for fuzzy resolution work
- `execution.subject_agent`: optional model/variant/parallelism settings for per-subject work
- `execution.after_all_agent`: optional model/variant settings for final build/test/repair work
- `context.read`: eager background material
- `context.references`: lazy background material
- `context.notes`: short operator guidance

Target filters are plain language or path/glob strings. For example:

- `all base classes that derive from HVACComponent`
- `all concrete epmodel types`
- `all straight components that belong only on the supply side of AirLoopHVAC`

The backend keeps selector interpretation intentionally small and generic.
When a selector is fuzzy, `describe` uses the configured OpenCode runner to
resolve it against the live epmodel candidate catalog, then persists the result.

## Subjects and work items

- selectors resolve to `subjects`
- subjects may be types, files, or methods
- the tool then normalizes them into one `work_item_kind` for the run
- each work item is the unit of execution and progress tracking
- if the tool cannot normalize to one work-item kind, `describe` should fail hard

## Per-work-item vs final pass

- `execution.each_work_item` describes what happens inside each work item
- `execution.after_all_work_items` describes final build/test work after every work item is done
- `execution.subject_agent.parallelism` controls bounded subject fan-out for non-overlapping file sets
- manifest-defined model settings override backend defaults for speed/quality tradeoffs
- formatting/organization-heavy campaigns should generally prefer a mini subject model over Spark unless you explicitly want Spark
- if final repair is requested, it happens as a separate final pass
- the backend records this policy even when it cannot safely infer project-specific build/test commands on its own

## Long-running runs

- `run` and `resume` launch detached by default so the operator can keep interacting while work continues
- use `status --manifest <path>` for a snapshot and `status --manifest <path> --watch` for live progress
- use `pause --manifest <path>` or `cancel --manifest <path>` to control the latest run
- when `execution.backend: server` is enabled, status also reports the shared OpenCode server URL while the run is active

## Eager vs lazy context

- `context.read` is the material OpenCode should have in hand before planning
- `context.references` is extra material that should stay available but not be loaded unless needed

Example:

- put small, high-signal docs or code files in `read`
- put large PDFs such as engineering references in `references`

## What `describe` should tell you

- how the tool interpreted the change request
- how target filters were resolved
- subject kind counts and sample subjects
- the chosen work-item kind and sample work items
- the interpreted execution policy
- where local state will be recorded

`describe` also persists the canonical reviewed resolution. `run`
uses that persisted work-item set instead of re-resolving targets.

## Local state

The tool records progress automatically under:

- `.opencode/epmodel-campaigns/<manifest-stem>/`

Key files:

- `resolution.json`
- `subjects.json`
- `work-items.json`
- `latest-run.json`
- `runs/<run_id>/run.json`
- `runs/<run_id>/events.jsonl`

These are meant to stay lean and non-overlapping:

- `resolution.json` records the reviewed decision and counts
- `subjects.json` holds the actual resolved subject list
- `work-items.json` holds normalized execution ids and subject mapping
- for identity normalization, `work-items.json` stays minimal and references `subjects.json`

You do not need to specify state or report paths in the manifest.
