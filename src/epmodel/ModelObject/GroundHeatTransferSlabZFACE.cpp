/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "GroundHeatTransferSlabZFACE.hpp"
#include "GroundHeatTransferSlabZFACE_Impl.hpp"

#include "Model.hpp"

#include <utilities/idd/IddEnums.hxx>

namespace openstudio {
namespace epmodel {

GroundHeatTransferSlabZFACE::GroundHeatTransferSlabZFACE(const Model& model)
  : ModelObject(GroundHeatTransferSlabZFACE::iddObjectType(), model) {}

GroundHeatTransferSlabZFACE::GroundHeatTransferSlabZFACE(std::shared_ptr<detail::GroundHeatTransferSlabZFACE_Impl> impl)
  : ModelObject(std::move(impl)) {}

IddObjectType GroundHeatTransferSlabZFACE::iddObjectType() {
  return IddObjectType::GroundHeatTransfer_Slab_ZFACE;
}

}  // namespace epmodel
}  // namespace openstudio
