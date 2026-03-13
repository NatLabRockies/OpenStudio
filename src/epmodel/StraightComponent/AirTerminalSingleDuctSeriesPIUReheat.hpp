/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_AIRTERMINALSINGLEDUCTSERIESPIUREHEAT_HPP
#define EPMODEL_AIRTERMINALSINGLEDUCTSERIESPIUREHEAT_HPP

#include "EPModelAPI.hpp"
#include "ModelObject.hpp"

#include <utilities/idd/IddEnums.hxx>

#include <memory>
#include <vector>

namespace openstudio {
namespace epmodel {

  class Model;

  namespace detail {
    class AirTerminalSingleDuctSeriesPIUReheat_Impl;
  }

  class EPMODEL_API AirTerminalSingleDuctSeriesPIUReheat : public ModelObject
  {
   public:
    explicit AirTerminalSingleDuctSeriesPIUReheat(const Model& model);

    virtual ~AirTerminalSingleDuctSeriesPIUReheat() override = default;
    AirTerminalSingleDuctSeriesPIUReheat(const AirTerminalSingleDuctSeriesPIUReheat& other) = default;
    AirTerminalSingleDuctSeriesPIUReheat(AirTerminalSingleDuctSeriesPIUReheat&& other) = default;
    AirTerminalSingleDuctSeriesPIUReheat& operator=(const AirTerminalSingleDuctSeriesPIUReheat&) = default;
    AirTerminalSingleDuctSeriesPIUReheat& operator=(AirTerminalSingleDuctSeriesPIUReheat&&) = default;

    static IddObjectType iddObjectType();

    static std::vector<std::string> fanControlTypeValues();
    static std::vector<std::string> heatingControlTypeValues();

    // Schema Alignment Notes:
    // - API: Preserve openstudio::model scalar accessor names/signatures for this model-counterpart class.
    // - Field Mapping: maximumAirFlowRate, maximumPrimaryAirFlowRate, minimumPrimaryAirFlowFraction,
    //   maximumHotWaterorSteamFlowRate, minimumHotWaterorSteamFlowRate, convergenceTolerance,
    //   fanControlType, minimumFanTurnDownRatio, heatingControlType, designHeatingDischargeAirTemperature,
    //   and highLimitHeatingDischargeAirTemperature map directly to EnergyPlus
    //   AirTerminal:SingleDuct:SeriesPIU:Reheat scalar fields.
    // - Field Mapping: Availability Schedule Name, node names, Zone Mixer/Fan/Reheat Coil references,
    //   and related object-type/link fields are relationship fields and intentionally excluded.
    // - ForwardTranslator evidence: translateAirTerminalSingleDuctSeriesPIUReheat writes these scalar fields directly
    //   and handles relationship fields separately.
    // - TODO(parity): Add relationship/non-scalar behavior incrementally after scalar scaffold saturation.
    boost::optional<double> maximumAirFlowRate() const;
    bool isMaximumAirFlowRateAutosized() const;
    bool setMaximumAirFlowRate(double maximumAirFlowRate);
    void autosizeMaximumAirFlowRate();

    boost::optional<double> maximumPrimaryAirFlowRate() const;
    bool isMaximumPrimaryAirFlowRateAutosized() const;
    bool setMaximumPrimaryAirFlowRate(double maximumPrimaryAirFlowRate);
    void autosizeMaximumPrimaryAirFlowRate();

    boost::optional<double> minimumPrimaryAirFlowFraction() const;
    bool isMinimumPrimaryAirFlowFractionAutosized() const;
    bool setMinimumPrimaryAirFlowFraction(double minimumPrimaryAirFlowFraction);
    void autosizeMinimumPrimaryAirFlowFraction();

    boost::optional<double> maximumHotWaterorSteamFlowRate() const;
    bool isMaximumHotWaterorSteamFlowRateAutosized() const;
    bool setMaximumHotWaterorSteamFlowRate(double maximumHotWaterorSteamFlowRate);
    void resetMaximumHotWaterorSteamFlowRate();
    void autosizeMaximumHotWaterorSteamFlowRate();

    double minimumHotWaterorSteamFlowRate() const;
    bool setMinimumHotWaterorSteamFlowRate(double minimumHotWaterorSteamFlowRate);

    double convergenceTolerance() const;
    bool setConvergenceTolerance(double convergenceTolerance);

    std::string fanControlType() const;
    bool setFanControlType(const std::string& fanControlType);

    double minimumFanTurnDownRatio() const;
    bool setMinimumFanTurnDownRatio(double minimumFanTurnDownRatio);

    std::string heatingControlType() const;
    bool setHeatingControlType(const std::string& heatingControlType);

    double designHeatingDischargeAirTemperature() const;
    bool setDesignHeatingDischargeAirTemperature(double designHeatingDischargeAirTemperature);

    double highLimitHeatingDischargeAirTemperature() const;
    bool setHighLimitHeatingDischargeAirTemperature(double highLimitHeatingDischargeAirTemperature);

   protected:
    using ImplType = detail::AirTerminalSingleDuctSeriesPIUReheat_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    explicit AirTerminalSingleDuctSeriesPIUReheat(std::shared_ptr<detail::AirTerminalSingleDuctSeriesPIUReheat_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
