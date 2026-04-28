/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "StraightComponent/TemperingValve.hpp"
#include "StraightComponent/TemperingValve_Impl.hpp"

#include "Model.hpp"

#include "Loop/PlantLoop.hpp"
#include "Mixer/Mixer.hpp"
#include "StraightComponent/HeaderedPumpsConstantSpeed.hpp"
#include "StraightComponent/HeaderedPumpsVariableSpeed.hpp"
#include "StraightComponent/Node.hpp"
#include "StraightComponent/PumpConstantSpeed.hpp"
#include "StraightComponent/PumpVariableSpeed.hpp"

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

    bool TemperingValve_Impl::addToNode(Node& node) {
      if (auto plant = node.plantLoop()) {
        if (plant->supplyComponent(node.handle()) && StraightComponent_Impl::addToNode(node)) {
          return setControlNodes();
        }
      }

      return false;
    }

    boost::optional<Node> TemperingValve_Impl::stream2SourceNode() const {
      return getObject<ModelObject>().getModelObjectTarget<Node>(openstudio::TemperingValveFields::Stream2SourceNodeName);
    }

    bool TemperingValve_Impl::setStream2SourceNode(const Node& stream2SourceNode) {
      return setPointer(openstudio::TemperingValveFields::Stream2SourceNodeName, stream2SourceNode.handle());
    }

    void TemperingValve_Impl::resetStream2SourceNode() {
      const bool result = setPointer(openstudio::TemperingValveFields::Stream2SourceNodeName, Handle(), false);
      OS_ASSERT(result);
    }

    boost::optional<Node> TemperingValve_Impl::temperatureSetpointNode() const {
      return getObject<ModelObject>().getModelObjectTarget<Node>(openstudio::TemperingValveFields::TemperatureSetpointNodeName);
    }

    bool TemperingValve_Impl::setTemperatureSetpointNode(const Node& temperatureSetpointNode) {
      return setPointer(openstudio::TemperingValveFields::TemperatureSetpointNodeName, temperatureSetpointNode.handle());
    }

    void TemperingValve_Impl::resetTemperatureSetpointNode() {
      const bool result = setPointer(openstudio::TemperingValveFields::TemperatureSetpointNodeName, Handle(), false);
      OS_ASSERT(result);
    }

    boost::optional<Node> TemperingValve_Impl::pumpOutletNode() const {
      return getObject<ModelObject>().getModelObjectTarget<Node>(openstudio::TemperingValveFields::PumpOutletNodeName);
    }

    bool TemperingValve_Impl::setPumpOutletNode(const Node& pumpOutletNode) {
      return setPointer(openstudio::TemperingValveFields::PumpOutletNodeName, pumpOutletNode.handle());
    }

    void TemperingValve_Impl::resetPumpOutletNode() {
      const bool result = setPointer(openstudio::TemperingValveFields::PumpOutletNodeName, Handle(), false);
      OS_ASSERT(result);
    }

    bool TemperingValve_Impl::setControlNodes() {
      auto plant = plantLoop();
      if (!plant) {
        return false;
      }

      bool ok = true;

      if (!pumpOutletNode()) {
        std::vector<ModelObject> allPumps;

        auto pumps = plant->supplyComponents(openstudio::epmodel::PumpVariableSpeed::iddObjectType());
        allPumps.insert(allPumps.end(), pumps.begin(), pumps.end());
        pumps = plant->supplyComponents(openstudio::epmodel::PumpConstantSpeed::iddObjectType());
        allPumps.insert(allPumps.end(), pumps.begin(), pumps.end());
        pumps = plant->supplyComponents(openstudio::epmodel::HeaderedPumpsConstantSpeed::iddObjectType());
        allPumps.insert(allPumps.end(), pumps.begin(), pumps.end());
        pumps = plant->supplyComponents(openstudio::epmodel::HeaderedPumpsVariableSpeed::iddObjectType());
        allPumps.insert(allPumps.end(), pumps.begin(), pumps.end());

        if (!allPumps.empty()) {
          if (auto mo = allPumps.back().optionalCast<StraightComponent>()) {
            if (auto outlet = mo->outletModelObject()) {
              if (auto node = outlet->optionalCast<Node>()) {
                ok = setPumpOutletNode(*node) && ok;
              }
            }
          }
        }
      }

      if (!temperatureSetpointNode()) {
        ok = setTemperatureSetpointNode(plant->supplyOutletNode()) && ok;
      }

      if (!stream2SourceNode()) {
        auto mixer = plant->supplyMixer();
        const auto thisObject = getObject<TemperingValve>();
        for (const auto& inletObject : mixer.inletModelObjects()) {
          if (auto node = inletObject.optionalCast<Node>()) {
            if (plant->supplyComponents(thisObject, *node).empty()) {
              ok = setStream2SourceNode(*node) && ok;
            }
          }
        }
      }

      return ok;
    }

  }  // namespace detail

  TemperingValve::TemperingValve(const Model& model) : StraightComponent(TemperingValve::iddObjectType(), model) {
    OS_ASSERT(getImpl<detail::TemperingValve_Impl>());
  }

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
