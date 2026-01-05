/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "OSWorkflow.hpp"

#include "../utilities/filetypes/EpwFile.hpp"

namespace openstudio {

void OSWorkflow::runModelicaMeasures() {
  state = State::ModelicaMeasures;

  LOG(Info, "Beginning to execute Modelica Measures");
  const auto workflow = runner.workflow();
  const auto seedModelicaModel = workflow.seedModelicaModel();
  OS_ASSERT(seedModelicaModel);

  const auto runDir = workflow.absoluteRunDir();
  const auto quotePath = [](const openstudio::path& p) {
    auto s = p.generic_string();
    s.insert(s.begin(), '"');
    s.push_back('"');
    return s;
  };
  auto params = runner.modelicaParameters();

  const auto idfPath = runDir / "in.idf";
  params.setParameterValue(*seedModelicaModel, "idfPath", quotePath(idfPath));
  LOG(Info, "Setting Modelica parameter 'idfPath' to '" << idfPath.generic_string() << "'");

  if (const auto epwPath = runner.lastEpwFilePath()) {
    params.setParameterValue(*seedModelicaModel, "epwPath", quotePath(*epwPath));
    LOG(Info, "Setting Modelica parameter 'epwPath' to '" << epwPath->generic_string() << "'");

    const auto mosPath = runDir / "in.mos";
    bool generatedMos = false;
    if (auto epwFile = EpwFile::load(*epwPath, true)) {
      try {
        const auto parent = mosPath.parent_path();
        if (!parent.empty()) {
          openstudio::filesystem::create_directories(parent);
        }
      } catch (const std::exception& e) {
        LOG(Warn, "Unable to ensure directory for Modelica .mos file '" << mosPath.generic_string() << "': " << e.what());
      }

      generatedMos = epwFile->translateToMos(mosPath);
      if (!generatedMos) {
        LOG(Warn, "Failed to convert weather file '" << epwPath->generic_string() << "' into '" << mosPath.generic_string() << "'");
      }
    } else {
      LOG(Warn, "Unable to load weather file '" << epwPath->generic_string() << "' to generate a Modelica .mos file");
    }

    if (generatedMos) {
      params.setParameterValue(*seedModelicaModel, "weaPath", quotePath(mosPath));
      LOG(Info, "Setting Modelica parameter 'weaPath' to '" << mosPath.generic_string() << "'");
    }
  } else {
    LOG(Warn, "No weather file available from the workflow; 'epwPath' and 'weaPath' Modelica parameters were not set");
  }

  applyMeasures(MeasureType::ModelicaMeasure, ApplyMeasureType::Regular);
  try {
    saveModelicaFileSnapshot(workflowJSON.absoluteRunDir());
  } catch (const std::exception& e) {
    runner.registerError(e.what());
    state = State::Errored;
    throw;
  }
  LOG(Info, "Finished applying Modelica Measures.");

  communicateMeasureAttributes();
}

}  // namespace openstudio
