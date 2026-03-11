/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "SetpointManager/SetpointManagerSingleZoneReheat.hpp"
#include "SetpointManager/SetpointManagerSingleZoneReheat_Impl.hpp"

#include "Loop/AirLoopHVAC.hpp"
#include "Model.hpp"
#include "Node.hpp"
#include "HVACComponent/ThermalZone.hpp"
#include "HVACComponent/ThermalZone_Impl.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/idd/IddFactory.hxx>
#include <utilities/idd/IddEnums.hxx>
#include <utilities/idd/SetpointManager_SingleZone_Reheat_FieldEnums.hxx>

namespace openstudio {
namespace epmodel {

SetpointManagerSingleZoneReheat::SetpointManagerSingleZoneReheat(const Model& model)
  : SetpointManager(SetpointManagerSingleZoneReheat::iddObjectType(), model) {
  auto impl = getImpl<detail::SetpointManagerSingleZoneReheat_Impl>();
  OS_ASSERT(impl);
  OS_ASSERT(setControlVariable("Temperature"));
  OS_ASSERT(setMinimumSupplyAirTemperature(-99.0));
  OS_ASSERT(setMaximumSupplyAirTemperature(99.0));
  detail::LoadContext context{const_cast<Model&>(model), SanitizationPolicy::Repair, SanitizationReport{}, {}};  // NOLINT
  impl->canonicalize(context);
}

SetpointManagerSingleZoneReheat::SetpointManagerSingleZoneReheat(std::shared_ptr<detail::SetpointManagerSingleZoneReheat_Impl> impl)
  : SetpointManager(std::move(impl)) {}

IddObjectType SetpointManagerSingleZoneReheat::iddObjectType() {
  return IddObjectType::SetpointManager_SingleZone_Reheat;
}

std::vector<std::string> SetpointManagerSingleZoneReheat::controlVariableValues() {
  return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(),
                        openstudio::SetpointManager_SingleZone_ReheatFields::ControlVariable);
}

double SetpointManagerSingleZoneReheat::minimumSupplyAirTemperature() const {
  return getImpl<detail::SetpointManagerSingleZoneReheat_Impl>()->minimumSupplyAirTemperature();
}

double SetpointManagerSingleZoneReheat::maximumSupplyAirTemperature() const {
  return getImpl<detail::SetpointManagerSingleZoneReheat_Impl>()->maximumSupplyAirTemperature();
}

bool SetpointManagerSingleZoneReheat::setMinimumSupplyAirTemperature(double minimumSupplyAirTemperature) {
  const bool result = getImpl<detail::SetpointManagerSingleZoneReheat_Impl>()->setMinimumSupplyAirTemperature(minimumSupplyAirTemperature);
  OS_ASSERT(result);
  return result;
}

bool SetpointManagerSingleZoneReheat::setMaximumSupplyAirTemperature(double maximumSupplyAirTemperature) {
  const bool result = getImpl<detail::SetpointManagerSingleZoneReheat_Impl>()->setMaximumSupplyAirTemperature(maximumSupplyAirTemperature);
  OS_ASSERT(result);
  return result;
}

boost::optional<ThermalZone> SetpointManagerSingleZoneReheat::controlZone() const {
  return getModelObjectTarget<ThermalZone>(openstudio::SetpointManager_SingleZone_ReheatFields::ControlZoneName);
}

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
namespace detail {

double SetpointManagerSingleZoneReheat_Impl::minimumSupplyAirTemperature() const {
  const auto value = getDouble(openstudio::SetpointManager_SingleZone_ReheatFields::MinimumSupplyAirTemperature, true);
  OS_ASSERT(value);
  return *value;
}

double SetpointManagerSingleZoneReheat_Impl::maximumSupplyAirTemperature() const {
  const auto value = getDouble(openstudio::SetpointManager_SingleZone_ReheatFields::MaximumSupplyAirTemperature, true);
  OS_ASSERT(value);
  return *value;
}

bool SetpointManagerSingleZoneReheat_Impl::setMinimumSupplyAirTemperature(double minimumSupplyAirTemperature) {
  const bool result = setDouble(openstudio::SetpointManager_SingleZone_ReheatFields::MinimumSupplyAirTemperature, minimumSupplyAirTemperature);
  OS_ASSERT(result);
  return result;
}

bool SetpointManagerSingleZoneReheat_Impl::setMaximumSupplyAirTemperature(double maximumSupplyAirTemperature) {
  const bool result = setDouble(openstudio::SetpointManager_SingleZone_ReheatFields::MaximumSupplyAirTemperature, maximumSupplyAirTemperature);
  OS_ASSERT(result);
  return result;
}

bool SetpointManagerSingleZoneReheat_Impl::addToNode(Node& node) {
  if (!SetpointManager_Impl::addToNode(node)) {
    return false;
  }

  if (auto airLoop = node.airLoopHVAC()) {
    auto demandZones = airLoop->demandComponents(openstudio::IddObjectType::Zone);
    if (!demandZones.empty()) {
      auto thermalZone = demandZones.front().optionalCast<openstudio::epmodel::ThermalZone>();
      OS_ASSERT(thermalZone);
      OS_ASSERT(setControlZone(*thermalZone));
    }
  }

  return true;
}

bool SetpointManagerSingleZoneReheat_Impl::setControlZone(const ThermalZone& thermalZone) {
  return getObject<ModelObject>().setPointer(openstudio::SetpointManager_SingleZone_ReheatFields::ControlZoneName, thermalZone.handle());
}

unsigned SetpointManagerSingleZoneReheat_Impl::setpointNodeFieldIndex() const {
  return openstudio::SetpointManager_SingleZone_ReheatFields::SetpointNodeorNodeListName;
}

unsigned SetpointManagerSingleZoneReheat_Impl::controlVariableFieldIndex() const {
  return openstudio::SetpointManager_SingleZone_ReheatFields::ControlVariable;
}

void SetpointManagerSingleZoneReheat_Impl::doCanonicalize(LoadContext& context) {
  SetpointManager_Impl::doCanonicalize(context);

  if (auto value = getString(openstudio::SetpointManager_SingleZone_ReheatFields::ControlVariable, true)) {
    if (!value->empty()) {
      // continue
    } else {
      OS_ASSERT(setString(openstudio::SetpointManager_SingleZone_ReheatFields::ControlVariable, "Temperature"));
      detail::addLoadInfo(context, "Set default Control Variable to 'Temperature' for SetpointManager:SingleZone:Reheat '"
                                   + getObject<ModelObject>().nameString() + "'.");
    }
  } else {
    OS_ASSERT(setString(openstudio::SetpointManager_SingleZone_ReheatFields::ControlVariable, "Temperature"));
    detail::addLoadInfo(context, "Set default Control Variable to 'Temperature' for SetpointManager:SingleZone:Reheat '"
                                 + getObject<ModelObject>().nameString() + "'.");
  }

  if (auto value = getDouble(openstudio::SetpointManager_SingleZone_ReheatFields::MinimumSupplyAirTemperature, true)) {
    (void)value;
  } else {
    OS_ASSERT(setDouble(openstudio::SetpointManager_SingleZone_ReheatFields::MinimumSupplyAirTemperature, -99.0));
    detail::addLoadInfo(context, "Set default Minimum Supply Air Temperature to -99 for SetpointManager:SingleZone:Reheat '"
                                   + getObject<ModelObject>().nameString() + "'.");
  }

  if (auto value = getDouble(openstudio::SetpointManager_SingleZone_ReheatFields::MaximumSupplyAirTemperature, true)) {
    (void)value;
  } else {
    OS_ASSERT(setDouble(openstudio::SetpointManager_SingleZone_ReheatFields::MaximumSupplyAirTemperature, 99.0));
    detail::addLoadInfo(context, "Set default Maximum Supply Air Temperature to 99 for SetpointManager:SingleZone:Reheat '"
                                   + getObject<ModelObject>().nameString() + "'.");
  }
}

}  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
