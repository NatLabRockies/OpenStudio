/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"

#include "../ModelObject/OutputControlReportingTolerances.hpp"
#include "../ModelObject/OutputControlReportingTolerances_Impl.hpp"

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, OutputControlReportingTolerances_DefaultConstructor) {
  Model model;
  auto object = model.getUniqueModelObject<OutputControlReportingTolerances>();

  EXPECT_EQ(OutputControlReportingTolerances::iddObjectType(), object.iddObject().type());
}

TEST_F(EPModelFixture, OutputControlReportingTolerances_ScalarAccessors_RoundTrip) {
  Model model;
  auto object = model.getUniqueModelObject<OutputControlReportingTolerances>();

  EXPECT_TRUE(object.setToleranceforTimeHeatingSetpointNotMet(1.16));
  EXPECT_FALSE(object.isToleranceforTimeHeatingSetpointNotMetDefaulted());
  EXPECT_DOUBLE_EQ(1.16, object.toleranceforTimeHeatingSetpointNotMet());

  EXPECT_TRUE(object.setToleranceforTimeCoolingSetpointNotMet(0.75));
  EXPECT_FALSE(object.isToleranceforTimeCoolingSetpointNotMetDefaulted());
  EXPECT_DOUBLE_EQ(0.75, object.toleranceforTimeCoolingSetpointNotMet());

  object.resetToleranceforTimeHeatingSetpointNotMet();
  object.resetToleranceforTimeCoolingSetpointNotMet();

  EXPECT_TRUE(object.isToleranceforTimeHeatingSetpointNotMetDefaulted());
  EXPECT_TRUE(object.isToleranceforTimeCoolingSetpointNotMetDefaulted());
}
