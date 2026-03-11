/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "Mixer.hpp"
#include "Loop/AirLoopHVAC.hpp"
#include "Model.hpp"
#include "Node.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/idd/IddEnums.hxx>

namespace openstudio {
namespace epmodel {

Mixer::Mixer(const Model& model) : HVACComponent(openstudio::IddObjectType::Catchall, model) {}

Mixer::Mixer(IddObjectType type, const Model& model) : HVACComponent(type, model) {}

Mixer::Mixer(std::shared_ptr<detail::HVACComponent_Impl> impl) : HVACComponent(std::move(impl)) {}

boost::optional<ModelObject> Mixer::outletModelObject() const {
  const auto port = outletPort();
  if (auto nodeName = getString(port)) {
    if (nodeName->empty()) {
      return boost::none;
    }
    if (auto node = getModelObjectTarget<openstudio::epmodel::Node>(port)) {
      return node->cast<ModelObject>();
    }
    OS_ASSERT(false);
    return boost::none;
  }
  return boost::none;
}

unsigned Mixer::outletPort() const {
  // Base Mixer has no concrete field mapping.
  return 0u;
}

unsigned Mixer::inletPort(unsigned branchIndex) const {
  // Base Mixer has no concrete field mapping.
  return branchIndex;
}

unsigned Mixer::nextInletPort() const {
  return inletPort(nextBranchIndex());
}

std::vector<ModelObject> Mixer::inletModelObjects() const {
  std::vector<ModelObject> result;
  for (unsigned i = 0u;; ++i) {
    const auto port = inletPort(i);
    if (auto inletNodeName = getString(port)) {
      if (inletNodeName->empty()) {
        break;
      }
      if (auto node = getModelObjectTarget<openstudio::epmodel::Node>(port)) {
        result.emplace_back(node->cast<ModelObject>());
        continue;
      }
      OS_ASSERT(false);
      break;
    }
    break;
  }
  return result;
}

unsigned Mixer::newInletPortAfterBranch(unsigned branchIndex) {
  return inletPort(branchIndex + 1u);
}

unsigned Mixer::branchIndexForInletModelObject(const ModelObject& modelObject) const {
  const auto inlets = inletModelObjects();
  for (unsigned i = 0u; i < inlets.size(); ++i) {
    if (inlets[i] == modelObject) {
      return i;
    }
  }
  return 0u;
}

boost::optional<ModelObject> Mixer::inletModelObject(unsigned branchIndex) const {
  const auto inlets = inletModelObjects();
  if (branchIndex < inlets.size()) {
    return inlets[branchIndex];
  }
  return boost::none;
}

boost::optional<ModelObject> Mixer::lastInletModelObject() const {
  const auto inlets = inletModelObjects();
  if (!inlets.empty()) {
    return inlets.back();
  }
  return boost::none;
}

unsigned Mixer::nextBranchIndex() const {
  return static_cast<unsigned>(inletModelObjects().size());
}

void Mixer::removePortForBranch(unsigned branchIndex) {
  if (branchIndex < nextBranchIndex()) {
    setPointer(inletPort(branchIndex), Handle());
  }
}

bool Mixer::setInletModelObject(unsigned branchIndex, const ModelObject& modelObject) {
  if (modelObject.model() != model()) {
    return false;
  }
  return setPointer(inletPort(branchIndex), modelObject.handle());
}

}  // namespace epmodel
}  // namespace openstudio
