/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_AIRTERMINALSINGLEDUCTVAVNOREHEAT_HPP
#define EPMODEL_AIRTERMINALSINGLEDUCTVAVNOREHEAT_HPP

#include "EPModelAPI.hpp"
#include "StraightComponent/StraightComponent.hpp"

#include <utilities/idd/IddEnums.hxx>

#include <memory>
#include <vector>

namespace openstudio {
namespace epmodel {

  class Model;

  namespace detail {
    class AirTerminalSingleDuctVAVNoReheat_Impl;
  }

  class EPMODEL_API AirTerminalSingleDuctVAVNoReheat : public StraightComponent
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
    // - Status: Scalar Parity. The scalar VAV no-reheat contract is aligned; relationship and node plumbing remain narrower.
    // - Canonical Counterpart: openstudio::model::AirTerminalSingleDuctVAVNoReheat.
    // - Implemented Parity: `maximumAirFlowRate`, `zoneMinimumAirFlowInputMethod`, `constantMinimumAirFlowFraction`, and `fixedMinimumAirFlowRate` preserve the canonical scalar contract.
    // - Documented Delta: Availability schedule, air inlet/outlet node names, minimum air flow fraction schedule, design specification outdoor air reference, and minimum air flow turndown schedule are relationship fields and are not exposed as public methods yet.
    // - Field/Storage Mapping: The preserved scalars map directly to EnergyPlus `AirTerminal:SingleDuct:VAV:NoReheat` fields; the translator handles links separately.
    // - Evidence: `src/model/AirTerminalSingleDuctVAVNoReheat.hpp`, `src/model/AirTerminalSingleDuctVAVNoReheat.cpp`, `src/energyplus/ForwardTranslator/ForwardTranslateAirTerminalSingleDuctVAVNoReheat.cpp`, and `src/epmodel/test/AirTerminalSingleDuctVAVNoReheat_GTest.cpp`.
    // - Remaining Parity Work: Add the omitted relationship helpers when this type moves beyond scalar parity.
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
