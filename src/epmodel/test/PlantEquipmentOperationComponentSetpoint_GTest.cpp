/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../PlantEquipmentOperationScheme/PlantEquipmentOperationComponentSetpoint.hpp"

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, PlantEquipmentOperationComponentSetpoint_DefaultConstructor) {
  Model model;
  PlantEquipmentOperationComponentSetpoint setpoint(model);

  EXPECT_EQ(PlantEquipmentOperationComponentSetpoint::iddObjectType(), setpoint.iddObject().type());

  auto operationTypeValues = PlantEquipmentOperationComponentSetpoint::component1OperationTypeValues();
  ASSERT_FALSE(operationTypeValues.empty());
  EXPECT_EQ(operationTypeValues.front(), setpoint.component1OperationType());

  const auto defaultFlowRate = setpoint.component1FlowRate();
  ASSERT_TRUE(defaultFlowRate);
  EXPECT_DOUBLE_EQ(0.0, *defaultFlowRate);
  EXPECT_FALSE(setpoint.isComponent1FlowRateAutosized());
}

TEST_F(EPModelFixture, PlantEquipmentOperationComponentSetpoint_ScalarAccessors_RoundTrip) {
  Model model;
  PlantEquipmentOperationComponentSetpoint setpoint(model);

  EXPECT_TRUE(setpoint.setComponent1FlowRate(2.25));
  auto updatedFlowRate = setpoint.component1FlowRate();
  ASSERT_TRUE(updatedFlowRate);
  EXPECT_DOUBLE_EQ(2.25, *updatedFlowRate);
  EXPECT_FALSE(setpoint.isComponent1FlowRateAutosized());

  setpoint.autosizeComponent1FlowRate();
  EXPECT_TRUE(setpoint.isComponent1FlowRateAutosized());
  EXPECT_FALSE(setpoint.component1FlowRate());

  auto operationTypeValues = PlantEquipmentOperationComponentSetpoint::component1OperationTypeValues();
  ASSERT_GE(operationTypeValues.size(), 2u);
  EXPECT_TRUE(setpoint.setComponent1OperationType(operationTypeValues[1]));
  EXPECT_EQ(operationTypeValues[1], setpoint.component1OperationType());
}
