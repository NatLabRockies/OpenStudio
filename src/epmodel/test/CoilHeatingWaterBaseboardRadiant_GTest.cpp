/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <algorithm>
#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../Loop/PlantLoop.hpp"
#include "../ZoneHVACComponent/ZoneHVACBaseboardRadiantConvectiveWaterDesign.hpp"
#include "../ZoneHVACComponent/ZoneHVACBaseboardRadiantConvectiveWaterDesign_Impl.hpp"
#include "../StraightComponent/CoilHeatingWaterBaseboardRadiant.hpp"
#include "../StraightComponent/CoilHeatingWaterBaseboardRadiant_Impl.hpp"
#include "../StraightComponent/Node.hpp"
#include "../ZoneHVACComponent/ZoneHVACBaseboardRadiantConvectiveWater.hpp"

#include <utilities/idd/ZoneHVAC_Baseboard_RadiantConvective_Water_FieldEnums.hxx>

using namespace openstudio;
using namespace openstudio::epmodel;

TEST_F(EPModelFixture, CoilHeatingWaterBaseboardRadiant_IsTransientCompanionView) {
  Model model;
  ZoneHVACBaseboardRadiantConvectiveWater baseboard(model);
  auto heatingCoil = baseboard.heatingCoil();
  auto heatingImpl = heatingCoil.getImpl<openstudio::epmodel::detail::CoilHeatingWaterBaseboardRadiant_Impl>();

  ASSERT_TRUE(heatingImpl);
  EXPECT_TRUE(heatingImpl->isTransient());
  ASSERT_TRUE(heatingCoil.containingZoneHVACComponent());
  EXPECT_EQ(baseboard.handle(), heatingCoil.containingZoneHVACComponent()->handle());
}

TEST_F(EPModelFixture, CoilHeatingWaterBaseboardRadiant_PlantLoopTraversalProjectsTransientChild) {
  Model model;
  PlantLoop plantLoop(model);
  ZoneHVACBaseboardRadiantConvectiveWater baseboard(model);
  auto heatingCoil = baseboard.heatingCoil();

  ASSERT_TRUE(plantLoop.addDemandBranchForComponent(heatingCoil));
  ASSERT_TRUE(heatingCoil.plantLoop());
  EXPECT_EQ(plantLoop.handle(), heatingCoil.plantLoop()->handle());
  EXPECT_FALSE(baseboard.plantLoop());

  const auto demandComponents = plantLoop.demandComponents();
  EXPECT_TRUE(std::any_of(demandComponents.begin(), demandComponents.end(),
                          [&](const auto& object) { return object.handle() == heatingCoil.handle(); }));
  EXPECT_FALSE(std::any_of(demandComponents.begin(), demandComponents.end(),
                           [&](const auto& object) { return object.handle() == baseboard.handle(); }));

  auto inletNode = heatingCoil.inletModelObject()->cast<Node>();
  ASSERT_TRUE(inletNode.outletModelObject());
  EXPECT_EQ(heatingCoil.handle(), inletNode.outletModelObject()->handle());

  ASSERT_TRUE(heatingCoil.removeFromLoop());
  EXPECT_FALSE(heatingCoil.plantLoop());
  EXPECT_FALSE(heatingCoil.inletModelObject());
  EXPECT_FALSE(heatingCoil.outletModelObject());
}

TEST_F(EPModelFixture, CoilHeatingWaterBaseboardRadiant_WriteThroughParentHeatingState) {
  Model model;
  ZoneHVACBaseboardRadiantConvectiveWater baseboard(model);
  auto heatingCoil = baseboard.heatingCoil().cast<CoilHeatingWaterBaseboardRadiant>();

  EXPECT_DOUBLE_EQ(87.78, heatingCoil.ratedAverageWaterTemperature());
  EXPECT_DOUBLE_EQ(0.063, heatingCoil.ratedWaterMassFlowRate());
  EXPECT_EQ("HeatingDesignCapacity", heatingCoil.heatingDesignCapacityMethod());
  EXPECT_TRUE(heatingCoil.isHeatingDesignCapacityAutosized());
  EXPECT_FALSE(heatingCoil.autosizedHeatingDesignCapacity());
  EXPECT_TRUE(heatingCoil.isMaximumWaterFlowRateAutosized());
  EXPECT_FALSE(heatingCoil.autosizedMaximumWaterFlowRate());
  EXPECT_DOUBLE_EQ(0.001, heatingCoil.convergenceTolerance());

  EXPECT_TRUE(heatingCoil.setRatedAverageWaterTemperature(71.0));
  EXPECT_DOUBLE_EQ(71.0, heatingCoil.ratedAverageWaterTemperature());
  ASSERT_TRUE(baseboard.ratedAverageWaterTemperature());
  EXPECT_DOUBLE_EQ(71.0, *baseboard.ratedAverageWaterTemperature());

  EXPECT_TRUE(heatingCoil.setRatedWaterMassFlowRate(0.15));
  EXPECT_DOUBLE_EQ(0.15, heatingCoil.ratedWaterMassFlowRate());
  ASSERT_TRUE(baseboard.ratedWaterMassFlowRate());
  EXPECT_DOUBLE_EQ(0.15, *baseboard.ratedWaterMassFlowRate());

  EXPECT_TRUE(heatingCoil.setHeatingDesignCapacityMethod("CapacityPerFloorArea"));
  EXPECT_EQ("CapacityPerFloorArea", heatingCoil.heatingDesignCapacityMethod());
  ASSERT_TRUE(baseboard.getModelObjectTarget<ZoneHVACBaseboardRadiantConvectiveWaterDesign>(
    openstudio::ZoneHVAC_Baseboard_RadiantConvective_WaterFields::DesignObject));
  auto design = baseboard.getModelObjectTarget<ZoneHVACBaseboardRadiantConvectiveWaterDesign>(
    openstudio::ZoneHVAC_Baseboard_RadiantConvective_WaterFields::DesignObject);
  EXPECT_EQ("CapacityPerFloorArea", design->heatingDesignCapacityMethod());

  EXPECT_TRUE(heatingCoil.setHeatingDesignCapacityPerFloorArea(0.8));
  EXPECT_DOUBLE_EQ(0.8, heatingCoil.heatingDesignCapacityPerFloorArea());
  ASSERT_TRUE(design->heatingDesignCapacityPerFloorArea());
  EXPECT_DOUBLE_EQ(0.8, *design->heatingDesignCapacityPerFloorArea());

  EXPECT_TRUE(heatingCoil.setFractionofAutosizedHeatingDesignCapacity(0.9));
  EXPECT_DOUBLE_EQ(0.9, heatingCoil.fractionofAutosizedHeatingDesignCapacity());
  EXPECT_DOUBLE_EQ(0.9, design->fractionofAutosizedHeatingDesignCapacity());

  EXPECT_TRUE(heatingCoil.setHeatingDesignCapacity(1400.0));
  ASSERT_TRUE(heatingCoil.heatingDesignCapacity());
  EXPECT_DOUBLE_EQ(1400.0, *heatingCoil.heatingDesignCapacity());
  ASSERT_TRUE(baseboard.heatingDesignCapacity());
  EXPECT_DOUBLE_EQ(1400.0, *baseboard.heatingDesignCapacity());
  heatingCoil.autosizeHeatingDesignCapacity();
  EXPECT_TRUE(heatingCoil.isHeatingDesignCapacityAutosized());
  EXPECT_TRUE(baseboard.isHeatingDesignCapacityAutosized());

  EXPECT_TRUE(heatingCoil.setMaximumWaterFlowRate(0.012));
  ASSERT_TRUE(heatingCoil.maximumWaterFlowRate());
  EXPECT_DOUBLE_EQ(0.012, *heatingCoil.maximumWaterFlowRate());
  ASSERT_TRUE(baseboard.maximumWaterFlowRate());
  EXPECT_DOUBLE_EQ(0.012, *baseboard.maximumWaterFlowRate());
  heatingCoil.autosizeMaximumWaterFlowRate();
  EXPECT_TRUE(heatingCoil.isMaximumWaterFlowRateAutosized());
  EXPECT_TRUE(baseboard.isMaximumWaterFlowRateAutosized());

  EXPECT_TRUE(heatingCoil.setConvergenceTolerance(0.002));
  EXPECT_DOUBLE_EQ(0.002, heatingCoil.convergenceTolerance());
  EXPECT_DOUBLE_EQ(0.002, design->convergenceTolerance());
}
