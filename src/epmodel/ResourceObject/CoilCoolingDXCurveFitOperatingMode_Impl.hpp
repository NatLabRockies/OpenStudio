/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_COILCOOLINGDXCURVEFITOPERATINGMODE_IMPL_HPP
#define EPMODEL_COILCOOLINGDXCURVEFITOPERATINGMODE_IMPL_HPP

#include "ModelObject_Impl.hpp"

#include <vector>

namespace openstudio {
namespace epmodel {

  namespace detail {

    class EPMODEL_API CoilCoolingDXCurveFitOperatingMode_Impl : public ModelObject_Impl
    {
     public:
      using ModelObject_Impl::ModelObject_Impl;
      virtual ~CoilCoolingDXCurveFitOperatingMode_Impl() override = default;

      boost::optional<double> ratedGrossTotalCoolingCapacity() const;
      bool isRatedGrossTotalCoolingCapacityAutosized() const;
      bool setRatedGrossTotalCoolingCapacity(double ratedGrossTotalCoolingCapacity);
      void autosizeRatedGrossTotalCoolingCapacity();

      boost::optional<double> ratedEvaporatorAirFlowRate() const;
      bool isRatedEvaporatorAirFlowRateAutosized() const;
      bool setRatedEvaporatorAirFlowRate(double ratedEvaporatorAirFlowRate);
      void autosizeRatedEvaporatorAirFlowRate();

      boost::optional<double> ratedCondenserAirFlowRate() const;
      bool isRatedCondenserAirFlowRateAutosized() const;
      bool setRatedCondenserAirFlowRate(double ratedCondenserAirFlowRate);
      void autosizeRatedCondenserAirFlowRate();

      double maximumCyclingRate() const;
      bool setMaximumCyclingRate(double maximumCyclingRate);

      double ratioofInitialMoistureEvaporationRateandSteadyStateLatentCapacity() const;
      bool setRatioofInitialMoistureEvaporationRateandSteadyStateLatentCapacity(
        double ratioofInitialMoistureEvaporationRateandSteadyStateLatentCapacity);

      double latentCapacityTimeConstant() const;
      bool setLatentCapacityTimeConstant(double latentCapacityTimeConstant);

      double nominalTimeforCondensateRemovaltoBegin() const;
      bool setNominalTimeforCondensateRemovaltoBegin(double nominalTimeforCondensateRemovaltoBegin);

      bool applyLatentDegradationtoSpeedsGreaterthan1() const;
      bool setApplyLatentDegradationtoSpeedsGreaterthan1(bool applyLatentDegradationtoSpeedsGreaterthan1);

      std::string condenserType() const;
      bool setCondenserType(const std::string& condenserType);

      boost::optional<double> nominalEvaporativeCondenserPumpPower() const;
      bool isNominalEvaporativeCondenserPumpPowerAutosized() const;
      bool setNominalEvaporativeCondenserPumpPower(double nominalEvaporativeCondenserPumpPower);
      void autosizeNominalEvaporativeCondenserPumpPower();

      unsigned nominalSpeedNumber() const;
      bool isNominalSpeedNumberDefaulted() const;
      bool setNominalSpeedNumber(unsigned nominalSpeedNumber);
      void resetNominalSpeedNumber();

      std::vector<std::string> condenserTypeValues() const;
    };

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
