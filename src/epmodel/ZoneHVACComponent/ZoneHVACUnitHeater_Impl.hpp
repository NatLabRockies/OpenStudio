/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_ZONEHVACUNITHEATER_IMPL_HPP
#define EPMODEL_ZONEHVACUNITHEATER_IMPL_HPP

#include "ZoneHVACComponent_Impl.hpp"

#include <boost/optional.hpp>
#include <string>
#include <vector>

namespace openstudio {
namespace epmodel {

  class ModelObject;

  namespace detail {

    class EPMODEL_API ZoneHVACUnitHeater_Impl : public ZoneHVACComponent_Impl
    {
     public:
      using ZoneHVACComponent_Impl::ZoneHVACComponent_Impl;
      virtual ~ZoneHVACUnitHeater_Impl() override = default;

      std::vector<ModelObject> children() const override;
      unsigned inletPort() const override;
      unsigned outletPort() const override;

      boost::optional<double> maximumSupplyAirFlowRate() const;
      bool isMaximumSupplyAirFlowRateAutosized() const;
      bool setMaximumSupplyAirFlowRate(double maximumSupplyAirFlowRate);
      void autosizeMaximumSupplyAirFlowRate();
      boost::optional<double> autosizedMaximumSupplyAirFlowRate() const;

      std::string fanControlType() const;
      bool setFanControlType(const std::string& fanControlType);

      boost::optional<double> maximumHotWaterFlowRate() const;
      bool isMaximumHotWaterFlowRateAutosized() const;
      bool setMaximumHotWaterFlowRate(double maximumHotWaterFlowRate);
      void resetMaximumHotWaterFlowRate();
      void autosizeMaximumHotWaterFlowRate();
      boost::optional<double> autosizedMaximumHotWaterFlowRate() const;

      double minimumHotWaterFlowRate() const;
      bool isMinimumHotWaterFlowRateDefaulted() const;
      bool setMinimumHotWaterFlowRate(double minimumHotWaterFlowRate);
      void resetMinimumHotWaterFlowRate();

      double heatingConvergenceTolerance() const;
      bool isHeatingConvergenceToleranceDefaulted() const;
      bool setHeatingConvergenceTolerance(double heatingConvergenceTolerance);
      void resetHeatingConvergenceTolerance();
    };

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
