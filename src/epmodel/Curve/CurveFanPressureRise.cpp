/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "Curve/CurveFanPressureRise.hpp"
#include "Curve/CurveFanPressureRise_Impl.hpp"

#include "Model.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/idd/Curve_FanPressureRise_FieldEnums.hxx>
#include <utilities/idd/IddEnums.hxx>

namespace openstudio {
namespace epmodel {

  CurveFanPressureRise::CurveFanPressureRise(const Model& model) : ModelObject(CurveFanPressureRise::iddObjectType(), model) {
    OS_ASSERT(getImpl<detail::CurveFanPressureRise_Impl>());
    OS_ASSERT(setCoefficient1C1(1.0));
    OS_ASSERT(setCoefficient2C2(1.0));
    OS_ASSERT(setCoefficient3C3(1.0));
    OS_ASSERT(setCoefficient4C4(1.0));
    OS_ASSERT(setMinimumValueofQfan(0.0));
    OS_ASSERT(setMaximumValueofQfan(10.0));
    OS_ASSERT(setMinimumValueofPsm(0.0));
    OS_ASSERT(setMaximumValueofPsm(500.0));
    resetMinimumCurveOutput();
    resetMaximumCurveOutput();
  }

  CurveFanPressureRise::CurveFanPressureRise(std::shared_ptr<detail::CurveFanPressureRise_Impl> impl) : ModelObject(std::move(impl)) {}

  IddObjectType CurveFanPressureRise::iddObjectType() {
    return IddObjectType::Curve_FanPressureRise;
  }

  double CurveFanPressureRise::coefficient1C1() const {
    return getImpl<detail::CurveFanPressureRise_Impl>()->coefficient1C1();
  }

  bool CurveFanPressureRise::setCoefficient1C1(double coefficient1C1) {
    return getImpl<detail::CurveFanPressureRise_Impl>()->setCoefficient1C1(coefficient1C1);
  }

  double CurveFanPressureRise::coefficient2C2() const {
    return getImpl<detail::CurveFanPressureRise_Impl>()->coefficient2C2();
  }

  bool CurveFanPressureRise::setCoefficient2C2(double coefficient2C2) {
    return getImpl<detail::CurveFanPressureRise_Impl>()->setCoefficient2C2(coefficient2C2);
  }

  double CurveFanPressureRise::coefficient3C3() const {
    return getImpl<detail::CurveFanPressureRise_Impl>()->coefficient3C3();
  }

  bool CurveFanPressureRise::setCoefficient3C3(double coefficient3C3) {
    return getImpl<detail::CurveFanPressureRise_Impl>()->setCoefficient3C3(coefficient3C3);
  }

  double CurveFanPressureRise::coefficient4C4() const {
    return getImpl<detail::CurveFanPressureRise_Impl>()->coefficient4C4();
  }

  bool CurveFanPressureRise::setCoefficient4C4(double coefficient4C4) {
    return getImpl<detail::CurveFanPressureRise_Impl>()->setCoefficient4C4(coefficient4C4);
  }

  double CurveFanPressureRise::minimumValueofQfan() const {
    return getImpl<detail::CurveFanPressureRise_Impl>()->minimumValueofQfan();
  }

  bool CurveFanPressureRise::setMinimumValueofQfan(double minimumValueofQfan) {
    return getImpl<detail::CurveFanPressureRise_Impl>()->setMinimumValueofQfan(minimumValueofQfan);
  }

  double CurveFanPressureRise::maximumValueofQfan() const {
    return getImpl<detail::CurveFanPressureRise_Impl>()->maximumValueofQfan();
  }

  bool CurveFanPressureRise::setMaximumValueofQfan(double maximumValueofQfan) {
    return getImpl<detail::CurveFanPressureRise_Impl>()->setMaximumValueofQfan(maximumValueofQfan);
  }

  double CurveFanPressureRise::minimumValueofPsm() const {
    return getImpl<detail::CurveFanPressureRise_Impl>()->minimumValueofPsm();
  }

  bool CurveFanPressureRise::setMinimumValueofPsm(double minimumValueofPsm) {
    return getImpl<detail::CurveFanPressureRise_Impl>()->setMinimumValueofPsm(minimumValueofPsm);
  }

  double CurveFanPressureRise::maximumValueofPsm() const {
    return getImpl<detail::CurveFanPressureRise_Impl>()->maximumValueofPsm();
  }

  bool CurveFanPressureRise::setMaximumValueofPsm(double maximumValueofPsm) {
    return getImpl<detail::CurveFanPressureRise_Impl>()->setMaximumValueofPsm(maximumValueofPsm);
  }

  boost::optional<double> CurveFanPressureRise::minimumCurveOutput() const {
    return getImpl<detail::CurveFanPressureRise_Impl>()->minimumCurveOutput();
  }

  bool CurveFanPressureRise::setMinimumCurveOutput(double minimumCurveOutput) {
    return getImpl<detail::CurveFanPressureRise_Impl>()->setMinimumCurveOutput(minimumCurveOutput);
  }

  void CurveFanPressureRise::resetMinimumCurveOutput() {
    getImpl<detail::CurveFanPressureRise_Impl>()->resetMinimumCurveOutput();
  }

  boost::optional<double> CurveFanPressureRise::maximumCurveOutput() const {
    return getImpl<detail::CurveFanPressureRise_Impl>()->maximumCurveOutput();
  }

  bool CurveFanPressureRise::setMaximumCurveOutput(double maximumCurveOutput) {
    return getImpl<detail::CurveFanPressureRise_Impl>()->setMaximumCurveOutput(maximumCurveOutput);
  }

  void CurveFanPressureRise::resetMaximumCurveOutput() {
    getImpl<detail::CurveFanPressureRise_Impl>()->resetMaximumCurveOutput();
  }

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
  namespace detail {

    double CurveFanPressureRise_Impl::coefficient1C1() const {
      const auto value = getDouble(openstudio::Curve_FanPressureRiseFields::Coefficient1C1, true);
      OS_ASSERT(value);
      return *value;
    }

    bool CurveFanPressureRise_Impl::setCoefficient1C1(double coefficient1C1) {
      const bool result = setDouble(openstudio::Curve_FanPressureRiseFields::Coefficient1C1, coefficient1C1);
      OS_ASSERT(result);
      return result;
    }

    double CurveFanPressureRise_Impl::coefficient2C2() const {
      const auto value = getDouble(openstudio::Curve_FanPressureRiseFields::Coefficient2C2, true);
      OS_ASSERT(value);
      return *value;
    }

    bool CurveFanPressureRise_Impl::setCoefficient2C2(double coefficient2C2) {
      const bool result = setDouble(openstudio::Curve_FanPressureRiseFields::Coefficient2C2, coefficient2C2);
      OS_ASSERT(result);
      return result;
    }

    double CurveFanPressureRise_Impl::coefficient3C3() const {
      const auto value = getDouble(openstudio::Curve_FanPressureRiseFields::Coefficient3C3, true);
      OS_ASSERT(value);
      return *value;
    }

    bool CurveFanPressureRise_Impl::setCoefficient3C3(double coefficient3C3) {
      const bool result = setDouble(openstudio::Curve_FanPressureRiseFields::Coefficient3C3, coefficient3C3);
      OS_ASSERT(result);
      return result;
    }

    double CurveFanPressureRise_Impl::coefficient4C4() const {
      const auto value = getDouble(openstudio::Curve_FanPressureRiseFields::Coefficient4C4, true);
      OS_ASSERT(value);
      return *value;
    }

    bool CurveFanPressureRise_Impl::setCoefficient4C4(double coefficient4C4) {
      const bool result = setDouble(openstudio::Curve_FanPressureRiseFields::Coefficient4C4, coefficient4C4);
      OS_ASSERT(result);
      return result;
    }

    double CurveFanPressureRise_Impl::minimumValueofQfan() const {
      const auto value = getDouble(openstudio::Curve_FanPressureRiseFields::MinimumValueofQfan, true);
      OS_ASSERT(value);
      return *value;
    }

    bool CurveFanPressureRise_Impl::setMinimumValueofQfan(double minimumValueofQfan) {
      const bool result = setDouble(openstudio::Curve_FanPressureRiseFields::MinimumValueofQfan, minimumValueofQfan);
      OS_ASSERT(result);
      return result;
    }

    double CurveFanPressureRise_Impl::maximumValueofQfan() const {
      const auto value = getDouble(openstudio::Curve_FanPressureRiseFields::MaximumValueofQfan, true);
      OS_ASSERT(value);
      return *value;
    }

    bool CurveFanPressureRise_Impl::setMaximumValueofQfan(double maximumValueofQfan) {
      const bool result = setDouble(openstudio::Curve_FanPressureRiseFields::MaximumValueofQfan, maximumValueofQfan);
      OS_ASSERT(result);
      return result;
    }

    double CurveFanPressureRise_Impl::minimumValueofPsm() const {
      const auto value = getDouble(openstudio::Curve_FanPressureRiseFields::MinimumValueofPsm, true);
      OS_ASSERT(value);
      return *value;
    }

    bool CurveFanPressureRise_Impl::setMinimumValueofPsm(double minimumValueofPsm) {
      const bool result = setDouble(openstudio::Curve_FanPressureRiseFields::MinimumValueofPsm, minimumValueofPsm);
      OS_ASSERT(result);
      return result;
    }

    double CurveFanPressureRise_Impl::maximumValueofPsm() const {
      const auto value = getDouble(openstudio::Curve_FanPressureRiseFields::MaximumValueofPsm, true);
      OS_ASSERT(value);
      return *value;
    }

    bool CurveFanPressureRise_Impl::setMaximumValueofPsm(double maximumValueofPsm) {
      const bool result = setDouble(openstudio::Curve_FanPressureRiseFields::MaximumValueofPsm, maximumValueofPsm);
      OS_ASSERT(result);
      return result;
    }

    boost::optional<double> CurveFanPressureRise_Impl::minimumCurveOutput() const {
      return getDouble(openstudio::Curve_FanPressureRiseFields::MinimumCurveOutput, true);
    }

    bool CurveFanPressureRise_Impl::setMinimumCurveOutput(double minimumCurveOutput) {
      const bool result = setDouble(openstudio::Curve_FanPressureRiseFields::MinimumCurveOutput, minimumCurveOutput);
      OS_ASSERT(result);
      return result;
    }

    void CurveFanPressureRise_Impl::resetMinimumCurveOutput() {
      OS_ASSERT(setString(openstudio::Curve_FanPressureRiseFields::MinimumCurveOutput, ""));
    }

    boost::optional<double> CurveFanPressureRise_Impl::maximumCurveOutput() const {
      return getDouble(openstudio::Curve_FanPressureRiseFields::MaximumCurveOutput, true);
    }

    bool CurveFanPressureRise_Impl::setMaximumCurveOutput(double maximumCurveOutput) {
      const bool result = setDouble(openstudio::Curve_FanPressureRiseFields::MaximumCurveOutput, maximumCurveOutput);
      OS_ASSERT(result);
      return result;
    }

    void CurveFanPressureRise_Impl::resetMaximumCurveOutput() {
      OS_ASSERT(setString(openstudio::Curve_FanPressureRiseFields::MaximumCurveOutput, ""));
    }

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
