/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../Schedule/ScheduleConstant.hpp"
#include "../ModelObject/ZoneHVACLowTempRadiantVarFlowDesign.hpp"

#include <utilities/idd/ZoneHVAC_LowTemperatureRadiant_VariableFlow_Design_FieldEnums.hxx>

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, ZoneHVACLowTempRadiantVarFlowDesign_DefaultConstructor) {
  Model model;
  ZoneHVACLowTempRadiantVarFlowDesign design(model);

  EXPECT_EQ(ZoneHVACLowTempRadiantVarFlowDesign::iddObjectType(), design.iddObject().type());
  EXPECT_EQ("ConvectionOnly", design.fluidtoRadiantSurfaceHeatTransferModel());
  EXPECT_EQ("MeanAirTemperature", design.temperatureControlType());
  EXPECT_EQ("HalfFlowPower", design.setpointControlType());
  EXPECT_DOUBLE_EQ(0.013, design.hydronicTubingInsideDiameter());
  EXPECT_DOUBLE_EQ(0.016, design.hydronicTubingOutsideDiameter());
  EXPECT_DOUBLE_EQ(0.35, design.hydronicTubingConductivity());
  EXPECT_EQ("HeatingDesignCapacity", design.heatingDesignCapacityMethod());
  EXPECT_DOUBLE_EQ(1.0, design.fractionofAutosizedHeatingDesignCapacity());
  EXPECT_DOUBLE_EQ(0.5, design.heatingControlThrottlingRange());
  EXPECT_EQ("CoolingDesignCapacity", design.coolingDesignCapacityMethod());
  EXPECT_DOUBLE_EQ(0.5, design.coolingControlThrottlingRange());
  EXPECT_EQ("SimpleOff", design.condensationControlType());
  EXPECT_DOUBLE_EQ(1.0, design.condensationControlDewpointOffset());
}

TEST_F(EPModelFixture, ZoneHVACLowTempRadiantVarFlowDesign_ScalarAccessors_RoundTrip) {
  Model model;
  ZoneHVACLowTempRadiantVarFlowDesign design(model);
  ScheduleConstant schedule(model);
  ASSERT_TRUE(schedule.setValue(1.0));

  // This EnergyPlus-only companion wrapper is intentionally read-oriented in
  // the public API. Set up persisted storage directly here and verify that the
  // typed getter surface reads it back correctly.
  EXPECT_TRUE(
    design.setPointer(openstudio::ZoneHVAC_LowTemperatureRadiant_VariableFlow_DesignFields::HeatingControlTemperatureScheduleName, schedule.handle()));
  ASSERT_TRUE(design.heatingControlTemperatureSchedule());
  EXPECT_EQ(schedule.handle(), design.heatingControlTemperatureSchedule()->handle());

  EXPECT_TRUE(
    design.setPointer(openstudio::ZoneHVAC_LowTemperatureRadiant_VariableFlow_DesignFields::CoolingControlTemperatureScheduleName, schedule.handle()));
  ASSERT_TRUE(design.coolingControlTemperatureSchedule());
  EXPECT_EQ(schedule.handle(), design.coolingControlTemperatureSchedule()->handle());

  EXPECT_TRUE(
    design.setPointer(openstudio::ZoneHVAC_LowTemperatureRadiant_VariableFlow_DesignFields::ChangeoverDelayTimePeriodSchedule, schedule.handle()));
  ASSERT_TRUE(design.changeoverDelayTimePeriodSchedule());
  EXPECT_EQ(schedule.handle(), design.changeoverDelayTimePeriodSchedule()->handle());

  EXPECT_TRUE(
    design.setString(openstudio::ZoneHVAC_LowTemperatureRadiant_VariableFlow_DesignFields::FluidtoRadiantSurfaceHeatTransferModel, "ISOStandard"));
  EXPECT_EQ("ISOStandard", design.fluidtoRadiantSurfaceHeatTransferModel());

  EXPECT_TRUE(design.setString(openstudio::ZoneHVAC_LowTemperatureRadiant_VariableFlow_DesignFields::TemperatureControlType,
                               "SurfaceFaceTemperature"));
  EXPECT_EQ("SurfaceFaceTemperature", design.temperatureControlType());

  EXPECT_TRUE(design.setString(openstudio::ZoneHVAC_LowTemperatureRadiant_VariableFlow_DesignFields::SetpointControlType, "ZeroFlowPower"));
  EXPECT_EQ("ZeroFlowPower", design.setpointControlType());

  EXPECT_TRUE(
    design.setString(openstudio::ZoneHVAC_LowTemperatureRadiant_VariableFlow_DesignFields::CondensationControlType, "VariableOff"));
  EXPECT_EQ("VariableOff", design.condensationControlType());

  EXPECT_TRUE(
    design.setDouble(openstudio::ZoneHVAC_LowTemperatureRadiant_VariableFlow_DesignFields::CondensationControlDewpointOffset, 1.5));
  EXPECT_DOUBLE_EQ(1.5, design.condensationControlDewpointOffset());
}
