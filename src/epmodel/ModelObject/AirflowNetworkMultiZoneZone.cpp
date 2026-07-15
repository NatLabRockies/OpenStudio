/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "AirflowNetworkMultiZoneZone.hpp"
#include "AirflowNetworkMultiZoneZone_Impl.hpp"

#include "Model.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/idd/AirflowNetwork_MultiZone_Zone_FieldEnums.hxx>
#include <utilities/idd/IddEnums.hxx>
#include <utilities/idd/IddFactory.hxx>
#include <utilities/idd/IddObject.hpp>

namespace openstudio {
namespace epmodel {

  AirflowNetworkMultiZoneZone::AirflowNetworkMultiZoneZone(const Model& model) : ModelObject(AirflowNetworkMultiZoneZone::iddObjectType(), model) {}

  AirflowNetworkMultiZoneZone::AirflowNetworkMultiZoneZone(std::shared_ptr<detail::AirflowNetworkMultiZoneZone_Impl> impl)
    : ModelObject(std::move(impl)) {}

  IddObjectType AirflowNetworkMultiZoneZone::iddObjectType() {
    return IddObjectType::AirflowNetwork_MultiZone_Zone;
  }

  std::vector<std::string> AirflowNetworkMultiZoneZone::ventilationControlModeValues() {
    return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(),
                          openstudio::AirflowNetwork_MultiZone_ZoneFields::VentilationControlMode);
  }

  std::vector<std::string> AirflowNetworkMultiZoneZone::singleSidedWindPressureCoefficientAlgorithmValues() {
    return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(),
                          openstudio::AirflowNetwork_MultiZone_ZoneFields::SingleSidedWindPressureCoefficientAlgorithm);
  }

  std::string AirflowNetworkMultiZoneZone::ventilationControlMode() const {
    return getImpl<detail::AirflowNetworkMultiZoneZone_Impl>()->ventilationControlMode();
  }

  bool AirflowNetworkMultiZoneZone::isVentilationControlModeDefaulted() const {
    return getImpl<detail::AirflowNetworkMultiZoneZone_Impl>()->isVentilationControlModeDefaulted();
  }

  bool AirflowNetworkMultiZoneZone::setVentilationControlMode(const std::string& ventilationControlMode) {
    return getImpl<detail::AirflowNetworkMultiZoneZone_Impl>()->setVentilationControlMode(ventilationControlMode);
  }

  void AirflowNetworkMultiZoneZone::resetVentilationControlMode() {
    getImpl<detail::AirflowNetworkMultiZoneZone_Impl>()->resetVentilationControlMode();
  }

  double AirflowNetworkMultiZoneZone::minimumVentingOpenFactor() const {
    return getImpl<detail::AirflowNetworkMultiZoneZone_Impl>()->minimumVentingOpenFactor();
  }

  bool AirflowNetworkMultiZoneZone::isMinimumVentingOpenFactorDefaulted() const {
    return getImpl<detail::AirflowNetworkMultiZoneZone_Impl>()->isMinimumVentingOpenFactorDefaulted();
  }

  bool AirflowNetworkMultiZoneZone::setMinimumVentingOpenFactor(double minimumVentingOpenFactor) {
    return getImpl<detail::AirflowNetworkMultiZoneZone_Impl>()->setMinimumVentingOpenFactor(minimumVentingOpenFactor);
  }

  void AirflowNetworkMultiZoneZone::resetMinimumVentingOpenFactor() {
    getImpl<detail::AirflowNetworkMultiZoneZone_Impl>()->resetMinimumVentingOpenFactor();
  }

  double AirflowNetworkMultiZoneZone::indoorandOutdoorTemperatureDifferenceLowerLimitForMaximumVentingOpenFactor() const {
    return getImpl<detail::AirflowNetworkMultiZoneZone_Impl>()->indoorandOutdoorTemperatureDifferenceLowerLimitForMaximumVentingOpenFactor();
  }

  bool AirflowNetworkMultiZoneZone::isIndoorandOutdoorTemperatureDifferenceLowerLimitForMaximumVentingOpenFactorDefaulted() const {
    return getImpl<detail::AirflowNetworkMultiZoneZone_Impl>()
      ->isIndoorandOutdoorTemperatureDifferenceLowerLimitForMaximumVentingOpenFactorDefaulted();
  }

  bool AirflowNetworkMultiZoneZone::setIndoorandOutdoorTemperatureDifferenceLowerLimitForMaximumVentingOpenFactor(
    double indoorandOutdoorTemperatureDifferenceLowerLimitForMaximumVentingOpenFactor) {
    return getImpl<detail::AirflowNetworkMultiZoneZone_Impl>()->setIndoorandOutdoorTemperatureDifferenceLowerLimitForMaximumVentingOpenFactor(
      indoorandOutdoorTemperatureDifferenceLowerLimitForMaximumVentingOpenFactor);
  }

  void AirflowNetworkMultiZoneZone::resetIndoorandOutdoorTemperatureDifferenceLowerLimitForMaximumVentingOpenFactor() {
    getImpl<detail::AirflowNetworkMultiZoneZone_Impl>()->resetIndoorandOutdoorTemperatureDifferenceLowerLimitForMaximumVentingOpenFactor();
  }

  double AirflowNetworkMultiZoneZone::indoorandOutdoorTemperatureDifferenceUpperLimitforMinimumVentingOpenFactor() const {
    return getImpl<detail::AirflowNetworkMultiZoneZone_Impl>()->indoorandOutdoorTemperatureDifferenceUpperLimitforMinimumVentingOpenFactor();
  }

  bool AirflowNetworkMultiZoneZone::isIndoorandOutdoorTemperatureDifferenceUpperLimitforMinimumVentingOpenFactorDefaulted() const {
    return getImpl<detail::AirflowNetworkMultiZoneZone_Impl>()
      ->isIndoorandOutdoorTemperatureDifferenceUpperLimitforMinimumVentingOpenFactorDefaulted();
  }

  bool AirflowNetworkMultiZoneZone::setIndoorandOutdoorTemperatureDifferenceUpperLimitforMinimumVentingOpenFactor(
    double indoorandOutdoorTemperatureDifferenceUpperLimitforMinimumVentingOpenFactor) {
    return getImpl<detail::AirflowNetworkMultiZoneZone_Impl>()->setIndoorandOutdoorTemperatureDifferenceUpperLimitforMinimumVentingOpenFactor(
      indoorandOutdoorTemperatureDifferenceUpperLimitforMinimumVentingOpenFactor);
  }

  void AirflowNetworkMultiZoneZone::resetIndoorandOutdoorTemperatureDifferenceUpperLimitforMinimumVentingOpenFactor() {
    getImpl<detail::AirflowNetworkMultiZoneZone_Impl>()->resetIndoorandOutdoorTemperatureDifferenceUpperLimitforMinimumVentingOpenFactor();
  }

  double AirflowNetworkMultiZoneZone::indoorandOutdoorEnthalpyDifferenceLowerLimitForMaximumVentingOpenFactor() const {
    return getImpl<detail::AirflowNetworkMultiZoneZone_Impl>()->indoorandOutdoorEnthalpyDifferenceLowerLimitForMaximumVentingOpenFactor();
  }

  bool AirflowNetworkMultiZoneZone::isIndoorandOutdoorEnthalpyDifferenceLowerLimitForMaximumVentingOpenFactorDefaulted() const {
    return getImpl<detail::AirflowNetworkMultiZoneZone_Impl>()->isIndoorandOutdoorEnthalpyDifferenceLowerLimitForMaximumVentingOpenFactorDefaulted();
  }

  bool AirflowNetworkMultiZoneZone::setIndoorandOutdoorEnthalpyDifferenceLowerLimitForMaximumVentingOpenFactor(
    double indoorandOutdoorEnthalpyDifferenceLowerLimitForMaximumVentingOpenFactor) {
    return getImpl<detail::AirflowNetworkMultiZoneZone_Impl>()->setIndoorandOutdoorEnthalpyDifferenceLowerLimitForMaximumVentingOpenFactor(
      indoorandOutdoorEnthalpyDifferenceLowerLimitForMaximumVentingOpenFactor);
  }

  void AirflowNetworkMultiZoneZone::resetIndoorandOutdoorEnthalpyDifferenceLowerLimitForMaximumVentingOpenFactor() {
    getImpl<detail::AirflowNetworkMultiZoneZone_Impl>()->resetIndoorandOutdoorEnthalpyDifferenceLowerLimitForMaximumVentingOpenFactor();
  }

  double AirflowNetworkMultiZoneZone::indoorandOutdoorEnthalpyDifferenceUpperLimitforMinimumVentingOpenFactor() const {
    return getImpl<detail::AirflowNetworkMultiZoneZone_Impl>()->indoorandOutdoorEnthalpyDifferenceUpperLimitforMinimumVentingOpenFactor();
  }

  bool AirflowNetworkMultiZoneZone::isIndoorandOutdoorEnthalpyDifferenceUpperLimitforMinimumVentingOpenFactorDefaulted() const {
    return getImpl<detail::AirflowNetworkMultiZoneZone_Impl>()->isIndoorandOutdoorEnthalpyDifferenceUpperLimitforMinimumVentingOpenFactorDefaulted();
  }

  bool AirflowNetworkMultiZoneZone::setIndoorandOutdoorEnthalpyDifferenceUpperLimitforMinimumVentingOpenFactor(
    double indoorandOutdoorEnthalpyDifferenceUpperLimitforMinimumVentingOpenFactor) {
    return getImpl<detail::AirflowNetworkMultiZoneZone_Impl>()->setIndoorandOutdoorEnthalpyDifferenceUpperLimitforMinimumVentingOpenFactor(
      indoorandOutdoorEnthalpyDifferenceUpperLimitforMinimumVentingOpenFactor);
  }

  void AirflowNetworkMultiZoneZone::resetIndoorandOutdoorEnthalpyDifferenceUpperLimitforMinimumVentingOpenFactor() {
    getImpl<detail::AirflowNetworkMultiZoneZone_Impl>()->resetIndoorandOutdoorEnthalpyDifferenceUpperLimitforMinimumVentingOpenFactor();
  }

  std::string AirflowNetworkMultiZoneZone::singleSidedWindPressureCoefficientAlgorithm() const {
    return getImpl<detail::AirflowNetworkMultiZoneZone_Impl>()->singleSidedWindPressureCoefficientAlgorithm();
  }

  bool AirflowNetworkMultiZoneZone::isSingleSidedWindPressureCoefficientAlgorithmDefaulted() const {
    return getImpl<detail::AirflowNetworkMultiZoneZone_Impl>()->isSingleSidedWindPressureCoefficientAlgorithmDefaulted();
  }

  bool AirflowNetworkMultiZoneZone::setSingleSidedWindPressureCoefficientAlgorithm(const std::string& singleSidedWindPressureCoefficientAlgorithm) {
    return getImpl<detail::AirflowNetworkMultiZoneZone_Impl>()->setSingleSidedWindPressureCoefficientAlgorithm(
      singleSidedWindPressureCoefficientAlgorithm);
  }

  void AirflowNetworkMultiZoneZone::resetSingleSidedWindPressureCoefficientAlgorithm() {
    getImpl<detail::AirflowNetworkMultiZoneZone_Impl>()->resetSingleSidedWindPressureCoefficientAlgorithm();
  }

  double AirflowNetworkMultiZoneZone::facadeWidth() const {
    return getImpl<detail::AirflowNetworkMultiZoneZone_Impl>()->facadeWidth();
  }

  bool AirflowNetworkMultiZoneZone::isFacadeWidthDefaulted() const {
    return getImpl<detail::AirflowNetworkMultiZoneZone_Impl>()->isFacadeWidthDefaulted();
  }

  bool AirflowNetworkMultiZoneZone::setFacadeWidth(double facadeWidth) {
    return getImpl<detail::AirflowNetworkMultiZoneZone_Impl>()->setFacadeWidth(facadeWidth);
  }

  void AirflowNetworkMultiZoneZone::resetFacadeWidth() {
    getImpl<detail::AirflowNetworkMultiZoneZone_Impl>()->resetFacadeWidth();
  }

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
  namespace detail {

    std::string AirflowNetworkMultiZoneZone_Impl::ventilationControlMode() const {
      const auto value = getString(openstudio::AirflowNetwork_MultiZone_ZoneFields::VentilationControlMode, true);
      OS_ASSERT(value);
      return *value;
    }

    bool AirflowNetworkMultiZoneZone_Impl::isVentilationControlModeDefaulted() const {
      return isEmpty(openstudio::AirflowNetwork_MultiZone_ZoneFields::VentilationControlMode);
    }

    bool AirflowNetworkMultiZoneZone_Impl::setVentilationControlMode(const std::string& ventilationControlMode) {
      return setString(openstudio::AirflowNetwork_MultiZone_ZoneFields::VentilationControlMode, ventilationControlMode);
    }

    void AirflowNetworkMultiZoneZone_Impl::resetVentilationControlMode() {
      OS_ASSERT(setString(openstudio::AirflowNetwork_MultiZone_ZoneFields::VentilationControlMode, ""));
    }

    double AirflowNetworkMultiZoneZone_Impl::minimumVentingOpenFactor() const {
      const auto value = getDouble(openstudio::AirflowNetwork_MultiZone_ZoneFields::MinimumVentingOpenFactor, true);
      OS_ASSERT(value);
      return *value;
    }

    bool AirflowNetworkMultiZoneZone_Impl::isMinimumVentingOpenFactorDefaulted() const {
      return isEmpty(openstudio::AirflowNetwork_MultiZone_ZoneFields::MinimumVentingOpenFactor);
    }

    bool AirflowNetworkMultiZoneZone_Impl::setMinimumVentingOpenFactor(double minimumVentingOpenFactor) {
      return setDouble(openstudio::AirflowNetwork_MultiZone_ZoneFields::MinimumVentingOpenFactor, minimumVentingOpenFactor);
    }

    void AirflowNetworkMultiZoneZone_Impl::resetMinimumVentingOpenFactor() {
      OS_ASSERT(setString(openstudio::AirflowNetwork_MultiZone_ZoneFields::MinimumVentingOpenFactor, ""));
    }

    double AirflowNetworkMultiZoneZone_Impl::indoorandOutdoorTemperatureDifferenceLowerLimitForMaximumVentingOpenFactor() const {
      const auto value =
        getDouble(openstudio::AirflowNetwork_MultiZone_ZoneFields::IndoorandOutdoorTemperatureDifferenceLowerLimitForMaximumVentingOpenFactor, true);
      OS_ASSERT(value);
      return *value;
    }

    bool AirflowNetworkMultiZoneZone_Impl::isIndoorandOutdoorTemperatureDifferenceLowerLimitForMaximumVentingOpenFactorDefaulted() const {
      return isEmpty(openstudio::AirflowNetwork_MultiZone_ZoneFields::IndoorandOutdoorTemperatureDifferenceLowerLimitForMaximumVentingOpenFactor);
    }

    bool AirflowNetworkMultiZoneZone_Impl::setIndoorandOutdoorTemperatureDifferenceLowerLimitForMaximumVentingOpenFactor(
      double indoorandOutdoorTemperatureDifferenceLowerLimitForMaximumVentingOpenFactor) {
      return setDouble(openstudio::AirflowNetwork_MultiZone_ZoneFields::IndoorandOutdoorTemperatureDifferenceLowerLimitForMaximumVentingOpenFactor,
                       indoorandOutdoorTemperatureDifferenceLowerLimitForMaximumVentingOpenFactor);
    }

    void AirflowNetworkMultiZoneZone_Impl::resetIndoorandOutdoorTemperatureDifferenceLowerLimitForMaximumVentingOpenFactor() {
      OS_ASSERT(
        setString(openstudio::AirflowNetwork_MultiZone_ZoneFields::IndoorandOutdoorTemperatureDifferenceLowerLimitForMaximumVentingOpenFactor, ""));
    }

    double AirflowNetworkMultiZoneZone_Impl::indoorandOutdoorTemperatureDifferenceUpperLimitforMinimumVentingOpenFactor() const {
      const auto value =
        getDouble(openstudio::AirflowNetwork_MultiZone_ZoneFields::IndoorandOutdoorTemperatureDifferenceUpperLimitforMinimumVentingOpenFactor, true);
      OS_ASSERT(value);
      return *value;
    }

    bool AirflowNetworkMultiZoneZone_Impl::isIndoorandOutdoorTemperatureDifferenceUpperLimitforMinimumVentingOpenFactorDefaulted() const {
      return isEmpty(openstudio::AirflowNetwork_MultiZone_ZoneFields::IndoorandOutdoorTemperatureDifferenceUpperLimitforMinimumVentingOpenFactor);
    }

    bool AirflowNetworkMultiZoneZone_Impl::setIndoorandOutdoorTemperatureDifferenceUpperLimitforMinimumVentingOpenFactor(
      double indoorandOutdoorTemperatureDifferenceUpperLimitforMinimumVentingOpenFactor) {
      return setDouble(openstudio::AirflowNetwork_MultiZone_ZoneFields::IndoorandOutdoorTemperatureDifferenceUpperLimitforMinimumVentingOpenFactor,
                       indoorandOutdoorTemperatureDifferenceUpperLimitforMinimumVentingOpenFactor);
    }

    void AirflowNetworkMultiZoneZone_Impl::resetIndoorandOutdoorTemperatureDifferenceUpperLimitforMinimumVentingOpenFactor() {
      OS_ASSERT(
        setString(openstudio::AirflowNetwork_MultiZone_ZoneFields::IndoorandOutdoorTemperatureDifferenceUpperLimitforMinimumVentingOpenFactor, ""));
    }

    double AirflowNetworkMultiZoneZone_Impl::indoorandOutdoorEnthalpyDifferenceLowerLimitForMaximumVentingOpenFactor() const {
      const auto value =
        getDouble(openstudio::AirflowNetwork_MultiZone_ZoneFields::IndoorandOutdoorEnthalpyDifferenceLowerLimitForMaximumVentingOpenFactor, true);
      OS_ASSERT(value);
      return *value;
    }

    bool AirflowNetworkMultiZoneZone_Impl::isIndoorandOutdoorEnthalpyDifferenceLowerLimitForMaximumVentingOpenFactorDefaulted() const {
      return isEmpty(openstudio::AirflowNetwork_MultiZone_ZoneFields::IndoorandOutdoorEnthalpyDifferenceLowerLimitForMaximumVentingOpenFactor);
    }

    bool AirflowNetworkMultiZoneZone_Impl::setIndoorandOutdoorEnthalpyDifferenceLowerLimitForMaximumVentingOpenFactor(
      double indoorandOutdoorEnthalpyDifferenceLowerLimitForMaximumVentingOpenFactor) {
      return setDouble(openstudio::AirflowNetwork_MultiZone_ZoneFields::IndoorandOutdoorEnthalpyDifferenceLowerLimitForMaximumVentingOpenFactor,
                       indoorandOutdoorEnthalpyDifferenceLowerLimitForMaximumVentingOpenFactor);
    }

    void AirflowNetworkMultiZoneZone_Impl::resetIndoorandOutdoorEnthalpyDifferenceLowerLimitForMaximumVentingOpenFactor() {
      OS_ASSERT(
        setString(openstudio::AirflowNetwork_MultiZone_ZoneFields::IndoorandOutdoorEnthalpyDifferenceLowerLimitForMaximumVentingOpenFactor, ""));
    }

    double AirflowNetworkMultiZoneZone_Impl::indoorandOutdoorEnthalpyDifferenceUpperLimitforMinimumVentingOpenFactor() const {
      const auto value =
        getDouble(openstudio::AirflowNetwork_MultiZone_ZoneFields::IndoorandOutdoorEnthalpyDifferenceUpperLimitforMinimumVentingOpenFactor, true);
      OS_ASSERT(value);
      return *value;
    }

    bool AirflowNetworkMultiZoneZone_Impl::isIndoorandOutdoorEnthalpyDifferenceUpperLimitforMinimumVentingOpenFactorDefaulted() const {
      return isEmpty(openstudio::AirflowNetwork_MultiZone_ZoneFields::IndoorandOutdoorEnthalpyDifferenceUpperLimitforMinimumVentingOpenFactor);
    }

    bool AirflowNetworkMultiZoneZone_Impl::setIndoorandOutdoorEnthalpyDifferenceUpperLimitforMinimumVentingOpenFactor(
      double indoorandOutdoorEnthalpyDifferenceUpperLimitforMinimumVentingOpenFactor) {
      return setDouble(openstudio::AirflowNetwork_MultiZone_ZoneFields::IndoorandOutdoorEnthalpyDifferenceUpperLimitforMinimumVentingOpenFactor,
                       indoorandOutdoorEnthalpyDifferenceUpperLimitforMinimumVentingOpenFactor);
    }

    void AirflowNetworkMultiZoneZone_Impl::resetIndoorandOutdoorEnthalpyDifferenceUpperLimitforMinimumVentingOpenFactor() {
      OS_ASSERT(
        setString(openstudio::AirflowNetwork_MultiZone_ZoneFields::IndoorandOutdoorEnthalpyDifferenceUpperLimitforMinimumVentingOpenFactor, ""));
    }

    std::string AirflowNetworkMultiZoneZone_Impl::singleSidedWindPressureCoefficientAlgorithm() const {
      const auto value = getString(openstudio::AirflowNetwork_MultiZone_ZoneFields::SingleSidedWindPressureCoefficientAlgorithm, true);
      OS_ASSERT(value);
      return *value;
    }

    bool AirflowNetworkMultiZoneZone_Impl::isSingleSidedWindPressureCoefficientAlgorithmDefaulted() const {
      return isEmpty(openstudio::AirflowNetwork_MultiZone_ZoneFields::SingleSidedWindPressureCoefficientAlgorithm);
    }

    bool AirflowNetworkMultiZoneZone_Impl::setSingleSidedWindPressureCoefficientAlgorithm(
      const std::string& singleSidedWindPressureCoefficientAlgorithm) {
      return setString(openstudio::AirflowNetwork_MultiZone_ZoneFields::SingleSidedWindPressureCoefficientAlgorithm,
                       singleSidedWindPressureCoefficientAlgorithm);
    }

    void AirflowNetworkMultiZoneZone_Impl::resetSingleSidedWindPressureCoefficientAlgorithm() {
      OS_ASSERT(setString(openstudio::AirflowNetwork_MultiZone_ZoneFields::SingleSidedWindPressureCoefficientAlgorithm, ""));
    }

    double AirflowNetworkMultiZoneZone_Impl::facadeWidth() const {
      const auto value = getDouble(openstudio::AirflowNetwork_MultiZone_ZoneFields::FacadeWidth, true);
      OS_ASSERT(value);
      return *value;
    }

    bool AirflowNetworkMultiZoneZone_Impl::isFacadeWidthDefaulted() const {
      return isEmpty(openstudio::AirflowNetwork_MultiZone_ZoneFields::FacadeWidth);
    }

    bool AirflowNetworkMultiZoneZone_Impl::setFacadeWidth(double facadeWidth) {
      return setDouble(openstudio::AirflowNetwork_MultiZone_ZoneFields::FacadeWidth, facadeWidth);
    }

    void AirflowNetworkMultiZoneZone_Impl::resetFacadeWidth() {
      OS_ASSERT(setString(openstudio::AirflowNetwork_MultiZone_ZoneFields::FacadeWidth, ""));
    }

    std::vector<std::string> AirflowNetworkMultiZoneZone_Impl::ventilationControlModeValues() const {
      return openstudio::epmodel::AirflowNetworkMultiZoneZone::ventilationControlModeValues();
    }

    std::vector<std::string> AirflowNetworkMultiZoneZone_Impl::singleSidedWindPressureCoefficientAlgorithmValues() const {
      return openstudio::epmodel::AirflowNetworkMultiZoneZone::singleSidedWindPressureCoefficientAlgorithmValues();
    }

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
