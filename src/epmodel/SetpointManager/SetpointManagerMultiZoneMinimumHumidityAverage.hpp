/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_SETPOINTMANAGERMULTIZONEMINIMUMHUMIDITYAVERAGE_HPP
#define EPMODEL_SETPOINTMANAGERMULTIZONEMINIMUMHUMIDITYAVERAGE_HPP

#include "EPModelAPI.hpp"
#include "SetpointManager/SetpointManager.hpp"

#include <memory>
#include <vector>

namespace openstudio {
namespace epmodel {

  class Model;

  namespace detail {
    class SetpointManagerMultiZoneMinimumHumidityAverage_Impl;
  }

  /** \brief Sets a humidity-ratio setpoint from the average of the zone minimum humidity conditions.
   *
   * \par EnergyPlus object
   * \epobject{group-setpoint-managers.html#setpointmanagermultizoneminimumhumidityaverage,SetpointManager:MultiZone:MinimumHumidity:Average}
   *
   * \par OpenStudio Model API
   * The corresponding OpenStudio Model class is <code>openstudio::model::SetpointManagerMultiZoneMinimumHumidityAverage</code>.
   * No known public API differences.
   *
   * \par Known limitations
   * <code>controlVariable()</code> always returns <code>MinimumHumidityRatio</code>,
   * and <code>setControlVariable</code> accepts only that value; the EnergyPlus
   * object has no control-variable field.
   */
  class EPMODEL_API SetpointManagerMultiZoneMinimumHumidityAverage : public SetpointManager
  {
   public:
    explicit SetpointManagerMultiZoneMinimumHumidityAverage(const Model& model);

    virtual ~SetpointManagerMultiZoneMinimumHumidityAverage() override = default;
    SetpointManagerMultiZoneMinimumHumidityAverage(const SetpointManagerMultiZoneMinimumHumidityAverage& other) = default;
    SetpointManagerMultiZoneMinimumHumidityAverage(SetpointManagerMultiZoneMinimumHumidityAverage&& other) = default;
    SetpointManagerMultiZoneMinimumHumidityAverage& operator=(const SetpointManagerMultiZoneMinimumHumidityAverage&) = default;
    SetpointManagerMultiZoneMinimumHumidityAverage& operator=(SetpointManagerMultiZoneMinimumHumidityAverage&&) = default;

    static IddObjectType iddObjectType();

    static std::vector<std::string> controlVariableValues();

    std::string controlVariable() const;
    bool setControlVariable(const std::string& controlVariable);

    double minimumSetpointHumidityRatio() const;
    bool isMinimumSetpointHumidityRatioDefaulted() const;
    bool setMinimumSetpointHumidityRatio(double minimumSetpointHumidityRatio);
    void resetMinimumSetpointHumidityRatio();

    double maximumSetpointHumidityRatio() const;
    bool isMaximumSetpointHumidityRatioDefaulted() const;
    bool setMaximumSetpointHumidityRatio(double maximumSetpointHumidityRatio);
    void resetMaximumSetpointHumidityRatio();

   protected:
    using ImplType = detail::SetpointManagerMultiZoneMinimumHumidityAverage_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    explicit SetpointManagerMultiZoneMinimumHumidityAverage(std::shared_ptr<detail::SetpointManagerMultiZoneMinimumHumidityAverage_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
