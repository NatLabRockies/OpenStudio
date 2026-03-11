/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "WaterToWaterComponent/CentralHeatPumpSystem.hpp"
#include "WaterToWaterComponent/CentralHeatPumpSystem_Impl.hpp"

#include "Model.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/idd/CentralHeatPumpSystem_FieldEnums.hxx>
#include <utilities/idd/IddEnums.hxx>
#include <utilities/idd/IddFactory.hxx>

namespace openstudio {
namespace epmodel {

CentralHeatPumpSystem::CentralHeatPumpSystem(const Model& model) : ModelObject(CentralHeatPumpSystem::iddObjectType(), model) {
  // Keep required scalar fields populated for strict non-optional getters.
  OS_ASSERT(setControlMethod("SmartMixing"));
  OS_ASSERT(setAncillaryPower(0.0));
}

CentralHeatPumpSystem::CentralHeatPumpSystem(std::shared_ptr<detail::CentralHeatPumpSystem_Impl> impl) : ModelObject(std::move(impl)) {}

IddObjectType CentralHeatPumpSystem::iddObjectType() {
  return IddObjectType::CentralHeatPumpSystem;
}

std::vector<std::string> CentralHeatPumpSystem::controlMethodValues() {
  return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(), openstudio::CentralHeatPumpSystemFields::ControlMethod);
}

std::string CentralHeatPumpSystem::controlMethod() const {
  return getImpl<detail::CentralHeatPumpSystem_Impl>()->controlMethod();
}

bool CentralHeatPumpSystem::setControlMethod(const std::string& controlMethod) {
  return getImpl<detail::CentralHeatPumpSystem_Impl>()->setControlMethod(controlMethod);
}

double CentralHeatPumpSystem::ancillaryPower() const {
  return getImpl<detail::CentralHeatPumpSystem_Impl>()->ancillaryPower();
}

bool CentralHeatPumpSystem::setAncillaryPower(double ancillaryPower) {
  return getImpl<detail::CentralHeatPumpSystem_Impl>()->setAncillaryPower(ancillaryPower);
}

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
namespace detail {

std::string CentralHeatPumpSystem_Impl::controlMethod() const {
  const auto value = getString(openstudio::CentralHeatPumpSystemFields::ControlMethod, true);
  OS_ASSERT(value);
  return *value;
}

bool CentralHeatPumpSystem_Impl::setControlMethod(const std::string& controlMethod) {
  return setString(openstudio::CentralHeatPumpSystemFields::ControlMethod, controlMethod);
}

double CentralHeatPumpSystem_Impl::ancillaryPower() const {
  const auto value = getDouble(openstudio::CentralHeatPumpSystemFields::AncillaryPower, true);
  OS_ASSERT(value);
  return *value;
}

bool CentralHeatPumpSystem_Impl::setAncillaryPower(double ancillaryPower) {
  return setDouble(openstudio::CentralHeatPumpSystemFields::AncillaryPower, ancillaryPower);
}

std::vector<std::string> CentralHeatPumpSystem_Impl::controlMethodValues() const {
  return openstudio::epmodel::CentralHeatPumpSystem::controlMethodValues();
}

}  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
