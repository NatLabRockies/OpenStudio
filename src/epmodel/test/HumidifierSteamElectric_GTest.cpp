/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include <utilities/idd/Humidifier_Steam_Electric_FieldEnums.hxx>

#include "EPModelFixture.hpp"
#include "../HVACComponent/AirLoopHVACOutdoorAirSystem.hpp"
#include "../Loop/AirLoopHVAC.hpp"
#include "../Loop/PlantLoop.hpp"
#include "../ResourceObject/ScheduleTypeLimits.hpp"
#include "../Schedule/ScheduleCompact.hpp"
#include "../Schedule/ScheduleConstant.hpp"
#include "../Splitter/AirLoopHVACZoneSplitter.hpp"
#include "../StraightComponent/HumidifierSteamElectric.hpp"
#include "../StraightComponent/HumidifierSteamElectric_Impl.hpp"
#include "../StraightComponent/Node.hpp"

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, HumidifierSteamElectric_DefaultConstructor) {
  Model model;
  HumidifierSteamElectric humidifier(model);
  EXPECT_EQ(HumidifierSteamElectric::iddObjectType(), humidifier.iddObject().type());
  EXPECT_FALSE(humidifier.nameString().empty());

  EXPECT_TRUE(humidifier.isRatedCapacityAutosized());
  EXPECT_FALSE(humidifier.ratedCapacity());

  ASSERT_TRUE(humidifier.ratedPower());
  EXPECT_DOUBLE_EQ(10200.0, humidifier.ratedPower().get());
  EXPECT_FALSE(humidifier.isRatedPowerAutosized());

  EXPECT_FALSE(humidifier.availabilitySchedule());

  const auto waterStorageTankName = humidifier.getString(openstudio::Humidifier_Steam_ElectricFields::WaterStorageTankName, true);
  ASSERT_TRUE(waterStorageTankName);
  EXPECT_TRUE(waterStorageTankName->empty());
}

TEST_F(EPModelFixture, HumidifierSteamElectric_ScalarAccessors_RoundTrip) {
  Model model;
  HumidifierSteamElectric humidifier(model);

  EXPECT_TRUE(humidifier.setRatedCapacity(0.42));
  ASSERT_TRUE(humidifier.ratedCapacity());
  EXPECT_DOUBLE_EQ(0.42, humidifier.ratedCapacity().get());
  EXPECT_FALSE(humidifier.isRatedCapacityAutosized());

  humidifier.autosizeRatedCapacity();
  EXPECT_TRUE(humidifier.isRatedCapacityAutosized());
  EXPECT_FALSE(humidifier.ratedCapacity());

  EXPECT_TRUE(humidifier.setRatedPower(9800.0));
  ASSERT_TRUE(humidifier.ratedPower());
  EXPECT_DOUBLE_EQ(9800.0, humidifier.ratedPower().get());
  EXPECT_FALSE(humidifier.isRatedPowerAutosized());

  humidifier.autosizeRatedPower();
  EXPECT_TRUE(humidifier.isRatedPowerAutosized());
  EXPECT_FALSE(humidifier.ratedPower());

  EXPECT_TRUE(humidifier.setRatedFanPower(110.0));
  ASSERT_TRUE(humidifier.ratedFanPower());
  EXPECT_DOUBLE_EQ(110.0, humidifier.ratedFanPower().get());
  humidifier.resetRatedFanPower();
  EXPECT_FALSE(humidifier.ratedFanPower());

  EXPECT_TRUE(humidifier.setStandbyPower(8.0));
  ASSERT_TRUE(humidifier.standbyPower());
  EXPECT_DOUBLE_EQ(8.0, humidifier.standbyPower().get());
  humidifier.resetStandbyPower();
  EXPECT_FALSE(humidifier.standbyPower());

  EXPECT_FALSE(humidifier.autosizedRatedCapacity());
  EXPECT_FALSE(humidifier.autosizedRatedPower());
}

TEST_F(EPModelFixture, HumidifierSteamElectric_AvailabilitySchedule_RoundTripAndValidation) {
  Model model;
  HumidifierSteamElectric humidifier(model);

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

TEST_F(EPModelFixture, HumidifierSteamElectric_AddToNodeSupplyOnlyAndClone) {
  Model model;
  AirLoopHVAC airLoop(model);
  HumidifierSteamElectric supplyHumidifier(model);
  HumidifierSteamElectric demandHumidifier(model);

  EXPECT_EQ(2u, airLoop.supplyComponents().size());

  auto supplyOutletNode = airLoop.supplyOutletNode();
  EXPECT_TRUE(supplyHumidifier.addToNode(supplyOutletNode));
  EXPECT_EQ(3u, airLoop.supplyComponents().size());
  EXPECT_EQ(1u, airLoop.supplyComponents(HumidifierSteamElectric::iddObjectType()).size());
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
  auto supplyHumidifierClone = supplyHumidifierCloneObject->cast<HumidifierSteamElectric>();

  supplyOutletNode = airLoop.supplyOutletNode();
  EXPECT_TRUE(supplyHumidifierClone.addToNode(supplyOutletNode));
  EXPECT_EQ(2u, airLoop.supplyComponents(HumidifierSteamElectric::iddObjectType()).size());
  ASSERT_TRUE(supplyHumidifierClone.airLoopHVAC());
  ASSERT_TRUE(supplyHumidifierClone.inletModelObject());
  ASSERT_TRUE(supplyHumidifierClone.outletModelObject());
}

TEST_F(EPModelFixture, HumidifierSteamElectric_AddToNodeSupportsOutboardOANodeAndReliefNode) {
  Model model;
  AirLoopHVAC airLoop(model);
  AirLoopHVACOutdoorAirSystem oaSystem(model);
  auto supplyInletNode = airLoop.supplyInletNode();
  ASSERT_TRUE(oaSystem.addToNode(supplyInletNode));

  auto outboardOANode = oaSystem.outboardOANode();
  ASSERT_TRUE(outboardOANode);

  HumidifierSteamElectric oaHumidifier(model);
  EXPECT_TRUE(oaHumidifier.addToNode(*outboardOANode));
  ASSERT_TRUE(oaHumidifier.inletModelObject());
  EXPECT_EQ(*outboardOANode, oaHumidifier.inletModelObject()->cast<Node>());
  EXPECT_EQ(3u, oaSystem.oaComponents().size());

  auto outboardReliefNode = oaSystem.outboardReliefNode();
  ASSERT_TRUE(outboardReliefNode);

  HumidifierSteamElectric reliefHumidifier(model);
  EXPECT_TRUE(reliefHumidifier.addToNode(*outboardReliefNode));
  ASSERT_TRUE(reliefHumidifier.outletModelObject());
  EXPECT_EQ(*outboardReliefNode, reliefHumidifier.outletModelObject()->cast<Node>());
  EXPECT_EQ(3u, oaSystem.reliefComponents().size());
}
