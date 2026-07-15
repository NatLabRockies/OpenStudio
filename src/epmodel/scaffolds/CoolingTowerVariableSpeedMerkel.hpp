/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_COOLINGTOWERVARIABLESPEEDMERKEL_HPP
#define EPMODEL_COOLINGTOWERVARIABLESPEEDMERKEL_HPP

#include "EPModelAPI.hpp"
#include "ModelObject.hpp"

#include <utilities/idd/IddEnums.hxx>

#include <memory>
#include <vector>

namespace openstudio {
namespace epmodel {

  class Model;

  namespace detail {
    class CoolingTowerVariableSpeedMerkel_Impl;
  }

  class EPMODEL_API CoolingTowerVariableSpeedMerkel : public ModelObject
  {
   public:
    explicit CoolingTowerVariableSpeedMerkel(const Model& model);

    virtual ~CoolingTowerVariableSpeedMerkel() override = default;
    CoolingTowerVariableSpeedMerkel(const CoolingTowerVariableSpeedMerkel& other) = default;
    CoolingTowerVariableSpeedMerkel(CoolingTowerVariableSpeedMerkel&& other) = default;
    CoolingTowerVariableSpeedMerkel& operator=(const CoolingTowerVariableSpeedMerkel&) = default;
    CoolingTowerVariableSpeedMerkel& operator=(CoolingTowerVariableSpeedMerkel&&) = default;

    static IddObjectType iddObjectType();

    static std::vector<std::string> performanceInputMethodValues();
    static std::vector<std::string> evaporationLossModeValues();
    static std::vector<std::string> blowdownCalculationModeValues();
    static std::vector<std::string> cellControlValues();

    // Schema Alignment Notes:
    // - API: This no-counterpart type uses IDD-derived class/accessor naming.
    // - Field Mapping: Scalar APIs map directly to CoolingTower:VariableSpeed:Merkel scalar fields.
    // - Field Mapping: Water inlet/outlet and outdoor air nodes, curve names, schedules, and tank-name links are excluded as relationship fields.
    // - TODO(parity): Add relationship APIs incrementally after scalar saturation without changing scalar signatures.
    std::string performanceInputMethod() const;
    bool isPerformanceInputMethodDefaulted() const;
    bool setPerformanceInputMethod(const std::string& performanceInputMethod);
    void resetPerformanceInputMethod();

    double heatRejectionCapacityandNominalCapacitySizingRatio() const;
    bool isHeatRejectionCapacityandNominalCapacitySizingRatioDefaulted() const;
    bool setHeatRejectionCapacityandNominalCapacitySizingRatio(double heatRejectionCapacityandNominalCapacitySizingRatio);
    void resetHeatRejectionCapacityandNominalCapacitySizingRatio();

    boost::optional<double> nominalCapacity() const;
    bool isNominalCapacityAutosized() const;
    bool setNominalCapacity(double nominalCapacity);
    void resetNominalCapacity();
    void autosizeNominalCapacity();

    boost::optional<double> freeConvectionNominalCapacity() const;
    bool isFreeConvectionNominalCapacityAutocalculated() const;
    bool setFreeConvectionNominalCapacity(double freeConvectionNominalCapacity);
    void resetFreeConvectionNominalCapacity();
    void autocalculateFreeConvectionNominalCapacity();

    double freeConvectionNominalCapacitySizingFactor() const;
    bool isFreeConvectionNominalCapacitySizingFactorDefaulted() const;
    bool setFreeConvectionNominalCapacitySizingFactor(double freeConvectionNominalCapacitySizingFactor);
    void resetFreeConvectionNominalCapacitySizingFactor();

    boost::optional<double> designWaterFlowRate() const;
    bool isDesignWaterFlowRateAutosized() const;
    bool setDesignWaterFlowRate(double designWaterFlowRate);
    void autosizeDesignWaterFlowRate();

    double designWaterFlowRateperUnitofNominalCapacity() const;
    bool isDesignWaterFlowRateperUnitofNominalCapacityDefaulted() const;
    bool setDesignWaterFlowRateperUnitofNominalCapacity(double designWaterFlowRateperUnitofNominalCapacity);
    void resetDesignWaterFlowRateperUnitofNominalCapacity();

    boost::optional<double> designAirFlowRate() const;
    bool isDesignAirFlowRateAutocalculated() const;
    bool setDesignAirFlowRate(double designAirFlowRate);
    void autocalculateDesignAirFlowRate();

    double designAirFlowRatePerUnitofNominalCapacity() const;
    bool isDesignAirFlowRatePerUnitofNominalCapacityDefaulted() const;
    bool setDesignAirFlowRatePerUnitofNominalCapacity(double designAirFlowRatePerUnitofNominalCapacity);
    void resetDesignAirFlowRatePerUnitofNominalCapacity();

    double minimumAirFlowRateRatio() const;
    bool isMinimumAirFlowRateRatioDefaulted() const;
    bool setMinimumAirFlowRateRatio(double minimumAirFlowRateRatio);
    void resetMinimumAirFlowRateRatio();

    boost::optional<double> designFanPower() const;
    bool isDesignFanPowerAutocalculated() const;
    bool setDesignFanPower(double designFanPower);
    void autocalculateDesignFanPower();

    double designFanPowerPerUnitofNominalCapacity() const;
    bool isDesignFanPowerPerUnitofNominalCapacityDefaulted() const;
    bool setDesignFanPowerPerUnitofNominalCapacity(double designFanPowerPerUnitofNominalCapacity);
    void resetDesignFanPowerPerUnitofNominalCapacity();

    boost::optional<double> freeConvectionRegimeAirFlowRate() const;
    bool isFreeConvectionRegimeAirFlowRateAutocalculated() const;
    bool setFreeConvectionRegimeAirFlowRate(double freeConvectionRegimeAirFlowRate);
    void resetFreeConvectionRegimeAirFlowRate();
    void autocalculateFreeConvectionRegimeAirFlowRate();

    double freeConvectionRegimeAirFlowRateSizingFactor() const;
    bool isFreeConvectionRegimeAirFlowRateSizingFactorDefaulted() const;
    bool setFreeConvectionRegimeAirFlowRateSizingFactor(double freeConvectionRegimeAirFlowRateSizingFactor);
    void resetFreeConvectionRegimeAirFlowRateSizingFactor();

    boost::optional<double> designAirFlowRateUFactorTimesAreaValue() const;
    bool isDesignAirFlowRateUFactorTimesAreaValueAutosized() const;
    bool setDesignAirFlowRateUFactorTimesAreaValue(double designAirFlowRateUFactorTimesAreaValue);
    void resetDesignAirFlowRateUFactorTimesAreaValue();
    void autosizeDesignAirFlowRateUFactorTimesAreaValue();

    boost::optional<double> freeConvectionRegimeUFactorTimesAreaValue() const;
    bool isFreeConvectionRegimeUFactorTimesAreaValueAutocalculated() const;
    bool setFreeConvectionRegimeUFactorTimesAreaValue(double freeConvectionRegimeUFactorTimesAreaValue);
    void resetFreeConvectionRegimeUFactorTimesAreaValue();
    void autocalculateFreeConvectionRegimeUFactorTimesAreaValue();

    double freeConvectionUFactorTimesAreaValueSizingFactor() const;
    bool isFreeConvectionUFactorTimesAreaValueSizingFactorDefaulted() const;
    bool setFreeConvectionUFactorTimesAreaValueSizingFactor(double freeConvectionUFactorTimesAreaValueSizingFactor);
    void resetFreeConvectionUFactorTimesAreaValueSizingFactor();

    double designInletAirDryBulbTemperature() const;
    bool isDesignInletAirDryBulbTemperatureDefaulted() const;
    bool setDesignInletAirDryBulbTemperature(double designInletAirDryBulbTemperature);
    void resetDesignInletAirDryBulbTemperature();

    double designInletAirWetBulbTemperature() const;
    bool isDesignInletAirWetBulbTemperatureDefaulted() const;
    bool setDesignInletAirWetBulbTemperature(double designInletAirWetBulbTemperature);
    void resetDesignInletAirWetBulbTemperature();

    boost::optional<double> designApproachTemperature() const;
    bool isDesignApproachTemperatureDefaulted() const;
    bool isDesignApproachTemperatureAutosized() const;
    bool setDesignApproachTemperature(double designApproachTemperature);
    void resetDesignApproachTemperature();
    void autosizeDesignApproachTemperature();

    boost::optional<double> designRangeTemperature() const;
    bool isDesignRangeTemperatureDefaulted() const;
    bool isDesignRangeTemperatureAutosized() const;
    bool setDesignRangeTemperature(double designRangeTemperature);
    void resetDesignRangeTemperature();
    void autosizeDesignRangeTemperature();

    double basinHeaterCapacity() const;
    bool isBasinHeaterCapacityDefaulted() const;
    bool setBasinHeaterCapacity(double basinHeaterCapacity);
    void resetBasinHeaterCapacity();

    double basinHeaterSetpointTemperature() const;
    bool isBasinHeaterSetpointTemperatureDefaulted() const;
    bool setBasinHeaterSetpointTemperature(double basinHeaterSetpointTemperature);
    void resetBasinHeaterSetpointTemperature();

    std::string evaporationLossMode() const;
    bool isEvaporationLossModeDefaulted() const;
    bool setEvaporationLossMode(const std::string& evaporationLossMode);
    void resetEvaporationLossMode();

    double evaporationLossFactor() const;
    bool isEvaporationLossFactorDefaulted() const;
    bool setEvaporationLossFactor(double evaporationLossFactor);
    void resetEvaporationLossFactor();

    double driftLossPercent() const;
    bool isDriftLossPercentDefaulted() const;
    bool setDriftLossPercent(double driftLossPercent);
    void resetDriftLossPercent();

    std::string blowdownCalculationMode() const;
    bool isBlowdownCalculationModeDefaulted() const;
    bool setBlowdownCalculationMode(const std::string& blowdownCalculationMode);
    void resetBlowdownCalculationMode();

    double blowdownConcentrationRatio() const;
    bool isBlowdownConcentrationRatioDefaulted() const;
    bool setBlowdownConcentrationRatio(double blowdownConcentrationRatio);
    void resetBlowdownConcentrationRatio();

    int numberofCells() const;
    bool isNumberofCellsDefaulted() const;
    bool setNumberofCells(int numberofCells);
    void resetNumberofCells();

    std::string cellControl() const;
    bool isCellControlDefaulted() const;
    bool setCellControl(const std::string& cellControl);
    void resetCellControl();

    double cellMinimumWaterFlowRateFraction() const;
    bool isCellMinimumWaterFlowRateFractionDefaulted() const;
    bool setCellMinimumWaterFlowRateFraction(double cellMinimumWaterFlowRateFraction);
    void resetCellMinimumWaterFlowRateFraction();

    double cellMaximumWaterFlowRateFraction() const;
    bool isCellMaximumWaterFlowRateFractionDefaulted() const;
    bool setCellMaximumWaterFlowRateFraction(double cellMaximumWaterFlowRateFraction);
    void resetCellMaximumWaterFlowRateFraction();

    double sizingFactor() const;
    bool isSizingFactorDefaulted() const;
    bool setSizingFactor(double sizingFactor);
    void resetSizingFactor();

    std::string endUseSubcategory() const;
    bool isEndUseSubcategoryDefaulted() const;
    bool setEndUseSubcategory(const std::string& endUseSubcategory);
    void resetEndUseSubcategory();

   protected:
    using ImplType = detail::CoolingTowerVariableSpeedMerkel_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    explicit CoolingTowerVariableSpeedMerkel(std::shared_ptr<detail::CoolingTowerVariableSpeedMerkel_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
