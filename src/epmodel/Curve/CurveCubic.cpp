/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "Curve/CurveCubic.hpp"
#include "Curve/CurveCubic_Impl.hpp"

#include "Model.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/core/StringHelpers.hpp>
#include <utilities/idd/Curve_Cubic_FieldEnums.hxx>
#include <utilities/idd/IddEnums.hxx>
#include <utilities/idd/IddFactory.hxx>

namespace openstudio {
namespace epmodel {

namespace {

boost::optional<std::string> curveCubicDefaultString(unsigned fieldIndex) {
  const auto iddObject = IddFactory::instance().getObject(IddObjectType::Curve_Cubic);
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

CurveCubic::CurveCubic(const Model& model) : ModelObject(CurveCubic::iddObjectType(), model) {
  OS_ASSERT(getImpl<detail::CurveCubic_Impl>());
  OS_ASSERT(setCoefficient1Constant(0.0));
  OS_ASSERT(setCoefficient2x(0.0));
  OS_ASSERT(setCoefficient3xPOW2(0.0));
  OS_ASSERT(setCoefficient4xPOW3(1.0));
  OS_ASSERT(setMinimumValueofx(0.0));
  OS_ASSERT(setMaximumValueofx(1.0));
}

CurveCubic::CurveCubic(std::shared_ptr<detail::CurveCubic_Impl> impl) : ModelObject(std::move(impl)) {}

IddObjectType CurveCubic::iddObjectType() {
  return IddObjectType::Curve_Cubic;
}

std::vector<std::string> CurveCubic::validInputUnitTypeforXValues() {
  return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(), openstudio::Curve_CubicFields::InputUnitTypeforX);
}

std::vector<std::string> CurveCubic::validOutputUnitTypeValues() {
  return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(), openstudio::Curve_CubicFields::OutputUnitType);
}

double CurveCubic::coefficient1Constant() const {
  return getImpl<detail::CurveCubic_Impl>()->coefficient1Constant();
}

bool CurveCubic::setCoefficient1Constant(double coefficient1Constant) {
  return getImpl<detail::CurveCubic_Impl>()->setCoefficient1Constant(coefficient1Constant);
}

double CurveCubic::coefficient2x() const {
  return getImpl<detail::CurveCubic_Impl>()->coefficient2x();
}

bool CurveCubic::setCoefficient2x(double coefficient2x) {
  return getImpl<detail::CurveCubic_Impl>()->setCoefficient2x(coefficient2x);
}

double CurveCubic::coefficient3xPOW2() const {
  return getImpl<detail::CurveCubic_Impl>()->coefficient3xPOW2();
}

bool CurveCubic::setCoefficient3xPOW2(double coefficient3xPOW2) {
  return getImpl<detail::CurveCubic_Impl>()->setCoefficient3xPOW2(coefficient3xPOW2);
}

double CurveCubic::coefficient4xPOW3() const {
  return getImpl<detail::CurveCubic_Impl>()->coefficient4xPOW3();
}

bool CurveCubic::setCoefficient4xPOW3(double coefficient4xPOW3) {
  return getImpl<detail::CurveCubic_Impl>()->setCoefficient4xPOW3(coefficient4xPOW3);
}

double CurveCubic::minimumValueofx() const {
  return getImpl<detail::CurveCubic_Impl>()->minimumValueofx();
}

bool CurveCubic::setMinimumValueofx(double minimumValueofx) {
  return getImpl<detail::CurveCubic_Impl>()->setMinimumValueofx(minimumValueofx);
}

double CurveCubic::maximumValueofx() const {
  return getImpl<detail::CurveCubic_Impl>()->maximumValueofx();
}

bool CurveCubic::setMaximumValueofx(double maximumValueofx) {
  return getImpl<detail::CurveCubic_Impl>()->setMaximumValueofx(maximumValueofx);
}

boost::optional<double> CurveCubic::minimumCurveOutput() const {
  return getImpl<detail::CurveCubic_Impl>()->minimumCurveOutput();
}

bool CurveCubic::setMinimumCurveOutput(double minimumCurveOutput) {
  return getImpl<detail::CurveCubic_Impl>()->setMinimumCurveOutput(minimumCurveOutput);
}

void CurveCubic::resetMinimumCurveOutput() {
  getImpl<detail::CurveCubic_Impl>()->resetMinimumCurveOutput();
}

boost::optional<double> CurveCubic::maximumCurveOutput() const {
  return getImpl<detail::CurveCubic_Impl>()->maximumCurveOutput();
}

bool CurveCubic::setMaximumCurveOutput(double maximumCurveOutput) {
  return getImpl<detail::CurveCubic_Impl>()->setMaximumCurveOutput(maximumCurveOutput);
}

void CurveCubic::resetMaximumCurveOutput() {
  getImpl<detail::CurveCubic_Impl>()->resetMaximumCurveOutput();
}

std::string CurveCubic::inputUnitTypeforX() const {
  return getImpl<detail::CurveCubic_Impl>()->inputUnitTypeforX();
}

bool CurveCubic::isInputUnitTypeforXDefaulted() const {
  return getImpl<detail::CurveCubic_Impl>()->isInputUnitTypeforXDefaulted();
}

bool CurveCubic::setInputUnitTypeforX(const std::string& inputUnitTypeforX) {
  return getImpl<detail::CurveCubic_Impl>()->setInputUnitTypeforX(inputUnitTypeforX);
}

void CurveCubic::resetInputUnitTypeforX() {
  getImpl<detail::CurveCubic_Impl>()->resetInputUnitTypeforX();
}

std::string CurveCubic::outputUnitType() const {
  return getImpl<detail::CurveCubic_Impl>()->outputUnitType();
}

bool CurveCubic::isOutputUnitTypeDefaulted() const {
  return getImpl<detail::CurveCubic_Impl>()->isOutputUnitTypeDefaulted();
}

bool CurveCubic::setOutputUnitType(const std::string& outputUnitType) {
  return getImpl<detail::CurveCubic_Impl>()->setOutputUnitType(outputUnitType);
}

void CurveCubic::resetOutputUnitType() {
  getImpl<detail::CurveCubic_Impl>()->resetOutputUnitType();
}

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
namespace detail {

double CurveCubic_Impl::coefficient1Constant() const {
  const auto value = getDouble(openstudio::Curve_CubicFields::Coefficient1Constant, true);
  OS_ASSERT(value);
  return *value;
}

bool CurveCubic_Impl::setCoefficient1Constant(double coefficient1Constant) {
  const bool result = setDouble(openstudio::Curve_CubicFields::Coefficient1Constant, coefficient1Constant);
  OS_ASSERT(result);
  return result;
}

double CurveCubic_Impl::coefficient2x() const {
  const auto value = getDouble(openstudio::Curve_CubicFields::Coefficient2x, true);
  OS_ASSERT(value);
  return *value;
}

bool CurveCubic_Impl::setCoefficient2x(double coefficient2x) {
  const bool result = setDouble(openstudio::Curve_CubicFields::Coefficient2x, coefficient2x);
  OS_ASSERT(result);
  return result;
}

double CurveCubic_Impl::coefficient3xPOW2() const {
  const auto value = getDouble(openstudio::Curve_CubicFields::Coefficient3x_POW_2, true);
  OS_ASSERT(value);
  return *value;
}

bool CurveCubic_Impl::setCoefficient3xPOW2(double coefficient3xPOW2) {
  const bool result = setDouble(openstudio::Curve_CubicFields::Coefficient3x_POW_2, coefficient3xPOW2);
  OS_ASSERT(result);
  return result;
}

double CurveCubic_Impl::coefficient4xPOW3() const {
  const auto value = getDouble(openstudio::Curve_CubicFields::Coefficient4x_POW_3, true);
  OS_ASSERT(value);
  return *value;
}

bool CurveCubic_Impl::setCoefficient4xPOW3(double coefficient4xPOW3) {
  const bool result = setDouble(openstudio::Curve_CubicFields::Coefficient4x_POW_3, coefficient4xPOW3);
  OS_ASSERT(result);
  return result;
}

double CurveCubic_Impl::minimumValueofx() const {
  const auto value = getDouble(openstudio::Curve_CubicFields::MinimumValueofx, true);
  OS_ASSERT(value);
  return *value;
}

bool CurveCubic_Impl::setMinimumValueofx(double minimumValueofx) {
  const bool result = setDouble(openstudio::Curve_CubicFields::MinimumValueofx, minimumValueofx);
  OS_ASSERT(result);
  return result;
}

double CurveCubic_Impl::maximumValueofx() const {
  const auto value = getDouble(openstudio::Curve_CubicFields::MaximumValueofx, true);
  OS_ASSERT(value);
  return *value;
}

bool CurveCubic_Impl::setMaximumValueofx(double maximumValueofx) {
  const bool result = setDouble(openstudio::Curve_CubicFields::MaximumValueofx, maximumValueofx);
  OS_ASSERT(result);
  return result;
}

boost::optional<double> CurveCubic_Impl::minimumCurveOutput() const {
  return getDouble(openstudio::Curve_CubicFields::MinimumCurveOutput, true);
}

bool CurveCubic_Impl::setMinimumCurveOutput(double minimumCurveOutput) {
  const bool result = setDouble(openstudio::Curve_CubicFields::MinimumCurveOutput, minimumCurveOutput);
  OS_ASSERT(result);
  return result;
}

void CurveCubic_Impl::resetMinimumCurveOutput() {
  OS_ASSERT(setString(openstudio::Curve_CubicFields::MinimumCurveOutput, ""));
}

boost::optional<double> CurveCubic_Impl::maximumCurveOutput() const {
  return getDouble(openstudio::Curve_CubicFields::MaximumCurveOutput, true);
}

bool CurveCubic_Impl::setMaximumCurveOutput(double maximumCurveOutput) {
  const bool result = setDouble(openstudio::Curve_CubicFields::MaximumCurveOutput, maximumCurveOutput);
  OS_ASSERT(result);
  return result;
}

void CurveCubic_Impl::resetMaximumCurveOutput() {
  OS_ASSERT(setString(openstudio::Curve_CubicFields::MaximumCurveOutput, ""));
}

std::string CurveCubic_Impl::inputUnitTypeforX() const {
  const auto value = getString(openstudio::Curve_CubicFields::InputUnitTypeforX, true);
  OS_ASSERT(value);
  return *value;
}

bool CurveCubic_Impl::isInputUnitTypeforXDefaulted() const {
  if (const auto value = getString(openstudio::Curve_CubicFields::InputUnitTypeforX, false, true)) {
    if (const auto defaultValue = curveCubicDefaultString(openstudio::Curve_CubicFields::InputUnitTypeforX)) {
      return openstudio::istringEqual(*value, *defaultValue);
    }
    return false;
  }
  return true;
}

bool CurveCubic_Impl::setInputUnitTypeforX(const std::string& inputUnitTypeforX) {
  return setString(openstudio::Curve_CubicFields::InputUnitTypeforX, inputUnitTypeforX);
}

void CurveCubic_Impl::resetInputUnitTypeforX() {
  bool result = false;
  if (const auto defaultValue = curveCubicDefaultString(openstudio::Curve_CubicFields::InputUnitTypeforX)) {
    result = setString(openstudio::Curve_CubicFields::InputUnitTypeforX, *defaultValue);
  } else {
    result = setString(openstudio::Curve_CubicFields::InputUnitTypeforX, "");
  }
  OS_ASSERT(result);
}

std::string CurveCubic_Impl::outputUnitType() const {
  const auto value = getString(openstudio::Curve_CubicFields::OutputUnitType, true);
  OS_ASSERT(value);
  return *value;
}

bool CurveCubic_Impl::isOutputUnitTypeDefaulted() const {
  if (const auto value = getString(openstudio::Curve_CubicFields::OutputUnitType, false, true)) {
    if (const auto defaultValue = curveCubicDefaultString(openstudio::Curve_CubicFields::OutputUnitType)) {
      return openstudio::istringEqual(*value, *defaultValue);
    }
    return false;
  }
  return true;
}

bool CurveCubic_Impl::setOutputUnitType(const std::string& outputUnitType) {
  return setString(openstudio::Curve_CubicFields::OutputUnitType, outputUnitType);
}

void CurveCubic_Impl::resetOutputUnitType() {
  bool result = false;
  if (const auto defaultValue = curveCubicDefaultString(openstudio::Curve_CubicFields::OutputUnitType)) {
    result = setString(openstudio::Curve_CubicFields::OutputUnitType, *defaultValue);
  } else {
    result = setString(openstudio::Curve_CubicFields::OutputUnitType, "");
  }
  OS_ASSERT(result);
}

std::vector<std::string> CurveCubic_Impl::validInputUnitTypeforXValues() const {
  return openstudio::epmodel::CurveCubic::validInputUnitTypeforXValues();
}

std::vector<std::string> CurveCubic_Impl::validOutputUnitTypeValues() const {
  return openstudio::epmodel::CurveCubic::validOutputUnitTypeValues();
}

}  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
