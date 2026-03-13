/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_COILCOOLINGWATER_IMPL_HPP
#define EPMODEL_COILCOOLINGWATER_IMPL_HPP

#include "ModelObject_Impl.hpp"

#include <vector>

namespace openstudio {
namespace epmodel {

  namespace detail {

    class EPMODEL_API CoilCoolingWater_Impl : public ModelObject_Impl
    {
     public:
      using ModelObject_Impl::ModelObject_Impl;
      virtual ~CoilCoolingWater_Impl() override = default;

      // Design water flow rate
      boost::optional<double> designWaterFlowRate() const;
      bool setDesignWaterFlowRate(double value);
      bool isDesignWaterFlowRateAutosized() const;
      void autosizeDesignWaterFlowRate();

      // Design air flow rate
      boost::optional<double> designAirFlowRate() const;
      bool setDesignAirFlowRate(double value);
      bool isDesignAirFlowRateAutosized() const;
      void autosizeDesignAirFlowRate();

      // Design inlet water temperature
      boost::optional<double> designInletWaterTemperature() const;
      bool setDesignInletWaterTemperature(double value);
      bool isDesignInletWaterTemperatureAutosized() const;
      void autosizeDesignInletWaterTemperature();

      // Design inlet air temperature
      boost::optional<double> designInletAirTemperature() const;
      bool setDesignInletAirTemperature(double value);
      bool isDesignInletAirTemperatureAutosized() const;
      void autosizeDesignInletAirTemperature();

      // Design outlet air temperature
      boost::optional<double> designOutletAirTemperature() const;
      bool setDesignOutletAirTemperature(double value);
      bool isDesignOutletAirTemperatureAutosized() const;
      void autosizeDesignOutletAirTemperature();

      // Design inlet air humidity ratio
      boost::optional<double> designInletAirHumidityRatio() const;
      bool setDesignInletAirHumidityRatio(double value);
      bool isDesignInletAirHumidityRatioAutosized() const;
      void autosizeDesignInletAirHumidityRatio();

      // Design outlet air humidity ratio
      boost::optional<double> designOutletAirHumidityRatio() const;
      bool setDesignOutletAirHumidityRatio(double value);
      bool isDesignOutletAirHumidityRatioAutosized() const;
      void autosizeDesignOutletAirHumidityRatio();

      std::string typeOfAnalysis() const;
      bool setTypeOfAnalysis(const std::string& value);

      std::string heatExchangerConfiguration() const;
      bool setHeatExchangerConfiguration(const std::string& value);

      std::vector<std::string> typeOfAnalysisValues() const;
      std::vector<std::string> heatExchangerConfigurationValues() const;
    };

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
