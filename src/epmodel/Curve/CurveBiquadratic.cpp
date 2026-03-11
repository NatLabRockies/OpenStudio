/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "Curve/CurveBiquadratic.hpp"
#include "Curve/CurveBiquadratic_Impl.hpp"

#include "Model.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/core/StringHelpers.hpp>
#include <utilities/idd/Curve_Biquadratic_FieldEnums.hxx>
#include <utilities/idd/IddEnums.hxx>
#include <utilities/idd/IddFactory.hxx>

namespace openstudio {
namespace epmodel {

namespace {

boost::optional<std::string> curveBiquadraticDefaultString(unsigned fieldIndex) {
  const auto iddObject = IddFactory::instance().getObject(IddObjectType::Curve_Biquadratic);
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

CurveBiquadratic::CurveBiquadratic(const Model& model) : ModelObject(CurveBiquadratic::iddObjectType(), model) {
  OS_ASSERT(getImpl<detail::CurveBiquadratic_Impl>());
  OS_ASSERT(setCoefficient1Constant(0.0));
  OS_ASSERT(setCoefficient2x(0.0));
  OS_ASSERT(setCoefficient3xPOW2(0.0));
  OS_ASSERT(setCoefficient4y(0.0));
  OS_ASSERT(setCoefficient5yPOW2(0.0));
  OS_ASSERT(setCoefficient6xTIMESY(0.0));
  OS_ASSERT(setMinimumValueofx(0.0));
  OS_ASSERT(setMaximumValueofx(1.0));
  OS_ASSERT(setMinimumValueofy(0.0));
  OS_ASSERT(setMaximumValueofy(1.0));
}

CurveBiquadratic::CurveBiquadratic(std::shared_ptr<detail::CurveBiquadratic_Impl> impl) : ModelObject(std::move(impl)) {}

IddObjectType CurveBiquadratic::iddObjectType() {
  return IddObjectType::Curve_Biquadratic;
}

std::vector<std::string> CurveBiquadratic::validInputUnitTypeforXValues() {
  return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(), openstudio::Curve_BiquadraticFields::InputUnitTypeforX);
}

std::vector<std::string> CurveBiquadratic::validInputUnitTypeforYValues() {
  return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(), openstudio::Curve_BiquadraticFields::InputUnitTypeforY);
}

std::vector<std::string> CurveBiquadratic::validOutputUnitTypeValues() {
  return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(), openstudio::Curve_BiquadraticFields::OutputUnitType);
}

double CurveBiquadratic::coefficient1Constant() const {
  return getImpl<detail::CurveBiquadratic_Impl>()->coefficient1Constant();
}

double CurveBiquadratic::coefficient2x() const {
  return getImpl<detail::CurveBiquadratic_Impl>()->coefficient2x();
}

double CurveBiquadratic::coefficient3xPOW2() const {
  return getImpl<detail::CurveBiquadratic_Impl>()->coefficient3xPOW2();
}

double CurveBiquadratic::coefficient4y() const {
  return getImpl<detail::CurveBiquadratic_Impl>()->coefficient4y();
}

double CurveBiquadratic::coefficient5yPOW2() const {
  return getImpl<detail::CurveBiquadratic_Impl>()->coefficient5yPOW2();
}

double CurveBiquadratic::coefficient6xTIMESY() const {
  return getImpl<detail::CurveBiquadratic_Impl>()->coefficient6xTIMESY();
}

double CurveBiquadratic::minimumValueofx() const {
  return getImpl<detail::CurveBiquadratic_Impl>()->minimumValueofx();
}

double CurveBiquadratic::maximumValueofx() const {
  return getImpl<detail::CurveBiquadratic_Impl>()->maximumValueofx();
}

double CurveBiquadratic::minimumValueofy() const {
  return getImpl<detail::CurveBiquadratic_Impl>()->minimumValueofy();
}

double CurveBiquadratic::maximumValueofy() const {
  return getImpl<detail::CurveBiquadratic_Impl>()->maximumValueofy();
}

boost::optional<double> CurveBiquadratic::minimumCurveOutput() const {
  return getImpl<detail::CurveBiquadratic_Impl>()->minimumCurveOutput();
}

boost::optional<double> CurveBiquadratic::maximumCurveOutput() const {
  return getImpl<detail::CurveBiquadratic_Impl>()->maximumCurveOutput();
}

std::string CurveBiquadratic::inputUnitTypeforX() const {
  return getImpl<detail::CurveBiquadratic_Impl>()->inputUnitTypeforX();
}

bool CurveBiquadratic::isInputUnitTypeforXDefaulted() const {
  return getImpl<detail::CurveBiquadratic_Impl>()->isInputUnitTypeforXDefaulted();
}

std::string CurveBiquadratic::inputUnitTypeforY() const {
  return getImpl<detail::CurveBiquadratic_Impl>()->inputUnitTypeforY();
}

bool CurveBiquadratic::isInputUnitTypeforYDefaulted() const {
  return getImpl<detail::CurveBiquadratic_Impl>()->isInputUnitTypeforYDefaulted();
}

std::string CurveBiquadratic::outputUnitType() const {
  return getImpl<detail::CurveBiquadratic_Impl>()->outputUnitType();
}

bool CurveBiquadratic::isOutputUnitTypeDefaulted() const {
  return getImpl<detail::CurveBiquadratic_Impl>()->isOutputUnitTypeDefaulted();
}

bool CurveBiquadratic::setCoefficient1Constant(double coefficient1Constant) {
  return getImpl<detail::CurveBiquadratic_Impl>()->setCoefficient1Constant(coefficient1Constant);
}

bool CurveBiquadratic::setCoefficient2x(double coefficient2x) {
  return getImpl<detail::CurveBiquadratic_Impl>()->setCoefficient2x(coefficient2x);
}

bool CurveBiquadratic::setCoefficient3xPOW2(double coefficient3xPOW2) {
  return getImpl<detail::CurveBiquadratic_Impl>()->setCoefficient3xPOW2(coefficient3xPOW2);
}

bool CurveBiquadratic::setCoefficient4y(double coefficient4y) {
  return getImpl<detail::CurveBiquadratic_Impl>()->setCoefficient4y(coefficient4y);
}

bool CurveBiquadratic::setCoefficient5yPOW2(double coefficient5yPOW2) {
  return getImpl<detail::CurveBiquadratic_Impl>()->setCoefficient5yPOW2(coefficient5yPOW2);
}

bool CurveBiquadratic::setCoefficient6xTIMESY(double coefficient6xTIMESY) {
  return getImpl<detail::CurveBiquadratic_Impl>()->setCoefficient6xTIMESY(coefficient6xTIMESY);
}

bool CurveBiquadratic::setMinimumValueofx(double minimumValueofx) {
  return getImpl<detail::CurveBiquadratic_Impl>()->setMinimumValueofx(minimumValueofx);
}

bool CurveBiquadratic::setMaximumValueofx(double maximumValueofx) {
  return getImpl<detail::CurveBiquadratic_Impl>()->setMaximumValueofx(maximumValueofx);
}

bool CurveBiquadratic::setMinimumValueofy(double minimumValueofy) {
  return getImpl<detail::CurveBiquadratic_Impl>()->setMinimumValueofy(minimumValueofy);
}

bool CurveBiquadratic::setMaximumValueofy(double maximumValueofy) {
  return getImpl<detail::CurveBiquadratic_Impl>()->setMaximumValueofy(maximumValueofy);
}

bool CurveBiquadratic::setMinimumCurveOutput(double minimumCurveOutput) {
  return getImpl<detail::CurveBiquadratic_Impl>()->setMinimumCurveOutput(minimumCurveOutput);
}

void CurveBiquadratic::resetMinimumCurveOutput() {
  getImpl<detail::CurveBiquadratic_Impl>()->resetMinimumCurveOutput();
}

bool CurveBiquadratic::setMaximumCurveOutput(double maximumCurveOutput) {
  return getImpl<detail::CurveBiquadratic_Impl>()->setMaximumCurveOutput(maximumCurveOutput);
}

void CurveBiquadratic::resetMaximumCurveOutput() {
  getImpl<detail::CurveBiquadratic_Impl>()->resetMaximumCurveOutput();
}

bool CurveBiquadratic::setInputUnitTypeforX(const std::string& inputUnitTypeforX) {
  return getImpl<detail::CurveBiquadratic_Impl>()->setInputUnitTypeforX(inputUnitTypeforX);
}

void CurveBiquadratic::resetInputUnitTypeforX() {
  getImpl<detail::CurveBiquadratic_Impl>()->resetInputUnitTypeforX();
}

bool CurveBiquadratic::setInputUnitTypeforY(const std::string& inputUnitTypeforY) {
  return getImpl<detail::CurveBiquadratic_Impl>()->setInputUnitTypeforY(inputUnitTypeforY);
}

void CurveBiquadratic::resetInputUnitTypeforY() {
  getImpl<detail::CurveBiquadratic_Impl>()->resetInputUnitTypeforY();
}

bool CurveBiquadratic::setOutputUnitType(const std::string& outputUnitType) {
  return getImpl<detail::CurveBiquadratic_Impl>()->setOutputUnitType(outputUnitType);
}

void CurveBiquadratic::resetOutputUnitType() {
  getImpl<detail::CurveBiquadratic_Impl>()->resetOutputUnitType();
}

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
namespace detail {

double CurveBiquadratic_Impl::coefficient1Constant() const {
  const auto value = getDouble(openstudio::Curve_BiquadraticFields::Coefficient1Constant, true);
  OS_ASSERT(value);
  return *value;
}

double CurveBiquadratic_Impl::coefficient2x() const {
  const auto value = getDouble(openstudio::Curve_BiquadraticFields::Coefficient2x, true);
  OS_ASSERT(value);
  return *value;
}

double CurveBiquadratic_Impl::coefficient3xPOW2() const {
  const auto value = getDouble(openstudio::Curve_BiquadraticFields::Coefficient3x_POW_2, true);
  OS_ASSERT(value);
  return *value;
}

double CurveBiquadratic_Impl::coefficient4y() const {
  const auto value = getDouble(openstudio::Curve_BiquadraticFields::Coefficient4y, true);
  OS_ASSERT(value);
  return *value;
}

double CurveBiquadratic_Impl::coefficient5yPOW2() const {
  const auto value = getDouble(openstudio::Curve_BiquadraticFields::Coefficient5y_POW_2, true);
  OS_ASSERT(value);
  return *value;
}

double CurveBiquadratic_Impl::coefficient6xTIMESY() const {
  const auto value = getDouble(openstudio::Curve_BiquadraticFields::Coefficient6x_TIMES_y, true);
  OS_ASSERT(value);
  return *value;
}

double CurveBiquadratic_Impl::minimumValueofx() const {
  const auto value = getDouble(openstudio::Curve_BiquadraticFields::MinimumValueofx, true);
  OS_ASSERT(value);
  return *value;
}

double CurveBiquadratic_Impl::maximumValueofx() const {
  const auto value = getDouble(openstudio::Curve_BiquadraticFields::MaximumValueofx, true);
  OS_ASSERT(value);
  return *value;
}

double CurveBiquadratic_Impl::minimumValueofy() const {
  const auto value = getDouble(openstudio::Curve_BiquadraticFields::MinimumValueofy, true);
  OS_ASSERT(value);
  return *value;
}

double CurveBiquadratic_Impl::maximumValueofy() const {
  const auto value = getDouble(openstudio::Curve_BiquadraticFields::MaximumValueofy, true);
  OS_ASSERT(value);
  return *value;
}

boost::optional<double> CurveBiquadratic_Impl::minimumCurveOutput() const {
  return getDouble(openstudio::Curve_BiquadraticFields::MinimumCurveOutput, true);
}

boost::optional<double> CurveBiquadratic_Impl::maximumCurveOutput() const {
  return getDouble(openstudio::Curve_BiquadraticFields::MaximumCurveOutput, true);
}

std::string CurveBiquadratic_Impl::inputUnitTypeforX() const {
  const auto value = getString(openstudio::Curve_BiquadraticFields::InputUnitTypeforX, true);
  OS_ASSERT(value);
  return *value;
}

bool CurveBiquadratic_Impl::isInputUnitTypeforXDefaulted() const {
  if (const auto value = getString(openstudio::Curve_BiquadraticFields::InputUnitTypeforX, false, true)) {
    if (const auto defaultValue = curveBiquadraticDefaultString(openstudio::Curve_BiquadraticFields::InputUnitTypeforX)) {
      return openstudio::istringEqual(*value, *defaultValue);
    }
    return false;
  }
  return true;
}

std::string CurveBiquadratic_Impl::inputUnitTypeforY() const {
  const auto value = getString(openstudio::Curve_BiquadraticFields::InputUnitTypeforY, true);
  OS_ASSERT(value);
  return *value;
}

bool CurveBiquadratic_Impl::isInputUnitTypeforYDefaulted() const {
  if (const auto value = getString(openstudio::Curve_BiquadraticFields::InputUnitTypeforY, false, true)) {
    if (const auto defaultValue = curveBiquadraticDefaultString(openstudio::Curve_BiquadraticFields::InputUnitTypeforY)) {
      return openstudio::istringEqual(*value, *defaultValue);
    }
    return false;
  }
  return true;
}

std::string CurveBiquadratic_Impl::outputUnitType() const {
  const auto value = getString(openstudio::Curve_BiquadraticFields::OutputUnitType, true);
  OS_ASSERT(value);
  return *value;
}

bool CurveBiquadratic_Impl::isOutputUnitTypeDefaulted() const {
  if (const auto value = getString(openstudio::Curve_BiquadraticFields::OutputUnitType, false, true)) {
    if (const auto defaultValue = curveBiquadraticDefaultString(openstudio::Curve_BiquadraticFields::OutputUnitType)) {
      return openstudio::istringEqual(*value, *defaultValue);
    }
    return false;
  }
  return true;
}

bool CurveBiquadratic_Impl::setCoefficient1Constant(double coefficient1Constant) {
  const bool result = setDouble(openstudio::Curve_BiquadraticFields::Coefficient1Constant, coefficient1Constant);
  OS_ASSERT(result);
  return result;
}

bool CurveBiquadratic_Impl::setCoefficient2x(double coefficient2x) {
  const bool result = setDouble(openstudio::Curve_BiquadraticFields::Coefficient2x, coefficient2x);
  OS_ASSERT(result);
  return result;
}

bool CurveBiquadratic_Impl::setCoefficient3xPOW2(double coefficient3xPOW2) {
  const bool result = setDouble(openstudio::Curve_BiquadraticFields::Coefficient3x_POW_2, coefficient3xPOW2);
  OS_ASSERT(result);
  return result;
}

bool CurveBiquadratic_Impl::setCoefficient4y(double coefficient4y) {
  const bool result = setDouble(openstudio::Curve_BiquadraticFields::Coefficient4y, coefficient4y);
  OS_ASSERT(result);
  return result;
}

bool CurveBiquadratic_Impl::setCoefficient5yPOW2(double coefficient5yPOW2) {
  const bool result = setDouble(openstudio::Curve_BiquadraticFields::Coefficient5y_POW_2, coefficient5yPOW2);
  OS_ASSERT(result);
  return result;
}

bool CurveBiquadratic_Impl::setCoefficient6xTIMESY(double coefficient6xTIMESY) {
  const bool result = setDouble(openstudio::Curve_BiquadraticFields::Coefficient6x_TIMES_y, coefficient6xTIMESY);
  OS_ASSERT(result);
  return result;
}

bool CurveBiquadratic_Impl::setMinimumValueofx(double minimumValueofx) {
  const bool result = setDouble(openstudio::Curve_BiquadraticFields::MinimumValueofx, minimumValueofx);
  OS_ASSERT(result);
  return result;
}

bool CurveBiquadratic_Impl::setMaximumValueofx(double maximumValueofx) {
  const bool result = setDouble(openstudio::Curve_BiquadraticFields::MaximumValueofx, maximumValueofx);
  OS_ASSERT(result);
  return result;
}

bool CurveBiquadratic_Impl::setMinimumValueofy(double minimumValueofy) {
  const bool result = setDouble(openstudio::Curve_BiquadraticFields::MinimumValueofy, minimumValueofy);
  OS_ASSERT(result);
  return result;
}

bool CurveBiquadratic_Impl::setMaximumValueofy(double maximumValueofy) {
  const bool result = setDouble(openstudio::Curve_BiquadraticFields::MaximumValueofy, maximumValueofy);
  OS_ASSERT(result);
  return result;
}

bool CurveBiquadratic_Impl::setMinimumCurveOutput(double minimumCurveOutput) {
  const bool result = setDouble(openstudio::Curve_BiquadraticFields::MinimumCurveOutput, minimumCurveOutput);
  OS_ASSERT(result);
  return result;
}

void CurveBiquadratic_Impl::resetMinimumCurveOutput() {
  OS_ASSERT(setString(openstudio::Curve_BiquadraticFields::MinimumCurveOutput, ""));
}

bool CurveBiquadratic_Impl::setMaximumCurveOutput(double maximumCurveOutput) {
  const bool result = setDouble(openstudio::Curve_BiquadraticFields::MaximumCurveOutput, maximumCurveOutput);
  OS_ASSERT(result);
  return result;
}

void CurveBiquadratic_Impl::resetMaximumCurveOutput() {
  OS_ASSERT(setString(openstudio::Curve_BiquadraticFields::MaximumCurveOutput, ""));
}

bool CurveBiquadratic_Impl::setInputUnitTypeforX(const std::string& inputUnitTypeforX) {
  return setString(openstudio::Curve_BiquadraticFields::InputUnitTypeforX, inputUnitTypeforX);
}

void CurveBiquadratic_Impl::resetInputUnitTypeforX() {
  bool result = false;
  if (const auto defaultValue = curveBiquadraticDefaultString(openstudio::Curve_BiquadraticFields::InputUnitTypeforX)) {
    result = setString(openstudio::Curve_BiquadraticFields::InputUnitTypeforX, *defaultValue);
  } else {
    result = setString(openstudio::Curve_BiquadraticFields::InputUnitTypeforX, "");
  }
  OS_ASSERT(result);
}

bool CurveBiquadratic_Impl::setInputUnitTypeforY(const std::string& inputUnitTypeforY) {
  return setString(openstudio::Curve_BiquadraticFields::InputUnitTypeforY, inputUnitTypeforY);
}

void CurveBiquadratic_Impl::resetInputUnitTypeforY() {
  bool result = false;
  if (const auto defaultValue = curveBiquadraticDefaultString(openstudio::Curve_BiquadraticFields::InputUnitTypeforY)) {
    result = setString(openstudio::Curve_BiquadraticFields::InputUnitTypeforY, *defaultValue);
  } else {
    result = setString(openstudio::Curve_BiquadraticFields::InputUnitTypeforY, "");
  }
  OS_ASSERT(result);
}

bool CurveBiquadratic_Impl::setOutputUnitType(const std::string& outputUnitType) {
  return setString(openstudio::Curve_BiquadraticFields::OutputUnitType, outputUnitType);
}

void CurveBiquadratic_Impl::resetOutputUnitType() {
  bool result = false;
  if (const auto defaultValue = curveBiquadraticDefaultString(openstudio::Curve_BiquadraticFields::OutputUnitType)) {
    result = setString(openstudio::Curve_BiquadraticFields::OutputUnitType, *defaultValue);
  } else {
    result = setString(openstudio::Curve_BiquadraticFields::OutputUnitType, "");
  }
  OS_ASSERT(result);
}

std::vector<std::string> CurveBiquadratic_Impl::validInputUnitTypeforXValues() const {
  return openstudio::epmodel::CurveBiquadratic::validInputUnitTypeforXValues();
}

std::vector<std::string> CurveBiquadratic_Impl::validInputUnitTypeforYValues() const {
  return openstudio::epmodel::CurveBiquadratic::validInputUnitTypeforYValues();
}

std::vector<std::string> CurveBiquadratic_Impl::validOutputUnitTypeValues() const {
  return openstudio::epmodel::CurveBiquadratic::validOutputUnitTypeValues();
}

}  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
