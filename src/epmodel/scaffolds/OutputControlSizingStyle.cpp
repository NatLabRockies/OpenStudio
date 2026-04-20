/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "OutputControlSizingStyle.hpp"
#include "OutputControlSizingStyle_Impl.hpp"

#include "Model.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/idd/IddEnums.hxx>
#include <utilities/idd/IddFactory.hxx>
#include <utilities/idd/IddObject.hpp>
#include <utilities/idd/OutputControl_Sizing_Style_FieldEnums.hxx>

namespace openstudio {
namespace epmodel {

OutputControlSizingStyle::OutputControlSizingStyle(const Model& model) : ModelObject(OutputControlSizingStyle::iddObjectType(), model) {
  const bool ok = setColumnSeparator("Comma");
  OS_ASSERT(ok);
}

OutputControlSizingStyle::OutputControlSizingStyle(std::shared_ptr<detail::OutputControlSizingStyle_Impl> impl)
  : ModelObject(std::move(impl)) {}

IddObjectType OutputControlSizingStyle::iddObjectType() {
  return IddObjectType::OutputControl_Sizing_Style;
}

std::vector<std::string> OutputControlSizingStyle::columnSeparatorValues() {
  return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(), openstudio::OutputControl_Sizing_StyleFields::ColumnSeparator);
}

std::string OutputControlSizingStyle::columnSeparator() const {
  return getImpl<detail::OutputControlSizingStyle_Impl>()->columnSeparator();
}

bool OutputControlSizingStyle::setColumnSeparator(const std::string& columnSeparator) {
  return getImpl<detail::OutputControlSizingStyle_Impl>()->setColumnSeparator(columnSeparator);
}

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
namespace detail {

std::string OutputControlSizingStyle_Impl::columnSeparator() const {
  const auto value = getString(openstudio::OutputControl_Sizing_StyleFields::ColumnSeparator, true);
  OS_ASSERT(value);
  return *value;
}

bool OutputControlSizingStyle_Impl::setColumnSeparator(const std::string& columnSeparator) {
  return setString(openstudio::OutputControl_Sizing_StyleFields::ColumnSeparator, columnSeparator);
}

std::vector<std::string> OutputControlSizingStyle_Impl::columnSeparatorValues() const {
  return openstudio::epmodel::OutputControlSizingStyle::columnSeparatorValues();
}

}  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
