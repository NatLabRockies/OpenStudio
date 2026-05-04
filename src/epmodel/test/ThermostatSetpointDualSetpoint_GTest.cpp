/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../HVACComponent/ThermalZone.hpp"
#include "../Model.hpp"
#include "../Model_Impl.hpp"
#include "../ResourceObject/ScheduleTypeLimits.hpp"
#include "../Schedule/ScheduleConstant.hpp"
#include "../Thermostat/ThermostatSetpointDualSetpoint.hpp"
#include "../Thermostat/ThermostatSetpointDualSetpoint_Impl.hpp"

#include <utilities/idd/IddEnums.hxx>

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, ThermostatSetpointDualSetpoint_DefaultConstructor) {
  Model model;
  ThermostatSetpointDualSetpoint thermostat(model);
  EXPECT_EQ(ThermostatSetpointDualSetpoint::iddObjectType(), thermostat.iddObject().type());
}

TEST_F(EPModelFixture, ThermostatSetpointDualSetpoint_ScalarAccessors_RoundTrip) {
  Model model;
  ThermostatSetpointDualSetpoint thermostat(model);

  EXPECT_TRUE(thermostat.setName("Dual Setpoint"));
  EXPECT_EQ("Dual Setpoint", thermostat.nameString());
}

TEST_F(EPModelFixture, ThermostatSetpointDualSetpoint_ScheduleRelationships_RoundTrip) {
  Model model;
  ThermostatSetpointDualSetpoint thermostat(model);
  ScheduleConstant heatingSchedule(model);
  ScheduleConstant coolingSchedule(model);

  EXPECT_FALSE(thermostat.heatingSetpointTemperatureSchedule());
  EXPECT_FALSE(thermostat.coolingSetpointTemperatureSchedule());

  EXPECT_TRUE(thermostat.setHeatingSetpointTemperatureSchedule(heatingSchedule));
  EXPECT_TRUE(thermostat.heatingSetpointTemperatureSchedule());
  EXPECT_EQ(heatingSchedule, thermostat.heatingSetpointTemperatureSchedule().get());
  ASSERT_TRUE(heatingSchedule.scheduleTypeLimits());
  EXPECT_EQ("Temperature", heatingSchedule.scheduleTypeLimits()->unitType());

  EXPECT_TRUE(thermostat.setCoolingSetpointTemperatureSchedule(coolingSchedule));
  EXPECT_TRUE(thermostat.coolingSetpointTemperatureSchedule());
  EXPECT_EQ(coolingSchedule, thermostat.coolingSetpointTemperatureSchedule().get());
  ASSERT_TRUE(coolingSchedule.scheduleTypeLimits());
  EXPECT_EQ("Temperature", coolingSchedule.scheduleTypeLimits()->unitType());

  EXPECT_TRUE(thermostat.setHeatingSchedule(coolingSchedule));
  EXPECT_TRUE(thermostat.getHeatingSchedule());
  EXPECT_EQ(coolingSchedule, thermostat.getHeatingSchedule().get());

  EXPECT_TRUE(thermostat.setCoolingSchedule(heatingSchedule));
  EXPECT_TRUE(thermostat.getCoolingSchedule());
  EXPECT_EQ(heatingSchedule, thermostat.getCoolingSchedule().get());

  thermostat.resetHeatingSetpointTemperatureSchedule();
  EXPECT_FALSE(thermostat.heatingSetpointTemperatureSchedule());

  thermostat.resetCoolingSchedule();
  EXPECT_FALSE(thermostat.coolingSetpointTemperatureSchedule());
}

TEST_F(EPModelFixture, ThermostatSetpointDualSetpoint_ScheduleRelationships_RejectIncompatibleScheduleTypeLimits) {
  Model model;
  ThermostatSetpointDualSetpoint thermostat(model);
  ScheduleConstant wrongSchedule(model);
  ASSERT_TRUE(wrongSchedule.setValue(1.0));
  ScheduleTypeLimits availabilityLimits(model);
  ASSERT_TRUE(availabilityLimits.setUnitType("Availability"));
  ASSERT_TRUE(availabilityLimits.setLowerLimitValue(0.0));
  ASSERT_TRUE(availabilityLimits.setUpperLimitValue(1.0));
  ASSERT_TRUE(wrongSchedule.setScheduleTypeLimits(availabilityLimits));

  EXPECT_FALSE(thermostat.setHeatingSetpointTemperatureSchedule(wrongSchedule));
  EXPECT_FALSE(thermostat.setCoolingSetpointTemperatureSchedule(wrongSchedule));
}

TEST_F(EPModelFixture, ThermostatSetpointDualSetpoint_TemperatureDifference_UnattachedRoundTrip) {
  Model model;
  ThermostatSetpointDualSetpoint thermostat(model);

  EXPECT_TRUE(thermostat.isTemperatureDifferenceBetweenCutoutAndSetpointDefaulted());
  EXPECT_DOUBLE_EQ(0.0, thermostat.temperatureDifferenceBetweenCutoutAndSetpoint());

  EXPECT_TRUE(thermostat.setTemperatureDifferenceBetweenCutoutAndSetpoint(1.75));
  EXPECT_FALSE(thermostat.isTemperatureDifferenceBetweenCutoutAndSetpointDefaulted());
  EXPECT_DOUBLE_EQ(1.75, thermostat.temperatureDifferenceBetweenCutoutAndSetpoint());
}

TEST_F(EPModelFixture, ThermostatSetpointDualSetpoint_TemperatureDifference_AttachAndDetachRoundTrip) {
  Model model;
  ThermalZone zone(model);
  ThermostatSetpointDualSetpoint thermostat(model);

  EXPECT_TRUE(thermostat.setTemperatureDifferenceBetweenCutoutAndSetpoint(1.75));
  ASSERT_TRUE(zone.setThermostatSetpointDualSetpoint(thermostat));
  EXPECT_FALSE(zone.isTemperatureDifferenceBetweenCutoutAndSetpointDefaulted());
  EXPECT_DOUBLE_EQ(1.75, zone.temperatureDifferenceBetweenCutoutAndSetpoint());
  EXPECT_FALSE(thermostat.isTemperatureDifferenceBetweenCutoutAndSetpointDefaulted());
  EXPECT_DOUBLE_EQ(1.75, thermostat.temperatureDifferenceBetweenCutoutAndSetpoint());

  EXPECT_TRUE(zone.setTemperatureDifferenceBetweenCutoutAndSetpoint(2.25));
  EXPECT_DOUBLE_EQ(2.25, thermostat.temperatureDifferenceBetweenCutoutAndSetpoint());

  zone.resetThermostatSetpointDualSetpoint();
  EXPECT_FALSE(thermostat.isTemperatureDifferenceBetweenCutoutAndSetpointDefaulted());
  EXPECT_DOUBLE_EQ(2.25, thermostat.temperatureDifferenceBetweenCutoutAndSetpoint());
}

TEST_F(EPModelFixture, ThermostatSetpointDualSetpoint_TemperatureDifference_ReusedAttachedThermostatCarriesLiveValue) {
  Model model;
  ThermalZone zone1(model);
  ThermalZone zone2(model);
  ThermostatSetpointDualSetpoint thermostat(model);

  ASSERT_TRUE(zone1.setThermostatSetpointDualSetpoint(thermostat));
  ASSERT_TRUE(zone1.setTemperatureDifferenceBetweenCutoutAndSetpoint(2.5));

  ASSERT_TRUE(zone2.setThermostat(thermostat));
  ASSERT_TRUE(zone2.thermostatSetpointDualSetpoint());
  EXPECT_DOUBLE_EQ(2.5, zone2.temperatureDifferenceBetweenCutoutAndSetpoint());
  EXPECT_DOUBLE_EQ(2.5, zone2.thermostatSetpointDualSetpoint()->temperatureDifferenceBetweenCutoutAndSetpoint());
  EXPECT_NE(zone1.thermostatSetpointDualSetpoint().get(), zone2.thermostatSetpointDualSetpoint().get());
}

TEST_F(EPModelFixture, ThermostatSetpointDualSetpoint_SingleCoolingImport) {
  Model model;

  openstudio::IdfObject singleCooling(openstudio::IddObjectType::ThermostatSetpoint_SingleCooling);
  singleCooling.setName("Single Cooling");
  auto modelImpl = model.getImpl<detail::Model_Impl>();
  auto objectImpl = modelImpl->createObject(singleCooling, false);
  ASSERT_TRUE(objectImpl);

  auto thermostatImpl = std::dynamic_pointer_cast<detail::ThermostatSetpointDualSetpoint_Impl>(objectImpl);
  ASSERT_TRUE(thermostatImpl);

  EXPECT_EQ("Single Cooling", thermostatImpl->nameString());
  auto type = thermostatImpl->iddObject().type();
  EXPECT_EQ(openstudio::IddObjectType::ThermostatSetpoint_SingleCooling, type.value());
}

TEST_F(EPModelFixture, ThermostatSetpointDualSetpoint_SingleHeatingImport) {
  Model model;

  openstudio::IdfObject singleHeating(openstudio::IddObjectType::ThermostatSetpoint_SingleHeating);
  singleHeating.setName("Single Heating");
  auto modelImpl = model.getImpl<detail::Model_Impl>();
  auto objectImpl = modelImpl->createObject(singleHeating, false);
  ASSERT_TRUE(objectImpl);

  auto thermostatImpl = std::dynamic_pointer_cast<detail::ThermostatSetpointDualSetpoint_Impl>(objectImpl);
  ASSERT_TRUE(thermostatImpl);

  EXPECT_EQ("Single Heating", thermostatImpl->nameString());
  auto type = thermostatImpl->iddObject().type();
  EXPECT_EQ(openstudio::IddObjectType::ThermostatSetpoint_SingleHeating, type.value());
}
