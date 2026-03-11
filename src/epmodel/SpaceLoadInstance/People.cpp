/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "SpaceLoadInstance/People.hpp"
#include "SpaceLoadInstance/People_Impl.hpp"

#include "Model.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/idd/IddEnums.hxx>
#include <utilities/idd/IddFactory.hxx>
#include <utilities/idd/IddObject.hpp>
#include <utilities/idd/People_FieldEnums.hxx>

namespace openstudio {
namespace epmodel {

People::People(const Model& model) : ModelObject(People::iddObjectType(), model) {}

People::People(std::shared_ptr<detail::People_Impl> impl) : ModelObject(std::move(impl)) {}

IddObjectType People::iddObjectType() {
  return IddObjectType::People;
}

std::vector<std::string> People::clothingInsulationCalculationMethodValues() {
  return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(),
                        openstudio::PeopleFields::ClothingInsulationCalculationMethod);
}

std::string People::clothingInsulationCalculationMethod() const {
  return getImpl<detail::People_Impl>()->clothingInsulationCalculationMethod();
}

bool People::setClothingInsulationCalculationMethod(const std::string& clothingInsulationCalculationMethod) {
  return getImpl<detail::People_Impl>()->setClothingInsulationCalculationMethod(clothingInsulationCalculationMethod);
}

double People::coldStressTemperatureThreshold() const {
  return getImpl<detail::People_Impl>()->coldStressTemperatureThreshold();
}

bool People::isColdStressTemperatureThresholdDefaulted() const {
  return getImpl<detail::People_Impl>()->isColdStressTemperatureThresholdDefaulted();
}

bool People::setColdStressTemperatureThreshold(double coldStressTemperatureThreshold) {
  return getImpl<detail::People_Impl>()->setColdStressTemperatureThreshold(coldStressTemperatureThreshold);
}

void People::resetColdStressTemperatureThreshold() {
  getImpl<detail::People_Impl>()->resetColdStressTemperatureThreshold();
}

double People::heatStressTemperatureThreshold() const {
  return getImpl<detail::People_Impl>()->heatStressTemperatureThreshold();
}

bool People::isHeatStressTemperatureThresholdDefaulted() const {
  return getImpl<detail::People_Impl>()->isHeatStressTemperatureThresholdDefaulted();
}

bool People::setHeatStressTemperatureThreshold(double heatStressTemperatureThreshold) {
  return getImpl<detail::People_Impl>()->setHeatStressTemperatureThreshold(heatStressTemperatureThreshold);
}

void People::resetHeatStressTemperatureThreshold() {
  getImpl<detail::People_Impl>()->resetHeatStressTemperatureThreshold();
}

bool People::setMultiplier(double multiplier) {
  return getImpl<detail::People_Impl>()->setMultiplier(multiplier);
}

void People::resetMultiplier() {
  getImpl<detail::People_Impl>()->resetMultiplier();
}

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
namespace detail {

std::string People_Impl::clothingInsulationCalculationMethod() const {
  const auto value = getString(openstudio::PeopleFields::ClothingInsulationCalculationMethod, true);
  OS_ASSERT(value);
  return *value;
}

bool People_Impl::setClothingInsulationCalculationMethod(const std::string& clothingInsulationCalculationMethod) {
  return setString(openstudio::PeopleFields::ClothingInsulationCalculationMethod, clothingInsulationCalculationMethod);
}

double People_Impl::coldStressTemperatureThreshold() const {
  const auto value = getDouble(openstudio::PeopleFields::ColdStressTemperatureThreshold, true);
  OS_ASSERT(value);
  return *value;
}

bool People_Impl::isColdStressTemperatureThresholdDefaulted() const {
  return isEmpty(openstudio::PeopleFields::ColdStressTemperatureThreshold);
}

bool People_Impl::setColdStressTemperatureThreshold(double coldStressTemperatureThreshold) {
  return setDouble(openstudio::PeopleFields::ColdStressTemperatureThreshold, coldStressTemperatureThreshold);
}

void People_Impl::resetColdStressTemperatureThreshold() {
  OS_ASSERT(setString(openstudio::PeopleFields::ColdStressTemperatureThreshold, ""));
}

double People_Impl::heatStressTemperatureThreshold() const {
  const auto value = getDouble(openstudio::PeopleFields::HeatStressTemperatureThreshold, true);
  OS_ASSERT(value);
  return *value;
}

bool People_Impl::isHeatStressTemperatureThresholdDefaulted() const {
  return isEmpty(openstudio::PeopleFields::HeatStressTemperatureThreshold);
}

bool People_Impl::setHeatStressTemperatureThreshold(double heatStressTemperatureThreshold) {
  return setDouble(openstudio::PeopleFields::HeatStressTemperatureThreshold, heatStressTemperatureThreshold);
}

void People_Impl::resetHeatStressTemperatureThreshold() {
  OS_ASSERT(setString(openstudio::PeopleFields::HeatStressTemperatureThreshold, ""));
}

bool People_Impl::setMultiplier(double multiplier) {
  // EnergyPlus People has no dedicated translated multiplier field. Preserve model API by
  // scaling whichever person-density scalar field(s) are currently populated.
  bool applied = false;
  bool result = true;

  if (auto value = getDouble(openstudio::PeopleFields::NumberofPeople, true)) {
    const bool fieldResult = setDouble(openstudio::PeopleFields::NumberofPeople, (*value) * multiplier);
    OS_ASSERT(fieldResult);
    result = result && fieldResult;
    applied = true;
  }
  if (auto value = getDouble(openstudio::PeopleFields::PeopleperFloorArea, true)) {
    const bool fieldResult = setDouble(openstudio::PeopleFields::PeopleperFloorArea, (*value) * multiplier);
    OS_ASSERT(fieldResult);
    result = result && fieldResult;
    applied = true;
  }
  if (auto value = getDouble(openstudio::PeopleFields::FloorAreaperPerson, true)) {
    const bool fieldResult = setDouble(openstudio::PeopleFields::FloorAreaperPerson, (*value) * multiplier);
    OS_ASSERT(fieldResult);
    result = result && fieldResult;
    applied = true;
  }

  return applied && result;
}

void People_Impl::resetMultiplier() {
  // No dedicated translated multiplier field exists on EnergyPlus People.
}

std::vector<std::string> People_Impl::clothingInsulationCalculationMethodValues() const {
  return openstudio::epmodel::People::clothingInsulationCalculationMethodValues();
}

}  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
