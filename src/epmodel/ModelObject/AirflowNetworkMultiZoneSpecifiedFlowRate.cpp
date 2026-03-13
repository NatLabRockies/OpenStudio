/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "AirflowNetworkMultiZoneSpecifiedFlowRate.hpp"
#include "AirflowNetworkMultiZoneSpecifiedFlowRate_Impl.hpp"

#include "Model.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/idd/AirflowNetwork_MultiZone_SpecifiedFlowRate_FieldEnums.hxx>
#include <utilities/idd/IddEnums.hxx>

namespace openstudio {
namespace epmodel {

AirflowNetworkMultiZoneSpecifiedFlowRate::AirflowNetworkMultiZoneSpecifiedFlowRate(const Model& model)
  : ModelObject(AirflowNetworkMultiZoneSpecifiedFlowRate::iddObjectType(), model) {}

AirflowNetworkMultiZoneSpecifiedFlowRate::AirflowNetworkMultiZoneSpecifiedFlowRate(
  std::shared_ptr<detail::AirflowNetworkMultiZoneSpecifiedFlowRate_Impl> impl)
  : ModelObject(std::move(impl)) {}

IddObjectType AirflowNetworkMultiZoneSpecifiedFlowRate::iddObjectType() {
  return IddObjectType::AirflowNetwork_MultiZone_SpecifiedFlowRate;
}

std::vector<std::string> AirflowNetworkMultiZoneSpecifiedFlowRate::airFlowUnitsValues() {
  return {"VolumetricFlow", "MassFlow"};
}

double AirflowNetworkMultiZoneSpecifiedFlowRate::airFlowValue() const {
  return getImpl<detail::AirflowNetworkMultiZoneSpecifiedFlowRate_Impl>()->airFlowValue();
}

bool AirflowNetworkMultiZoneSpecifiedFlowRate::setAirFlowValue(double airFlowValue) {
  return getImpl<detail::AirflowNetworkMultiZoneSpecifiedFlowRate_Impl>()->setAirFlowValue(airFlowValue);
}

std::string AirflowNetworkMultiZoneSpecifiedFlowRate::airFlowUnits() const {
  return getImpl<detail::AirflowNetworkMultiZoneSpecifiedFlowRate_Impl>()->airFlowUnits();
}

bool AirflowNetworkMultiZoneSpecifiedFlowRate::setAirFlowUnits(const std::string& airFlowUnits) {
  return getImpl<detail::AirflowNetworkMultiZoneSpecifiedFlowRate_Impl>()->setAirFlowUnits(airFlowUnits);
}

bool AirflowNetworkMultiZoneSpecifiedFlowRate::isAirFlowUnitsDefaulted() const {
  return getImpl<detail::AirflowNetworkMultiZoneSpecifiedFlowRate_Impl>()->isAirFlowUnitsDefaulted();
}

void AirflowNetworkMultiZoneSpecifiedFlowRate::resetAirFlowUnits() {
  getImpl<detail::AirflowNetworkMultiZoneSpecifiedFlowRate_Impl>()->resetAirFlowUnits();
}

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
namespace detail {

double AirflowNetworkMultiZoneSpecifiedFlowRate_Impl::airFlowValue() const {
  const auto value = getDouble(openstudio::AirflowNetwork_MultiZone_SpecifiedFlowRateFields::AirFlowValue, true);
  OS_ASSERT(value);
  return *value;
}

bool AirflowNetworkMultiZoneSpecifiedFlowRate_Impl::setAirFlowValue(double airFlowValue) {
  const bool result = setDouble(openstudio::AirflowNetwork_MultiZone_SpecifiedFlowRateFields::AirFlowValue, airFlowValue);
  OS_ASSERT(result);
  return result;
}

std::string AirflowNetworkMultiZoneSpecifiedFlowRate_Impl::airFlowUnits() const {
  const auto value = getString(openstudio::AirflowNetwork_MultiZone_SpecifiedFlowRateFields::AirFlowUnits, true);
  OS_ASSERT(value);
  return *value;
}

bool AirflowNetworkMultiZoneSpecifiedFlowRate_Impl::setAirFlowUnits(const std::string& airFlowUnits) {
  return setString(openstudio::AirflowNetwork_MultiZone_SpecifiedFlowRateFields::AirFlowUnits, airFlowUnits);
}

bool AirflowNetworkMultiZoneSpecifiedFlowRate_Impl::isAirFlowUnitsDefaulted() const {
  return isEmpty(openstudio::AirflowNetwork_MultiZone_SpecifiedFlowRateFields::AirFlowUnits);
}

void AirflowNetworkMultiZoneSpecifiedFlowRate_Impl::resetAirFlowUnits() {
  OS_ASSERT(setString(openstudio::AirflowNetwork_MultiZone_SpecifiedFlowRateFields::AirFlowUnits, ""));
}

std::vector<std::string> AirflowNetworkMultiZoneSpecifiedFlowRate_Impl::airFlowUnitsValues() const {
  return openstudio::epmodel::AirflowNetworkMultiZoneSpecifiedFlowRate::airFlowUnitsValues();
}

}  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
