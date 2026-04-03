/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_AIRTERMINALSINGLEDUCTCONSTANTVOLUMENOREHEAT_IMPL_HPP
#define EPMODEL_AIRTERMINALSINGLEDUCTCONSTANTVOLUMENOREHEAT_IMPL_HPP

#include "StraightComponent/StraightComponent_Impl.hpp"
#include "Node.hpp"
#include "ModelObject/ZoneHVACAirDistributionUnit.hpp"

namespace openstudio {
namespace epmodel {
  class Schedule;
  namespace detail {

    class EPMODEL_API AirTerminalSingleDuctConstantVolumeNoReheat_Impl : public StraightComponent_Impl
    {
     public:
      using StraightComponent_Impl::StraightComponent_Impl;
      virtual ~AirTerminalSingleDuctConstantVolumeNoReheat_Impl() override = default;

      unsigned inletPort() const override;
      unsigned outletPort() const override;
      boost::optional<openstudio::epmodel::AirLoopHVAC> airLoopHVAC() const override;

      boost::optional<ZoneHVACAirDistributionUnit> zoneHVACAirDistributionUnit() const;
      bool addToNode(Node& node);

      Schedule availabilitySchedule() const;
      bool setAvailabilitySchedule(Schedule& schedule);

      /** @name Maximum air flow rate */
      //@{
      boost::optional<double> maximumAirFlowRate() const;
      bool isMaximumAirFlowRateAutosized() const;
      bool setMaximumAirFlowRate(double maximumAirFlowRate);
      void autosizeMaximumAirFlowRate();
      //@}
    };

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
