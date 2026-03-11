/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "Curve/CurveQuadraticLinear.hpp"
#include "Curve/CurveQuadraticLinear_Impl.hpp"

#include "Model.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/idd/Curve_QuadraticLinear_FieldEnums.hxx>
#include <utilities/idd/IddEnums.hxx>
#include <utilities/idd/IddFactory.hxx>

namespace openstudio {
namespace epmodel {

CurveQuadraticLinear::CurveQuadraticLinear(const Model& model) : ModelObject(CurveQuadraticLinear::iddObjectType(), model) {
  OS_ASSERT(getImpl<detail::CurveQuadraticLinear_Impl>());
  OS_ASSERT(setCoefficient1Constant(0.0));
  OS_ASSERT(setCoefficient2x(0.0));
  OS_ASSERT(setCoefficient3xPOW2(0.0));
  OS_ASSERT(setCoefficient4y(0.0));
  OS_ASSERT(setCoefficient5xTIMESY(0.0));
  OS_ASSERT(setCoefficient6xPOW2TIMESY(1.0));
  OS_ASSERT(setMinimumValueofx(0.0));
  OS_ASSERT(setMaximumValueofx(1.0));
  OS_ASSERT(setMinimumValueofy(0.0));
  OS_ASSERT(setMaximumValueofy(1.0));
  resetMinimumCurveOutput();
  resetMaximumCurveOutput();
  resetInputUnitTypeforX();
  resetInputUnitTypeforY();
  resetOutputUnitType();
}

CurveQuadraticLinear::CurveQuadraticLinear(std::shared_ptr<detail::CurveQuadraticLinear_Impl> impl) : ModelObject(std::move(impl)) {}

IddObjectType CurveQuadraticLinear::iddObjectType() {
  return IddObjectType::Curve_QuadraticLinear;
}

std::vector<std::string> CurveQuadraticLinear::validInputUnitTypeforXValues() {
  return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(), openstudio::Curve_QuadraticLinearFields::InputUnitTypeforX);
}

std::vector<std::string> CurveQuadraticLinear::validInputUnitTypeforYValues() {
  return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(), openstudio::Curve_QuadraticLinearFields::InputUnitTypeforY);
}

std::vector<std::string> CurveQuadraticLinear::validOutputUnitTypeValues() {
  return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(), openstudio::Curve_QuadraticLinearFields::OutputUnitType);
}

double CurveQuadraticLinear::coefficient1Constant() const {
  return getImpl<detail::CurveQuadraticLinear_Impl>()->coefficient1Constant();
}

double CurveQuadraticLinear::coefficient2x() const {
  return getImpl<detail::CurveQuadraticLinear_Impl>()->coefficient2x();
}

double CurveQuadraticLinear::coefficient3xPOW2() const {
  return getImpl<detail::CurveQuadraticLinear_Impl>()->coefficient3xPOW2();
}

double CurveQuadraticLinear::coefficient4y() const {
  return getImpl<detail::CurveQuadraticLinear_Impl>()->coefficient4y();
}

double CurveQuadraticLinear::coefficient5xTIMESY() const {
  return getImpl<detail::CurveQuadraticLinear_Impl>()->coefficient5xTIMESY();
}

double CurveQuadraticLinear::coefficient6xPOW2TIMESY() const {
  return getImpl<detail::CurveQuadraticLinear_Impl>()->coefficient6xPOW2TIMESY();
}

double CurveQuadraticLinear::minimumValueofx() const {
  return getImpl<detail::CurveQuadraticLinear_Impl>()->minimumValueofx();
}

double CurveQuadraticLinear::maximumValueofx() const {
  return getImpl<detail::CurveQuadraticLinear_Impl>()->maximumValueofx();
}

double CurveQuadraticLinear::minimumValueofy() const {
  return getImpl<detail::CurveQuadraticLinear_Impl>()->minimumValueofy();
}

double CurveQuadraticLinear::maximumValueofy() const {
  return getImpl<detail::CurveQuadraticLinear_Impl>()->maximumValueofy();
}

boost::optional<double> CurveQuadraticLinear::minimumCurveOutput() const {
  return getImpl<detail::CurveQuadraticLinear_Impl>()->minimumCurveOutput();
}

boost::optional<double> CurveQuadraticLinear::maximumCurveOutput() const {
  return getImpl<detail::CurveQuadraticLinear_Impl>()->maximumCurveOutput();
}

std::string CurveQuadraticLinear::inputUnitTypeforX() const {
  return getImpl<detail::CurveQuadraticLinear_Impl>()->inputUnitTypeforX();
}

bool CurveQuadraticLinear::isInputUnitTypeforXDefaulted() const {
  return getImpl<detail::CurveQuadraticLinear_Impl>()->isInputUnitTypeforXDefaulted();
}

std::string CurveQuadraticLinear::inputUnitTypeforY() const {
  return getImpl<detail::CurveQuadraticLinear_Impl>()->inputUnitTypeforY();
}

bool CurveQuadraticLinear::isInputUnitTypeforYDefaulted() const {
  return getImpl<detail::CurveQuadraticLinear_Impl>()->isInputUnitTypeforYDefaulted();
}

std::string CurveQuadraticLinear::outputUnitType() const {
  return getImpl<detail::CurveQuadraticLinear_Impl>()->outputUnitType();
}

bool CurveQuadraticLinear::isOutputUnitTypeDefaulted() const {
  return getImpl<detail::CurveQuadraticLinear_Impl>()->isOutputUnitTypeDefaulted();
}

bool CurveQuadraticLinear::setCoefficient1Constant(double coefficient1Constant) {
  return getImpl<detail::CurveQuadraticLinear_Impl>()->setCoefficient1Constant(coefficient1Constant);
}

bool CurveQuadraticLinear::setCoefficient2x(double coefficient2x) {
  return getImpl<detail::CurveQuadraticLinear_Impl>()->setCoefficient2x(coefficient2x);
}

bool CurveQuadraticLinear::setCoefficient3xPOW2(double coefficient3xPOW2) {
  return getImpl<detail::CurveQuadraticLinear_Impl>()->setCoefficient3xPOW2(coefficient3xPOW2);
}

bool CurveQuadraticLinear::setCoefficient4y(double coefficient4y) {
  return getImpl<detail::CurveQuadraticLinear_Impl>()->setCoefficient4y(coefficient4y);
}

bool CurveQuadraticLinear::setCoefficient5xTIMESY(double coefficient5xTIMESY) {
  return getImpl<detail::CurveQuadraticLinear_Impl>()->setCoefficient5xTIMESY(coefficient5xTIMESY);
}

bool CurveQuadraticLinear::setCoefficient6xPOW2TIMESY(double coefficient6xPOW2TIMESY) {
  return getImpl<detail::CurveQuadraticLinear_Impl>()->setCoefficient6xPOW2TIMESY(coefficient6xPOW2TIMESY);
}

bool CurveQuadraticLinear::setMinimumValueofx(double minimumValueofx) {
  return getImpl<detail::CurveQuadraticLinear_Impl>()->setMinimumValueofx(minimumValueofx);
}

bool CurveQuadraticLinear::setMaximumValueofx(double maximumValueofx) {
  return getImpl<detail::CurveQuadraticLinear_Impl>()->setMaximumValueofx(maximumValueofx);
}

bool CurveQuadraticLinear::setMinimumValueofy(double minimumValueofy) {
  return getImpl<detail::CurveQuadraticLinear_Impl>()->setMinimumValueofy(minimumValueofy);
}

bool CurveQuadraticLinear::setMaximumValueofy(double maximumValueofy) {
  return getImpl<detail::CurveQuadraticLinear_Impl>()->setMaximumValueofy(maximumValueofy);
}

bool CurveQuadraticLinear::setMinimumCurveOutput(double minimumCurveOutput) {
  return getImpl<detail::CurveQuadraticLinear_Impl>()->setMinimumCurveOutput(minimumCurveOutput);
}

void CurveQuadraticLinear::resetMinimumCurveOutput() {
  getImpl<detail::CurveQuadraticLinear_Impl>()->resetMinimumCurveOutput();
}

bool CurveQuadraticLinear::setMaximumCurveOutput(double maximumCurveOutput) {
  return getImpl<detail::CurveQuadraticLinear_Impl>()->setMaximumCurveOutput(maximumCurveOutput);
}

void CurveQuadraticLinear::resetMaximumCurveOutput() {
  getImpl<detail::CurveQuadraticLinear_Impl>()->resetMaximumCurveOutput();
}

bool CurveQuadraticLinear::setInputUnitTypeforX(const std::string& inputUnitTypeforX) {
  return getImpl<detail::CurveQuadraticLinear_Impl>()->setInputUnitTypeforX(inputUnitTypeforX);
}

void CurveQuadraticLinear::resetInputUnitTypeforX() {
  getImpl<detail::CurveQuadraticLinear_Impl>()->resetInputUnitTypeforX();
}

bool CurveQuadraticLinear::setInputUnitTypeforY(const std::string& inputUnitTypeforY) {
  return getImpl<detail::CurveQuadraticLinear_Impl>()->setInputUnitTypeforY(inputUnitTypeforY);
}

void CurveQuadraticLinear::resetInputUnitTypeforY() {
  getImpl<detail::CurveQuadraticLinear_Impl>()->resetInputUnitTypeforY();
}

bool CurveQuadraticLinear::setOutputUnitType(const std::string& outputUnitType) {
  return getImpl<detail::CurveQuadraticLinear_Impl>()->setOutputUnitType(outputUnitType);
}

void CurveQuadraticLinear::resetOutputUnitType() {
  getImpl<detail::CurveQuadraticLinear_Impl>()->resetOutputUnitType();
}

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
namespace detail {

double CurveQuadraticLinear_Impl::coefficient1Constant() const {
  const auto value = getDouble(openstudio::Curve_QuadraticLinearFields::Coefficient1Constant, true);
  OS_ASSERT(value);
  return *value;
}

double CurveQuadraticLinear_Impl::coefficient2x() const {
  const auto value = getDouble(openstudio::Curve_QuadraticLinearFields::Coefficient2x, true);
  OS_ASSERT(value);
  return *value;
}

double CurveQuadraticLinear_Impl::coefficient3xPOW2() const {
  const auto value = getDouble(openstudio::Curve_QuadraticLinearFields::Coefficient3x_POW_2, true);
  OS_ASSERT(value);
  return *value;
}

double CurveQuadraticLinear_Impl::coefficient4y() const {
  const auto value = getDouble(openstudio::Curve_QuadraticLinearFields::Coefficient4y, true);
  OS_ASSERT(value);
  return *value;
}

double CurveQuadraticLinear_Impl::coefficient5xTIMESY() const {
  const auto value = getDouble(openstudio::Curve_QuadraticLinearFields::Coefficient5x_TIMES_y, true);
  OS_ASSERT(value);
  return *value;
}

double CurveQuadraticLinear_Impl::coefficient6xPOW2TIMESY() const {
  const auto value = getDouble(openstudio::Curve_QuadraticLinearFields::Coefficient6x_POW_2_TIMES_y, true);
  OS_ASSERT(value);
  return *value;
}

double CurveQuadraticLinear_Impl::minimumValueofx() const {
  const auto value = getDouble(openstudio::Curve_QuadraticLinearFields::MinimumValueofx, true);
  OS_ASSERT(value);
  return *value;
}

double CurveQuadraticLinear_Impl::maximumValueofx() const {
  const auto value = getDouble(openstudio::Curve_QuadraticLinearFields::MaximumValueofx, true);
  OS_ASSERT(value);
  return *value;
}

double CurveQuadraticLinear_Impl::minimumValueofy() const {
  const auto value = getDouble(openstudio::Curve_QuadraticLinearFields::MinimumValueofy, true);
  OS_ASSERT(value);
  return *value;
}

double CurveQuadraticLinear_Impl::maximumValueofy() const {
  const auto value = getDouble(openstudio::Curve_QuadraticLinearFields::MaximumValueofy, true);
  OS_ASSERT(value);
  return *value;
}

boost::optional<double> CurveQuadraticLinear_Impl::minimumCurveOutput() const {
  return getDouble(openstudio::Curve_QuadraticLinearFields::MinimumCurveOutput, true);
}

boost::optional<double> CurveQuadraticLinear_Impl::maximumCurveOutput() const {
  return getDouble(openstudio::Curve_QuadraticLinearFields::MaximumCurveOutput, true);
}

std::string CurveQuadraticLinear_Impl::inputUnitTypeforX() const {
  const auto value = getString(openstudio::Curve_QuadraticLinearFields::InputUnitTypeforX, true);
  OS_ASSERT(value);
  return *value;
}

bool CurveQuadraticLinear_Impl::isInputUnitTypeforXDefaulted() const {
  return isEmpty(openstudio::Curve_QuadraticLinearFields::InputUnitTypeforX);
}

std::string CurveQuadraticLinear_Impl::inputUnitTypeforY() const {
  const auto value = getString(openstudio::Curve_QuadraticLinearFields::InputUnitTypeforY, true);
  OS_ASSERT(value);
  return *value;
}

bool CurveQuadraticLinear_Impl::isInputUnitTypeforYDefaulted() const {
  return isEmpty(openstudio::Curve_QuadraticLinearFields::InputUnitTypeforY);
}

std::string CurveQuadraticLinear_Impl::outputUnitType() const {
  const auto value = getString(openstudio::Curve_QuadraticLinearFields::OutputUnitType, true);
  OS_ASSERT(value);
  return *value;
}

bool CurveQuadraticLinear_Impl::isOutputUnitTypeDefaulted() const {
  return isEmpty(openstudio::Curve_QuadraticLinearFields::OutputUnitType);
}

bool CurveQuadraticLinear_Impl::setCoefficient1Constant(double coefficient1Constant) {
  const bool result = setDouble(openstudio::Curve_QuadraticLinearFields::Coefficient1Constant, coefficient1Constant);
  OS_ASSERT(result);
  return result;
}

bool CurveQuadraticLinear_Impl::setCoefficient2x(double coefficient2x) {
  const bool result = setDouble(openstudio::Curve_QuadraticLinearFields::Coefficient2x, coefficient2x);
  OS_ASSERT(result);
  return result;
}

bool CurveQuadraticLinear_Impl::setCoefficient3xPOW2(double coefficient3xPOW2) {
  const bool result = setDouble(openstudio::Curve_QuadraticLinearFields::Coefficient3x_POW_2, coefficient3xPOW2);
  OS_ASSERT(result);
  return result;
}

bool CurveQuadraticLinear_Impl::setCoefficient4y(double coefficient4y) {
  const bool result = setDouble(openstudio::Curve_QuadraticLinearFields::Coefficient4y, coefficient4y);
  OS_ASSERT(result);
  return result;
}

bool CurveQuadraticLinear_Impl::setCoefficient5xTIMESY(double coefficient5xTIMESY) {
  const bool result = setDouble(openstudio::Curve_QuadraticLinearFields::Coefficient5x_TIMES_y, coefficient5xTIMESY);
  OS_ASSERT(result);
  return result;
}

bool CurveQuadraticLinear_Impl::setCoefficient6xPOW2TIMESY(double coefficient6xPOW2TIMESY) {
  const bool result = setDouble(openstudio::Curve_QuadraticLinearFields::Coefficient6x_POW_2_TIMES_y, coefficient6xPOW2TIMESY);
  OS_ASSERT(result);
  return result;
}

bool CurveQuadraticLinear_Impl::setMinimumValueofx(double minimumValueofx) {
  const bool result = setDouble(openstudio::Curve_QuadraticLinearFields::MinimumValueofx, minimumValueofx);
  OS_ASSERT(result);
  return result;
}

bool CurveQuadraticLinear_Impl::setMaximumValueofx(double maximumValueofx) {
  const bool result = setDouble(openstudio::Curve_QuadraticLinearFields::MaximumValueofx, maximumValueofx);
  OS_ASSERT(result);
  return result;
}

bool CurveQuadraticLinear_Impl::setMinimumValueofy(double minimumValueofy) {
  const bool result = setDouble(openstudio::Curve_QuadraticLinearFields::MinimumValueofy, minimumValueofy);
  OS_ASSERT(result);
  return result;
}

bool CurveQuadraticLinear_Impl::setMaximumValueofy(double maximumValueofy) {
  const bool result = setDouble(openstudio::Curve_QuadraticLinearFields::MaximumValueofy, maximumValueofy);
  OS_ASSERT(result);
  return result;
}

bool CurveQuadraticLinear_Impl::setMinimumCurveOutput(double minimumCurveOutput) {
  const bool result = setDouble(openstudio::Curve_QuadraticLinearFields::MinimumCurveOutput, minimumCurveOutput);
  OS_ASSERT(result);
  return result;
}

void CurveQuadraticLinear_Impl::resetMinimumCurveOutput() {
  OS_ASSERT(setString(openstudio::Curve_QuadraticLinearFields::MinimumCurveOutput, ""));
}

bool CurveQuadraticLinear_Impl::setMaximumCurveOutput(double maximumCurveOutput) {
  const bool result = setDouble(openstudio::Curve_QuadraticLinearFields::MaximumCurveOutput, maximumCurveOutput);
  OS_ASSERT(result);
  return result;
}

void CurveQuadraticLinear_Impl::resetMaximumCurveOutput() {
  OS_ASSERT(setString(openstudio::Curve_QuadraticLinearFields::MaximumCurveOutput, ""));
}

bool CurveQuadraticLinear_Impl::setInputUnitTypeforX(const std::string& inputUnitTypeforX) {
  return setString(openstudio::Curve_QuadraticLinearFields::InputUnitTypeforX, inputUnitTypeforX);
}

void CurveQuadraticLinear_Impl::resetInputUnitTypeforX() {
  OS_ASSERT(setString(openstudio::Curve_QuadraticLinearFields::InputUnitTypeforX, ""));
}

bool CurveQuadraticLinear_Impl::setInputUnitTypeforY(const std::string& inputUnitTypeforY) {
  return setString(openstudio::Curve_QuadraticLinearFields::InputUnitTypeforY, inputUnitTypeforY);
}

void CurveQuadraticLinear_Impl::resetInputUnitTypeforY() {
  OS_ASSERT(setString(openstudio::Curve_QuadraticLinearFields::InputUnitTypeforY, ""));
}

bool CurveQuadraticLinear_Impl::setOutputUnitType(const std::string& outputUnitType) {
  return setString(openstudio::Curve_QuadraticLinearFields::OutputUnitType, outputUnitType);
}

void CurveQuadraticLinear_Impl::resetOutputUnitType() {
  OS_ASSERT(setString(openstudio::Curve_QuadraticLinearFields::OutputUnitType, ""));
}

std::vector<std::string> CurveQuadraticLinear_Impl::validInputUnitTypeforXValues() const {
  return openstudio::epmodel::CurveQuadraticLinear::validInputUnitTypeforXValues();
}

std::vector<std::string> CurveQuadraticLinear_Impl::validInputUnitTypeforYValues() const {
  return openstudio::epmodel::CurveQuadraticLinear::validInputUnitTypeforYValues();
}

std::vector<std::string> CurveQuadraticLinear_Impl::validOutputUnitTypeValues() const {
  return openstudio::epmodel::CurveQuadraticLinear::validOutputUnitTypeValues();
}

}  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
