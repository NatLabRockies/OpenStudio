/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_AIRTERMINALSINGLEDUCTVAVNOREHEAT_HPP
#define EPMODEL_AIRTERMINALSINGLEDUCTVAVNOREHEAT_HPP

#include "EPModelAPI.hpp"
#include "ModelObject.hpp"

#include <utilities/idd/IddEnums.hxx>

#include <memory>
#include <vector>

namespace openstudio {
namespace epmodel {

  class Model;

  namespace detail {
    class AirTerminalSingleDuctVAVNoReheat_Impl;
  }

  class EPMODEL_API AirTerminalSingleDuctVAVNoReheat : public ModelObject
  {
   public:
    explicit AirTerminalSingleDuctVAVNoReheat(const Model& model);

    virtual ~AirTerminalSingleDuctVAVNoReheat() override = default;
    AirTerminalSingleDuctVAVNoReheat(const AirTerminalSingleDuctVAVNoReheat& other) = default;
    AirTerminalSingleDuctVAVNoReheat(AirTerminalSingleDuctVAVNoReheat&& other) = default;
    AirTerminalSingleDuctVAVNoReheat& operator=(const AirTerminalSingleDuctVAVNoReheat&) = default;
    AirTerminalSingleDuctVAVNoReheat& operator=(AirTerminalSingleDuctVAVNoReheat&&) = default;

    static IddObjectType iddObjectType();

    static std::vector<std::string> zoneMinimumAirFlowInputMethodValues();

    // Schema Alignment Notes:
    // - API: Preserve openstudio::model scalar accessor names/signatures for this model-counterpart class.
    // - Field Mapping: maximumAirFlowRate, zoneMinimumAirFlowInputMethod, constantMinimumAirFlowFraction, and
    //   fixedMinimumAirFlowRate map directly to EnergyPlus AirTerminal:SingleDuct:VAV:NoReheat scalar fields.
    // - Field Mapping: Availability Schedule Name, Air Inlet/Air Outlet Node Name, Minimum Air Flow Fraction Schedule Name,
    //   Design Specification Outdoor Air Object Name, and Minimum Air Flow Turndown Schedule Name are relationship fields and
    //   intentionally excluded from scalar accessors.
    // - ForwardTranslator evidence: translateAirTerminalSingleDuctVAVNoReheat writes these scalar fields and handles
    //   relationship links separately.
    // - TODO(parity): Add relationship/non-scalar behavior incrementally after scalar scaffold saturation.
    boost::optional<double> maximumAirFlowRate() const;
    bool isMaximumAirFlowRateAutosized() const;
    bool setMaximumAirFlowRate(double maximumAirFlowRate);
    void autosizeMaximumAirFlowRate();
    void resetMaximumAirFlowRate();

    boost::optional<std::string> zoneMinimumAirFlowInputMethod() const;
    bool setZoneMinimumAirFlowInputMethod(const std::string& zoneMinimumAirFlowInputMethod);
    void resetZoneMinimumAirFlowInputMethod();

    boost::optional<double> constantMinimumAirFlowFraction() const;
    bool isConstantMinimumAirFlowFractionAutosized() const;
    bool isConstantMinimumAirFlowFractionDefaulted() const;
    bool setConstantMinimumAirFlowFraction(double constantMinimumAirFlowFraction);
    void autosizeConstantMinimumAirFlowFraction();
    void resetConstantMinimumAirFlowFraction();

    boost::optional<double> fixedMinimumAirFlowRate() const;
    bool isFixedMinimumAirFlowRateAutosized() const;
    bool isFixedMinimumAirFlowRateDefaulted() const;
    bool setFixedMinimumAirFlowRate(double fixedMinimumAirFlowRate);
    void autosizeFixedMinimumAirFlowRate();
    void resetFixedMinimumAirFlowRate();

   protected:
    using ImplType = detail::AirTerminalSingleDuctVAVNoReheat_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    explicit AirTerminalSingleDuctVAVNoReheat(std::shared_ptr<detail::AirTerminalSingleDuctVAVNoReheat_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
