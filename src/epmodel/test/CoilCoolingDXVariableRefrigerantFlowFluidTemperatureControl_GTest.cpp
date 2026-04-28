/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../Curve/CurveQuadratic.hpp"
#include "../Curve/CurveQuadratic_Impl.hpp"
#include "../StraightComponent/CoilCoolingDXVariableRefrigerantFlowFluidTemperatureControl.hpp"
#include "../Schedule/ScheduleConstant.hpp"
#include "../Schedule/ScheduleConstant_Impl.hpp"
#include "../StraightComponent/Node.hpp"
#include "../StraightComponent/StraightComponent.hpp"

#include <utilities/idd/Coil_Cooling_DX_VariableRefrigerantFlow_FluidTemperatureControl_FieldEnums.hxx>

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, CoilCoolingDXVariableRefrigerantFlowFluidTemperatureControl_DefaultConstructor) {
  Model model;
  CoilCoolingDXVariableRefrigerantFlowFluidTemperatureControl coil(model);
  EXPECT_EQ(CoilCoolingDXVariableRefrigerantFlowFluidTemperatureControl::iddObjectType(), coil.iddObject().type());
  EXPECT_FALSE(coil.nameString().empty());
  EXPECT_EQ(model.alwaysOnDiscreteSchedule().handle(), coil.availabilitySchedule().handle());
  EXPECT_TRUE(coil.isRatedTotalCoolingCapacityAutosized());
  EXPECT_TRUE(coil.isRatedSensibleHeatRatioAutosized());
  EXPECT_DOUBLE_EQ(5.0, coil.indoorUnitReferenceSuperheating());

  auto curve = coil.indoorUnitEvaporatingTemperatureFunctionofSuperheatingCurve().optionalCast<CurveQuadratic>();
  ASSERT_TRUE(curve);
  EXPECT_EQ("VRFIUEvapTempCurve", curve->nameString());
  EXPECT_DOUBLE_EQ(0.0, curve->coefficient1Constant());
  EXPECT_DOUBLE_EQ(0.843, curve->coefficient2x());
  EXPECT_DOUBLE_EQ(0.0, curve->coefficient3xPOW2());
  EXPECT_DOUBLE_EQ(0.0, curve->minimumValueofx());
  EXPECT_DOUBLE_EQ(15.0, curve->maximumValueofx());
}

TEST_F(EPModelFixture, CoilCoolingDXVariableRefrigerantFlowFluidTemperatureControl_ScalarAccessors_RoundTrip) {
  Model model;
  CoilCoolingDXVariableRefrigerantFlowFluidTemperatureControl coil(model);

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

  EXPECT_TRUE(coil.setIndoorUnitReferenceSuperheating(8.25));
  EXPECT_DOUBLE_EQ(8.25, coil.indoorUnitReferenceSuperheating());
}

TEST_F(EPModelFixture, CoilCoolingDXVariableRefrigerantFlowFluidTemperatureControl_RelationshipSetters_RoundTrip) {
  Model model;
  CoilCoolingDXVariableRefrigerantFlowFluidTemperatureControl coil(model);

  ScheduleConstant schedule(model);
  EXPECT_TRUE(schedule.setValue(0.25));
  EXPECT_TRUE(coil.setAvailabilitySchedule(schedule));
  EXPECT_EQ(schedule.handle(), coil.availabilitySchedule().handle());

  CurveQuadratic curve(model);
  EXPECT_TRUE(curve.setCoefficient1Constant(1.1));
  EXPECT_TRUE(curve.setCoefficient2x(1.2));
  EXPECT_TRUE(curve.setCoefficient3xPOW2(1.3));
  EXPECT_TRUE(curve.setMinimumValueofx(1.4));
  EXPECT_TRUE(curve.setMaximumValueofx(1.5));
  EXPECT_TRUE(coil.setIndoorUnitEvaporatingTemperatureFunctionofSuperheatingCurve(curve));
  auto reboundCurve = coil.indoorUnitEvaporatingTemperatureFunctionofSuperheatingCurve().optionalCast<CurveQuadratic>();
  ASSERT_TRUE(reboundCurve);
  EXPECT_DOUBLE_EQ(1.1, reboundCurve->coefficient1Constant());
  EXPECT_DOUBLE_EQ(1.2, reboundCurve->coefficient2x());
  EXPECT_DOUBLE_EQ(1.3, reboundCurve->coefficient3xPOW2());
  EXPECT_DOUBLE_EQ(1.4, reboundCurve->minimumValueofx());
  EXPECT_DOUBLE_EQ(1.5, reboundCurve->maximumValueofx());
}

TEST_F(EPModelFixture, CoilCoolingDXVariableRefrigerantFlowFluidTemperatureControl_StraightComponentPortsWithoutLoopPlacement) {
  Model model;
  CoilCoolingDXVariableRefrigerantFlowFluidTemperatureControl coil(model);
  Node node(model);

  EXPECT_TRUE(coil.optionalCast<StraightComponent>());
  EXPECT_EQ(openstudio::Coil_Cooling_DX_VariableRefrigerantFlow_FluidTemperatureControlFields::CoilAirInletNode, coil.inletPort());
  EXPECT_EQ(openstudio::Coil_Cooling_DX_VariableRefrigerantFlow_FluidTemperatureControlFields::CoilAirOutletNode, coil.outletPort());
  EXPECT_FALSE(coil.addToNode(node));
}
