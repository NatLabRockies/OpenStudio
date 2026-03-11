/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../Model.hpp"
#include "../Model_Impl.hpp"
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
