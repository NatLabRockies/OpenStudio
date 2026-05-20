/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "EPModelFixture.hpp"

#include "../../utilities/core/Finder.hpp"

using openstudio::Logger;
using openstudio::FileLogSink;
using openstudio::toPath;

void EPModelFixture::SetUp() {}

void EPModelFixture::TearDown() {}

void EPModelFixture::SetUpTestSuite() {
  logFile = FileLogSink(toPath("./EPModelTestFixture.log"));
  logFile->setLogLevel(Debug);
  logFile->useWorkflowGemFormatter(true, true);
  Logger::instance().standardOutLogger().disable();

  openstudio::filesystem::create_directory(resourcesPath() / toPath("epmodel"));
}

void EPModelFixture::TearDownTestSuite() {
  logFile->disable();
}

boost::optional<openstudio::FileLogSink> EPModelFixture::logFile;
