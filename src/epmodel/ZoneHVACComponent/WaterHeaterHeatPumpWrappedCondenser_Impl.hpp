/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_WATERHEATERHEATPUMPWRAPPEDCONDENSER_IMPL_HPP
#define EPMODEL_WATERHEATERHEATPUMPWRAPPEDCONDENSER_IMPL_HPP

#include "ModelObject_Impl.hpp"

#include <string>

namespace openstudio {
namespace epmodel {

  namespace detail {

    class EPMODEL_API WaterHeaterHeatPumpWrappedCondenser_Impl : public ModelObject_Impl
    {
     public:
      using ModelObject_Impl::ModelObject_Impl;
      virtual ~WaterHeaterHeatPumpWrappedCondenser_Impl() override = default;

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
