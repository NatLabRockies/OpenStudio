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

  namespace detail {

    class EPMODEL_API WaterHeaterHeatPump_Impl : public ZoneHVACComponent_Impl
    {
     public:
      using ZoneHVACComponent_Impl::ZoneHVACComponent_Impl;
      virtual ~WaterHeaterHeatPump_Impl() override = default;

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

      std::string tankElementControlLogic() const;
      bool isTankElementControlLogicDefaulted() const;
      bool setTankElementControlLogic(const std::string& tankElementControlLogic);
      void resetTankElementControlLogic();

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
    };

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
