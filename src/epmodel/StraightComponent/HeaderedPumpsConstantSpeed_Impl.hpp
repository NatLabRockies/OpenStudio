/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_HEADEREDPUMPSCONSTANTSPEED_IMPL_HPP
#define EPMODEL_HEADEREDPUMPSCONSTANTSPEED_IMPL_HPP

#include "StraightComponent/StraightComponent_Impl.hpp"

#include <boost/optional.hpp>
#include <string>
#include <vector>

namespace openstudio {
namespace epmodel {
namespace detail {

class EPMODEL_API HeaderedPumpsConstantSpeed_Impl : public StraightComponent_Impl
{
 public:
  using StraightComponent_Impl::StraightComponent_Impl;
  virtual ~HeaderedPumpsConstantSpeed_Impl() override = default;

  unsigned inletPort() const override;
  unsigned outletPort() const override;

  boost::optional<double> totalRatedFlowRate() const;
  bool isTotalRatedFlowRateAutosized() const;

  int numberofPumpsinBank() const;

  std::string flowSequencingControlScheme() const;

  double ratedPumpHead() const;

  boost::optional<double> ratedPowerConsumption() const;
  bool isRatedPowerConsumptionAutosized() const;

  double motorEfficiency() const;

  double fractionofMotorInefficienciestoFluidStream() const;

  std::string pumpControlType() const;

  double skinLossRadiativeFraction() const;

  std::string designPowerSizingMethod() const;

  double designElectricPowerPerUnitFlowRate() const;

  double designShaftPowerPerUnitFlowRatePerUnitHead() const;

  std::string endUseSubcategory() const;

  bool setTotalRatedFlowRate(double totalRatedFlowRate);
  void autosizeTotalRatedFlowRate();

  bool setNumberofPumpsinBank(int numberofPumpsinBank);

  bool setFlowSequencingControlScheme(const std::string& flowSequencingControlScheme);

  bool setRatedPumpHead(double ratedPumpHead);

  bool setRatedPowerConsumption(double ratedPowerConsumption);
  void autosizeRatedPowerConsumption();

  bool setMotorEfficiency(double motorEfficiency);

  bool setFractionofMotorInefficienciestoFluidStream(double fractionofMotorInefficienciestoFluidStream);

  bool setPumpControlType(const std::string& pumpControlType);

  bool setSkinLossRadiativeFraction(double skinLossRadiativeFraction);

  bool setDesignPowerSizingMethod(const std::string& designPowerSizingMethod);

  bool setDesignElectricPowerPerUnitFlowRate(double designElectricPowerPerUnitFlowRate);

  bool setDesignShaftPowerPerUnitFlowRatePerUnitHead(double designShaftPowerPerUnitFlowRatePerUnitHead);

  bool setEndUseSubcategory(const std::string& endUseSubcategory);

  boost::optional<double> autosizedTotalRatedFlowRate() const;

  boost::optional<double> autosizedRatedPowerConsumption() const;
};

}  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
