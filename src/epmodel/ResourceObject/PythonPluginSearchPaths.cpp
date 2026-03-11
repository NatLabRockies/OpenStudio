/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "ResourceObject/PythonPluginSearchPaths.hpp"
#include "ResourceObject/PythonPluginSearchPaths_Impl.hpp"

#include "Model.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/core/StringHelpers.hpp>
#include <utilities/idd/PythonPlugin_SearchPaths_FieldEnums.hxx>
#include <utilities/idd/IddEnums.hxx>

namespace openstudio {
namespace epmodel {

  PythonPluginSearchPaths::PythonPluginSearchPaths(const Model& model) : ModelObject(PythonPluginSearchPaths::iddObjectType(), model) {}

  PythonPluginSearchPaths::PythonPluginSearchPaths(std::shared_ptr<detail::PythonPluginSearchPaths_Impl> impl) : ModelObject(std::move(impl)) {}

  IddObjectType PythonPluginSearchPaths::iddObjectType() {
    return IddObjectType::PythonPlugin_SearchPaths;
  }

  bool PythonPluginSearchPaths::addCurrentWorkingDirectoryToSearchPath() const {
    return getImpl<detail::PythonPluginSearchPaths_Impl>()->addCurrentWorkingDirectoryToSearchPath();
  }

  bool PythonPluginSearchPaths::isAddCurrentWorkingDirectoryToSearchPathDefaulted() const {
    return getImpl<detail::PythonPluginSearchPaths_Impl>()->isAddCurrentWorkingDirectoryToSearchPathDefaulted();
  }

  bool PythonPluginSearchPaths::setAddCurrentWorkingDirectoryToSearchPath(bool addCurrentWorkingDirectoryToSearchPath) {
    return getImpl<detail::PythonPluginSearchPaths_Impl>()->setAddCurrentWorkingDirectoryToSearchPath(addCurrentWorkingDirectoryToSearchPath);
  }

  void PythonPluginSearchPaths::resetAddCurrentWorkingDirectoryToSearchPath() {
    getImpl<detail::PythonPluginSearchPaths_Impl>()->resetAddCurrentWorkingDirectoryToSearchPath();
  }

  bool PythonPluginSearchPaths::addInputFileDirectoryToSearchPath() const {
    return getImpl<detail::PythonPluginSearchPaths_Impl>()->addInputFileDirectoryToSearchPath();
  }

  bool PythonPluginSearchPaths::isAddInputFileDirectoryToSearchPathDefaulted() const {
    return getImpl<detail::PythonPluginSearchPaths_Impl>()->isAddInputFileDirectoryToSearchPathDefaulted();
  }

  bool PythonPluginSearchPaths::setAddInputFileDirectoryToSearchPath(bool addInputFileDirectoryToSearchPath) {
    return getImpl<detail::PythonPluginSearchPaths_Impl>()->setAddInputFileDirectoryToSearchPath(addInputFileDirectoryToSearchPath);
  }

  void PythonPluginSearchPaths::resetAddInputFileDirectoryToSearchPath() {
    getImpl<detail::PythonPluginSearchPaths_Impl>()->resetAddInputFileDirectoryToSearchPath();
  }

  bool PythonPluginSearchPaths::addEpinEnvironmentVariableToSearchPath() const {
    return getImpl<detail::PythonPluginSearchPaths_Impl>()->addEpinEnvironmentVariableToSearchPath();
  }

  bool PythonPluginSearchPaths::isAddEpinEnvironmentVariableToSearchPathDefaulted() const {
    return getImpl<detail::PythonPluginSearchPaths_Impl>()->isAddEpinEnvironmentVariableToSearchPathDefaulted();
  }

  bool PythonPluginSearchPaths::setAddEpinEnvironmentVariableToSearchPath(bool addEpinEnvironmentVariableToSearchPath) {
    return getImpl<detail::PythonPluginSearchPaths_Impl>()->setAddEpinEnvironmentVariableToSearchPath(addEpinEnvironmentVariableToSearchPath);
  }

  void PythonPluginSearchPaths::resetAddEpinEnvironmentVariableToSearchPath() {
    getImpl<detail::PythonPluginSearchPaths_Impl>()->resetAddEpinEnvironmentVariableToSearchPath();
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

    bool PythonPluginSearchPaths_Impl::addCurrentWorkingDirectoryToSearchPath() const {
      return getBooleanFieldValue(*this, openstudio::PythonPlugin_SearchPathsFields::AddCurrentWorkingDirectorytoSearchPath);
    }

    bool PythonPluginSearchPaths_Impl::isAddCurrentWorkingDirectoryToSearchPathDefaulted() const {
      return isEmpty(openstudio::PythonPlugin_SearchPathsFields::AddCurrentWorkingDirectorytoSearchPath);
    }

    bool PythonPluginSearchPaths_Impl::setAddCurrentWorkingDirectoryToSearchPath(bool addCurrentWorkingDirectoryToSearchPath) {
      const bool result = setBooleanFieldValue(*this, openstudio::PythonPlugin_SearchPathsFields::AddCurrentWorkingDirectorytoSearchPath,
                                               addCurrentWorkingDirectoryToSearchPath);
      OS_ASSERT(result);
      return result;
    }

    void PythonPluginSearchPaths_Impl::resetAddCurrentWorkingDirectoryToSearchPath() {
      OS_ASSERT(setString(openstudio::PythonPlugin_SearchPathsFields::AddCurrentWorkingDirectorytoSearchPath, ""));
    }

    bool PythonPluginSearchPaths_Impl::addInputFileDirectoryToSearchPath() const {
      return getBooleanFieldValue(*this, openstudio::PythonPlugin_SearchPathsFields::AddInputFileDirectorytoSearchPath);
    }

    bool PythonPluginSearchPaths_Impl::isAddInputFileDirectoryToSearchPathDefaulted() const {
      return isEmpty(openstudio::PythonPlugin_SearchPathsFields::AddInputFileDirectorytoSearchPath);
    }

    bool PythonPluginSearchPaths_Impl::setAddInputFileDirectoryToSearchPath(bool addInputFileDirectoryToSearchPath) {
      const bool result =
        setBooleanFieldValue(*this, openstudio::PythonPlugin_SearchPathsFields::AddInputFileDirectorytoSearchPath, addInputFileDirectoryToSearchPath);
      OS_ASSERT(result);
      return result;
    }

    void PythonPluginSearchPaths_Impl::resetAddInputFileDirectoryToSearchPath() {
      OS_ASSERT(setString(openstudio::PythonPlugin_SearchPathsFields::AddInputFileDirectorytoSearchPath, ""));
    }

    bool PythonPluginSearchPaths_Impl::addEpinEnvironmentVariableToSearchPath() const {
      return getBooleanFieldValue(*this, openstudio::PythonPlugin_SearchPathsFields::AddepinEnvironmentVariabletoSearchPath);
    }

    bool PythonPluginSearchPaths_Impl::isAddEpinEnvironmentVariableToSearchPathDefaulted() const {
      return isEmpty(openstudio::PythonPlugin_SearchPathsFields::AddepinEnvironmentVariabletoSearchPath);
    }

    bool PythonPluginSearchPaths_Impl::setAddEpinEnvironmentVariableToSearchPath(bool addEpinEnvironmentVariableToSearchPath) {
      const bool result = setBooleanFieldValue(*this, openstudio::PythonPlugin_SearchPathsFields::AddepinEnvironmentVariabletoSearchPath,
                                               addEpinEnvironmentVariableToSearchPath);
      OS_ASSERT(result);
      return result;
    }

    void PythonPluginSearchPaths_Impl::resetAddEpinEnvironmentVariableToSearchPath() {
      OS_ASSERT(setString(openstudio::PythonPlugin_SearchPathsFields::AddepinEnvironmentVariabletoSearchPath, ""));
    }

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
