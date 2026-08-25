/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_SETPOINTMANAGERSINGLEZONEHUMIDITYMAXIMUM_HPP
#define EPMODEL_SETPOINTMANAGERSINGLEZONEHUMIDITYMAXIMUM_HPP

#include "EPModelAPI.hpp"
#include "SetpointManager/SetpointManager.hpp"

#include <memory>
#include <vector>

namespace openstudio {
namespace epmodel {

  class Model;

  namespace detail {
    class SetpointManagerSingleZoneHumidityMaximum_Impl;
  }

  /** \brief Sets the maximum-humidity setpoint for one control zone.
   *
   * \par EnergyPlus object
   * \epobject{group-setpoint-managers.html#setpointmanagersinglezonehumiditymaximum,SetpointManager:SingleZone:Humidity:Maximum}
   *
   * \par OpenStudio Model API
   * The corresponding OpenStudio Model class is
   * <code>openstudio::model::SetpointManagerSingleZoneHumidityMaximum</code>.
   *
   * - <b>Not yet available:</b> <code>controlZone()</code>,
   *   <code>setControlZone(...)</code>, and <code>resetControlZone()</code>.
   *
   * \par Known limitations
   * No known EPModel-specific limitations.
   */
  class EPMODEL_API SetpointManagerSingleZoneHumidityMaximum : public SetpointManager
  {
   public:
    explicit SetpointManagerSingleZoneHumidityMaximum(const Model& model);

    virtual ~SetpointManagerSingleZoneHumidityMaximum() override = default;
    SetpointManagerSingleZoneHumidityMaximum(const SetpointManagerSingleZoneHumidityMaximum& other) = default;
    SetpointManagerSingleZoneHumidityMaximum(SetpointManagerSingleZoneHumidityMaximum&& other) = default;
    SetpointManagerSingleZoneHumidityMaximum& operator=(const SetpointManagerSingleZoneHumidityMaximum&) = default;
    SetpointManagerSingleZoneHumidityMaximum& operator=(SetpointManagerSingleZoneHumidityMaximum&&) = default;

    static IddObjectType iddObjectType();

    static std::vector<std::string> controlVariableValues();

    std::string controlVariable() const;

    bool setControlVariable(const std::string& controlVariable);

   protected:
    using ImplType = detail::SetpointManagerSingleZoneHumidityMaximum_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    explicit SetpointManagerSingleZoneHumidityMaximum(std::shared_ptr<detail::SetpointManagerSingleZoneHumidityMaximum_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
