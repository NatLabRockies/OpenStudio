/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "StraightComponent/SolarCollectorFlatPlateWater.hpp"
#include "StraightComponent/SolarCollectorFlatPlateWater_Impl.hpp"

#include "Model.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/idd/IddEnums.hxx>
#include <utilities/idd/SolarCollector_FlatPlate_Water_FieldEnums.hxx>

namespace openstudio {
namespace epmodel {

SolarCollectorFlatPlateWater::SolarCollectorFlatPlateWater(const Model& model)
  : StraightComponent(SolarCollectorFlatPlateWater::iddObjectType(), model) {}

SolarCollectorFlatPlateWater::SolarCollectorFlatPlateWater(std::shared_ptr<detail::SolarCollectorFlatPlateWater_Impl> impl)
  : StraightComponent(std::move(impl)) {}

IddObjectType SolarCollectorFlatPlateWater::iddObjectType() {
  return IddObjectType::SolarCollector_FlatPlate_Water;
}

boost::optional<double> SolarCollectorFlatPlateWater::maximumFlowRate() const {
  return getImpl<detail::SolarCollectorFlatPlateWater_Impl>()->maximumFlowRate();
}

bool SolarCollectorFlatPlateWater::setMaximumFlowRate(double maximumFlowRate) {
  return getImpl<detail::SolarCollectorFlatPlateWater_Impl>()->setMaximumFlowRate(maximumFlowRate);
}

void SolarCollectorFlatPlateWater::resetMaximumFlowRate() {
  getImpl<detail::SolarCollectorFlatPlateWater_Impl>()->resetMaximumFlowRate();
}

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
namespace detail {

unsigned SolarCollectorFlatPlateWater_Impl::inletPort() const {
  return openstudio::SolarCollector_FlatPlate_WaterFields::InletNodeName;
}

unsigned SolarCollectorFlatPlateWater_Impl::outletPort() const {
  return openstudio::SolarCollector_FlatPlate_WaterFields::OutletNodeName;
}

boost::optional<double> SolarCollectorFlatPlateWater_Impl::maximumFlowRate() const {
  return getDouble(openstudio::SolarCollector_FlatPlate_WaterFields::MaximumFlowRate, true);
}

bool SolarCollectorFlatPlateWater_Impl::setMaximumFlowRate(double maximumFlowRate) {
  return setDouble(openstudio::SolarCollector_FlatPlate_WaterFields::MaximumFlowRate, maximumFlowRate);
}

void SolarCollectorFlatPlateWater_Impl::resetMaximumFlowRate() {
  OS_ASSERT(setString(openstudio::SolarCollector_FlatPlate_WaterFields::MaximumFlowRate, ""));
}

}  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
