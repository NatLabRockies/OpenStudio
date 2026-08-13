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

  class Node;
  class Schedule;
  class ThermalZone;

  namespace detail {

    struct LoadContext;

    class EPMODEL_API ZoneHVACFourPipeFanCoil_Impl : public ZoneHVACComponent_Impl
    {
     public:
      using ZoneHVACComponent_Impl::ZoneHVACComponent_Impl;
      virtual ~ZoneHVACFourPipeFanCoil_Impl() override = default;

      std::vector<ModelObject> children() const override;
      std::vector<IdfObject> remove() override;
      unsigned inletPort() const override;
      unsigned outletPort() const override;
      bool addToNode(Node& node) override;
      bool addToThermalZone(ThermalZone& thermalZone) override;
      void removeFromThermalZone() override;
      void doCanonicalize(LoadContext& context) override;

      Schedule availabilitySchedule() const;
      bool setAvailabilitySchedule(Schedule& schedule);

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

      boost::optional<Schedule> outdoorAirSchedule() const;
      bool setOutdoorAirSchedule(Schedule& schedule);
      void resetOutdoorAirSchedule();

      HVACComponent supplyAirFan() const;
      HVACComponent coolingCoil() const;
      HVACComponent heatingCoil() const;
      boost::optional<Node> fanOutletNode() const;
      boost::optional<Node> coolingCoilOutletNode() const;

      bool setSupplyAirFan(const HVACComponent& fan);
      bool setCoolingCoil(const HVACComponent& coolingCoil);
      bool setHeatingCoil(const HVACComponent& heatingCoil);

      boost::optional<Schedule> supplyAirFanOperatingModeSchedule() const;
      bool setSupplyAirFanOperatingModeSchedule(Schedule& schedule);
      void resetSupplyAirFanOperatingModeSchedule();

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

     private:
      bool maintainContainedAirPath();
      bool repairContainedAirPath(LoadContext& context);
      bool reconcileContainedAirPath(bool allowChildNodeRecovery, LoadContext* context = nullptr);
    };

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif  // EPMODEL_ZONEHVACFOURPIPEFANCOIL_IMPL_HPP
