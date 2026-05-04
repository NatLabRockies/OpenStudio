/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../ModelObject/ExternalInterface.hpp"
#include "../ModelObject/ExternalInterface_Impl.hpp"

#include <algorithm>

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, ExternalInterface_DefaultConstructor) {
  Model model;
  auto externalInterface = model.getUniqueModelObject<ExternalInterface>();
  EXPECT_EQ(ExternalInterface::iddObjectType(), externalInterface.iddObject().type());
  EXPECT_EQ("PtolemyServer", externalInterface.nameofExternalInterface());
}

TEST_F(EPModelFixture, ExternalInterface_ScalarAccessors_RoundTrip) {
  Model model;
  auto externalInterface = model.getUniqueModelObject<ExternalInterface>();

  const auto values = ExternalInterface::nameofExternalInterfaceValues();
  EXPECT_NE(values.end(), std::find(values.begin(), values.end(), "PtolemyServer"));
  EXPECT_NE(values.end(), std::find(values.begin(), values.end(), "FunctionalMockupUnitImport"));
  EXPECT_NE(values.end(), std::find(values.begin(), values.end(), "FunctionalMockupUnitExport"));

  EXPECT_FALSE(externalInterface.setNameofExternalInterface("bad value"));
  EXPECT_TRUE(externalInterface.setNameofExternalInterface("FunctionalMockupUnitImport"));
  EXPECT_EQ("FunctionalMockupUnitImport", externalInterface.nameofExternalInterface());
}
