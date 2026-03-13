/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_SETPOINTMANAGEROUTDOORAIRPRETREAT_HPP
#define EPMODEL_SETPOINTMANAGEROUTDOORAIRPRETREAT_HPP

#include "EPModelAPI.hpp"
#include "SetpointManager/SetpointManager.hpp"

#include <memory>
#include <vector>

namespace openstudio {
namespace epmodel {

  class Model;

  namespace detail {
    class SetpointManagerOutdoorAirPretreat_Impl;
  }

  class EPMODEL_API SetpointManagerOutdoorAirPretreat : public SetpointManager
  {
   public:
    explicit SetpointManagerOutdoorAirPretreat(const Model& model);

    virtual ~SetpointManagerOutdoorAirPretreat() override = default;
    SetpointManagerOutdoorAirPretreat(const SetpointManagerOutdoorAirPretreat& other) = default;
    SetpointManagerOutdoorAirPretreat(SetpointManagerOutdoorAirPretreat&& other) = default;
    SetpointManagerOutdoorAirPretreat& operator=(const SetpointManagerOutdoorAirPretreat&) = default;
    SetpointManagerOutdoorAirPretreat& operator=(SetpointManagerOutdoorAirPretreat&&) = default;

    static IddObjectType iddObjectType();

    static std::vector<std::string> controlVariableValues();

    // Schema Alignment Notes:
    // - API: Preserves openstudio::model scalar accessor names/signatures for model-counterpart compatibility.
    // - Field Mapping: minimumSetpointTemperature, maximumSetpointTemperature,
    //   minimumSetpointHumidityRatio, and maximumSetpointHumidityRatio map directly to
    //   E+ SetpointManager:OutdoorAirPretreat fields.
    // - Field Mapping: Relationship fields Reference Setpoint Node Name, Mixed Air Stream Node Name,
    //   Outdoor Air Stream Node Name, Return Air Stream Node Name, and Setpoint Node or NodeList Name
    //   are intentionally excluded from scalar-only scaffolding.
    // - API: resetControlVariable is preserved; controlVariable()/setControlVariable() are inherited from SetpointManager.
    // - TODO(parity): Add non-scalar node-linkage parity, including ForwardTranslator OA-system fallback behavior.
    double minimumSetpointTemperature() const;
    bool isMinimumSetpointTemperatureDefaulted() const;
    bool setMinimumSetpointTemperature(double minimumSetpointTemperature);
    void resetMinimumSetpointTemperature();

    double maximumSetpointTemperature() const;
    bool isMaximumSetpointTemperatureDefaulted() const;
    bool setMaximumSetpointTemperature(double maximumSetpointTemperature);
    void resetMaximumSetpointTemperature();

    double minimumSetpointHumidityRatio() const;
    bool isMinimumSetpointHumidityRatioDefaulted() const;
    bool setMinimumSetpointHumidityRatio(double minimumSetpointHumidityRatio);
    void resetMinimumSetpointHumidityRatio();

    double maximumSetpointHumidityRatio() const;
    bool isMaximumSetpointHumidityRatioDefaulted() const;
    bool setMaximumSetpointHumidityRatio(double maximumSetpointHumidityRatio);
    void resetMaximumSetpointHumidityRatio();

    void resetControlVariable();

   protected:
    using ImplType = detail::SetpointManagerOutdoorAirPretreat_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    explicit SetpointManagerOutdoorAirPretreat(std::shared_ptr<detail::SetpointManagerOutdoorAirPretreat_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
