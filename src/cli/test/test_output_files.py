import json
import subprocess
from pathlib import Path

import pytest

from workflow_helpers import run_workflow


@pytest.fixture(scope="module")
def runWorkflow(osclipath):
    runDir, r = run_workflow(
        osclipath=osclipath,
        base_osw_name="in.osw",
        suffix="labs",
        verbose=False,
        debug=False,
        post_process_only=True,
    )
    r.check_returncode()
    return runDir


def test_(osclipath):
    runDir, r = run_workflow(
        osclipath=osclipath,
        base_osw_name="in.osw",
        suffix="labs_debug",
        verbose=False,
        debug=True,
        post_process_only=True,
    )
    r.check_returncode()
    out_osw_path = Path("out_in_labs_debug.osw")
    assert out_osw_path.is_file()
    out = json.loads(out_osw_path.read_text())

    assert out["completed_status"] == "Success"
    assert out["current_step"] == 1

    EXPECTED_TOPLEVEL_KEYS = {
        "completed_at",
        "completed_status",
        "current_step",
        "file_paths",
        "hash",
        "measure_paths",
        "out_name",
        "run_directory",
        "started_at",
        "steps",
        "updated_at",
    }
    EXPECTED_TOPLEVEL_KEYS.add("run_options")
    assert out.keys() == EXPECTED_TOPLEVEL_KEYS

    assert len(out["steps"]) == 1
    step = out["steps"][0]
    step.keys() == {"arguments", "measure_dir_name", "result"}
    assert step["arguments"] == {}
    assert step["measure_dir_name"] == "FakeReport"

    step_result = step["result"]
    assert step_result.keys() == {
        "completed_at",
        "measure_class_name",
        "measure_display_name",
        "measure_name",
        "measure_taxonomy",
        "measure_type",
        "measure_uid",
        "measure_version_id",
        "measure_version_modified",
        "measure_xml_checksum",
        "started_at",
        "stderr",
        "stdout",
        "step_errors",
        "step_files",
        "step_final_condition",
        "step_info",
        "step_result",
        "step_values",
        "step_warnings",
    }

    assert step_result["step_result"] == "Success"

    assert len(step_result["step_info"]) == 1
    assert len(step_result["step_warnings"]) == 1
    assert not step_result["step_errors"]

    len(step_result["step_values"]) == 3
    assert {x["name"] for x in step_result["step_values"]} == {
        "fake_report",
        "net_site_energy",
        "something_with_invalid_chars",
    }


@pytest.mark.parametrize("absolute_osw_paths", [False, True])
def test_output_directory_uses_contained_osw_output_paths(osclipath, tmp_path, absolute_osw_paths):
    source_osw_path = Path("in.osw").resolve()
    source_root = source_osw_path.parent

    input_directory = tmp_path / "input"
    input_directory.mkdir()
    input_osw_path = input_directory / "custom.osw"

    osw = json.loads(source_osw_path.read_text())
    osw["root"] = str(source_root)
    output_directory = tmp_path / "results"
    run_directory = output_directory / "simulation"
    output_osw_path = output_directory / "finished.osw"
    if absolute_osw_paths:
        osw["run_directory"] = str(run_directory)
        osw["out_name"] = str(output_osw_path)
    else:
        osw["run_directory"] = "simulation"
        osw["out_name"] = "finished.osw"
    input_osw_path.write_text(json.dumps(osw, indent=2))

    run_directory.mkdir(parents=True)
    (run_directory / "in.idf").write_text("Building,;")

    result = subprocess.run(
        [
            str(osclipath),
            "run",
            "--postprocess_only",
            "--output-directory",
            "results",
            "-w",
            str(input_osw_path),
        ],
        cwd=tmp_path,
        capture_output=True,
        encoding="utf-8",
    )
    result.check_returncode()

    assert output_osw_path.is_file()
    assert (run_directory / "run.log").is_file()
    assert (output_directory / "generated_files").is_dir()
    assert (output_directory / "reports").is_dir()
    assert not (input_directory / "simulation").exists()
    assert not (input_directory / "finished.osw").exists()

    input_osw = json.loads(input_osw_path.read_text())
    assert input_osw["run_directory"] == osw["run_directory"]
    assert input_osw["out_name"] == osw["out_name"]

    output_osw = json.loads(output_osw_path.read_text())
    assert Path(output_osw["root"]) == source_root
    assert Path(output_osw["run_directory"]) == run_directory


@pytest.mark.parametrize("setting_name", ["run_directory", "out_name"])
@pytest.mark.parametrize("path_kind", ["absolute", "parent"])
def test_output_directory_rejects_osw_paths_outside_it(osclipath, tmp_path, setting_name, path_kind):
    input_osw_path = tmp_path / "conflicting.osw"
    osw = {"steps": []}
    outside_name = "run" if setting_name == "run_directory" else "out.osw"
    if path_kind == "absolute":
        osw[setting_name] = str(tmp_path / "elsewhere" / outside_name)
    else:
        osw[setting_name] = f"../elsewhere/{outside_name}"
    input_osw_path.write_text(json.dumps(osw, indent=2))

    output_directory = tmp_path / "results"
    result = subprocess.run(
        [
            str(osclipath),
            "run",
            "--output-directory",
            str(output_directory),
            "-w",
            str(input_osw_path),
        ],
        capture_output=True,
        encoding="utf-8",
    )

    assert result.returncode != 0
    assert "outside --output-directory" in result.stdout + result.stderr
    assert not output_directory.exists()


@pytest.mark.parametrize("run_directory", [".", "reports", "generated_files/nested"])
def test_output_directory_rejects_conflicting_run_directories(osclipath, tmp_path, run_directory):
    input_osw_path = tmp_path / "conflicting.osw"
    input_osw_path.write_text(json.dumps({"run_directory": run_directory, "steps": []}, indent=2))

    output_directory = tmp_path / "results"
    result = subprocess.run(
        [
            str(osclipath),
            "run",
            "--output-directory",
            str(output_directory),
            "-w",
            str(input_osw_path),
        ],
        capture_output=True,
        encoding="utf-8",
    )

    assert result.returncode != 0
    assert not output_directory.exists()
