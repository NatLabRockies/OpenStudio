/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "SetpointManager/SetpointManagerSingleZoneHumidityMinimum.hpp"
#include "SetpointManager/SetpointManagerSingleZoneHumidityMinimum_Impl.hpp"

#include "Model.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/core/Compare.hpp>
#include <utilities/idd/IddEnums.hxx>
#include <utilities/idd/SetpointManager_SingleZone_Humidity_Minimum_FieldEnums.hxx>

namespace openstudio {
namespace epmodel {

  SetpointManagerSingleZoneHumidityMinimum::SetpointManagerSingleZoneHumidityMinimum(const Model& model)
    : SetpointManager(SetpointManagerSingleZoneHumidityMinimum::iddObjectType(), model) {
    auto impl = getImpl<detail::SetpointManagerSingleZoneHumidityMinimum_Impl>();
    OS_ASSERT(impl);
    OS_ASSERT(setControlVariable("MinimumHumidityRatio"));
  }

  SetpointManagerSingleZoneHumidityMinimum::SetpointManagerSingleZoneHumidityMinimum(
    std::shared_ptr<detail::SetpointManagerSingleZoneHumidityMinimum_Impl> impl)
    : SetpointManager(std::move(impl)) {}

  IddObjectType SetpointManagerSingleZoneHumidityMinimum::iddObjectType() {
    return IddObjectType::SetpointManager_SingleZone_Humidity_Minimum;
  }

  std::vector<std::string> SetpointManagerSingleZoneHumidityMinimum::controlVariableValues() {
    return {"MinimumHumidityRatio"};
  }

  std::string SetpointManagerSingleZoneHumidityMinimum::controlVariable() const {
    return "MinimumHumidityRatio";
  }

  bool SetpointManagerSingleZoneHumidityMinimum::setControlVariable(const std::string& controlVariable) {
    return openstudio::istringEqual(controlVariable, "MinimumHumidityRatio");
  }

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
  namespace detail {

    boost::optional<openstudio::epmodel::Node> SetpointManagerSingleZoneHumidityMinimum_Impl::setpointNode() const {
      return getObject<ModelObject>().getModelObjectTarget<openstudio::epmodel::Node>(
        openstudio::SetpointManager_SingleZone_Humidity_MinimumFields::SetpointNodeorNodeListName);
    }

    std::string SetpointManagerSingleZoneHumidityMinimum_Impl::controlVariable() const {
      return "MinimumHumidityRatio";
    }

    bool SetpointManagerSingleZoneHumidityMinimum_Impl::setControlVariable(const std::string& value) {
      return openstudio::istringEqual(value, "MinimumHumidityRatio");
    }

    bool SetpointManagerSingleZoneHumidityMinimum_Impl::setSetpointNode(const openstudio::epmodel::Node& node) {
      return getObject<ModelObject>().setPointer(openstudio::SetpointManager_SingleZone_Humidity_MinimumFields::SetpointNodeorNodeListName,
                                                 node.handle());
    }

    void SetpointManagerSingleZoneHumidityMinimum_Impl::doCanonicalize(LoadContext& context) {
      SetpointManager_Impl::doCanonicalize(context);
      canonicalizeSetpointNodeField(context, openstudio::SetpointManager_SingleZone_Humidity_MinimumFields::SetpointNodeorNodeListName);
    }

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
