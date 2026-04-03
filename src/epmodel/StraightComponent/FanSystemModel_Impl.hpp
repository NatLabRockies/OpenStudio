/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_FANSYSTEMMODEL_IMPL_HPP
#define EPMODEL_FANSYSTEMMODEL_IMPL_HPP

#include "Node.hpp"
#include "StraightComponent/StraightComponent_Impl.hpp"

#include <boost/optional.hpp>
#include <string>
#include <vector>

namespace openstudio {
namespace epmodel {
class Schedule;
namespace detail {

class EPMODEL_API FanSystemModel_Impl : public StraightComponent_Impl
{
 public:
  using StraightComponent_Impl::StraightComponent_Impl;
  virtual ~FanSystemModel_Impl() override = default;

  bool addToNode(Node& node) override;

  unsigned inletPort() const override;
  unsigned outletPort() const override;
  openstudio::epmodel::Schedule availabilitySchedule() const;
  bool setAvailabilitySchedule(openstudio::epmodel::Schedule& schedule);

  std::vector<std::string> speedControlMethodValues() const;
  std::vector<std::string> designPowerSizingMethodValues() const;

  boost::optional<double> designMaximumAirFlowRate() const;
  bool isDesignMaximumAirFlowRateAutosized() const;
  bool setDesignMaximumAirFlowRate(double designMaximumAirFlowRate);
  void autosizeDesignMaximumAirFlowRate();

  std::string speedControlMethod() const;
  bool setSpeedControlMethod(const std::string& speedControlMethod);

  double electricPowerMinimumFlowRateFraction() const;
  bool setElectricPowerMinimumFlowRateFraction(double electricPowerMinimumFlowRateFraction);

  double designPressureRise() const;
  bool setDesignPressureRise(double designPressureRise);

  double motorEfficiency() const;
  bool setMotorEfficiency(double motorEfficiency);

  double motorInAirStreamFraction() const;
  bool setMotorInAirStreamFraction(double motorInAirStreamFraction);

  boost::optional<double> designElectricPowerConsumption() const;
  bool isDesignElectricPowerConsumptionAutosized() const;
  bool setDesignElectricPowerConsumption(double designElectricPowerConsumption);
  void autosizeDesignElectricPowerConsumption();

  std::string designPowerSizingMethod() const;
  bool setDesignPowerSizingMethod(const std::string& designPowerSizingMethod);

  double electricPowerPerUnitFlowRate() const;
  bool setElectricPowerPerUnitFlowRate(double electricPowerPerUnitFlowRate);

  double electricPowerPerUnitFlowRatePerUnitPressure() const;
  bool setElectricPowerPerUnitFlowRatePerUnitPressure(double electricPowerPerUnitFlowRatePerUnitPressure);

  double fanTotalEfficiency() const;
  bool setFanTotalEfficiency(double fanTotalEfficiency);

  boost::optional<double> nightVentilationModePressureRise() const;
  bool setNightVentilationModePressureRise(double nightVentilationModePressureRise);
  void resetNightVentilationModePressureRise();

  boost::optional<double> nightVentilationModeFlowFraction() const;
  bool setNightVentilationModeFlowFraction(double nightVentilationModeFlowFraction);
  void resetNightVentilationModeFlowFraction();

  double motorLossRadiativeFraction() const;
  bool setMotorLossRadiativeFraction(double motorLossRadiativeFraction);

  std::string endUseSubcategory() const;
  bool setEndUseSubcategory(const std::string& endUseSubcategory);
};

}  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
