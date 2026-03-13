/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_PUMPCONSTANTSPEED_HPP
#define EPMODEL_PUMPCONSTANTSPEED_HPP

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
    class PumpConstantSpeed_Impl;
  }

  class EPMODEL_API PumpConstantSpeed : public StraightComponent
  {
   public:
    explicit PumpConstantSpeed(const Model& model);

    virtual ~PumpConstantSpeed() override = default;
    PumpConstantSpeed(const PumpConstantSpeed& other) = default;
    PumpConstantSpeed(PumpConstantSpeed&& other) = default;
    PumpConstantSpeed& operator=(const PumpConstantSpeed&) = default;
    PumpConstantSpeed& operator=(PumpConstantSpeed&&) = default;

    static IddObjectType iddObjectType();

    static std::vector<std::string> pumpControlTypeValues();
    static std::vector<std::string> designPowerSizingMethodValues();

    // Schema Alignment Notes:
    // - API: Preserve openstudio::model::PumpConstantSpeed scalar method names/signatures for exact model-counterpart parity.
    // - Field Mapping: ratedFlowRate/totalDesignFlowRate, ratedPumpHead/designPumpHead, ratedPowerConsumption/designPowerConsumption,
    //   motorEfficiency, fractionofMotorInefficienciestoFluidStream, pumpControlType, impellerDiameter, rotationalSpeed,
    //   skinLossRadiativeFraction map directly to the EnergyPlus OS:Pump:ConstantSpeed scalar fields, and designPowerSizingMethod,
    //   designElectricPowerPerUnitFlowRate, designShaftPowerPerUnitFlowRatePerUnitHead, and endUseSubcategory match the E+ fields listed.
    // - Field Mapping: pumpFlowRateSchedule, pumpCurve, zone linkage, and inlet/outlet node relationships are intentionally excluded from this scalar-only pass.
    // - ForwardTranslator evidence: ForwardTranslatePumpConstantSpeed.cpp confirms these field mappings and autosize semantics.
    // - TODO(parity): Add the relationship APIs once the scalar saturation milestone is complete without changing existing scalar signatures.

    // ratedFlowRate
    boost::optional<double> ratedFlowRate() const;
    bool isRatedFlowRateAutosized() const;
    bool setRatedFlowRate(double ratedFlowRate);
    void resetRatedFlowRate();
    void autosizeRatedFlowRate();
    boost::optional<double> autosizedRatedFlowRate() const;

    // ratedPumpHead
    double ratedPumpHead() const;
    bool isRatedPumpHeadDefaulted() const;
    bool setRatedPumpHead(double ratedPumpHead);
    void resetRatedPumpHead();

    // ratedPowerConsumption
    boost::optional<double> ratedPowerConsumption() const;
    bool isRatedPowerConsumptionAutosized() const;
    bool setRatedPowerConsumption(double ratedPowerConsumption);
    void resetRatedPowerConsumption();
    void autosizeRatedPowerConsumption();
    boost::optional<double> autosizedRatedPowerConsumption() const;

    // motorEfficiency
    double motorEfficiency() const;
    bool isMotorEfficiencyDefaulted() const;
    bool setMotorEfficiency(double motorEfficiency);
    void resetMotorEfficiency();

    // fractionofMotorInefficienciestoFluidStream
    double fractionofMotorInefficienciestoFluidStream() const;
    bool isFractionofMotorInefficienciestoFluidStreamDefaulted() const;
    bool setFractionofMotorInefficienciestoFluidStream(double fractionofMotorInefficienciestoFluidStream);
    void resetFractionofMotorInefficienciestoFluidStream();

    // pumpControlType
    std::string pumpControlType() const;
    bool isPumpControlTypeDefaulted() const;
    bool setPumpControlType(const std::string& pumpControlType);
    void resetPumpControlType();

    // impellerDiameter
    boost::optional<double> impellerDiameter() const;
    bool setImpellerDiameter(double impellerDiameter);
    void resetImpellerDiameter();

    // rotationalSpeed
    boost::optional<double> rotationalSpeed() const;
    bool setRotationalSpeed(double rotationalSpeed);
    void resetRotationalSpeed();

    // skinLossRadiativeFraction
    boost::optional<double> skinLossRadiativeFraction() const;
    bool setSkinLossRadiativeFraction(double skinLossRadiativeFraction);
    void resetSkinLossRadiativeFraction();

    // designPowerSizingMethod
    std::string designPowerSizingMethod() const;
    bool setDesignPowerSizingMethod(const std::string& designPowerSizingMethod);

    // designElectricPowerPerUnitFlowRate
    double designElectricPowerPerUnitFlowRate() const;
    bool setDesignElectricPowerPerUnitFlowRate(double designElectricPowerPerUnitFlowRate);

    // designShaftPowerPerUnitFlowRatePerUnitHead
    double designShaftPowerPerUnitFlowRatePerUnitHead() const;
    bool setDesignShaftPowerPerUnitFlowRatePerUnitHead(double designShaftPowerPerUnitFlowRatePerUnitHead);

    // endUseSubcategory
    std::string endUseSubcategory() const;
    bool setEndUseSubcategory(const std::string& endUseSubcategory);

   protected:
    using ImplType = detail::PumpConstantSpeed_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    explicit PumpConstantSpeed(std::shared_ptr<detail::PumpConstantSpeed_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
