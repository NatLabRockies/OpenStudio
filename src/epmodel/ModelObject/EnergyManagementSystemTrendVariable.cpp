/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "EnergyManagementSystemTrendVariable.hpp"
#include "EnergyManagementSystemTrendVariable_Impl.hpp"

#include "Model.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/idd/EnergyManagementSystem_TrendVariable_FieldEnums.hxx>
#include <utilities/idd/IddEnums.hxx>

#include <stdexcept>

namespace openstudio {
namespace epmodel {

  EnergyManagementSystemTrendVariable::EnergyManagementSystemTrendVariable(const Model& model, const std::string& eMSVariableName)
    : ModelObject(EnergyManagementSystemTrendVariable::iddObjectType(), model) {
    OS_ASSERT(getImpl<detail::EnergyManagementSystemTrendVariable_Impl>());
    const bool ok = setEMSVariableName(eMSVariableName);
    if (!ok) {
      remove();
      throw std::runtime_error("Unable to set EnergyManagementSystemTrendVariable EMS Variable Name to '" + eMSVariableName + "'.");
    }

    // Mirror model-side constructor defaults.
    setNumberOfTimestepsToBeLogged(1);
  }

  EnergyManagementSystemTrendVariable::EnergyManagementSystemTrendVariable(std::shared_ptr<detail::EnergyManagementSystemTrendVariable_Impl> impl)
    : ModelObject(std::move(impl)) {}

  IddObjectType EnergyManagementSystemTrendVariable::iddObjectType() {
    return IddObjectType::EnergyManagementSystem_TrendVariable;
  }

  std::string EnergyManagementSystemTrendVariable::emsVariableName() const {
    return getImpl<detail::EnergyManagementSystemTrendVariable_Impl>()->emsVariableName();
  }

  bool EnergyManagementSystemTrendVariable::setEMSVariableName(const std::string& eMSVariableName) {
    return getImpl<detail::EnergyManagementSystemTrendVariable_Impl>()->setEMSVariableName(eMSVariableName);
  }

  int EnergyManagementSystemTrendVariable::numberOfTimestepsToBeLogged() const {
    return getImpl<detail::EnergyManagementSystemTrendVariable_Impl>()->numberOfTimestepsToBeLogged();
  }

  bool EnergyManagementSystemTrendVariable::setNumberOfTimestepsToBeLogged(int numberofTimestepstobeLogged) {
    return getImpl<detail::EnergyManagementSystemTrendVariable_Impl>()->setNumberOfTimestepsToBeLogged(numberofTimestepstobeLogged);
  }

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
  namespace detail {

    std::string EnergyManagementSystemTrendVariable_Impl::emsVariableName() const {
      const auto value = getString(openstudio::EnergyManagementSystem_TrendVariableFields::EMSVariableName, true);
      OS_ASSERT(value);
      return *value;
    }

    bool EnergyManagementSystemTrendVariable_Impl::setEMSVariableName(const std::string& eMSVariableName) {
      return setString(openstudio::EnergyManagementSystem_TrendVariableFields::EMSVariableName, eMSVariableName);
    }

    int EnergyManagementSystemTrendVariable_Impl::numberOfTimestepsToBeLogged() const {
      const auto value = getInt(openstudio::EnergyManagementSystem_TrendVariableFields::NumberofTimestepstobeLogged, true);
      OS_ASSERT(value);
      return *value;
    }

    bool EnergyManagementSystemTrendVariable_Impl::setNumberOfTimestepsToBeLogged(int numberofTimestepstobeLogged) {
      return setInt(openstudio::EnergyManagementSystem_TrendVariableFields::NumberofTimestepstobeLogged, numberofTimestepstobeLogged);
    }

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
