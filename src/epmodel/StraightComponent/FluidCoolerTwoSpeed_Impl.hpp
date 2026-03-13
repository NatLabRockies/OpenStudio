/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_FLUIDCOOLERTWOSPEED_IMPL_HPP
#define EPMODEL_FLUIDCOOLERTWOSPEED_IMPL_HPP

#include "StraightComponent/StraightComponent_Impl.hpp"

#include <boost/optional.hpp>

#include <string>
#include <vector>

namespace openstudio {
namespace epmodel {
  namespace detail {

    class EPMODEL_API FluidCoolerTwoSpeed_Impl : public StraightComponent_Impl
    {
     public:
      using StraightComponent_Impl::StraightComponent_Impl;
      virtual ~FluidCoolerTwoSpeed_Impl() override = default;

      unsigned inletPort() const override;
      unsigned outletPort() const override;

      std::vector<std::string> performanceInputMethodValues() const;

      std::string performanceInputMethod() const;
      bool setPerformanceInputMethod(const std::string& performanceInputMethod);

      boost::optional<double> highFanSpeedUfactorTimesAreaValue() const;
      bool isHighFanSpeedUfactorTimesAreaValueAutosized() const;
      bool setHighFanSpeedUfactorTimesAreaValue(boost::optional<double> highFanSpeedUfactorTimesAreaValue);
      void autosizeHighFanSpeedUfactorTimesAreaValue();
      boost::optional<double> autosizedHighFanSpeedUfactorTimesAreaValue() const;

      boost::optional<double> lowFanSpeedUfactorTimesAreaValue() const;
      bool isLowFanSpeedUfactorTimesAreaValueAutosized() const;
      bool setLowFanSpeedUfactorTimesAreaValue(boost::optional<double> lowFanSpeedUfactorTimesAreaValue);
      void autosizeLowFanSpeedUfactorTimesAreaValue();
      boost::optional<double> autosizedLowFanSpeedUfactorTimesAreaValue() const;

      double lowFanSpeedUFactorTimesAreaSizingFactor() const;
      bool setLowFanSpeedUFactorTimesAreaSizingFactor(double lowFanSpeedUFactorTimesAreaSizingFactor);

      double highSpeedNominalCapacity() const;
      bool setHighSpeedNominalCapacity(double highSpeedNominalCapacity);

      boost::optional<double> lowSpeedNominalCapacity() const;
      bool isLowSpeedNominalCapacityAutosized() const;
      bool setLowSpeedNominalCapacity(boost::optional<double> lowSpeedNominalCapacity);
      void autosizeLowSpeedNominalCapacity();
      boost::optional<double> autosizedLowSpeedNominalCapacity() const;

      double lowSpeedNominalCapacitySizingFactor() const;
      bool setLowSpeedNominalCapacitySizingFactor(double lowSpeedNominalCapacitySizingFactor);

      double designEnteringWaterTemperature() const;
      bool setDesignEnteringWaterTemperature(double designEnteringWaterTemperature);

      double designEnteringAirTemperature() const;
      bool setDesignEnteringAirTemperature(double designEnteringAirTemperature);

      double designEnteringAirWetbulbTemperature() const;
      bool setDesignEnteringAirWetbulbTemperature(double designEnteringAirWetbulbTemperature);

      boost::optional<double> designWaterFlowRate() const;
      bool isDesignWaterFlowRateAutosized() const;
      bool setDesignWaterFlowRate(boost::optional<double> designWaterFlowRate);
      void autosizeDesignWaterFlowRate();
      boost::optional<double> autosizedDesignWaterFlowRate() const;

      boost::optional<double> highFanSpeedAirFlowRate() const;
      bool isHighFanSpeedAirFlowRateAutosized() const;
      bool setHighFanSpeedAirFlowRate(boost::optional<double> highFanSpeedAirFlowRate);
      void autosizeHighFanSpeedAirFlowRate();
      boost::optional<double> autosizedHighFanSpeedAirFlowRate() const;

      boost::optional<double> highFanSpeedFanPower() const;
      bool isHighFanSpeedFanPowerAutosized() const;
      bool setHighFanSpeedFanPower(boost::optional<double> highFanSpeedFanPower);
      void autosizeHighFanSpeedFanPower();
      boost::optional<double> autosizedHighFanSpeedFanPower() const;

      boost::optional<double> lowFanSpeedAirFlowRate() const;
      bool isLowFanSpeedAirFlowRateAutosized() const;
      bool setLowFanSpeedAirFlowRate(boost::optional<double> lowFanSpeedAirFlowRate);
      void autosizeLowFanSpeedAirFlowRate();
      boost::optional<double> autosizedLowFanSpeedAirFlowRate() const;

      double lowFanSpeedAirFlowRateSizingFactor() const;
      bool setLowFanSpeedAirFlowRateSizingFactor(double lowFanSpeedAirFlowRateSizingFactor);

      boost::optional<double> lowFanSpeedFanPower() const;
      bool isLowFanSpeedFanPowerAutosized() const;
      bool setLowFanSpeedFanPower(boost::optional<double> lowFanSpeedFanPower);
      void autosizeLowFanSpeedFanPower();
      boost::optional<double> autosizedLowFanSpeedFanPower() const;

      double lowFanSpeedFanPowerSizingFactor() const;
      bool setLowFanSpeedFanPowerSizingFactor(double lowFanSpeedFanPowerSizingFactor);
    };

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
