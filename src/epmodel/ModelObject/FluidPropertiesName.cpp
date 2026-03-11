/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "FluidPropertiesName.hpp"
#include "FluidPropertiesName_Impl.hpp"

#include "Model.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/idd/FluidProperties_Name_FieldEnums.hxx>
#include <utilities/idd/IddEnums.hxx>
#include <utilities/idd/IddFactory.hxx>
#include <utilities/idd/IddObject.hpp>

namespace openstudio {
namespace epmodel {

FluidPropertiesName::FluidPropertiesName(const Model& model)
  : ModelObject(FluidPropertiesName::iddObjectType(), model) {}

FluidPropertiesName::FluidPropertiesName(std::shared_ptr<detail::FluidPropertiesName_Impl> impl)
  : ModelObject(std::move(impl)) {}

IddObjectType FluidPropertiesName::iddObjectType() {
  return IddObjectType::FluidProperties_Name;
}

std::vector<std::string> FluidPropertiesName::fluidTypeValues() {
  return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(), openstudio::FluidProperties_NameFields::FluidType);
}

std::string FluidPropertiesName::fluidName() const {
  return getImpl<detail::FluidPropertiesName_Impl>()->fluidName();
}

bool FluidPropertiesName::setFluidName(const std::string& fluidName) {
  return getImpl<detail::FluidPropertiesName_Impl>()->setFluidName(fluidName);
}

std::string FluidPropertiesName::fluidType() const {
  return getImpl<detail::FluidPropertiesName_Impl>()->fluidType();
}

bool FluidPropertiesName::setFluidType(const std::string& fluidType) {
  return getImpl<detail::FluidPropertiesName_Impl>()->setFluidType(fluidType);
}

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
namespace detail {

std::string FluidPropertiesName_Impl::fluidName() const {
  const auto value = getString(openstudio::FluidProperties_NameFields::FluidName, true);
  OS_ASSERT(value);
  return *value;
}

bool FluidPropertiesName_Impl::setFluidName(const std::string& fluidName) {
  return setString(openstudio::FluidProperties_NameFields::FluidName, fluidName);
}

std::string FluidPropertiesName_Impl::fluidType() const {
  const auto value = getString(openstudio::FluidProperties_NameFields::FluidType, true);
  OS_ASSERT(value);
  return *value;
}

bool FluidPropertiesName_Impl::setFluidType(const std::string& fluidType) {
  return setString(openstudio::FluidProperties_NameFields::FluidType, fluidType);
}

std::vector<std::string> FluidPropertiesName_Impl::fluidTypeValues() const {
  return openstudio::epmodel::FluidPropertiesName::fluidTypeValues();
}

}  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
