/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "SetpointManager/SetpointManagerSingleZoneCooling.hpp"
#include "SetpointManager/SetpointManagerSingleZoneCooling_Impl.hpp"

#include "Model.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/idd/IddEnums.hxx>
#include <utilities/idd/SetpointManager_SingleZone_Cooling_FieldEnums.hxx>

namespace openstudio {
namespace epmodel {

  SetpointManagerSingleZoneCooling::SetpointManagerSingleZoneCooling(const Model& model)
    : SetpointManager(SetpointManagerSingleZoneCooling::iddObjectType(), model) {
    auto impl = getImpl<detail::SetpointManagerSingleZoneCooling_Impl>();
    OS_ASSERT(impl);
    OS_ASSERT(setControlVariable("Temperature"));
    OS_ASSERT(setMinimumSupplyAirTemperature(-99.0));
    OS_ASSERT(setMaximumSupplyAirTemperature(99.0));
    detail::LoadContext context{const_cast<Model&>(model), SanitizationPolicy::Repair, SanitizationReport{}, {}};  // NOLINT
    impl->canonicalize(context);
  }

  SetpointManagerSingleZoneCooling::SetpointManagerSingleZoneCooling(std::shared_ptr<detail::SetpointManagerSingleZoneCooling_Impl> impl)
    : SetpointManager(std::move(impl)) {}

  IddObjectType SetpointManagerSingleZoneCooling::iddObjectType() {
    return IddObjectType::SetpointManager_SingleZone_Cooling;
  }

  double SetpointManagerSingleZoneCooling::minimumSupplyAirTemperature() const {
    return getImpl<detail::SetpointManagerSingleZoneCooling_Impl>()->minimumSupplyAirTemperature();
  }

  bool SetpointManagerSingleZoneCooling::setMinimumSupplyAirTemperature(double minimumSupplyAirTemperature) {
    const bool result = getImpl<detail::SetpointManagerSingleZoneCooling_Impl>()->setMinimumSupplyAirTemperature(minimumSupplyAirTemperature);
    OS_ASSERT(result);
    return result;
  }

  double SetpointManagerSingleZoneCooling::maximumSupplyAirTemperature() const {
    return getImpl<detail::SetpointManagerSingleZoneCooling_Impl>()->maximumSupplyAirTemperature();
  }

  bool SetpointManagerSingleZoneCooling::setMaximumSupplyAirTemperature(double maximumSupplyAirTemperature) {
    const bool result = getImpl<detail::SetpointManagerSingleZoneCooling_Impl>()->setMaximumSupplyAirTemperature(maximumSupplyAirTemperature);
    OS_ASSERT(result);
    return result;
  }

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
  namespace detail {

    double SetpointManagerSingleZoneCooling_Impl::minimumSupplyAirTemperature() const {
      const auto value = getDouble(openstudio::SetpointManager_SingleZone_CoolingFields::MinimumSupplyAirTemperature, true);
      OS_ASSERT(value);
      return *value;
    }

    bool SetpointManagerSingleZoneCooling_Impl::setMinimumSupplyAirTemperature(double minimumSupplyAirTemperature) {
      const bool result = setDouble(openstudio::SetpointManager_SingleZone_CoolingFields::MinimumSupplyAirTemperature, minimumSupplyAirTemperature);
      OS_ASSERT(result);
      return result;
    }

    double SetpointManagerSingleZoneCooling_Impl::maximumSupplyAirTemperature() const {
      const auto value = getDouble(openstudio::SetpointManager_SingleZone_CoolingFields::MaximumSupplyAirTemperature, true);
      OS_ASSERT(value);
      return *value;
    }

    bool SetpointManagerSingleZoneCooling_Impl::setMaximumSupplyAirTemperature(double maximumSupplyAirTemperature) {
      const bool result = setDouble(openstudio::SetpointManager_SingleZone_CoolingFields::MaximumSupplyAirTemperature, maximumSupplyAirTemperature);
      OS_ASSERT(result);
      return result;
    }

    boost::optional<openstudio::epmodel::Node> SetpointManagerSingleZoneCooling_Impl::setpointNode() const {
      return getObject<ModelObject>().getModelObjectTarget<openstudio::epmodel::Node>(
        openstudio::SetpointManager_SingleZone_CoolingFields::SetpointNodeorNodeListName);
    }

    std::string SetpointManagerSingleZoneCooling_Impl::controlVariable() const {
      if (auto value = getString(openstudio::SetpointManager_SingleZone_CoolingFields::ControlVariable, true)) {
        return *value;
      }
      return "";
    }

    bool SetpointManagerSingleZoneCooling_Impl::setControlVariable(const std::string& value) {
      return setString(openstudio::SetpointManager_SingleZone_CoolingFields::ControlVariable, value);
    }

    bool SetpointManagerSingleZoneCooling_Impl::setSetpointNode(const openstudio::epmodel::Node& node) {
      return getObject<ModelObject>().setPointer(openstudio::SetpointManager_SingleZone_CoolingFields::SetpointNodeorNodeListName, node.handle());
    }

    void SetpointManagerSingleZoneCooling_Impl::doCanonicalize(LoadContext& context) {
      SetpointManager_Impl::doCanonicalize(context);
      canonicalizeSetpointNodeField(context, openstudio::SetpointManager_SingleZone_CoolingFields::SetpointNodeorNodeListName);

      if (auto value = getString(openstudio::SetpointManager_SingleZone_CoolingFields::ControlVariable, true)) {
        if (!value->empty()) {
          // continue
        } else {
          OS_ASSERT(setString(openstudio::SetpointManager_SingleZone_CoolingFields::ControlVariable, "Temperature"));
          detail::addLoadInfo(context, "Set default Control Variable to 'Temperature' for SetpointManager:SingleZone:Cooling '"
                                         + getObject<ModelObject>().nameString() + "'.");
        }
      } else {
        OS_ASSERT(setString(openstudio::SetpointManager_SingleZone_CoolingFields::ControlVariable, "Temperature"));
        detail::addLoadInfo(context, "Set default Control Variable to 'Temperature' for SetpointManager:SingleZone:Cooling '"
                                       + getObject<ModelObject>().nameString() + "'.");
      }

      if (auto value = getDouble(openstudio::SetpointManager_SingleZone_CoolingFields::MinimumSupplyAirTemperature, true)) {
        (void)value;
      } else {
        OS_ASSERT(setDouble(openstudio::SetpointManager_SingleZone_CoolingFields::MinimumSupplyAirTemperature, -99.0));
        detail::addLoadInfo(context, "Set default Minimum Supply Air Temperature to -99 for SetpointManager:SingleZone:Cooling '"
                                       + getObject<ModelObject>().nameString() + "'.");
      }

      if (auto value = getDouble(openstudio::SetpointManager_SingleZone_CoolingFields::MaximumSupplyAirTemperature, true)) {
        (void)value;
      } else {
        OS_ASSERT(setDouble(openstudio::SetpointManager_SingleZone_CoolingFields::MaximumSupplyAirTemperature, 99.0));
        detail::addLoadInfo(context, "Set default Maximum Supply Air Temperature to 99 for SetpointManager:SingleZone:Cooling '"
                                       + getObject<ModelObject>().nameString() + "'.");
      }
    }

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
