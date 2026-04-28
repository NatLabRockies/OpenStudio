/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "StraightComponent/SolarCollectorFlatPlateWater.hpp"
#include "StraightComponent/SolarCollectorFlatPlateWater_Impl.hpp"

#include "Loop/PlantLoop.hpp"
#include "Model.hpp"
#include "ModelObject/SolarCollectorPerformanceFlatPlate.hpp"
#include "ModelObject/SolarCollectorPerformanceFlatPlate_Impl.hpp"
#include "StraightComponent/Node.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/idd/IddEnums.hxx>
#include <utilities/idd/SolarCollector_FlatPlate_Water_FieldEnums.hxx>

namespace openstudio {
namespace epmodel {

SolarCollectorFlatPlateWater::SolarCollectorFlatPlateWater(const Model& model)
  : StraightComponent(SolarCollectorFlatPlateWater::iddObjectType(), model) {
  SolarCollectorPerformanceFlatPlate performance(model);
  const bool ok = getImpl<detail::SolarCollectorFlatPlateWater_Impl>()->setSolarCollectorPerformanceNoClone(performance);
  OS_ASSERT(ok);
}

SolarCollectorFlatPlateWater::SolarCollectorFlatPlateWater(std::shared_ptr<detail::SolarCollectorFlatPlateWater_Impl> impl)
  : StraightComponent(std::move(impl)) {}

IddObjectType SolarCollectorFlatPlateWater::iddObjectType() {
  return IddObjectType::SolarCollector_FlatPlate_Water;
}

SolarCollectorPerformanceFlatPlate SolarCollectorFlatPlateWater::solarCollectorPerformance() const {
  return getImpl<detail::SolarCollectorFlatPlateWater_Impl>()->solarCollectorPerformance();
}

bool SolarCollectorFlatPlateWater::setSolarCollectorPerformance(const SolarCollectorPerformanceFlatPlate& solarCollectorPerformanceFlatPlate) {
  return getImpl<detail::SolarCollectorFlatPlateWater_Impl>()->setSolarCollectorPerformance(solarCollectorPerformanceFlatPlate);
}

void SolarCollectorFlatPlateWater::resetSolarCollectorPerformance() {
  getImpl<detail::SolarCollectorFlatPlateWater_Impl>()->resetSolarCollectorPerformance();
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

std::vector<ModelObject> SolarCollectorFlatPlateWater_Impl::children() const {
  return {solarCollectorPerformance()};
}

unsigned SolarCollectorFlatPlateWater_Impl::inletPort() const {
  return openstudio::SolarCollector_FlatPlate_WaterFields::InletNodeName;
}

unsigned SolarCollectorFlatPlateWater_Impl::outletPort() const {
  return openstudio::SolarCollector_FlatPlate_WaterFields::OutletNodeName;
}

bool SolarCollectorFlatPlateWater_Impl::addToNode(Node& node) {
  if (auto plantLoop = node.plantLoop()) {
    if (plantLoop->supplyComponent(node.handle())) {
      return StraightComponent_Impl::addToNode(node);
    }
  }

  return false;
}

std::vector<IdfObject> SolarCollectorFlatPlateWater_Impl::remove() {
  auto performance = getObject<ModelObject>().getModelObjectTarget<SolarCollectorPerformanceFlatPlate>(
    openstudio::SolarCollector_FlatPlate_WaterFields::SolarCollectorPerformanceName);
  auto result = StraightComponent_Impl::remove();
  if (!result.empty() && performance) {
    performance->remove();
  }
  return result;
}

SolarCollectorPerformanceFlatPlate SolarCollectorFlatPlateWater_Impl::solarCollectorPerformance() const {
  auto value = getObject<ModelObject>().getModelObjectTarget<SolarCollectorPerformanceFlatPlate>(
    openstudio::SolarCollector_FlatPlate_WaterFields::SolarCollectorPerformanceName);
  if (!value) {
    LOG_AND_THROW(briefDescription() << " does not have a Solar Collector Performance attached.");
  }
  return *value;
}

bool SolarCollectorFlatPlateWater_Impl::setSolarCollectorPerformance(
  const SolarCollectorPerformanceFlatPlate& solarCollectorPerformanceFlatPlate) {
  auto current = getObject<ModelObject>().getModelObjectTarget<SolarCollectorPerformanceFlatPlate>(
    openstudio::SolarCollector_FlatPlate_WaterFields::SolarCollectorPerformanceName);
  if (current && (*current == solarCollectorPerformanceFlatPlate)) {
    return true;
  }

  auto clonedObject = model().addObject(solarCollectorPerformanceFlatPlate.clone());
  if (!clonedObject) {
    return false;
  }

  auto clonedPerformance = clonedObject->cast<SolarCollectorPerformanceFlatPlate>();
  if (!setSolarCollectorPerformanceNoClone(clonedPerformance)) {
    clonedPerformance.remove();
    return false;
  }

  if (current) {
    current->remove();
  }
  return true;
}

void SolarCollectorFlatPlateWater_Impl::resetSolarCollectorPerformance() {
  auto current = getObject<ModelObject>().getModelObjectTarget<SolarCollectorPerformanceFlatPlate>(
    openstudio::SolarCollector_FlatPlate_WaterFields::SolarCollectorPerformanceName);
  if (current) {
    current->remove();
  }

  SolarCollectorPerformanceFlatPlate performance(model());
  const bool ok = setSolarCollectorPerformanceNoClone(performance);
  OS_ASSERT(ok);
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

bool SolarCollectorFlatPlateWater_Impl::setSolarCollectorPerformanceNoClone(
  const SolarCollectorPerformanceFlatPlate& solarCollectorPerformanceFlatPlate) {
  return setPointer(openstudio::SolarCollector_FlatPlate_WaterFields::SolarCollectorPerformanceName,
                    solarCollectorPerformanceFlatPlate.handle());
}

}  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
