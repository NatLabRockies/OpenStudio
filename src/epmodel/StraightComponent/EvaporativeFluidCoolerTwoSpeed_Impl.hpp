/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_EVAPORATIVEFLUIDCOOLERTWOSPEED_IMPL_HPP
#define EPMODEL_EVAPORATIVEFLUIDCOOLERTWOSPEED_IMPL_HPP

#include "StraightComponent/StraightComponent_Impl.hpp"

#include <boost/optional.hpp>

#include <string>
#include <vector>

namespace openstudio {
namespace epmodel {
  namespace detail {

    class EPMODEL_API EvaporativeFluidCoolerTwoSpeed_Impl : public StraightComponent_Impl
    {
     public:
      using StraightComponent_Impl::StraightComponent_Impl;
      virtual ~EvaporativeFluidCoolerTwoSpeed_Impl() override = default;

      unsigned inletPort() const override;
      unsigned outletPort() const override;
      bool addToNode(Node& node) override;

      std::vector<std::string> performanceInputMethodValues() const;
      std::vector<std::string> evaporationLossModeValues() const;
      std::vector<std::string> blowdownCalculationModeValues() const;

      boost::optional<double> highFanSpeedAirFlowRate() const;
      bool isHighFanSpeedAirFlowRateAutosized() const;
      bool setHighFanSpeedAirFlowRate(boost::optional<double> highFanSpeedAirFlowRate);
      void autosizeHighFanSpeedAirFlowRate();

      boost::optional<double> highFanSpeedFanPower() const;
      bool isHighFanSpeedFanPowerAutosized() const;
      bool setHighFanSpeedFanPower(boost::optional<double> highFanSpeedFanPower);
      void autosizeHighFanSpeedFanPower();

      boost::optional<double> lowFanSpeedAirFlowRate() const;
      bool isLowFanSpeedAirFlowRateAutosized() const;
      bool setLowFanSpeedAirFlowRate(boost::optional<double> lowFanSpeedAirFlowRate);
      void autosizeLowFanSpeedAirFlowRate();

      double lowFanSpeedAirFlowRateSizingFactor() const;
      bool setLowFanSpeedAirFlowRateSizingFactor(double lowFanSpeedAirFlowRateSizingFactor);

      boost::optional<double> lowFanSpeedFanPower() const;
      bool isLowFanSpeedFanPowerAutosized() const;
      bool setLowFanSpeedFanPower(boost::optional<double> lowFanSpeedFanPower);
      void autosizeLowFanSpeedFanPower();

      double lowFanSpeedFanPowerSizingFactor() const;
      bool setLowFanSpeedFanPowerSizingFactor(double lowFanSpeedFanPowerSizingFactor);

      double designSprayWaterFlowRate() const;
      bool setDesignSprayWaterFlowRate(double designSprayWaterFlowRate);

      std::string performanceInputMethod() const;
      bool setPerformanceInputMethod(const std::string& performanceInputMethod);

      double heatRejectionCapacityandNominalCapacitySizingRatio() const;
      bool setHeatRejectionCapacityandNominalCapacitySizingRatio(double heatRejectionCapacityandNominalCapacitySizingRatio);

      boost::optional<double> highSpeedStandardDesignCapacity() const;
      bool setHighSpeedStandardDesignCapacity(boost::optional<double> highSpeedStandardDesignCapacity);
      void resetHighSpeedStandardDesignCapacity();

      boost::optional<double> lowSpeedStandardDesignCapacity() const;
      bool isLowSpeedStandardDesignCapacityAutosized() const;
      bool setLowSpeedStandardDesignCapacity(boost::optional<double> lowSpeedStandardDesignCapacity);
      void resetLowSpeedStandardDesignCapacity();
      void autosizeLowSpeedStandardDesignCapacity();

      double lowSpeedStandardCapacitySizingFactor() const;
      bool setLowSpeedStandardCapacitySizingFactor(double lowSpeedStandardCapacitySizingFactor);

      boost::optional<double> highFanSpeedUfactorTimesAreaValue() const;
      bool isHighFanSpeedUfactorTimesAreaValueAutosized() const;
      bool setHighFanSpeedUfactorTimesAreaValue(boost::optional<double> highFanSpeedUfactorTimesAreaValue);
      void resetHighFanSpeedUfactorTimesAreaValue();
      void autosizeHighFanSpeedUfactorTimesAreaValue();

      boost::optional<double> lowFanSpeedUfactorTimesAreaValue() const;
      bool isLowFanSpeedUfactorTimesAreaValueAutosized() const;
      bool setLowFanSpeedUfactorTimesAreaValue(boost::optional<double> lowFanSpeedUfactorTimesAreaValue);
      void resetLowFanSpeedUfactorTimesAreaValue();
      void autosizeLowFanSpeedUfactorTimesAreaValue();

      double lowFanSpeedUFactorTimesAreaSizingFactor() const;
      bool setLowFanSpeedUFactorTimesAreaSizingFactor(double lowFanSpeedUFactorTimesAreaSizingFactor);

      boost::optional<double> designWaterFlowRate() const;
      bool isDesignWaterFlowRateAutosized() const;
      bool setDesignWaterFlowRate(boost::optional<double> designWaterFlowRate);
      void resetDesignWaterFlowRate();
      void autosizeDesignWaterFlowRate();

      boost::optional<double> highSpeedUserSpecifiedDesignCapacity() const;
      bool setHighSpeedUserSpecifiedDesignCapacity(boost::optional<double> highSpeedUserSpecifiedDesignCapacity);
      void resetHighSpeedUserSpecifiedDesignCapacity();

      boost::optional<double> lowSpeedUserSpecifiedDesignCapacity() const;
      bool isLowSpeedUserSpecifiedDesignCapacityAutosized() const;
      bool setLowSpeedUserSpecifiedDesignCapacity(boost::optional<double> lowSpeedUserSpecifiedDesignCapacity);
      void resetLowSpeedUserSpecifiedDesignCapacity();
      void autosizeLowSpeedUserSpecifiedDesignCapacity();

      double lowSpeedUserSpecifiedDesignCapacitySizingFactor() const;
      bool setLowSpeedUserSpecifiedDesignCapacitySizingFactor(double lowSpeedUserSpecifiedDesignCapacitySizingFactor);

      boost::optional<double> designEnteringWaterTemperature() const;
      bool isDesignEnteringWaterTemperatureAutosized() const;
      bool setDesignEnteringWaterTemperature(boost::optional<double> designEnteringWaterTemperature);
      void autosizeDesignEnteringWaterTemperature();

      double designEnteringAirTemperature() const;
      bool setDesignEnteringAirTemperature(boost::optional<double> designEnteringAirTemperature);

      double designEnteringAirWetbulbTemperature() const;
      bool setDesignEnteringAirWetbulbTemperature(boost::optional<double> designEnteringAirWetbulbTemperature);

      double highSpeedSizingFactor() const;
      bool setHighSpeedSizingFactor(double highSpeedSizingFactor);

      std::string evaporationLossMode() const;
      bool setEvaporationLossMode(const std::string& evaporationLossMode);

      boost::optional<double> evaporationLossFactor() const;
      bool setEvaporationLossFactor(boost::optional<double> evaporationLossFactor);
      void resetEvaporationLossFactor();

      double driftLossPercent() const;
      bool setDriftLossPercent(double driftLossPercent);

      std::string blowdownCalculationMode() const;
      bool setBlowdownCalculationMode(const std::string& blowdownCalculationMode);

      double blowdownConcentrationRatio() const;
      bool setBlowdownConcentrationRatio(double blowdownConcentrationRatio);

      boost::optional<double> autosizedHighFanSpeedAirFlowRate() const;
      boost::optional<double> autosizedHighFanSpeedFanPower() const;
      boost::optional<double> autosizedLowFanSpeedAirFlowRate() const;
      boost::optional<double> autosizedLowFanSpeedFanPower() const;
      boost::optional<double> autosizedLowSpeedStandardDesignCapacity() const;
      boost::optional<double> autosizedHighFanSpeedUfactorTimesAreaValue() const;
      boost::optional<double> autosizedLowFanSpeedUfactorTimesAreaValue() const;
      boost::optional<double> autosizedDesignWaterFlowRate() const;
      boost::optional<double> autosizedLowSpeedUserSpecifiedDesignCapacity() const;
      boost::optional<double> autosizedDesignEnteringWaterTemperature() const;
    };

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
