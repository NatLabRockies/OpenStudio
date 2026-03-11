/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_HEATEXCHANGERAIRTOAIRSENSIBLEANDLATENT_IMPL_HPP
#define EPMODEL_HEATEXCHANGERAIRTOAIRSENSIBLEANDLATENT_IMPL_HPP

#include "ModelObject_Impl.hpp"

#include <vector>

namespace openstudio {
namespace epmodel {

namespace detail {

class EPMODEL_API HeatExchangerAirToAirSensibleAndLatent_Impl : public ModelObject_Impl
{
 public:
  using ModelObject_Impl::ModelObject_Impl;
  virtual ~HeatExchangerAirToAirSensibleAndLatent_Impl() override = default;

  boost::optional<double> nominalSupplyAirFlowRate() const;
  bool isNominalSupplyAirFlowRateAutosized() const;

  double sensibleEffectivenessat100HeatingAirFlow() const;
  double latentEffectivenessat100HeatingAirFlow() const;
  double sensibleEffectivenessat100CoolingAirFlow() const;
  double latentEffectivenessat100CoolingAirFlow() const;

  double nominalElectricPower() const;

  bool supplyAirOutletTemperatureControl() const;

  std::string heatExchangerType() const;
  std::string frostControlType() const;

  double thresholdTemperature() const;
  bool isThresholdTemperatureDefaulted() const;

  boost::optional<double> initialDefrostTimeFraction() const;
  boost::optional<double> rateofDefrostTimeFractionIncrease() const;

  bool economizerLockout() const;

  bool setNominalSupplyAirFlowRate(double nominalSupplyAirFlowRate);
  void autosizeNominalSupplyAirFlowRate();

  bool setSensibleEffectivenessat100HeatingAirFlow(double sensibleEffectivenessat100HeatingAirFlow);
  bool setLatentEffectivenessat100HeatingAirFlow(double latentEffectivenessat100HeatingAirFlow);
  bool setSensibleEffectivenessat100CoolingAirFlow(double sensibleEffectivenessat100CoolingAirFlow);
  bool setLatentEffectivenessat100CoolingAirFlow(double latentEffectivenessat100CoolingAirFlow);

  bool setNominalElectricPower(double nominalElectricPower);

  bool setSupplyAirOutletTemperatureControl(bool supplyAirOutletTemperatureControl);

  bool setHeatExchangerType(const std::string& heatExchangerType);
  bool setFrostControlType(const std::string& frostControlType);

  bool setThresholdTemperature(double thresholdTemperature);
  void resetThresholdTemperature();

  bool setInitialDefrostTimeFraction(double initialDefrostTimeFraction);
  void resetInitialDefrostTimeFraction();

  bool setRateofDefrostTimeFractionIncrease(double rateofDefrostTimeFractionIncrease);
  void resetRateofDefrostTimeFractionIncrease();

  bool setEconomizerLockout(bool economizerLockout);

 private:
  std::vector<std::string> heatExchangerTypeValues() const;
  std::vector<std::string> frostControlTypeValues() const;
};

}  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
