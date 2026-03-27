/***********************************************************************************************************************
 *  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
 *  See also https://openstudio.net/license
 ***********************************************************************************************************************/

#ifndef EPMODEL_ZONEHVACFOURPIPEFANCOIL_IMPL_HPP
#define EPMODEL_ZONEHVACFOURPIPEFANCOIL_IMPL_HPP

#include "ZoneHVACComponent_Impl.hpp"

#include <boost/optional.hpp>
#include <string>
#include <vector>

namespace openstudio {
namespace epmodel {

  namespace detail {

    class EPMODEL_API ZoneHVACFourPipeFanCoil_Impl : public ZoneHVACComponent_Impl
    {
     public:
      using ZoneHVACComponent_Impl::ZoneHVACComponent_Impl;
      virtual ~ZoneHVACFourPipeFanCoil_Impl() override = default;

      std::string capacityControlMethod() const;
      bool setCapacityControlMethod(const std::string& capacityControlMethod);
      std::vector<std::string> capacityControlMethodValues() const;

      boost::optional<double> maximumSupplyAirFlowRate() const;
      bool isMaximumSupplyAirFlowRateAutosized() const;
      bool setMaximumSupplyAirFlowRate(double maximumSupplyAirFlowRate);
      void autosizeMaximumSupplyAirFlowRate();

      double lowSpeedSupplyAirFlowRatio() const;
      bool isLowSpeedSupplyAirFlowRatioDefaulted() const;
      bool setLowSpeedSupplyAirFlowRatio(double lowSpeedSupplyAirFlowRatio);
      void resetLowSpeedSupplyAirFlowRatio();

      double mediumSpeedSupplyAirFlowRatio() const;
      bool isMediumSpeedSupplyAirFlowRatioDefaulted() const;
      bool setMediumSpeedSupplyAirFlowRatio(double mediumSpeedSupplyAirFlowRatio);
      void resetMediumSpeedSupplyAirFlowRatio();

      boost::optional<double> maximumOutdoorAirFlowRate() const;
      bool isMaximumOutdoorAirFlowRateAutosized() const;
      bool setMaximumOutdoorAirFlowRate(double maximumOutdoorAirFlowRate);
      void autosizeMaximumOutdoorAirFlowRate();

      std::string outdoorAirMixerObjectType() const;
      bool setOutdoorAirMixerObjectType(const std::string& outdoorAirMixerObjectType);
      std::vector<std::string> outdoorAirMixerObjectTypeValues() const;

      boost::optional<double> maximumColdWaterFlowRate() const;
      bool isMaximumColdWaterFlowRateAutosized() const;
      bool setMaximumColdWaterFlowRate(double maximumColdWaterFlowRate);
      void autosizeMaximumColdWaterFlowRate();

      double minimumColdWaterFlowRate() const;
      bool isMinimumColdWaterFlowRateDefaulted() const;
      bool setMinimumColdWaterFlowRate(double minimumColdWaterFlowRate);
      void resetMinimumColdWaterFlowRate();

      double coolingConvergenceTolerance() const;
      bool isCoolingConvergenceToleranceDefaulted() const;
      bool setCoolingConvergenceTolerance(double coolingConvergenceTolerance);
      void resetCoolingConvergenceTolerance();

      boost::optional<double> maximumHotWaterFlowRate() const;
      bool isMaximumHotWaterFlowRateAutosized() const;
      bool setMaximumHotWaterFlowRate(double maximumHotWaterFlowRate);
      void autosizeMaximumHotWaterFlowRate();

      double minimumHotWaterFlowRate() const;
      bool isMinimumHotWaterFlowRateDefaulted() const;
      bool setMinimumHotWaterFlowRate(double minimumHotWaterFlowRate);
      void resetMinimumHotWaterFlowRate();

      double heatingConvergenceTolerance() const;
      bool isHeatingConvergenceToleranceDefaulted() const;
      bool setHeatingConvergenceTolerance(double heatingConvergenceTolerance);
      void resetHeatingConvergenceTolerance();

      bool isMinimumSupplyAirTemperatureInCoolingModeAutosized() const;
      boost::optional<double> minimumSupplyAirTemperatureInCoolingMode() const;
      bool setMinimumSupplyAirTemperatureInCoolingMode(double minimumSupplyAirTemperatureInCoolingMode);
      void autosizeMinimumSupplyAirTemperatureInCoolingMode();

      bool isMaximumSupplyAirTemperatureInHeatingModeAutosized() const;
      boost::optional<double> maximumSupplyAirTemperatureInHeatingMode() const;
      bool setMaximumSupplyAirTemperatureInHeatingMode(double maximumSupplyAirTemperatureInHeatingMode);
      void autosizeMaximumSupplyAirTemperatureInHeatingMode();
    };

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif  // EPMODEL_ZONEHVACFOURPIPEFANCOIL_IMPL_HPP
