/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_WATERHEATERHEATPUMPWRAPPEDCONDENSER_IMPL_HPP
#define EPMODEL_WATERHEATERHEATPUMPWRAPPEDCONDENSER_IMPL_HPP

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

    class EPMODEL_API WaterHeaterHeatPumpWrappedCondenser_Impl : public ZoneHVACComponent_Impl
    {
     public:
      using ZoneHVACComponent_Impl::ZoneHVACComponent_Impl;
      virtual ~WaterHeaterHeatPumpWrappedCondenser_Impl() override = default;

      boost::optional<Schedule> availabilitySchedule() const;
      bool setAvailabilitySchedule(Schedule& schedule);
      void resetAvailabilitySchedule();

      Schedule compressorSetpointTemperatureSchedule() const;
      bool setCompressorSetpointTemperatureSchedule(Schedule& schedule);

      double deadBandTemperatureDifference() const;
      bool isDeadBandTemperatureDifferenceDefaulted() const;
      bool setDeadBandTemperatureDifference(double deadBandTemperatureDifference);
      void resetDeadBandTemperatureDifference();

      double condenserBottomLocation() const;
      bool isCondenserBottomLocationDefaulted() const;
      bool setCondenserBottomLocation(double condenserBottomLocation);
      void resetCondenserBottomLocation();

      double condenserTopLocation() const;
      bool setCondenserTopLocation(double condenserTopLocation);

      boost::optional<double> evaporatorAirFlowRate() const;
      bool isEvaporatorAirFlowRateAutocalculated() const;
      bool setEvaporatorAirFlowRate(double evaporatorAirFlowRate);
      void resetEvaporatorAirFlowRate();
      void autocalculateEvaporatorAirFlowRate();

      std::string inletAirConfiguration() const;
      bool setInletAirConfiguration(const std::string& inletAirConfiguration);

      boost::optional<Schedule> inletAirTemperatureSchedule() const;
      bool setInletAirTemperatureSchedule(Schedule& schedule);
      void resetInletAirTemperatureSchedule();

      boost::optional<Schedule> inletAirHumiditySchedule() const;
      bool setInletAirHumiditySchedule(Schedule& schedule);
      void resetInletAirHumiditySchedule();

      HVACComponent tank() const;
      bool setTank(const HVACComponent& waterHeaterStratified);

      ModelObject dXCoil() const;
      bool setDXCoil(const ModelObject& heatPumpWaterHeaterDXCoilWrapped);

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

      boost::optional<Schedule> inletAirMixerSchedule() const;
      bool setInletAirMixerSchedule(Schedule& schedule);
      void resetInletAirMixerSchedule();

      std::string tankElementControlLogic() const;
      bool isTankElementControlLogicDefaulted() const;
      bool setTankElementControlLogic(const std::string& tankElementControlLogic);
      void resetTankElementControlLogic();

      std::string airInletNodeName() const;
      std::string airOutletNodeName() const;
      boost::optional<Node> fanOutletNode() const;
      boost::optional<Node> mixedAirNode() const;
      boost::optional<Node> outdoorAirNode() const;
      boost::optional<Node> reliefAirNode() const;

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
      bool maintainContainedAirPath();
      bool repairContainedAirPath(LoadContext& context);
      bool reconcileContainedAirPath(bool allowNodeRecovery, LoadContext* context = nullptr);
    };

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
