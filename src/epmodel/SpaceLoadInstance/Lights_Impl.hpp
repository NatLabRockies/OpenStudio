/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_LIGHTS_IMPL_HPP
#define EPMODEL_LIGHTS_IMPL_HPP

#include "ModelObject_Impl.hpp"

#include <vector>

namespace openstudio {
namespace epmodel {

namespace detail {

class EPMODEL_API Lights_Impl : public ModelObject_Impl
{
 public:
  using ModelObject_Impl::ModelObject_Impl;
  virtual ~Lights_Impl() override = default;

  std::string designLevelCalculationMethod() const;
  bool isDesignLevelCalculationMethodDefaulted() const;
  bool setDesignLevelCalculationMethod(const std::string& designLevelCalculationMethod);
  void resetDesignLevelCalculationMethod();

  boost::optional<double> lightingLevel() const;
  bool setLightingLevel(double lightingLevel);
  void resetLightingLevel();

  boost::optional<double> powerPerFloorArea() const;
  bool setPowerPerFloorArea(double powerPerFloorArea);
  void resetPowerPerFloorArea();

  boost::optional<double> powerPerPerson() const;
  bool setPowerPerPerson(double powerPerPerson);
  void resetPowerPerPerson();

  double returnAirFraction() const;
  bool isReturnAirFractionDefaulted() const;
  bool setReturnAirFraction(double returnAirFraction);
  void resetReturnAirFraction();

  double fractionRadiant() const;
  bool isFractionRadiantDefaulted() const;
  bool setFractionRadiant(double fractionRadiant);
  void resetFractionRadiant();

  double fractionVisible() const;
  bool isFractionVisibleDefaulted() const;
  bool setFractionVisible(double fractionVisible);
  void resetFractionVisible();

  double fractionReplaceable() const;
  bool isFractionReplaceableDefaulted() const;
  bool setFractionReplaceable(double fractionReplaceable);
  void resetFractionReplaceable();

  std::string endUseSubcategory() const;
  bool isEndUseSubcategoryDefaulted() const;
  bool setEndUseSubcategory(const std::string& endUseSubcategory);
  void resetEndUseSubcategory();

  bool returnAirFractionCalculatedfromPlenumTemperature() const;
  bool isReturnAirFractionCalculatedfromPlenumTemperatureDefaulted() const;
  bool setReturnAirFractionCalculatedfromPlenumTemperature(bool returnAirFractionCalculatedfromPlenumTemperature);
  void resetReturnAirFractionCalculatedfromPlenumTemperature();

  double returnAirFractionFunctionofPlenumTemperatureCoefficient1() const;
  bool isReturnAirFractionFunctionofPlenumTemperatureCoefficient1Defaulted() const;
  bool setReturnAirFractionFunctionofPlenumTemperatureCoefficient1(double returnAirFractionFunctionofPlenumTemperatureCoefficient1);
  void resetReturnAirFractionFunctionofPlenumTemperatureCoefficient1();

  double returnAirFractionFunctionofPlenumTemperatureCoefficient2() const;
  bool isReturnAirFractionFunctionofPlenumTemperatureCoefficient2Defaulted() const;
  bool setReturnAirFractionFunctionofPlenumTemperatureCoefficient2(double returnAirFractionFunctionofPlenumTemperatureCoefficient2);
  void resetReturnAirFractionFunctionofPlenumTemperatureCoefficient2();

  bool setMultiplier(double multiplier);
  void resetMultiplier();

  std::vector<std::string> designLevelCalculationMethodValues() const;
};

}  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
