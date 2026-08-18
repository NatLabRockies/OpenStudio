# Modelica Workflow Quickstart

This guide walks you through running the bundled Modelica example (`compact_modelica.osw`) with the OpenStudio CLI. It is written for engineers who want to see a successful end‑to‑end simulation and understand the knobs that influence compiler selection.

## Prerequisites

1. **OpenModelica** – Install a recent OpenModelica distribution (https://openmodelica.org/download) so that the `omc` executable is available. You can override the discovery logic with environment variables (see below) if `omc` is not on `PATH`.
2. **OpenStudio CLI** – Install the official OpenStudio distribution from https://www.openstudio.net/downloads (or otherwise acquire the CLI) so that the `openstudio` executable is available. All commands below assume it is on your `PATH`; if not, substitute the absolute path to the binary you installed.
3. **Modelica Buildings Library (MBL) 12.1.0 + Spawn** – Download the 12.1.0 release archive from https://github.com/lbl-srg/modelica-buildings/releases (or clone the repository at that tag). If you cloned the repo, run the Spawn install script described in the official README (https://github.com/lbl-srg/modelica-buildings#spawn-of-energyplus-library) so that the `spawn-0.6.0-…` binary is installed under `Buildings/Resources/bin/`. Then add the folder containing `package.mo` (for example `Buildings/package.mo`) to your `MODELICAPATH` so the workflow can load the required package before compiling the seed model.

## Environment Variables You May Need

| Variable | When to use it |
| --- | --- |
| `OS_MODELICA_COMPILER=openmodelica` | Forces the workflow to pick OpenModelica explicitly. Any other value is ignored. |
| `OPENMODELICA_EXECUTABLE=/full/path/to/omc` | Points directly to `omc` when it is not on `PATH` or when you have multiple installs. |
| `MODELICAPATH=/path/to/packages:...` | Adds extra Modelica packages (for example a custom Modelica Buildings Library) to the compiler search path. The workflow also loads any packages declared in the OSW. |

Set the variables in the shell before running `openstudio`.

## Run the Example Workflow

1. Locate the installed `Examples` folder inside your OpenStudio installation (for user packages this is typically `<openstudio-install>/Examples/`). The Modelica workflow is `compact_osw/compact_modelica.osw`.
2. Run the installed OSW directly and use `--output-directory` to send its results to a writable location. The example assumes `openstudio` is on your `PATH`; otherwise use the full path to the installed CLI:

   ```bash
   openstudio run \
     --output-directory ~/openstudio-runs/compact-modelica \
     -w <openstudio-install>/Examples/compact_osw/compact_modelica.osw
   ```

   The output directory is resolved from the current working directory when it
   is relative. The workflow's Modelica seed, measures, and other inputs remain
   relative to the installed OSW. Relative `run_directory` and `out_name`
   settings are instead resolved beneath the selected output directory.
   Absolute settings are accepted only when they point inside that directory;
   any path that would escape it is rejected. The run directory must be a
   separate child and cannot be placed under `reports` or `generated_files`.

3. Watch the log output. The CLI prints which Modelica compiler it selected and the exact command line it is about to execute. If the run fails to find `omc`, double‑check the environment variables listed above.

4. Verify the results in `~/openstudio-runs/compact-modelica/run/`:
   - `run.log` – contains the compiler selection message and any warnings/errors, in addition to normal OS Workflow logs.
   - `OpenStudioExample.SeedBuilding_res.mat` – contains time series reults and confirms a successful Modelica simulation.
   - `stdout-modelica` – captures the raw Modelica compiler stdout stream; inspect this when you need the exact console output that was generated during the run.
   - `OpenStudioExample.SeedBuilding.log` – useful when troubleshooting Modelica solver issues.

OpenStudio replaces the `run/` directory at the start of a normal workflow run.

## Customizing the Workflow

`compact_modelica.osw` exposes a few Modelica-specific fields at the top level:

| Key | Description |
| --- | --- |
| `seed_modelica_file` | Path (relative to the OSW) of the Modelica template that will be copied into the run directory before measures edit it. |
| `seed_modelica_model` | Fully qualified class name passed to the compiler (required whenever `seed_modelica_file` is set). |
| `modelica_packages` | Array of package directories or `package.mo` files that should be added to the compiler search path before loading the seed model. |

When those keys are present, the workflow automatically populates the standard *Modelica parameters* that reference EnergyPlus artifacts—no manual overrides required. In the bundled seed model (`OpenStudioExample.SeedBuilding`) these appear as:

```modelica
parameter String idfPath = "...";
parameter String epwPath = "...";
parameter String weaPath = "...";
```

At runtime OpenStudio sets them on whatever `seed_modelica_model` you select so they always map to the files produced in `run/`:

- `idfPath` points to the translated `run/in.idf`.
- `epwPath` uses the weather file resolved by the OSW (falling back to the model’s weather if needed).
- `weaPath` is regenerated from that EPW each run (`run/in.mos`) so Spawn sees a matching MOS file.

Adjust these keys to point at your own Modelica model or package layout, rerun the CLI, and inspect the `run/` directory to confirm that a `.mat` result file is produced.

## Editing Modelica with Measures

The workflow also includes `SetModelicaZones`, a sample `ModelicaMeasure` (`resources/Examples/compact_osw/measures/SetModelicaZones/measure.rb`) that demonstrates the Modelica editing API. The measure receives an `OpenStudio::Modelica::ModelicaFile`, calls `getClassDefinitions` to obtain the parsed AST, and uses `addComponentClause` to append new `OpenStudioExample.TemplatesZoneHVAC.SingleZoneRTU` instances (one per non-plenum thermal zone). Because the API works on structured objects rather than raw text, you can programmatically redeclare templates or tweak parameters without hand-editing `.mo` files. Expect this API—as well as the bundled examples and supporting library content—to expand in future releases; in the meantime this measure is a good reference when crafting your own Modelica modifiers.
