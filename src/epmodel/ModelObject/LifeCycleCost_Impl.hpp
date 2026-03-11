/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_LIFECYCLECOST_IMPL_HPP
#define EPMODEL_LIFECYCLECOST_IMPL_HPP

#include "ModelObject_Impl.hpp"

#include <vector>

namespace openstudio {
namespace epmodel {

namespace detail {

class EPMODEL_API LifeCycleCost_Impl : public ModelObject_Impl
{
 public:
  using ModelObject_Impl::ModelObject_Impl;
  virtual ~LifeCycleCost_Impl() override = default;

  std::string category() const;
  double cost() const;
  std::string startOfCosts() const;
  bool isStartOfCostsDefaulted() const;
  int yearsFromStart() const;
  bool isYearsFromStartDefaulted() const;
  int monthsFromStart() const;
  bool isMonthsFromStartDefaulted() const;
  int repeatPeriodYears() const;
  bool isRepeatPeriodYearsDefaulted() const;
  int repeatPeriodMonths() const;
  bool isRepeatPeriodMonthsDefaulted() const;

  bool setCategory(const std::string& category);
  bool setCost(double cost);
  bool setStartOfCosts(const std::string& startOfCosts);
  void resetStartOfCosts();
  bool setYearsFromStart(int yearsFromStart);
  void resetYearsFromStart();
  bool setMonthsFromStart(int monthsFromStart);
  void resetMonthsFromStart();
  bool setRepeatPeriodYears(int repeatPeriodYears);
  void resetRepeatPeriodYears();
  bool setRepeatPeriodMonths(int repeatPeriodMonths);
  void resetRepeatPeriodMonths();

  std::vector<std::string> validCategoryValues() const;
  std::vector<std::string> validStartOfCostsValues() const;
};

}  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
