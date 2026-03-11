/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"

#include "../Loop/AirLoopHVAC.hpp"
#include "../ModelObject/SizingSystem.hpp"

#include <utilities/idd/Sizing_System_FieldEnums.hxx>

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, SizingSystem_DefaultConstructor) {
  Model model;
  AirLoopHVAC airLoop(model);
  SizingSystem sizingSystem(model, airLoop);

  EXPECT_EQ(SizingSystem::iddObjectType(), sizingSystem.iddObject().type());

  EXPECT_DOUBLE_EQ(0.3, sizingSystem.centralHeatingMaximumSystemAirFlowRatio().get());
  EXPECT_TRUE(sizingSystem.allOutdoorAirinCooling());
  EXPECT_TRUE(sizingSystem.allOutdoorAirinHeating());
  EXPECT_TRUE(sizingSystem.isCoolingDesignCapacityAutosized());
  EXPECT_TRUE(sizingSystem.isHeatingDesignCapacityAutosized());
}

TEST_F(EPModelFixture, SizingSystem_ScalarAccessors_RoundTrip) {
  Model model;
  AirLoopHVAC airLoop(model);
  SizingSystem sizingSystem(model, airLoop);

  EXPECT_FALSE(SizingSystem::validTypeofLoadtoSizeOnValues().empty());
  EXPECT_FALSE(SizingSystem::validSizingOptionValues().empty());
  EXPECT_FALSE(SizingSystem::validCoolingDesignAirFlowMethodValues().empty());
  EXPECT_FALSE(SizingSystem::validHeatingDesignAirFlowMethodValues().empty());
  EXPECT_FALSE(SizingSystem::validSystemOutdoorAirMethodValues().empty());
  EXPECT_FALSE(SizingSystem::heatingCoilSizingMethodValues().empty());

  EXPECT_TRUE(sizingSystem.setSizingOption("Coincident"));
  EXPECT_EQ("Coincident", sizingSystem.sizingOption());
  EXPECT_EQ("Coincident", sizingSystem.getString(openstudio::Sizing_SystemFields::TypeofZoneSumtoUse, true).get());

  EXPECT_TRUE(sizingSystem.setCoolingDesignAirFlowMethod("Flow/System"));
  EXPECT_EQ("Flow/System", sizingSystem.coolingDesignAirFlowMethod());
  EXPECT_EQ("Flow/System", sizingSystem.getString(openstudio::Sizing_SystemFields::CoolingSupplyAirFlowRateMethod, true).get());

  EXPECT_TRUE(sizingSystem.setHeatingDesignAirFlowMethod("Flow/System"));
  EXPECT_EQ("Flow/System", sizingSystem.heatingDesignAirFlowMethod());
  EXPECT_EQ("Flow/System", sizingSystem.getString(openstudio::Sizing_SystemFields::HeatingSupplyAirFlowRateMethod, true).get());

  EXPECT_TRUE(sizingSystem.setAllOutdoorAirinCooling(false));
  EXPECT_FALSE(sizingSystem.allOutdoorAirinCooling());
  EXPECT_EQ("No", sizingSystem.getString(openstudio::Sizing_SystemFields::AllOutdoorAirinCooling, true).get());

  EXPECT_TRUE(sizingSystem.setAllOutdoorAirinHeating(false));
  EXPECT_FALSE(sizingSystem.allOutdoorAirinHeating());
  EXPECT_EQ("No", sizingSystem.getString(openstudio::Sizing_SystemFields::AllOutdoorAirinHeating, true).get());

  sizingSystem.autosizeDesignOutdoorAirFlowRate();
  EXPECT_TRUE(sizingSystem.isDesignOutdoorAirFlowRateAutosized());
  EXPECT_FALSE(sizingSystem.designOutdoorAirFlowRate());

  EXPECT_TRUE(sizingSystem.setDesignOutdoorAirFlowRate(1.234));
  EXPECT_FALSE(sizingSystem.isDesignOutdoorAirFlowRateAutosized());
  ASSERT_TRUE(sizingSystem.designOutdoorAirFlowRate());
  EXPECT_DOUBLE_EQ(1.234, sizingSystem.designOutdoorAirFlowRate().get());

  sizingSystem.resetDesignOutdoorAirFlowRate();
  EXPECT_TRUE(sizingSystem.isDesignOutdoorAirFlowRateDefaulted());

  sizingSystem.autosizeCentralHeatingMaximumSystemAirFlowRatio();
  EXPECT_TRUE(sizingSystem.isCentralHeatingMaximumSystemAirFlowRatioAutosized());
  EXPECT_FALSE(sizingSystem.centralHeatingMaximumSystemAirFlowRatio());

  EXPECT_TRUE(sizingSystem.setCentralHeatingMaximumSystemAirFlowRatio(0.42));
  EXPECT_FALSE(sizingSystem.isCentralHeatingMaximumSystemAirFlowRatioAutosized());
  ASSERT_TRUE(sizingSystem.centralHeatingMaximumSystemAirFlowRatio());
  EXPECT_DOUBLE_EQ(0.42, sizingSystem.centralHeatingMaximumSystemAirFlowRatio().get());

  sizingSystem.autosizeOccupantDiversity();
  EXPECT_TRUE(sizingSystem.isOccupantDiversityAutosized());
  EXPECT_FALSE(sizingSystem.occupantDiversity());

  EXPECT_TRUE(sizingSystem.setOccupantDiversity(0.87));
  ASSERT_TRUE(sizingSystem.occupantDiversity());
  EXPECT_DOUBLE_EQ(0.87, sizingSystem.occupantDiversity().get());

  EXPECT_TRUE(sizingSystem.setCoolingDesignCapacity(1550.0));
  ASSERT_TRUE(sizingSystem.coolingDesignCapacity());
  EXPECT_DOUBLE_EQ(1550.0, sizingSystem.coolingDesignCapacity().get());
  sizingSystem.autosizeCoolingDesignCapacity();
  EXPECT_TRUE(sizingSystem.isCoolingDesignCapacityAutosized());

  EXPECT_TRUE(sizingSystem.setHeatingDesignCapacity(1660.0));
  ASSERT_TRUE(sizingSystem.heatingDesignCapacity());
  EXPECT_DOUBLE_EQ(1660.0, sizingSystem.heatingDesignCapacity().get());
  sizingSystem.autosizeHeatingDesignCapacity();
  EXPECT_TRUE(sizingSystem.isHeatingDesignCapacityAutosized());
}
