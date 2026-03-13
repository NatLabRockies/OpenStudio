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

    // Schema Alignment Notes:
    // - API: Preserves openstudio::model scalar accessor names/signatures for model-counterpart compatibility.
    // - Field Mapping: minimumSetpointHumidityRatio and maximumSetpointHumidityRatio map directly to
    //   E+ SetpointManager:MultiZone:Humidity:Maximum fields.
    // - Field Mapping: controlVariable is preserved as a fixed-value API ("MaximumHumidityRatio")
    //   even though the E+ object has no explicit control-variable field.
    // - Field Mapping: Relationship fields HVAC Air Loop Name and Setpoint Node or NodeList Name are
    //   intentionally excluded from scalar-only scaffolding.
    // - TODO(parity): Add non-scalar relationship parity for explicit loop/node linkage in a follow-up pass.
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
