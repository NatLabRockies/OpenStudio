/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_SETPOINTMANAGERSINGLEZONECOOLING_HPP
#define EPMODEL_SETPOINTMANAGERSINGLEZONECOOLING_HPP

#include "EPModelAPI.hpp"
#include "SetpointManager/SetpointManager.hpp"

#include <memory>

namespace openstudio {
namespace epmodel {

  class Model;

  namespace detail {
    class SetpointManagerSingleZoneCooling_Impl;
  }

  /** \brief Sets a cooling supply-air setpoint for one control zone.
   *
   * \par EnergyPlus object
   * \epobject{group-setpoint-managers.html#setpointmanagersinglezonecooling,SetpointManager:SingleZone:Cooling}
   *
   * \par OpenStudio Model API
   * The corresponding OpenStudio Model class is
   * <code>openstudio::model::SetpointManagerSingleZoneCooling</code>.
   *
   * - <b>Not yet available:</b> <code>controlZone()</code>,
   *   <code>setControlZone(...)</code>, and <code>resetControlZone()</code>.
   *
   * \par Known limitations
   * No known EPModel-specific limitations.
   */
  class EPMODEL_API SetpointManagerSingleZoneCooling : public SetpointManager
  {
   public:
    explicit SetpointManagerSingleZoneCooling(const Model& model);

    virtual ~SetpointManagerSingleZoneCooling() override = default;
    SetpointManagerSingleZoneCooling(const SetpointManagerSingleZoneCooling& other) = default;
    SetpointManagerSingleZoneCooling(SetpointManagerSingleZoneCooling&& other) = default;
    SetpointManagerSingleZoneCooling& operator=(const SetpointManagerSingleZoneCooling&) = default;
    SetpointManagerSingleZoneCooling& operator=(SetpointManagerSingleZoneCooling&&) = default;

    static IddObjectType iddObjectType();

    double minimumSupplyAirTemperature() const;
    bool setMinimumSupplyAirTemperature(double minimumSupplyAirTemperature);

    double maximumSupplyAirTemperature() const;
    bool setMaximumSupplyAirTemperature(double maximumSupplyAirTemperature);

   protected:
    using ImplType = detail::SetpointManagerSingleZoneCooling_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    explicit SetpointManagerSingleZoneCooling(std::shared_ptr<detail::SetpointManagerSingleZoneCooling_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
