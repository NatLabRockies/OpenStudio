/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "Curve/CurveRectangularHyperbola2.hpp"
#include "Curve/CurveRectangularHyperbola2_Impl.hpp"

#include "Model.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/idd/Curve_RectangularHyperbola2_FieldEnums.hxx>
#include <utilities/idd/IddEnums.hxx>
#include <utilities/idd/IddFactory.hxx>

namespace openstudio {
namespace epmodel {

CurveRectangularHyperbola2::CurveRectangularHyperbola2(const Model& model) : ModelObject(CurveRectangularHyperbola2::iddObjectType(), model) {
  OS_ASSERT(getImpl<detail::CurveRectangularHyperbola2_Impl>());
  OS_ASSERT(setCoefficient1C1(1.0));
  OS_ASSERT(setCoefficient2C2(1.0));
  OS_ASSERT(setCoefficient3C3(1.0));
  OS_ASSERT(setMinimumValueofx(0.0));
  OS_ASSERT(setMaximumValueofx(1.0));
}

CurveRectangularHyperbola2::CurveRectangularHyperbola2(std::shared_ptr<detail::CurveRectangularHyperbola2_Impl> impl)
  : ModelObject(std::move(impl)) {}

IddObjectType CurveRectangularHyperbola2::iddObjectType() {
  return IddObjectType::Curve_RectangularHyperbola2;
}

std::vector<std::string> CurveRectangularHyperbola2::validInputUnitTypeforxValues() {
  return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(), openstudio::Curve_RectangularHyperbola2Fields::InputUnitTypeforx);
}

std::vector<std::string> CurveRectangularHyperbola2::validOutputUnitTypeValues() {
  return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(), openstudio::Curve_RectangularHyperbola2Fields::OutputUnitType);
}

double CurveRectangularHyperbola2::coefficient1C1() const {
  return getImpl<detail::CurveRectangularHyperbola2_Impl>()->coefficient1C1();
}

double CurveRectangularHyperbola2::coefficient2C2() const {
  return getImpl<detail::CurveRectangularHyperbola2_Impl>()->coefficient2C2();
}

double CurveRectangularHyperbola2::coefficient3C3() const {
  return getImpl<detail::CurveRectangularHyperbola2_Impl>()->coefficient3C3();
}

double CurveRectangularHyperbola2::minimumValueofx() const {
  return getImpl<detail::CurveRectangularHyperbola2_Impl>()->minimumValueofx();
}

double CurveRectangularHyperbola2::maximumValueofx() const {
  return getImpl<detail::CurveRectangularHyperbola2_Impl>()->maximumValueofx();
}

boost::optional<double> CurveRectangularHyperbola2::minimumCurveOutput() const {
  return getImpl<detail::CurveRectangularHyperbola2_Impl>()->minimumCurveOutput();
}

boost::optional<double> CurveRectangularHyperbola2::maximumCurveOutput() const {
  return getImpl<detail::CurveRectangularHyperbola2_Impl>()->maximumCurveOutput();
}

std::string CurveRectangularHyperbola2::inputUnitTypeforx() const {
  return getImpl<detail::CurveRectangularHyperbola2_Impl>()->inputUnitTypeforx();
}

bool CurveRectangularHyperbola2::isInputUnitTypeforxDefaulted() const {
  return getImpl<detail::CurveRectangularHyperbola2_Impl>()->isInputUnitTypeforxDefaulted();
}

std::string CurveRectangularHyperbola2::outputUnitType() const {
  return getImpl<detail::CurveRectangularHyperbola2_Impl>()->outputUnitType();
}

bool CurveRectangularHyperbola2::isOutputUnitTypeDefaulted() const {
  return getImpl<detail::CurveRectangularHyperbola2_Impl>()->isOutputUnitTypeDefaulted();
}

bool CurveRectangularHyperbola2::setCoefficient1C1(double coefficient1C1) {
  return getImpl<detail::CurveRectangularHyperbola2_Impl>()->setCoefficient1C1(coefficient1C1);
}

bool CurveRectangularHyperbola2::setCoefficient2C2(double coefficient2C2) {
  return getImpl<detail::CurveRectangularHyperbola2_Impl>()->setCoefficient2C2(coefficient2C2);
}

bool CurveRectangularHyperbola2::setCoefficient3C3(double coefficient3C3) {
  return getImpl<detail::CurveRectangularHyperbola2_Impl>()->setCoefficient3C3(coefficient3C3);
}

bool CurveRectangularHyperbola2::setMinimumValueofx(double minimumValueofx) {
  return getImpl<detail::CurveRectangularHyperbola2_Impl>()->setMinimumValueofx(minimumValueofx);
}

bool CurveRectangularHyperbola2::setMaximumValueofx(double maximumValueofx) {
  return getImpl<detail::CurveRectangularHyperbola2_Impl>()->setMaximumValueofx(maximumValueofx);
}

bool CurveRectangularHyperbola2::setMinimumCurveOutput(double minimumCurveOutput) {
  return getImpl<detail::CurveRectangularHyperbola2_Impl>()->setMinimumCurveOutput(minimumCurveOutput);
}

void CurveRectangularHyperbola2::resetMinimumCurveOutput() {
  getImpl<detail::CurveRectangularHyperbola2_Impl>()->resetMinimumCurveOutput();
}

bool CurveRectangularHyperbola2::setMaximumCurveOutput(double maximumCurveOutput) {
  return getImpl<detail::CurveRectangularHyperbola2_Impl>()->setMaximumCurveOutput(maximumCurveOutput);
}

void CurveRectangularHyperbola2::resetMaximumCurveOutput() {
  getImpl<detail::CurveRectangularHyperbola2_Impl>()->resetMaximumCurveOutput();
}

bool CurveRectangularHyperbola2::setInputUnitTypeforx(const std::string& inputUnitTypeforx) {
  return getImpl<detail::CurveRectangularHyperbola2_Impl>()->setInputUnitTypeforx(inputUnitTypeforx);
}

void CurveRectangularHyperbola2::resetInputUnitTypeforx() {
  getImpl<detail::CurveRectangularHyperbola2_Impl>()->resetInputUnitTypeforx();
}

bool CurveRectangularHyperbola2::setOutputUnitType(const std::string& outputUnitType) {
  return getImpl<detail::CurveRectangularHyperbola2_Impl>()->setOutputUnitType(outputUnitType);
}

void CurveRectangularHyperbola2::resetOutputUnitType() {
  getImpl<detail::CurveRectangularHyperbola2_Impl>()->resetOutputUnitType();
}

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
namespace detail {

double CurveRectangularHyperbola2_Impl::coefficient1C1() const {
  const auto value = getDouble(openstudio::Curve_RectangularHyperbola2Fields::Coefficient1C1, true);
  OS_ASSERT(value);
  return *value;
}

double CurveRectangularHyperbola2_Impl::coefficient2C2() const {
  const auto value = getDouble(openstudio::Curve_RectangularHyperbola2Fields::Coefficient2C2, true);
  OS_ASSERT(value);
  return *value;
}

double CurveRectangularHyperbola2_Impl::coefficient3C3() const {
  const auto value = getDouble(openstudio::Curve_RectangularHyperbola2Fields::Coefficient3C3, true);
  OS_ASSERT(value);
  return *value;
}

double CurveRectangularHyperbola2_Impl::minimumValueofx() const {
  const auto value = getDouble(openstudio::Curve_RectangularHyperbola2Fields::MinimumValueofx, true);
  OS_ASSERT(value);
  return *value;
}

double CurveRectangularHyperbola2_Impl::maximumValueofx() const {
  const auto value = getDouble(openstudio::Curve_RectangularHyperbola2Fields::MaximumValueofx, true);
  OS_ASSERT(value);
  return *value;
}

boost::optional<double> CurveRectangularHyperbola2_Impl::minimumCurveOutput() const {
  return getDouble(openstudio::Curve_RectangularHyperbola2Fields::MinimumCurveOutput, true);
}

boost::optional<double> CurveRectangularHyperbola2_Impl::maximumCurveOutput() const {
  return getDouble(openstudio::Curve_RectangularHyperbola2Fields::MaximumCurveOutput, true);
}

std::string CurveRectangularHyperbola2_Impl::inputUnitTypeforx() const {
  const auto value = getString(openstudio::Curve_RectangularHyperbola2Fields::InputUnitTypeforx, true);
  OS_ASSERT(value);
  return *value;
}

bool CurveRectangularHyperbola2_Impl::isInputUnitTypeforxDefaulted() const {
  return isEmpty(openstudio::Curve_RectangularHyperbola2Fields::InputUnitTypeforx);
}

std::string CurveRectangularHyperbola2_Impl::outputUnitType() const {
  const auto value = getString(openstudio::Curve_RectangularHyperbola2Fields::OutputUnitType, true);
  OS_ASSERT(value);
  return *value;
}

bool CurveRectangularHyperbola2_Impl::isOutputUnitTypeDefaulted() const {
  return isEmpty(openstudio::Curve_RectangularHyperbola2Fields::OutputUnitType);
}

bool CurveRectangularHyperbola2_Impl::setCoefficient1C1(double coefficient1C1) {
  const bool result = setDouble(openstudio::Curve_RectangularHyperbola2Fields::Coefficient1C1, coefficient1C1);
  OS_ASSERT(result);
  return result;
}

bool CurveRectangularHyperbola2_Impl::setCoefficient2C2(double coefficient2C2) {
  const bool result = setDouble(openstudio::Curve_RectangularHyperbola2Fields::Coefficient2C2, coefficient2C2);
  OS_ASSERT(result);
  return result;
}

bool CurveRectangularHyperbola2_Impl::setCoefficient3C3(double coefficient3C3) {
  const bool result = setDouble(openstudio::Curve_RectangularHyperbola2Fields::Coefficient3C3, coefficient3C3);
  OS_ASSERT(result);
  return result;
}

bool CurveRectangularHyperbola2_Impl::setMinimumValueofx(double minimumValueofx) {
  const bool result = setDouble(openstudio::Curve_RectangularHyperbola2Fields::MinimumValueofx, minimumValueofx);
  OS_ASSERT(result);
  return result;
}

bool CurveRectangularHyperbola2_Impl::setMaximumValueofx(double maximumValueofx) {
  const bool result = setDouble(openstudio::Curve_RectangularHyperbola2Fields::MaximumValueofx, maximumValueofx);
  OS_ASSERT(result);
  return result;
}

bool CurveRectangularHyperbola2_Impl::setMinimumCurveOutput(double minimumCurveOutput) {
  const bool result = setDouble(openstudio::Curve_RectangularHyperbola2Fields::MinimumCurveOutput, minimumCurveOutput);
  OS_ASSERT(result);
  return result;
}

void CurveRectangularHyperbola2_Impl::resetMinimumCurveOutput() {
  OS_ASSERT(setString(openstudio::Curve_RectangularHyperbola2Fields::MinimumCurveOutput, ""));
}

bool CurveRectangularHyperbola2_Impl::setMaximumCurveOutput(double maximumCurveOutput) {
  const bool result = setDouble(openstudio::Curve_RectangularHyperbola2Fields::MaximumCurveOutput, maximumCurveOutput);
  OS_ASSERT(result);
  return result;
}

void CurveRectangularHyperbola2_Impl::resetMaximumCurveOutput() {
  OS_ASSERT(setString(openstudio::Curve_RectangularHyperbola2Fields::MaximumCurveOutput, ""));
}

bool CurveRectangularHyperbola2_Impl::setInputUnitTypeforx(const std::string& inputUnitTypeforx) {
  return setString(openstudio::Curve_RectangularHyperbola2Fields::InputUnitTypeforx, inputUnitTypeforx);
}

void CurveRectangularHyperbola2_Impl::resetInputUnitTypeforx() {
  OS_ASSERT(setString(openstudio::Curve_RectangularHyperbola2Fields::InputUnitTypeforx, ""));
}

bool CurveRectangularHyperbola2_Impl::setOutputUnitType(const std::string& outputUnitType) {
  return setString(openstudio::Curve_RectangularHyperbola2Fields::OutputUnitType, outputUnitType);
}

void CurveRectangularHyperbola2_Impl::resetOutputUnitType() {
  OS_ASSERT(setString(openstudio::Curve_RectangularHyperbola2Fields::OutputUnitType, ""));
}

std::vector<std::string> CurveRectangularHyperbola2_Impl::validInputUnitTypeforxValues() const {
  return openstudio::epmodel::CurveRectangularHyperbola2::validInputUnitTypeforxValues();
}

std::vector<std::string> CurveRectangularHyperbola2_Impl::validOutputUnitTypeValues() const {
  return openstudio::epmodel::CurveRectangularHyperbola2::validOutputUnitTypeValues();
}

}  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
