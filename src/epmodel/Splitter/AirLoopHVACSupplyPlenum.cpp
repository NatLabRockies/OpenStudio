/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "Splitter/AirLoopHVACSupplyPlenum.hpp"
#include "Splitter/AirLoopHVACSupplyPlenum_Impl.hpp"

#include "Model.hpp"

#include <utilities/idd/IddEnums.hxx>

namespace openstudio {
namespace epmodel {

  AirLoopHVACSupplyPlenum::AirLoopHVACSupplyPlenum(const Model& model) : ModelObject(AirLoopHVACSupplyPlenum::iddObjectType(), model) {}

  AirLoopHVACSupplyPlenum::AirLoopHVACSupplyPlenum(std::shared_ptr<detail::AirLoopHVACSupplyPlenum_Impl> impl) : ModelObject(std::move(impl)) {}

  IddObjectType AirLoopHVACSupplyPlenum::iddObjectType() {
    return IddObjectType::AirLoopHVAC_SupplyPlenum;
  }

}  // namespace epmodel
}  // namespace openstudio
