/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "GroundHeatTransferSlabXFACE.hpp"
#include "GroundHeatTransferSlabXFACE_Impl.hpp"

#include "Model.hpp"

#include <utilities/idd/IddEnums.hxx>

namespace openstudio {
namespace epmodel {

  GroundHeatTransferSlabXFACE::GroundHeatTransferSlabXFACE(const Model& model) : ModelObject(GroundHeatTransferSlabXFACE::iddObjectType(), model) {}

  GroundHeatTransferSlabXFACE::GroundHeatTransferSlabXFACE(std::shared_ptr<detail::GroundHeatTransferSlabXFACE_Impl> impl)
    : ModelObject(std::move(impl)) {}

  IddObjectType GroundHeatTransferSlabXFACE::iddObjectType() {
    return IddObjectType::GroundHeatTransfer_Slab_XFACE;
  }

}  // namespace epmodel
}  // namespace openstudio
