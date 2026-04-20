/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "OutputVariableDictionary.hpp"
#include "OutputVariableDictionary_Impl.hpp"

#include "Model.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/idd/IddEnums.hxx>
#include <utilities/idd/IddFactory.hxx>
#include <utilities/idd/IddObject.hpp>
#include <utilities/idd/Output_VariableDictionary_FieldEnums.hxx>

namespace openstudio {
namespace epmodel {

  OutputVariableDictionary::OutputVariableDictionary(const Model& model) : ModelObject(OutputVariableDictionary::iddObjectType(), model) {}

  OutputVariableDictionary::OutputVariableDictionary(std::shared_ptr<detail::OutputVariableDictionary_Impl> impl) : ModelObject(std::move(impl)) {}

  IddObjectType OutputVariableDictionary::iddObjectType() {
    return IddObjectType::Output_VariableDictionary;
  }

  std::vector<std::string> OutputVariableDictionary::keyFieldValues() {
    return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(), openstudio::Output_VariableDictionaryFields::KeyField);
  }

  std::vector<std::string> OutputVariableDictionary::sortOptionValues() {
    return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(), openstudio::Output_VariableDictionaryFields::SortOption);
  }

  std::string OutputVariableDictionary::keyField() const {
    return getImpl<detail::OutputVariableDictionary_Impl>()->keyField();
  }

  bool OutputVariableDictionary::isKeyFieldDefaulted() const {
    return getImpl<detail::OutputVariableDictionary_Impl>()->isKeyFieldDefaulted();
  }

  boost::optional<std::string> OutputVariableDictionary::sortOption() const {
    return getImpl<detail::OutputVariableDictionary_Impl>()->sortOption();
  }

  bool OutputVariableDictionary::setKeyField(const std::string& keyField) {
    return getImpl<detail::OutputVariableDictionary_Impl>()->setKeyField(keyField);
  }

  void OutputVariableDictionary::resetKeyField() {
    getImpl<detail::OutputVariableDictionary_Impl>()->resetKeyField();
  }

  bool OutputVariableDictionary::setSortOption(const std::string& sortOption) {
    return getImpl<detail::OutputVariableDictionary_Impl>()->setSortOption(sortOption);
  }

  void OutputVariableDictionary::resetSortOption() {
    getImpl<detail::OutputVariableDictionary_Impl>()->resetSortOption();
  }

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
  namespace detail {

    std::string OutputVariableDictionary_Impl::keyField() const {
      const auto value = getString(openstudio::Output_VariableDictionaryFields::KeyField, true);
      OS_ASSERT(value);
      return *value;
    }

    bool OutputVariableDictionary_Impl::isKeyFieldDefaulted() const {
      return isEmpty(openstudio::Output_VariableDictionaryFields::KeyField);
    }

    bool OutputVariableDictionary_Impl::setKeyField(const std::string& keyField) {
      return setString(openstudio::Output_VariableDictionaryFields::KeyField, keyField);
    }

    void OutputVariableDictionary_Impl::resetKeyField() {
      const bool result = setString(openstudio::Output_VariableDictionaryFields::KeyField, "");
      OS_ASSERT(result);
    }

    bool OutputVariableDictionary_Impl::setSortOption(const std::string& sortOption) {
      return setString(openstudio::Output_VariableDictionaryFields::SortOption, sortOption);
    }

    void OutputVariableDictionary_Impl::resetSortOption() {
      const bool result = setString(openstudio::Output_VariableDictionaryFields::SortOption, "");
      OS_ASSERT(result);
    }

    boost::optional<std::string> OutputVariableDictionary_Impl::sortOption() const {
      return getString(openstudio::Output_VariableDictionaryFields::SortOption, true);
    }

    std::vector<std::string> OutputVariableDictionary_Impl::keyFieldValues() const {
      return openstudio::epmodel::OutputVariableDictionary::keyFieldValues();
    }

    std::vector<std::string> OutputVariableDictionary_Impl::sortOptionValues() const {
      return openstudio::epmodel::OutputVariableDictionary::sortOptionValues();
    }

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
