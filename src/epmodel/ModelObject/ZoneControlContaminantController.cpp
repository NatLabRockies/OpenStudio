/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "ZoneControlContaminantController.hpp"
#include "ZoneControlContaminantController_Impl.hpp"

#include "HVACComponent/ThermalZone.hpp"
#include "HVACComponent/ThermalZone_Impl.hpp"
#include "Model.hpp"
#include "Schedule/Schedule.hpp"
#include "Schedule/Schedule_Impl.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/idd/IddEnums.hxx>
#include <utilities/idd/ZoneControl_ContaminantController_FieldEnums.hxx>
#include <utilities/idf/IdfObject_Impl.hpp>

namespace openstudio {
namespace epmodel {

  ZoneControlContaminantController::ZoneControlContaminantController(const Model& model)
    : ModelObject(ZoneControlContaminantController::iddObjectType(), model) {}

  ZoneControlContaminantController::ZoneControlContaminantController(std::shared_ptr<detail::ZoneControlContaminantController_Impl> impl)
    : ModelObject(std::move(impl)) {}

  IddObjectType ZoneControlContaminantController::iddObjectType() {
    return IddObjectType::ZoneControl_ContaminantController;
  }

  boost::optional<ThermalZone> ZoneControlContaminantController::controlledZone() const {
    return getImpl<detail::ZoneControlContaminantController_Impl>()->controlledZone();
  }

  boost::optional<Schedule> ZoneControlContaminantController::carbonDioxideControlAvailabilitySchedule() const {
    return getImpl<detail::ZoneControlContaminantController_Impl>()->carbonDioxideControlAvailabilitySchedule();
  }

  bool ZoneControlContaminantController::setCarbonDioxideControlAvailabilitySchedule(Schedule& schedule) {
    return getImpl<detail::ZoneControlContaminantController_Impl>()->setCarbonDioxideControlAvailabilitySchedule(schedule);
  }

  void ZoneControlContaminantController::resetCarbonDioxideControlAvailabilitySchedule() {
    getImpl<detail::ZoneControlContaminantController_Impl>()->resetCarbonDioxideControlAvailabilitySchedule();
  }

  boost::optional<Schedule> ZoneControlContaminantController::carbonDioxideSetpointSchedule() const {
    return getImpl<detail::ZoneControlContaminantController_Impl>()->carbonDioxideSetpointSchedule();
  }

  bool ZoneControlContaminantController::setCarbonDioxideSetpointSchedule(Schedule& schedule) {
    return getImpl<detail::ZoneControlContaminantController_Impl>()->setCarbonDioxideSetpointSchedule(schedule);
  }

  void ZoneControlContaminantController::resetCarbonDioxideSetpointSchedule() {
    getImpl<detail::ZoneControlContaminantController_Impl>()->resetCarbonDioxideSetpointSchedule();
  }

  boost::optional<Schedule> ZoneControlContaminantController::minimumCarbonDioxideConcentrationSchedule() const {
    return getImpl<detail::ZoneControlContaminantController_Impl>()->minimumCarbonDioxideConcentrationSchedule();
  }

  bool ZoneControlContaminantController::setMinimumCarbonDioxideConcentrationSchedule(Schedule& schedule) {
    return getImpl<detail::ZoneControlContaminantController_Impl>()->setMinimumCarbonDioxideConcentrationSchedule(schedule);
  }

  void ZoneControlContaminantController::resetMinimumCarbonDioxideConcentrationSchedule() {
    getImpl<detail::ZoneControlContaminantController_Impl>()->resetMinimumCarbonDioxideConcentrationSchedule();
  }

  boost::optional<Schedule> ZoneControlContaminantController::genericContaminantControlAvailabilitySchedule() const {
    return getImpl<detail::ZoneControlContaminantController_Impl>()->genericContaminantControlAvailabilitySchedule();
  }

  bool ZoneControlContaminantController::setGenericContaminantControlAvailabilitySchedule(Schedule& schedule) {
    return getImpl<detail::ZoneControlContaminantController_Impl>()->setGenericContaminantControlAvailabilitySchedule(schedule);
  }

  void ZoneControlContaminantController::resetGenericContaminantControlAvailabilitySchedule() {
    getImpl<detail::ZoneControlContaminantController_Impl>()->resetGenericContaminantControlAvailabilitySchedule();
  }

  boost::optional<Schedule> ZoneControlContaminantController::genericContaminantSetpointSchedule() const {
    return getImpl<detail::ZoneControlContaminantController_Impl>()->genericContaminantSetpointSchedule();
  }

  bool ZoneControlContaminantController::setGenericContaminantSetpointSchedule(Schedule& schedule) {
    return getImpl<detail::ZoneControlContaminantController_Impl>()->setGenericContaminantSetpointSchedule(schedule);
  }

  void ZoneControlContaminantController::resetGenericContaminantSetpointSchedule() {
    getImpl<detail::ZoneControlContaminantController_Impl>()->resetGenericContaminantSetpointSchedule();
  }

  namespace detail {

    boost::optional<openstudio::epmodel::ThermalZone> ZoneControlContaminantController_Impl::controlledZone() const {
      return getObject<ModelObject>().getModelObjectTarget<openstudio::epmodel::ThermalZone>(
        openstudio::ZoneControl_ContaminantControllerFields::ZoneName);
    }

    boost::optional<openstudio::epmodel::Schedule> ZoneControlContaminantController_Impl::carbonDioxideControlAvailabilitySchedule() const {
      return getObject<ModelObject>().getModelObjectTarget<openstudio::epmodel::Schedule>(
        openstudio::ZoneControl_ContaminantControllerFields::CarbonDioxideControlAvailabilityScheduleName);
    }

    bool ZoneControlContaminantController_Impl::setCarbonDioxideControlAvailabilitySchedule(openstudio::epmodel::Schedule& schedule) {
      return setSchedule(openstudio::ZoneControl_ContaminantControllerFields::CarbonDioxideControlAvailabilityScheduleName,
                         "ZoneControlContaminantController", "Carbon Dioxide Control Availability", schedule);
    }

    void ZoneControlContaminantController_Impl::resetCarbonDioxideControlAvailabilitySchedule() {
      constexpr auto field = openstudio::ZoneControl_ContaminantControllerFields::CarbonDioxideControlAvailabilityScheduleName;
      OS_ASSERT(setPointer(field, Handle(), false));
      OS_ASSERT(openstudio::detail::IdfObject_Impl::setString(field, "", false));
    }

    boost::optional<openstudio::epmodel::Schedule> ZoneControlContaminantController_Impl::carbonDioxideSetpointSchedule() const {
      return getObject<ModelObject>().getModelObjectTarget<openstudio::epmodel::Schedule>(
        openstudio::ZoneControl_ContaminantControllerFields::CarbonDioxideSetpointScheduleName);
    }

    bool ZoneControlContaminantController_Impl::setCarbonDioxideSetpointSchedule(openstudio::epmodel::Schedule& schedule) {
      return setSchedule(openstudio::ZoneControl_ContaminantControllerFields::CarbonDioxideSetpointScheduleName, "ZoneControlContaminantController",
                         "Carbon Dioxide Setpoint", schedule);
    }

    void ZoneControlContaminantController_Impl::resetCarbonDioxideSetpointSchedule() {
      constexpr auto field = openstudio::ZoneControl_ContaminantControllerFields::CarbonDioxideSetpointScheduleName;
      OS_ASSERT(setPointer(field, Handle(), false));
      OS_ASSERT(openstudio::detail::IdfObject_Impl::setString(field, "", false));
    }

    boost::optional<openstudio::epmodel::Schedule> ZoneControlContaminantController_Impl::minimumCarbonDioxideConcentrationSchedule() const {
      return getObject<ModelObject>().getModelObjectTarget<openstudio::epmodel::Schedule>(
        openstudio::ZoneControl_ContaminantControllerFields::MinimumCarbonDioxideConcentrationScheduleName);
    }

    bool ZoneControlContaminantController_Impl::setMinimumCarbonDioxideConcentrationSchedule(openstudio::epmodel::Schedule& schedule) {
      return setSchedule(openstudio::ZoneControl_ContaminantControllerFields::MinimumCarbonDioxideConcentrationScheduleName,
                         "ZoneControlContaminantController", "Minimum Carbon Dioxide Concentration", schedule);
    }

    void ZoneControlContaminantController_Impl::resetMinimumCarbonDioxideConcentrationSchedule() {
      constexpr auto field = openstudio::ZoneControl_ContaminantControllerFields::MinimumCarbonDioxideConcentrationScheduleName;
      OS_ASSERT(setPointer(field, Handle(), false));
      OS_ASSERT(openstudio::detail::IdfObject_Impl::setString(field, "", false));
    }

    boost::optional<openstudio::epmodel::Schedule> ZoneControlContaminantController_Impl::genericContaminantControlAvailabilitySchedule() const {
      return getObject<ModelObject>().getModelObjectTarget<openstudio::epmodel::Schedule>(
        openstudio::ZoneControl_ContaminantControllerFields::GenericContaminantControlAvailabilityScheduleName);
    }

    bool ZoneControlContaminantController_Impl::setGenericContaminantControlAvailabilitySchedule(openstudio::epmodel::Schedule& schedule) {
      return setSchedule(openstudio::ZoneControl_ContaminantControllerFields::GenericContaminantControlAvailabilityScheduleName,
                         "ZoneControlContaminantController", "Generic Contaminant Control Availability", schedule);
    }

    void ZoneControlContaminantController_Impl::resetGenericContaminantControlAvailabilitySchedule() {
      constexpr auto field = openstudio::ZoneControl_ContaminantControllerFields::GenericContaminantControlAvailabilityScheduleName;
      OS_ASSERT(setPointer(field, Handle(), false));
      OS_ASSERT(openstudio::detail::IdfObject_Impl::setString(field, "", false));
    }

    boost::optional<openstudio::epmodel::Schedule> ZoneControlContaminantController_Impl::genericContaminantSetpointSchedule() const {
      return getObject<ModelObject>().getModelObjectTarget<openstudio::epmodel::Schedule>(
        openstudio::ZoneControl_ContaminantControllerFields::GenericContaminantSetpointScheduleName);
    }

    bool ZoneControlContaminantController_Impl::setGenericContaminantSetpointSchedule(openstudio::epmodel::Schedule& schedule) {
      return setSchedule(openstudio::ZoneControl_ContaminantControllerFields::GenericContaminantSetpointScheduleName,
                         "ZoneControlContaminantController", "Generic Contaminant Setpoint", schedule);
    }

    void ZoneControlContaminantController_Impl::resetGenericContaminantSetpointSchedule() {
      constexpr auto field = openstudio::ZoneControl_ContaminantControllerFields::GenericContaminantSetpointScheduleName;
      OS_ASSERT(setPointer(field, Handle(), false));
      OS_ASSERT(openstudio::detail::IdfObject_Impl::setString(field, "", false));
    }

  }  // namespace detail

}  // namespace epmodel
}  // namespace openstudio
