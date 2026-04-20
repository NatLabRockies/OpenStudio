/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>
#include "EPModelFixture.hpp"
#include "../scaffolds/HeatExchangerAirToAirFlatPlate.hpp"

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, HeatExchangerAirToAirFlatPlate_DefaultConstructor) {
  Model model;
  HeatExchangerAirToAirFlatPlate object(model);

  EXPECT_EQ(HeatExchangerAirToAirFlatPlate::iddObjectType(), object.iddObject().type());
}

TEST_F(EPModelFixture, HeatExchangerAirToAirFlatPlate_ScalarAccessors_RoundTrip) {
  Model model;
  HeatExchangerAirToAirFlatPlate object(model);

  EXPECT_TRUE(object.setRatioofSupplytoSecondaryhAValues(1.1));
  ASSERT_TRUE(object.ratioofSupplytoSecondaryhAValues());
  EXPECT_DOUBLE_EQ(1.1, object.ratioofSupplytoSecondaryhAValues().get());
  EXPECT_FALSE(object.setRatioofSupplytoSecondaryhAValues(-0.5));
  const auto values = HeatExchangerAirToAirFlatPlate::flowArrangementTypeValues();
  EXPECT_GE(values.size(), 1u);
}
