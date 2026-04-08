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

namespace detail {

// OutdoorAirMixer owns these field-to-node conversions. Callers should use the
// typed owner methods instead of reaching into raw mixer fields from unrelated
// HVAC topology code.
constexpr unsigned mixedAirNodeField() {
  return openstudio::OutdoorAir_MixerFields::MixedAirNodeName;
}

constexpr unsigned outdoorAirNodeField() {
  return openstudio::OutdoorAir_MixerFields::OutdoorAirStreamNodeName;
}

constexpr unsigned reliefAirNodeField() {
  return openstudio::OutdoorAir_MixerFields::ReliefAirStreamNodeName;
}

constexpr unsigned returnAirNodeField() {
  return openstudio::OutdoorAir_MixerFields::ReturnAirStreamNodeName;
}

bool assignNodeAtField(OutdoorAirMixer_Impl& impl, unsigned fieldIndex, const openstudio::epmodel::Node& node) {
  auto mixer = impl.getObject<openstudio::epmodel::OutdoorAirMixer>();
  if (node.model() != mixer.model()) {
    return false;
  }
  return mixer.setPointer(fieldIndex, node.handle());
}

void reconcileNamedNodeField(OutdoorAirMixer_Impl& impl, unsigned fieldIndex) {
  if (auto node = impl.getObject<openstudio::epmodel::OutdoorAirMixer>().getModelObjectTarget<openstudio::epmodel::Node>(fieldIndex)) {
    return;
  }

  auto existingName = impl.getString(fieldIndex);
  if (existingName && !existingName->empty()) {
    if (auto object = impl.workspace().getObjectByTypeAndName(openstudio::IddObjectType::Node, *existingName, true)) {
      if (object->optionalCast<openstudio::epmodel::Node>()) {
        return;
      }
    }
  }

  auto nodeName = impl.getString(fieldIndex);
  if (!(nodeName && !nodeName->empty())) {
    return;
  }

  auto node = impl.model().getOrCreateTransientByName<openstudio::epmodel::Node>(*nodeName);
  OS_ASSERT(assignNodeAtField(impl, fieldIndex, node));
}

boost::optional<openstudio::epmodel::Node> OutdoorAirMixer_Impl::mixedAirNode() const {
  return resolvedNodeTarget(mixedAirNodeField());
}

boost::optional<openstudio::epmodel::Node> OutdoorAirMixer_Impl::outdoorAirNode() const {
  return resolvedNodeTarget(outdoorAirNodeField());
}

boost::optional<openstudio::epmodel::Node> OutdoorAirMixer_Impl::reliefAirNode() const {
  return resolvedNodeTarget(reliefAirNodeField());
}

boost::optional<openstudio::epmodel::Node> OutdoorAirMixer_Impl::returnAirNode() const {
  return resolvedNodeTarget(returnAirNodeField());
}

bool OutdoorAirMixer_Impl::setMixedAirNode(const openstudio::epmodel::Node& node) {
  return assignNodeAtField(*this, mixedAirNodeField(), node);
}

bool OutdoorAirMixer_Impl::setOutdoorAirNode(const openstudio::epmodel::Node& node) {
  return assignNodeAtField(*this, outdoorAirNodeField(), node);
}

bool OutdoorAirMixer_Impl::setReliefAirNode(const openstudio::epmodel::Node& node) {
  return assignNodeAtField(*this, reliefAirNodeField(), node);
}

bool OutdoorAirMixer_Impl::setReturnAirNode(const openstudio::epmodel::Node& node) {
  return assignNodeAtField(*this, returnAirNodeField(), node);
}

void OutdoorAirMixer_Impl::doCanonicalize(LoadContext&) {
  // OutdoorAir:Mixer owns the simple node-field reconciliation step: if a
  // persisted node name already exists on one of its ports, materialize or
  // reattach the corresponding transient Node object here. Parent objects own
  // higher-level topology policy such as default naming for missing ports.
  reconcileNamedNodeField(*this, mixedAirNodeField());
  reconcileNamedNodeField(*this, outdoorAirNodeField());
  reconcileNamedNodeField(*this, reliefAirNodeField());
  reconcileNamedNodeField(*this, returnAirNodeField());
}

}  // namespace detail

}  // namespace epmodel
}  // namespace openstudio
