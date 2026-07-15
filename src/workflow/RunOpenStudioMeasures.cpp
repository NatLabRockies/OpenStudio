/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "OSWorkflow.hpp"

#include "../model/Model.hpp"
#include "../epmodel/Model.hpp"

#include "../utilities/filetypes/WorkflowJSON.hpp"
#include "../utilities/filetypes/RunOptions.hpp"
#include "../utilities/core/Filesystem.hpp"
#include "../utilities/idf/Workspace.hpp"

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

  if (!epModel_) {
    LOG_AND_THROW("Cannot run OpenStudio ModelMeasures because the workflow does not have an initialized epmodel.");
  }

  // Save the model-measure artifact without modifying the seed.  The mutable workflow model is
  // already EnergyPlus/IDD-backed, so the step artifact is an IDF instead of an OSM.
  if (!workflowJSON.runOptions()->fast()) {
    auto savePath = workflowJSON.absoluteRunDir() / "model-measures.idf";
    detailedTimeBlock("Saving ModelMeasure IDF to Run Dir", [this, &savePath]() { epModel_->save(savePath, true); });
  }

  communicateMeasureAttributes();
  workspace_ = openstudio::Workspace(*epModel_);
  saveIDFToRootDirIfDebug();
}

}  // namespace openstudio
