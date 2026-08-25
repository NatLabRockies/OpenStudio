/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_SETPOINTMANAGERMULTIZONEHUMIDITYMAXIMUM_HPP
#define EPMODEL_SETPOINTMANAGERMULTIZONEHUMIDITYMAXIMUM_HPP

#include "EPModelAPI.hpp"
#include "SetpointManager/SetpointManager.hpp"

#include <memory>
#include <vector>

namespace openstudio {
namespace epmodel {

  class Model;

  namespace detail {
    class SetpointManagerMultiZoneHumidityMaximum_Impl;
  }

  /** \brief Sets a humidity-ratio setpoint from the maximum zone humidity condition.
   *
   * \par EnergyPlus object
   * \epobject{group-setpoint-managers.html#setpointmanagermultizonehumiditymaximum,SetpointManager:MultiZone:Humidity:Maximum}
   *
   * \par OpenStudio Model API
   * The corresponding OpenStudio Model class is <code>openstudio::model::SetpointManagerMultiZoneHumidityMaximum</code>.
   * No known public API differences.
   *
   * \par Known limitations
   * <code>controlVariable()</code> always returns <code>MaximumHumidityRatio</code>,
   * and <code>setControlVariable</code> accepts only that value; the EnergyPlus
   * object has no control-variable field.
   */
  class EPMODEL_API SetpointManagerMultiZoneHumidityMaximum : public SetpointManager
  {
   public:
    explicit SetpointManagerMultiZoneHumidityMaximum(const Model& model);

    virtual ~SetpointManagerMultiZoneHumidityMaximum() override = default;
    SetpointManagerMultiZoneHumidityMaximum(const SetpointManagerMultiZoneHumidityMaximum& other) = default;
    SetpointManagerMultiZoneHumidityMaximum(SetpointManagerMultiZoneHumidityMaximum&& other) = default;
    SetpointManagerMultiZoneHumidityMaximum& operator=(const SetpointManagerMultiZoneHumidityMaximum&) = default;
    SetpointManagerMultiZoneHumidityMaximum& operator=(SetpointManagerMultiZoneHumidityMaximum&&) = default;

    static IddObjectType iddObjectType();

    static std::vector<std::string> controlVariableValues();

    std::string controlVariable() const;
    bool setControlVariable(const std::string& controlVariable);

    double minimumSetpointHumidityRatio() const;
    bool setMinimumSetpointHumidityRatio(double minimumSetpointHumidityRatio);

    double maximumSetpointHumidityRatio() const;
    bool setMaximumSetpointHumidityRatio(double maximumSetpointHumidityRatio);

   protected:
    using ImplType = detail::SetpointManagerMultiZoneHumidityMaximum_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    explicit SetpointManagerMultiZoneHumidityMaximum(std::shared_ptr<detail::SetpointManagerMultiZoneHumidityMaximum_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
