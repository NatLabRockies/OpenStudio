/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include <utilities/idd/LoadProfile_Plant_FieldEnums.hxx>
#include <utilities/idf/IdfExtensibleGroup.hpp>

#include "EPModelFixture.hpp"
#include "../Loop/AirLoopHVAC.hpp"
#include "../Loop/PlantLoop.hpp"
#include "../ResourceObject/ScheduleTypeLimits.hpp"
#include "../Schedule/Schedule.hpp"
#include "../Schedule/Schedule_Impl.hpp"
#include "../Schedule/ScheduleCompact.hpp"
#include "../Schedule/ScheduleCompact_Impl.hpp"
#include "../Schedule/ScheduleConstant.hpp"
#include "../Splitter/AirLoopHVACZoneSplitter.hpp"
#include "../StraightComponent/LoadProfilePlant.hpp"
#include "../StraightComponent/LoadProfilePlant_Impl.hpp"
#include "../StraightComponent/Node.hpp"

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, LoadProfilePlant_DefaultConstructor) {
  Model model;
  LoadProfilePlant loadProfilePlant(model);
  EXPECT_EQ(LoadProfilePlant::iddObjectType(), loadProfilePlant.iddObject().type());
  EXPECT_FALSE(loadProfilePlant.nameString().empty());

  auto loadSchedule = loadProfilePlant.loadSchedule();
  auto loadScheduleCompact = loadSchedule.optionalCast<ScheduleCompact>();
  ASSERT_TRUE(loadScheduleCompact);
  ASSERT_TRUE(loadSchedule.scheduleTypeLimits());
  auto loadNumericType = loadSchedule.scheduleTypeLimits()->numericType();
  ASSERT_TRUE(loadNumericType);
  EXPECT_EQ("Continuous", *loadNumericType);

  const auto scheduleData = loadScheduleCompact->extensibleGroups();
  ASSERT_EQ(12u, scheduleData.size());
  ASSERT_TRUE(scheduleData[0].getString(0u, false));
  EXPECT_EQ("Through: 12/31", scheduleData[0].getString(0u, false).get());
  ASSERT_TRUE(scheduleData[1].getString(0u, false));
  EXPECT_EQ("For: AllDays", scheduleData[1].getString(0u, false).get());
  ASSERT_TRUE(scheduleData[3].getDouble(0u));
  EXPECT_DOUBLE_EQ(8000.0, scheduleData[3].getDouble(0u).get());
  ASSERT_TRUE(scheduleData[5].getDouble(0u));
  EXPECT_DOUBLE_EQ(6000.0, scheduleData[5].getDouble(0u).get());
  ASSERT_TRUE(scheduleData[7].getDouble(0u));
  EXPECT_DOUBLE_EQ(0.0, scheduleData[7].getDouble(0u).get());
  ASSERT_TRUE(scheduleData[9].getDouble(0u));
  EXPECT_DOUBLE_EQ(6000.0, scheduleData[9].getDouble(0u).get());
  ASSERT_TRUE(scheduleData[11].getDouble(0u));
  EXPECT_DOUBLE_EQ(10000.0, scheduleData[11].getDouble(0u).get());

  EXPECT_DOUBLE_EQ(0.002, loadProfilePlant.peakFlowRate());
  EXPECT_EQ(model.alwaysOnDiscreteSchedule().handle(), loadProfilePlant.flowRateFractionSchedule().handle());
  EXPECT_EQ("Water", loadProfilePlant.plantLoopFluidType());
  EXPECT_DOUBLE_EQ(5.0, loadProfilePlant.degreeofSubCooling());
  EXPECT_DOUBLE_EQ(20.0, loadProfilePlant.degreeofLoopSubCooling());

  auto storedLoadSchedule = loadProfilePlant.getModelObjectTarget<Schedule>(openstudio::LoadProfile_PlantFields::LoadScheduleName);
  ASSERT_TRUE(storedLoadSchedule);
  EXPECT_EQ(loadSchedule.handle(), storedLoadSchedule->handle());

  auto storedFlowSchedule = loadProfilePlant.getModelObjectTarget<Schedule>(openstudio::LoadProfile_PlantFields::FlowRateFractionScheduleName);
  ASSERT_TRUE(storedFlowSchedule);
  EXPECT_EQ(loadProfilePlant.flowRateFractionSchedule().handle(), storedFlowSchedule->handle());
}

TEST_F(EPModelFixture, LoadProfilePlant_ScheduleAndScalarAccessors_RoundTrip) {
  Model model;
  ScheduleConstant loadSchedule(model);
  ASSERT_TRUE(loadSchedule.setValue(9000.0));
  ScheduleConstant flowRateFractionSchedule(model);
  ASSERT_TRUE(flowRateFractionSchedule.setValue(0.75));

  LoadProfilePlant loadProfilePlant(model, loadSchedule, flowRateFractionSchedule);
  EXPECT_EQ(loadSchedule.handle(), loadProfilePlant.loadSchedule().handle());
  EXPECT_EQ(flowRateFractionSchedule.handle(), loadProfilePlant.flowRateFractionSchedule().handle());

  ASSERT_TRUE(loadSchedule.scheduleTypeLimits());
  auto loadNumericType = loadSchedule.scheduleTypeLimits()->numericType();
  ASSERT_TRUE(loadNumericType);
  EXPECT_EQ("Continuous", *loadNumericType);

  ASSERT_TRUE(flowRateFractionSchedule.scheduleTypeLimits());
  auto flowNumericType = flowRateFractionSchedule.scheduleTypeLimits()->numericType();
  ASSERT_TRUE(flowNumericType);
  EXPECT_EQ("Continuous", *flowNumericType);
  ASSERT_TRUE(flowRateFractionSchedule.scheduleTypeLimits()->lowerLimitValue());
  EXPECT_DOUBLE_EQ(0.0, flowRateFractionSchedule.scheduleTypeLimits()->lowerLimitValue().get());
  ASSERT_TRUE(flowRateFractionSchedule.scheduleTypeLimits()->upperLimitValue());
  EXPECT_DOUBLE_EQ(1.0, flowRateFractionSchedule.scheduleTypeLimits()->upperLimitValue().get());

  ScheduleCompact replacementLoadSchedule(model, 12000.0);
  EXPECT_TRUE(loadProfilePlant.setLoadSchedule(replacementLoadSchedule));
  EXPECT_EQ(replacementLoadSchedule.handle(), loadProfilePlant.loadSchedule().handle());

  ScheduleConstant replacementFlowSchedule(model);
  ASSERT_TRUE(replacementFlowSchedule.setValue(0.25));
  EXPECT_TRUE(loadProfilePlant.setFlowRateFractionSchedule(replacementFlowSchedule));
  EXPECT_EQ(replacementFlowSchedule.handle(), loadProfilePlant.flowRateFractionSchedule().handle());

  EXPECT_TRUE(loadProfilePlant.setPeakFlowRate(0.005));
  EXPECT_DOUBLE_EQ(0.005, loadProfilePlant.peakFlowRate());
  EXPECT_EQ(std::vector<std::string>({"Water", "Steam"}), LoadProfilePlant::plantLoopFluidTypeValues());
  EXPECT_TRUE(loadProfilePlant.setPlantLoopFluidType("Steam"));
  EXPECT_EQ("Steam", loadProfilePlant.plantLoopFluidType());
  EXPECT_FALSE(loadProfilePlant.isPlantLoopFluidTypeDefaulted());
  loadProfilePlant.resetPlantLoopFluidType();
  EXPECT_TRUE(loadProfilePlant.isPlantLoopFluidTypeDefaulted());
  EXPECT_EQ("Water", loadProfilePlant.plantLoopFluidType());

  EXPECT_TRUE(loadProfilePlant.setDegreeofSubCooling(6.0));
  EXPECT_DOUBLE_EQ(6.0, loadProfilePlant.degreeofSubCooling());
  EXPECT_FALSE(loadProfilePlant.isDegreeofSubCoolingDefaulted());
  EXPECT_FALSE(loadProfilePlant.setDegreeofSubCooling(0.5));
  loadProfilePlant.resetDegreeofSubCooling();
  EXPECT_TRUE(loadProfilePlant.isDegreeofSubCoolingDefaulted());
  EXPECT_DOUBLE_EQ(5.0, loadProfilePlant.degreeofSubCooling());

  EXPECT_TRUE(loadProfilePlant.setDegreeofLoopSubCooling(21.0));
  EXPECT_DOUBLE_EQ(21.0, loadProfilePlant.degreeofLoopSubCooling());
  EXPECT_FALSE(loadProfilePlant.isDegreeofLoopSubCoolingDefaulted());
  EXPECT_FALSE(loadProfilePlant.setDegreeofLoopSubCooling(5.0));
  loadProfilePlant.resetDegreeofLoopSubCooling();
  EXPECT_TRUE(loadProfilePlant.isDegreeofLoopSubCoolingDefaulted());
  EXPECT_DOUBLE_EQ(20.0, loadProfilePlant.degreeofLoopSubCooling());

  auto loadProfilePlantCloneObject = model.addObject(loadProfilePlant.idfObject());
  ASSERT_TRUE(loadProfilePlantCloneObject);
  auto loadProfilePlantClone = loadProfilePlantCloneObject->cast<LoadProfilePlant>();
  EXPECT_EQ(replacementLoadSchedule.handle(), loadProfilePlantClone.loadSchedule().handle());
  EXPECT_EQ(replacementFlowSchedule.handle(), loadProfilePlantClone.flowRateFractionSchedule().handle());
  EXPECT_DOUBLE_EQ(0.005, loadProfilePlantClone.peakFlowRate());
  EXPECT_EQ("Water", loadProfilePlantClone.plantLoopFluidType());
  EXPECT_DOUBLE_EQ(5.0, loadProfilePlantClone.degreeofSubCooling());
  EXPECT_DOUBLE_EQ(20.0, loadProfilePlantClone.degreeofLoopSubCooling());
}

TEST_F(EPModelFixture, LoadProfilePlant_ScheduleRelationships_MatchCanonicalCompatibility) {
  Model model;
  LoadProfilePlant loadProfilePlant(model);

  ScheduleConstant discreteLoadSchedule(model);
  ASSERT_TRUE(discreteLoadSchedule.setValue(1.0));
  ScheduleTypeLimits discreteLimits(model);
  ASSERT_TRUE(discreteLimits.setNumericType("Discrete"));
  ASSERT_TRUE(discreteLoadSchedule.setScheduleTypeLimits(discreteLimits));

  EXPECT_TRUE(loadProfilePlant.setLoadSchedule(discreteLoadSchedule));
  EXPECT_EQ(discreteLoadSchedule.handle(), loadProfilePlant.loadSchedule().handle());

  ScheduleConstant temperatureLoadSchedule(model);
  ASSERT_TRUE(temperatureLoadSchedule.setValue(1.0));
  ScheduleTypeLimits temperatureLoadLimits(model);
  ASSERT_TRUE(temperatureLoadLimits.setUnitType("Temperature"));
  ASSERT_TRUE(temperatureLoadSchedule.setScheduleTypeLimits(temperatureLoadLimits));

  const auto originalLoadSchedule = loadProfilePlant.loadSchedule();
  EXPECT_FALSE(loadProfilePlant.setLoadSchedule(temperatureLoadSchedule));
  EXPECT_EQ(originalLoadSchedule.handle(), loadProfilePlant.loadSchedule().handle());

  auto discreteFlowSchedule = model.alwaysOnDiscreteSchedule();
  EXPECT_TRUE(loadProfilePlant.setFlowRateFractionSchedule(discreteFlowSchedule));
  EXPECT_EQ(discreteFlowSchedule.handle(), loadProfilePlant.flowRateFractionSchedule().handle());

  ScheduleConstant temperatureFlowSchedule(model);
  ASSERT_TRUE(temperatureFlowSchedule.setValue(1.0));
  ScheduleTypeLimits temperatureLimits(model);
  ASSERT_TRUE(temperatureLimits.setUnitType("Temperature"));
  ASSERT_TRUE(temperatureFlowSchedule.setScheduleTypeLimits(temperatureLimits));

  const auto originalFlowSchedule = loadProfilePlant.flowRateFractionSchedule();
  EXPECT_FALSE(loadProfilePlant.setFlowRateFractionSchedule(temperatureFlowSchedule));
  EXPECT_EQ(originalFlowSchedule.handle(), loadProfilePlant.flowRateFractionSchedule().handle());
}

TEST_F(EPModelFixture, LoadProfilePlant_AddToNode_PlantDemandOnly) {
  Model model;
  LoadProfilePlant loadProfilePlant(model);

  AirLoopHVAC airLoop(model);
  Node airSupplyOutletNode = airLoop.supplyOutletNode();
  const auto initialAirSupplyCount = airLoop.supplyComponents().size();
  EXPECT_FALSE(loadProfilePlant.addToNode(airSupplyOutletNode));
  EXPECT_EQ(initialAirSupplyCount, airLoop.supplyComponents().size());

  Node airDemandNode = airLoop.zoneSplitter().lastOutletModelObject()->cast<Node>();
  const auto initialAirDemandCount = airLoop.demandComponents().size();
  EXPECT_FALSE(loadProfilePlant.addToNode(airDemandNode));
  EXPECT_EQ(initialAirDemandCount, airLoop.demandComponents().size());

  PlantLoop plantLoop(model);
  Node supplyOutletNode = plantLoop.supplyOutletNode();
  const auto initialPlantSupplyCount = plantLoop.supplyComponents().size();
  EXPECT_FALSE(loadProfilePlant.addToNode(supplyOutletNode));
  EXPECT_EQ(initialPlantSupplyCount, plantLoop.supplyComponents().size());

  Node demandOutletNode = plantLoop.demandOutletNode();
  const auto initialPlantDemandCount = plantLoop.demandComponents().size();
  EXPECT_TRUE(loadProfilePlant.addToNode(demandOutletNode));
  EXPECT_GT(plantLoop.demandComponents().size(), initialPlantDemandCount);
  ASSERT_TRUE(loadProfilePlant.loop());
  ASSERT_TRUE(loadProfilePlant.inletModelObject());
  ASSERT_TRUE(loadProfilePlant.outletModelObject());
  EXPECT_TRUE(loadProfilePlant.isRemovable());

  auto inletNode = loadProfilePlant.getModelObjectTarget<Node>(openstudio::LoadProfile_PlantFields::InletNodeName);
  auto outletNode = loadProfilePlant.getModelObjectTarget<Node>(openstudio::LoadProfile_PlantFields::OutletNodeName);
  ASSERT_TRUE(inletNode);
  ASSERT_TRUE(outletNode);
  EXPECT_EQ(loadProfilePlant.inletModelObject()->handle(), inletNode->handle());
  EXPECT_EQ(loadProfilePlant.outletModelObject()->handle(), outletNode->handle());

  loadProfilePlant.disconnect();
  EXPECT_FALSE(loadProfilePlant.loop());
  EXPECT_FALSE(loadProfilePlant.inletModelObject());
  EXPECT_FALSE(loadProfilePlant.outletModelObject());

  demandOutletNode = plantLoop.demandOutletNode();
  EXPECT_TRUE(loadProfilePlant.addToNode(demandOutletNode));
  ASSERT_TRUE(loadProfilePlant.inletModelObject());
  ASSERT_TRUE(loadProfilePlant.outletModelObject());
}
