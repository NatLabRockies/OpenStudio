/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_EVAPORATIVEFLUIDCOOLERSINGLESPEED_HPP
#define EPMODEL_EVAPORATIVEFLUIDCOOLERSINGLESPEED_HPP

#include "EPModelAPI.hpp"
#include "StraightComponent/StraightComponent.hpp"

#include <boost/optional.hpp>

#include <memory>
#include <string>
#include <vector>

namespace openstudio {
namespace epmodel {

  class Model;

  namespace detail {
    class EvaporativeFluidCoolerSingleSpeed_Impl;
  }

  class EPMODEL_API EvaporativeFluidCoolerSingleSpeed : public StraightComponent
  {
   public:
    explicit EvaporativeFluidCoolerSingleSpeed(const Model& model);

    virtual ~EvaporativeFluidCoolerSingleSpeed() override = default;
    EvaporativeFluidCoolerSingleSpeed(const EvaporativeFluidCoolerSingleSpeed& other) = default;
    EvaporativeFluidCoolerSingleSpeed(EvaporativeFluidCoolerSingleSpeed&& other) = default;
    EvaporativeFluidCoolerSingleSpeed& operator=(const EvaporativeFluidCoolerSingleSpeed&) = default;
    EvaporativeFluidCoolerSingleSpeed& operator=(EvaporativeFluidCoolerSingleSpeed&&) = default;

    static IddObjectType iddObjectType();

    static std::vector<std::string> performanceInputMethodValues();
    static std::vector<std::string> capacityControlValues();
    static std::vector<std::string> evaporationLossModeValues();
    static std::vector<std::string> blowdownCalculationModeValues();

    // Schema Alignment Notes:
    // - API: Preserve openstudio::model::EvaporativeFluidCoolerSingleSpeed scalar accessor names/signatures.
    // - Field Mapping: fanPoweratDesignAirFlowRate maps to E+ field DesignAirFlowRateFanPower.
    // - Field Mapping: ufactorTimesAreaValueatDesignAirFlowRate maps to E+ field DesignAirFlowRateUfactorTimesAreaValue.
    // - Field Mapping: all other scalar APIs map directly to matching E+ EvaporativeFluidCooler:SingleSpeed fields.
    // - Field Mapping: node/schedule/storage-tank relationship-like fields are intentionally excluded from this scalar-only pass.
    // - ForwardTranslator evidence: ForwardTranslateEvaporativeFluidCoolerSingleSpeed.cpp maps preserved scalar APIs to these fields.
    // - TODO(parity): Add excluded relationship APIs without changing preserved scalar signatures.

    boost::optional<double> designAirFlowRate() const;
    bool isDesignAirFlowRateAutosized() const;
    bool setDesignAirFlowRate(double designAirFlowRate);
    void autosizeDesignAirFlowRate();
    boost::optional<double> autosizedDesignAirFlowRate() const;

    boost::optional<double> fanPoweratDesignAirFlowRate() const;
    bool isFanPoweratDesignAirFlowRateAutosized() const;
    bool setFanPoweratDesignAirFlowRate(double fanPoweratDesignAirFlowRate);
    void autosizeFanPoweratDesignAirFlowRate();
    boost::optional<double> autosizedFanPoweratDesignAirFlowRate() const;

    double designSprayWaterFlowRate() const;
    bool setDesignSprayWaterFlowRate(double designSprayWaterFlowRate);

    std::string performanceInputMethod() const;
    bool setPerformanceInputMethod(const std::string& performanceInputMethod);

    double heatRejectionCapacityandNominalCapacitySizingRatio() const;
    bool setHeatRejectionCapacityandNominalCapacitySizingRatio(double heatRejectionCapacityandNominalCapacitySizingRatio);

    boost::optional<double> standardDesignCapacity() const;
    bool setStandardDesignCapacity(double standardDesignCapacity);
    void resetStandardDesignCapacity();

    boost::optional<double> ufactorTimesAreaValueatDesignAirFlowRate() const;
    bool isUfactorTimesAreaValueatDesignAirFlowRateAutosized() const;
    bool setUfactorTimesAreaValueatDesignAirFlowRate(double ufactorTimesAreaValueatDesignAirFlowRate);
    void resetUfactorTimesAreaValueatDesignAirFlowRate();
    void autosizeUfactorTimesAreaValueatDesignAirFlowRate();
    boost::optional<double> autosizedUfactorTimesAreaValueatDesignAirFlowRate() const;

    boost::optional<double> designWaterFlowRate() const;
    bool isDesignWaterFlowRateAutosized() const;
    bool setDesignWaterFlowRate(double designWaterFlowRate);
    void resetDesignWaterFlowRate();
    void autosizeDesignWaterFlowRate();
    boost::optional<double> autosizedDesignWaterFlowRate() const;

    boost::optional<double> userSpecifiedDesignCapacity() const;
    bool setUserSpecifiedDesignCapacity(double userSpecifiedDesignCapacity);
    void resetUserSpecifiedDesignCapacity();

    boost::optional<double> designEnteringWaterTemperature() const;
    bool isDesignEnteringWaterTemperatureAutosized() const;
    bool setDesignEnteringWaterTemperature(double designEnteringWaterTemperature);
    void autosizeDesignEnteringWaterTemperature();
    boost::optional<double> autosizedDesignEnteringWaterTemperature() const;

    double designEnteringAirTemperature() const;
    bool setDesignEnteringAirTemperature(double designEnteringAirTemperature);

    double designEnteringAirWetbulbTemperature() const;
    bool setDesignEnteringAirWetbulbTemperature(double designEnteringAirWetbulbTemperature);

    std::string capacityControl() const;
    bool isCapacityControlDefaulted() const;
    bool setCapacityControl(const std::string& capacityControl);
    void resetCapacityControl();

    double sizingFactor() const;
    bool isSizingFactorDefaulted() const;
    bool setSizingFactor(double sizingFactor);
    void resetSizingFactor();

    std::string evaporationLossMode() const;
    bool isEvaporationLossModeDefaulted() const;
    bool setEvaporationLossMode(const std::string& evaporationLossMode);
    void resetEvaporationLossMode();

    boost::optional<double> evaporationLossFactor() const;
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

   protected:
    using ImplType = detail::EvaporativeFluidCoolerSingleSpeed_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    explicit EvaporativeFluidCoolerSingleSpeed(std::shared_ptr<detail::EvaporativeFluidCoolerSingleSpeed_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
