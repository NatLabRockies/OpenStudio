/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "GroundHeatTransferSlabYFACE.hpp"
#include "GroundHeatTransferSlabYFACE_Impl.hpp"

#include "Model.hpp"

#include <utilities/idd/IddEnums.hxx>

namespace openstudio {
namespace epmodel {

GroundHeatTransferSlabYFACE::GroundHeatTransferSlabYFACE(const Model& model)
  : ModelObject(GroundHeatTransferSlabYFACE::iddObjectType(), model) {}

GroundHeatTransferSlabYFACE::GroundHeatTransferSlabYFACE(std::shared_ptr<detail::GroundHeatTransferSlabYFACE_Impl> impl)
  : ModelObject(std::move(impl)) {}

IddObjectType GroundHeatTransferSlabYFACE::iddObjectType() {
  return IddObjectType::GroundHeatTransfer_Slab_YFACE;
}

}  // namespace epmodel
}  // namespace openstudio
