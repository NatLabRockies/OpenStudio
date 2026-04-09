/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "OutdoorAirMixer.hpp"
#include "OutdoorAirMixer_Impl.hpp"

#include "Model.hpp"
#include "Node.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/idd/IddEnums.hxx>
#include <utilities/idd/OutdoorAir_Mixer_FieldEnums.hxx>

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
      (void)context;
      resolvedNodeTarget(mixedAirNodeField);
      resolvedNodeTarget(outdoorAirNodeField);
      resolvedNodeTarget(reliefAirNodeField);
      resolvedNodeTarget(returnAirNodeField);
    }

  }  // namespace detail

}  // namespace epmodel
}  // namespace openstudio
