/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "StraightComponent/TemperingValve.hpp"
#include "StraightComponent/TemperingValve_Impl.hpp"

#include "Model.hpp"

#include "StraightComponent/Node.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/idd/IddEnums.hxx>
#include <utilities/idd/TemperingValve_FieldEnums.hxx>

namespace openstudio {
namespace epmodel {

  namespace detail {

    unsigned TemperingValve_Impl::inletPort() const {
      return openstudio::TemperingValveFields::InletNodeName;
    }

    unsigned TemperingValve_Impl::outletPort() const {
      return openstudio::TemperingValveFields::OutletNodeName;
    }

    boost::optional<Node> TemperingValve_Impl::stream2SourceNode() const {
      return getObject<ModelObject>().getModelObjectTarget<Node>(openstudio::TemperingValveFields::Stream2SourceNodeName);
    }

    bool TemperingValve_Impl::setStream2SourceNode(const Node& stream2SourceNode) {
      return setPointer(openstudio::TemperingValveFields::Stream2SourceNodeName, stream2SourceNode.handle());
    }

    void TemperingValve_Impl::resetStream2SourceNode() {
      const bool result = setString(openstudio::TemperingValveFields::Stream2SourceNodeName, "");
      OS_ASSERT(result);
    }

    boost::optional<Node> TemperingValve_Impl::temperatureSetpointNode() const {
      return getObject<ModelObject>().getModelObjectTarget<Node>(openstudio::TemperingValveFields::TemperatureSetpointNodeName);
    }

    bool TemperingValve_Impl::setTemperatureSetpointNode(const Node& temperatureSetpointNode) {
      return setPointer(openstudio::TemperingValveFields::TemperatureSetpointNodeName, temperatureSetpointNode.handle());
    }

    void TemperingValve_Impl::resetTemperatureSetpointNode() {
      const bool result = setString(openstudio::TemperingValveFields::TemperatureSetpointNodeName, "");
      OS_ASSERT(result);
    }

    boost::optional<Node> TemperingValve_Impl::pumpOutletNode() const {
      return getObject<ModelObject>().getModelObjectTarget<Node>(openstudio::TemperingValveFields::PumpOutletNodeName);
    }

    bool TemperingValve_Impl::setPumpOutletNode(const Node& pumpOutletNode) {
      return setPointer(openstudio::TemperingValveFields::PumpOutletNodeName, pumpOutletNode.handle());
    }

    void TemperingValve_Impl::resetPumpOutletNode() {
      const bool result = setString(openstudio::TemperingValveFields::PumpOutletNodeName, "");
      OS_ASSERT(result);
    }

  }  // namespace detail

  TemperingValve::TemperingValve(const Model& model) : StraightComponent(TemperingValve::iddObjectType(), model) {}

  TemperingValve::TemperingValve(std::shared_ptr<detail::TemperingValve_Impl> impl) : StraightComponent(std::move(impl)) {}

  IddObjectType TemperingValve::iddObjectType() {
    return {IddObjectType::TemperingValve};
  }

  boost::optional<Node> TemperingValve::stream2SourceNode() const {
    return getImpl<detail::TemperingValve_Impl>()->stream2SourceNode();
  }

  bool TemperingValve::setStream2SourceNode(const Node& stream2SourceNode) {
    return getImpl<detail::TemperingValve_Impl>()->setStream2SourceNode(stream2SourceNode);
  }

  void TemperingValve::resetStream2SourceNode() {
    getImpl<detail::TemperingValve_Impl>()->resetStream2SourceNode();
  }

  boost::optional<Node> TemperingValve::temperatureSetpointNode() const {
    return getImpl<detail::TemperingValve_Impl>()->temperatureSetpointNode();
  }

  bool TemperingValve::setTemperatureSetpointNode(const Node& temperatureSetpointNode) {
    return getImpl<detail::TemperingValve_Impl>()->setTemperatureSetpointNode(temperatureSetpointNode);
  }

  void TemperingValve::resetTemperatureSetpointNode() {
    getImpl<detail::TemperingValve_Impl>()->resetTemperatureSetpointNode();
  }

  boost::optional<Node> TemperingValve::pumpOutletNode() const {
    return getImpl<detail::TemperingValve_Impl>()->pumpOutletNode();
  }

  bool TemperingValve::setPumpOutletNode(const Node& pumpOutletNode) {
    return getImpl<detail::TemperingValve_Impl>()->setPumpOutletNode(pumpOutletNode);
  }

  void TemperingValve::resetPumpOutletNode() {
    getImpl<detail::TemperingValve_Impl>()->resetPumpOutletNode();
  }

}  // namespace epmodel
}  // namespace openstudio
