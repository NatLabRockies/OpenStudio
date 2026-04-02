/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "SetpointManager/SetpointManagerSingleZoneOneStageCooling.hpp"
#include "SetpointManager/SetpointManagerSingleZoneOneStageCooling_Impl.hpp"

#include "Model.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/core/Compare.hpp>
#include <utilities/idd/IddEnums.hxx>
#include <utilities/idd/SetpointManager_SingleZone_OneStageCooling_FieldEnums.hxx>

namespace openstudio {
namespace epmodel {

  SetpointManagerSingleZoneOneStageCooling::SetpointManagerSingleZoneOneStageCooling(const Model& model)
    : SetpointManager(SetpointManagerSingleZoneOneStageCooling::iddObjectType(), model) {
    auto impl = getImpl<detail::SetpointManagerSingleZoneOneStageCooling_Impl>();
    OS_ASSERT(impl);
    OS_ASSERT(setControlVariable("Temperature"));
    OS_ASSERT(setCoolingStageOnSupplyAirSetpointTemperature(-99.0));
    OS_ASSERT(setCoolingStageOffSupplyAirSetpointTemperature(99.0));
    detail::LoadContext context{const_cast<Model&>(model), SanitizationPolicy::Repair, SanitizationReport{}, {}};  // NOLINT
    impl->canonicalize(context);
  }

  SetpointManagerSingleZoneOneStageCooling::SetpointManagerSingleZoneOneStageCooling(
    std::shared_ptr<detail::SetpointManagerSingleZoneOneStageCooling_Impl> impl)
    : SetpointManager(std::move(impl)) {}

  IddObjectType SetpointManagerSingleZoneOneStageCooling::iddObjectType() {
    return IddObjectType::SetpointManager_SingleZone_OneStageCooling;
  }

  std::vector<std::string> SetpointManagerSingleZoneOneStageCooling::controlVariableValues() {
    return {"Temperature"};
  }

  std::string SetpointManagerSingleZoneOneStageCooling::controlVariable() const {
    return "Temperature";
  }

  bool SetpointManagerSingleZoneOneStageCooling::setControlVariable(const std::string& controlVariable) {
    return openstudio::istringEqual(controlVariable, "Temperature");
  }

  double SetpointManagerSingleZoneOneStageCooling::coolingStageOnSupplyAirSetpointTemperature() const {
    return getImpl<detail::SetpointManagerSingleZoneOneStageCooling_Impl>()->coolingStageOnSupplyAirSetpointTemperature();
  }

  bool SetpointManagerSingleZoneOneStageCooling::setCoolingStageOnSupplyAirSetpointTemperature(double coolingStageOnSupplyAirSetpointTemperature) {
    const bool result = getImpl<detail::SetpointManagerSingleZoneOneStageCooling_Impl>()->setCoolingStageOnSupplyAirSetpointTemperature(
      coolingStageOnSupplyAirSetpointTemperature);
    OS_ASSERT(result);
    return result;
  }

  double SetpointManagerSingleZoneOneStageCooling::coolingStageOffSupplyAirSetpointTemperature() const {
    return getImpl<detail::SetpointManagerSingleZoneOneStageCooling_Impl>()->coolingStageOffSupplyAirSetpointTemperature();
  }

  bool SetpointManagerSingleZoneOneStageCooling::setCoolingStageOffSupplyAirSetpointTemperature(double coolingStageOffSupplyAirSetpointTemperature) {
    const bool result = getImpl<detail::SetpointManagerSingleZoneOneStageCooling_Impl>()->setCoolingStageOffSupplyAirSetpointTemperature(
      coolingStageOffSupplyAirSetpointTemperature);
    OS_ASSERT(result);
    return result;
  }

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
  namespace detail {

    double SetpointManagerSingleZoneOneStageCooling_Impl::coolingStageOnSupplyAirSetpointTemperature() const {
      const auto value = getDouble(openstudio::SetpointManager_SingleZone_OneStageCoolingFields::CoolingStageOnSupplyAirSetpointTemperature, true);
      OS_ASSERT(value);
      return *value;
    }

    bool SetpointManagerSingleZoneOneStageCooling_Impl::setCoolingStageOnSupplyAirSetpointTemperature(
      double coolingStageOnSupplyAirSetpointTemperature) {
      const bool result = setDouble(openstudio::SetpointManager_SingleZone_OneStageCoolingFields::CoolingStageOnSupplyAirSetpointTemperature,
                                    coolingStageOnSupplyAirSetpointTemperature);
      OS_ASSERT(result);
      return result;
    }

    double SetpointManagerSingleZoneOneStageCooling_Impl::coolingStageOffSupplyAirSetpointTemperature() const {
      const auto value = getDouble(openstudio::SetpointManager_SingleZone_OneStageCoolingFields::CoolingStageOffSupplyAirSetpointTemperature, true);
      OS_ASSERT(value);
      return *value;
    }

    bool SetpointManagerSingleZoneOneStageCooling_Impl::setCoolingStageOffSupplyAirSetpointTemperature(
      double coolingStageOffSupplyAirSetpointTemperature) {
      const bool result = setDouble(openstudio::SetpointManager_SingleZone_OneStageCoolingFields::CoolingStageOffSupplyAirSetpointTemperature,
                                    coolingStageOffSupplyAirSetpointTemperature);
      OS_ASSERT(result);
      return result;
    }

    boost::optional<openstudio::epmodel::Node> SetpointManagerSingleZoneOneStageCooling_Impl::setpointNode() const {
      return getObject<ModelObject>().getModelObjectTarget<openstudio::epmodel::Node>(
        openstudio::SetpointManager_SingleZone_OneStageCoolingFields::SetpointNodeorNodeListName);
    }

    std::string SetpointManagerSingleZoneOneStageCooling_Impl::controlVariable() const {
      return "Temperature";
    }

    bool SetpointManagerSingleZoneOneStageCooling_Impl::setControlVariable(const std::string& value) {
      return openstudio::istringEqual(value, "Temperature");
    }

    bool SetpointManagerSingleZoneOneStageCooling_Impl::setSetpointNode(const openstudio::epmodel::Node& node) {
      return getObject<ModelObject>().setPointer(openstudio::SetpointManager_SingleZone_OneStageCoolingFields::SetpointNodeorNodeListName,
                                                 node.handle());
    }

    void SetpointManagerSingleZoneOneStageCooling_Impl::doCanonicalize(LoadContext& context) {
      SetpointManager_Impl::doCanonicalize(context);
      canonicalizeSetpointNodeField(context, openstudio::SetpointManager_SingleZone_OneStageCoolingFields::SetpointNodeorNodeListName);

      if (auto value = getDouble(openstudio::SetpointManager_SingleZone_OneStageCoolingFields::CoolingStageOnSupplyAirSetpointTemperature, true)) {
        (void)value;
      } else {
        OS_ASSERT(setDouble(openstudio::SetpointManager_SingleZone_OneStageCoolingFields::CoolingStageOnSupplyAirSetpointTemperature, -99.0));
        detail::addLoadInfo(context,
                            "Set default Cooling Stage On Supply Air Setpoint Temperature to -99 for SetpointManager:SingleZone:OneStageCooling '"
                              + getObject<ModelObject>().nameString() + "'.");
      }

      if (auto value = getDouble(openstudio::SetpointManager_SingleZone_OneStageCoolingFields::CoolingStageOffSupplyAirSetpointTemperature, true)) {
        (void)value;
      } else {
        OS_ASSERT(setDouble(openstudio::SetpointManager_SingleZone_OneStageCoolingFields::CoolingStageOffSupplyAirSetpointTemperature, 99.0));
        detail::addLoadInfo(context,
                            "Set default Cooling Stage Off Supply Air Setpoint Temperature to 99 for SetpointManager:SingleZone:OneStageCooling '"
                              + getObject<ModelObject>().nameString() + "'.");
      }
    }

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
