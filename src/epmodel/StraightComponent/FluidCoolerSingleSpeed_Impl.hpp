/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_FLUIDCOOLERSINGLESPEED_IMPL_HPP
#define EPMODEL_FLUIDCOOLERSINGLESPEED_IMPL_HPP

#include "StraightComponent/StraightComponent_Impl.hpp"

#include <boost/optional.hpp>

#include <string>
#include <vector>

namespace openstudio {
namespace epmodel {
  namespace detail {

    class EPMODEL_API FluidCoolerSingleSpeed_Impl : public StraightComponent_Impl
    {
     public:
      using StraightComponent_Impl::StraightComponent_Impl;
      virtual ~FluidCoolerSingleSpeed_Impl() override = default;

      unsigned inletPort() const override;
      unsigned outletPort() const override;

      std::vector<std::string> performanceInputMethodValues() const;
      std::string performanceInputMethod() const;
      bool setPerformanceInputMethod(const std::string& performanceInputMethod);

      boost::optional<double> designAirFlowRateUfactorTimesAreaValue() const;
      bool isDesignAirFlowRateUfactorTimesAreaValueAutosized() const;
      bool setDesignAirFlowRateUfactorTimesAreaValue(boost::optional<double> designAirFlowRateUfactorTimesAreaValue);
      void autosizeDesignAirFlowRateUfactorTimesAreaValue();
      boost::optional<double> autosizedDesignAirFlowRateUfactorTimesAreaValue() const;

      double nominalCapacity() const;
      bool setNominalCapacity(double nominalCapacity);

      double designEnteringWaterTemperature() const;
      bool setDesignEnteringWaterTemperature(boost::optional<double> designEnteringWaterTemperature);

      double designEnteringAirTemperature() const;
      bool setDesignEnteringAirTemperature(boost::optional<double> designEnteringAirTemperature);

      double designEnteringAirWetbulbTemperature() const;
      bool setDesignEnteringAirWetbulbTemperature(boost::optional<double> designEnteringAirWetbulbTemperature);

      boost::optional<double> designWaterFlowRate() const;
      bool isDesignWaterFlowRateAutosized() const;
      bool setDesignWaterFlowRate(boost::optional<double> designWaterFlowRate);
      void autosizeDesignWaterFlowRate();
      boost::optional<double> autosizedDesignWaterFlowRate() const;

      boost::optional<double> designAirFlowRate() const;
      bool isDesignAirFlowRateAutosized() const;
      bool setDesignAirFlowRate(boost::optional<double> designAirFlowRate);
      void autosizeDesignAirFlowRate();
      boost::optional<double> autosizedDesignAirFlowRate() const;

      boost::optional<double> designAirFlowRateFanPower() const;
      bool isDesignAirFlowRateFanPowerAutosized() const;
      bool setDesignAirFlowRateFanPower(boost::optional<double> designAirFlowRateFanPower);
      void autosizeDesignAirFlowRateFanPower();
      boost::optional<double> autosizedDesignAirFlowRateFanPower() const;
    };

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
