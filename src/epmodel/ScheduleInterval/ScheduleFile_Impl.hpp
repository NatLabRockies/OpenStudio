/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_SCHEDULEFILE_IMPL_HPP
#define EPMODEL_SCHEDULEFILE_IMPL_HPP

#include "ModelObject/ModelObject_Impl.hpp"

#include <vector>

namespace openstudio {
namespace epmodel {
namespace detail {

class EPMODEL_API ScheduleFile_Impl : public ModelObject_Impl
{
 public:
  using ModelObject_Impl::ModelObject_Impl;
  virtual ~ScheduleFile_Impl() override = default;

  int columnNumber() const;
  int rowstoSkipatTop() const;
  boost::optional<int> numberofHoursofData() const;
  bool isNumberofHoursofDataDefaulted() const;
  std::string columnSeparator() const;
  bool isColumnSeparatorDefaulted() const;
  bool interpolatetoTimestep() const;
  bool isInterpolatetoTimestepDefaulted() const;
  boost::optional<std::string> minutesperItem() const;
  bool isMinutesperItemDefaulted() const;
  bool adjustScheduleforDaylightSavings() const;
  bool isAdjustScheduleforDaylightSavingsDefaulted() const;

  bool setColumnNumber(int columnNumber);
  bool setRowstoSkipatTop(int rowstoSkipatTop);
  bool setNumberofHoursofData(int numberofHours);
  bool setColumnSeparator(const std::string& columnSeparator);
  void resetColumnSeparator();
  bool setInterpolatetoTimestep(bool interpolatetoTimestep);
  void resetInterpolatetoTimestep();
  bool setMinutesperItem(int minutesperItem);
  void resetMinutesperItem();
  bool setAdjustScheduleforDaylightSavings(bool adjustScheduleforDaylightSavings);
  void resetAdjustScheduleforDaylightSavings();

  std::vector<std::string> columnSeparatorValues() const;
  std::vector<std::string> minutesperItemValues() const;
};

}  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
