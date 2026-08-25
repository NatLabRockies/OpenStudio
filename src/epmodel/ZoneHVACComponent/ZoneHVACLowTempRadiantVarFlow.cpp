/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "ZoneHVACComponent/ZoneHVACLowTempRadiantVarFlow.hpp"
#include "ZoneHVACComponent/ZoneHVACLowTempRadiantVarFlow_Impl.hpp"
#include "ModelObject/ZoneHVACLowTempRadiantVarFlowDesign.hpp"
#include "ModelObject/ZoneHVACLowTempRadiantVarFlowDesign_Impl.hpp"
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
#include "StraightComponent/CoilCoolingLowTempRadiantVarFlow.hpp"
#include "StraightComponent/CoilCoolingLowTempRadiantVarFlow_Impl.hpp"
#include "StraightComponent/CoilHeatingLowTempRadiantVarFlow.hpp"
#include "StraightComponent/CoilHeatingLowTempRadiantVarFlow_Impl.hpp"
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
#include <utilities/idd/ZoneHVAC_LowTemperatureRadiant_VariableFlow_FieldEnums.hxx>
#include <utilities/idd/ZoneHVAC_LowTemperatureRadiant_VariableFlow_Design_FieldEnums.hxx>
#include <utilities/idd/ZoneHVAC_LowTemperatureRadiant_SurfaceGroup_FieldEnums.hxx>
#include <utilities/idf/IdfExtensibleGroup.hpp>

#include <algorithm>

namespace openstudio {
namespace epmodel {
  namespace detail {

    constexpr const char* kDefaultFluidtoRadiantSurfaceHeatTransferModel = "ConvectionOnly";
    constexpr double kDefaultHydronicTubingInsideDiameter = 0.013;
    constexpr double kDefaultHydronicTubingOutsideDiameter = 0.016;
    constexpr double kDefaultHydronicTubingConductivity = 0.35;
    constexpr const char* kDefaultTemperatureControlType = "MeanAirTemperature";
    constexpr const char* kDefaultSetpointControlType = "HalfFlowPower";
    constexpr const char* kDefaultHeatingDesignCapacityMethod = "HeatingDesignCapacity";
    constexpr double kDefaultFractionofAutosizedHeatingDesignCapacity = 1.0;
    constexpr double kDefaultHeatingControlThrottlingRange = 0.5;
    constexpr const char* kDefaultCoolingDesignCapacityMethod = "CoolingDesignCapacity";
    constexpr double kDefaultCoolingControlThrottlingRange = 0.5;
    constexpr const char* kDefaultCondensationControlType = "SimpleOff";
    constexpr double kDefaultCondensationControlDewpointOffset = 1.0;

    std::string transientHeatingCoilName(const openstudio::epmodel::ZoneHVACLowTempRadiantVarFlow& parent) {
      return "__transient__" + openstudio::toString(parent.handle()) + "__heating_low_temp_radiant_var_flow";
    }

    std::string transientCoolingCoilName(const openstudio::epmodel::ZoneHVACLowTempRadiantVarFlow& parent) {
      return "__transient__" + openstudio::toString(parent.handle()) + "__cooling_low_temp_radiant_var_flow";
    }

    using SurfaceGroupFields = openstudio::ZoneHVAC_LowTemperatureRadiant_SurfaceGroupExtensibleFields;
    using SurfaceFields = openstudio::BuildingSurface_DetailedFields;
    using SurfaceVertexFields = openstudio::BuildingSurface_DetailedExtensibleFields;

    static bool surfaceMatchesRadiantSelection(const openstudio::epmodel::Surface& surface, const std::string& radiantSurfaceType) {
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

    static bool surfaceHasInternalSourceConstruction(const openstudio::epmodel::Surface& surface) {
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

    static std::vector<openstudio::epmodel::Surface> eligibleRadiantSurfaces(const openstudio::epmodel::Model& model,
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

    static bool sameVarFlowSurfaceSet(const std::vector<openstudio::epmodel::Surface>& lhs, const std::vector<openstudio::epmodel::Surface>& rhs) {
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

    static bool hasHeatingCoilData(const openstudio::epmodel::detail::ZoneHVACLowTempRadiantVarFlow_Impl& impl) {
      using Fields = openstudio::ZoneHVAC_LowTemperatureRadiant_VariableFlowFields;
      if (!impl.isEmpty(Fields::HeatingDesignCapacity) || !impl.isEmpty(Fields::MaximumHotWaterFlow)
          || !impl.isEmpty(Fields::HeatingWaterInletNodeName) || !impl.isEmpty(Fields::HeatingWaterOutletNodeName)) {
        return true;
      }

      if (auto target = impl.getTarget(openstudio::ZoneHVAC_LowTemperatureRadiant_VariableFlowFields::DesignObject)) {
        if (auto design = target->optionalCast<ZoneHVACLowTempRadiantVarFlowDesign>()) {
          auto designImpl = design->getImpl<detail::ZoneHVACLowTempRadiantVarFlowDesign_Impl>();
          using DesignFields = openstudio::ZoneHVAC_LowTemperatureRadiant_VariableFlow_DesignFields;
          return !designImpl->isEmpty(DesignFields::HeatingControlTemperatureScheduleName)
                 || !designImpl->isEmpty(DesignFields::HeatingDesignCapacityMethod)
                 || !designImpl->isEmpty(DesignFields::HeatingDesignCapacityPerFloorArea)
                 || !designImpl->isEmpty(DesignFields::FractionofAutosizedHeatingDesignCapacity)
                 || !designImpl->isEmpty(DesignFields::HeatingControlThrottlingRange);
        }
      }

      return false;
    }

    static bool hasCoolingCoilData(const openstudio::epmodel::detail::ZoneHVACLowTempRadiantVarFlow_Impl& impl) {
      using Fields = openstudio::ZoneHVAC_LowTemperatureRadiant_VariableFlowFields;
      if (!impl.isEmpty(Fields::CoolingDesignCapacity) || !impl.isEmpty(Fields::MaximumColdWaterFlow)
          || !impl.isEmpty(Fields::CoolingWaterInletNodeName) || !impl.isEmpty(Fields::CoolingWaterOutletNodeName)) {
        return true;
      }

      if (auto target = impl.getTarget(openstudio::ZoneHVAC_LowTemperatureRadiant_VariableFlowFields::DesignObject)) {
        if (auto design = target->optionalCast<ZoneHVACLowTempRadiantVarFlowDesign>()) {
          auto designImpl = design->getImpl<detail::ZoneHVACLowTempRadiantVarFlowDesign_Impl>();
          using DesignFields = openstudio::ZoneHVAC_LowTemperatureRadiant_VariableFlow_DesignFields;
          return !designImpl->isEmpty(DesignFields::CoolingControlTemperatureScheduleName)
                 || !designImpl->isEmpty(DesignFields::CoolingDesignCapacityMethod)
                 || !designImpl->isEmpty(DesignFields::CoolingDesignCapacityPerFloorArea)
                 || !designImpl->isEmpty(DesignFields::FractionofAutosizedCoolingDesignCapacity)
                 || !designImpl->isEmpty(DesignFields::CoolingControlThrottlingRange) || !designImpl->isEmpty(DesignFields::CondensationControlType)
                 || !designImpl->isEmpty(DesignFields::CondensationControlDewpointOffset);
        }
      }

      return false;
    }

  }  // namespace detail

  ZoneHVACLowTempRadiantVarFlow::ZoneHVACLowTempRadiantVarFlow(const Model& model)
    : ZoneHVACComponent(ZoneHVACLowTempRadiantVarFlow::iddObjectType(), model) {
    auto impl = getImpl<detail::ZoneHVACLowTempRadiantVarFlow_Impl>();
    OS_ASSERT(impl);
    impl->ensureDesignObject();
  }

  ZoneHVACLowTempRadiantVarFlow::ZoneHVACLowTempRadiantVarFlow(const Model& model, Schedule& availabilitySchedule, HVACComponent& heatingCoil,
                                                               HVACComponent& coolingCoil)
    : ZoneHVACLowTempRadiantVarFlow(model) {
    OS_ASSERT(setAvailabilitySchedule(availabilitySchedule));
    OS_ASSERT(setHeatingCoil(heatingCoil));
    OS_ASSERT(setCoolingCoil(coolingCoil));
  }

  ZoneHVACLowTempRadiantVarFlow::ZoneHVACLowTempRadiantVarFlow(std::shared_ptr<detail::ZoneHVACLowTempRadiantVarFlow_Impl> impl)
    : ZoneHVACComponent(std::move(impl)) {}

  IddObjectType ZoneHVACLowTempRadiantVarFlow::iddObjectType() {
    return IddObjectType::ZoneHVAC_LowTemperatureRadiant_VariableFlow;
  }

  std::vector<std::string> ZoneHVACLowTempRadiantVarFlow::radiantSurfaceTypeValues() {
    static const std::vector<std::string> values{"Ceilings", "Floors", "CeilingsandFloors", "AllSurfaces"};
    return values;
  }

  std::vector<std::string> ZoneHVACLowTempRadiantVarFlow::numberofCircuitsValues() {
    return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(),
                          ZoneHVAC_LowTemperatureRadiant_VariableFlowFields::NumberofCircuits);
  }

  std::vector<std::string> ZoneHVACLowTempRadiantVarFlow::fluidtoRadiantSurfaceHeatTransferModelValues() {
    return getIddKeyNames(IddFactory::instance().getObject(IddObjectType::ZoneHVAC_LowTemperatureRadiant_VariableFlow_Design).get(),
                          ZoneHVAC_LowTemperatureRadiant_VariableFlow_DesignFields::FluidtoRadiantSurfaceHeatTransferModel);
  }

  std::vector<std::string> ZoneHVACLowTempRadiantVarFlow::temperatureControlTypeValues() {
    return getIddKeyNames(IddFactory::instance().getObject(IddObjectType::ZoneHVAC_LowTemperatureRadiant_VariableFlow_Design).get(),
                          ZoneHVAC_LowTemperatureRadiant_VariableFlow_DesignFields::TemperatureControlType);
  }

  std::vector<std::string> ZoneHVACLowTempRadiantVarFlow::setpointControlTypeValues() {
    return getIddKeyNames(IddFactory::instance().getObject(IddObjectType::ZoneHVAC_LowTemperatureRadiant_VariableFlow_Design).get(),
                          ZoneHVAC_LowTemperatureRadiant_VariableFlow_DesignFields::SetpointControlType);
  }

  std::vector<std::string> ZoneHVACLowTempRadiantVarFlow::heatingDesignCapacityMethodValues() {
    return getIddKeyNames(IddFactory::instance().getObject(IddObjectType::ZoneHVAC_LowTemperatureRadiant_VariableFlow_Design).get(),
                          ZoneHVAC_LowTemperatureRadiant_VariableFlow_DesignFields::HeatingDesignCapacityMethod);
  }

  std::vector<std::string> ZoneHVACLowTempRadiantVarFlow::coolingDesignCapacityMethodValues() {
    return getIddKeyNames(IddFactory::instance().getObject(IddObjectType::ZoneHVAC_LowTemperatureRadiant_VariableFlow_Design).get(),
                          ZoneHVAC_LowTemperatureRadiant_VariableFlow_DesignFields::CoolingDesignCapacityMethod);
  }

  std::vector<std::string> ZoneHVACLowTempRadiantVarFlow::condensationControlTypeValues() {
    return getIddKeyNames(IddFactory::instance().getObject(IddObjectType::ZoneHVAC_LowTemperatureRadiant_VariableFlow_Design).get(),
                          ZoneHVAC_LowTemperatureRadiant_VariableFlow_DesignFields::CondensationControlType);
  }

  unsigned detail::ZoneHVACLowTempRadiantVarFlow_Impl::inletPort() const {
    return 0u;
  }

  unsigned detail::ZoneHVACLowTempRadiantVarFlow_Impl::outletPort() const {
    return 0u;
  }

  namespace detail {

    boost::optional<Schedule> ZoneHVACLowTempRadiantVarFlow_Impl::availabilitySchedule() const {
      return getObject<ModelObject>().getModelObjectTarget<Schedule>(
        openstudio::ZoneHVAC_LowTemperatureRadiant_VariableFlowFields::AvailabilityScheduleName);
    }

    bool ZoneHVACLowTempRadiantVarFlow_Impl::setAvailabilitySchedule(Schedule& schedule) {
      return setPointer(openstudio::ZoneHVAC_LowTemperatureRadiant_VariableFlowFields::AvailabilityScheduleName, schedule.handle(), false);
    }

    void ZoneHVACLowTempRadiantVarFlow_Impl::resetAvailabilitySchedule() {
      OS_ASSERT(setPointer(openstudio::ZoneHVAC_LowTemperatureRadiant_VariableFlowFields::AvailabilityScheduleName, Handle(), false));
    }

    boost::optional<std::string> ZoneHVACLowTempRadiantVarFlow_Impl::radiantSurfaceType() const {
      const auto surfaces_ = surfaces();
      if (surfaces_.empty()) {
        return boost::none;
      }

      const auto zone = thermalZone();
      if (!zone) {
        return boost::none;
      }

      for (const auto& candidate : openstudio::epmodel::ZoneHVACLowTempRadiantVarFlow::radiantSurfaceTypeValues()) {
        if (sameVarFlowSurfaceSet(surfaces_, eligibleRadiantSurfaces(model(), *zone, candidate))) {
          return candidate;
        }
      }

      return boost::none;
    }

    bool ZoneHVACLowTempRadiantVarFlow_Impl::setRadiantSurfaceType(const std::string& radiantSurfaceType) {
      const auto validValues = openstudio::epmodel::ZoneHVACLowTempRadiantVarFlow::radiantSurfaceTypeValues();
      if (std::find(validValues.begin(), validValues.end(), radiantSurfaceType) == validValues.end()) {
        return false;
      }

      auto zone = thermalZone();
      if (!zone) {
        return false;
      }

      const auto selectedSurfaces = eligibleRadiantSurfaces(model(), *zone, radiantSurfaceType);
      auto groupObject = ensureSurfaceGroup();
      auto groupImpl = groupObject.getImpl<detail::ZoneHVACLowTemperatureRadiantSurfaceGroup_Impl>();
      groupImpl->clearSurfaces();

      double totalArea = 0.0;
      for (const auto& surface : selectedSurfaces) {
        totalArea += surfaceGrossArea(surface);
      }

      if (totalArea <= 0.0) {
        return true;
      }

      bool result = true;
      for (auto surface : selectedSurfaces) {
        const auto area = surfaceGrossArea(surface);
        result = groupImpl->addSurface(surface, area / totalArea) && result;
      }
      return result;
    }

    void ZoneHVACLowTempRadiantVarFlow_Impl::resetRadiantSurfaceType() {
      if (thermalZone()) {
        OS_ASSERT(setRadiantSurfaceType("Ceilings"));
      } else if (auto group = surfaceGroup()) {
        group->getImpl<detail::ZoneHVACLowTemperatureRadiantSurfaceGroup_Impl>()->clearSurfaces();
      }
    }

    std::vector<Surface> ZoneHVACLowTempRadiantVarFlow_Impl::surfaces() const {
      if (auto groupObject = surfaceGroup()) {
        return groupObject->getImpl<detail::ZoneHVACLowTemperatureRadiantSurfaceGroup_Impl>()->surfaces();
      }
      return {};
    }

    boost::optional<HVACComponent> ZoneHVACLowTempRadiantVarFlow_Impl::heatingCoil() const {
      if (!detail::hasHeatingCoilData(*this)) {
        return boost::none;
      }
      const auto parent = getObject<openstudio::epmodel::ZoneHVACLowTempRadiantVarFlow>();
      return model()
        .getOrCreateTransientByName<openstudio::epmodel::CoilHeatingLowTempRadiantVarFlow>(detail::transientHeatingCoilName(parent))
        .cast<HVACComponent>();
    }

    bool ZoneHVACLowTempRadiantVarFlow_Impl::setHeatingCoil(HVACComponent& heatingCoil) {
      auto source = heatingCoil.optionalCast<CoilHeatingLowTempRadiantVarFlow>();
      if (!source) {
        return false;
      }

      auto target = model().getOrCreateTransientByName<openstudio::epmodel::CoilHeatingLowTempRadiantVarFlow>(
        detail::transientHeatingCoilName(getObject<openstudio::epmodel::ZoneHVACLowTempRadiantVarFlow>()));

      bool result = true;

      result = source->isMaximumHotWaterFlowAutosized()
                 ? (target.autosizeMaximumHotWaterFlow(), result)
                 : (source->maximumHotWaterFlow() ? (target.setMaximumHotWaterFlow(*source->maximumHotWaterFlow()) && result)
                                                  : (target.resetMaximumHotWaterFlow(), result));

      if (auto schedule = source->heatingControlTemperatureSchedule()) {
        result = target.setHeatingControlTemperatureSchedule(*schedule) && result;
      } else {
        target.resetHeatingControlTemperatureSchedule();
      }

      result = target.setHeatingDesignCapacityMethod(source->heatingDesignCapacityMethod()) && result;
      result = source->isHeatingDesignCapacityAutosized()
                 ? (target.autosizeHeatingDesignCapacity(), result)
                 : (source->heatingDesignCapacity()
                      ? (target.setHeatingDesignCapacity(*source->heatingDesignCapacity()) && result)
                      : (setString(openstudio::ZoneHVAC_LowTemperatureRadiant_VariableFlowFields::HeatingDesignCapacity, "", false) && result));
      result = target.setHeatingDesignCapacityPerFloorArea(source->heatingDesignCapacityPerFloorArea()) && result;
      result = target.setFractionofAutosizedHeatingDesignCapacity(source->fractionofAutosizedHeatingDesignCapacity()) && result;
      result = target.setHeatingControlThrottlingRange(source->heatingControlThrottlingRange()) && result;

      if (auto inlet = source->inletModelObject()) {
        if (auto node = inlet->optionalCast<Node>()) {
          result =
            setPointer(openstudio::ZoneHVAC_LowTemperatureRadiant_VariableFlowFields::HeatingWaterInletNodeName, node->handle(), false) && result;
        }
      } else {
        result = setPointer(openstudio::ZoneHVAC_LowTemperatureRadiant_VariableFlowFields::HeatingWaterInletNodeName, Handle(), false) && result;
      }

      if (auto outlet = source->outletModelObject()) {
        if (auto node = outlet->optionalCast<Node>()) {
          result =
            setPointer(openstudio::ZoneHVAC_LowTemperatureRadiant_VariableFlowFields::HeatingWaterOutletNodeName, node->handle(), false) && result;
        }
      } else {
        result = setPointer(openstudio::ZoneHVAC_LowTemperatureRadiant_VariableFlowFields::HeatingWaterOutletNodeName, Handle(), false) && result;
      }

      return result;
    }

    void ZoneHVACLowTempRadiantVarFlow_Impl::resetHeatingCoil() {
      OS_ASSERT(setString(openstudio::ZoneHVAC_LowTemperatureRadiant_VariableFlowFields::HeatingDesignCapacity, "", false));
      OS_ASSERT(setString(openstudio::ZoneHVAC_LowTemperatureRadiant_VariableFlowFields::MaximumHotWaterFlow, "", false));
      OS_ASSERT(setPointer(openstudio::ZoneHVAC_LowTemperatureRadiant_VariableFlowFields::HeatingWaterInletNodeName, Handle(), false));
      OS_ASSERT(setPointer(openstudio::ZoneHVAC_LowTemperatureRadiant_VariableFlowFields::HeatingWaterOutletNodeName, Handle(), false));
      auto design = ensureDesignObject();
      auto impl = design.getImpl<detail::ZoneHVACLowTempRadiantVarFlowDesign_Impl>();
      impl->resetHeatingDesignCapacityMethod();
      impl->resetHeatingDesignCapacityPerFloorArea();
      impl->resetFractionofAutosizedHeatingDesignCapacity();
      impl->resetHeatingControlThrottlingRange();
      impl->resetHeatingControlTemperatureSchedule();

      const auto transientName = detail::transientHeatingCoilName(getObject<openstudio::epmodel::ZoneHVACLowTempRadiantVarFlow>());
      if (auto object = workspace().getObjectByTypeAndName(IddObjectType::OS_Coil_Heating_LowTemperatureRadiant_VariableFlow, transientName)) {
        object->remove();
      }
    }

    boost::optional<HVACComponent> ZoneHVACLowTempRadiantVarFlow_Impl::coolingCoil() const {
      if (!detail::hasCoolingCoilData(*this)) {
        return boost::none;
      }
      const auto parent = getObject<openstudio::epmodel::ZoneHVACLowTempRadiantVarFlow>();
      return model()
        .getOrCreateTransientByName<openstudio::epmodel::CoilCoolingLowTempRadiantVarFlow>(detail::transientCoolingCoilName(parent))
        .cast<HVACComponent>();
    }

    bool ZoneHVACLowTempRadiantVarFlow_Impl::setCoolingCoil(HVACComponent& coolingCoil) {
      auto source = coolingCoil.optionalCast<CoilCoolingLowTempRadiantVarFlow>();
      if (!source) {
        return false;
      }

      auto target = model().getOrCreateTransientByName<openstudio::epmodel::CoilCoolingLowTempRadiantVarFlow>(
        detail::transientCoolingCoilName(getObject<openstudio::epmodel::ZoneHVACLowTempRadiantVarFlow>()));

      bool result = true;

      result = source->isMaximumColdWaterFlowAutosized()
                 ? (target.autosizeMaximumColdWaterFlow(), result)
                 : (source->maximumColdWaterFlow() ? (target.setMaximumColdWaterFlow(*source->maximumColdWaterFlow()) && result)
                                                   : (target.resetMaximumColdWaterFlow(), result));

      if (auto schedule = source->coolingControlTemperatureSchedule()) {
        result = target.setCoolingControlTemperatureSchedule(*schedule) && result;
      } else {
        target.resetCoolingControlTemperatureSchedule();
      }

      result = target.setCondensationControlType(source->condensationControlType()) && result;
      result = target.setCondensationControlDewpointOffset(source->condensationControlDewpointOffset()) && result;
      result = target.setCoolingDesignCapacityMethod(source->coolingDesignCapacityMethod()) && result;
      result = source->isCoolingDesignCapacityAutosized()
                 ? (target.autosizeCoolingDesignCapacity(), result)
                 : (source->coolingDesignCapacity()
                      ? (target.setCoolingDesignCapacity(*source->coolingDesignCapacity()) && result)
                      : (setString(openstudio::ZoneHVAC_LowTemperatureRadiant_VariableFlowFields::CoolingDesignCapacity, "", false) && result));
      result = target.setCoolingDesignCapacityPerFloorArea(source->coolingDesignCapacityPerFloorArea()) && result;
      result = target.setFractionofAutosizedCoolingDesignCapacity(source->fractionofAutosizedCoolingDesignCapacity()) && result;
      result = target.setCoolingControlThrottlingRange(source->coolingControlThrottlingRange()) && result;

      if (auto inlet = source->inletModelObject()) {
        if (auto node = inlet->optionalCast<Node>()) {
          result =
            setPointer(openstudio::ZoneHVAC_LowTemperatureRadiant_VariableFlowFields::CoolingWaterInletNodeName, node->handle(), false) && result;
        }
      } else {
        result = setPointer(openstudio::ZoneHVAC_LowTemperatureRadiant_VariableFlowFields::CoolingWaterInletNodeName, Handle(), false) && result;
      }

      if (auto outlet = source->outletModelObject()) {
        if (auto node = outlet->optionalCast<Node>()) {
          result =
            setPointer(openstudio::ZoneHVAC_LowTemperatureRadiant_VariableFlowFields::CoolingWaterOutletNodeName, node->handle(), false) && result;
        }
      } else {
        result = setPointer(openstudio::ZoneHVAC_LowTemperatureRadiant_VariableFlowFields::CoolingWaterOutletNodeName, Handle(), false) && result;
      }

      return result;
    }

    void ZoneHVACLowTempRadiantVarFlow_Impl::resetCoolingCoil() {
      OS_ASSERT(setString(openstudio::ZoneHVAC_LowTemperatureRadiant_VariableFlowFields::CoolingDesignCapacity, "", false));
      OS_ASSERT(setString(openstudio::ZoneHVAC_LowTemperatureRadiant_VariableFlowFields::MaximumColdWaterFlow, "", false));
      OS_ASSERT(setPointer(openstudio::ZoneHVAC_LowTemperatureRadiant_VariableFlowFields::CoolingWaterInletNodeName, Handle(), false));
      OS_ASSERT(setPointer(openstudio::ZoneHVAC_LowTemperatureRadiant_VariableFlowFields::CoolingWaterOutletNodeName, Handle(), false));
      auto design = ensureDesignObject();
      auto impl = design.getImpl<detail::ZoneHVACLowTempRadiantVarFlowDesign_Impl>();
      impl->resetCoolingDesignCapacityMethod();
      impl->resetCoolingDesignCapacityPerFloorArea();
      impl->resetFractionofAutosizedCoolingDesignCapacity();
      impl->resetCoolingControlThrottlingRange();
      impl->resetCoolingControlTemperatureSchedule();
      impl->resetCondensationControlType();
      impl->resetCondensationControlDewpointOffset();

      const auto transientName = detail::transientCoolingCoilName(getObject<openstudio::epmodel::ZoneHVACLowTempRadiantVarFlow>());
      if (auto object = workspace().getObjectByTypeAndName(IddObjectType::OS_Coil_Cooling_LowTemperatureRadiant_VariableFlow, transientName)) {
        object->remove();
      }
    }

    boost::optional<Schedule> ZoneHVACLowTempRadiantVarFlow_Impl::changeoverDelayTimePeriodSchedule() const {
      if (auto design = designObject()) {
        return design->changeoverDelayTimePeriodSchedule();
      }
      return boost::none;
    }

    bool ZoneHVACLowTempRadiantVarFlow_Impl::setChangeoverDelayTimePeriodSchedule(Schedule& schedule) {
      auto design = ensureDesignObject();
      return design.getImpl<detail::ZoneHVACLowTempRadiantVarFlowDesign_Impl>()->setChangeoverDelayTimePeriodSchedule(schedule);
    }

    void ZoneHVACLowTempRadiantVarFlow_Impl::resetChangeoverDelayTimePeriodSchedule() {
      auto design = ensureDesignObject();
      design.getImpl<detail::ZoneHVACLowTempRadiantVarFlowDesign_Impl>()->resetChangeoverDelayTimePeriodSchedule();
    }

    std::vector<ModelObject> ZoneHVACLowTempRadiantVarFlow_Impl::children() const {
      std::vector<ModelObject> result;
      if (const auto hc = heatingCoil()) {
        result.push_back(*hc);
      }
      if (const auto cc = coolingCoil()) {
        result.push_back(*cc);
      }
      return result;
    }

    void ZoneHVACLowTempRadiantVarFlow_Impl::doCanonicalize(LoadContext& context) {
      if (context.repairEnabled()) {
        ensureDesignObject();
      }
    }

  }  // namespace detail

  boost::optional<Schedule> ZoneHVACLowTempRadiantVarFlow::availabilitySchedule() const {
    return getImpl<detail::ZoneHVACLowTempRadiantVarFlow_Impl>()->availabilitySchedule();
  }

  bool ZoneHVACLowTempRadiantVarFlow::setAvailabilitySchedule(Schedule& schedule) {
    return getImpl<detail::ZoneHVACLowTempRadiantVarFlow_Impl>()->setAvailabilitySchedule(schedule);
  }

  void ZoneHVACLowTempRadiantVarFlow::resetAvailabilitySchedule() {
    getImpl<detail::ZoneHVACLowTempRadiantVarFlow_Impl>()->resetAvailabilitySchedule();
  }

  boost::optional<std::string> ZoneHVACLowTempRadiantVarFlow::radiantSurfaceType() const {
    return getImpl<detail::ZoneHVACLowTempRadiantVarFlow_Impl>()->radiantSurfaceType();
  }

  bool ZoneHVACLowTempRadiantVarFlow::setRadiantSurfaceType(const std::string& radiantSurfaceType) {
    return getImpl<detail::ZoneHVACLowTempRadiantVarFlow_Impl>()->setRadiantSurfaceType(radiantSurfaceType);
  }

  void ZoneHVACLowTempRadiantVarFlow::resetRadiantSurfaceType() {
    getImpl<detail::ZoneHVACLowTempRadiantVarFlow_Impl>()->resetRadiantSurfaceType();
  }

  std::vector<Surface> ZoneHVACLowTempRadiantVarFlow::surfaces() const {
    return getImpl<detail::ZoneHVACLowTempRadiantVarFlow_Impl>()->surfaces();
  }

  boost::optional<HVACComponent> ZoneHVACLowTempRadiantVarFlow::heatingCoil() const {
    return getImpl<detail::ZoneHVACLowTempRadiantVarFlow_Impl>()->heatingCoil();
  }

  bool ZoneHVACLowTempRadiantVarFlow::setHeatingCoil(HVACComponent& heatingCoil) {
    return getImpl<detail::ZoneHVACLowTempRadiantVarFlow_Impl>()->setHeatingCoil(heatingCoil);
  }

  void ZoneHVACLowTempRadiantVarFlow::resetHeatingCoil() {
    getImpl<detail::ZoneHVACLowTempRadiantVarFlow_Impl>()->resetHeatingCoil();
  }

  boost::optional<HVACComponent> ZoneHVACLowTempRadiantVarFlow::coolingCoil() const {
    return getImpl<detail::ZoneHVACLowTempRadiantVarFlow_Impl>()->coolingCoil();
  }

  bool ZoneHVACLowTempRadiantVarFlow::setCoolingCoil(HVACComponent& coolingCoil) {
    return getImpl<detail::ZoneHVACLowTempRadiantVarFlow_Impl>()->setCoolingCoil(coolingCoil);
  }

  void ZoneHVACLowTempRadiantVarFlow::resetCoolingCoil() {
    getImpl<detail::ZoneHVACLowTempRadiantVarFlow_Impl>()->resetCoolingCoil();
  }

  boost::optional<Schedule> ZoneHVACLowTempRadiantVarFlow::changeoverDelayTimePeriodSchedule() const {
    return getImpl<detail::ZoneHVACLowTempRadiantVarFlow_Impl>()->changeoverDelayTimePeriodSchedule();
  }

  bool ZoneHVACLowTempRadiantVarFlow::setChangeoverDelayTimePeriodSchedule(Schedule& schedule) {
    return getImpl<detail::ZoneHVACLowTempRadiantVarFlow_Impl>()->setChangeoverDelayTimePeriodSchedule(schedule);
  }

  void ZoneHVACLowTempRadiantVarFlow::resetChangeoverDelayTimePeriodSchedule() {
    getImpl<detail::ZoneHVACLowTempRadiantVarFlow_Impl>()->resetChangeoverDelayTimePeriodSchedule();
  }

  std::vector<ModelObject> ZoneHVACLowTempRadiantVarFlow::children() const {
    return getImpl<detail::ZoneHVACLowTempRadiantVarFlow_Impl>()->children();
  }

  boost::optional<ZoneHVACLowTempRadiantVarFlowDesign> ZoneHVACLowTempRadiantVarFlow::designObject() const {
    return getImpl<detail::ZoneHVACLowTempRadiantVarFlow_Impl>()->designObject();
  }

  boost::optional<ZoneHVACLowTemperatureRadiantSurfaceGroup> ZoneHVACLowTempRadiantVarFlow::surfaceGroup() const {
    return getImpl<detail::ZoneHVACLowTempRadiantVarFlow_Impl>()->surfaceGroup();
  }

  boost::optional<double> ZoneHVACLowTempRadiantVarFlow::hydronicTubingLength() const {
    return getImpl<detail::ZoneHVACLowTempRadiantVarFlow_Impl>()->hydronicTubingLength();
  }

  boost::optional<double> ZoneHVACLowTempRadiantVarFlow::autosizedHydronicTubingLength() const {
    return getImpl<detail::ZoneHVACLowTempRadiantVarFlow_Impl>()->autosizedHydronicTubingLength();
  }

  bool ZoneHVACLowTempRadiantVarFlow::isHydronicTubingLengthAutosized() const {
    return getImpl<detail::ZoneHVACLowTempRadiantVarFlow_Impl>()->isHydronicTubingLengthAutosized();
  }

  bool ZoneHVACLowTempRadiantVarFlow::setHydronicTubingLength(double hydronicTubingLength) {
    return getImpl<detail::ZoneHVACLowTempRadiantVarFlow_Impl>()->setHydronicTubingLength(hydronicTubingLength);
  }

  void ZoneHVACLowTempRadiantVarFlow::autosizeHydronicTubingLength() {
    getImpl<detail::ZoneHVACLowTempRadiantVarFlow_Impl>()->autosizeHydronicTubingLength();
  }

  boost::optional<double> ZoneHVACLowTempRadiantVarFlow::heatingDesignCapacity() const {
    return getImpl<detail::ZoneHVACLowTempRadiantVarFlow_Impl>()->heatingDesignCapacity();
  }

  bool ZoneHVACLowTempRadiantVarFlow::isHeatingDesignCapacityAutosized() const {
    return getImpl<detail::ZoneHVACLowTempRadiantVarFlow_Impl>()->isHeatingDesignCapacityAutosized();
  }

  bool ZoneHVACLowTempRadiantVarFlow::setHeatingDesignCapacity(double heatingDesignCapacity) {
    return getImpl<detail::ZoneHVACLowTempRadiantVarFlow_Impl>()->setHeatingDesignCapacity(heatingDesignCapacity);
  }

  void ZoneHVACLowTempRadiantVarFlow::autosizeHeatingDesignCapacity() {
    getImpl<detail::ZoneHVACLowTempRadiantVarFlow_Impl>()->autosizeHeatingDesignCapacity();
  }

  boost::optional<double> ZoneHVACLowTempRadiantVarFlow::maximumHotWaterFlow() const {
    return getImpl<detail::ZoneHVACLowTempRadiantVarFlow_Impl>()->maximumHotWaterFlow();
  }

  bool ZoneHVACLowTempRadiantVarFlow::isMaximumHotWaterFlowAutosized() const {
    return getImpl<detail::ZoneHVACLowTempRadiantVarFlow_Impl>()->isMaximumHotWaterFlowAutosized();
  }

  bool ZoneHVACLowTempRadiantVarFlow::setMaximumHotWaterFlow(double maximumHotWaterFlow) {
    return getImpl<detail::ZoneHVACLowTempRadiantVarFlow_Impl>()->setMaximumHotWaterFlow(maximumHotWaterFlow);
  }

  void ZoneHVACLowTempRadiantVarFlow::autosizeMaximumHotWaterFlow() {
    getImpl<detail::ZoneHVACLowTempRadiantVarFlow_Impl>()->autosizeMaximumHotWaterFlow();
  }

  boost::optional<double> ZoneHVACLowTempRadiantVarFlow::coolingDesignCapacity() const {
    return getImpl<detail::ZoneHVACLowTempRadiantVarFlow_Impl>()->coolingDesignCapacity();
  }

  bool ZoneHVACLowTempRadiantVarFlow::isCoolingDesignCapacityAutosized() const {
    return getImpl<detail::ZoneHVACLowTempRadiantVarFlow_Impl>()->isCoolingDesignCapacityAutosized();
  }

  bool ZoneHVACLowTempRadiantVarFlow::setCoolingDesignCapacity(double coolingDesignCapacity) {
    return getImpl<detail::ZoneHVACLowTempRadiantVarFlow_Impl>()->setCoolingDesignCapacity(coolingDesignCapacity);
  }

  void ZoneHVACLowTempRadiantVarFlow::autosizeCoolingDesignCapacity() {
    getImpl<detail::ZoneHVACLowTempRadiantVarFlow_Impl>()->autosizeCoolingDesignCapacity();
  }

  boost::optional<double> ZoneHVACLowTempRadiantVarFlow::maximumColdWaterFlow() const {
    return getImpl<detail::ZoneHVACLowTempRadiantVarFlow_Impl>()->maximumColdWaterFlow();
  }

  bool ZoneHVACLowTempRadiantVarFlow::isMaximumColdWaterFlowAutosized() const {
    return getImpl<detail::ZoneHVACLowTempRadiantVarFlow_Impl>()->isMaximumColdWaterFlowAutosized();
  }

  bool ZoneHVACLowTempRadiantVarFlow::setMaximumColdWaterFlow(double maximumColdWaterFlow) {
    return getImpl<detail::ZoneHVACLowTempRadiantVarFlow_Impl>()->setMaximumColdWaterFlow(maximumColdWaterFlow);
  }

  void ZoneHVACLowTempRadiantVarFlow::autosizeMaximumColdWaterFlow() {
    getImpl<detail::ZoneHVACLowTempRadiantVarFlow_Impl>()->autosizeMaximumColdWaterFlow();
  }

  std::string ZoneHVACLowTempRadiantVarFlow::numberofCircuits() const {
    return getImpl<detail::ZoneHVACLowTempRadiantVarFlow_Impl>()->numberofCircuits();
  }

  bool ZoneHVACLowTempRadiantVarFlow::isNumberofCircuitsDefaulted() const {
    return getImpl<detail::ZoneHVACLowTempRadiantVarFlow_Impl>()->isNumberofCircuitsDefaulted();
  }

  bool ZoneHVACLowTempRadiantVarFlow::setNumberofCircuits(const std::string& numberofCircuits) {
    return getImpl<detail::ZoneHVACLowTempRadiantVarFlow_Impl>()->setNumberofCircuits(numberofCircuits);
  }

  void ZoneHVACLowTempRadiantVarFlow::resetNumberofCircuits() {
    getImpl<detail::ZoneHVACLowTempRadiantVarFlow_Impl>()->resetNumberofCircuits();
  }

  double ZoneHVACLowTempRadiantVarFlow::circuitLength() const {
    return getImpl<detail::ZoneHVACLowTempRadiantVarFlow_Impl>()->circuitLength();
  }

  bool ZoneHVACLowTempRadiantVarFlow::isCircuitLengthDefaulted() const {
    return getImpl<detail::ZoneHVACLowTempRadiantVarFlow_Impl>()->isCircuitLengthDefaulted();
  }

  bool ZoneHVACLowTempRadiantVarFlow::setCircuitLength(double circuitLength) {
    return getImpl<detail::ZoneHVACLowTempRadiantVarFlow_Impl>()->setCircuitLength(circuitLength);
  }

  void ZoneHVACLowTempRadiantVarFlow::resetCircuitLength() {
    getImpl<detail::ZoneHVACLowTempRadiantVarFlow_Impl>()->resetCircuitLength();
  }

  std::string ZoneHVACLowTempRadiantVarFlow::fluidtoRadiantSurfaceHeatTransferModel() const {
    return getImpl<detail::ZoneHVACLowTempRadiantVarFlow_Impl>()->fluidtoRadiantSurfaceHeatTransferModel();
  }

  bool ZoneHVACLowTempRadiantVarFlow::isFluidtoRadiantSurfaceHeatTransferModelDefaulted() const {
    return getImpl<detail::ZoneHVACLowTempRadiantVarFlow_Impl>()->isFluidtoRadiantSurfaceHeatTransferModelDefaulted();
  }

  bool ZoneHVACLowTempRadiantVarFlow::setFluidtoRadiantSurfaceHeatTransferModel(const std::string& fluidtoRadiantSurfaceHeatTransferModel) {
    return getImpl<detail::ZoneHVACLowTempRadiantVarFlow_Impl>()->setFluidtoRadiantSurfaceHeatTransferModel(fluidtoRadiantSurfaceHeatTransferModel);
  }

  void ZoneHVACLowTempRadiantVarFlow::resetFluidtoRadiantSurfaceHeatTransferModel() {
    getImpl<detail::ZoneHVACLowTempRadiantVarFlow_Impl>()->resetFluidtoRadiantSurfaceHeatTransferModel();
  }

  double ZoneHVACLowTempRadiantVarFlow::hydronicTubingInsideDiameter() const {
    return getImpl<detail::ZoneHVACLowTempRadiantVarFlow_Impl>()->hydronicTubingInsideDiameter();
  }

  bool ZoneHVACLowTempRadiantVarFlow::isHydronicTubingInsideDiameterDefaulted() const {
    return getImpl<detail::ZoneHVACLowTempRadiantVarFlow_Impl>()->isHydronicTubingInsideDiameterDefaulted();
  }

  bool ZoneHVACLowTempRadiantVarFlow::setHydronicTubingInsideDiameter(double hydronicTubingInsideDiameter) {
    return getImpl<detail::ZoneHVACLowTempRadiantVarFlow_Impl>()->setHydronicTubingInsideDiameter(hydronicTubingInsideDiameter);
  }

  void ZoneHVACLowTempRadiantVarFlow::resetHydronicTubingInsideDiameter() {
    getImpl<detail::ZoneHVACLowTempRadiantVarFlow_Impl>()->resetHydronicTubingInsideDiameter();
  }

  double ZoneHVACLowTempRadiantVarFlow::hydronicTubingOutsideDiameter() const {
    return getImpl<detail::ZoneHVACLowTempRadiantVarFlow_Impl>()->hydronicTubingOutsideDiameter();
  }

  bool ZoneHVACLowTempRadiantVarFlow::isHydronicTubingOutsideDiameterDefaulted() const {
    return getImpl<detail::ZoneHVACLowTempRadiantVarFlow_Impl>()->isHydronicTubingOutsideDiameterDefaulted();
  }

  bool ZoneHVACLowTempRadiantVarFlow::setHydronicTubingOutsideDiameter(double hydronicTubingOutsideDiameter) {
    return getImpl<detail::ZoneHVACLowTempRadiantVarFlow_Impl>()->setHydronicTubingOutsideDiameter(hydronicTubingOutsideDiameter);
  }

  void ZoneHVACLowTempRadiantVarFlow::resetHydronicTubingOutsideDiameter() {
    getImpl<detail::ZoneHVACLowTempRadiantVarFlow_Impl>()->resetHydronicTubingOutsideDiameter();
  }

  double ZoneHVACLowTempRadiantVarFlow::hydronicTubingConductivity() const {
    return getImpl<detail::ZoneHVACLowTempRadiantVarFlow_Impl>()->hydronicTubingConductivity();
  }

  bool ZoneHVACLowTempRadiantVarFlow::isHydronicTubingConductivityDefaulted() const {
    return getImpl<detail::ZoneHVACLowTempRadiantVarFlow_Impl>()->isHydronicTubingConductivityDefaulted();
  }

  bool ZoneHVACLowTempRadiantVarFlow::setHydronicTubingConductivity(double hydronicTubingConductivity) {
    return getImpl<detail::ZoneHVACLowTempRadiantVarFlow_Impl>()->setHydronicTubingConductivity(hydronicTubingConductivity);
  }

  void ZoneHVACLowTempRadiantVarFlow::resetHydronicTubingConductivity() {
    getImpl<detail::ZoneHVACLowTempRadiantVarFlow_Impl>()->resetHydronicTubingConductivity();
  }

  std::string ZoneHVACLowTempRadiantVarFlow::temperatureControlType() const {
    return getImpl<detail::ZoneHVACLowTempRadiantVarFlow_Impl>()->temperatureControlType();
  }

  bool ZoneHVACLowTempRadiantVarFlow::isTemperatureControlTypeDefaulted() const {
    return getImpl<detail::ZoneHVACLowTempRadiantVarFlow_Impl>()->isTemperatureControlTypeDefaulted();
  }

  bool ZoneHVACLowTempRadiantVarFlow::setTemperatureControlType(const std::string& temperatureControlType) {
    return getImpl<detail::ZoneHVACLowTempRadiantVarFlow_Impl>()->setTemperatureControlType(temperatureControlType);
  }

  void ZoneHVACLowTempRadiantVarFlow::resetTemperatureControlType() {
    getImpl<detail::ZoneHVACLowTempRadiantVarFlow_Impl>()->resetTemperatureControlType();
  }

  std::string ZoneHVACLowTempRadiantVarFlow::setpointControlType() const {
    return getImpl<detail::ZoneHVACLowTempRadiantVarFlow_Impl>()->setpointControlType();
  }

  bool ZoneHVACLowTempRadiantVarFlow::isSetpointControlTypeDefaulted() const {
    return getImpl<detail::ZoneHVACLowTempRadiantVarFlow_Impl>()->isSetpointControlTypeDefaulted();
  }

  bool ZoneHVACLowTempRadiantVarFlow::setSetpointControlType(const std::string& setpointControlType) {
    return getImpl<detail::ZoneHVACLowTempRadiantVarFlow_Impl>()->setSetpointControlType(setpointControlType);
  }

  void ZoneHVACLowTempRadiantVarFlow::resetSetpointControlType() {
    getImpl<detail::ZoneHVACLowTempRadiantVarFlow_Impl>()->resetSetpointControlType();
  }

  std::string ZoneHVACLowTempRadiantVarFlow::heatingDesignCapacityMethod() const {
    return getImpl<detail::ZoneHVACLowTempRadiantVarFlow_Impl>()->heatingDesignCapacityMethod();
  }

  bool ZoneHVACLowTempRadiantVarFlow::isHeatingDesignCapacityMethodDefaulted() const {
    return getImpl<detail::ZoneHVACLowTempRadiantVarFlow_Impl>()->isHeatingDesignCapacityMethodDefaulted();
  }

  bool ZoneHVACLowTempRadiantVarFlow::setHeatingDesignCapacityMethod(const std::string& heatingDesignCapacityMethod) {
    return getImpl<detail::ZoneHVACLowTempRadiantVarFlow_Impl>()->setHeatingDesignCapacityMethod(heatingDesignCapacityMethod);
  }

  void ZoneHVACLowTempRadiantVarFlow::resetHeatingDesignCapacityMethod() {
    getImpl<detail::ZoneHVACLowTempRadiantVarFlow_Impl>()->resetHeatingDesignCapacityMethod();
  }

  boost::optional<double> ZoneHVACLowTempRadiantVarFlow::heatingDesignCapacityPerFloorArea() const {
    return getImpl<detail::ZoneHVACLowTempRadiantVarFlow_Impl>()->heatingDesignCapacityPerFloorArea();
  }

  bool ZoneHVACLowTempRadiantVarFlow::setHeatingDesignCapacityPerFloorArea(double heatingDesignCapacityPerFloorArea) {
    return getImpl<detail::ZoneHVACLowTempRadiantVarFlow_Impl>()->setHeatingDesignCapacityPerFloorArea(heatingDesignCapacityPerFloorArea);
  }

  void ZoneHVACLowTempRadiantVarFlow::resetHeatingDesignCapacityPerFloorArea() {
    getImpl<detail::ZoneHVACLowTempRadiantVarFlow_Impl>()->resetHeatingDesignCapacityPerFloorArea();
  }

  double ZoneHVACLowTempRadiantVarFlow::fractionofAutosizedHeatingDesignCapacity() const {
    return getImpl<detail::ZoneHVACLowTempRadiantVarFlow_Impl>()->fractionofAutosizedHeatingDesignCapacity();
  }

  bool ZoneHVACLowTempRadiantVarFlow::isFractionofAutosizedHeatingDesignCapacityDefaulted() const {
    return getImpl<detail::ZoneHVACLowTempRadiantVarFlow_Impl>()->isFractionofAutosizedHeatingDesignCapacityDefaulted();
  }

  bool ZoneHVACLowTempRadiantVarFlow::setFractionofAutosizedHeatingDesignCapacity(double fractionofAutosizedHeatingDesignCapacity) {
    return getImpl<detail::ZoneHVACLowTempRadiantVarFlow_Impl>()->setFractionofAutosizedHeatingDesignCapacity(
      fractionofAutosizedHeatingDesignCapacity);
  }

  void ZoneHVACLowTempRadiantVarFlow::resetFractionofAutosizedHeatingDesignCapacity() {
    getImpl<detail::ZoneHVACLowTempRadiantVarFlow_Impl>()->resetFractionofAutosizedHeatingDesignCapacity();
  }

  double ZoneHVACLowTempRadiantVarFlow::heatingControlThrottlingRange() const {
    return getImpl<detail::ZoneHVACLowTempRadiantVarFlow_Impl>()->heatingControlThrottlingRange();
  }

  bool ZoneHVACLowTempRadiantVarFlow::isHeatingControlThrottlingRangeDefaulted() const {
    return getImpl<detail::ZoneHVACLowTempRadiantVarFlow_Impl>()->isHeatingControlThrottlingRangeDefaulted();
  }

  bool ZoneHVACLowTempRadiantVarFlow::setHeatingControlThrottlingRange(double heatingControlThrottlingRange) {
    return getImpl<detail::ZoneHVACLowTempRadiantVarFlow_Impl>()->setHeatingControlThrottlingRange(heatingControlThrottlingRange);
  }

  void ZoneHVACLowTempRadiantVarFlow::resetHeatingControlThrottlingRange() {
    getImpl<detail::ZoneHVACLowTempRadiantVarFlow_Impl>()->resetHeatingControlThrottlingRange();
  }

  std::string ZoneHVACLowTempRadiantVarFlow::coolingDesignCapacityMethod() const {
    return getImpl<detail::ZoneHVACLowTempRadiantVarFlow_Impl>()->coolingDesignCapacityMethod();
  }

  bool ZoneHVACLowTempRadiantVarFlow::isCoolingDesignCapacityMethodDefaulted() const {
    return getImpl<detail::ZoneHVACLowTempRadiantVarFlow_Impl>()->isCoolingDesignCapacityMethodDefaulted();
  }

  bool ZoneHVACLowTempRadiantVarFlow::setCoolingDesignCapacityMethod(const std::string& coolingDesignCapacityMethod) {
    return getImpl<detail::ZoneHVACLowTempRadiantVarFlow_Impl>()->setCoolingDesignCapacityMethod(coolingDesignCapacityMethod);
  }

  void ZoneHVACLowTempRadiantVarFlow::resetCoolingDesignCapacityMethod() {
    getImpl<detail::ZoneHVACLowTempRadiantVarFlow_Impl>()->resetCoolingDesignCapacityMethod();
  }

  boost::optional<double> ZoneHVACLowTempRadiantVarFlow::coolingDesignCapacityPerFloorArea() const {
    return getImpl<detail::ZoneHVACLowTempRadiantVarFlow_Impl>()->coolingDesignCapacityPerFloorArea();
  }

  bool ZoneHVACLowTempRadiantVarFlow::setCoolingDesignCapacityPerFloorArea(double coolingDesignCapacityPerFloorArea) {
    return getImpl<detail::ZoneHVACLowTempRadiantVarFlow_Impl>()->setCoolingDesignCapacityPerFloorArea(coolingDesignCapacityPerFloorArea);
  }

  void ZoneHVACLowTempRadiantVarFlow::resetCoolingDesignCapacityPerFloorArea() {
    getImpl<detail::ZoneHVACLowTempRadiantVarFlow_Impl>()->resetCoolingDesignCapacityPerFloorArea();
  }

  boost::optional<double> ZoneHVACLowTempRadiantVarFlow::fractionofAutosizedCoolingDesignCapacity() const {
    return getImpl<detail::ZoneHVACLowTempRadiantVarFlow_Impl>()->fractionofAutosizedCoolingDesignCapacity();
  }

  bool ZoneHVACLowTempRadiantVarFlow::setFractionofAutosizedCoolingDesignCapacity(double fractionofAutosizedCoolingDesignCapacity) {
    return getImpl<detail::ZoneHVACLowTempRadiantVarFlow_Impl>()->setFractionofAutosizedCoolingDesignCapacity(
      fractionofAutosizedCoolingDesignCapacity);
  }

  void ZoneHVACLowTempRadiantVarFlow::resetFractionofAutosizedCoolingDesignCapacity() {
    getImpl<detail::ZoneHVACLowTempRadiantVarFlow_Impl>()->resetFractionofAutosizedCoolingDesignCapacity();
  }

  double ZoneHVACLowTempRadiantVarFlow::coolingControlThrottlingRange() const {
    return getImpl<detail::ZoneHVACLowTempRadiantVarFlow_Impl>()->coolingControlThrottlingRange();
  }

  bool ZoneHVACLowTempRadiantVarFlow::isCoolingControlThrottlingRangeDefaulted() const {
    return getImpl<detail::ZoneHVACLowTempRadiantVarFlow_Impl>()->isCoolingControlThrottlingRangeDefaulted();
  }

  bool ZoneHVACLowTempRadiantVarFlow::setCoolingControlThrottlingRange(double coolingControlThrottlingRange) {
    return getImpl<detail::ZoneHVACLowTempRadiantVarFlow_Impl>()->setCoolingControlThrottlingRange(coolingControlThrottlingRange);
  }

  void ZoneHVACLowTempRadiantVarFlow::resetCoolingControlThrottlingRange() {
    getImpl<detail::ZoneHVACLowTempRadiantVarFlow_Impl>()->resetCoolingControlThrottlingRange();
  }

  std::string ZoneHVACLowTempRadiantVarFlow::condensationControlType() const {
    return getImpl<detail::ZoneHVACLowTempRadiantVarFlow_Impl>()->condensationControlType();
  }

  bool ZoneHVACLowTempRadiantVarFlow::isCondensationControlTypeDefaulted() const {
    return getImpl<detail::ZoneHVACLowTempRadiantVarFlow_Impl>()->isCondensationControlTypeDefaulted();
  }

  bool ZoneHVACLowTempRadiantVarFlow::setCondensationControlType(const std::string& condensationControlType) {
    return getImpl<detail::ZoneHVACLowTempRadiantVarFlow_Impl>()->setCondensationControlType(condensationControlType);
  }

  void ZoneHVACLowTempRadiantVarFlow::resetCondensationControlType() {
    getImpl<detail::ZoneHVACLowTempRadiantVarFlow_Impl>()->resetCondensationControlType();
  }

  double ZoneHVACLowTempRadiantVarFlow::condensationControlDewpointOffset() const {
    return getImpl<detail::ZoneHVACLowTempRadiantVarFlow_Impl>()->condensationControlDewpointOffset();
  }

  bool ZoneHVACLowTempRadiantVarFlow::isCondensationControlDewpointOffsetDefaulted() const {
    return getImpl<detail::ZoneHVACLowTempRadiantVarFlow_Impl>()->isCondensationControlDewpointOffsetDefaulted();
  }

  bool ZoneHVACLowTempRadiantVarFlow::setCondensationControlDewpointOffset(double condensationControlDewpointOffset) {
    return getImpl<detail::ZoneHVACLowTempRadiantVarFlow_Impl>()->setCondensationControlDewpointOffset(condensationControlDewpointOffset);
  }

  void ZoneHVACLowTempRadiantVarFlow::resetCondensationControlDewpointOffset() {
    getImpl<detail::ZoneHVACLowTempRadiantVarFlow_Impl>()->resetCondensationControlDewpointOffset();
  }

  namespace detail {

    boost::optional<double> ZoneHVACLowTempRadiantVarFlow_Impl::hydronicTubingLength() const {
      return getDouble(ZoneHVAC_LowTemperatureRadiant_VariableFlowFields::HydronicTubingLength, true);
    }

    bool ZoneHVACLowTempRadiantVarFlow_Impl::isHydronicTubingLengthAutosized() const {
      bool result = false;
      if (auto value = getString(ZoneHVAC_LowTemperatureRadiant_VariableFlowFields::HydronicTubingLength, true)) {
        result = openstudio::istringEqual(value.get(), "Autosize");
      }
      return result;
    }

    bool ZoneHVACLowTempRadiantVarFlow_Impl::setHydronicTubingLength(double hydronicTubingLength) {
      const bool result = setDouble(ZoneHVAC_LowTemperatureRadiant_VariableFlowFields::HydronicTubingLength, hydronicTubingLength);
      OS_ASSERT(result);
      return result;
    }

    void ZoneHVACLowTempRadiantVarFlow_Impl::autosizeHydronicTubingLength() {
      const bool result = setString(ZoneHVAC_LowTemperatureRadiant_VariableFlowFields::HydronicTubingLength, "Autosize", false);
      OS_ASSERT(result);
    }

    boost::optional<double> ZoneHVACLowTempRadiantVarFlow_Impl::heatingDesignCapacity() const {
      return getDouble(ZoneHVAC_LowTemperatureRadiant_VariableFlowFields::HeatingDesignCapacity, true);
    }

    bool ZoneHVACLowTempRadiantVarFlow_Impl::isHeatingDesignCapacityAutosized() const {
      bool result = false;
      if (auto value = getString(ZoneHVAC_LowTemperatureRadiant_VariableFlowFields::HeatingDesignCapacity, true)) {
        result = openstudio::istringEqual(value.get(), "Autosize");
      }
      return result;
    }

    bool ZoneHVACLowTempRadiantVarFlow_Impl::setHeatingDesignCapacity(double heatingDesignCapacity) {
      const bool result = setDouble(ZoneHVAC_LowTemperatureRadiant_VariableFlowFields::HeatingDesignCapacity, heatingDesignCapacity);
      OS_ASSERT(result);
      return result;
    }

    void ZoneHVACLowTempRadiantVarFlow_Impl::autosizeHeatingDesignCapacity() {
      const bool result = setString(ZoneHVAC_LowTemperatureRadiant_VariableFlowFields::HeatingDesignCapacity, "Autosize", false);
      OS_ASSERT(result);
    }

    boost::optional<double> ZoneHVACLowTempRadiantVarFlow_Impl::maximumHotWaterFlow() const {
      return getDouble(ZoneHVAC_LowTemperatureRadiant_VariableFlowFields::MaximumHotWaterFlow, true);
    }

    bool ZoneHVACLowTempRadiantVarFlow_Impl::isMaximumHotWaterFlowAutosized() const {
      bool result = false;
      if (auto value = getString(ZoneHVAC_LowTemperatureRadiant_VariableFlowFields::MaximumHotWaterFlow, true)) {
        result = openstudio::istringEqual(value.get(), "Autosize");
      }
      return result;
    }

    bool ZoneHVACLowTempRadiantVarFlow_Impl::setMaximumHotWaterFlow(double maximumHotWaterFlow) {
      const bool result = setDouble(ZoneHVAC_LowTemperatureRadiant_VariableFlowFields::MaximumHotWaterFlow, maximumHotWaterFlow);
      OS_ASSERT(result);
      return result;
    }

    void ZoneHVACLowTempRadiantVarFlow_Impl::autosizeMaximumHotWaterFlow() {
      const bool result = setString(ZoneHVAC_LowTemperatureRadiant_VariableFlowFields::MaximumHotWaterFlow, "Autosize", false);
      OS_ASSERT(result);
    }

    boost::optional<double> ZoneHVACLowTempRadiantVarFlow_Impl::coolingDesignCapacity() const {
      return getDouble(ZoneHVAC_LowTemperatureRadiant_VariableFlowFields::CoolingDesignCapacity, true);
    }

    bool ZoneHVACLowTempRadiantVarFlow_Impl::isCoolingDesignCapacityAutosized() const {
      bool result = false;
      if (auto value = getString(ZoneHVAC_LowTemperatureRadiant_VariableFlowFields::CoolingDesignCapacity, true)) {
        result = openstudio::istringEqual(value.get(), "Autosize");
      }
      return result;
    }

    bool ZoneHVACLowTempRadiantVarFlow_Impl::setCoolingDesignCapacity(double coolingDesignCapacity) {
      const bool result = setDouble(ZoneHVAC_LowTemperatureRadiant_VariableFlowFields::CoolingDesignCapacity, coolingDesignCapacity);
      OS_ASSERT(result);
      return result;
    }

    void ZoneHVACLowTempRadiantVarFlow_Impl::autosizeCoolingDesignCapacity() {
      const bool result = setString(ZoneHVAC_LowTemperatureRadiant_VariableFlowFields::CoolingDesignCapacity, "Autosize", false);
      OS_ASSERT(result);
    }

    boost::optional<double> ZoneHVACLowTempRadiantVarFlow_Impl::maximumColdWaterFlow() const {
      return getDouble(ZoneHVAC_LowTemperatureRadiant_VariableFlowFields::MaximumColdWaterFlow, true);
    }

    bool ZoneHVACLowTempRadiantVarFlow_Impl::isMaximumColdWaterFlowAutosized() const {
      bool result = false;
      if (auto value = getString(ZoneHVAC_LowTemperatureRadiant_VariableFlowFields::MaximumColdWaterFlow, true)) {
        result = openstudio::istringEqual(value.get(), "Autosize");
      }
      return result;
    }

    bool ZoneHVACLowTempRadiantVarFlow_Impl::setMaximumColdWaterFlow(double maximumColdWaterFlow) {
      const bool result = setDouble(ZoneHVAC_LowTemperatureRadiant_VariableFlowFields::MaximumColdWaterFlow, maximumColdWaterFlow);
      OS_ASSERT(result);
      return result;
    }

    void ZoneHVACLowTempRadiantVarFlow_Impl::autosizeMaximumColdWaterFlow() {
      const bool result = setString(ZoneHVAC_LowTemperatureRadiant_VariableFlowFields::MaximumColdWaterFlow, "Autosize", false);
      OS_ASSERT(result);
    }

    std::string ZoneHVACLowTempRadiantVarFlow_Impl::numberofCircuits() const {
      auto value = getString(ZoneHVAC_LowTemperatureRadiant_VariableFlowFields::NumberofCircuits, true);
      OS_ASSERT(value);
      return value.get();
    }

    bool ZoneHVACLowTempRadiantVarFlow_Impl::isNumberofCircuitsDefaulted() const {
      return isEmpty(ZoneHVAC_LowTemperatureRadiant_VariableFlowFields::NumberofCircuits);
    }

    bool ZoneHVACLowTempRadiantVarFlow_Impl::setNumberofCircuits(const std::string& numberofCircuits) {
      const bool result = setString(ZoneHVAC_LowTemperatureRadiant_VariableFlowFields::NumberofCircuits, numberofCircuits, false);
      OS_ASSERT(result);
      return result;
    }

    void ZoneHVACLowTempRadiantVarFlow_Impl::resetNumberofCircuits() {
      const bool result = setString(ZoneHVAC_LowTemperatureRadiant_VariableFlowFields::NumberofCircuits, "", false);
      OS_ASSERT(result);
    }

    double ZoneHVACLowTempRadiantVarFlow_Impl::circuitLength() const {
      auto value = getDouble(ZoneHVAC_LowTemperatureRadiant_VariableFlowFields::CircuitLength, true);
      OS_ASSERT(value);
      return value.get();
    }

    bool ZoneHVACLowTempRadiantVarFlow_Impl::isCircuitLengthDefaulted() const {
      return isEmpty(ZoneHVAC_LowTemperatureRadiant_VariableFlowFields::CircuitLength);
    }

    bool ZoneHVACLowTempRadiantVarFlow_Impl::setCircuitLength(double circuitLength) {
      const bool result = setDouble(ZoneHVAC_LowTemperatureRadiant_VariableFlowFields::CircuitLength, circuitLength, false);
      OS_ASSERT(result);
      return result;
    }

    void ZoneHVACLowTempRadiantVarFlow_Impl::resetCircuitLength() {
      const bool result = setString(ZoneHVAC_LowTemperatureRadiant_VariableFlowFields::CircuitLength, "", false);
      OS_ASSERT(result);
    }

    boost::optional<ZoneHVACLowTempRadiantVarFlowDesign> ZoneHVACLowTempRadiantVarFlow_Impl::designObject() const {
      if (auto target = getTarget(openstudio::ZoneHVAC_LowTemperatureRadiant_VariableFlowFields::DesignObject)) {
        if (auto typed = target->optionalCast<ZoneHVACLowTempRadiantVarFlowDesign>()) {
          return *typed;
        }
      }

      if (auto name = getString(openstudio::ZoneHVAC_LowTemperatureRadiant_VariableFlowFields::DesignObject, true); name && !name->empty()) {
        if (auto obj = workspace().getObjectByTypeAndName(IddObjectType::ZoneHVAC_LowTemperatureRadiant_VariableFlow_Design, *name)) {
          if (auto typed = obj->optionalCast<ZoneHVACLowTempRadiantVarFlowDesign>()) {
            auto* self = const_cast<ZoneHVACLowTempRadiantVarFlow_Impl*>(this);
            self->setPointer(openstudio::ZoneHVAC_LowTemperatureRadiant_VariableFlowFields::DesignObject, typed->handle(), false);
            return *typed;
          }
        }
      }

      return boost::none;
    }

    ZoneHVACLowTempRadiantVarFlowDesign ZoneHVACLowTempRadiantVarFlow_Impl::ensureDesignObject() {
      if (auto existing = designObject()) {
        return *existing;
      }

      ZoneHVACLowTempRadiantVarFlowDesign created(model());
      if (const auto existingName = getString(openstudio::ZoneHVAC_LowTemperatureRadiant_VariableFlowFields::DesignObject, true);
          existingName && !existingName->empty()) {
        created.setName(*existingName);
      } else {
        created.setName(getObject<ModelObject>().nameString() + " Design");
      }
      OS_ASSERT(setPointer(openstudio::ZoneHVAC_LowTemperatureRadiant_VariableFlowFields::DesignObject, created.handle(), false));
      return created;
    }

    boost::optional<ZoneHVACLowTemperatureRadiantSurfaceGroup> ZoneHVACLowTempRadiantVarFlow_Impl::surfaceGroup() const {
      // Ordinary typed access should reflect the persisted relationship that
      // is already linked, not silently repair it by stored name. Repair and
      // materialization belong in canonicalization or setter-side helper
      // paths.
      if (auto target = getTarget(openstudio::ZoneHVAC_LowTemperatureRadiant_VariableFlowFields::SurfaceNameorRadiantSurfaceGroupName)) {
        if (auto typed = target->optionalCast<ZoneHVACLowTemperatureRadiantSurfaceGroup>()) {
          return *typed;
        }
      }

      return boost::none;
    }

    ZoneHVACLowTemperatureRadiantSurfaceGroup ZoneHVACLowTempRadiantVarFlow_Impl::ensureSurfaceGroup() {
      if (auto existing = surfaceGroup()) {
        return *existing;
      }

      if (const auto existingName =
            getString(openstudio::ZoneHVAC_LowTemperatureRadiant_VariableFlowFields::SurfaceNameorRadiantSurfaceGroupName, true);
          existingName && !existingName->empty()) {
        if (auto obj = workspace().getObjectByTypeAndName(IddObjectType::ZoneHVAC_LowTemperatureRadiant_SurfaceGroup, *existingName)) {
          if (auto typed = obj->optionalCast<ZoneHVACLowTemperatureRadiantSurfaceGroup>()) {
            OS_ASSERT(setPointer(openstudio::ZoneHVAC_LowTemperatureRadiant_VariableFlowFields::SurfaceNameorRadiantSurfaceGroupName, typed->handle(),
                                 false));
            return *typed;
          }
        }
      }

      ZoneHVACLowTemperatureRadiantSurfaceGroup created(model());
      if (const auto existingName =
            getString(openstudio::ZoneHVAC_LowTemperatureRadiant_VariableFlowFields::SurfaceNameorRadiantSurfaceGroupName, true);
          existingName && !existingName->empty()) {
        created.setName(*existingName);
      } else {
        created.setName(getObject<ModelObject>().nameString() + " Surface Group");
      }
      OS_ASSERT(
        setPointer(openstudio::ZoneHVAC_LowTemperatureRadiant_VariableFlowFields::SurfaceNameorRadiantSurfaceGroupName, created.handle(), false));
      return created;
    }

    std::string ZoneHVACLowTempRadiantVarFlow_Impl::fluidtoRadiantSurfaceHeatTransferModel() const {
      if (const auto design = designObject()) {
        return design->getImpl<detail::ZoneHVACLowTempRadiantVarFlowDesign_Impl>()->fluidtoRadiantSurfaceHeatTransferModel();
      }
      return kDefaultFluidtoRadiantSurfaceHeatTransferModel;
    }

    bool ZoneHVACLowTempRadiantVarFlow_Impl::isFluidtoRadiantSurfaceHeatTransferModelDefaulted() const {
      if (const auto design = designObject()) {
        return design->getImpl<detail::ZoneHVACLowTempRadiantVarFlowDesign_Impl>()->isFluidtoRadiantSurfaceHeatTransferModelDefaulted();
      }
      return true;
    }

    bool ZoneHVACLowTempRadiantVarFlow_Impl::setFluidtoRadiantSurfaceHeatTransferModel(const std::string& value) {
      auto design = ensureDesignObject();
      return design.getImpl<detail::ZoneHVACLowTempRadiantVarFlowDesign_Impl>()->setFluidtoRadiantSurfaceHeatTransferModel(value);
    }

    void ZoneHVACLowTempRadiantVarFlow_Impl::resetFluidtoRadiantSurfaceHeatTransferModel() {
      auto design = ensureDesignObject();
      design.getImpl<detail::ZoneHVACLowTempRadiantVarFlowDesign_Impl>()->resetFluidtoRadiantSurfaceHeatTransferModel();
    }

    double ZoneHVACLowTempRadiantVarFlow_Impl::hydronicTubingInsideDiameter() const {
      if (const auto design = designObject()) {
        return design->getImpl<detail::ZoneHVACLowTempRadiantVarFlowDesign_Impl>()->hydronicTubingInsideDiameter();
      }
      return kDefaultHydronicTubingInsideDiameter;
    }

    bool ZoneHVACLowTempRadiantVarFlow_Impl::isHydronicTubingInsideDiameterDefaulted() const {
      if (const auto design = designObject()) {
        return design->getImpl<detail::ZoneHVACLowTempRadiantVarFlowDesign_Impl>()->isHydronicTubingInsideDiameterDefaulted();
      }
      return true;
    }

    bool ZoneHVACLowTempRadiantVarFlow_Impl::setHydronicTubingInsideDiameter(double value) {
      auto design = ensureDesignObject();
      return design.getImpl<detail::ZoneHVACLowTempRadiantVarFlowDesign_Impl>()->setHydronicTubingInsideDiameter(value);
    }

    void ZoneHVACLowTempRadiantVarFlow_Impl::resetHydronicTubingInsideDiameter() {
      auto design = ensureDesignObject();
      design.getImpl<detail::ZoneHVACLowTempRadiantVarFlowDesign_Impl>()->resetHydronicTubingInsideDiameter();
    }

    double ZoneHVACLowTempRadiantVarFlow_Impl::hydronicTubingOutsideDiameter() const {
      if (const auto design = designObject()) {
        return design->getImpl<detail::ZoneHVACLowTempRadiantVarFlowDesign_Impl>()->hydronicTubingOutsideDiameter();
      }
      return kDefaultHydronicTubingOutsideDiameter;
    }

    bool ZoneHVACLowTempRadiantVarFlow_Impl::isHydronicTubingOutsideDiameterDefaulted() const {
      if (const auto design = designObject()) {
        return design->getImpl<detail::ZoneHVACLowTempRadiantVarFlowDesign_Impl>()->isHydronicTubingOutsideDiameterDefaulted();
      }
      return true;
    }

    bool ZoneHVACLowTempRadiantVarFlow_Impl::setHydronicTubingOutsideDiameter(double value) {
      auto design = ensureDesignObject();
      return design.getImpl<detail::ZoneHVACLowTempRadiantVarFlowDesign_Impl>()->setHydronicTubingOutsideDiameter(value);
    }

    void ZoneHVACLowTempRadiantVarFlow_Impl::resetHydronicTubingOutsideDiameter() {
      auto design = ensureDesignObject();
      design.getImpl<detail::ZoneHVACLowTempRadiantVarFlowDesign_Impl>()->resetHydronicTubingOutsideDiameter();
    }

    double ZoneHVACLowTempRadiantVarFlow_Impl::hydronicTubingConductivity() const {
      if (const auto design = designObject()) {
        return design->getImpl<detail::ZoneHVACLowTempRadiantVarFlowDesign_Impl>()->hydronicTubingConductivity();
      }
      return kDefaultHydronicTubingConductivity;
    }

    bool ZoneHVACLowTempRadiantVarFlow_Impl::isHydronicTubingConductivityDefaulted() const {
      if (const auto design = designObject()) {
        return design->getImpl<detail::ZoneHVACLowTempRadiantVarFlowDesign_Impl>()->isHydronicTubingConductivityDefaulted();
      }
      return true;
    }

    bool ZoneHVACLowTempRadiantVarFlow_Impl::setHydronicTubingConductivity(double value) {
      auto design = ensureDesignObject();
      return design.getImpl<detail::ZoneHVACLowTempRadiantVarFlowDesign_Impl>()->setHydronicTubingConductivity(value);
    }

    void ZoneHVACLowTempRadiantVarFlow_Impl::resetHydronicTubingConductivity() {
      auto design = ensureDesignObject();
      design.getImpl<detail::ZoneHVACLowTempRadiantVarFlowDesign_Impl>()->resetHydronicTubingConductivity();
    }

    std::string ZoneHVACLowTempRadiantVarFlow_Impl::temperatureControlType() const {
      if (const auto design = designObject()) {
        return design->getImpl<detail::ZoneHVACLowTempRadiantVarFlowDesign_Impl>()->temperatureControlType();
      }
      return kDefaultTemperatureControlType;
    }

    bool ZoneHVACLowTempRadiantVarFlow_Impl::isTemperatureControlTypeDefaulted() const {
      if (const auto design = designObject()) {
        return design->getImpl<detail::ZoneHVACLowTempRadiantVarFlowDesign_Impl>()->isTemperatureControlTypeDefaulted();
      }
      return true;
    }

    bool ZoneHVACLowTempRadiantVarFlow_Impl::setTemperatureControlType(const std::string& value) {
      auto design = ensureDesignObject();
      return design.getImpl<detail::ZoneHVACLowTempRadiantVarFlowDesign_Impl>()->setTemperatureControlType(value);
    }

    void ZoneHVACLowTempRadiantVarFlow_Impl::resetTemperatureControlType() {
      auto design = ensureDesignObject();
      design.getImpl<detail::ZoneHVACLowTempRadiantVarFlowDesign_Impl>()->resetTemperatureControlType();
    }

    std::string ZoneHVACLowTempRadiantVarFlow_Impl::setpointControlType() const {
      if (const auto design = designObject()) {
        return design->getImpl<detail::ZoneHVACLowTempRadiantVarFlowDesign_Impl>()->setpointControlType();
      }
      return kDefaultSetpointControlType;
    }

    bool ZoneHVACLowTempRadiantVarFlow_Impl::isSetpointControlTypeDefaulted() const {
      if (const auto design = designObject()) {
        return design->getImpl<detail::ZoneHVACLowTempRadiantVarFlowDesign_Impl>()->isSetpointControlTypeDefaulted();
      }
      return true;
    }

    bool ZoneHVACLowTempRadiantVarFlow_Impl::setSetpointControlType(const std::string& value) {
      auto design = ensureDesignObject();
      return design.getImpl<detail::ZoneHVACLowTempRadiantVarFlowDesign_Impl>()->setSetpointControlType(value);
    }

    void ZoneHVACLowTempRadiantVarFlow_Impl::resetSetpointControlType() {
      auto design = ensureDesignObject();
      design.getImpl<detail::ZoneHVACLowTempRadiantVarFlowDesign_Impl>()->resetSetpointControlType();
    }

    std::string ZoneHVACLowTempRadiantVarFlow_Impl::heatingDesignCapacityMethod() const {
      if (const auto design = designObject()) {
        return design->getImpl<detail::ZoneHVACLowTempRadiantVarFlowDesign_Impl>()->heatingDesignCapacityMethod();
      }
      return kDefaultHeatingDesignCapacityMethod;
    }

    bool ZoneHVACLowTempRadiantVarFlow_Impl::isHeatingDesignCapacityMethodDefaulted() const {
      if (const auto design = designObject()) {
        return design->getImpl<detail::ZoneHVACLowTempRadiantVarFlowDesign_Impl>()->isHeatingDesignCapacityMethodDefaulted();
      }
      return true;
    }

    bool ZoneHVACLowTempRadiantVarFlow_Impl::setHeatingDesignCapacityMethod(const std::string& value) {
      auto design = ensureDesignObject();
      return design.getImpl<detail::ZoneHVACLowTempRadiantVarFlowDesign_Impl>()->setHeatingDesignCapacityMethod(value);
    }

    void ZoneHVACLowTempRadiantVarFlow_Impl::resetHeatingDesignCapacityMethod() {
      auto design = ensureDesignObject();
      design.getImpl<detail::ZoneHVACLowTempRadiantVarFlowDesign_Impl>()->resetHeatingDesignCapacityMethod();
    }

    boost::optional<double> ZoneHVACLowTempRadiantVarFlow_Impl::heatingDesignCapacityPerFloorArea() const {
      if (const auto design = designObject()) {
        return design->getImpl<detail::ZoneHVACLowTempRadiantVarFlowDesign_Impl>()->heatingDesignCapacityPerFloorArea();
      }
      return boost::none;
    }

    bool ZoneHVACLowTempRadiantVarFlow_Impl::setHeatingDesignCapacityPerFloorArea(double value) {
      auto design = ensureDesignObject();
      return design.getImpl<detail::ZoneHVACLowTempRadiantVarFlowDesign_Impl>()->setHeatingDesignCapacityPerFloorArea(value);
    }

    void ZoneHVACLowTempRadiantVarFlow_Impl::resetHeatingDesignCapacityPerFloorArea() {
      auto design = ensureDesignObject();
      design.getImpl<detail::ZoneHVACLowTempRadiantVarFlowDesign_Impl>()->resetHeatingDesignCapacityPerFloorArea();
    }

    double ZoneHVACLowTempRadiantVarFlow_Impl::fractionofAutosizedHeatingDesignCapacity() const {
      if (const auto design = designObject()) {
        return design->getImpl<detail::ZoneHVACLowTempRadiantVarFlowDesign_Impl>()->fractionofAutosizedHeatingDesignCapacity();
      }
      return kDefaultFractionofAutosizedHeatingDesignCapacity;
    }

    bool ZoneHVACLowTempRadiantVarFlow_Impl::isFractionofAutosizedHeatingDesignCapacityDefaulted() const {
      if (const auto design = designObject()) {
        return design->getImpl<detail::ZoneHVACLowTempRadiantVarFlowDesign_Impl>()->isFractionofAutosizedHeatingDesignCapacityDefaulted();
      }
      return true;
    }

    bool ZoneHVACLowTempRadiantVarFlow_Impl::setFractionofAutosizedHeatingDesignCapacity(double value) {
      auto design = ensureDesignObject();
      return design.getImpl<detail::ZoneHVACLowTempRadiantVarFlowDesign_Impl>()->setFractionofAutosizedHeatingDesignCapacity(value);
    }

    void ZoneHVACLowTempRadiantVarFlow_Impl::resetFractionofAutosizedHeatingDesignCapacity() {
      auto design = ensureDesignObject();
      design.getImpl<detail::ZoneHVACLowTempRadiantVarFlowDesign_Impl>()->resetFractionofAutosizedHeatingDesignCapacity();
    }

    double ZoneHVACLowTempRadiantVarFlow_Impl::heatingControlThrottlingRange() const {
      if (const auto design = designObject()) {
        return design->getImpl<detail::ZoneHVACLowTempRadiantVarFlowDesign_Impl>()->heatingControlThrottlingRange();
      }
      return kDefaultHeatingControlThrottlingRange;
    }

    bool ZoneHVACLowTempRadiantVarFlow_Impl::isHeatingControlThrottlingRangeDefaulted() const {
      if (const auto design = designObject()) {
        return design->getImpl<detail::ZoneHVACLowTempRadiantVarFlowDesign_Impl>()->isHeatingControlThrottlingRangeDefaulted();
      }
      return true;
    }

    bool ZoneHVACLowTempRadiantVarFlow_Impl::setHeatingControlThrottlingRange(double value) {
      auto design = ensureDesignObject();
      return design.getImpl<detail::ZoneHVACLowTempRadiantVarFlowDesign_Impl>()->setHeatingControlThrottlingRange(value);
    }

    void ZoneHVACLowTempRadiantVarFlow_Impl::resetHeatingControlThrottlingRange() {
      auto design = ensureDesignObject();
      design.getImpl<detail::ZoneHVACLowTempRadiantVarFlowDesign_Impl>()->resetHeatingControlThrottlingRange();
    }

    std::string ZoneHVACLowTempRadiantVarFlow_Impl::coolingDesignCapacityMethod() const {
      if (const auto design = designObject()) {
        return design->getImpl<detail::ZoneHVACLowTempRadiantVarFlowDesign_Impl>()->coolingDesignCapacityMethod();
      }
      return kDefaultCoolingDesignCapacityMethod;
    }

    bool ZoneHVACLowTempRadiantVarFlow_Impl::isCoolingDesignCapacityMethodDefaulted() const {
      if (const auto design = designObject()) {
        return design->getImpl<detail::ZoneHVACLowTempRadiantVarFlowDesign_Impl>()->isCoolingDesignCapacityMethodDefaulted();
      }
      return true;
    }

    bool ZoneHVACLowTempRadiantVarFlow_Impl::setCoolingDesignCapacityMethod(const std::string& value) {
      auto design = ensureDesignObject();
      return design.getImpl<detail::ZoneHVACLowTempRadiantVarFlowDesign_Impl>()->setCoolingDesignCapacityMethod(value);
    }

    void ZoneHVACLowTempRadiantVarFlow_Impl::resetCoolingDesignCapacityMethod() {
      auto design = ensureDesignObject();
      design.getImpl<detail::ZoneHVACLowTempRadiantVarFlowDesign_Impl>()->resetCoolingDesignCapacityMethod();
    }

    boost::optional<double> ZoneHVACLowTempRadiantVarFlow_Impl::coolingDesignCapacityPerFloorArea() const {
      if (const auto design = designObject()) {
        return design->getImpl<detail::ZoneHVACLowTempRadiantVarFlowDesign_Impl>()->coolingDesignCapacityPerFloorArea();
      }
      return boost::none;
    }

    bool ZoneHVACLowTempRadiantVarFlow_Impl::setCoolingDesignCapacityPerFloorArea(double value) {
      auto design = ensureDesignObject();
      return design.getImpl<detail::ZoneHVACLowTempRadiantVarFlowDesign_Impl>()->setCoolingDesignCapacityPerFloorArea(value);
    }

    void ZoneHVACLowTempRadiantVarFlow_Impl::resetCoolingDesignCapacityPerFloorArea() {
      auto design = ensureDesignObject();
      design.getImpl<detail::ZoneHVACLowTempRadiantVarFlowDesign_Impl>()->resetCoolingDesignCapacityPerFloorArea();
    }

    boost::optional<double> ZoneHVACLowTempRadiantVarFlow_Impl::fractionofAutosizedCoolingDesignCapacity() const {
      if (const auto design = designObject()) {
        return design->getImpl<detail::ZoneHVACLowTempRadiantVarFlowDesign_Impl>()->fractionofAutosizedCoolingDesignCapacity();
      }
      return boost::none;
    }

    bool ZoneHVACLowTempRadiantVarFlow_Impl::setFractionofAutosizedCoolingDesignCapacity(double value) {
      auto design = ensureDesignObject();
      return design.getImpl<detail::ZoneHVACLowTempRadiantVarFlowDesign_Impl>()->setFractionofAutosizedCoolingDesignCapacity(value);
    }

    void ZoneHVACLowTempRadiantVarFlow_Impl::resetFractionofAutosizedCoolingDesignCapacity() {
      auto design = ensureDesignObject();
      design.getImpl<detail::ZoneHVACLowTempRadiantVarFlowDesign_Impl>()->resetFractionofAutosizedCoolingDesignCapacity();
    }

    double ZoneHVACLowTempRadiantVarFlow_Impl::coolingControlThrottlingRange() const {
      if (const auto design = designObject()) {
        return design->getImpl<detail::ZoneHVACLowTempRadiantVarFlowDesign_Impl>()->coolingControlThrottlingRange();
      }
      return kDefaultCoolingControlThrottlingRange;
    }

    bool ZoneHVACLowTempRadiantVarFlow_Impl::isCoolingControlThrottlingRangeDefaulted() const {
      if (const auto design = designObject()) {
        return design->getImpl<detail::ZoneHVACLowTempRadiantVarFlowDesign_Impl>()->isCoolingControlThrottlingRangeDefaulted();
      }
      return true;
    }

    bool ZoneHVACLowTempRadiantVarFlow_Impl::setCoolingControlThrottlingRange(double value) {
      auto design = ensureDesignObject();
      return design.getImpl<detail::ZoneHVACLowTempRadiantVarFlowDesign_Impl>()->setCoolingControlThrottlingRange(value);
    }

    void ZoneHVACLowTempRadiantVarFlow_Impl::resetCoolingControlThrottlingRange() {
      auto design = ensureDesignObject();
      design.getImpl<detail::ZoneHVACLowTempRadiantVarFlowDesign_Impl>()->resetCoolingControlThrottlingRange();
    }

    std::string ZoneHVACLowTempRadiantVarFlow_Impl::condensationControlType() const {
      if (const auto design = designObject()) {
        return design->getImpl<detail::ZoneHVACLowTempRadiantVarFlowDesign_Impl>()->condensationControlType();
      }
      return kDefaultCondensationControlType;
    }

    bool ZoneHVACLowTempRadiantVarFlow_Impl::isCondensationControlTypeDefaulted() const {
      if (const auto design = designObject()) {
        return design->getImpl<detail::ZoneHVACLowTempRadiantVarFlowDesign_Impl>()->isCondensationControlTypeDefaulted();
      }
      return true;
    }

    bool ZoneHVACLowTempRadiantVarFlow_Impl::setCondensationControlType(const std::string& value) {
      auto design = ensureDesignObject();
      return design.getImpl<detail::ZoneHVACLowTempRadiantVarFlowDesign_Impl>()->setCondensationControlType(value);
    }

    void ZoneHVACLowTempRadiantVarFlow_Impl::resetCondensationControlType() {
      auto design = ensureDesignObject();
      design.getImpl<detail::ZoneHVACLowTempRadiantVarFlowDesign_Impl>()->resetCondensationControlType();
    }

    double ZoneHVACLowTempRadiantVarFlow_Impl::condensationControlDewpointOffset() const {
      if (const auto design = designObject()) {
        return design->getImpl<detail::ZoneHVACLowTempRadiantVarFlowDesign_Impl>()->condensationControlDewpointOffset();
      }
      return kDefaultCondensationControlDewpointOffset;
    }

    bool ZoneHVACLowTempRadiantVarFlow_Impl::isCondensationControlDewpointOffsetDefaulted() const {
      if (const auto design = designObject()) {
        return design->getImpl<detail::ZoneHVACLowTempRadiantVarFlowDesign_Impl>()->isCondensationControlDewpointOffsetDefaulted();
      }
      return true;
    }

    bool ZoneHVACLowTempRadiantVarFlow_Impl::setCondensationControlDewpointOffset(double value) {
      auto design = ensureDesignObject();
      return design.getImpl<detail::ZoneHVACLowTempRadiantVarFlowDesign_Impl>()->setCondensationControlDewpointOffset(value);
    }

    void ZoneHVACLowTempRadiantVarFlow_Impl::resetCondensationControlDewpointOffset() {
      auto design = ensureDesignObject();
      design.getImpl<detail::ZoneHVACLowTempRadiantVarFlowDesign_Impl>()->resetCondensationControlDewpointOffset();
    }

    boost::optional<double> ZoneHVACLowTempRadiantVarFlow_Impl::autosizedHydronicTubingLength() const {
      return boost::none;
    }

  }  // namespace detail

}  // namespace epmodel
}  // namespace openstudio
