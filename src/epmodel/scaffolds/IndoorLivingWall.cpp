/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "IndoorLivingWall.hpp"
#include "IndoorLivingWall_Impl.hpp"

#include "Model.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/idd/IndoorLivingWall_FieldEnums.hxx>
#include <utilities/idd/IddEnums.hxx>
#include <utilities/idd/IddFactory.hxx>
#include <utilities/idd/IddObject.hpp>

namespace openstudio {
namespace epmodel {

  IndoorLivingWall::IndoorLivingWall(const Model& model) : ModelObject(IndoorLivingWall::iddObjectType(), model) {}

  IndoorLivingWall::IndoorLivingWall(std::shared_ptr<detail::IndoorLivingWall_Impl> impl) : ModelObject(std::move(impl)) {}

  IddObjectType IndoorLivingWall::iddObjectType() {
    return IddObjectType::IndoorLivingWall;
  }

  std::vector<std::string> IndoorLivingWall::evapotranspirationCalculationMethodValues() {
    return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(),
                          openstudio::IndoorLivingWallFields::EvapotranspirationCalculationMethod);
  }

  std::vector<std::string> IndoorLivingWall::lightingMethodValues() {
    return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(), openstudio::IndoorLivingWallFields::LightingMethod);
  }

  std::string IndoorLivingWall::evapotranspirationCalculationMethod() const {
    return getImpl<detail::IndoorLivingWall_Impl>()->evapotranspirationCalculationMethod();
  }

  bool IndoorLivingWall::setEvapotranspirationCalculationMethod(const std::string& evapotranspirationCalculationMethod) {
    return getImpl<detail::IndoorLivingWall_Impl>()->setEvapotranspirationCalculationMethod(evapotranspirationCalculationMethod);
  }

  bool IndoorLivingWall::isEvapotranspirationCalculationMethodDefaulted() const {
    return getImpl<detail::IndoorLivingWall_Impl>()->isEvapotranspirationCalculationMethodDefaulted();
  }

  void IndoorLivingWall::resetEvapotranspirationCalculationMethod() {
    getImpl<detail::IndoorLivingWall_Impl>()->resetEvapotranspirationCalculationMethod();
  }

  boost::optional<std::string> IndoorLivingWall::lightingMethod() const {
    return getImpl<detail::IndoorLivingWall_Impl>()->lightingMethod();
  }

  bool IndoorLivingWall::setLightingMethod(const std::string& lightingMethod) {
    return getImpl<detail::IndoorLivingWall_Impl>()->setLightingMethod(lightingMethod);
  }

  void IndoorLivingWall::resetLightingMethod() {
    getImpl<detail::IndoorLivingWall_Impl>()->resetLightingMethod();
  }

  boost::optional<std::string> IndoorLivingWall::daylightingControlName() const {
    return getImpl<detail::IndoorLivingWall_Impl>()->daylightingControlName();
  }

  bool IndoorLivingWall::setDaylightingControlName(const std::string& daylightingControlName) {
    return getImpl<detail::IndoorLivingWall_Impl>()->setDaylightingControlName(daylightingControlName);
  }

  void IndoorLivingWall::resetDaylightingControlName() {
    getImpl<detail::IndoorLivingWall_Impl>()->resetDaylightingControlName();
  }

  boost::optional<double> IndoorLivingWall::totalLeafArea() const {
    return getImpl<detail::IndoorLivingWall_Impl>()->totalLeafArea();
  }

  bool IndoorLivingWall::setTotalLeafArea(double totalLeafArea) {
    return getImpl<detail::IndoorLivingWall_Impl>()->setTotalLeafArea(totalLeafArea);
  }

  void IndoorLivingWall::resetTotalLeafArea() {
    getImpl<detail::IndoorLivingWall_Impl>()->resetTotalLeafArea();
  }

  boost::optional<double> IndoorLivingWall::lEDNominalIntensity() const {
    return getImpl<detail::IndoorLivingWall_Impl>()->lEDNominalIntensity();
  }

  bool IndoorLivingWall::setLEDNominalIntensity(double lEDNominalIntensity) {
    return getImpl<detail::IndoorLivingWall_Impl>()->setLEDNominalIntensity(lEDNominalIntensity);
  }

  void IndoorLivingWall::resetLEDNominalIntensity() {
    getImpl<detail::IndoorLivingWall_Impl>()->resetLEDNominalIntensity();
  }

  boost::optional<double> IndoorLivingWall::lEDNominalPower() const {
    return getImpl<detail::IndoorLivingWall_Impl>()->lEDNominalPower();
  }

  bool IndoorLivingWall::setLEDNominalPower(double lEDNominalPower) {
    return getImpl<detail::IndoorLivingWall_Impl>()->setLEDNominalPower(lEDNominalPower);
  }

  void IndoorLivingWall::resetLEDNominalPower() {
    getImpl<detail::IndoorLivingWall_Impl>()->resetLEDNominalPower();
  }

  double IndoorLivingWall::radiantFractionofLEDLights() const {
    return getImpl<detail::IndoorLivingWall_Impl>()->radiantFractionofLEDLights();
  }

  bool IndoorLivingWall::isRadiantFractionofLEDLightsDefaulted() const {
    return getImpl<detail::IndoorLivingWall_Impl>()->isRadiantFractionofLEDLightsDefaulted();
  }

  bool IndoorLivingWall::setRadiantFractionofLEDLights(double radiantFractionofLEDLights) {
    return getImpl<detail::IndoorLivingWall_Impl>()->setRadiantFractionofLEDLights(radiantFractionofLEDLights);
  }

  void IndoorLivingWall::resetRadiantFractionofLEDLights() {
    getImpl<detail::IndoorLivingWall_Impl>()->resetRadiantFractionofLEDLights();
  }

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
  namespace detail {

    std::string IndoorLivingWall_Impl::evapotranspirationCalculationMethod() const {
      const auto value = getString(openstudio::IndoorLivingWallFields::EvapotranspirationCalculationMethod, true);
      OS_ASSERT(value);
      return *value;
    }

    bool IndoorLivingWall_Impl::setEvapotranspirationCalculationMethod(const std::string& evapotranspirationCalculationMethod) {
      return setString(openstudio::IndoorLivingWallFields::EvapotranspirationCalculationMethod, evapotranspirationCalculationMethod);
    }

    bool IndoorLivingWall_Impl::isEvapotranspirationCalculationMethodDefaulted() const {
      return isEmpty(openstudio::IndoorLivingWallFields::EvapotranspirationCalculationMethod);
    }

    void IndoorLivingWall_Impl::resetEvapotranspirationCalculationMethod() {
      OS_ASSERT(setString(openstudio::IndoorLivingWallFields::EvapotranspirationCalculationMethod, ""));
    }

    boost::optional<std::string> IndoorLivingWall_Impl::lightingMethod() const {
      return getString(openstudio::IndoorLivingWallFields::LightingMethod, true);
    }

    bool IndoorLivingWall_Impl::setLightingMethod(const std::string& lightingMethod) {
      return setString(openstudio::IndoorLivingWallFields::LightingMethod, lightingMethod);
    }

    void IndoorLivingWall_Impl::resetLightingMethod() {
      OS_ASSERT(setString(openstudio::IndoorLivingWallFields::LightingMethod, ""));
    }

    boost::optional<std::string> IndoorLivingWall_Impl::daylightingControlName() const {
      return getString(openstudio::IndoorLivingWallFields::DaylightingControlName, true);
    }

    bool IndoorLivingWall_Impl::setDaylightingControlName(const std::string& daylightingControlName) {
      const bool result = setString(openstudio::IndoorLivingWallFields::DaylightingControlName, daylightingControlName);
      OS_ASSERT(result);
      return result;
    }

    void IndoorLivingWall_Impl::resetDaylightingControlName() {
      OS_ASSERT(setString(openstudio::IndoorLivingWallFields::DaylightingControlName, ""));
    }

    boost::optional<double> IndoorLivingWall_Impl::totalLeafArea() const {
      return getDouble(openstudio::IndoorLivingWallFields::TotalLeafArea, true);
    }

    bool IndoorLivingWall_Impl::setTotalLeafArea(double totalLeafArea) {
      return setDouble(openstudio::IndoorLivingWallFields::TotalLeafArea, totalLeafArea);
    }

    void IndoorLivingWall_Impl::resetTotalLeafArea() {
      OS_ASSERT(setString(openstudio::IndoorLivingWallFields::TotalLeafArea, ""));
    }

    boost::optional<double> IndoorLivingWall_Impl::lEDNominalIntensity() const {
      return getDouble(openstudio::IndoorLivingWallFields::LEDNominalIntensity, true);
    }

    bool IndoorLivingWall_Impl::setLEDNominalIntensity(double lEDNominalIntensity) {
      return setDouble(openstudio::IndoorLivingWallFields::LEDNominalIntensity, lEDNominalIntensity);
    }

    void IndoorLivingWall_Impl::resetLEDNominalIntensity() {
      OS_ASSERT(setString(openstudio::IndoorLivingWallFields::LEDNominalIntensity, ""));
    }

    boost::optional<double> IndoorLivingWall_Impl::lEDNominalPower() const {
      return getDouble(openstudio::IndoorLivingWallFields::LEDNominalPower, true);
    }

    bool IndoorLivingWall_Impl::setLEDNominalPower(double lEDNominalPower) {
      return setDouble(openstudio::IndoorLivingWallFields::LEDNominalPower, lEDNominalPower);
    }

    void IndoorLivingWall_Impl::resetLEDNominalPower() {
      OS_ASSERT(setString(openstudio::IndoorLivingWallFields::LEDNominalPower, ""));
    }

    double IndoorLivingWall_Impl::radiantFractionofLEDLights() const {
      const auto value = getDouble(openstudio::IndoorLivingWallFields::RadiantFractionofLEDLights, true);
      OS_ASSERT(value);
      return *value;
    }

    bool IndoorLivingWall_Impl::isRadiantFractionofLEDLightsDefaulted() const {
      return isEmpty(openstudio::IndoorLivingWallFields::RadiantFractionofLEDLights);
    }

    bool IndoorLivingWall_Impl::setRadiantFractionofLEDLights(double radiantFractionofLEDLights) {
      return setDouble(openstudio::IndoorLivingWallFields::RadiantFractionofLEDLights, radiantFractionofLEDLights);
    }

    void IndoorLivingWall_Impl::resetRadiantFractionofLEDLights() {
      OS_ASSERT(setString(openstudio::IndoorLivingWallFields::RadiantFractionofLEDLights, ""));
    }

    std::vector<std::string> IndoorLivingWall_Impl::evapotranspirationCalculationMethodValues() const {
      return openstudio::epmodel::IndoorLivingWall::evapotranspirationCalculationMethodValues();
    }

    std::vector<std::string> IndoorLivingWall_Impl::lightingMethodValues() const {
      return openstudio::epmodel::IndoorLivingWall::lightingMethodValues();
    }

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
