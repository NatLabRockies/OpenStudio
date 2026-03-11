/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "ScheduleInterval/ScheduleFile.hpp"
#include "ScheduleInterval/ScheduleFile_Impl.hpp"

#include "Model.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/idd/IddEnums.hxx>
#include <utilities/idd/IddFactory.hxx>
#include <utilities/idd/IddObject.hpp>
#include <utilities/idd/Schedule_File_FieldEnums.hxx>

namespace openstudio {
namespace epmodel {

ScheduleFile::ScheduleFile(const Model& model) : ModelObject(ScheduleFile::iddObjectType(), model) {
  // Mirror preserved counterpart constructor behavior for required scalar fields.
  bool ok = true;
  ok &= setColumnNumber(1);
  ok &= setRowstoSkipatTop(0);
  OS_ASSERT(ok);
}

ScheduleFile::ScheduleFile(std::shared_ptr<detail::ScheduleFile_Impl> impl) : ModelObject(std::move(impl)) {}

IddObjectType ScheduleFile::iddObjectType() {
  return IddObjectType::Schedule_File;
}

std::vector<std::string> ScheduleFile::columnSeparatorValues() {
  return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(), openstudio::Schedule_FileFields::ColumnSeparator);
}

std::vector<std::string> ScheduleFile::minutesperItemValues() {
  return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(), openstudio::Schedule_FileFields::MinutesperItem);
}

int ScheduleFile::columnNumber() const {
  return getImpl<detail::ScheduleFile_Impl>()->columnNumber();
}

int ScheduleFile::rowstoSkipatTop() const {
  return getImpl<detail::ScheduleFile_Impl>()->rowstoSkipatTop();
}

boost::optional<int> ScheduleFile::numberofHoursofData() const {
  return getImpl<detail::ScheduleFile_Impl>()->numberofHoursofData();
}

bool ScheduleFile::isNumberofHoursofDataDefaulted() const {
  return getImpl<detail::ScheduleFile_Impl>()->isNumberofHoursofDataDefaulted();
}

std::string ScheduleFile::columnSeparator() const {
  return getImpl<detail::ScheduleFile_Impl>()->columnSeparator();
}

bool ScheduleFile::isColumnSeparatorDefaulted() const {
  return getImpl<detail::ScheduleFile_Impl>()->isColumnSeparatorDefaulted();
}

bool ScheduleFile::interpolatetoTimestep() const {
  return getImpl<detail::ScheduleFile_Impl>()->interpolatetoTimestep();
}

bool ScheduleFile::isInterpolatetoTimestepDefaulted() const {
  return getImpl<detail::ScheduleFile_Impl>()->isInterpolatetoTimestepDefaulted();
}

boost::optional<std::string> ScheduleFile::minutesperItem() const {
  return getImpl<detail::ScheduleFile_Impl>()->minutesperItem();
}

bool ScheduleFile::isMinutesperItemDefaulted() const {
  return getImpl<detail::ScheduleFile_Impl>()->isMinutesperItemDefaulted();
}

bool ScheduleFile::adjustScheduleforDaylightSavings() const {
  return getImpl<detail::ScheduleFile_Impl>()->adjustScheduleforDaylightSavings();
}

bool ScheduleFile::isAdjustScheduleforDaylightSavingsDefaulted() const {
  return getImpl<detail::ScheduleFile_Impl>()->isAdjustScheduleforDaylightSavingsDefaulted();
}

bool ScheduleFile::setColumnNumber(int columnNumber) {
  return getImpl<detail::ScheduleFile_Impl>()->setColumnNumber(columnNumber);
}

bool ScheduleFile::setRowstoSkipatTop(int rowstoSkipatTop) {
  return getImpl<detail::ScheduleFile_Impl>()->setRowstoSkipatTop(rowstoSkipatTop);
}

bool ScheduleFile::setNumberofHoursofData(int numberofHours) {
  return getImpl<detail::ScheduleFile_Impl>()->setNumberofHoursofData(numberofHours);
}

bool ScheduleFile::setColumnSeparator(const std::string& columnSeparator) {
  return getImpl<detail::ScheduleFile_Impl>()->setColumnSeparator(columnSeparator);
}

void ScheduleFile::resetColumnSeparator() {
  getImpl<detail::ScheduleFile_Impl>()->resetColumnSeparator();
}

bool ScheduleFile::setInterpolatetoTimestep(bool interpolatetoTimestep) {
  return getImpl<detail::ScheduleFile_Impl>()->setInterpolatetoTimestep(interpolatetoTimestep);
}

void ScheduleFile::resetInterpolatetoTimestep() {
  getImpl<detail::ScheduleFile_Impl>()->resetInterpolatetoTimestep();
}

bool ScheduleFile::setMinutesperItem(const std::string& minutesperItem) {
  try {
    return getImpl<detail::ScheduleFile_Impl>()->setMinutesperItem(std::stoi(minutesperItem));
  } catch (const std::exception&) {
    return false;
  }
}

bool ScheduleFile::setMinutesperItem(int minutesperItem) {
  return getImpl<detail::ScheduleFile_Impl>()->setMinutesperItem(minutesperItem);
}

void ScheduleFile::resetMinutesperItem() {
  getImpl<detail::ScheduleFile_Impl>()->resetMinutesperItem();
}

bool ScheduleFile::setAdjustScheduleforDaylightSavings(bool adjustScheduleforDaylightSavings) {
  return getImpl<detail::ScheduleFile_Impl>()->setAdjustScheduleforDaylightSavings(adjustScheduleforDaylightSavings);
}

void ScheduleFile::resetAdjustScheduleforDaylightSavings() {
  getImpl<detail::ScheduleFile_Impl>()->resetAdjustScheduleforDaylightSavings();
}

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
namespace detail {

int ScheduleFile_Impl::columnNumber() const {
  const auto value = getInt(openstudio::Schedule_FileFields::ColumnNumber, true);
  OS_ASSERT(value);
  return *value;
}

int ScheduleFile_Impl::rowstoSkipatTop() const {
  const auto value = getInt(openstudio::Schedule_FileFields::RowstoSkipatTop, true);
  OS_ASSERT(value);
  return *value;
}

boost::optional<int> ScheduleFile_Impl::numberofHoursofData() const {
  return getInt(openstudio::Schedule_FileFields::NumberofHoursofData, true);
}

bool ScheduleFile_Impl::isNumberofHoursofDataDefaulted() const {
  return isEmpty(openstudio::Schedule_FileFields::NumberofHoursofData);
}

std::string ScheduleFile_Impl::columnSeparator() const {
  const auto value = getString(openstudio::Schedule_FileFields::ColumnSeparator, true);
  OS_ASSERT(value);
  return *value;
}

bool ScheduleFile_Impl::isColumnSeparatorDefaulted() const {
  return isEmpty(openstudio::Schedule_FileFields::ColumnSeparator);
}

bool ScheduleFile_Impl::interpolatetoTimestep() const {
  const auto value = getString(openstudio::Schedule_FileFields::InterpolatetoTimestep, true);
  OS_ASSERT(value);
  return openstudio::istringEqual(*value, "Yes");
}

bool ScheduleFile_Impl::isInterpolatetoTimestepDefaulted() const {
  return isEmpty(openstudio::Schedule_FileFields::InterpolatetoTimestep);
}

boost::optional<std::string> ScheduleFile_Impl::minutesperItem() const {
  const auto value = getInt(openstudio::Schedule_FileFields::MinutesperItem, true);
  OS_ASSERT(value);
  return std::to_string(*value);
}

bool ScheduleFile_Impl::isMinutesperItemDefaulted() const {
  return isEmpty(openstudio::Schedule_FileFields::MinutesperItem);
}

bool ScheduleFile_Impl::adjustScheduleforDaylightSavings() const {
  const auto value = getString(openstudio::Schedule_FileFields::AdjustScheduleforDaylightSavings, true);
  OS_ASSERT(value);
  return openstudio::istringEqual(*value, "Yes");
}

bool ScheduleFile_Impl::isAdjustScheduleforDaylightSavingsDefaulted() const {
  return isEmpty(openstudio::Schedule_FileFields::AdjustScheduleforDaylightSavings);
}

bool ScheduleFile_Impl::setColumnNumber(int columnNumber) {
  return setInt(openstudio::Schedule_FileFields::ColumnNumber, columnNumber);
}

bool ScheduleFile_Impl::setRowstoSkipatTop(int rowstoSkipatTop) {
  return setInt(openstudio::Schedule_FileFields::RowstoSkipatTop, rowstoSkipatTop);
}

bool ScheduleFile_Impl::setNumberofHoursofData(int numberofHours) {
  return setInt(openstudio::Schedule_FileFields::NumberofHoursofData, numberofHours);
}

bool ScheduleFile_Impl::setColumnSeparator(const std::string& columnSeparator) {
  return setString(openstudio::Schedule_FileFields::ColumnSeparator, columnSeparator);
}

void ScheduleFile_Impl::resetColumnSeparator() {
  OS_ASSERT(setString(openstudio::Schedule_FileFields::ColumnSeparator, ""));
}

bool ScheduleFile_Impl::setInterpolatetoTimestep(bool interpolatetoTimestep) {
  const bool result = setString(openstudio::Schedule_FileFields::InterpolatetoTimestep, interpolatetoTimestep ? "Yes" : "No");
  OS_ASSERT(result);
  return result;
}

void ScheduleFile_Impl::resetInterpolatetoTimestep() {
  OS_ASSERT(setString(openstudio::Schedule_FileFields::InterpolatetoTimestep, ""));
}

bool ScheduleFile_Impl::setMinutesperItem(int minutesperItem) {
  return setInt(openstudio::Schedule_FileFields::MinutesperItem, minutesperItem);
}

void ScheduleFile_Impl::resetMinutesperItem() {
  OS_ASSERT(setString(openstudio::Schedule_FileFields::MinutesperItem, ""));
}

bool ScheduleFile_Impl::setAdjustScheduleforDaylightSavings(bool adjustScheduleforDaylightSavings) {
  const bool result = setString(openstudio::Schedule_FileFields::AdjustScheduleforDaylightSavings,
                                adjustScheduleforDaylightSavings ? "Yes" : "No");
  OS_ASSERT(result);
  return result;
}

void ScheduleFile_Impl::resetAdjustScheduleforDaylightSavings() {
  OS_ASSERT(setString(openstudio::Schedule_FileFields::AdjustScheduleforDaylightSavings, ""));
}

std::vector<std::string> ScheduleFile_Impl::columnSeparatorValues() const {
  return openstudio::epmodel::ScheduleFile::columnSeparatorValues();
}

std::vector<std::string> ScheduleFile_Impl::minutesperItemValues() const {
  return openstudio::epmodel::ScheduleFile::minutesperItemValues();
}

}  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
