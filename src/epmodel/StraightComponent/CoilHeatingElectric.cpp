/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "StraightComponent/CoilHeatingElectric.hpp"
#include "StraightComponent/CoilHeatingElectric_Impl.hpp"

#include "Loop/AirLoopHVAC.hpp"
#include "HVACComponent/AirLoopHVACOutdoorAirSystem.hpp"
#include "Model.hpp"
#include "ModelObject.hpp"
#include "Node.hpp"
#include "Schedule/Schedule.hpp"
#include "Schedule/Schedule_Impl.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/core/Exception.hpp>
#include <utilities/core/StringHelpers.hpp>
#include <utilities/core/UUID.hpp>
#include <utilities/idd/Coil_Heating_Electric_FieldEnums.hxx>
#include <utilities/idd/IddEnums.hxx>
#include <utilities/idf/IdfObject_Impl.hpp>

namespace openstudio {
namespace epmodel {

  CoilHeatingElectric::CoilHeatingElectric(const Model& model, Schedule& schedule) : StraightComponent(CoilHeatingElectric::iddObjectType(), model) {
    OS_ASSERT(getImpl<detail::CoilHeatingElectric_Impl>());
    if (!setAvailabilitySchedule(schedule)) {
      remove();
      throw openstudio::Exception("Unable to set " + briefDescription() + "'s availability schedule to " + schedule.briefDescription() + ".");
    }
  }

  CoilHeatingElectric::CoilHeatingElectric(const Model& model) : StraightComponent(CoilHeatingElectric::iddObjectType(), model) {
    auto alwaysOn = model.alwaysOnDiscreteSchedule();
    const bool result = setAvailabilitySchedule(alwaysOn);
    OS_ASSERT(result);
  }

  CoilHeatingElectric::CoilHeatingElectric(std::shared_ptr<detail::CoilHeatingElectric_Impl> impl) : StraightComponent(std::move(impl)) {}

  IddObjectType CoilHeatingElectric::iddObjectType() {
    return IddObjectType::Coil_Heating_Electric;
  }

  bool CoilHeatingElectric::addToNode(Node& node) {
    return getImpl<detail::CoilHeatingElectric_Impl>()->addToNode(node);
  }

  Schedule CoilHeatingElectric::availabilitySchedule() const {
    return getImpl<detail::CoilHeatingElectric_Impl>()->availabilitySchedule();
  }

  bool CoilHeatingElectric::setAvailabilitySchedule(Schedule& schedule) {
    return getImpl<detail::CoilHeatingElectric_Impl>()->setAvailabilitySchedule(schedule);
  }

  boost::optional<Node> CoilHeatingElectric::temperatureSetpointNode() const {
    return getImpl<detail::CoilHeatingElectric_Impl>()->temperatureSetpointNode();
  }

  bool CoilHeatingElectric::setTemperatureSetpointNode(Node& temperatureSetpointNode) {
    return getImpl<detail::CoilHeatingElectric_Impl>()->setTemperatureSetpointNode(temperatureSetpointNode);
  }

  void CoilHeatingElectric::resetTemperatureSetpointNode() {
    getImpl<detail::CoilHeatingElectric_Impl>()->resetTemperatureSetpointNode();
  }

  double CoilHeatingElectric::efficiency() const {
    return getImpl<detail::CoilHeatingElectric_Impl>()->efficiency();
  }

  bool CoilHeatingElectric::isEfficiencyDefaulted() const {
    return getImpl<detail::CoilHeatingElectric_Impl>()->isEfficiencyDefaulted();
  }

  bool CoilHeatingElectric::setEfficiency(double efficiency) {
    return getImpl<detail::CoilHeatingElectric_Impl>()->setEfficiency(efficiency);
  }

  void CoilHeatingElectric::resetEfficiency() {
    getImpl<detail::CoilHeatingElectric_Impl>()->resetEfficiency();
  }

  boost::optional<double> CoilHeatingElectric::nominalCapacity() const {
    return getImpl<detail::CoilHeatingElectric_Impl>()->nominalCapacity();
  }

  bool CoilHeatingElectric::isNominalCapacityDefaulted() const {
    return getImpl<detail::CoilHeatingElectric_Impl>()->isNominalCapacityDefaulted();
  }

  bool CoilHeatingElectric::isNominalCapacityAutosized() const {
    return getImpl<detail::CoilHeatingElectric_Impl>()->isNominalCapacityAutosized();
  }

  bool CoilHeatingElectric::setNominalCapacity(double nominalCapacity) {
    return getImpl<detail::CoilHeatingElectric_Impl>()->setNominalCapacity(nominalCapacity);
  }

  void CoilHeatingElectric::resetNominalCapacity() {
    getImpl<detail::CoilHeatingElectric_Impl>()->resetNominalCapacity();
  }

  void CoilHeatingElectric::autosizeNominalCapacity() {
    getImpl<detail::CoilHeatingElectric_Impl>()->autosizeNominalCapacity();
  }

  boost::optional<double> CoilHeatingElectric::autosizedNominalCapacity() const {
    return getImpl<detail::CoilHeatingElectric_Impl>()->autosizedNominalCapacity();
  }

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
  namespace detail {

    namespace {

      bool isAutosized(const ModelObject_Impl& impl, int fieldIndex) {
        if (const auto value = impl.getString(fieldIndex, true)) {
          return openstudio::istringEqual(*value, "autosize");
        }
        return false;
      }

    }  // namespace

    unsigned CoilHeatingElectric_Impl::inletPort() const {
      return openstudio::Coil_Heating_ElectricFields::AirInletNodeName;
    }

    unsigned CoilHeatingElectric_Impl::outletPort() const {
      return openstudio::Coil_Heating_ElectricFields::AirOutletNodeName;
    }

    Schedule CoilHeatingElectric_Impl::availabilitySchedule() const {
      constexpr auto field = openstudio::Coil_Heating_ElectricFields::AvailabilityScheduleName;
      const auto managedValue = getObject<ModelObject>().getField(field, false);
      OS_ASSERT(managedValue && !managedValue->empty());
      const auto targetHandle = openstudio::toUUID(*managedValue);
      OS_ASSERT(!targetHandle.isNull());
      const auto value = model().getModelObject<Schedule>(targetHandle);
      OS_ASSERT(value);
      return *value;
    }

    bool CoilHeatingElectric_Impl::setAvailabilitySchedule(Schedule& schedule) {
      return ModelObject_Impl::setSchedule(openstudio::Coil_Heating_ElectricFields::AvailabilityScheduleName, "CoilHeatingElectric", "Availability",
                                           schedule);
    }

    boost::optional<Node> CoilHeatingElectric_Impl::temperatureSetpointNode() const {
      return getObject<ModelObject>().getModelObjectTarget<Node>(openstudio::Coil_Heating_ElectricFields::TemperatureSetpointNodeName);
    }

    bool CoilHeatingElectric_Impl::setTemperatureSetpointNode(Node& temperatureSetpointNode) {
      return setPointer(openstudio::Coil_Heating_ElectricFields::TemperatureSetpointNodeName, temperatureSetpointNode.handle(), false);
    }

    void CoilHeatingElectric_Impl::resetTemperatureSetpointNode() {
      OS_ASSERT(setPointer(openstudio::Coil_Heating_ElectricFields::TemperatureSetpointNodeName, openstudio::Handle(), false));
    }

    double CoilHeatingElectric_Impl::efficiency() const {
      const auto value = getDouble(openstudio::Coil_Heating_ElectricFields::Efficiency, true);
      OS_ASSERT(value);
      return *value;
    }

    bool CoilHeatingElectric_Impl::isEfficiencyDefaulted() const {
      return isEmpty(openstudio::Coil_Heating_ElectricFields::Efficiency);
    }

    bool CoilHeatingElectric_Impl::setEfficiency(double efficiency) {
      return setDouble(openstudio::Coil_Heating_ElectricFields::Efficiency, efficiency);
    }

    void CoilHeatingElectric_Impl::resetEfficiency() {
      const bool result = setString(openstudio::Coil_Heating_ElectricFields::Efficiency, "");
      OS_ASSERT(result);
    }

    boost::optional<double> CoilHeatingElectric_Impl::nominalCapacity() const {
      return getDouble(openstudio::Coil_Heating_ElectricFields::NominalCapacity, true);
    }

    bool CoilHeatingElectric_Impl::isNominalCapacityDefaulted() const {
      return isEmpty(openstudio::Coil_Heating_ElectricFields::NominalCapacity);
    }

    bool CoilHeatingElectric_Impl::isNominalCapacityAutosized() const {
      return isAutosized(*this, openstudio::Coil_Heating_ElectricFields::NominalCapacity);
    }

    bool CoilHeatingElectric_Impl::setNominalCapacity(double nominalCapacity) {
      return setDouble(openstudio::Coil_Heating_ElectricFields::NominalCapacity, nominalCapacity);
    }

    void CoilHeatingElectric_Impl::resetNominalCapacity() {
      const bool result = setString(openstudio::Coil_Heating_ElectricFields::NominalCapacity, "");
      OS_ASSERT(result);
    }

    void CoilHeatingElectric_Impl::autosizeNominalCapacity() {
      const bool result = setString(openstudio::Coil_Heating_ElectricFields::NominalCapacity, "Autosize");
      OS_ASSERT(result);
    }

    boost::optional<double> CoilHeatingElectric_Impl::autosizedNominalCapacity() const {
      // epmodel does not currently resolve autosized values from SQL results.
      return boost::none;
    }

    void CoilHeatingElectric_Impl::doCanonicalize(LoadContext& context) {
      StraightComponent_Impl::doCanonicalize(context);

      constexpr auto field = openstudio::Coil_Heating_ElectricFields::AvailabilityScheduleName;
      const auto coil = getObject<ModelObject>();
      const auto coilName = coil.nameString();
      const auto managedValue = coil.getField(field, false);
      const auto managedHandle = managedValue ? openstudio::toUUID(*managedValue) : Handle{};
      if (!managedHandle.isNull()) {
        auto schedule = model().getModelObject<Schedule>(managedHandle);
        boost::optional<Schedule> uniqueEligibleSchedule;
        bool ambiguous = false;
        if (schedule) {
          for (const auto& candidate : model().getObjectsByName(schedule->nameString(), true)) {
            if (auto namedSchedule = candidate.optionalCast<Schedule>()) {
              if (!model().canBeTarget(namedSchedule->handle(), iddObject().objectLists(field))) {
                continue;
              }
              if (uniqueEligibleSchedule) {
                ambiguous = true;
                break;
              }
              uniqueEligibleSchedule = *namedSchedule;
            }
          }
        }

        if (schedule && !ambiguous && uniqueEligibleSchedule && (uniqueEligibleSchedule->handle() == schedule->handle())
            && setAvailabilitySchedule(*schedule)) {
          return;
        }
        detail::addLoadWarning(context, "Preserved an unresolved, ambiguous, ineligible, or incompatible availability schedule on "
                                        "Coil:Heating:Electric '"
                                          + coilName + "'.");
        return;
      }

      const auto rawName = openstudio::detail::IdfObject_Impl::getString(field, false, true);
      if (rawName && !rawName->empty()) {
        boost::optional<Schedule> uniqueEligibleSchedule;
        bool ambiguous = false;
        for (const auto& candidate : model().getObjectsByName(*rawName, true)) {
          if (auto schedule = candidate.optionalCast<Schedule>()) {
            if (!model().canBeTarget(schedule->handle(), iddObject().objectLists(field))) {
              continue;
            }
            if (uniqueEligibleSchedule) {
              ambiguous = true;
              break;
            }
            uniqueEligibleSchedule = *schedule;
          }
        }

        if (uniqueEligibleSchedule && !ambiguous) {
          if (setAvailabilitySchedule(*uniqueEligibleSchedule)) {
            detail::addLoadInfo(context, "Reattached availability schedule '" + uniqueEligibleSchedule->nameString() + "' to Coil:Heating:Electric '"
                                           + coilName + "'.");
          } else {
            detail::addLoadWarning(context, "Preserved incompatible availability schedule reference '" + *rawName + "' on Coil:Heating:Electric '"
                                              + coilName + "'.");
          }
        } else {
          detail::addLoadWarning(context, "Preserved unresolved or ambiguous availability schedule reference '" + *rawName
                                            + "' on Coil:Heating:Electric '" + coilName + "'.");
        }
      } else if (context.repairEnabled()) {
        auto alwaysOn = model().alwaysOnDiscreteSchedule();
        if (setAvailabilitySchedule(alwaysOn)) {
          detail::addLoadInfo(context, "Attached the always-on availability schedule to Coil:Heating:Electric '" + coilName + "'.");
        } else {
          detail::addLoadError(context, "Failed to attach the always-on availability schedule to Coil:Heating:Electric '" + coilName + "'.");
        }
      } else {
        detail::addLoadWarning(context, "Coil:Heating:Electric '" + coilName + "' has a blank availability schedule.");
      }
    }

    bool CoilHeatingElectric_Impl::addToNode(Node& node) {
      if (node.airLoopHVACOutdoorAirSystem()) {
        return StraightComponent_Impl::addToNode(node);
      }

      auto airLoop = node.airLoopHVAC();

      if (!(airLoop && airLoop->supplyComponent(node.handle()))) {
        return false;
      }

      return StraightComponent_Impl::addToNode(node);
    }

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
