/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "Thermostat.hpp"
#include "Thermostat_Impl.hpp"

#include "HVACComponent/ThermalZone.hpp"
#include "HVACComponent/ThermalZone_Impl.hpp"
#include "Model.hpp"

#include <utilities/idd/IddEnums.hxx>
#include <utilities/idd/ZoneControl_Thermostat_FieldEnums.hxx>

namespace openstudio {
namespace epmodel {

  Thermostat::Thermostat(std::shared_ptr<detail::Thermostat_Impl> impl) : ModelObject(std::move(impl)) {}

  Thermostat::Thermostat(IddObjectType type, const Model& model) : ModelObject(type, model) {}

  boost::optional<ThermalZone> Thermostat::thermalZone() const {
    const auto thisThermostat = *this;
    for (const auto& zoneControl : model().getObjectsByType(openstudio::IddObjectType::ZoneControl_Thermostat, true)) {
      if (auto thermostatTarget = zoneControl.getTarget(openstudio::ZoneControl_ThermostatFields::Control1Name)) {
        if (*thermostatTarget != thisThermostat) {
          continue;
        }
        if (auto zoneTarget = zoneControl.getTarget(openstudio::ZoneControl_ThermostatFields::ZoneorZoneListName)) {
          if (auto zone = zoneTarget->optionalCast<ThermalZone>()) {
            return zone;
          }
        }
      }
    }
    return boost::none;
  }

}  // namespace epmodel
}  // namespace openstudio
