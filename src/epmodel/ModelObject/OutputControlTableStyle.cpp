/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "OutputControlTableStyle.hpp"
#include "OutputControlTableStyle_Impl.hpp"

#include "Model.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/idd/IddEnums.hxx>
#include <utilities/idd/IddFactory.hxx>
#include <utilities/idd/IddObject.hpp>
#include <utilities/idd/OutputControl_Table_Style_FieldEnums.hxx>

namespace openstudio {
namespace epmodel {

OutputControlTableStyle::OutputControlTableStyle(const Model& model) : ModelObject(OutputControlTableStyle::iddObjectType(), model) {
  bool ok = setColumnSeparator("HTML");
  OS_ASSERT(ok);

  ok = setUnitConversion("None");
  OS_ASSERT(ok);
}

OutputControlTableStyle::OutputControlTableStyle(std::shared_ptr<detail::OutputControlTableStyle_Impl> impl) : ModelObject(std::move(impl)) {}

IddObjectType OutputControlTableStyle::iddObjectType() {
  return IddObjectType::OutputControl_Table_Style;
}

std::vector<std::string> OutputControlTableStyle::columnSeparatorValues() {
  return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(), openstudio::OutputControl_Table_StyleFields::ColumnSeparator);
}

std::vector<std::string> OutputControlTableStyle::unitConversionValues() {
  return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(), openstudio::OutputControl_Table_StyleFields::UnitConversion);
}

std::string OutputControlTableStyle::columnSeparator() const {
  return getImpl<detail::OutputControlTableStyle_Impl>()->columnSeparator();
}

std::string OutputControlTableStyle::unitConversion() const {
  return getImpl<detail::OutputControlTableStyle_Impl>()->unitConversion();
}

bool OutputControlTableStyle::setColumnSeparator(const std::string& columnSeparator) {
  return getImpl<detail::OutputControlTableStyle_Impl>()->setColumnSeparator(columnSeparator);
}

bool OutputControlTableStyle::setUnitConversion(const std::string& unitConversion) {
  return getImpl<detail::OutputControlTableStyle_Impl>()->setUnitConversion(unitConversion);
}

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
namespace detail {

std::string OutputControlTableStyle_Impl::columnSeparator() const {
  const auto value = getString(openstudio::OutputControl_Table_StyleFields::ColumnSeparator, true);
  OS_ASSERT(value);
  return *value;
}

std::string OutputControlTableStyle_Impl::unitConversion() const {
  const auto value = getString(openstudio::OutputControl_Table_StyleFields::UnitConversion, true);
  OS_ASSERT(value);
  return *value;
}

bool OutputControlTableStyle_Impl::setColumnSeparator(const std::string& columnSeparator) {
  return setString(openstudio::OutputControl_Table_StyleFields::ColumnSeparator, columnSeparator);
}

bool OutputControlTableStyle_Impl::setUnitConversion(const std::string& unitConversion) {
  return setString(openstudio::OutputControl_Table_StyleFields::UnitConversion, unitConversion);
}

std::vector<std::string> OutputControlTableStyle_Impl::columnSeparatorValues() const {
  return openstudio::epmodel::OutputControlTableStyle::columnSeparatorValues();
}

std::vector<std::string> OutputControlTableStyle_Impl::unitConversionValues() const {
  return openstudio::epmodel::OutputControlTableStyle::unitConversionValues();
}

}  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
