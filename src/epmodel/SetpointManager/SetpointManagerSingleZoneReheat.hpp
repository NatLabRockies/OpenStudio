/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_SETPOINTMANAGERSINGLEZONEREHEAT_HPP
#define EPMODEL_SETPOINTMANAGERSINGLEZONEREHEAT_HPP

#include "EPModelAPI.hpp"
#include "SetpointManager/SetpointManager.hpp"

#include <memory>
#include <vector>

namespace openstudio {
namespace epmodel {

  class Model;
  class ThermalZone;

  namespace detail {
    class SetpointManagerSingleZoneReheat_Impl;
  }

  /** \brief Sets a reheat supply-air setpoint for one control zone.
   *
   * \par EnergyPlus object
   * \epobject{group-setpoint-managers.html#setpointmanagersinglezonereheat,SetpointManager:SingleZone:Reheat}
   *
   * \par Important behavior
   * When added to an air-loop node, EPModel attempts to infer the first demand-zone control zone and its zone-air inlet node.
   *
   * \par OpenStudio Model API
   * The corresponding OpenStudio Model class is
   * <code>openstudio::model::SetpointManagerSingleZoneReheat</code>.
   *
   * - <b>Not yet available:</b> <code>setControlZone(...)</code> and
   *   <code>resetControlZone()</code>.
   *
   * \par Known limitations
   * No known EPModel-specific limitations.
   */
  class EPMODEL_API SetpointManagerSingleZoneReheat : public SetpointManager
  {
   public:
    explicit SetpointManagerSingleZoneReheat(const Model& model);

    virtual ~SetpointManagerSingleZoneReheat() override = default;
    SetpointManagerSingleZoneReheat(const SetpointManagerSingleZoneReheat& other) = default;
    SetpointManagerSingleZoneReheat(SetpointManagerSingleZoneReheat&& other) = default;
    SetpointManagerSingleZoneReheat& operator=(const SetpointManagerSingleZoneReheat&) = default;
    SetpointManagerSingleZoneReheat& operator=(SetpointManagerSingleZoneReheat&&) = default;

    static IddObjectType iddObjectType();

    static std::vector<std::string> controlVariableValues();

    double minimumSupplyAirTemperature() const;
    bool setMinimumSupplyAirTemperature(double minimumSupplyAirTemperature);

    double maximumSupplyAirTemperature() const;
    bool setMaximumSupplyAirTemperature(double maximumSupplyAirTemperature);

    boost::optional<ThermalZone> controlZone() const;

   protected:
    using ImplType = detail::SetpointManagerSingleZoneReheat_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    explicit SetpointManagerSingleZoneReheat(std::shared_ptr<detail::SetpointManagerSingleZoneReheat_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
