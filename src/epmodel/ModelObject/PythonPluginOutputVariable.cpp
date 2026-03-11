/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "PythonPluginOutputVariable.hpp"
#include "PythonPluginOutputVariable_Impl.hpp"

#include "Model.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/idd/IddFactory.hxx>
#include <utilities/idd/IddEnums.hxx>
#include <utilities/idd/PythonPlugin_OutputVariable_FieldEnums.hxx>

namespace openstudio {
namespace epmodel {

  PythonPluginOutputVariable::PythonPluginOutputVariable(const Model& model) : ModelObject(PythonPluginOutputVariable::iddObjectType(), model) {}

  PythonPluginOutputVariable::PythonPluginOutputVariable(std::shared_ptr<detail::PythonPluginOutputVariable_Impl> impl)
    : ModelObject(std::move(impl)) {}

  IddObjectType PythonPluginOutputVariable::iddObjectType() {
    return IddObjectType::PythonPlugin_OutputVariable;
  }

  std::vector<std::string> PythonPluginOutputVariable::typeofDatainVariableValues() {
    return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(),
                          openstudio::PythonPlugin_OutputVariableFields::TypeofDatainVariable);
  }

  std::vector<std::string> PythonPluginOutputVariable::updateFrequencyValues() {
    return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(), openstudio::PythonPlugin_OutputVariableFields::UpdateFrequency);
  }

  std::vector<std::string> PythonPluginOutputVariable::resourceTypeValues() {
    return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(), openstudio::PythonPlugin_OutputVariableFields::ResourceType);
  }

  std::vector<std::string> PythonPluginOutputVariable::groupTypeValues() {
    return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(), openstudio::PythonPlugin_OutputVariableFields::GroupType);
  }

  std::vector<std::string> PythonPluginOutputVariable::endUseCategoryValues() {
    return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(), openstudio::PythonPlugin_OutputVariableFields::EndUseCategory);
  }

  std::string PythonPluginOutputVariable::typeofDatainVariable() const {
    return getImpl<detail::PythonPluginOutputVariable_Impl>()->typeofDatainVariable();
  }

  std::string PythonPluginOutputVariable::updateFrequency() const {
    return getImpl<detail::PythonPluginOutputVariable_Impl>()->updateFrequency();
  }

  boost::optional<std::string> PythonPluginOutputVariable::units() const {
    return getImpl<detail::PythonPluginOutputVariable_Impl>()->units();
  }

  boost::optional<std::string> PythonPluginOutputVariable::resourceType() const {
    return getImpl<detail::PythonPluginOutputVariable_Impl>()->resourceType();
  }

  boost::optional<std::string> PythonPluginOutputVariable::groupType() const {
    return getImpl<detail::PythonPluginOutputVariable_Impl>()->groupType();
  }

  boost::optional<std::string> PythonPluginOutputVariable::endUseCategory() const {
    return getImpl<detail::PythonPluginOutputVariable_Impl>()->endUseCategory();
  }

  boost::optional<std::string> PythonPluginOutputVariable::endUseSubcategory() const {
    return getImpl<detail::PythonPluginOutputVariable_Impl>()->endUseSubcategory();
  }

  bool PythonPluginOutputVariable::setTypeofDatainVariable(const std::string& typeofDatainVariable) {
    return getImpl<detail::PythonPluginOutputVariable_Impl>()->setTypeofDatainVariable(typeofDatainVariable);
  }

  bool PythonPluginOutputVariable::setUpdateFrequency(const std::string& updateFrequency) {
    return getImpl<detail::PythonPluginOutputVariable_Impl>()->setUpdateFrequency(updateFrequency);
  }

  bool PythonPluginOutputVariable::setUnits(const std::string& units) {
    return getImpl<detail::PythonPluginOutputVariable_Impl>()->setUnits(units);
  }

  void PythonPluginOutputVariable::resetUnits() {
    getImpl<detail::PythonPluginOutputVariable_Impl>()->resetUnits();
  }

  bool PythonPluginOutputVariable::setResourceType(const std::string& resourceType) {
    return getImpl<detail::PythonPluginOutputVariable_Impl>()->setResourceType(resourceType);
  }

  void PythonPluginOutputVariable::resetResourceType() {
    getImpl<detail::PythonPluginOutputVariable_Impl>()->resetResourceType();
  }

  bool PythonPluginOutputVariable::setGroupType(const std::string& groupType) {
    return getImpl<detail::PythonPluginOutputVariable_Impl>()->setGroupType(groupType);
  }

  void PythonPluginOutputVariable::resetGroupType() {
    getImpl<detail::PythonPluginOutputVariable_Impl>()->resetGroupType();
  }

  bool PythonPluginOutputVariable::setEndUseCategory(const std::string& endUseCategory) {
    return getImpl<detail::PythonPluginOutputVariable_Impl>()->setEndUseCategory(endUseCategory);
  }

  void PythonPluginOutputVariable::resetEndUseCategory() {
    getImpl<detail::PythonPluginOutputVariable_Impl>()->resetEndUseCategory();
  }

  bool PythonPluginOutputVariable::setEndUseSubcategory(const std::string& endUseSubcategory) {
    return getImpl<detail::PythonPluginOutputVariable_Impl>()->setEndUseSubcategory(endUseSubcategory);
  }

  void PythonPluginOutputVariable::resetEndUseSubcategory() {
    getImpl<detail::PythonPluginOutputVariable_Impl>()->resetEndUseSubcategory();
  }

  namespace detail {

    std::string PythonPluginOutputVariable_Impl::typeofDatainVariable() const {
      const auto value = getString(openstudio::PythonPlugin_OutputVariableFields::TypeofDatainVariable, true);
      OS_ASSERT(value);
      return *value;
    }

    std::string PythonPluginOutputVariable_Impl::updateFrequency() const {
      const auto value = getString(openstudio::PythonPlugin_OutputVariableFields::UpdateFrequency, true);
      OS_ASSERT(value);
      return *value;
    }

    boost::optional<std::string> PythonPluginOutputVariable_Impl::units() const {
      return getString(openstudio::PythonPlugin_OutputVariableFields::Units, true);
    }

    boost::optional<std::string> PythonPluginOutputVariable_Impl::resourceType() const {
      return getString(openstudio::PythonPlugin_OutputVariableFields::ResourceType, true);
    }

    boost::optional<std::string> PythonPluginOutputVariable_Impl::groupType() const {
      return getString(openstudio::PythonPlugin_OutputVariableFields::GroupType, true);
    }

    boost::optional<std::string> PythonPluginOutputVariable_Impl::endUseCategory() const {
      return getString(openstudio::PythonPlugin_OutputVariableFields::EndUseCategory, true);
    }

    boost::optional<std::string> PythonPluginOutputVariable_Impl::endUseSubcategory() const {
      return getString(openstudio::PythonPlugin_OutputVariableFields::EndUseSubcategory, true);
    }

    bool PythonPluginOutputVariable_Impl::setTypeofDatainVariable(const std::string& typeofDatainVariable) {
      return setString(openstudio::PythonPlugin_OutputVariableFields::TypeofDatainVariable, typeofDatainVariable);
    }

    bool PythonPluginOutputVariable_Impl::setUpdateFrequency(const std::string& updateFrequency) {
      return setString(openstudio::PythonPlugin_OutputVariableFields::UpdateFrequency, updateFrequency);
    }

    bool PythonPluginOutputVariable_Impl::setUnits(const std::string& units) {
      const bool result = setString(openstudio::PythonPlugin_OutputVariableFields::Units, units);
      OS_ASSERT(result);
      return result;
    }

    void PythonPluginOutputVariable_Impl::resetUnits() {
      const bool result = setString(openstudio::PythonPlugin_OutputVariableFields::Units, "");
      OS_ASSERT(result);
    }

    bool PythonPluginOutputVariable_Impl::setResourceType(const std::string& resourceType) {
      return setString(openstudio::PythonPlugin_OutputVariableFields::ResourceType, resourceType);
    }

    void PythonPluginOutputVariable_Impl::resetResourceType() {
      const bool result = setString(openstudio::PythonPlugin_OutputVariableFields::ResourceType, "");
      OS_ASSERT(result);
    }

    bool PythonPluginOutputVariable_Impl::setGroupType(const std::string& groupType) {
      return setString(openstudio::PythonPlugin_OutputVariableFields::GroupType, groupType);
    }

    void PythonPluginOutputVariable_Impl::resetGroupType() {
      const bool result = setString(openstudio::PythonPlugin_OutputVariableFields::GroupType, "");
      OS_ASSERT(result);
    }

    bool PythonPluginOutputVariable_Impl::setEndUseCategory(const std::string& endUseCategory) {
      return setString(openstudio::PythonPlugin_OutputVariableFields::EndUseCategory, endUseCategory);
    }

    void PythonPluginOutputVariable_Impl::resetEndUseCategory() {
      const bool result = setString(openstudio::PythonPlugin_OutputVariableFields::EndUseCategory, "");
      OS_ASSERT(result);
    }

    bool PythonPluginOutputVariable_Impl::setEndUseSubcategory(const std::string& endUseSubcategory) {
      const bool result = setString(openstudio::PythonPlugin_OutputVariableFields::EndUseSubcategory, endUseSubcategory);
      OS_ASSERT(result);
      return result;
    }

    void PythonPluginOutputVariable_Impl::resetEndUseSubcategory() {
      const bool result = setString(openstudio::PythonPlugin_OutputVariableFields::EndUseSubcategory, "");
      OS_ASSERT(result);
    }

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
