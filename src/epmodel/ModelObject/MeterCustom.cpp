/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "MeterCustom.hpp"
#include "MeterCustom_Impl.hpp"

#include "Model.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/idd/IddEnums.hxx>
#include <utilities/idd/IddFactory.hxx>
#include <utilities/idd/IddObject.hpp>
#include <utilities/idd/Meter_Custom_FieldEnums.hxx>

namespace openstudio {
namespace epmodel {

MeterCustom::MeterCustom(const Model& model) : ModelObject(MeterCustom::iddObjectType(), model) {
  // Preserve model counterpart constructor behavior for this scalar field.
  OS_ASSERT(setFuelType("Electricity"));
}

MeterCustom::MeterCustom(std::shared_ptr<detail::MeterCustom_Impl> impl) : ModelObject(std::move(impl)) {}

IddObjectType MeterCustom::iddObjectType() {
  return IddObjectType::Meter_Custom;
}

std::vector<std::string> MeterCustom::fuelTypeValues() {
  return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(), openstudio::Meter_CustomFields::ResourceType);
}

boost::optional<std::string> MeterCustom::fuelType() const {
  return getImpl<detail::MeterCustom_Impl>()->fuelType();
}

bool MeterCustom::setFuelType(const std::string& fuelType) {
  return getImpl<detail::MeterCustom_Impl>()->setFuelType(fuelType);
}

void MeterCustom::resetFuelType() {
  getImpl<detail::MeterCustom_Impl>()->resetFuelType();
}

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
namespace detail {

boost::optional<std::string> MeterCustom_Impl::fuelType() const {
  if (isEmpty(openstudio::Meter_CustomFields::ResourceType)) {
    return boost::none;
  }
  return getString(openstudio::Meter_CustomFields::ResourceType, true);
}

bool MeterCustom_Impl::setFuelType(const std::string& fuelType) {
  return setString(openstudio::Meter_CustomFields::ResourceType, fuelType);
}

void MeterCustom_Impl::resetFuelType() {
  OS_ASSERT(setString(openstudio::Meter_CustomFields::ResourceType, ""));
}

std::vector<std::string> MeterCustom_Impl::fuelTypeValues() const {
  return openstudio::epmodel::MeterCustom::fuelTypeValues();
}

}  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
