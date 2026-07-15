/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "Curve/Curve_Impl.hpp"

#include "Curve/Curve.hpp"
#include "Curve/CurveBicubic.hpp"
#include "Curve/CurveBicubic_Impl.hpp"
#include "Curve/CurveBiquadratic.hpp"
#include "Curve/CurveBiquadratic_Impl.hpp"
#include "Curve/CurveCubic.hpp"
#include "Curve/CurveCubic_Impl.hpp"
#include "Curve/CurveCubicLinear.hpp"
#include "Curve/CurveCubicLinear_Impl.hpp"
#include "Curve/CurveChillerPartLoadWithLift.hpp"
#include "Curve/CurveChillerPartLoadWithLift_Impl.hpp"
#include "Curve/CurveDoubleExponentialDecay.hpp"
#include "Curve/CurveDoubleExponentialDecay_Impl.hpp"
#include "Curve/CurveExponent.hpp"
#include "Curve/CurveExponent_Impl.hpp"
#include "Curve/CurveExponentialDecay.hpp"
#include "Curve/CurveExponentialDecay_Impl.hpp"
#include "Curve/CurveExponentialSkewNormal.hpp"
#include "Curve/CurveExponentialSkewNormal_Impl.hpp"
#include "Curve/CurveFanPressureRise.hpp"
#include "Curve/CurveFanPressureRise_Impl.hpp"
#include "Curve/CurveFunctionalPressureDrop.hpp"
#include "Curve/CurveFunctionalPressureDrop_Impl.hpp"
#include "Curve/CurveLinear.hpp"
#include "Curve/CurveLinear_Impl.hpp"
#include "Curve/CurveQuadLinear.hpp"
#include "Curve/CurveQuadLinear_Impl.hpp"
#include "Curve/CurveQuadratic.hpp"
#include "Curve/CurveQuadratic_Impl.hpp"
#include "Curve/CurveQuadraticLinear.hpp"
#include "Curve/CurveQuadraticLinear_Impl.hpp"
#include "Curve/CurveQuartic.hpp"
#include "Curve/CurveQuartic_Impl.hpp"
#include "Curve/CurveQuintLinear.hpp"
#include "Curve/CurveQuintLinear_Impl.hpp"
#include "Curve/CurveRectangularHyperbola1.hpp"
#include "Curve/CurveRectangularHyperbola1_Impl.hpp"
#include "Curve/CurveRectangularHyperbola2.hpp"
#include "Curve/CurveRectangularHyperbola2_Impl.hpp"
#include "Curve/CurveSigmoid.hpp"
#include "Curve/CurveSigmoid_Impl.hpp"
#include "Curve/CurveTriquadratic.hpp"
#include "Curve/CurveTriquadratic_Impl.hpp"
#include "Curve/TableLookup.hpp"
#include "Curve/TableLookup_Impl.hpp"
#include "ResourceObject/TableIndependentVariable.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/core/Logger.hpp>

#include <boost/math/special_functions/erf.hpp>

#include <cmath>

namespace openstudio {
namespace epmodel {
  namespace detail {

    namespace {

      double clampToRange(double value, double minimumValue, double maximumValue, const char* variableName) {
        if (value < minimumValue) {
          LOG_FREE(Warn, "openstudio.epmodel.Curve", "Supplied " << variableName << " is below the minimum, resetting it.");
          return minimumValue;
        }
        if (value > maximumValue) {
          LOG_FREE(Warn, "openstudio.epmodel.Curve", "Supplied " << variableName << " is above the maximum, resetting it.");
          return maximumValue;
        }
        return value;
      }

      double clampToOptionalRange(double value, const boost::optional<double>& minimumValue, const boost::optional<double>& maximumValue,
                                  const char* variableName) {
        if (minimumValue && value < *minimumValue) {
          LOG_FREE(Warn, "openstudio.epmodel.Curve", "Supplied " << variableName << " is below the minimum, resetting it.");
          value = *minimumValue;
        }
        if (maximumValue && value > *maximumValue) {
          LOG_FREE(Warn, "openstudio.epmodel.Curve", "Supplied " << variableName << " is above the maximum, resetting it.");
          value = *maximumValue;
        }
        return value;
      }

      double applyOutputLimits(double result, const boost::optional<double>& minimumValue, const boost::optional<double>& maximumValue) {
        if (minimumValue && result < *minimumValue) {
          LOG_FREE(Warn, "openstudio.epmodel.Curve", "Calculated curve output is below minimumCurveOutput, resetting it.");
          result = *minimumValue;
        }
        if (maximumValue && result > *maximumValue) {
          LOG_FREE(Warn, "openstudio.epmodel.Curve", "Calculated curve output is above maximumCurveOutput, resetting it.");
          result = *maximumValue;
        }
        return result;
      }

      template <typename OptionalDouble>
      double valueOrZero(const OptionalDouble& value) {
        return value ? *value : 0.0;
      }

    }  // namespace

    Curve_Impl::Curve_Impl(const openstudio::IdfObject& idfObject, Model_Impl* model, bool keepHandle)
      : ResourceObject_Impl(idfObject, model, keepHandle) {}

    Curve_Impl::Curve_Impl(const openstudio::detail::WorkspaceObject_Impl& other, Model_Impl* model, bool keepHandle)
      : ResourceObject_Impl(other, model, keepHandle) {}

    int Curve_Impl::numVariables() const {
      const auto curve = getObject<openstudio::epmodel::Curve>();

      if (auto typed = curve.optionalCast<CurveLinear>()) {
        return 1;
      } else if (auto typed = curve.optionalCast<CurveQuadratic>()) {
        return 1;
      } else if (auto typed = curve.optionalCast<CurveCubic>()) {
        return 1;
      } else if (auto typed = curve.optionalCast<CurveQuartic>()) {
        return 1;
      } else if (auto typed = curve.optionalCast<CurveExponent>()) {
        return 1;
      } else if (auto typed = curve.optionalCast<CurveExponentialDecay>()) {
        return 1;
      } else if (auto typed = curve.optionalCast<CurveDoubleExponentialDecay>()) {
        return 1;
      } else if (auto typed = curve.optionalCast<CurveExponentialSkewNormal>()) {
        return 1;
      } else if (auto typed = curve.optionalCast<CurveRectangularHyperbola1>()) {
        return 1;
      } else if (auto typed = curve.optionalCast<CurveRectangularHyperbola2>()) {
        return 1;
      } else if (auto typed = curve.optionalCast<CurveSigmoid>()) {
        return 1;
      } else if (auto typed = curve.optionalCast<CurveBiquadratic>()) {
        return 2;
      } else if (auto typed = curve.optionalCast<CurveBicubic>()) {
        return 2;
      } else if (auto typed = curve.optionalCast<CurveCubicLinear>()) {
        return 2;
      } else if (auto typed = curve.optionalCast<CurveQuadraticLinear>()) {
        return 2;
      } else if (auto typed = curve.optionalCast<CurveFanPressureRise>()) {
        return 2;
      } else if (auto typed = curve.optionalCast<CurveChillerPartLoadWithLift>()) {
        return 3;
      } else if (auto typed = curve.optionalCast<CurveTriquadratic>()) {
        return 3;
      } else if (auto typed = curve.optionalCast<CurveQuadLinear>()) {
        return 4;
      } else if (auto typed = curve.optionalCast<CurveQuintLinear>()) {
        return 5;
      } else if (auto typed = curve.optionalCast<TableLookup>()) {
        return static_cast<int>(typed->independentVariables().size());
      } else if (curve.optionalCast<CurveFunctionalPressureDrop>()) {
        LOG_FREE_AND_THROW("openstudio.epmodel.Curve",
                           "CurveFunctionalPressureDrop must be evaluated by EnergyPlus in the context of plant pressure simulations.");
      }

      LOG_FREE_AND_THROW("openstudio.epmodel.Curve", "Unsupported curve type '" << curve.iddObject().type().valueName() << "'.");
    }

    double Curve_Impl::evaluate(const std::vector<double>& independentVariables) const {
      const auto curve = getObject<openstudio::epmodel::Curve>();

      if (auto typed = curve.optionalCast<CurveLinear>()) {
        OS_ASSERT(independentVariables.size() == 1u);
        const double x = clampToRange(independentVariables[0], typed->minimumValueofx(), typed->maximumValueofx(), "x");
        double result = typed->coefficient1Constant() + typed->coefficient2x() * x;
        return applyOutputLimits(result, typed->minimumCurveOutput(), typed->maximumCurveOutput());
      } else if (auto typed = curve.optionalCast<CurveQuadratic>()) {
        OS_ASSERT(independentVariables.size() == 1u);
        const double x = clampToRange(independentVariables[0], typed->minimumValueofx(), typed->maximumValueofx(), "x");
        double result = typed->coefficient1Constant();
        result += typed->coefficient2x() * x;
        result += typed->coefficient3xPOW2() * std::pow(x, 2);
        return applyOutputLimits(result, typed->minimumCurveOutput(), typed->maximumCurveOutput());
      } else if (auto typed = curve.optionalCast<CurveCubic>()) {
        OS_ASSERT(independentVariables.size() == 1u);
        const double x = clampToRange(independentVariables[0], typed->minimumValueofx(), typed->maximumValueofx(), "x");
        double result = typed->coefficient1Constant();
        result += typed->coefficient2x() * x;
        result += typed->coefficient3xPOW2() * std::pow(x, 2);
        result += typed->coefficient4xPOW3() * std::pow(x, 3);
        return applyOutputLimits(result, typed->minimumCurveOutput(), typed->maximumCurveOutput());
      } else if (auto typed = curve.optionalCast<CurveQuartic>()) {
        OS_ASSERT(independentVariables.size() == 1u);
        const double x = clampToRange(independentVariables[0], typed->minimumValueofx(), typed->maximumValueofx(), "x");
        double result = typed->coefficient1Constant();
        result += typed->coefficient2x() * x;
        result += typed->coefficient3xPOW2() * std::pow(x, 2);
        result += typed->coefficient4xPOW3() * std::pow(x, 3);
        result += typed->coefficient5xPOW4() * std::pow(x, 4);
        return applyOutputLimits(result, typed->minimumCurveOutput(), typed->maximumCurveOutput());
      } else if (auto typed = curve.optionalCast<CurveExponent>()) {
        OS_ASSERT(independentVariables.size() == 1u);
        const double x = clampToRange(independentVariables[0], typed->minimumValueofx(), typed->maximumValueofx(), "x");
        double result = typed->coefficient1Constant();
        result += typed->coefficient2Constant() * std::pow(x, typed->coefficient3Constant());
        return applyOutputLimits(result, typed->minimumCurveOutput(), typed->maximumCurveOutput());
      } else if (auto typed = curve.optionalCast<CurveExponentialDecay>()) {
        OS_ASSERT(independentVariables.size() == 1u);
        const double x = clampToRange(independentVariables[0], typed->minimumValueofx(), typed->maximumValueofx(), "x");
        double result = typed->coefficient1C1();
        result += typed->coefficient2C2() * std::exp(typed->coefficient3C3() * x);
        return applyOutputLimits(result, typed->minimumCurveOutput(), typed->maximumCurveOutput());
      } else if (auto typed = curve.optionalCast<CurveDoubleExponentialDecay>()) {
        OS_ASSERT(independentVariables.size() == 1u);
        const double x = clampToRange(independentVariables[0], typed->minimumValueofx(), typed->maximumValueofx(), "x");
        double result = typed->coefficient1C1();
        result += typed->coefficient2C2() * std::exp(typed->coefficient3C3() * x);
        result += typed->coefficient4C4() * std::exp(typed->coefficient5C5() * x);
        return applyOutputLimits(result, typed->minimumCurveOutput(), typed->maximumCurveOutput());
      } else if (auto typed = curve.optionalCast<CurveExponentialSkewNormal>()) {
        OS_ASSERT(independentVariables.size() == 1u);
        const double x = clampToRange(independentVariables[0], typed->minimumValueofx(), typed->maximumValueofx(), "x");
        const double z1 = (x - typed->coefficient1C1()) / typed->coefficient2C2();
        const double z2 = (typed->coefficient4C4() * x * std::exp(typed->coefficient3C3() * x) - typed->coefficient1C1()) / typed->coefficient2C2();
        const double z3 = -typed->coefficient1C1() / typed->coefficient2C2();
        double numerator = 1.0 + (z2 / std::abs(z2)) * boost::math::erf<double>(std::abs(z2) / std::sqrt(2.0));
        numerator *= std::exp(-0.5 * std::pow(z1, 2));
        double denominator = 1.0 + (z3 / std::abs(z3)) * boost::math::erf<double>(std::abs(z3) / std::sqrt(2.0));
        denominator *= std::exp(-0.5 * std::pow(z3, 2));
        const double result = numerator / denominator;
        return applyOutputLimits(result, typed->minimumCurveOutput(), typed->maximumCurveOutput());
      } else if (auto typed = curve.optionalCast<CurveRectangularHyperbola1>()) {
        OS_ASSERT(independentVariables.size() == 1u);
        const double x = clampToRange(independentVariables[0], typed->minimumValueofx(), typed->maximumValueofx(), "x");
        double result = typed->coefficient1C1() * x;
        result /= (typed->coefficient2C2() + x);
        result += typed->coefficient3C3();
        return applyOutputLimits(result, typed->minimumCurveOutput(), typed->maximumCurveOutput());
      } else if (auto typed = curve.optionalCast<CurveRectangularHyperbola2>()) {
        OS_ASSERT(independentVariables.size() == 1u);
        const double x = clampToRange(independentVariables[0], typed->minimumValueofx(), typed->maximumValueofx(), "x");
        double result = typed->coefficient1C1() * x;
        result /= (typed->coefficient2C2() + x);
        result += typed->coefficient3C3() * x;
        return applyOutputLimits(result, typed->minimumCurveOutput(), typed->maximumCurveOutput());
      } else if (auto typed = curve.optionalCast<CurveSigmoid>()) {
        OS_ASSERT(independentVariables.size() == 1u);
        const double x = clampToRange(independentVariables[0], typed->minimumValueofx(), typed->maximumValueofx(), "x");
        double result = typed->coefficient2C2();
        double temp = (typed->coefficient3C3() - x) / typed->coefficient4C4();
        temp = std::exp(temp);
        temp = std::pow(1.0 + temp, typed->coefficient5C5());
        result /= temp;
        result += typed->coefficient1C1();
        return applyOutputLimits(result, typed->minimumCurveOutput(), typed->maximumCurveOutput());
      } else if (auto typed = curve.optionalCast<CurveBiquadratic>()) {
        OS_ASSERT(independentVariables.size() == 2u);
        const double x = clampToRange(independentVariables[0], typed->minimumValueofx(), typed->maximumValueofx(), "x");
        const double y = clampToRange(independentVariables[1], typed->minimumValueofy(), typed->maximumValueofy(), "y");
        double result = typed->coefficient1Constant();
        result += typed->coefficient2x() * x;
        result += typed->coefficient3xPOW2() * std::pow(x, 2);
        result += typed->coefficient4y() * y;
        result += typed->coefficient5yPOW2() * std::pow(y, 2);
        result += typed->coefficient6xTIMESY() * x * y;
        return applyOutputLimits(result, typed->minimumCurveOutput(), typed->maximumCurveOutput());
      } else if (auto typed = curve.optionalCast<CurveBicubic>()) {
        OS_ASSERT(independentVariables.size() == 2u);
        const double x = clampToRange(independentVariables[0], typed->minimumValueofx(), typed->maximumValueofx(), "x");
        const double y = clampToRange(independentVariables[1], typed->minimumValueofy(), typed->maximumValueofy(), "y");
        const double x2 = std::pow(x, 2);
        const double y2 = std::pow(y, 2);
        double result = typed->coefficient1Constant();
        result += typed->coefficient2x() * x;
        result += typed->coefficient3xPOW2() * x2;
        result += typed->coefficient4y() * y;
        result += typed->coefficient5yPOW2() * y2;
        result += typed->coefficient6xTIMESY() * x * y;
        result += typed->coefficient7xPOW3() * std::pow(x, 3);
        result += typed->coefficient8yPOW3() * std::pow(y, 3);
        result += typed->coefficient9xPOW2TIMESY() * x2 * y;
        result += typed->coefficient10xTIMESYPOW2() * x * y2;
        return applyOutputLimits(result, typed->minimumCurveOutput(), typed->maximumCurveOutput());
      } else if (auto typed = curve.optionalCast<CurveCubicLinear>()) {
        OS_ASSERT(independentVariables.size() == 2u);
        const double x = clampToRange(independentVariables[0], typed->minimumValueofx(), typed->maximumValueofx(), "x");
        const double y = clampToRange(independentVariables[1], typed->minimumValueofy(), typed->maximumValueofy(), "y");
        const double x2 = std::pow(x, 2);
        double result = typed->coefficient1Constant();
        result += typed->coefficient2x() * x;
        result += typed->coefficient3xPOW2() * x2;
        result += typed->coefficient4xPOW3() * std::pow(x, 3);
        double temp = typed->coefficient5y();
        temp += typed->coefficient6xTIMESY() * x;
        result += temp * y;
        return applyOutputLimits(result, typed->minimumCurveOutput(), typed->maximumCurveOutput());
      } else if (auto typed = curve.optionalCast<CurveQuadraticLinear>()) {
        OS_ASSERT(independentVariables.size() == 2u);
        const double x = clampToRange(independentVariables[0], typed->minimumValueofx(), typed->maximumValueofx(), "x");
        const double y = clampToRange(independentVariables[1], typed->minimumValueofy(), typed->maximumValueofy(), "y");
        const double x2 = std::pow(x, 2);
        double result = typed->coefficient1Constant();
        result += typed->coefficient2x() * x;
        result += typed->coefficient3xPOW2() * x2;
        double temp = typed->coefficient4y();
        temp += typed->coefficient5xTIMESY() * x;
        temp += typed->coefficient6xPOW2TIMESY() * x2;
        result += temp * y;
        return applyOutputLimits(result, typed->minimumCurveOutput(), typed->maximumCurveOutput());
      } else if (auto typed = curve.optionalCast<CurveFanPressureRise>()) {
        OS_ASSERT(independentVariables.size() == 2u);
        const double qFan = clampToRange(independentVariables[0], typed->minimumValueofQfan(), typed->maximumValueofQfan(), "Qfan");
        const double psm = clampToRange(independentVariables[1], typed->minimumValueofPsm(), typed->maximumValueofPsm(), "Psm");
        double result = typed->coefficient1C1() * std::pow(qFan, 2);
        result += typed->coefficient2C2() * qFan;
        result += typed->coefficient3C3() * qFan * std::sqrt(psm);
        result += typed->coefficient4C4() * psm;
        return applyOutputLimits(result, typed->minimumCurveOutput(), typed->maximumCurveOutput());
      } else if (auto typed = curve.optionalCast<CurveChillerPartLoadWithLift>()) {
        OS_ASSERT(independentVariables.size() == 3u);
        const double x = clampToRange(independentVariables[0], typed->minimumValueofx(), typed->maximumValueofx(), "x");
        const double y = clampToRange(independentVariables[1], typed->minimumValueofy(), typed->maximumValueofy(), "y");
        const double z = clampToRange(independentVariables[2], typed->minimumValueofz(), typed->maximumValueofz(), "z");
        const double x2 = std::pow(x, 2);
        const double y2 = std::pow(y, 2);
        const double y3 = std::pow(y, 3);
        double result = typed->coefficient1C1();
        result += typed->coefficient2C2() * x;
        result += typed->coefficient3C3() * x2;
        result += typed->coefficient4C4() * y;
        result += typed->coefficient5C5() * y2;
        result += typed->coefficient6C6() * x * y;
        result += typed->coefficient7C7() * std::pow(x, 3);
        result += typed->coefficient8C8() * y3;
        result += typed->coefficient9C9() * x2 * y;
        result += typed->coefficient10C10() * x * y2;
        result += typed->coefficient11C11() * x2 * y2;
        result += typed->coefficient12C12() * z * y3;
        return applyOutputLimits(result, typed->minimumCurveOutput(), typed->maximumCurveOutput());
      } else if (auto typed = curve.optionalCast<CurveTriquadratic>()) {
        OS_ASSERT(independentVariables.size() == 3u);
        const double x = clampToOptionalRange(independentVariables[0], typed->minimumValueofx(), typed->maximumValueofx(), "x");
        const double y = clampToOptionalRange(independentVariables[1], typed->minimumValueofy(), typed->maximumValueofy(), "y");
        const double z = clampToOptionalRange(independentVariables[2], typed->minimumValueofz(), typed->maximumValueofz(), "z");
        const double x2 = std::pow(x, 2);
        const double y2 = std::pow(y, 2);
        const double z2 = std::pow(z, 2);
        double result = 0.0;
        result += valueOrZero(typed->coefficient1Constant());
        result += valueOrZero(typed->coefficient2xPOW2()) * x2;
        result += valueOrZero(typed->coefficient3x()) * x;
        result += valueOrZero(typed->coefficient4yPOW2()) * y2;
        result += valueOrZero(typed->coefficient5y()) * y;
        result += valueOrZero(typed->coefficient6zPOW2()) * z2;
        result += valueOrZero(typed->coefficient7z()) * z;
        result += valueOrZero(typed->coefficient8xPOW2TIMESYPOW2()) * x2 * y2;
        result += valueOrZero(typed->coefficient9xTIMESY()) * x * y;
        result += valueOrZero(typed->coefficient10xTIMESYPOW2()) * x * y2;
        result += valueOrZero(typed->coefficient11xPOW2TIMESY()) * x2 * y;
        result += valueOrZero(typed->coefficient12xPOW2TIMESZPOW2()) * x2 * z2;
        result += valueOrZero(typed->coefficient13xTIMESZ()) * x * z;
        result += valueOrZero(typed->coefficient14xTIMESZPOW2()) * x * z2;
        result += valueOrZero(typed->coefficient15xPOW2TIMESZ()) * x2 * z;
        result += valueOrZero(typed->coefficient16yPOW2TIMESZPOW2()) * y2 * z2;
        result += valueOrZero(typed->coefficient17yTIMESZ()) * y * z;
        result += valueOrZero(typed->coefficient18yTIMESZPOW2()) * y * z2;
        result += valueOrZero(typed->coefficient19yPOW2TIMESZ()) * y2 * z;
        result += valueOrZero(typed->coefficient20xPOW2TIMESYPOW2TIMESZPOW2()) * x2 * y2 * z2;
        result += valueOrZero(typed->coefficient21xPOW2TIMESYPOW2TIMESZ()) * x2 * y2 * z;
        result += valueOrZero(typed->coefficient22xPOW2TIMESYTIMESZPOW2()) * x2 * y * z2;
        result += valueOrZero(typed->coefficient23xTIMESYPOW2TIMESZPOW2()) * x * y2 * z2;
        result += valueOrZero(typed->coefficient24xPOW2TIMESYTIMESZ()) * x2 * y * z;
        result += valueOrZero(typed->coefficient25xTIMESYPOW2TIMESZ()) * x * y2 * z;
        result += valueOrZero(typed->coefficient26xTIMESYTIMESZPOW2()) * x * y * z2;
        result += valueOrZero(typed->coefficient27xTIMESYTIMESZ()) * x * y * z;
        return applyOutputLimits(result, typed->minimumCurveOutput(), typed->maximumCurveOutput());
      } else if (auto typed = curve.optionalCast<CurveQuadLinear>()) {
        OS_ASSERT(independentVariables.size() == 4u);
        const double w = clampToRange(independentVariables[0], typed->minimumValueofw(), typed->maximumValueofw(), "w");
        const double x = clampToRange(independentVariables[1], typed->minimumValueofx(), typed->maximumValueofx(), "x");
        const double y = clampToRange(independentVariables[2], typed->minimumValueofy(), typed->maximumValueofy(), "y");
        const double z = clampToRange(independentVariables[3], typed->minimumValueofz(), typed->maximumValueofz(), "z");
        double result = typed->coefficient1Constant();
        result += typed->coefficient2w() * w;
        result += typed->coefficient3x() * x;
        result += typed->coefficient4y() * y;
        result += typed->coefficient5z() * z;
        return applyOutputLimits(result, typed->minimumCurveOutput(), typed->maximumCurveOutput());
      } else if (auto typed = curve.optionalCast<CurveQuintLinear>()) {
        OS_ASSERT(independentVariables.size() == 5u);
        const double v = clampToRange(independentVariables[0], typed->minimumValueofv(), typed->maximumValueofv(), "v");
        const double w = clampToRange(independentVariables[1], typed->minimumValueofw(), typed->maximumValueofw(), "w");
        const double x = clampToRange(independentVariables[2], typed->minimumValueofx(), typed->maximumValueofx(), "x");
        const double y = clampToRange(independentVariables[3], typed->minimumValueofy(), typed->maximumValueofy(), "y");
        const double z = clampToRange(independentVariables[4], typed->minimumValueofz(), typed->maximumValueofz(), "z");
        double result = typed->coefficient1Constant();
        result += typed->coefficient2v() * v;
        result += typed->coefficient3w() * w;
        result += typed->coefficient4x() * x;
        result += typed->coefficient5y() * y;
        result += typed->coefficient6z() * z;
        return applyOutputLimits(result, typed->minimumCurveOutput(), typed->maximumCurveOutput());
      } else if (curve.optionalCast<TableLookup>()) {
        LOG_FREE(Warn, "openstudio.epmodel.Curve", "Curve evaluation isn't implemented for TableLookup.");
        return -9999.0;
      } else if (curve.optionalCast<CurveFunctionalPressureDrop>()) {
        LOG_FREE_AND_THROW("openstudio.epmodel.Curve",
                           "CurveFunctionalPressureDrop must be evaluated by EnergyPlus in the context of plant pressure simulations.");
      }

      LOG_FREE_AND_THROW("openstudio.epmodel.Curve", "Unsupported curve type '" << curve.iddObject().type().valueName() << "'.");
    }

    double Curve_Impl::evaluate(double x) const {
      return evaluate(std::vector<double>{x});
    }

    double Curve_Impl::evaluate(double x, double y) const {
      return evaluate(std::vector<double>{x, y});
    }

    double Curve_Impl::evaluate(double x, double y, double z) const {
      return evaluate(std::vector<double>{x, y, z});
    }

    double Curve_Impl::evaluate(double w, double x, double y, double z) const {
      return evaluate(std::vector<double>{w, x, y, z});
    }

    double Curve_Impl::evaluate(double v, double w, double x, double y, double z) const {
      return evaluate(std::vector<double>{v, w, x, y, z});
    }

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
