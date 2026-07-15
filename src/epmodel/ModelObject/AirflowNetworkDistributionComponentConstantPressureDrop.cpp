/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "AirflowNetworkDistributionComponentConstantPressureDrop.hpp"
#include "AirflowNetworkDistributionComponentConstantPressureDrop_Impl.hpp"

#include "Model.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/idd/AirflowNetwork_Distribution_Component_ConstantPressureDrop_FieldEnums.hxx>
#include <utilities/idd/IddEnums.hxx>

namespace openstudio {
namespace epmodel {

  AirflowNetworkDistributionComponentConstantPressureDrop::AirflowNetworkDistributionComponentConstantPressureDrop(const Model& model)
    : ModelObject(AirflowNetworkDistributionComponentConstantPressureDrop::iddObjectType(), model) {}

  AirflowNetworkDistributionComponentConstantPressureDrop::AirflowNetworkDistributionComponentConstantPressureDrop(
    std::shared_ptr<detail::AirflowNetworkDistributionComponentConstantPressureDrop_Impl> impl)
    : ModelObject(std::move(impl)) {}

  IddObjectType AirflowNetworkDistributionComponentConstantPressureDrop::iddObjectType() {
    return IddObjectType::AirflowNetwork_Distribution_Component_ConstantPressureDrop;
  }

  double AirflowNetworkDistributionComponentConstantPressureDrop::pressureDifferenceAcrosstheComponent() const {
    return getImpl<detail::AirflowNetworkDistributionComponentConstantPressureDrop_Impl>()->pressureDifferenceAcrosstheComponent();
  }

  bool AirflowNetworkDistributionComponentConstantPressureDrop::setPressureDifferenceAcrosstheComponent(double pressureDifferenceAcrosstheComponent) {
    return getImpl<detail::AirflowNetworkDistributionComponentConstantPressureDrop_Impl>()->setPressureDifferenceAcrosstheComponent(
      pressureDifferenceAcrosstheComponent);
  }

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
  namespace detail {

    double AirflowNetworkDistributionComponentConstantPressureDrop_Impl::pressureDifferenceAcrosstheComponent() const {
      const auto value =
        getDouble(openstudio::AirflowNetwork_Distribution_Component_ConstantPressureDropFields::PressureDifferenceAcrosstheComponent, true);
      OS_ASSERT(value);
      return *value;
    }

    bool AirflowNetworkDistributionComponentConstantPressureDrop_Impl::setPressureDifferenceAcrosstheComponent(
      double pressureDifferenceAcrosstheComponent) {
      const bool result =
        setDouble(openstudio::AirflowNetwork_Distribution_Component_ConstantPressureDropFields::PressureDifferenceAcrosstheComponent,
                  pressureDifferenceAcrosstheComponent);
      OS_ASSERT(result);
      return result;
    }

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
