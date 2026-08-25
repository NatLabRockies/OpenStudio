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
  class Schedule;

  namespace detail {
    class RefrigerationCase_Impl;
  }

/** \brief Defines a refrigerated display case and its heat and moisture loads.
 *
 * \par EnergyPlus object
 * \epobject{group-refrigeration.html#refrigerationcase,Refrigeration:Case}
 *
 * \par Important behavior
 * Case temperature, capacity, lighting, anti-sweat, infiltration, defrost, fan, and refrigeration-load fields map directly to EnergyPlus.
 *
 * \par OpenStudio Model API
 * The corresponding OpenStudio Model class is <code>openstudio::model::RefrigerationCase</code>.
 * <b>Not yet available:</b> Model's compressor-rack, secondary-system, refrigeration-system, thermal-zone, curve, and detailed per-door/defrost relationship and convenience methods are not exposed.
 *
 * \par Known limitations
 * The case does not own the refrigeration system, compressor, condenser, or case-rack relationship.
 */
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


    /** @name Getters */
    //@{
    boost::optional<Schedule> availabilitySchedule() const;
    bool setAvailabilitySchedule(Schedule& schedule);
    void resetAvailabilitySchedule();

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

    boost::optional<Schedule> caseLightingSchedule() const;
    bool setCaseLightingSchedule(Schedule& schedule);
    void resetCaseLightingSchedule();

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

    boost::optional<Schedule> caseDefrostSchedule() const;
    bool setCaseDefrostSchedule(Schedule& schedule);
    void resetCaseDefrostSchedule();

    boost::optional<Schedule> caseDefrostDripDownSchedule() const;
    bool setCaseDefrostDripDownSchedule(Schedule& schedule);
    void resetCaseDefrostDripDownSchedule();

    std::string defrostEnergyCorrectionCurveType() const;
    bool isDefrostEnergyCorrectionCurveTypeDefaulted() const;
    bool setDefrostEnergyCorrectionCurveType(const std::string& defrostEnergyCorrectionCurveType);
    void resetDefrostEnergyCorrectionCurveType();

    double underCaseHVACReturnAirFraction() const;
    bool isUnderCaseHVACReturnAirFractionDefaulted() const;
    bool setUnderCaseHVACReturnAirFraction(double underCaseHVACReturnAirFraction);
    void resetUnderCaseHVACReturnAirFraction();

    boost::optional<Schedule> refrigeratedCaseRestockingSchedule() const;
    bool setRefrigeratedCaseRestockingSchedule(Schedule& schedule);
    void resetRefrigeratedCaseRestockingSchedule();

    boost::optional<Schedule> caseCreditFractionSchedule() const;
    bool setCaseCreditFractionSchedule(Schedule& schedule);
    void resetCaseCreditFractionSchedule();

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
