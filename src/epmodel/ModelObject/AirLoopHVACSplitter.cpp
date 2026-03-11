/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "AirLoopHVACSplitter.hpp"
#include "AirLoopHVACSplitter_Impl.hpp"

#include "Model.hpp"

#include <utilities/idd/IddEnums.hxx>

namespace openstudio {
namespace epmodel {

AirLoopHVACSplitter::AirLoopHVACSplitter(const Model& model) : ModelObject(AirLoopHVACSplitter::iddObjectType(), model) {}

AirLoopHVACSplitter::AirLoopHVACSplitter(std::shared_ptr<detail::AirLoopHVACSplitter_Impl> impl) : ModelObject(std::move(impl)) {}

IddObjectType AirLoopHVACSplitter::iddObjectType() {
  return IddObjectType::AirLoopHVAC_Splitter;
}

}  // namespace epmodel
}  // namespace openstudio
