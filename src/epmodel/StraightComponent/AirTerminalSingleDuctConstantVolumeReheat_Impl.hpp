/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_AIRTERMINALSINGLEDUCTCONSTANTVOLUMEREHEAT_IMPL_HPP
#define EPMODEL_AIRTERMINALSINGLEDUCTCONSTANTVOLUMEREHEAT_IMPL_HPP

#include "StraightComponent/StraightComponent_Impl.hpp"
#include "Node.hpp"
#include "ModelObject/ZoneHVACAirDistributionUnit.hpp"

namespace openstudio {
namespace epmodel {

  class Schedule;
  class HVACComponent;

  namespace detail {

    class EPMODEL_API AirTerminalSingleDuctConstantVolumeReheat_Impl : public StraightComponent_Impl
    {
     public:
      using StraightComponent_Impl::StraightComponent_Impl;
      virtual ~AirTerminalSingleDuctConstantVolumeReheat_Impl() override = default;

      unsigned inletPort() const override;
      unsigned outletPort() const override;
      std::vector<ModelObject> children() const override;
      std::vector<openstudio::IdfObject> remove() override;
      bool removeFromLoop() override;
      boost::optional<ZoneHVACAirDistributionUnit> zoneHVACAirDistributionUnit() const;
      bool addToNode(Node& node) override;

      Schedule availabilitySchedule() const;
      bool setAvailabilitySchedule(Schedule& schedule);

      HVACComponent reheatCoil() const;
      bool setReheatCoil(const HVACComponent& coil);
      void resetReheatCoil();

      boost::optional<double> maximumAirFlowRate() const;
      bool setMaximumAirFlowRate(double maximumAirFlowRate);
      void resetMaximumAirFlowRate();
      bool isMaximumAirFlowRateAutosized() const;
      void autosizeMaximumAirFlowRate();

      boost::optional<double> maximumHotWaterorSteamFlowRate() const;
      bool setMaximumHotWaterorSteamFlowRate(double maximumHotWaterorSteamFlowRate);
      void resetMaximumHotWaterorSteamFlowRate();
      bool isMaximumHotWaterorSteamFlowRateAutosized() const;
      void autosizeMaximumHotWaterorSteamFlowRate();

      double minimumHotWaterorSteamFlowRate() const;
      bool setMinimumHotWaterorSteamFlowRate(double minimumHotWaterorSteamFlowRate);
      void resetMinimumHotWaterorSteamFlowRate();
      bool isMinimumHotWaterorSteamFlowRateDefaulted() const;

      double convergenceTolerance() const;
      bool setConvergenceTolerance(double convergenceTolerance);
      void resetConvergenceTolerance();
      bool isConvergenceToleranceDefaulted() const;

      double maximumReheatAirTemperature() const;
      bool setMaximumReheatAirTemperature(double maximumReheatAirTemperature);
      void resetMaximumReheatAirTemperature();
      bool isMaximumReheatAirTemperatureDefaulted() const;
    };

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
