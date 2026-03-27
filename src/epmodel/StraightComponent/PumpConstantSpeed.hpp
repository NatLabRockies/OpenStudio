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
    // - Status: Scalar Parity. The canonical scalar pump surface is largely present, while schedule, curve, zone, and richer relationship helpers remain out of scope.
    // - Canonical Counterpart: openstudio::model::PumpConstantSpeed.
    // - Implemented Parity: Preserved scalar accessor names/signatures cover flow, head, power, efficiency, control type, impeller/rotation, radiative fraction, design-power sizing, and end-use metadata with matching autosize semantics.
    // - Documented Delta: `pumpFlowRateSchedule`, `pumpCurve`, thermal-zone linkage, and explicit node-link convenience APIs are not exposed yet, so parity currently stops at the canonical scalar surface.
    // - Field/Storage Mapping: The preserved scalar APIs map directly to EnergyPlus `Pump:ConstantSpeed` scalar fields used by the forward translator.
    // - Evidence: `src/model/PumpConstantSpeed.hpp` defines the canonical wrapper surface, and `src/energyplus/ForwardTranslator/ForwardTranslatePumpConstantSpeed.cpp` confirms the direct scalar field mapping and autosize tokens.
    // - Remaining Parity Work: Add the omitted schedule, curve, thermal-zone, and relationship helpers without changing the preserved scalar signatures.

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
