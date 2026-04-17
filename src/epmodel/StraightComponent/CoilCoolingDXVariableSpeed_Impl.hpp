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
  class Schedule;
  class Curve;
  namespace detail {

    class EPMODEL_API CoilCoolingDXVariableSpeed_Impl : public StraightComponent_Impl
    {
     public:
      using StraightComponent_Impl::StraightComponent_Impl;
      virtual ~CoilCoolingDXVariableSpeed_Impl() override = default;

      unsigned inletPort() const override;
      unsigned outletPort() const override;
      std::vector<ModelObject> children() const override;

      bool addToNode(Node& node) override;

      Schedule availabilitySchedule() const;
      bool setAvailabilitySchedule(Schedule& schedule);

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

      Curve energyPartLoadFractionCurve() const;
      bool setEnergyPartLoadFractionCurve(const Curve& curve);

      std::vector<std::string> condenserTypeValues() const;
      std::string condenserType() const;
      bool setCondenserType(const std::string& condenserType);

      boost::optional<double> evaporativeCondenserPumpRatedPowerConsumption() const;
      bool setEvaporativeCondenserPumpRatedPowerConsumption(double evaporativeCondenserPumpRatedPowerConsumption);
      bool isEvaporativeCondenserPumpRatedPowerConsumptionAutosized() const;
      void autosizeEvaporativeCondenserPumpRatedPowerConsumption();

      double crankcaseHeaterCapacity() const;
      bool setCrankcaseHeaterCapacity(double crankcaseHeaterCapacity);

      boost::optional<Curve> crankcaseHeaterCapacityFunctionofTemperatureCurve() const;
      bool setCrankcaseHeaterCapacityFunctionofTemperatureCurve(const Curve& curve);
      void resetCrankcaseHeaterCapacityFunctionofTemperatureCurve();

      double maximumOutdoorDryBulbTemperatureforCrankcaseHeaterOperation() const;
      bool setMaximumOutdoorDryBulbTemperatureforCrankcaseHeaterOperation(double maximumOutdoorDryBulbTemperatureforCrankcaseHeaterOperation);

      double basinHeaterCapacity() const;
      bool setBasinHeaterCapacity(double basinHeaterCapacity);

      double basinHeaterSetpointTemperature() const;
      bool setBasinHeaterSetpointTemperature(double basinHeaterSetpointTemperature);

      boost::optional<Schedule> basinHeaterOperatingSchedule() const;
      bool setBasinHeaterOperatingSchedule(Schedule& schedule);
      void resetBasinHeaterOperatingSchedule();

      double minimumOutdoorDryBulbTemperatureforCompressorOperation() const;
      bool setMinimumOutdoorDryBulbTemperatureforCompressorOperation(double minimumOutdoorDryBulbTemperatureforCompressorOperation);
    };

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
