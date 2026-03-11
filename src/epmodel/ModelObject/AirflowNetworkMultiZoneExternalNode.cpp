/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "AirflowNetworkMultiZoneExternalNode.hpp"
#include "AirflowNetworkMultiZoneExternalNode_Impl.hpp"

#include "Model.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/core/StringHelpers.hpp>
#include <utilities/idd/AirflowNetwork_MultiZone_ExternalNode_FieldEnums.hxx>
#include <utilities/idd/IddEnums.hxx>
#include <utilities/idd/IddFactory.hxx>
#include <utilities/idd/IddObject.hpp>

namespace openstudio {
namespace epmodel {

AirflowNetworkMultiZoneExternalNode::AirflowNetworkMultiZoneExternalNode(const Model& model)
  : ModelObject(AirflowNetworkMultiZoneExternalNode::iddObjectType(), model) {}

AirflowNetworkMultiZoneExternalNode::AirflowNetworkMultiZoneExternalNode(
  std::shared_ptr<detail::AirflowNetworkMultiZoneExternalNode_Impl> impl)
  : ModelObject(std::move(impl)) {}

IddObjectType AirflowNetworkMultiZoneExternalNode::iddObjectType() {
  return IddObjectType::AirflowNetwork_MultiZone_ExternalNode;
}

std::vector<std::string> AirflowNetworkMultiZoneExternalNode::windAngleTypeValues() {
  return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(),
                        openstudio::AirflowNetwork_MultiZone_ExternalNodeFields::WindAngleType);
}

double AirflowNetworkMultiZoneExternalNode::externalNodeHeight() const {
  return getImpl<detail::AirflowNetworkMultiZoneExternalNode_Impl>()->externalNodeHeight();
}

bool AirflowNetworkMultiZoneExternalNode::isExternalNodeHeightDefaulted() const {
  return getImpl<detail::AirflowNetworkMultiZoneExternalNode_Impl>()->isExternalNodeHeightDefaulted();
}

bool AirflowNetworkMultiZoneExternalNode::setExternalNodeHeight(double externalNodeHeight) {
  return getImpl<detail::AirflowNetworkMultiZoneExternalNode_Impl>()->setExternalNodeHeight(externalNodeHeight);
}

void AirflowNetworkMultiZoneExternalNode::resetExternalNodeHeight() {
  getImpl<detail::AirflowNetworkMultiZoneExternalNode_Impl>()->resetExternalNodeHeight();
}

bool AirflowNetworkMultiZoneExternalNode::symmetricWindPressureCoefficientCurve() const {
  return getImpl<detail::AirflowNetworkMultiZoneExternalNode_Impl>()->symmetricWindPressureCoefficientCurve();
}

bool AirflowNetworkMultiZoneExternalNode::isSymmetricWindPressureCoefficientCurveDefaulted() const {
  return getImpl<detail::AirflowNetworkMultiZoneExternalNode_Impl>()->isSymmetricWindPressureCoefficientCurveDefaulted();
}

bool AirflowNetworkMultiZoneExternalNode::setSymmetricWindPressureCoefficientCurve(bool symmetricWindPressureCoefficientCurve) {
  return getImpl<detail::AirflowNetworkMultiZoneExternalNode_Impl>()->setSymmetricWindPressureCoefficientCurve(
    symmetricWindPressureCoefficientCurve);
}

void AirflowNetworkMultiZoneExternalNode::resetSymmetricWindPressureCoefficientCurve() {
  getImpl<detail::AirflowNetworkMultiZoneExternalNode_Impl>()->resetSymmetricWindPressureCoefficientCurve();
}

std::string AirflowNetworkMultiZoneExternalNode::windAngleType() const {
  return getImpl<detail::AirflowNetworkMultiZoneExternalNode_Impl>()->windAngleType();
}

bool AirflowNetworkMultiZoneExternalNode::isWindAngleTypeDefaulted() const {
  return getImpl<detail::AirflowNetworkMultiZoneExternalNode_Impl>()->isWindAngleTypeDefaulted();
}

bool AirflowNetworkMultiZoneExternalNode::setWindAngleType(const std::string& windAngleType) {
  return getImpl<detail::AirflowNetworkMultiZoneExternalNode_Impl>()->setWindAngleType(windAngleType);
}

void AirflowNetworkMultiZoneExternalNode::resetWindAngleType() {
  getImpl<detail::AirflowNetworkMultiZoneExternalNode_Impl>()->resetWindAngleType();
}

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
namespace detail {

double AirflowNetworkMultiZoneExternalNode_Impl::externalNodeHeight() const {
  const auto value = getDouble(openstudio::AirflowNetwork_MultiZone_ExternalNodeFields::ExternalNodeHeight, true);
  OS_ASSERT(value);
  return *value;
}

bool AirflowNetworkMultiZoneExternalNode_Impl::isExternalNodeHeightDefaulted() const {
  return isEmpty(openstudio::AirflowNetwork_MultiZone_ExternalNodeFields::ExternalNodeHeight);
}

bool AirflowNetworkMultiZoneExternalNode_Impl::setExternalNodeHeight(double externalNodeHeight) {
  const bool result = setDouble(openstudio::AirflowNetwork_MultiZone_ExternalNodeFields::ExternalNodeHeight, externalNodeHeight);
  OS_ASSERT(result);
  return result;
}

void AirflowNetworkMultiZoneExternalNode_Impl::resetExternalNodeHeight() {
  OS_ASSERT(setString(openstudio::AirflowNetwork_MultiZone_ExternalNodeFields::ExternalNodeHeight, ""));
}

bool AirflowNetworkMultiZoneExternalNode_Impl::symmetricWindPressureCoefficientCurve() const {
  const auto value = getString(openstudio::AirflowNetwork_MultiZone_ExternalNodeFields::SymmetricWindPressureCoefficientCurve, true);
  OS_ASSERT(value);
  return openstudio::istringEqual(*value, "Yes");
}

bool AirflowNetworkMultiZoneExternalNode_Impl::isSymmetricWindPressureCoefficientCurveDefaulted() const {
  return isEmpty(openstudio::AirflowNetwork_MultiZone_ExternalNodeFields::SymmetricWindPressureCoefficientCurve);
}

bool AirflowNetworkMultiZoneExternalNode_Impl::setSymmetricWindPressureCoefficientCurve(bool symmetricWindPressureCoefficientCurve) {
  const bool result = setString(openstudio::AirflowNetwork_MultiZone_ExternalNodeFields::SymmetricWindPressureCoefficientCurve,
                                symmetricWindPressureCoefficientCurve ? "Yes" : "No");
  OS_ASSERT(result);
  return result;
}

void AirflowNetworkMultiZoneExternalNode_Impl::resetSymmetricWindPressureCoefficientCurve() {
  OS_ASSERT(setString(openstudio::AirflowNetwork_MultiZone_ExternalNodeFields::SymmetricWindPressureCoefficientCurve, ""));
}

std::string AirflowNetworkMultiZoneExternalNode_Impl::windAngleType() const {
  const auto value = getString(openstudio::AirflowNetwork_MultiZone_ExternalNodeFields::WindAngleType, true);
  OS_ASSERT(value);
  return *value;
}

bool AirflowNetworkMultiZoneExternalNode_Impl::isWindAngleTypeDefaulted() const {
  return isEmpty(openstudio::AirflowNetwork_MultiZone_ExternalNodeFields::WindAngleType);
}

bool AirflowNetworkMultiZoneExternalNode_Impl::setWindAngleType(const std::string& windAngleType) {
  return setString(openstudio::AirflowNetwork_MultiZone_ExternalNodeFields::WindAngleType, windAngleType);
}

void AirflowNetworkMultiZoneExternalNode_Impl::resetWindAngleType() {
  OS_ASSERT(setString(openstudio::AirflowNetwork_MultiZone_ExternalNodeFields::WindAngleType, ""));
}

std::vector<std::string> AirflowNetworkMultiZoneExternalNode_Impl::windAngleTypeValues() const {
  return openstudio::epmodel::AirflowNetworkMultiZoneExternalNode::windAngleTypeValues();
}

}  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
