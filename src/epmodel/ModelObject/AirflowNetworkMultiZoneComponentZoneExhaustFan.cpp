/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "AirflowNetworkMultiZoneComponentZoneExhaustFan.hpp"
#include "AirflowNetworkMultiZoneComponentZoneExhaustFan_Impl.hpp"

#include "Model.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/idd/AirflowNetwork_MultiZone_Component_ZoneExhaustFan_FieldEnums.hxx>
#include <utilities/idd/IddEnums.hxx>

namespace openstudio {
namespace epmodel {

AirflowNetworkMultiZoneComponentZoneExhaustFan::AirflowNetworkMultiZoneComponentZoneExhaustFan(const Model& model)
  : ModelObject(AirflowNetworkMultiZoneComponentZoneExhaustFan::iddObjectType(), model) {}

AirflowNetworkMultiZoneComponentZoneExhaustFan::AirflowNetworkMultiZoneComponentZoneExhaustFan(
  std::shared_ptr<detail::AirflowNetworkMultiZoneComponentZoneExhaustFan_Impl> impl)
  : ModelObject(std::move(impl)) {}

IddObjectType AirflowNetworkMultiZoneComponentZoneExhaustFan::iddObjectType() {
  return IddObjectType::AirflowNetwork_MultiZone_Component_ZoneExhaustFan;
}

double AirflowNetworkMultiZoneComponentZoneExhaustFan::airMassFlowCoefficientWhentheZoneExhaustFanisOffatReferenceConditions() const {
  return getImpl<detail::AirflowNetworkMultiZoneComponentZoneExhaustFan_Impl>()
    ->airMassFlowCoefficientWhentheZoneExhaustFanisOffatReferenceConditions();
}

bool AirflowNetworkMultiZoneComponentZoneExhaustFan::setAirMassFlowCoefficientWhentheZoneExhaustFanisOffatReferenceConditions(
  double airMassFlowCoefficientWhentheZoneExhaustFanisOffatReferenceConditions) {
  return getImpl<detail::AirflowNetworkMultiZoneComponentZoneExhaustFan_Impl>()
    ->setAirMassFlowCoefficientWhentheZoneExhaustFanisOffatReferenceConditions(
      airMassFlowCoefficientWhentheZoneExhaustFanisOffatReferenceConditions);
}

double AirflowNetworkMultiZoneComponentZoneExhaustFan::airMassFlowExponentWhentheZoneExhaustFanisOff() const {
  return getImpl<detail::AirflowNetworkMultiZoneComponentZoneExhaustFan_Impl>()->airMassFlowExponentWhentheZoneExhaustFanisOff();
}

bool AirflowNetworkMultiZoneComponentZoneExhaustFan::isAirMassFlowExponentWhentheZoneExhaustFanisOffDefaulted() const {
  return getImpl<detail::AirflowNetworkMultiZoneComponentZoneExhaustFan_Impl>()->isAirMassFlowExponentWhentheZoneExhaustFanisOffDefaulted();
}

bool AirflowNetworkMultiZoneComponentZoneExhaustFan::setAirMassFlowExponentWhentheZoneExhaustFanisOff(
  double airMassFlowExponentWhentheZoneExhaustFanisOff) {
  return getImpl<detail::AirflowNetworkMultiZoneComponentZoneExhaustFan_Impl>()->setAirMassFlowExponentWhentheZoneExhaustFanisOff(
    airMassFlowExponentWhentheZoneExhaustFanisOff);
}

void AirflowNetworkMultiZoneComponentZoneExhaustFan::resetAirMassFlowExponentWhentheZoneExhaustFanisOff() {
  getImpl<detail::AirflowNetworkMultiZoneComponentZoneExhaustFan_Impl>()->resetAirMassFlowExponentWhentheZoneExhaustFanisOff();
}

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
namespace detail {

double AirflowNetworkMultiZoneComponentZoneExhaustFan_Impl::airMassFlowCoefficientWhentheZoneExhaustFanisOffatReferenceConditions() const {
  const auto value = getDouble(
    openstudio::AirflowNetwork_MultiZone_Component_ZoneExhaustFanFields::AirMassFlowCoefficientWhentheZoneExhaustFanisOffatReferenceConditions,
    true);
  OS_ASSERT(value);
  return *value;
}

bool AirflowNetworkMultiZoneComponentZoneExhaustFan_Impl::setAirMassFlowCoefficientWhentheZoneExhaustFanisOffatReferenceConditions(
  double airMassFlowCoefficientWhentheZoneExhaustFanisOffatReferenceConditions) {
  return setDouble(
    openstudio::AirflowNetwork_MultiZone_Component_ZoneExhaustFanFields::AirMassFlowCoefficientWhentheZoneExhaustFanisOffatReferenceConditions,
    airMassFlowCoefficientWhentheZoneExhaustFanisOffatReferenceConditions);
}

double AirflowNetworkMultiZoneComponentZoneExhaustFan_Impl::airMassFlowExponentWhentheZoneExhaustFanisOff() const {
  const auto value =
    getDouble(openstudio::AirflowNetwork_MultiZone_Component_ZoneExhaustFanFields::AirMassFlowExponentWhentheZoneExhaustFanisOff, true);
  OS_ASSERT(value);
  return *value;
}

bool AirflowNetworkMultiZoneComponentZoneExhaustFan_Impl::isAirMassFlowExponentWhentheZoneExhaustFanisOffDefaulted() const {
  return isEmpty(openstudio::AirflowNetwork_MultiZone_Component_ZoneExhaustFanFields::AirMassFlowExponentWhentheZoneExhaustFanisOff);
}

bool AirflowNetworkMultiZoneComponentZoneExhaustFan_Impl::setAirMassFlowExponentWhentheZoneExhaustFanisOff(
  double airMassFlowExponentWhentheZoneExhaustFanisOff) {
  return setDouble(openstudio::AirflowNetwork_MultiZone_Component_ZoneExhaustFanFields::AirMassFlowExponentWhentheZoneExhaustFanisOff,
                   airMassFlowExponentWhentheZoneExhaustFanisOff);
}

void AirflowNetworkMultiZoneComponentZoneExhaustFan_Impl::resetAirMassFlowExponentWhentheZoneExhaustFanisOff() {
  OS_ASSERT(setString(openstudio::AirflowNetwork_MultiZone_Component_ZoneExhaustFanFields::AirMassFlowExponentWhentheZoneExhaustFanisOff, ""));
}

}  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
