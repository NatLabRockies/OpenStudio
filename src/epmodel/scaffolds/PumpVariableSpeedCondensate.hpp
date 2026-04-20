/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_PUMPVARIABLESPEEDCONDENSATE_HPP
#define EPMODEL_PUMPVARIABLESPEEDCONDENSATE_HPP

#include "EPModelAPI.hpp"
#include "ModelObject.hpp"

#include <utilities/idd/IddEnums.hxx>

#include <memory>
#include <string>
#include <vector>

namespace openstudio {
namespace epmodel {

  class Model;

  namespace detail {
    class PumpVariableSpeedCondensate_Impl;
  }

  class EPMODEL_API PumpVariableSpeedCondensate : public ModelObject
  {
   public:
    explicit PumpVariableSpeedCondensate(const Model& model);

    virtual ~PumpVariableSpeedCondensate() override = default;
    PumpVariableSpeedCondensate(const PumpVariableSpeedCondensate& other) = default;
    PumpVariableSpeedCondensate(PumpVariableSpeedCondensate&& other) = default;
    PumpVariableSpeedCondensate& operator=(const PumpVariableSpeedCondensate&) = default;
    PumpVariableSpeedCondensate& operator=(PumpVariableSpeedCondensate&&) = default;

    static IddObjectType iddObjectType();

    static std::vector<std::string> designPowerSizingMethodValues();

    // Schema Alignment Notes:
    // - API: No-model-counterpart type that follows the Pump:VariableSpeed:Condensate IDD naming for scalar accessors.
    // - Field Mapping: Simple numeric scalars map directly to Design Steam Volume Flow Rate, Design Pump Head, Design Power
    //   Consumption, Motor Efficiency, Fraction of Motor Inefficiencies to Fluid Stream, Part Load Performance Curve
    //   coefficients, Skin Loss Radiative Fraction, Design Electric Power per Unit Flow Rate, Design Shaft Power per Unit Flow
    //   Rate per Unit Head, and End-Use Subcategory.
    // - Field Mapping: Choice scalar maps to Design Power Sizing Method values (PowerPerFlow, PowerPerFlowPerPressure).
    // - Field Mapping: Relationship fields (Inlet Node Name, Outlet Node Name, Pump Flow Rate Schedule Name, Zone Name)
    //   remain excluded from the scalar API surface.
    // - TODO(parity): Add relationship helpers and grouping fields after scalar saturation without changing signatures.

    boost::optional<double> designSteamVolumeFlowRate() const;
    bool isDesignSteamVolumeFlowRateAutosized() const;
    bool setDesignSteamVolumeFlowRate(double designSteamVolumeFlowRate);
    void resetDesignSteamVolumeFlowRate();
    void autosizeDesignSteamVolumeFlowRate();

    double designPumpHead() const;
    bool isDesignPumpHeadDefaulted() const;
    bool setDesignPumpHead(double designPumpHead);
    void resetDesignPumpHead();

    boost::optional<double> designPowerConsumption() const;
    bool isDesignPowerConsumptionAutosized() const;
    bool setDesignPowerConsumption(double designPowerConsumption);
    void resetDesignPowerConsumption();
    void autosizeDesignPowerConsumption();

    double motorEfficiency() const;
    bool isMotorEfficiencyDefaulted() const;
    bool setMotorEfficiency(double motorEfficiency);
    void resetMotorEfficiency();

    double fractionOfMotorInefficienciesToFluidStream() const;
    bool isFractionOfMotorInefficienciesToFluidStreamDefaulted() const;
    bool setFractionOfMotorInefficienciesToFluidStream(double fractionOfMotorInefficienciesToFluidStream);
    void resetFractionOfMotorInefficienciesToFluidStream();

    double coefficient1OfThePartLoadPerformanceCurve() const;
    bool isCoefficient1OfThePartLoadPerformanceCurveDefaulted() const;
    bool setCoefficient1OfThePartLoadPerformanceCurve(double coefficient1OfThePartLoadPerformanceCurve);
    void resetCoefficient1OfThePartLoadPerformanceCurve();

    double coefficient2OfThePartLoadPerformanceCurve() const;
    bool isCoefficient2OfThePartLoadPerformanceCurveDefaulted() const;
    bool setCoefficient2OfThePartLoadPerformanceCurve(double coefficient2OfThePartLoadPerformanceCurve);
    void resetCoefficient2OfThePartLoadPerformanceCurve();

    double coefficient3OfThePartLoadPerformanceCurve() const;
    bool isCoefficient3OfThePartLoadPerformanceCurveDefaulted() const;
    bool setCoefficient3OfThePartLoadPerformanceCurve(double coefficient3OfThePartLoadPerformanceCurve);
    void resetCoefficient3OfThePartLoadPerformanceCurve();

    double coefficient4OfThePartLoadPerformanceCurve() const;
    bool isCoefficient4OfThePartLoadPerformanceCurveDefaulted() const;
    bool setCoefficient4OfThePartLoadPerformanceCurve(double coefficient4OfThePartLoadPerformanceCurve);
    void resetCoefficient4OfThePartLoadPerformanceCurve();

    boost::optional<double> skinLossRadiativeFraction() const;
    bool setSkinLossRadiativeFraction(double skinLossRadiativeFraction);
    void resetSkinLossRadiativeFraction();

    std::string designPowerSizingMethod() const;
    bool isDesignPowerSizingMethodDefaulted() const;
    bool setDesignPowerSizingMethod(const std::string& designPowerSizingMethod);
    void resetDesignPowerSizingMethod();

    double designElectricPowerPerUnitFlowRate() const;
    bool isDesignElectricPowerPerUnitFlowRateDefaulted() const;
    bool setDesignElectricPowerPerUnitFlowRate(double designElectricPowerPerUnitFlowRate);
    void resetDesignElectricPowerPerUnitFlowRate();

    double designShaftPowerPerUnitFlowRatePerUnitHead() const;
    bool isDesignShaftPowerPerUnitFlowRatePerUnitHeadDefaulted() const;
    bool setDesignShaftPowerPerUnitFlowRatePerUnitHead(double designShaftPowerPerUnitFlowRatePerUnitHead);
    void resetDesignShaftPowerPerUnitFlowRatePerUnitHead();

    std::string endUseSubcategory() const;
    bool isEndUseSubcategoryDefaulted() const;
    bool setEndUseSubcategory(const std::string& endUseSubcategory);
    void resetEndUseSubcategory();

   protected:
    using ImplType = detail::PumpVariableSpeedCondensate_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    explicit PumpVariableSpeedCondensate(std::shared_ptr<detail::PumpVariableSpeedCondensate_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
