/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_ZONEHVACUNITVENTILATOR_IMPL_HPP
#define EPMODEL_ZONEHVACUNITVENTILATOR_IMPL_HPP

#include "ZoneHVACComponent_Impl.hpp"

#include <boost/optional.hpp>
#include <string>

namespace openstudio {
namespace epmodel {

  namespace detail {

    class EPMODEL_API ZoneHVACUnitVentilator_Impl : public ZoneHVACComponent_Impl
    {
     public:
      using ZoneHVACComponent_Impl::ZoneHVACComponent_Impl;
      virtual ~ZoneHVACUnitVentilator_Impl() override = default;

      boost::optional<double> maximumSupplyAirFlowRate() const;
      bool isMaximumSupplyAirFlowRateAutosized() const;
      bool setMaximumSupplyAirFlowRate(double maximumSupplyAirFlowRate);
      void autosizeMaximumSupplyAirFlowRate();
      boost::optional<double> autosizedMaximumSupplyAirFlowRate() const;

      std::string outdoorAirControlType() const;
      bool setOutdoorAirControlType(const std::string& outdoorAirControlType);

      boost::optional<double> minimumOutdoorAirFlowRate() const;
      bool isMinimumOutdoorAirFlowRateAutosized() const;
      bool setMinimumOutdoorAirFlowRate(double minimumOutdoorAirFlowRate);
      void autosizeMinimumOutdoorAirFlowRate();
      boost::optional<double> autosizedMinimumOutdoorAirFlowRate() const;

      boost::optional<double> maximumOutdoorAirFlowRate() const;
      bool isMaximumOutdoorAirFlowRateAutosized() const;
      bool setMaximumOutdoorAirFlowRate(double maximumOutdoorAirFlowRate);
      void autosizeMaximumOutdoorAirFlowRate();
      boost::optional<double> autosizedMaximumOutdoorAirFlowRate() const;
      double heatingConvergenceTolerance() const;
      bool setHeatingConvergenceTolerance(double heatingConvergenceTolerance);

      double coolingConvergenceTolerance() const;
      bool setCoolingConvergenceTolerance(double coolingConvergenceTolerance);

      std::vector<ModelObject> children() const;

      unsigned inletPort() const override;
      unsigned outletPort() const override;
    };

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif  // EPMODEL_ZONEHVACUNITVENTILATOR_IMPL_HPP
