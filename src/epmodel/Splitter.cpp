/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "Splitter.hpp"
#include "AirLoopHVAC.hpp"
#include "Model.hpp"
#include "Node.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/idd/IddEnums.hxx>

namespace openstudio {
namespace epmodel {

Splitter::Splitter(const Model& model) : HVACComponent(openstudio::IddObjectType::Catchall, model) {}

Splitter::Splitter(IddObjectType type, const Model& model) : HVACComponent(type, model) {}

Splitter::Splitter(std::shared_ptr<detail::HVACComponent_Impl> impl) : HVACComponent(std::move(impl)) {}

boost::optional<ModelObject> Splitter::inletModelObject() const {
  const auto port = inletPort();
  if (auto inletNodeName = getString(port)) {
    if (inletNodeName->empty()) {
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

unsigned Splitter::inletPort() const {
  // Base Splitter has no concrete field mapping.
  return 0u;
}

unsigned Splitter::outletPort(unsigned branchIndex) const {
  // Base Splitter has no concrete field mapping.
  return branchIndex;
}

unsigned Splitter::nextOutletPort() const {
  return outletPort(nextBranchIndex());
}

std::vector<ModelObject> Splitter::outletModelObjects() const {
  std::vector<ModelObject> result;
  for (unsigned i = 0u;; ++i) {
    const auto port = outletPort(i);
    if (auto outletNodeName = getString(port)) {
      if (outletNodeName->empty()) {
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

unsigned Splitter::newOutletPortAfterBranch(unsigned branchIndex) {
  return outletPort(branchIndex + 1u);
}

unsigned Splitter::branchIndexForOutletModelObject(ModelObject modelObject) const {
  const auto outlets = outletModelObjects();
  for (unsigned i = 0u; i < outlets.size(); ++i) {
    if (outlets[i] == modelObject) {
      return i;
    }
  }
  return 0u;
}

boost::optional<ModelObject> Splitter::outletModelObject(unsigned branchIndex) const {
  const auto outlets = outletModelObjects();
  if (branchIndex < outlets.size()) {
    return outlets[branchIndex];
  }
  return boost::none;
}

boost::optional<ModelObject> Splitter::lastOutletModelObject() const {
  const auto outlets = outletModelObjects();
  if (!outlets.empty()) {
    return outlets.back();
  }
  return boost::none;
}

unsigned Splitter::nextBranchIndex() const {
  return static_cast<unsigned>(outletModelObjects().size());
}

void Splitter::removePortForBranch(unsigned branchIndex) {
  if (branchIndex < nextBranchIndex()) {
    setPointer(outletPort(branchIndex), Handle());
  }
}

bool Splitter::setOutletModelObject(unsigned branchIndex, const ModelObject& modelObject) {
  if (modelObject.model() != model()) {
    return false;
  }
  return setPointer(outletPort(branchIndex), modelObject.handle());
}

}  // namespace epmodel
}  // namespace openstudio
