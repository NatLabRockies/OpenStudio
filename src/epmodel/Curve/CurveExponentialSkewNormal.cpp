/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "Curve/CurveExponentialSkewNormal.hpp"
#include "Curve/CurveExponentialSkewNormal_Impl.hpp"

#include "Model.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/idd/Curve_ExponentialSkewNormal_FieldEnums.hxx>
#include <utilities/idd/IddEnums.hxx>
#include <utilities/idd/IddFactory.hxx>

namespace openstudio {
namespace epmodel {

CurveExponentialSkewNormal::CurveExponentialSkewNormal(const Model& model) : ModelObject(CurveExponentialSkewNormal::iddObjectType(), model) {
  OS_ASSERT(getImpl<detail::CurveExponentialSkewNormal_Impl>());
  OS_ASSERT(setCoefficient1C1(1.0));
  OS_ASSERT(setCoefficient2C2(1.0));
  OS_ASSERT(setCoefficient3C3(-1.0));
  OS_ASSERT(setCoefficient4C4(1.0));
  OS_ASSERT(setMinimumValueofx(-1.0));
  OS_ASSERT(setMaximumValueofx(1.0));
  resetMinimumCurveOutput();
  resetMaximumCurveOutput();
  resetInputUnitTypeforx();
  resetOutputUnitType();
}

CurveExponentialSkewNormal::CurveExponentialSkewNormal(std::shared_ptr<detail::CurveExponentialSkewNormal_Impl> impl)
  : ModelObject(std::move(impl)) {}

IddObjectType CurveExponentialSkewNormal::iddObjectType() {
  return IddObjectType::Curve_ExponentialSkewNormal;
}

std::vector<std::string> CurveExponentialSkewNormal::validInputUnitTypeforxValues() {
  return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(), openstudio::Curve_ExponentialSkewNormalFields::InputUnitTypeforx);
}

std::vector<std::string> CurveExponentialSkewNormal::validOutputUnitTypeValues() {
  return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(), openstudio::Curve_ExponentialSkewNormalFields::OutputUnitType);
}

double CurveExponentialSkewNormal::coefficient1C1() const {
  return getImpl<detail::CurveExponentialSkewNormal_Impl>()->coefficient1C1();
}

double CurveExponentialSkewNormal::coefficient2C2() const {
  return getImpl<detail::CurveExponentialSkewNormal_Impl>()->coefficient2C2();
}

double CurveExponentialSkewNormal::coefficient3C3() const {
  return getImpl<detail::CurveExponentialSkewNormal_Impl>()->coefficient3C3();
}

double CurveExponentialSkewNormal::coefficient4C4() const {
  return getImpl<detail::CurveExponentialSkewNormal_Impl>()->coefficient4C4();
}

double CurveExponentialSkewNormal::minimumValueofx() const {
  return getImpl<detail::CurveExponentialSkewNormal_Impl>()->minimumValueofx();
}

double CurveExponentialSkewNormal::maximumValueofx() const {
  return getImpl<detail::CurveExponentialSkewNormal_Impl>()->maximumValueofx();
}

boost::optional<double> CurveExponentialSkewNormal::minimumCurveOutput() const {
  return getImpl<detail::CurveExponentialSkewNormal_Impl>()->minimumCurveOutput();
}

boost::optional<double> CurveExponentialSkewNormal::maximumCurveOutput() const {
  return getImpl<detail::CurveExponentialSkewNormal_Impl>()->maximumCurveOutput();
}

std::string CurveExponentialSkewNormal::inputUnitTypeforx() const {
  return getImpl<detail::CurveExponentialSkewNormal_Impl>()->inputUnitTypeforx();
}

bool CurveExponentialSkewNormal::isInputUnitTypeforxDefaulted() const {
  return getImpl<detail::CurveExponentialSkewNormal_Impl>()->isInputUnitTypeforxDefaulted();
}

std::string CurveExponentialSkewNormal::outputUnitType() const {
  return getImpl<detail::CurveExponentialSkewNormal_Impl>()->outputUnitType();
}

bool CurveExponentialSkewNormal::isOutputUnitTypeDefaulted() const {
  return getImpl<detail::CurveExponentialSkewNormal_Impl>()->isOutputUnitTypeDefaulted();
}

bool CurveExponentialSkewNormal::setCoefficient1C1(double coefficient1C1) {
  return getImpl<detail::CurveExponentialSkewNormal_Impl>()->setCoefficient1C1(coefficient1C1);
}

bool CurveExponentialSkewNormal::setCoefficient2C2(double coefficient2C2) {
  return getImpl<detail::CurveExponentialSkewNormal_Impl>()->setCoefficient2C2(coefficient2C2);
}

bool CurveExponentialSkewNormal::setCoefficient3C3(double coefficient3C3) {
  return getImpl<detail::CurveExponentialSkewNormal_Impl>()->setCoefficient3C3(coefficient3C3);
}

bool CurveExponentialSkewNormal::setCoefficient4C4(double coefficient4C4) {
  return getImpl<detail::CurveExponentialSkewNormal_Impl>()->setCoefficient4C4(coefficient4C4);
}

bool CurveExponentialSkewNormal::setMinimumValueofx(double minimumValueofx) {
  return getImpl<detail::CurveExponentialSkewNormal_Impl>()->setMinimumValueofx(minimumValueofx);
}

bool CurveExponentialSkewNormal::setMaximumValueofx(double maximumValueofx) {
  return getImpl<detail::CurveExponentialSkewNormal_Impl>()->setMaximumValueofx(maximumValueofx);
}

bool CurveExponentialSkewNormal::setMinimumCurveOutput(double minimumCurveOutput) {
  return getImpl<detail::CurveExponentialSkewNormal_Impl>()->setMinimumCurveOutput(minimumCurveOutput);
}

void CurveExponentialSkewNormal::resetMinimumCurveOutput() {
  getImpl<detail::CurveExponentialSkewNormal_Impl>()->resetMinimumCurveOutput();
}

bool CurveExponentialSkewNormal::setMaximumCurveOutput(double maximumCurveOutput) {
  return getImpl<detail::CurveExponentialSkewNormal_Impl>()->setMaximumCurveOutput(maximumCurveOutput);
}

void CurveExponentialSkewNormal::resetMaximumCurveOutput() {
  getImpl<detail::CurveExponentialSkewNormal_Impl>()->resetMaximumCurveOutput();
}

bool CurveExponentialSkewNormal::setInputUnitTypeforx(const std::string& inputUnitTypeforx) {
  return getImpl<detail::CurveExponentialSkewNormal_Impl>()->setInputUnitTypeforx(inputUnitTypeforx);
}

void CurveExponentialSkewNormal::resetInputUnitTypeforx() {
  getImpl<detail::CurveExponentialSkewNormal_Impl>()->resetInputUnitTypeforx();
}

bool CurveExponentialSkewNormal::setOutputUnitType(const std::string& outputUnitType) {
  return getImpl<detail::CurveExponentialSkewNormal_Impl>()->setOutputUnitType(outputUnitType);
}

void CurveExponentialSkewNormal::resetOutputUnitType() {
  getImpl<detail::CurveExponentialSkewNormal_Impl>()->resetOutputUnitType();
}

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
namespace detail {

double CurveExponentialSkewNormal_Impl::coefficient1C1() const {
  const auto value = getDouble(openstudio::Curve_ExponentialSkewNormalFields::Coefficient1C1, true);
  OS_ASSERT(value);
  return *value;
}

double CurveExponentialSkewNormal_Impl::coefficient2C2() const {
  const auto value = getDouble(openstudio::Curve_ExponentialSkewNormalFields::Coefficient2C2, true);
  OS_ASSERT(value);
  return *value;
}

double CurveExponentialSkewNormal_Impl::coefficient3C3() const {
  const auto value = getDouble(openstudio::Curve_ExponentialSkewNormalFields::Coefficient3C3, true);
  OS_ASSERT(value);
  return *value;
}

double CurveExponentialSkewNormal_Impl::coefficient4C4() const {
  const auto value = getDouble(openstudio::Curve_ExponentialSkewNormalFields::Coefficient4C4, true);
  OS_ASSERT(value);
  return *value;
}

double CurveExponentialSkewNormal_Impl::minimumValueofx() const {
  const auto value = getDouble(openstudio::Curve_ExponentialSkewNormalFields::MinimumValueofx, true);
  OS_ASSERT(value);
  return *value;
}

double CurveExponentialSkewNormal_Impl::maximumValueofx() const {
  const auto value = getDouble(openstudio::Curve_ExponentialSkewNormalFields::MaximumValueofx, true);
  OS_ASSERT(value);
  return *value;
}

boost::optional<double> CurveExponentialSkewNormal_Impl::minimumCurveOutput() const {
  return getDouble(openstudio::Curve_ExponentialSkewNormalFields::MinimumCurveOutput, true);
}

boost::optional<double> CurveExponentialSkewNormal_Impl::maximumCurveOutput() const {
  return getDouble(openstudio::Curve_ExponentialSkewNormalFields::MaximumCurveOutput, true);
}

std::string CurveExponentialSkewNormal_Impl::inputUnitTypeforx() const {
  const auto value = getString(openstudio::Curve_ExponentialSkewNormalFields::InputUnitTypeforx, true);
  OS_ASSERT(value);
  return *value;
}

bool CurveExponentialSkewNormal_Impl::isInputUnitTypeforxDefaulted() const {
  return isEmpty(openstudio::Curve_ExponentialSkewNormalFields::InputUnitTypeforx);
}

std::string CurveExponentialSkewNormal_Impl::outputUnitType() const {
  const auto value = getString(openstudio::Curve_ExponentialSkewNormalFields::OutputUnitType, true);
  OS_ASSERT(value);
  return *value;
}

bool CurveExponentialSkewNormal_Impl::isOutputUnitTypeDefaulted() const {
  return isEmpty(openstudio::Curve_ExponentialSkewNormalFields::OutputUnitType);
}

bool CurveExponentialSkewNormal_Impl::setCoefficient1C1(double coefficient1C1) {
  const bool result = setDouble(openstudio::Curve_ExponentialSkewNormalFields::Coefficient1C1, coefficient1C1);
  OS_ASSERT(result);
  return result;
}

bool CurveExponentialSkewNormal_Impl::setCoefficient2C2(double coefficient2C2) {
  const bool result = setDouble(openstudio::Curve_ExponentialSkewNormalFields::Coefficient2C2, coefficient2C2);
  OS_ASSERT(result);
  return result;
}

bool CurveExponentialSkewNormal_Impl::setCoefficient3C3(double coefficient3C3) {
  const bool result = setDouble(openstudio::Curve_ExponentialSkewNormalFields::Coefficient3C3, coefficient3C3);
  OS_ASSERT(result);
  return result;
}

bool CurveExponentialSkewNormal_Impl::setCoefficient4C4(double coefficient4C4) {
  const bool result = setDouble(openstudio::Curve_ExponentialSkewNormalFields::Coefficient4C4, coefficient4C4);
  OS_ASSERT(result);
  return result;
}

bool CurveExponentialSkewNormal_Impl::setMinimumValueofx(double minimumValueofx) {
  const bool result = setDouble(openstudio::Curve_ExponentialSkewNormalFields::MinimumValueofx, minimumValueofx);
  OS_ASSERT(result);
  return result;
}

bool CurveExponentialSkewNormal_Impl::setMaximumValueofx(double maximumValueofx) {
  const bool result = setDouble(openstudio::Curve_ExponentialSkewNormalFields::MaximumValueofx, maximumValueofx);
  OS_ASSERT(result);
  return result;
}

bool CurveExponentialSkewNormal_Impl::setMinimumCurveOutput(double minimumCurveOutput) {
  const bool result = setDouble(openstudio::Curve_ExponentialSkewNormalFields::MinimumCurveOutput, minimumCurveOutput);
  OS_ASSERT(result);
  return result;
}

void CurveExponentialSkewNormal_Impl::resetMinimumCurveOutput() {
  OS_ASSERT(setString(openstudio::Curve_ExponentialSkewNormalFields::MinimumCurveOutput, ""));
}

bool CurveExponentialSkewNormal_Impl::setMaximumCurveOutput(double maximumCurveOutput) {
  const bool result = setDouble(openstudio::Curve_ExponentialSkewNormalFields::MaximumCurveOutput, maximumCurveOutput);
  OS_ASSERT(result);
  return result;
}

void CurveExponentialSkewNormal_Impl::resetMaximumCurveOutput() {
  OS_ASSERT(setString(openstudio::Curve_ExponentialSkewNormalFields::MaximumCurveOutput, ""));
}

bool CurveExponentialSkewNormal_Impl::setInputUnitTypeforx(const std::string& inputUnitTypeforx) {
  return setString(openstudio::Curve_ExponentialSkewNormalFields::InputUnitTypeforx, inputUnitTypeforx);
}

void CurveExponentialSkewNormal_Impl::resetInputUnitTypeforx() {
  OS_ASSERT(setString(openstudio::Curve_ExponentialSkewNormalFields::InputUnitTypeforx, ""));
}

bool CurveExponentialSkewNormal_Impl::setOutputUnitType(const std::string& outputUnitType) {
  return setString(openstudio::Curve_ExponentialSkewNormalFields::OutputUnitType, outputUnitType);
}

void CurveExponentialSkewNormal_Impl::resetOutputUnitType() {
  OS_ASSERT(setString(openstudio::Curve_ExponentialSkewNormalFields::OutputUnitType, ""));
}

std::vector<std::string> CurveExponentialSkewNormal_Impl::validInputUnitTypeforxValues() const {
  return openstudio::epmodel::CurveExponentialSkewNormal::validInputUnitTypeforxValues();
}

std::vector<std::string> CurveExponentialSkewNormal_Impl::validOutputUnitTypeValues() const {
  return openstudio::epmodel::CurveExponentialSkewNormal::validOutputUnitTypeValues();
}

}  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
