/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "Curve/CurveDoubleExponentialDecay.hpp"
#include "Curve/CurveDoubleExponentialDecay_Impl.hpp"

#include "Model.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/core/StringHelpers.hpp>
#include <utilities/idd/Curve_DoubleExponentialDecay_FieldEnums.hxx>
#include <utilities/idd/IddEnums.hxx>
#include <utilities/idd/IddFactory.hxx>

namespace openstudio {
namespace epmodel {

  namespace {

    boost::optional<std::string> curveDoubleExponentialDecayDefaultString(unsigned fieldIndex) {
      const auto iddObject = IddFactory::instance().getObject(IddObjectType::Curve_DoubleExponentialDecay);
      if (!iddObject) {
        return boost::none;
      }

      const auto iddField = iddObject->getField(fieldIndex);
      if (!iddField || !iddField->properties().stringDefault) {
        return boost::none;
      }

      return *(iddField->properties().stringDefault);
    }

  }  // namespace

  CurveDoubleExponentialDecay::CurveDoubleExponentialDecay(const Model& model) : Curve(CurveDoubleExponentialDecay::iddObjectType(), model) {
    OS_ASSERT(getImpl<detail::CurveDoubleExponentialDecay_Impl>());
    OS_ASSERT(setCoefficient1C1(0.0));
    OS_ASSERT(setCoefficient2C2(0.0));
    OS_ASSERT(setCoefficient3C3(0.0));
    OS_ASSERT(setCoefficient4C4(0.0));
    OS_ASSERT(setCoefficient5C5(0.0));
    OS_ASSERT(setMinimumValueofx(0.0));
    OS_ASSERT(setMaximumValueofx(1.0));
  }

  CurveDoubleExponentialDecay::CurveDoubleExponentialDecay(std::shared_ptr<detail::CurveDoubleExponentialDecay_Impl> impl) : Curve(std::move(impl)) {}

  IddObjectType CurveDoubleExponentialDecay::iddObjectType() {
    return IddObjectType::Curve_DoubleExponentialDecay;
  }

  std::vector<std::string> CurveDoubleExponentialDecay::validInputUnitTypeforxValues() {
    return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(), openstudio::Curve_DoubleExponentialDecayFields::InputUnitTypeforx);
  }

  std::vector<std::string> CurveDoubleExponentialDecay::validOutputUnitTypeValues() {
    return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(), openstudio::Curve_DoubleExponentialDecayFields::OutputUnitType);
  }

  double CurveDoubleExponentialDecay::coefficient1C1() const {
    return getImpl<detail::CurveDoubleExponentialDecay_Impl>()->coefficient1C1();
  }

  bool CurveDoubleExponentialDecay::setCoefficient1C1(double coefficient1C1) {
    return getImpl<detail::CurveDoubleExponentialDecay_Impl>()->setCoefficient1C1(coefficient1C1);
  }

  double CurveDoubleExponentialDecay::coefficient2C2() const {
    return getImpl<detail::CurveDoubleExponentialDecay_Impl>()->coefficient2C2();
  }

  bool CurveDoubleExponentialDecay::setCoefficient2C2(double coefficient2C2) {
    return getImpl<detail::CurveDoubleExponentialDecay_Impl>()->setCoefficient2C2(coefficient2C2);
  }

  double CurveDoubleExponentialDecay::coefficient3C3() const {
    return getImpl<detail::CurveDoubleExponentialDecay_Impl>()->coefficient3C3();
  }

  bool CurveDoubleExponentialDecay::setCoefficient3C3(double coefficient3C3) {
    return getImpl<detail::CurveDoubleExponentialDecay_Impl>()->setCoefficient3C3(coefficient3C3);
  }

  double CurveDoubleExponentialDecay::coefficient4C4() const {
    return getImpl<detail::CurveDoubleExponentialDecay_Impl>()->coefficient4C4();
  }

  bool CurveDoubleExponentialDecay::setCoefficient4C4(double coefficient4C4) {
    return getImpl<detail::CurveDoubleExponentialDecay_Impl>()->setCoefficient4C4(coefficient4C4);
  }

  double CurveDoubleExponentialDecay::coefficient3C4() const {
    return getImpl<detail::CurveDoubleExponentialDecay_Impl>()->coefficient4C4();
  }

  bool CurveDoubleExponentialDecay::setCoefficient3C4(double coefficient4C4) {
    return getImpl<detail::CurveDoubleExponentialDecay_Impl>()->setCoefficient4C4(coefficient4C4);
  }

  double CurveDoubleExponentialDecay::coefficient5C5() const {
    return getImpl<detail::CurveDoubleExponentialDecay_Impl>()->coefficient5C5();
  }

  bool CurveDoubleExponentialDecay::setCoefficient5C5(double coefficient5C5) {
    return getImpl<detail::CurveDoubleExponentialDecay_Impl>()->setCoefficient5C5(coefficient5C5);
  }

  double CurveDoubleExponentialDecay::coefficient3C5() const {
    return getImpl<detail::CurveDoubleExponentialDecay_Impl>()->coefficient5C5();
  }

  bool CurveDoubleExponentialDecay::setCoefficient3C5(double coefficient5C5) {
    return getImpl<detail::CurveDoubleExponentialDecay_Impl>()->setCoefficient5C5(coefficient5C5);
  }

  double CurveDoubleExponentialDecay::minimumValueofx() const {
    return getImpl<detail::CurveDoubleExponentialDecay_Impl>()->minimumValueofx();
  }

  bool CurveDoubleExponentialDecay::setMinimumValueofx(double minimumValueofx) {
    return getImpl<detail::CurveDoubleExponentialDecay_Impl>()->setMinimumValueofx(minimumValueofx);
  }

  double CurveDoubleExponentialDecay::maximumValueofx() const {
    return getImpl<detail::CurveDoubleExponentialDecay_Impl>()->maximumValueofx();
  }

  bool CurveDoubleExponentialDecay::setMaximumValueofx(double maximumValueofx) {
    return getImpl<detail::CurveDoubleExponentialDecay_Impl>()->setMaximumValueofx(maximumValueofx);
  }

  boost::optional<double> CurveDoubleExponentialDecay::minimumCurveOutput() const {
    return getImpl<detail::CurveDoubleExponentialDecay_Impl>()->minimumCurveOutput();
  }

  bool CurveDoubleExponentialDecay::setMinimumCurveOutput(double minimumCurveOutput) {
    return getImpl<detail::CurveDoubleExponentialDecay_Impl>()->setMinimumCurveOutput(minimumCurveOutput);
  }

  void CurveDoubleExponentialDecay::resetMinimumCurveOutput() {
    getImpl<detail::CurveDoubleExponentialDecay_Impl>()->resetMinimumCurveOutput();
  }

  boost::optional<double> CurveDoubleExponentialDecay::maximumCurveOutput() const {
    return getImpl<detail::CurveDoubleExponentialDecay_Impl>()->maximumCurveOutput();
  }

  bool CurveDoubleExponentialDecay::setMaximumCurveOutput(double maximumCurveOutput) {
    return getImpl<detail::CurveDoubleExponentialDecay_Impl>()->setMaximumCurveOutput(maximumCurveOutput);
  }

  void CurveDoubleExponentialDecay::resetMaximumCurveOutput() {
    getImpl<detail::CurveDoubleExponentialDecay_Impl>()->resetMaximumCurveOutput();
  }

  std::string CurveDoubleExponentialDecay::inputUnitTypeforx() const {
    return getImpl<detail::CurveDoubleExponentialDecay_Impl>()->inputUnitTypeforx();
  }

  bool CurveDoubleExponentialDecay::isInputUnitTypeforxDefaulted() const {
    return getImpl<detail::CurveDoubleExponentialDecay_Impl>()->isInputUnitTypeforxDefaulted();
  }

  bool CurveDoubleExponentialDecay::setInputUnitTypeforx(const std::string& inputUnitTypeforx) {
    return getImpl<detail::CurveDoubleExponentialDecay_Impl>()->setInputUnitTypeforx(inputUnitTypeforx);
  }

  void CurveDoubleExponentialDecay::resetInputUnitTypeforx() {
    getImpl<detail::CurveDoubleExponentialDecay_Impl>()->resetInputUnitTypeforx();
  }

  std::string CurveDoubleExponentialDecay::outputUnitType() const {
    return getImpl<detail::CurveDoubleExponentialDecay_Impl>()->outputUnitType();
  }

  bool CurveDoubleExponentialDecay::isOutputUnitTypeDefaulted() const {
    return getImpl<detail::CurveDoubleExponentialDecay_Impl>()->isOutputUnitTypeDefaulted();
  }

  bool CurveDoubleExponentialDecay::setOutputUnitType(const std::string& outputUnitType) {
    return getImpl<detail::CurveDoubleExponentialDecay_Impl>()->setOutputUnitType(outputUnitType);
  }

  void CurveDoubleExponentialDecay::resetOutputUnitType() {
    getImpl<detail::CurveDoubleExponentialDecay_Impl>()->resetOutputUnitType();
  }

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
  namespace detail {

    double CurveDoubleExponentialDecay_Impl::coefficient1C1() const {
      const auto value = getDouble(openstudio::Curve_DoubleExponentialDecayFields::Coefficient1C1, true);
      OS_ASSERT(value);
      return *value;
    }

    double CurveDoubleExponentialDecay_Impl::coefficient2C2() const {
      const auto value = getDouble(openstudio::Curve_DoubleExponentialDecayFields::Coefficient2C2, true);
      OS_ASSERT(value);
      return *value;
    }

    double CurveDoubleExponentialDecay_Impl::coefficient3C3() const {
      const auto value = getDouble(openstudio::Curve_DoubleExponentialDecayFields::Coefficient3C3, true);
      OS_ASSERT(value);
      return *value;
    }

    double CurveDoubleExponentialDecay_Impl::coefficient4C4() const {
      const auto value = getDouble(openstudio::Curve_DoubleExponentialDecayFields::Coefficient4C4, true);
      OS_ASSERT(value);
      return *value;
    }

    double CurveDoubleExponentialDecay_Impl::coefficient5C5() const {
      const auto value = getDouble(openstudio::Curve_DoubleExponentialDecayFields::Coefficient5C5, true);
      OS_ASSERT(value);
      return *value;
    }

    double CurveDoubleExponentialDecay_Impl::minimumValueofx() const {
      const auto value = getDouble(openstudio::Curve_DoubleExponentialDecayFields::MinimumValueofx, true);
      OS_ASSERT(value);
      return *value;
    }

    double CurveDoubleExponentialDecay_Impl::maximumValueofx() const {
      const auto value = getDouble(openstudio::Curve_DoubleExponentialDecayFields::MaximumValueofx, true);
      OS_ASSERT(value);
      return *value;
    }

    boost::optional<double> CurveDoubleExponentialDecay_Impl::minimumCurveOutput() const {
      return getDouble(openstudio::Curve_DoubleExponentialDecayFields::MinimumCurveOutput, true);
    }

    boost::optional<double> CurveDoubleExponentialDecay_Impl::maximumCurveOutput() const {
      return getDouble(openstudio::Curve_DoubleExponentialDecayFields::MaximumCurveOutput, true);
    }

    std::string CurveDoubleExponentialDecay_Impl::inputUnitTypeforx() const {
      const auto value = getString(openstudio::Curve_DoubleExponentialDecayFields::InputUnitTypeforx, true);
      OS_ASSERT(value);
      return *value;
    }

    bool CurveDoubleExponentialDecay_Impl::isInputUnitTypeforxDefaulted() const {
      if (const auto value = getString(openstudio::Curve_DoubleExponentialDecayFields::InputUnitTypeforx, false, true)) {
        if (const auto defaultValue = curveDoubleExponentialDecayDefaultString(openstudio::Curve_DoubleExponentialDecayFields::InputUnitTypeforx)) {
          return openstudio::istringEqual(*value, *defaultValue);
        }
        return false;
      }
      return true;
    }

    std::string CurveDoubleExponentialDecay_Impl::outputUnitType() const {
      const auto value = getString(openstudio::Curve_DoubleExponentialDecayFields::OutputUnitType, true);
      OS_ASSERT(value);
      return *value;
    }

    bool CurveDoubleExponentialDecay_Impl::isOutputUnitTypeDefaulted() const {
      if (const auto value = getString(openstudio::Curve_DoubleExponentialDecayFields::OutputUnitType, false, true)) {
        if (const auto defaultValue = curveDoubleExponentialDecayDefaultString(openstudio::Curve_DoubleExponentialDecayFields::OutputUnitType)) {
          return openstudio::istringEqual(*value, *defaultValue);
        }
        return false;
      }
      return true;
    }

    bool CurveDoubleExponentialDecay_Impl::setCoefficient1C1(double coefficient1C1) {
      const bool result = setDouble(openstudio::Curve_DoubleExponentialDecayFields::Coefficient1C1, coefficient1C1);
      OS_ASSERT(result);
      return result;
    }

    bool CurveDoubleExponentialDecay_Impl::setCoefficient2C2(double coefficient2C2) {
      const bool result = setDouble(openstudio::Curve_DoubleExponentialDecayFields::Coefficient2C2, coefficient2C2);
      OS_ASSERT(result);
      return result;
    }

    bool CurveDoubleExponentialDecay_Impl::setCoefficient3C3(double coefficient3C3) {
      const bool result = setDouble(openstudio::Curve_DoubleExponentialDecayFields::Coefficient3C3, coefficient3C3);
      OS_ASSERT(result);
      return result;
    }

    bool CurveDoubleExponentialDecay_Impl::setCoefficient4C4(double coefficient4C4) {
      const bool result = setDouble(openstudio::Curve_DoubleExponentialDecayFields::Coefficient4C4, coefficient4C4);
      OS_ASSERT(result);
      return result;
    }

    bool CurveDoubleExponentialDecay_Impl::setCoefficient5C5(double coefficient5C5) {
      const bool result = setDouble(openstudio::Curve_DoubleExponentialDecayFields::Coefficient5C5, coefficient5C5);
      OS_ASSERT(result);
      return result;
    }

    bool CurveDoubleExponentialDecay_Impl::setMinimumValueofx(double minimumValueofx) {
      const bool result = setDouble(openstudio::Curve_DoubleExponentialDecayFields::MinimumValueofx, minimumValueofx);
      OS_ASSERT(result);
      return result;
    }

    bool CurveDoubleExponentialDecay_Impl::setMaximumValueofx(double maximumValueofx) {
      const bool result = setDouble(openstudio::Curve_DoubleExponentialDecayFields::MaximumValueofx, maximumValueofx);
      OS_ASSERT(result);
      return result;
    }

    bool CurveDoubleExponentialDecay_Impl::setMinimumCurveOutput(double minimumCurveOutput) {
      const bool result = setDouble(openstudio::Curve_DoubleExponentialDecayFields::MinimumCurveOutput, minimumCurveOutput);
      OS_ASSERT(result);
      return result;
    }

    void CurveDoubleExponentialDecay_Impl::resetMinimumCurveOutput() {
      OS_ASSERT(setString(openstudio::Curve_DoubleExponentialDecayFields::MinimumCurveOutput, ""));
    }

    bool CurveDoubleExponentialDecay_Impl::setMaximumCurveOutput(double maximumCurveOutput) {
      const bool result = setDouble(openstudio::Curve_DoubleExponentialDecayFields::MaximumCurveOutput, maximumCurveOutput);
      OS_ASSERT(result);
      return result;
    }

    void CurveDoubleExponentialDecay_Impl::resetMaximumCurveOutput() {
      OS_ASSERT(setString(openstudio::Curve_DoubleExponentialDecayFields::MaximumCurveOutput, ""));
    }

    bool CurveDoubleExponentialDecay_Impl::setInputUnitTypeforx(const std::string& inputUnitTypeforx) {
      return setString(openstudio::Curve_DoubleExponentialDecayFields::InputUnitTypeforx, inputUnitTypeforx);
    }

    void CurveDoubleExponentialDecay_Impl::resetInputUnitTypeforx() {
      bool result = false;
      if (const auto defaultValue = curveDoubleExponentialDecayDefaultString(openstudio::Curve_DoubleExponentialDecayFields::InputUnitTypeforx)) {
        result = setString(openstudio::Curve_DoubleExponentialDecayFields::InputUnitTypeforx, *defaultValue);
      } else {
        result = setString(openstudio::Curve_DoubleExponentialDecayFields::InputUnitTypeforx, "");
      }
      OS_ASSERT(result);
    }

    bool CurveDoubleExponentialDecay_Impl::setOutputUnitType(const std::string& outputUnitType) {
      return setString(openstudio::Curve_DoubleExponentialDecayFields::OutputUnitType, outputUnitType);
    }

    void CurveDoubleExponentialDecay_Impl::resetOutputUnitType() {
      bool result = false;
      if (const auto defaultValue = curveDoubleExponentialDecayDefaultString(openstudio::Curve_DoubleExponentialDecayFields::OutputUnitType)) {
        result = setString(openstudio::Curve_DoubleExponentialDecayFields::OutputUnitType, *defaultValue);
      } else {
        result = setString(openstudio::Curve_DoubleExponentialDecayFields::OutputUnitType, "");
      }
      OS_ASSERT(result);
    }

    std::vector<std::string> CurveDoubleExponentialDecay_Impl::validInputUnitTypeforxValues() const {
      return openstudio::epmodel::CurveDoubleExponentialDecay::validInputUnitTypeforxValues();
    }

    std::vector<std::string> CurveDoubleExponentialDecay_Impl::validOutputUnitTypeValues() const {
      return openstudio::epmodel::CurveDoubleExponentialDecay::validOutputUnitTypeValues();
    }

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
