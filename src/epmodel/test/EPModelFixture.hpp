/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_TEST_EPMODELFIXTURE_HPP
#define EPMODEL_TEST_EPMODELFIXTURE_HPP

#include <gtest/gtest.h>

#include <resources.hxx>

#include "../Model.hpp"

#include "../../utilities/core/Logger.hpp"
#include "../../utilities/core/FileLogSink.hpp"

class EPModelFixture : public ::testing::Test
{
 protected:
  void SetUp() override;
  void TearDown() override;

  static void SetUpTestSuite();
  static void TearDownTestSuite();

  REGISTER_LOGGER("EPModelFixture");

  static boost::optional<openstudio::FileLogSink> logFile;
};

#endif  // EPMODEL_TEST_EPMODELFIXTURE_HPP
