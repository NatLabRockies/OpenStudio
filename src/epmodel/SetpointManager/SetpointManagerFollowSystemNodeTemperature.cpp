/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "SetpointManager/SetpointManagerFollowSystemNodeTemperature.hpp"
#include "SetpointManager/SetpointManagerFollowSystemNodeTemperature_Impl.hpp"

#include "Model.hpp"

#include <utilities/core/Assert.hpp>
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

    bool SetpointManagerFollowSystemNodeTemperature_Impl::isAllowedOnPlantLoop() const {
      return true;
    }

    unsigned SetpointManagerFollowSystemNodeTemperature_Impl::setpointNodeFieldIndex() const {
      return openstudio::SetpointManager_FollowSystemNodeTemperatureFields::SetpointNodeorNodeListName;
    }

    unsigned SetpointManagerFollowSystemNodeTemperature_Impl::controlVariableFieldIndex() const {
      return openstudio::SetpointManager_FollowSystemNodeTemperatureFields::ControlVariable;
    }

    void SetpointManagerFollowSystemNodeTemperature_Impl::doCanonicalize(LoadContext& context) {
      SetpointManager_Impl::doCanonicalize(context);

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
