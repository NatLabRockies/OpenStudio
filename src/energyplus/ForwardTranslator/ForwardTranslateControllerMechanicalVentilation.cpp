/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Sustainable Energy, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "../ForwardTranslator.hpp"
#include "../../model/Model.hpp"
#include "../../model/Schedule.hpp"
#include "../../model/Schedule_Impl.hpp"
#include "../../model/Space.hpp"
#include "../../model/Space_Impl.hpp"
#include "../../model/ThermalZone.hpp"
#include "../../model/ThermalZone_Impl.hpp"
#include "../../model/AirLoopHVACOutdoorAirSystem.hpp"
#include "../../model/AirLoopHVACOutdoorAirSystem_Impl.hpp"
#include "../../model/ControllerMechanicalVentilation.hpp"
#include "../../model/ControllerMechanicalVentilation_Impl.hpp"
#include "../../model/DesignSpecificationOutdoorAir.hpp"
#include "../../model/DesignSpecificationOutdoorAir_Impl.hpp"
#include "../../model/ControllerOutdoorAir.hpp"
#include "../../model/ControllerOutdoorAir_Impl.hpp"
#include "../../model/AirLoopHVAC.hpp"
#include "../../model/AirLoopHVAC_Impl.hpp"
#include "../../utilities/idf/IdfExtensibleGroup.hpp"
#include "../../utilities/idf/Workspace.hpp"
#include "../../utilities/idf/WorkspaceObjectOrder.hpp"
#include "../../utilities/core/Logger.hpp"
#include <utilities/idd/Controller_MechanicalVentilation_FieldEnums.hxx>
#include <utilities/idd/IddEnums.hxx>

using namespace openstudio::model;

namespace openstudio {

namespace energyplus {

  boost::optional<IdfObject> ForwardTranslator::translateControllerMechanicalVentilation(ControllerMechanicalVentilation& modelObject) {

    // NOTE: don't translate it if it has no DSOA
    if (!modelObject.hasZonesWithDesignSpecificationOutdoorAir()) {
      return boost::none;
    }

    OptionalString s;
    OptionalDouble d;
    OptionalModelObject temp;

    IdfObject idfObject(IddObjectType::Controller_MechanicalVentilation);

    // Name
    s = modelObject.name();
    if (s) {
      idfObject.setName(*s);
    }

    // Availability Schedule
    // If there is a ControllerOutdoorAir::minimumOutdoorAirSchedule
    // then use that for the ControllerMechanicalVentilation::availabilitySchedule
    // Note that this scheme will not support fractions (schedule values above 0) because anything greater than 0 will
    // make the mechanical ventilation controller avaiable and thus taking precedence.
    bool useAvailabiltySchedule = true;
    auto availabilitySchedule = modelObject.availabilitySchedule();

    // alwaysOnDiscreteSchedule is the default availability schedule for the mechanical ventilation controller
    // if the default is still in place BUT the user has defined a minimumOutdoorAirSchedule for the oa controller,
    // then use the minimumOutdoorAirSchedule for the mechanical ventilation controller availability schedule
    // The minimumOutdoorAirSchedule will not do its job while the controller mechanical ventilation object is available.
    if (availabilitySchedule == modelObject.model().alwaysOnDiscreteSchedule()) {
      if (auto minOASchedule = modelObject.controllerOutdoorAir().minimumOutdoorAirSchedule()) {
        auto _schedule = translateAndMapModelObject(minOASchedule.get());
        OS_ASSERT(_schedule);
        idfObject.setString(Controller_MechanicalVentilationFields::AvailabilityScheduleName, _schedule->name().get());
        useAvailabiltySchedule = false;
      }
    }

    if (useAvailabiltySchedule) {
      boost::optional<IdfObject> availabilityScheduleIdf = translateAndMapModelObject(availabilitySchedule);
      OS_ASSERT(availabilityScheduleIdf);
      idfObject.setString(openstudio::Controller_MechanicalVentilationFields::AvailabilityScheduleName, availabilityScheduleIdf->name().get());
    }

    // Demand Controlled Ventilation
    if (modelObject.demandControlledVentilation()) {
      idfObject.setString(openstudio::Controller_MechanicalVentilationFields::DemandControlledVentilation, "Yes");
    } else {
      idfObject.setString(openstudio::Controller_MechanicalVentilationFields::DemandControlledVentilation, "No");
    }

    // System Outdoor Air Method
    s = modelObject.systemOutdoorAirMethod();
    if (s) {
      idfObject.setString(openstudio::Controller_MechanicalVentilationFields::SystemOutdoorAirMethod, s.get());
    }

    // Extensible Groups for DSOAs are no longer pushed in translateSizingZone to retain order of the file, because:
    // 1) Thermal Zones are translated before AirLoopHVACs, so we guarantee proper order (unless we mess something up, like adding a new always
    // translated object early on that will call it)
    // 2) Doing it in translateSizingZone means that it will NOT be written if the Sizing:Zone isn't, for eg when you have no design days
    //    but that is a valid use case
    auto oa_controller = modelObject.controllerOutdoorAir();
    if (auto oa_sys_ = oa_controller.airLoopHVACOutdoorAirSystem()) {
      if (auto a_ = oa_sys_->airLoopHVAC()) {
        for (const auto& z : a_->thermalZones()) {
          if (auto dsoaOrList_ = getOrCreateThermalZoneDSOA(z)) {
            IdfExtensibleGroup eg = idfObject.pushExtensibleGroup({z.nameString(), dsoaOrList_->nameString(), zoneDSZADName(z).value_or("")});
          }
        }
      }
    }

    m_idfObjects.push_back(idfObject);
    return boost::optional<IdfObject>(idfObject);
  }

}  // namespace energyplus

}  // namespace openstudio
