/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../Curve/CurveQuadratic.hpp"
#include "../Curve/CurveQuadratic_Impl.hpp"
#include "../Schedule/ScheduleConstant.hpp"
#include "../StraightComponent/CoilHeatingDXVariableRefrigerantFlowFluidTemperatureControl.hpp"
#include "../StraightComponent/Node.hpp"
#include "../StraightComponent/StraightComponent.hpp"

#include <utilities/idd/Coil_Heating_DX_VariableRefrigerantFlow_FluidTemperatureControl_FieldEnums.hxx>

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, CoilHeatingDXVariableRefrigerantFlowFluidTemperatureControl_DefaultConstructor) {
  Model model;
  CoilHeatingDXVariableRefrigerantFlowFluidTemperatureControl coil(model);
  EXPECT_EQ(CoilHeatingDXVariableRefrigerantFlowFluidTemperatureControl::iddObjectType(), coil.iddObject().type());
  EXPECT_FALSE(coil.nameString().empty());
  EXPECT_EQ(model.alwaysOnDiscreteSchedule().handle(), coil.availabilitySchedule().handle());
  EXPECT_TRUE(coil.isRatedTotalHeatingCapacityAutosized());
  EXPECT_DOUBLE_EQ(5.0, coil.indoorUnitReferenceSubcooling());

  auto curve = coil.indoorUnitCondensingTemperatureFunctionofSubcoolingCurve().optionalCast<CurveQuadratic>();
  ASSERT_TRUE(curve);
  EXPECT_DOUBLE_EQ(-1.85, curve->coefficient1Constant());
  EXPECT_DOUBLE_EQ(0.411, curve->coefficient2x());
  EXPECT_DOUBLE_EQ(0.0196, curve->coefficient3xPOW2());
  EXPECT_DOUBLE_EQ(0.0, curve->minimumValueofx());
  EXPECT_DOUBLE_EQ(20.0, curve->maximumValueofx());

  const auto children = coil.children();
  ASSERT_EQ(1u, children.size());
  EXPECT_EQ(coil.indoorUnitCondensingTemperatureFunctionofSubcoolingCurve().handle(), children[0].handle());
}

TEST_F(EPModelFixture, CoilHeatingDXVariableRefrigerantFlowFluidTemperatureControl_ScalarAccessors_RoundTrip) {
  Model model;
  CoilHeatingDXVariableRefrigerantFlowFluidTemperatureControl coil(model);

  EXPECT_TRUE(coil.setRatedTotalHeatingCapacity(12345.0));
  ASSERT_TRUE(coil.ratedTotalHeatingCapacity());
  EXPECT_DOUBLE_EQ(12345.0, coil.ratedTotalHeatingCapacity().get());
  EXPECT_FALSE(coil.isRatedTotalHeatingCapacityAutosized());
  coil.autosizeRatedTotalHeatingCapacity();
  EXPECT_TRUE(coil.isRatedTotalHeatingCapacityAutosized());

  EXPECT_TRUE(coil.setIndoorUnitReferenceSubcooling(7.5));
  EXPECT_DOUBLE_EQ(7.5, coil.indoorUnitReferenceSubcooling());
}

TEST_F(EPModelFixture, CoilHeatingDXVariableRefrigerantFlowFluidTemperatureControl_RelationshipSetters_RoundTrip) {
  Model model;
  CoilHeatingDXVariableRefrigerantFlowFluidTemperatureControl coil(model);

  ScheduleConstant schedule(model);
  EXPECT_TRUE(schedule.setValue(0.25));
  EXPECT_TRUE(coil.setAvailabilitySchedule(schedule));
  EXPECT_EQ(schedule.handle(), coil.availabilitySchedule().handle());

  CurveQuadratic curve(model);
  EXPECT_TRUE(curve.setCoefficient1Constant(-1.1));
  EXPECT_TRUE(curve.setCoefficient2x(0.2));
  EXPECT_TRUE(curve.setCoefficient3xPOW2(0.3));
  EXPECT_TRUE(curve.setMinimumValueofx(1.0));
  EXPECT_TRUE(curve.setMaximumValueofx(9.0));
  EXPECT_TRUE(coil.setIndoorUnitCondensingTemperatureFunctionofSubcoolingCurve(curve));

  auto reboundCurve = coil.indoorUnitCondensingTemperatureFunctionofSubcoolingCurve().optionalCast<CurveQuadratic>();
  ASSERT_TRUE(reboundCurve);
  EXPECT_DOUBLE_EQ(-1.1, reboundCurve->coefficient1Constant());
  EXPECT_DOUBLE_EQ(0.3, reboundCurve->coefficient3xPOW2());

  const auto children = coil.children();
  ASSERT_EQ(1u, children.size());
  EXPECT_EQ(curve.handle(), children[0].handle());
}

TEST_F(EPModelFixture, CoilHeatingDXVariableRefrigerantFlowFluidTemperatureControl_StraightComponentPortsWithoutLoopPlacement) {
  Model model;
  CoilHeatingDXVariableRefrigerantFlowFluidTemperatureControl coil(model);
  Node node(model);

  EXPECT_TRUE(coil.optionalCast<StraightComponent>());
  EXPECT_EQ(openstudio::Coil_Heating_DX_VariableRefrigerantFlow_FluidTemperatureControlFields::CoilAirInletNode, coil.inletPort());
  EXPECT_EQ(openstudio::Coil_Heating_DX_VariableRefrigerantFlow_FluidTemperatureControlFields::CoilAirOutletNode, coil.outletPort());
  EXPECT_FALSE(coil.addToNode(node));
}
