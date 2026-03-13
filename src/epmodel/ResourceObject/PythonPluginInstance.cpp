/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "ResourceObject/PythonPluginInstance.hpp"
#include "ResourceObject/PythonPluginInstance_Impl.hpp"

#include "Model.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/core/StringHelpers.hpp>
#include <utilities/idd/IddEnums.hxx>
#include <utilities/idd/PythonPlugin_Instance_FieldEnums.hxx>

namespace openstudio {
namespace epmodel {

  PythonPluginInstance::PythonPluginInstance(const Model& model) : ModelObject(PythonPluginInstance::iddObjectType(), model) {}

  PythonPluginInstance::PythonPluginInstance(std::shared_ptr<detail::PythonPluginInstance_Impl> impl) : ModelObject(std::move(impl)) {}

  IddObjectType PythonPluginInstance::iddObjectType() {
    return IddObjectType::PythonPlugin_Instance;
  }

  bool PythonPluginInstance::runDuringWarmupDays() const {
    return getImpl<detail::PythonPluginInstance_Impl>()->runDuringWarmupDays();
  }

  bool PythonPluginInstance::setRunDuringWarmupDays(bool runDuringWarmupDays) {
    return getImpl<detail::PythonPluginInstance_Impl>()->setRunDuringWarmupDays(runDuringWarmupDays);
  }

  bool PythonPluginInstance::isRunDuringWarmupDaysDefaulted() const {
    return getImpl<detail::PythonPluginInstance_Impl>()->isRunDuringWarmupDaysDefaulted();
  }

  void PythonPluginInstance::resetRunDuringWarmupDays() {
    getImpl<detail::PythonPluginInstance_Impl>()->resetRunDuringWarmupDays();
  }

  std::string PythonPluginInstance::pythonModuleName() const {
    return getImpl<detail::PythonPluginInstance_Impl>()->pythonModuleName();
  }

  bool PythonPluginInstance::setPythonModuleName(const std::string& pythonModuleName) {
    return getImpl<detail::PythonPluginInstance_Impl>()->setPythonModuleName(pythonModuleName);
  }

  std::string PythonPluginInstance::pluginClassName() const {
    return getImpl<detail::PythonPluginInstance_Impl>()->pluginClassName();
  }

  bool PythonPluginInstance::setPluginClassName(const std::string& pluginClassName) {
    return getImpl<detail::PythonPluginInstance_Impl>()->setPluginClassName(pluginClassName);
  }

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
  namespace detail {

    namespace {

      bool getBooleanFieldValue(const ModelObject_Impl& impl, int fieldIndex) {
        const auto value = impl.getString(fieldIndex, true);
        OS_ASSERT(value);
        return openstudio::istringEqual(*value, "Yes");
      }

      bool setBooleanFieldValue(ModelObject_Impl& impl, int fieldIndex, bool value) {
        return impl.setString(fieldIndex, value ? "Yes" : "No");
      }

    }  // namespace

    bool PythonPluginInstance_Impl::runDuringWarmupDays() const {
      return getBooleanFieldValue(*this, openstudio::PythonPlugin_InstanceFields::RunDuringWarmupDays);
    }

    bool PythonPluginInstance_Impl::setRunDuringWarmupDays(bool runDuringWarmupDays) {
      const bool result = setBooleanFieldValue(*this, openstudio::PythonPlugin_InstanceFields::RunDuringWarmupDays, runDuringWarmupDays);
      OS_ASSERT(result);
      return result;
    }

    bool PythonPluginInstance_Impl::isRunDuringWarmupDaysDefaulted() const {
      return isEmpty(openstudio::PythonPlugin_InstanceFields::RunDuringWarmupDays);
    }

    void PythonPluginInstance_Impl::resetRunDuringWarmupDays() {
      OS_ASSERT(setString(openstudio::PythonPlugin_InstanceFields::RunDuringWarmupDays, ""));
    }

    std::string PythonPluginInstance_Impl::pythonModuleName() const {
      const auto value = getString(openstudio::PythonPlugin_InstanceFields::PythonModuleName, true);
      OS_ASSERT(value);
      return *value;
    }

    bool PythonPluginInstance_Impl::setPythonModuleName(const std::string& pythonModuleName) {
      return setString(openstudio::PythonPlugin_InstanceFields::PythonModuleName, pythonModuleName);
    }

    std::string PythonPluginInstance_Impl::pluginClassName() const {
      const auto value = getString(openstudio::PythonPlugin_InstanceFields::PluginClassName, true);
      OS_ASSERT(value);
      return *value;
    }

    bool PythonPluginInstance_Impl::setPluginClassName(const std::string& pluginClassName) {
      return setString(openstudio::PythonPlugin_InstanceFields::PluginClassName, pluginClassName);
    }

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
