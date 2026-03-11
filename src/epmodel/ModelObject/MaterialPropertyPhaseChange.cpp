/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "ModelObject/MaterialPropertyPhaseChange.hpp"
#include "ModelObject/MaterialPropertyPhaseChange_Impl.hpp"

#include "Model.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/idd/IddEnums.hxx>
#include <utilities/idd/MaterialProperty_PhaseChange_FieldEnums.hxx>

namespace openstudio {
namespace epmodel {

MaterialPropertyPhaseChange::MaterialPropertyPhaseChange(const Model& model)
  : ModelObject(MaterialPropertyPhaseChange::iddObjectType(), model) {}

MaterialPropertyPhaseChange::MaterialPropertyPhaseChange(std::shared_ptr<detail::MaterialPropertyPhaseChange_Impl> impl)
  : ModelObject(std::move(impl)) {}

IddObjectType MaterialPropertyPhaseChange::iddObjectType() {
  return IddObjectType::MaterialProperty_PhaseChange;
}

double MaterialPropertyPhaseChange::temperatureCoefficientforThermalConductivity() const {
  return getImpl<detail::MaterialPropertyPhaseChange_Impl>()->temperatureCoefficientforThermalConductivity();
}

bool MaterialPropertyPhaseChange::isTemperatureCoefficientforThermalConductivityDefaulted() const {
  return getImpl<detail::MaterialPropertyPhaseChange_Impl>()->isTemperatureCoefficientforThermalConductivityDefaulted();
}

bool MaterialPropertyPhaseChange::setTemperatureCoefficientforThermalConductivity(double temperatureCoefficientforThermalConductivity) {
  return getImpl<detail::MaterialPropertyPhaseChange_Impl>()->setTemperatureCoefficientforThermalConductivity(
    temperatureCoefficientforThermalConductivity);
}

void MaterialPropertyPhaseChange::resetTemperatureCoefficientforThermalConductivity() {
  getImpl<detail::MaterialPropertyPhaseChange_Impl>()->resetTemperatureCoefficientforThermalConductivity();
}

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
namespace detail {

double MaterialPropertyPhaseChange_Impl::temperatureCoefficientforThermalConductivity() const {
  const auto value = getDouble(openstudio::MaterialProperty_PhaseChangeFields::TemperatureCoefficientforThermalConductivity, true);
  OS_ASSERT(value);
  return *value;
}

bool MaterialPropertyPhaseChange_Impl::isTemperatureCoefficientforThermalConductivityDefaulted() const {
  return isEmpty(openstudio::MaterialProperty_PhaseChangeFields::TemperatureCoefficientforThermalConductivity);
}

bool MaterialPropertyPhaseChange_Impl::setTemperatureCoefficientforThermalConductivity(double temperatureCoefficientforThermalConductivity) {
  const bool result = setDouble(openstudio::MaterialProperty_PhaseChangeFields::TemperatureCoefficientforThermalConductivity,
                                temperatureCoefficientforThermalConductivity);
  OS_ASSERT(result);
  return result;
}

void MaterialPropertyPhaseChange_Impl::resetTemperatureCoefficientforThermalConductivity() {
  const bool result =
    setString(openstudio::MaterialProperty_PhaseChangeFields::TemperatureCoefficientforThermalConductivity, "");
  OS_ASSERT(result);
}

}  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
