/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_GENERATORWINDTURBINE_IMPL_HPP
#define EPMODEL_GENERATORWINDTURBINE_IMPL_HPP

#include "ModelObject/ModelObject_Impl.hpp"

#include <vector>

namespace openstudio {
namespace epmodel {

namespace detail {

class EPMODEL_API GeneratorWindTurbine_Impl : public ModelObject_Impl
{
 public:
  using ModelObject_Impl::ModelObject_Impl;
  virtual ~GeneratorWindTurbine_Impl() override = default;

  std::string rotorType() const;
  std::string powerControl() const;
  double ratedRotorSpeed() const;
  double rotorDiameter() const;
  double overallHeight() const;
  int numberofBlades() const;
  double ratedPower() const;
  double ratedWindSpeed() const;
  double cutInWindSpeed() const;
  double cutOutWindSpeed() const;
  double fractionSystemEfficiency() const;
  double maximumTipSpeedRatio() const;
  double maximumPowerCoefficient() const;
  boost::optional<double> annualLocalAverageWindSpeed() const;
  double heightforLocalAverageWindSpeed() const;
  double bladeChordArea() const;
  double bladeDragCoefficient() const;
  double bladeLiftCoefficient() const;
  double powerCoefficientC1() const;
  double powerCoefficientC2() const;
  double powerCoefficientC3() const;
  double powerCoefficientC4() const;
  double powerCoefficientC5() const;
  double powerCoefficientC6() const;

  bool setRotorType(const std::string& rotorType);
  bool setPowerControl(const std::string& powerControl);
  bool setRatedRotorSpeed(double ratedRotorSpeed);
  bool setRotorDiameter(double rotorDiameter);
  bool setOverallHeight(double overallHeight);
  bool setNumberofBlades(int numberofBlades);
  bool setRatedPower(double ratedPower);
  bool setRatedWindSpeed(double ratedWindSpeed);
  bool setCutInWindSpeed(double cutInWindSpeed);
  bool setCutOutWindSpeed(double cutOutWindSpeed);
  bool setFractionSystemEfficiency(double fractionSystemEfficiency);
  bool setMaximumTipSpeedRatio(double maximumTipSpeedRatio);
  bool setMaximumPowerCoefficient(double maximumPowerCoefficient);
  bool setAnnualLocalAverageWindSpeed(double annualLocalAverageWindSpeed);
  void resetAnnualLocalAverageWindSpeed();
  bool setHeightforLocalAverageWindSpeed(double heightforLocalAverageWindSpeed);
  bool setBladeChordArea(double bladeChordArea);
  bool setBladeDragCoefficient(double bladeDragCoefficient);
  bool setBladeLiftCoefficient(double bladeLiftCoefficient);
  bool setPowerCoefficientC1(double powerCoefficientC1);
  bool setPowerCoefficientC2(double powerCoefficientC2);
  bool setPowerCoefficientC3(double powerCoefficientC3);
  bool setPowerCoefficientC4(double powerCoefficientC4);
  bool setPowerCoefficientC5(double powerCoefficientC5);
  bool setPowerCoefficientC6(double powerCoefficientC6);

  std::vector<std::string> rotorTypeValues() const;
  std::vector<std::string> powerControlValues() const;
};

}  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
