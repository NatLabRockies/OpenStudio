/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "Curve/CurveFunctionalPressureDrop.hpp"
#include "Curve/CurveFunctionalPressureDrop_Impl.hpp"

#include "Model.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/idd/Curve_Functional_PressureDrop_FieldEnums.hxx>
#include <utilities/idd/IddEnums.hxx>

namespace openstudio {
namespace epmodel {

CurveFunctionalPressureDrop::CurveFunctionalPressureDrop(const Model& model) : ModelObject(CurveFunctionalPressureDrop::iddObjectType(), model) {
  OS_ASSERT(getImpl<detail::CurveFunctionalPressureDrop_Impl>());
  OS_ASSERT(setDiameter(0.05));
}

CurveFunctionalPressureDrop::CurveFunctionalPressureDrop(std::shared_ptr<detail::CurveFunctionalPressureDrop_Impl> impl)
  : ModelObject(std::move(impl)) {}

IddObjectType CurveFunctionalPressureDrop::iddObjectType() {
  return IddObjectType::Curve_Functional_PressureDrop;
}

double CurveFunctionalPressureDrop::diameter() const {
  return getImpl<detail::CurveFunctionalPressureDrop_Impl>()->diameter();
}

boost::optional<double> CurveFunctionalPressureDrop::minorLossCoefficient() const {
  return getImpl<detail::CurveFunctionalPressureDrop_Impl>()->minorLossCoefficient();
}

boost::optional<double> CurveFunctionalPressureDrop::length() const {
  return getImpl<detail::CurveFunctionalPressureDrop_Impl>()->length();
}

boost::optional<double> CurveFunctionalPressureDrop::roughness() const {
  return getImpl<detail::CurveFunctionalPressureDrop_Impl>()->roughness();
}

boost::optional<double> CurveFunctionalPressureDrop::fixedFrictionFactor() const {
  return getImpl<detail::CurveFunctionalPressureDrop_Impl>()->fixedFrictionFactor();
}

bool CurveFunctionalPressureDrop::setDiameter(double diameter) {
  return getImpl<detail::CurveFunctionalPressureDrop_Impl>()->setDiameter(diameter);
}

bool CurveFunctionalPressureDrop::setMinorLossCoefficient(double minorLossCoefficient) {
  return getImpl<detail::CurveFunctionalPressureDrop_Impl>()->setMinorLossCoefficient(minorLossCoefficient);
}

void CurveFunctionalPressureDrop::resetMinorLossCoefficient() {
  getImpl<detail::CurveFunctionalPressureDrop_Impl>()->resetMinorLossCoefficient();
}

bool CurveFunctionalPressureDrop::setLength(double length) {
  return getImpl<detail::CurveFunctionalPressureDrop_Impl>()->setLength(length);
}

void CurveFunctionalPressureDrop::resetLength() {
  getImpl<detail::CurveFunctionalPressureDrop_Impl>()->resetLength();
}

bool CurveFunctionalPressureDrop::setRoughness(double roughness) {
  return getImpl<detail::CurveFunctionalPressureDrop_Impl>()->setRoughness(roughness);
}

void CurveFunctionalPressureDrop::resetRoughness() {
  getImpl<detail::CurveFunctionalPressureDrop_Impl>()->resetRoughness();
}

bool CurveFunctionalPressureDrop::setFixedFrictionFactor(double fixedFrictionFactor) {
  return getImpl<detail::CurveFunctionalPressureDrop_Impl>()->setFixedFrictionFactor(fixedFrictionFactor);
}

void CurveFunctionalPressureDrop::resetFixedFrictionFactor() {
  getImpl<detail::CurveFunctionalPressureDrop_Impl>()->resetFixedFrictionFactor();
}

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
namespace detail {

double CurveFunctionalPressureDrop_Impl::diameter() const {
  const auto value = getDouble(openstudio::Curve_Functional_PressureDropFields::Diameter, true);
  OS_ASSERT(value);
  return *value;
}

boost::optional<double> CurveFunctionalPressureDrop_Impl::minorLossCoefficient() const {
  return getDouble(openstudio::Curve_Functional_PressureDropFields::MinorLossCoefficient, true);
}

boost::optional<double> CurveFunctionalPressureDrop_Impl::length() const {
  return getDouble(openstudio::Curve_Functional_PressureDropFields::Length, true);
}

boost::optional<double> CurveFunctionalPressureDrop_Impl::roughness() const {
  return getDouble(openstudio::Curve_Functional_PressureDropFields::Roughness, true);
}

boost::optional<double> CurveFunctionalPressureDrop_Impl::fixedFrictionFactor() const {
  return getDouble(openstudio::Curve_Functional_PressureDropFields::FixedFrictionFactor, true);
}

bool CurveFunctionalPressureDrop_Impl::setDiameter(double diameter) {
  return setDouble(openstudio::Curve_Functional_PressureDropFields::Diameter, diameter);
}

bool CurveFunctionalPressureDrop_Impl::setMinorLossCoefficient(double minorLossCoefficient) {
  return setDouble(openstudio::Curve_Functional_PressureDropFields::MinorLossCoefficient, minorLossCoefficient);
}

void CurveFunctionalPressureDrop_Impl::resetMinorLossCoefficient() {
  OS_ASSERT(setString(openstudio::Curve_Functional_PressureDropFields::MinorLossCoefficient, ""));
}

bool CurveFunctionalPressureDrop_Impl::setLength(double length) {
  return setDouble(openstudio::Curve_Functional_PressureDropFields::Length, length);
}

void CurveFunctionalPressureDrop_Impl::resetLength() {
  OS_ASSERT(setString(openstudio::Curve_Functional_PressureDropFields::Length, ""));
}

bool CurveFunctionalPressureDrop_Impl::setRoughness(double roughness) {
  return setDouble(openstudio::Curve_Functional_PressureDropFields::Roughness, roughness);
}

void CurveFunctionalPressureDrop_Impl::resetRoughness() {
  OS_ASSERT(setString(openstudio::Curve_Functional_PressureDropFields::Roughness, ""));
}

bool CurveFunctionalPressureDrop_Impl::setFixedFrictionFactor(double fixedFrictionFactor) {
  return setDouble(openstudio::Curve_Functional_PressureDropFields::FixedFrictionFactor, fixedFrictionFactor);
}

void CurveFunctionalPressureDrop_Impl::resetFixedFrictionFactor() {
  OS_ASSERT(setString(openstudio::Curve_Functional_PressureDropFields::FixedFrictionFactor, ""));
}

}  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
