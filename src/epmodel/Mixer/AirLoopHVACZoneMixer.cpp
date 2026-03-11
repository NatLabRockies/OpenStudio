/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "Mixer/AirLoopHVACZoneMixer.hpp"
#include "Mixer/AirLoopHVACZoneMixer_Impl.hpp"

#include "Loop/AirLoopHVAC.hpp"
#include "Loop/AirLoopHVAC_Impl.hpp"
#include "Model.hpp"
#include "Node.hpp"

#include <algorithm>
#include <utilities/core/Assert.hpp>
#include <utilities/idd/AirLoopHVAC_FieldEnums.hxx>
#include <utilities/idd/AirLoopHVAC_ZoneMixer_FieldEnums.hxx>
#include <utilities/idd/IddEnums.hxx>
#include <utilities/idf/IdfExtensibleGroup.hpp>
#include <utilities/idf/WorkspaceExtensibleGroup.hpp>

namespace openstudio {
namespace epmodel {

  AirLoopHVACZoneMixer::AirLoopHVACZoneMixer(const Model& model) : Mixer(AirLoopHVACZoneMixer::iddObjectType(), model) {
    auto impl = getImpl<detail::AirLoopHVACZoneMixer_Impl>();
    OS_ASSERT(impl);
    detail::LoadContext context{const_cast<Model&>(model), SanitizationPolicy::Repair, SanitizationReport{}, {}};  // NOLINT
    impl->canonicalize(context);
  }

  AirLoopHVACZoneMixer::AirLoopHVACZoneMixer(std::shared_ptr<detail::AirLoopHVACZoneMixer_Impl> impl) : Mixer(std::move(impl)) {}

  IddObjectType AirLoopHVACZoneMixer::iddObjectType() {
    return IddObjectType::AirLoopHVAC_ZoneMixer;
  }

  boost::optional<AirLoopHVAC> AirLoopHVACZoneMixer::airLoopHVAC() const {
    auto outletNode = getImpl<detail::AirLoopHVACZoneMixer_Impl>()->outletNode();
    if (!outletNode) {
      return boost::none;
    }

    const auto airLoops = model().getConcreteModelObjects<openstudio::epmodel::AirLoopHVAC>();
    const auto it = std::ranges::find_if(airLoops, [&](const auto& airLoop) { return *outletNode == airLoop.demandOutletNode(); });

    if (it != airLoops.end()) {
      return *it;
    }

    return boost::none;
  }

  unsigned AirLoopHVACZoneMixer::outletPort() const {
    return static_cast<unsigned>(openstudio::AirLoopHVAC_ZoneMixerFields::OutletNodeName);
  }

  unsigned AirLoopHVACZoneMixer::inletPort(unsigned branchIndex) const {
    return numNonextensibleFields() + branchIndex;
  }

  unsigned AirLoopHVACZoneMixer::nextInletPort() const {
    return inletPort(nextBranchIndex());
  }

  std::vector<ModelObject> AirLoopHVACZoneMixer::inletModelObjects() const {
    return Mixer::inletModelObjects();
  }

  unsigned AirLoopHVACZoneMixer::nextBranchIndex() const {
    return static_cast<unsigned>(inletModelObjects().size());
  }

  void AirLoopHVACZoneMixer::removePortForBranch(unsigned branchIndex) {
    if (branchIndex < extensibleGroups().size()) {
      eraseExtensibleGroup(branchIndex);
    }
  }

  bool AirLoopHVACZoneMixer::setInletModelObject(unsigned branchIndex, const ModelObject& modelObject) {
    if (modelObject.model() != model()) {
      return false;
    }

    auto groups = extensibleGroups();
    IdfExtensibleGroup group = (branchIndex < groups.size()) ? groups[branchIndex] : pushExtensibleGroup();
    auto workspaceGroup = group.optionalCast<openstudio::WorkspaceExtensibleGroup>();
    if (!workspaceGroup) {
      return false;
    }
    if (auto node = modelObject.optionalCast<openstudio::epmodel::Node>()) {
      if (!workspaceGroup->setString(openstudio::AirLoopHVAC_ZoneMixerExtensibleFields::InletNodeName, node->nameString())) {
        return false;
      }
    }
    return workspaceGroup->setPointer(openstudio::AirLoopHVAC_ZoneMixerExtensibleFields::InletNodeName, modelObject.handle(), false);
  }

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
  namespace detail {

    boost::optional<openstudio::epmodel::Node> AirLoopHVACZoneMixer_Impl::outletNode() const {
      if (auto node = getObject<openstudio::epmodel::AirLoopHVACZoneMixer>().getModelObjectTarget<openstudio::epmodel::Node>(
            openstudio::AirLoopHVAC_ZoneMixerFields::OutletNodeName)) {
        return node;
      }

      auto name = getString(openstudio::AirLoopHVAC_ZoneMixerFields::OutletNodeName);
      if (name && !name->empty()) {
        if (auto object = workspace().getObjectByTypeAndName(openstudio::IddObjectType::Node, *name, true)) {
          return object->optionalCast<openstudio::epmodel::Node>();
        }
      }

      return boost::none;
    }

    bool AirLoopHVACZoneMixer_Impl::setOutletNode(const openstudio::epmodel::Node& node) {
      return setPointer(openstudio::AirLoopHVAC_ZoneMixerFields::OutletNodeName, node.handle(), false);
    }

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
