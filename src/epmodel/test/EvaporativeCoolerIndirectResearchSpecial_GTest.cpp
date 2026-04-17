/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../Curve/CurveLinear.hpp"
#include "../HVACComponent/AirLoopHVACOutdoorAirSystem.hpp"
#include "../Loop/AirLoopHVAC.hpp"
#include "../Loop/PlantLoop.hpp"
#include "../ResourceObject/ScheduleTypeLimits.hpp"
#include "../Schedule/Schedule.hpp"
#include "../Schedule/Schedule_Impl.hpp"
#include "../Schedule/ScheduleCompact.hpp"
#include "../Schedule/ScheduleConstant.hpp"
#include "../Splitter/AirLoopHVACZoneSplitter.hpp"
#include "../StraightComponent/EvaporativeCoolerIndirectResearchSpecial.hpp"
#include "../StraightComponent/EvaporativeCoolerIndirectResearchSpecial_Impl.hpp"
#include "../StraightComponent/Node.hpp"

#include <utilities/idd/EvaporativeCooler_Indirect_ResearchSpecial_FieldEnums.hxx>

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, EvaporativeCoolerIndirectResearchSpecial_DefaultConstructor) {
  Model model;
  EvaporativeCoolerIndirectResearchSpecial evaporativeCooler(model);

  EXPECT_EQ(EvaporativeCoolerIndirectResearchSpecial::iddObjectType(), evaporativeCooler.iddObject().type());
  EXPECT_FALSE(evaporativeCooler.nameString().empty());
  EXPECT_FALSE(evaporativeCooler.availabilitySchedule());

  EXPECT_DOUBLE_EQ(0.75, evaporativeCooler.coolerMaximumEffectiveness());
  ASSERT_TRUE(evaporativeCooler.recirculatingWaterPumpPowerConsumption());
  EXPECT_DOUBLE_EQ(30.0, evaporativeCooler.recirculatingWaterPumpPowerConsumption().get());
  EXPECT_FALSE(evaporativeCooler.isRecirculatingWaterPumpPowerConsumptionAutosized());

  EXPECT_DOUBLE_EQ(0.6, evaporativeCooler.secondaryFanTotalEfficiency());
  EXPECT_DOUBLE_EQ(124.6, evaporativeCooler.secondaryFanDeltaPressure());
  ASSERT_TRUE(evaporativeCooler.driftLossFraction());
  EXPECT_DOUBLE_EQ(0.0, evaporativeCooler.driftLossFraction().get());
  EXPECT_FALSE(evaporativeCooler.blowdownConcentrationRatio());
  EXPECT_FALSE(evaporativeCooler.wetbulbEffectivenessFlowRatioModifierCurve());
  EXPECT_FALSE(evaporativeCooler.drybulbEffectivenessFlowRatioModifierCurve());
  EXPECT_FALSE(evaporativeCooler.waterPumpPowerModifierCurve());
  EXPECT_FALSE(evaporativeCooler.secondaryAirFanPowerModifierCurve());

  EXPECT_DOUBLE_EQ(0.1, evaporativeCooler.waterPumpPowerSizingFactor());
  EXPECT_DOUBLE_EQ(1.0, evaporativeCooler.secondaryAirFlowScalingFactor());
}

TEST_F(EPModelFixture, EvaporativeCoolerIndirectResearchSpecial_RelationshipAndScalarAccessors_RoundTrip) {
  Model model;
  EvaporativeCoolerIndirectResearchSpecial evaporativeCooler(model);
  ScheduleCompact compactSchedule(model);
  ScheduleConstant continuousAvailabilitySchedule(model);
  ScheduleConstant wrongSchedule(model);
  ScheduleTypeLimits continuousAvailabilityLimits(model);
  ScheduleTypeLimits temperatureLimits(model);
  CurveLinear wetbulbCurve(model);
  CurveLinear drybulbCurve(model);
  CurveLinear waterPumpCurve(model);
  CurveLinear secondaryAirFanCurve(model);
  Node reliefAirInletNode(model);

  ASSERT_TRUE(compactSchedule.setToConstantValue(0.5));
  EXPECT_TRUE(evaporativeCooler.setAvailabilitySchedule(compactSchedule));
  ASSERT_TRUE(evaporativeCooler.availabilitySchedule());
  EXPECT_EQ(compactSchedule.cast<ModelObject>(), evaporativeCooler.availabilitySchedule()->cast<ModelObject>());
  ASSERT_TRUE(compactSchedule.scheduleTypeLimits());
  EXPECT_EQ("Availability", compactSchedule.scheduleTypeLimits()->unitType());

  ASSERT_TRUE(continuousAvailabilitySchedule.setValue(1.0));
  ASSERT_TRUE(continuousAvailabilityLimits.setUnitType("Availability"));
  ASSERT_TRUE(continuousAvailabilityLimits.setNumericType("Continuous"));
  ASSERT_TRUE(continuousAvailabilityLimits.setLowerLimitValue(0.0));
  ASSERT_TRUE(continuousAvailabilityLimits.setUpperLimitValue(1.0));
  ASSERT_TRUE(continuousAvailabilitySchedule.setScheduleTypeLimits(continuousAvailabilityLimits));
  EXPECT_TRUE(evaporativeCooler.setAvailabilitySchedule(continuousAvailabilitySchedule));
  ASSERT_TRUE(evaporativeCooler.availabilitySchedule());
  EXPECT_EQ(continuousAvailabilitySchedule.cast<ModelObject>(), evaporativeCooler.availabilitySchedule()->cast<ModelObject>());

  ASSERT_TRUE(wrongSchedule.setValue(20.0));
  ASSERT_TRUE(temperatureLimits.setUnitType("Temperature"));
  ASSERT_TRUE(wrongSchedule.setScheduleTypeLimits(temperatureLimits));
  EXPECT_FALSE(evaporativeCooler.setAvailabilitySchedule(wrongSchedule));
  ASSERT_TRUE(evaporativeCooler.availabilitySchedule());
  EXPECT_EQ(continuousAvailabilitySchedule.cast<ModelObject>(), evaporativeCooler.availabilitySchedule()->cast<ModelObject>());

  evaporativeCooler.resetAvailabilitySchedule();
  EXPECT_FALSE(evaporativeCooler.availabilitySchedule());

  auto evaporativeCoolerImpl = evaporativeCooler.getImpl<detail::EvaporativeCoolerIndirectResearchSpecial_Impl>();
  ASSERT_TRUE(evaporativeCoolerImpl->setReliefAirInletNode(reliefAirInletNode));
  ASSERT_TRUE(evaporativeCoolerImpl->reliefAirInletNode());
  EXPECT_EQ(reliefAirInletNode.handle(), evaporativeCoolerImpl->reliefAirInletNode()->handle());

  EXPECT_TRUE(evaporativeCooler.setCoolerMaximumEffectiveness(0.81));
  EXPECT_DOUBLE_EQ(0.81, evaporativeCooler.coolerMaximumEffectiveness());

  EXPECT_TRUE(evaporativeCooler.setRecirculatingWaterPumpPowerConsumption(225.0));
  ASSERT_TRUE(evaporativeCooler.recirculatingWaterPumpPowerConsumption());
  EXPECT_DOUBLE_EQ(225.0, evaporativeCooler.recirculatingWaterPumpPowerConsumption().get());
  EXPECT_FALSE(evaporativeCooler.isRecirculatingWaterPumpPowerConsumptionAutosized());

  evaporativeCooler.autosizeRecirculatingWaterPumpPowerConsumption();
  EXPECT_TRUE(evaporativeCooler.isRecirculatingWaterPumpPowerConsumptionAutosized());
  EXPECT_FALSE(evaporativeCooler.recirculatingWaterPumpPowerConsumption());

  EXPECT_TRUE(evaporativeCooler.setSecondaryFanFlowRate(1.9));
  ASSERT_TRUE(evaporativeCooler.secondaryFanFlowRate());
  EXPECT_DOUBLE_EQ(1.9, evaporativeCooler.secondaryFanFlowRate().get());
  EXPECT_FALSE(evaporativeCooler.isSecondaryFanFlowRateAutosized());

  evaporativeCooler.resetSecondaryFanFlowRate();
  EXPECT_FALSE(evaporativeCooler.secondaryFanFlowRate());

  evaporativeCooler.autosizeSecondaryFanFlowRate();
  EXPECT_TRUE(evaporativeCooler.isSecondaryFanFlowRateAutosized());
  EXPECT_FALSE(evaporativeCooler.secondaryFanFlowRate());

  EXPECT_TRUE(evaporativeCooler.setSecondaryFanTotalEfficiency(0.64));
  EXPECT_TRUE(evaporativeCooler.setSecondaryFanDeltaPressure(140.0));
  EXPECT_DOUBLE_EQ(0.64, evaporativeCooler.secondaryFanTotalEfficiency());
  EXPECT_DOUBLE_EQ(140.0, evaporativeCooler.secondaryFanDeltaPressure());

  const double specificPower = evaporativeCooler.secondaryFanDeltaPressure() / evaporativeCooler.secondaryFanTotalEfficiency();
  auto cloneObject = model.addObject(evaporativeCooler.idfObject());
  ASSERT_TRUE(cloneObject);
  auto clone = cloneObject->cast<EvaporativeCoolerIndirectResearchSpecial>();
  EXPECT_GT(clone.secondaryFanTotalEfficiency(), 0.0);
  EXPECT_DOUBLE_EQ(specificPower, clone.secondaryFanDeltaPressure() / clone.secondaryFanTotalEfficiency());

  EXPECT_TRUE(evaporativeCooler.setDewpointEffectivenessFactor(0.87));
  EXPECT_DOUBLE_EQ(0.87, evaporativeCooler.dewpointEffectivenessFactor());

  EXPECT_TRUE(evaporativeCooler.setDriftLossFraction(0.003));
  ASSERT_TRUE(evaporativeCooler.driftLossFraction());
  EXPECT_DOUBLE_EQ(0.003, evaporativeCooler.driftLossFraction().get());
  evaporativeCooler.resetDriftLossFraction();
  EXPECT_FALSE(evaporativeCooler.driftLossFraction());

  EXPECT_TRUE(evaporativeCooler.setBlowdownConcentrationRatio(3.2));
  ASSERT_TRUE(evaporativeCooler.blowdownConcentrationRatio());
  EXPECT_DOUBLE_EQ(3.2, evaporativeCooler.blowdownConcentrationRatio().get());
  evaporativeCooler.resetBlowdownConcentrationRatio();
  EXPECT_FALSE(evaporativeCooler.blowdownConcentrationRatio());

  EXPECT_TRUE(evaporativeCooler.setWetbulbEffectivenessFlowRatioModifierCurve(wetbulbCurve));
  ASSERT_TRUE(evaporativeCooler.wetbulbEffectivenessFlowRatioModifierCurve());
  EXPECT_EQ(wetbulbCurve.handle(), evaporativeCooler.wetbulbEffectivenessFlowRatioModifierCurve()->handle());
  evaporativeCooler.resetWetbulbEffectivenessFlowRatioModifierCurve();
  EXPECT_FALSE(evaporativeCooler.wetbulbEffectivenessFlowRatioModifierCurve());

  EXPECT_TRUE(evaporativeCooler.setCoolerDrybulbDesignEffectiveness(0.59));
  ASSERT_TRUE(evaporativeCooler.coolerDrybulbDesignEffectiveness());
  EXPECT_DOUBLE_EQ(0.59, evaporativeCooler.coolerDrybulbDesignEffectiveness().get());
  evaporativeCooler.resetCoolerDrybulbDesignEffectiveness();
  EXPECT_FALSE(evaporativeCooler.coolerDrybulbDesignEffectiveness());

  EXPECT_TRUE(evaporativeCooler.setDrybulbEffectivenessFlowRatioModifierCurve(drybulbCurve));
  ASSERT_TRUE(evaporativeCooler.drybulbEffectivenessFlowRatioModifierCurve());
  EXPECT_EQ(drybulbCurve.handle(), evaporativeCooler.drybulbEffectivenessFlowRatioModifierCurve()->handle());
  evaporativeCooler.resetDrybulbEffectivenessFlowRatioModifierCurve();
  EXPECT_FALSE(evaporativeCooler.drybulbEffectivenessFlowRatioModifierCurve());

  EXPECT_TRUE(evaporativeCooler.setWaterPumpPowerSizingFactor(0.19));
  EXPECT_DOUBLE_EQ(0.19, evaporativeCooler.waterPumpPowerSizingFactor());

  EXPECT_TRUE(evaporativeCooler.setWaterPumpPowerModifierCurve(waterPumpCurve));
  ASSERT_TRUE(evaporativeCooler.waterPumpPowerModifierCurve());
  EXPECT_EQ(waterPumpCurve.handle(), evaporativeCooler.waterPumpPowerModifierCurve()->handle());
  evaporativeCooler.resetWaterPumpPowerModifierCurve();
  EXPECT_FALSE(evaporativeCooler.waterPumpPowerModifierCurve());

  EXPECT_TRUE(evaporativeCooler.setSecondaryAirFlowScalingFactor(1.15));
  EXPECT_DOUBLE_EQ(1.15, evaporativeCooler.secondaryAirFlowScalingFactor());

  EXPECT_TRUE(evaporativeCooler.setSecondaryAirFanDesignPower(560.0));
  ASSERT_TRUE(evaporativeCooler.secondaryAirFanDesignPower());
  EXPECT_DOUBLE_EQ(560.0, evaporativeCooler.secondaryAirFanDesignPower().get());
  EXPECT_FALSE(evaporativeCooler.isSecondaryAirFanDesignPowerAutosized());

  evaporativeCooler.autosizeSecondaryAirFanDesignPower();
  EXPECT_TRUE(evaporativeCooler.isSecondaryAirFanDesignPowerAutosized());
  EXPECT_FALSE(evaporativeCooler.secondaryAirFanDesignPower());

  EXPECT_TRUE(evaporativeCooler.setSecondaryAirFanPowerModifierCurve(secondaryAirFanCurve));
  ASSERT_TRUE(evaporativeCooler.secondaryAirFanPowerModifierCurve());
  EXPECT_EQ(secondaryAirFanCurve.handle(), evaporativeCooler.secondaryAirFanPowerModifierCurve()->handle());
  evaporativeCooler.resetSecondaryAirFanPowerModifierCurve();
  EXPECT_FALSE(evaporativeCooler.secondaryAirFanPowerModifierCurve());

  EXPECT_TRUE(evaporativeCooler.setPrimaryDesignAirFlowRate(1.25));
  ASSERT_TRUE(evaporativeCooler.primaryDesignAirFlowRate());
  EXPECT_DOUBLE_EQ(1.25, evaporativeCooler.primaryDesignAirFlowRate().get());
  EXPECT_FALSE(evaporativeCooler.isPrimaryDesignAirFlowRateAutosized());

  evaporativeCooler.resetPrimaryDesignAirFlowRate();
  EXPECT_FALSE(evaporativeCooler.primaryDesignAirFlowRate());

  evaporativeCooler.autosizePrimaryDesignAirFlowRate();
  EXPECT_TRUE(evaporativeCooler.isPrimaryDesignAirFlowRateAutosized());
  EXPECT_FALSE(evaporativeCooler.primaryDesignAirFlowRate());

  EXPECT_FALSE(evaporativeCooler.autosizedRecirculatingWaterPumpPowerConsumption());
  EXPECT_FALSE(evaporativeCooler.autosizedSecondaryFanFlowRate());
  EXPECT_FALSE(evaporativeCooler.autosizedSecondaryAirFanDesignPower());
  EXPECT_FALSE(evaporativeCooler.autosizedPrimaryDesignAirFlowRate());
}

TEST_F(EPModelFixture, EvaporativeCoolerIndirectResearchSpecial_AddToSupplyNodeSetsSensorNode) {
  Model model;
  AirLoopHVAC airLoop(model);
  EvaporativeCoolerIndirectResearchSpecial evaporativeCooler(model);

  auto supplyInletNode = airLoop.supplyInletNode();
  EXPECT_TRUE(evaporativeCooler.addToNode(supplyInletNode));
  EXPECT_TRUE(evaporativeCooler.airLoopHVAC());
  ASSERT_TRUE(evaporativeCooler.inletModelObject());
  EXPECT_EQ(supplyInletNode, evaporativeCooler.inletModelObject()->cast<Node>());

  auto outletObject = evaporativeCooler.outletModelObject();
  ASSERT_TRUE(outletObject);
  auto outletNode = outletObject->optionalCast<Node>();
  ASSERT_TRUE(outletNode);

  auto sensorNode = evaporativeCooler.getModelObjectTarget<Node>(openstudio::EvaporativeCooler_Indirect_ResearchSpecialFields::SensorNodeName);
  ASSERT_TRUE(sensorNode);
  EXPECT_EQ(outletNode->handle(), sensorNode->handle());
}

TEST_F(EPModelFixture, EvaporativeCoolerIndirectResearchSpecial_AddToDemandAndPlantNodesRejected) {
  Model model;
  AirLoopHVAC airLoop(model);
  EvaporativeCoolerIndirectResearchSpecial demandCooler(model);

  auto branchObject = airLoop.zoneSplitter().lastOutletModelObject();
  ASSERT_TRUE(branchObject);
  auto branchNode = branchObject->optionalCast<Node>();
  ASSERT_TRUE(branchNode);

  EXPECT_FALSE(demandCooler.addToNode(*branchNode));
  EXPECT_FALSE(demandCooler.airLoopHVAC());

  PlantLoop plant(model);
  EvaporativeCoolerIndirectResearchSpecial plantCooler(model);
  auto plantSupplyOutletNode = plant.supplyOutletNode();
  EXPECT_FALSE(plantCooler.addToNode(plantSupplyOutletNode));
}

TEST_F(EPModelFixture, EvaporativeCoolerIndirectResearchSpecial_AddToNodeSupportsOutboardOANode) {
  Model model;
  AirLoopHVAC airLoop(model);
  AirLoopHVACOutdoorAirSystem oaSystem(model);
  auto supplyInletNode = airLoop.supplyInletNode();
  ASSERT_TRUE(oaSystem.addToNode(supplyInletNode));

  auto outboardOANode = oaSystem.outboardOANode();
  ASSERT_TRUE(outboardOANode);

  EvaporativeCoolerIndirectResearchSpecial evaporativeCooler(model);
  EXPECT_TRUE(evaporativeCooler.addToNode(*outboardOANode));
  EXPECT_EQ(3u, oaSystem.oaComponents().size());

  auto outletObject = evaporativeCooler.outletModelObject();
  ASSERT_TRUE(outletObject);
  auto outletNode = outletObject->optionalCast<Node>();
  ASSERT_TRUE(outletNode);

  auto sensorNode = evaporativeCooler.getModelObjectTarget<Node>(openstudio::EvaporativeCooler_Indirect_ResearchSpecialFields::SensorNodeName);
  ASSERT_TRUE(sensorNode);
  EXPECT_EQ(outletNode->handle(), sensorNode->handle());
}
