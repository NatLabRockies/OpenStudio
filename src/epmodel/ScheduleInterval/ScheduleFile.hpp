/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_SCHEDULEFILE_HPP
#define EPMODEL_SCHEDULEFILE_HPP

#include "EPModelAPI.hpp"
#include "ModelObject/ModelObject.hpp"

#include <utilities/idd/IddEnums.hxx>

#include <memory>
#include <vector>

namespace openstudio {
namespace epmodel {

class Model;

namespace detail {
class ScheduleFile_Impl;
}

class EPMODEL_API ScheduleFile : public ModelObject
{
 public:
  explicit ScheduleFile(const Model& model);

  virtual ~ScheduleFile() override = default;
  ScheduleFile(const ScheduleFile& other) = default;
  ScheduleFile(ScheduleFile&& other) = default;
  ScheduleFile& operator=(const ScheduleFile&) = default;
  ScheduleFile& operator=(ScheduleFile&&) = default;

  static IddObjectType iddObjectType();

  static std::vector<std::string> columnSeparatorValues();
  static std::vector<std::string> minutesperItemValues();

  // Schema Alignment Notes:
  // - API: Preserve openstudio::model::ScheduleFile scalar accessor names/signatures where fields map to E+ Schedule:File.
  // - Field Mapping: columnNumber, rowstoSkipatTop, numberofHoursofData, columnSeparator, interpolatetoTimestep,
  //   minutesperItem, and adjustScheduleforDaylightSavings map directly to EnergyPlus Schedule:File scalar fields.
  // - ForwardTranslator evidence: ForwardTranslateScheduleFile.cpp writes these preserved APIs directly to Schedule:File fields.
  // - Field Mapping: ScheduleTypeLimitsName and FileName are intentionally excluded in this scalar-only pass
  //   (relationship/file-path behavior is handled separately from scalar accessors).
  // - TODO(parity): Add relationship and path-translation parity APIs incrementally after scalar scaffold saturation.
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
  bool setMinutesperItem(const std::string& minutesperItem);
  bool setMinutesperItem(int minutesperItem);
  void resetMinutesperItem();
  bool setAdjustScheduleforDaylightSavings(bool adjustScheduleforDaylightSavings);
  void resetAdjustScheduleforDaylightSavings();

 protected:
  using ImplType = detail::ScheduleFile_Impl;

  friend class Model;
  friend class openstudio::IdfObject;
  friend class openstudio::detail::IdfObject_Impl;

  explicit ScheduleFile(std::shared_ptr<detail::ScheduleFile_Impl> impl);
};

}  // namespace epmodel
}  // namespace openstudio

#endif
