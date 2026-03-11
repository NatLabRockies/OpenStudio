/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_RUNPERIODCONTROLSPECIALDAYS_IMPL_HPP
#define EPMODEL_RUNPERIODCONTROLSPECIALDAYS_IMPL_HPP

#include "ModelObject_Impl.hpp"

#include <vector>

namespace openstudio {
namespace epmodel {

namespace detail {

class EPMODEL_API RunPeriodControlSpecialDays_Impl : public ModelObject_Impl
{
 public:
  using ModelObject_Impl::ModelObject_Impl;
  virtual ~RunPeriodControlSpecialDays_Impl() override = default;

  std::string startDate() const;
  unsigned duration() const;
  std::string specialDayType() const;

  bool setStartDate(const std::string& startDate);
  bool setDuration(unsigned duration);
  bool setSpecialDayType(const std::string& specialDayType);

  std::vector<std::string> specialDayTypeValues() const;
  std::vector<std::string> validSpecialDayTypeValues() const;
};

}  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
