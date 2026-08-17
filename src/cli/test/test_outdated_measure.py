from workflow_helpers import run_workflow


def test_outdated_reportingmeasure(osclipath):
    runDir, r = run_workflow(
        osclipath=osclipath,
        base_osw_name="outdatedreportingmeasure.osw",
        suffix="labs",
        verbose=False,
        debug=True,
        post_process_only=True,
    )
    r.check_returncode()
    assert r.returncode == 0
