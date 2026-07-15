/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "Mixer/AirLoopHVACReturnPlenum.hpp"
#include "Mixer/AirLoopHVACReturnPlenum_Impl.hpp"

#include "Model.hpp"

#include <utilities/idd/IddEnums.hxx>

namespace openstudio {
namespace epmodel {

  AirLoopHVACReturnPlenum::AirLoopHVACReturnPlenum(const Model& model) : ModelObject(AirLoopHVACReturnPlenum::iddObjectType(), model) {}

  AirLoopHVACReturnPlenum::AirLoopHVACReturnPlenum(std::shared_ptr<detail::AirLoopHVACReturnPlenum_Impl> impl) : ModelObject(std::move(impl)) {}

  IddObjectType AirLoopHVACReturnPlenum::iddObjectType() {
    return IddObjectType::AirLoopHVAC_ReturnPlenum;
  }

}  // namespace epmodel
}  // namespace openstudio
