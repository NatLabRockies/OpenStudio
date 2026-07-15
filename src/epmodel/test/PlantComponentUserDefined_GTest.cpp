/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include <algorithm>

#include <utilities/idd/PlantComponent_UserDefined_FieldEnums.hxx>

#include "EPModelFixture.hpp"
#include "../Loop/PlantLoop.hpp"
#include "../StraightComponent/Node.hpp"
#include "../StraightComponent/PlantComponentUserDefined.hpp"
#include "../StraightComponent/PlantComponentUserDefined_Impl.hpp"

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, PlantComponentUserDefined_DefaultConstructor) {
  Model model;
  PlantComponentUserDefined userDefined(model);
  EXPECT_EQ(PlantComponentUserDefined::iddObjectType(), userDefined.iddObject().type());
  EXPECT_FALSE(userDefined.nameString().empty());
  EXPECT_EQ(1, userDefined.numberOfPlantLoopConnections());
  EXPECT_EQ("MeetsLoadWithNominalCapacityHiOutLimit", userDefined.plantConnection1LoadingMode());
  EXPECT_EQ("NeedsFlowIfLoopOn", userDefined.plantConnection1LoopFlowRequestMode());
  EXPECT_FALSE(userDefined.plantConnection2LoadingMode());
  EXPECT_FALSE(userDefined.plantConnection2LoopFlowRequestMode());
  EXPECT_FALSE(userDefined.plantConnection3LoadingMode());
  EXPECT_FALSE(userDefined.plantConnection3LoopFlowRequestMode());
  EXPECT_FALSE(userDefined.plantConnection4LoadingMode());
  EXPECT_FALSE(userDefined.plantConnection4LoopFlowRequestMode());
}

TEST_F(EPModelFixture, PlantComponentUserDefined_ScalarAccessors_RoundTrip) {
  Model model;
  PlantComponentUserDefined userDefined(model);

  EXPECT_FALSE(PlantComponentUserDefined::plantConnection1LoadingModeValues().empty());
  EXPECT_FALSE(PlantComponentUserDefined::plantConnection1LoopFlowRequestModeValues().empty());
  EXPECT_FALSE(PlantComponentUserDefined::plantConnection2LoadingModeValues().empty());
  EXPECT_FALSE(PlantComponentUserDefined::plantConnection2LoopFlowRequestModeValues().empty());
  EXPECT_FALSE(PlantComponentUserDefined::plantConnection3LoadingModeValues().empty());
  EXPECT_FALSE(PlantComponentUserDefined::plantConnection3LoopFlowRequestModeValues().empty());
  EXPECT_FALSE(PlantComponentUserDefined::plantConnection4LoadingModeValues().empty());
  EXPECT_FALSE(PlantComponentUserDefined::plantConnection4LoopFlowRequestModeValues().empty());

  EXPECT_NE(std::find(PlantComponentUserDefined::plantConnection1LoadingModeValues().begin(),
                      PlantComponentUserDefined::plantConnection1LoadingModeValues().end(), "DemandsLoad"),
            PlantComponentUserDefined::plantConnection1LoadingModeValues().end());
  EXPECT_NE(std::find(PlantComponentUserDefined::plantConnection1LoopFlowRequestModeValues().begin(),
                      PlantComponentUserDefined::plantConnection1LoopFlowRequestModeValues().end(), "NeedsFlowIfLoopOn"),
            PlantComponentUserDefined::plantConnection1LoopFlowRequestModeValues().end());

  EXPECT_FALSE(userDefined.setNumberOfPlantLoopConnections(0));
  EXPECT_FALSE(userDefined.setNumberOfPlantLoopConnections(2));
  EXPECT_FALSE(userDefined.setNumberOfPlantLoopConnections(5));
  EXPECT_EQ(1, userDefined.numberOfPlantLoopConnections());

  EXPECT_FALSE(userDefined.setPlantConnection1LoadingMode("BadValue"));
  EXPECT_EQ("MeetsLoadWithNominalCapacityHiOutLimit", userDefined.plantConnection1LoadingMode());

  const auto loadingMode1 = PlantComponentUserDefined::plantConnection1LoadingModeValues().front();
  EXPECT_TRUE(userDefined.setPlantConnection1LoadingMode(loadingMode1));
  EXPECT_EQ(loadingMode1, userDefined.plantConnection1LoadingMode());

  EXPECT_FALSE(userDefined.setPlantConnection1LoopFlowRequestMode("BadValue"));
  EXPECT_EQ("NeedsFlowIfLoopOn", userDefined.plantConnection1LoopFlowRequestMode());

  const auto loopMode1 = PlantComponentUserDefined::plantConnection1LoopFlowRequestModeValues().front();
  EXPECT_TRUE(userDefined.setPlantConnection1LoopFlowRequestMode(loopMode1));
  EXPECT_EQ(loopMode1, userDefined.plantConnection1LoopFlowRequestMode());

  const auto loadingMode2 = PlantComponentUserDefined::plantConnection2LoadingModeValues().front();
  EXPECT_TRUE(userDefined.setPlantConnection2LoadingMode(loadingMode2));
  ASSERT_TRUE(userDefined.plantConnection2LoadingMode());
  EXPECT_EQ(loadingMode2, userDefined.plantConnection2LoadingMode().get());
  userDefined.resetPlantConnection2LoadingMode();
  ASSERT_TRUE(userDefined.plantConnection2LoadingMode());
  EXPECT_TRUE(userDefined.plantConnection2LoadingMode()->empty());

  const auto loopMode2 = PlantComponentUserDefined::plantConnection2LoopFlowRequestModeValues().front();
  EXPECT_TRUE(userDefined.setPlantConnection2LoopFlowRequestMode(loopMode2));
  ASSERT_TRUE(userDefined.plantConnection2LoopFlowRequestMode());
  EXPECT_EQ(loopMode2, userDefined.plantConnection2LoopFlowRequestMode().get());
  userDefined.resetPlantConnection2LoopFlowRequestMode();
  ASSERT_TRUE(userDefined.plantConnection2LoopFlowRequestMode());
  EXPECT_TRUE(userDefined.plantConnection2LoopFlowRequestMode()->empty());

  const auto loadingMode3 = PlantComponentUserDefined::plantConnection3LoadingModeValues().front();
  EXPECT_TRUE(userDefined.setPlantConnection3LoadingMode(loadingMode3));
  ASSERT_TRUE(userDefined.plantConnection3LoadingMode());
  EXPECT_EQ(loadingMode3, userDefined.plantConnection3LoadingMode().get());
  userDefined.resetPlantConnection3LoadingMode();
  ASSERT_TRUE(userDefined.plantConnection3LoadingMode());
  EXPECT_TRUE(userDefined.plantConnection3LoadingMode()->empty());

  const auto loopMode3 = PlantComponentUserDefined::plantConnection3LoopFlowRequestModeValues().front();
  EXPECT_TRUE(userDefined.setPlantConnection3LoopFlowRequestMode(loopMode3));
  ASSERT_TRUE(userDefined.plantConnection3LoopFlowRequestMode());
  EXPECT_EQ(loopMode3, userDefined.plantConnection3LoopFlowRequestMode().get());
  userDefined.resetPlantConnection3LoopFlowRequestMode();
  ASSERT_TRUE(userDefined.plantConnection3LoopFlowRequestMode());
  EXPECT_TRUE(userDefined.plantConnection3LoopFlowRequestMode()->empty());

  const auto loadingMode4 = PlantComponentUserDefined::plantConnection4LoadingModeValues().front();
  EXPECT_TRUE(userDefined.setPlantConnection4LoadingMode(loadingMode4));
  ASSERT_TRUE(userDefined.plantConnection4LoadingMode());
  EXPECT_EQ(loadingMode4, userDefined.plantConnection4LoadingMode().get());
  userDefined.resetPlantConnection4LoadingMode();
  ASSERT_TRUE(userDefined.plantConnection4LoadingMode());
  EXPECT_TRUE(userDefined.plantConnection4LoadingMode()->empty());

  const auto loopMode4 = PlantComponentUserDefined::plantConnection4LoopFlowRequestModeValues().front();
  EXPECT_TRUE(userDefined.setPlantConnection4LoopFlowRequestMode(loopMode4));
  ASSERT_TRUE(userDefined.plantConnection4LoopFlowRequestMode());
  EXPECT_EQ(loopMode4, userDefined.plantConnection4LoopFlowRequestMode().get());
  userDefined.resetPlantConnection4LoopFlowRequestMode();
  ASSERT_TRUE(userDefined.plantConnection4LoopFlowRequestMode());
  EXPECT_TRUE(userDefined.plantConnection4LoopFlowRequestMode()->empty());

  auto cloneObject = model.addObject(userDefined.idfObject());
  ASSERT_TRUE(cloneObject);
  auto clone = cloneObject->cast<PlantComponentUserDefined>();
  EXPECT_EQ(1, clone.numberOfPlantLoopConnections());
  ASSERT_TRUE(clone.plantConnection2LoadingMode());
  EXPECT_TRUE(clone.plantConnection2LoadingMode()->empty());
  ASSERT_TRUE(clone.plantConnection2LoopFlowRequestMode());
  EXPECT_TRUE(clone.plantConnection2LoopFlowRequestMode()->empty());
}

TEST_F(EPModelFixture, PlantComponentUserDefined_AddToAndRemoveFromPlantLoop) {
  Model model;
  PlantLoop plantLoop(model);
  PlantComponentUserDefined userDefined(model);

  auto supplyOutletNode = plantLoop.supplyOutletNode();
  EXPECT_TRUE(userDefined.addToNode(supplyOutletNode));
  EXPECT_EQ(1, userDefined.numberOfPlantLoopConnections());
  ASSERT_TRUE(userDefined.loop());
  EXPECT_EQ(plantLoop.handle(), userDefined.loop()->handle());
  ASSERT_TRUE(userDefined.inletModelObject());
  ASSERT_TRUE(userDefined.outletModelObject());
  EXPECT_TRUE(plantLoop.supplyComponent(userDefined.handle()));
  EXPECT_FALSE(plantLoop.demandComponent(userDefined.handle()));

  auto inletNode = userDefined.getModelObjectTarget<Node>(openstudio::PlantComponent_UserDefinedFields::PlantConnection1InletNodeName);
  auto outletNode = userDefined.getModelObjectTarget<Node>(openstudio::PlantComponent_UserDefinedFields::PlantConnection1OutletNodeName);
  ASSERT_TRUE(inletNode);
  ASSERT_TRUE(outletNode);
  EXPECT_EQ(userDefined.inletModelObject()->handle(), inletNode->handle());
  EXPECT_EQ(userDefined.outletModelObject()->handle(), outletNode->handle());

  auto demandOutletNode = plantLoop.demandOutletNode();
  EXPECT_TRUE(userDefined.addToNode(demandOutletNode));
  EXPECT_EQ(1, userDefined.numberOfPlantLoopConnections());
  ASSERT_TRUE(userDefined.loop());
  EXPECT_EQ(plantLoop.handle(), userDefined.loop()->handle());
  ASSERT_TRUE(userDefined.inletModelObject());
  ASSERT_TRUE(userDefined.outletModelObject());
  EXPECT_FALSE(plantLoop.supplyComponent(userDefined.handle()));
  EXPECT_TRUE(plantLoop.demandComponent(userDefined.handle()));

  inletNode = userDefined.getModelObjectTarget<Node>(openstudio::PlantComponent_UserDefinedFields::PlantConnection1InletNodeName);
  outletNode = userDefined.getModelObjectTarget<Node>(openstudio::PlantComponent_UserDefinedFields::PlantConnection1OutletNodeName);
  ASSERT_TRUE(inletNode);
  ASSERT_TRUE(outletNode);
  EXPECT_EQ(userDefined.inletModelObject()->handle(), inletNode->handle());
  EXPECT_EQ(userDefined.outletModelObject()->handle(), outletNode->handle());

  EXPECT_TRUE(userDefined.removeFromLoop());
  EXPECT_FALSE(userDefined.loop());
  EXPECT_TRUE(userDefined.inletModelObject());
  EXPECT_TRUE(userDefined.outletModelObject());

  userDefined.disconnect();
  EXPECT_FALSE(userDefined.inletModelObject());
  EXPECT_FALSE(userDefined.outletModelObject());
  EXPECT_FALSE(plantLoop.supplyComponent(userDefined.handle()));
  EXPECT_FALSE(plantLoop.demandComponent(userDefined.handle()));
}
