/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "SetpointManager/SetpointManagerFollowSystemNodeTemperature.hpp"
#include "SetpointManager/SetpointManagerFollowSystemNodeTemperature_Impl.hpp"

#include "Model.hpp"
#include "StraightComponent/Node.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/core/UUID.hpp>
#include <utilities/idd/IddEnums.hxx>
#include <utilities/idd/IddFactory.hxx>
#include <utilities/idd/SetpointManager_FollowSystemNodeTemperature_FieldEnums.hxx>

namespace openstudio {
namespace epmodel {

  SetpointManagerFollowSystemNodeTemperature::SetpointManagerFollowSystemNodeTemperature(const Model& model)
    : SetpointManager(SetpointManagerFollowSystemNodeTemperature::iddObjectType(), model) {
    auto impl = getImpl<detail::SetpointManagerFollowSystemNodeTemperature_Impl>();
    OS_ASSERT(impl);
    OS_ASSERT(setControlVariable("Temperature"));
    OS_ASSERT(setReferenceTemperatureType("NodeDryBulb"));
    OS_ASSERT(setOffsetTemperatureDifference(0.0));
    OS_ASSERT(setMaximumLimitSetpointTemperature(100.0));
    OS_ASSERT(setMinimumLimitSetpointTemperature(0.0));
    detail::LoadContext context{const_cast<Model&>(model), SanitizationPolicy::Repair, SanitizationReport{}, {}};  // NOLINT
    impl->canonicalize(context);
  }

  SetpointManagerFollowSystemNodeTemperature::SetpointManagerFollowSystemNodeTemperature(
    std::shared_ptr<detail::SetpointManagerFollowSystemNodeTemperature_Impl> impl)
    : SetpointManager(std::move(impl)) {}

  IddObjectType SetpointManagerFollowSystemNodeTemperature::iddObjectType() {
    return IddObjectType::SetpointManager_FollowSystemNodeTemperature;
  }

  std::vector<std::string> SetpointManagerFollowSystemNodeTemperature::controlVariableValues() {
    return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(),
                          openstudio::SetpointManager_FollowSystemNodeTemperatureFields::ControlVariable);
  }

  std::vector<std::string> SetpointManagerFollowSystemNodeTemperature::referenceTemperatureTypeValues() {
    return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(),
                          openstudio::SetpointManager_FollowSystemNodeTemperatureFields::ReferenceTemperatureType);
  }

  boost::optional<Node> SetpointManagerFollowSystemNodeTemperature::referenceNode() const {
    return getImpl<detail::SetpointManagerFollowSystemNodeTemperature_Impl>()->referenceNode();
  }

  bool SetpointManagerFollowSystemNodeTemperature::setReferenceNode(const Node& node) {
    return getImpl<detail::SetpointManagerFollowSystemNodeTemperature_Impl>()->setReferenceNode(node);
  }

  void SetpointManagerFollowSystemNodeTemperature::resetReferenceNode() {
    getImpl<detail::SetpointManagerFollowSystemNodeTemperature_Impl>()->resetReferenceNode();
  }

  std::string SetpointManagerFollowSystemNodeTemperature::referenceTemperatureType() const {
    return getImpl<detail::SetpointManagerFollowSystemNodeTemperature_Impl>()->referenceTemperatureType();
  }

  bool SetpointManagerFollowSystemNodeTemperature::setReferenceTemperatureType(const std::string& referenceTemperatureType) {
    return getImpl<detail::SetpointManagerFollowSystemNodeTemperature_Impl>()->setReferenceTemperatureType(referenceTemperatureType);
  }

  double SetpointManagerFollowSystemNodeTemperature::offsetTemperatureDifference() const {
    return getImpl<detail::SetpointManagerFollowSystemNodeTemperature_Impl>()->offsetTemperatureDifference();
  }

  bool SetpointManagerFollowSystemNodeTemperature::setOffsetTemperatureDifference(double offsetTemperatureDifference) {
    const bool result =
      getImpl<detail::SetpointManagerFollowSystemNodeTemperature_Impl>()->setOffsetTemperatureDifference(offsetTemperatureDifference);
    OS_ASSERT(result);
    return result;
  }

  double SetpointManagerFollowSystemNodeTemperature::maximumLimitSetpointTemperature() const {
    return getImpl<detail::SetpointManagerFollowSystemNodeTemperature_Impl>()->maximumLimitSetpointTemperature();
  }

  bool SetpointManagerFollowSystemNodeTemperature::setMaximumLimitSetpointTemperature(double maximumLimitSetpointTemperature) {
    const bool result =
      getImpl<detail::SetpointManagerFollowSystemNodeTemperature_Impl>()->setMaximumLimitSetpointTemperature(maximumLimitSetpointTemperature);
    OS_ASSERT(result);
    return result;
  }

  double SetpointManagerFollowSystemNodeTemperature::minimumLimitSetpointTemperature() const {
    return getImpl<detail::SetpointManagerFollowSystemNodeTemperature_Impl>()->minimumLimitSetpointTemperature();
  }

  bool SetpointManagerFollowSystemNodeTemperature::setMinimumLimitSetpointTemperature(double minimumLimitSetpointTemperature) {
    const bool result =
      getImpl<detail::SetpointManagerFollowSystemNodeTemperature_Impl>()->setMinimumLimitSetpointTemperature(minimumLimitSetpointTemperature);
    OS_ASSERT(result);
    return result;
  }

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
  namespace detail {

    std::string SetpointManagerFollowSystemNodeTemperature_Impl::referenceTemperatureType() const {
      const auto value = getString(openstudio::SetpointManager_FollowSystemNodeTemperatureFields::ReferenceTemperatureType, true);
      OS_ASSERT(value);
      return *value;
    }

    bool SetpointManagerFollowSystemNodeTemperature_Impl::setReferenceTemperatureType(const std::string& referenceTemperatureType) {
      return setString(openstudio::SetpointManager_FollowSystemNodeTemperatureFields::ReferenceTemperatureType, referenceTemperatureType);
    }

    double SetpointManagerFollowSystemNodeTemperature_Impl::offsetTemperatureDifference() const {
      const auto value = getDouble(openstudio::SetpointManager_FollowSystemNodeTemperatureFields::OffsetTemperatureDifference, true);
      OS_ASSERT(value);
      return *value;
    }

    bool SetpointManagerFollowSystemNodeTemperature_Impl::setOffsetTemperatureDifference(double offsetTemperatureDifference) {
      const bool result =
        setDouble(openstudio::SetpointManager_FollowSystemNodeTemperatureFields::OffsetTemperatureDifference, offsetTemperatureDifference);
      OS_ASSERT(result);
      return result;
    }

    double SetpointManagerFollowSystemNodeTemperature_Impl::maximumLimitSetpointTemperature() const {
      const auto value = getDouble(openstudio::SetpointManager_FollowSystemNodeTemperatureFields::MaximumLimitSetpointTemperature, true);
      OS_ASSERT(value);
      return *value;
    }

    bool SetpointManagerFollowSystemNodeTemperature_Impl::setMaximumLimitSetpointTemperature(double maximumLimitSetpointTemperature) {
      const bool result =
        setDouble(openstudio::SetpointManager_FollowSystemNodeTemperatureFields::MaximumLimitSetpointTemperature, maximumLimitSetpointTemperature);
      OS_ASSERT(result);
      return result;
    }

    double SetpointManagerFollowSystemNodeTemperature_Impl::minimumLimitSetpointTemperature() const {
      const auto value = getDouble(openstudio::SetpointManager_FollowSystemNodeTemperatureFields::MinimumLimitSetpointTemperature, true);
      OS_ASSERT(value);
      return *value;
    }

    bool SetpointManagerFollowSystemNodeTemperature_Impl::setMinimumLimitSetpointTemperature(double minimumLimitSetpointTemperature) {
      const bool result =
        setDouble(openstudio::SetpointManager_FollowSystemNodeTemperatureFields::MinimumLimitSetpointTemperature, minimumLimitSetpointTemperature);
      OS_ASSERT(result);
      return result;
    }

    boost::optional<openstudio::epmodel::Node> SetpointManagerFollowSystemNodeTemperature_Impl::referenceNode() const {
      constexpr auto field = openstudio::SetpointManager_FollowSystemNodeTemperatureFields::ReferenceNodeName;
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

    bool SetpointManagerFollowSystemNodeTemperature_Impl::setReferenceNode(const openstudio::epmodel::Node& node) {
      if (node.model() != model()) {
        return false;
      }
      return getObject<ModelObject>().setPointer(openstudio::SetpointManager_FollowSystemNodeTemperatureFields::ReferenceNodeName, node.handle());
    }

    void SetpointManagerFollowSystemNodeTemperature_Impl::resetReferenceNode() {
      constexpr auto field = openstudio::SetpointManager_FollowSystemNodeTemperatureFields::ReferenceNodeName;
      OS_ASSERT(setPointer(field, Handle(), false));
      OS_ASSERT(openstudio::detail::IdfObject_Impl::setString(field, "", false));
    }

    bool SetpointManagerFollowSystemNodeTemperature_Impl::isAllowedOnPlantLoop() const {
      return true;
    }

    boost::optional<openstudio::epmodel::Node> SetpointManagerFollowSystemNodeTemperature_Impl::setpointNode() const {
      return getObject<ModelObject>().getModelObjectTarget<openstudio::epmodel::Node>(
        openstudio::SetpointManager_FollowSystemNodeTemperatureFields::SetpointNodeorNodeListName);
    }

    std::string SetpointManagerFollowSystemNodeTemperature_Impl::controlVariable() const {
      if (auto value = getString(openstudio::SetpointManager_FollowSystemNodeTemperatureFields::ControlVariable, true)) {
        return *value;
      }
      return "";
    }

    bool SetpointManagerFollowSystemNodeTemperature_Impl::setControlVariable(const std::string& value) {
      return setString(openstudio::SetpointManager_FollowSystemNodeTemperatureFields::ControlVariable, value);
    }

    bool SetpointManagerFollowSystemNodeTemperature_Impl::setSetpointNode(const openstudio::epmodel::Node& node) {
      return getObject<ModelObject>().setPointer(openstudio::SetpointManager_FollowSystemNodeTemperatureFields::SetpointNodeorNodeListName,
                                                 node.handle());
    }

    void SetpointManagerFollowSystemNodeTemperature_Impl::doCanonicalize(LoadContext& context) {
      SetpointManager_Impl::doCanonicalize(context);
      (void)resolvedNodeTarget(openstudio::SetpointManager_FollowSystemNodeTemperatureFields::ReferenceNodeName);
      canonicalizeSetpointNodeField(context, openstudio::SetpointManager_FollowSystemNodeTemperatureFields::SetpointNodeorNodeListName);

      if (auto value = getString(openstudio::SetpointManager_FollowSystemNodeTemperatureFields::ControlVariable, true)) {
        if (!value->empty()) {
          // continue
        } else {
          OS_ASSERT(setString(openstudio::SetpointManager_FollowSystemNodeTemperatureFields::ControlVariable, "Temperature"));
          detail::addLoadInfo(context, "Set default Control Variable to 'Temperature' for SetpointManager:FollowSystemNodeTemperature '"
                                         + getObject<ModelObject>().nameString() + "'.");
        }
      } else {
        OS_ASSERT(setString(openstudio::SetpointManager_FollowSystemNodeTemperatureFields::ControlVariable, "Temperature"));
        detail::addLoadInfo(context, "Set default Control Variable to 'Temperature' for SetpointManager:FollowSystemNodeTemperature '"
                                       + getObject<ModelObject>().nameString() + "'.");
      }

      if (auto value = getString(openstudio::SetpointManager_FollowSystemNodeTemperatureFields::ReferenceTemperatureType, true)) {
        if (!value->empty()) {
          // continue
        } else {
          OS_ASSERT(setString(openstudio::SetpointManager_FollowSystemNodeTemperatureFields::ReferenceTemperatureType, "NodeDryBulb"));
          detail::addLoadInfo(context, "Set default Reference Temperature Type to 'NodeDryBulb' for "
                                       "SetpointManager:FollowSystemNodeTemperature '"
                                         + getObject<ModelObject>().nameString() + "'.");
        }
      } else {
        OS_ASSERT(setString(openstudio::SetpointManager_FollowSystemNodeTemperatureFields::ReferenceTemperatureType, "NodeDryBulb"));
        detail::addLoadInfo(context, "Set default Reference Temperature Type to 'NodeDryBulb' for "
                                     "SetpointManager:FollowSystemNodeTemperature '"
                                       + getObject<ModelObject>().nameString() + "'.");
      }

      if (auto value = getDouble(openstudio::SetpointManager_FollowSystemNodeTemperatureFields::OffsetTemperatureDifference, true)) {
        (void)value;
      } else {
        OS_ASSERT(setDouble(openstudio::SetpointManager_FollowSystemNodeTemperatureFields::OffsetTemperatureDifference, 0.0));
        detail::addLoadInfo(context, "Set default Offset Temperature Difference to 0 for SetpointManager:FollowSystemNodeTemperature '"
                                       + getObject<ModelObject>().nameString() + "'.");
      }

      if (auto value = getDouble(openstudio::SetpointManager_FollowSystemNodeTemperatureFields::MaximumLimitSetpointTemperature, true)) {
        (void)value;
      } else {
        OS_ASSERT(setDouble(openstudio::SetpointManager_FollowSystemNodeTemperatureFields::MaximumLimitSetpointTemperature, 100.0));
        detail::addLoadInfo(context, "Set default Maximum Limit Setpoint Temperature to 100 for SetpointManager:FollowSystemNodeTemperature '"
                                       + getObject<ModelObject>().nameString() + "'.");
      }

      if (auto value = getDouble(openstudio::SetpointManager_FollowSystemNodeTemperatureFields::MinimumLimitSetpointTemperature, true)) {
        (void)value;
      } else {
        OS_ASSERT(setDouble(openstudio::SetpointManager_FollowSystemNodeTemperatureFields::MinimumLimitSetpointTemperature, 0.0));
        detail::addLoadInfo(context, "Set default Minimum Limit Setpoint Temperature to 0 for SetpointManager:FollowSystemNodeTemperature '"
                                       + getObject<ModelObject>().nameString() + "'.");
      }
    }

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
