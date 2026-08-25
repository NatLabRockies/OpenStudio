/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "StraightComponent/SwimmingPoolIndoor.hpp"
#include "StraightComponent/SwimmingPoolIndoor_Impl.hpp"

#include "Loop/PlantLoop.hpp"
#include "Model.hpp"
#include "Schedule/Schedule.hpp"
#include "Schedule/Schedule_Impl.hpp"
#include "Schedule/ScheduleConstant.hpp"
#include "StraightComponent/Node.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/idd/SwimmingPool_Indoor_FieldEnums.hxx>
#include <utilities/idf/IdfObject_Impl.hpp>

namespace openstudio {
namespace epmodel {

  SwimmingPoolIndoor::SwimmingPoolIndoor(const Model& model) : StraightComponent(SwimmingPoolIndoor::iddObjectType(), model) {
    OS_ASSERT(getImpl<detail::SwimmingPoolIndoor_Impl>());

    OS_ASSERT(setAverageDepth(2.0));
    OS_ASSERT(setPoolHeatingSystemMaximumWaterFlowRate(0.1));
    OS_ASSERT(setPoolMiscellaneousEquipmentPower(0.0));
    OS_ASSERT(setMaximumNumberofPeople(15.0));

    auto alwaysOn = model.alwaysOnDiscreteSchedule();
    OS_ASSERT(setActivityFactorSchedule(alwaysOn));
    OS_ASSERT(setPeopleSchedule(alwaysOn));

    ScheduleConstant cover(model);
    OS_ASSERT(cover.setValue(0.0));
    OS_ASSERT(setCoverSchedule(cover));

    ScheduleConstant makeupWater(model);
    OS_ASSERT(makeupWater.setValue(16.67));
    OS_ASSERT(makeupWater.setName("Pool MakeUp Water Temperature Schedule"));
    OS_ASSERT(setMakeupWaterSupplySchedule(makeupWater));

    ScheduleConstant peopleHeatGain(model);
    OS_ASSERT(peopleHeatGain.setValue(300.0));
    OS_ASSERT(peopleHeatGain.setName("Pool People Heat Gain Schedule"));
    OS_ASSERT(setPeopleHeatGainSchedule(peopleHeatGain));

    ScheduleConstant setpointTemperature(model);
    OS_ASSERT(setpointTemperature.setValue(27.0));
    OS_ASSERT(setpointTemperature.setName("Pool Setpoint Temperature Schedule"));
    OS_ASSERT(setSetpointTemperatureSchedule(setpointTemperature));
  }

  SwimmingPoolIndoor::SwimmingPoolIndoor(std::shared_ptr<detail::SwimmingPoolIndoor_Impl> impl) : StraightComponent(std::move(impl)) {}

  IddObjectType SwimmingPoolIndoor::iddObjectType() {
    return IddObjectType::SwimmingPool_Indoor;
  }

  double SwimmingPoolIndoor::averageDepth() const {
    return getImpl<detail::SwimmingPoolIndoor_Impl>()->averageDepth();
  }

  bool SwimmingPoolIndoor::setAverageDepth(double averageDepth) {
    return getImpl<detail::SwimmingPoolIndoor_Impl>()->setAverageDepth(averageDepth);
  }

  Schedule SwimmingPoolIndoor::activityFactorSchedule() const {
    return getImpl<detail::SwimmingPoolIndoor_Impl>()->activityFactorSchedule();
  }

  bool SwimmingPoolIndoor::setActivityFactorSchedule(Schedule& schedule) {
    return getImpl<detail::SwimmingPoolIndoor_Impl>()->setActivityFactorSchedule(schedule);
  }

  Schedule SwimmingPoolIndoor::makeupWaterSupplySchedule() const {
    return getImpl<detail::SwimmingPoolIndoor_Impl>()->makeupWaterSupplySchedule();
  }

  bool SwimmingPoolIndoor::setMakeupWaterSupplySchedule(Schedule& schedule) {
    return getImpl<detail::SwimmingPoolIndoor_Impl>()->setMakeupWaterSupplySchedule(schedule);
  }

  Schedule SwimmingPoolIndoor::coverSchedule() const {
    return getImpl<detail::SwimmingPoolIndoor_Impl>()->coverSchedule();
  }

  bool SwimmingPoolIndoor::setCoverSchedule(Schedule& schedule) {
    return getImpl<detail::SwimmingPoolIndoor_Impl>()->setCoverSchedule(schedule);
  }

  double SwimmingPoolIndoor::coverEvaporationFactor() const {
    return getImpl<detail::SwimmingPoolIndoor_Impl>()->coverEvaporationFactor();
  }

  bool SwimmingPoolIndoor::isCoverEvaporationFactorDefaulted() const {
    return getImpl<detail::SwimmingPoolIndoor_Impl>()->isCoverEvaporationFactorDefaulted();
  }

  bool SwimmingPoolIndoor::setCoverEvaporationFactor(double coverEvaporationFactor) {
    return getImpl<detail::SwimmingPoolIndoor_Impl>()->setCoverEvaporationFactor(coverEvaporationFactor);
  }

  void SwimmingPoolIndoor::resetCoverEvaporationFactor() {
    getImpl<detail::SwimmingPoolIndoor_Impl>()->resetCoverEvaporationFactor();
  }

  double SwimmingPoolIndoor::coverConvectionFactor() const {
    return getImpl<detail::SwimmingPoolIndoor_Impl>()->coverConvectionFactor();
  }

  bool SwimmingPoolIndoor::isCoverConvectionFactorDefaulted() const {
    return getImpl<detail::SwimmingPoolIndoor_Impl>()->isCoverConvectionFactorDefaulted();
  }

  bool SwimmingPoolIndoor::setCoverConvectionFactor(double coverConvectionFactor) {
    return getImpl<detail::SwimmingPoolIndoor_Impl>()->setCoverConvectionFactor(coverConvectionFactor);
  }

  void SwimmingPoolIndoor::resetCoverConvectionFactor() {
    getImpl<detail::SwimmingPoolIndoor_Impl>()->resetCoverConvectionFactor();
  }

  double SwimmingPoolIndoor::coverShortWavelengthRadiationFactor() const {
    return getImpl<detail::SwimmingPoolIndoor_Impl>()->coverShortWavelengthRadiationFactor();
  }

  bool SwimmingPoolIndoor::isCoverShortWavelengthRadiationFactorDefaulted() const {
    return getImpl<detail::SwimmingPoolIndoor_Impl>()->isCoverShortWavelengthRadiationFactorDefaulted();
  }

  bool SwimmingPoolIndoor::setCoverShortWavelengthRadiationFactor(double coverShortWavelengthRadiationFactor) {
    return getImpl<detail::SwimmingPoolIndoor_Impl>()->setCoverShortWavelengthRadiationFactor(coverShortWavelengthRadiationFactor);
  }

  void SwimmingPoolIndoor::resetCoverShortWavelengthRadiationFactor() {
    getImpl<detail::SwimmingPoolIndoor_Impl>()->resetCoverShortWavelengthRadiationFactor();
  }

  double SwimmingPoolIndoor::coverLongWavelengthRadiationFactor() const {
    return getImpl<detail::SwimmingPoolIndoor_Impl>()->coverLongWavelengthRadiationFactor();
  }

  bool SwimmingPoolIndoor::isCoverLongWavelengthRadiationFactorDefaulted() const {
    return getImpl<detail::SwimmingPoolIndoor_Impl>()->isCoverLongWavelengthRadiationFactorDefaulted();
  }

  bool SwimmingPoolIndoor::setCoverLongWavelengthRadiationFactor(double coverLongWavelengthRadiationFactor) {
    return getImpl<detail::SwimmingPoolIndoor_Impl>()->setCoverLongWavelengthRadiationFactor(coverLongWavelengthRadiationFactor);
  }

  void SwimmingPoolIndoor::resetCoverLongWavelengthRadiationFactor() {
    getImpl<detail::SwimmingPoolIndoor_Impl>()->resetCoverLongWavelengthRadiationFactor();
  }

  double SwimmingPoolIndoor::poolHeatingSystemMaximumWaterFlowRate() const {
    return getImpl<detail::SwimmingPoolIndoor_Impl>()->poolHeatingSystemMaximumWaterFlowRate();
  }

  bool SwimmingPoolIndoor::setPoolHeatingSystemMaximumWaterFlowRate(double poolHeatingSystemMaximumWaterFlowRate) {
    return getImpl<detail::SwimmingPoolIndoor_Impl>()->setPoolHeatingSystemMaximumWaterFlowRate(poolHeatingSystemMaximumWaterFlowRate);
  }

  double SwimmingPoolIndoor::poolMiscellaneousEquipmentPower() const {
    return getImpl<detail::SwimmingPoolIndoor_Impl>()->poolMiscellaneousEquipmentPower();
  }

  bool SwimmingPoolIndoor::setPoolMiscellaneousEquipmentPower(double poolMiscellaneousEquipmentPower) {
    return getImpl<detail::SwimmingPoolIndoor_Impl>()->setPoolMiscellaneousEquipmentPower(poolMiscellaneousEquipmentPower);
  }

  Schedule SwimmingPoolIndoor::setpointTemperatureSchedule() const {
    return getImpl<detail::SwimmingPoolIndoor_Impl>()->setpointTemperatureSchedule();
  }

  bool SwimmingPoolIndoor::setSetpointTemperatureSchedule(Schedule& schedule) {
    return getImpl<detail::SwimmingPoolIndoor_Impl>()->setSetpointTemperatureSchedule(schedule);
  }

  double SwimmingPoolIndoor::maximumNumberofPeople() const {
    return getImpl<detail::SwimmingPoolIndoor_Impl>()->maximumNumberofPeople();
  }

  bool SwimmingPoolIndoor::setMaximumNumberofPeople(double maximumNumberofPeople) {
    return getImpl<detail::SwimmingPoolIndoor_Impl>()->setMaximumNumberofPeople(maximumNumberofPeople);
  }

  Schedule SwimmingPoolIndoor::peopleSchedule() const {
    return getImpl<detail::SwimmingPoolIndoor_Impl>()->peopleSchedule();
  }

  bool SwimmingPoolIndoor::setPeopleSchedule(Schedule& schedule) {
    return getImpl<detail::SwimmingPoolIndoor_Impl>()->setPeopleSchedule(schedule);
  }

  Schedule SwimmingPoolIndoor::peopleHeatGainSchedule() const {
    return getImpl<detail::SwimmingPoolIndoor_Impl>()->peopleHeatGainSchedule();
  }

  bool SwimmingPoolIndoor::setPeopleHeatGainSchedule(Schedule& schedule) {
    return getImpl<detail::SwimmingPoolIndoor_Impl>()->setPeopleHeatGainSchedule(schedule);
  }

  boost::optional<Node> SwimmingPoolIndoor::poolWaterInletNode() const {
    return getImpl<detail::SwimmingPoolIndoor_Impl>()->poolWaterInletNode();
  }

  boost::optional<Node> SwimmingPoolIndoor::poolWaterOutletNode() const {
    return getImpl<detail::SwimmingPoolIndoor_Impl>()->poolWaterOutletNode();
  }

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
  namespace detail {

    bool SwimmingPoolIndoor_Impl::addToNode(Node& node) {
      if (auto plantLoop = node.plantLoop()) {
        if (plantLoop->demandComponent(node.handle())) {
          return StraightComponent_Impl::addToNode(node);
        }
      }
      return false;
    }

    unsigned SwimmingPoolIndoor_Impl::inletPort() const {
      return openstudio::SwimmingPool_IndoorFields::PoolWaterInletNode;
    }

    unsigned SwimmingPoolIndoor_Impl::outletPort() const {
      return openstudio::SwimmingPool_IndoorFields::PoolWaterOutletNode;
    }

    double SwimmingPoolIndoor_Impl::averageDepth() const {
      const auto value = getDouble(openstudio::SwimmingPool_IndoorFields::AverageDepth, true);
      OS_ASSERT(value);
      return *value;
    }

    bool SwimmingPoolIndoor_Impl::setAverageDepth(double averageDepth) {
      const bool result = setDouble(openstudio::SwimmingPool_IndoorFields::AverageDepth, averageDepth);
      OS_ASSERT(result);
      return result;
    }

    Schedule SwimmingPoolIndoor_Impl::activityFactorSchedule() const {
      auto schedule = getObject<ModelObject>().getModelObjectTarget<Schedule>(openstudio::SwimmingPool_IndoorFields::ActivityFactorScheduleName);
      OS_ASSERT(schedule);
      return *schedule;
    }

    bool SwimmingPoolIndoor_Impl::setActivityFactorSchedule(Schedule& schedule) {
      return ModelObject_Impl::setSchedule(openstudio::SwimmingPool_IndoorFields::ActivityFactorScheduleName, "SwimmingPoolIndoor", "Activity Factor",
                                           schedule);
    }

    Schedule SwimmingPoolIndoor_Impl::makeupWaterSupplySchedule() const {
      auto schedule = getObject<ModelObject>().getModelObjectTarget<Schedule>(openstudio::SwimmingPool_IndoorFields::MakeupWaterSupplyScheduleName);
      OS_ASSERT(schedule);
      return *schedule;
    }

    bool SwimmingPoolIndoor_Impl::setMakeupWaterSupplySchedule(Schedule& schedule) {
      return ModelObject_Impl::setSchedule(openstudio::SwimmingPool_IndoorFields::MakeupWaterSupplyScheduleName, "SwimmingPoolIndoor",
                                           "Make-up Water Supply", schedule);
    }

    Schedule SwimmingPoolIndoor_Impl::coverSchedule() const {
      auto schedule = getObject<ModelObject>().getModelObjectTarget<Schedule>(openstudio::SwimmingPool_IndoorFields::CoverScheduleName);
      OS_ASSERT(schedule);
      return *schedule;
    }

    bool SwimmingPoolIndoor_Impl::setCoverSchedule(Schedule& schedule) {
      return ModelObject_Impl::setSchedule(openstudio::SwimmingPool_IndoorFields::CoverScheduleName, "SwimmingPoolIndoor", "Cover", schedule);
    }

    double SwimmingPoolIndoor_Impl::coverEvaporationFactor() const {
      const auto value = getDouble(openstudio::SwimmingPool_IndoorFields::CoverEvaporationFactor, true);
      OS_ASSERT(value);
      return *value;
    }

    bool SwimmingPoolIndoor_Impl::isCoverEvaporationFactorDefaulted() const {
      return isEmpty(openstudio::SwimmingPool_IndoorFields::CoverEvaporationFactor);
    }

    bool SwimmingPoolIndoor_Impl::setCoverEvaporationFactor(double coverEvaporationFactor) {
      return setDouble(openstudio::SwimmingPool_IndoorFields::CoverEvaporationFactor, coverEvaporationFactor);
    }

    void SwimmingPoolIndoor_Impl::resetCoverEvaporationFactor() {
      OS_ASSERT(setString(openstudio::SwimmingPool_IndoorFields::CoverEvaporationFactor, ""));
    }

    double SwimmingPoolIndoor_Impl::coverConvectionFactor() const {
      const auto value = getDouble(openstudio::SwimmingPool_IndoorFields::CoverConvectionFactor, true);
      OS_ASSERT(value);
      return *value;
    }

    bool SwimmingPoolIndoor_Impl::isCoverConvectionFactorDefaulted() const {
      return isEmpty(openstudio::SwimmingPool_IndoorFields::CoverConvectionFactor);
    }

    bool SwimmingPoolIndoor_Impl::setCoverConvectionFactor(double coverConvectionFactor) {
      return setDouble(openstudio::SwimmingPool_IndoorFields::CoverConvectionFactor, coverConvectionFactor);
    }

    void SwimmingPoolIndoor_Impl::resetCoverConvectionFactor() {
      OS_ASSERT(setString(openstudio::SwimmingPool_IndoorFields::CoverConvectionFactor, ""));
    }

    double SwimmingPoolIndoor_Impl::coverShortWavelengthRadiationFactor() const {
      const auto value = getDouble(openstudio::SwimmingPool_IndoorFields::CoverShortWavelengthRadiationFactor, true);
      OS_ASSERT(value);
      return *value;
    }

    bool SwimmingPoolIndoor_Impl::isCoverShortWavelengthRadiationFactorDefaulted() const {
      return isEmpty(openstudio::SwimmingPool_IndoorFields::CoverShortWavelengthRadiationFactor);
    }

    bool SwimmingPoolIndoor_Impl::setCoverShortWavelengthRadiationFactor(double coverShortWavelengthRadiationFactor) {
      return setDouble(openstudio::SwimmingPool_IndoorFields::CoverShortWavelengthRadiationFactor, coverShortWavelengthRadiationFactor);
    }

    void SwimmingPoolIndoor_Impl::resetCoverShortWavelengthRadiationFactor() {
      OS_ASSERT(setString(openstudio::SwimmingPool_IndoorFields::CoverShortWavelengthRadiationFactor, ""));
    }

    double SwimmingPoolIndoor_Impl::coverLongWavelengthRadiationFactor() const {
      const auto value = getDouble(openstudio::SwimmingPool_IndoorFields::CoverLongWavelengthRadiationFactor, true);
      OS_ASSERT(value);
      return *value;
    }

    bool SwimmingPoolIndoor_Impl::isCoverLongWavelengthRadiationFactorDefaulted() const {
      return isEmpty(openstudio::SwimmingPool_IndoorFields::CoverLongWavelengthRadiationFactor);
    }

    bool SwimmingPoolIndoor_Impl::setCoverLongWavelengthRadiationFactor(double coverLongWavelengthRadiationFactor) {
      return setDouble(openstudio::SwimmingPool_IndoorFields::CoverLongWavelengthRadiationFactor, coverLongWavelengthRadiationFactor);
    }

    void SwimmingPoolIndoor_Impl::resetCoverLongWavelengthRadiationFactor() {
      OS_ASSERT(setString(openstudio::SwimmingPool_IndoorFields::CoverLongWavelengthRadiationFactor, ""));
    }

    double SwimmingPoolIndoor_Impl::poolHeatingSystemMaximumWaterFlowRate() const {
      const auto value = getDouble(openstudio::SwimmingPool_IndoorFields::PoolHeatingSystemMaximumWaterFlowRate, true);
      OS_ASSERT(value);
      return *value;
    }

    bool SwimmingPoolIndoor_Impl::setPoolHeatingSystemMaximumWaterFlowRate(double poolHeatingSystemMaximumWaterFlowRate) {
      return setDouble(openstudio::SwimmingPool_IndoorFields::PoolHeatingSystemMaximumWaterFlowRate, poolHeatingSystemMaximumWaterFlowRate);
    }

    double SwimmingPoolIndoor_Impl::poolMiscellaneousEquipmentPower() const {
      const auto value = getDouble(openstudio::SwimmingPool_IndoorFields::PoolMiscellaneousEquipmentPower, true);
      OS_ASSERT(value);
      return *value;
    }

    bool SwimmingPoolIndoor_Impl::setPoolMiscellaneousEquipmentPower(double poolMiscellaneousEquipmentPower) {
      return setDouble(openstudio::SwimmingPool_IndoorFields::PoolMiscellaneousEquipmentPower, poolMiscellaneousEquipmentPower);
    }

    Schedule SwimmingPoolIndoor_Impl::setpointTemperatureSchedule() const {
      auto schedule = getObject<ModelObject>().getModelObjectTarget<Schedule>(openstudio::SwimmingPool_IndoorFields::SetpointTemperatureSchedule);
      OS_ASSERT(schedule);
      return *schedule;
    }

    bool SwimmingPoolIndoor_Impl::setSetpointTemperatureSchedule(Schedule& schedule) {
      return ModelObject_Impl::setSchedule(openstudio::SwimmingPool_IndoorFields::SetpointTemperatureSchedule, "SwimmingPoolIndoor",
                                           "Setpoint Temperature Schedule", schedule);
    }

    double SwimmingPoolIndoor_Impl::maximumNumberofPeople() const {
      const auto value = getDouble(openstudio::SwimmingPool_IndoorFields::MaximumNumberofPeople, true);
      OS_ASSERT(value);
      return *value;
    }

    bool SwimmingPoolIndoor_Impl::setMaximumNumberofPeople(double maximumNumberofPeople) {
      return setDouble(openstudio::SwimmingPool_IndoorFields::MaximumNumberofPeople, maximumNumberofPeople);
    }

    Schedule SwimmingPoolIndoor_Impl::peopleSchedule() const {
      auto schedule = getObject<ModelObject>().getModelObjectTarget<Schedule>(openstudio::SwimmingPool_IndoorFields::PeopleSchedule);
      OS_ASSERT(schedule);
      return *schedule;
    }

    bool SwimmingPoolIndoor_Impl::setPeopleSchedule(Schedule& schedule) {
      return ModelObject_Impl::setSchedule(openstudio::SwimmingPool_IndoorFields::PeopleSchedule, "SwimmingPoolIndoor", "People Schedule", schedule);
    }

    Schedule SwimmingPoolIndoor_Impl::peopleHeatGainSchedule() const {
      auto schedule = getObject<ModelObject>().getModelObjectTarget<Schedule>(openstudio::SwimmingPool_IndoorFields::PeopleHeatGainSchedule);
      OS_ASSERT(schedule);
      return *schedule;
    }

    bool SwimmingPoolIndoor_Impl::setPeopleHeatGainSchedule(Schedule& schedule) {
      return ModelObject_Impl::setSchedule(openstudio::SwimmingPool_IndoorFields::PeopleHeatGainSchedule, "SwimmingPoolIndoor",
                                           "People Heat Gain Schedule", schedule);
    }

    boost::optional<Node> SwimmingPoolIndoor_Impl::poolWaterInletNode() const {
      return resolvedNodeTarget(inletPort());
    }

    boost::optional<Node> SwimmingPoolIndoor_Impl::poolWaterOutletNode() const {
      return resolvedNodeTarget(outletPort());
    }

    void SwimmingPoolIndoor_Impl::doCanonicalize(LoadContext& context) {
      StraightComponent_Impl::doCanonicalize(context);

      const auto pool = getObject<ModelObject>();
      const auto poolName = pool.nameString();

      auto ensureSchedule = [&](unsigned field, const std::string& relationshipName, auto&& makeDefault, auto&& setRelationship) {
        if (auto schedule = pool.getModelObjectTarget<Schedule>(field)) {
          boost::optional<Schedule> uniqueNamedSchedule;
          bool ambiguousName = false;
          for (const auto& candidate : model().getObjectsByName(schedule->nameString(), true)) {
            if (auto namedSchedule = candidate.optionalCast<Schedule>()) {
              if (!model().canBeTarget(namedSchedule->handle(), iddObject().objectLists(field))) {
                continue;
              }
              if (uniqueNamedSchedule) {
                ambiguousName = true;
                break;
              }
              uniqueNamedSchedule = *namedSchedule;
            }
          }

          if (!ambiguousName && uniqueNamedSchedule && (uniqueNamedSchedule->handle() == schedule->handle()) && setRelationship(*schedule)) {
            return;
          }
          detail::addLoadWarning(context, "Preserved an ambiguous, ineligible, or incompatible " + relationshipName + " on SwimmingPool:Indoor '"
                                            + poolName + "'.");
          return;
        }

        const auto rawName = openstudio::detail::IdfObject_Impl::getString(field, false, true);
        if (rawName && !rawName->empty()) {
          boost::optional<Schedule> match;
          bool ambiguous = false;
          for (const auto& candidate : model().getObjectsByName(*rawName, true)) {
            if (auto schedule = candidate.optionalCast<Schedule>()) {
              if (!model().canBeTarget(schedule->handle(), iddObject().objectLists(field))) {
                continue;
              }
              if (match) {
                ambiguous = true;
                break;
              }
              match = *schedule;
            }
          }

          if (match && !ambiguous) {
            if (setRelationship(*match)) {
              detail::addLoadInfo(context,
                                  "Reattached " + relationshipName + " '" + match->nameString() + "' to SwimmingPool:Indoor '" + poolName + "'.");
            } else {
              detail::addLoadWarning(context, "Preserved incompatible " + relationshipName + " reference '" + *rawName + "' on SwimmingPool:Indoor '"
                                                + poolName + "'.");
            }
          } else {
            detail::addLoadWarning(context, "Preserved unresolved or ambiguous " + relationshipName + " reference '" + *rawName
                                              + "' on SwimmingPool:Indoor '" + poolName + "'.");
          }
          return;
        }

        if (!context.repairEnabled()) {
          detail::addLoadWarning(context, "SwimmingPool:Indoor '" + poolName + "' has a blank " + relationshipName + ".");
          return;
        }

        auto schedule = makeDefault();
        if (setRelationship(schedule)) {
          detail::addLoadInfo(context, "Attached the canonical " + relationshipName + " to SwimmingPool:Indoor '" + poolName + "'.");
        } else {
          detail::addLoadError(context, "Failed to attach the canonical " + relationshipName + " to SwimmingPool:Indoor '" + poolName + "'.");
        }
      };

      ensureSchedule(
        openstudio::SwimmingPool_IndoorFields::ActivityFactorScheduleName, "activity factor schedule",
        [&]() -> Schedule { return model().alwaysOnDiscreteSchedule(); }, [&](Schedule& schedule) { return setActivityFactorSchedule(schedule); });
      ensureSchedule(
        openstudio::SwimmingPool_IndoorFields::MakeupWaterSupplyScheduleName, "make-up water supply schedule",
        [&]() -> Schedule {
          ScheduleConstant schedule(model());
          OS_ASSERT(schedule.setValue(16.67));
          OS_ASSERT(schedule.setName("Pool MakeUp Water Temperature Schedule"));
          return schedule;
        },
        [&](Schedule& schedule) { return setMakeupWaterSupplySchedule(schedule); });
      ensureSchedule(
        openstudio::SwimmingPool_IndoorFields::CoverScheduleName, "cover schedule",
        [&]() -> Schedule {
          ScheduleConstant schedule(model());
          OS_ASSERT(schedule.setValue(0.0));
          return schedule;
        },
        [&](Schedule& schedule) { return setCoverSchedule(schedule); });
      ensureSchedule(
        openstudio::SwimmingPool_IndoorFields::SetpointTemperatureSchedule, "setpoint temperature schedule",
        [&]() -> Schedule {
          ScheduleConstant schedule(model());
          OS_ASSERT(schedule.setValue(27.0));
          OS_ASSERT(schedule.setName("Pool Setpoint Temperature Schedule"));
          return schedule;
        },
        [&](Schedule& schedule) { return setSetpointTemperatureSchedule(schedule); });
      ensureSchedule(
        openstudio::SwimmingPool_IndoorFields::PeopleSchedule, "people schedule", [&]() -> Schedule { return model().alwaysOnDiscreteSchedule(); },
        [&](Schedule& schedule) { return setPeopleSchedule(schedule); });
      ensureSchedule(
        openstudio::SwimmingPool_IndoorFields::PeopleHeatGainSchedule, "people heat gain schedule",
        [&]() -> Schedule {
          ScheduleConstant schedule(model());
          OS_ASSERT(schedule.setValue(300.0));
          OS_ASSERT(schedule.setName("Pool People Heat Gain Schedule"));
          return schedule;
        },
        [&](Schedule& schedule) { return setPeopleHeatGainSchedule(schedule); });
    }

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
