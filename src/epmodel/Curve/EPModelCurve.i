#ifndef EPMODEL_Curve_I
#define EPMODEL_Curve_I

#ifdef SWIGPYTHON
  %module openstudioepmodelcurve
#endif

%include <epmodel/EPModel_Common_Include.i>
%import <epmodel/EPModel.i>

EPMODELOBJECT_WRAP(Curve, <epmodel/Curve/Curve.hpp>)
EPMODELOBJECT_WRAP(CurveBicubic, <epmodel/Curve/CurveBicubic.hpp>)
EPMODELOBJECT_WRAP(CurveCubic, <epmodel/Curve/CurveCubic.hpp>)
EPMODELOBJECT_WRAP(CurveBiquadratic, <epmodel/Curve/CurveBiquadratic.hpp>)
EPMODELOBJECT_WRAP(CurveExponent, <epmodel/Curve/CurveExponent.hpp>)
EPMODELOBJECT_WRAP(CurveDoubleExponentialDecay, <epmodel/Curve/CurveDoubleExponentialDecay.hpp>)
EPMODELOBJECT_WRAP(CurveExponentialDecay, <epmodel/Curve/CurveExponentialDecay.hpp>)
EPMODELOBJECT_WRAP(CurveExponentialSkewNormal, <epmodel/Curve/CurveExponentialSkewNormal.hpp>)
EPMODELOBJECT_WRAP(CurveFanPressureRise, <epmodel/Curve/CurveFanPressureRise.hpp>)
EPMODELOBJECT_WRAP(CurveFunctionalPressureDrop, <epmodel/Curve/CurveFunctionalPressureDrop.hpp>)
EPMODELOBJECT_WRAP(CurveLinear, <epmodel/Curve/CurveLinear.hpp>)
EPMODELOBJECT_WRAP(CurveQuadratic, <epmodel/Curve/CurveQuadratic.hpp>)
EPMODELOBJECT_WRAP(CurveQuartic, <epmodel/Curve/CurveQuartic.hpp>)
EPMODELOBJECT_WRAP(CurveQuadLinear, <epmodel/Curve/CurveQuadLinear.hpp>)
EPMODELOBJECT_WRAP(CurveQuintLinear, <epmodel/Curve/CurveQuintLinear.hpp>)
EPMODELOBJECT_WRAP(CurveRectangularHyperbola1, <epmodel/Curve/CurveRectangularHyperbola1.hpp>)
EPMODELOBJECT_WRAP(CurveRectangularHyperbola2, <epmodel/Curve/CurveRectangularHyperbola2.hpp>)
EPMODELOBJECT_WRAP(CurveSigmoid, <epmodel/Curve/CurveSigmoid.hpp>)
EPMODELOBJECT_WRAP(CurveTriquadratic, <epmodel/Curve/CurveTriquadratic.hpp>)
EPMODELOBJECT_WRAP(CurveQuadraticLinear, <epmodel/Curve/CurveQuadraticLinear.hpp>)
EPMODELOBJECT_WRAP(TableLookup, <epmodel/Curve/TableLookup.hpp>)
EPMODELOBJECT_WRAP(CurveCubicLinear, <epmodel/Curve/CurveCubicLinear.hpp>)
EPMODELOBJECT_WRAP(CurveChillerPartLoadWithLift, <epmodel/Curve/CurveChillerPartLoadWithLift.hpp>)

#endif
