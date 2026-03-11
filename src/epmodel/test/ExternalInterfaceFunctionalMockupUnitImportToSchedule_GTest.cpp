/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../Schedule/ExternalInterfaceFunctionalMockupUnitImportToSchedule.hpp"

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, ExternalInterfaceFunctionalMockupUnitImportToSchedule_DefaultConstructor) {
  Model model;
  ExternalInterfaceFunctionalMockupUnitImportToSchedule object(model);
  EXPECT_EQ(ExternalInterfaceFunctionalMockupUnitImportToSchedule::iddObjectType(), object.iddObject().type());
}

TEST_F(EPModelFixture, ExternalInterfaceFunctionalMockupUnitImportToSchedule_ScalarAccessors_RoundTrip) {
  Model model;
  ExternalInterfaceFunctionalMockupUnitImportToSchedule object(model);

  EXPECT_TRUE(object.setFMUInstanceName("instanceA"));
  EXPECT_EQ("instanceA", object.fMUInstanceName());

  EXPECT_TRUE(object.setFMUVariableName("variableA"));
  EXPECT_EQ("variableA", object.fMUVariableName());

  EXPECT_TRUE(object.setInitialValue(11.25));
  EXPECT_DOUBLE_EQ(11.25, object.initialValue());
}
