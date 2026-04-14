/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../Curve/CurveBiquadratic.hpp"
#include "../ParentObject/CoilWaterHeatingAirToWaterHeatPumpVariableSpeedSpeedData.hpp"

#include <utilities/idd/IddEnums.hxx>

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, CoilWaterHeatingAirToWaterHeatPumpVariableSpeedSpeedData_DefaultConstructor) {
  Model model;
  CoilWaterHeatingAirToWaterHeatPumpVariableSpeedSpeedData speed(model);

  EXPECT_EQ(CoilWaterHeatingAirToWaterHeatPumpVariableSpeedSpeedData::iddObjectType(), speed.iddObject().type());
  EXPECT_DOUBLE_EQ(400.0, speed.ratedWaterHeatingCapacity());
  EXPECT_DOUBLE_EQ(5.0, speed.ratedWaterHeatingCOP());
  EXPECT_DOUBLE_EQ(0.8, speed.ratedSensibleHeatRatio());
  EXPECT_DOUBLE_EQ(0.02014, speed.referenceUnitRatedAirFlowRate());
  EXPECT_DOUBLE_EQ(0.000018, speed.referenceUnitRatedWaterFlowRate());
  EXPECT_DOUBLE_EQ(10.0, speed.referenceUnitWaterPumpInputPowerAtRatedConditions());
  EXPECT_EQ(openstudio::IddObjectType::Curve_Biquadratic, speed.totalWaterHeatingCapacityFunctionofTemperatureCurve().iddObject().type().value());
  EXPECT_EQ(openstudio::IddObjectType::Curve_Cubic, speed.totalWaterHeatingCapacityFunctionofAirFlowFractionCurve().iddObject().type().value());
  EXPECT_EQ(openstudio::IddObjectType::Curve_Cubic, speed.totalWaterHeatingCapacityFunctionofWaterFlowFractionCurve().iddObject().type().value());
  EXPECT_EQ(openstudio::IddObjectType::Curve_Biquadratic, speed.cOPFunctionofTemperatureCurve().iddObject().type().value());
  EXPECT_EQ(openstudio::IddObjectType::Curve_Cubic, speed.cOPFunctionofAirFlowFractionCurve().iddObject().type().value());
  EXPECT_EQ(openstudio::IddObjectType::Curve_Cubic, speed.cOPFunctionofWaterFlowFractionCurve().iddObject().type().value());
  EXPECT_EQ(6u, speed.children().size());
}

TEST_F(EPModelFixture, CoilWaterHeatingAirToWaterHeatPumpVariableSpeedSpeedData_SettersRoundTrip) {
  Model model;
  CoilWaterHeatingAirToWaterHeatPumpVariableSpeedSpeedData speed(model);
  CurveBiquadratic replacement(model);

  EXPECT_TRUE(speed.setRatedWaterHeatingCapacity(450.0));
  EXPECT_TRUE(speed.setRatedWaterHeatingCOP(4.9));
  EXPECT_TRUE(speed.setRatedSensibleHeatRatio(0.75));
  EXPECT_TRUE(speed.setReferenceUnitRatedAirFlowRate(0.025));
  EXPECT_TRUE(speed.setReferenceUnitRatedWaterFlowRate(0.000025));
  EXPECT_TRUE(speed.setReferenceUnitWaterPumpInputPowerAtRatedConditions(12.0));
  EXPECT_TRUE(speed.setTotalWaterHeatingCapacityFunctionofTemperatureCurve(replacement));
  EXPECT_TRUE(speed.setCOPFunctionofTemperatureCurve(replacement));

  EXPECT_DOUBLE_EQ(450.0, speed.ratedWaterHeatingCapacity());
  EXPECT_DOUBLE_EQ(4.9, speed.ratedWaterHeatingCOP());
  EXPECT_DOUBLE_EQ(0.75, speed.ratedSensibleHeatRatio());
  EXPECT_DOUBLE_EQ(0.025, speed.referenceUnitRatedAirFlowRate());
  EXPECT_DOUBLE_EQ(0.000025, speed.referenceUnitRatedWaterFlowRate());
  EXPECT_DOUBLE_EQ(12.0, speed.referenceUnitWaterPumpInputPowerAtRatedConditions());
  EXPECT_EQ(replacement, speed.totalWaterHeatingCapacityFunctionofTemperatureCurve());
  EXPECT_EQ(replacement, speed.cOPFunctionofTemperatureCurve());
}
