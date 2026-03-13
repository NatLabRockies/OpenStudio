/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "Curve/CurveQuartic.hpp"
#include "Curve/CurveQuartic_Impl.hpp"

#include "Model.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/idd/Curve_Quartic_FieldEnums.hxx>
#include <utilities/idd/IddEnums.hxx>
#include <utilities/idd/IddFactory.hxx>

namespace openstudio {
namespace epmodel {

  CurveQuartic::CurveQuartic(const Model& model) : ModelObject(CurveQuartic::iddObjectType(), model) {
    OS_ASSERT(getImpl<detail::CurveQuartic_Impl>());
    OS_ASSERT(setCoefficient1Constant(0.0));
    OS_ASSERT(setCoefficient2x(0.0));
    OS_ASSERT(setCoefficient3xPOW2(0.0));
    OS_ASSERT(setCoefficient4xPOW3(0.0));
    OS_ASSERT(setCoefficient5xPOW4(1.0));
    OS_ASSERT(setMinimumValueofx(0.0));
    OS_ASSERT(setMaximumValueofx(1.0));
  }

  CurveQuartic::CurveQuartic(std::shared_ptr<detail::CurveQuartic_Impl> impl) : ModelObject(std::move(impl)) {}

  IddObjectType CurveQuartic::iddObjectType() {
    return IddObjectType::Curve_Quartic;
  }

  std::vector<std::string> CurveQuartic::validInputUnitTypeforXValues() {
    return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(), openstudio::Curve_QuarticFields::InputUnitTypeforX);
  }

  std::vector<std::string> CurveQuartic::validOutputUnitTypeValues() {
    return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(), openstudio::Curve_QuarticFields::OutputUnitType);
  }

  double CurveQuartic::coefficient1Constant() const {
    return getImpl<detail::CurveQuartic_Impl>()->coefficient1Constant();
  }

  bool CurveQuartic::setCoefficient1Constant(double coefficient1Constant) {
    return getImpl<detail::CurveQuartic_Impl>()->setCoefficient1Constant(coefficient1Constant);
  }

  double CurveQuartic::coefficient2x() const {
    return getImpl<detail::CurveQuartic_Impl>()->coefficient2x();
  }

  bool CurveQuartic::setCoefficient2x(double coefficient2x) {
    return getImpl<detail::CurveQuartic_Impl>()->setCoefficient2x(coefficient2x);
  }

  double CurveQuartic::coefficient3xPOW2() const {
    return getImpl<detail::CurveQuartic_Impl>()->coefficient3xPOW2();
  }

  bool CurveQuartic::setCoefficient3xPOW2(double coefficient3xPOW2) {
    return getImpl<detail::CurveQuartic_Impl>()->setCoefficient3xPOW2(coefficient3xPOW2);
  }

  double CurveQuartic::coefficient4xPOW3() const {
    return getImpl<detail::CurveQuartic_Impl>()->coefficient4xPOW3();
  }

  bool CurveQuartic::setCoefficient4xPOW3(double coefficient4xPOW3) {
    return getImpl<detail::CurveQuartic_Impl>()->setCoefficient4xPOW3(coefficient4xPOW3);
  }

  double CurveQuartic::coefficient5xPOW4() const {
    return getImpl<detail::CurveQuartic_Impl>()->coefficient5xPOW4();
  }

  bool CurveQuartic::setCoefficient5xPOW4(double coefficient5xPOW4) {
    return getImpl<detail::CurveQuartic_Impl>()->setCoefficient5xPOW4(coefficient5xPOW4);
  }

  double CurveQuartic::minimumValueofx() const {
    return getImpl<detail::CurveQuartic_Impl>()->minimumValueofx();
  }

  bool CurveQuartic::setMinimumValueofx(double minimumValueofx) {
    return getImpl<detail::CurveQuartic_Impl>()->setMinimumValueofx(minimumValueofx);
  }

  double CurveQuartic::maximumValueofx() const {
    return getImpl<detail::CurveQuartic_Impl>()->maximumValueofx();
  }

  bool CurveQuartic::setMaximumValueofx(double maximumValueofx) {
    return getImpl<detail::CurveQuartic_Impl>()->setMaximumValueofx(maximumValueofx);
  }

  boost::optional<double> CurveQuartic::minimumCurveOutput() const {
    return getImpl<detail::CurveQuartic_Impl>()->minimumCurveOutput();
  }

  bool CurveQuartic::setMinimumCurveOutput(double minimumCurveOutput) {
    return getImpl<detail::CurveQuartic_Impl>()->setMinimumCurveOutput(minimumCurveOutput);
  }

  void CurveQuartic::resetMinimumCurveOutput() {
    getImpl<detail::CurveQuartic_Impl>()->resetMinimumCurveOutput();
  }

  boost::optional<double> CurveQuartic::maximumCurveOutput() const {
    return getImpl<detail::CurveQuartic_Impl>()->maximumCurveOutput();
  }

  bool CurveQuartic::setMaximumCurveOutput(double maximumCurveOutput) {
    return getImpl<detail::CurveQuartic_Impl>()->setMaximumCurveOutput(maximumCurveOutput);
  }

  void CurveQuartic::resetMaximumCurveOutput() {
    getImpl<detail::CurveQuartic_Impl>()->resetMaximumCurveOutput();
  }

  std::string CurveQuartic::inputUnitTypeforX() const {
    return getImpl<detail::CurveQuartic_Impl>()->inputUnitTypeforX();
  }

  bool CurveQuartic::isInputUnitTypeforXDefaulted() const {
    return getImpl<detail::CurveQuartic_Impl>()->isInputUnitTypeforXDefaulted();
  }

  bool CurveQuartic::setInputUnitTypeforX(const std::string& inputUnitTypeforX) {
    return getImpl<detail::CurveQuartic_Impl>()->setInputUnitTypeforX(inputUnitTypeforX);
  }

  void CurveQuartic::resetInputUnitTypeforX() {
    getImpl<detail::CurveQuartic_Impl>()->resetInputUnitTypeforX();
  }

  std::string CurveQuartic::outputUnitType() const {
    return getImpl<detail::CurveQuartic_Impl>()->outputUnitType();
  }

  bool CurveQuartic::isOutputUnitTypeDefaulted() const {
    return getImpl<detail::CurveQuartic_Impl>()->isOutputUnitTypeDefaulted();
  }

  bool CurveQuartic::setOutputUnitType(const std::string& outputUnitType) {
    return getImpl<detail::CurveQuartic_Impl>()->setOutputUnitType(outputUnitType);
  }

  void CurveQuartic::resetOutputUnitType() {
    getImpl<detail::CurveQuartic_Impl>()->resetOutputUnitType();
  }

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
  namespace detail {

    double CurveQuartic_Impl::coefficient1Constant() const {
      const auto value = getDouble(openstudio::Curve_QuarticFields::Coefficient1Constant, true);
      OS_ASSERT(value);
      return *value;
    }

    bool CurveQuartic_Impl::setCoefficient1Constant(double coefficient1Constant) {
      const bool result = setDouble(openstudio::Curve_QuarticFields::Coefficient1Constant, coefficient1Constant);
      OS_ASSERT(result);
      return result;
    }

    double CurveQuartic_Impl::coefficient2x() const {
      const auto value = getDouble(openstudio::Curve_QuarticFields::Coefficient2x, true);
      OS_ASSERT(value);
      return *value;
    }

    bool CurveQuartic_Impl::setCoefficient2x(double coefficient2x) {
      const bool result = setDouble(openstudio::Curve_QuarticFields::Coefficient2x, coefficient2x);
      OS_ASSERT(result);
      return result;
    }

    double CurveQuartic_Impl::coefficient3xPOW2() const {
      const auto value = getDouble(openstudio::Curve_QuarticFields::Coefficient3x_POW_2, true);
      OS_ASSERT(value);
      return *value;
    }

    bool CurveQuartic_Impl::setCoefficient3xPOW2(double coefficient3xPOW2) {
      const bool result = setDouble(openstudio::Curve_QuarticFields::Coefficient3x_POW_2, coefficient3xPOW2);
      OS_ASSERT(result);
      return result;
    }

    double CurveQuartic_Impl::coefficient4xPOW3() const {
      const auto value = getDouble(openstudio::Curve_QuarticFields::Coefficient4x_POW_3, true);
      OS_ASSERT(value);
      return *value;
    }

    bool CurveQuartic_Impl::setCoefficient4xPOW3(double coefficient4xPOW3) {
      const bool result = setDouble(openstudio::Curve_QuarticFields::Coefficient4x_POW_3, coefficient4xPOW3);
      OS_ASSERT(result);
      return result;
    }

    double CurveQuartic_Impl::coefficient5xPOW4() const {
      const auto value = getDouble(openstudio::Curve_QuarticFields::Coefficient5x_POW_4, true);
      OS_ASSERT(value);
      return *value;
    }

    bool CurveQuartic_Impl::setCoefficient5xPOW4(double coefficient5xPOW4) {
      const bool result = setDouble(openstudio::Curve_QuarticFields::Coefficient5x_POW_4, coefficient5xPOW4);
      OS_ASSERT(result);
      return result;
    }

    double CurveQuartic_Impl::minimumValueofx() const {
      const auto value = getDouble(openstudio::Curve_QuarticFields::MinimumValueofx, true);
      OS_ASSERT(value);
      return *value;
    }

    bool CurveQuartic_Impl::setMinimumValueofx(double minimumValueofx) {
      const bool result = setDouble(openstudio::Curve_QuarticFields::MinimumValueofx, minimumValueofx);
      OS_ASSERT(result);
      return result;
    }

    double CurveQuartic_Impl::maximumValueofx() const {
      const auto value = getDouble(openstudio::Curve_QuarticFields::MaximumValueofx, true);
      OS_ASSERT(value);
      return *value;
    }

    bool CurveQuartic_Impl::setMaximumValueofx(double maximumValueofx) {
      const bool result = setDouble(openstudio::Curve_QuarticFields::MaximumValueofx, maximumValueofx);
      OS_ASSERT(result);
      return result;
    }

    boost::optional<double> CurveQuartic_Impl::minimumCurveOutput() const {
      return getDouble(openstudio::Curve_QuarticFields::MinimumCurveOutput, true);
    }

    bool CurveQuartic_Impl::setMinimumCurveOutput(double minimumCurveOutput) {
      const bool result = setDouble(openstudio::Curve_QuarticFields::MinimumCurveOutput, minimumCurveOutput);
      OS_ASSERT(result);
      return result;
    }

    void CurveQuartic_Impl::resetMinimumCurveOutput() {
      OS_ASSERT(setString(openstudio::Curve_QuarticFields::MinimumCurveOutput, ""));
    }

    boost::optional<double> CurveQuartic_Impl::maximumCurveOutput() const {
      return getDouble(openstudio::Curve_QuarticFields::MaximumCurveOutput, true);
    }

    bool CurveQuartic_Impl::setMaximumCurveOutput(double maximumCurveOutput) {
      const bool result = setDouble(openstudio::Curve_QuarticFields::MaximumCurveOutput, maximumCurveOutput);
      OS_ASSERT(result);
      return result;
    }

    void CurveQuartic_Impl::resetMaximumCurveOutput() {
      OS_ASSERT(setString(openstudio::Curve_QuarticFields::MaximumCurveOutput, ""));
    }

    std::string CurveQuartic_Impl::inputUnitTypeforX() const {
      const auto value = getString(openstudio::Curve_QuarticFields::InputUnitTypeforX, true);
      OS_ASSERT(value);
      return *value;
    }

    bool CurveQuartic_Impl::isInputUnitTypeforXDefaulted() const {
      return isEmpty(openstudio::Curve_QuarticFields::InputUnitTypeforX);
    }

    bool CurveQuartic_Impl::setInputUnitTypeforX(const std::string& inputUnitTypeforX) {
      return setString(openstudio::Curve_QuarticFields::InputUnitTypeforX, inputUnitTypeforX);
    }

    void CurveQuartic_Impl::resetInputUnitTypeforX() {
      OS_ASSERT(setString(openstudio::Curve_QuarticFields::InputUnitTypeforX, ""));
    }

    std::string CurveQuartic_Impl::outputUnitType() const {
      const auto value = getString(openstudio::Curve_QuarticFields::OutputUnitType, true);
      OS_ASSERT(value);
      return *value;
    }

    bool CurveQuartic_Impl::isOutputUnitTypeDefaulted() const {
      return isEmpty(openstudio::Curve_QuarticFields::OutputUnitType);
    }

    bool CurveQuartic_Impl::setOutputUnitType(const std::string& outputUnitType) {
      return setString(openstudio::Curve_QuarticFields::OutputUnitType, outputUnitType);
    }

    void CurveQuartic_Impl::resetOutputUnitType() {
      OS_ASSERT(setString(openstudio::Curve_QuarticFields::OutputUnitType, ""));
    }

    std::vector<std::string> CurveQuartic_Impl::validInputUnitTypeforXValues() const {
      return openstudio::epmodel::CurveQuartic::validInputUnitTypeforXValues();
    }

    std::vector<std::string> CurveQuartic_Impl::validOutputUnitTypeValues() const {
      return openstudio::epmodel::CurveQuartic::validOutputUnitTypeValues();
    }

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
