/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "Curve/CurveBicubic.hpp"
#include "Curve/CurveBicubic_Impl.hpp"

#include "Model.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/core/StringHelpers.hpp>
#include <utilities/idd/Curve_Bicubic_FieldEnums.hxx>
#include <utilities/idd/IddEnums.hxx>
#include <utilities/idd/IddFactory.hxx>

namespace openstudio {
namespace epmodel {

namespace {

boost::optional<std::string> curveBicubicDefaultString(unsigned fieldIndex) {
  const auto iddObject = IddFactory::instance().getObject(IddObjectType::Curve_Bicubic);
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

CurveBicubic::CurveBicubic(const Model& model) : ModelObject(CurveBicubic::iddObjectType(), model) {
  OS_ASSERT(getImpl<detail::CurveBicubic_Impl>());
  OS_ASSERT(setCoefficient1Constant(0.0));
  OS_ASSERT(setCoefficient2x(0.0));
  OS_ASSERT(setCoefficient3xPOW2(0.0));
  OS_ASSERT(setCoefficient4y(0.0));
  OS_ASSERT(setCoefficient5yPOW2(0.0));
  OS_ASSERT(setCoefficient6xTIMESY(0.0));
  OS_ASSERT(setCoefficient7xPOW3(0.0));
  OS_ASSERT(setCoefficient8yPOW3(0.0));
  OS_ASSERT(setCoefficient9xPOW2TIMESY(0.0));
  OS_ASSERT(setCoefficient10xTIMESYPOW2(0.0));
  OS_ASSERT(setMinimumValueofx(0.0));
  OS_ASSERT(setMaximumValueofx(1.0));
  OS_ASSERT(setMinimumValueofy(0.0));
  OS_ASSERT(setMaximumValueofy(1.0));
}

CurveBicubic::CurveBicubic(std::shared_ptr<detail::CurveBicubic_Impl> impl) : ModelObject(std::move(impl)) {}

IddObjectType CurveBicubic::iddObjectType() {
  return IddObjectType::Curve_Bicubic;
}

std::vector<std::string> CurveBicubic::validInputUnitTypeforXValues() {
  return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(), openstudio::Curve_BicubicFields::InputUnitTypeforX);
}

std::vector<std::string> CurveBicubic::validInputUnitTypeforYValues() {
  return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(), openstudio::Curve_BicubicFields::InputUnitTypeforY);
}

std::vector<std::string> CurveBicubic::validOutputUnitTypeValues() {
  return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(), openstudio::Curve_BicubicFields::OutputUnitType);
}

double CurveBicubic::coefficient1Constant() const {
  return getImpl<detail::CurveBicubic_Impl>()->coefficient1Constant();
}

double CurveBicubic::coefficient2x() const {
  return getImpl<detail::CurveBicubic_Impl>()->coefficient2x();
}

double CurveBicubic::coefficient3xPOW2() const {
  return getImpl<detail::CurveBicubic_Impl>()->coefficient3xPOW2();
}

double CurveBicubic::coefficient4y() const {
  return getImpl<detail::CurveBicubic_Impl>()->coefficient4y();
}

double CurveBicubic::coefficient5yPOW2() const {
  return getImpl<detail::CurveBicubic_Impl>()->coefficient5yPOW2();
}

double CurveBicubic::coefficient6xTIMESY() const {
  return getImpl<detail::CurveBicubic_Impl>()->coefficient6xTIMESY();
}

double CurveBicubic::coefficient7xPOW3() const {
  return getImpl<detail::CurveBicubic_Impl>()->coefficient7xPOW3();
}

double CurveBicubic::coefficient8yPOW3() const {
  return getImpl<detail::CurveBicubic_Impl>()->coefficient8yPOW3();
}

double CurveBicubic::coefficient9xPOW2TIMESY() const {
  return getImpl<detail::CurveBicubic_Impl>()->coefficient9xPOW2TIMESY();
}

double CurveBicubic::coefficient10xTIMESYPOW2() const {
  return getImpl<detail::CurveBicubic_Impl>()->coefficient10xTIMESYPOW2();
}

double CurveBicubic::minimumValueofx() const {
  return getImpl<detail::CurveBicubic_Impl>()->minimumValueofx();
}

double CurveBicubic::maximumValueofx() const {
  return getImpl<detail::CurveBicubic_Impl>()->maximumValueofx();
}

double CurveBicubic::minimumValueofy() const {
  return getImpl<detail::CurveBicubic_Impl>()->minimumValueofy();
}

double CurveBicubic::maximumValueofy() const {
  return getImpl<detail::CurveBicubic_Impl>()->maximumValueofy();
}

boost::optional<double> CurveBicubic::minimumCurveOutput() const {
  return getImpl<detail::CurveBicubic_Impl>()->minimumCurveOutput();
}

boost::optional<double> CurveBicubic::maximumCurveOutput() const {
  return getImpl<detail::CurveBicubic_Impl>()->maximumCurveOutput();
}

std::string CurveBicubic::inputUnitTypeforX() const {
  return getImpl<detail::CurveBicubic_Impl>()->inputUnitTypeforX();
}

bool CurveBicubic::isInputUnitTypeforXDefaulted() const {
  return getImpl<detail::CurveBicubic_Impl>()->isInputUnitTypeforXDefaulted();
}

std::string CurveBicubic::inputUnitTypeforY() const {
  return getImpl<detail::CurveBicubic_Impl>()->inputUnitTypeforY();
}

bool CurveBicubic::isInputUnitTypeforYDefaulted() const {
  return getImpl<detail::CurveBicubic_Impl>()->isInputUnitTypeforYDefaulted();
}

std::string CurveBicubic::outputUnitType() const {
  return getImpl<detail::CurveBicubic_Impl>()->outputUnitType();
}

bool CurveBicubic::isOutputUnitTypeDefaulted() const {
  return getImpl<detail::CurveBicubic_Impl>()->isOutputUnitTypeDefaulted();
}

bool CurveBicubic::setCoefficient1Constant(double coefficient1Constant) {
  return getImpl<detail::CurveBicubic_Impl>()->setCoefficient1Constant(coefficient1Constant);
}

bool CurveBicubic::setCoefficient2x(double coefficient2x) {
  return getImpl<detail::CurveBicubic_Impl>()->setCoefficient2x(coefficient2x);
}

bool CurveBicubic::setCoefficient3xPOW2(double coefficient3xPOW2) {
  return getImpl<detail::CurveBicubic_Impl>()->setCoefficient3xPOW2(coefficient3xPOW2);
}

bool CurveBicubic::setCoefficient4y(double coefficient4y) {
  return getImpl<detail::CurveBicubic_Impl>()->setCoefficient4y(coefficient4y);
}

bool CurveBicubic::setCoefficient5yPOW2(double coefficient5yPOW2) {
  return getImpl<detail::CurveBicubic_Impl>()->setCoefficient5yPOW2(coefficient5yPOW2);
}

bool CurveBicubic::setCoefficient6xTIMESY(double coefficient6xTIMESY) {
  return getImpl<detail::CurveBicubic_Impl>()->setCoefficient6xTIMESY(coefficient6xTIMESY);
}

bool CurveBicubic::setCoefficient7xPOW3(double coefficient7xPOW3) {
  return getImpl<detail::CurveBicubic_Impl>()->setCoefficient7xPOW3(coefficient7xPOW3);
}

bool CurveBicubic::setCoefficient8yPOW3(double coefficient8yPOW3) {
  return getImpl<detail::CurveBicubic_Impl>()->setCoefficient8yPOW3(coefficient8yPOW3);
}

bool CurveBicubic::setCoefficient9xPOW2TIMESY(double coefficient9xPOW2TIMESY) {
  return getImpl<detail::CurveBicubic_Impl>()->setCoefficient9xPOW2TIMESY(coefficient9xPOW2TIMESY);
}

bool CurveBicubic::setCoefficient10xTIMESYPOW2(double coefficient10xTIMESYPOW2) {
  return getImpl<detail::CurveBicubic_Impl>()->setCoefficient10xTIMESYPOW2(coefficient10xTIMESYPOW2);
}

bool CurveBicubic::setMinimumValueofx(double minimumValueofx) {
  return getImpl<detail::CurveBicubic_Impl>()->setMinimumValueofx(minimumValueofx);
}

bool CurveBicubic::setMaximumValueofx(double maximumValueofx) {
  return getImpl<detail::CurveBicubic_Impl>()->setMaximumValueofx(maximumValueofx);
}

bool CurveBicubic::setMinimumValueofy(double minimumValueofy) {
  return getImpl<detail::CurveBicubic_Impl>()->setMinimumValueofy(minimumValueofy);
}

bool CurveBicubic::setMaximumValueofy(double maximumValueofy) {
  return getImpl<detail::CurveBicubic_Impl>()->setMaximumValueofy(maximumValueofy);
}

bool CurveBicubic::setMinimumCurveOutput(double minimumCurveOutput) {
  return getImpl<detail::CurveBicubic_Impl>()->setMinimumCurveOutput(minimumCurveOutput);
}

void CurveBicubic::resetMinimumCurveOutput() {
  getImpl<detail::CurveBicubic_Impl>()->resetMinimumCurveOutput();
}

bool CurveBicubic::setMaximumCurveOutput(double maximumCurveOutput) {
  return getImpl<detail::CurveBicubic_Impl>()->setMaximumCurveOutput(maximumCurveOutput);
}

void CurveBicubic::resetMaximumCurveOutput() {
  getImpl<detail::CurveBicubic_Impl>()->resetMaximumCurveOutput();
}

bool CurveBicubic::setInputUnitTypeforX(const std::string& inputUnitTypeforX) {
  return getImpl<detail::CurveBicubic_Impl>()->setInputUnitTypeforX(inputUnitTypeforX);
}

void CurveBicubic::resetInputUnitTypeforX() {
  getImpl<detail::CurveBicubic_Impl>()->resetInputUnitTypeforX();
}

bool CurveBicubic::setInputUnitTypeforY(const std::string& inputUnitTypeforY) {
  return getImpl<detail::CurveBicubic_Impl>()->setInputUnitTypeforY(inputUnitTypeforY);
}

void CurveBicubic::resetInputUnitTypeforY() {
  getImpl<detail::CurveBicubic_Impl>()->resetInputUnitTypeforY();
}

bool CurveBicubic::setOutputUnitType(const std::string& outputUnitType) {
  return getImpl<detail::CurveBicubic_Impl>()->setOutputUnitType(outputUnitType);
}

void CurveBicubic::resetOutputUnitType() {
  getImpl<detail::CurveBicubic_Impl>()->resetOutputUnitType();
}

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
namespace detail {

double CurveBicubic_Impl::coefficient1Constant() const {
  const auto value = getDouble(openstudio::Curve_BicubicFields::Coefficient1Constant, true);
  OS_ASSERT(value);
  return *value;
}

double CurveBicubic_Impl::coefficient2x() const {
  const auto value = getDouble(openstudio::Curve_BicubicFields::Coefficient2x, true);
  OS_ASSERT(value);
  return *value;
}

double CurveBicubic_Impl::coefficient3xPOW2() const {
  const auto value = getDouble(openstudio::Curve_BicubicFields::Coefficient3x_POW_2, true);
  OS_ASSERT(value);
  return *value;
}

double CurveBicubic_Impl::coefficient4y() const {
  const auto value = getDouble(openstudio::Curve_BicubicFields::Coefficient4y, true);
  OS_ASSERT(value);
  return *value;
}

double CurveBicubic_Impl::coefficient5yPOW2() const {
  const auto value = getDouble(openstudio::Curve_BicubicFields::Coefficient5y_POW_2, true);
  OS_ASSERT(value);
  return *value;
}

double CurveBicubic_Impl::coefficient6xTIMESY() const {
  const auto value = getDouble(openstudio::Curve_BicubicFields::Coefficient6x_TIMES_y, true);
  OS_ASSERT(value);
  return *value;
}

double CurveBicubic_Impl::coefficient7xPOW3() const {
  const auto value = getDouble(openstudio::Curve_BicubicFields::Coefficient7x_POW_3, true);
  OS_ASSERT(value);
  return *value;
}

double CurveBicubic_Impl::coefficient8yPOW3() const {
  const auto value = getDouble(openstudio::Curve_BicubicFields::Coefficient8y_POW_3, true);
  OS_ASSERT(value);
  return *value;
}

double CurveBicubic_Impl::coefficient9xPOW2TIMESY() const {
  const auto value = getDouble(openstudio::Curve_BicubicFields::Coefficient9x_POW_2_TIMES_y, true);
  OS_ASSERT(value);
  return *value;
}

double CurveBicubic_Impl::coefficient10xTIMESYPOW2() const {
  const auto value = getDouble(openstudio::Curve_BicubicFields::Coefficient10x_TIMES_y_POW_2, true);
  OS_ASSERT(value);
  return *value;
}

double CurveBicubic_Impl::minimumValueofx() const {
  const auto value = getDouble(openstudio::Curve_BicubicFields::MinimumValueofx, true);
  OS_ASSERT(value);
  return *value;
}

double CurveBicubic_Impl::maximumValueofx() const {
  const auto value = getDouble(openstudio::Curve_BicubicFields::MaximumValueofx, true);
  OS_ASSERT(value);
  return *value;
}

double CurveBicubic_Impl::minimumValueofy() const {
  const auto value = getDouble(openstudio::Curve_BicubicFields::MinimumValueofy, true);
  OS_ASSERT(value);
  return *value;
}

double CurveBicubic_Impl::maximumValueofy() const {
  const auto value = getDouble(openstudio::Curve_BicubicFields::MaximumValueofy, true);
  OS_ASSERT(value);
  return *value;
}

boost::optional<double> CurveBicubic_Impl::minimumCurveOutput() const {
  return getDouble(openstudio::Curve_BicubicFields::MinimumCurveOutput, true);
}

boost::optional<double> CurveBicubic_Impl::maximumCurveOutput() const {
  return getDouble(openstudio::Curve_BicubicFields::MaximumCurveOutput, true);
}

std::string CurveBicubic_Impl::inputUnitTypeforX() const {
  const auto value = getString(openstudio::Curve_BicubicFields::InputUnitTypeforX, true);
  OS_ASSERT(value);
  return *value;
}

bool CurveBicubic_Impl::isInputUnitTypeforXDefaulted() const {
  if (const auto value = getString(openstudio::Curve_BicubicFields::InputUnitTypeforX, false, true)) {
    if (const auto defaultValue = curveBicubicDefaultString(openstudio::Curve_BicubicFields::InputUnitTypeforX)) {
      return openstudio::istringEqual(*value, *defaultValue);
    }
    return false;
  }
  return true;
}

std::string CurveBicubic_Impl::inputUnitTypeforY() const {
  const auto value = getString(openstudio::Curve_BicubicFields::InputUnitTypeforY, true);
  OS_ASSERT(value);
  return *value;
}

bool CurveBicubic_Impl::isInputUnitTypeforYDefaulted() const {
  if (const auto value = getString(openstudio::Curve_BicubicFields::InputUnitTypeforY, false, true)) {
    if (const auto defaultValue = curveBicubicDefaultString(openstudio::Curve_BicubicFields::InputUnitTypeforY)) {
      return openstudio::istringEqual(*value, *defaultValue);
    }
    return false;
  }
  return true;
}

std::string CurveBicubic_Impl::outputUnitType() const {
  const auto value = getString(openstudio::Curve_BicubicFields::OutputUnitType, true);
  OS_ASSERT(value);
  return *value;
}

bool CurveBicubic_Impl::isOutputUnitTypeDefaulted() const {
  if (const auto value = getString(openstudio::Curve_BicubicFields::OutputUnitType, false, true)) {
    if (const auto defaultValue = curveBicubicDefaultString(openstudio::Curve_BicubicFields::OutputUnitType)) {
      return openstudio::istringEqual(*value, *defaultValue);
    }
    return false;
  }
  return true;
}

bool CurveBicubic_Impl::setCoefficient1Constant(double coefficient1Constant) {
  const bool result = setDouble(openstudio::Curve_BicubicFields::Coefficient1Constant, coefficient1Constant);
  OS_ASSERT(result);
  return result;
}

bool CurveBicubic_Impl::setCoefficient2x(double coefficient2x) {
  const bool result = setDouble(openstudio::Curve_BicubicFields::Coefficient2x, coefficient2x);
  OS_ASSERT(result);
  return result;
}

bool CurveBicubic_Impl::setCoefficient3xPOW2(double coefficient3xPOW2) {
  const bool result = setDouble(openstudio::Curve_BicubicFields::Coefficient3x_POW_2, coefficient3xPOW2);
  OS_ASSERT(result);
  return result;
}

bool CurveBicubic_Impl::setCoefficient4y(double coefficient4y) {
  const bool result = setDouble(openstudio::Curve_BicubicFields::Coefficient4y, coefficient4y);
  OS_ASSERT(result);
  return result;
}

bool CurveBicubic_Impl::setCoefficient5yPOW2(double coefficient5yPOW2) {
  const bool result = setDouble(openstudio::Curve_BicubicFields::Coefficient5y_POW_2, coefficient5yPOW2);
  OS_ASSERT(result);
  return result;
}

bool CurveBicubic_Impl::setCoefficient6xTIMESY(double coefficient6xTIMESY) {
  const bool result = setDouble(openstudio::Curve_BicubicFields::Coefficient6x_TIMES_y, coefficient6xTIMESY);
  OS_ASSERT(result);
  return result;
}

bool CurveBicubic_Impl::setCoefficient7xPOW3(double coefficient7xPOW3) {
  const bool result = setDouble(openstudio::Curve_BicubicFields::Coefficient7x_POW_3, coefficient7xPOW3);
  OS_ASSERT(result);
  return result;
}

bool CurveBicubic_Impl::setCoefficient8yPOW3(double coefficient8yPOW3) {
  const bool result = setDouble(openstudio::Curve_BicubicFields::Coefficient8y_POW_3, coefficient8yPOW3);
  OS_ASSERT(result);
  return result;
}

bool CurveBicubic_Impl::setCoefficient9xPOW2TIMESY(double coefficient9xPOW2TIMESY) {
  const bool result = setDouble(openstudio::Curve_BicubicFields::Coefficient9x_POW_2_TIMES_y, coefficient9xPOW2TIMESY);
  OS_ASSERT(result);
  return result;
}

bool CurveBicubic_Impl::setCoefficient10xTIMESYPOW2(double coefficient10xTIMESYPOW2) {
  const bool result = setDouble(openstudio::Curve_BicubicFields::Coefficient10x_TIMES_y_POW_2, coefficient10xTIMESYPOW2);
  OS_ASSERT(result);
  return result;
}

bool CurveBicubic_Impl::setMinimumValueofx(double minimumValueofx) {
  const bool result = setDouble(openstudio::Curve_BicubicFields::MinimumValueofx, minimumValueofx);
  OS_ASSERT(result);
  return result;
}

bool CurveBicubic_Impl::setMaximumValueofx(double maximumValueofx) {
  const bool result = setDouble(openstudio::Curve_BicubicFields::MaximumValueofx, maximumValueofx);
  OS_ASSERT(result);
  return result;
}

bool CurveBicubic_Impl::setMinimumValueofy(double minimumValueofy) {
  const bool result = setDouble(openstudio::Curve_BicubicFields::MinimumValueofy, minimumValueofy);
  OS_ASSERT(result);
  return result;
}

bool CurveBicubic_Impl::setMaximumValueofy(double maximumValueofy) {
  const bool result = setDouble(openstudio::Curve_BicubicFields::MaximumValueofy, maximumValueofy);
  OS_ASSERT(result);
  return result;
}

bool CurveBicubic_Impl::setMinimumCurveOutput(double minimumCurveOutput) {
  const bool result = setDouble(openstudio::Curve_BicubicFields::MinimumCurveOutput, minimumCurveOutput);
  OS_ASSERT(result);
  return result;
}

void CurveBicubic_Impl::resetMinimumCurveOutput() {
  OS_ASSERT(setString(openstudio::Curve_BicubicFields::MinimumCurveOutput, ""));
}

bool CurveBicubic_Impl::setMaximumCurveOutput(double maximumCurveOutput) {
  const bool result = setDouble(openstudio::Curve_BicubicFields::MaximumCurveOutput, maximumCurveOutput);
  OS_ASSERT(result);
  return result;
}

void CurveBicubic_Impl::resetMaximumCurveOutput() {
  OS_ASSERT(setString(openstudio::Curve_BicubicFields::MaximumCurveOutput, ""));
}

bool CurveBicubic_Impl::setInputUnitTypeforX(const std::string& inputUnitTypeforX) {
  return setString(openstudio::Curve_BicubicFields::InputUnitTypeforX, inputUnitTypeforX);
}

void CurveBicubic_Impl::resetInputUnitTypeforX() {
  bool result = false;
  if (const auto defaultValue = curveBicubicDefaultString(openstudio::Curve_BicubicFields::InputUnitTypeforX)) {
    result = setString(openstudio::Curve_BicubicFields::InputUnitTypeforX, *defaultValue);
  } else {
    result = setString(openstudio::Curve_BicubicFields::InputUnitTypeforX, "");
  }
  OS_ASSERT(result);
}

bool CurveBicubic_Impl::setInputUnitTypeforY(const std::string& inputUnitTypeforY) {
  return setString(openstudio::Curve_BicubicFields::InputUnitTypeforY, inputUnitTypeforY);
}

void CurveBicubic_Impl::resetInputUnitTypeforY() {
  bool result = false;
  if (const auto defaultValue = curveBicubicDefaultString(openstudio::Curve_BicubicFields::InputUnitTypeforY)) {
    result = setString(openstudio::Curve_BicubicFields::InputUnitTypeforY, *defaultValue);
  } else {
    result = setString(openstudio::Curve_BicubicFields::InputUnitTypeforY, "");
  }
  OS_ASSERT(result);
}

bool CurveBicubic_Impl::setOutputUnitType(const std::string& outputUnitType) {
  return setString(openstudio::Curve_BicubicFields::OutputUnitType, outputUnitType);
}

void CurveBicubic_Impl::resetOutputUnitType() {
  bool result = false;
  if (const auto defaultValue = curveBicubicDefaultString(openstudio::Curve_BicubicFields::OutputUnitType)) {
    result = setString(openstudio::Curve_BicubicFields::OutputUnitType, *defaultValue);
  } else {
    result = setString(openstudio::Curve_BicubicFields::OutputUnitType, "");
  }
  OS_ASSERT(result);
}

std::vector<std::string> CurveBicubic_Impl::validInputUnitTypeforXValues() const {
  return openstudio::epmodel::CurveBicubic::validInputUnitTypeforXValues();
}

std::vector<std::string> CurveBicubic_Impl::validInputUnitTypeforYValues() const {
  return openstudio::epmodel::CurveBicubic::validInputUnitTypeforYValues();
}

std::vector<std::string> CurveBicubic_Impl::validOutputUnitTypeValues() const {
  return openstudio::epmodel::CurveBicubic::validOutputUnitTypeValues();
}

}  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
