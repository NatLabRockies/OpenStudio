/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "OutputControlTimestamp.hpp"
#include "OutputControlTimestamp_Impl.hpp"

#include "Model.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/core/StringHelpers.hpp>
#include <utilities/idd/IddEnums.hxx>
#include <utilities/idd/OutputControl_Timestamp_FieldEnums.hxx>

namespace openstudio {
namespace epmodel {

OutputControlTimestamp::OutputControlTimestamp(const Model& model) : ModelObject(OutputControlTimestamp::iddObjectType(), model) {
  bool ok = setISO8601Format(false);
  OS_ASSERT(ok);

  ok = setTimestampAtBeginningOfInterval(false);
  OS_ASSERT(ok);
}

OutputControlTimestamp::OutputControlTimestamp(std::shared_ptr<detail::OutputControlTimestamp_Impl> impl) : ModelObject(std::move(impl)) {}

IddObjectType OutputControlTimestamp::iddObjectType() {
  return IddObjectType::OutputControl_Timestamp;
}

bool OutputControlTimestamp::iso8601Format() const {
  return getImpl<detail::OutputControlTimestamp_Impl>()->iso8601Format();
}

bool OutputControlTimestamp::timestampAtBeginningOfInterval() const {
  return getImpl<detail::OutputControlTimestamp_Impl>()->timestampAtBeginningOfInterval();
}

bool OutputControlTimestamp::setISO8601Format(bool iso8601Format) {
  return getImpl<detail::OutputControlTimestamp_Impl>()->setISO8601Format(iso8601Format);
}

bool OutputControlTimestamp::setTimestampAtBeginningOfInterval(bool timestampAtBeginningOfInterval) {
  return getImpl<detail::OutputControlTimestamp_Impl>()->setTimestampAtBeginningOfInterval(timestampAtBeginningOfInterval);
}

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
namespace detail {

namespace {

bool getYesNoFieldValue(const ModelObject_Impl& impl, const int fieldIndex) {
  if (const auto value = impl.getString(fieldIndex, true)) {
    return openstudio::istringEqual(*value, "Yes") || openstudio::istringEqual(*value, "True");
  }
  return false;
}

bool setYesNoFieldValue(ModelObject_Impl& impl, const int fieldIndex, const bool value) {
  const bool result = impl.setString(fieldIndex, value ? "Yes" : "No");
  OS_ASSERT(result);
  return result;
}

}  // namespace

bool OutputControlTimestamp_Impl::iso8601Format() const {
  return getYesNoFieldValue(*this, openstudio::OutputControl_TimestampFields::ISO8601Format);
}

bool OutputControlTimestamp_Impl::timestampAtBeginningOfInterval() const {
  return getYesNoFieldValue(*this, openstudio::OutputControl_TimestampFields::TimestampatBeginningofInterval);
}

bool OutputControlTimestamp_Impl::setISO8601Format(bool iso8601Format) {
  return setYesNoFieldValue(*this, openstudio::OutputControl_TimestampFields::ISO8601Format, iso8601Format);
}

bool OutputControlTimestamp_Impl::setTimestampAtBeginningOfInterval(bool timestampAtBeginningOfInterval) {
  return setYesNoFieldValue(*this, openstudio::OutputControl_TimestampFields::TimestampatBeginningofInterval,
                            timestampAtBeginningOfInterval);
}

}  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
