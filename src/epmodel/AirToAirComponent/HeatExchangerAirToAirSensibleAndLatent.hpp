/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_HEATEXCHANGERAIRTOAIRSENSIBLEANDLATENT_HPP
#define EPMODEL_HEATEXCHANGERAIRTOAIRSENSIBLEANDLATENT_HPP

#include "EPModelAPI.hpp"
#include "ModelObject.hpp"

#include <utilities/idd/IddEnums.hxx>

#include <memory>
#include <vector>

namespace openstudio {
namespace epmodel {

  class Model;

  namespace detail {
    class HeatExchangerAirToAirSensibleAndLatent_Impl;
  }

  class EPMODEL_API HeatExchangerAirToAirSensibleAndLatent : public ModelObject
  {
   public:
    explicit HeatExchangerAirToAirSensibleAndLatent(const Model& model);

    virtual ~HeatExchangerAirToAirSensibleAndLatent() override = default;
    HeatExchangerAirToAirSensibleAndLatent(const HeatExchangerAirToAirSensibleAndLatent& other) = default;
    HeatExchangerAirToAirSensibleAndLatent(HeatExchangerAirToAirSensibleAndLatent&& other) = default;
    HeatExchangerAirToAirSensibleAndLatent& operator=(const HeatExchangerAirToAirSensibleAndLatent&) = default;
    HeatExchangerAirToAirSensibleAndLatent& operator=(HeatExchangerAirToAirSensibleAndLatent&&) = default;

    static IddObjectType iddObjectType();

    static std::vector<std::string> heatExchangerTypeValues();
    static std::vector<std::string> frostControlTypeValues();

    // Schema Alignment Notes:
    // - Status: Partial Parity. Scalar effectiveness and control fields are aligned, but the canonical relationship/performance-surface is still incomplete.
    // - Canonical Counterpart: openstudio::model::HeatExchangerAirToAirSensibleAndLatent.
    // - Implemented Parity: The scalar effectiveness, frost-control, defrost, and economizer-lockout accessors preserve the canonical model-facing field semantics.
    // - Documented Delta: Epmodel does not yet expose the canonical availability schedule, curve/table relationship APIs, or the historical 75% effectiveness compatibility helpers that remain part of `openstudio::model`.
    // - Field/Storage Mapping: Preserved scalar APIs map directly to `HeatExchanger:AirToAir:SensibleAndLatent` fields in EnergyPlus storage.
    // - Evidence: `src/model/HeatExchangerAirToAirSensibleAndLatent.hpp`, `src/model/HeatExchangerAirToAirSensibleAndLatent.cpp`, and `src/energyplus/ForwardTranslator/ForwardTranslateHeatExchangerAirToAirSensibleAndLatent.cpp` define the canonical surface and scalar translation behavior.
    // - Remaining Parity Work: Add the schedule and curve/table relationship APIs, plus any remaining compatibility helpers, when the epmodel relationship surface is ready for them.
    /** @name Field Accessors */
    //@{

    boost::optional<double> nominalSupplyAirFlowRate() const;
    bool setNominalSupplyAirFlowRate(double nominalSupplyAirFlowRate);
    bool isNominalSupplyAirFlowRateAutosized() const;
    void autosizeNominalSupplyAirFlowRate();

    double sensibleEffectivenessat100HeatingAirFlow() const;
    bool setSensibleEffectivenessat100HeatingAirFlow(double sensibleEffectivenessat100HeatingAirFlow);

    double latentEffectivenessat100HeatingAirFlow() const;
    bool setLatentEffectivenessat100HeatingAirFlow(double latentEffectivenessat100HeatingAirFlow);

    double sensibleEffectivenessat100CoolingAirFlow() const;
    bool setSensibleEffectivenessat100CoolingAirFlow(double sensibleEffectivenessat100CoolingAirFlow);

    double latentEffectivenessat100CoolingAirFlow() const;
    bool setLatentEffectivenessat100CoolingAirFlow(double latentEffectivenessat100CoolingAirFlow);

    double nominalElectricPower() const;
    bool setNominalElectricPower(double nominalElectricPower);

    bool supplyAirOutletTemperatureControl() const;
    bool setSupplyAirOutletTemperatureControl(bool supplyAirOutletTemperatureControl);

    std::string heatExchangerType() const;
    bool setHeatExchangerType(const std::string& heatExchangerType);

    std::string frostControlType() const;
    bool setFrostControlType(const std::string& frostControlType);

    double thresholdTemperature() const;
    bool setThresholdTemperature(double thresholdTemperature);
    bool isThresholdTemperatureDefaulted() const;
    void resetThresholdTemperature();

    boost::optional<double> initialDefrostTimeFraction() const;
    bool setInitialDefrostTimeFraction(double initialDefrostTimeFraction);
    void resetInitialDefrostTimeFraction();

    boost::optional<double> rateofDefrostTimeFractionIncrease() const;
    bool setRateofDefrostTimeFractionIncrease(double rateofDefrostTimeFractionIncrease);
    void resetRateofDefrostTimeFractionIncrease();

    bool economizerLockout() const;
    bool setEconomizerLockout(bool economizerLockout);

    //@}

   protected:
    using ImplType = detail::HeatExchangerAirToAirSensibleAndLatent_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    explicit HeatExchangerAirToAirSensibleAndLatent(std::shared_ptr<detail::HeatExchangerAirToAirSensibleAndLatent_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
