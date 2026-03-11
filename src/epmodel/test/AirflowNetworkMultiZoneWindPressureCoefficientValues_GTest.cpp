/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../ModelObject/AirflowNetworkMultiZoneWindPressureCoefficientValues.hpp"

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, AirflowNetworkMultiZoneWindPressureCoefficientValues_DefaultConstructor) {
  Model model;
  AirflowNetworkMultiZoneWindPressureCoefficientValues windPressureCoefficientValues(model);
  EXPECT_EQ(AirflowNetworkMultiZoneWindPressureCoefficientValues::iddObjectType(), windPressureCoefficientValues.iddObject().type());
}

TEST_F(EPModelFixture, AirflowNetworkMultiZoneWindPressureCoefficientValues_ScalarAccessors_RoundTrip) {
  Model model;
  AirflowNetworkMultiZoneWindPressureCoefficientValues windPressureCoefficientValues(model);

  EXPECT_TRUE(windPressureCoefficientValues.setName("WPC Values for N-S-E-W"));
  EXPECT_EQ("WPC Values for N-S-E-W", windPressureCoefficientValues.nameString());
}
