/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_EVAPORATIVECOOLERDIRECTRESEARCHSPECIAL_IMPL_HPP
#define EPMODEL_EVAPORATIVECOOLERDIRECTRESEARCHSPECIAL_IMPL_HPP

#include "StraightComponent/StraightComponent_Impl.hpp"

namespace openstudio {
namespace epmodel {
namespace detail {

class EPMODEL_API EvaporativeCoolerDirectResearchSpecial_Impl : public StraightComponent_Impl
{
 public:
  using StraightComponent_Impl::StraightComponent_Impl;
  virtual ~EvaporativeCoolerDirectResearchSpecial_Impl() override = default;

  unsigned inletPort() const override;
  unsigned outletPort() const override;

  double coolerDesignEffectiveness() const;
  bool setCoolerDesignEffectiveness(double value);

  boost::optional<double> recirculatingWaterPumpPowerConsumption() const;
  bool setRecirculatingWaterPumpPowerConsumption(double value);
  void autosizeRecirculatingWaterPumpPowerConsumption();
  bool isRecirculatingWaterPumpPowerConsumptionAutosized() const;

  boost::optional<double> primaryAirDesignFlowRate() const;
  bool setPrimaryAirDesignFlowRate(double value);
  void autosizePrimaryAirDesignFlowRate();
  bool isPrimaryAirDesignFlowRateAutosized() const;

  double driftLossFraction() const;
  bool setDriftLossFraction(double value);

  double blowdownConcentrationRatio() const;
  bool setBlowdownConcentrationRatio(double value);

  double waterPumpPowerSizingFactor() const;
  bool setWaterPumpPowerSizingFactor(double waterPumpPowerSizingFactor);

  double evaporativeOperationMinimumDrybulbTemperature() const;
  bool setEvaporativeOperationMinimumDrybulbTemperature(double evaporativeOperationMinimumDrybulbTemperature);

  double evaporativeOperationMaximumLimitWetbulbTemperature() const;
  bool setEvaporativeOperationMaximumLimitWetbulbTemperature(double evaporativeOperationMaximumLimitWetbulbTemperature);

  double evaporativeOperationMaximumLimitDrybulbTemperature() const;
  bool setEvaporativeOperationMaximumLimitDrybulbTemperature(double evaporativeOperationMaximumLimitDrybulbTemperature);

  boost::optional<double> autosizedRecirculatingWaterPumpPowerConsumption() const;
  boost::optional<double> autosizedPrimaryAirDesignFlowRate() const;
};

}  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
