/***********************************************************************************************************************
 *  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
 *  See also https://openstudio.net/license
 ***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"

#include <utilities/idd/Refrigeration_Condenser_WaterCooled_FieldEnums.hxx>

#include "../Loop/AirLoopHVAC.hpp"
#include "../Loop/PlantLoop.hpp"
#include "../ResourceObject/ScheduleTypeLimits.hpp"
#include "../Schedule/Schedule.hpp"
#include "../Schedule/Schedule_Impl.hpp"
#include "../Schedule/ScheduleConstant.hpp"
#include "../Splitter/AirLoopHVACZoneSplitter.hpp"
#include "../StraightComponent/Node.hpp"
#include "../StraightComponent/RefrigerationCondenserWaterCooled.hpp"
#include "../StraightComponent/RefrigerationCondenserWaterCooled_Impl.hpp"

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, RefrigerationCondenserWaterCooled_DefaultConstructor) {
  Model model;
  RefrigerationCondenserWaterCooled condenser(model);

  EXPECT_EQ(RefrigerationCondenserWaterCooled::iddObjectType(), openstudio::IddObjectType::Refrigeration_Condenser_WaterCooled);
  ASSERT_TRUE(condenser.ratedEffectiveTotalHeatRejectionRate());
  EXPECT_DOUBLE_EQ(58000.0, condenser.ratedEffectiveTotalHeatRejectionRate().get());
  EXPECT_DOUBLE_EQ(29.4, condenser.ratedCondensingTemperature());
  EXPECT_DOUBLE_EQ(0.0, condenser.ratedSubcoolingTemperatureDifference());
  EXPECT_FALSE(condenser.isRatedSubcoolingTemperatureDifferenceDefaulted());
  EXPECT_DOUBLE_EQ(10.0, condenser.ratedWaterInletTemperature());
  EXPECT_EQ("ConstantFlow", condenser.waterCooledLoopFlowType());
  EXPECT_FALSE(condenser.isWaterCooledLoopFlowTypeDefaulted());
  EXPECT_FALSE(condenser.waterOutletTemperatureSchedule());
  ASSERT_TRUE(condenser.waterDesignFlowRate());
  EXPECT_DOUBLE_EQ(0.0025, condenser.waterDesignFlowRate().get());
  ASSERT_TRUE(condenser.waterMaximumFlowRate());
  EXPECT_DOUBLE_EQ(0.003, condenser.waterMaximumFlowRate().get());
  EXPECT_DOUBLE_EQ(55.0, condenser.waterMaximumWaterOutletTemperature());
  EXPECT_FALSE(condenser.isWaterMaximumWaterOutletTemperatureDefaulted());
  EXPECT_DOUBLE_EQ(10.0, condenser.waterMinimumWaterInletTemperature());
  EXPECT_FALSE(condenser.isWaterMinimumWaterInletTemperatureDefaulted());
  EXPECT_EQ("General", condenser.endUseSubcategory());
  EXPECT_TRUE(condenser.isEndUseSubcategoryDefaulted());
  EXPECT_FALSE(condenser.condenserRefrigerantOperatingChargeInventory());
  EXPECT_FALSE(condenser.condensateReceiverRefrigerantInventory());
  EXPECT_FALSE(condenser.condensatePipingRefrigerantInventory());
}

TEST_F(EPModelFixture, RefrigerationCondenserWaterCooled_ScheduleAndScalarAccessors_RoundTrip) {
  Model model;
  RefrigerationCondenserWaterCooled condenser(model);

  ScheduleConstant outletTemperatureSchedule(model);
  ASSERT_TRUE(outletTemperatureSchedule.setValue(32.5));
  EXPECT_TRUE(condenser.setWaterOutletTemperatureSchedule(outletTemperatureSchedule));
  ASSERT_TRUE(condenser.waterOutletTemperatureSchedule());
  EXPECT_EQ(outletTemperatureSchedule.handle(), condenser.waterOutletTemperatureSchedule()->handle());
  ASSERT_TRUE(outletTemperatureSchedule.scheduleTypeLimits());
  EXPECT_EQ("Temperature", outletTemperatureSchedule.scheduleTypeLimits()->unitType());
  ASSERT_TRUE(outletTemperatureSchedule.scheduleTypeLimits()->numericType());
  EXPECT_EQ("Continuous", outletTemperatureSchedule.scheduleTypeLimits()->numericType().get());

  ScheduleConstant incompatibleSchedule(model);
  ASSERT_TRUE(incompatibleSchedule.setValue(1.0));
  ScheduleTypeLimits availabilityLimits(model);
  ASSERT_TRUE(availabilityLimits.setUnitType("Availability"));
  ASSERT_TRUE(incompatibleSchedule.setScheduleTypeLimits(availabilityLimits));
  EXPECT_FALSE(condenser.setWaterOutletTemperatureSchedule(incompatibleSchedule));
  ASSERT_TRUE(condenser.waterOutletTemperatureSchedule());
  EXPECT_EQ(outletTemperatureSchedule.handle(), condenser.waterOutletTemperatureSchedule()->handle());

  Model otherModel;
  ScheduleConstant foreignSchedule(otherModel);
  ASSERT_TRUE(foreignSchedule.setValue(30.0));
  EXPECT_FALSE(condenser.setWaterOutletTemperatureSchedule(foreignSchedule));
  ASSERT_TRUE(condenser.waterOutletTemperatureSchedule());
  EXPECT_EQ(outletTemperatureSchedule.handle(), condenser.waterOutletTemperatureSchedule()->handle());

  condenser.resetWaterOutletTemperatureSchedule();
  EXPECT_FALSE(condenser.waterOutletTemperatureSchedule());

  EXPECT_TRUE(condenser.setRatedEffectiveTotalHeatRejectionRate(12345.0));
  ASSERT_TRUE(condenser.ratedEffectiveTotalHeatRejectionRate());
  EXPECT_DOUBLE_EQ(12345.0, condenser.ratedEffectiveTotalHeatRejectionRate().get());
  condenser.resetRatedEffectiveTotalHeatRejectionRate();
  EXPECT_FALSE(condenser.ratedEffectiveTotalHeatRejectionRate());

  EXPECT_TRUE(condenser.setWaterDesignFlowRate(0.005));
  ASSERT_TRUE(condenser.waterDesignFlowRate());
  EXPECT_DOUBLE_EQ(0.005, condenser.waterDesignFlowRate().get());
  condenser.resetWaterDesignFlowRate();
  EXPECT_FALSE(condenser.waterDesignFlowRate());

  EXPECT_TRUE(condenser.setWaterMaximumFlowRate(0.006));
  ASSERT_TRUE(condenser.waterMaximumFlowRate());
  EXPECT_DOUBLE_EQ(0.006, condenser.waterMaximumFlowRate().get());
  condenser.resetWaterMaximumFlowRate();
  EXPECT_FALSE(condenser.waterMaximumFlowRate());

  EXPECT_TRUE(condenser.setWaterMaximumWaterOutletTemperature(54.0));
  EXPECT_FALSE(condenser.isWaterMaximumWaterOutletTemperatureDefaulted());
  EXPECT_DOUBLE_EQ(54.0, condenser.waterMaximumWaterOutletTemperature());
  condenser.resetWaterMaximumWaterOutletTemperature();
  EXPECT_TRUE(condenser.isWaterMaximumWaterOutletTemperatureDefaulted());
  EXPECT_DOUBLE_EQ(55.0, condenser.waterMaximumWaterOutletTemperature());

  EXPECT_TRUE(condenser.setWaterMinimumWaterInletTemperature(12.0));
  EXPECT_FALSE(condenser.isWaterMinimumWaterInletTemperatureDefaulted());
  EXPECT_DOUBLE_EQ(12.0, condenser.waterMinimumWaterInletTemperature());
  condenser.resetWaterMinimumWaterInletTemperature();
  EXPECT_TRUE(condenser.isWaterMinimumWaterInletTemperatureDefaulted());
  EXPECT_DOUBLE_EQ(10.0, condenser.waterMinimumWaterInletTemperature());

  EXPECT_TRUE(condenser.setEndUseSubcategory("CustomRefrigeration"));
  EXPECT_FALSE(condenser.isEndUseSubcategoryDefaulted());
  EXPECT_EQ("CustomRefrigeration", condenser.endUseSubcategory());
  condenser.resetEndUseSubcategory();
  EXPECT_TRUE(condenser.isEndUseSubcategoryDefaulted());
  EXPECT_EQ("General", condenser.endUseSubcategory());

  EXPECT_TRUE(condenser.setWaterCooledLoopFlowType("ConstantFlow"));
  condenser.resetWaterCooledLoopFlowType();
  EXPECT_TRUE(condenser.isWaterCooledLoopFlowTypeDefaulted());
  EXPECT_EQ("VariableFlow", condenser.waterCooledLoopFlowType());

  auto cloneObject = model.addObject(condenser.idfObject());
  ASSERT_TRUE(cloneObject);
  auto clone = cloneObject->cast<RefrigerationCondenserWaterCooled>();
  EXPECT_EQ("VariableFlow", clone.waterCooledLoopFlowType());
  EXPECT_FALSE(clone.waterOutletTemperatureSchedule());
}

TEST_F(EPModelFixture, RefrigerationCondenserWaterCooled_CustomScalarRoundTripViaIdfObject) {
  Model model;
  RefrigerationCondenserWaterCooled condenser(model);

  EXPECT_TRUE(condenser.setRatedEffectiveTotalHeatRejectionRate(52000.0));
  EXPECT_TRUE(condenser.setRatedCondensingTemperature(25.0));
  EXPECT_TRUE(condenser.setRatedSubcoolingTemperatureDifference(3.0));
  EXPECT_TRUE(condenser.setRatedWaterInletTemperature(11.0));
  EXPECT_TRUE(condenser.setWaterCooledLoopFlowType("VariableFlow"));
  EXPECT_TRUE(condenser.setWaterDesignFlowRate(0.005));
  EXPECT_TRUE(condenser.setWaterMaximumFlowRate(0.0055));
  EXPECT_TRUE(condenser.setWaterMaximumWaterOutletTemperature(50.0));
  EXPECT_TRUE(condenser.setWaterMinimumWaterInletTemperature(15.0));
  EXPECT_TRUE(condenser.setEndUseSubcategory("Condensers"));
  EXPECT_TRUE(condenser.setCondenserRefrigerantOperatingChargeInventory(1.5));
  EXPECT_TRUE(condenser.setCondensateReceiverRefrigerantInventory(0.25));
  EXPECT_TRUE(condenser.setCondensatePipingRefrigerantInventory(0.1));

  auto cloneObject = model.addObject(condenser.idfObject());
  ASSERT_TRUE(cloneObject);
  auto clone = cloneObject->cast<RefrigerationCondenserWaterCooled>();

  ASSERT_TRUE(clone.ratedEffectiveTotalHeatRejectionRate());
  EXPECT_DOUBLE_EQ(52000.0, clone.ratedEffectiveTotalHeatRejectionRate().get());
  EXPECT_DOUBLE_EQ(25.0, clone.ratedCondensingTemperature());
  EXPECT_DOUBLE_EQ(3.0, clone.ratedSubcoolingTemperatureDifference());
  EXPECT_DOUBLE_EQ(11.0, clone.ratedWaterInletTemperature());
  EXPECT_EQ("VariableFlow", clone.waterCooledLoopFlowType());
  ASSERT_TRUE(clone.waterDesignFlowRate());
  EXPECT_DOUBLE_EQ(0.005, clone.waterDesignFlowRate().get());
  ASSERT_TRUE(clone.waterMaximumFlowRate());
  EXPECT_DOUBLE_EQ(0.0055, clone.waterMaximumFlowRate().get());
  EXPECT_DOUBLE_EQ(50.0, clone.waterMaximumWaterOutletTemperature());
  EXPECT_DOUBLE_EQ(15.0, clone.waterMinimumWaterInletTemperature());
  EXPECT_EQ("Condensers", clone.endUseSubcategory());
  ASSERT_TRUE(clone.condenserRefrigerantOperatingChargeInventory());
  EXPECT_DOUBLE_EQ(1.5, clone.condenserRefrigerantOperatingChargeInventory().get());
  ASSERT_TRUE(clone.condensateReceiverRefrigerantInventory());
  EXPECT_DOUBLE_EQ(0.25, clone.condensateReceiverRefrigerantInventory().get());
  ASSERT_TRUE(clone.condensatePipingRefrigerantInventory());
  EXPECT_DOUBLE_EQ(0.1, clone.condensatePipingRefrigerantInventory().get());
}

TEST_F(EPModelFixture, RefrigerationCondenserWaterCooled_AddToNode_PlantDemandOnlyAndReattach) {
  Model model;
  RefrigerationCondenserWaterCooled rejectedCondenser(model);

  AirLoopHVAC airLoop(model);
  Node airSupplyOutletNode = airLoop.supplyOutletNode();
  const auto initialAirSupplyCount = airLoop.supplyComponents().size();
  EXPECT_FALSE(rejectedCondenser.addToNode(airSupplyOutletNode));
  EXPECT_EQ(initialAirSupplyCount, airLoop.supplyComponents().size());

  Node airDemandNode = airLoop.zoneSplitter().lastOutletModelObject()->cast<Node>();
  const auto initialAirDemandCount = airLoop.demandComponents().size();
  EXPECT_FALSE(rejectedCondenser.addToNode(airDemandNode));
  EXPECT_EQ(initialAirDemandCount, airLoop.demandComponents().size());

  PlantLoop plantLoop(model);
  Node plantSupplyOutletNode = plantLoop.supplyOutletNode();
  const auto initialPlantSupplyCount = plantLoop.supplyComponents().size();
  EXPECT_FALSE(rejectedCondenser.addToNode(plantSupplyOutletNode));
  EXPECT_EQ(initialPlantSupplyCount, plantLoop.supplyComponents().size());

  Node unconnectedNode = model.getOrCreateTransientByName<Node>("Unconnected RefrigerationCondenserWaterCooled Node");
  EXPECT_FALSE(rejectedCondenser.addToNode(unconnectedNode));
  EXPECT_FALSE(rejectedCondenser.loop());
  EXPECT_FALSE(rejectedCondenser.inletModelObject());
  EXPECT_FALSE(rejectedCondenser.outletModelObject());

  RefrigerationCondenserWaterCooled condenser(model);
  Node plantDemandOutletNode = plantLoop.demandOutletNode();
  const auto initialPlantDemandCount = plantLoop.demandComponents().size();
  EXPECT_TRUE(condenser.addToNode(plantDemandOutletNode));
  EXPECT_GT(plantLoop.demandComponents().size(), initialPlantDemandCount);
  ASSERT_TRUE(condenser.plantLoop());
  EXPECT_EQ(plantLoop.handle(), condenser.plantLoop()->handle());
  ASSERT_TRUE(condenser.inletModelObject());
  ASSERT_TRUE(condenser.outletModelObject());

  auto inletNode = condenser.getModelObjectTarget<Node>(openstudio::Refrigeration_Condenser_WaterCooledFields::WaterInletNodeName);
  auto outletNode = condenser.getModelObjectTarget<Node>(openstudio::Refrigeration_Condenser_WaterCooledFields::WaterOutletNodeName);
  ASSERT_TRUE(inletNode);
  ASSERT_TRUE(outletNode);
  EXPECT_EQ(condenser.inletModelObject()->handle(), inletNode->handle());
  EXPECT_EQ(condenser.outletModelObject()->handle(), outletNode->handle());

  condenser.disconnect();
  EXPECT_FALSE(condenser.plantLoop());
  EXPECT_FALSE(condenser.inletModelObject());
  EXPECT_FALSE(condenser.outletModelObject());

  plantDemandOutletNode = plantLoop.demandOutletNode();
  EXPECT_TRUE(condenser.addToNode(plantDemandOutletNode));

  PlantLoop secondPlantLoop(model);
  Node plantDemandInletNode = secondPlantLoop.demandInletNode();
  condenser.disconnect();
  EXPECT_TRUE(condenser.addToNode(plantDemandInletNode));
  ASSERT_TRUE(condenser.plantLoop());
  EXPECT_EQ(secondPlantLoop.handle(), condenser.plantLoop()->handle());

  RefrigerationCondenserWaterCooled branchManagedCondenser(model);
  EXPECT_TRUE(secondPlantLoop.addDemandBranchForComponent(branchManagedCondenser));
  ASSERT_TRUE(branchManagedCondenser.plantLoop());
  EXPECT_TRUE(secondPlantLoop.removeDemandBranchWithComponent(branchManagedCondenser));
  EXPECT_FALSE(branchManagedCondenser.plantLoop());
  EXPECT_FALSE(branchManagedCondenser.inletModelObject());
  EXPECT_FALSE(branchManagedCondenser.outletModelObject());

  auto cloneObject = model.addObject(branchManagedCondenser.idfObject());
  ASSERT_TRUE(cloneObject);
  auto clone = cloneObject->cast<RefrigerationCondenserWaterCooled>();
  EXPECT_TRUE(secondPlantLoop.addDemandBranchForComponent(clone));
  EXPECT_EQ(2u, secondPlantLoop.demandComponents(RefrigerationCondenserWaterCooled::iddObjectType()).size());
}

TEST_F(EPModelFixture, RefrigerationCondenserWaterCooled_Remove_PreservesReferencedSchedule) {
  Model model;
  RefrigerationCondenserWaterCooled condenser(model);
  ScheduleConstant outletTemperatureSchedule(model);

  ASSERT_TRUE(outletTemperatureSchedule.setValue(31.0));
  ASSERT_TRUE(condenser.setWaterOutletTemperatureSchedule(outletTemperatureSchedule));
  EXPECT_EQ(1u, model.getConcreteModelObjects<RefrigerationCondenserWaterCooled>().size());
  EXPECT_EQ(1u, model.getModelObjects<Schedule>().size());

  condenser.remove();

  EXPECT_TRUE(model.getConcreteModelObjects<RefrigerationCondenserWaterCooled>().empty());
  EXPECT_EQ(1u, model.getModelObjects<Schedule>().size());
}
