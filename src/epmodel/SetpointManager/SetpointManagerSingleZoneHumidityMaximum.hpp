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

    // Schema Alignment Notes:
    // - API: Preserves openstudio::model scalar accessor names/signatures for model-counterpart compatibility.
    // - Field Mapping: controlVariable is preserved as a fixed-value API ("MaximumHumidityRatio")
    //   even though current E+ SetpointManager:SingleZone:Humidity:Maximum has no explicit control-variable field.
    // - API: setControlVariable accepts only "MaximumHumidityRatio" and does not persist to any E+ field.
    // - ForwardTranslator Evidence: ForwardTranslateSetpointManagerSingleZoneHumidityMaximum writes only
    //   Control Zone Air Node Name and Setpoint Node or NodeList Name; legacy Control Variable is deprecated.
    // - Field Mapping: Relationship fields Control Zone Air Node Name and Setpoint Node or NodeList Name are
    //   intentionally excluded from scalar-only scaffolding.
    // - TODO(parity): Add non-scalar relationship parity for control-zone linkage in a follow-up pass.
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
