/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "StraightComponent/AirTerminalSingleDuctConstantVolumeReheat.hpp"
#include "StraightComponent/AirTerminalSingleDuctConstantVolumeReheat_Impl.hpp"

#include "HVACComponent/ThermalZone.hpp"
#include "HVACComponent/ThermalZone_Impl.hpp"
#include "HVACComponent.hpp"
#include "Loop/PlantLoop.hpp"
#include "Loop/PlantLoop_Impl.hpp"
#include "Model.hpp"
#include "ModelObject.hpp"
#include "ModelObject/ModelObject_Impl.hpp"
#include "ModelObject/ZoneHVACAirDistributionUnit.hpp"
#include "ModelObject/ZoneHVACAirDistributionUnit_Impl.hpp"
#include "Node.hpp"
#include "Schedule/Schedule.hpp"
#include "Schedule/Schedule_Impl.hpp"
#include "StraightComponent/SingleDuctTerminalInsertionPlan.hpp"
#include "StraightComponent/SingleDuctTerminalRemovalPlan.hpp"
#include "StraightComponent/StraightComponent.hpp"
#include "WaterToAirComponent/CoilHeatingWater.hpp"
#include "WaterToAirComponent/CoilHeatingWater_Impl.hpp"

#include <algorithm>
#include <utilities/core/Assert.hpp>
#include <utilities/core/Logger.hpp>
#include <utilities/core/StringHelpers.hpp>
#include <utilities/core/UUID.hpp>
#include <utilities/idd/AirTerminal_SingleDuct_ConstantVolume_Reheat_FieldEnums.hxx>
#include <utilities/idd/Coil_Heating_Electric_FieldEnums.hxx>
#include <utilities/idd/Coil_Heating_Fuel_FieldEnums.hxx>
#include <utilities/idd/Coil_Heating_Water_FieldEnums.hxx>
#include <utilities/idd/IddEnums.hxx>
#include <utilities/idf/WorkspaceObject_Impl.hpp>

namespace openstudio {
namespace epmodel {

  namespace {

    void assertSuccessfulMutation(bool result) {
      OS_ASSERT(result);
      (void)result;
    }

    void applyConstructorDefaults(AirTerminalSingleDuctConstantVolumeReheat& terminal) {
      terminal.autosizeMaximumAirFlowRate();
      terminal.autosizeMaximumHotWaterorSteamFlowRate();
      assertSuccessfulMutation(terminal.setMinimumHotWaterorSteamFlowRate(0.0));
      assertSuccessfulMutation(terminal.setConvergenceTolerance(0.001));
      assertSuccessfulMutation(terminal.setMaximumReheatAirTemperature(35.0));
    }

    boost::optional<ThermalZone> thermalZoneContainingTerminal(const Model& model, const ModelObject& terminal) {
      for (const auto& zone : model.getConcreteModelObjects<ThermalZone>()) {
        const auto equipment = zone.equipment();
        if (std::ranges::find(equipment, terminal) != equipment.end()) {
          return zone;
        }
      }
      return boost::none;
    }

    struct ReheatCoilAirFields
    {
      unsigned inlet;
      unsigned outlet;
    };

    boost::optional<ReheatCoilAirFields> reheatCoilAirFields(const HVACComponent& coil) {
      switch (coil.iddObject().type().value()) {
        case IddObjectType::Coil_Heating_Fuel:
          return ReheatCoilAirFields{openstudio::Coil_Heating_FuelFields::AirInletNodeName, openstudio::Coil_Heating_FuelFields::AirOutletNodeName};
        case IddObjectType::Coil_Heating_Electric:
          return ReheatCoilAirFields{openstudio::Coil_Heating_ElectricFields::AirInletNodeName,
                                     openstudio::Coil_Heating_ElectricFields::AirOutletNodeName};
        case IddObjectType::Coil_Heating_Water:
          return ReheatCoilAirFields{openstudio::Coil_Heating_WaterFields::AirInletNodeName, openstudio::Coil_Heating_WaterFields::AirOutletNodeName};
        default:
          return boost::none;
      }
    }

    struct ExistingNodeField
    {
      bool set = false;
      boost::optional<Node> node;
    };

    ExistingNodeField existingNodeField(const ModelObject& object, unsigned field) {
      ExistingNodeField result;
      const auto managedValue = object.getField(field, false);
      auto workspaceImpl = object.getImpl<openstudio::detail::WorkspaceObject_Impl>();
      OS_ASSERT(workspaceImpl);
      const auto rawValue = workspaceImpl->openstudio::detail::IdfObject_Impl::getString(field, false, true);
      if ((!managedValue || managedValue->empty()) && (!rawValue || rawValue->empty())) {
        return result;
      }

      result.set = true;
      if (!managedValue || managedValue->empty()) {
        return result;
      }
      const auto targetHandle = toUUID(*managedValue);
      if (targetHandle.isNull()) {
        return result;
      }
      if (auto target = object.model().getObject(targetHandle)) {
        result.node = target->optionalCast<Node>();
      }
      return result;
    }

    // Constant-volume reheat projects its contained coil directly across the
    // terminal inlet and outlet. Detaching the terminal therefore clears both
    // coil air ports; there is no retained intermediate node as there is for a
    // VAV reheat terminal.
    class ConstantVolumeReheatAirPathRemovalPlan
    {
     public:
      static std::unique_ptr<ConstantVolumeReheatAirPathRemovalPlan> prepare(const ModelObject& terminal, const HVACComponent& coil) {
        if (terminal.model() != coil.model()) {
          return nullptr;
        }

        const auto coilFields = reheatCoilAirFields(coil);
        if (!coilFields) {
          return nullptr;
        }
        const auto coilType = terminal.getString(openstudio::AirTerminal_SingleDuct_ConstantVolume_ReheatFields::ReheatCoilObjectType, false, true);
        const auto owner = coil.containingHVACComponent();
        if (!coilType || !openstudio::istringEqual(*coilType, coil.iddObject().name()) || !owner || owner->handle() != terminal.handle()) {
          return nullptr;
        }

        const auto terminalComponent = terminal.cast<StraightComponent>();
        const auto coilObject = coil.cast<ModelObject>();
        const auto terminalInlet = existingNodeField(terminal, terminalComponent.inletPort());
        const auto terminalOutlet = existingNodeField(terminal, terminalComponent.outletPort());
        const auto coilInlet = existingNodeField(coilObject, coilFields->inlet);
        const auto coilOutlet = existingNodeField(coilObject, coilFields->outlet);
        if (terminalInlet.set != terminalOutlet.set || coilInlet.set != coilOutlet.set || terminalInlet.set != coilInlet.set) {
          return nullptr;
        }

        if (terminalInlet.set) {
          if (!terminalInlet.node || !terminalOutlet.node || !coilInlet.node || !coilOutlet.node
              || coilInlet.node->handle() != terminalInlet.node->handle() || coilOutlet.node->handle() != terminalOutlet.node->handle()) {
            return nullptr;
          }
        }

        return std::unique_ptr<ConstantVolumeReheatAirPathRemovalPlan>(
          new ConstantVolumeReheatAirPathRemovalPlan(coilObject, *coilFields, terminalInlet.set));
      }

      bool contributesInletSource() const {
        return m_clearCoilPorts;
      }

      void commit() {
        if (m_clearCoilPorts) {
          auto coilImpl = m_coil.getImpl<detail::ModelObject_Impl>();
          OS_ASSERT(coilImpl);
          assertSuccessfulMutation(coilImpl->setPointer(m_coilFields.inlet, Handle(), false));
          assertSuccessfulMutation(coilImpl->setPointer(m_coilFields.outlet, Handle(), false));
        }
      }

     private:
      ConstantVolumeReheatAirPathRemovalPlan(ModelObject coil, ReheatCoilAirFields coilFields, bool clearCoilPorts)
        : m_coil(std::move(coil)), m_coilFields(coilFields), m_clearCoilPorts(clearCoilPorts) {}

      ModelObject m_coil;
      ReheatCoilAirFields m_coilFields;
      bool m_clearCoilPorts;
    };

    struct ConstantVolumeReheatTopologyRemovalPlans
    {
      std::unique_ptr<ConstantVolumeReheatAirPathRemovalPlan> coilAirPath;
      std::unique_ptr<detail::SingleDuctTerminalRemovalPlan> externalTopology;
    };

    std::unique_ptr<ConstantVolumeReheatTopologyRemovalPlans> prepareConstantVolumeReheatTopologyRemoval(const ModelObject& terminalObject,
                                                                                                         const boost::optional<HVACComponent>& coil) {
      auto result = std::make_unique<ConstantVolumeReheatTopologyRemovalPlans>();
      std::vector<ModelObject> containedInletSources;
      if (coil) {
        result->coilAirPath = ConstantVolumeReheatAirPathRemovalPlan::prepare(terminalObject, *coil);
        if (!result->coilAirPath) {
          return nullptr;
        }
        if (result->coilAirPath->contributesInletSource()) {
          containedInletSources.push_back(coil->cast<ModelObject>());
        }
      }

      auto terminal = terminalObject.cast<StraightComponent>();
      if (detail::SingleDuctTerminalRemovalPlan::hasTopology(terminal)) {
        result->externalTopology = detail::SingleDuctTerminalRemovalPlan::prepare(terminal, containedInletSources);
        if (!result->externalTopology) {
          return nullptr;
        }
      }
      return result;
    }

  }  // namespace

  AirTerminalSingleDuctConstantVolumeReheat::AirTerminalSingleDuctConstantVolumeReheat(const Model& model)
    : StraightComponent(AirTerminalSingleDuctConstantVolumeReheat::iddObjectType(), model) {
    auto impl = getImpl<detail::AirTerminalSingleDuctConstantVolumeReheat_Impl>();
    OS_ASSERT(impl);
    detail::LoadContext context{const_cast<Model&>(model), SanitizationPolicy::Repair, SanitizationReport{}, {}};  // NOLINT
    impl->canonicalize(context);

    auto alwaysOn = model.alwaysOnDiscreteSchedule();
    assertSuccessfulMutation(setAvailabilitySchedule(alwaysOn));
    applyConstructorDefaults(*this);
  }

  AirTerminalSingleDuctConstantVolumeReheat::AirTerminalSingleDuctConstantVolumeReheat(const Model& model, Schedule& availabilitySchedule,
                                                                                       HVACComponent& reheatCoil)
    : StraightComponent(AirTerminalSingleDuctConstantVolumeReheat::iddObjectType(), model) {
    auto impl = getImpl<detail::AirTerminalSingleDuctConstantVolumeReheat_Impl>();
    OS_ASSERT(impl);
    detail::LoadContext context{const_cast<Model&>(model), SanitizationPolicy::Repair, SanitizationReport{}, {}};  // NOLINT
    impl->canonicalize(context);

    assertSuccessfulMutation(setAvailabilitySchedule(availabilitySchedule));
    assertSuccessfulMutation(setReheatCoil(reheatCoil));
    applyConstructorDefaults(*this);
  }

  AirTerminalSingleDuctConstantVolumeReheat::AirTerminalSingleDuctConstantVolumeReheat(
    std::shared_ptr<detail::AirTerminalSingleDuctConstantVolumeReheat_Impl> impl)
    : StraightComponent(std::move(impl)) {}

  IddObjectType AirTerminalSingleDuctConstantVolumeReheat::iddObjectType() {
    return IddObjectType::AirTerminal_SingleDuct_ConstantVolume_Reheat;
  }

  bool AirTerminalSingleDuctConstantVolumeReheat::addToNode(Node& node) {
    return getImpl<detail::AirTerminalSingleDuctConstantVolumeReheat_Impl>()->addToNode(node);
  }

  Schedule AirTerminalSingleDuctConstantVolumeReheat::availabilitySchedule() const {
    return getImpl<detail::AirTerminalSingleDuctConstantVolumeReheat_Impl>()->availabilitySchedule();
  }

  bool AirTerminalSingleDuctConstantVolumeReheat::setAvailabilitySchedule(Schedule& schedule) {
    return getImpl<detail::AirTerminalSingleDuctConstantVolumeReheat_Impl>()->setAvailabilitySchedule(schedule);
  }

  HVACComponent AirTerminalSingleDuctConstantVolumeReheat::reheatCoil() const {
    return getImpl<detail::AirTerminalSingleDuctConstantVolumeReheat_Impl>()->reheatCoil();
  }

  bool AirTerminalSingleDuctConstantVolumeReheat::setReheatCoil(const HVACComponent& coil) {
    return getImpl<detail::AirTerminalSingleDuctConstantVolumeReheat_Impl>()->setReheatCoil(coil);
  }

  void AirTerminalSingleDuctConstantVolumeReheat::resetReheatCoil() {
    getImpl<detail::AirTerminalSingleDuctConstantVolumeReheat_Impl>()->resetReheatCoil();
  }

  boost::optional<double> AirTerminalSingleDuctConstantVolumeReheat::maximumAirFlowRate() const {
    return getImpl<detail::AirTerminalSingleDuctConstantVolumeReheat_Impl>()->maximumAirFlowRate();
  }

  bool AirTerminalSingleDuctConstantVolumeReheat::isMaximumAirFlowRateAutosized() const {
    return getImpl<detail::AirTerminalSingleDuctConstantVolumeReheat_Impl>()->isMaximumAirFlowRateAutosized();
  }

  bool AirTerminalSingleDuctConstantVolumeReheat::setMaximumAirFlowRate(double maximumAirFlowRate) {
    return getImpl<detail::AirTerminalSingleDuctConstantVolumeReheat_Impl>()->setMaximumAirFlowRate(maximumAirFlowRate);
  }

  void AirTerminalSingleDuctConstantVolumeReheat::resetMaximumAirFlowRate() {
    getImpl<detail::AirTerminalSingleDuctConstantVolumeReheat_Impl>()->resetMaximumAirFlowRate();
  }

  void AirTerminalSingleDuctConstantVolumeReheat::autosizeMaximumAirFlowRate() {
    getImpl<detail::AirTerminalSingleDuctConstantVolumeReheat_Impl>()->autosizeMaximumAirFlowRate();
  }

  boost::optional<double> AirTerminalSingleDuctConstantVolumeReheat::maximumHotWaterorSteamFlowRate() const {
    return getImpl<detail::AirTerminalSingleDuctConstantVolumeReheat_Impl>()->maximumHotWaterorSteamFlowRate();
  }

  bool AirTerminalSingleDuctConstantVolumeReheat::isMaximumHotWaterorSteamFlowRateAutosized() const {
    return getImpl<detail::AirTerminalSingleDuctConstantVolumeReheat_Impl>()->isMaximumHotWaterorSteamFlowRateAutosized();
  }

  bool AirTerminalSingleDuctConstantVolumeReheat::setMaximumHotWaterorSteamFlowRate(double maximumHotWaterorSteamFlowRate) {
    return getImpl<detail::AirTerminalSingleDuctConstantVolumeReheat_Impl>()->setMaximumHotWaterorSteamFlowRate(maximumHotWaterorSteamFlowRate);
  }

  void AirTerminalSingleDuctConstantVolumeReheat::resetMaximumHotWaterorSteamFlowRate() {
    getImpl<detail::AirTerminalSingleDuctConstantVolumeReheat_Impl>()->resetMaximumHotWaterorSteamFlowRate();
  }

  void AirTerminalSingleDuctConstantVolumeReheat::autosizeMaximumHotWaterorSteamFlowRate() {
    getImpl<detail::AirTerminalSingleDuctConstantVolumeReheat_Impl>()->autosizeMaximumHotWaterorSteamFlowRate();
  }

  double AirTerminalSingleDuctConstantVolumeReheat::minimumHotWaterorSteamFlowRate() const {
    return getImpl<detail::AirTerminalSingleDuctConstantVolumeReheat_Impl>()->minimumHotWaterorSteamFlowRate();
  }

  bool AirTerminalSingleDuctConstantVolumeReheat::isMinimumHotWaterorSteamFlowRateDefaulted() const {
    return getImpl<detail::AirTerminalSingleDuctConstantVolumeReheat_Impl>()->isMinimumHotWaterorSteamFlowRateDefaulted();
  }

  bool AirTerminalSingleDuctConstantVolumeReheat::setMinimumHotWaterorSteamFlowRate(double minimumHotWaterorSteamFlowRate) {
    return getImpl<detail::AirTerminalSingleDuctConstantVolumeReheat_Impl>()->setMinimumHotWaterorSteamFlowRate(minimumHotWaterorSteamFlowRate);
  }

  void AirTerminalSingleDuctConstantVolumeReheat::resetMinimumHotWaterorSteamFlowRate() {
    getImpl<detail::AirTerminalSingleDuctConstantVolumeReheat_Impl>()->resetMinimumHotWaterorSteamFlowRate();
  }

  double AirTerminalSingleDuctConstantVolumeReheat::convergenceTolerance() const {
    return getImpl<detail::AirTerminalSingleDuctConstantVolumeReheat_Impl>()->convergenceTolerance();
  }

  bool AirTerminalSingleDuctConstantVolumeReheat::isConvergenceToleranceDefaulted() const {
    return getImpl<detail::AirTerminalSingleDuctConstantVolumeReheat_Impl>()->isConvergenceToleranceDefaulted();
  }

  bool AirTerminalSingleDuctConstantVolumeReheat::setConvergenceTolerance(double convergenceTolerance) {
    return getImpl<detail::AirTerminalSingleDuctConstantVolumeReheat_Impl>()->setConvergenceTolerance(convergenceTolerance);
  }

  void AirTerminalSingleDuctConstantVolumeReheat::resetConvergenceTolerance() {
    getImpl<detail::AirTerminalSingleDuctConstantVolumeReheat_Impl>()->resetConvergenceTolerance();
  }

  double AirTerminalSingleDuctConstantVolumeReheat::maximumReheatAirTemperature() const {
    return getImpl<detail::AirTerminalSingleDuctConstantVolumeReheat_Impl>()->maximumReheatAirTemperature();
  }

  bool AirTerminalSingleDuctConstantVolumeReheat::isMaximumReheatAirTemperatureDefaulted() const {
    return getImpl<detail::AirTerminalSingleDuctConstantVolumeReheat_Impl>()->isMaximumReheatAirTemperatureDefaulted();
  }

  bool AirTerminalSingleDuctConstantVolumeReheat::setMaximumReheatAirTemperature(double maximumReheatAirTemperature) {
    return getImpl<detail::AirTerminalSingleDuctConstantVolumeReheat_Impl>()->setMaximumReheatAirTemperature(maximumReheatAirTemperature);
  }

  void AirTerminalSingleDuctConstantVolumeReheat::resetMaximumReheatAirTemperature() {
    getImpl<detail::AirTerminalSingleDuctConstantVolumeReheat_Impl>()->resetMaximumReheatAirTemperature();
  }

  unsigned detail::AirTerminalSingleDuctConstantVolumeReheat_Impl::inletPort() const {
    return openstudio::AirTerminal_SingleDuct_ConstantVolume_ReheatFields::AirInletNodeName;
  }

  unsigned detail::AirTerminalSingleDuctConstantVolumeReheat_Impl::outletPort() const {
    return openstudio::AirTerminal_SingleDuct_ConstantVolume_ReheatFields::AirOutletNodeName;
  }

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
  namespace detail {

    boost::optional<ZoneHVACAirDistributionUnit> AirTerminalSingleDuctConstantVolumeReheat_Impl::zoneHVACAirDistributionUnit() const {
      auto terminal = getObject<openstudio::epmodel::ModelObject>();
      for (const auto& source : terminal.getSources(openstudio::IddObjectType::ZoneHVAC_AirDistributionUnit)) {
        if (auto adu = source.optionalCast<openstudio::epmodel::ZoneHVACAirDistributionUnit>()) {
          return adu;
        }
      }
      return boost::none;
    }

    std::vector<ModelObject> AirTerminalSingleDuctConstantVolumeReheat_Impl::children() const {
      std::vector<ModelObject> result;
      auto coil =
        getObject<ModelObject>().getModelObjectTarget<HVACComponent>(openstudio::AirTerminal_SingleDuct_ConstantVolume_ReheatFields::ReheatCoilName);
      if (coil) {
        result.push_back(*coil);
      }
      return result;
    }

    bool AirTerminalSingleDuctConstantVolumeReheat_Impl::isRemovable() const {
      if (!HVACComponent_Impl::isRemovable()) {
        return false;
      }

      auto terminalObject = getObject<ModelObject>();
      auto terminal = terminalObject.cast<StraightComponent>();
      const auto coil =
        terminalObject.getModelObjectTarget<HVACComponent>(openstudio::AirTerminal_SingleDuct_ConstantVolume_ReheatFields::ReheatCoilName);
      const bool hasExternalTopology = SingleDuctTerminalRemovalPlan::hasTopology(terminal);
      const bool hasPlantTopology = coil && coil->plantLoop();
      if (!hasExternalTopology && !hasPlantTopology) {
        return true;
      }

      if (!prepareConstantVolumeReheatTopologyRemoval(terminalObject, coil)) {
        return false;
      }

      if (coil) {
        if (auto waterCoil = coil->optionalCast<CoilHeatingWater>()) {
          if (auto plantLoop = waterCoil->plantLoop()) {
            auto plantLoopImpl = plantLoop->getImpl<PlantLoop_Impl>();
            OS_ASSERT(plantLoopImpl);
            return static_cast<bool>(plantLoopImpl->prepareCoilHeatingWaterDemandBranchRemoval(*waterCoil));
          }
        } else if (coil->plantLoop()) {
          return false;
        }
      }
      return true;
    }

    std::vector<openstudio::IdfObject> AirTerminalSingleDuctConstantVolumeReheat_Impl::remove() {
      auto thisObject = getObject<openstudio::epmodel::ModelObject>();
      auto ownedChildren = children();
      auto terminal = thisObject.cast<StraightComponent>();
      const bool hadTopology = SingleDuctTerminalRemovalPlan::hasTopology(terminal);
      bool childHadPlantTopology = false;
      for (const auto& child : ownedChildren) {
        if (auto component = child.optionalCast<openstudio::epmodel::HVACComponent>(); component && component->plantLoop()) {
          childHadPlantTopology = true;
          break;
        }
      }

      if ((hadTopology || childHadPlantTopology) && !removeFromLoop()) {
        return {};
      }

      auto result = HVACComponent_Impl::remove();
      if (result.empty()) {
        return result;
      }

      for (auto& child : ownedChildren) {
        auto removedChild = child.remove();
        result.insert(result.end(), removedChild.begin(), removedChild.end());
      }
      return result;
    }

    bool AirTerminalSingleDuctConstantVolumeReheat_Impl::removeFromLoop() {
      auto thisObject = getObject<openstudio::epmodel::ModelObject>();
      auto coil = thisObject.getModelObjectTarget<openstudio::epmodel::HVACComponent>(
        openstudio::AirTerminal_SingleDuct_ConstantVolume_ReheatFields::ReheatCoilName);

      auto topologyRemovalPlans = prepareConstantVolumeReheatTopologyRemoval(thisObject, coil);
      if (!topologyRemovalPlans) {
        return false;
      }

      std::unique_ptr<PlantLoop_Impl::CoilHeatingWaterDemandBranchRemovalPlan> plantRemovalPlan;
      if (coil) {
        if (auto waterCoil = coil->optionalCast<CoilHeatingWater>()) {
          if (auto plantLoop = waterCoil->plantLoop()) {
            auto plantLoopImpl = plantLoop->getImpl<PlantLoop_Impl>();
            OS_ASSERT(plantLoopImpl);
            plantRemovalPlan = plantLoopImpl->prepareCoilHeatingWaterDemandBranchRemoval(*waterCoil);
            if (!plantRemovalPlan) {
              return false;
            }
          }
        } else if (coil->plantLoop()) {
          return false;
        }
      }

      if (!topologyRemovalPlans->externalTopology && !plantRemovalPlan) {
        return false;
      }

      // Controller cleanup needs the intact air projection. Once the plant
      // branch is gone, clear the coil projection before the shared terminal
      // plan removes the now-unreferenced branch inlet node.
      if (plantRemovalPlan) {
        plantRemovalPlan->commit();
      }
      if (topologyRemovalPlans->coilAirPath) {
        topologyRemovalPlans->coilAirPath->commit();
      }
      if (topologyRemovalPlans->externalTopology) {
        topologyRemovalPlans->externalTopology->commit();
      }

      return true;
    }

    bool AirTerminalSingleDuctConstantVolumeReheat_Impl::addToNode(Node& node) {
      if (node.model() != model()) {
        return false;
      }

      auto thisObject = getObject<openstudio::epmodel::ModelObject>();
      if (!thisObject.getModelObjectTarget<HVACComponent>(openstudio::AirTerminal_SingleDuct_ConstantVolume_ReheatFields::ReheatCoilName)) {
        LOG_FREE(Warn, "openstudio.epmodel.AirTerminalSingleDuctConstantVolumeReheat",
                 "Refusing to connect a terminal without its required reheat coil.");
        return false;
      }

      auto terminal = thisObject.cast<StraightComponent>();
      auto plan = SingleDuctTerminalInsertionPlan::prepare(terminal, node);
      if (!plan) {
        LOG_FREE(Warn, "openstudio.epmodel.AirTerminalSingleDuctConstantVolumeReheat",
                 "addToNode requires a terminal-free effective demand branch on the target AirLoopHVAC.");
        return false;
      }

      if (!plan->apply()) {
        return false;
      }
      if (!maintainContainedAirPath()) {
        plan.reset();
        OS_ASSERT(maintainContainedAirPath());
        return false;
      }
      plan->commit();
      return true;
    }

    Schedule AirTerminalSingleDuctConstantVolumeReheat_Impl::availabilitySchedule() const {
      auto schedule = getObject<ModelObject>().getModelObjectTarget<Schedule>(
        openstudio::AirTerminal_SingleDuct_ConstantVolume_ReheatFields::AvailabilityScheduleName);
      if (!schedule) {
        LOG_FREE(Error, "openstudio.epmodel.AirTerminalSingleDuctConstantVolumeReheat",
                 "Required availability schedule not set, repairing persisted state with the model always-on discrete schedule");
        schedule = model().alwaysOnDiscreteSchedule();
        const bool ok = const_cast<AirTerminalSingleDuctConstantVolumeReheat_Impl*>(this)->setAvailabilitySchedule(*schedule);
        OS_ASSERT(ok);
        schedule = getObject<ModelObject>().getModelObjectTarget<Schedule>(
          openstudio::AirTerminal_SingleDuct_ConstantVolume_ReheatFields::AvailabilityScheduleName);
      }
      OS_ASSERT(schedule);
      return *schedule;
    }

    bool AirTerminalSingleDuctConstantVolumeReheat_Impl::setAvailabilitySchedule(Schedule& schedule) {
      return ModelObject_Impl::setSchedule(openstudio::AirTerminal_SingleDuct_ConstantVolume_ReheatFields::AvailabilityScheduleName,
                                           "AirTerminalSingleDuctConstantVolumeReheat", "Availability", schedule);
    }

    HVACComponent AirTerminalSingleDuctConstantVolumeReheat_Impl::reheatCoil() const {
      auto coil =
        getObject<ModelObject>().getModelObjectTarget<HVACComponent>(openstudio::AirTerminal_SingleDuct_ConstantVolume_ReheatFields::ReheatCoilName);
      OS_ASSERT(coil);
      return *coil;
    }

    bool AirTerminalSingleDuctConstantVolumeReheat_Impl::setReheatCoil(const HVACComponent& coil) {
      if (coil.model() != model()) {
        return false;
      }

      const auto iddObjectType = coil.iddObject().type();
      if ((iddObjectType != IddObjectType::Coil_Heating_Fuel) && (iddObjectType != IddObjectType::Coil_Heating_Electric)
          && (iddObjectType != IddObjectType::Coil_Heating_Water)) {
        LOG_FREE(Warn, "openstudio.epmodel.AirTerminalSingleDuctConstantVolumeReheat",
                 "Unsupported reheat coil type '" << coil.iddObject().name() << "' for AirTerminalSingleDuctConstantVolumeReheat.");
        return false;
      }

      auto terminal = getObject<ModelObject>();
      auto previousCoil =
        terminal.getModelObjectTarget<HVACComponent>(openstudio::AirTerminal_SingleDuct_ConstantVolume_ReheatFields::ReheatCoilName);
      if (previousCoil && previousCoil->handle() == coil.handle()) {
        return maintainContainedAirPath();
      }
      if (auto owner = coil.containingHVACComponent(); owner && owner->handle() != terminal.handle()) {
        return false;
      }
      if (iddObjectType == IddObjectType::Coil_Heating_Electric) {
        if (coil.getTarget(openstudio::Coil_Heating_ElectricFields::AirInletNodeName)
            || coil.getTarget(openstudio::Coil_Heating_ElectricFields::AirOutletNodeName)) {
          return false;
        }
      } else if (iddObjectType == IddObjectType::Coil_Heating_Fuel) {
        if (coil.getTarget(openstudio::Coil_Heating_FuelFields::AirInletNodeName)
            || coil.getTarget(openstudio::Coil_Heating_FuelFields::AirOutletNodeName)) {
          return false;
        }
      } else if (iddObjectType == IddObjectType::Coil_Heating_Water) {
        if (coil.getTarget(openstudio::Coil_Heating_WaterFields::AirInletNodeName)
            || coil.getTarget(openstudio::Coil_Heating_WaterFields::AirOutletNodeName)) {
          return false;
        }
      }

      resetReheatCoil();
      if (!setPointer(openstudio::AirTerminal_SingleDuct_ConstantVolume_ReheatFields::ReheatCoilName, coil.handle(), false)) {
        if (previousCoil) {
          OS_ASSERT(setPointer(openstudio::AirTerminal_SingleDuct_ConstantVolume_ReheatFields::ReheatCoilName, previousCoil->handle(), false));
          OS_ASSERT(maintainContainedAirPath());
        }
        return false;
      }
      if (!maintainContainedAirPath()) {
        resetReheatCoil();
        if (previousCoil) {
          OS_ASSERT(setPointer(openstudio::AirTerminal_SingleDuct_ConstantVolume_ReheatFields::ReheatCoilName, previousCoil->handle(), false));
          OS_ASSERT(maintainContainedAirPath());
        }
        return false;
      }
      return true;
    }

    void AirTerminalSingleDuctConstantVolumeReheat_Impl::resetReheatCoil() {
      if (auto previousCoil = getObject<ModelObject>().getModelObjectTarget<HVACComponent>(
            openstudio::AirTerminal_SingleDuct_ConstantVolume_ReheatFields::ReheatCoilName)) {
        const auto type = previousCoil->iddObject().type();
        if (type == IddObjectType::Coil_Heating_Electric) {
          OS_ASSERT(previousCoil->setPointer(openstudio::Coil_Heating_ElectricFields::AirInletNodeName, Handle()));
          OS_ASSERT(previousCoil->setPointer(openstudio::Coil_Heating_ElectricFields::AirOutletNodeName, Handle()));
        } else if (type == IddObjectType::Coil_Heating_Fuel) {
          OS_ASSERT(previousCoil->setPointer(openstudio::Coil_Heating_FuelFields::AirInletNodeName, Handle()));
          OS_ASSERT(previousCoil->setPointer(openstudio::Coil_Heating_FuelFields::AirOutletNodeName, Handle()));
        } else if (type == IddObjectType::Coil_Heating_Water) {
          OS_ASSERT(previousCoil->setPointer(openstudio::Coil_Heating_WaterFields::AirInletNodeName, Handle()));
          OS_ASSERT(previousCoil->setPointer(openstudio::Coil_Heating_WaterFields::AirOutletNodeName, Handle()));
        }
      }
      OS_ASSERT(setString(openstudio::AirTerminal_SingleDuct_ConstantVolume_ReheatFields::ReheatCoilObjectType, ""));
      OS_ASSERT(setString(openstudio::AirTerminal_SingleDuct_ConstantVolume_ReheatFields::ReheatCoilName, ""));
    }

    void AirTerminalSingleDuctConstantVolumeReheat_Impl::doCanonicalize(LoadContext& context) {
      if (!repairContainedAirPath(context)) {
        detail::addLoadError(context, "Failed to repair contained air path for AirTerminal:SingleDuct:ConstantVolume:Reheat '"
                                        + getObject<ModelObject>().nameString() + "'.");
      }
    }

    bool AirTerminalSingleDuctConstantVolumeReheat_Impl::maintainContainedAirPath() {
      return reconcileContainedAirPath(nullptr);
    }

    bool AirTerminalSingleDuctConstantVolumeReheat_Impl::repairContainedAirPath(LoadContext& context) {
      return reconcileContainedAirPath(&context);
    }

    bool AirTerminalSingleDuctConstantVolumeReheat_Impl::reconcileContainedAirPath(LoadContext* context) {
      auto terminal = getObject<ModelObject>();
      auto coil = terminal.getModelObjectTarget<HVACComponent>(openstudio::AirTerminal_SingleDuct_ConstantVolume_ReheatFields::ReheatCoilName);
      if (coil && context) {
        const auto type = coil->iddObject().type();
        const bool supported =
          (type == IddObjectType::Coil_Heating_Electric) || (type == IddObjectType::Coil_Heating_Fuel) || (type == IddObjectType::Coil_Heating_Water);
        const auto owner = coil->containingHVACComponent();
        if (!supported || (owner && owner->handle() != terminal.handle())) {
          detail::addLoadWarning(*context, "Dropped " + std::string(supported ? "shared" : "unsupported")
                                             + " reheat-coil reference from AirTerminal:SingleDuct:ConstantVolume:Reheat '" + terminal.nameString()
                                             + "'.");
          OS_ASSERT(setPointer(openstudio::AirTerminal_SingleDuct_ConstantVolume_ReheatFields::ReheatCoilName, Handle(), false));
          coil = boost::none;
        }
      }
      if (!coil) {
        const auto previousName = getString(openstudio::AirTerminal_SingleDuct_ConstantVolume_ReheatFields::ReheatCoilName, false, true).value_or("");
        const auto previousType =
          getString(openstudio::AirTerminal_SingleDuct_ConstantVolume_ReheatFields::ReheatCoilObjectType, false, true).value_or("");
        const bool hadExternalTopology = static_cast<bool>(inletModelObject()) || static_cast<bool>(outletModelObject())
                                         || static_cast<bool>(thermalZoneContainingTerminal(model(), terminal))
                                         || static_cast<bool>(zoneHVACAirDistributionUnit());
        if (context && hadExternalTopology) {
          boost::optional<StraightComponent> staleProjectedCoil;
          boost::optional<Handle> staleCoilInletHandle;
          boost::optional<Handle> staleCoilOutletHandle;
          const auto terminalInlet = inletModelObject();
          const auto terminalOutlet = outletModelObject();
          if (terminalInlet && terminalOutlet && !previousType.empty()) {
            // A lost parent pointer can leave the former child coil projected
            // across the same air nodes. Only canonical repair may detach that
            // exact, otherwise-unowned projection before strict loop removal.
            std::vector<StraightComponent> directBranchComponents;
            for (const auto& source : terminalInlet->sources()) {
              auto candidate = source.optionalCast<StraightComponent>();
              if (!candidate || candidate->iddObject().type() == IddObjectType::Node) {
                continue;
              }
              const auto candidateInlet = candidate->inletModelObject();
              if (candidateInlet && (*candidateInlet == *terminalInlet)) {
                const auto owner = candidate->containingHVACComponent();
                if (!owner || (owner->handle() != terminal.handle())) {
                  directBranchComponents.push_back(*candidate);
                }
              }
            }

            if (directBranchComponents.size() == 2u) {
              bool foundTerminal = false;
              unsigned matchingCoilCount = 0u;
              boost::optional<StraightComponent> matchingCoil;
              for (const auto& candidate : directBranchComponents) {
                if (candidate.handle() == terminal.handle()) {
                  foundTerminal = true;
                  continue;
                }
                const auto candidateType = candidate.iddObject().type();
                const bool supportedType = (candidateType == IddObjectType::Coil_Heating_Electric)
                                           || (candidateType == IddObjectType::Coil_Heating_Fuel)
                                           || (candidateType == IddObjectType::Coil_Heating_Water);
                const auto candidateOutlet = candidate.outletModelObject();
                if (supportedType && openstudio::istringEqual(candidate.iddObject().name(), previousType) && candidateOutlet
                    && (*candidateOutlet == *terminalOutlet) && !candidate.containingHVACComponent() && !candidate.plantLoop()) {
                  matchingCoil = candidate;
                  ++matchingCoilCount;
                }
              }
              if (foundTerminal && (matchingCoilCount == 1u)) {
                staleProjectedCoil = matchingCoil;
                if (staleProjectedCoil) {
                  staleCoilInletHandle = terminalInlet->handle();
                  staleCoilOutletHandle = terminalOutlet->handle();
                }
              }
            }
          }

          if (staleProjectedCoil) {
            const bool inletCleared = staleProjectedCoil->setPointer(staleProjectedCoil->inletPort(), Handle());
            const bool outletCleared = inletCleared && staleProjectedCoil->setPointer(staleProjectedCoil->outletPort(), Handle());
            if (!outletCleared) {
              if (inletCleared && staleCoilInletHandle) {
                (void)staleProjectedCoil->setPointer(staleProjectedCoil->inletPort(), *staleCoilInletHandle);
              }
              detail::addLoadError(*context,
                                   "Could not detach the stale reheat-coil air path from incomplete terminal '" + terminal.nameString() + "'.");
              return false;
            }
          }

          if (!removeFromLoop()) {
            if (staleProjectedCoil && staleCoilInletHandle && staleCoilOutletHandle) {
              (void)staleProjectedCoil->setPointer(staleProjectedCoil->inletPort(), *staleCoilInletHandle);
              (void)staleProjectedCoil->setPointer(staleProjectedCoil->outletPort(), *staleCoilOutletHandle);
            }
            detail::addLoadError(*context, "Could not detach incomplete AirTerminal:SingleDuct:ConstantVolume:Reheat '" + terminal.nameString()
                                             + "' from its external topology.");
            return false;
          }
        }
        OS_ASSERT(setString(openstudio::AirTerminal_SingleDuct_ConstantVolume_ReheatFields::ReheatCoilName, ""));
        OS_ASSERT(setString(openstudio::AirTerminal_SingleDuct_ConstantVolume_ReheatFields::ReheatCoilObjectType, ""));
        OS_ASSERT(setPointer(inletPort(), Handle(), false));
        OS_ASSERT(setPointer(outletPort(), Handle(), false));
        if ((!previousName.empty() || !previousType.empty() || hadExternalTopology) && context) {
          detail::addLoadWarning(*context, "Detached incomplete AirTerminal:SingleDuct:ConstantVolume:Reheat '" + terminal.nameString()
                                             + "' and cleared its unresolved reheat-coil reference.");
        }
        return true;
      }
      const auto coilType = coil->iddObject().type();
      if ((coilType != IddObjectType::Coil_Heating_Electric) && (coilType != IddObjectType::Coil_Heating_Fuel)
          && (coilType != IddObjectType::Coil_Heating_Water)) {
        return false;
      }
      bool changed =
        !terminal.getString(openstudio::AirTerminal_SingleDuct_ConstantVolume_ReheatFields::ReheatCoilObjectType)
        || !openstudio::istringEqual(terminal.getString(openstudio::AirTerminal_SingleDuct_ConstantVolume_ReheatFields::ReheatCoilObjectType).get(),
                                     coil->iddObject().name());
      if (!setString(openstudio::AirTerminal_SingleDuct_ConstantVolume_ReheatFields::ReheatCoilObjectType, coil->iddObject().name())) {
        return false;
      }

      auto inletNode = resolvedNodeTarget(openstudio::AirTerminal_SingleDuct_ConstantVolume_ReheatFields::AirInletNodeName);
      auto outletNode = resolvedNodeTarget(openstudio::AirTerminal_SingleDuct_ConstantVolume_ReheatFields::AirOutletNodeName);
      if (!inletNode || !outletNode) {
        const auto type = coil->iddObject().type();
        if (type == IddObjectType::Coil_Heating_Electric) {
          changed = changed || static_cast<bool>(coil->getTarget(openstudio::Coil_Heating_ElectricFields::AirInletNodeName))
                    || static_cast<bool>(coil->getTarget(openstudio::Coil_Heating_ElectricFields::AirOutletNodeName));
          OS_ASSERT(coil->setPointer(openstudio::Coil_Heating_ElectricFields::AirInletNodeName, Handle()));
          OS_ASSERT(coil->setPointer(openstudio::Coil_Heating_ElectricFields::AirOutletNodeName, Handle()));
        } else if (type == IddObjectType::Coil_Heating_Fuel) {
          changed = changed || static_cast<bool>(coil->getTarget(openstudio::Coil_Heating_FuelFields::AirInletNodeName))
                    || static_cast<bool>(coil->getTarget(openstudio::Coil_Heating_FuelFields::AirOutletNodeName));
          OS_ASSERT(coil->setPointer(openstudio::Coil_Heating_FuelFields::AirInletNodeName, Handle()));
          OS_ASSERT(coil->setPointer(openstudio::Coil_Heating_FuelFields::AirOutletNodeName, Handle()));
        } else if (type == IddObjectType::Coil_Heating_Water) {
          changed = changed || static_cast<bool>(coil->getTarget(openstudio::Coil_Heating_WaterFields::AirInletNodeName))
                    || static_cast<bool>(coil->getTarget(openstudio::Coil_Heating_WaterFields::AirOutletNodeName));
          OS_ASSERT(coil->setPointer(openstudio::Coil_Heating_WaterFields::AirInletNodeName, Handle()));
          OS_ASSERT(coil->setPointer(openstudio::Coil_Heating_WaterFields::AirOutletNodeName, Handle()));
        }
        if (changed && context) {
          detail::addLoadInfo(*context,
                              "Reconciled contained air path for AirTerminal:SingleDuct:ConstantVolume:Reheat '" + terminal.nameString() + "'.");
        }
        return true;
      }

      const auto type = coil->iddObject().type();
      if (type == IddObjectType::Coil_Heating_Electric) {
        const auto previousInlet = coil->getModelObjectTarget<Node>(openstudio::Coil_Heating_ElectricFields::AirInletNodeName);
        const auto previousOutlet = coil->getModelObjectTarget<Node>(openstudio::Coil_Heating_ElectricFields::AirOutletNodeName);
        changed = changed || previousInlet != inletNode || previousOutlet != outletNode;
        const bool result = coil->setPointer(openstudio::Coil_Heating_ElectricFields::AirInletNodeName, inletNode->handle())
                            && coil->setPointer(openstudio::Coil_Heating_ElectricFields::AirOutletNodeName, outletNode->handle());
        for (auto displacedNode : {previousInlet, previousOutlet}) {
          if (result && displacedNode && *displacedNode != *inletNode && *displacedNode != *outletNode && displacedNode->sources().empty()
              && model().getObject(displacedNode->handle())) {
            displacedNode->remove();
          }
        }
        if (result && changed && context) {
          detail::addLoadInfo(*context,
                              "Reconciled contained air path for AirTerminal:SingleDuct:ConstantVolume:Reheat '" + terminal.nameString() + "'.");
        }
        return result;
      }
      if (type == IddObjectType::Coil_Heating_Fuel) {
        const auto previousInlet = coil->getModelObjectTarget<Node>(openstudio::Coil_Heating_FuelFields::AirInletNodeName);
        const auto previousOutlet = coil->getModelObjectTarget<Node>(openstudio::Coil_Heating_FuelFields::AirOutletNodeName);
        changed = changed || previousInlet != inletNode || previousOutlet != outletNode;
        const bool result = coil->setPointer(openstudio::Coil_Heating_FuelFields::AirInletNodeName, inletNode->handle())
                            && coil->setPointer(openstudio::Coil_Heating_FuelFields::AirOutletNodeName, outletNode->handle());
        for (auto displacedNode : {previousInlet, previousOutlet}) {
          if (result && displacedNode && *displacedNode != *inletNode && *displacedNode != *outletNode && displacedNode->sources().empty()
              && model().getObject(displacedNode->handle())) {
            displacedNode->remove();
          }
        }
        if (result && changed && context) {
          detail::addLoadInfo(*context,
                              "Reconciled contained air path for AirTerminal:SingleDuct:ConstantVolume:Reheat '" + terminal.nameString() + "'.");
        }
        return result;
      }
      if (type == IddObjectType::Coil_Heating_Water) {
        const auto previousInlet = coil->getModelObjectTarget<Node>(openstudio::Coil_Heating_WaterFields::AirInletNodeName);
        const auto previousOutlet = coil->getModelObjectTarget<Node>(openstudio::Coil_Heating_WaterFields::AirOutletNodeName);
        changed = changed || previousInlet != inletNode || previousOutlet != outletNode;
        const bool result = coil->setPointer(openstudio::Coil_Heating_WaterFields::AirInletNodeName, inletNode->handle())
                            && coil->setPointer(openstudio::Coil_Heating_WaterFields::AirOutletNodeName, outletNode->handle());
        for (auto displacedNode : {previousInlet, previousOutlet}) {
          if (result && displacedNode && *displacedNode != *inletNode && *displacedNode != *outletNode && displacedNode->sources().empty()
              && model().getObject(displacedNode->handle())) {
            displacedNode->remove();
          }
        }
        if (result && changed && context) {
          detail::addLoadInfo(*context,
                              "Reconciled contained air path for AirTerminal:SingleDuct:ConstantVolume:Reheat '" + terminal.nameString() + "'.");
        }
        return result;
      }
      return false;
    }

    boost::optional<double> AirTerminalSingleDuctConstantVolumeReheat_Impl::maximumAirFlowRate() const {
      return getDouble(openstudio::AirTerminal_SingleDuct_ConstantVolume_ReheatFields::MaximumAirFlowRate, true);
    }

    bool AirTerminalSingleDuctConstantVolumeReheat_Impl::isMaximumAirFlowRateAutosized() const {
      if (auto value = getString(openstudio::AirTerminal_SingleDuct_ConstantVolume_ReheatFields::MaximumAirFlowRate, true)) {
        return openstudio::istringEqual(*value, "autosize");
      }
      return false;
    }

    bool AirTerminalSingleDuctConstantVolumeReheat_Impl::setMaximumAirFlowRate(double maximumAirFlowRate) {
      return setDouble(openstudio::AirTerminal_SingleDuct_ConstantVolume_ReheatFields::MaximumAirFlowRate, maximumAirFlowRate);
    }

    void AirTerminalSingleDuctConstantVolumeReheat_Impl::resetMaximumAirFlowRate() {
      OS_ASSERT(setString(openstudio::AirTerminal_SingleDuct_ConstantVolume_ReheatFields::MaximumAirFlowRate, ""));
    }

    void AirTerminalSingleDuctConstantVolumeReheat_Impl::autosizeMaximumAirFlowRate() {
      const bool result = setString(openstudio::AirTerminal_SingleDuct_ConstantVolume_ReheatFields::MaximumAirFlowRate, "autosize");
      OS_ASSERT(result);
      (void)result;
    }

    boost::optional<double> AirTerminalSingleDuctConstantVolumeReheat_Impl::maximumHotWaterorSteamFlowRate() const {
      return getDouble(openstudio::AirTerminal_SingleDuct_ConstantVolume_ReheatFields::MaximumHotWaterorSteamFlowRate, true);
    }

    bool AirTerminalSingleDuctConstantVolumeReheat_Impl::isMaximumHotWaterorSteamFlowRateAutosized() const {
      if (auto value = getString(openstudio::AirTerminal_SingleDuct_ConstantVolume_ReheatFields::MaximumHotWaterorSteamFlowRate, true)) {
        return openstudio::istringEqual(*value, "autosize");
      }
      return false;
    }

    bool AirTerminalSingleDuctConstantVolumeReheat_Impl::setMaximumHotWaterorSteamFlowRate(double maximumHotWaterorSteamFlowRate) {
      return setDouble(openstudio::AirTerminal_SingleDuct_ConstantVolume_ReheatFields::MaximumHotWaterorSteamFlowRate,
                       maximumHotWaterorSteamFlowRate);
    }

    void AirTerminalSingleDuctConstantVolumeReheat_Impl::resetMaximumHotWaterorSteamFlowRate() {
      OS_ASSERT(setString(openstudio::AirTerminal_SingleDuct_ConstantVolume_ReheatFields::MaximumHotWaterorSteamFlowRate, ""));
    }

    void AirTerminalSingleDuctConstantVolumeReheat_Impl::autosizeMaximumHotWaterorSteamFlowRate() {
      const bool result = setString(openstudio::AirTerminal_SingleDuct_ConstantVolume_ReheatFields::MaximumHotWaterorSteamFlowRate, "autosize");
      OS_ASSERT(result);
      (void)result;
    }

    double AirTerminalSingleDuctConstantVolumeReheat_Impl::minimumHotWaterorSteamFlowRate() const {
      const auto value = getDouble(openstudio::AirTerminal_SingleDuct_ConstantVolume_ReheatFields::MinimumHotWaterorSteamFlowRate, true);
      OS_ASSERT(value);
      return *value;
    }

    bool AirTerminalSingleDuctConstantVolumeReheat_Impl::isMinimumHotWaterorSteamFlowRateDefaulted() const {
      return isEmpty(openstudio::AirTerminal_SingleDuct_ConstantVolume_ReheatFields::MinimumHotWaterorSteamFlowRate);
    }

    bool AirTerminalSingleDuctConstantVolumeReheat_Impl::setMinimumHotWaterorSteamFlowRate(double minimumHotWaterorSteamFlowRate) {
      return setDouble(openstudio::AirTerminal_SingleDuct_ConstantVolume_ReheatFields::MinimumHotWaterorSteamFlowRate,
                       minimumHotWaterorSteamFlowRate);
    }

    void AirTerminalSingleDuctConstantVolumeReheat_Impl::resetMinimumHotWaterorSteamFlowRate() {
      OS_ASSERT(setString(openstudio::AirTerminal_SingleDuct_ConstantVolume_ReheatFields::MinimumHotWaterorSteamFlowRate, ""));
    }

    double AirTerminalSingleDuctConstantVolumeReheat_Impl::convergenceTolerance() const {
      const auto value = getDouble(openstudio::AirTerminal_SingleDuct_ConstantVolume_ReheatFields::ConvergenceTolerance, true);
      OS_ASSERT(value);
      return *value;
    }

    bool AirTerminalSingleDuctConstantVolumeReheat_Impl::isConvergenceToleranceDefaulted() const {
      return isEmpty(openstudio::AirTerminal_SingleDuct_ConstantVolume_ReheatFields::ConvergenceTolerance);
    }

    bool AirTerminalSingleDuctConstantVolumeReheat_Impl::setConvergenceTolerance(double convergenceTolerance) {
      return setDouble(openstudio::AirTerminal_SingleDuct_ConstantVolume_ReheatFields::ConvergenceTolerance, convergenceTolerance);
    }

    void AirTerminalSingleDuctConstantVolumeReheat_Impl::resetConvergenceTolerance() {
      OS_ASSERT(setString(openstudio::AirTerminal_SingleDuct_ConstantVolume_ReheatFields::ConvergenceTolerance, ""));
    }

    double AirTerminalSingleDuctConstantVolumeReheat_Impl::maximumReheatAirTemperature() const {
      const auto value = getDouble(openstudio::AirTerminal_SingleDuct_ConstantVolume_ReheatFields::MaximumReheatAirTemperature, true);
      OS_ASSERT(value);
      return *value;
    }

    bool AirTerminalSingleDuctConstantVolumeReheat_Impl::isMaximumReheatAirTemperatureDefaulted() const {
      return isEmpty(openstudio::AirTerminal_SingleDuct_ConstantVolume_ReheatFields::MaximumReheatAirTemperature);
    }

    bool AirTerminalSingleDuctConstantVolumeReheat_Impl::setMaximumReheatAirTemperature(double maximumReheatAirTemperature) {
      return setDouble(openstudio::AirTerminal_SingleDuct_ConstantVolume_ReheatFields::MaximumReheatAirTemperature, maximumReheatAirTemperature);
    }

    void AirTerminalSingleDuctConstantVolumeReheat_Impl::resetMaximumReheatAirTemperature() {
      OS_ASSERT(setString(openstudio::AirTerminal_SingleDuct_ConstantVolume_ReheatFields::MaximumReheatAirTemperature, ""));
    }

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
