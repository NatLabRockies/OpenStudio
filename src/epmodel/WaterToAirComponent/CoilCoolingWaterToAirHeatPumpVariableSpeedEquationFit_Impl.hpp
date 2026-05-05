/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_COILCOOLINGWATERTOAIRHEATPUMPVARIABLESPEEDEQUATIONFIT_IMPL_HPP
#define EPMODEL_COILCOOLINGWATERTOAIRHEATPUMPVARIABLESPEEDEQUATIONFIT_IMPL_HPP

#include "WaterToAirComponent_Impl.hpp"

namespace openstudio {
namespace epmodel {

  class Curve;
  class Schedule;
  class CoilCoolingWaterToAirHeatPumpVariableSpeedEquationFit;
  class CoilCoolingWaterToAirHeatPumpVariableSpeedEquationFitSpeedData;
  class AirflowNetworkDistributionComponentCoil;

  namespace detail {

    std::string transientSpeedDataName(const openstudio::epmodel::CoilCoolingWaterToAirHeatPumpVariableSpeedEquationFit& parent, unsigned speedIndex);

    class EPMODEL_API CoilCoolingWaterToAirHeatPumpVariableSpeedEquationFit_Impl : public WaterToAirComponent_Impl
    {
     public:
      using WaterToAirComponent_Impl::WaterToAirComponent_Impl;
      virtual ~CoilCoolingWaterToAirHeatPumpVariableSpeedEquationFit_Impl() override = default;

      unsigned airInletPort() const override;
      unsigned airOutletPort() const override;
      unsigned waterInletPort() const override;
      unsigned waterOutletPort() const override;

      Schedule availabilitySchedule() const;
      bool setAvailabilitySchedule(Schedule& schedule);

      int nominalSpeedLevel() const;
      bool setNominalSpeedLevel(int nominalSpeedLevel);

      boost::optional<double> grossRatedTotalCoolingCapacityAtSelectedNominalSpeedLevel() const;
      bool setGrossRatedTotalCoolingCapacityAtSelectedNominalSpeedLevel(double grossRatedTotalCoolingCapacityAtSelectedNominalSpeedLevel);
      void autosizeGrossRatedTotalCoolingCapacityAtSelectedNominalSpeedLevel();
      bool isGrossRatedTotalCoolingCapacityAtSelectedNominalSpeedLevelAutosized() const;
      boost::optional<double> autosizedGrossRatedTotalCoolingCapacityAtSelectedNominalSpeedLevel() const;

      boost::optional<double> ratedAirFlowRateAtSelectedNominalSpeedLevel() const;
      bool setRatedAirFlowRateAtSelectedNominalSpeedLevel(double ratedAirFlowRateAtSelectedNominalSpeedLevel);
      void autosizeRatedAirFlowRateAtSelectedNominalSpeedLevel();
      bool isRatedAirFlowRateAtSelectedNominalSpeedLevelAutosized() const;
      boost::optional<double> autosizedRatedAirFlowRateAtSelectedNominalSpeedLevel() const;

      boost::optional<double> ratedWaterFlowRateAtSelectedNominalSpeedLevel() const;
      bool setRatedWaterFlowRateAtSelectedNominalSpeedLevel(double ratedWaterFlowRateAtSelectedNominalSpeedLevel);
      void autosizeRatedWaterFlowRateAtSelectedNominalSpeedLevel();
      bool isRatedWaterFlowRateAtSelectedNominalSpeedLevelAutosized() const;
      boost::optional<double> autosizedRatedWaterFlowRateAtSelectedNominalSpeedLevel() const;

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

      bool useHotGasReheat() const;
      bool setUseHotGasReheat(bool useHotGasReheat);

      Curve energyPartLoadFractionCurve() const;
      bool setEnergyPartLoadFractionCurve(const Curve& curve);

      std::vector<CoilCoolingWaterToAirHeatPumpVariableSpeedEquationFitSpeedData> speeds() const;
      bool addSpeed(const CoilCoolingWaterToAirHeatPumpVariableSpeedEquationFitSpeedData& speed);
      void removeSpeed(const CoilCoolingWaterToAirHeatPumpVariableSpeedEquationFitSpeedData& speed);
      void removeAllSpeeds();

      AirflowNetworkDistributionComponentCoil getAirflowNetworkEquivalentDuct(double length, double diameter);
      boost::optional<AirflowNetworkDistributionComponentCoil> airflowNetworkEquivalentDuct() const;

      std::vector<ModelObject> children() const override;
      std::vector<IdfObject> remove() override;

      void setConstructorScalarDefaults();
    };

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
