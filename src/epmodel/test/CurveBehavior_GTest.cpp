/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../Curve/CurveBicubic.hpp"
#include "../Curve/CurveBiquadratic.hpp"
#include "../Curve/CurveCubic.hpp"
#include "../Curve/CurveCubicLinear.hpp"
#include "../Curve/CurveDoubleExponentialDecay.hpp"
#include "../Curve/CurveExponent.hpp"
#include "../Curve/CurveExponentialDecay.hpp"
#include "../Curve/CurveExponentialSkewNormal.hpp"
#include "../Curve/CurveFanPressureRise.hpp"
#include "../Curve/CurveChillerPartLoadWithLift.hpp"
#include "../Curve/CurveFunctionalPressureDrop.hpp"
#include "../Curve/CurveLinear.hpp"
#include "../Curve/CurveQuadLinear.hpp"
#include "../Curve/CurveQuadratic.hpp"
#include "../Curve/CurveQuadraticLinear.hpp"
#include "../Curve/CurveQuartic.hpp"
#include "../Curve/CurveQuintLinear.hpp"
#include "../Curve/CurveRectangularHyperbola1.hpp"
#include "../Curve/CurveRectangularHyperbola2.hpp"
#include "../Curve/CurveSigmoid.hpp"
#include "../Curve/CurveTriquadratic.hpp"

#include <boost/math/special_functions/erf.hpp>

#include <cmath>

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, Curve_NumVariables_Parity) {
  Model model;

  EXPECT_EQ(1, CurveLinear(model).numVariables());
  EXPECT_EQ(1, CurveQuadratic(model).numVariables());
  EXPECT_EQ(1, CurveCubic(model).numVariables());
  EXPECT_EQ(1, CurveQuartic(model).numVariables());
  EXPECT_EQ(1, CurveExponent(model).numVariables());
  EXPECT_EQ(1, CurveExponentialDecay(model).numVariables());
  EXPECT_EQ(1, CurveDoubleExponentialDecay(model).numVariables());
  EXPECT_EQ(1, CurveExponentialSkewNormal(model).numVariables());
  EXPECT_EQ(1, CurveRectangularHyperbola1(model).numVariables());
  EXPECT_EQ(1, CurveRectangularHyperbola2(model).numVariables());
  EXPECT_EQ(1, CurveSigmoid(model).numVariables());
  EXPECT_EQ(2, CurveBiquadratic(model).numVariables());
  EXPECT_EQ(2, CurveBicubic(model).numVariables());
  EXPECT_EQ(2, CurveCubicLinear(model).numVariables());
  EXPECT_EQ(2, CurveQuadraticLinear(model).numVariables());
  EXPECT_EQ(2, CurveFanPressureRise(model).numVariables());
  EXPECT_EQ(3, CurveChillerPartLoadWithLift(model).numVariables());
  EXPECT_EQ(3, CurveTriquadratic(model).numVariables());
  EXPECT_EQ(4, CurveQuadLinear(model).numVariables());
  EXPECT_EQ(5, CurveQuintLinear(model).numVariables());
}

TEST_F(EPModelFixture, Curve_UnaryPolynomialBehavior) {
  Model model;

  {
    CurveQuadratic curve(model);
    curve.setCoefficient1Constant(1.0);
    curve.setCoefficient2x(2.0);
    curve.setCoefficient3xPOW2(3.0);
    curve.setMinimumValueofx(0.1);
    curve.setMaximumValueofx(3.0);
    EXPECT_DOUBLE_EQ(2.75, curve.evaluate(0.5));
    EXPECT_DOUBLE_EQ(1.23, curve.evaluate(0.05));
    EXPECT_DOUBLE_EQ(34.0, curve.evaluate(20.0));
    curve.setMinimumCurveOutput(2.5);
    curve.setMaximumCurveOutput(4.0);
    EXPECT_DOUBLE_EQ(2.5, curve.evaluate(0.05));
    EXPECT_DOUBLE_EQ(4.0, curve.evaluate(20.0));
  }

  {
    CurveCubic curve(model);
    curve.setCoefficient1Constant(1.0);
    curve.setCoefficient2x(2.0);
    curve.setCoefficient3xPOW2(3.0);
    curve.setCoefficient4xPOW3(4.0);
    curve.setMinimumValueofx(0.1);
    curve.setMaximumValueofx(3.0);
    EXPECT_DOUBLE_EQ(3.25, curve.evaluate(0.5));
    EXPECT_DOUBLE_EQ(1.234, curve.evaluate(0.05));
    EXPECT_DOUBLE_EQ(142.0, curve.evaluate(20.0));
    curve.setMinimumCurveOutput(2.5);
    curve.setMaximumCurveOutput(4.0);
    EXPECT_DOUBLE_EQ(2.5, curve.evaluate(0.05));
    EXPECT_DOUBLE_EQ(4.0, curve.evaluate(20.0));
  }

  {
    CurveQuartic curve(model);
    curve.setCoefficient1Constant(1.0);
    curve.setCoefficient2x(2.0);
    curve.setCoefficient3xPOW2(3.0);
    curve.setCoefficient4xPOW3(4.0);
    curve.setCoefficient5xPOW4(5.0);
    curve.setMinimumValueofx(0.1);
    curve.setMaximumValueofx(3.0);
    EXPECT_DOUBLE_EQ(3.5625, curve.evaluate(0.5));
    EXPECT_DOUBLE_EQ(1.2345, curve.evaluate(0.05));
    EXPECT_DOUBLE_EQ(547.0, curve.evaluate(20.0));
    curve.setMinimumCurveOutput(2.5);
    curve.setMaximumCurveOutput(4.0);
    EXPECT_DOUBLE_EQ(2.5, curve.evaluate(0.05));
    EXPECT_DOUBLE_EQ(4.0, curve.evaluate(20.0));
  }

  {
    CurveExponent curve(model);
    curve.setCoefficient1Constant(1.0);
    curve.setCoefficient2Constant(2.0);
    curve.setCoefficient3Constant(3.0);
    curve.setMinimumValueofx(0.1);
    curve.setMaximumValueofx(3.0);
    EXPECT_DOUBLE_EQ(1.25, curve.evaluate(0.5));
    EXPECT_DOUBLE_EQ(1.002, curve.evaluate(0.05));
    EXPECT_DOUBLE_EQ(55.0, curve.evaluate(20.0));
    curve.setMinimumCurveOutput(2.5);
    curve.setMaximumCurveOutput(4.0);
    EXPECT_DOUBLE_EQ(2.5, curve.evaluate(0.05));
    EXPECT_DOUBLE_EQ(4.0, curve.evaluate(20.0));
  }
}

TEST_F(EPModelFixture, Curve_UnaryExponentialAndShapeBehavior) {
  Model model;

  {
    CurveExponentialDecay curve(model);
    curve.setCoefficient1C1(1.0);
    curve.setCoefficient2C2(2.0);
    curve.setCoefficient3C3(3.0);
    curve.setMinimumValueofx(0.1);
    curve.setMaximumValueofx(3.0);
    EXPECT_DOUBLE_EQ(9.963378140676129, curve.evaluate(0.5));
    EXPECT_DOUBLE_EQ(3.6997176151520064, curve.evaluate(0.05));
    EXPECT_DOUBLE_EQ(16207.167855150768, curve.evaluate(20.0));
    curve.setMinimumCurveOutput(5.0);
    curve.setMaximumCurveOutput(10.5);
    EXPECT_DOUBLE_EQ(5.0, curve.evaluate(0.05));
    EXPECT_DOUBLE_EQ(10.5, curve.evaluate(20.0));
  }

  {
    CurveDoubleExponentialDecay curve(model);
    curve.setCoefficient1C1(1.0);
    curve.setCoefficient2C2(2.0);
    curve.setCoefficient3C3(3.0);
    curve.setCoefficient4C4(4.0);
    curve.setCoefficient5C5(5.0);
    curve.setMinimumValueofx(0.1);
    curve.setMaximumValueofx(3.0);
    EXPECT_DOUBLE_EQ(58.69335398349002, curve.evaluate(0.5));
    EXPECT_DOUBLE_EQ(10.29460269795252, curve.evaluate(0.05));
    EXPECT_DOUBLE_EQ(13092276.657743594, curve.evaluate(20.0));
    curve.setMinimumCurveOutput(12.0);
    curve.setMaximumCurveOutput(20.5);
    EXPECT_DOUBLE_EQ(12.0, curve.evaluate(0.05));
    EXPECT_DOUBLE_EQ(20.5, curve.evaluate(20.0));
  }

  {
    CurveExponentialSkewNormal curve(model);
    curve.setCoefficient1C1(1.0);
    curve.setCoefficient2C2(2.0);
    curve.setCoefficient3C3(3.0);
    curve.setCoefficient4C4(4.0);
    curve.setMinimumValueofx(0.1);
    curve.setMaximumValueofx(3.0);
    EXPECT_DOUBLE_EQ(3.559526560439694, curve.evaluate(0.5));
    EXPECT_DOUBLE_EQ(1.3575844732109894, curve.evaluate(0.05));
    EXPECT_DOUBLE_EQ(2.2275710165736293, curve.evaluate(20.0));
    curve.setMinimumCurveOutput(1.5);
    curve.setMaximumCurveOutput(2.0);
    EXPECT_DOUBLE_EQ(1.5, curve.evaluate(0.05));
    EXPECT_DOUBLE_EQ(2.0, curve.evaluate(20.0));
  }

  {
    CurveRectangularHyperbola1 curve(model);
    curve.setCoefficient1C1(1.0);
    curve.setCoefficient2C2(2.0);
    curve.setCoefficient3C3(3.0);
    curve.setMinimumValueofx(0.1);
    curve.setMaximumValueofx(3.0);
    EXPECT_DOUBLE_EQ(3.2, curve.evaluate(0.5));
    EXPECT_DOUBLE_EQ(3.0476190476190474, curve.evaluate(0.05));
    EXPECT_DOUBLE_EQ(3.6, curve.evaluate(20.0));
    curve.setMinimumCurveOutput(3.1);
    curve.setMaximumCurveOutput(3.5);
    EXPECT_DOUBLE_EQ(3.1, curve.evaluate(0.05));
    EXPECT_DOUBLE_EQ(3.5, curve.evaluate(20.0));
  }

  {
    CurveRectangularHyperbola2 curve(model);
    curve.setCoefficient1C1(1.0);
    curve.setCoefficient2C2(2.0);
    curve.setCoefficient3C3(3.0);
    curve.setMinimumValueofx(0.1);
    curve.setMaximumValueofx(3.0);
    EXPECT_DOUBLE_EQ(1.7, curve.evaluate(0.5));
    EXPECT_DOUBLE_EQ(0.34761904761904766, curve.evaluate(0.05));
    EXPECT_DOUBLE_EQ(9.6, curve.evaluate(20.0));
    curve.setMinimumCurveOutput(1.0);
    curve.setMaximumCurveOutput(3.5);
    EXPECT_DOUBLE_EQ(1.0, curve.evaluate(0.05));
    EXPECT_DOUBLE_EQ(3.5, curve.evaluate(20.0));
  }

  {
    CurveSigmoid curve(model);
    curve.setCoefficient1C1(1.0);
    curve.setCoefficient2C2(2.0);
    curve.setCoefficient3C3(3.0);
    curve.setCoefficient4C4(4.0);
    curve.setCoefficient5C5(5.0);
    curve.setMinimumValueofx(-10.0);
    curve.setMaximumValueofx(10.0);
    EXPECT_DOUBLE_EQ(1.1868895010341447, curve.evaluate(5.0));
    EXPECT_DOUBLE_EQ(1.0000001449235205, curve.evaluate(-20.0));
    EXPECT_DOUBLE_EQ(1.8976513195777158, curve.evaluate(20.0));
    curve.setMinimumCurveOutput(1.1);
    curve.setMaximumCurveOutput(1.5);
    EXPECT_DOUBLE_EQ(1.1, curve.evaluate(-20.0));
    EXPECT_DOUBLE_EQ(1.5, curve.evaluate(20.0));
  }
}

TEST_F(EPModelFixture, Curve_BivariateBehavior) {
  Model model;

  {
    CurveBiquadratic curve(model);
    curve.setCoefficient1Constant(1.0);
    curve.setCoefficient2x(2.0);
    curve.setCoefficient3xPOW2(3.0);
    curve.setCoefficient4y(4.0);
    curve.setCoefficient5yPOW2(5.0);
    curve.setCoefficient6xTIMESY(6.0);
    curve.setMinimumValueofx(0.1);
    curve.setMaximumValueofx(3.0);
    curve.setMinimumValueofy(10.0);
    curve.setMaximumValueofy(30.0);
    EXPECT_DOUBLE_EQ(1232.75, curve.evaluate(0.5, 15.0));
    EXPECT_DOUBLE_EQ(547.23, curve.evaluate(0.05, 5.0));
    EXPECT_DOUBLE_EQ(5194.0, curve.evaluate(20.0, 50.0));
    curve.setMinimumCurveOutput(700.0);
    curve.setMaximumCurveOutput(1000.0);
    EXPECT_DOUBLE_EQ(700.0, curve.evaluate(0.05, 5.0));
    EXPECT_DOUBLE_EQ(1000.0, curve.evaluate(20.0, 50.0));
  }

  {
    CurveBicubic curve(model);
    curve.setCoefficient1Constant(1.0);
    curve.setCoefficient2x(2.0);
    curve.setCoefficient3xPOW2(3.0);
    curve.setCoefficient4y(4.0);
    curve.setCoefficient5yPOW2(5.0);
    curve.setCoefficient6xTIMESY(6.0);
    curve.setCoefficient7xPOW3(7.0);
    curve.setCoefficient8yPOW3(8.0);
    curve.setCoefficient9xPOW2TIMESY(9.0);
    curve.setCoefficient10xTIMESYPOW2(10.0);
    curve.setMinimumValueofx(0.1);
    curve.setMaximumValueofx(3.0);
    curve.setMinimumValueofy(10.0);
    curve.setMaximumValueofy(30.0);
    EXPECT_DOUBLE_EQ(29392.375, curve.evaluate(0.5, 15.0));
    EXPECT_DOUBLE_EQ(8648.137, curve.evaluate(0.05, 5.0));
    EXPECT_DOUBLE_EQ(250813.0, curve.evaluate(20.0, 50.0));
    curve.setMinimumCurveOutput(10000.0);
    curve.setMaximumCurveOutput(100000.0);
    EXPECT_DOUBLE_EQ(10000.0, curve.evaluate(0.05, 5.0));
    EXPECT_DOUBLE_EQ(100000.0, curve.evaluate(20.0, 50.0));
  }

  {
    CurveQuadraticLinear curve(model);
    curve.setCoefficient1Constant(1.0);
    curve.setCoefficient2x(2.0);
    curve.setCoefficient3xPOW2(3.0);
    curve.setCoefficient4y(4.0);
    curve.setCoefficient5xTIMESY(5.0);
    curve.setCoefficient6xPOW2TIMESY(6.0);
    curve.setMinimumValueofx(0.1);
    curve.setMaximumValueofx(3.0);
    curve.setMinimumValueofy(10.0);
    curve.setMaximumValueofy(30.0);
    EXPECT_DOUBLE_EQ(122.75, curve.evaluate(0.5, 15.0));
    EXPECT_DOUBLE_EQ(46.83, curve.evaluate(0.05, 5.0));
    EXPECT_DOUBLE_EQ(2224.0, curve.evaluate(20.0, 50.0));
    curve.setMinimumCurveOutput(70.0);
    curve.setMaximumCurveOutput(1000.0);
    EXPECT_DOUBLE_EQ(70.0, curve.evaluate(0.05, 5.0));
    EXPECT_DOUBLE_EQ(1000.0, curve.evaluate(20.0, 50.0));
  }

  {
    CurveCubicLinear curve(model);
    curve.setCoefficient1Constant(1.0);
    curve.setCoefficient2x(2.0);
    curve.setCoefficient3xPOW2(3.0);
    curve.setCoefficient4xPOW3(4.0);
    curve.setCoefficient5y(5.0);
    curve.setCoefficient6xTIMESY(6.0);
    curve.setMinimumValueofx(0.1);
    curve.setMaximumValueofx(3.0);
    curve.setMinimumValueofy(10.0);
    curve.setMaximumValueofy(30.0);
    EXPECT_DOUBLE_EQ(123.25, curve.evaluate(0.5, 15.0));
    EXPECT_DOUBLE_EQ(57.234, curve.evaluate(0.05, 5.0));
    EXPECT_DOUBLE_EQ(832.0, curve.evaluate(20.0, 50.0));
    curve.setMinimumCurveOutput(70.0);
    curve.setMaximumCurveOutput(800.0);
    EXPECT_DOUBLE_EQ(70.0, curve.evaluate(0.05, 5.0));
    EXPECT_DOUBLE_EQ(800.0, curve.evaluate(20.0, 50.0));
  }
}

TEST_F(EPModelFixture, Curve_FanPressureRiseBehavior) {
  Model model;
  CurveFanPressureRise curve(model);

  curve.setCoefficient1C1(1.0);
  curve.setCoefficient2C2(2.0);
  curve.setCoefficient3C3(3.0);
  curve.setCoefficient4C4(4.0);
  curve.setMinimumValueofQfan(0.1);
  curve.setMaximumValueofQfan(3.0);
  curve.setMinimumValueofPsm(10.0);
  curve.setMaximumValueofPsm(400.0);

  EXPECT_DOUBLE_EQ(67.05947501931112, curve.evaluate(0.5, 15.0));
  EXPECT_DOUBLE_EQ(41.15868329805051, curve.evaluate(0.05, 5.0));
  EXPECT_DOUBLE_EQ(1795.0, curve.evaluate(20.0, 1000.0));

  curve.setMinimumCurveOutput(50.0);
  curve.setMaximumCurveOutput(1500.0);
  EXPECT_DOUBLE_EQ(50.0, curve.evaluate(0.05, 5.0));
  EXPECT_DOUBLE_EQ(1500.0, curve.evaluate(20.0, 1000.0));
}

TEST_F(EPModelFixture, Curve_HigherArityLinearBehavior) {
  Model model;

  {
    CurveQuadLinear curve(model);
    curve.setCoefficient1Constant(1.0);
    curve.setCoefficient2w(2.0);
    curve.setCoefficient3x(3.0);
    curve.setCoefficient4y(4.0);
    curve.setCoefficient5z(5.0);
    EXPECT_EQ(4, curve.numVariables());
    EXPECT_DOUBLE_EQ(5.0, curve.evaluate(0.1, 0.2, 0.3, 0.4));
  }

  {
    CurveQuintLinear curve(model);
    curve.setCoefficient1Constant(1.0);
    curve.setCoefficient2v(2.0);
    curve.setCoefficient3w(3.0);
    curve.setCoefficient4x(4.0);
    curve.setCoefficient5y(5.0);
    curve.setCoefficient6z(6.0);
    EXPECT_EQ(5, curve.numVariables());
    EXPECT_DOUBLE_EQ(8.0, curve.evaluate(0.1, 0.2, 0.3, 0.4, 0.5));
  }
}

TEST_F(EPModelFixture, Curve_TriquadraticBehavior) {
  Model model;
  CurveTriquadratic curve(model);

  curve.setCoefficient1Constant(1.0);
  curve.setCoefficient2xPOW2(2.0);
  curve.setCoefficient3x(3.0);
  curve.setCoefficient4yPOW2(4.0);
  curve.setCoefficient5y(5.0);
  curve.setCoefficient6zPOW2(6.0);
  curve.setCoefficient7z(7.0);
  curve.setCoefficient8xPOW2TIMESYPOW2(8.0);
  curve.setCoefficient9xTIMESY(9.0);
  curve.setCoefficient10xTIMESYPOW2(10.0);
  curve.setCoefficient11xPOW2TIMESY(11.0);
  curve.setCoefficient12xPOW2TIMESZPOW2(12.0);
  curve.setCoefficient13xTIMESZ(13.0);
  curve.setCoefficient14xTIMESZPOW2(14.0);
  curve.setCoefficient15xPOW2TIMESZ(15.0);
  curve.setCoefficient16yPOW2TIMESZPOW2(16.0);
  curve.setCoefficient17yTIMESZ(17.0);
  curve.setCoefficient18yTIMESZPOW2(18.0);
  curve.setCoefficient19yPOW2TIMESZ(19.0);
  curve.setCoefficient20xPOW2TIMESYPOW2TIMESZPOW2(20.0);
  curve.setCoefficient21xPOW2TIMESYPOW2TIMESZ(21.0);
  curve.setCoefficient22xPOW2TIMESYTIMESZPOW2(22.0);
  curve.setCoefficient23xTIMESYPOW2TIMESZPOW2(23.0);
  curve.setCoefficient24xPOW2TIMESYTIMESZ(24.0);
  curve.setCoefficient25xTIMESYPOW2TIMESZ(25.0);
  curve.setCoefficient26xTIMESYTIMESZPOW2(26.0);
  curve.setCoefficient27xTIMESYTIMESZ(27.0);
  curve.setMinimumValueofx(0.1);
  curve.setMaximumValueofx(3.0);
  curve.setMinimumValueofy(4.0);
  curve.setMaximumValueofy(6.0);
  curve.setMinimumValueofz(8.0);
  curve.setMaximumValueofz(10.0);

  EXPECT_DOUBLE_EQ(92296.75, curve.evaluate(0.5, 5.0, 9.0));
  EXPECT_DOUBLE_EQ(28346.4, curve.evaluate(-5.0, -5.0, -5.0));
  EXPECT_DOUBLE_EQ(1273160.0, curve.evaluate(10.0, 10.0, 10.0));

  curve.setMinimumCurveOutput(40000.0);
  curve.setMaximumCurveOutput(100000.0);
  EXPECT_DOUBLE_EQ(40000.0, curve.evaluate(-5.0, -5.0, -5.0));
  EXPECT_DOUBLE_EQ(100000.0, curve.evaluate(10.0, 10.0, 10.0));
}

TEST_F(EPModelFixture, Curve_ChillerPartLoadWithLiftBehavior) {
  Model model;
  CurveChillerPartLoadWithLift curve(model);

  curve.setCoefficient1C1(1.0);
  curve.setCoefficient2C2(2.0);
  curve.setCoefficient3C3(3.0);
  curve.setCoefficient4C4(4.0);
  curve.setCoefficient5C5(5.0);
  curve.setCoefficient6C6(6.0);
  curve.setCoefficient7C7(7.0);
  curve.setCoefficient8C8(8.0);
  curve.setCoefficient9C9(9.0);
  curve.setCoefficient10C10(10.0);
  curve.setCoefficient11C11(11.0);
  curve.setCoefficient12C12(12.0);
  curve.setMinimumValueofx(0.1);
  curve.setMaximumValueofx(3.0);
  curve.setMinimumValueofy(0.2);
  curve.setMaximumValueofy(0.8);
  curve.setMinimumValueofz(0.3);
  curve.setMaximumValueofz(0.7);

  EXPECT_DOUBLE_EQ(6.934375, curve.evaluate(0.5, 0.25, 0.4));
  EXPECT_DOUBLE_EQ(2.5122000000000004, curve.evaluate(0.05, 0.1, 0.2));
  EXPECT_DOUBLE_EQ(399.5568, curve.evaluate(20.0, 2.0, 3.0));

  curve.setMinimumCurveOutput(3.0);
  curve.setMaximumCurveOutput(300.0);
  EXPECT_DOUBLE_EQ(3.0, curve.evaluate(0.05, 0.1, 0.2));
  EXPECT_DOUBLE_EQ(300.0, curve.evaluate(20.0, 2.0, 3.0));
}

TEST_F(EPModelFixture, Curve_FunctionalPressureDropThrows) {
  Model model;
  CurveFunctionalPressureDrop curve(model);
  EXPECT_ANY_THROW(curve.numVariables());
  EXPECT_ANY_THROW(curve.evaluate(10.0));
}
