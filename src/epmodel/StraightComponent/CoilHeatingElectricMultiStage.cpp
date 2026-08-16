/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "StraightComponent/CoilHeatingElectricMultiStage.hpp"
#include "StraightComponent/CoilHeatingElectricMultiStage_Impl.hpp"

#include "Loop/AirLoopHVAC.hpp"
#include "Model.hpp"
#include "ModelObject.hpp"
#include "Schedule/Schedule.hpp"
#include "Schedule/Schedule_Impl.hpp"
#include "StraightComponent/Node.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/core/UUID.hpp>
#include <utilities/idd/Coil_Heating_Electric_MultiStage_FieldEnums.hxx>
#include <utilities/idd/IddEnums.hxx>
#include <utilities/idf/IdfObject_Impl.hpp>

namespace openstudio {
namespace epmodel {

  CoilHeatingElectricMultiStage::CoilHeatingElectricMultiStage(const Model& model)
    : StraightComponent(CoilHeatingElectricMultiStage::iddObjectType(), model) {
    // Keep required scalar field populated for strict non-optional getter behavior.
    auto availabilitySchedule = model.alwaysOnDiscreteSchedule();
    OS_ASSERT(getImpl<detail::CoilHeatingElectricMultiStage_Impl>()->setAvailabilitySchedule(availabilitySchedule));
    OS_ASSERT(getImpl<detail::CoilHeatingElectricMultiStage_Impl>()->setNumberOfStages(1u));
  }

  CoilHeatingElectricMultiStage::CoilHeatingElectricMultiStage(std::shared_ptr<detail::CoilHeatingElectricMultiStage_Impl> impl)
    : StraightComponent(std::move(impl)) {}

  IddObjectType CoilHeatingElectricMultiStage::iddObjectType() {
    return IddObjectType::Coil_Heating_Electric_MultiStage;
  }

  bool CoilHeatingElectricMultiStage::addToNode(Node& node) {
    return getImpl<detail::CoilHeatingElectricMultiStage_Impl>()->addToNode(node);
  }

  Schedule CoilHeatingElectricMultiStage::availabilitySchedule() const {
    return getImpl<detail::CoilHeatingElectricMultiStage_Impl>()->availabilitySchedule();
  }

  bool CoilHeatingElectricMultiStage::setAvailabilitySchedule(Schedule& schedule) {
    return getImpl<detail::CoilHeatingElectricMultiStage_Impl>()->setAvailabilitySchedule(schedule);
  }

  unsigned CoilHeatingElectricMultiStage::numberOfStages() const {
    return getImpl<detail::CoilHeatingElectricMultiStage_Impl>()->numberOfStages();
  }

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
  namespace detail {

    unsigned CoilHeatingElectricMultiStage_Impl::inletPort() const {
      return openstudio::Coil_Heating_Electric_MultiStageFields::AirInletNodeName;
    }

    unsigned CoilHeatingElectricMultiStage_Impl::outletPort() const {
      return openstudio::Coil_Heating_Electric_MultiStageFields::AirOutletNodeName;
    }

    bool CoilHeatingElectricMultiStage_Impl::addToNode(Node& node) {
      return false;
    }

    Schedule CoilHeatingElectricMultiStage_Impl::availabilitySchedule() const {
      constexpr auto field = openstudio::Coil_Heating_Electric_MultiStageFields::AvailabilityScheduleName;
      const auto managedValue = getObject<ModelObject>().getField(field, false);
      OS_ASSERT(managedValue && !managedValue->empty());
      const auto targetHandle = openstudio::toUUID(*managedValue);
      OS_ASSERT(!targetHandle.isNull());
      const auto value = model().getModelObject<Schedule>(targetHandle);
      OS_ASSERT(value);
      return *value;
    }

    bool CoilHeatingElectricMultiStage_Impl::setAvailabilitySchedule(Schedule& schedule) {
      return ModelObject_Impl::setSchedule(openstudio::Coil_Heating_Electric_MultiStageFields::AvailabilityScheduleName,
                                           "CoilHeatingElectricMultiStage", "Availability Schedule", schedule);
    }

    unsigned CoilHeatingElectricMultiStage_Impl::numberOfStages() const {
      const auto value = getUnsigned(openstudio::Coil_Heating_Electric_MultiStageFields::NumberofStages, true);
      OS_ASSERT(value);
      return *value;
    }

    bool CoilHeatingElectricMultiStage_Impl::setNumberOfStages(unsigned numberOfStages) {
      return setUnsigned(openstudio::Coil_Heating_Electric_MultiStageFields::NumberofStages, numberOfStages);
    }

    void CoilHeatingElectricMultiStage_Impl::doCanonicalize(LoadContext& context) {
      StraightComponent_Impl::doCanonicalize(context);

      constexpr auto field = openstudio::Coil_Heating_Electric_MultiStageFields::AvailabilityScheduleName;
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
                                        "Coil:Heating:Electric:MultiStage '"
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
            detail::addLoadInfo(context, "Reattached availability schedule '" + uniqueEligibleSchedule->nameString()
                                           + "' to Coil:Heating:Electric:MultiStage '" + coilName + "'.");
          } else {
            detail::addLoadWarning(context, "Preserved incompatible availability schedule reference '" + *rawName
                                              + "' on Coil:Heating:Electric:MultiStage '" + coilName + "'.");
          }
        } else {
          detail::addLoadWarning(context, "Preserved unresolved or ambiguous availability schedule reference '" + *rawName
                                            + "' on Coil:Heating:Electric:MultiStage '" + coilName + "'.");
        }
      } else if (context.repairEnabled()) {
        auto alwaysOn = model().alwaysOnDiscreteSchedule();
        if (setAvailabilitySchedule(alwaysOn)) {
          detail::addLoadInfo(context, "Attached the always-on availability schedule to Coil:Heating:Electric:MultiStage '" + coilName + "'.");
        } else {
          detail::addLoadError(context,
                               "Failed to attach the always-on availability schedule to Coil:Heating:Electric:MultiStage '" + coilName + "'.");
        }
      } else {
        detail::addLoadWarning(context, "Coil:Heating:Electric:MultiStage '" + coilName + "' has a blank availability schedule.");
      }
    }

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
