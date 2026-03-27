/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_AIRTERMINALSINGLEDUCTVAVREHEAT_HPP
#define EPMODEL_AIRTERMINALSINGLEDUCTVAVREHEAT_HPP

#include "EPModelAPI.hpp"
#include "StraightComponent/StraightComponent.hpp"

#include <utilities/idd/IddEnums.hxx>

#include <memory>
#include <vector>

namespace openstudio {
namespace epmodel {

  class Model;

  namespace detail {
    class AirTerminalSingleDuctVAVReheat_Impl;
  }

  class EPMODEL_API AirTerminalSingleDuctVAVReheat : public StraightComponent
  {
   public:
    explicit AirTerminalSingleDuctVAVReheat(const Model& model);

    virtual ~AirTerminalSingleDuctVAVReheat() override = default;
    AirTerminalSingleDuctVAVReheat(const AirTerminalSingleDuctVAVReheat& other) = default;
    AirTerminalSingleDuctVAVReheat(AirTerminalSingleDuctVAVReheat&& other) = default;
    AirTerminalSingleDuctVAVReheat& operator=(const AirTerminalSingleDuctVAVReheat&) = default;
    AirTerminalSingleDuctVAVReheat& operator=(AirTerminalSingleDuctVAVReheat&&) = default;

    static IddObjectType iddObjectType();

    static std::vector<std::string> zoneMinimumAirFlowInputMethodValues();
    static std::vector<std::string> damperHeatingActionValues();

    // Schema Alignment Notes:
    // - Status: Scalar Parity. The scalar VAV reheat contract is aligned; relationship and node plumbing remain narrower.
    // - Canonical Counterpart: openstudio::model::AirTerminalSingleDuctVAVReheat.
    // - Implemented Parity: `maximumAirFlowRate`, `zoneMinimumAirFlowInputMethod`, `zoneMinimumAirFlowMethod`, `constantMinimumAirFlowFraction`, `fixedMinimumAirFlowRate`, `maximumHotWaterorSteamFlowRate`, `minimumHotWaterorSteamFlowRate`, `maximumReheatAirTemperature`, and the legacy naming compatibility around `setMinimumHotWaterOrStreamFlowRate` preserve the canonical scalar contract.
    // - Documented Delta: Availability schedule, damper/air inlet/air outlet node names, reheat-coil references, minimum air flow fraction schedule, design specification outdoor air reference, minimum air flow turndown schedule, and `controlForOutdoorAir` behavior are relationship fields and are not exposed as public methods yet.
    // - Field/Storage Mapping: The preserved scalars map directly to EnergyPlus `AirTerminal:SingleDuct:VAV:Reheat` fields; the translator handles links separately.
    // - Evidence: `src/model/AirTerminalSingleDuctVAVReheat.hpp`, `src/model/AirTerminalSingleDuctVAVReheat.cpp`, `src/energyplus/ForwardTranslator/ForwardTranslateAirTerminalSingleDuctVAVReheat.cpp`, and `src/epmodel/test/AirTerminalSingleDuctVAVReheat_GTest.cpp`.
    // - Remaining Parity Work: Add the omitted relationship helpers when this type moves beyond scalar parity.
    boost::optional<double> maximumAirFlowRate() const;
    bool isMaximumAirFlowRateAutosized() const;
    bool setMaximumAirFlowRate(double maximumAirFlowRate);
    void autosizeMaximumAirFlowRate();

    std::string zoneMinimumAirFlowInputMethod();
    bool setZoneMinimumAirFlowInputMethod(const std::string& value);

    std::string zoneMinimumAirFlowMethod();
    bool setZoneMinimumAirFlowMethod(const std::string& value);

    boost::optional<double> constantMinimumAirFlowFraction() const;
    bool isConstantMinimumAirFlowFractionAutosized() const;
    bool setConstantMinimumAirFlowFraction(double value);
    void autosizeConstantMinimumAirFlowFraction();

    boost::optional<double> fixedMinimumAirFlowRate() const;
    bool isFixedMinimumAirFlowRateAutosized() const;
    bool setFixedMinimumAirFlowRate(double value);
    void autosizeFixedMinimumAirFlowRate();

    boost::optional<double> maximumHotWaterOrSteamFlowRate();
    bool isMaximumHotWaterOrSteamFlowRateAutosized() const;
    bool setMaximumHotWaterOrSteamFlowRate(double value);
    void autosizeMaximumHotWaterOrSteamFlowRate();

    double minimumHotWaterOrSteamFlowRate();
    bool setMinimumHotWaterOrStreamFlowRate(double value);

    double convergenceTolerance();
    bool setConvergenceTolerance(double value);

    std::string damperHeatingAction();
    bool setDamperHeatingAction(const std::string& value);

    boost::optional<double> maximumFlowPerZoneFloorAreaDuringReheat();
    bool isMaximumFlowPerZoneFloorAreaDuringReheatAutosized() const;
    bool setMaximumFlowPerZoneFloorAreaDuringReheat(double value);
    void autosizeMaximumFlowPerZoneFloorAreaDuringReheat();
    void resetMaximumFlowPerZoneFloorAreaDuringReheat();

    boost::optional<double> maximumFlowFractionDuringReheat();
    bool isMaximumFlowFractionDuringReheatAutosized() const;
    bool setMaximumFlowFractionDuringReheat(double value);
    void autosizeMaximumFlowFractionDuringReheat();
    void resetMaximumFlowFractionDuringReheat();

    double maximumReheatAirTemperature();
    bool setMaximumReheatAirTemperature(double value);

  protected:
    using ImplType = detail::AirTerminalSingleDuctVAVReheat_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    explicit AirTerminalSingleDuctVAVReheat(std::shared_ptr<detail::AirTerminalSingleDuctVAVReheat_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
