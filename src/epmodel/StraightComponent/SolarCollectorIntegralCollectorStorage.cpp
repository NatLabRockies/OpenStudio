/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "StraightComponent/SolarCollectorIntegralCollectorStorage.hpp"
#include "StraightComponent/SolarCollectorIntegralCollectorStorage_Impl.hpp"

#include "Model.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/idd/IddEnums.hxx>
#include <utilities/idd/IddFactory.hxx>
#include <utilities/idd/SolarCollector_IntegralCollectorStorage_FieldEnums.hxx>

namespace openstudio {
namespace epmodel {

SolarCollectorIntegralCollectorStorage::SolarCollectorIntegralCollectorStorage(const Model& model)
  : StraightComponent(SolarCollectorIntegralCollectorStorage::iddObjectType(), model) {}

SolarCollectorIntegralCollectorStorage::SolarCollectorIntegralCollectorStorage(
  std::shared_ptr<detail::SolarCollectorIntegralCollectorStorage_Impl> impl)
  : StraightComponent(std::move(impl)) {}

IddObjectType SolarCollectorIntegralCollectorStorage::iddObjectType() {
  return IddObjectType::SolarCollector_IntegralCollectorStorage;
}

std::vector<std::string> SolarCollectorIntegralCollectorStorage::bottomSurfaceBoundaryConditionsTypeValues() {
  return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(),
                        openstudio::SolarCollector_IntegralCollectorStorageFields::BottomSurfaceBoundaryConditionsType);
}

std::string SolarCollectorIntegralCollectorStorage::bottomSurfaceBoundaryConditionsType() const {
  return getImpl<detail::SolarCollectorIntegralCollectorStorage_Impl>()->bottomSurfaceBoundaryConditionsType();
}

bool SolarCollectorIntegralCollectorStorage::isBottomSurfaceBoundaryConditionsTypeDefaulted() const {
  return getImpl<detail::SolarCollectorIntegralCollectorStorage_Impl>()->isBottomSurfaceBoundaryConditionsTypeDefaulted();
}

boost::optional<double> SolarCollectorIntegralCollectorStorage::maximumFlowRate() const {
  return getImpl<detail::SolarCollectorIntegralCollectorStorage_Impl>()->maximumFlowRate();
}

bool SolarCollectorIntegralCollectorStorage::setMaximumFlowRate(double maximumFlowRate) {
  return getImpl<detail::SolarCollectorIntegralCollectorStorage_Impl>()->setMaximumFlowRate(maximumFlowRate);
}

void SolarCollectorIntegralCollectorStorage::resetMaximumFlowRate() {
  getImpl<detail::SolarCollectorIntegralCollectorStorage_Impl>()->resetMaximumFlowRate();
}

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
namespace detail {

unsigned SolarCollectorIntegralCollectorStorage_Impl::inletPort() const {
  return openstudio::SolarCollector_IntegralCollectorStorageFields::InletNodeName;
}

unsigned SolarCollectorIntegralCollectorStorage_Impl::outletPort() const {
  return openstudio::SolarCollector_IntegralCollectorStorageFields::OutletNodeName;
}

std::string SolarCollectorIntegralCollectorStorage_Impl::bottomSurfaceBoundaryConditionsType() const {
  auto value = getString(openstudio::SolarCollector_IntegralCollectorStorageFields::BottomSurfaceBoundaryConditionsType, true);
  OS_ASSERT(value);
  return *value;
}

bool SolarCollectorIntegralCollectorStorage_Impl::isBottomSurfaceBoundaryConditionsTypeDefaulted() const {
  return isEmpty(openstudio::SolarCollector_IntegralCollectorStorageFields::BottomSurfaceBoundaryConditionsType);
}

boost::optional<double> SolarCollectorIntegralCollectorStorage_Impl::maximumFlowRate() const {
  return getDouble(openstudio::SolarCollector_IntegralCollectorStorageFields::MaximumFlowRate, true);
}

bool SolarCollectorIntegralCollectorStorage_Impl::setMaximumFlowRate(double maximumFlowRate) {
  return setDouble(openstudio::SolarCollector_IntegralCollectorStorageFields::MaximumFlowRate, maximumFlowRate);
}

void SolarCollectorIntegralCollectorStorage_Impl::resetMaximumFlowRate() {
  OS_ASSERT(setString(openstudio::SolarCollector_IntegralCollectorStorageFields::MaximumFlowRate, ""));
}

std::vector<std::string> SolarCollectorIntegralCollectorStorage_Impl::bottomSurfaceBoundaryConditionsTypeValues() const {
  return openstudio::epmodel::SolarCollectorIntegralCollectorStorage::bottomSurfaceBoundaryConditionsTypeValues();
}

}  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
