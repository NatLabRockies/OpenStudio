/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "ParentObject/RefrigerationCase.hpp"
#include "ParentObject/RefrigerationCase_Impl.hpp"

#include "Model.hpp"
#include "ModelObject.hpp"
#include "Schedule/Schedule.hpp"
#include "Schedule/Schedule_Impl.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/idd/IddFactory.hxx>
#include <utilities/idd/Refrigeration_Case_FieldEnums.hxx>
#include <utilities/idf/IdfObject_Impl.hpp>

namespace openstudio {
namespace epmodel {

  RefrigerationCase::RefrigerationCase(const Model& model) : ParentObject(RefrigerationCase::iddObjectType(), model) {}

  RefrigerationCase::RefrigerationCase(std::shared_ptr<detail::RefrigerationCase_Impl> impl) : ParentObject(std::move(impl)) {}

  IddObjectType RefrigerationCase::iddObjectType() {
    return IddObjectType::Refrigeration_Case;
  }

  std::vector<std::string> RefrigerationCase::latentCaseCreditCurveTypeValues() {
    return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(), Refrigeration_CaseFields::LatentCaseCreditCurveType);
  }

  std::vector<std::string> RefrigerationCase::antiSweatHeaterControlTypeValues() {
    return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(), Refrigeration_CaseFields::AntiSweatHeaterControlType);
  }

  std::vector<std::string> RefrigerationCase::caseDefrostTypeValues() {
    return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(), Refrigeration_CaseFields::CaseDefrostType);
  }

  std::vector<std::string> RefrigerationCase::defrostEnergyCorrectionCurveTypeValues() {
    return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(), Refrigeration_CaseFields::DefrostEnergyCorrectionCurveType);
  }

  boost::optional<Schedule> RefrigerationCase::availabilitySchedule() const {
    return getImpl<detail::RefrigerationCase_Impl>()->availabilitySchedule();
  }

  bool RefrigerationCase::setAvailabilitySchedule(Schedule& schedule) {
    return getImpl<detail::RefrigerationCase_Impl>()->setAvailabilitySchedule(schedule);
  }

  void RefrigerationCase::resetAvailabilitySchedule() {
    getImpl<detail::RefrigerationCase_Impl>()->resetAvailabilitySchedule();
  }

  double RefrigerationCase::ratedAmbientTemperature() const {
    return getImpl<detail::RefrigerationCase_Impl>()->ratedAmbientTemperature();
  }

  bool RefrigerationCase::isRatedAmbientTemperatureDefaulted() const {
    return getImpl<detail::RefrigerationCase_Impl>()->isRatedAmbientTemperatureDefaulted();
  }

  bool RefrigerationCase::setRatedAmbientTemperature(double ratedAmbientTemperature) {
    return getImpl<detail::RefrigerationCase_Impl>()->setRatedAmbientTemperature(ratedAmbientTemperature);
  }

  void RefrigerationCase::resetRatedAmbientTemperature() {
    getImpl<detail::RefrigerationCase_Impl>()->resetRatedAmbientTemperature();
  }

  double RefrigerationCase::ratedAmbientRelativeHumidity() const {
    return getImpl<detail::RefrigerationCase_Impl>()->ratedAmbientRelativeHumidity();
  }

  bool RefrigerationCase::isRatedAmbientRelativeHumidityDefaulted() const {
    return getImpl<detail::RefrigerationCase_Impl>()->isRatedAmbientRelativeHumidityDefaulted();
  }

  bool RefrigerationCase::setRatedAmbientRelativeHumidity(double ratedAmbientRelativeHumidity) {
    return getImpl<detail::RefrigerationCase_Impl>()->setRatedAmbientRelativeHumidity(ratedAmbientRelativeHumidity);
  }

  void RefrigerationCase::resetRatedAmbientRelativeHumidity() {
    getImpl<detail::RefrigerationCase_Impl>()->resetRatedAmbientRelativeHumidity();
  }

  double RefrigerationCase::ratedTotalCoolingCapacityperUnitLength() const {
    return getImpl<detail::RefrigerationCase_Impl>()->ratedTotalCoolingCapacityperUnitLength();
  }

  bool RefrigerationCase::isRatedTotalCoolingCapacityperUnitLengthDefaulted() const {
    return getImpl<detail::RefrigerationCase_Impl>()->isRatedTotalCoolingCapacityperUnitLengthDefaulted();
  }

  bool RefrigerationCase::setRatedTotalCoolingCapacityperUnitLength(double ratedTotalCoolingCapacityperUnitLength) {
    return getImpl<detail::RefrigerationCase_Impl>()->setRatedTotalCoolingCapacityperUnitLength(ratedTotalCoolingCapacityperUnitLength);
  }

  void RefrigerationCase::resetRatedTotalCoolingCapacityperUnitLength() {
    getImpl<detail::RefrigerationCase_Impl>()->resetRatedTotalCoolingCapacityperUnitLength();
  }

  double RefrigerationCase::ratedLatentHeatRatio() const {
    return getImpl<detail::RefrigerationCase_Impl>()->ratedLatentHeatRatio();
  }

  bool RefrigerationCase::isRatedLatentHeatRatioDefaulted() const {
    return getImpl<detail::RefrigerationCase_Impl>()->isRatedLatentHeatRatioDefaulted();
  }

  bool RefrigerationCase::setRatedLatentHeatRatio(double ratedLatentHeatRatio) {
    return getImpl<detail::RefrigerationCase_Impl>()->setRatedLatentHeatRatio(ratedLatentHeatRatio);
  }

  void RefrigerationCase::resetRatedLatentHeatRatio() {
    getImpl<detail::RefrigerationCase_Impl>()->resetRatedLatentHeatRatio();
  }

  double RefrigerationCase::ratedRuntimeFraction() const {
    return getImpl<detail::RefrigerationCase_Impl>()->ratedRuntimeFraction();
  }

  bool RefrigerationCase::isRatedRuntimeFractionDefaulted() const {
    return getImpl<detail::RefrigerationCase_Impl>()->isRatedRuntimeFractionDefaulted();
  }

  bool RefrigerationCase::setRatedRuntimeFraction(double ratedRuntimeFraction) {
    return getImpl<detail::RefrigerationCase_Impl>()->setRatedRuntimeFraction(ratedRuntimeFraction);
  }

  void RefrigerationCase::resetRatedRuntimeFraction() {
    getImpl<detail::RefrigerationCase_Impl>()->resetRatedRuntimeFraction();
  }

  double RefrigerationCase::caseLength() const {
    return getImpl<detail::RefrigerationCase_Impl>()->caseLength();
  }

  bool RefrigerationCase::isCaseLengthDefaulted() const {
    return getImpl<detail::RefrigerationCase_Impl>()->isCaseLengthDefaulted();
  }

  bool RefrigerationCase::setCaseLength(double caseLength) {
    return getImpl<detail::RefrigerationCase_Impl>()->setCaseLength(caseLength);
  }

  void RefrigerationCase::resetCaseLength() {
    getImpl<detail::RefrigerationCase_Impl>()->resetCaseLength();
  }

  double RefrigerationCase::caseOperatingTemperature() const {
    return getImpl<detail::RefrigerationCase_Impl>()->caseOperatingTemperature();
  }

  bool RefrigerationCase::isCaseOperatingTemperatureDefaulted() const {
    return getImpl<detail::RefrigerationCase_Impl>()->isCaseOperatingTemperatureDefaulted();
  }

  bool RefrigerationCase::setCaseOperatingTemperature(double caseOperatingTemperature) {
    return getImpl<detail::RefrigerationCase_Impl>()->setCaseOperatingTemperature(caseOperatingTemperature);
  }

  void RefrigerationCase::resetCaseOperatingTemperature() {
    getImpl<detail::RefrigerationCase_Impl>()->resetCaseOperatingTemperature();
  }

  std::string RefrigerationCase::latentCaseCreditCurveType() const {
    return getImpl<detail::RefrigerationCase_Impl>()->latentCaseCreditCurveType();
  }

  bool RefrigerationCase::isLatentCaseCreditCurveTypeDefaulted() const {
    return getImpl<detail::RefrigerationCase_Impl>()->isLatentCaseCreditCurveTypeDefaulted();
  }

  bool RefrigerationCase::setLatentCaseCreditCurveType(const std::string& latentCaseCreditCurveType) {
    return getImpl<detail::RefrigerationCase_Impl>()->setLatentCaseCreditCurveType(latentCaseCreditCurveType);
  }

  void RefrigerationCase::resetLatentCaseCreditCurveType() {
    getImpl<detail::RefrigerationCase_Impl>()->resetLatentCaseCreditCurveType();
  }

  double RefrigerationCase::standardCaseFanPowerperUnitLength() const {
    return getImpl<detail::RefrigerationCase_Impl>()->standardCaseFanPowerperUnitLength();
  }

  bool RefrigerationCase::isStandardCaseFanPowerperUnitLengthDefaulted() const {
    return getImpl<detail::RefrigerationCase_Impl>()->isStandardCaseFanPowerperUnitLengthDefaulted();
  }

  bool RefrigerationCase::setStandardCaseFanPowerperUnitLength(double standardCaseFanPowerperUnitLength) {
    return getImpl<detail::RefrigerationCase_Impl>()->setStandardCaseFanPowerperUnitLength(standardCaseFanPowerperUnitLength);
  }

  void RefrigerationCase::resetStandardCaseFanPowerperUnitLength() {
    getImpl<detail::RefrigerationCase_Impl>()->resetStandardCaseFanPowerperUnitLength();
  }

  double RefrigerationCase::operatingCaseFanPowerperUnitLength() const {
    return getImpl<detail::RefrigerationCase_Impl>()->operatingCaseFanPowerperUnitLength();
  }

  bool RefrigerationCase::isOperatingCaseFanPowerperUnitLengthDefaulted() const {
    return getImpl<detail::RefrigerationCase_Impl>()->isOperatingCaseFanPowerperUnitLengthDefaulted();
  }

  bool RefrigerationCase::setOperatingCaseFanPowerperUnitLength(double operatingCaseFanPowerperUnitLength) {
    return getImpl<detail::RefrigerationCase_Impl>()->setOperatingCaseFanPowerperUnitLength(operatingCaseFanPowerperUnitLength);
  }

  void RefrigerationCase::resetOperatingCaseFanPowerperUnitLength() {
    getImpl<detail::RefrigerationCase_Impl>()->resetOperatingCaseFanPowerperUnitLength();
  }

  double RefrigerationCase::standardCaseLightingPowerperUnitLength() const {
    return getImpl<detail::RefrigerationCase_Impl>()->standardCaseLightingPowerperUnitLength();
  }

  bool RefrigerationCase::isStandardCaseLightingPowerperUnitLengthDefaulted() const {
    return getImpl<detail::RefrigerationCase_Impl>()->isStandardCaseLightingPowerperUnitLengthDefaulted();
  }

  bool RefrigerationCase::setStandardCaseLightingPowerperUnitLength(double standardCaseLightingPowerperUnitLength) {
    return getImpl<detail::RefrigerationCase_Impl>()->setStandardCaseLightingPowerperUnitLength(standardCaseLightingPowerperUnitLength);
  }

  void RefrigerationCase::resetStandardCaseLightingPowerperUnitLength() {
    getImpl<detail::RefrigerationCase_Impl>()->resetStandardCaseLightingPowerperUnitLength();
  }

  boost::optional<double> RefrigerationCase::installedCaseLightingPowerperUnitLength() const {
    return getImpl<detail::RefrigerationCase_Impl>()->installedCaseLightingPowerperUnitLength();
  }

  bool RefrigerationCase::setInstalledCaseLightingPowerperUnitLength(double installedCaseLightingPowerperUnitLength) {
    return getImpl<detail::RefrigerationCase_Impl>()->setInstalledCaseLightingPowerperUnitLength(installedCaseLightingPowerperUnitLength);
  }

  void RefrigerationCase::resetInstalledCaseLightingPowerperUnitLength() {
    getImpl<detail::RefrigerationCase_Impl>()->resetInstalledCaseLightingPowerperUnitLength();
  }

  boost::optional<Schedule> RefrigerationCase::caseLightingSchedule() const {
    return getImpl<detail::RefrigerationCase_Impl>()->caseLightingSchedule();
  }

  bool RefrigerationCase::setCaseLightingSchedule(Schedule& schedule) {
    return getImpl<detail::RefrigerationCase_Impl>()->setCaseLightingSchedule(schedule);
  }

  void RefrigerationCase::resetCaseLightingSchedule() {
    getImpl<detail::RefrigerationCase_Impl>()->resetCaseLightingSchedule();
  }

  double RefrigerationCase::fractionofLightingEnergytoCase() const {
    return getImpl<detail::RefrigerationCase_Impl>()->fractionofLightingEnergytoCase();
  }

  bool RefrigerationCase::isFractionofLightingEnergytoCaseDefaulted() const {
    return getImpl<detail::RefrigerationCase_Impl>()->isFractionofLightingEnergytoCaseDefaulted();
  }

  bool RefrigerationCase::setFractionofLightingEnergytoCase(double fractionofLightingEnergytoCase) {
    return getImpl<detail::RefrigerationCase_Impl>()->setFractionofLightingEnergytoCase(fractionofLightingEnergytoCase);
  }

  void RefrigerationCase::resetFractionofLightingEnergytoCase() {
    getImpl<detail::RefrigerationCase_Impl>()->resetFractionofLightingEnergytoCase();
  }

  double RefrigerationCase::caseAntiSweatHeaterPowerperUnitLength() const {
    return getImpl<detail::RefrigerationCase_Impl>()->caseAntiSweatHeaterPowerperUnitLength();
  }

  bool RefrigerationCase::isCaseAntiSweatHeaterPowerperUnitLengthDefaulted() const {
    return getImpl<detail::RefrigerationCase_Impl>()->isCaseAntiSweatHeaterPowerperUnitLengthDefaulted();
  }

  bool RefrigerationCase::setCaseAntiSweatHeaterPowerperUnitLength(double caseAntiSweatHeaterPowerperUnitLength) {
    return getImpl<detail::RefrigerationCase_Impl>()->setCaseAntiSweatHeaterPowerperUnitLength(caseAntiSweatHeaterPowerperUnitLength);
  }

  void RefrigerationCase::resetCaseAntiSweatHeaterPowerperUnitLength() {
    getImpl<detail::RefrigerationCase_Impl>()->resetCaseAntiSweatHeaterPowerperUnitLength();
  }

  double RefrigerationCase::minimumAntiSweatHeaterPowerperUnitLength() const {
    return getImpl<detail::RefrigerationCase_Impl>()->minimumAntiSweatHeaterPowerperUnitLength();
  }

  bool RefrigerationCase::isMinimumAntiSweatHeaterPowerperUnitLengthDefaulted() const {
    return getImpl<detail::RefrigerationCase_Impl>()->isMinimumAntiSweatHeaterPowerperUnitLengthDefaulted();
  }

  bool RefrigerationCase::setMinimumAntiSweatHeaterPowerperUnitLength(double minimumAntiSweatHeaterPowerperUnitLength) {
    return getImpl<detail::RefrigerationCase_Impl>()->setMinimumAntiSweatHeaterPowerperUnitLength(minimumAntiSweatHeaterPowerperUnitLength);
  }

  void RefrigerationCase::resetMinimumAntiSweatHeaterPowerperUnitLength() {
    getImpl<detail::RefrigerationCase_Impl>()->resetMinimumAntiSweatHeaterPowerperUnitLength();
  }

  std::string RefrigerationCase::antiSweatHeaterControlType() const {
    return getImpl<detail::RefrigerationCase_Impl>()->antiSweatHeaterControlType();
  }

  bool RefrigerationCase::isAntiSweatHeaterControlTypeDefaulted() const {
    return getImpl<detail::RefrigerationCase_Impl>()->isAntiSweatHeaterControlTypeDefaulted();
  }

  bool RefrigerationCase::setAntiSweatHeaterControlType(const std::string& antiSweatHeaterControlType) {
    return getImpl<detail::RefrigerationCase_Impl>()->setAntiSweatHeaterControlType(antiSweatHeaterControlType);
  }

  void RefrigerationCase::resetAntiSweatHeaterControlType() {
    getImpl<detail::RefrigerationCase_Impl>()->resetAntiSweatHeaterControlType();
  }

  double RefrigerationCase::humidityatZeroAntiSweatHeaterEnergy() const {
    return getImpl<detail::RefrigerationCase_Impl>()->humidityatZeroAntiSweatHeaterEnergy();
  }

  bool RefrigerationCase::isHumidityatZeroAntiSweatHeaterEnergyDefaulted() const {
    return getImpl<detail::RefrigerationCase_Impl>()->isHumidityatZeroAntiSweatHeaterEnergyDefaulted();
  }

  bool RefrigerationCase::setHumidityatZeroAntiSweatHeaterEnergy(double humidityatZeroAntiSweatHeaterEnergy) {
    return getImpl<detail::RefrigerationCase_Impl>()->setHumidityatZeroAntiSweatHeaterEnergy(humidityatZeroAntiSweatHeaterEnergy);
  }

  void RefrigerationCase::resetHumidityatZeroAntiSweatHeaterEnergy() {
    getImpl<detail::RefrigerationCase_Impl>()->resetHumidityatZeroAntiSweatHeaterEnergy();
  }

  double RefrigerationCase::caseHeight() const {
    return getImpl<detail::RefrigerationCase_Impl>()->caseHeight();
  }

  bool RefrigerationCase::isCaseHeightDefaulted() const {
    return getImpl<detail::RefrigerationCase_Impl>()->isCaseHeightDefaulted();
  }

  bool RefrigerationCase::setCaseHeight(double caseHeight) {
    return getImpl<detail::RefrigerationCase_Impl>()->setCaseHeight(caseHeight);
  }

  void RefrigerationCase::resetCaseHeight() {
    getImpl<detail::RefrigerationCase_Impl>()->resetCaseHeight();
  }

  double RefrigerationCase::fractionofAntiSweatHeaterEnergytoCase() const {
    return getImpl<detail::RefrigerationCase_Impl>()->fractionofAntiSweatHeaterEnergytoCase();
  }

  bool RefrigerationCase::isFractionofAntiSweatHeaterEnergytoCaseDefaulted() const {
    return getImpl<detail::RefrigerationCase_Impl>()->isFractionofAntiSweatHeaterEnergytoCaseDefaulted();
  }

  bool RefrigerationCase::setFractionofAntiSweatHeaterEnergytoCase(double fractionofAntiSweatHeaterEnergytoCase) {
    return getImpl<detail::RefrigerationCase_Impl>()->setFractionofAntiSweatHeaterEnergytoCase(fractionofAntiSweatHeaterEnergytoCase);
  }

  void RefrigerationCase::resetFractionofAntiSweatHeaterEnergytoCase() {
    getImpl<detail::RefrigerationCase_Impl>()->resetFractionofAntiSweatHeaterEnergytoCase();
  }

  double RefrigerationCase::caseDefrostPowerperUnitLength() const {
    return getImpl<detail::RefrigerationCase_Impl>()->caseDefrostPowerperUnitLength();
  }

  bool RefrigerationCase::isCaseDefrostPowerperUnitLengthDefaulted() const {
    return getImpl<detail::RefrigerationCase_Impl>()->isCaseDefrostPowerperUnitLengthDefaulted();
  }

  bool RefrigerationCase::setCaseDefrostPowerperUnitLength(double caseDefrostPowerperUnitLength) {
    return getImpl<detail::RefrigerationCase_Impl>()->setCaseDefrostPowerperUnitLength(caseDefrostPowerperUnitLength);
  }

  void RefrigerationCase::resetCaseDefrostPowerperUnitLength() {
    getImpl<detail::RefrigerationCase_Impl>()->resetCaseDefrostPowerperUnitLength();
  }

  std::string RefrigerationCase::caseDefrostType() const {
    return getImpl<detail::RefrigerationCase_Impl>()->caseDefrostType();
  }

  bool RefrigerationCase::isCaseDefrostTypeDefaulted() const {
    return getImpl<detail::RefrigerationCase_Impl>()->isCaseDefrostTypeDefaulted();
  }

  bool RefrigerationCase::setCaseDefrostType(const std::string& caseDefrostType) {
    return getImpl<detail::RefrigerationCase_Impl>()->setCaseDefrostType(caseDefrostType);
  }

  void RefrigerationCase::resetCaseDefrostType() {
    getImpl<detail::RefrigerationCase_Impl>()->resetCaseDefrostType();
  }

  boost::optional<Schedule> RefrigerationCase::caseDefrostSchedule() const {
    return getImpl<detail::RefrigerationCase_Impl>()->caseDefrostSchedule();
  }

  bool RefrigerationCase::setCaseDefrostSchedule(Schedule& schedule) {
    return getImpl<detail::RefrigerationCase_Impl>()->setCaseDefrostSchedule(schedule);
  }

  void RefrigerationCase::resetCaseDefrostSchedule() {
    getImpl<detail::RefrigerationCase_Impl>()->resetCaseDefrostSchedule();
  }

  boost::optional<Schedule> RefrigerationCase::caseDefrostDripDownSchedule() const {
    return getImpl<detail::RefrigerationCase_Impl>()->caseDefrostDripDownSchedule();
  }

  bool RefrigerationCase::setCaseDefrostDripDownSchedule(Schedule& schedule) {
    return getImpl<detail::RefrigerationCase_Impl>()->setCaseDefrostDripDownSchedule(schedule);
  }

  void RefrigerationCase::resetCaseDefrostDripDownSchedule() {
    getImpl<detail::RefrigerationCase_Impl>()->resetCaseDefrostDripDownSchedule();
  }

  std::string RefrigerationCase::defrostEnergyCorrectionCurveType() const {
    return getImpl<detail::RefrigerationCase_Impl>()->defrostEnergyCorrectionCurveType();
  }

  bool RefrigerationCase::isDefrostEnergyCorrectionCurveTypeDefaulted() const {
    return getImpl<detail::RefrigerationCase_Impl>()->isDefrostEnergyCorrectionCurveTypeDefaulted();
  }

  bool RefrigerationCase::setDefrostEnergyCorrectionCurveType(const std::string& defrostEnergyCorrectionCurveType) {
    return getImpl<detail::RefrigerationCase_Impl>()->setDefrostEnergyCorrectionCurveType(defrostEnergyCorrectionCurveType);
  }

  void RefrigerationCase::resetDefrostEnergyCorrectionCurveType() {
    getImpl<detail::RefrigerationCase_Impl>()->resetDefrostEnergyCorrectionCurveType();
  }

  double RefrigerationCase::underCaseHVACReturnAirFraction() const {
    return getImpl<detail::RefrigerationCase_Impl>()->underCaseHVACReturnAirFraction();
  }

  bool RefrigerationCase::isUnderCaseHVACReturnAirFractionDefaulted() const {
    return getImpl<detail::RefrigerationCase_Impl>()->isUnderCaseHVACReturnAirFractionDefaulted();
  }

  bool RefrigerationCase::setUnderCaseHVACReturnAirFraction(double underCaseHVACReturnAirFraction) {
    return getImpl<detail::RefrigerationCase_Impl>()->setUnderCaseHVACReturnAirFraction(underCaseHVACReturnAirFraction);
  }

  void RefrigerationCase::resetUnderCaseHVACReturnAirFraction() {
    getImpl<detail::RefrigerationCase_Impl>()->resetUnderCaseHVACReturnAirFraction();
  }

  boost::optional<Schedule> RefrigerationCase::refrigeratedCaseRestockingSchedule() const {
    return getImpl<detail::RefrigerationCase_Impl>()->refrigeratedCaseRestockingSchedule();
  }

  bool RefrigerationCase::setRefrigeratedCaseRestockingSchedule(Schedule& schedule) {
    return getImpl<detail::RefrigerationCase_Impl>()->setRefrigeratedCaseRestockingSchedule(schedule);
  }

  void RefrigerationCase::resetRefrigeratedCaseRestockingSchedule() {
    getImpl<detail::RefrigerationCase_Impl>()->resetRefrigeratedCaseRestockingSchedule();
  }

  boost::optional<Schedule> RefrigerationCase::caseCreditFractionSchedule() const {
    return getImpl<detail::RefrigerationCase_Impl>()->caseCreditFractionSchedule();
  }

  bool RefrigerationCase::setCaseCreditFractionSchedule(Schedule& schedule) {
    return getImpl<detail::RefrigerationCase_Impl>()->setCaseCreditFractionSchedule(schedule);
  }

  void RefrigerationCase::resetCaseCreditFractionSchedule() {
    getImpl<detail::RefrigerationCase_Impl>()->resetCaseCreditFractionSchedule();
  }

  boost::optional<double> RefrigerationCase::designEvaporatorTemperatureorBrineInletTemperature() const {
    return getImpl<detail::RefrigerationCase_Impl>()->designEvaporatorTemperatureorBrineInletTemperature();
  }

  bool RefrigerationCase::setDesignEvaporatorTemperatureorBrineInletTemperature(double designEvaporatorTemperatureorBrineInletTemperature) {
    return getImpl<detail::RefrigerationCase_Impl>()->setDesignEvaporatorTemperatureorBrineInletTemperature(
      designEvaporatorTemperatureorBrineInletTemperature);
  }

  void RefrigerationCase::resetDesignEvaporatorTemperatureorBrineInletTemperature() {
    getImpl<detail::RefrigerationCase_Impl>()->resetDesignEvaporatorTemperatureorBrineInletTemperature();
  }

  double RefrigerationCase::averageRefrigerantChargeInventory() const {
    return getImpl<detail::RefrigerationCase_Impl>()->averageRefrigerantChargeInventory();
  }

  bool RefrigerationCase::isAverageRefrigerantChargeInventoryDefaulted() const {
    return getImpl<detail::RefrigerationCase_Impl>()->isAverageRefrigerantChargeInventoryDefaulted();
  }

  bool RefrigerationCase::setAverageRefrigerantChargeInventory(double averageRefrigerantChargeInventory) {
    return getImpl<detail::RefrigerationCase_Impl>()->setAverageRefrigerantChargeInventory(averageRefrigerantChargeInventory);
  }

  void RefrigerationCase::resetAverageRefrigerantChargeInventory() {
    getImpl<detail::RefrigerationCase_Impl>()->resetAverageRefrigerantChargeInventory();
  }

  namespace detail {

    boost::optional<Schedule> RefrigerationCase_Impl::availabilitySchedule() const {
      return getObject<ModelObject>().getModelObjectTarget<Schedule>(Refrigeration_CaseFields::AvailabilityScheduleName);
    }

    bool RefrigerationCase_Impl::setAvailabilitySchedule(Schedule& schedule) {
      return ModelObject_Impl::setSchedule(Refrigeration_CaseFields::AvailabilityScheduleName, "RefrigerationCase", "Availability", schedule);
    }

    void RefrigerationCase_Impl::resetAvailabilitySchedule() {
      constexpr auto field = Refrigeration_CaseFields::AvailabilityScheduleName;
      OS_ASSERT(setPointer(field, Handle(), false));
      OS_ASSERT(openstudio::detail::IdfObject_Impl::setString(field, "", false));
    }

    boost::optional<Schedule> RefrigerationCase_Impl::caseLightingSchedule() const {
      return getObject<ModelObject>().getModelObjectTarget<Schedule>(Refrigeration_CaseFields::CaseLightingScheduleName);
    }

    bool RefrigerationCase_Impl::setCaseLightingSchedule(Schedule& schedule) {
      return ModelObject_Impl::setSchedule(Refrigeration_CaseFields::CaseLightingScheduleName, "RefrigerationCase", "Case Lighting", schedule);
    }

    void RefrigerationCase_Impl::resetCaseLightingSchedule() {
      constexpr auto field = Refrigeration_CaseFields::CaseLightingScheduleName;
      OS_ASSERT(setPointer(field, Handle(), false));
      OS_ASSERT(openstudio::detail::IdfObject_Impl::setString(field, "", false));
    }

    boost::optional<Schedule> RefrigerationCase_Impl::caseDefrostSchedule() const {
      return getObject<ModelObject>().getModelObjectTarget<Schedule>(Refrigeration_CaseFields::CaseDefrostScheduleName);
    }

    bool RefrigerationCase_Impl::setCaseDefrostSchedule(Schedule& schedule) {
      return ModelObject_Impl::setSchedule(Refrigeration_CaseFields::CaseDefrostScheduleName, "RefrigerationCase", "Case Defrost", schedule);
    }

    void RefrigerationCase_Impl::resetCaseDefrostSchedule() {
      constexpr auto field = Refrigeration_CaseFields::CaseDefrostScheduleName;
      OS_ASSERT(setPointer(field, Handle(), false));
      OS_ASSERT(openstudio::detail::IdfObject_Impl::setString(field, "", false));
    }

    boost::optional<Schedule> RefrigerationCase_Impl::caseDefrostDripDownSchedule() const {
      return getObject<ModelObject>().getModelObjectTarget<Schedule>(Refrigeration_CaseFields::CaseDefrostDripDownScheduleName);
    }

    bool RefrigerationCase_Impl::setCaseDefrostDripDownSchedule(Schedule& schedule) {
      return ModelObject_Impl::setSchedule(Refrigeration_CaseFields::CaseDefrostDripDownScheduleName, "RefrigerationCase", "Case Defrost Drip-Down",
                                           schedule);
    }

    void RefrigerationCase_Impl::resetCaseDefrostDripDownSchedule() {
      constexpr auto field = Refrigeration_CaseFields::CaseDefrostDripDownScheduleName;
      OS_ASSERT(setPointer(field, Handle(), false));
      OS_ASSERT(openstudio::detail::IdfObject_Impl::setString(field, "", false));
    }

    boost::optional<Schedule> RefrigerationCase_Impl::refrigeratedCaseRestockingSchedule() const {
      return getObject<ModelObject>().getModelObjectTarget<Schedule>(Refrigeration_CaseFields::RefrigeratedCaseRestockingScheduleName);
    }

    bool RefrigerationCase_Impl::setRefrigeratedCaseRestockingSchedule(Schedule& schedule) {
      return ModelObject_Impl::setSchedule(Refrigeration_CaseFields::RefrigeratedCaseRestockingScheduleName, "RefrigerationCase",
                                           "Refrigerated Case Restocking", schedule);
    }

    void RefrigerationCase_Impl::resetRefrigeratedCaseRestockingSchedule() {
      constexpr auto field = Refrigeration_CaseFields::RefrigeratedCaseRestockingScheduleName;
      OS_ASSERT(setPointer(field, Handle(), false));
      OS_ASSERT(openstudio::detail::IdfObject_Impl::setString(field, "", false));
    }

    boost::optional<Schedule> RefrigerationCase_Impl::caseCreditFractionSchedule() const {
      return getObject<ModelObject>().getModelObjectTarget<Schedule>(Refrigeration_CaseFields::CaseCreditFractionScheduleName);
    }

    bool RefrigerationCase_Impl::setCaseCreditFractionSchedule(Schedule& schedule) {
      return ModelObject_Impl::setSchedule(Refrigeration_CaseFields::CaseCreditFractionScheduleName, "RefrigerationCase", "Case Credit Fraction",
                                           schedule);
    }

    void RefrigerationCase_Impl::resetCaseCreditFractionSchedule() {
      constexpr auto field = Refrigeration_CaseFields::CaseCreditFractionScheduleName;
      OS_ASSERT(setPointer(field, Handle(), false));
      OS_ASSERT(openstudio::detail::IdfObject_Impl::setString(field, "", false));
    }

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
