/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "StraightComponent/DistrictHeatingWater.hpp"
#include "StraightComponent/DistrictHeatingWater_Impl.hpp"

#include "Model.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/core/StringHelpers.hpp>
#include <utilities/idd/DistrictHeating_Water_FieldEnums.hxx>
#include <utilities/idd/IddEnums.hxx>

namespace openstudio {
namespace epmodel {

DistrictHeatingWater::DistrictHeatingWater(const Model& model) : StraightComponent(DistrictHeatingWater::iddObjectType(), model) {
  autosizeNominalCapacity();
}

DistrictHeatingWater::DistrictHeatingWater(std::shared_ptr<detail::DistrictHeatingWater_Impl> impl) : StraightComponent(std::move(impl)) {}

IddObjectType DistrictHeatingWater::iddObjectType() {
  return IddObjectType::DistrictHeating_Water;
}

boost::optional<double> DistrictHeatingWater::nominalCapacity() const {
  return getImpl<detail::DistrictHeatingWater_Impl>()->nominalCapacity();
}

bool DistrictHeatingWater::isNominalCapacityAutosized() const {
  return getImpl<detail::DistrictHeatingWater_Impl>()->isNominalCapacityAutosized();
}

bool DistrictHeatingWater::setNominalCapacity(double nominalCapacity) {
  return getImpl<detail::DistrictHeatingWater_Impl>()->setNominalCapacity(nominalCapacity);
}

void DistrictHeatingWater::autosizeNominalCapacity() {
  getImpl<detail::DistrictHeatingWater_Impl>()->autosizeNominalCapacity();
}

boost::optional<double> DistrictHeatingWater::autosizedNominalCapacity() const {
  return getImpl<detail::DistrictHeatingWater_Impl>()->autosizedNominalCapacity();
}

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
namespace detail {

unsigned DistrictHeatingWater_Impl::inletPort() const {
  return openstudio::DistrictHeating_WaterFields::HotWaterInletNodeName;
}

unsigned DistrictHeatingWater_Impl::outletPort() const {
  return openstudio::DistrictHeating_WaterFields::HotWaterOutletNodeName;
}

boost::optional<double> DistrictHeatingWater_Impl::nominalCapacity() const {
  return getDouble(openstudio::DistrictHeating_WaterFields::NominalCapacity, true);
}

bool DistrictHeatingWater_Impl::isNominalCapacityAutosized() const {
  if (auto value = getString(openstudio::DistrictHeating_WaterFields::NominalCapacity, true)) {
    return openstudio::istringEqual(*value, "autosize");
  }
  return false;
}

bool DistrictHeatingWater_Impl::setNominalCapacity(double nominalCapacity) {
  return setDouble(openstudio::DistrictHeating_WaterFields::NominalCapacity, nominalCapacity);
}

void DistrictHeatingWater_Impl::autosizeNominalCapacity() {
  OS_ASSERT(setString(openstudio::DistrictHeating_WaterFields::NominalCapacity, "Autosize"));
}

boost::optional<double> DistrictHeatingWater_Impl::autosizedNominalCapacity() const {
  // epmodel does not currently resolve autosized values from SQL results.
  return boost::none;
}

}  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
