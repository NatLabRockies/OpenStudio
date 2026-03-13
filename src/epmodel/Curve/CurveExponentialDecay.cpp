/***********************************************************************************************************************
 *  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
 *  See also https://openstudio.net/license
 ***********************************************************************************************************************/

#include "Curve/CurveExponentialDecay.hpp"
#include "Curve/CurveExponentialDecay_Impl.hpp"

#include "Model.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/idd/Curve_ExponentialDecay_FieldEnums.hxx>
#include <utilities/idd/IddEnums.hxx>
#include <utilities/idd/IddFactory.hxx>

namespace openstudio {
namespace epmodel {

  CurveExponentialDecay::CurveExponentialDecay(const Model& model) : Curve(CurveExponentialDecay::iddObjectType(), model) {
    OS_ASSERT(getImpl<detail::CurveExponentialDecay_Impl>());
    OS_ASSERT(setCoefficient1C1(0.0));
    OS_ASSERT(setCoefficient2C2(1.0));
    OS_ASSERT(setCoefficient3C3(-1.0));
    OS_ASSERT(setMinimumValueofx(0.0));
    OS_ASSERT(setMaximumValueofx(1.0));
    resetMinimumCurveOutput();
    resetMaximumCurveOutput();
    resetInputUnitTypeforx();
    resetOutputUnitType();
  }

  CurveExponentialDecay::CurveExponentialDecay(std::shared_ptr<detail::CurveExponentialDecay_Impl> impl) : Curve(std::move(impl)) {}

  IddObjectType CurveExponentialDecay::iddObjectType() {
    return IddObjectType::Curve_ExponentialDecay;
  }

  std::vector<std::string> CurveExponentialDecay::validInputUnitTypeforxValues() {
    return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(), openstudio::Curve_ExponentialDecayFields::InputUnitTypeforx);
  }

  std::vector<std::string> CurveExponentialDecay::validOutputUnitTypeValues() {
    return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(), openstudio::Curve_ExponentialDecayFields::OutputUnitType);
  }

  double CurveExponentialDecay::coefficient1C1() const {
    return getImpl<detail::CurveExponentialDecay_Impl>()->coefficient1C1();
  }

  bool CurveExponentialDecay::setCoefficient1C1(double coefficient1C1) {
    return getImpl<detail::CurveExponentialDecay_Impl>()->setCoefficient1C1(coefficient1C1);
  }

  double CurveExponentialDecay::coefficient2C2() const {
    return getImpl<detail::CurveExponentialDecay_Impl>()->coefficient2C2();
  }

  bool CurveExponentialDecay::setCoefficient2C2(double coefficient2C2) {
    return getImpl<detail::CurveExponentialDecay_Impl>()->setCoefficient2C2(coefficient2C2);
  }

  double CurveExponentialDecay::coefficient3C3() const {
    return getImpl<detail::CurveExponentialDecay_Impl>()->coefficient3C3();
  }

  bool CurveExponentialDecay::setCoefficient3C3(double coefficient3C3) {
    return getImpl<detail::CurveExponentialDecay_Impl>()->setCoefficient3C3(coefficient3C3);
  }

  double CurveExponentialDecay::minimumValueofx() const {
    return getImpl<detail::CurveExponentialDecay_Impl>()->minimumValueofx();
  }

  bool CurveExponentialDecay::setMinimumValueofx(double minimumValueofx) {
    return getImpl<detail::CurveExponentialDecay_Impl>()->setMinimumValueofx(minimumValueofx);
  }

  double CurveExponentialDecay::maximumValueofx() const {
    return getImpl<detail::CurveExponentialDecay_Impl>()->maximumValueofx();
  }

  bool CurveExponentialDecay::setMaximumValueofx(double maximumValueofx) {
    return getImpl<detail::CurveExponentialDecay_Impl>()->setMaximumValueofx(maximumValueofx);
  }

  boost::optional<double> CurveExponentialDecay::minimumCurveOutput() const {
    return getImpl<detail::CurveExponentialDecay_Impl>()->minimumCurveOutput();
  }

  bool CurveExponentialDecay::setMinimumCurveOutput(double minimumCurveOutput) {
    return getImpl<detail::CurveExponentialDecay_Impl>()->setMinimumCurveOutput(minimumCurveOutput);
  }

  void CurveExponentialDecay::resetMinimumCurveOutput() {
    getImpl<detail::CurveExponentialDecay_Impl>()->resetMinimumCurveOutput();
  }

  boost::optional<double> CurveExponentialDecay::maximumCurveOutput() const {
    return getImpl<detail::CurveExponentialDecay_Impl>()->maximumCurveOutput();
  }

  bool CurveExponentialDecay::setMaximumCurveOutput(double maximumCurveOutput) {
    return getImpl<detail::CurveExponentialDecay_Impl>()->setMaximumCurveOutput(maximumCurveOutput);
  }

  void CurveExponentialDecay::resetMaximumCurveOutput() {
    getImpl<detail::CurveExponentialDecay_Impl>()->resetMaximumCurveOutput();
  }

  std::string CurveExponentialDecay::inputUnitTypeforx() const {
    return getImpl<detail::CurveExponentialDecay_Impl>()->inputUnitTypeforx();
  }

  bool CurveExponentialDecay::setInputUnitTypeforx(const std::string& inputUnitTypeforx) {
    return getImpl<detail::CurveExponentialDecay_Impl>()->setInputUnitTypeforx(inputUnitTypeforx);
  }

  bool CurveExponentialDecay::isInputUnitTypeforxDefaulted() const {
    return getImpl<detail::CurveExponentialDecay_Impl>()->isInputUnitTypeforxDefaulted();
  }

  void CurveExponentialDecay::resetInputUnitTypeforx() {
    getImpl<detail::CurveExponentialDecay_Impl>()->resetInputUnitTypeforx();
  }

  std::string CurveExponentialDecay::outputUnitType() const {
    return getImpl<detail::CurveExponentialDecay_Impl>()->outputUnitType();
  }

  bool CurveExponentialDecay::setOutputUnitType(const std::string& outputUnitType) {
    return getImpl<detail::CurveExponentialDecay_Impl>()->setOutputUnitType(outputUnitType);
  }

  bool CurveExponentialDecay::isOutputUnitTypeDefaulted() const {
    return getImpl<detail::CurveExponentialDecay_Impl>()->isOutputUnitTypeDefaulted();
  }

  void CurveExponentialDecay::resetOutputUnitType() {
    getImpl<detail::CurveExponentialDecay_Impl>()->resetOutputUnitType();
  }

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
  namespace detail {

    double CurveExponentialDecay_Impl::coefficient1C1() const {
      const auto value = getDouble(openstudio::Curve_ExponentialDecayFields::Coefficient1C1, true);
      OS_ASSERT(value);
      return *value;
    }

    bool CurveExponentialDecay_Impl::setCoefficient1C1(double coefficient1C1) {
      const bool result = setDouble(openstudio::Curve_ExponentialDecayFields::Coefficient1C1, coefficient1C1);
      OS_ASSERT(result);
      return result;
    }

    double CurveExponentialDecay_Impl::coefficient2C2() const {
      const auto value = getDouble(openstudio::Curve_ExponentialDecayFields::Coefficient2C2, true);
      OS_ASSERT(value);
      return *value;
    }

    bool CurveExponentialDecay_Impl::setCoefficient2C2(double coefficient2C2) {
      const bool result = setDouble(openstudio::Curve_ExponentialDecayFields::Coefficient2C2, coefficient2C2);
      OS_ASSERT(result);
      return result;
    }

    double CurveExponentialDecay_Impl::coefficient3C3() const {
      const auto value = getDouble(openstudio::Curve_ExponentialDecayFields::Coefficient3C3, true);
      OS_ASSERT(value);
      return *value;
    }

    bool CurveExponentialDecay_Impl::setCoefficient3C3(double coefficient3C3) {
      const bool result = setDouble(openstudio::Curve_ExponentialDecayFields::Coefficient3C3, coefficient3C3);
      OS_ASSERT(result);
      return result;
    }

    double CurveExponentialDecay_Impl::minimumValueofx() const {
      const auto value = getDouble(openstudio::Curve_ExponentialDecayFields::MinimumValueofx, true);
      OS_ASSERT(value);
      return *value;
    }

    bool CurveExponentialDecay_Impl::setMinimumValueofx(double minimumValueofx) {
      const bool result = setDouble(openstudio::Curve_ExponentialDecayFields::MinimumValueofx, minimumValueofx);
      OS_ASSERT(result);
      return result;
    }

    double CurveExponentialDecay_Impl::maximumValueofx() const {
      const auto value = getDouble(openstudio::Curve_ExponentialDecayFields::MaximumValueofx, true);
      OS_ASSERT(value);
      return *value;
    }

    bool CurveExponentialDecay_Impl::setMaximumValueofx(double maximumValueofx) {
      const bool result = setDouble(openstudio::Curve_ExponentialDecayFields::MaximumValueofx, maximumValueofx);
      OS_ASSERT(result);
      return result;
    }

    boost::optional<double> CurveExponentialDecay_Impl::minimumCurveOutput() const {
      return getDouble(openstudio::Curve_ExponentialDecayFields::MinimumCurveOutput, true);
    }

    bool CurveExponentialDecay_Impl::setMinimumCurveOutput(double minimumCurveOutput) {
      const bool result = setDouble(openstudio::Curve_ExponentialDecayFields::MinimumCurveOutput, minimumCurveOutput);
      OS_ASSERT(result);
      return result;
    }

    void CurveExponentialDecay_Impl::resetMinimumCurveOutput() {
      OS_ASSERT(setString(openstudio::Curve_ExponentialDecayFields::MinimumCurveOutput, ""));
    }

    boost::optional<double> CurveExponentialDecay_Impl::maximumCurveOutput() const {
      return getDouble(openstudio::Curve_ExponentialDecayFields::MaximumCurveOutput, true);
    }

    bool CurveExponentialDecay_Impl::setMaximumCurveOutput(double maximumCurveOutput) {
      const bool result = setDouble(openstudio::Curve_ExponentialDecayFields::MaximumCurveOutput, maximumCurveOutput);
      OS_ASSERT(result);
      return result;
    }

    void CurveExponentialDecay_Impl::resetMaximumCurveOutput() {
      OS_ASSERT(setString(openstudio::Curve_ExponentialDecayFields::MaximumCurveOutput, ""));
    }

    std::string CurveExponentialDecay_Impl::inputUnitTypeforx() const {
      const auto value = getString(openstudio::Curve_ExponentialDecayFields::InputUnitTypeforx, true);
      OS_ASSERT(value);
      return *value;
    }

    bool CurveExponentialDecay_Impl::setInputUnitTypeforx(const std::string& inputUnitTypeforx) {
      return setString(openstudio::Curve_ExponentialDecayFields::InputUnitTypeforx, inputUnitTypeforx);
    }

    bool CurveExponentialDecay_Impl::isInputUnitTypeforxDefaulted() const {
      return isEmpty(openstudio::Curve_ExponentialDecayFields::InputUnitTypeforx);
    }

    void CurveExponentialDecay_Impl::resetInputUnitTypeforx() {
      OS_ASSERT(setString(openstudio::Curve_ExponentialDecayFields::InputUnitTypeforx, ""));
    }

    std::string CurveExponentialDecay_Impl::outputUnitType() const {
      const auto value = getString(openstudio::Curve_ExponentialDecayFields::OutputUnitType, true);
      OS_ASSERT(value);
      return *value;
    }

    bool CurveExponentialDecay_Impl::setOutputUnitType(const std::string& outputUnitType) {
      return setString(openstudio::Curve_ExponentialDecayFields::OutputUnitType, outputUnitType);
    }

    bool CurveExponentialDecay_Impl::isOutputUnitTypeDefaulted() const {
      return isEmpty(openstudio::Curve_ExponentialDecayFields::OutputUnitType);
    }

    void CurveExponentialDecay_Impl::resetOutputUnitType() {
      OS_ASSERT(setString(openstudio::Curve_ExponentialDecayFields::OutputUnitType, ""));
    }

    std::vector<std::string> CurveExponentialDecay_Impl::validInputUnitTypeforxValues() const {
      return openstudio::epmodel::CurveExponentialDecay::validInputUnitTypeforxValues();
    }

    std::vector<std::string> CurveExponentialDecay_Impl::validOutputUnitTypeValues() const {
      return openstudio::epmodel::CurveExponentialDecay::validOutputUnitTypeValues();
    }

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
