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
  ASSERT_TRUE(panel.getDouble(openstudio::ZoneHVAC_CoolingPanel_RadiantConvective_WaterFields::RatedInletWaterTemperature, false));
  EXPECT_DOUBLE_EQ(8.0, panel.getDouble(openstudio::ZoneHVAC_CoolingPanel_RadiantConvective_WaterFields::RatedInletWaterTemperature, false).get());
  ASSERT_TRUE(panel.getDouble(openstudio::ZoneHVAC_CoolingPanel_RadiantConvective_WaterFields::RatedInletSpaceTemperature, false));
  EXPECT_DOUBLE_EQ(23.0, panel.getDouble(openstudio::ZoneHVAC_CoolingPanel_RadiantConvective_WaterFields::RatedInletSpaceTemperature, false).get());
  ASSERT_TRUE(panel.getDouble(openstudio::ZoneHVAC_CoolingPanel_RadiantConvective_WaterFields::RatedWaterMassFlowRate, false));
  EXPECT_DOUBLE_EQ(0.07, panel.getDouble(openstudio::ZoneHVAC_CoolingPanel_RadiantConvective_WaterFields::RatedWaterMassFlowRate, false).get());
  ASSERT_TRUE(panel.getString(openstudio::ZoneHVAC_CoolingPanel_RadiantConvective_WaterFields::CoolingDesignCapacityMethod, false));
  EXPECT_EQ("CoolingDesignCapacity",
            panel.getString(openstudio::ZoneHVAC_CoolingPanel_RadiantConvective_WaterFields::CoolingDesignCapacityMethod, false).get());
  ASSERT_TRUE(panel.getString(openstudio::ZoneHVAC_CoolingPanel_RadiantConvective_WaterFields::CoolingDesignCapacity, false));
  EXPECT_EQ("autosize", panel.getString(openstudio::ZoneHVAC_CoolingPanel_RadiantConvective_WaterFields::CoolingDesignCapacity, false).get());
  ASSERT_TRUE(panel.getDouble(openstudio::ZoneHVAC_CoolingPanel_RadiantConvective_WaterFields::CoolingDesignCapacityPerFloorArea, false));
  EXPECT_DOUBLE_EQ(10.0,
                   panel.getDouble(openstudio::ZoneHVAC_CoolingPanel_RadiantConvective_WaterFields::CoolingDesignCapacityPerFloorArea, false)
                     .get());
  ASSERT_TRUE(panel.getDouble(openstudio::ZoneHVAC_CoolingPanel_RadiantConvective_WaterFields::FractionofAutosizedCoolingDesignCapacity, false));
  EXPECT_DOUBLE_EQ(
    0.9,
    panel.getDouble(openstudio::ZoneHVAC_CoolingPanel_RadiantConvective_WaterFields::FractionofAutosizedCoolingDesignCapacity, false).get());
  ASSERT_TRUE(panel.getDouble(openstudio::ZoneHVAC_CoolingPanel_RadiantConvective_WaterFields::MaximumChilledWaterFlowRate, false));
  EXPECT_DOUBLE_EQ(0.09, panel.getDouble(openstudio::ZoneHVAC_CoolingPanel_RadiantConvective_WaterFields::MaximumChilledWaterFlowRate, false).get());
  ASSERT_TRUE(panel.getString(openstudio::ZoneHVAC_CoolingPanel_RadiantConvective_WaterFields::ControlType, false));
  EXPECT_EQ("OutdoorDryBulbTemperature",
            panel.getString(openstudio::ZoneHVAC_CoolingPanel_RadiantConvective_WaterFields::ControlType, false).get());
  ASSERT_TRUE(panel.getDouble(openstudio::ZoneHVAC_CoolingPanel_RadiantConvective_WaterFields::CoolingControlThrottlingRange, false));
  EXPECT_DOUBLE_EQ(
    0.8, panel.getDouble(openstudio::ZoneHVAC_CoolingPanel_RadiantConvective_WaterFields::CoolingControlThrottlingRange, false).get());
  ASSERT_TRUE(panel.getTarget(openstudio::ZoneHVAC_CoolingPanel_RadiantConvective_WaterFields::CoolingControlTemperatureScheduleName));
  EXPECT_EQ(controlSchedule.handle(),
            panel.getTarget(openstudio::ZoneHVAC_CoolingPanel_RadiantConvective_WaterFields::CoolingControlTemperatureScheduleName)->handle());
  ASSERT_TRUE(panel.getString(openstudio::ZoneHVAC_CoolingPanel_RadiantConvective_WaterFields::CondensationControlType, false));
  EXPECT_EQ("VariableOff",
            panel.getString(openstudio::ZoneHVAC_CoolingPanel_RadiantConvective_WaterFields::CondensationControlType, false).get());
  ASSERT_TRUE(panel.getDouble(openstudio::ZoneHVAC_CoolingPanel_RadiantConvective_WaterFields::CondensationControlDewpointOffset, false));
  EXPECT_DOUBLE_EQ(
    1.7, panel.getDouble(openstudio::ZoneHVAC_CoolingPanel_RadiantConvective_WaterFields::CondensationControlDewpointOffset, false).get());

  coil.resetRatedInletWaterTemperature();
  coil.resetRatedInletSpaceTemperature();
  coil.resetRatedWaterMassFlowRate();
  coil.resetCoolingDesignCapacityMethod();
  coil.autosizeCoolingDesignCapacity();
  coil.autosizeMaximumChilledWaterFlowRate();
  coil.resetControlType();
  coil.resetCoolingControlThrottlingRange();
  coil.resetCoolingControlTemperatureSchedule();
  coil.resetCondensationControlType();
  coil.resetCondensationControlDewpointOffset();

  EXPECT_TRUE(coil.isRatedInletWaterTemperatureDefaulted());
  EXPECT_TRUE(coil.isRatedInletSpaceTemperatureDefaulted());
  EXPECT_TRUE(coil.isRatedWaterMassFlowRateDefaulted());
  EXPECT_TRUE(coil.isCoolingDesignCapacityMethodDefaulted());
  EXPECT_TRUE(coil.isCoolingDesignCapacityAutosized());
  EXPECT_FALSE(coil.coolingDesignCapacity());
  EXPECT_FALSE(coil.autosizedCoolingDesignCapacity());
  EXPECT_TRUE(coil.isMaximumChilledWaterFlowRateAutosized());
  EXPECT_FALSE(coil.maximumChilledWaterFlowRate());
  EXPECT_FALSE(coil.autosizedMaximumChilledWaterFlowRate());
  EXPECT_TRUE(coil.isControlTypeDefaulted());
  EXPECT_TRUE(coil.isCoolingControlThrottlingRangeDefaulted());
  EXPECT_FALSE(coil.coolingControlTemperatureSchedule());
  EXPECT_TRUE(coil.isCondensationControlTypeDefaulted());
  EXPECT_TRUE(coil.isCondensationControlDewpointOffsetDefaulted());
  EXPECT_FALSE(panel.getDouble(openstudio::ZoneHVAC_CoolingPanel_RadiantConvective_WaterFields::RatedInletWaterTemperature, false));
  EXPECT_FALSE(panel.getDouble(openstudio::ZoneHVAC_CoolingPanel_RadiantConvective_WaterFields::RatedInletSpaceTemperature, false));
  EXPECT_FALSE(panel.getDouble(openstudio::ZoneHVAC_CoolingPanel_RadiantConvective_WaterFields::RatedWaterMassFlowRate, false));
  ASSERT_TRUE(panel.getString(openstudio::ZoneHVAC_CoolingPanel_RadiantConvective_WaterFields::CoolingDesignCapacityMethod, false));
  EXPECT_TRUE(panel.getString(openstudio::ZoneHVAC_CoolingPanel_RadiantConvective_WaterFields::CoolingDesignCapacityMethod, false)->empty());
  ASSERT_TRUE(panel.getString(openstudio::ZoneHVAC_CoolingPanel_RadiantConvective_WaterFields::CoolingDesignCapacity, false));
  EXPECT_EQ("autosize", panel.getString(openstudio::ZoneHVAC_CoolingPanel_RadiantConvective_WaterFields::CoolingDesignCapacity, false).get());
  ASSERT_TRUE(panel.getString(openstudio::ZoneHVAC_CoolingPanel_RadiantConvective_WaterFields::MaximumChilledWaterFlowRate, false));
  EXPECT_EQ("autosize",
            panel.getString(openstudio::ZoneHVAC_CoolingPanel_RadiantConvective_WaterFields::MaximumChilledWaterFlowRate, false).get());
  ASSERT_TRUE(panel.getString(openstudio::ZoneHVAC_CoolingPanel_RadiantConvective_WaterFields::ControlType, false));
  EXPECT_TRUE(panel.getString(openstudio::ZoneHVAC_CoolingPanel_RadiantConvective_WaterFields::ControlType, false)->empty());
  EXPECT_FALSE(panel.getDouble(openstudio::ZoneHVAC_CoolingPanel_RadiantConvective_WaterFields::CoolingControlThrottlingRange, false));
  EXPECT_FALSE(panel.getTarget(openstudio::ZoneHVAC_CoolingPanel_RadiantConvective_WaterFields::CoolingControlTemperatureScheduleName));
  ASSERT_TRUE(panel.getString(openstudio::ZoneHVAC_CoolingPanel_RadiantConvective_WaterFields::CondensationControlType, false));
  EXPECT_TRUE(panel.getString(openstudio::ZoneHVAC_CoolingPanel_RadiantConvective_WaterFields::CondensationControlType, false)->empty());
  EXPECT_FALSE(panel.getDouble(openstudio::ZoneHVAC_CoolingPanel_RadiantConvective_WaterFields::CondensationControlDewpointOffset, false));
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
