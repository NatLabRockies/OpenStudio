/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "ModelObject/OutputTableMonthly.hpp"
#include "ModelObject/OutputTableMonthly_Impl.hpp"

#include "Model.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/idd/IddEnums.hxx>
#include <utilities/idd/Output_Table_Monthly_FieldEnums.hxx>

namespace openstudio {
namespace epmodel {

OutputTableMonthly::OutputTableMonthly(const Model& model) : ModelObject(OutputTableMonthly::iddObjectType(), model) {
  bool ok = setDigitsAfterDecimal(2);
  OS_ASSERT(ok);
}

OutputTableMonthly::OutputTableMonthly(std::shared_ptr<detail::OutputTableMonthly_Impl> impl) : ModelObject(std::move(impl)) {}

IddObjectType OutputTableMonthly::iddObjectType() {
  return IddObjectType::Output_Table_Monthly;
}

int OutputTableMonthly::digitsAfterDecimal() const {
  return getImpl<detail::OutputTableMonthly_Impl>()->digitsAfterDecimal();
}

bool OutputTableMonthly::setDigitsAfterDecimal(int digitsAfterDecimal) {
  return getImpl<detail::OutputTableMonthly_Impl>()->setDigitsAfterDecimal(digitsAfterDecimal);
}

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
namespace detail {

int OutputTableMonthly_Impl::digitsAfterDecimal() const {
  const auto value = getInt(openstudio::Output_Table_MonthlyFields::DigitsAfterDecimal, true);
  OS_ASSERT(value);
  return *value;
}

bool OutputTableMonthly_Impl::setDigitsAfterDecimal(int digitsAfterDecimal) {
  return setInt(openstudio::Output_Table_MonthlyFields::DigitsAfterDecimal, digitsAfterDecimal);
}

}  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
