/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "ScheduleDayHourly.hpp"
#include "ScheduleDayHourly_Impl.hpp"

#include "Model.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/idd/IddEnums.hxx>
#include <utilities/idd/Schedule_Day_Hourly_FieldEnums.hxx>

namespace openstudio {
namespace epmodel {

ScheduleDayHourly::ScheduleDayHourly(const Model& model) : ModelObject(ScheduleDayHourly::iddObjectType(), model) {}

ScheduleDayHourly::ScheduleDayHourly(std::shared_ptr<detail::ScheduleDayHourly_Impl> impl) : ModelObject(std::move(impl)) {}

IddObjectType ScheduleDayHourly::iddObjectType() {
  return IddObjectType::Schedule_Day_Hourly;
}

double ScheduleDayHourly::hour1() const {
  return getImpl<detail::ScheduleDayHourly_Impl>()->hour1();
}

bool ScheduleDayHourly::isHour1Defaulted() const {
  return getImpl<detail::ScheduleDayHourly_Impl>()->isHour1Defaulted();
}

bool ScheduleDayHourly::setHour1(double hour1) {
  return getImpl<detail::ScheduleDayHourly_Impl>()->setHour1(hour1);
}

void ScheduleDayHourly::resetHour1() {
  getImpl<detail::ScheduleDayHourly_Impl>()->resetHour1();
}

double ScheduleDayHourly::hour2() const {
  return getImpl<detail::ScheduleDayHourly_Impl>()->hour2();
}

bool ScheduleDayHourly::isHour2Defaulted() const {
  return getImpl<detail::ScheduleDayHourly_Impl>()->isHour2Defaulted();
}

bool ScheduleDayHourly::setHour2(double hour2) {
  return getImpl<detail::ScheduleDayHourly_Impl>()->setHour2(hour2);
}

void ScheduleDayHourly::resetHour2() {
  getImpl<detail::ScheduleDayHourly_Impl>()->resetHour2();
}

double ScheduleDayHourly::hour3() const {
  return getImpl<detail::ScheduleDayHourly_Impl>()->hour3();
}

bool ScheduleDayHourly::isHour3Defaulted() const {
  return getImpl<detail::ScheduleDayHourly_Impl>()->isHour3Defaulted();
}

bool ScheduleDayHourly::setHour3(double hour3) {
  return getImpl<detail::ScheduleDayHourly_Impl>()->setHour3(hour3);
}

void ScheduleDayHourly::resetHour3() {
  getImpl<detail::ScheduleDayHourly_Impl>()->resetHour3();
}

double ScheduleDayHourly::hour4() const {
  return getImpl<detail::ScheduleDayHourly_Impl>()->hour4();
}

bool ScheduleDayHourly::isHour4Defaulted() const {
  return getImpl<detail::ScheduleDayHourly_Impl>()->isHour4Defaulted();
}

bool ScheduleDayHourly::setHour4(double hour4) {
  return getImpl<detail::ScheduleDayHourly_Impl>()->setHour4(hour4);
}

void ScheduleDayHourly::resetHour4() {
  getImpl<detail::ScheduleDayHourly_Impl>()->resetHour4();
}

double ScheduleDayHourly::hour5() const {
  return getImpl<detail::ScheduleDayHourly_Impl>()->hour5();
}

bool ScheduleDayHourly::isHour5Defaulted() const {
  return getImpl<detail::ScheduleDayHourly_Impl>()->isHour5Defaulted();
}

bool ScheduleDayHourly::setHour5(double hour5) {
  return getImpl<detail::ScheduleDayHourly_Impl>()->setHour5(hour5);
}

void ScheduleDayHourly::resetHour5() {
  getImpl<detail::ScheduleDayHourly_Impl>()->resetHour5();
}

double ScheduleDayHourly::hour6() const {
  return getImpl<detail::ScheduleDayHourly_Impl>()->hour6();
}

bool ScheduleDayHourly::isHour6Defaulted() const {
  return getImpl<detail::ScheduleDayHourly_Impl>()->isHour6Defaulted();
}

bool ScheduleDayHourly::setHour6(double hour6) {
  return getImpl<detail::ScheduleDayHourly_Impl>()->setHour6(hour6);
}

void ScheduleDayHourly::resetHour6() {
  getImpl<detail::ScheduleDayHourly_Impl>()->resetHour6();
}

double ScheduleDayHourly::hour7() const {
  return getImpl<detail::ScheduleDayHourly_Impl>()->hour7();
}

bool ScheduleDayHourly::isHour7Defaulted() const {
  return getImpl<detail::ScheduleDayHourly_Impl>()->isHour7Defaulted();
}

bool ScheduleDayHourly::setHour7(double hour7) {
  return getImpl<detail::ScheduleDayHourly_Impl>()->setHour7(hour7);
}

void ScheduleDayHourly::resetHour7() {
  getImpl<detail::ScheduleDayHourly_Impl>()->resetHour7();
}

double ScheduleDayHourly::hour8() const {
  return getImpl<detail::ScheduleDayHourly_Impl>()->hour8();
}

bool ScheduleDayHourly::isHour8Defaulted() const {
  return getImpl<detail::ScheduleDayHourly_Impl>()->isHour8Defaulted();
}

bool ScheduleDayHourly::setHour8(double hour8) {
  return getImpl<detail::ScheduleDayHourly_Impl>()->setHour8(hour8);
}

void ScheduleDayHourly::resetHour8() {
  getImpl<detail::ScheduleDayHourly_Impl>()->resetHour8();
}

double ScheduleDayHourly::hour9() const {
  return getImpl<detail::ScheduleDayHourly_Impl>()->hour9();
}

bool ScheduleDayHourly::isHour9Defaulted() const {
  return getImpl<detail::ScheduleDayHourly_Impl>()->isHour9Defaulted();
}

bool ScheduleDayHourly::setHour9(double hour9) {
  return getImpl<detail::ScheduleDayHourly_Impl>()->setHour9(hour9);
}

void ScheduleDayHourly::resetHour9() {
  getImpl<detail::ScheduleDayHourly_Impl>()->resetHour9();
}

double ScheduleDayHourly::hour10() const {
  return getImpl<detail::ScheduleDayHourly_Impl>()->hour10();
}

bool ScheduleDayHourly::isHour10Defaulted() const {
  return getImpl<detail::ScheduleDayHourly_Impl>()->isHour10Defaulted();
}

bool ScheduleDayHourly::setHour10(double hour10) {
  return getImpl<detail::ScheduleDayHourly_Impl>()->setHour10(hour10);
}

void ScheduleDayHourly::resetHour10() {
  getImpl<detail::ScheduleDayHourly_Impl>()->resetHour10();
}

double ScheduleDayHourly::hour11() const {
  return getImpl<detail::ScheduleDayHourly_Impl>()->hour11();
}

bool ScheduleDayHourly::isHour11Defaulted() const {
  return getImpl<detail::ScheduleDayHourly_Impl>()->isHour11Defaulted();
}

bool ScheduleDayHourly::setHour11(double hour11) {
  return getImpl<detail::ScheduleDayHourly_Impl>()->setHour11(hour11);
}

void ScheduleDayHourly::resetHour11() {
  getImpl<detail::ScheduleDayHourly_Impl>()->resetHour11();
}

double ScheduleDayHourly::hour12() const {
  return getImpl<detail::ScheduleDayHourly_Impl>()->hour12();
}

bool ScheduleDayHourly::isHour12Defaulted() const {
  return getImpl<detail::ScheduleDayHourly_Impl>()->isHour12Defaulted();
}

bool ScheduleDayHourly::setHour12(double hour12) {
  return getImpl<detail::ScheduleDayHourly_Impl>()->setHour12(hour12);
}

void ScheduleDayHourly::resetHour12() {
  getImpl<detail::ScheduleDayHourly_Impl>()->resetHour12();
}

double ScheduleDayHourly::hour13() const {
  return getImpl<detail::ScheduleDayHourly_Impl>()->hour13();
}

bool ScheduleDayHourly::isHour13Defaulted() const {
  return getImpl<detail::ScheduleDayHourly_Impl>()->isHour13Defaulted();
}

bool ScheduleDayHourly::setHour13(double hour13) {
  return getImpl<detail::ScheduleDayHourly_Impl>()->setHour13(hour13);
}

void ScheduleDayHourly::resetHour13() {
  getImpl<detail::ScheduleDayHourly_Impl>()->resetHour13();
}

double ScheduleDayHourly::hour14() const {
  return getImpl<detail::ScheduleDayHourly_Impl>()->hour14();
}

bool ScheduleDayHourly::isHour14Defaulted() const {
  return getImpl<detail::ScheduleDayHourly_Impl>()->isHour14Defaulted();
}

bool ScheduleDayHourly::setHour14(double hour14) {
  return getImpl<detail::ScheduleDayHourly_Impl>()->setHour14(hour14);
}

void ScheduleDayHourly::resetHour14() {
  getImpl<detail::ScheduleDayHourly_Impl>()->resetHour14();
}

double ScheduleDayHourly::hour15() const {
  return getImpl<detail::ScheduleDayHourly_Impl>()->hour15();
}

bool ScheduleDayHourly::isHour15Defaulted() const {
  return getImpl<detail::ScheduleDayHourly_Impl>()->isHour15Defaulted();
}

bool ScheduleDayHourly::setHour15(double hour15) {
  return getImpl<detail::ScheduleDayHourly_Impl>()->setHour15(hour15);
}

void ScheduleDayHourly::resetHour15() {
  getImpl<detail::ScheduleDayHourly_Impl>()->resetHour15();
}

double ScheduleDayHourly::hour16() const {
  return getImpl<detail::ScheduleDayHourly_Impl>()->hour16();
}

bool ScheduleDayHourly::isHour16Defaulted() const {
  return getImpl<detail::ScheduleDayHourly_Impl>()->isHour16Defaulted();
}

bool ScheduleDayHourly::setHour16(double hour16) {
  return getImpl<detail::ScheduleDayHourly_Impl>()->setHour16(hour16);
}

void ScheduleDayHourly::resetHour16() {
  getImpl<detail::ScheduleDayHourly_Impl>()->resetHour16();
}

double ScheduleDayHourly::hour17() const {
  return getImpl<detail::ScheduleDayHourly_Impl>()->hour17();
}

bool ScheduleDayHourly::isHour17Defaulted() const {
  return getImpl<detail::ScheduleDayHourly_Impl>()->isHour17Defaulted();
}

bool ScheduleDayHourly::setHour17(double hour17) {
  return getImpl<detail::ScheduleDayHourly_Impl>()->setHour17(hour17);
}

void ScheduleDayHourly::resetHour17() {
  getImpl<detail::ScheduleDayHourly_Impl>()->resetHour17();
}

double ScheduleDayHourly::hour18() const {
  return getImpl<detail::ScheduleDayHourly_Impl>()->hour18();
}

bool ScheduleDayHourly::isHour18Defaulted() const {
  return getImpl<detail::ScheduleDayHourly_Impl>()->isHour18Defaulted();
}

bool ScheduleDayHourly::setHour18(double hour18) {
  return getImpl<detail::ScheduleDayHourly_Impl>()->setHour18(hour18);
}

void ScheduleDayHourly::resetHour18() {
  getImpl<detail::ScheduleDayHourly_Impl>()->resetHour18();
}

double ScheduleDayHourly::hour19() const {
  return getImpl<detail::ScheduleDayHourly_Impl>()->hour19();
}

bool ScheduleDayHourly::isHour19Defaulted() const {
  return getImpl<detail::ScheduleDayHourly_Impl>()->isHour19Defaulted();
}

bool ScheduleDayHourly::setHour19(double hour19) {
  return getImpl<detail::ScheduleDayHourly_Impl>()->setHour19(hour19);
}

void ScheduleDayHourly::resetHour19() {
  getImpl<detail::ScheduleDayHourly_Impl>()->resetHour19();
}

double ScheduleDayHourly::hour20() const {
  return getImpl<detail::ScheduleDayHourly_Impl>()->hour20();
}

bool ScheduleDayHourly::isHour20Defaulted() const {
  return getImpl<detail::ScheduleDayHourly_Impl>()->isHour20Defaulted();
}

bool ScheduleDayHourly::setHour20(double hour20) {
  return getImpl<detail::ScheduleDayHourly_Impl>()->setHour20(hour20);
}

void ScheduleDayHourly::resetHour20() {
  getImpl<detail::ScheduleDayHourly_Impl>()->resetHour20();
}

double ScheduleDayHourly::hour21() const {
  return getImpl<detail::ScheduleDayHourly_Impl>()->hour21();
}

bool ScheduleDayHourly::isHour21Defaulted() const {
  return getImpl<detail::ScheduleDayHourly_Impl>()->isHour21Defaulted();
}

bool ScheduleDayHourly::setHour21(double hour21) {
  return getImpl<detail::ScheduleDayHourly_Impl>()->setHour21(hour21);
}

void ScheduleDayHourly::resetHour21() {
  getImpl<detail::ScheduleDayHourly_Impl>()->resetHour21();
}

double ScheduleDayHourly::hour22() const {
  return getImpl<detail::ScheduleDayHourly_Impl>()->hour22();
}

bool ScheduleDayHourly::isHour22Defaulted() const {
  return getImpl<detail::ScheduleDayHourly_Impl>()->isHour22Defaulted();
}

bool ScheduleDayHourly::setHour22(double hour22) {
  return getImpl<detail::ScheduleDayHourly_Impl>()->setHour22(hour22);
}

void ScheduleDayHourly::resetHour22() {
  getImpl<detail::ScheduleDayHourly_Impl>()->resetHour22();
}

double ScheduleDayHourly::hour23() const {
  return getImpl<detail::ScheduleDayHourly_Impl>()->hour23();
}

bool ScheduleDayHourly::isHour23Defaulted() const {
  return getImpl<detail::ScheduleDayHourly_Impl>()->isHour23Defaulted();
}

bool ScheduleDayHourly::setHour23(double hour23) {
  return getImpl<detail::ScheduleDayHourly_Impl>()->setHour23(hour23);
}

void ScheduleDayHourly::resetHour23() {
  getImpl<detail::ScheduleDayHourly_Impl>()->resetHour23();
}

double ScheduleDayHourly::hour24() const {
  return getImpl<detail::ScheduleDayHourly_Impl>()->hour24();
}

bool ScheduleDayHourly::isHour24Defaulted() const {
  return getImpl<detail::ScheduleDayHourly_Impl>()->isHour24Defaulted();
}

bool ScheduleDayHourly::setHour24(double hour24) {
  return getImpl<detail::ScheduleDayHourly_Impl>()->setHour24(hour24);
}

void ScheduleDayHourly::resetHour24() {
  getImpl<detail::ScheduleDayHourly_Impl>()->resetHour24();
}

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
namespace detail {

double ScheduleDayHourly_Impl::hour1() const {
  const auto value = getDouble(openstudio::Schedule_Day_HourlyFields::Hour1, true);
  OS_ASSERT(value);
  return *value;
}

bool ScheduleDayHourly_Impl::isHour1Defaulted() const {
  return isEmpty(openstudio::Schedule_Day_HourlyFields::Hour1);
}

bool ScheduleDayHourly_Impl::setHour1(double hour1) {
  const bool result = setDouble(openstudio::Schedule_Day_HourlyFields::Hour1, hour1);
  OS_ASSERT(result);
  return result;
}

void ScheduleDayHourly_Impl::resetHour1() {
  OS_ASSERT(setString(openstudio::Schedule_Day_HourlyFields::Hour1, ""));
}

double ScheduleDayHourly_Impl::hour2() const {
  const auto value = getDouble(openstudio::Schedule_Day_HourlyFields::Hour2, true);
  OS_ASSERT(value);
  return *value;
}

bool ScheduleDayHourly_Impl::isHour2Defaulted() const {
  return isEmpty(openstudio::Schedule_Day_HourlyFields::Hour2);
}

bool ScheduleDayHourly_Impl::setHour2(double hour2) {
  const bool result = setDouble(openstudio::Schedule_Day_HourlyFields::Hour2, hour2);
  OS_ASSERT(result);
  return result;
}

void ScheduleDayHourly_Impl::resetHour2() {
  OS_ASSERT(setString(openstudio::Schedule_Day_HourlyFields::Hour2, ""));
}

double ScheduleDayHourly_Impl::hour3() const {
  const auto value = getDouble(openstudio::Schedule_Day_HourlyFields::Hour3, true);
  OS_ASSERT(value);
  return *value;
}

bool ScheduleDayHourly_Impl::isHour3Defaulted() const {
  return isEmpty(openstudio::Schedule_Day_HourlyFields::Hour3);
}

bool ScheduleDayHourly_Impl::setHour3(double hour3) {
  const bool result = setDouble(openstudio::Schedule_Day_HourlyFields::Hour3, hour3);
  OS_ASSERT(result);
  return result;
}

void ScheduleDayHourly_Impl::resetHour3() {
  OS_ASSERT(setString(openstudio::Schedule_Day_HourlyFields::Hour3, ""));
}

double ScheduleDayHourly_Impl::hour4() const {
  const auto value = getDouble(openstudio::Schedule_Day_HourlyFields::Hour4, true);
  OS_ASSERT(value);
  return *value;
}

bool ScheduleDayHourly_Impl::isHour4Defaulted() const {
  return isEmpty(openstudio::Schedule_Day_HourlyFields::Hour4);
}

bool ScheduleDayHourly_Impl::setHour4(double hour4) {
  const bool result = setDouble(openstudio::Schedule_Day_HourlyFields::Hour4, hour4);
  OS_ASSERT(result);
  return result;
}

void ScheduleDayHourly_Impl::resetHour4() {
  OS_ASSERT(setString(openstudio::Schedule_Day_HourlyFields::Hour4, ""));
}

double ScheduleDayHourly_Impl::hour5() const {
  const auto value = getDouble(openstudio::Schedule_Day_HourlyFields::Hour5, true);
  OS_ASSERT(value);
  return *value;
}

bool ScheduleDayHourly_Impl::isHour5Defaulted() const {
  return isEmpty(openstudio::Schedule_Day_HourlyFields::Hour5);
}

bool ScheduleDayHourly_Impl::setHour5(double hour5) {
  const bool result = setDouble(openstudio::Schedule_Day_HourlyFields::Hour5, hour5);
  OS_ASSERT(result);
  return result;
}

void ScheduleDayHourly_Impl::resetHour5() {
  OS_ASSERT(setString(openstudio::Schedule_Day_HourlyFields::Hour5, ""));
}

double ScheduleDayHourly_Impl::hour6() const {
  const auto value = getDouble(openstudio::Schedule_Day_HourlyFields::Hour6, true);
  OS_ASSERT(value);
  return *value;
}

bool ScheduleDayHourly_Impl::isHour6Defaulted() const {
  return isEmpty(openstudio::Schedule_Day_HourlyFields::Hour6);
}

bool ScheduleDayHourly_Impl::setHour6(double hour6) {
  const bool result = setDouble(openstudio::Schedule_Day_HourlyFields::Hour6, hour6);
  OS_ASSERT(result);
  return result;
}

void ScheduleDayHourly_Impl::resetHour6() {
  OS_ASSERT(setString(openstudio::Schedule_Day_HourlyFields::Hour6, ""));
}

double ScheduleDayHourly_Impl::hour7() const {
  const auto value = getDouble(openstudio::Schedule_Day_HourlyFields::Hour7, true);
  OS_ASSERT(value);
  return *value;
}

bool ScheduleDayHourly_Impl::isHour7Defaulted() const {
  return isEmpty(openstudio::Schedule_Day_HourlyFields::Hour7);
}

bool ScheduleDayHourly_Impl::setHour7(double hour7) {
  const bool result = setDouble(openstudio::Schedule_Day_HourlyFields::Hour7, hour7);
  OS_ASSERT(result);
  return result;
}

void ScheduleDayHourly_Impl::resetHour7() {
  OS_ASSERT(setString(openstudio::Schedule_Day_HourlyFields::Hour7, ""));
}

double ScheduleDayHourly_Impl::hour8() const {
  const auto value = getDouble(openstudio::Schedule_Day_HourlyFields::Hour8, true);
  OS_ASSERT(value);
  return *value;
}

bool ScheduleDayHourly_Impl::isHour8Defaulted() const {
  return isEmpty(openstudio::Schedule_Day_HourlyFields::Hour8);
}

bool ScheduleDayHourly_Impl::setHour8(double hour8) {
  const bool result = setDouble(openstudio::Schedule_Day_HourlyFields::Hour8, hour8);
  OS_ASSERT(result);
  return result;
}

void ScheduleDayHourly_Impl::resetHour8() {
  OS_ASSERT(setString(openstudio::Schedule_Day_HourlyFields::Hour8, ""));
}

double ScheduleDayHourly_Impl::hour9() const {
  const auto value = getDouble(openstudio::Schedule_Day_HourlyFields::Hour9, true);
  OS_ASSERT(value);
  return *value;
}

bool ScheduleDayHourly_Impl::isHour9Defaulted() const {
  return isEmpty(openstudio::Schedule_Day_HourlyFields::Hour9);
}

bool ScheduleDayHourly_Impl::setHour9(double hour9) {
  const bool result = setDouble(openstudio::Schedule_Day_HourlyFields::Hour9, hour9);
  OS_ASSERT(result);
  return result;
}

void ScheduleDayHourly_Impl::resetHour9() {
  OS_ASSERT(setString(openstudio::Schedule_Day_HourlyFields::Hour9, ""));
}

double ScheduleDayHourly_Impl::hour10() const {
  const auto value = getDouble(openstudio::Schedule_Day_HourlyFields::Hour10, true);
  OS_ASSERT(value);
  return *value;
}

bool ScheduleDayHourly_Impl::isHour10Defaulted() const {
  return isEmpty(openstudio::Schedule_Day_HourlyFields::Hour10);
}

bool ScheduleDayHourly_Impl::setHour10(double hour10) {
  const bool result = setDouble(openstudio::Schedule_Day_HourlyFields::Hour10, hour10);
  OS_ASSERT(result);
  return result;
}

void ScheduleDayHourly_Impl::resetHour10() {
  OS_ASSERT(setString(openstudio::Schedule_Day_HourlyFields::Hour10, ""));
}

double ScheduleDayHourly_Impl::hour11() const {
  const auto value = getDouble(openstudio::Schedule_Day_HourlyFields::Hour11, true);
  OS_ASSERT(value);
  return *value;
}

bool ScheduleDayHourly_Impl::isHour11Defaulted() const {
  return isEmpty(openstudio::Schedule_Day_HourlyFields::Hour11);
}

bool ScheduleDayHourly_Impl::setHour11(double hour11) {
  const bool result = setDouble(openstudio::Schedule_Day_HourlyFields::Hour11, hour11);
  OS_ASSERT(result);
  return result;
}

void ScheduleDayHourly_Impl::resetHour11() {
  OS_ASSERT(setString(openstudio::Schedule_Day_HourlyFields::Hour11, ""));
}

double ScheduleDayHourly_Impl::hour12() const {
  const auto value = getDouble(openstudio::Schedule_Day_HourlyFields::Hour12, true);
  OS_ASSERT(value);
  return *value;
}

bool ScheduleDayHourly_Impl::isHour12Defaulted() const {
  return isEmpty(openstudio::Schedule_Day_HourlyFields::Hour12);
}

bool ScheduleDayHourly_Impl::setHour12(double hour12) {
  const bool result = setDouble(openstudio::Schedule_Day_HourlyFields::Hour12, hour12);
  OS_ASSERT(result);
  return result;
}

void ScheduleDayHourly_Impl::resetHour12() {
  OS_ASSERT(setString(openstudio::Schedule_Day_HourlyFields::Hour12, ""));
}

double ScheduleDayHourly_Impl::hour13() const {
  const auto value = getDouble(openstudio::Schedule_Day_HourlyFields::Hour13, true);
  OS_ASSERT(value);
  return *value;
}

bool ScheduleDayHourly_Impl::isHour13Defaulted() const {
  return isEmpty(openstudio::Schedule_Day_HourlyFields::Hour13);
}

bool ScheduleDayHourly_Impl::setHour13(double hour13) {
  const bool result = setDouble(openstudio::Schedule_Day_HourlyFields::Hour13, hour13);
  OS_ASSERT(result);
  return result;
}

void ScheduleDayHourly_Impl::resetHour13() {
  OS_ASSERT(setString(openstudio::Schedule_Day_HourlyFields::Hour13, ""));
}

double ScheduleDayHourly_Impl::hour14() const {
  const auto value = getDouble(openstudio::Schedule_Day_HourlyFields::Hour14, true);
  OS_ASSERT(value);
  return *value;
}

bool ScheduleDayHourly_Impl::isHour14Defaulted() const {
  return isEmpty(openstudio::Schedule_Day_HourlyFields::Hour14);
}

bool ScheduleDayHourly_Impl::setHour14(double hour14) {
  const bool result = setDouble(openstudio::Schedule_Day_HourlyFields::Hour14, hour14);
  OS_ASSERT(result);
  return result;
}

void ScheduleDayHourly_Impl::resetHour14() {
  OS_ASSERT(setString(openstudio::Schedule_Day_HourlyFields::Hour14, ""));
}

double ScheduleDayHourly_Impl::hour15() const {
  const auto value = getDouble(openstudio::Schedule_Day_HourlyFields::Hour15, true);
  OS_ASSERT(value);
  return *value;
}

bool ScheduleDayHourly_Impl::isHour15Defaulted() const {
  return isEmpty(openstudio::Schedule_Day_HourlyFields::Hour15);
}

bool ScheduleDayHourly_Impl::setHour15(double hour15) {
  const bool result = setDouble(openstudio::Schedule_Day_HourlyFields::Hour15, hour15);
  OS_ASSERT(result);
  return result;
}

void ScheduleDayHourly_Impl::resetHour15() {
  OS_ASSERT(setString(openstudio::Schedule_Day_HourlyFields::Hour15, ""));
}

double ScheduleDayHourly_Impl::hour16() const {
  const auto value = getDouble(openstudio::Schedule_Day_HourlyFields::Hour16, true);
  OS_ASSERT(value);
  return *value;
}

bool ScheduleDayHourly_Impl::isHour16Defaulted() const {
  return isEmpty(openstudio::Schedule_Day_HourlyFields::Hour16);
}

bool ScheduleDayHourly_Impl::setHour16(double hour16) {
  const bool result = setDouble(openstudio::Schedule_Day_HourlyFields::Hour16, hour16);
  OS_ASSERT(result);
  return result;
}

void ScheduleDayHourly_Impl::resetHour16() {
  OS_ASSERT(setString(openstudio::Schedule_Day_HourlyFields::Hour16, ""));
}

double ScheduleDayHourly_Impl::hour17() const {
  const auto value = getDouble(openstudio::Schedule_Day_HourlyFields::Hour17, true);
  OS_ASSERT(value);
  return *value;
}

bool ScheduleDayHourly_Impl::isHour17Defaulted() const {
  return isEmpty(openstudio::Schedule_Day_HourlyFields::Hour17);
}

bool ScheduleDayHourly_Impl::setHour17(double hour17) {
  const bool result = setDouble(openstudio::Schedule_Day_HourlyFields::Hour17, hour17);
  OS_ASSERT(result);
  return result;
}

void ScheduleDayHourly_Impl::resetHour17() {
  OS_ASSERT(setString(openstudio::Schedule_Day_HourlyFields::Hour17, ""));
}

double ScheduleDayHourly_Impl::hour18() const {
  const auto value = getDouble(openstudio::Schedule_Day_HourlyFields::Hour18, true);
  OS_ASSERT(value);
  return *value;
}

bool ScheduleDayHourly_Impl::isHour18Defaulted() const {
  return isEmpty(openstudio::Schedule_Day_HourlyFields::Hour18);
}

bool ScheduleDayHourly_Impl::setHour18(double hour18) {
  const bool result = setDouble(openstudio::Schedule_Day_HourlyFields::Hour18, hour18);
  OS_ASSERT(result);
  return result;
}

void ScheduleDayHourly_Impl::resetHour18() {
  OS_ASSERT(setString(openstudio::Schedule_Day_HourlyFields::Hour18, ""));
}

double ScheduleDayHourly_Impl::hour19() const {
  const auto value = getDouble(openstudio::Schedule_Day_HourlyFields::Hour19, true);
  OS_ASSERT(value);
  return *value;
}

bool ScheduleDayHourly_Impl::isHour19Defaulted() const {
  return isEmpty(openstudio::Schedule_Day_HourlyFields::Hour19);
}

bool ScheduleDayHourly_Impl::setHour19(double hour19) {
  const bool result = setDouble(openstudio::Schedule_Day_HourlyFields::Hour19, hour19);
  OS_ASSERT(result);
  return result;
}

void ScheduleDayHourly_Impl::resetHour19() {
  OS_ASSERT(setString(openstudio::Schedule_Day_HourlyFields::Hour19, ""));
}

double ScheduleDayHourly_Impl::hour20() const {
  const auto value = getDouble(openstudio::Schedule_Day_HourlyFields::Hour20, true);
  OS_ASSERT(value);
  return *value;
}

bool ScheduleDayHourly_Impl::isHour20Defaulted() const {
  return isEmpty(openstudio::Schedule_Day_HourlyFields::Hour20);
}

bool ScheduleDayHourly_Impl::setHour20(double hour20) {
  const bool result = setDouble(openstudio::Schedule_Day_HourlyFields::Hour20, hour20);
  OS_ASSERT(result);
  return result;
}

void ScheduleDayHourly_Impl::resetHour20() {
  OS_ASSERT(setString(openstudio::Schedule_Day_HourlyFields::Hour20, ""));
}

double ScheduleDayHourly_Impl::hour21() const {
  const auto value = getDouble(openstudio::Schedule_Day_HourlyFields::Hour21, true);
  OS_ASSERT(value);
  return *value;
}

bool ScheduleDayHourly_Impl::isHour21Defaulted() const {
  return isEmpty(openstudio::Schedule_Day_HourlyFields::Hour21);
}

bool ScheduleDayHourly_Impl::setHour21(double hour21) {
  const bool result = setDouble(openstudio::Schedule_Day_HourlyFields::Hour21, hour21);
  OS_ASSERT(result);
  return result;
}

void ScheduleDayHourly_Impl::resetHour21() {
  OS_ASSERT(setString(openstudio::Schedule_Day_HourlyFields::Hour21, ""));
}

double ScheduleDayHourly_Impl::hour22() const {
  const auto value = getDouble(openstudio::Schedule_Day_HourlyFields::Hour22, true);
  OS_ASSERT(value);
  return *value;
}

bool ScheduleDayHourly_Impl::isHour22Defaulted() const {
  return isEmpty(openstudio::Schedule_Day_HourlyFields::Hour22);
}

bool ScheduleDayHourly_Impl::setHour22(double hour22) {
  const bool result = setDouble(openstudio::Schedule_Day_HourlyFields::Hour22, hour22);
  OS_ASSERT(result);
  return result;
}

void ScheduleDayHourly_Impl::resetHour22() {
  OS_ASSERT(setString(openstudio::Schedule_Day_HourlyFields::Hour22, ""));
}

double ScheduleDayHourly_Impl::hour23() const {
  const auto value = getDouble(openstudio::Schedule_Day_HourlyFields::Hour23, true);
  OS_ASSERT(value);
  return *value;
}

bool ScheduleDayHourly_Impl::isHour23Defaulted() const {
  return isEmpty(openstudio::Schedule_Day_HourlyFields::Hour23);
}

bool ScheduleDayHourly_Impl::setHour23(double hour23) {
  const bool result = setDouble(openstudio::Schedule_Day_HourlyFields::Hour23, hour23);
  OS_ASSERT(result);
  return result;
}

void ScheduleDayHourly_Impl::resetHour23() {
  OS_ASSERT(setString(openstudio::Schedule_Day_HourlyFields::Hour23, ""));
}

double ScheduleDayHourly_Impl::hour24() const {
  const auto value = getDouble(openstudio::Schedule_Day_HourlyFields::Hour24, true);
  OS_ASSERT(value);
  return *value;
}

bool ScheduleDayHourly_Impl::isHour24Defaulted() const {
  return isEmpty(openstudio::Schedule_Day_HourlyFields::Hour24);
}

bool ScheduleDayHourly_Impl::setHour24(double hour24) {
  const bool result = setDouble(openstudio::Schedule_Day_HourlyFields::Hour24, hour24);
  OS_ASSERT(result);
  return result;
}

void ScheduleDayHourly_Impl::resetHour24() {
  OS_ASSERT(setString(openstudio::Schedule_Day_HourlyFields::Hour24, ""));
}

}  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
