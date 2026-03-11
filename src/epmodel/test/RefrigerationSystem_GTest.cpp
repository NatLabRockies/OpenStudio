/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../ModelObject/FluidPropertiesName.hpp"
#include "../ModelObject/RefrigerationSystem.hpp"

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, RefrigerationSystem_DefaultConstructor) {
  Model model;
  RefrigerationSystem system(model);

  EXPECT_EQ(RefrigerationSystem::iddObjectType(), system.iddObject().type());
  EXPECT_DOUBLE_EQ(21.0, system.minimumCondensingTemperature());
  EXPECT_EQ("ConstantSuctionTemperature", system.suctionTemperatureControlType());
}

TEST_F(EPModelFixture, RefrigerationSystem_ScalarAccessors_RoundTrip) {
  Model model;
  RefrigerationSystem system(model);

  EXPECT_TRUE(system.setMinimumCondensingTemperature(24.1));
  EXPECT_DOUBLE_EQ(24.1, system.minimumCondensingTemperature());

  FluidPropertiesName fluid(model);
  ASSERT_FALSE(fluid.fluidTypeValues().empty());
  EXPECT_TRUE(fluid.setFluidName("R404a"));
  EXPECT_TRUE(fluid.setFluidType(fluid.fluidTypeValues().front()));
  EXPECT_TRUE(system.setRefrigerationSystemWorkingFluidType(fluid.fluidName()));
  EXPECT_EQ(fluid.fluidName(), system.refrigerationSystemWorkingFluidType());

  auto intercoolerValues = RefrigerationSystem::intercoolerTypeValues();
  ASSERT_FALSE(intercoolerValues.empty());
  EXPECT_TRUE(system.setIntercoolerType(intercoolerValues.front()));
  EXPECT_EQ(intercoolerValues.front(), system.intercoolerType());

  EXPECT_TRUE(system.setSumUASuctionPiping(5.5));
  EXPECT_DOUBLE_EQ(5.5, system.sumUASuctionPiping());
  EXPECT_FALSE(system.isSumUASuctionPipingDefaulted());

  EXPECT_TRUE(system.setEndUseSubcategory("Retail"));
  EXPECT_EQ("Retail", system.endUseSubcategory());
  EXPECT_FALSE(system.isEndUseSubcategoryDefaulted());

  EXPECT_TRUE(system.setShellandCoilIntercoolerEffectiveness(0.85));
  EXPECT_DOUBLE_EQ(0.85, system.shellandCoilIntercoolerEffectiveness());
  EXPECT_FALSE(system.isShellandCoilIntercoolerEffectivenessDefaulted());

  system.resetSumUASuctionPiping();
  EXPECT_TRUE(system.isSumUASuctionPipingDefaulted());

  system.resetEndUseSubcategory();
  EXPECT_TRUE(system.isEndUseSubcategoryDefaulted());

  system.resetIntercoolerType();
  EXPECT_TRUE(system.isIntercoolerTypeDefaulted());

  system.resetShellandCoilIntercoolerEffectiveness();
  EXPECT_TRUE(system.isShellandCoilIntercoolerEffectivenessDefaulted());
}

// The TransferLoadList object only exposes a name, so ensure the base name API round-trips for this type.
TEST_F(EPModelFixture, RefrigerationSystem_TransferLoadListName) {
  Model model;
  RefrigerationSystem system(model);

  const char* listName = "TransferLoadListLink";
  system.setName(listName);
  EXPECT_EQ(listName, system.nameString());
}
