/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../Loop/AirLoopHVAC.hpp"
#include "../HVACComponent/AirLoopHVACOutdoorAirSystem.hpp"
#include "../Schedule/ScheduleConstant.hpp"
#include "../Schedule/ScheduleConstant_Impl.hpp"
#include "../StraightComponent/CoilCoolingDXSingleSpeedThermalStorage.hpp"
#include "../StraightComponent/Node.hpp"

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, CoilCoolingDXSingleSpeedThermalStorage_DefaultConstructor) {
  Model model;
  CoilCoolingDXSingleSpeedThermalStorage coil(model);
  EXPECT_EQ(CoilCoolingDXSingleSpeedThermalStorage::iddObjectType(), coil.iddObject().type());
  EXPECT_FALSE(coil.nameString().empty());

  auto availability = coil.availabilitySchedule().optionalCast<ScheduleConstant>();
  ASSERT_TRUE(availability);
  EXPECT_DOUBLE_EQ(1.0, availability->value());
  EXPECT_FALSE(coil.operationModeControlSchedule());
  EXPECT_FALSE(coil.basinHeaterAvailabilitySchedule());
}

TEST_F(EPModelFixture, CoilCoolingDXSingleSpeedThermalStorage_ScalarAccessors_RoundTrip) {
  Model model;
  CoilCoolingDXSingleSpeedThermalStorage coil(model);

  ASSERT_FALSE(CoilCoolingDXSingleSpeedThermalStorage::operatingModeControlMethodValues().empty());
  ASSERT_FALSE(CoilCoolingDXSingleSpeedThermalStorage::storageTypeValues().empty());
  ASSERT_FALSE(CoilCoolingDXSingleSpeedThermalStorage::condenserTypeValues().empty());

  EXPECT_TRUE(coil.setOperatingModeControlMethod("ScheduledModes"));
  EXPECT_EQ("ScheduledModes", coil.operatingModeControlMethod());

  EXPECT_TRUE(coil.setStorageType("Ice"));
  EXPECT_EQ("Ice", coil.storageType());

  coil.autosizeRatedEvaporatorAirFlowRate();
  EXPECT_TRUE(coil.isRatedEvaporatorAirFlowRateAutosized());
  EXPECT_FALSE(coil.ratedEvaporatorAirFlowRate());
  EXPECT_TRUE(coil.setRatedEvaporatorAirFlowRate(1.15));
  ASSERT_TRUE(coil.ratedEvaporatorAirFlowRate());
  EXPECT_DOUBLE_EQ(1.15, *coil.ratedEvaporatorAirFlowRate());

  EXPECT_TRUE(coil.setCoolingOnlyModeAvailable(true));
  EXPECT_TRUE(coil.coolingOnlyModeAvailable());

  coil.autosizeCoolingAndDischargeModeRatedStorageDischargingCapacity();
  EXPECT_TRUE(coil.isCoolingAndDischargeModeRatedStorageDischargingCapacityAutosized());

  EXPECT_TRUE(coil.setCondenserType("EvaporativelyCooled"));
  EXPECT_EQ("EvaporativelyCooled", coil.condenserType());

  EXPECT_TRUE(coil.setColdWeatherOperationMinimumOutdoorAirTemperature(-7.0));
  ASSERT_TRUE(coil.coldWeatherOperationMinimumOutdoorAirTemperature());
  EXPECT_DOUBLE_EQ(-7.0, *coil.coldWeatherOperationMinimumOutdoorAirTemperature());
  coil.resetColdWeatherOperationMinimumOutdoorAirTemperature();
  EXPECT_FALSE(coil.coldWeatherOperationMinimumOutdoorAirTemperature());
}

TEST_F(EPModelFixture, CoilCoolingDXSingleSpeedThermalStorage_RelationshipSetters_RoundTrip) {
  Model model;
  CoilCoolingDXSingleSpeedThermalStorage coil(model);

  ScheduleConstant availability(model);
  ASSERT_TRUE(availability.setValue(0.25));
  ScheduleConstant operatingMode(model);
  ASSERT_TRUE(operatingMode.setValue(0.5));
  ScheduleConstant basinHeater(model);
  ASSERT_TRUE(basinHeater.setValue(0.75));

  EXPECT_TRUE(coil.setAvailabilitySchedule(availability));
  EXPECT_EQ(availability.handle(), coil.availabilitySchedule().handle());

  EXPECT_TRUE(coil.setOperationModeControlSchedule(operatingMode));
  ASSERT_TRUE(coil.operationModeControlSchedule());
  EXPECT_EQ(operatingMode.handle(), coil.operationModeControlSchedule()->handle());

  EXPECT_TRUE(coil.setBasinHeaterAvailabilitySchedule(basinHeater));
  ASSERT_TRUE(coil.basinHeaterAvailabilitySchedule());
  EXPECT_EQ(basinHeater.handle(), coil.basinHeaterAvailabilitySchedule()->handle());

  coil.resetOperationModeControlSchedule();
  EXPECT_FALSE(coil.operationModeControlSchedule());
  coil.resetBasinHeaterAvailabilitySchedule();
  EXPECT_FALSE(coil.basinHeaterAvailabilitySchedule());
}

TEST_F(EPModelFixture, CoilCoolingDXSingleSpeedThermalStorage_AddToNodeSupplyOnly) {
  Model model;
  AirLoopHVAC airLoop(model);
  CoilCoolingDXSingleSpeedThermalStorage supplyCoil(model);
  CoilCoolingDXSingleSpeedThermalStorage demandCoil(model);
  CoilCoolingDXSingleSpeedThermalStorage oaCoil(model);

  auto supplyInletNode = airLoop.supplyInletNode();
  EXPECT_TRUE(supplyCoil.addToNode(supplyInletNode));
  ASSERT_TRUE(supplyCoil.inletModelObject());
  EXPECT_EQ(supplyInletNode, supplyCoil.inletModelObject()->cast<Node>());
  EXPECT_TRUE(supplyCoil.outletModelObject());

  auto demandInletNode = airLoop.demandInletNode();
  EXPECT_FALSE(demandCoil.addToNode(demandInletNode));
  EXPECT_FALSE(demandCoil.airLoopHVAC());

  AirLoopHVACOutdoorAirSystem oaSystem(model);
  ASSERT_TRUE(oaSystem.addToNode(supplyInletNode));
  auto outboardOANode = oaSystem.outboardOANode();
  ASSERT_TRUE(outboardOANode);
  EXPECT_FALSE(oaCoil.addToNode(*outboardOANode));
  EXPECT_FALSE(oaCoil.airLoopHVAC());
}
