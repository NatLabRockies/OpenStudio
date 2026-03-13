/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "SetpointManager/SetpointManagerColdest.hpp"
#include "SetpointManager/SetpointManagerColdest_Impl.hpp"

#include "Model.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/idd/IddEnums.hxx>
#include <utilities/idd/IddFactory.hxx>
#include <utilities/idd/SetpointManager_Coldest_FieldEnums.hxx>

namespace openstudio {
namespace epmodel {

  SetpointManagerColdest::SetpointManagerColdest(const Model& model) : SetpointManager(SetpointManagerColdest::iddObjectType(), model) {
    auto impl = getImpl<detail::SetpointManagerColdest_Impl>();
    OS_ASSERT(impl);
    OS_ASSERT(setControlVariable("Temperature"));
    OS_ASSERT(setMinimumSetpointTemperature(20.0));
    OS_ASSERT(setMaximumSetpointTemperature(50.0));
    OS_ASSERT(setStrategy("MinimumTemperature"));
    detail::LoadContext context{const_cast<Model&>(model), SanitizationPolicy::Repair, SanitizationReport{}, {}};  // NOLINT
    impl->canonicalize(context);
  }

  SetpointManagerColdest::SetpointManagerColdest(std::shared_ptr<detail::SetpointManagerColdest_Impl> impl) : SetpointManager(std::move(impl)) {}

  IddObjectType SetpointManagerColdest::iddObjectType() {
    return IddObjectType::SetpointManager_Coldest;
  }

  std::vector<std::string> SetpointManagerColdest::controlVariableValues() {
    return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(), openstudio::SetpointManager_ColdestFields::ControlVariable);
  }

  std::vector<std::string> SetpointManagerColdest::strategyValues() {
    return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(), openstudio::SetpointManager_ColdestFields::Strategy);
  }

  double SetpointManagerColdest::minimumSetpointTemperature() const {
    return getImpl<detail::SetpointManagerColdest_Impl>()->minimumSetpointTemperature();
  }

  bool SetpointManagerColdest::setMinimumSetpointTemperature(double minimumSetpointTemperature) {
    const bool result = getImpl<detail::SetpointManagerColdest_Impl>()->setMinimumSetpointTemperature(minimumSetpointTemperature);
    OS_ASSERT(result);
    return result;
  }

  double SetpointManagerColdest::maximumSetpointTemperature() const {
    return getImpl<detail::SetpointManagerColdest_Impl>()->maximumSetpointTemperature();
  }

  bool SetpointManagerColdest::setMaximumSetpointTemperature(double maximumSetpointTemperature) {
    const bool result = getImpl<detail::SetpointManagerColdest_Impl>()->setMaximumSetpointTemperature(maximumSetpointTemperature);
    OS_ASSERT(result);
    return result;
  }

  std::string SetpointManagerColdest::strategy() const {
    return getImpl<detail::SetpointManagerColdest_Impl>()->strategy();
  }

  bool SetpointManagerColdest::setStrategy(const std::string& strategy) {
    return getImpl<detail::SetpointManagerColdest_Impl>()->setStrategy(strategy);
  }

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
  namespace detail {

    double SetpointManagerColdest_Impl::minimumSetpointTemperature() const {
      const auto value = getDouble(openstudio::SetpointManager_ColdestFields::MinimumSetpointTemperature, true);
      OS_ASSERT(value);
      return *value;
    }

    bool SetpointManagerColdest_Impl::setMinimumSetpointTemperature(double minimumSetpointTemperature) {
      const bool result = setDouble(openstudio::SetpointManager_ColdestFields::MinimumSetpointTemperature, minimumSetpointTemperature);
      OS_ASSERT(result);
      return result;
    }

    double SetpointManagerColdest_Impl::maximumSetpointTemperature() const {
      const auto value = getDouble(openstudio::SetpointManager_ColdestFields::MaximumSetpointTemperature, true);
      OS_ASSERT(value);
      return *value;
    }

    bool SetpointManagerColdest_Impl::setMaximumSetpointTemperature(double maximumSetpointTemperature) {
      const bool result = setDouble(openstudio::SetpointManager_ColdestFields::MaximumSetpointTemperature, maximumSetpointTemperature);
      OS_ASSERT(result);
      return result;
    }

    std::string SetpointManagerColdest_Impl::strategy() const {
      const auto value = getString(openstudio::SetpointManager_ColdestFields::Strategy, true);
      OS_ASSERT(value);
      return *value;
    }

    bool SetpointManagerColdest_Impl::setStrategy(const std::string& strategy) {
      return setString(openstudio::SetpointManager_ColdestFields::Strategy, strategy);
    }

    unsigned SetpointManagerColdest_Impl::setpointNodeFieldIndex() const {
      return openstudio::SetpointManager_ColdestFields::SetpointNodeorNodeListName;
    }

    unsigned SetpointManagerColdest_Impl::controlVariableFieldIndex() const {
      return openstudio::SetpointManager_ColdestFields::ControlVariable;
    }

    void SetpointManagerColdest_Impl::doCanonicalize(LoadContext& context) {
      SetpointManager_Impl::doCanonicalize(context);

      if (auto value = getString(openstudio::SetpointManager_ColdestFields::ControlVariable, true)) {
        if (!value->empty()) {
          // continue
        } else {
          OS_ASSERT(setString(openstudio::SetpointManager_ColdestFields::ControlVariable, "Temperature"));
          detail::addLoadInfo(context, "Set default Control Variable to 'Temperature' for SetpointManager:Coldest '"
                                         + getObject<ModelObject>().nameString() + "'.");
        }
      } else {
        OS_ASSERT(setString(openstudio::SetpointManager_ColdestFields::ControlVariable, "Temperature"));
        detail::addLoadInfo(context, "Set default Control Variable to 'Temperature' for SetpointManager:Coldest '"
                                       + getObject<ModelObject>().nameString() + "'.");
      }

      if (auto value = getDouble(openstudio::SetpointManager_ColdestFields::MinimumSetpointTemperature, true)) {
        (void)value;
      } else {
        OS_ASSERT(setDouble(openstudio::SetpointManager_ColdestFields::MinimumSetpointTemperature, 20.0));
        detail::addLoadInfo(context, "Set default Minimum Setpoint Temperature to 20 for SetpointManager:Coldest '"
                                       + getObject<ModelObject>().nameString() + "'.");
      }

      if (auto value = getDouble(openstudio::SetpointManager_ColdestFields::MaximumSetpointTemperature, true)) {
        (void)value;
      } else {
        OS_ASSERT(setDouble(openstudio::SetpointManager_ColdestFields::MaximumSetpointTemperature, 50.0));
        detail::addLoadInfo(context, "Set default Maximum Setpoint Temperature to 50 for SetpointManager:Coldest '"
                                       + getObject<ModelObject>().nameString() + "'.");
      }

      if (auto value = getString(openstudio::SetpointManager_ColdestFields::Strategy, true)) {
        if (!value->empty()) {
          return;
        }
      }

      OS_ASSERT(setString(openstudio::SetpointManager_ColdestFields::Strategy, "MinimumTemperature"));
      detail::addLoadInfo(context, "Set default Strategy to 'MinimumTemperature' for SetpointManager:Coldest '"
                                     + getObject<ModelObject>().nameString() + "'.");
    }

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
