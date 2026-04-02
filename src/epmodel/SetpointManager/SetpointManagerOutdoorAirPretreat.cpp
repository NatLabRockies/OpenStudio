/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "SetpointManager/SetpointManagerOutdoorAirPretreat.hpp"
#include "SetpointManager/SetpointManagerOutdoorAirPretreat_Impl.hpp"

#include "Model.hpp"

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
      return getObject<ModelObject>().setPointer(openstudio::SetpointManager_OutdoorAirPretreatFields::SetpointNodeorNodeListName,
                                                 node.handle());
    }

    void SetpointManagerOutdoorAirPretreat_Impl::doCanonicalize(LoadContext& context) {
      SetpointManager_Impl::doCanonicalize(context);
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
