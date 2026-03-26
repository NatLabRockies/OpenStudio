/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "Mixer.hpp"
#include "Mixer/Mixer_Impl.hpp"
#include "Loop/AirLoopHVAC.hpp"
#include "Model.hpp"
#include "StraightComponent/Node.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/idd/IddEnums.hxx>

namespace openstudio {
namespace epmodel {

namespace detail {

unsigned Mixer_Impl::nextInletPort() const {
  return inletPort(nextBranchIndex());
}

boost::optional<ModelObject> Mixer_Impl::outletModelObject() const {
  auto mixer = getObject<openstudio::epmodel::Mixer>();
  if (auto node = mixer.getModelObjectTarget<openstudio::epmodel::Node>(outletPort())) {
    return node->cast<ModelObject>();
  }
  return boost::none;
}

boost::optional<ModelObject> Mixer_Impl::inletModelObject(unsigned branchIndex) const {
  auto mixer = getObject<openstudio::epmodel::Mixer>();
  if (auto node = mixer.getModelObjectTarget<openstudio::epmodel::Node>(inletPort(branchIndex))) {
    return node->cast<ModelObject>();
  }
  return boost::none;
}

boost::optional<ModelObject> Mixer_Impl::lastInletModelObject() const {
  const auto inlets = inletModelObjects();
  if (!inlets.empty()) {
    return inlets.back();
  }
  return boost::none;
}

std::vector<ModelObject> Mixer_Impl::inletModelObjects() const {
  std::vector<ModelObject> result;
  const auto stop = nextBranchIndex();
  for (unsigned i = 0; i < stop; ++i) {
    if (auto modelObject = inletModelObject(i)) {
      result.push_back(*modelObject);
    }
  }
  return result;
}

unsigned Mixer_Impl::newInletPortAfterBranch(unsigned branchIndex) {
  const auto stop = nextBranchIndex();
  for (int i = static_cast<int>(stop) - 1; i > static_cast<int>(branchIndex); --i) {
    auto mo = inletModelObject(static_cast<unsigned>(i));
    OS_ASSERT(mo);
    if (!setInletModelObject(static_cast<unsigned>(i + 1), *mo)) {
      return inletPort(branchIndex);
    }
  }

  Model _model = model();
  Node node(_model);
  if (!setInletModelObject(branchIndex + 1u, node.cast<ModelObject>())) {
    return inletPort(branchIndex);
  }

  return inletPort(branchIndex);
}

unsigned Mixer_Impl::branchIndexForInletModelObject(const ModelObject& modelObject) const {
  const auto inlets = inletModelObjects();
  for (unsigned i = 0; i < inlets.size(); ++i) {
    if (inlets[i] == modelObject) {
      return i;
    }
  }
  return 0u;
}

unsigned Mixer_Impl::nextBranchIndex() const {
  unsigned i = 0u;
  while (inletModelObject(i)) {
    ++i;
  }
  return i;
}

void Mixer_Impl::removePortForBranch(unsigned branchIndex) {
  const auto next = nextBranchIndex();
  auto mixer = getObject<openstudio::epmodel::Mixer>();
  if (branchIndex >= next) {
    return;
  }

  mixer.setPointer(inletPort(branchIndex), Handle());
  for (unsigned i = branchIndex + 1; i < next; ++i) {
    auto mo = inletModelObject(i);
    OS_ASSERT(mo);
    if (!setInletModelObject(i - 1u, *mo)) {
      return;
    }
  }

  mixer.setPointer(inletPort(next - 1u), Handle());
}

bool Mixer_Impl::setInletModelObject(unsigned branchIndex, const ModelObject& modelObject) {
  auto mixer = getObject<openstudio::epmodel::Mixer>();
  if (modelObject.model() != mixer.model()) {
    return false;
  }
  return mixer.setPointer(inletPort(branchIndex), modelObject.handle());
}

}  // namespace detail

Mixer::Mixer(const Model& model) : HVACComponent(openstudio::IddObjectType::Catchall, model) {}

Mixer::Mixer(IddObjectType type, const Model& model) : HVACComponent(type, model) {}

Mixer::Mixer(std::shared_ptr<ImplType> impl) : HVACComponent(std::move(impl)) {}

boost::optional<ModelObject> Mixer::outletModelObject() const {
  return getImpl<detail::Mixer_Impl>()->outletModelObject();
}

unsigned Mixer::outletPort() const {
  return getImpl<detail::Mixer_Impl>()->outletPort();
}

unsigned Mixer::inletPort(unsigned branchIndex) const {
  return getImpl<detail::Mixer_Impl>()->inletPort(branchIndex);
}

unsigned Mixer::nextInletPort() const {
  return getImpl<detail::Mixer_Impl>()->nextInletPort();
}

std::vector<ModelObject> Mixer::inletModelObjects() const {
  return getImpl<detail::Mixer_Impl>()->inletModelObjects();
}

unsigned Mixer::newInletPortAfterBranch(unsigned branchIndex) {
  return getImpl<detail::Mixer_Impl>()->newInletPortAfterBranch(branchIndex);
}

unsigned Mixer::branchIndexForInletModelObject(const ModelObject& modelObject) const {
  return getImpl<detail::Mixer_Impl>()->branchIndexForInletModelObject(modelObject);
}

boost::optional<ModelObject> Mixer::inletModelObject(unsigned branchIndex) const {
  return getImpl<detail::Mixer_Impl>()->inletModelObject(branchIndex);
}

boost::optional<ModelObject> Mixer::lastInletModelObject() const {
  return getImpl<detail::Mixer_Impl>()->lastInletModelObject();
}

unsigned Mixer::nextBranchIndex() const {
  return getImpl<detail::Mixer_Impl>()->nextBranchIndex();
}

void Mixer::removePortForBranch(unsigned branchIndex) {
  return getImpl<detail::Mixer_Impl>()->removePortForBranch(branchIndex);
}

bool Mixer::setInletModelObject(unsigned branchIndex, const ModelObject& modelObject) {
  return getImpl<detail::Mixer_Impl>()->setInletModelObject(branchIndex, modelObject);
}

}  // namespace epmodel
}  // namespace openstudio
