/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "ModelObject/OutputSQLite.hpp"
#include "ModelObject/OutputSQLite_Impl.hpp"

#include "Model.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/idd/IddEnums.hxx>
#include <utilities/idd/IddFactory.hxx>
#include <utilities/idd/IddObject.hpp>
#include <utilities/idd/Output_SQLite_FieldEnums.hxx>

namespace openstudio {
namespace epmodel {

  OutputSQLite::OutputSQLite(const Model& model) : ModelObject(OutputSQLite::iddObjectType(), model) {
    bool ok = setOptionType("SimpleAndTabular");
    OS_ASSERT(ok);

    ok = setUnitConversionforTabularData("UseOutputControlTableStyle");
    OS_ASSERT(ok);
  }

  OutputSQLite::OutputSQLite(std::shared_ptr<detail::OutputSQLite_Impl> impl) : ModelObject(std::move(impl)) {}

  IddObjectType OutputSQLite::iddObjectType() {
    return IddObjectType::Output_SQLite;
  }

  std::vector<std::string> OutputSQLite::optionTypeValues() {
    return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(), openstudio::Output_SQLiteFields::OptionType);
  }

  std::vector<std::string> OutputSQLite::unitConversionforTabularDataValues() {
    return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(), openstudio::Output_SQLiteFields::UnitConversionforTabularData);
  }

  std::string OutputSQLite::optionType() const {
    return getImpl<detail::OutputSQLite_Impl>()->optionType();
  }

  std::string OutputSQLite::unitConversionforTabularData() const {
    return getImpl<detail::OutputSQLite_Impl>()->unitConversionforTabularData();
  }

  bool OutputSQLite::setOptionType(const std::string& optionType) {
    return getImpl<detail::OutputSQLite_Impl>()->setOptionType(optionType);
  }

  bool OutputSQLite::setUnitConversionforTabularData(const std::string& unitConversionforTabularData) {
    return getImpl<detail::OutputSQLite_Impl>()->setUnitConversionforTabularData(unitConversionforTabularData);
  }

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
  namespace detail {

    std::string OutputSQLite_Impl::optionType() const {
      const auto value = getString(openstudio::Output_SQLiteFields::OptionType, true);
      OS_ASSERT(value);
      return *value;
    }

    bool OutputSQLite_Impl::setOptionType(const std::string& optionType) {
      return setString(openstudio::Output_SQLiteFields::OptionType, optionType);
    }

    bool OutputSQLite_Impl::setUnitConversionforTabularData(const std::string& unitConversionforTabularData) {
      return setString(openstudio::Output_SQLiteFields::UnitConversionforTabularData, unitConversionforTabularData);
    }

    std::string OutputSQLite_Impl::unitConversionforTabularData() const {
      const auto value = getString(openstudio::Output_SQLiteFields::UnitConversionforTabularData, true);
      OS_ASSERT(value);
      return *value;
    }

    std::vector<std::string> OutputSQLite_Impl::optionTypeValues() const {
      return openstudio::epmodel::OutputSQLite::optionTypeValues();
    }

    std::vector<std::string> OutputSQLite_Impl::unitConversionforTabularDataValues() const {
      return openstudio::epmodel::OutputSQLite::unitConversionforTabularDataValues();
    }

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
