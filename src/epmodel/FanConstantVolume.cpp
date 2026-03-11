/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "FanConstantVolume.hpp"
#include "FanConstantVolume_Impl.hpp"

#include "Loop/AirLoopHVAC_Impl.hpp"
#include "HVACComponent/AirLoopHVACOutdoorAirSystem.hpp"
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
  auto airLoop = node.airLoopHVAC();
  auto oaSystem = node.airLoopHVACOutdoorAirSystem();

  // Parity with openstudio::model: allow insertion on AirLoop supply path and
  // OA-system-connected nodes (for contexts currently represented in epmodel).
  if ((airLoop && airLoop->supplyComponent(node.handle())) || oaSystem) {
    if (!StraightComponent_Impl::addToNode(node)) {
      return false;
    }

    // MixedAir SPM fan-node fields are derived from supply topology and must be
    // refreshed whenever a fan insertion mutates that topology.
    if (!airLoop && oaSystem) {
      airLoop = oaSystem->airLoopHVAC();
    }
    if (airLoop) {
      auto airLoopImpl = airLoop->getImpl<openstudio::epmodel::detail::AirLoopHVAC_Impl>();
      OS_ASSERT(airLoopImpl);
      airLoopImpl->syncSetpointManagerMixedAirFanNodes();
    }
    return true;
  }

  return false;
}

}  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
