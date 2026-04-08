/***********************************************************************************************************************  
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.  
*  See also https://openstudio.net/license  
***********************************************************************************************************************/

#ifndef EPMODEL_ZONEHVACPACKAGEDTERMINALAIRCONDITIONER_IMPL_HPP
#define EPMODEL_ZONEHVACPACKAGEDTERMINALAIRCONDITIONER_IMPL_HPP

#include "ZoneHVACComponent_Impl.hpp"

#include <utilities/idd/ZoneHVAC_PackagedTerminalAirConditioner_FieldEnums.hxx>

#include <boost/optional.hpp>
#include <vector>

namespace openstudio {
namespace epmodel {

  class HVACComponent;
  class ModelObject;
  class Node;
  class Schedule;
  class ThermalZone;

  namespace detail {

    struct LoadContext;

    class EPMODEL_API ZoneHVACPackagedTerminalAirConditioner_Impl : public ZoneHVACComponent_Impl
    {
     public:
      using ZoneHVACComponent_Impl::ZoneHVACComponent_Impl;
      virtual ~ZoneHVACPackagedTerminalAirConditioner_Impl() override = default;

      Schedule availabilitySchedule() const;
      bool setAvailabilitySchedule(Schedule& schedule);

      boost::optional<double> supplyAirFlowRateDuringCoolingOperation() const;
      bool setSupplyAirFlowRateDuringCoolingOperation(boost::optional<double> supplyAirFlowRateDuringCoolingOperation);
      bool isSupplyAirFlowRateDuringCoolingOperationAutosized() const;
      void autosizeSupplyAirFlowRateDuringCoolingOperation();
      boost::optional<double> autosizedSupplyAirFlowRateDuringCoolingOperation() const;

      boost::optional<double> supplyAirFlowRateDuringHeatingOperation() const;
      bool setSupplyAirFlowRateDuringHeatingOperation(boost::optional<double> supplyAirFlowRateDuringHeatingOperation);
      bool isSupplyAirFlowRateDuringHeatingOperationAutosized() const;
      void autosizeSupplyAirFlowRateDuringHeatingOperation();
      boost::optional<double> autosizedSupplyAirFlowRateDuringHeatingOperation() const;

      boost::optional<double> supplyAirFlowRateWhenNoCoolingorHeatingisNeeded() const;
      bool setSupplyAirFlowRateWhenNoCoolingorHeatingisNeeded(boost::optional<double> supplyAirFlowRateWhenNoCoolingorHeatingisNeeded);
      void resetSupplyAirFlowRateWhenNoCoolingorHeatingisNeeded();
      bool isSupplyAirFlowRateWhenNoCoolingorHeatingisNeededAutosized() const;
      void autosizeSupplyAirFlowRateWhenNoCoolingorHeatingisNeeded();
      boost::optional<double> autosizedSupplyAirFlowRateWhenNoCoolingorHeatingisNeeded() const;

      bool noLoadSupplyAirFlowRateControlSetToLowSpeed() const;
      bool setNoLoadSupplyAirFlowRateControlSetToLowSpeed(bool noLoadSupplyAirFlowRateControlSetToLowSpeed);

      boost::optional<double> outdoorAirFlowRateDuringCoolingOperation() const;
      bool setOutdoorAirFlowRateDuringCoolingOperation(boost::optional<double> outdoorAirFlowRateDuringCoolingOperation);
      bool isOutdoorAirFlowRateDuringCoolingOperationAutosized() const;
      void autosizeOutdoorAirFlowRateDuringCoolingOperation();
      boost::optional<double> autosizedOutdoorAirFlowRateDuringCoolingOperation() const;

      boost::optional<double> outdoorAirFlowRateDuringHeatingOperation() const;
      bool setOutdoorAirFlowRateDuringHeatingOperation(boost::optional<double> outdoorAirFlowRateDuringHeatingOperation);
      bool isOutdoorAirFlowRateDuringHeatingOperationAutosized() const;
      void autosizeOutdoorAirFlowRateDuringHeatingOperation();
      boost::optional<double> autosizedOutdoorAirFlowRateDuringHeatingOperation() const;

      boost::optional<double> outdoorAirFlowRateWhenNoCoolingorHeatingisNeeded() const;
      bool setOutdoorAirFlowRateWhenNoCoolingorHeatingisNeeded(boost::optional<double> outdoorAirFlowRateWhenNoCoolingorHeatingisNeeded);
      void resetOutdoorAirFlowRateWhenNoCoolingorHeatingisNeeded();
      bool isOutdoorAirFlowRateWhenNoCoolingorHeatingisNeededAutosized() const;
      void autosizeOutdoorAirFlowRateWhenNoCoolingorHeatingisNeeded();
      boost::optional<double> autosizedOutdoorAirFlowRateWhenNoCoolingorHeatingisNeeded() const;

      std::string fanPlacement() const;
      bool isFanPlacementDefaulted() const;
      bool setFanPlacement(const std::string& fanPlacement);
      void resetFanPlacement();

      std::vector<ModelObject> children() const override;
      unsigned inletPort() const override;
      unsigned outletPort() const override;
      bool addToThermalZone(ThermalZone& thermalZone) override;
      void removeFromThermalZone() override;
      void doCanonicalize(LoadContext& context) override;

      HVACComponent supplyAirFan() const;
      bool setSupplyAirFan(const HVACComponent& fan);

      Schedule supplyAirFanOperatingModeSchedule() const;
      bool setSupplyAirFanOperatingModeSchedule(Schedule& schedule);

      HVACComponent heatingCoil() const;
      bool setHeatingCoil(const HVACComponent& heatingCoil);

      HVACComponent coolingCoil() const;
      bool setCoolingCoil(const HVACComponent& coolingCoil);

      boost::optional<Node> fanOutletNode() const;
      boost::optional<Node> coolingCoilOutletNode() const;
      boost::optional<Node> heatingCoilOutletNode() const;

     private:
      bool maintainContainedAirPath();
      bool repairContainedAirPath(LoadContext& context);
      bool reconcileContainedAirPath(bool allowChildNodeRecovery, LoadContext* context = nullptr);
    };

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
