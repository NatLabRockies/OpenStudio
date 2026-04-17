/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../Curve/CurveLinear.hpp"
#include "../HVACComponent/AirLoopHVACOutdoorAirSystem.hpp"
#include "../Loop/AirLoopHVAC.hpp"
#include "../ResourceObject/ScheduleTypeLimits.hpp"
#include "../Schedule/ScheduleCompact.hpp"
#include "../Schedule/ScheduleConstant.hpp"
#include "../Schedule/Schedule.hpp"
#include "../Schedule/Schedule_Impl.hpp"
#include "../StraightComponent/EvaporativeCoolerDirectResearchSpecial.hpp"
#include "../StraightComponent/Node.hpp"
#include "../Splitter/AirLoopHVACZoneSplitter.hpp"

#include <utilities/idd/EvaporativeCooler_Direct_ResearchSpecial_FieldEnums.hxx>
#include <utilities/idf/Handle.hpp>

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, EvaporativeCoolerDirectResearchSpecial_DefaultConstructor) {
  Model model;
  EvaporativeCoolerDirectResearchSpecial evaporativeCooler(model);

  EXPECT_EQ(EvaporativeCoolerDirectResearchSpecial::iddObjectType(), evaporativeCooler.iddObject().type());
  EXPECT_FALSE(evaporativeCooler.nameString().empty());
  EXPECT_EQ(model.alwaysOnDiscreteSchedule().handle(), evaporativeCooler.availabilitySchedule().handle());
  EXPECT_EQ(model.alwaysOnDiscreteSchedule().handle(), evaporativeCooler.availableSchedule().handle());

  EXPECT_DOUBLE_EQ(1.0, evaporativeCooler.coolerDesignEffectiveness());
  ASSERT_TRUE(evaporativeCooler.recirculatingWaterPumpPowerConsumption());
  EXPECT_DOUBLE_EQ(0.0, evaporativeCooler.recirculatingWaterPumpPowerConsumption().get());
  EXPECT_FALSE(evaporativeCooler.isRecirculatingWaterPumpPowerConsumptionAutosized());
  EXPECT_FALSE(evaporativeCooler.primaryAirDesignFlowRate());
  EXPECT_FALSE(evaporativeCooler.isPrimaryAirDesignFlowRateAutosized());
  EXPECT_FALSE(evaporativeCooler.sensorNode());

  EXPECT_DOUBLE_EQ(0.0, evaporativeCooler.driftLossFraction());
  EXPECT_DOUBLE_EQ(2.0, evaporativeCooler.blowdownConcentrationRatio());
  EXPECT_FALSE(evaporativeCooler.effectivenessFlowRatioModifierCurve());
  EXPECT_DOUBLE_EQ(0.1, evaporativeCooler.waterPumpPowerSizingFactor());
  EXPECT_FALSE(evaporativeCooler.waterPumpPowerModifierCurve());
  EXPECT_DOUBLE_EQ(16.0, evaporativeCooler.evaporativeOperationMinimumDrybulbTemperature());
  EXPECT_DOUBLE_EQ(24.0, evaporativeCooler.evaporativeOperationMaximumLimitWetbulbTemperature());
  EXPECT_DOUBLE_EQ(28.0, evaporativeCooler.evaporativeOperationMaximumLimitDrybulbTemperature());
}

TEST_F(EPModelFixture, EvaporativeCoolerDirectResearchSpecial_ScalarAccessors_RoundTrip) {
  Model model;
  EvaporativeCoolerDirectResearchSpecial evaporativeCooler(model);
  ScheduleConstant availabilitySchedule(model);
  CurveLinear effectivenessCurve(model);
  CurveLinear waterPumpCurve(model);
  Node sensorNode(model);

  EXPECT_TRUE(evaporativeCooler.setAvailabilitySchedule(availabilitySchedule));
  EXPECT_EQ(availabilitySchedule.handle(), evaporativeCooler.availabilitySchedule().handle());
  EXPECT_EQ(availabilitySchedule.handle(), evaporativeCooler.availableSchedule().handle());

  EXPECT_TRUE(evaporativeCooler.setCoolerDesignEffectiveness(0.84));
  EXPECT_DOUBLE_EQ(0.84, evaporativeCooler.coolerDesignEffectiveness());
  EXPECT_DOUBLE_EQ(0.84, evaporativeCooler.coolerEffectiveness());

  EXPECT_TRUE(evaporativeCooler.setCoolerEffectiveness(0.81));
  EXPECT_DOUBLE_EQ(0.81, evaporativeCooler.coolerDesignEffectiveness());

  EXPECT_TRUE(evaporativeCooler.setRecirculatingWaterPumpPowerConsumption(195.0));
  ASSERT_TRUE(evaporativeCooler.recirculatingWaterPumpPowerConsumption());
  EXPECT_DOUBLE_EQ(195.0, evaporativeCooler.recirculatingWaterPumpPowerConsumption().get());
  EXPECT_FALSE(evaporativeCooler.isRecirculatingWaterPumpPowerConsumptionAutosized());

  evaporativeCooler.autosizeRecirculatingWaterPumpPowerConsumption();
  EXPECT_TRUE(evaporativeCooler.isRecirculatingWaterPumpPowerConsumptionAutosized());
  EXPECT_FALSE(evaporativeCooler.recirculatingWaterPumpPowerConsumption());

  EXPECT_TRUE(evaporativeCooler.setPrimaryAirDesignFlowRate(1.15));
  ASSERT_TRUE(evaporativeCooler.primaryAirDesignFlowRate());
  EXPECT_DOUBLE_EQ(1.15, evaporativeCooler.primaryAirDesignFlowRate().get());
  EXPECT_FALSE(evaporativeCooler.isPrimaryAirDesignFlowRateAutosized());

  evaporativeCooler.autosizePrimaryAirDesignFlowRate();
  EXPECT_TRUE(evaporativeCooler.isPrimaryAirDesignFlowRateAutosized());
  EXPECT_FALSE(evaporativeCooler.primaryAirDesignFlowRate());

  EXPECT_TRUE(evaporativeCooler.setSensorNode(sensorNode));
  ASSERT_TRUE(evaporativeCooler.sensorNode());
  EXPECT_EQ(sensorNode.handle(), evaporativeCooler.sensorNode()->handle());

  EXPECT_TRUE(evaporativeCooler.setDriftLossFraction(0.002));
  EXPECT_DOUBLE_EQ(0.002, evaporativeCooler.driftLossFraction());

  EXPECT_TRUE(evaporativeCooler.setBlowdownConcentrationRatio(3.5));
  EXPECT_DOUBLE_EQ(3.5, evaporativeCooler.blowdownConcentrationRatio());

  EXPECT_TRUE(evaporativeCooler.setEffectivenessFlowRatioModifierCurve(effectivenessCurve));
  ASSERT_TRUE(evaporativeCooler.effectivenessFlowRatioModifierCurve());
  EXPECT_EQ(effectivenessCurve.handle(), evaporativeCooler.effectivenessFlowRatioModifierCurve()->handle());
  evaporativeCooler.resetEffectivenessFlowRatioModifierCurve();
  EXPECT_FALSE(evaporativeCooler.effectivenessFlowRatioModifierCurve());

  EXPECT_TRUE(evaporativeCooler.setWaterPumpPowerSizingFactor(85.0));
  EXPECT_DOUBLE_EQ(85.0, evaporativeCooler.waterPumpPowerSizingFactor());

  EXPECT_TRUE(evaporativeCooler.setWaterPumpPowerModifierCurve(waterPumpCurve));
  ASSERT_TRUE(evaporativeCooler.waterPumpPowerModifierCurve());
  EXPECT_EQ(waterPumpCurve.handle(), evaporativeCooler.waterPumpPowerModifierCurve()->handle());
  evaporativeCooler.resetWaterPumpPowerModifierCurve();
  EXPECT_FALSE(evaporativeCooler.waterPumpPowerModifierCurve());

  EXPECT_TRUE(evaporativeCooler.setEvaporativeOperationMinimumDrybulbTemperature(15.0));
  EXPECT_TRUE(evaporativeCooler.setEvaporativeOperationMaximumLimitWetbulbTemperature(24.0));
  EXPECT_TRUE(evaporativeCooler.setEvaporativeOperationMaximumLimitDrybulbTemperature(29.0));

  EXPECT_DOUBLE_EQ(15.0, evaporativeCooler.evaporativeOperationMinimumDrybulbTemperature());
  EXPECT_DOUBLE_EQ(24.0, evaporativeCooler.evaporativeOperationMaximumLimitWetbulbTemperature());
  EXPECT_DOUBLE_EQ(29.0, evaporativeCooler.evaporativeOperationMaximumLimitDrybulbTemperature());

  EXPECT_FALSE(evaporativeCooler.autosizedRecirculatingWaterPumpPowerConsumption());
  EXPECT_FALSE(evaporativeCooler.autosizedPrimaryAirDesignFlowRate());
}

TEST_F(EPModelFixture, EvaporativeCoolerDirectResearchSpecial_AvailabilitySchedule_RoundTripAndValidation) {
  Model model;
  EvaporativeCoolerDirectResearchSpecial evaporativeCooler(model);

  ScheduleCompact compactSchedule(model);
  ASSERT_TRUE(compactSchedule.setToConstantValue(0.5));
  EXPECT_TRUE(evaporativeCooler.setAvailabilitySchedule(compactSchedule));
  EXPECT_EQ(compactSchedule.cast<ModelObject>(), evaporativeCooler.availabilitySchedule().cast<ModelObject>());
  EXPECT_TRUE(evaporativeCooler.setAvailableSchedule(compactSchedule));
  EXPECT_EQ(compactSchedule.cast<ModelObject>(), evaporativeCooler.availableSchedule().cast<ModelObject>());
  ASSERT_TRUE(compactSchedule.scheduleTypeLimits());
  EXPECT_EQ("Availability", compactSchedule.scheduleTypeLimits()->unitType());

  ScheduleConstant continuousAvailabilitySchedule(model);
  ASSERT_TRUE(continuousAvailabilitySchedule.setValue(1.0));
  ScheduleTypeLimits continuousAvailabilityLimits(model);
  ASSERT_TRUE(continuousAvailabilityLimits.setUnitType("Availability"));
  ASSERT_TRUE(continuousAvailabilityLimits.setNumericType("Continuous"));
  ASSERT_TRUE(continuousAvailabilityLimits.setLowerLimitValue(0.0));
  ASSERT_TRUE(continuousAvailabilityLimits.setUpperLimitValue(1.0));
  ASSERT_TRUE(continuousAvailabilitySchedule.setScheduleTypeLimits(continuousAvailabilityLimits));
  EXPECT_TRUE(evaporativeCooler.setAvailabilitySchedule(continuousAvailabilitySchedule));
  EXPECT_EQ(continuousAvailabilitySchedule.cast<ModelObject>(), evaporativeCooler.availabilitySchedule().cast<ModelObject>());
  EXPECT_TRUE(evaporativeCooler.setAvailableSchedule(continuousAvailabilitySchedule));
  EXPECT_EQ(continuousAvailabilitySchedule.cast<ModelObject>(), evaporativeCooler.availableSchedule().cast<ModelObject>());

  ScheduleConstant wrongSchedule(model);
  ASSERT_TRUE(wrongSchedule.setValue(20.0));
  ScheduleTypeLimits temperatureLimits(model);
  ASSERT_TRUE(temperatureLimits.setUnitType("Temperature"));
  ASSERT_TRUE(wrongSchedule.setScheduleTypeLimits(temperatureLimits));
  EXPECT_FALSE(evaporativeCooler.setAvailabilitySchedule(wrongSchedule));
  EXPECT_FALSE(evaporativeCooler.setAvailableSchedule(wrongSchedule));
}

TEST_F(EPModelFixture, EvaporativeCoolerDirectResearchSpecial_AvailabilityScheduleGetterRepairsMissingRequiredReference) {
  Model model;
  EvaporativeCoolerDirectResearchSpecial evaporativeCooler(model);

  ASSERT_TRUE(evaporativeCooler.setPointer(openstudio::EvaporativeCooler_Direct_ResearchSpecialFields::AvailabilityScheduleName,
                                          openstudio::Handle()));
  EXPECT_FALSE(evaporativeCooler.getModelObjectTarget<Schedule>(openstudio::EvaporativeCooler_Direct_ResearchSpecialFields::AvailabilityScheduleName));

  const auto repairedSchedule = evaporativeCooler.availabilitySchedule();
  EXPECT_EQ(model.alwaysOnDiscreteSchedule(), repairedSchedule);
  EXPECT_EQ(repairedSchedule, evaporativeCooler.availableSchedule());

  const auto storedSchedule =
    evaporativeCooler.getModelObjectTarget<Schedule>(openstudio::EvaporativeCooler_Direct_ResearchSpecialFields::AvailabilityScheduleName);
  ASSERT_TRUE(storedSchedule);
  EXPECT_EQ(model.alwaysOnDiscreteSchedule(), *storedSchedule);
}

TEST_F(EPModelFixture, EvaporativeCoolerDirectResearchSpecial_AddToSupplyNode) {
  Model model;
  AirLoopHVAC airLoop(model);
  EvaporativeCoolerDirectResearchSpecial evaporativeCooler(model);

  auto supplyInlet = airLoop.supplyInletNode();
  EXPECT_TRUE(evaporativeCooler.addToNode(supplyInlet));
  EXPECT_TRUE(evaporativeCooler.airLoopHVAC());

  ASSERT_TRUE(evaporativeCooler.sensorNode());
  auto outletObject = evaporativeCooler.outletModelObject();
  ASSERT_TRUE(outletObject);
  auto outletNode = outletObject->optionalCast<Node>();
  ASSERT_TRUE(outletNode);
  EXPECT_EQ(outletNode->handle(), evaporativeCooler.sensorNode()->handle());
}

TEST_F(EPModelFixture, EvaporativeCoolerDirectResearchSpecial_AddToDemandBranchRejected) {
  Model model;
  AirLoopHVAC airLoop(model);
  EvaporativeCoolerDirectResearchSpecial evaporativeCooler(model);

  auto branchObject = airLoop.zoneSplitter().lastOutletModelObject();
  ASSERT_TRUE(branchObject);
  auto branchNode = branchObject->optionalCast<Node>();
  ASSERT_TRUE(branchNode);

  EXPECT_FALSE(evaporativeCooler.addToNode(*branchNode));
  EXPECT_FALSE(evaporativeCooler.airLoopHVAC());
}

TEST_F(EPModelFixture, EvaporativeCoolerDirectResearchSpecial_AddToNodeSupportsOutboardOANode) {
  Model model;
  AirLoopHVAC airLoop(model);
  AirLoopHVACOutdoorAirSystem oaSystem(model);
  auto supplyInletNode = airLoop.supplyInletNode();
  ASSERT_TRUE(oaSystem.addToNode(supplyInletNode));

  auto outboardOANode = oaSystem.outboardOANode();
  ASSERT_TRUE(outboardOANode);

  EvaporativeCoolerDirectResearchSpecial evaporativeCooler(model);
  EXPECT_TRUE(evaporativeCooler.addToNode(*outboardOANode));
  EXPECT_EQ(3u, oaSystem.oaComponents().size());

  ASSERT_TRUE(evaporativeCooler.sensorNode());
  auto outletObject = evaporativeCooler.outletModelObject();
  ASSERT_TRUE(outletObject);
  auto outletNode = outletObject->optionalCast<Node>();
  ASSERT_TRUE(outletNode);
  EXPECT_EQ(outletNode->handle(), evaporativeCooler.sensorNode()->handle());
}
