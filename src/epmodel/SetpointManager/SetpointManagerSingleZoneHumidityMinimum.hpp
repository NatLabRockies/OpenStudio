/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_SETPOINTMANAGERSINGLEZONEHUMIDITYMINIMUM_HPP
#define EPMODEL_SETPOINTMANAGERSINGLEZONEHUMIDITYMINIMUM_HPP

#include "EPModelAPI.hpp"
#include "SetpointManager/SetpointManager.hpp"

#include <memory>
#include <vector>

namespace openstudio {
namespace epmodel {

  class Model;

  namespace detail {
    class SetpointManagerSingleZoneHumidityMinimum_Impl;
  }

  class EPMODEL_API SetpointManagerSingleZoneHumidityMinimum : public SetpointManager
  {
   public:
    explicit SetpointManagerSingleZoneHumidityMinimum(const Model& model);

    virtual ~SetpointManagerSingleZoneHumidityMinimum() override = default;
    SetpointManagerSingleZoneHumidityMinimum(const SetpointManagerSingleZoneHumidityMinimum& other) = default;
    SetpointManagerSingleZoneHumidityMinimum(SetpointManagerSingleZoneHumidityMinimum&& other) = default;
    SetpointManagerSingleZoneHumidityMinimum& operator=(const SetpointManagerSingleZoneHumidityMinimum&) = default;
    SetpointManagerSingleZoneHumidityMinimum& operator=(SetpointManagerSingleZoneHumidityMinimum&&) = default;

    static IddObjectType iddObjectType();

    static std::vector<std::string> controlVariableValues();

    /** @name Getters */
    //@{
    // Schema Alignment Notes:
    // - API: Preserves openstudio::model scalar accessor names/signatures for model-counterpart compatibility.
    // - Field Mapping: controlVariable is preserved as a fixed-value API ("MinimumHumidityRatio")
    //   even though current E+ SetpointManager:SingleZone:Humidity:Minimum has no explicit control-variable field.
    // - API: setControlVariable accepts only "MinimumHumidityRatio" and does not persist to any E+ field.
    // - ForwardTranslator Evidence: ForwardTranslateSetpointManagerSingleZoneHumidityMinimum writes only
    //   Control Zone Air Node Name and Setpoint Node or NodeList Name; legacy Control Variable is deprecated.
    // - Field Mapping: Relationship fields Control Zone Air Node Name and Setpoint Node or NodeList Name are
    //   intentionally excluded from scalar-only scaffolding.
    // - TODO(parity): Add non-scalar relationship parity for control-zone linkage in a follow-up pass.
    std::string controlVariable() const;
    //@}

    /** @name Setters */
    //@{
    bool setControlVariable(const std::string& controlVariable);
    //@}

   protected:
    using ImplType = detail::SetpointManagerSingleZoneHumidityMinimum_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    explicit SetpointManagerSingleZoneHumidityMinimum(std::shared_ptr<detail::SetpointManagerSingleZoneHumidityMinimum_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
