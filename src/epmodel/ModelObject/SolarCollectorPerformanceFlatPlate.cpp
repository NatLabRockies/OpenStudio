/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "SolarCollectorPerformanceFlatPlate.hpp"
#include "SolarCollectorPerformanceFlatPlate_Impl.hpp"

#include "Model.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/idd/IddEnums.hxx>
#include <utilities/idd/IddFactory.hxx>
#include <utilities/idd/IddObject.hpp>
#include <utilities/idd/SolarCollectorPerformance_FlatPlate_FieldEnums.hxx>

namespace openstudio {
namespace epmodel {

SolarCollectorPerformanceFlatPlate::SolarCollectorPerformanceFlatPlate(const Model& model)
  : ModelObject(SolarCollectorPerformanceFlatPlate::iddObjectType(), model) {}

SolarCollectorPerformanceFlatPlate::SolarCollectorPerformanceFlatPlate(std::shared_ptr<detail::SolarCollectorPerformanceFlatPlate_Impl> impl)
  : ModelObject(std::move(impl)) {}

IddObjectType SolarCollectorPerformanceFlatPlate::iddObjectType() {
  return IddObjectType::SolarCollectorPerformance_FlatPlate;
}

std::vector<std::string> SolarCollectorPerformanceFlatPlate::testFluidValues() {
  return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(),
                        openstudio::SolarCollectorPerformance_FlatPlateFields::TestFluid);
}

std::vector<std::string> SolarCollectorPerformanceFlatPlate::testCorrelationTypeValues() {
  return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(),
                        openstudio::SolarCollectorPerformance_FlatPlateFields::TestCorrelationType);
}

double SolarCollectorPerformanceFlatPlate::grossArea() const {
  return getImpl<detail::SolarCollectorPerformanceFlatPlate_Impl>()->grossArea();
}

std::string SolarCollectorPerformanceFlatPlate::testFluid() const {
  return getImpl<detail::SolarCollectorPerformanceFlatPlate_Impl>()->testFluid();
}

bool SolarCollectorPerformanceFlatPlate::isTestFluidDefaulted() const {
  return getImpl<detail::SolarCollectorPerformanceFlatPlate_Impl>()->isTestFluidDefaulted();
}

double SolarCollectorPerformanceFlatPlate::testFlowRate() const {
  return getImpl<detail::SolarCollectorPerformanceFlatPlate_Impl>()->testFlowRate();
}

std::string SolarCollectorPerformanceFlatPlate::testCorrelationType() const {
  return getImpl<detail::SolarCollectorPerformanceFlatPlate_Impl>()->testCorrelationType();
}

double SolarCollectorPerformanceFlatPlate::coefficient1ofEfficiencyEquation() const {
  return getImpl<detail::SolarCollectorPerformanceFlatPlate_Impl>()->coefficient1ofEfficiencyEquation();
}

double SolarCollectorPerformanceFlatPlate::coefficient2ofEfficiencyEquation() const {
  return getImpl<detail::SolarCollectorPerformanceFlatPlate_Impl>()->coefficient2ofEfficiencyEquation();
}

boost::optional<double> SolarCollectorPerformanceFlatPlate::coefficient3ofEfficiencyEquation() const {
  return getImpl<detail::SolarCollectorPerformanceFlatPlate_Impl>()->coefficient3ofEfficiencyEquation();
}

boost::optional<double> SolarCollectorPerformanceFlatPlate::coefficient2ofIncidentAngleModifier() const {
  return getImpl<detail::SolarCollectorPerformanceFlatPlate_Impl>()->coefficient2ofIncidentAngleModifier();
}

boost::optional<double> SolarCollectorPerformanceFlatPlate::coefficient3ofIncidentAngleModifier() const {
  return getImpl<detail::SolarCollectorPerformanceFlatPlate_Impl>()->coefficient3ofIncidentAngleModifier();
}

bool SolarCollectorPerformanceFlatPlate::setGrossArea(double grossArea) {
  return getImpl<detail::SolarCollectorPerformanceFlatPlate_Impl>()->setGrossArea(grossArea);
}

bool SolarCollectorPerformanceFlatPlate::setTestFluid(const std::string& testFluid) {
  return getImpl<detail::SolarCollectorPerformanceFlatPlate_Impl>()->setTestFluid(testFluid);
}

void SolarCollectorPerformanceFlatPlate::resetTestFluid() {
  getImpl<detail::SolarCollectorPerformanceFlatPlate_Impl>()->resetTestFluid();
}

bool SolarCollectorPerformanceFlatPlate::setTestFlowRate(double testFlowRate) {
  return getImpl<detail::SolarCollectorPerformanceFlatPlate_Impl>()->setTestFlowRate(testFlowRate);
}

bool SolarCollectorPerformanceFlatPlate::setTestCorrelationType(const std::string& testCorrelationType) {
  return getImpl<detail::SolarCollectorPerformanceFlatPlate_Impl>()->setTestCorrelationType(testCorrelationType);
}

bool SolarCollectorPerformanceFlatPlate::setCoefficient1ofEfficiencyEquation(double coefficient1ofEfficiencyEquation) {
  return getImpl<detail::SolarCollectorPerformanceFlatPlate_Impl>()->setCoefficient1ofEfficiencyEquation(coefficient1ofEfficiencyEquation);
}

bool SolarCollectorPerformanceFlatPlate::setCoefficient2ofEfficiencyEquation(double coefficient2ofEfficiencyEquation) {
  return getImpl<detail::SolarCollectorPerformanceFlatPlate_Impl>()->setCoefficient2ofEfficiencyEquation(coefficient2ofEfficiencyEquation);
}

bool SolarCollectorPerformanceFlatPlate::setCoefficient3ofEfficiencyEquation(double coefficient3ofEfficiencyEquation) {
  return getImpl<detail::SolarCollectorPerformanceFlatPlate_Impl>()->setCoefficient3ofEfficiencyEquation(coefficient3ofEfficiencyEquation);
}

void SolarCollectorPerformanceFlatPlate::resetCoefficient3ofEfficiencyEquation() {
  getImpl<detail::SolarCollectorPerformanceFlatPlate_Impl>()->resetCoefficient3ofEfficiencyEquation();
}

bool SolarCollectorPerformanceFlatPlate::setCoefficient2ofIncidentAngleModifier(double coefficient2ofIncidentAngleModifier) {
  return getImpl<detail::SolarCollectorPerformanceFlatPlate_Impl>()->setCoefficient2ofIncidentAngleModifier(coefficient2ofIncidentAngleModifier);
}

void SolarCollectorPerformanceFlatPlate::resetCoefficient2ofIncidentAngleModifier() {
  getImpl<detail::SolarCollectorPerformanceFlatPlate_Impl>()->resetCoefficient2ofIncidentAngleModifier();
}

bool SolarCollectorPerformanceFlatPlate::setCoefficient3ofIncidentAngleModifier(double coefficient3ofIncidentAngleModifier) {
  return getImpl<detail::SolarCollectorPerformanceFlatPlate_Impl>()->setCoefficient3ofIncidentAngleModifier(coefficient3ofIncidentAngleModifier);
}

void SolarCollectorPerformanceFlatPlate::resetCoefficient3ofIncidentAngleModifier() {
  getImpl<detail::SolarCollectorPerformanceFlatPlate_Impl>()->resetCoefficient3ofIncidentAngleModifier();
}

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
namespace detail {

double SolarCollectorPerformanceFlatPlate_Impl::grossArea() const {
  const auto value = getDouble(openstudio::SolarCollectorPerformance_FlatPlateFields::GrossArea, true);
  OS_ASSERT(value);
  return *value;
}

std::string SolarCollectorPerformanceFlatPlate_Impl::testFluid() const {
  const auto value = getString(openstudio::SolarCollectorPerformance_FlatPlateFields::TestFluid, true);
  OS_ASSERT(value);
  return *value;
}

bool SolarCollectorPerformanceFlatPlate_Impl::isTestFluidDefaulted() const {
  return isEmpty(openstudio::SolarCollectorPerformance_FlatPlateFields::TestFluid);
}

double SolarCollectorPerformanceFlatPlate_Impl::testFlowRate() const {
  const auto value = getDouble(openstudio::SolarCollectorPerformance_FlatPlateFields::TestFlowRate, true);
  OS_ASSERT(value);
  return *value;
}

std::string SolarCollectorPerformanceFlatPlate_Impl::testCorrelationType() const {
  const auto value = getString(openstudio::SolarCollectorPerformance_FlatPlateFields::TestCorrelationType, true);
  OS_ASSERT(value);
  return *value;
}

double SolarCollectorPerformanceFlatPlate_Impl::coefficient1ofEfficiencyEquation() const {
  const auto value = getDouble(openstudio::SolarCollectorPerformance_FlatPlateFields::Coefficient1ofEfficiencyEquation, true);
  OS_ASSERT(value);
  return *value;
}

double SolarCollectorPerformanceFlatPlate_Impl::coefficient2ofEfficiencyEquation() const {
  const auto value = getDouble(openstudio::SolarCollectorPerformance_FlatPlateFields::Coefficient2ofEfficiencyEquation, true);
  OS_ASSERT(value);
  return *value;
}

boost::optional<double> SolarCollectorPerformanceFlatPlate_Impl::coefficient3ofEfficiencyEquation() const {
  return getDouble(openstudio::SolarCollectorPerformance_FlatPlateFields::Coefficient3ofEfficiencyEquation, true);
}

boost::optional<double> SolarCollectorPerformanceFlatPlate_Impl::coefficient2ofIncidentAngleModifier() const {
  return getDouble(openstudio::SolarCollectorPerformance_FlatPlateFields::Coefficient2ofIncidentAngleModifier, true);
}

boost::optional<double> SolarCollectorPerformanceFlatPlate_Impl::coefficient3ofIncidentAngleModifier() const {
  return getDouble(openstudio::SolarCollectorPerformance_FlatPlateFields::Coefficient3ofIncidentAngleModifier, true);
}

bool SolarCollectorPerformanceFlatPlate_Impl::setGrossArea(double grossArea) {
  const bool result = setDouble(openstudio::SolarCollectorPerformance_FlatPlateFields::GrossArea, grossArea);
  return result;
}

bool SolarCollectorPerformanceFlatPlate_Impl::setTestFluid(const std::string& testFluid) {
  const bool result = setString(openstudio::SolarCollectorPerformance_FlatPlateFields::TestFluid, testFluid);
  return result;
}

void SolarCollectorPerformanceFlatPlate_Impl::resetTestFluid() {
  OS_ASSERT(setString(openstudio::SolarCollectorPerformance_FlatPlateFields::TestFluid, ""));
}

bool SolarCollectorPerformanceFlatPlate_Impl::setTestFlowRate(double testFlowRate) {
  const bool result = setDouble(openstudio::SolarCollectorPerformance_FlatPlateFields::TestFlowRate, testFlowRate);
  return result;
}

bool SolarCollectorPerformanceFlatPlate_Impl::setTestCorrelationType(const std::string& testCorrelationType) {
  const bool result = setString(openstudio::SolarCollectorPerformance_FlatPlateFields::TestCorrelationType, testCorrelationType);
  return result;
}

bool SolarCollectorPerformanceFlatPlate_Impl::setCoefficient1ofEfficiencyEquation(double coefficient1ofEfficiencyEquation) {
  const bool result =
    setDouble(openstudio::SolarCollectorPerformance_FlatPlateFields::Coefficient1ofEfficiencyEquation, coefficient1ofEfficiencyEquation);
  OS_ASSERT(result);
  return result;
}

bool SolarCollectorPerformanceFlatPlate_Impl::setCoefficient2ofEfficiencyEquation(double coefficient2ofEfficiencyEquation) {
  const bool result =
    setDouble(openstudio::SolarCollectorPerformance_FlatPlateFields::Coefficient2ofEfficiencyEquation, coefficient2ofEfficiencyEquation);
  OS_ASSERT(result);
  return result;
}

bool SolarCollectorPerformanceFlatPlate_Impl::setCoefficient3ofEfficiencyEquation(boost::optional<double> coefficient3ofEfficiencyEquation) {
  bool result = false;
  if (coefficient3ofEfficiencyEquation) {
    result = setDouble(openstudio::SolarCollectorPerformance_FlatPlateFields::Coefficient3ofEfficiencyEquation,
                       coefficient3ofEfficiencyEquation.get());
  } else {
    resetCoefficient3ofEfficiencyEquation();
    result = true;
  }
  OS_ASSERT(result);
  return result;
}

void SolarCollectorPerformanceFlatPlate_Impl::resetCoefficient3ofEfficiencyEquation() {
  OS_ASSERT(setString(openstudio::SolarCollectorPerformance_FlatPlateFields::Coefficient3ofEfficiencyEquation, ""));
}

bool SolarCollectorPerformanceFlatPlate_Impl::setCoefficient2ofIncidentAngleModifier(
  boost::optional<double> coefficient2ofIncidentAngleModifier) {
  bool result = false;
  if (coefficient2ofIncidentAngleModifier) {
    result = setDouble(openstudio::SolarCollectorPerformance_FlatPlateFields::Coefficient2ofIncidentAngleModifier,
                       coefficient2ofIncidentAngleModifier.get());
  } else {
    resetCoefficient2ofIncidentAngleModifier();
    result = true;
  }
  OS_ASSERT(result);
  return result;
}

void SolarCollectorPerformanceFlatPlate_Impl::resetCoefficient2ofIncidentAngleModifier() {
  OS_ASSERT(setString(openstudio::SolarCollectorPerformance_FlatPlateFields::Coefficient2ofIncidentAngleModifier, ""));
}

bool SolarCollectorPerformanceFlatPlate_Impl::setCoefficient3ofIncidentAngleModifier(
  boost::optional<double> coefficient3ofIncidentAngleModifier) {
  bool result = false;
  if (coefficient3ofIncidentAngleModifier) {
    result = setDouble(openstudio::SolarCollectorPerformance_FlatPlateFields::Coefficient3ofIncidentAngleModifier,
                       coefficient3ofIncidentAngleModifier.get());
  } else {
    resetCoefficient3ofIncidentAngleModifier();
    result = true;
  }
  OS_ASSERT(result);
  return result;
}

void SolarCollectorPerformanceFlatPlate_Impl::resetCoefficient3ofIncidentAngleModifier() {
  OS_ASSERT(setString(openstudio::SolarCollectorPerformance_FlatPlateFields::Coefficient3ofIncidentAngleModifier, ""));
}

std::vector<std::string> SolarCollectorPerformanceFlatPlate_Impl::testFluidValues() const {
  return openstudio::epmodel::SolarCollectorPerformanceFlatPlate::testFluidValues();
}

std::vector<std::string> SolarCollectorPerformanceFlatPlate_Impl::testCorrelationTypeValues() const {
  return openstudio::epmodel::SolarCollectorPerformanceFlatPlate::testCorrelationTypeValues();
}

}  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
