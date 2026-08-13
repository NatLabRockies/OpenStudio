/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_AIRTERMINALSINGLEDUCTCONSTANTVOLUMEFOURPIPEINDUCTION_IMPL_HPP
#define EPMODEL_AIRTERMINALSINGLEDUCTCONSTANTVOLUMEFOURPIPEINDUCTION_IMPL_HPP

#include "StraightComponent/StraightComponent_Impl.hpp"

namespace openstudio {
namespace epmodel {

  class Node;
  class Schedule;
  class ZoneHVACAirDistributionUnit;

  namespace detail {

    class EPMODEL_API AirTerminalSingleDuctConstantVolumeFourPipeInduction_Impl : public StraightComponent_Impl
    {
     public:
      enum class AddToNodeFailureStage
      {
        None,
        AfterTopologyPrepared,
      };

      using StraightComponent_Impl::StraightComponent_Impl;
      virtual ~AirTerminalSingleDuctConstantVolumeFourPipeInduction_Impl() override = default;

      unsigned inletPort() const override;
      unsigned outletPort() const override;
      bool addToNode(Node& node) override;
      bool addToNode(Node& node, AddToNodeFailureStage failureStage);
      std::vector<ModelObject> children() const override;
      std::vector<openstudio::IdfObject> remove() override;
      bool removeFromLoop() override;
      boost::optional<ZoneHVACAirDistributionUnit> zoneHVACAirDistributionUnit() const;

      boost::optional<Schedule> availabilitySchedule() const;
      bool setAvailabilitySchedule(Schedule& schedule);
      void resetAvailabilitySchedule();

      boost::optional<double> maximumTotalAirFlowRate() const;
      bool isMaximumTotalAirFlowRateAutosized() const;
      bool setMaximumTotalAirFlowRate(double maximumTotalAirFlowRate);
      void autosizeMaximumTotalAirFlowRate();

      double inductionRatio() const;
      bool isInductionRatioDefaulted() const;
      bool setInductionRatio(double inductionRatio);
      void resetInductionRatio();

      HVACComponent heatingCoil() const;
      bool setHeatingCoil(const HVACComponent& heatingCoil);

      boost::optional<double> maximumHotWaterFlowRate() const;
      bool isMaximumHotWaterFlowRateAutosized() const;
      bool setMaximumHotWaterFlowRate(double maximumHotWaterFlowRate);
      void resetMaximumHotWaterFlowRate();
      void autosizeMaximumHotWaterFlowRate();

      double minimumHotWaterFlowRate() const;
      bool isMinimumHotWaterFlowRateDefaulted() const;
      bool setMinimumHotWaterFlowRate(double minimumHotWaterFlowRate);
      void resetMinimumHotWaterFlowRate();

      double heatingConvergenceTolerance() const;
      bool isHeatingConvergenceToleranceDefaulted() const;
      bool setHeatingConvergenceTolerance(double heatingConvergenceTolerance);
      void resetHeatingConvergenceTolerance();

      boost::optional<HVACComponent> coolingCoil() const;
      bool setCoolingCoil(const boost::optional<HVACComponent>& coolingCoil);
      void resetCoolingCoil();

      boost::optional<double> maximumColdWaterFlowRate() const;
      bool isMaximumColdWaterFlowRateAutosized() const;
      bool setMaximumColdWaterFlowRate(double maximumColdWaterFlowRate);
      void resetMaximumColdWaterFlowRate();
      void autosizeMaximumColdWaterFlowRate();

      double minimumColdWaterFlowRate() const;
      bool isMinimumColdWaterFlowRateDefaulted() const;
      bool setMinimumColdWaterFlowRate(double minimumColdWaterFlowRate);
      void resetMinimumColdWaterFlowRate();

      double coolingConvergenceTolerance() const;
      bool isCoolingConvergenceToleranceDefaulted() const;
      bool setCoolingConvergenceTolerance(double coolingConvergenceTolerance);
      void resetCoolingConvergenceTolerance();

      boost::optional<Node> inducedAirInletNode() const;
      unsigned inducedAirInletPort() const;

     private:
      void doCanonicalize(LoadContext& context) override;
      bool maintainContainedAirPath();
      bool repairContainedAirPath(LoadContext& context);
      bool reconcileContainedAirPath(bool allowChildNodeRecovery, LoadContext* context);
    };

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
