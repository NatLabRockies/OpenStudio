/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "SetpointManager.hpp"
#include "SetpointManager_Impl.hpp"

#include "Loop/AirLoopHVAC.hpp"
#include "HVACComponent/AirLoopHVACOutdoorAirSystem.hpp"
#include "Model.hpp"
#include "Node.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/core/Compare.hpp>

namespace openstudio {
namespace epmodel {

SetpointManager::SetpointManager(IddObjectType type, const Model& model) : HVACComponent(type, model) {
  OS_ASSERT(getImpl<detail::SetpointManager_Impl>());
}

SetpointManager::SetpointManager(std::shared_ptr<detail::SetpointManager_Impl> impl) : HVACComponent(std::move(impl)) {}

boost::optional<Node> SetpointManager::setpointNode() const {
  return getImpl<detail::SetpointManager_Impl>()->setpointNode();
}

std::string SetpointManager::controlVariable() const {
  return getImpl<detail::SetpointManager_Impl>()->controlVariable();
}

bool SetpointManager::setControlVariable(const std::string& value) {
  return getImpl<detail::SetpointManager_Impl>()->setControlVariable(value);
}

bool SetpointManager::isAllowedOnPlantLoop() const {
  return getImpl<detail::SetpointManager_Impl>()->isAllowedOnPlantLoop();
}

bool SetpointManager::addToNode(Node& node) {
  return getImpl<detail::SetpointManager_Impl>()->addToNode(node);
}

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
namespace detail {

bool SetpointManager_Impl::isAllowedOnPlantLoop() const {
  return false;
}

bool SetpointManager_Impl::addToNode(openstudio::epmodel::Node& node) {
  auto thisObject = getObject<openstudio::epmodel::SetpointManager>();
  if (node.model() != thisObject.model()) {
    return false;
  }

  // Keep one SPM per control variable on the node, matching model behavior.
  for (const auto& object : model().objects()) {
    auto spm = object.optionalCast<openstudio::epmodel::SetpointManager>();
    if (!spm || (*spm == thisObject)) {
      continue;
    }

    auto spmNode = spm->setpointNode();
    if (!spmNode || (*spmNode != node)) {
      continue;
    }

    if (openstudio::istringEqual(spm->controlVariable(), thisObject.controlVariable())) {
      spm->remove();
    }
  }

  if (auto airLoop = node.airLoopHVAC()) {
    if (airLoop->supplyComponent(node.handle())) {
      return setSetpointNode(node);
    }
  }

  if (auto oaSystem = node.airLoopHVACOutdoorAirSystem()) {
    // Match model behavior: OA outboard nodes are never valid SPM placement
    // points, while other OA-system nodes are allowed.
    if (auto outboardOANode = oaSystem->outboardOANode()) {
      if (*outboardOANode == node) {
        return false;
      }
    }
    if (auto outboardReliefNode = oaSystem->outboardReliefNode()) {
      if (*outboardReliefNode == node) {
        return false;
      }
    }
    return setSetpointNode(node);
  }

  return false;
}

void SetpointManager_Impl::doCanonicalize(LoadContext& context) {
  (void)context;
}

void SetpointManager_Impl::canonicalizeSetpointNodeField(LoadContext& context, unsigned field) {
  (void)context;
  if (auto nodeName = getString(field)) {
    if (!nodeName->empty()) {
      auto node = model().getOrCreateTransientByName<openstudio::epmodel::Node>(*nodeName);
      OS_ASSERT(getObject<ModelObject>().setPointer(field, node.handle()));
    }
  }
}

}  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
