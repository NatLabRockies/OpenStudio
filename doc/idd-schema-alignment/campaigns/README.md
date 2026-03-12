# epmodel Campaign Workflow

This directory defines the current OpenCode-first workflow for systematic
`src/epmodel` campaigns.

Operator pattern:

`Use manifest <path> and <action>`

Supported actions:

- `describe`
- `run it end to end`
- `resume`

The manifest stays small. It declares the code change, optional target filters,
and optional context. Target filters resolve to `subjects`, which are then
normalized into one `work_item_kind` for the run. The backend tool owns that
normalization and all local state.

`describe` is the point where fuzzy target input is resolved and persisted into
canonical subjects and work items for audit and progress tracking. When needed,
that resolution can be OpenCode-assisted.

Execution policy can also be declared in the manifest:

- what each work item should do
- what should happen after all work items are complete

Start here:

- `workflow-contract.md`
- `operator-manual.md`
- `file-map.md`
