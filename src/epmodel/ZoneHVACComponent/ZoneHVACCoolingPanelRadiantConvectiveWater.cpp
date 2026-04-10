/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "ZoneHVACComponent/ZoneHVACCoolingPanelRadiantConvectiveWater.hpp"
#include "ZoneHVACComponent/ZoneHVACCoolingPanelRadiantConvectiveWater_Impl.hpp"

#include "Model.hpp"
#include "HVACComponent/HVACComponent.hpp"
#include "HVACComponent/ThermalZone.hpp"
#include "HVACComponent/ThermalZone_Impl.hpp"
#include "ModelObject/ModelObject.hpp"
#include "PlanarSurface/Surface.hpp"
#include "PlanarSurface/Surface_Impl.hpp"
#include "PlanarSurfaceGroup/Space.hpp"
#include "PlanarSurfaceGroup/Space_Impl.hpp"
#include "Schedule/Schedule.hpp"
#include "Schedule/ScheduleConstant.hpp"
#include "Schedule/Schedule_Impl.hpp"
#include "StraightComponent/CoilCoolingWaterPanelRadiant.hpp"
#include "StraightComponent/CoilCoolingWaterPanelRadiant_Impl.hpp"
#include "StraightComponent/Node.hpp"

#include "../utilities/core/Assert.hpp"

#include <utilities/geometry/Geometry.hpp>
#include <utilities/geometry/Point3d.hpp>
#include <utilities/idd/BuildingSurface_Detailed_FieldEnums.hxx>
#include <utilities/idd/IddEnums.hxx>
#include <utilities/idd/ZoneHVAC_CoolingPanel_RadiantConvective_Water_FieldEnums.hxx>
#include <utilities/idf/WorkspaceExtensibleGroup.hpp>

namespace openstudio {
namespace epmodel {
namespace detail {

constexpr double kDefaultFractionRadiant = 0.65;
constexpr double kDefaultFractionofRadiantEnergyIncidentonPeople = 0.2;

using PanelFields = openstudio::ZoneHVAC_CoolingPanel_RadiantConvective_WaterFields;
using PanelExtensibleFields = openstudio::ZoneHVAC_CoolingPanel_RadiantConvective_WaterExtensibleFields;
using SurfaceFields = openstudio::BuildingSurface_DetailedFields;
using SurfaceVertexFields = openstudio::BuildingSurface_DetailedExtensibleFields;

std::string transientCoolingCoilName(const openstudio::epmodel::ZoneHVACCoolingPanelRadiantConvectiveWater& parent) {
  return "__transient__" + openstudio::toString(parent.handle()) + "__cooling_water_panel_radiant";
}

static std::vector<openstudio::Point3d> surfaceVertices(const openstudio::epmodel::Surface& surface) {
  std::vector<openstudio::Point3d> result;
  for (const auto& group : surface.extensibleGroups()) {
    auto x = group.getDouble(SurfaceVertexFields::VertexXcoordinate, true);
    auto y = group.getDouble(SurfaceVertexFields::VertexYcoordinate, true);
    auto z = group.getDouble(SurfaceVertexFields::VertexZcoordinate, true);
    if (!x || !y || !z) {
      return {};
    }
    result.emplace_back(*x, *y, *z);
  }
  return result;
}

static double surfaceGrossArea(const openstudio::epmodel::Surface& surface) {
  const auto vertices = surfaceVertices(surface);
  if (vertices.size() < 3u) {
    return 0.0;
  }
  if (const auto area = openstudio::getArea(vertices)) {
    return *area;
  }
  return 0.0;
}

static bool isFloorSurface(const openstudio::epmodel::Surface& surface) {
  return openstudio::istringEqual(surface.surfaceType(), "Floor");
}

static bool isCeilingSurface(const openstudio::epmodel::Surface& surface) {
  const auto surfaceType = surface.surfaceType();
  return openstudio::istringEqual(surfaceType, "RoofCeiling") || openstudio::istringEqual(surfaceType, "Roof")
         || openstudio::istringEqual(surfaceType, "Ceiling");
}

}  // namespace detail

ZoneHVACCoolingPanelRadiantConvectiveWater::ZoneHVACCoolingPanelRadiantConvectiveWater(const Model& model)
  : ZoneHVACComponent(ZoneHVACCoolingPanelRadiantConvectiveWater::iddObjectType(), model) {
  auto impl = getImpl<detail::ZoneHVACCoolingPanelRadiantConvectiveWater_Impl>();
  OS_ASSERT(impl);

  ScheduleConstant alwaysOn(model);
  OS_ASSERT(alwaysOn.setValue(1.0));
  OS_ASSERT(setAvailabilitySchedule(alwaysOn));
  OS_ASSERT(setFractionRadiant(detail::kDefaultFractionRadiant));
  OS_ASSERT(setFractionofRadiantEnergyIncidentonPeople(detail::kDefaultFractionofRadiantEnergyIncidentonPeople));

  // Canonical OpenStudio gives this parent a cooling-coil child with these
  // defaults. EnergyPlus flattens that child state onto the parent object, so
  // the epmodel parent constructor seeds the persisted parent fields directly.
  OS_ASSERT(impl->setRatedInletWaterTemperature(5.0));
  OS_ASSERT(impl->setRatedInletSpaceTemperature(24.0));
  OS_ASSERT(impl->setRatedWaterMassFlowRate(0.063));
  OS_ASSERT(impl->setCoolingDesignCapacityMethod("CoolingDesignCapacity"));
  impl->autosizeCoolingDesignCapacity();
  OS_ASSERT(impl->setCoolingDesignCapacityPerFloorArea(0.0));
  OS_ASSERT(impl->setFractionOfAutosizedCoolingDesignCapacity(1.0));
  impl->autosizeMaximumChilledWaterFlowRate();
  OS_ASSERT(impl->setControlType("MeanAirTemperature"));
  OS_ASSERT(impl->setCoolingControlThrottlingRange(0.5));
  OS_ASSERT(impl->setCondensationControlType("SimpleOff"));
  OS_ASSERT(impl->setCondensationControlDewpointOffset(1.0));
}

ZoneHVACCoolingPanelRadiantConvectiveWater::ZoneHVACCoolingPanelRadiantConvectiveWater(
  std::shared_ptr<detail::ZoneHVACCoolingPanelRadiantConvectiveWater_Impl> impl)
  : ZoneHVACComponent(std::move(impl)) {}

IddObjectType ZoneHVACCoolingPanelRadiantConvectiveWater::iddObjectType() {
  return IddObjectType::ZoneHVAC_CoolingPanel_RadiantConvective_Water;
}

Schedule ZoneHVACCoolingPanelRadiantConvectiveWater::availabilitySchedule() const {
  return getImpl<detail::ZoneHVACCoolingPanelRadiantConvectiveWater_Impl>()->availabilitySchedule();
}

bool ZoneHVACCoolingPanelRadiantConvectiveWater::setAvailabilitySchedule(Schedule& schedule) {
  return getImpl<detail::ZoneHVACCoolingPanelRadiantConvectiveWater_Impl>()->setAvailabilitySchedule(schedule);
}

void ZoneHVACCoolingPanelRadiantConvectiveWater::resetAvailabilitySchedule() {
  getImpl<detail::ZoneHVACCoolingPanelRadiantConvectiveWater_Impl>()->resetAvailabilitySchedule();
}

double ZoneHVACCoolingPanelRadiantConvectiveWater::fractionRadiant() const {
  return getImpl<detail::ZoneHVACCoolingPanelRadiantConvectiveWater_Impl>()->fractionRadiant();
}

bool ZoneHVACCoolingPanelRadiantConvectiveWater::setFractionRadiant(double fractionRadiant) {
  return getImpl<detail::ZoneHVACCoolingPanelRadiantConvectiveWater_Impl>()->setFractionRadiant(fractionRadiant);
}

double ZoneHVACCoolingPanelRadiantConvectiveWater::fractionofRadiantEnergyIncidentonPeople() const {
  return getImpl<detail::ZoneHVACCoolingPanelRadiantConvectiveWater_Impl>()->fractionofRadiantEnergyIncidentonPeople();
}

bool ZoneHVACCoolingPanelRadiantConvectiveWater::setFractionofRadiantEnergyIncidentonPeople(double fractionofRadiantEnergyIncidentonPeople) {
  return getImpl<detail::ZoneHVACCoolingPanelRadiantConvectiveWater_Impl>()->setFractionofRadiantEnergyIncidentonPeople(
    fractionofRadiantEnergyIncidentonPeople);
}

HVACComponent ZoneHVACCoolingPanelRadiantConvectiveWater::coolingCoil() const {
  return getImpl<detail::ZoneHVACCoolingPanelRadiantConvectiveWater_Impl>()->coolingCoil();
}

bool ZoneHVACCoolingPanelRadiantConvectiveWater::setCoolingCoil(HVACComponent& coolingCoil) {
  return getImpl<detail::ZoneHVACCoolingPanelRadiantConvectiveWater_Impl>()->setCoolingCoil(coolingCoil);
}

std::vector<ModelObject> ZoneHVACCoolingPanelRadiantConvectiveWater::children() const {
  return getImpl<detail::ZoneHVACCoolingPanelRadiantConvectiveWater_Impl>()->children();
}

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
namespace detail {

unsigned ZoneHVACCoolingPanelRadiantConvectiveWater_Impl::inletPort() const {
  return 0u;
}

unsigned ZoneHVACCoolingPanelRadiantConvectiveWater_Impl::outletPort() const {
  return 0u;
}

bool ZoneHVACCoolingPanelRadiantConvectiveWater_Impl::addToThermalZone(ThermalZone& thermalZone) {
  if (!ZoneHVACComponent_Impl::addToThermalZone(thermalZone)) {
    return false;
  }
  rewriteSurfaceFractions();
  return true;
}

void ZoneHVACCoolingPanelRadiantConvectiveWater_Impl::removeFromThermalZone() {
  ZoneHVACComponent_Impl::removeFromThermalZone();
  getObject<ModelObject>().clearExtensibleGroups();
}

Schedule ZoneHVACCoolingPanelRadiantConvectiveWater_Impl::availabilitySchedule() const {
  if (auto schedule = optionalAvailabilitySchedule()) {
    return *schedule;
  }
  LOG_FREE_AND_THROW("openstudio.epmodel.ZoneHVACCoolingPanelRadiantConvectiveWater",
                     briefDescription() << " does not have an Availability Schedule attached.");
}

boost::optional<Schedule> ZoneHVACCoolingPanelRadiantConvectiveWater_Impl::optionalAvailabilitySchedule() const {
  return getObject<ModelObject>().getModelObjectTarget<Schedule>(PanelFields::AvailabilityScheduleName);
}

bool ZoneHVACCoolingPanelRadiantConvectiveWater_Impl::setAvailabilitySchedule(Schedule& schedule) {
  return setPointer(PanelFields::AvailabilityScheduleName, schedule.handle(), false);
}

void ZoneHVACCoolingPanelRadiantConvectiveWater_Impl::resetAvailabilitySchedule() {
  OS_ASSERT(setPointer(PanelFields::AvailabilityScheduleName, Handle(), false));
}

double ZoneHVACCoolingPanelRadiantConvectiveWater_Impl::fractionRadiant() const {
  auto value = getDouble(PanelFields::FractionRadiant, true);
  OS_ASSERT(value);
  return *value;
}

bool ZoneHVACCoolingPanelRadiantConvectiveWater_Impl::setFractionRadiant(double fractionRadiant) {
  return setDouble(PanelFields::FractionRadiant, fractionRadiant);
}

double ZoneHVACCoolingPanelRadiantConvectiveWater_Impl::fractionofRadiantEnergyIncidentonPeople() const {
  auto value = getDouble(PanelFields::FractionofRadiantEnergyIncidentonPeople, true);
  OS_ASSERT(value);
  return *value;
}

bool ZoneHVACCoolingPanelRadiantConvectiveWater_Impl::setFractionofRadiantEnergyIncidentonPeople(double fractionofRadiantEnergyIncidentonPeople) {
  const bool changed = setDouble(PanelFields::FractionofRadiantEnergyIncidentonPeople, fractionofRadiantEnergyIncidentonPeople);
  if (changed && thermalZone()) {
    rewriteSurfaceFractions();
  }
  return changed;
}

HVACComponent ZoneHVACCoolingPanelRadiantConvectiveWater_Impl::coolingCoil() const {
  const auto parent = getObject<openstudio::epmodel::ZoneHVACCoolingPanelRadiantConvectiveWater>();
  return model().getOrCreateTransientByName<openstudio::epmodel::CoilCoolingWaterPanelRadiant>(
                  detail::transientCoolingCoilName(parent))
    .cast<HVACComponent>();
}

bool ZoneHVACCoolingPanelRadiantConvectiveWater_Impl::setCoolingCoil(HVACComponent& coolingCoil) {
  auto source = coolingCoil.optionalCast<CoilCoolingWaterPanelRadiant>();
  if (!source) {
    return false;
  }

  auto target = this->coolingCoil().cast<CoilCoolingWaterPanelRadiant>();
  bool result = true;

  result = target.setRatedInletWaterTemperature(source->ratedInletWaterTemperature()) && result;
  result = target.setRatedInletSpaceTemperature(source->ratedInletSpaceTemperature()) && result;
  result = target.setRatedWaterMassFlowRate(source->ratedWaterMassFlowRate()) && result;
  result = target.setCoolingDesignCapacityMethod(source->coolingDesignCapacityMethod()) && result;
  result = source->isCoolingDesignCapacityAutosized() ? (target.autosizeCoolingDesignCapacity(), result)
                                                      : (source->coolingDesignCapacity() ? (target.setCoolingDesignCapacity(*source->coolingDesignCapacity()) && result)
                                                                                        : (setString(PanelFields::CoolingDesignCapacity, "", false) && result));
  result = target.setCoolingDesignCapacityPerFloorArea(source->coolingDesignCapacityPerFloorArea()) && result;
  result = target.setFractionofAutosizedCoolingDesignCapacity(source->fractionofAutosizedCoolingDesignCapacity()) && result;
  result = source->isMaximumChilledWaterFlowRateAutosized() ? (target.autosizeMaximumChilledWaterFlowRate(), result)
                                                            : (source->maximumChilledWaterFlowRate()
                                                                 ? (target.setMaximumChilledWaterFlowRate(*source->maximumChilledWaterFlowRate()) && result)
                                                                 : (setString(PanelFields::MaximumChilledWaterFlowRate, "", false) && result));
  result = target.setControlType(source->controlType()) && result;
  result = target.setCoolingControlThrottlingRange(source->coolingControlThrottlingRange()) && result;
  if (auto schedule = source->coolingControlTemperatureSchedule()) {
    result = target.setCoolingControlTemperatureSchedule(*schedule) && result;
  } else {
    target.resetCoolingControlTemperatureSchedule();
  }
  result = target.setCondensationControlType(source->condensationControlType()) && result;
  result = target.setCondensationControlDewpointOffset(source->condensationControlDewpointOffset()) && result;

  if (auto inlet = source->inletModelObject()) {
    if (auto node = inlet->optionalCast<Node>()) {
      result = setPointer(PanelFields::WaterInletNodeName, node->handle(), false) && result;
    }
  } else {
    result = setPointer(PanelFields::WaterInletNodeName, Handle(), false) && result;
  }

  if (auto outlet = source->outletModelObject()) {
    if (auto node = outlet->optionalCast<Node>()) {
      result = setPointer(PanelFields::WaterOutletNodeName, node->handle(), false) && result;
    }
  } else {
    result = setPointer(PanelFields::WaterOutletNodeName, Handle(), false) && result;
  }

  return result;
}

std::vector<ModelObject> ZoneHVACCoolingPanelRadiantConvectiveWater_Impl::children() const {
  return {coolingCoil().cast<ModelObject>()};
}

void ZoneHVACCoolingPanelRadiantConvectiveWater_Impl::doCanonicalize(LoadContext& context) {
  if (context.repairEnabled() && thermalZone()) {
    rewriteSurfaceFractions();
  }
}

double ZoneHVACCoolingPanelRadiantConvectiveWater_Impl::ratedInletWaterTemperature() const {
  auto value = getDouble(PanelFields::RatedInletWaterTemperature, true);
  OS_ASSERT(value);
  return *value;
}

bool ZoneHVACCoolingPanelRadiantConvectiveWater_Impl::isRatedInletWaterTemperatureDefaulted() const {
  return isEmpty(PanelFields::RatedInletWaterTemperature);
}

bool ZoneHVACCoolingPanelRadiantConvectiveWater_Impl::setRatedInletWaterTemperature(double ratedInletWaterTemperature) {
  return setDouble(PanelFields::RatedInletWaterTemperature, ratedInletWaterTemperature);
}

void ZoneHVACCoolingPanelRadiantConvectiveWater_Impl::resetRatedInletWaterTemperature() {
  OS_ASSERT(setString(PanelFields::RatedInletWaterTemperature, ""));
}

double ZoneHVACCoolingPanelRadiantConvectiveWater_Impl::ratedInletSpaceTemperature() const {
  auto value = getDouble(PanelFields::RatedInletSpaceTemperature, true);
  OS_ASSERT(value);
  return *value;
}

bool ZoneHVACCoolingPanelRadiantConvectiveWater_Impl::isRatedInletSpaceTemperatureDefaulted() const {
  return isEmpty(PanelFields::RatedInletSpaceTemperature);
}

bool ZoneHVACCoolingPanelRadiantConvectiveWater_Impl::setRatedInletSpaceTemperature(double ratedInletSpaceTemperature) {
  return setDouble(PanelFields::RatedInletSpaceTemperature, ratedInletSpaceTemperature);
}

void ZoneHVACCoolingPanelRadiantConvectiveWater_Impl::resetRatedInletSpaceTemperature() {
  OS_ASSERT(setString(PanelFields::RatedInletSpaceTemperature, ""));
}

double ZoneHVACCoolingPanelRadiantConvectiveWater_Impl::ratedWaterMassFlowRate() const {
  auto value = getDouble(PanelFields::RatedWaterMassFlowRate, true);
  OS_ASSERT(value);
  return *value;
}

bool ZoneHVACCoolingPanelRadiantConvectiveWater_Impl::isRatedWaterMassFlowRateDefaulted() const {
  return isEmpty(PanelFields::RatedWaterMassFlowRate);
}

bool ZoneHVACCoolingPanelRadiantConvectiveWater_Impl::setRatedWaterMassFlowRate(double ratedWaterMassFlowRate) {
  return setDouble(PanelFields::RatedWaterMassFlowRate, ratedWaterMassFlowRate);
}

void ZoneHVACCoolingPanelRadiantConvectiveWater_Impl::resetRatedWaterMassFlowRate() {
  OS_ASSERT(setString(PanelFields::RatedWaterMassFlowRate, ""));
}

std::string ZoneHVACCoolingPanelRadiantConvectiveWater_Impl::coolingDesignCapacityMethod() const {
  auto value = getString(PanelFields::CoolingDesignCapacityMethod, true);
  OS_ASSERT(value);
  return *value;
}

bool ZoneHVACCoolingPanelRadiantConvectiveWater_Impl::isCoolingDesignCapacityMethodDefaulted() const {
  return isEmpty(PanelFields::CoolingDesignCapacityMethod);
}

bool ZoneHVACCoolingPanelRadiantConvectiveWater_Impl::setCoolingDesignCapacityMethod(const std::string& coolingDesignCapacityMethod) {
  return setString(PanelFields::CoolingDesignCapacityMethod, coolingDesignCapacityMethod);
}

void ZoneHVACCoolingPanelRadiantConvectiveWater_Impl::resetCoolingDesignCapacityMethod() {
  OS_ASSERT(setString(PanelFields::CoolingDesignCapacityMethod, ""));
}

boost::optional<double> ZoneHVACCoolingPanelRadiantConvectiveWater_Impl::coolingDesignCapacity() const {
  return getDouble(PanelFields::CoolingDesignCapacity, true);
}

bool ZoneHVACCoolingPanelRadiantConvectiveWater_Impl::isCoolingDesignCapacityAutosized() const {
  if (auto value = getString(PanelFields::CoolingDesignCapacity, true)) {
    return openstudio::istringEqual(*value, "autosize");
  }
  return false;
}

bool ZoneHVACCoolingPanelRadiantConvectiveWater_Impl::setCoolingDesignCapacity(double coolingDesignCapacity) {
  return setDouble(PanelFields::CoolingDesignCapacity, coolingDesignCapacity);
}

void ZoneHVACCoolingPanelRadiantConvectiveWater_Impl::autosizeCoolingDesignCapacity() {
  OS_ASSERT(setString(PanelFields::CoolingDesignCapacity, "autosize"));
}

boost::optional<double> ZoneHVACCoolingPanelRadiantConvectiveWater_Impl::coolingDesignCapacityPerFloorArea() const {
  return getDouble(PanelFields::CoolingDesignCapacityPerFloorArea, true);
}

bool ZoneHVACCoolingPanelRadiantConvectiveWater_Impl::setCoolingDesignCapacityPerFloorArea(double coolingDesignCapacityPerFloorArea) {
  return setDouble(PanelFields::CoolingDesignCapacityPerFloorArea, coolingDesignCapacityPerFloorArea);
}

void ZoneHVACCoolingPanelRadiantConvectiveWater_Impl::resetCoolingDesignCapacityPerFloorArea() {
  OS_ASSERT(setString(PanelFields::CoolingDesignCapacityPerFloorArea, ""));
}

boost::optional<double> ZoneHVACCoolingPanelRadiantConvectiveWater_Impl::fractionofAutosizedCoolingDesignCapacity() const {
  return getDouble(PanelFields::FractionofAutosizedCoolingDesignCapacity, true);
}

bool ZoneHVACCoolingPanelRadiantConvectiveWater_Impl::setFractionOfAutosizedCoolingDesignCapacity(
  double fractionOfAutosizedCoolingDesignCapacity) {
  return setDouble(PanelFields::FractionofAutosizedCoolingDesignCapacity, fractionOfAutosizedCoolingDesignCapacity);
}

void ZoneHVACCoolingPanelRadiantConvectiveWater_Impl::resetFractionOfAutosizedCoolingDesignCapacity() {
  OS_ASSERT(setString(PanelFields::FractionofAutosizedCoolingDesignCapacity, ""));
}

boost::optional<double> ZoneHVACCoolingPanelRadiantConvectiveWater_Impl::maximumChilledWaterFlowRate() const {
  return getDouble(PanelFields::MaximumChilledWaterFlowRate, true);
}

bool ZoneHVACCoolingPanelRadiantConvectiveWater_Impl::isMaximumChilledWaterFlowRateAutosized() const {
  if (auto value = getString(PanelFields::MaximumChilledWaterFlowRate, true)) {
    return openstudio::istringEqual(*value, "autosize");
  }
  return false;
}

bool ZoneHVACCoolingPanelRadiantConvectiveWater_Impl::setMaximumChilledWaterFlowRate(double maximumChilledWaterFlowRate) {
  return setDouble(PanelFields::MaximumChilledWaterFlowRate, maximumChilledWaterFlowRate);
}

void ZoneHVACCoolingPanelRadiantConvectiveWater_Impl::autosizeMaximumChilledWaterFlowRate() {
  OS_ASSERT(setString(PanelFields::MaximumChilledWaterFlowRate, "autosize"));
}

std::string ZoneHVACCoolingPanelRadiantConvectiveWater_Impl::controlType() const {
  auto value = getString(PanelFields::ControlType, true);
  OS_ASSERT(value);
  return *value;
}

bool ZoneHVACCoolingPanelRadiantConvectiveWater_Impl::isControlTypeDefaulted() const {
  return isEmpty(PanelFields::ControlType);
}

bool ZoneHVACCoolingPanelRadiantConvectiveWater_Impl::setControlType(const std::string& controlType) {
  return setString(PanelFields::ControlType, controlType);
}

void ZoneHVACCoolingPanelRadiantConvectiveWater_Impl::resetControlType() {
  OS_ASSERT(setString(PanelFields::ControlType, ""));
}

double ZoneHVACCoolingPanelRadiantConvectiveWater_Impl::coolingControlThrottlingRange() const {
  auto value = getDouble(PanelFields::CoolingControlThrottlingRange, true);
  OS_ASSERT(value);
  return *value;
}

bool ZoneHVACCoolingPanelRadiantConvectiveWater_Impl::isCoolingControlThrottlingRangeDefaulted() const {
  return isEmpty(PanelFields::CoolingControlThrottlingRange);
}

bool ZoneHVACCoolingPanelRadiantConvectiveWater_Impl::setCoolingControlThrottlingRange(double coolingControlThrottlingRange) {
  return setDouble(PanelFields::CoolingControlThrottlingRange, coolingControlThrottlingRange);
}

void ZoneHVACCoolingPanelRadiantConvectiveWater_Impl::resetCoolingControlThrottlingRange() {
  OS_ASSERT(setString(PanelFields::CoolingControlThrottlingRange, ""));
}

std::string ZoneHVACCoolingPanelRadiantConvectiveWater_Impl::condensationControlType() const {
  auto value = getString(PanelFields::CondensationControlType, true);
  OS_ASSERT(value);
  return *value;
}

bool ZoneHVACCoolingPanelRadiantConvectiveWater_Impl::isCondensationControlTypeDefaulted() const {
  return isEmpty(PanelFields::CondensationControlType);
}

bool ZoneHVACCoolingPanelRadiantConvectiveWater_Impl::setCondensationControlType(const std::string& condensationControlType) {
  return setString(PanelFields::CondensationControlType, condensationControlType);
}

void ZoneHVACCoolingPanelRadiantConvectiveWater_Impl::resetCondensationControlType() {
  OS_ASSERT(setString(PanelFields::CondensationControlType, ""));
}

double ZoneHVACCoolingPanelRadiantConvectiveWater_Impl::condensationControlDewpointOffset() const {
  auto value = getDouble(PanelFields::CondensationControlDewpointOffset, true);
  OS_ASSERT(value);
  return *value;
}

bool ZoneHVACCoolingPanelRadiantConvectiveWater_Impl::isCondensationControlDewpointOffsetDefaulted() const {
  return isEmpty(PanelFields::CondensationControlDewpointOffset);
}

bool ZoneHVACCoolingPanelRadiantConvectiveWater_Impl::setCondensationControlDewpointOffset(double condensationControlDewpointOffset) {
  return setDouble(PanelFields::CondensationControlDewpointOffset, condensationControlDewpointOffset);
}

void ZoneHVACCoolingPanelRadiantConvectiveWater_Impl::resetCondensationControlDewpointOffset() {
  OS_ASSERT(setString(PanelFields::CondensationControlDewpointOffset, ""));
}

std::vector<Surface> ZoneHVACCoolingPanelRadiantConvectiveWater_Impl::zoneSurfaces() const {
  std::vector<Surface> result;
  if (auto zone = thermalZone()) {
    for (const auto& surface : model().getConcreteModelObjects<openstudio::epmodel::Surface>()) {
      bool belongsToZone = false;
      if (auto space = surface.getModelObjectTarget<openstudio::epmodel::Space>(SurfaceFields::SpaceName)) {
        if (auto surfaceZone = space->thermalZone()) {
          belongsToZone = (*surfaceZone == *zone);
        }
      } else if (auto directZone = surface.getModelObjectTarget<openstudio::epmodel::ThermalZone>(SurfaceFields::ZoneName)) {
        belongsToZone = (*directZone == *zone);
      }

      if (belongsToZone) {
        result.push_back(surface);
      }
    }
  }
  return result;
}

void ZoneHVACCoolingPanelRadiantConvectiveWater_Impl::rewriteSurfaceFractions() {
  auto panel = getObject<ModelObject>();
  panel.clearExtensibleGroups();

  const auto surfaces = zoneSurfaces();
  if (surfaces.empty()) {
    return;
  }

  double totalFloorArea = 0.0;
  double totalCeilingArea = 0.0;
  double totalWallArea = 0.0;

  for (const auto& surface : surfaces) {
    const double area = surfaceGrossArea(surface);
    if (detail::isFloorSurface(surface)) {
      totalFloorArea += area;
    } else if (detail::isCeilingSurface(surface)) {
      totalCeilingArea += area;
    } else {
      totalWallArea += area;
    }
  }

  const double radiantToPeople = fractionofRadiantEnergyIncidentonPeople();
  const double fractionOnFloor = (1.0 - radiantToPeople) * 0.05;
  const double fractionOnWall = (1.0 - radiantToPeople) * 0.55;
  const double fractionOnCeiling = (1.0 - radiantToPeople) * 0.40;

  for (const auto& surface : surfaces) {
    const double area = surfaceGrossArea(surface);
    if (area <= 0.0) {
      continue;
    }

    double denominator = totalWallArea;
    double weight = fractionOnWall;
    if (detail::isFloorSurface(surface)) {
      denominator = totalFloorArea;
      weight = fractionOnFloor;
    } else if (detail::isCeilingSurface(surface)) {
      denominator = totalCeilingArea;
      weight = fractionOnCeiling;
    }

    if (denominator <= 0.0) {
      continue;
    }

    auto group = panel.pushExtensibleGroup().cast<openstudio::WorkspaceExtensibleGroup>();
    OS_ASSERT(group.setPointer(PanelExtensibleFields::SurfaceName, surface.handle(), false));
    OS_ASSERT(group.setDouble(PanelExtensibleFields::FractionofRadiantEnergytoSurface, (area / denominator) * weight));
  }
}

}  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
