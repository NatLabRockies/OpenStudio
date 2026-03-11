/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "ResourceObject/SurfacePropertyOtherSideConditionsModel.hpp"
#include "ResourceObject/SurfacePropertyOtherSideConditionsModel_Impl.hpp"

#include "Model.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/idd/IddFactory.hxx>
#include <utilities/idd/IddEnums.hxx>
#include <utilities/idd/OS_SurfaceProperty_OtherSideConditionsModel_FieldEnums.hxx>

namespace openstudio {
namespace epmodel {

  namespace detail {

    std::string SurfacePropertyOtherSideConditionsModel_Impl::typeOfModeling() const {
      auto value = getString(OS_SurfaceProperty_OtherSideConditionsModelFields::TypeofModeling, true);
      OS_ASSERT(value);
      return value.get();
    }

    bool SurfacePropertyOtherSideConditionsModel_Impl::isTypeOfModelingDefaulted() const {
      return isEmpty(OS_SurfaceProperty_OtherSideConditionsModelFields::TypeofModeling);
    }

    bool SurfacePropertyOtherSideConditionsModel_Impl::setTypeOfModeling(const std::string& typeOfModeling) {
      return setString(OS_SurfaceProperty_OtherSideConditionsModelFields::TypeofModeling, typeOfModeling);
    }

    void SurfacePropertyOtherSideConditionsModel_Impl::resetTypeOfModeling() {
      const bool result = setString(OS_SurfaceProperty_OtherSideConditionsModelFields::TypeofModeling, "");
      OS_ASSERT(result);
    }

  }  // namespace detail

  SurfacePropertyOtherSideConditionsModel::SurfacePropertyOtherSideConditionsModel(const Model& model)
    : ModelObject(SurfacePropertyOtherSideConditionsModel::iddObjectType(), model) {
    OS_ASSERT(getImpl<detail::SurfacePropertyOtherSideConditionsModel_Impl>());
  }

  IddObjectType SurfacePropertyOtherSideConditionsModel::iddObjectType() {
    return IddObjectType::OS_SurfaceProperty_OtherSideConditionsModel;
  }

  std::vector<std::string> SurfacePropertyOtherSideConditionsModel::typeOfModelingValues() {
    return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(), OS_SurfaceProperty_OtherSideConditionsModelFields::TypeofModeling);
  }

  std::string SurfacePropertyOtherSideConditionsModel::typeOfModeling() const {
    return getImpl<detail::SurfacePropertyOtherSideConditionsModel_Impl>()->typeOfModeling();
  }

  bool SurfacePropertyOtherSideConditionsModel::isTypeOfModelingDefaulted() const {
    return getImpl<detail::SurfacePropertyOtherSideConditionsModel_Impl>()->isTypeOfModelingDefaulted();
  }

  bool SurfacePropertyOtherSideConditionsModel::setTypeOfModeling(const std::string& typeOfModeling) {
    return getImpl<detail::SurfacePropertyOtherSideConditionsModel_Impl>()->setTypeOfModeling(typeOfModeling);
  }

  void SurfacePropertyOtherSideConditionsModel::resetTypeOfModeling() {
    getImpl<detail::SurfacePropertyOtherSideConditionsModel_Impl>()->resetTypeOfModeling();
  }

  SurfacePropertyOtherSideConditionsModel::SurfacePropertyOtherSideConditionsModel(
    std::shared_ptr<detail::SurfacePropertyOtherSideConditionsModel_Impl> impl)
    : ModelObject(std::move(impl)) {}

}  // namespace epmodel
}  // namespace openstudio
