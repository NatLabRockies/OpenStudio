/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_ZONEHVACEVAPORATIVECOOLERUNIT_IMPL_HPP
#define EPMODEL_ZONEHVACEVAPORATIVECOOLERUNIT_IMPL_HPP

#include "ZoneHVACComponent_Impl.hpp"

#include <boost/optional.hpp>

#include <string>

namespace openstudio {
namespace epmodel {

  class HVACComponent;
  class Node;
  class Schedule;

  namespace detail {

    struct LoadContext;

    class EPMODEL_API ZoneHVACEvaporativeCoolerUnit_Impl : public ZoneHVACComponent_Impl
    {
     public:
      using ZoneHVACComponent_Impl::ZoneHVACComponent_Impl;
      virtual ~ZoneHVACEvaporativeCoolerUnit_Impl() override = default;

      unsigned inletPort() const override;
      unsigned outletPort() const override;
      std::vector<ModelObject> children() const override;
      bool addToThermalZone(ThermalZone& thermalZone) override;
      void removeFromThermalZone() override;
      void doCanonicalize(LoadContext& context) override;

      Schedule availabilitySchedule() const;
      bool setAvailabilitySchedule(Schedule& schedule);

      HVACComponent supplyAirFan() const;
      bool setSupplyAirFan(const HVACComponent& supplyAirFan);

      boost::optional<double> designSupplyAirFlowRate() const;
      bool isDesignSupplyAirFlowRateAutosized() const;
      bool setDesignSupplyAirFlowRate(double designSupplyAirFlowRate);
      void autosizeDesignSupplyAirFlowRate();

      std::string fanPlacement() const;
      bool setFanPlacement(const std::string& fanPlacement);

      std::string coolerUnitControlMethod() const;
      bool setCoolerUnitControlMethod(const std::string& coolerUnitControlMethod);

      double throttlingRangeTemperatureDifference() const;
      bool setThrottlingRangeTemperatureDifference(double throttlingRangeTemperatureDifference);

      double coolingLoadControlThresholdHeatTransferRate() const;
      bool setCoolingLoadControlThresholdHeatTransferRate(double coolingLoadControlThresholdHeatTransferRate);

      HVACComponent firstEvaporativeCooler() const;
      bool setFirstEvaporativeCooler(const HVACComponent& firstEvaporativeCooler);

      boost::optional<HVACComponent> secondEvaporativeCooler() const;
      bool setSecondEvaporativeCooler(const HVACComponent& secondEvaporativeCooler);
      void resetSecondEvaporativeCooler();

      double shutOffRelativeHumidity() const;
      bool setShutOffRelativeHumidity(double shutOffRelativeHumidity);

      boost::optional<Node> outdoorAirNode() const;
      boost::optional<Node> fanOutletNode() const;
      boost::optional<Node> firstEvaporativeCoolerOutletNode() const;
      boost::optional<Node> secondEvaporativeCoolerOutletNode() const;

     private:
      bool maintainContainedAirPath();
      bool repairContainedAirPath(LoadContext& context);
      bool reconcileContainedAirPath(bool allowChildNodeRecovery, LoadContext* context = nullptr);
    };

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
