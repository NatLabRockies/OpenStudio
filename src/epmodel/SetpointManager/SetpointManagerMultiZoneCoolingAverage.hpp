/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_SETPOINTMANAGERMULTIZONECOOLINGAVERAGE_HPP
#define EPMODEL_SETPOINTMANAGERMULTIZONECOOLINGAVERAGE_HPP

#include "EPModelAPI.hpp"
#include "SetpointManager/SetpointManager.hpp"

#include <memory>
#include <vector>

namespace openstudio {
namespace epmodel {

  class Model;

  namespace detail {
    class SetpointManagerMultiZoneCoolingAverage_Impl;
  }

  /** \brief Sets the average supply-air temperature based on cooling load requirements.
   *
   * \par EnergyPlus object
   * \epobject{group-setpoint-managers.html#setpointmanagermultizonecoolingaverage,SetpointManager:MultiZone:Cooling:Average}
   *
   * \par OpenStudio Model API
   * The corresponding OpenStudio Model class is <code>openstudio::model::SetpointManagerMultiZoneCoolingAverage</code>.
   * No known public API differences.
   *
   * \par Known limitations
   * <code>controlVariable()</code> always returns <code>Temperature</code>, and
   * <code>setControlVariable</code> accepts only that value; the EnergyPlus object
   * has no control-variable field.
   */
  class EPMODEL_API SetpointManagerMultiZoneCoolingAverage : public SetpointManager
  {
   public:
    explicit SetpointManagerMultiZoneCoolingAverage(const Model& model);

    virtual ~SetpointManagerMultiZoneCoolingAverage() override = default;
    SetpointManagerMultiZoneCoolingAverage(const SetpointManagerMultiZoneCoolingAverage& other) = default;
    SetpointManagerMultiZoneCoolingAverage(SetpointManagerMultiZoneCoolingAverage&& other) = default;
    SetpointManagerMultiZoneCoolingAverage& operator=(const SetpointManagerMultiZoneCoolingAverage&) = default;
    SetpointManagerMultiZoneCoolingAverage& operator=(SetpointManagerMultiZoneCoolingAverage&&) = default;

    static IddObjectType iddObjectType();

    static std::vector<std::string> controlVariableValues();

    std::string controlVariable() const;
    bool setControlVariable(const std::string& controlVariable);

    double minimumSetpointTemperature() const;
    bool setMinimumSetpointTemperature(double minimumSetpointTemperature);

    double maximumSetpointTemperature() const;
    bool setMaximumSetpointTemperature(double maximumSetpointTemperature);

   protected:
    using ImplType = detail::SetpointManagerMultiZoneCoolingAverage_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    explicit SetpointManagerMultiZoneCoolingAverage(std::shared_ptr<detail::SetpointManagerMultiZoneCoolingAverage_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
