/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_HUMIDIFIERSTEAMGAS_IMPL_HPP
#define EPMODEL_HUMIDIFIERSTEAMGAS_IMPL_HPP

#include "StraightComponent/StraightComponent_Impl.hpp"

#include <vector>

namespace openstudio {
namespace epmodel {
namespace detail {

class EPMODEL_API HumidifierSteamGas_Impl : public StraightComponent_Impl
{
 public:
  using StraightComponent_Impl::StraightComponent_Impl;
  virtual ~HumidifierSteamGas_Impl() override = default;

  unsigned inletPort() const override;
  unsigned outletPort() const override;

  boost::optional<double> ratedCapacity() const;
  bool isRatedCapacityAutosized() const;

  boost::optional<double> ratedGasUseRate() const;
  bool isRatedGasUseRateAutosized() const;

  double thermalEfficiency() const;
  bool isThermalEfficiencyDefaulted() const;

  boost::optional<double> ratedFanPower() const;

  double auxiliaryElectricPower() const;
  bool isAuxiliaryElectricPowerDefaulted() const;

  std::string inletWaterTemperatureOption() const;
  bool isInletWaterTemperatureOptionDefaulted() const;

  bool setRatedCapacity(double ratedCapacity);
  void autosizeRatedCapacity();

  bool setRatedGasUseRate(double ratedGasUseRate);
  void resetRatedGasUseRate();
  void autosizeRatedGasUseRate();

  bool setThermalEfficiency(double thermalEfficiency);
  void resetThermalEfficiency();

  bool setRatedFanPower(double ratedFanPower);
  void resetRatedFanPower();

  bool setAuxiliaryElectricPower(double auxiliaryElectricPower);
  void resetAuxiliaryElectricPower();

  bool setInletWaterTemperatureOption(const std::string& inletWaterTemperatureOption);
  void resetInletWaterTemperatureOption();

  boost::optional<double> autosizedRatedCapacity() const;
  boost::optional<double> autosizedRatedGasUseRate() const;

  std::vector<std::string> inletWaterTemperatureOptionValues() const;
};

}  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
