/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_COILCOOLINGWATER_IMPL_HPP
#define EPMODEL_COILCOOLINGWATER_IMPL_HPP

#include "WaterToAirComponent/WaterToAirComponent_Impl.hpp"

#include <vector>

namespace openstudio {
namespace epmodel {

  class Node;
  class Schedule;
  class AirflowNetworkDistributionComponentCoil;

  namespace detail {

    class EPMODEL_API CoilCoolingWater_Impl : public WaterToAirComponent_Impl
    {
     public:
      using WaterToAirComponent_Impl::WaterToAirComponent_Impl;
      virtual ~CoilCoolingWater_Impl() override = default;

      unsigned airInletPort() const override;
      unsigned airOutletPort() const override;
      unsigned waterInletPort() const override;
      unsigned waterOutletPort() const override;
      bool addToNode(Node& node) override;
      std::vector<IdfObject> remove() override;
      bool removeFromPlantLoop();

      std::vector<ModelObject> children() const override;

      Schedule availabilitySchedule() const;
      bool setAvailabilitySchedule(Schedule& schedule);

      // Design water flow rate
      boost::optional<double> designWaterFlowRate() const;
      boost::optional<double> autosizedDesignWaterFlowRate() const;
      bool setDesignWaterFlowRate(double value);
      bool isDesignWaterFlowRateAutosized() const;
      void autosizeDesignWaterFlowRate();

      // Design air flow rate
      boost::optional<double> designAirFlowRate() const;
      boost::optional<double> autosizedDesignAirFlowRate() const;
      bool setDesignAirFlowRate(double value);
      bool isDesignAirFlowRateAutosized() const;
      void autosizeDesignAirFlowRate();

      // Design inlet water temperature
      boost::optional<double> designInletWaterTemperature() const;
      boost::optional<double> autosizedDesignInletWaterTemperature() const;
      bool setDesignInletWaterTemperature(double value);
      bool isDesignInletWaterTemperatureAutosized() const;
      void autosizeDesignInletWaterTemperature();

      // Design inlet air temperature
      boost::optional<double> designInletAirTemperature() const;
      boost::optional<double> autosizedDesignInletAirTemperature() const;
      bool setDesignInletAirTemperature(double value);
      bool isDesignInletAirTemperatureAutosized() const;
      void autosizeDesignInletAirTemperature();

      // Design outlet air temperature
      boost::optional<double> designOutletAirTemperature() const;
      boost::optional<double> autosizedDesignOutletAirTemperature() const;
      bool setDesignOutletAirTemperature(double value);
      bool isDesignOutletAirTemperatureAutosized() const;
      void autosizeDesignOutletAirTemperature();

      // Design inlet air humidity ratio
      boost::optional<double> designInletAirHumidityRatio() const;
      boost::optional<double> autosizedDesignInletAirHumidityRatio() const;
      bool setDesignInletAirHumidityRatio(double value);
      bool isDesignInletAirHumidityRatioAutosized() const;
      void autosizeDesignInletAirHumidityRatio();

      // Design outlet air humidity ratio
      boost::optional<double> designOutletAirHumidityRatio() const;
      boost::optional<double> autosizedDesignOutletAirHumidityRatio() const;
      bool setDesignOutletAirHumidityRatio(double value);
      bool isDesignOutletAirHumidityRatioAutosized() const;
      void autosizeDesignOutletAirHumidityRatio();

      std::string typeOfAnalysis() const;
      bool setTypeOfAnalysis(const std::string& value);

      std::string heatExchangerConfiguration() const;
      bool setHeatExchangerConfiguration(const std::string& value);

      std::vector<std::string> typeOfAnalysisValues() const;
      std::vector<std::string> heatExchangerConfigurationValues() const;

      AirflowNetworkDistributionComponentCoil getAirflowNetworkEquivalentDuct(double length, double diameter);
      boost::optional<AirflowNetworkDistributionComponentCoil> airflowNetworkEquivalentDuct() const;

      boost::optional<double> autosizedDesignCoilLoad() const;
    };

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
