/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_WATERHEATERHEATPUMP_IMPL_HPP
#define EPMODEL_WATERHEATERHEATPUMP_IMPL_HPP

#include "ZoneHVACComponent_Impl.hpp"

#include <string>

namespace openstudio {
namespace epmodel {

  class HVACComponent;
  class LoadContext;
  class ModelObject;
  class Node;
  class Schedule;
  class ThermalZone;

  namespace detail {

    class EPMODEL_API WaterHeaterHeatPump_Impl : public ZoneHVACComponent_Impl
    {
     public:
      using ZoneHVACComponent_Impl::ZoneHVACComponent_Impl;
      virtual ~WaterHeaterHeatPump_Impl() override = default;

      boost::optional<Schedule> availabilitySchedule() const;
      bool setAvailabilitySchedule(Schedule& schedule);
      void resetAvailabilitySchedule();

      Schedule compressorSetpointTemperatureSchedule() const;
      bool setCompressorSetpointTemperatureSchedule(Schedule& schedule);

      double deadBandTemperatureDifference() const;
      bool isDeadBandTemperatureDifferenceDefaulted() const;
      bool setDeadBandTemperatureDifference(double deadBandTemperatureDifference);
      void resetDeadBandTemperatureDifference();

      boost::optional<double> condenserWaterFlowRate() const;
      bool isCondenserWaterFlowRateAutosized() const;
      bool setCondenserWaterFlowRate(double condenserWaterFlowRate);
      void resetCondenserWaterFlowRate();
      void autosizeCondenserWaterFlowRate();

      boost::optional<double> evaporatorAirFlowRate() const;
      bool isEvaporatorAirFlowRateAutosized() const;
      bool setEvaporatorAirFlowRate(double evaporatorAirFlowRate);
      void resetEvaporatorAirFlowRate();
      void autosizeEvaporatorAirFlowRate();

      std::string inletAirConfiguration() const;
      bool setInletAirConfiguration(const std::string& inletAirConfiguration);

      boost::optional<Schedule> inletAirTemperatureSchedule() const;
      bool setInletAirTemperatureSchedule(Schedule& schedule);
      void resetInletAirTemperatureSchedule();

      boost::optional<Schedule> inletAirHumiditySchedule() const;
      bool setInletAirHumiditySchedule(Schedule& schedule);
      void resetInletAirHumiditySchedule();

      HVACComponent tank() const;
      bool setTank(const HVACComponent& waterHeater);

      ModelObject dXCoil() const;
      bool setDXCoil(const ModelObject& heatPumpWaterHeaterDXCoil);

      double minimumInletAirTemperatureforCompressorOperation() const;
      bool isMinimumInletAirTemperatureforCompressorOperationDefaulted() const;
      bool setMinimumInletAirTemperatureforCompressorOperation(double minimumInletAirTemperatureforCompressorOperation);
      void resetMinimumInletAirTemperatureforCompressorOperation();

      double maximumInletAirTemperatureforCompressorOperation() const;
      bool isMaximumInletAirTemperatureforCompressorOperationDefaulted() const;
      bool setMaximumInletAirTemperatureforCompressorOperation(double maximumInletAirTemperatureforCompressorOperation);
      void resetMaximumInletAirTemperatureforCompressorOperation();

      std::string compressorLocation() const;
      bool setCompressorLocation(const std::string& compressorLocation);

      boost::optional<Schedule> compressorAmbientTemperatureSchedule() const;
      bool setCompressorAmbientTemperatureSchedule(Schedule& schedule);
      void resetCompressorAmbientTemperatureSchedule();

      HVACComponent fan() const;
      bool setFan(const HVACComponent& fan);

      std::string fanPlacement() const;
      bool isFanPlacementDefaulted() const;
      bool setFanPlacement(const std::string& fanPlacement);
      void resetFanPlacement();

      double onCycleParasiticElectricLoad() const;
      bool isOnCycleParasiticElectricLoadDefaulted() const;
      bool setOnCycleParasiticElectricLoad(double onCycleParasiticElectricLoad);
      void resetOnCycleParasiticElectricLoad();

      double offCycleParasiticElectricLoad() const;
      bool isOffCycleParasiticElectricLoadDefaulted() const;
      bool setOffCycleParasiticElectricLoad(double offCycleParasiticElectricLoad);
      void resetOffCycleParasiticElectricLoad();

      std::string parasiticHeatRejectionLocation() const;
      bool isParasiticHeatRejectionLocationDefaulted() const;
      bool setParasiticHeatRejectionLocation(const std::string& parasiticHeatRejectionLocation);
      void resetParasiticHeatRejectionLocation();

      Schedule inletAirMixerSchedule() const;
      bool setInletAirMixerSchedule(Schedule& schedule);

      std::string tankElementControlLogic() const;
      bool isTankElementControlLogicDefaulted() const;
      bool setTankElementControlLogic(const std::string& tankElementControlLogic);
      void resetTankElementControlLogic();

      boost::optional<Node> fanOutletNode() const;
      boost::optional<Node> mixedAirNode() const;
      boost::optional<Node> outdoorAirNode() const;
      boost::optional<Node> reliefAirNode() const;
      boost::optional<Node> condenserWaterInletNode() const;
      boost::optional<Node> condenserWaterOutletNode() const;

      std::vector<ModelObject> children() const override;
      unsigned inletPort() const override;
      unsigned outletPort() const override;

      bool addToThermalZone(ThermalZone& thermalZone) override;
      void removeFromThermalZone() override;
      void doCanonicalize(LoadContext& context) override;

      boost::optional<double> controlSensor1HeightInStratifiedTank() const;
      bool setControlSensor1HeightInStratifiedTank(double controlSensor1HeightInStratifiedTank);
      void resetControlSensor1HeightInStratifiedTank();

      double controlSensor1Weight() const;
      bool isControlSensor1WeightDefaulted() const;
      bool setControlSensor1Weight(double controlSensor1Weight);
      void resetControlSensor1Weight();

      boost::optional<double> controlSensor2HeightInStratifiedTank() const;
      bool setControlSensor2HeightInStratifiedTank(double controlSensor2HeightInStratifiedTank);
      void resetControlSensor2HeightInStratifiedTank();

     private:
      bool maintainContainedTopology();
      bool repairContainedTopology(LoadContext& context);
      bool reconcileContainedTopology(bool allowNodeRecovery, LoadContext* context = nullptr);
    };

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
