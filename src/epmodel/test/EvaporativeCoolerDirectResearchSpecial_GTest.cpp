/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../Curve/CurveLinear.hpp"
#include "../HVACComponent/AirLoopHVACOutdoorAirSystem.hpp"
#include "../HVACComponent/AirLoopHVACOutdoorAirSystem_Impl.hpp"
#include "../Loop/AirLoopHVAC.hpp"
#include "../ResourceObject/ScheduleTypeLimits.hpp"
#include "../Schedule/ScheduleCompact.hpp"
#include "../Schedule/ScheduleConstant.hpp"
#include "../Schedule/Schedule.hpp"
#include "../Schedule/Schedule_Impl.hpp"
#include "../StraightComponent/EvaporativeCoolerDirectResearchSpecial.hpp"
#include "../StraightComponent/EvaporativeCoolerDirectResearchSpecial_Impl.hpp"
#include "../StraightComponent/EvaporativeCoolerIndirectResearchSpecial.hpp"
#include "../StraightComponent/EvaporativeCoolerIndirectResearchSpecial_Impl.hpp"
#include "../StraightComponent/Node.hpp"
#include "../Splitter/AirLoopHVACZoneSplitter.hpp"

#include <utilities/idd/EvaporativeCooler_Direct_ResearchSpecial_FieldEnums.hxx>
#include <utilities/idd/EvaporativeCooler_Indirect_ResearchSpecial_FieldEnums.hxx>
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

  ASSERT_TRUE(
    evaporativeCooler.setPointer(openstudio::EvaporativeCooler_Direct_ResearchSpecialFields::AvailabilityScheduleName, openstudio::Handle()));
  EXPECT_FALSE(
    evaporativeCooler.getModelObjectTarget<Schedule>(openstudio::EvaporativeCooler_Direct_ResearchSpecialFields::AvailabilityScheduleName));

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

TEST_F(EPModelFixture, EvaporativeCoolers_OutdoorAirChainSurvivesSaveLoadAndAdjacentRemoval) {
  const auto idfPath = openstudio::tempDir() / openstudio::toPath("epmodel-evaporative-cooler-oa-chain-roundtrip.idf");

  Model model;
  AirLoopHVAC airLoop(model);
  AirLoopHVACOutdoorAirSystem oaSystem(model);
  EvaporativeCoolerDirectResearchSpecial directCooler(model);
  EvaporativeCoolerIndirectResearchSpecial indirectCooler(model);
  ASSERT_TRUE(airLoop.setName("Evaporative Cooler Air Loop"));
  ASSERT_TRUE(oaSystem.setName("Evaporative Cooler OA System"));
  ASSERT_TRUE(directCooler.setName("Direct Evaporative Cooler"));
  ASSERT_TRUE(indirectCooler.setName("Indirect Evaporative Cooler"));

  auto supplyInletNode = airLoop.supplyInletNode();
  ASSERT_TRUE(oaSystem.addToNode(supplyInletNode));
  auto outboardOANode = oaSystem.outboardOANode();
  ASSERT_TRUE(outboardOANode);
  ASSERT_TRUE(directCooler.addToNode(*outboardOANode));
  ASSERT_TRUE(indirectCooler.addToNode(*outboardOANode));

  auto equipment = oaSystem.oaComponents();
  std::erase_if(equipment, [](const ModelObject& object) { return object.optionalCast<Node>().has_value(); });
  ASSERT_EQ(2u, equipment.size());
  EXPECT_EQ(indirectCooler.handle(), equipment[0].handle());
  EXPECT_EQ(directCooler.handle(), equipment[1].handle());
  ASSERT_TRUE(indirectCooler.outletModelObject());
  ASSERT_TRUE(directCooler.inletModelObject());
  EXPECT_EQ(indirectCooler.outletModelObject()->handle(), directCooler.inletModelObject()->handle());

  ASSERT_TRUE(directCooler.sensorNode());
  ASSERT_TRUE(directCooler.outletModelObject());
  EXPECT_EQ(directCooler.outletModelObject()->handle(), directCooler.sensorNode()->handle());
  auto indirectSensor = indirectCooler.getModelObjectTarget<Node>(openstudio::EvaporativeCooler_Indirect_ResearchSpecialFields::SensorNodeName);
  ASSERT_TRUE(indirectSensor);
  EXPECT_EQ(indirectCooler.outletModelObject()->handle(), indirectSensor->handle());

  ASSERT_TRUE(model.save(idfPath, true));
  auto loadedModel = Model::load(idfPath);
  ASSERT_TRUE(loadedModel);
  auto loadedOASystem = loadedModel->getConcreteModelObjectByName<AirLoopHVACOutdoorAirSystem>("Evaporative Cooler OA System");
  auto loadedDirect = loadedModel->getConcreteModelObjectByName<EvaporativeCoolerDirectResearchSpecial>("Direct Evaporative Cooler");
  auto loadedIndirect = loadedModel->getConcreteModelObjectByName<EvaporativeCoolerIndirectResearchSpecial>("Indirect Evaporative Cooler");
  ASSERT_TRUE(loadedOASystem);
  ASSERT_TRUE(loadedDirect);
  ASSERT_TRUE(loadedIndirect);

  equipment = loadedOASystem->oaComponents();
  std::erase_if(equipment, [](const ModelObject& object) { return object.optionalCast<Node>().has_value(); });
  ASSERT_EQ(2u, equipment.size());
  EXPECT_EQ(loadedIndirect->handle(), equipment[0].handle());
  EXPECT_EQ(loadedDirect->handle(), equipment[1].handle());
  ASSERT_TRUE(loadedDirect->sensorNode());
  ASSERT_TRUE(loadedDirect->outletModelObject());
  EXPECT_EQ(loadedDirect->outletModelObject()->handle(), loadedDirect->sensorNode()->handle());
  indirectSensor = loadedIndirect->getModelObjectTarget<Node>(openstudio::EvaporativeCooler_Indirect_ResearchSpecialFields::SensorNodeName);
  ASSERT_TRUE(indirectSensor);
  ASSERT_TRUE(loadedIndirect->outletModelObject());
  EXPECT_EQ(loadedIndirect->outletModelObject()->handle(), indirectSensor->handle());

  ASSERT_TRUE(loadedIndirect->removeFromLoop());
  equipment = loadedOASystem->oaComponents();
  std::erase_if(equipment, [](const ModelObject& object) { return object.optionalCast<Node>().has_value(); });
  ASSERT_EQ(1u, equipment.size());
  EXPECT_EQ(loadedDirect->handle(), equipment.front().handle());
  ASSERT_TRUE(loadedOASystem->outboardOANode());
  ASSERT_TRUE(loadedDirect->inletModelObject());
  EXPECT_EQ(loadedOASystem->outboardOANode()->handle(), loadedDirect->inletModelObject()->handle());
  ASSERT_TRUE(loadedDirect->sensorNode());
  EXPECT_EQ(loadedDirect->outletModelObject()->handle(), loadedDirect->sensorNode()->handle());

  auto loadedOutboardOANode = loadedOASystem->outboardOANode();
  ASSERT_TRUE(loadedOutboardOANode);
  ASSERT_TRUE(loadedIndirect->addToNode(*loadedOutboardOANode));
  equipment = loadedOASystem->oaComponents();
  std::erase_if(equipment, [](const ModelObject& object) { return object.optionalCast<Node>().has_value(); });
  ASSERT_EQ(2u, equipment.size());
  EXPECT_EQ(loadedIndirect->handle(), equipment[0].handle());
  EXPECT_EQ(loadedDirect->handle(), equipment[1].handle());

  openstudio::filesystem::remove(idfPath);
}
