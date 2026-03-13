/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "Curve/CurveQuadratic.hpp"
#include "Curve/CurveQuadratic_Impl.hpp"

#include "Model.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/idd/Curve_Quadratic_FieldEnums.hxx>
#include <utilities/idd/IddEnums.hxx>
#include <utilities/idd/IddFactory.hxx>

namespace openstudio {
namespace epmodel {

  CurveQuadratic::CurveQuadratic(const Model& model) : ModelObject(CurveQuadratic::iddObjectType(), model) {
    OS_ASSERT(getImpl<detail::CurveQuadratic_Impl>());
    OS_ASSERT(setCoefficient1Constant(0.0));
    OS_ASSERT(setCoefficient2x(0.0));
    OS_ASSERT(setCoefficient3xPOW2(1.0));
    OS_ASSERT(setMinimumValueofx(0.0));
    OS_ASSERT(setMaximumValueofx(1.0));
    resetMinimumCurveOutput();
    resetMaximumCurveOutput();
    resetInputUnitTypeforX();
    resetOutputUnitType();
  }

  CurveQuadratic::CurveQuadratic(std::shared_ptr<detail::CurveQuadratic_Impl> impl) : ModelObject(std::move(impl)) {}

  IddObjectType CurveQuadratic::iddObjectType() {
    return IddObjectType::Curve_Quadratic;
  }

  std::vector<std::string> CurveQuadratic::validInputUnitTypeforXValues() {
    return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(), openstudio::Curve_QuadraticFields::InputUnitTypeforX);
  }

  std::vector<std::string> CurveQuadratic::validOutputUnitTypeValues() {
    return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(), openstudio::Curve_QuadraticFields::OutputUnitType);
  }

  double CurveQuadratic::coefficient1Constant() const {
    return getImpl<detail::CurveQuadratic_Impl>()->coefficient1Constant();
  }

  bool CurveQuadratic::setCoefficient1Constant(double coefficient1Constant) {
    return getImpl<detail::CurveQuadratic_Impl>()->setCoefficient1Constant(coefficient1Constant);
  }

  double CurveQuadratic::coefficient2x() const {
    return getImpl<detail::CurveQuadratic_Impl>()->coefficient2x();
  }

  bool CurveQuadratic::setCoefficient2x(double coefficient2x) {
    return getImpl<detail::CurveQuadratic_Impl>()->setCoefficient2x(coefficient2x);
  }

  double CurveQuadratic::coefficient3xPOW2() const {
    return getImpl<detail::CurveQuadratic_Impl>()->coefficient3xPOW2();
  }

  bool CurveQuadratic::setCoefficient3xPOW2(double coefficient3xPOW2) {
    return getImpl<detail::CurveQuadratic_Impl>()->setCoefficient3xPOW2(coefficient3xPOW2);
  }

  double CurveQuadratic::minimumValueofx() const {
    return getImpl<detail::CurveQuadratic_Impl>()->minimumValueofx();
  }

  bool CurveQuadratic::setMinimumValueofx(double minimumValueofx) {
    return getImpl<detail::CurveQuadratic_Impl>()->setMinimumValueofx(minimumValueofx);
  }

  double CurveQuadratic::maximumValueofx() const {
    return getImpl<detail::CurveQuadratic_Impl>()->maximumValueofx();
  }

  bool CurveQuadratic::setMaximumValueofx(double maximumValueofx) {
    return getImpl<detail::CurveQuadratic_Impl>()->setMaximumValueofx(maximumValueofx);
  }

  boost::optional<double> CurveQuadratic::minimumCurveOutput() const {
    return getImpl<detail::CurveQuadratic_Impl>()->minimumCurveOutput();
  }

  bool CurveQuadratic::setMinimumCurveOutput(double minimumCurveOutput) {
    return getImpl<detail::CurveQuadratic_Impl>()->setMinimumCurveOutput(minimumCurveOutput);
  }

  void CurveQuadratic::resetMinimumCurveOutput() {
    getImpl<detail::CurveQuadratic_Impl>()->resetMinimumCurveOutput();
  }

  boost::optional<double> CurveQuadratic::maximumCurveOutput() const {
    return getImpl<detail::CurveQuadratic_Impl>()->maximumCurveOutput();
  }

  bool CurveQuadratic::setMaximumCurveOutput(double maximumCurveOutput) {
    return getImpl<detail::CurveQuadratic_Impl>()->setMaximumCurveOutput(maximumCurveOutput);
  }

  void CurveQuadratic::resetMaximumCurveOutput() {
    getImpl<detail::CurveQuadratic_Impl>()->resetMaximumCurveOutput();
  }

  std::string CurveQuadratic::inputUnitTypeforX() const {
    return getImpl<detail::CurveQuadratic_Impl>()->inputUnitTypeforX();
  }

  bool CurveQuadratic::isInputUnitTypeforXDefaulted() const {
    return getImpl<detail::CurveQuadratic_Impl>()->isInputUnitTypeforXDefaulted();
  }

  bool CurveQuadratic::setInputUnitTypeforX(const std::string& inputUnitTypeforX) {
    return getImpl<detail::CurveQuadratic_Impl>()->setInputUnitTypeforX(inputUnitTypeforX);
  }

  void CurveQuadratic::resetInputUnitTypeforX() {
    getImpl<detail::CurveQuadratic_Impl>()->resetInputUnitTypeforX();
  }

  std::string CurveQuadratic::outputUnitType() const {
    return getImpl<detail::CurveQuadratic_Impl>()->outputUnitType();
  }

  bool CurveQuadratic::isOutputUnitTypeDefaulted() const {
    return getImpl<detail::CurveQuadratic_Impl>()->isOutputUnitTypeDefaulted();
  }

  bool CurveQuadratic::setOutputUnitType(const std::string& outputUnitType) {
    return getImpl<detail::CurveQuadratic_Impl>()->setOutputUnitType(outputUnitType);
  }

  void CurveQuadratic::resetOutputUnitType() {
    getImpl<detail::CurveQuadratic_Impl>()->resetOutputUnitType();
  }

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
  namespace detail {

    double CurveQuadratic_Impl::coefficient1Constant() const {
      const auto value = getDouble(openstudio::Curve_QuadraticFields::Coefficient1Constant, true);
      OS_ASSERT(value);
      return *value;
    }

    bool CurveQuadratic_Impl::setCoefficient1Constant(double coefficient1Constant) {
      const bool result = setDouble(openstudio::Curve_QuadraticFields::Coefficient1Constant, coefficient1Constant);
      OS_ASSERT(result);
      return result;
    }

    double CurveQuadratic_Impl::coefficient2x() const {
      const auto value = getDouble(openstudio::Curve_QuadraticFields::Coefficient2x, true);
      OS_ASSERT(value);
      return *value;
    }

    bool CurveQuadratic_Impl::setCoefficient2x(double coefficient2x) {
      const bool result = setDouble(openstudio::Curve_QuadraticFields::Coefficient2x, coefficient2x);
      OS_ASSERT(result);
      return result;
    }

    double CurveQuadratic_Impl::coefficient3xPOW2() const {
      const auto value = getDouble(openstudio::Curve_QuadraticFields::Coefficient3x_POW_2, true);
      OS_ASSERT(value);
      return *value;
    }

    bool CurveQuadratic_Impl::setCoefficient3xPOW2(double coefficient3xPOW2) {
      const bool result = setDouble(openstudio::Curve_QuadraticFields::Coefficient3x_POW_2, coefficient3xPOW2);
      OS_ASSERT(result);
      return result;
    }

    double CurveQuadratic_Impl::minimumValueofx() const {
      const auto value = getDouble(openstudio::Curve_QuadraticFields::MinimumValueofx, true);
      OS_ASSERT(value);
      return *value;
    }

    bool CurveQuadratic_Impl::setMinimumValueofx(double minimumValueofx) {
      const bool result = setDouble(openstudio::Curve_QuadraticFields::MinimumValueofx, minimumValueofx);
      OS_ASSERT(result);
      return result;
    }

    double CurveQuadratic_Impl::maximumValueofx() const {
      const auto value = getDouble(openstudio::Curve_QuadraticFields::MaximumValueofx, true);
      OS_ASSERT(value);
      return *value;
    }

    bool CurveQuadratic_Impl::setMaximumValueofx(double maximumValueofx) {
      const bool result = setDouble(openstudio::Curve_QuadraticFields::MaximumValueofx, maximumValueofx);
      OS_ASSERT(result);
      return result;
    }

    boost::optional<double> CurveQuadratic_Impl::minimumCurveOutput() const {
      return getDouble(openstudio::Curve_QuadraticFields::MinimumCurveOutput, true);
    }

    bool CurveQuadratic_Impl::setMinimumCurveOutput(double minimumCurveOutput) {
      const bool result = setDouble(openstudio::Curve_QuadraticFields::MinimumCurveOutput, minimumCurveOutput);
      OS_ASSERT(result);
      return result;
    }

    void CurveQuadratic_Impl::resetMinimumCurveOutput() {
      OS_ASSERT(setString(openstudio::Curve_QuadraticFields::MinimumCurveOutput, ""));
    }

    boost::optional<double> CurveQuadratic_Impl::maximumCurveOutput() const {
      return getDouble(openstudio::Curve_QuadraticFields::MaximumCurveOutput, true);
    }

    bool CurveQuadratic_Impl::setMaximumCurveOutput(double maximumCurveOutput) {
      const bool result = setDouble(openstudio::Curve_QuadraticFields::MaximumCurveOutput, maximumCurveOutput);
      OS_ASSERT(result);
      return result;
    }

    void CurveQuadratic_Impl::resetMaximumCurveOutput() {
      OS_ASSERT(setString(openstudio::Curve_QuadraticFields::MaximumCurveOutput, ""));
    }

    std::string CurveQuadratic_Impl::inputUnitTypeforX() const {
      const auto value = getString(openstudio::Curve_QuadraticFields::InputUnitTypeforX, true);
      OS_ASSERT(value);
      return *value;
    }

    bool CurveQuadratic_Impl::isInputUnitTypeforXDefaulted() const {
      return isEmpty(openstudio::Curve_QuadraticFields::InputUnitTypeforX);
    }

    bool CurveQuadratic_Impl::setInputUnitTypeforX(const std::string& inputUnitTypeforX) {
      return setString(openstudio::Curve_QuadraticFields::InputUnitTypeforX, inputUnitTypeforX);
    }

    void CurveQuadratic_Impl::resetInputUnitTypeforX() {
      OS_ASSERT(setString(openstudio::Curve_QuadraticFields::InputUnitTypeforX, ""));
    }

    std::string CurveQuadratic_Impl::outputUnitType() const {
      const auto value = getString(openstudio::Curve_QuadraticFields::OutputUnitType, true);
      OS_ASSERT(value);
      return *value;
    }

    bool CurveQuadratic_Impl::isOutputUnitTypeDefaulted() const {
      return isEmpty(openstudio::Curve_QuadraticFields::OutputUnitType);
    }

    bool CurveQuadratic_Impl::setOutputUnitType(const std::string& outputUnitType) {
      return setString(openstudio::Curve_QuadraticFields::OutputUnitType, outputUnitType);
    }

    void CurveQuadratic_Impl::resetOutputUnitType() {
      OS_ASSERT(setString(openstudio::Curve_QuadraticFields::OutputUnitType, ""));
    }

    std::vector<std::string> CurveQuadratic_Impl::validInputUnitTypeforXValues() const {
      return openstudio::epmodel::CurveQuadratic::validInputUnitTypeforXValues();
    }

    std::vector<std::string> CurveQuadratic_Impl::validOutputUnitTypeValues() const {
      return openstudio::epmodel::CurveQuadratic::validOutputUnitTypeValues();
    }

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
