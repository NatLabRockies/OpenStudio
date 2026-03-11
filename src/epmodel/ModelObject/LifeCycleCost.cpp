/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "LifeCycleCost.hpp"
#include "LifeCycleCost_Impl.hpp"

#include "Model.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/idd/IddEnums.hxx>
#include <utilities/idd/IddFactory.hxx>
#include <utilities/idd/IddObject.hpp>
#include <utilities/idd/LifeCycleCost_RecurringCosts_FieldEnums.hxx>

namespace openstudio {
namespace epmodel {

LifeCycleCost::LifeCycleCost(const Model& model) : ModelObject(LifeCycleCost::iddObjectType(), model) {}

LifeCycleCost::LifeCycleCost(std::shared_ptr<detail::LifeCycleCost_Impl> impl) : ModelObject(std::move(impl)) {}

IddObjectType LifeCycleCost::iddObjectType() {
  return IddObjectType::LifeCycleCost_RecurringCosts;
}

std::vector<std::string> LifeCycleCost::validCategoryValues() {
  return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(), openstudio::LifeCycleCost_RecurringCostsFields::Category);
}

std::vector<std::string> LifeCycleCost::validStartOfCostsValues() {
  return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(), openstudio::LifeCycleCost_RecurringCostsFields::StartofCosts);
}

std::string LifeCycleCost::category() const {
  return getImpl<detail::LifeCycleCost_Impl>()->category();
}

double LifeCycleCost::cost() const {
  return getImpl<detail::LifeCycleCost_Impl>()->cost();
}

std::string LifeCycleCost::startOfCosts() const {
  return getImpl<detail::LifeCycleCost_Impl>()->startOfCosts();
}

bool LifeCycleCost::isStartOfCostsDefaulted() const {
  return getImpl<detail::LifeCycleCost_Impl>()->isStartOfCostsDefaulted();
}

int LifeCycleCost::yearsFromStart() const {
  return getImpl<detail::LifeCycleCost_Impl>()->yearsFromStart();
}

bool LifeCycleCost::isYearsFromStartDefaulted() const {
  return getImpl<detail::LifeCycleCost_Impl>()->isYearsFromStartDefaulted();
}

int LifeCycleCost::monthsFromStart() const {
  return getImpl<detail::LifeCycleCost_Impl>()->monthsFromStart();
}

bool LifeCycleCost::isMonthsFromStartDefaulted() const {
  return getImpl<detail::LifeCycleCost_Impl>()->isMonthsFromStartDefaulted();
}

int LifeCycleCost::repeatPeriodYears() const {
  return getImpl<detail::LifeCycleCost_Impl>()->repeatPeriodYears();
}

bool LifeCycleCost::isRepeatPeriodYearsDefaulted() const {
  return getImpl<detail::LifeCycleCost_Impl>()->isRepeatPeriodYearsDefaulted();
}

int LifeCycleCost::repeatPeriodMonths() const {
  return getImpl<detail::LifeCycleCost_Impl>()->repeatPeriodMonths();
}

bool LifeCycleCost::isRepeatPeriodMonthsDefaulted() const {
  return getImpl<detail::LifeCycleCost_Impl>()->isRepeatPeriodMonthsDefaulted();
}

bool LifeCycleCost::setCategory(const std::string& category) {
  return getImpl<detail::LifeCycleCost_Impl>()->setCategory(category);
}

bool LifeCycleCost::setCost(double cost) {
  return getImpl<detail::LifeCycleCost_Impl>()->setCost(cost);
}

bool LifeCycleCost::setStartOfCosts(const std::string& startOfCosts) {
  return getImpl<detail::LifeCycleCost_Impl>()->setStartOfCosts(startOfCosts);
}

void LifeCycleCost::resetStartOfCosts() {
  getImpl<detail::LifeCycleCost_Impl>()->resetStartOfCosts();
}

bool LifeCycleCost::setYearsFromStart(int yearsFromStart) {
  return getImpl<detail::LifeCycleCost_Impl>()->setYearsFromStart(yearsFromStart);
}

void LifeCycleCost::resetYearsFromStart() {
  getImpl<detail::LifeCycleCost_Impl>()->resetYearsFromStart();
}

bool LifeCycleCost::setMonthsFromStart(int monthsFromStart) {
  return getImpl<detail::LifeCycleCost_Impl>()->setMonthsFromStart(monthsFromStart);
}

void LifeCycleCost::resetMonthsFromStart() {
  getImpl<detail::LifeCycleCost_Impl>()->resetMonthsFromStart();
}

bool LifeCycleCost::setRepeatPeriodYears(int repeatPeriodYears) {
  return getImpl<detail::LifeCycleCost_Impl>()->setRepeatPeriodYears(repeatPeriodYears);
}

void LifeCycleCost::resetRepeatPeriodYears() {
  getImpl<detail::LifeCycleCost_Impl>()->resetRepeatPeriodYears();
}

bool LifeCycleCost::setRepeatPeriodMonths(int repeatPeriodMonths) {
  return getImpl<detail::LifeCycleCost_Impl>()->setRepeatPeriodMonths(repeatPeriodMonths);
}

void LifeCycleCost::resetRepeatPeriodMonths() {
  getImpl<detail::LifeCycleCost_Impl>()->resetRepeatPeriodMonths();
}

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
namespace detail {

std::string LifeCycleCost_Impl::category() const {
  const auto value = getString(openstudio::LifeCycleCost_RecurringCostsFields::Category, true);
  OS_ASSERT(value);
  return *value;
}

double LifeCycleCost_Impl::cost() const {
  const auto value = getDouble(openstudio::LifeCycleCost_RecurringCostsFields::Cost, true);
  OS_ASSERT(value);
  return *value;
}

std::string LifeCycleCost_Impl::startOfCosts() const {
  const auto value = getString(openstudio::LifeCycleCost_RecurringCostsFields::StartofCosts, true);
  OS_ASSERT(value);
  return *value;
}

bool LifeCycleCost_Impl::isStartOfCostsDefaulted() const {
  return isEmpty(openstudio::LifeCycleCost_RecurringCostsFields::StartofCosts);
}

int LifeCycleCost_Impl::yearsFromStart() const {
  return getInt(openstudio::LifeCycleCost_RecurringCostsFields::YearsfromStart, false).value_or(0);
}

bool LifeCycleCost_Impl::isYearsFromStartDefaulted() const {
  return isEmpty(openstudio::LifeCycleCost_RecurringCostsFields::YearsfromStart);
}

int LifeCycleCost_Impl::monthsFromStart() const {
  return getInt(openstudio::LifeCycleCost_RecurringCostsFields::MonthsfromStart, false).value_or(0);
}

bool LifeCycleCost_Impl::isMonthsFromStartDefaulted() const {
  return isEmpty(openstudio::LifeCycleCost_RecurringCostsFields::MonthsfromStart);
}

int LifeCycleCost_Impl::repeatPeriodYears() const {
  const auto value = getInt(openstudio::LifeCycleCost_RecurringCostsFields::RepeatPeriodYears, true);
  OS_ASSERT(value);
  return *value;
}

bool LifeCycleCost_Impl::isRepeatPeriodYearsDefaulted() const {
  return isEmpty(openstudio::LifeCycleCost_RecurringCostsFields::RepeatPeriodYears);
}

int LifeCycleCost_Impl::repeatPeriodMonths() const {
  const auto value = getInt(openstudio::LifeCycleCost_RecurringCostsFields::RepeatPeriodMonths, true);
  OS_ASSERT(value);
  return *value;
}

bool LifeCycleCost_Impl::isRepeatPeriodMonthsDefaulted() const {
  return isEmpty(openstudio::LifeCycleCost_RecurringCostsFields::RepeatPeriodMonths);
}

bool LifeCycleCost_Impl::setCategory(const std::string& category) {
  return setString(openstudio::LifeCycleCost_RecurringCostsFields::Category, category);
}

bool LifeCycleCost_Impl::setCost(double cost) {
  return setDouble(openstudio::LifeCycleCost_RecurringCostsFields::Cost, cost);
}

bool LifeCycleCost_Impl::setStartOfCosts(const std::string& startOfCosts) {
  return setString(openstudio::LifeCycleCost_RecurringCostsFields::StartofCosts, startOfCosts);
}

void LifeCycleCost_Impl::resetStartOfCosts() {
  OS_ASSERT(setString(openstudio::LifeCycleCost_RecurringCostsFields::StartofCosts, ""));
}

bool LifeCycleCost_Impl::setYearsFromStart(int yearsFromStart) {
  return setInt(openstudio::LifeCycleCost_RecurringCostsFields::YearsfromStart, yearsFromStart);
}

void LifeCycleCost_Impl::resetYearsFromStart() {
  OS_ASSERT(setString(openstudio::LifeCycleCost_RecurringCostsFields::YearsfromStart, ""));
}

bool LifeCycleCost_Impl::setMonthsFromStart(int monthsFromStart) {
  return setInt(openstudio::LifeCycleCost_RecurringCostsFields::MonthsfromStart, monthsFromStart);
}

void LifeCycleCost_Impl::resetMonthsFromStart() {
  OS_ASSERT(setString(openstudio::LifeCycleCost_RecurringCostsFields::MonthsfromStart, ""));
}

bool LifeCycleCost_Impl::setRepeatPeriodYears(int repeatPeriodYears) {
  return setInt(openstudio::LifeCycleCost_RecurringCostsFields::RepeatPeriodYears, repeatPeriodYears);
}

void LifeCycleCost_Impl::resetRepeatPeriodYears() {
  OS_ASSERT(setString(openstudio::LifeCycleCost_RecurringCostsFields::RepeatPeriodYears, ""));
}

bool LifeCycleCost_Impl::setRepeatPeriodMonths(int repeatPeriodMonths) {
  return setInt(openstudio::LifeCycleCost_RecurringCostsFields::RepeatPeriodMonths, repeatPeriodMonths);
}

void LifeCycleCost_Impl::resetRepeatPeriodMonths() {
  OS_ASSERT(setString(openstudio::LifeCycleCost_RecurringCostsFields::RepeatPeriodMonths, ""));
}

std::vector<std::string> LifeCycleCost_Impl::validCategoryValues() const {
  return openstudio::epmodel::LifeCycleCost::validCategoryValues();
}

std::vector<std::string> LifeCycleCost_Impl::validStartOfCostsValues() const {
  return openstudio::epmodel::LifeCycleCost::validStartOfCostsValues();
}

}  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
