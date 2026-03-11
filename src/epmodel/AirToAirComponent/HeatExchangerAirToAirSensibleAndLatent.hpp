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
