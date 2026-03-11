/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../ModelObject/AirflowNetworkMultiZoneWindPressureCoefficientArray.hpp"

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, AirflowNetworkMultiZoneWindPressureCoefficientArray_DefaultConstructor) {
  Model model;
  AirflowNetworkMultiZoneWindPressureCoefficientArray windPressureCoefficientArray(model);
  EXPECT_EQ(AirflowNetworkMultiZoneWindPressureCoefficientArray::iddObjectType(), windPressureCoefficientArray.iddObject().type());
}

TEST_F(EPModelFixture, AirflowNetworkMultiZoneWindPressureCoefficientArray_ScalarAccessors_RoundTrip) {
  Model model;
  AirflowNetworkMultiZoneWindPressureCoefficientArray windPressureCoefficientArray(model);

  EXPECT_TRUE(windPressureCoefficientArray.setName("WPC Array 36 Directions"));
  EXPECT_EQ("WPC Array 36 Directions", windPressureCoefficientArray.nameString());
}
