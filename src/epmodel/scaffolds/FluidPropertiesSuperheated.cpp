/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "FluidPropertiesSuperheated.hpp"
#include "FluidPropertiesSuperheated_Impl.hpp"

#include "Model.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/idd/FluidProperties_Superheated_FieldEnums.hxx>
#include <utilities/idd/IddEnums.hxx>
#include <utilities/idd/IddFactory.hxx>
#include <utilities/idd/IddObject.hpp>

namespace openstudio {
namespace epmodel {

FluidPropertiesSuperheated::FluidPropertiesSuperheated(const Model& model)
  : ModelObject(FluidPropertiesSuperheated::iddObjectType(), model) {}

FluidPropertiesSuperheated::FluidPropertiesSuperheated(std::shared_ptr<detail::FluidPropertiesSuperheated_Impl> impl)
  : ModelObject(std::move(impl)) {}

IddObjectType FluidPropertiesSuperheated::iddObjectType() {
  return IddObjectType::FluidProperties_Superheated;
}

std::vector<std::string> FluidPropertiesSuperheated::fluidPropertyTypeValues() {
  return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(),
                        openstudio::FluidProperties_SuperheatedFields::FluidPropertyType);
}

boost::optional<std::string> FluidPropertiesSuperheated::fluidPropertyType() const {
  return getImpl<detail::FluidPropertiesSuperheated_Impl>()->fluidPropertyType();
}

bool FluidPropertiesSuperheated::setFluidPropertyType(const std::string& fluidPropertyType) {
  return getImpl<detail::FluidPropertiesSuperheated_Impl>()->setFluidPropertyType(fluidPropertyType);
}

void FluidPropertiesSuperheated::resetFluidPropertyType() {
  getImpl<detail::FluidPropertiesSuperheated_Impl>()->resetFluidPropertyType();
}

boost::optional<double> FluidPropertiesSuperheated::pressure() const {
  return getImpl<detail::FluidPropertiesSuperheated_Impl>()->pressure();
}

bool FluidPropertiesSuperheated::setPressure(double pressure) {
  return getImpl<detail::FluidPropertiesSuperheated_Impl>()->setPressure(pressure);
}

void FluidPropertiesSuperheated::resetPressure() {
  getImpl<detail::FluidPropertiesSuperheated_Impl>()->resetPressure();
}

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
namespace detail {

boost::optional<std::string> FluidPropertiesSuperheated_Impl::fluidPropertyType() const {
  return getString(openstudio::FluidProperties_SuperheatedFields::FluidPropertyType, true);
}

bool FluidPropertiesSuperheated_Impl::setFluidPropertyType(const std::string& fluidPropertyType) {
  return setString(openstudio::FluidProperties_SuperheatedFields::FluidPropertyType, fluidPropertyType);
}

void FluidPropertiesSuperheated_Impl::resetFluidPropertyType() {
  OS_ASSERT(setString(openstudio::FluidProperties_SuperheatedFields::FluidPropertyType, ""));
}

boost::optional<double> FluidPropertiesSuperheated_Impl::pressure() const {
  return getDouble(openstudio::FluidProperties_SuperheatedFields::Pressure, true);
}

bool FluidPropertiesSuperheated_Impl::setPressure(double pressure) {
  return setDouble(openstudio::FluidProperties_SuperheatedFields::Pressure, pressure);
}

void FluidPropertiesSuperheated_Impl::resetPressure() {
  OS_ASSERT(setString(openstudio::FluidProperties_SuperheatedFields::Pressure, ""));
}

std::vector<std::string> FluidPropertiesSuperheated_Impl::fluidPropertyTypeValues() const {
  return openstudio::epmodel::FluidPropertiesSuperheated::fluidPropertyTypeValues();
}

}  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
