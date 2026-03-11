/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "PythonPluginTrendVariable.hpp"
#include "PythonPluginTrendVariable_Impl.hpp"

#include "Model.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/idd/IddEnums.hxx>
#include <utilities/idd/OS_PythonPlugin_TrendVariable_FieldEnums.hxx>

namespace openstudio {
namespace epmodel {

  PythonPluginTrendVariable::PythonPluginTrendVariable(const Model& model) : ModelObject(PythonPluginTrendVariable::iddObjectType(), model) {
    // Keep the required scalar field populated for strict getter semantics.
    OS_ASSERT(setNumberofTimestepstobeLogged(4));
  }

  PythonPluginTrendVariable::PythonPluginTrendVariable(std::shared_ptr<detail::PythonPluginTrendVariable_Impl> impl) : ModelObject(std::move(impl)) {}

  IddObjectType PythonPluginTrendVariable::iddObjectType() {
    return IddObjectType::OS_PythonPlugin_TrendVariable;
  }

  int PythonPluginTrendVariable::numberofTimestepstobeLogged() const {
    return getImpl<detail::PythonPluginTrendVariable_Impl>()->numberofTimestepstobeLogged();
  }

  bool PythonPluginTrendVariable::setNumberofTimestepstobeLogged(int numberofTimestepstobeLogged) {
    return getImpl<detail::PythonPluginTrendVariable_Impl>()->setNumberofTimestepstobeLogged(numberofTimestepstobeLogged);
  }

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
  namespace detail {

    int PythonPluginTrendVariable_Impl::numberofTimestepstobeLogged() const {
      const auto value = getInt(openstudio::OS_PythonPlugin_TrendVariableFields::NumberofTimestepstobeLogged, true);
      OS_ASSERT(value);
      return *value;
    }

    bool PythonPluginTrendVariable_Impl::setNumberofTimestepstobeLogged(int numberofTimestepstobeLogged) {
      return setInt(openstudio::OS_PythonPlugin_TrendVariableFields::NumberofTimestepstobeLogged, numberofTimestepstobeLogged);
    }

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
