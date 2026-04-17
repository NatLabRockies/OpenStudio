/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "StraightComponent/DistrictHeatingWater.hpp"
#include "StraightComponent/DistrictHeatingWater_Impl.hpp"

#include "Loop/PlantLoop.hpp"
#include "Model.hpp"
#include "Schedule/Schedule.hpp"
#include "Schedule/Schedule_Impl.hpp"
#include "StraightComponent/Node.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/core/StringHelpers.hpp>
#include <utilities/idd/DistrictHeating_Water_FieldEnums.hxx>
#include <utilities/idd/IddEnums.hxx>

namespace openstudio {
namespace epmodel {

DistrictHeatingWater::DistrictHeatingWater(const Model& model) : StraightComponent(DistrictHeatingWater::iddObjectType(), model) {
  autosizeNominalCapacity();

  auto capacityFractionSchedule = model.alwaysOnContinuousSchedule();
  OS_ASSERT(getImpl<detail::DistrictHeatingWater_Impl>()->setCapacityFractionSchedule(capacityFractionSchedule));
}

DistrictHeatingWater::DistrictHeatingWater(std::shared_ptr<detail::DistrictHeatingWater_Impl> impl) : StraightComponent(std::move(impl)) {}

IddObjectType DistrictHeatingWater::iddObjectType() {
  return IddObjectType::DistrictHeating_Water;
}

boost::optional<double> DistrictHeatingWater::nominalCapacity() const {
  return getImpl<detail::DistrictHeatingWater_Impl>()->nominalCapacity();
}

Schedule DistrictHeatingWater::capacityFractionSchedule() const {
  return getImpl<detail::DistrictHeatingWater_Impl>()->capacityFractionSchedule();
}

bool DistrictHeatingWater::isNominalCapacityAutosized() const {
  return getImpl<detail::DistrictHeatingWater_Impl>()->isNominalCapacityAutosized();
}

bool DistrictHeatingWater::setNominalCapacity(double nominalCapacity) {
  return getImpl<detail::DistrictHeatingWater_Impl>()->setNominalCapacity(nominalCapacity);
}

bool DistrictHeatingWater::setCapacityFractionSchedule(Schedule& schedule) {
  return getImpl<detail::DistrictHeatingWater_Impl>()->setCapacityFractionSchedule(schedule);
}

void DistrictHeatingWater::autosizeNominalCapacity() {
  getImpl<detail::DistrictHeatingWater_Impl>()->autosizeNominalCapacity();
}

bool DistrictHeatingWater::addToNode(Node& node) {
  return getImpl<detail::DistrictHeatingWater_Impl>()->addToNode(node);
}

boost::optional<double> DistrictHeatingWater::autosizedNominalCapacity() const {
  return getImpl<detail::DistrictHeatingWater_Impl>()->autosizedNominalCapacity();
}

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
namespace detail {

bool DistrictHeatingWater_Impl::addToNode(Node& node) {
  if (auto plant = node.plantLoop()) {
    if (plant->supplyComponent(node.handle())) {
      return StraightComponent_Impl::addToNode(node);
    }
  }

  return false;
}

unsigned DistrictHeatingWater_Impl::inletPort() const {
  return openstudio::DistrictHeating_WaterFields::HotWaterInletNodeName;
}

unsigned DistrictHeatingWater_Impl::outletPort() const {
  return openstudio::DistrictHeating_WaterFields::HotWaterOutletNodeName;
}

boost::optional<double> DistrictHeatingWater_Impl::nominalCapacity() const {
  return getDouble(openstudio::DistrictHeating_WaterFields::NominalCapacity, true);
}

Schedule DistrictHeatingWater_Impl::capacityFractionSchedule() const {
  auto schedule = getObject<ModelObject>().getModelObjectTarget<Schedule>(openstudio::DistrictHeating_WaterFields::CapacityFractionScheduleName);
  OS_ASSERT(schedule);
  return *schedule;
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

bool DistrictHeatingWater_Impl::setCapacityFractionSchedule(Schedule& schedule) {
  return setSchedule(openstudio::DistrictHeating_WaterFields::CapacityFractionScheduleName, "DistrictHeatingWater", "Capacity Fraction", schedule);
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
