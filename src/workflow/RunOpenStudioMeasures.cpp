/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "OSWorkflow.hpp"

#include "../model/Model.hpp"

#include "../utilities/filetypes/WorkflowJSON.hpp"
#include "../utilities/filetypes/RunOptions.hpp"
#include "../utilities/core/Filesystem.hpp"

namespace openstudio {

void OSWorkflow::runOpenStudioMeasures() {
  state = State::OpenStudioMeasures;

  // Weather file is handled in runInitialization

  LOG(Info, "Beginning to execute OpenStudio Measures");
  applyMeasures(MeasureType::ModelMeasure, ApplyMeasureType::Regular);
  LOG(Info, "Finished applying OpenStudio Measures.");

  LOG(Info, "Beginning to execute Reporting Measures's Model Output Requests");
  applyMeasures(MeasureType::ReportingMeasure, ApplyMeasureType::ModelOutputRequests);
  LOG(Info, "Finished applying Reporting Measures's Model Output Requests.")

  // Save final OSM
  if (!workflowJSON.runOptions()->fast()) {
    // Save to run dir
    auto savePath = workflowJSON.absoluteRunDir() / "in.osm";
    detailedTimeBlock("Saving Final OSM to Run Dir", [this, &savePath]() {
      // TODO: workflow gem was actually serializating via model.to_s for speed...
      model.save(savePath, true);
    });
  }

  communicateMeasureAttributes();
  saveOSMToRootDirIfDebug();
}

}  // namespace openstudio
