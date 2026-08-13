/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_AIRTERMINALSINGLEDUCTVAVHEATANDCOOLREHEAT_IMPL_HPP
#define EPMODEL_AIRTERMINALSINGLEDUCTVAVHEATANDCOOLREHEAT_IMPL_HPP

#include "StraightComponent/StraightComponent_Impl.hpp"
#include "ModelObject/ZoneHVACAirDistributionUnit.hpp"
#include "Node.hpp"

#include <vector>

namespace openstudio {
namespace epmodel {

  class Schedule;
  class HVACComponent;

  namespace detail {

    class EPMODEL_API AirTerminalSingleDuctVAVHeatAndCoolReheat_Impl : public StraightComponent_Impl
    {
     public:
      enum class AddToNodeFailureStage
      {
        None,
        AfterADUUpdateBeforeZoneRegistration,
      };

      using StraightComponent_Impl::StraightComponent_Impl;
      virtual ~AirTerminalSingleDuctVAVHeatAndCoolReheat_Impl() override = default;

      unsigned inletPort() const override;
      unsigned outletPort() const override;
      std::vector<ModelObject> children() const override;
      bool isRemovable() const override;
      std::vector<openstudio::IdfObject> remove() override;
      bool removeFromLoop() override;
      boost::optional<ZoneHVACAirDistributionUnit> zoneHVACAirDistributionUnit() const;
      bool addToNode(Node& node) override;
      bool addToNode(Node& node, AddToNodeFailureStage failureStage);

      boost::optional<Schedule> availabilitySchedule() const;
      bool setAvailabilitySchedule(Schedule& schedule);
      void resetAvailabilitySchedule();

      HVACComponent reheatCoil() const;
      bool setReheatCoil(const HVACComponent& heatingCoilName);

      boost::optional<Schedule> minimumAirFlowTurndownSchedule() const;
      bool setMinimumAirFlowTurndownSchedule(Schedule& schedule);
      void resetMinimumAirFlowTurndownSchedule();

      boost::optional<double> maximumAirFlowRate() const;
      bool setMaximumAirFlowRate(double maximumAirFlowRate);
      bool isMaximumAirFlowRateAutosized() const;
      void autosizeMaximumAirFlowRate();

      double zoneMinimumAirFlowFraction() const;
      bool setZoneMinimumAirFlowFraction(double zoneMinimumAirFlowFraction);

      boost::optional<double> maximumHotWaterorSteamFlowRate() const;
      bool setMaximumHotWaterorSteamFlowRate(double maximumHotWaterorSteamFlowRate);
      bool isMaximumHotWaterorSteamFlowRateAutosized() const;
      void autosizeMaximumHotWaterorSteamFlowRate();

      double minimumHotWaterorSteamFlowRate() const;
      bool setMinimumHotWaterorSteamFlowRate(double minimumHotWaterorSteamFlowRate);

      double convergenceTolerance() const;
      bool setConvergenceTolerance(double convergenceTolerance);

      double maximumReheatAirTemperature() const;
      bool setMaximumReheatAirTemperature(double maximumReheatAirTemperature);
    };

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
