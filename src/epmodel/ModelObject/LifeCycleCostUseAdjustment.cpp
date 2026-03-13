/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "LifeCycleCostUseAdjustment.hpp"
#include "LifeCycleCostUseAdjustment_Impl.hpp"

#include "Model.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/idd/IddEnums.hxx>
#include <utilities/idd/IddFactory.hxx>
#include <utilities/idd/IddObject.hpp>
#include <utilities/idd/LifeCycleCost_UseAdjustment_FieldEnums.hxx>

namespace openstudio {
namespace epmodel {

  LifeCycleCostUseAdjustment::LifeCycleCostUseAdjustment(const Model& model) : ModelObject(LifeCycleCostUseAdjustment::iddObjectType(), model) {}

  LifeCycleCostUseAdjustment::LifeCycleCostUseAdjustment(std::shared_ptr<detail::LifeCycleCostUseAdjustment_Impl> impl)
    : ModelObject(std::move(impl)) {}

  IddObjectType LifeCycleCostUseAdjustment::iddObjectType() {
    return IddObjectType::LifeCycleCost_UseAdjustment;
  }

  std::vector<std::string> LifeCycleCostUseAdjustment::resourceValues() {
    return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(), openstudio::LifeCycleCost_UseAdjustmentFields::Resource);
  }

  std::string LifeCycleCostUseAdjustment::resource() const {
    return getImpl<detail::LifeCycleCostUseAdjustment_Impl>()->resource();
  }

  bool LifeCycleCostUseAdjustment::setResource(const std::string& resource) {
    return getImpl<detail::LifeCycleCostUseAdjustment_Impl>()->setResource(resource);
  }

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
  namespace detail {

    std::vector<std::string> LifeCycleCostUseAdjustment_Impl::resourceValues() const {
      return openstudio::epmodel::LifeCycleCostUseAdjustment::resourceValues();
    }

    std::string LifeCycleCostUseAdjustment_Impl::resource() const {
      const auto value = getString(openstudio::LifeCycleCost_UseAdjustmentFields::Resource, true);
      OS_ASSERT(value);
      return *value;
    }

    bool LifeCycleCostUseAdjustment_Impl::setResource(const std::string& resource) {
      return setString(openstudio::LifeCycleCost_UseAdjustmentFields::Resource, resource);
    }

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
