/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_EVAPORATIVECOOLERDIRECTRESEARCHSPECIAL_IMPL_HPP
#define EPMODEL_EVAPORATIVECOOLERDIRECTRESEARCHSPECIAL_IMPL_HPP

#include "StraightComponent/StraightComponent_Impl.hpp"

namespace openstudio {
namespace epmodel {
  class Curve;
  class Node;
  class Schedule;
  namespace detail {

    class EPMODEL_API EvaporativeCoolerDirectResearchSpecial_Impl : public StraightComponent_Impl
    {
     public:
      using StraightComponent_Impl::StraightComponent_Impl;
      virtual ~EvaporativeCoolerDirectResearchSpecial_Impl() override = default;

      bool addToNode(Node& node) override;

      unsigned inletPort() const override;
      unsigned outletPort() const override;

      Schedule availabilitySchedule() const;
      bool setAvailabilitySchedule(Schedule& schedule);

      double coolerDesignEffectiveness() const;
      bool setCoolerDesignEffectiveness(double value);

      boost::optional<double> recirculatingWaterPumpPowerConsumption() const;
      bool setRecirculatingWaterPumpPowerConsumption(double value);
      void autosizeRecirculatingWaterPumpPowerConsumption();
      bool isRecirculatingWaterPumpPowerConsumptionAutosized() const;
      boost::optional<double> autosizedRecirculatingWaterPumpPowerConsumption() const;

      boost::optional<double> primaryAirDesignFlowRate() const;
      bool setPrimaryAirDesignFlowRate(double value);
      void autosizePrimaryAirDesignFlowRate();
      bool isPrimaryAirDesignFlowRateAutosized() const;
      boost::optional<double> autosizedPrimaryAirDesignFlowRate() const;

      boost::optional<Node> sensorNode() const;
      bool setSensorNode(const Node& node);

      double driftLossFraction() const;
      bool setDriftLossFraction(double value);

      double blowdownConcentrationRatio() const;
      bool setBlowdownConcentrationRatio(double value);

      boost::optional<Curve> effectivenessFlowRatioModifierCurve() const;
      bool setEffectivenessFlowRatioModifierCurve(const Curve& curve);
      void resetEffectivenessFlowRatioModifierCurve();

      double waterPumpPowerSizingFactor() const;
      bool setWaterPumpPowerSizingFactor(double waterPumpPowerSizingFactor);

      boost::optional<Curve> waterPumpPowerModifierCurve() const;
      bool setWaterPumpPowerModifierCurve(const Curve& curve);
      void resetWaterPumpPowerModifierCurve();

      double evaporativeOperationMinimumDrybulbTemperature() const;
      bool setEvaporativeOperationMinimumDrybulbTemperature(double evaporativeOperationMinimumDrybulbTemperature);

      double evaporativeOperationMaximumLimitWetbulbTemperature() const;
      bool setEvaporativeOperationMaximumLimitWetbulbTemperature(double evaporativeOperationMaximumLimitWetbulbTemperature);

      double evaporativeOperationMaximumLimitDrybulbTemperature() const;
      bool setEvaporativeOperationMaximumLimitDrybulbTemperature(double evaporativeOperationMaximumLimitDrybulbTemperature);
    };

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
