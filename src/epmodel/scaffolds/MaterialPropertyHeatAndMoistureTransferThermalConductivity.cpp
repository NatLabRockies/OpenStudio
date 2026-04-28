/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "scaffolds/MaterialPropertyHeatAndMoistureTransferThermalConductivity.hpp"
#include "scaffolds/MaterialPropertyHeatAndMoistureTransferThermalConductivity_Impl.hpp"

#include "Model.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/idd/IddEnums.hxx>
#include <utilities/idd/MaterialProperty_HeatAndMoistureTransfer_ThermalConductivity_FieldEnums.hxx>

namespace openstudio {
namespace epmodel {

MaterialPropertyHeatAndMoistureTransferThermalConductivity::MaterialPropertyHeatAndMoistureTransferThermalConductivity(const Model& model)
  : ModelObject(MaterialPropertyHeatAndMoistureTransferThermalConductivity::iddObjectType(), model) {}

MaterialPropertyHeatAndMoistureTransferThermalConductivity::MaterialPropertyHeatAndMoistureTransferThermalConductivity(
  std::shared_ptr<detail::MaterialPropertyHeatAndMoistureTransferThermalConductivity_Impl> impl)
  : ModelObject(std::move(impl)) {}

IddObjectType MaterialPropertyHeatAndMoistureTransferThermalConductivity::iddObjectType() {
  return IddObjectType::MaterialProperty_HeatAndMoistureTransfer_ThermalConductivity;
}

int MaterialPropertyHeatAndMoistureTransferThermalConductivity::numberofThermalCoordinates() const {
  return getImpl<detail::MaterialPropertyHeatAndMoistureTransferThermalConductivity_Impl>()->numberofThermalCoordinates();
}

bool MaterialPropertyHeatAndMoistureTransferThermalConductivity::setNumberofThermalCoordinates(int numberofThermalCoordinates) {
  return getImpl<detail::MaterialPropertyHeatAndMoistureTransferThermalConductivity_Impl>()->setNumberofThermalCoordinates(
    numberofThermalCoordinates);
}

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
namespace detail {

int MaterialPropertyHeatAndMoistureTransferThermalConductivity_Impl::numberofThermalCoordinates() const {
  const auto value = getInt(openstudio::MaterialProperty_HeatAndMoistureTransfer_ThermalConductivityFields::NumberofThermalCoordinates, true);
  OS_ASSERT(value);
  return *value;
}

bool MaterialPropertyHeatAndMoistureTransferThermalConductivity_Impl::setNumberofThermalCoordinates(int numberofThermalCoordinates) {
  return setInt(openstudio::MaterialProperty_HeatAndMoistureTransfer_ThermalConductivityFields::NumberofThermalCoordinates,
                numberofThermalCoordinates);
}

}  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
