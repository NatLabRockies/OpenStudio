/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "AirLoopHVACMixer.hpp"
#include "AirLoopHVACMixer_Impl.hpp"

#include "Model.hpp"

#include <utilities/idd/IddEnums.hxx>

namespace openstudio {
namespace epmodel {

  AirLoopHVACMixer::AirLoopHVACMixer(const Model& model) : ModelObject(AirLoopHVACMixer::iddObjectType(), model) {}

  AirLoopHVACMixer::AirLoopHVACMixer(std::shared_ptr<detail::AirLoopHVACMixer_Impl> impl) : ModelObject(std::move(impl)) {}

  IddObjectType AirLoopHVACMixer::iddObjectType() {
    return IddObjectType::AirLoopHVAC_Mixer;
  }

}  // namespace epmodel
}  // namespace openstudio
