/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_AIRLOOPHVACUNITARYHEATCOOL_IMPL_HPP
#define EPMODEL_AIRLOOPHVACUNITARYHEATCOOL_IMPL_HPP

#include "StraightComponent/StraightComponent_Impl.hpp"

#include <vector>

namespace openstudio {
namespace epmodel {
  class Node;
  class HVACComponent;
  class Schedule;
  class ThermalZone;

  namespace detail {
    struct LoadContext;

    class EPMODEL_API AirLoopHVACUnitaryHeatCool_Impl : public StraightComponent_Impl
    {
     public:
      using StraightComponent_Impl::StraightComponent_Impl;
      ~AirLoopHVACUnitaryHeatCool_Impl() override = default;

      unsigned inletPort() const override;
      unsigned outletPort() const override;
      bool addToNode(Node& node) override;
      std::vector<IdfObject> remove() override;
      void doCanonicalize(LoadContext& context) override;
      std::vector<ModelObject> children() const override;

      Schedule availabilitySchedule() const;
      bool setAvailabilitySchedule(Schedule& schedule);

      boost::optional<Schedule> supplyAirFanOperatingModeSchedule() const;
      bool setSupplyAirFanOperatingModeSchedule(Schedule& schedule);
      void resetSupplyAirFanOperatingModeSchedule();

      boost::optional<ThermalZone> controllingZone() const;
      bool setControllingZone(ThermalZone& zone);
      void resetControllingZone();

      HVACComponent supplyFan() const;
      bool setSupplyFan(HVACComponent& hvacComponent);
      HVACComponent heatingCoil() const;
      bool setHeatingCoil(HVACComponent& hvacComponent);
      HVACComponent coolingCoil() const;
      bool setCoolingCoil(HVACComponent& hvacComponent);
      boost::optional<HVACComponent> reheatCoil() const;
      bool setReheatCoil(HVACComponent& hvacComponent);
      void resetReheatCoil();

      boost::optional<Node> fanOutletNode() const;
      boost::optional<Node> coolingCoilOutletNode() const;
      boost::optional<Node> heatingCoilOutletNode() const;

      boost::optional<double> maximumSupplyAirTemperature() const;
      bool setMaximumSupplyAirTemperature(double maximumSupplyAirTemperature);
      bool isMaximumSupplyAirTemperatureDefaulted() const;
      bool isMaximumSupplyAirTemperatureAutosized() const;
      void resetMaximumSupplyAirTemperature();
      void autosizeMaximumSupplyAirTemperature();

      boost::optional<double> coolingSupplyAirFlowRate() const;
      bool setCoolingSupplyAirFlowRate(double coolingSupplyAirFlowRate);
      bool isCoolingSupplyAirFlowRateAutosized() const;
      void autosizeCoolingSupplyAirFlowRate();

      boost::optional<double> heatingSupplyAirFlowRate() const;
      bool setHeatingSupplyAirFlowRate(double heatingSupplyAirFlowRate);
      bool isHeatingSupplyAirFlowRateAutosized() const;
      void autosizeHeatingSupplyAirFlowRate();

      boost::optional<double> noLoadSupplyAirFlowRate() const;
      bool setNoLoadSupplyAirFlowRate(double noLoadSupplyAirFlowRate);
      bool isNoLoadSupplyAirFlowRateAutosized() const;
      void resetNoLoadSupplyAirFlowRate();
      void autosizeNoLoadSupplyAirFlowRate();

      std::string supplyFanObjectType() const;
      bool setSupplyFanObjectType(const std::string& supplyFanObjectType);

      std::string fanPlacement() const;
      bool setFanPlacement(const std::string& fanPlacement);
      bool isFanPlacementDefaulted() const;
      void resetFanPlacement();

      std::string heatingCoilObjectType() const;
      bool setHeatingCoilObjectType(const std::string& heatingCoilObjectType);

      std::string coolingCoilObjectType() const;
      bool setCoolingCoilObjectType(const std::string& coolingCoilObjectType);

      std::string dehumidificationControlType() const;
      bool setDehumidificationControlType(const std::string& dehumidificationControlType);
      bool isDehumidificationControlTypeDefaulted() const;
      void resetDehumidificationControlType();

      boost::optional<std::string> reheatCoilObjectType() const;
      bool setReheatCoilObjectType(const std::string& reheatCoilObjectType);
      void resetReheatCoilObjectType();

      std::vector<std::string> supplyFanObjectTypeValues() const;
      std::vector<std::string> fanPlacementValues() const;
      std::vector<std::string> heatingCoilObjectTypeValues() const;
      std::vector<std::string> coolingCoilObjectTypeValues() const;
      std::vector<std::string> dehumidificationControlTypeValues() const;
      std::vector<std::string> reheatCoilObjectTypeValues() const;

     private:
      bool maintainContainedAirPath();
      bool repairContainedAirPath(LoadContext& context);
      bool reconcileContainedAirPath(bool allowChildNodeRecovery, LoadContext* context = nullptr);
    };

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
