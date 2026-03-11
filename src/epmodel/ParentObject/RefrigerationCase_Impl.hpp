/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_REFRIGERATIONCASE_IMPL_HPP
#define EPMODEL_REFRIGERATIONCASE_IMPL_HPP

#include "ParentObject/ParentObject_Impl.hpp"

#include <boost/optional.hpp>

namespace openstudio {
namespace epmodel {
  namespace detail {

    class EPMODEL_API RefrigerationCase_Impl : public ParentObject_Impl
    {
     public:
      using ParentObject_Impl::ParentObject_Impl;
      virtual ~RefrigerationCase_Impl() override = default;

      double ratedAmbientTemperature() const;
      bool isRatedAmbientTemperatureDefaulted() const;
      bool setRatedAmbientTemperature(double ratedAmbientTemperature);
      void resetRatedAmbientTemperature();

      double ratedAmbientRelativeHumidity() const;
      bool isRatedAmbientRelativeHumidityDefaulted() const;
      bool setRatedAmbientRelativeHumidity(double ratedAmbientRelativeHumidity);
      void resetRatedAmbientRelativeHumidity();

      double ratedTotalCoolingCapacityperUnitLength() const;
      bool isRatedTotalCoolingCapacityperUnitLengthDefaulted() const;
      bool setRatedTotalCoolingCapacityperUnitLength(double ratedTotalCoolingCapacityperUnitLength);
      void resetRatedTotalCoolingCapacityperUnitLength();

      double ratedLatentHeatRatio() const;
      bool isRatedLatentHeatRatioDefaulted() const;
      bool setRatedLatentHeatRatio(double ratedLatentHeatRatio);
      void resetRatedLatentHeatRatio();

      double ratedRuntimeFraction() const;
      bool isRatedRuntimeFractionDefaulted() const;
      bool setRatedRuntimeFraction(double ratedRuntimeFraction);
      void resetRatedRuntimeFraction();

      double caseLength() const;
      bool isCaseLengthDefaulted() const;
      bool setCaseLength(double caseLength);
      void resetCaseLength();

      double caseOperatingTemperature() const;
      bool isCaseOperatingTemperatureDefaulted() const;
      bool setCaseOperatingTemperature(double caseOperatingTemperature);
      void resetCaseOperatingTemperature();

      std::string latentCaseCreditCurveType() const;
      bool isLatentCaseCreditCurveTypeDefaulted() const;
      bool setLatentCaseCreditCurveType(const std::string& latentCaseCreditCurveType);
      void resetLatentCaseCreditCurveType();

      double standardCaseFanPowerperUnitLength() const;
      bool isStandardCaseFanPowerperUnitLengthDefaulted() const;
      bool setStandardCaseFanPowerperUnitLength(double standardCaseFanPowerperUnitLength);
      void resetStandardCaseFanPowerperUnitLength();

      double operatingCaseFanPowerperUnitLength() const;
      bool isOperatingCaseFanPowerperUnitLengthDefaulted() const;
      bool setOperatingCaseFanPowerperUnitLength(double operatingCaseFanPowerperUnitLength);
      void resetOperatingCaseFanPowerperUnitLength();

      double standardCaseLightingPowerperUnitLength() const;
      bool isStandardCaseLightingPowerperUnitLengthDefaulted() const;
      bool setStandardCaseLightingPowerperUnitLength(double standardCaseLightingPowerperUnitLength);
      void resetStandardCaseLightingPowerperUnitLength();

      boost::optional<double> installedCaseLightingPowerperUnitLength() const;
      bool setInstalledCaseLightingPowerperUnitLength(double installedCaseLightingPowerperUnitLength);
      void resetInstalledCaseLightingPowerperUnitLength();

      double fractionofLightingEnergytoCase() const;
      bool isFractionofLightingEnergytoCaseDefaulted() const;
      bool setFractionofLightingEnergytoCase(double fractionofLightingEnergytoCase);
      void resetFractionofLightingEnergytoCase();

      double caseAntiSweatHeaterPowerperUnitLength() const;
      bool isCaseAntiSweatHeaterPowerperUnitLengthDefaulted() const;
      bool setCaseAntiSweatHeaterPowerperUnitLength(double caseAntiSweatHeaterPowerperUnitLength);
      void resetCaseAntiSweatHeaterPowerperUnitLength();

      double minimumAntiSweatHeaterPowerperUnitLength() const;
      bool isMinimumAntiSweatHeaterPowerperUnitLengthDefaulted() const;
      bool setMinimumAntiSweatHeaterPowerperUnitLength(double minimumAntiSweatHeaterPowerperUnitLength);
      void resetMinimumAntiSweatHeaterPowerperUnitLength();

      std::string antiSweatHeaterControlType() const;
      bool isAntiSweatHeaterControlTypeDefaulted() const;
      bool setAntiSweatHeaterControlType(const std::string& antiSweatHeaterControlType);
      void resetAntiSweatHeaterControlType();

      double humidityatZeroAntiSweatHeaterEnergy() const;
      bool isHumidityatZeroAntiSweatHeaterEnergyDefaulted() const;
      bool setHumidityatZeroAntiSweatHeaterEnergy(double humidityatZeroAntiSweatHeaterEnergy);
      void resetHumidityatZeroAntiSweatHeaterEnergy();

      double caseHeight() const;
      bool isCaseHeightDefaulted() const;
      bool setCaseHeight(double caseHeight);
      void resetCaseHeight();

      double fractionofAntiSweatHeaterEnergytoCase() const;
      bool isFractionofAntiSweatHeaterEnergytoCaseDefaulted() const;
      bool setFractionofAntiSweatHeaterEnergytoCase(double fractionofAntiSweatHeaterEnergytoCase);
      void resetFractionofAntiSweatHeaterEnergytoCase();

      double caseDefrostPowerperUnitLength() const;
      bool isCaseDefrostPowerperUnitLengthDefaulted() const;
      bool setCaseDefrostPowerperUnitLength(double caseDefrostPowerperUnitLength);
      void resetCaseDefrostPowerperUnitLength();

      std::string caseDefrostType() const;
      bool isCaseDefrostTypeDefaulted() const;
      bool setCaseDefrostType(const std::string& caseDefrostType);
      void resetCaseDefrostType();

      std::string defrostEnergyCorrectionCurveType() const;
      bool isDefrostEnergyCorrectionCurveTypeDefaulted() const;
      bool setDefrostEnergyCorrectionCurveType(const std::string& defrostEnergyCorrectionCurveType);
      void resetDefrostEnergyCorrectionCurveType();

      double underCaseHVACReturnAirFraction() const;
      bool isUnderCaseHVACReturnAirFractionDefaulted() const;
      bool setUnderCaseHVACReturnAirFraction(double underCaseHVACReturnAirFraction);
      void resetUnderCaseHVACReturnAirFraction();

      boost::optional<double> designEvaporatorTemperatureorBrineInletTemperature() const;
      bool setDesignEvaporatorTemperatureorBrineInletTemperature(double designEvaporatorTemperatureorBrineInletTemperature);
      void resetDesignEvaporatorTemperatureorBrineInletTemperature();

      double averageRefrigerantChargeInventory() const;
      bool isAverageRefrigerantChargeInventoryDefaulted() const;
      bool setAverageRefrigerantChargeInventory(double averageRefrigerantChargeInventory);
      void resetAverageRefrigerantChargeInventory();
    };

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
