/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../ModelObject/PlantEquipmentOperationThermalEnergyStorage.hpp"

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, PlantEquipmentOperationThermalEnergyStorage_DefaultConstructor) {
  Model model;
  PlantEquipmentOperationThermalEnergyStorage scheme(model);

  EXPECT_EQ(PlantEquipmentOperationThermalEnergyStorage::iddObjectType(), scheme.iddObject().type());

  EXPECT_FALSE(scheme.component1FlowRate());
  EXPECT_FALSE(scheme.component2FlowRate());
  EXPECT_FALSE(scheme.component2ObjectType());
  EXPECT_FALSE(scheme.component2OperationType());

  auto objectTypeValues = PlantEquipmentOperationThermalEnergyStorage::component1ObjectTypeValues();
  ASSERT_FALSE(objectTypeValues.empty());
  auto operationTypeValues = PlantEquipmentOperationThermalEnergyStorage::component1OperationTypeValues();
  ASSERT_FALSE(operationTypeValues.empty());
}

TEST_F(EPModelFixture, PlantEquipmentOperationThermalEnergyStorage_ScalarAccessors_RoundTrip) {
  Model model;
  PlantEquipmentOperationThermalEnergyStorage scheme(model);

  EXPECT_TRUE(scheme.setNonChargingChilledWaterTemperature(5.5));
  EXPECT_DOUBLE_EQ(5.5, scheme.nonChargingChilledWaterTemperature());
  EXPECT_TRUE(scheme.setChargingChilledWaterTemperature(1.25));
  EXPECT_DOUBLE_EQ(1.25, scheme.chargingChilledWaterTemperature());

  auto objectTypeValues = PlantEquipmentOperationThermalEnergyStorage::component1ObjectTypeValues();
  ASSERT_GE(objectTypeValues.size(), 2u);
  EXPECT_TRUE(scheme.setComponent1ObjectType(objectTypeValues[1]));
  EXPECT_EQ(objectTypeValues[1], scheme.component1ObjectType());

  auto operationTypeValues = PlantEquipmentOperationThermalEnergyStorage::component1OperationTypeValues();
  ASSERT_GE(operationTypeValues.size(), 2u);
  EXPECT_TRUE(scheme.setComponent1OperationType(operationTypeValues[1]));
  EXPECT_EQ(operationTypeValues[1], scheme.component1OperationType());

  EXPECT_TRUE(scheme.setComponent1FlowRate(2.4));
  auto component1Flow = scheme.component1FlowRate();
  ASSERT_TRUE(component1Flow);
  EXPECT_DOUBLE_EQ(2.4, *component1Flow);
  EXPECT_FALSE(scheme.isComponent1FlowRateAutosized());

  scheme.autosizeComponent1FlowRate();
  EXPECT_TRUE(scheme.isComponent1FlowRateAutosized());
  EXPECT_FALSE(scheme.component1FlowRate());

  auto component2ObjectTypeValues = PlantEquipmentOperationThermalEnergyStorage::component2ObjectTypeValues();
  ASSERT_FALSE(component2ObjectTypeValues.empty());
  auto component2OperationTypeValues = PlantEquipmentOperationThermalEnergyStorage::component2OperationTypeValues();
  ASSERT_FALSE(component2OperationTypeValues.empty());

  EXPECT_TRUE(scheme.setComponent2ObjectType(component2ObjectTypeValues[0]));
  auto component2ObjectType = scheme.component2ObjectType();
  ASSERT_TRUE(component2ObjectType);
  EXPECT_EQ(component2ObjectTypeValues[0], *component2ObjectType);
  EXPECT_TRUE(scheme.setComponent2OperationType(component2OperationTypeValues[0]));
  auto component2OperationType = scheme.component2OperationType();
  ASSERT_TRUE(component2OperationType);
  EXPECT_EQ(component2OperationTypeValues[0], *component2OperationType);
  EXPECT_TRUE(scheme.setComponent2FlowRate(1.15));
  auto component2Flow = scheme.component2FlowRate();
  ASSERT_TRUE(component2Flow);
  EXPECT_DOUBLE_EQ(1.15, *component2Flow);

  scheme.resetComponent2FlowRate();
  EXPECT_FALSE(scheme.component2FlowRate());

  scheme.resetComponent2ObjectType();
  auto resetComponent2Object = scheme.component2ObjectType();
  ASSERT_TRUE(resetComponent2Object);
  EXPECT_TRUE(resetComponent2Object->empty());

  scheme.resetComponent2OperationType();
  auto resetComponent2Operation = scheme.component2OperationType();
  ASSERT_TRUE(resetComponent2Operation);
  EXPECT_TRUE(resetComponent2Operation->empty());
}
