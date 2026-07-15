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
#include "../ParentObject/CoilHeatingWaterToAirHeatPumpVariableSpeedEquationFitSpeedData.hpp"

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, CoilHeatingWaterToAirHeatPumpVariableSpeedEquationFitSpeedData_DefaultConstructor) {
  Model model;
  CoilHeatingWaterToAirHeatPumpVariableSpeedEquationFitSpeedData speed(model);

  EXPECT_EQ(CoilHeatingWaterToAirHeatPumpVariableSpeedEquationFitSpeedData::iddObjectType(), speed.iddObject().type());
  EXPECT_DOUBLE_EQ(1838.7, speed.referenceUnitGrossRatedHeatingCapacity());
  EXPECT_DOUBLE_EQ(5.0, speed.referenceUnitGrossRatedHeatingCOP());
  EXPECT_DOUBLE_EQ(0.1661088, speed.referenceUnitRatedAirFlow());
  EXPECT_TRUE(speed.heatingCapacityFunctionofTemperatureCurve().optionalCast<CurveBiquadratic>());
  EXPECT_TRUE(speed.totalHeatingCapacityFunctionofAirFlowFractionCurve().optionalCast<CurveQuadratic>());
  EXPECT_EQ(7u, speed.children().size());
}

TEST_F(EPModelFixture, CoilHeatingWaterToAirHeatPumpVariableSpeedEquationFitSpeedData_CurveConstructorAndSetters) {
  Model model;
  CurveBiquadratic heatingCurve1(model);
  CurveQuadratic heatingCurve2(model);
  CurveQuadratic heatingCurve3(model);
  CurveBiquadratic heatingCurve4(model);
  CurveQuadratic heatingCurve5(model);
  CurveQuadratic heatingCurve6(model);
  CurveBiquadratic heatingCurve7(model);

  CoilHeatingWaterToAirHeatPumpVariableSpeedEquationFitSpeedData speed(model, heatingCurve1, heatingCurve2, heatingCurve3, heatingCurve4,
                                                                       heatingCurve5, heatingCurve6, heatingCurve7);
  EXPECT_EQ(heatingCurve1, speed.heatingCapacityFunctionofTemperatureCurve());
  EXPECT_EQ(heatingCurve4, speed.energyInputRatioFunctionofTemperatureCurve());
  EXPECT_EQ(heatingCurve7, speed.wasteHeatFunctionofTemperatureCurve());

  EXPECT_TRUE(speed.setReferenceUnitGrossRatedHeatingCOP(5.1));
  EXPECT_TRUE(speed.setReferenceUnitRatedAirFlow(0.21));
  EXPECT_TRUE(speed.setReferenceUnitWasteHeatFractionofInputPowerAtRatedConditions(0.2));
  EXPECT_DOUBLE_EQ(5.1, speed.referenceUnitGrossRatedHeatingCOP());
  EXPECT_DOUBLE_EQ(0.21, speed.referenceUnitRatedAirFlow());
  EXPECT_DOUBLE_EQ(0.2, speed.referenceUnitWasteHeatFractionofInputPowerAtRatedConditions());
}
