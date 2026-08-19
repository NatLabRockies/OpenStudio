/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_SETPOINTMANAGERSINGLEZONEHEATING_HPP
#define EPMODEL_SETPOINTMANAGERSINGLEZONEHEATING_HPP

#include "EPModelAPI.hpp"
#include "SetpointManager/SetpointManager.hpp"

#include <memory>

namespace openstudio {
namespace epmodel {

  class Model;

  namespace detail {
    class SetpointManagerSingleZoneHeating_Impl;
  }

  /** \brief Sets a heating supply-air setpoint for one control zone.
   *
   * \par EnergyPlus object
   * \epobject{group-setpoint-managers.html#setpointmanagersinglezoneheating,SetpointManager:SingleZone:Heating}
   *
   * \par OpenStudio Model API
   * The corresponding OpenStudio Model class is
   * <code>openstudio::model::SetpointManagerSingleZoneHeating</code>.
   *
   * - <b>Not yet available:</b> <code>controlZone()</code>,
   *   <code>setControlZone(...)</code>, and <code>resetControlZone()</code>.
   *
   * \par Known limitations
   * No known EPModel-specific limitations.
   */
  class EPMODEL_API SetpointManagerSingleZoneHeating : public SetpointManager
  {
   public:
    explicit SetpointManagerSingleZoneHeating(const Model& model);

    virtual ~SetpointManagerSingleZoneHeating() override = default;
    SetpointManagerSingleZoneHeating(const SetpointManagerSingleZoneHeating& other) = default;
    SetpointManagerSingleZoneHeating(SetpointManagerSingleZoneHeating&& other) = default;
    SetpointManagerSingleZoneHeating& operator=(const SetpointManagerSingleZoneHeating&) = default;
    SetpointManagerSingleZoneHeating& operator=(SetpointManagerSingleZoneHeating&&) = default;

    static IddObjectType iddObjectType();

    double minimumSupplyAirTemperature() const;
    bool setMinimumSupplyAirTemperature(double minimumSupplyAirTemperature);

    double maximumSupplyAirTemperature() const;
    bool setMaximumSupplyAirTemperature(double maximumSupplyAirTemperature);

   protected:
    using ImplType = detail::SetpointManagerSingleZoneHeating_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    explicit SetpointManagerSingleZoneHeating(std::shared_ptr<detail::SetpointManagerSingleZoneHeating_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
