/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "GeneratorWindTurbine.hpp"
#include "GeneratorWindTurbine_Impl.hpp"

#include "Model.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/idd/Generator_WindTurbine_FieldEnums.hxx>
#include <utilities/idd/IddEnums.hxx>
#include <utilities/idd/IddFactory.hxx>
#include <utilities/idd/IddObject.hpp>

namespace openstudio {
namespace epmodel {

GeneratorWindTurbine::GeneratorWindTurbine(const Model& model) : ModelObject(GeneratorWindTurbine::iddObjectType(), model) {}

GeneratorWindTurbine::GeneratorWindTurbine(std::shared_ptr<detail::GeneratorWindTurbine_Impl> impl) : ModelObject(std::move(impl)) {}

IddObjectType GeneratorWindTurbine::iddObjectType() {
  return IddObjectType::Generator_WindTurbine;
}

std::vector<std::string> GeneratorWindTurbine::rotorTypeValues() {
  return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(), openstudio::Generator_WindTurbineFields::RotorType);
}

std::vector<std::string> GeneratorWindTurbine::powerControlValues() {
  return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(), openstudio::Generator_WindTurbineFields::PowerControl);
}

std::string GeneratorWindTurbine::rotorType() const {
  return getImpl<detail::GeneratorWindTurbine_Impl>()->rotorType();
}

std::string GeneratorWindTurbine::powerControl() const {
  return getImpl<detail::GeneratorWindTurbine_Impl>()->powerControl();
}

double GeneratorWindTurbine::ratedRotorSpeed() const {
  return getImpl<detail::GeneratorWindTurbine_Impl>()->ratedRotorSpeed();
}

double GeneratorWindTurbine::rotorDiameter() const {
  return getImpl<detail::GeneratorWindTurbine_Impl>()->rotorDiameter();
}

double GeneratorWindTurbine::overallHeight() const {
  return getImpl<detail::GeneratorWindTurbine_Impl>()->overallHeight();
}

int GeneratorWindTurbine::numberofBlades() const {
  return getImpl<detail::GeneratorWindTurbine_Impl>()->numberofBlades();
}

double GeneratorWindTurbine::ratedPower() const {
  return getImpl<detail::GeneratorWindTurbine_Impl>()->ratedPower();
}

double GeneratorWindTurbine::ratedWindSpeed() const {
  return getImpl<detail::GeneratorWindTurbine_Impl>()->ratedWindSpeed();
}

double GeneratorWindTurbine::cutInWindSpeed() const {
  return getImpl<detail::GeneratorWindTurbine_Impl>()->cutInWindSpeed();
}

double GeneratorWindTurbine::cutOutWindSpeed() const {
  return getImpl<detail::GeneratorWindTurbine_Impl>()->cutOutWindSpeed();
}

double GeneratorWindTurbine::fractionSystemEfficiency() const {
  return getImpl<detail::GeneratorWindTurbine_Impl>()->fractionSystemEfficiency();
}

double GeneratorWindTurbine::maximumTipSpeedRatio() const {
  return getImpl<detail::GeneratorWindTurbine_Impl>()->maximumTipSpeedRatio();
}

double GeneratorWindTurbine::maximumPowerCoefficient() const {
  return getImpl<detail::GeneratorWindTurbine_Impl>()->maximumPowerCoefficient();
}

boost::optional<double> GeneratorWindTurbine::annualLocalAverageWindSpeed() const {
  return getImpl<detail::GeneratorWindTurbine_Impl>()->annualLocalAverageWindSpeed();
}

double GeneratorWindTurbine::heightforLocalAverageWindSpeed() const {
  return getImpl<detail::GeneratorWindTurbine_Impl>()->heightforLocalAverageWindSpeed();
}

double GeneratorWindTurbine::bladeChordArea() const {
  return getImpl<detail::GeneratorWindTurbine_Impl>()->bladeChordArea();
}

double GeneratorWindTurbine::bladeDragCoefficient() const {
  return getImpl<detail::GeneratorWindTurbine_Impl>()->bladeDragCoefficient();
}

double GeneratorWindTurbine::bladeLiftCoefficient() const {
  return getImpl<detail::GeneratorWindTurbine_Impl>()->bladeLiftCoefficient();
}

double GeneratorWindTurbine::powerCoefficientC1() const {
  return getImpl<detail::GeneratorWindTurbine_Impl>()->powerCoefficientC1();
}

double GeneratorWindTurbine::powerCoefficientC2() const {
  return getImpl<detail::GeneratorWindTurbine_Impl>()->powerCoefficientC2();
}

double GeneratorWindTurbine::powerCoefficientC3() const {
  return getImpl<detail::GeneratorWindTurbine_Impl>()->powerCoefficientC3();
}

double GeneratorWindTurbine::powerCoefficientC4() const {
  return getImpl<detail::GeneratorWindTurbine_Impl>()->powerCoefficientC4();
}

double GeneratorWindTurbine::powerCoefficientC5() const {
  return getImpl<detail::GeneratorWindTurbine_Impl>()->powerCoefficientC5();
}

double GeneratorWindTurbine::powerCoefficientC6() const {
  return getImpl<detail::GeneratorWindTurbine_Impl>()->powerCoefficientC6();
}

bool GeneratorWindTurbine::setRotorType(const std::string& rotorType) {
  return getImpl<detail::GeneratorWindTurbine_Impl>()->setRotorType(rotorType);
}

bool GeneratorWindTurbine::setPowerControl(const std::string& powerControl) {
  return getImpl<detail::GeneratorWindTurbine_Impl>()->setPowerControl(powerControl);
}

bool GeneratorWindTurbine::setRatedRotorSpeed(double ratedRotorSpeed) {
  return getImpl<detail::GeneratorWindTurbine_Impl>()->setRatedRotorSpeed(ratedRotorSpeed);
}

bool GeneratorWindTurbine::setRotorDiameter(double rotorDiameter) {
  return getImpl<detail::GeneratorWindTurbine_Impl>()->setRotorDiameter(rotorDiameter);
}

bool GeneratorWindTurbine::setOverallHeight(double overallHeight) {
  return getImpl<detail::GeneratorWindTurbine_Impl>()->setOverallHeight(overallHeight);
}

bool GeneratorWindTurbine::setNumberofBlades(int numberofBlades) {
  return getImpl<detail::GeneratorWindTurbine_Impl>()->setNumberofBlades(numberofBlades);
}

bool GeneratorWindTurbine::setRatedPower(double ratedPower) {
  return getImpl<detail::GeneratorWindTurbine_Impl>()->setRatedPower(ratedPower);
}

bool GeneratorWindTurbine::setRatedWindSpeed(double ratedWindSpeed) {
  return getImpl<detail::GeneratorWindTurbine_Impl>()->setRatedWindSpeed(ratedWindSpeed);
}

bool GeneratorWindTurbine::setCutInWindSpeed(double cutInWindSpeed) {
  return getImpl<detail::GeneratorWindTurbine_Impl>()->setCutInWindSpeed(cutInWindSpeed);
}

bool GeneratorWindTurbine::setCutOutWindSpeed(double cutOutWindSpeed) {
  return getImpl<detail::GeneratorWindTurbine_Impl>()->setCutOutWindSpeed(cutOutWindSpeed);
}

bool GeneratorWindTurbine::setFractionSystemEfficiency(double fractionSystemEfficiency) {
  return getImpl<detail::GeneratorWindTurbine_Impl>()->setFractionSystemEfficiency(fractionSystemEfficiency);
}

bool GeneratorWindTurbine::setMaximumTipSpeedRatio(double maximumTipSpeedRatio) {
  return getImpl<detail::GeneratorWindTurbine_Impl>()->setMaximumTipSpeedRatio(maximumTipSpeedRatio);
}

bool GeneratorWindTurbine::setMaximumPowerCoefficient(double maximumPowerCoefficient) {
  return getImpl<detail::GeneratorWindTurbine_Impl>()->setMaximumPowerCoefficient(maximumPowerCoefficient);
}

bool GeneratorWindTurbine::setAnnualLocalAverageWindSpeed(double annualLocalAverageWindSpeed) {
  return getImpl<detail::GeneratorWindTurbine_Impl>()->setAnnualLocalAverageWindSpeed(annualLocalAverageWindSpeed);
}

void GeneratorWindTurbine::resetAnnualLocalAverageWindSpeed() {
  getImpl<detail::GeneratorWindTurbine_Impl>()->resetAnnualLocalAverageWindSpeed();
}

bool GeneratorWindTurbine::setHeightforLocalAverageWindSpeed(double heightforLocalAverageWindSpeed) {
  return getImpl<detail::GeneratorWindTurbine_Impl>()->setHeightforLocalAverageWindSpeed(heightforLocalAverageWindSpeed);
}

bool GeneratorWindTurbine::setBladeChordArea(double bladeChordArea) {
  return getImpl<detail::GeneratorWindTurbine_Impl>()->setBladeChordArea(bladeChordArea);
}

bool GeneratorWindTurbine::setBladeDragCoefficient(double bladeDragCoefficient) {
  return getImpl<detail::GeneratorWindTurbine_Impl>()->setBladeDragCoefficient(bladeDragCoefficient);
}

bool GeneratorWindTurbine::setBladeLiftCoefficient(double bladeLiftCoefficient) {
  return getImpl<detail::GeneratorWindTurbine_Impl>()->setBladeLiftCoefficient(bladeLiftCoefficient);
}

bool GeneratorWindTurbine::setPowerCoefficientC1(double powerCoefficientC1) {
  return getImpl<detail::GeneratorWindTurbine_Impl>()->setPowerCoefficientC1(powerCoefficientC1);
}

bool GeneratorWindTurbine::setPowerCoefficientC2(double powerCoefficientC2) {
  return getImpl<detail::GeneratorWindTurbine_Impl>()->setPowerCoefficientC2(powerCoefficientC2);
}

bool GeneratorWindTurbine::setPowerCoefficientC3(double powerCoefficientC3) {
  return getImpl<detail::GeneratorWindTurbine_Impl>()->setPowerCoefficientC3(powerCoefficientC3);
}

bool GeneratorWindTurbine::setPowerCoefficientC4(double powerCoefficientC4) {
  return getImpl<detail::GeneratorWindTurbine_Impl>()->setPowerCoefficientC4(powerCoefficientC4);
}

bool GeneratorWindTurbine::setPowerCoefficientC5(double powerCoefficientC5) {
  return getImpl<detail::GeneratorWindTurbine_Impl>()->setPowerCoefficientC5(powerCoefficientC5);
}

bool GeneratorWindTurbine::setPowerCoefficientC6(double powerCoefficientC6) {
  return getImpl<detail::GeneratorWindTurbine_Impl>()->setPowerCoefficientC6(powerCoefficientC6);
}

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
namespace detail {

std::string GeneratorWindTurbine_Impl::rotorType() const {
  const auto value = getString(openstudio::Generator_WindTurbineFields::RotorType, true);
  OS_ASSERT(value);
  return *value;
}

std::string GeneratorWindTurbine_Impl::powerControl() const {
  const auto value = getString(openstudio::Generator_WindTurbineFields::PowerControl, true);
  OS_ASSERT(value);
  return *value;
}

double GeneratorWindTurbine_Impl::ratedRotorSpeed() const {
  const auto value = getDouble(openstudio::Generator_WindTurbineFields::RatedRotorSpeed, true);
  OS_ASSERT(value);
  return *value;
}

double GeneratorWindTurbine_Impl::rotorDiameter() const {
  const auto value = getDouble(openstudio::Generator_WindTurbineFields::RotorDiameter, true);
  OS_ASSERT(value);
  return *value;
}

double GeneratorWindTurbine_Impl::overallHeight() const {
  const auto value = getDouble(openstudio::Generator_WindTurbineFields::OverallHeight, true);
  OS_ASSERT(value);
  return *value;
}

int GeneratorWindTurbine_Impl::numberofBlades() const {
  const auto value = getInt(openstudio::Generator_WindTurbineFields::NumberofBlades, true);
  OS_ASSERT(value);
  return *value;
}

double GeneratorWindTurbine_Impl::ratedPower() const {
  const auto value = getDouble(openstudio::Generator_WindTurbineFields::RatedPower, true);
  OS_ASSERT(value);
  return *value;
}

double GeneratorWindTurbine_Impl::ratedWindSpeed() const {
  const auto value = getDouble(openstudio::Generator_WindTurbineFields::RatedWindSpeed, true);
  OS_ASSERT(value);
  return *value;
}

double GeneratorWindTurbine_Impl::cutInWindSpeed() const {
  const auto value = getDouble(openstudio::Generator_WindTurbineFields::CutInWindSpeed, true);
  OS_ASSERT(value);
  return *value;
}

double GeneratorWindTurbine_Impl::cutOutWindSpeed() const {
  const auto value = getDouble(openstudio::Generator_WindTurbineFields::CutOutWindSpeed, true);
  OS_ASSERT(value);
  return *value;
}

double GeneratorWindTurbine_Impl::fractionSystemEfficiency() const {
  const auto value = getDouble(openstudio::Generator_WindTurbineFields::FractionsystemEfficiency, true);
  OS_ASSERT(value);
  return *value;
}

double GeneratorWindTurbine_Impl::maximumTipSpeedRatio() const {
  const auto value = getDouble(openstudio::Generator_WindTurbineFields::MaximumTipSpeedRatio, true);
  OS_ASSERT(value);
  return *value;
}

double GeneratorWindTurbine_Impl::maximumPowerCoefficient() const {
  const auto value = getDouble(openstudio::Generator_WindTurbineFields::MaximumPowerCoefficient, true);
  OS_ASSERT(value);
  return *value;
}

boost::optional<double> GeneratorWindTurbine_Impl::annualLocalAverageWindSpeed() const {
  return getDouble(openstudio::Generator_WindTurbineFields::AnnualLocalAverageWindSpeed, true);
}

double GeneratorWindTurbine_Impl::heightforLocalAverageWindSpeed() const {
  const auto value = getDouble(openstudio::Generator_WindTurbineFields::HeightforLocalAverageWindSpeed, true);
  OS_ASSERT(value);
  return *value;
}

double GeneratorWindTurbine_Impl::bladeChordArea() const {
  const auto value = getDouble(openstudio::Generator_WindTurbineFields::BladeChordArea, true);
  OS_ASSERT(value);
  return *value;
}

double GeneratorWindTurbine_Impl::bladeDragCoefficient() const {
  const auto value = getDouble(openstudio::Generator_WindTurbineFields::BladeDragCoefficient, true);
  OS_ASSERT(value);
  return *value;
}

double GeneratorWindTurbine_Impl::bladeLiftCoefficient() const {
  const auto value = getDouble(openstudio::Generator_WindTurbineFields::BladeLiftCoefficient, true);
  OS_ASSERT(value);
  return *value;
}

double GeneratorWindTurbine_Impl::powerCoefficientC1() const {
  const auto value = getDouble(openstudio::Generator_WindTurbineFields::PowerCoefficientC1, true);
  OS_ASSERT(value);
  return *value;
}

double GeneratorWindTurbine_Impl::powerCoefficientC2() const {
  const auto value = getDouble(openstudio::Generator_WindTurbineFields::PowerCoefficientC2, true);
  OS_ASSERT(value);
  return *value;
}

double GeneratorWindTurbine_Impl::powerCoefficientC3() const {
  const auto value = getDouble(openstudio::Generator_WindTurbineFields::PowerCoefficientC3, true);
  OS_ASSERT(value);
  return *value;
}

double GeneratorWindTurbine_Impl::powerCoefficientC4() const {
  const auto value = getDouble(openstudio::Generator_WindTurbineFields::PowerCoefficientC4, true);
  OS_ASSERT(value);
  return *value;
}

double GeneratorWindTurbine_Impl::powerCoefficientC5() const {
  const auto value = getDouble(openstudio::Generator_WindTurbineFields::PowerCoefficientC5, true);
  OS_ASSERT(value);
  return *value;
}

double GeneratorWindTurbine_Impl::powerCoefficientC6() const {
  const auto value = getDouble(openstudio::Generator_WindTurbineFields::PowerCoefficientC6, true);
  OS_ASSERT(value);
  return *value;
}

bool GeneratorWindTurbine_Impl::setRotorType(const std::string& rotorType) {
  return setString(openstudio::Generator_WindTurbineFields::RotorType, rotorType);
}

bool GeneratorWindTurbine_Impl::setPowerControl(const std::string& powerControl) {
  return setString(openstudio::Generator_WindTurbineFields::PowerControl, powerControl);
}

bool GeneratorWindTurbine_Impl::setRatedRotorSpeed(double ratedRotorSpeed) {
  return setDouble(openstudio::Generator_WindTurbineFields::RatedRotorSpeed, ratedRotorSpeed);
}

bool GeneratorWindTurbine_Impl::setRotorDiameter(double rotorDiameter) {
  return setDouble(openstudio::Generator_WindTurbineFields::RotorDiameter, rotorDiameter);
}

bool GeneratorWindTurbine_Impl::setOverallHeight(double overallHeight) {
  return setDouble(openstudio::Generator_WindTurbineFields::OverallHeight, overallHeight);
}

bool GeneratorWindTurbine_Impl::setNumberofBlades(int numberofBlades) {
  return setInt(openstudio::Generator_WindTurbineFields::NumberofBlades, numberofBlades);
}

bool GeneratorWindTurbine_Impl::setRatedPower(double ratedPower) {
  return setDouble(openstudio::Generator_WindTurbineFields::RatedPower, ratedPower);
}

bool GeneratorWindTurbine_Impl::setRatedWindSpeed(double ratedWindSpeed) {
  return setDouble(openstudio::Generator_WindTurbineFields::RatedWindSpeed, ratedWindSpeed);
}

bool GeneratorWindTurbine_Impl::setCutInWindSpeed(double cutInWindSpeed) {
  return setDouble(openstudio::Generator_WindTurbineFields::CutInWindSpeed, cutInWindSpeed);
}

bool GeneratorWindTurbine_Impl::setCutOutWindSpeed(double cutOutWindSpeed) {
  return setDouble(openstudio::Generator_WindTurbineFields::CutOutWindSpeed, cutOutWindSpeed);
}

bool GeneratorWindTurbine_Impl::setFractionSystemEfficiency(double fractionSystemEfficiency) {
  return setDouble(openstudio::Generator_WindTurbineFields::FractionsystemEfficiency, fractionSystemEfficiency);
}

bool GeneratorWindTurbine_Impl::setMaximumTipSpeedRatio(double maximumTipSpeedRatio) {
  return setDouble(openstudio::Generator_WindTurbineFields::MaximumTipSpeedRatio, maximumTipSpeedRatio);
}

bool GeneratorWindTurbine_Impl::setMaximumPowerCoefficient(double maximumPowerCoefficient) {
  return setDouble(openstudio::Generator_WindTurbineFields::MaximumPowerCoefficient, maximumPowerCoefficient);
}

bool GeneratorWindTurbine_Impl::setAnnualLocalAverageWindSpeed(double annualLocalAverageWindSpeed) {
  return setDouble(openstudio::Generator_WindTurbineFields::AnnualLocalAverageWindSpeed, annualLocalAverageWindSpeed);
}

void GeneratorWindTurbine_Impl::resetAnnualLocalAverageWindSpeed() {
  OS_ASSERT(setString(openstudio::Generator_WindTurbineFields::AnnualLocalAverageWindSpeed, ""));
}

bool GeneratorWindTurbine_Impl::setHeightforLocalAverageWindSpeed(double heightforLocalAverageWindSpeed) {
  return setDouble(openstudio::Generator_WindTurbineFields::HeightforLocalAverageWindSpeed, heightforLocalAverageWindSpeed);
}

bool GeneratorWindTurbine_Impl::setBladeChordArea(double bladeChordArea) {
  return setDouble(openstudio::Generator_WindTurbineFields::BladeChordArea, bladeChordArea);
}

bool GeneratorWindTurbine_Impl::setBladeDragCoefficient(double bladeDragCoefficient) {
  return setDouble(openstudio::Generator_WindTurbineFields::BladeDragCoefficient, bladeDragCoefficient);
}

bool GeneratorWindTurbine_Impl::setBladeLiftCoefficient(double bladeLiftCoefficient) {
  return setDouble(openstudio::Generator_WindTurbineFields::BladeLiftCoefficient, bladeLiftCoefficient);
}

bool GeneratorWindTurbine_Impl::setPowerCoefficientC1(double powerCoefficientC1) {
  return setDouble(openstudio::Generator_WindTurbineFields::PowerCoefficientC1, powerCoefficientC1);
}

bool GeneratorWindTurbine_Impl::setPowerCoefficientC2(double powerCoefficientC2) {
  return setDouble(openstudio::Generator_WindTurbineFields::PowerCoefficientC2, powerCoefficientC2);
}

bool GeneratorWindTurbine_Impl::setPowerCoefficientC3(double powerCoefficientC3) {
  return setDouble(openstudio::Generator_WindTurbineFields::PowerCoefficientC3, powerCoefficientC3);
}

bool GeneratorWindTurbine_Impl::setPowerCoefficientC4(double powerCoefficientC4) {
  return setDouble(openstudio::Generator_WindTurbineFields::PowerCoefficientC4, powerCoefficientC4);
}

bool GeneratorWindTurbine_Impl::setPowerCoefficientC5(double powerCoefficientC5) {
  return setDouble(openstudio::Generator_WindTurbineFields::PowerCoefficientC5, powerCoefficientC5);
}

bool GeneratorWindTurbine_Impl::setPowerCoefficientC6(double powerCoefficientC6) {
  return setDouble(openstudio::Generator_WindTurbineFields::PowerCoefficientC6, powerCoefficientC6);
}

std::vector<std::string> GeneratorWindTurbine_Impl::rotorTypeValues() const {
  return openstudio::epmodel::GeneratorWindTurbine::rotorTypeValues();
}

std::vector<std::string> GeneratorWindTurbine_Impl::powerControlValues() const {
  return openstudio::epmodel::GeneratorWindTurbine::powerControlValues();
}

}  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
