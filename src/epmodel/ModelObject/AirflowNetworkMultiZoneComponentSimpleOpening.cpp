/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "AirflowNetworkMultiZoneComponentSimpleOpening.hpp"
#include "AirflowNetworkMultiZoneComponentSimpleOpening_Impl.hpp"

#include "Model.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/idd/AirflowNetwork_MultiZone_Component_SimpleOpening_FieldEnums.hxx>
#include <utilities/idd/IddEnums.hxx>

namespace openstudio {
namespace epmodel {

AirflowNetworkMultiZoneComponentSimpleOpening::AirflowNetworkMultiZoneComponentSimpleOpening(const Model& model)
  : ModelObject(AirflowNetworkMultiZoneComponentSimpleOpening::iddObjectType(), model) {}

AirflowNetworkMultiZoneComponentSimpleOpening::AirflowNetworkMultiZoneComponentSimpleOpening(
  std::shared_ptr<detail::AirflowNetworkMultiZoneComponentSimpleOpening_Impl> impl)
  : ModelObject(std::move(impl)) {}

IddObjectType AirflowNetworkMultiZoneComponentSimpleOpening::iddObjectType() {
  return IddObjectType::AirflowNetwork_MultiZone_Component_SimpleOpening;
}

double AirflowNetworkMultiZoneComponentSimpleOpening::airMassFlowCoefficientWhenOpeningisClosed() const {
  return getImpl<detail::AirflowNetworkMultiZoneComponentSimpleOpening_Impl>()->airMassFlowCoefficientWhenOpeningisClosed();
}

bool AirflowNetworkMultiZoneComponentSimpleOpening::setAirMassFlowCoefficientWhenOpeningisClosed(
  double airMassFlowCoefficientWhenOpeningisClosed) {
  return getImpl<detail::AirflowNetworkMultiZoneComponentSimpleOpening_Impl>()->setAirMassFlowCoefficientWhenOpeningisClosed(
    airMassFlowCoefficientWhenOpeningisClosed);
}

double AirflowNetworkMultiZoneComponentSimpleOpening::airMassFlowExponentWhenOpeningisClosed() const {
  return getImpl<detail::AirflowNetworkMultiZoneComponentSimpleOpening_Impl>()->airMassFlowExponentWhenOpeningisClosed();
}

bool AirflowNetworkMultiZoneComponentSimpleOpening::isAirMassFlowExponentWhenOpeningisClosedDefaulted() const {
  return getImpl<detail::AirflowNetworkMultiZoneComponentSimpleOpening_Impl>()->isAirMassFlowExponentWhenOpeningisClosedDefaulted();
}

bool AirflowNetworkMultiZoneComponentSimpleOpening::setAirMassFlowExponentWhenOpeningisClosed(double airMassFlowExponentWhenOpeningisClosed) {
  return getImpl<detail::AirflowNetworkMultiZoneComponentSimpleOpening_Impl>()->setAirMassFlowExponentWhenOpeningisClosed(
    airMassFlowExponentWhenOpeningisClosed);
}

void AirflowNetworkMultiZoneComponentSimpleOpening::resetAirMassFlowExponentWhenOpeningisClosed() {
  getImpl<detail::AirflowNetworkMultiZoneComponentSimpleOpening_Impl>()->resetAirMassFlowExponentWhenOpeningisClosed();
}

double AirflowNetworkMultiZoneComponentSimpleOpening::minimumDensityDifferenceforTwoWayFlow() const {
  return getImpl<detail::AirflowNetworkMultiZoneComponentSimpleOpening_Impl>()->minimumDensityDifferenceforTwoWayFlow();
}

bool AirflowNetworkMultiZoneComponentSimpleOpening::setMinimumDensityDifferenceforTwoWayFlow(double minimumDensityDifferenceforTwoWayFlow) {
  return getImpl<detail::AirflowNetworkMultiZoneComponentSimpleOpening_Impl>()->setMinimumDensityDifferenceforTwoWayFlow(
    minimumDensityDifferenceforTwoWayFlow);
}

double AirflowNetworkMultiZoneComponentSimpleOpening::dischargeCoefficient() const {
  return getImpl<detail::AirflowNetworkMultiZoneComponentSimpleOpening_Impl>()->dischargeCoefficient();
}

bool AirflowNetworkMultiZoneComponentSimpleOpening::setDischargeCoefficient(double dischargeCoefficient) {
  return getImpl<detail::AirflowNetworkMultiZoneComponentSimpleOpening_Impl>()->setDischargeCoefficient(dischargeCoefficient);
}

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
namespace detail {

double AirflowNetworkMultiZoneComponentSimpleOpening_Impl::airMassFlowCoefficientWhenOpeningisClosed() const {
  const auto value =
    getDouble(openstudio::AirflowNetwork_MultiZone_Component_SimpleOpeningFields::AirMassFlowCoefficientWhenOpeningisClosed, true);
  OS_ASSERT(value);
  return *value;
}

bool AirflowNetworkMultiZoneComponentSimpleOpening_Impl::setAirMassFlowCoefficientWhenOpeningisClosed(
  double airMassFlowCoefficientWhenOpeningisClosed) {
  return setDouble(openstudio::AirflowNetwork_MultiZone_Component_SimpleOpeningFields::AirMassFlowCoefficientWhenOpeningisClosed,
                   airMassFlowCoefficientWhenOpeningisClosed);
}

double AirflowNetworkMultiZoneComponentSimpleOpening_Impl::airMassFlowExponentWhenOpeningisClosed() const {
  const auto value =
    getDouble(openstudio::AirflowNetwork_MultiZone_Component_SimpleOpeningFields::AirMassFlowExponentWhenOpeningisClosed, true);
  OS_ASSERT(value);
  return *value;
}

bool AirflowNetworkMultiZoneComponentSimpleOpening_Impl::isAirMassFlowExponentWhenOpeningisClosedDefaulted() const {
  return isEmpty(openstudio::AirflowNetwork_MultiZone_Component_SimpleOpeningFields::AirMassFlowExponentWhenOpeningisClosed);
}

bool AirflowNetworkMultiZoneComponentSimpleOpening_Impl::setAirMassFlowExponentWhenOpeningisClosed(double airMassFlowExponentWhenOpeningisClosed) {
  return setDouble(openstudio::AirflowNetwork_MultiZone_Component_SimpleOpeningFields::AirMassFlowExponentWhenOpeningisClosed,
                   airMassFlowExponentWhenOpeningisClosed);
}

void AirflowNetworkMultiZoneComponentSimpleOpening_Impl::resetAirMassFlowExponentWhenOpeningisClosed() {
  OS_ASSERT(setString(openstudio::AirflowNetwork_MultiZone_Component_SimpleOpeningFields::AirMassFlowExponentWhenOpeningisClosed, ""));
}

double AirflowNetworkMultiZoneComponentSimpleOpening_Impl::minimumDensityDifferenceforTwoWayFlow() const {
  const auto value =
    getDouble(openstudio::AirflowNetwork_MultiZone_Component_SimpleOpeningFields::MinimumDensityDifferenceforTwoWayFlow, true);
  OS_ASSERT(value);
  return *value;
}

bool AirflowNetworkMultiZoneComponentSimpleOpening_Impl::setMinimumDensityDifferenceforTwoWayFlow(double minimumDensityDifferenceforTwoWayFlow) {
  return setDouble(openstudio::AirflowNetwork_MultiZone_Component_SimpleOpeningFields::MinimumDensityDifferenceforTwoWayFlow,
                   minimumDensityDifferenceforTwoWayFlow);
}

double AirflowNetworkMultiZoneComponentSimpleOpening_Impl::dischargeCoefficient() const {
  const auto value = getDouble(openstudio::AirflowNetwork_MultiZone_Component_SimpleOpeningFields::DischargeCoefficient, true);
  OS_ASSERT(value);
  return *value;
}

bool AirflowNetworkMultiZoneComponentSimpleOpening_Impl::setDischargeCoefficient(double dischargeCoefficient) {
  return setDouble(openstudio::AirflowNetwork_MultiZone_Component_SimpleOpeningFields::DischargeCoefficient, dischargeCoefficient);
}

}  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
