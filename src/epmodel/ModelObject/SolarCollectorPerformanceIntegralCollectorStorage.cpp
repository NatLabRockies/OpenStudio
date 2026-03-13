/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "SolarCollectorPerformanceIntegralCollectorStorage.hpp"
#include "SolarCollectorPerformanceIntegralCollectorStorage_Impl.hpp"

#include "Model.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/idd/IddEnums.hxx>
#include <utilities/idd/IddFactory.hxx>
#include <utilities/idd/IddObject.hpp>
#include <utilities/idd/SolarCollectorPerformance_IntegralCollectorStorage_FieldEnums.hxx>

namespace openstudio {
namespace epmodel {

  SolarCollectorPerformanceIntegralCollectorStorage::SolarCollectorPerformanceIntegralCollectorStorage(const Model& model)
    : ModelObject(SolarCollectorPerformanceIntegralCollectorStorage::iddObjectType(), model) {
    OS_ASSERT(getImpl<detail::SolarCollectorPerformanceIntegralCollectorStorage_Impl>());

    // Preserve existing model counterpart non-IDD defaults.
    bool ok = true;
    ok = setGrossArea(2.9800);
    OS_ASSERT(ok);
    ok = setCollectorWaterVolume(0.1862);
    OS_ASSERT(ok);
  }

  SolarCollectorPerformanceIntegralCollectorStorage::SolarCollectorPerformanceIntegralCollectorStorage(
    std::shared_ptr<detail::SolarCollectorPerformanceIntegralCollectorStorage_Impl> impl)
    : ModelObject(std::move(impl)) {}

  IddObjectType SolarCollectorPerformanceIntegralCollectorStorage::iddObjectType() {
    return IddObjectType::SolarCollectorPerformance_IntegralCollectorStorage;
  }

  std::vector<std::string> SolarCollectorPerformanceIntegralCollectorStorage::iCSCollectorTypeValues() {
    return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(),
                          openstudio::SolarCollectorPerformance_IntegralCollectorStorageFields::ICSCollectorType);
  }

  std::string SolarCollectorPerformanceIntegralCollectorStorage::iCSCollectorType() const {
    return getImpl<detail::SolarCollectorPerformanceIntegralCollectorStorage_Impl>()->iCSCollectorType();
  }

  bool SolarCollectorPerformanceIntegralCollectorStorage::isICSCollectorTypeDefaulted() const {
    return getImpl<detail::SolarCollectorPerformanceIntegralCollectorStorage_Impl>()->isICSCollectorTypeDefaulted();
  }

  bool SolarCollectorPerformanceIntegralCollectorStorage::setICSCollectorType(const std::string& iCSCollectorType) {
    return getImpl<detail::SolarCollectorPerformanceIntegralCollectorStorage_Impl>()->setICSCollectorType(iCSCollectorType);
  }

  void SolarCollectorPerformanceIntegralCollectorStorage::resetICSCollectorType() {
    getImpl<detail::SolarCollectorPerformanceIntegralCollectorStorage_Impl>()->resetICSCollectorType();
  }

  double SolarCollectorPerformanceIntegralCollectorStorage::grossArea() const {
    return getImpl<detail::SolarCollectorPerformanceIntegralCollectorStorage_Impl>()->grossArea();
  }

  bool SolarCollectorPerformanceIntegralCollectorStorage::setGrossArea(double grossArea) {
    return getImpl<detail::SolarCollectorPerformanceIntegralCollectorStorage_Impl>()->setGrossArea(grossArea);
  }

  double SolarCollectorPerformanceIntegralCollectorStorage::collectorWaterVolume() const {
    return getImpl<detail::SolarCollectorPerformanceIntegralCollectorStorage_Impl>()->collectorWaterVolume();
  }

  bool SolarCollectorPerformanceIntegralCollectorStorage::setCollectorWaterVolume(double collectorWaterVolume) {
    return getImpl<detail::SolarCollectorPerformanceIntegralCollectorStorage_Impl>()->setCollectorWaterVolume(collectorWaterVolume);
  }

  double SolarCollectorPerformanceIntegralCollectorStorage::bottomHeatLossConductance() const {
    return getImpl<detail::SolarCollectorPerformanceIntegralCollectorStorage_Impl>()->bottomHeatLossConductance();
  }

  bool SolarCollectorPerformanceIntegralCollectorStorage::isBottomHeatLossConductanceDefaulted() const {
    return getImpl<detail::SolarCollectorPerformanceIntegralCollectorStorage_Impl>()->isBottomHeatLossConductanceDefaulted();
  }

  bool SolarCollectorPerformanceIntegralCollectorStorage::setBottomHeatLossConductance(double bottomHeatLossConductance) {
    return getImpl<detail::SolarCollectorPerformanceIntegralCollectorStorage_Impl>()->setBottomHeatLossConductance(bottomHeatLossConductance);
  }

  void SolarCollectorPerformanceIntegralCollectorStorage::resetBottomHeatLossConductance() {
    getImpl<detail::SolarCollectorPerformanceIntegralCollectorStorage_Impl>()->resetBottomHeatLossConductance();
  }

  double SolarCollectorPerformanceIntegralCollectorStorage::sideHeatLossConductance() const {
    return getImpl<detail::SolarCollectorPerformanceIntegralCollectorStorage_Impl>()->sideHeatLossConductance();
  }

  bool SolarCollectorPerformanceIntegralCollectorStorage::isSideHeatLossConductanceDefaulted() const {
    return getImpl<detail::SolarCollectorPerformanceIntegralCollectorStorage_Impl>()->isSideHeatLossConductanceDefaulted();
  }

  bool SolarCollectorPerformanceIntegralCollectorStorage::setSideHeatLossConductance(double sideHeatLossConductance) {
    return getImpl<detail::SolarCollectorPerformanceIntegralCollectorStorage_Impl>()->setSideHeatLossConductance(sideHeatLossConductance);
  }

  void SolarCollectorPerformanceIntegralCollectorStorage::resetSideHeatLossConductance() {
    getImpl<detail::SolarCollectorPerformanceIntegralCollectorStorage_Impl>()->resetSideHeatLossConductance();
  }

  double SolarCollectorPerformanceIntegralCollectorStorage::aspectRatio() const {
    return getImpl<detail::SolarCollectorPerformanceIntegralCollectorStorage_Impl>()->aspectRatio();
  }

  bool SolarCollectorPerformanceIntegralCollectorStorage::isAspectRatioDefaulted() const {
    return getImpl<detail::SolarCollectorPerformanceIntegralCollectorStorage_Impl>()->isAspectRatioDefaulted();
  }

  bool SolarCollectorPerformanceIntegralCollectorStorage::setAspectRatio(double aspectRatio) {
    return getImpl<detail::SolarCollectorPerformanceIntegralCollectorStorage_Impl>()->setAspectRatio(aspectRatio);
  }

  void SolarCollectorPerformanceIntegralCollectorStorage::resetAspectRatio() {
    getImpl<detail::SolarCollectorPerformanceIntegralCollectorStorage_Impl>()->resetAspectRatio();
  }

  double SolarCollectorPerformanceIntegralCollectorStorage::collectorSideHeight() const {
    return getImpl<detail::SolarCollectorPerformanceIntegralCollectorStorage_Impl>()->collectorSideHeight();
  }

  bool SolarCollectorPerformanceIntegralCollectorStorage::isCollectorSideHeightDefaulted() const {
    return getImpl<detail::SolarCollectorPerformanceIntegralCollectorStorage_Impl>()->isCollectorSideHeightDefaulted();
  }

  bool SolarCollectorPerformanceIntegralCollectorStorage::setCollectorSideHeight(double collectorSideHeight) {
    return getImpl<detail::SolarCollectorPerformanceIntegralCollectorStorage_Impl>()->setCollectorSideHeight(collectorSideHeight);
  }

  void SolarCollectorPerformanceIntegralCollectorStorage::resetCollectorSideHeight() {
    getImpl<detail::SolarCollectorPerformanceIntegralCollectorStorage_Impl>()->resetCollectorSideHeight();
  }

  double SolarCollectorPerformanceIntegralCollectorStorage::thermalMassOfAbsorberPlate() const {
    return getImpl<detail::SolarCollectorPerformanceIntegralCollectorStorage_Impl>()->thermalMassOfAbsorberPlate();
  }

  bool SolarCollectorPerformanceIntegralCollectorStorage::isThermalMassOfAbsorberPlateDefaulted() const {
    return getImpl<detail::SolarCollectorPerformanceIntegralCollectorStorage_Impl>()->isThermalMassOfAbsorberPlateDefaulted();
  }

  bool SolarCollectorPerformanceIntegralCollectorStorage::setThermalMassOfAbsorberPlate(double thermalMassOfAbsorberPlate) {
    return getImpl<detail::SolarCollectorPerformanceIntegralCollectorStorage_Impl>()->setThermalMassOfAbsorberPlate(thermalMassOfAbsorberPlate);
  }

  void SolarCollectorPerformanceIntegralCollectorStorage::resetThermalMassOfAbsorberPlate() {
    getImpl<detail::SolarCollectorPerformanceIntegralCollectorStorage_Impl>()->resetThermalMassOfAbsorberPlate();
  }

  int SolarCollectorPerformanceIntegralCollectorStorage::numberOfCovers() const {
    return getImpl<detail::SolarCollectorPerformanceIntegralCollectorStorage_Impl>()->numberOfCovers();
  }

  bool SolarCollectorPerformanceIntegralCollectorStorage::isNumberOfCoversDefaulted() const {
    return getImpl<detail::SolarCollectorPerformanceIntegralCollectorStorage_Impl>()->isNumberOfCoversDefaulted();
  }

  bool SolarCollectorPerformanceIntegralCollectorStorage::setNumberOfCovers(int numberOfCovers) {
    return getImpl<detail::SolarCollectorPerformanceIntegralCollectorStorage_Impl>()->setNumberOfCovers(numberOfCovers);
  }

  void SolarCollectorPerformanceIntegralCollectorStorage::resetNumberOfCovers() {
    getImpl<detail::SolarCollectorPerformanceIntegralCollectorStorage_Impl>()->resetNumberOfCovers();
  }

  double SolarCollectorPerformanceIntegralCollectorStorage::coverSpacing() const {
    return getImpl<detail::SolarCollectorPerformanceIntegralCollectorStorage_Impl>()->coverSpacing();
  }

  bool SolarCollectorPerformanceIntegralCollectorStorage::isCoverSpacingDefaulted() const {
    return getImpl<detail::SolarCollectorPerformanceIntegralCollectorStorage_Impl>()->isCoverSpacingDefaulted();
  }

  bool SolarCollectorPerformanceIntegralCollectorStorage::setCoverSpacing(double coverSpacing) {
    return getImpl<detail::SolarCollectorPerformanceIntegralCollectorStorage_Impl>()->setCoverSpacing(coverSpacing);
  }

  void SolarCollectorPerformanceIntegralCollectorStorage::resetCoverSpacing() {
    getImpl<detail::SolarCollectorPerformanceIntegralCollectorStorage_Impl>()->resetCoverSpacing();
  }

  double SolarCollectorPerformanceIntegralCollectorStorage::refractiveIndexOfOuterCover() const {
    return getImpl<detail::SolarCollectorPerformanceIntegralCollectorStorage_Impl>()->refractiveIndexOfOuterCover();
  }

  bool SolarCollectorPerformanceIntegralCollectorStorage::isRefractiveIndexOfOuterCoverDefaulted() const {
    return getImpl<detail::SolarCollectorPerformanceIntegralCollectorStorage_Impl>()->isRefractiveIndexOfOuterCoverDefaulted();
  }

  bool SolarCollectorPerformanceIntegralCollectorStorage::setRefractiveIndexOfOuterCover(double refractiveIndexOfOuterCover) {
    return getImpl<detail::SolarCollectorPerformanceIntegralCollectorStorage_Impl>()->setRefractiveIndexOfOuterCover(refractiveIndexOfOuterCover);
  }

  void SolarCollectorPerformanceIntegralCollectorStorage::resetRefractiveIndexOfOuterCover() {
    getImpl<detail::SolarCollectorPerformanceIntegralCollectorStorage_Impl>()->resetRefractiveIndexOfOuterCover();
  }

  double SolarCollectorPerformanceIntegralCollectorStorage::extinctionCoefficientTimesThicknessOfOuterCover() const {
    return getImpl<detail::SolarCollectorPerformanceIntegralCollectorStorage_Impl>()->extinctionCoefficientTimesThicknessOfOuterCover();
  }

  bool SolarCollectorPerformanceIntegralCollectorStorage::isExtinctionCoefficientTimesThicknessOfOuterCoverDefaulted() const {
    return getImpl<detail::SolarCollectorPerformanceIntegralCollectorStorage_Impl>()->isExtinctionCoefficientTimesThicknessOfOuterCoverDefaulted();
  }

  bool SolarCollectorPerformanceIntegralCollectorStorage::setExtinctionCoefficientTimesThicknessOfOuterCover(
    double extinctionCoefficientTimesThicknessOfOuterCover) {
    return getImpl<detail::SolarCollectorPerformanceIntegralCollectorStorage_Impl>()->setExtinctionCoefficientTimesThicknessOfOuterCover(
      extinctionCoefficientTimesThicknessOfOuterCover);
  }

  void SolarCollectorPerformanceIntegralCollectorStorage::resetExtinctionCoefficientTimesThicknessOfOuterCover() {
    getImpl<detail::SolarCollectorPerformanceIntegralCollectorStorage_Impl>()->resetExtinctionCoefficientTimesThicknessOfOuterCover();
  }

  double SolarCollectorPerformanceIntegralCollectorStorage::emissivityOfOuterCover() const {
    return getImpl<detail::SolarCollectorPerformanceIntegralCollectorStorage_Impl>()->emissivityOfOuterCover();
  }

  bool SolarCollectorPerformanceIntegralCollectorStorage::isEmissivityOfOuterCoverDefaulted() const {
    return getImpl<detail::SolarCollectorPerformanceIntegralCollectorStorage_Impl>()->isEmissivityOfOuterCoverDefaulted();
  }

  bool SolarCollectorPerformanceIntegralCollectorStorage::setEmissivityOfOuterCover(double emissivityOfOuterCover) {
    return getImpl<detail::SolarCollectorPerformanceIntegralCollectorStorage_Impl>()->setEmissivityOfOuterCover(emissivityOfOuterCover);
  }

  void SolarCollectorPerformanceIntegralCollectorStorage::resetEmissivityOfOuterCover() {
    getImpl<detail::SolarCollectorPerformanceIntegralCollectorStorage_Impl>()->resetEmissivityOfOuterCover();
  }

  double SolarCollectorPerformanceIntegralCollectorStorage::refractiveIndexOfInnerCover() const {
    return getImpl<detail::SolarCollectorPerformanceIntegralCollectorStorage_Impl>()->refractiveIndexOfInnerCover();
  }

  bool SolarCollectorPerformanceIntegralCollectorStorage::isRefractiveIndexOfInnerCoverDefaulted() const {
    return getImpl<detail::SolarCollectorPerformanceIntegralCollectorStorage_Impl>()->isRefractiveIndexOfInnerCoverDefaulted();
  }

  bool SolarCollectorPerformanceIntegralCollectorStorage::setRefractiveIndexOfInnerCover(double refractiveIndexOfInnerCover) {
    return getImpl<detail::SolarCollectorPerformanceIntegralCollectorStorage_Impl>()->setRefractiveIndexOfInnerCover(refractiveIndexOfInnerCover);
  }

  void SolarCollectorPerformanceIntegralCollectorStorage::resetRefractiveIndexOfInnerCover() {
    getImpl<detail::SolarCollectorPerformanceIntegralCollectorStorage_Impl>()->resetRefractiveIndexOfInnerCover();
  }

  double SolarCollectorPerformanceIntegralCollectorStorage::extinctionCoefficientTimesThicknessOfTheInnerCover() const {
    return getImpl<detail::SolarCollectorPerformanceIntegralCollectorStorage_Impl>()->extinctionCoefficientTimesThicknessOfTheInnerCover();
  }

  bool SolarCollectorPerformanceIntegralCollectorStorage::isExtinctionCoefficientTimesThicknessOfTheInnerCoverDefaulted() const {
    return getImpl<detail::SolarCollectorPerformanceIntegralCollectorStorage_Impl>()->isExtinctionCoefficientTimesThicknessOfTheInnerCoverDefaulted();
  }

  bool SolarCollectorPerformanceIntegralCollectorStorage::setExtinctionCoefficientTimesThicknessOfTheInnerCover(
    double extinctionCoefficientTimesThicknessOfTheInnerCover) {
    return getImpl<detail::SolarCollectorPerformanceIntegralCollectorStorage_Impl>()->setExtinctionCoefficientTimesThicknessOfTheInnerCover(
      extinctionCoefficientTimesThicknessOfTheInnerCover);
  }

  void SolarCollectorPerformanceIntegralCollectorStorage::resetExtinctionCoefficientTimesThicknessOfTheInnerCover() {
    getImpl<detail::SolarCollectorPerformanceIntegralCollectorStorage_Impl>()->resetExtinctionCoefficientTimesThicknessOfTheInnerCover();
  }

  double SolarCollectorPerformanceIntegralCollectorStorage::emissivityOfInnerCover() const {
    return getImpl<detail::SolarCollectorPerformanceIntegralCollectorStorage_Impl>()->emissivityOfInnerCover();
  }

  bool SolarCollectorPerformanceIntegralCollectorStorage::isEmissivityOfInnerCoverDefaulted() const {
    return getImpl<detail::SolarCollectorPerformanceIntegralCollectorStorage_Impl>()->isEmissivityOfInnerCoverDefaulted();
  }

  bool SolarCollectorPerformanceIntegralCollectorStorage::setEmissivityOfInnerCover(double emissivityOfInnerCover) {
    return getImpl<detail::SolarCollectorPerformanceIntegralCollectorStorage_Impl>()->setEmissivityOfInnerCover(emissivityOfInnerCover);
  }

  void SolarCollectorPerformanceIntegralCollectorStorage::resetEmissivityOfInnerCover() {
    getImpl<detail::SolarCollectorPerformanceIntegralCollectorStorage_Impl>()->resetEmissivityOfInnerCover();
  }

  double SolarCollectorPerformanceIntegralCollectorStorage::absorptanceOfAbsorberPlate() const {
    return getImpl<detail::SolarCollectorPerformanceIntegralCollectorStorage_Impl>()->absorptanceOfAbsorberPlate();
  }

  bool SolarCollectorPerformanceIntegralCollectorStorage::isAbsorptanceOfAbsorberPlateDefaulted() const {
    return getImpl<detail::SolarCollectorPerformanceIntegralCollectorStorage_Impl>()->isAbsorptanceOfAbsorberPlateDefaulted();
  }

  bool SolarCollectorPerformanceIntegralCollectorStorage::setAbsorptanceOfAbsorberPlate(double absorptanceOfAbsorberPlate) {
    return getImpl<detail::SolarCollectorPerformanceIntegralCollectorStorage_Impl>()->setAbsorptanceOfAbsorberPlate(absorptanceOfAbsorberPlate);
  }

  void SolarCollectorPerformanceIntegralCollectorStorage::resetAbsorptanceOfAbsorberPlate() {
    getImpl<detail::SolarCollectorPerformanceIntegralCollectorStorage_Impl>()->resetAbsorptanceOfAbsorberPlate();
  }

  double SolarCollectorPerformanceIntegralCollectorStorage::emissivityOfAbsorberPlate() const {
    return getImpl<detail::SolarCollectorPerformanceIntegralCollectorStorage_Impl>()->emissivityOfAbsorberPlate();
  }

  bool SolarCollectorPerformanceIntegralCollectorStorage::isEmissivityOfAbsorberPlateDefaulted() const {
    return getImpl<detail::SolarCollectorPerformanceIntegralCollectorStorage_Impl>()->isEmissivityOfAbsorberPlateDefaulted();
  }

  bool SolarCollectorPerformanceIntegralCollectorStorage::setEmissivityOfAbsorberPlate(double emissivityOfAbsorberPlate) {
    return getImpl<detail::SolarCollectorPerformanceIntegralCollectorStorage_Impl>()->setEmissivityOfAbsorberPlate(emissivityOfAbsorberPlate);
  }

  void SolarCollectorPerformanceIntegralCollectorStorage::resetEmissivityOfAbsorberPlate() {
    getImpl<detail::SolarCollectorPerformanceIntegralCollectorStorage_Impl>()->resetEmissivityOfAbsorberPlate();
  }

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
  namespace detail {

    std::string SolarCollectorPerformanceIntegralCollectorStorage_Impl::iCSCollectorType() const {
      const auto value = getString(openstudio::SolarCollectorPerformance_IntegralCollectorStorageFields::ICSCollectorType, true);
      OS_ASSERT(value);
      return *value;
    }

    bool SolarCollectorPerformanceIntegralCollectorStorage_Impl::isICSCollectorTypeDefaulted() const {
      return isEmpty(openstudio::SolarCollectorPerformance_IntegralCollectorStorageFields::ICSCollectorType);
    }

    bool SolarCollectorPerformanceIntegralCollectorStorage_Impl::setICSCollectorType(const std::string& iCSCollectorType) {
      return setString(openstudio::SolarCollectorPerformance_IntegralCollectorStorageFields::ICSCollectorType, iCSCollectorType);
    }

    void SolarCollectorPerformanceIntegralCollectorStorage_Impl::resetICSCollectorType() {
      OS_ASSERT(setString(openstudio::SolarCollectorPerformance_IntegralCollectorStorageFields::ICSCollectorType, ""));
    }

    double SolarCollectorPerformanceIntegralCollectorStorage_Impl::grossArea() const {
      const auto value = getDouble(openstudio::SolarCollectorPerformance_IntegralCollectorStorageFields::GrossArea, true);
      OS_ASSERT(value);
      return *value;
    }

    bool SolarCollectorPerformanceIntegralCollectorStorage_Impl::setGrossArea(double grossArea) {
      return setDouble(openstudio::SolarCollectorPerformance_IntegralCollectorStorageFields::GrossArea, grossArea);
    }

    double SolarCollectorPerformanceIntegralCollectorStorage_Impl::collectorWaterVolume() const {
      const auto value = getDouble(openstudio::SolarCollectorPerformance_IntegralCollectorStorageFields::CollectorWaterVolume, true);
      OS_ASSERT(value);
      return *value;
    }

    bool SolarCollectorPerformanceIntegralCollectorStorage_Impl::setCollectorWaterVolume(double collectorWaterVolume) {
      return setDouble(openstudio::SolarCollectorPerformance_IntegralCollectorStorageFields::CollectorWaterVolume, collectorWaterVolume);
    }

    double SolarCollectorPerformanceIntegralCollectorStorage_Impl::bottomHeatLossConductance() const {
      const auto value = getDouble(openstudio::SolarCollectorPerformance_IntegralCollectorStorageFields::BottomHeatLossConductance, true);
      OS_ASSERT(value);
      return *value;
    }

    bool SolarCollectorPerformanceIntegralCollectorStorage_Impl::isBottomHeatLossConductanceDefaulted() const {
      return isEmpty(openstudio::SolarCollectorPerformance_IntegralCollectorStorageFields::BottomHeatLossConductance);
    }

    bool SolarCollectorPerformanceIntegralCollectorStorage_Impl::setBottomHeatLossConductance(double bottomHeatLossConductance) {
      return setDouble(openstudio::SolarCollectorPerformance_IntegralCollectorStorageFields::BottomHeatLossConductance, bottomHeatLossConductance);
    }

    void SolarCollectorPerformanceIntegralCollectorStorage_Impl::resetBottomHeatLossConductance() {
      OS_ASSERT(setString(openstudio::SolarCollectorPerformance_IntegralCollectorStorageFields::BottomHeatLossConductance, ""));
    }

    double SolarCollectorPerformanceIntegralCollectorStorage_Impl::sideHeatLossConductance() const {
      const auto value = getDouble(openstudio::SolarCollectorPerformance_IntegralCollectorStorageFields::SideHeatLossConductance, true);
      OS_ASSERT(value);
      return *value;
    }

    bool SolarCollectorPerformanceIntegralCollectorStorage_Impl::isSideHeatLossConductanceDefaulted() const {
      return isEmpty(openstudio::SolarCollectorPerformance_IntegralCollectorStorageFields::SideHeatLossConductance);
    }

    bool SolarCollectorPerformanceIntegralCollectorStorage_Impl::setSideHeatLossConductance(double sideHeatLossConductance) {
      return setDouble(openstudio::SolarCollectorPerformance_IntegralCollectorStorageFields::SideHeatLossConductance, sideHeatLossConductance);
    }

    void SolarCollectorPerformanceIntegralCollectorStorage_Impl::resetSideHeatLossConductance() {
      OS_ASSERT(setString(openstudio::SolarCollectorPerformance_IntegralCollectorStorageFields::SideHeatLossConductance, ""));
    }

    double SolarCollectorPerformanceIntegralCollectorStorage_Impl::aspectRatio() const {
      const auto value = getDouble(openstudio::SolarCollectorPerformance_IntegralCollectorStorageFields::AspectRatio, true);
      OS_ASSERT(value);
      return *value;
    }

    bool SolarCollectorPerformanceIntegralCollectorStorage_Impl::isAspectRatioDefaulted() const {
      return isEmpty(openstudio::SolarCollectorPerformance_IntegralCollectorStorageFields::AspectRatio);
    }

    bool SolarCollectorPerformanceIntegralCollectorStorage_Impl::setAspectRatio(double aspectRatio) {
      return setDouble(openstudio::SolarCollectorPerformance_IntegralCollectorStorageFields::AspectRatio, aspectRatio);
    }

    void SolarCollectorPerformanceIntegralCollectorStorage_Impl::resetAspectRatio() {
      OS_ASSERT(setString(openstudio::SolarCollectorPerformance_IntegralCollectorStorageFields::AspectRatio, ""));
    }

    double SolarCollectorPerformanceIntegralCollectorStorage_Impl::collectorSideHeight() const {
      const auto value = getDouble(openstudio::SolarCollectorPerformance_IntegralCollectorStorageFields::CollectorSideHeight, true);
      OS_ASSERT(value);
      return *value;
    }

    bool SolarCollectorPerformanceIntegralCollectorStorage_Impl::isCollectorSideHeightDefaulted() const {
      return isEmpty(openstudio::SolarCollectorPerformance_IntegralCollectorStorageFields::CollectorSideHeight);
    }

    bool SolarCollectorPerformanceIntegralCollectorStorage_Impl::setCollectorSideHeight(double collectorSideHeight) {
      return setDouble(openstudio::SolarCollectorPerformance_IntegralCollectorStorageFields::CollectorSideHeight, collectorSideHeight);
    }

    void SolarCollectorPerformanceIntegralCollectorStorage_Impl::resetCollectorSideHeight() {
      OS_ASSERT(setString(openstudio::SolarCollectorPerformance_IntegralCollectorStorageFields::CollectorSideHeight, ""));
    }

    double SolarCollectorPerformanceIntegralCollectorStorage_Impl::thermalMassOfAbsorberPlate() const {
      const auto value = getDouble(openstudio::SolarCollectorPerformance_IntegralCollectorStorageFields::ThermalMassofAbsorberPlate, true);
      OS_ASSERT(value);
      return *value;
    }

    bool SolarCollectorPerformanceIntegralCollectorStorage_Impl::isThermalMassOfAbsorberPlateDefaulted() const {
      return isEmpty(openstudio::SolarCollectorPerformance_IntegralCollectorStorageFields::ThermalMassofAbsorberPlate);
    }

    bool SolarCollectorPerformanceIntegralCollectorStorage_Impl::setThermalMassOfAbsorberPlate(double thermalMassOfAbsorberPlate) {
      return setDouble(openstudio::SolarCollectorPerformance_IntegralCollectorStorageFields::ThermalMassofAbsorberPlate, thermalMassOfAbsorberPlate);
    }

    void SolarCollectorPerformanceIntegralCollectorStorage_Impl::resetThermalMassOfAbsorberPlate() {
      OS_ASSERT(setString(openstudio::SolarCollectorPerformance_IntegralCollectorStorageFields::ThermalMassofAbsorberPlate, ""));
    }

    int SolarCollectorPerformanceIntegralCollectorStorage_Impl::numberOfCovers() const {
      const auto value = getInt(openstudio::SolarCollectorPerformance_IntegralCollectorStorageFields::NumberofCovers, true);
      OS_ASSERT(value);
      return *value;
    }

    bool SolarCollectorPerformanceIntegralCollectorStorage_Impl::isNumberOfCoversDefaulted() const {
      return isEmpty(openstudio::SolarCollectorPerformance_IntegralCollectorStorageFields::NumberofCovers);
    }

    bool SolarCollectorPerformanceIntegralCollectorStorage_Impl::setNumberOfCovers(int numberOfCovers) {
      return setInt(openstudio::SolarCollectorPerformance_IntegralCollectorStorageFields::NumberofCovers, numberOfCovers);
    }

    void SolarCollectorPerformanceIntegralCollectorStorage_Impl::resetNumberOfCovers() {
      OS_ASSERT(setString(openstudio::SolarCollectorPerformance_IntegralCollectorStorageFields::NumberofCovers, ""));
    }

    double SolarCollectorPerformanceIntegralCollectorStorage_Impl::coverSpacing() const {
      const auto value = getDouble(openstudio::SolarCollectorPerformance_IntegralCollectorStorageFields::CoverSpacing, true);
      OS_ASSERT(value);
      return *value;
    }

    bool SolarCollectorPerformanceIntegralCollectorStorage_Impl::isCoverSpacingDefaulted() const {
      return isEmpty(openstudio::SolarCollectorPerformance_IntegralCollectorStorageFields::CoverSpacing);
    }

    bool SolarCollectorPerformanceIntegralCollectorStorage_Impl::setCoverSpacing(double coverSpacing) {
      return setDouble(openstudio::SolarCollectorPerformance_IntegralCollectorStorageFields::CoverSpacing, coverSpacing);
    }

    void SolarCollectorPerformanceIntegralCollectorStorage_Impl::resetCoverSpacing() {
      OS_ASSERT(setString(openstudio::SolarCollectorPerformance_IntegralCollectorStorageFields::CoverSpacing, ""));
    }

    double SolarCollectorPerformanceIntegralCollectorStorage_Impl::refractiveIndexOfOuterCover() const {
      const auto value = getDouble(openstudio::SolarCollectorPerformance_IntegralCollectorStorageFields::RefractiveIndexofOuterCover, true);
      OS_ASSERT(value);
      return *value;
    }

    bool SolarCollectorPerformanceIntegralCollectorStorage_Impl::isRefractiveIndexOfOuterCoverDefaulted() const {
      return isEmpty(openstudio::SolarCollectorPerformance_IntegralCollectorStorageFields::RefractiveIndexofOuterCover);
    }

    bool SolarCollectorPerformanceIntegralCollectorStorage_Impl::setRefractiveIndexOfOuterCover(double refractiveIndexOfOuterCover) {
      return setDouble(openstudio::SolarCollectorPerformance_IntegralCollectorStorageFields::RefractiveIndexofOuterCover,
                       refractiveIndexOfOuterCover);
    }

    void SolarCollectorPerformanceIntegralCollectorStorage_Impl::resetRefractiveIndexOfOuterCover() {
      OS_ASSERT(setString(openstudio::SolarCollectorPerformance_IntegralCollectorStorageFields::RefractiveIndexofOuterCover, ""));
    }

    double SolarCollectorPerformanceIntegralCollectorStorage_Impl::extinctionCoefficientTimesThicknessOfOuterCover() const {
      const auto value =
        getDouble(openstudio::SolarCollectorPerformance_IntegralCollectorStorageFields::ExtinctionCoefficientTimesThicknessofOuterCover, true);
      OS_ASSERT(value);
      return *value;
    }

    bool SolarCollectorPerformanceIntegralCollectorStorage_Impl::isExtinctionCoefficientTimesThicknessOfOuterCoverDefaulted() const {
      return isEmpty(openstudio::SolarCollectorPerformance_IntegralCollectorStorageFields::ExtinctionCoefficientTimesThicknessofOuterCover);
    }

    bool SolarCollectorPerformanceIntegralCollectorStorage_Impl::setExtinctionCoefficientTimesThicknessOfOuterCover(
      double extinctionCoefficientTimesThicknessOfOuterCover) {
      return setDouble(openstudio::SolarCollectorPerformance_IntegralCollectorStorageFields::ExtinctionCoefficientTimesThicknessofOuterCover,
                       extinctionCoefficientTimesThicknessOfOuterCover);
    }

    void SolarCollectorPerformanceIntegralCollectorStorage_Impl::resetExtinctionCoefficientTimesThicknessOfOuterCover() {
      OS_ASSERT(setString(openstudio::SolarCollectorPerformance_IntegralCollectorStorageFields::ExtinctionCoefficientTimesThicknessofOuterCover,
                          ""));
    }

    double SolarCollectorPerformanceIntegralCollectorStorage_Impl::emissivityOfOuterCover() const {
      const auto value = getDouble(openstudio::SolarCollectorPerformance_IntegralCollectorStorageFields::EmissivityofOuterCover, true);
      OS_ASSERT(value);
      return *value;
    }

    bool SolarCollectorPerformanceIntegralCollectorStorage_Impl::isEmissivityOfOuterCoverDefaulted() const {
      return isEmpty(openstudio::SolarCollectorPerformance_IntegralCollectorStorageFields::EmissivityofOuterCover);
    }

    bool SolarCollectorPerformanceIntegralCollectorStorage_Impl::setEmissivityOfOuterCover(double emissivityOfOuterCover) {
      return setDouble(openstudio::SolarCollectorPerformance_IntegralCollectorStorageFields::EmissivityofOuterCover, emissivityOfOuterCover);
    }

    void SolarCollectorPerformanceIntegralCollectorStorage_Impl::resetEmissivityOfOuterCover() {
      OS_ASSERT(setString(openstudio::SolarCollectorPerformance_IntegralCollectorStorageFields::EmissivityofOuterCover, ""));
    }

    double SolarCollectorPerformanceIntegralCollectorStorage_Impl::refractiveIndexOfInnerCover() const {
      const auto value = getDouble(openstudio::SolarCollectorPerformance_IntegralCollectorStorageFields::RefractiveIndexofInnerCover, true);
      OS_ASSERT(value);
      return *value;
    }

    bool SolarCollectorPerformanceIntegralCollectorStorage_Impl::isRefractiveIndexOfInnerCoverDefaulted() const {
      return isEmpty(openstudio::SolarCollectorPerformance_IntegralCollectorStorageFields::RefractiveIndexofInnerCover);
    }

    bool SolarCollectorPerformanceIntegralCollectorStorage_Impl::setRefractiveIndexOfInnerCover(double refractiveIndexOfInnerCover) {
      return setDouble(openstudio::SolarCollectorPerformance_IntegralCollectorStorageFields::RefractiveIndexofInnerCover,
                       refractiveIndexOfInnerCover);
    }

    void SolarCollectorPerformanceIntegralCollectorStorage_Impl::resetRefractiveIndexOfInnerCover() {
      OS_ASSERT(setString(openstudio::SolarCollectorPerformance_IntegralCollectorStorageFields::RefractiveIndexofInnerCover, ""));
    }

    double SolarCollectorPerformanceIntegralCollectorStorage_Impl::extinctionCoefficientTimesThicknessOfTheInnerCover() const {
      const auto value =
        getDouble(openstudio::SolarCollectorPerformance_IntegralCollectorStorageFields::ExtinctionCoefficientTimesThicknessoftheinnerCover, true);
      OS_ASSERT(value);
      return *value;
    }

    bool SolarCollectorPerformanceIntegralCollectorStorage_Impl::isExtinctionCoefficientTimesThicknessOfTheInnerCoverDefaulted() const {
      return isEmpty(openstudio::SolarCollectorPerformance_IntegralCollectorStorageFields::ExtinctionCoefficientTimesThicknessoftheinnerCover);
    }

    bool SolarCollectorPerformanceIntegralCollectorStorage_Impl::setExtinctionCoefficientTimesThicknessOfTheInnerCover(
      double extinctionCoefficientTimesThicknessOfTheInnerCover) {
      return setDouble(openstudio::SolarCollectorPerformance_IntegralCollectorStorageFields::ExtinctionCoefficientTimesThicknessoftheinnerCover,
                       extinctionCoefficientTimesThicknessOfTheInnerCover);
    }

    void SolarCollectorPerformanceIntegralCollectorStorage_Impl::resetExtinctionCoefficientTimesThicknessOfTheInnerCover() {
      OS_ASSERT(setString(openstudio::SolarCollectorPerformance_IntegralCollectorStorageFields::ExtinctionCoefficientTimesThicknessoftheinnerCover, ""));
    }

    double SolarCollectorPerformanceIntegralCollectorStorage_Impl::emissivityOfInnerCover() const {
      const auto value = getDouble(openstudio::SolarCollectorPerformance_IntegralCollectorStorageFields::EmissivityofInnerCover, true);
      OS_ASSERT(value);
      return *value;
    }

    bool SolarCollectorPerformanceIntegralCollectorStorage_Impl::isEmissivityOfInnerCoverDefaulted() const {
      return isEmpty(openstudio::SolarCollectorPerformance_IntegralCollectorStorageFields::EmissivityofInnerCover);
    }

    bool SolarCollectorPerformanceIntegralCollectorStorage_Impl::setEmissivityOfInnerCover(double emissivityOfInnerCover) {
      return setDouble(openstudio::SolarCollectorPerformance_IntegralCollectorStorageFields::EmissivityofInnerCover, emissivityOfInnerCover);
    }

    void SolarCollectorPerformanceIntegralCollectorStorage_Impl::resetEmissivityOfInnerCover() {
      OS_ASSERT(setString(openstudio::SolarCollectorPerformance_IntegralCollectorStorageFields::EmissivityofInnerCover, ""));
    }

    double SolarCollectorPerformanceIntegralCollectorStorage_Impl::absorptanceOfAbsorberPlate() const {
      const auto value = getDouble(openstudio::SolarCollectorPerformance_IntegralCollectorStorageFields::AbsorptanceofAbsorberPlate, true);
      OS_ASSERT(value);
      return *value;
    }

    bool SolarCollectorPerformanceIntegralCollectorStorage_Impl::isAbsorptanceOfAbsorberPlateDefaulted() const {
      return isEmpty(openstudio::SolarCollectorPerformance_IntegralCollectorStorageFields::AbsorptanceofAbsorberPlate);
    }

    bool SolarCollectorPerformanceIntegralCollectorStorage_Impl::setAbsorptanceOfAbsorberPlate(double absorptanceOfAbsorberPlate) {
      return setDouble(openstudio::SolarCollectorPerformance_IntegralCollectorStorageFields::AbsorptanceofAbsorberPlate, absorptanceOfAbsorberPlate);
    }

    void SolarCollectorPerformanceIntegralCollectorStorage_Impl::resetAbsorptanceOfAbsorberPlate() {
      OS_ASSERT(setString(openstudio::SolarCollectorPerformance_IntegralCollectorStorageFields::AbsorptanceofAbsorberPlate, ""));
    }

    double SolarCollectorPerformanceIntegralCollectorStorage_Impl::emissivityOfAbsorberPlate() const {
      const auto value = getDouble(openstudio::SolarCollectorPerformance_IntegralCollectorStorageFields::EmissivityofAbsorberPlate, true);
      OS_ASSERT(value);
      return *value;
    }

    bool SolarCollectorPerformanceIntegralCollectorStorage_Impl::isEmissivityOfAbsorberPlateDefaulted() const {
      return isEmpty(openstudio::SolarCollectorPerformance_IntegralCollectorStorageFields::EmissivityofAbsorberPlate);
    }

    bool SolarCollectorPerformanceIntegralCollectorStorage_Impl::setEmissivityOfAbsorberPlate(double emissivityOfAbsorberPlate) {
      return setDouble(openstudio::SolarCollectorPerformance_IntegralCollectorStorageFields::EmissivityofAbsorberPlate, emissivityOfAbsorberPlate);
    }

    void SolarCollectorPerformanceIntegralCollectorStorage_Impl::resetEmissivityOfAbsorberPlate() {
      OS_ASSERT(setString(openstudio::SolarCollectorPerformance_IntegralCollectorStorageFields::EmissivityofAbsorberPlate, ""));
    }

    std::vector<std::string> SolarCollectorPerformanceIntegralCollectorStorage_Impl::iCSCollectorTypeValues() const {
      return openstudio::epmodel::SolarCollectorPerformanceIntegralCollectorStorage::iCSCollectorTypeValues();
    }

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
