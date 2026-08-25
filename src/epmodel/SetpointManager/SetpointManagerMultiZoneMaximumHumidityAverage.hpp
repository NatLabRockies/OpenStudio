/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_SETPOINTMANAGERMULTIZONEMAXIMUMHUMIDITYAVERAGE_HPP
#define EPMODEL_SETPOINTMANAGERMULTIZONEMAXIMUMHUMIDITYAVERAGE_HPP

#include "EPModelAPI.hpp"
#include "SetpointManager/SetpointManager.hpp"

#include <memory>
#include <vector>

namespace openstudio {
namespace epmodel {

  class Model;

  namespace detail {
    class SetpointManagerMultiZoneMaximumHumidityAverage_Impl;
  }

  /** \brief Sets a humidity-ratio setpoint from the average of the zone maximum humidity conditions.
   *
   * \par EnergyPlus object
   * \epobject{group-setpoint-managers.html#setpointmanagermultizonemaximumhumidityaverage,SetpointManager:MultiZone:MaximumHumidity:Average}
   *
   * \par OpenStudio Model API
   * The corresponding OpenStudio Model class is <code>openstudio::model::SetpointManagerMultiZoneMaximumHumidityAverage</code>.
   * No known public API differences.
   *
   * \par Known limitations
   * <code>controlVariable()</code> always returns <code>MaximumHumidityRatio</code>,
   * and <code>setControlVariable</code> accepts only that value; the EnergyPlus
   * object has no control-variable field.
   */
  class EPMODEL_API SetpointManagerMultiZoneMaximumHumidityAverage : public SetpointManager
  {
   public:
    explicit SetpointManagerMultiZoneMaximumHumidityAverage(const Model& model);

    virtual ~SetpointManagerMultiZoneMaximumHumidityAverage() override = default;
    SetpointManagerMultiZoneMaximumHumidityAverage(const SetpointManagerMultiZoneMaximumHumidityAverage& other) = default;
    SetpointManagerMultiZoneMaximumHumidityAverage(SetpointManagerMultiZoneMaximumHumidityAverage&& other) = default;
    SetpointManagerMultiZoneMaximumHumidityAverage& operator=(const SetpointManagerMultiZoneMaximumHumidityAverage&) = default;
    SetpointManagerMultiZoneMaximumHumidityAverage& operator=(SetpointManagerMultiZoneMaximumHumidityAverage&&) = default;

    static IddObjectType iddObjectType();

    static std::vector<std::string> controlVariableValues();


    // Control Variable (MaximumHumidityRatio)
    std::string controlVariable() const;
    bool setControlVariable(const std::string& controlVariable);

    // Minimum Setpoint Humidity Ratio
    double minimumSetpointHumidityRatio() const;
    bool setMinimumSetpointHumidityRatio(double minimumSetpointHumidityRatio);

    // Maximum Setpoint Humidity Ratio
    double maximumSetpointHumidityRatio() const;
    bool setMaximumSetpointHumidityRatio(double maximumSetpointHumidityRatio);

   protected:
    using ImplType = detail::SetpointManagerMultiZoneMaximumHumidityAverage_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    explicit SetpointManagerMultiZoneMaximumHumidityAverage(std::shared_ptr<detail::SetpointManagerMultiZoneMaximumHumidityAverage_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
