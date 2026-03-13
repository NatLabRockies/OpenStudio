/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "AirflowNetworkDistributionComponentCoil.hpp"
#include "AirflowNetworkDistributionComponentCoil_Impl.hpp"

#include "Model.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/idd/AirflowNetwork_Distribution_Component_Coil_FieldEnums.hxx>
#include <utilities/idd/IddEnums.hxx>

namespace openstudio {
namespace epmodel {

  AirflowNetworkDistributionComponentCoil::AirflowNetworkDistributionComponentCoil(const Model& model)
    : ModelObject(AirflowNetworkDistributionComponentCoil::iddObjectType(), model) {}

  AirflowNetworkDistributionComponentCoil::AirflowNetworkDistributionComponentCoil(
    std::shared_ptr<detail::AirflowNetworkDistributionComponentCoil_Impl> impl)
    : ModelObject(std::move(impl)) {}

  IddObjectType AirflowNetworkDistributionComponentCoil::iddObjectType() {
    return IddObjectType::AirflowNetwork_Distribution_Component_Coil;
  }

  double AirflowNetworkDistributionComponentCoil::airPathLength() const {
    return getImpl<detail::AirflowNetworkDistributionComponentCoil_Impl>()->airPathLength();
  }

  bool AirflowNetworkDistributionComponentCoil::setAirPathLength(double airPathLength) {
    return getImpl<detail::AirflowNetworkDistributionComponentCoil_Impl>()->setAirPathLength(airPathLength);
  }

  namespace detail {

    double AirflowNetworkDistributionComponentCoil_Impl::airPathLength() const {
      const auto value = getDouble(openstudio::AirflowNetwork_Distribution_Component_CoilFields::AirPathLength, true);
      OS_ASSERT(value);
      return *value;
    }

    bool AirflowNetworkDistributionComponentCoil_Impl::setAirPathLength(double airPathLength) {
      const bool result = setDouble(openstudio::AirflowNetwork_Distribution_Component_CoilFields::AirPathLength, airPathLength);
      OS_ASSERT(result);
      return result;
    }

  }  // namespace detail

  double AirflowNetworkDistributionComponentCoil::airPathHydraulicDiameter() const {
    return getImpl<detail::AirflowNetworkDistributionComponentCoil_Impl>()->airPathHydraulicDiameter();
  }

  bool AirflowNetworkDistributionComponentCoil::setAirPathHydraulicDiameter(double airPathHydraulicDiameter) {
    return getImpl<detail::AirflowNetworkDistributionComponentCoil_Impl>()->setAirPathHydraulicDiameter(airPathHydraulicDiameter);
  }

  namespace detail {

    double AirflowNetworkDistributionComponentCoil_Impl::airPathHydraulicDiameter() const {
      const auto value = getDouble(openstudio::AirflowNetwork_Distribution_Component_CoilFields::AirPathHydraulicDiameter, true);
      OS_ASSERT(value);
      return *value;
    }

    bool AirflowNetworkDistributionComponentCoil_Impl::setAirPathHydraulicDiameter(double airPathHydraulicDiameter) {
      const bool result = setDouble(openstudio::AirflowNetwork_Distribution_Component_CoilFields::AirPathHydraulicDiameter, airPathHydraulicDiameter);
      OS_ASSERT(result);
      return result;
    }

  }  // namespace detail

}  // namespace epmodel
}  // namespace openstudio
