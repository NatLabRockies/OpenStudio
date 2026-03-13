/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "Curve/CurveExponent.hpp"
#include "Curve/CurveExponent_Impl.hpp"

#include "Model.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/idd/Curve_Exponent_FieldEnums.hxx>
#include <utilities/idd/IddEnums.hxx>
#include <utilities/idd/IddFactory.hxx>

namespace openstudio {
namespace epmodel {

  CurveExponent::CurveExponent(const Model& model) : ModelObject(CurveExponent::iddObjectType(), model) {
    OS_ASSERT(getImpl<detail::CurveExponent_Impl>());
    OS_ASSERT(setCoefficient1Constant(0.0));
    OS_ASSERT(setCoefficient2Constant(1.0));
    OS_ASSERT(setCoefficient3Constant(1.0));
    OS_ASSERT(setMinimumValueofx(0.0));
    OS_ASSERT(setMaximumValueofx(1.0));
    resetMinimumCurveOutput();
    resetMaximumCurveOutput();
    resetInputUnitTypeforX();
    resetOutputUnitType();
  }

  CurveExponent::CurveExponent(std::shared_ptr<detail::CurveExponent_Impl> impl) : ModelObject(std::move(impl)) {}

  IddObjectType CurveExponent::iddObjectType() {
    return IddObjectType::Curve_Exponent;
  }

  std::vector<std::string> CurveExponent::validInputUnitTypeforXValues() {
    return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(), openstudio::Curve_ExponentFields::InputUnitTypeforX);
  }

  std::vector<std::string> CurveExponent::validOutputUnitTypeValues() {
    return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(), openstudio::Curve_ExponentFields::OutputUnitType);
  }

  double CurveExponent::coefficient1Constant() const {
    return getImpl<detail::CurveExponent_Impl>()->coefficient1Constant();
  }

  bool CurveExponent::setCoefficient1Constant(double coefficient1Constant) {
    return getImpl<detail::CurveExponent_Impl>()->setCoefficient1Constant(coefficient1Constant);
  }

  double CurveExponent::coefficient2Constant() const {
    return getImpl<detail::CurveExponent_Impl>()->coefficient2Constant();
  }

  bool CurveExponent::setCoefficient2Constant(double coefficient2Constant) {
    return getImpl<detail::CurveExponent_Impl>()->setCoefficient2Constant(coefficient2Constant);
  }

  double CurveExponent::coefficient3Constant() const {
    return getImpl<detail::CurveExponent_Impl>()->coefficient3Constant();
  }

  bool CurveExponent::setCoefficient3Constant(double coefficient3Constant) {
    return getImpl<detail::CurveExponent_Impl>()->setCoefficient3Constant(coefficient3Constant);
  }

  double CurveExponent::minimumValueofx() const {
    return getImpl<detail::CurveExponent_Impl>()->minimumValueofx();
  }

  bool CurveExponent::setMinimumValueofx(double minimumValueofx) {
    return getImpl<detail::CurveExponent_Impl>()->setMinimumValueofx(minimumValueofx);
  }

  double CurveExponent::maximumValueofx() const {
    return getImpl<detail::CurveExponent_Impl>()->maximumValueofx();
  }

  bool CurveExponent::setMaximumValueofx(double maximumValueofx) {
    return getImpl<detail::CurveExponent_Impl>()->setMaximumValueofx(maximumValueofx);
  }

  boost::optional<double> CurveExponent::minimumCurveOutput() const {
    return getImpl<detail::CurveExponent_Impl>()->minimumCurveOutput();
  }

  bool CurveExponent::setMinimumCurveOutput(double minimumCurveOutput) {
    return getImpl<detail::CurveExponent_Impl>()->setMinimumCurveOutput(minimumCurveOutput);
  }

  void CurveExponent::resetMinimumCurveOutput() {
    getImpl<detail::CurveExponent_Impl>()->resetMinimumCurveOutput();
  }

  boost::optional<double> CurveExponent::maximumCurveOutput() const {
    return getImpl<detail::CurveExponent_Impl>()->maximumCurveOutput();
  }

  bool CurveExponent::setMaximumCurveOutput(double maximumCurveOutput) {
    return getImpl<detail::CurveExponent_Impl>()->setMaximumCurveOutput(maximumCurveOutput);
  }

  void CurveExponent::resetMaximumCurveOutput() {
    getImpl<detail::CurveExponent_Impl>()->resetMaximumCurveOutput();
  }

  std::string CurveExponent::inputUnitTypeforX() const {
    return getImpl<detail::CurveExponent_Impl>()->inputUnitTypeforX();
  }

  bool CurveExponent::isInputUnitTypeforXDefaulted() const {
    return getImpl<detail::CurveExponent_Impl>()->isInputUnitTypeforXDefaulted();
  }

  bool CurveExponent::setInputUnitTypeforX(const std::string& inputUnitTypeforX) {
    return getImpl<detail::CurveExponent_Impl>()->setInputUnitTypeforX(inputUnitTypeforX);
  }

  void CurveExponent::resetInputUnitTypeforX() {
    getImpl<detail::CurveExponent_Impl>()->resetInputUnitTypeforX();
  }

  std::string CurveExponent::outputUnitType() const {
    return getImpl<detail::CurveExponent_Impl>()->outputUnitType();
  }

  bool CurveExponent::isOutputUnitTypeDefaulted() const {
    return getImpl<detail::CurveExponent_Impl>()->isOutputUnitTypeDefaulted();
  }

  bool CurveExponent::setOutputUnitType(const std::string& outputUnitType) {
    return getImpl<detail::CurveExponent_Impl>()->setOutputUnitType(outputUnitType);
  }

  void CurveExponent::resetOutputUnitType() {
    getImpl<detail::CurveExponent_Impl>()->resetOutputUnitType();
  }

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
  namespace detail {

    double CurveExponent_Impl::coefficient1Constant() const {
      const auto value = getDouble(openstudio::Curve_ExponentFields::Coefficient1Constant, true);
      OS_ASSERT(value);
      return *value;
    }

    bool CurveExponent_Impl::setCoefficient1Constant(double coefficient1Constant) {
      const bool result = setDouble(openstudio::Curve_ExponentFields::Coefficient1Constant, coefficient1Constant);
      OS_ASSERT(result);
      return result;
    }

    double CurveExponent_Impl::coefficient2Constant() const {
      const auto value = getDouble(openstudio::Curve_ExponentFields::Coefficient2Constant, true);
      OS_ASSERT(value);
      return *value;
    }

    bool CurveExponent_Impl::setCoefficient2Constant(double coefficient2Constant) {
      const bool result = setDouble(openstudio::Curve_ExponentFields::Coefficient2Constant, coefficient2Constant);
      OS_ASSERT(result);
      return result;
    }

    double CurveExponent_Impl::coefficient3Constant() const {
      const auto value = getDouble(openstudio::Curve_ExponentFields::Coefficient3Constant, true);
      OS_ASSERT(value);
      return *value;
    }

    bool CurveExponent_Impl::setCoefficient3Constant(double coefficient3Constant) {
      const bool result = setDouble(openstudio::Curve_ExponentFields::Coefficient3Constant, coefficient3Constant);
      OS_ASSERT(result);
      return result;
    }

    double CurveExponent_Impl::minimumValueofx() const {
      const auto value = getDouble(openstudio::Curve_ExponentFields::MinimumValueofx, true);
      OS_ASSERT(value);
      return *value;
    }

    bool CurveExponent_Impl::setMinimumValueofx(double minimumValueofx) {
      const bool result = setDouble(openstudio::Curve_ExponentFields::MinimumValueofx, minimumValueofx);
      OS_ASSERT(result);
      return result;
    }

    double CurveExponent_Impl::maximumValueofx() const {
      const auto value = getDouble(openstudio::Curve_ExponentFields::MaximumValueofx, true);
      OS_ASSERT(value);
      return *value;
    }

    bool CurveExponent_Impl::setMaximumValueofx(double maximumValueofx) {
      const bool result = setDouble(openstudio::Curve_ExponentFields::MaximumValueofx, maximumValueofx);
      OS_ASSERT(result);
      return result;
    }

    boost::optional<double> CurveExponent_Impl::minimumCurveOutput() const {
      return getDouble(openstudio::Curve_ExponentFields::MinimumCurveOutput, true);
    }

    bool CurveExponent_Impl::setMinimumCurveOutput(double minimumCurveOutput) {
      const bool result = setDouble(openstudio::Curve_ExponentFields::MinimumCurveOutput, minimumCurveOutput);
      OS_ASSERT(result);
      return result;
    }

    void CurveExponent_Impl::resetMinimumCurveOutput() {
      OS_ASSERT(setString(openstudio::Curve_ExponentFields::MinimumCurveOutput, ""));
    }

    boost::optional<double> CurveExponent_Impl::maximumCurveOutput() const {
      return getDouble(openstudio::Curve_ExponentFields::MaximumCurveOutput, true);
    }

    bool CurveExponent_Impl::setMaximumCurveOutput(double maximumCurveOutput) {
      const bool result = setDouble(openstudio::Curve_ExponentFields::MaximumCurveOutput, maximumCurveOutput);
      OS_ASSERT(result);
      return result;
    }

    void CurveExponent_Impl::resetMaximumCurveOutput() {
      OS_ASSERT(setString(openstudio::Curve_ExponentFields::MaximumCurveOutput, ""));
    }

    std::string CurveExponent_Impl::inputUnitTypeforX() const {
      const auto value = getString(openstudio::Curve_ExponentFields::InputUnitTypeforX, true);
      OS_ASSERT(value);
      return *value;
    }

    bool CurveExponent_Impl::isInputUnitTypeforXDefaulted() const {
      return isEmpty(openstudio::Curve_ExponentFields::InputUnitTypeforX);
    }

    bool CurveExponent_Impl::setInputUnitTypeforX(const std::string& inputUnitTypeforX) {
      return setString(openstudio::Curve_ExponentFields::InputUnitTypeforX, inputUnitTypeforX);
    }

    void CurveExponent_Impl::resetInputUnitTypeforX() {
      OS_ASSERT(setString(openstudio::Curve_ExponentFields::InputUnitTypeforX, ""));
    }

    std::string CurveExponent_Impl::outputUnitType() const {
      const auto value = getString(openstudio::Curve_ExponentFields::OutputUnitType, true);
      OS_ASSERT(value);
      return *value;
    }

    bool CurveExponent_Impl::isOutputUnitTypeDefaulted() const {
      return isEmpty(openstudio::Curve_ExponentFields::OutputUnitType);
    }

    bool CurveExponent_Impl::setOutputUnitType(const std::string& outputUnitType) {
      return setString(openstudio::Curve_ExponentFields::OutputUnitType, outputUnitType);
    }

    void CurveExponent_Impl::resetOutputUnitType() {
      OS_ASSERT(setString(openstudio::Curve_ExponentFields::OutputUnitType, ""));
    }

    std::vector<std::string> CurveExponent_Impl::validInputUnitTypeforXValues() const {
      return openstudio::epmodel::CurveExponent::validInputUnitTypeforXValues();
    }

    std::vector<std::string> CurveExponent_Impl::validOutputUnitTypeValues() const {
      return openstudio::epmodel::CurveExponent::validOutputUnitTypeValues();
    }

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
