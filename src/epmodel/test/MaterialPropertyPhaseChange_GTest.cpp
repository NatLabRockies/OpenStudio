/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../ModelObject/MaterialPropertyPhaseChange.hpp"

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, MaterialPropertyPhaseChange_DefaultConstructor) {
  Model model;
  MaterialPropertyPhaseChange object(model);
  EXPECT_EQ(MaterialPropertyPhaseChange::iddObjectType(), object.iddObject().type());
}

TEST_F(EPModelFixture, MaterialPropertyPhaseChange_ScalarAccessors_RoundTrip) {
  Model model;
  MaterialPropertyPhaseChange object(model);

  EXPECT_TRUE(object.isTemperatureCoefficientforThermalConductivityDefaulted());

  EXPECT_TRUE(object.setTemperatureCoefficientforThermalConductivity(0.0025));
  EXPECT_DOUBLE_EQ(0.0025, object.temperatureCoefficientforThermalConductivity());
  EXPECT_FALSE(object.isTemperatureCoefficientforThermalConductivityDefaulted());

  object.resetTemperatureCoefficientforThermalConductivity();
  EXPECT_TRUE(object.isTemperatureCoefficientforThermalConductivityDefaulted());
}
