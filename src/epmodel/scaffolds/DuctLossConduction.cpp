/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "DuctLossConduction.hpp"
#include "DuctLossConduction_Impl.hpp"

#include "Model.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/idd/Duct_Loss_Conduction_FieldEnums.hxx>
#include <utilities/idd/IddEnums.hxx>
#include <utilities/idd/IddFactory.hxx>
#include <utilities/idd/IddObject.hpp>

namespace openstudio {
namespace epmodel {

  DuctLossConduction::DuctLossConduction(const Model& model) : ModelObject(DuctLossConduction::iddObjectType(), model) {}

  DuctLossConduction::DuctLossConduction(std::shared_ptr<detail::DuctLossConduction_Impl> impl) : ModelObject(std::move(impl)) {}

  IddObjectType DuctLossConduction::iddObjectType() {
    return IddObjectType::Duct_Loss_Conduction;
  }

  std::vector<std::string> DuctLossConduction::environmentTypeValues() {
    return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(), openstudio::Duct_Loss_ConductionFields::EnvironmentType);
  }

  std::string DuctLossConduction::environmentType() const {
    return getImpl<detail::DuctLossConduction_Impl>()->environmentType();
  }

  bool DuctLossConduction::setEnvironmentType(const std::string& environmentType) {
    return getImpl<detail::DuctLossConduction_Impl>()->setEnvironmentType(environmentType);
  }

  bool DuctLossConduction::isEnvironmentTypeDefaulted() const {
    return getImpl<detail::DuctLossConduction_Impl>()->isEnvironmentTypeDefaulted();
  }

  void DuctLossConduction::resetEnvironmentType() {
    getImpl<detail::DuctLossConduction_Impl>()->resetEnvironmentType();
  }

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
  namespace detail {

    std::string DuctLossConduction_Impl::environmentType() const {
      const auto value = getString(openstudio::Duct_Loss_ConductionFields::EnvironmentType, true);
      OS_ASSERT(value);
      return *value;
    }

    bool DuctLossConduction_Impl::setEnvironmentType(const std::string& environmentType) {
      return setString(openstudio::Duct_Loss_ConductionFields::EnvironmentType, environmentType);
    }

    bool DuctLossConduction_Impl::isEnvironmentTypeDefaulted() const {
      return isEmpty(openstudio::Duct_Loss_ConductionFields::EnvironmentType);
    }

    void DuctLossConduction_Impl::resetEnvironmentType() {
      OS_ASSERT(setString(openstudio::Duct_Loss_ConductionFields::EnvironmentType, ""));
    }

    std::vector<std::string> DuctLossConduction_Impl::environmentTypeValues() const {
      return openstudio::epmodel::DuctLossConduction::environmentTypeValues();
    }

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
