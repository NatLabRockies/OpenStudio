/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include <algorithm>

#include "EPModelFixture.hpp"
#include "../Curve/Curve.hpp"
#include "../Curve/CurveBiquadratic.hpp"
#include "../ParentObject/CoilWaterHeatingAirToWaterHeatPumpVariableSpeedSpeedData.hpp"
#include "../ParentObject/CoilWaterHeatingAirToWaterHeatPumpVariableSpeedSpeedData_Impl.hpp"
#include "../WaterToAirComponent/CoilWaterHeatingAirToWaterHeatPumpVariableSpeed.hpp"

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

TEST_F(EPModelFixture, CoilWaterHeatingAirToWaterHeatPumpVariableSpeedSpeedData_DetachesWhenParentRemovesRows) {
  Model model;
  CoilWaterHeatingAirToWaterHeatPumpVariableSpeed coil(model);
  CoilWaterHeatingAirToWaterHeatPumpVariableSpeedSpeedData speed(model);

  auto speedImpl = speed.getImpl<detail::CoilWaterHeatingAirToWaterHeatPumpVariableSpeedSpeedData_Impl>();
  ASSERT_FALSE(speedImpl->parent());
  ASSERT_FALSE(speedImpl->attachedSpeedIndex());

  ASSERT_TRUE(speed.setRatedWaterHeatingCOP(5.4));
  ASSERT_TRUE(coil.addSpeed(speed));
  ASSERT_TRUE(speedImpl->parent());
  ASSERT_TRUE(speedImpl->attachedSpeedIndex());
  EXPECT_EQ(coil.handle(), speedImpl->parent()->handle());
  EXPECT_EQ(0u, speedImpl->attachedSpeedIndex().get());
  EXPECT_DOUBLE_EQ(5.4, coil.speeds().front().ratedWaterHeatingCOP());

  coil.removeAllSpeeds();

  EXPECT_FALSE(speedImpl->parent());
  EXPECT_FALSE(speedImpl->attachedSpeedIndex());
  EXPECT_TRUE(coil.speeds().empty());
  EXPECT_DOUBLE_EQ(5.4, speed.ratedWaterHeatingCOP());
}

TEST_F(EPModelFixture, CoilWaterHeatingAirToWaterHeatPumpVariableSpeedSpeedData_RemoveDeletesDetachedTransientWrapper) {
  Model model;
  CoilWaterHeatingAirToWaterHeatPumpVariableSpeedSpeedData speed(model);
  const auto speedHandle = speed.handle();

  EXPECT_EQ(1u, model.getConcreteModelObjects<CoilWaterHeatingAirToWaterHeatPumpVariableSpeedSpeedData>(true).size());
  EXPECT_EQ(2u, model.getObjectsByType(openstudio::IddObjectType::Curve_Biquadratic, true).size());
  EXPECT_EQ(1u, model.getObjectsByType(openstudio::IddObjectType::Curve_Cubic, true).size());

  speed.remove();

  const auto remainingSpeeds = model.getConcreteModelObjects<CoilWaterHeatingAirToWaterHeatPumpVariableSpeedSpeedData>(true);
  EXPECT_TRUE(std::none_of(remainingSpeeds.begin(), remainingSpeeds.end(), [&](const auto& candidate) { return candidate.handle() == speedHandle; }));
  EXPECT_TRUE(remainingSpeeds.empty());
  EXPECT_TRUE(model.getObjectsByType(openstudio::IddObjectType::Curve_Biquadratic, true).empty());
  EXPECT_TRUE(model.getObjectsByType(openstudio::IddObjectType::Curve_Cubic, true).empty());
}
