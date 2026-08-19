/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_COOLINGTOWERVARIABLESPEED_HPP
#define EPMODEL_COOLINGTOWERVARIABLESPEED_HPP

#include "EPModelAPI.hpp"
#include "StraightComponent/StraightComponent.hpp"

#include <memory>
#include <vector>

namespace openstudio {
namespace epmodel {

  class Model;
  class ModelObject;
  class Schedule;
  class CurveCubic;

  namespace detail {
    class CoolingTowerVariableSpeed_Impl;
  }

  /** \brief Represents a variable-speed cooling tower.
   *
   * \par EnergyPlus object
   * \epobject{group-condenser-equipment.html#coolingtowervariablespeed,CoolingTower:VariableSpeed}.
   *
   * \par Important behavior
   * The persisted scalar, schedule, and currently supported performance relationships use the EnergyPlus coil topology.
   *
   * \par OpenStudio Model API
   * The corresponding OpenStudio Model class is <code>openstudio::model::CoolingTowerVariableSpeed</code>. No known public API differences after comparing the headers; parameter names differ only trivially in a few setters.
   * \par Known limitations
   * No known EPModel-specific limitations beyond the listed API differences.
   */
  class EPMODEL_API CoolingTowerVariableSpeed : public StraightComponent
  {
   public:
    explicit CoolingTowerVariableSpeed(const Model& model);

    virtual ~CoolingTowerVariableSpeed() override = default;
    CoolingTowerVariableSpeed(const CoolingTowerVariableSpeed& other) = default;
    CoolingTowerVariableSpeed(CoolingTowerVariableSpeed&& other) = default;
    CoolingTowerVariableSpeed& operator=(const CoolingTowerVariableSpeed&) = default;
    CoolingTowerVariableSpeed& operator=(CoolingTowerVariableSpeed&&) = default;

    static IddObjectType iddObjectType();

    static std::vector<std::string> modelTypeValues();
    static std::vector<std::string> evaporationLossModeValues();
    static std::vector<std::string> blowdownCalculationModeValues();
    static std::vector<std::string> cellControlValues();

    boost::optional<std::string> modelType() const;
    bool setModelType(const std::string& modelType);
    void resetModelType();

    boost::optional<ModelObject> modelCoefficient() const;
    bool setModelCoefficient(const ModelObject& modelCoefficient);
    void resetModelCoefficient();

    boost::optional<double> designInletAirWetBulbTemperature() const;
    bool setDesignInletAirWetBulbTemperature(double designInletAirWetBulbTemperature);
    void resetDesignInletAirWetBulbTemperature();

    boost::optional<double> designApproachTemperature() const;
    bool setDesignApproachTemperature(double designApproachTemperature);
    void resetDesignApproachTemperature();

    boost::optional<double> designRangeTemperature() const;
    bool setDesignRangeTemperature(double designRangeTemperature);
    void resetDesignRangeTemperature();

    boost::optional<double> designWaterFlowRate() const;
    bool isDesignWaterFlowRateAutosized() const;
    bool setDesignWaterFlowRate(double designWaterFlowRate);
    void autosizeDesignWaterFlowRate();

    boost::optional<double> designAirFlowRate() const;
    bool isDesignAirFlowRateAutosized() const;
    bool setDesignAirFlowRate(double designAirFlowRate);
    void autosizeDesignAirFlowRate();

    boost::optional<double> designFanPower() const;
    bool isDesignFanPowerAutosized() const;
    bool setDesignFanPower(double designFanPower);
    void autosizeDesignFanPower();

    boost::optional<CurveCubic> fanPowerRatioFunctionofAirFlowRateRatioCurve() const;
    bool setFanPowerRatioFunctionofAirFlowRateRatioCurve(const CurveCubic& curve);
    void resetFanPowerRatioFunctionofAirFlowRateRatioCurve();

    boost::optional<double> minimumAirFlowRateRatio() const;
    bool setMinimumAirFlowRateRatio(double minimumAirFlowRateRatio);
    void resetMinimumAirFlowRateRatio();

    boost::optional<double> fractionofTowerCapacityinFreeConvectionRegime() const;
    bool setFractionofTowerCapacityinFreeConvectionRegime(double fractionofTowerCapacityinFreeConvectionRegime);
    void resetFractionofTowerCapacityinFreeConvectionRegime();

    boost::optional<double> basinHeaterCapacity() const;
    bool setBasinHeaterCapacity(double basinHeaterCapacity);
    void resetBasinHeaterCapacity();

    boost::optional<double> basinHeaterSetpointTemperature() const;
    bool setBasinHeaterSetpointTemperature(double basinHeaterSetpointTemperature);
    void resetBasinHeaterSetpointTemperature();

    boost::optional<Schedule> basinHeaterOperatingSchedule() const;
    bool setBasinHeaterOperatingSchedule(Schedule& basinHeaterOperatingSchedule);
    void resetBasinHeaterOperatingSchedule();

    std::string evaporationLossMode() const;
    bool setEvaporationLossMode(const std::string& evaporationLossMode);
    bool isEvaporationLossModeDefaulted() const;
    void resetEvaporationLossMode();

    double evaporationLossFactor() const;
    bool setEvaporationLossFactor(double evaporationLossFactor);
    bool isEvaporationLossFactorDefaulted() const;
    void resetEvaporationLossFactor();

    boost::optional<double> driftLossPercent() const;
    bool setDriftLossPercent(double driftLossPercent);
    void resetDriftLossPercent();

    std::string blowdownCalculationMode() const;
    bool setBlowdownCalculationMode(const std::string& blowdownCalculationMode);
    bool isBlowdownCalculationModeDefaulted() const;
    void resetBlowdownCalculationMode();

    boost::optional<double> blowdownConcentrationRatio() const;
    bool setBlowdownConcentrationRatio(double blowdownConcentrationRatio);
    void resetBlowdownConcentrationRatio();

    boost::optional<Schedule> blowdownMakeupWaterUsageSchedule() const;
    bool setBlowdownMakeupWaterUsageSchedule(Schedule& blowdownMakeupWaterUsageSchedule);
    void resetBlowdownMakeupWaterUsageSchedule();

    boost::optional<int> numberofCells() const;
    bool setNumberofCells(int numberofCells);
    void resetNumberofCells();

    std::string cellControl() const;
    bool setCellControl(const std::string& cellControl);
    bool isCellControlDefaulted() const;
    void resetCellControl();

    boost::optional<double> cellMinimumWaterFlowRateFraction() const;
    bool setCellMinimumWaterFlowRateFraction(double cellMinimumWaterFlowRateFraction);
    void resetCellMinimumWaterFlowRateFraction();

    boost::optional<double> cellMaximumWaterFlowRateFraction() const;
    bool setCellMaximumWaterFlowRateFraction(double cellMaximumWaterFlowRateFraction);
    void resetCellMaximumWaterFlowRateFraction();

    boost::optional<double> sizingFactor() const;
    bool setSizingFactor(double sizingFactor);
    void resetSizingFactor();

    boost::optional<double> autosizedDesignWaterFlowRate() const;
    boost::optional<double> autosizedDesignAirFlowRate() const;
    boost::optional<double> autosizedDesignFanPower() const;

    std::string endUseSubcategory() const;
    bool setEndUseSubcategory(const std::string& endUseSubcategory);

   protected:
    using ImplType = detail::CoolingTowerVariableSpeed_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    explicit CoolingTowerVariableSpeed(std::shared_ptr<detail::CoolingTowerVariableSpeed_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
