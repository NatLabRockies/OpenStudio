/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_FANZONEEXHAUST_IMPL_HPP
#define EPMODEL_FANZONEEXHAUST_IMPL_HPP

#include "ModelObject_Impl.hpp"

#include <string>
#include <vector>

namespace openstudio {
namespace epmodel {

namespace detail {

class EPMODEL_API FanZoneExhaust_Impl : public ModelObject_Impl
{
 public:
  using ModelObject_Impl::ModelObject_Impl;
  virtual ~FanZoneExhaust_Impl() override = default;

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

  std::vector<std::string> systemAvailabilityManagerCouplingModeValues() const;
};

}  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
