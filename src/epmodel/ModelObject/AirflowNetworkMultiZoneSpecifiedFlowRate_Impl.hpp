/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_AIRFLOWNETWORKMULTIZONESPECIFIEDFLOWRATE_IMPL_HPP
#define EPMODEL_AIRFLOWNETWORKMULTIZONESPECIFIEDFLOWRATE_IMPL_HPP

#include "ModelObject_Impl.hpp"

#include <vector>

namespace openstudio {
namespace epmodel {

namespace detail {

class EPMODEL_API AirflowNetworkMultiZoneSpecifiedFlowRate_Impl : public ModelObject_Impl
{
 public:
  using ModelObject_Impl::ModelObject_Impl;
  virtual ~AirflowNetworkMultiZoneSpecifiedFlowRate_Impl() override = default;

  double airFlowValue() const;
  bool setAirFlowValue(double airFlowValue);

  std::string airFlowUnits() const;
  bool setAirFlowUnits(const std::string& airFlowUnits);
  bool isAirFlowUnitsDefaulted() const;
  void resetAirFlowUnits();

  std::vector<std::string> airFlowUnitsValues() const;
};

}  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
