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

    // Schema Alignment Notes:
    // - API: Preserves openstudio::model scalar accessor names/signatures for model-counterpart compatibility.
    // - Field Mapping: minimumSetpointHumidityRatio and maximumSetpointHumidityRatio map directly to
    //   E+ SetpointManager:MultiZone:MinimumHumidity:Average fields.
    // - Field Mapping: controlVariable is preserved as a fixed-value API ("MinimumHumidityRatio")
    //   even though the E+ object has no explicit control-variable field.
    // - Field Mapping: Relationship fields HVAC Air Loop Name and Setpoint Node or NodeList Name are
    //   intentionally excluded from scalar-only scaffolding.
    // - TODO(parity): Add non-scalar relationship parity for explicit loop/node linkage in a follow-up pass.
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
