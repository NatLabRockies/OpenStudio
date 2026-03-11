/***********************************************************************************************************************
 *  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
 *  See also https://openstudio.net/license
 ***********************************************************************************************************************/

#ifndef EPMODEL_PUMPVARIABLESPEED_HPP
#define EPMODEL_PUMPVARIABLESPEED_HPP

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
    class PumpVariableSpeed_Impl;
  }

  class EPMODEL_API PumpVariableSpeed : public StraightComponent
  {
   public:
    explicit PumpVariableSpeed(const Model& model);

    virtual ~PumpVariableSpeed() override = default;
    PumpVariableSpeed(const PumpVariableSpeed& other) = default;
    PumpVariableSpeed(PumpVariableSpeed&& other) = default;
    PumpVariableSpeed& operator=(const PumpVariableSpeed&) = default;
    PumpVariableSpeed& operator=(PumpVariableSpeed&&) = default;

    static IddObjectType iddObjectType();

    static std::vector<std::string> pumpControlTypeValues();
    static std::vector<std::string> designPowerSizingMethodValues();
    static std::vector<std::string> validPumpControlTypeValues();
    static std::vector<std::string> vfdControlTypeValues();

    // Schema Alignment Notes:
    // - API: Preserves openstudio::model::PumpVariableSpeed scalar accessor names/signatures for counterpart parity.
    // - Field Mapping: Scalar APIs map directly to EnergyPlus Pump:VariableSpeed fields used by ForwardTranslatePumpVariableSpeed.
    // - ForwardTranslator evidence: ForwardTranslatePumpVariableSpeed populates these fields and autosize tokens in EnergyPlus.
    // - TODO(parity): Schedule/curve references (pump flow rate, RPM, pressure) remain relationship-only and excluded from scalar coverage.
    boost::optional<double> ratedFlowRate() const;
    bool isRatedFlowRateDefaulted() const;
    bool isRatedFlowRateAutosized() const;
    bool setRatedFlowRate(double ratedFlowRate);
    void resetRatedFlowRate();
    void autosizeRatedFlowRate();

    double ratedPumpHead() const;
    bool isRatedPumpHeadDefaulted() const;
    bool setRatedPumpHead(double ratedPumpHead);
    void resetRatedPumpHead();

    boost::optional<double> ratedPowerConsumption() const;
    bool isRatedPowerConsumptionDefaulted() const;
    bool isRatedPowerConsumptionAutosized() const;
    bool setRatedPowerConsumption(double ratedPowerConsumption);
    void resetRatedPowerConsumption();
    void autosizeRatedPowerConsumption();

    double motorEfficiency() const;
    bool isMotorEfficiencyDefaulted() const;
    bool setMotorEfficiency(double motorEfficiency);
    void resetMotorEfficiency();

    double fractionofMotorInefficienciestoFluidStream() const;
    bool isFractionofMotorInefficienciestoFluidStreamDefaulted() const;
    bool setFractionofMotorInefficienciestoFluidStream(double fractionofMotorInefficienciestoFluidStream);
    void resetFractionofMotorInefficienciestoFluidStream();

    double coefficient1ofthePartLoadPerformanceCurve() const;
    bool isCoefficient1ofthePartLoadPerformanceCurveDefaulted() const;
    bool setCoefficient1ofthePartLoadPerformanceCurve(double coefficient1ofthePartLoadPerformanceCurve);
    void resetCoefficient1ofthePartLoadPerformanceCurve();

    double coefficient2ofthePartLoadPerformanceCurve() const;
    bool isCoefficient2ofthePartLoadPerformanceCurveDefaulted() const;
    bool setCoefficient2ofthePartLoadPerformanceCurve(double coefficient2ofthePartLoadPerformanceCurve);
    void resetCoefficient2ofthePartLoadPerformanceCurve();

    double coefficient3ofthePartLoadPerformanceCurve() const;
    bool isCoefficient3ofthePartLoadPerformanceCurveDefaulted() const;
    bool setCoefficient3ofthePartLoadPerformanceCurve(double coefficient3ofthePartLoadPerformanceCurve);
    void resetCoefficient3ofthePartLoadPerformanceCurve();

    double coefficient4ofthePartLoadPerformanceCurve() const;
    bool isCoefficient4ofthePartLoadPerformanceCurveDefaulted() const;
    bool setCoefficient4ofthePartLoadPerformanceCurve(double coefficient4ofthePartLoadPerformanceCurve);
    void resetCoefficient4ofthePartLoadPerformanceCurve();

    double minimumFlowRate() const;
    bool isMinimumFlowRateDefaulted() const;
    bool setMinimumFlowRate(double minimumFlowRate);
    void resetMinimumFlowRate();

    std::string pumpControlType() const;
    bool isPumpControlTypeDefaulted() const;
    bool setPumpControlType(const std::string& pumpControlType);
    void resetPumpControlType();

    boost::optional<double> impellerDiameter() const;
    bool setImpellerDiameter(double impellerDiameter);
    void resetImpellerDiameter();

    boost::optional<std::string> vFDControlType() const;
    bool setVFDControlType(const std::string& vFDControlType);
    void resetVFDControlType();

    double skinLossRadiativeFraction() const;
    bool setSkinLossRadiativeFraction(double skinLossRadiativeFraction);

    std::string designPowerSizingMethod() const;
    bool setDesignPowerSizingMethod(const std::string& designPowerSizingMethod);

    double designElectricPowerPerUnitFlowRate() const;
    bool setDesignElectricPowerPerUnitFlowRate(double designElectricPowerPerUnitFlowRate);

    double designShaftPowerPerUnitFlowRatePerUnitHead() const;
    bool setDesignShaftPowerPerUnitFlowRatePerUnitHead(double designShaftPowerPerUnitFlowRatePerUnitHead);

    double designMinimumFlowRateFraction() const;
    bool setDesignMinimumFlowRateFraction(double designMinimumFlowRateFraction);

    std::string endUseSubcategory() const;
    bool setEndUseSubcategory(const std::string& endUseSubcategory);

   protected:
    using ImplType = detail::PumpVariableSpeed_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    explicit PumpVariableSpeed(std::shared_ptr<detail::PumpVariableSpeed_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
