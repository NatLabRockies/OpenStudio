/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "AirflowNetworkDistributionDuctViewFactors.hpp"
#include "AirflowNetworkDistributionDuctViewFactors_Impl.hpp"

#include "Model.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/idd/AirflowNetwork_Distribution_DuctViewFactors_FieldEnums.hxx>
#include <utilities/idd/IddEnums.hxx>

namespace openstudio {
namespace epmodel {

  AirflowNetworkDistributionDuctViewFactors::AirflowNetworkDistributionDuctViewFactors(const Model& model)
    : ModelObject(AirflowNetworkDistributionDuctViewFactors::iddObjectType(), model) {}

  AirflowNetworkDistributionDuctViewFactors::AirflowNetworkDistributionDuctViewFactors(
    std::shared_ptr<detail::AirflowNetworkDistributionDuctViewFactors_Impl> impl)
    : ModelObject(std::move(impl)) {}

  IddObjectType AirflowNetworkDistributionDuctViewFactors::iddObjectType() {
    return IddObjectType::AirflowNetwork_Distribution_DuctViewFactors;
  }

  double AirflowNetworkDistributionDuctViewFactors::ductSurfaceExposureFraction() const {
    return getImpl<detail::AirflowNetworkDistributionDuctViewFactors_Impl>()->ductSurfaceExposureFraction();
  }

  bool AirflowNetworkDistributionDuctViewFactors::isDuctSurfaceExposureFractionDefaulted() const {
    return getImpl<detail::AirflowNetworkDistributionDuctViewFactors_Impl>()->isDuctSurfaceExposureFractionDefaulted();
  }

  bool AirflowNetworkDistributionDuctViewFactors::setDuctSurfaceExposureFraction(double ductSurfaceExposureFraction) {
    return getImpl<detail::AirflowNetworkDistributionDuctViewFactors_Impl>()->setDuctSurfaceExposureFraction(ductSurfaceExposureFraction);
  }

  void AirflowNetworkDistributionDuctViewFactors::resetDuctSurfaceExposureFraction() {
    getImpl<detail::AirflowNetworkDistributionDuctViewFactors_Impl>()->resetDuctSurfaceExposureFraction();
  }

  double AirflowNetworkDistributionDuctViewFactors::ductSurfaceEmittance() const {
    return getImpl<detail::AirflowNetworkDistributionDuctViewFactors_Impl>()->ductSurfaceEmittance();
  }

  bool AirflowNetworkDistributionDuctViewFactors::isDuctSurfaceEmittanceDefaulted() const {
    return getImpl<detail::AirflowNetworkDistributionDuctViewFactors_Impl>()->isDuctSurfaceEmittanceDefaulted();
  }

  bool AirflowNetworkDistributionDuctViewFactors::setDuctSurfaceEmittance(double ductSurfaceEmittance) {
    return getImpl<detail::AirflowNetworkDistributionDuctViewFactors_Impl>()->setDuctSurfaceEmittance(ductSurfaceEmittance);
  }

  void AirflowNetworkDistributionDuctViewFactors::resetDuctSurfaceEmittance() {
    getImpl<detail::AirflowNetworkDistributionDuctViewFactors_Impl>()->resetDuctSurfaceEmittance();
  }

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
  namespace detail {

    double AirflowNetworkDistributionDuctViewFactors_Impl::ductSurfaceExposureFraction() const {
      const auto value = getDouble(openstudio::AirflowNetwork_Distribution_DuctViewFactorsFields::DuctSurfaceExposureFraction, true);
      OS_ASSERT(value);
      return *value;
    }

    bool AirflowNetworkDistributionDuctViewFactors_Impl::isDuctSurfaceExposureFractionDefaulted() const {
      return isEmpty(openstudio::AirflowNetwork_Distribution_DuctViewFactorsFields::DuctSurfaceExposureFraction);
    }

    bool AirflowNetworkDistributionDuctViewFactors_Impl::setDuctSurfaceExposureFraction(double ductSurfaceExposureFraction) {
      return setDouble(openstudio::AirflowNetwork_Distribution_DuctViewFactorsFields::DuctSurfaceExposureFraction, ductSurfaceExposureFraction);
    }

    void AirflowNetworkDistributionDuctViewFactors_Impl::resetDuctSurfaceExposureFraction() {
      OS_ASSERT(setString(openstudio::AirflowNetwork_Distribution_DuctViewFactorsFields::DuctSurfaceExposureFraction, ""));
    }

    double AirflowNetworkDistributionDuctViewFactors_Impl::ductSurfaceEmittance() const {
      const auto value = getDouble(openstudio::AirflowNetwork_Distribution_DuctViewFactorsFields::DuctSurfaceEmittance, true);
      OS_ASSERT(value);
      return *value;
    }

    bool AirflowNetworkDistributionDuctViewFactors_Impl::isDuctSurfaceEmittanceDefaulted() const {
      return isEmpty(openstudio::AirflowNetwork_Distribution_DuctViewFactorsFields::DuctSurfaceEmittance);
    }

    bool AirflowNetworkDistributionDuctViewFactors_Impl::setDuctSurfaceEmittance(double ductSurfaceEmittance) {
      return setDouble(openstudio::AirflowNetwork_Distribution_DuctViewFactorsFields::DuctSurfaceEmittance, ductSurfaceEmittance);
    }

    void AirflowNetworkDistributionDuctViewFactors_Impl::resetDuctSurfaceEmittance() {
      OS_ASSERT(setString(openstudio::AirflowNetwork_Distribution_DuctViewFactorsFields::DuctSurfaceEmittance, ""));
    }

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
