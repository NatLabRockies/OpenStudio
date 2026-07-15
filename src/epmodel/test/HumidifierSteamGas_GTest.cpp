/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include <utilities/idd/Humidifier_Steam_Gas_FieldEnums.hxx>

#include "EPModelFixture.hpp"
#include "../HVACComponent/AirLoopHVACOutdoorAirSystem.hpp"
#include "../Loop/AirLoopHVAC.hpp"
#include "../Loop/PlantLoop.hpp"
#include "../ResourceObject/ScheduleTypeLimits.hpp"
#include "../Schedule/ScheduleCompact.hpp"
#include "../Schedule/ScheduleConstant.hpp"
#include "../Splitter/AirLoopHVACZoneSplitter.hpp"
#include "../StraightComponent/HumidifierSteamGas.hpp"
#include "../StraightComponent/HumidifierSteamGas_Impl.hpp"
#include "../StraightComponent/Node.hpp"

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, HumidifierSteamGas_DefaultConstructor) {
  Model model;
  HumidifierSteamGas humidifier(model);
  EXPECT_EQ(HumidifierSteamGas::iddObjectType(), humidifier.iddObject().type());
  EXPECT_FALSE(humidifier.nameString().empty());

  const std::vector<std::string> expectedInletWaterTemperatureOptionValues{"FixedInletWaterTemperature", "VariableInletWaterTemperature"};
  EXPECT_EQ(expectedInletWaterTemperatureOptionValues, HumidifierSteamGas::inletWaterTemperatureOptionValues());

  EXPECT_TRUE(humidifier.isRatedCapacityAutosized());
  EXPECT_FALSE(humidifier.ratedCapacity());

  ASSERT_TRUE(humidifier.ratedGasUseRate());
  EXPECT_DOUBLE_EQ(104000.0, humidifier.ratedGasUseRate().get());
  EXPECT_FALSE(humidifier.isRatedGasUseRateAutosized());

  EXPECT_FALSE(humidifier.availabilitySchedule());

  EXPECT_DOUBLE_EQ(0.8, humidifier.thermalEfficiency());
  EXPECT_TRUE(humidifier.isThermalEfficiencyDefaulted());

  EXPECT_FALSE(humidifier.ratedFanPower());

  EXPECT_DOUBLE_EQ(0.0, humidifier.auxiliaryElectricPower());
  EXPECT_TRUE(humidifier.isAuxiliaryElectricPowerDefaulted());

  EXPECT_EQ("FixedInletWaterTemperature", humidifier.inletWaterTemperatureOption());
  EXPECT_TRUE(humidifier.isInletWaterTemperatureOptionDefaulted());

  const auto waterStorageTankName = humidifier.getString(openstudio::Humidifier_Steam_GasFields::WaterStorageTankName, true);
  ASSERT_TRUE(waterStorageTankName);
  EXPECT_TRUE(waterStorageTankName->empty());
}

TEST_F(EPModelFixture, HumidifierSteamGas_ScalarAccessors_RoundTrip) {
  Model model;
  HumidifierSteamGas humidifier(model);

  EXPECT_TRUE(humidifier.setRatedCapacity(0.42));
  ASSERT_TRUE(humidifier.ratedCapacity());
  EXPECT_DOUBLE_EQ(0.42, humidifier.ratedCapacity().get());
  EXPECT_FALSE(humidifier.isRatedCapacityAutosized());
  humidifier.autosizeRatedCapacity();
  EXPECT_TRUE(humidifier.isRatedCapacityAutosized());
  EXPECT_FALSE(humidifier.ratedCapacity());

  EXPECT_TRUE(humidifier.setRatedGasUseRate(1234.0));
  ASSERT_TRUE(humidifier.ratedGasUseRate());
  EXPECT_DOUBLE_EQ(1234.0, humidifier.ratedGasUseRate().get());
  EXPECT_FALSE(humidifier.isRatedGasUseRateAutosized());
  humidifier.autosizeRatedGasUseRate();
  EXPECT_TRUE(humidifier.isRatedGasUseRateAutosized());
  EXPECT_FALSE(humidifier.ratedGasUseRate());
  humidifier.resetRatedGasUseRate();
  EXPECT_FALSE(humidifier.ratedGasUseRate());
  EXPECT_FALSE(humidifier.isRatedGasUseRateAutosized());

  EXPECT_TRUE(humidifier.setThermalEfficiency(0.9));
  EXPECT_DOUBLE_EQ(0.9, humidifier.thermalEfficiency());
  EXPECT_FALSE(humidifier.isThermalEfficiencyDefaulted());
  humidifier.resetThermalEfficiency();
  EXPECT_DOUBLE_EQ(0.8, humidifier.thermalEfficiency());
  EXPECT_TRUE(humidifier.isThermalEfficiencyDefaulted());

  EXPECT_TRUE(humidifier.setRatedFanPower(110.0));
  ASSERT_TRUE(humidifier.ratedFanPower());
  EXPECT_DOUBLE_EQ(110.0, humidifier.ratedFanPower().get());
  humidifier.resetRatedFanPower();
  EXPECT_FALSE(humidifier.ratedFanPower());

  EXPECT_TRUE(humidifier.setAuxiliaryElectricPower(8.0));
  EXPECT_DOUBLE_EQ(8.0, humidifier.auxiliaryElectricPower());
  EXPECT_FALSE(humidifier.isAuxiliaryElectricPowerDefaulted());
  humidifier.resetAuxiliaryElectricPower();
  EXPECT_DOUBLE_EQ(0.0, humidifier.auxiliaryElectricPower());
  EXPECT_TRUE(humidifier.isAuxiliaryElectricPowerDefaulted());

  EXPECT_TRUE(humidifier.setInletWaterTemperatureOption("VariableInletWaterTemperature"));
  EXPECT_EQ("VariableInletWaterTemperature", humidifier.inletWaterTemperatureOption());
  EXPECT_FALSE(humidifier.isInletWaterTemperatureOptionDefaulted());
  humidifier.resetInletWaterTemperatureOption();
  EXPECT_EQ("FixedInletWaterTemperature", humidifier.inletWaterTemperatureOption());
  EXPECT_TRUE(humidifier.isInletWaterTemperatureOptionDefaulted());

  EXPECT_FALSE(humidifier.autosizedRatedCapacity());
  EXPECT_FALSE(humidifier.autosizedRatedGasUseRate());
}

TEST_F(EPModelFixture, HumidifierSteamGas_AvailabilitySchedule_RoundTripAndValidation) {
  Model model;
  HumidifierSteamGas humidifier(model);

  ScheduleCompact compactSchedule(model);
  ASSERT_TRUE(compactSchedule.setToConstantValue(0.5));
  EXPECT_TRUE(humidifier.setAvailabilitySchedule(compactSchedule));
  ASSERT_TRUE(humidifier.availabilitySchedule());
  EXPECT_EQ(compactSchedule.cast<ModelObject>(), humidifier.availabilitySchedule()->cast<ModelObject>());
  ASSERT_TRUE(compactSchedule.scheduleTypeLimits());
  EXPECT_EQ("Availability", compactSchedule.scheduleTypeLimits()->unitType());

  ScheduleConstant discreteAvailabilitySchedule(model);
  ASSERT_TRUE(discreteAvailabilitySchedule.setValue(1.0));
  ScheduleTypeLimits discreteAvailabilityLimits(model);
  ASSERT_TRUE(discreteAvailabilityLimits.setUnitType("Availability"));
  ASSERT_TRUE(discreteAvailabilityLimits.setNumericType("Discrete"));
  ASSERT_TRUE(discreteAvailabilityLimits.setLowerLimitValue(0.0));
  ASSERT_TRUE(discreteAvailabilityLimits.setUpperLimitValue(1.0));
  ASSERT_TRUE(discreteAvailabilitySchedule.setScheduleTypeLimits(discreteAvailabilityLimits));
  EXPECT_TRUE(humidifier.setAvailabilitySchedule(discreteAvailabilitySchedule));
  ASSERT_TRUE(humidifier.availabilitySchedule());
  EXPECT_EQ(discreteAvailabilitySchedule.cast<ModelObject>(), humidifier.availabilitySchedule()->cast<ModelObject>());

  ScheduleConstant wrongSchedule(model);
  ASSERT_TRUE(wrongSchedule.setValue(20.0));
  ScheduleTypeLimits temperatureLimits(model);
  ASSERT_TRUE(temperatureLimits.setUnitType("Temperature"));
  ASSERT_TRUE(wrongSchedule.setScheduleTypeLimits(temperatureLimits));
  EXPECT_FALSE(humidifier.setAvailabilitySchedule(wrongSchedule));
  ASSERT_TRUE(humidifier.availabilitySchedule());
  EXPECT_EQ(discreteAvailabilitySchedule.cast<ModelObject>(), humidifier.availabilitySchedule()->cast<ModelObject>());

  humidifier.resetAvailabilitySchedule();
  EXPECT_FALSE(humidifier.availabilitySchedule());
}

TEST_F(EPModelFixture, HumidifierSteamGas_AddToNodeSupplyOnlyAndClone) {
  Model model;
  AirLoopHVAC airLoop(model);
  HumidifierSteamGas supplyHumidifier(model);
  HumidifierSteamGas demandHumidifier(model);

  EXPECT_EQ(2u, airLoop.supplyComponents().size());

  auto supplyOutletNode = airLoop.supplyOutletNode();
  EXPECT_TRUE(supplyHumidifier.addToNode(supplyOutletNode));
  EXPECT_EQ(3u, airLoop.supplyComponents().size());
  EXPECT_EQ(1u, airLoop.supplyComponents(HumidifierSteamGas::iddObjectType()).size());
  ASSERT_TRUE(supplyHumidifier.airLoopHVAC());
  ASSERT_TRUE(supplyHumidifier.inletModelObject());
  ASSERT_TRUE(supplyHumidifier.outletModelObject());
  EXPECT_EQ(supplyOutletNode, supplyHumidifier.outletModelObject()->cast<Node>());

  auto demandBranchObject = airLoop.zoneSplitter().lastOutletModelObject();
  ASSERT_TRUE(demandBranchObject);
  auto demandBranchNode = demandBranchObject->optionalCast<Node>();
  ASSERT_TRUE(demandBranchNode);
  EXPECT_FALSE(demandHumidifier.addToNode(*demandBranchNode));
  EXPECT_FALSE(demandHumidifier.airLoopHVAC());

  Node unconnectedNode(model);
  EXPECT_FALSE(demandHumidifier.addToNode(unconnectedNode));

  PlantLoop plantLoop(model);
  auto plantSupplyOutletNode = plantLoop.supplyOutletNode();
  EXPECT_FALSE(demandHumidifier.addToNode(plantSupplyOutletNode));
  EXPECT_FALSE(demandHumidifier.plantLoop());

  auto plantDemandOutletNode = plantLoop.demandOutletNode();
  EXPECT_FALSE(demandHumidifier.addToNode(plantDemandOutletNode));
  EXPECT_FALSE(demandHumidifier.plantLoop());

  auto supplyHumidifierCloneObject = model.addObject(supplyHumidifier.idfObject());
  ASSERT_TRUE(supplyHumidifierCloneObject);
  auto supplyHumidifierClone = supplyHumidifierCloneObject->cast<HumidifierSteamGas>();

  supplyOutletNode = airLoop.supplyOutletNode();
  EXPECT_TRUE(supplyHumidifierClone.addToNode(supplyOutletNode));
  EXPECT_EQ(2u, airLoop.supplyComponents(HumidifierSteamGas::iddObjectType()).size());
  ASSERT_TRUE(supplyHumidifierClone.airLoopHVAC());
  ASSERT_TRUE(supplyHumidifierClone.inletModelObject());
  ASSERT_TRUE(supplyHumidifierClone.outletModelObject());
}

TEST_F(EPModelFixture, HumidifierSteamGas_AddToNodeSupportsOutboardOANodeAndReliefNode) {
  Model model;
  AirLoopHVAC airLoop(model);
  AirLoopHVACOutdoorAirSystem oaSystem(model);
  auto supplyInletNode = airLoop.supplyInletNode();
  ASSERT_TRUE(oaSystem.addToNode(supplyInletNode));

  auto outboardOANode = oaSystem.outboardOANode();
  ASSERT_TRUE(outboardOANode);

  HumidifierSteamGas oaHumidifier(model);
  EXPECT_TRUE(oaHumidifier.addToNode(*outboardOANode));
  ASSERT_TRUE(oaHumidifier.inletModelObject());
  EXPECT_EQ(*outboardOANode, oaHumidifier.inletModelObject()->cast<Node>());
  EXPECT_EQ(3u, oaSystem.oaComponents().size());

  auto outboardReliefNode = oaSystem.outboardReliefNode();
  ASSERT_TRUE(outboardReliefNode);

  HumidifierSteamGas reliefHumidifier(model);
  EXPECT_TRUE(reliefHumidifier.addToNode(*outboardReliefNode));
  ASSERT_TRUE(reliefHumidifier.outletModelObject());
  EXPECT_EQ(*outboardReliefNode, reliefHumidifier.outletModelObject()->cast<Node>());
  EXPECT_EQ(3u, oaSystem.reliefComponents().size());
}
