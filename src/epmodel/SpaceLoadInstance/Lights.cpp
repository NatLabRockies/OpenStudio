/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "SpaceLoadInstance/Lights.hpp"
#include "SpaceLoadInstance/Lights_Impl.hpp"

#include "Model.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/core/StringHelpers.hpp>
#include <utilities/idd/IddEnums.hxx>
#include <utilities/idd/IddFactory.hxx>
#include <utilities/idd/IddObject.hpp>
#include <utilities/idd/Lights_FieldEnums.hxx>

namespace openstudio {
namespace epmodel {

  Lights::Lights(const Model& model) : ModelObject(Lights::iddObjectType(), model) {}

  Lights::Lights(std::shared_ptr<detail::Lights_Impl> impl) : ModelObject(std::move(impl)) {}

  IddObjectType Lights::iddObjectType() {
    return IddObjectType::Lights;
  }

  std::vector<std::string> Lights::designLevelCalculationMethodValues() {
    return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(), openstudio::LightsFields::DesignLevelCalculationMethod);
  }

  std::string Lights::designLevelCalculationMethod() const {
    return getImpl<detail::Lights_Impl>()->designLevelCalculationMethod();
  }

  bool Lights::isDesignLevelCalculationMethodDefaulted() const {
    return getImpl<detail::Lights_Impl>()->isDesignLevelCalculationMethodDefaulted();
  }

  bool Lights::setDesignLevelCalculationMethod(const std::string& designLevelCalculationMethod) {
    return getImpl<detail::Lights_Impl>()->setDesignLevelCalculationMethod(designLevelCalculationMethod);
  }

  void Lights::resetDesignLevelCalculationMethod() {
    getImpl<detail::Lights_Impl>()->resetDesignLevelCalculationMethod();
  }

  boost::optional<double> Lights::lightingLevel() const {
    return getImpl<detail::Lights_Impl>()->lightingLevel();
  }

  bool Lights::setLightingLevel(double lightingLevel) {
    return getImpl<detail::Lights_Impl>()->setLightingLevel(lightingLevel);
  }

  void Lights::resetLightingLevel() {
    getImpl<detail::Lights_Impl>()->resetLightingLevel();
  }

  boost::optional<double> Lights::powerPerFloorArea() const {
    return getImpl<detail::Lights_Impl>()->powerPerFloorArea();
  }

  bool Lights::setPowerPerFloorArea(double powerPerFloorArea) {
    return getImpl<detail::Lights_Impl>()->setPowerPerFloorArea(powerPerFloorArea);
  }

  void Lights::resetPowerPerFloorArea() {
    getImpl<detail::Lights_Impl>()->resetPowerPerFloorArea();
  }

  boost::optional<double> Lights::powerPerPerson() const {
    return getImpl<detail::Lights_Impl>()->powerPerPerson();
  }

  bool Lights::setPowerPerPerson(double powerPerPerson) {
    return getImpl<detail::Lights_Impl>()->setPowerPerPerson(powerPerPerson);
  }

  void Lights::resetPowerPerPerson() {
    getImpl<detail::Lights_Impl>()->resetPowerPerPerson();
  }

  double Lights::returnAirFraction() const {
    return getImpl<detail::Lights_Impl>()->returnAirFraction();
  }

  bool Lights::isReturnAirFractionDefaulted() const {
    return getImpl<detail::Lights_Impl>()->isReturnAirFractionDefaulted();
  }

  bool Lights::setReturnAirFraction(double returnAirFraction) {
    return getImpl<detail::Lights_Impl>()->setReturnAirFraction(returnAirFraction);
  }

  void Lights::resetReturnAirFraction() {
    getImpl<detail::Lights_Impl>()->resetReturnAirFraction();
  }

  double Lights::fractionRadiant() const {
    return getImpl<detail::Lights_Impl>()->fractionRadiant();
  }

  bool Lights::isFractionRadiantDefaulted() const {
    return getImpl<detail::Lights_Impl>()->isFractionRadiantDefaulted();
  }

  bool Lights::setFractionRadiant(double fractionRadiant) {
    return getImpl<detail::Lights_Impl>()->setFractionRadiant(fractionRadiant);
  }

  void Lights::resetFractionRadiant() {
    getImpl<detail::Lights_Impl>()->resetFractionRadiant();
  }

  double Lights::fractionVisible() const {
    return getImpl<detail::Lights_Impl>()->fractionVisible();
  }

  bool Lights::isFractionVisibleDefaulted() const {
    return getImpl<detail::Lights_Impl>()->isFractionVisibleDefaulted();
  }

  bool Lights::setFractionVisible(double fractionVisible) {
    return getImpl<detail::Lights_Impl>()->setFractionVisible(fractionVisible);
  }

  void Lights::resetFractionVisible() {
    getImpl<detail::Lights_Impl>()->resetFractionVisible();
  }

  double Lights::fractionReplaceable() const {
    return getImpl<detail::Lights_Impl>()->fractionReplaceable();
  }

  bool Lights::isFractionReplaceableDefaulted() const {
    return getImpl<detail::Lights_Impl>()->isFractionReplaceableDefaulted();
  }

  bool Lights::setFractionReplaceable(double fractionReplaceable) {
    return getImpl<detail::Lights_Impl>()->setFractionReplaceable(fractionReplaceable);
  }

  void Lights::resetFractionReplaceable() {
    getImpl<detail::Lights_Impl>()->resetFractionReplaceable();
  }

  std::string Lights::endUseSubcategory() const {
    return getImpl<detail::Lights_Impl>()->endUseSubcategory();
  }

  bool Lights::isEndUseSubcategoryDefaulted() const {
    return getImpl<detail::Lights_Impl>()->isEndUseSubcategoryDefaulted();
  }

  bool Lights::setEndUseSubcategory(const std::string& endUseSubcategory) {
    return getImpl<detail::Lights_Impl>()->setEndUseSubcategory(endUseSubcategory);
  }

  void Lights::resetEndUseSubcategory() {
    getImpl<detail::Lights_Impl>()->resetEndUseSubcategory();
  }

  bool Lights::returnAirFractionCalculatedfromPlenumTemperature() const {
    return getImpl<detail::Lights_Impl>()->returnAirFractionCalculatedfromPlenumTemperature();
  }

  bool Lights::isReturnAirFractionCalculatedfromPlenumTemperatureDefaulted() const {
    return getImpl<detail::Lights_Impl>()->isReturnAirFractionCalculatedfromPlenumTemperatureDefaulted();
  }

  bool Lights::setReturnAirFractionCalculatedfromPlenumTemperature(bool returnAirFractionCalculatedfromPlenumTemperature) {
    return getImpl<detail::Lights_Impl>()->setReturnAirFractionCalculatedfromPlenumTemperature(returnAirFractionCalculatedfromPlenumTemperature);
  }

  void Lights::resetReturnAirFractionCalculatedfromPlenumTemperature() {
    getImpl<detail::Lights_Impl>()->resetReturnAirFractionCalculatedfromPlenumTemperature();
  }

  double Lights::returnAirFractionFunctionofPlenumTemperatureCoefficient1() const {
    return getImpl<detail::Lights_Impl>()->returnAirFractionFunctionofPlenumTemperatureCoefficient1();
  }

  bool Lights::isReturnAirFractionFunctionofPlenumTemperatureCoefficient1Defaulted() const {
    return getImpl<detail::Lights_Impl>()->isReturnAirFractionFunctionofPlenumTemperatureCoefficient1Defaulted();
  }

  bool Lights::setReturnAirFractionFunctionofPlenumTemperatureCoefficient1(double returnAirFractionFunctionofPlenumTemperatureCoefficient1) {
    return getImpl<detail::Lights_Impl>()->setReturnAirFractionFunctionofPlenumTemperatureCoefficient1(
      returnAirFractionFunctionofPlenumTemperatureCoefficient1);
  }

  void Lights::resetReturnAirFractionFunctionofPlenumTemperatureCoefficient1() {
    getImpl<detail::Lights_Impl>()->resetReturnAirFractionFunctionofPlenumTemperatureCoefficient1();
  }

  double Lights::returnAirFractionFunctionofPlenumTemperatureCoefficient2() const {
    return getImpl<detail::Lights_Impl>()->returnAirFractionFunctionofPlenumTemperatureCoefficient2();
  }

  bool Lights::isReturnAirFractionFunctionofPlenumTemperatureCoefficient2Defaulted() const {
    return getImpl<detail::Lights_Impl>()->isReturnAirFractionFunctionofPlenumTemperatureCoefficient2Defaulted();
  }

  bool Lights::setReturnAirFractionFunctionofPlenumTemperatureCoefficient2(double returnAirFractionFunctionofPlenumTemperatureCoefficient2) {
    return getImpl<detail::Lights_Impl>()->setReturnAirFractionFunctionofPlenumTemperatureCoefficient2(
      returnAirFractionFunctionofPlenumTemperatureCoefficient2);
  }

  void Lights::resetReturnAirFractionFunctionofPlenumTemperatureCoefficient2() {
    getImpl<detail::Lights_Impl>()->resetReturnAirFractionFunctionofPlenumTemperatureCoefficient2();
  }

  bool Lights::setMultiplier(double multiplier) {
    return getImpl<detail::Lights_Impl>()->setMultiplier(multiplier);
  }

  void Lights::resetMultiplier() {
    getImpl<detail::Lights_Impl>()->resetMultiplier();
  }

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
  namespace detail {

    std::string Lights_Impl::designLevelCalculationMethod() const {
      const auto value = getString(openstudio::LightsFields::DesignLevelCalculationMethod, true);
      OS_ASSERT(value);
      return *value;
    }

    bool Lights_Impl::isDesignLevelCalculationMethodDefaulted() const {
      return isEmpty(openstudio::LightsFields::DesignLevelCalculationMethod);
    }

    bool Lights_Impl::setDesignLevelCalculationMethod(const std::string& designLevelCalculationMethod) {
      return setString(openstudio::LightsFields::DesignLevelCalculationMethod, designLevelCalculationMethod);
    }

    void Lights_Impl::resetDesignLevelCalculationMethod() {
      OS_ASSERT(setString(openstudio::LightsFields::DesignLevelCalculationMethod, ""));
    }

    boost::optional<double> Lights_Impl::lightingLevel() const {
      return getDouble(openstudio::LightsFields::LightingLevel, true);
    }

    bool Lights_Impl::setLightingLevel(double lightingLevel) {
      return setDouble(openstudio::LightsFields::LightingLevel, lightingLevel);
    }

    void Lights_Impl::resetLightingLevel() {
      OS_ASSERT(setString(openstudio::LightsFields::LightingLevel, ""));
    }

    boost::optional<double> Lights_Impl::powerPerFloorArea() const {
      return getDouble(openstudio::LightsFields::WattsperFloorArea, true);
    }

    bool Lights_Impl::setPowerPerFloorArea(double powerPerFloorArea) {
      return setDouble(openstudio::LightsFields::WattsperFloorArea, powerPerFloorArea);
    }

    void Lights_Impl::resetPowerPerFloorArea() {
      OS_ASSERT(setString(openstudio::LightsFields::WattsperFloorArea, ""));
    }

    boost::optional<double> Lights_Impl::powerPerPerson() const {
      return getDouble(openstudio::LightsFields::WattsperPerson, true);
    }

    bool Lights_Impl::setPowerPerPerson(double powerPerPerson) {
      return setDouble(openstudio::LightsFields::WattsperPerson, powerPerPerson);
    }

    void Lights_Impl::resetPowerPerPerson() {
      OS_ASSERT(setString(openstudio::LightsFields::WattsperPerson, ""));
    }

    double Lights_Impl::returnAirFraction() const {
      const auto value = getDouble(openstudio::LightsFields::ReturnAirFraction, true);
      OS_ASSERT(value);
      return *value;
    }

    bool Lights_Impl::isReturnAirFractionDefaulted() const {
      return isEmpty(openstudio::LightsFields::ReturnAirFraction);
    }

    bool Lights_Impl::setReturnAirFraction(double returnAirFraction) {
      return setDouble(openstudio::LightsFields::ReturnAirFraction, returnAirFraction);
    }

    void Lights_Impl::resetReturnAirFraction() {
      OS_ASSERT(setString(openstudio::LightsFields::ReturnAirFraction, ""));
    }

    double Lights_Impl::fractionRadiant() const {
      const auto value = getDouble(openstudio::LightsFields::FractionRadiant, true);
      OS_ASSERT(value);
      return *value;
    }

    bool Lights_Impl::isFractionRadiantDefaulted() const {
      return isEmpty(openstudio::LightsFields::FractionRadiant);
    }

    bool Lights_Impl::setFractionRadiant(double fractionRadiant) {
      return setDouble(openstudio::LightsFields::FractionRadiant, fractionRadiant);
    }

    void Lights_Impl::resetFractionRadiant() {
      OS_ASSERT(setString(openstudio::LightsFields::FractionRadiant, ""));
    }

    double Lights_Impl::fractionVisible() const {
      const auto value = getDouble(openstudio::LightsFields::FractionVisible, true);
      OS_ASSERT(value);
      return *value;
    }

    bool Lights_Impl::isFractionVisibleDefaulted() const {
      return isEmpty(openstudio::LightsFields::FractionVisible);
    }

    bool Lights_Impl::setFractionVisible(double fractionVisible) {
      return setDouble(openstudio::LightsFields::FractionVisible, fractionVisible);
    }

    void Lights_Impl::resetFractionVisible() {
      OS_ASSERT(setString(openstudio::LightsFields::FractionVisible, ""));
    }

    double Lights_Impl::fractionReplaceable() const {
      const auto value = getDouble(openstudio::LightsFields::FractionReplaceable, true);
      OS_ASSERT(value);
      return *value;
    }

    bool Lights_Impl::isFractionReplaceableDefaulted() const {
      return isEmpty(openstudio::LightsFields::FractionReplaceable);
    }

    bool Lights_Impl::setFractionReplaceable(double fractionReplaceable) {
      return setDouble(openstudio::LightsFields::FractionReplaceable, fractionReplaceable);
    }

    void Lights_Impl::resetFractionReplaceable() {
      OS_ASSERT(setString(openstudio::LightsFields::FractionReplaceable, ""));
    }

    std::string Lights_Impl::endUseSubcategory() const {
      const auto value = getString(openstudio::LightsFields::EndUseSubcategory, true);
      OS_ASSERT(value);
      return *value;
    }

    bool Lights_Impl::isEndUseSubcategoryDefaulted() const {
      return isEmpty(openstudio::LightsFields::EndUseSubcategory);
    }

    bool Lights_Impl::setEndUseSubcategory(const std::string& endUseSubcategory) {
      const bool result = setString(openstudio::LightsFields::EndUseSubcategory, endUseSubcategory);
      OS_ASSERT(result);
      return result;
    }

    void Lights_Impl::resetEndUseSubcategory() {
      OS_ASSERT(setString(openstudio::LightsFields::EndUseSubcategory, ""));
    }

    bool Lights_Impl::returnAirFractionCalculatedfromPlenumTemperature() const {
      const auto value = getString(openstudio::LightsFields::ReturnAirFractionCalculatedfromPlenumTemperature, true);
      OS_ASSERT(value);
      return openstudio::istringEqual(*value, "Yes");
    }

    bool Lights_Impl::isReturnAirFractionCalculatedfromPlenumTemperatureDefaulted() const {
      return isEmpty(openstudio::LightsFields::ReturnAirFractionCalculatedfromPlenumTemperature);
    }

    bool Lights_Impl::setReturnAirFractionCalculatedfromPlenumTemperature(bool returnAirFractionCalculatedfromPlenumTemperature) {
      const bool result = setString(openstudio::LightsFields::ReturnAirFractionCalculatedfromPlenumTemperature,
                                    returnAirFractionCalculatedfromPlenumTemperature ? "Yes" : "No");
      OS_ASSERT(result);
      return result;
    }

    void Lights_Impl::resetReturnAirFractionCalculatedfromPlenumTemperature() {
      OS_ASSERT(setString(openstudio::LightsFields::ReturnAirFractionCalculatedfromPlenumTemperature, ""));
    }

    double Lights_Impl::returnAirFractionFunctionofPlenumTemperatureCoefficient1() const {
      const auto value = getDouble(openstudio::LightsFields::ReturnAirFractionFunctionofPlenumTemperatureCoefficient1, true);
      OS_ASSERT(value);
      return *value;
    }

    bool Lights_Impl::isReturnAirFractionFunctionofPlenumTemperatureCoefficient1Defaulted() const {
      return isEmpty(openstudio::LightsFields::ReturnAirFractionFunctionofPlenumTemperatureCoefficient1);
    }

    bool Lights_Impl::setReturnAirFractionFunctionofPlenumTemperatureCoefficient1(double returnAirFractionFunctionofPlenumTemperatureCoefficient1) {
      return setDouble(openstudio::LightsFields::ReturnAirFractionFunctionofPlenumTemperatureCoefficient1,
                       returnAirFractionFunctionofPlenumTemperatureCoefficient1);
    }

    void Lights_Impl::resetReturnAirFractionFunctionofPlenumTemperatureCoefficient1() {
      OS_ASSERT(setString(openstudio::LightsFields::ReturnAirFractionFunctionofPlenumTemperatureCoefficient1, ""));
    }

    double Lights_Impl::returnAirFractionFunctionofPlenumTemperatureCoefficient2() const {
      const auto value = getDouble(openstudio::LightsFields::ReturnAirFractionFunctionofPlenumTemperatureCoefficient2, true);
      OS_ASSERT(value);
      return *value;
    }

    bool Lights_Impl::isReturnAirFractionFunctionofPlenumTemperatureCoefficient2Defaulted() const {
      return isEmpty(openstudio::LightsFields::ReturnAirFractionFunctionofPlenumTemperatureCoefficient2);
    }

    bool Lights_Impl::setReturnAirFractionFunctionofPlenumTemperatureCoefficient2(double returnAirFractionFunctionofPlenumTemperatureCoefficient2) {
      return setDouble(openstudio::LightsFields::ReturnAirFractionFunctionofPlenumTemperatureCoefficient2,
                       returnAirFractionFunctionofPlenumTemperatureCoefficient2);
    }

    void Lights_Impl::resetReturnAirFractionFunctionofPlenumTemperatureCoefficient2() {
      OS_ASSERT(setString(openstudio::LightsFields::ReturnAirFractionFunctionofPlenumTemperatureCoefficient2, ""));
    }

    bool Lights_Impl::setMultiplier(double multiplier) {
      // EnergyPlus Lights has no dedicated multiplier field. Preserve model API by
      // scaling whichever design-level scalar field(s) are currently populated.
      bool applied = false;
      bool result = true;

      if (auto value = getDouble(openstudio::LightsFields::LightingLevel, true)) {
        const bool fieldResult = setDouble(openstudio::LightsFields::LightingLevel, (*value) * multiplier);
        OS_ASSERT(fieldResult);
        result = result && fieldResult;
        applied = true;
      }
      if (auto value = getDouble(openstudio::LightsFields::WattsperFloorArea, true)) {
        const bool fieldResult = setDouble(openstudio::LightsFields::WattsperFloorArea, (*value) * multiplier);
        OS_ASSERT(fieldResult);
        result = result && fieldResult;
        applied = true;
      }
      if (auto value = getDouble(openstudio::LightsFields::WattsperPerson, true)) {
        const bool fieldResult = setDouble(openstudio::LightsFields::WattsperPerson, (*value) * multiplier);
        OS_ASSERT(fieldResult);
        result = result && fieldResult;
        applied = true;
      }

      return applied && result;
    }

    void Lights_Impl::resetMultiplier() {
      // No dedicated translated multiplier field exists on EnergyPlus Lights.
    }

    std::vector<std::string> Lights_Impl::designLevelCalculationMethodValues() const {
      return openstudio::epmodel::Lights::designLevelCalculationMethodValues();
    }

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
