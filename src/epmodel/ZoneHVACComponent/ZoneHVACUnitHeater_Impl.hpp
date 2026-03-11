/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_ZONEHVACUNITHEATER_IMPL_HPP
#define EPMODEL_ZONEHVACUNITHEATER_IMPL_HPP

#include "ModelObject_Impl.hpp"

#include <boost/optional.hpp>
#include <string>

namespace openstudio {
namespace epmodel {

  namespace detail {

    class EPMODEL_API ZoneHVACUnitHeater_Impl : public ModelObject_Impl
    {
     public:
      using ModelObject_Impl::ModelObject_Impl;
      virtual ~ZoneHVACUnitHeater_Impl() override = default;

      boost::optional<double> maximumSupplyAirFlowRate() const;
      bool isMaximumSupplyAirFlowRateAutosized() const;
      bool setMaximumSupplyAirFlowRate(double maximumSupplyAirFlowRate);
      void autosizeMaximumSupplyAirFlowRate();

      std::string fanControlType() const;
      bool setFanControlType(const std::string& fanControlType);

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

      boost::optional<double> autosizedMaximumSupplyAirFlowRate() const;
      boost::optional<double> autosizedMaximumHotWaterFlowRate() const;
    };

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
