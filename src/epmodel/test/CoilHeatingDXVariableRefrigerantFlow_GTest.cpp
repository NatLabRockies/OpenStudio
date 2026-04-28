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
#include "../StraightComponent/CoilHeatingDXVariableRefrigerantFlow.hpp"
#include "../StraightComponent/Node.hpp"
#include "../StraightComponent/StraightComponent.hpp"

#include <utilities/idd/Coil_Heating_DX_VariableRefrigerantFlow_FieldEnums.hxx>

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, CoilHeatingDXVariableRefrigerantFlow_DefaultConstructor) {
  Model model;
  CoilHeatingDXVariableRefrigerantFlow coil(model);
  EXPECT_EQ(CoilHeatingDXVariableRefrigerantFlow::iddObjectType(), coil.iddObject().type());
  EXPECT_FALSE(coil.nameString().empty());
  EXPECT_EQ(model.alwaysOnDiscreteSchedule().handle(), coil.availabilitySchedule().handle());
  EXPECT_TRUE(coil.isRatedTotalHeatingCapacityAutosized());
  EXPECT_TRUE(coil.isRatedAirFlowRateAutosized());

  auto temperatureCurve = coil.heatingCapacityRatioModifierFunctionofTemperatureCurve().optionalCast<CurveBiquadratic>();
  ASSERT_TRUE(temperatureCurve);
  EXPECT_DOUBLE_EQ(0.375443994956127, temperatureCurve->coefficient1Constant());
  EXPECT_DOUBLE_EQ(6.68190645147821E-02, temperatureCurve->coefficient2x());
  EXPECT_DOUBLE_EQ(-1.94171026482001E-03, temperatureCurve->coefficient3xPOW2());
  EXPECT_DOUBLE_EQ(4.42618420640187E-02, temperatureCurve->coefficient4y());
  EXPECT_DOUBLE_EQ(-0.0004009578, temperatureCurve->coefficient5yPOW2());
  EXPECT_DOUBLE_EQ(-0.0014819801, temperatureCurve->coefficient6xTIMESY());
  EXPECT_DOUBLE_EQ(21.11, temperatureCurve->minimumValueofx());
  EXPECT_DOUBLE_EQ(27.22, temperatureCurve->maximumValueofx());
  EXPECT_DOUBLE_EQ(-15.0, temperatureCurve->minimumValueofy());
  EXPECT_DOUBLE_EQ(18.33, temperatureCurve->maximumValueofy());
  EXPECT_DOUBLE_EQ(0.6074, temperatureCurve->minimumCurveOutput().get());
  EXPECT_DOUBLE_EQ(1.0, temperatureCurve->maximumCurveOutput().get());

  auto flowCurve = coil.heatingCapacityModifierFunctionofFlowFractionCurve().optionalCast<CurveQuadratic>();
  ASSERT_TRUE(flowCurve);
  EXPECT_DOUBLE_EQ(0.8, flowCurve->coefficient1Constant());
  EXPECT_DOUBLE_EQ(0.2, flowCurve->coefficient2x());
  EXPECT_DOUBLE_EQ(0.0, flowCurve->coefficient3xPOW2());
  EXPECT_DOUBLE_EQ(0.5, flowCurve->minimumValueofx());
  EXPECT_DOUBLE_EQ(1.5, flowCurve->maximumValueofx());

  const auto children = coil.children();
  ASSERT_EQ(2u, children.size());
  EXPECT_EQ(coil.heatingCapacityRatioModifierFunctionofTemperatureCurve().handle(), children[0].handle());
  EXPECT_EQ(coil.heatingCapacityModifierFunctionofFlowFractionCurve().handle(), children[1].handle());
}

TEST_F(EPModelFixture, CoilHeatingDXVariableRefrigerantFlow_ScalarAccessors_RoundTrip) {
  Model model;
  CoilHeatingDXVariableRefrigerantFlow coil(model);

  EXPECT_TRUE(coil.setRatedTotalHeatingCapacity(12345.0));
  ASSERT_TRUE(coil.ratedTotalHeatingCapacity());
  EXPECT_DOUBLE_EQ(12345.0, coil.ratedTotalHeatingCapacity().get());
  EXPECT_FALSE(coil.isRatedTotalHeatingCapacityAutosized());
  coil.autosizeRatedTotalHeatingCapacity();
  EXPECT_TRUE(coil.isRatedTotalHeatingCapacityAutosized());

  EXPECT_TRUE(coil.setRatedAirFlowRate(1.35));
  ASSERT_TRUE(coil.ratedAirFlowRate());
  EXPECT_DOUBLE_EQ(1.35, coil.ratedAirFlowRate().get());
  EXPECT_FALSE(coil.isRatedAirFlowRateAutosized());
  coil.autosizeRatedAirFlowRate();
  EXPECT_TRUE(coil.isRatedAirFlowRateAutosized());
}

TEST_F(EPModelFixture, CoilHeatingDXVariableRefrigerantFlow_RelationshipSetters_RoundTrip) {
  Model model;
  CoilHeatingDXVariableRefrigerantFlow coil(model);

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
  EXPECT_TRUE(coil.setHeatingCapacityRatioModifierFunctionofTemperatureCurve(temperatureCurve));
  auto reboundTemperatureCurve = coil.heatingCapacityRatioModifierFunctionofTemperatureCurve().optionalCast<CurveBiquadratic>();
  ASSERT_TRUE(reboundTemperatureCurve);
  EXPECT_DOUBLE_EQ(1.1, reboundTemperatureCurve->coefficient1Constant());
  EXPECT_DOUBLE_EQ(1.6, reboundTemperatureCurve->coefficient6xTIMESY());

  CurveQuadratic flowCurve(model);
  EXPECT_TRUE(flowCurve.setCoefficient1Constant(3.1));
  EXPECT_TRUE(flowCurve.setCoefficient2x(3.2));
  EXPECT_TRUE(flowCurve.setCoefficient3xPOW2(3.3));
  EXPECT_TRUE(flowCurve.setMinimumValueofx(3.4));
  EXPECT_TRUE(flowCurve.setMaximumValueofx(3.5));
  EXPECT_TRUE(coil.setHeatingCapacityModifierFunctionofFlowFractionCurve(flowCurve));
  auto reboundFlowCurve = coil.heatingCapacityModifierFunctionofFlowFractionCurve().optionalCast<CurveQuadratic>();
  ASSERT_TRUE(reboundFlowCurve);
  EXPECT_DOUBLE_EQ(3.1, reboundFlowCurve->coefficient1Constant());
  EXPECT_DOUBLE_EQ(3.3, reboundFlowCurve->coefficient3xPOW2());

  const auto children = coil.children();
  ASSERT_EQ(2u, children.size());
  EXPECT_EQ(temperatureCurve.handle(), children[0].handle());
  EXPECT_EQ(flowCurve.handle(), children[1].handle());
}

TEST_F(EPModelFixture, CoilHeatingDXVariableRefrigerantFlow_StraightComponentPortsWithoutLoopPlacement) {
  Model model;
  CoilHeatingDXVariableRefrigerantFlow coil(model);
  Node node(model);

  EXPECT_TRUE(coil.optionalCast<StraightComponent>());
  EXPECT_EQ(openstudio::Coil_Heating_DX_VariableRefrigerantFlowFields::CoilAirInletNode, coil.inletPort());
  EXPECT_EQ(openstudio::Coil_Heating_DX_VariableRefrigerantFlowFields::CoilAirOutletNode, coil.outletPort());
  EXPECT_FALSE(coil.addToNode(node));
}
