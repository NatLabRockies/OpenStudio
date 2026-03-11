/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "SetpointManagerMixedAir.hpp"
#include "SetpointManagerMixedAir_Impl.hpp"

#include "Loop/AirLoopHVAC.hpp"
#include "Loop/AirLoopHVAC_Impl.hpp"
#include "Model.hpp"
#include "Node.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/idd/IddEnums.hxx>
#include <utilities/idd/SetpointManager_MixedAir_FieldEnums.hxx>

namespace openstudio {
namespace epmodel {

SetpointManagerMixedAir::SetpointManagerMixedAir(const Model& model) : SetpointManager(SetpointManagerMixedAir::iddObjectType(), model) {
  auto impl = getImpl<detail::SetpointManagerMixedAir_Impl>();
  OS_ASSERT(impl);
  detail::LoadContext context{const_cast<Model&>(model), SanitizationPolicy::Repair, SanitizationReport{}, {}};  // NOLINT
  impl->canonicalize(context);
}

SetpointManagerMixedAir::SetpointManagerMixedAir(std::shared_ptr<detail::SetpointManagerMixedAir_Impl> impl)
  : SetpointManager(std::move(impl)) {}

IddObjectType SetpointManagerMixedAir::iddObjectType() {
  return IddObjectType::SetpointManager_MixedAir;
}

boost::optional<Node> SetpointManagerMixedAir::referenceSetpointNode() const {
  return getModelObjectTarget<Node>(openstudio::SetpointManager_MixedAirFields::ReferenceSetpointNodeName);
}

boost::optional<Node> SetpointManagerMixedAir::fanInletNode() const {
  return getModelObjectTarget<Node>(openstudio::SetpointManager_MixedAirFields::FanInletNodeName);
}

boost::optional<Node> SetpointManagerMixedAir::fanOutletNode() const {
  return getModelObjectTarget<Node>(openstudio::SetpointManager_MixedAirFields::FanOutletNodeName);
}

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
namespace detail {

bool SetpointManagerMixedAir_Impl::addToNode(Node& node) {
  if (!SetpointManager_Impl::addToNode(node)) {
    return false;
  }

  auto airLoop = node.airLoopHVAC();
  OS_ASSERT(airLoop);
  OS_ASSERT(setReferenceSetpointNode(airLoop->supplyOutletNode()));

  auto airLoopImpl = airLoop->getImpl<openstudio::epmodel::detail::AirLoopHVAC_Impl>();
  OS_ASSERT(airLoopImpl);
  airLoopImpl->syncSetpointManagerMixedAirFanNodes();
  return true;
}

bool SetpointManagerMixedAir_Impl::setReferenceSetpointNode(const Node& node) {
  return getObject<ModelObject>().setPointer(openstudio::SetpointManager_MixedAirFields::ReferenceSetpointNodeName, node.handle());
}

bool SetpointManagerMixedAir_Impl::setFanInletNode(const Node& node) {
  return getObject<ModelObject>().setPointer(openstudio::SetpointManager_MixedAirFields::FanInletNodeName, node.handle());
}

bool SetpointManagerMixedAir_Impl::setFanOutletNode(const Node& node) {
  return getObject<ModelObject>().setPointer(openstudio::SetpointManager_MixedAirFields::FanOutletNodeName, node.handle());
}

unsigned SetpointManagerMixedAir_Impl::setpointNodeFieldIndex() const {
  return openstudio::SetpointManager_MixedAirFields::SetpointNodeorNodeListName;
}

unsigned SetpointManagerMixedAir_Impl::controlVariableFieldIndex() const {
  return openstudio::SetpointManager_MixedAirFields::ControlVariable;
}

void SetpointManagerMixedAir_Impl::doCanonicalize(LoadContext& context) {
  SetpointManager_Impl::doCanonicalize(context);

  if (auto value = getString(openstudio::SetpointManager_MixedAirFields::ControlVariable, true)) {
    if (!value->empty()) {
      return;
    }
  }

  OS_ASSERT(setString(openstudio::SetpointManager_MixedAirFields::ControlVariable, "Temperature"));
  detail::addLoadInfo(context, "Set default Control Variable to 'Temperature' for SetpointManager:MixedAir '"
                                 + getObject<ModelObject>().nameString() + "'.");
}

}  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
