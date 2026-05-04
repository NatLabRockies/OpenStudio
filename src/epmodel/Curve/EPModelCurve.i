#ifndef EPMODEL_Curve_I
#define EPMODEL_Curve_I

#ifdef SWIGPYTHON
  %module openstudioepmodelcurve
#endif

%include <epmodel/EPModel_Common_Include.i>
%import <epmodel/EPModel.i>

EPMODELOBJECT_WRAP(Curve, <epmodel/Curve/Curve.hpp>, 0, 0)
EPMODELOBJECT_WRAP(CurveBicubic, <epmodel/Curve/CurveBicubic.hpp>, 0, 1)
EPMODELOBJECT_WRAP(CurveCubic, <epmodel/Curve/CurveCubic.hpp>, 0, 1)
EPMODELOBJECT_WRAP(CurveBiquadratic, <epmodel/Curve/CurveBiquadratic.hpp>, 0, 1)
EPMODELOBJECT_WRAP(CurveExponent, <epmodel/Curve/CurveExponent.hpp>, 0, 1)
EPMODELOBJECT_WRAP(CurveDoubleExponentialDecay, <epmodel/Curve/CurveDoubleExponentialDecay.hpp>, 0, 1)
EPMODELOBJECT_WRAP(CurveExponentialDecay, <epmodel/Curve/CurveExponentialDecay.hpp>, 0, 1)
EPMODELOBJECT_WRAP(CurveExponentialSkewNormal, <epmodel/Curve/CurveExponentialSkewNormal.hpp>, 0, 1)
EPMODELOBJECT_WRAP(CurveFanPressureRise, <epmodel/Curve/CurveFanPressureRise.hpp>, 0, 1)
EPMODELOBJECT_WRAP(CurveFunctionalPressureDrop, <epmodel/Curve/CurveFunctionalPressureDrop.hpp>, 0, 1)
EPMODELOBJECT_WRAP(CurveLinear, <epmodel/Curve/CurveLinear.hpp>, 0, 1)
EPMODELOBJECT_WRAP(CurveQuadratic, <epmodel/Curve/CurveQuadratic.hpp>, 0, 1)
EPMODELOBJECT_WRAP(CurveQuartic, <epmodel/Curve/CurveQuartic.hpp>, 0, 1)
EPMODELOBJECT_WRAP(CurveQuadLinear, <epmodel/Curve/CurveQuadLinear.hpp>, 0, 1)
EPMODELOBJECT_WRAP(CurveQuintLinear, <epmodel/Curve/CurveQuintLinear.hpp>, 0, 1)
EPMODELOBJECT_WRAP(CurveRectangularHyperbola1, <epmodel/Curve/CurveRectangularHyperbola1.hpp>, 0, 1)
EPMODELOBJECT_WRAP(CurveRectangularHyperbola2, <epmodel/Curve/CurveRectangularHyperbola2.hpp>, 0, 1)
EPMODELOBJECT_WRAP(CurveSigmoid, <epmodel/Curve/CurveSigmoid.hpp>, 0, 1)
EPMODELOBJECT_WRAP(CurveTriquadratic, <epmodel/Curve/CurveTriquadratic.hpp>, 0, 1)
EPMODELOBJECT_WRAP(CurveQuadraticLinear, <epmodel/Curve/CurveQuadraticLinear.hpp>, 0, 1)
EPMODELOBJECT_WRAP(TableLookup, <epmodel/Curve/TableLookup.hpp>, 0, 1)
EPMODELOBJECT_WRAP(CurveCubicLinear, <epmodel/Curve/CurveCubicLinear.hpp>, 0, 1)
EPMODELOBJECT_WRAP(CurveChillerPartLoadWithLift, <epmodel/Curve/CurveChillerPartLoadWithLift.hpp>, 0, 1)

#endif
