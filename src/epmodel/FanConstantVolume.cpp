/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "FanConstantVolume.hpp"
#include "FanConstantVolume_Impl.hpp"

#include "Model.hpp"
#include "Node.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/idd/Fan_ConstantVolume_FieldEnums.hxx>
#include <utilities/idd/IddEnums.hxx>

namespace openstudio {
namespace epmodel {

FanConstantVolume::FanConstantVolume(const Model& model) : StraightComponent(FanConstantVolume::iddObjectType(), model) {
  auto impl = getImpl<detail::FanConstantVolume_Impl>();
  OS_ASSERT(impl);
  detail::LoadContext context{const_cast<Model&>(model), SanitizationPolicy::Repair, SanitizationReport{}, {}};  // NOLINT
  impl->canonicalize(context);
}

FanConstantVolume::FanConstantVolume(std::shared_ptr<detail::FanConstantVolume_Impl> impl) : StraightComponent(std::move(impl)) {}

IddObjectType FanConstantVolume::iddObjectType() {
  return IddObjectType::Fan_ConstantVolume;
}

bool FanConstantVolume::addToNode(Node& node) {
  return getImpl<detail::FanConstantVolume_Impl>()->addToNode(node);
}

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
namespace detail {

unsigned FanConstantVolume_Impl::inletPort() const {
  return Fan_ConstantVolumeFields::AirInletNodeName;
}

unsigned FanConstantVolume_Impl::outletPort() const {
  return Fan_ConstantVolumeFields::AirOutletNodeName;
}

bool FanConstantVolume_Impl::addToNode(Node& node) {
  // Delegate to StraightComponent implementation which edits the Branch extensible groups.
  return StraightComponent_Impl::addToNode(node);
}

}  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
