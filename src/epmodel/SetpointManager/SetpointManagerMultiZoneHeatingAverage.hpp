/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_SETPOINTMANAGERMULTIZONEHEATINGAVERAGE_HPP
#define EPMODEL_SETPOINTMANAGERMULTIZONEHEATINGAVERAGE_HPP

#include "EPModelAPI.hpp"
#include "SetpointManager/SetpointManager.hpp"

#include <memory>
#include <vector>

namespace openstudio {
namespace epmodel {

  class Model;

  namespace detail {
    class SetpointManagerMultiZoneHeatingAverage_Impl;
  }

  /** \brief Sets the average supply-air temperature based on heating load requirements.
   *
   * \par EnergyPlus object
   * \epobject{group-setpoint-managers.html#setpointmanagermultizoneheatingaverage,SetpointManager:MultiZone:Heating:Average}
   *
   * \par OpenStudio Model API
   * The corresponding OpenStudio Model class is <code>openstudio::model::SetpointManagerMultiZoneHeatingAverage</code>.
   * No known public API differences.
   *
   * \par Known limitations
   * <code>controlVariable()</code> always returns <code>Temperature</code>, and
   * <code>setControlVariable</code> accepts only that value; the EnergyPlus object
   * has no control-variable field.
   */
  class EPMODEL_API SetpointManagerMultiZoneHeatingAverage : public SetpointManager
  {
   public:
    explicit SetpointManagerMultiZoneHeatingAverage(const Model& model);

    virtual ~SetpointManagerMultiZoneHeatingAverage() override = default;
    SetpointManagerMultiZoneHeatingAverage(const SetpointManagerMultiZoneHeatingAverage& other) = default;
    SetpointManagerMultiZoneHeatingAverage(SetpointManagerMultiZoneHeatingAverage&& other) = default;
    SetpointManagerMultiZoneHeatingAverage& operator=(const SetpointManagerMultiZoneHeatingAverage&) = default;
    SetpointManagerMultiZoneHeatingAverage& operator=(SetpointManagerMultiZoneHeatingAverage&&) = default;

    static IddObjectType iddObjectType();

    static std::vector<std::string> controlVariableValues();


    std::string controlVariable() const;
    bool setControlVariable(const std::string& controlVariable);

    double minimumSetpointTemperature() const;
    bool setMinimumSetpointTemperature(double minimumSetpointTemperature);

    double maximumSetpointTemperature() const;
    bool setMaximumSetpointTemperature(double maximumSetpointTemperature);

   protected:
    using ImplType = detail::SetpointManagerMultiZoneHeatingAverage_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    explicit SetpointManagerMultiZoneHeatingAverage(std::shared_ptr<detail::SetpointManagerMultiZoneHeatingAverage_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
