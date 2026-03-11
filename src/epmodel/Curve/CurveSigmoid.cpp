/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "Curve/CurveSigmoid.hpp"
#include "Curve/CurveSigmoid_Impl.hpp"

#include "Model.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/idd/Curve_Sigmoid_FieldEnums.hxx>
#include <utilities/idd/IddEnums.hxx>
#include <utilities/idd/IddFactory.hxx>

namespace openstudio {
namespace epmodel {

CurveSigmoid::CurveSigmoid(const Model& model) : ModelObject(CurveSigmoid::iddObjectType(), model) {
  OS_ASSERT(getImpl<detail::CurveSigmoid_Impl>());
  OS_ASSERT(setCoefficient1C1(0.0));
  OS_ASSERT(setCoefficient2C2(1.0));
  OS_ASSERT(setCoefficient3C3(1.0));
  OS_ASSERT(setCoefficient4C4(1.0));
  OS_ASSERT(setCoefficient5C5(1.0));
  OS_ASSERT(setMinimumValueofx(0.0));
  OS_ASSERT(setMaximumValueofx(1.0));
}

CurveSigmoid::CurveSigmoid(std::shared_ptr<detail::CurveSigmoid_Impl> impl) : ModelObject(std::move(impl)) {}

IddObjectType CurveSigmoid::iddObjectType() {
  return IddObjectType::Curve_Sigmoid;
}

std::vector<std::string> CurveSigmoid::validInputUnitTypeforxValues() {
  return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(), openstudio::Curve_SigmoidFields::InputUnitTypeforx);
}

std::vector<std::string> CurveSigmoid::validOutputUnitTypeValues() {
  return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(), openstudio::Curve_SigmoidFields::OutputUnitType);
}

double CurveSigmoid::coefficient1C1() const {
  return getImpl<detail::CurveSigmoid_Impl>()->coefficient1C1();
}

double CurveSigmoid::coefficient2C2() const {
  return getImpl<detail::CurveSigmoid_Impl>()->coefficient2C2();
}

double CurveSigmoid::coefficient3C3() const {
  return getImpl<detail::CurveSigmoid_Impl>()->coefficient3C3();
}

double CurveSigmoid::coefficient4C4() const {
  return getImpl<detail::CurveSigmoid_Impl>()->coefficient4C4();
}

double CurveSigmoid::coefficient5C5() const {
  return getImpl<detail::CurveSigmoid_Impl>()->coefficient5C5();
}

double CurveSigmoid::minimumValueofx() const {
  return getImpl<detail::CurveSigmoid_Impl>()->minimumValueofx();
}

double CurveSigmoid::maximumValueofx() const {
  return getImpl<detail::CurveSigmoid_Impl>()->maximumValueofx();
}

boost::optional<double> CurveSigmoid::minimumCurveOutput() const {
  return getImpl<detail::CurveSigmoid_Impl>()->minimumCurveOutput();
}

boost::optional<double> CurveSigmoid::maximumCurveOutput() const {
  return getImpl<detail::CurveSigmoid_Impl>()->maximumCurveOutput();
}

std::string CurveSigmoid::inputUnitTypeforx() const {
  return getImpl<detail::CurveSigmoid_Impl>()->inputUnitTypeforx();
}

bool CurveSigmoid::isInputUnitTypeforxDefaulted() const {
  return getImpl<detail::CurveSigmoid_Impl>()->isInputUnitTypeforxDefaulted();
}

std::string CurveSigmoid::outputUnitType() const {
  return getImpl<detail::CurveSigmoid_Impl>()->outputUnitType();
}

bool CurveSigmoid::isOutputUnitTypeDefaulted() const {
  return getImpl<detail::CurveSigmoid_Impl>()->isOutputUnitTypeDefaulted();
}

bool CurveSigmoid::setCoefficient1C1(double coefficient1C1) {
  return getImpl<detail::CurveSigmoid_Impl>()->setCoefficient1C1(coefficient1C1);
}

bool CurveSigmoid::setCoefficient2C2(double coefficient2C2) {
  return getImpl<detail::CurveSigmoid_Impl>()->setCoefficient2C2(coefficient2C2);
}

bool CurveSigmoid::setCoefficient3C3(double coefficient3C3) {
  return getImpl<detail::CurveSigmoid_Impl>()->setCoefficient3C3(coefficient3C3);
}

bool CurveSigmoid::setCoefficient4C4(double coefficient4C4) {
  return getImpl<detail::CurveSigmoid_Impl>()->setCoefficient4C4(coefficient4C4);
}

bool CurveSigmoid::setCoefficient5C5(double coefficient5C5) {
  return getImpl<detail::CurveSigmoid_Impl>()->setCoefficient5C5(coefficient5C5);
}

bool CurveSigmoid::setMinimumValueofx(double minimumValueofx) {
  return getImpl<detail::CurveSigmoid_Impl>()->setMinimumValueofx(minimumValueofx);
}

bool CurveSigmoid::setMaximumValueofx(double maximumValueofx) {
  return getImpl<detail::CurveSigmoid_Impl>()->setMaximumValueofx(maximumValueofx);
}

bool CurveSigmoid::setMinimumCurveOutput(double minimumCurveOutput) {
  return getImpl<detail::CurveSigmoid_Impl>()->setMinimumCurveOutput(minimumCurveOutput);
}

void CurveSigmoid::resetMinimumCurveOutput() {
  getImpl<detail::CurveSigmoid_Impl>()->resetMinimumCurveOutput();
}

bool CurveSigmoid::setMaximumCurveOutput(double maximumCurveOutput) {
  return getImpl<detail::CurveSigmoid_Impl>()->setMaximumCurveOutput(maximumCurveOutput);
}

void CurveSigmoid::resetMaximumCurveOutput() {
  getImpl<detail::CurveSigmoid_Impl>()->resetMaximumCurveOutput();
}

bool CurveSigmoid::setInputUnitTypeforx(const std::string& inputUnitTypeforx) {
  return getImpl<detail::CurveSigmoid_Impl>()->setInputUnitTypeforx(inputUnitTypeforx);
}

void CurveSigmoid::resetInputUnitTypeforx() {
  getImpl<detail::CurveSigmoid_Impl>()->resetInputUnitTypeforx();
}

bool CurveSigmoid::setOutputUnitType(const std::string& outputUnitType) {
  return getImpl<detail::CurveSigmoid_Impl>()->setOutputUnitType(outputUnitType);
}

void CurveSigmoid::resetOutputUnitType() {
  getImpl<detail::CurveSigmoid_Impl>()->resetOutputUnitType();
}

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
namespace detail {

double CurveSigmoid_Impl::coefficient1C1() const {
  const auto value = getDouble(openstudio::Curve_SigmoidFields::Coefficient1C1, true);
  OS_ASSERT(value);
  return *value;
}

double CurveSigmoid_Impl::coefficient2C2() const {
  const auto value = getDouble(openstudio::Curve_SigmoidFields::Coefficient2C2, true);
  OS_ASSERT(value);
  return *value;
}

double CurveSigmoid_Impl::coefficient3C3() const {
  const auto value = getDouble(openstudio::Curve_SigmoidFields::Coefficient3C3, true);
  OS_ASSERT(value);
  return *value;
}

double CurveSigmoid_Impl::coefficient4C4() const {
  const auto value = getDouble(openstudio::Curve_SigmoidFields::Coefficient4C4, true);
  OS_ASSERT(value);
  return *value;
}

double CurveSigmoid_Impl::coefficient5C5() const {
  const auto value = getDouble(openstudio::Curve_SigmoidFields::Coefficient5C5, true);
  OS_ASSERT(value);
  return *value;
}

double CurveSigmoid_Impl::minimumValueofx() const {
  const auto value = getDouble(openstudio::Curve_SigmoidFields::MinimumValueofx, true);
  OS_ASSERT(value);
  return *value;
}

double CurveSigmoid_Impl::maximumValueofx() const {
  const auto value = getDouble(openstudio::Curve_SigmoidFields::MaximumValueofx, true);
  OS_ASSERT(value);
  return *value;
}

boost::optional<double> CurveSigmoid_Impl::minimumCurveOutput() const {
  return getDouble(openstudio::Curve_SigmoidFields::MinimumCurveOutput, true);
}

boost::optional<double> CurveSigmoid_Impl::maximumCurveOutput() const {
  return getDouble(openstudio::Curve_SigmoidFields::MaximumCurveOutput, true);
}

std::string CurveSigmoid_Impl::inputUnitTypeforx() const {
  const auto value = getString(openstudio::Curve_SigmoidFields::InputUnitTypeforx, true);
  OS_ASSERT(value);
  return *value;
}

bool CurveSigmoid_Impl::isInputUnitTypeforxDefaulted() const {
  return isEmpty(openstudio::Curve_SigmoidFields::InputUnitTypeforx);
}

std::string CurveSigmoid_Impl::outputUnitType() const {
  const auto value = getString(openstudio::Curve_SigmoidFields::OutputUnitType, true);
  OS_ASSERT(value);
  return *value;
}

bool CurveSigmoid_Impl::isOutputUnitTypeDefaulted() const {
  return isEmpty(openstudio::Curve_SigmoidFields::OutputUnitType);
}

bool CurveSigmoid_Impl::setCoefficient1C1(double coefficient1C1) {
  const bool result = setDouble(openstudio::Curve_SigmoidFields::Coefficient1C1, coefficient1C1);
  OS_ASSERT(result);
  return result;
}

bool CurveSigmoid_Impl::setCoefficient2C2(double coefficient2C2) {
  const bool result = setDouble(openstudio::Curve_SigmoidFields::Coefficient2C2, coefficient2C2);
  OS_ASSERT(result);
  return result;
}

bool CurveSigmoid_Impl::setCoefficient3C3(double coefficient3C3) {
  const bool result = setDouble(openstudio::Curve_SigmoidFields::Coefficient3C3, coefficient3C3);
  OS_ASSERT(result);
  return result;
}

bool CurveSigmoid_Impl::setCoefficient4C4(double coefficient4C4) {
  const bool result = setDouble(openstudio::Curve_SigmoidFields::Coefficient4C4, coefficient4C4);
  OS_ASSERT(result);
  return result;
}

bool CurveSigmoid_Impl::setCoefficient5C5(double coefficient5C5) {
  const bool result = setDouble(openstudio::Curve_SigmoidFields::Coefficient5C5, coefficient5C5);
  OS_ASSERT(result);
  return result;
}

bool CurveSigmoid_Impl::setMinimumValueofx(double minimumValueofx) {
  const bool result = setDouble(openstudio::Curve_SigmoidFields::MinimumValueofx, minimumValueofx);
  OS_ASSERT(result);
  return result;
}

bool CurveSigmoid_Impl::setMaximumValueofx(double maximumValueofx) {
  const bool result = setDouble(openstudio::Curve_SigmoidFields::MaximumValueofx, maximumValueofx);
  OS_ASSERT(result);
  return result;
}

bool CurveSigmoid_Impl::setMinimumCurveOutput(double minimumCurveOutput) {
  const bool result = setDouble(openstudio::Curve_SigmoidFields::MinimumCurveOutput, minimumCurveOutput);
  OS_ASSERT(result);
  return result;
}

void CurveSigmoid_Impl::resetMinimumCurveOutput() {
  OS_ASSERT(setString(openstudio::Curve_SigmoidFields::MinimumCurveOutput, ""));
}

bool CurveSigmoid_Impl::setMaximumCurveOutput(double maximumCurveOutput) {
  const bool result = setDouble(openstudio::Curve_SigmoidFields::MaximumCurveOutput, maximumCurveOutput);
  OS_ASSERT(result);
  return result;
}

void CurveSigmoid_Impl::resetMaximumCurveOutput() {
  OS_ASSERT(setString(openstudio::Curve_SigmoidFields::MaximumCurveOutput, ""));
}

bool CurveSigmoid_Impl::setInputUnitTypeforx(const std::string& inputUnitTypeforx) {
  return setString(openstudio::Curve_SigmoidFields::InputUnitTypeforx, inputUnitTypeforx);
}

void CurveSigmoid_Impl::resetInputUnitTypeforx() {
  OS_ASSERT(setString(openstudio::Curve_SigmoidFields::InputUnitTypeforx, ""));
}

bool CurveSigmoid_Impl::setOutputUnitType(const std::string& outputUnitType) {
  return setString(openstudio::Curve_SigmoidFields::OutputUnitType, outputUnitType);
}

void CurveSigmoid_Impl::resetOutputUnitType() {
  OS_ASSERT(setString(openstudio::Curve_SigmoidFields::OutputUnitType, ""));
}

std::vector<std::string> CurveSigmoid_Impl::validInputUnitTypeforxValues() const {
  return openstudio::epmodel::CurveSigmoid::validInputUnitTypeforxValues();
}

std::vector<std::string> CurveSigmoid_Impl::validOutputUnitTypeValues() const {
  return openstudio::epmodel::CurveSigmoid::validOutputUnitTypeValues();
}

}  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
