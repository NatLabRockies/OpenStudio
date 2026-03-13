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
    // - API: Preserve openstudio::model scalar accessor names/signatures for counterpart compatibility.
    // - Field Mapping: Preserved scalar APIs map directly to EnergyPlus HeatExchanger:AirToAir:SensibleAndLatent scalar fields.
    // - Field Mapping: Relationship fields (availability schedule, node names, curve references) are intentionally excluded.
    // - TODO(parity): Add non-scalar relationship parity incrementally after scalar scaffold saturation.
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
