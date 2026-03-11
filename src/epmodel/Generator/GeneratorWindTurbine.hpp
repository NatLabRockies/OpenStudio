/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_GENERATORWINDTURBINE_HPP
#define EPMODEL_GENERATORWINDTURBINE_HPP

#include "EPModelAPI.hpp"
#include "ModelObject/ModelObject.hpp"

#include <utilities/idd/IddEnums.hxx>

#include <memory>
#include <vector>

namespace openstudio {
namespace epmodel {

class Model;

namespace detail {
class GeneratorWindTurbine_Impl;
}

class EPMODEL_API GeneratorWindTurbine : public ModelObject
{
 public:
  explicit GeneratorWindTurbine(const Model& model);

  virtual ~GeneratorWindTurbine() override = default;
  GeneratorWindTurbine(const GeneratorWindTurbine& other) = default;
  GeneratorWindTurbine(GeneratorWindTurbine&& other) = default;
  GeneratorWindTurbine& operator=(const GeneratorWindTurbine&) = default;
  GeneratorWindTurbine& operator=(GeneratorWindTurbine&&) = default;

  static IddObjectType iddObjectType();

  static std::vector<std::string> rotorTypeValues();
  static std::vector<std::string> powerControlValues();

  // Schema Alignment Notes:
  // - API: Preserves openstudio::model::GeneratorWindTurbine scalar accessor names/signatures for counterpart parity.
  // - Field Mapping: Preserved scalar APIs map directly to EnergyPlus Generator:WindTurbine scalar fields.
  // - ForwardTranslator evidence: ForwardTranslateGeneratorWindTurbine writes these scalar APIs directly to matching
  //   Generator:WindTurbine fields.
  // - API: AvailabilitySchedule remains excluded in this scalar-only pass because it is a relationship field.
  // - TODO(parity): Add relationship APIs in a dedicated relationship pass.
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

 protected:
  using ImplType = detail::GeneratorWindTurbine_Impl;

  friend class Model;
  friend class openstudio::IdfObject;
  friend class openstudio::detail::IdfObject_Impl;

  explicit GeneratorWindTurbine(std::shared_ptr<detail::GeneratorWindTurbine_Impl> impl);
};

}  // namespace epmodel
}  // namespace openstudio

#endif
