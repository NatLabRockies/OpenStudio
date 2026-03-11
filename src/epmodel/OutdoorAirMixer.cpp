/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "OutdoorAirMixer.hpp"
#include "OutdoorAirMixer_Impl.hpp"

#include "Model.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/idd/IddEnums.hxx>

namespace openstudio {
namespace epmodel {

OutdoorAirMixer::OutdoorAirMixer(const Model& model) : ModelObject(OutdoorAirMixer::iddObjectType(), model) {
  auto impl = getImpl<detail::OutdoorAirMixer_Impl>();
  OS_ASSERT(impl);
  detail::LoadContext context{const_cast<Model&>(model), SanitizationPolicy::Repair, SanitizationReport{}, {}};  // NOLINT
  impl->canonicalize(context);
}

OutdoorAirMixer::OutdoorAirMixer(std::shared_ptr<detail::OutdoorAirMixer_Impl> impl) : ModelObject(std::move(impl)) {}

IddObjectType OutdoorAirMixer::iddObjectType() {
  return IddObjectType::OutdoorAir_Mixer;
}

}  // namespace epmodel
}  // namespace openstudio
