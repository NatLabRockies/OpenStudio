/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "RoomAirSettingsUnderFloorAirDistributionInterior.hpp"
#include "RoomAirSettingsUnderFloorAirDistributionInterior_Impl.hpp"

#include "Model.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/idd/IddEnums.hxx>
#include <utilities/idd/IddFactory.hxx>
#include <utilities/idd/IddObject.hpp>
#include <utilities/idd/RoomAirSettings_UnderFloorAirDistributionInterior_FieldEnums.hxx>

namespace openstudio {
namespace epmodel {

  RoomAirSettingsUnderFloorAirDistributionInterior::RoomAirSettingsUnderFloorAirDistributionInterior(const Model& model)
    : ModelObject(RoomAirSettingsUnderFloorAirDistributionInterior::iddObjectType(), model) {}

  RoomAirSettingsUnderFloorAirDistributionInterior::RoomAirSettingsUnderFloorAirDistributionInterior(
    std::shared_ptr<detail::RoomAirSettingsUnderFloorAirDistributionInterior_Impl> impl)
    : ModelObject(std::move(impl)) {}

  IddObjectType RoomAirSettingsUnderFloorAirDistributionInterior::iddObjectType() {
    return IddObjectType::RoomAirSettings_UnderFloorAirDistributionInterior;
  }

  std::vector<std::string> RoomAirSettingsUnderFloorAirDistributionInterior::floorDiffuserTypeValues() {
    return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(),
                          openstudio::RoomAirSettings_UnderFloorAirDistributionInteriorFields::FloorDiffuserType);
  }

  boost::optional<double> RoomAirSettingsUnderFloorAirDistributionInterior::numberofDiffusers() const {
    return getImpl<detail::RoomAirSettingsUnderFloorAirDistributionInterior_Impl>()->numberofDiffusers();
  }

  bool RoomAirSettingsUnderFloorAirDistributionInterior::isNumberofDiffusersDefaulted() const {
    return getImpl<detail::RoomAirSettingsUnderFloorAirDistributionInterior_Impl>()->isNumberofDiffusersDefaulted();
  }

  bool RoomAirSettingsUnderFloorAirDistributionInterior::isNumberofDiffusersAutocalculated() const {
    return getImpl<detail::RoomAirSettingsUnderFloorAirDistributionInterior_Impl>()->isNumberofDiffusersAutocalculated();
  }

  bool RoomAirSettingsUnderFloorAirDistributionInterior::setNumberofDiffusers(double numberofDiffusers) {
    return getImpl<detail::RoomAirSettingsUnderFloorAirDistributionInterior_Impl>()->setNumberofDiffusers(numberofDiffusers);
  }

  void RoomAirSettingsUnderFloorAirDistributionInterior::resetNumberofDiffusers() {
    getImpl<detail::RoomAirSettingsUnderFloorAirDistributionInterior_Impl>()->resetNumberofDiffusers();
  }

  void RoomAirSettingsUnderFloorAirDistributionInterior::autocalculateNumberofDiffusers() {
    getImpl<detail::RoomAirSettingsUnderFloorAirDistributionInterior_Impl>()->autocalculateNumberofDiffusers();
  }

  boost::optional<double> RoomAirSettingsUnderFloorAirDistributionInterior::powerperPlume() const {
    return getImpl<detail::RoomAirSettingsUnderFloorAirDistributionInterior_Impl>()->powerperPlume();
  }

  bool RoomAirSettingsUnderFloorAirDistributionInterior::isPowerperPlumeDefaulted() const {
    return getImpl<detail::RoomAirSettingsUnderFloorAirDistributionInterior_Impl>()->isPowerperPlumeDefaulted();
  }

  bool RoomAirSettingsUnderFloorAirDistributionInterior::isPowerperPlumeAutocalculated() const {
    return getImpl<detail::RoomAirSettingsUnderFloorAirDistributionInterior_Impl>()->isPowerperPlumeAutocalculated();
  }

  bool RoomAirSettingsUnderFloorAirDistributionInterior::setPowerperPlume(double powerperPlume) {
    return getImpl<detail::RoomAirSettingsUnderFloorAirDistributionInterior_Impl>()->setPowerperPlume(powerperPlume);
  }

  void RoomAirSettingsUnderFloorAirDistributionInterior::resetPowerperPlume() {
    getImpl<detail::RoomAirSettingsUnderFloorAirDistributionInterior_Impl>()->resetPowerperPlume();
  }

  void RoomAirSettingsUnderFloorAirDistributionInterior::autocalculatePowerperPlume() {
    getImpl<detail::RoomAirSettingsUnderFloorAirDistributionInterior_Impl>()->autocalculatePowerperPlume();
  }

  boost::optional<double> RoomAirSettingsUnderFloorAirDistributionInterior::designEffectiveAreaofDiffuser() const {
    return getImpl<detail::RoomAirSettingsUnderFloorAirDistributionInterior_Impl>()->designEffectiveAreaofDiffuser();
  }

  bool RoomAirSettingsUnderFloorAirDistributionInterior::isDesignEffectiveAreaofDiffuserDefaulted() const {
    return getImpl<detail::RoomAirSettingsUnderFloorAirDistributionInterior_Impl>()->isDesignEffectiveAreaofDiffuserDefaulted();
  }

  bool RoomAirSettingsUnderFloorAirDistributionInterior::isDesignEffectiveAreaofDiffuserAutocalculated() const {
    return getImpl<detail::RoomAirSettingsUnderFloorAirDistributionInterior_Impl>()->isDesignEffectiveAreaofDiffuserAutocalculated();
  }

  bool RoomAirSettingsUnderFloorAirDistributionInterior::setDesignEffectiveAreaofDiffuser(double designEffectiveAreaofDiffuser) {
    return getImpl<detail::RoomAirSettingsUnderFloorAirDistributionInterior_Impl>()->setDesignEffectiveAreaofDiffuser(designEffectiveAreaofDiffuser);
  }

  void RoomAirSettingsUnderFloorAirDistributionInterior::resetDesignEffectiveAreaofDiffuser() {
    getImpl<detail::RoomAirSettingsUnderFloorAirDistributionInterior_Impl>()->resetDesignEffectiveAreaofDiffuser();
  }

  void RoomAirSettingsUnderFloorAirDistributionInterior::autocalculateDesignEffectiveAreaofDiffuser() {
    getImpl<detail::RoomAirSettingsUnderFloorAirDistributionInterior_Impl>()->autocalculateDesignEffectiveAreaofDiffuser();
  }

  boost::optional<double> RoomAirSettingsUnderFloorAirDistributionInterior::diffuserSlotAnglefromVertical() const {
    return getImpl<detail::RoomAirSettingsUnderFloorAirDistributionInterior_Impl>()->diffuserSlotAnglefromVertical();
  }

  bool RoomAirSettingsUnderFloorAirDistributionInterior::isDiffuserSlotAnglefromVerticalDefaulted() const {
    return getImpl<detail::RoomAirSettingsUnderFloorAirDistributionInterior_Impl>()->isDiffuserSlotAnglefromVerticalDefaulted();
  }

  bool RoomAirSettingsUnderFloorAirDistributionInterior::isDiffuserSlotAnglefromVerticalAutocalculated() const {
    return getImpl<detail::RoomAirSettingsUnderFloorAirDistributionInterior_Impl>()->isDiffuserSlotAnglefromVerticalAutocalculated();
  }

  bool RoomAirSettingsUnderFloorAirDistributionInterior::setDiffuserSlotAnglefromVertical(double diffuserSlotAnglefromVertical) {
    return getImpl<detail::RoomAirSettingsUnderFloorAirDistributionInterior_Impl>()->setDiffuserSlotAnglefromVertical(diffuserSlotAnglefromVertical);
  }

  void RoomAirSettingsUnderFloorAirDistributionInterior::resetDiffuserSlotAnglefromVertical() {
    getImpl<detail::RoomAirSettingsUnderFloorAirDistributionInterior_Impl>()->resetDiffuserSlotAnglefromVertical();
  }

  void RoomAirSettingsUnderFloorAirDistributionInterior::autocalculateDiffuserSlotAnglefromVertical() {
    getImpl<detail::RoomAirSettingsUnderFloorAirDistributionInterior_Impl>()->autocalculateDiffuserSlotAnglefromVertical();
  }

  double RoomAirSettingsUnderFloorAirDistributionInterior::thermostatHeight() const {
    return getImpl<detail::RoomAirSettingsUnderFloorAirDistributionInterior_Impl>()->thermostatHeight();
  }

  bool RoomAirSettingsUnderFloorAirDistributionInterior::isThermostatHeightDefaulted() const {
    return getImpl<detail::RoomAirSettingsUnderFloorAirDistributionInterior_Impl>()->isThermostatHeightDefaulted();
  }

  bool RoomAirSettingsUnderFloorAirDistributionInterior::setThermostatHeight(double thermostatHeight) {
    return getImpl<detail::RoomAirSettingsUnderFloorAirDistributionInterior_Impl>()->setThermostatHeight(thermostatHeight);
  }

  void RoomAirSettingsUnderFloorAirDistributionInterior::resetThermostatHeight() {
    getImpl<detail::RoomAirSettingsUnderFloorAirDistributionInterior_Impl>()->resetThermostatHeight();
  }

  double RoomAirSettingsUnderFloorAirDistributionInterior::comfortHeight() const {
    return getImpl<detail::RoomAirSettingsUnderFloorAirDistributionInterior_Impl>()->comfortHeight();
  }

  bool RoomAirSettingsUnderFloorAirDistributionInterior::isComfortHeightDefaulted() const {
    return getImpl<detail::RoomAirSettingsUnderFloorAirDistributionInterior_Impl>()->isComfortHeightDefaulted();
  }

  bool RoomAirSettingsUnderFloorAirDistributionInterior::setComfortHeight(double comfortHeight) {
    return getImpl<detail::RoomAirSettingsUnderFloorAirDistributionInterior_Impl>()->setComfortHeight(comfortHeight);
  }

  void RoomAirSettingsUnderFloorAirDistributionInterior::resetComfortHeight() {
    getImpl<detail::RoomAirSettingsUnderFloorAirDistributionInterior_Impl>()->resetComfortHeight();
  }

  double RoomAirSettingsUnderFloorAirDistributionInterior::temperatureDifferenceThresholdforReporting() const {
    return getImpl<detail::RoomAirSettingsUnderFloorAirDistributionInterior_Impl>()->temperatureDifferenceThresholdforReporting();
  }

  bool RoomAirSettingsUnderFloorAirDistributionInterior::isTemperatureDifferenceThresholdforReportingDefaulted() const {
    return getImpl<detail::RoomAirSettingsUnderFloorAirDistributionInterior_Impl>()->isTemperatureDifferenceThresholdforReportingDefaulted();
  }

  bool RoomAirSettingsUnderFloorAirDistributionInterior::setTemperatureDifferenceThresholdforReporting(
    double temperatureDifferenceThresholdforReporting) {
    return getImpl<detail::RoomAirSettingsUnderFloorAirDistributionInterior_Impl>()->setTemperatureDifferenceThresholdforReporting(
      temperatureDifferenceThresholdforReporting);
  }

  void RoomAirSettingsUnderFloorAirDistributionInterior::resetTemperatureDifferenceThresholdforReporting() {
    getImpl<detail::RoomAirSettingsUnderFloorAirDistributionInterior_Impl>()->resetTemperatureDifferenceThresholdforReporting();
  }

  std::string RoomAirSettingsUnderFloorAirDistributionInterior::floorDiffuserType() const {
    return getImpl<detail::RoomAirSettingsUnderFloorAirDistributionInterior_Impl>()->floorDiffuserType();
  }

  bool RoomAirSettingsUnderFloorAirDistributionInterior::isFloorDiffuserTypeDefaulted() const {
    return getImpl<detail::RoomAirSettingsUnderFloorAirDistributionInterior_Impl>()->isFloorDiffuserTypeDefaulted();
  }

  bool RoomAirSettingsUnderFloorAirDistributionInterior::setFloorDiffuserType(const std::string& floorDiffuserType) {
    return getImpl<detail::RoomAirSettingsUnderFloorAirDistributionInterior_Impl>()->setFloorDiffuserType(floorDiffuserType);
  }

  void RoomAirSettingsUnderFloorAirDistributionInterior::resetFloorDiffuserType() {
    getImpl<detail::RoomAirSettingsUnderFloorAirDistributionInterior_Impl>()->resetFloorDiffuserType();
  }

  boost::optional<double> RoomAirSettingsUnderFloorAirDistributionInterior::transitionHeight() const {
    return getImpl<detail::RoomAirSettingsUnderFloorAirDistributionInterior_Impl>()->transitionHeight();
  }

  bool RoomAirSettingsUnderFloorAirDistributionInterior::isTransitionHeightDefaulted() const {
    return getImpl<detail::RoomAirSettingsUnderFloorAirDistributionInterior_Impl>()->isTransitionHeightDefaulted();
  }

  bool RoomAirSettingsUnderFloorAirDistributionInterior::isTransitionHeightAutocalculated() const {
    return getImpl<detail::RoomAirSettingsUnderFloorAirDistributionInterior_Impl>()->isTransitionHeightAutocalculated();
  }

  bool RoomAirSettingsUnderFloorAirDistributionInterior::setTransitionHeight(double transitionHeight) {
    return getImpl<detail::RoomAirSettingsUnderFloorAirDistributionInterior_Impl>()->setTransitionHeight(transitionHeight);
  }

  void RoomAirSettingsUnderFloorAirDistributionInterior::resetTransitionHeight() {
    getImpl<detail::RoomAirSettingsUnderFloorAirDistributionInterior_Impl>()->resetTransitionHeight();
  }

  void RoomAirSettingsUnderFloorAirDistributionInterior::autocalculateTransitionHeight() {
    getImpl<detail::RoomAirSettingsUnderFloorAirDistributionInterior_Impl>()->autocalculateTransitionHeight();
  }

  boost::optional<double> RoomAirSettingsUnderFloorAirDistributionInterior::coefficientA() const {
    return getImpl<detail::RoomAirSettingsUnderFloorAirDistributionInterior_Impl>()->coefficientA();
  }

  bool RoomAirSettingsUnderFloorAirDistributionInterior::isCoefficientADefaulted() const {
    return getImpl<detail::RoomAirSettingsUnderFloorAirDistributionInterior_Impl>()->isCoefficientADefaulted();
  }

  bool RoomAirSettingsUnderFloorAirDistributionInterior::isCoefficientAAutocalculated() const {
    return getImpl<detail::RoomAirSettingsUnderFloorAirDistributionInterior_Impl>()->isCoefficientAAutocalculated();
  }

  bool RoomAirSettingsUnderFloorAirDistributionInterior::setCoefficientA(double coefficientA) {
    return getImpl<detail::RoomAirSettingsUnderFloorAirDistributionInterior_Impl>()->setCoefficientA(coefficientA);
  }

  void RoomAirSettingsUnderFloorAirDistributionInterior::resetCoefficientA() {
    getImpl<detail::RoomAirSettingsUnderFloorAirDistributionInterior_Impl>()->resetCoefficientA();
  }

  void RoomAirSettingsUnderFloorAirDistributionInterior::autocalculateCoefficientA() {
    getImpl<detail::RoomAirSettingsUnderFloorAirDistributionInterior_Impl>()->autocalculateCoefficientA();
  }

  boost::optional<double> RoomAirSettingsUnderFloorAirDistributionInterior::coefficientB() const {
    return getImpl<detail::RoomAirSettingsUnderFloorAirDistributionInterior_Impl>()->coefficientB();
  }

  bool RoomAirSettingsUnderFloorAirDistributionInterior::isCoefficientBDefaulted() const {
    return getImpl<detail::RoomAirSettingsUnderFloorAirDistributionInterior_Impl>()->isCoefficientBDefaulted();
  }

  bool RoomAirSettingsUnderFloorAirDistributionInterior::isCoefficientBAutocalculated() const {
    return getImpl<detail::RoomAirSettingsUnderFloorAirDistributionInterior_Impl>()->isCoefficientBAutocalculated();
  }

  bool RoomAirSettingsUnderFloorAirDistributionInterior::setCoefficientB(double coefficientB) {
    return getImpl<detail::RoomAirSettingsUnderFloorAirDistributionInterior_Impl>()->setCoefficientB(coefficientB);
  }

  void RoomAirSettingsUnderFloorAirDistributionInterior::resetCoefficientB() {
    getImpl<detail::RoomAirSettingsUnderFloorAirDistributionInterior_Impl>()->resetCoefficientB();
  }

  void RoomAirSettingsUnderFloorAirDistributionInterior::autocalculateCoefficientB() {
    getImpl<detail::RoomAirSettingsUnderFloorAirDistributionInterior_Impl>()->autocalculateCoefficientB();
  }

  boost::optional<double> RoomAirSettingsUnderFloorAirDistributionInterior::coefficientC() const {
    return getImpl<detail::RoomAirSettingsUnderFloorAirDistributionInterior_Impl>()->coefficientC();
  }

  bool RoomAirSettingsUnderFloorAirDistributionInterior::isCoefficientCDefaulted() const {
    return getImpl<detail::RoomAirSettingsUnderFloorAirDistributionInterior_Impl>()->isCoefficientCDefaulted();
  }

  bool RoomAirSettingsUnderFloorAirDistributionInterior::isCoefficientCAutocalculated() const {
    return getImpl<detail::RoomAirSettingsUnderFloorAirDistributionInterior_Impl>()->isCoefficientCAutocalculated();
  }

  bool RoomAirSettingsUnderFloorAirDistributionInterior::setCoefficientC(double coefficientC) {
    return getImpl<detail::RoomAirSettingsUnderFloorAirDistributionInterior_Impl>()->setCoefficientC(coefficientC);
  }

  void RoomAirSettingsUnderFloorAirDistributionInterior::resetCoefficientC() {
    getImpl<detail::RoomAirSettingsUnderFloorAirDistributionInterior_Impl>()->resetCoefficientC();
  }

  void RoomAirSettingsUnderFloorAirDistributionInterior::autocalculateCoefficientC() {
    getImpl<detail::RoomAirSettingsUnderFloorAirDistributionInterior_Impl>()->autocalculateCoefficientC();
  }

  boost::optional<double> RoomAirSettingsUnderFloorAirDistributionInterior::coefficientD() const {
    return getImpl<detail::RoomAirSettingsUnderFloorAirDistributionInterior_Impl>()->coefficientD();
  }

  bool RoomAirSettingsUnderFloorAirDistributionInterior::isCoefficientDDefaulted() const {
    return getImpl<detail::RoomAirSettingsUnderFloorAirDistributionInterior_Impl>()->isCoefficientDDefaulted();
  }

  bool RoomAirSettingsUnderFloorAirDistributionInterior::isCoefficientDAutocalculated() const {
    return getImpl<detail::RoomAirSettingsUnderFloorAirDistributionInterior_Impl>()->isCoefficientDAutocalculated();
  }

  bool RoomAirSettingsUnderFloorAirDistributionInterior::setCoefficientD(double coefficientD) {
    return getImpl<detail::RoomAirSettingsUnderFloorAirDistributionInterior_Impl>()->setCoefficientD(coefficientD);
  }

  void RoomAirSettingsUnderFloorAirDistributionInterior::resetCoefficientD() {
    getImpl<detail::RoomAirSettingsUnderFloorAirDistributionInterior_Impl>()->resetCoefficientD();
  }

  void RoomAirSettingsUnderFloorAirDistributionInterior::autocalculateCoefficientD() {
    getImpl<detail::RoomAirSettingsUnderFloorAirDistributionInterior_Impl>()->autocalculateCoefficientD();
  }

  boost::optional<double> RoomAirSettingsUnderFloorAirDistributionInterior::coefficientE() const {
    return getImpl<detail::RoomAirSettingsUnderFloorAirDistributionInterior_Impl>()->coefficientE();
  }

  bool RoomAirSettingsUnderFloorAirDistributionInterior::isCoefficientEDefaulted() const {
    return getImpl<detail::RoomAirSettingsUnderFloorAirDistributionInterior_Impl>()->isCoefficientEDefaulted();
  }

  bool RoomAirSettingsUnderFloorAirDistributionInterior::isCoefficientEAutocalculated() const {
    return getImpl<detail::RoomAirSettingsUnderFloorAirDistributionInterior_Impl>()->isCoefficientEAutocalculated();
  }

  bool RoomAirSettingsUnderFloorAirDistributionInterior::setCoefficientE(double coefficientE) {
    return getImpl<detail::RoomAirSettingsUnderFloorAirDistributionInterior_Impl>()->setCoefficientE(coefficientE);
  }

  void RoomAirSettingsUnderFloorAirDistributionInterior::resetCoefficientE() {
    getImpl<detail::RoomAirSettingsUnderFloorAirDistributionInterior_Impl>()->resetCoefficientE();
  }

  void RoomAirSettingsUnderFloorAirDistributionInterior::autocalculateCoefficientE() {
    getImpl<detail::RoomAirSettingsUnderFloorAirDistributionInterior_Impl>()->autocalculateCoefficientE();
  }

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
  namespace detail {

    boost::optional<double> RoomAirSettingsUnderFloorAirDistributionInterior_Impl::numberofDiffusers() const {
      return getDouble(openstudio::RoomAirSettings_UnderFloorAirDistributionInteriorFields::NumberofDiffusers, true);
    }

    bool RoomAirSettingsUnderFloorAirDistributionInterior_Impl::isNumberofDiffusersDefaulted() const {
      return isEmpty(openstudio::RoomAirSettings_UnderFloorAirDistributionInteriorFields::NumberofDiffusers);
    }

    bool RoomAirSettingsUnderFloorAirDistributionInterior_Impl::isNumberofDiffusersAutocalculated() const {
      if (const auto value = getString(openstudio::RoomAirSettings_UnderFloorAirDistributionInteriorFields::NumberofDiffusers, true)) {
        return openstudio::istringEqual(*value, "autocalculate");
      }
      return false;
    }

    bool RoomAirSettingsUnderFloorAirDistributionInterior_Impl::setNumberofDiffusers(double numberofDiffusers) {
      return setDouble(openstudio::RoomAirSettings_UnderFloorAirDistributionInteriorFields::NumberofDiffusers, numberofDiffusers);
    }

    void RoomAirSettingsUnderFloorAirDistributionInterior_Impl::resetNumberofDiffusers() {
      OS_ASSERT(setString(openstudio::RoomAirSettings_UnderFloorAirDistributionInteriorFields::NumberofDiffusers, ""));
    }

    void RoomAirSettingsUnderFloorAirDistributionInterior_Impl::autocalculateNumberofDiffusers() {
      OS_ASSERT(setString(openstudio::RoomAirSettings_UnderFloorAirDistributionInteriorFields::NumberofDiffusers, "autocalculate"));
    }

    boost::optional<double> RoomAirSettingsUnderFloorAirDistributionInterior_Impl::powerperPlume() const {
      return getDouble(openstudio::RoomAirSettings_UnderFloorAirDistributionInteriorFields::PowerperPlume, true);
    }

    bool RoomAirSettingsUnderFloorAirDistributionInterior_Impl::isPowerperPlumeDefaulted() const {
      return isEmpty(openstudio::RoomAirSettings_UnderFloorAirDistributionInteriorFields::PowerperPlume);
    }

    bool RoomAirSettingsUnderFloorAirDistributionInterior_Impl::isPowerperPlumeAutocalculated() const {
      if (const auto value = getString(openstudio::RoomAirSettings_UnderFloorAirDistributionInteriorFields::PowerperPlume, true)) {
        return openstudio::istringEqual(*value, "autocalculate");
      }
      return false;
    }

    bool RoomAirSettingsUnderFloorAirDistributionInterior_Impl::setPowerperPlume(double powerperPlume) {
      return setDouble(openstudio::RoomAirSettings_UnderFloorAirDistributionInteriorFields::PowerperPlume, powerperPlume);
    }

    void RoomAirSettingsUnderFloorAirDistributionInterior_Impl::resetPowerperPlume() {
      OS_ASSERT(setString(openstudio::RoomAirSettings_UnderFloorAirDistributionInteriorFields::PowerperPlume, ""));
    }

    void RoomAirSettingsUnderFloorAirDistributionInterior_Impl::autocalculatePowerperPlume() {
      OS_ASSERT(setString(openstudio::RoomAirSettings_UnderFloorAirDistributionInteriorFields::PowerperPlume, "autocalculate"));
    }

    boost::optional<double> RoomAirSettingsUnderFloorAirDistributionInterior_Impl::designEffectiveAreaofDiffuser() const {
      return getDouble(openstudio::RoomAirSettings_UnderFloorAirDistributionInteriorFields::DesignEffectiveAreaofDiffuser, true);
    }

    bool RoomAirSettingsUnderFloorAirDistributionInterior_Impl::isDesignEffectiveAreaofDiffuserDefaulted() const {
      return isEmpty(openstudio::RoomAirSettings_UnderFloorAirDistributionInteriorFields::DesignEffectiveAreaofDiffuser);
    }

    bool RoomAirSettingsUnderFloorAirDistributionInterior_Impl::isDesignEffectiveAreaofDiffuserAutocalculated() const {
      if (const auto value = getString(openstudio::RoomAirSettings_UnderFloorAirDistributionInteriorFields::DesignEffectiveAreaofDiffuser, true)) {
        return openstudio::istringEqual(*value, "autocalculate");
      }
      return false;
    }

    bool RoomAirSettingsUnderFloorAirDistributionInterior_Impl::setDesignEffectiveAreaofDiffuser(double designEffectiveAreaofDiffuser) {
      return setDouble(openstudio::RoomAirSettings_UnderFloorAirDistributionInteriorFields::DesignEffectiveAreaofDiffuser,
                       designEffectiveAreaofDiffuser);
    }

    void RoomAirSettingsUnderFloorAirDistributionInterior_Impl::resetDesignEffectiveAreaofDiffuser() {
      OS_ASSERT(setString(openstudio::RoomAirSettings_UnderFloorAirDistributionInteriorFields::DesignEffectiveAreaofDiffuser, ""));
    }

    void RoomAirSettingsUnderFloorAirDistributionInterior_Impl::autocalculateDesignEffectiveAreaofDiffuser() {
      OS_ASSERT(setString(openstudio::RoomAirSettings_UnderFloorAirDistributionInteriorFields::DesignEffectiveAreaofDiffuser, "autocalculate"));
    }

    boost::optional<double> RoomAirSettingsUnderFloorAirDistributionInterior_Impl::diffuserSlotAnglefromVertical() const {
      return getDouble(openstudio::RoomAirSettings_UnderFloorAirDistributionInteriorFields::DiffuserSlotAnglefromVertical, true);
    }

    bool RoomAirSettingsUnderFloorAirDistributionInterior_Impl::isDiffuserSlotAnglefromVerticalDefaulted() const {
      return isEmpty(openstudio::RoomAirSettings_UnderFloorAirDistributionInteriorFields::DiffuserSlotAnglefromVertical);
    }

    bool RoomAirSettingsUnderFloorAirDistributionInterior_Impl::isDiffuserSlotAnglefromVerticalAutocalculated() const {
      if (const auto value = getString(openstudio::RoomAirSettings_UnderFloorAirDistributionInteriorFields::DiffuserSlotAnglefromVertical, true)) {
        return openstudio::istringEqual(*value, "autocalculate");
      }
      return false;
    }

    bool RoomAirSettingsUnderFloorAirDistributionInterior_Impl::setDiffuserSlotAnglefromVertical(double diffuserSlotAnglefromVertical) {
      return setDouble(openstudio::RoomAirSettings_UnderFloorAirDistributionInteriorFields::DiffuserSlotAnglefromVertical,
                       diffuserSlotAnglefromVertical);
    }

    void RoomAirSettingsUnderFloorAirDistributionInterior_Impl::resetDiffuserSlotAnglefromVertical() {
      OS_ASSERT(setString(openstudio::RoomAirSettings_UnderFloorAirDistributionInteriorFields::DiffuserSlotAnglefromVertical, ""));
    }

    void RoomAirSettingsUnderFloorAirDistributionInterior_Impl::autocalculateDiffuserSlotAnglefromVertical() {
      OS_ASSERT(setString(openstudio::RoomAirSettings_UnderFloorAirDistributionInteriorFields::DiffuserSlotAnglefromVertical, "autocalculate"));
    }

    double RoomAirSettingsUnderFloorAirDistributionInterior_Impl::thermostatHeight() const {
      const auto value = getDouble(openstudio::RoomAirSettings_UnderFloorAirDistributionInteriorFields::ThermostatHeight, true);
      OS_ASSERT(value);
      return *value;
    }

    bool RoomAirSettingsUnderFloorAirDistributionInterior_Impl::isThermostatHeightDefaulted() const {
      return isEmpty(openstudio::RoomAirSettings_UnderFloorAirDistributionInteriorFields::ThermostatHeight);
    }

    bool RoomAirSettingsUnderFloorAirDistributionInterior_Impl::setThermostatHeight(double thermostatHeight) {
      return setDouble(openstudio::RoomAirSettings_UnderFloorAirDistributionInteriorFields::ThermostatHeight, thermostatHeight);
    }

    void RoomAirSettingsUnderFloorAirDistributionInterior_Impl::resetThermostatHeight() {
      OS_ASSERT(setString(openstudio::RoomAirSettings_UnderFloorAirDistributionInteriorFields::ThermostatHeight, ""));
    }

    double RoomAirSettingsUnderFloorAirDistributionInterior_Impl::comfortHeight() const {
      const auto value = getDouble(openstudio::RoomAirSettings_UnderFloorAirDistributionInteriorFields::ComfortHeight, true);
      OS_ASSERT(value);
      return *value;
    }

    bool RoomAirSettingsUnderFloorAirDistributionInterior_Impl::isComfortHeightDefaulted() const {
      return isEmpty(openstudio::RoomAirSettings_UnderFloorAirDistributionInteriorFields::ComfortHeight);
    }

    bool RoomAirSettingsUnderFloorAirDistributionInterior_Impl::setComfortHeight(double comfortHeight) {
      return setDouble(openstudio::RoomAirSettings_UnderFloorAirDistributionInteriorFields::ComfortHeight, comfortHeight);
    }

    void RoomAirSettingsUnderFloorAirDistributionInterior_Impl::resetComfortHeight() {
      OS_ASSERT(setString(openstudio::RoomAirSettings_UnderFloorAirDistributionInteriorFields::ComfortHeight, ""));
    }

    double RoomAirSettingsUnderFloorAirDistributionInterior_Impl::temperatureDifferenceThresholdforReporting() const {
      const auto value =
        getDouble(openstudio::RoomAirSettings_UnderFloorAirDistributionInteriorFields::TemperatureDifferenceThresholdforReporting, true);
      OS_ASSERT(value);
      return *value;
    }

    bool RoomAirSettingsUnderFloorAirDistributionInterior_Impl::isTemperatureDifferenceThresholdforReportingDefaulted() const {
      return isEmpty(openstudio::RoomAirSettings_UnderFloorAirDistributionInteriorFields::TemperatureDifferenceThresholdforReporting);
    }

    bool RoomAirSettingsUnderFloorAirDistributionInterior_Impl::setTemperatureDifferenceThresholdforReporting(
      double temperatureDifferenceThresholdforReporting) {
      return setDouble(openstudio::RoomAirSettings_UnderFloorAirDistributionInteriorFields::TemperatureDifferenceThresholdforReporting,
                       temperatureDifferenceThresholdforReporting);
    }

    void RoomAirSettingsUnderFloorAirDistributionInterior_Impl::resetTemperatureDifferenceThresholdforReporting() {
      OS_ASSERT(setString(openstudio::RoomAirSettings_UnderFloorAirDistributionInteriorFields::TemperatureDifferenceThresholdforReporting, ""));
    }

    std::string RoomAirSettingsUnderFloorAirDistributionInterior_Impl::floorDiffuserType() const {
      const auto value = getString(openstudio::RoomAirSettings_UnderFloorAirDistributionInteriorFields::FloorDiffuserType, true);
      OS_ASSERT(value);
      return *value;
    }

    bool RoomAirSettingsUnderFloorAirDistributionInterior_Impl::isFloorDiffuserTypeDefaulted() const {
      return isEmpty(openstudio::RoomAirSettings_UnderFloorAirDistributionInteriorFields::FloorDiffuserType);
    }

    bool RoomAirSettingsUnderFloorAirDistributionInterior_Impl::setFloorDiffuserType(const std::string& floorDiffuserType) {
      return setString(openstudio::RoomAirSettings_UnderFloorAirDistributionInteriorFields::FloorDiffuserType, floorDiffuserType);
    }

    void RoomAirSettingsUnderFloorAirDistributionInterior_Impl::resetFloorDiffuserType() {
      OS_ASSERT(setString(openstudio::RoomAirSettings_UnderFloorAirDistributionInteriorFields::FloorDiffuserType, ""));
    }

    boost::optional<double> RoomAirSettingsUnderFloorAirDistributionInterior_Impl::transitionHeight() const {
      return getDouble(openstudio::RoomAirSettings_UnderFloorAirDistributionInteriorFields::TransitionHeight, true);
    }

    bool RoomAirSettingsUnderFloorAirDistributionInterior_Impl::isTransitionHeightDefaulted() const {
      return isEmpty(openstudio::RoomAirSettings_UnderFloorAirDistributionInteriorFields::TransitionHeight);
    }

    bool RoomAirSettingsUnderFloorAirDistributionInterior_Impl::isTransitionHeightAutocalculated() const {
      if (const auto value = getString(openstudio::RoomAirSettings_UnderFloorAirDistributionInteriorFields::TransitionHeight, true)) {
        return openstudio::istringEqual(*value, "autocalculate");
      }
      return false;
    }

    bool RoomAirSettingsUnderFloorAirDistributionInterior_Impl::setTransitionHeight(double transitionHeight) {
      return setDouble(openstudio::RoomAirSettings_UnderFloorAirDistributionInteriorFields::TransitionHeight, transitionHeight);
    }

    void RoomAirSettingsUnderFloorAirDistributionInterior_Impl::resetTransitionHeight() {
      OS_ASSERT(setString(openstudio::RoomAirSettings_UnderFloorAirDistributionInteriorFields::TransitionHeight, ""));
    }

    void RoomAirSettingsUnderFloorAirDistributionInterior_Impl::autocalculateTransitionHeight() {
      OS_ASSERT(setString(openstudio::RoomAirSettings_UnderFloorAirDistributionInteriorFields::TransitionHeight, "autocalculate"));
    }

    boost::optional<double> RoomAirSettingsUnderFloorAirDistributionInterior_Impl::coefficientA() const {
      return getDouble(openstudio::RoomAirSettings_UnderFloorAirDistributionInteriorFields::CoefficientA, true);
    }

    bool RoomAirSettingsUnderFloorAirDistributionInterior_Impl::isCoefficientADefaulted() const {
      return isEmpty(openstudio::RoomAirSettings_UnderFloorAirDistributionInteriorFields::CoefficientA);
    }

    bool RoomAirSettingsUnderFloorAirDistributionInterior_Impl::isCoefficientAAutocalculated() const {
      if (const auto value = getString(openstudio::RoomAirSettings_UnderFloorAirDistributionInteriorFields::CoefficientA, true)) {
        return openstudio::istringEqual(*value, "autocalculate");
      }
      return false;
    }

    bool RoomAirSettingsUnderFloorAirDistributionInterior_Impl::setCoefficientA(double coefficientA) {
      const bool result = setDouble(openstudio::RoomAirSettings_UnderFloorAirDistributionInteriorFields::CoefficientA, coefficientA);
      OS_ASSERT(result);
      return result;
    }

    void RoomAirSettingsUnderFloorAirDistributionInterior_Impl::resetCoefficientA() {
      OS_ASSERT(setString(openstudio::RoomAirSettings_UnderFloorAirDistributionInteriorFields::CoefficientA, ""));
    }

    void RoomAirSettingsUnderFloorAirDistributionInterior_Impl::autocalculateCoefficientA() {
      OS_ASSERT(setString(openstudio::RoomAirSettings_UnderFloorAirDistributionInteriorFields::CoefficientA, "autocalculate"));
    }

    boost::optional<double> RoomAirSettingsUnderFloorAirDistributionInterior_Impl::coefficientB() const {
      return getDouble(openstudio::RoomAirSettings_UnderFloorAirDistributionInteriorFields::CoefficientB, true);
    }

    bool RoomAirSettingsUnderFloorAirDistributionInterior_Impl::isCoefficientBDefaulted() const {
      return isEmpty(openstudio::RoomAirSettings_UnderFloorAirDistributionInteriorFields::CoefficientB);
    }

    bool RoomAirSettingsUnderFloorAirDistributionInterior_Impl::isCoefficientBAutocalculated() const {
      if (const auto value = getString(openstudio::RoomAirSettings_UnderFloorAirDistributionInteriorFields::CoefficientB, true)) {
        return openstudio::istringEqual(*value, "autocalculate");
      }
      return false;
    }

    bool RoomAirSettingsUnderFloorAirDistributionInterior_Impl::setCoefficientB(double coefficientB) {
      const bool result = setDouble(openstudio::RoomAirSettings_UnderFloorAirDistributionInteriorFields::CoefficientB, coefficientB);
      OS_ASSERT(result);
      return result;
    }

    void RoomAirSettingsUnderFloorAirDistributionInterior_Impl::resetCoefficientB() {
      OS_ASSERT(setString(openstudio::RoomAirSettings_UnderFloorAirDistributionInteriorFields::CoefficientB, ""));
    }

    void RoomAirSettingsUnderFloorAirDistributionInterior_Impl::autocalculateCoefficientB() {
      OS_ASSERT(setString(openstudio::RoomAirSettings_UnderFloorAirDistributionInteriorFields::CoefficientB, "autocalculate"));
    }

    boost::optional<double> RoomAirSettingsUnderFloorAirDistributionInterior_Impl::coefficientC() const {
      return getDouble(openstudio::RoomAirSettings_UnderFloorAirDistributionInteriorFields::CoefficientC, true);
    }

    bool RoomAirSettingsUnderFloorAirDistributionInterior_Impl::isCoefficientCDefaulted() const {
      return isEmpty(openstudio::RoomAirSettings_UnderFloorAirDistributionInteriorFields::CoefficientC);
    }

    bool RoomAirSettingsUnderFloorAirDistributionInterior_Impl::isCoefficientCAutocalculated() const {
      if (const auto value = getString(openstudio::RoomAirSettings_UnderFloorAirDistributionInteriorFields::CoefficientC, true)) {
        return openstudio::istringEqual(*value, "autocalculate");
      }
      return false;
    }

    bool RoomAirSettingsUnderFloorAirDistributionInterior_Impl::setCoefficientC(double coefficientC) {
      const bool result = setDouble(openstudio::RoomAirSettings_UnderFloorAirDistributionInteriorFields::CoefficientC, coefficientC);
      OS_ASSERT(result);
      return result;
    }

    void RoomAirSettingsUnderFloorAirDistributionInterior_Impl::resetCoefficientC() {
      OS_ASSERT(setString(openstudio::RoomAirSettings_UnderFloorAirDistributionInteriorFields::CoefficientC, ""));
    }

    void RoomAirSettingsUnderFloorAirDistributionInterior_Impl::autocalculateCoefficientC() {
      OS_ASSERT(setString(openstudio::RoomAirSettings_UnderFloorAirDistributionInteriorFields::CoefficientC, "autocalculate"));
    }

    boost::optional<double> RoomAirSettingsUnderFloorAirDistributionInterior_Impl::coefficientD() const {
      return getDouble(openstudio::RoomAirSettings_UnderFloorAirDistributionInteriorFields::CoefficientD, true);
    }

    bool RoomAirSettingsUnderFloorAirDistributionInterior_Impl::isCoefficientDDefaulted() const {
      return isEmpty(openstudio::RoomAirSettings_UnderFloorAirDistributionInteriorFields::CoefficientD);
    }

    bool RoomAirSettingsUnderFloorAirDistributionInterior_Impl::isCoefficientDAutocalculated() const {
      if (const auto value = getString(openstudio::RoomAirSettings_UnderFloorAirDistributionInteriorFields::CoefficientD, true)) {
        return openstudio::istringEqual(*value, "autocalculate");
      }
      return false;
    }

    bool RoomAirSettingsUnderFloorAirDistributionInterior_Impl::setCoefficientD(double coefficientD) {
      const bool result = setDouble(openstudio::RoomAirSettings_UnderFloorAirDistributionInteriorFields::CoefficientD, coefficientD);
      OS_ASSERT(result);
      return result;
    }

    void RoomAirSettingsUnderFloorAirDistributionInterior_Impl::resetCoefficientD() {
      OS_ASSERT(setString(openstudio::RoomAirSettings_UnderFloorAirDistributionInteriorFields::CoefficientD, ""));
    }

    void RoomAirSettingsUnderFloorAirDistributionInterior_Impl::autocalculateCoefficientD() {
      OS_ASSERT(setString(openstudio::RoomAirSettings_UnderFloorAirDistributionInteriorFields::CoefficientD, "autocalculate"));
    }

    boost::optional<double> RoomAirSettingsUnderFloorAirDistributionInterior_Impl::coefficientE() const {
      return getDouble(openstudio::RoomAirSettings_UnderFloorAirDistributionInteriorFields::CoefficientE, true);
    }

    bool RoomAirSettingsUnderFloorAirDistributionInterior_Impl::isCoefficientEDefaulted() const {
      return isEmpty(openstudio::RoomAirSettings_UnderFloorAirDistributionInteriorFields::CoefficientE);
    }

    bool RoomAirSettingsUnderFloorAirDistributionInterior_Impl::isCoefficientEAutocalculated() const {
      if (const auto value = getString(openstudio::RoomAirSettings_UnderFloorAirDistributionInteriorFields::CoefficientE, true)) {
        return openstudio::istringEqual(*value, "autocalculate");
      }
      return false;
    }

    bool RoomAirSettingsUnderFloorAirDistributionInterior_Impl::setCoefficientE(double coefficientE) {
      const bool result = setDouble(openstudio::RoomAirSettings_UnderFloorAirDistributionInteriorFields::CoefficientE, coefficientE);
      OS_ASSERT(result);
      return result;
    }

    void RoomAirSettingsUnderFloorAirDistributionInterior_Impl::resetCoefficientE() {
      OS_ASSERT(setString(openstudio::RoomAirSettings_UnderFloorAirDistributionInteriorFields::CoefficientE, ""));
    }

    void RoomAirSettingsUnderFloorAirDistributionInterior_Impl::autocalculateCoefficientE() {
      OS_ASSERT(setString(openstudio::RoomAirSettings_UnderFloorAirDistributionInteriorFields::CoefficientE, "autocalculate"));
    }

    std::vector<std::string> RoomAirSettingsUnderFloorAirDistributionInterior_Impl::floorDiffuserTypeValues() const {
      return openstudio::epmodel::RoomAirSettingsUnderFloorAirDistributionInterior::floorDiffuserTypeValues();
    }

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
