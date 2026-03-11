/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "ThermalStorageChilledWaterMixed.hpp"
#include "ThermalStorageChilledWaterMixed_Impl.hpp"

#include "Model.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/core/StringHelpers.hpp>
#include <utilities/idd/ThermalStorage_ChilledWater_Mixed_FieldEnums.hxx>
#include <utilities/idd/IddEnums.hxx>
#include <utilities/idd/IddFactory.hxx>
#include <utilities/idd/IddObject.hpp>

namespace openstudio {
namespace epmodel {

  ThermalStorageChilledWaterMixed::ThermalStorageChilledWaterMixed(const Model& model)
    : ModelObject(ThermalStorageChilledWaterMixed::iddObjectType(), model) {}

  ThermalStorageChilledWaterMixed::ThermalStorageChilledWaterMixed(std::shared_ptr<detail::ThermalStorageChilledWaterMixed_Impl> impl)
    : ModelObject(std::move(impl)) {}

  IddObjectType ThermalStorageChilledWaterMixed::iddObjectType() {
    return IddObjectType::ThermalStorage_ChilledWater_Mixed;
  }

  std::vector<std::string> ThermalStorageChilledWaterMixed::ambientTemperatureIndicatorValues() {
    return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(),
                          openstudio::ThermalStorage_ChilledWater_MixedFields::AmbientTemperatureIndicator);
  }

  double ThermalStorageChilledWaterMixed::tankVolume() const {
    return getImpl<detail::ThermalStorageChilledWaterMixed_Impl>()->tankVolume();
  }

  bool ThermalStorageChilledWaterMixed::setTankVolume(double tankVolume) {
    return getImpl<detail::ThermalStorageChilledWaterMixed_Impl>()->setTankVolume(tankVolume);
  }

  bool ThermalStorageChilledWaterMixed::isTankVolumeDefaulted() const {
    return getImpl<detail::ThermalStorageChilledWaterMixed_Impl>()->isTankVolumeDefaulted();
  }

  void ThermalStorageChilledWaterMixed::resetTankVolume() {
    getImpl<detail::ThermalStorageChilledWaterMixed_Impl>()->resetTankVolume();
  }

  double ThermalStorageChilledWaterMixed::deadbandTemperatureDifference() const {
    return getImpl<detail::ThermalStorageChilledWaterMixed_Impl>()->deadbandTemperatureDifference();
  }

  bool ThermalStorageChilledWaterMixed::setDeadbandTemperatureDifference(double deadbandTemperatureDifference) {
    return getImpl<detail::ThermalStorageChilledWaterMixed_Impl>()->setDeadbandTemperatureDifference(deadbandTemperatureDifference);
  }

  bool ThermalStorageChilledWaterMixed::isDeadbandTemperatureDifferenceDefaulted() const {
    return getImpl<detail::ThermalStorageChilledWaterMixed_Impl>()->isDeadbandTemperatureDifferenceDefaulted();
  }

  void ThermalStorageChilledWaterMixed::resetDeadbandTemperatureDifference() {
    getImpl<detail::ThermalStorageChilledWaterMixed_Impl>()->resetDeadbandTemperatureDifference();
  }

  boost::optional<double> ThermalStorageChilledWaterMixed::minimumTemperatureLimit() const {
    return getImpl<detail::ThermalStorageChilledWaterMixed_Impl>()->minimumTemperatureLimit();
  }

  bool ThermalStorageChilledWaterMixed::setMinimumTemperatureLimit(double minimumTemperatureLimit) {
    return getImpl<detail::ThermalStorageChilledWaterMixed_Impl>()->setMinimumTemperatureLimit(minimumTemperatureLimit);
  }

  void ThermalStorageChilledWaterMixed::resetMinimumTemperatureLimit() {
    getImpl<detail::ThermalStorageChilledWaterMixed_Impl>()->resetMinimumTemperatureLimit();
  }

  boost::optional<double> ThermalStorageChilledWaterMixed::nominalCoolingCapacity() const {
    return getImpl<detail::ThermalStorageChilledWaterMixed_Impl>()->nominalCoolingCapacity();
  }

  bool ThermalStorageChilledWaterMixed::setNominalCoolingCapacity(double nominalCoolingCapacity) {
    return getImpl<detail::ThermalStorageChilledWaterMixed_Impl>()->setNominalCoolingCapacity(nominalCoolingCapacity);
  }

  void ThermalStorageChilledWaterMixed::resetNominalCoolingCapacity() {
    getImpl<detail::ThermalStorageChilledWaterMixed_Impl>()->resetNominalCoolingCapacity();
  }

  std::string ThermalStorageChilledWaterMixed::ambientTemperatureIndicator() const {
    return getImpl<detail::ThermalStorageChilledWaterMixed_Impl>()->ambientTemperatureIndicator();
  }

  bool ThermalStorageChilledWaterMixed::setAmbientTemperatureIndicator(const std::string& ambientTemperatureIndicator) {
    return getImpl<detail::ThermalStorageChilledWaterMixed_Impl>()->setAmbientTemperatureIndicator(ambientTemperatureIndicator);
  }

  boost::optional<double> ThermalStorageChilledWaterMixed::heatGainCoefficientFromAmbientTemperature() const {
    return getImpl<detail::ThermalStorageChilledWaterMixed_Impl>()->heatGainCoefficientFromAmbientTemperature();
  }

  bool ThermalStorageChilledWaterMixed::setHeatGainCoefficientFromAmbientTemperature(double heatGainCoefficientFromAmbientTemperature) {
    return getImpl<detail::ThermalStorageChilledWaterMixed_Impl>()->setHeatGainCoefficientFromAmbientTemperature(
      heatGainCoefficientFromAmbientTemperature);
  }

  void ThermalStorageChilledWaterMixed::resetHeatGainCoefficientFromAmbientTemperature() {
    getImpl<detail::ThermalStorageChilledWaterMixed_Impl>()->resetHeatGainCoefficientFromAmbientTemperature();
  }

  double ThermalStorageChilledWaterMixed::useSideHeatTransferEffectiveness() const {
    return getImpl<detail::ThermalStorageChilledWaterMixed_Impl>()->useSideHeatTransferEffectiveness();
  }

  bool ThermalStorageChilledWaterMixed::setUseSideHeatTransferEffectiveness(double useSideHeatTransferEffectiveness) {
    return getImpl<detail::ThermalStorageChilledWaterMixed_Impl>()->setUseSideHeatTransferEffectiveness(useSideHeatTransferEffectiveness);
  }

  bool ThermalStorageChilledWaterMixed::isUseSideHeatTransferEffectivenessDefaulted() const {
    return getImpl<detail::ThermalStorageChilledWaterMixed_Impl>()->isUseSideHeatTransferEffectivenessDefaulted();
  }

  void ThermalStorageChilledWaterMixed::resetUseSideHeatTransferEffectiveness() {
    getImpl<detail::ThermalStorageChilledWaterMixed_Impl>()->resetUseSideHeatTransferEffectiveness();
  }

  boost::optional<double> ThermalStorageChilledWaterMixed::useSideDesignFlowRate() const {
    return getImpl<detail::ThermalStorageChilledWaterMixed_Impl>()->useSideDesignFlowRate();
  }

  bool ThermalStorageChilledWaterMixed::setUseSideDesignFlowRate(double useSideDesignFlowRate) {
    return getImpl<detail::ThermalStorageChilledWaterMixed_Impl>()->setUseSideDesignFlowRate(useSideDesignFlowRate);
  }

  bool ThermalStorageChilledWaterMixed::isUseSideDesignFlowRateDefaulted() const {
    return getImpl<detail::ThermalStorageChilledWaterMixed_Impl>()->isUseSideDesignFlowRateDefaulted();
  }

  bool ThermalStorageChilledWaterMixed::isUseSideDesignFlowRateAutosized() const {
    return getImpl<detail::ThermalStorageChilledWaterMixed_Impl>()->isUseSideDesignFlowRateAutosized();
  }

  void ThermalStorageChilledWaterMixed::resetUseSideDesignFlowRate() {
    getImpl<detail::ThermalStorageChilledWaterMixed_Impl>()->resetUseSideDesignFlowRate();
  }

  void ThermalStorageChilledWaterMixed::autosizeUseSideDesignFlowRate() {
    getImpl<detail::ThermalStorageChilledWaterMixed_Impl>()->autosizeUseSideDesignFlowRate();
  }

  double ThermalStorageChilledWaterMixed::sourceSideHeatTransferEffectiveness() const {
    return getImpl<detail::ThermalStorageChilledWaterMixed_Impl>()->sourceSideHeatTransferEffectiveness();
  }

  bool ThermalStorageChilledWaterMixed::setSourceSideHeatTransferEffectiveness(double sourceSideHeatTransferEffectiveness) {
    return getImpl<detail::ThermalStorageChilledWaterMixed_Impl>()->setSourceSideHeatTransferEffectiveness(sourceSideHeatTransferEffectiveness);
  }

  bool ThermalStorageChilledWaterMixed::isSourceSideHeatTransferEffectivenessDefaulted() const {
    return getImpl<detail::ThermalStorageChilledWaterMixed_Impl>()->isSourceSideHeatTransferEffectivenessDefaulted();
  }

  void ThermalStorageChilledWaterMixed::resetSourceSideHeatTransferEffectiveness() {
    getImpl<detail::ThermalStorageChilledWaterMixed_Impl>()->resetSourceSideHeatTransferEffectiveness();
  }

  boost::optional<double> ThermalStorageChilledWaterMixed::sourceSideDesignFlowRate() const {
    return getImpl<detail::ThermalStorageChilledWaterMixed_Impl>()->sourceSideDesignFlowRate();
  }

  bool ThermalStorageChilledWaterMixed::setSourceSideDesignFlowRate(double sourceSideDesignFlowRate) {
    return getImpl<detail::ThermalStorageChilledWaterMixed_Impl>()->setSourceSideDesignFlowRate(sourceSideDesignFlowRate);
  }

  bool ThermalStorageChilledWaterMixed::isSourceSideDesignFlowRateDefaulted() const {
    return getImpl<detail::ThermalStorageChilledWaterMixed_Impl>()->isSourceSideDesignFlowRateDefaulted();
  }

  bool ThermalStorageChilledWaterMixed::isSourceSideDesignFlowRateAutosized() const {
    return getImpl<detail::ThermalStorageChilledWaterMixed_Impl>()->isSourceSideDesignFlowRateAutosized();
  }

  void ThermalStorageChilledWaterMixed::resetSourceSideDesignFlowRate() {
    getImpl<detail::ThermalStorageChilledWaterMixed_Impl>()->resetSourceSideDesignFlowRate();
  }

  void ThermalStorageChilledWaterMixed::autosizeSourceSideDesignFlowRate() {
    getImpl<detail::ThermalStorageChilledWaterMixed_Impl>()->autosizeSourceSideDesignFlowRate();
  }

  double ThermalStorageChilledWaterMixed::tankRecoveryTime() const {
    return getImpl<detail::ThermalStorageChilledWaterMixed_Impl>()->tankRecoveryTime();
  }

  bool ThermalStorageChilledWaterMixed::setTankRecoveryTime(double tankRecoveryTime) {
    return getImpl<detail::ThermalStorageChilledWaterMixed_Impl>()->setTankRecoveryTime(tankRecoveryTime);
  }

  bool ThermalStorageChilledWaterMixed::isTankRecoveryTimeDefaulted() const {
    return getImpl<detail::ThermalStorageChilledWaterMixed_Impl>()->isTankRecoveryTimeDefaulted();
  }

  void ThermalStorageChilledWaterMixed::resetTankRecoveryTime() {
    getImpl<detail::ThermalStorageChilledWaterMixed_Impl>()->resetTankRecoveryTime();
  }

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
  namespace detail {

    double ThermalStorageChilledWaterMixed_Impl::tankVolume() const {
      const auto value = getDouble(openstudio::ThermalStorage_ChilledWater_MixedFields::TankVolume, true);
      OS_ASSERT(value);
      return *value;
    }

    bool ThermalStorageChilledWaterMixed_Impl::setTankVolume(double tankVolume) {
      return setDouble(openstudio::ThermalStorage_ChilledWater_MixedFields::TankVolume, tankVolume);
    }

    bool ThermalStorageChilledWaterMixed_Impl::isTankVolumeDefaulted() const {
      return isEmpty(openstudio::ThermalStorage_ChilledWater_MixedFields::TankVolume);
    }

    void ThermalStorageChilledWaterMixed_Impl::resetTankVolume() {
      OS_ASSERT(setString(openstudio::ThermalStorage_ChilledWater_MixedFields::TankVolume, ""));
    }

    double ThermalStorageChilledWaterMixed_Impl::deadbandTemperatureDifference() const {
      const auto value = getDouble(openstudio::ThermalStorage_ChilledWater_MixedFields::DeadbandTemperatureDifference, true);
      OS_ASSERT(value);
      return *value;
    }

    bool ThermalStorageChilledWaterMixed_Impl::setDeadbandTemperatureDifference(double deadbandTemperatureDifference) {
      return setDouble(openstudio::ThermalStorage_ChilledWater_MixedFields::DeadbandTemperatureDifference, deadbandTemperatureDifference);
    }

    bool ThermalStorageChilledWaterMixed_Impl::isDeadbandTemperatureDifferenceDefaulted() const {
      return isEmpty(openstudio::ThermalStorage_ChilledWater_MixedFields::DeadbandTemperatureDifference);
    }

    void ThermalStorageChilledWaterMixed_Impl::resetDeadbandTemperatureDifference() {
      OS_ASSERT(setString(openstudio::ThermalStorage_ChilledWater_MixedFields::DeadbandTemperatureDifference, ""));
    }

    boost::optional<double> ThermalStorageChilledWaterMixed_Impl::minimumTemperatureLimit() const {
      return getDouble(openstudio::ThermalStorage_ChilledWater_MixedFields::MinimumTemperatureLimit, true);
    }

    bool ThermalStorageChilledWaterMixed_Impl::setMinimumTemperatureLimit(double minimumTemperatureLimit) {
      const bool result = setDouble(openstudio::ThermalStorage_ChilledWater_MixedFields::MinimumTemperatureLimit, minimumTemperatureLimit);
      OS_ASSERT(result);
      return result;
    }

    void ThermalStorageChilledWaterMixed_Impl::resetMinimumTemperatureLimit() {
      OS_ASSERT(setString(openstudio::ThermalStorage_ChilledWater_MixedFields::MinimumTemperatureLimit, ""));
    }

    boost::optional<double> ThermalStorageChilledWaterMixed_Impl::nominalCoolingCapacity() const {
      return getDouble(openstudio::ThermalStorage_ChilledWater_MixedFields::NominalCoolingCapacity, true);
    }

    bool ThermalStorageChilledWaterMixed_Impl::setNominalCoolingCapacity(double nominalCoolingCapacity) {
      const bool result = setDouble(openstudio::ThermalStorage_ChilledWater_MixedFields::NominalCoolingCapacity, nominalCoolingCapacity);
      OS_ASSERT(result);
      return result;
    }

    void ThermalStorageChilledWaterMixed_Impl::resetNominalCoolingCapacity() {
      OS_ASSERT(setString(openstudio::ThermalStorage_ChilledWater_MixedFields::NominalCoolingCapacity, ""));
    }

    std::string ThermalStorageChilledWaterMixed_Impl::ambientTemperatureIndicator() const {
      const auto value = getString(openstudio::ThermalStorage_ChilledWater_MixedFields::AmbientTemperatureIndicator, true);
      OS_ASSERT(value);
      return *value;
    }

    bool ThermalStorageChilledWaterMixed_Impl::setAmbientTemperatureIndicator(const std::string& ambientTemperatureIndicator) {
      return setString(openstudio::ThermalStorage_ChilledWater_MixedFields::AmbientTemperatureIndicator, ambientTemperatureIndicator);
    }

    boost::optional<double> ThermalStorageChilledWaterMixed_Impl::heatGainCoefficientFromAmbientTemperature() const {
      return getDouble(openstudio::ThermalStorage_ChilledWater_MixedFields::HeatGainCoefficientfromAmbientTemperature, true);
    }

    bool ThermalStorageChilledWaterMixed_Impl::setHeatGainCoefficientFromAmbientTemperature(double heatGainCoefficientFromAmbientTemperature) {
      return setDouble(openstudio::ThermalStorage_ChilledWater_MixedFields::HeatGainCoefficientfromAmbientTemperature,
                       heatGainCoefficientFromAmbientTemperature);
    }

    void ThermalStorageChilledWaterMixed_Impl::resetHeatGainCoefficientFromAmbientTemperature() {
      OS_ASSERT(setString(openstudio::ThermalStorage_ChilledWater_MixedFields::HeatGainCoefficientfromAmbientTemperature, ""));
    }

    double ThermalStorageChilledWaterMixed_Impl::useSideHeatTransferEffectiveness() const {
      const auto value = getDouble(openstudio::ThermalStorage_ChilledWater_MixedFields::UseSideHeatTransferEffectiveness, true);
      OS_ASSERT(value);
      return *value;
    }

    bool ThermalStorageChilledWaterMixed_Impl::setUseSideHeatTransferEffectiveness(double useSideHeatTransferEffectiveness) {
      return setDouble(openstudio::ThermalStorage_ChilledWater_MixedFields::UseSideHeatTransferEffectiveness, useSideHeatTransferEffectiveness);
    }

    bool ThermalStorageChilledWaterMixed_Impl::isUseSideHeatTransferEffectivenessDefaulted() const {
      return isEmpty(openstudio::ThermalStorage_ChilledWater_MixedFields::UseSideHeatTransferEffectiveness);
    }

    void ThermalStorageChilledWaterMixed_Impl::resetUseSideHeatTransferEffectiveness() {
      OS_ASSERT(setString(openstudio::ThermalStorage_ChilledWater_MixedFields::UseSideHeatTransferEffectiveness, ""));
    }

    boost::optional<double> ThermalStorageChilledWaterMixed_Impl::useSideDesignFlowRate() const {
      return getDouble(openstudio::ThermalStorage_ChilledWater_MixedFields::UseSideDesignFlowRate, true);
    }

    bool ThermalStorageChilledWaterMixed_Impl::setUseSideDesignFlowRate(double useSideDesignFlowRate) {
      return setDouble(openstudio::ThermalStorage_ChilledWater_MixedFields::UseSideDesignFlowRate, useSideDesignFlowRate);
    }

    bool ThermalStorageChilledWaterMixed_Impl::isUseSideDesignFlowRateDefaulted() const {
      return isEmpty(openstudio::ThermalStorage_ChilledWater_MixedFields::UseSideDesignFlowRate);
    }

    bool ThermalStorageChilledWaterMixed_Impl::isUseSideDesignFlowRateAutosized() const {
      if (auto value = getString(openstudio::ThermalStorage_ChilledWater_MixedFields::UseSideDesignFlowRate, true)) {
        return istringEqual(*value, "autosize");
      }
      return false;
    }

    void ThermalStorageChilledWaterMixed_Impl::resetUseSideDesignFlowRate() {
      OS_ASSERT(setString(openstudio::ThermalStorage_ChilledWater_MixedFields::UseSideDesignFlowRate, ""));
    }

    void ThermalStorageChilledWaterMixed_Impl::autosizeUseSideDesignFlowRate() {
      OS_ASSERT(setString(openstudio::ThermalStorage_ChilledWater_MixedFields::UseSideDesignFlowRate, "autosize"));
    }

    double ThermalStorageChilledWaterMixed_Impl::sourceSideHeatTransferEffectiveness() const {
      const auto value = getDouble(openstudio::ThermalStorage_ChilledWater_MixedFields::SourceSideHeatTransferEffectiveness, true);
      OS_ASSERT(value);
      return *value;
    }

    bool ThermalStorageChilledWaterMixed_Impl::setSourceSideHeatTransferEffectiveness(double sourceSideHeatTransferEffectiveness) {
      return setDouble(openstudio::ThermalStorage_ChilledWater_MixedFields::SourceSideHeatTransferEffectiveness, sourceSideHeatTransferEffectiveness);
    }

    bool ThermalStorageChilledWaterMixed_Impl::isSourceSideHeatTransferEffectivenessDefaulted() const {
      return isEmpty(openstudio::ThermalStorage_ChilledWater_MixedFields::SourceSideHeatTransferEffectiveness);
    }

    void ThermalStorageChilledWaterMixed_Impl::resetSourceSideHeatTransferEffectiveness() {
      OS_ASSERT(setString(openstudio::ThermalStorage_ChilledWater_MixedFields::SourceSideHeatTransferEffectiveness, ""));
    }

    boost::optional<double> ThermalStorageChilledWaterMixed_Impl::sourceSideDesignFlowRate() const {
      return getDouble(openstudio::ThermalStorage_ChilledWater_MixedFields::SourceSideDesignFlowRate, true);
    }

    bool ThermalStorageChilledWaterMixed_Impl::setSourceSideDesignFlowRate(double sourceSideDesignFlowRate) {
      return setDouble(openstudio::ThermalStorage_ChilledWater_MixedFields::SourceSideDesignFlowRate, sourceSideDesignFlowRate);
    }

    bool ThermalStorageChilledWaterMixed_Impl::isSourceSideDesignFlowRateDefaulted() const {
      return isEmpty(openstudio::ThermalStorage_ChilledWater_MixedFields::SourceSideDesignFlowRate);
    }

    bool ThermalStorageChilledWaterMixed_Impl::isSourceSideDesignFlowRateAutosized() const {
      if (auto value = getString(openstudio::ThermalStorage_ChilledWater_MixedFields::SourceSideDesignFlowRate, true)) {
        return istringEqual(*value, "autosize");
      }
      return false;
    }

    void ThermalStorageChilledWaterMixed_Impl::resetSourceSideDesignFlowRate() {
      OS_ASSERT(setString(openstudio::ThermalStorage_ChilledWater_MixedFields::SourceSideDesignFlowRate, ""));
    }

    void ThermalStorageChilledWaterMixed_Impl::autosizeSourceSideDesignFlowRate() {
      OS_ASSERT(setString(openstudio::ThermalStorage_ChilledWater_MixedFields::SourceSideDesignFlowRate, "autosize"));
    }

    double ThermalStorageChilledWaterMixed_Impl::tankRecoveryTime() const {
      const auto value = getDouble(openstudio::ThermalStorage_ChilledWater_MixedFields::TankRecoveryTime, true);
      OS_ASSERT(value);
      return *value;
    }

    bool ThermalStorageChilledWaterMixed_Impl::setTankRecoveryTime(double tankRecoveryTime) {
      return setDouble(openstudio::ThermalStorage_ChilledWater_MixedFields::TankRecoveryTime, tankRecoveryTime);
    }

    bool ThermalStorageChilledWaterMixed_Impl::isTankRecoveryTimeDefaulted() const {
      return isEmpty(openstudio::ThermalStorage_ChilledWater_MixedFields::TankRecoveryTime);
    }

    void ThermalStorageChilledWaterMixed_Impl::resetTankRecoveryTime() {
      OS_ASSERT(setString(openstudio::ThermalStorage_ChilledWater_MixedFields::TankRecoveryTime, ""));
    }

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
