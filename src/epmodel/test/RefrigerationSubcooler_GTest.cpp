/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../ModelObject/RefrigerationSubcooler.hpp"
#include "../ModelObject/RefrigerationSubcooler_Impl.hpp"
#include "../ModelObject/RefrigerationSubcoolerLiquidSuction.hpp"
#include "../ModelObject/RefrigerationSubcoolerLiquidSuction_Impl.hpp"
#include "../ModelObject/RefrigerationSubcoolerMechanical.hpp"
#include "../ModelObject/RefrigerationSubcoolerMechanical_Impl.hpp"

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, RefrigerationSubcooler_DefaultConstructor) {
  Model model;
  RefrigerationSubcooler subcooler(model);

  EXPECT_EQ(RefrigerationSubcooler::iddObjectType(), subcooler.iddObject().type());
  EXPECT_EQ("LiquidSuction", subcooler.subcoolerType());
}

TEST_F(EPModelFixture, RefrigerationSubcooler_ScalarAccessors_RoundTrip) {
  Model model;
  RefrigerationSubcooler subcooler(model);

  EXPECT_TRUE(subcooler.setSubcoolerType("Mechanical"));
  EXPECT_EQ("Mechanical", subcooler.subcoolerType());
  EXPECT_TRUE(subcooler.setOutletControlTemperature(8.5));
  ASSERT_TRUE(subcooler.outletControlTemperature());
  EXPECT_DOUBLE_EQ(8.5, *subcooler.outletControlTemperature());

  EXPECT_TRUE(subcooler.setSubcoolerType("LiquidSuction"));
  EXPECT_EQ("LiquidSuction", subcooler.subcoolerType());
  EXPECT_TRUE(subcooler.setLiquidSuctionDesignSubcoolingTemperatureDifference(4.4));
  EXPECT_TRUE(subcooler.setDesignLiquidInletTemperature(14.0));
  EXPECT_TRUE(subcooler.setDesignVaporInletTemperature(-1.3));

  ASSERT_TRUE(subcooler.liquidSuctionDesignSubcoolingTemperatureDifference());
  ASSERT_TRUE(subcooler.designLiquidInletTemperature());
  ASSERT_TRUE(subcooler.designVaporInletTemperature());
  EXPECT_DOUBLE_EQ(4.4, *subcooler.liquidSuctionDesignSubcoolingTemperatureDifference());
  EXPECT_DOUBLE_EQ(14.0, *subcooler.designLiquidInletTemperature());
  EXPECT_DOUBLE_EQ(-1.3, *subcooler.designVaporInletTemperature());
}

TEST_F(EPModelFixture, RefrigerationSubcooler_TypedQueriesFilterBySubtypeImpl) {
  Model model;
  RefrigerationSubcoolerLiquidSuction liquid(model);
  RefrigerationSubcoolerMechanical mechanical(model);
  RefrigerationSubcooler generic(model);

  auto liquidObjects = model.getConcreteModelObjects<RefrigerationSubcoolerLiquidSuction>();
  auto mechanicalObjects = model.getConcreteModelObjects<RefrigerationSubcoolerMechanical>();
  auto allSubcoolers = model.getConcreteModelObjects<RefrigerationSubcooler>();

  EXPECT_EQ(1u, liquidObjects.size());
  EXPECT_EQ(1u, mechanicalObjects.size());
  EXPECT_EQ(3u, allSubcoolers.size());
  EXPECT_EQ("LiquidSuction", liquidObjects[0].subcoolerType());
  EXPECT_EQ("Mechanical", mechanicalObjects[0].subcoolerType());
  EXPECT_EQ("LiquidSuction", generic.subcoolerType());
}
