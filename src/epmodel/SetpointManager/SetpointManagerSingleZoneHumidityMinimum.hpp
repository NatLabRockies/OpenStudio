/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_SETPOINTMANAGERSINGLEZONEHUMIDITYMINIMUM_HPP
#define EPMODEL_SETPOINTMANAGERSINGLEZONEHUMIDITYMINIMUM_HPP

#include "EPModelAPI.hpp"
#include "SetpointManager/SetpointManager.hpp"

#include <memory>
#include <vector>

namespace openstudio {
namespace epmodel {

  class Model;

  namespace detail {
    class SetpointManagerSingleZoneHumidityMinimum_Impl;
  }

  /** \brief Sets the minimum-humidity setpoint for one control zone.
   *
   * \par EnergyPlus object
   * \epobject{group-setpoint-managers.html#setpointmanagersinglezonehumidityminimum,SetpointManager:SingleZone:Humidity:Minimum}
   *
   * \par OpenStudio Model API
   * The corresponding OpenStudio Model class is
   * <code>openstudio::model::SetpointManagerSingleZoneHumidityMinimum</code>.
   *
   * - <b>Not yet available:</b> <code>controlZone()</code>,
   *   <code>setControlZone(...)</code>, and <code>resetControlZone()</code>.
   *
   * \par Known limitations
   * No known EPModel-specific limitations.
   */
  class EPMODEL_API SetpointManagerSingleZoneHumidityMinimum : public SetpointManager
  {
   public:
    explicit SetpointManagerSingleZoneHumidityMinimum(const Model& model);

    virtual ~SetpointManagerSingleZoneHumidityMinimum() override = default;
    SetpointManagerSingleZoneHumidityMinimum(const SetpointManagerSingleZoneHumidityMinimum& other) = default;
    SetpointManagerSingleZoneHumidityMinimum(SetpointManagerSingleZoneHumidityMinimum&& other) = default;
    SetpointManagerSingleZoneHumidityMinimum& operator=(const SetpointManagerSingleZoneHumidityMinimum&) = default;
    SetpointManagerSingleZoneHumidityMinimum& operator=(SetpointManagerSingleZoneHumidityMinimum&&) = default;

    static IddObjectType iddObjectType();

    static std::vector<std::string> controlVariableValues();

    /** @name Getters */
    //@{
    std::string controlVariable() const;
    //@}

    /** @name Setters */
    //@{
    bool setControlVariable(const std::string& controlVariable);
    //@}

   protected:
    using ImplType = detail::SetpointManagerSingleZoneHumidityMinimum_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    explicit SetpointManagerSingleZoneHumidityMinimum(std::shared_ptr<detail::SetpointManagerSingleZoneHumidityMinimum_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
