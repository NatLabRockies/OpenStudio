/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "SetpointManager/SetpointManagerOutdoorAirPretreat.hpp"
#include "SetpointManager/SetpointManagerOutdoorAirPretreat_Impl.hpp"

#include "Model.hpp"
#include "StraightComponent/Node.hpp"
#include "StraightComponent/Node_Impl.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/idd/IddEnums.hxx>
#include <utilities/idd/IddFactory.hxx>
#include <utilities/idd/SetpointManager_OutdoorAirPretreat_FieldEnums.hxx>

namespace openstudio {
namespace epmodel {

  SetpointManagerOutdoorAirPretreat::SetpointManagerOutdoorAirPretreat(const Model& model)
    : SetpointManager(SetpointManagerOutdoorAirPretreat::iddObjectType(), model) {
    auto impl = getImpl<detail::SetpointManagerOutdoorAirPretreat_Impl>();
    OS_ASSERT(impl);
    OS_ASSERT(setControlVariable("Temperature"));
    detail::LoadContext context{const_cast<Model&>(model), SanitizationPolicy::Repair, SanitizationReport{}, {}};  // NOLINT
    impl->canonicalize(context);
  }

  SetpointManagerOutdoorAirPretreat::SetpointManagerOutdoorAirPretreat(std::shared_ptr<detail::SetpointManagerOutdoorAirPretreat_Impl> impl)
    : SetpointManager(std::move(impl)) {}

  IddObjectType SetpointManagerOutdoorAirPretreat::iddObjectType() {
    return IddObjectType::SetpointManager_OutdoorAirPretreat;
  }

  std::vector<std::string> SetpointManagerOutdoorAirPretreat::controlVariableValues() {
    return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(),
                          openstudio::SetpointManager_OutdoorAirPretreatFields::ControlVariable);
  }

  double SetpointManagerOutdoorAirPretreat::minimumSetpointTemperature() const {
    return getImpl<detail::SetpointManagerOutdoorAirPretreat_Impl>()->minimumSetpointTemperature();
  }

  bool SetpointManagerOutdoorAirPretreat::isMinimumSetpointTemperatureDefaulted() const {
    return getImpl<detail::SetpointManagerOutdoorAirPretreat_Impl>()->isMinimumSetpointTemperatureDefaulted();
  }

  bool SetpointManagerOutdoorAirPretreat::setMinimumSetpointTemperature(double minimumSetpointTemperature) {
    const bool result = getImpl<detail::SetpointManagerOutdoorAirPretreat_Impl>()->setMinimumSetpointTemperature(minimumSetpointTemperature);
    OS_ASSERT(result);
    return result;
  }

  void SetpointManagerOutdoorAirPretreat::resetMinimumSetpointTemperature() {
    getImpl<detail::SetpointManagerOutdoorAirPretreat_Impl>()->resetMinimumSetpointTemperature();
  }

  double SetpointManagerOutdoorAirPretreat::maximumSetpointTemperature() const {
    return getImpl<detail::SetpointManagerOutdoorAirPretreat_Impl>()->maximumSetpointTemperature();
  }

  bool SetpointManagerOutdoorAirPretreat::isMaximumSetpointTemperatureDefaulted() const {
    return getImpl<detail::SetpointManagerOutdoorAirPretreat_Impl>()->isMaximumSetpointTemperatureDefaulted();
  }

  bool SetpointManagerOutdoorAirPretreat::setMaximumSetpointTemperature(double maximumSetpointTemperature) {
    const bool result = getImpl<detail::SetpointManagerOutdoorAirPretreat_Impl>()->setMaximumSetpointTemperature(maximumSetpointTemperature);
    OS_ASSERT(result);
    return result;
  }

  void SetpointManagerOutdoorAirPretreat::resetMaximumSetpointTemperature() {
    getImpl<detail::SetpointManagerOutdoorAirPretreat_Impl>()->resetMaximumSetpointTemperature();
  }

  double SetpointManagerOutdoorAirPretreat::minimumSetpointHumidityRatio() const {
    return getImpl<detail::SetpointManagerOutdoorAirPretreat_Impl>()->minimumSetpointHumidityRatio();
  }

  bool SetpointManagerOutdoorAirPretreat::isMinimumSetpointHumidityRatioDefaulted() const {
    return getImpl<detail::SetpointManagerOutdoorAirPretreat_Impl>()->isMinimumSetpointHumidityRatioDefaulted();
  }

  bool SetpointManagerOutdoorAirPretreat::setMinimumSetpointHumidityRatio(double minimumSetpointHumidityRatio) {
    const bool result = getImpl<detail::SetpointManagerOutdoorAirPretreat_Impl>()->setMinimumSetpointHumidityRatio(minimumSetpointHumidityRatio);
    OS_ASSERT(result);
    return result;
  }

  void SetpointManagerOutdoorAirPretreat::resetMinimumSetpointHumidityRatio() {
    getImpl<detail::SetpointManagerOutdoorAirPretreat_Impl>()->resetMinimumSetpointHumidityRatio();
  }

  double SetpointManagerOutdoorAirPretreat::maximumSetpointHumidityRatio() const {
    return getImpl<detail::SetpointManagerOutdoorAirPretreat_Impl>()->maximumSetpointHumidityRatio();
  }

  bool SetpointManagerOutdoorAirPretreat::isMaximumSetpointHumidityRatioDefaulted() const {
    return getImpl<detail::SetpointManagerOutdoorAirPretreat_Impl>()->isMaximumSetpointHumidityRatioDefaulted();
  }

  bool SetpointManagerOutdoorAirPretreat::setMaximumSetpointHumidityRatio(double maximumSetpointHumidityRatio) {
    const bool result = getImpl<detail::SetpointManagerOutdoorAirPretreat_Impl>()->setMaximumSetpointHumidityRatio(maximumSetpointHumidityRatio);
    OS_ASSERT(result);
    return result;
  }

  void SetpointManagerOutdoorAirPretreat::resetMaximumSetpointHumidityRatio() {
    getImpl<detail::SetpointManagerOutdoorAirPretreat_Impl>()->resetMaximumSetpointHumidityRatio();
  }

  boost::optional<Node> SetpointManagerOutdoorAirPretreat::referenceSetpointNode() const {
    return getImpl<detail::SetpointManagerOutdoorAirPretreat_Impl>()->referenceSetpointNode();
  }

  bool SetpointManagerOutdoorAirPretreat::setReferenceSetpointNode(const Node& node) {
    return getImpl<detail::SetpointManagerOutdoorAirPretreat_Impl>()->setReferenceSetpointNode(node);
  }

  void SetpointManagerOutdoorAirPretreat::resetReferenceSetpointNode() {
    getImpl<detail::SetpointManagerOutdoorAirPretreat_Impl>()->resetReferenceSetpointNode();
  }

  boost::optional<Node> SetpointManagerOutdoorAirPretreat::mixedAirStreamNode() const {
    return getImpl<detail::SetpointManagerOutdoorAirPretreat_Impl>()->mixedAirStreamNode();
  }

  bool SetpointManagerOutdoorAirPretreat::setMixedAirStreamNode(const Node& node) {
    return getImpl<detail::SetpointManagerOutdoorAirPretreat_Impl>()->setMixedAirStreamNode(node);
  }

  void SetpointManagerOutdoorAirPretreat::resetMixedAirStreamNode() {
    getImpl<detail::SetpointManagerOutdoorAirPretreat_Impl>()->resetMixedAirStreamNode();
  }

  boost::optional<Node> SetpointManagerOutdoorAirPretreat::outdoorAirStreamNode() const {
    return getImpl<detail::SetpointManagerOutdoorAirPretreat_Impl>()->outdoorAirStreamNode();
  }

  bool SetpointManagerOutdoorAirPretreat::setOutdoorAirStreamNode(const Node& node) {
    return getImpl<detail::SetpointManagerOutdoorAirPretreat_Impl>()->setOutdoorAirStreamNode(node);
  }

  void SetpointManagerOutdoorAirPretreat::resetOutdoorAirStreamNode() {
    getImpl<detail::SetpointManagerOutdoorAirPretreat_Impl>()->resetOutdoorAirStreamNode();
  }

  boost::optional<Node> SetpointManagerOutdoorAirPretreat::returnAirStreamNode() const {
    return getImpl<detail::SetpointManagerOutdoorAirPretreat_Impl>()->returnAirStreamNode();
  }

  bool SetpointManagerOutdoorAirPretreat::setReturnAirStreamNode(const Node& node) {
    return getImpl<detail::SetpointManagerOutdoorAirPretreat_Impl>()->setReturnAirStreamNode(node);
  }

  void SetpointManagerOutdoorAirPretreat::resetReturnAirStreamNode() {
    getImpl<detail::SetpointManagerOutdoorAirPretreat_Impl>()->resetReturnAirStreamNode();
  }

  void SetpointManagerOutdoorAirPretreat::resetControlVariable() {
    getImpl<detail::SetpointManagerOutdoorAirPretreat_Impl>()->resetControlVariable();
  }

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
  namespace detail {

    double SetpointManagerOutdoorAirPretreat_Impl::minimumSetpointTemperature() const {
      const auto value = getDouble(openstudio::SetpointManager_OutdoorAirPretreatFields::MinimumSetpointTemperature, true);
      OS_ASSERT(value);
      return *value;
    }

    bool SetpointManagerOutdoorAirPretreat_Impl::isMinimumSetpointTemperatureDefaulted() const {
      return isEmpty(openstudio::SetpointManager_OutdoorAirPretreatFields::MinimumSetpointTemperature);
    }

    bool SetpointManagerOutdoorAirPretreat_Impl::setMinimumSetpointTemperature(double minimumSetpointTemperature) {
      const bool result = setDouble(openstudio::SetpointManager_OutdoorAirPretreatFields::MinimumSetpointTemperature, minimumSetpointTemperature);
      OS_ASSERT(result);
      return result;
    }

    void SetpointManagerOutdoorAirPretreat_Impl::resetMinimumSetpointTemperature() {
      OS_ASSERT(setString(openstudio::SetpointManager_OutdoorAirPretreatFields::MinimumSetpointTemperature, ""));
    }

    double SetpointManagerOutdoorAirPretreat_Impl::maximumSetpointTemperature() const {
      const auto value = getDouble(openstudio::SetpointManager_OutdoorAirPretreatFields::MaximumSetpointTemperature, true);
      OS_ASSERT(value);
      return *value;
    }

    bool SetpointManagerOutdoorAirPretreat_Impl::isMaximumSetpointTemperatureDefaulted() const {
      return isEmpty(openstudio::SetpointManager_OutdoorAirPretreatFields::MaximumSetpointTemperature);
    }

    bool SetpointManagerOutdoorAirPretreat_Impl::setMaximumSetpointTemperature(double maximumSetpointTemperature) {
      const bool result = setDouble(openstudio::SetpointManager_OutdoorAirPretreatFields::MaximumSetpointTemperature, maximumSetpointTemperature);
      OS_ASSERT(result);
      return result;
    }

    void SetpointManagerOutdoorAirPretreat_Impl::resetMaximumSetpointTemperature() {
      OS_ASSERT(setString(openstudio::SetpointManager_OutdoorAirPretreatFields::MaximumSetpointTemperature, ""));
    }

    double SetpointManagerOutdoorAirPretreat_Impl::minimumSetpointHumidityRatio() const {
      const auto value = getDouble(openstudio::SetpointManager_OutdoorAirPretreatFields::MinimumSetpointHumidityRatio, true);
      OS_ASSERT(value);
      return *value;
    }

    bool SetpointManagerOutdoorAirPretreat_Impl::isMinimumSetpointHumidityRatioDefaulted() const {
      return isEmpty(openstudio::SetpointManager_OutdoorAirPretreatFields::MinimumSetpointHumidityRatio);
    }

    bool SetpointManagerOutdoorAirPretreat_Impl::setMinimumSetpointHumidityRatio(double minimumSetpointHumidityRatio) {
      const bool result = setDouble(openstudio::SetpointManager_OutdoorAirPretreatFields::MinimumSetpointHumidityRatio, minimumSetpointHumidityRatio);
      OS_ASSERT(result);
      return result;
    }

    void SetpointManagerOutdoorAirPretreat_Impl::resetMinimumSetpointHumidityRatio() {
      OS_ASSERT(setString(openstudio::SetpointManager_OutdoorAirPretreatFields::MinimumSetpointHumidityRatio, ""));
    }

    double SetpointManagerOutdoorAirPretreat_Impl::maximumSetpointHumidityRatio() const {
      const auto value = getDouble(openstudio::SetpointManager_OutdoorAirPretreatFields::MaximumSetpointHumidityRatio, true);
      OS_ASSERT(value);
      return *value;
    }

    bool SetpointManagerOutdoorAirPretreat_Impl::isMaximumSetpointHumidityRatioDefaulted() const {
      return isEmpty(openstudio::SetpointManager_OutdoorAirPretreatFields::MaximumSetpointHumidityRatio);
    }

    bool SetpointManagerOutdoorAirPretreat_Impl::setMaximumSetpointHumidityRatio(double maximumSetpointHumidityRatio) {
      const bool result = setDouble(openstudio::SetpointManager_OutdoorAirPretreatFields::MaximumSetpointHumidityRatio, maximumSetpointHumidityRatio);
      OS_ASSERT(result);
      return result;
    }

    void SetpointManagerOutdoorAirPretreat_Impl::resetMaximumSetpointHumidityRatio() {
      OS_ASSERT(setString(openstudio::SetpointManager_OutdoorAirPretreatFields::MaximumSetpointHumidityRatio, ""));
    }

    boost::optional<openstudio::epmodel::Node> SetpointManagerOutdoorAirPretreat_Impl::referenceSetpointNode() const {
      return resolvedNodeTarget(openstudio::SetpointManager_OutdoorAirPretreatFields::ReferenceSetpointNodeName);
    }

    bool SetpointManagerOutdoorAirPretreat_Impl::setReferenceSetpointNode(const openstudio::epmodel::Node& node) {
      return setPointer(openstudio::SetpointManager_OutdoorAirPretreatFields::ReferenceSetpointNodeName, node.handle(), false);
    }

    void SetpointManagerOutdoorAirPretreat_Impl::resetReferenceSetpointNode() {
      OS_ASSERT(setPointer(openstudio::SetpointManager_OutdoorAirPretreatFields::ReferenceSetpointNodeName, Handle(), false));
    }

    boost::optional<openstudio::epmodel::Node> SetpointManagerOutdoorAirPretreat_Impl::mixedAirStreamNode() const {
      return resolvedNodeTarget(openstudio::SetpointManager_OutdoorAirPretreatFields::MixedAirStreamNodeName);
    }

    bool SetpointManagerOutdoorAirPretreat_Impl::setMixedAirStreamNode(const openstudio::epmodel::Node& node) {
      return setPointer(openstudio::SetpointManager_OutdoorAirPretreatFields::MixedAirStreamNodeName, node.handle(), false);
    }

    void SetpointManagerOutdoorAirPretreat_Impl::resetMixedAirStreamNode() {
      OS_ASSERT(setPointer(openstudio::SetpointManager_OutdoorAirPretreatFields::MixedAirStreamNodeName, Handle(), false));
    }

    boost::optional<openstudio::epmodel::Node> SetpointManagerOutdoorAirPretreat_Impl::outdoorAirStreamNode() const {
      return resolvedNodeTarget(openstudio::SetpointManager_OutdoorAirPretreatFields::OutdoorAirStreamNodeName);
    }

    bool SetpointManagerOutdoorAirPretreat_Impl::setOutdoorAirStreamNode(const openstudio::epmodel::Node& node) {
      return setPointer(openstudio::SetpointManager_OutdoorAirPretreatFields::OutdoorAirStreamNodeName, node.handle(), false);
    }

    void SetpointManagerOutdoorAirPretreat_Impl::resetOutdoorAirStreamNode() {
      OS_ASSERT(setPointer(openstudio::SetpointManager_OutdoorAirPretreatFields::OutdoorAirStreamNodeName, Handle(), false));
    }

    boost::optional<openstudio::epmodel::Node> SetpointManagerOutdoorAirPretreat_Impl::returnAirStreamNode() const {
      return resolvedNodeTarget(openstudio::SetpointManager_OutdoorAirPretreatFields::ReturnAirStreamNodeName);
    }

    bool SetpointManagerOutdoorAirPretreat_Impl::setReturnAirStreamNode(const openstudio::epmodel::Node& node) {
      return setPointer(openstudio::SetpointManager_OutdoorAirPretreatFields::ReturnAirStreamNodeName, node.handle(), false);
    }

    void SetpointManagerOutdoorAirPretreat_Impl::resetReturnAirStreamNode() {
      OS_ASSERT(setPointer(openstudio::SetpointManager_OutdoorAirPretreatFields::ReturnAirStreamNodeName, Handle(), false));
    }

    void SetpointManagerOutdoorAirPretreat_Impl::resetControlVariable() {
      OS_ASSERT(setString(openstudio::SetpointManager_OutdoorAirPretreatFields::ControlVariable, "Temperature"));
    }

    boost::optional<openstudio::epmodel::Node> SetpointManagerOutdoorAirPretreat_Impl::setpointNode() const {
      return getObject<ModelObject>().getModelObjectTarget<openstudio::epmodel::Node>(
        openstudio::SetpointManager_OutdoorAirPretreatFields::SetpointNodeorNodeListName);
    }

    std::string SetpointManagerOutdoorAirPretreat_Impl::controlVariable() const {
      if (auto value = getString(openstudio::SetpointManager_OutdoorAirPretreatFields::ControlVariable, true)) {
        return *value;
      }
      return "";
    }

    bool SetpointManagerOutdoorAirPretreat_Impl::setControlVariable(const std::string& value) {
      return setString(openstudio::SetpointManager_OutdoorAirPretreatFields::ControlVariable, value);
    }

    bool SetpointManagerOutdoorAirPretreat_Impl::setSetpointNode(const openstudio::epmodel::Node& node) {
      return getObject<ModelObject>().setPointer(openstudio::SetpointManager_OutdoorAirPretreatFields::SetpointNodeorNodeListName, node.handle());
    }

    void SetpointManagerOutdoorAirPretreat_Impl::doCanonicalize(LoadContext& context) {
      SetpointManager_Impl::doCanonicalize(context);
      canonicalizeSetpointNodeField(context, openstudio::SetpointManager_OutdoorAirPretreatFields::ReferenceSetpointNodeName);
      canonicalizeSetpointNodeField(context, openstudio::SetpointManager_OutdoorAirPretreatFields::MixedAirStreamNodeName);
      canonicalizeSetpointNodeField(context, openstudio::SetpointManager_OutdoorAirPretreatFields::OutdoorAirStreamNodeName);
      canonicalizeSetpointNodeField(context, openstudio::SetpointManager_OutdoorAirPretreatFields::ReturnAirStreamNodeName);
      canonicalizeSetpointNodeField(context, openstudio::SetpointManager_OutdoorAirPretreatFields::SetpointNodeorNodeListName);

      if (auto value = getString(openstudio::SetpointManager_OutdoorAirPretreatFields::ControlVariable, true)) {
        if (!value->empty()) {
          return;
        }
      }

      OS_ASSERT(setString(openstudio::SetpointManager_OutdoorAirPretreatFields::ControlVariable, "Temperature"));
      detail::addLoadInfo(context, "Set default Control Variable to 'Temperature' for SetpointManager:OutdoorAirPretreat '"
                                     + getObject<ModelObject>().nameString() + "'.");
    }

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
