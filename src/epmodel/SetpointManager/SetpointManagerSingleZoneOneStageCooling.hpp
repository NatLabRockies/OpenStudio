/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_SETPOINTMANAGERSINGLEZONEONESTAGECOOLING_HPP
#define EPMODEL_SETPOINTMANAGERSINGLEZONEONESTAGECOOLING_HPP

#include "EPModelAPI.hpp"
#include "SetpointManager/SetpointManager.hpp"

#include <memory>
#include <vector>

namespace openstudio {
namespace epmodel {

  class Model;

  namespace detail {
    class SetpointManagerSingleZoneOneStageCooling_Impl;
  }

  /** \brief Sets one-stage cooling supply-air setpoints for one control zone.
   *
   * \par EnergyPlus object
   * \epobject{group-setpoint-managers.html#setpointmanagersinglezoneonestagecooling,SetpointManager:SingleZone:OneStageCooling}
   *
   * \par OpenStudio Model API
   * The corresponding OpenStudio Model class is
   * <code>openstudio::model::SetpointManagerSingleZoneOneStageCooling</code>.
   *
   * - <b>Not yet available:</b> <code>controlZone()</code>,
   *   <code>setControlZone(...)</code>, and <code>resetControlZone()</code>.
   *
   * \par Known limitations
   * No known EPModel-specific limitations.
   */
  class EPMODEL_API SetpointManagerSingleZoneOneStageCooling : public SetpointManager
  {
   public:
    explicit SetpointManagerSingleZoneOneStageCooling(const Model& model);

    virtual ~SetpointManagerSingleZoneOneStageCooling() override = default;
    SetpointManagerSingleZoneOneStageCooling(const SetpointManagerSingleZoneOneStageCooling& other) = default;
    SetpointManagerSingleZoneOneStageCooling(SetpointManagerSingleZoneOneStageCooling&& other) = default;
    SetpointManagerSingleZoneOneStageCooling& operator=(const SetpointManagerSingleZoneOneStageCooling&) = default;
    SetpointManagerSingleZoneOneStageCooling& operator=(SetpointManagerSingleZoneOneStageCooling&&) = default;

    static IddObjectType iddObjectType();
    static std::vector<std::string> controlVariableValues();

    std::string controlVariable() const;
    bool setControlVariable(const std::string& controlVariable);

    double coolingStageOnSupplyAirSetpointTemperature() const;
    bool setCoolingStageOnSupplyAirSetpointTemperature(double coolingStageOnSupplyAirSetpointTemperature);

    double coolingStageOffSupplyAirSetpointTemperature() const;
    bool setCoolingStageOffSupplyAirSetpointTemperature(double coolingStageOffSupplyAirSetpointTemperature);

   protected:
    using ImplType = detail::SetpointManagerSingleZoneOneStageCooling_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    explicit SetpointManagerSingleZoneOneStageCooling(std::shared_ptr<detail::SetpointManagerSingleZoneOneStageCooling_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
