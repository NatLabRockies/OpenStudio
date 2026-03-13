/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "SizingZone.hpp"
#include "SizingZone_Impl.hpp"

#include "Model.hpp"
#include "HVACComponent/ThermalZone.hpp"
#include "HVACComponent/ThermalZone_Impl.hpp"
#include "ResourceObject/DesignSpecificationOutdoorAir.hpp"
#include "ResourceObject/DesignSpecificationOutdoorAir_Impl.hpp"
#include "ModelObject/DesignSpecificationOutdoorAirSpaceList.hpp"
#include "ModelObject/DesignSpecificationOutdoorAirSpaceList_Impl.hpp"
#include "PlanarSurfaceGroup/Space.hpp"
#include "PlanarSurfaceGroup/Space_Impl.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/core/StringHelpers.hpp>
#include <utilities/idd/DesignSpecification_ZoneAirDistribution_FieldEnums.hxx>
#include <utilities/idd/IddEnums.hxx>
#include <utilities/idd/IddFactory.hxx>
#include <utilities/idd/Sizing_Zone_FieldEnums.hxx>

namespace openstudio {
namespace epmodel {

  SizingZone::SizingZone(const Model& model, const ThermalZone& thermalZone) : ModelObject(SizingZone::iddObjectType(), model) {
    auto impl = getImpl<detail::SizingZone_Impl>();
    OS_ASSERT(impl);
    OS_ASSERT(impl->setPointer(openstudio::Sizing_ZoneFields::ZoneorZoneListName, thermalZone.handle(), false));

    // Keep model-counterpart constructor defaults for required/non-optional scalar fields.
    OS_ASSERT(setZoneCoolingDesignSupplyAirTemperatureInputMethod("SupplyAirTemperature"));
    OS_ASSERT(setZoneCoolingDesignSupplyAirTemperatureDifference(11.11));
    OS_ASSERT(setZoneCoolingDesignSupplyAirTemperature(14.0));
    OS_ASSERT(setZoneHeatingDesignSupplyAirTemperatureInputMethod("SupplyAirTemperature"));
    OS_ASSERT(setZoneHeatingDesignSupplyAirTemperatureDifference(11.11));
    OS_ASSERT(setZoneHeatingDesignSupplyAirTemperature(40.0));
    OS_ASSERT(setZoneCoolingDesignSupplyAirHumidityRatio(0.0085));
    OS_ASSERT(setZoneHeatingDesignSupplyAirHumidityRatio(0.008));
    OS_ASSERT(setCoolingDesignAirFlowMethod("DesignDay"));
    OS_ASSERT(setHeatingDesignAirFlowMethod("DesignDay"));
    OS_ASSERT(setAccountforDedicatedOutdoorAirSystem(false));
    OS_ASSERT(setDedicatedOutdoorAirSystemControlStrategy("NeutralSupplyAir"));
    autosizeDedicatedOutdoorAirLowSetpointTemperatureforDesign();
    autosizeDedicatedOutdoorAirHighSetpointTemperatureforDesign();

    OS_ASSERT(setZoneLoadSizingMethod("Sensible Load Only No Latent Load"));
    OS_ASSERT(setZoneLatentCoolingDesignSupplyAirHumidityRatioInputMethod("HumidityRatioDifference"));
    OS_ASSERT(setZoneCoolingDesignSupplyAirHumidityRatioDifference(0.005));
    OS_ASSERT(setZoneLatentHeatingDesignSupplyAirHumidityRatioInputMethod("HumidityRatioDifference"));
    OS_ASSERT(setZoneHumidificationDesignSupplyAirHumidityRatioDifference(0.005));

    OS_ASSERT(setSizingOption("Coincident"));
    OS_ASSERT(setHeatingCoilSizingMethod("None"));
    OS_ASSERT(setMaximumHeatingCapacityToCoolingLoadSizingRatio(1.0));

    detail::LoadContext context{const_cast<Model&>(model), SanitizationPolicy::Repair, SanitizationReport{}, {}};  // NOLINT
    impl->canonicalize(context);
  }

  SizingZone::SizingZone(std::shared_ptr<detail::SizingZone_Impl> impl) : ModelObject(std::move(impl)) {}

  IddObjectType SizingZone::iddObjectType() {
    return IddObjectType::Sizing_Zone;
  }

  std::vector<std::string> SizingZone::coolingDesignAirFlowMethodValues() {
    return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(), openstudio::Sizing_ZoneFields::CoolingDesignAirFlowMethod);
  }

  std::vector<std::string> SizingZone::heatingDesignAirFlowMethodValues() {
    return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(), openstudio::Sizing_ZoneFields::HeatingDesignAirFlowMethod);
  }

  std::vector<std::string> SizingZone::zoneCoolingDesignSupplyAirTemperatureInputMethodValues() {
    return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(),
                          openstudio::Sizing_ZoneFields::ZoneCoolingDesignSupplyAirTemperatureInputMethod);
  }

  std::vector<std::string> SizingZone::zoneHeatingDesignSupplyAirTemperatureInputMethodValues() {
    return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(),
                          openstudio::Sizing_ZoneFields::ZoneHeatingDesignSupplyAirTemperatureInputMethod);
  }

  std::vector<std::string> SizingZone::zoneLoadSizingMethodValues() {
    return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(), openstudio::Sizing_ZoneFields::ZoneLoadSizingMethod);
  }

  std::vector<std::string> SizingZone::zoneLatentCoolingDesignSupplyAirHumidityRatioInputMethodValues() {
    return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(),
                          openstudio::Sizing_ZoneFields::ZoneLatentCoolingDesignSupplyAirHumidityRatioInputMethod);
  }

  std::vector<std::string> SizingZone::zoneLatentHeatingDesignSupplyAirHumidityRatioInputMethodValues() {
    return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(),
                          openstudio::Sizing_ZoneFields::ZoneLatentHeatingDesignSupplyAirHumidityRatioInputMethod);
  }

  std::vector<std::string> SizingZone::validSizingOptionValues() {
    return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(), openstudio::Sizing_ZoneFields::TypeofSpaceSumtoUse);
  }

  std::vector<std::string> SizingZone::heatingCoilSizingMethodValues() {
    return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(), openstudio::Sizing_ZoneFields::HeatingCoilSizingMethod);
  }

  ThermalZone SizingZone::thermalZone() const {
    return getImpl<detail::SizingZone_Impl>()->thermalZone();
  }

  std::string SizingZone::zoneCoolingDesignSupplyAirTemperatureInputMethod() const {
    return getImpl<detail::SizingZone_Impl>()->zoneCoolingDesignSupplyAirTemperatureInputMethod();
  }

  bool SizingZone::setZoneCoolingDesignSupplyAirTemperatureInputMethod(const std::string& value) {
    return getImpl<detail::SizingZone_Impl>()->setZoneCoolingDesignSupplyAirTemperatureInputMethod(value);
  }

  double SizingZone::zoneCoolingDesignSupplyAirTemperature() const {
    return getImpl<detail::SizingZone_Impl>()->zoneCoolingDesignSupplyAirTemperature();
  }

  bool SizingZone::setZoneCoolingDesignSupplyAirTemperature(double zoneCoolingDesignSupplyAirTemperature) {
    return getImpl<detail::SizingZone_Impl>()->setZoneCoolingDesignSupplyAirTemperature(zoneCoolingDesignSupplyAirTemperature);
  }

  double SizingZone::zoneCoolingDesignSupplyAirTemperatureDifference() const {
    return getImpl<detail::SizingZone_Impl>()->zoneCoolingDesignSupplyAirTemperatureDifference();
  }

  bool SizingZone::setZoneCoolingDesignSupplyAirTemperatureDifference(double value) {
    return getImpl<detail::SizingZone_Impl>()->setZoneCoolingDesignSupplyAirTemperatureDifference(value);
  }

  std::string SizingZone::zoneHeatingDesignSupplyAirTemperatureInputMethod() const {
    return getImpl<detail::SizingZone_Impl>()->zoneHeatingDesignSupplyAirTemperatureInputMethod();
  }

  bool SizingZone::setZoneHeatingDesignSupplyAirTemperatureInputMethod(const std::string& value) {
    return getImpl<detail::SizingZone_Impl>()->setZoneHeatingDesignSupplyAirTemperatureInputMethod(value);
  }

  double SizingZone::zoneHeatingDesignSupplyAirTemperature() const {
    return getImpl<detail::SizingZone_Impl>()->zoneHeatingDesignSupplyAirTemperature();
  }

  bool SizingZone::setZoneHeatingDesignSupplyAirTemperature(double zoneHeatingDesignSupplyAirTemperature) {
    return getImpl<detail::SizingZone_Impl>()->setZoneHeatingDesignSupplyAirTemperature(zoneHeatingDesignSupplyAirTemperature);
  }

  double SizingZone::zoneHeatingDesignSupplyAirTemperatureDifference() const {
    return getImpl<detail::SizingZone_Impl>()->zoneHeatingDesignSupplyAirTemperatureDifference();
  }

  bool SizingZone::setZoneHeatingDesignSupplyAirTemperatureDifference(double value) {
    return getImpl<detail::SizingZone_Impl>()->setZoneHeatingDesignSupplyAirTemperatureDifference(value);
  }

  double SizingZone::zoneCoolingDesignSupplyAirHumidityRatio() const {
    return getImpl<detail::SizingZone_Impl>()->zoneCoolingDesignSupplyAirHumidityRatio();
  }

  bool SizingZone::setZoneCoolingDesignSupplyAirHumidityRatio(double zoneCoolingDesignSupplyAirHumidityRatio) {
    return getImpl<detail::SizingZone_Impl>()->setZoneCoolingDesignSupplyAirHumidityRatio(zoneCoolingDesignSupplyAirHumidityRatio);
  }

  double SizingZone::zoneHeatingDesignSupplyAirHumidityRatio() const {
    return getImpl<detail::SizingZone_Impl>()->zoneHeatingDesignSupplyAirHumidityRatio();
  }

  bool SizingZone::setZoneHeatingDesignSupplyAirHumidityRatio(double zoneHeatingDesignSupplyAirHumidityRatio) {
    return getImpl<detail::SizingZone_Impl>()->setZoneHeatingDesignSupplyAirHumidityRatio(zoneHeatingDesignSupplyAirHumidityRatio);
  }

  boost::optional<double> SizingZone::zoneHeatingSizingFactor() const {
    return getImpl<detail::SizingZone_Impl>()->zoneHeatingSizingFactor();
  }

  bool SizingZone::setZoneHeatingSizingFactor(double zoneHeatingSizingFactor) {
    return getImpl<detail::SizingZone_Impl>()->setZoneHeatingSizingFactor(zoneHeatingSizingFactor);
  }

  void SizingZone::resetZoneHeatingSizingFactor() {
    getImpl<detail::SizingZone_Impl>()->resetZoneHeatingSizingFactor();
  }

  boost::optional<double> SizingZone::zoneCoolingSizingFactor() const {
    return getImpl<detail::SizingZone_Impl>()->zoneCoolingSizingFactor();
  }

  bool SizingZone::setZoneCoolingSizingFactor(double zoneCoolingSizingFactor) {
    return getImpl<detail::SizingZone_Impl>()->setZoneCoolingSizingFactor(zoneCoolingSizingFactor);
  }

  void SizingZone::resetZoneCoolingSizingFactor() {
    getImpl<detail::SizingZone_Impl>()->resetZoneCoolingSizingFactor();
  }

  std::string SizingZone::coolingDesignAirFlowMethod() const {
    return getImpl<detail::SizingZone_Impl>()->coolingDesignAirFlowMethod();
  }

  bool SizingZone::isCoolingDesignAirFlowMethodDefaulted() const {
    return getImpl<detail::SizingZone_Impl>()->isCoolingDesignAirFlowMethodDefaulted();
  }

  bool SizingZone::setCoolingDesignAirFlowMethod(const std::string& coolingDesignAirFlowMethod) {
    return getImpl<detail::SizingZone_Impl>()->setCoolingDesignAirFlowMethod(coolingDesignAirFlowMethod);
  }

  void SizingZone::resetCoolingDesignAirFlowMethod() {
    getImpl<detail::SizingZone_Impl>()->resetCoolingDesignAirFlowMethod();
  }

  double SizingZone::coolingDesignAirFlowRate() const {
    return getImpl<detail::SizingZone_Impl>()->coolingDesignAirFlowRate();
  }

  bool SizingZone::isCoolingDesignAirFlowRateDefaulted() const {
    return getImpl<detail::SizingZone_Impl>()->isCoolingDesignAirFlowRateDefaulted();
  }

  bool SizingZone::setCoolingDesignAirFlowRate(double coolingDesignAirFlowRate) {
    return getImpl<detail::SizingZone_Impl>()->setCoolingDesignAirFlowRate(coolingDesignAirFlowRate);
  }

  void SizingZone::resetCoolingDesignAirFlowRate() {
    getImpl<detail::SizingZone_Impl>()->resetCoolingDesignAirFlowRate();
  }

  double SizingZone::coolingMinimumAirFlowperZoneFloorArea() const {
    return getImpl<detail::SizingZone_Impl>()->coolingMinimumAirFlowperZoneFloorArea();
  }

  bool SizingZone::isCoolingMinimumAirFlowperZoneFloorAreaDefaulted() const {
    return getImpl<detail::SizingZone_Impl>()->isCoolingMinimumAirFlowperZoneFloorAreaDefaulted();
  }

  bool SizingZone::setCoolingMinimumAirFlowperZoneFloorArea(double coolingMinimumAirFlowperZoneFloorArea) {
    return getImpl<detail::SizingZone_Impl>()->setCoolingMinimumAirFlowperZoneFloorArea(coolingMinimumAirFlowperZoneFloorArea);
  }

  void SizingZone::resetCoolingMinimumAirFlowperZoneFloorArea() {
    getImpl<detail::SizingZone_Impl>()->resetCoolingMinimumAirFlowperZoneFloorArea();
  }

  double SizingZone::coolingMinimumAirFlow() const {
    return getImpl<detail::SizingZone_Impl>()->coolingMinimumAirFlow();
  }

  bool SizingZone::isCoolingMinimumAirFlowDefaulted() const {
    return getImpl<detail::SizingZone_Impl>()->isCoolingMinimumAirFlowDefaulted();
  }

  bool SizingZone::setCoolingMinimumAirFlow(double coolingMinimumAirFlow) {
    return getImpl<detail::SizingZone_Impl>()->setCoolingMinimumAirFlow(coolingMinimumAirFlow);
  }

  void SizingZone::resetCoolingMinimumAirFlow() {
    getImpl<detail::SizingZone_Impl>()->resetCoolingMinimumAirFlow();
  }

  double SizingZone::coolingMinimumAirFlowFraction() const {
    return getImpl<detail::SizingZone_Impl>()->coolingMinimumAirFlowFraction();
  }

  bool SizingZone::isCoolingMinimumAirFlowFractionDefaulted() const {
    return getImpl<detail::SizingZone_Impl>()->isCoolingMinimumAirFlowFractionDefaulted();
  }

  bool SizingZone::setCoolingMinimumAirFlowFraction(double coolingMinimumAirFlowFraction) {
    return getImpl<detail::SizingZone_Impl>()->setCoolingMinimumAirFlowFraction(coolingMinimumAirFlowFraction);
  }

  void SizingZone::resetCoolingMinimumAirFlowFraction() {
    getImpl<detail::SizingZone_Impl>()->resetCoolingMinimumAirFlowFraction();
  }

  std::string SizingZone::heatingDesignAirFlowMethod() const {
    return getImpl<detail::SizingZone_Impl>()->heatingDesignAirFlowMethod();
  }

  bool SizingZone::isHeatingDesignAirFlowMethodDefaulted() const {
    return getImpl<detail::SizingZone_Impl>()->isHeatingDesignAirFlowMethodDefaulted();
  }

  bool SizingZone::setHeatingDesignAirFlowMethod(const std::string& heatingDesignAirFlowMethod) {
    return getImpl<detail::SizingZone_Impl>()->setHeatingDesignAirFlowMethod(heatingDesignAirFlowMethod);
  }

  void SizingZone::resetHeatingDesignAirFlowMethod() {
    getImpl<detail::SizingZone_Impl>()->resetHeatingDesignAirFlowMethod();
  }

  double SizingZone::heatingDesignAirFlowRate() const {
    return getImpl<detail::SizingZone_Impl>()->heatingDesignAirFlowRate();
  }

  bool SizingZone::isHeatingDesignAirFlowRateDefaulted() const {
    return getImpl<detail::SizingZone_Impl>()->isHeatingDesignAirFlowRateDefaulted();
  }

  bool SizingZone::setHeatingDesignAirFlowRate(double heatingDesignAirFlowRate) {
    return getImpl<detail::SizingZone_Impl>()->setHeatingDesignAirFlowRate(heatingDesignAirFlowRate);
  }

  void SizingZone::resetHeatingDesignAirFlowRate() {
    getImpl<detail::SizingZone_Impl>()->resetHeatingDesignAirFlowRate();
  }

  double SizingZone::heatingMaximumAirFlowperZoneFloorArea() const {
    return getImpl<detail::SizingZone_Impl>()->heatingMaximumAirFlowperZoneFloorArea();
  }

  bool SizingZone::isHeatingMaximumAirFlowperZoneFloorAreaDefaulted() const {
    return getImpl<detail::SizingZone_Impl>()->isHeatingMaximumAirFlowperZoneFloorAreaDefaulted();
  }

  bool SizingZone::setHeatingMaximumAirFlowperZoneFloorArea(double heatingMaximumAirFlowperZoneFloorArea) {
    return getImpl<detail::SizingZone_Impl>()->setHeatingMaximumAirFlowperZoneFloorArea(heatingMaximumAirFlowperZoneFloorArea);
  }

  void SizingZone::resetHeatingMaximumAirFlowperZoneFloorArea() {
    getImpl<detail::SizingZone_Impl>()->resetHeatingMaximumAirFlowperZoneFloorArea();
  }

  double SizingZone::heatingMaximumAirFlow() const {
    return getImpl<detail::SizingZone_Impl>()->heatingMaximumAirFlow();
  }

  bool SizingZone::isHeatingMaximumAirFlowDefaulted() const {
    return getImpl<detail::SizingZone_Impl>()->isHeatingMaximumAirFlowDefaulted();
  }

  bool SizingZone::setHeatingMaximumAirFlow(double heatingMaximumAirFlow) {
    return getImpl<detail::SizingZone_Impl>()->setHeatingMaximumAirFlow(heatingMaximumAirFlow);
  }

  void SizingZone::resetHeatingMaximumAirFlow() {
    getImpl<detail::SizingZone_Impl>()->resetHeatingMaximumAirFlow();
  }

  double SizingZone::heatingMaximumAirFlowFraction() const {
    return getImpl<detail::SizingZone_Impl>()->heatingMaximumAirFlowFraction();
  }

  bool SizingZone::isHeatingMaximumAirFlowFractionDefaulted() const {
    return getImpl<detail::SizingZone_Impl>()->isHeatingMaximumAirFlowFractionDefaulted();
  }

  bool SizingZone::setHeatingMaximumAirFlowFraction(double heatingMaximumAirFlowFraction) {
    return getImpl<detail::SizingZone_Impl>()->setHeatingMaximumAirFlowFraction(heatingMaximumAirFlowFraction);
  }

  void SizingZone::resetHeatingMaximumAirFlowFraction() {
    getImpl<detail::SizingZone_Impl>()->resetHeatingMaximumAirFlowFraction();
  }

  bool SizingZone::accountforDedicatedOutdoorAirSystem() const {
    return getImpl<detail::SizingZone_Impl>()->accountforDedicatedOutdoorAirSystem();
  }

  bool SizingZone::setAccountforDedicatedOutdoorAirSystem(bool accountforDedicatedOutdoorAirSystem) {
    return getImpl<detail::SizingZone_Impl>()->setAccountforDedicatedOutdoorAirSystem(accountforDedicatedOutdoorAirSystem);
  }

  std::string SizingZone::dedicatedOutdoorAirSystemControlStrategy() const {
    return getImpl<detail::SizingZone_Impl>()->dedicatedOutdoorAirSystemControlStrategy();
  }

  bool SizingZone::setDedicatedOutdoorAirSystemControlStrategy(const std::string& dedicatedOutdoorAirSystemControlStrategy) {
    return getImpl<detail::SizingZone_Impl>()->setDedicatedOutdoorAirSystemControlStrategy(dedicatedOutdoorAirSystemControlStrategy);
  }

  boost::optional<double> SizingZone::dedicatedOutdoorAirLowSetpointTemperatureforDesign() const {
    return getImpl<detail::SizingZone_Impl>()->dedicatedOutdoorAirLowSetpointTemperatureforDesign();
  }

  bool SizingZone::isDedicatedOutdoorAirLowSetpointTemperatureforDesignAutosized() const {
    return getImpl<detail::SizingZone_Impl>()->isDedicatedOutdoorAirLowSetpointTemperatureforDesignAutosized();
  }

  bool SizingZone::setDedicatedOutdoorAirLowSetpointTemperatureforDesign(double dedicatedOutdoorAirLowSetpointTemperatureforDesign) {
    return getImpl<detail::SizingZone_Impl>()->setDedicatedOutdoorAirLowSetpointTemperatureforDesign(
      dedicatedOutdoorAirLowSetpointTemperatureforDesign);
  }

  void SizingZone::autosizeDedicatedOutdoorAirLowSetpointTemperatureforDesign() {
    getImpl<detail::SizingZone_Impl>()->autosizeDedicatedOutdoorAirLowSetpointTemperatureforDesign();
  }

  boost::optional<double> SizingZone::dedicatedOutdoorAirHighSetpointTemperatureforDesign() const {
    return getImpl<detail::SizingZone_Impl>()->dedicatedOutdoorAirHighSetpointTemperatureforDesign();
  }

  bool SizingZone::isDedicatedOutdoorAirHighSetpointTemperatureforDesignAutosized() const {
    return getImpl<detail::SizingZone_Impl>()->isDedicatedOutdoorAirHighSetpointTemperatureforDesignAutosized();
  }

  bool SizingZone::setDedicatedOutdoorAirHighSetpointTemperatureforDesign(double dedicatedOutdoorAirHighSetpointTemperatureforDesign) {
    return getImpl<detail::SizingZone_Impl>()->setDedicatedOutdoorAirHighSetpointTemperatureforDesign(
      dedicatedOutdoorAirHighSetpointTemperatureforDesign);
  }

  void SizingZone::autosizeDedicatedOutdoorAirHighSetpointTemperatureforDesign() {
    getImpl<detail::SizingZone_Impl>()->autosizeDedicatedOutdoorAirHighSetpointTemperatureforDesign();
  }

  std::string SizingZone::zoneLoadSizingMethod() const {
    return getImpl<detail::SizingZone_Impl>()->zoneLoadSizingMethod();
  }

  bool SizingZone::setZoneLoadSizingMethod(const std::string& zoneLoadSizingMethod) {
    return getImpl<detail::SizingZone_Impl>()->setZoneLoadSizingMethod(zoneLoadSizingMethod);
  }

  std::string SizingZone::zoneLatentCoolingDesignSupplyAirHumidityRatioInputMethod() const {
    return getImpl<detail::SizingZone_Impl>()->zoneLatentCoolingDesignSupplyAirHumidityRatioInputMethod();
  }

  bool SizingZone::setZoneLatentCoolingDesignSupplyAirHumidityRatioInputMethod(
    const std::string& zoneLatentCoolingDesignSupplyAirHumidityRatioInputMethod) {
    return getImpl<detail::SizingZone_Impl>()->setZoneLatentCoolingDesignSupplyAirHumidityRatioInputMethod(
      zoneLatentCoolingDesignSupplyAirHumidityRatioInputMethod);
  }

  boost::optional<double> SizingZone::zoneDehumidificationDesignSupplyAirHumidityRatio() const {
    return getImpl<detail::SizingZone_Impl>()->zoneDehumidificationDesignSupplyAirHumidityRatio();
  }

  bool SizingZone::setZoneDehumidificationDesignSupplyAirHumidityRatio(double zoneDehumidificationDesignSupplyAirHumidityRatio) {
    return getImpl<detail::SizingZone_Impl>()->setZoneDehumidificationDesignSupplyAirHumidityRatio(zoneDehumidificationDesignSupplyAirHumidityRatio);
  }

  void SizingZone::resetZoneDehumidificationDesignSupplyAirHumidityRatio() {
    getImpl<detail::SizingZone_Impl>()->resetZoneDehumidificationDesignSupplyAirHumidityRatio();
  }

  double SizingZone::zoneCoolingDesignSupplyAirHumidityRatioDifference() const {
    return getImpl<detail::SizingZone_Impl>()->zoneCoolingDesignSupplyAirHumidityRatioDifference();
  }

  bool SizingZone::setZoneCoolingDesignSupplyAirHumidityRatioDifference(double zoneCoolingDesignSupplyAirHumidityRatioDifference) {
    return getImpl<detail::SizingZone_Impl>()->setZoneCoolingDesignSupplyAirHumidityRatioDifference(
      zoneCoolingDesignSupplyAirHumidityRatioDifference);
  }

  std::string SizingZone::zoneLatentHeatingDesignSupplyAirHumidityRatioInputMethod() const {
    return getImpl<detail::SizingZone_Impl>()->zoneLatentHeatingDesignSupplyAirHumidityRatioInputMethod();
  }

  bool SizingZone::setZoneLatentHeatingDesignSupplyAirHumidityRatioInputMethod(
    const std::string& zoneLatentHeatingDesignSupplyAirHumidityRatioInputMethod) {
    return getImpl<detail::SizingZone_Impl>()->setZoneLatentHeatingDesignSupplyAirHumidityRatioInputMethod(
      zoneLatentHeatingDesignSupplyAirHumidityRatioInputMethod);
  }

  boost::optional<double> SizingZone::zoneHumidificationDesignSupplyAirHumidityRatio() const {
    return getImpl<detail::SizingZone_Impl>()->zoneHumidificationDesignSupplyAirHumidityRatio();
  }

  bool SizingZone::setZoneHumidificationDesignSupplyAirHumidityRatio(double zoneHumidificationDesignSupplyAirHumidityRatio) {
    return getImpl<detail::SizingZone_Impl>()->setZoneHumidificationDesignSupplyAirHumidityRatio(zoneHumidificationDesignSupplyAirHumidityRatio);
  }

  void SizingZone::resetZoneHumidificationDesignSupplyAirHumidityRatio() {
    getImpl<detail::SizingZone_Impl>()->resetZoneHumidificationDesignSupplyAirHumidityRatio();
  }

  double SizingZone::zoneHumidificationDesignSupplyAirHumidityRatioDifference() const {
    return getImpl<detail::SizingZone_Impl>()->zoneHumidificationDesignSupplyAirHumidityRatioDifference();
  }

  bool SizingZone::setZoneHumidificationDesignSupplyAirHumidityRatioDifference(double zoneHumidificationDesignSupplyAirHumidityRatioDifference) {
    return getImpl<detail::SizingZone_Impl>()->setZoneHumidificationDesignSupplyAirHumidityRatioDifference(
      zoneHumidificationDesignSupplyAirHumidityRatioDifference);
  }

  double SizingZone::designZoneAirDistributionEffectivenessinCoolingMode() const {
    return getImpl<detail::SizingZone_Impl>()->designZoneAirDistributionEffectivenessinCoolingMode();
  }

  bool SizingZone::isDesignZoneAirDistributionEffectivenessinCoolingModeDefaulted() const {
    return getImpl<detail::SizingZone_Impl>()->isDesignZoneAirDistributionEffectivenessinCoolingModeDefaulted();
  }

  bool SizingZone::setDesignZoneAirDistributionEffectivenessinCoolingMode(double designZoneAirDistributionEffectivenessinCoolingMode) {
    return getImpl<detail::SizingZone_Impl>()->setDesignZoneAirDistributionEffectivenessinCoolingMode(
      designZoneAirDistributionEffectivenessinCoolingMode);
  }

  void SizingZone::resetDesignZoneAirDistributionEffectivenessinCoolingMode() {
    getImpl<detail::SizingZone_Impl>()->resetDesignZoneAirDistributionEffectivenessinCoolingMode();
  }

  double SizingZone::designZoneAirDistributionEffectivenessinHeatingMode() const {
    return getImpl<detail::SizingZone_Impl>()->designZoneAirDistributionEffectivenessinHeatingMode();
  }

  bool SizingZone::isDesignZoneAirDistributionEffectivenessinHeatingModeDefaulted() const {
    return getImpl<detail::SizingZone_Impl>()->isDesignZoneAirDistributionEffectivenessinHeatingModeDefaulted();
  }

  bool SizingZone::setDesignZoneAirDistributionEffectivenessinHeatingMode(double designZoneAirDistributionEffectivenessinHeatingMode) {
    return getImpl<detail::SizingZone_Impl>()->setDesignZoneAirDistributionEffectivenessinHeatingMode(
      designZoneAirDistributionEffectivenessinHeatingMode);
  }

  void SizingZone::resetDesignZoneAirDistributionEffectivenessinHeatingMode() {
    getImpl<detail::SizingZone_Impl>()->resetDesignZoneAirDistributionEffectivenessinHeatingMode();
  }

  double SizingZone::designZoneSecondaryRecirculationFraction() const {
    return getImpl<detail::SizingZone_Impl>()->designZoneSecondaryRecirculationFraction();
  }

  bool SizingZone::isDesignZoneSecondaryRecirculationFractionDefaulted() const {
    return getImpl<detail::SizingZone_Impl>()->isDesignZoneSecondaryRecirculationFractionDefaulted();
  }

  bool SizingZone::setDesignZoneSecondaryRecirculationFraction(double designZoneSecondaryRecirculationFraction) {
    return getImpl<detail::SizingZone_Impl>()->setDesignZoneSecondaryRecirculationFraction(designZoneSecondaryRecirculationFraction);
  }

  void SizingZone::resetDesignZoneSecondaryRecirculationFraction() {
    getImpl<detail::SizingZone_Impl>()->resetDesignZoneSecondaryRecirculationFraction();
  }

  double SizingZone::designMinimumZoneVentilationEfficiency() const {
    return getImpl<detail::SizingZone_Impl>()->designMinimumZoneVentilationEfficiency();
  }

  bool SizingZone::isDesignMinimumZoneVentilationEfficiencyDefaulted() const {
    return getImpl<detail::SizingZone_Impl>()->isDesignMinimumZoneVentilationEfficiencyDefaulted();
  }

  bool SizingZone::setDesignMinimumZoneVentilationEfficiency(double designMinimumZoneVentilationEfficiency) {
    return getImpl<detail::SizingZone_Impl>()->setDesignMinimumZoneVentilationEfficiency(designMinimumZoneVentilationEfficiency);
  }

  void SizingZone::resetDesignMinimumZoneVentilationEfficiency() {
    getImpl<detail::SizingZone_Impl>()->resetDesignMinimumZoneVentilationEfficiency();
  }

  std::string SizingZone::sizingOption() const {
    return getImpl<detail::SizingZone_Impl>()->sizingOption();
  }

  bool SizingZone::setSizingOption(const std::string& sizingOption) {
    return getImpl<detail::SizingZone_Impl>()->setSizingOption(sizingOption);
  }

  std::string SizingZone::heatingCoilSizingMethod() const {
    return getImpl<detail::SizingZone_Impl>()->heatingCoilSizingMethod();
  }

  bool SizingZone::setHeatingCoilSizingMethod(const std::string& heatingCoilSizingMethod) {
    return getImpl<detail::SizingZone_Impl>()->setHeatingCoilSizingMethod(heatingCoilSizingMethod);
  }

  double SizingZone::maximumHeatingCapacityToCoolingLoadSizingRatio() const {
    return getImpl<detail::SizingZone_Impl>()->maximumHeatingCapacityToCoolingLoadSizingRatio();
  }

  bool SizingZone::setMaximumHeatingCapacityToCoolingLoadSizingRatio(double maximumHeatingCapacityToCoolingLoadSizingRatio) {
    return getImpl<detail::SizingZone_Impl>()->setMaximumHeatingCapacityToCoolingLoadSizingRatio(maximumHeatingCapacityToCoolingLoadSizingRatio);
  }

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
  namespace detail {

    namespace {

      constexpr double kDefaultDesignZoneAirDistributionEffectivenessinCoolingMode = 1.0;
      constexpr double kDefaultDesignZoneAirDistributionEffectivenessinHeatingMode = 1.0;
      constexpr double kDefaultDesignZoneSecondaryRecirculationFraction = 0.0;
      constexpr double kDefaultDesignMinimumZoneVentilationEfficiency = 0.0;

    }  // namespace

    boost::optional<openstudio::epmodel::ThermalZone> SizingZone_Impl::optionalThermalZone() const {
      return getObject<openstudio::epmodel::SizingZone>().getModelObjectTarget<openstudio::epmodel::ThermalZone>(
        openstudio::Sizing_ZoneFields::ZoneorZoneListName);
    }

    openstudio::epmodel::ThermalZone SizingZone_Impl::thermalZone() const {
      auto result = optionalThermalZone();
      OS_ASSERT(result);
      return *result;
    }

    boost::optional<openstudio::epmodel::DesignSpecificationOutdoorAirSpaceList> SizingZone_Impl::designSpecificationOutdoorAirSpaceList() const {
      if (auto result = getObject<openstudio::epmodel::SizingZone>().getModelObjectTarget<openstudio::epmodel::ModelObject>(
            openstudio::Sizing_ZoneFields::DesignSpecificationOutdoorAirObjectName)) {
        return result->optionalCast<openstudio::epmodel::DesignSpecificationOutdoorAirSpaceList>();
      }
      return boost::none;
    }

    bool SizingZone_Impl::setDesignSpecificationOutdoorAirSpaceList(
      const openstudio::epmodel::DesignSpecificationOutdoorAirSpaceList& designSpecificationOutdoorAirSpaceList) {
      return setPointer(openstudio::Sizing_ZoneFields::DesignSpecificationOutdoorAirObjectName, designSpecificationOutdoorAirSpaceList.handle(),
                        false);
    }

    std::string SizingZone_Impl::zoneCoolingDesignSupplyAirTemperatureInputMethod() const {
      auto value = getString(openstudio::Sizing_ZoneFields::ZoneCoolingDesignSupplyAirTemperatureInputMethod, true);
      OS_ASSERT(value);
      return *value;
    }

    double SizingZone_Impl::zoneCoolingDesignSupplyAirTemperature() const {
      auto value = getDouble(openstudio::Sizing_ZoneFields::ZoneCoolingDesignSupplyAirTemperature, true);
      OS_ASSERT(value);
      return *value;
    }

    double SizingZone_Impl::zoneCoolingDesignSupplyAirTemperatureDifference() const {
      auto value = getDouble(openstudio::Sizing_ZoneFields::ZoneCoolingDesignSupplyAirTemperatureDifference, true);
      OS_ASSERT(value);
      return *value;
    }

    std::string SizingZone_Impl::zoneHeatingDesignSupplyAirTemperatureInputMethod() const {
      auto value = getString(openstudio::Sizing_ZoneFields::ZoneHeatingDesignSupplyAirTemperatureInputMethod, true);
      OS_ASSERT(value);
      return *value;
    }

    double SizingZone_Impl::zoneHeatingDesignSupplyAirTemperature() const {
      auto value = getDouble(openstudio::Sizing_ZoneFields::ZoneHeatingDesignSupplyAirTemperature, true);
      OS_ASSERT(value);
      return *value;
    }

    double SizingZone_Impl::zoneHeatingDesignSupplyAirTemperatureDifference() const {
      auto value = getDouble(openstudio::Sizing_ZoneFields::ZoneHeatingDesignSupplyAirTemperatureDifference, true);
      OS_ASSERT(value);
      return *value;
    }

    double SizingZone_Impl::zoneCoolingDesignSupplyAirHumidityRatio() const {
      auto value = getDouble(openstudio::Sizing_ZoneFields::ZoneCoolingDesignSupplyAirHumidityRatio, true);
      OS_ASSERT(value);
      return *value;
    }

    double SizingZone_Impl::zoneHeatingDesignSupplyAirHumidityRatio() const {
      auto value = getDouble(openstudio::Sizing_ZoneFields::ZoneHeatingDesignSupplyAirHumidityRatio, true);
      OS_ASSERT(value);
      return *value;
    }

    boost::optional<double> SizingZone_Impl::zoneHeatingSizingFactor() const {
      return getDouble(openstudio::Sizing_ZoneFields::ZoneHeatingSizingFactor, true);
    }

    boost::optional<double> SizingZone_Impl::zoneCoolingSizingFactor() const {
      return getDouble(openstudio::Sizing_ZoneFields::ZoneCoolingSizingFactor, true);
    }

    std::string SizingZone_Impl::coolingDesignAirFlowMethod() const {
      auto value = getString(openstudio::Sizing_ZoneFields::CoolingDesignAirFlowMethod, true);
      OS_ASSERT(value);
      return *value;
    }

    bool SizingZone_Impl::isCoolingDesignAirFlowMethodDefaulted() const {
      return isEmpty(openstudio::Sizing_ZoneFields::CoolingDesignAirFlowMethod);
    }

    double SizingZone_Impl::coolingDesignAirFlowRate() const {
      auto value = getDouble(openstudio::Sizing_ZoneFields::CoolingDesignAirFlowRate, true);
      OS_ASSERT(value);
      return *value;
    }

    bool SizingZone_Impl::isCoolingDesignAirFlowRateDefaulted() const {
      return isEmpty(openstudio::Sizing_ZoneFields::CoolingDesignAirFlowRate);
    }

    double SizingZone_Impl::coolingMinimumAirFlowperZoneFloorArea() const {
      auto value = getDouble(openstudio::Sizing_ZoneFields::CoolingMinimumAirFlowperZoneFloorArea, true);
      OS_ASSERT(value);
      return *value;
    }

    bool SizingZone_Impl::isCoolingMinimumAirFlowperZoneFloorAreaDefaulted() const {
      return isEmpty(openstudio::Sizing_ZoneFields::CoolingMinimumAirFlowperZoneFloorArea);
    }

    double SizingZone_Impl::coolingMinimumAirFlow() const {
      auto value = getDouble(openstudio::Sizing_ZoneFields::CoolingMinimumAirFlow, true);
      OS_ASSERT(value);
      return *value;
    }

    bool SizingZone_Impl::isCoolingMinimumAirFlowDefaulted() const {
      return isEmpty(openstudio::Sizing_ZoneFields::CoolingMinimumAirFlow);
    }

    double SizingZone_Impl::coolingMinimumAirFlowFraction() const {
      auto value = getDouble(openstudio::Sizing_ZoneFields::CoolingMinimumAirFlowFraction, true);
      OS_ASSERT(value);
      return *value;
    }

    bool SizingZone_Impl::isCoolingMinimumAirFlowFractionDefaulted() const {
      return isEmpty(openstudio::Sizing_ZoneFields::CoolingMinimumAirFlowFraction);
    }

    std::string SizingZone_Impl::heatingDesignAirFlowMethod() const {
      auto value = getString(openstudio::Sizing_ZoneFields::HeatingDesignAirFlowMethod, true);
      OS_ASSERT(value);
      return *value;
    }

    bool SizingZone_Impl::isHeatingDesignAirFlowMethodDefaulted() const {
      return isEmpty(openstudio::Sizing_ZoneFields::HeatingDesignAirFlowMethod);
    }

    double SizingZone_Impl::heatingDesignAirFlowRate() const {
      auto value = getDouble(openstudio::Sizing_ZoneFields::HeatingDesignAirFlowRate, true);
      OS_ASSERT(value);
      return *value;
    }

    bool SizingZone_Impl::isHeatingDesignAirFlowRateDefaulted() const {
      return isEmpty(openstudio::Sizing_ZoneFields::HeatingDesignAirFlowRate);
    }

    double SizingZone_Impl::heatingMaximumAirFlowperZoneFloorArea() const {
      auto value = getDouble(openstudio::Sizing_ZoneFields::HeatingMaximumAirFlowperZoneFloorArea, true);
      OS_ASSERT(value);
      return *value;
    }

    bool SizingZone_Impl::isHeatingMaximumAirFlowperZoneFloorAreaDefaulted() const {
      return isEmpty(openstudio::Sizing_ZoneFields::HeatingMaximumAirFlowperZoneFloorArea);
    }

    double SizingZone_Impl::heatingMaximumAirFlow() const {
      auto value = getDouble(openstudio::Sizing_ZoneFields::HeatingMaximumAirFlow, true);
      OS_ASSERT(value);
      return *value;
    }

    bool SizingZone_Impl::isHeatingMaximumAirFlowDefaulted() const {
      return isEmpty(openstudio::Sizing_ZoneFields::HeatingMaximumAirFlow);
    }

    double SizingZone_Impl::heatingMaximumAirFlowFraction() const {
      auto value = getDouble(openstudio::Sizing_ZoneFields::HeatingMaximumAirFlowFraction, true);
      OS_ASSERT(value);
      return *value;
    }

    bool SizingZone_Impl::isHeatingMaximumAirFlowFractionDefaulted() const {
      return isEmpty(openstudio::Sizing_ZoneFields::HeatingMaximumAirFlowFraction);
    }

    bool SizingZone_Impl::accountforDedicatedOutdoorAirSystem() const {
      auto value = getString(openstudio::Sizing_ZoneFields::AccountforDedicatedOutdoorAirSystem, true);
      OS_ASSERT(value);
      return openstudio::istringEqual(*value, "Yes");
    }

    std::string SizingZone_Impl::dedicatedOutdoorAirSystemControlStrategy() const {
      auto value = getString(openstudio::Sizing_ZoneFields::DedicatedOutdoorAirSystemControlStrategy, true);
      OS_ASSERT(value);
      return *value;
    }

    boost::optional<double> SizingZone_Impl::dedicatedOutdoorAirLowSetpointTemperatureforDesign() const {
      return getDouble(openstudio::Sizing_ZoneFields::DedicatedOutdoorAirLowSetpointTemperatureforDesign, true);
    }

    bool SizingZone_Impl::isDedicatedOutdoorAirLowSetpointTemperatureforDesignAutosized() const {
      if (auto value = getString(openstudio::Sizing_ZoneFields::DedicatedOutdoorAirLowSetpointTemperatureforDesign, true)) {
        return openstudio::istringEqual(*value, "autosize");
      }
      return false;
    }

    boost::optional<double> SizingZone_Impl::dedicatedOutdoorAirHighSetpointTemperatureforDesign() const {
      return getDouble(openstudio::Sizing_ZoneFields::DedicatedOutdoorAirHighSetpointTemperatureforDesign, true);
    }

    bool SizingZone_Impl::isDedicatedOutdoorAirHighSetpointTemperatureforDesignAutosized() const {
      if (auto value = getString(openstudio::Sizing_ZoneFields::DedicatedOutdoorAirHighSetpointTemperatureforDesign, true)) {
        return openstudio::istringEqual(*value, "autosize");
      }
      return false;
    }

    std::string SizingZone_Impl::zoneLoadSizingMethod() const {
      auto value = getString(openstudio::Sizing_ZoneFields::ZoneLoadSizingMethod, true);
      OS_ASSERT(value);
      return *value;
    }

    std::string SizingZone_Impl::zoneLatentCoolingDesignSupplyAirHumidityRatioInputMethod() const {
      auto value = getString(openstudio::Sizing_ZoneFields::ZoneLatentCoolingDesignSupplyAirHumidityRatioInputMethod, true);
      OS_ASSERT(value);
      return *value;
    }

    boost::optional<double> SizingZone_Impl::zoneDehumidificationDesignSupplyAirHumidityRatio() const {
      return getDouble(openstudio::Sizing_ZoneFields::ZoneDehumidificationDesignSupplyAirHumidityRatio, true);
    }

    double SizingZone_Impl::zoneCoolingDesignSupplyAirHumidityRatioDifference() const {
      auto value = getDouble(openstudio::Sizing_ZoneFields::ZoneCoolingDesignSupplyAirHumidityRatioDifference, true);
      OS_ASSERT(value);
      return *value;
    }

    std::string SizingZone_Impl::zoneLatentHeatingDesignSupplyAirHumidityRatioInputMethod() const {
      auto value = getString(openstudio::Sizing_ZoneFields::ZoneLatentHeatingDesignSupplyAirHumidityRatioInputMethod, true);
      OS_ASSERT(value);
      return *value;
    }

    boost::optional<double> SizingZone_Impl::zoneHumidificationDesignSupplyAirHumidityRatio() const {
      return getDouble(openstudio::Sizing_ZoneFields::ZoneHumidificationDesignSupplyAirHumidityRatio, true);
    }

    double SizingZone_Impl::zoneHumidificationDesignSupplyAirHumidityRatioDifference() const {
      auto value = getDouble(openstudio::Sizing_ZoneFields::ZoneHumidificationDesignSupplyAirHumidityRatioDifference, true);
      OS_ASSERT(value);
      return *value;
    }

    std::string SizingZone_Impl::sizingOption() const {
      auto value = getString(openstudio::Sizing_ZoneFields::TypeofSpaceSumtoUse, true);
      OS_ASSERT(value);
      return *value;
    }

    std::string SizingZone_Impl::heatingCoilSizingMethod() const {
      auto value = getString(openstudio::Sizing_ZoneFields::HeatingCoilSizingMethod, true);
      OS_ASSERT(value);
      return *value;
    }

    double SizingZone_Impl::maximumHeatingCapacityToCoolingLoadSizingRatio() const {
      auto value = getDouble(openstudio::Sizing_ZoneFields::MaximumHeatingCapacityToCoolingLoadSizingRatio, true);
      OS_ASSERT(value);
      return *value;
    }

    bool SizingZone_Impl::setZoneCoolingDesignSupplyAirTemperatureInputMethod(const std::string& value) {
      return setString(openstudio::Sizing_ZoneFields::ZoneCoolingDesignSupplyAirTemperatureInputMethod, value);
    }

    bool SizingZone_Impl::setZoneCoolingDesignSupplyAirTemperature(double zoneCoolingDesignSupplyAirTemperature) {
      const bool result = setDouble(openstudio::Sizing_ZoneFields::ZoneCoolingDesignSupplyAirTemperature, zoneCoolingDesignSupplyAirTemperature);
      OS_ASSERT(result);
      return result;
    }

    bool SizingZone_Impl::setZoneCoolingDesignSupplyAirTemperatureDifference(double value) {
      const bool result = setDouble(openstudio::Sizing_ZoneFields::ZoneCoolingDesignSupplyAirTemperatureDifference, value);
      OS_ASSERT(result);
      return result;
    }

    bool SizingZone_Impl::setZoneHeatingDesignSupplyAirTemperatureInputMethod(const std::string& value) {
      return setString(openstudio::Sizing_ZoneFields::ZoneHeatingDesignSupplyAirTemperatureInputMethod, value);
    }

    bool SizingZone_Impl::setZoneHeatingDesignSupplyAirTemperature(double zoneHeatingDesignSupplyAirTemperature) {
      const bool result = setDouble(openstudio::Sizing_ZoneFields::ZoneHeatingDesignSupplyAirTemperature, zoneHeatingDesignSupplyAirTemperature);
      OS_ASSERT(result);
      return result;
    }

    bool SizingZone_Impl::setZoneHeatingDesignSupplyAirTemperatureDifference(double value) {
      const bool result = setDouble(openstudio::Sizing_ZoneFields::ZoneHeatingDesignSupplyAirTemperatureDifference, value);
      OS_ASSERT(result);
      return result;
    }

    bool SizingZone_Impl::setZoneCoolingDesignSupplyAirHumidityRatio(double zoneCoolingDesignSupplyAirHumidityRatio) {
      return setDouble(openstudio::Sizing_ZoneFields::ZoneCoolingDesignSupplyAirHumidityRatio, zoneCoolingDesignSupplyAirHumidityRatio);
    }

    bool SizingZone_Impl::setZoneHeatingDesignSupplyAirHumidityRatio(double zoneHeatingDesignSupplyAirHumidityRatio) {
      return setDouble(openstudio::Sizing_ZoneFields::ZoneHeatingDesignSupplyAirHumidityRatio, zoneHeatingDesignSupplyAirHumidityRatio);
    }

    bool SizingZone_Impl::setZoneHeatingSizingFactor(double zoneHeatingSizingFactor) {
      return setDouble(openstudio::Sizing_ZoneFields::ZoneHeatingSizingFactor, zoneHeatingSizingFactor);
    }

    void SizingZone_Impl::resetZoneHeatingSizingFactor() {
      OS_ASSERT(setString(openstudio::Sizing_ZoneFields::ZoneHeatingSizingFactor, ""));
    }

    bool SizingZone_Impl::setZoneCoolingSizingFactor(double zoneCoolingSizingFactor) {
      return setDouble(openstudio::Sizing_ZoneFields::ZoneCoolingSizingFactor, zoneCoolingSizingFactor);
    }

    void SizingZone_Impl::resetZoneCoolingSizingFactor() {
      OS_ASSERT(setString(openstudio::Sizing_ZoneFields::ZoneCoolingSizingFactor, ""));
    }

    bool SizingZone_Impl::setCoolingDesignAirFlowMethod(const std::string& coolingDesignAirFlowMethod) {
      return setString(openstudio::Sizing_ZoneFields::CoolingDesignAirFlowMethod, coolingDesignAirFlowMethod);
    }

    void SizingZone_Impl::resetCoolingDesignAirFlowMethod() {
      OS_ASSERT(setString(openstudio::Sizing_ZoneFields::CoolingDesignAirFlowMethod, ""));
    }

    bool SizingZone_Impl::setCoolingDesignAirFlowRate(double coolingDesignAirFlowRate) {
      return setDouble(openstudio::Sizing_ZoneFields::CoolingDesignAirFlowRate, coolingDesignAirFlowRate);
    }

    void SizingZone_Impl::resetCoolingDesignAirFlowRate() {
      OS_ASSERT(setString(openstudio::Sizing_ZoneFields::CoolingDesignAirFlowRate, ""));
    }

    bool SizingZone_Impl::setCoolingMinimumAirFlowperZoneFloorArea(double coolingMinimumAirFlowperZoneFloorArea) {
      return setDouble(openstudio::Sizing_ZoneFields::CoolingMinimumAirFlowperZoneFloorArea, coolingMinimumAirFlowperZoneFloorArea);
    }

    void SizingZone_Impl::resetCoolingMinimumAirFlowperZoneFloorArea() {
      OS_ASSERT(setString(openstudio::Sizing_ZoneFields::CoolingMinimumAirFlowperZoneFloorArea, ""));
    }

    bool SizingZone_Impl::setCoolingMinimumAirFlow(double coolingMinimumAirFlow) {
      return setDouble(openstudio::Sizing_ZoneFields::CoolingMinimumAirFlow, coolingMinimumAirFlow);
    }

    void SizingZone_Impl::resetCoolingMinimumAirFlow() {
      OS_ASSERT(setString(openstudio::Sizing_ZoneFields::CoolingMinimumAirFlow, ""));
    }

    bool SizingZone_Impl::setCoolingMinimumAirFlowFraction(double coolingMinimumAirFlowFraction) {
      return setDouble(openstudio::Sizing_ZoneFields::CoolingMinimumAirFlowFraction, coolingMinimumAirFlowFraction);
    }

    void SizingZone_Impl::resetCoolingMinimumAirFlowFraction() {
      OS_ASSERT(setString(openstudio::Sizing_ZoneFields::CoolingMinimumAirFlowFraction, ""));
    }

    bool SizingZone_Impl::setHeatingDesignAirFlowMethod(const std::string& heatingDesignAirFlowMethod) {
      return setString(openstudio::Sizing_ZoneFields::HeatingDesignAirFlowMethod, heatingDesignAirFlowMethod);
    }

    void SizingZone_Impl::resetHeatingDesignAirFlowMethod() {
      OS_ASSERT(setString(openstudio::Sizing_ZoneFields::HeatingDesignAirFlowMethod, ""));
    }

    bool SizingZone_Impl::setHeatingDesignAirFlowRate(double heatingDesignAirFlowRate) {
      return setDouble(openstudio::Sizing_ZoneFields::HeatingDesignAirFlowRate, heatingDesignAirFlowRate);
    }

    void SizingZone_Impl::resetHeatingDesignAirFlowRate() {
      OS_ASSERT(setString(openstudio::Sizing_ZoneFields::HeatingDesignAirFlowRate, ""));
    }

    bool SizingZone_Impl::setHeatingMaximumAirFlowperZoneFloorArea(double heatingMaximumAirFlowperZoneFloorArea) {
      return setDouble(openstudio::Sizing_ZoneFields::HeatingMaximumAirFlowperZoneFloorArea, heatingMaximumAirFlowperZoneFloorArea);
    }

    void SizingZone_Impl::resetHeatingMaximumAirFlowperZoneFloorArea() {
      OS_ASSERT(setString(openstudio::Sizing_ZoneFields::HeatingMaximumAirFlowperZoneFloorArea, ""));
    }

    bool SizingZone_Impl::setHeatingMaximumAirFlow(double heatingMaximumAirFlow) {
      return setDouble(openstudio::Sizing_ZoneFields::HeatingMaximumAirFlow, heatingMaximumAirFlow);
    }

    void SizingZone_Impl::resetHeatingMaximumAirFlow() {
      OS_ASSERT(setString(openstudio::Sizing_ZoneFields::HeatingMaximumAirFlow, ""));
    }

    bool SizingZone_Impl::setHeatingMaximumAirFlowFraction(double heatingMaximumAirFlowFraction) {
      return setDouble(openstudio::Sizing_ZoneFields::HeatingMaximumAirFlowFraction, heatingMaximumAirFlowFraction);
    }

    void SizingZone_Impl::resetHeatingMaximumAirFlowFraction() {
      OS_ASSERT(setString(openstudio::Sizing_ZoneFields::HeatingMaximumAirFlowFraction, ""));
    }

    bool SizingZone_Impl::setAccountforDedicatedOutdoorAirSystem(bool accountforDedicatedOutdoorAirSystem) {
      const bool result =
        setString(openstudio::Sizing_ZoneFields::AccountforDedicatedOutdoorAirSystem, accountforDedicatedOutdoorAirSystem ? "Yes" : "No");
      OS_ASSERT(result);
      return result;
    }

    bool SizingZone_Impl::setDedicatedOutdoorAirSystemControlStrategy(const std::string& dedicatedOutdoorAirSystemControlStrategy) {
      return setString(openstudio::Sizing_ZoneFields::DedicatedOutdoorAirSystemControlStrategy, dedicatedOutdoorAirSystemControlStrategy);
    }

    bool SizingZone_Impl::setDedicatedOutdoorAirLowSetpointTemperatureforDesign(double dedicatedOutdoorAirLowSetpointTemperatureforDesign) {
      const bool result = setDouble(openstudio::Sizing_ZoneFields::DedicatedOutdoorAirLowSetpointTemperatureforDesign,
                                    dedicatedOutdoorAirLowSetpointTemperatureforDesign);
      OS_ASSERT(result);
      return result;
    }

    void SizingZone_Impl::autosizeDedicatedOutdoorAirLowSetpointTemperatureforDesign() {
      OS_ASSERT(setString(openstudio::Sizing_ZoneFields::DedicatedOutdoorAirLowSetpointTemperatureforDesign, "autosize"));
    }

    bool SizingZone_Impl::setDedicatedOutdoorAirHighSetpointTemperatureforDesign(double dedicatedOutdoorAirHighSetpointTemperatureforDesign) {
      const bool result = setDouble(openstudio::Sizing_ZoneFields::DedicatedOutdoorAirHighSetpointTemperatureforDesign,
                                    dedicatedOutdoorAirHighSetpointTemperatureforDesign);
      OS_ASSERT(result);
      return result;
    }

    void SizingZone_Impl::autosizeDedicatedOutdoorAirHighSetpointTemperatureforDesign() {
      OS_ASSERT(setString(openstudio::Sizing_ZoneFields::DedicatedOutdoorAirHighSetpointTemperatureforDesign, "autosize"));
    }

    bool SizingZone_Impl::setZoneLoadSizingMethod(const std::string& zoneLoadSizingMethod) {
      return setString(openstudio::Sizing_ZoneFields::ZoneLoadSizingMethod, zoneLoadSizingMethod);
    }

    bool SizingZone_Impl::setZoneLatentCoolingDesignSupplyAirHumidityRatioInputMethod(
      const std::string& zoneLatentCoolingDesignSupplyAirHumidityRatioInputMethod) {
      return setString(openstudio::Sizing_ZoneFields::ZoneLatentCoolingDesignSupplyAirHumidityRatioInputMethod,
                       zoneLatentCoolingDesignSupplyAirHumidityRatioInputMethod);
    }

    bool SizingZone_Impl::setZoneDehumidificationDesignSupplyAirHumidityRatio(double zoneDehumidificationDesignSupplyAirHumidityRatio) {
      return setDouble(openstudio::Sizing_ZoneFields::ZoneDehumidificationDesignSupplyAirHumidityRatio,
                       zoneDehumidificationDesignSupplyAirHumidityRatio);
    }

    void SizingZone_Impl::resetZoneDehumidificationDesignSupplyAirHumidityRatio() {
      OS_ASSERT(setString(openstudio::Sizing_ZoneFields::ZoneDehumidificationDesignSupplyAirHumidityRatio, ""));
    }

    bool SizingZone_Impl::setZoneCoolingDesignSupplyAirHumidityRatioDifference(double zoneCoolingDesignSupplyAirHumidityRatioDifference) {
      return setDouble(openstudio::Sizing_ZoneFields::ZoneCoolingDesignSupplyAirHumidityRatioDifference,
                       zoneCoolingDesignSupplyAirHumidityRatioDifference);
    }

    bool SizingZone_Impl::setZoneLatentHeatingDesignSupplyAirHumidityRatioInputMethod(
      const std::string& zoneLatentHeatingDesignSupplyAirHumidityRatioInputMethod) {
      return setString(openstudio::Sizing_ZoneFields::ZoneLatentHeatingDesignSupplyAirHumidityRatioInputMethod,
                       zoneLatentHeatingDesignSupplyAirHumidityRatioInputMethod);
    }

    bool SizingZone_Impl::setZoneHumidificationDesignSupplyAirHumidityRatio(double zoneHumidificationDesignSupplyAirHumidityRatio) {
      return setDouble(openstudio::Sizing_ZoneFields::ZoneHumidificationDesignSupplyAirHumidityRatio, zoneHumidificationDesignSupplyAirHumidityRatio);
    }

    void SizingZone_Impl::resetZoneHumidificationDesignSupplyAirHumidityRatio() {
      OS_ASSERT(setString(openstudio::Sizing_ZoneFields::ZoneHumidificationDesignSupplyAirHumidityRatio, ""));
    }

    bool
      SizingZone_Impl::setZoneHumidificationDesignSupplyAirHumidityRatioDifference(double zoneHumidificationDesignSupplyAirHumidityRatioDifference) {
      return setDouble(openstudio::Sizing_ZoneFields::ZoneHumidificationDesignSupplyAirHumidityRatioDifference,
                       zoneHumidificationDesignSupplyAirHumidityRatioDifference);
    }

    boost::optional<openstudio::epmodel::ModelObject> SizingZone_Impl::designSpecificationZoneAirDistribution() const {
      if (auto result = getObject<openstudio::epmodel::SizingZone>().getModelObjectTarget<openstudio::epmodel::ModelObject>(
            openstudio::Sizing_ZoneFields::DesignSpecificationZoneAirDistributionObjectName)) {
        if (result->iddObject().type() == openstudio::IddObjectType::DesignSpecification_ZoneAirDistribution) {
          return result;
        }
      }
      return boost::none;
    }

    boost::optional<openstudio::epmodel::ModelObject> SizingZone_Impl::getOrCreateDesignSpecificationZoneAirDistribution() {
      if (auto existing = designSpecificationZoneAirDistribution()) {
        return existing;
      }

      auto designSpecificationZoneAirDistribution =
        openstudio::epmodel::ModelObject::create(openstudio::IddObjectType::DesignSpecification_ZoneAirDistribution, model(), true);

      if (auto zone = optionalThermalZone()) {
        (void)designSpecificationZoneAirDistribution.setName(zone->nameString() + " Design Spec Zone Air Dist");
      }

      if (!setPointer(openstudio::Sizing_ZoneFields::DesignSpecificationZoneAirDistributionObjectName,
                      designSpecificationZoneAirDistribution.handle(), false)) {
        return boost::none;
      }
      return designSpecificationZoneAirDistribution;
    }

    double SizingZone_Impl::designZoneAirDistributionEffectivenessinCoolingMode() const {
      if (auto designSpecification = designSpecificationZoneAirDistribution()) {
        if (auto value = designSpecification->getDouble(
              openstudio::DesignSpecification_ZoneAirDistributionFields::ZoneAirDistributionEffectivenessinCoolingMode, false)) {
          return *value;
        }
      }
      return kDefaultDesignZoneAirDistributionEffectivenessinCoolingMode;
    }

    bool SizingZone_Impl::isDesignZoneAirDistributionEffectivenessinCoolingModeDefaulted() const {
      if (auto designSpecification = designSpecificationZoneAirDistribution()) {
        return !designSpecification->getDouble(
          openstudio::DesignSpecification_ZoneAirDistributionFields::ZoneAirDistributionEffectivenessinCoolingMode, false);
      }
      return true;
    }

    double SizingZone_Impl::designZoneAirDistributionEffectivenessinHeatingMode() const {
      if (auto designSpecification = designSpecificationZoneAirDistribution()) {
        if (auto value = designSpecification->getDouble(
              openstudio::DesignSpecification_ZoneAirDistributionFields::ZoneAirDistributionEffectivenessinHeatingMode, false)) {
          return *value;
        }
      }
      return kDefaultDesignZoneAirDistributionEffectivenessinHeatingMode;
    }

    bool SizingZone_Impl::isDesignZoneAirDistributionEffectivenessinHeatingModeDefaulted() const {
      if (auto designSpecification = designSpecificationZoneAirDistribution()) {
        return !designSpecification->getDouble(
          openstudio::DesignSpecification_ZoneAirDistributionFields::ZoneAirDistributionEffectivenessinHeatingMode, false);
      }
      return true;
    }

    double SizingZone_Impl::designZoneSecondaryRecirculationFraction() const {
      if (auto designSpecification = designSpecificationZoneAirDistribution()) {
        if (auto value =
              designSpecification->getDouble(openstudio::DesignSpecification_ZoneAirDistributionFields::ZoneSecondaryRecirculationFraction, false)) {
          return *value;
        }
      }
      return kDefaultDesignZoneSecondaryRecirculationFraction;
    }

    bool SizingZone_Impl::isDesignZoneSecondaryRecirculationFractionDefaulted() const {
      if (auto designSpecification = designSpecificationZoneAirDistribution()) {
        return !designSpecification->getDouble(openstudio::DesignSpecification_ZoneAirDistributionFields::ZoneSecondaryRecirculationFraction, false);
      }
      return true;
    }

    double SizingZone_Impl::designMinimumZoneVentilationEfficiency() const {
      if (auto designSpecification = designSpecificationZoneAirDistribution()) {
        if (auto value =
              designSpecification->getDouble(openstudio::DesignSpecification_ZoneAirDistributionFields::MinimumZoneVentilationEfficiency, false)) {
          return *value;
        }
      }
      return kDefaultDesignMinimumZoneVentilationEfficiency;
    }

    bool SizingZone_Impl::isDesignMinimumZoneVentilationEfficiencyDefaulted() const {
      if (auto designSpecification = designSpecificationZoneAirDistribution()) {
        return !designSpecification->getDouble(openstudio::DesignSpecification_ZoneAirDistributionFields::MinimumZoneVentilationEfficiency, false);
      }
      return true;
    }

    bool SizingZone_Impl::setDesignZoneAirDistributionEffectivenessinCoolingMode(double designZoneAirDistributionEffectivenessinCoolingMode) {
      auto designSpecification = getOrCreateDesignSpecificationZoneAirDistribution();
      if (!designSpecification) {
        return false;
      }
      return designSpecification->setDouble(openstudio::DesignSpecification_ZoneAirDistributionFields::ZoneAirDistributionEffectivenessinCoolingMode,
                                            designZoneAirDistributionEffectivenessinCoolingMode);
    }

    void SizingZone_Impl::resetDesignZoneAirDistributionEffectivenessinCoolingMode() {
      if (auto designSpecification = designSpecificationZoneAirDistribution()) {
        bool result = designSpecification->setString(
          openstudio::DesignSpecification_ZoneAirDistributionFields::ZoneAirDistributionEffectivenessinCoolingMode, "");
        OS_ASSERT(result);
      }
    }

    bool SizingZone_Impl::setDesignZoneAirDistributionEffectivenessinHeatingMode(double designZoneAirDistributionEffectivenessinHeatingMode) {
      auto designSpecification = getOrCreateDesignSpecificationZoneAirDistribution();
      if (!designSpecification) {
        return false;
      }
      return designSpecification->setDouble(openstudio::DesignSpecification_ZoneAirDistributionFields::ZoneAirDistributionEffectivenessinHeatingMode,
                                            designZoneAirDistributionEffectivenessinHeatingMode);
    }

    void SizingZone_Impl::resetDesignZoneAirDistributionEffectivenessinHeatingMode() {
      if (auto designSpecification = designSpecificationZoneAirDistribution()) {
        bool result = designSpecification->setString(
          openstudio::DesignSpecification_ZoneAirDistributionFields::ZoneAirDistributionEffectivenessinHeatingMode, "");
        OS_ASSERT(result);
      }
    }

    bool SizingZone_Impl::setDesignZoneSecondaryRecirculationFraction(double designZoneSecondaryRecirculationFraction) {
      auto designSpecification = getOrCreateDesignSpecificationZoneAirDistribution();
      if (!designSpecification) {
        return false;
      }
      return designSpecification->setDouble(openstudio::DesignSpecification_ZoneAirDistributionFields::ZoneSecondaryRecirculationFraction,
                                            designZoneSecondaryRecirculationFraction);
    }

    void SizingZone_Impl::resetDesignZoneSecondaryRecirculationFraction() {
      if (auto designSpecification = designSpecificationZoneAirDistribution()) {
        bool result =
          designSpecification->setString(openstudio::DesignSpecification_ZoneAirDistributionFields::ZoneSecondaryRecirculationFraction, "");
        OS_ASSERT(result);
      }
    }

    bool SizingZone_Impl::setDesignMinimumZoneVentilationEfficiency(double designMinimumZoneVentilationEfficiency) {
      auto designSpecification = getOrCreateDesignSpecificationZoneAirDistribution();
      if (!designSpecification) {
        return false;
      }
      return designSpecification->setDouble(openstudio::DesignSpecification_ZoneAirDistributionFields::MinimumZoneVentilationEfficiency,
                                            designMinimumZoneVentilationEfficiency);
    }

    void SizingZone_Impl::resetDesignMinimumZoneVentilationEfficiency() {
      if (auto designSpecification = designSpecificationZoneAirDistribution()) {
        bool result = designSpecification->setString(openstudio::DesignSpecification_ZoneAirDistributionFields::MinimumZoneVentilationEfficiency, "");
        OS_ASSERT(result);
      }
    }

    bool SizingZone_Impl::setSizingOption(const std::string& sizingOption) {
      return setString(openstudio::Sizing_ZoneFields::TypeofSpaceSumtoUse, sizingOption);
    }

    bool SizingZone_Impl::setHeatingCoilSizingMethod(const std::string& heatingCoilSizingMethod) {
      return setString(openstudio::Sizing_ZoneFields::HeatingCoilSizingMethod, heatingCoilSizingMethod);
    }

    bool SizingZone_Impl::setMaximumHeatingCapacityToCoolingLoadSizingRatio(double maximumHeatingCapacityToCoolingLoadSizingRatio) {
      return setDouble(openstudio::Sizing_ZoneFields::MaximumHeatingCapacityToCoolingLoadSizingRatio, maximumHeatingCapacityToCoolingLoadSizingRatio);
    }

    std::vector<std::string> SizingZone_Impl::coolingDesignAirFlowMethodValues() const {
      return openstudio::epmodel::SizingZone::coolingDesignAirFlowMethodValues();
    }

    std::vector<std::string> SizingZone_Impl::heatingDesignAirFlowMethodValues() const {
      return openstudio::epmodel::SizingZone::heatingDesignAirFlowMethodValues();
    }

    std::vector<std::string> SizingZone_Impl::zoneCoolingDesignSupplyAirTemperatureInputMethodValues() const {
      return openstudio::epmodel::SizingZone::zoneCoolingDesignSupplyAirTemperatureInputMethodValues();
    }

    std::vector<std::string> SizingZone_Impl::zoneHeatingDesignSupplyAirTemperatureInputMethodValues() const {
      return openstudio::epmodel::SizingZone::zoneHeatingDesignSupplyAirTemperatureInputMethodValues();
    }

    std::vector<std::string> SizingZone_Impl::zoneLoadSizingMethodValues() const {
      return openstudio::epmodel::SizingZone::zoneLoadSizingMethodValues();
    }

    std::vector<std::string> SizingZone_Impl::zoneLatentCoolingDesignSupplyAirHumidityRatioInputMethodValues() const {
      return openstudio::epmodel::SizingZone::zoneLatentCoolingDesignSupplyAirHumidityRatioInputMethodValues();
    }

    std::vector<std::string> SizingZone_Impl::zoneLatentHeatingDesignSupplyAirHumidityRatioInputMethodValues() const {
      return openstudio::epmodel::SizingZone::zoneLatentHeatingDesignSupplyAirHumidityRatioInputMethodValues();
    }

    std::vector<std::string> SizingZone_Impl::validSizingOptionValues() const {
      return openstudio::epmodel::SizingZone::validSizingOptionValues();
    }

    std::vector<std::string> SizingZone_Impl::heatingCoilSizingMethodValues() const {
      return openstudio::epmodel::SizingZone::heatingCoilSizingMethodValues();
    }

    void SizingZone_Impl::doCanonicalize(LoadContext& context) {
      auto thisSizingZone = getObject<openstudio::epmodel::SizingZone>();
      auto zoneOrZoneListTarget =
        thisSizingZone.getModelObjectTarget<openstudio::epmodel::ModelObject>(openstudio::Sizing_ZoneFields::ZoneorZoneListName);
      auto zone = optionalThermalZone();
      if (!zone) {
        if (zoneOrZoneListTarget) {
          detail::addLoadWarning(
            context, "Sizing:Zone '" + thisSizingZone.nameString()
                       + "' references a non-ThermalZone target for Zone or ZoneList Name. ZoneList normalization is not yet implemented.");
        }
        return;
      }
      // Canonical prerequisite: zone-level OA normalization depends on Space -> ThermalZone links.
      // We canonicalize the owning ThermalZone first so downstream lookups are stable.
      zone->getImpl<openstudio::epmodel::detail::ThermalZone_Impl>()->canonicalize(context);

      boost::optional<openstudio::epmodel::DesignSpecificationOutdoorAir> directDSOA;
      if (auto dsoaObject = getObject<openstudio::epmodel::SizingZone>().getModelObjectTarget<openstudio::epmodel::ModelObject>(
            openstudio::Sizing_ZoneFields::DesignSpecificationOutdoorAirObjectName)) {
        directDSOA = dsoaObject->optionalCast<openstudio::epmodel::DesignSpecificationOutdoorAir>();
      }
      auto sourceSpaceList = designSpecificationOutdoorAirSpaceList();
      if (!directDSOA && !sourceSpaceList) {
        return;
      }

      std::vector<openstudio::epmodel::Space> zoneSpaces;
      for (const auto& space : model().getConcreteModelObjects<openstudio::epmodel::Space>()) {
        auto spaceZone = space.thermalZone();
        if (spaceZone && (*spaceZone == *zone)) {
          zoneSpaces.push_back(space);
        }
      }
      if (zoneSpaces.empty()) {
        return;
      }

      // Canonical OA representation in epmodel:
      // If a zone has spaces and any zone OA assignment exists, represent it as
      // DesignSpecification:OutdoorAir:SpaceList (one extensible assignment per Space).
      //
      // We intentionally do not branch on "all spaces share the same DSOA".
      // A single representation avoids API/behavior divergence and keeps getter
      // semantics deterministic after canonicalization.
      std::vector<std::pair<openstudio::epmodel::Space, boost::optional<openstudio::epmodel::DesignSpecificationOutdoorAir>>> assignments;
      assignments.reserve(zoneSpaces.size());
      for (const auto& space : zoneSpaces) {
        auto assignedDSOA = sourceSpaceList ? sourceSpaceList->designSpecificationOutdoorAir(space) : boost::none;
        if (!assignedDSOA && directDSOA) {
          assignedDSOA = directDSOA;
        }
        assignments.emplace_back(space, assignedDSOA);
      }

      const auto canonicalSpaceListName = zone->nameString() + " DSOA Space List";
      boost::optional<openstudio::epmodel::DesignSpecificationOutdoorAirSpaceList> canonicalSpaceList = sourceSpaceList;
      if (!canonicalSpaceList) {
        canonicalSpaceList =
          model().getConcreteModelObjectByName<openstudio::epmodel::DesignSpecificationOutdoorAirSpaceList>(canonicalSpaceListName);
      }
      if (!canonicalSpaceList) {
        canonicalSpaceList = openstudio::epmodel::DesignSpecificationOutdoorAirSpaceList(model());
        canonicalSpaceList->setName(canonicalSpaceListName);
        detail::addLoadInfo(context, "Created DesignSpecification:OutdoorAir:SpaceList '" + canonicalSpaceList->nameString() + "' for Sizing:Zone '"
                                       + thisSizingZone.nameString() + "'.");
      }
      OS_ASSERT(canonicalSpaceList);

      while (canonicalSpaceList->numExtensibleGroups() > 0u) {
        canonicalSpaceList->eraseExtensibleGroup(0u);
      }

      // Rebuild groups from current zone-space membership and resolved assignments.
      // Rebuild (instead of patching) keeps canonicalization idempotent and eliminates
      // stale groups for spaces that moved across zones.
      bool populatedAny = false;
      for (const auto& [space, assignedDSOA] : assignments) {
        if (!assignedDSOA) {
          continue;
        }
        OS_ASSERT(
          canonicalSpaceList->getImpl<openstudio::epmodel::detail::DesignSpecificationOutdoorAirSpaceList_Impl>()->setDesignSpecificationOutdoorAir(
            space, *assignedDSOA));
        populatedAny = true;
      }

      if (!populatedAny) {
        return;
      }

      // Canonical postcondition: Sizing:Zone points at the canonical SpaceList object.
      // Direct DSOA on Sizing:Zone remains non-canonical and is normalized away here.
      if (setDesignSpecificationOutdoorAirSpaceList(*canonicalSpaceList)) {
        if (directDSOA) {
          detail::addLoadInfo(context, "Normalized Sizing:Zone '" + thisSizingZone.nameString()
                                         + "' OA reference to DesignSpecification:OutdoorAir:SpaceList '" + canonicalSpaceList->nameString() + "'.");
        }
        canonicalSpaceList->getImpl<openstudio::epmodel::detail::DesignSpecificationOutdoorAirSpaceList_Impl>()->canonicalize(context);
      }
    }

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
