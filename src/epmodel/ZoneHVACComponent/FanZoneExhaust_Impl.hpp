/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_FANZONEEXHAUST_IMPL_HPP
#define EPMODEL_FANZONEEXHAUST_IMPL_HPP

#include "ZoneHVACComponent_Impl.hpp"

#include <string>
#include <vector>

namespace openstudio {
namespace epmodel {

  namespace detail {

    class EPMODEL_API FanZoneExhaust_Impl : public ZoneHVACComponent_Impl
    {
     public:
      using ZoneHVACComponent_Impl::ZoneHVACComponent_Impl;
      virtual ~FanZoneExhaust_Impl() override = default;

      std::vector<std::string> systemAvailabilityManagerCouplingModeValues() const;

      double fanTotalEfficiency() const;
      bool setFanTotalEfficiency(double fanTotalEfficiency);

      double pressureRise() const;
      bool setPressureRise(double pressureRise);

      boost::optional<double> maximumFlowRate() const;
      bool setMaximumFlowRate(double maximumFlowRate);
      void resetMaximumFlowRate();

      std::string endUseSubcategory() const;
      bool setEndUseSubcategory(const std::string& endUseSubcategory);

      std::string systemAvailabilityManagerCouplingMode() const;
      bool setSystemAvailabilityManagerCouplingMode(const std::string& systemAvailabilityManagerCouplingMode);
    };

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
