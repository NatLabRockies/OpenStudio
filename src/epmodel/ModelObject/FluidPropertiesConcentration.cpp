/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "FluidPropertiesConcentration.hpp"
#include "FluidPropertiesConcentration_Impl.hpp"

#include "Model.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/idd/FluidProperties_Concentration_FieldEnums.hxx>
#include <utilities/idd/IddEnums.hxx>
#include <utilities/idd/IddFactory.hxx>
#include <utilities/idd/IddObject.hpp>

namespace openstudio {
namespace epmodel {

FluidPropertiesConcentration::FluidPropertiesConcentration(const Model& model)
  : ModelObject(FluidPropertiesConcentration::iddObjectType(), model) {}

FluidPropertiesConcentration::FluidPropertiesConcentration(std::shared_ptr<detail::FluidPropertiesConcentration_Impl> impl)
  : ModelObject(std::move(impl)) {}

IddObjectType FluidPropertiesConcentration::iddObjectType() {
  return IddObjectType::FluidProperties_Concentration;
}

std::vector<std::string> FluidPropertiesConcentration::fluidPropertyTypeValues() {
  return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(),
                        openstudio::FluidProperties_ConcentrationFields::FluidPropertyType);
}

boost::optional<std::string> FluidPropertiesConcentration::fluidPropertyType() const {
  return getImpl<detail::FluidPropertiesConcentration_Impl>()->fluidPropertyType();
}

bool FluidPropertiesConcentration::setFluidPropertyType(const std::string& fluidPropertyType) {
  return getImpl<detail::FluidPropertiesConcentration_Impl>()->setFluidPropertyType(fluidPropertyType);
}

void FluidPropertiesConcentration::resetFluidPropertyType() {
  getImpl<detail::FluidPropertiesConcentration_Impl>()->resetFluidPropertyType();
}

boost::optional<double> FluidPropertiesConcentration::concentration() const {
  return getImpl<detail::FluidPropertiesConcentration_Impl>()->concentration();
}

bool FluidPropertiesConcentration::setConcentration(double concentration) {
  return getImpl<detail::FluidPropertiesConcentration_Impl>()->setConcentration(concentration);
}

void FluidPropertiesConcentration::resetConcentration() {
  getImpl<detail::FluidPropertiesConcentration_Impl>()->resetConcentration();
}

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
namespace detail {

boost::optional<std::string> FluidPropertiesConcentration_Impl::fluidPropertyType() const {
  return getString(openstudio::FluidProperties_ConcentrationFields::FluidPropertyType, true);
}

bool FluidPropertiesConcentration_Impl::setFluidPropertyType(const std::string& fluidPropertyType) {
  return setString(openstudio::FluidProperties_ConcentrationFields::FluidPropertyType, fluidPropertyType);
}

void FluidPropertiesConcentration_Impl::resetFluidPropertyType() {
  OS_ASSERT(setString(openstudio::FluidProperties_ConcentrationFields::FluidPropertyType, ""));
}

boost::optional<double> FluidPropertiesConcentration_Impl::concentration() const {
  return getDouble(openstudio::FluidProperties_ConcentrationFields::Concentration, true);
}

bool FluidPropertiesConcentration_Impl::setConcentration(double concentration) {
  return setDouble(openstudio::FluidProperties_ConcentrationFields::Concentration, concentration);
}

void FluidPropertiesConcentration_Impl::resetConcentration() {
  OS_ASSERT(setString(openstudio::FluidProperties_ConcentrationFields::Concentration, ""));
}

std::vector<std::string> FluidPropertiesConcentration_Impl::fluidPropertyTypeValues() const {
  return openstudio::epmodel::FluidPropertiesConcentration::fluidPropertyTypeValues();
}

}  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
