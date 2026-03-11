/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_DEMANDMANAGERASSIGNMENTLIST_IMPL_HPP
#define EPMODEL_DEMANDMANAGERASSIGNMENTLIST_IMPL_HPP

#include "ModelObject_Impl.hpp"

#include <vector>

namespace openstudio {
namespace epmodel {

namespace detail {

class EPMODEL_API DemandManagerAssignmentList_Impl : public ModelObject_Impl
{
 public:
  using ModelObject_Impl::ModelObject_Impl;
  virtual ~DemandManagerAssignmentList_Impl() override = default;

  std::string meterName() const;
  bool setMeterName(const std::string& meterName);

  double demandLimitSafetyFraction() const;
  bool setDemandLimitSafetyFraction(double demandLimitSafetyFraction);

  int demandWindowLength() const;
  bool setDemandWindowLength(int demandWindowLength);

  std::string demandManagerPriority() const;
  bool setDemandManagerPriority(const std::string& demandManagerPriority);

  std::vector<std::string> demandManagerPriorityValues() const;
};

}  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
