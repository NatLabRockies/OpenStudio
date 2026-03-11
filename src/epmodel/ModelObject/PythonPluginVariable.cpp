/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "PythonPluginVariable.hpp"
#include "PythonPluginVariable_Impl.hpp"

#include "Model.hpp"

#include "ModelObject/PythonPluginOutputVariable.hpp"
#include "ModelObject/PythonPluginTrendVariable.hpp"
#include "ModelObject/PythonPluginOutputVariable_Impl.hpp"
#include "ModelObject/PythonPluginTrendVariable_Impl.hpp"

namespace openstudio {
namespace epmodel {

  PythonPluginVariable::PythonPluginVariable(const Model& model) : ModelObject(PythonPluginVariable::iddObjectType(), model) {}

  IddObjectType PythonPluginVariable::iddObjectType() {
    return IddObjectType::OS_PythonPlugin_Variable;
  }

  std::vector<PythonPluginTrendVariable> PythonPluginVariable::pythonPluginTrendVariables() const {
    return getImpl<detail::PythonPluginVariable_Impl>()->pythonPluginTrendVariables();
  }

  std::vector<PythonPluginOutputVariable> PythonPluginVariable::pythonPluginOutputVariables() const {
    return getImpl<detail::PythonPluginVariable_Impl>()->pythonPluginOutputVariables();
  }

  PythonPluginVariable::PythonPluginVariable(std::shared_ptr<detail::PythonPluginVariable_Impl> impl) : ModelObject(std::move(impl)) {}

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
  namespace detail {

    std::vector<PythonPluginTrendVariable> PythonPluginVariable_Impl::pythonPluginTrendVariables() const {
      std::vector<PythonPluginTrendVariable> result;
      auto sources = getObject<ModelObject>().getSources(PythonPluginTrendVariable::iddObjectType());
      result.reserve(sources.size());
      for (const auto& source : sources) {
        if (auto typed = source.template optionalCast<PythonPluginTrendVariable>()) {
          result.emplace_back(*typed);
        }
      }
      return result;
    }

    std::vector<PythonPluginOutputVariable> PythonPluginVariable_Impl::pythonPluginOutputVariables() const {
      std::vector<PythonPluginOutputVariable> result;
      auto sources = getObject<ModelObject>().getSources(PythonPluginOutputVariable::iddObjectType());
      result.reserve(sources.size());
      for (const auto& source : sources) {
        if (auto typed = source.template optionalCast<PythonPluginOutputVariable>()) {
          result.emplace_back(*typed);
        }
      }
      return result;
    }

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
