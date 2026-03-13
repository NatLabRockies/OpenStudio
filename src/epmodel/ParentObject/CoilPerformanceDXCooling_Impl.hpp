/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_COILPERFORMANCEDXCOOLING_IMPL_HPP
#define EPMODEL_COILPERFORMANCEDXCOOLING_IMPL_HPP

#include "ParentObject/ParentObject_Impl.hpp"

#include <vector>

namespace openstudio {
namespace epmodel {

  namespace detail {

    class EPMODEL_API CoilPerformanceDXCooling_Impl : public ParentObject_Impl
    {
     public:
      using ParentObject_Impl::ParentObject_Impl;
      virtual ~CoilPerformanceDXCooling_Impl() override = default;

      std::vector<std::string> condenserTypeValues() const;

      boost::optional<double> grossRatedTotalCoolingCapacity() const;
      bool setGrossRatedTotalCoolingCapacity(double grossRatedTotalCoolingCapacity);
      bool isGrossRatedTotalCoolingCapacityAutosized() const;
      void autosizeGrossRatedTotalCoolingCapacity();

      boost::optional<double> grossRatedSensibleHeatRatio() const;
      bool setGrossRatedSensibleHeatRatio(double grossRatedSensibleHeatRatio);
      bool isGrossRatedSensibleHeatRatioAutosized() const;
      void autosizeGrossRatedSensibleHeatRatio();

      double grossRatedCoolingCOP() const;
      bool setGrossRatedCoolingCOP(double grossRatedCoolingCOP);

      boost::optional<double> ratedAirFlowRate() const;
      bool setRatedAirFlowRate(double ratedAirFlowRate);
      bool isRatedAirFlowRateAutosized() const;
      void autosizeRatedAirFlowRate();

      double fractionofAirFlowBypassedAroundCoil() const;
      bool setFractionofAirFlowBypassedAroundCoil(double fractionofAirFlowBypassedAroundCoil);

      double nominalTimeforCondensateRemovaltoBegin() const;
      bool setNominalTimeforCondensateRemovaltoBegin(double nominalTimeforCondensateRemovaltoBegin);

      double ratioofInitialMoistureEvaporationRateandSteadyStateLatentCapacity() const;
      bool setRatioofInitialMoistureEvaporationRateandSteadyStateLatentCapacity(
        double ratioofInitialMoistureEvaporationRateandSteadyStateLatentCapacity);

      double maximumCyclingRate() const;
      bool setMaximumCyclingRate(double maximumCyclingRate);

      double latentCapacityTimeConstant() const;
      bool setLatentCapacityTimeConstant(double latentCapacityTimeConstant);

      std::string condenserType() const;
      bool setCondenserType(const std::string& condenserType);

      double evaporativeCondenserEffectiveness() const;
      bool setEvaporativeCondenserEffectiveness(double evaporativeCondenserEffectiveness);

      boost::optional<double> evaporativeCondenserAirFlowRate() const;
      bool setEvaporativeCondenserAirFlowRate(double evaporativeCondenserAirFlowRate);
      bool isEvaporativeCondenserAirFlowRateAutosized() const;
      void autosizeEvaporativeCondenserAirFlowRate();

      boost::optional<double> evaporativeCondenserPumpRatedPowerConsumption() const;
      bool setEvaporativeCondenserPumpRatedPowerConsumption(double evaporativeCondenserPumpRatedPowerConsumption);
      bool isEvaporativeCondenserPumpRatedPowerConsumptionAutosized() const;
      void autosizeEvaporativeCondenserPumpRatedPowerConsumption();
    };

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
