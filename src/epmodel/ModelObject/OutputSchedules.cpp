/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "OutputSchedules.hpp"
#include "OutputSchedules_Impl.hpp"

#include "Model.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/idd/IddEnums.hxx>
#include <utilities/idd/IddFactory.hxx>
#include <utilities/idd/IddObject.hpp>
#include <utilities/idd/Output_Schedules_FieldEnums.hxx>

namespace openstudio {
namespace epmodel {

OutputSchedules::OutputSchedules(const Model& model) : ModelObject(OutputSchedules::iddObjectType(), model) {
  const bool ok = setKeyField("Hourly");
  OS_ASSERT(ok);
}

OutputSchedules::OutputSchedules(std::shared_ptr<detail::OutputSchedules_Impl> impl) : ModelObject(std::move(impl)) {}

IddObjectType OutputSchedules::iddObjectType() {
  return IddObjectType::Output_Schedules;
}

std::vector<std::string> OutputSchedules::keyFieldValues() {
  return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(), openstudio::Output_SchedulesFields::KeyField);
}

std::vector<std::string> OutputSchedules::validKeyFieldValues() {
  return keyFieldValues();
}

std::string OutputSchedules::keyField() const {
  return getImpl<detail::OutputSchedules_Impl>()->keyField();
}

bool OutputSchedules::setKeyField(const std::string& keyField) {
  return getImpl<detail::OutputSchedules_Impl>()->setKeyField(keyField);
}

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
namespace detail {

std::string OutputSchedules_Impl::keyField() const {
  const auto value = getString(openstudio::Output_SchedulesFields::KeyField, true);
  OS_ASSERT(value);
  return *value;
}

bool OutputSchedules_Impl::setKeyField(const std::string& keyField) {
  return setString(openstudio::Output_SchedulesFields::KeyField, keyField);
}

std::vector<std::string> OutputSchedules_Impl::keyFieldValues() const {
  return openstudio::epmodel::OutputSchedules::keyFieldValues();
}

std::vector<std::string> OutputSchedules_Impl::validKeyFieldValues() const {
  return openstudio::epmodel::OutputSchedules::validKeyFieldValues();
}

}  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
