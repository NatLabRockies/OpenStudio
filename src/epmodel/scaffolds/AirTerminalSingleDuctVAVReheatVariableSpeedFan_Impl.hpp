/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_AIRTERMINALSINGLEDUCTVAVREHEATVARIABLESPEEDFAN_IMPL_HPP
#define EPMODEL_AIRTERMINALSINGLEDUCTVAVREHEATVARIABLESPEEDFAN_IMPL_HPP

#include "StraightComponent/StraightComponent_Impl.hpp"
#include "ModelObject/ZoneHVACAirDistributionUnit.hpp"
#include "Node.hpp"

namespace openstudio {
namespace epmodel {

  class Schedule;
  class HVACComponent;

  namespace detail {

    class EPMODEL_API AirTerminalSingleDuctVAVReheatVariableSpeedFan_Impl : public StraightComponent_Impl
    {
     public:
      using StraightComponent_Impl::StraightComponent_Impl;
      virtual ~AirTerminalSingleDuctVAVReheatVariableSpeedFan_Impl() override = default;

      unsigned inletPort() const override;
      unsigned outletPort() const override;
      std::vector<ModelObject> children() const override;
      std::vector<openstudio::IdfObject> remove() override;
      bool removeFromLoop() override;
      boost::optional<ZoneHVACAirDistributionUnit> zoneHVACAirDistributionUnit() const;
      bool addToNode(Node& node) override;

      boost::optional<Schedule> availabilitySchedule() const;
      bool setAvailabilitySchedule(Schedule& schedule);

      HVACComponent fan() const;
      bool setFan(HVACComponent& fan);

      HVACComponent heatingCoil() const;
      bool setHeatingCoil(HVACComponent& coil);

      boost::optional<double> maximumCoolingAirFlowRate() const;
      bool setMaximumCoolingAirFlowRate(double maximumCoolingAirFlowRate);
      bool isMaximumCoolingAirFlowRateAutosized() const;
      void autosizeMaximumCoolingAirFlowRate();

      boost::optional<double> maximumHeatingAirFlowRate() const;
      bool setMaximumHeatingAirFlowRate(double maximumHeatingAirFlowRate);
      bool isMaximumHeatingAirFlowRateAutosized() const;
      void autosizeMaximumHeatingAirFlowRate();

      double zoneMinimumAirFlowFraction() const;
      bool setZoneMinimumAirFlowFraction(double zoneMinimumAirFlowFraction);

      boost::optional<double> maximumHotWaterorSteamFlowRate() const;
      bool setMaximumHotWaterorSteamFlowRate(double maximumHotWaterorSteamFlowRate);
      bool isMaximumHotWaterorSteamFlowRateAutosized() const;
      void autosizeMaximumHotWaterorSteamFlowRate();

      double minimumHotWaterorSteamFlowRate() const;
      bool setMinimumHotWaterorSteamFlowRate(double minimumHotWaterorSteamFlowRate);
      bool isMinimumHotWaterorSteamFlowRateDefaulted() const;
      void resetMinimumHotWaterorSteamFlowRate();

      double heatingConvergenceTolerance() const;
      bool setHeatingConvergenceTolerance(double heatingConvergenceTolerance);
      bool isHeatingConvergenceToleranceDefaulted() const;
      void resetHeatingConvergenceTolerance();
    };

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
