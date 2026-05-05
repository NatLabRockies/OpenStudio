/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "ZoneHVACComponent/ZoneHVACLowTempRadiantConstFlow.hpp"
#include "ZoneHVACComponent/ZoneHVACLowTempRadiantConstFlow_Impl.hpp"
#include "ModelObject/ZoneHVACLowTempRadiantConstFlowDesign.hpp"
#include "ModelObject/ZoneHVACLowTempRadiantConstFlowDesign_Impl.hpp"
#include "ModelObject/ZoneHVACLowTemperatureRadiantSurfaceGroup.hpp"
#include "ModelObject/ZoneHVACLowTemperatureRadiantSurfaceGroup_Impl.hpp"

#include "Model.hpp"
#include "HVACComponent/HVACComponent.hpp"
#include "ModelObject/ModelObject.hpp"
#include "PlanarSurface/Surface.hpp"
#include "PlanarSurface/Surface_Impl.hpp"
#include "PlanarSurfaceGroup/Space.hpp"
#include "PlanarSurfaceGroup/Space_Impl.hpp"
#include "Schedule/Schedule.hpp"
#include "Schedule/Schedule_Impl.hpp"
#include "StraightComponent/CoilCoolingLowTempRadiantConstFlow.hpp"
#include "StraightComponent/CoilCoolingLowTempRadiantConstFlow_Impl.hpp"
#include "StraightComponent/CoilHeatingLowTempRadiantConstFlow.hpp"
#include "StraightComponent/CoilHeatingLowTempRadiantConstFlow_Impl.hpp"
#include "StraightComponent/Node.hpp"
#include "HVACComponent/ThermalZone.hpp"
#include "HVACComponent/ThermalZone_Impl.hpp"
#include "LayeredConstruction/ConstructionWithInternalSource.hpp"
#include "LayeredConstruction/ConstructionWithInternalSource_Impl.hpp"

#include "../utilities/core/Assert.hpp"
#include "../utilities/core/Compare.hpp"

#include <utilities/geometry/Geometry.hpp>
#include <utilities/geometry/Point3d.hpp>
#include <utilities/idd/IddFactory.hxx>
#include <utilities/idd/IddEnums.hxx>
#include <utilities/idd/BuildingSurface_Detailed_FieldEnums.hxx>
#include <utilities/idd/ConstructionProperty_InternalHeatSource_FieldEnums.hxx>
#include <utilities/idd/ZoneHVAC_LowTemperatureRadiant_ConstantFlow_FieldEnums.hxx>
#include <utilities/idd/ZoneHVAC_LowTemperatureRadiant_ConstantFlow_Design_FieldEnums.hxx>
#include <utilities/idd/ZoneHVAC_LowTemperatureRadiant_SurfaceGroup_FieldEnums.hxx>
#include <utilities/idf/IdfExtensibleGroup.hpp>

#include <algorithm>

namespace openstudio {
namespace epmodel {
  namespace detail {

    constexpr const char* kDefaultFluidtoRadiantSurfaceHeatTransferModel = "ConvectionOnly";
    constexpr const char* kDefaultTemperatureControlType = "MeanAirTemperature";
    constexpr double kDefaultHydronicTubingInsideDiameter = 0.013;
    constexpr double kDefaultHydronicTubingOutsideDiameter = 0.016;
    constexpr double kDefaultHydronicTubingConductivity = 0.35;
    constexpr double kDefaultRunningMeanOutdoorDryBulbTemperatureWeightingFactor = 0.8;
    constexpr double kDefaultMotorEfficiency = 0.9;
    constexpr double kDefaultFractionofMotorInefficienciestoFluidStream = 0.0;

    // These companion coils are transient views over parent-owned storage, so they
    // still need a stable model-level identity while the parent exists. We key that
    // identity off the parent handle instead of the parent display name so a rename
    // does not orphan the transient child. The "__transient__" prefix is just a
    // blunt marker that this name is internal plumbing, not a user-facing naming
    // convention.
    std::string transientHeatingCoilName(const openstudio::epmodel::ZoneHVACLowTempRadiantConstFlow& parent) {
      return "__transient__" + openstudio::toString(parent.handle()) + "__heating_low_temp_radiant_const_flow";
    }

    std::string transientCoolingCoilName(const openstudio::epmodel::ZoneHVACLowTempRadiantConstFlow& parent) {
      return "__transient__" + openstudio::toString(parent.handle()) + "__cooling_low_temp_radiant_const_flow";
    }

    using SurfaceGroupFields = openstudio::ZoneHVAC_LowTemperatureRadiant_SurfaceGroupExtensibleFields;
    using SurfaceFields = openstudio::BuildingSurface_DetailedFields;
    using SurfaceVertexFields = openstudio::BuildingSurface_DetailedExtensibleFields;

    // The envelope side of epmodel is still relatively thin compared to the HVAC
    // side. In particular, this family does not yet have rich wrapper support for
    // radiant surface groups, internal-source construction relationships, or
    // surface geometry helpers at the same level as canonical openstudio::model.
    // For now we therefore do the honest low-level work here:
    // - inspect persisted BuildingSurface fields directly
    // - resolve the internal-heat-source relationship through the underlying fields
    // - populate the EnergyPlus surface-group extensible rows explicitly
    //
    // That is acceptable for this prototype because the goal is to preserve the
    // canonical public API while staying anchored to EnergyPlus storage. It should
    // be revisited as the envelope portion of epmodel grows more fully developed.
    bool surfaceMatchesRadiantSelection(const openstudio::epmodel::Surface& surface, const std::string& radiantSurfaceType) {
      const auto surfaceType = surface.surfaceType();
      const bool isCeilingLike = openstudio::istringEqual(surfaceType, "RoofCeiling") || openstudio::istringEqual(surfaceType, "Roof")
                                 || openstudio::istringEqual(surfaceType, "Ceiling");
      if (openstudio::istringEqual(radiantSurfaceType, "Ceilings")) {
        return isCeilingLike;
      }
      if (openstudio::istringEqual(radiantSurfaceType, "Floors")) {
        return openstudio::istringEqual(surfaceType, "Floor");
      }
      if (openstudio::istringEqual(radiantSurfaceType, "CeilingsandFloors")) {
        return isCeilingLike || openstudio::istringEqual(surfaceType, "Floor");
      }
      if (openstudio::istringEqual(radiantSurfaceType, "AllSurfaces")) {
        return true;
      }
      return false;
    }

    bool surfaceHasInternalSourceConstruction(const openstudio::epmodel::Surface& surface) {
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

    std::vector<openstudio::Point3d> surfaceVertices(const openstudio::epmodel::Surface& surface) {
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

    double surfaceGrossArea(const openstudio::epmodel::Surface& surface) {
      const auto vertices = surfaceVertices(surface);
      if (vertices.size() < 3u) {
        return 0.0;
      }
      if (const auto area = openstudio::getArea(vertices)) {
        return *area;
      }
      return 0.0;
    }

    std::vector<openstudio::epmodel::Surface> eligibleRadiantSurfaces(const openstudio::epmodel::Model& model,
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
        if (!surfaceHasInternalSourceConstruction(surface)) {
          continue;
        }
        if (!surfaceMatchesRadiantSelection(surface, radiantSurfaceType)) {
          continue;
        }
        result.push_back(surface);
      }

      return result;
    }

    bool sameConstFlowSurfaceSet(const std::vector<openstudio::epmodel::Surface>& lhs, const std::vector<openstudio::epmodel::Surface>& rhs) {
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

  ZoneHVACLowTempRadiantConstFlow::ZoneHVACLowTempRadiantConstFlow(const Model& model)
    : ZoneHVACComponent(ZoneHVACLowTempRadiantConstFlow::iddObjectType(), model) {
    auto impl = getImpl<detail::ZoneHVACLowTempRadiantConstFlow_Impl>();
    OS_ASSERT(impl);
    impl->ensureDesignObject();
  }

  ZoneHVACLowTempRadiantConstFlow::ZoneHVACLowTempRadiantConstFlow(const Model& model, Schedule& availabilitySchedule, HVACComponent& heatingCoil,
                                                                   HVACComponent& coolingCoil, double hydronicTubingLength)
    : ZoneHVACLowTempRadiantConstFlow(model) {
    OS_ASSERT(setAvailabilitySchedule(availabilitySchedule));
    OS_ASSERT(setHeatingCoil(heatingCoil));
    OS_ASSERT(setCoolingCoil(coolingCoil));
    OS_ASSERT(setHydronicTubingLength(hydronicTubingLength));
  }

  ZoneHVACLowTempRadiantConstFlow::ZoneHVACLowTempRadiantConstFlow(const Model& model, Schedule& availabilitySchedule, HVACComponent& heatingCoil,
                                                                   HVACComponent& coolingCoil)
    : ZoneHVACLowTempRadiantConstFlow(model) {
    OS_ASSERT(setAvailabilitySchedule(availabilitySchedule));
    OS_ASSERT(setHeatingCoil(heatingCoil));
    OS_ASSERT(setCoolingCoil(coolingCoil));
    autosizeHydronicTubingLength();
  }

  ZoneHVACLowTempRadiantConstFlow::ZoneHVACLowTempRadiantConstFlow(std::shared_ptr<detail::ZoneHVACLowTempRadiantConstFlow_Impl> impl)
    : ZoneHVACComponent(std::move(impl)) {}

  IddObjectType ZoneHVACLowTempRadiantConstFlow::iddObjectType() {
    return IddObjectType::ZoneHVAC_LowTemperatureRadiant_ConstantFlow;
  }

  std::vector<std::string> ZoneHVACLowTempRadiantConstFlow::radiantSurfaceTypeValues() {
    static const std::vector<std::string> values{"Ceilings", "Floors", "CeilingsandFloors", "AllSurfaces"};
    return values;
  }

  std::vector<std::string> ZoneHVACLowTempRadiantConstFlow::numberofCircuitsValues() {
    return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(),
                          ZoneHVAC_LowTemperatureRadiant_ConstantFlowFields::NumberofCircuits);
  }

  std::vector<std::string> ZoneHVACLowTempRadiantConstFlow::fluidtoRadiantSurfaceHeatTransferModelValues() {
    return getIddKeyNames(IddFactory::instance().getObject(IddObjectType::ZoneHVAC_LowTemperatureRadiant_ConstantFlow_Design).get(),
                          ZoneHVAC_LowTemperatureRadiant_ConstantFlow_DesignFields::FluidtoRadiantSurfaceHeatTransferModel);
  }

  std::vector<std::string> ZoneHVACLowTempRadiantConstFlow::temperatureControlTypeValues() {
    return getIddKeyNames(IddFactory::instance().getObject(IddObjectType::ZoneHVAC_LowTemperatureRadiant_ConstantFlow_Design).get(),
                          ZoneHVAC_LowTemperatureRadiant_ConstantFlow_DesignFields::TemperatureControlType);
  }

  boost::optional<Schedule> ZoneHVACLowTempRadiantConstFlow::availabilitySchedule() const {
    return getImpl<detail::ZoneHVACLowTempRadiantConstFlow_Impl>()->availabilitySchedule();
  }

  bool ZoneHVACLowTempRadiantConstFlow::setAvailabilitySchedule(Schedule& schedule) {
    return getImpl<detail::ZoneHVACLowTempRadiantConstFlow_Impl>()->setAvailabilitySchedule(schedule);
  }

  void ZoneHVACLowTempRadiantConstFlow::resetAvailabilitySchedule() {
    getImpl<detail::ZoneHVACLowTempRadiantConstFlow_Impl>()->resetAvailabilitySchedule();
  }

  boost::optional<std::string> ZoneHVACLowTempRadiantConstFlow::radiantSurfaceType() const {
    return getImpl<detail::ZoneHVACLowTempRadiantConstFlow_Impl>()->radiantSurfaceType();
  }

  bool ZoneHVACLowTempRadiantConstFlow::setRadiantSurfaceType(const std::string& radiantSurfaceType) {
    return getImpl<detail::ZoneHVACLowTempRadiantConstFlow_Impl>()->setRadiantSurfaceType(radiantSurfaceType);
  }

  void ZoneHVACLowTempRadiantConstFlow::resetRadiantSurfaceType() {
    getImpl<detail::ZoneHVACLowTempRadiantConstFlow_Impl>()->resetRadiantSurfaceType();
  }

  std::vector<Surface> ZoneHVACLowTempRadiantConstFlow::surfaces() const {
    return getImpl<detail::ZoneHVACLowTempRadiantConstFlow_Impl>()->surfaces();
  }

  CoilHeatingLowTempRadiantConstFlow ZoneHVACLowTempRadiantConstFlow::heatingCoil() const {
    return getImpl<detail::ZoneHVACLowTempRadiantConstFlow_Impl>()->heatingCoil();
  }

  bool ZoneHVACLowTempRadiantConstFlow::setHeatingCoil(HVACComponent& heatingCoil) {
    return getImpl<detail::ZoneHVACLowTempRadiantConstFlow_Impl>()->setHeatingCoil(heatingCoil);
  }

  CoilCoolingLowTempRadiantConstFlow ZoneHVACLowTempRadiantConstFlow::coolingCoil() const {
    return getImpl<detail::ZoneHVACLowTempRadiantConstFlow_Impl>()->coolingCoil();
  }

  bool ZoneHVACLowTempRadiantConstFlow::setCoolingCoil(HVACComponent& coolingCoil) {
    return getImpl<detail::ZoneHVACLowTempRadiantConstFlow_Impl>()->setCoolingCoil(coolingCoil);
  }

  boost::optional<Schedule> ZoneHVACLowTempRadiantConstFlow::pumpFlowRateSchedule() const {
    return getImpl<detail::ZoneHVACLowTempRadiantConstFlow_Impl>()->pumpFlowRateSchedule();
  }

  bool ZoneHVACLowTempRadiantConstFlow::setPumpFlowRateSchedule(Schedule& schedule) {
    return getImpl<detail::ZoneHVACLowTempRadiantConstFlow_Impl>()->setPumpFlowRateSchedule(schedule);
  }

  void ZoneHVACLowTempRadiantConstFlow::resetPumpFlowRateSchedule() {
    getImpl<detail::ZoneHVACLowTempRadiantConstFlow_Impl>()->resetPumpFlowRateSchedule();
  }

  boost::optional<Schedule> ZoneHVACLowTempRadiantConstFlow::changeoverDelayTimePeriodSchedule() const {
    return getImpl<detail::ZoneHVACLowTempRadiantConstFlow_Impl>()->changeoverDelayTimePeriodSchedule();
  }

  bool ZoneHVACLowTempRadiantConstFlow::setChangeoverDelayTimePeriodSchedule(Schedule& schedule) {
    return getImpl<detail::ZoneHVACLowTempRadiantConstFlow_Impl>()->setChangeoverDelayTimePeriodSchedule(schedule);
  }

  void ZoneHVACLowTempRadiantConstFlow::resetChangeoverDelayTimePeriodSchedule() {
    getImpl<detail::ZoneHVACLowTempRadiantConstFlow_Impl>()->resetChangeoverDelayTimePeriodSchedule();
  }

  std::vector<ModelObject> ZoneHVACLowTempRadiantConstFlow::children() const {
    return getImpl<detail::ZoneHVACLowTempRadiantConstFlow_Impl>()->children();
  }

  boost::optional<ZoneHVACLowTempRadiantConstFlowDesign> ZoneHVACLowTempRadiantConstFlow::designObject() const {
    return getImpl<detail::ZoneHVACLowTempRadiantConstFlow_Impl>()->designObject();
  }

  boost::optional<ZoneHVACLowTemperatureRadiantSurfaceGroup> ZoneHVACLowTempRadiantConstFlow::surfaceGroup() const {
    return getImpl<detail::ZoneHVACLowTempRadiantConstFlow_Impl>()->surfaceGroup();
  }

  std::string ZoneHVACLowTempRadiantConstFlow::fluidtoRadiantSurfaceHeatTransferModel() const {
    return getImpl<detail::ZoneHVACLowTempRadiantConstFlow_Impl>()->fluidtoRadiantSurfaceHeatTransferModel();
  }

  bool ZoneHVACLowTempRadiantConstFlow::isFluidtoRadiantSurfaceHeatTransferModelDefaulted() const {
    return getImpl<detail::ZoneHVACLowTempRadiantConstFlow_Impl>()->isFluidtoRadiantSurfaceHeatTransferModelDefaulted();
  }

  bool ZoneHVACLowTempRadiantConstFlow::setFluidtoRadiantSurfaceHeatTransferModel(const std::string& fluidtoRadiantSurfaceHeatTransferModel) {
    return getImpl<detail::ZoneHVACLowTempRadiantConstFlow_Impl>()->setFluidtoRadiantSurfaceHeatTransferModel(fluidtoRadiantSurfaceHeatTransferModel);
  }

  void ZoneHVACLowTempRadiantConstFlow::resetFluidtoRadiantSurfaceHeatTransferModel() {
    getImpl<detail::ZoneHVACLowTempRadiantConstFlow_Impl>()->resetFluidtoRadiantSurfaceHeatTransferModel();
  }

  double ZoneHVACLowTempRadiantConstFlow::hydronicTubingInsideDiameter() const {
    return getImpl<detail::ZoneHVACLowTempRadiantConstFlow_Impl>()->hydronicTubingInsideDiameter();
  }

  bool ZoneHVACLowTempRadiantConstFlow::isHydronicTubingInsideDiameterDefaulted() const {
    return getImpl<detail::ZoneHVACLowTempRadiantConstFlow_Impl>()->isHydronicTubingInsideDiameterDefaulted();
  }

  bool ZoneHVACLowTempRadiantConstFlow::setHydronicTubingInsideDiameter(double hydronicTubingInsideDiameter) {
    return getImpl<detail::ZoneHVACLowTempRadiantConstFlow_Impl>()->setHydronicTubingInsideDiameter(hydronicTubingInsideDiameter);
  }

  void ZoneHVACLowTempRadiantConstFlow::resetHydronicTubingInsideDiameter() {
    getImpl<detail::ZoneHVACLowTempRadiantConstFlow_Impl>()->resetHydronicTubingInsideDiameter();
  }

  double ZoneHVACLowTempRadiantConstFlow::hydronicTubingOutsideDiameter() const {
    return getImpl<detail::ZoneHVACLowTempRadiantConstFlow_Impl>()->hydronicTubingOutsideDiameter();
  }

  bool ZoneHVACLowTempRadiantConstFlow::isHydronicTubingOutsideDiameterDefaulted() const {
    return getImpl<detail::ZoneHVACLowTempRadiantConstFlow_Impl>()->isHydronicTubingOutsideDiameterDefaulted();
  }

  bool ZoneHVACLowTempRadiantConstFlow::setHydronicTubingOutsideDiameter(double hydronicTubingOutsideDiameter) {
    return getImpl<detail::ZoneHVACLowTempRadiantConstFlow_Impl>()->setHydronicTubingOutsideDiameter(hydronicTubingOutsideDiameter);
  }

  void ZoneHVACLowTempRadiantConstFlow::resetHydronicTubingOutsideDiameter() {
    getImpl<detail::ZoneHVACLowTempRadiantConstFlow_Impl>()->resetHydronicTubingOutsideDiameter();
  }

  double ZoneHVACLowTempRadiantConstFlow::hydronicTubingConductivity() const {
    return getImpl<detail::ZoneHVACLowTempRadiantConstFlow_Impl>()->hydronicTubingConductivity();
  }

  bool ZoneHVACLowTempRadiantConstFlow::isHydronicTubingConductivityDefaulted() const {
    return getImpl<detail::ZoneHVACLowTempRadiantConstFlow_Impl>()->isHydronicTubingConductivityDefaulted();
  }

  bool ZoneHVACLowTempRadiantConstFlow::setHydronicTubingConductivity(double hydronicTubingConductivity) {
    return getImpl<detail::ZoneHVACLowTempRadiantConstFlow_Impl>()->setHydronicTubingConductivity(hydronicTubingConductivity);
  }

  void ZoneHVACLowTempRadiantConstFlow::resetHydronicTubingConductivity() {
    getImpl<detail::ZoneHVACLowTempRadiantConstFlow_Impl>()->resetHydronicTubingConductivity();
  }

  std::string ZoneHVACLowTempRadiantConstFlow::temperatureControlType() const {
    return getImpl<detail::ZoneHVACLowTempRadiantConstFlow_Impl>()->temperatureControlType();
  }

  bool ZoneHVACLowTempRadiantConstFlow::isTemperatureControlTypeDefaulted() const {
    return getImpl<detail::ZoneHVACLowTempRadiantConstFlow_Impl>()->isTemperatureControlTypeDefaulted();
  }

  bool ZoneHVACLowTempRadiantConstFlow::setTemperatureControlType(const std::string& temperatureControlType) {
    return getImpl<detail::ZoneHVACLowTempRadiantConstFlow_Impl>()->setTemperatureControlType(temperatureControlType);
  }

  void ZoneHVACLowTempRadiantConstFlow::resetTemperatureControlType() {
    getImpl<detail::ZoneHVACLowTempRadiantConstFlow_Impl>()->resetTemperatureControlType();
  }

  double ZoneHVACLowTempRadiantConstFlow::runningMeanOutdoorDryBulbTemperatureWeightingFactor() const {
    return getImpl<detail::ZoneHVACLowTempRadiantConstFlow_Impl>()->runningMeanOutdoorDryBulbTemperatureWeightingFactor();
  }

  bool ZoneHVACLowTempRadiantConstFlow::isRunningMeanOutdoorDryBulbTemperatureWeightingFactorDefaulted() const {
    return getImpl<detail::ZoneHVACLowTempRadiantConstFlow_Impl>()->isRunningMeanOutdoorDryBulbTemperatureWeightingFactorDefaulted();
  }

  bool ZoneHVACLowTempRadiantConstFlow::setRunningMeanOutdoorDryBulbTemperatureWeightingFactor(
    double runningMeanOutdoorDryBulbTemperatureWeightingFactor) {
    return getImpl<detail::ZoneHVACLowTempRadiantConstFlow_Impl>()->setRunningMeanOutdoorDryBulbTemperatureWeightingFactor(
      runningMeanOutdoorDryBulbTemperatureWeightingFactor);
  }

  void ZoneHVACLowTempRadiantConstFlow::resetRunningMeanOutdoorDryBulbTemperatureWeightingFactor() {
    getImpl<detail::ZoneHVACLowTempRadiantConstFlow_Impl>()->resetRunningMeanOutdoorDryBulbTemperatureWeightingFactor();
  }

  double ZoneHVACLowTempRadiantConstFlow::motorEfficiency() const {
    return getImpl<detail::ZoneHVACLowTempRadiantConstFlow_Impl>()->motorEfficiency();
  }

  bool ZoneHVACLowTempRadiantConstFlow::isMotorEfficiencyDefaulted() const {
    return getImpl<detail::ZoneHVACLowTempRadiantConstFlow_Impl>()->isMotorEfficiencyDefaulted();
  }

  bool ZoneHVACLowTempRadiantConstFlow::setMotorEfficiency(double motorEfficiency) {
    return getImpl<detail::ZoneHVACLowTempRadiantConstFlow_Impl>()->setMotorEfficiency(motorEfficiency);
  }

  void ZoneHVACLowTempRadiantConstFlow::resetMotorEfficiency() {
    getImpl<detail::ZoneHVACLowTempRadiantConstFlow_Impl>()->resetMotorEfficiency();
  }

  double ZoneHVACLowTempRadiantConstFlow::fractionofMotorInefficienciestoFluidStream() const {
    return getImpl<detail::ZoneHVACLowTempRadiantConstFlow_Impl>()->fractionofMotorInefficienciestoFluidStream();
  }

  bool ZoneHVACLowTempRadiantConstFlow::isFractionofMotorInefficienciestoFluidStreamDefaulted() const {
    return getImpl<detail::ZoneHVACLowTempRadiantConstFlow_Impl>()->isFractionofMotorInefficienciestoFluidStreamDefaulted();
  }

  bool ZoneHVACLowTempRadiantConstFlow::setFractionofMotorInefficienciestoFluidStream(double fractionofMotorInefficienciestoFluidStream) {
    return getImpl<detail::ZoneHVACLowTempRadiantConstFlow_Impl>()->setFractionofMotorInefficienciestoFluidStream(
      fractionofMotorInefficienciestoFluidStream);
  }

  void ZoneHVACLowTempRadiantConstFlow::resetFractionofMotorInefficienciestoFluidStream() {
    getImpl<detail::ZoneHVACLowTempRadiantConstFlow_Impl>()->resetFractionofMotorInefficienciestoFluidStream();
  }

  boost::optional<double> ZoneHVACLowTempRadiantConstFlow::hydronicTubingLength() const {
    return getImpl<detail::ZoneHVACLowTempRadiantConstFlow_Impl>()->hydronicTubingLength();
  }

  boost::optional<double> ZoneHVACLowTempRadiantConstFlow::autosizedHydronicTubingLength() const {
    return getImpl<detail::ZoneHVACLowTempRadiantConstFlow_Impl>()->autosizedHydronicTubingLength();
  }

  bool ZoneHVACLowTempRadiantConstFlow::isHydronicTubingLengthAutosized() const {
    return getImpl<detail::ZoneHVACLowTempRadiantConstFlow_Impl>()->isHydronicTubingLengthAutosized();
  }

  bool ZoneHVACLowTempRadiantConstFlow::setHydronicTubingLength(double hydronicTubingLength) {
    return getImpl<detail::ZoneHVACLowTempRadiantConstFlow_Impl>()->setHydronicTubingLength(hydronicTubingLength);
  }

  void ZoneHVACLowTempRadiantConstFlow::autosizeHydronicTubingLength() {
    getImpl<detail::ZoneHVACLowTempRadiantConstFlow_Impl>()->autosizeHydronicTubingLength();
  }

  boost::optional<double> ZoneHVACLowTempRadiantConstFlow::ratedFlowRate() const {
    return getImpl<detail::ZoneHVACLowTempRadiantConstFlow_Impl>()->ratedFlowRate();
  }

  boost::optional<double> ZoneHVACLowTempRadiantConstFlow::autosizedRatedFlowRate() const {
    return getImpl<detail::ZoneHVACLowTempRadiantConstFlow_Impl>()->autosizedRatedFlowRate();
  }

  bool ZoneHVACLowTempRadiantConstFlow::isRatedFlowRateAutosized() const {
    return getImpl<detail::ZoneHVACLowTempRadiantConstFlow_Impl>()->isRatedFlowRateAutosized();
  }

  bool ZoneHVACLowTempRadiantConstFlow::setRatedFlowRate(double ratedFlowRate) {
    return getImpl<detail::ZoneHVACLowTempRadiantConstFlow_Impl>()->setRatedFlowRate(ratedFlowRate);
  }

  void ZoneHVACLowTempRadiantConstFlow::autosizeRatedFlowRate() {
    getImpl<detail::ZoneHVACLowTempRadiantConstFlow_Impl>()->autosizeRatedFlowRate();
  }

  double ZoneHVACLowTempRadiantConstFlow::ratedPumpHead() const {
    return getImpl<detail::ZoneHVACLowTempRadiantConstFlow_Impl>()->ratedPumpHead();
  }

  bool ZoneHVACLowTempRadiantConstFlow::isRatedPumpHeadDefaulted() const {
    return getImpl<detail::ZoneHVACLowTempRadiantConstFlow_Impl>()->isRatedPumpHeadDefaulted();
  }

  bool ZoneHVACLowTempRadiantConstFlow::setRatedPumpHead(double ratedPumpHead) {
    return getImpl<detail::ZoneHVACLowTempRadiantConstFlow_Impl>()->setRatedPumpHead(ratedPumpHead);
  }

  void ZoneHVACLowTempRadiantConstFlow::resetRatedPumpHead() {
    getImpl<detail::ZoneHVACLowTempRadiantConstFlow_Impl>()->resetRatedPumpHead();
  }

  boost::optional<double> ZoneHVACLowTempRadiantConstFlow::ratedPowerConsumption() const {
    return getImpl<detail::ZoneHVACLowTempRadiantConstFlow_Impl>()->ratedPowerConsumption();
  }

  bool ZoneHVACLowTempRadiantConstFlow::setRatedPowerConsumption(double ratedPowerConsumption) {
    return getImpl<detail::ZoneHVACLowTempRadiantConstFlow_Impl>()->setRatedPowerConsumption(ratedPowerConsumption);
  }

  void ZoneHVACLowTempRadiantConstFlow::resetRatedPowerConsumption() {
    getImpl<detail::ZoneHVACLowTempRadiantConstFlow_Impl>()->resetRatedPowerConsumption();
  }

  std::string ZoneHVACLowTempRadiantConstFlow::numberofCircuits() const {
    return getImpl<detail::ZoneHVACLowTempRadiantConstFlow_Impl>()->numberofCircuits();
  }

  bool ZoneHVACLowTempRadiantConstFlow::isNumberofCircuitsDefaulted() const {
    return getImpl<detail::ZoneHVACLowTempRadiantConstFlow_Impl>()->isNumberofCircuitsDefaulted();
  }

  bool ZoneHVACLowTempRadiantConstFlow::setNumberofCircuits(const std::string& numberofCircuits) {
    return getImpl<detail::ZoneHVACLowTempRadiantConstFlow_Impl>()->setNumberofCircuits(numberofCircuits);
  }

  void ZoneHVACLowTempRadiantConstFlow::resetNumberofCircuits() {
    getImpl<detail::ZoneHVACLowTempRadiantConstFlow_Impl>()->resetNumberofCircuits();
  }

  double ZoneHVACLowTempRadiantConstFlow::circuitLength() const {
    return getImpl<detail::ZoneHVACLowTempRadiantConstFlow_Impl>()->circuitLength();
  }

  bool ZoneHVACLowTempRadiantConstFlow::isCircuitLengthDefaulted() const {
    return getImpl<detail::ZoneHVACLowTempRadiantConstFlow_Impl>()->isCircuitLengthDefaulted();
  }

  bool ZoneHVACLowTempRadiantConstFlow::setCircuitLength(double circuitLength) {
    return getImpl<detail::ZoneHVACLowTempRadiantConstFlow_Impl>()->setCircuitLength(circuitLength);
  }

  void ZoneHVACLowTempRadiantConstFlow::resetCircuitLength() {
    getImpl<detail::ZoneHVACLowTempRadiantConstFlow_Impl>()->resetCircuitLength();
  }

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
  namespace detail {

    unsigned ZoneHVACLowTempRadiantConstFlow_Impl::inletPort() const {
      return 0u;
    }

    unsigned ZoneHVACLowTempRadiantConstFlow_Impl::outletPort() const {
      return 0u;
    }

    boost::optional<Schedule> ZoneHVACLowTempRadiantConstFlow_Impl::availabilitySchedule() const {
      return getObject<ModelObject>().getModelObjectTarget<Schedule>(
        openstudio::ZoneHVAC_LowTemperatureRadiant_ConstantFlowFields::AvailabilityScheduleName);
    }

    bool ZoneHVACLowTempRadiantConstFlow_Impl::setAvailabilitySchedule(Schedule& schedule) {
      return setPointer(openstudio::ZoneHVAC_LowTemperatureRadiant_ConstantFlowFields::AvailabilityScheduleName, schedule.handle(), false);
    }

    void ZoneHVACLowTempRadiantConstFlow_Impl::resetAvailabilitySchedule() {
      OS_ASSERT(setString(openstudio::ZoneHVAC_LowTemperatureRadiant_ConstantFlowFields::AvailabilityScheduleName, "", false));
    }

    boost::optional<std::string> ZoneHVACLowTempRadiantConstFlow_Impl::radiantSurfaceType() const {
      const auto groupSurfaces = surfaces();
      if (groupSurfaces.empty()) {
        return boost::none;
      }

      const auto zone = thermalZone();
      if (!zone) {
        return boost::none;
      }

      for (const auto& candidate : openstudio::epmodel::ZoneHVACLowTempRadiantConstFlow::radiantSurfaceTypeValues()) {
        if (detail::sameConstFlowSurfaceSet(groupSurfaces, detail::eligibleRadiantSurfaces(model(), *zone, candidate))) {
          return candidate;
        }
      }

      return boost::none;
    }

    bool ZoneHVACLowTempRadiantConstFlow_Impl::setRadiantSurfaceType(const std::string& radiantSurfaceType) {
      const auto validTypes = openstudio::epmodel::ZoneHVACLowTempRadiantConstFlow::radiantSurfaceTypeValues();
      if (std::find_if(validTypes.begin(), validTypes.end(),
                       [&](const std::string& candidate) { return openstudio::istringEqual(candidate, radiantSurfaceType); })
          == validTypes.end()) {
        return false;
      }

      auto zone = thermalZone();
      if (!zone) {
        return false;
      }

      auto groupObject = ensureSurfaceGroup();
      groupObject.getImpl<detail::ZoneHVACLowTemperatureRadiantSurfaceGroup_Impl>()->clearSurfaces();

      // For now this is a snapshot rewrite of the persisted EnergyPlus surface
      // group. We are not yet trying to hook later zone or surface edits back into
      // this membership automatically.
      const auto groupSurfaces = detail::eligibleRadiantSurfaces(model(), *zone, radiantSurfaceType);
      double totalArea = 0.0;
      for (const auto& surface : groupSurfaces) {
        totalArea += detail::surfaceGrossArea(surface);
      }

      const double fallbackFraction = groupSurfaces.empty() ? 0.0 : (1.0 / static_cast<double>(groupSurfaces.size()));
      for (const auto& surface : groupSurfaces) {
        const double area = detail::surfaceGrossArea(surface);
        const double fraction = (totalArea > 0.0) ? (area / totalArea) : fallbackFraction;
        if (!groupObject.getImpl<detail::ZoneHVACLowTemperatureRadiantSurfaceGroup_Impl>()->addSurface(const_cast<Surface&>(surface), fraction)) {
          return false;
        }
      }

      return true;
    }

    void ZoneHVACLowTempRadiantConstFlow_Impl::resetRadiantSurfaceType() {
      if (auto zone = thermalZone()) {
        OS_ASSERT(setRadiantSurfaceType("Ceilings"));
      } else if (auto group = surfaceGroup()) {
        group->getImpl<detail::ZoneHVACLowTemperatureRadiantSurfaceGroup_Impl>()->clearSurfaces();
      }
    }

    std::vector<Surface> ZoneHVACLowTempRadiantConstFlow_Impl::surfaces() const {
      if (auto groupObject = surfaceGroup()) {
        return groupObject->getImpl<detail::ZoneHVACLowTemperatureRadiantSurfaceGroup_Impl>()->surfaces();
      }
      return {};
    }

    CoilHeatingLowTempRadiantConstFlow ZoneHVACLowTempRadiantConstFlow_Impl::heatingCoil() const {
      const auto parent = getObject<openstudio::epmodel::ZoneHVACLowTempRadiantConstFlow>();
      return model().getOrCreateTransientByName<openstudio::epmodel::CoilHeatingLowTempRadiantConstFlow>(detail::transientHeatingCoilName(parent));
    }

    bool ZoneHVACLowTempRadiantConstFlow_Impl::setHeatingCoil(HVACComponent& heatingCoil) {
      auto source = heatingCoil.optionalCast<CoilHeatingLowTempRadiantConstFlow>();
      if (!source) {
        return false;
      }

      auto target = this->heatingCoil();
      bool result = true;

      if (auto schedule = source->heatingHighWaterTemperatureSchedule()) {
        result = target.setHeatingHighWaterTemperatureSchedule(*schedule) && result;
      } else {
        target.resetHeatingHighWaterTemperatureSchedule();
      }

      if (auto schedule = source->heatingLowWaterTemperatureSchedule()) {
        result = target.setHeatingLowWaterTemperatureSchedule(*schedule) && result;
      } else {
        target.resetHeatingLowWaterTemperatureSchedule();
      }

      if (auto schedule = source->heatingHighControlTemperatureSchedule()) {
        result = target.setHeatingHighControlTemperatureSchedule(*schedule) && result;
      } else {
        target.resetHeatingHighControlTemperatureSchedule();
      }

      if (auto schedule = source->heatingLowControlTemperatureSchedule()) {
        result = target.setHeatingLowControlTemperatureSchedule(*schedule) && result;
      } else {
        target.resetHeatingLowControlTemperatureSchedule();
      }

      if (auto inlet = source->inletModelObject()) {
        if (auto node = inlet->optionalCast<Node>()) {
          result =
            setPointer(openstudio::ZoneHVAC_LowTemperatureRadiant_ConstantFlowFields::HeatingWaterInletNodeName, node->handle(), false) && result;
        }
      } else {
        result = setString(openstudio::ZoneHVAC_LowTemperatureRadiant_ConstantFlowFields::HeatingWaterInletNodeName, "", false) && result;
      }

      if (auto outlet = source->outletModelObject()) {
        if (auto node = outlet->optionalCast<Node>()) {
          result =
            setPointer(openstudio::ZoneHVAC_LowTemperatureRadiant_ConstantFlowFields::HeatingWaterOutletNodeName, node->handle(), false) && result;
        }
      } else {
        result = setString(openstudio::ZoneHVAC_LowTemperatureRadiant_ConstantFlowFields::HeatingWaterOutletNodeName, "", false) && result;
      }

      return result;
    }

    CoilCoolingLowTempRadiantConstFlow ZoneHVACLowTempRadiantConstFlow_Impl::coolingCoil() const {
      const auto parent = getObject<openstudio::epmodel::ZoneHVACLowTempRadiantConstFlow>();
      return model().getOrCreateTransientByName<openstudio::epmodel::CoilCoolingLowTempRadiantConstFlow>(detail::transientCoolingCoilName(parent));
    }

    bool ZoneHVACLowTempRadiantConstFlow_Impl::setCoolingCoil(HVACComponent& coolingCoil) {
      auto source = coolingCoil.optionalCast<CoilCoolingLowTempRadiantConstFlow>();
      if (!source) {
        return false;
      }

      auto target = this->coolingCoil();
      bool result = true;

      if (auto schedule = source->coolingHighWaterTemperatureSchedule()) {
        result = target.setCoolingHighWaterTemperatureSchedule(*schedule) && result;
      } else {
        target.resetCoolingHighWaterTemperatureSchedule();
      }

      if (auto schedule = source->coolingLowWaterTemperatureSchedule()) {
        result = target.setCoolingLowWaterTemperatureSchedule(*schedule) && result;
      } else {
        target.resetCoolingLowWaterTemperatureSchedule();
      }

      if (auto schedule = source->coolingHighControlTemperatureSchedule()) {
        result = target.setCoolingHighControlTemperatureSchedule(*schedule) && result;
      } else {
        target.resetCoolingHighControlTemperatureSchedule();
      }

      if (auto schedule = source->coolingLowControlTemperatureSchedule()) {
        result = target.setCoolingLowControlTemperatureSchedule(*schedule) && result;
      } else {
        target.resetCoolingLowControlTemperatureSchedule();
      }

      if (source->isCondensationControlTypeDefaulted()) {
        target.resetCondensationControlType();
      } else {
        result = target.setCondensationControlType(source->condensationControlType()) && result;
      }

      if (source->isCondensationControlDewpointOffsetDefaulted()) {
        target.resetCondensationControlDewpointOffset();
      } else {
        result = target.setCondensationControlDewpointOffset(source->condensationControlDewpointOffset()) && result;
      }

      if (auto inlet = source->inletModelObject()) {
        if (auto node = inlet->optionalCast<Node>()) {
          result =
            setPointer(openstudio::ZoneHVAC_LowTemperatureRadiant_ConstantFlowFields::CoolingWaterInletNodeName, node->handle(), false) && result;
        }
      } else {
        result = setString(openstudio::ZoneHVAC_LowTemperatureRadiant_ConstantFlowFields::CoolingWaterInletNodeName, "", false) && result;
      }

      if (auto outlet = source->outletModelObject()) {
        if (auto node = outlet->optionalCast<Node>()) {
          result =
            setPointer(openstudio::ZoneHVAC_LowTemperatureRadiant_ConstantFlowFields::CoolingWaterOutletNodeName, node->handle(), false) && result;
        }
      } else {
        result = setString(openstudio::ZoneHVAC_LowTemperatureRadiant_ConstantFlowFields::CoolingWaterOutletNodeName, "", false) && result;
      }

      return result;
    }

    boost::optional<Schedule> ZoneHVACLowTempRadiantConstFlow_Impl::pumpFlowRateSchedule() const {
      return getObject<ModelObject>().getModelObjectTarget<Schedule>(
        openstudio::ZoneHVAC_LowTemperatureRadiant_ConstantFlowFields::PumpFlowRateScheduleName);
    }

    bool ZoneHVACLowTempRadiantConstFlow_Impl::setPumpFlowRateSchedule(Schedule& schedule) {
      return setPointer(openstudio::ZoneHVAC_LowTemperatureRadiant_ConstantFlowFields::PumpFlowRateScheduleName, schedule.handle(), false);
    }

    void ZoneHVACLowTempRadiantConstFlow_Impl::resetPumpFlowRateSchedule() {
      OS_ASSERT(setString(openstudio::ZoneHVAC_LowTemperatureRadiant_ConstantFlowFields::PumpFlowRateScheduleName, "", false));
    }

    boost::optional<Schedule> ZoneHVACLowTempRadiantConstFlow_Impl::changeoverDelayTimePeriodSchedule() const {
      if (auto design = designObject()) {
        return design->getImpl<detail::ZoneHVACLowTempRadiantConstFlowDesign_Impl>()->changeoverDelayTimePeriodSchedule();
      }
      return boost::none;
    }

    bool ZoneHVACLowTempRadiantConstFlow_Impl::setChangeoverDelayTimePeriodSchedule(Schedule& schedule) {
      auto design = ensureDesignObject();
      return design.getImpl<detail::ZoneHVACLowTempRadiantConstFlowDesign_Impl>()->setChangeoverDelayTimePeriodSchedule(schedule);
    }

    void ZoneHVACLowTempRadiantConstFlow_Impl::resetChangeoverDelayTimePeriodSchedule() {
      auto design = ensureDesignObject();
      design.getImpl<detail::ZoneHVACLowTempRadiantConstFlowDesign_Impl>()->resetChangeoverDelayTimePeriodSchedule();
    }

    std::vector<ModelObject> ZoneHVACLowTempRadiantConstFlow_Impl::children() const {
      return {heatingCoil().cast<ModelObject>(), coolingCoil().cast<ModelObject>()};
    }

    void ZoneHVACLowTempRadiantConstFlow_Impl::doCanonicalize(LoadContext& context) {
      if (context.repairEnabled()) {
        ensureDesignObject();
      }
    }

    boost::optional<ZoneHVACLowTempRadiantConstFlowDesign> ZoneHVACLowTempRadiantConstFlow_Impl::designObject() const {
      if (auto target = getTarget(openstudio::ZoneHVAC_LowTemperatureRadiant_ConstantFlowFields::DesignObject)) {
        if (auto typed = target->optionalCast<ZoneHVACLowTempRadiantConstFlowDesign>()) {
          return *typed;
        }
      }

      if (auto name = getString(openstudio::ZoneHVAC_LowTemperatureRadiant_ConstantFlowFields::DesignObject, true); name && !name->empty()) {
        if (auto obj = workspace().getObjectByTypeAndName(IddObjectType::ZoneHVAC_LowTemperatureRadiant_ConstantFlow_Design, *name, true)) {
          if (auto typed = obj->optionalCast<ZoneHVACLowTempRadiantConstFlowDesign>()) {
            auto* self = const_cast<ZoneHVACLowTempRadiantConstFlow_Impl*>(this);
            self->setPointer(openstudio::ZoneHVAC_LowTemperatureRadiant_ConstantFlowFields::DesignObject, typed->handle(), false);
            return *typed;
          }
        }
      }

      return boost::none;
    }

    ZoneHVACLowTempRadiantConstFlowDesign ZoneHVACLowTempRadiantConstFlow_Impl::ensureDesignObject() {
      if (auto existing = designObject()) {
        return *existing;
      }

      ZoneHVACLowTempRadiantConstFlowDesign created(model());
      if (const auto existingName = getString(openstudio::ZoneHVAC_LowTemperatureRadiant_ConstantFlowFields::DesignObject, true);
          existingName && !existingName->empty()) {
        created.setName(*existingName);
      } else {
        created.setName(getObject<ModelObject>().nameString() + " Design");
      }
      OS_ASSERT(setPointer(openstudio::ZoneHVAC_LowTemperatureRadiant_ConstantFlowFields::DesignObject, created.handle(), false));
      return created;
    }

    boost::optional<ZoneHVACLowTemperatureRadiantSurfaceGroup> ZoneHVACLowTempRadiantConstFlow_Impl::surfaceGroup() const {
      // Ordinary typed access should reflect the persisted relationship that is
      // already linked, not silently repair it by stored name. Repair and
      // materialization belong in canonicalization or setter-side helper paths.
      if (auto target = getTarget(openstudio::ZoneHVAC_LowTemperatureRadiant_ConstantFlowFields::SurfaceNameorRadiantSurfaceGroupName)) {
        if (auto typed = target->optionalCast<ZoneHVACLowTemperatureRadiantSurfaceGroup>()) {
          return *typed;
        }
      }

      return boost::none;
    }

    ZoneHVACLowTemperatureRadiantSurfaceGroup ZoneHVACLowTempRadiantConstFlow_Impl::ensureSurfaceGroup() {
      if (auto existing = surfaceGroup()) {
        return *existing;
      }

      // This is a real persisted EnergyPlus companion object, not a transient
      // canonical wrapper. The typed wrapper is intentionally thin for now; the
      // richer surface-group semantics still live mostly on the parent until the
      // envelope side of epmodel is developed further.
      if (const auto existingName =
            getString(openstudio::ZoneHVAC_LowTemperatureRadiant_ConstantFlowFields::SurfaceNameorRadiantSurfaceGroupName, true);
          existingName && !existingName->empty()) {
        if (auto obj = workspace().getObjectByTypeAndName(IddObjectType::ZoneHVAC_LowTemperatureRadiant_SurfaceGroup, *existingName, true)) {
          if (auto typed = obj->optionalCast<ZoneHVACLowTemperatureRadiantSurfaceGroup>()) {
            OS_ASSERT(setPointer(openstudio::ZoneHVAC_LowTemperatureRadiant_ConstantFlowFields::SurfaceNameorRadiantSurfaceGroupName, typed->handle(),
                                 false));
            return *typed;
          }
        }
      }

      ZoneHVACLowTemperatureRadiantSurfaceGroup created(model());
      if (const auto existingName =
            getString(openstudio::ZoneHVAC_LowTemperatureRadiant_ConstantFlowFields::SurfaceNameorRadiantSurfaceGroupName, true);
          existingName && !existingName->empty()) {
        created.setName(*existingName);
      } else {
        created.setName(getObject<ModelObject>().nameString() + " Surface Group");
      }
      OS_ASSERT(
        setPointer(openstudio::ZoneHVAC_LowTemperatureRadiant_ConstantFlowFields::SurfaceNameorRadiantSurfaceGroupName, created.handle(), false));
      return created;
    }

    std::string ZoneHVACLowTempRadiantConstFlow_Impl::fluidtoRadiantSurfaceHeatTransferModel() const {
      if (const auto design = designObject()) {
        return design->getImpl<detail::ZoneHVACLowTempRadiantConstFlowDesign_Impl>()->fluidtoRadiantSurfaceHeatTransferModel();
      }
      return kDefaultFluidtoRadiantSurfaceHeatTransferModel;
    }

    bool ZoneHVACLowTempRadiantConstFlow_Impl::isFluidtoRadiantSurfaceHeatTransferModelDefaulted() const {
      if (const auto design = designObject()) {
        return design->getImpl<detail::ZoneHVACLowTempRadiantConstFlowDesign_Impl>()->isFluidtoRadiantSurfaceHeatTransferModelDefaulted();
      }
      return true;
    }

    bool ZoneHVACLowTempRadiantConstFlow_Impl::setFluidtoRadiantSurfaceHeatTransferModel(const std::string& fluidtoRadiantSurfaceHeatTransferModel) {
      auto design = ensureDesignObject();
      return design.getImpl<detail::ZoneHVACLowTempRadiantConstFlowDesign_Impl>()->setFluidtoRadiantSurfaceHeatTransferModel(
        fluidtoRadiantSurfaceHeatTransferModel);
    }

    void ZoneHVACLowTempRadiantConstFlow_Impl::resetFluidtoRadiantSurfaceHeatTransferModel() {
      auto design = ensureDesignObject();
      design.getImpl<detail::ZoneHVACLowTempRadiantConstFlowDesign_Impl>()->resetFluidtoRadiantSurfaceHeatTransferModel();
    }

    double ZoneHVACLowTempRadiantConstFlow_Impl::hydronicTubingInsideDiameter() const {
      if (const auto design = designObject()) {
        return design->getImpl<detail::ZoneHVACLowTempRadiantConstFlowDesign_Impl>()->hydronicTubingInsideDiameter();
      }
      return kDefaultHydronicTubingInsideDiameter;
    }

    bool ZoneHVACLowTempRadiantConstFlow_Impl::isHydronicTubingInsideDiameterDefaulted() const {
      if (const auto design = designObject()) {
        return design->getImpl<detail::ZoneHVACLowTempRadiantConstFlowDesign_Impl>()->isHydronicTubingInsideDiameterDefaulted();
      }
      return true;
    }

    bool ZoneHVACLowTempRadiantConstFlow_Impl::setHydronicTubingInsideDiameter(double hydronicTubingInsideDiameter) {
      auto design = ensureDesignObject();
      return design.getImpl<detail::ZoneHVACLowTempRadiantConstFlowDesign_Impl>()->setHydronicTubingInsideDiameter(hydronicTubingInsideDiameter);
    }

    void ZoneHVACLowTempRadiantConstFlow_Impl::resetHydronicTubingInsideDiameter() {
      auto design = ensureDesignObject();
      design.getImpl<detail::ZoneHVACLowTempRadiantConstFlowDesign_Impl>()->resetHydronicTubingInsideDiameter();
    }

    double ZoneHVACLowTempRadiantConstFlow_Impl::hydronicTubingOutsideDiameter() const {
      if (const auto design = designObject()) {
        return design->getImpl<detail::ZoneHVACLowTempRadiantConstFlowDesign_Impl>()->hydronicTubingOutsideDiameter();
      }
      return kDefaultHydronicTubingOutsideDiameter;
    }

    bool ZoneHVACLowTempRadiantConstFlow_Impl::isHydronicTubingOutsideDiameterDefaulted() const {
      if (const auto design = designObject()) {
        return design->getImpl<detail::ZoneHVACLowTempRadiantConstFlowDesign_Impl>()->isHydronicTubingOutsideDiameterDefaulted();
      }
      return true;
    }

    bool ZoneHVACLowTempRadiantConstFlow_Impl::setHydronicTubingOutsideDiameter(double hydronicTubingOutsideDiameter) {
      auto design = ensureDesignObject();
      return design.getImpl<detail::ZoneHVACLowTempRadiantConstFlowDesign_Impl>()->setHydronicTubingOutsideDiameter(hydronicTubingOutsideDiameter);
    }

    void ZoneHVACLowTempRadiantConstFlow_Impl::resetHydronicTubingOutsideDiameter() {
      auto design = ensureDesignObject();
      design.getImpl<detail::ZoneHVACLowTempRadiantConstFlowDesign_Impl>()->resetHydronicTubingOutsideDiameter();
    }

    double ZoneHVACLowTempRadiantConstFlow_Impl::hydronicTubingConductivity() const {
      if (const auto design = designObject()) {
        return design->getImpl<detail::ZoneHVACLowTempRadiantConstFlowDesign_Impl>()->hydronicTubingConductivity();
      }
      return kDefaultHydronicTubingConductivity;
    }

    bool ZoneHVACLowTempRadiantConstFlow_Impl::isHydronicTubingConductivityDefaulted() const {
      if (const auto design = designObject()) {
        return design->getImpl<detail::ZoneHVACLowTempRadiantConstFlowDesign_Impl>()->isHydronicTubingConductivityDefaulted();
      }
      return true;
    }

    bool ZoneHVACLowTempRadiantConstFlow_Impl::setHydronicTubingConductivity(double hydronicTubingConductivity) {
      auto design = ensureDesignObject();
      return design.getImpl<detail::ZoneHVACLowTempRadiantConstFlowDesign_Impl>()->setHydronicTubingConductivity(hydronicTubingConductivity);
    }

    void ZoneHVACLowTempRadiantConstFlow_Impl::resetHydronicTubingConductivity() {
      auto design = ensureDesignObject();
      design.getImpl<detail::ZoneHVACLowTempRadiantConstFlowDesign_Impl>()->resetHydronicTubingConductivity();
    }

    std::string ZoneHVACLowTempRadiantConstFlow_Impl::temperatureControlType() const {
      if (const auto design = designObject()) {
        return design->getImpl<detail::ZoneHVACLowTempRadiantConstFlowDesign_Impl>()->temperatureControlType();
      }
      return kDefaultTemperatureControlType;
    }

    bool ZoneHVACLowTempRadiantConstFlow_Impl::isTemperatureControlTypeDefaulted() const {
      if (const auto design = designObject()) {
        return design->getImpl<detail::ZoneHVACLowTempRadiantConstFlowDesign_Impl>()->isTemperatureControlTypeDefaulted();
      }
      return true;
    }

    bool ZoneHVACLowTempRadiantConstFlow_Impl::setTemperatureControlType(const std::string& temperatureControlType) {
      auto design = ensureDesignObject();
      return design.getImpl<detail::ZoneHVACLowTempRadiantConstFlowDesign_Impl>()->setTemperatureControlType(temperatureControlType);
    }

    void ZoneHVACLowTempRadiantConstFlow_Impl::resetTemperatureControlType() {
      auto design = ensureDesignObject();
      design.getImpl<detail::ZoneHVACLowTempRadiantConstFlowDesign_Impl>()->resetTemperatureControlType();
    }

    double ZoneHVACLowTempRadiantConstFlow_Impl::runningMeanOutdoorDryBulbTemperatureWeightingFactor() const {
      if (const auto design = designObject()) {
        return design->getImpl<detail::ZoneHVACLowTempRadiantConstFlowDesign_Impl>()->runningMeanOutdoorDryBulbTemperatureWeightingFactor();
      }
      return kDefaultRunningMeanOutdoorDryBulbTemperatureWeightingFactor;
    }

    bool ZoneHVACLowTempRadiantConstFlow_Impl::isRunningMeanOutdoorDryBulbTemperatureWeightingFactorDefaulted() const {
      if (const auto design = designObject()) {
        return design->getImpl<detail::ZoneHVACLowTempRadiantConstFlowDesign_Impl>()
          ->isRunningMeanOutdoorDryBulbTemperatureWeightingFactorDefaulted();
      }
      return true;
    }

    bool ZoneHVACLowTempRadiantConstFlow_Impl::setRunningMeanOutdoorDryBulbTemperatureWeightingFactor(
      double runningMeanOutdoorDryBulbTemperatureWeightingFactor) {
      auto design = ensureDesignObject();
      return design.getImpl<detail::ZoneHVACLowTempRadiantConstFlowDesign_Impl>()->setRunningMeanOutdoorDryBulbTemperatureWeightingFactor(
        runningMeanOutdoorDryBulbTemperatureWeightingFactor);
    }

    void ZoneHVACLowTempRadiantConstFlow_Impl::resetRunningMeanOutdoorDryBulbTemperatureWeightingFactor() {
      auto design = ensureDesignObject();
      design.getImpl<detail::ZoneHVACLowTempRadiantConstFlowDesign_Impl>()->resetRunningMeanOutdoorDryBulbTemperatureWeightingFactor();
    }

    double ZoneHVACLowTempRadiantConstFlow_Impl::motorEfficiency() const {
      if (const auto design = designObject()) {
        return design->getImpl<detail::ZoneHVACLowTempRadiantConstFlowDesign_Impl>()->motorEfficiency();
      }
      return kDefaultMotorEfficiency;
    }

    bool ZoneHVACLowTempRadiantConstFlow_Impl::isMotorEfficiencyDefaulted() const {
      if (const auto design = designObject()) {
        return design->getImpl<detail::ZoneHVACLowTempRadiantConstFlowDesign_Impl>()->isMotorEfficiencyDefaulted();
      }
      return true;
    }

    bool ZoneHVACLowTempRadiantConstFlow_Impl::setMotorEfficiency(double motorEfficiency) {
      auto design = ensureDesignObject();
      return design.getImpl<detail::ZoneHVACLowTempRadiantConstFlowDesign_Impl>()->setMotorEfficiency(motorEfficiency);
    }

    void ZoneHVACLowTempRadiantConstFlow_Impl::resetMotorEfficiency() {
      auto design = ensureDesignObject();
      design.getImpl<detail::ZoneHVACLowTempRadiantConstFlowDesign_Impl>()->resetMotorEfficiency();
    }

    double ZoneHVACLowTempRadiantConstFlow_Impl::fractionofMotorInefficienciestoFluidStream() const {
      if (const auto design = designObject()) {
        return design->getImpl<detail::ZoneHVACLowTempRadiantConstFlowDesign_Impl>()->fractionofMotorInefficienciestoFluidStream();
      }
      return kDefaultFractionofMotorInefficienciestoFluidStream;
    }

    bool ZoneHVACLowTempRadiantConstFlow_Impl::isFractionofMotorInefficienciestoFluidStreamDefaulted() const {
      if (const auto design = designObject()) {
        return design->getImpl<detail::ZoneHVACLowTempRadiantConstFlowDesign_Impl>()->isFractionofMotorInefficienciestoFluidStreamDefaulted();
      }
      return true;
    }

    bool ZoneHVACLowTempRadiantConstFlow_Impl::setFractionofMotorInefficienciestoFluidStream(double fractionofMotorInefficienciestoFluidStream) {
      auto design = ensureDesignObject();
      return design.getImpl<detail::ZoneHVACLowTempRadiantConstFlowDesign_Impl>()->setFractionofMotorInefficienciestoFluidStream(
        fractionofMotorInefficienciestoFluidStream);
    }

    void ZoneHVACLowTempRadiantConstFlow_Impl::resetFractionofMotorInefficienciestoFluidStream() {
      auto design = ensureDesignObject();
      design.getImpl<detail::ZoneHVACLowTempRadiantConstFlowDesign_Impl>()->resetFractionofMotorInefficienciestoFluidStream();
    }

    boost::optional<double> ZoneHVACLowTempRadiantConstFlow_Impl::hydronicTubingLength() const {
      return getDouble(openstudio::ZoneHVAC_LowTemperatureRadiant_ConstantFlowFields::HydronicTubingLength, true);
    }

    boost::optional<double> ZoneHVACLowTempRadiantConstFlow_Impl::autosizedHydronicTubingLength() const {
      return {};
    }

    bool ZoneHVACLowTempRadiantConstFlow_Impl::isHydronicTubingLengthAutosized() const {
      if (auto value = getString(openstudio::ZoneHVAC_LowTemperatureRadiant_ConstantFlowFields::HydronicTubingLength, true)) {
        return openstudio::istringEqual(*value, "Autosize");
      }
      return false;
    }

    bool ZoneHVACLowTempRadiantConstFlow_Impl::setHydronicTubingLength(double hydronicTubingLength) {
      return setDouble(openstudio::ZoneHVAC_LowTemperatureRadiant_ConstantFlowFields::HydronicTubingLength, hydronicTubingLength, false);
    }

    void ZoneHVACLowTempRadiantConstFlow_Impl::autosizeHydronicTubingLength() {
      OS_ASSERT(setString(openstudio::ZoneHVAC_LowTemperatureRadiant_ConstantFlowFields::HydronicTubingLength, "Autosize", false));
    }

    boost::optional<double> ZoneHVACLowTempRadiantConstFlow_Impl::ratedFlowRate() const {
      return getDouble(openstudio::ZoneHVAC_LowTemperatureRadiant_ConstantFlowFields::RatedFlowRate, true);
    }

    boost::optional<double> ZoneHVACLowTempRadiantConstFlow_Impl::autosizedRatedFlowRate() const {
      return {};
    }

    bool ZoneHVACLowTempRadiantConstFlow_Impl::isRatedFlowRateAutosized() const {
      if (auto value = getString(openstudio::ZoneHVAC_LowTemperatureRadiant_ConstantFlowFields::RatedFlowRate, true)) {
        return openstudio::istringEqual(*value, "Autosize");
      }
      return false;
    }

    bool ZoneHVACLowTempRadiantConstFlow_Impl::setRatedFlowRate(double ratedFlowRate) {
      return setDouble(openstudio::ZoneHVAC_LowTemperatureRadiant_ConstantFlowFields::RatedFlowRate, ratedFlowRate, false);
    }

    void ZoneHVACLowTempRadiantConstFlow_Impl::autosizeRatedFlowRate() {
      OS_ASSERT(setString(openstudio::ZoneHVAC_LowTemperatureRadiant_ConstantFlowFields::RatedFlowRate, "Autosize", false));
    }

    double ZoneHVACLowTempRadiantConstFlow_Impl::ratedPumpHead() const {
      auto value = getDouble(openstudio::ZoneHVAC_LowTemperatureRadiant_ConstantFlowFields::RatedPumpHead, true);
      OS_ASSERT(value);
      return *value;
    }

    bool ZoneHVACLowTempRadiantConstFlow_Impl::isRatedPumpHeadDefaulted() const {
      return isEmpty(openstudio::ZoneHVAC_LowTemperatureRadiant_ConstantFlowFields::RatedPumpHead);
    }

    bool ZoneHVACLowTempRadiantConstFlow_Impl::setRatedPumpHead(double ratedPumpHead) {
      return setDouble(openstudio::ZoneHVAC_LowTemperatureRadiant_ConstantFlowFields::RatedPumpHead, ratedPumpHead, false);
    }

    void ZoneHVACLowTempRadiantConstFlow_Impl::resetRatedPumpHead() {
      OS_ASSERT(setString(openstudio::ZoneHVAC_LowTemperatureRadiant_ConstantFlowFields::RatedPumpHead, "", false));
    }

    boost::optional<double> ZoneHVACLowTempRadiantConstFlow_Impl::ratedPowerConsumption() const {
      return getDouble(openstudio::ZoneHVAC_LowTemperatureRadiant_ConstantFlowFields::RatedPowerConsumption, true);
    }

    bool ZoneHVACLowTempRadiantConstFlow_Impl::setRatedPowerConsumption(double ratedPowerConsumption) {
      return setDouble(openstudio::ZoneHVAC_LowTemperatureRadiant_ConstantFlowFields::RatedPowerConsumption, ratedPowerConsumption, false);
    }

    void ZoneHVACLowTempRadiantConstFlow_Impl::resetRatedPowerConsumption() {
      OS_ASSERT(setString(openstudio::ZoneHVAC_LowTemperatureRadiant_ConstantFlowFields::RatedPowerConsumption, "", false));
    }

    std::string ZoneHVACLowTempRadiantConstFlow_Impl::numberofCircuits() const {
      auto value = getString(openstudio::ZoneHVAC_LowTemperatureRadiant_ConstantFlowFields::NumberofCircuits, true);
      OS_ASSERT(value);
      return *value;
    }

    bool ZoneHVACLowTempRadiantConstFlow_Impl::isNumberofCircuitsDefaulted() const {
      return isEmpty(openstudio::ZoneHVAC_LowTemperatureRadiant_ConstantFlowFields::NumberofCircuits);
    }

    bool ZoneHVACLowTempRadiantConstFlow_Impl::setNumberofCircuits(const std::string& numberofCircuits) {
      return setString(openstudio::ZoneHVAC_LowTemperatureRadiant_ConstantFlowFields::NumberofCircuits, numberofCircuits, false);
    }

    void ZoneHVACLowTempRadiantConstFlow_Impl::resetNumberofCircuits() {
      OS_ASSERT(setString(openstudio::ZoneHVAC_LowTemperatureRadiant_ConstantFlowFields::NumberofCircuits, "", false));
    }

    double ZoneHVACLowTempRadiantConstFlow_Impl::circuitLength() const {
      auto value = getDouble(openstudio::ZoneHVAC_LowTemperatureRadiant_ConstantFlowFields::CircuitLength, true);
      OS_ASSERT(value);
      return *value;
    }

    bool ZoneHVACLowTempRadiantConstFlow_Impl::isCircuitLengthDefaulted() const {
      return isEmpty(openstudio::ZoneHVAC_LowTemperatureRadiant_ConstantFlowFields::CircuitLength);
    }

    bool ZoneHVACLowTempRadiantConstFlow_Impl::setCircuitLength(double circuitLength) {
      return setDouble(openstudio::ZoneHVAC_LowTemperatureRadiant_ConstantFlowFields::CircuitLength, circuitLength, false);
    }

    void ZoneHVACLowTempRadiantConstFlow_Impl::resetCircuitLength() {
      OS_ASSERT(setString(openstudio::ZoneHVAC_LowTemperatureRadiant_ConstantFlowFields::CircuitLength, "", false));
    }

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
