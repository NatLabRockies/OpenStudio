/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "ModelObject/MaterialPropertyHeatAndMoistureTransferDiffusion.hpp"
#include "ModelObject/MaterialPropertyHeatAndMoistureTransferDiffusion_Impl.hpp"

#include "Model.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/idd/IddEnums.hxx>
#include <utilities/idd/MaterialProperty_HeatAndMoistureTransfer_Diffusion_FieldEnums.hxx>

namespace openstudio {
namespace epmodel {

  MaterialPropertyHeatAndMoistureTransferDiffusion::MaterialPropertyHeatAndMoistureTransferDiffusion(const Model& model)
    : ModelObject(MaterialPropertyHeatAndMoistureTransferDiffusion::iddObjectType(), model) {}

  MaterialPropertyHeatAndMoistureTransferDiffusion::MaterialPropertyHeatAndMoistureTransferDiffusion(
    std::shared_ptr<detail::MaterialPropertyHeatAndMoistureTransferDiffusion_Impl> impl)
    : ModelObject(std::move(impl)) {}

  IddObjectType MaterialPropertyHeatAndMoistureTransferDiffusion::iddObjectType() {
    return IddObjectType::MaterialProperty_HeatAndMoistureTransfer_Diffusion;
  }

  int MaterialPropertyHeatAndMoistureTransferDiffusion::numberofDataPairs() const {
    return getImpl<detail::MaterialPropertyHeatAndMoistureTransferDiffusion_Impl>()->numberofDataPairs();
  }

  bool MaterialPropertyHeatAndMoistureTransferDiffusion::setNumberofDataPairs(int numberofDataPairs) {
    return getImpl<detail::MaterialPropertyHeatAndMoistureTransferDiffusion_Impl>()->setNumberofDataPairs(numberofDataPairs);
  }

  namespace detail {

    int MaterialPropertyHeatAndMoistureTransferDiffusion_Impl::numberofDataPairs() const {
      const auto value = getInt(openstudio::MaterialProperty_HeatAndMoistureTransfer_DiffusionFields::NumberofDataPairs, true);
      OS_ASSERT(value);
      return *value;
    }

    bool MaterialPropertyHeatAndMoistureTransferDiffusion_Impl::setNumberofDataPairs(int numberofDataPairs) {
      return setInt(openstudio::MaterialProperty_HeatAndMoistureTransfer_DiffusionFields::NumberofDataPairs, numberofDataPairs);
    }

  }  // namespace detail

}  // namespace epmodel
}  // namespace openstudio
