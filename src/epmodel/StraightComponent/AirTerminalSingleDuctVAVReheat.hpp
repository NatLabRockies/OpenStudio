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
    // - API: Preserve openstudio::model scalar accessor names/signatures for this model-counterpart class.
    // - Field Mapping: Scalar APIs map to EnergyPlus AirTerminal:SingleDuct:VAV:Reheat fields, including legacy model naming
    //   such as setMinimumHotWaterOrStreamFlowRate and "autosize"-named methods for autocalculated reheat limit fields.
    // - Field Mapping: Availability Schedule Name, Damper Air Outlet Node Name, Air Outlet Node Name, Air Inlet Node Name,
    //   Reheat Coil Object Type/Name, Minimum Air Flow Fraction Schedule Name, Design Specification Outdoor Air Object Name,
    //   Minimum Air Flow Turndown Schedule Name, and model-level controlForOutdoorAir behavior are relationship/target-link
    //   concepts and intentionally excluded.
    // - ForwardTranslator evidence: translateAirTerminalSingleDuctVAVReheat writes scalar values separately from relationship links.
    // - TODO(parity): Add relationship/non-scalar behavior incrementally after scalar scaffold saturation.
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
