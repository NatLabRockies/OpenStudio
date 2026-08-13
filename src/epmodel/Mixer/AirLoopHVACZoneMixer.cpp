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
    return getImpl<detail::AirLoopHVACZoneMixer_Impl>()->outletPort();
  }

  unsigned AirLoopHVACZoneMixer::inletPort(unsigned branchIndex) const {
    return getImpl<detail::AirLoopHVACZoneMixer_Impl>()->inletPort(branchIndex);
  }

  unsigned AirLoopHVACZoneMixer::nextInletPort() const {
    return getImpl<detail::AirLoopHVACZoneMixer_Impl>()->nextInletPort();
  }

  std::vector<ModelObject> AirLoopHVACZoneMixer::inletModelObjects() const {
    return getImpl<detail::AirLoopHVACZoneMixer_Impl>()->inletModelObjects();
  }

  unsigned AirLoopHVACZoneMixer::nextBranchIndex() const {
    return getImpl<detail::AirLoopHVACZoneMixer_Impl>()->nextBranchIndex();
  }

  void AirLoopHVACZoneMixer::removePortForBranch(unsigned branchIndex) {
    return getImpl<detail::AirLoopHVACZoneMixer_Impl>()->removePortForBranch(branchIndex);
  }

  bool AirLoopHVACZoneMixer::setInletModelObject(unsigned branchIndex, const ModelObject& modelObject) {
    return getImpl<detail::AirLoopHVACZoneMixer_Impl>()->setInletModelObject(branchIndex, modelObject);
  }

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
  namespace detail {

    unsigned AirLoopHVACZoneMixer_Impl::outletPort() const {
      return static_cast<unsigned>(openstudio::AirLoopHVAC_ZoneMixerFields::OutletNodeName);
    }

    unsigned AirLoopHVACZoneMixer_Impl::inletPort(unsigned branchIndex) const {
      return getObject<openstudio::epmodel::AirLoopHVACZoneMixer>().numNonextensibleFields() + branchIndex;
    }

    void AirLoopHVACZoneMixer_Impl::removePortForBranch(unsigned branchIndex) {
      auto mixer = getObject<openstudio::epmodel::AirLoopHVACZoneMixer>();
      if (branchIndex < mixer.extensibleGroups().size()) {
        mixer.eraseExtensibleGroup(branchIndex);
      }
    }

    bool AirLoopHVACZoneMixer_Impl::setInletModelObject(unsigned branchIndex, const openstudio::epmodel::ModelObject& modelObject) {
      auto mixer = getObject<openstudio::epmodel::AirLoopHVACZoneMixer>();
      if (modelObject.model() != mixer.model()) {
        return false;
      }

      while (mixer.extensibleGroups().size() <= branchIndex) {
        mixer.pushExtensibleGroup();
      }

      const auto groups = mixer.extensibleGroups();
      auto workspaceGroup = groups[branchIndex].optionalCast<openstudio::WorkspaceExtensibleGroup>();
      if (!workspaceGroup) {
        return false;
      }

      return workspaceGroup->setPointer(openstudio::AirLoopHVAC_ZoneMixerExtensibleFields::InletNodeName, modelObject.handle(), false);
    }

    boost::optional<openstudio::epmodel::Node> AirLoopHVACZoneMixer_Impl::outletNode() const {
      if (auto node = getObject<openstudio::epmodel::AirLoopHVACZoneMixer>().getModelObjectTarget<openstudio::epmodel::Node>(
            openstudio::AirLoopHVAC_ZoneMixerFields::OutletNodeName)) {
        return node;
      }

      auto name = getString(openstudio::AirLoopHVAC_ZoneMixerFields::OutletNodeName);
      if (name && !name->empty()) {
        if (auto object = workspace().getObjectByTypeAndName(openstudio::IddObjectType::Node, *name)) {
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
