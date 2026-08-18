/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "AirLoopHVACUnitaryHeatCool.hpp"
#include "AirLoopHVACUnitaryHeatCool_Impl.hpp"

#include "HVACComponent.hpp"
#include "HVACComponent/AirLoopHVACOutdoorAirSystem.hpp"
#include "HVACComponent/ThermalZone.hpp"
#include "HVACComponent/ThermalZone_Impl.hpp"
#include "Loop/AirLoopHVAC.hpp"
#include "Model.hpp"
#include "ModelObject/ModelObject.hpp"
#include "ModelObject/ModelObject_Impl.hpp"
#include "Node.hpp"
#include "Schedule/Schedule.hpp"
#include "Schedule/Schedule_Impl.hpp"
#include "Schedule/ScheduleConstant.hpp"
#include "StraightComponent/StraightComponent.hpp"
#include "WaterToAirComponent/WaterToAirComponent.hpp"
#include "WaterToAirComponent/WaterToAirComponent_Impl.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/core/StringHelpers.hpp>
#include <utilities/idd/AirLoopHVAC_UnitaryHeatCool_FieldEnums.hxx>
#include <utilities/idd/IddEnums.hxx>
#include <utilities/idd/IddFactory.hxx>
#include <utilities/idd/IddObject.hpp>

#include <array>
#include <tuple>

namespace openstudio {
namespace epmodel {

  namespace detail {

    bool isUnitaryHeatCoolAirPathComponent(const HVACComponent& component) {
      return static_cast<bool>(component.optionalCast<StraightComponent>()) || static_cast<bool>(component.optionalCast<WaterToAirComponent>());
    }

    unsigned unitaryHeatCoolAirInletPort(const HVACComponent& component) {
      if (auto straightComponent = component.optionalCast<StraightComponent>()) {
        return straightComponent->inletPort();
      }
      if (auto waterToAirComponent = component.optionalCast<WaterToAirComponent>()) {
        return waterToAirComponent->airInletPort();
      }
      return 0u;
    }

    unsigned unitaryHeatCoolAirOutletPort(const HVACComponent& component) {
      if (auto straightComponent = component.optionalCast<StraightComponent>()) {
        return straightComponent->outletPort();
      }
      if (auto waterToAirComponent = component.optionalCast<WaterToAirComponent>()) {
        return waterToAirComponent->airOutletPort();
      }
      return 0u;
    }

    boost::optional<Node> unitaryHeatCoolAirOutletNode(const HVACComponent& component) {
      const auto outletPort = unitaryHeatCoolAirOutletPort(component);
      if (outletPort == 0u) {
        return boost::none;
      }
      return component.getImpl<detail::ModelObject_Impl>()->resolvedNodeTarget(outletPort);
    }

    bool canAdoptUnitaryHeatCoolChild(const ModelObject& owner, const HVACComponent& component, unsigned roleNameField) {
      if ((component.model() != owner.model()) || !isUnitaryHeatCoolAirPathComponent(component)) {
        return false;
      }
      if (auto containingOwner = component.containingHVACComponent(); containingOwner && (containingOwner->handle() != owner.handle())) {
        return false;
      }
      if (component.airLoopHVAC() || component.airLoopHVACOutdoorAirSystem()) {
        return false;
      }
      for (const auto field :
           {openstudio::AirLoopHVAC_UnitaryHeatCoolFields::SupplyFanName, openstudio::AirLoopHVAC_UnitaryHeatCoolFields::HeatingCoilName,
            openstudio::AirLoopHVAC_UnitaryHeatCoolFields::CoolingCoilName, openstudio::AirLoopHVAC_UnitaryHeatCoolFields::ReheatCoilName}) {
        if (field == roleNameField) {
          continue;
        }
        if (auto existing = owner.getModelObjectTarget<HVACComponent>(field); existing && (existing->handle() == component.handle())) {
          return false;
        }
      }
      return true;
    }

    void disconnectFormerUnitaryHeatCoolChild(HVACComponent& component) {
      if (component.containingHVACComponent()) {
        return;
      }
      const auto inletPort = unitaryHeatCoolAirInletPort(component);
      const auto outletPort = unitaryHeatCoolAirOutletPort(component);
      if ((inletPort != 0u) && (outletPort != 0u)) {
        auto impl = component.getImpl<detail::ModelObject_Impl>();
        impl->setPointer(inletPort, Handle(), false);
        impl->setPointer(outletPort, Handle(), false);
      }
    }

    void reserveUniqueUnitaryHeatCoolName(AirLoopHVACUnitaryHeatCool& unitary, const Model& model) {
      const auto internalNodeNameIsTaken = [&model](const std::string& unitaryName) {
        return static_cast<bool>(model.getConcreteModelObjectByName<Node>(unitaryName + " Air Inlet Node"))
               || static_cast<bool>(model.getConcreteModelObjectByName<Node>(unitaryName + " Air Outlet Node"))
               || static_cast<bool>(model.getConcreteModelObjectByName<Node>(unitaryName + " Fan Outlet Node"))
               || static_cast<bool>(model.getConcreteModelObjectByName<Node>(unitaryName + " Cooling Coil Outlet Node"))
               || static_cast<bool>(model.getConcreteModelObjectByName<Node>(unitaryName + " Heating Coil Outlet Node"));
      };
      while (internalNodeNameIsTaken(unitary.nameString())) {
        OS_ASSERT(unitary.setName(model.nextName(unitary.iddObjectType(), false)));
      }
    }

  }  // namespace detail

  AirLoopHVACUnitaryHeatCool::AirLoopHVACUnitaryHeatCool(const Model& model) : StraightComponent(AirLoopHVACUnitaryHeatCool::iddObjectType(), model) {
    detail::reserveUniqueUnitaryHeatCoolName(*this, model);
    ScheduleConstant alwaysOn(model);
    OS_ASSERT(alwaysOn.setValue(1.0));
    OS_ASSERT(setAvailabilitySchedule(alwaysOn));
    OS_ASSERT(setFanPlacement("DrawThrough"));
    OS_ASSERT(setDehumidificationControlType("None"));
    autosizeCoolingSupplyAirFlowRate();
    autosizeHeatingSupplyAirFlowRate();
    autosizeNoLoadSupplyAirFlowRate();
  }

  AirLoopHVACUnitaryHeatCool::AirLoopHVACUnitaryHeatCool(const Model& model, Schedule& availabilitySchedule, HVACComponent& supplyFan,
                                                         HVACComponent& heatingCoil, HVACComponent& coolingCoil)
    : AirLoopHVACUnitaryHeatCool(model) {
    OS_ASSERT(setAvailabilitySchedule(availabilitySchedule));
    OS_ASSERT(setSupplyFan(supplyFan));
    OS_ASSERT(setHeatingCoil(heatingCoil));
    OS_ASSERT(setCoolingCoil(coolingCoil));
  }

  AirLoopHVACUnitaryHeatCool::AirLoopHVACUnitaryHeatCool(std::shared_ptr<detail::AirLoopHVACUnitaryHeatCool_Impl> impl)
    : StraightComponent(std::move(impl)) {}

  IddObjectType AirLoopHVACUnitaryHeatCool::iddObjectType() {
    return IddObjectType::AirLoopHVAC_UnitaryHeatCool;
  }

  bool AirLoopHVACUnitaryHeatCool::addToNode(Node& node) {
    return getImpl<detail::AirLoopHVACUnitaryHeatCool_Impl>()->addToNode(node);
  }

  Schedule AirLoopHVACUnitaryHeatCool::availabilitySchedule() const {
    return getImpl<detail::AirLoopHVACUnitaryHeatCool_Impl>()->availabilitySchedule();
  }

  bool AirLoopHVACUnitaryHeatCool::setAvailabilitySchedule(Schedule& schedule) {
    return getImpl<detail::AirLoopHVACUnitaryHeatCool_Impl>()->setAvailabilitySchedule(schedule);
  }

  boost::optional<Schedule> AirLoopHVACUnitaryHeatCool::supplyAirFanOperatingModeSchedule() const {
    return getImpl<detail::AirLoopHVACUnitaryHeatCool_Impl>()->supplyAirFanOperatingModeSchedule();
  }

  bool AirLoopHVACUnitaryHeatCool::setSupplyAirFanOperatingModeSchedule(Schedule& schedule) {
    return getImpl<detail::AirLoopHVACUnitaryHeatCool_Impl>()->setSupplyAirFanOperatingModeSchedule(schedule);
  }

  void AirLoopHVACUnitaryHeatCool::resetSupplyAirFanOperatingModeSchedule() {
    getImpl<detail::AirLoopHVACUnitaryHeatCool_Impl>()->resetSupplyAirFanOperatingModeSchedule();
  }

  boost::optional<ThermalZone> AirLoopHVACUnitaryHeatCool::controllingZone() const {
    return getImpl<detail::AirLoopHVACUnitaryHeatCool_Impl>()->controllingZone();
  }

  bool AirLoopHVACUnitaryHeatCool::setControllingZone(ThermalZone& zone) {
    return getImpl<detail::AirLoopHVACUnitaryHeatCool_Impl>()->setControllingZone(zone);
  }

  void AirLoopHVACUnitaryHeatCool::resetControllingZone() {
    getImpl<detail::AirLoopHVACUnitaryHeatCool_Impl>()->resetControllingZone();
  }

  HVACComponent AirLoopHVACUnitaryHeatCool::supplyFan() const {
    return getImpl<detail::AirLoopHVACUnitaryHeatCool_Impl>()->supplyFan();
  }

  bool AirLoopHVACUnitaryHeatCool::setSupplyFan(HVACComponent& hvacComponent) {
    return getImpl<detail::AirLoopHVACUnitaryHeatCool_Impl>()->setSupplyFan(hvacComponent);
  }

  HVACComponent AirLoopHVACUnitaryHeatCool::heatingCoil() const {
    return getImpl<detail::AirLoopHVACUnitaryHeatCool_Impl>()->heatingCoil();
  }

  bool AirLoopHVACUnitaryHeatCool::setHeatingCoil(HVACComponent& hvacComponent) {
    return getImpl<detail::AirLoopHVACUnitaryHeatCool_Impl>()->setHeatingCoil(hvacComponent);
  }

  HVACComponent AirLoopHVACUnitaryHeatCool::coolingCoil() const {
    return getImpl<detail::AirLoopHVACUnitaryHeatCool_Impl>()->coolingCoil();
  }

  bool AirLoopHVACUnitaryHeatCool::setCoolingCoil(HVACComponent& hvacComponent) {
    return getImpl<detail::AirLoopHVACUnitaryHeatCool_Impl>()->setCoolingCoil(hvacComponent);
  }

  boost::optional<HVACComponent> AirLoopHVACUnitaryHeatCool::reheatCoil() const {
    return getImpl<detail::AirLoopHVACUnitaryHeatCool_Impl>()->reheatCoil();
  }

  bool AirLoopHVACUnitaryHeatCool::setReheatCoil(HVACComponent& hvacComponent) {
    return getImpl<detail::AirLoopHVACUnitaryHeatCool_Impl>()->setReheatCoil(hvacComponent);
  }

  void AirLoopHVACUnitaryHeatCool::resetReheatCoil() {
    getImpl<detail::AirLoopHVACUnitaryHeatCool_Impl>()->resetReheatCoil();
  }

  boost::optional<Node> AirLoopHVACUnitaryHeatCool::fanOutletNode() const {
    return getImpl<detail::AirLoopHVACUnitaryHeatCool_Impl>()->fanOutletNode();
  }

  boost::optional<Node> AirLoopHVACUnitaryHeatCool::coolingCoilOutletNode() const {
    return getImpl<detail::AirLoopHVACUnitaryHeatCool_Impl>()->coolingCoilOutletNode();
  }

  boost::optional<Node> AirLoopHVACUnitaryHeatCool::heatingCoilOutletNode() const {
    return getImpl<detail::AirLoopHVACUnitaryHeatCool_Impl>()->heatingCoilOutletNode();
  }

  std::vector<std::string> AirLoopHVACUnitaryHeatCool::supplyFanObjectTypeValues() {
    return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(),
                          openstudio::AirLoopHVAC_UnitaryHeatCoolFields::SupplyFanObjectType);
  }

  std::vector<std::string> AirLoopHVACUnitaryHeatCool::fanPlacementValues() {
    return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(), openstudio::AirLoopHVAC_UnitaryHeatCoolFields::FanPlacement);
  }

  std::vector<std::string> AirLoopHVACUnitaryHeatCool::heatingCoilObjectTypeValues() {
    return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(),
                          openstudio::AirLoopHVAC_UnitaryHeatCoolFields::HeatingCoilObjectType);
  }

  std::vector<std::string> AirLoopHVACUnitaryHeatCool::coolingCoilObjectTypeValues() {
    return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(),
                          openstudio::AirLoopHVAC_UnitaryHeatCoolFields::CoolingCoilObjectType);
  }

  std::vector<std::string> AirLoopHVACUnitaryHeatCool::dehumidificationControlTypeValues() {
    return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(),
                          openstudio::AirLoopHVAC_UnitaryHeatCoolFields::DehumidificationControlType);
  }

  std::vector<std::string> AirLoopHVACUnitaryHeatCool::reheatCoilObjectTypeValues() {
    return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(),
                          openstudio::AirLoopHVAC_UnitaryHeatCoolFields::ReheatCoilObjectType);
  }

  boost::optional<double> AirLoopHVACUnitaryHeatCool::maximumSupplyAirTemperature() const {
    return getImpl<detail::AirLoopHVACUnitaryHeatCool_Impl>()->maximumSupplyAirTemperature();
  }

  bool AirLoopHVACUnitaryHeatCool::isMaximumSupplyAirTemperatureDefaulted() const {
    return getImpl<detail::AirLoopHVACUnitaryHeatCool_Impl>()->isMaximumSupplyAirTemperatureDefaulted();
  }

  bool AirLoopHVACUnitaryHeatCool::isMaximumSupplyAirTemperatureAutosized() const {
    return getImpl<detail::AirLoopHVACUnitaryHeatCool_Impl>()->isMaximumSupplyAirTemperatureAutosized();
  }

  bool AirLoopHVACUnitaryHeatCool::setMaximumSupplyAirTemperature(double maximumSupplyAirTemperature) {
    return getImpl<detail::AirLoopHVACUnitaryHeatCool_Impl>()->setMaximumSupplyAirTemperature(maximumSupplyAirTemperature);
  }

  void AirLoopHVACUnitaryHeatCool::resetMaximumSupplyAirTemperature() {
    getImpl<detail::AirLoopHVACUnitaryHeatCool_Impl>()->resetMaximumSupplyAirTemperature();
  }

  void AirLoopHVACUnitaryHeatCool::autosizeMaximumSupplyAirTemperature() {
    getImpl<detail::AirLoopHVACUnitaryHeatCool_Impl>()->autosizeMaximumSupplyAirTemperature();
  }

  boost::optional<double> AirLoopHVACUnitaryHeatCool::coolingSupplyAirFlowRate() const {
    return getImpl<detail::AirLoopHVACUnitaryHeatCool_Impl>()->coolingSupplyAirFlowRate();
  }

  bool AirLoopHVACUnitaryHeatCool::isCoolingSupplyAirFlowRateAutosized() const {
    return getImpl<detail::AirLoopHVACUnitaryHeatCool_Impl>()->isCoolingSupplyAirFlowRateAutosized();
  }

  bool AirLoopHVACUnitaryHeatCool::setCoolingSupplyAirFlowRate(double coolingSupplyAirFlowRate) {
    return getImpl<detail::AirLoopHVACUnitaryHeatCool_Impl>()->setCoolingSupplyAirFlowRate(coolingSupplyAirFlowRate);
  }

  void AirLoopHVACUnitaryHeatCool::autosizeCoolingSupplyAirFlowRate() {
    getImpl<detail::AirLoopHVACUnitaryHeatCool_Impl>()->autosizeCoolingSupplyAirFlowRate();
  }

  boost::optional<double> AirLoopHVACUnitaryHeatCool::heatingSupplyAirFlowRate() const {
    return getImpl<detail::AirLoopHVACUnitaryHeatCool_Impl>()->heatingSupplyAirFlowRate();
  }

  bool AirLoopHVACUnitaryHeatCool::isHeatingSupplyAirFlowRateAutosized() const {
    return getImpl<detail::AirLoopHVACUnitaryHeatCool_Impl>()->isHeatingSupplyAirFlowRateAutosized();
  }

  bool AirLoopHVACUnitaryHeatCool::setHeatingSupplyAirFlowRate(double heatingSupplyAirFlowRate) {
    return getImpl<detail::AirLoopHVACUnitaryHeatCool_Impl>()->setHeatingSupplyAirFlowRate(heatingSupplyAirFlowRate);
  }

  void AirLoopHVACUnitaryHeatCool::autosizeHeatingSupplyAirFlowRate() {
    getImpl<detail::AirLoopHVACUnitaryHeatCool_Impl>()->autosizeHeatingSupplyAirFlowRate();
  }

  boost::optional<double> AirLoopHVACUnitaryHeatCool::noLoadSupplyAirFlowRate() const {
    return getImpl<detail::AirLoopHVACUnitaryHeatCool_Impl>()->noLoadSupplyAirFlowRate();
  }

  bool AirLoopHVACUnitaryHeatCool::isNoLoadSupplyAirFlowRateAutosized() const {
    return getImpl<detail::AirLoopHVACUnitaryHeatCool_Impl>()->isNoLoadSupplyAirFlowRateAutosized();
  }

  bool AirLoopHVACUnitaryHeatCool::setNoLoadSupplyAirFlowRate(double noLoadSupplyAirFlowRate) {
    return getImpl<detail::AirLoopHVACUnitaryHeatCool_Impl>()->setNoLoadSupplyAirFlowRate(noLoadSupplyAirFlowRate);
  }

  void AirLoopHVACUnitaryHeatCool::resetNoLoadSupplyAirFlowRate() {
    getImpl<detail::AirLoopHVACUnitaryHeatCool_Impl>()->resetNoLoadSupplyAirFlowRate();
  }

  void AirLoopHVACUnitaryHeatCool::autosizeNoLoadSupplyAirFlowRate() {
    getImpl<detail::AirLoopHVACUnitaryHeatCool_Impl>()->autosizeNoLoadSupplyAirFlowRate();
  }

  std::string AirLoopHVACUnitaryHeatCool::supplyFanObjectType() const {
    return getImpl<detail::AirLoopHVACUnitaryHeatCool_Impl>()->supplyFanObjectType();
  }

  bool AirLoopHVACUnitaryHeatCool::setSupplyFanObjectType(const std::string& supplyFanObjectType) {
    return getImpl<detail::AirLoopHVACUnitaryHeatCool_Impl>()->setSupplyFanObjectType(supplyFanObjectType);
  }

  std::string AirLoopHVACUnitaryHeatCool::fanPlacement() const {
    return getImpl<detail::AirLoopHVACUnitaryHeatCool_Impl>()->fanPlacement();
  }

  bool AirLoopHVACUnitaryHeatCool::setFanPlacement(const std::string& fanPlacement) {
    return getImpl<detail::AirLoopHVACUnitaryHeatCool_Impl>()->setFanPlacement(fanPlacement);
  }

  bool AirLoopHVACUnitaryHeatCool::isFanPlacementDefaulted() const {
    return getImpl<detail::AirLoopHVACUnitaryHeatCool_Impl>()->isFanPlacementDefaulted();
  }

  void AirLoopHVACUnitaryHeatCool::resetFanPlacement() {
    getImpl<detail::AirLoopHVACUnitaryHeatCool_Impl>()->resetFanPlacement();
  }

  std::string AirLoopHVACUnitaryHeatCool::heatingCoilObjectType() const {
    return getImpl<detail::AirLoopHVACUnitaryHeatCool_Impl>()->heatingCoilObjectType();
  }

  bool AirLoopHVACUnitaryHeatCool::setHeatingCoilObjectType(const std::string& heatingCoilObjectType) {
    return getImpl<detail::AirLoopHVACUnitaryHeatCool_Impl>()->setHeatingCoilObjectType(heatingCoilObjectType);
  }

  std::string AirLoopHVACUnitaryHeatCool::coolingCoilObjectType() const {
    return getImpl<detail::AirLoopHVACUnitaryHeatCool_Impl>()->coolingCoilObjectType();
  }

  bool AirLoopHVACUnitaryHeatCool::setCoolingCoilObjectType(const std::string& coolingCoilObjectType) {
    return getImpl<detail::AirLoopHVACUnitaryHeatCool_Impl>()->setCoolingCoilObjectType(coolingCoilObjectType);
  }

  std::string AirLoopHVACUnitaryHeatCool::dehumidificationControlType() const {
    return getImpl<detail::AirLoopHVACUnitaryHeatCool_Impl>()->dehumidificationControlType();
  }

  bool AirLoopHVACUnitaryHeatCool::setDehumidificationControlType(const std::string& dehumidificationControlType) {
    return getImpl<detail::AirLoopHVACUnitaryHeatCool_Impl>()->setDehumidificationControlType(dehumidificationControlType);
  }

  bool AirLoopHVACUnitaryHeatCool::isDehumidificationControlTypeDefaulted() const {
    return getImpl<detail::AirLoopHVACUnitaryHeatCool_Impl>()->isDehumidificationControlTypeDefaulted();
  }

  void AirLoopHVACUnitaryHeatCool::resetDehumidificationControlType() {
    getImpl<detail::AirLoopHVACUnitaryHeatCool_Impl>()->resetDehumidificationControlType();
  }

  boost::optional<std::string> AirLoopHVACUnitaryHeatCool::reheatCoilObjectType() const {
    return getImpl<detail::AirLoopHVACUnitaryHeatCool_Impl>()->reheatCoilObjectType();
  }

  bool AirLoopHVACUnitaryHeatCool::setReheatCoilObjectType(const std::string& reheatCoilObjectType) {
    return getImpl<detail::AirLoopHVACUnitaryHeatCool_Impl>()->setReheatCoilObjectType(reheatCoilObjectType);
  }

  void AirLoopHVACUnitaryHeatCool::resetReheatCoilObjectType() {
    getImpl<detail::AirLoopHVACUnitaryHeatCool_Impl>()->resetReheatCoilObjectType();
  }

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
  namespace detail {

    unsigned AirLoopHVACUnitaryHeatCool_Impl::inletPort() const {
      return openstudio::AirLoopHVAC_UnitaryHeatCoolFields::UnitarySystemAirInletNodeName;
    }

    unsigned AirLoopHVACUnitaryHeatCool_Impl::outletPort() const {
      return openstudio::AirLoopHVAC_UnitaryHeatCoolFields::UnitarySystemAirOutletNodeName;
    }

    bool AirLoopHVACUnitaryHeatCool_Impl::addToNode(Node& node) {
      auto airLoop = node.airLoopHVAC();
      if (!(airLoop && airLoop->supplyComponent(node.handle()))) {
        return false;
      }
      if (!StraightComponent_Impl::addToNode(node)) {
        return false;
      }
      maintainContainedAirPath();
      return true;
    }

    std::vector<IdfObject> AirLoopHVACUnitaryHeatCool_Impl::remove() {
      const auto ownedChildren = children();
      auto removedParent = StraightComponent_Impl::remove();
      if (removedParent.empty()) {
        return {};
      }

      std::vector<IdfObject> result;
      for (const auto& child : ownedChildren) {
        if (auto component = child.optionalCast<HVACComponent>()) {
          auto removed = component->remove();
          result.insert(result.end(), removed.begin(), removed.end());
        }
      }
      result.insert(result.end(), removedParent.begin(), removedParent.end());
      return result;
    }

    void AirLoopHVACUnitaryHeatCool_Impl::doCanonicalize(LoadContext& context) {
      struct ChildRole
      {
        unsigned typeField;
        unsigned nameField;
        const char* description;
      };
      static constexpr std::array<ChildRole, 4> childRoles{{
        {openstudio::AirLoopHVAC_UnitaryHeatCoolFields::SupplyFanObjectType, openstudio::AirLoopHVAC_UnitaryHeatCoolFields::SupplyFanName,
         "supply fan"},
        {openstudio::AirLoopHVAC_UnitaryHeatCoolFields::HeatingCoilObjectType, openstudio::AirLoopHVAC_UnitaryHeatCoolFields::HeatingCoilName,
         "heating coil"},
        {openstudio::AirLoopHVAC_UnitaryHeatCoolFields::CoolingCoilObjectType, openstudio::AirLoopHVAC_UnitaryHeatCoolFields::CoolingCoilName,
         "cooling coil"},
        {openstudio::AirLoopHVAC_UnitaryHeatCoolFields::ReheatCoilObjectType, openstudio::AirLoopHVAC_UnitaryHeatCoolFields::ReheatCoilName,
         "reheat coil"},
      }};

      auto owner = getObject<ModelObject>();
      const auto unitaryHeatCools = model().getConcreteModelObjects<AirLoopHVACUnitaryHeatCool>();
      const auto stableOwnerKey = [&unitaryHeatCools](const AirLoopHVACUnitaryHeatCool& candidate, std::size_t roleIndex) {
        const auto candidateIt =
          std::ranges::find_if(unitaryHeatCools, [&candidate](const auto& object) { return object.handle() == candidate.handle(); });
        OS_ASSERT(candidateIt != unitaryHeatCools.end());
        return std::tuple(candidate.nameString(), static_cast<std::size_t>(std::distance(unitaryHeatCools.begin(), candidateIt)), roleIndex);
      };
      const auto thisUnitary = owner.cast<AirLoopHVACUnitaryHeatCool>();
      for (std::size_t roleIndex = 0; roleIndex < childRoles.size(); ++roleIndex) {
        const auto& role = childRoles[roleIndex];
        auto child = owner.getModelObjectTarget<HVACComponent>(role.nameField);
        if (!child) {
          continue;
        }

        bool keepClaim = true;
        const auto ownerKey = stableOwnerKey(thisUnitary, roleIndex);
        for (const auto& source : child->sources()) {
          const auto candidateOwner = source.optionalCast<HVACComponent>();
          if (!candidateOwner) {
            continue;
          }
          const auto candidateChildren = candidateOwner->children();
          if (std::ranges::none_of(candidateChildren, [&child](const auto& candidateChild) { return candidateChild.handle() == child->handle(); })) {
            continue;
          }

          if (const auto candidateUnitary = candidateOwner->optionalCast<AirLoopHVACUnitaryHeatCool>()) {
            for (std::size_t candidateRoleIndex = 0; candidateRoleIndex < childRoles.size(); ++candidateRoleIndex) {
              const auto candidateChild = candidateUnitary->getModelObjectTarget<HVACComponent>(childRoles[candidateRoleIndex].nameField);
              if (candidateChild && (candidateChild->handle() == child->handle())
                  && (stableOwnerKey(*candidateUnitary, candidateRoleIndex) < ownerKey)) {
                keepClaim = false;
              }
            }
          } else {
            // Established compound types retain their persisted ownership claim. This type yields so that importing a malformed shared-child
            // graph converges without allowing two canonicalizers to fight over the child's air-node wiring.
            keepClaim = false;
          }
        }

        if (!keepClaim) {
          OS_ASSERT(setPointer(role.nameField, Handle(), false));
          OS_ASSERT(setString(role.typeField, ""));
          detail::addLoadWarning(context, "Cleared duplicate " + std::string(role.description) + " ownership from AirLoopHVAC:UnitaryHeatCool '"
                                            + owner.nameString() + "' for child '" + child->nameString() + "'.");
        }
      }

      repairContainedAirPath(context);
      constexpr auto availabilityField = openstudio::AirLoopHVAC_UnitaryHeatCoolFields::AvailabilityScheduleName;
      const auto rawAvailability = openstudio::detail::IdfObject_Impl::getString(availabilityField, false, true);
      if ((!rawAvailability || rawAvailability->empty()) && !owner.getModelObjectTarget<Schedule>(availabilityField)) {
        auto alwaysOn = model().alwaysOnDiscreteSchedule();
        if (setAvailabilitySchedule(alwaysOn)) {
          detail::addLoadInfo(context, "Attached the always-on availability schedule to AirLoopHVAC:UnitaryHeatCool '" + owner.nameString() + "'.");
        } else {
          detail::addLoadError(context,
                               "Failed to attach the always-on availability schedule to AirLoopHVAC:UnitaryHeatCool '" + owner.nameString() + "'.");
        }
      }
    }

    std::vector<ModelObject> AirLoopHVACUnitaryHeatCool_Impl::children() const {
      std::vector<ModelObject> result;
      const auto object = getObject<ModelObject>();
      for (const auto field :
           {openstudio::AirLoopHVAC_UnitaryHeatCoolFields::SupplyFanName, openstudio::AirLoopHVAC_UnitaryHeatCoolFields::HeatingCoilName,
            openstudio::AirLoopHVAC_UnitaryHeatCoolFields::CoolingCoilName, openstudio::AirLoopHVAC_UnitaryHeatCoolFields::ReheatCoilName}) {
        if (auto component = object.getModelObjectTarget<HVACComponent>(field)) {
          result.emplace_back(*component);
        }
      }
      return result;
    }

    Schedule AirLoopHVACUnitaryHeatCool_Impl::availabilitySchedule() const {
      auto value = getObject<ModelObject>().getModelObjectTarget<Schedule>(openstudio::AirLoopHVAC_UnitaryHeatCoolFields::AvailabilityScheduleName);
      OS_ASSERT(value);
      return *value;
    }

    bool AirLoopHVACUnitaryHeatCool_Impl::setAvailabilitySchedule(Schedule& schedule) {
      return setSchedule(openstudio::AirLoopHVAC_UnitaryHeatCoolFields::AvailabilityScheduleName, "AirLoopHVACUnitaryHeatCool", "Availability",
                         schedule);
    }

    boost::optional<Schedule> AirLoopHVACUnitaryHeatCool_Impl::supplyAirFanOperatingModeSchedule() const {
      return getObject<ModelObject>().getModelObjectTarget<Schedule>(
        openstudio::AirLoopHVAC_UnitaryHeatCoolFields::SupplyAirFanOperatingModeScheduleName);
    }

    bool AirLoopHVACUnitaryHeatCool_Impl::setSupplyAirFanOperatingModeSchedule(Schedule& schedule) {
      return setSchedule(openstudio::AirLoopHVAC_UnitaryHeatCoolFields::SupplyAirFanOperatingModeScheduleName, "AirLoopHVACUnitaryHeatCool",
                         "Supply Air Fan Operating Mode", schedule);
    }

    void AirLoopHVACUnitaryHeatCool_Impl::resetSupplyAirFanOperatingModeSchedule() {
      OS_ASSERT(setString(openstudio::AirLoopHVAC_UnitaryHeatCoolFields::SupplyAirFanOperatingModeScheduleName, ""));
    }

    boost::optional<ThermalZone> AirLoopHVACUnitaryHeatCool_Impl::controllingZone() const {
      return getObject<ModelObject>().getModelObjectTarget<ThermalZone>(
        openstudio::AirLoopHVAC_UnitaryHeatCoolFields::ControllingZoneorThermostatLocation);
    }

    bool AirLoopHVACUnitaryHeatCool_Impl::setControllingZone(ThermalZone& zone) {
      return setPointer(openstudio::AirLoopHVAC_UnitaryHeatCoolFields::ControllingZoneorThermostatLocation, zone.handle());
    }

    void AirLoopHVACUnitaryHeatCool_Impl::resetControllingZone() {
      OS_ASSERT(setString(openstudio::AirLoopHVAC_UnitaryHeatCoolFields::ControllingZoneorThermostatLocation, ""));
    }

    HVACComponent AirLoopHVACUnitaryHeatCool_Impl::supplyFan() const {
      auto value = getObject<ModelObject>().getModelObjectTarget<HVACComponent>(openstudio::AirLoopHVAC_UnitaryHeatCoolFields::SupplyFanName);
      OS_ASSERT(value);
      return *value;
    }

    bool AirLoopHVACUnitaryHeatCool_Impl::setSupplyFan(HVACComponent& hvacComponent) {
      const auto owner = getObject<ModelObject>();
      constexpr auto typeField = openstudio::AirLoopHVAC_UnitaryHeatCoolFields::SupplyFanObjectType;
      constexpr auto nameField = openstudio::AirLoopHVAC_UnitaryHeatCoolFields::SupplyFanName;
      if (!hvacComponent.optionalCast<StraightComponent>() || !canAdoptUnitaryHeatCoolChild(owner, hvacComponent, nameField)) {
        return false;
      }
      auto oldComponent = owner.getModelObjectTarget<HVACComponent>(nameField);
      const auto oldType = getString(typeField).value_or("");
      if (!setString(typeField, hvacComponent.iddObject().name()) || !setPointer(nameField, hvacComponent.handle(), false)) {
        OS_ASSERT(setString(typeField, oldType));
        OS_ASSERT(setPointer(nameField, oldComponent ? oldComponent->handle() : Handle(), false));
        return false;
      }
      if (oldComponent && (oldComponent->handle() != hvacComponent.handle())) {
        disconnectFormerUnitaryHeatCoolChild(*oldComponent);
      }
      maintainContainedAirPath();
      return true;
    }

    HVACComponent AirLoopHVACUnitaryHeatCool_Impl::heatingCoil() const {
      auto value = getObject<ModelObject>().getModelObjectTarget<HVACComponent>(openstudio::AirLoopHVAC_UnitaryHeatCoolFields::HeatingCoilName);
      OS_ASSERT(value);
      return *value;
    }

    bool AirLoopHVACUnitaryHeatCool_Impl::setHeatingCoil(HVACComponent& hvacComponent) {
      const auto owner = getObject<ModelObject>();
      constexpr auto typeField = openstudio::AirLoopHVAC_UnitaryHeatCoolFields::HeatingCoilObjectType;
      constexpr auto nameField = openstudio::AirLoopHVAC_UnitaryHeatCoolFields::HeatingCoilName;
      if (!canAdoptUnitaryHeatCoolChild(owner, hvacComponent, nameField)) {
        return false;
      }
      auto oldComponent = owner.getModelObjectTarget<HVACComponent>(nameField);
      const auto oldType = getString(typeField).value_or("");
      if (!setString(typeField, hvacComponent.iddObject().name()) || !setPointer(nameField, hvacComponent.handle(), false)) {
        OS_ASSERT(setString(typeField, oldType));
        OS_ASSERT(setPointer(nameField, oldComponent ? oldComponent->handle() : Handle(), false));
        return false;
      }
      if (oldComponent && (oldComponent->handle() != hvacComponent.handle())) {
        disconnectFormerUnitaryHeatCoolChild(*oldComponent);
      }
      maintainContainedAirPath();
      return true;
    }

    HVACComponent AirLoopHVACUnitaryHeatCool_Impl::coolingCoil() const {
      auto value = getObject<ModelObject>().getModelObjectTarget<HVACComponent>(openstudio::AirLoopHVAC_UnitaryHeatCoolFields::CoolingCoilName);
      OS_ASSERT(value);
      return *value;
    }

    bool AirLoopHVACUnitaryHeatCool_Impl::setCoolingCoil(HVACComponent& hvacComponent) {
      const auto owner = getObject<ModelObject>();
      constexpr auto typeField = openstudio::AirLoopHVAC_UnitaryHeatCoolFields::CoolingCoilObjectType;
      constexpr auto nameField = openstudio::AirLoopHVAC_UnitaryHeatCoolFields::CoolingCoilName;
      if (!canAdoptUnitaryHeatCoolChild(owner, hvacComponent, nameField)) {
        return false;
      }
      auto oldComponent = owner.getModelObjectTarget<HVACComponent>(nameField);
      const auto oldType = getString(typeField).value_or("");
      if (!setString(typeField, hvacComponent.iddObject().name()) || !setPointer(nameField, hvacComponent.handle(), false)) {
        OS_ASSERT(setString(typeField, oldType));
        OS_ASSERT(setPointer(nameField, oldComponent ? oldComponent->handle() : Handle(), false));
        return false;
      }
      if (oldComponent && (oldComponent->handle() != hvacComponent.handle())) {
        disconnectFormerUnitaryHeatCoolChild(*oldComponent);
      }
      maintainContainedAirPath();
      return true;
    }

    boost::optional<HVACComponent> AirLoopHVACUnitaryHeatCool_Impl::reheatCoil() const {
      return getObject<ModelObject>().getModelObjectTarget<HVACComponent>(openstudio::AirLoopHVAC_UnitaryHeatCoolFields::ReheatCoilName);
    }

    bool AirLoopHVACUnitaryHeatCool_Impl::setReheatCoil(HVACComponent& hvacComponent) {
      const auto owner = getObject<ModelObject>();
      constexpr auto typeField = openstudio::AirLoopHVAC_UnitaryHeatCoolFields::ReheatCoilObjectType;
      constexpr auto nameField = openstudio::AirLoopHVAC_UnitaryHeatCoolFields::ReheatCoilName;
      if (!canAdoptUnitaryHeatCoolChild(owner, hvacComponent, nameField)) {
        return false;
      }
      auto oldComponent = owner.getModelObjectTarget<HVACComponent>(nameField);
      const auto oldType = getString(typeField).value_or("");
      if (!setString(typeField, hvacComponent.iddObject().name()) || !setPointer(nameField, hvacComponent.handle(), false)) {
        OS_ASSERT(setString(typeField, oldType));
        OS_ASSERT(setPointer(nameField, oldComponent ? oldComponent->handle() : Handle(), false));
        return false;
      }
      if (oldComponent && (oldComponent->handle() != hvacComponent.handle())) {
        disconnectFormerUnitaryHeatCoolChild(*oldComponent);
      }
      maintainContainedAirPath();
      return true;
    }

    void AirLoopHVACUnitaryHeatCool_Impl::resetReheatCoil() {
      auto oldComponent = reheatCoil();
      OS_ASSERT(setString(openstudio::AirLoopHVAC_UnitaryHeatCoolFields::ReheatCoilName, ""));
      OS_ASSERT(setString(openstudio::AirLoopHVAC_UnitaryHeatCoolFields::ReheatCoilObjectType, ""));
      if (oldComponent) {
        disconnectFormerUnitaryHeatCoolChild(*oldComponent);
      }
      maintainContainedAirPath();
    }

    boost::optional<Node> AirLoopHVACUnitaryHeatCool_Impl::fanOutletNode() const {
      auto fanObject = getObject<ModelObject>().getModelObjectTarget<HVACComponent>(openstudio::AirLoopHVAC_UnitaryHeatCoolFields::SupplyFanName);
      auto fan = fanObject ? fanObject->optionalCast<StraightComponent>() : boost::none;
      if (!fan) {
        return boost::none;
      }
      auto outlet = fan->outletModelObject();
      return outlet ? outlet->optionalCast<Node>() : boost::none;
    }

    boost::optional<Node> AirLoopHVACUnitaryHeatCool_Impl::coolingCoilOutletNode() const {
      auto component = getObject<ModelObject>().getModelObjectTarget<HVACComponent>(openstudio::AirLoopHVAC_UnitaryHeatCoolFields::CoolingCoilName);
      return component ? unitaryHeatCoolAirOutletNode(*component) : boost::none;
    }

    boost::optional<Node> AirLoopHVACUnitaryHeatCool_Impl::heatingCoilOutletNode() const {
      auto component = getObject<ModelObject>().getModelObjectTarget<HVACComponent>(openstudio::AirLoopHVAC_UnitaryHeatCoolFields::HeatingCoilName);
      return component ? unitaryHeatCoolAirOutletNode(*component) : boost::none;
    }

    boost::optional<double> AirLoopHVACUnitaryHeatCool_Impl::maximumSupplyAirTemperature() const {
      return getDouble(openstudio::AirLoopHVAC_UnitaryHeatCoolFields::MaximumSupplyAirTemperature, true);
    }

    bool AirLoopHVACUnitaryHeatCool_Impl::isMaximumSupplyAirTemperatureDefaulted() const {
      return isEmpty(openstudio::AirLoopHVAC_UnitaryHeatCoolFields::MaximumSupplyAirTemperature);
    }

    bool AirLoopHVACUnitaryHeatCool_Impl::isMaximumSupplyAirTemperatureAutosized() const {
      if (auto value = getString(openstudio::AirLoopHVAC_UnitaryHeatCoolFields::MaximumSupplyAirTemperature, true)) {
        return openstudio::istringEqual(*value, "autosize");
      }
      return false;
    }

    bool AirLoopHVACUnitaryHeatCool_Impl::setMaximumSupplyAirTemperature(double maximumSupplyAirTemperature) {
      const bool result = setDouble(openstudio::AirLoopHVAC_UnitaryHeatCoolFields::MaximumSupplyAirTemperature, maximumSupplyAirTemperature);
      OS_ASSERT(result);
      return result;
    }

    void AirLoopHVACUnitaryHeatCool_Impl::resetMaximumSupplyAirTemperature() {
      OS_ASSERT(setString(openstudio::AirLoopHVAC_UnitaryHeatCoolFields::MaximumSupplyAirTemperature, ""));
    }

    void AirLoopHVACUnitaryHeatCool_Impl::autosizeMaximumSupplyAirTemperature() {
      OS_ASSERT(setString(openstudio::AirLoopHVAC_UnitaryHeatCoolFields::MaximumSupplyAirTemperature, "autosize"));
    }

    boost::optional<double> AirLoopHVACUnitaryHeatCool_Impl::coolingSupplyAirFlowRate() const {
      return getDouble(openstudio::AirLoopHVAC_UnitaryHeatCoolFields::CoolingSupplyAirFlowRate, true);
    }

    bool AirLoopHVACUnitaryHeatCool_Impl::isCoolingSupplyAirFlowRateAutosized() const {
      if (auto value = getString(openstudio::AirLoopHVAC_UnitaryHeatCoolFields::CoolingSupplyAirFlowRate, true)) {
        return openstudio::istringEqual(*value, "autosize");
      }
      return false;
    }

    bool AirLoopHVACUnitaryHeatCool_Impl::setCoolingSupplyAirFlowRate(double coolingSupplyAirFlowRate) {
      return setDouble(openstudio::AirLoopHVAC_UnitaryHeatCoolFields::CoolingSupplyAirFlowRate, coolingSupplyAirFlowRate);
    }

    void AirLoopHVACUnitaryHeatCool_Impl::autosizeCoolingSupplyAirFlowRate() {
      OS_ASSERT(setString(openstudio::AirLoopHVAC_UnitaryHeatCoolFields::CoolingSupplyAirFlowRate, "autosize"));
    }

    boost::optional<double> AirLoopHVACUnitaryHeatCool_Impl::heatingSupplyAirFlowRate() const {
      return getDouble(openstudio::AirLoopHVAC_UnitaryHeatCoolFields::HeatingSupplyAirFlowRate, true);
    }

    bool AirLoopHVACUnitaryHeatCool_Impl::isHeatingSupplyAirFlowRateAutosized() const {
      if (auto value = getString(openstudio::AirLoopHVAC_UnitaryHeatCoolFields::HeatingSupplyAirFlowRate, true)) {
        return openstudio::istringEqual(*value, "autosize");
      }
      return false;
    }

    bool AirLoopHVACUnitaryHeatCool_Impl::setHeatingSupplyAirFlowRate(double heatingSupplyAirFlowRate) {
      return setDouble(openstudio::AirLoopHVAC_UnitaryHeatCoolFields::HeatingSupplyAirFlowRate, heatingSupplyAirFlowRate);
    }

    void AirLoopHVACUnitaryHeatCool_Impl::autosizeHeatingSupplyAirFlowRate() {
      OS_ASSERT(setString(openstudio::AirLoopHVAC_UnitaryHeatCoolFields::HeatingSupplyAirFlowRate, "autosize"));
    }

    boost::optional<double> AirLoopHVACUnitaryHeatCool_Impl::noLoadSupplyAirFlowRate() const {
      return getDouble(openstudio::AirLoopHVAC_UnitaryHeatCoolFields::NoLoadSupplyAirFlowRate, true);
    }

    bool AirLoopHVACUnitaryHeatCool_Impl::isNoLoadSupplyAirFlowRateAutosized() const {
      if (auto value = getString(openstudio::AirLoopHVAC_UnitaryHeatCoolFields::NoLoadSupplyAirFlowRate, true)) {
        return openstudio::istringEqual(*value, "autosize");
      }
      return false;
    }

    bool AirLoopHVACUnitaryHeatCool_Impl::setNoLoadSupplyAirFlowRate(double noLoadSupplyAirFlowRate) {
      return setDouble(openstudio::AirLoopHVAC_UnitaryHeatCoolFields::NoLoadSupplyAirFlowRate, noLoadSupplyAirFlowRate);
    }

    void AirLoopHVACUnitaryHeatCool_Impl::resetNoLoadSupplyAirFlowRate() {
      OS_ASSERT(setString(openstudio::AirLoopHVAC_UnitaryHeatCoolFields::NoLoadSupplyAirFlowRate, ""));
    }

    void AirLoopHVACUnitaryHeatCool_Impl::autosizeNoLoadSupplyAirFlowRate() {
      OS_ASSERT(setString(openstudio::AirLoopHVAC_UnitaryHeatCoolFields::NoLoadSupplyAirFlowRate, "autosize"));
    }

    std::string AirLoopHVACUnitaryHeatCool_Impl::supplyFanObjectType() const {
      const auto value = getString(openstudio::AirLoopHVAC_UnitaryHeatCoolFields::SupplyFanObjectType, true);
      OS_ASSERT(value);
      return *value;
    }

    bool AirLoopHVACUnitaryHeatCool_Impl::setSupplyFanObjectType(const std::string& supplyFanObjectType) {
      if (auto component =
            getObject<ModelObject>().getModelObjectTarget<HVACComponent>(openstudio::AirLoopHVAC_UnitaryHeatCoolFields::SupplyFanName)) {
        return openstudio::istringEqual(supplyFanObjectType, component->iddObject().name())
               && setString(openstudio::AirLoopHVAC_UnitaryHeatCoolFields::SupplyFanObjectType, component->iddObject().name());
      }
      return false;
    }

    std::string AirLoopHVACUnitaryHeatCool_Impl::fanPlacement() const {
      const auto value = getString(openstudio::AirLoopHVAC_UnitaryHeatCoolFields::FanPlacement, true);
      OS_ASSERT(value);
      return *value;
    }

    bool AirLoopHVACUnitaryHeatCool_Impl::setFanPlacement(const std::string& fanPlacement) {
      const bool result = setString(openstudio::AirLoopHVAC_UnitaryHeatCoolFields::FanPlacement, fanPlacement);
      if (result) {
        maintainContainedAirPath();
      }
      return result;
    }

    bool AirLoopHVACUnitaryHeatCool_Impl::isFanPlacementDefaulted() const {
      return isEmpty(openstudio::AirLoopHVAC_UnitaryHeatCoolFields::FanPlacement);
    }

    void AirLoopHVACUnitaryHeatCool_Impl::resetFanPlacement() {
      OS_ASSERT(setString(openstudio::AirLoopHVAC_UnitaryHeatCoolFields::FanPlacement, ""));
      maintainContainedAirPath();
    }

    std::string AirLoopHVACUnitaryHeatCool_Impl::heatingCoilObjectType() const {
      const auto value = getString(openstudio::AirLoopHVAC_UnitaryHeatCoolFields::HeatingCoilObjectType, true);
      OS_ASSERT(value);
      return *value;
    }

    bool AirLoopHVACUnitaryHeatCool_Impl::setHeatingCoilObjectType(const std::string& heatingCoilObjectType) {
      if (auto component =
            getObject<ModelObject>().getModelObjectTarget<HVACComponent>(openstudio::AirLoopHVAC_UnitaryHeatCoolFields::HeatingCoilName)) {
        return openstudio::istringEqual(heatingCoilObjectType, component->iddObject().name())
               && setString(openstudio::AirLoopHVAC_UnitaryHeatCoolFields::HeatingCoilObjectType, component->iddObject().name());
      }
      return false;
    }

    std::string AirLoopHVACUnitaryHeatCool_Impl::coolingCoilObjectType() const {
      const auto value = getString(openstudio::AirLoopHVAC_UnitaryHeatCoolFields::CoolingCoilObjectType, true);
      OS_ASSERT(value);
      return *value;
    }

    bool AirLoopHVACUnitaryHeatCool_Impl::setCoolingCoilObjectType(const std::string& coolingCoilObjectType) {
      if (auto component =
            getObject<ModelObject>().getModelObjectTarget<HVACComponent>(openstudio::AirLoopHVAC_UnitaryHeatCoolFields::CoolingCoilName)) {
        return openstudio::istringEqual(coolingCoilObjectType, component->iddObject().name())
               && setString(openstudio::AirLoopHVAC_UnitaryHeatCoolFields::CoolingCoilObjectType, component->iddObject().name());
      }
      return false;
    }

    std::string AirLoopHVACUnitaryHeatCool_Impl::dehumidificationControlType() const {
      const auto value = getString(openstudio::AirLoopHVAC_UnitaryHeatCoolFields::DehumidificationControlType, true);
      OS_ASSERT(value);
      return *value;
    }

    bool AirLoopHVACUnitaryHeatCool_Impl::setDehumidificationControlType(const std::string& dehumidificationControlType) {
      return setString(openstudio::AirLoopHVAC_UnitaryHeatCoolFields::DehumidificationControlType, dehumidificationControlType);
    }

    bool AirLoopHVACUnitaryHeatCool_Impl::isDehumidificationControlTypeDefaulted() const {
      return isEmpty(openstudio::AirLoopHVAC_UnitaryHeatCoolFields::DehumidificationControlType);
    }

    void AirLoopHVACUnitaryHeatCool_Impl::resetDehumidificationControlType() {
      OS_ASSERT(setString(openstudio::AirLoopHVAC_UnitaryHeatCoolFields::DehumidificationControlType, ""));
    }

    boost::optional<std::string> AirLoopHVACUnitaryHeatCool_Impl::reheatCoilObjectType() const {
      return getString(openstudio::AirLoopHVAC_UnitaryHeatCoolFields::ReheatCoilObjectType, true);
    }

    bool AirLoopHVACUnitaryHeatCool_Impl::setReheatCoilObjectType(const std::string& reheatCoilObjectType) {
      if (auto component = reheatCoil()) {
        return openstudio::istringEqual(reheatCoilObjectType, component->iddObject().name())
               && setString(openstudio::AirLoopHVAC_UnitaryHeatCoolFields::ReheatCoilObjectType, component->iddObject().name());
      }
      return false;
    }

    void AirLoopHVACUnitaryHeatCool_Impl::resetReheatCoilObjectType() {
      if (auto component = reheatCoil()) {
        OS_ASSERT(setString(openstudio::AirLoopHVAC_UnitaryHeatCoolFields::ReheatCoilObjectType, component->iddObject().name()));
      } else {
        OS_ASSERT(setString(openstudio::AirLoopHVAC_UnitaryHeatCoolFields::ReheatCoilObjectType, ""));
      }
    }

    bool AirLoopHVACUnitaryHeatCool_Impl::maintainContainedAirPath() {
      return reconcileContainedAirPath(false, nullptr);
    }

    bool AirLoopHVACUnitaryHeatCool_Impl::repairContainedAirPath(LoadContext& context) {
      return reconcileContainedAirPath(true, &context);
    }

    bool AirLoopHVACUnitaryHeatCool_Impl::reconcileContainedAirPath(bool allowChildNodeRecovery, LoadContext* context) {
      auto thisObject = getObject<ModelObject>();
      if (!thisObject.name()) {
        thisObject.createName();
      }

      auto fanObject = thisObject.getModelObjectTarget<HVACComponent>(openstudio::AirLoopHVAC_UnitaryHeatCoolFields::SupplyFanName);
      auto heatingObject = thisObject.getModelObjectTarget<HVACComponent>(openstudio::AirLoopHVAC_UnitaryHeatCoolFields::HeatingCoilName);
      auto coolingObject = thisObject.getModelObjectTarget<HVACComponent>(openstudio::AirLoopHVAC_UnitaryHeatCoolFields::CoolingCoilName);
      auto reheatObject = thisObject.getModelObjectTarget<HVACComponent>(openstudio::AirLoopHVAC_UnitaryHeatCoolFields::ReheatCoilName);

      auto fan = fanObject ? fanObject->optionalCast<StraightComponent>() : boost::none;
      auto heating =
        (heatingObject && isUnitaryHeatCoolAirPathComponent(*heatingObject)) ? boost::optional<HVACComponent>(*heatingObject) : boost::none;
      auto cooling =
        (coolingObject && isUnitaryHeatCoolAirPathComponent(*coolingObject)) ? boost::optional<HVACComponent>(*coolingObject) : boost::none;
      auto reheat = (reheatObject && isUnitaryHeatCoolAirPathComponent(*reheatObject)) ? boost::optional<HVACComponent>(*reheatObject) : boost::none;

      bool changed = false;
      bool nodeWiringChanged = false;
      auto trackNodeChange = [&](bool value) {
        nodeWiringChanged = nodeWiringChanged || value;
        changed = changed || value;
      };

      const auto synchronizeObjectType = [&](unsigned objectTypeField, const boost::optional<HVACComponent>& component) {
        const auto currentType = thisObject.getString(objectTypeField, true);
        const auto expectedType = component ? boost::optional<std::string>(component->iddObject().name()) : boost::none;
        if (expectedType) {
          if (!currentType || !openstudio::istringEqual(*currentType, *expectedType)) {
            OS_ASSERT(thisObject.setString(objectTypeField, *expectedType));
            changed = true;
          }
        } else if (currentType && !currentType->empty()) {
          OS_ASSERT(thisObject.setString(objectTypeField, ""));
          changed = true;
        }
      };
      synchronizeObjectType(openstudio::AirLoopHVAC_UnitaryHeatCoolFields::SupplyFanObjectType,
                            fan ? boost::optional<HVACComponent>(fan->cast<HVACComponent>()) : boost::none);
      synchronizeObjectType(openstudio::AirLoopHVAC_UnitaryHeatCoolFields::HeatingCoilObjectType, heatingObject);
      synchronizeObjectType(openstudio::AirLoopHVAC_UnitaryHeatCoolFields::CoolingCoilObjectType, coolingObject);
      synchronizeObjectType(openstudio::AirLoopHVAC_UnitaryHeatCoolFields::ReheatCoilObjectType, reheatObject);

      if (!fan && !heating && !cooling && !reheat) {
        return changed;
      }

      const auto baseName = thisObject.nameString();
      auto inletNode = resolvedOrCreatedNodeTarget(inletPort(), baseName + " Air Inlet Node");
      auto outletNode = resolvedOrCreatedNodeTarget(outletPort(), baseName + " Air Outlet Node");
      trackNodeChange(setPointer(inletPort(), inletNode.handle(), false));
      trackNodeChange(setPointer(outletPort(), outletNode.handle(), false));

      std::vector<HVACComponent> orderedComponents;
      const bool blowThrough = openstudio::istringEqual(fanPlacement(), "BlowThrough");
      if (blowThrough) {
        if (fan) {
          orderedComponents.emplace_back(fan->cast<HVACComponent>());
        }
        if (cooling) {
          orderedComponents.emplace_back(*cooling);
        }
        if (heating) {
          orderedComponents.emplace_back(*heating);
        }
      } else {
        if (cooling) {
          orderedComponents.emplace_back(*cooling);
        }
        if (heating) {
          orderedComponents.emplace_back(*heating);
        }
        if (fan) {
          orderedComponents.emplace_back(fan->cast<HVACComponent>());
        }
      }
      if (reheat) {
        orderedComponents.emplace_back(*reheat);
      }

      auto connectorName = [&](const HVACComponent& component) {
        if (fan && (component.handle() == fan->handle())) {
          return baseName + " Fan Outlet Node";
        }
        if (cooling && (component.handle() == cooling->handle())) {
          return baseName + " Cooling Coil Outlet Node";
        }
        if (heating && (component.handle() == heating->handle())) {
          return baseName + " Heating Coil Outlet Node";
        }
        return component.nameString() + " Outlet Node";
      };

      Node upstreamNode = inletNode;
      for (std::size_t i = 0; i < orderedComponents.size(); ++i) {
        auto component = orderedComponents[i];
        const auto componentInletPort = unitaryHeatCoolAirInletPort(component);
        const auto componentOutletPort = unitaryHeatCoolAirOutletPort(component);
        if ((componentInletPort == 0u) || (componentOutletPort == 0u)) {
          continue;
        }

        trackNodeChange(component.getImpl<detail::ModelObject_Impl>()->setPointer(componentInletPort, upstreamNode.handle(), false));
        Node downstreamNode = outletNode;
        if ((i + 1u) < orderedComponents.size()) {
          auto downstream = orderedComponents[i + 1u];
          boost::optional<Node> connectorNode;
          if (allowChildNodeRecovery) {
            if (auto currentOutlet = component.getImpl<detail::ModelObject_Impl>()->resolvedNodeTarget(componentOutletPort)) {
              const auto downstreamInletPort = unitaryHeatCoolAirInletPort(downstream);
              if (auto downstreamInlet = downstream.getImpl<detail::ModelObject_Impl>()->resolvedNodeTarget(downstreamInletPort)) {
                if ((*currentOutlet == *downstreamInlet) && (*currentOutlet != inletNode) && (*currentOutlet != outletNode)) {
                  connectorNode = currentOutlet;
                }
              }
            }
          }
          if (!connectorNode) {
            connectorNode = model().getOrCreateTransientByName<Node>(connectorName(component));
          }
          downstreamNode = *connectorNode;
          trackNodeChange(
            downstream.getImpl<detail::ModelObject_Impl>()->setPointer(unitaryHeatCoolAirInletPort(downstream), connectorNode->handle(), false));
        }
        trackNodeChange(component.getImpl<detail::ModelObject_Impl>()->setPointer(componentOutletPort, downstreamNode.handle(), false));
        upstreamNode = downstreamNode;
      }

      if (nodeWiringChanged && context) {
        detail::addLoadInfo(*context, "Reconciled internal node wiring for AirLoopHVAC:UnitaryHeatCool '" + baseName + "'.");
      }
      return changed;
    }

    std::vector<std::string> AirLoopHVACUnitaryHeatCool_Impl::supplyFanObjectTypeValues() const {
      return openstudio::epmodel::AirLoopHVACUnitaryHeatCool::supplyFanObjectTypeValues();
    }

    std::vector<std::string> AirLoopHVACUnitaryHeatCool_Impl::fanPlacementValues() const {
      return openstudio::epmodel::AirLoopHVACUnitaryHeatCool::fanPlacementValues();
    }

    std::vector<std::string> AirLoopHVACUnitaryHeatCool_Impl::heatingCoilObjectTypeValues() const {
      return openstudio::epmodel::AirLoopHVACUnitaryHeatCool::heatingCoilObjectTypeValues();
    }

    std::vector<std::string> AirLoopHVACUnitaryHeatCool_Impl::coolingCoilObjectTypeValues() const {
      return openstudio::epmodel::AirLoopHVACUnitaryHeatCool::coolingCoilObjectTypeValues();
    }

    std::vector<std::string> AirLoopHVACUnitaryHeatCool_Impl::dehumidificationControlTypeValues() const {
      return openstudio::epmodel::AirLoopHVACUnitaryHeatCool::dehumidificationControlTypeValues();
    }

    std::vector<std::string> AirLoopHVACUnitaryHeatCool_Impl::reheatCoilObjectTypeValues() const {
      return openstudio::epmodel::AirLoopHVACUnitaryHeatCool::reheatCoilObjectTypeValues();
    }

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
