/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "SetpointManager/SetpointManagerMultiZoneMaximumHumidityAverage.hpp"
#include "SetpointManager/SetpointManagerMultiZoneMaximumHumidityAverage_Impl.hpp"

#include "Model.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/core/Compare.hpp>
#include <utilities/idd/IddEnums.hxx>
#include <utilities/idd/SetpointManager_MultiZone_MaximumHumidity_Average_FieldEnums.hxx>

namespace openstudio {
namespace epmodel {

  SetpointManagerMultiZoneMaximumHumidityAverage::SetpointManagerMultiZoneMaximumHumidityAverage(const Model& model)
    : SetpointManager(SetpointManagerMultiZoneMaximumHumidityAverage::iddObjectType(), model) {
    auto impl = getImpl<detail::SetpointManagerMultiZoneMaximumHumidityAverage_Impl>();
    OS_ASSERT(impl);
    OS_ASSERT(setMinimumSetpointHumidityRatio(0.008));
    OS_ASSERT(setMaximumSetpointHumidityRatio(0.015));
    detail::LoadContext context{const_cast<Model&>(model), SanitizationPolicy::Repair, SanitizationReport{}, {}};  // NOLINT
    impl->canonicalize(context);
  }

  SetpointManagerMultiZoneMaximumHumidityAverage::SetpointManagerMultiZoneMaximumHumidityAverage(
    std::shared_ptr<detail::SetpointManagerMultiZoneMaximumHumidityAverage_Impl> impl)
    : SetpointManager(std::move(impl)) {}

  IddObjectType SetpointManagerMultiZoneMaximumHumidityAverage::iddObjectType() {
    return IddObjectType::SetpointManager_MultiZone_MaximumHumidity_Average;
  }

  std::vector<std::string> SetpointManagerMultiZoneMaximumHumidityAverage::controlVariableValues() {
    return {"MaximumHumidityRatio"};
  }

  std::string SetpointManagerMultiZoneMaximumHumidityAverage::controlVariable() const {
    return "MaximumHumidityRatio";
  }

  bool SetpointManagerMultiZoneMaximumHumidityAverage::setControlVariable(const std::string& controlVariable) {
    return openstudio::istringEqual(controlVariable, "MaximumHumidityRatio");
  }

  double SetpointManagerMultiZoneMaximumHumidityAverage::minimumSetpointHumidityRatio() const {
    return getImpl<detail::SetpointManagerMultiZoneMaximumHumidityAverage_Impl>()->minimumSetpointHumidityRatio();
  }

  bool SetpointManagerMultiZoneMaximumHumidityAverage::setMinimumSetpointHumidityRatio(double minimumSetpointHumidityRatio) {
    const bool result =
      getImpl<detail::SetpointManagerMultiZoneMaximumHumidityAverage_Impl>()->setMinimumSetpointHumidityRatio(minimumSetpointHumidityRatio);
    OS_ASSERT(result);
    return result;
  }

  double SetpointManagerMultiZoneMaximumHumidityAverage::maximumSetpointHumidityRatio() const {
    return getImpl<detail::SetpointManagerMultiZoneMaximumHumidityAverage_Impl>()->maximumSetpointHumidityRatio();
  }

  bool SetpointManagerMultiZoneMaximumHumidityAverage::setMaximumSetpointHumidityRatio(double maximumSetpointHumidityRatio) {
    const bool result =
      getImpl<detail::SetpointManagerMultiZoneMaximumHumidityAverage_Impl>()->setMaximumSetpointHumidityRatio(maximumSetpointHumidityRatio);
    OS_ASSERT(result);
    return result;
  }

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
  namespace detail {

    double SetpointManagerMultiZoneMaximumHumidityAverage_Impl::minimumSetpointHumidityRatio() const {
      const auto value = getDouble(openstudio::SetpointManager_MultiZone_MaximumHumidity_AverageFields::MinimumSetpointHumidityRatio, true);
      OS_ASSERT(value);
      return *value;
    }

    bool SetpointManagerMultiZoneMaximumHumidityAverage_Impl::setMinimumSetpointHumidityRatio(double minimumSetpointHumidityRatio) {
      const bool result =
        setDouble(openstudio::SetpointManager_MultiZone_MaximumHumidity_AverageFields::MinimumSetpointHumidityRatio, minimumSetpointHumidityRatio);
      OS_ASSERT(result);
      return result;
    }

    double SetpointManagerMultiZoneMaximumHumidityAverage_Impl::maximumSetpointHumidityRatio() const {
      const auto value = getDouble(openstudio::SetpointManager_MultiZone_MaximumHumidity_AverageFields::MaximumSetpointHumidityRatio, true);
      OS_ASSERT(value);
      return *value;
    }

    bool SetpointManagerMultiZoneMaximumHumidityAverage_Impl::setMaximumSetpointHumidityRatio(double maximumSetpointHumidityRatio) {
      const bool result =
        setDouble(openstudio::SetpointManager_MultiZone_MaximumHumidity_AverageFields::MaximumSetpointHumidityRatio, maximumSetpointHumidityRatio);
      OS_ASSERT(result);
      return result;
    }

    boost::optional<openstudio::epmodel::Node> SetpointManagerMultiZoneMaximumHumidityAverage_Impl::setpointNode() const {
      return getObject<ModelObject>().getModelObjectTarget<openstudio::epmodel::Node>(
        openstudio::SetpointManager_MultiZone_MaximumHumidity_AverageFields::SetpointNodeorNodeListName);
    }

    std::string SetpointManagerMultiZoneMaximumHumidityAverage_Impl::controlVariable() const {
      return "MaximumHumidityRatio";
    }

    bool SetpointManagerMultiZoneMaximumHumidityAverage_Impl::setControlVariable(const std::string& value) {
      return openstudio::istringEqual(value, "MaximumHumidityRatio");
    }

    bool SetpointManagerMultiZoneMaximumHumidityAverage_Impl::setSetpointNode(const openstudio::epmodel::Node& node) {
      return getObject<ModelObject>().setPointer(openstudio::SetpointManager_MultiZone_MaximumHumidity_AverageFields::SetpointNodeorNodeListName,
                                                 node.handle());
    }

    void SetpointManagerMultiZoneMaximumHumidityAverage_Impl::doCanonicalize(LoadContext& context) {
      SetpointManager_Impl::doCanonicalize(context);
      canonicalizeSetpointNodeField(context, openstudio::SetpointManager_MultiZone_MaximumHumidity_AverageFields::SetpointNodeorNodeListName);

      if (auto value = getDouble(openstudio::SetpointManager_MultiZone_MaximumHumidity_AverageFields::MinimumSetpointHumidityRatio, true)) {
        (void)value;
      } else {
        OS_ASSERT(setDouble(openstudio::SetpointManager_MultiZone_MaximumHumidity_AverageFields::MinimumSetpointHumidityRatio, 0.008));
        detail::addLoadInfo(context, "Set default Minimum Setpoint Humidity Ratio to 0.008 for SetpointManager:MultiZone:MaximumHumidity:Average '"
                                       + getObject<ModelObject>().nameString() + "'.");
      }

      if (auto value = getDouble(openstudio::SetpointManager_MultiZone_MaximumHumidity_AverageFields::MaximumSetpointHumidityRatio, true)) {
        (void)value;
      } else {
        OS_ASSERT(setDouble(openstudio::SetpointManager_MultiZone_MaximumHumidity_AverageFields::MaximumSetpointHumidityRatio, 0.015));
        detail::addLoadInfo(context, "Set default Maximum Setpoint Humidity Ratio to 0.015 for SetpointManager:MultiZone:MaximumHumidity:Average '"
                                      + getObject<ModelObject>().nameString() + "'.");
      }
    }

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
