/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_AIRTERMINALSINGLEDUCTVAVNOREHEAT_IMPL_HPP
#define EPMODEL_AIRTERMINALSINGLEDUCTVAVNOREHEAT_IMPL_HPP

#include "StraightComponent/StraightComponent_Impl.hpp"
#include "ModelObject/ZoneHVACAirDistributionUnit.hpp"
#include "Node.hpp"

#include <vector>

namespace openstudio {
namespace epmodel {
  class Schedule;
  namespace detail {

    class EPMODEL_API AirTerminalSingleDuctVAVNoReheat_Impl : public StraightComponent_Impl
    {
     public:
      enum class AddToNodeFailureStage
      {
        None,
        AfterADUUpdateBeforeZoneRegistration,
      };

      using StraightComponent_Impl::StraightComponent_Impl;
      virtual ~AirTerminalSingleDuctVAVNoReheat_Impl() override = default;

      unsigned inletPort() const override;
      unsigned outletPort() const override;
      bool removeFromLoop() override;
      boost::optional<ZoneHVACAirDistributionUnit> zoneHVACAirDistributionUnit() const;
      bool addToNode(Node& node) override;
      bool addToNode(Node& node, AddToNodeFailureStage failureStage);

      std::vector<std::string> zoneMinimumAirFlowInputMethodValues() const;

      Schedule availabilitySchedule() const;
      bool setAvailabilitySchedule(Schedule& schedule);

      boost::optional<Schedule> minimumAirFlowFractionSchedule() const;
      bool setMinimumAirFlowFractionSchedule(Schedule& schedule);
      void resetMinimumAirFlowFractionSchedule();

      boost::optional<Schedule> minimumAirFlowTurndownSchedule() const;
      bool setMinimumAirFlowTurndownSchedule(Schedule& schedule);
      void resetMinimumAirFlowTurndownSchedule();

      boost::optional<double> maximumAirFlowRate() const;
      bool isMaximumAirFlowRateAutosized() const;
      bool setMaximumAirFlowRate(double maximumAirFlowRate);
      void resetMaximumAirFlowRate();
      void autosizeMaximumAirFlowRate();

      boost::optional<std::string> zoneMinimumAirFlowInputMethod() const;
      bool setZoneMinimumAirFlowInputMethod(const std::string& zoneMinimumAirFlowInputMethod);
      void resetZoneMinimumAirFlowInputMethod();

      boost::optional<double> constantMinimumAirFlowFraction() const;
      bool isConstantMinimumAirFlowFractionAutosized() const;
      bool isConstantMinimumAirFlowFractionDefaulted() const;
      bool setConstantMinimumAirFlowFraction(double constantMinimumAirFlowFraction);
      void autosizeConstantMinimumAirFlowFraction();
      void resetConstantMinimumAirFlowFraction();

      boost::optional<double> fixedMinimumAirFlowRate() const;
      bool isFixedMinimumAirFlowRateAutosized() const;
      bool isFixedMinimumAirFlowRateDefaulted() const;
      bool setFixedMinimumAirFlowRate(double fixedMinimumAirFlowRate);
      void autosizeFixedMinimumAirFlowRate();
      void resetFixedMinimumAirFlowRate();
    };

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
