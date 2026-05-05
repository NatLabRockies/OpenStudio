/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../Schedule/ScheduleConstant.hpp"
#include "../ModelObject/ZoneHVACLowTempRadiantConstFlowDesign.hpp"

#include <utilities/idd/ZoneHVAC_LowTemperatureRadiant_ConstantFlow_Design_FieldEnums.hxx>

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, ZoneHVACLowTempRadiantConstFlowDesign_DefaultConstructor) {
  Model model;
  ZoneHVACLowTempRadiantConstFlowDesign design(model);

  EXPECT_EQ(ZoneHVACLowTempRadiantConstFlowDesign::iddObjectType(), design.iddObject().type());
  EXPECT_EQ("ConvectionOnly", design.fluidtoRadiantSurfaceHeatTransferModel());
  EXPECT_EQ("MeanAirTemperature", design.temperatureControlType());
  EXPECT_DOUBLE_EQ(0.013, design.hydronicTubingInsideDiameter());
  EXPECT_DOUBLE_EQ(0.016, design.hydronicTubingOutsideDiameter());
  EXPECT_DOUBLE_EQ(0.35, design.hydronicTubingConductivity());
  EXPECT_DOUBLE_EQ(0.8, design.runningMeanOutdoorDryBulbTemperatureWeightingFactor());
  EXPECT_DOUBLE_EQ(0.9, design.motorEfficiency());
  EXPECT_DOUBLE_EQ(0.0, design.fractionofMotorInefficienciestoFluidStream());
  EXPECT_EQ("SimpleOff", design.condensationControlType());
  EXPECT_DOUBLE_EQ(1.0, design.condensationControlDewpointOffset());
}

TEST_F(EPModelFixture, ZoneHVACLowTempRadiantConstFlowDesign_ScalarAccessors_RoundTrip) {
  Model model;
  ZoneHVACLowTempRadiantConstFlowDesign design(model);
  ScheduleConstant schedule(model);
  ASSERT_TRUE(schedule.setValue(1.0));

  // This EnergyPlus-only companion wrapper is intentionally read-oriented in
  // the public API. Set up persisted storage directly here and verify that the
  // typed getter surface reads it back correctly.
  EXPECT_TRUE(
    design.setPointer(openstudio::ZoneHVAC_LowTemperatureRadiant_ConstantFlow_DesignFields::ChangeoverDelayTimePeriodSchedule, schedule.handle()));
  ASSERT_TRUE(design.changeoverDelayTimePeriodSchedule());
  EXPECT_EQ(schedule.handle(), design.changeoverDelayTimePeriodSchedule()->handle());

  EXPECT_TRUE(
    design.setString(openstudio::ZoneHVAC_LowTemperatureRadiant_ConstantFlow_DesignFields::FluidtoRadiantSurfaceHeatTransferModel, "ISOStandard"));
  EXPECT_EQ("ISOStandard", design.fluidtoRadiantSurfaceHeatTransferModel());

  EXPECT_TRUE(
    design.setString(openstudio::ZoneHVAC_LowTemperatureRadiant_ConstantFlow_DesignFields::TemperatureControlType, "SurfaceFaceTemperature"));
  EXPECT_EQ("SurfaceFaceTemperature", design.temperatureControlType());

  EXPECT_TRUE(design.setString(openstudio::ZoneHVAC_LowTemperatureRadiant_ConstantFlow_DesignFields::CondensationControlType, "VariableOff"));
  EXPECT_EQ("VariableOff", design.condensationControlType());

  EXPECT_TRUE(design.setDouble(openstudio::ZoneHVAC_LowTemperatureRadiant_ConstantFlow_DesignFields::CondensationControlDewpointOffset, 1.5));
  EXPECT_DOUBLE_EQ(1.5, design.condensationControlDewpointOffset());
}
