/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "SetpointManager/SetpointManagerFollowOutdoorAirTemperature.hpp"
#include "SetpointManager/SetpointManagerFollowOutdoorAirTemperature_Impl.hpp"

#include "Model.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/core/Compare.hpp>
#include <utilities/idd/IddEnums.hxx>
#include <utilities/idd/SetpointManager_FollowOutdoorAirTemperature_FieldEnums.hxx>

namespace openstudio {
namespace epmodel {

  SetpointManagerFollowOutdoorAirTemperature::SetpointManagerFollowOutdoorAirTemperature(const Model& model)
    : SetpointManager(SetpointManagerFollowOutdoorAirTemperature::iddObjectType(), model) {
    auto impl = getImpl<detail::SetpointManagerFollowOutdoorAirTemperature_Impl>();
    OS_ASSERT(impl);
    OS_ASSERT(setControlVariable("Temperature"));
    OS_ASSERT(setReferenceTemperatureType("OutdoorAirWetBulb"));
    OS_ASSERT(setOffsetTemperatureDifference(1.5));
    OS_ASSERT(setMaximumSetpointTemperature(80.0));
    OS_ASSERT(setMinimumSetpointTemperature(6.0));
    detail::LoadContext context{const_cast<Model&>(model), SanitizationPolicy::Repair, SanitizationReport{}, {}};  // NOLINT
    impl->canonicalize(context);
  }

  SetpointManagerFollowOutdoorAirTemperature::SetpointManagerFollowOutdoorAirTemperature(
    std::shared_ptr<detail::SetpointManagerFollowOutdoorAirTemperature_Impl> impl)
    : SetpointManager(std::move(impl)) {}

  IddObjectType SetpointManagerFollowOutdoorAirTemperature::iddObjectType() {
    return IddObjectType::SetpointManager_FollowOutdoorAirTemperature;
  }

  std::string SetpointManagerFollowOutdoorAirTemperature::referenceTemperatureType() const {
    return getImpl<detail::SetpointManagerFollowOutdoorAirTemperature_Impl>()->referenceTemperatureType();
  }

  bool SetpointManagerFollowOutdoorAirTemperature::setReferenceTemperatureType(const std::string& value) {
    return getImpl<detail::SetpointManagerFollowOutdoorAirTemperature_Impl>()->setReferenceTemperatureType(value);
  }

  double SetpointManagerFollowOutdoorAirTemperature::offsetTemperatureDifference() const {
    return getImpl<detail::SetpointManagerFollowOutdoorAirTemperature_Impl>()->offsetTemperatureDifference();
  }

  bool SetpointManagerFollowOutdoorAirTemperature::setOffsetTemperatureDifference(double value) {
    const bool result = getImpl<detail::SetpointManagerFollowOutdoorAirTemperature_Impl>()->setOffsetTemperatureDifference(value);
    OS_ASSERT(result);
    return result;
  }

  double SetpointManagerFollowOutdoorAirTemperature::maximumSetpointTemperature() const {
    return getImpl<detail::SetpointManagerFollowOutdoorAirTemperature_Impl>()->maximumSetpointTemperature();
  }

  bool SetpointManagerFollowOutdoorAirTemperature::setMaximumSetpointTemperature(double value) {
    const bool result = getImpl<detail::SetpointManagerFollowOutdoorAirTemperature_Impl>()->setMaximumSetpointTemperature(value);
    OS_ASSERT(result);
    return result;
  }

  double SetpointManagerFollowOutdoorAirTemperature::minimumSetpointTemperature() const {
    return getImpl<detail::SetpointManagerFollowOutdoorAirTemperature_Impl>()->minimumSetpointTemperature();
  }

  bool SetpointManagerFollowOutdoorAirTemperature::setMinimumSetpointTemperature(double value) {
    const bool result = getImpl<detail::SetpointManagerFollowOutdoorAirTemperature_Impl>()->setMinimumSetpointTemperature(value);
    OS_ASSERT(result);
    return result;
  }

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
  namespace detail {

    std::string SetpointManagerFollowOutdoorAirTemperature_Impl::referenceTemperatureType() const {
      const auto value = getString(openstudio::SetpointManager_FollowOutdoorAirTemperatureFields::ReferenceTemperatureType, true);
      OS_ASSERT(value);
      return *value;
    }

    bool SetpointManagerFollowOutdoorAirTemperature_Impl::setReferenceTemperatureType(const std::string& value) {
      if (istringEqual(value, "OutdoorAirWetBulb")) {
        return setString(openstudio::SetpointManager_FollowOutdoorAirTemperatureFields::ReferenceTemperatureType, "OutdoorAirWetBulb");
      }
      if (istringEqual(value, "OutdoorAirDryBulb")) {
        return setString(openstudio::SetpointManager_FollowOutdoorAirTemperatureFields::ReferenceTemperatureType, "OutdoorAirDryBulb");
      }
      return false;
    }

    double SetpointManagerFollowOutdoorAirTemperature_Impl::offsetTemperatureDifference() const {
      const auto value = getDouble(openstudio::SetpointManager_FollowOutdoorAirTemperatureFields::OffsetTemperatureDifference, true);
      OS_ASSERT(value);
      return *value;
    }

    bool SetpointManagerFollowOutdoorAirTemperature_Impl::setOffsetTemperatureDifference(double value) {
      const bool result = setDouble(openstudio::SetpointManager_FollowOutdoorAirTemperatureFields::OffsetTemperatureDifference, value);
      OS_ASSERT(result);
      return result;
    }

    double SetpointManagerFollowOutdoorAirTemperature_Impl::maximumSetpointTemperature() const {
      const auto value = getDouble(openstudio::SetpointManager_FollowOutdoorAirTemperatureFields::MaximumSetpointTemperature, true);
      OS_ASSERT(value);
      return *value;
    }

    bool SetpointManagerFollowOutdoorAirTemperature_Impl::setMaximumSetpointTemperature(double value) {
      const bool result = setDouble(openstudio::SetpointManager_FollowOutdoorAirTemperatureFields::MaximumSetpointTemperature, value);
      OS_ASSERT(result);
      return result;
    }

    double SetpointManagerFollowOutdoorAirTemperature_Impl::minimumSetpointTemperature() const {
      const auto value = getDouble(openstudio::SetpointManager_FollowOutdoorAirTemperatureFields::MinimumSetpointTemperature, true);
      OS_ASSERT(value);
      return *value;
    }

    bool SetpointManagerFollowOutdoorAirTemperature_Impl::setMinimumSetpointTemperature(double value) {
      const bool result = setDouble(openstudio::SetpointManager_FollowOutdoorAirTemperatureFields::MinimumSetpointTemperature, value);
      OS_ASSERT(result);
      return result;
    }

    bool SetpointManagerFollowOutdoorAirTemperature_Impl::isAllowedOnPlantLoop() const {
      return true;
    }

    boost::optional<openstudio::epmodel::Node> SetpointManagerFollowOutdoorAirTemperature_Impl::setpointNode() const {
      return getObject<ModelObject>().getModelObjectTarget<openstudio::epmodel::Node>(
        openstudio::SetpointManager_FollowOutdoorAirTemperatureFields::SetpointNodeorNodeListName);
    }

    std::string SetpointManagerFollowOutdoorAirTemperature_Impl::controlVariable() const {
      if (auto value = getString(openstudio::SetpointManager_FollowOutdoorAirTemperatureFields::ControlVariable, true)) {
        return *value;
      }
      return "";
    }

    bool SetpointManagerFollowOutdoorAirTemperature_Impl::setControlVariable(const std::string& value) {
      return setString(openstudio::SetpointManager_FollowOutdoorAirTemperatureFields::ControlVariable, value);
    }

    bool SetpointManagerFollowOutdoorAirTemperature_Impl::setSetpointNode(const openstudio::epmodel::Node& node) {
      return getObject<ModelObject>().setPointer(openstudio::SetpointManager_FollowOutdoorAirTemperatureFields::SetpointNodeorNodeListName,
                                                 node.handle());
    }

    void SetpointManagerFollowOutdoorAirTemperature_Impl::doCanonicalize(LoadContext& context) {
      SetpointManager_Impl::doCanonicalize(context);
      canonicalizeSetpointNodeField(context, openstudio::SetpointManager_FollowOutdoorAirTemperatureFields::SetpointNodeorNodeListName);

      if (auto value = getString(openstudio::SetpointManager_FollowOutdoorAirTemperatureFields::ControlVariable, true)) {
        if (!value->empty()) {
          // continue
        } else {
          OS_ASSERT(setString(openstudio::SetpointManager_FollowOutdoorAirTemperatureFields::ControlVariable, "Temperature"));
          detail::addLoadInfo(context, "Set default Control Variable to 'Temperature' for SetpointManager:FollowOutdoorAirTemperature '"
                                         + getObject<ModelObject>().nameString() + "'.");
        }
      } else {
        OS_ASSERT(setString(openstudio::SetpointManager_FollowOutdoorAirTemperatureFields::ControlVariable, "Temperature"));
        detail::addLoadInfo(context, "Set default Control Variable to 'Temperature' for SetpointManager:FollowOutdoorAirTemperature '"
                                       + getObject<ModelObject>().nameString() + "'.");
      }

      if (auto value = getString(openstudio::SetpointManager_FollowOutdoorAirTemperatureFields::ReferenceTemperatureType, true)) {
        if (!value->empty()) {
          // continue
        } else {
          OS_ASSERT(setString(openstudio::SetpointManager_FollowOutdoorAirTemperatureFields::ReferenceTemperatureType, "OutdoorAirWetBulb"));
          detail::addLoadInfo(context, "Set default Reference Temperature Type to 'OutdoorAirWetBulb' for "
                                       "SetpointManager:FollowOutdoorAirTemperature '"
                                         + getObject<ModelObject>().nameString() + "'.");
        }
      } else {
        OS_ASSERT(setString(openstudio::SetpointManager_FollowOutdoorAirTemperatureFields::ReferenceTemperatureType, "OutdoorAirWetBulb"));
        detail::addLoadInfo(context, "Set default Reference Temperature Type to 'OutdoorAirWetBulb' for "
                                     "SetpointManager:FollowOutdoorAirTemperature '"
                                       + getObject<ModelObject>().nameString() + "'.");
      }

      if (auto value = getDouble(openstudio::SetpointManager_FollowOutdoorAirTemperatureFields::OffsetTemperatureDifference, true)) {
        (void)value;
      } else {
        OS_ASSERT(setDouble(openstudio::SetpointManager_FollowOutdoorAirTemperatureFields::OffsetTemperatureDifference, 1.5));
        detail::addLoadInfo(context, "Set default Offset Temperature Difference to 1.5 for SetpointManager:FollowOutdoorAirTemperature '"
                                       + getObject<ModelObject>().nameString() + "'.");
      }

      if (auto value = getDouble(openstudio::SetpointManager_FollowOutdoorAirTemperatureFields::MaximumSetpointTemperature, true)) {
        (void)value;
      } else {
        OS_ASSERT(setDouble(openstudio::SetpointManager_FollowOutdoorAirTemperatureFields::MaximumSetpointTemperature, 80.0));
        detail::addLoadInfo(context, "Set default Maximum Setpoint Temperature to 80 for SetpointManager:FollowOutdoorAirTemperature '"
                                       + getObject<ModelObject>().nameString() + "'.");
      }

      if (auto value = getDouble(openstudio::SetpointManager_FollowOutdoorAirTemperatureFields::MinimumSetpointTemperature, true)) {
        (void)value;
      } else {
        OS_ASSERT(setDouble(openstudio::SetpointManager_FollowOutdoorAirTemperatureFields::MinimumSetpointTemperature, 6.0));
        detail::addLoadInfo(context, "Set default Minimum Setpoint Temperature to 6 for SetpointManager:FollowOutdoorAirTemperature '"
                                       + getObject<ModelObject>().nameString() + "'.");
      }
    }

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
