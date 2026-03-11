/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../StraightComponent/PlantComponentUserDefined.hpp"

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, PlantComponentUserDefined_DefaultConstructor) {
  Model model;
  PlantComponentUserDefined userDefined(model);
  EXPECT_EQ(PlantComponentUserDefined::iddObjectType(), userDefined.iddObject().type());
  EXPECT_FALSE(userDefined.nameString().empty());
}

TEST_F(EPModelFixture, PlantComponentUserDefined_ScalarAccessors_RoundTrip) {
  Model model;
  PlantComponentUserDefined userDefined(model);

  EXPECT_TRUE(userDefined.setNumberOfPlantLoopConnections(2));
  EXPECT_EQ(2, userDefined.numberOfPlantLoopConnections());

  const auto loadingMode1 = PlantComponentUserDefined::plantConnection1LoadingModeValues().front();
  EXPECT_TRUE(userDefined.setPlantConnection1LoadingMode(loadingMode1));
  EXPECT_EQ(loadingMode1, userDefined.plantConnection1LoadingMode());

  const auto loopMode1 = PlantComponentUserDefined::plantConnection1LoopFlowRequestModeValues().front();
  EXPECT_TRUE(userDefined.setPlantConnection1LoopFlowRequestMode(loopMode1));
  EXPECT_EQ(loopMode1, userDefined.plantConnection1LoopFlowRequestMode());

  const auto loadingMode2 = PlantComponentUserDefined::plantConnection2LoadingModeValues().front();
  EXPECT_TRUE(userDefined.setPlantConnection2LoadingMode(loadingMode2));
  ASSERT_TRUE(userDefined.plantConnection2LoadingMode());
  EXPECT_EQ(loadingMode2, userDefined.plantConnection2LoadingMode().get());
  userDefined.resetPlantConnection2LoadingMode();

  const auto loopMode2 = PlantComponentUserDefined::plantConnection2LoopFlowRequestModeValues().front();
  EXPECT_TRUE(userDefined.setPlantConnection2LoopFlowRequestMode(loopMode2));
  ASSERT_TRUE(userDefined.plantConnection2LoopFlowRequestMode());
  EXPECT_EQ(loopMode2, userDefined.plantConnection2LoopFlowRequestMode().get());
  userDefined.resetPlantConnection2LoopFlowRequestMode();

  const auto loadingMode3 = PlantComponentUserDefined::plantConnection3LoadingModeValues().front();
  EXPECT_TRUE(userDefined.setPlantConnection3LoadingMode(loadingMode3));
  ASSERT_TRUE(userDefined.plantConnection3LoadingMode());
  EXPECT_EQ(loadingMode3, userDefined.plantConnection3LoadingMode().get());
  userDefined.resetPlantConnection3LoadingMode();

  const auto loopMode3 = PlantComponentUserDefined::plantConnection3LoopFlowRequestModeValues().front();
  EXPECT_TRUE(userDefined.setPlantConnection3LoopFlowRequestMode(loopMode3));
  ASSERT_TRUE(userDefined.plantConnection3LoopFlowRequestMode());
  EXPECT_EQ(loopMode3, userDefined.plantConnection3LoopFlowRequestMode().get());
  userDefined.resetPlantConnection3LoopFlowRequestMode();

  const auto loadingMode4 = PlantComponentUserDefined::plantConnection4LoadingModeValues().front();
  EXPECT_TRUE(userDefined.setPlantConnection4LoadingMode(loadingMode4));
  ASSERT_TRUE(userDefined.plantConnection4LoadingMode());
  EXPECT_EQ(loadingMode4, userDefined.plantConnection4LoadingMode().get());
  userDefined.resetPlantConnection4LoadingMode();

  const auto loopMode4 = PlantComponentUserDefined::plantConnection4LoopFlowRequestModeValues().front();
  EXPECT_TRUE(userDefined.setPlantConnection4LoopFlowRequestMode(loopMode4));
  ASSERT_TRUE(userDefined.plantConnection4LoopFlowRequestMode());
  EXPECT_EQ(loopMode4, userDefined.plantConnection4LoopFlowRequestMode().get());
  userDefined.resetPlantConnection4LoopFlowRequestMode();
}
