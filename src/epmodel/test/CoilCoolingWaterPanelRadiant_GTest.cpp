/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <algorithm>
#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../Loop/PlantLoop.hpp"
#include "../Schedule/ScheduleConstant.hpp"
#include "../StraightComponent/CoilCoolingWaterPanelRadiant.hpp"
#include "../StraightComponent/CoilCoolingWaterPanelRadiant_Impl.hpp"
#include "../StraightComponent/Node.hpp"
#include "../ZoneHVACComponent/ZoneHVACCoolingPanelRadiantConvectiveWater.hpp"

#include <utilities/idd/ZoneHVAC_CoolingPanel_RadiantConvective_Water_FieldEnums.hxx>

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, CoilCoolingWaterPanelRadiant_IsTransientCompanionView) {
  Model model;
  ZoneHVACCoolingPanelRadiantConvectiveWater panel(model);

  auto coil = panel.coolingCoil().cast<CoilCoolingWaterPanelRadiant>();
  EXPECT_EQ(CoilCoolingWaterPanelRadiant::iddObjectType(), coil.iddObject().type());
  EXPECT_TRUE(coil.getImpl<detail::CoilCoolingWaterPanelRadiant_Impl>()->isTransient());
}

TEST_F(EPModelFixture, CoilCoolingWaterPanelRadiant_ResolvesParentWaterNodesAndWritesThroughStorage) {
  Model model;
  ZoneHVACCoolingPanelRadiantConvectiveWater panel(model);
  auto coil = panel.coolingCoil().cast<CoilCoolingWaterPanelRadiant>();

  ScheduleConstant controlSchedule(model);
  ASSERT_TRUE(controlSchedule.setValue(19.0));

  Node inlet = model.getOrCreateTransientByName<Node>("Cooling Panel Coil Inlet");
  Node outlet = model.getOrCreateTransientByName<Node>("Cooling Panel Coil Outlet");
  ASSERT_TRUE(panel.setPointer(openstudio::ZoneHVAC_CoolingPanel_RadiantConvective_WaterFields::WaterInletNodeName, inlet.handle()));
  ASSERT_TRUE(panel.setPointer(openstudio::ZoneHVAC_CoolingPanel_RadiantConvective_WaterFields::WaterOutletNodeName, outlet.handle()));

  ASSERT_TRUE(coil.setRatedInletWaterTemperature(8.0));
  ASSERT_TRUE(coil.setRatedInletSpaceTemperature(23.0));
  ASSERT_TRUE(coil.setRatedWaterMassFlowRate(0.07));
  ASSERT_TRUE(coil.setCoolingDesignCapacityMethod("CoolingDesignCapacity"));
  coil.autosizeCoolingDesignCapacity();
  ASSERT_TRUE(coil.setCoolingDesignCapacityPerFloorArea(10.0));
  ASSERT_TRUE(coil.setFractionofAutosizedCoolingDesignCapacity(0.9));
  ASSERT_TRUE(coil.setMaximumChilledWaterFlowRate(0.09));
  ASSERT_TRUE(coil.setControlType("OutdoorDryBulbTemperature"));
  ASSERT_TRUE(coil.setCoolingControlThrottlingRange(0.8));
  ASSERT_TRUE(coil.setCoolingControlTemperatureSchedule(controlSchedule));
  ASSERT_TRUE(coil.setCondensationControlType("VariableOff"));
  ASSERT_TRUE(coil.setCondensationControlDewpointOffset(1.7));

  EXPECT_DOUBLE_EQ(8.0, coil.ratedInletWaterTemperature());
  EXPECT_DOUBLE_EQ(23.0, coil.ratedInletSpaceTemperature());
  EXPECT_DOUBLE_EQ(0.07, coil.ratedWaterMassFlowRate());
  EXPECT_EQ("CoolingDesignCapacity", coil.coolingDesignCapacityMethod());
  EXPECT_TRUE(coil.isCoolingDesignCapacityAutosized());
  EXPECT_DOUBLE_EQ(10.0, coil.coolingDesignCapacityPerFloorArea());
  EXPECT_DOUBLE_EQ(0.9, coil.fractionofAutosizedCoolingDesignCapacity());
  ASSERT_TRUE(coil.maximumChilledWaterFlowRate());
  EXPECT_DOUBLE_EQ(0.09, *coil.maximumChilledWaterFlowRate());
  EXPECT_EQ("OutdoorDryBulbTemperature", coil.controlType());
  EXPECT_DOUBLE_EQ(0.8, coil.coolingControlThrottlingRange());
  ASSERT_TRUE(coil.coolingControlTemperatureSchedule());
  EXPECT_EQ(controlSchedule.handle(), coil.coolingControlTemperatureSchedule()->handle());
  EXPECT_EQ("VariableOff", coil.condensationControlType());
  EXPECT_DOUBLE_EQ(1.7, coil.condensationControlDewpointOffset());
  ASSERT_TRUE(coil.inletModelObject());
  EXPECT_EQ(inlet.handle(), coil.inletModelObject()->handle());
  ASSERT_TRUE(coil.outletModelObject());
  EXPECT_EQ(outlet.handle(), coil.outletModelObject()->handle());
  EXPECT_FALSE(coil.addToNode(inlet));
}

TEST_F(EPModelFixture, CoilCoolingWaterPanelRadiant_PlantLoopTraversalProjectsTransientChild) {
  Model model;
  PlantLoop plantLoop(model);
  ZoneHVACCoolingPanelRadiantConvectiveWater panel(model);
  auto coil = panel.coolingCoil().cast<CoilCoolingWaterPanelRadiant>();

  ASSERT_TRUE(plantLoop.addDemandBranchForComponent(coil));
  ASSERT_TRUE(coil.plantLoop());
  EXPECT_EQ(plantLoop.handle(), coil.plantLoop()->handle());
  EXPECT_FALSE(panel.plantLoop());

  const auto demandComponents = plantLoop.demandComponents();
  EXPECT_TRUE(std::any_of(demandComponents.begin(), demandComponents.end(), [&](const auto& object) { return object.handle() == coil.handle(); }));
  EXPECT_FALSE(std::any_of(demandComponents.begin(), demandComponents.end(), [&](const auto& object) { return object.handle() == panel.handle(); }));

  auto inletNode = coil.inletModelObject()->cast<Node>();
  ASSERT_TRUE(inletNode.outletModelObject());
  EXPECT_EQ(coil.handle(), inletNode.outletModelObject()->handle());

  ASSERT_TRUE(coil.removeFromLoop());
  EXPECT_FALSE(coil.plantLoop());
  EXPECT_FALSE(coil.inletModelObject());
  EXPECT_FALSE(coil.outletModelObject());
}
