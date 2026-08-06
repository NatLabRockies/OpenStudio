/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_AIRTERMINALSINGLEDUCTSERIESPIUREHEAT_IMPL_HPP
#define EPMODEL_AIRTERMINALSINGLEDUCTSERIESPIUREHEAT_IMPL_HPP

#include "StraightComponent/StraightComponent_Impl.hpp"
#include "ModelObject/ZoneHVACAirDistributionUnit.hpp"

#include <vector>

namespace openstudio {
namespace epmodel {

  class Schedule;
  class HVACComponent;
  class Node;

  namespace detail {

    class EPMODEL_API AirTerminalSingleDuctSeriesPIUReheat_Impl : public StraightComponent_Impl
    {
     public:
      enum class AddToNodeFailureStage
      {
        None,
        AfterTopologyPrepared,
      };

      using StraightComponent_Impl::StraightComponent_Impl;
      virtual ~AirTerminalSingleDuctSeriesPIUReheat_Impl() override = default;

      unsigned inletPort() const override;
      unsigned outletPort() const override;
      std::vector<ModelObject> children() const override;
      std::vector<openstudio::IdfObject> remove() override;
      bool removeFromLoop() override;
      bool addToNode(Node& node) override;
      bool addToNode(Node& node, AddToNodeFailureStage failureStage);
      boost::optional<ZoneHVACAirDistributionUnit> zoneHVACAirDistributionUnit() const;

      boost::optional<Schedule> availabilitySchedule() const;
      bool setAvailabilitySchedule(Schedule& schedule);
      void resetAvailabilitySchedule();

      HVACComponent fan() const;
      bool setFan(const HVACComponent& fan);

      HVACComponent reheatCoil() const;
      bool setReheatCoil(const HVACComponent& coil);

      boost::optional<Node> secondaryAirInletNode() const;

      std::vector<std::string> fanControlTypeValues() const;
      std::vector<std::string> heatingControlTypeValues() const;

      boost::optional<double> maximumAirFlowRate() const;
      bool isMaximumAirFlowRateAutosized() const;
      bool setMaximumAirFlowRate(double maximumAirFlowRate);
      void autosizeMaximumAirFlowRate();

      boost::optional<double> maximumPrimaryAirFlowRate() const;
      bool isMaximumPrimaryAirFlowRateAutosized() const;
      bool setMaximumPrimaryAirFlowRate(double maximumPrimaryAirFlowRate);
      void autosizeMaximumPrimaryAirFlowRate();

      boost::optional<double> minimumPrimaryAirFlowFraction() const;
      bool isMinimumPrimaryAirFlowFractionAutosized() const;
      bool setMinimumPrimaryAirFlowFraction(double minimumPrimaryAirFlowFraction);
      void autosizeMinimumPrimaryAirFlowFraction();

      boost::optional<double> maximumHotWaterorSteamFlowRate() const;
      bool isMaximumHotWaterorSteamFlowRateAutosized() const;
      bool setMaximumHotWaterorSteamFlowRate(double maximumHotWaterorSteamFlowRate);
      void resetMaximumHotWaterorSteamFlowRate();
      void autosizeMaximumHotWaterorSteamFlowRate();

      double minimumHotWaterorSteamFlowRate() const;
      bool setMinimumHotWaterorSteamFlowRate(double minimumHotWaterorSteamFlowRate);

      double convergenceTolerance() const;
      bool setConvergenceTolerance(double convergenceTolerance);

      std::string fanControlType() const;
      bool setFanControlType(const std::string& fanControlType);

      double minimumFanTurnDownRatio() const;
      bool setMinimumFanTurnDownRatio(double minimumFanTurnDownRatio);

      std::string heatingControlType() const;
      bool setHeatingControlType(const std::string& heatingControlType);

      double designHeatingDischargeAirTemperature() const;
      bool setDesignHeatingDischargeAirTemperature(double designHeatingDischargeAirTemperature);

      double highLimitHeatingDischargeAirTemperature() const;
      bool setHighLimitHeatingDischargeAirTemperature(double highLimitHeatingDischargeAirTemperature);

     private:
      class InsertionPlan;
    };

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
