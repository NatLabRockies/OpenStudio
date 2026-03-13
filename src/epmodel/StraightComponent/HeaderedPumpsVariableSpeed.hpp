/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_HEADEREDPUMPSVARIABLESPEED_HPP
#define EPMODEL_HEADEREDPUMPSVARIABLESPEED_HPP

#include "EPModelAPI.hpp"
#include "StraightComponent/StraightComponent.hpp"

#include <boost/optional.hpp>
#include <memory>
#include <string>
#include <vector>

namespace openstudio {
namespace epmodel {

  class Model;

  namespace detail {
    class HeaderedPumpsVariableSpeed_Impl;
  }

  class EPMODEL_API HeaderedPumpsVariableSpeed : public StraightComponent
  {
   public:
    explicit HeaderedPumpsVariableSpeed(const Model& model);

    virtual ~HeaderedPumpsVariableSpeed() override = default;
    HeaderedPumpsVariableSpeed(const HeaderedPumpsVariableSpeed& other) = default;
    HeaderedPumpsVariableSpeed(HeaderedPumpsVariableSpeed&& other) = default;
    HeaderedPumpsVariableSpeed& operator=(const HeaderedPumpsVariableSpeed&) = default;
    HeaderedPumpsVariableSpeed& operator=(HeaderedPumpsVariableSpeed&&) = default;

    static IddObjectType iddObjectType();

    static std::vector<std::string> flowSequencingControlSchemeValues();
    static std::vector<std::string> pumpControlTypeValues();
    static std::vector<std::string> designPowerSizingMethodValues();

    // Schema Alignment Notes:
    // - API: Preserve openstudio::model::HeaderedPumpsVariableSpeed scalar accessor names/signatures for counterpart parity.
    // - Field Mapping: totalRatedFlowRate/ratedPumpHead/ratedPowerConsumption APIs map to E+ HeaderedPumps:VariableSpeed TotalDesignFlowRate/DesignPumpHead/DesignPowerConsumption.
    // - Field Mapping: pumpFlowRateSchedule, thermalZone, and inlet/outlet node name fields are relationship-like fields and are excluded in this scalar-only pass.
    // - ForwardTranslator evidence: ForwardTranslateHeaderedPumpsVariableSpeed.cpp maps the preserved API names to these E+ fields.
    // - TODO(parity): Add excluded relationship APIs without changing preserved scalar signatures.

    boost::optional<double> totalRatedFlowRate() const;
    bool isTotalRatedFlowRateAutosized() const;
    bool setTotalRatedFlowRate(double totalRatedFlowRate);
    void autosizeTotalRatedFlowRate();
    boost::optional<double> autosizedTotalRatedFlowRate() const;

    int numberofPumpsinBank() const;
    bool setNumberofPumpsinBank(int numberofPumpsinBank);

    std::string flowSequencingControlScheme() const;
    bool setFlowSequencingControlScheme(const std::string& flowSequencingControlScheme);

    double ratedPumpHead() const;
    bool setRatedPumpHead(double ratedPumpHead);

    boost::optional<double> ratedPowerConsumption() const;
    bool isRatedPowerConsumptionAutosized() const;
    bool setRatedPowerConsumption(double ratedPowerConsumption);
    void autosizeRatedPowerConsumption();
    boost::optional<double> autosizedRatedPowerConsumption() const;

    double motorEfficiency() const;
    bool setMotorEfficiency(double motorEfficiency);

    double fractionofMotorInefficienciestoFluidStream() const;
    bool setFractionofMotorInefficienciestoFluidStream(double fractionofMotorInefficienciestoFluidStream);

    double coefficient1ofthePartLoadPerformanceCurve() const;
    bool setCoefficient1ofthePartLoadPerformanceCurve(double coefficient1ofthePartLoadPerformanceCurve);

    double coefficient2ofthePartLoadPerformanceCurve() const;
    bool setCoefficient2ofthePartLoadPerformanceCurve(double coefficient2ofthePartLoadPerformanceCurve);

    double coefficient3ofthePartLoadPerformanceCurve() const;
    bool setCoefficient3ofthePartLoadPerformanceCurve(double coefficient3ofthePartLoadPerformanceCurve);

    double coefficient4ofthePartLoadPerformanceCurve() const;
    bool setCoefficient4ofthePartLoadPerformanceCurve(double coefficient4ofthePartLoadPerformanceCurve);

    double minimumFlowRateFraction() const;
    bool setMinimumFlowRateFraction(double minimumFlowRateFraction);

    std::string pumpControlType() const;
    bool setPumpControlType(const std::string& pumpControlType);

    double skinLossRadiativeFraction() const;
    bool setSkinLossRadiativeFraction(double skinLossRadiativeFraction);

    std::string designPowerSizingMethod() const;
    bool setDesignPowerSizingMethod(const std::string& designPowerSizingMethod);

    double designElectricPowerPerUnitFlowRate() const;
    bool setDesignElectricPowerPerUnitFlowRate(double designElectricPowerPerUnitFlowRate);

    double designShaftPowerPerUnitFlowRatePerUnitHead() const;
    bool setDesignShaftPowerPerUnitFlowRatePerUnitHead(double designShaftPowerPerUnitFlowRatePerUnitHead);

    std::string endUseSubcategory() const;
    bool setEndUseSubcategory(const std::string& endUseSubcategory);

   protected:
    using ImplType = detail::HeaderedPumpsVariableSpeed_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    explicit HeaderedPumpsVariableSpeed(std::shared_ptr<detail::HeaderedPumpsVariableSpeed_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
