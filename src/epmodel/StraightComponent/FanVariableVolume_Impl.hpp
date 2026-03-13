/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_FANVARIABLEVOLUME_IMPL_HPP
#define EPMODEL_FANVARIABLEVOLUME_IMPL_HPP

#include "StraightComponent/StraightComponent_Impl.hpp"
#include "Node.hpp"

#include <boost/optional.hpp>
#include <string>
#include <vector>

namespace openstudio {
namespace epmodel {
namespace detail {

class EPMODEL_API FanVariableVolume_Impl : public StraightComponent_Impl
{
 public:
  using StraightComponent_Impl::StraightComponent_Impl;
  virtual ~FanVariableVolume_Impl() override = default;

  unsigned inletPort() const override;
  unsigned outletPort() const override;
  bool addToNode(Node& node) override;

  std::vector<std::string> fanPowerMinimumFlowRateInputMethodValues() const;

  double fanTotalEfficiency() const;
  bool isFanTotalEfficiencyDefaulted() const;
  bool setFanTotalEfficiency(double fanTotalEfficiency);
  void resetFanTotalEfficiency();

  double pressureRise() const;
  bool setPressureRise(double pressureRise);

  boost::optional<double> maximumFlowRate() const;
  bool isMaximumFlowRateAutosized() const;
  bool setMaximumFlowRate(double maximumFlowRate);
  void resetMaximumFlowRate();
  void autosizeMaximumFlowRate();

  std::string fanPowerMinimumFlowRateInputMethod() const;
  bool isFanPowerMinimumFlowRateInputMethodDefaulted() const;
  bool setFanPowerMinimumFlowRateInputMethod(const std::string& fanPowerMinimumFlowRateInputMethod);
  void resetFanPowerMinimumFlowRateInputMethod();

  double fanPowerMinimumFlowFraction() const;
  bool isFanPowerMinimumFlowFractionDefaulted() const;
  bool setFanPowerMinimumFlowFraction(double fanPowerMinimumFlowFraction);
  void resetFanPowerMinimumFlowFraction();

  boost::optional<double> fanPowerMinimumAirFlowRate() const;
  bool setFanPowerMinimumAirFlowRate(double fanPowerMinimumAirFlowRate);
  void resetFanPowerMinimumAirFlowRate();

  double motorEfficiency() const;
  bool isMotorEfficiencyDefaulted() const;
  bool setMotorEfficiency(double motorEfficiency);
  void resetMotorEfficiency();

  double motorInAirstreamFraction() const;
  bool isMotorInAirstreamFractionDefaulted() const;
  bool setMotorInAirstreamFraction(double motorInAirstreamFraction);
  void resetMotorInAirstreamFraction();

  boost::optional<double> fanPowerCoefficient1() const;
  bool setFanPowerCoefficient1(double fanPowerCoefficient1);
  void resetFanPowerCoefficient1();

  boost::optional<double> fanPowerCoefficient2() const;
  bool setFanPowerCoefficient2(double fanPowerCoefficient2);
  void resetFanPowerCoefficient2();

  boost::optional<double> fanPowerCoefficient3() const;
  bool setFanPowerCoefficient3(double fanPowerCoefficient3);
  void resetFanPowerCoefficient3();

  boost::optional<double> fanPowerCoefficient4() const;
  bool setFanPowerCoefficient4(double fanPowerCoefficient4);
  void resetFanPowerCoefficient4();

  boost::optional<double> fanPowerCoefficient5() const;
  bool setFanPowerCoefficient5(double fanPowerCoefficient5);
  void resetFanPowerCoefficient5();

  std::string endUseSubcategory() const;
  bool isEndUseSubcategoryDefaulted() const;
  bool setEndUseSubcategory(const std::string& endUseSubcategory);
  void resetEndUseSubcategory();
};

}  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
