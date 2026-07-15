/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "OSWorkflow.hpp"

#include "Util.hpp"

#include "../epmodel/Model.hpp"

#include "../utilities/filetypes/WorkflowJSON.hpp"

#include "../utilities/core/Filesystem.hpp"

namespace openstudio {

void OSWorkflow::runTranslator() {

  state = State::Translator;

  // skip if halted
  // TODO: I don't understand this
  if (runner.halted()) {
    LOG(Info, "Workflow halted, skipping the OSM to IDF translation");
    // This allows model arguments to still be calculated
    workspace_ = Workspace{};
    return;
  }

  auto runDir = workflowJSON.absoluteRunDir();
  OS_ASSERT(openstudio::filesystem::is_directory(runDir));

  // Copy in the weather file
  if (!epwPath.empty()) {
    openstudio::filesystem::copy_file(epwPath, runDir / "in.epw", openstudio::filesystem::copy_options::overwrite_existing);
  } else {
    LOG(Warn, "EPW file not found");
  }

  if (!epModel_) {
    LOG_AND_THROW("Cannot stage EnergyPlus input because the workflow does not have an initialized epmodel.");
  }

  LOG(Info, "Staging epmodel as the EnergyPlus workspace");
  detailedTimeBlock("Serializing epmodel to EnergyPlus IDF", [this]() {
    /*
     * This state deliberately no longer forward translates the post-measure model.  Translation has
     * already happened at workflow ingress when the seed was an OSM.  From this point forward the
     * workflow model is the EnergyPlus/IDD-backed epmodel, so the EnergyPlus workspace is just the
     * serialized view of the same object graph the ModelMeasures mutated.
     */
    workspace_ = openstudio::Workspace(*epModel_);
  });
  LOG(Info, "Successfully staged epmodel as IDF");

  saveIDFToRootDirIfDebug();
}

}  // namespace openstudio
