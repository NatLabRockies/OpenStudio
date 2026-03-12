# OpenStudio Agent Notes

## Manifest Campaign Shortcut

When the user says:

- `Use manifest <path> and describe.`
- `Use manifest <path> and run it end to end.`
- `Use manifest <path> and resume.`

do not just summarize the manifest contents.

Instead:

1. Treat it as an instruction to execute the epmodel campaign backend.
2. Run:
   - `python3 doc/idd-schema-alignment/scripts/epmodel_campaign_cli.py use --manifest "<path>" --action "describe"`
   - `python3 doc/idd-schema-alignment/scripts/epmodel_campaign_cli.py use --manifest "<path>" --action "run it end to end"`
   - `python3 doc/idd-schema-alignment/scripts/epmodel_campaign_cli.py use --manifest "<path>" --action "resume"`
3. Summarize the backend result for the user.
4. For `describe`, report the persisted resolution paths.
5. For `run it end to end` and `resume`, report the run state paths and outcome.

If the backend fails, report the actual failure and the next corrective step.
