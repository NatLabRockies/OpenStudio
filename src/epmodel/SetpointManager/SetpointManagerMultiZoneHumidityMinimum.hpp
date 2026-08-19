/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_SETPOINTMANAGERMULTIZONEHUMIDITYMINIMUM_HPP
#define EPMODEL_SETPOINTMANAGERMULTIZONEHUMIDITYMINIMUM_HPP

#include "EPModelAPI.hpp"
#include "SetpointManager/SetpointManager.hpp"

#include <memory>
#include <vector>

namespace openstudio {
namespace epmodel {

  class Model;

  namespace detail {
    class SetpointManagerMultiZoneHumidityMinimum_Impl;
  }

  /** \brief Sets a humidity-ratio setpoint from the minimum zone humidity condition.
   *
   * \par EnergyPlus object
   * \epobject{group-setpoint-managers.html#setpointmanagermultizonehumidityminimum,SetpointManager:MultiZone:Humidity:Minimum}
   *
   * \par OpenStudio Model API
   * The corresponding OpenStudio Model class is <code>openstudio::model::SetpointManagerMultiZoneHumidityMinimum</code>.
   * No known public API differences.
   *
   * \par Known limitations
   * <code>controlVariable()</code> always returns <code>MinimumHumidityRatio</code>,
   * and <code>setControlVariable</code> accepts only that value; the EnergyPlus
   * object has no control-variable field.
   */
  class EPMODEL_API SetpointManagerMultiZoneHumidityMinimum : public SetpointManager
  {
   public:
    explicit SetpointManagerMultiZoneHumidityMinimum(const Model& model);

    virtual ~SetpointManagerMultiZoneHumidityMinimum() override = default;
    SetpointManagerMultiZoneHumidityMinimum(const SetpointManagerMultiZoneHumidityMinimum& other) = default;
    SetpointManagerMultiZoneHumidityMinimum(SetpointManagerMultiZoneHumidityMinimum&& other) = default;
    SetpointManagerMultiZoneHumidityMinimum& operator=(const SetpointManagerMultiZoneHumidityMinimum&) = default;
    SetpointManagerMultiZoneHumidityMinimum& operator=(SetpointManagerMultiZoneHumidityMinimum&&) = default;

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
    using ImplType = detail::SetpointManagerMultiZoneHumidityMinimum_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    explicit SetpointManagerMultiZoneHumidityMinimum(std::shared_ptr<detail::SetpointManagerMultiZoneHumidityMinimum_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
