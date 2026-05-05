/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "SetpointManager/SetpointManagerMultiZoneCoolingAverage.hpp"
#include "SetpointManager/SetpointManagerMultiZoneCoolingAverage_Impl.hpp"

#include "Model.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/core/Compare.hpp>
#include <utilities/idd/IddEnums.hxx>
#include <utilities/idd/SetpointManager_MultiZone_Cooling_Average_FieldEnums.hxx>

namespace openstudio {
namespace epmodel {

  SetpointManagerMultiZoneCoolingAverage::SetpointManagerMultiZoneCoolingAverage(const Model& model)
    : SetpointManager(SetpointManagerMultiZoneCoolingAverage::iddObjectType(), model) {
    auto impl = getImpl<detail::SetpointManagerMultiZoneCoolingAverage_Impl>();
    OS_ASSERT(impl);
    OS_ASSERT(setMinimumSetpointTemperature(12.0));
    OS_ASSERT(setMaximumSetpointTemperature(18.0));
    detail::LoadContext context{const_cast<Model&>(model), SanitizationPolicy::Repair, SanitizationReport{}, {}};  // NOLINT
    impl->canonicalize(context);
  }

  SetpointManagerMultiZoneCoolingAverage::SetpointManagerMultiZoneCoolingAverage(
    std::shared_ptr<detail::SetpointManagerMultiZoneCoolingAverage_Impl> impl)
    : SetpointManager(std::move(impl)) {}

  IddObjectType SetpointManagerMultiZoneCoolingAverage::iddObjectType() {
    return IddObjectType::SetpointManager_MultiZone_Cooling_Average;
  }

  std::vector<std::string> SetpointManagerMultiZoneCoolingAverage::controlVariableValues() {
    return {"Temperature"};
  }

  std::string SetpointManagerMultiZoneCoolingAverage::controlVariable() const {
    return "Temperature";
  }

  bool SetpointManagerMultiZoneCoolingAverage::setControlVariable(const std::string& controlVariable) {
    return openstudio::istringEqual(controlVariable, "Temperature");
  }

  double SetpointManagerMultiZoneCoolingAverage::minimumSetpointTemperature() const {
    return getImpl<detail::SetpointManagerMultiZoneCoolingAverage_Impl>()->minimumSetpointTemperature();
  }

  bool SetpointManagerMultiZoneCoolingAverage::setMinimumSetpointTemperature(double minimumSetpointTemperature) {
    const bool result = getImpl<detail::SetpointManagerMultiZoneCoolingAverage_Impl>()->setMinimumSetpointTemperature(minimumSetpointTemperature);
    OS_ASSERT(result);
    return result;
  }

  double SetpointManagerMultiZoneCoolingAverage::maximumSetpointTemperature() const {
    return getImpl<detail::SetpointManagerMultiZoneCoolingAverage_Impl>()->maximumSetpointTemperature();
  }

  bool SetpointManagerMultiZoneCoolingAverage::setMaximumSetpointTemperature(double maximumSetpointTemperature) {
    const bool result = getImpl<detail::SetpointManagerMultiZoneCoolingAverage_Impl>()->setMaximumSetpointTemperature(maximumSetpointTemperature);
    OS_ASSERT(result);
    return result;
  }

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
  namespace detail {

    double SetpointManagerMultiZoneCoolingAverage_Impl::minimumSetpointTemperature() const {
      const auto value = getDouble(openstudio::SetpointManager_MultiZone_Cooling_AverageFields::MinimumSetpointTemperature, true);
      OS_ASSERT(value);
      return *value;
    }

    bool SetpointManagerMultiZoneCoolingAverage_Impl::setMinimumSetpointTemperature(double minimumSetpointTemperature) {
      const bool result =
        setDouble(openstudio::SetpointManager_MultiZone_Cooling_AverageFields::MinimumSetpointTemperature, minimumSetpointTemperature);
      OS_ASSERT(result);
      return result;
    }

    double SetpointManagerMultiZoneCoolingAverage_Impl::maximumSetpointTemperature() const {
      const auto value = getDouble(openstudio::SetpointManager_MultiZone_Cooling_AverageFields::MaximumSetpointTemperature, true);
      OS_ASSERT(value);
      return *value;
    }

    bool SetpointManagerMultiZoneCoolingAverage_Impl::setMaximumSetpointTemperature(double maximumSetpointTemperature) {
      const bool result =
        setDouble(openstudio::SetpointManager_MultiZone_Cooling_AverageFields::MaximumSetpointTemperature, maximumSetpointTemperature);
      OS_ASSERT(result);
      return result;
    }

    boost::optional<openstudio::epmodel::Node> SetpointManagerMultiZoneCoolingAverage_Impl::setpointNode() const {
      return getObject<ModelObject>().getModelObjectTarget<openstudio::epmodel::Node>(
        openstudio::SetpointManager_MultiZone_Cooling_AverageFields::SetpointNodeorNodeListName);
    }

    std::string SetpointManagerMultiZoneCoolingAverage_Impl::controlVariable() const {
      return "Temperature";
    }

    bool SetpointManagerMultiZoneCoolingAverage_Impl::setControlVariable(const std::string& value) {
      return openstudio::istringEqual(value, "Temperature");
    }

    bool SetpointManagerMultiZoneCoolingAverage_Impl::setSetpointNode(const openstudio::epmodel::Node& node) {
      return getObject<ModelObject>().setPointer(openstudio::SetpointManager_MultiZone_Cooling_AverageFields::SetpointNodeorNodeListName,
                                                 node.handle());
    }

    void SetpointManagerMultiZoneCoolingAverage_Impl::doCanonicalize(LoadContext& context) {
      SetpointManager_Impl::doCanonicalize(context);
      canonicalizeSetpointNodeField(context, openstudio::SetpointManager_MultiZone_Cooling_AverageFields::SetpointNodeorNodeListName);

      if (auto value = getDouble(openstudio::SetpointManager_MultiZone_Cooling_AverageFields::MinimumSetpointTemperature, true)) {
        (void)value;
      } else {
        OS_ASSERT(setDouble(openstudio::SetpointManager_MultiZone_Cooling_AverageFields::MinimumSetpointTemperature, 12.0));
        detail::addLoadInfo(context, "Set default Minimum Setpoint Temperature to 12 for SetpointManager:MultiZone:Cooling:Average '"
                                       + getObject<ModelObject>().nameString() + "'.");
      }

      if (auto value = getDouble(openstudio::SetpointManager_MultiZone_Cooling_AverageFields::MaximumSetpointTemperature, true)) {
        (void)value;
      } else {
        OS_ASSERT(setDouble(openstudio::SetpointManager_MultiZone_Cooling_AverageFields::MaximumSetpointTemperature, 18.0));
        detail::addLoadInfo(context, "Set default Maximum Setpoint Temperature to 18 for SetpointManager:MultiZone:Cooling:Average '"
                                       + getObject<ModelObject>().nameString() + "'.");
      }
    }

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
