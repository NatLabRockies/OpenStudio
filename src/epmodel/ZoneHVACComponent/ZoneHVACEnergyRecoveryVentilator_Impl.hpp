/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_ZONEHVACENERGYRECOVERYVENTILATOR_IMPL_HPP
#define EPMODEL_ZONEHVACENERGYRECOVERYVENTILATOR_IMPL_HPP

#include "ZoneHVACComponent_Impl.hpp"

#include <vector>

namespace openstudio {
namespace epmodel {

  class HVACComponent;
  class Node;
  class Schedule;
  class ThermalZone;
  class ZoneHVACEnergyRecoveryVentilatorController;
  namespace detail {

    struct LoadContext;

    class EPMODEL_API ZoneHVACEnergyRecoveryVentilator_Impl : public ZoneHVACComponent_Impl
    {
     public:
      using ZoneHVACComponent_Impl::ZoneHVACComponent_Impl;
      virtual ~ZoneHVACEnergyRecoveryVentilator_Impl() override = default;

      Schedule availabilitySchedule() const;
      bool setAvailabilitySchedule(Schedule& schedule);

      HVACComponent heatExchanger() const;
      bool setHeatExchanger(const HVACComponent& heatExchanger);

      boost::optional<double> supplyAirFlowRate() const;
      bool setSupplyAirFlowRate(double supplyAirFlowRate);
      bool isSupplyAirFlowRateAutosized() const;
      void autosizeSupplyAirFlowRate();

      boost::optional<double> exhaustAirFlowRate() const;
      bool setExhaustAirFlowRate(double exhaustAirFlowRate);
      bool isExhaustAirFlowRateAutosized() const;
      void autosizeExhaustAirFlowRate();

      HVACComponent supplyAirFan() const;
      bool setSupplyAirFan(const HVACComponent& supplyAirFan);

      HVACComponent exhaustAirFan() const;
      bool setExhaustAirFan(const HVACComponent& exhaustAirFan);

      boost::optional<ZoneHVACEnergyRecoveryVentilatorController> controller() const;
      bool setController(const ZoneHVACEnergyRecoveryVentilatorController& controller);
      void resetController();

      double ventilationRateperUnitFloorArea() const;
      bool setVentilationRateperUnitFloorArea(double ventilationRateperUnitFloorArea);

      double ventilationRateperOccupant() const;
      bool setVentilationRateperOccupant(double ventilationRateperOccupant);

      boost::optional<Node> outdoorAirNode() const;
      boost::optional<Node> supplyAirFanInletNode() const;
      boost::optional<Node> exhaustAirFanInletNode() const;
      boost::optional<Node> reliefAirNode() const;

      std::vector<ModelObject> children() const override;

      boost::optional<Node> inletNode() const override;
      boost::optional<Node> outletNode() const override;
      bool addToThermalZone(ThermalZone& thermalZone) override;
      void removeFromThermalZone() override;
      void doCanonicalize(LoadContext& context) override;

      unsigned inletPort() const override;
      unsigned outletPort() const override;

     private:
      bool maintainContainedAirPath();
      bool repairContainedAirPath(LoadContext& context);
      bool reconcileContainedAirPath(bool allowChildNodeRecovery, LoadContext* context = nullptr);
    };

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
