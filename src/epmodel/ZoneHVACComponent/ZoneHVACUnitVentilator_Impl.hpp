/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_ZONEHVACUNITVENTILATOR_IMPL_HPP
#define EPMODEL_ZONEHVACUNITVENTILATOR_IMPL_HPP

#include "ZoneHVACComponent_Impl.hpp"

#include <boost/optional.hpp>
#include <string>

namespace openstudio {
namespace epmodel {

  class ModelObject;
  class Node;
  class Schedule;
  class HVACComponent;
  class ThermalZone;

  namespace detail {

    struct LoadContext;

    class EPMODEL_API ZoneHVACUnitVentilator_Impl : public ZoneHVACComponent_Impl
    {
     public:
      using ZoneHVACComponent_Impl::ZoneHVACComponent_Impl;
      virtual ~ZoneHVACUnitVentilator_Impl() override = default;

      std::vector<ModelObject> children() const override;
      unsigned inletPort() const override;
      unsigned outletPort() const override;
      bool addToThermalZone(ThermalZone& thermalZone) override;
      void removeFromThermalZone() override;
      void doCanonicalize(LoadContext& context) override;

      boost::optional<double> maximumSupplyAirFlowRate() const;
      bool isMaximumSupplyAirFlowRateAutosized() const;
      bool setMaximumSupplyAirFlowRate(double maximumSupplyAirFlowRate);
      void autosizeMaximumSupplyAirFlowRate();
      boost::optional<double> autosizedMaximumSupplyAirFlowRate() const;

      Schedule availabilitySchedule() const;
      bool setAvailabilitySchedule(Schedule& schedule);

      Schedule minimumOutdoorAirSchedule() const;
      bool setMinimumOutdoorAirSchedule(Schedule& schedule);

      Schedule maximumOutdoorAirFractionorTemperatureSchedule() const;
      bool setMaximumOutdoorAirFractionorTemperatureSchedule(Schedule& schedule);

      HVACComponent supplyAirFan() const;
      bool setSupplyAirFan(const HVACComponent& supplyAirFan);

      boost::optional<Schedule> supplyAirFanOperatingModeSchedule() const;
      bool setSupplyAirFanOperatingModeSchedule(Schedule& schedule);
      void resetSupplyAirFanOperatingModeSchedule();

      boost::optional<HVACComponent> heatingCoil() const;
      bool setHeatingCoil(const HVACComponent& heatingCoil);
      void resetHeatingCoil();

      boost::optional<HVACComponent> coolingCoil() const;
      bool setCoolingCoil(const HVACComponent& coolingCoil);
      void resetCoolingCoil();
      boost::optional<Node> mixedAirNode() const;
      boost::optional<Node> outdoorAirNode() const;
      boost::optional<Node> exhaustAirNode() const;
      boost::optional<Node> fanOutletNode() const;
      boost::optional<Node> coolingCoilOutletNode() const;

      std::string outdoorAirControlType() const;
      bool setOutdoorAirControlType(const std::string& outdoorAirControlType);

      boost::optional<double> minimumOutdoorAirFlowRate() const;
      bool isMinimumOutdoorAirFlowRateAutosized() const;
      bool setMinimumOutdoorAirFlowRate(double minimumOutdoorAirFlowRate);
      void autosizeMinimumOutdoorAirFlowRate();
      boost::optional<double> autosizedMinimumOutdoorAirFlowRate() const;

      boost::optional<double> maximumOutdoorAirFlowRate() const;
      bool isMaximumOutdoorAirFlowRateAutosized() const;
      bool setMaximumOutdoorAirFlowRate(double maximumOutdoorAirFlowRate);
      void autosizeMaximumOutdoorAirFlowRate();
      boost::optional<double> autosizedMaximumOutdoorAirFlowRate() const;
      double heatingConvergenceTolerance() const;
      bool setHeatingConvergenceTolerance(double heatingConvergenceTolerance);

      double coolingConvergenceTolerance() const;
      bool setCoolingConvergenceTolerance(double coolingConvergenceTolerance);

     private:
      bool maintainContainedAirPath();
      bool repairContainedAirPath(LoadContext& context);
      bool reconcileContainedAirPath(bool allowChildNodeRecovery, LoadContext* context = nullptr);
    };

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif  // EPMODEL_ZONEHVACUNITVENTILATOR_IMPL_HPP
