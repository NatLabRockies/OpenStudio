/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "Splitter/Splitter.hpp"
#include "Splitter/Splitter_Impl.hpp"
#include "Loop/AirLoopHVAC.hpp"
#include "Model.hpp"
#include "StraightComponent/Node.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/idd/IddEnums.hxx>

namespace openstudio {
namespace epmodel {

namespace detail {

unsigned Splitter_Impl::nextOutletPort() const {
  return outletPort(nextBranchIndex());
}

boost::optional<ModelObject> Splitter_Impl::inletModelObject() const {
  auto splitter = getObject<openstudio::epmodel::Splitter>();
  if (auto node = splitter.getModelObjectTarget<openstudio::epmodel::Node>(inletPort())) {
    return node->cast<ModelObject>();
  }
  return boost::none;
}

boost::optional<ModelObject> Splitter_Impl::outletModelObject(unsigned branchIndex) const {
  auto splitter = getObject<openstudio::epmodel::Splitter>();
  if (auto node = splitter.getModelObjectTarget<openstudio::epmodel::Node>(outletPort(branchIndex))) {
    return node->cast<ModelObject>();
  }
  return boost::none;
}

boost::optional<ModelObject> Splitter_Impl::lastOutletModelObject() const {
  const auto outlets = outletModelObjects();
  if (!outlets.empty()) {
    return outlets.back();
  }
  return boost::none;
}

std::vector<ModelObject> Splitter_Impl::outletModelObjects() const {
  std::vector<ModelObject> result;
  const auto stop = nextBranchIndex();
  for (unsigned i = 0; i < stop; ++i) {
    if (auto modelObject = outletModelObject(i)) {
      result.push_back(*modelObject);
    }
  }
  return result;
}

unsigned Splitter_Impl::newOutletPortAfterBranch(unsigned branchIndex) {
  const auto stop = nextBranchIndex();
  for (int i = static_cast<int>(stop) - 1; i > static_cast<int>(branchIndex); --i) {
    auto mo = outletModelObject(static_cast<unsigned>(i));
    OS_ASSERT(mo);
    if (!setOutletModelObject(static_cast<unsigned>(i + 1), *mo)) {
      return outletPort(branchIndex);
    }
  }

  Model _model = model();
  Node node(_model);
  if (!setOutletModelObject(branchIndex + 1u, node.cast<ModelObject>())) {
    return outletPort(branchIndex);
  }

  return outletPort(branchIndex);
}

unsigned Splitter_Impl::branchIndexForOutletModelObject(ModelObject modelObject) const {
  const auto outlets = outletModelObjects();
  for (unsigned i = 0; i < outlets.size(); ++i) {
    if (outlets[i] == modelObject) {
      return i;
    }
  }
  return 0u;
}

unsigned Splitter_Impl::nextBranchIndex() const {
  unsigned i = 0u;
  while (outletModelObject(i)) {
    ++i;
  }
  return i;
}

void Splitter_Impl::removePortForBranch(unsigned branchIndex) {
  const auto next = nextBranchIndex();
  auto splitter = getObject<openstudio::epmodel::Splitter>();
  if (branchIndex >= next) {
    return;
  }

  splitter.setPointer(outletPort(branchIndex), Handle());
  for (unsigned i = branchIndex + 1; i < next; ++i) {
    auto mo = outletModelObject(i);
    OS_ASSERT(mo);
    if (!setOutletModelObject(i - 1u, *mo)) {
      return;
    }
  }

  splitter.setPointer(outletPort(next - 1u), Handle());
}

bool Splitter_Impl::setOutletModelObject(unsigned branchIndex, const ModelObject& modelObject) {
  auto splitter = getObject<openstudio::epmodel::Splitter>();
  if (modelObject.model() != splitter.model()) {
    return false;
  }
  return splitter.setPointer(outletPort(branchIndex), modelObject.handle());
}

}  // namespace detail

Splitter::Splitter(const Model& model) : HVACComponent(openstudio::IddObjectType::Catchall, model) {}

Splitter::Splitter(IddObjectType type, const Model& model) : HVACComponent(type, model) {}

Splitter::Splitter(std::shared_ptr<ImplType> impl) : HVACComponent(std::move(impl)) {}

boost::optional<ModelObject> Splitter::inletModelObject() const {
  return getImpl<detail::Splitter_Impl>()->inletModelObject();
}

unsigned Splitter::inletPort() const {
  return getImpl<detail::Splitter_Impl>()->inletPort();
}

unsigned Splitter::outletPort(unsigned branchIndex) const {
  return getImpl<detail::Splitter_Impl>()->outletPort(branchIndex);
}

unsigned Splitter::nextOutletPort() const {
  return getImpl<detail::Splitter_Impl>()->nextOutletPort();
}

std::vector<ModelObject> Splitter::outletModelObjects() const {
  return getImpl<detail::Splitter_Impl>()->outletModelObjects();
}

unsigned Splitter::newOutletPortAfterBranch(unsigned branchIndex) {
  return getImpl<detail::Splitter_Impl>()->newOutletPortAfterBranch(branchIndex);
}

unsigned Splitter::branchIndexForOutletModelObject(ModelObject modelObject) const {
  return getImpl<detail::Splitter_Impl>()->branchIndexForOutletModelObject(modelObject);
}

boost::optional<ModelObject> Splitter::outletModelObject(unsigned branchIndex) const {
  return getImpl<detail::Splitter_Impl>()->outletModelObject(branchIndex);
}

boost::optional<ModelObject> Splitter::lastOutletModelObject() const {
  return getImpl<detail::Splitter_Impl>()->lastOutletModelObject();
}

unsigned Splitter::nextBranchIndex() const {
  return getImpl<detail::Splitter_Impl>()->nextBranchIndex();
}

void Splitter::removePortForBranch(unsigned branchIndex) {
  return getImpl<detail::Splitter_Impl>()->removePortForBranch(branchIndex);
}

bool Splitter::setOutletModelObject(unsigned branchIndex, const ModelObject& modelObject) {
  return getImpl<detail::Splitter_Impl>()->setOutletModelObject(branchIndex, modelObject);
}

}  // namespace epmodel
}  // namespace openstudio
