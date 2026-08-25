/***********************************************************************************************************************  
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.  
*  See also https://openstudio.net/license  
***********************************************************************************************************************/

#include "ZoneHVACComponent/ZoneHVACLowTemperatureRadiantElectric.hpp"
#include "ZoneHVACComponent/ZoneHVACLowTemperatureRadiantElectric_Impl.hpp"

#include "Model.hpp"
#include "HVACComponent/ThermalZone.hpp"
#include "HVACComponent/ThermalZone_Impl.hpp"
#include "LayeredConstruction/ConstructionWithInternalSource.hpp"
#include "LayeredConstruction/ConstructionWithInternalSource_Impl.hpp"
#include "ModelObject/ModelObject.hpp"
#include "ModelObject/ZoneHVACLowTemperatureRadiantSurfaceGroup.hpp"
#include "ModelObject/ZoneHVACLowTemperatureRadiantSurfaceGroup_Impl.hpp"
#include "PlanarSurface/Surface.hpp"
#include "PlanarSurface/Surface_Impl.hpp"
#include "PlanarSurfaceGroup/Space.hpp"
#include "PlanarSurfaceGroup/Space_Impl.hpp"
#include "Schedule/Schedule.hpp"
#include "Schedule/Schedule_Impl.hpp"

#include "../utilities/core/Assert.hpp"
#include "../utilities/core/Compare.hpp"

#include <utilities/geometry/Geometry.hpp>
#include <utilities/geometry/Point3d.hpp>
#include <utilities/idd/BuildingSurface_Detailed_FieldEnums.hxx>
#include <utilities/idd/ConstructionProperty_InternalHeatSource_FieldEnums.hxx>
#include <utilities/idd/IddFactory.hxx>
#include <utilities/idd/ZoneHVAC_LowTemperatureRadiant_Electric_FieldEnums.hxx>
#include <utilities/idf/IdfExtensibleGroup.hpp>

#include <algorithm>

namespace openstudio {
namespace epmodel {
  namespace detail {

    using SurfaceFields = openstudio::BuildingSurface_DetailedFields;
    using SurfaceVertexFields = openstudio::BuildingSurface_DetailedExtensibleFields;

    // The envelope side of epmodel is still thinner than the HVAC side, so this
    // family currently does its radiant-surface bookkeeping through the persisted
    // surface, construction, and surface-group fields directly. That matches the
    // underlying EnergyPlus storage shape and keeps the canonical OpenStudio API in
    // place until richer envelope wrappers exist.
    bool electricSurfaceMatchesRadiantSelection(const openstudio::epmodel::Surface& surface, const std::string& radiantSurfaceType) {
      const auto surfaceType = surface.surfaceType();
      if (openstudio::istringEqual(radiantSurfaceType, "Ceilings")) {
        return openstudio::epmodel::Surface::isCeilingLike(surfaceType);
      }
      if (openstudio::istringEqual(radiantSurfaceType, "Floors")) {
        return openstudio::istringEqual(surfaceType, "Floor");
      }
      if (openstudio::istringEqual(radiantSurfaceType, "CeilingsandFloors")) {
        return openstudio::epmodel::Surface::isCeilingLike(surfaceType) || openstudio::istringEqual(surfaceType, "Floor");
      }
      if (openstudio::istringEqual(radiantSurfaceType, "AllSurfaces")) {
        return true;
      }
      return false;
    }

    bool electricSurfaceHasInternalSourceConstruction(const openstudio::epmodel::Surface& surface) {
      const auto construction = surface.getModelObjectTarget<openstudio::epmodel::ModelObject>(SurfaceFields::ConstructionName);
      if (!construction) {
        return false;
      }

      for (const auto& internalSourceProperty : surface.model().getConcreteModelObjects<openstudio::epmodel::ConstructionWithInternalSource>()) {
        if (auto propertyConstruction = internalSourceProperty.getModelObjectTarget<openstudio::epmodel::ModelObject>(
              openstudio::ConstructionProperty_InternalHeatSourceFields::ConstructionName)) {
          if (propertyConstruction->handle() == construction->handle()) {
            return true;
          }
        }
      }

      return false;
    }

    std::vector<openstudio::Point3d> electricSurfaceVertices(const openstudio::epmodel::Surface& surface) {
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

    double electricSurfaceGrossArea(const openstudio::epmodel::Surface& surface) {
      const auto vertices = electricSurfaceVertices(surface);
      if (vertices.size() < 3u) {
        return 0.0;
      }
      if (const auto area = openstudio::getArea(vertices)) {
        return *area;
      }
      return 0.0;
    }

    std::vector<openstudio::epmodel::Surface> electricEligibleRadiantSurfaces(const openstudio::epmodel::Model& model,
                                                                              const openstudio::epmodel::ThermalZone& zone,
                                                                              const std::string& radiantSurfaceType) {
      std::vector<openstudio::epmodel::Surface> result;

      for (const auto& surface : model.getConcreteModelObjects<openstudio::epmodel::Surface>()) {
        bool belongsToZone = false;
        if (auto space = surface.getModelObjectTarget<openstudio::epmodel::Space>(SurfaceFields::SpaceName)) {
          if (auto surfaceZone = space->thermalZone()) {
            belongsToZone = (*surfaceZone == zone);
          }
        } else if (auto directZone = surface.getModelObjectTarget<openstudio::epmodel::ThermalZone>(SurfaceFields::ZoneName)) {
          belongsToZone = (*directZone == zone);
        }

        if (!belongsToZone) {
          continue;
        }
        if (!electricSurfaceHasInternalSourceConstruction(surface)) {
          continue;
        }
        if (!electricSurfaceMatchesRadiantSelection(surface, radiantSurfaceType)) {
          continue;
        }
        result.push_back(surface);
      }

      return result;
    }

    bool sameElectricSurfaceSet(const std::vector<openstudio::epmodel::Surface>& lhs, const std::vector<openstudio::epmodel::Surface>& rhs) {
      if (lhs.size() != rhs.size()) {
        return false;
      }

      std::vector<openstudio::Handle> lhsHandles;
      lhsHandles.reserve(lhs.size());
      for (const auto& surface : lhs) {
        lhsHandles.push_back(surface.handle());
      }
      std::sort(lhsHandles.begin(), lhsHandles.end());

      std::vector<openstudio::Handle> rhsHandles;
      rhsHandles.reserve(rhs.size());
      for (const auto& surface : rhs) {
        rhsHandles.push_back(surface.handle());
      }
      std::sort(rhsHandles.begin(), rhsHandles.end());

      return lhsHandles == rhsHandles;
    }

  }  // namespace detail

  ZoneHVACLowTemperatureRadiantElectric::ZoneHVACLowTemperatureRadiantElectric(const Model& model, Schedule& availabilitySchedule,
                                                                               Schedule& heatingTemperatureSchedule)
    : ZoneHVACComponent(ZoneHVACLowTemperatureRadiantElectric::iddObjectType(), model) {
    OS_ASSERT(getImpl<detail::ZoneHVACLowTemperatureRadiantElectric_Impl>());
    OS_ASSERT(setAvailabilitySchedule(availabilitySchedule));
    OS_ASSERT(setHeatingSetpointTemperatureSchedule(heatingTemperatureSchedule));
    resetRadiantSurfaceType();
    autosizeMaximumElectricalPowertoPanel();
    OS_ASSERT(setTemperatureControlType("MeanAirTemperature"));
    OS_ASSERT(setHeatingThrottlingRange(2.0));
  }

  ZoneHVACLowTemperatureRadiantElectric::ZoneHVACLowTemperatureRadiantElectric(
    std::shared_ptr<detail::ZoneHVACLowTemperatureRadiantElectric_Impl> impl)
    : ZoneHVACComponent(std::move(impl)) {}

  IddObjectType ZoneHVACLowTemperatureRadiantElectric::iddObjectType() {
    return IddObjectType::ZoneHVAC_LowTemperatureRadiant_Electric;
  }

  std::vector<std::string> ZoneHVACLowTemperatureRadiantElectric::radiantSurfaceTypeValues() {
    static const std::vector<std::string> values{"Ceilings", "Floors", "CeilingsandFloors", "AllSurfaces"};
    return values;
  }

  std::vector<std::string> ZoneHVACLowTemperatureRadiantElectric::temperatureControlTypeValues() {
    return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(),
                          ZoneHVAC_LowTemperatureRadiant_ElectricFields::TemperatureControlType);
  }

  unsigned detail::ZoneHVACLowTemperatureRadiantElectric_Impl::inletPort() const {
    return 0u;
  }

  unsigned detail::ZoneHVACLowTemperatureRadiantElectric_Impl::outletPort() const {
    return 0u;
  }

  Schedule ZoneHVACLowTemperatureRadiantElectric::availabilitySchedule() const {
    return getImpl<detail::ZoneHVACLowTemperatureRadiantElectric_Impl>()->availabilitySchedule();
  }

  bool ZoneHVACLowTemperatureRadiantElectric::setAvailabilitySchedule(Schedule& schedule) {
    return getImpl<detail::ZoneHVACLowTemperatureRadiantElectric_Impl>()->setAvailabilitySchedule(schedule);
  }

  Schedule ZoneHVACLowTemperatureRadiantElectric::heatingSetpointTemperatureSchedule() const {
    return getImpl<detail::ZoneHVACLowTemperatureRadiantElectric_Impl>()->heatingSetpointTemperatureSchedule();
  }

  bool ZoneHVACLowTemperatureRadiantElectric::setHeatingSetpointTemperatureSchedule(Schedule& schedule) {
    return getImpl<detail::ZoneHVACLowTemperatureRadiantElectric_Impl>()->setHeatingSetpointTemperatureSchedule(schedule);
  }

  boost::optional<std::string> ZoneHVACLowTemperatureRadiantElectric::radiantSurfaceType() const {
    return getImpl<detail::ZoneHVACLowTemperatureRadiantElectric_Impl>()->radiantSurfaceType();
  }

  bool ZoneHVACLowTemperatureRadiantElectric::setRadiantSurfaceType(const std::string& radiantSurfaceType) {
    return getImpl<detail::ZoneHVACLowTemperatureRadiantElectric_Impl>()->setRadiantSurfaceType(radiantSurfaceType);
  }

  void ZoneHVACLowTemperatureRadiantElectric::resetRadiantSurfaceType() {
    getImpl<detail::ZoneHVACLowTemperatureRadiantElectric_Impl>()->resetRadiantSurfaceType();
  }

  std::vector<Surface> ZoneHVACLowTemperatureRadiantElectric::surfaces() const {
    return getImpl<detail::ZoneHVACLowTemperatureRadiantElectric_Impl>()->surfaces();
  }

  boost::optional<ZoneHVACLowTemperatureRadiantSurfaceGroup> ZoneHVACLowTemperatureRadiantElectric::surfaceGroup() const {
    return getImpl<detail::ZoneHVACLowTemperatureRadiantElectric_Impl>()->surfaceGroup();
  }

  boost::optional<double> ZoneHVACLowTemperatureRadiantElectric::maximumElectricalPowertoPanel() const {
    return getImpl<detail::ZoneHVACLowTemperatureRadiantElectric_Impl>()->maximumElectricalPowertoPanel();
  }

  bool ZoneHVACLowTemperatureRadiantElectric::isMaximumElectricalPowertoPanelDefaulted() const {
    return getImpl<detail::ZoneHVACLowTemperatureRadiantElectric_Impl>()->isMaximumElectricalPowertoPanelDefaulted();
  }

  bool ZoneHVACLowTemperatureRadiantElectric::isMaximumElectricalPowertoPanelAutosized() const {
    return getImpl<detail::ZoneHVACLowTemperatureRadiantElectric_Impl>()->isMaximumElectricalPowertoPanelAutosized();
  }

  bool ZoneHVACLowTemperatureRadiantElectric::setMaximumElectricalPowertoPanel(double maximumElectricalPowertoPanel) {
    return getImpl<detail::ZoneHVACLowTemperatureRadiantElectric_Impl>()->setMaximumElectricalPowertoPanel(maximumElectricalPowertoPanel);
  }

  void ZoneHVACLowTemperatureRadiantElectric::resetMaximumElectricalPowertoPanel() {
    getImpl<detail::ZoneHVACLowTemperatureRadiantElectric_Impl>()->resetMaximumElectricalPowertoPanel();
  }

  void ZoneHVACLowTemperatureRadiantElectric::autosizeMaximumElectricalPowertoPanel() {
    getImpl<detail::ZoneHVACLowTemperatureRadiantElectric_Impl>()->autosizeMaximumElectricalPowertoPanel();
  }

  boost::optional<double> ZoneHVACLowTemperatureRadiantElectric::autosizedMaximumElectricalPowertoPanel() const {
    return getImpl<detail::ZoneHVACLowTemperatureRadiantElectric_Impl>()->autosizedMaximumElectricalPowertoPanel();
  }

  std::string ZoneHVACLowTemperatureRadiantElectric::temperatureControlType() const {
    return getImpl<detail::ZoneHVACLowTemperatureRadiantElectric_Impl>()->temperatureControlType();
  }

  bool ZoneHVACLowTemperatureRadiantElectric::isTemperatureControlTypeDefaulted() const {
    return getImpl<detail::ZoneHVACLowTemperatureRadiantElectric_Impl>()->isTemperatureControlTypeDefaulted();
  }

  bool ZoneHVACLowTemperatureRadiantElectric::setTemperatureControlType(const std::string& temperatureControlType) {
    return getImpl<detail::ZoneHVACLowTemperatureRadiantElectric_Impl>()->setTemperatureControlType(temperatureControlType);
  }

  void ZoneHVACLowTemperatureRadiantElectric::resetTemperatureControlType() {
    getImpl<detail::ZoneHVACLowTemperatureRadiantElectric_Impl>()->resetTemperatureControlType();
  }

  std::string ZoneHVACLowTemperatureRadiantElectric::setpointControlType() const {
    return getImpl<detail::ZoneHVACLowTemperatureRadiantElectric_Impl>()->setpointControlType();
  }

  bool ZoneHVACLowTemperatureRadiantElectric::isSetpointControlTypeDefaulted() const {
    return getImpl<detail::ZoneHVACLowTemperatureRadiantElectric_Impl>()->isSetpointControlTypeDefaulted();
  }

  bool ZoneHVACLowTemperatureRadiantElectric::setSetpointControlType(const std::string& setpointControlType) {
    return getImpl<detail::ZoneHVACLowTemperatureRadiantElectric_Impl>()->setSetpointControlType(setpointControlType);
  }

  void ZoneHVACLowTemperatureRadiantElectric::resetSetpointControlType() {
    getImpl<detail::ZoneHVACLowTemperatureRadiantElectric_Impl>()->resetSetpointControlType();
  }

  double ZoneHVACLowTemperatureRadiantElectric::heatingThrottlingRange() const {
    return getImpl<detail::ZoneHVACLowTemperatureRadiantElectric_Impl>()->heatingThrottlingRange();
  }

  bool ZoneHVACLowTemperatureRadiantElectric::isHeatingThrottlingRangeDefaulted() const {
    return getImpl<detail::ZoneHVACLowTemperatureRadiantElectric_Impl>()->isHeatingThrottlingRangeDefaulted();
  }

  bool ZoneHVACLowTemperatureRadiantElectric::setHeatingThrottlingRange(double heatingThrottlingRange) {
    return getImpl<detail::ZoneHVACLowTemperatureRadiantElectric_Impl>()->setHeatingThrottlingRange(heatingThrottlingRange);
  }

  void ZoneHVACLowTemperatureRadiantElectric::resetHeatingThrottlingRange() {
    getImpl<detail::ZoneHVACLowTemperatureRadiantElectric_Impl>()->resetHeatingThrottlingRange();
  }

  namespace detail {

    Schedule ZoneHVACLowTemperatureRadiantElectric_Impl::availabilitySchedule() const {
      if (auto schedule =
            getObject<ModelObject>().getModelObjectTarget<Schedule>(ZoneHVAC_LowTemperatureRadiant_ElectricFields::AvailabilityScheduleName)) {
        return *schedule;
      }

      LOG_FREE(Error, "openstudio.epmodel.ZoneHVACLowTemperatureRadiantElectric", "Required availability schedule not set");
      LOG_FREE_AND_THROW("openstudio.epmodel.ZoneHVACLowTemperatureRadiantElectric", briefDescription()
                                                                                       << " does not have an Availability Schedule attached.");
    }

    bool ZoneHVACLowTemperatureRadiantElectric_Impl::setAvailabilitySchedule(Schedule& schedule) {
      return setSchedule(ZoneHVAC_LowTemperatureRadiant_ElectricFields::AvailabilityScheduleName, "ZoneHVACLowTemperatureRadiantElectric",
                         "Availability", schedule);
    }

    Schedule ZoneHVACLowTemperatureRadiantElectric_Impl::heatingSetpointTemperatureSchedule() const {
      if (auto schedule = getObject<ModelObject>().getModelObjectTarget<Schedule>(
            ZoneHVAC_LowTemperatureRadiant_ElectricFields::HeatingSetpointTemperatureScheduleName)) {
        return *schedule;
      }

      LOG_FREE(Error, "openstudio.epmodel.ZoneHVACLowTemperatureRadiantElectric", "Required heating setpoint temperature schedule not set");
      LOG_FREE_AND_THROW("openstudio.epmodel.ZoneHVACLowTemperatureRadiantElectric",
                         briefDescription() << " does not have a Heating Setpoint Temperature Schedule attached.");
    }

    bool ZoneHVACLowTemperatureRadiantElectric_Impl::setHeatingSetpointTemperatureSchedule(Schedule& schedule) {
      return setSchedule(ZoneHVAC_LowTemperatureRadiant_ElectricFields::HeatingSetpointTemperatureScheduleName,
                         "ZoneHVACLowTemperatureRadiantElectric", "Heating Setpoint Temperature", schedule);
    }

    boost::optional<std::string> ZoneHVACLowTemperatureRadiantElectric_Impl::radiantSurfaceType() const {
      const auto groupSurfaces = surfaces();
      if (groupSurfaces.empty()) {
        return boost::none;
      }

      const auto zone = thermalZone();
      if (!zone) {
        return boost::none;
      }

      for (const auto& candidate : openstudio::epmodel::ZoneHVACLowTemperatureRadiantElectric::radiantSurfaceTypeValues()) {
        if (sameElectricSurfaceSet(groupSurfaces, electricEligibleRadiantSurfaces(model(), *zone, candidate))) {
          return candidate;
        }
      }

      return boost::none;
    }

    bool ZoneHVACLowTemperatureRadiantElectric_Impl::setRadiantSurfaceType(const std::string& radiantSurfaceType) {
      const auto validValues = openstudio::epmodel::ZoneHVACLowTemperatureRadiantElectric::radiantSurfaceTypeValues();
      if (std::find_if(validValues.begin(), validValues.end(),
                       [&](const std::string& candidate) { return openstudio::istringEqual(candidate, radiantSurfaceType); })
          == validValues.end()) {
        return false;
      }

      auto zone = thermalZone();
      if (!zone) {
        return false;
      }

      auto groupObject = ensureSurfaceGroup();
      groupObject.getImpl<detail::ZoneHVACLowTemperatureRadiantSurfaceGroup_Impl>()->clearSurfaces();

      const auto groupSurfaces = electricEligibleRadiantSurfaces(model(), *zone, radiantSurfaceType);
      double totalArea = 0.0;
      for (const auto& surface : groupSurfaces) {
        totalArea += electricSurfaceGrossArea(surface);
      }

      const double fallbackFraction = groupSurfaces.empty() ? 0.0 : (1.0 / static_cast<double>(groupSurfaces.size()));
      for (const auto& surface : groupSurfaces) {
        const double area = electricSurfaceGrossArea(surface);
        const double fraction = (totalArea > 0.0) ? (area / totalArea) : fallbackFraction;
        if (!groupObject.getImpl<detail::ZoneHVACLowTemperatureRadiantSurfaceGroup_Impl>()->addSurface(const_cast<Surface&>(surface), fraction)) {
          return false;
        }
      }

      return true;
    }

    void ZoneHVACLowTemperatureRadiantElectric_Impl::resetRadiantSurfaceType() {
      if (auto zone = thermalZone()) {
        OS_ASSERT(setRadiantSurfaceType("Ceilings"));
      } else if (auto group = surfaceGroup()) {
        group->getImpl<detail::ZoneHVACLowTemperatureRadiantSurfaceGroup_Impl>()->clearSurfaces();
      }
    }

    std::vector<Surface> ZoneHVACLowTemperatureRadiantElectric_Impl::surfaces() const {
      if (auto groupObject = surfaceGroup()) {
        return groupObject->getImpl<detail::ZoneHVACLowTemperatureRadiantSurfaceGroup_Impl>()->surfaces();
      }
      return {};
    }

    boost::optional<ZoneHVACLowTemperatureRadiantSurfaceGroup> ZoneHVACLowTemperatureRadiantElectric_Impl::surfaceGroup() const {
      if (auto target = getTarget(ZoneHVAC_LowTemperatureRadiant_ElectricFields::SurfaceNameorRadiantSurfaceGroupName)) {
        if (auto typed = target->optionalCast<ZoneHVACLowTemperatureRadiantSurfaceGroup>()) {
          return *typed;
        }
      }

      return boost::none;
    }

    ZoneHVACLowTemperatureRadiantSurfaceGroup ZoneHVACLowTemperatureRadiantElectric_Impl::ensureSurfaceGroup() {
      if (auto existing = surfaceGroup()) {
        return *existing;
      }

      // Ordinary typed accessors should not repair broken linkage by stored name.
      // This helper is different: it is the setter-side path that materializes the
      // persisted EnergyPlus surface-group relationship on purpose. Reusing an
      // already-named surface group here avoids creating a duplicate object when
      // the stored field text already names the intended companion object.
      if (const auto existingName = getString(ZoneHVAC_LowTemperatureRadiant_ElectricFields::SurfaceNameorRadiantSurfaceGroupName, true);
          existingName && !existingName->empty()) {
        if (auto obj = workspace().getObjectByTypeAndName(IddObjectType::ZoneHVAC_LowTemperatureRadiant_SurfaceGroup, *existingName)) {
          if (auto typed = obj->optionalCast<ZoneHVACLowTemperatureRadiantSurfaceGroup>()) {
            OS_ASSERT(setPointer(ZoneHVAC_LowTemperatureRadiant_ElectricFields::SurfaceNameorRadiantSurfaceGroupName, typed->handle(), false));
            return *typed;
          }
        }
      }

      ZoneHVACLowTemperatureRadiantSurfaceGroup created(model());
      if (const auto existingName = getString(ZoneHVAC_LowTemperatureRadiant_ElectricFields::SurfaceNameorRadiantSurfaceGroupName, true);
          existingName && !existingName->empty()) {
        created.setName(*existingName);
      } else {
        created.setName(getObject<ModelObject>().nameString() + " Surface Group");
      }
      OS_ASSERT(setPointer(ZoneHVAC_LowTemperatureRadiant_ElectricFields::SurfaceNameorRadiantSurfaceGroupName, created.handle(), false));
      return created;
    }

    boost::optional<double> ZoneHVACLowTemperatureRadiantElectric_Impl::maximumElectricalPowertoPanel() const {
      return getDouble(ZoneHVAC_LowTemperatureRadiant_ElectricFields::HeatingDesignCapacity, true);
    }

    bool ZoneHVACLowTemperatureRadiantElectric_Impl::isMaximumElectricalPowertoPanelDefaulted() const {
      return isEmpty(ZoneHVAC_LowTemperatureRadiant_ElectricFields::HeatingDesignCapacity);
    }

    bool ZoneHVACLowTemperatureRadiantElectric_Impl::isMaximumElectricalPowertoPanelAutosized() const {
      if (auto value = getString(ZoneHVAC_LowTemperatureRadiant_ElectricFields::HeatingDesignCapacity, true)) {
        return openstudio::istringEqual(*value, "Autosize");
      }
      return false;
    }

    bool ZoneHVACLowTemperatureRadiantElectric_Impl::setMaximumElectricalPowertoPanel(double maximumElectricalPowertoPanel) {
      const bool result = setDouble(ZoneHVAC_LowTemperatureRadiant_ElectricFields::HeatingDesignCapacity, maximumElectricalPowertoPanel, false);
      OS_ASSERT(result);
      return result;
    }

    void ZoneHVACLowTemperatureRadiantElectric_Impl::resetMaximumElectricalPowertoPanel() {
      const bool result = setString(ZoneHVAC_LowTemperatureRadiant_ElectricFields::HeatingDesignCapacity, "", false);
      OS_ASSERT(result);
    }

    void ZoneHVACLowTemperatureRadiantElectric_Impl::autosizeMaximumElectricalPowertoPanel() {
      const bool result = setString(ZoneHVAC_LowTemperatureRadiant_ElectricFields::HeatingDesignCapacity, "Autosize", false);
      OS_ASSERT(result);
    }

    boost::optional<double> ZoneHVACLowTemperatureRadiantElectric_Impl::autosizedMaximumElectricalPowertoPanel() const {
      return boost::none;
    }

    std::string ZoneHVACLowTemperatureRadiantElectric_Impl::temperatureControlType() const {
      auto value = getString(ZoneHVAC_LowTemperatureRadiant_ElectricFields::TemperatureControlType, true);
      OS_ASSERT(value);
      return value.get();
    }

    bool ZoneHVACLowTemperatureRadiantElectric_Impl::isTemperatureControlTypeDefaulted() const {
      return isEmpty(ZoneHVAC_LowTemperatureRadiant_ElectricFields::TemperatureControlType);
    }

    bool ZoneHVACLowTemperatureRadiantElectric_Impl::setTemperatureControlType(const std::string& temperatureControlType) {
      const bool result = setString(ZoneHVAC_LowTemperatureRadiant_ElectricFields::TemperatureControlType, temperatureControlType, false);
      OS_ASSERT(result);
      return result;
    }

    void ZoneHVACLowTemperatureRadiantElectric_Impl::resetTemperatureControlType() {
      const bool result = setString(ZoneHVAC_LowTemperatureRadiant_ElectricFields::TemperatureControlType, "", false);
      OS_ASSERT(result);
    }

    std::string ZoneHVACLowTemperatureRadiantElectric_Impl::setpointControlType() const {
      auto value = getString(ZoneHVAC_LowTemperatureRadiant_ElectricFields::SetpointControlType, true);
      OS_ASSERT(value);
      return value.get();
    }

    bool ZoneHVACLowTemperatureRadiantElectric_Impl::isSetpointControlTypeDefaulted() const {
      return isEmpty(ZoneHVAC_LowTemperatureRadiant_ElectricFields::SetpointControlType);
    }

    bool ZoneHVACLowTemperatureRadiantElectric_Impl::setSetpointControlType(const std::string& setpointControlType) {
      const bool result = setString(ZoneHVAC_LowTemperatureRadiant_ElectricFields::SetpointControlType, setpointControlType, false);
      OS_ASSERT(result);
      return result;
    }

    void ZoneHVACLowTemperatureRadiantElectric_Impl::resetSetpointControlType() {
      const bool result = setString(ZoneHVAC_LowTemperatureRadiant_ElectricFields::SetpointControlType, "", false);
      OS_ASSERT(result);
    }

    double ZoneHVACLowTemperatureRadiantElectric_Impl::heatingThrottlingRange() const {
      auto value = getDouble(ZoneHVAC_LowTemperatureRadiant_ElectricFields::HeatingThrottlingRange, true);
      OS_ASSERT(value);
      return value.get();
    }

    bool ZoneHVACLowTemperatureRadiantElectric_Impl::isHeatingThrottlingRangeDefaulted() const {
      return isEmpty(ZoneHVAC_LowTemperatureRadiant_ElectricFields::HeatingThrottlingRange);
    }

    bool ZoneHVACLowTemperatureRadiantElectric_Impl::setHeatingThrottlingRange(double heatingThrottlingRange) {
      const bool result = setDouble(ZoneHVAC_LowTemperatureRadiant_ElectricFields::HeatingThrottlingRange, heatingThrottlingRange, false);
      OS_ASSERT(result);
      return result;
    }

    void ZoneHVACLowTemperatureRadiantElectric_Impl::resetHeatingThrottlingRange() {
      const bool result = setString(ZoneHVAC_LowTemperatureRadiant_ElectricFields::HeatingThrottlingRange, "", false);
      OS_ASSERT(result);
    }

  }  // namespace detail

}  // namespace epmodel
}  // namespace openstudio
