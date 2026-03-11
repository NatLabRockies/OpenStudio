/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "ParentObject/RefrigerationCase.hpp"
#include "ParentObject/RefrigerationCase_Impl.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/idd/Refrigeration_Case_FieldEnums.hxx>

namespace openstudio {
namespace epmodel {
  namespace detail {

    double RefrigerationCase_Impl::ratedAmbientTemperature() const {
      const auto value = getDouble(Refrigeration_CaseFields::RatedAmbientTemperature, true);
      OS_ASSERT(value);
      return *value;
    }

    bool RefrigerationCase_Impl::isRatedAmbientTemperatureDefaulted() const {
      return isEmpty(Refrigeration_CaseFields::RatedAmbientTemperature);
    }

    bool RefrigerationCase_Impl::setRatedAmbientTemperature(double ratedAmbientTemperature) {
      return setDouble(Refrigeration_CaseFields::RatedAmbientTemperature, ratedAmbientTemperature);
    }

    void RefrigerationCase_Impl::resetRatedAmbientTemperature() {
      OS_ASSERT(setString(Refrigeration_CaseFields::RatedAmbientTemperature, ""));
    }

    double RefrigerationCase_Impl::ratedAmbientRelativeHumidity() const {
      const auto value = getDouble(Refrigeration_CaseFields::RatedAmbientRelativeHumidity, true);
      OS_ASSERT(value);
      return *value;
    }

    bool RefrigerationCase_Impl::isRatedAmbientRelativeHumidityDefaulted() const {
      return isEmpty(Refrigeration_CaseFields::RatedAmbientRelativeHumidity);
    }

    bool RefrigerationCase_Impl::setRatedAmbientRelativeHumidity(double ratedAmbientRelativeHumidity) {
      return setDouble(Refrigeration_CaseFields::RatedAmbientRelativeHumidity, ratedAmbientRelativeHumidity);
    }

    void RefrigerationCase_Impl::resetRatedAmbientRelativeHumidity() {
      OS_ASSERT(setString(Refrigeration_CaseFields::RatedAmbientRelativeHumidity, ""));
    }

    double RefrigerationCase_Impl::ratedTotalCoolingCapacityperUnitLength() const {
      const auto value = getDouble(Refrigeration_CaseFields::RatedTotalCoolingCapacityperUnitLength, true);
      OS_ASSERT(value);
      return *value;
    }

    bool RefrigerationCase_Impl::isRatedTotalCoolingCapacityperUnitLengthDefaulted() const {
      return isEmpty(Refrigeration_CaseFields::RatedTotalCoolingCapacityperUnitLength);
    }

    bool RefrigerationCase_Impl::setRatedTotalCoolingCapacityperUnitLength(double ratedTotalCoolingCapacityperUnitLength) {
      return setDouble(Refrigeration_CaseFields::RatedTotalCoolingCapacityperUnitLength, ratedTotalCoolingCapacityperUnitLength);
    }

    void RefrigerationCase_Impl::resetRatedTotalCoolingCapacityperUnitLength() {
      OS_ASSERT(setString(Refrigeration_CaseFields::RatedTotalCoolingCapacityperUnitLength, ""));
    }

    double RefrigerationCase_Impl::ratedLatentHeatRatio() const {
      const auto value = getDouble(Refrigeration_CaseFields::RatedLatentHeatRatio, true);
      OS_ASSERT(value);
      return *value;
    }

    bool RefrigerationCase_Impl::isRatedLatentHeatRatioDefaulted() const {
      return isEmpty(Refrigeration_CaseFields::RatedLatentHeatRatio);
    }

    bool RefrigerationCase_Impl::setRatedLatentHeatRatio(double ratedLatentHeatRatio) {
      return setDouble(Refrigeration_CaseFields::RatedLatentHeatRatio, ratedLatentHeatRatio);
    }

    void RefrigerationCase_Impl::resetRatedLatentHeatRatio() {
      OS_ASSERT(setString(Refrigeration_CaseFields::RatedLatentHeatRatio, ""));
    }

    double RefrigerationCase_Impl::ratedRuntimeFraction() const {
      const auto value = getDouble(Refrigeration_CaseFields::RatedRuntimeFraction, true);
      OS_ASSERT(value);
      return *value;
    }

    bool RefrigerationCase_Impl::isRatedRuntimeFractionDefaulted() const {
      return isEmpty(Refrigeration_CaseFields::RatedRuntimeFraction);
    }

    bool RefrigerationCase_Impl::setRatedRuntimeFraction(double ratedRuntimeFraction) {
      return setDouble(Refrigeration_CaseFields::RatedRuntimeFraction, ratedRuntimeFraction);
    }

    void RefrigerationCase_Impl::resetRatedRuntimeFraction() {
      OS_ASSERT(setString(Refrigeration_CaseFields::RatedRuntimeFraction, ""));
    }

    double RefrigerationCase_Impl::caseLength() const {
      const auto value = getDouble(Refrigeration_CaseFields::CaseLength, true);
      OS_ASSERT(value);
      return *value;
    }

    bool RefrigerationCase_Impl::isCaseLengthDefaulted() const {
      return isEmpty(Refrigeration_CaseFields::CaseLength);
    }

    bool RefrigerationCase_Impl::setCaseLength(double caseLength) {
      return setDouble(Refrigeration_CaseFields::CaseLength, caseLength);
    }

    void RefrigerationCase_Impl::resetCaseLength() {
      OS_ASSERT(setString(Refrigeration_CaseFields::CaseLength, ""));
    }

    double RefrigerationCase_Impl::caseOperatingTemperature() const {
      const auto value = getDouble(Refrigeration_CaseFields::CaseOperatingTemperature, true);
      OS_ASSERT(value);
      return *value;
    }

    bool RefrigerationCase_Impl::isCaseOperatingTemperatureDefaulted() const {
      return isEmpty(Refrigeration_CaseFields::CaseOperatingTemperature);
    }

    bool RefrigerationCase_Impl::setCaseOperatingTemperature(double caseOperatingTemperature) {
      return setDouble(Refrigeration_CaseFields::CaseOperatingTemperature, caseOperatingTemperature);
    }

    void RefrigerationCase_Impl::resetCaseOperatingTemperature() {
      OS_ASSERT(setString(Refrigeration_CaseFields::CaseOperatingTemperature, ""));
    }

    std::string RefrigerationCase_Impl::latentCaseCreditCurveType() const {
      const auto value = getString(Refrigeration_CaseFields::LatentCaseCreditCurveType, true);
      OS_ASSERT(value);
      return *value;
    }

    bool RefrigerationCase_Impl::isLatentCaseCreditCurveTypeDefaulted() const {
      return isEmpty(Refrigeration_CaseFields::LatentCaseCreditCurveType);
    }

    bool RefrigerationCase_Impl::setLatentCaseCreditCurveType(const std::string& latentCaseCreditCurveType) {
      return setString(Refrigeration_CaseFields::LatentCaseCreditCurveType, latentCaseCreditCurveType);
    }

    void RefrigerationCase_Impl::resetLatentCaseCreditCurveType() {
      OS_ASSERT(setString(Refrigeration_CaseFields::LatentCaseCreditCurveType, ""));
    }

    double RefrigerationCase_Impl::standardCaseFanPowerperUnitLength() const {
      const auto value = getDouble(Refrigeration_CaseFields::StandardCaseFanPowerperUnitLength, true);
      OS_ASSERT(value);
      return *value;
    }

    bool RefrigerationCase_Impl::isStandardCaseFanPowerperUnitLengthDefaulted() const {
      return isEmpty(Refrigeration_CaseFields::StandardCaseFanPowerperUnitLength);
    }

    bool RefrigerationCase_Impl::setStandardCaseFanPowerperUnitLength(double standardCaseFanPowerperUnitLength) {
      return setDouble(Refrigeration_CaseFields::StandardCaseFanPowerperUnitLength, standardCaseFanPowerperUnitLength);
    }

    void RefrigerationCase_Impl::resetStandardCaseFanPowerperUnitLength() {
      OS_ASSERT(setString(Refrigeration_CaseFields::StandardCaseFanPowerperUnitLength, ""));
    }

    double RefrigerationCase_Impl::operatingCaseFanPowerperUnitLength() const {
      const auto value = getDouble(Refrigeration_CaseFields::OperatingCaseFanPowerperUnitLength, true);
      OS_ASSERT(value);
      return *value;
    }

    bool RefrigerationCase_Impl::isOperatingCaseFanPowerperUnitLengthDefaulted() const {
      return isEmpty(Refrigeration_CaseFields::OperatingCaseFanPowerperUnitLength);
    }

    bool RefrigerationCase_Impl::setOperatingCaseFanPowerperUnitLength(double operatingCaseFanPowerperUnitLength) {
      return setDouble(Refrigeration_CaseFields::OperatingCaseFanPowerperUnitLength, operatingCaseFanPowerperUnitLength);
    }

    void RefrigerationCase_Impl::resetOperatingCaseFanPowerperUnitLength() {
      OS_ASSERT(setString(Refrigeration_CaseFields::OperatingCaseFanPowerperUnitLength, ""));
    }

    double RefrigerationCase_Impl::standardCaseLightingPowerperUnitLength() const {
      const auto value = getDouble(Refrigeration_CaseFields::StandardCaseLightingPowerperUnitLength, true);
      OS_ASSERT(value);
      return *value;
    }

    bool RefrigerationCase_Impl::isStandardCaseLightingPowerperUnitLengthDefaulted() const {
      return isEmpty(Refrigeration_CaseFields::StandardCaseLightingPowerperUnitLength);
    }

    bool RefrigerationCase_Impl::setStandardCaseLightingPowerperUnitLength(double standardCaseLightingPowerperUnitLength) {
      const bool result = setDouble(Refrigeration_CaseFields::StandardCaseLightingPowerperUnitLength, standardCaseLightingPowerperUnitLength);
      OS_ASSERT(result);
      return result;
    }

    void RefrigerationCase_Impl::resetStandardCaseLightingPowerperUnitLength() {
      OS_ASSERT(setString(Refrigeration_CaseFields::StandardCaseLightingPowerperUnitLength, ""));
    }

    boost::optional<double> RefrigerationCase_Impl::installedCaseLightingPowerperUnitLength() const {
      return getDouble(Refrigeration_CaseFields::InstalledCaseLightingPowerperUnitLength, true);
    }

    bool RefrigerationCase_Impl::setInstalledCaseLightingPowerperUnitLength(double installedCaseLightingPowerperUnitLength) {
      const bool result = setDouble(Refrigeration_CaseFields::InstalledCaseLightingPowerperUnitLength, installedCaseLightingPowerperUnitLength);
      OS_ASSERT(result);
      return result;
    }

    void RefrigerationCase_Impl::resetInstalledCaseLightingPowerperUnitLength() {
      OS_ASSERT(setString(Refrigeration_CaseFields::InstalledCaseLightingPowerperUnitLength, ""));
    }

    double RefrigerationCase_Impl::fractionofLightingEnergytoCase() const {
      const auto value = getDouble(Refrigeration_CaseFields::FractionofLightingEnergytoCase, true);
      OS_ASSERT(value);
      return *value;
    }

    bool RefrigerationCase_Impl::isFractionofLightingEnergytoCaseDefaulted() const {
      return isEmpty(Refrigeration_CaseFields::FractionofLightingEnergytoCase);
    }

    bool RefrigerationCase_Impl::setFractionofLightingEnergytoCase(double fractionofLightingEnergytoCase) {
      return setDouble(Refrigeration_CaseFields::FractionofLightingEnergytoCase, fractionofLightingEnergytoCase);
    }

    void RefrigerationCase_Impl::resetFractionofLightingEnergytoCase() {
      OS_ASSERT(setString(Refrigeration_CaseFields::FractionofLightingEnergytoCase, ""));
    }

    double RefrigerationCase_Impl::caseAntiSweatHeaterPowerperUnitLength() const {
      const auto value = getDouble(Refrigeration_CaseFields::CaseAntiSweatHeaterPowerperUnitLength, true);
      OS_ASSERT(value);
      return *value;
    }

    bool RefrigerationCase_Impl::isCaseAntiSweatHeaterPowerperUnitLengthDefaulted() const {
      return isEmpty(Refrigeration_CaseFields::CaseAntiSweatHeaterPowerperUnitLength);
    }

    bool RefrigerationCase_Impl::setCaseAntiSweatHeaterPowerperUnitLength(double caseAntiSweatHeaterPowerperUnitLength) {
      return setDouble(Refrigeration_CaseFields::CaseAntiSweatHeaterPowerperUnitLength, caseAntiSweatHeaterPowerperUnitLength);
    }

    void RefrigerationCase_Impl::resetCaseAntiSweatHeaterPowerperUnitLength() {
      OS_ASSERT(setString(Refrigeration_CaseFields::CaseAntiSweatHeaterPowerperUnitLength, ""));
    }

    double RefrigerationCase_Impl::minimumAntiSweatHeaterPowerperUnitLength() const {
      const auto value = getDouble(Refrigeration_CaseFields::MinimumAntiSweatHeaterPowerperUnitLength, true);
      OS_ASSERT(value);
      return *value;
    }

    bool RefrigerationCase_Impl::isMinimumAntiSweatHeaterPowerperUnitLengthDefaulted() const {
      return isEmpty(Refrigeration_CaseFields::MinimumAntiSweatHeaterPowerperUnitLength);
    }

    bool RefrigerationCase_Impl::setMinimumAntiSweatHeaterPowerperUnitLength(double minimumAntiSweatHeaterPowerperUnitLength) {
      return setDouble(Refrigeration_CaseFields::MinimumAntiSweatHeaterPowerperUnitLength, minimumAntiSweatHeaterPowerperUnitLength);
    }

    void RefrigerationCase_Impl::resetMinimumAntiSweatHeaterPowerperUnitLength() {
      OS_ASSERT(setString(Refrigeration_CaseFields::MinimumAntiSweatHeaterPowerperUnitLength, ""));
    }

    std::string RefrigerationCase_Impl::antiSweatHeaterControlType() const {
      const auto value = getString(Refrigeration_CaseFields::AntiSweatHeaterControlType, true);
      OS_ASSERT(value);
      return *value;
    }

    bool RefrigerationCase_Impl::isAntiSweatHeaterControlTypeDefaulted() const {
      return isEmpty(Refrigeration_CaseFields::AntiSweatHeaterControlType);
    }

    bool RefrigerationCase_Impl::setAntiSweatHeaterControlType(const std::string& antiSweatHeaterControlType) {
      return setString(Refrigeration_CaseFields::AntiSweatHeaterControlType, antiSweatHeaterControlType);
    }

    void RefrigerationCase_Impl::resetAntiSweatHeaterControlType() {
      OS_ASSERT(setString(Refrigeration_CaseFields::AntiSweatHeaterControlType, ""));
    }

    double RefrigerationCase_Impl::humidityatZeroAntiSweatHeaterEnergy() const {
      const auto value = getDouble(Refrigeration_CaseFields::HumidityatZeroAntiSweatHeaterEnergy, true);
      OS_ASSERT(value);
      return *value;
    }

    bool RefrigerationCase_Impl::isHumidityatZeroAntiSweatHeaterEnergyDefaulted() const {
      return isEmpty(Refrigeration_CaseFields::HumidityatZeroAntiSweatHeaterEnergy);
    }

    bool RefrigerationCase_Impl::setHumidityatZeroAntiSweatHeaterEnergy(double humidityatZeroAntiSweatHeaterEnergy) {
      const bool result = setDouble(Refrigeration_CaseFields::HumidityatZeroAntiSweatHeaterEnergy, humidityatZeroAntiSweatHeaterEnergy);
      OS_ASSERT(result);
      return result;
    }

    void RefrigerationCase_Impl::resetHumidityatZeroAntiSweatHeaterEnergy() {
      OS_ASSERT(setString(Refrigeration_CaseFields::HumidityatZeroAntiSweatHeaterEnergy, ""));
    }

    double RefrigerationCase_Impl::caseHeight() const {
      const auto value = getDouble(Refrigeration_CaseFields::CaseHeight, true);
      OS_ASSERT(value);
      return *value;
    }

    bool RefrigerationCase_Impl::isCaseHeightDefaulted() const {
      return isEmpty(Refrigeration_CaseFields::CaseHeight);
    }

    bool RefrigerationCase_Impl::setCaseHeight(double caseHeight) {
      return setDouble(Refrigeration_CaseFields::CaseHeight, caseHeight);
    }

    void RefrigerationCase_Impl::resetCaseHeight() {
      OS_ASSERT(setString(Refrigeration_CaseFields::CaseHeight, ""));
    }

    double RefrigerationCase_Impl::fractionofAntiSweatHeaterEnergytoCase() const {
      const auto value = getDouble(Refrigeration_CaseFields::FractionofAntiSweatHeaterEnergytoCase, true);
      OS_ASSERT(value);
      return *value;
    }

    bool RefrigerationCase_Impl::isFractionofAntiSweatHeaterEnergytoCaseDefaulted() const {
      return isEmpty(Refrigeration_CaseFields::FractionofAntiSweatHeaterEnergytoCase);
    }

    bool RefrigerationCase_Impl::setFractionofAntiSweatHeaterEnergytoCase(double fractionofAntiSweatHeaterEnergytoCase) {
      return setDouble(Refrigeration_CaseFields::FractionofAntiSweatHeaterEnergytoCase, fractionofAntiSweatHeaterEnergytoCase);
    }

    void RefrigerationCase_Impl::resetFractionofAntiSweatHeaterEnergytoCase() {
      OS_ASSERT(setString(Refrigeration_CaseFields::FractionofAntiSweatHeaterEnergytoCase, ""));
    }

    double RefrigerationCase_Impl::caseDefrostPowerperUnitLength() const {
      const auto value = getDouble(Refrigeration_CaseFields::CaseDefrostPowerperUnitLength, true);
      OS_ASSERT(value);
      return *value;
    }

    bool RefrigerationCase_Impl::isCaseDefrostPowerperUnitLengthDefaulted() const {
      return isEmpty(Refrigeration_CaseFields::CaseDefrostPowerperUnitLength);
    }

    bool RefrigerationCase_Impl::setCaseDefrostPowerperUnitLength(double caseDefrostPowerperUnitLength) {
      return setDouble(Refrigeration_CaseFields::CaseDefrostPowerperUnitLength, caseDefrostPowerperUnitLength);
    }

    void RefrigerationCase_Impl::resetCaseDefrostPowerperUnitLength() {
      OS_ASSERT(setString(Refrigeration_CaseFields::CaseDefrostPowerperUnitLength, ""));
    }

    std::string RefrigerationCase_Impl::caseDefrostType() const {
      const auto value = getString(Refrigeration_CaseFields::CaseDefrostType, true);
      OS_ASSERT(value);
      return *value;
    }

    bool RefrigerationCase_Impl::isCaseDefrostTypeDefaulted() const {
      return isEmpty(Refrigeration_CaseFields::CaseDefrostType);
    }

    bool RefrigerationCase_Impl::setCaseDefrostType(const std::string& caseDefrostType) {
      return setString(Refrigeration_CaseFields::CaseDefrostType, caseDefrostType);
    }

    void RefrigerationCase_Impl::resetCaseDefrostType() {
      OS_ASSERT(setString(Refrigeration_CaseFields::CaseDefrostType, ""));
    }

    std::string RefrigerationCase_Impl::defrostEnergyCorrectionCurveType() const {
      const auto value = getString(Refrigeration_CaseFields::DefrostEnergyCorrectionCurveType, true);
      OS_ASSERT(value);
      return *value;
    }

    bool RefrigerationCase_Impl::isDefrostEnergyCorrectionCurveTypeDefaulted() const {
      return isEmpty(Refrigeration_CaseFields::DefrostEnergyCorrectionCurveType);
    }

    bool RefrigerationCase_Impl::setDefrostEnergyCorrectionCurveType(const std::string& defrostEnergyCorrectionCurveType) {
      return setString(Refrigeration_CaseFields::DefrostEnergyCorrectionCurveType, defrostEnergyCorrectionCurveType);
    }

    void RefrigerationCase_Impl::resetDefrostEnergyCorrectionCurveType() {
      OS_ASSERT(setString(Refrigeration_CaseFields::DefrostEnergyCorrectionCurveType, ""));
    }

    double RefrigerationCase_Impl::underCaseHVACReturnAirFraction() const {
      const auto value = getDouble(Refrigeration_CaseFields::UnderCaseHVACReturnAirFraction, true);
      OS_ASSERT(value);
      return *value;
    }

    bool RefrigerationCase_Impl::isUnderCaseHVACReturnAirFractionDefaulted() const {
      return isEmpty(Refrigeration_CaseFields::UnderCaseHVACReturnAirFraction);
    }

    bool RefrigerationCase_Impl::setUnderCaseHVACReturnAirFraction(double underCaseHVACReturnAirFraction) {
      return setDouble(Refrigeration_CaseFields::UnderCaseHVACReturnAirFraction, underCaseHVACReturnAirFraction);
    }

    void RefrigerationCase_Impl::resetUnderCaseHVACReturnAirFraction() {
      OS_ASSERT(setString(Refrigeration_CaseFields::UnderCaseHVACReturnAirFraction, ""));
    }

    boost::optional<double> RefrigerationCase_Impl::designEvaporatorTemperatureorBrineInletTemperature() const {
      return getDouble(Refrigeration_CaseFields::DesignEvaporatorTemperatureorBrineInletTemperature, true);
    }

    bool RefrigerationCase_Impl::setDesignEvaporatorTemperatureorBrineInletTemperature(double designEvaporatorTemperatureorBrineInletTemperature) {
      return setDouble(Refrigeration_CaseFields::DesignEvaporatorTemperatureorBrineInletTemperature,
                       designEvaporatorTemperatureorBrineInletTemperature);
    }

    void RefrigerationCase_Impl::resetDesignEvaporatorTemperatureorBrineInletTemperature() {
      OS_ASSERT(setString(Refrigeration_CaseFields::DesignEvaporatorTemperatureorBrineInletTemperature, ""));
    }

    double RefrigerationCase_Impl::averageRefrigerantChargeInventory() const {
      const auto value = getDouble(Refrigeration_CaseFields::AverageRefrigerantChargeInventory, true);
      OS_ASSERT(value);
      return *value;
    }

    bool RefrigerationCase_Impl::isAverageRefrigerantChargeInventoryDefaulted() const {
      return isEmpty(Refrigeration_CaseFields::AverageRefrigerantChargeInventory);
    }

    bool RefrigerationCase_Impl::setAverageRefrigerantChargeInventory(double averageRefrigerantChargeInventory) {
      const bool result = setDouble(Refrigeration_CaseFields::AverageRefrigerantChargeInventory, averageRefrigerantChargeInventory);
      OS_ASSERT(result);
      return result;
    }

    void RefrigerationCase_Impl::resetAverageRefrigerantChargeInventory() {
      OS_ASSERT(setString(Refrigeration_CaseFields::AverageRefrigerantChargeInventory, ""));
    }

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
