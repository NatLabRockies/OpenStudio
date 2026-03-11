/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "CoilDXASHRAE205Performance.hpp"
#include "CoilDXASHRAE205Performance_Impl.hpp"

#include "Model.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/core/StringHelpers.hpp>
#include <utilities/idd/Coil_DX_ASHRAE205_Performance_FieldEnums.hxx>
#include <utilities/idd/IddEnums.hxx>
#include <utilities/idd/IddFactory.hxx>
#include <utilities/idd/IddObject.hpp>

namespace openstudio {
namespace epmodel {

CoilDXASHRAE205Performance::CoilDXASHRAE205Performance(const Model& model)
  : ModelObject(CoilDXASHRAE205Performance::iddObjectType(), model) {}

CoilDXASHRAE205Performance::CoilDXASHRAE205Performance(std::shared_ptr<detail::CoilDXASHRAE205Performance_Impl> impl)
  : ModelObject(std::move(impl)) {}

IddObjectType CoilDXASHRAE205Performance::iddObjectType() {
  return IddObjectType::Coil_DX_ASHRAE205_Performance;
}

std::vector<std::string> CoilDXASHRAE205Performance::performanceInterpolationMethodValues() {
  return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(),
                        openstudio::Coil_DX_ASHRAE205_PerformanceFields::PerformanceInterpolationMethod);
}

std::string CoilDXASHRAE205Performance::representationFileName() const {
  return getImpl<detail::CoilDXASHRAE205Performance_Impl>()->representationFileName();
}

bool CoilDXASHRAE205Performance::setRepresentationFileName(const std::string& representationFileName) {
  return getImpl<detail::CoilDXASHRAE205Performance_Impl>()->setRepresentationFileName(representationFileName);
}

std::string CoilDXASHRAE205Performance::performanceInterpolationMethod() const {
  return getImpl<detail::CoilDXASHRAE205Performance_Impl>()->performanceInterpolationMethod();
}

bool CoilDXASHRAE205Performance::isPerformanceInterpolationMethodDefaulted() const {
  return getImpl<detail::CoilDXASHRAE205Performance_Impl>()->isPerformanceInterpolationMethodDefaulted();
}

bool CoilDXASHRAE205Performance::setPerformanceInterpolationMethod(const std::string& performanceInterpolationMethod) {
  return getImpl<detail::CoilDXASHRAE205Performance_Impl>()->setPerformanceInterpolationMethod(performanceInterpolationMethod);
}

void CoilDXASHRAE205Performance::resetPerformanceInterpolationMethod() {
  getImpl<detail::CoilDXASHRAE205Performance_Impl>()->resetPerformanceInterpolationMethod();
}

boost::optional<double> CoilDXASHRAE205Performance::ratedTotalCoolingCapacity() const {
  return getImpl<detail::CoilDXASHRAE205Performance_Impl>()->ratedTotalCoolingCapacity();
}

bool CoilDXASHRAE205Performance::isRatedTotalCoolingCapacityAutosized() const {
  return getImpl<detail::CoilDXASHRAE205Performance_Impl>()->isRatedTotalCoolingCapacityAutosized();
}

bool CoilDXASHRAE205Performance::setRatedTotalCoolingCapacity(double ratedTotalCoolingCapacity) {
  return getImpl<detail::CoilDXASHRAE205Performance_Impl>()->setRatedTotalCoolingCapacity(ratedTotalCoolingCapacity);
}

void CoilDXASHRAE205Performance::resetRatedTotalCoolingCapacity() {
  getImpl<detail::CoilDXASHRAE205Performance_Impl>()->resetRatedTotalCoolingCapacity();
}

void CoilDXASHRAE205Performance::autosizeRatedTotalCoolingCapacity() {
  getImpl<detail::CoilDXASHRAE205Performance_Impl>()->autosizeRatedTotalCoolingCapacity();
}

boost::optional<double> CoilDXASHRAE205Performance::ratedSteadyStateHeatingCapacity() const {
  return getImpl<detail::CoilDXASHRAE205Performance_Impl>()->ratedSteadyStateHeatingCapacity();
}

bool CoilDXASHRAE205Performance::isRatedSteadyStateHeatingCapacityAutosized() const {
  return getImpl<detail::CoilDXASHRAE205Performance_Impl>()->isRatedSteadyStateHeatingCapacityAutosized();
}

bool CoilDXASHRAE205Performance::setRatedSteadyStateHeatingCapacity(double ratedSteadyStateHeatingCapacity) {
  return getImpl<detail::CoilDXASHRAE205Performance_Impl>()->setRatedSteadyStateHeatingCapacity(ratedSteadyStateHeatingCapacity);
}

void CoilDXASHRAE205Performance::resetRatedSteadyStateHeatingCapacity() {
  getImpl<detail::CoilDXASHRAE205Performance_Impl>()->resetRatedSteadyStateHeatingCapacity();
}

void CoilDXASHRAE205Performance::autosizeRatedSteadyStateHeatingCapacity() {
  getImpl<detail::CoilDXASHRAE205Performance_Impl>()->autosizeRatedSteadyStateHeatingCapacity();
}

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
namespace detail {

std::string CoilDXASHRAE205Performance_Impl::representationFileName() const {
  const auto value = getString(openstudio::Coil_DX_ASHRAE205_PerformanceFields::RepresentationFileName, true);
  OS_ASSERT(value);
  return *value;
}

bool CoilDXASHRAE205Performance_Impl::setRepresentationFileName(const std::string& representationFileName) {
  const bool result = setString(openstudio::Coil_DX_ASHRAE205_PerformanceFields::RepresentationFileName, representationFileName);
  OS_ASSERT(result);
  return result;
}

std::string CoilDXASHRAE205Performance_Impl::performanceInterpolationMethod() const {
  const auto value = getString(openstudio::Coil_DX_ASHRAE205_PerformanceFields::PerformanceInterpolationMethod, true);
  OS_ASSERT(value);
  return *value;
}

bool CoilDXASHRAE205Performance_Impl::isPerformanceInterpolationMethodDefaulted() const {
  return isEmpty(openstudio::Coil_DX_ASHRAE205_PerformanceFields::PerformanceInterpolationMethod);
}

bool CoilDXASHRAE205Performance_Impl::setPerformanceInterpolationMethod(const std::string& performanceInterpolationMethod) {
  return setString(openstudio::Coil_DX_ASHRAE205_PerformanceFields::PerformanceInterpolationMethod, performanceInterpolationMethod);
}

void CoilDXASHRAE205Performance_Impl::resetPerformanceInterpolationMethod() {
  OS_ASSERT(setString(openstudio::Coil_DX_ASHRAE205_PerformanceFields::PerformanceInterpolationMethod, ""));
}

boost::optional<double> CoilDXASHRAE205Performance_Impl::ratedTotalCoolingCapacity() const {
  return getDouble(openstudio::Coil_DX_ASHRAE205_PerformanceFields::RatedTotalCoolingCapacity, true);
}

bool CoilDXASHRAE205Performance_Impl::isRatedTotalCoolingCapacityAutosized() const {
  if (const auto value = getString(openstudio::Coil_DX_ASHRAE205_PerformanceFields::RatedTotalCoolingCapacity, true)) {
    return openstudio::istringEqual(*value, "autosize");
  }
  return false;
}

bool CoilDXASHRAE205Performance_Impl::setRatedTotalCoolingCapacity(double ratedTotalCoolingCapacity) {
  return setDouble(openstudio::Coil_DX_ASHRAE205_PerformanceFields::RatedTotalCoolingCapacity, ratedTotalCoolingCapacity);
}

void CoilDXASHRAE205Performance_Impl::resetRatedTotalCoolingCapacity() {
  OS_ASSERT(setString(openstudio::Coil_DX_ASHRAE205_PerformanceFields::RatedTotalCoolingCapacity, ""));
}

void CoilDXASHRAE205Performance_Impl::autosizeRatedTotalCoolingCapacity() {
  OS_ASSERT(setString(openstudio::Coil_DX_ASHRAE205_PerformanceFields::RatedTotalCoolingCapacity, "autosize"));
}

boost::optional<double> CoilDXASHRAE205Performance_Impl::ratedSteadyStateHeatingCapacity() const {
  return getDouble(openstudio::Coil_DX_ASHRAE205_PerformanceFields::RatedSteadyStateHeatingCapacity, true);
}

bool CoilDXASHRAE205Performance_Impl::isRatedSteadyStateHeatingCapacityAutosized() const {
  if (const auto value = getString(openstudio::Coil_DX_ASHRAE205_PerformanceFields::RatedSteadyStateHeatingCapacity, true)) {
    return openstudio::istringEqual(*value, "autosize");
  }
  return false;
}

bool CoilDXASHRAE205Performance_Impl::setRatedSteadyStateHeatingCapacity(double ratedSteadyStateHeatingCapacity) {
  return setDouble(openstudio::Coil_DX_ASHRAE205_PerformanceFields::RatedSteadyStateHeatingCapacity, ratedSteadyStateHeatingCapacity);
}

void CoilDXASHRAE205Performance_Impl::resetRatedSteadyStateHeatingCapacity() {
  OS_ASSERT(setString(openstudio::Coil_DX_ASHRAE205_PerformanceFields::RatedSteadyStateHeatingCapacity, ""));
}

void CoilDXASHRAE205Performance_Impl::autosizeRatedSteadyStateHeatingCapacity() {
  OS_ASSERT(setString(openstudio::Coil_DX_ASHRAE205_PerformanceFields::RatedSteadyStateHeatingCapacity, "autosize"));
}

std::vector<std::string> CoilDXASHRAE205Performance_Impl::performanceInterpolationMethodValues() const {
  return openstudio::epmodel::CoilDXASHRAE205Performance::performanceInterpolationMethodValues();
}

}  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
