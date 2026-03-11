/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "FluidPropertiesSaturated.hpp"
#include "FluidPropertiesSaturated_Impl.hpp"

#include "Model.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/idd/FluidProperties_Saturated_FieldEnums.hxx>
#include <utilities/idd/IddEnums.hxx>
#include <utilities/idd/IddFactory.hxx>
#include <utilities/idd/IddObject.hpp>

namespace openstudio {
namespace epmodel {

FluidPropertiesSaturated::FluidPropertiesSaturated(const Model& model)
  : ModelObject(FluidPropertiesSaturated::iddObjectType(), model) {}

FluidPropertiesSaturated::FluidPropertiesSaturated(std::shared_ptr<detail::FluidPropertiesSaturated_Impl> impl)
  : ModelObject(std::move(impl)) {}

IddObjectType FluidPropertiesSaturated::iddObjectType() {
  return IddObjectType::FluidProperties_Saturated;
}

std::vector<std::string> FluidPropertiesSaturated::fluidPropertyTypeValues() {
  return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(),
                        openstudio::FluidProperties_SaturatedFields::FluidPropertyType);
}

std::vector<std::string> FluidPropertiesSaturated::fluidPhaseValues() {
  return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(),
                        openstudio::FluidProperties_SaturatedFields::FluidPhase);
}

boost::optional<std::string> FluidPropertiesSaturated::fluidPropertyType() const {
  return getImpl<detail::FluidPropertiesSaturated_Impl>()->fluidPropertyType();
}

bool FluidPropertiesSaturated::setFluidPropertyType(const std::string& fluidPropertyType) {
  return getImpl<detail::FluidPropertiesSaturated_Impl>()->setFluidPropertyType(fluidPropertyType);
}

void FluidPropertiesSaturated::resetFluidPropertyType() {
  getImpl<detail::FluidPropertiesSaturated_Impl>()->resetFluidPropertyType();
}

boost::optional<std::string> FluidPropertiesSaturated::fluidPhase() const {
  return getImpl<detail::FluidPropertiesSaturated_Impl>()->fluidPhase();
}

bool FluidPropertiesSaturated::setFluidPhase(const std::string& fluidPhase) {
  return getImpl<detail::FluidPropertiesSaturated_Impl>()->setFluidPhase(fluidPhase);
}

void FluidPropertiesSaturated::resetFluidPhase() {
  getImpl<detail::FluidPropertiesSaturated_Impl>()->resetFluidPhase();
}

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
namespace detail {

boost::optional<std::string> FluidPropertiesSaturated_Impl::fluidPropertyType() const {
  return getString(openstudio::FluidProperties_SaturatedFields::FluidPropertyType, true);
}

bool FluidPropertiesSaturated_Impl::setFluidPropertyType(const std::string& fluidPropertyType) {
  return setString(openstudio::FluidProperties_SaturatedFields::FluidPropertyType, fluidPropertyType);
}

void FluidPropertiesSaturated_Impl::resetFluidPropertyType() {
  OS_ASSERT(setString(openstudio::FluidProperties_SaturatedFields::FluidPropertyType, ""));
}

boost::optional<std::string> FluidPropertiesSaturated_Impl::fluidPhase() const {
  return getString(openstudio::FluidProperties_SaturatedFields::FluidPhase, true);
}

bool FluidPropertiesSaturated_Impl::setFluidPhase(const std::string& fluidPhase) {
  return setString(openstudio::FluidProperties_SaturatedFields::FluidPhase, fluidPhase);
}

void FluidPropertiesSaturated_Impl::resetFluidPhase() {
  OS_ASSERT(setString(openstudio::FluidProperties_SaturatedFields::FluidPhase, ""));
}

std::vector<std::string> FluidPropertiesSaturated_Impl::fluidPropertyTypeValues() const {
  return openstudio::epmodel::FluidPropertiesSaturated::fluidPropertyTypeValues();
}

std::vector<std::string> FluidPropertiesSaturated_Impl::fluidPhaseValues() const {
  return openstudio::epmodel::FluidPropertiesSaturated::fluidPhaseValues();
}

}  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
