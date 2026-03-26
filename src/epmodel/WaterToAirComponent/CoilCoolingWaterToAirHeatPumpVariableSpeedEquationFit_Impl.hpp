/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_COILCOOLINGWATERTOAIRHEATPUMPVARIABLESPEEDEQUATIONFIT_IMPL_HPP
#define EPMODEL_COILCOOLINGWATERTOAIRHEATPUMPVARIABLESPEEDEQUATIONFIT_IMPL_HPP

#include "WaterToAirComponent_Impl.hpp"

namespace openstudio {
namespace epmodel {

  namespace detail {

    class EPMODEL_API CoilCoolingWaterToAirHeatPumpVariableSpeedEquationFit_Impl : public WaterToAirComponent_Impl
    {
     public:
      using WaterToAirComponent_Impl::WaterToAirComponent_Impl;
      virtual ~CoilCoolingWaterToAirHeatPumpVariableSpeedEquationFit_Impl() override = default;

      unsigned airInletPort() const override;
      unsigned airOutletPort() const override;
      unsigned waterInletPort() const override;
      unsigned waterOutletPort() const override;

      int nominalSpeedLevel() const;
      bool setNominalSpeedLevel(int nominalSpeedLevel);

      boost::optional<double> grossRatedTotalCoolingCapacityAtSelectedNominalSpeedLevel() const;
      bool setGrossRatedTotalCoolingCapacityAtSelectedNominalSpeedLevel(double grossRatedTotalCoolingCapacityAtSelectedNominalSpeedLevel);
      void autosizeGrossRatedTotalCoolingCapacityAtSelectedNominalSpeedLevel();
      bool isGrossRatedTotalCoolingCapacityAtSelectedNominalSpeedLevelAutosized() const;

      boost::optional<double> ratedAirFlowRateAtSelectedNominalSpeedLevel() const;
      bool setRatedAirFlowRateAtSelectedNominalSpeedLevel(double ratedAirFlowRateAtSelectedNominalSpeedLevel);
      void autosizeRatedAirFlowRateAtSelectedNominalSpeedLevel();
      bool isRatedAirFlowRateAtSelectedNominalSpeedLevelAutosized() const;

      boost::optional<double> ratedWaterFlowRateAtSelectedNominalSpeedLevel() const;
      bool setRatedWaterFlowRateAtSelectedNominalSpeedLevel(double ratedWaterFlowRateAtSelectedNominalSpeedLevel);
      void autosizeRatedWaterFlowRateAtSelectedNominalSpeedLevel();
      bool isRatedWaterFlowRateAtSelectedNominalSpeedLevelAutosized() const;

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
    };

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
