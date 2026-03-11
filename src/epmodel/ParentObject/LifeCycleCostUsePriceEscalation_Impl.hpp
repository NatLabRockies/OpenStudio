/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_LIFECYCLECOSTUSEPRICEESCALATION_IMPL_HPP
#define EPMODEL_LIFECYCLECOSTUSEPRICEESCALATION_IMPL_HPP

#include "ParentObject/ParentObject_Impl.hpp"

#include <vector>

namespace openstudio {
namespace epmodel {

namespace detail {

class EPMODEL_API LifeCycleCostUsePriceEscalation_Impl : public ParentObject_Impl
{
 public:
  using ParentObject_Impl::ParentObject_Impl;
  virtual ~LifeCycleCostUsePriceEscalation_Impl() override = default;

  std::string resource() const;
  bool setResource(const std::string& resource);

  boost::optional<int> escalationStartYear() const;
  bool setEscalationStartYear(int escalationStartYear);
  void resetEscalationStartYear();

  std::string escalationStartMonth() const;
  bool isEscalationStartMonthDefaulted() const;
  bool setEscalationStartMonth(const std::string& escalationStartMonth);
  void resetEscalationStartMonth();

  std::vector<std::string> resourceValues() const;
  std::vector<std::string> escalationStartMonthValues() const;
};

}  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
