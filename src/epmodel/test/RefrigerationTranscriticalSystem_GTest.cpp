/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../ModelObject/FluidPropertiesName.hpp"
#include "../ModelObject/RefrigerationTranscriticalSystem.hpp"

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, RefrigerationTranscriticalSystem_DefaultConstructor) {
  Model model;
  RefrigerationTranscriticalSystem system(model);
  EXPECT_EQ(RefrigerationTranscriticalSystem::iddObjectType(), system.iddObject().type());
  EXPECT_DOUBLE_EQ(3500000.0, system.receiverPressure());
  EXPECT_DOUBLE_EQ(0.4, system.subcoolerEffectiveness());
  EXPECT_EQ("R744", system.refrigerationSystemWorkingFluidType());
  EXPECT_DOUBLE_EQ(0.0, system.sumUASuctionPipingforMediumTemperatureLoads());
  EXPECT_DOUBLE_EQ(0.0, system.sumUASuctionPipingforLowTemperatureLoads());
  EXPECT_TRUE(system.isEndUseSubcategoryDefaulted());
}

TEST_F(EPModelFixture, RefrigerationTranscriticalSystem_ScalarAccessors_RoundTrip) {
  Model model;
  RefrigerationTranscriticalSystem system(model);

  EXPECT_TRUE(system.setReceiverPressure(3600000.0));
  EXPECT_DOUBLE_EQ(3600000.0, system.receiverPressure());
  system.resetReceiverPressure();
  EXPECT_TRUE(system.isReceiverPressureDefaulted());

  EXPECT_TRUE(system.setSubcoolerEffectiveness(0.5));
  EXPECT_DOUBLE_EQ(0.5, system.subcoolerEffectiveness());
  system.resetSubcoolerEffectiveness();
  EXPECT_TRUE(system.isSubcoolerEffectivenessDefaulted());

  FluidPropertiesName fluid(model);
  ASSERT_FALSE(fluid.fluidTypeValues().empty());
  EXPECT_TRUE(fluid.setFluidName("R134a"));
  EXPECT_TRUE(fluid.setFluidType(fluid.fluidTypeValues().front()));
  EXPECT_TRUE(system.setRefrigerationSystemWorkingFluidType(fluid.fluidName()));
  EXPECT_EQ(fluid.fluidName(), system.refrigerationSystemWorkingFluidType());

  EXPECT_TRUE(system.setSumUASuctionPipingforMediumTemperatureLoads(1.1));
  EXPECT_DOUBLE_EQ(1.1, system.sumUASuctionPipingforMediumTemperatureLoads());
  system.resetSumUASuctionPipingforMediumTemperatureLoads();
  EXPECT_TRUE(system.isSumUASuctionPipingforMediumTemperatureLoadsDefaulted());

  EXPECT_TRUE(system.setSumUASuctionPipingforLowTemperatureLoads(2.2));
  EXPECT_DOUBLE_EQ(2.2, system.sumUASuctionPipingforLowTemperatureLoads());
  system.resetSumUASuctionPipingforLowTemperatureLoads();
  EXPECT_TRUE(system.isSumUASuctionPipingforLowTemperatureLoadsDefaulted());

  EXPECT_TRUE(system.setEndUseSubcategory("Grocery"));
  EXPECT_EQ("Grocery", system.endUseSubcategory());
  EXPECT_FALSE(system.isEndUseSubcategoryDefaulted());
  system.resetEndUseSubcategory();
  EXPECT_TRUE(system.isEndUseSubcategoryDefaulted());
}
