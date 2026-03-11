/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_REFRIGERATIONCASE_HPP
#define EPMODEL_REFRIGERATIONCASE_HPP

#include "EPModelAPI.hpp"
#include "ParentObject/ParentObject.hpp"

#include <utilities/idd/IddEnums.hxx>

#include <boost/optional.hpp>
#include <string>
#include <vector>

namespace openstudio {
namespace epmodel {

  class Model;

  namespace detail {
    class RefrigerationCase_Impl;
  }

  class EPMODEL_API RefrigerationCase : public ParentObject
  {
   public:
    explicit RefrigerationCase(const Model& model);

    virtual ~RefrigerationCase() override = default;
    RefrigerationCase(const RefrigerationCase& other) = default;
    RefrigerationCase(RefrigerationCase&& other) = default;
    RefrigerationCase& operator=(const RefrigerationCase&) = default;
    RefrigerationCase& operator=(RefrigerationCase&&) = default;

    static IddObjectType iddObjectType();

    static std::vector<std::string> latentCaseCreditCurveTypeValues();
    static std::vector<std::string> antiSweatHeaterControlTypeValues();
    static std::vector<std::string> caseDefrostTypeValues();
    static std::vector<std::string> defrostEnergyCorrectionCurveTypeValues();

    // Schema Alignment Notes:
    // - API: Preserve openstudio::model::RefrigerationCase scalar accessor names/signatures for the simple numeric and
    //   choice fields that map directly to EnergyPlus Refrigeration:Case.
    // - Field Mapping: Refrigeration_Case_FieldEnums and ForwardTranslateRefrigerationCase.cpp evidence that the retained
    //   scalars (rated ambient stats, fan/lighting powers, anti-sweat heater and defrost controls, etc.) map directly to
    //   Refrigeration:Case field enums.
    // - Field Mapping: Availability Schedule Name, Zone Name, Latent Case Credit Curve Name, Case Lighting Schedule Name,
    //   Case Defrost Schedule Name, Case Defrost Drip-Down Schedule Name, Defrost Energy Correction Curve Name,
    //   Refrigerated Case Restocking Schedule Name, Case Credit Fraction Schedule Name, and Under Case HVAC Return Air
    //   Node Name are richer relationship-like fields and are intentionally excluded from this scalar-only scaffold.

    /** @name Getters */
    //@{
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
    //@}

   protected:
    using ImplType = detail::RefrigerationCase_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    explicit RefrigerationCase(std::shared_ptr<detail::RefrigerationCase_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
