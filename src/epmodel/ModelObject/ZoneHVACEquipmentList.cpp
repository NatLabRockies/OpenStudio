/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "ZoneHVACEquipmentList.hpp"
#include "ZoneHVACEquipmentList_Impl.hpp"

#include "HVACComponent/ThermalZone.hpp"
#include "HVACComponent/ThermalZone_Impl.hpp"
#include "Model.hpp"
#include "ModelObject.hpp"
#include "ModelObject/ZoneHVACAirDistributionUnit.hpp"
#include "ModelObject/ZoneHVACAirDistributionUnit_Impl.hpp"
#include "ModelObject/ZoneHVACEquipmentConnections.hpp"
#include "ModelObject/ZoneHVACEquipmentConnections_Impl.hpp"
#include "Mixer/Mixer.hpp"
#include "Mixer/Mixer_Impl.hpp"
#include "Node.hpp"
#include "Schedule/Schedule.hpp"
#include "Schedule/Schedule_Impl.hpp"
#include "Schedule/ScheduleConstant.hpp"
#include "Schedule/ScheduleConstant_Impl.hpp"
#include "StraightComponent/StraightComponent.hpp"

#include <memory>
#include <optional>
#include <stdexcept>
#include <utilities/core/Assert.hpp>
#include <utilities/core/StringHelpers.hpp>
#include <utilities/idd/IddEnums.hxx>
#include <utilities/idd/IddFactory.hxx>
#include <utilities/idd/ZoneHVAC_AirDistributionUnit_FieldEnums.hxx>
#include <utilities/idd/ZoneHVAC_EquipmentConnections_FieldEnums.hxx>
#include <utilities/idd/ZoneHVAC_EquipmentList_FieldEnums.hxx>
#include <utilities/idf/IdfExtensibleGroup.hpp>
#include <utilities/idf/WorkspaceExtensibleGroup.hpp>

#include <algorithm>

namespace openstudio {
namespace epmodel {

  ZoneHVACEquipmentList::ZoneHVACEquipmentList(const Model& model) : ModelObject(ZoneHVACEquipmentList::iddObjectType(), model) {
    auto impl = getImpl<detail::ZoneHVACEquipmentList_Impl>();
    OS_ASSERT(impl);
    detail::LoadContext context{const_cast<Model&>(model), SanitizationPolicy::Repair, SanitizationReport{}, {}};  // NOLINT
    impl->canonicalize(context);
  }

  ZoneHVACEquipmentList::ZoneHVACEquipmentList(const ThermalZone& thermalZone)
    : ModelObject(ZoneHVACEquipmentList::iddObjectType(), thermalZone.model()) {
    auto impl = getImpl<detail::ZoneHVACEquipmentList_Impl>();
    OS_ASSERT(impl);
    auto zoneModel = thermalZone.model();
    detail::LoadContext context{zoneModel, SanitizationPolicy::Repair, SanitizationReport{}, {}};
    impl->canonicalize(context);

    auto zone = const_cast<ThermalZone&>(thermalZone);  // NOLINT
    auto connections = zone.getImpl<detail::ThermalZone_Impl>()->getZoneHVACEquipmentConnections();
    OS_ASSERT(connections.setPointer(openstudio::ZoneHVAC_EquipmentConnectionsFields::ZoneConditioningEquipmentListName, handle()));
  }

  ZoneHVACEquipmentList::ZoneHVACEquipmentList(std::shared_ptr<detail::ZoneHVACEquipmentList_Impl> impl) : ModelObject(std::move(impl)) {}

  IddObjectType ZoneHVACEquipmentList::iddObjectType() {
    return IddObjectType::ZoneHVAC_EquipmentList;
  }

  std::vector<std::string> ZoneHVACEquipmentList::loadDistributionSchemeValues() {
    return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(), openstudio::ZoneHVAC_EquipmentListFields::LoadDistributionScheme);
  }

  std::vector<std::string> ZoneHVACEquipmentList::validLoadDistributionSchemeValues() {
    return loadDistributionSchemeValues();
  }

  std::string ZoneHVACEquipmentList::loadDistributionScheme() const {
    return getImpl<detail::ZoneHVACEquipmentList_Impl>()->loadDistributionScheme();
  }

  bool ZoneHVACEquipmentList::isLoadDistributionSchemeDefaulted() const {
    return getImpl<detail::ZoneHVACEquipmentList_Impl>()->isLoadDistributionSchemeDefaulted();
  }

  bool ZoneHVACEquipmentList::setLoadDistributionScheme(const std::string& loadDistributionScheme) {
    return getImpl<detail::ZoneHVACEquipmentList_Impl>()->setLoadDistributionScheme(loadDistributionScheme);
  }

  void ZoneHVACEquipmentList::resetLoadDistributionScheme() {
    getImpl<detail::ZoneHVACEquipmentList_Impl>()->resetLoadDistributionScheme();
  }

  bool ZoneHVACEquipmentList::addEquipment(const ModelObject& equipment) {
    return getImpl<detail::ZoneHVACEquipmentList_Impl>()->addEquipment(equipment);
  }

  bool ZoneHVACEquipmentList::removeEquipment(const ModelObject& equipment) {
    return getImpl<detail::ZoneHVACEquipmentList_Impl>()->removeEquipment(equipment);
  }

  bool ZoneHVACEquipmentList::setCoolingPriority(const ModelObject& equipment, unsigned priority) {
    return getImpl<detail::ZoneHVACEquipmentList_Impl>()->setCoolingPriority(equipment, priority);
  }

  bool ZoneHVACEquipmentList::setHeatingPriority(const ModelObject& equipment, unsigned priority) {
    return getImpl<detail::ZoneHVACEquipmentList_Impl>()->setHeatingPriority(equipment, priority);
  }

  std::vector<ModelObject> ZoneHVACEquipmentList::equipment() const {
    return getImpl<detail::ZoneHVACEquipmentList_Impl>()->equipment();
  }

  std::vector<ModelObject> ZoneHVACEquipmentList::equipmentInHeatingOrder() const {
    return getImpl<detail::ZoneHVACEquipmentList_Impl>()->equipmentInHeatingOrder();
  }

  std::vector<ModelObject> ZoneHVACEquipmentList::equipmentInCoolingOrder() const {
    return getImpl<detail::ZoneHVACEquipmentList_Impl>()->equipmentInCoolingOrder();
  }

  ThermalZone ZoneHVACEquipmentList::thermalZone() const {
    return getImpl<detail::ZoneHVACEquipmentList_Impl>()->thermalZone();
  }

  unsigned ZoneHVACEquipmentList::heatingPriority(const ModelObject& equipment) const {
    return getImpl<detail::ZoneHVACEquipmentList_Impl>()->heatingPriority(equipment);
  }

  unsigned ZoneHVACEquipmentList::coolingPriority(const ModelObject& equipment) const {
    return getImpl<detail::ZoneHVACEquipmentList_Impl>()->coolingPriority(equipment);
  }

  boost::optional<double> ZoneHVACEquipmentList::sequentialCoolingFraction(const ModelObject& equipment) const {
    return getImpl<detail::ZoneHVACEquipmentList_Impl>()->sequentialCoolingFraction(equipment);
  }

  boost::optional<Schedule> ZoneHVACEquipmentList::sequentialCoolingFractionSchedule(const ModelObject& equipment) const {
    return getImpl<detail::ZoneHVACEquipmentList_Impl>()->sequentialCoolingFractionSchedule(equipment);
  }

  boost::optional<double> ZoneHVACEquipmentList::sequentialHeatingFraction(const ModelObject& equipment) const {
    return getImpl<detail::ZoneHVACEquipmentList_Impl>()->sequentialHeatingFraction(equipment);
  }

  boost::optional<Schedule> ZoneHVACEquipmentList::sequentialHeatingFractionSchedule(const ModelObject& equipment) const {
    return getImpl<detail::ZoneHVACEquipmentList_Impl>()->sequentialHeatingFractionSchedule(equipment);
  }

  bool ZoneHVACEquipmentList::setSequentialCoolingFraction(const ModelObject& equipment, double fraction) {
    return getImpl<detail::ZoneHVACEquipmentList_Impl>()->setSequentialCoolingFraction(equipment, fraction);
  }

  bool ZoneHVACEquipmentList::setSequentialCoolingFractionSchedule(const ModelObject& equipment, Schedule& schedule) {
    return getImpl<detail::ZoneHVACEquipmentList_Impl>()->setSequentialCoolingFractionSchedule(equipment, schedule);
  }

  bool ZoneHVACEquipmentList::setSequentialHeatingFraction(const ModelObject& equipment, double fraction) {
    return getImpl<detail::ZoneHVACEquipmentList_Impl>()->setSequentialHeatingFraction(equipment, fraction);
  }

  bool ZoneHVACEquipmentList::setSequentialHeatingFractionSchedule(const ModelObject& equipment, Schedule& schedule) {
    return getImpl<detail::ZoneHVACEquipmentList_Impl>()->setSequentialHeatingFractionSchedule(equipment, schedule);
  }

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
  namespace detail {

    namespace {

      boost::optional<openstudio::epmodel::ModelObject> resolveEquipmentTarget(const openstudio::WorkspaceExtensibleGroup& group,
                                                                               const openstudio::epmodel::Model& model) {
        if (auto target = group.getTarget(openstudio::ZoneHVAC_EquipmentListExtensibleFields::ZoneEquipmentName)) {
          if (auto modelObject = target->optionalCast<openstudio::epmodel::ModelObject>()) {
            return *modelObject;
          }
        }

        const auto objectType = group.getString(openstudio::ZoneHVAC_EquipmentListExtensibleFields::ZoneEquipmentObjectType, true);
        const auto name = group.getString(openstudio::ZoneHVAC_EquipmentListExtensibleFields::ZoneEquipmentName, true);
        if (!objectType || objectType->empty() || !name || name->empty()) {
          return boost::none;
        }

        try {
          const auto iddType = openstudio::IddObjectType(*objectType);
          if (auto object = model.getObjectByTypeAndName(iddType, *name)) {
            if (auto modelObject = object->optionalCast<openstudio::epmodel::ModelObject>()) {
              return *modelObject;
            }
          }
        } catch (const std::runtime_error&) {  // NOLINT
          return boost::none;
        }

        return boost::none;
      }

      bool setEquipmentTarget(openstudio::WorkspaceExtensibleGroup& group, const openstudio::epmodel::ModelObject& component) {
        if (group.setPointer(openstudio::ZoneHVAC_EquipmentListExtensibleFields::ZoneEquipmentName, component.handle(), false)) {
          return true;
        }
        return group.setString(openstudio::ZoneHVAC_EquipmentListExtensibleFields::ZoneEquipmentName, component.nameString(), false);
      }

      bool isAirTerminal(const openstudio::epmodel::ModelObject& component) {
        switch (component.iddObject().type().value()) {
          case openstudio::IddObjectType::AirTerminal_DualDuct_ConstantVolume:
          case openstudio::IddObjectType::AirTerminal_DualDuct_VAV:
          case openstudio::IddObjectType::AirTerminal_DualDuct_VAV_OutdoorAir:
          case openstudio::IddObjectType::AirTerminal_SingleDuct_ConstantVolume_CooledBeam:
          case openstudio::IddObjectType::AirTerminal_SingleDuct_ConstantVolume_FourPipeBeam:
          case openstudio::IddObjectType::AirTerminal_SingleDuct_ConstantVolume_FourPipeInduction:
          case openstudio::IddObjectType::AirTerminal_SingleDuct_ConstantVolume_NoReheat:
          case openstudio::IddObjectType::AirTerminal_SingleDuct_ConstantVolume_Reheat:
          case openstudio::IddObjectType::AirTerminal_SingleDuct_Mixer:
          case openstudio::IddObjectType::AirTerminal_SingleDuct_ParallelPIU_Reheat:
          case openstudio::IddObjectType::AirTerminal_SingleDuct_SeriesPIU_Reheat:
          case openstudio::IddObjectType::AirTerminal_SingleDuct_UserDefined:
          case openstudio::IddObjectType::AirTerminal_SingleDuct_VAV_HeatAndCool_NoReheat:
          case openstudio::IddObjectType::AirTerminal_SingleDuct_VAV_HeatAndCool_Reheat:
          case openstudio::IddObjectType::AirTerminal_SingleDuct_VAV_NoReheat:
          case openstudio::IddObjectType::AirTerminal_SingleDuct_VAV_Reheat:
          case openstudio::IddObjectType::AirTerminal_SingleDuct_VAV_Reheat_VariableSpeedFan:
            return true;
          default:
            return false;
        }
      }

      boost::optional<openstudio::epmodel::ModelObject> modelEquipmentObject(const openstudio::epmodel::ModelObject& equipmentListTarget) {
        if (auto airDistributionUnit = equipmentListTarget.optionalCast<openstudio::epmodel::ZoneHVACAirDistributionUnit>()) {
          if (auto terminal = airDistributionUnit->airTerminal()) {
            return *terminal;
          }
          return boost::none;
        }
        return equipmentListTarget;
      }

      boost::optional<openstudio::epmodel::Node> airTerminalOutletNode(const openstudio::epmodel::ModelObject& terminal) {
        boost::optional<openstudio::epmodel::ModelObject> outletObject;
        if (auto component = terminal.optionalCast<openstudio::epmodel::StraightComponent>()) {
          outletObject = component->outletModelObject();
        } else if (auto mixer = terminal.optionalCast<openstudio::epmodel::Mixer>()) {
          outletObject = mixer->outletModelObject();
        }

        if (!outletObject) {
          return boost::none;
        }
        return outletObject->optionalCast<openstudio::epmodel::Node>();
      }

      boost::optional<openstudio::epmodel::ZoneHVACAirDistributionUnit>
        existingAirDistributionUnitForTerminal(const openstudio::epmodel::ModelObject& terminal) {
        for (const auto& source : terminal.getSources(openstudio::IddObjectType::ZoneHVAC_AirDistributionUnit)) {
          if (auto airDistributionUnit = source.optionalCast<openstudio::epmodel::ZoneHVACAirDistributionUnit>()) {
            return *airDistributionUnit;
          }
        }

        return boost::none;
      }

      class EquipmentRegistrationPlan
      {
       public:
        static std::unique_ptr<EquipmentRegistrationPlan> prepare(openstudio::epmodel::ZoneHVACEquipmentList equipmentList,
                                                                  const openstudio::epmodel::ModelObject& component) {
          if (component.model() != equipmentList.model()) {
            return nullptr;
          }

          auto plan = std::unique_ptr<EquipmentRegistrationPlan>(new EquipmentRegistrationPlan(std::move(equipmentList), component));
          if (!plan->prepareTarget()) {
            return nullptr;
          }
          return plan;
        }

        EquipmentRegistrationPlan(const EquipmentRegistrationPlan&) = delete;
        EquipmentRegistrationPlan& operator=(const EquipmentRegistrationPlan&) = delete;
        EquipmentRegistrationPlan(EquipmentRegistrationPlan&&) = delete;
        EquipmentRegistrationPlan& operator=(EquipmentRegistrationPlan&&) = delete;

        ~EquipmentRegistrationPlan() {
          if (m_state == State::Prepared) {
            cleanupPreparedState();
          }
        }

        bool addExtensibleRow() {
          if (m_state != State::Prepared || m_alreadyRegistered || !m_equipmentListTarget) {
            return m_state == State::Prepared && m_alreadyRegistered;
          }

          const unsigned coolingPriority = static_cast<unsigned>(m_equipmentList.equipmentInCoolingOrder().size() + 1u);
          const unsigned heatingPriority = static_cast<unsigned>(m_equipmentList.equipmentInHeatingOrder().size() + 1u);
          auto group = m_equipmentList.pushExtensibleGroup().optionalCast<openstudio::WorkspaceExtensibleGroup>();
          if (!group) {
            return false;
          }
          m_groupIndex = group->groupIndex();

          if (!group->setString(openstudio::ZoneHVAC_EquipmentListExtensibleFields::ZoneEquipmentObjectType,
                                m_equipmentListTarget->iddObject().name(), false)
              || !setEquipmentTarget(*group, *m_equipmentListTarget)) {
            return false;
          }

          return group->setUnsigned(openstudio::ZoneHVAC_EquipmentListExtensibleFields::ZoneEquipmentCoolingSequence, coolingPriority)
                 && group->setUnsigned(openstudio::ZoneHVAC_EquipmentListExtensibleFields::ZoneEquipmentHeatingorNoLoadSequence, heatingPriority);
        }

        bool alreadyRegistered() const {
          return m_alreadyRegistered;
        }

        void commit() {
          OS_ASSERT(m_state == State::Prepared);
          m_state = State::Committed;
        }

       private:
        enum class State
        {
          Prepared,
          Committed,
        };

        EquipmentRegistrationPlan(openstudio::epmodel::ZoneHVACEquipmentList equipmentList, openstudio::epmodel::ModelObject component)
          : m_equipmentList(std::move(equipmentList)), m_component(std::move(component)) {}

        bool prepareTarget() {
          const auto currentEquipment = m_equipmentList.equipment();
          m_alreadyRegistered = std::ranges::find(currentEquipment, m_component) != currentEquipment.end();

          if (!isAirTerminal(m_component)) {
            m_equipmentListTarget = m_component;
            return true;
          }

          m_airDistributionUnit = existingAirDistributionUnitForTerminal(m_component);
          if (!m_airDistributionUnit) {
            m_airDistributionUnit = openstudio::epmodel::ZoneHVACAirDistributionUnit(m_component.model());
            m_createdAirDistributionUnit = true;
            if (!m_component.nameString().empty()) {
              m_airDistributionUnit->setName(m_component.nameString() + " Air Distribution Unit");
            }

            auto airDistributionUnitImpl = m_airDistributionUnit->getImpl<openstudio::epmodel::detail::ZoneHVACAirDistributionUnit_Impl>();
            OS_ASSERT(airDistributionUnitImpl);
            if (!airDistributionUnitImpl->setAirTerminal(m_component)) {
              return false;
            }
          } else {
            const auto outletField = openstudio::ZoneHVAC_AirDistributionUnitFields::AirDistributionUnitOutletNodeName;
            if (auto managedField = m_airDistributionUnit->getField(outletField, false)) {
              const auto targetHandle = toUUID(*managedField);
              if (!targetHandle.isNull()) {
                if (auto target = m_component.model().getObject(targetHandle)) {
                  m_originalOutletTarget = target->optionalCast<openstudio::epmodel::ModelObject>();
                }
              }
            }
            if (!m_originalOutletTarget) {
              auto workspaceImpl = m_airDistributionUnit->getImpl<openstudio::detail::WorkspaceObject_Impl>();
              OS_ASSERT(workspaceImpl);
              m_originalOutletNodeName = workspaceImpl->openstudio::detail::IdfObject_Impl::getString(outletField, false, true);
            }
          }

          if (auto outletNode = airTerminalOutletNode(m_component)) {
            auto airDistributionUnitImpl = m_airDistributionUnit->getImpl<openstudio::epmodel::detail::ZoneHVACAirDistributionUnit_Impl>();
            OS_ASSERT(airDistributionUnitImpl);
            if (!airDistributionUnitImpl->setOutletNode(*outletNode)) {
              return false;
            }
            m_outletSynchronized = true;
          }

          m_equipmentListTarget = m_airDistributionUnit->cast<openstudio::epmodel::ModelObject>();
          return true;
        }

        void cleanupPreparedState() {
          if (m_groupIndex && *m_groupIndex < m_equipmentList.extensibleGroups().size()) {
            m_equipmentList.eraseExtensibleGroup(*m_groupIndex);
          }

          if (!m_airDistributionUnit) {
            return;
          }
          if (m_createdAirDistributionUnit) {
            if (m_equipmentList.model().getObject(m_airDistributionUnit->handle())) {
              m_airDistributionUnit->remove();
            }
            return;
          }
          if (m_outletSynchronized) {
            auto impl = m_airDistributionUnit->getImpl<openstudio::epmodel::detail::ZoneHVACAirDistributionUnit_Impl>();
            OS_ASSERT(impl);
            const auto outletField = openstudio::ZoneHVAC_AirDistributionUnitFields::AirDistributionUnitOutletNodeName;
            bool restored = false;
            if (m_originalOutletTarget) {
              restored = impl->setPointer(outletField, m_originalOutletTarget->handle(), false);
            } else {
              const bool pointerCleared = impl->setPointer(outletField, Handle(), false);
              const bool rawRestored =
                impl->openstudio::detail::IdfObject_Impl::setString(outletField, m_originalOutletNodeName.get_value_or(""), false);
              restored = pointerCleared && rawRestored;
            }
            OS_ASSERT(restored);
            (void)restored;
          }
        }

        State m_state = State::Prepared;
        openstudio::epmodel::ZoneHVACEquipmentList m_equipmentList;
        openstudio::epmodel::ModelObject m_component;
        boost::optional<openstudio::epmodel::ModelObject> m_equipmentListTarget;
        boost::optional<openstudio::epmodel::ZoneHVACAirDistributionUnit> m_airDistributionUnit;
        boost::optional<openstudio::epmodel::ModelObject> m_originalOutletTarget;
        boost::optional<std::string> m_originalOutletNodeName;
        boost::optional<unsigned> m_groupIndex;
        bool m_alreadyRegistered = false;
        bool m_createdAirDistributionUnit = false;
        bool m_outletSynchronized = false;
      };

      bool equipmentListTargetMatches(const openstudio::epmodel::ModelObject& equipmentListTarget,
                                      const openstudio::epmodel::ModelObject& component) {
        if (equipmentListTarget == component) {
          return true;
        }
        if (auto airDistributionUnit = equipmentListTarget.optionalCast<openstudio::epmodel::ZoneHVACAirDistributionUnit>()) {
          auto terminal = airDistributionUnit->airTerminal();
          return terminal && (*terminal == component);
        }
        return false;
      }

      boost::optional<openstudio::WorkspaceExtensibleGroup> groupForModelObject(const openstudio::epmodel::ZoneHVACEquipmentList& equipmentList,
                                                                                const openstudio::epmodel::ModelObject& component) {
        for (const auto& group : equipmentList.extensibleGroups()) {
          auto workspaceGroup = group.optionalCast<openstudio::WorkspaceExtensibleGroup>();
          if (!workspaceGroup) {
            continue;
          }

          auto target = resolveEquipmentTarget(*workspaceGroup, equipmentList.model());
          if (target && equipmentListTargetMatches(*target, component)) {
            return workspaceGroup;
          }
        }
        return boost::none;
      }

      boost::optional<openstudio::epmodel::Schedule> resolveScheduleTarget(const openstudio::WorkspaceExtensibleGroup& group,
                                                                           const openstudio::epmodel::Model& model, unsigned fieldIndex) {
        if (auto target = group.getTarget(fieldIndex)) {
          if (auto schedule = target->optionalCast<openstudio::epmodel::Schedule>()) {
            return *schedule;
          }
        }

        if (auto scheduleName = group.getString(fieldIndex, true)) {
          if (!scheduleName->empty()) {
            for (const auto& candidate : model.getObjectsByName(*scheduleName, true)) {
              if (auto schedule = candidate.optionalCast<openstudio::epmodel::Schedule>()) {
                return *schedule;
              }
            }
          }
        }
        return boost::none;
      }

      bool setScheduleTarget(openstudio::WorkspaceExtensibleGroup& group, unsigned fieldIndex, const openstudio::epmodel::Schedule& schedule) {
        if (group.setPointer(fieldIndex, schedule.handle(), false)) {
          return true;
        }
        return group.setString(fieldIndex, schedule.nameString(), false);
      }

    }  // namespace

    std::string ZoneHVACEquipmentList_Impl::loadDistributionScheme() const {
      const auto value = getString(openstudio::ZoneHVAC_EquipmentListFields::LoadDistributionScheme, true);
      OS_ASSERT(value);
      return *value;
    }

    bool ZoneHVACEquipmentList_Impl::isLoadDistributionSchemeDefaulted() const {
      return isEmpty(openstudio::ZoneHVAC_EquipmentListFields::LoadDistributionScheme);
    }

    bool ZoneHVACEquipmentList_Impl::setLoadDistributionScheme(const std::string& loadDistributionScheme) {
      auto thisScheme = loadDistributionScheme;
      if (openstudio::istringEqual(thisScheme, "Sequential")) {
        thisScheme = "SequentialLoad";
      } else if (openstudio::istringEqual(thisScheme, "Uniform")) {
        thisScheme = "UniformLoad";
      }

      if (!openstudio::istringEqual(thisScheme, "SequentialLoad")) {
        for (const auto& group : getObject<openstudio::epmodel::ZoneHVACEquipmentList>().extensibleGroups()) {
          auto workspaceGroup = group.optionalCast<openstudio::WorkspaceExtensibleGroup>();
          if (!workspaceGroup) {
            continue;
          }
          workspaceGroup->setString(openstudio::ZoneHVAC_EquipmentListExtensibleFields::ZoneEquipmentSequentialCoolingFractionScheduleName, "",
                                    false);
          workspaceGroup->setString(openstudio::ZoneHVAC_EquipmentListExtensibleFields::ZoneEquipmentSequentialHeatingFractionScheduleName, "",
                                    false);
        }
      }

      const bool result = setString(openstudio::ZoneHVAC_EquipmentListFields::LoadDistributionScheme, thisScheme, false);
      OS_ASSERT(result);
      return result;
    }

    void ZoneHVACEquipmentList_Impl::resetLoadDistributionScheme() {
      OS_ASSERT(setString(openstudio::ZoneHVAC_EquipmentListFields::LoadDistributionScheme, "", false));
    }

    std::vector<openstudio::epmodel::ModelObject> ZoneHVACEquipmentList_Impl::equipment() const {
      std::vector<openstudio::epmodel::ModelObject> result;
      for (const auto& group : getObject<openstudio::epmodel::ZoneHVACEquipmentList>().extensibleGroups()) {
        auto workspaceGroup = group.optionalCast<openstudio::WorkspaceExtensibleGroup>();
        if (!workspaceGroup) {
          continue;
        }

        auto target = resolveEquipmentTarget(*workspaceGroup, model());
        if (!target) {
          continue;
        }

        if (auto equipmentObject = modelEquipmentObject(*target)) {
          result.push_back(*equipmentObject);
        }
      }
      return result;
    }

    std::vector<openstudio::epmodel::ModelObject> ZoneHVACEquipmentList_Impl::equipmentInHeatingOrder() const {
      std::vector<std::pair<unsigned, openstudio::epmodel::ModelObject>> equipmentByPriority;
      for (const auto& group : getObject<openstudio::epmodel::ZoneHVACEquipmentList>().extensibleGroups()) {
        auto workspaceGroup = group.optionalCast<openstudio::WorkspaceExtensibleGroup>();
        if (!workspaceGroup) {
          continue;
        }

        auto priority = workspaceGroup->getUnsigned(openstudio::ZoneHVAC_EquipmentListExtensibleFields::ZoneEquipmentHeatingorNoLoadSequence);
        auto target = resolveEquipmentTarget(*workspaceGroup, model());
        if (priority && (*priority > 0u) && target) {
          if (auto equipmentObject = modelEquipmentObject(*target)) {
            equipmentByPriority.emplace_back(*priority, *equipmentObject);
          }
        }
      }

      std::stable_sort(equipmentByPriority.begin(), equipmentByPriority.end(),
                       [](const auto& lhs, const auto& rhs) { return lhs.first < rhs.first; });

      std::vector<openstudio::epmodel::ModelObject> result;
      result.reserve(equipmentByPriority.size());
      for (const auto& [priority, equipment] : equipmentByPriority) {
        result.emplace_back(equipment);
      }
      return result;
    }

    std::vector<openstudio::epmodel::ModelObject> ZoneHVACEquipmentList_Impl::equipmentInCoolingOrder() const {
      std::vector<std::pair<unsigned, openstudio::epmodel::ModelObject>> equipmentByPriority;
      for (const auto& group : getObject<openstudio::epmodel::ZoneHVACEquipmentList>().extensibleGroups()) {
        auto workspaceGroup = group.optionalCast<openstudio::WorkspaceExtensibleGroup>();
        if (!workspaceGroup) {
          continue;
        }

        auto priority = workspaceGroup->getUnsigned(openstudio::ZoneHVAC_EquipmentListExtensibleFields::ZoneEquipmentCoolingSequence);
        auto target = resolveEquipmentTarget(*workspaceGroup, model());
        if (priority && (*priority > 0u) && target) {
          if (auto equipmentObject = modelEquipmentObject(*target)) {
            equipmentByPriority.emplace_back(*priority, *equipmentObject);
          }
        }
      }

      std::stable_sort(equipmentByPriority.begin(), equipmentByPriority.end(),
                       [](const auto& lhs, const auto& rhs) { return lhs.first < rhs.first; });

      std::vector<openstudio::epmodel::ModelObject> result;
      result.reserve(equipmentByPriority.size());
      for (const auto& [priority, equipment] : equipmentByPriority) {
        result.emplace_back(equipment);
      }
      return result;
    }

    openstudio::epmodel::ThermalZone ZoneHVACEquipmentList_Impl::thermalZone() const {
      const auto equipmentList = getObject<openstudio::epmodel::ZoneHVACEquipmentList>();
      for (const auto& conn : model().getConcreteModelObjects<openstudio::epmodel::ZoneHVACEquipmentConnections>()) {
        if (auto linkedList = conn.getModelObjectTarget<openstudio::epmodel::ZoneHVACEquipmentList>(
              openstudio::ZoneHVAC_EquipmentConnectionsFields::ZoneConditioningEquipmentListName)) {
          if (*linkedList == equipmentList) {
            return conn.thermalZone();
          }
        }
      }

      throw std::runtime_error("ZoneHVACEquipmentList is not referenced by a ZoneHVAC:EquipmentConnections object with a thermal zone.");
    }

    bool ZoneHVACEquipmentList_Impl::addEquipment(const openstudio::epmodel::ModelObject& component) {
      return addEquipment(component, AddEquipmentFailureStage::None);
    }

    bool ZoneHVACEquipmentList_Impl::addEquipment(const openstudio::epmodel::ModelObject& component, AddEquipmentFailureStage failureStage) {
      auto registration = EquipmentRegistrationPlan::prepare(getObject<openstudio::epmodel::ZoneHVACEquipmentList>(), component);
      if (!registration || failureStage == AddEquipmentFailureStage::AfterTargetPrepared) {
        return false;
      }
      if (!registration->alreadyRegistered() && !registration->addExtensibleRow()) {
        return false;
      }
      if (failureStage == AddEquipmentFailureStage::AfterExtensibleRowAdded) {
        return false;
      }
      registration->commit();
      return true;
    }

    bool ZoneHVACEquipmentList_Impl::removeEquipment(const openstudio::epmodel::ModelObject& component) {
      auto equipmentList = getObject<openstudio::epmodel::ZoneHVACEquipmentList>();
      auto coolingEquipment = equipmentInCoolingOrder();
      auto heatingEquipment = equipmentInHeatingOrder();
      auto priorityComponent = modelEquipmentObject(component);
      if (!priorityComponent) {
        priorityComponent = component;
      }
      const auto groups = equipmentList.extensibleGroups();
      for (unsigned i = 0; i < groups.size(); ++i) {
        auto workspaceGroup = groups[i].optionalCast<openstudio::WorkspaceExtensibleGroup>();
        if (!workspaceGroup) {
          continue;
        }

        auto target = resolveEquipmentTarget(*workspaceGroup, model());
        if (!target || !equipmentListTargetMatches(*target, component)) {
          continue;
        }

        equipmentList.getImpl<openstudio::epmodel::detail::ModelObject_Impl>()->eraseExtensibleGroup(workspaceGroup->groupIndex(), false);

        coolingEquipment.erase(std::remove(coolingEquipment.begin(), coolingEquipment.end(), *priorityComponent), coolingEquipment.end());
        heatingEquipment.erase(std::remove(heatingEquipment.begin(), heatingEquipment.end(), *priorityComponent), heatingEquipment.end());

        for (unsigned j = 0; j < coolingEquipment.size(); ++j) {
          auto remainingGroup = groupForModelObject(equipmentList, coolingEquipment[j]);
          OS_ASSERT(remainingGroup);
          if (!remainingGroup) {
            return false;
          }
          const bool prioritySet =
            remainingGroup->setUnsigned(openstudio::ZoneHVAC_EquipmentListExtensibleFields::ZoneEquipmentCoolingSequence, j + 1u);
          OS_ASSERT(prioritySet);
          if (!prioritySet) {
            return false;
          }
        }
        for (unsigned j = 0; j < heatingEquipment.size(); ++j) {
          auto remainingGroup = groupForModelObject(equipmentList, heatingEquipment[j]);
          OS_ASSERT(remainingGroup);
          if (!remainingGroup) {
            return false;
          }
          const bool prioritySet =
            remainingGroup->setUnsigned(openstudio::ZoneHVAC_EquipmentListExtensibleFields::ZoneEquipmentHeatingorNoLoadSequence, j + 1u);
          OS_ASSERT(prioritySet);
          if (!prioritySet) {
            return false;
          }
        }
        return true;
      }
      return false;
    }

    bool ZoneHVACEquipmentList_Impl::setCoolingPriority(const openstudio::epmodel::ModelObject& component, unsigned priority) {
      auto equipmentList = getObject<openstudio::epmodel::ZoneHVACEquipmentList>();
      auto equipmentVector = equipmentInCoolingOrder();
      auto group = groupForModelObject(equipmentList, component);
      if (!group) {
        return false;
      }

      if (std::ranges::find(equipmentVector, component) == equipmentVector.end()) {
        equipmentVector.push_back(component);
      }

      if (priority > equipmentVector.size()) {
        priority = static_cast<unsigned>(equipmentVector.size());
      } else if (priority < 1u) {
        priority = 1u;
      }

      equipmentVector.erase(std::remove(equipmentVector.begin(), equipmentVector.end(), component), equipmentVector.end());
      equipmentVector.insert(equipmentVector.begin() + (priority - 1u), component);

      for (unsigned i = 0; i < equipmentVector.size(); ++i) {
        auto equipmentGroup = groupForModelObject(equipmentList, equipmentVector[i]);
        OS_ASSERT(equipmentGroup);
        if (!equipmentGroup) {
          return false;
        }
        const bool prioritySet =
          equipmentGroup->setUnsigned(openstudio::ZoneHVAC_EquipmentListExtensibleFields::ZoneEquipmentCoolingSequence, i + 1u);
        OS_ASSERT(prioritySet);
        if (!prioritySet) {
          return false;
        }
      }
      return true;
    }

    bool ZoneHVACEquipmentList_Impl::setHeatingPriority(const openstudio::epmodel::ModelObject& component, unsigned priority) {
      auto equipmentList = getObject<openstudio::epmodel::ZoneHVACEquipmentList>();
      auto equipmentVector = equipmentInHeatingOrder();
      auto group = groupForModelObject(equipmentList, component);
      if (!group) {
        return false;
      }

      if (std::ranges::find(equipmentVector, component) == equipmentVector.end()) {
        equipmentVector.push_back(component);
      }

      if (priority > equipmentVector.size()) {
        priority = static_cast<unsigned>(equipmentVector.size());
      } else if (priority < 1u) {
        priority = 1u;
      }

      equipmentVector.erase(std::remove(equipmentVector.begin(), equipmentVector.end(), component), equipmentVector.end());
      equipmentVector.insert(equipmentVector.begin() + (priority - 1u), component);

      for (unsigned i = 0; i < equipmentVector.size(); ++i) {
        auto equipmentGroup = groupForModelObject(equipmentList, equipmentVector[i]);
        OS_ASSERT(equipmentGroup);
        if (!equipmentGroup) {
          return false;
        }
        const bool prioritySet = equipmentGroup->setUnsigned(
          openstudio::ZoneHVAC_EquipmentListExtensibleFields::ZoneEquipmentHeatingorNoLoadSequence, i + 1u);
        OS_ASSERT(prioritySet);
        if (!prioritySet) {
          return false;
        }
      }
      return true;
    }

    unsigned ZoneHVACEquipmentList_Impl::heatingPriority(const openstudio::epmodel::ModelObject& component) const {
      auto group = groupForModelObject(getObject<openstudio::epmodel::ZoneHVACEquipmentList>(), component);
      if (!group) {
        return 0u;
      }
      return group->getUnsigned(openstudio::ZoneHVAC_EquipmentListExtensibleFields::ZoneEquipmentHeatingorNoLoadSequence).get_value_or(0u);
    }

    unsigned ZoneHVACEquipmentList_Impl::coolingPriority(const openstudio::epmodel::ModelObject& component) const {
      auto group = groupForModelObject(getObject<openstudio::epmodel::ZoneHVACEquipmentList>(), component);
      if (!group) {
        return 0u;
      }
      return group->getUnsigned(openstudio::ZoneHVAC_EquipmentListExtensibleFields::ZoneEquipmentCoolingSequence).get_value_or(0u);
    }

    boost::optional<openstudio::epmodel::Schedule>
      ZoneHVACEquipmentList_Impl::sequentialCoolingFractionSchedule(const openstudio::epmodel::ModelObject& component) const {
      if (!openstudio::istringEqual(loadDistributionScheme(), "SequentialLoad") || (coolingPriority(component) == 0u)) {
        return boost::none;
      }
      auto group = groupForModelObject(getObject<openstudio::epmodel::ZoneHVACEquipmentList>(), component);
      if (!group) {
        return boost::none;
      }
      return resolveScheduleTarget(*group, model(),
                                   openstudio::ZoneHVAC_EquipmentListExtensibleFields::ZoneEquipmentSequentialCoolingFractionScheduleName);
    }

    boost::optional<openstudio::epmodel::Schedule>
      ZoneHVACEquipmentList_Impl::sequentialHeatingFractionSchedule(const openstudio::epmodel::ModelObject& component) const {
      if (!openstudio::istringEqual(loadDistributionScheme(), "SequentialLoad") || (heatingPriority(component) == 0u)) {
        return boost::none;
      }
      auto group = groupForModelObject(getObject<openstudio::epmodel::ZoneHVACEquipmentList>(), component);
      if (!group) {
        return boost::none;
      }
      return resolveScheduleTarget(*group, model(),
                                   openstudio::ZoneHVAC_EquipmentListExtensibleFields::ZoneEquipmentSequentialHeatingFractionScheduleName);
    }

    boost::optional<double> ZoneHVACEquipmentList_Impl::sequentialCoolingFraction(const openstudio::epmodel::ModelObject& component) const {
      if (auto schedule = sequentialCoolingFractionSchedule(component)) {
        if (auto constant = schedule->optionalCast<openstudio::epmodel::ScheduleConstant>()) {
          return constant->value();
        }
      }
      return boost::none;
    }

    boost::optional<double> ZoneHVACEquipmentList_Impl::sequentialHeatingFraction(const openstudio::epmodel::ModelObject& component) const {
      if (auto schedule = sequentialHeatingFractionSchedule(component)) {
        if (auto constant = schedule->optionalCast<openstudio::epmodel::ScheduleConstant>()) {
          return constant->value();
        }
      }
      return boost::none;
    }

    bool ZoneHVACEquipmentList_Impl::setSequentialCoolingFractionSchedule(const openstudio::epmodel::ModelObject& component,
                                                                          openstudio::epmodel::Schedule& schedule) {
      if (schedule.model() != model() || !openstudio::istringEqual(loadDistributionScheme(), "SequentialLoad")
          || (coolingPriority(component) == 0u)) {
        return false;
      }
      auto group = groupForModelObject(getObject<openstudio::epmodel::ZoneHVACEquipmentList>(), component);
      if (!group) {
        return false;
      }
      return setScheduleTarget(*group, openstudio::ZoneHVAC_EquipmentListExtensibleFields::ZoneEquipmentSequentialCoolingFractionScheduleName,
                               schedule);
    }

    bool ZoneHVACEquipmentList_Impl::setSequentialHeatingFractionSchedule(const openstudio::epmodel::ModelObject& component,
                                                                          openstudio::epmodel::Schedule& schedule) {
      if (schedule.model() != model() || !openstudio::istringEqual(loadDistributionScheme(), "SequentialLoad")
          || (heatingPriority(component) == 0u)) {
        return false;
      }
      auto group = groupForModelObject(getObject<openstudio::epmodel::ZoneHVACEquipmentList>(), component);
      if (!group) {
        return false;
      }
      return setScheduleTarget(*group, openstudio::ZoneHVAC_EquipmentListExtensibleFields::ZoneEquipmentSequentialHeatingFractionScheduleName,
                               schedule);
    }

    bool ZoneHVACEquipmentList_Impl::setSequentialCoolingFraction(const openstudio::epmodel::ModelObject& component, double fraction) {
      openstudio::epmodel::ScheduleConstant schedule(model());
      OS_ASSERT(schedule.setValue(fraction));
      return setSequentialCoolingFractionSchedule(component, schedule);
    }

    bool ZoneHVACEquipmentList_Impl::setSequentialHeatingFraction(const openstudio::epmodel::ModelObject& component, double fraction) {
      openstudio::epmodel::ScheduleConstant schedule(model());
      OS_ASSERT(schedule.setValue(fraction));
      return setSequentialHeatingFractionSchedule(component, schedule);
    }

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
