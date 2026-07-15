/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "GroundHeatTransferBasementYFACE.hpp"
#include "GroundHeatTransferBasementYFACE_Impl.hpp"

#include "Model.hpp"

#include <utilities/idd/IddEnums.hxx>

namespace openstudio {
namespace epmodel {

  GroundHeatTransferBasementYFACE::GroundHeatTransferBasementYFACE(const Model& model)
    : ModelObject(GroundHeatTransferBasementYFACE::iddObjectType(), model) {}

  GroundHeatTransferBasementYFACE::GroundHeatTransferBasementYFACE(std::shared_ptr<detail::GroundHeatTransferBasementYFACE_Impl> impl)
    : ModelObject(std::move(impl)) {}

  IddObjectType GroundHeatTransferBasementYFACE::iddObjectType() {
    return IddObjectType::GroundHeatTransfer_Basement_YFACE;
  }

}  // namespace epmodel
}  // namespace openstudio
