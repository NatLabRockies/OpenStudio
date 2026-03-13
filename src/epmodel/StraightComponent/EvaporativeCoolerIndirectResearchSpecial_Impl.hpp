/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_EVAPORATIVECOOLERINDIRECTRESEARCHSPECIAL_IMPL_HPP
#define EPMODEL_EVAPORATIVECOOLERINDIRECTRESEARCHSPECIAL_IMPL_HPP

#include "StraightComponent/StraightComponent_Impl.hpp"

#include <boost/optional.hpp>

namespace openstudio {
namespace epmodel {
  class Node;
  namespace detail {

    class EPMODEL_API EvaporativeCoolerIndirectResearchSpecial_Impl : public StraightComponent_Impl
    {
     public:
      using StraightComponent_Impl::StraightComponent_Impl;
      virtual ~EvaporativeCoolerIndirectResearchSpecial_Impl() override = default;

      bool addToNode(Node& node) override;

      unsigned inletPort() const override;
      unsigned outletPort() const override;

      double coolerMaximumEffectiveness() const;
      bool setCoolerMaximumEffectiveness(double coolerMaximumEffectiveness);

      boost::optional<double> recirculatingWaterPumpPowerConsumption() const;
      bool isRecirculatingWaterPumpPowerConsumptionAutosized() const;
      bool setRecirculatingWaterPumpPowerConsumption(double recirculatingWaterPumpPowerConsumption);
      void autosizeRecirculatingWaterPumpPowerConsumption();
      boost::optional<double> autosizedRecirculatingWaterPumpPowerConsumption() const;

      boost::optional<double> secondaryFanFlowRate() const;
      bool isSecondaryFanFlowRateAutosized() const;
      bool setSecondaryFanFlowRate(double secondaryFanFlowRate);
      void resetSecondaryFanFlowRate();
      void autosizeSecondaryFanFlowRate();
      boost::optional<double> autosizedSecondaryFanFlowRate() const;

      double secondaryFanTotalEfficiency() const;
      bool setSecondaryFanTotalEfficiency(double secondaryFanTotalEfficiency);

      double secondaryFanDeltaPressure() const;
      bool setSecondaryFanDeltaPressure(double secondaryFanDeltaPressure);

      double dewpointEffectivenessFactor() const;
      bool setDewpointEffectivenessFactor(double dewpointEffectivenessFactor);

      boost::optional<double> driftLossFraction() const;
      bool setDriftLossFraction(double driftLossFraction);
      void resetDriftLossFraction();

      boost::optional<double> blowdownConcentrationRatio() const;
      bool setBlowdownConcentrationRatio(double blowdownConcentrationRatio);
      void resetBlowdownConcentrationRatio();

      boost::optional<double> coolerDrybulbDesignEffectiveness() const;
      bool setCoolerDrybulbDesignEffectiveness(double coolerDrybulbDesignEffectiveness);
      void resetCoolerDrybulbDesignEffectiveness();

      double waterPumpPowerSizingFactor() const;
      bool setWaterPumpPowerSizingFactor(double waterPumpPowerSizingFactor);

      double secondaryAirFlowScalingFactor() const;
      bool setSecondaryAirFlowScalingFactor(double secondaryAirFlowScalingFactor);

      boost::optional<double> secondaryAirFanDesignPower() const;
      bool isSecondaryAirFanDesignPowerAutosized() const;
      bool setSecondaryAirFanDesignPower(double secondaryAirFanDesignPower);
      void autosizeSecondaryAirFanDesignPower();
      boost::optional<double> autosizedSecondaryAirFanDesignPower() const;

      boost::optional<double> primaryDesignAirFlowRate() const;
      bool isPrimaryDesignAirFlowRateAutosized() const;
      bool setPrimaryDesignAirFlowRate(double primaryDesignAirFlowRate);
      void resetPrimaryDesignAirFlowRate();
      void autosizePrimaryDesignAirFlowRate();
      boost::optional<double> autosizedPrimaryDesignAirFlowRate() const;
    };

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
