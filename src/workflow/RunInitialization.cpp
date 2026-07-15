/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "OSWorkflow.hpp"

#include "Util.hpp"

#include "../model/Model.hpp"
#include "../model/WeatherFile.hpp"
#include "../model/FileOperations.hpp"
#include "../epmodel/Model.hpp"
#include "../energyplus/ForwardTranslator.hpp"

#include "../utilities/filetypes/WorkflowJSON.hpp"
#include "../utilities/filetypes/RunOptions.hpp"
#include "../utilities/filetypes/ForwardTranslatorOptions.hpp"

#include "../utilities/core/Assert.hpp"
#include "../utilities/core/Filesystem.hpp"
#include "../utilities/idf/IdfFile.hpp"

#include <fmt/chrono.h>

namespace openstudio {

void OSWorkflow::runInitialization() {

  state = State::Initialization;

  auto rootDir = workflowJSON.absoluteRootDir();
  LOG(Debug, "The root_dir for the datapoint is " << rootDir);

  detailedTimeBlock("Wiping directories", [this, &rootDir]() {
    {
      auto generatedFilesDir = rootDir / "generated_files";
      if (openstudio::filesystem::is_directory(generatedFilesDir)) {
        LOG(Debug, "Removing existing generated files directory: " << generatedFilesDir);
        openstudio::filesystem::remove_all(generatedFilesDir);
      }
      LOG(Debug, "Creating generated files directory: " << generatedFilesDir);
      openstudio::filesystem::create_directories(generatedFilesDir);

      // insert the generated files directory in the first spot so all generated ExternalFiles go here
      auto fps = workflowJSON.filePaths();
      workflowJSON.resetFilePaths();
      workflowJSON.addFilePath(generatedFilesDir);
      for (const auto& fp : fps) {
        workflowJSON.addFilePath(fp);
      }

      auto reportsDir = rootDir / "reports";
      if (openstudio::filesystem::is_directory(reportsDir)) {
        LOG(Debug, "Removing existing reports directory: " << reportsDir);
        openstudio::filesystem::remove_all(reportsDir);
      }
    }
  });

  // TODO: Validate the OSW measures if the flag is set to true, (the default state)
  // There isn't a 'verify_osw' key in the RunOptions, so always do it for now. Maybe don't if `fast`?
  {
    LOG(Info, "Attempting to validate the measure workflow");

    if (!workflowJSON.validateMeasures()) {
      LOG_AND_THROW("Workflow is invalid");
    }

    LOG(Info, "Validated the measure workflow");
  }

  LOG(Debug, "Finding and loading the seed file");
  bool loadedIDFSeed = false;
  auto seedPath_ = workflowJSON.seedFile();
  if (seedPath_) {
    auto modelFullPath_ = workflowJSON.findFile(seedPath_.get());
    if (!modelFullPath_) {
      state = State::Errored;
      throw std::runtime_error(fmt::format("Seed model {} specified in OSW cannot be found", seedPath_->string()));
    }

    if (modelFullPath_->extension() == openstudio::filesystem::path(".idf")) {
      loadedIDFSeed = true;
      if (m_add_timings && m_detailed_timings) {
        m_timers->newTimer("    Loading seed IDF");
      }
      detailedTimeBlock("Loading seed IDF as epmodel", [this, &modelFullPath_] {
        epModel_ = std::make_unique<openstudio::epmodel::Model>(openstudio::workflow::util::loadEPModel(modelFullPath_.get()));
      });

    } else {
      detailedTimeBlock("Loading seed OSM (VersionTranslation)",
                        [this, &modelFullPath_] { model = openstudio::workflow::util::loadOSM(modelFullPath_.get()); });
    }
  } else {
    model = openstudio::model::Model{};
    openstudio::model::initializeModelObjects(model);
  }

  // The OSM ingress translation now happens during initialization, before ModelMeasures run.
  // Attach the workflow file-search context before that translation so any model objects that
  // resolve external files see the generated_files directory and the OSW file_paths exactly as
  // they did when translation happened later in the workflow.
  model.setWorkflowJSON(workflowJSON.clone());

  initializeWeatherFileFromOSW();

  if (epModel_) {
    workspace_ = openstudio::Workspace(*epModel_);
  } else if (!m_post_process_only) {
    detailedTimeBlock("Translating seed OSM to EnergyPlus IDF for epmodel", [this]() {
      openstudio::energyplus::ForwardTranslator ft;
      ft.setForwardTranslatorOptions(workflowJSON.runOptions()->forwardTranslatorOptions());
      workspace_ = ft.translateModel(model);
      epModel_ = std::make_unique<openstudio::epmodel::Model>(workspace_->toIdfFile());
    });
  }

  if (epModel_ && !m_post_process_only && !workflowJSON.runOptions()->fast()) {
    auto savePath = workflowJSON.absoluteRunDir() / "pre-model-measures.idf";
    detailedTimeBlock(loadedIDFSeed ? "Saving staged seed IDF to Run Dir" : "Saving staged translated seed IDF to Run Dir", [this, &savePath]() {
      /*
       * The seed file remains read-only.  For an IDF seed this is a byte-level new artifact in the
       * workflow, not an overwrite of the user input.  For an OSM seed this is the point where the
       * workflow crosses from the legacy canonical model into the EnergyPlus/IDD-backed model.
       */
      epModel_->save(savePath, true);
    });
  }

  const auto seedModelicaPath = workflowJSON.seedModelicaFile();
  if (seedModelicaPath) {
    auto seedModelicaFileFullPath = workflowJSON.findFile(seedModelicaPath.get());
    if (!seedModelicaFileFullPath) {
      state = State::Errored;
      throw std::runtime_error(fmt::format("Seed Modelica File: {}, specified in OSW cannot be found", seedModelicaPath->string()));
    }
    modelicaFile = modelica::ModelicaFile(seedModelicaFileFullPath.get());
    m_modelicaSeedFileName = seedModelicaFileFullPath->filename();
    m_latestModelicaFilePath = seedModelicaFileFullPath.get();
  }

  // Tell the workflowJSON we have started, it'll log the start time and reset the stepResults
  workflowJSON.start();
}

}  // namespace openstudio
