/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "ParentObject/LifeCycleCostUsePriceEscalation.hpp"
#include "ParentObject/LifeCycleCostUsePriceEscalation_Impl.hpp"

#include "Model.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/idd/IddEnums.hxx>
#include <utilities/idd/IddFactory.hxx>
#include <utilities/idd/IddObject.hpp>
#include <utilities/idd/LifeCycleCost_UsePriceEscalation_FieldEnums.hxx>

namespace openstudio {
namespace epmodel {

LifeCycleCostUsePriceEscalation::LifeCycleCostUsePriceEscalation(const Model& model)
  : ParentObject(LifeCycleCostUsePriceEscalation::iddObjectType(), model) {}

LifeCycleCostUsePriceEscalation::LifeCycleCostUsePriceEscalation(std::shared_ptr<detail::LifeCycleCostUsePriceEscalation_Impl> impl)
  : ParentObject(std::move(impl)) {}

IddObjectType LifeCycleCostUsePriceEscalation::iddObjectType() {
  return IddObjectType::LifeCycleCost_UsePriceEscalation;
}

std::vector<std::string> LifeCycleCostUsePriceEscalation::resourceValues() {
  return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(), openstudio::LifeCycleCost_UsePriceEscalationFields::Resource);
}

std::vector<std::string> LifeCycleCostUsePriceEscalation::escalationStartMonthValues() {
  return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(),
                        openstudio::LifeCycleCost_UsePriceEscalationFields::EscalationStartMonth);
}

std::string LifeCycleCostUsePriceEscalation::resource() const {
  return getImpl<detail::LifeCycleCostUsePriceEscalation_Impl>()->resource();
}

bool LifeCycleCostUsePriceEscalation::setResource(const std::string& resource) {
  return getImpl<detail::LifeCycleCostUsePriceEscalation_Impl>()->setResource(resource);
}

boost::optional<int> LifeCycleCostUsePriceEscalation::escalationStartYear() const {
  return getImpl<detail::LifeCycleCostUsePriceEscalation_Impl>()->escalationStartYear();
}

bool LifeCycleCostUsePriceEscalation::setEscalationStartYear(int escalationStartYear) {
  return getImpl<detail::LifeCycleCostUsePriceEscalation_Impl>()->setEscalationStartYear(escalationStartYear);
}

void LifeCycleCostUsePriceEscalation::resetEscalationStartYear() {
  getImpl<detail::LifeCycleCostUsePriceEscalation_Impl>()->resetEscalationStartYear();
}

std::string LifeCycleCostUsePriceEscalation::escalationStartMonth() const {
  return getImpl<detail::LifeCycleCostUsePriceEscalation_Impl>()->escalationStartMonth();
}

bool LifeCycleCostUsePriceEscalation::isEscalationStartMonthDefaulted() const {
  return getImpl<detail::LifeCycleCostUsePriceEscalation_Impl>()->isEscalationStartMonthDefaulted();
}

bool LifeCycleCostUsePriceEscalation::setEscalationStartMonth(const std::string& escalationStartMonth) {
  return getImpl<detail::LifeCycleCostUsePriceEscalation_Impl>()->setEscalationStartMonth(escalationStartMonth);
}

void LifeCycleCostUsePriceEscalation::resetEscalationStartMonth() {
  getImpl<detail::LifeCycleCostUsePriceEscalation_Impl>()->resetEscalationStartMonth();
}

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
namespace detail {

std::string LifeCycleCostUsePriceEscalation_Impl::resource() const {
  const auto value = getString(openstudio::LifeCycleCost_UsePriceEscalationFields::Resource, true);
  OS_ASSERT(value);
  return *value;
}

bool LifeCycleCostUsePriceEscalation_Impl::setResource(const std::string& resource) {
  return setString(openstudio::LifeCycleCost_UsePriceEscalationFields::Resource, resource);
}

boost::optional<int> LifeCycleCostUsePriceEscalation_Impl::escalationStartYear() const {
  return getInt(openstudio::LifeCycleCost_UsePriceEscalationFields::EscalationStartYear, true);
}

bool LifeCycleCostUsePriceEscalation_Impl::setEscalationStartYear(int escalationStartYear) {
  return setInt(openstudio::LifeCycleCost_UsePriceEscalationFields::EscalationStartYear, escalationStartYear);
}

void LifeCycleCostUsePriceEscalation_Impl::resetEscalationStartYear() {
  OS_ASSERT(setString(openstudio::LifeCycleCost_UsePriceEscalationFields::EscalationStartYear, ""));
}

std::string LifeCycleCostUsePriceEscalation_Impl::escalationStartMonth() const {
  const auto value = getString(openstudio::LifeCycleCost_UsePriceEscalationFields::EscalationStartMonth, true);
  OS_ASSERT(value);
  return *value;
}

bool LifeCycleCostUsePriceEscalation_Impl::isEscalationStartMonthDefaulted() const {
  return isEmpty(openstudio::LifeCycleCost_UsePriceEscalationFields::EscalationStartMonth);
}

bool LifeCycleCostUsePriceEscalation_Impl::setEscalationStartMonth(const std::string& escalationStartMonth) {
  return setString(openstudio::LifeCycleCost_UsePriceEscalationFields::EscalationStartMonth, escalationStartMonth);
}

void LifeCycleCostUsePriceEscalation_Impl::resetEscalationStartMonth() {
  OS_ASSERT(setString(openstudio::LifeCycleCost_UsePriceEscalationFields::EscalationStartMonth, ""));
}

std::vector<std::string> LifeCycleCostUsePriceEscalation_Impl::resourceValues() const {
  return openstudio::epmodel::LifeCycleCostUsePriceEscalation::resourceValues();
}

std::vector<std::string> LifeCycleCostUsePriceEscalation_Impl::escalationStartMonthValues() const {
  return openstudio::epmodel::LifeCycleCostUsePriceEscalation::escalationStartMonthValues();
}

}  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
