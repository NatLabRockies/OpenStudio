/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_SETPOINTMANAGERSINGLEZONEONESTAGEHEATING_HPP
#define EPMODEL_SETPOINTMANAGERSINGLEZONEONESTAGEHEATING_HPP

#include "EPModelAPI.hpp"
#include "SetpointManager/SetpointManager.hpp"

#include <memory>
#include <vector>

namespace openstudio {
namespace epmodel {

  class Model;

  namespace detail {
    class SetpointManagerSingleZoneOneStageHeating_Impl;
  }

  /** \brief Sets one-stage heating supply-air setpoints for one control zone.
   *
   * \par EnergyPlus object
   * \epobject{group-setpoint-managers.html#setpointmanagersinglezoneonestageheating,SetpointManager:SingleZone:OneStageHeating}
   *
   * \par OpenStudio Model API
   * The corresponding OpenStudio Model class is
   * <code>openstudio::model::SetpointManagerSingleZoneOneStageHeating</code>.
   *
   * - <b>Not yet available:</b> <code>controlZone()</code>,
   *   <code>setControlZone(...)</code>, and <code>resetControlZone()</code>.
   *
   * \par Known limitations
   * No known EPModel-specific limitations.
   */
  class EPMODEL_API SetpointManagerSingleZoneOneStageHeating : public SetpointManager
  {
   public:
    explicit SetpointManagerSingleZoneOneStageHeating(const Model& model);

    virtual ~SetpointManagerSingleZoneOneStageHeating() override = default;
    SetpointManagerSingleZoneOneStageHeating(const SetpointManagerSingleZoneOneStageHeating& other) = default;
    SetpointManagerSingleZoneOneStageHeating(SetpointManagerSingleZoneOneStageHeating&& other) = default;
    SetpointManagerSingleZoneOneStageHeating& operator=(const SetpointManagerSingleZoneOneStageHeating&) = default;
    SetpointManagerSingleZoneOneStageHeating& operator=(SetpointManagerSingleZoneOneStageHeating&&) = default;

    static IddObjectType iddObjectType();
    static std::vector<std::string> controlVariableValues();

    std::string controlVariable() const;
    bool setControlVariable(const std::string& controlVariable);

    double heatingStageOnSupplyAirSetpointTemperature() const;
    bool setHeatingStageOnSupplyAirSetpointTemperature(double heatingStageOnSupplyAirSetpointTemperature);

    double heatingStageOffSupplyAirSetpointTemperature() const;
    bool setHeatingStageOffSupplyAirSetpointTemperature(double heatingStageOffSupplyAirSetpointTemperature);

   protected:
    using ImplType = detail::SetpointManagerSingleZoneOneStageHeating_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    explicit SetpointManagerSingleZoneOneStageHeating(std::shared_ptr<detail::SetpointManagerSingleZoneOneStageHeating_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
