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
#include "../ParentObject/CoilCoolingWaterToAirHeatPumpVariableSpeedEquationFitSpeedData.hpp"

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, CoilCoolingWaterToAirHeatPumpVariableSpeedEquationFitSpeedData_DefaultConstructor) {
  Model model;
  CoilCoolingWaterToAirHeatPumpVariableSpeedEquationFitSpeedData speed(model);

  EXPECT_EQ(CoilCoolingWaterToAirHeatPumpVariableSpeedEquationFitSpeedData::iddObjectType(), speed.iddObject().type());
  EXPECT_DOUBLE_EQ(1524.1, speed.referenceUnitGrossRatedTotalCoolingCapacity());
  EXPECT_DOUBLE_EQ(0.75, speed.referenceUnitGrossRatedSensibleHeatRatio());
  EXPECT_DOUBLE_EQ(4.0, speed.referenceUnitGrossRatedCoolingCOP());
  EXPECT_TRUE(speed.totalCoolingCapacityFunctionofTemperatureCurve().optionalCast<CurveBiquadratic>());
  EXPECT_TRUE(speed.totalCoolingCapacityFunctionofAirFlowFractionCurve().optionalCast<CurveQuadratic>());
  EXPECT_EQ(7u, speed.children().size());
}

TEST_F(EPModelFixture, CoilCoolingWaterToAirHeatPumpVariableSpeedEquationFitSpeedData_CurveConstructorAndSetters) {
  Model model;
  CurveBiquadratic coolingCurve1(model);
  CurveQuadratic coolingCurve2(model);
  CurveQuadratic coolingCurve3(model);
  CurveBiquadratic coolingCurve4(model);
  CurveQuadratic coolingCurve5(model);
  CurveQuadratic coolingCurve6(model);
  CurveBiquadratic coolingCurve7(model);

  CoilCoolingWaterToAirHeatPumpVariableSpeedEquationFitSpeedData speed(model, coolingCurve1, coolingCurve2, coolingCurve3, coolingCurve4,
                                                                        coolingCurve5, coolingCurve6, coolingCurve7);
  EXPECT_EQ(coolingCurve1, speed.totalCoolingCapacityFunctionofTemperatureCurve());
  EXPECT_EQ(coolingCurve4, speed.energyInputRatioFunctionofTemperatureCurve());
  EXPECT_EQ(coolingCurve7, speed.wasteHeatFunctionofTemperatureCurve());

  EXPECT_TRUE(speed.setReferenceUnitGrossRatedCoolingCOP(5.1));
  EXPECT_TRUE(speed.setReferenceUnitRatedAirFlowRate(0.21));
  EXPECT_TRUE(speed.setReferenceUnitWasteHeatFractionofInputPowerAtRatedConditions(0.2));
  EXPECT_DOUBLE_EQ(5.1, speed.referenceUnitGrossRatedCoolingCOP());
  EXPECT_DOUBLE_EQ(0.21, speed.referenceUnitRatedAirFlowRate());
  EXPECT_DOUBLE_EQ(0.2, speed.referenceUnitWasteHeatFractionofInputPowerAtRatedConditions());
}
