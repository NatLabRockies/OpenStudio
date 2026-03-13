/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_COILCOOLINGDXVARIABLESPEED_IMPL_HPP
#define EPMODEL_COILCOOLINGDXVARIABLESPEED_IMPL_HPP

#include "StraightComponent/StraightComponent_Impl.hpp"

#include <vector>

namespace openstudio {
namespace epmodel {
  class Node;
  namespace detail {

    class EPMODEL_API CoilCoolingDXVariableSpeed_Impl : public StraightComponent_Impl
    {
     public:
      using StraightComponent_Impl::StraightComponent_Impl;
      virtual ~CoilCoolingDXVariableSpeed_Impl() override = default;

      unsigned inletPort() const override;
      unsigned outletPort() const override;

      bool addToNode(Node& node) override;

      int nominalSpeedLevel() const;
      bool setNominalSpeedLevel(int nominalSpeedLevel);

      boost::optional<double> grossRatedTotalCoolingCapacityAtSelectedNominalSpeedLevel() const;
      bool setGrossRatedTotalCoolingCapacityAtSelectedNominalSpeedLevel(double grossRatedTotalCoolingCapacityAtSelectedNominalSpeedLevel);
      bool isGrossRatedTotalCoolingCapacityAtSelectedNominalSpeedLevelAutosized() const;
      void autosizeGrossRatedTotalCoolingCapacityAtSelectedNominalSpeedLevel();

      boost::optional<double> ratedAirFlowRateAtSelectedNominalSpeedLevel() const;
      bool setRatedAirFlowRateAtSelectedNominalSpeedLevel(double ratedAirFlowRateAtSelectedNominalSpeedLevel);
      bool isRatedAirFlowRateAtSelectedNominalSpeedLevelAutosized() const;
      void autosizeRatedAirFlowRateAtSelectedNominalSpeedLevel();

      double nominalTimeforCondensatetoBeginLeavingtheCoil() const;
      bool setNominalTimeforCondensatetoBeginLeavingtheCoil(double nominalTimeforCondensatetoBeginLeavingtheCoil);

      double initialMoistureEvaporationRateDividedbySteadyStateACLatentCapacity() const;
      bool setInitialMoistureEvaporationRateDividedbySteadyStateACLatentCapacity(
        double initialMoistureEvaporationRateDividedbySteadyStateACLatentCapacity);

      double maximumCyclingRate() const;
      bool setMaximumCyclingRate(double maximumCyclingRate);

      double latentCapacityTimeConstant() const;
      bool setLatentCapacityTimeConstant(double latentCapacityTimeConstant);

      double fanDelayTime() const;
      bool setFanDelayTime(double fanDelayTime);

      std::vector<std::string> condenserTypeValues() const;
      std::string condenserType() const;
      bool setCondenserType(const std::string& condenserType);

      boost::optional<double> evaporativeCondenserPumpRatedPowerConsumption() const;
      bool setEvaporativeCondenserPumpRatedPowerConsumption(double evaporativeCondenserPumpRatedPowerConsumption);
      bool isEvaporativeCondenserPumpRatedPowerConsumptionAutosized() const;
      void autosizeEvaporativeCondenserPumpRatedPowerConsumption();

      double crankcaseHeaterCapacity() const;
      bool setCrankcaseHeaterCapacity(double crankcaseHeaterCapacity);

      double maximumOutdoorDryBulbTemperatureforCrankcaseHeaterOperation() const;
      bool setMaximumOutdoorDryBulbTemperatureforCrankcaseHeaterOperation(double maximumOutdoorDryBulbTemperatureforCrankcaseHeaterOperation);

      double basinHeaterCapacity() const;
      bool setBasinHeaterCapacity(double basinHeaterCapacity);

      double basinHeaterSetpointTemperature() const;
      bool setBasinHeaterSetpointTemperature(double basinHeaterSetpointTemperature);

      double minimumOutdoorDryBulbTemperatureforCompressorOperation() const;
      bool setMinimumOutdoorDryBulbTemperatureforCompressorOperation(double minimumOutdoorDryBulbTemperatureforCompressorOperation);
    };

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
