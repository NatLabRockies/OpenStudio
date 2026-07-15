/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "GroundHeatTransferBasementXFACE.hpp"
#include "GroundHeatTransferBasementXFACE_Impl.hpp"

#include "Model.hpp"

#include <utilities/idd/IddEnums.hxx>

namespace openstudio {
namespace epmodel {

  GroundHeatTransferBasementXFACE::GroundHeatTransferBasementXFACE(const Model& model)
    : ModelObject(GroundHeatTransferBasementXFACE::iddObjectType(), model) {}

  GroundHeatTransferBasementXFACE::GroundHeatTransferBasementXFACE(std::shared_ptr<detail::GroundHeatTransferBasementXFACE_Impl> impl)
    : ModelObject(std::move(impl)) {}

  IddObjectType GroundHeatTransferBasementXFACE::iddObjectType() {
    return IddObjectType::GroundHeatTransfer_Basement_XFACE;
  }

}  // namespace epmodel
}  // namespace openstudio
