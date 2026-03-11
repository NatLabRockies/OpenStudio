/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "GroundHeatTransferBasementZFACE.hpp"
#include "GroundHeatTransferBasementZFACE_Impl.hpp"

#include "Model.hpp"

#include <utilities/idd/IddEnums.hxx>

namespace openstudio {
namespace epmodel {

GroundHeatTransferBasementZFACE::GroundHeatTransferBasementZFACE(const Model& model)
  : ModelObject(GroundHeatTransferBasementZFACE::iddObjectType(), model) {}

GroundHeatTransferBasementZFACE::GroundHeatTransferBasementZFACE(std::shared_ptr<detail::GroundHeatTransferBasementZFACE_Impl> impl)
  : ModelObject(std::move(impl)) {}

IddObjectType GroundHeatTransferBasementZFACE::iddObjectType() {
  return IddObjectType::GroundHeatTransfer_Basement_ZFACE;
}

}  // namespace epmodel
}  // namespace openstudio
