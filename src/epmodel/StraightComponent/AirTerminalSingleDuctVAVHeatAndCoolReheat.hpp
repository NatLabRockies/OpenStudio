/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_AIRTERMINALSINGLEDUCTVAVHEATANDCOOLREHEAT_HPP
#define EPMODEL_AIRTERMINALSINGLEDUCTVAVHEATANDCOOLREHEAT_HPP

#include "EPModelAPI.hpp"
#include "StraightComponent/StraightComponent.hpp"

#include <utilities/idd/IddEnums.hxx>

#include <memory>

namespace openstudio {
namespace epmodel {

  class Model;

  namespace detail {
    class AirTerminalSingleDuctVAVHeatAndCoolReheat_Impl;
  }

  class EPMODEL_API AirTerminalSingleDuctVAVHeatAndCoolReheat : public StraightComponent
  {
   public:
    explicit AirTerminalSingleDuctVAVHeatAndCoolReheat(const Model& model);

    virtual ~AirTerminalSingleDuctVAVHeatAndCoolReheat() override = default;
    AirTerminalSingleDuctVAVHeatAndCoolReheat(const AirTerminalSingleDuctVAVHeatAndCoolReheat& other) = default;
    AirTerminalSingleDuctVAVHeatAndCoolReheat(AirTerminalSingleDuctVAVHeatAndCoolReheat&& other) = default;
    AirTerminalSingleDuctVAVHeatAndCoolReheat& operator=(const AirTerminalSingleDuctVAVHeatAndCoolReheat&) = default;
    AirTerminalSingleDuctVAVHeatAndCoolReheat& operator=(AirTerminalSingleDuctVAVHeatAndCoolReheat&&) = default;

    static IddObjectType iddObjectType();

  // Schema Alignment Notes:
  // - Status: Scalar Parity. The scalar VAV heat-and-cool reheat contract is aligned; relationship and node plumbing remain narrower.
  // - Canonical Counterpart: openstudio::model::AirTerminalSingleDuctVAVHeatAndCoolReheat.
  // - Implemented Parity: `maximumAirFlowRate`, `zoneMinimumAirFlowFraction`, `maximumHotWaterorSteamFlowRate`, `minimumHotWaterorSteamFlowRate`, `convergenceTolerance`, and `maximumReheatAirTemperature` preserve the canonical scalar contract.
  // - Documented Delta: Availability schedule, damper/air inlet/air outlet node names, reheat-coil references, and the minimum air flow turndown schedule are relationship fields and are not exposed as public methods yet.
  // - Field/Storage Mapping: The preserved scalars map directly to EnergyPlus `AirTerminal:SingleDuct:VAV:HeatAndCool:Reheat` fields; the translator handles links separately.
  // - Evidence: `src/model/AirTerminalSingleDuctVAVHeatAndCoolReheat.hpp`, `src/model/AirTerminalSingleDuctVAVHeatAndCoolReheat.cpp`, `src/energyplus/ForwardTranslator/ForwardTranslateAirTerminalSingleDuctVAVHeatAndCoolReheat.cpp`, and `src/epmodel/test/AirTerminalSingleDuctVAVHeatAndCoolReheat_GTest.cpp`.
  // - Remaining Parity Work: Add the omitted relationship helpers when this type moves beyond scalar parity.
    boost::optional<double> maximumAirFlowRate() const;
    bool setMaximumAirFlowRate(double maximumAirFlowRate);
    bool isMaximumAirFlowRateAutosized() const;
    void autosizeMaximumAirFlowRate();

    double zoneMinimumAirFlowFraction() const;
    bool setZoneMinimumAirFlowFraction(double zoneMinimumAirFlowFraction);

    boost::optional<double> maximumHotWaterorSteamFlowRate() const;
    bool setMaximumHotWaterorSteamFlowRate(double maximumHotWaterorSteamFlowRate);
    bool isMaximumHotWaterorSteamFlowRateAutosized() const;
    void autosizeMaximumHotWaterorSteamFlowRate();

    double minimumHotWaterorSteamFlowRate() const;
    bool setMinimumHotWaterorSteamFlowRate(double minimumHotWaterorSteamFlowRate);

    double convergenceTolerance() const;
    bool setConvergenceTolerance(double convergenceTolerance);

    double maximumReheatAirTemperature() const;
    bool setMaximumReheatAirTemperature(double maximumReheatAirTemperature);

  protected:
    using ImplType = detail::AirTerminalSingleDuctVAVHeatAndCoolReheat_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    explicit AirTerminalSingleDuctVAVHeatAndCoolReheat(std::shared_ptr<detail::AirTerminalSingleDuctVAVHeatAndCoolReheat_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
