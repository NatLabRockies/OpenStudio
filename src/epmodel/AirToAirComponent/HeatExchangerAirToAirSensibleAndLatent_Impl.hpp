/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_HEATEXCHANGERAIRTOAIRSENSIBLEANDLATENT_IMPL_HPP
#define EPMODEL_HEATEXCHANGERAIRTOAIRSENSIBLEANDLATENT_IMPL_HPP

#include "AirToAirComponent/AirToAirComponent_Impl.hpp"

#include <vector>

namespace openstudio {
namespace epmodel {

  namespace detail {

    class EPMODEL_API HeatExchangerAirToAirSensibleAndLatent_Impl : public AirToAirComponent_Impl
    {
     public:
      HeatExchangerAirToAirSensibleAndLatent_Impl(const IdfObject& idfObject, Model_Impl* model, bool keepHandle);
      HeatExchangerAirToAirSensibleAndLatent_Impl(const openstudio::detail::WorkspaceObject_Impl& other, Model_Impl* model, bool keepHandle);
      HeatExchangerAirToAirSensibleAndLatent_Impl(const HeatExchangerAirToAirSensibleAndLatent_Impl& other, Model_Impl* model, bool keepHandle);
      virtual ~HeatExchangerAirToAirSensibleAndLatent_Impl() override = default;

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

      unsigned primaryAirInletPort() const override;
      unsigned primaryAirOutletPort() const override;
      unsigned secondaryAirInletPort() const override;
      unsigned secondaryAirOutletPort() const override;

     private:
      std::vector<std::string> heatExchangerTypeValues() const;
      std::vector<std::string> frostControlTypeValues() const;
    };

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
