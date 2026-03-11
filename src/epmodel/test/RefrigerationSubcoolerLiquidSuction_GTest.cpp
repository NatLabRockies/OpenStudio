/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../ModelObject/RefrigerationSubcoolerLiquidSuction.hpp"

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, RefrigerationSubcoolerLiquidSuction_DefaultConstructor) {
  Model model;
  RefrigerationSubcoolerLiquidSuction subcooler(model);
  EXPECT_EQ(RefrigerationSubcoolerLiquidSuction::iddObjectType(), subcooler.iddObject().type());
  EXPECT_DOUBLE_EQ(6.0, subcooler.liquidSuctionDesignSubcoolingTemperatureDifference().value());
  EXPECT_DOUBLE_EQ(16.0, subcooler.designLiquidInletTemperature().value());
  EXPECT_DOUBLE_EQ(0.0, subcooler.designVaporInletTemperature().value());
}

TEST_F(EPModelFixture, RefrigerationSubcoolerLiquidSuction_ScalarAccessors_RoundTrip) {
  Model model;
  RefrigerationSubcoolerLiquidSuction subcooler(model);

  EXPECT_TRUE(subcooler.setLiquidSuctionDesignSubcoolingTemperatureDifference(4.3));
  EXPECT_TRUE(subcooler.setDesignLiquidInletTemperature(13.4));
  EXPECT_TRUE(subcooler.setDesignVaporInletTemperature(-2.1));

  EXPECT_DOUBLE_EQ(4.3, subcooler.liquidSuctionDesignSubcoolingTemperatureDifference().value());
  EXPECT_DOUBLE_EQ(13.4, subcooler.designLiquidInletTemperature().value());
  EXPECT_DOUBLE_EQ(-2.1, subcooler.designVaporInletTemperature().value());
}
