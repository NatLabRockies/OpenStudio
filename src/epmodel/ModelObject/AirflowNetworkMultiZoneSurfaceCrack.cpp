/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "AirflowNetworkMultiZoneSurfaceCrack.hpp"
#include "AirflowNetworkMultiZoneSurfaceCrack_Impl.hpp"

#include "Model.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/idd/AirflowNetwork_MultiZone_Surface_Crack_FieldEnums.hxx>
#include <utilities/idd/IddEnums.hxx>

namespace openstudio {
namespace epmodel {

  AirflowNetworkMultiZoneSurfaceCrack::AirflowNetworkMultiZoneSurfaceCrack(const Model& model)
    : ModelObject(AirflowNetworkMultiZoneSurfaceCrack::iddObjectType(), model) {}

  AirflowNetworkMultiZoneSurfaceCrack::AirflowNetworkMultiZoneSurfaceCrack(std::shared_ptr<detail::AirflowNetworkMultiZoneSurfaceCrack_Impl> impl)
    : ModelObject(std::move(impl)) {}

  IddObjectType AirflowNetworkMultiZoneSurfaceCrack::iddObjectType() {
    return IddObjectType::AirflowNetwork_MultiZone_Surface_Crack;
  }

  double AirflowNetworkMultiZoneSurfaceCrack::airMassFlowCoefficientatReferenceConditions() const {
    return getImpl<detail::AirflowNetworkMultiZoneSurfaceCrack_Impl>()->airMassFlowCoefficientatReferenceConditions();
  }

  bool AirflowNetworkMultiZoneSurfaceCrack::setAirMassFlowCoefficientatReferenceConditions(double airMassFlowCoefficientatReferenceConditions) {
    return getImpl<detail::AirflowNetworkMultiZoneSurfaceCrack_Impl>()->setAirMassFlowCoefficientatReferenceConditions(
      airMassFlowCoefficientatReferenceConditions);
  }

  double AirflowNetworkMultiZoneSurfaceCrack::airMassFlowExponent() const {
    return getImpl<detail::AirflowNetworkMultiZoneSurfaceCrack_Impl>()->airMassFlowExponent();
  }

  bool AirflowNetworkMultiZoneSurfaceCrack::isAirMassFlowExponentDefaulted() const {
    return getImpl<detail::AirflowNetworkMultiZoneSurfaceCrack_Impl>()->isAirMassFlowExponentDefaulted();
  }

  bool AirflowNetworkMultiZoneSurfaceCrack::setAirMassFlowExponent(double airMassFlowExponent) {
    return getImpl<detail::AirflowNetworkMultiZoneSurfaceCrack_Impl>()->setAirMassFlowExponent(airMassFlowExponent);
  }

  void AirflowNetworkMultiZoneSurfaceCrack::resetAirMassFlowExponent() {
    getImpl<detail::AirflowNetworkMultiZoneSurfaceCrack_Impl>()->resetAirMassFlowExponent();
  }

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
  namespace detail {

    double AirflowNetworkMultiZoneSurfaceCrack_Impl::airMassFlowCoefficientatReferenceConditions() const {
      const auto value = getDouble(openstudio::AirflowNetwork_MultiZone_Surface_CrackFields::AirMassFlowCoefficientatReferenceConditions, true);
      OS_ASSERT(value);
      return *value;
    }

    bool
      AirflowNetworkMultiZoneSurfaceCrack_Impl::setAirMassFlowCoefficientatReferenceConditions(double airMassFlowCoefficientatReferenceConditions) {
      return setDouble(openstudio::AirflowNetwork_MultiZone_Surface_CrackFields::AirMassFlowCoefficientatReferenceConditions,
                       airMassFlowCoefficientatReferenceConditions);
    }

    double AirflowNetworkMultiZoneSurfaceCrack_Impl::airMassFlowExponent() const {
      const auto value = getDouble(openstudio::AirflowNetwork_MultiZone_Surface_CrackFields::AirMassFlowExponent, true);
      OS_ASSERT(value);
      return *value;
    }

    bool AirflowNetworkMultiZoneSurfaceCrack_Impl::isAirMassFlowExponentDefaulted() const {
      return isEmpty(openstudio::AirflowNetwork_MultiZone_Surface_CrackFields::AirMassFlowExponent);
    }

    bool AirflowNetworkMultiZoneSurfaceCrack_Impl::setAirMassFlowExponent(double airMassFlowExponent) {
      return setDouble(openstudio::AirflowNetwork_MultiZone_Surface_CrackFields::AirMassFlowExponent, airMassFlowExponent);
    }

    void AirflowNetworkMultiZoneSurfaceCrack_Impl::resetAirMassFlowExponent() {
      OS_ASSERT(setString(openstudio::AirflowNetwork_MultiZone_Surface_CrackFields::AirMassFlowExponent, ""));
    }

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
