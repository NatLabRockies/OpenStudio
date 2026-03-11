/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../Schedule/ExternalInterfaceFunctionalMockupUnitExportToSchedule.hpp"

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, ExternalInterfaceFunctionalMockupUnitExportToSchedule_Constructor) {
  Model model;
  ExternalInterfaceFunctionalMockupUnitExportToSchedule object(model, "fmuVar");
  EXPECT_EQ(ExternalInterfaceFunctionalMockupUnitExportToSchedule::iddObjectType(), object.iddObject().type());
  EXPECT_EQ("fmuVar", object.fMUVariableName());

  ExternalInterfaceFunctionalMockupUnitExportToSchedule withInitial(model, "fmuVar2", 8.5);
  ASSERT_TRUE(withInitial.initialValue());
  EXPECT_DOUBLE_EQ(8.5, withInitial.initialValue().get());
}

TEST_F(EPModelFixture, ExternalInterfaceFunctionalMockupUnitExportToSchedule_ScalarAccessors_RoundTrip) {
  Model model;
  ExternalInterfaceFunctionalMockupUnitExportToSchedule object(model, "fmuVar");

  EXPECT_TRUE(object.setFMUVariableName("fmuVarNew"));
  EXPECT_EQ("fmuVarNew", object.fMUVariableName());

  EXPECT_FALSE(object.initialValue());
  EXPECT_TRUE(object.setInitialValue(12.0));
  ASSERT_TRUE(object.initialValue());
  EXPECT_DOUBLE_EQ(12.0, object.initialValue().get());
}
