/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "DaylightingDELightComplexFenestration.hpp"
#include "DaylightingDELightComplexFenestration_Impl.hpp"

#include "Model.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/idd/Daylighting_DELight_ComplexFenestration_FieldEnums.hxx>
#include <utilities/idd/IddEnums.hxx>

namespace openstudio {
namespace epmodel {

DaylightingDELightComplexFenestration::DaylightingDELightComplexFenestration(const Model& model)
  : ModelObject(DaylightingDELightComplexFenestration::iddObjectType(), model) {}

DaylightingDELightComplexFenestration::DaylightingDELightComplexFenestration(
  std::shared_ptr<detail::DaylightingDELightComplexFenestration_Impl> impl)
  : ModelObject(std::move(impl)) {}

IddObjectType DaylightingDELightComplexFenestration::iddObjectType() {
  return IddObjectType::Daylighting_DELight_ComplexFenestration;
}

std::string DaylightingDELightComplexFenestration::complexFenestrationType() const {
  return getImpl<detail::DaylightingDELightComplexFenestration_Impl>()->complexFenestrationType();
}

bool DaylightingDELightComplexFenestration::setComplexFenestrationType(const std::string& complexFenestrationType) {
  return getImpl<detail::DaylightingDELightComplexFenestration_Impl>()->setComplexFenestrationType(complexFenestrationType);
}

double DaylightingDELightComplexFenestration::fenestrationRotation() const {
  return getImpl<detail::DaylightingDELightComplexFenestration_Impl>()->fenestrationRotation();
}

bool DaylightingDELightComplexFenestration::isFenestrationRotationDefaulted() const {
  return getImpl<detail::DaylightingDELightComplexFenestration_Impl>()->isFenestrationRotationDefaulted();
}

bool DaylightingDELightComplexFenestration::setFenestrationRotation(double fenestrationRotation) {
  return getImpl<detail::DaylightingDELightComplexFenestration_Impl>()->setFenestrationRotation(fenestrationRotation);
}

void DaylightingDELightComplexFenestration::resetFenestrationRotation() {
  getImpl<detail::DaylightingDELightComplexFenestration_Impl>()->resetFenestrationRotation();
}

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
namespace detail {

std::string DaylightingDELightComplexFenestration_Impl::complexFenestrationType() const {
  const auto value = getString(openstudio::Daylighting_DELight_ComplexFenestrationFields::ComplexFenestrationType, true);
  OS_ASSERT(value);
  return *value;
}

bool DaylightingDELightComplexFenestration_Impl::setComplexFenestrationType(const std::string& complexFenestrationType) {
  const bool result = setString(openstudio::Daylighting_DELight_ComplexFenestrationFields::ComplexFenestrationType, complexFenestrationType);
  OS_ASSERT(result);
  return result;
}

double DaylightingDELightComplexFenestration_Impl::fenestrationRotation() const {
  const auto value = getDouble(openstudio::Daylighting_DELight_ComplexFenestrationFields::FenestrationRotation, true);
  OS_ASSERT(value);
  return *value;
}

bool DaylightingDELightComplexFenestration_Impl::isFenestrationRotationDefaulted() const {
  return isEmpty(openstudio::Daylighting_DELight_ComplexFenestrationFields::FenestrationRotation);
}

bool DaylightingDELightComplexFenestration_Impl::setFenestrationRotation(double fenestrationRotation) {
  const bool result = setDouble(openstudio::Daylighting_DELight_ComplexFenestrationFields::FenestrationRotation, fenestrationRotation);
  OS_ASSERT(result);
  return result;
}

void DaylightingDELightComplexFenestration_Impl::resetFenestrationRotation() {
  OS_ASSERT(setString(openstudio::Daylighting_DELight_ComplexFenestrationFields::FenestrationRotation, ""));
}

}  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
