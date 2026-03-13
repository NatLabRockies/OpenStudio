/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "ModelObject/CurveCubicLinear.hpp"
#include "ModelObject/CurveCubicLinear_Impl.hpp"

#include "Model.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/core/StringHelpers.hpp>
#include <utilities/idd/Curve_CubicLinear_FieldEnums.hxx>
#include <utilities/idd/IddEnums.hxx>
#include <utilities/idd/IddFactory.hxx>

namespace openstudio {
namespace epmodel {

  namespace {

    boost::optional<std::string> curveCubicLinearDefaultString(unsigned fieldIndex) {
      const auto iddObject = IddFactory::instance().getObject(IddObjectType::Curve_CubicLinear);
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

  CurveCubicLinear::CurveCubicLinear(const Model& model) : ModelObject(CurveCubicLinear::iddObjectType(), model) {
    OS_ASSERT(getImpl<detail::CurveCubicLinear_Impl>());
    OS_ASSERT(setCoefficient1Constant(0.0));
    OS_ASSERT(setCoefficient2x(0.0));
    OS_ASSERT(setCoefficient3xPOW2(0.0));
    OS_ASSERT(setCoefficient4xPOW3(0.0));
    OS_ASSERT(setCoefficient5y(0.0));
    OS_ASSERT(setCoefficient6xTIMESY(0.0));
    OS_ASSERT(setMinimumValueofx(0.0));
    OS_ASSERT(setMaximumValueofx(1.0));
    OS_ASSERT(setMinimumValueofy(0.0));
    OS_ASSERT(setMaximumValueofy(1.0));
  }

  CurveCubicLinear::CurveCubicLinear(std::shared_ptr<detail::CurveCubicLinear_Impl> impl) : ModelObject(std::move(impl)) {}

  IddObjectType CurveCubicLinear::iddObjectType() {
    return IddObjectType::Curve_CubicLinear;
  }

  std::vector<std::string> CurveCubicLinear::validInputUnitTypeforXValues() {
    return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(), openstudio::Curve_CubicLinearFields::InputUnitTypeforX);
  }

  std::vector<std::string> CurveCubicLinear::validInputUnitTypeforYValues() {
    return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(), openstudio::Curve_CubicLinearFields::InputUnitTypeforY);
  }

  std::vector<std::string> CurveCubicLinear::validOutputUnitTypeValues() {
    return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(), openstudio::Curve_CubicLinearFields::OutputUnitType);
  }

  double CurveCubicLinear::coefficient1Constant() const {
    return getImpl<detail::CurveCubicLinear_Impl>()->coefficient1Constant();
  }

  bool CurveCubicLinear::setCoefficient1Constant(double coefficient1Constant) {
    return getImpl<detail::CurveCubicLinear_Impl>()->setCoefficient1Constant(coefficient1Constant);
  }

  double CurveCubicLinear::coefficient2x() const {
    return getImpl<detail::CurveCubicLinear_Impl>()->coefficient2x();
  }

  bool CurveCubicLinear::setCoefficient2x(double coefficient2x) {
    return getImpl<detail::CurveCubicLinear_Impl>()->setCoefficient2x(coefficient2x);
  }

  double CurveCubicLinear::coefficient3xPOW2() const {
    return getImpl<detail::CurveCubicLinear_Impl>()->coefficient3xPOW2();
  }

  bool CurveCubicLinear::setCoefficient3xPOW2(double coefficient3xPOW2) {
    return getImpl<detail::CurveCubicLinear_Impl>()->setCoefficient3xPOW2(coefficient3xPOW2);
  }

  double CurveCubicLinear::coefficient4xPOW3() const {
    return getImpl<detail::CurveCubicLinear_Impl>()->coefficient4xPOW3();
  }

  bool CurveCubicLinear::setCoefficient4xPOW3(double coefficient4xPOW3) {
    return getImpl<detail::CurveCubicLinear_Impl>()->setCoefficient4xPOW3(coefficient4xPOW3);
  }

  double CurveCubicLinear::coefficient5y() const {
    return getImpl<detail::CurveCubicLinear_Impl>()->coefficient5y();
  }

  bool CurveCubicLinear::setCoefficient5y(double coefficient5y) {
    return getImpl<detail::CurveCubicLinear_Impl>()->setCoefficient5y(coefficient5y);
  }

  double CurveCubicLinear::coefficient6xTIMESY() const {
    return getImpl<detail::CurveCubicLinear_Impl>()->coefficient6xTIMESY();
  }

  bool CurveCubicLinear::setCoefficient6xTIMESY(double coefficient6xTIMESY) {
    return getImpl<detail::CurveCubicLinear_Impl>()->setCoefficient6xTIMESY(coefficient6xTIMESY);
  }

  double CurveCubicLinear::minimumValueofx() const {
    return getImpl<detail::CurveCubicLinear_Impl>()->minimumValueofx();
  }

  bool CurveCubicLinear::setMinimumValueofx(double minimumValueofx) {
    return getImpl<detail::CurveCubicLinear_Impl>()->setMinimumValueofx(minimumValueofx);
  }

  double CurveCubicLinear::maximumValueofx() const {
    return getImpl<detail::CurveCubicLinear_Impl>()->maximumValueofx();
  }

  bool CurveCubicLinear::setMaximumValueofx(double maximumValueofx) {
    return getImpl<detail::CurveCubicLinear_Impl>()->setMaximumValueofx(maximumValueofx);
  }

  double CurveCubicLinear::minimumValueofy() const {
    return getImpl<detail::CurveCubicLinear_Impl>()->minimumValueofy();
  }

  bool CurveCubicLinear::setMinimumValueofy(double minimumValueofy) {
    return getImpl<detail::CurveCubicLinear_Impl>()->setMinimumValueofy(minimumValueofy);
  }

  double CurveCubicLinear::maximumValueofy() const {
    return getImpl<detail::CurveCubicLinear_Impl>()->maximumValueofy();
  }

  bool CurveCubicLinear::setMaximumValueofy(double maximumValueofy) {
    return getImpl<detail::CurveCubicLinear_Impl>()->setMaximumValueofy(maximumValueofy);
  }

  boost::optional<double> CurveCubicLinear::minimumCurveOutput() const {
    return getImpl<detail::CurveCubicLinear_Impl>()->minimumCurveOutput();
  }

  bool CurveCubicLinear::setMinimumCurveOutput(double minimumCurveOutput) {
    return getImpl<detail::CurveCubicLinear_Impl>()->setMinimumCurveOutput(minimumCurveOutput);
  }

  void CurveCubicLinear::resetMinimumCurveOutput() {
    getImpl<detail::CurveCubicLinear_Impl>()->resetMinimumCurveOutput();
  }

  boost::optional<double> CurveCubicLinear::maximumCurveOutput() const {
    return getImpl<detail::CurveCubicLinear_Impl>()->maximumCurveOutput();
  }

  bool CurveCubicLinear::setMaximumCurveOutput(double maximumCurveOutput) {
    return getImpl<detail::CurveCubicLinear_Impl>()->setMaximumCurveOutput(maximumCurveOutput);
  }

  void CurveCubicLinear::resetMaximumCurveOutput() {
    getImpl<detail::CurveCubicLinear_Impl>()->resetMaximumCurveOutput();
  }

  std::string CurveCubicLinear::inputUnitTypeforX() const {
    return getImpl<detail::CurveCubicLinear_Impl>()->inputUnitTypeforX();
  }

  bool CurveCubicLinear::isInputUnitTypeforXDefaulted() const {
    return getImpl<detail::CurveCubicLinear_Impl>()->isInputUnitTypeforXDefaulted();
  }

  bool CurveCubicLinear::setInputUnitTypeforX(const std::string& inputUnitTypeforX) {
    return getImpl<detail::CurveCubicLinear_Impl>()->setInputUnitTypeforX(inputUnitTypeforX);
  }

  void CurveCubicLinear::resetInputUnitTypeforX() {
    getImpl<detail::CurveCubicLinear_Impl>()->resetInputUnitTypeforX();
  }

  std::string CurveCubicLinear::inputUnitTypeforY() const {
    return getImpl<detail::CurveCubicLinear_Impl>()->inputUnitTypeforY();
  }

  bool CurveCubicLinear::isInputUnitTypeforYDefaulted() const {
    return getImpl<detail::CurveCubicLinear_Impl>()->isInputUnitTypeforYDefaulted();
  }

  bool CurveCubicLinear::setInputUnitTypeforY(const std::string& inputUnitTypeforY) {
    return getImpl<detail::CurveCubicLinear_Impl>()->setInputUnitTypeforY(inputUnitTypeforY);
  }

  void CurveCubicLinear::resetInputUnitTypeforY() {
    getImpl<detail::CurveCubicLinear_Impl>()->resetInputUnitTypeforY();
  }

  std::string CurveCubicLinear::outputUnitType() const {
    return getImpl<detail::CurveCubicLinear_Impl>()->outputUnitType();
  }

  bool CurveCubicLinear::isOutputUnitTypeDefaulted() const {
    return getImpl<detail::CurveCubicLinear_Impl>()->isOutputUnitTypeDefaulted();
  }

  bool CurveCubicLinear::setOutputUnitType(const std::string& outputUnitType) {
    return getImpl<detail::CurveCubicLinear_Impl>()->setOutputUnitType(outputUnitType);
  }

  void CurveCubicLinear::resetOutputUnitType() {
    getImpl<detail::CurveCubicLinear_Impl>()->resetOutputUnitType();
  }

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
  namespace detail {

    double CurveCubicLinear_Impl::coefficient1Constant() const {
      const auto value = getDouble(openstudio::Curve_CubicLinearFields::Coefficient1Constant, true);
      OS_ASSERT(value);
      return *value;
    }

    bool CurveCubicLinear_Impl::setCoefficient1Constant(double coefficient1Constant) {
      const bool result = setDouble(openstudio::Curve_CubicLinearFields::Coefficient1Constant, coefficient1Constant);
      OS_ASSERT(result);
      return result;
    }

    double CurveCubicLinear_Impl::coefficient2x() const {
      const auto value = getDouble(openstudio::Curve_CubicLinearFields::Coefficient2x, true);
      OS_ASSERT(value);
      return *value;
    }

    bool CurveCubicLinear_Impl::setCoefficient2x(double coefficient2x) {
      const bool result = setDouble(openstudio::Curve_CubicLinearFields::Coefficient2x, coefficient2x);
      OS_ASSERT(result);
      return result;
    }

    double CurveCubicLinear_Impl::coefficient3xPOW2() const {
      const auto value = getDouble(openstudio::Curve_CubicLinearFields::Coefficient3x_POW_2, true);
      OS_ASSERT(value);
      return *value;
    }

    bool CurveCubicLinear_Impl::setCoefficient3xPOW2(double coefficient3xPOW2) {
      const bool result = setDouble(openstudio::Curve_CubicLinearFields::Coefficient3x_POW_2, coefficient3xPOW2);
      OS_ASSERT(result);
      return result;
    }

    double CurveCubicLinear_Impl::coefficient4xPOW3() const {
      const auto value = getDouble(openstudio::Curve_CubicLinearFields::Coefficient4x_POW_3, true);
      OS_ASSERT(value);
      return *value;
    }

    bool CurveCubicLinear_Impl::setCoefficient4xPOW3(double coefficient4xPOW3) {
      const bool result = setDouble(openstudio::Curve_CubicLinearFields::Coefficient4x_POW_3, coefficient4xPOW3);
      OS_ASSERT(result);
      return result;
    }

    double CurveCubicLinear_Impl::coefficient5y() const {
      const auto value = getDouble(openstudio::Curve_CubicLinearFields::Coefficient5y, true);
      OS_ASSERT(value);
      return *value;
    }

    bool CurveCubicLinear_Impl::setCoefficient5y(double coefficient5y) {
      const bool result = setDouble(openstudio::Curve_CubicLinearFields::Coefficient5y, coefficient5y);
      OS_ASSERT(result);
      return result;
    }

    double CurveCubicLinear_Impl::coefficient6xTIMESY() const {
      const auto value = getDouble(openstudio::Curve_CubicLinearFields::Coefficient6x_TIMES_y, true);
      OS_ASSERT(value);
      return *value;
    }

    bool CurveCubicLinear_Impl::setCoefficient6xTIMESY(double coefficient6xTIMESY) {
      const bool result = setDouble(openstudio::Curve_CubicLinearFields::Coefficient6x_TIMES_y, coefficient6xTIMESY);
      OS_ASSERT(result);
      return result;
    }

    double CurveCubicLinear_Impl::minimumValueofx() const {
      const auto value = getDouble(openstudio::Curve_CubicLinearFields::MinimumValueofx, true);
      OS_ASSERT(value);
      return *value;
    }

    bool CurveCubicLinear_Impl::setMinimumValueofx(double minimumValueofx) {
      const bool result = setDouble(openstudio::Curve_CubicLinearFields::MinimumValueofx, minimumValueofx);
      OS_ASSERT(result);
      return result;
    }

    double CurveCubicLinear_Impl::maximumValueofx() const {
      const auto value = getDouble(openstudio::Curve_CubicLinearFields::MaximumValueofx, true);
      OS_ASSERT(value);
      return *value;
    }

    bool CurveCubicLinear_Impl::setMaximumValueofx(double maximumValueofx) {
      const bool result = setDouble(openstudio::Curve_CubicLinearFields::MaximumValueofx, maximumValueofx);
      OS_ASSERT(result);
      return result;
    }

    double CurveCubicLinear_Impl::minimumValueofy() const {
      const auto value = getDouble(openstudio::Curve_CubicLinearFields::MinimumValueofy, true);
      OS_ASSERT(value);
      return *value;
    }

    bool CurveCubicLinear_Impl::setMinimumValueofy(double minimumValueofy) {
      const bool result = setDouble(openstudio::Curve_CubicLinearFields::MinimumValueofy, minimumValueofy);
      OS_ASSERT(result);
      return result;
    }

    double CurveCubicLinear_Impl::maximumValueofy() const {
      const auto value = getDouble(openstudio::Curve_CubicLinearFields::MaximumValueofy, true);
      OS_ASSERT(value);
      return *value;
    }

    bool CurveCubicLinear_Impl::setMaximumValueofy(double maximumValueofy) {
      const bool result = setDouble(openstudio::Curve_CubicLinearFields::MaximumValueofy, maximumValueofy);
      OS_ASSERT(result);
      return result;
    }

    boost::optional<double> CurveCubicLinear_Impl::minimumCurveOutput() const {
      return getDouble(openstudio::Curve_CubicLinearFields::MinimumCurveOutput, true);
    }

    bool CurveCubicLinear_Impl::setMinimumCurveOutput(double minimumCurveOutput) {
      const bool result = setDouble(openstudio::Curve_CubicLinearFields::MinimumCurveOutput, minimumCurveOutput);
      OS_ASSERT(result);
      return result;
    }

    void CurveCubicLinear_Impl::resetMinimumCurveOutput() {
      OS_ASSERT(setString(openstudio::Curve_CubicLinearFields::MinimumCurveOutput, ""));
    }

    boost::optional<double> CurveCubicLinear_Impl::maximumCurveOutput() const {
      return getDouble(openstudio::Curve_CubicLinearFields::MaximumCurveOutput, true);
    }

    bool CurveCubicLinear_Impl::setMaximumCurveOutput(double maximumCurveOutput) {
      const bool result = setDouble(openstudio::Curve_CubicLinearFields::MaximumCurveOutput, maximumCurveOutput);
      OS_ASSERT(result);
      return result;
    }

    void CurveCubicLinear_Impl::resetMaximumCurveOutput() {
      OS_ASSERT(setString(openstudio::Curve_CubicLinearFields::MaximumCurveOutput, ""));
    }

    std::string CurveCubicLinear_Impl::inputUnitTypeforX() const {
      const auto value = getString(openstudio::Curve_CubicLinearFields::InputUnitTypeforX, true);
      OS_ASSERT(value);
      return *value;
    }

    bool CurveCubicLinear_Impl::isInputUnitTypeforXDefaulted() const {
      if (const auto value = getString(openstudio::Curve_CubicLinearFields::InputUnitTypeforX, false, true)) {
        if (const auto defaultValue = curveCubicLinearDefaultString(openstudio::Curve_CubicLinearFields::InputUnitTypeforX)) {
          return openstudio::istringEqual(*value, *defaultValue);
        }
        return false;
      }
      return true;
    }

    bool CurveCubicLinear_Impl::setInputUnitTypeforX(const std::string& inputUnitTypeforX) {
      return setString(openstudio::Curve_CubicLinearFields::InputUnitTypeforX, inputUnitTypeforX);
    }

    void CurveCubicLinear_Impl::resetInputUnitTypeforX() {
      bool result = false;
      if (const auto defaultValue = curveCubicLinearDefaultString(openstudio::Curve_CubicLinearFields::InputUnitTypeforX)) {
        result = setString(openstudio::Curve_CubicLinearFields::InputUnitTypeforX, *defaultValue);
      } else {
        result = setString(openstudio::Curve_CubicLinearFields::InputUnitTypeforX, "");
      }
      OS_ASSERT(result);
    }

    std::string CurveCubicLinear_Impl::inputUnitTypeforY() const {
      const auto value = getString(openstudio::Curve_CubicLinearFields::InputUnitTypeforY, true);
      OS_ASSERT(value);
      return *value;
    }

    bool CurveCubicLinear_Impl::isInputUnitTypeforYDefaulted() const {
      if (const auto value = getString(openstudio::Curve_CubicLinearFields::InputUnitTypeforY, false, true)) {
        if (const auto defaultValue = curveCubicLinearDefaultString(openstudio::Curve_CubicLinearFields::InputUnitTypeforY)) {
          return openstudio::istringEqual(*value, *defaultValue);
        }
        return false;
      }
      return true;
    }

    bool CurveCubicLinear_Impl::setInputUnitTypeforY(const std::string& inputUnitTypeforY) {
      return setString(openstudio::Curve_CubicLinearFields::InputUnitTypeforY, inputUnitTypeforY);
    }

    void CurveCubicLinear_Impl::resetInputUnitTypeforY() {
      bool result = false;
      if (const auto defaultValue = curveCubicLinearDefaultString(openstudio::Curve_CubicLinearFields::InputUnitTypeforY)) {
        result = setString(openstudio::Curve_CubicLinearFields::InputUnitTypeforY, *defaultValue);
      } else {
        result = setString(openstudio::Curve_CubicLinearFields::InputUnitTypeforY, "");
      }
      OS_ASSERT(result);
    }

    std::string CurveCubicLinear_Impl::outputUnitType() const {
      const auto value = getString(openstudio::Curve_CubicLinearFields::OutputUnitType, true);
      OS_ASSERT(value);
      return *value;
    }

    bool CurveCubicLinear_Impl::isOutputUnitTypeDefaulted() const {
      if (const auto value = getString(openstudio::Curve_CubicLinearFields::OutputUnitType, false, true)) {
        if (const auto defaultValue = curveCubicLinearDefaultString(openstudio::Curve_CubicLinearFields::OutputUnitType)) {
          return openstudio::istringEqual(*value, *defaultValue);
        }
        return false;
      }
      return true;
    }

    bool CurveCubicLinear_Impl::setOutputUnitType(const std::string& outputUnitType) {
      return setString(openstudio::Curve_CubicLinearFields::OutputUnitType, outputUnitType);
    }

    void CurveCubicLinear_Impl::resetOutputUnitType() {
      bool result = false;
      if (const auto defaultValue = curveCubicLinearDefaultString(openstudio::Curve_CubicLinearFields::OutputUnitType)) {
        result = setString(openstudio::Curve_CubicLinearFields::OutputUnitType, *defaultValue);
      } else {
        result = setString(openstudio::Curve_CubicLinearFields::OutputUnitType, "");
      }
      OS_ASSERT(result);
    }

    std::vector<std::string> CurveCubicLinear_Impl::validInputUnitTypeforXValues() const {
      return openstudio::epmodel::CurveCubicLinear::validInputUnitTypeforXValues();
    }

    std::vector<std::string> CurveCubicLinear_Impl::validInputUnitTypeforYValues() const {
      return openstudio::epmodel::CurveCubicLinear::validInputUnitTypeforYValues();
    }

    std::vector<std::string> CurveCubicLinear_Impl::validOutputUnitTypeValues() const {
      return openstudio::epmodel::CurveCubicLinear::validOutputUnitTypeValues();
    }

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
