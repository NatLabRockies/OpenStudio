/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "ZoneControlHumidistat.hpp"
#include "ZoneControlHumidistat_Impl.hpp"

#include "HVACComponent/ThermalZone.hpp"
#include "HVACComponent/ThermalZone_Impl.hpp"
#include "Model.hpp"
#include "Schedule/Schedule.hpp"
#include "Schedule/Schedule_Impl.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/idd/IddEnums.hxx>
#include <utilities/idd/ZoneControl_Humidistat_FieldEnums.hxx>

namespace openstudio {
namespace epmodel {

  ZoneControlHumidistat::ZoneControlHumidistat(const Model& model) : ModelObject(ZoneControlHumidistat::iddObjectType(), model) {}

  ZoneControlHumidistat::ZoneControlHumidistat(std::shared_ptr<detail::ZoneControlHumidistat_Impl> impl) : ModelObject(std::move(impl)) {}

  IddObjectType ZoneControlHumidistat::iddObjectType() {
    return {IddObjectType::ZoneControl_Humidistat};
  }

  boost::optional<ThermalZone> ZoneControlHumidistat::controlledZone() const {
    return getImpl<detail::ZoneControlHumidistat_Impl>()->controlledZone();
  }

  boost::optional<Schedule> ZoneControlHumidistat::humidifyingRelativeHumiditySetpointSchedule() const {
    return getImpl<detail::ZoneControlHumidistat_Impl>()->humidifyingRelativeHumiditySetpointSchedule();
  }

  boost::optional<Schedule> ZoneControlHumidistat::dehumidifyingRelativeHumiditySetpointSchedule() const {
    return getImpl<detail::ZoneControlHumidistat_Impl>()->dehumidifyingRelativeHumiditySetpointSchedule();
  }

  bool ZoneControlHumidistat::setHumidifyingRelativeHumiditySetpointSchedule(Schedule& schedule) {
    return getImpl<detail::ZoneControlHumidistat_Impl>()->setHumidifyingRelativeHumiditySetpointSchedule(schedule);
  }

  bool ZoneControlHumidistat::setDehumidifyingRelativeHumiditySetpointSchedule(Schedule& schedule) {
    return getImpl<detail::ZoneControlHumidistat_Impl>()->setDehumidifyingRelativeHumiditySetpointSchedule(schedule);
  }

  void ZoneControlHumidistat::resetHumidifyingRelativeHumiditySetpointSchedule() {
    getImpl<detail::ZoneControlHumidistat_Impl>()->resetHumidifyingRelativeHumiditySetpointSchedule();
  }

  void ZoneControlHumidistat::resetDehumidifyingRelativeHumiditySetpointSchedule() {
    getImpl<detail::ZoneControlHumidistat_Impl>()->resetDehumidifyingRelativeHumiditySetpointSchedule();
  }

  namespace detail {

    boost::optional<openstudio::epmodel::ThermalZone> ZoneControlHumidistat_Impl::controlledZone() const {
      const auto humidistat = getObject<openstudio::epmodel::ZoneControlHumidistat>();
      for (const auto& zone : model().getConcreteModelObjects<openstudio::epmodel::ThermalZone>()) {
        if (auto candidate = zone.zoneControlHumidistat(); candidate && (*candidate == humidistat)) {
          return zone;
        }
      }
      return boost::none;
    }

    boost::optional<openstudio::epmodel::Schedule> ZoneControlHumidistat_Impl::humidifyingRelativeHumiditySetpointSchedule() const {
      return getObject<ModelObject>().getModelObjectTarget<openstudio::epmodel::Schedule>(
        openstudio::ZoneControl_HumidistatFields::HumidifyingRelativeHumiditySetpointScheduleName);
    }

    boost::optional<openstudio::epmodel::Schedule> ZoneControlHumidistat_Impl::dehumidifyingRelativeHumiditySetpointSchedule() const {
      return getObject<ModelObject>().getModelObjectTarget<openstudio::epmodel::Schedule>(
        openstudio::ZoneControl_HumidistatFields::DehumidifyingRelativeHumiditySetpointScheduleName);
    }

    bool ZoneControlHumidistat_Impl::setHumidifyingRelativeHumiditySetpointSchedule(openstudio::epmodel::Schedule& schedule) {
      return setSchedule(openstudio::ZoneControl_HumidistatFields::HumidifyingRelativeHumiditySetpointScheduleName, "ZoneControlHumidistat",
                         "Humidifying Relative Humidity Setpoint", schedule);
    }

    bool ZoneControlHumidistat_Impl::setDehumidifyingRelativeHumiditySetpointSchedule(openstudio::epmodel::Schedule& schedule) {
      return setSchedule(openstudio::ZoneControl_HumidistatFields::DehumidifyingRelativeHumiditySetpointScheduleName, "ZoneControlHumidistat",
                         "Dehumidifying Relative Humidity Setpoint", schedule);
    }

    void ZoneControlHumidistat_Impl::resetHumidifyingRelativeHumiditySetpointSchedule() {
      OS_ASSERT(setPointer(openstudio::ZoneControl_HumidistatFields::HumidifyingRelativeHumiditySetpointScheduleName, openstudio::Handle(), false));
    }

    void ZoneControlHumidistat_Impl::resetDehumidifyingRelativeHumiditySetpointSchedule() {
      OS_ASSERT(setPointer(openstudio::ZoneControl_HumidistatFields::DehumidifyingRelativeHumiditySetpointScheduleName, openstudio::Handle(), false));
    }

  }  // namespace detail

}  // namespace epmodel
}  // namespace openstudio
