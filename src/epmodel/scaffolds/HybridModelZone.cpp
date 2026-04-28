/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "HybridModelZone.hpp"
#include "HybridModelZone_Impl.hpp"

#include "Model.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/core/StringHelpers.hpp>
#include <utilities/idd/HybridModel_Zone_FieldEnums.hxx>
#include <utilities/idd/IddEnums.hxx>

namespace openstudio {
namespace epmodel {

HybridModelZone::HybridModelZone(const Model& model) : ModelObject(HybridModelZone::iddObjectType(), model) {}

HybridModelZone::HybridModelZone(std::shared_ptr<detail::HybridModelZone_Impl> impl) : ModelObject(std::move(impl)) {}

IddObjectType HybridModelZone::iddObjectType() {
  return IddObjectType::HybridModel_Zone;
}

bool HybridModelZone::calculateZoneInternalThermalMass() const {
  return getImpl<detail::HybridModelZone_Impl>()->calculateZoneInternalThermalMass();
}

bool HybridModelZone::isCalculateZoneInternalThermalMassDefaulted() const {
  return getImpl<detail::HybridModelZone_Impl>()->isCalculateZoneInternalThermalMassDefaulted();
}

bool HybridModelZone::setCalculateZoneInternalThermalMass(bool calculateZoneInternalThermalMass) {
  return getImpl<detail::HybridModelZone_Impl>()->setCalculateZoneInternalThermalMass(calculateZoneInternalThermalMass);
}

void HybridModelZone::resetCalculateZoneInternalThermalMass() {
  getImpl<detail::HybridModelZone_Impl>()->resetCalculateZoneInternalThermalMass();
}

bool HybridModelZone::calculateZoneAirInfiltrationRate() const {
  return getImpl<detail::HybridModelZone_Impl>()->calculateZoneAirInfiltrationRate();
}

bool HybridModelZone::isCalculateZoneAirInfiltrationRateDefaulted() const {
  return getImpl<detail::HybridModelZone_Impl>()->isCalculateZoneAirInfiltrationRateDefaulted();
}

bool HybridModelZone::setCalculateZoneAirInfiltrationRate(bool calculateZoneAirInfiltrationRate) {
  return getImpl<detail::HybridModelZone_Impl>()->setCalculateZoneAirInfiltrationRate(calculateZoneAirInfiltrationRate);
}

void HybridModelZone::resetCalculateZoneAirInfiltrationRate() {
  getImpl<detail::HybridModelZone_Impl>()->resetCalculateZoneAirInfiltrationRate();
}

bool HybridModelZone::calculateZonePeopleCount() const {
  return getImpl<detail::HybridModelZone_Impl>()->calculateZonePeopleCount();
}

bool HybridModelZone::isCalculateZonePeopleCountDefaulted() const {
  return getImpl<detail::HybridModelZone_Impl>()->isCalculateZonePeopleCountDefaulted();
}

bool HybridModelZone::setCalculateZonePeopleCount(bool calculateZonePeopleCount) {
  return getImpl<detail::HybridModelZone_Impl>()->setCalculateZonePeopleCount(calculateZonePeopleCount);
}

void HybridModelZone::resetCalculateZonePeopleCount() {
  getImpl<detail::HybridModelZone_Impl>()->resetCalculateZonePeopleCount();
}

int HybridModelZone::beginMonth() const {
  return getImpl<detail::HybridModelZone_Impl>()->beginMonth();
}

bool HybridModelZone::setBeginMonth(int beginMonth) {
  return getImpl<detail::HybridModelZone_Impl>()->setBeginMonth(beginMonth);
}

int HybridModelZone::beginDayofMonth() const {
  return getImpl<detail::HybridModelZone_Impl>()->beginDayofMonth();
}

bool HybridModelZone::setBeginDayofMonth(int beginDayofMonth) {
  return getImpl<detail::HybridModelZone_Impl>()->setBeginDayofMonth(beginDayofMonth);
}

int HybridModelZone::endMonth() const {
  return getImpl<detail::HybridModelZone_Impl>()->endMonth();
}

bool HybridModelZone::setEndMonth(int endMonth) {
  return getImpl<detail::HybridModelZone_Impl>()->setEndMonth(endMonth);
}

int HybridModelZone::endDayofMonth() const {
  return getImpl<detail::HybridModelZone_Impl>()->endDayofMonth();
}

bool HybridModelZone::setEndDayofMonth(int endDayofMonth) {
  return getImpl<detail::HybridModelZone_Impl>()->setEndDayofMonth(endDayofMonth);
}

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
namespace detail {

bool HybridModelZone_Impl::calculateZoneInternalThermalMass() const {
  const auto value = getString(openstudio::HybridModel_ZoneFields::CalculateZoneInternalThermalMass, true);
  OS_ASSERT(value);
  return openstudio::istringEqual(*value, "Yes");
}

bool HybridModelZone_Impl::isCalculateZoneInternalThermalMassDefaulted() const {
  return isEmpty(openstudio::HybridModel_ZoneFields::CalculateZoneInternalThermalMass);
}

bool HybridModelZone_Impl::setCalculateZoneInternalThermalMass(bool calculateZoneInternalThermalMass) {
  const bool result = setString(openstudio::HybridModel_ZoneFields::CalculateZoneInternalThermalMass,
                                calculateZoneInternalThermalMass ? "Yes" : "No");
  OS_ASSERT(result);
  return result;
}

void HybridModelZone_Impl::resetCalculateZoneInternalThermalMass() {
  OS_ASSERT(setString(openstudio::HybridModel_ZoneFields::CalculateZoneInternalThermalMass, ""));
}

bool HybridModelZone_Impl::calculateZoneAirInfiltrationRate() const {
  const auto value = getString(openstudio::HybridModel_ZoneFields::CalculateZoneAirInfiltrationRate, true);
  OS_ASSERT(value);
  return openstudio::istringEqual(*value, "Yes");
}

bool HybridModelZone_Impl::isCalculateZoneAirInfiltrationRateDefaulted() const {
  return isEmpty(openstudio::HybridModel_ZoneFields::CalculateZoneAirInfiltrationRate);
}

bool HybridModelZone_Impl::setCalculateZoneAirInfiltrationRate(bool calculateZoneAirInfiltrationRate) {
  const bool result =
    setString(openstudio::HybridModel_ZoneFields::CalculateZoneAirInfiltrationRate, calculateZoneAirInfiltrationRate ? "Yes" : "No");
  OS_ASSERT(result);
  return result;
}

void HybridModelZone_Impl::resetCalculateZoneAirInfiltrationRate() {
  OS_ASSERT(setString(openstudio::HybridModel_ZoneFields::CalculateZoneAirInfiltrationRate, ""));
}

bool HybridModelZone_Impl::calculateZonePeopleCount() const {
  const auto value = getString(openstudio::HybridModel_ZoneFields::CalculateZonePeopleCount, true);
  OS_ASSERT(value);
  return openstudio::istringEqual(*value, "Yes");
}

bool HybridModelZone_Impl::isCalculateZonePeopleCountDefaulted() const {
  return isEmpty(openstudio::HybridModel_ZoneFields::CalculateZonePeopleCount);
}

bool HybridModelZone_Impl::setCalculateZonePeopleCount(bool calculateZonePeopleCount) {
  const bool result = setString(openstudio::HybridModel_ZoneFields::CalculateZonePeopleCount, calculateZonePeopleCount ? "Yes" : "No");
  OS_ASSERT(result);
  return result;
}

void HybridModelZone_Impl::resetCalculateZonePeopleCount() {
  OS_ASSERT(setString(openstudio::HybridModel_ZoneFields::CalculateZonePeopleCount, ""));
}

int HybridModelZone_Impl::beginMonth() const {
  const auto value = getInt(openstudio::HybridModel_ZoneFields::BeginMonth, true);
  OS_ASSERT(value);
  return *value;
}

bool HybridModelZone_Impl::setBeginMonth(int beginMonth) {
  const bool result = setInt(openstudio::HybridModel_ZoneFields::BeginMonth, beginMonth);
  OS_ASSERT(result);
  return result;
}

int HybridModelZone_Impl::beginDayofMonth() const {
  const auto value = getInt(openstudio::HybridModel_ZoneFields::BeginDayofMonth, true);
  OS_ASSERT(value);
  return *value;
}

bool HybridModelZone_Impl::setBeginDayofMonth(int beginDayofMonth) {
  const bool result = setInt(openstudio::HybridModel_ZoneFields::BeginDayofMonth, beginDayofMonth);
  OS_ASSERT(result);
  return result;
}

int HybridModelZone_Impl::endMonth() const {
  const auto value = getInt(openstudio::HybridModel_ZoneFields::EndMonth, true);
  OS_ASSERT(value);
  return *value;
}

bool HybridModelZone_Impl::setEndMonth(int endMonth) {
  const bool result = setInt(openstudio::HybridModel_ZoneFields::EndMonth, endMonth);
  OS_ASSERT(result);
  return result;
}

int HybridModelZone_Impl::endDayofMonth() const {
  const auto value = getInt(openstudio::HybridModel_ZoneFields::EndDayofMonth, true);
  OS_ASSERT(value);
  return *value;
}

bool HybridModelZone_Impl::setEndDayofMonth(int endDayofMonth) {
  const bool result = setInt(openstudio::HybridModel_ZoneFields::EndDayofMonth, endDayofMonth);
  OS_ASSERT(result);
  return result;
}

}  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
