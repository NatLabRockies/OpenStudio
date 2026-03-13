/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "Curve/CurveLinear.hpp"
#include "Curve/CurveLinear_Impl.hpp"

#include "Model.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/idd/Curve_Linear_FieldEnums.hxx>
#include <utilities/idd/IddEnums.hxx>
#include <utilities/idd/IddFactory.hxx>

namespace openstudio {
namespace epmodel {

  CurveLinear::CurveLinear(const Model& model) : Curve(CurveLinear::iddObjectType(), model) {
    OS_ASSERT(getImpl<detail::CurveLinear_Impl>());
    OS_ASSERT(setCoefficient1Constant(0.0));
    OS_ASSERT(setCoefficient2x(1.0));
    OS_ASSERT(setMinimumValueofx(0.0));
    OS_ASSERT(setMaximumValueofx(1.0));
    resetMinimumCurveOutput();
    resetMaximumCurveOutput();
    resetInputUnitTypeforX();
    resetOutputUnitType();
  }

  CurveLinear::CurveLinear(std::shared_ptr<detail::CurveLinear_Impl> impl) : Curve(std::move(impl)) {}

  IddObjectType CurveLinear::iddObjectType() {
    return IddObjectType::Curve_Linear;
  }

  std::vector<std::string> CurveLinear::validInputUnitTypeforXValues() {
    return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(), openstudio::Curve_LinearFields::InputUnitTypeforX);
  }

  std::vector<std::string> CurveLinear::validOutputUnitTypeValues() {
    return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(), openstudio::Curve_LinearFields::OutputUnitType);
  }

  double CurveLinear::coefficient1Constant() const {
    return getImpl<detail::CurveLinear_Impl>()->coefficient1Constant();
  }

  bool CurveLinear::setCoefficient1Constant(double coefficient1Constant) {
    return getImpl<detail::CurveLinear_Impl>()->setCoefficient1Constant(coefficient1Constant);
  }

  double CurveLinear::coefficient2x() const {
    return getImpl<detail::CurveLinear_Impl>()->coefficient2x();
  }

  bool CurveLinear::setCoefficient2x(double coefficient2x) {
    return getImpl<detail::CurveLinear_Impl>()->setCoefficient2x(coefficient2x);
  }

  double CurveLinear::minimumValueofx() const {
    return getImpl<detail::CurveLinear_Impl>()->minimumValueofx();
  }

  bool CurveLinear::setMinimumValueofx(double minimumValueofx) {
    return getImpl<detail::CurveLinear_Impl>()->setMinimumValueofx(minimumValueofx);
  }

  double CurveLinear::maximumValueofx() const {
    return getImpl<detail::CurveLinear_Impl>()->maximumValueofx();
  }

  bool CurveLinear::setMaximumValueofx(double maximumValueofx) {
    return getImpl<detail::CurveLinear_Impl>()->setMaximumValueofx(maximumValueofx);
  }

  boost::optional<double> CurveLinear::minimumCurveOutput() const {
    return getImpl<detail::CurveLinear_Impl>()->minimumCurveOutput();
  }

  bool CurveLinear::setMinimumCurveOutput(double minimumCurveOutput) {
    return getImpl<detail::CurveLinear_Impl>()->setMinimumCurveOutput(minimumCurveOutput);
  }

  void CurveLinear::resetMinimumCurveOutput() {
    getImpl<detail::CurveLinear_Impl>()->resetMinimumCurveOutput();
  }

  boost::optional<double> CurveLinear::maximumCurveOutput() const {
    return getImpl<detail::CurveLinear_Impl>()->maximumCurveOutput();
  }

  bool CurveLinear::setMaximumCurveOutput(double maximumCurveOutput) {
    return getImpl<detail::CurveLinear_Impl>()->setMaximumCurveOutput(maximumCurveOutput);
  }

  void CurveLinear::resetMaximumCurveOutput() {
    getImpl<detail::CurveLinear_Impl>()->resetMaximumCurveOutput();
  }

  std::string CurveLinear::inputUnitTypeforX() const {
    return getImpl<detail::CurveLinear_Impl>()->inputUnitTypeforX();
  }

  bool CurveLinear::setInputUnitTypeforX(const std::string& inputUnitTypeforX) {
    return getImpl<detail::CurveLinear_Impl>()->setInputUnitTypeforX(inputUnitTypeforX);
  }

  void CurveLinear::resetInputUnitTypeforX() {
    getImpl<detail::CurveLinear_Impl>()->resetInputUnitTypeforX();
  }

  bool CurveLinear::isInputUnitTypeforXDefaulted() const {
    return getImpl<detail::CurveLinear_Impl>()->isInputUnitTypeforXDefaulted();
  }

  std::string CurveLinear::outputUnitType() const {
    return getImpl<detail::CurveLinear_Impl>()->outputUnitType();
  }

  bool CurveLinear::setOutputUnitType(const std::string& outputUnitType) {
    return getImpl<detail::CurveLinear_Impl>()->setOutputUnitType(outputUnitType);
  }

  void CurveLinear::resetOutputUnitType() {
    getImpl<detail::CurveLinear_Impl>()->resetOutputUnitType();
  }

  bool CurveLinear::isOutputUnitTypeDefaulted() const {
    return getImpl<detail::CurveLinear_Impl>()->isOutputUnitTypeDefaulted();
  }

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
  namespace detail {

    double CurveLinear_Impl::coefficient1Constant() const {
      const auto value = getDouble(openstudio::Curve_LinearFields::Coefficient1Constant, true);
      OS_ASSERT(value);
      return *value;
    }

    bool CurveLinear_Impl::setCoefficient1Constant(double coefficient1Constant) {
      const bool result = setDouble(openstudio::Curve_LinearFields::Coefficient1Constant, coefficient1Constant);
      OS_ASSERT(result);
      return result;
    }

    double CurveLinear_Impl::coefficient2x() const {
      const auto value = getDouble(openstudio::Curve_LinearFields::Coefficient2x, true);
      OS_ASSERT(value);
      return *value;
    }

    bool CurveLinear_Impl::setCoefficient2x(double coefficient2x) {
      const bool result = setDouble(openstudio::Curve_LinearFields::Coefficient2x, coefficient2x);
      OS_ASSERT(result);
      return result;
    }

    double CurveLinear_Impl::minimumValueofx() const {
      const auto value = getDouble(openstudio::Curve_LinearFields::MinimumValueofx, true);
      OS_ASSERT(value);
      return *value;
    }

    bool CurveLinear_Impl::setMinimumValueofx(double minimumValueofx) {
      const bool result = setDouble(openstudio::Curve_LinearFields::MinimumValueofx, minimumValueofx);
      OS_ASSERT(result);
      return result;
    }

    double CurveLinear_Impl::maximumValueofx() const {
      const auto value = getDouble(openstudio::Curve_LinearFields::MaximumValueofx, true);
      OS_ASSERT(value);
      return *value;
    }

    bool CurveLinear_Impl::setMaximumValueofx(double maximumValueofx) {
      const bool result = setDouble(openstudio::Curve_LinearFields::MaximumValueofx, maximumValueofx);
      OS_ASSERT(result);
      return result;
    }

    boost::optional<double> CurveLinear_Impl::minimumCurveOutput() const {
      return getDouble(openstudio::Curve_LinearFields::MinimumCurveOutput, true);
    }

    bool CurveLinear_Impl::setMinimumCurveOutput(double minimumCurveOutput) {
      const bool result = setDouble(openstudio::Curve_LinearFields::MinimumCurveOutput, minimumCurveOutput);
      OS_ASSERT(result);
      return result;
    }

    void CurveLinear_Impl::resetMinimumCurveOutput() {
      OS_ASSERT(setString(openstudio::Curve_LinearFields::MinimumCurveOutput, ""));
    }

    boost::optional<double> CurveLinear_Impl::maximumCurveOutput() const {
      return getDouble(openstudio::Curve_LinearFields::MaximumCurveOutput, true);
    }

    bool CurveLinear_Impl::setMaximumCurveOutput(double maximumCurveOutput) {
      const bool result = setDouble(openstudio::Curve_LinearFields::MaximumCurveOutput, maximumCurveOutput);
      OS_ASSERT(result);
      return result;
    }

    void CurveLinear_Impl::resetMaximumCurveOutput() {
      OS_ASSERT(setString(openstudio::Curve_LinearFields::MaximumCurveOutput, ""));
    }

    std::string CurveLinear_Impl::inputUnitTypeforX() const {
      const auto value = getString(openstudio::Curve_LinearFields::InputUnitTypeforX, true);
      OS_ASSERT(value);
      return *value;
    }

    bool CurveLinear_Impl::setInputUnitTypeforX(const std::string& inputUnitTypeforX) {
      return setString(openstudio::Curve_LinearFields::InputUnitTypeforX, inputUnitTypeforX);
    }

    void CurveLinear_Impl::resetInputUnitTypeforX() {
      OS_ASSERT(setString(openstudio::Curve_LinearFields::InputUnitTypeforX, ""));
    }

    bool CurveLinear_Impl::isInputUnitTypeforXDefaulted() const {
      return isEmpty(openstudio::Curve_LinearFields::InputUnitTypeforX);
    }

    std::string CurveLinear_Impl::outputUnitType() const {
      const auto value = getString(openstudio::Curve_LinearFields::OutputUnitType, true);
      OS_ASSERT(value);
      return *value;
    }

    bool CurveLinear_Impl::setOutputUnitType(const std::string& outputUnitType) {
      return setString(openstudio::Curve_LinearFields::OutputUnitType, outputUnitType);
    }

    void CurveLinear_Impl::resetOutputUnitType() {
      OS_ASSERT(setString(openstudio::Curve_LinearFields::OutputUnitType, ""));
    }

    bool CurveLinear_Impl::isOutputUnitTypeDefaulted() const {
      return isEmpty(openstudio::Curve_LinearFields::OutputUnitType);
    }

    std::vector<std::string> CurveLinear_Impl::validInputUnitTypeforXValues() const {
      return openstudio::epmodel::CurveLinear::validInputUnitTypeforXValues();
    }

    std::vector<std::string> CurveLinear_Impl::validOutputUnitTypeValues() const {
      return openstudio::epmodel::CurveLinear::validOutputUnitTypeValues();
    }

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
