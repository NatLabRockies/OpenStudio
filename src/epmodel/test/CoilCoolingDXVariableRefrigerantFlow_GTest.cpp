/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../Curve/CurveBiquadratic.hpp"
#include "../Curve/CurveBiquadratic_Impl.hpp"
#include "../Curve/CurveQuadratic.hpp"
#include "../Curve/CurveQuadratic_Impl.hpp"
#include "../Schedule/ScheduleConstant.hpp"
#include "../StraightComponent/CoilCoolingDXVariableRefrigerantFlow.hpp"
#include "../StraightComponent/Node.hpp"
#include "../StraightComponent/StraightComponent.hpp"

#include <utilities/idd/Coil_Cooling_DX_VariableRefrigerantFlow_FieldEnums.hxx>

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, CoilCoolingDXVariableRefrigerantFlow_DefaultConstructor) {
  Model model;
  CoilCoolingDXVariableRefrigerantFlow coil(model);
  EXPECT_EQ(CoilCoolingDXVariableRefrigerantFlow::iddObjectType(), coil.iddObject().type());
  EXPECT_FALSE(coil.nameString().empty());
  EXPECT_EQ(model.alwaysOnDiscreteSchedule().handle(), coil.availabilitySchedule().handle());
  EXPECT_TRUE(coil.isRatedTotalCoolingCapacityAutosized());
  EXPECT_TRUE(coil.isRatedSensibleHeatRatioAutosized());
  EXPECT_TRUE(coil.isRatedAirFlowRateAutosized());

  auto temperatureCurve = coil.coolingCapacityRatioModifierFunctionofTemperatureCurve().optionalCast<CurveBiquadratic>();
  ASSERT_TRUE(temperatureCurve);
  EXPECT_DOUBLE_EQ(5.85884077803259E-02, temperatureCurve->coefficient1Constant());
  EXPECT_DOUBLE_EQ(5.87396532718384E-02, temperatureCurve->coefficient2x());
  EXPECT_DOUBLE_EQ(-2.10274979759697E-04, temperatureCurve->coefficient3xPOW2());
  EXPECT_DOUBLE_EQ(1.09370473889647E-02, temperatureCurve->coefficient4y());
  EXPECT_DOUBLE_EQ(-0.0001219549, temperatureCurve->coefficient5yPOW2());
  EXPECT_DOUBLE_EQ(-0.0005246615, temperatureCurve->coefficient6xTIMESY());
  EXPECT_DOUBLE_EQ(15.0, temperatureCurve->minimumValueofx());
  EXPECT_DOUBLE_EQ(23.89, temperatureCurve->maximumValueofx());
  EXPECT_DOUBLE_EQ(20.0, temperatureCurve->minimumValueofy());
  EXPECT_DOUBLE_EQ(43.33, temperatureCurve->maximumValueofy());
  EXPECT_DOUBLE_EQ(0.8083, temperatureCurve->minimumCurveOutput().get());
  EXPECT_DOUBLE_EQ(1.2583, temperatureCurve->maximumCurveOutput().get());

  auto flowCurve = coil.coolingCapacityModifierCurveFunctionofFlowFraction().optionalCast<CurveQuadratic>();
  ASSERT_TRUE(flowCurve);
  EXPECT_DOUBLE_EQ(0.8, flowCurve->coefficient1Constant());
  EXPECT_DOUBLE_EQ(0.2, flowCurve->coefficient2x());
  EXPECT_DOUBLE_EQ(0.0, flowCurve->coefficient3xPOW2());
  EXPECT_DOUBLE_EQ(0.5, flowCurve->minimumValueofx());
  EXPECT_DOUBLE_EQ(1.5, flowCurve->maximumValueofx());
}

TEST_F(EPModelFixture, CoilCoolingDXVariableRefrigerantFlow_ScalarAccessors_RoundTrip) {
  Model model;
  CoilCoolingDXVariableRefrigerantFlow coil(model);

  EXPECT_TRUE(coil.setRatedTotalCoolingCapacity(12345.0));
  ASSERT_TRUE(coil.ratedTotalCoolingCapacity());
  EXPECT_DOUBLE_EQ(12345.0, coil.ratedTotalCoolingCapacity().get());
  EXPECT_FALSE(coil.isRatedTotalCoolingCapacityAutosized());
  coil.autosizeRatedTotalCoolingCapacity();
  EXPECT_TRUE(coil.isRatedTotalCoolingCapacityAutosized());

  EXPECT_TRUE(coil.setRatedSensibleHeatRatio(0.71));
  ASSERT_TRUE(coil.ratedSensibleHeatRatio());
  EXPECT_DOUBLE_EQ(0.71, coil.ratedSensibleHeatRatio().get());
  EXPECT_FALSE(coil.isRatedSensibleHeatRatioAutosized());
  coil.autosizeRatedSensibleHeatRatio();
  EXPECT_TRUE(coil.isRatedSensibleHeatRatioAutosized());

  EXPECT_TRUE(coil.setRatedAirFlowRate(1.35));
  ASSERT_TRUE(coil.ratedAirFlowRate());
  EXPECT_DOUBLE_EQ(1.35, coil.ratedAirFlowRate().get());
  EXPECT_FALSE(coil.isRatedAirFlowRateAutosized());
  coil.autosizeRatedAirFlowRate();
  EXPECT_TRUE(coil.isRatedAirFlowRateAutosized());
}

TEST_F(EPModelFixture, CoilCoolingDXVariableRefrigerantFlow_RelationshipSetters_RoundTrip) {
  Model model;
  CoilCoolingDXVariableRefrigerantFlow coil(model);

  ScheduleConstant schedule(model);
  EXPECT_TRUE(schedule.setValue(0.25));
  EXPECT_TRUE(coil.setAvailabilitySchedule(schedule));
  EXPECT_EQ(schedule.handle(), coil.availabilitySchedule().handle());

  CurveBiquadratic temperatureCurve(model);
  EXPECT_TRUE(temperatureCurve.setCoefficient1Constant(1.1));
  EXPECT_TRUE(temperatureCurve.setCoefficient2x(1.2));
  EXPECT_TRUE(temperatureCurve.setCoefficient3xPOW2(1.3));
  EXPECT_TRUE(temperatureCurve.setCoefficient4y(1.4));
  EXPECT_TRUE(temperatureCurve.setCoefficient5yPOW2(1.5));
  EXPECT_TRUE(temperatureCurve.setCoefficient6xTIMESY(1.6));
  EXPECT_TRUE(temperatureCurve.setMinimumValueofx(2.1));
  EXPECT_TRUE(temperatureCurve.setMaximumValueofx(2.2));
  EXPECT_TRUE(temperatureCurve.setMinimumValueofy(2.3));
  EXPECT_TRUE(temperatureCurve.setMaximumValueofy(2.4));
  EXPECT_TRUE(temperatureCurve.setMinimumCurveOutput(2.5));
  EXPECT_TRUE(temperatureCurve.setMaximumCurveOutput(2.6));
  EXPECT_TRUE(coil.setCoolingCapacityRatioModifierFunctionofTemperatureCurve(temperatureCurve));
  auto reboundTemperatureCurve = coil.coolingCapacityRatioModifierFunctionofTemperatureCurve().optionalCast<CurveBiquadratic>();
  ASSERT_TRUE(reboundTemperatureCurve);
  EXPECT_DOUBLE_EQ(1.1, reboundTemperatureCurve->coefficient1Constant());
  EXPECT_DOUBLE_EQ(1.6, reboundTemperatureCurve->coefficient6xTIMESY());

  CurveQuadratic flowCurve(model);
  EXPECT_TRUE(flowCurve.setCoefficient1Constant(3.1));
  EXPECT_TRUE(flowCurve.setCoefficient2x(3.2));
  EXPECT_TRUE(flowCurve.setCoefficient3xPOW2(3.3));
  EXPECT_TRUE(flowCurve.setMinimumValueofx(3.4));
  EXPECT_TRUE(flowCurve.setMaximumValueofx(3.5));
  EXPECT_TRUE(coil.setCoolingCapacityModifierCurveFunctionofFlowFraction(flowCurve));
  auto reboundFlowCurve = coil.coolingCapacityModifierCurveFunctionofFlowFraction().optionalCast<CurveQuadratic>();
  ASSERT_TRUE(reboundFlowCurve);
  EXPECT_DOUBLE_EQ(3.1, reboundFlowCurve->coefficient1Constant());
  EXPECT_DOUBLE_EQ(3.3, reboundFlowCurve->coefficient3xPOW2());
}

TEST_F(EPModelFixture, CoilCoolingDXVariableRefrigerantFlow_StraightComponentPortsWithoutLoopPlacement) {
  Model model;
  CoilCoolingDXVariableRefrigerantFlow coil(model);
  Node node(model);

  EXPECT_TRUE(coil.optionalCast<StraightComponent>());
  EXPECT_EQ(openstudio::Coil_Cooling_DX_VariableRefrigerantFlowFields::CoilAirInletNode, coil.inletPort());
  EXPECT_EQ(openstudio::Coil_Cooling_DX_VariableRefrigerantFlowFields::CoilAirOutletNode, coil.outletPort());
  EXPECT_FALSE(coil.addToNode(node));
}
