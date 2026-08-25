/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "SetpointManager/SetpointManagerSystemNodeResetTemperature.hpp"
#include "SetpointManager/SetpointManagerSystemNodeResetTemperature_Impl.hpp"

#include "Model.hpp"
#include "StraightComponent/Node.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/core/UUID.hpp>
#include <utilities/idd/IddEnums.hxx>
#include <utilities/idd/IddFactory.hxx>
#include <utilities/idd/SetpointManager_SystemNodeReset_Temperature_FieldEnums.hxx>

namespace openstudio {
namespace epmodel {

  SetpointManagerSystemNodeResetTemperature::SetpointManagerSystemNodeResetTemperature(const Model& model)
    : SetpointManager(SetpointManagerSystemNodeResetTemperature::iddObjectType(), model) {
    auto impl = getImpl<detail::SetpointManagerSystemNodeResetTemperature_Impl>();
    OS_ASSERT(impl);
    OS_ASSERT(setControlVariable("Temperature"));
    OS_ASSERT(setSetpointatLowReferenceTemperature(16.7));
    OS_ASSERT(setSetpointatHighReferenceTemperature(12.8));
    OS_ASSERT(setLowReferenceTemperature(20.0));
    OS_ASSERT(setHighReferenceTemperature(23.3));
    detail::LoadContext context{const_cast<Model&>(model), SanitizationPolicy::Repair, SanitizationReport{}, {}};  // NOLINT
    impl->canonicalize(context);
  }

  SetpointManagerSystemNodeResetTemperature::SetpointManagerSystemNodeResetTemperature(
    std::shared_ptr<detail::SetpointManagerSystemNodeResetTemperature_Impl> impl)
    : SetpointManager(std::move(impl)) {}

  IddObjectType SetpointManagerSystemNodeResetTemperature::iddObjectType() {
    return IddObjectType::SetpointManager_SystemNodeReset_Temperature;
  }

  std::vector<std::string> SetpointManagerSystemNodeResetTemperature::controlVariableValues() {
    return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(),
                          openstudio::SetpointManager_SystemNodeReset_TemperatureFields::ControlVariable);
  }

  double SetpointManagerSystemNodeResetTemperature::setpointatLowReferenceTemperature() const {
    return getImpl<detail::SetpointManagerSystemNodeResetTemperature_Impl>()->setpointatLowReferenceTemperature();
  }

  bool SetpointManagerSystemNodeResetTemperature::setSetpointatLowReferenceTemperature(double setpointatLowReferenceTemperature) {
    const bool result =
      getImpl<detail::SetpointManagerSystemNodeResetTemperature_Impl>()->setSetpointatLowReferenceTemperature(setpointatLowReferenceTemperature);
    OS_ASSERT(result);
    return result;
  }

  double SetpointManagerSystemNodeResetTemperature::setpointatHighReferenceTemperature() const {
    return getImpl<detail::SetpointManagerSystemNodeResetTemperature_Impl>()->setpointatHighReferenceTemperature();
  }

  bool SetpointManagerSystemNodeResetTemperature::setSetpointatHighReferenceTemperature(double setpointatHighReferenceTemperature) {
    const bool result =
      getImpl<detail::SetpointManagerSystemNodeResetTemperature_Impl>()->setSetpointatHighReferenceTemperature(setpointatHighReferenceTemperature);
    OS_ASSERT(result);
    return result;
  }

  double SetpointManagerSystemNodeResetTemperature::lowReferenceTemperature() const {
    return getImpl<detail::SetpointManagerSystemNodeResetTemperature_Impl>()->lowReferenceTemperature();
  }

  bool SetpointManagerSystemNodeResetTemperature::setLowReferenceTemperature(double lowReferenceTemperature) {
    const bool result = getImpl<detail::SetpointManagerSystemNodeResetTemperature_Impl>()->setLowReferenceTemperature(lowReferenceTemperature);
    OS_ASSERT(result);
    return result;
  }

  double SetpointManagerSystemNodeResetTemperature::highReferenceTemperature() const {
    return getImpl<detail::SetpointManagerSystemNodeResetTemperature_Impl>()->highReferenceTemperature();
  }

  bool SetpointManagerSystemNodeResetTemperature::setHighReferenceTemperature(double highReferenceTemperature) {
    const bool result = getImpl<detail::SetpointManagerSystemNodeResetTemperature_Impl>()->setHighReferenceTemperature(highReferenceTemperature);
    OS_ASSERT(result);
    return result;
  }

  boost::optional<Node> SetpointManagerSystemNodeResetTemperature::referenceNode() const {
    return getImpl<detail::SetpointManagerSystemNodeResetTemperature_Impl>()->referenceNode();
  }

  bool SetpointManagerSystemNodeResetTemperature::setReferenceNode(const Node& node) {
    return getImpl<detail::SetpointManagerSystemNodeResetTemperature_Impl>()->setReferenceNode(node);
  }

  void SetpointManagerSystemNodeResetTemperature::resetReferenceNode() {
    getImpl<detail::SetpointManagerSystemNodeResetTemperature_Impl>()->resetReferenceNode();
  }

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
  namespace detail {

    double SetpointManagerSystemNodeResetTemperature_Impl::setpointatLowReferenceTemperature() const {
      const auto value = getDouble(openstudio::SetpointManager_SystemNodeReset_TemperatureFields::SetpointatLowReferenceTemperature, true);
      OS_ASSERT(value);
      return *value;
    }

    bool SetpointManagerSystemNodeResetTemperature_Impl::setSetpointatLowReferenceTemperature(double setpointatLowReferenceTemperature) {
      const bool result = setDouble(openstudio::SetpointManager_SystemNodeReset_TemperatureFields::SetpointatLowReferenceTemperature,
                                    setpointatLowReferenceTemperature);
      OS_ASSERT(result);
      return result;
    }

    double SetpointManagerSystemNodeResetTemperature_Impl::setpointatHighReferenceTemperature() const {
      const auto value = getDouble(openstudio::SetpointManager_SystemNodeReset_TemperatureFields::SetpointatHighReferenceTemperature, true);
      OS_ASSERT(value);
      return *value;
    }

    bool SetpointManagerSystemNodeResetTemperature_Impl::setSetpointatHighReferenceTemperature(double setpointatHighReferenceTemperature) {
      const bool result = setDouble(openstudio::SetpointManager_SystemNodeReset_TemperatureFields::SetpointatHighReferenceTemperature,
                                    setpointatHighReferenceTemperature);
      OS_ASSERT(result);
      return result;
    }

    double SetpointManagerSystemNodeResetTemperature_Impl::lowReferenceTemperature() const {
      const auto value = getDouble(openstudio::SetpointManager_SystemNodeReset_TemperatureFields::LowReferenceTemperature, true);
      OS_ASSERT(value);
      return *value;
    }

    bool SetpointManagerSystemNodeResetTemperature_Impl::setLowReferenceTemperature(double lowReferenceTemperature) {
      const bool result = setDouble(openstudio::SetpointManager_SystemNodeReset_TemperatureFields::LowReferenceTemperature, lowReferenceTemperature);
      OS_ASSERT(result);
      return result;
    }

    double SetpointManagerSystemNodeResetTemperature_Impl::highReferenceTemperature() const {
      const auto value = getDouble(openstudio::SetpointManager_SystemNodeReset_TemperatureFields::HighReferenceTemperature, true);
      OS_ASSERT(value);
      return *value;
    }

    bool SetpointManagerSystemNodeResetTemperature_Impl::setHighReferenceTemperature(double highReferenceTemperature) {
      const bool result =
        setDouble(openstudio::SetpointManager_SystemNodeReset_TemperatureFields::HighReferenceTemperature, highReferenceTemperature);
      OS_ASSERT(result);
      return result;
    }

    boost::optional<openstudio::epmodel::Node> SetpointManagerSystemNodeResetTemperature_Impl::referenceNode() const {
      constexpr auto field = openstudio::SetpointManager_SystemNodeReset_TemperatureFields::ReferenceNodeName;
      const auto managedValue = getObject<ModelObject>().getField(field, false);
      if (!managedValue || managedValue->empty()) {
        return boost::none;
      }
      const auto targetHandle = openstudio::toUUID(*managedValue);
      if (targetHandle.isNull()) {
        return boost::none;
      }
      return model().getModelObject<openstudio::epmodel::Node>(targetHandle);
    }

    bool SetpointManagerSystemNodeResetTemperature_Impl::setReferenceNode(const openstudio::epmodel::Node& node) {
      if (node.model() != model()) {
        return false;
      }
      return getObject<ModelObject>().setPointer(openstudio::SetpointManager_SystemNodeReset_TemperatureFields::ReferenceNodeName, node.handle());
    }

    void SetpointManagerSystemNodeResetTemperature_Impl::resetReferenceNode() {
      constexpr auto field = openstudio::SetpointManager_SystemNodeReset_TemperatureFields::ReferenceNodeName;
      OS_ASSERT(setPointer(field, Handle(), false));
      OS_ASSERT(openstudio::detail::IdfObject_Impl::setString(field, "", false));
    }

    boost::optional<openstudio::epmodel::Node> SetpointManagerSystemNodeResetTemperature_Impl::setpointNode() const {
      return getObject<ModelObject>().getModelObjectTarget<openstudio::epmodel::Node>(
        openstudio::SetpointManager_SystemNodeReset_TemperatureFields::SetpointNodeorNodeListName);
    }

    std::string SetpointManagerSystemNodeResetTemperature_Impl::controlVariable() const {
      if (auto value = getString(openstudio::SetpointManager_SystemNodeReset_TemperatureFields::ControlVariable, true)) {
        return *value;
      }
      return "";
    }

    bool SetpointManagerSystemNodeResetTemperature_Impl::setControlVariable(const std::string& value) {
      return setString(openstudio::SetpointManager_SystemNodeReset_TemperatureFields::ControlVariable, value);
    }

    bool SetpointManagerSystemNodeResetTemperature_Impl::setSetpointNode(const openstudio::epmodel::Node& node) {
      return getObject<ModelObject>().setPointer(openstudio::SetpointManager_SystemNodeReset_TemperatureFields::SetpointNodeorNodeListName,
                                                 node.handle());
    }

    void SetpointManagerSystemNodeResetTemperature_Impl::doCanonicalize(LoadContext& context) {
      SetpointManager_Impl::doCanonicalize(context);
      (void)resolvedNodeTarget(openstudio::SetpointManager_SystemNodeReset_TemperatureFields::ReferenceNodeName);
      canonicalizeSetpointNodeField(context, openstudio::SetpointManager_SystemNodeReset_TemperatureFields::SetpointNodeorNodeListName);

      if (auto value = getString(openstudio::SetpointManager_SystemNodeReset_TemperatureFields::ControlVariable, true)) {
        if (!value->empty()) {
          // continue
        } else {
          OS_ASSERT(setString(openstudio::SetpointManager_SystemNodeReset_TemperatureFields::ControlVariable, "Temperature"));
          detail::addLoadInfo(context, "Set default Control Variable to 'Temperature' for SetpointManager:SystemNodeReset:Temperature '"
                                         + getObject<ModelObject>().nameString() + "'.");
        }
      } else {
        OS_ASSERT(setString(openstudio::SetpointManager_SystemNodeReset_TemperatureFields::ControlVariable, "Temperature"));
        detail::addLoadInfo(context, "Set default Control Variable to 'Temperature' for SetpointManager:SystemNodeReset:Temperature '"
                                       + getObject<ModelObject>().nameString() + "'.");
      }

      if (auto value = getDouble(openstudio::SetpointManager_SystemNodeReset_TemperatureFields::SetpointatLowReferenceTemperature, true)) {
        (void)value;
      } else {
        OS_ASSERT(setDouble(openstudio::SetpointManager_SystemNodeReset_TemperatureFields::SetpointatLowReferenceTemperature, 16.7));
        detail::addLoadInfo(context, "Set default Setpoint at Low Reference Temperature to 16.7 for SetpointManager:SystemNodeReset:Temperature '"
                                       + getObject<ModelObject>().nameString() + "'.");
      }

      if (auto value = getDouble(openstudio::SetpointManager_SystemNodeReset_TemperatureFields::SetpointatHighReferenceTemperature, true)) {
        (void)value;
      } else {
        OS_ASSERT(setDouble(openstudio::SetpointManager_SystemNodeReset_TemperatureFields::SetpointatHighReferenceTemperature, 12.8));
        detail::addLoadInfo(context, "Set default Setpoint at High Reference Temperature to 12.8 for SetpointManager:SystemNodeReset:Temperature '"
                                       + getObject<ModelObject>().nameString() + "'.");
      }

      if (auto value = getDouble(openstudio::SetpointManager_SystemNodeReset_TemperatureFields::LowReferenceTemperature, true)) {
        (void)value;
      } else {
        OS_ASSERT(setDouble(openstudio::SetpointManager_SystemNodeReset_TemperatureFields::LowReferenceTemperature, 20.0));
        detail::addLoadInfo(context, "Set default Low Reference Temperature to 20.0 for SetpointManager:SystemNodeReset:Temperature '"
                                       + getObject<ModelObject>().nameString() + "'.");
      }

      if (auto value = getDouble(openstudio::SetpointManager_SystemNodeReset_TemperatureFields::HighReferenceTemperature, true)) {
        (void)value;
      } else {
        OS_ASSERT(setDouble(openstudio::SetpointManager_SystemNodeReset_TemperatureFields::HighReferenceTemperature, 23.3));
        detail::addLoadInfo(context, "Set default High Reference Temperature to 23.3 for SetpointManager:SystemNodeReset:Temperature '"
                                       + getObject<ModelObject>().nameString() + "'.");
      }
    }

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
