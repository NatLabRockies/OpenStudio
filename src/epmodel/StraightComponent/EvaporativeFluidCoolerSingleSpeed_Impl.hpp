/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_EVAPORATIVEFLUIDCOOLERSINGLESPEED_IMPL_HPP
#define EPMODEL_EVAPORATIVEFLUIDCOOLERSINGLESPEED_IMPL_HPP

#include "StraightComponent/StraightComponent_Impl.hpp"

#include <boost/optional.hpp>

#include <string>
#include <vector>

namespace openstudio {
namespace epmodel {
  namespace detail {

    class EPMODEL_API EvaporativeFluidCoolerSingleSpeed_Impl : public StraightComponent_Impl
    {
     public:
      using StraightComponent_Impl::StraightComponent_Impl;
      virtual ~EvaporativeFluidCoolerSingleSpeed_Impl() override = default;

      unsigned inletPort() const override;
      unsigned outletPort() const override;
      bool addToNode(Node& node) override;

      std::vector<std::string> performanceInputMethodValues() const;
      std::vector<std::string> capacityControlValues() const;
      std::vector<std::string> evaporationLossModeValues() const;
      std::vector<std::string> blowdownCalculationModeValues() const;

      boost::optional<double> designAirFlowRate() const;
      bool isDesignAirFlowRateAutosized() const;
      bool setDesignAirFlowRate(boost::optional<double> designAirFlowRate);
      void autosizeDesignAirFlowRate();
      boost::optional<double> autosizedDesignAirFlowRate() const;

      boost::optional<double> fanPoweratDesignAirFlowRate() const;
      bool isFanPoweratDesignAirFlowRateAutosized() const;
      bool setFanPoweratDesignAirFlowRate(boost::optional<double> fanPoweratDesignAirFlowRate);
      void autosizeFanPoweratDesignAirFlowRate();
      boost::optional<double> autosizedFanPoweratDesignAirFlowRate() const;

      double designSprayWaterFlowRate() const;
      bool setDesignSprayWaterFlowRate(double designSprayWaterFlowRate);

      std::string performanceInputMethod() const;
      bool setPerformanceInputMethod(const std::string& performanceInputMethod);

      double heatRejectionCapacityandNominalCapacitySizingRatio() const;
      bool setHeatRejectionCapacityandNominalCapacitySizingRatio(double heatRejectionCapacityandNominalCapacitySizingRatio);

      boost::optional<double> standardDesignCapacity() const;
      bool setStandardDesignCapacity(boost::optional<double> standardDesignCapacity);
      void resetStandardDesignCapacity();

      boost::optional<double> ufactorTimesAreaValueatDesignAirFlowRate() const;
      bool isUfactorTimesAreaValueatDesignAirFlowRateAutosized() const;
      bool setUfactorTimesAreaValueatDesignAirFlowRate(boost::optional<double> ufactorTimesAreaValueatDesignAirFlowRate);
      void resetUfactorTimesAreaValueatDesignAirFlowRate();
      void autosizeUfactorTimesAreaValueatDesignAirFlowRate();
      boost::optional<double> autosizedUfactorTimesAreaValueatDesignAirFlowRate() const;

      boost::optional<double> designWaterFlowRate() const;
      bool isDesignWaterFlowRateAutosized() const;
      bool setDesignWaterFlowRate(boost::optional<double> designWaterFlowRate);
      void resetDesignWaterFlowRate();
      void autosizeDesignWaterFlowRate();
      boost::optional<double> autosizedDesignWaterFlowRate() const;

      boost::optional<double> userSpecifiedDesignCapacity() const;
      bool setUserSpecifiedDesignCapacity(boost::optional<double> userSpecifiedDesignCapacity);
      void resetUserSpecifiedDesignCapacity();

      boost::optional<double> designEnteringWaterTemperature() const;
      bool isDesignEnteringWaterTemperatureAutosized() const;
      bool setDesignEnteringWaterTemperature(boost::optional<double> designEnteringWaterTemperature);
      void autosizeDesignEnteringWaterTemperature();
      boost::optional<double> autosizedDesignEnteringWaterTemperature() const;

      double designEnteringAirTemperature() const;
      bool setDesignEnteringAirTemperature(boost::optional<double> designEnteringAirTemperature);

      double designEnteringAirWetbulbTemperature() const;
      bool setDesignEnteringAirWetbulbTemperature(boost::optional<double> designEnteringAirWetbulbTemperature);

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
      bool setEvaporationLossFactor(boost::optional<double> evaporationLossFactor);
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
    };

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
