import pytest

from workflow_helpers import run_workflow


@pytest.mark.parametrize("language", ["ruby", "python"])
def test_reportingmeasure_model_output_requests(osclipath, language: str):
    base_osw_name = f"{language}.osw"

    runDir, r = run_workflow(
        osclipath=osclipath,
        base_osw_name=base_osw_name,
        suffix="labs",
        verbose=False,
        debug=True,
        post_process_only=False,
    )
    r.check_returncode()
    assert r.returncode == 0
