/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "scaffolds/MaterialPropertyHeatAndMoistureTransferSorptionIsotherm.hpp"
#include "scaffolds/MaterialPropertyHeatAndMoistureTransferSorptionIsotherm_Impl.hpp"

#include "Model.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/idd/IddEnums.hxx>
#include <utilities/idd/MaterialProperty_HeatAndMoistureTransfer_SorptionIsotherm_FieldEnums.hxx>

namespace openstudio {
namespace epmodel {

  MaterialPropertyHeatAndMoistureTransferSorptionIsotherm::MaterialPropertyHeatAndMoistureTransferSorptionIsotherm(const Model& model)
    : ModelObject(MaterialPropertyHeatAndMoistureTransferSorptionIsotherm::iddObjectType(), model) {}

  MaterialPropertyHeatAndMoistureTransferSorptionIsotherm::MaterialPropertyHeatAndMoistureTransferSorptionIsotherm(
    std::shared_ptr<detail::MaterialPropertyHeatAndMoistureTransferSorptionIsotherm_Impl> impl)
    : ModelObject(std::move(impl)) {}

  IddObjectType MaterialPropertyHeatAndMoistureTransferSorptionIsotherm::iddObjectType() {
    return IddObjectType::MaterialProperty_HeatAndMoistureTransfer_SorptionIsotherm;
  }

  int MaterialPropertyHeatAndMoistureTransferSorptionIsotherm::numberofIsothermCoordinates() const {
    return getImpl<detail::MaterialPropertyHeatAndMoistureTransferSorptionIsotherm_Impl>()->numberofIsothermCoordinates();
  }

  bool MaterialPropertyHeatAndMoistureTransferSorptionIsotherm::setNumberofIsothermCoordinates(int numberofIsothermCoordinates) {
    return getImpl<detail::MaterialPropertyHeatAndMoistureTransferSorptionIsotherm_Impl>()->setNumberofIsothermCoordinates(
      numberofIsothermCoordinates);
  }

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
  namespace detail {

    int MaterialPropertyHeatAndMoistureTransferSorptionIsotherm_Impl::numberofIsothermCoordinates() const {
      // Required integer getter (strict) for IDD field N1 Number of Isotherm Coordinates.
      const auto value = getInt(openstudio::MaterialProperty_HeatAndMoistureTransfer_SorptionIsothermFields::NumberofIsothermCoordinates, true);
      OS_ASSERT(value);
      return *value;
    }

    bool MaterialPropertyHeatAndMoistureTransferSorptionIsotherm_Impl::setNumberofIsothermCoordinates(int numberofIsothermCoordinates) {
      // Failable setter (bounded integer in schema: min/max), so return setInt result directly.
      return setInt(openstudio::MaterialProperty_HeatAndMoistureTransfer_SorptionIsothermFields::NumberofIsothermCoordinates,
                    numberofIsothermCoordinates);
    }

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
