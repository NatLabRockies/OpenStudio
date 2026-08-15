/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_CONTROLLERMECHANICALVENTILATION_HPP
#define EPMODEL_CONTROLLERMECHANICALVENTILATION_HPP

#include "EPModelAPI.hpp"
#include "ModelObject.hpp"

#include "../utilities/idd/IddEnums.hpp"

#include <memory>
#include <vector>

namespace openstudio {
namespace epmodel {

  class Model;
  class Schedule;
  class ControllerOutdoorAir;

  namespace detail {
    class ControllerMechanicalVentilation_Impl;
  }

  class EPMODEL_API ControllerMechanicalVentilation : public ModelObject
  {
   public:
    explicit ControllerMechanicalVentilation(const Model& model);

    virtual ~ControllerMechanicalVentilation() override = default;
    ControllerMechanicalVentilation(const ControllerMechanicalVentilation& other) = default;
    ControllerMechanicalVentilation(ControllerMechanicalVentilation&& other) = default;
    ControllerMechanicalVentilation& operator=(const ControllerMechanicalVentilation&) = default;
    ControllerMechanicalVentilation& operator=(ControllerMechanicalVentilation&&) = default;

    static IddObjectType iddObjectType();

    static std::vector<std::string> systemOutdoorAirMethodValues();

    // Schema Alignment Notes:
    // - Canonical Counterpart: openstudio::model::ControllerMechanicalVentilation.
    // - Implemented Parity: Canonical required availability schedule API and scalar controls.
    // - EPModel Behavior: Optional inverse outdoor-air controller discovery and owner-managed zone rows support EnergyPlus topology.
    // - Field Storage: Relationships use EnergyPlus object-list pointers; load repair restores a missing or incompatible required schedule.
    // - Remaining Parity: Tighten unique outdoor-air-controller ownership and lifecycle behavior without changing the public API.
    Schedule availabilitySchedule() const;
    bool setAvailabilitySchedule(Schedule& schedule);
    bool demandControlledVentilation() const;
    bool isDemandControlledVentilationDefaulted() const;
    bool setDemandControlledVentilation(bool value);
    void setDemandControlledVentilationNoFail(bool value);
    void resetDemandControlledVentilation();

    std::string systemOutdoorAirMethod() const;
    bool isSystemOutdoorAirMethodDefaulted() const;
    bool setSystemOutdoorAirMethod(const std::string& value);
    void resetSystemOutdoorAirMethod();

    boost::optional<ControllerOutdoorAir> controllerOutdoorAir() const;

   protected:
    using ImplType = detail::ControllerMechanicalVentilation_Impl;

    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;
    friend class Model;

    explicit ControllerMechanicalVentilation(std::shared_ptr<detail::ControllerMechanicalVentilation_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
