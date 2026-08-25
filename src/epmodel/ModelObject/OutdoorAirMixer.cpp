/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "OutdoorAirMixer.hpp"
#include "OutdoorAirMixer_Impl.hpp"

#include "Model.hpp"
#include "Node.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/core/StringHelpers.hpp>
#include <utilities/idd/IddEnums.hxx>
#include <utilities/idd/OutdoorAir_Mixer_FieldEnums.hxx>
#include <utilities/idf/IdfObject_Impl.hpp>
#include <utilities/idf/WorkspaceObject_Impl.hpp>

#include <array>

namespace openstudio {
namespace epmodel {

  OutdoorAirMixer::OutdoorAirMixer(const Model& model) : ModelObject(OutdoorAirMixer::iddObjectType(), model) {
    auto impl = getImpl<detail::OutdoorAirMixer_Impl>();
    OS_ASSERT(impl);
    detail::LoadContext context{const_cast<Model&>(model), SanitizationPolicy::Repair, SanitizationReport{}, {}};  // NOLINT
    impl->canonicalize(context);
  }

  OutdoorAirMixer::OutdoorAirMixer(std::shared_ptr<detail::OutdoorAirMixer_Impl> impl) : ModelObject(std::move(impl)) {}

  IddObjectType OutdoorAirMixer::iddObjectType() {
    return IddObjectType::OutdoorAir_Mixer;
  }

  boost::optional<Node> OutdoorAirMixer::mixedAirNode() const {
    return getImpl<detail::OutdoorAirMixer_Impl>()->mixedAirNode();
  }

  boost::optional<Node> OutdoorAirMixer::outdoorAirNode() const {
    return getImpl<detail::OutdoorAirMixer_Impl>()->outdoorAirNode();
  }

  boost::optional<Node> OutdoorAirMixer::reliefAirNode() const {
    return getImpl<detail::OutdoorAirMixer_Impl>()->reliefAirNode();
  }

  boost::optional<Node> OutdoorAirMixer::returnAirNode() const {
    return getImpl<detail::OutdoorAirMixer_Impl>()->returnAirNode();
  }

  namespace detail {

    constexpr unsigned mixedAirNodeField = openstudio::OutdoorAir_MixerFields::MixedAirNodeName;
    constexpr unsigned outdoorAirNodeField = openstudio::OutdoorAir_MixerFields::OutdoorAirStreamNodeName;
    constexpr unsigned reliefAirNodeField = openstudio::OutdoorAir_MixerFields::ReliefAirStreamNodeName;
    constexpr unsigned returnAirNodeField = openstudio::OutdoorAir_MixerFields::ReturnAirStreamNodeName;

    boost::optional<openstudio::epmodel::Node> OutdoorAirMixer_Impl::mixedAirNode() const {
      return resolvedNodeTarget(mixedAirNodeField);
    }

    boost::optional<openstudio::epmodel::Node> OutdoorAirMixer_Impl::outdoorAirNode() const {
      return resolvedNodeTarget(outdoorAirNodeField);
    }

    boost::optional<openstudio::epmodel::Node> OutdoorAirMixer_Impl::reliefAirNode() const {
      return resolvedNodeTarget(reliefAirNodeField);
    }

    boost::optional<openstudio::epmodel::Node> OutdoorAirMixer_Impl::returnAirNode() const {
      return resolvedNodeTarget(returnAirNodeField);
    }

    bool OutdoorAirMixer_Impl::setMixedAirNode(const openstudio::epmodel::Node& node) {
      if (node.model() != model()) {
        return false;
      }
      return getObject<openstudio::epmodel::OutdoorAirMixer>().setPointer(mixedAirNodeField, node.handle());
    }

    bool OutdoorAirMixer_Impl::setOutdoorAirNode(const openstudio::epmodel::Node& node) {
      if (node.model() != model()) {
        return false;
      }
      return getObject<openstudio::epmodel::OutdoorAirMixer>().setPointer(outdoorAirNodeField, node.handle());
    }

    bool OutdoorAirMixer_Impl::setReliefAirNode(const openstudio::epmodel::Node& node) {
      if (node.model() != model()) {
        return false;
      }
      return getObject<openstudio::epmodel::OutdoorAirMixer>().setPointer(reliefAirNodeField, node.handle());
    }

    bool OutdoorAirMixer_Impl::setReturnAirNode(const openstudio::epmodel::Node& node) {
      if (node.model() != model()) {
        return false;
      }
      return getObject<openstudio::epmodel::OutdoorAirMixer>().setPointer(returnAirNodeField, node.handle());
    }

    void OutdoorAirMixer_Impl::doCanonicalize(LoadContext& context) {
      const auto mixer = getObject<OutdoorAirMixer>();
      auto workspaceImpl = mixer.getImpl<openstudio::detail::WorkspaceObject_Impl>();
      OS_ASSERT(workspaceImpl);
      const std::array fields = {mixedAirNodeField, outdoorAirNodeField, reliefAirNodeField, returnAirNodeField};
      for (const auto field : fields) {
        const auto stored = mixer.getField(field, false);
        const auto raw = workspaceImpl->openstudio::detail::IdfObject_Impl::getString(field, false, true);
        const bool hasRaw = raw && !raw->empty();
        boost::optional<Node> managed;
        if (stored && !stored->empty()) {
          const auto handle = openstudio::toUUID(*stored);
          const auto target = handle.isNull() ? boost::optional<WorkspaceObject>() : model().getObject(handle);
          managed = target ? target->optionalCast<Node>() : boost::none;
        }

        if (managed) {
          unsigned sameNameCount = 0u;
          for (const auto& node : model().getConcreteModelObjects<Node>()) {
            if (openstudio::istringEqual(node.nameString(), managed->nameString())) {
              ++sameNameCount;
            }
          }
          const auto rawHandle = hasRaw ? openstudio::toUUID(*raw) : Handle();
          const bool rawAgrees = !hasRaw || (!rawHandle.isNull() && rawHandle == managed->handle())
                                 || (rawHandle.isNull() && openstudio::istringEqual(*raw, managed->nameString()));
          if (sameNameCount != 1u || !rawAgrees) {
            detail::addLoadWarning(context, "Preserved ambiguous OutdoorAir:Mixer node evidence on '" + mixer.nameString() + "'.");
          }
          continue;
        }
        if (!hasRaw) {
          continue;
        }

        boost::optional<Node> uniqueNode;
        const auto rawHandle = openstudio::toUUID(*raw);
        for (const auto& node : model().getConcreteModelObjects<Node>()) {
          const bool matches =
            (!rawHandle.isNull() && node.handle() == rawHandle) || (rawHandle.isNull() && openstudio::istringEqual(node.nameString(), *raw));
          if (!matches) {
            continue;
          }
          if (uniqueNode) {
            uniqueNode = boost::none;
            break;
          }
          uniqueNode = node;
        }
        if (!uniqueNode) {
          detail::addLoadWarning(context, "Preserved unresolved or ambiguous OutdoorAir:Mixer node evidence on '" + mixer.nameString() + "'.");
          continue;
        }
        if (context.repairEnabled()) {
          OS_ASSERT(setPointer(field, uniqueNode->handle(), false));
          detail::addLoadInfo(context, "Resolved an OutdoorAir:Mixer node relationship on '" + mixer.nameString() + "'.");
        } else {
          detail::addLoadWarning(context, "OutdoorAir:Mixer '" + mixer.nameString() + "' has an unresolved managed node relationship.");
        }
      }
    }

  }  // namespace detail

}  // namespace epmodel
}  // namespace openstudio
